//
// Copyright (c) 2008-2014 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <Urho3D/Urho3D.h>

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/UI/UI.h>

#include "Sprites.h"

#include <Urho3D/DebugNew.h>

// Number of sprites to draw
static const unsigned NUM_SPRITES = 100;

// Custom variable identifier for storing sprite velocity within the UI element
static const StringHash VAR_VELOCITY("Velocity");

DEFINE_APPLICATION_MAIN(Sprites)

Sprites::Sprites(Context* context) :
    Sample(context)
{
}

void Sprites::Start()
{
    // Execute base class startup
    Sample::Start();

    // Create the sprites to the user interface
    CreateSprites();

    // Hook up to the frame update events
    SubscribeToEvents();
}

void Sprites::CreateSprites()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Graphics* graphics = GetSubsystem<Graphics>();
    UI* ui = GetSubsystem<UI>();

    // Get rendering window size as floats
    float width = (float)graphics->GetWidth();
    float height = (float)graphics->GetHeight();

    // Get the Urho3D fish texture
    Texture2D* decalTex = cache->GetResource<Texture2D>("Textures/UrhoDecal.dds");

    for (unsigned i = 0; i < NUM_SPRITES; ++i)
    {
        // Create a new sprite, set it to use the texture
        SharedPtr<Sprite> sprite(new Sprite(context_));
        sprite->SetTexture(decalTex);

        // The UI root element is as big as the rendering window, set random position within it
        sprite->SetPosition(Vector2(Random() * width, Random() * height));

        // Set sprite size & hotspot in its center
        sprite->SetSize(IntVector2(128, 128));
        sprite->SetHotSpot(IntVector2(64, 64));

        // Set random rotation in degrees and random scale
        sprite->SetRotation(Random() * 360.0f);
        sprite->SetScale(Random(1.0f) + 0.5f);

        // Set random color and additive blending mode
        sprite->SetColor(Color(Random(0.5f) + 0.5f, Random(0.5f) + 0.5f, Random(0.5f) + 0.5f));
        sprite->SetBlendMode(BLEND_ADD);

        // Add as a child of the root UI element
        ui->GetRoot()->AddChild(sprite);

        // Store sprite's velocity as a custom variable
        sprite->SetVar(VAR_VELOCITY, Vector2(Random(200.0f) - 100.0f, Random(200.0f) - 100.0f));

        // Store sprites to our own container for easy movement update iteration
        sprites_.Push(sprite);
    }
}

void Sprites::MoveSprites(float timeStep)
{
    Graphics* graphics = GetSubsystem<Graphics>();
    float width = (float)graphics->GetWidth();
    float height = (float)graphics->GetHeight();

    // Go through all sprites
    for (unsigned i = 0; i < sprites_.Size(); ++i)
    {
        Sprite* sprite = sprites_[i];

        // Rotate
        float newRot = sprite->GetRotation() + timeStep * 30.0f;
        sprite->SetRotation(newRot);
        
        // Move, wrap around rendering window edges
        Vector2 newPos = sprite->GetPosition() + sprite->GetVar(VAR_VELOCITY).GetVector2() * timeStep;
        if (newPos.x_ < 0.0f)
            newPos.x_ += width;
        if (newPos.x_ >= width)
            newPos.x_ -= width;
        if (newPos.y_ < 0.0f)
            newPos.y_ += height;
        if (newPos.y_ >= height)
            newPos.y_ -= height;
        sprite->SetPosition(newPos);
    }
}

void Sprites::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, HANDLER(Sprites, HandleUpdate));
}

void Sprites::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    
    // Move sprites, scale movement with time step
    MoveSprites(timeStep);
}
