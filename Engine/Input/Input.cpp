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

#include "Input.h"
#include "Log.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererEvents.h"

#include <cstring>
#include <windows.h>

#include "DebugNew.h"

Input::Input(Renderer* renderer) :
    mRenderer(renderer),
    mClipCursor(true),
    mShowCursor(true),
    mToggleFullscreen(true),
    mActive(false),
    mMinimized(false),
    mActivated(true),
    mSuppressNextChar(false)
{
    LOGINFO("Input created");
    
    // Zero the initial state so that clearState() does not send any extra events at the start
    memset(&mKeyDown, 0, sizeof(mKeyDown));
    memset(&mKeyPress, 0, sizeof(mKeyPress));
    mMouseButtonDown = 0;
    mMouseButtonPress = 0;
    mLastMousePosition = IntVector2::sZero;
    
    if (mRenderer)
    {
        subscribeToEvent(mRenderer, EVENT_WINDOWMESSAGE, EVENT_HANDLER(Input, handleWindowMessage));
        subscribeToEvent(mRenderer, EVENT_SCREENMODE, EVENT_HANDLER(Input, handleScreenMode));
    }
    
    // Perform the initial update immediately so that the mouse cursor gets hidden
    update();
}

Input::~Input()
{
    LOGINFO("Input shut down");
}

void Input::update()
{
    PROFILE(Input_Update);
    
    if (!mRenderer)
        return;
    
    memset(mKeyPress, 0, sizeof(mKeyPress));
    mMouseButtonPress = 0;
    mMouseMove = IntVector2::sZero;
    mMouseMoveWheel = 0;
    
    mRenderer->messagePump();
    
    if (mActivated)
        makeActive();
    
    checkMouseMove();
}

void Input::setClipCursor(bool enable)
{
    mClipCursor = enable;
    if (!mRenderer)
        return;
    
    if ((!mRenderer->getFullscreen()) && (mActive) && (mClipCursor))
    {
        HWND window = (HWND)mRenderer->getWindowHandle();
        RECT clipRect;
        
        setMousePosition(mRenderer->getWidth() / 2, mRenderer->getHeight() / 2);
        mLastMousePosition = getMousePosition();
        GetWindowRect(window, &clipRect);
        ClipCursor(&clipRect);
    }
    else
    {
        if ((mRenderer->getFullscreen()) && (mActive) && (mClipCursor))
        {
            setMousePosition(mRenderer->getWidth() / 2, mRenderer->getHeight() / 2);
            mLastMousePosition = getMousePosition();
        }
        ClipCursor(0);
    }
}

void Input::setToggleFullscreen(bool enable)
{
    mToggleFullscreen = enable;
}

void Input::setMousePosition(const IntVector2& position)
{
    POINT point;
    point.x = position.mX;
    point.y = position.mY;
    ClientToScreen((HWND)mRenderer->getWindowHandle(), &point);
    SetCursorPos(point.x, point.y);
}

void Input::setMousePosition(int x, int y)
{
    setMousePosition(IntVector2(x, y));
}

void Input::suppressNextChar()
{
    mSuppressNextChar = true;
}

bool Input::getKeyDown(int key) const
{
    if ((key < 0) || (key >= MAX_KEYS))
        return false;
    
    return mKeyDown[key];
}

bool Input::getKeyPress(int key) const
{
    if ((key < 0) || (key >= MAX_KEYS))
        return false;
    
    return mKeyPress[key];
}

IntVector2 Input::getMousePosition() const
{
    POINT mouse;
    GetCursorPos(&mouse);
    ScreenToClient((HWND)mRenderer->getWindowHandle(), &mouse);
    return IntVector2(mouse.x, mouse.y);
}

bool Input::getMouseButtonDown(int button) const
{
    return (mMouseButtonDown & button) != 0;
}

bool Input::getMouseButtonPress(int button) const
{
    return (mMouseButtonPress & button) != 0;
}

bool Input::getQualifierDown(int qualifier) const
{
    if (qualifier == QUAL_SHIFT)
        return mKeyDown[KEY_SHIFT] != 0;
    if (qualifier == QUAL_CTRL)
        return mKeyDown[KEY_CTRL] != 0;
    return false;
}

bool Input::getQualifierPress(int qualifier) const
{
    if (qualifier == QUAL_SHIFT)
        return mKeyPress[KEY_SHIFT] != 0;
    if (qualifier == QUAL_CTRL)
        return mKeyPress[KEY_CTRL] != 0;
    return false;
}

