//
// Copyright (c) 2008-2013 the Urho3D project.
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

#pragma once

#include "UIElement.h"

namespace Urho3D
{

class BorderImage;
class ScrollBar;

/// Scrollable %UI element for showing a (possibly large) child element.
class ScrollView : public UIElement
{
    OBJECT(ScrollView);
    
public:
    /// Construct.
    ScrollView(Context* context);
    /// Destruct.
    virtual ~ScrollView();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Apply attribute changes that can not be applied immediately.
    virtual void ApplyAttributes();
    /// React to mouse wheel.
    virtual void OnWheel(int delta, int buttons, int qualifiers);
    /// React to a key press.
    virtual void OnKey(int key, int buttons, int qualifiers);
    /// React to resize.
    virtual void OnResize();
    
    /// Set content element.
    void SetContentElement(UIElement* element);
    /// Set view offset from the top-left corner.
    void SetViewPosition(const IntVector2& position);
    /// Set view offset from the top-left corner.
    void SetViewPosition(int x, int y);
    /// Set scrollbars' visibility.
    void SetScrollBarsVisible(bool horizontal, bool vertical);
    /// Set arrow key scroll step. Also sets it on the scrollbars.
    void SetScrollStep(float step);
    /// Set arrow key page step.
    void SetPageStep(float step);
    
    /// Return view offset from the top-left corner.
    const IntVector2& GetViewPosition() const { return viewPosition_; }
    /// Return content element.
    UIElement* GetContentElement() const { return contentElement_; }
    /// Return horizontal scroll bar.
    ScrollBar* GetHorizontalScrollBar() const { return horizontalScrollBar_; }
    /// Return vertical scroll bar.
    ScrollBar* GetVerticalScrollBar() const { return verticalScrollBar_; }
    /// Return scroll panel.
    BorderImage* GetScrollPanel() const { return scrollPanel_; }
    /// Return arrow key scroll step.
    float GetScrollStep() const;
    /// Return arrow key page step.
    float GetPageStep() const { return pageStep_; }
    
    /// Set view position attribut.
    void SetViewPositionAttr(const IntVector2& value);
    
protected:
    /// Update view size from the content element.
    void UpdateViewSize();
    /// Update the scrollbars' ranges and positions.
    void UpdateScrollBars();
    /// Limit and update the view with a new position.
    void UpdateView(const IntVector2& position);
    
    /// Content element.
    SharedPtr<UIElement> contentElement_;
    /// Horizontal scroll bar.
    SharedPtr<ScrollBar> horizontalScrollBar_;
    /// Vertical scroll bar.
    SharedPtr<ScrollBar> verticalScrollBar_;
    /// Scroll panel element.
    SharedPtr<BorderImage> scrollPanel_;
    /// Current view offset from the top-left corner.
    IntVector2 viewPosition_;
    /// Total view size.
    IntVector2 viewSize_;
    /// View offset attribute.
    IntVector2 viewPositionAttr_;
    /// Arrow key page step.
    float pageStep_;
    /// Ignore scrollbar events flag. Used to prevent possible endless loop when setting position.
    bool ignoreEvents_;
    
private:
    /// Return true when scrollbar has the visible flag toggled.
    static bool SetScrollBarVisible(ScrollBar* scrollBar, bool visible);
    /// Handle scrollbar value changed.
    void HandleScrollBarChanged(StringHash eventType, VariantMap& eventData);
    /// Handle scrollbar visibility changed.
    void HandleScrollBarVisibleChanged(StringHash eventType, VariantMap& eventData);
    /// Handle content element resized.
    void HandleElementResized(StringHash eventType, VariantMap& eventData);
};

}
