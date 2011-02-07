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

#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "BorderImage.h"

//! An image that reacts to mouse presses
class Button : public BorderImage
{
    DEFINE_TYPE(Button);
    
public:
    //! Construct with name
    Button(const std::string& name = std::string());
    //! Destruct
    virtual ~Button();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! Perform UI element update
    virtual void update(float timeStep);
    //! Return UI rendering batches
    virtual void getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor);
    //! React to mouse hover
    virtual void onHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers);
    //! React to mouse click
    virtual void onClick(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers);
    
    //! Set inactive image rectangle
    void setInactiveRect(const IntRect& rect);
    //! Set inactive image rectangle
    void setInactiveRect(int left, int top, int right, int bottom);
    //! Set pressed image rectangle
    void setPressedRect(const IntRect& rect);
    //! Set pressed image rectangle
    void setPressedRect(int left, int top, int right, int bottom);
    //! Set label offset on press
    void setLabelOffset(const IntVector2& offset);
    //! Set label offset on press
    void setLabelOffset(int x, int y);
    
    //! Return inactive image rectangle
    const IntRect& getInactiveRect() const { return mInactiveRect; }
    //! Return pressed image rectangle
    const IntRect& getPressedRect() const { return mPressedRect; }
    //! Return label offset on press
    const IntVector2& getLabelOffset() const { return mLabelOffset; }
    
protected:
    //! Set new pressed state
    void setPressed(bool enable);
    
    //! Inactive image rectangle
    IntRect mInactiveRect;
    //! Pressed image rectangle
    IntRect mPressedRect;
    //! Label offset on press
    IntVector2 mLabelOffset;
    //! Current pressed state
    bool mPressed;
};

#endif // UI_BUTTON_H
