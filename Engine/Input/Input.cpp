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
#include <Windows.h>

#include "DebugNew.h"

OBJECTTYPESTATIC(Input);

Input::Input(Context* context) :
    Object(context),
    clipCursor_(true),
    showCursor_(true),
    toggleFullscreen_(true),
    active_(false),
    minimized_(false),
    activated_(false),
    suppressNextChar_(false),
    initialized_(false)
{
    // Zero the initial state
    memset(&keyDown_, 0, sizeof(keyDown_));
    memset(&keyPress_, 0, sizeof(keyPress_));
    mouseButtonDown_ = 0;
    mouseButtonPress_ = 0;
    lastMousePosition_ = IntVector2::ZERO;
    
    SubscribeToEvent(E_WINDOWMESSAGE, HANDLER(Input, HandleWindowMessage));
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
    
    memset(keyPress_, 0, sizeof(keyPress_));
    mouseButtonPress_ = 0;
    mouseMove_ = IntVector2::ZERO;
    mouseMoveWheel_ = 0;
    
    graphics_->MessagePump();
    
    if (activated_)
        MakeActive();
    
    CheckMouseMove();
}

void Input::SetClipCursor(bool enable)
{
    clipCursor_ = enable;
    
    if (!graphics_)
        return;
    
    if ((!graphics_->GetFullscreen()) && (active_) && (clipCursor_))
    {
        RECT clipRect;
        SetMousePosition(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2);
        lastMousePosition_ = GetMousePosition();
        GetWindowRect((HWND)graphics_->GetWindowHandle(), &clipRect);
        ClipCursor(&clipRect);
    }
    else
    {
        if ((graphics_->GetFullscreen()) && (active_) && (clipCursor_))
        {
            SetMousePosition(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2);
            lastMousePosition_ = GetMousePosition();
        }
        ClipCursor(0);
    }
}

void Input::SetToggleFullscreen(bool enable)
{
    toggleFullscreen_ = enable;
}

void Input::SetMousePosition(const IntVector2& position)
{
    if (!graphics_)
        return;
    
    POINT point;
    point.x = position.x_;
    point.y = position.y_;
    ClientToScreen((HWND)graphics_->GetWindowHandle(), &point);
    SetCursorPos(point.x, point.y);
}

void Input::SetMousePosition(int x, int y)
{
    SetMousePosition(IntVector2(x, y));
}

void Input::SuppressNextChar()
{
    suppressNextChar_ = true;
}

bool Input::GetKeyDown(int key) const
{
    if ((key < 0) || (key >= MAX_KEYS))
        return false;
    
    return keyDown_[key];
}

bool Input::GetKeyPress(int key) const
{
    if ((key < 0) || (key >= MAX_KEYS))
        return false;
    
    return keyPress_[key];
}

IntVector2 Input::GetMousePosition() const
{
    if (!graphics_)
        return IntVector2(0, 0);
    
    POINT mouse;
    GetCursorPos(&mouse);
    ScreenToClient((HWND)graphics_->GetWindowHandle(), &mouse);
    return IntVector2(mouse.x, mouse.y);
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
    if (qualifier == QUAL_SHIFT)
        return keyDown_[KEY_SHIFT] != 0;
    if (qualifier == QUAL_CTRL)
        return keyDown_[KEY_CTRL] != 0;
    return false;
}

bool Input::GetQualifierPress(int qualifier) const
{
    if (qualifier == QUAL_SHIFT)
        return keyPress_[KEY_SHIFT] != 0;
    if (qualifier == QUAL_CTRL)
        return keyPress_[KEY_CTRL] != 0;
    return false;
}

int Input::GetQualifiers() const
{
    int ret = 0;
    if (keyDown_[KEY_SHIFT] != 0)
        ret |= QUAL_SHIFT;
    if (keyDown_[KEY_CTRL] != 0)
        ret |= QUAL_CTRL;
    return ret;
}

void Input::Initialize()
{
    Graphics* graphics = GetSubsystem<Graphics>();
    if ((!graphics) || (!graphics->IsInitialized()))
        return;
    
    graphics_ = graphics;
    
    // In fullscreen mode there is no initial window activation message. Therefore assume activation
    if (graphics_->GetFullscreen())
        activated_ = true;
    
    initialized_ = true;
    
    LOGINFO("Initialized input");
}

void Input::MakeActive()
{
    if (!graphics_)
        return;
        
    clearState();
    
    active_ = true;
    activated_ = false;
    
    // Re-establish mouse cursor clipping if necessary
    SetClipCursor(clipCursor_);
    SetCursorVisible(false);
    
    SendEvent(E_ACTIVATED);
}

