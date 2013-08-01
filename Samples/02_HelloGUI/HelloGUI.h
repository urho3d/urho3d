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

#include "Sample.h"
#include "Window.h"

using namespace Urho3D;

/// A simple 'HelloWorld' GUI created purely from code.
/// This sample demonstrates:
///     - Creation of controls and building a UI hierarchy;
///     - Loading UI style from XML and applying it to controls;
///     - Handling of global and per-control events;
class HelloGUI : public Sample
{
    OBJECT(HelloGUI)

public:
    /// Construct.
    HelloGUI(Context* context);

    /// Setup after engine initialization and before running the main loop.
    virtual void Start();

private:
    /// Creates and initializes a Window control.
    void InitWindow();

    /// Creates and add various common controls for demonstration purposes.
    void InitControls();

    /// Convenience method for event subscription.
    void SubscribeToEvents();

    /// Callback method invoked when a logic update event is dispatched.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    /// Callback method invoked whenever any control is clicked.
    void HandleControlClicked(StringHash eventType, VariantMap& eventData);

    /// Callback method invoked when the close button is pressed and released.
    void HandleClosePressed(StringHash eventType, VariantMap& eventData);

    /// The Window.
    SharedPtr<Window> window_;
    /// The UI's root UIElement.
    SharedPtr<UIElement> uiRoot_;
};


