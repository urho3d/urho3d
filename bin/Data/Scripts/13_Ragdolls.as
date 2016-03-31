// Ragdoll example.
// This sample demonstrates:
//     - Detecting physics collisions
//     - Moving an AnimatedModel's bones with physics and connecting them with constraints
//     - Using rolling friction to stop rolling objects from moving infinitely

#include "Scripts/Utilities/Sample.as"

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateInstructions();

    // Setup the viewport for displaying the scene
    SetupViewport();

    // Hook up to the frame update and render post-update events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    // Create a physics simulation world with default parameters, which will update at 60fps. Like the Octree must
    // exist before creating drawable components, the PhysicsWorld must exist before creating physics components.
    // Finally, create a DebugRenderer component so that we can draw physics debug geometry
    scene_.CreateComponent("Octree");
    scene_.CreateComponent("PhysicsWorld");
    scene_.CreateComponent("DebugRenderer");

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

    {
        // Create a floor object, 500 x 500 world units. Adjust position so that the ground is at zero Y
        Node@ floorNode = scene_.CreateChild("Floor");
        floorNode.position = Vector3(0.0f, -0.5f, 0.0f);
        floorNode.scale = Vector3(500.0f, 1.0f, 500.0f);
        StaticModel@ floorObject = floorNode.CreateComponent("StaticModel");
        floorObject.model = cache.GetResource("Model", "Models/Box.mdl");
        floorObject.material = cache.GetResource("Material", "Materials/StoneTiled.xml");

        // Make the floor physical by adding RigidBody and CollisionShape components
        RigidBody@ body = floorNode.CreateComponent("RigidBody");
        // We will be spawning spherical objects in this sample. The ground also needs non-zero rolling friction so that
        // the spheres will eventually come to rest
        body.rollingFriction = 0.15f;
        CollisionShape@ shape = floorNode.CreateComponent("CollisionShape");
        // Set a box shape of size 1 x 1 x 1 for collision. The shape will be scaled with the scene node scale, so the
        // rendering and physics representation sizes should match (the box model is also 1 x 1 x 1.)
        shape.SetBox(Vector3(1.0f, 1.0f, 1.0f));
    }

    // Create animated models
    for (int z = -1; z <= 1; ++z)
    {
        for (int x = -4; x <= 4; ++x)
        {
            Node@ modelNode = scene_.CreateChild("Jack");
            modelNode.position = Vector3(x * 5.0f, 0.0f, z * 5.0f);
            modelNode.rotation = Quaternion(0.0f, 180.0f, 0.0f);
            AnimatedModel@ modelObject = modelNode.CreateComponent("AnimatedModel");
            modelObject.model = cache.GetResource("Model", "Models/Jack.mdl");
            modelObject.material = cache.GetResource("Material", "Materials/Jack.xml");
            modelObject.castShadows = true;
            // Set the model to also update when invisible to avoid staying invisible when the model should come into
            // view, but does not as the bounding box is not updated
            modelObject.updateInvisible = true;

            // Create a rigid body and a collision shape. These will act as a trigger for transforming the
            // model into a ragdoll when hit by a moving object
            RigidBody@ body = modelNode.CreateComponent("RigidBody");
            // The trigger mode makes the rigid body only detect collisions, but impart no forces on the
            // colliding objects
            body.trigger = true;
            CollisionShape@ shape = modelNode.CreateComponent("CollisionShape");
            // Create the capsule shape with an offset so that it is correctly aligned with the model, which
            // has its origin at the feet
            shape.SetCapsule(0.7f, 2.0f, Vector3(0.0f, 1.0f, 0.0f));

            // Create a custom script object that reacts to collisions and creates the ragdoll
            modelNode.CreateScriptObject(scriptFile, "CreateRagdoll");
        }
    }

    // Create the camera. Limit far clip distance to match the fog. Note: now we actually create the camera node outside
    // the scene, because we want it to be unaffected by scene load / save
    cameraNode = Node();
    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.farClip = 300.0f;

    // Set an initial position for the camera scene node above the floor
    cameraNode.position = Vector3(0.0f, 5.0f, -20.0f);
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text =
        "Use WASD keys and mouse to move\n"
        "LMB to spawn physics objects\n"
        "F5 to save scene, F7 to load\n"
        "Space to toggle physics debug geometry";
    instructionText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    instructionText.textAlignment = HA_CENTER;

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
}

