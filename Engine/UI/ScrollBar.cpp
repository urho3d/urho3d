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

#include "Precompiled.h"
#include "Button.h"
#include "Context.h"
#include "InputEvents.h"
#include "ScrollBar.h"
#include "Slider.h"
#include "UIEvents.h"

namespace Urho3D
{

static const float DEFAULT_SCROLL_STEP = 0.1f;
static const float DEFAULT_REPEAT_DELAY = 0.4f;
static const float DEFAULT_REPEAT_RATE = 20.0f;

extern const char* orientations[];
extern const char* UI_CATEGORY;

OBJECTTYPESTATIC(ScrollBar);

ScrollBar::ScrollBar(Context* context) :
    UIElement(context),
    scrollStep_(DEFAULT_SCROLL_STEP),
    stepFactor_(1.0f),
    leftRect_(IntRect::ZERO),
    rightRect_(IntRect::ZERO),
    upRect_(IntRect::ZERO),
    downRect_(IntRect::ZERO)
{
    enabled_ = true;

    backButton_ = CreateChild<Button>("SB_Back");
    backButton_->SetInternal(true);
    backButton_->SetRepeat(DEFAULT_REPEAT_DELAY, DEFAULT_REPEAT_RATE);
    slider_ = CreateChild<Slider>("SB_Slider");
    slider_->SetInternal(true);
    slider_->SetRepeatRate(DEFAULT_REPEAT_RATE);
    forwardButton_ = CreateChild<Button>("SB_Forward");
    forwardButton_->SetInternal(true);
    forwardButton_->SetRepeat(DEFAULT_REPEAT_DELAY, DEFAULT_REPEAT_RATE);

    SubscribeToEvent(backButton_, E_PRESSED, HANDLER(ScrollBar, HandleBackButtonPressed));
    SubscribeToEvent(forwardButton_, E_PRESSED, HANDLER(ScrollBar, HandleForwardButtonPressed));
    SubscribeToEvent(slider_, E_SLIDERCHANGED, HANDLER(ScrollBar, HandleSliderChanged));
    SubscribeToEvent(slider_, E_SLIDERPAGED, HANDLER(ScrollBar, HandleSliderPaged));

    // Set default orientation/layout
    SetOrientation(O_HORIZONTAL);
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::RegisterObject(Context* context)
{
    context->RegisterFactory<ScrollBar>(UI_CATEGORY);

    COPY_BASE_ATTRIBUTES(ScrollBar, UIElement);
    UPDATE_ATTRIBUTE_DEFAULT_VALUE(ScrollBar, "Is Enabled", true);
    ENUM_ACCESSOR_ATTRIBUTE(ScrollBar, "Orientation", GetOrientation, SetOrientation, Orientation, orientations, O_HORIZONTAL, AM_FILE);
    ACCESSOR_ATTRIBUTE(ScrollBar, VAR_FLOAT, "Range", GetRange, SetRange, float, 1.0f, AM_FILE);
    ACCESSOR_ATTRIBUTE(ScrollBar, VAR_FLOAT, "Value", GetValue, SetValue, float, 0.0f, AM_FILE);
    ACCESSOR_ATTRIBUTE(ScrollBar, VAR_FLOAT, "Scroll Step", GetScrollStep, SetScrollStep, float, DEFAULT_SCROLL_STEP, AM_FILE);
    ACCESSOR_ATTRIBUTE(ScrollBar, VAR_FLOAT, "Step Factor", GetStepFactor, SetStepFactor, float, 1.0f, AM_FILE);
    ATTRIBUTE(ScrollBar, VAR_INTRECT, "Left Image Rect", leftRect_, IntRect::ZERO, AM_FILE);
    ATTRIBUTE(ScrollBar, VAR_INTRECT, "Right Image Rect", rightRect_, IntRect::ZERO, AM_FILE);
    ATTRIBUTE(ScrollBar, VAR_INTRECT, "Up Image Rect", upRect_, IntRect::ZERO, AM_FILE);
    ATTRIBUTE(ScrollBar, VAR_INTRECT, "Down Image Rect", downRect_, IntRect::ZERO, AM_FILE);
}

void ScrollBar::ApplyAttributes()
{
    UIElement::ApplyAttributes();

    // Reapply orientation to the button images
    if (slider_->GetOrientation() == O_HORIZONTAL)
    {
        backButton_->SetImageRect(leftRect_);
        forwardButton_->SetImageRect(rightRect_);
    }
    else
    {
        backButton_->SetImageRect(upRect_);
        forwardButton_->SetImageRect(downRect_);
    }
}

void ScrollBar::OnResize()
{
    // Disable layout operations while setting the button sizes is incomplete
    DisableLayoutUpdate();

    if (slider_->GetOrientation() == O_HORIZONTAL)
    {
        int height = GetHeight();
        backButton_->SetFixedSize(height, height);
        forwardButton_->SetFixedSize(height, height);
    }
    else
    {
        int width = GetWidth();
        backButton_->SetFixedSize(width, width);
        forwardButton_->SetFixedSize(width, width);
    }

    EnableLayoutUpdate();
}

void ScrollBar::SetOrientation(Orientation orientation)
{
    slider_->SetOrientation(orientation);

    if (orientation == O_HORIZONTAL)
    {
        backButton_->SetImageRect(leftRect_);
        forwardButton_->SetImageRect(rightRect_);
    }
    else
    {
        backButton_->SetImageRect(upRect_);
        forwardButton_->SetImageRect(downRect_);
    }

    OnResize();
    if (orientation == O_HORIZONTAL)
        SetLayout(LM_HORIZONTAL);
    else
        SetLayout(LM_VERTICAL);
}

void ScrollBar::SetRange(float range)
{
    slider_->SetRange(range);
}

void ScrollBar::SetValue(float value)
{
    slider_->SetValue(value);
}

void ScrollBar::ChangeValue(float delta)
{
    slider_->ChangeValue(delta);
}

void ScrollBar::SetScrollStep(float step)
{
    scrollStep_ = Max(step, 0.0f);
}

void ScrollBar::SetStepFactor(float factor)
{
    stepFactor_ = Max(factor, M_EPSILON);
}

void ScrollBar::StepBack()
{
    slider_->SetValue(slider_->GetValue() - GetEffectiveScrollStep());
}

void ScrollBar::StepForward()
{
    slider_->SetValue(slider_->GetValue() + GetEffectiveScrollStep());
}

Orientation ScrollBar::GetOrientation() const
{
    return slider_->GetOrientation();
}

float ScrollBar::GetRange() const
{
    return slider_->GetRange();
}

float ScrollBar::GetValue() const
{
    return slider_->GetValue();
}

float ScrollBar::GetEffectiveScrollStep() const
{
    return scrollStep_ * stepFactor_;
}

bool ScrollBar::FilterImplicitAttributes(XMLElement& dest) const
{
    if (!UIElement::FilterImplicitAttributes(dest))
        return false;

    if (!RemoveChildXML(dest, "Layout Mode"))
        return false;

    XMLElement childElem = dest.GetChild("element");
    if (!FilterButtonImplicitAttributes(childElem, "SB_Back"))
        return false;

    childElem = childElem.GetNext("element");
    if (!childElem)
        return false;
    if (!RemoveChildXML(childElem, "Name", "SB_Slider"))
        return false;
    if (!RemoveChildXML(childElem, "Repeat Rate", String(DEFAULT_REPEAT_RATE)))
        return false;
    if (!RemoveChildXML(childElem, "Orientation"))
        return false;
    if (!RemoveChildXML(childElem, "Range"))
        return false;
    if (!RemoveChildXML(childElem, "Value"))
        return false;

    childElem = childElem.GetNext("element");
    if (!FilterButtonImplicitAttributes(childElem, "SB_Forward"))
        return false;

    return true;
}

bool ScrollBar::FilterButtonImplicitAttributes(XMLElement& dest, const String& name) const
{
    if (!dest)
        return false;
    if (!RemoveChildXML(dest, "Name", name))
        return false;
    if (!RemoveChildXML(dest, "Repeat Delay", String(DEFAULT_REPEAT_DELAY)))
        return false;
    if (!RemoveChildXML(dest, "Repeat Rate", String(DEFAULT_REPEAT_RATE)))
        return false;
    if (!RemoveChildXML(dest, "Image Rect"))
        return false;
    if (!RemoveChildXML(dest, "Min Size"))
        return false;
    if (!RemoveChildXML(dest, "Max Size"))
        return false;

    return true;
}

void ScrollBar::HandleBackButtonPressed(StringHash eventType, VariantMap& eventData)
{
    StepBack();
}

void ScrollBar::HandleForwardButtonPressed(StringHash eventType, VariantMap& eventData)
{
    StepForward();
}

void ScrollBar::HandleSliderChanged(StringHash eventType, VariantMap& eventData)
{
    // Send the event forward
    VariantMap newEventData;

    newEventData[ScrollBarChanged::P_ELEMENT] = (void*)this;
    newEventData[ScrollBarChanged::P_VALUE] = slider_->GetValue();
    SendEvent(E_SCROLLBARCHANGED, newEventData);
}

void ScrollBar::HandleSliderPaged(StringHash eventType, VariantMap& eventData)
{
    using namespace SliderPaged;

    if (eventData[P_BUTTONS].GetInt() & MOUSEB_LEFT)
    {
        if (eventData[P_OFFSET].GetInt() < 0)
            backButton_->OnClick(IntVector2::ZERO, backButton_->ElementToScreen(IntVector2::ZERO), eventData[P_BUTTONS].GetInt(), eventData[P_QUALIFIERS].GetInt(), 0);
        else
            forwardButton_->OnClick(IntVector2::ZERO, backButton_->ElementToScreen(IntVector2::ZERO), eventData[P_BUTTONS].GetInt(), eventData[P_QUALIFIERS].GetInt(), 0);
    }
    else
    {
        if (eventData[P_OFFSET].GetInt() < 0)
            backButton_->OnHover(IntVector2::ZERO, backButton_->ElementToScreen(IntVector2::ZERO), eventData[P_BUTTONS].GetInt(), eventData[P_QUALIFIERS].GetInt(), 0);
        else
            forwardButton_->OnHover(IntVector2::ZERO, backButton_->ElementToScreen(IntVector2::ZERO), eventData[P_BUTTONS].GetInt(), eventData[P_QUALIFIERS].GetInt(), 0);
    }
}

}
