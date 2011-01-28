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

#ifndef ENGINE_CONSOLE_H
#define ENGINE_CONSOLE_H

#include "EventListener.h"
#include "Log.h"
#include "SharedPtr.h"

class BorderImage;
class Engine;
class Font;
class Text;
class LineEdit;

//! A console window with log history and AngelScript prompt
class Console : public RefCounted, public EventListener, public LogListener
{
public:
    //! Construct with an Engine pointer
    Console(Engine* engine);
    //! Destruct
    ~Console();
    
    //! Write a log message
    virtual void write(const std::string& message);
    
    //! Show/hide. Showing automatically focuses the line edit
    void setVisible(bool enable);
    //! Set number of rows
    void setNumRows(unsigned rows);
    //! Set font to use
    void setFont(Font* font, int size);
    //! Set key for toggling
    void setToggleKey(int key);
    
    //! Return whether is visible
    bool isVisible() const;
    //! Return number of rows
    unsigned getNumRows() const { return mRows.size(); }
    //! Return key for toggling
    int getToggleKey() const { return mToggleKey; }
    //! Return background element
    BorderImage* getBackgroundElement() const { return mBackground; }
    //! Return line edit element
    LineEdit* getLineEditElement() const { return mLineEdit; }
    
private:
    //! Update layout
    void updateElements();
    //! Handle update
    void handleUpdate(StringHash eventType, VariantMap& eventData);
    //! Handle key press
    void handleKeyDown(StringHash eventType, VariantMap& eventData);
    //! Handle enter pressed on the line edit
    void handleTextFinished(StringHash eventType, VariantMap& eventData);
    
    //! Engine
    WeakPtr<Engine> mEngine;
    //! Background
    SharedPtr<BorderImage> mBackground;
    //! Font
    SharedPtr<Font> mFont;
    //! Text rows
    std::vector<SharedPtr<Text> > mRows;
    //! Line edit
    SharedPtr<LineEdit> mLineEdit;
    //! Font size
    int mFontSize;
    //! Key for toggling
    int mToggleKey;
    //! Focus flag
    bool mFocus;
};

#endif // ENGINE_CONSOLE_H
