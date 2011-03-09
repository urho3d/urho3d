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
#include "StringUtils.h"
#include "UIEvents.h"

#include "DebugNew.h"

static const ShortStringHash indentHash("Indent");

static const std::string highlightModes[] =
{
    "never",
    "focus",
    "always"
};

int getItemIndent(UIElement* item)
{
    if (!item)
        return 0;
    return item->getUserData()[indentHash].getInt();
}

ListView::ListView(const std::string& name) :
    ScrollView(name),
    mHighlightMode(HM_FOCUS),
    mMultiselect(false),
    mHierarchyMode(false),
    mClearSelectionOnDefocus(false),
    mDoubleClickInterval(0.5f),
    mDoubleClickTimer(0.0f),
    mLastClickedItem(M_MAX_UNSIGNED)
{
    UIElement* container = new UIElement();
    container->setEnabled(true);
    container->setLayout(LM_VERTICAL);
    setContentElement(container);
    
    subscribeToEvent(EVENT_UIMOUSECLICK, EVENT_HANDLER(ListView, handleUIMouseClick));
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
            if (itemElem.hasAttribute("name"))
            {
                UIElement* item = root->getChild(itemElem.getString("name"), true);
                addItem(item);
                if (itemElem.hasAttribute("indent"))
                    item->getUserData()[indentHash] = itemElem.getInt("indent");
                itemElem = itemElem.getNextElement("listitem");
            }
        }
    }
    
    if (element.hasChildElement("highlight"))
    {
        std::string highlight = element.getChildElement("highlight").getStringLower("value");
        setHighlightMode((HighlightMode)getIndexFromStringList(highlight, highlightModes, 3, 1));
    }
    if (element.hasChildElement("multiselect"))
        setMultiselect(element.getChildElement("multiselect").getBool("enable"));
    if (element.hasChildElement("hierarchy"))
        setHierarchyMode(element.getChildElement("hierarchy").getBool("enable"));
    if (element.hasChildElement("clearselection"))
        setClearSelectionOnDefocus(element.getChildElement("clearselection").getBool("enable"));
    if (element.hasChildElement("doubleclickinterval"))
        setDoubleClickInterval(element.getChildElement("doubleclickinterval").getFloat("value"));
    
    XMLElement selectionElem = element.getChildElement("selection");
    while (selectionElem)
    {
        addSelection(selectionElem.getInt("value"));
        selectionElem = selectionElem.getNextElement("selection");
    }
}

void ListView::update(float timeStep)
{
    if (mDoubleClickTimer > 0.0f)
        mDoubleClickTimer = max(mDoubleClickTimer - timeStep, 0.0f);
}

void ListView::onKey(int key, int buttons, int qualifiers)
{
    // If no selection, can not move with keys
    unsigned numItems = getNumItems();
    unsigned selection = getSelection();
    
    if ((selection != M_MAX_UNSIGNED) && (numItems))
    {
        // If either shift or ctrl held down, add to selection if multiselect enabled
        bool additive = (mMultiselect) && (qualifiers != 0);
        
        switch (key)
        {
        case KEY_LEFT:
            if (mHierarchyMode)
            {
                setChildItemsVisible(selection, false);
                return;
            }
            break;
            
        case KEY_RIGHT:
            if (mHierarchyMode)
            {
                setChildItemsVisible(selection, true);
                return;
            }
            break;
            
        case KEY_RETURN:
            if (mHierarchyMode)
            {
                toggleChildItemsVisible(selection);
                return;
            }
            break;
            
        case KEY_UP:
            changeSelection(-1, additive);
            return;
            
        case KEY_DOWN:
            changeSelection(1, additive);
            return;
            
        case KEY_PAGEUP:
            {
                // Convert page step to pixels and see how many items we have to skip to reach that many pixels
                int stepPixels = ((int)(mPageStep * mScrollPanel->getHeight())) - getSelectedItem()->getHeight();
                unsigned newSelection = selection;
                unsigned okSelection = selection;
                while (newSelection < numItems)
                {
                    UIElement* item = getItem(newSelection);
                    int height = 0;
                    if (item->isVisible())
                    {
                        height = item->getHeight();
                        okSelection = newSelection;
                    }
                    if (stepPixels < height)
                        break;
                    stepPixels -= height;
                    --newSelection;
                }
                if (!additive)
                    setSelection(okSelection);
                else
                    addSelection(okSelection);
            }
            return;
            
        case KEY_PAGEDOWN:
            {
                int stepPixels = ((int)(mPageStep * mScrollPanel->getHeight())) - getSelectedItem()->getHeight();
                unsigned newSelection = selection;
                unsigned okSelection = selection;
                while (newSelection < numItems)
                {
                    UIElement* item = getItem(newSelection);
                    int height = 0;
                    if (item->isVisible())
                    {
                        height = item->getHeight();
                        okSelection = newSelection;
                    }
                    if (stepPixels < height)
                        break;
                    stepPixels -= height;
                    ++newSelection;
                }
                if (!additive)
                    setSelection(okSelection);
                else
                    addSelection(okSelection);
            }
            return;
            
        case KEY_HOME:
            changeSelection(-(int)getNumItems(), additive);
            return;
            
        case KEY_END:
            changeSelection(getNumItems(), additive);
            return;
        }
    }
    
    using namespace UnhandledKey;
    
    VariantMap eventData;
    eventData[P_ELEMENT] = (void*)this;
    eventData[P_KEY] = key;
    eventData[P_BUTTONS] = buttons;
    eventData[P_QUALIFIERS] = qualifiers;
    sendEvent(EVENT_UNHANDLEDKEY, eventData);
}

