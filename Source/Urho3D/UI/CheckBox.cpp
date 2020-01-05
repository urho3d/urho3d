//
// Copyright (c) 2008-2020 the Urho3D project.
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
    URHO3D_ACCESSOR_ATTRIBUTE("Is Checked", IsChecked, SetChecked, bool, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Checked Image Offset", GetCheckedOffset, SetCheckedOffset, IntVector2, IntVector2::ZERO, AM_FILE);
}

void CheckBox::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
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

void CheckBox::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers,
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
        OnClickBegin(IntVector2(), IntVector2(), MOUSEB_LEFT, 0, 0, nullptr);
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
