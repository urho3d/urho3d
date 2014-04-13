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

#include "Precompiled.h"
#include "Context.h"
#include "CoreEvents.h"
#include "FileSystem.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "GraphicsImpl.h"
#include "Input.h"
#include "Log.h"
#include "Mutex.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "Text.h"
#include "UI.h"
#include "UIEvents.h"

#include <cstring>

#include <SDL.h>

#include "DebugNew.h"

// Require a click inside window before re-hiding mouse cursor on OSX, otherwise dragging the window
// can be incorrectly interpreted as mouse movement inside the window
#if defined(__APPLE__) && !defined(IOS)
    #define REQUIRE_CLICK_TO_FOCUS
#endif

namespace Urho3D
{

const int SCREEN_JOYSTICK_START_INDEX = 1000;
const ShortStringHash VAR_INJECT_AS_KEY_EVENTS("VAR_INJECT_AS_KEY_EVENTS");
const ShortStringHash VAR_BUTTON_KEY_BINDING("VAR_BUTTON_KEY_BINDING");
const ShortStringHash VAR_SCREEN_JOYSTICK_INDEX("VAR_SCREEN_JOYSTICK_INDEX");

/// Convert SDL keycode if necessary.
int ConvertSDLKeyCode(int keySym, int scanCode)
{
    if (scanCode == SCANCODE_AC_BACK)
        return KEY_ESC;
    else
        return SDL_toupper(keySym);
}

JoystickState::~JoystickState()
{
    if (screenJoystick_)
        screenJoystick_->Remove();
}

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
    scancodePress_.Clear();
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

    // Check and handle SDL events
    SDL_PumpEvents();
    SDL_Event evt;
    while (SDL_PeepEvents(&evt, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) > 0)
        HandleSDLEvent(&evt);

    // Check for activation and inactivation from SDL window flags. Must nullcheck the window pointer because it may have
    // been closed due to input events
    SDL_Window* window = graphics_->GetImpl()->GetWindow();
    unsigned flags = window ? SDL_GetWindowFlags(window) & (SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS) : 0;
    if (window)
    {
#ifdef REQUIRE_CLICK_TO_FOCUS
        if (!inputFocus_ && (graphics_->GetFullscreen() || mouseVisible_) && flags == (SDL_WINDOW_INPUT_FOCUS |
            SDL_WINDOW_MOUSE_FOCUS))
#else
        if (!inputFocus_ && (flags & SDL_WINDOW_INPUT_FOCUS))
#endif
            focusedThisFrame_ = true;

        if (focusedThisFrame_)
            GainFocus();

        if (inputFocus_ && (flags & SDL_WINDOW_INPUT_FOCUS) == 0)
            LoseFocus();
    }
    else
        return;

    // Check for relative mode mouse move
    if (graphics_->GetExternalWindow() || (!mouseVisible_ && inputFocus_ && (flags & SDL_WINDOW_MOUSE_FOCUS)))
    {
        IntVector2 mousePosition = GetMousePosition();
        mouseMove_ = mousePosition - lastMousePosition_;

        if (graphics_->GetExternalWindow())
            lastMousePosition_ = mousePosition;
        else
        {
            // Recenter the mouse cursor manually
            IntVector2 center(graphics_->GetWidth() / 2, graphics_->GetHeight() / 2);
            if (mousePosition != center)
            {
                SetMousePosition(center);
                lastMousePosition_ = center;
            }
        }

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

                VariantMap& eventData = GetEventDataMap();
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
}

void Input::SetMouseVisible(bool enable)
{
    // SDL Raspberry Pi "video driver" does not have proper OS mouse support yet, so no-op for now
    #ifndef RASPI
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

        using namespace MouseVisibleChanged;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_VISIBLE] = mouseVisible_;
        SendEvent(E_MOUSEVISIBLECHANGED, eventData);
    }
    #endif
}

void Input::SetToggleFullscreen(bool enable)
{
    toggleFullscreen_ = enable;
}

bool Input::DetectJoysticks()
{
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    ResetJoysticks();
    return true;
}

