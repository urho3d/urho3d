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
#include "CollisionShape2D.h"
#include "CoreEvents.h"
#include "DebugRenderer.h"
#include "Engine.h"
#include "Font.h"
#include "Graphics.h"
#include "Input.h"
#include "Octree.h"
#include "PhysicsWorld2D.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "Sprite2D.h"
#include "StaticSprite2D.h"
#include "Text.h"
#include "Urho2DPhysics.h"
#include "Zone.h"

#include "DebugNew.h"

DEFINE_APPLICATION_MAIN(Urho2DPhysics)

Urho2DPhysics::Urho2DPhysics(Context* context) :
Sample(context)
{    
}

void Urho2DPhysics::Start()
{
    // Execute base class startup
    Sample::Start();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateInstructions();

    // Setup the viewport for displaying the scene
    SetupViewport();

    // Hook up to the frame update events
    SubscribeToEvents();
}

void Urho2DPhysics::CreateScene()
{
    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<DebugRenderer>();
    // Create camera node
    cameraNode_ = scene_->CreateChild("Camera");
    // Set camera's position
    cameraNode_->SetPosition(Vector3(0.0f, 0.0f, -10.0f));

    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetOrthographic(true);

    Graphics* graphics = GetSubsystem<Graphics>();
    float width = (float)graphics->GetWidth();
    float height = (float)graphics->GetHeight();
    camera->SetOrthoSize(Vector2(width, height) * PIXEL_SIZE);

    PhysicsWorld2D* physicsWorld = scene_->CreateComponent<PhysicsWorld2D>();
    // Define the gravity vector.
    physicsWorld->SetGravity(Vector2(0.0f, -10.0f));
    

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    // Get sprite
    Sprite2D* sprite = cache->GetResource<Sprite2D>("Urho2D/Box.png");
    if (!sprite)
        return;

    // Create ground.
    Node* groundNode = scene_->CreateChild("Ground");
    groundNode->SetPosition(Vector3(0.0f, -3.0f, 0.0f));
    RigidBody2D* groundBody = groundNode->CreateComponent<RigidBody2D>();

    CollisionShape2D* groundShape = groundNode->CreateComponent<CollisionShape2D>();
    groundShape->SetBox(Vector2(10.0f, 0.05f));
    groundShape->SetFriction(0.5f);

    for (unsigned i = 0; i < 100; ++i)
    {
        // Create a box.
        Node* boxNode  = scene_->CreateChild("Box");
        boxNode->SetPosition(Vector3(Random(-0.1f, 0.1f), 5.0f + i * 0.4f, 0.0f));

        RigidBody2D* boxBody = boxNode->CreateComponent<RigidBody2D>();
        boxBody->SetBodyType(BT_DYNAMIC);

        CollisionShape2D* boxShape = boxNode->CreateComponent<CollisionShape2D>();
        boxShape->SetBox(Vector2(0.16f, 0.16f));
        // Set the box density to be non-zero, so it will be dynamic.
        boxShape->SetDensity(1.0f);
        // Override the default friction.
        boxShape->SetFriction(0.5f);
        boxShape->SetRestitution(0.1f);

        // Create static sprite.
        StaticSprite2D* staticSprite = boxNode->CreateComponent<StaticSprite2D>();
        // Set sprite
        staticSprite->SetSprite(sprite);
    }
}

void Urho2DPhysics::CreateInstructions()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    // Construct new Text object, set string to display and font to use
    Text* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText("Use WASD keys to move, use PageUp PageDown keys to zoom.");
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void Urho2DPhysics::SetupViewport()
{
    Renderer* renderer = GetSubsystem<Renderer>();

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void Urho2DPhysics::MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (GetSubsystem<UI>()->GetFocusElement())
        return;

    Input* input = GetSubsystem<Input>();

    // Movement speed as world units per second
    const float MOVE_SPEED = 4.0f;

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    // Use the TranslateRelative() function to move relative to the node's orientation. Alternatively we could
    // multiply the desired direction with the node's orientation quaternion, and use just Translate()
    if (input->GetKeyDown('W'))
        cameraNode_->TranslateRelative(Vector3::UP * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('S'))
        cameraNode_->TranslateRelative(Vector3::DOWN* MOVE_SPEED * timeStep);
    if (input->GetKeyDown('A'))
        cameraNode_->TranslateRelative(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('D'))
        cameraNode_->TranslateRelative(Vector3::RIGHT * MOVE_SPEED * timeStep);
    
    if (input->GetKeyDown(KEY_PAGEUP))
    {
        Camera* camera = cameraNode_->GetComponent<Camera>();
        camera->SetZoom(camera->GetZoom() * 1.01f);
    }

    if (input->GetKeyDown(KEY_PAGEDOWN))
    {
        Camera* camera = cameraNode_->GetComponent<Camera>();
        camera->SetZoom(camera->GetZoom() * 0.99f);
    }
}

void Urho2DPhysics::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, HANDLER(Urho2DPhysics, HandleUpdate));
}

void Urho2DPhysics::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);
}
