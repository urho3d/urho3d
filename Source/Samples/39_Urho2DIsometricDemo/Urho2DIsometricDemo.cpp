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

#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Urho2D/CollisionBox2D.h>
#include <Urho3D/Urho2D/CollisionChain2D.h>
#include <Urho3D/Urho2D/CollisionCircle2D.h>
#include <Urho3D/Urho2D/CollisionPolygon2D.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Urho2D/Drawable2D.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/GraphicsEvents.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Urho2D/PhysicsWorld2D.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/Urho2D/TileMap2D.h>
#include <Urho3D/Urho2D/TileMapLayer2D.h>
#include <Urho3D/Urho2D/TmxFile2D.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/Graphics/Zone.h>

#include <Urho3D/DebugNew.h>

#include "Character2D.h"
#include "Utilities2D/Sample2D.h"
#include "Utilities2D/Mover.h"
#include "Urho2DIsometricDemo.h"


DEFINE_APPLICATION_MAIN(Urho2DIsometricDemo)

Urho2DIsometricDemo::Urho2DIsometricDemo(Context* context) :
    Sample(context),
    zoom_(2.0f),
    drawDebug_(false)
{
    // Register factory for the Character2D component so it can be created via CreateComponent
    Character2D::RegisterObject(context);
    // Register factory and attributes for the Mover component so it can be created via CreateComponent, and loaded / saved
    Mover::RegisterObject(context);
}

void Urho2DIsometricDemo::Start()
{
    // Execute base class startup
    Sample::Start();

    sample2D_ = new Sample2D(context_);

    // Set filename for load/save functions
    sample2D_->demoFilename_ = "Isometric2D";

    // Create the scene content
    CreateScene();

    // Create the UI content
    sample2D_->CreateUIContent("ISOMETRIC 2.5D DEMO", character2D_->remainingLifes_, character2D_->remainingCoins_);
    UI* ui = GetSubsystem<UI>();
    Button* playButton = static_cast<Button*>(ui->GetRoot()->GetChild("PlayButton", true));
    SubscribeToEvent(playButton, E_RELEASED, HANDLER(Urho2DIsometricDemo, HandlePlayButton));

    // Hook up to the frame update events
    SubscribeToEvents();
}

void Urho2DIsometricDemo::CreateScene()
{
    scene_ = new Scene(context_);
    sample2D_->scene_ = scene_;

    // Create the Octree, DebugRenderer and PhysicsWorld2D components to the scene
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<DebugRenderer>();
    PhysicsWorld2D* physicsWorld = scene_->CreateComponent<PhysicsWorld2D>();
    physicsWorld->SetGravity(Vector2(0.0f, 0.0f)); // Neutralize gravity as the character will always be grounded

    // Create camera
    cameraNode_ = scene_->CreateChild("Camera");
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetOrthographic(true);

    Graphics* graphics = GetSubsystem<Graphics>();
    camera->SetOrthoSize((float)graphics->GetHeight() * PIXEL_SIZE);
    camera->SetZoom(2.0f * Min((float)graphics->GetWidth() / 1280.0f, (float)graphics->GetHeight() / 800.0f)); // Set zoom according to user's resolution to ensure full visibility (initial zoom (2.0) is set for full visibility at 1280x800 resolution)

    // Setup the viewport for displaying the scene
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, camera));
    Renderer* renderer = GetSubsystem<Renderer>();
    renderer->SetViewport(0, viewport);

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    // Create tile map from tmx file
    TmxFile2D* tmxFile = cache->GetResource<TmxFile2D>("Urho2D/Tilesets/atrium.tmx");
    SharedPtr<Node> tileMapNode(scene_->CreateChild("TileMap"));
    TileMap2D* tileMap = tileMapNode->CreateComponent<TileMap2D>();
    tileMap->SetTmxFile(tmxFile);
    const TileMapInfo2D& info = tileMap->GetInfo();

    // Create Spriter Imp character (from sample 33_SpriterAnimation)
    Node* spriteNode = sample2D_->CreateCharacter(info, 0.0f, Vector3(-5.0f, 11.0f, 0.0f), 0.15f);
    character2D_ = spriteNode->CreateComponent<Character2D>(); // Create a logic component to handle character behavior
    // Scale character's speed on the Y axis according to tiles' aspect ratio
    character2D_->moveSpeedScale_ = info.tileHeight_ / info.tileWidth_;
    character2D_->zoom_ = camera->GetZoom();

    // Generate physics collision shapes from the tmx file's objects located in "Physics" (top) layer
    TileMapLayer2D* tileMapLayer = tileMap->GetLayer(tileMap->GetNumLayers() - 1);
    sample2D_->CreateCollisionShapesFromTMXObjects(tileMapNode, tileMapLayer, info);

    // Instantiate enemies at each placeholder of "MovingEntities" layer (placeholders are Poly Line objects defining a path from points)
    sample2D_->PopulateMovingEntities(tileMap->GetLayer(tileMap->GetNumLayers() - 2));

    // Check when scene is rendered
    SubscribeToEvent(E_ENDRENDERING, HANDLER(Urho2DIsometricDemo, HandleSceneRendered));
}

