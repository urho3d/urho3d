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

#include "Object.h"
#include "Scene.h"
#include "ResourceCache.h"

// All Urho3D classes reside in namespace Urho3D
using namespace Urho3D;

/// This first example, maintaining tradition, prints a "Hello World" message.
/// Furthermore it shows:
///     - Initialization of the Urho3D engine;
///     - Adding a Text element to the graphical user interface;
///     - Subscribing to and handling of update events;
class HelloWorld : public Object
{
    // Mandatory when deriving from Object, enables type information
    OBJECT(HelloWorld)

public:
    /// Construct.
    HelloWorld(Context* context);

private:
    /// Constructs a new Text instance, containing the 'Hello World' String, and
    /// adds it to the UI root element.
    void CreateText();

    /// Subscribe to application-wide logic update events.
    void SubscribeToEvents();

    /// Callback method invoked when a logic update event is dispatched.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    /// Handle to ResourceCache instance for loading the used Font.
    SharedPtr<ResourceCache> cache_;
};
