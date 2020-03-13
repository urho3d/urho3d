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
