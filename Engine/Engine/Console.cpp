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
#include "BorderImage.h"
#include "Console.h"
#include "Engine.h"
#include "EngineEvents.h"
#include "Font.h"
#include "InputEvents.h"
#include "LineEdit.h"
#include "ScriptEngine.h"
#include "StringUtils.h"
#include "Text.h"
#include "UI.h"
#include "UIEvents.h"

Console::Console(Engine* engine) :
    mEngine(engine),
    mFontSize(1)
{
    LOGINFO("Console created");
    
    if (!mEngine)
        return;
    
    Log* log = getLog();
    if (log)
        log->addListener(this);
    
    UIElement* uiRoot = mEngine->getUIRoot();
    if (!uiRoot)
        return;
    
    mBackground = new BorderImage();
    mBackground->setWidth(uiRoot->getWidth());
    mBackground->setColor(C_TOPLEFT, Color(0.25f, 0.25f, 0.5f, 0.5f));
    mBackground->setColor(C_TOPRIGHT, Color(0.25f, 0.25f, 0.5f, 0.5f));
    mBackground->setColor(C_BOTTOMLEFT, Color(0.5f, 0.5f, 1.0f, 0.5f));
    mBackground->setColor(C_BOTTOMRIGHT, Color(0.5f, 0.5f, 1.0f, 0.5f));
    mBackground->setEnabled(true);
    mBackground->setVisible(false);
    mBackground->setPriority(200); // Show on top of the debug HUD
    
    mLineEdit = new LineEdit();
    mLineEdit->setWidth(uiRoot->getWidth() - 8);
    mLineEdit->setColor(Color(0.0f, 0.0f, 0.25f, 0.5f));
    mLineEdit->setDefocusable(false);
    mBackground->addChild(mLineEdit);
    
    uiRoot->addChild(mBackground);
    
    updateElements();
    
    subscribeToEvent(EVENT_TEXTFINISHED, EVENT_HANDLER(Console, handleTextFinished));
}

Console::~Console()
{
    if (mEngine)
    {
        UIElement* uiRoot = mEngine->getUIRoot();
        if (uiRoot)
            uiRoot->removeChild(mBackground);
    }
    
    Log* log = getLog();
    if (log)
        log->removeListener(this);
    
    LOGINFO("Console shut down");
}

void Console::write(const std::string& message)
{
    if (!mRows.size())
        return;
    
    // Be prepared for possible multi-line messages
    std::vector<std::string> rows = split(message, '\n');
    
    for (unsigned i = 0; i < rows.size(); ++i)
    {
        for (int j = 0; j < (int)mRows.size() - 1; ++j)
            mRows[j]->setText(mRows[j + 1]->getText());
        
        mRows[mRows.size() - 1]->setText(rows[i]);
    }
}

void Console::setVisible(bool enable)
{
    if (!mBackground)
        return;
    
    mBackground->setVisible(enable);
    if (enable)
        mEngine->getUI()->setFocusElement(mLineEdit);
    else
    {
        mLineEdit->setFocus(false);
        mLineEdit->setText(std::string());
    }
}

void Console::toggle()
{
    setVisible(!isVisible());
}

void Console::setNumRows(unsigned rows)
{
    if (!mBackground)
        return;
    
    for (unsigned i = 0; i < mRows.size(); ++i)
        mBackground->removeChild(mRows[i]);
    mRows.clear();
    mBackground->removeChild(mLineEdit);
    
    mRows.resize(rows);
    for (unsigned i = 0; i < mRows.size(); ++i)
    {
        mRows[i] = new Text();
        mBackground->addChild(mRows[i]);
    }
    mBackground->addChild(mLineEdit);
    
    updateElements();
}

void Console::setFont(Font* font, int size)
{
    if (!mBackground)
        return;
    
    mFont = font;
    mFontSize = max(size, 1);
    
    updateElements();
}

bool Console::isVisible() const
{
    if (!mBackground)
        return false;
    return mBackground->isVisible();
}

void Console::updateElements()
{
    if (mFont)
    {
        try
        {
            for (unsigned i = 0; i < mRows.size(); ++i)
                mRows[i]->setFont(mFont, mFontSize);
            mLineEdit->getTextElement()->setFont(mFont, mFontSize);
        }
        catch (...)
        {
        }
    }
    
    mLineEdit->setHeight(mLineEdit->getTextElement()->getRowHeight());
    mBackground->layoutVertical(0, IntRect(4, 4, 4, 4), true, true);
    
    int maxWidth = mEngine->getUIRoot()->getWidth();
    if (mBackground->getWidth() > maxWidth)
        mBackground->setWidth(maxWidth);
}

void Console::handleTextFinished(StringHash eventType, VariantMap& eventData)
{
    using namespace TextFinished;
    
    if (eventData[P_ELEMENT].getPtr() == (void*)mLineEdit)
    {
        std::string line = mLineEdit->getText();
        ScriptEngine* scriptEngine = mEngine->getScriptEngine();
        if (scriptEngine)
            scriptEngine->execute(line);
        mLineEdit->setText(std::string());
    }
}
