// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Input/InputEvents.h"
#include "../IO/Log.h"
#include "../UI/CheckBox.h"
#include "../UI/ListView.h"
#include "../UI/Text.h"
#include "../UI/UI.h"
#include "../UI/UIEvents.h"

#include "../DebugNew.h"

namespace Urho3D
{

static const char* highlightModes[] =
{
    "Never",
    "Focus",
    "Always",
    nullptr
};

static const StringHash expandedHash("Expanded");

extern const char* UI_CATEGORY;

bool GetItemExpanded(UIElement* item)
{
    return item ? item->GetVar(expandedHash).GetBool() : false;
}

void SetItemExpanded(UIElement* item, bool enable)
{
    item->SetVar(expandedHash, enable);
}

static const StringHash hierarchyParentHash("HierarchyParent");

bool GetItemHierarchyParent(UIElement* item)
{
    return item ? item->GetVar(hierarchyParentHash).GetBool() : false;
}

void SetItemHierarchyParent(UIElement* item, bool enable)
{
    item->SetVar(hierarchyParentHash, enable);
}

/// Hierarchy container (used by ListView internally when in hierarchy mode).
class HierarchyContainer : public UIElement
{
    URHO3D_OBJECT(HierarchyContainer, UIElement);

public:
    /// Construct.
    HierarchyContainer(Context* context, ListView* listView, UIElement* overlayContainer) :
        UIElement(context),
        listView_(listView),
        overlayContainer_(overlayContainer)
    {
        SubscribeToEvent(this, E_LAYOUTUPDATED, URHO3D_HANDLER(HierarchyContainer, HandleLayoutUpdated));
        SubscribeToEvent(overlayContainer->GetParent(), E_VIEWCHANGED, URHO3D_HANDLER(HierarchyContainer, HandleViewChanged));
        SubscribeToEvent(E_UIMOUSECLICK, URHO3D_HANDLER(HierarchyContainer, HandleUIMouseClick));
    }

    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Handle layout updated by adjusting the position of the overlays.
    void HandleLayoutUpdated(StringHash eventType, VariantMap& eventData)
    {
        // Adjust the container size for child clipping effect
        overlayContainer_->SetSize(GetParent()->GetSize());

        for (i32 i = 0; i < children_.Size(); ++i)
        {
            const IntVector2& position = children_[i]->GetPosition();
            auto* overlay = overlayContainer_->GetChildStaticCast<CheckBox>(i);
            bool visible = children_[i]->IsVisible() && GetItemHierarchyParent(children_[i]);
            overlay->SetVisible(visible);
            if (visible)
            {
                overlay->SetPosition(position.x_, position.y_);
                overlay->SetChecked(GetItemExpanded(children_[i]));
            }
        }
    }

    /// Handle view changed by scrolling the overlays in tandem.
    void HandleViewChanged(StringHash eventType, VariantMap& eventData)
    {
        using namespace ViewChanged;

        int x = eventData[P_X].GetInt();
        int y = eventData[P_Y].GetInt();

        IntRect panelBorder = GetParent()->GetClipBorder();
        overlayContainer_->SetChildOffset(IntVector2(-x + panelBorder.left_, -y + panelBorder.top_));
    }

    /// Handle mouse click on overlays by toggling the expansion state of the corresponding item.
    void HandleUIMouseClick(StringHash eventType, VariantMap& eventData)
    {
        using namespace UIMouseClick;

        auto* overlay = static_cast<UIElement*>(eventData[UIMouseClick::P_ELEMENT].GetPtr());
        if (overlay)
        {
            const Vector<SharedPtr<UIElement>>& children = overlayContainer_->GetChildren();
            Vector<SharedPtr<UIElement>>::ConstIterator i = children.Find(SharedPtr<UIElement>(overlay));
            if (i != children.End())
                listView_->ToggleExpand((i32)(i - children.Begin()));
        }
    }

    /// Insert a child element into a specific position in the child list.
    void InsertChild(i32 index, UIElement* element)
    {
        // Insert the overlay at the same index position to the overlay container
        CheckBox* overlay = static_cast<CheckBox*>(overlayContainer_->CreateChild(CheckBox::GetTypeStatic(), String::EMPTY, index));
        overlay->SetStyle("HierarchyListViewOverlay");
        int baseIndent = listView_->GetBaseIndent();
        int indent = element->GetIndent() - baseIndent - 1;
        overlay->SetIndent(indent);
        overlay->SetFixedWidth((indent + 1) * element->GetIndentSpacing());

        // Then insert the element as child as per normal
        UIElement::InsertChild(index, element);
    }

private:
    // Parent list view.
    ListView* listView_;
    // Container for overlay checkboxes.
    UIElement* overlayContainer_;
};

void HierarchyContainer::RegisterObject(Context* context)
{
    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);
}