void SetupViewport()
{
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
    renderer.viewports[0] = viewport;
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");

    // Subscribe HandlePostRenderUpdate() function for processing the post-render update event, during which we request
    // debug geometry
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
}

void MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (ui.focusElement !is null)
        return;

    // Movement speed as world units per second
    const float MOVE_SPEED = 20.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    IntVector2 mouseMove = input.mouseMove;
    yaw += MOUSE_SENSITIVITY * mouseMove.x;
    pitch += MOUSE_SENSITIVITY * mouseMove.y;
    pitch = Clamp(pitch, -90.0f, 90.0f);

    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode.rotation = Quaternion(pitch, yaw, 0.0f);

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input.keyDown['W'])
        cameraNode.Translate(Vector3(0.0f, 0.0f, 1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['S'])
        cameraNode.Translate(Vector3(0.0f, 0.0f, -1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['A'])
        cameraNode.Translate(Vector3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['D'])
        cameraNode.Translate(Vector3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);

    // "Shoot" a physics object with left mousebutton
    if (input.mouseButtonPress[MOUSEB_LEFT])
        SpawnObject();

    // Check for loading / saving the scene
    if (input.keyPress[KEY_F5])
    {
        File saveFile(fileSystem.programDir + "Data/Scenes/Ragdolls.xml", FILE_WRITE);
        scene_.SaveXML(saveFile);
    }
    if (input.keyPress[KEY_F7])
    {
        File loadFile(fileSystem.programDir + "Data/Scenes/Ragdolls.xml", FILE_READ);
        scene_.LoadXML(loadFile);
    }

    // Toggle debug geometry with space
    if (input.keyPress[KEY_SPACE])
        drawDebug = !drawDebug;
}

void SpawnObject()
{
    Node@ boxNode = scene_.CreateChild("Sphere");
    boxNode.position = cameraNode.position;
    boxNode.rotation = cameraNode.rotation;
    boxNode.SetScale(0.25f);
    StaticModel@ boxObject = boxNode.CreateComponent("StaticModel");
    boxObject.model = cache.GetResource("Model", "Models/Sphere.mdl");
    boxObject.material = cache.GetResource("Material", "Materials/StoneSmall.xml");
    boxObject.castShadows = true;

    RigidBody@ body = boxNode.CreateComponent("RigidBody");
    body.mass = 1.0f;
    body.rollingFriction = 0.15f;
    CollisionShape@ shape = boxNode.CreateComponent("CollisionShape");
    shape.SetSphere(1.0f);

    const float OBJECT_VELOCITY = 10.0f;

    // Set initial velocity for the RigidBody based on camera forward vector. Add also a slight up component
    // to overcome gravity better
    body.linearVelocity = cameraNode.rotation * Vector3(0.0f, 0.25f, 1.0f) * OBJECT_VELOCITY;
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);
}

void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    // If draw debug mode is enabled, draw physics debug geometry. Use depth test to make the result easier to interpret
    if (drawDebug)
        scene_.physicsWorld.DrawDebugGeometry(true);
}

// CreateRagdoll script object class
class CreateRagdoll : ScriptObject
{
    void Start()
    {
        // Subscribe physics collisions that concern this scene node
        SubscribeToEvent(node, "NodeCollision", "HandleNodeCollision");
    }

