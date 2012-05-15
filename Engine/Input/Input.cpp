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

#include "Context.h"
#include "CoreEvents.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "Input.h"
#include "Log.h"
#include "Mutex.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "StringUtils.h"

#include <cstring>

#ifdef USE_OPENGL
#include <GraphicsImpl.h>
#else
#include <windows.h>
#endif

#include "DebugNew.h"

#ifdef USE_OPENGL
static HashMap<unsigned, Input*> inputInstances;

/// Return the Input subsystem instance corresponding to an SDL window ID.
Input* GetInputInstance(unsigned windowID)
{
    return windowID ? inputInstances[windowID] : 0;
}
#else
/// Convert the virtual key code & scan code if necessary. Return non-zero if key should be posted
int ConvertKeyCode(unsigned wParam, unsigned lParam)
{
    unsigned scanCode = (lParam >> 16) & 0x1ff;
    
    // Recognize left/right qualifier key from the scan code
    switch (wParam)
    {
    case VK_SHIFT:
        if (scanCode == 54)
            return KEY_RSHIFT;
        else
            return KEY_LSHIFT;
        break;
        
    case VK_CONTROL:
        // Control might not be a real key, as Windows posts it whenever Alt-Gr is pressed (inspired by GLFW)
        {
            MSG nextMsg;
            DWORD msgTime = GetMessageTime();
            
            if (PeekMessage(&nextMsg, NULL, 0, 0, PM_NOREMOVE))
            {
                if ((nextMsg.message == WM_KEYDOWN || nextMsg.message == WM_SYSKEYDOWN) && nextMsg.wParam == VK_MENU &&
                    (nextMsg.lParam & 0x01000000) != 0 && nextMsg.time == msgTime)
                    return 0;
            }
            
            if (scanCode & 0x100)
                return KEY_RCTRL;
            else
                return KEY_LCTRL;
        }
        break;
        
    case VK_MENU:
        if (scanCode & 0x100)
            return KEY_RALT;
        else
            return KEY_LALT;
        
    default:
        return wParam;
    }
}
#endif

OBJECTTYPESTATIC(Input);

Input::Input(Context* context) :
    Object(context),
    #ifdef USE_OPENGL
    windowID_(0),
    #else
    showCursor_(true),
    #endif
    toggleFullscreen_(true),
    active_(false),
    minimized_(false),
    activated_(false),
    suppressNextMouseMove_(false),
    initialized_(false)
{
    // Zero the initial state
    mouseButtonDown_ = 0;
    ResetState();
    
    #ifndef USE_OPENGL
    SubscribeToEvent(E_WINDOWMESSAGE, HANDLER(Input, HandleWindowMessage));
    #endif
    
    SubscribeToEvent(E_SCREENMODE, HANDLER(Input, HandleScreenMode));
    SubscribeToEvent(E_BEGINFRAME, HANDLER(Input, HandleBeginFrame));
    
    // Try to initialize right now, but skip if screen mode is not yet set
    Initialize();
}

Input::~Input()
{
    #ifdef USE_OPENGL
    // Remove input instance mapping
    if (initialized_)
    {
        MutexLock lock(GetStaticMutex());
        
        inputInstances.Erase(windowID_);
    }
    #endif
}

