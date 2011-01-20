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
#include "AnimatedModel.h"
#include "AnimationController.h"
#include "CollisionShape.h"
#include "Deserializer.h"
#include "Entity.h"
#include "GameConfig.h"
#include "GameEvents.h"
#include "Light.h"
#include "Material.h"
#include "Ninja.h"
#include "ParticleEmitter.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "RigidBody.h"
#include "Serializer.h"
#include "SnowBall.h"
#include "Texture2D.h"
#include "XMLFile.h"

#include "DebugNew.h"

static int tPoints;
static int tHealth;
static float tMass;
static float tFriction;
static float tMaxYAim;
static float tMinYAim;
static float tMoveForce;
static float tAirMoveForce;
static float tDampingForce;
static float tJumpForce;
static float tCorpseDuration;
static Vector3 tThrowVelocity;
static Vector3 tThrowPosition;
static float tThrowDelay;
static float tRenderDistance;

// Animation groups
static const int ANIM_MOVE = 1;
static const int ANIM_ATTACK = 2;

void Ninja::setup()
{
    GameConfig::setSection("Objects/Ninja");
    
    tPoints = GameConfig::getInt("Points");
    tHealth = GameConfig::getInt("Health");
    tMass = GameConfig::getReal("Mass");
    tFriction = GameConfig::getReal("Friction");
    tMaxYAim = GameConfig::getReal("MaxYAim");
    tMinYAim = GameConfig::getReal("MinYAim");
    tMoveForce = GameConfig::getReal("MoveForce");
    tAirMoveForce = GameConfig::getReal("AirMoveForce");
    tDampingForce = GameConfig::getReal("DampingForce");
    tJumpForce = GameConfig::getReal("JumpForce");
    tCorpseDuration = GameConfig::getReal("CorpseDuration");
    tThrowVelocity = GameConfig::getVector3("ThrowVelocity");
    tThrowPosition = GameConfig::getVector3("ThrowPosition");
    tThrowDelay = GameConfig::getReal("ThrowDelay");
    tRenderDistance = GameConfig::getReal("RenderDistance");
    
    GameConfig::setSection();
}

Ninja::Ninja() :
    mOkToJump(false),
    mSmoke(false),
    mInAirTime(1.0f),
    mOnGroundTime(0.0f),
    mThrowTime(0.0f),
    mDeathTime(0.0f),
    mDeathDir(0.0f),
    mDirChangeTime(0.0f),
    mAimX(0),
    mAimY(0)
{
    mMaxHealth = tHealth;
    mPoints = tPoints;
}

void Ninja::save(Serializer& dest)
{
    // Write GameObject properties
    GameObject::save(dest);
    
    // Write Ninja properties
    dest.writeBool(mOkToJump);
    dest.writeBool(mSmoke);
    dest.writeFloat(mDeathTime);
    dest.writeFloat(mInAirTime);
    dest.writeFloat(mOnGroundTime);
    dest.writeFloat(mDeathDir);
    dest.writeFloat(mThrowTime);
    dest.writeFloat(mDirChangeTime);
    dest.writeFloat(mAimX);
    dest.writeFloat(mAimY);
    // This function is used both for singleplayer load/save, and restoring predicted entities
    // For prediction restore, we do not want to save controls
    if (!isProxy())
    {
        mControls.write(dest);
        mPrevControls.write(dest);
    }
}

void Ninja::load(Deserializer& source, ResourceCache* cache)
{
    // Read GameObject properties
    GameObject::load(source, cache);
    
    // Read Ninja properties
    mOkToJump = source.readBool();
    mSmoke = source.readBool();
    mDeathTime = source.readFloat();
    mInAirTime = source.readFloat();
    mOnGroundTime = source.readFloat();
    mDeathDir = source.readFloat();
    mThrowTime = source.readFloat();
    mDirChangeTime = source.readFloat();
    mAimX = source.readFloat();
    mAimY = source.readFloat();
    // This function is used both for singleplayer load/save, and restoring predicted entities
    // For prediction restore, we do not want to save controls
    if (!isProxy())
    {
        mControls.read(source);
        mPrevControls.read(source);
    }
}

