// Moving character example.
// This sample demonstrates:
//     - Controlling a humanoid character through physics
//     - Driving animations using the AnimationController component
//     - Manual control of a bone scene node
//     - Implementing 1st and 3rd person cameras, using raycasts to avoid the 3rd person camera clipping into scenery
//     - Saving and loading the variables of a script object
//     - Using touch inputs/gyroscope for iOS/Android (implemented through an external file)

#include "Scripts/Utilities/Sample.as"
#include "Scripts/Utilities/Touch.as"

const int CTRL_FORWARD = 1;
const int CTRL_BACK = 2;
const int CTRL_LEFT = 4;
const int CTRL_RIGHT = 8;
const int CTRL_JUMP = 16;

const float MOVE_FORCE = 0.8f;
const float INAIR_MOVE_FORCE = 0.02f;
const float BRAKE_FORCE = 0.2f;
const float JUMP_FORCE = 7.0f;
const float YAW_SENSITIVITY = 0.1f;
const float INAIR_THRESHOLD_TIME = 0.1f;
bool firstPerson = false; // First person camera flag

Node@ characterNode;

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create static scene content
    CreateScene();

    // Create the controllable character
    CreateCharacter();

    // Create the UI content
    CreateInstructions();

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_RELATIVE);

    // Subscribe to necessary events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create scene subsystem components
    scene_.CreateComponent("Octree");
    scene_.CreateComponent("PhysicsWorld");

    // Create camera and define viewport. Camera does not necessarily have to belong to the scene
    cameraNode = Node();
    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.farClip = 300.0f;
    renderer.viewports[0] = Viewport(scene_, camera);

    // Create a Zone component for ambient lighting & fog control
    Node@ zoneNode = scene_.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000.0f, 1000.0f);
    zone.ambientColor = Color(0.15f, 0.15f, 0.15f);
    zone.fogColor = Color(0.5f, 0.5f, 0.7f);
    zone.fogStart = 100.0f;
    zone.fogEnd = 300.0f;

    // Create a directional light to the world. Enable cascaded shadows on it
    Node@ lightNode = scene_.CreateChild("DirectionalLight");
    lightNode.direction = Vector3(0.6f, -1.0f, 0.8f);
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_DIRECTIONAL;
    light.castShadows = true;
    light.shadowBias = BiasParameters(0.00025f, 0.5f);
    // Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light.shadowCascade = CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f);

    // Create the floor object
    Node@ floorNode = scene_.CreateChild("Floor");
    floorNode.position = Vector3(0.0f, -0.5f, 0.0f);
    floorNode.scale = Vector3(200.0f, 1.0f, 200.0f);
    StaticModel@ object = floorNode.CreateComponent("StaticModel");
    object.model = cache.GetResource("Model", "Models/Box.mdl");
    object.material = cache.GetResource("Material", "Materials/Stone.xml");

    RigidBody@ body = floorNode.CreateComponent("RigidBody");
    // Use collision layer bit 2 to mark world scenery. This is what we will raycast against to prevent camera from going
    // inside geometry
    body.collisionLayer = 2;
    CollisionShape@ shape = floorNode.CreateComponent("CollisionShape");
    shape.SetBox(Vector3(1.0f, 1.0f, 1.0f));

    // Create mushrooms of varying sizes
    const uint NUM_MUSHROOMS = 60;
    for (uint i = 0; i < NUM_MUSHROOMS; ++i)
    {
        Node@ objectNode = scene_.CreateChild("Mushroom");
        objectNode.position = Vector3(Random(180.0f) - 90.0f, 0.0f, Random(180.0f) - 90.0f);
        objectNode.rotation = Quaternion(0.0f, Random(360.0f), 0.0f);
        objectNode.SetScale(2.0f + Random(5.0f));
        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Mushroom.mdl");
        object.material = cache.GetResource("Material", "Materials/Mushroom.xml");
        object.castShadows = true;

        RigidBody@ body = objectNode.CreateComponent("RigidBody");
        body.collisionLayer = 2;
        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetTriangleMesh(object.model, 0);
    }

    // Create movable boxes. Let them fall from the sky at first
    const uint NUM_BOXES = 100;
    for (uint i = 0; i < NUM_BOXES; ++i)
    {
        float scale = Random(2.0f) + 0.5f;

        Node@ objectNode = scene_.CreateChild("Box");
        objectNode.position = Vector3(Random(180.0f) - 90.0f, Random(10.0f) + 10.0f, Random(180.0f) - 90.0f);
        objectNode.rotation = Quaternion(Random(360.0f), Random(360.0f), Random(360.0f));
        objectNode.SetScale(scale);
        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Box.mdl");
        object.material = cache.GetResource("Material", "Materials/Stone.xml");
        object.castShadows = true;

        RigidBody@ body = objectNode.CreateComponent("RigidBody");
        body.collisionLayer = 2;
        // Bigger boxes will be heavier and harder to move
        body.mass = scale * 2.0f;
        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetBox(Vector3(1.0f, 1.0f, 1.0f));
    }
}

