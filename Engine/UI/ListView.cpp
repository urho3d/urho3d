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
#include "BorderImage.h"
#include "Context.h"
#include "InputEvents.h"
#include "ListView.h"
#include "Log.h"
#include "Sort.h"
#include "StringUtils.h"
#include "UIEvents.h"

#include "DebugNew.h"

static const ShortStringHash indentHash("Indent");

static const String highlightModes[] =
{
    "never",
    "focus",
    "always",
    ""
};

int GetItemIndent(UIElement* item)
{
    if (!item)
        return 0;
    return item->GetVar(indentHash).GetInt();
}

OBJECTTYPESTATIC(ListView);

ListView::ListView(Context* context) :
    ScrollView(context),
    highlightMode_(HM_FOCUS),
    multiselect_(false),
    hierarchyMode_(false),
    clearSelectionOnDefocus_(false),
    doubleClickInterval_(0.5f),
    doubleClickTimer_(0.0f),
    lastClickedItem_(M_MAX_UNSIGNED)
{
    UIElement* container = new UIElement(context_);
    container->SetActive(true);
    container->SetLayout(LM_VERTICAL);
    container->SetSortChildren(false);
    SetContentElement(container);
    
    SubscribeToEvent(E_UIMOUSECLICK, HANDLER(ListView, HandleUIMouseClick));
    SubscribeToEvent(E_FOCUSCHANGED, HANDLER(ListView, HandleFocusChanged));
    SubscribeToEvent(this, E_FOCUSED, HANDLER(ListView, HandleFocused));
    SubscribeToEvent(this, E_DEFOCUSED, HANDLER(ListView, HandleDefocused));
}

ListView::~ListView()
{
}

void ListView::RegisterObject(Context* context)
{
    context->RegisterFactory<ListView>();
}

void ListView::SetStyle(const XMLElement& element)
{
    ScrollView::SetStyle(element);
    
    UIElement* root = GetRoot();
    XMLElement itemElem = element.GetChild("listitem");
    if (root)
    {
        while (itemElem)
        {
            if (itemElem.HasAttribute("name"))
            {
                UIElement* item = root->GetChild(itemElem.GetAttribute("name"), true);
                AddItem(item);
                if (itemElem.HasAttribute("indent"))
                    item->SetVar(indentHash, itemElem.GetInt("indent"));
                itemElem = itemElem.GetNext("listitem");
            }
        }
    }
    
    if (element.HasChild("highlight"))
    {
        String highlight = element.GetChild("highlight").GetAttributeLower("value");
        SetHighlightMode((HighlightMode)GetStringListIndex(highlight, highlightModes, HM_FOCUS));
    }
    if (element.HasChild("multiselect"))
        SetMultiselect(element.GetChild("multiselect").GetBool("enable"));
    if (element.HasChild("hierarchy"))
        SetHierarchyMode(element.GetChild("hierarchy").GetBool("enable"));
    if (element.HasChild("clearselection"))
        SetClearSelectionOnDefocus(element.GetChild("clearselection").GetBool("enable"));
    if (element.HasChild("doubleclickinterval"))
        SetDoubleClickInterval(element.GetChild("doubleclickinterval").GetFloat("value"));
    
    XMLElement selectionElem = element.GetChild("selection");
    while (selectionElem)
    {
        AddSelection(selectionElem.GetInt("value"));
        selectionElem = selectionElem.GetNext("selection");
    }
    
    // Set the container's layout border to match scroll panel clipping, so that elements are not left partially hidden
    contentElement_->SetLayoutBorder(scrollPanel_->GetClipBorder());
}

void ListView::Update(float timeStep)
{
    if (doubleClickTimer_ > 0.0f)
        doubleClickTimer_ = Max(doubleClickTimer_ - timeStep, 0.0f);
}

