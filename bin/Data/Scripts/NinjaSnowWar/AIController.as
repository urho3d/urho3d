const float initialAggression = 0.0020;
const float initialPrediction = 30;
const float initialAimSpeed = 10;
const float deltaAggression = 0.000025;
const float deltaPrediction = -0.15;
const float deltaAimSpeed = 0.30;
const float maxAggression = 0.01;
const float maxPrediction = 20;
const float maxAimSpeed = 40;

float aiAggression = initialAggression;
float aiPrediction = initialPrediction;
float aiAimSpeed = initialAimSpeed;

void ResetAI()
{
    aiAggression = initialAggression;
    aiPrediction = initialPrediction;
    aiAimSpeed = initialAimSpeed;
}

void MakeAIHarder()
{
    aiAggression += deltaAggression;
    if (aiAggression > maxAggression)
        aiAggression = maxAggression;

    aiPrediction += deltaPrediction;
    if (aiPrediction < maxPrediction)
        aiPrediction = maxPrediction;

    aiAimSpeed += deltaAimSpeed;
    if (aiAimSpeed > maxAimSpeed)
        aiAimSpeed = maxAimSpeed;
}

class AIController
{
    // Use a weak handle instead of a normal handle to point to the current target
    // so that we don't mistakenly keep it alive.
    WeakHandle currentTarget;
    float newTargetTimer = 0;

    void Control(Ninja@ ownNinja, Node@ ownNode, float timeStep)
    {
        // Get new target if none. Do not constantly scan for new targets to conserve CPU time
        if (currentTarget.Get() is null)
        {
            newTargetTimer += timeStep;
            if (newTargetTimer > 0.5)
                GetNewTarget(ownNode);
        }

        Node@ targetNode = currentTarget.Get();

        if (targetNode !is null)
        {
            // Check that current target is still alive. Otherwise choose new
            Ninja@ targetNinja = cast<Ninja>(targetNode.scriptObject);
            if (targetNinja is null || targetNinja.health <= 0)
            {
                currentTarget = null;
                return;
            }

            RigidBody@ targetBody = targetNode.GetComponent("RigidBody");

            ownNinja.controls.Set(CTRL_FIRE, false);
            ownNinja.controls.Set(CTRL_JUMP, false);

            float deltaX = 0.0f;
            float deltaY = 0.0f;

            // Aim from own head to target's feet
            Vector3 ownPos(ownNode.position + Vector3(0, 0.9, 0));
            Vector3 targetPos(targetNode.position + Vector3(0, -0.9, 0));
            float distance = (targetPos - ownPos).length;

            // Use prediction according to target distance & estimated snowball speed
            Vector3 currentAim(ownNinja.GetAim() * Vector3(0, 0, 1));
            float predictDistance = distance;
            if (predictDistance > 50) predictDistance = 50;
            Vector3 predictedPos = targetPos + targetBody.linearVelocity * predictDistance / aiPrediction;
            Vector3 targetAim = (predictedPos - ownPos);

            // Add distance/height compensation
            float compensation = Max(targetAim.length - 15, 0.0);
            targetAim += Vector3(0, 0.6, 0) * compensation;

            // X-aiming
            targetAim.Normalize();
            Vector3 currentYaw(currentAim.x, 0, currentAim.z);
            Vector3 targetYaw(targetAim.x, 0, targetAim.z);
            currentYaw.Normalize();
            targetYaw.Normalize();
            deltaX = Clamp(Quaternion(currentYaw, targetYaw).yaw, -aiAimSpeed, aiAimSpeed);

            // Y-aiming
            Vector3 currentPitch(0, currentAim.y, 1);
            Vector3 targetPitch(0, targetAim.y, 1);
            currentPitch.Normalize();
            targetPitch.Normalize();
            deltaY = Clamp(Quaternion(currentPitch, targetPitch).pitch, -aiAimSpeed, aiAimSpeed);

            ownNinja.controls.yaw += 0.1 * deltaX;
            ownNinja.controls.pitch += 0.1 * deltaY;

            // Firing? if close enough and relatively correct aim
            if ((distance < 25) && (currentAim.DotProduct(targetAim) > 0.75))
            {
                if (Random(1.0) < aiAggression)
                    ownNinja.controls.Set(CTRL_FIRE, true);
            }

            // Movement
            ownNinja.dirChangeTime -= timeStep;
            if (ownNinja.dirChangeTime <= 0)
            {
                ownNinja.dirChangeTime = 0.5 + Random(1.0);
                ownNinja.controls.Set(CTRL_UP|CTRL_DOWN|CTRL_LEFT|CTRL_RIGHT, false);

                // Far distance: go forward
                if (distance > 30)
                    ownNinja.controls.Set(CTRL_UP, true);
                else if (distance > 6)
                {
                    // Medium distance: random strafing, predominantly forward
                    float v = Random(1.0);
                    if (v < 0.8)
                        ownNinja.controls.Set(CTRL_UP, true);
                    float h = Random(1.0);
                    if (h < 0.3)
                        ownNinja.controls.Set(CTRL_LEFT, true);
                    if (h > 0.7)
                        ownNinja.controls.Set(CTRL_RIGHT, true);
                }
                else
                {
                    // Close distance: random strafing backwards
                    float v = Random(1.0);
                    if (v < 0.8)
                        ownNinja.controls.Set(CTRL_DOWN, true);
                    float h = Random(1.0);
                    if (h < 0.4)
                        ownNinja.controls.Set(CTRL_LEFT, true);
                    if (h > 0.6)
                        ownNinja.controls.Set(CTRL_RIGHT, true);
                }
            }

            // Random jump, if going forward
            if ((ownNinja.controls.IsDown(CTRL_UP)) && (distance < 1000))
            {
                if (Random(1.0) < (aiAggression / 5.0))
                    ownNinja.controls.Set(CTRL_JUMP, true);
            }
        }
        else
        {
            // If no target, walk idly
            ownNinja.controls.Set(CTRL_ALL, false);
            ownNinja.controls.Set(CTRL_UP, true);
            ownNinja.dirChangeTime -= timeStep;
            if (ownNinja.dirChangeTime <= 0)
            {
                ownNinja.dirChangeTime = 1 + Random(2);
                ownNinja.controls.yaw += 0.1 * (Random(600) - 300);
            }
            if (ownNinja.isSliding)
                ownNinja.controls.yaw += 0.2;
        }
    }

    void GetNewTarget(Node@ ownNode)
    {
        newTargetTimer = 0;

        Array<Node@> nodes = ownNode.scene.GetChildrenWithScript("Ninja", true);
        float closestDistance = M_INFINITY;
        for (uint i = 0; i < nodes.length; ++i)
        {
            Node@ otherNode = nodes[i];
            Ninja@ otherNinja = cast<Ninja>(otherNode.scriptObject);
            if (otherNinja.side == SIDE_PLAYER && otherNinja.health > 0)
            {
                float distance = (ownNode.position - otherNode.position).lengthSquared;
                if (distance < closestDistance)
                {
                    currentTarget = otherNode;
                    closestDistance = distance;
                }
            }
        }
    }
}