void ListView::onResize()
{
    ScrollView::onResize();
    
    // Set the content element width to match the scrollpanel
    const IntRect& clipBorder = mScrollPanel->getClipBorder();
    mContentElement->setWidth(mScrollPanel->getWidth() - clipBorder.mLeft - clipBorder.mRight);
}

void ListView::onFocus()
{
    updateSelectionEffect();
}

void ListView::onDefocus()
{
    if (mClearSelectionOnDefocus)
        clearSelection();
    
    updateSelectionEffect();
}

void ListView::addItem(UIElement* item)
{
    insertItem(mContentElement->getNumChildren(), item);
}

void ListView::insertItem(unsigned index, UIElement* item)
{
    if ((!item) || (item->getParent() == mContentElement))
        return;
    
    // Enable input so that clicking the item can be detected
    item->setEnabled(true);
    item->setSelected(false);
    mContentElement->insertChild(index, item);
    
    // If necessary, shift the following selections
    std::set<unsigned> prevSelections;
    mSelections.clear();
    for (std::set<unsigned>::iterator j = prevSelections.begin(); j != prevSelections.end(); ++j)
    {
        if (*j >= index)
            mSelections.insert(*j + 1);
        else
            mSelections.insert(*j);
    }
    updateSelectionEffect();
}

void ListView::removeItem(UIElement* item)
{
    unsigned numItems = getNumItems();
    
    for (unsigned i = 0; i < numItems; ++i)
    {
        if (getItem(i) == item)
        {
            item->setSelected(false);
            mSelections.erase(i);
            
            // Remove any child items in hierarchy mode
            unsigned removed = 1;
            if (mHierarchyMode)
            {
                int baseIndent = getItemIndent(item);
                int j = i + 1;
                for (;;)
                {
                    UIElement* childItem = getItem(i + 1);
                    if (!childItem)
                        break;
                    if (getItemIndent(childItem) > baseIndent)
                    {
                        childItem->setSelected(false);
                        mSelections.erase(j);
                        mContentElement->removeChild(childItem);
                        ++removed;
                    }
                    else
                        break;
                    ++j;
                }
            }
            
            // If necessary, shift the following selections
            std::set<unsigned> prevSelections;
            mSelections.clear();
            for (std::set<unsigned>::iterator j = prevSelections.begin(); j != prevSelections.end(); ++j)
            {
                if (*j > i)
                    mSelections.insert(*j - removed);
                else
                    mSelections.insert(*j);
            }
            updateSelectionEffect();
            break;
        }
    }
    mContentElement->removeChild(item);
}

void ListView::removeItem(unsigned index)
{
    removeItem(getItem(index));
}

void ListView::removeAllItems()
{
    unsigned numItems = getNumItems();
    for (unsigned i = 0; i < numItems; ++i)
        mContentElement->getChild(i)->setSelected(false);
    mContentElement->removeAllChildren();
    clearSelection();
}

void ListView::setSelection(unsigned index)
{
    std::set<unsigned> indices;
    indices.insert(index);
    setSelections(indices);
    ensureItemVisibility(index);
}

