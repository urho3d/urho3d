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
#include "Context.h"
#include "Input.h"
#include "LineEdit.h"
#include "Text.h"
#include "UI.h"
#include "UIEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

OBJECTTYPESTATIC(LineEdit);

LineEdit::LineEdit(Context* context) :
    BorderImage(context),
    lastFont_(0),
    lastFontSize_(0),
    cursorPosition_(0),
    dragBeginCursor_(M_MAX_UNSIGNED),
    cursorBlinkRate_(1.0f),
    cursorBlinkTimer_(0.0f),
    maxLength_(0),
    echoCharacter_(0),
    cursorMovable_(true),
    textSelectable_(true),
    textCopyable_(true)
{
    clipChildren_ = true;
    active_ = true;
    focusMode_ = FM_FOCUSABLE_DEFOCUSABLE;
    
    text_ = CreateChild<Text>();
    text_->SetInternal(true);
    cursor_ = CreateChild<BorderImage>();
    cursor_->SetInternal(true);
    cursor_->SetPriority(1); // Show over text
    
    SubscribeToEvent(this, E_FOCUSED, HANDLER(LineEdit, HandleFocused));
    SubscribeToEvent(this, E_DEFOCUSED, HANDLER(LineEdit, HandleDefocused));
}

LineEdit::~LineEdit()
{
}

void LineEdit::RegisterObject(Context* context)
{
    context->RegisterFactory<LineEdit>();
    
    ACCESSOR_ATTRIBUTE(LineEdit, VAR_INT, "Max Length", GetMaxLength, SetMaxLength, unsigned, 0, AM_FILE);
    ACCESSOR_ATTRIBUTE(LineEdit, VAR_BOOL, "Is Cursor Movable", IsCursorMovable, SetCursorMovable, bool, true, AM_FILE);
    ACCESSOR_ATTRIBUTE(LineEdit, VAR_BOOL, "Is Text Selectable", IsTextSelectable, SetTextSelectable, bool, true, AM_FILE);
    ACCESSOR_ATTRIBUTE(LineEdit, VAR_BOOL, "Is Text Copyable", IsTextCopyable, SetTextCopyable, bool, true, AM_FILE);
    ACCESSOR_ATTRIBUTE(LineEdit, VAR_FLOAT, "Cursor Blink Rate", GetCursorBlinkRate, SetCursorBlinkRate, float, 1.0f, AM_FILE);
    ATTRIBUTE(LineEdit, VAR_INT, "Echo Character", echoCharacter_, 0, AM_FILE);
    COPY_BASE_ATTRIBUTES(LineEdit, BorderImage);
}

void LineEdit::ApplyAttributes()
{
    BorderImage::ApplyAttributes();
    
    // Set the text's position to match clipping, so that text left edge is not left partially hidden
    text_->SetPosition(clipBorder_.left_, clipBorder_.top_);
}

void LineEdit::Update(float timeStep)
{
    if (cursorBlinkRate_ > 0.0f)
        cursorBlinkTimer_ = fmodf(cursorBlinkTimer_ + cursorBlinkRate_ * timeStep, 1.0f);
    
    // Update cursor position if font has changed
    if (text_->GetFont() != lastFont_ || text_->GetFontSize() != lastFontSize_)
    {
        lastFont_ = text_->GetFont();
        lastFontSize_ = text_->GetFontSize();
        UpdateCursor();
    }
   
    bool cursorVisible = HasFocus() ? cursorBlinkTimer_ < 0.5f : false;
    cursor_->SetVisible(cursorVisible);
}

void LineEdit::OnClick(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    if (buttons & MOUSEB_LEFT && cursorMovable_)
    {
        unsigned pos = GetCharIndex(position);
        if (pos != M_MAX_UNSIGNED)
        {
            SetCursorPosition(pos);
            text_->ClearSelection();
        }
    }
}

void LineEdit::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    dragBeginCursor_ = GetCharIndex(position);
}

void LineEdit::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    if (cursorMovable_ && textSelectable_)
    {
        unsigned start = dragBeginCursor_;
        unsigned current = GetCharIndex(position);
        if (start != M_MAX_UNSIGNED && current != M_MAX_UNSIGNED)
        {
            if (start < current)
                text_->SetSelection(start, current - start);
            else
                text_->SetSelection(current, start - current);
            SetCursorPosition(current);
        }
    }
}

