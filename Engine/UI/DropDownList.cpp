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
#include "DropDownList.h"
#include "ListView.h"
#include "UIEvents.h"
#include "Window.h"

#include "DebugNew.h"

DropDownList::DropDownList(const std::string& name) :
    Menu(name),
    mResizePopup(false)
{
    Window* window = new Window();
    setPopup(window);
    
    mListView = new ListView();
    mListView->setScrollBarsVisible(false, false);
    mListView->setFocusMode(FM_NOTFOCUSABLE);
    mPopup->setLayout(LM_VERTICAL);
    mPopup->addChild(mListView);
    mPlaceholder = new UIElement();
    addChild(mPlaceholder);
    
    subscribeToEvent(mListView, EVENT_ITEMSELECTED, EVENT_HANDLER(DropDownList, handleItemSelected));
}

DropDownList::~DropDownList()
{
}

void DropDownList::setStyle(const XMLElement& element, ResourceCache* cache)
{
    Menu::setStyle(element, cache);
    
    XMLElement listElem = element.getChildElement("listview");
    if (listElem)
        mListView->setStyle(listElem, cache);
    
    XMLElement popupElem = element.getChildElement("popup");
    if (popupElem)
        mPopup->setStyle(popupElem, cache);
    
    XMLElement placeholderElem = element.getChildElement("placeholder");
    if (placeholderElem)
        mPlaceholder->setStyle(placeholderElem, cache);
    
    UIElement* root = getRootElement();
    XMLElement itemElem = element.getChildElement("popupitem");
    if (root)
    {
        while (itemElem)
        {
            if (itemElem.hasAttribute("name"))
                addItem(root->getChild(itemElem.getString("name"), true));
            itemElem = itemElem.getNextElement("popupitem");
        }
    }
    
    if (element.hasChildElement("selection"))
        setSelection(element.getChildElement("selection").getInt("value"));
    if (element.hasChildElement("resizepopup"))
        setResizePopup(element.getChildElement("resizepopup").getBool("enable"));
}

void DropDownList::getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor)
{
    Button::getBatches(batches, quads, currentScissor);
    
    UIElement* selectedItem = getSelectedItem();
    if (selectedItem)
    {
        // We can not easily copy the selected item. However, we can re-render it on the placeholder's position
        const IntVector2& targetPos = mPlaceholder->getScreenPosition();
        const IntVector2& originalPos = selectedItem->getScreenPosition();
        IntVector2 offset = targetPos - originalPos;
        
        // getBatches() usually resets the hover flag. Therefore get its value and then reset it for the real rendering
        bool hover = selectedItem->isHovering();
        selectedItem->setHovering(false);
        selectedItem->getBatchesWithOffset(offset, batches, quads, currentScissor);
        selectedItem->setHovering(hover);
    }
}

void DropDownList::onShowPopup()
{
    // Resize the popup to match the size of the list content, and optionally match the button width
    UIElement* content = mListView->getContentElement();
    content->updateLayout();
    const IntVector2& contentSize = content->getSize();
    const IntRect& border = mPopup->getLayoutBorder();
    mPopup->setSize(mResizePopup ? getWidth() : contentSize.mX + border.mLeft + border.mRight, contentSize.mY + border.mTop + 
        border.mBottom);
    
    // Check if popup fits below the button. If not, show above instead
    bool showAbove = false;
    UIElement* root = getRootElement();
    if (root)
    {
        const IntVector2& screenPos = getScreenPosition();
        if ((screenPos.mY + getHeight() + mPopup->getHeight() > root->getHeight()) && (screenPos.mY - mPopup->getHeight() >= 0))
            showAbove = true;
    }
    if (!showAbove)
        setPopupOffset(0, getHeight());
    else
        setPopupOffset(0, -mPopup->getHeight());
}

void DropDownList::addItem(UIElement* item)
{
    insertItem(mListView->getNumItems(), item);
}

void DropDownList::insertItem(unsigned index, UIElement* item)
{
    mListView->insertItem(index, item);
    
    // If there was no selection, set to the first
    if (mListView->getSelection() == M_MAX_UNSIGNED)
        mListView->setSelection(0);
}

void DropDownList::removeItem(UIElement* item)
{
    mListView->removeItem(item);
}

void DropDownList::removeItem(unsigned index)
{
    mListView->removeItem(index);
}

void DropDownList::removeAllItems()
{
    mListView->removeAllItems();
}

void DropDownList::setSelection(unsigned index)
{
    // The list should always show a selection if possible, so clamp the selection
    unsigned numItems = getNumItems();
    if (index >= numItems)
        index = numItems - 1;
    mListView->setSelection(index);
}

void DropDownList::setResizePopup(bool enable)
{
    mResizePopup = enable;
}

unsigned DropDownList::getNumItems() const
{
    return mListView->getNumItems();
}

UIElement* DropDownList::getItem(unsigned index) const
{
    return mListView->getItem(index);
}

std::vector<UIElement*> DropDownList::getItems() const
{
    return mListView->getContentElement()->getChildren();
}

unsigned DropDownList::getSelection() const
{
    return mListView->getSelection();
}

UIElement* DropDownList::getSelectedItem() const
{
    return mListView->getSelectedItem();
}

void DropDownList::handleItemSelected(StringHash eventType, VariantMap& eventData)
{
    // Resize the selection placeholder to match the selected item
    UIElement* selectedItem = getSelectedItem();
    if (selectedItem)
        mPlaceholder->setSize(selectedItem->getSize());
    
    // Close the popup as the selection was made
    if (getShowPopup())
        showPopup(false);
    
    // Send the event forward
    using namespace ItemSelected;
    
    VariantMap newEventData;
    newEventData[P_ELEMENT] = (void*)this;
    newEventData[P_SELECTION] = getSelection();
    sendEvent(EVENT_ITEMSELECTED, newEventData);
}