void Ninja::saveXML(XMLElement& dest)
{
    // Write GameObject properties
    GameObject::saveXML(dest);
    
    // Write Ninja properties
    XMLElement ninjaElem = dest.createChildElement("ninja");
    ninjaElem.setBool("oktojump", mOkToJump);
    ninjaElem.setBool("smoke", mSmoke);
    ninjaElem.setFloat("deathtime", mDeathTime);
    ninjaElem.setFloat("inairtime", mInAirTime);
    ninjaElem.setFloat("ongroundtime", mOnGroundTime);
    ninjaElem.setFloat("deathdir", mDeathDir);
    ninjaElem.setFloat("throwtime", mThrowTime);
    ninjaElem.setFloat("dirchangetime", mDirChangeTime);
    ninjaElem.setFloat("aimx", mAimX);
    ninjaElem.setFloat("aimy", mAimY);
    
    XMLElement controlsElem = dest.createChildElement("controls");
    mControls.writeXML(controlsElem);
    
    XMLElement prevControlsElem = dest.createChildElement("prevcontrols");
    mControls.writeXML(prevControlsElem);
}

void Ninja::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read GameObject properties
    GameObject::loadXML(source, cache);
    
    // Read Ninja properties
    XMLElement ninjaElem = source.getChildElement("ninja");
    mOkToJump = ninjaElem.getBool("oktojump");
    mSmoke = ninjaElem.getBool("smoke");
    mDeathTime = ninjaElem.getFloat("deathtime");
    mInAirTime = ninjaElem.getFloat("inairtime");
    mOnGroundTime = ninjaElem.getFloat("ongroundtime");
    mDeathDir = ninjaElem.getFloat("deathdir");
    mThrowTime = ninjaElem.getFloat("throwtime");
    mDirChangeTime = ninjaElem.getFloat("dirchangetime");
    mAimX = ninjaElem.getFloat("aimx");
    mAimY = ninjaElem.getFloat("aimy");
    
    XMLElement controlsElem = source.getChildElement("controls");
    mControls.readXML(controlsElem);
    
    XMLElement prevControlsElem = source.getChildElement("prevcontrols");
    mPrevControls.readXML(prevControlsElem);
}

bool Ninja::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    bool prevBits = GameObject::writeNetUpdate(dest, destRevision, baseRevision, info);
    
    // Note: only the death animation direction is replicated from server to client
    unsigned char bits = 0;
    checkBool(mOkToJump, baseRevision, bits, 1);
    checkBool(mSmoke, baseRevision, bits, 1);
    checkFloat(mDeathTime, baseRevision, bits, 2);
    checkFloat(mInAirTime, baseRevision, bits, 4);
    checkFloat(mOnGroundTime, baseRevision, bits, 8);
    checkFloat(mDeathDir, baseRevision, bits, 16);
    checkFloat(mThrowTime, baseRevision, bits, 32);
    
    dest.writeUByte(bits);
    writeBoolDelta(mOkToJump, dest, destRevision, bits & 1);
    writeBoolDelta(mSmoke, dest, destRevision, bits & 1);
    writeFloatDelta(mDeathTime, dest, destRevision, bits & 2);
    writeFloatDelta(mInAirTime, dest, destRevision, bits & 4);
    writeFloatDelta(mOnGroundTime, dest, destRevision, bits & 8);
    writeFloatDelta(mDeathDir, dest, destRevision, bits & 16);
    writeFloatDelta(mThrowTime, dest, destRevision, bits & 32);
    
    return prevBits || (bits != 0);
}

void Ninja::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    GameObject::readNetUpdate(source, cache, info);
    
    unsigned char bits = source.readUByte();
    readBoolDelta(mOkToJump, source, bits & 1);
    readBoolDelta(mSmoke, source, bits & 1);
    readFloatDelta(mDeathTime, source, bits & 2);
    readFloatDelta(mInAirTime, source, bits & 4);
    readFloatDelta(mOnGroundTime, source, bits & 8);
    readFloatDelta(mDeathDir, source, bits & 16);
    readFloatDelta(mThrowTime, source, bits & 32);
}

