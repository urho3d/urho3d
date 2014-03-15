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

#include "HashSet.h"
#include "InputEvents.h"
#include "Mutex.h"
#include "Object.h"

namespace Urho3D
{

class Graphics;

/// %Input state for a finger touch.
struct TouchState
{
    /// Touch (finger) ID.
    int touchID_;
    /// Position in screen coordinates.
    IntVector2 position_;
    /// Last position in screen coordinates.
    IntVector2 lastPosition_;
    /// Movement since last frame.
    IntVector2 delta_;
    /// Finger pressure.
    float pressure_;
};

/// %Input state for a joystick.
struct JoystickState
{
    /// Construct with defaults.
    JoystickState() :
        joystick_(0), controller_(0)
    {
    }
    
    /// Return number of buttons.
    unsigned GetNumButtons() const { return buttons_.Size(); }
    /// Return number of axes.
    unsigned GetNumAxes() const { return axes_.Size(); }
    /// Return number of hats.
    unsigned GetNumHats() const { return hats_.Size(); }
    
    /// Check if a button is held down.
    bool GetButtonDown(unsigned index) const
    {
        if (index < buttons_.Size())
            return buttons_[index];
        else
            return false;
    }
    
    /// Check if a button has been pressed on this frame.
    bool GetButtonPress(unsigned index) const
    {
        if (index < buttons_.Size())
            return buttonPress_[index];
        else
            return false;
    }
    
    /// Return axis position.
    float GetAxisPosition(unsigned index) const
    {
        if (index < axes_.Size())
            return axes_[index];
        else
            return 0.0f;
    }
    
    /// Return hat position.
    int GetHatPosition(unsigned index) const
    {
        if (index < hats_.Size())
            return hats_[index];
        else
            return HAT_CENTER;
    }
    
    /// SDL joystick.
    SDL_Joystick* joystick_;
    /// SDL game controller
    SDL_GameController* controller_;
    /// Joystick name.
    String name_;
    /// Button up/down state.
    PODVector<bool> buttons_;
    /// Button pressed on this frame.
    PODVector<bool> buttonPress_;
    /// Axis position from -1 to 1.
    PODVector<float> axes_;
    /// POV hat bits.
    PODVector<int> hats_;
};

/// %Input subsystem. Converts operating system window messages to input state and events.
class URHO3D_API Input : public Object
{
    OBJECT(Input);
    
public:
    /// Construct.
    Input(Context* context);
    /// Destruct.
    virtual ~Input();
    
    /// Poll for window messages. Called by HandleBeginFrame().
    void Update();
    /// Set whether ALT-ENTER fullscreen toggle is enabled.
    void SetToggleFullscreen(bool enable);
    /// Set whether the operating system mouse cursor is visible. When not visible (default), is kept centered to prevent leaving the window.
    void SetMouseVisible(bool enable);
    /// Open a joystick. Return true if successful.
    bool OpenJoystick(unsigned index);
    /// Close a joystick.
    void CloseJoystick(unsigned index);
    /// Redetect joysticks. Return true if successful.
    bool DetectJoysticks();
    /// Show or hide on-screen keyboard on platforms that support it. When shown, keypresses from it are delivered as key events.
    void SetScreenKeyboardVisible(bool enable);
    