unsigned Input::AddScreenJoystick(bool injectAsKeyEvents, XMLFile* layoutFile, XMLFile* styleFile)
{
    if (!graphics_)
    {
        LOGWARNING("Cannot add screen joystick in headless mode");
        return M_MAX_UNSIGNED;
    }

    // If layout file is not given, use the default screen joystick layout
    if (!layoutFile)
    {
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        layoutFile = cache->GetResource<XMLFile>("UI/ScreenJoystick.xml");
        if (!layoutFile)    // Error is already logged
            return M_MAX_UNSIGNED;
    }

    UI* ui = GetSubsystem<UI>();
    SharedPtr<UIElement> screenJoystick = ui->LoadLayout(layoutFile, styleFile);
    if (!screenJoystick)     // Error is already logged
        return M_MAX_UNSIGNED;

    screenJoystick->SetSize(ui->GetRoot()->GetSize());
    screenJoystick->SetVisible(false);      // Set to visible when it is "open" later
    screenJoystick->SetVar(VAR_INJECT_AS_KEY_EVENTS, injectAsKeyEvents);
    ui->GetRoot()->AddChild(screenJoystick);
    unsigned index = joysticks_.Size();
    joysticks_.Resize(index + 1);
    JoystickState& state = joysticks_[index];
    joystickIDMap_[SCREEN_JOYSTICK_START_INDEX + index] = index;
    state.name_ = screenJoystick->GetName();
    state.screenJoystick_ = screenJoystick;

    unsigned numButtons = 0;
    unsigned numAxes = 0;
    unsigned numHats = 0;
    const Vector<SharedPtr<UIElement> >& children = state.screenJoystick_->GetChildren();
    for (Vector<SharedPtr<UIElement> >::ConstIterator iter = children.Begin(); iter != children.End(); ++iter)
    {
        UIElement* element = iter->Get();
        String name = element->GetName();
        if (name.StartsWith("Button"))
        {
            ++numButtons;

            // Check whether the button has key binding
            if (injectAsKeyEvents)
            {
                Text* text = dynamic_cast<Text*>(element->GetChild("KeyBinding", false));
                if (text)
                {
                    text->SetVisible(false);
                    const String& key = text->GetText();
                    if (key.Length() == 1)
                        element->SetVar(VAR_BUTTON_KEY_BINDING, key);
                    else if (key == "SPACE")
                        element->SetVar(VAR_BUTTON_KEY_BINDING, KEY_SPACE);
                    else if (key == "LCTRL")
                        element->SetVar(VAR_BUTTON_KEY_BINDING, KEY_LCTRL);
                    else if (key == "RCTRL")
                        element->SetVar(VAR_BUTTON_KEY_BINDING, KEY_RCTRL);
                    else if (key == "LSHIFT")
                        element->SetVar(VAR_BUTTON_KEY_BINDING, KEY_LSHIFT);
                    else if (key == "RSHIFT")
                        element->SetVar(VAR_BUTTON_KEY_BINDING, KEY_RSHIFT);
                    else if (key == "LALT")
                        element->SetVar(VAR_BUTTON_KEY_BINDING, KEY_LALT);
                    else if (key == "RALT")
                        element->SetVar(VAR_BUTTON_KEY_BINDING, KEY_RALT);
                    else if (key == "TAB")
                        element->SetVar(VAR_BUTTON_KEY_BINDING, KEY_TAB);
                    else if (key == "RETURN")
                        element->SetVar(VAR_BUTTON_KEY_BINDING, KEY_RETURN);
                    else if (key == "LEFT")
                        element->SetVar(VAR_BUTTON_KEY_BINDING, KEY_LEFT);
                    else if (key == "RIGHT")
                        element->SetVar(VAR_BUTTON_KEY_BINDING, KEY_RIGHT);
                    else if (key == "UP")
                        element->SetVar(VAR_BUTTON_KEY_BINDING, KEY_UP);
                    else if (key == "DOWN")
                        element->SetVar(VAR_BUTTON_KEY_BINDING, KEY_DOWN);
                }
            }
        }
        else if (name.StartsWith("Axis"))
            ++numAxes;
        else if (name.StartsWith("Hat"))
            ++numHats;
        element->SetVar(VAR_SCREEN_JOYSTICK_INDEX, index);
    }

    state.buttons_.Resize(numButtons);
    state.buttonPress_.Resize(numButtons);
    state.axes_.Resize(numAxes);
    state.hats_.Resize(numHats);

    // There could be potentially more than one screen joystick, however they all will be handled by a same handler
    // So there is no harm to replace the old handler with the new handler in each call to SubscribeToEvent()
    SubscribeToEvent(E_UIMOUSECLICK, HANDLER(Input, HandleMouseClick));
    SubscribeToEvent(E_UIMOUSECLICKEND, HANDLER(Input, HandleMouseClick));

    return index;
}

