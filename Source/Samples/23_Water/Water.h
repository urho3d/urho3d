//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include <Urho3D/Math/Plane.h>

#include "Sample.h"

namespace Urho3D
{

class Node;
class Scene;

}

/// Water example.
/// This sample demonstrates:
///     - Creating a large plane to represent a water body for rendering
///     - Setting up a second camera to render reflections on the water surface
class Water : public Sample
{
    URHO3D_OBJECT(Water, Sample);

public:
    /// Construct.
    Water(Context* context);

    /// Setup after engine initialization and before running the main loop.
    virtual void Start();

private:
    /// Construct the scene content.
    void CreateScene();
    /// Construct an instruction text to the UI.
    void CreateInstructions();
    /// Set up a viewport for displaying the scene.
    void SetupViewport();
    /// Subscribe to the logic update event.
    void SubscribeToEvents();
    /// Read input and moves the camera.
    void MoveCamera(float timeStep);
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    /// Reflection camera scene node.
    SharedPtr<Node> reflectionCameraNode_;
    /// Water body scene node.
    SharedPtr<Node> waterNode_;
    /// Reflection plane representing the water surface.
    Plane waterPlane_;
    /// Clipping plane for reflection rendering. Slightly biased downward from the reflection plane to avoid artifacts.
    Plane waterClipPlane_;
};