void Urho2DIsometricDemo::HandleSceneRendered(StringHash eventType, VariantMap& eventData)
{
    UnsubscribeFromEvent(E_ENDRENDERING);
    // Save the scene so we can reload it later
    sample2D_->SaveScene(true);
    // Pause the scene as long as the UI is hiding it
    scene_->SetUpdateEnabled(false);
}

void Urho2DIsometricDemo::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, HANDLER(Urho2DIsometricDemo, HandleUpdate));

    // Subscribe HandlePostUpdate() function for processing post update events
    SubscribeToEvent(E_POSTUPDATE, HANDLER(Urho2DIsometricDemo, HandlePostUpdate));

    // Subscribe to PostRenderUpdate to draw debug geometry
    SubscribeToEvent(E_POSTRENDERUPDATE, HANDLER(Urho2DIsometricDemo, HandlePostRenderUpdate));

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent(E_SCENEUPDATE);
}

void Urho2DIsometricDemo::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Zoom in/out
    if (cameraNode_)
        sample2D_->Zoom(cameraNode_->GetComponent<Camera>());

    Input* input = GetSubsystem<Input>();

    // Toggle debug geometry with 'Z' key
    if (input->GetKeyPress(KEY_Z))
        drawDebug_ = !drawDebug_;

    // Check for loading / saving the scene
    if (input->GetKeyPress(KEY_F5))
        sample2D_->SaveScene(false);

    if (input->GetKeyPress(KEY_F7))
        ReloadScene(false);
}

void Urho2DIsometricDemo::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if (!character2D_)
        return;

    Node* character2DNode = character2D_->GetNode();
    cameraNode_->SetPosition(Vector3(character2DNode->GetPosition().x_, character2DNode->GetPosition().y_, -10.0f)); // Camera tracks character
}

void Urho2DIsometricDemo::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    if (drawDebug_)
    {
        PhysicsWorld2D* physicsWorld = scene_->GetComponent<PhysicsWorld2D>();
        physicsWorld->DrawDebugGeometry();

        Node* tileMapNode = scene_->GetChild("TileMap", true);
        TileMap2D* map = tileMapNode->GetComponent<TileMap2D>();
        map->DrawDebugGeometry(scene_->GetComponent<DebugRenderer>(), false);
    }
}

void Urho2DIsometricDemo::ReloadScene(bool reInit)
{
    String filename = sample2D_->demoFilename_;
    if (!reInit)
        filename += "InGame";

    File loadFile(context_, GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Scenes/" + filename + ".xml", FILE_READ);
    scene_->LoadXML(loadFile);
    // After loading we have to reacquire the weak pointer to the Character2D component, as it has been recreated
    // Simply find the character's scene node by name as there's only one of them
    Node* character2DNode = scene_->GetChild("Imp", true);
    if (character2DNode)
        character2D_ = character2DNode->GetComponent<Character2D>();

    // Set what number to use depending whether reload is requested from 'PLAY' button (reInit=true) or 'F7' key (reInit=false)
    int lifes = character2D_->remainingLifes_;
    int coins = character2D_->remainingCoins_;
    if (reInit)
    {
        lifes = LIFES;
        coins = character2D_->maxCoins_;
    }

    // Update lifes UI
    UI* ui = GetSubsystem<UI>();
    Text* lifeText = static_cast<Text*>(ui->GetRoot()->GetChild("LifeText", true));
    lifeText->SetText(String(lifes));

    // Update coins UI
    Text* coinsText = static_cast<Text*>(ui->GetRoot()->GetChild("CoinsText", true));
    coinsText->SetText(String(coins));
}

void Urho2DIsometricDemo::HandlePlayButton(StringHash eventType, VariantMap& eventData)
{
    // Remove fullscreen UI and unfreeze the scene
    UI* ui = GetSubsystem<UI>();
    if (static_cast<Text*>(ui->GetRoot()->GetChild("FullUI", true)))
    {
        ui->GetRoot()->GetChild("FullUI", true)->Remove();
        scene_->SetUpdateEnabled(true);
    }
    else
        // Reload scene
        ReloadScene(true);

    // Hide Instructions and Play/Exit buttons
    Text* instructionText = static_cast<Text*>(ui->GetRoot()->GetChild("Instructions", true));
    instructionText->SetText("");
    Button* exitButton = static_cast<Button*>(ui->GetRoot()->GetChild("ExitButton", true));
    exitButton->SetVisible(false);
    Button* playButton = static_cast<Button*>(ui->GetRoot()->GetChild("PlayButton", true));
    playButton->SetVisible(false);

    // Hide mouse cursor
    Input* input = GetSubsystem<Input>();
    input->SetMouseVisible(false);
}