ListView::ListView(Context* context) :
    ScrollView(context),
    highlightMode_(HM_FOCUS),
    multiselect_(false),
    hierarchyMode_(true),    // Init to true here so that the setter below takes effect
    baseIndent_(0),
    clearSelectionOnDefocus_(false),
    selectOnClickEnd_(false)
{
    resizeContentWidth_ = true;

    // By default list view is set to non-hierarchy mode
    SetHierarchyMode(false);

    SubscribeToEvent(E_UIMOUSEDOUBLECLICK, URHO3D_HANDLER(ListView, HandleUIMouseDoubleClick));
    SubscribeToEvent(E_FOCUSCHANGED, URHO3D_HANDLER(ListView, HandleItemFocusChanged));
    SubscribeToEvent(this, E_DEFOCUSED, URHO3D_HANDLER(ListView, HandleFocusChanged));
    SubscribeToEvent(this, E_FOCUSED, URHO3D_HANDLER(ListView, HandleFocusChanged));

    UpdateUIClickSubscription();
}

ListView::~ListView() = default;

void ListView::RegisterObject(Context* context)
{
    context->RegisterFactory<ListView>(UI_CATEGORY);

    HierarchyContainer::RegisterObject(context);

    URHO3D_COPY_BASE_ATTRIBUTES(ScrollView);
    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Highlight Mode", GetHighlightMode, SetHighlightMode, HighlightMode, highlightModes, HM_FOCUS, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Multiselect", GetMultiselect, SetMultiselect, bool, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Hierarchy Mode", GetHierarchyMode, SetHierarchyMode, bool, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Base Indent", GetBaseIndent, SetBaseIndent, int, 0, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Clear Sel. On Defocus", GetClearSelectionOnDefocus, SetClearSelectionOnDefocus, bool, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Select On Click End", GetSelectOnClickEnd, SetSelectOnClickEnd, bool, false, AM_FILE);
}

void ListView::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers)
{
    // If no selection, can not move with keys
    i32 numItems = GetNumItems();
    i32 selection = GetSelection();

    // If either shift or ctrl held down, add to selection if multiselect enabled
    bool additive = multiselect_ && qualifiers & (QUAL_SHIFT | QUAL_CTRL);
    int delta = M_MAX_INT;
    int pageDirection = 1;

    if (numItems)
    {
        if (selection != NINDEX && qualifiers & QUAL_CTRL && key == KEY_C)
        {
            CopySelectedItemsToClipboard();
            return;
        }

        switch (key)
        {
        case KEY_LEFT:
        case KEY_RIGHT:
            if (selection != NINDEX && hierarchyMode_)
            {
                Expand(selection, key == KEY_RIGHT);
                return;
            }
            break;

        case KEY_RETURN:
        case KEY_RETURN2:
        case KEY_KP_ENTER:
            if (selection != NINDEX && hierarchyMode_)
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
            [[fallthrough]];

        case KEY_PAGEDOWN:
            {
                // Convert page step to pixels and see how many items have to be skipped to reach that many pixels
                if (selection == NINDEX)
                    selection = 0;      // Assume as if first item is selected
                int stepPixels = ((int)(pageStep_ * scrollPanel_->GetHeight())) - contentElement_->GetChild(selection)->GetHeight();
                i32 newSelection = selection;
                i32 okSelection = selection;
                i32 invisible = 0;
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
            delta = -GetNumItems();
            break;

        case KEY_END:
            delta = GetNumItems();
            break;

        default: break;
        }
    }

    if (delta != M_MAX_INT)
    {
        ChangeSelection(delta, additive);
        return;
    }

    using namespace UnhandledKey;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_ELEMENT] = this;
    eventData[P_KEY] = key;
    eventData[P_BUTTONS] = (unsigned)buttons;
    eventData[P_QUALIFIERS] = (unsigned)qualifiers;
    SendEvent(E_UNHANDLEDKEY, eventData);
}

