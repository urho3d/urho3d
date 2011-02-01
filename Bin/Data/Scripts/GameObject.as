const int CTRL_UP = 1;
const int CTRL_DOWN = 2;
const int CTRL_LEFT = 4;
const int CTRL_RIGHT = 8;
const int CTRL_FIRE = 16;
const int CTRL_JUMP = 32;
const int CTRL_ALL = 63;

const int SIDE_NEUTRAL = 0;
const int SIDE_PLAYER = 1;
const int SIDE_ENEMY = 2;

class GameObject : ScriptObject
{
    bool onGround;
    bool isSliding;
    float duration;
    int health;
    int maxHealth;
    int side;
    int lastDamageSide;

    GameObject()
    {
        onGround = false;
        isSliding = false;
        duration = -1; // Infinite
        health = 0;
        maxHealth = 0;
        side = SIDE_NEUTRAL;
        lastDamageSide = SIDE_NEUTRAL;
    }

    void create(const Vector3&in position, const Quaternion&in rotation)
    {
    }

    void updateFixed(float timeStep)
    {
        // Disappear when duration expired
        if (duration >= 0)
        {
            duration -= timeStep;
            if (duration <= 0)
                scene.removeEntity(entity);
        }
    }

    bool damage(GameObject@ origin, int amount)
    {
        if ((origin.side == side) || (health == 0))
            return false;

        lastDamageSide = origin.side;
        health -= amount;
        if (health < 0)
            health = 0;
        return true;
    }

    bool heal(int amount)
    {
        // By default do not heal
        return false;
    }

    void playSound(const string&in soundName)
    {
        RigidBody@ body = entity.getComponent("RigidBody");
        if (@body == null)
            return;

        // Create the sound channel
        PositionalChannel@ channel = entity.createComponent("PositionalChannel", entity.getUniqueComponentName());
        body.addChild(channel);
        channel.setAutoRemove(true);
        channel.setDistanceAttenuation(200, 5000, 1);
        Sound@ sound = cache.getResource("Sound", soundName);
        channel.play(sound, sound.getFrequency());
    }

    Entity@ spawnObject(const Vector3&in position, const Quaternion&in rotation, const string&in className)
    {
        Entity@ newEntity = scene.createEntity();

        // Create the script object with specified class
        GameObject@ object = cast<GameObject>(newEntity.createScriptObject("Scripts/NinjaSnowWar.as", className));
        if (@object != null)
            object.create(position, rotation);

        return newEntity;
    }

    Entity@ spawnParticleEffect(const Vector3&in position, const string&in effectName, float duration)
    {
        Entity@ newEntity = scene.createEntity();

        // Create the particle emitter
        ParticleEmitter@ emitter = newEntity.createComponent("ParticleEmitter");
        emitter.loadParameters(cache.getResource("XMLFile", effectName));
        emitter.setPosition(position);

        // Create a GameObject for managing the effect lifetime
        GameObject@ object = cast<GameObject>(newEntity.createScriptObject("Scripts/NinjaSnowWar.as", "GameObject"));
        if (@object != null)
            object.duration = duration;

        return newEntity;
    }

    Entity@ spawnSound(const Vector3&in position, const string&in soundName, float duration)
    {
        Entity@ newEntity = scene.createEntity();

        // Create the sound channel
        PositionalChannel@ channel = newEntity.createComponent("PositionalChannel");
        channel.setPosition(position);
        channel.setAutoRemove(true);
        channel.setDistanceAttenuation(200, 5000, 1);
        Sound@ sound = cache.getResource("Sound", soundName);
        channel.play(sound, sound.getFrequency());

        // Create a GameObject for managing the sound lifetime
        GameObject@ object = cast<GameObject>(newEntity.createScriptObject("Scripts/NinjaSnowWar.as", "GameObject"));
        if (@object != null)
            object.duration = duration;

        return newEntity;
    }

    void handleEntityCollision(StringHash eventType, VariantMap& eventData)
    {
        Entity@ otherEntity = eventData["OtherEntity"].getEntity();
        RigidBody@ otherBody = eventData["OtherBody"].getRigidBody();

        // If the other rigid body belongs to static geometry, perform world collision
        if (otherBody.getCollisionGroup() == 2)
            worldCollision(eventData);

        // If the other entity is scripted, perform object-to-object collision
        GameObject@ otherObject = cast<GameObject>(otherEntity.getScriptObject());
        if (@otherObject != null)
            objectCollision(otherObject, eventData);
    }

    void worldCollision(VariantMap& eventData)
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

    void objectCollision(GameObject@ otherObject, VariantMap& eventData)
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
}
