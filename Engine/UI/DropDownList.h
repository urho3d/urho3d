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

#pragma once

#include "Menu.h"

class ListView;

/// %Menu %UI element that displays a popup list view.
class DropDownList : public Menu
{
    OBJECT(DropDownList)
    
    using UIElement::SetStyle;
    
public:
    /// Construct.
    DropDownList(Context* context);
    /// Destruct.
    ~DropDownList();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// %Set UI element style from XML data.
    virtual void SetStyle(const XMLElement& element);
    /// Return UI rendering batches.
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<UIQuad>& quads, const IntRect& currentScissor);
    /// React to the popup being shown.
    virtual void OnShowPopup();
    
    /// Add item to the end of the list.
    void AddItem(UIElement* item);
    /// Insert item to a specific position.
    void InsertItem(unsigned index, UIElement* item);
    /// Remove specific item.
    void RemoveItem(UIElement* item);
    /// Remove item at index.
    void RemoveItem(unsigned index);
    /// Remove all items.
    void RemoveAllItems();
    /// %Set selection.
    void SetSelection(unsigned index);
    /// %Set whether popup should be automatically resized to match the dropdown button width.
    void SetResizePopup(bool enable);
    
    /// Return number of items.
    unsigned GetNumItems() const;
    /// Return item at index.
    UIElement* GetItem(unsigned index) const;
    /// Return all items.
    PODVector<UIElement*> GetItems() const;
    /// Return selection index, or M_MAX_UNSIGNED if none selected.
    unsigned GetSelection() const;
    /// Return selected item, or null if none selected.
    UIElement* GetSelectedItem() const;
    /// Return listview element.
    ListView* GetListView() const { return listView_; }
    /// Return selected item placeholder element.
    UIElement* GetPlaceholder() const { return placeholder_; }
    /// Return whether popup should be automatically resized.
    bool GetResizePopup() const { return resizePopup_; }
    
protected:
    /// Listview element.
    SharedPtr<ListView> listView_;
    /// Selected item placeholder element.
    SharedPtr<UIElement> placeholder_;
    /// Resize popup flag.
    bool resizePopup_;
    
private:
    /// Handle listview item selected event.
    void HandleItemSelected(StringHash eventType, VariantMap& eventData);
};