void ListView::OnResize(const IntVector2& newSize, const IntVector2& delta)
{
    ScrollView::OnResize(newSize, delta);

    // When in hierarchy mode also need to resize the overlay container
    if (hierarchyMode_)
        overlayContainer_->SetSize(scrollPanel_->GetSize());
}

void ListView::UpdateInternalLayout()
{
    if (overlayContainer_)
        overlayContainer_->UpdateLayout();
    contentElement_->UpdateLayout();
}

void ListView::DisableInternalLayoutUpdate()
{
    if (overlayContainer_)
        overlayContainer_->DisableLayoutUpdate();
    contentElement_->DisableLayoutUpdate();
}

void ListView::EnableInternalLayoutUpdate()
{
    if (overlayContainer_)
        overlayContainer_->EnableLayoutUpdate();
    contentElement_->EnableLayoutUpdate();
}

void ListView::AddItem(UIElement* item)
{
    InsertItem(ENDPOS, item);
}

void ListView::InsertItem(i32 index, UIElement* item, UIElement* parentItem)
{
    assert(index >= 0 || index == ENDPOS);

    if (!item || item->GetParent() == contentElement_)
        return;

    // Enable input so that clicking the item can be detected
    item->SetEnabled(true);
    item->SetSelected(false);

    const i32 numItems = contentElement_->GetNumChildren();
    if (hierarchyMode_)
    {
        int baseIndent = baseIndent_;
        if (parentItem)
        {
            baseIndent = parentItem->GetIndent();
            SetItemHierarchyParent(parentItem, true);

            // Hide item if parent is collapsed
            const i32 parentIndex = FindItem(parentItem);
            if (!IsExpanded(parentIndex))
                item->SetVisible(false);

            // Adjust the index to ensure it is within the children index limit of the parent item
            if (index <= parentIndex && index != ENDPOS)
            {
                index = parentIndex + 1;
            }
            else
            {
                i32 indexLimit = parentIndex;

                while (++indexLimit < numItems)
                {
                    if (contentElement_->GetChild(indexLimit)->GetIndent() <= baseIndent)
                        break;
                }

                if (index > indexLimit || index == ENDPOS)
                    index = indexLimit;
            }
        }
        item->SetIndent(baseIndent + 1);
        SetItemExpanded(item, item->IsVisible());

        // Use the 'overrided' version to insert the child item
        static_cast<HierarchyContainer*>(contentElement_.Get())->InsertChild(index, item);
    }
    else
    {
        if (index > numItems || index == ENDPOS)
            index = numItems;

        contentElement_->InsertChild(index, item);
    }

    // If necessary, shift the following selections
    if (!selections_.Empty())
    {
        for (i32 i = 0; i < selections_.Size(); ++i)
        {
            if (selections_[i] >= index)
                ++selections_[i];
        }

        UpdateSelectionEffect();
    }
}

void ListView::RemoveItem(UIElement* item, i32 index/* = 0*/)
{
    assert(index >= 0);

    if (!item)
        return;

    i32 numItems = GetNumItems();
    for (i32 i = index; i < numItems; ++i)
    {
        if (GetItem(i) == item)
        {
            item->SetSelected(false);
            selections_.Remove(i);

            i32 removed = 1;
            if (hierarchyMode_)
            {
                // Remove any child items in hierarchy mode
                if (GetItemHierarchyParent(item))
                {
                    int baseIndent = item->GetIndent();
                    for (i32 j = i + 1; ; ++j)
                    {
                        UIElement* childItem = GetItem(i + 1);
                        if (!childItem)
                            break;
                        if (childItem->GetIndent() > baseIndent)
                        {
                            childItem->SetSelected(false);
                            if (j < selections_.Size()) // TODO: Rework?
                                selections_.Erase(j);
                            contentElement_->RemoveChildAtIndex(i + 1);
                            overlayContainer_->RemoveChildAtIndex(i + 1);
                            ++removed;
                        }
                        else
                            break;
                    }
                }

                // Check if the parent of removed item still has other children
                if (i > 0)
                {
                    int baseIndent = item->GetIndent();
                    UIElement* prevKin = GetItem(i - 1);        // Could be parent or sibling
                    if (prevKin->GetIndent() < baseIndent)
                    {
                        UIElement* nextKin = GetItem(i + 1);    // Could be sibling or parent-sibling or 0 if index out of bound
                        if (!nextKin || nextKin->GetIndent() < baseIndent)
                        {
                            // If we reach here then the parent has no other children
                            SetItemHierarchyParent(prevKin, false);
                        }
                    }
                }

                // Remove the overlay at the same index
                overlayContainer_->RemoveChildAtIndex(i);
            }

            // If necessary, shift the following selections
            if (!selections_.Empty())
            {
                for (i32 j = 0; j < selections_.Size(); ++j)
                {
                    if (selections_[j] > i)
                        selections_[j] -= removed;
                }

                UpdateSelectionEffect();
            }

            contentElement_->RemoveChildAtIndex(i);
            break;
        }
    }
}