bool LineEdit::OnDragDropTest(UIElement* source)
{
    if (source)
    {
        ShortStringHash sourceType = source->GetType();
        return sourceType == LineEdit::GetTypeStatic() || sourceType == Text::GetTypeStatic();
    }
    
    return false;
}

bool LineEdit::OnDragDropFinish(UIElement* source)
{
    if (source)
    {
        ShortStringHash sourceType = source->GetType();
        if (sourceType == LineEdit::GetTypeStatic())
        {
            LineEdit* sourceLineEdit = static_cast<LineEdit*>(source);
            SetText(sourceLineEdit->GetText());
            return true;
        }
        else if (sourceType == Text::GetTypeStatic())
        {
            Text* sourceText = static_cast<Text*>(source);
            SetText(sourceText->GetText());
            return true;
        }
    }
    
    return false;
}

void LineEdit::OnKey(int key, int buttons, int qualifiers)
{
    bool changed = false;
    bool cursorMoved = false;
    
    switch (key)
    {
    case 'X':
    case 'C':
        if (textCopyable_ && qualifiers & QUAL_CTRL)
        {
            unsigned start = text_->GetSelectionStart();
            unsigned length = text_->GetSelectionLength();
            
            if (text_->GetSelectionLength())
                GetSubsystem<UI>()->SetClipBoardText(line_.SubstringUTF8(start, length));
            
            if (key == 'X')
            {
                if (start + length < line_.LengthUTF8())
                    line_ = line_.SubstringUTF8(0, start) + line_.SubstringUTF8(start + length);
                else
                    line_ = line_.SubstringUTF8(0, start);
                text_->ClearSelection();
                cursorPosition_ = start;
                changed = true;
            }
        }
        break;
        
    case 'V':
        if (textCopyable_ && qualifiers & QUAL_CTRL)
        {
            const String& clipBoard = GetSubsystem<UI>()->GetClipBoardText();
            if (!clipBoard.Empty())
            {
                // Remove selected text first
                if(text_->GetSelectionLength() > 0)
                {
                    unsigned start = text_->GetSelectionStart();
                    unsigned length = text_->GetSelectionLength();
                    if (start + length < line_.LengthUTF8())
                        line_ = line_.SubstringUTF8(0, start) + line_.SubstringUTF8(start + length);
                    else
                        line_ = line_.SubstringUTF8(0, start);
                    text_->ClearSelection();
                    cursorPosition_ = start;
                }
                if (cursorPosition_ < line_.LengthUTF8())
                    line_ = line_.SubstringUTF8(0, cursorPosition_) + clipBoard + line_.SubstringUTF8(cursorPosition_);
                else
                    line_ += clipBoard;
                cursorPosition_ += clipBoard.LengthUTF8();
                changed = true;
            }
        }
        break;
        
    case KEY_HOME:
        qualifiers |= QUAL_CTRL;
        // Fallthru
            
    case KEY_LEFT:
        if (!(qualifiers & QUAL_SHIFT))
            text_->ClearSelection();
        if (cursorMovable_ && cursorPosition_ > 0)
        {
            if (textSelectable_ && qualifiers & QUAL_SHIFT && !text_->GetSelectionLength())
                dragBeginCursor_ = cursorPosition_;
            
            if (qualifiers & QUAL_CTRL)
                cursorPosition_ = 0;
            else
                --cursorPosition_;
            cursorMoved = true;
            
            if (textSelectable_ && qualifiers & QUAL_SHIFT)
            {
                unsigned start = dragBeginCursor_;
                unsigned current = cursorPosition_;
                if (start < current)
                    text_->SetSelection(start, current - start);
                else
                    text_->SetSelection(current, start - current);
            }
        }
        break;
        
    case KEY_END:
        qualifiers |= QUAL_CTRL;
        // Fallthru

    case KEY_RIGHT:
        if (!(qualifiers & QUAL_SHIFT))
            text_->ClearSelection();
        if (cursorMovable_ && cursorPosition_ < line_.LengthUTF8())
        {
            if (textSelectable_ && qualifiers & QUAL_SHIFT && !text_->GetSelectionLength())
                dragBeginCursor_ = cursorPosition_;
            
            if (qualifiers & QUAL_CTRL)
                cursorPosition_ = line_.LengthUTF8();
            else
                ++cursorPosition_;
            cursorMoved = true;
            
            if (textSelectable_ && qualifiers & QUAL_SHIFT)
            {
                unsigned start = dragBeginCursor_;
                unsigned current = cursorPosition_;
                if (start < current)
                    text_->SetSelection(start, current - start);
                else
                    text_->SetSelection(current, start - current);
            }
        }
        break;
        
    case KEY_DELETE:
        if (!text_->GetSelectionLength())
        {
            if (cursorPosition_ < line_.LengthUTF8())
            {
                line_ = line_.SubstringUTF8(0, cursorPosition_) + line_.SubstringUTF8(cursorPosition_ + 1);
                changed = true;
            }
        }
        else
        {
            // If a selection exists, erase it
            unsigned start = text_->GetSelectionStart();
            unsigned length = text_->GetSelectionLength();
            if (start + length < line_.LengthUTF8())
                line_ = line_.SubstringUTF8(0, start) + line_.SubstringUTF8(start + length);
            else
                line_ = line_.SubstringUTF8(0, start);
            text_->ClearSelection();
            cursorPosition_ = start;
            changed = true;
        }
        break;
        
    case KEY_UP:
    case KEY_DOWN:
    case KEY_PAGEUP:
    case KEY_PAGEDOWN:
        {
            using namespace UnhandledKey;
            
            VariantMap eventData;
            eventData[P_ELEMENT] = (void*)this;
            eventData[P_KEY] = key;
            eventData[P_BUTTONS] = buttons;
            eventData[P_QUALIFIERS] = qualifiers;
            SendEvent(E_UNHANDLEDKEY, eventData);
        }
        return;
        
    case KEY_BACKSPACE:
        if (!text_->GetSelectionLength())
        {
            if (line_.LengthUTF8() && cursorPosition_)
            {
                if (cursorPosition_ < line_.LengthUTF8())
                    line_ = line_.SubstringUTF8(0, cursorPosition_ - 1) + line_.SubstringUTF8(cursorPosition_);
                else
                    line_ = line_.SubstringUTF8(0, cursorPosition_ - 1);
                --cursorPosition_;
                changed = true;
            }
        }
        else
        {
            // If a selection exists, erase it
            unsigned start = text_->GetSelectionStart();
            unsigned length = text_->GetSelectionLength();
            if (start + length < line_.LengthUTF8())
                line_ = line_.SubstringUTF8(0, start) + line_.SubstringUTF8(start + length);
            else
                line_ = line_.SubstringUTF8(0, start);
            text_->ClearSelection();
            cursorPosition_ = start;
            changed = true;
        }
        break;
        
    case KEY_RETURN:
        {
            using namespace TextFinished;
            
            VariantMap eventData;
            eventData[P_ELEMENT] = (void*)this;
            eventData[P_TEXT] = line_;
            SendEvent(E_TEXTFINISHED, eventData);
            return;
        }
        break;
    }
    
    if (changed)
    {
        UpdateText();
        UpdateCursor();
    }
    else if (cursorMoved)
        UpdateCursor();
}

