// Convenient functions for Urho2D samples:
//    - Generate collision shapes from a tmx file objects
//    - Create Spriter Imp character
//    - Handle camera zoom using PageUp, PageDown and MouseWheel
//    - Create UI instructions
//    - Set global variables
//    - Set XML patch instructions for screen joystick

float CAMERA_MIN_DIST = 0.1f;
float CAMERA_MAX_DIST = 6.0f;

const float MOVE_SPEED = 23.0f; // Movement speed as world units per second
const float MOVE_SPEED_X = 1.5f; // Movement speed as world units per second
float MOVE_SPEED_SCALE = 1.0f; // Scaling factor based on tiles' aspect ratio

float zoom = 2.0f; // Speed is scaled according to zoom
Node@ character2DNode;


void CreateCollisionShapesFromTMXObjects(Node@ tileMapNode, TileMapLayer2D@ tileMapLayer, TileMapInfo2D@ info)
{
    // Create rigid body to the root node
    RigidBody2D@ body = tileMapNode.CreateComponent("RigidBody2D");
    body.bodyType = BT_STATIC;

    // Generate physics collision shapes and rigid bodies from the tmx file's objects located in "Physics" layer
    for (uint i = 0; i < tileMapLayer.numObjects; ++i)
    {
        TileMapObject2D@ tileMapObject = tileMapLayer.GetObject(i); // Get physics objects

        // Create collision shape from tmx object
        switch (tileMapObject.objectType)
        {
            case OT_RECTANGLE:
                CreateRectangleShape(tileMapNode, tileMapObject, tileMapObject.size, info);
                continue;
            case OT_ELLIPSE:
                CreateCircleShape(tileMapNode, tileMapObject, tileMapObject.size.x / 2, info); // Ellipse is built as a Circle shape as it doesn't exist in Box2D
                continue;
            case OT_POLYGON:
                CreatePolygonShape(tileMapNode, tileMapObject);
                continue;
            case OT_POLYLINE:
                CreatePolyLineShape(tileMapNode, tileMapObject);
                continue;
            default:
                continue;
        }
    }
}

CollisionBox2D@ CreateRectangleShape(Node@ node, TileMapObject2D@ object, Vector2 size, TileMapInfo2D@ info)
{
    CollisionBox2D@ shape = node.CreateComponent("CollisionBox2D");
    shape.size = size;
    if (info.orientation == O_ORTHOGONAL)
        shape.center = object.position + size / 2;
    else
    {
        shape.center = object.position + Vector2(info.tileWidth / 2, 0.0f);
        shape.angle = 45.0f; // If our tile map is isometric then shape is losange
    }
    shape.friction = 0.8f;
    if (object.HasProperty("Friction"))
        shape.friction = object.GetProperty("Friction").ToFloat();
    return shape;
}

CollisionCircle2D@ CreateCircleShape(Node@ node, TileMapObject2D@ object, float radius, TileMapInfo2D@ info)
{
    CollisionCircle2D@ shape = node.CreateComponent("CollisionCircle2D");
    Vector2 size = object.size;
    shape.radius = radius;
    if (info.orientation == O_ORTHOGONAL)
        shape.center = object.position + size / 2;
    else
    {
        shape.center = object.position + Vector2(info.tileWidth / 2, 0.0f);
    }
    shape.friction = 0.8f;
    if (object.HasProperty("Friction"))
        shape.friction = object.GetProperty("Friction").ToFloat();
    return shape;
}

CollisionPolygon2D@ CreatePolygonShape(Node@ node, TileMapObject2D@ object)
{
    CollisionPolygon2D@ shape = node.CreateComponent("CollisionPolygon2D");
    uint numVertices = object.numPoints;
    shape.vertexCount = numVertices;
    for (uint i = 0; i < numVertices; ++i)
        shape.SetVertex(i, object.GetPoint(i));
    shape.friction = 0.8f;
    if (object.HasProperty("Friction"))
        shape.friction = object.GetProperty("Friction").ToFloat();
    return shape;
}

CollisionChain2D@ CreatePolyLineShape(Node@ node, TileMapObject2D@ object)
{
    CollisionChain2D@ shape = node.CreateComponent("CollisionChain2D");
    uint numVertices = object.numPoints;
    shape.vertexCount = numVertices;
    for (uint i = 0; i < numVertices; ++i)
        shape.SetVertex(i, object.GetPoint(i));
    shape.friction = 0.8f;
    if (object.HasProperty("Friction"))
        shape.friction = object.GetProperty("Friction").ToFloat();
    return shape;
}

