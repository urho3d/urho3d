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
#include "GraphicsImpl.h"
#include "Input.h"
#include "Log.h"
#include "Mutex.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "StringUtils.h"

#include <cstring>

#include <SDL.h>

#include "DebugNew.h"

static HashMap<unsigned, Input*> inputInstances;

/// Return the Input subsystem instance corresponding to an SDL window ID.
Input* GetInputInstance(unsigned windowID)
{
    #ifndef ANDROID
    return windowID ? inputInstances[windowID] : 0;
    #else
    // On Android we support only a single instance of Urho3D in the process, and the window ID can not be relied on.
    return inputInstances.Size() ? inputInstances.Begin()->second_ : 0;
    #endif
}

/// Convert SDL keycode if necessary
int ConvertSDLKeyCode(int keySym, int scanCode)
{
    if (scanCode == SDL_SCANCODE_AC_BACK)
        return KEY_ESC;
    else return SDL_toupper(keySym);
}

OBJECTTYPESTATIC(Input);

Input::Input(Context* context) :
    Object(context),
    windowID_(0),
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
    
    SubscribeToEvent(E_SCREENMODE, HANDLER(Input, HandleScreenMode));
    SubscribeToEvent(E_BEGINFRAME, HANDLER(Input, HandleBeginFrame));
    
    // Try to initialize right now, but skip if screen mode is not yet set
    Initialize();
}

