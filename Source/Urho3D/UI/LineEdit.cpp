// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Input/Input.h"
#include "../UI/LineEdit.h"
#include "../UI/Text.h"
#include "../UI/UI.h"
#include "../UI/UIEvents.h"

#include "../DebugNew.h"

#include <SDL/SDL.h>

namespace Urho3D
{

StringHash VAR_DRAGDROPCONTENT("DragDropContent");

extern const char* UI_CATEGORY;

LineEdit::LineEdit(Context* context) :
    BorderImage(context),
    lastFont_(nullptr),
    lastFontSize_(0),
    cursorPosition_(0),
    dragBeginCursor_(NINDEX),
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

    text_ = CreateChild<Text>("LE_Text");
    text_->SetInternal(true);
    cursor_ = CreateChild<BorderImage>("LE_Cursor");
    cursor_->SetInternal(true);
    cursor_->SetPriority(1); // Show over text

    SubscribeToEvent(this, E_FOCUSED, URHO3D_HANDLER(LineEdit, HandleFocused));
    SubscribeToEvent(this, E_DEFOCUSED, URHO3D_HANDLER(LineEdit, HandleDefocused));
    SubscribeToEvent(this, E_LAYOUTUPDATED, URHO3D_HANDLER(LineEdit, HandleLayoutUpdated));
}

LineEdit::~LineEdit() = default;

void LineEdit::RegisterObject(Context* context)
{
    context->RegisterFactory<LineEdit>(UI_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(BorderImage);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Clip Children", true);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Is Enabled", true);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Focus Mode", FM_FOCUSABLE_DEFOCUSABLE);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Length", GetMaxLength, SetMaxLength, unsigned, 0, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Is Cursor Movable", IsCursorMovable, SetCursorMovable, bool, true, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Is Text Selectable", IsTextSelectable, SetTextSelectable, bool, true, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Is Text Copyable", IsTextCopyable, SetTextCopyable, bool, true, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Cursor Blink Rate", GetCursorBlinkRate, SetCursorBlinkRate, float, 1.0f, AM_FILE);
    URHO3D_ATTRIBUTE("Echo Character", echoCharacter_, 0, AM_FILE);
}

void LineEdit::ApplyAttributes()
{
    BorderImage::ApplyAttributes();

    // Set the text's position to match clipping and indent width, so that text left edge is not left partially hidden
    text_->SetPosition(GetIndentWidth() + clipBorder_.left_, clipBorder_.top_);

    // Sync the text line
    line_ = text_->GetText();
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

void LineEdit::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers,
    Cursor* cursor)
{
    if (button == MOUSEB_LEFT && cursorMovable_)
    {
        i32 pos = GetCharIndex(position);
        if (pos != NINDEX)
        {
            SetCursorPosition(pos);
            text_->ClearSelection();
        }
    }
}

void LineEdit::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers,
    Cursor* cursor)
{
    if (button == MOUSEB_LEFT)
        text_->SetSelection(0);
}

void LineEdit::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers,
    Cursor* cursor)
{
    UIElement::OnDragBegin(position, screenPosition, buttons, qualifiers, cursor);

    dragBeginCursor_ = GetCharIndex(position);
}

