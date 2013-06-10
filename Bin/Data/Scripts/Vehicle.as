Scene@ testScene;
Camera@ camera;
Node@ cameraNode;
Node@ vehicleHullNode;

float yaw = 0.0;
float pitch = 0.0;
int drawDebug = 0;

void Start()
{
    if (!engine.headless)
    {
        InitConsole();
        InitUI();
    }
    else
        OpenConsoleWindow();

    InitScene();
    InitVehicle();

    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent("PostUpdate", "HandlePostUpdate");
    SubscribeToEvent("KeyDown", "HandleKeyDown");
    SubscribeToEvent("MouseMove", "HandleMouseMove");
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
}

void InitConsole()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    engine.CreateDebugHud();
    debugHud.defaultStyle = uiStyle;
    debugHud.mode = DEBUGHUD_SHOW_ALL;

    engine.CreateConsole();
    console.defaultStyle = uiStyle;
}

void InitUI()
{
    XMLFile@ uiStyle = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    Cursor@ newCursor = Cursor("Cursor");
    newCursor.SetStyleAuto(uiStyle);
    newCursor.position = IntVector2(graphics.width / 2, graphics.height / 2);
    ui.cursor = newCursor;
    ui.cursor.visible = false;
}

void InitScene()
{
    testScene = Scene("TestScene");

    // Enable access to this script file & scene from the console
    script.defaultScene = testScene;
    script.defaultScriptFile = scriptFile;

    // Create the camera outside the scene so it is unaffected by scene load/save
    cameraNode = Node();
    camera = cameraNode.CreateComponent("Camera");
    camera.farClip = 1000;
    camera.nearClip = 0.5;
    cameraNode.position = Vector3(0, 20, 0);

    if (!engine.headless)
    {
        renderer.viewports[0] = Viewport(testScene, camera);
        audio.listener = cameraNode.CreateComponent("SoundListener");
    }

    PhysicsWorld@ world = testScene.CreateComponent("PhysicsWorld");
    testScene.CreateComponent("Octree");
    testScene.CreateComponent("DebugRenderer");

    Node@ zoneNode = testScene.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.ambientColor = Color(0.15, 0.15, 0.15);
    zone.fogColor = Color(0.5, 0.5, 0.7);
    zone.fogStart = 500.0;
    zone.fogEnd = 1000.0;
    zone.boundingBox = BoundingBox(-2000, 2000);

    {
        Node@ lightNode = testScene.CreateChild("GlobalLight");
        lightNode.direction = Vector3(0.5, -0.5, 0.5);

        Light@ light = lightNode.CreateComponent("Light");
        light.lightType = LIGHT_DIRECTIONAL;
        light.castShadows = true;
        light.shadowBias = BiasParameters(0.0001, 0.5);
        light.shadowCascade = CascadeParameters(15.0, 50.0, 200.0, 0.0, 0.8);
        light.specularIntensity = 0.5;
    }

    Terrain@ terrain;

    {
        Node@ terrainNode = testScene.CreateChild("Terrain");
        terrainNode.position = Vector3(0, 0, 0);
        terrain = terrainNode.CreateComponent("Terrain");
        terrain.patchSize = 64;
        terrain.spacing = Vector3(2, 0.1, 2);
        terrain.heightMap = cache.GetResource("Image", "Textures/HeightMap.png");
        terrain.material = cache.GetResource("Material", "Materials/Terrain.xml");
        terrain.occluder = true;

        RigidBody@ body = terrainNode.CreateComponent("RigidBody");
        body.collisionLayer = 2;
        CollisionShape@ shape = terrainNode.CreateComponent("CollisionShape");
        shape.SetTerrain();
        shape.margin = 0.01;
    }

    for (uint i = 0; i < 1000; ++i)
    {
        Node@ objectNode = testScene.CreateChild("Mushroom");
        Vector3 position(Random() * 2000 - 1000, 0, Random() * 2000 - 1000);
        position.y = terrain.GetHeight(position) - 0.1;

        objectNode.position = position;
        objectNode.rotation = Quaternion(Vector3(0, 1, 0), terrain.GetNormal(position));
        objectNode.SetScale(3);

        StaticModel@ object = objectNode.CreateComponent("StaticModel");
        object.model = cache.GetResource("Model", "Models/Mushroom.mdl");
        object.material = cache.GetResource("Material", "Materials/Mushroom.xml");
        object.castShadows = true;

        RigidBody@ body = objectNode.CreateComponent("RigidBody");
        body.collisionLayer = 2;
        CollisionShape@ shape = objectNode.CreateComponent("CollisionShape");
        shape.SetTriangleMesh(cache.GetResource("Model", "Models/Mushroom.mdl"), 0);
    }
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();
    
    // Nothing to do for now
}

void HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();

    // Physics update has completed. Position camera behind vehicle
    Quaternion dir(vehicleHullNode.rotation.yaw, Vector3(0, 1, 0));;
    dir = dir * Quaternion(yaw, Vector3(0, 1, 0));
    dir = dir * Quaternion(pitch, Vector3(1, 0, 0));

    Vector3 cameraTargetPos = vehicleHullNode.position - dir * Vector3(0, 0, 10);
    Vector3 cameraStartPos = vehicleHullNode.position;

    // Raycast camera against static objects (physics collision mask 2)
    // and move it closer to the vehicle if something in between
    Ray cameraRay(cameraStartPos, (cameraTargetPos - cameraStartPos).Normalized());
    float cameraRayLength = (cameraTargetPos - cameraStartPos).length;
    PhysicsRaycastResult result = scene.physicsWorld.RaycastSingle(cameraRay, cameraRayLength, 2);
    if (result.body !is null)
        cameraTargetPos = cameraStartPos + cameraRay.direction * (result.distance - 0.5f);

    cameraNode.position = cameraTargetPos;
    cameraNode.rotation = dir;
}

void HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();

    if (key == KEY_ESC)
    {
        if (ui.focusElement is null)
            engine.Exit();
        else
            console.visible = false;
    }

    if (key == KEY_F1)
        console.Toggle();

    if (ui.focusElement is null)
    {
        if (key == '1')
        {
            int quality = renderer.textureQuality;
            ++quality;
            if (quality > 2)
                quality = 0;
            renderer.textureQuality = quality;
        }

        if (key == '2')
        {
            int quality = renderer.materialQuality;
            ++quality;
            if (quality > 2)
                quality = 0;
            renderer.materialQuality = quality;
        }

        if (key == '3')
            renderer.specularLighting = !renderer.specularLighting;

        if (key == '4')
            renderer.drawShadows = !renderer.drawShadows;

        if (key == '5')
        {
            int size = renderer.shadowMapSize;
            size *= 2;
            if (size > 2048)
                size = 512;
            renderer.shadowMapSize = size;
        }

        if (key == '6')
            renderer.shadowQuality = renderer.shadowQuality + 1;

        if (key == '7')
        {
            bool occlusion = renderer.maxOccluderTriangles > 0;
            occlusion = !occlusion;
            renderer.maxOccluderTriangles = occlusion ? 5000 : 0;
        }

        if (key == '8')
            renderer.dynamicInstancing = !renderer.dynamicInstancing;

        if (key == ' ')
        {
            drawDebug++;
            if (drawDebug > 2)
                drawDebug = 0;
        }

        if (key == 'T')
            debugHud.Toggle(DEBUGHUD_SHOW_PROFILER);
    }
}

void HandleMouseMove(StringHash eventType, VariantMap& eventData)
{
    int mousedx = eventData["DX"].GetInt();
    int mousedy = eventData["DY"].GetInt();
    yaw += mousedx / 10.0;
    pitch += mousedy / 10.0;
    if (pitch < 0.0)
        pitch = 0.0;
    if (pitch > 60.0)
        pitch = 60.0;
}

void HandlePostRenderUpdate()
{
    if (engine.headless)
        return;

    // Draw rendering debug geometry without depth test to see the effect of occlusion
    if (drawDebug == 1)
        renderer.DrawDebugGeometry(false);
    if (drawDebug == 2)
        testScene.physicsWorld.DrawDebugGeometry(true);
}

void InitVehicle()
{
    vehicleHullNode = testScene.CreateChild("VehicleHull");
    StaticModel@ hullObject = vehicleHullNode.CreateComponent("StaticModel");
    RigidBody@ hullBody = vehicleHullNode.CreateComponent("RigidBody");
    CollisionShape@ hullShape = vehicleHullNode.CreateComponent("CollisionShape");

    vehicleHullNode.position = Vector3(0, 5, 0);
    vehicleHullNode.scale = Vector3(1.5, 1, 3);
    hullObject.model = cache.GetResource("Model", "Models/Box.mdl");
    hullObject.material = cache.GetResource("Material", "Materials/Stone.xml");
    hullObject.castShadows = true;
    hullShape.SetBox(Vector3(1, 1, 1));
    hullBody.mass = 3;
    hullBody.linearDamping = 0.2; // Some air resistance
    hullBody.collisionLayer = 1;

    Node@ fl = InitVehicleWheel("FrontLeft", vehicleHullNode, Vector3(-0.6, -0.4, 0.3));
    Node@ fr = InitVehicleWheel("FrontRight", vehicleHullNode, Vector3(0.6, -0.4, 0.3));
    Node@ rr = InitVehicleWheel("RearLeft", vehicleHullNode, Vector3(-0.6, -0.4, -0.3));
    Node@ rl = InitVehicleWheel("RearRight", vehicleHullNode, Vector3(0.6, -0.4, -0.3));

    Vehicle@ vehicle = cast<Vehicle>(vehicleHullNode.CreateScriptObject(scriptFile, "Vehicle"));
    vehicle.SetWheels(fl, fr, rl, rr);
}

