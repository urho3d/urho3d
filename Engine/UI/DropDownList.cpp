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
#include "DropDownList.h"
#include "ListView.h"
#include "UIEvents.h"
#include "Window.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(DropDownList);

DropDownList::DropDownList(Context* context) :
    Menu(context),
    resizePopup_(false)
{
    Window* window = new Window(context_);
    SetPopup(window);
    
    listView_ = new ListView(context_);
    listView_->SetScrollBarsVisible(false, false);
    listView_->SetFocusMode(FM_NOTFOCUSABLE);
    popup_->SetLayout(LM_VERTICAL);
    popup_->AddChild(listView_);
    placeholder_ = new UIElement(context_);
    AddChild(placeholder_);
    
    SubscribeToEvent(listView_, E_ITEMSELECTED, HANDLER(DropDownList, HandleItemSelected));
}

DropDownList::~DropDownList()
{
}

void DropDownList::RegisterObject(Context* context)
{
    context->RegisterFactory<DropDownList>();
}

void DropDownList::SetStyle(const XMLElement& element)
{
    Menu::SetStyle(element);
    
    XMLElement listElem = element.GetChild("listview");
    if (listElem)
        listView_->SetStyle(listElem);
    
    XMLElement popupElem = element.GetChild("popup");
    if (popupElem)
        popup_->SetStyle(popupElem);
    
    XMLElement placeholderElem = element.GetChild("placeholder");
    if (placeholderElem)
        placeholder_->SetStyle(placeholderElem);
    
    UIElement* root = GetRoot();
    XMLElement itemElem = element.GetChild("popupitem");
    if (root)
    {
        while (itemElem)
        {
            if (itemElem.HasAttribute("name"))
                AddItem(root->GetChild(itemElem.GetString("name"), true));
            itemElem = itemElem.GetNext("popupitem");
        }
    }
    
    if (element.HasChild("selection"))
        SetSelection(element.GetChild("selection").GetInt("value"));
    if (element.HasChild("resizepopup"))
        SetResizePopup(element.GetChild("resizepopup").GetBool("enable"));
}

void DropDownList::GetBatches(PODVector<UIBatch>& batches, PODVector<UIQuad>& quads, const IntRect& currentScissor)
{
    Button::GetBatches(batches, quads, currentScissor);
    
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
        bool hover = selectedItem->IsHovering();
        selectedItem->SetHovering(false);
        selectedItem->GetBatchesWithOffset(offset, batches, quads, currentScissor);
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
    popup_->SetSize(resizePopup_ ? GetWidth() : contentSize.x_ + border.left_ + border.right_, contentSize.y_ + border.top_ + 
        border.bottom_);
    
    // Check if popup fits below the button. If not, show above instead
    bool showAbove = false;
    UIElement* root = GetRoot();
    if (root)
    {
        const IntVector2& screenPos = GetScreenPosition();
        if (screenPos.y_ + GetHeight() + popup_->GetHeight() > root->GetHeight() && screenPos.y_ - popup_->GetHeight() >= 0)
            showAbove = true;
    }
    if (!showAbove)
        SetPopupOffset(0, GetHeight());
    else
        SetPopupOffset(0, -popup_->GetHeight());
}

void DropDownList::AddItem(UIElement* item)
{
    InsertItem(listView_->GetNumItems(), item);
}

void DropDownList::InsertItem(unsigned index, UIElement* item)
{
    listView_->InsertItem(index, item);
    
    // If there was no selection, set to the first
    if (listView_->GetSelection() == M_MAX_UNSIGNED)
        listView_->SetSelection(0);
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
    return listView_->GetContentElement()->GetChildren();
}

unsigned DropDownList::GetSelection() const
{
    return listView_->GetSelection();
}

UIElement* DropDownList::GetSelectedItem() const
{
    return listView_->GetSelectedItem();
}

void DropDownList::HandleItemSelected(StringHash eventType, VariantMap& eventData)
{
    // Resize the selection placeholder to match the selected item
    UIElement* selectedItem = GetSelectedItem();
    if (selectedItem)
        placeholder_->SetSize(selectedItem->GetSize());
    
    // Close the popup as the selection was made
    if (GetShowPopup())
        ShowPopup(false);
    
    // Send the event forward
    using namespace Iteselected_;
    
    VariantMap newEventData;
    newEventData[P_ELEMENT] = (void*)this;
    newEventData[P_SELECTION] = GetSelection();
    SendEvent(E_ITEMSELECTED, newEventData);
}
