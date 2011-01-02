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
#include "CollisionShape.h"
#include "Deserializer.h"
#include "Entity.h"
#include "Exception.h"
#include "GameConfig.h"
#include "Material.h"
#include "Model.h"
#include "ParticleEmitter.h"
#include "ResourceCache.h"
#include "RigidBody.h"
#include "Serializer.h"
#include "SnowBall.h"
#include "StaticModel.h"
#include "XMLFile.h"

#include "DebugNew.h"

static int tDamage;
static float tMass;
static float tFriction;
static float tDampingForce;
static float tMinHitSpeed;
static float tRenderDistance;
static float tDuration;
static float tGroundHitDuration;
static float tObjectHitDuration;

void SnowBall::setup()
{
    GameConfig::setSection("Objects/SnowBall");

    tDamage = GameConfig::getInt("Damage");
    tMass = GameConfig::getReal("Mass");
    tFriction = GameConfig::getReal("Friction");
    tDampingForce = GameConfig::getReal("DampingForce");
    tMinHitSpeed = GameConfig::getReal("MinHitSpeed");
    tRenderDistance = GameConfig::getReal("RenderDistance");
    tDuration = GameConfig::getReal("Duration");
    tGroundHitDuration = GameConfig::getReal("GroundHitDuration");
    tObjectHitDuration = GameConfig::getReal("ObjectHitDuration");
    
    GameConfig::setSection("");
}

SnowBall::SnowBall()
{
    mDamage = tDamage;
    mDuration = tDuration;
}

void SnowBall::save(Serializer& dest)
{
    // Write GameObject properties
    GameObject::save(dest);
    
    // Write SnowBall properties
    dest.writeInt(mDamage);
}

void SnowBall::load(Deserializer& source, ResourceCache* cache)
{
    // Read GameObject properties
    GameObject::load(source, cache);
    
    // Read SnowBall properties
    mDamage = source.readInt();
}

void SnowBall::saveXML(XMLElement& dest)
{
    // Write GameObject properties
    GameObject::saveXML(dest);
    
    // Write SnowBall properties
    XMLElement snowBallElem = dest.createChildElement("snowball");
    snowBallElem.setInt("damage", mDamage);
}

void SnowBall::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read GameObject properties
    GameObject::loadXML(source, cache);
    
    // Read SnowBall properties
    XMLElement snowBallElem = source.getChildElement("snowball");
    mDamage = snowBallElem.getInt("damage");
}

void SnowBall::onCreate(const Vector3& position, const Quaternion& orientation)
{
    // Note: in multiplayer the onCreate() function is only run on the server
    ResourceCache* cache = getResourceCache();
    
    // Create model
    StaticModel* model = createComponent<StaticModel>();
    model->setModel(cache->getResource<Model>("Models/SnowBall.mdl"));
    model->setMaterial(cache->getResource<Material>("Materials/Snow.xml"));
    model->setDrawDistance(tRenderDistance);
    model->setCastShadows(true);
    
    // Create body
    RigidBody* body = createComponent<RigidBody>();
    body->setPosition(position);
    body->setRotation(orientation);
    body->setMode(PHYS_DYNAMIC);
    body->setMass(tMass);
    body->setFriction(tFriction);
    body->setCollisionShape(cache->getResource<CollisionShape>("Physics/SnowBall.xml"));
    body->setCollisionGroup(1);
    body->setCollisionMask(3);
    body->addChild(model);
}

bool SnowBall::onUpdate(float time)
{
    // Apply damping when rolling on the ground, or near disappearing
    RigidBody* body = getBody();
    if (body)
    {
        Vector3 vel = body->getLinearVelocity();
        if ((mOnGround) || (mDuration < tGroundHitDuration))
            body->applyForce(Vector3(-tDampingForce * vel.mX, 0, -tDampingForce * vel.mZ));
    }
    
    return true;
}

bool SnowBall::onDamage(int damage)
{
    // Two snowballs collide: no damage
    return false;
}

void SnowBall::onCollide(GameObject* other, VariantMap& collision)
{
    // If it's not a snowball we collided with, damage the other object,
    // but only once and vanish immediately
    if (other->getType() != getTypeStatic())
    {
        // We must have some speed, opponent must be on different side
        float minSpeedSquared = tMinHitSpeed * tMinHitSpeed;
        if (getBody()->getLinearVelocity().getLengthSquared() >= minSpeedSquared)
        {
            if ((mDamage) && (mSide != other->getSide()))
            {
                other->damage(mDamage, this);
                // Create a sound object for the hit
                GameObject* obj = spawnObject<GameObject>("HitSound");
                obj->setDuration(0.2f);
                obj->playSound("Sounds/PlayerFistHit.wav", getBody()->getPhysicsPosition());
            }
            if (mDuration > tObjectHitDuration)
                mDuration = tObjectHitDuration;
            mDamage = 0;
        }
    }
}

void SnowBall::onCollide(VariantMap& collision)
{
    // World collision: disappear after set time
    if (mDuration > tGroundHitDuration)
        mDuration = tGroundHitDuration;
}

void SnowBall::onRemove()
{
    ResourceCache* cache = getResourceCache();
    
    GameObject* obj = spawnObject<GameObject>("Explosion");
    obj->setDuration(1);
    
    ParticleEmitter* emitter = obj->createComponent<ParticleEmitter>();
    emitter->loadParameters(cache->getResource<XMLFile>("Particle/SnowExplosion.xml"), cache);
    emitter->setPosition(getBody()->getPhysicsPosition());
    emitter->setAnimationLodBias(100.0f);
}

