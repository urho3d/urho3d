//
// Copyright (c) 2008-2017 the Urho3D project.
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
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/RibbonTrail.h>
#include <Urho3D/IK/IKEffector.h>
#include <Urho3D/IK/IKSolver.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Text3D.h>

#include "InverseKinematics.h"

#include <Urho3D/DebugNew.h>

URHO3D_DEFINE_APPLICATION_MAIN(InverseKinematics)

InverseKinematics::InverseKinematics(Context* context) :
    Sample(context),
    timeStepSum_(0.0f)
{
}

void InverseKinematics::Start()
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
    Sample::InitMouseMode(MM_RELATIVE);

    GetSubsystem<Input>()->SetMouseVisible(true);
}

void InverseKinematics::CreateScene()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    scene_ = new Scene(context_);

    // Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_->CreateComponent<Octree>();

    // Create scene node & StaticModel component for showing a static plane
    Node* planeNode = scene_->CreateChild("Plane");
    planeNode->SetScale(Vector3(100.0f, 1.0f, 100.0f));
    StaticModel* planeObject = planeNode->CreateComponent<StaticModel>();
    planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));

    // Create a directional light to the world.
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f)); // The direction vector does not need to be normalized
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00005f, 0.5f));
    // Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));

    // Load Jack model and walking animation.
    Node* jackNode = scene_->CreateChild("Jack");
    jackNode->SetPosition(Vector3(5.0f, 0.0f, 0.0f));
    jackNode->SetRotation(Quaternion(0.0f, 180.0f, 0.0f));
    AnimatedModel* ninja = jackNode->CreateComponent<AnimatedModel>();
    ninja->SetModel(cache->GetResource<Model>("Models/Jack.mdl"));
    ninja->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
    ninja->SetCastShadows(true);

    // We need to attach two inverse kinematic effectors to Jack's feet to
    // control the grounding.
    Node* leftToe  = jackNode->GetChild("Bip01_L_Toe0", true);
    Node* rightToe = jackNode->GetChild("Bip01_R_Toe0", true);
    leftEffector_  = leftToe->CreateComponent<IKEffector>();
    rightEffector_ = rightToe->CreateComponent<IKEffector>();
    // Control 3 segments up to the hips
    leftEffector_->SetChainLength(3);
    rightEffector_->SetChainLength(3);

    // For the effectors to work, an IKSolver needs to be attached to one of
    // the parent nodes. Typically, you want to place the solver as close as
    // possible to the effectors for optimal performance. Since in this case
    // we're solving the legs only, we can place the solver at the spine.
    Node* spine = jackNode->GetChild("Bip01_Spine", true);
    IKSolver* solver = spine->CreateComponent<IKSolver>();

    // We want to solve for target rotations so the feet can be properly
    // rotated to match the incline. Sometimes, if the feet are small, this
    // isn't necessary. It does have a performance impact on the solver.
    solver->EnableTargetRotation(true);

    // Set the effectors so only the feet bones are affected by the target
    // rotation. This is accomplished by setting the rotation weight to 1 and
    // then decay by a factor of 0 so the next bone has weight 0.
    leftEffector_->SetRotationWeight(1.0);
    leftEffector_->SetRotationDecay(0.0);
    rightEffector_->SetRotationWeight(1.0);
    rightEffector_->SetRotationDecay(0.0);

    // Create animation controller and play walk animation
    jackAnimController_ = jackNode->CreateComponent<AnimationController>();
    jackAnimController_->PlayExclusive("Models/Jack_Walk.ani", 0, true, 0.0f);

    // Create the camera.
    cameraRotateNode_ = scene_->CreateChild("CameraAttach");
    cameraNode_ = cameraRotateNode_->CreateChild("Camera");
    cameraNode_->CreateComponent<Camera>();

    // Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(Vector3(0.0f, 0.0f, -14.0f));
    pitch_ = 5;
}

void InverseKinematics::CreateInstructions()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    // Construct new Text object, set string to display and font to use
    Text* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText("Use WASD keys and mouse/touch to move");
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void InverseKinematics::SetupViewport()
{
    Renderer* renderer = GetSubsystem<Renderer>();

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen. We need to define the scene and the camera
    // at minimum. Additionally we could configure the viewport screen size and the rendering path (eg. forward / deferred) to
    // use, but now we just use full screen and default render path configured in the engine command line options
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void InverseKinematics::MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (GetSubsystem<UI>()->GetFocusElement())
        return;

    Input* input = GetSubsystem<Input>();

    // Movement speed as world units per second
    const float MOVE_SPEED = 20.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    if (input->GetMouseButtonDown(MOUSEB_LEFT))
    {
        IntVector2 mouseMove = input->GetMouseMove();
        yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
        pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
        pitch_ = Clamp(pitch_, -90.0f, 90.0f);
    }

    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraRotateNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
}

void InverseKinematics::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(InverseKinematics, HandleUpdate));
}

void InverseKinematics::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);
}
