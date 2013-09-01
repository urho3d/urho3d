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
#include "Context.h"
#include "InputEvents.h"
#include "Log.h"
#include "Slider.h"
#include "UIEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

const char* orientations[] =
{
    "Horizontal",
    "Vertical",
    0
};

template<> Orientation Variant::Get<Orientation>() const
{
    return (Orientation)GetInt();
}

extern const char* UI_CATEGORY;

Slider::Slider(Context* context) :
    BorderImage(context),
    orientation_(O_HORIZONTAL),
    range_(1.0f),
    value_(0.0f),
    dragSlider_(false),
    repeatRate_(0.0f)
{
    enabled_ = true;
    knob_ = CreateChild<BorderImage>("S_Knob");
    knob_->SetInternal(true);

    UpdateSlider();
}

Slider::~Slider()
{
}

void Slider::RegisterObject(Context* context)
{
    context->RegisterFactory<Slider>(UI_CATEGORY);

    COPY_BASE_ATTRIBUTES(Slider, BorderImage);
    UPDATE_ATTRIBUTE_DEFAULT_VALUE(Slider, "Is Enabled", true);
    ENUM_ACCESSOR_ATTRIBUTE(Slider, "Orientation", GetOrientation, SetOrientation, Orientation, orientations, O_HORIZONTAL, AM_FILE);
    ACCESSOR_ATTRIBUTE(Slider, VAR_FLOAT, "Range", GetRange, SetRange, float, 1.0f, AM_FILE);
    ACCESSOR_ATTRIBUTE(Slider, VAR_FLOAT, "Value", GetValue, SetValue, float, 0.0f, AM_FILE);
    ACCESSOR_ATTRIBUTE(Slider, VAR_FLOAT, "Repeat Rate", GetRepeatRate, SetRepeatRate, float, 0.0f, AM_FILE);
}

void Slider::Update(float timeStep)
{
    if (dragSlider_)
        hovering_ = true;

    // Propagate hover effect to the slider knob
    knob_->SetHovering(hovering_);
    knob_->SetSelected(hovering_);
}

void Slider::OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    BorderImage::OnHover(position, screenPosition, buttons, qualifiers, cursor);

    // Show hover effect if inside the slider knob
    hovering_ = knob_->IsInside(screenPosition, true);

    // If not hovering on the knob, send it as page event
    if (!hovering_)
        Page(position, 0, buttons, qualifiers);
}

void Slider::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor)
{
    selected_ = true;
    hovering_ = knob_->IsInside(screenPosition, true);
    if (!hovering_)
        Page(position, button, buttons, qualifiers);
}

void Slider::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    dragBeginCursor_ = position;
    dragBeginPosition_ = knob_->GetPosition();
    dragSlider_ = knob_->IsInside(screenPosition, true);
}

void Slider::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    if (!dragSlider_ || GetSize() == knob_->GetSize())
        return;

    float newValue = value_;
    IntVector2 delta = position - dragBeginCursor_;

    if (orientation_ == O_HORIZONTAL)
    {
        int newX = Clamp(dragBeginPosition_.x_ + delta.x_, 0, GetWidth() - knob_->GetWidth());
        knob_->SetPosition(newX, 0);
        newValue = (float)newX * range_ / (float)(GetWidth() - knob_->GetWidth());
    }
    else
    {
        int newY = Clamp(dragBeginPosition_.y_ + delta.y_, 0, GetHeight() - knob_->GetHeight());
        knob_->SetPosition(0, newY);
        newValue = (float)newY * range_ / (float)(GetHeight() - knob_->GetHeight());
    }

    SetValue(newValue);
}

void Slider::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, Cursor* cursor)
{
    dragSlider_ = false;
    selected_ = false;
}

void Slider::OnResize()
{
    UpdateSlider();
}

void Slider::SetOrientation(Orientation type)
{
    orientation_ = type;
    UpdateSlider();
}

void Slider::SetRange(float range)
{
    range = Max(range, 0.0f);
    if (range != range_)
    {
        range_ = range;
        UpdateSlider();
    }
}

void Slider::SetValue(float value)
{
    value = Clamp(value, 0.0f, range_);
    if (value != value_)
    {
        value_ = value;
        UpdateSlider();

        using namespace SliderChanged;

        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        eventData[P_VALUE] = value_;
        SendEvent(E_SLIDERCHANGED, eventData);
    }
}

void Slider::ChangeValue(float delta)
{
    SetValue(value_ + delta);
}

void Slider::SetRepeatRate(float rate)
{
    repeatRate_ = Max(rate, 0.0f);
}

bool Slider::FilterImplicitAttributes(XMLElement& dest) const
{
    if (!BorderImage::FilterImplicitAttributes(dest))
        return false;

    XMLElement childElem = dest.GetChild("element");
    if (!childElem)
        return false;
    if (!RemoveChildXML(childElem, "Name", "S_Knob"))
        return false;
    if (!RemoveChildXML(childElem, "Position"))
        return false;
    if (!RemoveChildXML(childElem, "Size"))
        return false;

    return true;
}

void Slider::UpdateSlider()
{
    const IntRect& border = knob_->GetBorder();

    if (range_ > 0.0f)
    {
        if (orientation_ == O_HORIZONTAL)
        {
            int sliderLength = (int)Max((float)GetWidth() / (range_ + 1.0f), (float)(border.left_ + border.right_));
            float sliderPos = (float)(GetWidth() - sliderLength) * value_ / range_;
            knob_->SetSize(sliderLength, GetHeight());
            knob_->SetPosition(Clamp((int)(sliderPos + 0.5f), 0, GetWidth() - knob_->GetWidth()), 0);
        }
        else
        {
            int sliderLength = (int)Max((float)GetHeight() / (range_ + 1.0f), (float)(border.top_ + border.bottom_));
            float sliderPos = (float)(GetHeight() - sliderLength) * value_ / range_;
            knob_->SetSize(GetWidth(), sliderLength);
            knob_->SetPosition(0, Clamp((int)(sliderPos + 0.5f), 0, GetHeight() - knob_->GetHeight()));
        }
    }
    else
    {
        knob_->SetSize(GetSize());
        knob_->SetPosition(0, 0);
    }
}

void Slider::Page(const IntVector2& position, int button, int buttons, int qualifiers)
{
    IntVector2 offsetXY = position - knob_->GetPosition() - knob_->GetSize() / 2;
    int offset = orientation_ == O_HORIZONTAL ? offsetXY.x_ : offsetXY.y_;
    float length = (float)(orientation_ == O_HORIZONTAL ? GetWidth() : GetHeight());

    using namespace SliderPaged;

    VariantMap eventData;
    eventData[P_ELEMENT] = (void*)this;
    eventData[P_OFFSET] = offset;
    // Only generate the 'click' variant of the event when the slider is selected
    // i.e. when it has received the first initial click.
    if (selected_ && repeatRate_ > 0.0f && repeatTimer_.GetMSec(false) >= Lerp(1000.0f / repeatRate_, 0, Abs(offset) / length))
    {
        repeatTimer_.Reset();
        eventData[P_BUTTON] = button;
        eventData[P_BUTTONS] = buttons;
        eventData[P_QUALIFIERS] = qualifiers;
    }
    // When without buttons & qualifiers parameters, the receiver should interpret
    // this event as just mouse hovering on slider's 'paging' area instead
    SendEvent(E_SLIDERPAGED, eventData);
}

}
