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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Input/Input.h"
#include "../UI/MultiLineEdit.h"
#include "../UI/Text.h"
#include "../UI/UI.h"
#include "../UI/UIEvents.h"
#include "../UI/ScrollBar.h"

#include <SDL/SDL.h>

namespace Urho3D
{

StringHash VAR_MULTILINEDRAGDROPCONTENT("MultiLineDragDropContent");

extern const char* UI_CATEGORY;

MultiLineEdit::MultiLineEdit(Context* context) :
    ScrollView(context),
    lastFont_(nullptr),
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
    SetEnabled(true);
    focusMode_ = FM_FOCUSABLE_DEFOCUSABLE;

    textFieldContainer_ = new UIElement(GetContext());
    SetContentElement(textFieldContainer_);
    textFieldContainer_->SetEnabled(false);

    text_ = new Text(GetContext());
    text_->SetInternal(true);
    text_->SetAlignment(HA_CENTER, VA_CENTER);
    textFieldContainer_->AddChild(text_);
    text_->SetEnabled(false);
    SubscribeToEvent(text_, E_RESIZED, URHO3D_HANDLER(MultiLineEdit, HandleTextFieldResize));

    cursor_ = text_->CreateChild<BorderImage>("MLE_Cursor");
    cursor_->SetInternal(true);

    GetChild("SV_ScrollPanel", true)->SetEnabled(false);

    SubscribeToEvent(this, E_FOCUSED, URHO3D_HANDLER(MultiLineEdit, HandleFocused));
    SubscribeToEvent(this, E_DEFOCUSED, URHO3D_HANDLER(MultiLineEdit, HandleDefocused));
    SubscribeToEvent(this, E_LAYOUTUPDATED, URHO3D_HANDLER(MultiLineEdit, HandleLayoutUpdated));
}

MultiLineEdit::~MultiLineEdit() = default;

void MultiLineEdit::RegisterObject(Context* context)
{
    context->RegisterFactory<MultiLineEdit>(UI_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(BorderImage);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Clip Children", true);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Is Enabled", true);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Focus Mode", FM_FOCUSABLE_DEFOCUSABLE);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Length", GetMaxLength, SetMaxLength, unsigned, 0, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Is Cursor Movable", IsCursorMovable, SetCursorMovable, bool, true, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Is Text Selectable", IsTextSelectable, SetTextSelectable, bool, true, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Is Text Copyable", IsTextCopyable, SetTextCopyable, bool, true, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Cursor Blink Rate", GetCursorBlinkRate, SetCursorBlinkRate, float, 1.0f, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Paddings", GetPaddings, SetPaddings, IntRect, IntRect::ZERO, AM_FILE);
    URHO3D_ATTRIBUTE("Echo Character", int, echoCharacter_, 0, AM_FILE);
}

void MultiLineEdit::ApplyAttributes()
{
    UIElement::ApplyAttributes();

    // Sync the text line
    string_ = text_->GetText();

    XMLFile* style = GetDefaultStyle(true);
    text_->SetStyle(text_->GetTypeName(), style); // apply default
    if (appliedStyle_.Length() && style)
    {
        XMLElement multiLineEditStyle = style->GetRoot().GetChild();
        while (!multiLineEditStyle.IsNull() && multiLineEditStyle.GetAttribute("type") != appliedStyle_)
            multiLineEditStyle= multiLineEditStyle.GetNext();
        XMLElement textStyle = multiLineEditStyle.GetChild();
        while (!textStyle.IsNull() && textStyle.GetAttribute("type") != text_->GetTypeName())
            textStyle= textStyle.GetNext();
        if (!textStyle.IsNull())
            text_->SetStyle(textStyle);
    }

    UpdateTextFieldContainerSize();
}

void MultiLineEdit::Update(float timeStep)
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

