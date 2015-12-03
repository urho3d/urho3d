//
// Copyright (c) 2008-2015 the Urho3D project.
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
#include "../UI/DropDownList.h"
#include "../UI/ListView.h"
#include "../UI/Text.h"
#include "../UI/UI.h"
#include "../UI/UIEvents.h"
#include "../UI/Window.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* UI_CATEGORY;

DropDownList::DropDownList(Context* context) :
    Menu(context),
    resizePopup_(false),
    selectionAttr_(0)
{
    focusMode_ = FM_FOCUSABLE_DEFOCUSABLE;

    Window* window = new Window(context_);
    window->SetInternal(true);
    SetPopup(window);

    listView_ = new ListView(context_);
    listView_->SetInternal(true);
    listView_->SetScrollBarsVisible(false, false);
    popup_->SetLayout(LM_VERTICAL);
    popup_->AddChild(listView_);
    placeholder_ = CreateChild<UIElement>("DDL_Placeholder");
    placeholder_->SetInternal(true);
    Text* text = placeholder_->CreateChild<Text>("DDL_Placeholder_Text");
    text->SetInternal(true);
    text->SetVisible(false);

    SubscribeToEvent(listView_, E_ITEMCLICKED, URHO3D_HANDLER(DropDownList, HandleItemClicked));
    SubscribeToEvent(listView_, E_UNHANDLEDKEY, URHO3D_HANDLER(DropDownList, HandleListViewKey));
    SubscribeToEvent(listView_, E_SELECTIONCHANGED, URHO3D_HANDLER(DropDownList, HandleSelectionChanged));
}

DropDownList::~DropDownList()
{
}

void DropDownList::RegisterObject(Context* context)
{
    context->RegisterFactory<DropDownList>(UI_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(Menu);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Focus Mode", FM_FOCUSABLE_DEFOCUSABLE);
    URHO3D_ACCESSOR_ATTRIBUTE("Selection", GetSelection, SetSelectionAttr, unsigned, 0, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Resize Popup", GetResizePopup, SetResizePopup, bool, false, AM_FILE);
}

void DropDownList::ApplyAttributes()
{
    // Reapply selection after possible items have been loaded
    SetSelection(selectionAttr_);
}

void DropDownList::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    Menu::GetBatches(batches, vertexData, currentScissor);

    if (!placeholder_->IsVisible())
        return;

    UIElement* selectedItem = GetSelectedItem();
    if (selectedItem)
    {
        // Can not easily copy the selected item. However, it can be re-rendered on the placeholder's position
        const IntVector2& targetPos = placeholder_->GetScreenPosition();
        const IntVector2& originalPos = selectedItem->GetScreenPosition();
        IntVector2 offset = targetPos - originalPos;

        // GetBatches() usually resets the hover flag. Therefore get its value and then reset it for the real rendering
        // Render the selected item without its selection color, so temporarily reset the item's selected attribute
        bool hover = selectedItem->IsHovering();
        selectedItem->SetSelected(false);
        selectedItem->SetHovering(false);
        selectedItem->GetBatchesWithOffset(offset, batches, vertexData, currentScissor);
        selectedItem->SetSelected(true);
        selectedItem->SetHovering(hover);
    }
}

void DropDownList::OnShowPopup()
{
    // Resize the popup to match the size of the list content, and optionally match the button width
    UIElement* content = listView_->GetContentElement();
    content->UpdateLayout();
    const IntVector2& contentSize = content->GetSize();
    const IntRect& border = popup_->GetLayoutBorder();
    popup_->SetSize(resizePopup_ ? GetWidth() : contentSize.x_ + border.left_ + border.right_,
        contentSize.y_ + border.top_ + border.bottom_);

    // Check if popup fits below the button. If not, show above instead
    bool showAbove = false;
    UIElement* root = GetRoot();
    if (root)
    {
        const IntVector2& screenPos = GetScreenPosition();
        if (screenPos.y_ + GetHeight() + popup_->GetHeight() > root->GetHeight() && screenPos.y_ - popup_->GetHeight() >= 0)
            showAbove = true;
    }
    SetPopupOffset(0, showAbove ? -popup_->GetHeight() : GetHeight());

    // Focus the ListView to allow making the selection with keys
    GetSubsystem<UI>()->SetFocusElement(listView_);
}

void DropDownList::OnHidePopup()
{
    // When the popup is hidden, propagate the selection
    using namespace ItemSelected;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_ELEMENT] = this;
    eventData[P_SELECTION] = GetSelection();
    SendEvent(E_ITEMSELECTED, eventData);
}

void DropDownList::OnSetEditable()
{
    listView_->SetEditable(editable_);
}

void DropDownList::AddItem(UIElement* item)
{
    InsertItem(M_MAX_UNSIGNED, item);
}

void DropDownList::InsertItem(unsigned index, UIElement* item)
{
    listView_->InsertItem(index, item);

    // If there was no selection, set to the first
    if (GetSelection() == M_MAX_UNSIGNED)
        SetSelection(0);
}

void DropDownList::RemoveItem(UIElement* item)
{
    listView_->RemoveItem(item);
}

