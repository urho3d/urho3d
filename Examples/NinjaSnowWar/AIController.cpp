//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Precompiled.h"
#include "AIController.h"
#include "Controls.h"
#include "Deserializer.h"
#include "Entity.h"
#include "GameConfig.h"
#include "Ninja.h"
#include "RigidBody.h"
#include "Scene.h"
#include "Serializer.h"

#include "DebugNew.h"

static float aggression;
static float prediction;
static float aimSpeed;
static float maxAggression;
static float maxPrediction;
static float maxAimSpeed;
static float deltaAggression;
static float deltaPrediction;
static float deltaAimSpeed;

void AIController::setup()
{
    GameConfig::setSection("AI");
    
    aggression = GameConfig::getReal("Aggression");
    prediction = GameConfig::getReal("Prediction");
    aimSpeed = GameConfig::getReal("AimSpeed");
    maxAggression = GameConfig::getReal("MaxAggression");
    maxPrediction = GameConfig::getReal("MaxPrediction");
    maxAimSpeed = GameConfig::getReal("MaxAimSpeed");
    deltaAggression = GameConfig::getReal("DeltaAggression");
    deltaPrediction = GameConfig::getReal("DeltaPrediction");
    deltaAimSpeed = GameConfig::getReal("DeltaAimSpeed");
    
    GameConfig::setSection("");
}

void AIController::save(Serializer& dest)
{
    dest.writeFloat(aggression);
    dest.writeFloat(prediction);
    dest.writeFloat(aimSpeed);
    dest.writeFloat(maxAggression);
    dest.writeFloat(maxPrediction);
    dest.writeFloat(maxAimSpeed);
    dest.writeFloat(deltaAggression);
    dest.writeFloat(deltaPrediction);
    dest.writeFloat(deltaAimSpeed);
}

void AIController::load(Deserializer& source)
{
    aggression = source.readFloat();
    prediction = source.readFloat();
    aimSpeed = source.readFloat();
    maxAggression = source.readFloat();
    maxPrediction = source.readFloat();
    maxAimSpeed = source.readFloat();
    deltaAggression = source.readFloat();
    deltaPrediction = source.readFloat();
    deltaAimSpeed = source.readFloat();
}

void AIController::makeHarder()
{
    aggression += deltaAggression;
    prediction += deltaPrediction;
    aimSpeed += deltaAimSpeed;
    
    if (aggression > maxAggression) aggression = maxAggression;
    if (prediction < maxPrediction) prediction = maxPrediction;
    if (aimSpeed > maxAimSpeed) aimSpeed = maxAimSpeed;
}