void LineEdit::OnChar(unsigned c, int buttons, int qualifiers)
{
    bool changed = false;
    
    // If only CTRL is held down, do not edit
    if ((qualifiers & (QUAL_CTRL | QUAL_ALT)) == QUAL_CTRL)
        return;
    
    if (c >= 0x20 && (!maxLength_ || line_.LengthUTF8() < maxLength_))
    {
        String charStr;
        charStr.AppendUTF8(c);

        if (!text_->GetSelectionLength())
        {
            if (cursorPosition_ == line_.LengthUTF8())
                line_ += charStr;
            else
                line_ = line_.SubstringUTF8(0, cursorPosition_) + charStr + line_.SubstringUTF8(cursorPosition_);
            ++cursorPosition_;
        }
        else
        {
            // If a selection exists, erase it first
            unsigned start = text_->GetSelectionStart();
            unsigned length = text_->GetSelectionLength();
            if (start + length < line_.LengthUTF8())
                line_ = line_.SubstringUTF8(0, start) + charStr + line_.SubstringUTF8(start + length);
            else
                line_ = line_.SubstringUTF8(0, start) + charStr;
            cursorPosition_ = start + 1;
        }
        changed = true;
    }
    
    if (changed)
    {
        text_->ClearSelection();
        UpdateText();
        UpdateCursor();
    }
}

