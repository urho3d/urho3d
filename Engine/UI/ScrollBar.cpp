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
#include "ScrollBar.h"
#include "Slider.h"
#include "UIEvents.h"

static const float DEFAULT_REPEAT_DELAY = 0.4f;
static const float DEFAULT_REPEAT_RATE = 20.0f;

ScrollBar::ScrollBar(const std::string& name) :
    UIElement(name),
    mScrollStep(0.1f),
    mLeftRect(IntRect::sZero),
    mRightRect(IntRect::sZero),
    mUpRect(IntRect::sZero),
    mDownRect(IntRect::sZero)
{
    mEnabled = true;
    
    mBackButton = new Button();
    mBackButton->setRepeat(DEFAULT_REPEAT_DELAY, DEFAULT_REPEAT_RATE);
    mForwardButton = new Button();
    mForwardButton->setRepeat(DEFAULT_REPEAT_DELAY, DEFAULT_REPEAT_RATE);
    mSlider = new Slider();
    
    addChild(mBackButton);
    addChild(mSlider);
    addChild(mForwardButton);
    
    subscribeToEvent(mBackButton, EVENT_PRESSED, EVENT_HANDLER(ScrollBar, handleBackButtonPressed));
    subscribeToEvent(mForwardButton, EVENT_PRESSED, EVENT_HANDLER(ScrollBar, handleForwardButtonPressed));
    subscribeToEvent(mSlider, EVENT_SLIDERCHANGED, EVENT_HANDLER(ScrollBar, handleSliderChanged));
    
    // Set default orientation/layout
    setOrientation(O_HORIZONTAL);
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::setStyle(const XMLElement& element, ResourceCache* cache)
{
    UIElement::setStyle(element, cache);
    
    XMLElement backButtonElem = element.getChildElement("backbutton");
    if (backButtonElem)
    {
        XMLElement imageElem = backButtonElem.getChildElement("imagerect");
        if (imageElem.hasAttribute("horizontal"))
            mLeftRect = imageElem.getIntRect("horizontal");
        if (imageElem.hasAttribute("vertical"))
            mUpRect = imageElem.getIntRect("vertical");
        if (imageElem.hasAttribute("h"))
            mLeftRect = imageElem.getIntRect("h");
        if (imageElem.hasAttribute("v"))
            mUpRect = imageElem.getIntRect("v");
        mBackButton->setStyle(backButtonElem, cache);
    }
    XMLElement forwardButtonElem = element.getChildElement("forwardbutton");
    if (forwardButtonElem)
    {
        XMLElement imageElem = forwardButtonElem.getChildElement("imagerect");
        if (imageElem.hasAttribute("horizontal"))
            mRightRect = imageElem.getIntRect("horizontal");
        if (imageElem.hasAttribute("vertical"))
            mDownRect = imageElem.getIntRect("vertical");
        if (imageElem.hasAttribute("h"))
            mRightRect = imageElem.getIntRect("h");
        if (imageElem.hasAttribute("v"))
            mDownRect = imageElem.getIntRect("v");
        mForwardButton->setStyle(forwardButtonElem, cache);
    }
    XMLElement sliderElem = element.getChildElement("slider");
    if (sliderElem)
        mSlider->setStyle(sliderElem, cache);
    
    if (element.hasChildElement("range"))
    {
        XMLElement rangeElem = element.getChildElement("range");
        setRange(rangeElem.getFloat("max"));
        setValue(rangeElem.getFloat("value"));
    }
    if (element.hasChildElement("orientation"))
    {
        std::string orientation = element.getChildElement("orientation").getStringLower("value");
        if ((orientation == "horizontal") || (orientation == "h"))
            setOrientation(O_HORIZONTAL);
        if ((orientation == "vertical") || (orientation == "v"))
            setOrientation(O_VERTICAL);
    }
}

void ScrollBar::onResize()
{
    // Disable layout operations while setting the button sizes is incomplete
    mUpdateLayoutNestingLevel++;
    
    if (mSlider->getOrientation() == O_HORIZONTAL)
    {
        int height = getHeight();
        mBackButton->setFixedSize(height, height);
        mForwardButton->setFixedSize(height, height);
    }
    else
    {
        int width = getWidth();
        mBackButton->setFixedSize(width, width);
        mForwardButton->setFixedSize(width, width);
    }
    
    mUpdateLayoutNestingLevel--;
}

void ScrollBar::setOrientation(Orientation orientation)
{
    mSlider->setOrientation(orientation);
    
    if (orientation == O_HORIZONTAL)
    {
        mBackButton->setImageRect(mLeftRect);
        mForwardButton->setImageRect(mRightRect);
    }
    else
    {
        mBackButton->setImageRect(mUpRect);
        mForwardButton->setImageRect(mDownRect);
    }
    
    onResize();
    setLayout(orientation, LM_RESIZECHILDREN, LM_RESIZECHILDREN);
}

void ScrollBar::setRange(float range)
{
    mSlider->setRange(range);
}

void ScrollBar::setValue(float value)
{
    mSlider->setValue(value);
}

void ScrollBar::setScrollStep(float step)
{
    mScrollStep = max(step, 0.0f);
}

Orientation ScrollBar::getOrientation() const
{
    return mSlider->getOrientation();
}

float ScrollBar::getRange() const
{
    return mSlider->getRange();
}

float ScrollBar::getValue() const
{
    return mSlider->getValue();
}

void ScrollBar::handleBackButtonPressed(StringHash eventType, VariantMap& eventData)
{
    mSlider->setValue(mSlider->getValue() - mScrollStep);
}

void ScrollBar::handleForwardButtonPressed(StringHash eventType, VariantMap& eventData)
{
    mSlider->setValue(mSlider->getValue() + mScrollStep);
}

void ScrollBar::handleSliderChanged(StringHash eventType, VariantMap& eventData)
{
    // Send the event forward
    VariantMap newEventData;
    
    newEventData[ScrollBarChanged::P_ELEMENT] = (void*)this;
    newEventData[ScrollBarChanged::P_VALUE] = mSlider->getValue();
    sendEvent(EVENT_SCROLLBARCHANGED, newEventData);
}