void Ninja::onCreate(const Vector3& position, const Quaternion& orientation)
{
    // Note: in multiplayer the onCreate() function is only run on the server
    ResourceCache* cache = getResourceCache();
    
    // Create model
    AnimatedModel* model = createComponent<AnimatedModel>();
    model->setModel(cache->getResource<Model>("Models/Ninja.mdl"));
    model->setMaterial(cache->getResource<Material>("Materials/Ninja.xml"));
    model->setDrawDistance(tRenderDistance);
    model->setCastShadows(true);
    
    // Create animation controller
    AnimationController* controller = createComponent<AnimationController>();
    controller->setAnimatedModel(model);
    
    // Create body
    RigidBody* body = createComponent<RigidBody>();
    body->setPosition(position);
    body->setRotation(orientation);
    body->setMode(PHYS_DYNAMIC);
    body->setMass(tMass);
    body->setFriction(tFriction);
    body->setCollisionShape(cache->getResource<CollisionShape>("Physics/Ninja.xml"));
    body->setCollisionGroup(1);
    body->setCollisionMask(3);
    body->setAngularMaxVelocity(0.0f);
    body->addChild(model);
    model->setPosition(Vector3(0.0f, -90.0f, 0.0f));
    
    // Set initial aim
    mAimX = orientation.getYaw();
    
    // Enable owner prediction on the entity, sync the ninja component to the owner only
    mEntity->setNetFlags(NET_SYNCTOALL | NET_OWNERPREDICT);
    setNetFlags(NET_SYNCTOOWNER | NET_OWNERPREDICT);
    model->setNetFlags(NET_SYNCTOALL | NET_OWNERPREDICT);
    controller->setNetFlags(NET_SYNCTOOWNER | NET_OWNERPREDICT);
    body->setNetFlags(NET_SYNCTOALL | NET_OWNERPREDICT);
    
    // Enable local animation for the player's predicted ninja
    model->setLocalAnimation(true);
}

