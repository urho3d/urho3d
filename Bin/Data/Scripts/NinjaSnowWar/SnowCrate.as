#include "Scripts/NinjaSnowWar/GameObject.as"

const int snowcrateHealth = 5;
const float snowcrateMass = 200;
const float snowcrateFriction = 0.35;
const float snowcrateDrawDistance = 15000;
const int snowcratePoints = 250;

class SnowCrate : GameObject
{
    SnowCrate()
    {
        health = maxHealth = snowcrateHealth;
    }
    
    void Start()
    {
        SubscribeToEvent("NodeCollision", "HandleNodeCollision");
        
        // Setup interest management for networking
        NetworkPriority@ priority = node.CreateComponent("NetworkPriority", LOCAL);
        priority.basePriority = 100.0;
        priority.distanceFactor = 0.04;
        priority.minPriority = 15.0;

        // Create model
        StaticModel@ model = node.CreateComponent("StaticModel");
        model.model = cache.GetResource("Model", "Models/SnowCrate.mdl");
        model.material = cache.GetResource("Material", "Materials/SnowCrate.xml");
        model.drawDistance = snowcrateDrawDistance;
        model.castShadows = true;

        // Create collision shape
        CollisionShape@ shape = node.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(80, 80, 80));
        shape.collisionLayer = 2;
        shape.collisionMask = 3;
        shape.friction = snowcrateFriction;

        // Create body
        RigidBody@ body = node.CreateComponent("RigidBody");
        body.mass = snowcrateMass;
    }
    
    void FixedUpdate(float timeStep)
    {
        if (health <= 0)
        {
            SpawnParticleEffect(node.position, "Particle/SnowExplosionBig.xml", 2);
            SpawnObject(node.position, Quaternion(), "Potion");

            VariantMap eventData;
            eventData["Points"] = snowcratePoints;
            eventData["Receiver"] = lastDamageCreatorID;
            eventData["DamageSide"] = lastDamageSide;
            SendEvent("Points", eventData);
        
            node.Remove();
        }
    }
}