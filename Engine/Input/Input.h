//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
#include "Object.h"

class Graphics;

/// Input subsystem. Converts operating system window messages to input state and events
class Input : public Object
{
    OBJECT(Input);
    
public:
    /// Construct
    Input(Context* context);
    /// Destruct
    virtual ~Input();
    
    /// Poll for window messages. Called by HandleBeginFrame()
    void Update();
    /// Set whether mouse cursor is confined inside the window. Mouse delta movement is sent only when enabled, which is default.
    void SetClipCursor(bool enable);
    /// Set whether ALT-ENTER fullscreen Toggle is enabled
    void SetToggleFullscreen(bool enable);
    /// Set absolute mouse cursor position within the window. Only useful when the cursor is not confined
    void SetMousePosition(const IntVector2& position);
    /// Set absolute mouse cursor position within the window. Only useful when the cursor is not confined
    void SetMousePosition(int x, int y);
    /// Suppress the next char message
    void SuppressNextChar();
    
    /// Check if a key is held down
    bool GetKeyDown(int key) const;
    /// Check if a key has been pressed on this frame
    bool GetKeyPress(int key) const;
    /// Check if a mouse button is held down
    bool GetMouseButtonDown(int button) const;
    /// Check if a mouse button has been pressed on this frame
    bool GetMouseButtonPress(int button) const;
    /// Check if a qualifier key is held down
    bool GetQualifierDown(int qualifier) const;
    /// Check if a qualifier key has been pressed on this frame
    bool GetQualifierPress(int qualifier) const;
    /// Return the currently held down qualifiers
    int GetQualifiers() const;
    /// Return absolute mouse cursor position within the window. Only useful when the cursor is not confined
    IntVector2 GetMousePosition() const;
    /// Return mouse movement since last frame
    const IntVector2& GetMouseMove() const { return mouseMove_; }
    /// Return horizontal mouse movement since last frame
    int GetMouseMoveX() const { return mouseMove_.x_; }
    /// Return vertical mouse movement since last frame
    int GetMouseMoveY() const { return mouseMove_.y_; }
    /// Return mouse wheel movement since last frame
    int GetMouseMoveWheel() const { return mouseMoveWheel_; }
    /// Return whether mouse cursor is confined inside the window
    bool GetClipCursor() const { return clipCursor_; }
    /// Return whether fullscreen Toggle is enabled
    bool GetToggleFullscreen() const { return toggleFullscreen_; }
    /// Return whether application window is active
    bool IsActive() { return active_; }
    /// Return whether application window is minimized
    bool IsMinimized() { return minimized_; }
    
private:
    /// Initialize when screen mode initially set
    void Initialize();
    /// Activate the application
    void MakeActive();
    /// Deactivate the application
    void MakeInactive();
    /// Clear input state
    void ResetState();
    /// Handle a mouse button change
    void SetMouseButton(int button, bool newState);
    /// Handle a key change
    void SetKey(int key, int scanCode, bool newState);
    /// Handle mousewheel change
    void SetMouseWheel(int delta);
    /// Internal function to show/hide the operating system mouse cursor
    void SetCursorVisible(bool enable);
    #ifndef USE_SDL
    /// Handle window message event
    void HandleWindowMessage(StringHash eventType, VariantMap& eventData);
    #else
    /// Handle SDL event
    void HandleSDLEvent(void* sdlEvent);
    #endif
    /// Handle screen mode event
    void HandleScreenMode(StringHash eventType, VariantMap& eventData);
    /// Handle frame start event
    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);
    
    /// Graphics
    WeakPtr<Graphics> graphics_;
    /// Key down state
    HashSet<int> keyDown_;
    /// Key pressed state
    HashSet<int> keyPress_;
    /// Mouse buttons' down state
    unsigned mouseButtonDown_;
    /// Mouse buttons' pressed state
    unsigned mouseButtonPress_;
    /// Last mouse position for calculating deltas
    IntVector2 lastMousePosition_;
    /// Mouse movement since last frame
    IntVector2 mouseMove_;
    /// Mouse wheel movement since last frame
    int mouseMoveWheel_;
    /// Mouse cursor confine flag
    bool clipCursor_;
    /// Mouse cursor show/hide flag
    bool showCursor_;
    /// Fullscreen Toggle flag
    bool toggleFullscreen_;
    /// Active flag
    bool active_;
    /// Minimized flag
    bool minimized_;
    /// Activated on this frame flag
    bool activated_;
    /// Next char message suppress flag
    bool suppressNextChar_;
    /// Initialized flag
    bool initialized_;
};
