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

#ifndef UI_MENUITEM_H
#define UI_MENUITEM_H

#include "Button.h"

//! A button that either triggers a menu selection or shows a popup element
class MenuItem : public Button
{
    DEFINE_TYPE(MenuItem);
    
    //! Construct with name
    MenuItem(const std::string& name = std::string());
    //! Destruct
    virtual ~MenuItem();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! Perform UI element update
    virtual void update(float timeStep);
    //! React to mouse hover
    virtual void onHover(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    //! React to mouse click
    virtual void onClick(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    
    //! Set popup element to show on selection
    void setPopup(UIElement* element);
    //! Set popup element offset
    void setPopupOffset(const IntVector2& offset);
    //! Set popup element offset
    void setPopupOffset(int x, int y);
    //! Force the popup to show or hide
    void showPopup(bool enable);
    
    //! Return popup element
    UIElement* getPopup() const { return mPopup; }
    //! Return popup element offset
    const IntVector2& getPopupOffset() const { return mPopupOffset; }
    //! Return whether popup is open
    bool getShowPopup() const { return mShowPopup; }
    
protected:
    //! Popup element
    SharedPtr<UIElement> mPopup;
    //! Popup element offset
    IntVector2 mPopupOffset;
    //! Show popup flag
    bool mShowPopup;
    
private:
    //! Handle focus change attempt in case the popup needs to be hidden
    void handleTryFocus(StringHash eventType, VariantMap& eventData);
};

#endif // UI_MENUITEM_H
