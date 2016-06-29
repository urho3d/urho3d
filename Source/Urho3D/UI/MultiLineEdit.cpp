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

#include "Urho3D/Precompiled.h"

#include "Urho3D/Core/Context.h"
#include "Urho3D/Input/Input.h"
#include "MultiLineEdit.h"
#include "Urho3D/UI/Text.h"
#include "Urho3D/UI/LineEdit.h"
#include "Urho3D/UI/UI.h"
#include "Urho3D/UI/UIEvents.h"
#include <Urho3D/IO/Log.h>
#include "Urho3D/DebugNew.h"

namespace Urho3D
{

StringHash VAR_ML_DRAGDROPCONTENT("DragDropContent");

extern const char* UI_CATEGORY;

MultiLineEdit::MultiLineEdit(Context* context) :
    Text(context),
    lastFont_(0),
    lastFontSize_(0),
    cursorPosition_(0),
	cursorPosition_x(0),
	cursorPosition_y(0),
    dragBeginCursor_(M_MAX_UNSIGNED),
    cursorBlinkRate_(1.0f),
    cursorBlinkTimer_(0.0f),
    maxLength_(0),
    echoCharacter_(0),
    cursorMovable_(true),
    textSelectable_(true),
    textCopyable_(true),
	multiLine_(false)
{
    clipChildren_ = true;
    SetEnabled(true);
    focusMode_ = FM_FOCUSABLE_DEFOCUSABLE;

    text_ = CreateChild<Text>("LE_Text");
    text_->SetInternal(true);
    cursor_ = CreateChild<Text>("LE_Cursor");
	cursor_->SetText("|");
	cursor_->SetStyleAuto();
    cursor_->SetInternal(true);
    cursor_->SetPriority(100); // Show over text

    SubscribeToEvent(this, E_FOCUSED, URHO3D_HANDLER(MultiLineEdit, HandleFocused));
    SubscribeToEvent(this, E_DEFOCUSED, URHO3D_HANDLER(MultiLineEdit, HandleDefocused));
    SubscribeToEvent(this, E_LAYOUTUPDATED, URHO3D_HANDLER(MultiLineEdit, HandleLayoutUpdated));
	SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(MultiLineEdit, HandleKeyDown));

	hasMaxLines = false;
	MaxLines = 0;
}

MultiLineEdit::~MultiLineEdit()
{
}

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
	URHO3D_ATTRIBUTE("Echo Character", int, echoCharacter_, 0, AM_FILE);
}
int MultiLineEdit::GetNumLines() 
{
	String Alltext = text_->GetText();
	int startpos = 0;
	int counter = 0;
	while (startpos >= 0) {
		counter++;
		startpos = Alltext.Find("\n", startpos);
		if (startpos != -1) startpos += 1;
	}
	Log::WriteRaw("num lines  " + String(counter));
	return counter;
}

void MultiLineEdit::ApplyAttributes()
{
    Text::ApplyAttributes();

    // Set the text's position to match clipping and indent width, so that text left edge is not left partially hidden
    text_->SetPosition(GetIndentWidth() + clipBorder_.left_, clipBorder_.top_);

    // Sync the text line
    line_ = text_->GetText();
}

void MultiLineEdit::Update(float timeStep)
{
	cursor_->SetFont(text_->GetFont(), text_->GetFontSize());
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
	//cursor_->SetVisible(true);
}

void MultiLineEdit::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers,
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

void MultiLineEdit::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers,
    Cursor* cursor)
{
    if (button == MOUSEB_LEFT)
        text_->SetSelection(0);
}

void MultiLineEdit::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers,
    Cursor* cursor)
{
    UIElement::OnDragBegin(position, screenPosition, buttons, qualifiers, cursor);

    dragBeginCursor_ = GetCharIndex(position);
}

