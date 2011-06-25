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

#include "Context.h"
#include "CoreEvents.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "Input.h"
#include "Log.h"
#include "Profiler.h"

#include <cstring>

#ifndef USE_OPENGL
#include <Windows.h>
#else
#include <GL/glfw.h>

static Input* inputInstance = 0;
#endif

#include "DebugNew.h"

OBJECTTYPESTATIC(Input);

Input::Input(Context* context) :
    Object(context),
    showCursor_(true),
    toggleFullscreen_(true),
    active_(false),
    minimized_(false),
    activated_(false),
    suppressNextChar_(false),
    initialized_(false)
{
    // Zero the initial state
    mouseButtonDown_ = 0;
    mouseButtonPress_ = 0;
    lastCursorPosition_ = IntVector2::ZERO;
    
    #ifndef USE_OPENGL
    SubscribeToEvent(E_WINDOWMESSAGE, HANDLER(Input, HandleWindowMessage));
    #else
    // GLFW callbacks do not include userdata, so a static instance pointer is necessary
    inputInstance = this;
    #endif
    
    SubscribeToEvent(E_SCREENMODE, HANDLER(Input, HandleScreenMode));
    SubscribeToEvent(E_BEGINFRAME, HANDLER(Input, HandleBeginFrame));
    
    // Try to initialize right now, but skip if screen mode is not yet set
    Initialize();
}

Input::~Input()
{
}

void Input::Update()
{
    PROFILE(UpdateInput);
    
    if (!graphics_)
        return;
    
    // Reset current state
    keyPress_.Clear();
    mouseButtonPress_ = 0;
    mouseMove_ = IntVector2::ZERO;
    mouseMoveWheel_ = 0;
    
    #ifndef USE_OPENGL
    // Pump Win32 events
    MSG msg;
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    #else
    // Pump GLFW events
    glfwPollEvents();
    
    // Check state
    if (glfwGetWindowParam(GLFW_ACTIVE))
    {
        if (!active_)
            activated_ = true;
    }
    else
    {
        if (active_)
            MakeInactive();
    }
    #endif
    
    // Activate application now if necessary
    if (activated_)
        MakeActive();
    
    // Finally send the mouse move event if motion has been accumulated
    if (active_)
    {
        #ifndef USE_OPENGL
        IntVector2 mousePos = GetCursorPosition();
        mouseMove_ = mousePos - lastCursorPosition_;
        
        // Recenter the mouse cursor manually if it moved
        if (mouseMove_ != IntVector2::ZERO)
        {
            IntVector2 center(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2);
            SetCursorPosition(center);
            lastCursorPosition_ = GetCursorPosition();
        }
        else
            lastCursorPosition_ = mousePos;
        #else
        IntVector2 mousePos = GetCursorPosition();
        mouseMove_ = mousePos - lastCursorPosition_;
        lastCursorPosition_ = mousePos;
        #endif
        
        if (mouseMove_ != IntVector2::ZERO)
        {
            using namespace MouseMove;
            
            VariantMap eventData;
            eventData[P_DX] = mouseMove_.x_;
            eventData[P_DY] = mouseMove_.y_;
            eventData[P_BUTTONS] = mouseButtonDown_;
            eventData[P_QUALIFIERS] = GetQualifiers();
            SendEvent(E_MOUSEMOVE, eventData);
        }
    }
}

void Input::SetToggleFullscreen(bool enable)
{
    toggleFullscreen_ = enable;
}

void Input::SuppressNextChar()
{
    suppressNextChar_ = true;
}

bool Input::GetKeyDown(int key) const
{
    return keyDown_.Contains(key);
}

bool Input::GetKeyPress(int key) const
{
    return keyPress_.Contains(key);
}

bool Input::GetMouseButtonDown(int button) const
{
    return (mouseButtonDown_ & button) != 0;
}

bool Input::GetMouseButtonPress(int button) const
{
    return (mouseButtonPress_ & button) != 0;
}

