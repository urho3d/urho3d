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
        subscribeToEvent(mRenderer, EVENT_WINDOWMESSAGE, EVENT_HANDLER(Input, handleWindowMessage));
    
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
    mMouseMoveWheel = 0;
    mRenderer->messagePump();
    
    if (mActivated)
        makeActive();
    
    if (mActive)
    {
        IntVector2 mousePos = getMousePosition();
        
        if (mClipCursor)
        {
            IntVector2 center(mRenderer->getWidth() / 2, mRenderer->getHeight() / 2);
            mMouseMove = mousePos - center;
            setMousePosition(center);
        }
        else
        {
            mMouseMove = mousePos - mLastMousePosition;
            mLastMousePosition = mousePos;
        }
        
        if (mMouseMove != IntVector2::sZero)
        {
            using namespace MouseMove;
            
            VariantMap eventData;
            eventData[P_X] = mMouseMove.mX;
            eventData[P_Y] = mMouseMove.mY;
            eventData[P_POSX] = mousePos.mX;
            eventData[P_POSY] = mousePos.mY;
            eventData[P_BUTTONS] = mMouseButtonDown;
            eventData[P_QUALIFIERS] = getQualifiers();
            eventData[P_CLIPCURSOR] = mClipCursor;
            sendEvent(EVENT_MOUSEMOVE, eventData);
        }
        if (mMouseMoveWheel)
        {
            using namespace MouseWheel;
            
            VariantMap eventData;
            eventData[P_WHEEL] = mMouseMoveWheel;
            eventData[P_BUTTONS] = mMouseButtonDown;
            eventData[P_QUALIFIERS] = getQualifiers();
            sendEvent(EVENT_MOUSEWHEEL, eventData);
        }
    }
    else
    {
        mMouseMove = IntVector2::sZero;
        mMouseMoveWheel = 0;
    }
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
        GetWindowRect(window, &clipRect);
        ClipCursor(&clipRect);
    }
    else
    {
        if ((mRenderer->getFullscreen()) && (mActive) && (mClipCursor))
            setMousePosition(mRenderer->getWidth() / 2, mRenderer->getHeight() / 2);
        
        ClipCursor(0);
    }
    
    mMouseMove = IntVector2::sZero;
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
        mMouseMoveWheel += (wParam >> 16);
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
    }
}

void Input::makeActive()
{
    clearState();
    
    if (!mRenderer)
    {
        mActive = true;
        return;
    }
    
    if (!mActive)
        ShowCursor(FALSE);
    
    mActive = true;
    mActivated = false;
    
    // Re-establish mouse cursor clipping if necessary
    setClipCursor(mClipCursor);
}

void Input::makeInactive()
{
    clearState();
    
    if (!mRenderer)
    {
        mActive = false;
        return;
    }
    
    if (mActive)
    {
        ShowCursor(TRUE);
        ReleaseCapture();
    }
    
    ClipCursor(0);
    
    mActive = false;
    mActivated = false;
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
