// Vehicle example.
// This sample demonstrates:
//     - Creating a heightmap terrain with collision
//     - Constructing a physical vehicle with rigid bodies for the hull and the wheels, joined with constraints
//     - Saving and loading the variables of a script object, including node & component references

#include "Scripts/Utilities/Sample.as"

const int CTRL_FORWARD = 1;
const int CTRL_BACK = 2;
const int CTRL_LEFT = 4;
const int CTRL_RIGHT = 8;
const int CTRL_BRAKE = 16;

const float CAMERA_DISTANCE = 10.0f;
const float YAW_SENSITIVITY = 0.1f;
const float ENGINE_FORCE = 2500.0f;
const float DOWN_FORCE = 100.0f;
const float MAX_WHEEL_ANGLE = 22.5f;
const float CHASSIS_WIDTH = 2.6f;

Node@ vehicleNode;

void Start()
{
    // Execute the common startup for samples
    SampleStart();
    // Create static scene content
    CreateScene();
    // Create the controllable vehicle
    CreateVehicle();
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
    camera.farClip = 500.0f;
    renderer.viewports[0] = Viewport(scene_, camera);
    // Create static scene content. First create a zone for ambient lighting and fog control
    Node@ zoneNode = scene_.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.ambientColor = Color(0.15f, 0.15f, 0.15f);
    zone.fogColor = Color(0.5f, 0.5f, 0.7f);
    zone.fogStart = 300.0f;
    zone.fogEnd = 500.0f;
    zone.boundingBox = BoundingBox(-2000.0f, 2000.0f);
    // Create a directional light to the world. Enable cascaded shadows on it
    Node@ lightNode = scene_.CreateChild("DirectionalLight");
    lightNode.direction = Vector3(0.3f, -0.5f, 0.425f);
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_DIRECTIONAL;
    light.castShadows = true;
    light.shadowBias = BiasParameters(0.00025f, 0.5f);
    light.shadowCascade = CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f);
    light.specularIntensity = 0.5f;
    // Create heightmap terrain with collision
    Node@ terrainNode = scene_.CreateChild("Terrain");
    terrainNode.position = Vector3(0.0f, 0.0f, 0.0f);
    Terrain@ terrain = terrainNode.CreateComponent("Terrain");
    terrain.patchSize = 64;
    terrain.spacing = Vector3(2.0f, 0.1f, 2.0f);       // Spacing between vertices and vertical resolution of the height map
    terrain.smoothing = true;
    terrain.heightMap = cache.GetResource("Image", "Textures/HeightMap.png");
    terrain.material = cache.GetResource("Material", "Materials/Terrain.xml");
    // The terrain consists of large triangles, which fits well for occlusion rendering, as a hill can occlude all
    // terrain patches and other objects behind it
    terrain.occluder = true;
    RigidBody@ body = terrainNode.CreateComponent("RigidBody");
    body.collisionLayer = 2;   // Use layer bitmask 2 for static geometry
    CollisionShape@ shape = terrainNode.CreateComponent("CollisionShape");
    shape.SetTerrain();
    // Create 1000 mushrooms in the terrain. Always face outward along the terrain normal
    const uint NUM_MUSHROOMS = 1000;
    for (uint i = 0; i < NUM_MUSHROOMS; ++i)
    {
        Node@ objectNode = scene_.CreateChild("Mushroom");
        Vector3 position(Random(2000.0f) - 1000.0f, 0.0f, Random(2000.0f) - 1000.0f);
        position.y = terrain.GetHeight(position) - 0.1f;
        objectNode.position = position;
        // Create a rotation quaternion from up vector to terrain normal
        objectNode.rotation = Quaternion(Vector3(0.0f, 1.0f, 0.0), terrain.GetNormal(position));
        objectNode.SetScale(3.0f);
        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Mushroom.mdl");
        object.material = cache.GetResource("Material", "Materials/Mushroom.xml");
        object.castShadows = true;
        RigidBody@ mushroomBody = objectNode.CreateComponent("RigidBody");
        mushroomBody.collisionLayer = 2;
        CollisionShape@ mushroomShape = objectNode.CreateComponent("CollisionShape");
        mushroomShape.SetTriangleMesh(object.model, 0);
    }
}

