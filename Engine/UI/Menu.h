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

#ifndef UI_MENU_H
#define UI_MENU_H

#include "Button.h"

//! A menu element that optionally shows a popup
class Menu : public Button
{
    DEFINE_TYPE(Menu);
    
    //! Construct with name
    Menu(const std::string& name = std::string());
    //! Destruct
    virtual ~Menu();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! React to mouse click
    virtual void onClick(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers);
    //! React to resize
    virtual void onResize();
    
    //! Set popup element to show on selection
    void setPopup(UIElement* element);
    //! Set popup element offset
    void setPopupOffset(const IntVector2& offset);
    //! Set popup element offset
    void setPopupOffset(int x, int y);
    //! Set whether automatically resizes the popup to match width
    void setResizePopup(bool enable);
    //! Force the popup to show or hide
    void showPopup(bool enable);
    
    //! Return popup element
    UIElement* getPopup() const { return mPopup; }
    //! Return popup element offset
    const IntVector2& getPopupOffset() const { return mPopupOffset; }
    //! Return whether popup is open
    bool getShowPopup() const { return mShowPopup; }
    //! Return whether automatically resizes the popup
    bool getResizePopup() const { return mResizePopup; }
    
protected:
    //! Popup element
    SharedPtr<UIElement> mPopup;
    //! Popup element offset
    IntVector2 mPopupOffset;
    //! Show popup flag
    bool mShowPopup;
    //! Resize popup automatically flag
    bool mResizePopup;
    
private:
    //! Handle focus change attempt in case the popup needs to be hidden
    void handleTryFocus(StringHash eventType, VariantMap& eventData);
};

#endif // UI_MENU_H
