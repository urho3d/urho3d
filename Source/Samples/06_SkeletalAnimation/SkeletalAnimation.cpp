//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Animation.h"
#include "AnimatedModel.h"
#include "AnimationState.h"
#include "Camera.h"
#include "CoreEvents.h"
#include "DebugRenderer.h"
#include "Engine.h"
#include "Font.h"
#include "Graphics.h"
#include "Input.h"
#include "Log.h"
#include "Material.h"
#include "Model.h"
#include "Octree.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "Text.h"
#include "UI.h"
#include "Zone.h"

#include "SkeletalAnimation.h"

#include "DebugNew.h"

// Expands to this example's entry-point
DEFINE_APPLICATION_MAIN(SkeletalAnimation)

SkeletalAnimation::SkeletalAnimation(Context* context) :
    Sample(context),
    yaw_(0.0f),
    pitch_(0.0f),
    drawDebug_(false)
{
}

void SkeletalAnimation::Start()
{
    // Execute base class startup
    Sample::Start();

    // Create the scene content
    CreateScene();
    
    // Create the UI content
    CreateInstructions();
    
    // Setup the viewport for displaying the scene
    SetupViewport();

    // Hook up to the frame update and render post-update events
    SubscribeToEvents();
}

void SkeletalAnimation::CreateScene()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    scene_ = new Scene(context_);
    
    // Create the Octree component to the scene so that drawable objects can be rendered. Use default volume
    // (-1000, -1000, -1000) to (1000, 1000, 1000). Also create a DebugRenderer component so that we can draw
    // debug geometry
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<DebugRenderer>();
    
    // Create scene node & StaticModel component for showing a static plane
    Node* planeNode = scene_->CreateChild("Plane");
    StaticModel* planeObject = planeNode->CreateComponent<StaticModel>();
    planeNode->SetScale(Vector3(100.0f, 1.0f, 100.0f));
    planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    planeObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
    
    // Create a Zone component for ambient lighting & fog color control
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    // Set same volume as the Octree, set a close bluish fog and some ambient light
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.5f, 0.5f, 0.7f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(300.0f);
    
    // Create a directional light to the world. Enable cascaded shadows on it
    Node* lightNode = scene_->CreateChild("Directional light");
    lightNode->SetDirection(Vector3(-1.0f, -1.0f, -1.0f)); // The direction vector does not need to be normalized
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.0001f, 0.5f));
    // Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    
    // Create animated models
    const unsigned NUM_OBJECTS = 100;
    for (unsigned i = 0; i < NUM_OBJECTS; ++i)
    {
        Node* modelNode = scene_->CreateChild("Jack");
        AnimatedModel* modelObject = modelNode->CreateComponent<AnimatedModel>();
        modelNode->SetPosition(Vector3(Random(90.0f) - 45.0f, 0.0f, Random(90.0f) - 45.0f));
        modelNode->SetRotation(Quaternion(0.0f, Random(360.0f), 0.0f));
        modelObject->SetModel(cache->GetResource<Model>("Models/Jack.mdl"));
        modelObject->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
        modelObject->SetCastShadows(true);
        
        // Create an AnimationState for a walk animation. Its time position will need to be manually updated to advance the
        // animation, The alternative would be to use an AnimationController component which updates the animation automatically,
        // but we need to update the model's position manually in any case
        Animation* walkAnimation = cache->GetResource<Animation>("Models/Jack_Walk.ani");
        AnimationState* state = modelObject->AddAnimationState(walkAnimation);
        // Enable looping and full blending weight
        state->SetWeight(1.0f);
        state->SetLooped(true);
    }
    
    // Create the camera. Limit far clip distance to match the fog
    cameraNode_ = scene_->CreateChild("Camera");
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(300.0f);
    
    // Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(Vector3(0.0f, 5.0f, 0.0f));
}

void SkeletalAnimation::CreateInstructions()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();
    
    // Construct new Text object, set string to display and font to use
    Text* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText("Use WASD keys and mouse to move\nSpace to toggle debug geometry");
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    
    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void SkeletalAnimation::SetupViewport()
{
    Renderer* renderer = GetSubsystem<Renderer>();
    
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void SkeletalAnimation::MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    UI* ui = GetSubsystem<UI>();
    if (ui->GetFocusElement())
        return;
    
    Input* input = GetSubsystem<Input>();
    
    // Movement speed as world units per second
    const float MOVE_SPEED = 20.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;
    
    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
    pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);
    
    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
    
    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input->GetKeyDown('W'))
        cameraNode_->TranslateRelative(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('S'))
        cameraNode_->TranslateRelative(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('A'))
        cameraNode_->TranslateRelative(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('D'))
        cameraNode_->TranslateRelative(Vector3::RIGHT * MOVE_SPEED * timeStep);
}

void SkeletalAnimation::MoveModels(float timeStep)
{
    // We could store all the created models into our own array, like in the Sprites example. However, we can also query the
    // scene for all nodes with an AnimatedModel component. That is slightly slower, as each node's components have to be looped
    // through. We know the nodes are on the root level, so we do not need to do the query as recursive
    PODVector<Node*> modelNodes;
    scene_->GetChildrenWithComponent<AnimatedModel>(modelNodes);
    
    const float MODEL_MOVE_SPEED = 2.0f;
    const float MODEL_ROTATE_SPEED = 100.0f;
    
    for (unsigned i = 0; i < modelNodes.Size(); ++i)
    {
        Node* modelNode = modelNodes[i];
        modelNode->TranslateRelative(Vector3::FORWARD * MODEL_MOVE_SPEED * timeStep);
        
        // If in risk of going outside the plane, rotate the model right
        Vector3 pos = modelNode->GetPosition();
        if (pos.x_ < -47.0f || pos.x_ > 47.0f || pos.z_ < -47.0f || pos.z_ > 47.0f)
            modelNode->Yaw(timeStep * MODEL_ROTATE_SPEED);
        
        // Get the model's first (only) animation state and advance its time
        AnimationState* state = modelNode->GetComponent<AnimatedModel>()->GetAnimationStates()[0];
        state->AddTime(timeStep);
    }
}

void SkeletalAnimation::SubscribeToEvents()
{
    // Subscribes HandleUpdate() method for processing update events
    SubscribeToEvent(E_UPDATE, HANDLER(SkeletalAnimation, HandleUpdate));
    
    // Subscribes HandlePostRenderUpdate() method for processing the post-render update event, sent after Renderer subsystem is
    // done with defining the draw calls for the viewports (but before actually executing them)
    SubscribeToEvent(E_POSTRENDERUPDATE, HANDLER(SkeletalAnimation, HandlePostRenderUpdate));
}

void SkeletalAnimation::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Event parameters are always defined inside a namespace corresponding to the event's name
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    
    // Move the camera and the animating models, scale movement with time step
    MoveCamera(timeStep);
    MoveModels(timeStep);
    
    // Check for space pressed and toggle debug geometry
    if (GetSubsystem<Input>()->GetKeyPress(KEY_SPACE))
        drawDebug_ = !drawDebug_;
}

void SkeletalAnimation::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    // If draw debug mode is enabled, draw viewport debug geometry, which will show eg. drawable bounding boxes and skeleton
    // bones. Disable depth test so that we can see the bones properly
    if (drawDebug_)
        GetSubsystem<Renderer>()->DrawDebugGeometry(false);
}