void CreateVehicle()
{
    vehicleNode = scene_.CreateChild("Vehicle");
    vehicleNode.position = Vector3(0.0f, 5.0f, 0.0f);
    // First createing player-controlled vehicle
    // Create the vehicle logic script object
    Vehicle@ vehicle = cast<Vehicle>(vehicleNode.CreateScriptObject(scriptFile, "Vehicle"));
    // Initialize vehicle component
    vehicle.Init();
    vehicleNode.AddTag("vehicle");
    // Set RigidBody physics parameters
    // (The RigidBody was created by vehicle.Init()
    RigidBody@ hullBody = vehicleNode.GetComponent("RigidBody");
    hullBody.mass = 800.0f;
    hullBody.linearDamping = 0.2f;     // Some air resistance
    hullBody.angularDamping = 0.5f;
    hullBody.collisionLayer = 1;
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text =
        "Use WASD keys to drive, F to brake, mouse/touch to rotate camera\n"
        "F5 to save scene, F7 to load";
    instructionText.
    SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    instructionText.textAlignment = HA_CENTER;
    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
}

void SubscribeToEvents()
{
    // Subscribe to Update event for setting the vehicle controls before physics simulation
    SubscribeToEvent("Update", "HandleUpdate");
    // Subscribe to PostUpdate event for updating the camera position after physics simulation
    SubscribeToEvent("PostUpdate", "HandlePostUpdate");
    // Unsubscribe the SceneUpdate event from base class as the camera node is being controlled in HandlePostUpdate() in this sample
    UnsubscribeFromEvent("SceneUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    if (vehicleNode is null)
        return;

    Vehicle@ vehicle = cast < Vehicle > (vehicleNode.scriptObject);
    if (vehicle is null)
        return;
    // Get movement controls and assign them to the vehicle component. If UI has a focused element, clear controls
    if (ui.focusElement is null)
    {
        vehicle.controls.Set(CTRL_FORWARD, input.keyDown[KEY_W]);
        vehicle.controls.Set(CTRL_BACK, input.keyDown[KEY_S]);
        vehicle.controls.Set(CTRL_LEFT, input.keyDown[KEY_A]);
        vehicle.controls.Set(CTRL_RIGHT, input.keyDown[KEY_D]);
        vehicle.controls.Set(CTRL_BRAKE, input.keyDown[KEY_F]);
        // Add yaw & pitch from the mouse motion. Used only for the camera, does not affect motion
        if (touchEnabled)
        {
            for (uint i = 0; i < input.numTouches; ++i)
            {
                TouchState@ state = input.touches[i];
                if (state.touchedElement is null)        // Touch on empty space
                {
                    Camera@ camera = cameraNode.GetComponent("Camera");
                    if (camera is null)
                        return;
                    vehicle.controls.yaw += TOUCH_SENSITIVITY * camera.fov / graphics.height * state.delta.x;
                    vehicle.controls.pitch += TOUCH_SENSITIVITY * camera.fov / graphics.height * state.delta.y;
                }
            }
        }
        else
        {
            vehicle.controls.yaw += input.mouseMoveX * YAW_SENSITIVITY;
            vehicle.controls.pitch += input.mouseMoveY * YAW_SENSITIVITY;
        }
        // Limit pitch
        vehicle.controls.pitch = Clamp(vehicle.controls.pitch, 0.0f, 80.0f);
        // Check for loading / saving the scene
        if (input.keyPress[KEY_F5])
        {
            File saveFile(fileSystem.programDir + "Data/Scenes/RaycastScriptVehicleDemo.xml", FILE_WRITE);
            scene_.SaveXML(saveFile);
        }
        if (input.keyPress[KEY_F7])
        {
            File loadFile(fileSystem.programDir + "Data/Scenes/RaycastScriptVehicleDemo.xml", FILE_READ);
            scene_.LoadXML(loadFile);
            // After loading we have to reacquire the vehicle scene node, as it has been recreated
            // Simply find by name as there's only one of them
            Array<Node@>@ vehicles = scene_.GetChildrenWithTag("vehicle");
            for (int i = 0; i < vehicles.length; i++)
            {
                Vehicle@ vehicleData = cast<Vehicle>(vehicles[i].scriptObject);
                vehicleData.CreateEmitters();
            }
            vehicleNode = scene_.GetChild("Vehicle", true);
        }
    }
    else
        vehicle.controls.Set(CTRL_FORWARD | CTRL_BACK | CTRL_LEFT | CTRL_RIGHT | CTRL_BRAKE, false);
}

void HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if (vehicleNode is null)
        return;
    Vehicle@ vehicle = cast < Vehicle > (vehicleNode.scriptObject);
    if (vehicle is null)
        return;
    // Physics update has completed. Position camera behind vehicle
    Quaternion dir(vehicleNode.rotation.yaw, Vector3(0.0f, 1.0f, 0.0f));
    dir = dir * Quaternion(vehicle.controls.yaw, Vector3(0.0f, 1.0f, 0.0f));
    dir = dir * Quaternion(vehicle.controls.pitch, Vector3(1.0f, 0.0f, 0.0f));
    Vector3 cameraTargetPos = vehicleNode.position - dir * Vector3(0.0f, 0.0f, CAMERA_DISTANCE);
    Vector3 cameraStartPos = vehicleNode.position;
    // Raycast camera against static objects (physics collision mask 2)
    // and move it closer to the vehicle if something in between
    Ray cameraRay(cameraStartPos, (cameraTargetPos - cameraStartPos).Normalized());
    float cameraRayLength = (cameraTargetPos - cameraStartPos).length;
    PhysicsRaycastResult result = scene_.physicsWorld.RaycastSingle(cameraRay, cameraRayLength, 2);
    if (result.body !is null)
        cameraTargetPos = cameraStartPos + cameraRay.direction * (result.distance - 0.5f);
    cameraNode.position = cameraTargetPos;
    cameraNode.rotation = dir;
}

