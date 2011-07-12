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

#include "Precompiled.h"
#include "Button.h"
#include "Context.h"
#include "ScrollBar.h"
#include "Slider.h"
#include "UIEvents.h"

static const float DEFAULT_SCROLL_STEP = 0.1f;
static const float DEFAULT_REPEAT_DELAY = 0.4f;
static const float DEFAULT_REPEAT_RATE = 20.0f;

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
    active_ = true;
    
    backButton_ = new Button(context_);
    backButton_->SetRepeat(DEFAULT_REPEAT_DELAY, DEFAULT_REPEAT_RATE);
    forwardButton_ = new Button(context_);
    forwardButton_->SetRepeat(DEFAULT_REPEAT_DELAY, DEFAULT_REPEAT_RATE);
    slider_ = new Slider(context_);
    
    AddChild(backButton_);
    AddChild(slider_);
    AddChild(forwardButton_);
    
    SubscribeToEvent(backButton_, E_PRESSED, HANDLER(ScrollBar, HandleBackButtonPressed));
    SubscribeToEvent(forwardButton_, E_PRESSED, HANDLER(ScrollBar, HandleForwardButtonPressed));
    SubscribeToEvent(slider_, E_SLIDERCHANGED, HANDLER(ScrollBar, HandleSliderChanged));
    
    // Set default orientation/layout
    SetOrientation(O_HORIZONTAL);
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::RegisterObject(Context* context)
{
    context->RegisterFactory<ScrollBar>();
}

void ScrollBar::SetStyle(const XMLElement& element)
{
    UIElement::SetStyle(element);
    
    if (element.HasChild("range"))
    {
        XMLElement rangeElem = element.GetChild("range");
        SetRange(rangeElem.GetFloat("max"));
        SetValue(rangeElem.GetFloat("value"));
    }
    if (element.HasChild("scrollstep"))
        SetScrollStep(element.GetChild("scrollstep").GetFloat("value"));
    if (element.HasChild("stepfactor"))
        SetStepFactor(element.GetChild("stepfactor").GetFloat("value"));
    
    XMLElement backButtonElem = element.GetChild("backbutton");
    if (backButtonElem)
    {
        XMLElement imageElem = backButtonElem.GetChild("imagerect");
        if (imageElem.HasAttribute("horizontal"))
            leftRect_ = imageElem.GetIntRect("horizontal");
        if (imageElem.HasAttribute("vertical"))
            upRect_ = imageElem.GetIntRect("vertical");
        if (imageElem.HasAttribute("h"))
            leftRect_ = imageElem.GetIntRect("h");
        if (imageElem.HasAttribute("v"))
            upRect_ = imageElem.GetIntRect("v");
        backButton_->SetStyle(backButtonElem);
    }
    
    XMLElement forwardButtonElem = element.GetChild("forwardbutton");
    if (forwardButtonElem)
    {
        XMLElement imageElem = forwardButtonElem.GetChild("imagerect");
        if (imageElem.HasAttribute("horizontal"))
            rightRect_ = imageElem.GetIntRect("horizontal");
        if (imageElem.HasAttribute("vertical"))
            downRect_ = imageElem.GetIntRect("vertical");
        if (imageElem.HasAttribute("h"))
            rightRect_ = imageElem.GetIntRect("h");
        if (imageElem.HasAttribute("v"))
            downRect_ = imageElem.GetIntRect("v");
        forwardButton_->SetStyle(forwardButtonElem);
    }
    
    XMLElement sliderElem = element.GetChild("slider");
    if (sliderElem)
        slider_->SetStyle(sliderElem);
    
    if (element.HasChild("orientation"))
    {
        String orientation = element.GetChild("orientation").GetStringLower("value");
        if (orientation == "horizontal" || orientation == "h")
            SetOrientation(O_HORIZONTAL);
        if (orientation == "vertical" || orientation == "v")
            SetOrientation(O_VERTICAL);
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