bool Input::GetQualifierDown(int qualifier) const
{
    #ifndef USE_OPENGL
    if (qualifier == QUAL_SHIFT)
        return GetKeyDown(KEY_SHIFT);
    if (qualifier == QUAL_CTRL)
        return GetKeyDown(KEY_CTRL);
    if (qualifier == QUAL_ALT)
        return GetKeyDown(KEY_ALT);
    #else
    if (qualifier == QUAL_SHIFT)
        return GetKeyDown(KEY_LSHIFT) || GetKeyDown(KEY_RSHIFT);
    if (qualifier == QUAL_CTRL)
        return GetKeyDown(KEY_LCTRL) || GetKeyDown(KEY_RCTRL);
    if (qualifier == QUAL_ALT)
        return GetKeyDown(KEY_LALT) || GetKeyDown(KEY_RALT);
    #endif
    return false;
}

bool Input::GetQualifierPress(int qualifier) const
{
    #ifndef USE_OPENGL
    if (qualifier == QUAL_SHIFT)
        return GetKeyPress(KEY_SHIFT);
    if (qualifier == QUAL_CTRL)
        return GetKeyPress(KEY_CTRL);
    if (qualifier == QUAL_ALT)
        return GetKeyPress(KEY_ALT);
    #else
    if (qualifier == QUAL_SHIFT)
        return GetKeyPress(KEY_LSHIFT) || GetKeyPress(KEY_RSHIFT);
    if (qualifier == QUAL_CTRL)
        return GetKeyPress(KEY_LCTRL) || GetKeyPress(KEY_RCTRL);
    if (qualifier == QUAL_ALT)
        return GetKeyPress(KEY_LALT) || GetKeyPress(KEY_RALT);
    #endif
    return false;
}

int Input::GetQualifiers() const
{
    int ret = 0;
    if (GetQualifierDown(QUAL_SHIFT))
        ret |= QUAL_SHIFT;
    if (GetQualifierDown(QUAL_CTRL))
        ret |= QUAL_CTRL;
    if (GetQualifierDown(QUAL_ALT))
        ret |= QUAL_ALT;
    return ret;
}

void Input::Initialize()
{
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics || !graphics->IsInitialized())
        return;
    
    graphics_ = graphics;
    
    // Set the initial activation
    MakeActive();
    #ifndef USE_OPENGL
    SetClipCursor(true);
    SetCursorVisible(false);
    #endif
    
    initialized_ = true;
    
    LOGINFO("Initialized input");
}

void Input::MakeActive()
{
    if (!graphics_)
        return;
    
    ResetState();
    
    active_ = true;
    activated_ = false;
    
    // Re-establish mouse cursor clipping as necessary
    #ifndef USE_OPENGL
    SetClipCursor(true);
    SetCursorVisible(false);
    #else
    // Get the current mouse position as a base for movement calculations
    lastCursorPosition_ = GetCursorPosition();
    #endif
    
    using namespace Activation;
    
    VariantMap eventData;
    eventData[P_ACTIVE] = active_;
    eventData[P_MINIMIZED] = minimized_;
    SendEvent(E_ACTIVATION, eventData);
}

void Input::MakeInactive()
{
    if (!graphics_)
        return;
    
    ResetState();
    
    active_ = false;
    activated_ = false;
    
    // Free and show the mouse cursor
    #ifndef USE_OPENGL
    ReleaseCapture();
    ClipCursor(0);
    SetCursorVisible(true);
    #endif
    
    using namespace Activation;
    
    VariantMap eventData;
    eventData[P_ACTIVE] = active_;
    eventData[P_MINIMIZED] = minimized_;
    SendEvent(E_ACTIVATION, eventData);
}

void Input::ResetState()
{
    keyDown_.Clear();
    keyPress_.Clear();
    
    // Use SetMouseButton() to reset the state so that mouse events will be sent properly
    SetMouseButton(MOUSEB_LEFT, false);
    SetMouseButton(MOUSEB_RIGHT, false);
    SetMouseButton(MOUSEB_MIDDLE, false);
    
    mouseMove_ = IntVector2::ZERO;
    mouseMoveWheel_ = 0;
    mouseButtonPress_ = 0;
}