void LineEdit::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons,
    QualifierFlags qualifiers, Cursor* cursor)
{
    if (cursorMovable_ && textSelectable_)
    {
        i32 start = dragBeginCursor_;
        i32 current = GetCharIndex(position);
        if (start != NINDEX && current != NINDEX)
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
    if (source && editable_)
    {
        if (source->GetVars().Contains(VAR_DRAGDROPCONTENT))
            return true;
        StringHash sourceType = source->GetType();
        return sourceType == LineEdit::GetTypeStatic() || sourceType == Text::GetTypeStatic();
    }

    return false;
}

bool LineEdit::OnDragDropFinish(UIElement* source)
{
    if (source && editable_)
    {
        // If the UI element in question has a drag-and-drop content string defined, use it instead of element text
        if (source->GetVars().Contains(VAR_DRAGDROPCONTENT))
        {
            SetText(source->GetVar(VAR_DRAGDROPCONTENT).GetString());
            return true;
        }

        StringHash sourceType = source->GetType();
        if (sourceType == LineEdit::GetTypeStatic())
        {
            auto* sourceLineEdit = static_cast<LineEdit*>(source);
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

void LineEdit::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers)
{
    bool changed = false;
    bool cursorMoved = false;

    switch (key)
    {
    case KEY_X:
    case KEY_C:
        if (textCopyable_ && qualifiers & QUAL_CTRL)
        {
            i32 start = text_->GetSelectionStart();
            i32 length = text_->GetSelectionLength();

            if (text_->GetSelectionLength())
                GetSubsystem<UI>()->SetClipboardText(line_.SubstringUTF8(start, length));

            if (key == KEY_X && editable_)
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

    case KEY_V:
        if (editable_ && textCopyable_ && qualifiers & QUAL_CTRL)
        {
            const String& clipBoard = GetSubsystem<UI>()->GetClipboardText();
            if (!clipBoard.Empty())
            {
                // Remove selected text first
                if (text_->GetSelectionLength() > 0)
                {
                    i32 start = text_->GetSelectionStart();
                    i32 length = text_->GetSelectionLength();
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
        [[fallthrough]];

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
                i32 start = dragBeginCursor_;
                i32 current = cursorPosition_;
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
        qualifiers |= QUAL_CTRL;
        [[fallthrough]];

    case KEY_RIGHT:
        if (cursorMovable_ && cursorPosition_ < line_.LengthUTF8())
        {
            if (textSelectable_ && qualifiers & QUAL_SHIFT && !text_->GetSelectionLength())
                dragBeginCursor_ = cursorPosition_;

            if (qualifiers & QUAL_CTRL)
                cursorPosition_ = line_.LengthUTF8();
            else if (text_->GetSelectionLength() && !(qualifiers & QUAL_SHIFT))
                cursorPosition_ = text_->GetSelectionStart() + text_->GetSelectionLength();
            else
                ++cursorPosition_;
            cursorMoved = true;

            if (textSelectable_ && qualifiers & QUAL_SHIFT)
            {
                i32 start = dragBeginCursor_;
                i32 current = cursorPosition_;
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
                if (cursorPosition_ < line_.LengthUTF8())
                {
                    line_ = line_.SubstringUTF8(0, cursorPosition_) + line_.SubstringUTF8(cursorPosition_ + 1);
                    changed = true;
                }
            }
            else
            {
                // If a selection exists, erase it
                i32 start = text_->GetSelectionStart();
                i32 length = text_->GetSelectionLength();
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

    case KEY_UP:
    case KEY_DOWN:
    case KEY_PAGEUP:
    case KEY_PAGEDOWN:
        {
            using namespace UnhandledKey;

            VariantMap& eventData = GetEventDataMap();
            eventData[P_ELEMENT] = this;
            eventData[P_KEY] = key;
            eventData[P_BUTTONS] = (unsigned)buttons;
            eventData[P_QUALIFIERS] = (unsigned)qualifiers;
            SendEvent(E_UNHANDLEDKEY, eventData);
        }
        return;

    case KEY_BACKSPACE:
        if (editable_)
        {
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
                i32 start = text_->GetSelectionStart();
                i32 length = text_->GetSelectionLength();
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

    case KEY_RETURN:
    case KEY_RETURN2:
    case KEY_KP_ENTER:
        {
            // If using the on-screen keyboard, defocus this element to hide it now
            if (GetSubsystem<UI>()->GetUseScreenKeyboard() && HasFocus())
                SetFocus(false);

            using namespace TextFinished;

            VariantMap& eventData = GetEventDataMap();
            eventData[P_ELEMENT] = this;
            eventData[P_TEXT] = line_;
            SendEvent(E_TEXTFINISHED, eventData);
            return;
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

void LineEdit::OnTextInput(const String& text)
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
    if (!newText.Empty() && (!maxLength_ || line_.LengthUTF8() + newText.LengthUTF8() <= maxLength_))
    {
        if (!text_->GetSelectionLength())
        {
            if (cursorPosition_ == line_.LengthUTF8())
                line_ += newText;
            else
                line_ = line_.SubstringUTF8(0, cursorPosition_) + newText + line_.SubstringUTF8(cursorPosition_);
            cursorPosition_ += newText.LengthUTF8();
        }
        else
        {
            // If a selection exists, erase it first
            i32 start = text_->GetSelectionStart();
            i32 length = text_->GetSelectionLength();
            if (start + length < line_.LengthUTF8())
                line_ = line_.SubstringUTF8(0, start) + newText + line_.SubstringUTF8(start + length);
            else
                line_ = line_.SubstringUTF8(0, start) + newText;
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

void LineEdit::SetCursorPosition(i32 position)
{
    assert(position >= 0);

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

void LineEdit::SetMaxLength(i32 length)
{
    assert(length >= 0);
    maxLength_ = length;
}

void LineEdit::SetEchoCharacter(c32 c)
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

bool LineEdit::FilterImplicitAttributes(XMLElement& dest) const
{
    if (!BorderImage::FilterImplicitAttributes(dest))
        return false;

    XMLElement childElem = dest.GetChild("element");
    if (!childElem)
        return false;
    if (!RemoveChildXML(childElem, "Name", "LE_Text"))
        return false;
    if (!RemoveChildXML(childElem, "Position"))
        return false;

    childElem = childElem.GetNext("element");
    if (!childElem)
        return false;
    if (!RemoveChildXML(childElem, "Name", "LE_Cursor"))
        return false;
    if (!RemoveChildXML(childElem, "Priority", "1"))
        return false;
    if (!RemoveChildXML(childElem, "Position"))
        return false;
    if (!RemoveChildXML(childElem, "Is Visible"))
        return false;

    return true;
}

void LineEdit::UpdateText()
{
    i32 utf8Length = line_.LengthUTF8();

    // If maxLength_ nonzero, truncate line to enforce length
    if (maxLength_ && utf8Length > maxLength_)
    {
        line_ = line_.SubstringUTF8(0, maxLength_);
        utf8Length = maxLength_;
    }

    if (!echoCharacter_)
    {
        text_->SetText(line_);
    }
    else
    {
        String echoText;
        for (i32 i = 0; i < utf8Length; ++i)
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
    eventData[P_TEXT] = line_;
    SendEvent(E_TEXTCHANGED, eventData);
}

void LineEdit::UpdateCursor()
{
    i32 x = text_->GetCharPosition(cursorPosition_).x_;

    text_->SetPosition(GetIndentWidth() + clipBorder_.left_, clipBorder_.top_);
    cursor_->SetPosition(text_->GetPosition() + IntVector2(x, 0));
    cursor_->SetSize(cursor_->GetWidth(), text_->GetRowHeight());

    IntVector2 screenPosition = ElementToScreen(cursor_->GetPosition());
    SDL_Rect rect = {screenPosition.x_, screenPosition.y_, cursor_->GetSize().x_, cursor_->GetSize().y_};
    SDL_SetTextInputRect(&rect);

    // Scroll if necessary
    i32 sx = -GetChildOffset().x_;
    i32 left = clipBorder_.left_;
    i32 right = GetWidth() - clipBorder_.left_ - clipBorder_.right_ - cursor_->GetWidth();
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

i32 LineEdit::GetCharIndex(const IntVector2& position)
{
    IntVector2 screenPosition = ElementToScreen(position);
    IntVector2 textPosition = text_->ScreenToElement(screenPosition);

    if (textPosition.x_ < 0)
        return 0;

    for (i32 i = text_->GetNumChars(); i >= 0; --i)
    {
        if (textPosition.x_ >= text_->GetCharPosition(i).x_)
            return i;
    }

    return NINDEX;
}

void LineEdit::HandleFocused(StringHash /*eventType*/, VariantMap& eventData)
{
    if (eventData[Focused::P_BYKEY].GetBool())
    {
        cursorPosition_ = line_.LengthUTF8();
        text_->SetSelection(0);
    }
    UpdateCursor();

    if (GetSubsystem<UI>()->GetUseScreenKeyboard())
        GetSubsystem<Input>()->SetScreenKeyboardVisible(true);
}

void LineEdit::HandleDefocused(StringHash /*eventType*/, VariantMap& /*eventData*/)
{
    text_->ClearSelection();

    if (GetSubsystem<UI>()->GetUseScreenKeyboard())
        GetSubsystem<Input>()->SetScreenKeyboardVisible(false);
}

void LineEdit::HandleLayoutUpdated(StringHash /*eventType*/, VariantMap& /*eventData*/)
{
    UpdateCursor();
}

}