// Vehicle script object class
//
// When saving, the node and component handles are automatically converted into nodeID or componentID attributes
// and are acquired from the scene when loading. The steering member variable will likewise be saved automatically.
// The Controls object can not be automatically saved, so handle it manually in the Load() and Save() methods

class Vehicle:ScriptObject
{

    RigidBody@ hullBody;

    // Current left/right steering amount (-1 to 1.)
    float steering = 0.0f;

    // Vehicle controls.
    Controls controls;

    float suspensionRestLength = 0.6f;
    float suspensionStiffness = 14.0f;
    float suspensionDamping = 2.0f;
    float suspensionCompression = 4.0f;
    float wheelFriction = 1000.0f;
    float rollInfluence = 0.12f;
    float maxEngineForce = ENGINE_FORCE;

    float wheelWidth = 0.4f;
    float wheelRadius = 0.5f;
    float brakingForce = 50.0f;
    Array<Vector3> connectionPoints;
    Array<Node@> particleEmitterNodeList;
    protected Vector3 prevVelocity;

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

    void Init()
    {
        // This function is called only from the main program when initially creating the vehicle, not on scene load
        StaticModel@ hullObject = node.CreateComponent("StaticModel");
        hullBody = node.CreateComponent("RigidBody");
        CollisionShape@ hullShape = node.CreateComponent("CollisionShape");
        node.scale = Vector3(2.3f, 1.0f, 4.0f);
        hullObject.model = cache.GetResource("Model", "Models/Box.mdl");
        hullObject.material = cache.GetResource("Material", "Materials/Stone.xml");
        hullObject.castShadows = true;
        hullShape.SetBox(Vector3(1.0f, 1.0f, 1.0f));
        hullBody.mass = 800.0f;
        hullBody.linearDamping = 0.2f; // Some air resistance
        hullBody.angularDamping = 0.5f;
        hullBody.collisionLayer = 1;
        RaycastVehicle@ raycastVehicle = node.CreateComponent("RaycastVehicle");
        raycastVehicle.Init();
        connectionPoints.Reserve(4);
        float connectionHeight = -0.4f;      //1.2f;
        bool isFrontWheel = true;
        Vector3 wheelDirection(0, -1, 0);
        Vector3 wheelAxle(-1, 0, 0);
        float wheelX = CHASSIS_WIDTH / 2.0 - wheelWidth;
        // Front left
        connectionPoints.Push(Vector3(-wheelX, connectionHeight, 2.5f - wheelRadius * 2.0f));
        // Front right
        connectionPoints.Push(Vector3(wheelX, connectionHeight, 2.5f - wheelRadius * 2.0f));
        // Back left
        connectionPoints.Push(Vector3(-wheelX, connectionHeight, -2.5f + wheelRadius * 2.0f));
        // Back right
        connectionPoints.Push(Vector3(wheelX, connectionHeight, -2.5f + wheelRadius * 2.0f));
        const Color LtBrown(0.972f, 0.780f, 0.412f);
        for (int id = 0; id < connectionPoints.length; id++)
        {
            Node@ wheelNode = scene_.CreateChild();
            Vector3 connectionPoint = connectionPoints[id];
            // Front wheels are at front (z > 0)
            // back wheels are at z < 0
            // Setting rotation according to wheel position
            bool isFrontWheel = connectionPoints[id].z > 0.0f;
            wheelNode.rotation = (connectionPoint.x >= 0.0 ? Quaternion(0.0f, 0.0f, -90.0f) : Quaternion(0.0f, 0.0f, 90.0f));
            wheelNode.worldPosition = (node.worldPosition + node.worldRotation * connectionPoints[id]);
            wheelNode.scale = Vector3(1.0f, 0.65f, 1.0f);
            raycastVehicle.AddWheel(wheelNode, wheelDirection, wheelAxle, suspensionRestLength, wheelRadius, isFrontWheel);
            raycastVehicle.SetWheelSuspensionStiffness(id, suspensionStiffness);
            raycastVehicle.SetWheelDampingRelaxation(id, suspensionDamping);
            raycastVehicle.SetWheelDampingCompression(id, suspensionCompression);
            raycastVehicle.SetWheelFrictionSlip(id, wheelFriction);
            raycastVehicle.SetWheelRollInfluence(id, rollInfluence);
            StaticModel@ pWheel = wheelNode.CreateComponent("StaticModel");
            pWheel.model = cache.GetResource("Model", "Models/Cylinder.mdl");
            pWheel.material = cache.GetResource("Material", "Materials/Stone.xml");
            pWheel.castShadows = true;
        }
        CreateEmitters();
        raycastVehicle.ResetWheels();
    }