bool Ninja::onUpdate(float time)
{
    // Do not update if being a non-predicted proxy. In this case the check is redundant, as this component should
    // only be replicated to the owning player, and AI ninjas (having no owner) should not be replicated to anyone
    if ((isProxy()) && (!checkPrediction()))
        return true;
    
    // Check health
    if (mHealth <= 0) return onDeathUpdate(time);
    
    RigidBody* body = getBody();
    AnimationController* controller = mEntity->getComponent<AnimationController>();
    if ((!body) || (!controller))
        return true;
    
    if (mSide == SIDE_ENEMY)
        AIController::control(this, time);
    
    // Turning / horizontal aiming
    if (mAimX != mControls.mYaw)
    {
        body->setActive(true);
        mAimX = mControls.mYaw;
    }
    // Vertical aiming
    if (mAimY != mControls.mPitch)
    {
        body->setActive(true);
        mAimY = mControls.mPitch;
    }
    
    // Force orientation to horizontal aim
    Quaternion q = Quaternion::sIdentity;
    q = q * Quaternion(mAimX, Vector3::sUp);
    body->setRotation(q);
    
    // Movement ground/air
    Vector3 vel = body->getLinearVelocity();
    if (mOnGround)
    {
        mInAirTime = 0;
        mOnGroundTime += time;
    }
    else
    {
        mOnGroundTime = 0;
        mInAirTime += time;
    }
    
    if ((mInAirTime < 0.3f) && (!mIsSliding))
    { 
        bool sidemove = false;
        
        // Movement in four directions
        if (mControls.isDown(CTRL_UP|CTRL_DOWN|CTRL_LEFT|CTRL_RIGHT))
        {
            float animDir = 1.0f;
            Vector3 force(Vector3::sZero);
            if (mControls.isDown(CTRL_UP))
                force += q * Vector3::sForward;
            if (mControls.isDown(CTRL_DOWN))
            {
                animDir = -1.0f;
                force += q * Vector3::sBack;
            }
            if (mControls.isDown(CTRL_LEFT))
            {
                sidemove = true;
                force += q * Vector3::sLeft;
            }
            if (mControls.isDown(CTRL_RIGHT))
            {
                sidemove = true;
                force += q * Vector3::sRight;
            }
            // Normalize so that diagonal strafing isn't faster
            force.normalize();
            force *= tMoveForce;
            body->applyForce(force);
            
            // Walk or sidestep animation
            if (sidemove)
                controller->setAnimation("Models/Ninja_Stealth.ani", ANIM_MOVE, true, false, animDir * 2.2f, 1.0f, 0.2f, 0.0f, true);
            else
                controller->setAnimation("Models/Ninja_Walk.ani", ANIM_MOVE, true, false, animDir * 1.6f, 1.0f, 0.2f, 0.0f, true);
        }
        else
        {
            // Idle animation
            controller->setAnimation("Models/Ninja_Idle3.ani", ANIM_MOVE, true, false, 1.0f, 1.0f, 0.2f, 0.0f, true);
        }
        
        // Overall damping to cap maximum speed
        body->applyForce(Vector3(-tDampingForce * vel.mX, 0, -tDampingForce * vel.mZ));
        
        // Jumping
        if (mControls.isDown(CTRL_JUMP))
        {
            if ((mOkToJump) && (mInAirTime < 0.1f))
            {
                // Lift slightly off the ground for better animation
                body->setPosition(body->getPhysicsPosition() + 3.0f * Vector3::sUp);
                body->applyForce(Vector3(0, tJumpForce, 0));
                mInAirTime = 1.0f;
                controller->setAnimation("Models/Ninja_JumpNoHeight.ani", ANIM_MOVE, false, true, 1.0f, 1.0f, 0.0f, 0.0f, true);
                mOkToJump = false;
            }
        }
        else mOkToJump = true;
    }
    else
    {
        // Motion in the air
        // Note: when sliding a steep slope, control (or damping) isn't allowed!
        if ((mInAirTime > 0.3f) && (!mIsSliding))
        {
            if (mControls.isDown(CTRL_UP|CTRL_DOWN|CTRL_LEFT|CTRL_RIGHT))
            {
                Vector3 force = Vector3::sZero;
                if (mControls.isDown(CTRL_UP))
                    force += q * Vector3::sForward;
                if (mControls.isDown(CTRL_DOWN))
                    force += q * Vector3::sBack;
                if (mControls.isDown(CTRL_LEFT))
                    force += q * Vector3::sLeft;
                if (mControls.isDown(CTRL_RIGHT))
                    force += q * Vector3::sRight;
                // Normalize so that diagonal strafing isn't faster
                force.normalize();
                force *= tAirMoveForce;
                body->applyForce(force);
            }
        }
        
        // Falling/jumping/sliding animation
        if (mInAirTime > 0.01f)
            controller->setAnimation("Models/Ninja_JumpNoHeight.ani", ANIM_MOVE, false, false, 1.0f, 1.0f, 0.2f, 0.0f, true);
    }
    
    // Shooting
    if (mThrowTime >= 0)
        mThrowTime -= time;
    
    if ((mControls.isPressed(CTRL_FIRE, mPrevControls)) && (mThrowTime <= 0))
    {
        Vector3 projectileVel = getAim() * tThrowVelocity;
        
        controller->setAnimation("Models/Ninja_Attack1.ani", ANIM_ATTACK, false, true, 1.0f, 0.75f, 0.0f, 0.0f, false);
        controller->setFade("Models/Ninja_Attack1.ani", 0.0f, 0.5f);
        controller->setPriority("Models/Ninja_Attack1.ani", 1);
        
        // Do not spawn object for clientside prediction, only animate for now
        if (!isProxy())
        {
            SnowBall* obj = spawnObject<SnowBall>("Snowball");
            obj->create(getBody()->getPhysicsPosition() + time * vel + q * tThrowPosition, getAim());
            obj->setSide(mSide);
            obj->setOrigin(getEntity()->getID());
            obj->getBody()->setLinearVelocity(projectileVel);
            
            //! \todo the throw sound should be instant, and therefore predicted on client
            playSound("Sounds/NutThrow.wav");
        }
        
        mThrowTime = tThrowDelay;
    }
    
    mPrevControls = mControls;
    return true;
}