void ListView::OnKey(int key, int buttons, int qualifiers)
{
    // If no selection, can not move with keys
    unsigned numItems = GetNumItems();
    unsigned selection = GetSelection();
    
    if (selection != M_MAX_UNSIGNED && numItems)
    {
        // If either shift or ctrl held down, add to selection if multiselect enabled
        bool additive = multiselect_ && qualifiers != 0;
        
        switch (key)
        {
        case KEY_LEFT:
            if (hierarchyMode_)
            {
                SetChildItemsVisible(selection, false);
                return;
            }
            break;
            
        case KEY_RIGHT:
            if (hierarchyMode_)
            {
                SetChildItemsVisible(selection, true);
                return;
            }
            break;
            
        case KEY_RETURN:
            if (hierarchyMode_)
            {
                ToggleChildItemsVisible(selection);
                return;
            }
            break;
            
        case KEY_UP:
            ChangeSelection(-1, additive);
            return;
            
        case KEY_DOWN:
            ChangeSelection(1, additive);
            return;
            
        case KEY_PAGEUP:
            {
                // Convert page step to pixels and see how many items have to be skipped to reach that many pixels
                int stepPixels = ((int)(pageStep_ * scrollPanel_->GetHeight())) - GetSelectedItem()->GetHeight();
                unsigned newSelection = selection;
                unsigned okSelection = selection;
                while (newSelection < numItems)
                {
                    UIElement* item = GetItem(newSelection);
                    int height = 0;
                    if (item->IsVisible())
                    {
                        height = item->GetHeight();
                        okSelection = newSelection;
                    }
                    if (stepPixels < height)
                        break;
                    stepPixels -= height;
                    --newSelection;
                }
                if (!additive)
                    SetSelection(okSelection);
                else
                    AddSelection(okSelection);
            }
            return;
            
        case KEY_PAGEDOWN:
            {
                int stepPixels = ((int)(pageStep_ * scrollPanel_->GetHeight())) - GetSelectedItem()->GetHeight();
                unsigned newSelection = selection;
                unsigned okSelection = selection;
                while (newSelection < numItems)
                {
                    UIElement* item = GetItem(newSelection);
                    int height = 0;
                    if (item->IsVisible())
                    {
                        height = item->GetHeight();
                        okSelection = newSelection;
                    }
                    if (stepPixels < height)
                        break;
                    stepPixels -= height;
                    ++newSelection;
                }
                if (!additive)
                    SetSelection(okSelection);
                else
                    AddSelection(okSelection);
            }
            return;
            
        case KEY_HOME:
            ChangeSelection(-(int)GetNumItems(), additive);
            return;
            
        case KEY_END:
            ChangeSelection(GetNumItems(), additive);
            return;
        }
    }
    
    using namespace UnhandledKey;
    
    VariantMap eventData;
    eventData[P_ELEMENT] = (void*)this;
    eventData[P_KEY] = key;
    eventData[P_BUTTONS] = buttons;
    eventData[P_QUALIFIERS] = qualifiers;
    SendEvent(E_UNHANDLEDKEY, eventData);
}

void ListView::OnResize()
{
    ScrollView::OnResize();
    
    // Set the content element width to match the scrollpanel
    contentElement_->SetWidth(scrollPanel_->GetWidth());
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
        HashSet<unsigned> prevSelections = selections_;
        selections_.Clear();
        for (HashSet<unsigned>::Iterator j = prevSelections.Begin(); j != prevSelections.End(); ++j)
        {
            if (*j >= index)
                selections_.Insert(*j + 1);
            else
                selections_.Insert(*j);
        }
        UpdateSelectionEffect();
    }
}

void ListView::RemoveItem(UIElement* item)
{
    unsigned numItems = GetNumItems();
    
    for (unsigned i = 0; i < numItems; ++i)
    {
        if (GetItem(i) == item)
        {
            item->SetSelected(false);
            selections_.Erase(i);
            
            // Remove any child items in hierarchy mode
            unsigned removed = 1;
            if (hierarchyMode_)
            {
                int baseIndent = GetItemIndent(item);
                int j = i + 1;
                for (;;)
                {
                    UIElement* childItem = GetItem(i + 1);
                    if (!childItem)
                        break;
                    if (GetItemIndent(childItem) > baseIndent)
                    {
                        childItem->SetSelected(false);
                        selections_.Erase(j);
                        contentElement_->RemoveChild(childItem);
                        ++removed;
                    }
                    else
                        break;
                    ++j;
                }
            }
            
            // If necessary, shift the following selections
            if (!selections_.Empty())
            {
                HashSet<unsigned> prevSelections = selections_;
                selections_.Clear();
                for (HashSet<unsigned>::Iterator j = prevSelections.Begin(); j != prevSelections.End(); ++j)
                {
                    if (*j > i)
                        selections_.Insert(*j - removed);
                    else
                        selections_.Insert(*j);
                }
                UpdateSelectionEffect();
            }
            break;
        }
    }
    contentElement_->RemoveChild(item);
}

void ListView::RemoveItem(unsigned index)
{
    RemoveItem(GetItem(index));
}

