//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Font.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "InputEvents.h"
#include "IOEvents.h"
#include "LineEdit.h"
#include "Log.h"
#include "ResourceCache.h"
#include "Script.h"
#include "Text.h"
#include "UI.h"
#include "UIEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

static const int DEFAULT_CONSOLE_ROWS = 16;
static const int DEFAULT_HISTORY_SIZE = 16;

OBJECTTYPESTATIC(Console);

Console::Console(Context* context) :
    Object(context),
    historyRows_(DEFAULT_HISTORY_SIZE),
    historyPosition_(0),
    inLogMessage_(false)
{
    UI* ui = GetSubsystem<UI>();
    UIElement* uiRoot = ui->GetRoot();
    
    background_ = new BorderImage(context_);
    background_->SetBringToBack(false);
    background_->SetClipChildren(true);
    background_->SetActive(true);
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
    UpdateElements();
    
    SubscribeToEvent(lineEdit_, E_TEXTFINISHED, HANDLER(Console, HandleTextFinished));
    SubscribeToEvent(lineEdit_, E_UNHANDLEDKEY, HANDLER(Console, HandleLineEditKey));
    SubscribeToEvent(E_SCREENMODE, HANDLER(Console, HandleScreenMode));
    SubscribeToEvent(E_LOGMESSAGE, HANDLER(Console, HandleLogMessage));
}

Console::~Console()
{
    UI* ui = GetSubsystem<UI>();
    if (ui)
        ui->GetRoot()->RemoveChild(background_);
}

void Console::SetStyle(XMLFile* style)
{
    if (!style)
        return;
    
    style_ = style;
    background_->SetStyle(style, "ConsoleBackground");
    
    for (unsigned i = 0; i < rows_.Size(); ++i)
        rows_[i]->SetStyle(style, "ConsoleText");
    
    lineEdit_->SetStyle(style, "ConsoleLineEdit");
    
    UpdateElements();
}

void Console::SetVisible(bool enable)
{
    background_->SetVisible(enable);
    if (enable)
        GetSubsystem<UI>()->SetFocusElement(lineEdit_);
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
    
    rowContainer_->RemoveAllChildren();
    
    rows_.Resize(rows);
    for (unsigned i = 0; i < rows_.Size(); ++i)
    {
        if (!rows_[i])
        {
            rows_[i] = new Text(context_);
            rows_[i]->SetStyle(style_, "ConsoleText");
        }
        rowContainer_->AddChild(rows_[i]);
    }
    
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
    rowContainer_->SetFixedWidth(width - border.left_ - border.right_);
    lineEdit_->SetFixedHeight(lineEdit_->GetTextElement()->GetRowHeight());
}

bool Console::IsVisible() const
{
    if (!background_)
        return false;
    return background_->IsVisible();
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
        Script* script = GetSubsystem<Script>();
        if (script)
            script->Execute(line);
        
        // Store to history, then clear the lineedit
        history_.Push(line);
        if (history_.Size() > historyRows_)
            history_.Erase(history_.Begin());
        historyPosition_ = history_.Size();
        
        current_Row.Clear();
        lineEdit_->SetText(current_Row);
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
                current_Row = lineEdit_->GetText();
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
            lineEdit_->SetText(current_Row);
    }
}

void Console::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    UpdateElements();
}

void Console::HandleLogMessage(StringHash eventType, VariantMap& eventData)
{
    // If the rows are not fully initialized yet, or we are recursing here, do not write the message
    if (inLogMessage_ || rows_.Empty() || !rows_.Back())
        return;
    
    inLogMessage_ = true;
    
    using namespace LogMessage;
    
    // Be prepared for possible multi-line messages
    Vector<String> rows = eventData[P_MESSAGE].GetString().Split('\n');
    for (unsigned i = 0; i < rows.Size(); ++i)
    {
        // Remove the first row, change its text and re-add to the bottom
        Text* text = static_cast<Text*>(rowContainer_->GetChild(0));
        rowContainer_->RemoveChild(text);
        text->SetText(rows[i]);
        rowContainer_->AddChild(text);
    }
    
    inLogMessage_ = false;
}

}