void AIController::control(Ninja* ninja, float time)
{
    // Get closest ninja on the players' side
    Ninja* target = 0;
    float closestDistance = M_INFINITY;
    Scene* scene = ninja->getScene();
    const std::map<EntityID, SharedPtr<Entity> >& entities = scene->getEntities();
    for (std::map<EntityID, SharedPtr<Entity> >::const_iterator i = entities.begin(); i != entities.end(); ++i)
    {
        Entity* entity = i->second;
        Ninja* testTarget = entity->getComponent<Ninja>();
        if (testTarget)
        {
            if (testTarget->getSide() == SIDE_PLAYER)
            {
                float distance = (ninja->getBody()->getPosition() - testTarget->getBody()->getPosition()).getLengthSquared();
                if (distance < closestDistance)
                {
                    target = testTarget;
                    closestDistance = distance;
                }
            }
        }
    }
    
    if ((target) && (target->getHealth() > 0))
    {
        ninja->mControls.set(CTRL_FIRE, false);
        ninja->mControls.set(CTRL_JUMP, false);
        
        float deltaX = 0.0f;
        float deltaY = 0.0f;
        
        // Aim from own head to target's feet
        Vector3 ownPos(ninja->getBody()->getPosition() + Vector3(0,90,0));
        Vector3 targetPos(target->getBody()->getPosition() + Vector3(0,-90,0));
        float distance = (targetPos - ownPos).getLength();
        
        // Use prediction according to target distance & estimated snowball speed
        Vector3 currentAim(ninja->getAim() * Vector3::sForward);
        float predictDistance = distance;
        if (predictDistance > 5000) predictDistance = 5000;
        Vector3 predictedPos = targetPos + target->getBody()->getLinearVelocity() * predictDistance / prediction;
        Vector3 targetAim = (predictedPos - ownPos);
        
        // Add distance/height compensation
        float compensation = max(targetAim.getLength() - 1500, 0.0f);
        targetAim += compensation * compensation * Vector3(0,0.005f,0);
        
        // X-aiming
        targetAim.normalize();
        Vector3 currentYaw(currentAim.mX, 0, currentAim.mZ);
        Vector3 targetYaw(targetAim.mX, 0, targetAim.mZ);
        currentYaw.normalize();
        targetYaw.normalize();
        deltaX = clamp(Quaternion(currentYaw, targetYaw).getYaw(), -aimSpeed, aimSpeed);
        
        // Y-aiming
        Vector3 currentPitch(0, currentAim.mY, 1.0f);
        Vector3 targetPitch(0, targetAim.mY, 1.0f);
        currentPitch.normalize();
        targetPitch.normalize();
        deltaY = clamp(Quaternion(currentPitch, targetPitch).getPitch(), -aimSpeed, aimSpeed);
        
        ninja->mControls.mYaw += 0.1f * deltaX;
        ninja->mControls.mPitch += 0.1f * deltaY;
        
        // Firing? if close enough and relatively correct aim
        if ((distance < 2500) && (currentAim.dotProduct(targetAim) > 0.75f))
        {
            if (random(1.0f) < aggression)
                ninja->mControls.set(CTRL_FIRE, true);
        }
        
        // Movement
        ninja->mDirChangeTime -= time;
        if (ninja->mDirChangeTime <= 0)
        {
            ninja->mDirChangeTime = 0.5f + random(1.0f);
            ninja->mControls.set(CTRL_UP|CTRL_DOWN|CTRL_LEFT|CTRL_RIGHT, false);
            
            // Far distance: go forward
            if (distance > 3000)
                ninja->mControls.set(CTRL_UP, true);
            else if (distance > 600)
            {
                // Medium distance: random strafing, predominantly forward
                float v = random(1.0f);
                if (v < 0.8)
                    ninja->mControls.set(CTRL_UP, true);
                float h = random(1.0f);
                if (h < 0.3)
                    ninja->mControls.set(CTRL_LEFT, true);
                if (h > 0.7)
                    ninja->mControls.set(CTRL_RIGHT, true);
            }
            else
            {
                // Close distance: random strafing backwards
                float v = random(1.0f);
                if (v < 0.8)
                    ninja->mControls.set(CTRL_DOWN, true);
                float h = random(1.0f);
                if (h < 0.4)
                    ninja->mControls.set(CTRL_LEFT, true);
                if (h > 0.6)
                    ninja->mControls.set(CTRL_RIGHT, true);
            }
        }
        
        // Random jump, if going forward
        if ((ninja->mControls.isDown(CTRL_UP)) && (distance < 1000))
        { 
            if (random(1.0f) < (aggression / 5.0f))
                ninja->mControls.set(CTRL_JUMP, true);
        }
    }
    else
    {
        // If no target, walk idly
        ninja->mControls.set(CTRL_ALL, false);
        ninja->mControls.set(CTRL_UP, true);
        ninja->mDirChangeTime -= time;
        if (ninja->mDirChangeTime <= 0)
        {
            ninja->mDirChangeTime = 1 + random(2.0f);
            ninja->mControls.mYaw += 0.1f * (random(600.0f) - 300.0f);
        }
        if (ninja->isSliding())
            ninja->mControls.mYaw += 0.2f;
    }
}