    void CreateEmitter(Vector3 place)
    {
        Node@ emitter = scene_.CreateChild();
        emitter.worldPosition = node.worldPosition + node.worldRotation * place + Vector3(0, -wheelRadius, 0);
        ParticleEmitter@ particleEmitter = emitter.CreateComponent("ParticleEmitter");
        particleEmitter.effect = cache.GetResource("ParticleEffect", "Particle/Dust.xml");
        particleEmitter.emitting = false;
        particleEmitterNodeList.Push(emitter);
        emitter.temporary = true;
    }

    void CreateEmitters()
    {
        particleEmitterNodeList.Clear();
        RaycastVehicle@ raycastVehicle = node.GetComponent("RaycastVehicle");
        for (int id = 0; id < raycastVehicle.numWheels; id++)
        {
            Vector3 connectionPoint = raycastVehicle.GetWheelConnectionPoint(id);
            CreateEmitter(connectionPoint);
        }
    }

    void FixedUpdate(float timeStep)
    {
        float newSteering = 0.0f;
        float accelerator = 0.0f;
        bool brake = false;
        RaycastVehicle@ raycastVehicle = node.GetComponent("RaycastVehicle");
        if (controls.IsDown(CTRL_LEFT))
            newSteering = -1.0f;
        if (controls.IsDown(CTRL_RIGHT))
            newSteering = 1.0f;
        if (controls.IsDown(CTRL_FORWARD))
            accelerator = 1.0f;
        if (controls.IsDown(CTRL_BACK))
            accelerator = -0.5f;
        if (controls.IsDown(CTRL_BRAKE))
            brake = true;
        // When steering, wake up the wheel rigidbodies so that their orientation is updated
        if (newSteering != 0.0f)
        {
            steering = steering * 0.95f + newSteering * 0.05f;
        }
        else
            steering = steering * 0.8f + newSteering * 0.2f;
        Quaternion steeringRot(0.0f, steering * MAX_WHEEL_ANGLE, 0.0f);
        raycastVehicle.SetSteeringValue(0, steering);
        raycastVehicle.SetSteeringValue(1, steering);
        raycastVehicle.SetEngineForce(2, maxEngineForce * accelerator);
        raycastVehicle.SetEngineForce(3, maxEngineForce * accelerator);
        for (int i = 0; i < raycastVehicle.numWheels; i++)
        {
            if (brake)
            {
                raycastVehicle.SetBrake(i, brakingForce);
            }
            else
            {
                raycastVehicle.SetBrake(i, 0.0f);
            }
        }
        // Apply downforce proportional to velocity
        Vector3 localVelocity = hullBody.rotation.Inverse() * hullBody.linearVelocity;
        hullBody.ApplyForce(hullBody.rotation * Vector3(0.0f, -1.0f, 0.0f) * Abs(localVelocity.z) * DOWN_FORCE);
    }

    void PostUpdate(float timeStep)
    {
        if (particleEmitterNodeList.length == 0)
            return;
        RaycastVehicle@ raycastVehicle = node.GetComponent("RaycastVehicle");
        RigidBody@ vehicleBody = node.GetComponent("RigidBody");
        Vector3 velocity = hullBody.linearVelocity;
        Vector3 accel = (velocity - prevVelocity) / timeStep;
        float planeAccel = Vector3(accel.x, 0.0f, accel.z).length;
        for (int i = 0; i < raycastVehicle.numWheels; i++)
        {
            Node@ emitter = particleEmitterNodeList[i];
            ParticleEmitter@ particleEmitter = emitter.GetComponent("ParticleEmitter");
            if (raycastVehicle.WheelIsGrounded(i) && (raycastVehicle.GetWheelSkidInfoCumulative(i) < 0.9f || raycastVehicle.GetBrake(i) > 2.0f ||
                planeAccel > 15.0f))
            {
                emitter.worldPosition = raycastVehicle.GetContactPosition(i);
                if (!particleEmitter.emitting)
                    particleEmitter.emitting = true;
            }
            else if (particleEmitter.emitting)
                particleEmitter.emitting = false;
        }
        prevVelocity = velocity;
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions = "";

