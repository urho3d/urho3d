#include "Scripts/NinjaSnowWar/GameObject.as"


const int snowcrateHealth = 5;
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