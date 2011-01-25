#include "Scripts/Controls.as"

const int ANIM_MOVE = 1;
const int ANIM_ATTACK = 2;

const float mass = 80;
const float friction = 0.5;
const float moveForce = 500000;
const float airMoveForce = 25000;
const float dampingForce = 1000;
const float jumpForce = 9000000;
const Vector3 throwVelocity(0, 425, 2000);
const Vector3 throwPosition(0, 20, 100);
const float throwDelay = 0.1;

class Ninja
{
    Controls controls;
    Controls prevControls;
    bool okToJump;
    bool smoke;
    bool onGround;
    bool isSliding;
    float inAirTime;
    float onGroundTime;
    float throwTime;
    float deathTime;
    float deathDir;
    float dirChangeTime;
    float aimX;
    float aimY;

    void start()
    {
        okToJump = false;
        smoke = false;
        onGround = false;
        isSliding = false;
        inAirTime = 1;
        onGroundTime = 0;
        throwTime = 0;
        deathTime = 0;
        deathDir = 0;
        dirChangeTime = 0;
        aimX = 0;
        aimY = 0;

        subscribeToEvent("EntityCollision", "handleEntityCollision");
    }

    void create(const Vector3&in pos, const Quaternion&in rot)
    {
        // Create model
        AnimatedModel@ model = entity.createComponent("AnimatedModel");
        model.setModel(cache.getResource("Model", "Models/Ninja.mdl"));
        model.setMaterial(cache.getResource("Material", "Materials/Ninja.xml"));
        model.setDrawDistance(15000);
        model.setCastShadows(true);

        // Create animation controller
        AnimationController@ controller = entity.createComponent("AnimationController");
        controller.setAnimatedModel(model);

        // Create body
        RigidBody@ body = entity.createComponent("RigidBody");
        body.setPosition(pos);
        body.setRotation(rot);
        body.setMode(PHYS_DYNAMIC);
        body.setMass(mass);
        body.setFriction(friction);
        body.setCollisionShape(cache.getResource("CollisionShape", "Physics/Ninja.xml"));
        body.setCollisionGroup(1);
        body.setCollisionMask(3);
        body.setAngularMaxVelocity(0);
        body.addChild(model);
        model.setPosition(Vector3(0, -90, 0));

        aimX = rot.getYaw();
    }

    void setControls(uint buttons, float yaw, float pitch)
    {
        controls.buttons = buttons;
        controls.yaw = yaw;
        controls.pitch = pitch;
    }

    Quaternion getAim()
    {
        Quaternion q;
        q = q * Quaternion(aimX, Vector3(0, 1, 0));
        q = q * Quaternion(aimY, Vector3(1, 0, 0));
        return q;
    }