void Input::MakeInactive()
{
    if (!graphics_)
        return;
    
    clearState();
    
    active_ = false;
    activated_ = false;
    
    // Free and show the mouse cursor
    ReleaseCapture();
    ClipCursor(0);
    SetCursorVisible(true);
    
    SendEvent(E_INACTIVATED);
}

void Input::clearState()
{
    // Use SetKey() & SetMouseButton() to reset the state so that events will be sent properly
    for (unsigned i = 0; i < MAX_KEYS; ++i)
        SetKey(i, false);
    SetMouseButton(MOUSEB_LEFT, false);
    SetMouseButton(MOUSEB_RIGHT, false);
    SetMouseButton(MOUSEB_MIDDLE, false);
    
    mouseMove_ = IntVector2::ZERO;
    mouseMoveWheel_ = 0;
    mouseButtonPress_ = 0;
    memset(&keyPress_, 0, sizeof(keyPress_));
}

void Input::SetMouseButton(int button, bool newState)
{
    // If we are not active yet, do not react to the mouse button down
    if ((newState) && (!active_))
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
    
    // In non-confined mode, while any of the mouse buttons are down, capture the mouse so that we get the button release reliably
    if ((graphics_) && (!clipCursor_))
    {
        if (mouseButtonDown_)
            SetCapture((HWND)graphics_->GetWindowHandle());
        else
            ReleaseCapture();
    }
}

void Input::SetKey(int key, bool newState)
{
    if ((key < 0) || (key >= MAX_KEYS))
        return;
    
    bool repeat = false;
    
    if (newState)
    {
        if (!keyDown_[key])
            keyPress_[key] = true;
        else
            repeat = true;
    }
    else
    {
        if (!keyDown_[key])
            return;
    }
    
    keyDown_[key] = newState;
    
    using namespace KeyDown;
    
    VariantMap eventData;
    eventData[P_KEY] = key;
    eventData[P_BUTTONS] = mouseButtonDown_;
    eventData[P_QUALIFIERS] = GetQualifiers();
    if (newState)
        eventData[P_REPEAT] = repeat;
    SendEvent(newState ? E_KEYDOWN : E_KEYUP, eventData);
}

void Input::SetMouseWheel(int delta)
{
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
void Input::CheckMouseMove()
{
    if (!active_)
        return;
    
    IntVector2 mousePos = GetMousePosition();
    IntVector2 mouseMove = mousePos - lastMousePosition_;
    
    if ((clipCursor_) && (mouseMove != IntVector2::ZERO))
    {
        IntVector2 center(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2);
        SetMousePosition(center);
        lastMousePosition_ = GetMousePosition();
    }
    else
        lastMousePosition_ = mousePos;
    
    if (mouseMove != IntVector2::ZERO)
    {
        mouseMove_ += mouseMove;
        
        using namespace MouseMove;
        
        VariantMap eventData;
        eventData[P_X] = lastMousePosition_.x_;
        eventData[P_Y] = lastMousePosition_.y_;
        eventData[P_DX] = mouseMove.x_;
        eventData[P_DY] = mouseMove.y_;
        eventData[P_BUTTONS] = mouseButtonDown_;
        eventData[P_QUALIFIERS] = GetQualifiers();
        eventData[P_CLIPCURSOR] = clipCursor_;
        SendEvent(E_MOUSEMOVE, eventData);
    }
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
        if (LOWORD(wParam) == WA_INACTIVE)
        {
            MakeInactive();
            if (graphics_->GetFullscreen())
                minimized_ = true;
        }
        else
        {
            if (!minimized_)
               activated_ = true;
        }
        eventData[P_HANDLED] = true;
        break;
        
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
        {
            minimized_ = true;
            MakeInactive();
        }
        if ((wParam == SIZE_RESTORED) || (wParam == SIZE_MAXIMIZED))
        {
            minimized_ = false;
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
        if ((wParam == KEY_RETURN) && (toggleFullscreen_))
            graphics_->ToggleFullscreen();
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
        
    case WM_SETCURSOR:
        if ((lParam & 0xffff) == HTCLIENT)
        {
            SetCursorVisible(false);
            eventData[P_HANDLED] = true;
        }
        else
            SetCursorVisible(true);
        break;
    }
}

void Input::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    if (!initialized_)
        Initialize();
    // Screen mode change may affect the cursor clipping behaviour. Also re-center the cursor (if needed) to the new screen size,
    // so that there is no erroneous mouse move event
    else
        SetClipCursor(clipCursor_);
}

void Input::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    // Update input right at the beginning of the frame
    if (initialized_)
        Update();
}
