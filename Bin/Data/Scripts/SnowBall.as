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

    void Start()
    {
        SubscribeToEvent("NodeCollision", "HandleNodeCollision");
    }

    void Create(const Vector3&in position, const Quaternion&in rotation)
    {
        node.position = position;
        node.rotation = rotation;

        // Setup interest management for networking
        node.priority = 100.0;
        node.priorityDistanceFactor = 0.04;
        node.minPriority = 25.0;

        // Create model
        StaticModel@ model = node.CreateComponent("StaticModel");
        model.model = cache.GetResource("Model", "Models/SnowBall.mdl");
        model.material = cache.GetResource("Material", "Materials/Snow.xml");
        model.drawDistance = snowballDrawDistance;
        model.castShadows = true;
    
        // Create collision shape
        CollisionShape@ shape = node.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(15, 15, 15), Vector3(), Quaternion());
        shape.collisionGroup = 1;
        shape.collisionMask = 3;
        shape.friction = snowballFriction;

        // Create body
        RigidBody@ body = node.CreateComponent("RigidBody");
        body.mass = snowballMass;
    }
    
    void FixedUpdate(float timeStep)
    {
        // Apply damping when rolling on the ground, or near disappearing
        RigidBody@ body = node.GetComponent("RigidBody");
        if ((onGround) || (duration < snowballGroundHitDuration))
        {
            Vector3 vel = body.linearVelocity;
            body.ApplyForce(Vector3(-snowballDampingForce * vel.x, 0, -snowballDampingForce * vel.z));
        }

        // Disappear when duration expired
        if (duration >= 0)
        {
            duration -= timeStep;
            if (duration <= 0)
            {
                SpawnParticleEffect(node.position, "Particle/SnowExplosion.xml", 1);
                node.Remove();
            }
        }
    }
    
    void WorldCollision(VariantMap& eventData)
    {
        GameObject::WorldCollision(eventData);
        
        // If hit the ground, disappear after a short while
        if (duration > snowballGroundHitDuration)
            duration = snowballGroundHitDuration;
    }

    void ObjectCollision(GameObject@ otherObject, VariantMap& eventData)
    {
        if (hitDamage > 0)
        {
            RigidBody@ body = node.GetComponent("RigidBody");
            if ((body.linearVelocity.length >= snowballMinHitSpeed))
            {
                if (side != otherObject.side)
                {
                    otherObject.Damage(this, hitDamage);
                    // Create a temp entity for the hit sound
                    SpawnSound(node.position, "Sounds/PlayerFistHit.wav", 0.2);
                }

                hitDamage = 0;
            }
        }
        if (duration > snowballObjectHitDuration)
            duration = snowballObjectHitDuration;
    }
}
