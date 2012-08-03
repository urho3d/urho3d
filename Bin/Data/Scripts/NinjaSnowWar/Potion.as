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
        SubscribeToEvent(node, "NodeCollision", "HandleNodeCollision");
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