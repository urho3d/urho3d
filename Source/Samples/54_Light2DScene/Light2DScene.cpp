//
// Copyright (c) 2008-2019 the Urho3D project.
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
#include <Urho3D/Urho2D/Light2D.h>
#include <Urho3D/Math/MathDefs.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Urho2D/CollisionCircle2D.h>
#include <Urho3D/Core/StringUtils.h>

#include "Light2DScene.h"

#include <Urho3D/DebugNew.h>

// Number of static sprites to draw
static const unsigned NUM_SPRITES = 200;
static const StringHash VAR_MOVESPEED("MoveSpeed");
static const StringHash VAR_ROTATESPEED("RotateSpeed");

URHO3D_DEFINE_APPLICATION_MAIN(Light2DScene)

Light2DScene::Light2DScene(Context* context) :
    Sample(context)
{
    context->RegisterFactory<Background>();
    context->RegisterFactory<LightComponent>();
    context->RegisterFactory<ShadowCaster>();
}

void Light2DScene::Start()
{
    // Execute base class startup
    Sample::Start();

    // Setup the viewport for displaying the scene
    SetupViewport();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateInstructions();

    // Hook up to the frame update events
    SubscribeToEvents();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);
}

void Light2DScene::CreateScene()
{
    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();
    
    auto* cache = GetSubsystem<ResourceCache>();
    SharedPtr<File> file = cache->GetFile("Scenes/SceneLight2D.xml");
    if(file == nullptr || !file->IsOpen())
        return;
    scene_->LoadXML(*file);
    Camera* camera = nullptr;
    PODVector<Node*> cameraNodes;
    scene_->GetChildrenWithComponent(cameraNodes, Camera::GetTypeStatic(), true);
    if (cameraNodes.Size())
    {
        cameraNode_ = cameraNodes[0];
        camera = cameraNode_->GetComponent<Camera>();
    }
    viewport_->SetScene(scene_);

    if (camera)
    {
        //set its ortho size
        camera->SetOrthoSize(GetSubsystem<Graphics>()->GetHeight() * PIXEL_SIZE);
        viewport_->SetCamera(camera);
    }

    auto* node = scene_->GetChild("background");
    if (node != nullptr)
    {
        node->CreateComponent<Background>();
    }

    cameraNodes.Clear();
    scene_->GetChildrenWithComponent(cameraNodes, PointLight2D::GetTypeStatic(), true);
    for(auto var : cameraNodes)
    {
         var->CreateComponent<LightComponent>();
    }

    cameraNodes.Clear();
    node = scene_->GetChild("ShadowCasters");
    if (node != nullptr)
    {
         node->GetChildren(cameraNodes);
         for (auto var : cameraNodes)
         {
             var->CreateComponent<ShadowCaster>();
         }
    }
}

void Light2DScene::CreateInstructions()
{
    auto* cache = GetSubsystem<ResourceCache>();
    auto* ui = GetSubsystem<UI>();

    // Construct new Text object, set string to display and font to use
    auto* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText("Use WASD keys to move, use PageUp PageDown keys to zoom.");
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void Light2DScene::SetupViewport()
{
    viewport_ = new Viewport(context_);

    auto* renderer = GetSubsystem<Renderer>();

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen

    renderer->SetViewport(0, viewport_);
}

void Light2DScene::MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (GetSubsystem<UI>()->GetFocusElement())
        return;

    auto* input = GetSubsystem<Input>();

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
        auto* camera = cameraNode_->GetComponent<Camera>();
        camera->SetZoom(camera->GetZoom() * 1.01f);
    }

    if (input->GetKeyDown(KEY_PAGEDOWN))
    {
        auto* camera = cameraNode_->GetComponent<Camera>();
        camera->SetZoom(camera->GetZoom() * 0.99f);
    }
}

void Light2DScene::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Light2DScene, HandleUpdate));

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent(E_SCENEUPDATE);
}

