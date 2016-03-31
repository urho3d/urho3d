// Moving sprites example.
// This sample demonstrates:
//     - Adding Sprite elements to the UI
//     - Storing custom data (sprite velocity) inside UI elements
//     - Handling frame update events in which the sprites are moved

#include "Scripts/Utilities/Sample.as"

// Number of sprites to draw
const uint NUM_SPRITES = 100;

Array<Sprite@> sprites;

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Create the sprites to the user interface
    CreateSprites();

    // Hook up to the frame update events
    SubscribeToEvents();
}

void CreateSprites()
{
    // Get rendering window size as floats
    float width = graphics.width;
    float height = graphics.height;

    // Get the Urho3D fish texture
    Texture2D@ decalTex = cache.GetResource("Texture2D", "Textures/UrhoDecal.dds");

    for (uint i = 0; i < NUM_SPRITES; ++i)
    {
        // Create a new sprite, set it to use the texture
        Sprite@ sprite = Sprite();
        sprite.texture = decalTex;

        // The UI root element is as big as the rendering window, set random position within it
        sprite.position = Vector2(Random() * width, Random() * height);

        // Set sprite size & hotspot in its center
        sprite.size = IntVector2(128, 128);
        sprite.hotSpot = IntVector2(64, 64);

        // Set random rotation in degrees and random scale
        sprite.rotation = Random() * 360.0f;
        sprite.SetScale(Random(1.0f) + 0.5f);

        // Set random color and additive blending mode
        sprite.color = Color(Random(0.5f) + 0.5f, Random(0.5f) + 0.5f, Random(0.5f) + 0.5f);
        sprite.blendMode = BLEND_ADD;

        // Add as a child of the root UI element
        ui.root.AddChild(sprite);

        // Store sprite's velocity as a custom variable
        sprite.vars["Velocity"] = Vector2(Random(200.0f) - 100.0f, Random(200.0f) - 100.0f);

        // Store sprites to our own container for easy movement update iteration
        sprites.Push(sprite);
    }
}

void MoveSprites(float timeStep)
{
    float width = graphics.width;
    float height = graphics.height;

    // Go through all sprites
    for (uint i = 0; i < sprites.length; ++i)
    {
        Sprite@ sprite = sprites[i];

        // Rotate
        float newRot = sprite.rotation + timeStep * 30.0f;
        sprite.rotation = newRot;

        // Move, wrap around rendering window edges
        Vector2 newPos = sprite.position + sprite.vars["Velocity"].GetVector2() * timeStep;
        if (newPos.x < 0.0f)
            newPos.x += width;
        if (newPos.x >= width)
            newPos.x -= width;
        if (newPos.y < 0.0f)
            newPos.y += height;
        if (newPos.y >= height)
            newPos.y -= height;
        sprite.position = newPos;
    }
}

void SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent("Update", "HandleUpdate");
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float timeStep = eventData["TimeStep"].GetFloat();

    // Move sprites, scale movement with time step
    MoveSprites(timeStep);
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
