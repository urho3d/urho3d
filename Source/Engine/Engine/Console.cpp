//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "Context.h"
#include "CoreEvents.h"
#include "EngineEvents.h"
#include "Font.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "InputEvents.h"
#include "IOEvents.h"
#include "LineEdit.h"
#include "Log.h"
#include "ResourceCache.h"
#include "Text.h"
#include "UI.h"
#include "UIEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

static const int DEFAULT_CONSOLE_ROWS = 16;
static const int DEFAULT_HISTORY_SIZE = 16;

Console::Console(Context* context) :
    Object(context),
    autoVisibleOnError_(false),
    historyRows_(DEFAULT_HISTORY_SIZE),
    historyPosition_(0),
    printing_(false)
{
    UI* ui = GetSubsystem<UI>();
    UIElement* uiRoot = ui->GetRoot();

    background_ = new BorderImage(context_);
    background_->SetBringToBack(false);
    background_->SetClipChildren(true);
    background_->SetEnabled(true);
    background_->SetVisible(false); // Hide by default
    background_->SetPriority(200); // Show on top of the debug HUD
    background_->SetLayout(LM_VERTICAL);

    rowContainer_ = new UIElement(context_);
    rowContainer_->SetClipChildren(true);
    rowContainer_->SetLayout(LM_VERTICAL);
    background_->AddChild(rowContainer_);

    lineEdit_ = new LineEdit(context_);
    lineEdit_->SetFocusMode(FM_FOCUSABLE); // Do not allow defocus with ESC
    background_->AddChild(lineEdit_);

    uiRoot->AddChild(background_);

    SetNumRows(DEFAULT_CONSOLE_ROWS);

    SubscribeToEvent(lineEdit_, E_TEXTFINISHED, HANDLER(Console, HandleTextFinished));
    SubscribeToEvent(lineEdit_, E_UNHANDLEDKEY, HANDLER(Console, HandleLineEditKey));
    SubscribeToEvent(E_SCREENMODE, HANDLER(Console, HandleScreenMode));
    SubscribeToEvent(E_LOGMESSAGE, HANDLER(Console, HandleLogMessage));
    SubscribeToEvent(E_POSTUPDATE, HANDLER(Console, HandlePostUpdate));
}

Console::~Console()
{
    background_->Remove();
}

void Console::SetDefaultStyle(XMLFile* style)
{
    if (!style)
        return;

    background_->SetDefaultStyle(style);
    background_->SetStyle("ConsoleBackground");

    const Vector<SharedPtr<UIElement> >& children = rowContainer_->GetChildren();
    for (unsigned i = 0; i < children.Size(); ++i)
        children[i]->SetStyle("ConsoleText");
    
    lineEdit_->SetStyle("ConsoleLineEdit");
    
    UpdateElements();
}

void Console::SetVisible(bool enable)
{
    background_->SetVisible(enable);

    if (enable)
    {
        // Check if we have handler for E_CONSOLECOMMAND every time here in case the handler is being added later dynamically
        bool hasConsoleCommandEventHandler = context_->GetEventReceivers(this, E_CONSOLECOMMAND) != 0 ||
            context_->GetEventReceivers(E_CONSOLECOMMAND) != 0;
        lineEdit_->SetVisible(hasConsoleCommandEventHandler);
        if (hasConsoleCommandEventHandler)
            GetSubsystem<UI>()->SetFocusElement(lineEdit_);

        // Ensure the background has no empty space when shown without the lineedit
        background_->SetHeight(background_->GetMinHeight());
    }
    else
        lineEdit_->SetFocus(false);
}

void Console::Toggle()
{
    SetVisible(!IsVisible());
}

void Console::SetNumRows(unsigned rows)
{
    if (!rows)
        return;

    rowContainer_->DisableLayoutUpdate();

    int delta = rowContainer_->GetNumChildren() - rows;
    if (delta > 0)
    {
        // We have more, remove oldest rows first
        for (int i = 0; i < delta; ++i)
            rowContainer_->RemoveChildAtIndex(0);
    }
    else
    {
        // We have less, add more rows at the bottom
        for (int i = 0; i > delta; --i)
        {
            Text* text = rowContainer_->CreateChild<Text>();
            // If style is already set, apply here to ensure proper height of the console when
            // amount of rows is changed
            if (background_->GetDefaultStyle())
                text->SetStyle("ConsoleText");
        }
    }

    rowContainer_->EnableLayoutUpdate();
    rowContainer_->UpdateLayout();

    UpdateElements();
}

