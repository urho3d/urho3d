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

#pragma once

#include "../UI/BorderImage.h"

namespace Urho3D
{

/// Push button %UI element.
class URHO3D_API Button : public BorderImage
{
    URHO3D_OBJECT(Button, BorderImage);

public:
    /// Construct.
    explicit Button(Context* context);
    /// Destruct.
    ~Button() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Perform UI element update.
    void Update(float timeStep) override;
    /// Return UI rendering batches.
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;
    /// React to mouse click begin.
    void OnClickBegin
        (const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override;
    /// React to mouse click end.
    void OnClickEnd
        (const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor,
            UIElement* beginElement) override;
    /// React to mouse drag motion.
    void OnDragMove
        (const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers,
            Cursor* cursor) override;
    /// React to a key press.
    void OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override;

    /// Set offset to image rectangle used when pressed.
    void SetPressedOffset(const IntVector2& offset);
    /// Set offset to image rectangle used when pressed.
    void SetPressedOffset(int x, int y);
    /// Set offset of child elements when pressed.
    void SetPressedChildOffset(const IntVector2& offset);
    /// Set offset of child elements when pressed.
    void SetPressedChildOffset(int x, int y);
    /// Set repeat properties. Rate 0 (default) disables repeat.
    void SetRepeat(float delay, float rate);
    /// Set repeat delay.
    void SetRepeatDelay(float delay);
    /// Set repeat rate.
    void SetRepeatRate(float rate);

    /// Return pressed image offset.
    const IntVector2& GetPressedOffset() const { return pressedOffset_; }

    /// Return offset of child elements when pressed.
    const IntVector2& GetPressedChildOffset() const { return pressedChildOffset_; }

    /// Return repeat delay.
    float GetRepeatDelay() const { return repeatDelay_; }

    /// Return repeat rate.
    float GetRepeatRate() const { return repeatRate_; }

    /// Return whether is currently pressed.
    bool IsPressed() const { return pressed_; }

protected:
    /// Set new pressed state.
    void SetPressed(bool enable);

    /// Pressed image offset.
    IntVector2 pressedOffset_;
    /// Pressed label offset.
    IntVector2 pressedChildOffset_;
    /// Repeat delay.
    float repeatDelay_;
    /// Repeat rate.
    float repeatRate_;
    /// Repeat timer.
    float repeatTimer_;
    /// Current pressed state.
    bool pressed_;
};

}
