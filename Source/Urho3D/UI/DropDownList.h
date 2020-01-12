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

#pragma once

#include "../UI/Menu.h"

namespace Urho3D
{

class ListView;

/// %Menu %UI element that displays a popup list view.
class URHO3D_API DropDownList : public Menu
{
    URHO3D_OBJECT(DropDownList, Menu)

public:
    /// Construct.
    explicit DropDownList(Context* context);
    /// Destruct.
    ~DropDownList() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately.
    void ApplyAttributes() override;
    /// Return UI rendering batches.
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
    /// React to the popup being shown.
    void OnShowPopup() override;
    /// React to the popup being hidden.
    void OnHidePopup() override;
    /// React to editable status change.
    void OnSetEditable() override;

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
    /// Set selection.
    void SetSelection(unsigned index);
    /// Set place holder text. This is the text shown when there is no selection (-1) in drop down list. Note that if the list has items, the default is to show the first item, so the "no selection" state has to be set explicitly.
    void SetPlaceholderText(const String& text);
    /// Set whether popup should be automatically resized to match the dropdown button width.
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

    /// Return place holder text.
    const String& GetPlaceholderText() const;

    /// Return whether popup should be automatically resized.
    bool GetResizePopup() const { return resizePopup_; }

    /// Set selection attribute.
    void SetSelectionAttr(unsigned index);

protected:
    /// Filter implicit attributes in serialization process.
    bool FilterImplicitAttributes(XMLElement& dest) const override;
    /// Filter implicit attributes in serialization process.
    bool FilterPopupImplicitAttributes(XMLElement& dest) const override;

    /// Listview element.
    SharedPtr<ListView> listView_;
    /// Selected item placeholder element.
    SharedPtr<UIElement> placeholder_;
    /// Resize popup flag.
    bool resizePopup_;

private:
    /// Handle listview item click event.
    void HandleItemClicked(StringHash eventType, VariantMap& eventData);
    /// Handle a key press from the listview.
    void HandleListViewKey(StringHash eventType, VariantMap& eventData);
    /// Handle the listview selection change. Set placeholder text hidden/visible as necessary.
    void HandleSelectionChanged(StringHash eventType, VariantMap& eventData);

    /// Selected item index attribute.
    unsigned selectionAttr_;
};

}
