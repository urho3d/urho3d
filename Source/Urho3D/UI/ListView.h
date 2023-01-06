// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../Input/InputConstants.h"
#include "../UI/ScrollView.h"

namespace Urho3D
{

/// %ListView selection highlight mode.
enum HighlightMode
{
    /// Never highlight selections.
    HM_NEVER,
    /// Highlight when focused.
    HM_FOCUS,
    /// Highlight always.
    HM_ALWAYS
};

/// Scrollable list %UI element.
class URHO3D_API ListView : public ScrollView
{
    URHO3D_OBJECT(ListView, ScrollView);

public:
    /// Construct.
    explicit ListView(Context* context);
    /// Destruct.
    ~ListView() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// React to a key press.
    void OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override;
    /// React to resize.
    void OnResize(const IntVector2& newSize, const IntVector2& delta) override;

    /// Manually update layout on internal elements.
    void UpdateInternalLayout();
    /// Disable automatic layout update for internal elements.
    void DisableInternalLayoutUpdate();
    /// Enable automatic layout update for internal elements.
    void EnableInternalLayoutUpdate();

    /// Add item to the end of the list.
    void AddItem(UIElement* item);

    /// \brief Insert item at a specific index. In hierarchy mode, the optional parameter will be used to determine the child's indent level in respect to its parent.
    /// If index is greater than the total items then the new item is inserted at the end of the list.
    /// In hierarchy mode, if index is greater than the index of last children of the specified parent item then the new item is inserted next to the last children.
    /// And if the index is lesser than the index of the parent item itself then the new item is inserted before the first child item.
    /// index can be ENDPOS.
    void InsertItem(i32 index, UIElement* item, UIElement* parentItem = nullptr);

    /// Remove specific item, starting search at the specified index if provided. In hierarchy mode will also remove any children.
    void RemoveItem(UIElement* item, i32 index = 0);
    /// Remove item at index. In hierarchy mode will also remove any children.
    void RemoveItem(i32 index);
    /// Remove all items.
    void RemoveAllItems();
    /// Set selection.
    /// @property
    void SetSelection(i32 index);
    /// Set multiple selected items. If multiselect disabled, sets only the first.
    void SetSelections(const Vector<i32>& indices);
    /// Add item to the selection, multiselect mode only.
    void AddSelection(i32 index);
    /// Remove item from the selection.
    void RemoveSelection(i32 index);
    /// Toggle selection of an item.
    void ToggleSelection(i32 index);
    /// Move selection by a delta and clamp at list ends. If additive (multiselect only), will add to the existing selection.
    void ChangeSelection(int delta, bool additive = false);
    /// Clear selection.
    void ClearSelection();
    /// Set selected items' highlight mode.
    /// @property
    void SetHighlightMode(HighlightMode mode);
    /// Enable multiselect.
    /// @property
    void SetMultiselect(bool enable);
    /// \brief Enable hierarchy mode. Allows items to have parent-child relationship at different indent level and the ability to expand/collapse child items.
    /// All items in the list will be lost during mode change.
    /// @property
    void SetHierarchyMode(bool enable);
    /// Set base indent, i.e. the indent level of the ultimate parent item.
    /// @property
    void SetBaseIndent(int baseIndent);
    /// Enable clearing of selection on defocus.
    /// @property
    void SetClearSelectionOnDefocus(bool enable);
    /// Enable reacting to click end instead of click start for item selection. Default false.
    /// @property
    void SetSelectOnClickEnd(bool enable);

    /// Expand item at index. Only has effect in hierarchy mode.
    void Expand(i32 index, bool enable, bool recursive = false);
    /// Toggle item's expanded flag at index. Only has effect in hierarchy mode.
    void ToggleExpand(i32 index, bool recursive = false);

    /// Return number of items.
    /// @property
    i32 GetNumItems() const;
    /// Return item at index.
    /// @property{get_items}
    UIElement* GetItem(i32 index) const;
    /// Return all items.
    Vector<UIElement*> GetItems() const;
    /// Return index of item, or NINDEX If not found.
    i32 FindItem(UIElement* item) const;
    /// Return first selected index, or NINDEX if none selected.
    /// @property
    i32 GetSelection() const;

    /// Return all selected indices.
    /// @property
    const Vector<i32>& GetSelections() const { return selections_; }

    /// Copy selected items to system clipboard. Currently only applicable to Text items.
    void CopySelectedItemsToClipboard() const;
    /// Return first selected item, or null if none selected.
    /// @property
    UIElement* GetSelectedItem() const;
    /// Return all selected items.
    /// @property
    Vector<UIElement*> GetSelectedItems() const;
    /// Return whether an item at index is selected.
    bool IsSelected(i32 index) const;
    /// Return whether an item at index has its children expanded (in hierarchy mode only).
    bool IsExpanded(i32 index) const;

    /// Return highlight mode.
    /// @property
    HighlightMode GetHighlightMode() const { return highlightMode_; }

    /// Return whether multiselect enabled.
    /// @property
    bool GetMultiselect() const { return multiselect_; }

    /// Return whether selection is cleared on defocus.
    /// @property
    bool GetClearSelectionOnDefocus() const { return clearSelectionOnDefocus_; }

    /// Return whether reacts to click end instead of click start for item selection.
    /// @property
    bool GetSelectOnClickEnd() const { return selectOnClickEnd_; }

    /// Return whether hierarchy mode enabled.
    /// @property
    bool GetHierarchyMode() const { return hierarchyMode_; }

    /// Return base indent.
    /// @property
    int GetBaseIndent() const { return baseIndent_; }

    /// Ensure full visibility of the item.
    void EnsureItemVisibility(i32 index);
    /// Ensure full visibility of the item.
    void EnsureItemVisibility(UIElement* item);

protected:
    /// Filter implicit attributes in serialization process.
    bool FilterImplicitAttributes(XMLElement& dest) const override;
    /// Update selection effect when selection or focus changes.
    void UpdateSelectionEffect();

    /// Current selection.
    Vector<i32> selections_;
    /// Highlight mode.
    HighlightMode highlightMode_;
    /// Multiselect flag.
    bool multiselect_;
    /// Hierarchy mode flag.
    bool hierarchyMode_;
    /// Base indent, used in hierarchy mode only.
    int baseIndent_;
    /// Overlay container, used in hierarchy mode only.
    SharedPtr<UIElement> overlayContainer_;
    /// Clear selection on defocus flag.
    bool clearSelectionOnDefocus_;
    /// React to click end instead of click start flag.
    bool selectOnClickEnd_;

private:
    /// Handle global UI mouseclick to check for selection change.
    void HandleUIMouseClick(StringHash eventType, VariantMap& eventData);
    /// Handle global UI mouse doubleclick.
    void HandleUIMouseDoubleClick(StringHash eventType, VariantMap& eventData);
    /// Handle global focus change to check whether an invisible item was focused.
    void HandleItemFocusChanged(StringHash eventType, VariantMap& eventData);
    /// Handle focus changed.
    void HandleFocusChanged(StringHash eventType, VariantMap& eventData);
    /// Update subscription to UI click events.
    void UpdateUIClickSubscription();
};

}
