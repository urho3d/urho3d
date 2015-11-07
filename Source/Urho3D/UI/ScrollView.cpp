//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Input/InputEvents.h"
#include "../UI/BorderImage.h"
#include "../UI/ScrollBar.h"
#include "../UI/ScrollView.h"
#include "../UI/Slider.h"
#include "../UI/UI.h"
#include "../UI/UIEvents.h"

#include "../DebugNew.h"

namespace Urho3D
{

static const float STEP_FACTOR = 300.0f;

extern const char* UI_CATEGORY;

ScrollView::ScrollView(Context* context) :
    UIElement(context),
    viewPosition_(IntVector2::ZERO),
    viewSize_(IntVector2::ZERO),
    viewPositionAttr_(IntVector2::ZERO),
    touchScrollSpeed_(Vector2::ZERO),
    touchScrollSpeedMax_(Vector2::ZERO),
    pageStep_(1.0f),
    scrollBarsAutoVisible_(true),
    ignoreEvents_(false),
    resizeContentWidth_(false),
    scrollDeceleration_(30.0f),
    scrollSnapEpsilon_(M_EPSILON),
    scrollTouchDown_(false),
    barScrolling_(false),
    autoDisableChildren_(false),
    scrollChildrenDisable_(false),
    touchDistanceSum_(0.0f),
    autoDisableThreshold_(25.0f)
{
    clipChildren_ = true;
    SetEnabled(true);
    focusMode_ = FM_FOCUSABLE_DEFOCUSABLE;

    horizontalScrollBar_ = CreateChild<ScrollBar>("SV_HorizontalScrollBar");
    horizontalScrollBar_->SetInternal(true);
    horizontalScrollBar_->SetAlignment(HA_LEFT, VA_BOTTOM);
    horizontalScrollBar_->SetOrientation(O_HORIZONTAL);
    verticalScrollBar_ = CreateChild<ScrollBar>("SV_VerticalScrollBar");
    verticalScrollBar_->SetInternal(true);
    verticalScrollBar_->SetAlignment(HA_RIGHT, VA_TOP);
    verticalScrollBar_->SetOrientation(O_VERTICAL);
    scrollPanel_ = CreateChild<BorderImage>("SV_ScrollPanel");
    scrollPanel_->SetInternal(true);
    scrollPanel_->SetEnabled(true);
    scrollPanel_->SetClipChildren(true);

    SubscribeToEvent(horizontalScrollBar_, E_SCROLLBARCHANGED, URHO3D_HANDLER(ScrollView, HandleScrollBarChanged));
    SubscribeToEvent(horizontalScrollBar_, E_VISIBLECHANGED, URHO3D_HANDLER(ScrollView, HandleScrollBarVisibleChanged));
    SubscribeToEvent(verticalScrollBar_, E_SCROLLBARCHANGED, URHO3D_HANDLER(ScrollView, HandleScrollBarChanged));
    SubscribeToEvent(verticalScrollBar_, E_VISIBLECHANGED, URHO3D_HANDLER(ScrollView, HandleScrollBarVisibleChanged));
    SubscribeToEvent(E_TOUCHMOVE, URHO3D_HANDLER(ScrollView, HandleTouchMove));
    SubscribeToEvent(E_TOUCHBEGIN, URHO3D_HANDLER(ScrollView, HandleTouchMove));
    SubscribeToEvent(E_TOUCHEND, URHO3D_HANDLER(ScrollView, HandleTouchMove));

}

ScrollView::~ScrollView()
{
}

void ScrollView::RegisterObject(Context* context)
{
    context->RegisterFactory<ScrollView>(UI_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Clip Children", true);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Is Enabled", true);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Focus Mode", FM_FOCUSABLE_DEFOCUSABLE);
    URHO3D_ACCESSOR_ATTRIBUTE("View Position", GetViewPosition, SetViewPositionAttr, IntVector2, IntVector2::ZERO, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Scroll Step", GetScrollStep, SetScrollStep, float, 0.1f, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Page Step", GetPageStep, SetPageStep, float, 1.0f, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Auto Show/Hide Scrollbars", GetScrollBarsAutoVisible, SetScrollBarsAutoVisible, bool, true, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Scroll Deceleration", GetScrollDeceleration, SetScrollDeceleration, float, 30.0f, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Scroll Snap Epsilon", GetScrollSnapEpsilon, SetScrollSnapEpsilon, float, 1.0f, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Auto Disable Children", GetAutoDisableChildren, SetAutoDisableChildren, bool, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Auto Disable Threshold", GetAutoDisableThreshold, SetAutoDisableThreshold, float, 25.0f, AM_FILE);
}

void ScrollView::Update(float timeStep)
{
    // Update touch scrolling here if necessary
    if (touchScrollSpeed_ == Vector2::ZERO && touchScrollSpeedMax_ == Vector2::ZERO && !barScrolling_)
        return;

    // Check if we should not scroll:
    // - ScrollView is not visible, is not enabled, or doesn't have focus
    // - The element being dragged is not a child of the ScrollView, or is one of our scrollbars
    if (!IsVisible() || !IsEnabled() || !HasFocus())
    {
        touchScrollSpeed_ = Vector2::ZERO;
        touchScrollSpeedMax_ = Vector2::ZERO;
        return;
    }

    if (GetSubsystem<UI>()->IsDragging())
    {
        Vector<UIElement*> dragElements = GetSubsystem<UI>()->GetDragElements();

        for (unsigned i = 0; i < dragElements.Size(); i++)
        {
            UIElement* dragElement = dragElements[i];
            int dragButtons = dragElement->GetDragButtonCombo();

            if (dragButtons != MOUSEB_LEFT)
                continue;

            UIElement* dragParent = dragElement->GetParent();
            bool dragElementIsChild = false;

            while (dragParent)
            {
                if (dragParent == this)
                {
                    dragElementIsChild = true;
                    break;
                }
                dragParent = dragParent->GetParent();
            }

            if (!dragElementIsChild || dragElement == horizontalScrollBar_->GetSlider() ||
                dragElement == verticalScrollBar_->GetSlider())
            {
                touchScrollSpeed_ = Vector2::ZERO;
                touchScrollSpeedMax_ = Vector2::ZERO;
                return;
            }
        }
    }

    // Update view position
    IntVector2 newPosition = viewPosition_;
    newPosition.x_ += (int)touchScrollSpeed_.x_;
    newPosition.y_ += (int)touchScrollSpeed_.y_;
    SetViewPosition(newPosition);

    // Smooth deceleration
    ScrollSmooth(timeStep);
}

void ScrollView::ApplyAttributes()
{
    UIElement::ApplyAttributes();

    // Set the scrollbar orientations again and perform size update now that the style is known
    horizontalScrollBar_->SetOrientation(O_HORIZONTAL);
    verticalScrollBar_->SetOrientation(O_VERTICAL);

    // If the scroll panel has a child, it should be the content element, which has some special handling
    if (scrollPanel_->GetNumChildren())
        SetContentElement(scrollPanel_->GetChild(0));

    OnResize();

    // Reapply view position with proper content element and size
    SetViewPosition(viewPositionAttr_);
}

void ScrollView::OnWheel(int delta, int buttons, int qualifiers)
{
    if (delta > 0)
        verticalScrollBar_->StepBack();
    if (delta < 0)
        verticalScrollBar_->StepForward();
}

void ScrollView::OnKey(int key, int buttons, int qualifiers)
{
    switch (key)
    {
    case KEY_LEFT:
        if (horizontalScrollBar_->IsVisible())
        {
            if (qualifiers & QUAL_CTRL)
                horizontalScrollBar_->SetValue(0.0f);
            else
                horizontalScrollBar_->StepBack();
        }
        break;

    case KEY_RIGHT:
        if (horizontalScrollBar_->IsVisible())
        {
            if (qualifiers & QUAL_CTRL)
                horizontalScrollBar_->SetValue(horizontalScrollBar_->GetRange());
            else
                horizontalScrollBar_->StepForward();
        }
        break;

    case KEY_HOME:
        qualifiers |= QUAL_CTRL;
        // Fallthru

    case KEY_UP:
        if (verticalScrollBar_->IsVisible())
        {
            if (qualifiers & QUAL_CTRL)
                verticalScrollBar_->SetValue(0.0f);
            else
                verticalScrollBar_->StepBack();
        }
        break;

    case KEY_END:
        qualifiers |= QUAL_CTRL;
        // Fallthru

    case KEY_DOWN:
        if (verticalScrollBar_->IsVisible())
        {
            if (qualifiers & QUAL_CTRL)
                verticalScrollBar_->SetValue(verticalScrollBar_->GetRange());
            else
                verticalScrollBar_->StepForward();
        }
        break;

    case KEY_PAGEUP:
        if (verticalScrollBar_->IsVisible())
            verticalScrollBar_->ChangeValue(-pageStep_);
        break;

    case KEY_PAGEDOWN:
        if (verticalScrollBar_->IsVisible())
            verticalScrollBar_->ChangeValue(pageStep_);
        break;

    default: break;
    }
}

void ScrollView::OnResize()
{
    UpdatePanelSize();
    UpdateViewSize();

    // If scrollbar auto visibility is enabled, check whether scrollbars should be visible.
    // This may force another update of the panel size
    if (scrollBarsAutoVisible_)
    {
        ignoreEvents_ = true;
        horizontalScrollBar_->SetVisible(horizontalScrollBar_->GetRange() > M_EPSILON);
        verticalScrollBar_->SetVisible(verticalScrollBar_->GetRange() > M_EPSILON);
        ignoreEvents_ = false;

        UpdatePanelSize();
    }
}

void ScrollView::SetContentElement(UIElement* element)
{
    if (element == contentElement_)
        return;

    if (contentElement_)
    {
        scrollPanel_->RemoveChild(contentElement_);
        UnsubscribeFromEvent(contentElement_, E_RESIZED);
    }
    contentElement_ = element;
    if (contentElement_)
    {
        scrollPanel_->AddChild(contentElement_);
        SubscribeToEvent(contentElement_, E_RESIZED, URHO3D_HANDLER(ScrollView, HandleElementResized));
    }

    OnResize();
}

void ScrollView::SetViewPosition(const IntVector2& position)
{
    UpdateView(position);
    UpdateScrollBars();
}

void ScrollView::SetViewPosition(int x, int y)
{
    SetViewPosition(IntVector2(x, y));
}

void ScrollView::SetScrollBarsVisible(bool horizontal, bool vertical)
{
    scrollBarsAutoVisible_ = false;
    horizontalScrollBar_->SetVisible(horizontal);
    verticalScrollBar_->SetVisible(vertical);
}

void ScrollView::SetScrollBarsAutoVisible(bool enable)
{
    if (enable != scrollBarsAutoVisible_)
    {
        scrollBarsAutoVisible_ = enable;
        // Check whether scrollbars should be visible now
        if (enable)
            OnResize();
        else
        {
            horizontalScrollBar_->SetVisible(true);
            verticalScrollBar_->SetVisible(true);
        }
    }
}

void ScrollView::SetScrollStep(float step)
{
    horizontalScrollBar_->SetScrollStep(step);
    verticalScrollBar_->SetScrollStep(step);
}

void ScrollView::SetPageStep(float step)
{
    pageStep_ = Max(step, 0.0f);
}

float ScrollView::GetScrollStep() const
{
    return horizontalScrollBar_->GetScrollStep();
}

void ScrollView::SetViewPositionAttr(const IntVector2& value)
{
    viewPositionAttr_ = value;
    SetViewPosition(value);
}

bool ScrollView::FilterImplicitAttributes(XMLElement& dest) const
{
    if (!UIElement::FilterImplicitAttributes(dest))
        return false;

    XMLElement childElem = dest.GetChild("element");
    if (!FilterScrollBarImplicitAttributes(childElem, "SV_HorizontalScrollBar"))
        return false;
    if (!RemoveChildXML(childElem, "Vert Alignment", "Bottom"))
        return false;

    childElem = childElem.GetNext("element");
    if (!FilterScrollBarImplicitAttributes(childElem, "SV_VerticalScrollBar"))
        return false;
    if (!RemoveChildXML(childElem, "Horiz Alignment", "Right"))
        return false;

    childElem = childElem.GetNext("element");
    if (!childElem)
        return false;
    if (!RemoveChildXML(childElem, "Name", "SV_ScrollPanel"))
        return false;
    if (!RemoveChildXML(childElem, "Is Enabled", "true"))
        return false;
    if (!RemoveChildXML(childElem, "Clip Children", "true"))
        return false;
    if (!RemoveChildXML(childElem, "Size"))
        return false;

    return true;
}

bool ScrollView::FilterScrollBarImplicitAttributes(XMLElement& dest, const String& name) const
{
    if (!dest)
        return false;
    if (!RemoveChildXML(dest, "Name", name))
        return false;
    if (!RemoveChildXML(dest, "Orientation"))
        return false;
    if (!RemoveChildXML(dest, "Range"))
        return false;
    if (!RemoveChildXML(dest, "Step Factor"))
        return false;
    if (scrollBarsAutoVisible_)
    {
        if (!RemoveChildXML(dest, "Is Visible"))
            return false;
    }

    return true;
}

void ScrollView::UpdatePanelSize()
{
    // Ignore events in case content element resizes itself along with the panel
    // (content element resize triggers our OnResize(), so it could lead to infinite recursion)
    ignoreEvents_ = true;

    IntVector2 panelSize = GetSize();
    if (verticalScrollBar_->IsVisible())
        panelSize.x_ -= verticalScrollBar_->GetWidth();
    if (horizontalScrollBar_->IsVisible())
        panelSize.y_ -= horizontalScrollBar_->GetHeight();

    scrollPanel_->SetSize(panelSize);
    horizontalScrollBar_->SetWidth(scrollPanel_->GetWidth());
    verticalScrollBar_->SetHeight(scrollPanel_->GetHeight());

    if (resizeContentWidth_ && contentElement_)
    {
        IntRect panelBorder = scrollPanel_->GetClipBorder();
        contentElement_->SetWidth(scrollPanel_->GetWidth() - panelBorder.left_ - panelBorder.right_);
        UpdateViewSize();
    }

    ignoreEvents_ = false;
}

void ScrollView::UpdateViewSize()
{
    IntVector2 size(IntVector2::ZERO);
    if (contentElement_)
        size = contentElement_->GetSize();
    IntRect panelBorder = scrollPanel_->GetClipBorder();

    viewSize_.x_ = Max(size.x_, scrollPanel_->GetWidth() - panelBorder.left_ - panelBorder.right_);
    viewSize_.y_ = Max(size.y_, scrollPanel_->GetHeight() - panelBorder.top_ - panelBorder.bottom_);

    UpdateView(viewPosition_);
    UpdateScrollBars();
}

void ScrollView::UpdateScrollBars()
{
    ignoreEvents_ = true;

    IntVector2 size = scrollPanel_->GetSize();
    IntRect panelBorder = scrollPanel_->GetClipBorder();
    size.x_ -= panelBorder.left_ + panelBorder.right_;
    size.y_ -= panelBorder.top_ + panelBorder.bottom_;

    if (size.x_ > 0 && viewSize_.x_ > 0)
    {
        float range = (float)viewSize_.x_ / (float)size.x_ - 1.0f;
        horizontalScrollBar_->SetRange(range);
        horizontalScrollBar_->SetValue((float)viewPosition_.x_ / (float)size.x_);
        horizontalScrollBar_->SetStepFactor(STEP_FACTOR / (float)size.x_);
    }
    if (size.y_ > 0 && viewSize_.y_ > 0)
    {
        float range = (float)viewSize_.y_ / (float)size.y_ - 1.0f;
        verticalScrollBar_->SetRange(range);
        verticalScrollBar_->SetValue((float)viewPosition_.y_ / (float)size.y_);
        verticalScrollBar_->SetStepFactor(STEP_FACTOR / (float)size.y_);
    }

    ignoreEvents_ = false;
}

void ScrollView::UpdateView(const IntVector2& position)
{
    IntVector2 oldPosition = viewPosition_;
    IntRect panelBorder = scrollPanel_->GetClipBorder();
    IntVector2 panelSize(scrollPanel_->GetWidth() - panelBorder.left_ - panelBorder.right_,
        scrollPanel_->GetHeight() - panelBorder.top_ - panelBorder.bottom_);

    viewPosition_.x_ = Clamp(position.x_, 0, viewSize_.x_ - panelSize.x_);
    viewPosition_.y_ = Clamp(position.y_, 0, viewSize_.y_ - panelSize.y_);
    scrollPanel_->SetChildOffset(IntVector2(-viewPosition_.x_ + panelBorder.left_, -viewPosition_.y_ + panelBorder.top_));

    if (viewPosition_ != oldPosition)
    {
        using namespace ViewChanged;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_ELEMENT] = this;
        eventData[P_X] = viewPosition_.x_;
        eventData[P_Y] = viewPosition_.y_;
        SendEvent(E_VIEWCHANGED, eventData);
    }
}

void ScrollView::HandleScrollBarChanged(StringHash eventType, VariantMap& eventData)
{
    if (!ignoreEvents_)
    {
        IntVector2 size = scrollPanel_->GetSize();
        IntRect panelBorder = scrollPanel_->GetClipBorder();
        size.x_ -= panelBorder.left_ + panelBorder.right_;
        size.y_ -= panelBorder.top_ + panelBorder.bottom_;

        UpdateView(IntVector2(
            (int)(horizontalScrollBar_->GetValue() * (float)size.x_),
            (int)(verticalScrollBar_->GetValue() * (float)size.y_)
        ));
    }
}

void ScrollView::HandleScrollBarVisibleChanged(StringHash eventType, VariantMap& eventData)
{
    // Need to recalculate panel size when scrollbar visibility changes
    if (!ignoreEvents_)
        OnResize();
}

void ScrollView::HandleElementResized(StringHash eventType, VariantMap& eventData)
{
    if (!ignoreEvents_)
        OnResize();
}

void ScrollView::HandleTouchMove(StringHash eventType, VariantMap& eventData)
{
    using namespace TouchMove;

    if (eventType == E_TOUCHMOVE && !barScrolling_)
    {
        scrollTouchDown_ = true;
        // Take new scrolling speed if it's faster than the current accumulated value
        float dX = (float)-eventData[P_DX].GetInt();
        float dY = (float)-eventData[P_DY].GetInt();

        if (Abs(dX) > Abs(touchScrollSpeed_.x_))
            touchScrollSpeed_.x_ = dX;
        if (Abs(dY) > Abs(touchScrollSpeed_.y_))
            touchScrollSpeed_.y_ = dY;

        // Auto disable children
        touchDistanceSum_ += dX * dX + dY * dY;
        if (autoDisableChildren_ && touchDistanceSum_ >= autoDisableThreshold_)
        {
            if (visible_ && !scrollChildrenDisable_)
            {
                scrollChildrenDisable_ = true;
                scrollPanel_->SetDeepEnabled(false);
            }
        }

        touchScrollSpeedMax_.x_ = dX;
        touchScrollSpeedMax_.y_ = dY;
    }
    else if (eventType == E_TOUCHBEGIN)
    {
        int X = eventData[P_X].GetInt();
        int Y = eventData[P_Y].GetInt();
        IntVector2 pos = IntVector2(X, Y);

        // Prevent conflict between touch scroll and scrollbar scroll
        if (horizontalScrollBar_->IsVisible() && horizontalScrollBar_->IsInsideCombined(pos, true))
            barScrolling_ = true;

        if (verticalScrollBar_->IsVisible() && verticalScrollBar_->IsInsideCombined(pos, true))
            barScrolling_ = true;

        // Stop the smooth scrolling
        touchScrollSpeed_ = Vector2::ZERO;
        touchScrollSpeedMax_ = Vector2::ZERO;
    }
    else if (eventType == E_TOUCHEND)
    {
        // 'Flick' action
        // Release any auto disabled children
        if (scrollChildrenDisable_)
        {
            touchDistanceSum_ = 0.0f;
            scrollChildrenDisable_ = false;
            scrollPanel_->ResetDeepEnabled();
        }

        barScrolling_ = false;
        scrollTouchDown_ = false;
        if (Abs(touchScrollSpeedMax_.x_) > scrollSnapEpsilon_)
            touchScrollSpeed_.x_ = touchScrollSpeedMax_.x_;
        else
            touchScrollSpeed_.x_ = 0;

        if (Abs(touchScrollSpeedMax_.y_) > scrollSnapEpsilon_)
            touchScrollSpeed_.y_ = touchScrollSpeedMax_.y_;
        else
            touchScrollSpeed_.y_ = 0;
        touchScrollSpeedMax_ = Vector2::ZERO;
    }
}

void ScrollView::ScrollSmooth(float timeStep)
{
    // Decay the momentum
    if (touchScrollSpeedMax_.x_ >= scrollSnapEpsilon_)
    {
        touchScrollSpeedMax_.x_ -= scrollDeceleration_ * timeStep;
        touchScrollSpeedMax_.x_ = touchScrollSpeedMax_.x_ > 0 ? touchScrollSpeedMax_.x_ : 0;
    }
    else if (touchScrollSpeedMax_.x_ <= -scrollSnapEpsilon_)
    {
        touchScrollSpeedMax_.x_ += scrollDeceleration_ * timeStep;
        touchScrollSpeedMax_.x_ = touchScrollSpeedMax_.x_ < 0 ? touchScrollSpeedMax_.x_ : 0;
    }
    else
        touchScrollSpeedMax_.x_ = 0;

    if (touchScrollSpeedMax_.y_ >= scrollSnapEpsilon_)
    {
        touchScrollSpeedMax_.y_ -= scrollDeceleration_ * timeStep;
        touchScrollSpeedMax_.y_ = touchScrollSpeedMax_.y_ > 0 ? touchScrollSpeedMax_.y_ : 0;
    }
    else if (touchScrollSpeedMax_.y_ <= -scrollSnapEpsilon_)
    {
        touchScrollSpeedMax_.y_ += scrollDeceleration_ * timeStep;
        touchScrollSpeedMax_.y_ = touchScrollSpeedMax_.y_ < 0 ? touchScrollSpeedMax_.y_ : 0;
    }
    else
        touchScrollSpeedMax_.y_ = 0;

    // Control vs flick
    if (scrollTouchDown_)
    {
        // Finger is held down: control = instant stop
        touchScrollSpeed_ = Vector2::ZERO;
    }
    else
    {
        // Finger is released: flick = smooth deceleration
        if (touchScrollSpeed_.x_ >= scrollSnapEpsilon_)
        {
            touchScrollSpeed_.x_ -= scrollDeceleration_ * timeStep;
            if (touchScrollSpeed_.x_ < 0)
            {
                touchScrollSpeed_.x_ = 0;
            }

            if (horizontalScrollBar_->GetValue() >= horizontalScrollBar_->GetRange() - M_EPSILON)
            {
                // Stop movement when we reach end of scroll
                touchScrollSpeed_.x_ = 0;
            }
        }
        else if (touchScrollSpeed_.x_ < -scrollSnapEpsilon_)
        {
            touchScrollSpeed_.x_ += scrollDeceleration_ * timeStep;
            if (touchScrollSpeed_.x_ > 0)
            {
                touchScrollSpeed_.x_ = 0;
            }

            if (horizontalScrollBar_->GetValue() <= M_EPSILON)
            {
                // Stop movement when we reach end of scroll
                touchScrollSpeed_.x_ = 0;
            }
        }
        else
            touchScrollSpeed_.x_ = 0;

        if (touchScrollSpeed_.y_ >= scrollSnapEpsilon_)
        {
            touchScrollSpeed_.y_ -= scrollDeceleration_ * timeStep;
            if (touchScrollSpeed_.y_ < 0)
            {
                touchScrollSpeed_.y_ = 0;
            }

            if (verticalScrollBar_->GetValue() >= verticalScrollBar_->GetRange() - M_EPSILON)
            {
                // Stop movement when we reach end of scroll
                touchScrollSpeed_.y_ = 0;
            }
        }
        else if (touchScrollSpeed_.y_ < -scrollSnapEpsilon_)
        {
            touchScrollSpeed_.y_ += scrollDeceleration_ * timeStep;
            if (touchScrollSpeed_.y_ > 0)
            {
                touchScrollSpeed_.y_ = 0;
            }

            if (verticalScrollBar_->GetValue() <= M_EPSILON)
            {
                // Stop movement when we reach end of scroll
                touchScrollSpeed_.y_ = 0;
            }
        }
        else
            touchScrollSpeed_.y_ = 0;
    }
}

}