void CreateCharacter(TileMapInfo2D@ info, bool createObject, float friction, Vector3 position)
{
    character2DNode = scene_.CreateChild("Imp");
    character2DNode.position = position;
    character2DNode.SetScale(0.2f);
    AnimatedSprite2D@ animatedSprite = character2DNode.CreateComponent("AnimatedSprite2D");
    animatedSprite.SetAnimation(cache.GetResource("AnimationSet2D", "Urho2D/imp/imp.scml"), "idle"); // Get scml file and Play "idle" anim
    animatedSprite.layer = 1; // Put character over tile map
    RigidBody2D@ characterBody = character2DNode.CreateComponent("RigidBody2D");
    characterBody.bodyType = BT_DYNAMIC;
    characterBody.allowSleep = false;
    CollisionCircle2D@ shape = character2DNode.CreateComponent("CollisionCircle2D");
    shape.radius = 1.2f; // Set shape size
    shape.friction = friction; // Set friction
    shape.restitution = 0.1f; // Bounce
    if (createObject)
        character2DNode.CreateScriptObject(scriptFile, "Character2D"); // Create a ScriptObject to handle character behavior

    // Scale character's speed on the Y axis according to tiles' aspect ratio
    MOVE_SPEED_SCALE = info.tileHeight / info.tileWidth;
}

void Zoom(Camera@ camera)
{
    if (input.mouseMoveWheel != 0)
        camera.zoom = Clamp(camera.zoom + input.mouseMoveWheel * 0.1, CAMERA_MIN_DIST, CAMERA_MAX_DIST);

    if (input.keyDown[KEY_PAGEUP])
    {
        zoom = Clamp(camera.zoom * 1.01f, CAMERA_MIN_DIST, CAMERA_MAX_DIST);
        camera.zoom = zoom;
    }

    if (input.keyDown[KEY_PAGEDOWN])
    {
        zoom = Clamp(camera.zoom * 0.99f, CAMERA_MIN_DIST, CAMERA_MAX_DIST);
        camera.zoom = zoom;
    }
}

// Mover script object class
//class Mover : ScriptObject
//{
    //Vector2 startPos = Vector2(0.0f, 0.0f);
    //Vector2 endPos = Vector2(0.0f, 0.0f);
    //float speed = 0.5f;

    //void Update(float timeStep)
    //{
        //Vector2 target = Vector2(0.0f, 0.0f);
        //// Set new target
        //if (speed > 0.0f)
            //target = endPos;
        //else
            //target = startPos;
        //// Set direction and move to target
        //Vector2 dir = target - node.position2D;
        //Vector2 dirNormal = dir.Normalized();
        //node.Translate(Vector3(dirNormal.x, dirNormal.y, 0.0f) * Abs(speed) * timeStep);
        //// Check for reversal
        //if (Abs(dir.length) < 0.1f)
            //speed = -speed;
    //}
//}

void CreateInstructions(String text)
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text = text;
    instructionText.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 15);
    instructionText.textAlignment = HA_CENTER; // Center rows in relation to each other

    // Position the text relative to the screen center
    instructionText.horizontalAlignment = HA_CENTER;
    instructionText.verticalAlignment = VA_CENTER;
    instructionText.SetPosition(0, ui.root.height / 4);
}

Vector2[] CreatePathFromPoints(TileMapObject2D@ object)
{
    Array<Vector2> path;
    for (uint i=0; i < object.numPoints; ++i)
        path.Push(object.GetPoint(i));
    return path;
}

// Mover script object class
class Mover : ScriptObject
{
    float speed = 0.5f;
    Array<Vector2> path;
    int currentPathID = 1;

    void Update(float timeStep)
    {
        // Set direction and move to target
        Vector2 dir = path[currentPathID] - node.position2D;
        Vector2 dirNormal = dir.Normalized();
        node.Translate(Vector3(dirNormal.x, dirNormal.y, 0.0f) * Abs(speed) * timeStep);

        // Check for new target to reach
        if (Abs(dir.length) < 0.1f)
        {
            if (speed > 0.0f)
            {
                if (currentPathID + 1 < path.length)
                    currentPathID = currentPathID + 1;
                else
                {
                    currentPathID = currentPathID - 1;
                    speed = -speed;
                }
            }
            else
            {
                if (currentPathID - 1 >= 0)
                    currentPathID = currentPathID - 1;
                else
                {
                    currentPathID = 1;
                    speed = -speed;
                }
            }
        }
    }
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