void ListView::RemoveAllItems()
{
    contentElement_->DisableLayoutUpdate();
    
    unsigned numItems = GetNumItems();
    for (unsigned i = 0; i < numItems; ++i)
        contentElement_->GetChild(i)->SetSelected(false);
    contentElement_->RemoveAllChildren();
    ClearSelection();
    
    contentElement_->EnableLayoutUpdate();
    contentElement_->UpdateLayout();
}

void ListView::SetSelection(unsigned index)
{
    HashSet<unsigned> indices;
    indices.Insert(index);
    SetSelections(indices);
    EnsureItemVisibility(index);
}

void ListView::SetSelections(const PODVector<unsigned>& indices)
{
    HashSet<unsigned> newSelection;
    for (PODVector<unsigned>::ConstIterator i = indices.Begin(); i != indices.End(); ++i)
        newSelection.Insert(*i);
    SetSelections(newSelection);
}

void ListView::AddSelection(unsigned index)
{
    if (!multiselect_)
        SetSelection(index);
    else
    {
        if (index >= GetNumItems())
            return;
        
        HashSet<unsigned> newSelections = selections_;
        newSelections.Insert(index);
        SetSelections(newSelections);
        EnsureItemVisibility(index);
    }
}

void ListView::RemoveSelection(unsigned index)
{
    if (index >= GetNumItems())
        return;
    
    HashSet<unsigned> newSelections = selections_;
    newSelections.Erase(index);
    SetSelections(newSelections);
    EnsureItemVisibility(index);
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
    unsigned numItems = GetNumItems();
    unsigned newSelection = selection;
    unsigned okSelection = selection;
    while (delta != 0)
    {
        if (delta > 0)
        {
            ++newSelection;
            if (newSelection >= numItems)
                break;
        }
        if (delta < 0)
        {
            --newSelection;
            if (newSelection >= numItems)
                break;
        }
        UIElement* item = GetItem(newSelection);
        if (item->IsVisible())
        {
            okSelection = newSelection;
            if (delta > 0)
                --delta;
            if (delta < 0)
                ++delta;
        }
    }
    
    if (!additive)
        SetSelection(okSelection);
    else
        AddSelection(okSelection);
}

void ListView::ClearSelection()
{
    SetSelections(HashSet<unsigned>());
    UpdateSelectionEffect();
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
    clearSelectionOnDefocus_ = enable;
}

void ListView::SetDoubleClickInterval(float interval)
{
    doubleClickInterval_ = interval;
}

void ListView::SetChildItemsVisible(unsigned index, bool enable)
{
    unsigned numItems = GetNumItems();
    
    if (!hierarchyMode_ || index >= numItems)
        return;
    
    contentElement_->DisableLayoutUpdate();
    
    int baseIndent = GetItemIndent(GetItem(index));
    
    for (unsigned i = index + 1; i < numItems; ++i)
    {
        UIElement* item = GetItem(i);
        if (GetItemIndent(item) > baseIndent)
            item->SetVisible(enable);
        else
            break;
    }
    
    contentElement_->EnableLayoutUpdate();
    contentElement_->UpdateLayout();
}

void ListView::SetChildItemsVisible(bool enable)
{
    unsigned numItems = GetNumItems();
    
    for (unsigned i = 0; i < numItems; ++i)
    {
        if (!GetItemIndent(GetItem(i)))
            SetChildItemsVisible(i, enable);
    }
    
    if (GetSelections().Size() == 1)
        EnsureItemVisibility(GetSelection());
}