void ListView::RemoveItem(i32 index)
{
    assert(index >= 0);
    RemoveItem(GetItem(index), index);
}

void ListView::RemoveAllItems()
{
    contentElement_->DisableLayoutUpdate();

    ClearSelection();
    contentElement_->RemoveAllChildren();
    if (hierarchyMode_)
        overlayContainer_->RemoveAllChildren();

    contentElement_->EnableLayoutUpdate();
    contentElement_->UpdateLayout();
}

void ListView::SetSelection(i32 index)
{
    assert(index >= 0);
    Vector<i32> indices;
    indices.Push(index);
    SetSelections(indices);
    EnsureItemVisibility(index);
}

void ListView::SetSelections(const Vector<i32>& indices)
{
    // Make a weak pointer to self to check for destruction as a response to events
    WeakPtr<ListView> self(this);

    i32 numItems = GetNumItems();

    // Remove first items that should no longer be selected
    for (Vector<i32>::Iterator i = selections_.Begin(); i != selections_.End();)
    {
        i32 index = *i;
        if (!indices.Contains(index))
        {
            i = selections_.Erase(i);

            using namespace ItemSelected;

            VariantMap& eventData = GetEventDataMap();
            eventData[P_ELEMENT] = this;
            eventData[P_SELECTION] = index;
            SendEvent(E_ITEMDESELECTED, eventData);

            if (self.Expired())
                return;
        }
        else
            ++i;
    }

    bool added = false;

    // Then add missing items
    for (Vector<i32>::ConstIterator i = indices.Begin(); i != indices.End(); ++i)
    {
        i32 index = *i;
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

                VariantMap& eventData = GetEventDataMap();
                eventData[P_ELEMENT] = this;
                eventData[P_SELECTION] = *i;
                SendEvent(E_ITEMSELECTED, eventData);

                if (self.Expired())
                    return;
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

void ListView::AddSelection(i32 index)
{
    assert(index >= 0);

    // Make a weak pointer to self to check for destruction as a response to events
    WeakPtr<ListView> self(this);

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

            VariantMap& eventData = GetEventDataMap();
            eventData[P_ELEMENT] = this;
            eventData[P_SELECTION] = index;
            SendEvent(E_ITEMSELECTED, eventData);

            if (self.Expired())
                return;

            Sort(selections_.Begin(), selections_.End());
        }

        EnsureItemVisibility(index);
        UpdateSelectionEffect();
        SendEvent(E_SELECTIONCHANGED);
    }
}

void ListView::RemoveSelection(i32 index)
{
    assert(index >= 0);

    if (index >= GetNumItems())
        return;

    if (selections_.Remove(index))
    {
        using namespace ItemSelected;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_ELEMENT] = this;
        eventData[P_SELECTION] = index;
        SendEvent(E_ITEMDESELECTED, eventData);
    }

    EnsureItemVisibility(index);
    UpdateSelectionEffect();
    SendEvent(E_SELECTIONCHANGED);
}

void ListView::ToggleSelection(i32 index)
{
    assert(index >= 0);

    i32 numItems = GetNumItems();

    if (index >= numItems)
        return;

    if (selections_.Contains(index))
        RemoveSelection(index);
    else
        AddSelection(index);
}

