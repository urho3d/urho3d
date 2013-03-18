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
#include "BorderImage.h"
#include "Context.h"
#include "InputEvents.h"
#include "ListView.h"
#include "Log.h"
#include "Sort.h"
#include "StringUtils.h"
#include "UIEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

static const ShortStringHash indentHash("Indent");
static const ShortStringHash expandedHash("Expanded");

static const char* highlightModes[] =
{
    "Never",
    "Focus",
    "Always",
    ""
};

template<> HighlightMode Variant::Get<HighlightMode>() const
{
    return (HighlightMode)GetInt();
}

int GetItemIndent(UIElement* item)
{
    return item ? item->GetVar(indentHash).GetInt() : 0;
}

bool GetItemExpanded(UIElement* item)
{
    return item ? item->GetVar(expandedHash).GetBool() : true;
}
    
void SetItemExpanded(UIElement* item, bool enable)
{
    item->SetVar(expandedHash, enable);
}

OBJECTTYPESTATIC(ListView);

ListView::ListView(Context* context) :
    ScrollView(context),
    highlightMode_(HM_FOCUS),
    multiselect_(false),
    hierarchyMode_(false),
    clearSelectionOnDefocus_(false),
    doubleClickInterval_(500),
    lastClickedItem_(M_MAX_UNSIGNED)
{
    resizeContentWidth_ = true;
    
    UIElement* container = new UIElement(context_);
    container->SetInternal(true);
    container->SetActive(true);
    container->SetLayout(LM_VERTICAL);
    container->SetSortChildren(false);
    SetContentElement(container);
    
    SubscribeToEvent(E_UIMOUSECLICK, HANDLER(ListView, HandleUIMouseClick));
    SubscribeToEvent(E_FOCUSCHANGED, HANDLER(ListView, HandleFocusChanged));
}

ListView::~ListView()
{
}

void ListView::RegisterObject(Context* context)
{
    context->RegisterFactory<ListView>();
    
    ENUM_ACCESSOR_ATTRIBUTE(ListView, "Highlight Mode", GetHighlightMode, SetHighlightMode, HighlightMode, highlightModes, HM_FOCUS, AM_FILE);
    ACCESSOR_ATTRIBUTE(ListView, VAR_BOOL, "Multiselect", GetMultiselect, SetMultiselect, bool, false, AM_FILE);
    ACCESSOR_ATTRIBUTE(ListView, VAR_BOOL, "Hierarchy Mode", GetHierarchyMode, SetHierarchyMode, bool, false, AM_FILE);
    ACCESSOR_ATTRIBUTE(ListView, VAR_BOOL, "Clear Sel. On Defocus", GetClearSelectionOnDefocus, SetClearSelectionOnDefocus, bool, false, AM_FILE);
    ACCESSOR_ATTRIBUTE(ListView, VAR_FLOAT, "Double Click Interval", GetDoubleClickInterval, SetDoubleClickInterval, float, 0.5f, AM_FILE);
    COPY_BASE_ATTRIBUTES(ListView, ScrollView);
}