void ListView::ToggleChildItemsVisible(unsigned index)
{
    unsigned numItems = GetNumItems();
    
    if (!hierarchyMode_ || index >= numItems)
        return;
    
    contentElement_->DisableLayoutUpdate();
    
    int baseIndent = GetItemIndent(GetItem(index));
    bool firstChild = true;
    UIElement* prevItem = 0;
    for (unsigned i = index + 1; i < numItems; ++i)
    {
        UIElement* item = GetItem(i);
        if (GetItemIndent(item) > baseIndent)
        {
            if (firstChild)
            {
                item->SetVisible(!item->IsVisible());
                firstChild = false;
            }
            else
                item->SetVisible(prevItem->IsVisible());
        }
        else
            break;
        
        prevItem = item;
    }
    
    contentElement_->EnableLayoutUpdate();
    contentElement_->UpdateLayout();
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

PODVector<unsigned> ListView::GetSelections() const
{
    PODVector<unsigned> sortedIndices;
    
    for (HashSet<unsigned>::ConstIterator i = selections_.Begin(); i != selections_.End(); ++i)
        sortedIndices.Push(*i);
    Sort(sortedIndices.Begin(), sortedIndices.End());
    
    return sortedIndices;
}

UIElement* ListView::GetSelectedItem() const
{
    return contentElement_->GetChild(GetSelection());
}

PODVector<UIElement*> ListView::GetSelectedItems() const
{
    PODVector<UIElement*> ret;
    PODVector<unsigned> sortedIndices;
    
    for (HashSet<unsigned>::ConstIterator i = selections_.Begin(); i != selections_.End(); ++i)
        sortedIndices.Push(*i);
    Sort(sortedIndices.Begin(), sortedIndices.End());
    
    for (PODVector<unsigned>::ConstIterator i = sortedIndices.Begin(); i != sortedIndices.End(); ++i)
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

void ListView::UpdateSelectionEffect()
{
    unsigned numItems = GetNumItems();
    
    for (unsigned i = 0; i < numItems; ++i)
    {
        UIElement* item = GetItem(i);
        if (highlightMode_ != HM_NEVER && selections_.Contains(i))
            item->SetSelected(HasFocus() || highlightMode_ == HM_ALWAYS);
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
    
    IntVector2 currentOffset = item->GetScreenPosition() - scrollPanel_->GetScreenPosition() - contentElement_->GetPosition();
    IntVector2 newView = GetViewPosition();
    const IntRect& clipBorder = scrollPanel_->GetClipBorder();
    IntVector2 windowSize(scrollPanel_->GetWidth() - clipBorder.left_ - clipBorder.right_, scrollPanel_->GetHeight() -
        clipBorder.top_ - clipBorder.bottom_);
    
    if (currentOffset.y_ < 0)
        newView.y_ += currentOffset.y_;
    if (currentOffset.y_ + item->GetHeight() > windowSize.y_)
        newView.y_ += currentOffset.y_ + item->GetHeight() - windowSize.y_;
    
    SetViewPosition(newView);
}

void ListView::SetSelections(const HashSet<unsigned>& indices)
{
    unsigned numItems = GetNumItems();
    
    // Remove first items that should no longer be selected
    for (HashSet<unsigned>::Iterator i = selections_.Begin(); i != selections_.End();)
    {
        unsigned index = *i;
        if (!indices.Contains(index))
        {
            HashSet<unsigned>::Iterator current = i++;
            selections_.Erase(current);
            
            using namespace ItemSelected;
            
            VariantMap eventData;
            eventData[P_ELEMENT] = (void*)this;
            eventData[P_SELECTION] = index;
            SendEvent(E_ITEMDESELECTED, eventData);
        }
        else
            ++i;
    }
    
    // Then add missing items
    for (HashSet<unsigned>::ConstIterator i = indices.Begin(); i != indices.End(); ++i)
    {
        unsigned index = *i;
        if (index < numItems)
        {
            // In singleselect mode, resend the event even for the same selection
            if (selections_.Find(index) == selections_.End() || !multiselect_)
            {
                selections_.Insert(*i);
                
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
    
    SendEvent(E_SELECTIONCHANGED);
    
    UpdateSelectionEffect();
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
                if (doubleClickTimer_ > 0.0f && lastClickedItem_ == i)
                {
                    isDoubleClick = true;
                    doubleClickTimer_ = 0.0f;
                }
                else
                {
                    doubleClickTimer_ = doubleClickInterval_;
                    lastClickedItem_ = i;
                }
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
                        HashSet<unsigned> newSelections = selections_;
                        if (i == first || i == last)
                        {
                            for (unsigned j = first; j <= last; ++j)
                                newSelections.Insert(j);
                        }
                        else if (i < first)
                        {
                            for (unsigned j = i; j <= first; ++j)
                                newSelections.Insert(j);
                        }
                        else if (i < last)
                        {
                            if ((abs((int)i - (int)first)) <= (abs((int)i - (int)last)))
                            {
                                for (unsigned j = first; j <= i; ++j)
                                    newSelections.Insert(j);
                            }
                            else
                            {
                                for (unsigned j = i; j <= last; ++j)
                                    newSelections.Insert(j);
                            }
                        }
                        else if (i > last)
                        {
                            for (unsigned j = last; j <= i; ++j)
                                newSelections.Insert(j);
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

void ListView::HandleFocused(StringHash eventType, VariantMap& eventData)
{
    UpdateSelectionEffect();
}

void ListView::HandleDefocused(StringHash eventType, VariantMap& eventData)
{
    if (clearSelectionOnDefocus_)
        ClearSelection();
    
    UpdateSelectionEffect();
}
