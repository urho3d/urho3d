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

#include "Menu.h"

class ListView;

//! A menu item which displays a popup list view
class DropDownList : public Menu
{
    DEFINE_TYPE(DropDownList)
    
    using UIElement::setStyle;
    
public:
    //! Construct with name
    DropDownList(const std::string& name = std::string());
    //! Destruct
    ~DropDownList();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! Return UI rendering batches
    virtual void getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor);
    //! React to the popup being shown
    virtual void onShowPopup();
    
    //! Add item to the end of the list
    void addItem(UIElement* item);
    //! Insert item to a specific position
    void insertItem(unsigned index, UIElement* item);
    //! Remove specific item
    void removeItem(UIElement* item);
    //! Remove item at index
    void removeItem(unsigned index);
    //! Remove all items
    void removeAllItems();
    //! Set selection
    void setSelection(unsigned index);
    //! Set whether popup should be automatically resized to match the dropdown button width
    void setResizePopup(bool enable);
    
    //! Return number of items
    unsigned getNumItems() const;
    //! Return item at index
    UIElement* getItem(unsigned index) const;
    //! Return all items
    std::vector<UIElement*> getItems() const;
    //! Return selection index, or M_MAX_UNSIGNED if none selected
    unsigned getSelection() const;
    //! Return selected item, or null if none selected
    UIElement* getSelectedItem() const;
    //! Return listview element
    ListView* getListView() const { return mListView; }
    //! Return selected item placeholder element
    UIElement* getPlaceholder() const { return mPlaceholder; }
    //! Return whether popup should be automatically resized
    bool getResizePopup() const { return mResizePopup; }
    
protected:
    //! Listview element
    SharedPtr<ListView> mListView;
    //! Selected item placeholder element
    SharedPtr<UIElement> mPlaceholder;
    //! Resize popup flag
    bool mResizePopup;
    
private:
    //! Handle listview item selected event
    void handleItemSelected(StringHash eventType, VariantMap& eventData);
};
