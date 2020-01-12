//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include <Urho3D/Audio/Audio.h>
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
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/GraphicsEvents.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Urho2D/PhysicsEvents2D.h>
#include <Urho3D/Urho2D/PhysicsWorld2D.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/Urho2D/TileMap2D.h>
#include <Urho3D/Urho2D/TileMapLayer2D.h>
#include <Urho3D/Urho2D/TmxFile2D.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/Graphics/Zone.h>

#include <Urho3D/DebugNew.h>

#include "Character2D.h"
#include "Utilities2D/Sample2D.h"
#include "Utilities2D/Mover.h"
#include "Urho2DPlatformer.h"


URHO3D_DEFINE_APPLICATION_MAIN(Urho2DPlatformer)

Urho2DPlatformer::Urho2DPlatformer(Context* context) :
    Sample(context)
{
    // Register factory for the Character2D component so it can be created via CreateComponent
    Character2D::RegisterObject(context);
    // Register factory and attributes for the Mover component so it can be created via CreateComponent, and loaded / saved
    Mover::RegisterObject(context);
}

void Urho2DPlatformer::Setup()
{
    Sample::Setup();
    engineParameters_[EP_SOUND] = true;
}

void Urho2DPlatformer::Start()
{
    // Execute base class startup
    Sample::Start();

    sample2D_ = new Sample2D(context_);

    // Set filename for load/save functions
    sample2D_->demoFilename_ = "Platformer2D";

    // Create the scene content
    CreateScene();

    // Create the UI content
    sample2D_->CreateUIContent("PLATFORMER 2D DEMO", character2D_->remainingLifes_, character2D_->remainingCoins_);
    auto* ui = GetSubsystem<UI>();
    Button* playButton = static_cast<Button*>(ui->GetRoot()->GetChild("PlayButton", true));
    SubscribeToEvent(playButton, E_RELEASED, URHO3D_HANDLER(Urho2DPlatformer, HandlePlayButton));

    // Hook up to the frame update events
    SubscribeToEvents();
}

void Urho2DPlatformer::CreateScene()
{
    scene_ = new Scene(context_);
    sample2D_->scene_ = scene_;

    // Create the Octree, DebugRenderer and PhysicsWorld2D components to the scene
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<DebugRenderer>();
    /*PhysicsWorld2D* physicsWorld =*/ scene_->CreateComponent<PhysicsWorld2D>();

    // Create camera
    cameraNode_ = scene_->CreateChild("Camera");
    auto* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetOrthographic(true);

    auto* graphics = GetSubsystem<Graphics>();
    camera->SetOrthoSize((float)graphics->GetHeight() * PIXEL_SIZE);
    camera->SetZoom(2.0f * Min((float)graphics->GetWidth() / 1280.0f, (float)graphics->GetHeight() / 800.0f)); // Set zoom according to user's resolution to ensure full visibility (initial zoom (2.0) is set for full visibility at 1280x800 resolution)

    // Setup the viewport for displaying the scene
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, camera));
    auto* renderer = GetSubsystem<Renderer>();
    renderer->SetViewport(0, viewport);

    // Set background color for the scene
    Zone* zone = renderer->GetDefaultZone();
    zone->SetFogColor(Color(0.2f, 0.2f, 0.2f));

    // Create tile map from tmx file
    auto* cache = GetSubsystem<ResourceCache>();
    SharedPtr<Node> tileMapNode(scene_->CreateChild("TileMap"));
    auto* tileMap = tileMapNode->CreateComponent<TileMap2D>();
    tileMap->SetTmxFile(cache->GetResource<TmxFile2D>("Urho2D/Tilesets/Ortho.tmx"));
    const TileMapInfo2D& info = tileMap->GetInfo();

    // Create Spriter Imp character (from sample 33_SpriterAnimation)
    Node* spriteNode = sample2D_->CreateCharacter(info, 0.8f, Vector3(1.0f, 8.0f, 0.0f), 0.2f);
    character2D_ = spriteNode->CreateComponent<Character2D>(); // Create a logic component to handle character behavior

    // Generate physics collision shapes from the tmx file's objects located in "Physics" (top) layer
    TileMapLayer2D* tileMapLayer = tileMap->GetLayer(tileMap->GetNumLayers() - 1);
    sample2D_->CreateCollisionShapesFromTMXObjects(tileMapNode, tileMapLayer, info);

    // Instantiate enemies and moving platforms at each placeholder of "MovingEntities" layer (placeholders are Poly Line objects defining a path from points)
    sample2D_->PopulateMovingEntities(tileMap->GetLayer(tileMap->GetNumLayers() - 2));

    // Instantiate coins to pick at each placeholder of "Coins" layer (placeholders for coins are Rectangle objects)
    TileMapLayer2D* coinsLayer = tileMap->GetLayer(tileMap->GetNumLayers() - 3);
    sample2D_->PopulateCoins(coinsLayer);

    // Init coins counters
    character2D_->remainingCoins_ = coinsLayer->GetNumObjects();
    character2D_->maxCoins_ = coinsLayer->GetNumObjects();

    //Instantiate triggers (for ropes, ladders, lava, slopes...) at each placeholder of "Triggers" layer (placeholders for triggers are Rectangle objects)
    sample2D_->PopulateTriggers(tileMap->GetLayer(tileMap->GetNumLayers() - 4));

    // Create background
    sample2D_->CreateBackgroundSprite(info, 3.5, "Textures/HeightMap.png", true);

    // Check when scene is rendered
    SubscribeToEvent(E_ENDRENDERING, URHO3D_HANDLER(Urho2DPlatformer, HandleSceneRendered));
}

