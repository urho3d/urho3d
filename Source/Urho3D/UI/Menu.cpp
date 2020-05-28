//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Input/InputEvents.h"
#include "../IO/Log.h"
#include "../UI/LineEdit.h"
#include "../UI/Menu.h"
#include "../UI/UI.h"
#include "../UI/UIEvents.h"
#include "../UI/Window.h"

#include "../DebugNew.h"

namespace Urho3D
{

const StringHash VAR_SHOW_POPUP("ShowPopup");
extern StringHash VAR_ORIGIN;

extern const char* UI_CATEGORY;

Menu::Menu(Context* context) :
    Button(context),
    popupOffset_(IntVector2::ZERO),
    showPopup_(false),
    acceleratorKey_(0),
    acceleratorQualifiers_(0),
    autoPopup_(true)
{
    focusMode_ = FM_NOTFOCUSABLE;

    SubscribeToEvent(this, E_PRESSED, URHO3D_HANDLER(Menu, HandlePressedReleased));
    SubscribeToEvent(this, E_RELEASED, URHO3D_HANDLER(Menu, HandlePressedReleased));
    SubscribeToEvent(E_UIMOUSECLICK, URHO3D_HANDLER(Menu, HandleFocusChanged));
    SubscribeToEvent(E_FOCUSCHANGED, URHO3D_HANDLER(Menu, HandleFocusChanged));
}

Menu::~Menu()
{
    if (popup_ && showPopup_)
        ShowPopup(false);
}

void Menu::RegisterObject(Context* context)
{
    context->RegisterFactory<Menu>(UI_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(Button);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Focus Mode", FM_NOTFOCUSABLE);
    URHO3D_ACCESSOR_ATTRIBUTE("Popup Offset", GetPopupOffset, SetPopupOffset, IntVector2, IntVector2::ZERO, AM_FILE);
}

void Menu::Update(float timeStep)
{
    Button::Update(timeStep);

    if (popup_ && showPopup_)
    {
        const Vector<SharedPtr<UIElement> >& children = popup_->GetChildren();
        for (unsigned i = 0; i < children.Size(); ++i)
        {
            auto* menu = dynamic_cast<Menu*>(children[i].Get());
            if (menu && !menu->autoPopup_ && !menu->IsHovering())
                menu->autoPopup_ = true;
        }
    }
}

void Menu::OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    Button::OnHover(position, screenPosition, buttons, qualifiers, cursor);

    auto* sibling = parent_->GetChildStaticCast<Menu>(VAR_SHOW_POPUP, true);
    if (popup_ && !showPopup_)
    {
        // Check if popup is shown by one of the siblings
        if (sibling)
        {
            // "Move" the popup from sibling menu to this menu
            sibling->ShowPopup(false);
            ShowPopup(true);
            return;
        }

        if (autoPopup_)
        {
            // Show popup when parent menu has its popup shown
            auto* parentMenu = static_cast<Menu*>(parent_->GetVar(VAR_ORIGIN).GetPtr());
            if (parentMenu && parentMenu->showPopup_)
                ShowPopup(true);
        }
    }
    else
    {
        // Hide child menu popup when its parent is no longer being hovered
        if (sibling && sibling != this)
            sibling->ShowPopup(false);
    }
}

void Menu::OnShowPopup()
{
}

bool Menu::LoadXML(const XMLElement& source, XMLFile* styleFile)
{
    // Get style override if defined
    String styleName = source.GetAttribute("style");

    // Apply the style first, if the style file is available
    if (styleFile)
    {
        // If not defined, use type name
        if (styleName.Empty())
            styleName = GetTypeName();

        SetStyle(styleName, styleFile);
    }
    // The 'style' attribute value in the style file cannot be equals to original's applied style to prevent infinite loop
    else if (!styleName.Empty() && styleName != appliedStyle_)
    {
        // Attempt to use the default style file
        styleFile = GetDefaultStyle();

        if (styleFile)
        {
            // Remember the original applied style
            String appliedStyle(appliedStyle_);
            SetStyle(styleName, styleFile);
            appliedStyle_ = appliedStyle;
        }
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
        unsigned index = childElem.HasAttribute("index") ? childElem.GetUInt("index") : M_MAX_UNSIGNED;
        UIElement* child = nullptr;

        if (!internalElem)
        {
            if (!popupElem)
                child = CreateChild(typeName, String::EMPTY, index);
            else
            {
                // Do not add the popup element as a child even temporarily, as that can break layouts
                SharedPtr<UIElement> popup = DynamicCast<UIElement>(context_->CreateObject(typeName));
                if (!popup)
                    URHO3D_LOGERROR("Could not create popup element type " + typeName);
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
                    URHO3D_LOGWARNING("Could not find matching internal child element of type " + typeName + " in " + GetTypeName());
            }
        }

        if (child)
        {
            if (!styleFile)
                styleFile = GetDefaultStyle();

            // As popup is not a child element in itself, the parental chain to acquire the default style file is broken for popup's child elements
            // To recover from this, popup needs to have the default style set in its own instance so the popup's child elements can find it later
            if (popupElem)
                child->SetDefaultStyle(styleFile);

            if (!child->LoadXML(childElem, styleFile))
                return false;
        }

        childElem = childElem.GetNext("element");
    }

    ApplyAttributes();

    return true;
}

bool Menu::SaveXML(XMLElement& dest) const
{
    if (!Button::SaveXML(dest))
        return false;

    // Save the popup element as a "virtual" child element
    if (popup_)
    {
        XMLElement childElem = dest.CreateChild("element");
        childElem.SetBool("popup", true);
        if (!popup_->SaveXML(childElem))
            return false;

        // Filter popup implicit attributes
        if (!FilterPopupImplicitAttributes(childElem))
        {
            URHO3D_LOGERROR("Could not remove popup implicit attributes");
            return false;
        }
    }

    return true;
}

void Menu::SetPopup(UIElement* popup)
{
    if (popup == this)
        return;

    // Currently only allow popup 'window'
    if (popup->GetType() != Window::GetTypeStatic())
    {
        URHO3D_LOGERROR("Could not set popup element of type " + popup->GetTypeName() + ", only support popup window for now");
        return;
    }

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
        OnShowPopup();

        popup_->SetVar(VAR_ORIGIN, this);
        static_cast<Window*>(popup_.Get())->SetModal(true);

        popup_->SetPosition(GetScreenPosition() + popupOffset_);
        popup_->SetVisible(true);
        // BringToFront() is unreliable in this case as it takes into account only input-enabled elements.
        // Rather just force priority to max
        popup_->SetPriority(M_MAX_INT);
    }
    else
    {
        OnHidePopup();

        // If the popup has child menus, hide their popups as well
        PODVector<UIElement*> children;
        popup_->GetChildren(children, true);
        for (PODVector<UIElement*>::ConstIterator i = children.Begin(); i != children.End(); ++i)
        {
            auto* menu = dynamic_cast<Menu*>(*i);
            if (menu)
                menu->ShowPopup(false);
        }

        static_cast<Window*>(popup_.Get())->SetModal(false);
        const_cast<VariantMap&>(popup_->GetVars()).Erase(VAR_ORIGIN);

        popup_->SetVisible(false);
        popup_->Remove();
    }
    SetVar(VAR_SHOW_POPUP, enable);

