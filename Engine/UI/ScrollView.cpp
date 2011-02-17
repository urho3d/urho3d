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
#include "BorderImage.h"
#include "InputEvents.h"
#include "ScrollBar.h"
#include "ScrollView.h"
#include "UIEvents.h"

#include "DebugNew.h"

ScrollView::ScrollView(const std::string& name) :
    UIElement(name),
    mViewPosition(IntVector2::sZero),
    mViewSize(IntVector2::sZero),
    mPageStep(1.0f)
{
    mClipChildren = true;
    mEnabled = true;
    mFocusMode = FM_FOCUSABLE_DEFOCUSABLE;
    
    mHorizontalScrollBar = new ScrollBar();
    mHorizontalScrollBar->setAlignment(HA_LEFT, VA_BOTTOM);
    mHorizontalScrollBar->setOrientation(O_HORIZONTAL);
    mVerticalScrollBar = new ScrollBar();
    mVerticalScrollBar->setAlignment(HA_RIGHT, VA_TOP);
    mVerticalScrollBar->setOrientation(O_VERTICAL);
    mScrollPanel = new BorderImage();
    mScrollPanel->setEnabled(true);
    mScrollPanel->setClipChildren(true);
    
    addChild(mHorizontalScrollBar);
    addChild(mVerticalScrollBar);
    addChild(mScrollPanel);
    
    subscribeToEvent(mHorizontalScrollBar, EVENT_SCROLLBARCHANGED, EVENT_HANDLER(ScrollView, handleScrollBarChanged));
    subscribeToEvent(mHorizontalScrollBar, EVENT_VISIBLECHANGED, EVENT_HANDLER(ScrollView, handleScrollBarVisibleChanged));
    subscribeToEvent(mVerticalScrollBar, EVENT_SCROLLBARCHANGED, EVENT_HANDLER(ScrollView, handleScrollBarChanged));
    subscribeToEvent(mVerticalScrollBar, EVENT_VISIBLECHANGED, EVENT_HANDLER(ScrollView, handleScrollBarVisibleChanged));
}

ScrollView::~ScrollView()
{
}

void ScrollView::setStyle(const XMLElement& element, ResourceCache* cache)
{
    UIElement::setStyle(element, cache);
    
    if (element.hasChildElement("viewposition"))
        setViewPosition(element.getChildElement("viewposition").getIntVector2("value"));
    if (element.hasChildElement("scrollstep"))
        setScrollStep(element.getChildElement("scrollstep").getFloat("value"));
    if (element.hasChildElement("pagestep"))
        setScrollStep(element.getChildElement("pagestep").getFloat("value"));
    if (element.hasChildElement("normalizescrollstep"))
        setNormalizeScrollStep(element.getChildElement("normalizescrollstep").getBool("enable"));
    
    XMLElement horizElem = element.getChildElement("horizontalscrollbar");
    if (horizElem)
        mHorizontalScrollBar->setStyle(horizElem, cache);
    XMLElement vertElem = element.getChildElement("verticalscrollbar");
    if (vertElem)
        mVerticalScrollBar->setStyle(vertElem, cache);
    XMLElement panelElem = element.getChildElement("scrollpanel");
    if (panelElem)
        mScrollPanel->setStyle(panelElem, cache);
    
    UIElement* root = getRootElement();
    if ((root) && (element.hasChildElement("contentelement")))
        setContentElement(root->getChild(element.getChildElement("contentelement").getString("name"), true));
    
    // Set the scrollbar orientations again and perform size update now that the style is known
    mHorizontalScrollBar->setOrientation(O_HORIZONTAL);
    mVerticalScrollBar->setOrientation(O_VERTICAL);
    onResize();
}

void ScrollView::onWheel(int delta, int buttons, int qualifiers)
{
    if (delta > 0)
        mVerticalScrollBar->stepBack();
    if (delta < 0)
        mHorizontalScrollBar->stepForward();
}

