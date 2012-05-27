//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

OBJECTTYPESTATIC(Slider);

Slider::Slider(Context* context) :
    BorderImage(context),
    orientation_(O_HORIZONTAL),
    range_(1.0f),
    value_(0.0f),
    dragSlider_(false)
{
    active_ = true;
    knob_ = new BorderImage(context_);
    AddChild(knob_);
    
    UpdateSlider();
}

Slider::~Slider()
{
}

void Slider::RegisterObject(Context* context)
{
    context->RegisterFactory<Slider>();
}

void Slider::SetStyle(const XMLElement& element)
{
    BorderImage::SetStyle(element);
    
    if (element.HasChild("orientation"))
    {
        String orientation = element.GetChild("orientation").GetAttributeLower("value");
        if (orientation == "horizontal" || orientation == "h")
            SetOrientation(O_HORIZONTAL);
        if (orientation == "vertical" || orientation == "v")
            SetOrientation(O_VERTICAL);
    }
    if (element.HasChild("range"))
    {
        XMLElement rangeElem = element.GetChild("range");
        SetRange(rangeElem.GetFloat("max"));
        SetValue(rangeElem.GetFloat("value"));
    }
    
    XMLElement knobElem = element.GetChild("knob");
    if (knobElem)
        knob_->SetStyle(knobElem);
}

void Slider::Update(float timeStep)
{
    if (dragSlider_)
        hovering_ = true;
    
    // Propagate hover and selection effect to the slider knob
    knob_->SetHovering(hovering_);
    knob_->SetSelected(selected_);
}

void Slider::OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    // Show hover effect if inside the slider knob
    hovering_ = knob_->IsInside(screenPosition, true);
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
