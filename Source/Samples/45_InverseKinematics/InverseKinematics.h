// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "Sample.h"

namespace Urho3D
{
class AnimationController;
class Node;
class IKEffector;
class IKSolver;
class Scene;
}

/// Inverse Kinematics demo.
/// This sample demonstrates how to adjust the position of animated feet so they match the ground's angle using IK.
class InverseKinematics : public Sample
{
    URHO3D_OBJECT(InverseKinematics, Sample);

public:
    /// Construct.
    explicit InverseKinematics(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

protected:
    /// Animation controller of Jack.
    SharedPtr<Urho3D::AnimationController> jackAnimCtrl_;
    /// Inverse kinematic left effector.
    SharedPtr<Urho3D::IKEffector> leftEffector_;
    /// Inverse kinematic right effector.
    SharedPtr<Urho3D::IKEffector> rightEffector_;
    /// Inverse kinematic solver.
    SharedPtr<Urho3D::IKSolver> solver_;
    /// Need references to these nodes to calculate foot angles and offsets.
    SharedPtr<Urho3D::Node> leftFoot_;
    SharedPtr<Urho3D::Node> rightFoot_;
    SharedPtr<Urho3D::Node> jackNode_;
    /// So we can rotate the floor.
    SharedPtr<Urho3D::Node> floorNode_;
    float floorPitch_{};
    float floorRoll_{};
    /// Whether or not to draw debug geometry.
    bool drawDebug_{};

private:
    /// Construct the scene content.
    void CreateScene();
    /// Construct an instruction text to the UI.
    void CreateInstructions();
    /// Set up a viewport for displaying the scene.
    void SetupViewport();
    /// Read input and moves the camera.
    void UpdateCameraAndFloor(float timeStep);
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Draw debug geometry.
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);
    /// Process IK logic.
    void HandleSceneDrawableUpdateFinished(StringHash eventType, VariantMap& eventData);
    /// Camera node.
    SharedPtr<Node> cameraRotateNode_;
};