void Light2DScene::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);

    auto* graphics = GetSubsystem<Graphics>();
    float halfWidth = (float)graphics->GetWidth() * 0.5f * PIXEL_SIZE;
    float halfHeight = (float)graphics->GetHeight() * 0.5f * PIXEL_SIZE;

    for (unsigned i = 0; i < spriteNodes_.Size(); ++i)
    {
        SharedPtr<Node> node = spriteNodes_[i];

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


Background::Background(Context* context)
    :LogicComponent(context)
{

}

void Background::Start()
{
    auto* graphics = context_->GetSubsystem<Graphics>();
    
    //Get StaticSprite2D component from the current node
    StaticSprite2D* sprite2D = dynamic_cast<StaticSprite2D*>(node_->GetComponent("StaticSprite2D"));

    auto width = sprite2D->GetSprite()->GetTexture()->GetWidth();
    auto height = sprite2D->GetSprite()->GetTexture()->GetHeight();

    auto viewWidth = (float)graphics->GetWidth();
    auto viewHeight = (float)graphics->GetHeight();

    //scale the current node with X and Y
    node_->SetScale2D(viewWidth / width, viewHeight / height);
}

LightComponent::LightComponent(Context* context)
    :LogicComponent(context)
{
    auto* graphics = context_->GetSubsystem<Graphics>();

    auto viewWidth = (float)graphics->GetWidth();
    auto viewHeight = (float)graphics->GetHeight();

    halfWidth_ = viewWidth * PIXEL_SIZE * 0.5f;
    halfHeight_ = viewHeight * PIXEL_SIZE * 0.5f;
}

void LightComponent::Start()
{

    //Get PointLight2D component and set its color
    auto* light = node_->GetComponent<PointLight2D>();
    light->SetColor(Color(.1 + Random() * .9, .1 + Random() * .9, .1 + Random() * .9, 1));

    auto x = -halfWidth_ + (halfWidth_ * 2) * Random();
    auto y = -halfHeight_ + (halfHeight_ * 2) * Random();

    //Set position of the current node in the 2D spaceR
    node_->SetPosition2D(x, y);

    moveX_ = -2.f + (Random() * 4);
    moveY_ = -2.f + (Random() * 4);
}

void LightComponent::Update(float timeStep)
{
    auto prev = node_->GetPosition2D();
    //translate node in 2D space on X and Y values
    node_->Translate2D(Vector2((int)(moveX_ * timeStep), (int)(moveY_ * timeStep)));

    auto p = node_->GetPosition2D();

    if (p.x_ < -halfWidth_ || p.x_ > halfWidth_) {
        node_->SetPosition2D(prev);
        moveX_ = -moveX_;
    }

    if (p.y_ < -halfHeight_ || p.y_ > halfHeight_) {
        node_->SetPosition2D(prev);
        moveY_ = -moveY_;
    }
}

ShadowCaster::ShadowCaster(Context* context)
    :LogicComponent(context)
{
    auto* graphics = context_->GetSubsystem<Graphics>();

    auto viewWidth = (float)graphics->GetWidth();
    auto viewHeight = (float)graphics->GetHeight();

    halfWidth_ = viewWidth * PIXEL_SIZE * 0.5f;
    halfHeight_ = viewHeight * PIXEL_SIZE * 0.5f;
}

void ShadowCaster::Start()
{
    //Create RigidBody2D component on the current node and make its static and cast shadows
    auto* body = node_->CreateComponent<RigidBody2D>();
    body->SetBodyType(BodyType2D::BT_STATIC);
    body->SetCastShadows(true);

    //Create circle collision and set its radius
    auto* circle = node_->CreateComponent<CollisionCircle2D>();
    circle->SetRadius(.35f);

    //Create sprite
    auto* sprite = node_->CreateComponent<StaticSprite2D>();
    auto cache = context_->GetSubsystem<ResourceCache>();
    int idx = Round(Random() * 7) + 1;
    
    auto sprite2D = cache->GetResource<Sprite2D>(ToString("Urho2D/Light2D/ball%d.png", idx));
    sprite->SetSprite(sprite2D);

    auto x = -halfWidth_ + (halfWidth_ * 2) * Random();
    auto y = -halfHeight_ + (halfHeight_ * 2) * Random();

    // tolerance towards the middle of screen
    x *= .7;
    y *= .7;
    //Set position of the current node in 2D space
    node_->SetPosition2D(x, y);
}