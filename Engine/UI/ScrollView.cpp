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
#include "ScrollBar.h"
#include "ScrollView.h"
#include "UIEvents.h"

#include "DebugNew.h"

ScrollView::ScrollView(const std::string& name) :
    BorderImage(name),
    mViewPosition(IntVector2::sZero),
    mViewSize(IntVector2::sZero),
    mScrollStep(0.1f),
    mPageStep(1.0f)
{
    mClipChildren = true;
    mEnabled = true;
    mFocusMode = FM_FOCUSABLE_DEFOCUSABLE;
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
        if (element.hasChildElement("horizontalscrollbar"))
            setHorizontalScrollBar(dynamic_cast<ScrollBar*>(root->getChild(element.getChildElement("horizontalscrollbar").getString("name"), true)));
        if (element.hasChildElement("verticalscrollbar"))
            setVerticalScrollBar(dynamic_cast<ScrollBar*>(root->getChild(element.getChildElement("verticalscrollbar").getString("name"), true)));
    }
}

void ScrollView::onKey(int key, int buttons, int qualifiers)
{
    switch (key)
    {
    case KEY_LEFT:
        if (mHorizontalScrollBar)
        {
            if (qualifiers & QUAL_CTRL)
                mHorizontalScrollBar->setValue(0.0f);
            else
                mHorizontalScrollBar->setValue(mHorizontalScrollBar->getValue() - mScrollStep);
        }
        break;
        
    case KEY_RIGHT:
        if (mHorizontalScrollBar)
        {
            if (qualifiers & QUAL_CTRL)
                mHorizontalScrollBar->setValue(mHorizontalScrollBar->getRange());
            else
                mHorizontalScrollBar->setValue(mHorizontalScrollBar->getValue() + mScrollStep);
        }
        break;
        
    case KEY_UP:
        if (mVerticalScrollBar)
        {
            if (qualifiers & QUAL_CTRL)
                mVerticalScrollBar->setValue(0.0f);
            else
                mVerticalScrollBar->setValue(mVerticalScrollBar->getValue() - mScrollStep);
        }
        break;
        
    case KEY_DOWN:
        if (mVerticalScrollBar)
        {
            if (qualifiers & QUAL_CTRL)
                mVerticalScrollBar->setValue(mVerticalScrollBar->getRange());
            else
                mVerticalScrollBar->setValue(mVerticalScrollBar->getValue() + mScrollStep);
        }
        break;
        
    case KEY_PAGEUP:
        if (mVerticalScrollBar)
            mVerticalScrollBar->setValue(mVerticalScrollBar->getValue() - mPageStep);
        break;
        
    case KEY_PAGEDOWN:
        if (mVerticalScrollBar)
            mVerticalScrollBar->setValue(mVerticalScrollBar->getValue() + mPageStep);
        break;
    
    case KEY_HOME:
        if (mVerticalScrollBar)
            mVerticalScrollBar->setValue(0.0f);
        break;
    
    case KEY_END:
        if (mVerticalScrollBar)
            mVerticalScrollBar->setValue(mVerticalScrollBar->getRange());
        break;
    }
}

void ScrollView::onFocus()
{
    // Set selected state (constant hover) on the scroll bars to show they are now under key control
    if (mHorizontalScrollBar)
        mHorizontalScrollBar->setSelected(true);
    if (mVerticalScrollBar)
        mVerticalScrollBar->setSelected(true);
}

void ScrollView::onDefocus()
{
    if (mHorizontalScrollBar)
        mHorizontalScrollBar->setSelected(false);
    if (mVerticalScrollBar)
        mVerticalScrollBar->setSelected(false);
}

void ScrollView::onResize()
{
    // This will grow the view size if it is smaller than current size
    setViewSize(mViewSize);
}

void ScrollView::setViewPosition(const IntVector2& position)
{
    updateView(position);
    updateScrollBars();
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
    updateScrollBars();
}

void ScrollView::setViewSize(int x, int y)
{
    setViewSize(IntVector2(x, y));
}

void ScrollView::setHorizontalScrollBar(ScrollBar* scrollBar)
{
    if (mHorizontalScrollBar)
        unsubscribeFromEvent(mHorizontalScrollBar, EVENT_SCROLLBARCHANGED);
    
    mHorizontalScrollBar = scrollBar;
    if (mHorizontalScrollBar)
        subscribeToEvent(mHorizontalScrollBar, EVENT_SCROLLBARCHANGED, EVENT_HANDLER(ScrollView, handleScrollBarChanged));
    
    updateScrollBars();
}

void ScrollView::setVerticalScrollBar(ScrollBar* scrollBar)
{
    if (mVerticalScrollBar)
        unsubscribeFromEvent(mVerticalScrollBar, EVENT_SCROLLBARCHANGED);
    
    mVerticalScrollBar = scrollBar;
    if (mVerticalScrollBar)
        subscribeToEvent(mVerticalScrollBar, EVENT_SCROLLBARCHANGED, EVENT_HANDLER(ScrollView, handleScrollBarChanged));
    
    updateScrollBars();
}

void ScrollView::setScrollStep(float step)
{
    mScrollStep = max(step, 0.0f);
}

void ScrollView::setPageStep(float step)
{
    mPageStep = max(step, 0.0f);
}

void ScrollView::updateViewFromScrollBars()
{
    if ((!mHorizontalScrollBar) && (!mVerticalScrollBar))
        return;
    
    IntVector2 oldPosition = mViewPosition;
    IntVector2 newPosition = mViewPosition;
    const IntVector2& size = getSize();
    
    if (mHorizontalScrollBar)
        newPosition.mX = (int)(mHorizontalScrollBar->getValue() * (float)size.mX);
    if (mVerticalScrollBar)
        newPosition.mY = (int)(mVerticalScrollBar->getValue() * (float)size.mY);
    
    updateView(newPosition);
}

void ScrollView::updateScrollBars()
{
    mIgnoreEvents = true;
    
    const IntVector2& size = getSize();
    
    if ((mHorizontalScrollBar) && (size.mX > 0) && (mViewSize.mX > 0))
    {
        mHorizontalScrollBar->setRange((float)mViewSize.mX / (float)size.mX - 1.0f);
        mHorizontalScrollBar->setValue((float)mViewPosition.mX / (float)size.mX);
    }
    if ((mVerticalScrollBar) && (size.mY > 0) && (mViewSize.mY > 0))
    {
        mVerticalScrollBar->setRange((float)mViewSize.mY / (float)size.mY - 1.0f);
        mVerticalScrollBar->setValue((float)mViewPosition.mY / (float)size.mY);
    }
    
    mIgnoreEvents = false;
}

void ScrollView::updateView(const IntVector2& position)
{
    IntVector2 oldPosition = mViewPosition;
    
    mViewPosition.mX = clamp(position.mX, 0, mViewSize.mX - getWidth());
    mViewPosition.mY = clamp(position.mY, 0, mViewSize.mY - getHeight());
    setChildOffset(-mViewPosition);
    
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

void ScrollView::handleScrollBarChanged(StringHash eventType, VariantMap& eventData)
{
    if (!mIgnoreEvents)
        updateViewFromScrollBars();
}
