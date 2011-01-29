#include "Scripts/Controls.as"

class GameObject : ScriptObject
{
    Controls controls;
    Controls prevControls;
    float duration;
    bool onGround;
    bool isSliding;

    GameObject()
    {
        duration = 0.0;
        onGround = false;
        isSliding = false;
    }

    void create(const Vector3&in position, const Quaternion&in rotation)
    {
    }

    void setControls(const Controls&in newControls)
    {
        controls = newControls;
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