void ListView::ChangeSelection(int delta, bool additive)
{
    i32 numItems = GetNumItems();
    if (selections_.Empty())
    {
        // Select first item if there is no selection yet
        if (numItems > 0)
            SetSelection(0);
        if (abs(delta) == 1)
            return;
    }
    if (!multiselect_)
        additive = false;

    // If going downwards, use the last selection as a base. Otherwise use first
    i32 selection = delta > 0 ? selections_.Back() : selections_.Front();
    int direction = delta > 0 ? 1 : -1;
    i32 newSelection = selection;
    i32 okSelection = selection;
    Vector<i32> indices = selections_;

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
    SetSelections(Vector<i32>());
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
    if (enable == hierarchyMode_)
        return;

    hierarchyMode_ = enable;
    UIElement* container;
    if (enable)
    {
        overlayContainer_ = new UIElement(context_);
        overlayContainer_->SetName("LV_OverlayContainer");
        overlayContainer_->SetInternal(true);
        AddChild(overlayContainer_);
        overlayContainer_->SetSortChildren(false);
        overlayContainer_->SetClipChildren(true);

        container = new HierarchyContainer(context_, this, overlayContainer_);
    }
    else
    {
        if (overlayContainer_)
        {
            RemoveChild(overlayContainer_);
            overlayContainer_.Reset();
        }

        container = new UIElement(context_);
    }

    container->SetName("LV_ItemContainer");
    container->SetInternal(true);
    SetContentElement(container);
    container->SetEnabled(true);
    container->SetSortChildren(false);
}

void ListView::SetBaseIndent(int baseIndent)
{
    baseIndent_ = baseIndent;
    UpdateLayout();
}

void ListView::SetClearSelectionOnDefocus(bool enable)
{
    if (enable != clearSelectionOnDefocus_)
    {
        clearSelectionOnDefocus_ = enable;
        if (clearSelectionOnDefocus_ && !HasFocus())
            ClearSelection();
    }
}

void ListView::SetSelectOnClickEnd(bool enable)
{
    if (enable != selectOnClickEnd_)
    {
        selectOnClickEnd_ = enable;
        UpdateUIClickSubscription();
    }
}

