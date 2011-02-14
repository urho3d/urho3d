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

ScrollBar::ScrollBar(const std::string& name) :
    UIElement(name),
    mScrollStep(0.1f)
{
    mEnabled = true;
    mBackButton = new Button();
    mForwardButton = new Button();
    mSlider = new Slider();
    
    addChild(mBackButton);
    addChild(mForwardButton);
    addChild(mSlider);
    
    subscribeToEvent(mBackButton, EVENT_PRESSED, EVENT_HANDLER(ScrollBar, handleBackButtonPressed));
    subscribeToEvent(mForwardButton, EVENT_PRESSED, EVENT_HANDLER(ScrollBar, handleForwardButtonPressed));
    subscribeToEvent(mSlider, EVENT_SLIDERCHANGED, EVENT_HANDLER(ScrollBar, handleSliderChanged));
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::setStyle(const XMLElement& element, ResourceCache* cache)
{
    XMLElement backButtonElem = element.getChildElement("backbutton");
    if (backButtonElem)
    {
        mBackButton->setStyle(backButtonElem, cache);
        setButtonStyle(0, backButtonElem);
    }
    XMLElement forwardButtonElem = element.getChildElement("forwardbutton");
    if (forwardButtonElem)
    {
        mForwardButton->setStyle(forwardButtonElem, cache);
        setButtonStyle(1, forwardButtonElem);
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
    
    // Setup size last so that orientation and child elements are first setup correctly
    UIElement::setStyle(element, cache);
}

void ScrollBar::onResize()
{
    if (mSlider->getOrientation() == O_HORIZONTAL)
    {
        int height = getHeight();
        
        mBackButton->setAlignment(HA_LEFT, VA_TOP);
        mBackButton->setPosition(0, 0);
        mBackButton->setHeight(height);
        
        mSlider->setAlignment(HA_LEFT, VA_TOP);
        mSlider->setPosition(mBackButton->getWidth(), 0);
        mSlider->setSize(getWidth() - mBackButton->getWidth() - mForwardButton->getWidth(), height);
        
        mForwardButton->setAlignment(HA_LEFT, VA_TOP);
        mForwardButton->setPosition(mBackButton->getWidth() + mSlider->getWidth(), 0);
        mForwardButton->setHeight(height);
    }
    else
    {
        int width = getWidth();
        
        mBackButton->setAlignment(HA_LEFT, VA_TOP);
        mBackButton->setPosition(0, 0);
        mBackButton->setWidth(width);
        
        mSlider->setAlignment(HA_LEFT, VA_TOP);
        mSlider->setPosition(0, mBackButton->getHeight());
        mSlider->setSize(width, getHeight() - mBackButton->getHeight() - mForwardButton->getHeight());
        
        mForwardButton->setAlignment(HA_LEFT, VA_TOP);
        mForwardButton->setPosition(0, mBackButton->getHeight() + mSlider->getHeight());
        mForwardButton->setWidth(width);
    }
}

void ScrollBar::setOrientation(Orientation orientation)
{
    mSlider->setOrientation(orientation);
    
    unsigned orient = (unsigned)orientation;
    mBackButton->setInactiveRect(mInactiveRects[orient][0]);
    mBackButton->setPressedRect(mPressedRects[orient][0]);
    mForwardButton->setInactiveRect(mInactiveRects[orient][1]);
    mForwardButton->setPressedRect(mPressedRects[orient][1]);
    
    onResize();
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

void ScrollBar::setButtonStyle(unsigned index, const XMLElement& buttonElem)
{
    Button* button = index ? mForwardButton : mBackButton;
    unsigned orient = (unsigned)getType();
    
    XMLElement inactiveRectElem = buttonElem.getChildElement("inactiverect");
    if (inactiveRectElem.hasAttribute("horizontal"))
        mInactiveRects[0][index] = inactiveRectElem.getIntRect("horizontal");
    if (inactiveRectElem.hasAttribute("h"))
        mInactiveRects[0][index] = inactiveRectElem.getIntRect("h");
    if (inactiveRectElem.hasAttribute("vertical"))
        mInactiveRects[1][index] = inactiveRectElem.getIntRect("vertical");
    if (inactiveRectElem.hasAttribute("v"))
        mInactiveRects[1][index] = inactiveRectElem.getIntRect("v");
    
    XMLElement pressedRectElem = buttonElem.getChildElement("pressedrect");
    if (pressedRectElem.hasAttribute("horizontal"))
        mPressedRects[0][index] = pressedRectElem.getIntRect("horizontal");
    if (pressedRectElem.hasAttribute("h"))
        mPressedRects[0][index] = pressedRectElem.getIntRect("h");
    if (inactiveRectElem.hasAttribute("vertical"))
        mPressedRects[1][index] = pressedRectElem.getIntRect("vertical");
    if (inactiveRectElem.hasAttribute("v"))
        mPressedRects[1][index] = pressedRectElem.getIntRect("v");
    
    button->setInactiveRect(mInactiveRects[orient][index]);
    button->setPressedRect(mPressedRects[orient][index]);
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
