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
        SubscribeToEvent(node, "NodeCollision", "HandleNodeCollision");
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