Node@ InitVehicleWheel(String name, Node@ vehicleHullNode, Vector3 offset)
{
    Node@ wheelNode = testScene.CreateChild(name);
    wheelNode.position = vehicleHullNode.LocalToWorld(offset);
    wheelNode.rotation = vehicleHullNode.worldRotation * (offset.x >= 0.0 ? Quaternion(0, 0, -90) : Quaternion(0, 0, 90));
    wheelNode.scale = Vector3(0.75, 0.5, 0.75);

    StaticModel@ wheelObject = wheelNode.CreateComponent("StaticModel");
    RigidBody@ wheelBody = wheelNode.CreateComponent("RigidBody");
    CollisionShape@ wheelShape = wheelNode.CreateComponent("CollisionShape");
    Constraint@ wheelConstraint = wheelNode.CreateComponent("Constraint");

    wheelObject.model = cache.GetResource("Model", "Models/Cylinder.mdl");
    wheelObject.material = cache.GetResource("Material", "Materials/Stone.xml");
    wheelObject.castShadows = true;
    wheelShape.SetCylinder(1, 1);
    wheelBody.friction = 1;
    wheelBody.mass = 1;
    wheelBody.linearDamping = 0.2; // Some air resistance
    wheelBody.angularDamping = 0.75; // Current version of Bullet used by Urho doesn't have rolling friction, so mimic that with
                                    // some angular damping on the wheels
    wheelBody.collisionLayer = 1;
    wheelConstraint.constraintType = CONSTRAINT_HINGE;
    wheelConstraint.otherBody = vehicleHullNode.GetComponent("RigidBody");
    wheelConstraint.worldPosition = wheelNode.worldPosition; // Set constraint's both ends at wheel's location
    wheelConstraint.axis = Vector3(0, 1, 0); // Wheel rotates around its local Y-axis
    wheelConstraint.otherAxis = offset.x >= 0.0 ? Vector3(1, 0, 0) : Vector3(-1, 0, 0); // Wheel's hull axis points either left or right
    wheelConstraint.lowLimit = Vector2(-180, 0); // Let the wheel rotate freely around the axis
    wheelConstraint.highLimit = Vector2(180, 0);
    wheelConstraint.disableCollision = true; // Let the wheel intersect the vehicle hull

    return wheelNode;
}

class Vehicle : ScriptObject
{
    Node@ frontLeft;
    Node@ frontRight;
    Node@ rearLeft;
    Node@ rearRight;
    Constraint@ frontLeftAxis;
    Constraint@ frontRightAxis;
    RigidBody@ hullBody;
    RigidBody@ frontLeftBody;
    RigidBody@ frontRightBody;
    RigidBody@ rearLeftBody;
    RigidBody@ rearRightBody;

    float steering = 0.0;
    float enginePower = 8.0;
    float downForce = 10.0;
    float maxWheelAngle = 22.5;

    void SetWheels(Node@ fl, Node@ fr, Node@ rl, Node@ rr)
    {
        frontLeft = fl;
        frontRight = fr;
        rearLeft = rl;
        rearRight = rr;

        hullBody = node.GetComponent("RigidBody");
        frontLeftAxis = frontLeft.GetComponent("Constraint");
        frontRightAxis = frontRight.GetComponent("Constraint");
        frontLeftBody = frontLeft.GetComponent("RigidBody");
        frontRightBody = frontRight.GetComponent("RigidBody");
        rearLeftBody = rearLeft.GetComponent("RigidBody");
        rearRightBody = rearRight.GetComponent("RigidBody");
    }

    void FixedUpdate(float timeStep)
    {
        float newSteering = 0.0;
        float accelerator = 0.0;

        if (ui.focusElement is null)
        {
            if (input.keyDown['A'])
                newSteering = -1.0f;
            if (input.keyDown['D'])
                newSteering = 1.0f;
            if (input.keyDown['W'])
                accelerator = 1.0f;
            if (input.keyDown['S'])
                accelerator = -0.5f;
        }

        // When steering, wake up the wheel rigidbodies so that their orientation is updated
        if (newSteering != 0.0)
        {
            frontLeftBody.Activate();
            frontRightBody.Activate();
            steering = steering * 0.95 + newSteering * 0.05;
        }
        else
            steering = steering * 0.8 + newSteering * 0.2;

        Quaternion steeringRot(0, steering * maxWheelAngle, 0);

        frontLeftAxis.otherAxis = steeringRot * Vector3(-1, 0, 0);
        frontRightAxis.otherAxis = steeringRot * Vector3(1, 0, 0);

        if (accelerator != 0.0)
        {
            // Torques are applied in world space, so need to take the vehicle & wheel rotation into account
            Vector3 torqueVec = Vector3(enginePower * accelerator, 0, 0);
            
            frontLeftBody.ApplyTorque(node.rotation * steeringRot * torqueVec);
            frontRightBody.ApplyTorque(node.rotation * steeringRot * torqueVec);
            rearLeftBody.ApplyTorque(node.rotation * torqueVec);
            rearRightBody.ApplyTorque(node.rotation * torqueVec);
        }

        // Apply downforce proportional to velocity
        Vector3 localVelocity = node.worldRotation.Inverse() * hullBody.linearVelocity;
        hullBody.ApplyForce(Vector3(0, -1, 0) * Abs(localVelocity.z) * downForce);
    }
}
