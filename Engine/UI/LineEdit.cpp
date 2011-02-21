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
#include "Input.h"
#include "LineEdit.h"
#include "Text.h"
#include "UIEvents.h"

#include "DebugNew.h"

LineEdit::LineEdit(const std::string& name, const std::string& text) :
    BorderImage(name),
    mLastFont(0),
    mLastFontSize(0),
    mCursorPosition(0),
    mDragStartPosition(M_MAX_UNSIGNED),
    mCursorBlinkRate(1.0f),
    mCursorBlinkTimer(0.0f),
    mMaxLength(0),
    mEchoCharacter(0),
    mCursorMovable(true),
    mTextSelectable(true),
    mTextCopyable(true)
{
    mClipChildren = true;
    mEnabled = true;
    mFocusMode = FM_FOCUSABLE_DEFOCUSABLE;
    mText = new Text();
    mCursor = new BorderImage();
    addChild(mText);
    addChild(mCursor);
    
    // Show cursor on top of text
    mCursor->setPriority(1);
    setText(text);
}

LineEdit::~LineEdit()
{
}

void LineEdit::setStyle(const XMLElement& element, ResourceCache* cache)
{
    BorderImage::setStyle(element, cache);
    
    if (element.hasChildElement("maxlength"))
        setMaxLength(element.getChildElement("maxlength").getInt("value"));
    if (element.hasChildElement("cursormovable"))
        setCursorMovable(element.getChildElement("cursormovable").getBool("enable"));
    if (element.hasChildElement("textselectable"))
        setTextSelectable(element.getChildElement("textselectable").getBool("enable"));
    if (element.hasChildElement("textcopyable"))
        setTextCopyable(element.getChildElement("textcopyable").getBool("enable"));
    
    XMLElement textElem = element.getChildElement("text");
    if (textElem)
    {
        if (textElem.hasAttribute("value"))
            setText(textElem.getString("value"));
        mText->setStyle(textElem, cache);
    }
    
    XMLElement cursorElem = element.getChildElement("cursor");
    if (cursorElem)
        mCursor->setStyle(cursorElem, cache);
    
    if (element.hasChildElement("cursorposition"))
        setCursorPosition(element.getChildElement("cursorposition").getInt("value"));
    if (element.hasChildElement("cursorblinkrate"))
        setCursorBlinkRate(element.getChildElement("cursorblinkrate").getFloat("value"));
    if (element.hasChildElement("echocharacter"))
    {
        std::string text = element.getChildElement("echocharacter").getString("value");
        if (text.length())
            setEchoCharacter(text[0]);
    }
}

void LineEdit::update(float timeStep)
{
    if (mCursorBlinkRate > 0.0f)
        mCursorBlinkTimer = fmodf(mCursorBlinkTimer + mCursorBlinkRate * timeStep, 1.0f);
    else
        mCursorBlinkTimer = 0.0f;
    
    // Update cursor position if font has changed
    if ((mText->getFont() != mLastFont) || (mText->getFontSize() != mLastFontSize))
    {
        mLastFont = mText->getFont();
        mLastFontSize = mText->getFontSize();
        updateCursor();
    }
   
    bool cursorVisible = false;
    if (mFocus)
        cursorVisible = mCursorBlinkTimer < 0.5f;
    mCursor->setVisible(cursorVisible);
}

void LineEdit::onClick(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers)
{
    if ((buttons & MOUSEB_LEFT) && (mCursorMovable))
    {
        unsigned pos = getCharIndex(position);
        if (pos != M_MAX_UNSIGNED)
        {
            setCursorPosition(pos);
            mText->clearSelection();
        }
    }
}

void LineEdit::onDragStart(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers)
{
    mDragStartPosition = getCharIndex(position);
}

void LineEdit::onDragMove(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers)
{
    if ((mCursorMovable) && (mTextSelectable))
    {
        unsigned start = mDragStartPosition;
        unsigned current = getCharIndex(position);
        if ((start != M_MAX_UNSIGNED) && (current != M_MAX_UNSIGNED))
        {
            if (start < current)
                mText->setSelection(start, current - start);
            else
                mText->setSelection(current, start - current);
            setCursorPosition(current);
        }
    }
}

