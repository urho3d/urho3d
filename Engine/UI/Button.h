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

//! Button UI element states
enum ButtonState
{
    BUTTON_INACTIVE = 0,
    BUTTON_HOVER,
    BUTTON_PRESSED
};

//! An image that reacts to mouse presses
class Button : public BorderImage
{
public:
    //! Construct with name
    Button(const std::string& name = std::string());
    //! Destruct
    virtual ~Button();
    
    //! Load parameters from an XML file
    virtual XMLElement loadParameters(XMLFile* file, const std::string& elementName, ResourceCache* cache);
    //! Perform UI element update
    virtual void update(float timeStep);
    //! Return UI rendering batches
    virtual void getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor);
    //! React to mouse hover
    virtual void onHover(const IntVector2& position, const IntVector2& screenPosition);
    //! React to mouse click
    virtual void onClick(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    
    //! Set inactive image rectangle
    void setInactiveRect(const IntRect& rect);
    //! Set inactive image rectangle
    void setInactiveRect(int left, int top, int right, int bottom);
    //! Set hovering image rectangle
    void setHoverRect(const IntRect& rect);
    //! Set hovering image rectangle
    void setHoverRect(int left, int top, int right, int bottom);
    //! Set pressed image rectangle
    void setPressedRect(const IntRect& rect);
    //! Set pressed image rectangle
    void setPressedRect(int left, int top, int right, int bottom);
    //! Set hovering image delay
    void setHoverDelay(float delay);
    //! Set pressed image delay
    void setPressedDelay(float delay);
    //! Set optional label UI element
    void setLabel(UIElement* label);
    
    //! Return inactive image rectangle
    const IntRect& getInactiveRect() const { return mInactiveRect; }
    //! Return hovering image rectangle
    const IntRect& getHoverRect() const { return mHoverRect; }
    //! Return pressed image rectangle
    const IntRect& getPressedRect() const { return mPressedRect; }
    //! Return hovering image delay
    float getHoverDelay() const { return mHoverDelay; }
    //! Return pressed image delay
    float getPressedDelay() const { return mPressedDelay; }
    //! Return label UI element
    UIElement* getLabel() const { return mLabel; }
    
protected:
    //! Label UI element
    SharedPtr<UIElement> mLabel;
    //! Inactive image rectangle
    IntRect mInactiveRect;
    //! Hovering image rectangle
    IntRect mHoverRect;
    //! Pressed image rectangle
    IntRect mPressedRect;
    //! Hovering image delay
    float mHoverDelay;
    //! Pressed image delay
    float mPressedDelay;
    //! State timer
    float mStateTime;
    //! Current state
    ButtonState mState;
    //! Hovering flag
    bool mHoveringThisFrame;
};

#endif // UI_BUTTON_H
