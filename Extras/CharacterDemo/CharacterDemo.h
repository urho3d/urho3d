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

#pragma once

#include "Application.h"

using namespace Urho3D;

namespace Urho3D
{
    class Node;
    class ResourceCache;
    class Scene;
}

class Character;

class CharacterDemo : public Application
{
    OBJECT(CharacterDemo);

public:
    /// Construct.
    CharacterDemo(Context* context);
    
    /// Setup after engine initialization and before running the main loop.
    virtual int Start();
    
private:
    /// Create static scene content.
    void CreateScene();
    /// Create controllable character.
    void CreateCharacter();
    /// Subscribe to necessary events.
    void SubscribeToEvents();
    /// Handle application update. Set controls to character & check global keys.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle application post-update. Update camera position after character has moved.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Scene.
    SharedPtr<Scene> scene_;
    /// Resource cache subsystem, stored here for convenience.
    SharedPtr<ResourceCache> cache_;
    /// Camera scene node.
    SharedPtr<Node> cameraNode_;
    /// The controllable character.
    WeakPtr<Character> character_;
    /// First person camera flag.
    bool firstPerson_;
};
