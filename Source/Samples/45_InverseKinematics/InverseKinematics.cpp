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

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/RibbonTrail.h>
#include <Urho3D/IK/IKEffector.h>
#include <Urho3D/IK/IKSolver.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Math/Matrix2.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Text3D.h>

#include "InverseKinematics.h"

#include <Urho3D/DebugNew.h>

URHO3D_DEFINE_APPLICATION_MAIN(InverseKinematics)

InverseKinematics::InverseKinematics(Context* context) :
    Sample(context)
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
    auto* cache = GetSubsystem<ResourceCache>();

    scene_ = new Scene(context_);

    // Create octree, use default volume (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<DebugRenderer>();
    scene_->CreateComponent<PhysicsWorld>();

    // Create scene node & StaticModel component for showing a static plane
    floorNode_ = scene_->CreateChild("Plane");
    floorNode_->SetScale(Vector3(50.0f, 1.0f, 50.0f));
    auto* planeObject = floorNode_->CreateComponent<StaticModel>();
    planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));

    // Set up collision, we need to raycast to determine foot height
    floorNode_->CreateComponent<RigidBody>();
    auto* col = floorNode_->CreateComponent<CollisionShape>();
    col->SetBox(Vector3(1, 0, 1));

    // Create a directional light to the world.
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f)); // The direction vector does not need to be normalized
    auto* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00005f, 0.5f));
    // Set cascade splits at 10, 50 and 200 world units, fade shadows out at 80% of maximum shadow distance
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));

    // Load Jack model
    jackNode_ = scene_->CreateChild("Jack");
    jackNode_->SetRotation(Quaternion(0.0f, 270.0f, 0.0f));
    auto* jack = jackNode_->CreateComponent<AnimatedModel>();
    jack->SetModel(cache->GetResource<Model>("Models/Jack.mdl"));
    jack->SetMaterial(cache->GetResource<Material>("Materials/Jack.xml"));
    jack->SetCastShadows(true);

    // Create animation controller and play walk animation
    jackAnimCtrl_ = jackNode_->CreateComponent<AnimationController>();
    jackAnimCtrl_->PlayExclusive("Models/Jack_Walk.ani", 0, true, 0.0f);

    // We need to attach two inverse kinematic effectors to Jack's feet to
    // control the grounding.
    leftFoot_  = jackNode_->GetChild("Bip01_L_Foot", true);
    rightFoot_ = jackNode_->GetChild("Bip01_R_Foot", true);
    leftEffector_  = leftFoot_->CreateComponent<IKEffector>();
    rightEffector_ = rightFoot_->CreateComponent<IKEffector>();
    // Control 2 segments up to the hips
    leftEffector_->SetChainLength(2);
    rightEffector_->SetChainLength(2);

    // For the effectors to work, an IKSolver needs to be attached to one of
    // the parent nodes. Typically, you want to place the solver as close as
    // possible to the effectors for optimal performance. Since in this case
    // we're solving the legs only, we can place the solver at the spine.
    Node* spine = jackNode_->GetChild("Bip01_Spine", true);
    solver_ = spine->CreateComponent<IKSolver>();

    // Two-bone solver is more efficient and more stable than FABRIK (but only
    // works for two bones, obviously).
    solver_->SetAlgorithm(IKSolver::TWO_BONE);

    // Disable auto-solving, which means we need to call Solve() manually
    solver_->SetFeature(IKSolver::AUTO_SOLVE, false);

    // Only enable this so the debug draw shows us the pose before solving.
    // This should NOT be enabled for any other reason (it does nothing and is
    // a waste of performance).
    solver_->SetFeature(IKSolver::UPDATE_ORIGINAL_POSE, true);

    // Create the camera.
    cameraRotateNode_ = scene_->CreateChild("CameraRotate");
    cameraNode_ = cameraRotateNode_->CreateChild("Camera");
    cameraNode_->CreateComponent<Camera>();

    // Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(Vector3(0, 0, -4));
    cameraRotateNode_->SetPosition(Vector3(0, 0.4, 0));
    pitch_ = 20;
    yaw_ = 50;
}

