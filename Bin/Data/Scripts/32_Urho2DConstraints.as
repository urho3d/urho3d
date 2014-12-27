// Urho2D physics Constraints sample.
// This sample is designed to help understanding and chosing the right constraint.
// This sample demonstrates:
//      - Creating physics constraints
//      - Creating Edge and Polygon Shapes from vertices
//      - Displaying physics debug geometry and constraints' joints
//      - Using SetOrderInLayer to alter the way sprites are drawn in relation to each other
//      - Using Text3D to display some text affected by zoom
//      - Setting the background color for the scene

#include "Scripts/Utilities/Sample.as"

Camera@ camera;
Node@ pickedNode;
RigidBody2D@ dummyBody;

void Start()
{
    SampleStart();
    CreateScene();
    input.mouseVisible = true; // Show mouse cursor
    CreateInstructions();
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();
    scene_.CreateComponent("Octree");
    scene_.CreateComponent("DebugRenderer");
    PhysicsWorld2D@ physicsWorld = scene_.CreateComponent("PhysicsWorld2D");
    physicsWorld.drawJoint = true; // Display the joints (Note that DrawDebugGeometry() must be set to true to acually draw the joints)
    drawDebug = true; // Set DrawDebugGeometry() to true

    // Create camera
    cameraNode = scene_.CreateChild("Camera");
    cameraNode.position = Vector3(0.0f, 0.0f, 0.0f); // Note that Z setting is discarded; use camera.zoom instead (see MoveCamera() below for example)
    camera = cameraNode.CreateComponent("Camera");
    camera.orthographic = true;
    camera.orthoSize = graphics.height * PIXEL_SIZE;
    camera.zoom = 1.2f * Min(graphics.width / 1280.0f, graphics.height / 800.0f); // Set zoom according to user's resolution to ensure full visibility (initial zoom (1.2) is set for full visibility at 1280x800 resolution)
    renderer.viewports[0] = Viewport(scene_, camera);
    renderer.defaultZone.fogColor = Color(0.1f, 0.1f, 0.1f); // Set background color for the scene

    // Create 4x3 grid
    for (uint i = 0; i<5; ++i)
    {
        Node@ edgeNode = scene_.CreateChild("VerticalEdge");
        RigidBody2D@ edgeBody = edgeNode.CreateComponent("RigidBody2D");
        if (dummyBody is null)
            dummyBody = edgeBody; // Mark first edge as dummy body (used by mouse pick)
        CollisionEdge2D@ edgeShape = edgeNode.CreateComponent("CollisionEdge2D");
        edgeShape.SetVertices(Vector2(i*2.5f -5.0f, -3.0f), Vector2(i*2.5f -5.0f, 3.0f));
        edgeShape.friction = 0.5f; // Set friction
    }

    for (uint j = 0; j<4; ++j)
    {
        Node@ edgeNode = scene_.CreateChild("HorizontalEdge");
        RigidBody2D@ edgeBody = edgeNode.CreateComponent("RigidBody2D");
        CollisionEdge2D@ edgeShape = edgeNode.CreateComponent("CollisionEdge2D");
        edgeShape.SetVertices(Vector2(-5.0f, j*2.0f -3.0f), Vector2(5.0f, j*2.0f -3.0f));
        edgeShape.friction = 0.5f; // Set friction
    }

    // Create a box (will be cloned later)
    Node@ box  = scene_.CreateChild("Box");
    box.position = Vector3(0.8f, -2.0f, 0.0f);
    StaticSprite2D@ boxSprite = box.CreateComponent("StaticSprite2D");
    boxSprite.sprite = cache.GetResource("Sprite2D", "Urho2D/Box.png");
    RigidBody2D@ boxBody = box.CreateComponent("RigidBody2D");
    boxBody.bodyType = BT_DYNAMIC;
    boxBody.linearDamping = 0.0f;
    boxBody.angularDamping  = 0.0f;
    CollisionBox2D@ shape = box.CreateComponent("CollisionBox2D"); // Create box shape
    shape.size = Vector2(0.32, 0.32); // Set size
    shape.density = 1.0f; // Set shape density (kilograms per meter squared)
    shape.friction = 0.5f; // Set friction
    shape.restitution = 0.1f; // Set restitution (slight bounce)

    // Create a ball (will be cloned later)
    Node@ ball  = scene_.CreateChild("Ball");
    ball.position = Vector3(1.8f, -2.0f, 0.0f);
    StaticSprite2D@ ballSprite = ball.CreateComponent("StaticSprite2D");
    ballSprite.sprite = cache.GetResource("Sprite2D", "Urho2D/Ball.png");
    RigidBody2D@ ballBody = ball.CreateComponent("RigidBody2D");
    ballBody.bodyType = BT_DYNAMIC;
    ballBody.linearDamping = 0.0f;
    ballBody.angularDamping  = 0.0f;
    CollisionCircle2D@ ballShape = ball.CreateComponent("CollisionCircle2D"); // Create circle shape
    ballShape.radius = 0.16f; // Set radius
    ballShape.density = 1.0f; // Set shape density (kilograms per meter squared)
    ballShape.friction = 0.5f; // Set friction
    ballShape.restitution = 0.6f; // Set restitution: make it bounce

    // Create a polygon
    Node@ polygon = scene_.CreateChild("Polygon");
    polygon.position = Vector3(1.6f, -2.0f, 0.0f);
    polygon.SetScale(0.7f);
    StaticSprite2D@ polygonSprite = polygon.CreateComponent("StaticSprite2D");
    polygonSprite.sprite = cache.GetResource("Sprite2D", "Urho2D/Aster.png");
    RigidBody2D@ polygonBody = polygon.CreateComponent("RigidBody2D");
    polygonBody.bodyType = BT_DYNAMIC;
    CollisionPolygon2D@ polygonShape = polygon.CreateComponent("CollisionPolygon2D");
    Array<Vector2> polygonVertices = {Vector2(-0.8f, -0.3f), Vector2(0.5f, -0.8f), Vector2(0.8f, -0.3f), Vector2(0.8f, 0.5f), Vector2(0.5f, 0.9f), Vector2(-0.5f, 0.7f)};
    polygonShape.SetVertices(polygonVertices);
    polygonShape.density = 1.0f; // Set shape density (kilograms per meter squared)
    polygonShape.friction = 0.3f; // Set friction
    polygonShape.restitution = 0.0f; // Set restitution (no bounce)

    // Create a ConstraintDistance2D
    CreateFlag("ConstraintDistance2D", -4.97f, 3.0f); // Display Text3D flag
    Node@ boxDistanceNode = box.Clone();
    Node@ ballDistanceNode = ball.Clone();
    RigidBody2D@ ballDistanceBody = ballDistanceNode.GetComponent("RigidBody2D");
    boxDistanceNode.position = Vector3(-4.5f, 2.0f, 0.0f);
    ballDistanceNode.position = Vector3(-3.0f, 2.0f, 0.0f);

    ConstraintDistance2D@ constraintDistance = boxDistanceNode.CreateComponent("ConstraintDistance2D"); // Apply ConstraintDistance2D to box
    constraintDistance.otherBody = ballDistanceBody; // Constrain ball to box
    constraintDistance.ownerBodyAnchor = boxDistanceNode.position2D;
    constraintDistance.otherBodyAnchor = ballDistanceNode.position2D;
    // Make the constraint soft (comment to make it rigid, which is its basic behavior)
    constraintDistance.frequencyHz = 4.0f;
    constraintDistance.dampingRatio = 0.5f;

    // Create a ConstraintFriction2D ********** Not functional. From Box2d samples it seems that 2 anchors are required, Urho2D only provides 1, needs investigation ***********
    CreateFlag("ConstraintFriction2D", 0.03f, 1.0f); // Display Text3D flag
    Node@ boxFrictionNode = box.Clone();
    Node@ ballFrictionNode = ball.Clone();
    boxFrictionNode.position = Vector3(0.5f, 0.0f, 0.0f);
    ballFrictionNode.position = Vector3(1.5f, 0.0f, 0.0f);

    ConstraintFriction2D@ constraintFriction = boxFrictionNode.CreateComponent("ConstraintFriction2D"); // Apply ConstraintDistance2D to box
    constraintFriction.otherBody = ballFrictionNode.GetComponent("RigidBody2D"); // Constraint ball to box
    //constraintFriction.ownerBodyAnchor = boxNode.position2D;
    //constraintFriction.otherBodyAnchor = ballNode.position2D;
    //constraintFriction.maxForce = 10.0f; // ballBody.mass * gravity
    //constraintDistance.maxTorque = 10.0f; // ballBody.mass * radius * gravity

    // Create a ConstraintGear2D
    CreateFlag("ConstraintGear2D", -4.97f, -1.0f); // Display Text3D flag
    Node@ baseNode = box.Clone();
    RigidBody2D@ tempBody = baseNode.GetComponent("RigidBody2D"); // Get body to make it static
    tempBody.bodyType = BT_STATIC;
    baseNode.position = Vector3(-3.7f, -2.5f, 0.0f);
    Node@ ball1Node = ball.Clone();
    ball1Node.position = Vector3(-4.5f, -2.0f, 0.0f);
    RigidBody2D@ ball1Body = ball1Node.GetComponent("RigidBody2D");
    Node@ ball2Node = ball.Clone();
    ball2Node.position = Vector3(-3.0f, -2.0f, 0.0f);
    RigidBody2D@ ball2Body = ball2Node.GetComponent("RigidBody2D");

    ConstraintRevolute2D@ gear1 = baseNode.CreateComponent("ConstraintRevolute2D"); // Apply constraint to baseBox
    gear1.otherBody = ball1Body; // Constrain ball1 to baseBox
    gear1.anchor = ball1Node.position2D;
    ConstraintRevolute2D@ gear2 = baseNode.CreateComponent("ConstraintRevolute2D"); // Apply constraint to baseBox
    gear2.otherBody = ball2Body; // Constrain ball2 to baseBox
    gear2.anchor = ball2Node.position2D;

    ConstraintGear2D@ constraintGear = ball1Node.CreateComponent("ConstraintGear2D"); // Apply constraint to ball1
    constraintGear.otherBody = ball2Body; // Constrain ball2 to ball1
    constraintGear.ownerConstraint = gear1;
    constraintGear.otherConstraint = gear2;
    constraintGear.ratio=1.0f;

    ball1Body.ApplyAngularImpulse(0.015f, true); // Animate

    // Create a vehicle from a compound of 2 ConstraintWheel2Ds
    CreateFlag("ConstraintWheel2Ds compound", -2.45f, -1.0f); // Display Text3D flag
    Node@ car = box.Clone();
    car.scale = Vector3(4.0f, 1.0f, 0.0f);
    car.position = Vector3(-1.2f, -2.3f, 0.0f);
    StaticSprite2D@ tempSprite = car.GetComponent("StaticSprite2D"); // Get car Sprite in order to draw it on top
    tempSprite.orderInLayer = 0; // Draw car on top of the wheels (set to -1 to draw below)
    Node@ ball1WheelNode = ball.Clone();
    ball1WheelNode.position = Vector3(-1.6f, -2.5f, 0.0f);
    Node@ ball2WheelNode = ball.Clone();
    ball2WheelNode.position = Vector3(-0.8f, -2.5f, 0.0f);

    ConstraintWheel2D@ wheel1 = car.CreateComponent("ConstraintWheel2D");
    wheel1.otherBody = ball1WheelNode.GetComponent("RigidBody2D");
    wheel1.anchor = ball1WheelNode.position2D;
    wheel1.axis = Vector2(0.0f, 1.0f);
    wheel1.maxMotorTorque = 20.0f;
    wheel1.frequencyHz = 4.0f;
    wheel1.dampingRatio = 0.4f;

    ConstraintWheel2D@ wheel2 = car.CreateComponent("ConstraintWheel2D");
    wheel2.otherBody = ball2WheelNode.GetComponent("RigidBody2D");
    wheel2.anchor = ball2WheelNode.position2D;
    wheel2.axis = Vector2(0.0f, 1.0f);
    wheel2.maxMotorTorque = 10.0f;
    wheel2.frequencyHz = 4.0f;
    wheel2.dampingRatio = 0.4f;

    // ConstraintMotor2D
    CreateFlag("ConstraintMotor2D", 2.53f, -1.0f); // Display Text3D flag
    Node@ boxMotorNode = box.Clone();
    tempBody = boxMotorNode.GetComponent("RigidBody2D"); // Get body to make it static
    tempBody.bodyType = BT_STATIC;
    Node@ ballMotorNode = ball.Clone();
    boxMotorNode.position = Vector3(3.8f, -2.1f, 0.0f);
    ballMotorNode.position = Vector3(3.8f, -1.5f, 0.0f);

    ConstraintMotor2D@ constraintMotor = boxMotorNode.CreateComponent("ConstraintMotor2D");
    constraintMotor.otherBody = ballMotorNode.GetComponent("RigidBody2D"); // Constrain ball to box
    constraintMotor.linearOffset = Vector2(0.0f, 0.8f); // Set ballNode position relative to boxNode position = (0,0)
    constraintMotor.angularOffset = 0.1f;
    constraintMotor.maxForce = 5.0f;
    constraintMotor.maxTorque = 10.0f;
    constraintMotor.correctionFactor = 1.0f;
    constraintMotor.collideConnected = true; // doesn't work

    // ConstraintMouse2D is demonstrated in HandleMouseButtonDown() function. It is used to "grasp" the sprites with the mouse.
    CreateFlag("ConstraintMouse2D", 0.03f, -1.0f); // Display Text3D flag

    // Create a ConstraintPrismatic2D
    CreateFlag("ConstraintPrismatic2D", 2.53f, 3.0f); // Display Text3D flag
    Node@ boxPrismaticNode = box.Clone();
    tempBody = boxPrismaticNode.GetComponent("RigidBody2D"); // Get body to make it static
    tempBody.bodyType = BT_STATIC;
    Node@ ballPrismaticNode = ball.Clone();
    boxPrismaticNode.position = Vector3(3.3f, 2.5f, 0.0f);
    ballPrismaticNode.position = Vector3(4.3f, 2.0f, 0.0f);

    ConstraintPrismatic2D@ constraintPrismatic = boxPrismaticNode.CreateComponent("ConstraintPrismatic2D");
    constraintPrismatic.otherBody = ballPrismaticNode.GetComponent("RigidBody2D"); // Constrain ball to box
    constraintPrismatic.axis = Vector2(1.0f, 1.0f); // Slide from [0,0] to [1,1]
    constraintPrismatic.anchor = Vector2(4.0f, 2.0f);
    constraintPrismatic.lowerTranslation = -1.0f;
    constraintPrismatic.upperTranslation = 0.5f;
    constraintPrismatic.enableLimit = true;
    constraintPrismatic.maxMotorForce = 1.0f;
    constraintPrismatic.motorSpeed = 0.0f;

    // ConstraintPulley2D
    CreateFlag("ConstraintPulley2D", 0.03f, 3.0f); // Display Text3D flag
    Node@ boxPulleyNode = box.Clone();
    Node@ ballPulleyNode = ball.Clone();
    boxPulleyNode.position = Vector3(0.5f, 2.0f, 0.0f);
    ballPulleyNode.position = Vector3(2.0f, 2.0f, 0.0f);

    ConstraintPulley2D@ constraintPulley = boxPulleyNode.CreateComponent("ConstraintPulley2D"); // Apply constraint to box
    constraintPulley.otherBody = ballPulleyNode.GetComponent("RigidBody2D"); // Constrain ball to box
    constraintPulley.ownerBodyAnchor = boxPulleyNode.position2D;
    constraintPulley.otherBodyAnchor = ballPulleyNode.position2D;
    constraintPulley.ownerBodyGroundAnchor = boxPulleyNode.position2D + Vector2(0.0f, 1.0f);
    constraintPulley.otherBodyGroundAnchor = ballPulleyNode.position2D + Vector2(0.0f, 1.0f);
    constraintPulley.ratio = 1.0; // Weight ratio between ownerBody and otherBody

    // Create a ConstraintRevolute2D
    CreateFlag("ConstraintRevolute2D", -2.45f, 3.0f); // Display Text3D flag
    Node@ boxRevoluteNode = box.Clone();
    tempBody = boxRevoluteNode.GetComponent("RigidBody2D"); // Get body to make it static
    tempBody.bodyType = BT_STATIC;
    Node@ ballRevoluteNode = ball.Clone();
    boxRevoluteNode.position = Vector3(-2.0f, 1.5f, 0.0f);
    ballRevoluteNode.position = Vector3(-1.0f, 2.0f, 0.0f);

    ConstraintRevolute2D@ constraintRevolute = boxRevoluteNode.CreateComponent("ConstraintRevolute2D"); // Apply constraint to box
    constraintRevolute.otherBody = ballRevoluteNode.GetComponent("RigidBody2D"); // Constrain ball to box
    constraintRevolute.anchor = Vector2(-1.0f, 1.5f);
    constraintRevolute.lowerAngle = -1.0f; // In radians
    constraintRevolute.upperAngle = 0.5f; // In radians
    constraintRevolute.enableLimit = true;
    constraintRevolute.maxMotorTorque = 10.0f;
    constraintRevolute.motorSpeed = 0.0f;
    constraintRevolute.enableMotor = true;

    // Create a ConstraintRope2D
    CreateFlag("ConstraintRope2D", -4.97f, 1.0f); // Display Text3D flag
    Node@ boxRopeNode = box.Clone();
    tempBody = boxRopeNode.GetComponent("RigidBody2D");
    tempBody.bodyType = BT_STATIC;
    Node@ ballRopeNode = ball.Clone();
    boxRopeNode.position = Vector3(-3.7f, 0.7f, 0.0f);
    ballRopeNode.position = Vector3(-4.5f, 0.0f, 0.0f);

    ConstraintRope2D@ constraintRope = boxRopeNode.CreateComponent("ConstraintRope2D");
    constraintRope.otherBody = ballRopeNode.GetComponent("RigidBody2D"); // Constrain ball to box
    constraintRope.ownerBodyAnchor = Vector2(0.0f, -0.5f); // Offset from box (OwnerBody) : the rope is rigid from OwnerBody center to this ownerBodyAnchor
    constraintRope.maxLength = 0.9f; // Rope length
    constraintRope.collideConnected = true;

    // Create a ConstraintWeld2D
    CreateFlag("ConstraintWeld2D", -2.45f, 1.0f); // Display Text3D flag
    Node@ boxWeldNode = box.Clone();
    Node@ ballWeldNode = ball.Clone();
    boxWeldNode.position = Vector3(-0.5f, 0.0f, 0.0f);
    ballWeldNode.position = Vector3(-2.0f, 0.0f, 0.0f);

    ConstraintWeld2D@ constraintWeld = boxWeldNode.CreateComponent("ConstraintWeld2D");
    constraintWeld.otherBody = ballWeldNode.GetComponent("RigidBody2D"); // Constrain ball to box
    constraintWeld.anchor = boxWeldNode.position2D;
    constraintWeld.frequencyHz = 4.0f;
    constraintWeld.dampingRatio = 0.5f;

    // Create a ConstraintWheel2D
    CreateFlag("ConstraintWheel2D",  2.53f, 1.0f); // Display Text3D flag
    Node@ boxWheelNode = box.Clone();
    Node@ ballWheelNode = ball.Clone();
    boxWheelNode.position = Vector3(3.8f, 0.0f, 0.0f);
    ballWheelNode.position = Vector3(3.8f, 0.9f, 0.0f);

    ConstraintWheel2D@ constraintWheel = boxWheelNode.CreateComponent("ConstraintWheel2D");
    constraintWheel.otherBody = ballWheelNode.GetComponent("RigidBody2D"); // Constrain ball to box
    constraintWheel.anchor = ballWheelNode.position2D;
    constraintWheel.axis = Vector2(0.0f, 1.0f);
    constraintWheel.enableMotor = true;
    constraintWheel.maxMotorTorque = 1.0f;
    constraintWheel.motorSpeed = 0.0f;
    constraintWheel.frequencyHz = 4.0f;
    constraintWheel.dampingRatio = 0.5f;
    constraintWheel.collideConnected = true; // doesn't work
}

