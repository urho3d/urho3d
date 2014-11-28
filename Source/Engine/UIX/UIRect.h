//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "Component.h"

namespace Urho3D
{

class UIRoot;

/// Layout mode.
enum UILayoutMode
{
    UILM_FREE = 0,
    UILM_ANCHOR,
};

/// X anchor pivot.
enum UIXAnchorPivot
{
    AP_XCENTER = 0,
    AP_LEFT,
    AP_RIGHT,
};

/// Y anchor pivot.
enum UIYAnchorPivot
{
    AP_YCENTER = 0,
    AP_TOP,
    AP_BOTTOM,
};

/// UI rectangle component.
class URHO3D_API UIRect : public Component
{
    OBJECT(UIRect);

public:
    /// Construct.
    UIRect(Context* scontext);
    /// Destruct.
    virtual ~UIRect();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Visualize the component as debug geometry.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

    /// Set layout mode.
    void SetLayoutMode(UILayoutMode layoutMode);
    /// Set position (center).
    void SetPosition(const Vector2& position);
    /// Set size.
    void SetSize(const Vector2& size);    
    /// Set left anchor pivot.
    void SetLeftAnchorPivot(UIXAnchorPivot anchorPivot);
    /// Set right anchor pivot.
    void SetRightAnchorPivot(UIXAnchorPivot anchorPivot);
    /// Set top anchor pivot.
    void SetTopAnchorPivot(UIYAnchorPivot anchorPivot);
    /// Set bottom anchor pivot.
    void SetBottomAnchorPivot(UIYAnchorPivot anchorPivot);
    /// Set left offset.
    void SetLeftOffset(float offset);
    /// Set right offset.
    void SetRightOffset(float offset);
    /// Set top offset.
    void SetTopOffset(float offset);
    /// Set bottom offset.
    void SetBottomOffset(float offset);

    /// Return layout mode.
    UILayoutMode GetLayoutMode() const { return layoutMode_; }
    /// Return position (center).
    const Vector2& GetPosition() const { return position_; }
    /// Return size.
    const Vector2& GetSize() const { return size_; }
    /// Return left anchor pivot.
    UIXAnchorPivot GetLeftAnchorPivot() const { return leftAnchorPivot_; }
    /// Return right anchor pivot
    UIXAnchorPivot GetRightAnchorPivot() const { return rightAnchorPivot_; }
    /// Return top anchor pivot
    UIYAnchorPivot GetTopAnchorPivot() const { return topAnchorPivot_; }
    /// Return bottom anchor pivot.
    UIYAnchorPivot GetBottomAnchorPivot() const { return bottomAnchorPivot_; }
    /// Return left offset.
    float GetLeftOffset() const { return leftOffset_; }
    /// Return right offset.
    float GetRightOffset() const { return rightOffset_; }
    /// Return top offset.
    float GetTopOffset() const { return topOffset_; }
    /// Return bottom offset.
    float GetBottomOffset() const { return bottomOffset_; }

    /// Return rectangle.
    const Rect& GetRect() const;
    /// Get x.
    float GetX() const { return GetRect().Center().x_; }
    /// Get y.
    float GetY() const { return GetRect().Center().y_; }
    /// Return left.
    float GetLeft() const { return GetRect().min_.x_; }
    /// Return right.
    float GetRight() const { return GetRect().max_.x_; }
    /// Return top.
    float GetTop() const { return GetRect().max_.y_; }
    /// Return bottom.
    float GetBottom() const { return GetRect().min_.y_; }
    /// Return width.
    float GetWidth() const { return GetRect().max_.x_ - GetRect().min_.x_; }
    /// Return height.
    float GetHeight() const { return GetRect().max_.y_ - GetRect().min_.y_; }

protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);
    /// Mark rectangle dirty.
    void MarkRectDirty();
    /// Mark children rectangle dirty.
    void MarkChildrenRectDirty();
    /// Calculate rectangle free mode.
    Rect CalculateRectFreeMode() const;
    /// Calculate free mode parameters.
    void CalculateFreeModeParameters(const Rect& rect);
    /// Calculate rectangle anchor mode.
    Rect CalculateRectAnchorMode() const;
    /// Calculate anchor offsets from rectangle.
    void CalculateAnchorModeParameters(const Rect& rect);
    /// Draw rectangle.
    void DrawRect(DebugRenderer* debug, bool depthTest);

    /// UIRoot.
    WeakPtr<UIRoot> root_;
    /// Parent.
    WeakPtr<UIRect> parent_;
    /// Layout mode.
    UILayoutMode layoutMode_;
    /// Position.
    Vector2 position_;
    /// Size.
    Vector2 size_;
    /// Left anchor pivot.
    UIXAnchorPivot leftAnchorPivot_;
    /// Right anchor pivot.
    UIXAnchorPivot rightAnchorPivot_;
    /// Top anchor pivot.
    UIYAnchorPivot topAnchorPivot_;
    /// Bottom anchor pivot.
    UIYAnchorPivot bottomAnchorPivot_;    
    /// Left offset.
    float leftOffset_;
    /// Right offset.
    float rightOffset_;
    /// Top offset.
    float topOffset_;
    /// Bottom offset.
    float bottomOffset_;
    /// Handle node dirty.
    bool handleNodeDirty_;
    /// Rectangle.
    mutable Rect rectangle_;
    /// Rectangle dirty flag.
    mutable bool rectangleDirty_;
};

}