void DropDownList::RemoveItem(unsigned index)
{
    listView_->RemoveItem(index);
}

void DropDownList::RemoveAllItems()
{
    listView_->RemoveAllItems();
}

void DropDownList::SetSelection(unsigned index)
{
    listView_->SetSelection(index);
}

void DropDownList::SetPlaceholderText(const String& text)
{
    static_cast<Text*>(placeholder_->GetChild(0))->SetText(text);
}

void DropDownList::SetResizePopup(bool enable)
{
    resizePopup_ = enable;
}

unsigned DropDownList::GetNumItems() const
{
    return listView_->GetNumItems();
}

UIElement* DropDownList::GetItem(unsigned index) const
{
    return listView_->GetItem(index);
}

PODVector<UIElement*> DropDownList::GetItems() const
{
    return listView_->GetItems();
}

unsigned DropDownList::GetSelection() const
{
    return listView_->GetSelection();
}

UIElement* DropDownList::GetSelectedItem() const
{
    return listView_->GetSelectedItem();
}

const String& DropDownList::GetPlaceholderText() const
{
    return static_cast<Text*>(placeholder_->GetChild(0))->GetText();
}

void DropDownList::SetSelectionAttr(unsigned index)
{
    selectionAttr_ = index;

    // We may not have the list items yet. Apply the index again in ApplyAttributes().
    SetSelection(index);
}

bool DropDownList::FilterImplicitAttributes(XMLElement& dest) const
{
    if (!Menu::FilterImplicitAttributes(dest))
        return false;

    if (!RemoveChildXML(dest, "Popup Offset"))
        return false;

    XMLElement childElem = dest.GetChild("element");
    if (!childElem)
        return false;
    if (!RemoveChildXML(childElem, "Name", "DDL_Placeholder"))
        return false;
    if (!RemoveChildXML(childElem, "Size"))
        return false;

    childElem = childElem.GetChild("element");
    if (!childElem)
        return false;
    if (!RemoveChildXML(childElem, "Name", "DDL_Placeholder_Text"))
        return false;
    if (!RemoveChildXML(childElem, "Is Visible"))
        return false;

    return true;
}

bool DropDownList::FilterPopupImplicitAttributes(XMLElement& dest) const
{
    if (!Menu::FilterPopupImplicitAttributes(dest))
        return false;

    // Window popup
    if (dest.GetAttribute("style").Empty() && !dest.SetAttribute("style", "none"))
        return false;
    if (!RemoveChildXML(dest, "Layout Mode", "Vertical"))
        return false;
    if (!RemoveChildXML(dest, "Size"))
        return false;

    // ListView
    XMLElement childElem = dest.GetChild("element");
    if (!childElem)
        return false;
    if (!listView_->FilterAttributes(childElem))
        return false;
    if (childElem.GetAttribute("style").Empty() && !childElem.SetAttribute("style", "none"))
        return false;
    if (!RemoveChildXML(childElem, "Focus Mode", "NotFocusable"))
        return false;
    if (!RemoveChildXML(childElem, "Auto Show/Hide Scrollbars", "false"))
        return false;

    // Horizontal scroll bar
    childElem = childElem.GetChild("element");
    if (childElem && !childElem.GetParent().RemoveChild(childElem))
        return false;

    // Vertical scroll bar
    childElem = childElem.GetNext("element");
    if (childElem && !childElem.GetParent().RemoveChild(childElem))
        return false;

    // Scroll panel
    childElem = childElem.GetNext("element");
    if (!childElem)
        return false;
    if (childElem.GetAttribute("style").Empty() && !childElem.SetAttribute("style", "none"))
        return false;

    // Item container
    childElem = childElem.GetChild("element");
    if (!childElem)
        return false;
    if (childElem.GetAttribute("style").Empty() && !childElem.SetAttribute("style", "none"))
        return false;

    return true;
}

void DropDownList::HandleItemClicked(StringHash eventType, VariantMap& eventData)
{
    // Resize the selection placeholder to match the selected item
    UIElement* selectedItem = GetSelectedItem();
    if (selectedItem)
        placeholder_->SetSize(selectedItem->GetSize());

    // Close and defocus the popup. This will actually send the selection forward
    if (listView_->HasFocus())
        GetSubsystem<UI>()->SetFocusElement(focusMode_ < FM_FOCUSABLE ? 0 : this);
    ShowPopup(false);
}

void DropDownList::HandleListViewKey(StringHash eventType, VariantMap& eventData)
{
    using namespace UnhandledKey;

    // If enter pressed in the list view, close and propagate selection
    int key = eventData[P_KEY].GetInt();
    if (key == KEY_RETURN || key == KEY_RETURN2 || key == KEY_KP_ENTER)
        HandleItemClicked(eventType, eventData);
}

void DropDownList::HandleSelectionChanged(StringHash eventType, VariantMap& eventData)
{
    // Display the place holder text when there is no selection, however, the place holder text is only visible when the place holder itself is set to visible
    placeholder_->GetChild(0)->SetVisible(GetSelection() == M_MAX_UNSIGNED);
}

}