void ListView::OnKey(int key, int buttons, int qualifiers)
{
    // If no selection, can not move with keys
    unsigned numItems = GetNumItems();
    unsigned selection = GetSelection();

    // If either shift or ctrl held down, add to selection if multiselect enabled
    bool additive = multiselect_ && qualifiers & (QUAL_SHIFT | QUAL_CTRL);
    int delta = 0;
    int pageDirection = 1;
    
    if (selection != M_MAX_UNSIGNED && numItems)
    {
        switch (key)
        {
        case KEY_LEFT:
        case KEY_RIGHT:
            if (hierarchyMode_)
            {
                Expand(selection, key == KEY_RIGHT);
                return;
            }
            break;
            
        case KEY_RETURN:
        case KEY_RETURN2:
        case KEY_KP_ENTER:
            if (hierarchyMode_)
            {
                ToggleExpand(selection);
                return;
            }
            break;
            
        case KEY_UP:
            delta = -1;
            break;
            
        case KEY_DOWN:
            delta = 1;
            break;
            
        case KEY_PAGEUP:
            pageDirection = -1;
            // Fallthru
            
        case KEY_PAGEDOWN:
            {
                // Convert page step to pixels and see how many items have to be skipped to reach that many pixels
                int stepPixels = ((int)(pageStep_ * scrollPanel_->GetHeight())) - GetSelectedItem()->GetHeight();
                unsigned newSelection = selection;
                unsigned okSelection = selection;
                unsigned invisible = 0;
                while (newSelection < numItems)
                {
                    UIElement* item = GetItem(newSelection);
                    int height = 0;
                    if (item->IsVisible())
                    {
                        height = item->GetHeight();
                        okSelection = newSelection;
                    }
                    else
                        ++invisible;
                    if (stepPixels < height)
                        break;
                    stepPixels -= height;
                    newSelection += pageDirection;
                }
                delta = okSelection - selection - pageDirection * invisible;
            }
            break;
            
        case KEY_HOME:
            delta = -(int)GetNumItems();
            break;
            
        case KEY_END:
            delta = GetNumItems();
            break;
        }
    }
    
    if (delta)
    {
        ChangeSelection(delta, additive);
        return;
    }
    
    using namespace UnhandledKey;
    
    VariantMap eventData;
    eventData[P_ELEMENT] = (void*)this;
    eventData[P_KEY] = key;
    eventData[P_BUTTONS] = buttons;
    eventData[P_QUALIFIERS] = qualifiers;
    SendEvent(E_UNHANDLEDKEY, eventData);
}

void ListView::AddItem(UIElement* item)
{
    InsertItem(contentElement_->GetNumChildren(), item);
}

void ListView::InsertItem(unsigned index, UIElement* item)
{
    if (!item || item->GetParent() == contentElement_)
        return;
    
    // Enable input so that clicking the item can be detected
    item->SetActive(true);
    item->SetSelected(false);
    contentElement_->InsertChild(index, item);
    
    // If necessary, shift the following selections
    if (!selections_.Empty())
    {
        for (unsigned i = 0; i < selections_.Size(); ++i)
        {
            if (selections_[i] >= index)
                ++selections_[i];
        }
        
        UpdateSelectionEffect();
    }
    
    if (hierarchyMode_)
        SetItemExpanded(item, item->IsVisible());
}

void ListView::RemoveItem(UIElement* item, unsigned index)
{
    unsigned numItems = GetNumItems();
    
    for (unsigned i = index; i < numItems; ++i)
    {
        if (GetItem(i) == item)
        {
            item->SetSelected(false);
            selections_.Remove(i);

            // Remove any child items in hierarchy mode
            unsigned removed = 1;
            if (hierarchyMode_)
            {
                int baseIndent = GetItemIndent(item);
                for (unsigned j = i + 1; ; ++j)
                {
                    UIElement* childItem = GetItem(i + 1);
                    if (!childItem)
                        break;
                    if (GetItemIndent(childItem) > baseIndent)
                    {
                        childItem->SetSelected(false);
                        selections_.Erase(j);
                        contentElement_->RemoveChild(childItem, i + 1);
                        ++removed;
                    }
                    else
                        break;
                }
            }

            // If necessary, shift the following selections
            if (!selections_.Empty())
            {
                for (unsigned j = 0; j < selections_.Size(); ++j)
                {
                    if (selections_[j] > i)
                        selections_[j] -= removed;
                }
                
                UpdateSelectionEffect();
            }
            
            contentElement_->RemoveChild(item, i);
            break;
        }
    }
}

void ListView::RemoveItem(unsigned index)
{
    RemoveItem(GetItem(index), index);
}

void ListView::RemoveAllItems()
{
    contentElement_->DisableLayoutUpdate();
    
    ClearSelection();
    contentElement_->RemoveAllChildren();
    
    contentElement_->EnableLayoutUpdate();
    contentElement_->UpdateLayout();
    UpdateViewSize();
}

void ListView::SetSelection(unsigned index)
{
    PODVector<unsigned> indices;
    indices.Push(index);
    SetSelections(indices);
    EnsureItemVisibility(index);
}