int Input::getQualifiers() const
{
    int ret = 0;
    if (mKeyDown[KEY_SHIFT] != 0)
        ret |= QUAL_SHIFT;
    if (mKeyDown[KEY_CTRL] != 0)
        ret |= QUAL_CTRL;
    return ret;
}

void Input::handleWindowMessage(StringHash eventType, VariantMap& eventData)
{
    using namespace WindowMessage;
    
    if (!mRenderer)
        return;
    
    int msg = eventData[P_MSG].getInt();
    int wParam = eventData[P_WPARAM].getInt();
    int lParam = eventData[P_LPARAM].getInt();
    
    switch (msg)
    {
    case WM_LBUTTONDOWN:
        mouseButtonChange(MOUSEB_LEFT, true);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_NCLBUTTONUP:
        case WM_LBUTTONUP:
        mouseButtonChange(MOUSEB_LEFT, false);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_RBUTTONDOWN:
        mouseButtonChange(MOUSEB_RIGHT, true);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_NCRBUTTONUP:
    case WM_RBUTTONUP:
        mouseButtonChange(MOUSEB_RIGHT, false);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_MBUTTONDOWN:
        mouseButtonChange(MOUSEB_MIDDLE, true);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_NCMBUTTONUP:
    case WM_MBUTTONUP:
        mouseButtonChange(MOUSEB_MIDDLE, false);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_MOUSEWHEEL:
        mouseWheelChange(wParam >> 16);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_ACTIVATE:
        if (LOWORD(wParam) == WA_INACTIVE)
        {
            makeInactive();
            if (mRenderer->getFullscreen())
                mMinimized = true;
        }
        else
        {
            if (!mMinimized)
               mActivated = true;
        }
        eventData[P_HANDLED] = true;
        break;
        
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
        {
            mMinimized = true;
            makeInactive();
        }
        if ((wParam == SIZE_RESTORED) || (wParam == SIZE_MAXIMIZED))
        {
            mMinimized = false;
            mActivated = true;
        }
        eventData[P_HANDLED] = true;
        break;
        
    case WM_KEYDOWN:
        keyChange(wParam, true);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_SYSKEYDOWN:
        keyChange(wParam, true);
        if ((wParam == KEY_RETURN) && (mToggleFullscreen))
            mRenderer->toggleFullscreen();
        if (wParam != KEY_F4)
            eventData[P_HANDLED] = true;
        break;
        
    case WM_KEYUP:
        keyChange(wParam, false);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_SYSKEYUP:
        keyChange(wParam, false);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_CHAR:
        if (!mSuppressNextChar)
        {
            using namespace Char;
            
            VariantMap keyEventData;
            keyEventData[P_CHAR] = wParam;
            eventData[P_BUTTONS] = mMouseButtonDown;
            eventData[P_QUALIFIERS] = getQualifiers();
            sendEvent(EVENT_CHAR, keyEventData);
        }
        mSuppressNextChar = false;
        eventData[P_HANDLED] = true;
        break;
        
    case WM_SETCURSOR:
        if ((lParam & 0xffff) == HTCLIENT)
        {
            setCursorVisible(false);
            eventData[P_HANDLED] = true;
        }
        else
            setCursorVisible(true);
        break;
    }
}

void Input::handleScreenMode(StringHash eventType, VariantMap& eventData)
{
    // Screen mode change may affect the cursor clipping behaviour. Also re-center the cursor (if needed) to the
    // new screen size, so that there is no erroneous mouse move event
    setClipCursor(mClipCursor);
}

void Input::makeActive()
{
    clearState();
    
    if (!mRenderer)
    {
        mActive = true;
        return;
    }
    
    mActive = true;
    mActivated = false;
    
    // Re-establish mouse cursor clipping if necessary
    setClipCursor(mClipCursor);
    setCursorVisible(false);
    
    sendEvent(EVENT_ACTIVATED);
}

void Input::makeInactive()
{
    clearState();
    
    if (!mRenderer)
    {
        mActive = false;
        return;
    }
    
    mActive = false;
    mActivated = false;
    
    // Free and show the mouse cursor
    ReleaseCapture();
    ClipCursor(0);
    setCursorVisible(true);
    
    sendEvent(EVENT_INACTIVATED);
}

