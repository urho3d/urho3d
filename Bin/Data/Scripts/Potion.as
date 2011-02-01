#include "Scripts/GameObject.as"

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

    void start()
    {
        subscribeToEvent("EntityCollision", "handleEntityCollision");
    }
    
    void create(const Vector3&in position, const Quaternion&in rotation)
    {
        // Create model
        StaticModel@ model = entity.createComponent("StaticModel");
        model.setModel(cache.getResource("Model", "Models/Potion.mdl"));
        model.setMaterial(cache.getResource("Material", "Materials/Potion.xml"));
        model.setDrawDistance(potionDrawDistance);
        model.setCastShadows(true);

        // Create body
        RigidBody@ body = entity.createComponent("RigidBody");
        body.setPosition(position);
        body.setRotation(rotation);
        body.setMode(PHYS_DYNAMIC);
        body.setMass(potionMass);
        body.setFriction(potionFriction);
        body.setCollisionShape(cache.getResource("CollisionShape", "Physics/Potion.xml"));
        body.setCollisionGroup(1);
        body.setCollisionMask(3);
        body.addChild(model);
    }
    
    void objectCollision(GameObject@ otherObject, VariantMap& eventData)
    {
        if (healAmount > 0)
        {
            if (otherObject.heal(healAmount))
            {
                // Note: this is called during a physics world callback. Can not remove the potion at this point,
                // but instead set it to remove itself during the next update
                healAmount = 0;
                duration = 0;
            }
        }
    }
}