void ListView::SetSelections(const PODVector<unsigned>& indices)
{
    unsigned numItems = GetNumItems();
    
    // Remove first items that should no longer be selected
    for (PODVector<unsigned>::Iterator i = selections_.Begin(); i != selections_.End();)
    {
        unsigned index = *i;
        if (!indices.Contains(index))
        {
            i = selections_.Erase(i);
            
            using namespace ItemSelected;
            
            VariantMap eventData;
            eventData[P_ELEMENT] = (void*)this;
            eventData[P_SELECTION] = index;
            SendEvent(E_ITEMDESELECTED, eventData);
        }
        else
            ++i;
    }
    
    bool added = false;
    
    // Then add missing items
    for (PODVector<unsigned>::ConstIterator i = indices.Begin(); i != indices.End(); ++i)
    {
        unsigned index = *i;
        if (index < numItems)
        {
            // In singleselect mode, resend the event even for the same selection
            bool duplicate = selections_.Contains(index);
            if (!duplicate || !multiselect_)
            {
                if (!duplicate)
                {
                    selections_.Push(index);
                    added = true;
                }
                
                using namespace ItemSelected;
                
                VariantMap eventData;
                eventData[P_ELEMENT] = (void*)this;
                eventData[P_SELECTION] = *i;
                SendEvent(E_ITEMSELECTED, eventData);
            }
        }
        // If no multiselect enabled, allow setting only one item
        if (!multiselect_)
            break;
    }
    
    // Re-sort selections if necessary
    if (added)
        Sort(selections_.Begin(), selections_.End());
    
    UpdateSelectionEffect();
    SendEvent(E_SELECTIONCHANGED);
}

void ListView::AddSelection(unsigned index)
{
    if (!multiselect_)
        SetSelection(index);
    else
    {
        if (index >= GetNumItems())
            return;
        
        if (!selections_.Contains(index))
        {
            selections_.Push(index);
            
            using namespace ItemSelected;
            
            VariantMap eventData;
            eventData[P_ELEMENT] = (void*)this;
            eventData[P_SELECTION] = index;
            SendEvent(E_ITEMSELECTED, eventData);
            
            Sort(selections_.Begin(), selections_.End());
        }
        
        EnsureItemVisibility(index);
        UpdateSelectionEffect();
        SendEvent(E_SELECTIONCHANGED);
    }
}

void ListView::RemoveSelection(unsigned index)
{
    if (index >= GetNumItems())
        return;
    
    if (selections_.Remove(index))
    {
        using namespace ItemSelected;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        eventData[P_SELECTION] = index;
        SendEvent(E_ITEMDESELECTED, eventData);
    }
    
    EnsureItemVisibility(index);
    UpdateSelectionEffect();
    SendEvent(E_SELECTIONCHANGED);
}

void ListView::ToggleSelection(unsigned index)
{
    unsigned numItems = GetNumItems();
    if (index >= numItems)
        return;
    
    if (selections_.Contains(index))
        RemoveSelection(index);
    else
        AddSelection(index);
}

void ListView::ChangeSelection(int delta, bool additive)
{
    if (selections_.Empty())
        return;
    if (!multiselect_)
        additive = false;
    
    // If going downwards, use the last selection as a base. Otherwise use first
    unsigned selection = delta > 0 ? selections_.Back() : selections_.Front();
    int direction = delta > 0 ? 1 : -1;
    unsigned numItems = GetNumItems();
    unsigned newSelection = selection;
    unsigned okSelection = selection;
    PODVector<unsigned> indices = selections_;

    while (delta != 0)
    {
        newSelection += direction;
        if (newSelection >= numItems)
            break;

        UIElement* item = GetItem(newSelection);
        if (item->IsVisible())
        {
            indices.Push(okSelection = newSelection);
            delta -= direction;            
        }
    }
    
    if (!additive)
        SetSelection(okSelection);
    else
        SetSelections(indices);
}

void ListView::ClearSelection()
{
    SetSelections(PODVector<unsigned>());
}

