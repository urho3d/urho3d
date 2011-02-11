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
#include "ScrollView.h"
#include "Slider.h"
#include "UIEvents.h"

#include "DebugNew.h"

ScrollView::ScrollView(const std::string& name) :
    BorderImage(name),
    mViewPosition(IntVector2::sZero),
    mViewSize(IntVector2::sZero),
    mScrollStep(0.25f),
    mPageStep(1.0f)
{
    mClipChildren = true;
    mEnabled = true;
    mFocusable = true;
}

ScrollView::~ScrollView()
{
}

void ScrollView::setStyle(const XMLElement& element, ResourceCache* cache)
{
    BorderImage::setStyle(element, cache);
    
    if (element.hasChildElement("viewposition"))
        setViewPosition(element.getChildElement("viewposition").getIntVector2("value"));
    if (element.hasChildElement("viewsize"))
        setViewSize(element.getChildElement("viewsize").getIntVector2("value"));
    if (element.hasChildElement("scrollstep"))
        setScrollStep(element.getChildElement("scrollstep").getFloat("value"));
    if (element.hasChildElement("pagestep"))
        setScrollStep(element.getChildElement("pagestep").getFloat("value"));
    
    UIElement* root = getRootElement();
    if (root)
    {
        if (element.hasChildElement("horizontalslider"))
            setHorizontalSlider(dynamic_cast<Slider*>(root->getChild(element.getChildElement("horizontalslider").getString("name"), true)));
        if (element.hasChildElement("verticalslider"))
            setVerticalSlider(dynamic_cast<Slider*>(root->getChild(element.getChildElement("verticalslider").getString("name"), true)));
    }
}

void ScrollView::update(float timeStep)
{
    updateViewFromSliders();
}

void ScrollView::onKey(int key, int buttons, int qualifiers)
{
    switch (key)
    {
    case KEY_LEFT:
        if (mHorizontalSlider)
        {
            if (qualifiers & QUAL_CTRL)
                mHorizontalSlider->setValue(0.0f);
            else
                mHorizontalSlider->setValue(mHorizontalSlider->getValue() - mScrollStep);
        }
        break;
        
    case KEY_RIGHT:
        if (mHorizontalSlider)
        {
            if (qualifiers & QUAL_CTRL)
                mHorizontalSlider->setValue(mHorizontalSlider->getRange());
            else
                mHorizontalSlider->setValue(mHorizontalSlider->getValue() + mScrollStep);
        }
        break;
        
    case KEY_UP:
        if (mVerticalSlider)
        {
            if (qualifiers & QUAL_CTRL)
                mVerticalSlider->setValue(0.0f);
            else
                mVerticalSlider->setValue(mVerticalSlider->getValue() - mScrollStep);
        }
        break;
        
    case KEY_DOWN:
        if (mVerticalSlider)
        {
            if (qualifiers & QUAL_CTRL)
                mVerticalSlider->setValue(mVerticalSlider->getRange());
            else
                mVerticalSlider->setValue(mVerticalSlider->getValue() + mScrollStep);
        }
        break;
        
    case KEY_PAGEUP:
        if (mVerticalSlider)
            mVerticalSlider->setValue(mVerticalSlider->getValue() - mPageStep);
        break;
        
    case KEY_PAGEDOWN:
        if (mVerticalSlider)
            mVerticalSlider->setValue(mVerticalSlider->getValue() + mPageStep);
        break;
    
    case KEY_HOME:
        if (mVerticalSlider)
            mVerticalSlider->setValue(0.0f);
        break;
    
    case KEY_END:
        if (mVerticalSlider)
            mVerticalSlider->setValue(mVerticalSlider->getRange());
        break;
    }
}

void ScrollView::onFocus()
{
    // Set selected state (constant hover) on the sliders to show they are now under key control
    if (mHorizontalSlider)
        mHorizontalSlider->setSelected(true);
    if (mVerticalSlider)
        mVerticalSlider->setSelected(true);
}

void ScrollView::onDefocus()
{
    if (mHorizontalSlider)
        mHorizontalSlider->setSelected(false);
    if (mVerticalSlider)
        mVerticalSlider->setSelected(false);
}

void ScrollView::onResize()
{
    // This will grow the view size if it is smaller than current size
    setViewSize(mViewSize);
}

void ScrollView::setViewPosition(const IntVector2& position)
{
    updateView(position);
    updateSliders();
}

void ScrollView::setViewPosition(int x, int y)
{
    setViewPosition(IntVector2(x, y));
}

void ScrollView::setViewSize(const IntVector2& size)
{
    mViewSize.mX = max(size.mX, getWidth());
    mViewSize.mY = max(size.mY, getHeight());
    updateView(mViewPosition);
    updateSliders();
}

void ScrollView::setViewSize(int x, int y)
{
    setViewSize(IntVector2(x, y));
}

void ScrollView::setHorizontalSlider(Slider* slider)
{
    mHorizontalSlider = slider;
    updateSliders();
}

void ScrollView::setVerticalSlider(Slider* slider)
{
    mVerticalSlider = slider;
    updateSliders();
}

void ScrollView::setScrollStep(float step)
{
    mScrollStep = max(step, 0.0f);
}

void ScrollView::setPageStep(float step)
{
    mPageStep = max(step, 0.0f);
}

void ScrollView::updateViewFromSliders()
{
    if ((!mHorizontalSlider) && (!mVerticalSlider))
        return;
    
    IntVector2 oldPosition = mViewPosition;
    IntVector2 newPosition = mViewPosition;
    const IntVector2& size = getSize();
    
    if (mHorizontalSlider)
        newPosition.mX = (int)(mHorizontalSlider->getValue() * (float)size.mX);
    if (mVerticalSlider)
        newPosition.mY = (int)(mVerticalSlider->getValue() * (float)size.mY);
    
    updateView(newPosition);
    
    if (mViewPosition != oldPosition)
    {
        using namespace ViewChanged;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        eventData[P_X] = mViewPosition.mX;
        eventData[P_Y] = mViewPosition.mY;
        sendEvent(EVENT_VIEWCHANGED, eventData);
    }
}

void ScrollView::updateSliders()
{
    const IntVector2& size = getSize();
    
    if ((mHorizontalSlider) && (size.mX > 0) && (mViewSize.mX > 0))
    {
        mHorizontalSlider->setRange((float)mViewSize.mX / (float)size.mX - 1.0f);
        mHorizontalSlider->setValue((float)mViewPosition.mX / (float)size.mX);
    }
    if ((mVerticalSlider) && (size.mY > 0) && (mViewSize.mY > 0))
    {
        mVerticalSlider->setRange((float)mViewSize.mY / (float)size.mY - 1.0f);
        mVerticalSlider->setValue((float)mViewPosition.mY / (float)size.mY);
    }
}

void ScrollView::updateView(const IntVector2& position)
{
    mViewPosition.mX = clamp(position.mX, 0, mViewSize.mX - getWidth());
    mViewPosition.mY = clamp(position.mY, 0, mViewSize.mY - getHeight());
    setChildOffset(-mViewPosition);
}
