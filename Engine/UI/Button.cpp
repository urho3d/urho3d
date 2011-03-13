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
    mPressedOffset(IntVector2::sZero),
    mLabelOffset(IntVector2::sZero),
    mRepeatDelay(1.0f),
    mRepeatRate(0.0f),
    mRepeatTimer(0.0f),
    mPressed(false)
{
    mEnabled = true;
}

Button::~Button()
{
}

void Button::setStyle(const XMLElement& element, ResourceCache* cache)
{
    BorderImage::setStyle(element, cache);
    
    if (element.hasChildElement("pressedoffset"))
        setPressedOffset(element.getChildElement("pressedoffset").getIntVector2("value"));
    if (element.hasChildElement("labeloffset"))
        setLabelOffset(element.getChildElement("labeloffset").getIntVector2("value"));
    if (element.hasChildElement("repeat"))
    {
        XMLElement repeatElem = element.getChildElement("repeat");
        setRepeat(repeatElem.getFloat("delay"), repeatElem.getFloat("rate"));
    }
}

void Button::update(float timeStep)
{
    if ((!mHovering) && (mPressed == true))
        setPressed(false);
    
    // Send repeat events if pressed
    if ((mPressed) && (mRepeatRate > 0.0f))
    {
        mRepeatTimer -= timeStep;
        if (mRepeatTimer <= 0.0f)
        {
            mRepeatTimer += 1.0f / mRepeatRate;
            
            using namespace Pressed;
            
            VariantMap eventData;
            eventData[P_ELEMENT] = (void*)this;
            sendEvent(EVENT_PRESSED, eventData);
        }
    }
}

void Button::getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor)
{
    IntVector2 offset(IntVector2::sZero);
    if (mHovering)
        offset += mHoverOffset;
    if ((mPressed) || (mSelected))
        offset += mPressedOffset;
    
    BorderImage::getBatches(batches, quads, currentScissor, offset);
}

void Button::onHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    bool oldPressed = mPressed;
    setPressed((buttons & MOUSEB_LEFT) != 0);
    mHovering = true;
    
    if ((oldPressed) && (!mPressed))
    {
        using namespace Released;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        sendEvent(EVENT_RELEASED, eventData);
    }
}

void Button::onClick(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    if (buttons & MOUSEB_LEFT)
    {
        setPressed(true);
        mRepeatTimer = mRepeatDelay;
        mHovering = true;
        
        using namespace Pressed;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        sendEvent(EVENT_PRESSED, eventData);
    }
}

void Button::setPressedOffset(const IntVector2& offset)
{
    mPressedOffset = offset;
}

void Button::setPressedOffset(int x, int y)
{
    mPressedOffset = IntVector2(x, y);
}


void Button::setLabelOffset(const IntVector2& offset)
{
    mLabelOffset = offset;
}

void Button::setLabelOffset(int x, int y)
{
    mLabelOffset = IntVector2(x, y);
}

void Button::setRepeat(float delay, float rate)
{
    mRepeatDelay = max(delay, 0.0f);
    mRepeatRate = max(rate, 0.0f);
}

void Button::setPressed(bool enable)
{
    mPressed = enable;
    setChildOffset(mPressed ? mLabelOffset : IntVector2::sZero);
}