void Urho2DPlatformer::HandleSceneRendered(StringHash eventType, VariantMap& eventData)
{
    UnsubscribeFromEvent(E_ENDRENDERING);
    // Save the scene so we can reload it later
    sample2D_->SaveScene(true);
    // Pause the scene as long as the UI is hiding it
    scene_->SetUpdateEnabled(false);
}

void Urho2DPlatformer::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Urho2DPlatformer, HandleUpdate));

    // Subscribe HandlePostUpdate() function for processing post update events
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(Urho2DPlatformer, HandlePostUpdate));

    // Subscribe to PostRenderUpdate to draw debug geometry
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(Urho2DPlatformer, HandlePostRenderUpdate));

    // Subscribe to Box2D contact listeners
    SubscribeToEvent(E_PHYSICSBEGINCONTACT2D, URHO3D_HANDLER(Urho2DPlatformer, HandleCollisionBegin));
    SubscribeToEvent(E_PHYSICSENDCONTACT2D, URHO3D_HANDLER(Urho2DPlatformer, HandleCollisionEnd));

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent(E_SCENEUPDATE);
}

void Urho2DPlatformer::HandleCollisionBegin(StringHash eventType, VariantMap& eventData)
{
    // Get colliding node
    auto* hitNode = static_cast<Node*>(eventData[PhysicsBeginContact2D::P_NODEA].GetPtr());
    if (hitNode->GetName() == "Imp")
        hitNode = static_cast<Node*>(eventData[PhysicsBeginContact2D::P_NODEB].GetPtr());
    String nodeName = hitNode->GetName();
    Node* character2DNode = scene_->GetChild("Imp", true);

    // Handle ropes and ladders climbing
    if (nodeName == "Climb")
    {
        if (character2D_->isClimbing_) // If transition between rope and top of rope (as we are using split triggers)
            character2D_->climb2_ = true;
        else
        {
            character2D_->isClimbing_ = true;
            auto* body = character2DNode->GetComponent<RigidBody2D>();
            body->SetGravityScale(0.0f); // Override gravity so that the character doesn't fall
            // Clear forces so that the character stops (should be performed by setting linear velocity to zero, but currently doesn't work)
            body->SetLinearVelocity(Vector2(0.0f, 0.0f));
            body->SetAwake(false);
            body->SetAwake(true);
        }
    }

    if (nodeName == "CanJump")
        character2D_->aboveClimbable_ = true;

    // Handle coins picking
    if (nodeName == "Coin")
    {
        hitNode->Remove();
        character2D_->remainingCoins_ -= 1;
        auto* ui = GetSubsystem<UI>();
        if (character2D_->remainingCoins_ == 0)
        {
            Text* instructions = static_cast<Text*>(ui->GetRoot()->GetChild("Instructions", true));
            instructions->SetText("!!! Go to the Exit !!!");
        }
        Text* coinsText = static_cast<Text*>(ui->GetRoot()->GetChild("CoinsText", true));
        coinsText->SetText(String(character2D_->remainingCoins_)); // Update coins UI counter
        sample2D_->PlaySoundEffect("Powerup.wav");
    }

    // Handle interactions with enemies
    if (nodeName == "Enemy" || nodeName == "Orc")
    {
        auto* animatedSprite = character2DNode->GetComponent<AnimatedSprite2D>();
        float deltaX = character2DNode->GetPosition().x_ - hitNode->GetPosition().x_;

        // Orc killed if character is fighting in its direction when the contact occurs (flowers are not destroyable)
        if (nodeName == "Orc" && animatedSprite->GetAnimation() == "attack" && (deltaX < 0 == animatedSprite->GetFlipX()))
        {
            static_cast<Mover*>(hitNode->GetComponent<Mover>())->emitTime_ = 1;
            if (!hitNode->GetChild("Emitter", true))
            {
                hitNode->GetComponent("RigidBody2D")->Remove(); // Remove Orc's body
                sample2D_->SpawnEffect(hitNode);
                sample2D_->PlaySoundEffect("BigExplosion.wav");
            }
        }
        // Player killed if not fighting in the direction of the Orc when the contact occurs, or when colliding with a flower
        else
        {
            if (!character2DNode->GetChild("Emitter", true))
            {
                character2D_->wounded_ = true;
                if (nodeName == "Orc")
                {
                    auto* orc = static_cast<Mover*>(hitNode->GetComponent<Mover>());
                    orc->fightTimer_ = 1;
                }
                sample2D_->SpawnEffect(character2DNode);
                sample2D_->PlaySoundEffect("BigExplosion.wav");
            }
        }
    }

    // Handle exiting the level when all coins have been gathered
    if (nodeName == "Exit" && character2D_->remainingCoins_ == 0)
    {
        // Update UI
        auto* ui = GetSubsystem<UI>();
        Text* instructions = static_cast<Text*>(ui->GetRoot()->GetChild("Instructions", true));
        instructions->SetText("!!! WELL DONE !!!");
        instructions->SetPosition(IntVector2(0, 0));
        // Put the character outside of the scene and magnify him
        character2DNode->SetPosition(Vector3(-20.0f, 0.0f, 0.0f));
        character2DNode->SetScale(1.5f);
    }

    // Handle falling into lava
    if (nodeName == "Lava")
    {
        auto* body = character2DNode->GetComponent<RigidBody2D>();
        body->ApplyForceToCenter(Vector2(0.0f, 1000.0f), true);
        if (!character2DNode->GetChild("Emitter", true))
        {
            character2D_->wounded_ = true;
            sample2D_->SpawnEffect(character2DNode);
            sample2D_->PlaySoundEffect("BigExplosion.wav");
        }
    }

    // Handle climbing a slope
    if (nodeName == "Slope")
        character2D_->onSlope_ = true;
}

