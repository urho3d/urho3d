// Urho2D platformer example.
// This sample demonstrates:
//    - Creating an orthogonal 2D scene from tile map file
//    - Displaying the scene using the Renderer subsystem
//    - Handling keyboard to move a character and zoom 2D camera
//    - Generating physics shapes from the tmx file's objects
//    - Mixing physics and translations to move the character
//    - Using Box2D Contact listeners to handle the gameplay
//    - Displaying debug geometry for physics and tile map
// Note that this sample uses some functions from Sample2D utility class.

#include "Scripts/Utilities/Sample.as"
#include "Scripts/Utilities/2D/Sample2D.as"


void Start()
{
    // Set filename for load/save functions
    demoFilename = "Platformer2D";

    // Execute the common startup for samples
    SampleStart();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateUIContent("PLATFORMER 2D DEMO");

    // Hook up to the frame update events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create the Octree, DebugRenderer and PhysicsWorld2D components to the scene
    scene_.CreateComponent("Octree");
    scene_.CreateComponent("DebugRenderer");
    scene_.CreateComponent("PhysicsWorld2D");

    // Create camera
    cameraNode = Node();
    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.orthographic = true;
    camera.orthoSize = graphics.height * PIXEL_SIZE;
    camera.zoom = 1.8f * Min(graphics.width / 1280.0f, graphics.height / 800.0f); // Set zoom according to user's resolution to ensure full visibility (initial zoom (1.8) is set for full visibility at 1280x800 resolution)

    // Setup the viewport for displaying the scene
    renderer.viewports[0] = Viewport(scene_, camera);
    renderer.defaultZone.fogColor = Color(0.2f, 0.2f, 0.2f); // Set background color for the scene

    // Create tile map from tmx file
    Node@ tileMapNode = scene_.CreateChild("TileMap");
    TileMap2D@ tileMap = tileMapNode.CreateComponent("TileMap2D");
    tileMap.tmxFile = cache.GetResource("TmxFile2D", "Urho2D/Tilesets/Ortho.tmx");
    TileMapInfo2D@ info = tileMap.info;

    // Create Spriter Imp character (from sample 33_SpriterAnimation)
    CreateCharacter(info, true, 0.8f, Vector3(1.0f, 8.0f, 0.0f), 0.2f);

    // Generate physics collision shapes from the tmx file's objects located in "Physics" (top) layer
    TileMapLayer2D@ tileMapLayer = tileMap.GetLayer(tileMap.numLayers - 1);
    CreateCollisionShapesFromTMXObjects(tileMapNode, tileMapLayer, info);

    // Instantiate enemies and moving platforms at each placeholder of "MovingEntities" layer (placeholders are Poly Line objects defining a path from points)
    PopulateMovingEntities(tileMap.GetLayer(tileMap.numLayers - 2));

    // Instantiate coins to pick at each placeholder of "Coins" layer (in this sample, placeholders for coins are Rectangle objects)
    PopulateCoins(tileMap.GetLayer(tileMap.numLayers - 3));

    // Instantiate triggers (for ropes, ladders, lava, slopes...) at each placeholder of "Triggers" layer (in this sample, placeholders for triggers are Rectangle objects)
    TileMapLayer2D@ triggersLayer = tileMap.GetLayer(tileMap.numLayers - 4);

    // Instantiate triggers at each placeholder (Rectangle objects)
    PopulateTriggers(triggersLayer);

    // Create background
    CreateBackgroundSprite(info, 3.5, "Textures/HeightMap.png", true);

    // Check when scene is rendered
    SubscribeToEvent("EndRendering", "HandleSceneRendered");
}

