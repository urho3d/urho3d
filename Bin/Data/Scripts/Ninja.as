#include "Scripts/GameObject.as"
#include "Scripts/AIController.as"

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
const float ninjaCorpseDuration = 3;
const int ninjaPoints = 250;

class Ninja : GameObject
{
    Controls controls;
    Controls prevControls;
    AIController@ controller;
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
        health = maxHealth = 2;
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

    void Start()
    {
        SubscribeToEvent("NodeCollision", "HandleNodeCollision");
    }

    void Create(const Vector3&in position, const Quaternion&in rotation)
    {
        node.position = position;
        node.rotation = rotation;

        // Create model
        Node@ modelNode = node.CreateChild();
        modelNode.position = Vector3(0, -90, 0);

        AnimatedModel@ model = modelNode.CreateComponent("AnimatedModel");
        model.model = cache.GetResource("Model", "Models/Ninja.mdl");
        model.material = cache.GetResource("Material", "Materials/Ninja.xml");
        model.drawDistance = ninjaDrawDistance;
        model.castShadows = true;
        model.invisibleLodFactor = 3.0f;

        // Create animation controller
        AnimationController@ controller = modelNode.CreateComponent("AnimationController");

        // Create collision shape
        CollisionShape@ shape = node.CreateComponent("CollisionShape");
        shape.SetCapsule(35, 110, Vector3(), Quaternion(90, 0, 0));
        shape.collisionGroup = 1;
        shape.collisionMask = 3;
        shape.friction = ninjaFriction;

        // Create body
        RigidBody@ body = node.CreateComponent("RigidBody");
        body.mass = ninjaMass;
        body.angularMaxVelocity = 0;

        aimX = rotation.yaw;
    }

    void SetControls(const Controls&in newControls)
    {
        controls = newControls;
    }

    Quaternion GetAim()
    {
        Quaternion q = Quaternion(aimX, Vector3(0, 1, 0));
        q = q * Quaternion(aimY, Vector3(1, 0, 0));
        return q;
    }

    void FixedUpdate(float timeStep)
    {
        if (health <= 0)
        {
            DeathUpdate(timeStep);
            return;
        }

        // AI control if controller exists
        if (controller !is null)
            controller.Control(this, node, timeStep);

        RigidBody@ body = node.GetComponent("RigidBody");
        AnimationController@ controller = node.children[0].GetComponent("AnimationController");

        // Turning / horizontal aiming
        if (aimX != controls.yaw)
        {
            aimX = controls.yaw;
            body.active = true;
        }
        // Vertical aiming
        if (aimY != controls.pitch)
            aimY = controls.pitch;

        // Force the physics rotation
        Quaternion q(aimX, Vector3(0, 1, 0));
        body.rotation = q;

        // Movement ground/air
        Vector3 vel = body.linearVelocity;
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
            if (controls.IsDown(CTRL_UP|CTRL_DOWN|CTRL_LEFT|CTRL_RIGHT))
            {
                float animDir = 1.0f;
                Vector3 force(0, 0, 0);
                if (controls.IsDown(CTRL_UP))
                    force += q * Vector3(0, 0, 1);
                if (controls.IsDown(CTRL_DOWN))
                {
                    animDir = -1.0f;
                    force += q * Vector3(0, 0, -1);
                }
                if (controls.IsDown(CTRL_LEFT))
                {
                    sidemove = true;
                    force += q * Vector3(-1, 0, 0);
                }
                if (controls.IsDown(CTRL_RIGHT))
                {
                    sidemove = true;
                    force += q * Vector3(1, 0, 0);
                }
                // Normalize so that diagonal strafing isn't faster
                force.Normalize();
                force *= ninjaMoveForce;
                body.ApplyForce(force);

                // Walk or sidestep animation
                if (sidemove)
                    controller.SetAnimation("Models/Ninja_Stealth.ani", ANIM_MOVE, true, false, animDir * 2.2, 1.0, 0.2, 0.0, true);
                else
                    controller.SetAnimation("Models/Ninja_Walk.ani", ANIM_MOVE, true, false, animDir * 1.6, 1.0, 0.2, 0.0, true);
            }
            else
            {
                // Idle animation
                controller.SetAnimation("Models/Ninja_Idle3.ani", ANIM_MOVE, true, false, 1.0, 1.0, 0.2, 0.0, true);
            }

            // Overall damping to cap maximum speed
            body.ApplyForce(Vector3(-ninjaDampingForce * vel.x, 0, -ninjaDampingForce * vel.z));

            // Jumping
            if (controls.IsDown(CTRL_JUMP))
            {
                if ((okToJump) && (inAirTime < 0.1f))
                {
                    // Lift slightly off the ground for better animation
                    node.position = node.position + Vector3(0, 3, 0);
                    body.ApplyForce(Vector3(0, ninjaJumpForce, 0));
                    inAirTime = 1.0f;
                    controller.SetAnimation("Models/Ninja_JumpNoHeight.ani", ANIM_MOVE, false, true, 1.0, 1.0, 0.0, 0.0, true);
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
                if (controls.IsDown(CTRL_UP|CTRL_DOWN|CTRL_LEFT|CTRL_RIGHT))
                {
                    Vector3 force(0, 0, 0);
                    if (controls.IsDown(CTRL_UP))
                        force += q * Vector3(0, 0, 1);
                    if (controls.IsDown(CTRL_DOWN))
                        force += q * Vector3(0, 0, -1);
                    if (controls.IsDown(CTRL_LEFT))
                        force += q * Vector3(-1, 0, 0);
                    if (controls.IsDown(CTRL_RIGHT))
                        force += q * Vector3(1, 0, 0);
                    // Normalize so that diagonal strafing isn't faster
                    force.Normalize();
                    force *= ninjaAirMoveForce;
                    body.ApplyForce(force);
                }
            }

            // Falling/jumping/sliding animation
            if (inAirTime > 0.01f)
                controller.SetAnimation("Models/Ninja_JumpNoHeight.ani", ANIM_MOVE, false, false, 1.0, 1.0, 0.2, 0.0, true);
        }

        // Shooting
        if (throwTime >= 0)
            throwTime -= timeStep;

        if ((controls.IsPressed(CTRL_FIRE, prevControls)) && (throwTime <= 0))
        {
            Vector3 projectileVel = GetAim() * ninjaThrowVelocity;

            controller.SetAnimation("Models/Ninja_Attack1.ani", ANIM_ATTACK, false, true, 1.0, 0.75, 0.0, 0.0, false);
            controller.SetFade("Models/Ninja_Attack1.ani", 0.0, 0.5);
            controller.priority["Models/Ninja_Attack1.ani"] = 1;

            Node@ snowball = SpawnObject(node.position + vel * timeStep + q * ninjaThrowPosition, GetAim(), "SnowBall");
            RigidBody@ snowballBody = snowball.GetComponent("RigidBody");
            snowballBody.linearVelocity = projectileVel;
            GameObject@ snowballObject = cast<GameObject>(snowball.scriptObject);
            snowballObject.side = side;

            PlaySound("Sounds/NutThrow.wav");

            throwTime = ninjaThrowDelay;
        }

        prevControls = controls;

        ResetWorldCollision();
    }

