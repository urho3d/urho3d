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

#ifndef UI_LINEEDIT_H
#define UI_LINEEDIT_H

#include "BorderImage.h"

class Text;

class LineEdit : public BorderImage
{
    DEFINE_TYPE(LineEdit);
    
public:
    //! Construct with name and initial text
    LineEdit(const std::string& name = std::string(), const std::string& text = std::string());
    //! Destruct
    virtual ~LineEdit();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! Perform UI element update
    virtual void update(float timeStep);
    
    //! React to mouse click
    virtual void onClick(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    //! React to a key press
    virtual void onKey(int key);
    //! React to a key press translated to a character
    virtual void onChar(unsigned char c);
    
    //! Set text
    void setText(const std::string& text);
    //! Set cursor position
    void setCursorPosition(unsigned position);
    //! Set cursor blink rate. 0 disables blinking
    void setCursorBlinkRate(float rate);
    //! Set maximum text length. 0 for unlimited
    void setMaxLength(unsigned length);
    //! Set echo character for password entry and such. 0 (default) shows the actual text
    void setEchoCharacter(char c);
    //! Set whether can defocus with ESC, default true
    void setDefocusable(bool enable);
    
    //! Return text
    const std::string& getText() const { return mLine; }
    //! Return cursor position
    unsigned getCursorPosition() const { return mCursorPosition; }
    //! Return cursor blink rate
    float getCursorBlinkRate() const { return mCursorBlinkRate; }
    //! Return maximum text length
    unsigned getMaxLength() const { return mMaxLength; }
    //! Return echo character
    char getEchoCharacter() const { return mEchoCharacter; }
    //! Return whether can defocus with ESC
    bool isDefocusable() const { return mDefocusable; }
    //! Return text element
    Text* getTextElement() const { return mText; }
    //! Return cursor element
    BorderImage* getCursorElement() const { return mCursor; }
    
protected:
    //! Update displayed text
    void updateText();
    
    //! Text line
    std::string mLine;
    //! Cursor position
    unsigned mCursorPosition;
    //! Cursor blink rate
    float mCursorBlinkRate;
    //! Cursor blink timer
    float mCursorBlinkTimer;
    //! Maximum text length
    unsigned mMaxLength;
    //! Echo character
    char mEchoCharacter;
    //! ESC defocus flag
    bool mDefocusable;
    //! Text element
    SharedPtr<Text> mText;
    //! Cursor element
    SharedPtr<BorderImage> mCursor;
    //! Defocus flag (defocus on next update)
    bool mDefocus;
};

#endif // UI_LINEEDIT_H
