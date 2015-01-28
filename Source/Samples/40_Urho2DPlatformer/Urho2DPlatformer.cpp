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

#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>
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
#include <Urho3D/Input/Input.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Urho2D/PhysicsWorld2D.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/Urho2D/TileMap2D.h>
#include <Urho3D/Urho2D/TileMapLayer2D.h>
#include <Urho3D/Urho2D/TmxFile2D.h>
#include <Urho3D/Graphics/Zone.h>

#include <Urho3D/Container/DebugNew.h>

#include "Character2D.h"
#include "Sample2D.h"
#include "Mover.h"
#include "Urho2DPlatformer.h"


DEFINE_APPLICATION_MAIN(Urho2DPlatformer)

Urho2DPlatformer::Urho2DPlatformer(Context* context) :
    Sample(context),
    drawDebug_(false)
{
    // Register factory for the Character2D component so it can be created via CreateComponent
    Character2D::RegisterObject(context);
    // Register an object factory for Mover component so that we can create them to scene nodes
    context->RegisterFactory<Mover>();
}

void Urho2DPlatformer::Start()
{
    // Execute base class startup
    Sample::Start();

    sample2D_ = new Sample2D(context_);

    // Create the scene content
    CreateScene();

    // Create the UI content
    sample2D_->CreateInstructions("Use WASD keys or Arrows to move\nPageUp/PageDown/MouseWheel to zoom\nF5/F7 to save/reload scene\n'Z' to toggle debug geometry\nSpace to fight");

    // Hook up to the frame update events
    SubscribeToEvents();
}

void Urho2DPlatformer::CreateScene()
{
    scene_ = new Scene(context_);

    // Create the Octree, DebugRenderer and PhysicsWorld2D component to the scene
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<DebugRenderer>();
    PhysicsWorld2D* physicsWorld = scene_->CreateComponent<PhysicsWorld2D>();

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

    // Set background color for the scene
    Zone* zone = renderer->GetDefaultZone();
    zone->SetFogColor(Color(0.2f, 0.2f, 0.2f));

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    // Get tmx file
    TmxFile2D* tmxFile = cache->GetResource<TmxFile2D>("Urho2D/Tilesets/Ortho.tmx");
    if (!tmxFile)
        return;

    SharedPtr<Node> tileMapNode(scene_->CreateChild("TileMap"));

    TileMap2D* tileMap = tileMapNode->CreateComponent<TileMap2D>();
    tileMap->SetTmxFile(tmxFile);
    const TileMapInfo2D& info = tileMap->GetInfo();

    // Get top layer ("Physics") which stores the objects for shapes
    TileMapLayer2D* tileMapLayer = tileMap->GetLayer(tileMap->GetNumLayers() - 1);

    // Generate physics collision shapes from the tmx file's objects located in "Physics" layer
    //CreateCollisionShapesFromTMXObjects(tileMapNode, tileMapLayer, info);
    sample2D_->CreateCollisionShapesFromTMXObjects(tileMapNode, tileMapLayer, info);

    // Get "Enemies" layer which stores the placeholder objects for enemies and their paths
    TileMapLayer2D* enemiesLayer = tileMap->GetLayer(tileMap->GetNumLayers() - 2);

    // Create enemy (will be cloned at each placeholder)
    Node* enemyNode = CreateEnemy();

    // Instantiate enemies at each placeholder (in this sample, placeholders are Poly Line objects defining start and end points)
    for (int i=0; i < enemiesLayer->GetNumObjects(); ++i)
    {
        TileMapObject2D* enemyObject = enemiesLayer->GetObject(i); // Get placeholder object (TileMapObject2D)
        if (enemyObject->GetObjectType() != OT_POLYLINE)
        {
            LOGWARNING("A non Poly Line Object has been found in 'Enemies' layer and skipped");
            continue;
        }
        Node* enemyClone = scene_->GetChild("Enemy")->Clone();
        Vector2 offset = Vector2(0, 0.15);
        enemyClone->SetPosition2D(enemyObject->GetPoint(0) + offset);
        Mover* mover = enemyClone->CreateComponent<Mover>(); // Create script object that handles enemy translation
        // Set path from points
        PODVector<Vector2> path = sample2D_->CreatePathFromPoints(enemyObject);
        mover->path_ = path;
        // Override default speed
        if (enemyObject->HasProperty("Speed"))
            mover->speed_ = ToFloat(enemyObject->GetProperty("Speed"));
    }

    // Get "Coins" layer which stores the placeholder objects for coins
    TileMapLayer2D* coinsLayer = tileMap->GetLayer(tileMap->GetNumLayers() - 3);

    // Create coin (will be cloned at each placeholder)
    Node* coinNode = CreateCoin();

    // Instantiate coins to pick at each placeholder
    for (int i=0; i < coinsLayer->GetNumObjects(); ++i)
    {
        TileMapObject2D* coinObject = coinsLayer->GetObject(i); // Get placeholder object
        Node* coinClone = coinNode->Clone();
        coinClone->SetPosition2D(coinObject->GetPosition() + coinObject->GetSize() / 2 + Vector2(0.0f, 0.15f));
    }

    // Get "MovingPlatforms" layer which stores the placeholder objects for moving platforms
    TileMapLayer2D* platformsLayer = tileMap->GetLayer(tileMap->GetNumLayers() - 4);

    // Create platform (will be cloned at each placeholder)
    Node* platformNode = CreateMovingPlatform();

    // Instantiate moving platforms at each placeholder
    for (int i=0; i < platformsLayer->GetNumObjects(); ++i)
    {
        TileMapObject2D* platformObject = platformsLayer->GetObject(i); // Get placeholder object
        if (platformObject->GetObjectType() != OT_POLYLINE)
        {
            LOGWARNING("A non Poly Line Object has been found in 'MovingPlatforms' layer and skipped");
            continue;
        }
        Node* platformClone = platformNode->Clone();
        platformClone->SetPosition2D(platformObject->GetPoint(0));
        Mover* mover = platformClone->CreateComponent<Mover>(); // Create script object that handles platform translation
        // Set path from points
        PODVector<Vector2> path = sample2D_->CreatePathFromPoints(platformObject);
        mover->path_ = path;
        if (platformObject->HasProperty("Speed"))
            mover->speed_ = ToFloat(platformObject->GetProperty("Speed"));
    }

    // Create Spriter Imp character (from sample 33_SpriterAnimation)
    Node* spriteNode = sample2D_->CreateCharacter(scene_, info, 0.8f, Vector3(1.0f, 23.0f, 0.0f));
    character2D_ = spriteNode->CreateComponent<Character2D>(); // Create a logic component to handle character behavior
}