    void DeathUpdate(float timeStep)
    {
        RigidBody@ body = node.GetComponent("RigidBody");
        CollisionShape@ shape = node.GetComponent("CollisionShape");
        Node@ modelNode = node.children[0];
        AnimationController@ controller = modelNode.GetComponent("AnimationController");
        AnimatedModel@ model = modelNode.GetComponent("AnimatedModel");

        Vector3 vel = body.linearVelocity;

        // Overall damping to cap maximum speed
        body.ApplyForce(Vector3(-ninjaDampingForce * vel.x, 0, -ninjaDampingForce * vel.z));

        // Collide only to world geometry
        shape.collisionMask = 2;

        // Pick death animation on first death update
        if (deathDir == 0)
        {
            if (Random(1.0) < 0.5)
                deathDir = -1;
            else
                deathDir = 1;

            PlaySound("Sounds/SmallExplosion.wav");

            VariantMap eventData;
            eventData["Points"] = ninjaPoints;
            eventData["DamageSide"] = lastDamageSide;
            SendEvent("Points", eventData);
            SendEvent("Kill", eventData);
        }

        deathTime += timeStep;

        // Move the model node to center the corpse mostly within the physics cylinder
        // (because of the animation)
        if (deathDir < 0)
        {
            // Backward death
            controller.RemoveAnimations(ANIM_ATTACK, 0.1);
            controller.SetAnimation("Models/Ninja_Death1.ani", ANIM_MOVE, false, false, 0.5, 1.0, 0.2, 0.0, true);
            if ((deathTime >= 0.3) && (deathTime < 0.8))
                modelNode.Translate(Vector3(0, 0, 425 * timeStep));
        }
        else if (deathDir > 0)
        {
            // Forward death
            controller.RemoveAnimations(ANIM_ATTACK, 0.1);
            controller.SetAnimation("Models/Ninja_Death2.ani", ANIM_MOVE, false, false, 0.5, 1.0, 0.2, 0.0, true);
            if ((deathTime >= 0.4) && (deathTime < 0.8))
                modelNode.Translate(Vector3(0, 0, -425 * timeStep));
        }

        // Create smokecloud just before vanishing
        if ((deathTime > (ninjaCorpseDuration - 1)) && (!smoke))
        {
            SpawnParticleEffect(node.position + Vector3(0, -40, 0), "Particle/Smoke.xml", 8);
            smoke = true;
        }

        if (deathTime > ninjaCorpseDuration)
        {
            SpawnObject(node.position + Vector3(0, -50, 0), Quaternion(), "LightFlash");
            SpawnSound(node.position + Vector3(0, -50, 0), "Sounds/BigExplosion.wav", 2);
            node.Remove();
        }
    }

    bool Heal(int amount)
    {
        if (health == maxHealth)
            return false;

        health += amount;
        if (health > maxHealth)
            health = maxHealth;
        // If player, play the "powerup" sound
        if (side == SIDE_PLAYER)
            PlaySound("Sounds/Powerup.wav");
        return true;
    }
}