void MultiLineEdit::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, int buttons,
    int qualifiers, Cursor* cursor)
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
        if (source->GetVars().Contains(VAR_ML_DRAGDROPCONTENT))
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
        if (source->GetVars().Contains(VAR_ML_DRAGDROPCONTENT))
        {
            SetText(source->GetVar(VAR_ML_DRAGDROPCONTENT).GetString());
            return true;
        }

        StringHash sourceType = source->GetType();
        if (sourceType == MultiLineEdit::GetTypeStatic())
        {
            MultiLineEdit* sourceMultiLineEdit = static_cast<MultiLineEdit*>(source);
            SetText(sourceMultiLineEdit->GetText());
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

void MultiLineEdit::OnKey(int key, int buttons, int qualifiers)
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
                GetSubsystem<UI>()->SetClipboardText(line_.SubstringUTF8(start, length));

            if (key == 'X' && editable_)
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
        qualifiers |= QUAL_CTRL;
        // Fallthru

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
        }
        break;

    case KEY_UP:
		if (multiLine_ && cursorMovable_ && cursorPosition_ > 0) {
			// get substring from start to cursor position
			String substring = line_.SubstringUTF8(0,cursorPosition_);
			// find nearest new line before cursor position
			unsigned lastlinepos = substring.FindLast("\n");
			// get substring from start to above new line
			String substring2 = substring.SubstringUTF8(0, (lastlinepos - 1));
			// find position of new line directly before previous
			unsigned lastlinepos2 = substring2.FindLast("\n");
			// move cursor to above position depending on width of above line
			if (lastlinepos - lastlinepos2 >= cursorPosition_ - lastlinepos) {
				cursorPosition_ = lastlinepos2 + (cursorPosition_ - lastlinepos);
			}
			else {
				cursorPosition_ = lastlinepos;
			}
			
		}
		changed = true;
		break;

    case KEY_DOWN:
		if (multiLine_ && cursorMovable_ && cursorPosition_ > 0) {
			// get substring from start to cursor position
			String substring = line_.SubstringUTF8(0, cursorPosition_);
			// find nearest new line before cursor position
			unsigned lastlinepos = substring.FindLast("\n");
			// get substring from cursor position to end
			String substring2 = line_.SubstringUTF8(cursorPosition_);
			// find position of new line after cursor postion
			unsigned nextlinepos = substring2.Find("\n") + cursorPosition_;
			// get substring from new line after cursor to end
			String substring3 = line_.SubstringUTF8(nextlinepos+1);
			// find position of new line after previous new line (width of line below cursor)
			unsigned widthofbelow = substring3.Find("\n")+1;
			// move cursor according to cursor position and width of below line
			if (substring3.Find("\n") == 0xffffffff) {
				if (line_.Length() - nextlinepos >= cursorPosition_ - lastlinepos) {
					cursorPosition_ = nextlinepos + (cursorPosition_ - lastlinepos);
				}
				else {
					cursorPosition_ = line_.Length();
				}
			}
			else if (cursorPosition_ - lastlinepos >= widthofbelow) {
				cursorPosition_ = nextlinepos + widthofbelow;
			}
			else {
				cursorPosition_ = nextlinepos + (cursorPosition_ - lastlinepos);
			}

		}
		changed = true;
		break;
    case KEY_PAGEUP:
    case KEY_PAGEDOWN:
        {
            using namespace UnhandledKey;

            VariantMap& eventData = GetEventDataMap();
            eventData[P_ELEMENT] = this;
            eventData[P_KEY] = key;
            eventData[P_BUTTONS] = buttons;
            eventData[P_QUALIFIERS] = qualifiers;
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
        }
        break;

    case KEY_RETURN:
		if (editable_ && multiLine_ && (!hasMaxLines || GetNumLines() < MaxLines))
			
		{
			line_.Insert(cursorPosition_, "\n");
			cursorPosition_ += 1;
		}
		changed = true;
		break;

	case KEY_TAB:
		if (editable_ && multiLine_ && (!hasMaxLines || GetNumLines() < MaxLines))

		{
			line_.Insert(cursorPosition_, "    ");
			cursorPosition_ += 4;
		}
		changed = true;
		break;



    case KEY_RETURN2:
		if (editable_ && multiLine_ && (!hasMaxLines || GetNumLines() < MaxLines))
		{
			line_.Insert(cursorPosition_, "\n");
			cursorPosition_ += 1;
		}
		changed = true;
		break;


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

