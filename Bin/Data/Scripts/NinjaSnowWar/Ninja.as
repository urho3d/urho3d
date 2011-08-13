#include "Scripts/NinjaSnowWar/GameObject.as"
#include "Scripts/NinjaSnowWar/AIController.as"

const int LAYER_MOVE = 0;
const int LAYER_ATTACK = 1;

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

        // Setup interest management for networking
        NetworkPriority@ priority = node.CreateComponent("NetworkPriority", LOCAL);
        priority.basePriority = 110.0;
        priority.distanceFactor = 0.03;
        priority.minPriority = 20.0;

        // Create child node for the model. Copy the owner connection in case it is set
        Node@ modelNode = node.CreateChild();
        modelNode.owner = node.owner;
        modelNode.position = Vector3(0, -90, 0);

        // Create animated model
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
        // For multiplayer, replicate the health into the node user variables
        node.vars["Health"] = health;

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
                {
                    controller.PlayExclusive("Models/Ninja_Stealth.ani", LAYER_MOVE, true, 0.2);
                    controller.SetSpeed("Models/Ninja_Stealth.ani", animDir * 2.2);
                }
                else
                {
                    controller.PlayExclusive("Models/Ninja_Walk.ani", LAYER_MOVE, true, 0.2);
                    controller.SetSpeed("Models/Ninja_Walk.ani", animDir * 1.6);
                }
            }
            else
            {
                // Idle animation
                controller.PlayExclusive("Models/Ninja_Idle3.ani", LAYER_MOVE, true, 0.2);
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
                    controller.PlayExclusive("Models/Ninja_JumpNoHeight.ani", LAYER_MOVE, false,  0.1);
                    controller.SetTime("Models/Ninja_JumpNoHeight.ani", 0.0); // Always play from beginning
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
                controller.PlayExclusive("Models/Ninja_JumpNoHeight.ani", LAYER_MOVE, false, 0.1);
        }

        // Shooting
        if (throwTime >= 0)
            throwTime -= timeStep;

        // Start fading the attack animation after it has progressed past a certain point
        if (controller.GetTime("Models/Ninja_Attack1.ani") > 0.1)
            controller.Fade("Models/Ninja_Attack1.ani", 0.0, 0.5);

        if ((controls.IsPressed(CTRL_FIRE, prevControls)) && (throwTime <= 0))
        {
            Vector3 projectileVel = GetAim() * ninjaThrowVelocity;

            controller.Play("Models/Ninja_Attack1.ani", LAYER_ATTACK, false, 0.0);
            controller.SetTime("Models/Ninja_Attack1.ani", 0.0); // Always play from beginning

            Node@ snowball = SpawnObject(node.position + vel * timeStep + q * ninjaThrowPosition, GetAim(), "SnowBall");
            RigidBody@ snowballBody = snowball.GetComponent("RigidBody");
            snowballBody.linearVelocity = projectileVel;
            GameObject@ snowballObject = cast<GameObject>(snowball.scriptObject);
            snowballObject.side = side;
            snowballObject.creatorID = node.id;

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
            eventData["Receiver"] = lastDamageCreatorID;
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
            controller.StopLayer(LAYER_ATTACK, 0.1);
            controller.PlayExclusive("Models/Ninja_Death1.ani", LAYER_MOVE, false, 0.2);
            controller.SetSpeed("Models/Ninja_Death1.ani", 0.5);
            if ((deathTime >= 0.3) && (deathTime < 0.8))
                modelNode.Translate(Vector3(0, 0, 425 * timeStep));
        }
        else if (deathDir > 0)
        {
            // Forward death
            controller.StopLayer(LAYER_ATTACK, 0.1);
            controller.PlayExclusive("Models/Ninja_Death2.ani", LAYER_MOVE, false, 0.2);
            controller.SetSpeed("Models/Ninja_Death2.ani", 0.5);
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