void LineEdit::SetText(const String& text)
{
    if (text != line_)
    {
        line_ = text;
        cursorPosition_ = line_.LengthUTF8();
        UpdateText();
        UpdateCursor();
    }
}

void LineEdit::SetCursorPosition(unsigned position)
{
    if (position > line_.LengthUTF8() || !cursorMovable_)
        position = line_.LengthUTF8();
    
    if (position != cursorPosition_)
    {
        cursorPosition_ = position;
        UpdateCursor();
    }
}

void LineEdit::SetCursorBlinkRate(float rate)
{
    cursorBlinkRate_ = Max(rate, 0.0f);
    
    if (cursorBlinkRate_ == 0.0f)
        cursorBlinkTimer_ = 0.0f;   // Cursor does not blink, i.e. always visible
}

void LineEdit::SetMaxLength(unsigned length)
{
    maxLength_ = length;
}

void LineEdit::SetEchoCharacter(unsigned c)
{
    echoCharacter_ = c;
    UpdateText();
}

void LineEdit::SetCursorMovable(bool enable)
{
    cursorMovable_ = enable;
}

void LineEdit::SetTextSelectable(bool enable)
{
    textSelectable_ = enable;
}

void LineEdit::SetTextCopyable(bool enable)
{
    textCopyable_ = enable;
}

void LineEdit::UpdateText()
{
    unsigned utf8Length = line_.LengthUTF8();
    
    if (!echoCharacter_)
        text_->SetText(line_);
    else
    {
        String echoText;
        for (unsigned i = 0; i < utf8Length; ++i)
            echoText.AppendUTF8(echoCharacter_);
        text_->SetText(echoText);
    }
    if (cursorPosition_ > utf8Length)
    {
        cursorPosition_ = utf8Length;
        UpdateCursor();
    }
    
    using namespace TextChanged;
    
    VariantMap eventData;
    eventData[P_ELEMENT] = (void*)this;
    eventData[P_TEXT] = line_;
    SendEvent(E_TEXTCHANGED, eventData);
}

void LineEdit::UpdateCursor()
{
    int x = 0;
    const PODVector<IntVector2>& charPositions = text_->GetCharPositions();
    if (charPositions.Size())
        x = cursorPosition_ < charPositions.Size() ? charPositions[cursorPosition_].x_ : charPositions.Back().x_;
    
    text_->SetPosition(clipBorder_.left_, clipBorder_.top_);
    cursor_->SetPosition(text_->GetPosition() + IntVector2(x, 0));
    cursor_->SetSize(cursor_->GetWidth(), text_->GetRowHeight());
    
    // Scroll if necessary
    int sx = -GetChildOffset().x_;
    int left = clipBorder_.left_;
    int right = GetWidth() - clipBorder_.left_ - clipBorder_.right_ - cursor_->GetWidth();
    if (x - sx > right)
        sx = x - right;
    if (x - sx < left)
        sx = x - left;
    if (sx < 0)
        sx = 0;
    SetChildOffset(IntVector2(-sx, 0));
    
    // Restart blinking
    cursorBlinkTimer_ = 0.0f;
}

unsigned LineEdit::GetCharIndex(const IntVector2& position)
{
    IntVector2 screenPosition = ElementToScreen(position);
    IntVector2 textPosition = text_->ScreenToElement(screenPosition);
    const PODVector<IntVector2>& charPositions = text_->GetCharPositions();
    
    if (textPosition.x_ < 0)
        return 0;
    
    for (unsigned i = charPositions.Size() - 1; i < charPositions.Size(); --i)
    {
        if (textPosition.x_ >= charPositions[i].x_)
            return i;
    }
    
    return M_MAX_UNSIGNED;
}

void LineEdit::HandleFocused(StringHash eventType, VariantMap& eventData)
{
    UpdateCursor();
}

void LineEdit::HandleDefocused(StringHash eventType, VariantMap& eventData)
{
    text_->ClearSelection();
}

}
