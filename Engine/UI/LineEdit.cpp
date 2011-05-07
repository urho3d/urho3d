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

#include "Precompiled.h"
#include "Context.h"
#include "Input.h"
#include "LineEdit.h"
#include "Text.h"
#include "UI.h"
#include "UIEvents.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(LineEdit);

LineEdit::LineEdit(Context* context) :
    BorderImage(context),
    lastFont_(0),
    lastFontSize_(0),
    cursorPosition_(0),
    dragStartCursor_(M_MAX_UNSIGNED),
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
    
    text_ = new Text(context_);
    cursor_ = new BorderImage(context_);
    AddChild(text_);
    AddChild(cursor_);
    
    // Show cursor on top of text
    cursor_->SetPriority(1);
}

LineEdit::~LineEdit()
{
}

void LineEdit::RegisterObject(Context* context)
{
    context->RegisterFactory<LineEdit>();
}

void LineEdit::SetStyle(const XMLElement& element)
{
    BorderImage::SetStyle(element);
    
    if (element.HasChildElement("maxlength"))
        SetMaxLength(element.GetChildElement("maxlength").GetInt("value"));
    if (element.HasChildElement("cursormovable"))
        SetCursorMovable(element.GetChildElement("cursormovable").GetBool("enable"));
    if (element.HasChildElement("textselectable"))
        SetTextSelectable(element.GetChildElement("textselectable").GetBool("enable"));
    if (element.HasChildElement("textcopyable"))
        SetTextCopyable(element.GetChildElement("textcopyable").GetBool("enable"));
    
    XMLElement textElem = element.GetChildElement("text");
    if (textElem)
    {
        if (textElem.HasAttribute("value"))
            SetText(textElem.GetString("value"));
        text_->SetStyle(textElem);
    }
    
    XMLElement cursorElem = element.GetChildElement("cursor");
    if (cursorElem)
        cursor_->SetStyle(cursorElem);
    
    if (element.HasChildElement("cursorposition"))
        SetCursorPosition(element.GetChildElement("cursorposition").GetInt("value"));
    if (element.HasChildElement("cursorblinkrate"))
        SetCursorBlinkRate(element.GetChildElement("cursorblinkrate").GetFloat("value"));
    if (element.HasChildElement("echocharacter"))
    {
        std::string text = element.GetChildElement("echocharacter").GetString("value");
        if (text.length())
            SetEchoCharacter(text[0]);
    }
}

void LineEdit::Update(float timeStep)
{
    if (cursorBlinkRate_ > 0.0f)
        cursorBlinkTimer_ = fmodf(cursorBlinkTimer_ + cursorBlinkRate_ * timeStep, 1.0f);
    else
        cursorBlinkTimer_ = 0.0f;
    
    // Update cursor position if font has changed
    if ((text_->GetFont() != lastFont_) || (text_->GetFontSize() != lastFontSize_))
    {
        lastFont_ = text_->GetFont();
        lastFontSize_ = text_->GetFontSize();
        UpdateCursor();
    }
   
    bool cursorVisible = false;
    if (focus_)
        cursorVisible = cursorBlinkTimer_ < 0.5f;
    cursor_->SetVisible(cursorVisible);
}

void LineEdit::OnClick(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    if ((buttons & MOUSEB_LEFT) && (cursorMovable_))
    {
        unsigned pos = GetCharIndex(position);
        if (pos != M_MAX_UNSIGNED)
        {
            SetCursorPosition(pos);
            text_->ClearSelection();
        }
    }
}

void LineEdit::OnDragStart(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    dragStartCursor_ = GetCharIndex(position);
}

void LineEdit::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    if ((cursorMovable_) && (textSelectable_))
    {
        unsigned start = dragStartCursor_;
        unsigned current = GetCharIndex(position);
        if ((start != M_MAX_UNSIGNED) && (current != M_MAX_UNSIGNED))
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
    return (dynamic_cast<LineEdit*>(source) != 0);
}