void Input::SetScreenKeyboardVisible(bool enable)
{
    if (!graphics_)
        return;

    if (enable != IsScreenKeyboardVisible())
    {
        if (enable)
            SDL_StartTextInput();
        else
            SDL_StopTextInput();
    }
}

bool Input::OpenJoystick(unsigned index)
{
    if (index >= joysticks_.Size())
    {
        LOGERRORF("Joystick index #%d is out of bound.", index);
        return false;
    }

    // Check if already opened
    JoystickState& state = joysticks_[index];
    if (joysticks_[index].joystick_ || (state.screenJoystick_ && state.screenJoystick_->IsVisible()))
        return true;

    if (state.screenJoystick_)
        state.screenJoystick_->SetVisible(true);
    else
    {
        SDL_Joystick* joystick = SDL_JoystickOpen(index);
        if (!joystick)
        {
            LOGERRORF("Cannot open joystick #%d (%s)", index, joysticks_[index].name_.CString());
            return false;
        }

        // Map SDL joystick index to internal index (which starts at 0)
        int sdl_joy_instance_id = SDL_JoystickInstanceID(joystick);
        joystickIDMap_[sdl_joy_instance_id] = index;

        state.joystick_ = joystick;
        if (SDL_IsGameController(index))
            state.controller_ = SDL_GameControllerOpen(index);

        state.buttons_.Resize(SDL_JoystickNumButtons(joystick));
        state.buttonPress_.Resize(state.buttons_.Size());
        state.axes_.Resize(SDL_JoystickNumAxes(joystick));
        state.hats_.Resize(SDL_JoystickNumHats(joystick));
    }

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

void Input::CloseJoystick(unsigned index)
{
    if (index >= joysticks_.Size())
        return;

    JoystickState& state = joysticks_[index];
    if (joysticks_[index].joystick_)
    {
        SDL_JoystickClose(state.joystick_);
        state.joystick_ = 0;
        state.controller_ = 0;
        state.buttons_.Clear();
        state.axes_.Clear();
        state.hats_.Clear();
    }
    else if (state.screenJoystick_ && state.screenJoystick_->IsVisible())
        state.screenJoystick_->SetVisible(false);
}

int Input::GetKeyFromName(const String& name) const
{
    return SDL_GetKeyFromName(name.CString());
}

int Input::GetKeyFromScancode(int scancode) const
{
    return SDL_GetKeyFromScancode((SDL_Scancode)scancode);
}

String Input::GetKeyName(int key) const
{
    return String(SDL_GetKeyName(key));
}

int Input::GetScancodeFromKey(int key) const
{
    return SDL_GetScancodeFromKey(key);
}

int Input::GetScancodeFromName(const String& name) const
{
    return SDL_GetScancodeFromName(name.CString());
}

String Input::GetScancodeName(int scancode) const
{
    return SDL_GetScancodeName((SDL_Scancode)scancode);
}

bool Input::GetKeyDown(int key) const
{
    return keyDown_.Contains(key);
}

bool Input::GetKeyPress(int key) const
{
    return keyPress_.Contains(key);
}

bool Input::GetScancodeDown(int scancode) const
{
    return scancodeDown_.Contains(scancode);
}

bool Input::GetScancodePress(int scancode) const
{
    return scancodePress_.Contains(scancode);
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
    return index < joysticks_.Size() ? joysticks_[index].name_ : String::EMPTY;
}

JoystickState* Input::GetJoystick(unsigned index)
{
    if (index < joysticks_.Size())
    {
        JoystickState& state = joysticks_[index];

        // If necessary, automatically open the joystick first
        if ((!state.joystick_ && !state.screenJoystick_) || (state.screenJoystick_ && !state.screenJoystick_->IsVisible()))
            OpenJoystick(index);

        return const_cast<JoystickState*>(&state);
    }
    else
        return 0;
}

bool Input::GetScreenKeyboardSupport() const
{
    return graphics_ ? SDL_HasScreenKeyboardSupport() : false;
}

bool Input::IsScreenKeyboardVisible() const
{
    if (graphics_)
    {
        SDL_Window* window = graphics_->GetImpl()->GetWindow();
        return SDL_IsScreenKeyboardShown(window);
    }
    else
        return false;
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
    scancodeDown_.Clear();
    scancodePress_.Clear();

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

        VariantMap& eventData = GetEventDataMap();
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

    VariantMap& eventData = GetEventDataMap();
    eventData[P_FOCUS] = HasFocus();
    eventData[P_MINIMIZED] = IsMinimized();
    SendEvent(E_INPUTFOCUS, eventData);
}

void Input::SetMouseButton(int button, bool newState)
{
#ifdef REQUIRE_CLICK_TO_FOCUS
    if (!mouseVisible_ && !graphics_->GetFullscreen())
    {
        if (!inputFocus_ && newState && button == MOUSEB_LEFT)
            focusedThisFrame_ = true;
    }
#endif

    // If we do not have focus yet, do not react to the mouse button down
    if (!graphics_->GetExternalWindow() && newState && !inputFocus_)
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

    VariantMap& eventData = GetEventDataMap();
    eventData[P_BUTTON] = button;
    eventData[P_BUTTONS] = mouseButtonDown_;
    eventData[P_QUALIFIERS] = GetQualifiers();
    SendEvent(newState ? E_MOUSEBUTTONDOWN : E_MOUSEBUTTONUP, eventData);
}

void Input::SetKey(int key, int scancode, unsigned raw, bool newState)
{
    // If we do not have focus yet, do not react to the key down
    if (!graphics_->GetExternalWindow() && newState && !inputFocus_)
        return;

    bool repeat = false;

    if (newState)
    {
        scancodeDown_.Insert(scancode);
        scancodePress_.Insert(scancode);

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
        scancodeDown_.Erase(scancode);

        if (!keyDown_.Erase(key))
            return;
    }

    using namespace KeyDown;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_KEY] = key;
    eventData[P_SCANCODE] = scancode;
    eventData[P_RAW] = raw;
    eventData[P_BUTTONS] = mouseButtonDown_;
    eventData[P_QUALIFIERS] = GetQualifiers();
    if (newState)
        eventData[P_REPEAT] = repeat;
    SendEvent(newState ? E_KEYDOWN : E_KEYUP, eventData);

    if ((key == KEY_RETURN || key == KEY_RETURN2 || key == KEY_KP_ENTER) && newState && !repeat && toggleFullscreen_ &&
        (GetKeyDown(KEY_LALT) || GetKeyDown(KEY_RALT)))
        graphics_->ToggleFullscreen();
}

