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

#include "Precompiled.h"
#include "InputEvents.h"
#include "Window.h"

#include "DebugNew.h"

static const int DEFAULT_RESIZE_BORDER = 4;

Window::Window(const std::string& name) :
    BorderImage(name),
    mMovable(false),
    mResizable(false),
    mResizeBorder(DEFAULT_RESIZE_BORDER, DEFAULT_RESIZE_BORDER, DEFAULT_RESIZE_BORDER, DEFAULT_RESIZE_BORDER),
    mDragMode(DRAG_NONE)
{
    mBringToFront = true;
    mClipChildren = true;
    mEnabled = true;
}

Window::~Window()
{
}

void Window::setStyle(const XMLElement& element, ResourceCache* cache)
{
    BorderImage::setStyle(element, cache);
    
    if (element.hasChildElement("resizeborder"))
        setResizeBorder(element.getChildElement("resizeborder").getIntRect("value"));
    if (element.hasChildElement("movable"))
        setMovable(element.getChildElement("movable").getBool("enable"));
    if (element.hasChildElement("resizable"))
        setResizable(element.getChildElement("resizable").getBool("enable"));
}

void Window::onDragStart(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers)
{
    if ((buttons != MOUSEB_LEFT) || (!checkAlignment()))
    {
        mDragMode = DRAG_NONE;
        return;
    }
    
    mDragStartPosition = screenPosition;
    mOriginalPosition = getPosition();
    mOriginalSize = getSize();
    
    // Identify drag type
    // Top row
    if (position.mY < mResizeBorder.mTop)
    {
        if (mMovable)
            mDragMode = DRAG_MOVE;
        if (mResizable)
        {
            mDragMode = DRAG_RESIZE_TOP;
            if (position.mX < mResizeBorder.mLeft)
                mDragMode = DRAG_RESIZE_TOPLEFT;
            if (position.mX >= mOriginalSize.mX - mResizeBorder.mRight)
                mDragMode = DRAG_RESIZE_TOPRIGHT;
        }
    }
    // Bottom row
    else if (position.mY >= mOriginalSize.mY - mResizeBorder.mBottom)
    {
        if (mMovable)
            mDragMode = DRAG_MOVE;
        if (mResizable)
        {
            mDragMode = DRAG_RESIZE_BOTTOM;
            if (position.mX < mResizeBorder.mLeft)
                mDragMode = DRAG_RESIZE_BOTTOMLEFT;
            if (position.mX >= mOriginalSize.mX - mResizeBorder.mRight)
                mDragMode = DRAG_RESIZE_BOTTOMRIGHT;
        }
    }
    // Middle
    else
    {
        if (mMovable)
            mDragMode = DRAG_MOVE;
        if (mResizable)
        {
            if (position.mX < mResizeBorder.mLeft)
                mDragMode = DRAG_RESIZE_LEFT;
            if (position.mX >= mOriginalSize.mX - mResizeBorder.mRight)
                mDragMode = DRAG_RESIZE_RIGHT;
        }
    }
}

void Window::onDragMove(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers)
{
    if (mDragMode == DRAG_NONE)
        return;
    
    IntVector2 delta = screenPosition - mDragStartPosition;
    
    switch (mDragMode)
    {
    case DRAG_MOVE:
        setPosition(mOriginalPosition + delta);
        break;
        
    case DRAG_RESIZE_TOPLEFT:
        setPosition(mOriginalPosition + delta);
        setSize(mOriginalSize - delta);
        break;
        
    case DRAG_RESIZE_TOP:
        setPosition(mOriginalPosition.mX, mOriginalPosition.mY + delta.mY);
        setSize(mOriginalSize.mX, mOriginalSize.mY - delta.mY);
        break;
        
    case DRAG_RESIZE_TOPRIGHT:
        setPosition(mOriginalPosition.mX, mOriginalPosition.mY + delta.mY);
        setSize(mOriginalSize.mX + delta.mX, mOriginalSize.mY - delta.mY);
        break;
        
    case DRAG_RESIZE_RIGHT:
        setSize(mOriginalSize.mX + delta.mX, mOriginalSize.mY);
        break;
        
    case DRAG_RESIZE_BOTTOMRIGHT:
        setSize(mOriginalSize + delta);
        break;
        
    case DRAG_RESIZE_BOTTOM:
        setSize(mOriginalSize.mX, mOriginalSize.mY + delta.mY);
        break;
        
    case DRAG_RESIZE_BOTTOMLEFT:
        setPosition(mOriginalPosition.mX + delta.mX, mOriginalPosition.mY);
        setSize(mOriginalSize.mX - delta.mX, mOriginalSize.mY + delta.mY);
        break;
        
    case DRAG_RESIZE_LEFT:
        setPosition(mOriginalPosition.mX + delta.mX, mOriginalPosition.mY);
        setSize(mOriginalSize.mX - delta.mX, mOriginalSize.mY);
        break;
    }
    
    validatePosition();
}

void Window::onDragEnd(const IntVector2& position, const IntVector2& screenPosition)
{
    mDragMode = DRAG_NONE;
}

void Window::setMovable(bool enable)
{
    mMovable = enable;
}

void Window::setResizable(bool enable)
{
    mResizable = enable;
}

void Window::setResizeBorder(const IntRect& rect)
{
    mResizeBorder.mLeft = max(rect.mLeft, 0);
    mResizeBorder.mTop = max(rect.mTop, 0);
    mResizeBorder.mRight = max(rect.mRight, 0);
    mResizeBorder.mBottom = max(rect.mBottom, 0);
}

void Window::setResizeBorder(int left, int top, int right, int bottom)
{
    setResizeBorder(IntRect(left, top, right, bottom));
}

void Window::validatePosition()
{
    // Check that window does not go more than halfway outside its parent in either dimension
    if (!mParent)
        return;
    
    const IntVector2& parentSize = mParent->getSize();
    IntVector2 position = getPosition();
    IntVector2 halfSize = getSize() / 2;
    
    position.mX = clamp(position.mX, -halfSize.mX, parentSize.mX - halfSize.mX);
    position.mY = clamp(position.mY, -halfSize.mY, parentSize.mY - halfSize.mY);
    
    setPosition(position);
}

bool Window::checkAlignment() const
{
    // Only top left-alignment is supported for move and resize
    if ((getHorizontalAlignment() == HA_LEFT) && (getVerticalAlignment() == VA_TOP))
        return true;
    else
        return false;
}
