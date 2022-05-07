// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
    /// @nobind
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
    /// @property
    void SetPressedOffset(const IntVector2& offset);
    /// Set offset to image rectangle used when pressed.
    void SetPressedOffset(int x, int y);
    /// Set offset of child elements when pressed.
    /// @property
    void SetPressedChildOffset(const IntVector2& offset);
    /// Set offset of child elements when pressed.
    void SetPressedChildOffset(int x, int y);
    /// Set repeat properties. Rate 0 (default) disables repeat.
    void SetRepeat(float delay, float rate);
    /// Set repeat delay.
    /// @property
    void SetRepeatDelay(float delay);
    /// Set repeat rate.
    /// @property
    void SetRepeatRate(float rate);

    /// Return pressed image offset.
    /// @property
    const IntVector2& GetPressedOffset() const { return pressedOffset_; }

    /// Return offset of child elements when pressed.
    /// @property
    const IntVector2& GetPressedChildOffset() const { return pressedChildOffset_; }

    /// Return repeat delay.
    /// @property
    float GetRepeatDelay() const { return repeatDelay_; }

    /// Return repeat rate.
    /// @property
    float GetRepeatRate() const { return repeatRate_; }

    /// Return whether is currently pressed.
    /// @property
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