Node* Urho2DPlatformer::CreateEnemy()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Node* node = scene_->CreateChild("Enemy");
    StaticSprite2D* staticSprite = node->CreateComponent<StaticSprite2D>();
    staticSprite->SetSprite(cache->GetResource<Sprite2D>("Urho2D/Aster.png"));
    RigidBody2D* body = node->CreateComponent<RigidBody2D>();
    body->SetBodyType(BT_STATIC);
    CollisionCircle2D* shape = node->CreateComponent<CollisionCircle2D>(); // Create circle shape
    shape->SetRadius(0.32f); // Set radius
    return node;
}

Node* Urho2DPlatformer::CreateCoin()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Node* node = scene_->CreateChild("Coin");
    node->SetScale(0.5);
    AnimatedSprite2D* animatedSprite = node->CreateComponent<AnimatedSprite2D>();
    animatedSprite->SetAnimation(cache->GetResource<AnimationSet2D>("Urho2D/GoldIcon.scml"), "idle"); // Get scml file and Play "idle" anim
    RigidBody2D* body = node->CreateComponent<RigidBody2D>();
    body->SetBodyType(BT_STATIC);
    CollisionCircle2D* shape = node->CreateComponent<CollisionCircle2D>(); // Create circle shape
    shape->SetRadius(0.32f); // Set radius
    shape->SetTrigger(true);
    return node;
}

Node* Urho2DPlatformer::CreateMovingPlatform()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Node* node = scene_->CreateChild("MovingPlatform");
    node->SetScale(Vector3(3.0f, 1.0f, 0.0f));
    StaticSprite2D* staticSprite = node->CreateComponent<StaticSprite2D>();
    staticSprite->SetSprite(cache->GetResource<Sprite2D>("Urho2D/Box.png"));
    RigidBody2D* body = node->CreateComponent<RigidBody2D>();
    body->SetBodyType(BT_STATIC);
    CollisionBox2D* shape = node->CreateComponent<CollisionBox2D>(); // Create rectangular shape
    shape->SetSize(Vector2(0.32f, 0.32f)); // Set box size
    shape->SetFriction(0.8f); // Set friction
    return node;
}

void Urho2DPlatformer::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, HANDLER(Urho2DPlatformer, HandleUpdate));

    // Subscribe HandlePostUpdate() function for processing post update events
    SubscribeToEvent(E_POSTUPDATE, HANDLER(Urho2DPlatformer, HandlePostUpdate));

    // Subscribe to PostRenderUpdate to draw physics shapes
    SubscribeToEvent(E_POSTRENDERUPDATE, HANDLER(Urho2DPlatformer, HandlePostRenderUpdate));

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent(E_SCENEUPDATE);
}

void Urho2DPlatformer::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Zoom in/out
    if (cameraNode_)
        sample2D_->Zoom(cameraNode_->GetComponent<Camera>());

    Input* input = GetSubsystem<Input>();

    // Toggle debug geometry with spacebar
    if (input->GetKeyPress(KEY_Z))
        drawDebug_ = !drawDebug_;

    // Check for loading / saving the scene
    if (input->GetKeyPress(KEY_F5))
    {
        File saveFile(context_, GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Scenes/TileMap.xml", FILE_WRITE);
        scene_->SaveXML(saveFile);
    }
    if (input->GetKeyPress(KEY_F7))
    {
        File loadFile(context_, GetSubsystem<FileSystem>()->GetProgramDir() + "Data/Scenes/TileMap.xml", FILE_READ);
        scene_->LoadXML(loadFile);
        // After loading we have to reacquire the weak pointer to the Character2D component, as it has been recreated
        // Simply find the character's scene node by name as there's only one of them
        Node* character2DNode = scene_->GetChild("Imp", true);
        if (character2DNode)
            character2D_ = character2DNode->GetComponent<Character2D>();
    }
}

void Urho2DPlatformer::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if (!character2D_)
        return;

    Node* character2DNode = character2D_->GetNode();
    cameraNode_->SetPosition(Vector3(character2DNode->GetPosition().x_, character2DNode->GetPosition().y_, -10.0f)); // Camera tracks character
}

void Urho2DPlatformer::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    if (drawDebug_)
    {
        PhysicsWorld2D* physicsWorld = scene_->GetComponent<PhysicsWorld2D>();
        physicsWorld->DrawDebugGeometry();
    }
}