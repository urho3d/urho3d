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
#include "Entity.h"
#include "Exception.h"
#include "GameConfig.h"
#include "GameEvents.h"
#include "Material.h"
#include "Model.h"
#include "ParticleEmitter.h"
#include "Potion.h"
#include "ResourceCache.h"
#include "RigidBody.h"
#include "SnowCrate.h"
#include "StaticModel.h"
#include "XMLFile.h"

#include "DebugNew.h"

static int tPoints;
static int tHealth;
static float tMass;
static float tFriction;
static float tRenderDistance;

void SnowCrate::setup()
{
    GameConfig::setSection("Objects/SnowCrate");
    
    tPoints = GameConfig::getInt("Points");
    tHealth = GameConfig::getInt("Health");
    tMass = GameConfig::getReal("Mass");
    tFriction = GameConfig::getReal("Friction");
    tRenderDistance = GameConfig::getReal("RenderDistance");
    
    GameConfig::setSection();
}

SnowCrate::SnowCrate()
{
    mMaxHealth = tHealth;
    mPoints = tPoints;
}

void SnowCrate::onCreate(const Vector3& position, const Quaternion& orientation)
{
    // Note: in multiplayer the onCreate() function is only run on the server
    ResourceCache* cache = getResourceCache();
    
    // Create model
    StaticModel* model = createComponent<StaticModel>();
    model->setModel(cache->getResource<Model>("Models/SnowCrate.mdl"));
    model->setMaterial(cache->getResource<Material>("Materials/SnowCrate.xml"));
    model->setDrawDistance(tRenderDistance);
    model->setCastShadows(true);
    
    // Create body
    RigidBody* body = createComponent<RigidBody>();
    body->setPosition(position);
    body->setRotation(orientation);
    body->setMode(PHYS_DYNAMIC);
    body->setMass(tMass);
    body->setFriction(tFriction);
    body->setCollisionShape(cache->getResource<CollisionShape>("Physics/SnowCrate.xml"));
    body->setCollisionGroup(1);
    body->setCollisionMask(3);
    body->addChild(model);
    
    // Enable transient prediction on the entity & rigid body
    mEntity->setNetFlags(NET_SYNCTOALL | NET_TRANSIENTPREDICT);
    body->setNetFlags(NET_SYNCTOALL | NET_TRANSIENTPREDICT);
}

bool SnowCrate::onUpdate(float time)
{
    // Destruct when damaged enough
    if (mHealth <= 0)
    {
        using namespace Die;
        
        VariantMap eventData;
        eventData[P_OBJECT] = (void*)this;
        sendEvent(EVENT_DIE, eventData);
        return false;
    }
    
    return true;
}

void SnowCrate::onRemove()
{
    ResourceCache* cache = getResourceCache();
    
    GameObject* obj = spawnObject<GameObject>("Explosion");
    obj->setDuration(2);
    ParticleEmitter* emitter = obj->createComponent<ParticleEmitter>();
    emitter->loadParameters(cache->getResource<XMLFile>("Particle/SnowExplosionBig.xml"), cache);
    emitter->setPosition(getBody()->getPhysicsPosition());
    emitter->setAnimationLodBias(100.0f);
    
    GameObject* obj2 = spawnObject<Potion>("Potion");
    obj2->create(getBody()->getPhysicsPosition());
}
