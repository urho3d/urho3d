//
// Copyright (c) 2008-2015 the Urho3D project.
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

/// Pushbutton %UI element.
class URHO3D_API Button : public BorderImage
{
    OBJECT(Button);
    
public:
    /// Construct.
    Button(Context* context);
    /// Destruct.
    virtual ~Button();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Perform UI element update.
    virtual void Update(float timeStep);
    /// Return UI rendering batches.
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);
    /// React to mouse click begin.
    virtual void OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse click end.
    virtual void OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement);
    /// React to mouse drag motion.
    virtual void OnDragMove(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to a key press.
    virtual void OnKey(int key, int buttons, int qualifiers);

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