void CreateCharacter()
{
    characterNode = scene_.CreateChild("Jack");
    characterNode.position = Vector3(0.0f, 1.0f, 0.0f);

    // Create the rendering component + animation controller
    AnimatedModel@ object = characterNode.CreateComponent("AnimatedModel");
    object.model = cache.GetResource("Model", "Models/Jack.mdl");
    object.material = cache.GetResource("Material", "Materials/Jack.xml");
    object.castShadows = true;
    characterNode.CreateComponent("AnimationController");

    // Set the head bone for manual control
    object.skeleton.GetBone("Bip01_Head").animated = false;

    // Create rigidbody, and set non-zero mass so that the body becomes dynamic
    RigidBody@ body = characterNode.CreateComponent("RigidBody");
    body.collisionLayer = 1;
    body.mass = 1.0f;

    // Set zero angular factor so that physics doesn't turn the character on its own.
    // Instead we will control the character yaw manually
    body.angularFactor = Vector3(0.0f, 0.0f, 0.0f);

    // Set the rigidbody to signal collision also when in rest, so that we get ground collisions properly
    body.collisionEventMode = COLLISION_ALWAYS;

    // Set a capsule shape for collision
    CollisionShape@ shape = characterNode.CreateComponent("CollisionShape");
    shape.SetCapsule(0.7f, 1.8f, Vector3(0.0f, 0.9f, 0.0f));

    // Create the character logic object, which takes care of steering the rigidbody
    characterNode.CreateScriptObject(scriptFile, "Character");
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text =
        "Use WASD keys and mouse to move\n"
        "Space to jump, F to toggle 1st/3rd person\n"
        "F5 to save scene, F7 to load";
    instructionText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    instructionText.textAlignment = HA_CENTER;

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
}

