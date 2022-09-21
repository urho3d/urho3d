// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Input/InputEvents.h"
#include "../UI/Button.h"
#include "../UI/ScrollBar.h"
#include "../UI/Slider.h"
#include "../UI/UIEvents.h"

namespace Urho3D
{

static const float DEFAULT_SCROLL_STEP = 0.1f;
static const float DEFAULT_REPEAT_DELAY = 0.4f;
static const float DEFAULT_REPEAT_RATE = 20.0f;

extern const char* orientations[];
extern const char* UI_CATEGORY;

ScrollBar::ScrollBar(Context* context) :
    BorderImage(context),
    scrollStep_(DEFAULT_SCROLL_STEP),
    stepFactor_(1.0f),
    leftRect_(IntRect::ZERO),
    rightRect_(IntRect::ZERO),
    upRect_(IntRect::ZERO),
    downRect_(IntRect::ZERO)
{
    SetEnabled(true);

    backButton_ = CreateChild<Button>("SB_Back");
    backButton_->SetInternal(true);
    backButton_->SetRepeat(DEFAULT_REPEAT_DELAY, DEFAULT_REPEAT_RATE);
    backButton_->SetFocusMode(FM_NOTFOCUSABLE);
    slider_ = CreateChild<Slider>("SB_Slider");
    slider_->SetInternal(true);
    slider_->SetRepeatRate(DEFAULT_REPEAT_RATE);
    forwardButton_ = CreateChild<Button>("SB_Forward");
    forwardButton_->SetInternal(true);
    forwardButton_->SetRepeat(DEFAULT_REPEAT_DELAY, DEFAULT_REPEAT_RATE);
    forwardButton_->SetFocusMode(FM_NOTFOCUSABLE);

    // For backward compatibility
    SetColor(Color(0.0f, 0.0f, 0.0f, 0.0f));

    SubscribeToEvent(backButton_, E_PRESSED, URHO3D_HANDLER(ScrollBar, HandleBackButtonPressed));
    SubscribeToEvent(forwardButton_, E_PRESSED, URHO3D_HANDLER(ScrollBar, HandleForwardButtonPressed));
    SubscribeToEvent(slider_, E_SLIDERCHANGED, URHO3D_HANDLER(ScrollBar, HandleSliderChanged));
    SubscribeToEvent(slider_, E_SLIDERPAGED, URHO3D_HANDLER(ScrollBar, HandleSliderPaged));

    // Set default orientation
    SetOrientation(O_HORIZONTAL);
}

ScrollBar::~ScrollBar() = default;

void ScrollBar::RegisterObject(Context* context)
{
    context->RegisterFactory<ScrollBar>(UI_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(BorderImage);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Is Enabled", true);
    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Orientation", GetOrientation, SetOrientation, Orientation, orientations, O_HORIZONTAL, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Range", GetRange, SetRange, float, 1.0f, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Value", GetValue, SetValue, float, 0.0f, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Scroll Step", GetScrollStep, SetScrollStep, float, DEFAULT_SCROLL_STEP, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Step Factor", GetStepFactor, SetStepFactor, float, 1.0f, AM_FILE);
    URHO3D_ATTRIBUTE("Left Image Rect", leftRect_, IntRect::ZERO, AM_FILE);
    URHO3D_ATTRIBUTE("Right Image Rect", rightRect_, IntRect::ZERO, AM_FILE);
    URHO3D_ATTRIBUTE("Up Image Rect", upRect_, IntRect::ZERO, AM_FILE);
    URHO3D_ATTRIBUTE("Down Image Rect", downRect_, IntRect::ZERO, AM_FILE);
}

void ScrollBar::ApplyAttributes()
{
    BorderImage::ApplyAttributes();

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

void ScrollBar::OnResize(const IntVector2& newSize, const IntVector2& delta)
{
    if (slider_->GetOrientation() == O_HORIZONTAL)
    {
        int height = newSize.y_;
        int sliderWidth = Max(GetWidth() - 2 * height, 0);

        backButton_->SetSize(height, height);
        slider_->SetSize(sliderWidth, height);
        forwardButton_->SetSize(height, height);

        backButton_->SetPosition(0, 0);
        slider_->SetPosition(height, 0);
        forwardButton_->SetPosition(height + sliderWidth, 0);
    }
    else
    {
        int width = newSize.x_;
        int sliderHeight = Max(GetHeight() - 2 * width, 0);

        backButton_->SetSize(width, width);
        slider_->SetSize(width, sliderHeight);
        forwardButton_->SetSize(width, width);

        backButton_->SetPosition(0, 0);
        slider_->SetPosition(0, width);
        forwardButton_->SetPosition(0, sliderHeight + width);
    }
}

void ScrollBar::OnSetEditable()
{
    slider_->SetEditable(editable_);
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

    OnResize(GetSize(), IntVector2::ZERO);
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
    if (!BorderImage::FilterImplicitAttributes(dest))
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
    return FilterButtonImplicitAttributes(childElem, "SB_Forward");

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
    if (!RemoveChildXML(dest, "Focus Mode", "NotFocusable"))
        return false;

    return true;
}

void ScrollBar::HandleBackButtonPressed(StringHash eventType, VariantMap& eventData)
{
    if (editable_)
        StepBack();
}

void ScrollBar::HandleForwardButtonPressed(StringHash eventType, VariantMap& eventData)
{
    if (editable_)
        StepForward();
}

void ScrollBar::HandleSliderChanged(StringHash eventType, VariantMap& eventData)
{
    // Send the event forward
    VariantMap& newEventData = GetEventDataMap();
    newEventData[ScrollBarChanged::P_ELEMENT] = this;
    newEventData[ScrollBarChanged::P_VALUE] = slider_->GetValue();
    SendEvent(E_SCROLLBARCHANGED, newEventData);
}

void ScrollBar::HandleSliderPaged(StringHash eventType, VariantMap& eventData)
{
    using namespace SliderPaged;

    // Synthesize hover event to the forward/back buttons
    if (eventData[P_OFFSET].GetInt() < 0)
        backButton_->OnHover(IntVector2::ZERO, backButton_->ElementToScreen(IntVector2::ZERO), MOUSEB_NONE, QUAL_NONE, nullptr);
    else
        forwardButton_->OnHover(IntVector2::ZERO, forwardButton_->ElementToScreen(IntVector2::ZERO), MOUSEB_NONE, QUAL_NONE, nullptr);

    // Synthesize click / release events to the buttons
    if (eventData[P_PRESSED].GetBool())
    {
        if (eventData[P_OFFSET].GetInt() < 0)
            backButton_->OnClickBegin(IntVector2::ZERO, backButton_->ElementToScreen(IntVector2::ZERO),
                MOUSEB_LEFT, MOUSEB_LEFT, QUAL_NONE, nullptr);
        else
            forwardButton_->OnClickBegin(IntVector2::ZERO, forwardButton_->ElementToScreen(IntVector2::ZERO),
                MOUSEB_LEFT, MOUSEB_LEFT, QUAL_NONE, nullptr);
    }
    else
    {
        if (eventData[P_OFFSET].GetInt() < 0)
            backButton_->OnClickEnd(IntVector2::ZERO, backButton_->ElementToScreen(IntVector2::ZERO),
                MOUSEB_LEFT, MOUSEB_NONE, QUAL_NONE, nullptr, backButton_);
        else
            forwardButton_->OnClickEnd(IntVector2::ZERO, forwardButton_->ElementToScreen(IntVector2::ZERO),
                MOUSEB_LEFT, MOUSEB_NONE, QUAL_NONE, nullptr, forwardButton_);
    }
}

}
