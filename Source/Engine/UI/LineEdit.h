//
// Copyright (c) 2008-2014 the Urho3D project.
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

namespace Urho3D
{

/// Layout Edit Mode
enum LineEditMode
{
    /// Alpha-numeric mode
    LEM_ALL = 0,
    /// Numeric only mode. Formats the value to specified formatting string and enables drag editing.
    LEM_NUMERIC
};

class Font;
class Text;

/// Single-line text editor %UI element.
class URHO3D_API LineEdit : public BorderImage
{
    OBJECT(LineEdit);

public:
    /// Construct.
    LineEdit(Context* context);
    /// Destruct.
    virtual ~LineEdit();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately.
    virtual void ApplyAttributes();
    /// Perform UI element update.
    virtual void Update(float timeStep);
    /// React to mouse click begin.
    virtual void OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse click end.
    virtual void OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor, UIElement* beginElement);
    /// React to mouse doubleclick.
    virtual void OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse drag begin.
    virtual void OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse drag motion.
    virtual void OnDragMove(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse drag cancel.
    virtual void OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, int dragButtons, int buttons, Cursor* cursor);
    /// React to mouse drag ending.
    virtual void OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, int dragButtons, int buttons, Cursor* cursor);
    /// React to drag and drop test. Return true to signal that the drop is acceptable.
    virtual bool OnDragDropTest(UIElement* source);
    /// React to drag and drop finish. Return true to signal that the drop was accepted.
    virtual bool OnDragDropFinish(UIElement* source);
    /// React to a key press.
    virtual void OnKey(int key, int buttons, int qualifiers);
    /// React to text input event.
    virtual void OnTextInput(const String& text, int buttons, int qualifiers);

    /// Set text.
    void SetText(const String& text);
    /// Set cursor position.
    void SetCursorPosition(unsigned position);
    /// Set cursor blink rate. 0 disables blinking.
    void SetCursorBlinkRate(float rate);
    /// Set maximum text length. 0 for unlimited.
    void SetMaxLength(unsigned length);
    /// Set echo character for password entry and such. 0 (default) shows the actual text.
    void SetEchoCharacter(unsigned c);
    /// Set whether can move cursor with arrows or mouse, default true.
    void SetCursorMovable(bool enable);
    /// Set whether selections are allowed, default true.
    void SetTextSelectable(bool enable);
    /// Set whether copy-paste operations are allowed, default true.
    void SetTextCopyable(bool enable);
    /// Set the mode.
    void SetMode(LineEditMode mode);
    /// Set the string format.
    void SetNumericPrecision(unsigned precision);
    /// Set the numeric value of the element.
    void SetValue(float val);
    /// Set the drag edit combo.
    void SetDragEditCombo(int combo) { dragButton_ = combo; }
    /// Set drag edit increment amount.
    void SetDragEditIncrement(float incr) { dragIncrement_ = incr; }
    /// Set how much movement in pixels it takes to drag increment.
    void SetDragEditSmooth(float pixels) { dragEditSmooth_ = pixels; }

    /// Return text.
    const String& GetText() const { return line_; }
    /// Return cursor position.
    unsigned GetCursorPosition() const { return cursorPosition_; }
    /// Return cursor blink rate.
    float GetCursorBlinkRate() const { return cursorBlinkRate_; }
    /// Return maximum text length.
    unsigned GetMaxLength() const { return maxLength_; }
    /// Return echo character.
    unsigned GetEchoCharacter() const { return echoCharacter_; }
    /// Return whether can move cursor with arrows or mouse.
    bool IsCursorMovable() const { return cursorMovable_; }
    /// Return whether selections are allowed.
    bool IsTextSelectable() const { return textSelectable_; }
    /// Return whether copy-paste operations are allowed.
    bool IsTextCopyable() const { return textCopyable_; }
    /// Return text element.
    Text* GetTextElement() const { return text_; }
    /// Return cursor element.
    BorderImage* GetCursor() const { return cursor_; }
    /// Return the mode.
    LineEditMode GetMode() const { return mode_; }
    /// Return the string format.
    unsigned GetNumericPrecision() const { return numericPrecision_; }
    /// Return the value.
    float GetValue() const { return lineValue_; }
    /// Return the drag edit combo.
    int GetDragEditCombo() const { return dragButton_; }
    /// Return drag edit increment amount;
    float GetDragEditIncrement() const { return dragIncrement_; }
    /// Return how many pixels it takes to drag increment.
    float GetDragEditSmooth() const { return dragEditSmooth_; }

protected:
    /// Filter implicit attributes in serialization process.
    virtual bool FilterImplicitAttributes(XMLElement& dest) const;
    /// Update displayed text.
    void UpdateText();
    /// Update cursor position and restart cursor blinking.
    void UpdateCursor();
    /// Return char index corresponding to position within element, or M_MAX_UNSIGNED if not found.
    unsigned GetCharIndex(const IntVector2& position);

    /// Text element.
    SharedPtr<Text> text_;
    /// Cursor element.
    SharedPtr<BorderImage> cursor_;
    /// Text line.
    String line_;
    /// Last used text font.
    Font* lastFont_;
    /// Last used text size.
    int lastFontSize_;
    /// Text edit cursor position.
    unsigned cursorPosition_;
    /// Drag begin cursor position.
    unsigned dragBeginCursor_;
    /// Cursor blink rate.
    float cursorBlinkRate_;
    /// Cursor blink timer.
    float cursorBlinkTimer_;
    /// Maximum text length.
    unsigned maxLength_;
    /// Echo character.
    unsigned echoCharacter_;
    /// Cursor movable flag.
    bool cursorMovable_;
    /// Text selectable flag.
    bool textSelectable_;
    /// Copy-paste enable flag.
    bool textCopyable_;
    /// How to process the element
    LineEditMode mode_;
    /// The numerical value
    float lineValue_;
    /// The string formatting value.
    unsigned numericPrecision_;
    /// The drag edit combo.
    int dragButton_;
    /// Drag increment amount.
    float dragIncrement_;
    /// Value of text when Line Edit receives focus.
    String focusBeginLine_;
    /// How much movement in pixels should cause a drag increment
    float dragEditSmooth_;

private:
    /// Handle being focused.
    void HandleFocused(StringHash eventType, VariantMap& eventData);
    /// Handle being defocused.
    void HandleDefocused(StringHash eventType, VariantMap& eventData);
    /// Handle the element layout having been updated.
    void HandleLayoutUpdated(StringHash eventType, VariantMap& eventData);
    /// Format the value to string.
    void FormatString();

    /// Where drag editing begins.
    IntVector2 dragBeginPosition_;
    /// Where last drag edit position was.
    IntVector2 dragLastPosition_;
    /// Value when beginning drag.
    float dragBeginValue_;
    /// Value while dragging.
    float dragAccumValue_;
    /// Used to prevent text finished being sent when drag cancelling.
    bool sendTextFinishedEvent_;
};

}
