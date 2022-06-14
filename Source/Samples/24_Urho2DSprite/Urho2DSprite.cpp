// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>
#include <Urho3D/Urho2D/Sprite2D.h>

#include "Urho2DSprite.h"

#include <Urho3D/DebugNew.h>

// Number of static sprites to draw
static const unsigned NUM_SPRITES = 200;
static const StringHash VAR_MOVESPEED("MoveSpeed");
static const StringHash VAR_ROTATESPEED("RotateSpeed");

URHO3D_DEFINE_APPLICATION_MAIN(Urho2DSprite)

Urho2DSprite::Urho2DSprite(Context* context) :
    Sample(context)
{
}

void Urho2DSprite::Start()
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

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);
}

void Urho2DSprite::CreateScene()
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
    camera->SetOrthoSize((float)graphics->GetHeight() * PIXEL_SIZE);

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    // Get sprite
    Sprite2D* sprite = cache->GetResource<Sprite2D>("Urho2D/Aster.png");
    if (!sprite)
        return;

    float halfWidth = graphics->GetWidth() * 0.5f * PIXEL_SIZE;
    float halfHeight = graphics->GetHeight() * 0.5f * PIXEL_SIZE;

    for (unsigned i = 0; i < NUM_SPRITES; ++i)
    {
        SharedPtr<Node> spriteNode(scene_->CreateChild("StaticSprite2D"));
        spriteNode->SetPosition(Vector3(Random(-halfWidth, halfWidth), Random(-halfHeight, halfHeight), 0.0f));

        StaticSprite2D* staticSprite = spriteNode->CreateComponent<StaticSprite2D>();
        // Set random color
        staticSprite->SetColor(Color(Random(1.0f), Random(1.0f), Random(1.0f), 1.0f));
        // Set blend mode
        staticSprite->SetBlendMode(BLEND_ALPHA);
        // Set sprite
        staticSprite->SetSprite(sprite);

        // Set move speed
        spriteNode->SetVar(VAR_MOVESPEED, Vector3(Random(-2.0f, 2.0f), Random(-2.0f, 2.0f), 0.0f));
        // Set rotate speed
        spriteNode->SetVar(VAR_ROTATESPEED, Random(-90.0f, 90.0f));

        // Add to sprite node vector
        spriteNodes_.Push(spriteNode);
    }

    // Get animation set
    AnimationSet2D* animationSet = cache->GetResource<AnimationSet2D>("Urho2D/GoldIcon.scml");
    if (!animationSet)
        return;

    SharedPtr<Node> spriteNode(scene_->CreateChild("AnimatedSprite2D"));
    spriteNode->SetPosition(Vector3(0.0f, 0.0f, -1.0f));

    AnimatedSprite2D* animatedSprite = spriteNode->CreateComponent<AnimatedSprite2D>();
    // Set animation
    animatedSprite->SetAnimationSet(animationSet);
    animatedSprite->SetAnimation("idle");
}

void Urho2DSprite::CreateInstructions()
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

void Urho2DSprite::SetupViewport()
{
    Renderer* renderer = GetSubsystem<Renderer>();

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void Urho2DSprite::MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (GetSubsystem<UI>()->GetFocusElement())
        return;

    Input* input = GetSubsystem<Input>();

    // Movement speed as world units per second
    const float MOVE_SPEED = 4.0f;

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input->GetKeyDown(KEY_W))
        cameraNode_->Translate(Vector3::UP * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_S))
        cameraNode_->Translate(Vector3::DOWN * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_A))
        cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_D))
        cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);

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

void Urho2DSprite::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Urho2DSprite, HandleUpdate));

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent(E_SCENEUPDATE);
}

void Urho2DSprite::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);

    Graphics* graphics = GetSubsystem<Graphics>();
    float halfWidth = (float)graphics->GetWidth() * 0.5f * PIXEL_SIZE;
    float halfHeight = (float)graphics->GetHeight() * 0.5f * PIXEL_SIZE;

    for (const SharedPtr<Node>& node : spriteNodes_)
    {
        Vector3 position = node->GetPosition();
        Vector3 moveSpeed = node->GetVar(VAR_MOVESPEED).GetVector3();
        Vector3 newPosition = position + moveSpeed * timeStep;
        if (newPosition.x_ < -halfWidth || newPosition.x_ > halfWidth)
        {
            newPosition.x_ = position.x_;
            moveSpeed.x_ = -moveSpeed.x_;
            node->SetVar(VAR_MOVESPEED, moveSpeed);
        }
        if (newPosition.y_ < -halfHeight || newPosition.y_ > halfHeight)
        {
            newPosition.y_ = position.y_;
            moveSpeed.y_ = -moveSpeed.y_;
            node->SetVar(VAR_MOVESPEED, moveSpeed);
        }

        node->SetPosition(newPosition);

        float rotateSpeed = node->GetVar(VAR_ROTATESPEED).GetFloat();
        node->Roll(rotateSpeed * timeStep);
    }
}
