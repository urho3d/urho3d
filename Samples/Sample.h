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
#include "Sprite.h"

// All Urho3D classes reside in namespace Urho3D
using namespace Urho3D;

/// Sample class, as framework for all samples.
///    - Initialization of the Urho3D engine (in Application class)
///    - Modify engine parameters for windowed mode and to show the class name as title
///    - Create Urho3D logo at screen;
///    - Create Console and Debug HUD, and use F1 and F2 key to toggle them;
///    - Handle Esc key down to hide Console or exit application;
class Sample : public Application
{
    // Mandatory when deriving from Object, enables type information
    OBJECT(Sample)

public:
    /// Construct.
    Sample(Context* context);

    /// Setup before engine initialization. Modifies the engine parameters.
    virtual void Setup();

    /// Setup after engine initialization. Creates the logo, console & debug HUD.
    virtual void Start();

    /// Control logo visibility.
    void SetLogoVisible(bool enable);

protected:
    /// Logo sprite.
    SharedPtr<Sprite> logoSprite_;

private:
    /// Create logo.
    void CreateLogo();

    /// Create console and debug HUD.
    void CreateConsoleAndDebugHud();

    /// Handle key down event.
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);
};

#include "Sample.inl"
