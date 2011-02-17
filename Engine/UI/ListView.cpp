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
#include "ListView.h"
#include "UIEvents.h"

ListView::ListView(const std::string& name) :
    ScrollView(name),
    mSelection(M_MAX_UNSIGNED),
    mShowSelectionAlways(false)
{
    UIElement* container = new UIElement();
    container->setEnabled(true);
    container->setLayout(O_VERTICAL, LM_RESIZECHILDREN, LM_RESIZEELEMENT);
    
    mScrollPanel->setLayout(O_HORIZONTAL, LM_RESIZECHILDREN, LM_FREE);
    setContentElement(container);
    
    subscribeToEvent(EVENT_TRYFOCUS, EVENT_HANDLER(ListView, handleTryFocus));
}

ListView::~ListView()
{
}

void ListView::setStyle(const XMLElement& element, ResourceCache* cache)
{
    ScrollView::setStyle(element, cache);
    
    UIElement* root = getRootElement();
    XMLElement itemElem = element.getChildElement("listitem");
    if (root)
    {
        while (itemElem)
        {
            addItem(root->getChild(itemElem.getString("name"), true));
            itemElem = itemElem.getNextElement("listitem");
        }
    }
    
    if (element.hasChildElement("selection"))
        setSelection(element.getChildElement("selection").getInt("value"));
    if (element.hasChildElement("showselectionalways"))
        setShowSelectionAlways(element.getChildElement("showselectionalways").getBool("enable"));
}

void ListView::onWheel(int delta, int buttons, int qualifiers)
{
    if (delta > 0)
        changeSelection(-1);
    if (delta < 0)
        changeSelection(1);
}

void ListView::onKey(int key, int buttons, int qualifiers)
{
    // If no selection, can not move with keys
    if ((mSelection == M_MAX_UNSIGNED) || (!getNumItems()))
        return;
    
    switch (key)
    {
    case KEY_UP:
        if (qualifiers & QUAL_CTRL)
            setSelection(0);
        else
            changeSelection(-1);
        break;
        
    case KEY_DOWN:
        if (qualifiers & QUAL_CTRL)
            setSelection(getNumItems() - 1);
        else
            changeSelection(1);
        break;
        
    case KEY_PAGEUP:
        {
            // Convert page step to pixels and see how many items we have to skip to reach that many pixels
            int stepPixels = ((int)(mPageStep * mScrollPanel->getHeight())) - getSelectedItem()->getHeight();
            unsigned newSelection = mSelection;
            while (newSelection)
            {
                int height = getItem(newSelection)->getHeight();
                if (stepPixels < height)
                    break;
                stepPixels -= height;
                --newSelection;
            }
            setSelection(newSelection);
        }
        break;
        
    case KEY_PAGEDOWN:
        {
            int stepPixels = ((int)(mPageStep * mScrollPanel->getHeight())) - getSelectedItem()->getHeight();
            unsigned newSelection = mSelection;
            while (newSelection < getNumItems() - 1)
            {
                int height = getItem(newSelection)->getHeight();
                if (stepPixels < height)
                    break;
                stepPixels -= height;
                ++newSelection;
            }
            setSelection(newSelection);
        }
        break;
        
    case KEY_HOME:
        setSelection(0);
        break;
        
    case KEY_END:
        setSelection(getNumItems() - 1);
        break;
    }
}

void ListView::onFocus()
{
    updateSelectionEffect();
}

void ListView::onDefocus()
{
    updateSelectionEffect();
}

void ListView::addItem(UIElement* item)
{
    if ((!item) || (item->getParent() == mContentElement))
        return;
    
    // Enable input so that clicking the item can be detected
    item->setEnabled(true);
    mContentElement->addChild(item);
}

void ListView::removeItem(UIElement* item)
{
    std::vector<UIElement*> items = mContentElement->getChildren();
    for (unsigned i = 0; i < items.size(); ++i)
    {
        if (items[i] == item)
        {
            if (mSelection == i)
                clearSelection();
            else if (mSelection > i)
                changeSelection(-1);
            break;
        }
    }
    mContentElement->removeChild(item);
}

void ListView::removeItem(unsigned index)
{
    if (index >= getNumItems())
        return;
    UIElement* item = mContentElement->getChild(index);
    if (mSelection == index)
        clearSelection();
    else if (mSelection > index)
        changeSelection(-1);
    mContentElement->removeChild(item);
}

void ListView::removeAllItems()
{
    mContentElement->removeAllChildren();
    clearSelection();
}

void ListView::setSelection(unsigned index)
{
    if (index >= getNumItems())
        index = M_MAX_UNSIGNED;
    
    mSelection = index;
    updateSelectionEffect();
    ensureItemVisibility();
}

void ListView::changeSelection(int delta)
{
    if (mSelection == M_MAX_UNSIGNED)
        return;
    
    int newSelection = clamp((int)mSelection + delta, 0, (int)getNumItems() - 1);
    setSelection(newSelection);
}

void ListView::clearSelection()
{
    setSelection(M_MAX_UNSIGNED);
}

void ListView::setShowSelectionAlways(bool enable)
{
    mShowSelectionAlways = enable;
}

unsigned ListView::getNumItems() const
{
    return mContentElement->getNumChildren();
}

UIElement* ListView::getItem(unsigned index) const
{
    return mContentElement->getChild(index);
}

std::vector<UIElement*> ListView::getItems() const
{
    return mContentElement->getChildren();
}

UIElement* ListView::getSelectedItem() const
{
    return mContentElement->getChild(mSelection);
}

void ListView::updateSelectionEffect()
{
    unsigned numItems = getNumItems();
    for (unsigned i = 0; i < numItems; ++i)
        getItem(i)->setSelected((i == mSelection) && ((mFocus) || (mShowSelectionAlways)));
}

void ListView::ensureItemVisibility()
{
    UIElement* selected = getSelectedItem();
    if (!selected)
        return;
    
    IntVector2 currentOffset = selected->getScreenPosition() - mScrollPanel->getScreenPosition() - mContentElement->getPosition();
    IntVector2 newView = getViewPosition();
    const IntRect& clipBorder = mScrollPanel->getClipBorder();
    IntVector2 windowSize(mScrollPanel->getWidth() - clipBorder.mLeft - clipBorder.mRight, mScrollPanel->getHeight() -
        clipBorder.mTop - clipBorder.mBottom);
    
    if (currentOffset.mX < 0)
        newView.mX += currentOffset.mX;
    if (currentOffset.mX + selected->getWidth() > windowSize.mX)
        newView.mX += currentOffset.mX + selected->getWidth() - windowSize.mX;
    if (currentOffset.mY < 0)
        newView.mY += currentOffset.mY;
    if (currentOffset.mY + selected->getHeight() > windowSize.mY)
        newView.mY += currentOffset.mY + selected->getHeight() - windowSize.mY;
    
    setViewPosition(newView);
}

void ListView::handleTryFocus(StringHash eventType, VariantMap& eventData)
{
    using namespace TryFocus;
    
    UIElement* focusElement = static_cast<UIElement*>(eventData[P_ELEMENT].getPtr());
    
    // If the scrollpanel itself was clicked, and not the container / items, clear selection
    if (focusElement == mScrollPanel)
    {
        clearSelection();
        return;
    }
    
    unsigned numItems = getNumItems();
    for (unsigned i = 0; i < numItems; ++i)
    {
        if (focusElement == getItem(i))
        {
            setSelection(i);
            return;
        }
    }
}