bool Ninja::onDeathUpdate(float time)
{
    RigidBody* body = getBody();
    AnimationController* controller = mEntity->getComponent<AnimationController>();
    if ((!body) || (!controller))
        return true;
    
    Vector3 vel = body->getLinearVelocity();
    
    // Overall damping to cap maximum speed
    body->applyForce(Vector3(-tDampingForce * vel.mX, 0, -tDampingForce * vel.mZ));
    
    if (canCollide())
        setCanCollide(false);
    
    // Pick death animation on first death update, do only on server so that results are consistent
    if (!isProxy())
    {
        if (mDeathDir == 0.0f)
        {
            if (random(1.0f) < 0.5f)
                mDeathDir = -1.0f;
            else
                mDeathDir = 1.0f;
            
            mDuration = tCorpseDuration;
            
            using namespace Die;
            
            VariantMap eventData;
            eventData[P_OBJECT] = (void*)this;
            sendEvent(EVENT_DIE, eventData);
            
            playSound("Sounds/SmallExplosion.wav");
        }
        
        mDeathTime += time;
        AnimatedModel* model = mEntity->getComponent<AnimatedModel>();
        
        // Move the model node to center the corpse mostly within the physics cylinder
        // (because of the animation)
        if (mDeathDir < 0.0f)
        {
            // Backward death
            controller->removeAnimations(ANIM_ATTACK, 0.1f);
            controller->setAnimation("Models/Ninja_Death1.ani", ANIM_MOVE, false, false, 0.5f, 1.0f, 0.2f, 0.0f, true);
            if ((mDeathTime >= 0.3f) && (mDeathTime < 0.8f))
                model->translate(Vector3(0, 0, 425 * time));
        }
        else if (mDeathDir > 0.0f)
        {
            // Forward death
            controller->removeAnimations(ANIM_ATTACK, 0.1f);
            controller->setAnimation("Models/Ninja_Death2.ani", ANIM_MOVE, false, false, 0.5f, 1.0f, 0.2f, 0.0f, true);
            if ((mDeathTime >= 0.4f) && (mDeathTime < 0.8f))
                model->translate(Vector3(0, 0, -425 * time));
        }
        
        // Create smokecloud just before vanishing
        if ((mDeathTime > (tCorpseDuration - 1.0f)) && (!mSmoke))
        {
            ResourceCache* cache = getResourceCache();
            
            GameObject* obj = spawnObject<GameObject>("Smoke");
            obj->setDuration(8);
            
            ParticleEmitter* emitter = obj->createComponent<ParticleEmitter>();
            emitter->loadParameters(cache->getResource<XMLFile>("Particle/Smoke.xml"), cache);
            emitter->setPosition(Vector3(0,-50,0));
            getBody()->addChild(emitter);
            mSmoke = true;
        }
    }
    
    mPrevControls = mControls;
    return true;
}

void Ninja::onRemove()
{
    // Do not create effects on client, because server will
    if (isProxy())
        return;
    
    RigidBody* body = getBody();
    if (!body)
        return;
    
    // Create a flash when disappearing
    ResourceCache* cache = getResourceCache();
    
    GameObject* obj = spawnObject<GameObject>("Flash");
    obj->setDuration(0.1f);
    
    Light* light = obj->createComponent<Light>();
    light->setLightType(LIGHT_POINT);
    light->setRange(500.0f);
    light->setColor(Color(2.0f, 2.0f, 2.0f));
    light->setCastShadows(true);
    light->setShadowResolution(0.25f);
    light->setRampTexture(cache->getResource<Texture2D>("Textures/RampWide.png"));
    light->setPosition(getBody()->getPhysicsPosition() + Vector3(0,-50,0));
    
    // Create a sound object for the explosion
    GameObject* obj2 = spawnObject<GameObject>("ExplosionSound");
    obj2->setDuration(2.0f);
    obj2->playSound("Sounds/BigExplosion.wav", light->getWorldPosition());
}

bool Ninja::onHeal(int amount)
{
    // Allow healing
    playSound("Sounds/Powerup.wav");
    return true;
}

Quaternion Ninja::getAim() const
{
    Quaternion q = Quaternion::sIdentity;
    q = q * Quaternion(mAimX, Vector3::sUp);
    q = q * Quaternion(mAimY, Vector3::sRight);
    return q;
}
