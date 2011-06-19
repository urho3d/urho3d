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

#ifndef USE_SDL
#include <Windows.h>
#else
#include <SDL.h>
#endif

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
    mouseButtonDown_ = 0;
    mouseButtonPress_ = 0;
    lastMousePosition_ = IntVector2::ZERO;
    
    #ifndef USE_SDL
    SubscribeToEvent(E_WINDOWMESSAGE, HANDLER(Input, HandleWindowMessage));
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
    
    #ifndef USE_SDL
    // Pump Win32 events
    MSG msg;
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    #else
    // Pump SDL events
    SDL_Event evt;
    SDL_PumpEvents();
    while (SDL_PollEvent(&evt))
        HandleSDLEvent(&evt);
    
    // Poll SDL activation state
    unsigned state = SDL_GetAppState();
    if ((state & (SDL_APPINPUTFOCUS | SDL_APPACTIVE)) == (SDL_APPINPUTFOCUS | SDL_APPACTIVE))
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
        // In clipped mode, require the operating system cursor to be hidden first
        IntVector2 mousePos = GetMousePosition();
        mouseMove_ = ((!clipCursor_) || (!showCursor_)) ? mousePos - lastMousePosition_ : IntVector2::ZERO;
        
        // Recenter the mouse cursor manually if cursor clipping is in effect
        if ((clipCursor_) && (mouseMove_ != IntVector2::ZERO))
        {
            IntVector2 center(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2);
            SetMousePosition(center);
            lastMousePosition_ = GetMousePosition();
        }
        else
            lastMousePosition_ = mousePos;
        
        if (mouseMove_ != IntVector2::ZERO)
        {
            using namespace MouseMove;
            
            VariantMap eventData;
            eventData[P_X] = lastMousePosition_.x_;
            eventData[P_Y] = lastMousePosition_.y_;
            eventData[P_DX] = mouseMove_.x_;
            eventData[P_DY] = mouseMove_.y_;
            eventData[P_BUTTONS] = mouseButtonDown_;
            eventData[P_QUALIFIERS] = GetQualifiers();
            eventData[P_CLIPCURSOR] = clipCursor_;
            SendEvent(E_MOUSEMOVE, eventData);
        }
    }
}

