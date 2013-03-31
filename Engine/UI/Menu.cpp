//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Log.h"
#include "Menu.h"
#include "UIEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

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
        ShowPopup(false);
}

void Menu::RegisterObject(Context* context)
{
    context->RegisterFactory<Menu>();
    
    REF_ACCESSOR_ATTRIBUTE(Menu, VAR_INTVECTOR2, "Popup Offset", GetPopupOffset, SetPopupOffset, IntVector2, IntVector2::ZERO, AM_FILE);
    COPY_BASE_ATTRIBUTES(Menu, Button);
}

void Menu::OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    Button::OnHover(position, screenPosition, buttons, qualifiers, cursor);
    if (popup_ && !showPopup_)
    {
        // Check if popup is shown by one of the siblings
        Vector<SharedPtr<UIElement> > children = GetParent()->GetChildren();
        for (Vector<SharedPtr<UIElement> >::ConstIterator i = children.Begin(); i != children.End(); ++i)
        {
            if ((*i) != this && (*i)->GetType() == Menu::GetTypeStatic())
            {
                Menu* sibling = static_cast<Menu*>(i->Get());
                if (sibling->showPopup_)
                {
                    // "Move" the popup from sibling menu to this menu
                    sibling->ShowPopup(false);
                    ShowPopup(true);
                    return;
                }
            }
        }
    }
}
    
void Menu::OnShowPopup()
{
}

bool Menu::LoadXML(const XMLElement& source, XMLFile* styleFile)
{
    // Apply the style first, but only for non-internal elements
    if (!internal_ && styleFile)
    {
        // Use style override if defined, otherwise type name
        String styleName = source.GetAttribute("style");
        if (styleName.Empty())
            styleName = GetTypeName();
        
        SetStyle(styleFile, styleName);
    }
    
    // Then load rest of the attributes from the source
    if (!Serializable::LoadXML(source))
        return false;
    
    unsigned nextInternalChild = 0;
    
    // Load child elements. Internal elements are not to be created as they already exist
    XMLElement childElem = source.GetChild("element");
    while (childElem)
    {
        bool internalElem = childElem.GetBool("internal");
        bool popupElem = childElem.GetBool("popup");
        String typeName = childElem.GetAttribute("type");
        if (typeName.Empty())
            typeName = "UIElement";
        UIElement* child = 0;
        
        if (!internalElem)
        {
            if (!popupElem)
                child = CreateChild(typeName);
            else
            {
                // Do not add the popup element as a child even temporarily, as that can break layouts
                SharedPtr<UIElement> popup = DynamicCast<UIElement>(context_->CreateObject(typeName));
                if (!popup)
                    LOGERROR("Could not create popup element type " + ShortStringHash(typeName).ToString());
                else
                {
                    child = popup;
                    SetPopup(popup);
                }
            }
        }
        else
        {
            // An internal popup element should already exist
            if (popupElem)
                child = popup_;
            else
            {
                for (unsigned i = nextInternalChild; i < children_.Size(); ++i)
                {
                    if (children_[i]->IsInternal() && children_[i]->GetTypeName() == typeName)
                    {
                        child = children_[i];
                        nextInternalChild = i + 1;
                        break;
                    }
                }
                
                if (!child)
                    LOGWARNING("Could not find matching internal child element of type " + typeName + " in " + GetTypeName());
            }
        }
        
        if (child)
        {
            if (!child->LoadXML(childElem, styleFile))
                return false;
        }
        
        childElem = childElem.GetNext("element");
    }
    
    ApplyAttributes();
    
    return true;
}

bool Menu::SaveXML(XMLElement& dest)
{
    // Write type and internal flag
    if (!dest.SetString("type", GetTypeName()))
        return false;
    if (internal_)
    {
        if (!dest.SetBool("internal", internal_))
            return false;
    }
    
    // Write attributes
    if (!Serializable::SaveXML(dest))
        return false;
    
    // Write child elements
    for (unsigned i = 0; i < children_.Size(); ++i)
    {
        UIElement* element = children_[i];
        XMLElement childElem = dest.CreateChild("element");
        if (!element->SaveXML(childElem))
            return false;
    }
    
    // Save the popup element as a "virtual" child element
    if (popup_)
    {
        XMLElement childElem = dest.CreateChild("element");
        childElem.SetBool("popup", true);
        if (!popup_->SaveXML(childElem))
            return false;
    }
    
    return true;
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
        popup_->Remove();
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
    
    if (enable)
    {
        // Find the UI root element for showing the popup
        UIElement* root = GetRoot();
        if (!root)
            return;
        
        OnShowPopup();
        
        if (popup_->GetParent() != root)
            root->AddChild(popup_);
        popup_->SetPosition(GetScreenPosition() + popupOffset_);
        popup_->SetVisible(true);
        popup_->SetVar(originHash, (void*)this);
        popup_->BringToFront();
    }
    else
    {
        // If the popup has child menus, hide their popups as well
        PODVector<UIElement*> children;
        popup_->GetChildren(children, true);
        for (PODVector<UIElement*>::ConstIterator i = children.Begin(); i != children.End(); ++i)
        {
            Menu* menu = dynamic_cast<Menu*>(*i);
            if (menu)
                menu->ShowPopup(false);
        }
        
        popup_->SetVar(originHash, Variant::EMPTY);
        popup_->SetVisible(false);
        popup_->Remove();
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
    UIElement* root = GetRoot();
    
    // If another element was focused due to the menu button being clicked, do not hide the popup
    if (eventType == E_FOCUSCHANGED && static_cast<UIElement*>(eventData[P_CLICKEDELEMENT].GetPtr()))
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
            element = static_cast<UIElement*>(element->GetVar(originHash).GetPtr());
        else
            element = element->GetParent();
    }
    
    ShowPopup(false);
}

void Menu::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    if (!enabled_)
        return;
    
    using namespace KeyDown;
    
    // Activate if accelerator key pressed
    if (eventData[P_KEY].GetInt() == acceleratorKey_ && (acceleratorQualifiers_ == QUAL_ANY || eventData[P_QUALIFIERS].GetInt() ==
        acceleratorQualifiers_) && eventData[P_REPEAT].GetBool() == false)
        HandlePressedReleased(eventType, eventData);
}

}
