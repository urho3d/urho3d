//
// Copyright (c) 2008-2021 the Urho3D project.
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

#include "../UI/ScrollView.h"

namespace Urho3D
{

class Font;
class Text;

/// Multi-line text editor %UI element.
class URHO3D_API MultiLineEdit : public ScrollView
{
    URHO3D_OBJECT(MultiLineEdit, ScrollView);

public:
    /// Construct.
    explicit MultiLineEdit(Context* context);
    /// Destruct.
    ~MultiLineEdit() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately.
    void ApplyAttributes() override;
    /// Perform UI element update.
    void Update(float timeStep) override;
    /// React to mouse click begin.
    void OnClickBegin
        (const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override;
    /// React to mouse doubleclick.
    void OnDoubleClick
        (const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override;
    /// React to mouse drag begin.
    void
    OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override;
    /// React to mouse drag motion.
    void OnDragMove
        (const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers,
         Cursor* cursor) override;
    /// React to drag and drop test. Return true to signal that the drop is acceptable.
    bool OnDragDropTest(UIElement* source) override;
    /// React to drag and drop finish. Return true to signal that the drop was accepted.
    bool OnDragDropFinish(UIElement* source) override;
    /// React to a key press.
    void OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override;
    /// React to text input event.
    void OnTextInput(const String& text) override;

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
    /// Set padding around text field.
    void SetPaddings(IntRect paddings);

    /// Return text.
    const String& GetText() const { return string_; }

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

    /// Current padding around text field.
    IntRect GetPaddings() const { return paddings_; }

protected:
    /// Filter implicit attributes in serialization process.
    bool FilterImplicitAttributes(XMLElement& dest) const override;
    /// Update displayed text.
    void UpdateText();
    /// Update cursor position and restart cursor blinking.
    void UpdateCursor();
    /// Return char index corresponding to position within element, or M_MAX_UNSIGNED if not found.
    unsigned GetCharIndex(const IntVector2& position);
    /// Returns the position where the cursor might be when moving up
    unsigned GetIndexAtPreviousLine(int currentIndex);
    /// Returns the position where the cursor might be when moving down
    unsigned GetIndexAtNextLine(int currentIndex);
    /// Returns the position where the line started
    unsigned LineStartAtIndex(int currentIndex);
    /// Returns the position where the line ended
    unsigned LineEndAtIndex(int currentIndex);
    /// Resize text field container.
    void UpdateTextFieldContainerSize();

    /// Text element.
    SharedPtr<Text> text_;
    /// Cursor element.
    SharedPtr<BorderImage> cursor_;
    /// For make padding around.
    SharedPtr<UIElement> textFieldContainer_;
    /// Text copy.
    String string_;
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
    /// Padding around text field.
    IntRect paddings_;

private:
    /// Handle being focused.
    void HandleFocused(StringHash eventType, VariantMap& eventData);
    /// Handle being defocused.
    void HandleDefocused(StringHash eventType, VariantMap& eventData);
    /// Handle the element layout having been updated.
    void HandleLayoutUpdated(StringHash eventType, VariantMap& eventData);
    /// Handle the text field resize and update paddings around.
    void HandleTextFieldResize(StringHash eventType, VariantMap& eventData);
};

}
