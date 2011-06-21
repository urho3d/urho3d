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
#include "Context.h"
#include "InputEvents.h"
#include "Menu.h"
#include "UIEvents.h"

#include "DebugNew.h"

static const ShortStringHash originHash("Origin");

OBJECTTYPESTATIC(Menu);

Menu::Menu(Context* context) :
    Button(context),
    popupOffset_(IntVector2::ZERO),
    showPopup_(false),
    acceleratorKey_(0),
    acceleratorQualifiers_(0)
{
    SubscribeToEvent(this, E_PRESSED, HANDLER(Menu, HandlePressedReleased));
    SubscribeToEvent(this, E_RELEASED, HANDLER(Menu, HandlePressedReleased));
    SubscribeToEvent(E_UIMOUSECLICK, HANDLER(Menu, HandleFocusChanged));
    SubscribeToEvent(E_FOCUSCHANGED, HANDLER(Menu, HandleFocusChanged));
}

Menu::~Menu()
{
    if (popup_)
    {
        ShowPopup(false);
        
        // Make sure the popup is removed from hierarchy if still visible
        UIElement* parent = popup_->GetParent();
        if (parent)
        {
            popup_->vars_[originHash].Clear();
            parent->RemoveChild(popup_);
        }
    }
}

void Menu::RegisterObject(Context* context)
{
    context->RegisterFactory<Menu>();
}

void Menu::SetStyle(const XMLElement& element)
{
    Button::SetStyle(element);
    
    XMLElement popupElem = element.GetChildElement("popup");
    if (popupElem && popupElem.HasAttribute("name"))
    {
        UIElement* root = GetRootElement();
        if (root)
            SetPopup(root->GetChild(popupElem.GetString("name"), true));
    }
    
    if (element.HasChildElement("popupoffset"))
        SetPopupOffset(element.GetChildElement("popupoffset").GetIntVector2("value"));
}

void Menu::OnShowPopup()
{
}

void Menu::SetPopup(UIElement* popup)
{
    if (popup == this)
        return;
    
    if (popup_ && !popup)
        ShowPopup(false);
    
    popup_ = popup;
    
    // Detach from current parent (if any) to only show when it is time
    if (popup_)
    {
        UIElement* parent = popup_->GetParent();
        if (parent)
            parent->RemoveChild(popup_);
    }
}

void Menu::SetPopupOffset(const IntVector2& offset)
{
    popupOffset_ = offset;
}

void Menu::SetPopupOffset(int x, int y)
{
    popupOffset_ = IntVector2(x, y);
}

void Menu::ShowPopup(bool enable)
{
    if (!popup_)
        return;
    
    // Find the UI root element for showing the popup
    UIElement* root = GetRootElement();
    if (!root)
        return;
    
    if (enable)
    {
        OnShowPopup();
        
        popup_->SetPosition(GetScreenPosition() + popupOffset_);
        popup_->SetVisible(true);
        popup_->vars_[originHash] = (void*)this;
        root->AddChild(popup_);
        
        // Set fixed high priority
        popup_->SetBringToFront(false);
        popup_->SetBringToBack(false);
        popup_->BringToFront();
    }
    else
    {
        popup_->vars_[originHash].Clear();
        root->RemoveChild(popup_);
    }
    
    showPopup_ = enable;
    selected_ = enable;
}

void Menu::SetAccelerator(int key, int qualifiers)
{
    acceleratorKey_ = key;
    acceleratorQualifiers_ = qualifiers;
    
    if (key)
        SubscribeToEvent(E_KEYDOWN, HANDLER(Menu, HandleKeyDown));
    else
        UnsubscribeFromEvent(E_KEYDOWN);
}

void Menu::HandlePressedReleased(StringHash eventType, VariantMap& eventData)
{
    // If this menu shows a sublevel popup, react to button press. Else react to release
    if (eventType == E_PRESSED)
    {
        if (!popup_)
            return;
    }
    if (eventType == E_RELEASED)
    {
        if (popup_)
            return;
    }
    
    // Toggle popup visibility if exists
    ShowPopup(!showPopup_);
    
    // Send event on each click if no popup, or whenever the popup is opened
    if (!popup_ || showPopup_)
    {
        using namespace MenuSelected;
        
        VariantMap newEventData;
        newEventData[P_ELEMENT] = (void*)this;
        SendEvent(E_MENUSELECTED, newEventData);
    }
}

void Menu::HandleFocusChanged(StringHash eventType, VariantMap& eventData)
{
    if (!showPopup_)
        return;
    
    using namespace FocusChanged;
    
    UIElement* element = static_cast<UIElement*>(eventData[P_ELEMENT].GetPtr());
    UIElement* root = GetRootElement();
    
    // If another element was focused due to the menu button being clicked, do not hide the popup
    if (eventType == E_FOCUSCHANGED && static_cast<UIElement*>(eventData[P_ORIGINALELEMENT].GetPtr()))
        return;
    
    // If clicked emptiness or defocused, hide the popup
    if (!element)
    {
        ShowPopup(false);
        return;
    }
    
    // Otherwise see if the clicked element has either the menu item or the popup in its parent chain.
    // In that case, do not hide
    while (element)
    {
        if (element == this || element == popup_)
            return;
        if (element->GetParent() == root)
            element = static_cast<UIElement*>(element->vars_[originHash].GetPtr());
        else
            element = element->GetParent();
    }
    
    ShowPopup(false);
}

void Menu::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    if (!active_)
        return;
    
    using namespace KeyDown;
    
    // Activate if accelerator key pressed
    if (eventData[P_KEY].GetInt() == acceleratorKey_ && eventData[P_QUALIFIERS].GetInt() == acceleratorQualifiers_ &&
        eventData[P_REPEAT].GetBool() == false)
        HandlePressedReleased(eventType, eventData);
}
