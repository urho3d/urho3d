// Copyright (c) 2022-2023 the Dviglo project
// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#include "ai_controller.h"

#include "ninja.h"

namespace Urho3D
{

static constexpr float INITIAL_AGGRESSION = 0.0020f;
static constexpr float INITIAL_PREDICTION = 30.f;
static constexpr float INITIAL_AIM_SPEED = 10.f;
static constexpr float DELTA_AGGRESSION = 0.000025f;
static constexpr float DELTA_PREDICTION = -0.15f;
static constexpr float DELTA_AIM_SPEED = 0.30f;
static constexpr float MAX_AGGRESSION = 0.01f;
static constexpr float MAX_PREDICTION = 20.f;
static constexpr float MAX_AIM_SPEED = 40.f;

float aiAggression = INITIAL_AGGRESSION;
float aiPrediction = INITIAL_PREDICTION;
float aiAimSpeed = INITIAL_AIM_SPEED;

void ResetAI()
{
    aiAggression = INITIAL_AGGRESSION;
    aiPrediction = INITIAL_PREDICTION;
    aiAimSpeed = INITIAL_AIM_SPEED;
}

void MakeAIHarder()
{
    aiAggression += DELTA_AGGRESSION;
    if (aiAggression > MAX_AGGRESSION)
        aiAggression = MAX_AGGRESSION;

    aiPrediction += DELTA_PREDICTION;
    if (aiPrediction < MAX_PREDICTION)
        aiPrediction = MAX_PREDICTION;

    aiAimSpeed += DELTA_AIM_SPEED;
    if (aiAimSpeed > MAX_AIM_SPEED)
        aiAimSpeed = MAX_AIM_SPEED;
}

void AIController::Control(Ninja* ownNinja, Node* ownNode, float timeStep)
{
    // Get new target if none. Do not constantly scan for new targets to conserve CPU time
    if (!currentTarget)
    {
        newTargetTimer += timeStep;
        if (newTargetTimer > 0.5)
            GetNewTarget(ownNode);
    }

    Node* targetNode = currentTarget.Get();

    if (targetNode)
    {
        // Check that current target is still alive. Otherwise choose new
        Ninja* targetNinja = targetNode->GetComponent<Ninja>();
        if (!targetNinja || targetNinja->health <= 0.f)
        {
            currentTarget = nullptr;
            return;
        }

        RigidBody* targetBody = targetNode->GetComponent<RigidBody>();

        ownNinja->controls.Set(CTRL_FIRE, false);
        ownNinja->controls.Set(CTRL_JUMP, false);

        float deltaX = 0.0f;
        float deltaY = 0.0f;

        // Aim from own head to target's feet
        Vector3 ownPos(ownNode->GetPosition() + Vector3(0.f, 0.9f, 0.f));
        Vector3 targetPos(targetNode->GetPosition() + Vector3(0.f, -0.9f, 0.f));
        float distance = (targetPos - ownPos).Length();

        // Use prediction according to target distance & estimated snowball speed
        Vector3 currentAim(ownNinja->GetAim() * Vector3(0.f, 0.f, 1.f));
        float predictDistance = distance;
        if (predictDistance > 50.f)
            predictDistance = 50.f;
        Vector3 predictedPos = targetPos + targetBody->GetLinearVelocity() * predictDistance / aiPrediction;
        Vector3 targetAim = predictedPos - ownPos;

        // Add distance/height compensation
        float compensation = Max(targetAim.Length() - 15.f, 0.0f);
        targetAim += Vector3(0.f, 0.6f, 0.f) * compensation;

        // X-aiming
        targetAim.Normalize();
        Vector3 currentYaw(currentAim.x_, 0.f, currentAim.z_);
        Vector3 targetYaw(targetAim.x_, 0.f, targetAim.z_);
        currentYaw.Normalize();
        targetYaw.Normalize();
        deltaX = Clamp(Quaternion(currentYaw, targetYaw).YawAngle(), -aiAimSpeed, aiAimSpeed);

        // Y-aiming
        Vector3 currentPitch(0.f, currentAim.y_, 1.f);
        Vector3 targetPitch(0.f, targetAim.y_, 1.f);
        currentPitch.Normalize();
        targetPitch.Normalize();
        deltaY = Clamp(Quaternion(currentPitch, targetPitch).PitchAngle(), -aiAimSpeed, aiAimSpeed);

        ownNinja->controls.yaw_ += 0.1f * deltaX;
        ownNinja->controls.pitch_ += 0.1f * deltaY;

        // Firing? if close enough and relatively correct aim
        if (distance < 25.f && currentAim.DotProduct(targetAim) > 0.75f)
        {
            if (Random(1.0f) < aiAggression)
                ownNinja->controls.Set(CTRL_FIRE, true);
        }

        // Movement
        ownNinja->dirChangeTime -= timeStep;
        if (ownNinja->dirChangeTime <= 0.f)
        {
            ownNinja->dirChangeTime = 0.5f + Random(1.0f);
            ownNinja->controls.Set(CTRL_UP | CTRL_DOWN | CTRL_LEFT | CTRL_RIGHT, false);

            // Far distance: go forward
            if (distance > 30.f)
                ownNinja->controls.Set(CTRL_UP, true);
            else if (distance > 6)
            {
                // Medium distance: random strafing, predominantly forward
                float v = Random(1.0f);
                if (v < 0.8f)
                    ownNinja->controls.Set(CTRL_UP, true);
                float h = Random(1.0f);
                if (h < 0.3f)
                    ownNinja->controls.Set(CTRL_LEFT, true);
                if (h > 0.7f)
                    ownNinja->controls.Set(CTRL_RIGHT, true);
            }
            else
            {
                // Close distance: random strafing backwards
                float v = Random(1.0f);
                if (v < 0.8f)
                    ownNinja->controls.Set(CTRL_DOWN, true);
                float h = Random(1.0f);
                if (h < 0.4f)
                    ownNinja->controls.Set(CTRL_LEFT, true);
                if (h > 0.6f)
                    ownNinja->controls.Set(CTRL_RIGHT, true);
            }
        }

        // Random jump, if going forward
        if (ownNinja->controls.IsDown(CTRL_UP) && distance < 1000.f)
        {
            if (Random(1.0f) < aiAggression / 5.0f)
                ownNinja->controls.Set(CTRL_JUMP, true);
        }
    }
    else
    {
        // If no target, walk idly
        ownNinja->controls.Set(CTRL_ALL, false);
        ownNinja->controls.Set(CTRL_UP, true);
        ownNinja->dirChangeTime -= timeStep;
        if (ownNinja->dirChangeTime <= 0.f)
        {
            ownNinja->dirChangeTime = 1.f + Random(2.f);
            ownNinja->controls.yaw_ += 0.1f * (Random(600.f) - 300.f);
        }
        if (ownNinja->isSliding)
            ownNinja->controls.yaw_ += 0.2f;
    }
}

void AIController::GetNewTarget(Node* ownNode)
{
    newTargetTimer = 0;

    Vector<Node*> nodes = ownNode->GetScene()->GetChildrenWithComponent("Ninja", true);
    float closestDistance = M_INFINITY;
    for (i32 i = 0; i < nodes.Size(); ++i)
    {
        Node* otherNode = nodes[i];
        Ninja* otherNinja = otherNode->GetComponent<Ninja>();
        if (otherNinja->side == SIDE_PLAYER && otherNinja->health > 0.f)
        {
            float distance = (ownNode->GetPosition() - otherNode->GetPosition()).LengthSquared();
            if (distance < closestDistance)
            {
                currentTarget = otherNode;
                closestDistance = distance;
            }
        }
    }
}

} // namespace Urho3D
