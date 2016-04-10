// Dynamic geometry example.
// This sample demonstrates:
//     - Cloning a Model resource
//     - Modifying the vertex buffer data of the cloned models at runtime to efficiently animate them
//     - Creating a Model resource and its buffer data from scratch

#include "Scripts/Utilities/Sample.as"

bool animate = true;
float animTime = 0.0;
VectorBuffer originalVertexData;
Array<VertexBuffer@> animatingBuffers;
Array<Vector3> originalVertices;
Array<uint> vertexDuplicates;

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

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_RELATIVE);

    // Hook up to the frame update events
    SubscribeToEvents();
}

void CreateScene()
{
    scene_ = Scene();

    // Create the Octree component to the scene so that drawable objects can be rendered. Use default volume
    // (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_.CreateComponent("Octree");

    // Create a Zone for ambient light & fog control
    Node@ zoneNode = scene_.CreateChild("Zone");
    Zone@ zone = zoneNode.CreateComponent("Zone");
    zone.boundingBox = BoundingBox(-1000.0, 1000.0);
    zone.fogColor = Color(0.2, 0.2, 0.2);
    zone.fogStart = 200.0;
    zone.fogEnd = 300.0;

    // Create a directional light
    Node@ lightNode = scene_.CreateChild("DirectionalLight");
    lightNode.direction = Vector3(-0.6, -1.0, -0.8); // The direction vector does not need to be normalized
    Light@ light = lightNode.CreateComponent("Light");
    light.lightType = LIGHT_DIRECTIONAL;
    light.color = Color(0.4, 1.0, 0.4);
    light.specularIntensity = 1.5;

    // Get the original model and its unmodified vertices, which are used as source data for the animation
    Model@ originalModel = cache.GetResource("Model", "Models/Box.mdl");
    if (originalModel is null)
    {
        Print("Model not found, cannot initialize example scene");
        return;
    }
    // Get the vertex buffer from the first geometry's first LOD level
    VertexBuffer@ buffer = originalModel.GetGeometry(0, 0).vertexBuffers[0];
    originalVertexData = buffer.GetData();
    uint numVertices = buffer.vertexCount;
    uint vertexSize = buffer.vertexSize;
    // Copy the original vertex positions
    for (uint i = 0; i < numVertices; ++i)
    {
        originalVertexData.Seek(i * vertexSize);
        originalVertices.Push(originalVertexData.ReadVector3());
    }

    // Detect duplicate vertices to allow seamless animation
    vertexDuplicates.Resize(originalVertices.length);
    for (uint i = 0; i < originalVertices.length; ++i)
    {
        vertexDuplicates[i] = i; // Assume not a duplicate
        for (uint j = 0; j < i; ++j)
        {
            if (originalVertices[i].Equals(originalVertices[j]))
            {
                vertexDuplicates[i] = j;
                break;
            }
        }
    }

    // Create StaticModels in the scene. Clone the model for each so that we can modify the vertex data individually
    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            Node@ node = scene_.CreateChild("Object");
            node.position = Vector3(x * 2.0, 0.0, y * 2.0);
            StaticModel@ object = node.CreateComponent("StaticModel");
            Model@ cloneModel = originalModel.Clone();
            object.model = cloneModel;
            // Store the cloned vertex buffer that we will modify when animating
            animatingBuffers.Push(cloneModel.GetGeometry(0, 0).vertexBuffers[0]);
        }
    }

    // Finally create one model (pyramid shape) and a StaticModel to display it from scratch
    // Note: there are duplicated vertices to enable face normals. We will calculate normals programmatically
    {
        const uint numVertices = 18;

        float[] vertexData = {
            // Position          Normal
            0.0, 0.5, 0.0,       0.0, 0.0, 0.0,
            0.5, -0.5, 0.5,      0.0, 0.0, 0.0,
            0.5, -0.5, -0.5,     0.0, 0.0, 0.0,

            0.0, 0.5, 0.0,       0.0, 0.0, 0.0,
            -0.5, -0.5, 0.5,     0.0, 0.0, 0.0,
            0.5, -0.5, 0.5,      0.0, 0.0, 0.0,

            0.0, 0.5, 0.0,       0.0, 0.0, 0.0,
            -0.5, -0.5, -0.5,    0.0, 0.0, 0.0,
            -0.5, -0.5, 0.5,     0.0, 0.0, 0.0,

            0.0, 0.5, 0.0,       0.0, 0.0, 0.0,
            0.5, -0.5, -0.5,     0.0, 0.0, 0.0,
            -0.5, -0.5, -0.5,    0.0, 0.0, 0.0,

            0.5, -0.5, -0.5,     0.0, 0.0, 0.0,
            0.5, -0.5, 0.5,      0.0, 0.0, 0.0,
            -0.5, -0.5, 0.5,     0.0, 0.0, 0.0,

            0.5, -0.5, -0.5,     0.0, 0.0, 0.0,
            -0.5, -0.5, 0.5,     0.0, 0.0, 0.0,
            -0.5, -0.5, -0.5,    0.0, 0.0, 0.0
        };

        const uint16[] indexData = {
            0, 1, 2,
            3, 4, 5,
            6, 7, 8,
            9, 10, 11,
            12, 13, 14,
            15, 16, 17
        };

        // Calculate face normals now
        for (uint i = 0; i < numVertices; i += 3)
        {
            Vector3 v1(vertexData[6 * i], vertexData[6 * i + 1], vertexData[6 * i + 2]);
            Vector3 v2(vertexData[6 * i + 6], vertexData[6 * i + 7], vertexData[6 * i + 8]);
            Vector3 v3(vertexData[6 * i + 12], vertexData[6 * i + 13], vertexData[6 * i + 14]);

            Vector3 edge1 = v1 - v2;
            Vector3 edge2 = v1 - v3;
            Vector3 normal = edge1.CrossProduct(edge2).Normalized();
            vertexData[6 * i + 3] = vertexData[6 * i + 9] = vertexData[6 * i + 15] = normal.x;
            vertexData[6 * i + 4] = vertexData[6 * i + 10] = vertexData[6 * i + 16] = normal.y;
            vertexData[6 * i + 5] = vertexData[6 * i + 11] = vertexData[6 * i + 17] = normal.z;
        }

        Model@ fromScratchModel = Model();
        VertexBuffer@ vb = VertexBuffer();
        IndexBuffer@ ib = IndexBuffer();
        Geometry@ geom = Geometry();

        // Shadowed buffer needed for raycasts to work, and so that data can be automatically restored on device loss
        vb.shadowed = true;
        // We could use the "legacy" element bitmask to define elements for more compact code, but let's demonstrate
        // defining the vertex elements explicitly to allow any element types and order
        Array<VertexElement> elements;
        elements.Push(VertexElement(TYPE_VECTOR3, SEM_POSITION));
        elements.Push(VertexElement(TYPE_VECTOR3, SEM_NORMAL));
        vb.SetSize(numVertices, elements);
        VectorBuffer temp;
        for (uint i = 0; i < numVertices * 6; ++i)
            temp.WriteFloat(vertexData[i]);
        vb.SetData(temp);

        ib.shadowed = true;
        ib.SetSize(numVertices, false);
        temp.Clear();
        for (uint i = 0; i < numVertices; ++i)
            temp.WriteUShort(indexData[i]);
        ib.SetData(temp);

        geom.SetVertexBuffer(0, vb);
        geom.SetIndexBuffer(ib);
        geom.SetDrawRange(TRIANGLE_LIST, 0, numVertices);

        fromScratchModel.numGeometries = 1;
        fromScratchModel.SetGeometry(0, 0, geom);
        fromScratchModel.boundingBox = BoundingBox(Vector3(-0.5, -0.5, -0.5), Vector3(0.5, 0.5, 0.5));

        Node@ node = scene_.CreateChild("FromScratchObject");
        node.position = Vector3(0.0, 3.0, 0.0);
        StaticModel@ object = node.CreateComponent("StaticModel");
        object.model = fromScratchModel;
    }

    // Create the camera
    cameraNode = Node("Camera");
    cameraNode.position = Vector3(0.0, 2.0, -20.0);
    Camera@ camera = cameraNode.CreateComponent("Camera");
    camera.farClip = 300.0f;
}