    showPopup_ = enable;
    selected_ = enable;
}

void Menu::SetAccelerator(int key, int qualifiers)
{
    acceleratorKey_ = ToLower(key);
    acceleratorQualifiers_ = qualifiers;

    if (key)
        SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(Menu, HandleKeyDown));
    else
        UnsubscribeFromEvent(E_KEYDOWN);
}

bool Menu::FilterPopupImplicitAttributes(XMLElement& dest) const
{
    if (!RemoveChildXML(dest, "Position"))
        return false;
    if (!RemoveChildXML(dest, "Is Visible"))
        return false;

    return true;
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

    // Manual handling of the popup, so switch off the auto popup flag
    autoPopup_ = false;
    // Toggle popup visibility if exists
    ShowPopup(!showPopup_);

    // Send event on each click if no popup, or whenever the popup is opened
    if (!popup_ || showPopup_)
    {
        using namespace MenuSelected;

        VariantMap& newEventData = GetEventDataMap();
        newEventData[P_ELEMENT] = this;
        SendEvent(E_MENUSELECTED, newEventData);
    }
}

void Menu::HandleFocusChanged(StringHash eventType, VariantMap& eventData)
{
    if (!showPopup_)
        return;

    using namespace FocusChanged;

    auto* element = static_cast<UIElement*>(eventData[P_ELEMENT].GetPtr());
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
            element = static_cast<UIElement*>(element->GetVar(VAR_ORIGIN).GetPtr());
        else
            element = element->GetParent();
    }

    ShowPopup(false);
}

void Menu::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    if (!IsInputEnabled())
        return;

    using namespace KeyDown;

    // Activate if accelerator key pressed
    if (eventData[P_KEY].GetInt() == acceleratorKey_ &&
        (acceleratorQualifiers_ == QUAL_ANY || eventData[P_QUALIFIERS].GetInt() == acceleratorQualifiers_) &&
        eventData[P_REPEAT].GetBool() == false)
    {
        // Ignore if UI has modal element or focused LineEdit
        auto* ui = GetSubsystem<UI>();
        UIElement* focusElement = ui->GetFocusElement();
        if (ui->HasModalElement() || (focusElement && focusElement->GetType() == LineEdit::GetTypeStatic()))
            return;

        HandlePressedReleased(eventType, eventData);
    }
}

}