void ListView::setSelections(const std::set<unsigned>& indices)
{
    unsigned numItems = getNumItems();
    
    // Remove first items that should no longer be selected
    for (std::set<unsigned>::iterator i = mSelections.begin(); i != mSelections.end();)
    {
        unsigned index = *i;
        if (indices.find(index) == indices.end())
        {
            std::set<unsigned>::iterator current = i++;
            mSelections.erase(current);
            
            using namespace ItemSelected;
            
            VariantMap eventData;
            eventData[P_ELEMENT] = (void*)this;
            eventData[P_SELECTION] = index;
            sendEvent(EVENT_ITEMDESELECTED, eventData);
        }
        else
            ++i;
    }
    
    // Then add missing items
    for (std::set<unsigned>::const_iterator i = indices.begin(); i != indices.end(); ++i)
    {
        unsigned index = *i;
        if (index < numItems)
        {
            // In singleselect mode, resend the event even for the same selection
            if ((mSelections.find(index) == mSelections.end()) || (!mMultiselect))
            {
                mSelections.insert(*i);
                
                using namespace ItemSelected;
                
                VariantMap eventData;
                eventData[P_ELEMENT] = (void*)this;
                eventData[P_SELECTION] = *i;
                sendEvent(EVENT_ITEMSELECTED, eventData);
            }
        }
        // If no multiselect enabled, allow setting only one item
        if (!mMultiselect)
            break;
    }
    
    updateSelectionEffect();
}

void ListView::addSelection(unsigned index)
{
    if (!mMultiselect)
        setSelection(index);
    else
    {
        if (index >= getNumItems())
            return;
        
        std::set<unsigned> newSelections = mSelections;
        newSelections.insert(index);
        setSelections(newSelections);
        ensureItemVisibility(index);
    }
}

void ListView::removeSelection(unsigned index)
{
    if (index >= getNumItems())
        return;
    
    std::set<unsigned> newSelections = mSelections;
    newSelections.erase(index);
    setSelections(newSelections);
    ensureItemVisibility(index);
}

void ListView::toggleSelection(unsigned index)
{
    unsigned numItems = getNumItems();
    if (index >= numItems)
        return;
    
    if (mSelections.find(index) != mSelections.end())
        removeSelection(index);
    else
        addSelection(index);
}

void ListView::changeSelection(int delta, bool additive)
{
    if (mSelections.empty())
        return;
    if (!mMultiselect)
        additive = false;
    
    // If going downwards, use the last selection as a base. Otherwise use first
    unsigned selection = delta > 0 ? *mSelections.rbegin() : *mSelections.begin();
    unsigned numItems = getNumItems();
    unsigned newSelection = selection;
    unsigned okSelection = selection;
    while (delta != 0)
    {
        if (delta > 0)
        {
            ++newSelection;
            if (newSelection >= numItems)
                break;
        }
        if (delta < 0)
        {
            --newSelection;
            if (newSelection >= numItems)
                break;
        }
        UIElement* item = getItem(newSelection);
        if (item->isVisible())
        {
            okSelection = newSelection;
            if (delta > 0)
                --delta;
            if (delta < 0)
                ++delta;
        }
    }
    
    if (!additive)
        setSelection(okSelection);
    else
        addSelection(okSelection);
}

void ListView::clearSelection()
{
    setSelections(std::set<unsigned>());
    updateSelectionEffect();
}

void ListView::setHighlightMode(HighlightMode mode)
{
    mHighlightMode = mode;
    updateSelectionEffect();
}

void ListView::setMultiselect(bool enable)
{
    mMultiselect = enable;
}

void ListView::setHierarchyMode(bool enable)
{
    mHierarchyMode = enable;
}

void ListView::setClearSelectionOnDefocus(bool enable)
{
    mClearSelectionOnDefocus = enable;
}

void ListView::setDoubleClickInterval(float interval)
{
    mDoubleClickInterval = interval;
}

void ListView::setChildItemsVisible(unsigned index, bool enable)
{
    unsigned numItems = getNumItems();
    
    if ((!mHierarchyMode) || (index >= numItems))
        return;
    
    int baseIndent = getItemIndent(getItem(index));
    
    for (unsigned i = index + 1; i < numItems; ++i)
    {
        UIElement* item = getItem(i);
        if (getItemIndent(item) > baseIndent)
            item->setVisible(enable);
        else
            break;
    }
}

void ListView::setChildItemsVisible(bool enable)
{
    unsigned numItems = getNumItems();
    
    for (unsigned i = 0; i < numItems; ++i)
    {
        if (!getItemIndent(getItem(i)))
            setChildItemsVisible(i, enable);
    }
    
    if (getSelections().size() == 1)
        ensureItemVisibility(getSelection());
}

