// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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


