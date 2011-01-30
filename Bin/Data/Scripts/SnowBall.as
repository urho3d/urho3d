#include "Scripts/GameObject.as"

const float snowballMass = 10;
const float snowballFriction = 0.5;
const float snowballDampingForce = 20;
const float snowballMinHitSpeed = 100;
const float snowballDuration = 5;
const float snowballGroundHitDuration = 1;
const float snowballDrawDistance = 7500;

class SnowBall : GameObject
{
    SnowBall()
    {
        duration = snowballDuration;
    }

    void start()
    {
        subscribeToEvent("EntityCollision", "handleEntityCollision");
    }

    void create(const Vector3&in position, const Quaternion&in rotation)
    {
        // Create model
        StaticModel@ model = entity.createComponent("StaticModel");
        model.setModel(cache.getResource("Model", "Models/SnowBall.mdl"));
        model.setMaterial(cache.getResource("Material", "Materials/Snow.xml"));
        model.setDrawDistance(snowballDrawDistance);
        model.setCastShadows(true);
    
        // Create body
        RigidBody@ body = entity.createComponent("RigidBody");
        body.setPosition(position);
        body.setRotation(rotation);
        body.setMode(PHYS_DYNAMIC);
        body.setMass(snowballMass);
        body.setFriction(snowballFriction);
        body.setCollisionShape(cache.getResource("CollisionShape", "Physics/SnowBall.xml"));
        body.setCollisionGroup(1);
        body.setCollisionMask(3);
        body.addChild(model);
    }
    
    void updateFixed(float timeStep)
    {
        // Apply damping when rolling on the ground, or near disappearing
        RigidBody@ body = entity.getComponent("RigidBody");
        Vector3 vel = body.getLinearVelocity();
        if ((onGround) || (duration < snowballGroundHitDuration))
            body.applyForce(Vector3(-snowballDampingForce * vel.x, 0, -snowballDampingForce * vel.z));
            
        // Disappear when duration expired
        if (duration > 0)
        {
            duration -= timeStep;
            if (duration <= 0)
            {
                spawnParticleEffect("Particle/SnowExplosion.xml", 1, body.getPhysicsPosition(), Quaternion());
                scene.removeEntity(entity);
            }
        }
    }
    
    void handleWorldCollision(VariantMap& eventData)
    {
        GameObject::handleWorldCollision(eventData);
        
        // If hit the ground, disappear after a short while
        if (duration > snowballGroundHitDuration)
            duration = snowballGroundHitDuration;
    }
}