void ListView::toggleChildItemsVisible(unsigned index)
{
    unsigned numItems = getNumItems();
    
    if ((!mHierarchyMode) || (index >= numItems))
        return;
    
    int baseIndent = getItemIndent(getItem(index));
    
    for (unsigned i = index + 1; i < numItems; ++i)
    {
        UIElement* item = getItem(i);
        if (getItemIndent(item) > baseIndent)
            item->setVisible(!item->isVisible());
        else
            break;
    }
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

unsigned ListView::getSelection() const
{
    if (mSelections.empty())
        return M_MAX_UNSIGNED;
    else
        return *mSelections.begin();
}

UIElement* ListView::getSelectedItem() const
{
    return mContentElement->getChild(getSelection());
}

std::vector<UIElement*> ListView::getSelectedItems() const
{
    std::vector<UIElement*> ret;
    for (std::set<unsigned>::const_iterator i = mSelections.begin(); i != mSelections.end(); ++i)
    {
        UIElement* item = getItem(*i);
        if (item)
            ret.push_back(item);
    }
    return ret;
}

void ListView::updateSelectionEffect()
{
    unsigned numItems = getNumItems();
    
    for (unsigned i = 0; i < numItems; ++i)
    {
        UIElement* item = getItem(i);
        if ((mHighlightMode != HM_NEVER) && (mSelections.find(i) != mSelections.end()))
            item->setSelected((mFocus) || (mHighlightMode == HM_ALWAYS));
        else
            item->setSelected(false);
    }
}

void ListView::ensureItemVisibility(unsigned index)
{
    UIElement* item = getItem(index);
    if ((!item) || (!item->isVisible()))
        return;
    
    IntVector2 currentOffset = item->getScreenPosition() - mScrollPanel->getScreenPosition() - mContentElement->getPosition();
    IntVector2 newView = getViewPosition();
    const IntRect& clipBorder = mScrollPanel->getClipBorder();
    IntVector2 windowSize(mScrollPanel->getWidth() - clipBorder.mLeft - clipBorder.mRight, mScrollPanel->getHeight() -
        clipBorder.mTop - clipBorder.mBottom);
    
    if (currentOffset.mY < 0)
        newView.mY += currentOffset.mY;
    if (currentOffset.mY + item->getHeight() > windowSize.mY)
        newView.mY += currentOffset.mY + item->getHeight() - windowSize.mY;
    
    setViewPosition(newView);
}

void ListView::handleUIMouseClick(StringHash eventType, VariantMap& eventData)
{
    if (eventData[UIMouseClick::P_BUTTON].getInt() != MOUSEB_LEFT)
        return;
    int qualifiers = eventData[UIMouseClick::P_QUALIFIERS].getInt();
    
    UIElement* element = static_cast<UIElement*>(eventData[UIMouseClick::P_ELEMENT].getPtr());
    
    unsigned numItems = getNumItems();
    for (unsigned i = 0; i < numItems; ++i)
    {
        if (element == getItem(i))
        {
            // Check doubleclick
            bool isDoubleClick = false;
            if ((!mMultiselect) || (!qualifiers))
            {
                if ((mDoubleClickTimer > 0.0f) && (mLastClickedItem == i))
                {
                    isDoubleClick = true;
                    mDoubleClickTimer = 0.0f;
                }
                else
                {
                    mDoubleClickTimer = mDoubleClickInterval;
                    mLastClickedItem = i;
                }
                setSelection(i);
            }
            
            // Check multiselect with shift & ctrl
            if (mMultiselect)
            {
                if (qualifiers & QUAL_SHIFT)
                {
                    if (mSelections.empty())
                        setSelection(i);
                    else
                    {
                        unsigned first = *mSelections.begin();
                        unsigned last = *mSelections.rbegin();
                        std::set<unsigned> newSelections = mSelections;
                        if ((i == first) || (i == last))
                        {
                            for (unsigned j = first; j <= last; ++j)
                                newSelections.insert(j);
                        }
                        else if (i < first)
                        {
                            for (unsigned j = i; j <= first; ++j)
                                newSelections.insert(j);
                        }
                        else if (i < last)
                        {
                            if ((abs((int)i - (int)first)) <= (abs((int)i - (int)last)))
                            {
                                for (unsigned j = first; j <= i; ++j)
                                    newSelections.insert(j);
                            }
                            else
                            {
                                for (unsigned j = i; j <= last; ++j)
                                    newSelections.insert(j);
                            }
                        }
                        else if (i > last)
                        {
                            for (unsigned j = last; j <= i; ++j)
                                newSelections.insert(j);
                        }
                        setSelections(newSelections);
                    }
                }
                else if (qualifiers & QUAL_CTRL)
                    toggleSelection(i);
            }
            
            if (isDoubleClick)
            {
                if (mHierarchyMode)
                    toggleChildItemsVisible(i);
                
                VariantMap eventData;
                eventData[ItemDoubleClicked::P_ELEMENT] = (void*)this;
                eventData[ItemDoubleClicked::P_SELECTION] = i;
                sendEvent(EVENT_ITEMDOUBLECLICKED, eventData);
            }
            
            return;
        }
    }
}