void ListView::SetHighlightMode(HighlightMode mode)
{
    highlightMode_ = mode;
    UpdateSelectionEffect();
}

void ListView::SetMultiselect(bool enable)
{
    multiselect_ = enable;
}

void ListView::SetHierarchyMode(bool enable)
{
    hierarchyMode_ = enable;
}

void ListView::SetClearSelectionOnDefocus(bool enable)
{
    if (enable != clearSelectionOnDefocus_)
    {
        clearSelectionOnDefocus_ = enable;
    
        if (clearSelectionOnDefocus_)
        {
            SubscribeToEvent(this, E_DEFOCUSED, HANDLER(ListView, HandleDefocused));

            if (!HasFocus())
                ClearSelection();
        }
        else
            UnsubscribeFromEvent(this, E_DEFOCUSED);
    }
}

void ListView::SetDoubleClickInterval(float interval)
{
    doubleClickInterval_ = Max((int)(interval * 1000.0f), 0);
}

void ListView::Expand(unsigned index, bool enable, bool recursive)
{
    if (!hierarchyMode_)
        return;
    
    unsigned numItems = GetNumItems();
    if (index >= numItems)
        return;
    
    UIElement* item = GetItem(index++);
    SetItemExpanded(item, enable);
    int baseIndent = GetItemIndent(item);
    
    PODVector<bool> expanded(baseIndent + 1);
    expanded[baseIndent] = enable;
    
    contentElement_->DisableLayoutUpdate();
    
    while (index < numItems)
    {
        item = GetItem(index++);
        int indent = GetItemIndent(item);
        if (indent <= baseIndent)
            break;

        // Propagate the state to children when it is recursive
        if (recursive)
            SetItemExpanded(item, enable);
        
        // Use the parent expanded flag to influence the visibility of its children
        bool visible = enable && expanded[indent - 1];
        item->SetVisible(visible);

        if (indent >= expanded.Size())
            expanded.Resize(indent + 1);
        expanded[indent] = visible && GetItemExpanded(item);
    }
    
    contentElement_->EnableLayoutUpdate();
    contentElement_->UpdateLayout();
    UpdateViewSize();
}

void ListView::ToggleExpand(unsigned index, bool recursive)
{
    if (!hierarchyMode_)
        return;
    
    unsigned numItems = GetNumItems();
    if (index >= numItems)
        return;
    
    UIElement* item = GetItem(index);
    Expand(index, !GetItemExpanded(item), recursive);
}

unsigned ListView::GetNumItems() const
{
    return contentElement_->GetNumChildren();
}

UIElement* ListView::GetItem(unsigned index) const
{
    return contentElement_->GetChild(index);
}

PODVector<UIElement*> ListView::GetItems() const
{
    PODVector<UIElement*> items;
    contentElement_->GetChildren(items);
    return items;
}

unsigned ListView::GetSelection() const
{
    if (selections_.Empty())
        return M_MAX_UNSIGNED;
    else
        return GetSelections().Front();
}

UIElement* ListView::GetSelectedItem() const
{
    return contentElement_->GetChild(GetSelection());
}

PODVector<UIElement*> ListView::GetSelectedItems() const
{
    PODVector<UIElement*> ret;
    
    for (PODVector<unsigned>::ConstIterator i = selections_.Begin(); i != selections_.End(); ++i)
    {
        UIElement* item = GetItem(*i);
        if (item)
            ret.Push(item);
    }
    
    return ret;
}

bool ListView::IsSelected(unsigned index) const
{
    return selections_.Contains(index);
}

float ListView::GetDoubleClickInterval() const
{
    return (float)doubleClickInterval_ / 1000.0f;
}

void ListView::UpdateSelectionEffect()
{
    unsigned numItems = GetNumItems();
    bool highlighted = highlightMode_ == HM_ALWAYS || HasFocus();
    
    for (unsigned i = 0; i < numItems; ++i)
    {
        UIElement* item = GetItem(i);
        if (highlightMode_ != HM_NEVER && selections_.Contains(i))
            item->SetSelected(highlighted);
        else
            item->SetSelected(false);
    }
}