void Urho2DPlatformer::HandleCollisionEnd(StringHash eventType, VariantMap& eventData)
{
    // Get colliding node
    auto* hitNode = static_cast<Node*>(eventData[PhysicsEndContact2D::P_NODEA].GetPtr());
    if (hitNode->GetName() == "Imp")
        hitNode = static_cast<Node*>(eventData[PhysicsEndContact2D::P_NODEB].GetPtr());
    String nodeName = hitNode->GetName();
    Node* character2DNode = scene_->GetChild("Imp", true);

    // Handle leaving a rope or ladder
    if (nodeName == "Climb")
    {
        if (character2D_->climb2_)
            character2D_->climb2_ = false;
        else
        {
            character2D_->isClimbing_ = false;
            auto* body = character2DNode->GetComponent<RigidBody2D>();
            body->SetGravityScale(1.0f); // Restore gravity
        }
    }

    if (nodeName == "CanJump")
        character2D_->aboveClimbable_ = false;

    // Handle leaving a slope
    if (nodeName == "Slope")
    {
        character2D_->onSlope_ = false;
        // Clear forces (should be performed by setting linear velocity to zero, but currently doesn't work)
        auto* body = character2DNode->GetComponent<RigidBody2D>();
        body->SetLinearVelocity(Vector2::ZERO);
        body->SetAwake(false);
        body->SetAwake(true);
    }
}

void Urho2DPlatformer::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Zoom in/out
    if (cameraNode_)
        sample2D_->Zoom(cameraNode_->GetComponent<Camera>());

    auto* input = GetSubsystem<Input>();

    // Toggle debug geometry with 'Z' key
    if (input->GetKeyPress(KEY_Z))
        drawDebug_ = !drawDebug_;

    // Check for loading / saving the scene
    if (input->GetKeyPress(KEY_F5))
        sample2D_->SaveScene(false);
    if (input->GetKeyPress(KEY_F7))
        ReloadScene(false);
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
        auto* physicsWorld = scene_->GetComponent<PhysicsWorld2D>();
        physicsWorld->DrawDebugGeometry();

        Node* tileMapNode = scene_->GetChild("TileMap", true);
        auto* map = tileMapNode->GetComponent<TileMap2D>();
        map->DrawDebugGeometry(scene_->GetComponent<DebugRenderer>(), false);
    }
}

void Urho2DPlatformer::ReloadScene(bool reInit)
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
    auto* ui = GetSubsystem<UI>();
    Text* lifeText = static_cast<Text*>(ui->GetRoot()->GetChild("LifeText", true));
    lifeText->SetText(String(lifes));

    // Update coins UI
    Text* coinsText = static_cast<Text*>(ui->GetRoot()->GetChild("CoinsText", true));
    coinsText->SetText(String(coins));
}

void Urho2DPlatformer::HandlePlayButton(StringHash eventType, VariantMap& eventData)
{
    // Remove fullscreen UI and unfreeze the scene
    auto* ui = GetSubsystem<UI>();
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
    auto* input = GetSubsystem<Input>();
    input->SetMouseVisible(false);
}
