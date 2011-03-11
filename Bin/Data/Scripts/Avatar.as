#include "Scripts/GameObject.as"

const int ANIM_MOVE = 1;

const float avatarMass = 80;
const float avatarFriction = 0.75;
const float avatarMoveForce = 4000;
const float avatarAirMoveForce = 250;
const float avatarDampingForce = 750;
const float avatarJumpForce = 50000;

class Avatar : GameObject
{
    Controls controls;
    Controls prevControls;
    bool okToJump;
    float inAirTime;
    float onGroundTime;
    float aimX;
    float aimY;

    Avatar()
    {
        health = maxHealth = 100;
        okToJump = false;
        onGround = false;
        isSliding = false;
        inAirTime = 1;
        onGroundTime = 0;
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
        model.setModel(cache.getResource("Model", "Models/Jack.mdl"));
        model.setMaterial(0, cache.getResource("Material", "Materials/Jack_Body.xml"));
        model.setMaterial(1, cache.getResource("Material", "Materials/Jack_Face.xml"));
        model.setCastShadows(true);
        model.setInvisibleLodFactor(3.0f);

        // Create animation controller
        AnimationController@ controller = entity.createComponent("AnimationController");
        controller.setAnimatedModel(model);

        // Create body
        RigidBody@ body = entity.createComponent("RigidBody");
        body.setPosition(position);
        body.setRotation(rotation);
        body.setMode(PHYS_DYNAMIC);
        body.setMass(avatarMass);
        body.setFriction(avatarFriction);
        body.setCollisionShape(cache.getResource("CollisionShape", "Physics/Avatar.xml"));
        body.setCollisionGroup(1);
        body.setCollisionMask(3);
        body.setAngularMaxVelocity(0);
        body.addChild(model);
        model.setPosition(Vector3(0, -1.0, 0));

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
                force *= avatarMoveForce;
                body.applyForce(force);
                
                // Walk animation
                controller.setAnimation("Models/Jack_Walk.ani", ANIM_MOVE, true, false, animDir * 0.3 * (Vector3(vel.x, 0, vel.z).getLength()), 1.0, 0.2, 0.0, true);
            }
            else
            {
                // Idle animation
                controller.removeAllAnimations(0.2);
            }

            // Overall damping to cap maximum speed
            body.applyForce(Vector3(-avatarDampingForce * vel.x, 0, -avatarDampingForce * vel.z));

            // Jumping
            if (controls.isDown(CTRL_JUMP))
            {
                if ((okToJump) && (inAirTime < 0.1f))
                {
                    // Lift slightly off the ground for better animation
                    body.setPosition(body.getPhysicsPosition() + Vector3(0, 0.05, 0));
                    body.applyForce(Vector3(0, avatarJumpForce, 0));
                    inAirTime = 1.0f;
                    controller.removeAllAnimations(0.2);
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
                    force *= avatarAirMoveForce;
                    body.applyForce(force);
                }
            }
            
            // Falling/jumping/sliding animation
            if (inAirTime > 0.01f)
                controller.removeAllAnimations(0.2);
        }

        prevControls = controls;
        
        resetWorldCollision();
    }
}