void Input::SetMouseButton(int button, bool newState)
{
    // If we are not active yet, do not react to the mouse button down
    if (newState && !active_)
        return;
    
    if (newState)
    {
        if (!(mouseButtonDown_ & button))
            mouseButtonPress_ |= button;
        
        mouseButtonDown_ |= button;
    }
    else
    {
        if (!(mouseButtonDown_ & button))
            return;
        
        mouseButtonDown_ &= ~button;
    }
    
    using namespace MouseButtonDown;
    
    VariantMap eventData;
    eventData[P_BUTTON] = button;
    eventData[P_BUTTONS] = mouseButtonDown_;
    eventData[P_QUALIFIERS] = GetQualifiers();
    SendEvent(newState ? E_MOUSEBUTTONDOWN : E_MOUSEBUTTONUP, eventData);
}

void Input::SetKey(int key, bool newState)
{
    // If we are not active yet, do not react to the key down
    if (newState && !active_)
        return;
    
    bool repeat = false;
    
    if (newState)
    {
        if (!keyDown_.Contains(key))
        {
            keyDown_.Insert(key);
            keyPress_.Insert(key);
        }
        else
            repeat = true;
    }
    else
    {
        if (!keyDown_.Erase(key))
            return;
    }
    
    using namespace KeyDown;
    
    VariantMap eventData;
    eventData[P_KEY] = key;
    eventData[P_BUTTONS] = mouseButtonDown_;
    eventData[P_QUALIFIERS] = GetQualifiers();
    if (newState)
        eventData[P_REPEAT] = repeat;
    SendEvent(newState ? E_KEYDOWN : E_KEYUP, eventData);

    if (key == KEY_RETURN && newState && !repeat && toggleFullscreen_ && (GetKeyDown(KEY_LALT) || GetKeyDown(KEY_RALT)))
        graphics_->ToggleFullscreen();
}

void Input::SetMouseWheel(int delta)
{
    // If we are not active yet, do not react to the wheel
    if (!active_)
        return;
    
    if (delta)
    {
        mouseMoveWheel_ += delta;
        
        using namespace MouseWheel;
        
        VariantMap eventData;
        eventData[P_WHEEL] = delta;
        eventData[P_BUTTONS] = mouseButtonDown_;
        eventData[P_QUALIFIERS] = GetQualifiers();
        SendEvent(E_MOUSEWHEEL, eventData);
    }
}

#ifndef USE_OPENGL
void Input::SetClipCursor(bool enable)
{
    if (!graphics_)
        return;
    
    if (!graphics_->GetFullscreen() && active_ && enable)
    {
        SetCursorPosition(IntVector2(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2));
        lastCursorPosition_ = GetCursorPosition();
        RECT clipRect;
        GetWindowRect((HWND)graphics_->GetWindowHandle(), &clipRect);
        ClipCursor(&clipRect);
    }
    else
    {
        if (graphics_->GetFullscreen() && active_ && enable)
        {
            SetCursorPosition(IntVector2(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2));
            lastCursorPosition_ = GetCursorPosition();
        }
        ClipCursor(0);
    }
}

void Input::SetCursorPosition(const IntVector2& position)
{
    if (!graphics_)
        return;
    
    POINT point;
    point.x = position.x_;
    point.y = position.y_;
    ClientToScreen((HWND)graphics_->GetWindowHandle(), &point);
    SetCursorPos(point.x, point.y);
}

void Input::SetCursorVisible(bool enable)
{
    if (!graphics_)
        return;
    
    // When inactive, always show the cursor
    if (!active_)
        enable = true;
    
    if (showCursor_ == enable)
        return;
    
    ShowCursor(enable ? TRUE : FALSE);
    showCursor_ = enable;
}