void InverseKinematics::CreateInstructions()
{
    auto* cache = GetSubsystem<ResourceCache>();
    auto* ui = GetSubsystem<UI>();

    // Construct new Text object, set string to display and font to use
    auto* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText("Left-Click and drag to look around\nRight-Click and drag to change incline\nPress space to reset floor\nPress D to draw debug geometry");
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void InverseKinematics::SetupViewport()
{
    auto* renderer = GetSubsystem<Renderer>();

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen. We need to define the scene and the camera
    // at minimum. Additionally we could configure the viewport screen size and the rendering path (eg. forward / deferred) to
    // use, but now we just use full screen and default render path configured in the engine command line options
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void InverseKinematics::UpdateCameraAndFloor(float /*timeStep*/)
{
    // Do not move if the UI has a focused element (the console)
    if (GetSubsystem<UI>()->GetFocusElement())
        return;

    auto* input = GetSubsystem<Input>();

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

    if (input->GetMouseButtonDown(MOUSEB_RIGHT))
    {
        IntVector2 mouseMoveInt = input->GetMouseMove();
        Vector2 mouseMove = Matrix2(
            -Cos(yaw_), Sin(yaw_),
            Sin(yaw_),  Cos(yaw_)
        ) * Vector2(mouseMoveInt.y_, -mouseMoveInt.x_);
        floorPitch_ += MOUSE_SENSITIVITY * mouseMove.x_;
        floorPitch_ = Clamp(floorPitch_, -90.0f, 90.0f);
        floorRoll_ += MOUSE_SENSITIVITY * mouseMove.y_;
    }

    if (input->GetKeyPress(KEY_SPACE))
    {
        floorPitch_ = 0;
        floorRoll_ = 0;
    }

    if (input->GetKeyPress(KEY_D))
    {
        drawDebug_ = !drawDebug_;
    }

    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraRotateNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
    floorNode_->SetRotation(Quaternion(floorPitch_, 0, floorRoll_));
}

void InverseKinematics::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(InverseKinematics, HandleUpdate));
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(InverseKinematics, HandlePostRenderUpdate));
    SubscribeToEvent(E_SCENEDRAWABLEUPDATEFINISHED, URHO3D_HANDLER(InverseKinematics, HandleSceneDrawableUpdateFinished));
}

void InverseKinematics::HandleUpdate(StringHash /*eventType*/, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Move the camera, scale movement with time step
    UpdateCameraAndFloor(timeStep);
}

void InverseKinematics::HandlePostRenderUpdate(StringHash /*eventType*/, VariantMap& eventData)
{
    if (drawDebug_)
        solver_->DrawDebugGeometry(false);
}

void InverseKinematics::HandleSceneDrawableUpdateFinished(StringHash /*eventType*/, VariantMap& eventData)
{
    auto* phyWorld = scene_->GetComponent<PhysicsWorld>();
    Vector3 leftFootPosition = leftFoot_->GetWorldPosition();
    Vector3 rightFootPosition = rightFoot_->GetWorldPosition();

    // Cast ray down to get the normal of the underlying surface
    PhysicsRaycastResult result;
    phyWorld->RaycastSingle(result, Ray(leftFootPosition + Vector3(0, 1, 0), Vector3(0, -1, 0)), 2);
    if (result.body_)
    {
        // Cast again, but this time along the normal. Set the target position
        // to the ray intersection
        phyWorld->RaycastSingle(result, Ray(leftFootPosition + result.normal_, -result.normal_), 2);
        // The foot node has an offset relative to the root node
        float footOffset = leftFoot_->GetWorldPosition().y_ - jackNode_->GetWorldPosition().y_;
        leftEffector_->SetTargetPosition(result.position_ + result.normal_ * footOffset);
        // Rotate foot according to normal
        leftFoot_->Rotate(Quaternion(Vector3(0, 1, 0), result.normal_), TS_WORLD);
    }

    // Same deal with the right foot
    phyWorld->RaycastSingle(result, Ray(rightFootPosition + Vector3(0, 1, 0), Vector3(0, -1, 0)), 2);
    if (result.body_)
    {
        phyWorld->RaycastSingle(result, Ray(rightFootPosition + result.normal_, -result.normal_), 2);
        float footOffset = rightFoot_->GetWorldPosition().y_ - jackNode_->GetWorldPosition().y_;
        rightEffector_->SetTargetPosition(result.position_ + result.normal_ * footOffset);
        rightFoot_->Rotate(Quaternion(Vector3(0, 1, 0), result.normal_), TS_WORLD);
    }

    solver_->Solve();
}
