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

#ifndef UI_SCROLLBAR_H
#define UI_SCROLLBAR_H

#include "UIElement.h"

class Button;
class Slider;

//! A slider bar with forward and back buttons
class ScrollBar : public UIElement
{
    DEFINE_TYPE(ScrollBar);
    
    using UIElement::setStyle;
    
public:
    //! Construct with name
    ScrollBar(const std::string& name = std::string());
    //! Destruct
    virtual ~ScrollBar();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! React to resize
    virtual void onResize();
    
    //! Set orientation type
    void setOrientation(Orientation orientation);
    //! Set slider range maximum value (minimum value is always 0)
    void setRange(float range);
    //! Set slider current value
    void setValue(float value);
    //! Change slider current value by a delta
    void changeValue(float delta);
    //! Set button scroll step
    void setScrollStep(float step);
    //! Set button step factor, can be used to adjust the step for constant pixel size
    void setStepFactor(float factor);
    //! Scroll back one step
    void stepBack();
    //! Scroll forward one step
    void stepForward();
    
    //! Return orientation type
    Orientation getOrientation() const;
    //! Return slider range
    float getRange() const;
    //! Return slider current value
    float getValue() const;
    //! Return button scroll step
    float getScrollStep() const { return mScrollStep; }
    //! Return button step factor
    float getStepFactor() const { return mStepFactor; }
    //! Return scroll step multiplied by factor
    float getEffectiveScrollStep() const;
    //! Return back button element
    Button* getBackButton() const { return mBackButton; }
    //! Return forward button element
    Button* getForwardButton() const { return mForwardButton; }
    //! Return slider element
    Slider* getSlider() const { return mSlider; }
    
protected:
    //! Back button
    SharedPtr<Button> mBackButton;
    //! Forward button
    SharedPtr<Button> mForwardButton;
    //! Slider
    SharedPtr<Slider> mSlider;
    //! Scroll step
    float mScrollStep;
    //! Step factor
    float mStepFactor;
    //! Left button image rect
    IntRect mLeftRect;
    //! Right button image rect
    IntRect mRightRect;
    //! Up button image rect
    IntRect mUpRect;
    //! Down button image rect
    IntRect mDownRect;
    
private:
    //! Handle back button pressed
    void handleBackButtonPressed(StringHash eventType, VariantMap& eventData);
    //! Handle forward button pressed
    void handleForwardButtonPressed(StringHash eventType, VariantMap& eventData);
    //! Handle slider movement
    void handleSliderChanged(StringHash eventType, VariantMap& eventData);
};

#endif // UI_SCROLLBAR_H
