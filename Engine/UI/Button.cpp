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
#include "Button.h"
#include "InputEvents.h"
#include "UIEvents.h"

#include "DebugNew.h"

Button::Button(const std::string& name) :
    BorderImage(name),
    mInactiveRect(IntRect::sZero),
    mPressedRect(IntRect::sZero),
    mLabelOffset(IntVector2::sZero),
    mPressed(false)
{
    mClipChildren = true;
    mEnabled = true;
}

Button::~Button()
{
}

void Button::setStyle(const XMLElement& element, ResourceCache* cache)
{
    BorderImage::setStyle(element, cache);
    
    if (element.hasChildElement("inactiverect"))
        setInactiveRect(element.getChildElement("inactiverect").getIntRect("value"));
    if (element.hasChildElement("pressedrect"))
        setPressedRect(element.getChildElement("pressedrect").getIntRect("value"));
    if (element.hasChildElement("labeloffset"))
        setLabelOffset(element.getChildElement("labeloffset").getIntVector2("value"));
}

void Button::update(float timeStep)
{
    if (!mHovering)
        setPressed(false);
}

void Button::getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor)
{
    if (mPressed)
        mImageRect = mPressedRect;
    else
        mImageRect = mInactiveRect;
    
    BorderImage::getBatches(batches, quads, currentScissor);
}

void Button::onHover(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons)
{
    setPressed((buttons & MOUSEB_LEFT) != 0);
    mHovering = true;
}

void Button::onClick(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons)
{
    if (buttons & MOUSEB_LEFT)
    {
        setPressed(true);
        mHovering = true;
        
        using namespace Pressed;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        sendEvent(EVENT_PRESSED, eventData);
    }
}

void Button::setInactiveRect(const IntRect& rect)
{
    mInactiveRect = rect;
}

void Button::setInactiveRect(int left, int top, int right, int bottom)
{
    mInactiveRect = IntRect(left, top, right, bottom);
}

void Button::setPressedRect(const IntRect& rect)
{
    mPressedRect = rect;
}

void Button::setPressedRect(int left, int top, int right, int bottom)
{
    mPressedRect = IntRect(left, top, right, bottom);
}

void Button::setLabelOffset(const IntVector2& offset)
{
    mLabelOffset = offset;
}

void Button::setLabelOffset(int x, int y)
{
    mLabelOffset = IntVector2(x, y);
}

void Button::setPressed(bool enable)
{
    mPressed = enable;
    setChildOffset(mPressed ? mLabelOffset : IntVector2::sZero);
}