void CreateInstructions()
{
    // Construct new Text object, set string to display and font to use
    Text@ instructionText = ui.root.CreateChild("Text");
    instructionText.text =
        "Use WASD keys and mouse/touch to move\n"
        "Space to toggle animation";
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
    pitch = Clamp(pitch, -90.0, 90.0f);

    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode.rotation = Quaternion(pitch, yaw, 0.0f);

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input.keyDown['W'])
        cameraNode.Translate(Vector3(0.0, 0.0, 1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['S'])
        cameraNode.Translate(Vector3(0.0, 0.0, -1.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['A'])
        cameraNode.Translate(Vector3(-1.0, 0.0, 0.0f) * MOVE_SPEED * timeStep);
    if (input.keyDown['D'])
        cameraNode.Translate(Vector3(1.0, 0.0, 0.0f) * MOVE_SPEED * timeStep);
}

void AnimateObjects(float timeStep)
{
    animTime += timeStep * 100.0;

    // Repeat for each of the cloned vertex buffers
    for (uint i = 0; i < animatingBuffers.length; ++i)
    {
        float startPhase = animTime + i * 30.0;
        VertexBuffer@ buffer = animatingBuffers[i];

        // Need to prepare a VectorBuffer with all data (positions, normals, uvs...)
        VectorBuffer newData;
        uint numVertices = buffer.vertexCount;
        uint vertexSize = buffer.vertexSize;
        for (uint j = 0; j < numVertices; ++j)
        {
            // If there are duplicate vertices, animate them in phase of the original
            float phase = startPhase + vertexDuplicates[j] * 10.0f;
            Vector3 src = originalVertices[j];
            Vector3 dest;
            dest.x = src.x * (1.0 + 0.1 * Sin(phase));
            dest.y = src.y * (1.0 + 0.1 * Sin(phase + 60.0));
            dest.z = src.z * (1.0 + 0.1 * Sin(phase + 120.0));

            // Write position
            newData.WriteVector3(dest);
            // Copy other vertex elements
            originalVertexData.Seek(j * vertexSize + 12); // Seek past the vertex position
            for (uint k = 12; k < vertexSize; k += 4)
                newData.WriteFloat(originalVertexData.ReadFloat());
        }

        buffer.SetData(newData);
    }
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Toggle animation with space
    if (input.keyPress[KEY_SPACE])
        animate = !animate;

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);

    // Animate objects' vertex data if enabled
    if (animate)
        AnimateObjects(timeStep);
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>"
        "    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />"
        "    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Animation</replace>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">"
        "        <element type=\"Text\">"
        "            <attribute name=\"Name\" value=\"KeyBinding\" />"
        "            <attribute name=\"Text\" value=\"SPACE\" />"
        "        </element>"
        "    </add>"
        "</patch>";