void Input::SetClipCursor(bool enable)
{
    clipCursor_ = enable;
    
    if (!graphics_)
        return;
    
    if ((!graphics_->GetFullscreen()) && (active_) && (clipCursor_))
    {
        SetMousePosition(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2);
        lastMousePosition_ = GetMousePosition();
        #ifndef USE_SDL
        RECT clipRect;
        GetWindowRect((HWND)graphics_->GetWindowHandle(), &clipRect);
        ClipCursor(&clipRect);
        #endif
    }
    else
    {
        if ((graphics_->GetFullscreen()) && (active_) && (clipCursor_))
        {
            SetMousePosition(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2);
            lastMousePosition_ = GetMousePosition();
        }
        #ifndef USE_SDL
        ClipCursor(0);
        #endif
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
    
    #ifndef USE_SDL
    POINT point;
    point.x = position.x_;
    point.y = position.y_;
    ClientToScreen((HWND)graphics_->GetWindowHandle(), &point);
    SetCursorPos(point.x, point.y);
    #else
    SDL_WarpMouse(position.x_, position.y_);
    #endif
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
    return keyDown_.Contains(key);
}

bool Input::GetKeyPress(int key) const
{
    return keyPress_.Contains(key);
}

IntVector2 Input::GetMousePosition() const
{
    IntVector2 ret(0, 0);
    
    if (!graphics_)
        return ret;
    
    #ifndef USE_SDL
    POINT mouse;
    GetCursorPos(&mouse);
    ScreenToClient((HWND)graphics_->GetWindowHandle(), &mouse);
    ret.x_ = mouse.x;
    ret.y_ = mouse.y;
    #else
    SDL_GetMouseState(&ret.x_, &ret.y_);
    #endif
    
    return ret;
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
    #ifndef USE_SDL
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
    #ifndef USE_SDL
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
    if ((!graphics) || (!graphics->IsInitialized()))
        return;
    
    graphics_ = graphics;
    
    #ifdef USE_SDL
    // Enable translated keyboard input
    SDL_EnableUNICODE(SDL_TRUE);
    #endif
    // Set the initial activation
    MakeActive();
    SetClipCursor(clipCursor_);
    SetCursorVisible(false);
    
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
    
    // Re-establish mouse cursor clipping immediately in fullscreen. In windowed mode, require a mouse click inside the window
    // first to not confuse with title bar drag
    if ((!clipCursor_) || (graphics_->GetFullscreen()))
    {
        SetClipCursor(clipCursor_);
        SetCursorVisible(false);
    }
    
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
    #ifndef USE_SDL
    ReleaseCapture();
    ClipCursor(0);
    #endif
    SetCursorVisible(true);
    
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
    if ((newState) && (!active_))
        return;
    
    // If we are still showing the cursor (waiting for a click inside window), hide it now and disregard this click
    if ((newState) && (clipCursor_) && (showCursor_))
    {
        SetClipCursor(clipCursor_);
        SetCursorVisible(false);
        return;
    }
    
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
    
    #ifndef USE_SDL
    // In non-clipped mode, while any of the mouse buttons are down, capture the mouse so that we get the button release reliably
    if ((graphics_) && (!clipCursor_))
    {
        if (mouseButtonDown_)
            SetCapture((HWND)graphics_->GetWindowHandle());
        else
            ReleaseCapture();
    }
    #endif
}

void Input::SetKey(int key, int scanCode, bool newState)
{
    // If we are not active yet, do not react to the key down
    if ((newState) && (!active_))
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
    eventData[P_SCANCODE] = scanCode;
    eventData[P_BUTTONS] = mouseButtonDown_;
    eventData[P_QUALIFIERS] = GetQualifiers();
    if (newState)
        eventData[P_REPEAT] = repeat;
    SendEvent(newState ? E_KEYDOWN : E_KEYUP, eventData);
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

void Input::SetCursorVisible(bool enable)
{
    if (!graphics_)
        return;
    
    #ifndef USE_SDL
    // When inactive, always show the cursor
    if (!active_)
        enable = true;
    
    if (showCursor_ == enable)
        return;
    
    ShowCursor(enable ? TRUE : FALSE);
    #else
    SDL_ShowCursor(enable ? SDL_TRUE : SDL_FALSE);
    #endif
    showCursor_ = enable;
}

#ifndef USE_SDL
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
        SetKey(wParam, (lParam >> 16) & 255, true);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_SYSKEYDOWN:
        SetKey(wParam, (lParam >> 16) & 255, true);
        if ((wParam == KEY_RETURN) && (toggleFullscreen_))
            graphics_->ToggleFullscreen();
        if (wParam != KEY_F4)
            eventData[P_HANDLED] = true;
        break;
        
    case WM_KEYUP:
        SetKey(wParam, (lParam >> 16) & 255, false);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_SYSKEYUP:
        SetKey(wParam, (lParam >> 16) & 255, false);
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
        // When cursor is not clipped, switch to the operating system cursor outside the client area
        if (!clipCursor_)
        {
            if ((lParam & 0xffff) == HTCLIENT)
            {
                SetCursorVisible(false);
                eventData[P_HANDLED] = true;
            }
            else
                SetCursorVisible(true);
        }
        break;
    }
}
#else
void Input::HandleSDLEvent(void* sdlEvent)
{
    SDL_Event& evt = *static_cast<SDL_Event*>(sdlEvent);
    switch (evt.type)
    {
    case SDL_KEYDOWN:
        // Convert to uppercase to match Win32 virtual key codes
        SetKey(SDL_toupper(evt.key.keysym.sym), evt.key.keysym.scancode, true);
        
        // Check ALT-ENTER fullscreen toggle
        if ((evt.key.keysym.sym == KEY_RETURN) && ((GetKeyDown(KEY_LALT)) || (GetKeyDown(KEY_RALT))) && (toggleFullscreen_))
            graphics_->ToggleFullscreen();
        break;
        
    case SDL_KEYUP:
        SetKey(SDL_toupper(evt.key.keysym.sym), evt.key.keysym.scancode, false);
        break;
        
    case SDL_TEXTINPUT:
        // Convert back to Latin-1
        if (!suppressNextChar_)
        {
            unsigned char x = evt.text.text[0];
            unsigned char y = evt.text.text[1];
            int latin1 = 0;
            
            if (x < 0x80)
                latin1 = x;
            else if (x < 0xe0)
                latin1 = (y & 0x3f) | ((x & 0x1f) << 6);
            
            if ((latin1) && (latin1 < 256))
            {
                using namespace Char;
                
                VariantMap keyEventData;
                
                keyEventData[P_CHAR] = latin1;
                keyEventData[P_BUTTONS] = mouseButtonDown_;
                keyEventData[P_QUALIFIERS] = GetQualifiers();
                SendEvent(E_CHAR, keyEventData);
            }
        }
        else
            suppressNextChar_ = false;
        break;
        
    case SDL_MOUSEBUTTONDOWN:
        SetMouseButton(1 << (evt.button.button - 1), true);
        break;
        
    case SDL_MOUSEBUTTONUP:
        SetMouseButton(1 << (evt.button.button - 1), false);
        break;
        
    case SDL_MOUSEWHEEL:
        SetMouseWheel(evt.wheel.y);
        break;
        
    case SDL_QUIT:
        if (graphics_)
            graphics_->Close();
        break;
    }
}
#endif

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