void Input::SetMouseWheel(int delta)
{
    // If we do not have focus yet, do not react to the wheel
    if (!graphics_->GetExternalWindow() && !inputFocus_)
        return;

    if (delta)
    {
        mouseMoveWheel_ += delta;

        using namespace MouseWheel;

        VariantMap& eventData = GetEventDataMap();
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
        SetKey(ConvertSDLKeyCode(evt.key.keysym.sym, evt.key.keysym.scancode), evt.key.keysym.scancode, evt.key.keysym.raw, true);
        break;

    case SDL_KEYUP:
        SetKey(ConvertSDLKeyCode(evt.key.keysym.sym, evt.key.keysym.scancode), evt.key.keysym.scancode, evt.key.keysym.raw, false);
        break;

    case SDL_TEXTINPUT:
        {
            textInput_ = &evt.text.text[0];
            unsigned unicode = textInput_.AtUTF8(0);
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

    case SDL_MOUSEBUTTONDOWN:
        SetMouseButton(1 << (evt.button.button - 1), true);
        break;

    case SDL_MOUSEBUTTONUP:
        SetMouseButton(1 << (evt.button.button - 1), false);
        break;

    case SDL_MOUSEMOTION:
        if (mouseVisible_)
        {
            mouseMove_.x_ += evt.motion.xrel;
            mouseMove_.y_ += evt.motion.yrel;

            using namespace MouseMove;

            VariantMap& eventData = GetEventDataMap();
            if (mouseVisible_)
            {
                eventData[P_X] = evt.motion.x;
                eventData[P_Y] = evt.motion.y;
            }
            eventData[P_DX] = evt.motion.xrel;
            eventData[P_DY] = evt.motion.yrel;
            eventData[P_BUTTONS] = mouseButtonDown_;
            eventData[P_QUALIFIERS] = GetQualifiers();
            SendEvent(E_MOUSEMOVE, eventData);
        }
        break;

    case SDL_MOUSEWHEEL:
        SetMouseWheel(evt.wheel.y);
        break;

    case SDL_FINGERDOWN:
        if (evt.tfinger.touchId != SDL_TOUCH_MOUSEID)
        {
            int touchID = evt.tfinger.fingerId & 0x7ffffff;
            TouchState& state = touches_[touchID];
            state.touchID_ = touchID;
            state.lastPosition_ = state.position_ = IntVector2((int)(evt.tfinger.x * graphics_->GetWidth()),
                (int)(evt.tfinger.y * graphics_->GetHeight()));
            state.delta_ = IntVector2::ZERO;
            state.pressure_ = evt.tfinger.pressure;

            using namespace TouchBegin;

            VariantMap& eventData = GetEventDataMap();
            eventData[P_TOUCHID] = touchID;
            eventData[P_X] = state.position_.x_;
            eventData[P_Y] = state.position_.y_;
            eventData[P_PRESSURE] = state.pressure_;
            SendEvent(E_TOUCHBEGIN, eventData);
        }
        break;

    case SDL_FINGERUP:
        if (evt.tfinger.touchId != SDL_TOUCH_MOUSEID)
        {
            int touchID = evt.tfinger.fingerId & 0x7ffffff;
            TouchState& state = touches_[touchID];

            using namespace TouchEnd;

            VariantMap& eventData = GetEventDataMap();
            // Do not trust the position in the finger up event. Instead use the last position stored in the
            // touch structure
            eventData[P_TOUCHID] = touchID;
            eventData[P_X] = state.position_.x_;
            eventData[P_Y] = state.position_.y_;

            touches_.Erase(touchID);
            SendEvent(E_TOUCHEND, eventData);
        }
        break;

    case SDL_FINGERMOTION:
        if (evt.tfinger.touchId != SDL_TOUCH_MOUSEID)
        {
            int touchID = evt.tfinger.fingerId & 0x7ffffff;
            TouchState& state = touches_[touchID];
            state.touchID_ = touchID;
            state.position_ = IntVector2((int)(evt.tfinger.x * graphics_->GetWidth()),
                (int)(evt.tfinger.y * graphics_->GetHeight()));
            state.delta_ = state.position_ - state.lastPosition_;
            state.pressure_ = evt.tfinger.pressure;

            using namespace TouchMove;

            VariantMap& eventData = GetEventDataMap();
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

            unsigned button = evt.jbutton.button;
            unsigned joystickIndex = joystickIDMap_[evt.jbutton.which];

            VariantMap& eventData = GetEventDataMap();
            eventData[P_JOYSTICK] = joystickIndex;
            eventData[P_BUTTON] = button;

            if (joystickIndex < joysticks_.Size() && button < joysticks_[joystickIndex].buttons_.Size()) {
                joysticks_[joystickIndex].buttons_[button] = true;
                joysticks_[joystickIndex].buttonPress_[button] = true;
                SendEvent(E_JOYSTICKBUTTONDOWN, eventData);
            }
        }
        break;

    case SDL_JOYBUTTONUP:
        {
            using namespace JoystickButtonUp;

            unsigned button = evt.jbutton.button;
            unsigned joystickIndex = joystickIDMap_[evt.jbutton.which];

            VariantMap& eventData = GetEventDataMap();
            eventData[P_JOYSTICK] = joystickIndex;
            eventData[P_BUTTON] = button;

            if (joystickIndex < joysticks_.Size() && button < joysticks_[joystickIndex].buttons_.Size()) {
                joysticks_[joystickIndex].buttons_[button] = false;
                SendEvent(E_JOYSTICKBUTTONUP, eventData);
            }
        }
        break;

    case SDL_JOYAXISMOTION:
        {
            using namespace JoystickAxisMove;

            unsigned joystickIndex = joystickIDMap_[evt.jaxis.which];

            VariantMap& eventData = GetEventDataMap();
            eventData[P_JOYSTICK] = joystickIndex;
            eventData[P_AXIS] = evt.jaxis.axis;
            eventData[P_POSITION] = Clamp((float)evt.jaxis.value / 32767.0f, -1.0f, 1.0f);

            if (joystickIndex < joysticks_.Size() && evt.jaxis.axis <
                joysticks_[joystickIndex].axes_.Size())
            {
                joysticks_[joystickIndex].axes_[evt.jaxis.axis] = eventData[P_POSITION].GetFloat();
                SendEvent(E_JOYSTICKAXISMOVE, eventData);
            }
        }
        break;

    case SDL_JOYHATMOTION:
        {
            using namespace JoystickHatMove;

            unsigned joystickIndex = joystickIDMap_[evt.jaxis.which];

            VariantMap& eventData = GetEventDataMap();
            eventData[P_JOYSTICK] = joystickIndex;
            eventData[P_HAT] = evt.jhat.hat;
            eventData[P_POSITION] = evt.jhat.value;

            if (joystickIndex < joysticks_.Size() && evt.jhat.hat <
                joysticks_[joystickIndex].hats_.Size())
            {
                joysticks_[joystickIndex].hats_[evt.jhat.hat] = evt.jhat.value;
                SendEvent(E_JOYSTICKHATMOVE, eventData);
            }
        }
        break;

    case SDL_CONTROLLERBUTTONDOWN:
        {
            using namespace ControllerButtonDown;

            unsigned button = evt.cbutton.button;
            unsigned joystickIndex = joystickIDMap_[evt.cbutton.which];

            VariantMap& eventData = GetEventDataMap();
            eventData[P_JOYSTICK] = joystickIndex;
            eventData[P_BUTTON] = button;

            if (joystickIndex < joysticks_.Size() && button < joysticks_[joystickIndex].buttons_.Size()) {
                joysticks_[joystickIndex].buttons_[button] = true;
                joysticks_[joystickIndex].buttonPress_[button] = true;
                SendEvent(E_CONTROLLERBUTTONDOWN, eventData);
            }
        }
        break;

    case SDL_CONTROLLERBUTTONUP:
        {
            using namespace ControllerButtonUp;

            unsigned button = evt.cbutton.button;
            unsigned joystickIndex = joystickIDMap_[evt.cbutton.which];

            VariantMap& eventData = GetEventDataMap();
            eventData[P_JOYSTICK] = joystickIndex;
            eventData[P_BUTTON] = button;

            if (joystickIndex < joysticks_.Size() && button < joysticks_[joystickIndex].buttons_.Size()) {
                joysticks_[joystickIndex].buttons_[button] = false;
                SendEvent(E_CONTROLLERBUTTONUP, eventData);
            }
        }
        break;

    case SDL_CONTROLLERAXISMOTION:
        {
            using namespace ControllerAxisMove;

            unsigned joystickIndex = joystickIDMap_[evt.caxis.which];

            VariantMap& eventData = GetEventDataMap();
            eventData[P_JOYSTICK] = joystickIndex;
            eventData[P_AXIS] = evt.caxis.axis;
            eventData[P_POSITION] = Clamp((float)evt.caxis.value / 32767.0f, -1.0f, 1.0f);

            if (joystickIndex < joysticks_.Size() && evt.caxis.axis <
                joysticks_[joystickIndex].axes_.Size())
            {
                joysticks_[joystickIndex].axes_[evt.caxis.axis] = eventData[P_POSITION].GetFloat();
                SendEvent(E_CONTROLLERAXISMOVE, eventData);
            }
        }
        break;

    case SDL_WINDOWEVENT:
        {
            switch (evt.window.event)
            {
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
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                // Restore GPU objects to the new GL context
                graphics_->Restore();
                break;
            #endif

            case SDL_WINDOWEVENT_RESIZED:
                graphics_->WindowResized();
                break;
            }
        }
        break;

    case SDL_DROPFILE:
        {
            using namespace DropFile;

            VariantMap& eventData = GetEventDataMap();
            eventData[P_FILENAME] = GetInternalPath(String(evt.drop.file));
            SDL_free(evt.drop.file);

            SendEvent(E_DROPFILE, eventData);
        }
        break;

    case SDL_QUIT:
        SendEvent(E_EXITREQUESTED);
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

void Input::HandleMouseClick(StringHash eventType, VariantMap& eventData)
{
    using namespace UIMouseClickEnd;

    // Only interested in events from screen joystick(s)
    UIElement* element = static_cast<UIElement*>(eventData[eventType == E_UIMOUSECLICK ? P_ELEMENT : P_BEGINELEMENT].GetPtr());
    if (!element)
        return;
    Variant variant = element->GetVar(VAR_SCREEN_JOYSTICK_INDEX);
    if (variant.IsEmpty())
        return;
    unsigned index = variant.GetUInt();

    int x = eventData[P_X].GetInt();
    int y = eventData[P_Y].GetInt();

    // Prepare a fake SDL event
    SDL_Event evt;

    const String& name = element->GetName();
    if (name.StartsWith("Button"))
    {
        // Determine whether to inject a joystick event or keyboard event
        if (joysticks_[index].screenJoystick_->GetVar(VAR_INJECT_AS_KEY_EVENTS).GetBool())
        {
            Variant variant = element->GetVar(VAR_BUTTON_KEY_BINDING);
            if (variant.IsEmpty())
                return;

            evt.type = eventType == E_UIMOUSECLICK ? SDL_KEYDOWN : SDL_KEYUP;
            evt.key.keysym.sym = variant.GetInt();
            evt.key.keysym.scancode = SDL_SCANCODE_UNKNOWN;
        }
        else
        {
            evt.type = eventType == E_UIMOUSECLICK ? SDL_JOYBUTTONDOWN : SDL_JOYBUTTONUP;
            evt.jbutton.which = SCREEN_JOYSTICK_START_INDEX + index;
            evt.jbutton.button = ToUInt(name.Substring(6));
        }
    }
    else if (name.StartsWith("Hat"))
    {
        if (joysticks_[index].screenJoystick_->GetVar(VAR_INJECT_AS_KEY_EVENTS).GetBool())
        {
            evt.type = eventType == E_UIMOUSECLICK ? SDL_KEYDOWN : SDL_KEYUP;
            IntVector2 relPosition = IntVector2(x, y) - element->GetScreenPosition() - element->GetSize() / 2;
            if (relPosition.y_ < 0 && Abs(relPosition.x_ * 3 / 2) < Abs(relPosition.y_))
            {
                evt.key.keysym.sym = SDLK_w;
                evt.key.keysym.scancode = SDL_SCANCODE_W;
            }
            else if (relPosition.y_ > 0 && Abs(relPosition.x_ * 3 / 2) < Abs(relPosition.y_))
            {
                evt.key.keysym.sym = SDLK_s;
                evt.key.keysym.scancode = SDL_SCANCODE_S;
            }
            else if (relPosition.x_ < 0 && Abs(relPosition.y_ * 3 / 2) < Abs(relPosition.x_))
            {
                evt.key.keysym.sym = SDLK_a;
                evt.key.keysym.scancode = SDL_SCANCODE_A;
            }
            else if (relPosition.x_ > 0 && Abs(relPosition.y_ * 3 / 2) < Abs(relPosition.x_))
            {
                evt.key.keysym.sym = SDLK_d;
                evt.key.keysym.scancode = SDL_SCANCODE_D;
            }
        }
        else
        {
            evt.type = SDL_JOYHATMOTION;
            evt.jaxis.which = SCREEN_JOYSTICK_START_INDEX + index;
            evt.jhat.hat = ToUInt(name.Substring(3));
            evt.jhat.value = HAT_CENTER;
            if (eventType == E_UIMOUSECLICK)
            {
                IntVector2 relPosition = IntVector2(x, y) - element->GetScreenPosition() - element->GetSize() / 2;
                if (relPosition.y_ < 0 && Abs(relPosition.x_ * 3 / 2) < Abs(relPosition.y_))
                    evt.jhat.value |= HAT_UP;
                if (relPosition.y_ > 0 && Abs(relPosition.x_ * 3 / 2) < Abs(relPosition.y_))
                    evt.jhat.value |= HAT_DOWN;
                if (relPosition.x_ < 0 && Abs(relPosition.y_ * 3 / 2) < Abs(relPosition.x_))
                    evt.jhat.value |= HAT_LEFT;
                if (relPosition.x_ > 0 && Abs(relPosition.y_ * 3 / 2) < Abs(relPosition.x_))
                    evt.jhat.value |= HAT_RIGHT;
            }
        }
    }
    else
        return;

    // Handle the fake SDL event to turn it into Urho3D genuine event
    HandleSDLEvent(&evt);
}

}
