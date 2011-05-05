const float initialAggression = 0.0020;
const float initialPrediction = 3000;
const float initialAimSpeed = 5;
const float deltaAggression = 0.00005;
const float deltaPrediction = -20;
const float deltaAimSpeed = 0.15;
const float maxAggression = 0.01;
const float maxPrediction = 2000;
const float maxAimSpeed = 20;

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
    void Control(Ninja@ ninja, Node@ node, float timeStep)
    {
        Scene@ scene = node.scene;

        // Get closest ninja on the player's side
        Node@ targetNode;
        Ninja@ targetNinja;
        Array<Node@> nodes = scene.GetScriptedChildren("Ninja", true);
        float closestDistance = M_INFINITY;
        for (uint i = 0; i < nodes.length; ++i)
        {
            Node@ otherNode = nodes[i];
            Ninja@ otherNinja = cast<Ninja>(otherNode.scriptObject);
            if (otherNinja.side == SIDE_PLAYER)
            {
                float distance = (node.position - otherNode.position).length;
                if (distance < closestDistance)
                {
                    @targetNode = otherNode;
                    @targetNinja = otherNinja;
                    closestDistance = distance;
                }
            }
        }

        if ((targetNode !is null) && (targetNinja.health > 0))
        {
            RigidBody@ targetBody = targetNode.GetComponent("RigidBody");

            ninja.controls.Set(CTRL_FIRE, false);
            ninja.controls.Set(CTRL_JUMP, false);

            float deltaX = 0.0f;
            float deltaY = 0.0f;

            // Aim from own head to target's feet
            Vector3 ownPos(node.position + Vector3(0, 90, 0));
            Vector3 targetPos(targetNode.position + Vector3(0, -90, 0));
            float distance = (targetPos - ownPos).length;

            // Use prediction according to target distance & estimated snowball speed
            Vector3 currentAim(ninja.GetAim() * Vector3(0, 0, 1));
            float predictDistance = distance;
            if (predictDistance > 5000) predictDistance = 5000;
            Vector3 predictedPos = targetPos + targetBody.linearVelocity * predictDistance / aiPrediction;
            Vector3 targetAim = (predictedPos - ownPos);

            // Add distance/height compensation
            float compensation = Max(targetAim.length - 1500, 0);
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

            ninja.controls.yaw += 0.1 * deltaX;
            ninja.controls.pitch += 0.1 * deltaY;

            // Firing? if close enough and relatively correct aim
            if ((distance < 2500) && (currentAim.DotProduct(targetAim) > 0.75))
            {
                if (Random(1.0) < aiAggression)
                    ninja.controls.Set(CTRL_FIRE, true);
            }

            // Movement
            ninja.dirChangeTime -= timeStep;
            if (ninja.dirChangeTime <= 0)
            {
                ninja.dirChangeTime = 0.5 + Random(1.0);
                ninja.controls.Set(CTRL_UP|CTRL_DOWN|CTRL_LEFT|CTRL_RIGHT, false);

                // Far distance: go forward
                if (distance > 3000)
                    ninja.controls.Set(CTRL_UP, true);
                else if (distance > 600)
                {
                    // Medium distance: random strafing, predominantly forward
                    float v = Random(1.0);
                    if (v < 0.8)
                        ninja.controls.Set(CTRL_UP, true);
                    float h = Random(1.0);
                    if (h < 0.3)
                        ninja.controls.Set(CTRL_LEFT, true);
                    if (h > 0.7)
                        ninja.controls.Set(CTRL_RIGHT, true);
                }
                else
                {
                    // Close distance: random strafing backwards
                    float v = Random(1.0);
                    if (v < 0.8)
                        ninja.controls.Set(CTRL_DOWN, true);
                    float h = Random(1.0);
                    if (h < 0.4)
                        ninja.controls.Set(CTRL_LEFT, true);
                    if (h > 0.6)
                        ninja.controls.Set(CTRL_RIGHT, true);
                }
            }

            // Random jump, if going forward
            if ((ninja.controls.IsDown(CTRL_UP)) && (distance < 1000))
            {
                if (Random(1.0) < (aiAggression / 5.0))
                    ninja.controls.Set(CTRL_JUMP, true);
            }
        }
        else
        {
            // If no target, walk idly
            ninja.controls.Set(CTRL_ALL, false);
            ninja.controls.Set(CTRL_UP, true);
            ninja.dirChangeTime -= timeStep;
            if (ninja.dirChangeTime <= 0)
            {
                ninja.dirChangeTime = 1.0 + Random(2.0);
                ninja.controls.yaw += 0.1 * (Random(600.0) - 300.0);
            }
            if (ninja.isSliding)
                ninja.controls.yaw += 0.2;
        }
    }
}