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

Menu::Menu(const std::string& name) :
    Button(name),
    mPopupOffset(IntVector2::sZero),
    mShowPopup(false)
{
    subscribeToEvent(EVENT_TRYFOCUS, EVENT_HANDLER(Menu, handleTryFocus));
}

Menu::~Menu()
{
    if (mPopup)
        mPopup->setOrigin(0);
}

void Menu::setStyle(const XMLElement& element, ResourceCache* cache)
{
    Button::setStyle(element, cache);
    
    XMLElement popupElem = element.getChildElement("popup");
    if ((popupElem) && (popupElem.hasAttribute("name")))
    {
        UIElement* root = getRootElement();
        if (root)
            setPopup(root->getChild(element.getChildElement("popup").getString("name"), true));
    }
    
    if (element.hasChildElement("popupoffset"))
        setPopupOffset(element.getChildElement("popupoffset").getIntVector2("value"));
}

void Menu::onClick(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers)
{
    setPressed(true);
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
    
    // Find the UI root element for showing the popup
    UIElement* root = getRootElement();
    if (!root)
        return;
    
    if (enable)
    {
        onShowPopup();
        
        mPopup->setPosition(getScreenPosition() + mPopupOffset);
        mPopup->setVisible(true);
        mPopup->setOrigin(this);
        root->addChild(mPopup);
        
        // Set fixed high priority
        mPopup->setBringToFront(false);
        mPopup->setBringToBack(false);
        mPopup->bringToFront();
    }
    else
    {
        mPopup->setOrigin(0);
        root->removeChild(mPopup);
    }
    
    mShowPopup = enable;
    mSelected = enable;
}

void Menu::handleTryFocus(StringHash eventType, VariantMap& eventData)
{
    if (!mShowPopup)
        return;
    
    using namespace TryFocus;
    
    UIElement* focusElement = static_cast<UIElement*>(eventData[P_ELEMENT].getPtr());
    UIElement* root = getRootElement();
    
    // If global defocus, hide the popup
    if (!focusElement)
    {
        showPopup(false);
        return;
    }
    
    // Otherwise see if the focused element has either the menu item or the popup in its parent chain.
    // In that case, do not hide
    while (focusElement)
    {
        if ((focusElement == this) || (focusElement == mPopup))
            return;
        if (focusElement->getParent() == root)
            focusElement = focusElement->getOrigin();
        else
            focusElement = focusElement->getParent();
    }
    
    showPopup(false);
}
