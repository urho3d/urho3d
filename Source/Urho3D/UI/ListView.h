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
    bool AddItem(UIElement* item);
    /// \brief Insert item at a specific index. In hierarchy mode, the optional parameter will be used to determine the child's indent level in respect to its parent.
    /// If index is greater than the total items then the new item is inserted at the end of the list.
    /// In hierarchy mode, if index is greater than the index of last children of the specified parent item then the new item is inserted next to the last children.
    /// And if the index is lesser than the index of the parent item itself then the new item is inserted before the first child item.
    bool InsertItem(unsigned index, UIElement* item, UIElement* parentItem = nullptr);
    /// Remove specific item, starting search at the specified index if provided. In hierarchy mode will also remove any children.
    bool RemoveItem(UIElement* item, unsigned index = 0);
    /// Remove item at index. In hierarchy mode will also remove any children.
    bool RemoveItem(unsigned index);
    /// Remove all items.
    void RemoveAllItems();
    /// Set selection.
    void SetSelection(unsigned index);
    /// Set multiple selected items. If multiselect disabled, sets only the first.
    void SetSelections(const PODVector<unsigned>& indices);
    /// Add item to the selection, multiselect mode only.
    void AddSelection(unsigned index);
    /// Remove item from the selection.
    void RemoveSelection(unsigned index);
    /// Toggle selection of an item.
    void ToggleSelection(unsigned index);
    /// Move selection by a delta and clamp at list ends. If additive (multiselect only), will add to the existing selection.
    void ChangeSelection(int delta, bool additive = false);
    /// Clear selection.
    void ClearSelection();
    /// Set selected items' highlight mode.
    void SetHighlightMode(HighlightMode mode);
    /// Enable multiselect.
    void SetMultiselect(bool enable);
    /// \brief Enable hierarchy mode. Allows items to have parent-child relationship at different indent level and the ability to expand/collapse child items.
    /// All items in the list will be lost during mode change.
    void SetHierarchyMode(bool enable);
    /// Set base indent, i.e. the indent level of the ultimate parent item.
    void SetBaseIndent(int baseIndent);
    /// Enable clearing of selection on defocus.
    void SetClearSelectionOnDefocus(bool enable);
    /// Enable reacting to click end instead of click start for item selection. Default false.
    void SetSelectOnClickEnd(bool enable);

    /// Expand item at index. Only has effect in hierarchy mode.
    void Expand(unsigned index, bool enable, bool recursive = false);
    /// Toggle item's expanded flag at index. Only has effect in hierarchy mode.
    void ToggleExpand(unsigned index, bool recursive = false);

    /// Return number of items.
    unsigned GetNumItems() const;
    /// Return item at index.
    UIElement* GetItem(unsigned index) const;
    /// Return all items.
    PODVector<UIElement*> GetItems() const;
    /// Return index of item, or M_MAX_UNSIGNED If not found.
    unsigned FindItem(UIElement* item) const;
    /// Return first selected index, or M_MAX_UNSIGNED if none selected.
    unsigned GetSelection() const;

    /// Return all selected indices.
    const PODVector<unsigned>& GetSelections() const { return selections_; }

    /// Copy selected items to system clipboard. Currently only applicable to Text items.
    void CopySelectedItemsToClipboard() const;
    /// Return first selected item, or null if none selected.
    UIElement* GetSelectedItem() const;
    /// Return all selected items.
    PODVector<UIElement*> GetSelectedItems() const;
    /// Return whether an item at index is selected.
    bool IsSelected(unsigned index) const;
    /// Return whether an item at index has its children expanded (in hierarchy mode only).
    bool IsExpanded(unsigned index) const;

    /// Return highlight mode.
    HighlightMode GetHighlightMode() const { return highlightMode_; }

    /// Return whether multiselect enabled.
    bool GetMultiselect() const { return multiselect_; }

    /// Return whether selection is cleared on defocus.
    bool GetClearSelectionOnDefocus() const { return clearSelectionOnDefocus_; }

    /// Return whether reacts to click end instead of click start for item selection.
    bool GetSelectOnClickEnd() const { return selectOnClickEnd_; }

    /// Return whether hierarchy mode enabled.
    bool GetHierarchyMode() const { return hierarchyMode_; }

    /// Return base indent.
    int GetBaseIndent() const { return baseIndent_; }

    /// Ensure full visibility of the item.
    void EnsureItemVisibility(unsigned index);
    /// Ensure full visibility of the item.
    void EnsureItemVisibility(UIElement* item);

protected:
    /// Filter implicit attributes in serialization process.
    bool FilterImplicitAttributes(XMLElement& dest) const override;
    /// Update selection effect when selection or focus changes.
    void UpdateSelectionEffect();

    /// Current selection.
    PODVector<unsigned> selections_;
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