    void updateFixed(float time)
    {
        RigidBody@ body = entity.getComponent("RigidBody");
        AnimationController@ controller = entity.getComponent("AnimationController");

        // Turning / horizontal aiming
        if (aimX != controls.yaw)
        {
            body.setActive(true);
            aimX = controls.yaw;
        }
        // Vertical aiming
        if (aimY != controls.pitch)
        {
            body.setActive(true);
            aimY = controls.pitch;
        }

        // Force orientation to horizontal aim
        Quaternion q;
        q = q * Quaternion(aimX, Vector3(0, 1, 0));
        body.setRotation(q);

        // Movement ground/air
        Vector3 vel = body.getLinearVelocity();
        if (onGround)
        {
            inAirTime = 0;
            onGroundTime += time;
        }
        else
        {
            onGroundTime = 0;
            inAirTime += time;
        }

        if ((inAirTime < 0.3f) && (!isSliding))
        {
            bool sidemove = false;

            // Movement in four directions
            if (controls.isDown(CTRL_UP|CTRL_DOWN|CTRL_LEFT|CTRL_RIGHT))
            {
                float animDir = 1.0f;
                Vector3 force(0, 0, 0);
                if (controls.isDown(CTRL_UP))
                    force += q * Vector3(0, 0, 1);
                if (controls.isDown(CTRL_DOWN))
                {
                    animDir = -1.0f;
                    force += q * Vector3(0, 0, -1);
                }
                if (controls.isDown(CTRL_LEFT))
                {
                    sidemove = true;
                    force += q * Vector3(-1, 0, 0);
                }
                if (controls.isDown(CTRL_RIGHT))
                {
                    sidemove = true;
                    force += q * Vector3(1, 0, 0);
                }
                // Normalize so that diagonal strafing isn't faster
                force.normalize();
                force *= moveForce;
                body.applyForce(force);
                
                // Walk or sidestep animation
                if (sidemove)
                    controller.setAnimation("Models/Ninja_Stealth.ani", ANIM_MOVE, true, false, animDir * 2.2, 1.0, 0.2, 0.0, true);
                else
                    controller.setAnimation("Models/Ninja_Walk.ani", ANIM_MOVE, true, false, animDir * 1.6, 1.0, 0.2, 0.0, true);
            }
            else
            {
                // Idle animation
                controller.setAnimation("Models/Ninja_Idle3.ani", ANIM_MOVE, true, false, 1.0, 1.0, 0.2, 0.0, true);
            }

            // Overall damping to cap maximum speed
            body.applyForce(Vector3(-dampingForce * vel.x, 0, -dampingForce * vel.z));

            // Jumping
            if (controls.isDown(CTRL_JUMP))
            {
                if ((okToJump) && (inAirTime < 0.1f))
                {
                    // Lift slightly off the ground for better animation
                    body.setPosition(body.getPhysicsPosition() + Vector3(0, 3, 0));
                    body.applyForce(Vector3(0, jumpForce, 0));
                    inAirTime = 1.0f;
                    controller.setAnimation("Models/Ninja_JumpNoHeight.ani", ANIM_MOVE, false, true, 1.0f, 1.0f, 0.0f, 0.0f, true);
                    okToJump = false;
                }
            }
            else okToJump = true;
        }
        else
        {
            // Motion in the air
            // Note: when sliding a steep slope, control (or damping) isn't allowed!
            if ((inAirTime > 0.3f) && (!isSliding))
            {
                if (controls.isDown(CTRL_UP|CTRL_DOWN|CTRL_LEFT|CTRL_RIGHT))
                {
                    Vector3 force(0, 0, 0);
                    if (controls.isDown(CTRL_UP))
                        force += q * Vector3(0, 0, 1);
                    if (controls.isDown(CTRL_DOWN))
                        force += q * Vector3(0, 0, -1);
                    if (controls.isDown(CTRL_LEFT))
                        force += q * Vector3(-1, 0, 0);
                    if (controls.isDown(CTRL_RIGHT))
                        force += q * Vector3(1, 0, 0);
                    // Normalize so that diagonal strafing isn't faster
                    force.normalize();
                    force *= airMoveForce;
                    body.applyForce(force);
                }
            }
            
            // Falling/jumping/sliding animation
            if (inAirTime > 0.01f)
                controller.setAnimation("Models/Ninja_JumpNoHeight.ani", ANIM_MOVE, false, false, 1.0f, 1.0f, 0.2f, 0.0f, true);
        }
        
        // Shooting
        if (throwTime >= 0)
            throwTime -= time;
        
        if ((controls.isPressed(CTRL_FIRE, prevControls)) && (throwTime <= 0))
        {
            Vector3 projectileVel = getAim() * throwVelocity;
            
            controller.setAnimation("Models/Ninja_Attack1.ani", ANIM_ATTACK, false, true, 1.0f, 0.75f, 0.0f, 0.0f, false);
            controller.setFade("Models/Ninja_Attack1.ani", 0.0f, 0.5f);
            controller.setPriority("Models/Ninja_Attack1.ani", 1);
            
            /*
            // Do not spawn object for clientside prediction, only animate for now
            if (!isProxy())
            {
                SnowBall* obj = spawnObject<SnowBall>("Snowball");
                obj->create(getBody()->getPhysicsPosition() + time * vel + q * tThrowPosition, getAim());
                obj->setSide(mSide);
                obj->setOrigin(getEntity()->getID());
                obj->getBody()->setLinearVelocity(projectileVel);

                //! \todo the throw sound should be instant, and therefore predicted on client
                playSound("Sounds/NutThrow.wav");
            }
            */
            
            throwTime = throwDelay;
        }
        
        prevControls = controls;
        
        resetWorldCollision();
    }
    
    void handleEntityCollision(StringHash eventType, VariantMap& eventData)
    {
        Entity@ otherEntity = eventData["OtherEntity"].getEntity();
        // If the other entity does not have a ScriptInstance component, it's static world geometry
        if (!otherEntity.hasComponent("ScriptInstance"))
            handleWorldCollision(eventData);
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