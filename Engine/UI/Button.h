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

//! A pushbutton image
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
    
    //! Set pressed image offset
    void setPressedOffset(const IntVector2& offset);
    //! Set pressed image offset
    void setPressedOffset(int x, int y);
    //! Set pressed label offset
    void setLabelOffset(const IntVector2& offset);
    //! Set pressed label offset
    void setLabelOffset(int x, int y);
    //! Set pressed event repeat. Rate 0 (default) disables repeat
    void setRepeat(float delay, float rate);
    
    //! Return pressed image offset
    const IntVector2& getPressedOffset() const { return mPressedOffset; }
    //! Return pressed label offset
    const IntVector2& getLabelOffset() const { return mLabelOffset; }
    //! Return repeat delay
    float getRepeatDelay() const { return mRepeatDelay; }
    //! Return repeat rate
    float getRepeatRate() const { return mRepeatRate; }
    
protected:
    //! Set new pressed state
    void setPressed(bool enable);
    
    //! Pressed image offset
    IntVector2 mPressedOffset;
    //! Pressed label offset
    IntVector2 mLabelOffset;
    //! Repeat delay
    float mRepeatDelay;
    //! Repeat rate
    float mRepeatRate;
    //! Repeat timer
    float mRepeatTimer;
    //! Current pressed state
    bool mPressed;
};

#endif // UI_BUTTON_H
