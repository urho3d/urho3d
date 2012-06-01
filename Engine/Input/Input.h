//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include "Map.h"
#include "HashSet.h"
#include "InputEvents.h"
#include "Object.h"

class Graphics;

/// Structure for an ongoing finger touch.
struct TouchState
{
    /// Touch (finger) ID.
    int touchID_;
    /// Position in screen coordinates.
    IntVector2 position_;
    /// Movement since last frame.
    IntVector2 delta_;
    /// Finger pressure.
    int pressure_;
};

/// %Input subsystem. Converts operating system window messages to input state and events.
class Input : public Object
{
    OBJECT(Input);
    
public:
    /// Construct.
    Input(Context* context);
    /// Destruct.
    virtual ~Input();
    
    /// Poll for window messages. Called by HandleBeginFrame().
    void Update();
    /// %Set whether ALT-ENTER fullscreen toggle is enabled.
    void SetToggleFullscreen(bool enable);
    
    /// Check if a key is held down.
    bool GetKeyDown(int key) const;
    /// Check if a key has been pressed on this frame.
    bool GetKeyPress(int key) const;
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
    TouchState GetTouch(unsigned index) const;
    /// Return whether fullscreen toggle is enabled.
    bool GetToggleFullscreen() const { return toggleFullscreen_; }
    /// Return whether application window is active.
    bool IsActive() { return active_; }
    /// Return whether application window is minimized.
    bool IsMinimized() const;
    
private:
    /// Initialize when screen mode initially set.
    void Initialize();
    /// Activate the application.
    void MakeActive();
    /// Deactivate the application.
    void MakeInactive();
    /// Clear input state.
    void ResetState();
    /// Handle a mouse button change.
    void SetMouseButton(int button, bool newState);
    /// Handle a key change.
    void SetKey(int key, bool newState);
    /// Handle mousewheel change.
    void SetMouseWheel(int delta);
    /// Internal function to set the mouse cursor position.
    void SetCursorPosition(const IntVector2& position);
    /// Internal function to get the mouse cursor position.
    IntVector2 GetCursorPosition() const;
    #ifndef USE_OPENGL
    /// Internal function to clip the mouse cursor to the window.
    void SetClipCursor(bool enable);
    /// Internal function to show/hide the mouse cursor.
    void SetCursorVisible(bool enable);
    /// Handle window message event.
    void HandleWindowMessage(StringHash eventType, VariantMap& eventData);
    #endif
    /// Handle screen mode event.
    void HandleScreenMode(StringHash eventType, VariantMap& eventData);
    /// Handle frame start event.
    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);
    
    #ifdef USE_OPENGL
    /// Handle SDL event.
    static void HandleSDLEvent(void* sdlEvent);
    #endif
    
    /// Graphics subsystem.
    WeakPtr<Graphics> graphics_;
    /// Key down state.
    HashSet<int> keyDown_;
    /// Key pressed state.
    HashSet<int> keyPress_;
    /// Active finger touches.
    Map<int, TouchState> touches_;
    /// Mouse buttons' down state.
    unsigned mouseButtonDown_;
    /// Mouse buttons' pressed state.
    unsigned mouseButtonPress_;
    /// Last mouse position for calculating movement.
    IntVector2 lastCursorPosition_;
    /// Mouse movement since last frame.
    IntVector2 mouseMove_;
    /// Mouse wheel movement since last frame.
    int mouseMoveWheel_;
    #ifdef USE_OPENGL
    /// SDL window ID.
    unsigned windowID_;
    #else
    /// Mouse cursor show/hide flag.
    bool showCursor_;
    #endif
    /// Fullscreen toggle flag.
    bool toggleFullscreen_;
    /// Active flag.
    bool active_;
    /// Minimized flag.
    bool minimized_;
    /// Activated on this frame flag.
    bool activated_;
    /// Next mouse move suppress flag.
    bool suppressNextMouseMove_;
    /// Initialized flag.
    bool initialized_;
};
