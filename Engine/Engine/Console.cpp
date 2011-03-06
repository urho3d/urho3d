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
#include "Console.h"
#include "Engine.h"
#include "Font.h"
#include "InputEvents.h"
#include "LineEdit.h"
#include "Log.h"
#include "Renderer.h"
#include "RendererEvents.h"
#include "ResourceCache.h"
#include "ScriptEngine.h"
#include "StringUtils.h"
#include "Text.h"
#include "UI.h"
#include "UIEvents.h"

#include "DebugNew.h"

static const int DEFAULT_CONSOLE_ROWS = 16;
static const int DEFAULT_HISTORY_SIZE = 16;

Console::Console(Engine* engine) :
    mEngine(engine),
    mHistoryRows(DEFAULT_HISTORY_SIZE),
    mHistoryPosition(0)
{
    LOGINFO("Console created");
    
    if (!mEngine)
        EXCEPTION("Null Engine for Console");
    
    UIElement* uiRoot = mEngine->getUIRoot();
    if (uiRoot)
    {
        mBackground = new BorderImage();
        mBackground->setBringToBack(false);
        mBackground->setClipChildren(true);
        mBackground->setEnabled(true);
        mBackground->setVisible(false); // Hide by default
        mBackground->setPriority(200); // Show on top of the debug HUD
        mBackground->setLayout(LM_VERTICAL);
        
        mRowContainer = new UIElement();
        mRowContainer->setClipChildren(true);
        mRowContainer->setLayout(LM_VERTICAL);
        mBackground->addChild(mRowContainer);
        
        mLineEdit = new LineEdit();
        mLineEdit->setFocusMode(FM_FOCUSABLE); // Do not allow defocus with ESC
        mBackground->addChild(mLineEdit);
        
        uiRoot->addChild(mBackground);
        
        setNumRows(DEFAULT_CONSOLE_ROWS);
        updateElements();
        
        subscribeToEvent(mLineEdit, EVENT_TEXTFINISHED, EVENT_HANDLER(Console, handleTextFinished));
        subscribeToEvent(mLineEdit, EVENT_UNHANDLEDKEY, EVENT_HANDLER(Console, handleLineEditKey));
        subscribeToEvent(EVENT_SCREENMODE, EVENT_HANDLER(Console, handleScreenMode));
        subscribeToEvent(EVENT_LOGMESSAGE, EVENT_HANDLER(Console, handleLogMessage));
    }
}

Console::~Console()
{
    UIElement* uiRoot = mEngine->getUIRoot();
    if (uiRoot)
        uiRoot->removeChild(mBackground);
    
    LOGINFO("Console shut down");
}

void Console::setStyle(XMLFile* style)
{
    if ((!style) || (!mEngine) || (!mBackground) || (!mLineEdit))
        return;
    
    mStyle = style;
    ResourceCache* cache = mEngine->getResourceCache();
    XMLElement backgroundElem = UIElement::getStyleElement(style, "ConsoleBackground");
    if (backgroundElem)
        mBackground->setStyle(backgroundElem, cache);
    XMLElement textElem = UIElement::getStyleElement(style, "ConsoleText");
    if (textElem)
    {
        for (unsigned i = 0; i < mRows.size(); ++i)
            mRows[i]->setStyle(textElem, cache);
    }
    XMLElement lineEditElem = UIElement::getStyleElement(style, "ConsoleLineEdit");
    if (lineEditElem)
        mLineEdit->setStyle(lineEditElem, cache);
    
    updateElements();
}

void Console::setVisible(bool enable)
{
    if (!mBackground)
        return;
    
    mBackground->setVisible(enable);
    if (enable)
        mEngine->getUI()->setFocusElement(mLineEdit);
    else
        mLineEdit->setFocus(false);
}

void Console::toggle()
{
    setVisible(!isVisible());
}

void Console::setNumRows(unsigned rows)
{
    if ((!mBackground) || (!rows))
        return;
    
    mRowContainer->removeAllChildren();
    
    mRows.resize(rows);
    for (unsigned i = 0; i < mRows.size(); ++i)
    {
        if (!mRows[i])
        {
            mRows[i] = new Text();
            XMLElement textElem = UIElement::getStyleElement(mStyle, "ConsoleText");
            if (textElem)
                mRows[i]->setStyle(textElem, mEngine->getResourceCache());
        }
        mRowContainer->addChild(mRows[i]);
    }
    
    updateElements();
}

void Console::setNumHistoryRows(unsigned rows)
{
    mHistoryRows = rows;
    if (mHistory.size() > rows)
        mHistory.resize(rows);
    if (mHistoryPosition > rows)
        mHistoryPosition = rows;
}

void Console::updateElements()
{
    int width = mEngine->getRenderer()->getWidth();
    const IntRect& border = mBackground->getLayoutBorder();
    mBackground->setFixedWidth(width);
    mRowContainer->setFixedWidth(width - border.mLeft - border.mRight);
    mLineEdit->setFixedHeight(mLineEdit->getTextElement()->getRowHeight());
}

bool Console::isVisible() const
{
    if (!mBackground)
        return false;
    return mBackground->isVisible();
}

const std::string& Console::getHistoryRow(unsigned index) const
{
    static const std::string noRow;
    return index < mHistory.size() ? mHistory[index] : noRow;
}

void Console::handleTextFinished(StringHash eventType, VariantMap& eventData)
{
    using namespace TextFinished;
    
    std::string line = mLineEdit->getText();
    if (!line.empty())
    {
        ScriptEngine* scriptEngine = mEngine->getScriptEngine();
        if (scriptEngine)
            scriptEngine->execute(line);
        
        // Store to history, then clear the lineedit
        mHistory.push_back(line);
        if (mHistory.size() > mHistoryRows)
            mHistory.erase(mHistory.begin());
        mHistoryPosition = mHistory.size();
        
        mCurrentRow = std::string();
        mLineEdit->setText(mCurrentRow);
    }
}

void Console::handleLineEditKey(StringHash eventType, VariantMap& eventData)
{
    if (!mHistoryRows)
        return;
    
    using namespace UnhandledKey;
    
    bool changed = false;
    
    switch(eventData[P_KEY].getInt())
    {
    case KEY_UP:
        if (mHistoryPosition > 0)
        {
            if (mHistoryPosition == mHistory.size())
                mCurrentRow = mLineEdit->getText();
            --mHistoryPosition;
            changed = true;
        }
        break;
    
    case KEY_DOWN:
        if (mHistoryPosition < mHistory.size())
        {
            ++mHistoryPosition;
            changed = true;
        }
        break;
    }
    
    if (changed)
    {
        if (mHistoryPosition < mHistory.size())
            mLineEdit->setText(mHistory[mHistoryPosition]);
        else
            mLineEdit->setText(mCurrentRow);
    }
}

void Console::handleScreenMode(StringHash eventType, VariantMap& eventData)
{
    updateElements();
}

void Console::handleLogMessage(StringHash eventType, VariantMap& eventData)
{
    // If the rows are not fully initialized yet, do not write the message
    if ((!mRows.size()) || (!mRows[mRows.size() - 1]))
        return;
    
    using namespace LogMessage;
    
    const std::string& message = eventData[P_MESSAGE].getString();
    
    // Be prepared for possible multi-line messages
    std::vector<std::string> rows = split(message, '\n');
    
    for (unsigned i = 0; i < rows.size(); ++i)
    {
        // Remove the first row, change its text and re-add to the bottom
        Text* text = static_cast<Text*>(mRowContainer->getChild(0));
        mRowContainer->removeChild(text);
        text->setText(rows[i]);
        mRowContainer->addChild(text);
    }
}