bool LineEdit::OnDragDropFinish(UIElement* source)
{
    LineEdit* sourceLineEdit = dynamic_cast<LineEdit*>(source);
    if (sourceLineEdit)
    {
        SetText(sourceLineEdit->GetText());
        return true;
    }
    else
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
        if ((textCopyable_) && (qualifiers & QUAL_CTRL))
        {
            unsigned start = text_->GetSelectionStart();
            unsigned length = text_->GetSelectionLength();
            
            if (text_->GetSelectionLength())
                GetSubsystem<UI>()->SetClipBoardText(line_.substr(start, length));
            
            if (key == 'X')
            {
                if (start + length < line_.length())
                    line_ = line_.substr(0, start) + line_.substr(start + length);
                else
                    line_ = line_.substr(0, start);
                text_->ClearSelection();
                cursorPosition_ = start;
                changed = true;
            }
        }
        break;
        
    case 'V':
        if ((textCopyable_) && (qualifiers & QUAL_CTRL))
        {
            const std::string& clipBoard = GetSubsystem<UI>()->GetClipBoardText();
            if (clipBoard.length())
            {
                if (cursorPosition_ < line_.length())
                    line_ = line_.substr(0, cursorPosition_) + clipBoard + line_.substr(cursorPosition_);
                else
                    line_ += clipBoard;
                cursorPosition_ += clipBoard.length();
                changed = true;
            }
        }
        break;
        
    case KEY_LEFT:
        if (!(qualifiers & QUAL_SHIFT))
            text_->ClearSelection();
        if ((cursorMovable_) && (cursorPosition_ > 0))
        {
            if ((textSelectable_) && (qualifiers & QUAL_SHIFT) && (!text_->GetSelectionLength()))
                dragStartCursor_ = cursorPosition_;
            
            if (qualifiers & QUAL_CTRL)
                cursorPosition_ = 0;
            else
                --cursorPosition_;
            cursorMoved = true;
            
            if ((textSelectable_) && (qualifiers & QUAL_SHIFT))
            {
                unsigned start = dragStartCursor_;
                unsigned current = cursorPosition_;
                if (start < current)
                    text_->SetSelection(start, current - start);
                else
                    text_->SetSelection(current, start - current);
            }
        }
        break;
        
    case KEY_RIGHT:
        if (!(qualifiers & QUAL_SHIFT))
            text_->ClearSelection();
        if ((cursorMovable_) && (cursorPosition_ < line_.length()))
        {
            if ((textSelectable_) && (qualifiers & QUAL_SHIFT) && (!text_->GetSelectionLength()))
                dragStartCursor_ = cursorPosition_;
            
            if (qualifiers & QUAL_CTRL)
                cursorPosition_ = line_.length();
            else
                ++cursorPosition_;
            cursorMoved = true;
            
            if ((textSelectable_) && (qualifiers & QUAL_SHIFT))
            {
                unsigned start = dragStartCursor_;
                unsigned current = cursorPosition_;
                if (start < current)
                    text_->SetSelection(start, current - start);
                else
                    text_->SetSelection(current, start - current);
            }
        }
        break;
        
    case KEY_HOME:
        if ((cursorMovable_) && (cursorPosition_ > 0))
        {
            cursorPosition_ = 0;
            cursorMoved = true;
        }
        break;
        
    case KEY_END:
        if ((cursorMovable_) && (cursorPosition_ < line_.length()))
        {
            cursorPosition_ = line_.length();
            cursorMoved = true;
        }
        break;
        
    case KEY_DELETE:
        if (!text_->GetSelectionLength())
        {
            if (cursorPosition_ < line_.length())
            {
                line_ = line_.substr(0, cursorPosition_) + line_.substr(cursorPosition_ + 1);
                changed = true;
            }
        }
        else
        {
            // If a selection exists, erase it
            unsigned start = text_->GetSelectionStart();
            unsigned length = text_->GetSelectionLength();
            if (start + length < line_.length())
                line_ = line_.substr(0, start) + line_.substr(start + length);
            else
                line_ = line_.substr(0, start);
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
    }
    
    if (changed)
    {
        UpdateText();
        UpdateCursor();
    }
    else if (cursorMoved)
        UpdateCursor();
}