void CreateFlag(const String&in text, float x, float y) // Used to create Tex3D flags
{
    Node@ flagNode = scene_.CreateChild("Flag");
    flagNode.position = Vector3(x, y, 0.0f);
    Text3D@ flag3D = flagNode.CreateComponent("Text3D"); // We use Text3D in order to make the text affected by zoom (so that it sticks to 2D)
    flag3D.text = text;
    flag3D.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text = "Use WASD keys and mouse to move, Use PageUp PageDown to zoom.\n Space to toggle debug geometry and joints - F5 to save the scene.";
    instructionText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);
    instructionText.textAlignment = HA_CENTER; // Center rows in relation to each other

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;

    instructionText.SetPosition(0.0f, ui.root.height / 4);
}


void MoveCamera(float timeStep)
{
    if (ui.focusElement !is null) return; // Do not move if the UI has a focused element (the console)

    uint MOVE_SPEED = 4; // Movement speed as world units per second

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input.keyDown['W']) cameraNode.Translate(Vector3(0.0f, 1.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['S']) cameraNode.Translate(Vector3(0.0f, -1.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['A']) cameraNode.Translate(Vector3(-1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['D']) cameraNode.Translate(Vector3(1.0f, 0.0f, 0.0f) * MOVE_SPEED * timeStep);

    if (input.keyDown[KEY_PAGEUP]) camera.zoom = camera.zoom * 1.01f; // Zoom In
    if (input.keyDown[KEY_PAGEDOWN]) camera.zoom = camera.zoom * 0.99f; // Zoom Out
}

void SubscribeToEvents()
{
    SubscribeToEvent("Update", "HandleUpdate");
    SubscribeToEvent("PostRenderUpdate", "HandlePostRenderUpdate");
    SubscribeToEvent("MouseButtonDown", "HandleMouseButtonDown");

    if (touchEnabled)
        SubscribeToEvent("TouchBegin", "HandleTouchBegin3");

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent("SceneUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    float timeStep = eventData["TimeStep"].GetFloat();
    MoveCamera(timeStep); // Move the camera according to frame's time step
    if (input.keyPress[KEY_SPACE]) drawDebug = !drawDebug; // Toggle debug geometry with space
    if (input.keyPress[KEY_F5]) // Save scene
    {
        File saveFile(fileSystem.programDir + "Data/Scenes/Constraints.xml", FILE_WRITE);
        scene_.SaveXML(saveFile);
    }
}

void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    PhysicsWorld2D@ physicsWorld = scene_.GetComponent("PhysicsWorld2D");
    if (drawDebug) physicsWorld.DrawDebugGeometry();
}

void HandleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    PhysicsWorld2D@ physicsWorld = scene_.GetComponent("PhysicsWorld2D");
    RigidBody2D@ rigidBody = physicsWorld.GetRigidBody(input.mousePosition.x, input.mousePosition.y, M_MAX_UNSIGNED); // Raycast for RigidBody2Ds to pick
    if (rigidBody !is null)
    {
        pickedNode = rigidBody.node;
        StaticSprite2D@ staticSprite = pickedNode.GetComponent("StaticSprite2D");
        staticSprite.color = Color(1.0f, 0.0f, 0.0f, 1.0f); // Temporary modify color of the picked sprite

        // Create a ConstraintMouse2D - Temporary apply this constraint to the pickedNode to allow grasping and moving with the mouse
        ConstraintMouse2D@ constraintMouse = pickedNode.CreateComponent("ConstraintMouse2D");
        constraintMouse.target = GetMousePositionXY();
        constraintMouse.maxForce = 1000 * rigidBody.mass;
        constraintMouse.collideConnected = true;
        constraintMouse.otherBody = dummyBody;  // Use dummy body instead of rigidBody. It's better to create a dummy body automatically in ConstraintMouse2D
        constraintMouse.dampingRatio = 0.0f;
    }
    SubscribeToEvent("MouseMove", "HandleMouseMove");
    SubscribeToEvent("MouseButtonUp", "HandleMouseButtonUp");
}

void HandleMouseButtonUp(StringHash eventType, VariantMap& eventData)
{
    if (pickedNode !is null)
    {
        StaticSprite2D@ staticSprite = pickedNode.GetComponent("StaticSprite2D");
        staticSprite.color = Color(1.0f, 1.0f, 1.0f, 1.0f); // Restore picked sprite color

        pickedNode.RemoveComponent("ConstraintMouse2D"); // Remove temporary constraint
        pickedNode = null;
    }
    UnsubscribeFromEvent("MouseMove");
    UnsubscribeFromEvent("MouseButtonUp");
}

Vector2 GetMousePositionXY()
{
    Vector3 screenPoint = Vector3(float(input.mousePosition.x) / graphics.width, float(input.mousePosition.y) / graphics.height, 0.0f);
    Vector3 worldPoint = camera.ScreenToWorldPoint(screenPoint);
    return Vector2(worldPoint.x, worldPoint.y);
}

void HandleMouseMove(StringHash eventType, VariantMap& eventData)
{
    if (pickedNode !is null)
    {
        ConstraintMouse2D@ constraintMouse = pickedNode.GetComponent("ConstraintMouse2D");
        constraintMouse.target = GetMousePositionXY();
    }
}

void HandleTouchBegin3(StringHash eventType, VariantMap& eventData)
{
    PhysicsWorld2D@ physicsWorld = scene_.GetComponent("PhysicsWorld2D");
    RigidBody2D@ rigidBody = physicsWorld.GetRigidBody(eventData["X"].GetInt(), eventData["Y"].GetInt(), M_MAX_UNSIGNED); // Raycast for RigidBody2Ds to pick
    if (rigidBody !is null)
    {
        pickedNode = rigidBody.node;
        StaticSprite2D@ staticSprite = pickedNode.GetComponent("StaticSprite2D");
        staticSprite.color = Color(1.0f, 0.0f, 0.0f, 1.0f); // Temporary modify color of the picked sprite
        RigidBody2D@ rigidBody = pickedNode.GetComponent("RigidBody2D");

        // Create a ConstraintMouse2D - Temporary apply this constraint to the pickedNode to allow grasping and moving with touch
        ConstraintMouse2D@ constraintMouse = pickedNode.CreateComponent("ConstraintMouse2D");
        Vector3 pos = camera.ScreenToWorldPoint(Vector3(float(eventData["X"].GetInt()) / graphics.width, float(eventData["Y"].GetInt()) / graphics.height, 0.0f));
        constraintMouse.target = Vector2(pos.x, pos.y);
        constraintMouse.maxForce = 1000 * rigidBody.mass;
        constraintMouse.collideConnected = true;
        constraintMouse.otherBody = dummyBody;  // Use dummy body instead of rigidBody. It's better to create a dummy body automatically in ConstraintMouse2D
        constraintMouse.dampingRatio = 0;
    }
    SubscribeToEvent("TouchMove", "HandleTouchMove3");
    SubscribeToEvent("TouchEnd", "HandleTouchEnd3");
}

void HandleTouchMove3(StringHash eventType, VariantMap& eventData)
{
    if (pickedNode !is null)
    {
        ConstraintMouse2D@ constraintMouse = pickedNode.GetComponent("ConstraintMouse2D");
        Vector3 pos = camera.ScreenToWorldPoint(Vector3(float(eventData["X"].GetInt()) / graphics.width, float(eventData["Y"].GetInt()) / graphics.height, 0.0f));
        constraintMouse.target = Vector2(pos.x, pos.y);
    }
}

void HandleTouchEnd3(StringHash eventType, VariantMap& eventData)
{
    if (pickedNode !is null)
    {
        StaticSprite2D@ staticSprite = pickedNode.GetComponent("StaticSprite2D");
        staticSprite.color = Color(1.0f, 1.0f, 1.0f, 1.0f); // Restore picked sprite color

        pickedNode.RemoveComponent("ConstraintMouse2D"); // Remove temporary constraint
        pickedNode = null;
    }
    UnsubscribeFromEvent("TouchMove");
    UnsubscribeFromEvent("TouchEnd");
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom In</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"PAGEUP\" />" +
        "        </element>" +
        "    </add>" +
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />" +
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom Out</replace>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">" +
        "        <element type=\"Text\">" +
        "            <attribute name=\"Name\" value=\"KeyBinding\" />" +
        "            <attribute name=\"Text\" value=\"PAGEDOWN\" />" +
        "        </element>" +
        "    </add>" +
        "</patch>";
