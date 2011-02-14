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

#ifndef UI_SCROLLVIEW_H
#define UI_SCROLLVIEW_H

#include "BorderImage.h"

class ScrollBar;

//! A scrollable view for showing child widgets
class ScrollView : public BorderImage
{
    DEFINE_TYPE(ScrollView);
    
public:
    //! Construct with name
    ScrollView(const std::string& name = std::string());
    //! Destruct
    virtual ~ScrollView();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! React to a key press
    virtual void onKey(int key, int buttons, int qualifiers);
    //! React to gaining focus
    virtual void onFocus();
    //! React to losing focus
    virtual void onDefocus();
    //! React to resize
    virtual void onResize();
    
    //! Set view offset from the top-left corner
    void setViewPosition(const IntVector2& position);
    //! Set view offset from the top-left corner
    void setViewPosition(int x, int y);
    //! Set total view size
    void setViewSize(const IntVector2& position);
    //! Set total view size
    void setViewSize(int x, int y);
    //! Set horizontal scroll bar
    void setHorizontalScrollBar(ScrollBar* scrollBar);
    //! Set vertical scroll bar
    void setVerticalScrollBar(ScrollBar* scrollBar);
    //! Set arrow key scroll step
    void setScrollStep(float step);
    //! Set arrow key page step
    void setPageStep(float step);
    
    //! Return view offset from the top-left corner
    const IntVector2& getViewPosition() const { return mViewPosition; }
    //! Return total view size
    const IntVector2& getViewSize() const { return mViewSize; }
    //! Return horizontal scroll bar
    ScrollBar* getHorizontalScrollBar() const { return mHorizontalScrollBar; }
    //! Return vertical scroll bar
    ScrollBar* getVerticalScrollBar() const { return mVerticalScrollBar; }
    //! Return arrow key scroll step
    float getScrollStep() const { return mScrollStep; }
    //! Return arrow key page step
    float getPageStep() const { return mPageStep; }
    
protected:
    //! Update the view from scrollbars if available
    void updateViewFromScrollBars();
    //! Update the scrollbars' ranges and positions
    void updateScrollBars();
    //! Limit and update view with a new position
    void updateView(const IntVector2& position);
    
    //! Horizontal scroll bar
    WeakPtr<ScrollBar> mHorizontalScrollBar;
    //! Vertical scroll bar
    WeakPtr<ScrollBar> mVerticalScrollBar;
    //! Current view offset from the top-left corner
    IntVector2 mViewPosition;
    //! Total view size
    IntVector2 mViewSize;
    //! Arrow key scroll step
    float mScrollStep;
    //! Arrow key page step
    float mPageStep;
    //! Ignore scrollbar events flag. Used to prevent possible endless loop when setting position
    bool mIgnoreEvents;
    
private:
    //! Handle scrollbar value changed
    void handleScrollBarChanged(StringHash eventType, VariantMap& eventData);
};

#endif // UI_SCROLLVIEW_H
