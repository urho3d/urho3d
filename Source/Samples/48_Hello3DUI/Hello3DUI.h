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

class Window;

}

/// A 3D UI demonstration based on the HelloGUI sample. Renders UI alternatively
/// either to a 3D scene object using UIComponent, or directly to the backbuffer.
class Hello3DUI : public Sample
{
    URHO3D_OBJECT(Hello3DUI, Sample);

public:
    /// Construct.
    explicit Hello3DUI(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

protected:
    /// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
    String GetScreenJoystickPatchString() const override { return
        "<patch>"
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">"
        "        <attribute name=\"Is Visible\" value=\"false\" />"
        "    </add>"
        "</patch>";
    }

private:
    /// Create and initialize a Scene.
    void InitScene();
    /// Create and initialize a Window control.
    void InitWindow();
    /// Create and add various common controls for demonstration purposes.
    void InitControls();
    /// Create a draggable fish button.
    void CreateDraggableFish();
    /// Handle drag begin for the fish button.
    void HandleDragBegin(StringHash eventType, VariantMap& eventData);
    /// Handle drag move for the fish button.
    void HandleDragMove(StringHash eventType, VariantMap& eventData);
    /// Handle drag end for the fish button.
    void HandleDragEnd(StringHash eventType, VariantMap& eventData);
    /// Handle any UI control being clicked.
    void HandleControlClicked(StringHash eventType, VariantMap& eventData);
    /// Handle close button pressed and released.
    void HandleClosePressed(StringHash eventType, VariantMap& eventData);
    /// Animate cube.
    void HandleUpdate(StringHash, VariantMap& eventData);
    /// Create 3D UI.
    void Init3DUI();

    /// The Scene.
    SharedPtr<Scene> scene_;
    /// The Window.
    SharedPtr<Window> window_;
    /// The UI's root UIElement.
    SharedPtr<UIElement> uiRoot_;
    /// Remembered drag begin position.
    IntVector2 dragBeginPosition_;
    /// Root UI element of texture.
    SharedPtr<UIElement> textureRoot_;
    /// UI element with instructions.
    SharedPtr<Text> instructions_;
    /// Enable or disable cube rotation.
    bool animateCube_;
    /// Enable or disable rendering to texture.
    bool renderOnCube_;
    /// Draw debug information of last clicked element.
    bool drawDebug_;
    /// Last clicked UI element.
    WeakPtr<UIElement> current_;
};