void SubscribeToEvents()
{
    // Subscribe to Update event for setting the character controls before physics simulation
    SubscribeToEvent("Update", "HandleUpdate");

    // Subscribe to PostUpdate event for updating the camera position after physics simulation
    SubscribeToEvent("PostUpdate", "HandlePostUpdate");

    // Unsubscribe the SceneUpdate event from base class as the camera node is being controlled in HandlePostUpdate() in this sample
    UnsubscribeFromEvent("SceneUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    if (characterNode is null)
        return;

    Character@ character = cast<Character>(characterNode.scriptObject);
    if (character is null)
        return;

    // Clear previous controls
    character.controls.Set(CTRL_FORWARD | CTRL_BACK | CTRL_LEFT | CTRL_RIGHT | CTRL_JUMP, false);

    // Update controls using touch utility
    if (touchEnabled)
        UpdateTouches(character.controls);

    // Update controls using keys (desktop)
    if (ui.focusElement is null)
    {
        if (touchEnabled || !useGyroscope)
        {
            character.controls.Set(CTRL_FORWARD, input.keyDown['W']);
            character.controls.Set(CTRL_BACK, input.keyDown['S']);
            character.controls.Set(CTRL_LEFT, input.keyDown['A']);
            character.controls.Set(CTRL_RIGHT, input.keyDown['D']);
        }
        character.controls.Set(CTRL_JUMP, input.keyDown[KEY_SPACE]);

        // Add character yaw & pitch from the mouse motion or touch input
        if (touchEnabled)
        {
            for (uint i = 0; i < input.numTouches; ++i)
            {
                TouchState@ state = input.touches[i];
                if (state.touchedElement is null) // Touch on empty space
                {
                    Camera@ camera = cameraNode.GetComponent("Camera");
                    if (camera is null)
                        return;

                    character.controls.yaw += TOUCH_SENSITIVITY * camera.fov / graphics.height * state.delta.x;
                    character.controls.pitch += TOUCH_SENSITIVITY * camera.fov / graphics.height * state.delta.y;
                }
            }
        }
        else
        {
            character.controls.yaw += input.mouseMoveX * YAW_SENSITIVITY;
            character.controls.pitch += input.mouseMoveY * YAW_SENSITIVITY;
        }
        // Limit pitch
        character.controls.pitch = Clamp(character.controls.pitch, -80.0f, 80.0f);
        // Set rotation already here so that it's updated every rendering frame instead of every physics frame
        characterNode.rotation = Quaternion(character.controls.yaw, Vector3(0.0f, 1.0f, 0.0f));

        // Switch between 1st and 3rd person
        if (input.keyPress['F'])
            firstPerson = !firstPerson;

        // Turn on/off gyroscope on mobile platform
        if (input.keyPress['G'])
            useGyroscope = !useGyroscope;

        // Check for loading / saving the scene
        if (input.keyPress[KEY_F5])
        {
            File saveFile(fileSystem.programDir + "Data/Scenes/CharacterDemo.xml", FILE_WRITE);
            scene_.SaveXML(saveFile);
        }
        if (input.keyPress[KEY_F7])
        {
            File loadFile(fileSystem.programDir + "Data/Scenes/CharacterDemo.xml", FILE_READ);
            scene_.LoadXML(loadFile);
            // After loading we have to reacquire the character scene node, as it has been recreated
            // Simply find by name as there's only one of them
            characterNode = scene_.GetChild("Jack", true);
            if (characterNode is null)
                return;
        }
    }
}

void HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if (characterNode is null)
        return;

    Character@ character = cast<Character>(characterNode.scriptObject);
    if (character is null)
        return;

    // Get camera lookat dir from character yaw + pitch
    Quaternion rot = characterNode.rotation;
    Quaternion dir = rot * Quaternion(character.controls.pitch, Vector3(1.0f, 0.0f, 0.0f));

    // Turn head to camera pitch, but limit to avoid unnatural animation
    Node@ headNode = characterNode.GetChild("Bip01_Head", true);
    float limitPitch = Clamp(character.controls.pitch, -45.0f, 45.0f);
    Quaternion headDir = rot * Quaternion(limitPitch, Vector3(1.0f, 0.0f, 0.0f));
    // This could be expanded to look at an arbitrary target, now just look at a point in front
    Vector3 headWorldTarget = headNode.worldPosition + headDir * Vector3(0.0f, 0.0f, 1.0f);
    headNode.LookAt(headWorldTarget, Vector3(0.0f, 1.0f, 0.0f));
    // Correct head orientation because LookAt assumes Z = forward, but the bone has been authored differently (Y = forward)
    headNode.Rotate(Quaternion(0.0f, 90.0f, 90.0f));

    if (firstPerson)
    {
        // First person camera: position to the head bone + offset slightly forward & up
        cameraNode.position = headNode.worldPosition + rot * Vector3(0.0f, 0.15f, 0.2f);
        cameraNode.rotation = dir;
    }
    else
    {
        // Third person camera: position behind the character
        Vector3 aimPoint = characterNode.position + rot * Vector3(0.0f, 1.7f, 0.0f); // You can modify x Vector3 value to translate the fixed character position (indicative range[-2;2])

        // Collide camera ray with static physics objects (layer bitmask 2) to ensure we see the character properly
        Vector3 rayDir = dir * Vector3(0.0f, 0.0f, -1.0f); // For indoor scenes you can use dir * Vector3(0.0, 0.0, -0.5) to prevent camera from crossing the walls
        float rayDistance = cameraDistance;
        PhysicsRaycastResult result = scene_.physicsWorld.RaycastSingle(Ray(aimPoint, rayDir), rayDistance, 2);
        if (result.body !is null)
            rayDistance = Min(rayDistance, result.distance);
        rayDistance = Clamp(rayDistance, CAMERA_MIN_DIST, cameraDistance);

        cameraNode.position = aimPoint + rayDir * rayDistance;
        cameraNode.rotation = dir;
    }
}

// Character script object class
//
// Those public member variables that can be expressed with a Variant and do not begin with an underscore are automatically
// loaded / saved as attributes of the ScriptInstance component. We also have variables which can not be automatically saved
// (yaw and pitch inside the Controls object) so we write manual binary format load / save methods for them. These functions
// will be called by ScriptInstance when the script object is being loaded or saved.
class Character : ScriptObject
{
    // Character controls.
    Controls controls;
    // Grounded flag for movement.
    bool onGround = false;
    // Jump flag.
    bool okToJump = true;
    // In air timer. Due to possible physics inaccuracy, character can be off ground for max. 1/10 second and still be allowed to move.
    float inAirTimer = 0.0f;

    void Start()
    {
        SubscribeToEvent(node, "NodeCollision", "HandleNodeCollision");
    }

    void Load(Deserializer& deserializer)
    {
        controls.yaw = deserializer.ReadFloat();
        controls.pitch = deserializer.ReadFloat();
    }

    void Save(Serializer& serializer)
    {
        serializer.WriteFloat(controls.yaw);
        serializer.WriteFloat(controls.pitch);
    }

    void HandleNodeCollision(StringHash eventType, VariantMap& eventData)
    {
        VectorBuffer contacts = eventData["Contacts"].GetBuffer();

        while (!contacts.eof)
        {
            Vector3 contactPosition = contacts.ReadVector3();
            Vector3 contactNormal = contacts.ReadVector3();
            float contactDistance = contacts.ReadFloat();
            float contactImpulse = contacts.ReadFloat();

            // If contact is below node center and mostly vertical, assume it's a ground contact
            if (contactPosition.y < (node.position.y + 1.0f))
            {
                float level = Abs(contactNormal.y);
                if (level > 0.75)
                    onGround = true;
            }
        }
    }