void MultiLineEdit::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers,
    Cursor* cursor)
{
    if (button == MOUSEB_LEFT && cursorMovable_)
    {
        unsigned pos = GetCharIndex(position);
        if (pos != M_MAX_UNSIGNED)
        {
            SetCursorPosition(pos);
            text_->ClearSelection();
        }
    }
}

void MultiLineEdit::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button,
                                  MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)
{
    if (button == MOUSEB_LEFT)
        text_->SetSelection(0);
}

void MultiLineEdit::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons,
                                QualifierFlags qualifiers, Cursor* cursor)
{
    UIElement::OnDragBegin(position, screenPosition, buttons, qualifiers, cursor);

    dragBeginCursor_ = GetCharIndex(position);
}

void MultiLineEdit::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos,
                               MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)
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

bool MultiLineEdit::OnDragDropTest(UIElement* source)
{
    if (source && editable_)
    {
        if (source->GetVars().Contains(VAR_MULTILINEDRAGDROPCONTENT))
            return true;
        StringHash sourceType = source->GetType();
        return sourceType == MultiLineEdit::GetTypeStatic() || sourceType == Text::GetTypeStatic();
    }

    return false;
}

bool MultiLineEdit::OnDragDropFinish(UIElement* source)
{
    if (source && editable_)
    {
        // If the UI element in question has a drag-and-drop content string defined, use it instead of element text
        if (source->GetVars().Contains(VAR_MULTILINEDRAGDROPCONTENT))
        {
            SetText(source->GetVar(VAR_MULTILINEDRAGDROPCONTENT).GetString());
            return true;
        }

        StringHash sourceType = source->GetType();
        if (sourceType == MultiLineEdit::GetTypeStatic())
        {
            auto* sourceLineEdit = static_cast<MultiLineEdit*>(source);
            SetText(sourceLineEdit->GetText());
            return true;
        }
        else if (sourceType == Text::GetTypeStatic())
        {
            auto* sourceText = static_cast<Text*>(source);
            SetText(sourceText->GetText());
            return true;
        }
    }

    return false;
}

