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

#pragma once

#include "ScrollView.h"
#include "HashSet.h"

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
class ListView : public ScrollView
{
    OBJECT(ListView);
    
    using UIElement::SetStyle;
    
public:
    /// Construct.
    ListView(Context* context);
    /// Destruct.
    virtual ~ListView();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// %Set UI element style from XML data.
    virtual void SetStyle(const XMLElement& element);
    /// Perform UI element update.
    virtual void Update(float timeStep);
    /// React to a key press.
    virtual void OnKey(int key, int buttons, int qualifiers);
    /// React to resize.
    virtual void OnResize();
    
    /// Add item to the end of the list.
    void AddItem(UIElement* item);
    /// Insert item at a specific position.
    void InsertItem(unsigned index, UIElement* item);
    /// Remove specific item. In hierarchy mode will also remove any children.
    void RemoveItem(UIElement* item);
    /// Remove item at index. In hierarchy mode will also remove any children.
    void RemoveItem(unsigned index);
    /// Remove all items.
    void RemoveAllItems();
    /// %Set selection.
    void SetSelection(unsigned index);
    /// %Set multiple selected items. If multiselect disabled, sets only the first.
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
    /// %Set selected items' highlight mode.
    void SetHighlightMode(HighlightMode mode);
    /// Enable multiselect.
    void SetMultiselect(bool enable);
    /// Enable hierarchy mode. Allows hiding/showing items that have "indent" userdata.
    void SetHierarchyMode(bool enable);
    /// Enable clearing of selection on defocus.
    void SetClearSelectionOnDefocus(bool enable);
    /// %Set item doubleclick interval in seconds.
    void SetDoubleClickInterval(float interval);
    /// Show or hide child items starting from index. Only has effect in hierarchy mode.
    void SetChildItemsVisible(unsigned index, bool enable);
    /// Show or hide all child items. Only has effect in hierarchy mode.
    void SetChildItemsVisible(bool enable);
    /// Toggle child items' visibility starting from index. Only has effect in hierarchy mode.
    void ToggleChildItemsVisible(unsigned index);
    
    /// Return number of items.
    unsigned GetNumItems() const;
    /// Return item at index.
    UIElement* GetItem(unsigned index) const;
    /// Return all items.
    PODVector<UIElement*> GetItems() const;
    /// Return first selected index, or M_MAX_UNSIGNED if none selected.
    unsigned GetSelection() const;
    /// Return all selected indices.
    PODVector<unsigned> GetSelections() const;
    /// Return first selected item, or null if none selected.
    UIElement* GetSelectedItem() const;
    /// Return all selected items.
    PODVector<UIElement*> GetSelectedItems() const;
    /// Return whether an item at index is seleccted.
    bool IsSelected(unsigned index) const;
    /// Return highlight mode.
    HighlightMode GetHighlightMode() const { return highlightMode_; }
    /// Return whether multiselect enabled.
    bool GetMultiselect() const { return multiselect_; }
    /// Return whether selection is cleared on defocus.
    bool GetClearSelectionOnDefocus() const { return clearSelectionOnDefocus_; }
    /// Return whether hierarchy mode enabled.
    bool GetHierarchyMode() const { return hierarchyMode_; }
    /// Return item doubleclick interval in seconds.
    float GetDoubleClickInterval() const { return doubleClickInterval_; }
    
protected:
    /// Update selection effect when selection or focus changes.
    void UpdateSelectionEffect();
    /// Ensure full visibility of the item.
    void EnsureItemVisibility(unsigned index);
    /// Ensure full visibility of the item.
    void EnsureItemVisibility(UIElement* item);
    
    /// Current selection.
    HashSet<unsigned> selections_;
    /// Highlight mode.
    HighlightMode highlightMode_;
    /// Multiselect flag.
    bool multiselect_;
    /// Hierarchy mode flag.
    bool hierarchyMode_;
    /// Clear selection on defocus flag.
    bool clearSelectionOnDefocus_;
    /// Doubleclick interval.
    float doubleClickInterval_;
    /// Doubleclick timer.
    float doubleClickTimer_;
    /// Last clicked item.
    unsigned lastClickedItem_;
    
private:
    /// %Set multiple selected items, used internally.
    void SetSelections(const HashSet<unsigned>& indices);
    /// Handle global UI mouseclick to check for selection change.
    void HandleUIMouseClick(StringHash eventType, VariantMap& eventData);
    /// Handle global focus change to check whether an invisible item was focused.
    void HandleFocusChanged(StringHash eventType, VariantMap& eventData);
    /// Handle being focused.
    void HandleFocused(StringHash eventType, VariantMap& eventData);
    /// Handle being defocused.
    void HandleDefocused(StringHash eventType, VariantMap& eventData);
};
