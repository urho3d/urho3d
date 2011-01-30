#include "Scripts/Controls.as"

class GameObject : ScriptObject
{
    Controls controls;
    Controls prevControls;
    bool onGround;
    bool isSliding;
    float duration;

    GameObject()
    {
        onGround = false;
        isSliding = false;
        duration = 0;
    }

    void create(const Vector3&in position, const Quaternion&in rotation)
    {
    }

    void setControls(const Controls&in newControls)
    {
        controls = newControls;
    }

    void updateFixed(float timeStep)
    {
        // Disappear when duration expired
        if (duration > 0)
        {
            duration -= timeStep;
            if (duration <= 0)
                scene.removeEntity(entity);
        }
    }

    void handleEntityCollision(StringHash eventType, VariantMap& eventData)
    {
        Entity@ otherEntity = eventData["OtherEntity"].getEntity();
        // If the other entity does not have a ScriptInstance component, it's static world geometry
        if (!otherEntity.hasComponent("ScriptInstance"))
            handleWorldCollision(eventData);
        else
            handleObjectCollision(otherEntity, eventData);
    }

    void handleWorldCollision(VariantMap& eventData)
    {
        RigidBody@ body = entity.getComponent("RigidBody");

        VectorBuffer contacts = eventData["Contacts"].getBuffer();
        while (!contacts.isEof())
        {
            Vector3 contactPosition = contacts.readVector3();
            Vector3 contactNormal = contacts.readVector3();
            float contactDepth = contacts.readFloat();
            float contactVelocity = contacts.readFloat();

            // If contact is below center and mostly vertical, assume it's ground contact
            if (contactPosition.y < body.getPhysicsPosition().y)
            {
                float level = abs(contactNormal.y);
                if (level > 0.75)
                    onGround = true;
                else
                {
                    // If contact is somewhere inbetween vertical/horizontal, is sliding a slope
                    if (level > 0.1)
                        isSliding = true;
                }
            }
        }

        // Ground contact has priority over sliding contact
        if (onGround == true)
            isSliding = false;
    }
    
    void handleObjectCollision(Entity@ otherEntity, VariantMap& eventData)
    {
    }

    void resetWorldCollision()
    {
        RigidBody@ body = entity.getComponent("RigidBody");
        if (body.isActive())
        {
            onGround = false;
            isSliding = false;
        }
        else
        {
            // If body is not active, assume it rests on the ground
            onGround = true;
            isSliding = false;
        }
    }

    Entity@ spawnObject(const string&in className, const Vector3&in position, const Quaternion&in rotation)
    {
        Entity@ newEntity = scene.createEntity();

        // Create the ScriptInstance with specified class
        ScriptInstance@ instance = newEntity.createComponent("ScriptInstance");
        instance.setScriptClass(cache.getResource("ScriptFile", "Scripts/NinjaSnowWar.as"), className);
        GameObject@ object = cast<GameObject>(instance.getScriptObject());
        if (@object != null)
            object.create(position, rotation);

        return newEntity;
    }

    Entity@ spawnParticleEffect(const string&in effectName, float duration, const Vector3&in position, const Quaternion&in rotation)
    {
        Entity@ newEntity = scene.createEntity();
        
        // Create the particle emitter
        ParticleEmitter@ emitter = newEntity.createComponent("ParticleEmitter");
        emitter.loadParameters(cache.getResource("XMLFile", effectName));
        emitter.setPosition(position);
        emitter.setRotation(rotation);

        // Create a GameObject for managing the effect lifetime
        ScriptInstance@ instance = newEntity.createComponent("ScriptInstance");
        instance.setScriptClass(cache.getResource("ScriptFile", "Scripts/NinjaSnowWar.as"), "GameObject");
        GameObject@ object = cast<GameObject>(instance.getScriptObject());
        if (@object != null)
            object.duration = duration;
        
        return newEntity;
    }

    void playSound(const string&in soundName)
    {
        RigidBody@ body = entity.getComponent("RigidBody");
        if (@body == null)
            return;
        PositionalChannel@ channel = entity.createComponent("PositionalChannel", entity.getUniqueComponentName());
        body.addChild(channel);
        channel.setAutoRemove(true);
        channel.setDistanceAttenuation(200, 5000, 1);
        Sound@ sound = cache.getResource("Sound", soundName);
        channel.play(sound, sound.getFrequency());
    }
}
