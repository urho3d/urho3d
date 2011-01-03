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
    mToggleFullscreen(true),
    mActive(false),
    mMinimized(false),
    mActivated(false)
{
    LOGINFO("Input created");
    
    makeActive();
    
    subscribeToEvent(EVENT_WINDOWMESSAGE, EVENT_HANDLER(Input, handleWindowMessage));
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
    mRenderer->messagePump();
    
    if (mActivated)
        makeActive();
    
    if (mActive)
    {
        if (mRenderer->getFullscreen())
        {
            POINT mouse;
            GetCursorPos(&mouse);
            mMouseMoveX = mouse.x - mRenderer->getWidth() / 2;
            mMouseMoveY = mouse.y - mRenderer->getHeight() / 2;
            SetCursorPos(mRenderer->getWidth() / 2, mRenderer->getHeight() / 2);
        }
        else
        {
            POINT mouse;
            POINT point;
            
            GetCursorPos(&mouse);
            point.x = mRenderer->getWidth() / 2;
            point.y = mRenderer->getHeight() / 2;
            ClientToScreen((HWND)mRenderer->getWindowHandle(), &point);
            mMouseMoveX = mouse.x - point.x;
            mMouseMoveY = mouse.y - point.y;
            SetCursorPos(point.x, point.y);
        }
    }
    else
    {
        mMouseMoveX = 0;
        mMouseMoveY = 0;
    }
    
    if ((mMouseMoveX) || (mMouseMoveY))
    {
        using namespace MouseMove;
        
        VariantMap eventData;
        eventData[P_X] = mMouseMoveX;
        eventData[P_Y] = mMouseMoveY;
        eventData[P_BUTTONS] = mMouseButtonDown;
        sendEvent(EVENT_MOUSEMOVE, eventData);
    }
}

void Input::setToggleFullscreen(bool enable)
{
    mToggleFullscreen = enable;
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

bool Input::getMouseButtonDown(int button) const
{
    return (mMouseButtonDown & button) != 0;
}

bool Input::getMouseButtonPress(int button) const
{
    return (mMouseButtonPress & button) != 0;
}

int Input::getMouseMoveX() const
{
    return mMouseMoveX;
}

int Input::getMouseMoveY() const
{
    return mMouseMoveY;
}

void Input::handleWindowMessage(StringHash eventType, VariantMap& eventData)
{
    using namespace WindowMessage;
    
    if ((!mRenderer) || (eventData[P_WINDOW].getInt() != mRenderer->getWindowHandle()))
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
        break;
        
    case WM_KEYUP:
        keyChange(wParam, false);
        eventData[P_HANDLED] = true;
        break;
        
    case WM_SYSKEYUP:
        keyChange(wParam, false);
        break;

    case WM_CHAR:
        {
            using namespace Char;
            
            VariantMap keyEventData;
            keyEventData[P_CHAR] = wParam;
            sendEvent(EVENT_CHAR, keyEventData);
        }
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
    
    if (mRenderer->getFullscreen())
        SetCursorPos(mRenderer->getWidth() / 2, mRenderer->getHeight() / 2);
    else
    {
        HWND window = (HWND)mRenderer->getWindowHandle();
        
        POINT point;
        point.x = mRenderer->getWidth() / 2;
        point.y = mRenderer->getHeight() / 2;
        ClientToScreen(window, &point);
        SetCursorPos(point.x, point.y);
        
        RECT clipRect;
        GetWindowRect(window, &clipRect);
        ClipCursor(&clipRect);
    }
    
    mActive = true;
    mActivated = false;
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
        ShowCursor(TRUE);
    
    ClipCursor(0);
    
    mActive = false;
    mActivated = false;
}

void Input::clearState()
{
    mMouseMoveX = 0;
    mMouseMoveY = 0;
    mMouseButtonDown = 0;
    mMouseButtonPress = 0;
    
    memset(&mKeyDown, 0, sizeof(mKeyDown));
    memset(&mKeyPress, 0, sizeof(mKeyPress));
}

void Input::mouseButtonChange(int button, bool newState)
{
    if (newState)
    {
        mMouseButtonDown |= button;
        if (!(mMouseButtonDown & button))
            mMouseButtonPress |= button;
    }
    else
    {
        mMouseButtonDown &= ~button;
    }
    
    using namespace MouseButtonDown;
    
    VariantMap eventData;
    eventData[P_BUTTON] = button;
    eventData[P_BUTTONS] = mMouseButtonDown;
    sendEvent(newState ? EVENT_MOUSEBUTTONDOWN : EVENT_MOUSEBUTTONUP, eventData);
}

void Input::keyChange(int key, bool newState)
{
    if ((key < 0) || (key >= MAX_KEYS))
        return;
    
    if ((newState) && (!mKeyDown[key]))
        mKeyPress[key] = true;
    
    mKeyDown[key] = newState;
    
    using namespace KeyDown;
    
    VariantMap eventData;
    eventData[P_KEY] = key;
    eventData[P_BUTTONS] = mMouseButtonDown;
    sendEvent(newState ? EVENT_KEYDOWN : EVENT_KEYUP, eventData);
}
