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
    //! React to a key press
    virtual void onKey(int key, int buttons, int qualifiers);
    
    //! Add item to the end of the list
    void addItem(UIElement* item);
    //! Add item at index
    void addItem(unsigned index, UIElement* item);
    //! Set item at index, replacing the previous
    void setItem(unsigned index, UIElement* item);
    //! Remove specific item
    void removeItem(UIElement* item);
    //! Remove item at index
    void removeItem(unsigned index);
    //! Remove all elements
    void removeAllItems();
    //! Set selected element
    void setSelection(unsigned index);
    //! Move selection by a delta. Clamp at list ends
    void changeSelection(int delta);
    
    //! Return item at index
    UIElement* getItem(unsigned index) const;
    //! Return whether has a certain item
    bool hasItem(UIElement* item) const;
    //! Return selection index, or M_MAX_UNSIGNED if none selected
    unsigned getSelection() const { return mSelection; }
    //! Return selected item, or null if none selected
    UIElement* getSelectedItem() const;
    
protected:
    //! Update content element when list has changed
    void updateList();
    //! Ensure full visibility of the selected item
    void ensureItemVisibility();
    
    //! List items
    std::vector<SharedPtr<UIElement> > mItems;
    //! Current selection
    unsigned mSelection;
    
private:
    //! Handle focus change to check for selection change
    void handleTryFocus(StringHash eventType, VariantMap& eventData);
};

#endif // UI_LISTVIEW_H
