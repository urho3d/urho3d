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

#include "Precompiled.h"
#include "Context.h"
#include "DebugRenderer.h"
#include "Log.h"
#include "Node.h"
#include "Scene.h"
#include "UIRect.h"
#include "UIRoot.h"
#include "UIXEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* UIX_CATEGORY;


static const char* uiLayoutModes[] =
{
    "Free",
    "Anchor",
    0
};

static const char* uiXAnchorPivots[] = 
{
    "Center",
    "Left",
    "Right",
    0
};

static const char* uiYAnchorPivots[] = 
{
    "Center",
    "Top",
    "Bottom",
    0
};

UIRect::UIRect(Context* context) :
    Component(context),
    layoutMode_(UILM_FREE),
    position_(0.0f, 0.0f),
    size_(2.0f, 2.0f),
    leftAnchorPivot_(AP_XCENTER),
    rightAnchorPivot_(AP_XCENTER),
    topAnchorPivot_(AP_YCENTER),
    bottomAnchorPivot_(AP_YCENTER),
    leftOffset_(1.0f),
    rightOffset_(1.0f),
    topOffset_(1.0f),
    bottomOffset_(1.0f),
    handleNodeDirty_(true),
    rectangleDirty_(true)
{
}

UIRect::~UIRect()
{
}

