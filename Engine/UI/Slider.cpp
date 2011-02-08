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
#include "Log.h"
#include "Slider.h"
#include "UIEvents.h"

#include "DebugNew.h"

Slider::Slider(const std::string& name) :
    BorderImage(name),
    mOrientation(O_HORIZONTAL),
    mRange(1.0f),
    mValue(0.0f),
    mDragSlider(false)
{
    mEnabled = true;
    mSlider = new BorderImage();
    addChild(mSlider);
    
    updateSlider();
}

Slider::~Slider()
{
}

void Slider::setStyle(const XMLElement& element, ResourceCache* cache)
{
    BorderImage::setStyle(element, cache);
    
    if (element.hasChildElement("orientation"))
    {
        std::string orientation = element.getChildElement("orientation").getStringLower("value");
        if ((orientation == "horizontal") || (orientation == "h"))
            setOrientation(O_HORIZONTAL);
        if ((orientation == "vertical") || (orientation == "v"))
            setOrientation(O_VERTICAL);
    }
    
    XMLElement sliderElem = element.getChildElement("slider");
    if (sliderElem)
    {
        mSlider->setStyle(sliderElem, cache);
        setRange(sliderElem.getFloat("range"));
        setValue(sliderElem.getFloat("value"));
    }
}

void Slider::update(float timeStep)
{
    if (mDragSlider)
        mHovering = true;
    
    // Copy hover and selection effect to the slider button
    mSlider->setHovering(mHovering);
    mSlider->setSelected(mSelected);
}

void Slider::onHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers)
{
    // Show hover effect if inside the slider button
    mHovering = mSlider->isInside(screenPosition, true);
}

void Slider::onDragStart(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers)
{
    mOriginalPosition = position;
    mOriginalSliderPosition = mSlider->getPosition();
    mDragSlider = mSlider->isInside(screenPosition, true);
}

void Slider::onDragMove(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers)
{
    if (!mDragSlider)
        return;
    
    float newValue = mValue;
    IntVector2 delta = position - mOriginalPosition;
    
    if (mOrientation == O_HORIZONTAL)
    {
        int newX = clamp(mOriginalSliderPosition.mX + delta.mX, 0, getWidth() - mSlider->getWidth());
        mSlider->setPosition(newX, mOriginalSliderPosition.mY);
        newValue = clamp((float)newX * (mRange + 1.0f) / (float)getWidth(), 0.0f, mRange);
    }
    else
    {
        int newY = clamp(mOriginalSliderPosition.mY + delta.mY, 0, getHeight() - mSlider->getHeight());
        mSlider->setPosition(mOriginalSliderPosition.mX, newY);
        newValue = clamp((float)newY * (mRange + 1.0f) / (float)getHeight(), 0.0f, mRange);
    }
    
    if (newValue != mValue)
    {
        mValue = newValue;
        
        using namespace SliderChanged;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        eventData[P_VALUE] = mValue;
        sendEvent(EVENT_SLIDERCHANGED, eventData);
    }
}

void Slider::onDragEnd(const IntVector2& position, const IntVector2& screenPosition)
{
    mDragSlider = false;
}

void Slider::setOrientation(UIElementOrientation orientation)
{
    mOrientation = orientation;
    updateSlider();
}

void Slider::setRange(float range)
{
    range = max(range, 0.0f);
    if (range != mRange)
    {
        mRange = range;
        updateSlider();
    }
}

void Slider::setValue(float value)
{
    value = clamp(value, 0.0f, mRange);
    if (value != mValue)
    {
        mValue = value;
        updateSlider();
    }
}

void Slider::updateSlider()
{
    if (mOrientation == O_HORIZONTAL)
    {
        float width = (float)getWidth();
        if (width < M_EPSILON)
            return;
        float sliderLength = width / (mRange + 1.0f);
        float sliderPos = width * mValue / (mRange + 1.0f);
        mSlider->setSize((int)sliderLength, getHeight());
        mSlider->setPosition(clamp((int)(sliderPos + 0.5f), 0, getWidth() - mSlider->getWidth()), 0);
    }
    else
    {
        float height = (float)getHeight();
        if (height < M_EPSILON)
            return;
        float sliderLength = height / (mRange + 1.0f);
        float sliderPos = height * mValue / (mRange + 1.0f);
        mSlider->setSize(getWidth(), (int)sliderLength);
        mSlider->setPosition(0, clamp((int)(sliderPos + 0.5f), 0, getHeight() - mSlider->getHeight()));
    }
}