void HandleSceneRendered()
{
    UnsubscribeFromEvent("EndRendering");
    // Save the scene so we can reload it later
    SaveScene(true);
    // Pause the scene as long as the UI is hiding it
    scene_.updateEnabled = false;
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");

    // Subscribe HandlePostUpdate() function for processing post update events
    SubscribeToEvent("PostUpdate", "HandlePostUpdate");

    // Subscribe to PostRenderUpdate to draw debug geometry
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");

    // Subscribe to Box2D contact listeners
    SubscribeToEvent("PhysicsBeginContact2D", "HandleCollisionBegin");
    SubscribeToEvent("PhysicsEndContact2D", "HandleCollisionEnd");

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent("SceneUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Zoom in/out
    if (cameraNode !is null)
        Zoom(cameraNode.GetComponent("Camera"));

    // Toggle debug geometry with 'Z' key
    if (input.keyPress[KEY_Z]) drawDebug = !drawDebug;

    // Check for loading / saving the scene
    if (input.keyPress[KEY_F5])
    {
        SaveScene(false);
    }
    if (input.keyPress[KEY_F7])
        ReloadScene(false);
}

void HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if (character2DNode is null || cameraNode is null)
        return;
    cameraNode.position = Vector3(character2DNode.position.x, character2DNode.position.y, -10.0f); // Camera tracks character
}

void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    if (drawDebug)
    {
        PhysicsWorld2D@ physicsWorld = scene_.GetComponent("PhysicsWorld2D");
        physicsWorld.DrawDebugGeometry();

        Node@ tileMapNode = scene_.GetChild("TileMap", true);
        TileMap2D@ map = tileMapNode.GetComponent("TileMap2D");
        map.DrawDebugGeometry(scene_.GetComponent("DebugRenderer"), false);
    }
}

void HandleCollisionBegin(StringHash eventType, VariantMap& eventData)
{
    // Get colliding node
    Node@ hitNode = eventData["NodeA"].GetPtr();
    if (hitNode.name == "Imp")
        hitNode = eventData["NodeB"].GetPtr();
    String nodeName = hitNode.name;
    Character2D@ character = cast<Character2D>(character2DNode.scriptObject);

    // Handle ropes and ladders climbing
    if (nodeName == "Climb")
    {
        if (character.isClimbing) // If transition between rope and top of rope (as we are using split triggers)
            character.climb2 = true;
        else
        {
            character.isClimbing = true;
            RigidBody2D@ body = character2DNode.GetComponent("RigidBody2D");
            body.gravityScale = 0.0f; // Override gravity so that the character doesn't fall
            // Clear forces so that the character stops (should be performed by setting linear velocity to zero, but currently doesn't work)
            body.linearVelocity = Vector2(0.0f, 0.0f);
            body.awake = false;
            body.awake = true;
        }
    }

    if (nodeName == "CanJump")
        character.aboveClimbable = true;

    // Handle coins picking
    if (nodeName == "Coin")
    {
        hitNode.Remove();
        character.remainingCoins = character.remainingCoins - 1;
        if (character.remainingCoins == 0)
        {
            Text@ instructions = ui.root.GetChild("Instructions", true);
            instructions.text = "!!! Go to the Exit !!!";
        }
        Text@ coinsText = ui.root.GetChild("CoinsText", true);
        coinsText.text = character.remainingCoins; // Update coins UI counter
        PlaySound("Powerup.wav");
    }

    // Handle interactions with enemies
    if (nodeName == "Enemy" || nodeName == "Orc")
    {
        AnimatedSprite2D@ animatedSprite = character2DNode.GetComponent("AnimatedSprite2D");
        float deltaX = character2DNode.position.x - hitNode.position.x;

        // Orc killed if character is fighting in its direction when the contact occurs (flowers are not destroyable)
        if (nodeName == "Orc" && animatedSprite.animation == "attack" && (deltaX < 0 == animatedSprite.flipX))
        {
            cast<Mover>(hitNode.scriptObject).emitTime = 1;
            if (hitNode.GetChild("Emitter", true) is null)
            {
                hitNode.GetComponent("RigidBody2D").Remove(); // Remove Orc's body
                SpawnEffect(hitNode);
                PlaySound("BigExplosion.wav");
            }
        }
        // Player killed if not fighting in the direction of the Orc when the contact occurs, or when colliding with a flower
        else
        {
            if (character2DNode.GetChild("Emitter", true) is null)
            {
                character.wounded = true;
                if (nodeName == "Orc")
                    cast<Mover>(hitNode.scriptObject).fightTimer = 1;
                SpawnEffect(character2DNode);
                PlaySound("BigExplosion.wav");
            }
        }
    }

    // Handle exiting the level when all coins have been gathered
    if (nodeName == "Exit" && character.remainingCoins == 0)
    {
        // Update UI
        Text@ instructions = ui.root.GetChild("Instructions", true);
        instructions.text = "!!! WELL DONE !!!";
        instructions.position = IntVector2(0, 0);

        // Put the character outside of the scene and magnify him
        character2DNode.position = Vector3(-20.0f, 0.0f, 0.0f);
        character2DNode.SetScale(1.2f);
    }

    // Handle falling into lava
    if (nodeName == "Lava")
    {
        RigidBody2D@ body = character2DNode.GetComponent("RigidBody2D");
        body.ApplyLinearImpulse(Vector2(0.0f, 1.0f) * MOVE_SPEED, body.massCenter, true); // Violently project character out of lava
        if (character2DNode.GetChild("Emitter", true) is null)
        {
            character.wounded = true;
            SpawnEffect(character2DNode);
            PlaySound("BigExplosion.wav");
        }
    }

    // Handle climbing a slope
    if (nodeName == "Slope")
        character.onSlope = true;
}

