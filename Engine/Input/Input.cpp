//
// Copyright (c) 2008-2013 the Urho3D project.
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

#if defined(__APPLE__) && !defined(IOS)
    #define REQUIRE_CLICK_TO_FOCUS
#endif

namespace Urho3D
{

/// Convert SDL keycode if necessary
int ConvertSDLKeyCode(int keySym, int scanCode)
{
    if (scanCode == SDL_SCANCODE_AC_BACK)
        return KEY_ESC;
    else
        return SDL_toupper(keySym);
}

OBJECTTYPESTATIC(Input);

Input::Input(Context* context) :
    Object(context),
    mouseButtonDown_(0),
    mouseButtonPress_(0),
    mouseMoveWheel_(0),
    windowID_(0),
    toggleFullscreen_(true),
    mouseVisible_(false),
    inputFocus_(false),
    minimized_(false),
    focusedThisFrame_(false),
    suppressNextMouseMove_(false),
    initialized_(false)
{
    SubscribeToEvent(E_SCREENMODE, HANDLER(Input, HandleScreenMode));
    
    // Try to initialize right now, but skip if screen mode is not yet set
    Initialize();
}

Input::~Input()
{
}

void Input::Update()
{
    assert(initialized_);
    
    PROFILE(UpdateInput);
    
    // Reset input accumulation for this frame
    keyPress_.Clear();
    mouseButtonPress_ = 0;
    mouseMove_ = IntVector2::ZERO;
    mouseMoveWheel_ = 0;
    for (Vector<JoystickState>::Iterator i = joysticks_.Begin(); i != joysticks_.End(); ++i)
    {
        for (unsigned j = 0; j < i->buttonPress_.Size(); ++j)
            i->buttonPress_[j] = false;
    }
    
    // Reset touch delta movement
    for (HashMap<int, TouchState>::Iterator i = touches_.Begin(); i != touches_.End(); ++i)
    {
        TouchState& state = i->second_;
        state.lastPosition_ = state.position_;
        state.delta_ = IntVector2::ZERO;
    }
    
    {
        MutexLock lock(GetStaticMutex());
        
        // Pump SDL events
        /// \todo This does not handle multiple input instances properly. Each instance will need its own event queue,
        /// where SDL events are copied and which it handles in its own main thread
        SDL_Event evt;
        SDL_PumpEvents();
        while (SDL_PollEvent(&evt))
            HandleSDLEvent(&evt);
    }
    
    // Check for activation and inactivation from SDL window flags. Must nullcheck the window pointer because it may have
    // been closed due to input events
    SDL_Window* window = graphics_->GetImpl()->GetWindow();
    if (window)
    {
        unsigned flags = SDL_GetWindowFlags(window) & (SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
#ifdef REQUIRE_CLICK_TO_FOCUS
        if (!inputFocus_ && (graphics_->GetFullscreen() || mouseVisible_) && flags == (SDL_WINDOW_INPUT_FOCUS |
            SDL_WINDOW_MOUSE_FOCUS))
#else
        if (!inputFocus_ && (flags & SDL_WINDOW_INPUT_FOCUS))
#endif
            focusedThisFrame_ = true;
        else if (inputFocus_ && (flags & SDL_WINDOW_INPUT_FOCUS) == 0)
            LoseFocus();
        
        // Activate input now if necessary
        if (focusedThisFrame_)
            GainFocus();
    }
    else
        return;
    
#if !defined(ANDROID) && !defined(IOS)
    // Check for mouse move
    if (inputFocus_)
    {
        IntVector2 mousePosition = GetMousePosition();
        mouseMove_ = mousePosition - lastMousePosition_;
        
        // Recenter the mouse cursor manually
        if (!mouseVisible_)
        {
            IntVector2 center(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2);
            SetMousePosition(center);
            lastMousePosition_ = center;
        }
        else
            lastMousePosition_ = mousePosition;
        
        // Send mouse move event if necessary
        if (mouseMove_ != IntVector2::ZERO)
        {
            if (suppressNextMouseMove_)
            {
                mouseMove_ = IntVector2::ZERO;
                suppressNextMouseMove_ = false;
            }
            else
            {
                using namespace MouseMove;
                
                VariantMap eventData;
                if (mouseVisible_)
                {
                    eventData[P_X] = mousePosition.x_;
                    eventData[P_Y] = mousePosition.y_;
                }
                eventData[P_DX] = mouseMove_.x_;
                eventData[P_DY] = mouseMove_.y_;
                eventData[P_BUTTONS] = mouseButtonDown_;
                eventData[P_QUALIFIERS] = GetQualifiers();
                SendEvent(E_MOUSEMOVE, eventData);
            }
        }
    }
#endif
}

void Input::SetMouseVisible(bool enable)
{
    if (enable != mouseVisible_)
    {
        mouseVisible_ = enable;
        
        if (initialized_)
        {
            // External windows can only support visible mouse cursor
            if (graphics_->GetExternalWindow())
            {
                mouseVisible_ = true;
                return;
            }
            
            if (!mouseVisible_ && inputFocus_)
                SDL_ShowCursor(SDL_FALSE);
            else
                SDL_ShowCursor(SDL_TRUE);
        }
    }
}

void Input::SetToggleFullscreen(bool enable)
{
    toggleFullscreen_ = enable;
}

bool Input::DetectJoysticks()
{
    {
        MutexLock lock(GetStaticMutex());
        
        SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
        ResetJoysticks();
        return true;
    }
}

bool Input::OpenJoystick(unsigned index)
{
    if (index >= joysticks_.Size())
        return false;
    
    // Check if already opened
    if (joysticks_[index].joystick_)
        return true;
    
    MutexLock lock(GetStaticMutex());
    
    SDL_Joystick* joystick = SDL_JoystickOpen(index);
    if (joystick)
    {
        JoystickState& state = joysticks_[index];
        state.joystick_ = joystick;
        state.buttons_.Resize(SDL_JoystickNumButtons(joystick));
        state.buttonPress_.Resize(state.buttons_.Size());
        state.axes_.Resize(SDL_JoystickNumAxes(joystick));
        state.hats_.Resize(SDL_JoystickNumHats(joystick));
        for (unsigned i = 0; i < state.buttons_.Size(); ++i)
        {
            state.buttons_[i] = false;
            state.buttonPress_[i] = false;
        }
        for (unsigned i = 0; i < state.axes_.Size(); ++i)
            state.axes_[i] = 0.0f;
        for (unsigned i = 0; i < state.hats_.Size(); ++i)
            state.hats_[i] = HAT_CENTER;
        
        return true;
    }
    else
        return false;
}

void Input::CloseJoystick(unsigned index)
{
    MutexLock lock(GetStaticMutex());
    
    if (index < joysticks_.Size() && joysticks_[index].joystick_)
    {
        JoystickState& state = joysticks_[index];
        SDL_JoystickClose(state.joystick_);
        state.joystick_ = 0;
        state.buttons_.Clear();
        state.axes_.Clear();
        state.hats_.Clear();
    }
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

IntVector2 Input::GetMousePosition() const
{
    IntVector2 ret = IntVector2::ZERO;
    
    if (!initialized_)
        return ret;
    
    SDL_GetMouseState(&ret.x_, &ret.y_);
    
    return ret;
}

TouchState* Input::GetTouch(unsigned index) const
{
    if (index >= touches_.Size())
        return 0;
    
    HashMap<int, TouchState>::ConstIterator i = touches_.Begin();
    while (index--)
        ++i;
    
    return const_cast<TouchState*>(&i->second_);
}

const String& Input::GetJoystickName(unsigned index) const
{
    if (index < joysticks_.Size())
        return joysticks_[index].name_;
    else
        return String::EMPTY;
}

JoystickState* Input::GetJoystick(unsigned index)
{
    if (index < joysticks_.Size())
    {
        // If necessary, automatically open the joystick first
        if (!joysticks_[index].joystick_)
            OpenJoystick(index);
        
        return const_cast<JoystickState*>(&joysticks_[index]);
    }
    else
        return 0;
}

bool Input::IsMinimized() const
{
    // Return minimized state also when unfocused in fullscreen
    if (!inputFocus_ && graphics_ && graphics_->GetFullscreen())
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
    
    // In external window mode only visible mouse is supported
    if (graphics_->GetExternalWindow())
        mouseVisible_ = true;
    
    // Set the initial activation
    focusedThisFrame_ = true;
    initialized_ = true;
    
    ResetJoysticks();
    ResetState();
    
    SubscribeToEvent(E_BEGINFRAME, HANDLER(Input, HandleBeginFrame));

    LOGINFO("Initialized input");
}

void Input::ResetJoysticks()
{
    joysticks_.Clear();
    joysticks_.Resize(SDL_NumJoysticks());
    for (unsigned i = 0; i < joysticks_.Size(); ++i)
        joysticks_[i].name_ = SDL_JoystickNameForIndex(i);
}

void Input::GainFocus()
{
    ResetState();
    
    inputFocus_ = true;
    focusedThisFrame_ = false;
    
    // Re-establish mouse cursor hiding as necessary
    if (!mouseVisible_)
    {
        SDL_ShowCursor(SDL_FALSE);
        suppressNextMouseMove_ = true;
    }
    else
        lastMousePosition_ = GetMousePosition();
    
    SendInputFocusEvent();
}

void Input::LoseFocus()
{
    ResetState();
    
    inputFocus_ = false;
    focusedThisFrame_ = false;
    
    // Show the mouse cursor when inactive
    SDL_ShowCursor(SDL_TRUE);
    
    SendInputFocusEvent();
}

void Input::ResetState()
{
    keyDown_.Clear();
    keyPress_.Clear();
    
    /// \todo Check if this is necessary
    for (Vector<JoystickState>::Iterator i = joysticks_.Begin(); i != joysticks_.End(); ++i)
    {
        for (unsigned j = 0; j < i->buttons_.Size(); ++j)
            i->buttons_[j] = false;
        for (unsigned j = 0; j < i->hats_.Size(); ++j)
            i->hats_[j] = HAT_CENTER;
    }
    
    // When clearing touch states, send the corresponding touch end events
    for (HashMap<int, TouchState>::Iterator i = touches_.Begin(); i != touches_.End(); ++i)
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

void Input::SendInputFocusEvent()
{
    using namespace InputFocus;
    
    VariantMap eventData;
    eventData[P_FOCUS] = HasFocus();
    eventData[P_MINIMIZED] = IsMinimized();
    SendEvent(E_INPUTFOCUS, eventData);
}

void Input::SetMouseButton(int button, bool newState)
{
#ifdef REQUIRE_CLICK_TO_FOCUS
    // OSX only: after losing focus in windowed hidden mouse mode, regain focus only after a left-click inside the window.
    // This allows glitchfree window dragging
    if (!mouseVisible_ && !graphics_->GetFullscreen())
    {
        if (!inputFocus_ && newState && button == MOUSEB_LEFT)
            focusedThisFrame_ = true;
    }
#endif
    
    // If we do not have focus yet, do not react to the mouse button down
    if (newState && !inputFocus_)
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
    // If we do not have focus yet, do not react to the key down
    if (newState && !inputFocus_)
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

    if ((key == KEY_RETURN || key == KEY_RETURN2 || key == KEY_KP_ENTER) && newState && !repeat && toggleFullscreen_ && (GetKeyDown(KEY_LALT) || GetKeyDown(KEY_RALT)))
        graphics_->ToggleFullscreen();
}

void Input::SetMouseWheel(int delta)
{
    // If we do not have focus yet, do not react to the wheel
    if (!inputFocus_)
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

void Input::SetMousePosition(const IntVector2& position)
{
    if (!graphics_)
        return;
    
    SDL_WarpMouseInWindow(graphics_->GetImpl()->GetWindow(), position.x_, position.y_);
}

void Input::HandleSDLEvent(void* sdlEvent)
{
    SDL_Event& evt = *static_cast<SDL_Event*>(sdlEvent);
    
    switch (evt.type)
    {
    case SDL_KEYDOWN:
        // Convert to uppercase to match Win32 virtual key codes
        SetKey(ConvertSDLKeyCode(evt.key.keysym.sym, evt.key.keysym.scancode), true);
        break;
        
    case SDL_KEYUP:
        SetKey(ConvertSDLKeyCode(evt.key.keysym.sym, evt.key.keysym.scancode), false);
        break;
        
    case SDL_TEXTINPUT:
        {
            String text(&evt.text.text[0]);
            unsigned unicode = text.AtUTF8(0);
            if (unicode)
            {
                using namespace Char;
                
                VariantMap keyEventData;
                
                keyEventData[P_CHAR] = unicode;
                keyEventData[P_BUTTONS] = mouseButtonDown_;
                keyEventData[P_QUALIFIERS] = GetQualifiers();
                SendEvent(E_CHAR, keyEventData);
            }
        }
        break;
        
#if !defined(ANDROID) && !defined(IOS)
    case SDL_MOUSEBUTTONDOWN:
        SetMouseButton(1 << (evt.button.button - 1), true);
        break;
        
    case SDL_MOUSEBUTTONUP:
        SetMouseButton(1 << (evt.button.button - 1), false);
        break;
        
    case SDL_MOUSEWHEEL:
        SetMouseWheel(evt.wheel.y);
        break;
#endif
        
    case SDL_FINGERDOWN:
        {
            int touchID = evt.tfinger.fingerId & 0x7ffffff;
            TouchState& state = touches_[touchID];
            state.touchID_ = touchID;
            state.lastPosition_ = state.position_ = IntVector2((int)(evt.tfinger.x * graphics_->GetWidth()),
                (int)(evt.tfinger.y * graphics_->GetHeight()));
            state.delta_ = IntVector2::ZERO;
            state.pressure_ = evt.tfinger.pressure;
            
            using namespace TouchBegin;
            
            VariantMap eventData;
            
            eventData[P_TOUCHID] = touchID;
            eventData[P_X] = state.position_.x_;
            eventData[P_Y] = state.position_.y_;
            eventData[P_PRESSURE] = state.pressure_;
            SendEvent(E_TOUCHBEGIN, eventData);
        }
        break;
        
    case SDL_FINGERUP:
        {
            int touchID = evt.tfinger.fingerId & 0x7ffffff;
            touches_.Erase(touchID);
            
            using namespace TouchEnd;
            
            VariantMap eventData;
            
            eventData[P_TOUCHID] = touchID;
            eventData[P_X] = evt.tfinger.x * graphics_->GetWidth();
            eventData[P_Y] = evt.tfinger.y * graphics_->GetHeight();
            SendEvent(E_TOUCHEND, eventData);
        }
        break;
        
    case SDL_FINGERMOTION:
        {
            int touchID = evt.tfinger.fingerId & 0x7ffffff;
            TouchState& state = touches_[touchID];
            state.touchID_ = touchID;
            state.position_ = IntVector2((int)(evt.tfinger.x * graphics_->GetWidth()),
                (int)(evt.tfinger.y * graphics_->GetHeight()));
            state.delta_ = state.position_ - state.lastPosition_;
            state.pressure_ = evt.tfinger.pressure;
            
            using namespace TouchMove;
            
            VariantMap eventData;
            
            eventData[P_TOUCHID] = touchID;
            eventData[P_X] = state.position_.x_;
            eventData[P_Y] = state.position_.y_;
            eventData[P_DX] = (int)(evt.tfinger.dx * graphics_->GetWidth());
            eventData[P_DY] = (int)(evt.tfinger.dy * graphics_->GetHeight());
            eventData[P_PRESSURE] = state.pressure_;
            SendEvent(E_TOUCHMOVE, eventData);
        }
        break;
        
    case SDL_JOYBUTTONDOWN:
        {
            using namespace JoystickButtonDown;
            
            VariantMap eventData;
            eventData[P_JOYSTICK] = evt.jbutton.which;
            eventData[P_BUTTON] = evt.jbutton.button;
            
            if (evt.jbutton.which < joysticks_.Size() && evt.jbutton.button <
                joysticks_[evt.jbutton.which].buttons_.Size())
            {
                joysticks_[evt.jbutton.which].buttons_[evt.jbutton.button] = true;
                joysticks_[evt.jbutton.which].buttonPress_[evt.jbutton.button] = true;
                SendEvent(E_JOYSTICKBUTTONDOWN, eventData);
            }
        }
        break;
        
    case SDL_JOYBUTTONUP:
        {
            using namespace JoystickButtonUp;
            
            VariantMap eventData;
            eventData[P_JOYSTICK] = evt.jbutton.which;
            eventData[P_BUTTON] = evt.jbutton.button;
            
            if (evt.jbutton.which < joysticks_.Size() && evt.jbutton.button <
                joysticks_[evt.jbutton.which].buttons_.Size())
            {
                joysticks_[evt.jbutton.which].buttons_[evt.jbutton.button] = false;
                SendEvent(E_JOYSTICKBUTTONUP, eventData);
            }
        }
        break;
        
    case SDL_JOYAXISMOTION:
        {
            using namespace JoystickAxisMove;
            
            VariantMap eventData;
            eventData[P_JOYSTICK] = evt.jaxis.which;
            eventData[P_AXIS] = evt.jaxis.axis;
            eventData[P_POSITION] = Clamp((float)evt.jaxis.value / 32767.0f, -1.0f, 1.0f);
            
            if (evt.jaxis.which < joysticks_.Size() && evt.jaxis.axis <
                joysticks_[evt.jaxis.which].axes_.Size())
            {
                joysticks_[evt.jaxis.which].axes_[evt.jaxis.axis] = eventData[P_POSITION].GetFloat();
                SendEvent(E_JOYSTICKAXISMOVE, eventData);
            }
        }
        break;
        
    case SDL_JOYHATMOTION:
        {
            using namespace JoystickHatMove;
            
            VariantMap eventData;
            eventData[P_JOYSTICK] = evt.jhat.which;
            eventData[P_HAT] = evt.jhat.hat;
            eventData[P_POSITION] = evt.jhat.value;
            
            if (evt.jhat.which < joysticks_.Size() && evt.jhat.hat <
                joysticks_[evt.jhat.which].hats_.Size())
            {
                joysticks_[evt.jhat.which].hats_[evt.jhat.hat] = evt.jhat.value;
                SendEvent(E_JOYSTICKHATMOVE, eventData);
            }
        }
        break;
        
    case SDL_WINDOWEVENT:
        {
            switch (evt.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                graphics_->Close();
                break;
                
            case SDL_WINDOWEVENT_MINIMIZED:
                minimized_ = true;
                SendInputFocusEvent();
                break;
                
            case SDL_WINDOWEVENT_MAXIMIZED:
            case SDL_WINDOWEVENT_RESTORED:
                minimized_ = false;
                SendInputFocusEvent();
            #ifdef IOS
                // On iOS we never lose the GL context, but may have done GPU object changes that could not be applied yet.
                // Apply them now
                graphics_->Restore();
            #endif
                break;
                
            #ifdef ANDROID
            case SDL_WINDOWEVENT_FOCUS_LOST:
                // Mark GPU objects lost
                graphics_->Release(false, false);
                break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
                // Restore GPU objects
                graphics_->Restore();
                break;
            #endif

            #if !defined(IOS) && !defined(ANDROID)
            case SDL_WINDOWEVENT_RESIZED:
                graphics_->WindowResized(evt.window.data1, evt.window.data2);
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
    // mouse move event. Also get new window ID if it changed
    SDL_Window* window = graphics_->GetImpl()->GetWindow();
    windowID_ = SDL_GetWindowID(window);
    
    if (!mouseVisible_)
    {
        IntVector2 center(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2);
        SetMousePosition(center);
        lastMousePosition_ = center;
    }
    
    focusedThisFrame_ = true;
    
    // After setting a new screen mode we should not be minimized
    minimized_ = (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) != 0;
}

void Input::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    // Update input right at the beginning of the frame
    Update();
}

}
