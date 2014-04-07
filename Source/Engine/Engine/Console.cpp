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
#include "Input.h"
#include "InputEvents.h"
#include "IOEvents.h"
#include "LineEdit.h"
#include "ListView.h"
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

    // By default prevent the automatic showing of the screen keyboard
    focusOnShow_ = !ui->GetUseScreenKeyboard();

    background_ = new BorderImage(context_);
    background_->SetBringToBack(false);
    background_->SetClipChildren(true);
    background_->SetEnabled(true);
    background_->SetVisible(false); // Hide by default
    background_->SetPriority(200); // Show on top of the debug HUD
    background_->SetLayout(LM_VERTICAL);

    rowContainer_ = new ListView(context_);
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
    rowContainer_->SetStyle("ListView");

    for (unsigned i = 0; i < rowContainer_->GetNumItems(); ++i)
        rowContainer_->GetItem(i)->SetStyle("ConsoleText");
    
    lineEdit_->SetStyle("ConsoleLineEdit");
    
    UpdateElements();
}

void Console::SetVisible(bool enable)
{
    Input* input = GetSubsystem<Input>();
    background_->SetVisible(enable);
    if (enable)
    {
        // Check if we have handler for E_CONSOLECOMMAND every time here in case the handler is being added later dynamically
        bool hasConsoleCommandEventHandler = context_->GetEventReceivers(this, E_CONSOLECOMMAND) != 0 ||
            context_->GetEventReceivers(E_CONSOLECOMMAND) != 0;
        lineEdit_->SetVisible(hasConsoleCommandEventHandler);
        if (hasConsoleCommandEventHandler && focusOnShow_)
            GetSubsystem<UI>()->SetFocusElement(lineEdit_);

        // Ensure the background has no empty space when shown without the lineedit
        background_->SetHeight(background_->GetMinHeight());

        // Show OS mouse
        savedMouseVisibility_ = input->IsMouseVisible();
        input->SetMouseVisible(true);
    }
    else
    {
        lineEdit_->SetFocus(false);

        // Restore OS mouse visibility
        input->SetMouseVisible(savedMouseVisibility_);
    }
}

void Console::Toggle()
{
    SetVisible(!IsVisible());
}

void Console::SetNumBufferedRows(unsigned rows)
{
    if (rows < displayedRows_)
        return;

    rowContainer_->DisableLayoutUpdate();

    int delta = rowContainer_->GetNumItems() - rows;
    if (delta > 0)
    {
        // We have more, remove oldest rows first
        for (int i = 0; i < delta; ++i)
            rowContainer_->RemoveItem((unsigned)0);
    }
    else
    {
        // We have less, add more rows at the bottom
        for (int i = 0; i > delta; --i)
        {
            Text* text = new Text(context_);
            // If style is already set, apply here to ensure proper height of the console when
            // amount of rows is changed
            if (background_->GetDefaultStyle())
                text->SetStyle("ConsoleText");
            rowContainer_->AddItem(text);
        }
    }

    rowContainer_->EnableLayoutUpdate();
    rowContainer_->UpdateLayout();

    UpdateElements();
}

void Console::SetNumRows(unsigned rows)
{
    if (!rows)
        return;
    displayedRows_ = rows;
    if (!GetNumBufferedRows())
        SetNumBufferedRows(2 * rows);
    const IntRect& border = rowContainer_->GetScrollPanel()->GetBorder();
    unsigned height = rows * rowContainer_->GetItem((unsigned)0)->GetHeight() + border.top_; border.bottom_;
    rowContainer_->SetMinHeight(height);
    rowContainer_->SetHeight(height);
}

void Console::SetNumHistoryRows(unsigned rows)
{
    historyRows_ = rows;
    if (history_.Size() > rows)
        history_.Resize(rows);
    if (historyPosition_ > rows)
        historyPosition_ = rows;
}

void Console::SetFocusOnShow(bool enable)
{
    focusOnShow_ = enable;
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

unsigned Console::GetNumBufferedRows() const
{
    rowContainer_->GetNumItems();
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
    if (!rowContainer_->GetNumItems())
        return;
    
    printing_ = true;
    rowContainer_->DisableLayoutUpdate();
    
    Text* text;
    for (unsigned i = 0; i < pendingRows_.Size(); ++i)
    {
        rowContainer_->RemoveItem((unsigned)0);
        text = new Text(context_);
        text->SetText(pendingRows_[i].second_);
        // Make error message highlight
        text->SetStyle(pendingRows_[i].first_ == LOG_ERROR ? "ConsoleHighlightedText" : "ConsoleText");
        rowContainer_->AddItem(text);
    }
    
    pendingRows_.Clear();
    
    rowContainer_->EnsureItemVisibility(text);
    rowContainer_->EnableLayoutUpdate();
    rowContainer_->UpdateLayout();
    printing_ = false;
}

}