void HandleCollisionEnd(StringHash eventType, VariantMap& eventData)
{
    // Get colliding node
    Node@ hitNode = eventData["NodeA"].GetPtr();
    if (hitNode.name == "Imp")
        hitNode = eventData["NodeB"].GetPtr();
    String nodeName = hitNode.name;
    Character2D@ character = cast<Character2D>(character2DNode.scriptObject);

    // Handle leaving a rope or ladder
    if (nodeName == "Climb")
    {
        if (character.climb2)
            character.climb2 = false;
        else
        {
            character.isClimbing = false;
            RigidBody2D@ body = character2DNode.GetComponent("RigidBody2D");
            body.gravityScale = 1.0f; // Restore gravity
        }
    }

    if (nodeName == "CanJump")
        character.aboveClimbable = false;

    // Handle leaving a slope
    if (nodeName == "Slope")
    {
        character.onSlope = false;
        // Clear forces (should be performed by setting linear velocity to zero, but currently doesn't work)
        RigidBody2D@ body = character2DNode.GetComponent("RigidBody2D");
        body.linearVelocity = Vector2(0.0f, 0.0f);
        body.awake = false;
        body.awake = true;
    }
}


// Character2D script object class
class Character2D : ScriptObject
{
    bool wounded = false;
    bool killed = false;
    float timer = 0.0f;
    int maxCoins = 0;
    int remainingCoins = 0;
    int remainingLifes = 3;
    bool isClimbing = false;
    bool climb2 = false; // Used only for ropes, as they are split into 2 shapes
    bool aboveClimbable = false;
    bool onSlope = false;

    void Save(Serializer& serializer)
    {
        isClimbing = false; // Overwrite before auto-deserialization
    }

