//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

namespace Urho3D
{

OBJECTTYPESTATIC(DropDownList);

DropDownList::DropDownList(Context* context) :
    Menu(context),
    resizePopup_(false),
    selectionAttr_(0)
{
    Window* window = new Window(context_);
    window->SetInternal(true);
    SetPopup(window);
    
    listView_ = new ListView(context_);
    listView_->SetInternal(true);
    listView_->SetScrollBarsVisible(false, false);
    listView_->SetFocusMode(FM_NOTFOCUSABLE);
    popup_->SetLayout(LM_VERTICAL);
    popup_->AddChild(listView_);
    placeholder_ = CreateChild<UIElement>();
    placeholder_->SetInternal(true);
    
    SubscribeToEvent(listView_, E_ITEMSELECTED, HANDLER(DropDownList, HandleItemSelected));
}

DropDownList::~DropDownList()
{
}

void DropDownList::RegisterObject(Context* context)
{
    context->RegisterFactory<DropDownList>();
    
    COPY_BASE_ATTRIBUTES(DropDownList, Menu);
    ACCESSOR_ATTRIBUTE(DropDownList, VAR_INT, "Selection", GetSelection, SetSelectionAttr, unsigned, 0, AM_FILE);
    ACCESSOR_ATTRIBUTE(DropDownList, VAR_BOOL, "Resize Popup", GetResizePopup, SetResizePopup, bool, false, AM_FILE);
}

void DropDownList::ApplyAttributes()
{
    // Reapply selection after possible items have been loaded
    SetSelection(selectionAttr_);
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
    PODVector<UIElement*> items;
    listView_->GetContentElement()->GetChildren(items);
    return items;
}

unsigned DropDownList::GetSelection() const
{
    return listView_->GetSelection();
}

UIElement* DropDownList::GetSelectedItem() const
{
    return listView_->GetSelectedItem();
}

void DropDownList::SetSelectionAttr(unsigned index)
{
    selectionAttr_ = index;
    
    // We may not have the list items yet. Apply the index again in ApplyAttributes().
    SetSelection(index);
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
    using namespace ItemSelected;
    
    VariantMap newEventData;
    newEventData[P_ELEMENT] = (void*)this;
    newEventData[P_SELECTION] = GetSelection();
    SendEvent(E_ITEMSELECTED, newEventData);
}

}
