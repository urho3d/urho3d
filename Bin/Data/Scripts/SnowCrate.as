#include "Scripts/GameObject.as"

const int snowcrateHealth = 5;
const float snowcrateMass = 200;
const float snowcrateFriction = 0.35;
const float snowcrateDrawDistance = 15000;

class SnowCrate : GameObject
{
    SnowCrate()
    {
        health = maxHealth = snowcrateHealth;
    }
    
    void start()
    {
        subscribeToEvent("EntityCollision", "handleEntityCollision");
    }
    
    void create(const Vector3&in position, const Quaternion&in rotation)
    {
        // Create model
        StaticModel@ model = entity.createComponent("StaticModel");
        model.setModel(cache.getResource("Model", "Models/SnowCrate.mdl"));
        model.setMaterial(cache.getResource("Material", "Materials/SnowCrate.xml"));
        model.setDrawDistance(snowcrateDrawDistance);
        model.setCastShadows(true);

        // Create body
        RigidBody@ body = entity.createComponent("RigidBody");
        body.setPosition(position);
        body.setRotation(rotation);
        body.setMode(PHYS_DYNAMIC);
        body.setMass(snowcrateMass);
        body.setFriction(snowcrateFriction);
        body.setCollisionShape(cache.getResource("CollisionShape", "Physics/SnowCrate.xml"));
        body.setCollisionGroup(2);
        body.setCollisionMask(3);
        body.addChild(model);
    }
    
    void updateFixed(float timeStep)
    {
        if (health <= 0)
        {
            RigidBody@ body = entity.getComponent("RigidBody");
            spawnParticleEffect(body.getPhysicsPosition(), "Particle/SnowExplosionBig.xml", 2);
            spawnObject(body.getPhysicsPosition(), Quaternion(), "Potion");
            scene.removeEntity(entity);
        }
    }
}