    void Update(float timeStep)
    {
        if (character2DNode is null)
            return;

        // Handle wounded/killed states
        if (killed)
            return;

        if (wounded)
        {
            HandleWoundedState(timeStep);
            return;
        }

        // Set temporary variables
        RigidBody2D@ body = node.GetComponent("RigidBody2D");
        AnimatedSprite2D@ animatedSprite = node.GetComponent("AnimatedSprite2D");
        bool onGround = false;
        bool jump = false;

        // Collision detection (AABB query)
        Vector2 characterHalfSize = Vector2(0.16f, 0.16f);
        PhysicsWorld2D@ physicsWorld = scene_.GetComponent("PhysicsWorld2D");
        RigidBody2D@[]@ collidingBodies = physicsWorld.GetRigidBodies(Rect(node.worldPosition2D - characterHalfSize - Vector2(0.0f, 0.1f), node.worldPosition2D + characterHalfSize));

        if (collidingBodies.length > 1 && !isClimbing)
            onGround = true;

        // Set direction
        Vector2 moveDir = Vector2(0.0f, 0.0f); // Reset

        if (input.keyDown['A'] || input.keyDown[KEY_LEFT])
        {
            moveDir = moveDir + Vector2(-1.0f, 0.0f);
            animatedSprite.flipX = false; // Flip sprite (reset to default play on the X axis);
        }

        if (input.keyDown['D'] || input.keyDown[KEY_RIGHT])
        {
            moveDir = moveDir + Vector2(1.0f, 0.0f);
            animatedSprite.flipX = true; // Flip sprite (flip animation on the X axis)
        }

        // Jump
        if ((onGround || aboveClimbable) && (input.keyPress['W'] || input.keyPress[KEY_UP]))
            jump = true;

        // Climb
        if (isClimbing)
        {
            if (!aboveClimbable && (input.keyDown[KEY_UP] || input.keyDown[KEY_W]))
                moveDir = moveDir + Vector2(0.0f, 1.0f);

            if (input.keyDown[KEY_DOWN] || input.keyDown[KEY_S])
                moveDir = moveDir + Vector2(0.0f, -1.0f);
        }

        // Move
        if (!moveDir.Equals(Vector2(0.0f, 0.0f)) || jump)
        {
            if (onSlope)
                body.ApplyForceToCenter(moveDir * MOVE_SPEED / 2, true); // When climbing a slope, apply force (todo: replace by setting linear velocity to zero when will work)
            else
                node.Translate(Vector3(moveDir.x, moveDir.y, 0) * timeStep * 1.8f);
            if (jump)
                body.ApplyLinearImpulse(Vector2(0.0f, 0.17f) * MOVE_SPEED, body.massCenter, true);
        }

        // Animate
        if (input.keyDown[KEY_SPACE])
        {
            if (animatedSprite.animation != "attack")
            {
                animatedSprite.SetAnimation("attack", LM_FORCE_LOOPED);
                animatedSprite.speed = 1.5f;
            }
        }
        else if (!moveDir.Equals(Vector2(0.0f, 0.0f)))
        {
            if (animatedSprite.animation != "run")
                animatedSprite.SetAnimation("run");
        }
        else if (animatedSprite.animation != "idle")
        {
            animatedSprite.SetAnimation("idle");
        }
    }

    void HandleWoundedState(float timeStep)
    {
        RigidBody2D@ body = node.GetComponent("RigidBody2D");
        AnimatedSprite2D@ animatedSprite = node.GetComponent("AnimatedSprite2D");

        // Play "hit" animation in loop
        if (animatedSprite.animation != "hit")
            animatedSprite.SetAnimation("hit", LM_FORCE_LOOPED);

        // Update timer
        timer = timer + timeStep;

        if (timer > 2.0f)
        {
            // Reset timer
            timer = 0.0f;

            // Clear forces (should be performed by setting linear velocity to zero, but currently doesn't work)
            body.linearVelocity = Vector2(0.0f, 0.0f);
            body.awake = false;
            body.awake = true;

            // Remove particle emitter
            node.GetChild("Emitter", true).Remove();

            // Update lifes UI and counter
            remainingLifes = remainingLifes - 1;
            Text@ lifeText = ui.root.GetChild("LifeText", true);
            lifeText.text = remainingLifes; // Update lifes UI counter

            // Reset wounded state
            wounded = false;

            // Handle death
            if (remainingLifes == 0)
            {
                HandleDeath();
                return;
            }

            // Re-position the character to the nearest point
            if (node.position.x < 15.0f)
                node.position = Vector3(1.0f, 8.0f, 0.0f);
            else
                node.position = Vector3(18.8f, 9.2f, 0.0f);
        }
    }

    void HandleDeath()
    {
        RigidBody2D@ body = node.GetComponent("RigidBody2D");
        AnimatedSprite2D@ animatedSprite = node.GetComponent("AnimatedSprite2D");

        // Set state to 'killed'
        killed = true;

        // Update UI elements
        Text@ instructions = ui.root.GetChild("Instructions", true);
        instructions.text = "!!! GAME OVER !!!";
        ui.root.GetChild("ExitButton", true).visible = true;
        ui.root.GetChild("PlayButton", true).visible = true;

        // Show mouse cursor so that we can click
        input.mouseVisible = true;

        // Put character outside of the scene and magnify him
        node.position = Vector3(-20.0f, 0.0f, 0.0f);
        node.SetScale(1.2f);

        // Play death animation once
        if (animatedSprite.animation != "dead2")
            animatedSprite.SetAnimation("dead2");
    }
}