void UIRect::RegisterObject(Context* context)
{
    context->RegisterFactory<UIRect>(UIX_CATEGORY);

    ENUM_ACCESSOR_ATTRIBUTE("Layout Mode", GetLayoutMode, SetLayoutMode, UILayoutMode, uiLayoutModes, UILM_FREE, AM_FILE);
    ACCESSOR_ATTRIBUTE("Center", GetPosition, SetPosition, Vector2, Vector2::ZERO, AM_FILE);
    ACCESSOR_ATTRIBUTE("Size", GetSize, SetSize, Vector2, Vector2(2.0f, 2.0f), AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE("Left Anchor Pivot", GetLeftAnchorPivot, SetLeftAnchorPivot, UIXAnchorPivot, uiXAnchorPivots, AP_XCENTER, AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE("Right Anchor Pivot", GetRightAnchorPivot, SetRightAnchorPivot, UIXAnchorPivot, uiXAnchorPivots, AP_XCENTER, AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE("Top Anchor Pivot", GetTopAnchorPivot, SetTopAnchorPivot, UIYAnchorPivot, uiYAnchorPivots, AP_YCENTER, AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE("Bottom Anchor Pivot", GetBottomAnchorPivot, SetBottomAnchorPivot, UIYAnchorPivot, uiYAnchorPivots, AP_YCENTER, AM_FILE);    
    ACCESSOR_ATTRIBUTE("Left Offset", GetLeftOffset, SetLeftOffset, float, 1.0f, AM_FILE);
    ACCESSOR_ATTRIBUTE("Right Offset", GetRightOffset, SetRightOffset, float, 1.0f, AM_FILE);
    ACCESSOR_ATTRIBUTE("Right Offset", GetTopOffset, SetTopOffset, float, 1.0f, AM_FILE);
    ACCESSOR_ATTRIBUTE("Bottom Offset", GetBottomOffset, SetBottomOffset, float, 1.0f, AM_FILE);    
}

void UIRect::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    // Draw parent rectangle
    if (parent_)
        parent_->DrawRect(debug, depthTest);

    DrawRect(debug, depthTest);
}

void UIRect::SetPosition(const Vector2& position)
{
    if (layoutMode_ == UILM_ANCHOR)
        return;

    if (position == position_)
        return;

    position_ = position;
    
    // Update node's position for editor
    if (node_)
    {
        handleNodeDirty_ = false;
        node_->SetWorldPosition2D(GetRect().Center());
        handleNodeDirty_ = true;
    }

    MarkRectDirty();
}

void UIRect::SetSize(const Vector2& size)
{
    if (layoutMode_ == UILM_ANCHOR)
        return;
    
    if (size.x_ < 0.0f || size.y_ < 0.0f || size == size_)
        return;

    size_ = size;
    
    MarkRectDirty();
}

void UIRect::SetLayoutMode(UILayoutMode layoutMode)
{
    if (layoutMode == layoutMode_)
        return;

    Rect rect = GetRect();    
    
    layoutMode_ = layoutMode;

    if (layoutMode_ == UILM_FREE)
        CalculateFreeModeParameters(rect);
    else
        CalculateAnchorModeParameters(rect);
}

void UIRect::SetLeftAnchorPivot(UIXAnchorPivot anchorPivot)
{
    if (layoutMode_ == UILM_FREE)
        return;

    if (anchorPivot == leftAnchorPivot_)
        return;

    Rect rect = GetRect();    
    leftAnchorPivot_ = anchorPivot;
    CalculateAnchorModeParameters(rect);
}

void UIRect::SetRightAnchorPivot(UIXAnchorPivot anchorPivot)
{
    if (layoutMode_ == UILM_FREE)
        return;
    
    if (anchorPivot == rightAnchorPivot_)
        return;

    Rect rect = GetRect();    
    rightAnchorPivot_ = anchorPivot;
    CalculateAnchorModeParameters(rect);
}

void UIRect::SetTopAnchorPivot(UIYAnchorPivot  anchorPivot)
{
    if (anchorPivot == topAnchorPivot_)
        return;

    Rect rect = GetRect();    
    topAnchorPivot_ = anchorPivot;
    CalculateAnchorModeParameters(rect);
}

void UIRect::SetBottomAnchorPivot(UIYAnchorPivot anchorPivot)
{
    if (layoutMode_ == UILM_FREE)
        return;
    
    if (anchorPivot == bottomAnchorPivot_)
        return;

    Rect rect = GetRect();    
    bottomAnchorPivot_ = anchorPivot;
    CalculateAnchorModeParameters(rect);
}

void UIRect::SetLeftOffset(float offset)
{
    if (layoutMode_ == UILM_FREE)
        return;

    if (offset == leftOffset_)
        return;

    leftOffset_ = offset;
    MarkRectDirty();
}

void UIRect::SetRightOffset(float offset)
{
    if (layoutMode_ == UILM_FREE)
        return;

    if (offset == rightOffset_)
        return;

    rightOffset_ = offset;
    MarkRectDirty();
}

void UIRect::SetBottomOffset(float offset)
{
    if (layoutMode_ == UILM_FREE)
        return;
    
    if (offset == bottomOffset_)
        return;

    bottomOffset_ = offset;
    MarkRectDirty();
}

void UIRect::SetTopOffset(float offset)
{
    if (layoutMode_ == UILM_FREE)
        return;
    
    if (offset == topOffset_)
        return;

    topOffset_ = offset;
    MarkRectDirty();
}

const Rect& UIRect::GetRect() const
{
    if (!rectangleDirty_)
        return rectangle_;

    if (layoutMode_ == UILM_FREE)
        rectangle_ = CalculateRectFreeMode();
    else
        rectangle_ = CalculateRectAnchorMode();

    rectangleDirty_ = false;

    return rectangle_;
}

void UIRect::OnNodeSet(Node* node)
{
    Component::OnNodeSet(node);

    if (node)
    {
        root_ = GetScene()->GetOrCreateComponent<UIRoot>();

        UIRect* rect = node->GetComponent<UIRect>();
        if (rect && rect != this)
        {
            LOGERROR("Can not add more than one UIRect in node");
            return;
        }

        node->AddListener(this);

        Node* parent = node->GetParent();
        if (parent)
        {
            parent_ = parent->GetComponent<UIRect>();
            MarkRectDirty();
        }
    }
    else
    {
        parent_ = 0;
        MarkRectDirty();
    }
}

void UIRect::OnMarkedDirty(Node* node)
{
    if (layoutMode_ == UILM_FREE && handleNodeDirty_)
    {
        position_ -= node_->GetPosition2D();
        MarkRectDirty();
    }
}

void UIRect::MarkRectDirty()
{
    rectangleDirty_ = true;

    using namespace UIRectDirtied;
    VariantMap& eventData = GetEventDataMap();
    eventData[P_UIRECT] = this;
    SendEvent(E_UIRECTDIRTIED, eventData);

    MarkChildrenRectDirty();
}

void UIRect::MarkChildrenRectDirty()
{
    if (!node_)
        return;

    const Vector<SharedPtr<Node> >& children = node_->GetChildren();
    for (unsigned i = 0; i < children.Size(); ++i)
    {
        UIRect* uiRect = children[i]->GetComponent<UIRect>();
        if (uiRect)
            uiRect->MarkRectDirty();
    }
}

Rect UIRect::CalculateRectFreeMode() const
{
    if (!node_)
        return Rect::ZERO;

    Vector2 center = node_->GetPosition2D();
    if (parent_)
        center += parent_->GetRect().Center();
    
    Vector2 halfSize = size_ * 0.5f; 
    return Rect(center - halfSize, center + halfSize);
}

void UIRect::CalculateFreeModeParameters(const Rect& rect)
{
    position_ = rect.Center();
    if (parent_)
        position_ -= parent_->GetRect().Center();
    size_ = rect.Size();
}

Rect UIRect::CalculateRectAnchorMode() const
{
    UIRect* parent = parent_;
    if (!parent)
        parent = root_;

    float parentXs[] = { parent->GetX(), parent->GetLeft(), parent->GetRight() };
    float parentYs[] = { parent->GetY(), parent->GetTop(), parent->GetBottom() };

    float left = parentXs[leftAnchorPivot_] + leftOffset_;
    float right = parentXs[rightAnchorPivot_] + rightOffset_;
    float top = parentYs[topAnchorPivot_] + topOffset_;
    float bottom = parentYs[bottomAnchorPivot_] + bottomOffset_;

    return Rect(left, bottom, right, top);
}

void UIRect::CalculateAnchorModeParameters(const Rect& rect)
{
    UIRect* parent = parent_;
    if (!parent)
        parent = root_;

    float parentXs[] = { parent->GetX(), parent->GetLeft(), parent->GetRight() };
    float parentYs[] = { parent->GetY(), parent->GetTop(), parent->GetBottom() };

    leftOffset_ = rect.min_.x_ - parentXs[leftAnchorPivot_];
    rightOffset_ = rect.max_.x_ - parentXs[rightAnchorPivot_];
    topOffset_ = rect.max_.y_ - parentYs[topAnchorPivot_];
    bottomOffset_ = rect.min_.y_ - parentYs[bottomAnchorPivot_];
}

void UIRect::DrawRect(DebugRenderer* debug, bool depthTest)
{
    if (!debug)
        return;

    const Rect& drawRect = GetRect();
    if (drawRect.Size().x_ < M_EPSILON || drawRect.Size().y_ < M_EPSILON)
        return;

    const Vector3 leftTop(drawRect.min_.x_, drawRect.max_.y_);
    const Vector3 leftBottom(drawRect.min_);
    const Vector3 rightTop(drawRect.max_);
    const Vector3 rightBottom(drawRect.max_.x_, drawRect.min_.y_);

    const Color& color = Color::GREEN;

    debug->AddLine(leftTop, rightTop, color, depthTest);
    debug->AddLine(rightTop, rightBottom, color, depthTest);
    debug->AddLine(rightBottom, leftBottom, color, depthTest);
    debug->AddLine(leftBottom, leftTop, color, depthTest);
}

}