Input::~Input()
{
    // Remove input instance mapping
    if (initialized_)
    {
        MutexLock lock(GetStaticMutex());
        
        inputInstances.Erase(windowID_);
    }
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
    
    // Reset touch delta movement
    for (Map<int, TouchState>::Iterator i = touches_.Begin(); i != touches_.End(); ++i)
    {
        TouchState& state = i->second_;
        state.lastPosition_ = state.position_;
        state.delta_ = IntVector2::ZERO;
    }
    
    {
        MutexLock lock(GetStaticMutex());
        
        // Pump SDL events
        SDL_Event evt;
        SDL_PumpEvents();
        while (SDL_PollEvent(&evt))
        {
            // Dispatch event to the appropriate Input instance. However SDL_QUIT can not at the moment be handled for multiple
            // instances properly (other threads' graphics devices can not be closed from this thread), so we handle it only
            // for own instance
            if (evt.type != SDL_QUIT)
                HandleSDLEvent(&evt);
            else
                graphics_->Close();
        }
    }
    
    // Poll SDL window activation state
    SDL_Window* window = graphics_->GetImpl()->GetWindow();
    if (!window)
        return;
    
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
    
    // Activate input now if necessary
    if (activated_)
        MakeActive();
    
    // Check for mouse move
    if (active_)
    {
        IntVector2 mousePos = GetCursorPosition();
        mouseMove_ = mousePos - lastCursorPosition_;
        
        // Recenter the mouse cursor manually
        IntVector2 center(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2);
        SetCursorPosition(center);
        lastCursorPosition_ = center;
        
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

TouchState Input::GetTouch(unsigned index) const
{
    unsigned cmpIndex = 0;
    for (Map<int, TouchState>::ConstIterator i = touches_.Begin(); i != touches_.End(); ++i)
    {
        /// \todo Do not make a value copy
        if (cmpIndex == index)
            return i->second_;
        else
            ++cmpIndex;
    }
    
    return TouchState();
}

bool Input::IsMinimized() const
{
    // Return minimized state also when inactive in fullscreen
    if (!active_ && graphics_ && graphics_->GetFullscreen())
        return true;
    else
        return minimized_;
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
    
    {
        MutexLock lock(GetStaticMutex());
        
        // Store window ID to direct SDL events to the correct instance
        windowID_ = SDL_GetWindowID(graphics_->GetImpl()->GetWindow());
        inputInstances[windowID_] = this;
    }
    
    LOGINFO("Initialized input");
}

void Input::MakeActive()
{
    if (!graphics_ || !graphics_->IsInitialized())
        return;
    
    ResetState();
    
    active_ = true;
    activated_ = false;
    
    // Re-establish mouse cursor hiding as necessary
    SDL_ShowCursor(SDL_FALSE);
    suppressNextMouseMove_ = true;
    
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
    
    // Show the mouse cursor when inactive
    SDL_ShowCursor(SDL_TRUE);
    
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
    
    // When clearing touch states, send the corresponding touch end events
    for (Map<int, TouchState>::Iterator i = touches_.Begin(); i != touches_.End(); ++i)
    {
        TouchState& state = i->second_;
        
        using namespace TouchEnd;
        
        VariantMap eventData;
        
        eventData[P_TOUCHID] = state.touchID_;
        eventData[P_X] = state.position_.x_;
        eventData[P_Y] = state.position_.y_;
        SendEvent(E_TOUCHEND, eventData);
    }
    
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
    
    SDL_WarpMouseInWindow(graphics_->GetImpl()->GetWindow(), position.x_, position.y_);
}


IntVector2 Input::GetCursorPosition() const
{
    IntVector2 ret = lastCursorPosition_;
    
    if (!graphics_ || !graphics_->IsInitialized())
        return ret;
    
    SDL_GetMouseState(&ret.x_, &ret.y_);
    
    return ret;
}

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
            input->SetKey(ConvertSDLKeyCode(evt.key.keysym.sym, evt.key.keysym.scancode), true);
        break;
        
    case SDL_KEYUP:
        input = GetInputInstance(evt.key.windowID);
        if (input)
            input->SetKey(ConvertSDLKeyCode(evt.key.keysym.sym, evt.key.keysym.scancode), false);
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
        
    case SDL_FINGERDOWN:
        input = GetInputInstance(evt.tfinger.windowID);
        if (input)
        {
            int touchID = evt.tfinger.fingerId & 0x7ffffff;
            TouchState& state = input->touches_[touchID];
            state.touchID_ = touchID;
            state.lastPosition_ = state.position_ = IntVector2(evt.tfinger.x * input->graphics_->GetWidth() / 32768,
                evt.tfinger.y * input->graphics_->GetHeight() / 32768);
            state.delta_ = IntVector2::ZERO;
            state.pressure_ = evt.tfinger.pressure;
            
            using namespace TouchBegin;
            
            VariantMap eventData;
            
            eventData[P_TOUCHID] = touchID;
            eventData[P_X] = state.position_.x_;
            eventData[P_Y] = state.position_.y_;
            eventData[P_PRESSURE] = state.pressure_;
            input->SendEvent(E_TOUCHBEGIN, eventData);
        }
        break;
        
    case SDL_FINGERUP:
        input = GetInputInstance(evt.tfinger.windowID);
        if (input)
        {
            int touchID = evt.tfinger.fingerId & 0x7ffffff;
            input->touches_.Erase(touchID);
            
            using namespace TouchEnd;
            
            VariantMap eventData;
            
            eventData[P_TOUCHID] = touchID;
            eventData[P_X] = evt.tfinger.x * input->graphics_->GetWidth() / 32768;
            eventData[P_Y] = evt.tfinger.y * input->graphics_->GetHeight() / 32768;
            input->SendEvent(E_TOUCHEND, eventData);
        }
        break;
        
    case SDL_FINGERMOTION:
        input = GetInputInstance(evt.tfinger.windowID);
        if (input)
        {
            int touchID = evt.tfinger.fingerId & 0x7ffffff;
            TouchState& state = input->touches_[touchID];
            state.touchID_ = touchID;
            state.position_ = IntVector2(evt.tfinger.x * input->graphics_->GetWidth() / 32768,
                evt.tfinger.y * input->graphics_->GetHeight() / 32768);
            state.delta_ = state.position_ - state.lastPosition_;
            state.pressure_ = evt.tfinger.pressure;
            
            using namespace TouchMove;
            
            VariantMap eventData;
            
            eventData[P_TOUCHID] = touchID;
            eventData[P_X] = state.position_.x_;
            eventData[P_Y] = state.position_.y_;
            eventData[P_DX] = evt.tfinger.dx * input->graphics_->GetWidth() / 32768;
            eventData[P_DY] = evt.tfinger.dy * input->graphics_->GetHeight() / 32768;
            eventData[P_PRESSURE] = state.pressure_;
            input->SendEvent(E_TOUCHMOVE, eventData);
        }
        break;
        
    case SDL_WINDOWEVENT:
        input = GetInputInstance(evt.window.windowID);
        if (input)
        {
            switch (evt.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                input->GetSubsystem<Graphics>()->Close();
                break;
                
            case SDL_WINDOWEVENT_MINIMIZED:
                input->minimized_ = true;
                break;
                
            case SDL_WINDOWEVENT_RESTORED:
                input->minimized_ = false;
                break;
                
            #ifdef ANDROID
            case SDL_WINDOWEVENT_SURFACE_LOST:
                // Mark GPU objects lost
                input->graphics_->Release(false, false);
                break;
                
            case SDL_WINDOWEVENT_SURFACE_CREATED:
                // Restore GPU objects
                input->graphics_->Restore();
                break;
            #endif
            }
        }
        break;
    }
}

void Input::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    // Reset input state on subsequent initializations
    if (!initialized_)
        Initialize();
    else
        ResetState();
    
    // Re-enable cursor clipping, and re-center the cursor (if needed) to the new screen size, so that there is no erroneous
    // mouse move event. Also get the new window ID in case it changed
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
    
    // After setting new screen mode we never should be minimized
    minimized_ = false;
}

void Input::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    // Update input right at the beginning of the frame
    if (initialized_)
        Update();
}
