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
#include "UIEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

OBJECTTYPESTATIC(Button);

Button::Button(Context* context) :
    BorderImage(context),
    pressedOffset_(IntVector2::ZERO),
    labelOffset_(IntVector2::ZERO),
    repeatDelay_(1.0f),
    repeatRate_(0.0f),
    repeatTimer_(0.0f),
    pressed_(false)
{
    enabled_ = true;
}

Button::~Button()
{
}

void Button::RegisterObject(Context* context)
{
    context->RegisterFactory<Button>();

    COPY_BASE_ATTRIBUTES(Button, BorderImage);
    REF_ACCESSOR_ATTRIBUTE(Button, VAR_INTVECTOR2, "Pressed Image Offset", GetPressedOffset, SetPressedOffset, IntVector2, IntVector2::ZERO, AM_FILE);
    REF_ACCESSOR_ATTRIBUTE(Button, VAR_INTVECTOR2, "Label Offset", GetLabelOffset, SetLabelOffset, IntVector2, IntVector2::ZERO, AM_FILE);
    ACCESSOR_ATTRIBUTE(Button, VAR_FLOAT, "Repeat Delay", GetRepeatDelay, SetRepeatDelay, float, 1.0f, AM_FILE);
    ACCESSOR_ATTRIBUTE(Button, VAR_FLOAT, "Repeat Rate", GetRepeatRate, SetRepeatRate, float, 0.0f, AM_FILE);
}

void Button::Update(float timeStep)
{
    if (!hovering_ && pressed_)
        SetPressed(false);

    // Send repeat events if pressed
    if (pressed_ && repeatRate_ > 0.0f)
    {
        repeatTimer_ -= timeStep;
        if (repeatTimer_ <= 0.0f)
        {
            repeatTimer_ += 1.0f / repeatRate_;

            using namespace Pressed;

            VariantMap eventData;
            eventData[P_ELEMENT] = (void*)this;
            SendEvent(E_PRESSED, eventData);
        }
    }
}

void Button::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    IntVector2 offset(IntVector2::ZERO);
    if (hovering_)
        offset += hoverOffset_;
    if (pressed_ || selected_)
        offset += pressedOffset_;

    BorderImage::GetBatches(batches, vertexData, currentScissor, offset);
}

void Button::OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    BorderImage::OnHover(position, screenPosition, buttons, qualifiers, cursor);
    if (pressed_)
    {
        if (!(buttons & MOUSEB_LEFT))
        {
            SetPressed(false);

            using namespace Released;

            VariantMap eventData;
            eventData[P_ELEMENT] = (void*)this;
            SendEvent(E_RELEASED, eventData);
        }
    }
}

void Button::OnClick(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    if (buttons & MOUSEB_LEFT)
    {
        SetPressed(true);
        repeatTimer_ = repeatDelay_;
        hovering_ = true;

        using namespace Pressed;

        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        SendEvent(E_PRESSED, eventData);
    }
}

void Button::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    SetPressed(true);
}

void Button::SetPressedOffset(const IntVector2& offset)
{
    pressedOffset_ = offset;
}

void Button::SetPressedOffset(int x, int y)
{
    pressedOffset_ = IntVector2(x, y);
}

void Button::SetLabelOffset(const IntVector2& offset)
{
    labelOffset_ = offset;
}

void Button::SetLabelOffset(int x, int y)
{
    labelOffset_ = IntVector2(x, y);
}

void Button::SetRepeat(float delay, float rate)
{
    SetRepeatDelay(delay);
    SetRepeatRate(rate);
}

void Button::SetRepeatDelay(float delay)
{
    repeatDelay_ = Max(delay, 0.0f);
}

void Button::SetRepeatRate(float rate)
{
    repeatRate_ = Max(rate, 0.0f);
}

void Button::SetPressed(bool enable)
{
    pressed_ = enable;
    SetChildOffset(pressed_ ? labelOffset_ : IntVector2::ZERO);
}

}
