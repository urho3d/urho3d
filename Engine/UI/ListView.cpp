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
#include "Log.h"
#include "UIEvents.h"

ListView::ListView(const std::string& name) :
    ScrollView(name),
    mSelection(M_MAX_UNSIGNED)
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
}

void ListView::onKey(int key, int buttons, int qualifiers)
{
    // If no selection, can not move with keys
    if ((mSelection == M_MAX_UNSIGNED) || (mItems.empty()))
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
            setSelection(mItems.size() - 1);
        else
            changeSelection(1);
        break;
        
    case KEY_PAGEUP:
        changeSelection((int)-mPageStep);
        break;
        
    case KEY_PAGEDOWN:
        changeSelection((int)mPageStep);
        break;
    
    case KEY_HOME:
        setSelection(0);
        break;
    
    case KEY_END:
        setSelection(mItems.size() - 1);
        break;
    }
}

void ListView::addItem(UIElement* item)
{
    if ((!item) || (hasItem(item)))
        return;
    
    // Enable input so that clicking the item can be detected
    item->setEnabled(true);
    mItems.push_back(SharedPtr<UIElement>(item));
    mContentElement->addChild(item);
}

void ListView::addItem(unsigned index, UIElement* item)
{
    if ((!item) || (hasItem(item)))
        return;
    if (index > mItems.size())
        index = mItems.size();
    
    // Enable input so that clicking the item can be detected
    item->setEnabled(true);
    mItems.insert(mItems.begin() + index, SharedPtr<UIElement>(item));
    updateList();
    
    if (mSelection >= index)
        setSelection(mSelection + 1);
}

void ListView::setItem(unsigned index, UIElement* item)
{
    if (index >= mItems.size())
    {
        LOGERROR("Illegal ListView item index");
        return;
    }
    if ((!item) || (hasItem(item)))
        return;
    
    // Enable input so that clicking the item can be detected
    item->setEnabled(true);
    mItems[index] = item;
    updateList();
}

void ListView::removeItem(UIElement* item)
{
    if (!item)
        return;
    
    for (unsigned i = 0; i < mItems.size(); ++i)
    {
        if (mItems[i] == item)
        {
            mItems.erase(mItems.begin() + i);
            mContentElement->removeChild(item);
            
            if (mSelection == i)
                setSelection(M_MAX_UNSIGNED);
            else if (mSelection > i)
                setSelection(mSelection - 1);
            
            return;
        }
    }
}

void ListView::removeItem(unsigned index)
{
    if (index >= mItems.size())
        return;
    
    UIElement* item = mItems[index];
    mItems.erase(mItems.begin() + index);
    mContentElement->removeChild(item);
    
    if (mSelection == index)
        setSelection(M_MAX_UNSIGNED);
    else if (mSelection > index)
        setSelection(mSelection - 1);
}

void ListView::removeAllItems()
{
    setSelection(M_MAX_UNSIGNED);
    mItems.clear();
    updateList();
}

void ListView::setSelection(unsigned index)
{
    if (index >= mItems.size())
        index = M_MAX_UNSIGNED;
    
    for (unsigned i = 0; i < mItems.size(); ++i)
        mItems[i]->setSelected(i == index);
    mSelection = index;
    
    ensureItemVisibility();
}

void ListView::changeSelection(int delta)
{
    if (mSelection == M_MAX_UNSIGNED)
        return;
    
    int newSelection = clamp((int)mSelection + delta, 0, (int)mItems.size() - 1);
    setSelection(newSelection);
}

UIElement* ListView::getItem(unsigned index) const
{
    if (index >= mItems.size())
        return 0;
    
    return mItems[index];
}

bool ListView::hasItem(UIElement* item) const
{
    for (unsigned i = 0; i < mItems.size(); ++i)
    {
        if (mItems[i] == item)
            return true;
    }
    return false;
}

UIElement* ListView::getSelectedItem() const
{
    return getItem(mSelection);
}

void ListView::updateList()
{
    mContentElement->removeAllChildren();
    for (unsigned i = 0; i < mItems.size(); ++i)
        mContentElement->addChild(mItems[i]);
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
        setSelection(M_MAX_UNSIGNED);
        return;
    }
    
    for (unsigned i = 0; i < mItems.size(); ++i)
    {
        if (focusElement == mItems[i])
        {
            setSelection(i);
            return;
        }
    }
}
