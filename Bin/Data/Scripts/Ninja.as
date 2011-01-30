#include "Scripts/GameObject.as"

const int ANIM_MOVE = 1;
const int ANIM_ATTACK = 2;

const float ninjaMass = 80;
const float ninjaFriction = 0.5;
const float ninjaMoveForce = 500000;
const float ninjaAirMoveForce = 25000;
const float ninjaDampingForce = 1000;
const float ninjaJumpForce = 9000000;
const Vector3 ninjaThrowVelocity(0, 425, 2000);
const Vector3 ninjaThrowPosition(0, 20, 100);
const float ninjaThrowDelay = 0.1;
const float ninjaDrawDistance = 15000;

class Ninja : GameObject
{
    bool okToJump;
    bool smoke;
    float inAirTime;
    float onGroundTime;
    float throwTime;
    float deathTime;
    float deathDir;
    float dirChangeTime;
    float aimX;
    float aimY;

    Ninja()
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
    }

    void start()
    {
        subscribeToEvent("EntityCollision", "handleEntityCollision");
    }

    void create(const Vector3&in position, const Quaternion&in rotation)
    {
        // Create model
        AnimatedModel@ model = entity.createComponent("AnimatedModel");
        model.setModel(cache.getResource("Model", "Models/Ninja.mdl"));
        model.setMaterial(cache.getResource("Material", "Materials/Ninja.xml"));
        model.setDrawDistance(ninjaDrawDistance);
        model.setCastShadows(true);

        // Create animation controller
        AnimationController@ controller = entity.createComponent("AnimationController");
        controller.setAnimatedModel(model);

        // Create body
        RigidBody@ body = entity.createComponent("RigidBody");
        body.setPosition(position);
        body.setRotation(rotation);
        body.setMode(PHYS_DYNAMIC);
        body.setMass(ninjaMass);
        body.setFriction(ninjaFriction);
        body.setCollisionShape(cache.getResource("CollisionShape", "Physics/Ninja.xml"));
        body.setCollisionGroup(1);
        body.setCollisionMask(3);
        body.setAngularMaxVelocity(0);
        body.addChild(model);
        model.setPosition(Vector3(0, -90, 0));

        aimX = rotation.getYaw();
    }

    void setControls(const Controls&in newControls)
    {
        controls = newControls;
    }

    Quaternion getAim()
    {
        Quaternion q;
        q = q * Quaternion(aimX, Vector3(0, 1, 0));
        q = q * Quaternion(aimY, Vector3(1, 0, 0));
        return q;
    }

    void updateFixed(float timeStep)
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
            onGroundTime += timeStep;
        }
        else
        {
            onGroundTime = 0;
            inAirTime += timeStep;
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
                force *= ninjaMoveForce;
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
            body.applyForce(Vector3(-ninjaDampingForce * vel.x, 0, -ninjaDampingForce * vel.z));

            // Jumping
            if (controls.isDown(CTRL_JUMP))
            {
                if ((okToJump) && (inAirTime < 0.1f))
                {
                    // Lift slightly off the ground for better animation
                    body.setPosition(body.getPhysicsPosition() + Vector3(0, 3, 0));
                    body.applyForce(Vector3(0, ninjaJumpForce, 0));
                    inAirTime = 1.0f;
                    controller.setAnimation("Models/Ninja_JumpNoHeight.ani", ANIM_MOVE, false, true, 1.0, 1.0, 0.0, 0.0, true);
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
                    force *= ninjaAirMoveForce;
                    body.applyForce(force);
                }
            }
            
            // Falling/jumping/sliding animation
            if (inAirTime > 0.01f)
                controller.setAnimation("Models/Ninja_JumpNoHeight.ani", ANIM_MOVE, false, false, 1.0, 1.0, 0.2, 0.0, true);
        }
        
        // Shooting
        if (throwTime >= 0)
            throwTime -= timeStep;
        
        if ((controls.isPressed(CTRL_FIRE, prevControls)) && (throwTime <= 0))
        {
            Vector3 projectileVel = getAim() * ninjaThrowVelocity;

            controller.setAnimation("Models/Ninja_Attack1.ani", ANIM_ATTACK, false, true, 1.0, 0.75, 0.0, 0.0, false);
            controller.setFade("Models/Ninja_Attack1.ani", 0.0, 0.5);
            controller.setPriority("Models/Ninja_Attack1.ani", 1);

            Entity@ snowball = spawnObject("SnowBall", body.getPhysicsPosition() + vel * timeStep + q * ninjaThrowPosition, getAim());
            RigidBody@ snowballBody = snowball.getComponent("RigidBody");
            snowballBody.setLinearVelocity(projectileVel);
            
            playSound("Sounds/NutThrow.wav");

            throwTime = ninjaThrowDelay;
        }
        
        prevControls = controls;
        
        resetWorldCollision();
    }
    

}