void ScrollView::onKey(int key, int buttons, int qualifiers)
{
    switch (key)
    {
    case KEY_LEFT:
        if (mHorizontalScrollBar->isVisible())
        {
            if (qualifiers & QUAL_CTRL)
                mHorizontalScrollBar->setValue(0.0f);
            else
                mHorizontalScrollBar->stepBack();
        }
        break;
        
    case KEY_RIGHT:
        if (mHorizontalScrollBar->isVisible())
        {
            if (qualifiers & QUAL_CTRL)
                mHorizontalScrollBar->setValue(mHorizontalScrollBar->getRange());
            else
                mHorizontalScrollBar->stepForward();
        }
        break;
        
    case KEY_UP:
        if (mVerticalScrollBar->isVisible())
        {
            if (qualifiers & QUAL_CTRL)
                mVerticalScrollBar->setValue(0.0f);
            else
                mVerticalScrollBar->stepBack();
        }
        break;
        
    case KEY_DOWN:
        if (mVerticalScrollBar->isVisible())
        {
            if (qualifiers & QUAL_CTRL)
                mVerticalScrollBar->setValue(mVerticalScrollBar->getRange());
            else
                mVerticalScrollBar->stepForward();
        }
        break;
        
    case KEY_PAGEUP:
        if (mVerticalScrollBar->isVisible())
            mVerticalScrollBar->changeValue(-mPageStep);
        break;
        
    case KEY_PAGEDOWN:
        if (mVerticalScrollBar->isVisible())
            mVerticalScrollBar->changeValue(mPageStep);
        break;
    
    case KEY_HOME:
        if (mVerticalScrollBar->isVisible())
            mVerticalScrollBar->setValue(0.0f);
        break;
    
    case KEY_END:
        if (mVerticalScrollBar->isVisible())
            mVerticalScrollBar->setValue(mVerticalScrollBar->getRange());
        break;
    }
}

void ScrollView::onResize()
{
    IntVector2 panelSize = getSize();
    if (mVerticalScrollBar->isVisible())
        panelSize.mX -= mVerticalScrollBar->getWidth();
    if (mHorizontalScrollBar->isVisible())
        panelSize.mY -= mHorizontalScrollBar->getHeight();
    
    mScrollPanel->setSize(panelSize);
    mHorizontalScrollBar->setWidth(mScrollPanel->getWidth());
    mVerticalScrollBar->setHeight(mScrollPanel->getHeight());
    
    updateViewSize();
}

void ScrollView::setContentElement(UIElement* element)
{
    if (element == mContentElement)
        return;
    
    if (mContentElement)
    {
        mScrollPanel->removeChild(mContentElement);
        unsubscribeFromEvent(mContentElement, EVENT_RESIZED);
    }
    mContentElement = element;
    if (mContentElement)
    {
        mScrollPanel->addChild(mContentElement);
        subscribeToEvent(mContentElement, EVENT_RESIZED, EVENT_HANDLER(ScrollView, handleElementResized));
    }
    
    updateViewSize();
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

void ScrollView::setScrollBarsVisible(bool horizontal, bool vertical)
{
    mHorizontalScrollBar->setVisible(horizontal);
    mVerticalScrollBar->setVisible(vertical);
}

void ScrollView::setScrollStep(float step)
{
    mHorizontalScrollBar->setScrollStep(step);
    mVerticalScrollBar->setScrollStep(step);
}

void ScrollView::setPageStep(float step)
{
    mPageStep = max(step, 0.0f);
}

void ScrollView::setNormalizeScrollStep(bool enable)
{
    mHorizontalScrollBar->setNormalizeScrollStep(enable);
    mVerticalScrollBar->setNormalizeScrollStep(enable);
}

bool ScrollView::getHorizontalScrollBarVisible() const
{
    return mHorizontalScrollBar->isVisible();
}

bool ScrollView::getVerticalScrollBarVisible() const
{
    return mVerticalScrollBar->isVisible();
}

float ScrollView::getScrollStep() const
{
    return mHorizontalScrollBar->getScrollStep();
}

bool ScrollView::getNormalizeScrollStep() const
{
    return mHorizontalScrollBar->getNormalizeScrollStep();
}

void ScrollView::updateViewSize()
{
    IntVector2 size(IntVector2::sZero);
    if (mContentElement)
        size = mContentElement->getSize();
    
    mViewSize.mX = max(size.mX, mScrollPanel->getWidth());
    mViewSize.mY = max(size.mY, mScrollPanel->getHeight());
    updateView(mViewPosition);
    updateScrollBars();
}

void ScrollView::updateScrollBars()
{
    mIgnoreEvents = true;
    
    const IntVector2& size = mScrollPanel->getSize();
    
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
    
    mViewPosition.mX = clamp(position.mX, 0, mViewSize.mX - mScrollPanel->getWidth());
    mViewPosition.mY = clamp(position.mY, 0, mViewSize.mY - mScrollPanel->getHeight());
    mScrollPanel->setChildOffset(-mViewPosition);
    
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
    {
        updateView(IntVector2(
            (int)(mHorizontalScrollBar->getValue() * (float)mScrollPanel->getWidth()),
            (int)(mVerticalScrollBar->getValue() * (float)mScrollPanel->getHeight())
        ));
    }
}

void ScrollView::handleScrollBarVisibleChanged(StringHash eventType, VariantMap& eventData)
{
    // Need to recalculate panel size when scrollbar visibility changes
    onResize();
}

void ScrollView::handleElementResized(StringHash eventType, VariantMap& eventData)
{
    updateViewSize();
}