void LineEdit::OnChar(unsigned char c, int buttons, int qualifiers)
{
    bool changed = false;
    
    // If only CTRL is held down, do not edit
    if ((qualifiers & (QUAL_CTRL | QUAL_ALT)) == QUAL_CTRL)
        return;
    
    if (c == '\b')
    {
        if (!text_->GetSelectionLength())
        {
            if ((line_.length()) && (cursorPosition_))
            {
                if (cursorPosition_ < line_.length())
                    line_ = line_.substr(0, cursorPosition_ - 1) + line_.substr(cursorPosition_);
                else
                    line_ = line_.substr(0, cursorPosition_ - 1);
                --cursorPosition_;
                changed = true;
            }
        }
        else
        {
            // If a selection exists, erase it
            unsigned start = text_->GetSelectionStart();
            unsigned length = text_->GetSelectionLength();
            if (start + length < line_.length())
                line_ = line_.substr(0, start) + line_.substr(start + length);
            else
                line_ = line_.substr(0, start);
            text_->ClearSelection();
            cursorPosition_ = start;
            changed = true;
        }
    }
    else if (c == '\r')
    {
        using namespace TextFinished;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        eventData[P_TEXT] = line_;
        SendEvent(E_TEXTFINISHED, eventData);
        return;
    }
    else if ((c >= 0x20) && ((!maxLength_) || (line_.length() < maxLength_)))
    {
        std::string charStr;
        charStr.resize(1);
        charStr[0] = c;
        
        if (!text_->GetSelectionLength())
        {
            if (cursorPosition_ == line_.length())
                line_ += charStr;
            else
                line_ = line_.substr(0, cursorPosition_) + charStr + line_.substr(cursorPosition_);
            ++cursorPosition_;
        }
        else
        {
            // If a selection exists, erase it first
            unsigned start = text_->GetSelectionStart();
            unsigned length = text_->GetSelectionLength();
            if (start + length < line_.length())
                line_ = line_.substr(0, start) + charStr + line_.substr(start + length);
            else
                line_ = line_.substr(0, start) + charStr;
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

void LineEdit::OnFocus()
{
    UpdateCursor();
}

void LineEdit::OnDefocus()
{
    text_->ClearSelection();
}

void LineEdit::SetText(const std::string& text)
{
    if (text != line_)
    {
        line_ = text;
        cursorPosition_ = line_.length();
        UpdateText();
        UpdateCursor();
    }
}

void LineEdit::SetCursorPosition(unsigned position)
{
    if ((position > line_.length()) || (!cursorMovable_))
        position = line_.length();
    
    if (position != cursorPosition_)
    {
        cursorPosition_ = position;
        UpdateCursor();
    }
}

void LineEdit::SetCursorBlinkRate(float rate)
{
    cursorBlinkRate_ = Max(rate, 0.0f);
}

void LineEdit::SetMaxLength(unsigned length)
{
    maxLength_ = length;
}

void LineEdit::SetEchoCharacter(char c)
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
    if (!echoCharacter_)
        text_->SetText(line_);
    else
    {
        std::string echoText;
        echoText.resize(line_.length());
        for (unsigned i = 0; i < line_.length(); ++i)
            echoText[i] = echoCharacter_;
        text_->SetText(echoText);
    }
    if (cursorPosition_ > line_.length())
    {
        cursorPosition_ = line_.length();
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
    const std::vector<IntVector2>& charPositions = text_->GetCharPositions();
    if (charPositions.size())
        x = cursorPosition_ < charPositions.size() ? charPositions[cursorPosition_].x_ : charPositions.back().x_;
    
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
    SetChildOffset(IntVector2(-sx, 0));
    
    // Restart blinking
    cursorBlinkTimer_ = 0.0f;
}

unsigned LineEdit::GetCharIndex(const IntVector2& position)
{
    IntVector2 screenPosition = ElementToScreen(position);
    IntVector2 textPosition = text_->ScreenToElement(screenPosition);
    const std::vector<IntVector2>& charPositions = text_->GetCharPositions();
    
    if (textPosition.x_ < 0)
        return 0;
    
    for (unsigned i = charPositions.size() - 1; i < charPositions.size(); --i)
    {
        if (textPosition.x_ >= charPositions[i].x_)
            return i;
    }
    
    return M_MAX_UNSIGNED;
}
