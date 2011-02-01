const float initialAggression = 0.0025;
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

void resetAI()
{
    aiAggression = initialAggression;
    aiPrediction = initialPrediction;
    aiAimSpeed = initialAimSpeed;
}

void makeAIHarder()
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
    void control(Ninja@ ninja, Entity@ entity, float timeStep)
    {
        Scene@ scene = entity.getScene();
        RigidBody@ body = entity.getComponent("RigidBody");

        // Get closest ninja on the player's side
        Entity@ targetEntity;
        Ninja@ targetNinja;
        RigidBody@ targetBody;
        array<Entity@> entities = scene.getScriptedEntities("Ninja");
        float closestDistance = M_INFINITY;
        for (uint i = 0; i < entities.length(); ++i)
        {
            Ninja@ otherNinja = cast<Ninja>(entities[i].getScriptObject());
            RigidBody@ otherBody = entities[i].getComponent("RigidBody");
            if (otherNinja.side == SIDE_PLAYER)
            {
                float distance = (body.getPhysicsPosition() - otherBody.getPhysicsPosition()).getLength();
                if (distance < closestDistance)
                {
                    @targetEntity = entities[i];
                    @targetNinja = otherNinja;
                    @targetBody = otherBody;
                    closestDistance = distance;
                }
            }
        }

        if ((@targetEntity != null) && (targetNinja.health > 0))
        {
            ninja.controls.set(CTRL_FIRE, false);
            ninja.controls.set(CTRL_JUMP, false);

            float deltaX = 0.0f;
            float deltaY = 0.0f;

            // Aim from own head to target's feet
            Vector3 ownPos(body.getPhysicsPosition() + Vector3(0, 90, 0));
            Vector3 targetPos(targetBody.getPhysicsPosition() + Vector3(0, -90, 0));
            float distance = (targetPos - ownPos).getLength();

            // Use prediction according to target distance & estimated snowball speed
            Vector3 currentAim(ninja.getAim() * Vector3(0, 0, 1));
            float predictDistance = distance;
            if (predictDistance > 5000) predictDistance = 5000;
            Vector3 predictedPos = targetPos + targetBody.getLinearVelocity() * predictDistance / aiPrediction;
            Vector3 targetAim = (predictedPos - ownPos);

            // Add distance/height compensation
            float compensation = max(targetAim.getLength() - 1500, 0);
            targetAim += Vector3(0, 0.005, 0) * (compensation * compensation);

            // X-aiming
            targetAim.normalize();
            Vector3 currentYaw(currentAim.x, 0, currentAim.z);
            Vector3 targetYaw(targetAim.x, 0, targetAim.z);
            currentYaw.normalize();
            targetYaw.normalize();
            deltaX = clamp(Quaternion(currentYaw, targetYaw).getYaw(), -aiAimSpeed, aiAimSpeed);

            // Y-aiming
            Vector3 currentPitch(0, currentAim.y, 1);
            Vector3 targetPitch(0, targetAim.y, 1);
            currentPitch.normalize();
            targetPitch.normalize();
            deltaY = clamp(Quaternion(currentPitch, targetPitch).getPitch(), -aiAimSpeed, aiAimSpeed);

            ninja.controls.yaw += 0.1 * deltaX;
            ninja.controls.pitch += 0.1 * deltaY;

            // Firing? if close enough and relatively correct aim
            if ((distance < 2500) && (currentAim.dotProduct(targetAim) > 0.75))
            {
                if (random(1.0) < aiAggression)
                    ninja.controls.set(CTRL_FIRE, true);
            }

            // Movement
            ninja.dirChangeTime -= timeStep;
            if (ninja.dirChangeTime <= 0)
            {
                ninja.dirChangeTime = 0.5 + random(1.0);
                ninja.controls.set(CTRL_UP|CTRL_DOWN|CTRL_LEFT|CTRL_RIGHT, false);

                // Far distance: go forward
                if (distance > 3000)
                    ninja.controls.set(CTRL_UP, true);
                else if (distance > 600)
                {
                    // Medium distance: random strafing, predominantly forward
                    float v = random(1.0);
                    if (v < 0.8)
                        ninja.controls.set(CTRL_UP, true);
                    float h = random(1.0);
                    if (h < 0.3)
                        ninja.controls.set(CTRL_LEFT, true);
                    if (h > 0.7)
                        ninja.controls.set(CTRL_RIGHT, true);
                }
                else
                {
                    // Close distance: random strafing backwards
                    float v = random(1.0);
                    if (v < 0.8)
                        ninja.controls.set(CTRL_DOWN, true);
                    float h = random(1.0);
                    if (h < 0.4)
                        ninja.controls.set(CTRL_LEFT, true);
                    if (h > 0.6)
                        ninja.controls.set(CTRL_RIGHT, true);
                }
            }

            // Random jump, if going forward
            if ((ninja.controls.isDown(CTRL_UP)) && (distance < 1000))
            {
                if (random(1.0) < (aiAggression / 5.0))
                    ninja.controls.set(CTRL_JUMP, true);
            }
        }
        else
        {
            // If no target, walk idly
            ninja.controls.set(CTRL_ALL, false);
            ninja.controls.set(CTRL_UP, true);
            ninja.dirChangeTime -= timeStep;
            if (ninja.dirChangeTime <= 0)
            {
                ninja.dirChangeTime = 1 + random(2.0);
                ninja.controls.yaw += 0.1 * (random(600.0) - 300.0);
            }
            if (ninja.isSliding)
                ninja.controls.yaw += 0.2;
        }
    }
}