void ListView::Expand(i32 index, bool enable, bool recursive)
{
    assert(index >= 0);

    if (!hierarchyMode_)
        return;

    i32 numItems = GetNumItems();
    if (index >= numItems)
        return;

    UIElement* item = GetItem(index++);
    SetItemExpanded(item, enable);
    int baseIndent = item->GetIndent();

    Vector<bool> expanded(baseIndent + 1);
    expanded[baseIndent] = enable;

    contentElement_->DisableLayoutUpdate();

    while (index < numItems)
    {
        item = GetItem(index++);
        int indent = item->GetIndent();
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
}

void ListView::ToggleExpand(i32 index, bool recursive)
{
    assert(index >= 0);

    if (!hierarchyMode_)
        return;

    i32 numItems = GetNumItems();
    if (index >= numItems)
        return;

    UIElement* item = GetItem(index);
    Expand(index, !GetItemExpanded(item), recursive);
}

i32 ListView::GetNumItems() const
{
    return contentElement_->GetNumChildren();
}

UIElement* ListView::GetItem(i32 index) const
{
    assert(index >= 0 || index == NINDEX);
    return contentElement_->GetChild(index);
}

Vector<UIElement*> ListView::GetItems() const
{
    Vector<UIElement*> items;
    contentElement_->GetChildren(items);
    return items;
}

i32 ListView::FindItem(UIElement* item) const
{
    if (!item)
        return NINDEX;

    // Early-out by checking if the item belongs to the listview hierarchy at all
    if (item->GetParent() != contentElement_)
        return NINDEX;

    const Vector<SharedPtr<UIElement>>& children = contentElement_->GetChildren();

    // Binary search for list item based on screen coordinate Y
    if (contentElement_->GetLayoutMode() == LM_VERTICAL && item->GetHeight())
    {
        int itemY = item->GetScreenPosition().y_;
        int left = 0;
        int right = children.Size() - 1;
        while (right >= left)
        {
            int mid = (left + right) / 2;
            if (children[mid] == item)
                return mid;
            if (itemY < children[mid]->GetScreenPosition().y_)
                right = mid - 1;
            else
                left = mid + 1;
        }
    }

    // Fallback to linear search in case the coordinates/sizes were not yet initialized
    for (i32 i = 0; i < children.Size(); ++i)
    {
        if (children[i] == item)
            return i;
    }

    return NINDEX;
}

i32 ListView::GetSelection() const
{
    if (selections_.Empty())
        return NINDEX;
    else
        return GetSelections().Front();
}

UIElement* ListView::GetSelectedItem() const
{
    return contentElement_->GetChild(GetSelection());
}

Vector<UIElement*> ListView::GetSelectedItems() const
{
    Vector<UIElement*> ret;

    for (Vector<i32>::ConstIterator i = selections_.Begin(); i != selections_.End(); ++i)
    {
        UIElement* item = GetItem(*i);
        if (item)
            ret.Push(item);
    }

    return ret;
}

void ListView::CopySelectedItemsToClipboard() const
{
    String selectedText;

    for (Vector<i32>::ConstIterator i = selections_.Begin(); i != selections_.End(); ++i)
    {
        // Only handle Text UI element
        auto* text = dynamic_cast<Text*>(GetItem(*i));
        if (text)
            selectedText.Append(text->GetText()).Append("\n");
    }

    GetSubsystem<UI>()->SetClipboardText(selectedText);
}

bool ListView::IsSelected(i32 index) const
{
    assert(index >= 0);
    return selections_.Contains(index);
}

bool ListView::IsExpanded(i32 index) const
{
    assert(index >= 0);
    return GetItemExpanded(contentElement_->GetChild(index));
}

bool ListView::FilterImplicitAttributes(XMLElement& dest) const
{
    if (!ScrollView::FilterImplicitAttributes(dest))
        return false;

    XMLElement childElem = dest.GetChild("element");    // Horizontal scroll bar
    if (!childElem)
        return false;
    childElem = childElem.GetNext("element");           // Vertical scroll bar
    if (!childElem)
        return false;
    childElem = childElem.GetNext("element");           // Scroll panel
    if (!childElem)
        return false;

    XMLElement containerElem = childElem.GetChild("element");   // Item container
    if (!containerElem)
        return false;
    if (!RemoveChildXML(containerElem, "Name", "LV_ItemContainer"))
        return false;
    if (!RemoveChildXML(containerElem, "Is Enabled", "true"))
        return false;
    if (!RemoveChildXML(containerElem, "Layout Mode", "Vertical"))
        return false;
    if (!RemoveChildXML(containerElem, "Size"))
        return false;

    if (hierarchyMode_)
    {
        containerElem = childElem.GetNext("element");           // Overlay container
        if (!containerElem)
            return false;
        if (!RemoveChildXML(containerElem, "Name", "LV_OverlayContainer"))
            return false;
        if (!RemoveChildXML(containerElem, "Clip Children", "true"))
            return false;
        if (!RemoveChildXML(containerElem, "Size"))
            return false;
    }

    return true;
}

void ListView::UpdateSelectionEffect()
{
    i32 numItems = GetNumItems();
    bool highlighted = highlightMode_ == HM_ALWAYS || HasFocus();

    for (i32 i = 0; i < numItems; ++i)
    {
        UIElement* item = GetItem(i);
        if (highlightMode_ != HM_NEVER && selections_.Contains(i))
            item->SetSelected(highlighted);
        else
            item->SetSelected(false);
    }
}

void ListView::EnsureItemVisibility(i32 index)
{
    assert(index >= 0);
    EnsureItemVisibility(GetItem(index));
}

void ListView::EnsureItemVisibility(UIElement* item)
{
    if (!item || !item->IsVisible())
        return;

    IntVector2 newView = GetViewPosition();
    IntVector2 currentOffset = item->GetPosition() - newView;
    const IntRect& clipBorder = scrollPanel_->GetClipBorder();
    IntVector2 windowSize(scrollPanel_->GetWidth() - clipBorder.left_ - clipBorder.right_,
        scrollPanel_->GetHeight() - clipBorder.top_ - clipBorder.bottom_);

    if (currentOffset.y_ < 0)
        newView.y_ += currentOffset.y_;
    if (currentOffset.y_ + item->GetHeight() > windowSize.y_)
        newView.y_ += currentOffset.y_ + item->GetHeight() - windowSize.y_;

    SetViewPosition(newView);
}

void ListView::HandleUIMouseClick(StringHash eventType, VariantMap& eventData)
{
    // Disregard the click end if a drag is going on
    if (selectOnClickEnd_ && GetSubsystem<UI>()->IsDragging())
        return;

    int button = eventData[UIMouseClick::P_BUTTON].GetInt();
    int buttons = eventData[UIMouseClick::P_BUTTONS].GetInt();
    int qualifiers = eventData[UIMouseClick::P_QUALIFIERS].GetInt();

    auto* element = static_cast<UIElement*>(eventData[UIMouseClick::P_ELEMENT].GetPtr());

    // Check if the clicked element belongs to the list
    i32 i = FindItem(element);
    if (i >= GetNumItems() || i == NINDEX)
        return;

    // If not editable, repeat the previous selection. This will send an event and allow eg. a dropdownlist to close
    if (!editable_)
    {
        SetSelections(selections_);
        return;
    }

    if (button == MOUSEB_LEFT)
    {
        // Single selection
        if (!multiselect_ || !qualifiers)
            SetSelection(i);

        // Check multiselect with shift & ctrl
        if (multiselect_)
        {
            if (qualifiers & QUAL_SHIFT)
            {
                if (selections_.Empty())
                    SetSelection(i);
                else
                {
                    i32 first = selections_.Front();
                    i32 last = selections_.Back();
                    Vector<i32> newSelections = selections_;
                    if (i == first || i == last)
                    {
                        for (i32 j = first; j <= last; ++j)
                            newSelections.Push(j);
                    }
                    else if (i < first)
                    {
                        for (i32 j = i; j <= first; ++j)
                            newSelections.Push(j);
                    }
                    else if (i < last)
                    {
                        if ((abs(i - first)) <= (abs(i - last)))
                        {
                            for (i32 j = first; j <= i; ++j)
                                newSelections.Push(j);
                        }
                        else
                        {
                            for (i32 j = i; j <= last; ++j)
                                newSelections.Push(j);
                        }
                    }
                    else if (i > last)
                    {
                        for (i32 j = last; j <= i; ++j)
                            newSelections.Push(j);
                    }
                    SetSelections(newSelections);
                }
            }
            else if (qualifiers & QUAL_CTRL)
                ToggleSelection(i);
        }
    }

    // Propagate the click as an event. Also include right-clicks
    VariantMap& clickEventData = GetEventDataMap();
    clickEventData[ItemClicked::P_ELEMENT] = this;
    clickEventData[ItemClicked::P_ITEM] = element;
    clickEventData[ItemClicked::P_SELECTION] = i;
    clickEventData[ItemClicked::P_BUTTON] = button;
    clickEventData[ItemClicked::P_BUTTONS] = buttons;
    clickEventData[ItemClicked::P_QUALIFIERS] = qualifiers;
    SendEvent(E_ITEMCLICKED, clickEventData);
}

void ListView::HandleUIMouseDoubleClick(StringHash eventType, VariantMap& eventData)
{
    int button = eventData[UIMouseClick::P_BUTTON].GetInt();
    int buttons = eventData[UIMouseClick::P_BUTTONS].GetInt();
    int qualifiers = eventData[UIMouseClick::P_QUALIFIERS].GetInt();

    auto* element = static_cast<UIElement*>(eventData[UIMouseClick::P_ELEMENT].GetPtr());
    // Check if the clicked element belongs to the list
    i32 i = FindItem(element);
    if (i >= GetNumItems())
        return;

    VariantMap& clickEventData = GetEventDataMap();
    clickEventData[ItemDoubleClicked::P_ELEMENT] = this;
    clickEventData[ItemDoubleClicked::P_ITEM] = element;
    clickEventData[ItemDoubleClicked::P_SELECTION] = i;
    clickEventData[ItemDoubleClicked::P_BUTTON] = button;
    clickEventData[ItemDoubleClicked::P_BUTTONS] = buttons;
    clickEventData[ItemDoubleClicked::P_QUALIFIERS] = qualifiers;
    SendEvent(E_ITEMDOUBLECLICKED, clickEventData);
}


void ListView::HandleItemFocusChanged(StringHash eventType, VariantMap& eventData)
{
    using namespace FocusChanged;

    auto* element = static_cast<UIElement*>(eventData[P_ELEMENT].GetPtr());
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

void ListView::HandleFocusChanged(StringHash eventType, VariantMap& eventData)
{
    scrollPanel_->SetSelected(eventType == E_FOCUSED);
    if (clearSelectionOnDefocus_ && eventType == E_DEFOCUSED)
        ClearSelection();
    else if (highlightMode_ == HM_FOCUS)
        UpdateSelectionEffect();
}

void ListView::UpdateUIClickSubscription()
{
    UnsubscribeFromEvent(E_UIMOUSECLICK);
    UnsubscribeFromEvent(E_UIMOUSECLICKEND);
    SubscribeToEvent(selectOnClickEnd_ ? E_UIMOUSECLICKEND : E_UIMOUSECLICK, URHO3D_HANDLER(ListView, HandleUIMouseClick));
}

}
