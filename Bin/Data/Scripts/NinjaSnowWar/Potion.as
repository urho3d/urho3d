#include "Scripts/NinjaSnowWar/GameObject.as"

const int potionHealAmount = 5;
const float potionMass = 10;
const float potionFriction = 0.5;
const float potionDrawDistance = 15000;

class Potion : GameObject
{
    int healAmount;

    Potion()
    {
        healAmount = potionHealAmount;
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
        NetworkPriority@ priority = node.CreateComponent("NetworkPriority", LOCAL);
        priority.basePriority = 100.0;
        priority.distanceFactor = 0.04;
        priority.minPriority = 15.0;

        // Create model
        StaticModel@ model = node.CreateComponent("StaticModel");
        model.model = cache.GetResource("Model", "Models/Potion.mdl");
        model.material = cache.GetResource("Material", "Materials/Potion.xml");
        model.drawDistance = potionDrawDistance;
        model.castShadows = true;

        // Create collision shape
        CollisionShape@ shape = node.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(20, 40, 20), Vector3(), Quaternion());
        shape.collisionGroup = 1;
        shape.collisionMask = 3;
        shape.friction = potionFriction;

        // Create body
        RigidBody@ body = node.CreateComponent("RigidBody");
        body.mass = potionMass;
    }
    
    void ObjectCollision(GameObject@ otherObject, VariantMap& eventData)
    {
        if (healAmount > 0)
        {
            if (otherObject.Heal(healAmount))
            {
                // Could also remove the potion directly, but this way it gets removed on next update
                healAmount = 0;
                duration = 0;
            }
        }
    }
}