void ListView::EnsureItemVisibility(unsigned index)
{
    EnsureItemVisibility(GetItem(index));
}

void ListView::EnsureItemVisibility(UIElement* item)
{
    if (!item || !item->IsVisible())
        return;
    
    IntVector2 newView = GetViewPosition();
    IntVector2 currentOffset = item->GetPosition() - newView;
    const IntRect& clipBorder = scrollPanel_->GetClipBorder();
    IntVector2 windowSize(scrollPanel_->GetWidth() - clipBorder.left_ - clipBorder.right_, scrollPanel_->GetHeight() -
        clipBorder.top_ - clipBorder.bottom_);
    
    if (currentOffset.y_ < 0)
        newView.y_ += currentOffset.y_;
    if (currentOffset.y_ + item->GetHeight() > windowSize.y_)
        newView.y_ += currentOffset.y_ + item->GetHeight() - windowSize.y_;
    
    SetViewPosition(newView);
}

void ListView::HandleUIMouseClick(StringHash eventType, VariantMap& eventData)
{
    if (eventData[UIMouseClick::P_BUTTON].GetInt() != MOUSEB_LEFT)
        return;
    int qualifiers = eventData[UIMouseClick::P_QUALIFIERS].GetInt();
    
    UIElement* element = static_cast<UIElement*>(eventData[UIMouseClick::P_ELEMENT].GetPtr());
    
    unsigned numItems = GetNumItems();
    for (unsigned i = 0; i < numItems; ++i)
    {
        if (element == GetItem(i))
        {
            // Check doubleclick
            bool isDoubleClick = false;
            if (!multiselect_ || !qualifiers)
            {
                if (!(isDoubleClick = doubleClickTimer_.GetMSec(true) < doubleClickInterval_ && lastClickedItem_ == i))
                    lastClickedItem_ = i;
                SetSelection(i);
            }
            
            // Check multiselect with shift & ctrl
            if (multiselect_)
            {
                if (qualifiers & QUAL_SHIFT)
                {
                    if (selections_.Empty())
                        SetSelection(i);
                    else
                    {
                        unsigned first = selections_.Front();
                        unsigned last = selections_.Back();
                        PODVector<unsigned> newSelections = selections_;
                        if (i == first || i == last)
                        {
                            for (unsigned j = first; j <= last; ++j)
                                newSelections.Push(j);
                        }
                        else if (i < first)
                        {
                            for (unsigned j = i; j <= first; ++j)
                                newSelections.Push(j);
                        }
                        else if (i < last)
                        {
                            if ((abs((int)i - (int)first)) <= (abs((int)i - (int)last)))
                            {
                                for (unsigned j = first; j <= i; ++j)
                                    newSelections.Push(j);
                            }
                            else
                            {
                                for (unsigned j = i; j <= last; ++j)
                                    newSelections.Push(j);
                            }
                        }
                        else if (i > last)
                        {
                            for (unsigned j = last; j <= i; ++j)
                                newSelections.Push(j);
                        }
                        SetSelections(newSelections);
                    }
                }
                else if (qualifiers & QUAL_CTRL)
                    ToggleSelection(i);
            }
            
            if (isDoubleClick)
            {
                VariantMap eventData;
                eventData[ItemDoubleClicked::P_ELEMENT] = (void*)this;
                eventData[ItemDoubleClicked::P_SELECTION] = i;
                SendEvent(E_ITEMDOUBLECLICKED, eventData);
            }
            
            return;
        }
    }
}

void ListView::HandleFocusChanged(StringHash eventType, VariantMap& eventData)
{
    using namespace FocusChanged;
    
    UIElement* element = static_cast<UIElement*>(eventData[P_ELEMENT].GetPtr());
    while (element)
    {
        // If the focused element or its parent is in the list, scroll the list to make the item visible
        UIElement* parent = element->GetParent();
        if (parent == contentElement_)
        {
            EnsureItemVisibility(element);
            return;
        }
        element = parent;
    }
}

void ListView::HandleDefocused(StringHash eventType, VariantMap& eventData)
{
    ClearSelection();
}

}