void Input::Update()
{
    PROFILE(UpdateInput);
    
    if (!graphics_ || !graphics_->IsInitialized())
        return;
    
    // Reset input accumulation for this frame
    keyPress_.Clear();
    mouseButtonPress_ = 0;
    mouseMove_ = IntVector2::ZERO;
    mouseMoveWheel_ = 0;
    
    #ifndef USE_OPENGL
    // Pump Win32 events
    MSG msg;
    while (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    #else
    {
        MutexLock lock(GetStaticMutex());
        
        // Pump SDL events
        SDL_Event evt;
        SDL_PumpEvents();
        while (SDL_PollEvent(&evt))
        {
            // Dispatch event to the appropriate Input instance. However SDL_QUIT can not at the moment be handled for multiple
            // instances properly (OpenGL contexts running in other threads can not be closed from this thread), so we handle
            // it only for the own instance
            if (evt.type != SDL_QUIT)
                HandleSDLEvent(&evt);
            else
                graphics_->Close();
        }
    }
    
    // Poll SDL window activation state
    SDL_Window* window = graphics_->GetImpl()->GetWindow();
    unsigned flags = SDL_GetWindowFlags(window);
    if ((flags & (SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS)) == (SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS))
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
    
    // Activate input now if necessary
    if (activated_)
        MakeActive();
    
    // Finally send the mouse move event if motion has been accumulated
    if (active_)
    {
        IntVector2 mousePos = GetCursorPosition();
        mouseMove_ = mousePos - lastCursorPosition_;

        // Recenter the mouse cursor manually if it moved
        if (mouseMove_ != IntVector2::ZERO)
        {
            IntVector2 center(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2);
            SetCursorPosition(center);
            lastCursorPosition_ = center;
        }
        else
            lastCursorPosition_ = mousePos;
        
        if (mouseMove_ != IntVector2::ZERO && suppressNextMouseMove_)
        {
            mouseMove_ = IntVector2::ZERO;
            suppressNextMouseMove_ = false;
        }
        
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
    if (qualifier == QUAL_SHIFT)
        return GetKeyDown(KEY_LSHIFT) || GetKeyDown(KEY_RSHIFT);
    if (qualifier == QUAL_CTRL)
        return GetKeyDown(KEY_LCTRL) || GetKeyDown(KEY_RCTRL);
    if (qualifier == QUAL_ALT)
        return GetKeyDown(KEY_LALT) || GetKeyDown(KEY_RALT);
    
    return false;
}

bool Input::GetQualifierPress(int qualifier) const
{
    if (qualifier == QUAL_SHIFT)
        return GetKeyPress(KEY_LSHIFT) || GetKeyPress(KEY_RSHIFT);
    if (qualifier == QUAL_CTRL)
        return GetKeyPress(KEY_LCTRL) || GetKeyPress(KEY_RCTRL);
    if (qualifier == QUAL_ALT)
        return GetKeyPress(KEY_LALT) || GetKeyPress(KEY_RALT);
    
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
    activated_ = true;
    initialized_ = true;
    
    #ifdef USE_OPENGL
    {
        MutexLock lock(GetStaticMutex());
        
        // Store window ID to direct SDL events to the correct instance
        windowID_ = SDL_GetWindowID(graphics_->GetImpl()->GetWindow());
        inputInstances[windowID_] = this;
    }
    #endif
    
    LOGINFO("Initialized input");
}

void Input::MakeActive()
{
    if (!graphics_ || !graphics_->IsInitialized())
        return;
    
    ResetState();
    
    active_ = true;
    activated_ = false;
    
    // Re-establish mouse cursor clipping as necessary
    #ifdef USE_OPENGL
    SDL_ShowCursor(SDL_FALSE);
    suppressNextMouseMove_ = true;
    #else
    SetClipCursor(true);
    SetCursorVisible(false);
    #endif
    
    using namespace Activation;
    
    VariantMap eventData;

    eventData[P_ACTIVE] = active_;
    eventData[P_MINIMIZED] = minimized_;
    SendEvent(E_ACTIVATION, eventData);
}

void Input::MakeInactive()
{
    if (!graphics_ || !graphics_->IsInitialized())
        return;
    
    ResetState();
    
    active_ = false;
    activated_ = false;
    
    // Free and show the mouse cursor
    #ifndef USE_OPENGL
    ReleaseCapture();
    ClipCursor(0);
    SetCursorVisible(true);
    #else
    SDL_ShowCursor(SDL_TRUE);
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

void Input::SetCursorPosition(const IntVector2& position)
{
    if (!graphics_)
        return;
    
    #ifdef USE_OPENGL
    SDL_WarpMouseInWindow(graphics_->GetImpl()->GetWindow(), position.x_, position.y_);
    #else
    POINT point;
    point.x = position.x_;
    point.y = position.y_;
    ClientToScreen((HWND)graphics_->GetWindowHandle(), &point);
    SetCursorPos(point.x, point.y);
    #endif
}


IntVector2 Input::GetCursorPosition() const
{
    IntVector2 ret = lastCursorPosition_;
    
    if (!graphics_ || !graphics_->IsInitialized())
        return ret;
    
    #ifdef USE_OPENGL
    SDL_GetMouseState(&ret.x_, &ret.y_);
    #else
    POINT mouse;
    GetCursorPos(&mouse);
    ScreenToClient((HWND)graphics_->GetWindowHandle(), &mouse);
    ret.x_ = mouse.x;
    ret.y_ = mouse.y;
    #endif
    
    return ret;
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
    if (!initialized_)
        Initialize();
    
    using namespace WindowMessage;
    
    int msg = eventData[P_MSG].GetInt();
    int wParam = eventData[P_WPARAM].GetInt();
    int lParam = eventData[P_LPARAM].GetInt();
    int keyCode;
    
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
        keyCode = ConvertKeyCode(wParam, lParam);
        if (keyCode)
            SetKey(keyCode, true);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_SYSKEYDOWN:
        keyCode = ConvertKeyCode(wParam, lParam);
        if (keyCode)
            SetKey(keyCode, true);
        if (keyCode != KEY_F4)
            eventData[P_HANDLED] = true;
        break;
        
    case WM_KEYUP:
    case WM_SYSKEYUP:
        keyCode = ConvertKeyCode(wParam, lParam);
        if (keyCode)
            SetKey(keyCode, false);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_CHAR:
        {
            using namespace Char;
            
            VariantMap keyEventData;
            keyEventData[P_CHAR] = wParam;
            keyEventData[P_BUTTONS] = mouseButtonDown_;
            keyEventData[P_QUALIFIERS] = GetQualifiers();
            SendEvent(E_CHAR, keyEventData);
        }
        eventData[P_HANDLED] = true;
        break;
    }
}
#else
void Input::HandleSDLEvent(void* sdlEvent)
{
    SDL_Event& evt = *static_cast<SDL_Event*>(sdlEvent);
    Input* input = 0;
    
    switch (evt.type)
    {
    case SDL_KEYDOWN:
        // Convert to uppercase to match Win32 virtual key codes
        input = GetInputInstance(evt.key.windowID);
        if (input)
            input->SetKey(SDL_toupper(evt.key.keysym.sym), true);
        break;
        
    case SDL_KEYUP:
        input = GetInputInstance(evt.key.windowID);
        if (input)
            input->SetKey(SDL_toupper(evt.key.keysym.sym), false);
        break;
        
    case SDL_TEXTINPUT:
        input = GetInputInstance(evt.text.windowID);
        if (input && evt.text.text[0])
        {
            String text(&evt.text.text[0]);
            unsigned unicode = text.AtUTF8(0);
            if (unicode)
            {
                using namespace Char;
                
                VariantMap keyEventData;
                
                keyEventData[P_CHAR] = unicode;
                keyEventData[P_BUTTONS] = input->mouseButtonDown_;
                keyEventData[P_QUALIFIERS] = input->GetQualifiers();
                input->SendEvent(E_CHAR, keyEventData);
            }
        }
        break;
        
    case SDL_MOUSEBUTTONDOWN:
        input = GetInputInstance(evt.button.windowID);
        if (input)
            input->SetMouseButton(1 << (evt.button.button - 1), true);
        break;
        
    case SDL_MOUSEBUTTONUP:
        input = GetInputInstance(evt.button.windowID);
        if (input)
            input->SetMouseButton(1 << (evt.button.button - 1), false);
        break;
        
    case SDL_MOUSEWHEEL:
        input = GetInputInstance(evt.wheel.windowID);
        if (input)
            input->SetMouseWheel(evt.wheel.y);
        break;
        
    case SDL_WINDOWEVENT:
        if (evt.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            input = GetInputInstance(evt.window.windowID);
            if (input)
                input->GetSubsystem<Graphics>()->Close();
        }
        break;
    }
}
#endif

void Input::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    // Reset input state on subsequent initializations
    if (!initialized_)
        Initialize();
    else
        ResetState();
    
    // Re-enable cursor clipping, and re-center the cursor (if needed) to the new screen size, so that there is no erroneous
    // mouse move event. Also, in SDL mode reset the window ID
    #ifdef USE_OPENGL
    unsigned newWindowID = SDL_GetWindowID(graphics_->GetImpl()->GetWindow());
    if (newWindowID != windowID_)
    {
        MutexLock lock(GetStaticMutex());
        
        inputInstances.Erase(windowID_);
        inputInstances[newWindowID] = this;
        windowID_ = newWindowID;
    }
    IntVector2 center(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2);
    SetCursorPosition(center);
    lastCursorPosition_ = center;
    activated_ = true;
    #else
    SetClipCursor(true);
    #endif
}

void Input::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    // Update input right at the beginning of the frame
    if (initialized_)
        Update();
}