void Console::SetNumHistoryRows(unsigned rows)
{
    historyRows_ = rows;
    if (history_.Size() > rows)
        history_.Resize(rows);
    if (historyPosition_ > rows)
        historyPosition_ = rows;
}

void Console::UpdateElements()
{
    int width = GetSubsystem<Graphics>()->GetWidth();
    const IntRect& border = background_->GetLayoutBorder();
    background_->SetFixedWidth(width);
    background_->SetHeight(background_->GetMinHeight());
    rowContainer_->SetFixedWidth(width - border.left_ - border.right_);
}

XMLFile* Console::GetDefaultStyle() const
{
    return background_->GetDefaultStyle(false);
}

bool Console::IsVisible() const
{
    return background_ && background_->IsVisible();
}

unsigned Console::GetNumRows() const
{
    return rowContainer_->GetNumChildren();
}

const String& Console::GetHistoryRow(unsigned index) const
{
    return index < history_.Size() ? history_[index] : String::EMPTY;
}

void Console::HandleTextFinished(StringHash eventType, VariantMap& eventData)
{
    using namespace TextFinished;

    String line = lineEdit_->GetText();
    if (!line.Empty())
    {
        // Send the command as an event for script subsystem
        using namespace ConsoleCommand;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_COMMAND] = line;
        SendEvent(E_CONSOLECOMMAND, eventData);

        // Store to history, then clear the lineedit
        history_.Push(line);
        if (history_.Size() > historyRows_)
            history_.Erase(history_.Begin());
        historyPosition_ = history_.Size();

        currentRow_.Clear();
        lineEdit_->SetText(currentRow_);
    }
}

void Console::HandleLineEditKey(StringHash eventType, VariantMap& eventData)
{
    if (!historyRows_)
        return;

    using namespace UnhandledKey;

    bool changed = false;

    switch (eventData[P_KEY].GetInt())
    {
    case KEY_UP:
        if (historyPosition_ > 0)
        {
            if (historyPosition_ == history_.Size())
                currentRow_ = lineEdit_->GetText();
            --historyPosition_;
            changed = true;
        }
        break;

    case KEY_DOWN:
        if (historyPosition_ < history_.Size())
        {
            ++historyPosition_;
            changed = true;
        }
        break;
    }

    if (changed)
    {
        if (historyPosition_ < history_.Size())
            lineEdit_->SetText(history_[historyPosition_]);
        else
            lineEdit_->SetText(currentRow_);
    }
}

void Console::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    UpdateElements();
}

void Console::HandleLogMessage(StringHash eventType, VariantMap& eventData)
{
    // If printing a log message causes more messages to be logged (error accessing font), disregard them
    if (printing_)
        return;
    
    using namespace LogMessage;

    int level = eventData[P_LEVEL].GetInt();
    // The message may be multi-line, so split to rows in that case
    Vector<String> rows = eventData[P_MESSAGE].GetString().Split('\n');
    
    for (unsigned i = 0; i < rows.Size(); ++i)
        pendingRows_.Push(MakePair(level, rows[i]));

    if (autoVisibleOnError_ && level == LOG_ERROR && !IsVisible())
        SetVisible(true);
}

void Console::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if (!rowContainer_->GetNumChildren())
        return;
    
    printing_ = true;
    rowContainer_->DisableLayoutUpdate();
    
    for (unsigned i = 0; i < pendingRows_.Size(); ++i)
    {
        rowContainer_->RemoveChildAtIndex(0);
        Text* text = rowContainer_->CreateChild<Text>();
        text->SetText(pendingRows_[i].second_);
        // Make error message highlight
        text->SetStyle(pendingRows_[i].first_ == LOG_ERROR ? "ConsoleHighlightedText" : "ConsoleText");
    }
    
    pendingRows_.Clear();
    
    rowContainer_->EnableLayoutUpdate();
    rowContainer_->UpdateLayout();
    printing_ = false;
}

}