void Input::clearState()
{
    // Use keyChange() & mouseButtonChange() to reset the state so that events will be sent properly
    for (unsigned i = 0; i < MAX_KEYS; ++i)
        keyChange(i, false);
    mouseButtonChange(MOUSEB_LEFT, false);
    mouseButtonChange(MOUSEB_RIGHT, false);
    mouseButtonChange(MOUSEB_MIDDLE, false);
    
    mMouseMove = IntVector2::sZero;
    mMouseMoveWheel = 0;
    mMouseButtonPress = 0;
    memset(&mKeyPress, 0, sizeof(mKeyPress));
}

void Input::mouseButtonChange(int button, bool newState)
{
    // If we are not active yet, do not react to the mouse button down
    if ((newState) && (!mActive))
        return;
    
    // Check mouse move before sending the button up/down so that the click will be interpreted correctly
    //checkMouseMove();
    
    if (newState)
    {
        if (!(mMouseButtonDown & button))
            mMouseButtonPress |= button;
        
        mMouseButtonDown |= button;
    }
    else
    {
        if (!(mMouseButtonDown & button))
            return;
        
        mMouseButtonDown &= ~button;
    }
    
    using namespace MouseButtonDown;
    
    VariantMap eventData;
    eventData[P_BUTTON] = button;
    eventData[P_BUTTONS] = mMouseButtonDown;
    eventData[P_QUALIFIERS] = getQualifiers();
    sendEvent(newState ? EVENT_MOUSEBUTTONDOWN : EVENT_MOUSEBUTTONUP, eventData);
    
    // In non-confined mode, while any of the mouse buttons are down, capture the mouse so that we get the button release reliably
    if ((mRenderer) && (!mClipCursor))
    {
        if (mMouseButtonDown)
            SetCapture((HWND)mRenderer->getWindowHandle());
        else
            ReleaseCapture();
    }
}

void Input::keyChange(int key, bool newState)
{
    if ((key < 0) || (key >= MAX_KEYS))
        return;
    
    if (newState)
    {
        if (!mKeyDown[key])
            mKeyPress[key] = true;
    }
    else
    {
        if (!mKeyDown[key])
            return;
    }
    
    mKeyDown[key] = newState;
    
    using namespace KeyDown;
    
    VariantMap eventData;
    eventData[P_KEY] = key;
    eventData[P_BUTTONS] = mMouseButtonDown;
    eventData[P_QUALIFIERS] = getQualifiers();
    sendEvent(newState ? EVENT_KEYDOWN : EVENT_KEYUP, eventData);
}

void Input::mouseWheelChange(int delta)
{
    if (!mActive)
        return;
    
    if (delta)
    {
        mMouseMoveWheel += delta;
        
        using namespace MouseWheel;
        
        VariantMap eventData;
        eventData[P_WHEEL] = delta;
        eventData[P_BUTTONS] = mMouseButtonDown;
        eventData[P_QUALIFIERS] = getQualifiers();
        sendEvent(EVENT_MOUSEWHEEL, eventData);
    }
}
void Input::checkMouseMove()
{
    if (!mActive)
        return;
    
    IntVector2 mousePos = getMousePosition();
    IntVector2 mouseMove = mousePos - mLastMousePosition;
    
    if ((mClipCursor) && (mouseMove != IntVector2::sZero))
    {
        IntVector2 center(mRenderer->getWidth() / 2, mRenderer->getHeight() / 2);
        setMousePosition(center);
        mLastMousePosition = getMousePosition();
    }
    else
        mLastMousePosition = mousePos;
    
    if (mouseMove != IntVector2::sZero)
    {
        mMouseMove += mouseMove;
        
        using namespace MouseMove;
        
        VariantMap eventData;
        eventData[P_X] = mLastMousePosition.mX;
        eventData[P_Y] = mLastMousePosition.mY;
        eventData[P_DX] = mouseMove.mX;
        eventData[P_DY] = mouseMove.mY;
        eventData[P_BUTTONS] = mMouseButtonDown;
        eventData[P_QUALIFIERS] = getQualifiers();
        eventData[P_CLIPCURSOR] = mClipCursor;
        sendEvent(EVENT_MOUSEMOVE, eventData);
    }
}

void Input::setCursorVisible(bool enable)
{
    // When inactive, always show the cursor
    if (!mActive)
        enable = true;
    
    if (mShowCursor == enable)
        return;
    
    ShowCursor(enable ? TRUE : FALSE);
    mShowCursor = enable;
}