void LineEdit::onKey(int key, int buttons, int qualifiers)
{
    bool changed = false;
    bool cursorMoved = false;
    
    switch (key)
    {
    case 'X':
    case 'C':
        if ((mTextCopyable) && (qualifiers & QUAL_CTRL))
        {
            unsigned start = mText->getSelectionStart();
            unsigned length = mText->getSelectionLength();
            
            if (mText->getSelectionLength())
                sClipBoard = mLine.substr(start, length);
            
            if (key == 'X')
            {
                if (start + length < mLine.length())
                    mLine = mLine.substr(0, start) + mLine.substr(start + length);
                else
                    mLine = mLine.substr(0, start);
                mText->clearSelection();
                mCursorPosition = start;
                changed = true;
            }
        }
        break;
        
    case 'V':
        if ((mTextCopyable) && (qualifiers & QUAL_CTRL))
        {
            if (sClipBoard.length())
            {
                if (mCursorPosition < mLine.length())
                    mLine = mLine.substr(0, mCursorPosition) + sClipBoard + mLine.substr(mCursorPosition);
                else
                    mLine += sClipBoard;
                mCursorPosition += sClipBoard.length();
                changed = true;
            }
        }
        break;
        
    case KEY_LEFT:
        if (!(qualifiers & QUAL_SHIFT))
            mText->clearSelection();
        if ((mCursorMovable) && (mCursorPosition > 0))
        {
            if ((mTextSelectable) && (qualifiers & QUAL_SHIFT) && (!mText->getSelectionLength()))
                mDragStartPosition = mCursorPosition;
            
            if (qualifiers & QUAL_CTRL)
                mCursorPosition = 0;
            else
                --mCursorPosition;
            cursorMoved = true;
            
            if ((mTextSelectable) && (qualifiers & QUAL_SHIFT))
            {
                unsigned start = mDragStartPosition;
                unsigned current = mCursorPosition;
                if (start < current)
                    mText->setSelection(start, current - start);
                else
                    mText->setSelection(current, start - current);
            }
        }
        break;
        
    case KEY_RIGHT:
        if (!(qualifiers & QUAL_SHIFT))
            mText->clearSelection();
        if ((mCursorMovable) && (mCursorPosition < mLine.length()))
        {
            if ((mTextSelectable) && (qualifiers & QUAL_SHIFT) && (!mText->getSelectionLength()))
                mDragStartPosition = mCursorPosition;
            
            if (qualifiers & QUAL_CTRL)
                mCursorPosition = mLine.length();
            else
                ++mCursorPosition;
            cursorMoved = true;
            
            if ((mTextSelectable) && (qualifiers & QUAL_SHIFT))
            {
                unsigned start = mDragStartPosition;
                unsigned current = mCursorPosition;
                if (start < current)
                    mText->setSelection(start, current - start);
                else
                    mText->setSelection(current, start - current);
            }
        }
        break;
        
    case KEY_HOME:
        if ((mCursorMovable) && (mCursorPosition > 0))
        {
            mCursorPosition = 0;
            cursorMoved = true;
        }
        break;
        
    case KEY_END:
        if ((mCursorMovable) && (mCursorPosition < mLine.length()))
        {
            mCursorPosition = mLine.length();
            cursorMoved = true;
        }
        break;
        
    case KEY_DELETE:
        if (!mText->getSelectionLength())
        {
            if (mCursorPosition < mLine.length())
            {
                mLine = mLine.substr(0, mCursorPosition) + mLine.substr(mCursorPosition + 1);
                changed = true;
            }
        }
        else
        {
            // If a selection exists, erase it
            unsigned start = mText->getSelectionStart();
            unsigned length = mText->getSelectionLength();
            if (start + length < mLine.length())
                mLine = mLine.substr(0, start) + mLine.substr(start + length);
            else
                mLine = mLine.substr(0, start);
            mText->clearSelection();
            mCursorPosition = start;
            changed = true;
        }
        break;
    }
    
    if (changed)
    {
        updateText();
        updateCursor();
    }
    else if (cursorMoved)
        updateCursor();
}

