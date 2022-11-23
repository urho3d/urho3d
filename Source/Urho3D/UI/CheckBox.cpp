// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Input/InputEvents.h"
#include "../UI/CheckBox.h"
#include "../UI/UIEvents.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* UI_CATEGORY;

CheckBox::CheckBox(Context* context) :
    BorderImage(context),
    checkedOffset_(IntVector2::ZERO),
    checked_(false)
{
    SetEnabled(true);
    focusMode_ = FM_FOCUSABLE_DEFOCUSABLE;
}

CheckBox::~CheckBox() = default;

void CheckBox::RegisterObject(Context* context)
{
    context->RegisterFactory<CheckBox>(UI_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(BorderImage);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Is Enabled", true);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Focus Mode", FM_FOCUSABLE_DEFOCUSABLE);
    URHO3D_ACCESSOR_ATTRIBUTE("Is Checked", IsChecked, SetChecked, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Checked Image Offset", GetCheckedOffset, SetCheckedOffset, IntVector2::ZERO, AM_FILE);
}

void CheckBox::GetBatches(Vector<UIBatch>& batches, Vector<float>& vertexData, const IntRect& currentScissor)
{
    IntVector2 offset(IntVector2::ZERO);
    if (enabled_)
    {
        if (hovering_ || selected_ || HasFocus())
            offset += hoverOffset_;
    }
    else
        offset += disabledOffset_;
    if (checked_)
        offset += checkedOffset_;

    BorderImage::GetBatches(batches, vertexData, currentScissor, offset);
}

void CheckBox::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers,
    Cursor* cursor)
{
    if (button == MOUSEB_LEFT && editable_)
        SetChecked(!checked_);
}

void CheckBox::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers)
{
    if (HasFocus() && key == KEY_SPACE)
    {
        // Simulate LMB click
        OnClickBegin(IntVector2(), IntVector2(), MOUSEB_LEFT, MOUSEB_NONE, QUAL_NONE, nullptr);
    }
}

void CheckBox::SetChecked(bool enable)
{
    if (enable != checked_)
    {
        checked_ = enable;

        using namespace Toggled;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_ELEMENT] = this;
        eventData[P_STATE] = checked_;
        SendEvent(E_TOGGLED, eventData);
    }
}

void CheckBox::SetCheckedOffset(const IntVector2& offset)
{
    checkedOffset_ = offset;
}

void CheckBox::SetCheckedOffset(int x, int y)
{
    checkedOffset_ = IntVector2(x, y);
}

}
