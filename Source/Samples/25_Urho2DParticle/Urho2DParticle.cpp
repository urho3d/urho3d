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

#include "Camera.h"
#include "CoreEvents.h"
#include "Engine.h"
#include "Font.h"
#include "Graphics.h"
#include "Input.h"
#include "InputEvents.h"
#include "Octree.h"
#include "ParticleEmitter2D.h"
#include "ParticleModel2D.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "Text.h"
#include "Urho2DParticle.h"
#include "Zone.h"

#include "DebugNew.h"

DEFINE_APPLICATION_MAIN(Urho2DParticle)

Urho2DParticle::Urho2DParticle(Context* context) :
Sample(context)
{    
}

void Urho2DParticle::Start()
{
    // Execute base class startup
    Sample::Start();

    // Set mouse visibile
    Input* input = GetSubsystem<Input>();
    input->SetMouseVisible(true);

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateInstructions();

    // Setup the viewport for displaying the scene
    SetupViewport();

    // Hook up to the frame update events
    SubscribeToEvents();
}

void Urho2DParticle::CreateScene()
{
    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();

    // Create camera node
    cameraNode_ = scene_->CreateChild("Camera");
    // Set camera's position
    cameraNode_->SetPosition(Vector3(0.0f, 0.0f, -10.0f));

    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetOrthographic(true);

    Graphics* graphics = GetSubsystem<Graphics>();
    camera->SetOrthoSize(Vector2((float)graphics->GetWidth(), (float)graphics->GetHeight()));

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    ParticleModel2D* particleModel = cache->GetResource<ParticleModel2D>("Urho2D/LavaFlow.plist");
    if (!particleModel)
        return;

    particleNode_ = scene_->CreateChild("ParticleEmitter2D");
    ParticleEmitter2D* particleEmitter = particleNode_->CreateComponent<ParticleEmitter2D>();
    particleEmitter->SetModel(particleModel);
}

void Urho2DParticle::CreateInstructions()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    // Construct new Text object, set string to display and font to use
    Text* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText("Use mouse to move the particle.");
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void Urho2DParticle::SetupViewport()
{
    Renderer* renderer = GetSubsystem<Renderer>();

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void Urho2DParticle::SubscribeToEvents()
{
    SubscribeToEvent(E_MOUSEMOVE, HANDLER(Urho2DParticle, HandleMouseMove));
}

void Urho2DParticle::HandleMouseMove(StringHash eventType, VariantMap& eventData)
{
    if (particleNode_)
    {
        using namespace MouseMove;
        float x = (float)eventData[P_X].GetInt();
        float y = (float)eventData[P_Y].GetInt();
        Graphics* graphics = GetSubsystem<Graphics>();
        particleNode_->SetPosition(Vector3(x - graphics->GetWidth() * 0.5f, -y + graphics->GetHeight() * 0.5f, 0.0));
    }
}
