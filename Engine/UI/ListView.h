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
    //! Remove specific item
    void removeItem(UIElement* item);
    //! Remove item at index
    void removeItem(unsigned index);
    //! Remove all items
    void removeAllItems();
    //! Set selection
    void setSelection(unsigned index);
    //! Move selection by a delta and clamp at list ends
    void changeSelection(int delta);
    //! Clear selection
    void clearSelection();
    //! Set whether to show selection even when defocused, default false
    void setShowSelectionAlways(bool enable);
    //! Set item doubleclick interval in seconds
    void setDoubleClickInterval(float interval);
    
    //! Return number of items
    unsigned getNumItems() const;
    //! Return item at index
    UIElement* getItem(unsigned index) const;
    //! Return all items
    std::vector<UIElement*> getItems() const;
    //! Return selection index, or M_MAX_UNSIGNED if none selected
    unsigned getSelection() const { return mSelection; }
    //! Return selected item, or null if none selected
    UIElement* getSelectedItem() const;
    //! Return whether to show selection even when defocused
    bool getShowSelectionAlways() const { return mShowSelectionAlways; }
    //! Return item doubleclick interval in seconds
    float getDoubleClickInterval() const { return mDoubleClickInterval; }
    
protected:
    //! Update selection effect when selection or focus changes
    void updateSelectionEffect();
    //! Ensure full visibility of the selected item
    void ensureItemVisibility();
    
    //! Current selection
    unsigned mSelection;
    //! Show selection even when defocused flag
    bool mShowSelectionAlways;
    //! Doubleclick interval
    float mDoubleClickInterval;
    //! Doubleclick timer
    float mDoubleClickTimer;
    
private:
    //! Handle focus change to check for selection change
    void handleTryFocus(StringHash eventType, VariantMap& eventData);
};

#endif // UI_LISTVIEW_H
