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
#include "LineEdit.h"
#include "Text.h"
#include "UIEvents.h"

#include "DebugNew.h"

LineEdit::LineEdit(const std::string& name, const std::string& text) :
    BorderImage(name),
    mEchoCharacter(0),
    mCursorBlinkRate(1.0f),
    mCursorBlinkTimer(0.0f),
    mMaxLength(0),
    mDefocusable(true),
    mDefocus(false)
{
    mClipChildren = true;
    mEnabled = true;
    mFocusable = true;
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
    
    if (element.hasChildElement("cursorblinkrate"))
        setCursorBlinkRate(element.getChildElement("cursorblinkrate").getFloat("value"));
    if (element.hasChildElement("echocharacter"))
    {
        std::string text = element.getChildElement("echocharacter").getString("value");
        if (text.length())
            setEchoCharacter(text[0]);
    }
    if (element.hasChildElement("maxlength"))
        setMaxLength(element.getChildElement("maxlength").getInt("value"));
    
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
}

void LineEdit::update(float timeStep)
{
    if (mCursorBlinkRate > 0.0f)
        mCursorBlinkTimer = fmodf(mCursorBlinkTimer + mCursorBlinkRate * timeStep, 1.0f);
    else
        mCursorBlinkTimer = 0.0f;
    
    bool cursorVisible = false;
    
    if (mFocus)
    {
        int textLength = 0;
        const std::vector<int>& rowWidths = mText->getRowWidths();
        if (rowWidths.size())
            textLength = rowWidths[0];
        
        // This assumes text alignment is top-left
        mCursor->setPosition(mText->getPosition() + IntVector2(textLength, 0));
        mCursor->setSize(mCursor->getWidth(), mText->getRowHeight());
        cursorVisible = mCursorBlinkTimer < 0.5f;
        
        // Scroll if text is longer than what can be visible at once
        int scrollThreshold = max(getWidth() - mClipBorder.mLeft - mClipBorder.mRight - mCursor->getWidth(), 0);
        if (textLength > scrollThreshold)
            setChildOffset(IntVector2(-(textLength - scrollThreshold), 0));
        else
            setChildOffset(IntVector2::sZero);
    }
    else
        setChildOffset(IntVector2::sZero);
    
    mCursor->setVisible(cursorVisible);
    
    if (mDefocus)
    {
        setFocus(false);
        mDefocus = false;
    }
}

void LineEdit::onChar(unsigned char c)
{
    unsigned currentLength = mLine.length();
    bool changed = false;
    
    if (c == '\b')
    {
        if (mLine.length())
        {
            mLine = mLine.substr(0, currentLength - 1);
            changed = true;
        }
    }
    else if (c == '\r')
    {
        using namespace TextFinished;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        sendEvent(EVENT_TEXTFINISHED, eventData);
    }
    else if (c == 27)
    {
        if (mDefocusable)
            mDefocus = true;
    }
    else if ((c >= 0x20) && ((!mMaxLength) || (currentLength < mMaxLength)))
    {
        mLine += (char)c;
        changed = true;
    }
    
    if (changed)
    {
        // Restart cursor blinking from the visible state
        mCursorBlinkTimer = 0.0f;
        updateText();
        
        using namespace TextChanged;
        
        VariantMap eventData;
        eventData[P_ELEMENT] = (void*)this;
        eventData[P_TEXT] = mLine;
        sendEvent(EVENT_TEXTCHANGED, eventData);
    }
}

void LineEdit::setText(const std::string& text)
{
    mLine = text;
    mText->setText(text);
    updateText();
}

void LineEdit::setEchoCharacter(char c)
{
    mEchoCharacter = c;
    updateText();
}

void LineEdit::setCursorBlinkRate(float rate)
{
    mCursorBlinkRate = max(rate, 0.0f);
}

void LineEdit::setMaxLength(unsigned length)
{
    mMaxLength = length;
}

void LineEdit::setDefocusable(bool enable)
{
    mDefocusable = enable;
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
}
