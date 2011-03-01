#include "Scripts/GameObject.as"

const float snowballMass = 10;
const float snowballFriction = 0.5;
const float snowballDampingForce = 20;
const float snowballMinHitSpeed = 100;
const float snowballDuration = 5;
const float snowballGroundHitDuration = 1;
const float snowballObjectHitDuration = 0;
const float snowballDrawDistance = 7500;
const int snowballDamage = 1;

class SnowBall : GameObject
{
    int hitDamage;

    SnowBall()
    {
        duration = snowballDuration;
        hitDamage = snowballDamage;
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
        if ((onGround) || (duration < snowballGroundHitDuration))
        {
            Vector3 vel = body.getLinearVelocity();
            body.applyForce(Vector3(-snowballDampingForce * vel.x, 0, -snowballDampingForce * vel.z));
        }

        // Disappear when duration expired
        if (duration >= 0)
        {
            duration -= timeStep;
            if (duration <= 0)
            {
                spawnParticleEffect(body.getPhysicsPosition(), "Particle/SnowExplosion.xml", 1);
                scene.removeEntity(entity);
            }
        }
    }
    
    void worldCollision(VariantMap& eventData)
    {
        GameObject::worldCollision(eventData);
        
        // If hit the ground, disappear after a short while
        if (duration > snowballGroundHitDuration)
            duration = snowballGroundHitDuration;
    }

    void objectCollision(GameObject@ otherObject, VariantMap& eventData)
    {
        if (hitDamage > 0)
        {
            RigidBody@ body = entity.getComponent("RigidBody");
            if ((body.getLinearVelocity().getLength() >= snowballMinHitSpeed))
            {
                if (side != otherObject.side)
                {
                    otherObject.damage(this, hitDamage);
                    // Create a temp entity for the hit sound
                    spawnSound(body.getPhysicsPosition(), "Sounds/PlayerFistHit.wav", 0.2);
                }

                hitDamage = 0;
            }
        }
        if (duration > snowballObjectHitDuration)
            duration = snowballObjectHitDuration;
    }
}
