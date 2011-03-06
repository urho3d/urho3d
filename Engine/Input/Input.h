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

#ifndef INPUT_INPUT_H
#define INPUT_INPUT_H

#include "EventListener.h"
#include "InputEvents.h"
#include "SharedPtr.h"

class Renderer;

static const int MAX_KEYS = 256;

//! Converts operating system window messages to input state and events
class Input : public RefCounted, public EventListener
{
public:
    //! Construct with renderer subsystem pointer
    Input(Renderer* renderer);
    //! Destruct
    virtual ~Input();
    
    //! Poll for window messages. Called by Engine each frame
    void update();
    //! Set whether mouse cursor is confined inside the window. Mouse delta movement is sent only when enabled, which is default.
    void setClipCursor(bool enable);
    //! Set whether ALT-ENTER fullscreen toggle is enabled
    void setToggleFullscreen(bool enable);
    //! Set absolute mouse cursor position within the window. Only useful when the cursor is not confined
    void setMousePosition(const IntVector2& position);
    //! Set absolute mouse cursor position within the window. Only useful when the cursor is not confined
    void setMousePosition(int x, int y);
    //! Suppress the next char message
    void suppressNextChar();
    
    //! Check if a key is held down
    bool getKeyDown(int key) const;
    //! Check if a key has been pressed on this frame
    bool getKeyPress(int key) const;
    //! Check if a mouse button is held down
    bool getMouseButtonDown(int button) const;
    //! Check if a mouse button has been pressed on this frame
    bool getMouseButtonPress(int button) const;
    //! Check if a qualifier key is held down
    bool getQualifierDown(int qualifier) const;
    //! Check if a qualifier key has been pressed on this frame
    bool getQualifierPress(int qualifier) const;
    //! Return the currently held down qualifiers
    int getQualifiers() const;
    //! Return absolute mouse cursor position within the window. Only useful when the cursor is not confined
    IntVector2 getMousePosition() const;
    //! Return mouse movement since last frame. When mouse is not confined, returns always zero
    const IntVector2& getMouseMove() const { return mMouseMove; }
    //! Return horizontal mouse movement since last frame. When mouse is not confined, returns always zero
    int getMouseMoveX() const { return mMouseMove.mX; }
    //! Return vertical mouse movement since last frame. When mouse is not confined, returns always zero
    int getMouseMoveY() const { return mMouseMove.mY; }
    //! Return mouse wheel movement since last frame
    int getMouseMoveWheel() const { return mMouseMoveWheel; }
    //! Return whether mouse cursor is confined inside the window
    bool getClipCursor() const { return mClipCursor; }
    //! Return whether fullscreen toggle is enabled
    bool getToggleFullscreen() const { return mToggleFullscreen; }
    //! Return whether application window is active
    bool isActive() { return mActive; }
    //! Return whether application window is minimized
    bool isMinimized() { return mMinimized; }
    
private:
    //! Handle a window message event
    void handleWindowMessage(StringHash eventType, VariantMap& eventData);
    //! Activate the application
    void makeActive();
    //! Deactivate the application
    void makeInactive();
    //! Clear input state
    void clearState();
    //! Handle a mouse button change
    void mouseButtonChange(int button, bool newState);
    //! Handle a key change
    void keyChange(int key, bool newState);
    
    //! Renderer subsystem
    SharedPtr<Renderer> mRenderer;
    //! Key down state
    bool mKeyDown[MAX_KEYS];
    //! Key pressed state
    bool mKeyPress[MAX_KEYS];
    //! Mouse buttons' down state
    unsigned mMouseButtonDown;
    //! Mouse buttons' pressed state
    unsigned mMouseButtonPress;
    //! Last mouse position for non-confined mode
    IntVector2 mLastMousePosition;
    //! Mouse movement since last frame
    IntVector2 mMouseMove;
    //! Mouse wheel movement since last frame
    int mMouseMoveWheel;
    //! Mouse cursor confine flag
    bool mClipCursor;
    //! Fullscreen toggle flag
    bool mToggleFullscreen;
    //! Active flag
    bool mActive;
    //! Minimized flag
    bool mMinimized;
    //! Activated on this frame flag
    bool mActivated;
    //! Next char message suppress flag
    bool mSuppressNextChar;
};

#endif // INPUT_INPUT_H
