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

#ifndef UI_LISTVIEW_H
#define UI_LISTVIEW_H

#include "ScrollView.h"

#include <set>

//! ListView selection highlight mode
enum HighlightMode
{
    //! Never highlight selections
    HM_NEVER,
    //! Highlight when focused
    HM_FOCUS,
    //! Highlight always
    HM_ALWAYS
};

//! A scrollable list
class ListView : public ScrollView
{
    DEFINE_TYPE(ListView);
    
public:
    //! Construct with name
    ListView(const std::string& name = std::string());
    //! Destruct
    virtual ~ListView();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! Perform UI element update
    virtual void update(float timeStep);
    //! React to a key press
    virtual void onKey(int key, int buttons, int qualifiers);
    //! React to resize
    virtual void onResize();
    //! React to defocus
    virtual void onDefocus();
    //! React to focus
    virtual void onFocus();
    
    //! Add item to the end of the list
    void addItem(UIElement* item);
    //! Remove specific item. In hierarchy mode will also remove any children
    void removeItem(UIElement* item);
    //! Remove item at index. In hierarchy mode will also remove any children
    void removeItem(unsigned index);
    //! Remove all items
    void removeAllItems();
    //! Set selection
    void setSelection(unsigned index);
    //! Set multiple selected items. If multiselect disabled, sets only the first
    void setSelections(const std::set<unsigned>& indices);
    //! Add item to the selection, multiselect mode only
    void addSelection(unsigned index);
    //! Remove item from the selection
    void removeSelection(unsigned index);
    //! Toggle selection of an item
    void toggleSelection(unsigned index);
    //! Move selection by a delta and clamp at list ends. If additive (multiselect only), will add to the existing selection
    void changeSelection(int delta, bool additive = false);
    //! Clear selection
    void clearSelection();
    //! Set selected items' highlight mode
    void setHighlightMode(HighlightMode mode);
    //! Enable multiselect
    void setMultiselect(bool enable);
    //! Enable hierarchy mode. Allows hiding/showing items that have "indent" userdata
    void setHierarchyMode(bool enable);
    //! Set item doubleclick interval in seconds
    void setDoubleClickInterval(float interval);
    //! Show or hide child items starting from index. Only has effect in hierarchy mode
    void setChildItemsVisible(unsigned index, bool enable);
    //! Toggle child items' visibility starting from index. Only has effect in hierarchy mode
    void toggleChildItemsVisible(unsigned index);
    
    //! Return number of items
    unsigned getNumItems() const;
    //! Return item at index
    UIElement* getItem(unsigned index) const;
    //! Return all items
    std::vector<UIElement*> getItems() const;
    //! Return first selected index, or M_MAX_UNSIGNED if none selected
    unsigned getSelection() const;
    //! Return all selected indices
    std::set<unsigned> getSelections() const { return mSelections; }
    //! Return first selected item, or null if none selected
    UIElement* getSelectedItem() const;
    //! Return all selected items
    std::vector<UIElement*> getSelectedItems() const;
    //! Return highlight mode
    HighlightMode getHighlightMode() const { return mHighlightMode; }
    //! Return whether multiselect enabled
    bool getMultiselect() const { return mMultiselect; }
    //! Return whether hierarchy mode enabled
    bool getHierarchyMode() const { return mHierarchyMode; }
    //! Return item doubleclick interval in seconds
    float getDoubleClickInterval() const { return mDoubleClickInterval; }
    
protected:
    //! Update selection effect when selection or focus changes
    void updateSelectionEffect();
    //! Ensure full visibility of the item
    void ensureItemVisibility(unsigned index);
    
    //! Current selection
    std::set<unsigned> mSelections;
    //! Highlight mode
    HighlightMode mHighlightMode;
    //! Multiselect flag
    bool mMultiselect;
    //! Hierarchy mode flag
    bool mHierarchyMode;
    //! Doubleclick interval
    float mDoubleClickInterval;
    //! Doubleclick timer
    float mDoubleClickTimer;
    //! Last clicked item
    unsigned mLastClickedItem;
    
private:
    //! Handle global UI mouseclick to check for selection change
    void handleUIMouseClick(StringHash eventType, VariantMap& eventData);
};

#endif // UI_LISTVIEW_H