    void HandleNodeCollision(StringHash eventType, VariantMap& eventData)
    {
        // Get the other colliding body, make sure it is moving (has nonzero mass)
        RigidBody@ otherBody = eventData["OtherBody"].GetPtr();

        if (otherBody.mass > 0.0f)
        {
            // We do not need the physics components in the AnimatedModel's root scene node anymore
            node.RemoveComponent("RigidBody");
            node.RemoveComponent("CollisionShape");

            // Create RigidBody & CollisionShape components to bones
            CreateRagdollBone("Bip01_Pelvis", SHAPE_BOX, Vector3(0.3f, 0.2f, 0.25f), Vector3(0.0f, 0.0f, 0.0f),
                Quaternion(0.0f, 0.0f, 0.0f));
            CreateRagdollBone("Bip01_Spine1", SHAPE_BOX, Vector3(0.35f, 0.2f, 0.3f), Vector3(0.15f, 0.0f, 0.0f),
                Quaternion(0.0f, 0.0f, 0.0f));
            CreateRagdollBone("Bip01_L_Thigh", SHAPE_CAPSULE, Vector3(0.175f, 0.45f, 0.175f), Vector3(0.25f, 0.0f, 0.0f),
                Quaternion(0.0f, 0.0f, 90.0f));
            CreateRagdollBone("Bip01_R_Thigh", SHAPE_CAPSULE, Vector3(0.175f, 0.45f, 0.175f), Vector3(0.25f, 0.0f, 0.0f),
                Quaternion(0.0f, 0.0f, 90.0f));
            CreateRagdollBone("Bip01_L_Calf", SHAPE_CAPSULE, Vector3(0.15f, 0.55f, 0.15f), Vector3(0.25f, 0.0f, 0.0f),
                Quaternion(0.0f, 0.0f, 90.0f));
            CreateRagdollBone("Bip01_R_Calf", SHAPE_CAPSULE, Vector3(0.15f, 0.55f, 0.15f), Vector3(0.25f, 0.0f, 0.0f),
                Quaternion(0.0f, 0.0f, 90.0f));
            CreateRagdollBone("Bip01_Head", SHAPE_BOX, Vector3(0.2f, 0.2f, 0.2f), Vector3(0.1f, 0.0f, 0.0f),
                Quaternion(0.0f, 0.0f, 0.0f));
            CreateRagdollBone("Bip01_L_UpperArm", SHAPE_CAPSULE, Vector3(0.15f, 0.35f, 0.15f), Vector3(0.1f, 0.0f, 0.0f),
                Quaternion(0.0f, 0.0f, 90.0f));
            CreateRagdollBone("Bip01_R_UpperArm", SHAPE_CAPSULE, Vector3(0.15f, 0.35f, 0.15f), Vector3(0.1f, 0.0f, 0.0f),
                Quaternion(0.0f, 0.0f, 90.0f));
            CreateRagdollBone("Bip01_L_Forearm", SHAPE_CAPSULE, Vector3(0.125f, 0.4f, 0.125f), Vector3(0.2f, 0.0f, 0.0f),
                Quaternion(0.0f, 0.0f, 90.0f));
            CreateRagdollBone("Bip01_R_Forearm", SHAPE_CAPSULE, Vector3(0.125f, 0.4f, 0.125f), Vector3(0.2f, 0.0f, 0.0f),
                Quaternion(0.0f, 0.0f, 90.0f));

            // Create Constraints between bones
            CreateRagdollConstraint("Bip01_L_Thigh", "Bip01_Pelvis", CONSTRAINT_CONETWIST, Vector3(0.0f, 0.0f, -1.0f),
                Vector3(0.0f, 0.0f, 1.0f), Vector2(45.0f, 45.0f), Vector2(0.0f, 0.0f));
            CreateRagdollConstraint("Bip01_R_Thigh", "Bip01_Pelvis", CONSTRAINT_CONETWIST, Vector3(0.0f, 0.0f, -1.0f),
                Vector3(0.0f, 0.0f, 1.0f), Vector2(45.0f, 45.0f), Vector2(0.0f, 0.0f));
            CreateRagdollConstraint("Bip01_L_Calf", "Bip01_L_Thigh", CONSTRAINT_HINGE, Vector3(0.0f, 0.0f, -1.0f),
                Vector3(0.0f, 0.0f, -1.0f), Vector2(90.0f, 0.0f), Vector2(0.0f, 0.0f));
            CreateRagdollConstraint("Bip01_R_Calf", "Bip01_R_Thigh", CONSTRAINT_HINGE, Vector3(0.0f, 0.0f, -1.0f),
                Vector3(0.0f, 0.0f, -1.0f), Vector2(90.0f, 0.0f), Vector2(0.0f, 0.0f));
            CreateRagdollConstraint("Bip01_Spine1", "Bip01_Pelvis", CONSTRAINT_HINGE, Vector3(0.0f, 0.0f, 1.0f),
                Vector3(0.0f, 0.0f, 1.0f), Vector2(45.0f, 0.0f), Vector2(-10.0f, 0.0f));
            CreateRagdollConstraint("Bip01_Head", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(-1.0f, 0.0f, 0.0f),
                Vector3(-1.0f, 0.0f, 0.0f), Vector2(0.0f, 30.0f), Vector2(0.0f, 0.0f));
            CreateRagdollConstraint("Bip01_L_UpperArm", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0.0f, -1.0f, 0.0f),
                Vector3(0.0f, 1.0f, 0.0f), Vector2(45.0f, 45.0f), Vector2(0.0f, 0.0f), false);
            CreateRagdollConstraint("Bip01_R_UpperArm", "Bip01_Spine1", CONSTRAINT_CONETWIST, Vector3(0.0f, -1.0f, 0.0f),
                Vector3(0.0f, 1.0f, 0.0f), Vector2(45.0f, 45.0f), Vector2(0.0f, 0.0f), false);
            CreateRagdollConstraint("Bip01_L_Forearm", "Bip01_L_UpperArm", CONSTRAINT_HINGE, Vector3(0.0f, 0.0f, -1.0f),
                Vector3(0.0f, 0.0f, -1.0f), Vector2(90.0f, 0.0f), Vector2(0.0f, 0.0f));
            CreateRagdollConstraint("Bip01_R_Forearm", "Bip01_R_UpperArm", CONSTRAINT_HINGE, Vector3(0.0f, 0.0f, -1.0f),
                Vector3(0.0f, 0.0f, -1.0f), Vector2(90.0f, 0.0f), Vector2(0.0f, 0.0f));

            // Disable keyframe animation from all bones so that they will not interfere with the ragdoll
            AnimatedModel@ model = node.GetComponent("AnimatedModel");
            Skeleton@ skeleton = model.skeleton;
            for (uint i = 0; i < skeleton.numBones; ++i)
                skeleton.bones[i].animated = false;

            // Finally remove self (the ScriptInstance which holds this script object) from the scene node. Note that this must
            // be the last operation performed in the function
            self.Remove();
        }
    }

    void CreateRagdollBone(const String&in boneName, ShapeType type, const Vector3&in size, const Vector3&in position,
        const Quaternion&in rotation)
    {
        // Find the correct child scene node recursively
        Node@ boneNode = node.GetChild(boneName, true);
        if (boneNode is null)
        {
            log.Warning("Could not find bone " + boneName + " for creating ragdoll physics components");
            return;
        }

        RigidBody@ body = boneNode.CreateComponent("RigidBody");
        // Set mass to make movable
        body.mass = 1.0f;
        // Set damping parameters to smooth out the motion
        body.linearDamping = 0.05f;
        body.angularDamping = 0.85f;
        // Set rest thresholds to ensure the ragdoll rigid bodies come to rest to not consume CPU endlessly
        body.linearRestThreshold = 1.5f;
        body.angularRestThreshold = 2.5f;

        CollisionShape@ shape = boneNode.CreateComponent("CollisionShape");
        // We use either a box or a capsule shape for all of the bones
        if (type == SHAPE_BOX)
            shape.SetBox(size, position, rotation);
        else
            shape.SetCapsule(size.x, size.y, position, rotation);
    }

    void CreateRagdollConstraint(const String&in boneName, const String&in parentName, ConstraintType type,
        const Vector3&in axis, const Vector3&in parentAxis, const Vector2&in highLimit, const Vector2&in lowLimit,
        bool disableCollision = true)
    {
        Node@ boneNode = node.GetChild(boneName, true);
        Node@ parentNode = node.GetChild(parentName, true);
        if (boneNode is null)
        {
            log.Warning("Could not find bone " + boneName + " for creating ragdoll constraint");
            return;
        }
        if (parentNode is null)
        {
            log.Warning("Could not find bone " + parentName + " for creating ragdoll constraint");
            return;
        }

        Constraint@ constraint = boneNode.CreateComponent("Constraint");
        constraint.constraintType = type;
        // Most of the constraints in the ragdoll will work better when the connected bodies don't collide against each other
        constraint.disableCollision = disableCollision;
        // The connected body must be specified before setting the world position
        constraint.otherBody = parentNode.GetComponent("RigidBody");
        // Position the constraint at the child bone we are connecting
        constraint.worldPosition = boneNode.worldPosition;
        // Configure axes and limits
        constraint.axis = axis;
        constraint.otherAxis = parentAxis;
        constraint.highLimit = highLimit;
        constraint.lowLimit = lowLimit;
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Spawn</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"MouseButtonBinding\" />" +
        "            <attribute name=\"Text\" value=\"LEFT\" />" +
        "        </element>" +
        "    </add>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Debug</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"SPACE\" />" +
        "        </element>" +
        "    </add>" +
        "</patch>";
