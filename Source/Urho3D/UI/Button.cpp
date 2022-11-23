// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Input/InputEvents.h"
#include "../UI/Button.h"
#include "../UI/UI.h"
#include "../UI/UIEvents.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* UI_CATEGORY;

Button::Button(Context* context) :
    BorderImage(context),
    pressedOffset_(IntVector2::ZERO),
    pressedChildOffset_(IntVector2::ZERO),
    repeatDelay_(1.0f),
    repeatRate_(0.0f),
    repeatTimer_(0.0f),
    pressed_(false)
{
    SetEnabled(true);
    focusMode_ = FM_FOCUSABLE;
}

Button::~Button() = default;

void Button::RegisterObject(Context* context)
{
    context->RegisterFactory<Button>(UI_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(BorderImage);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Is Enabled", true);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Focus Mode", FM_FOCUSABLE);
    URHO3D_ACCESSOR_ATTRIBUTE("Pressed Image Offset", GetPressedOffset, SetPressedOffset, IntVector2::ZERO, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Pressed Child Offset", GetPressedChildOffset, SetPressedChildOffset, IntVector2::ZERO, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Repeat Delay", GetRepeatDelay, SetRepeatDelay, 1.0f, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Repeat Rate", GetRepeatRate, SetRepeatRate, 0.0f, AM_FILE);
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

            VariantMap& eventData = GetEventDataMap();
            eventData[P_ELEMENT] = this;
            SendEvent(E_PRESSED, eventData);
        }
    }
}

void Button::GetBatches(Vector<UIBatch>& batches, Vector<float>& vertexData, const IntRect& currentScissor)
{
    IntVector2 offset(IntVector2::ZERO);
    if (enabled_)
    {
        if (hovering_ || HasFocus())
            offset += hoverOffset_;
        if (pressed_ || selected_)
            offset += pressedOffset_;
    }
    else
    {
        offset += disabledOffset_;
    }

    BorderImage::GetBatches(batches, vertexData, currentScissor, offset);
}

void Button::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers,
    Cursor* cursor)
{
    if (button == MOUSEB_LEFT)
    {
        SetPressed(true);
        repeatTimer_ = repeatDelay_;
        hovering_ = true;

        using namespace Pressed;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_ELEMENT] = this;
        SendEvent(E_PRESSED, eventData);
    }
}

void Button::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers,
    Cursor* cursor, UIElement* beginElement)
{
    if (pressed_ && button == MOUSEB_LEFT)
    {
        SetPressed(false);
        // If mouse was released on top of the element, consider it hovering on this frame yet (see issue #1453)
        if (IsInside(screenPosition, true))
            hovering_ = true;

        using namespace Released;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_ELEMENT] = this;
        SendEvent(E_RELEASED, eventData);
    }
}

void Button::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons,
    QualifierFlags qualifiers, Cursor* cursor)
{
    SetPressed(true);
}

void Button::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers)
{
    if (HasFocus() && (key == KEY_RETURN || key == KEY_RETURN2 || key == KEY_KP_ENTER || key == KEY_SPACE))
    {
        // Simulate LMB click
        OnClickBegin(IntVector2(), IntVector2(), MOUSEB_LEFT, MOUSEB_NONE, QUAL_NONE, nullptr);
        OnClickEnd(IntVector2(), IntVector2(), MOUSEB_LEFT, MOUSEB_NONE, QUAL_NONE, nullptr, nullptr);
    }
}

void Button::SetPressedOffset(const IntVector2& offset)
{
    pressedOffset_ = offset;
}

void Button::SetPressedOffset(int x, int y)
{
    pressedOffset_ = IntVector2(x, y);
}

void Button::SetPressedChildOffset(const IntVector2& offset)
{
    pressedChildOffset_ = offset;
}

void Button::SetPressedChildOffset(int x, int y)
{
    pressedChildOffset_ = IntVector2(x, y);
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
    SetChildOffset(pressed_ ? pressedChildOffset_ : IntVector2::ZERO);
}

}