void LineEdit::onChar(unsigned char c, int buttons, int qualifiers)
{
    bool changed = false;
    
    if (qualifiers & QUAL_CTRL)
        return;
    
    if (c == '\b')
    {
        if (!mText->getSelectionLength())
        {
            if ((mLine.length()) && (mCursorPosition))
            {
                if (mCursorPosition < mLine.length())
                    mLine = mLine.substr(0, mCursorPosition - 1) + mLine.substr(mCursorPosition);
                else
                    mLine = mLine.substr(0, mCursorPosition - 1);
                --mCursorPosition;
                changed = true;
            }
        }
        else
        {
            // If a selection exists, erase it
            unsigned start = mText->getSelectionStart();
            unsigned length = mText->getSelectionLength();
            if (start + length < mLine.length())
                mLine = mLine.substr(0, start) + mLine.substr(start + length);
            else
                mLine = mLine.substr(0, start);
            mText->clearSelection();
            mCursorPosition = start;
            changed = true;
        }
    }
    else if (c == '\r')
    {
        using namespace TextFinished;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        eventData[P_TEXT] = mLine;
        sendEvent(EVENT_TEXTFINISHED, eventData);
        
        mText->clearSelection();
    }
    else if ((c >= 0x20) && ((!mMaxLength) || (mLine.length() < mMaxLength)))
    {
        static std::string charStr;
        charStr.resize(1);
        charStr[0] = c;
        
        if (!mText->getSelectionLength())
        {
            if (mCursorPosition == mLine.length())
                mLine += charStr;
            else
                mLine = mLine.substr(0, mCursorPosition) + charStr + mLine.substr(mCursorPosition);
            ++mCursorPosition;
        }
        else
        {
            // If a selection exists, erase it first
            unsigned start = mText->getSelectionStart();
            unsigned length = mText->getSelectionLength();
            if (start + length < mLine.length())
                mLine = mLine.substr(0, start) + charStr + mLine.substr(start + length);
            else
                mLine = mLine.substr(0, start) + charStr;
            mCursorPosition = start + 1;
        }
        changed = true;
    }
    
    if (changed)
    {
        mText->clearSelection();
        updateText();
        updateCursor();
    }
}

void LineEdit::onFocus()
{
    updateCursor();
}

void LineEdit::onDefocus()
{
    mText->clearSelection();
}

void LineEdit::setText(const std::string& text)
{
    if (text != mLine)
    {
        mLine = text;
        // If cursor is not movable, make sure it's at the text end
        if (!mCursorMovable)
            setCursorPosition(mLine.length());
        updateText();
    }
}

void LineEdit::setCursorPosition(unsigned position)
{
    if ((position > mLine.length()) || (!mCursorMovable))
        position = mLine.length();
    
    if (position != mCursorPosition)
    {
        mCursorPosition = position;
        updateCursor();
    }
}

void LineEdit::setCursorBlinkRate(float rate)
{
    mCursorBlinkRate = max(rate, 0.0f);
}

void LineEdit::setMaxLength(unsigned length)
{
    mMaxLength = length;
}

void LineEdit::setEchoCharacter(char c)
{
    mEchoCharacter = c;
    updateText();
}

void LineEdit::setCursorMovable(bool enable)
{
    mCursorMovable = enable;
}

void LineEdit::setTextSelectable(bool enable)
{
    mTextSelectable = enable;
}

void LineEdit::setTextCopyable(bool enable)
{
    mTextCopyable = enable;
}

void LineEdit::updateText()
{
    if (!mEchoCharacter)
        mText->setText(mLine);
    else
    {
        std::string echoText;
        echoText.resize(mLine.length());
        for (unsigned i = 0; i < mLine.length(); ++i)
            echoText[i] = mEchoCharacter;
        mText->setText(echoText);
    }
    if (mCursorPosition > mLine.length())
    {
        mCursorPosition = mLine.length();
        updateCursor();
    }
    
    using namespace TextChanged;
    
    VariantMap eventData;
    eventData[P_ELEMENT] = (void*)this;
    eventData[P_TEXT] = mLine;
    sendEvent(EVENT_TEXTCHANGED, eventData);
}

void LineEdit::updateCursor()
{
    int x = 0;
    const std::vector<IntVector2>& charPositions = mText->getCharPositions();
    if (charPositions.size())
        x = mCursorPosition < charPositions.size() ? charPositions[mCursorPosition].mX : charPositions.back().mX;
    
    mCursor->setPosition(mText->getPosition() + IntVector2(x, 0));
    mCursor->setSize(mCursor->getWidth(), mText->getRowHeight());
    
    // Scroll if necessary
    int sx = -getChildOffset().mX;
    int left = mClipBorder.mLeft;
    int right = getWidth() - mClipBorder.mLeft - mClipBorder.mRight - mCursor->getWidth();
    if (x - sx > right)
        sx = x - right;
    if (x - sx < left)
        sx = x - left;
    setChildOffset(IntVector2(-sx, 0));
    
    // Restart blinking
    mCursorBlinkTimer = 0.0f;
}

unsigned LineEdit::getCharIndex(const IntVector2& position)
{
    IntVector2 screenPosition = elementToScreen(position);
    IntVector2 textPosition = mText->screenToElement(screenPosition);
    const std::vector<IntVector2>& charPositions = mText->getCharPositions();
    
    if (textPosition.mX < 0)
        return 0;
    
    for (unsigned i = charPositions.size() - 1; i < charPositions.size(); --i)
    {
        if (textPosition.mX >= charPositions[i].mX)
            return i;
    }
    
    return M_MAX_UNSIGNED;
}
