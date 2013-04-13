#include "Scripts/NinjaSnowWar/GameObject.as"

const float snowballMinHitSpeed = 1;
const float snowballDampingForce = 20;
const float snowballDuration = 5;
const float snowballGroundHitDuration = 1;
const float snowballObjectHitDuration = 0;
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
        SubscribeToEvent(node, "NodeCollision", "HandleNodeCollision");
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
                    // Create a temporary node for the hit sound
                    SpawnSound(node.position, "Sounds/PlayerFistHit.wav", 0.2);
                }

                hitDamage = 0;
            }
        }
        if (duration > snowballObjectHitDuration)
            duration = snowballObjectHitDuration;
    }
}