    void FixedUpdate(float timeStep)
    {
        /// \todo Could cache the components for faster access instead of finding them each frame
        RigidBody@ body = node.GetComponent("RigidBody");
        AnimationController@ animCtrl = node.GetComponent("AnimationController");

        // Update the in air timer. Reset if grounded
        if (!onGround)
            inAirTimer += timeStep;
        else
            inAirTimer = 0.0f;
        // When character has been in air less than 1/10 second, it's still interpreted as being on ground
        bool softGrounded = inAirTimer < INAIR_THRESHOLD_TIME;

        // Update movement & animation
        Quaternion rot = node.rotation;
        Vector3 moveDir(0.0f, 0.0f, 0.0f);
        Vector3 velocity = body.linearVelocity;
        // Velocity on the XZ plane
        Vector3 planeVelocity(velocity.x, 0.0f, velocity.z);

        if (controls.IsDown(CTRL_FORWARD))
            moveDir += Vector3(0.0f, 0.0f, 1.0f);
        if (controls.IsDown(CTRL_BACK))
            moveDir += Vector3(0.0f, 0.0f, -1.0f);
        if (controls.IsDown(CTRL_LEFT))
            moveDir += Vector3(-1.0f, 0.0f, 0.0f);
        if (controls.IsDown(CTRL_RIGHT))
            moveDir += Vector3(1.0f, 0.0f, 0.0f);

        // Normalize move vector so that diagonal strafing is not faster
        if (moveDir.lengthSquared > 0.0f)
            moveDir.Normalize();

        // If in air, allow control, but slower than when on ground
        body.ApplyImpulse(rot * moveDir * (softGrounded ? MOVE_FORCE : INAIR_MOVE_FORCE));

        if (softGrounded)
        {
            // When on ground, apply a braking force to limit maximum ground velocity
            Vector3 brakeForce = -planeVelocity * BRAKE_FORCE;
            body.ApplyImpulse(brakeForce);

            // Jump. Must release jump control inbetween jumps
            if (controls.IsDown(CTRL_JUMP))
            {
                if (okToJump)
                {
                    body.ApplyImpulse(Vector3(0.0f, 1.0f, 0.0f) * JUMP_FORCE);
                    okToJump = false;
                }
            }
            else
                okToJump = true;
        }

        // Play walk animation if moving on ground, otherwise fade it out
        if (softGrounded && !moveDir.Equals(Vector3(0.0f, 0.0f, 0.0f)))
            animCtrl.PlayExclusive("Models/Jack_Walk.ani", 0, true, 0.2f);
        else
            animCtrl.Stop("Models/Jack_Walk.ani", 0.2f);
        // Set walk animation speed proportional to velocity
        animCtrl.SetSpeed("Models/Jack_Walk.ani", planeVelocity.length * 0.3f);

        // Reset grounded flag for next frame
        onGround = false;
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element\">" +
        "        <element type=\"Button\">" +
        "            <attribute name=\"Name\" value=\"Button3\" />" +
        "            <attribute name=\"Position\" value=\"-120 -120\" />" +
        "            <attribute name=\"Size\" value=\"96 96\" />" +
        "            <attribute name=\"Horiz Alignment\" value=\"Right\" />" +
        "            <attribute name=\"Vert Alignment\" value=\"Bottom\" />" +
        "            <attribute name=\"Texture\" value=\"Texture2D;Textures/TouchInput.png\" />" +
        "            <attribute name=\"Image Rect\" value=\"96 0 192 96\" />" +
        "            <attribute name=\"Hover Image Offset\" value=\"0 0\" />" +
        "            <attribute name=\"Pressed Image Offset\" value=\"0 0\" />" +
        "            <element type=\"Text\">" +
        "                <attribute name=\"Name\" value=\"Label\" />" +
        "                <attribute name=\"Horiz Alignment\" value=\"Center\" />" +
        "                <attribute name=\"Vert Alignment\" value=\"Center\" />" +
        "                <attribute name=\"Color\" value=\"0 0 0 1\" />" +
        "                <attribute name=\"Text\" value=\"Gyroscope\" />" +
        "            </element>" +
        "            <element type=\"Text\">" +
        "                <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "                <attribute name=\"Text\" value=\"G\" />" +
        "            </element>" +
        "        </element>" +
        "    </add>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">1st/3rd</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"F\" />" +
        "        </element>" +
        "    </add>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Jump</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"SPACE\" />" +
        "        </element>" +
        "    </add>" +
        "</patch>";