void Input::HandleWindowMessage(StringHash eventType, VariantMap& eventData)
{
    using namespace WindowMessage;
    
    int msg = eventData[P_MSG].GetInt();
    int wParam = eventData[P_WPARAM].GetInt();
    int lParam = eventData[P_LPARAM].GetInt();
    
    switch (msg)
    {
    case WM_LBUTTONDOWN:
        SetMouseButton(MOUSEB_LEFT, true);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_NCLBUTTONUP:
    case WM_LBUTTONUP:
        SetMouseButton(MOUSEB_LEFT, false);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_RBUTTONDOWN:
        SetMouseButton(MOUSEB_RIGHT, true);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_NCRBUTTONUP:
    case WM_RBUTTONUP:
        SetMouseButton(MOUSEB_RIGHT, false);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_MBUTTONDOWN:
        SetMouseButton(MOUSEB_MIDDLE, true);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_NCMBUTTONUP:
    case WM_MBUTTONUP:
        SetMouseButton(MOUSEB_MIDDLE, false);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_MOUSEWHEEL:
        SetMouseWheel(wParam >> 16);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_ACTIVATE:
        minimized_ = HIWORD(wParam) != 0;
        if (LOWORD(wParam) == WA_INACTIVE)
            MakeInactive();
        else
        {
            if (!minimized_)
               activated_ = true;
        }
        eventData[P_HANDLED] = true;
        break;
        
    case WM_KEYDOWN:
        SetKey(wParam, true);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_SYSKEYDOWN:
        SetKey(wParam, true);
        if (wParam != KEY_F4)
            eventData[P_HANDLED] = true;
        break;
        
    case WM_KEYUP:
        SetKey(wParam, false);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_SYSKEYUP:
        SetKey(wParam, false);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_CHAR:
        if (!suppressNextChar_)
        {
            using namespace Char;
            
            VariantMap keyEventData;
            keyEventData[P_CHAR] = wParam;
            keyEventData[P_BUTTONS] = mouseButtonDown_;
            keyEventData[P_QUALIFIERS] = GetQualifiers();
            SendEvent(E_CHAR, keyEventData);
        }
        suppressNextChar_ = false;
        eventData[P_HANDLED] = true;
        break;
    }
}
#else
void KeyCallback(int key, int action)
{
    inputInstance->SetKey(key, action & GLFW_PRESS);
}

void CharCallback(int key, int action)
{
    if (key < 256 && action == GLFW_PRESS)
    {
        using namespace Char;
        
        VariantMap keyEventData;
        keyEventData[P_CHAR] = key;
        keyEventData[P_BUTTONS] = inputInstance->mouseButtonDown_;
        keyEventData[P_QUALIFIERS] = inputInstance->GetQualifiers();
        inputInstance->SendEvent(E_CHAR, keyEventData);
    }
}

void MouseButtonCallback(int button, int action)
{
    inputInstance->SetMouseButton(1 << button, action == GLFW_PRESS);
}

void MouseWheelCallback(int wheel)
{
    /// \todo Implement
}
#endif

IntVector2 Input::GetCursorPosition() const
{
    IntVector2 ret(0, 0);
    
    if (!graphics_)
        return ret;
    
    #ifndef USE_OPENGL
    POINT mouse;
    GetCursorPos(&mouse);
    ScreenToClient((HWND)graphics_->GetWindowHandle(), &mouse);
    ret.x_ = mouse.x;
    ret.y_ = mouse.y;
    #else
    glfwGetMousePos(&ret.x_, &ret.y_);
    #endif
    
    return ret;
}

void Input::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    if (!initialized_)
        Initialize();
    // Screen mode change may affect the cursor clipping behaviour. Also re-center the cursor (if needed) to the new screen size,
    // so that there is no erroneous mouse move event
    #ifndef USE_OPENGL
    SetClipCursor(true);
    #else
    // Re-enable GLFW callbacks each time the window has been recreated
    glfwDisable(GLFW_MOUSE_CURSOR);
    glfwSetKeyCallback(&KeyCallback);
    glfwSetCharCallback(&CharCallback);
    glfwSetMouseButtonCallback(&MouseButtonCallback);
    glfwSetMouseWheelCallback(&MouseWheelCallback);
    lastCursorPosition_ = GetCursorPosition();
    #endif
}

void Input::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    // Update input right at the beginning of the frame
    if (initialized_)
        Update();
}
