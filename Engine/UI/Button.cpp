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
#include "ResourceCache.h"
#include "Texture.h"
#include "UIEvents.h"

#include "DebugNew.h"

Button::Button(const std::string& name) :
    BorderImage(name),
    mInactiveRect(0, 0, 0, 0),
    mHoverRect(0, 0, 0, 0),
    mPressedRect(0, 0, 0, 0),
    mHoverDelay(0.0f),
    mPressedDelay(0.1f),
    mState(BUTTON_INACTIVE),
    mHoveringThisFrame(false)
{
    mClipChildren = true;
    mEnabled = true;
}

Button::~Button()
{
}

XMLElement Button::loadParameters(XMLFile* file, const std::string& elementName, ResourceCache* cache)
{
    XMLElement paramElem = BorderImage::loadParameters(file, elementName, cache);
    
    if (paramElem.hasChildElement("inactiverect"))
        setInactiveRect(paramElem.getChildElement("inactiverect").getIntRect("value"));
    if (paramElem.hasChildElement("hoverrect"))
        setHoverRect(paramElem.getChildElement("hoverrect").getIntRect("value"));
    if (paramElem.hasChildElement("pressedrect"))
        setPressedRect(paramElem.getChildElement("pressedrect").getIntRect("value"));
    if (paramElem.hasChildElement("hoverdelay"))
        setHoverDelay(paramElem.getChildElement("hoverdelay").getFloat("value"));
    if (paramElem.hasChildElement("presseddelay"))
        setPressedDelay(paramElem.getChildElement("presseddelay").getFloat("value"));
    
    return paramElem;
}

void Button::update(float timeStep)
{
    if ((mState != BUTTON_INACTIVE) && (mStateTime <= 0.0f))
    {
        if (!mHoveringThisFrame)
        {
            mState = BUTTON_INACTIVE;
            mStateTime = 0.0f;
        }
        else
        {
            mState = BUTTON_HOVER;
            mStateTime = mHoverDelay;
        }
    }
    else
        mStateTime -= timeStep;
    
    mHoveringThisFrame = false;
}

void Button::getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor)
{
    switch (mState)
    {
    default:
        mImageRect = mInactiveRect;
        break;
        
    case BUTTON_HOVER:
        mImageRect = mHoverRect;
        break;
        
    case BUTTON_PRESSED:
        mImageRect = mPressedRect;
        break;
    }
    
    BorderImage::getBatches(batches, quads, currentScissor);
}

void Button::onHover(const IntVector2& position, const IntVector2& screenPosition)
{
    if (mState != BUTTON_PRESSED)
    {
        mState = BUTTON_HOVER;
        mStateTime = mHoverDelay;
    }
    
    mHoveringThisFrame = true;
}

void Button::onClick(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons)
{
    if (buttons & MOUSEB_LEFT)
    {
        mState = BUTTON_PRESSED;
        mStateTime = mPressedDelay;
        
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

void Button::setHoverRect(const IntRect& rect)
{
    mHoverRect = rect;
}

void Button::setHoverRect(int left, int top, int right, int bottom)
{
    mHoverRect = IntRect(left, top, right, bottom);
}

void Button::setPressedRect(const IntRect& rect)
{
    mPressedRect = rect;
}

void Button::setPressedRect(int left, int top, int right, int bottom)
{
    mPressedRect = IntRect(left, top, right, bottom);
}

void Button::setHoverDelay(float delay)
{
    mHoverDelay = delay;
}

void Button::setPressedDelay(float delay)
{
    mPressedDelay = delay;
}

void Button::setLabel(UIElement* label)
{
    removeChild(mLabel);
    mLabel = label;
    if (mLabel)
    {
        addChild(mLabel);
        // Center the label element on the button forcibly
        mLabel->setAlignment(HA_CENTER, VA_CENTER);
    }
}

