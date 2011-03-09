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
#include "Menu.h"
#include "UIEvents.h"

#include "DebugNew.h"

static const ShortStringHash originHash("origin");

Menu::Menu(const std::string& name) :
    Button(name),
    mPopupOffset(IntVector2::sZero),
    mShowPopup(false),
    mAcceleratorKey(0),
    mAcceleratorQualifiers(0)
{
    subscribeToEvent(this, EVENT_RELEASED, EVENT_HANDLER(Menu, handleReleased));
    subscribeToEvent(EVENT_UIMOUSECLICK, EVENT_HANDLER(Menu, handleFocusChanged));
    subscribeToEvent(EVENT_FOCUSCHANGED, EVENT_HANDLER(Menu, handleFocusChanged));
}

Menu::~Menu()
{
    if (mPopup)
        showPopup(false);
}

void Menu::setStyle(const XMLElement& element, ResourceCache* cache)
{
    Button::setStyle(element, cache);
    
    XMLElement popupElem = element.getChildElement("popup");
    if ((popupElem) && (popupElem.hasAttribute("name")))
    {
        UIElement* root = getRootElement();
        if (root)
            setPopup(root->getChild(popupElem.getString("name"), true));
    }
    
    if (element.hasChildElement("popupoffset"))
        setPopupOffset(element.getChildElement("popupoffset").getIntVector2("value"));
}

void Menu::onShowPopup()
{
}

void Menu::setPopup(UIElement* popup)
{
    if (popup == this)
        return;
    
    if ((mPopup) && (!popup))
        showPopup(false);
    
    mPopup = popup;
    
    // Detach from current parent (if any) to only show when it is time
    if (mPopup)
    {
        UIElement* parent = mPopup->getParent();
        if (parent)
            parent->removeChild(mPopup);
    }
}

void Menu::setPopupOffset(const IntVector2& offset)
{
    mPopupOffset = offset;
}

void Menu::setPopupOffset(int x, int y)
{
    mPopupOffset = IntVector2(x, y);
}

void Menu::showPopup(bool enable)
{
    if (!mPopup)
        return;
    
    // Find the UI root element for showing the popup. If we are already detached, try to find it through the popup
    UIElement* root = getRootElement();
    if (!root)
        root = mPopup->getRootElement();
    if (!root)
        return;
    
    if (enable)
    {
        onShowPopup();
        
        mPopup->setPosition(getScreenPosition() + mPopupOffset);
        mPopup->setVisible(true);
        mPopup->getUserData()[originHash] = (void*)this;
        root->addChild(mPopup);
        
        // Set fixed high priority
        mPopup->setBringToFront(false);
        mPopup->setBringToBack(false);
        mPopup->bringToFront();
    }
    else
    {
        mPopup->getUserData()[originHash].clear();
        root->removeChild(mPopup);
    }
    
    mShowPopup = enable;
    mSelected = enable;
}

void Menu::setAccelerator(int key, int qualifiers)
{
    mAcceleratorKey = key;
    mAcceleratorQualifiers = qualifiers;
    
    if (key)
        subscribeToEvent(EVENT_KEYDOWN, EVENT_HANDLER(Menu, handleKeyDown));
    else
        unsubscribeFromEvent(EVENT_KEYDOWN);
}

void Menu::handleReleased(StringHash eventType, VariantMap& eventData)
{
    // Toggle popup visibility if exists
    showPopup(!mShowPopup);
    
    // Send event on each click if no popup, or whenever the popup is opened
    if ((!mPopup) || (mShowPopup))
    {
        using namespace MenuSelected;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        sendEvent(EVENT_MENUSELECTED, eventData);
    }
}

void Menu::handleFocusChanged(StringHash eventType, VariantMap& eventData)
{
    if (!mShowPopup)
        return;
    
    using namespace FocusChanged;
    
    UIElement* element = static_cast<UIElement*>(eventData[P_ELEMENT].getPtr());
    UIElement* root = getRootElement();
    
    // If clicked emptiness, hide the popup
    if (!element)
    {
        showPopup(false);
        return;
    }
    
    // Otherwise see if the clicked element has either the menu item or the popup in its parent chain.
    // In that case, do not hide
    while (element)
    {
        if ((element == this) || (element == mPopup))
            return;
        if (element->getParent() == root)
            element = static_cast<UIElement*>(element->getUserData()[originHash].getPtr());
        else
            element = element->getParent();
    }
    
    showPopup(false);
}

void Menu::handleKeyDown(StringHash eventType, VariantMap& eventData)
{
    if ((!mEnabled) || (!mVisible))
        return;
    
    using namespace KeyDown;
    
    // Simulate a click if accelerator key pressed
    if ((eventData[P_KEY].getInt() == mAcceleratorKey) && (eventData[P_QUALIFIERS].getInt() == mAcceleratorQualifiers) &&
        (eventData[P_REPEAT].getBool() == false))
        onClick(getPosition(), getScreenPosition(), eventData[P_BUTTONS].getInt(), eventData[P_QUALIFIERS].getInt(), 0);
}