    /// Return keycode from key name.
    int GetKeyFromName(const String& name) const;
    /// Return keycode from scancode.
    int GetKeyFromScancode(int scancode) const;
    /// Return name of key from keycode.
    String GetKeyName(int key) const;
    /// Return scancode from keycode.
    int GetScancodeFromKey(int key) const;
    /// Return scancode from key name.
    int GetScancodeFromName(const String& name) const;
    /// Return name of key from scancode.
    String GetScancodeName(int scancode) const;
    /// Check if a key is held down.
    bool GetKeyDown(int key) const;
    /// Check if a key has been pressed on this frame.
    bool GetKeyPress(int key) const;
    /// Check if a key is held down by scancode.
    bool GetScancodeDown(int scancode) const;
    /// Check if a key has been pressed on this frame by scancode.
    bool GetScancodePress(int scanode) const;
    /// Check if a mouse button is held down.
    bool GetMouseButtonDown(int button) const;
    /// Check if a mouse button has been pressed on this frame.
    bool GetMouseButtonPress(int button) const;
    /// Check if a qualifier key is held down.
    bool GetQualifierDown(int qualifier) const;
    /// Check if a qualifier key has been pressed on this frame.
    bool GetQualifierPress(int qualifier) const;
    /// Return the currently held down qualifiers.
    int GetQualifiers() const;
    /// Return mouse position within window. Should only be used with a visible mouse cursor.
    IntVector2 GetMousePosition() const;
    /// Return mouse movement since last frame.
    const IntVector2& GetMouseMove() const { return mouseMove_; }
    /// Return horizontal mouse movement since last frame.
    int GetMouseMoveX() const { return mouseMove_.x_; }
    /// Return vertical mouse movement since last frame.
    int GetMouseMoveY() const { return mouseMove_.y_; }
    /// Return mouse wheel movement since last frame.
    int GetMouseMoveWheel() const { return mouseMoveWheel_; }
    /// Return number of active finger touches.
    unsigned GetNumTouches() const { return touches_.Size(); }
    /// Return active finger touch by index.
    TouchState* GetTouch(unsigned index) const;
    /// Return number of connected joysticks.
    unsigned GetNumJoysticks() const { return joysticks_.Size(); }
    /// Return joystick name by index.
    const String& GetJoystickName(unsigned index) const;
    /// Return joystick state by index. Automatically open if not opened yet.
    JoystickState* GetJoystick(unsigned index);
    /// Return whether fullscreen toggle is enabled.
    bool GetToggleFullscreen() const { return toggleFullscreen_; }
    /// Return whether on-screen keyboard is supported.
    bool GetScreenKeyboardSupport() const;
    /// Return whether on-screen keyboard is being shown.
    bool IsScreenKeyboardVisible() const;
    /// Return whether the operating system mouse cursor is visible.
    bool IsMouseVisible() const { return mouseVisible_; }
    /// Return whether application window has input focus.
    bool HasFocus() { return inputFocus_; }
    /// Return whether application window is minimized.
    bool IsMinimized() const;
    
private:
    /// Initialize when screen mode initially set.
    void Initialize();
    /// Setup internal joystick structures.
    void ResetJoysticks();
    /// Prepare input state for application gaining input focus.
    void GainFocus();
    /// Prepare input state for application losing input focus.
    void LoseFocus();
    /// Clear input state.
    void ResetState();
    /// Send an input focus or window minimization change event.
    void SendInputFocusEvent();
    /// Handle a mouse button change.
    void SetMouseButton(int button, bool newState);
    /// Handle a key change.
    void SetKey(int key, int scancode, unsigned raw, bool newState);
    /// Handle mousewheel change.
    void SetMouseWheel(int delta);
    /// Internal function to set the mouse cursor position.
    void SetMousePosition(const IntVector2& position);
    /// Handle screen mode event.
    void HandleScreenMode(StringHash eventType, VariantMap& eventData);
    /// Handle frame start event.
    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);
    /// Handle SDL event.
    void HandleSDLEvent(void* sdlEvent);
    
    /// Graphics subsystem.
    WeakPtr<Graphics> graphics_;
    /// Key down state.
    HashSet<int> keyDown_;
    /// Key pressed state.
    HashSet<int> keyPress_;
    /// Key down state by scancode.
    HashSet<int> scancodeDown_;
    /// Key pressed state by scancode.
    HashSet<int> scancodePress_;
    /// Active finger touches.
    HashMap<int, TouchState> touches_;
    /// String for text input.
    String textInput_;
    /// Opened joysticks.
    Vector<JoystickState> joysticks_;
    /// Mouse buttons' down state.
    unsigned mouseButtonDown_;
    /// Mouse buttons' pressed state.
    unsigned mouseButtonPress_;
    /// Last mouse position for calculating movement.
    IntVector2 lastMousePosition_;
    /// Mouse movement since last frame.
    IntVector2 mouseMove_;
    /// Mouse wheel movement since last frame.
    int mouseMoveWheel_;
    /// SDL window ID.
    unsigned windowID_;
    /// Fullscreen toggle flag.
    bool toggleFullscreen_;
    /// Operating system mouse cursor visible flag.
    bool mouseVisible_;
    /// Input focus flag.
    bool inputFocus_;
    /// Minimized flag.
    bool minimized_;
    /// Gained focus on this frame flag.
    bool focusedThisFrame_;
    /// Next mouse move suppress flag.
    bool suppressNextMouseMove_;
    /// Initialized flag.
    bool initialized_;
    /// Map SDL joystick ID to internal index.
    HashMap<int, unsigned> joystickIDMap_;
};

}