void MultiLineEdit::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers)
{
    bool changed = false;
    bool cursorMoved = false;

    switch (key)
    {
    case KEY_A:
        if (qualifiers & QUAL_CTRL)
        {
            text_->SetSelection(0, string_.Length());
        }
        break;
    case KEY_X:
    case KEY_C:
        if (textCopyable_ && qualifiers & QUAL_CTRL)
        {
            unsigned start = text_->GetSelectionStart();
            unsigned length = text_->GetSelectionLength();

            if (text_->GetSelectionLength())
                GetSubsystem<UI>()->SetClipboardText(string_.SubstringUTF8(start, length));

            if (key == KEY_X && editable_)
            {
                if (start + length < string_.LengthUTF8())
                    string_ = string_.SubstringUTF8(0, start) + string_.SubstringUTF8(start + length);
                else
                    string_ = string_.SubstringUTF8(0, start);
                text_->ClearSelection();
                cursorPosition_ = start;
                changed = true;
            }
        }
        break;

    case KEY_V:
        if (editable_ && textCopyable_ && qualifiers & QUAL_CTRL)
        {
            const String& clipBoard = GetSubsystem<UI>()->GetClipboardText();
            if (!clipBoard.Empty())
            {
                // Remove selected text first
                if (text_->GetSelectionLength() > 0)
                {
                    unsigned start = text_->GetSelectionStart();
                    unsigned length = text_->GetSelectionLength();
                    if (start + length < string_.LengthUTF8())
                        string_ = string_.SubstringUTF8(0, start) + string_.SubstringUTF8(start + length);
                    else
                        string_ = string_.SubstringUTF8(0, start);
                    text_->ClearSelection();
                    cursorPosition_ = start;
                }
                if (cursorPosition_ < string_.LengthUTF8())
                    string_ = string_.SubstringUTF8(0, cursorPosition_) + clipBoard + string_.SubstringUTF8(cursorPosition_);
                else
                    string_ += clipBoard;
                cursorPosition_ += clipBoard.LengthUTF8();
                changed = true;
            }
        }
        break;

    case KEY_HOME:
        if (cursorMovable_ && cursorPosition_ > 0)
        {
            if (textSelectable_ && qualifiers & QUAL_SHIFT && !text_->GetSelectionLength())
                dragBeginCursor_ = cursorPosition_;

            if (qualifiers & QUAL_CTRL)
                cursorPosition_ = 0;
            else
                cursorPosition_ = LineStartAtIndex(cursorPosition_);
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
        if (!(qualifiers & QUAL_SHIFT))
            text_->ClearSelection();
        break;

    case KEY_LEFT:
        if (cursorMovable_ && cursorPosition_ > 0)
        {
            if (textSelectable_ && qualifiers & QUAL_SHIFT && !text_->GetSelectionLength())
                dragBeginCursor_ = cursorPosition_;

            if (qualifiers & QUAL_CTRL)
                cursorPosition_ = 0;
            else if (text_->GetSelectionLength() && !(qualifiers & QUAL_SHIFT))
                cursorPosition_ = text_->GetSelectionStart();
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
        if (!(qualifiers & QUAL_SHIFT))
            text_->ClearSelection();
        break;

    case KEY_END:
        if (cursorMovable_ && cursorPosition_ < string_.LengthUTF8())
        {
            if (textSelectable_ && qualifiers & QUAL_SHIFT && !text_->GetSelectionLength())
                dragBeginCursor_ = cursorPosition_;

            if (qualifiers & QUAL_CTRL)
                cursorPosition_ = string_.Length();
            else
                cursorPosition_ = LineEndAtIndex(cursorPosition_);
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
            if (!(qualifiers & QUAL_SHIFT))
                text_->ClearSelection();
            break;

    case KEY_RIGHT:
        if (cursorMovable_ && cursorPosition_ < string_.LengthUTF8())
        {
            if (textSelectable_ && qualifiers & QUAL_SHIFT && !text_->GetSelectionLength())
                dragBeginCursor_ = cursorPosition_;

            if (qualifiers & QUAL_CTRL)
                cursorPosition_ = string_.LengthUTF8();
            else if (text_->GetSelectionLength() && !(qualifiers & QUAL_SHIFT))
                cursorPosition_ = text_->GetSelectionStart() + text_->GetSelectionLength();
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
        if (!(qualifiers & QUAL_SHIFT))
            text_->ClearSelection();
        break;

    case KEY_DELETE:
        if (editable_)
        {
            if (!text_->GetSelectionLength())
            {
                if (cursorPosition_ < string_.LengthUTF8())
                {
                    string_ = string_.SubstringUTF8(0, cursorPosition_) + string_.SubstringUTF8(cursorPosition_ + 1);
                    changed = true;
                }
            }
            else
            {
                // If a selection exists, erase it
                unsigned start = text_->GetSelectionStart();
                unsigned length = text_->GetSelectionLength();
                if (start + length < string_.LengthUTF8())
                    string_ = string_.SubstringUTF8(0, start) + string_.SubstringUTF8(start + length);
                else
                    string_ = string_.SubstringUTF8(0, start);
                text_->ClearSelection();
                cursorPosition_ = start;
                changed = true;
            }
        }
        break;

    case KEY_UP:
        if (cursorMovable_ && cursorPosition_ > 0)
        {
            if (textSelectable_ && qualifiers & QUAL_SHIFT && !text_->GetSelectionLength())
                dragBeginCursor_ = cursorPosition_;

            cursorPosition_ = GetIndexAtPreviousLine(cursorPosition_);
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
        if (!(qualifiers & QUAL_SHIFT))
            text_->ClearSelection();
        break;
    case KEY_DOWN:
        if (cursorMovable_ && cursorPosition_ < string_.LengthUTF8())
        {
            if (textSelectable_ && qualifiers & QUAL_SHIFT && !text_->GetSelectionLength())
                dragBeginCursor_ = cursorPosition_;

            cursorPosition_ = GetIndexAtNextLine(cursorPosition_);
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
        if (!(qualifiers & QUAL_SHIFT))
            text_->ClearSelection();
        break;
        break;
    case KEY_PAGEUP:
        if (cursorMovable_ && cursorPosition_ > 0)
        {
            if (textSelectable_ && qualifiers & QUAL_SHIFT && !text_->GetSelectionLength())
                dragBeginCursor_ = cursorPosition_;

            int scrollBarHorizontalHeight = GetHorizontalScrollBarVisible() ? horizontalScrollBar_->GetHeight() : 0;
            int pageHeight = (GetHeight() - scrollBarHorizontalHeight - paddings_.top_ - paddings_.bottom_) / text_->GetRowHeight();
            for (int i = 0; i < pageHeight; ++i)
                cursorPosition_ = GetIndexAtPreviousLine(cursorPosition_);
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
        if (!(qualifiers & QUAL_SHIFT))
            text_->ClearSelection();
        break;
    case KEY_PAGEDOWN:
        if (cursorMovable_ && cursorPosition_ < string_.LengthUTF8())
        {
            if (textSelectable_ && qualifiers & QUAL_SHIFT && !text_->GetSelectionLength())
                dragBeginCursor_ = cursorPosition_;

            int scrollBarHorizontalHeight = GetHorizontalScrollBarVisible() ? horizontalScrollBar_->GetHeight() : 0;
            int pageHeight = (GetHeight() - scrollBarHorizontalHeight - paddings_.top_ - paddings_.bottom_) / text_->GetRowHeight();
            for (int i = 0; i < pageHeight; ++i)
                cursorPosition_ = GetIndexAtNextLine(cursorPosition_);
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

    case KEY_BACKSPACE:
        if (editable_)
        {
            if (!text_->GetSelectionLength())
            {
                if (string_.LengthUTF8() && cursorPosition_)
                {
                    if (cursorPosition_ < string_.LengthUTF8())
                        string_ = string_.SubstringUTF8(0, cursorPosition_ - 1) + string_.SubstringUTF8(cursorPosition_);
                    else
                        string_ = string_.SubstringUTF8(0, cursorPosition_ - 1);
                    --cursorPosition_;
                    changed = true;
                }
            }
            else
            {
                // If a selection exists, erase it
                unsigned start = text_->GetSelectionStart();
                unsigned length = text_->GetSelectionLength();
                if (start + length < string_.LengthUTF8())
                    string_ = string_.SubstringUTF8(0, start) + string_.SubstringUTF8(start + length);
                else
                    string_ = string_.SubstringUTF8(0, start);
                text_->ClearSelection();
                cursorPosition_ = start;
                changed = true;
            }
        }
        break;

    case KEY_RETURN:
    case KEY_RETURN2:
    case KEY_KP_ENTER:
        if (editable_)
        {
            // Remove selected text first
            if (text_->GetSelectionLength() > 0)
            {
                unsigned start = text_->GetSelectionStart();
                unsigned length = text_->GetSelectionLength();
                if (start + length < string_.LengthUTF8())
                    string_ = string_.SubstringUTF8(0, start) + string_.SubstringUTF8(start + length);
                else
                    string_ = string_.SubstringUTF8(0, start);
                text_->ClearSelection();
                cursorPosition_ = start;
            }
            if (cursorPosition_ < string_.LengthUTF8())
                string_ = string_.SubstringUTF8(0, cursorPosition_) + "\n" + string_.SubstringUTF8(cursorPosition_);
            else
                string_ += "\n";
            cursorPosition_ += 1;
            changed = true;
        }

    default: break;
    }

    if (changed)
    {
        UpdateText();
        UpdateCursor();
    }
    else if (cursorMoved)
        UpdateCursor();
}

void MultiLineEdit::OnTextInput(const String& text)
{
    if (!editable_)
        return;

    bool changed = false;

    // Send text entry as an event to allow changing it
    using namespace TextEntry;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_ELEMENT] = this;
    eventData[P_TEXT] = text;
    SendEvent(E_TEXTENTRY, eventData);

    const String newText = eventData[P_TEXT].GetString().SubstringUTF8(0);
    if (!newText.Empty() && (!maxLength_ || string_.LengthUTF8() + newText.LengthUTF8() <= maxLength_))
    {
        if (!text_->GetSelectionLength())
        {
            if (cursorPosition_ == string_.LengthUTF8())
                string_ += newText;
            else
                string_ = string_.SubstringUTF8(0, cursorPosition_) + newText + string_.SubstringUTF8(cursorPosition_);
            cursorPosition_ += newText.LengthUTF8();
        }
        else
        {
            // If a selection exists, erase it first
            unsigned start = text_->GetSelectionStart();
            unsigned length = text_->GetSelectionLength();
            if (start + length < string_.LengthUTF8())
                string_ = string_.SubstringUTF8(0, start) + newText + string_.SubstringUTF8(start + length);
            else
                string_ = string_.SubstringUTF8(0, start) + newText;
            cursorPosition_ = start + newText.LengthUTF8();
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

void MultiLineEdit::SetText(const String& text)
{
    if (text != string_)
    {
        string_ = text;
        cursorPosition_ = string_.LengthUTF8();
        UpdateText();
        UpdateCursor();
    }
}

void MultiLineEdit::SetCursorPosition(unsigned position)
{
    if (position > string_.LengthUTF8() || !cursorMovable_)
        position = string_.LengthUTF8();

    if (position != cursorPosition_)
    {
        cursorPosition_ = position;
        UpdateCursor();
    }
}

void MultiLineEdit::SetCursorBlinkRate(float rate)
{
    cursorBlinkRate_ = Max(rate, 0.0f);

    if (cursorBlinkRate_ == 0.0f)
        cursorBlinkTimer_ = 0.0f;   // Cursor does not blink, i.e. always visible
}

void MultiLineEdit::SetMaxLength(unsigned length)
{
    maxLength_ = length;
}

void MultiLineEdit::SetEchoCharacter(unsigned c)
{
    echoCharacter_ = c;
    UpdateText();
}

void MultiLineEdit::SetCursorMovable(bool enable)
{
    cursorMovable_ = enable;
}

void MultiLineEdit::SetTextSelectable(bool enable)
{
    textSelectable_ = enable;
}

void MultiLineEdit::SetTextCopyable(bool enable)
{
    textCopyable_ = enable;
}

bool MultiLineEdit::FilterImplicitAttributes(XMLElement& dest) const
{
    if (!UIElement::FilterImplicitAttributes(dest))
        return false;

    XMLElement childElem = dest.GetChild("element");
    if (!childElem)
        return false;
    if (!RemoveChildXML(childElem, "Name", "MLE_Text"))
        return false;
    if (!RemoveChildXML(childElem, "Position"))
        return false;

    childElem = childElem.GetNext("element");
    if (!childElem)
        return false;
    if (!RemoveChildXML(childElem, "Name", "MLE_Cursor"))
        return false;
    if (!RemoveChildXML(childElem, "Priority", "1"))
        return false;
    if (!RemoveChildXML(childElem, "Position"))
        return false;
    if (!RemoveChildXML(childElem, "Is Visible"))
        return false;

    return true;
}

void MultiLineEdit::UpdateText()
{
    unsigned utf8Length = string_.LengthUTF8();

    if (!echoCharacter_)
        text_->SetText(string_);
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

    VariantMap& eventData = GetEventDataMap();
    eventData[P_ELEMENT] = this;
    eventData[P_TEXT] = string_;
    SendEvent(E_TEXTCHANGED, eventData);

    UpdateTextFieldContainerSize();
}

void MultiLineEdit::UpdateCursor()
{
    Vector2 characterPosition = text_->GetCharPosition(cursorPosition_);

    cursor_->SetPosition(characterPosition.x_, characterPosition.y_ - (text_->GetHeight() - text_->GetRowHeight()) / 2);
    cursor_->SetSize(cursor_->GetWidth(), text_->GetRowHeight());

    Vector2 cursorPosition = text_->GetCharPosition(cursorPosition_);
    IntVector2 viewPosition = GetViewPosition();
    int scrollBarVerticalWidth = GetVerticalScrollBarVisible() ? verticalScrollBar_->GetWidth() : 0;
    int scrollBarHorizontalHeight = GetHorizontalScrollBarVisible() ? horizontalScrollBar_->GetHeight() : 0;

    bool updateViewPosition = false;

    if (paddings_.left_ + viewPosition.x_ > cursorPosition.x_ + cursor_->GetWidth())
    {
        viewPosition.x_ = cursorPosition.x_ + cursor_->GetWidth() - paddings_.left_ ;
        updateViewPosition = true;
    }
    if (viewPosition.x_ + GetWidth() - scrollBarVerticalWidth - paddings_.left_ - paddings_.right_ <= cursorPosition.x_ + cursor_->GetWidth())
    {
        viewPosition.x_ = cursorPosition.x_ + cursor_->GetWidth() - GetWidth() + scrollBarVerticalWidth + paddings_.left_ + paddings_.right_;
        updateViewPosition = true;
    }
    if (viewPosition.y_ - paddings_.top_ + cursor_->GetHeight() >= cursorPosition.y_)
    {
        viewPosition.y_ = cursorPosition.y_ - paddings_.top_ ;
        updateViewPosition = true;
    }
    if (viewPosition.y_ + GetHeight() - scrollBarHorizontalHeight - paddings_.top_ - paddings_.bottom_ < cursorPosition.y_ + cursor_->GetHeight())
    {
        viewPosition.y_ = cursorPosition.y_ + cursor_->GetHeight() - GetHeight() + scrollBarHorizontalHeight + paddings_.top_ + paddings_.bottom_;
        updateViewPosition = true;
    }

    if(updateViewPosition)
        SetViewPosition(viewPosition);

    IntVector2 screenPosition = ElementToScreen(cursor_->GetPosition());
    SDL_Rect rect = {screenPosition.x_, screenPosition.y_, cursor_->GetSize().x_, cursor_->GetSize().y_};
    SDL_SetTextInputRect(&rect);

    // Restart blinking
    cursorBlinkTimer_ = 0.0f;
}

unsigned MultiLineEdit::GetCharIndex(const IntVector2& position)
{
    IntVector2 screenPosition = ElementToScreen(position);
    IntVector2 textPosition = text_->ScreenToElement(screenPosition);

    int line = textPosition.y_ / text_->GetRowHeight();
    int charWidth = 0;
    int pos = 0;
    while (!charWidth && ++pos < string_.Length())
        charWidth = text_->GetCharSize(pos).x_;
    if (charWidth == 0)
        return line;
    int index = 0;
    for (int i = 0; i < line; ++i)
        index += text_->GetRowWidth(i) / charWidth;
    index = LineEndAtIndex(index) + 1;
    while (true)
    {
        if (index >= string_.Length())
        {
            index = string_.Length() - 1;
            break;
        }
        if (textPosition.y_ < text_->GetCharPosition(index).y_)
            break;
        index--;
    }
    index++;
    for (; index >= 0; --index)
    {
        Vector2 pos = text_->GetCharPosition(index);
        if (textPosition.x_ >= pos.x_ && textPosition.y_ >= pos.y_)
            return index;
    }
    return M_MAX_UNSIGNED;
}

unsigned MultiLineEdit::GetIndexAtPreviousLine(int currentIndex)
{
    if (currentIndex < 0)
        return 0;
    int numChars = text_->GetNumChars();
    if (currentIndex > numChars)
        return numChars;
    int currentLineStartAtIndex = LineStartAtIndex(currentIndex);
    int positionInLine = currentIndex - currentLineStartAtIndex;
    int previousLineStartAtIndex = LineStartAtIndex(currentLineStartAtIndex - 1);
    if (previousLineStartAtIndex == currentLineStartAtIndex)
        return currentIndex;
    if (previousLineStartAtIndex + positionInLine < currentLineStartAtIndex - 1)
        return previousLineStartAtIndex + positionInLine;
    return currentLineStartAtIndex - 1;
}

unsigned MultiLineEdit::GetIndexAtNextLine(int currentIndex)
{
    if (currentIndex < 0)
        return 0;
    int numChars = text_->GetNumChars();
    if (currentIndex >= numChars)
        return numChars;
    int currentLineStartAtIndex = LineStartAtIndex(currentIndex);
    int currentLineEndAtIndex = LineEndAtIndex(currentIndex);
    int positionInLine = currentIndex - currentLineStartAtIndex;
    int nextLineEndAtIndex = LineEndAtIndex(currentLineEndAtIndex + 1);
    if (currentLineEndAtIndex == nextLineEndAtIndex)
        return currentIndex;
    if (currentLineEndAtIndex + 1 == nextLineEndAtIndex)
        return currentLineEndAtIndex + 1;
    if (currentLineEndAtIndex + positionInLine + 1 < nextLineEndAtIndex)
        return currentLineEndAtIndex + positionInLine + 1;
    if (nextLineEndAtIndex == numChars - 1)
        return currentIndex;
    return nextLineEndAtIndex;
}

unsigned MultiLineEdit::LineStartAtIndex(int currentIndex)
{
    if (currentIndex < 0)
        return 0;
    int numChars = text_->GetNumChars();
    if (currentIndex > numChars)
        return numChars - 1;

    for (int i = currentIndex - 1; i >= 0; --i)
    {
        if (string_.At(i) == '\n')
            return i + 1;
    }

    return 0;
}

unsigned MultiLineEdit::LineEndAtIndex(int currentIndex)
{
    if (currentIndex < 0)
        return 0;
    int numChars = text_->GetNumChars();
    if (currentIndex > numChars)
        return numChars - 1;

    for (int i = currentIndex; i < numChars; ++i)
    {
        if (string_.At(i) == '\n')
            return i;
    }

    return numChars;
}

void MultiLineEdit::HandleFocused(StringHash /*eventType*/, VariantMap& eventData)
{
    if (eventData[Focused::P_BYKEY].GetBool())
    {
        cursorPosition_ = string_.LengthUTF8();
        text_->SetSelection(0);
    }
    UpdateCursor();

    if (GetSubsystem<UI>()->GetUseScreenKeyboard())
        GetSubsystem<Input>()->SetScreenKeyboardVisible(true);
}

void MultiLineEdit::HandleDefocused(StringHash /*eventType*/, VariantMap& /*eventData*/)
{
    text_->ClearSelection();

    if (GetSubsystem<UI>()->GetUseScreenKeyboard())
        GetSubsystem<Input>()->SetScreenKeyboardVisible(false);
}

void MultiLineEdit::HandleLayoutUpdated(StringHash /*eventType*/, VariantMap& /*eventData*/)
{
    UpdateCursor();
}

void MultiLineEdit::SetPaddings(IntRect paddings)
{
    paddings_ = paddings;
}

void MultiLineEdit::HandleTextFieldResize(StringHash eventType, VariantMap &eventData)
{
    UpdateTextFieldContainerSize();
}

void MultiLineEdit::UpdateTextFieldContainerSize()
{
    textFieldContainer_->SetWidth(text_->GetWidth() + paddings_.left_ + paddings_.right_);
    textFieldContainer_->SetHeight(text_->GetHeight() + paddings_.top_ + paddings_.bottom_);

    // Set the text's position to match clipping and indent width, so that text left edge is not left partially hidden
    textFieldContainer_->SetPosition(GetIndentWidth() + clipBorder_.left_, clipBorder_.top_);
}

}