void MultiLineEdit::OnTextInput(const String& text, int buttons, int qualifiers)
{
    if (!editable_)
        return;

    bool changed = false;

    // If only CTRL is held down, do not edit
    if ((qualifiers & (QUAL_CTRL | QUAL_ALT)) == QUAL_CTRL)
        return;

    // Send char as an event to allow changing it
    using namespace CharEntry;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_ELEMENT] = this;
    eventData[P_TEXT] = text;
    eventData[P_BUTTONS] = buttons;
    eventData[P_QUALIFIERS] = qualifiers;
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
            unsigned start = text_->GetSelectionStart();
            unsigned length = text_->GetSelectionLength();
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

void MultiLineEdit::SetText(const String& text)
{
    if (text != line_)
    {
        line_ = text;
        cursorPosition_ = line_.LengthUTF8();
        UpdateText();
        UpdateCursor();
    }
}

void MultiLineEdit::SetMultiLine(bool enable) 
{
	multiLine_ = enable;
}

void MultiLineEdit::SetCursorPosition(unsigned position)
{
    if (position > line_.LengthUTF8() || !cursorMovable_)
        position = line_.LengthUTF8();

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
    if (!Text::FilterImplicitAttributes(dest))
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

void MultiLineEdit::UpdateText()
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

    VariantMap& eventData = GetEventDataMap();
    eventData[P_ELEMENT] = this;
    eventData[P_TEXT] = line_;
    SendEvent(E_TEXTCHANGED, eventData);
}

void MultiLineEdit::UpdateCursor()
{
    int x = text_->GetCharPosition(cursorPosition_).x_;
	int y = text_->GetCharPosition(cursorPosition_).y_;


    text_->SetPosition(GetIndentWidth() + clipBorder_.left_, clipBorder_.top_);
    cursor_->SetPosition(text_->GetPosition() + IntVector2(x-text_->GetCharSize(cursorPosition_).x_/2, y));
    //cursor_->SetSize(cursor_->GetWidth(), text_->GetRowHeight());
	cursor_->SetSize(2, text_->GetRowHeight());
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

unsigned MultiLineEdit::GetCharIndex(const IntVector2& position)
{
    IntVector2 screenPosition = ElementToScreen(position);
    IntVector2 textPosition = text_->ScreenToElement(screenPosition);

    if (textPosition.x_ < 0)
        return 0;

    for (int i = text_->GetNumChars(); i >= 0; --i)
    {
        if (textPosition.x_ >= text_->GetCharPosition((unsigned)i).x_ && textPosition.y_ >= text_->GetCharPosition((unsigned)i).y_)
            return (unsigned)i;
    }

    return M_MAX_UNSIGNED;
}

void MultiLineEdit::HandleFocused(StringHash eventType, VariantMap& eventData)
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

void MultiLineEdit::HandleDefocused(StringHash eventType, VariantMap& eventData)
{
    text_->ClearSelection();

    if (GetSubsystem<UI>()->GetUseScreenKeyboard())
        GetSubsystem<Input>()->SetScreenKeyboardVisible(false);
}
void MultiLineEdit::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
	using namespace KeyDown;
	int key = eventData[P_KEY].GetInt();
	int mouseButtons_ = eventData[P_BUTTONS].GetInt();
	int qualifiers_ = eventData[P_QUALIFIERS].GetInt();
	OnKey(key, mouseButtons_, qualifiers_);
}

void MultiLineEdit::HandleLayoutUpdated(StringHash eventType, VariantMap& eventData)
{
	UpdateCursor();
}

}
