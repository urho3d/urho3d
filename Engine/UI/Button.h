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

#pragma once

#include "BorderImage.h"

/// Pushbutton %UI element.
class Button : public BorderImage
{
    OBJECT(Button);
    
    using UIElement::SetStyle;
    
public:
    /// Construct.
    Button(Context* context);
    /// Destruct.
    virtual ~Button();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// %Set UI element style from XML data.
    virtual void SetStyle(const XMLElement& element);
    /// Perform UI element update.
    virtual void Update(float timeStep);
    /// Return UI rendering batches.
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<UIQuad>& quads, const IntRect& currentScissor);
    /// React to mouse hover.
    virtual void OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse click.
    virtual void OnClick(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    
    /// %Set pressed image offset.
    void SetPressedOffset(const IntVector2& offset);
    /// %Set pressed image offset.
    void SetPressedOffset(int x, int y);
    /// %Set pressed label offset.
    void SetLabelOffset(const IntVector2& offset);
    /// %Set pressed label offset.
    void SetLabelOffset(int x, int y);
    /// %Set repeat properties. Rate 0 (default) disables repeat.
    void SetRepeat(float delay, float rate);
    /// %Set repeat delay.
    void SetRepeatDelay(float delay);
    /// %Set repeat rate.
    void SetRepeatRate(float rate);
    
    /// Return pressed image offset.
    const IntVector2& GetPressedOffset() const { return pressedOffset_; }
    /// Return pressed label offset.
    const IntVector2& GetLabelOffset() const { return labelOffset_; }
    /// Return repeat delay.
    float GetRepeatDelay() const { return repeatDelay_; }
    /// Return repeat rate.
    float GetRepeatRate() const { return repeatRate_; }
    
protected:
    /// %Set new pressed state.
    void SetPressed(bool enable);
    
    /// Pressed image offset.
    IntVector2 pressedOffset_;
    /// Pressed label offset.
    IntVector2 labelOffset_;
    /// Repeat delay.
    float repeatDelay_;
    /// Repeat rate.
    float repeatRate_;
    /// Repeat timer.
    float repeatTimer_;
    /// Current pressed state.
    bool pressed_;
};
