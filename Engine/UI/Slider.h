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

#ifndef UI_SLIDER_H
#define UI_SLIDER_H

#include "BorderImage.h"

//! An image that contains a slideable child image
class Slider : public BorderImage
{
    DEFINE_TYPE(Slider);
    
public:
    //! Construct with name
    Slider(const std::string& name = std::string());
    //! Destruct
    virtual ~Slider();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! Perform UI element update
    virtual void update(float timeStep);
    //! React to mouse hover
    virtual void onHover(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    //! React to mouse drag start
    virtual void onDragStart(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    //! React to mouse drag motion
    virtual void onDragMove(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    //! React to mouse drag end
    virtual void onDragEnd(const IntVector2& position, const IntVector2& screenPosition);
    
    //! Set orientation
    void setOrientation(UIElementOrientation orientation);
    //! Set slider range maximum value (minimum value is always 0)
    void setRange(float range);
    //! Set slider current value
    void setValue(float value);
    
    //! Return orientation
    UIElementOrientation getOrientation() const { return mOrientation; }
    //! Return slider range
    float getRange() const { return mRange; }
    //! Return slider current value
    float getValue() const { return mValue; }
    //! Return slider image element
    BorderImage* getSliderElement() const { return mSlider; }
    
protected:
    //! Update slider image position & size
    void updateSlider();
    
    //! Slider image
    SharedPtr<BorderImage> mSlider;
    //! Orientation
    UIElementOrientation mOrientation;
    //! Slider range
    float mRange;
    //! Slider current value
    float mValue;
    //! Internal flag of whether the slider is being dragged
    bool mDragSlider;
    //! Original mouse position at drag start
    IntVector2 mOriginalPosition;
    //! Original slider position at drag start
    IntVector2 mOriginalSliderPosition;
};

#endif // UI_SLIDER_H
