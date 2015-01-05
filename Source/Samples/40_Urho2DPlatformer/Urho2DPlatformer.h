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

#pragma once

#include "Sample.h"
#include "Sample2D.h"

namespace Urho3D
{
    class Node;
    class Scene;
}

class Character2D;
class Sample2D;

/// Urho2D platformer example.
/// This sample demonstrates:
///    - Creating an orthogonal 2D scene with tile map
///    - Displaying the scene using the Renderer subsystem
///    - Handling keyboard to move a character and zoom 2D camera
///    - Generating physics shapes from the tmx file's objects
///    - Using physics to move the character
/// Note that this sample uses some functions from Sample2D utility class.
class Urho2DPlatformer : public Sample
{
    OBJECT(Urho2DPlatformer);

public:
    /// Construct.
    Urho2DPlatformer(Context* context);

    /// Setup after engine initialization and before running the main loop.
    virtual void Start();



private:
    /// Construct the scene content.
    void CreateScene();
    /// Construct an instruction text to the UI.
    void CreateInstructions();
    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the logic post update event.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle the post render update event.
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);
    /// Create an enemy (will be cloned at each tmx placeholder).
    Node* CreateEnemy();
    /// Create a coin (will be cloned at each tmx placeholder).
    Node* CreateCoin();
    /// Create a moving platform (will be cloned at each tmx placeholder).
    Node* CreateMovingPlatform();

    /// The controllable character component.
    WeakPtr<Character2D> character2D_;
    /// Flag for drawing debug geometry.
    bool drawDebug_;
    /// Scaling factor based on tiles' aspect ratio.
    float moveSpeedScale_;

    /// Sample2D utility object.
    SharedPtr<Sample2D> sample2D_;
};