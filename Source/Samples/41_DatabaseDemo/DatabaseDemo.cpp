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

#include <Urho3D/Urho3D.h>

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Database/Database.h>
#include <Urho3D/Database/DatabaseEvents.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Engine/EngineEvents.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/UI/Button.h>

#include "DatabaseDemo.h"

// Expands to this example's entry-point
DEFINE_APPLICATION_MAIN(DatabaseDemo)

DatabaseDemo::DatabaseDemo(Context* context) :
    Sample(context),
    connection_(0),
    row_(0)
{
}

DatabaseDemo::~DatabaseDemo()
{
    GetSubsystem<Database>()->Disconnect(connection_);
}

void DatabaseDemo::Start()
{
    // Execute base class startup
    Sample::Start();

    // Subscribe to console commands and the frame update
    SubscribeToEvent(E_CONSOLECOMMAND, HANDLER(DatabaseDemo, HandleConsoleCommand));
    SubscribeToEvent(E_UPDATE, HANDLER(DatabaseDemo, HandleUpdate));

    // Subscribe key down event
    SubscribeToEvent(E_KEYDOWN, HANDLER(DatabaseDemo, HandleEscKeyDown));

    // Hide logo to make room for the console
    SetLogoVisible(false);

    // Show the console by default, make it large. Console will show the text edit field when there is at least one
    // subscriber for the console command event
    Console* console = GetSubsystem<Console>();
    console->SetNumRows((unsigned)(GetSubsystem<Graphics>()->GetHeight() / 16));
    console->SetNumBufferedRows(2 * console->GetNumRows());
    console->SetCommandInterpreter(GetTypeName());
    console->SetVisible(true);
    console->GetCloseButton()->SetVisible(false);

    // Show OS mouse cursor
    GetSubsystem<Input>()->SetMouseVisible(true);

    // Open the operating system console window (for stdin / stdout) if not open yet
    OpenConsoleWindow();

    // Connect to a temporary in-memory database
    connection_ = GetSubsystem<Database>()->Connect("file://");

    // Subscribe to database cursor event to loop through query resultset
    SubscribeToEvent(connection_, E_DBCURSOR, HANDLER(DatabaseDemo, HandleDbCursor));

    // Show instruction
    Print("This demo connects to temporary in-memory database.\n"
        "All the tables and their data will be lost after exiting the demo.\n"
        "Enter a valid SQL statement in the console input and press Enter to execute.\n"
        "For example:\n ");
    HandleInput("create table tbl1(col1 varchar(10), col2 smallint)");
    HandleInput("insert into tbl1 values('Hello', 10)");
    HandleInput("insert into tbl1 values('World', 20)");
    HandleInput("select * from tbl1");
}

void DatabaseDemo::HandleConsoleCommand(StringHash eventType, VariantMap& eventData)
{
    using namespace ConsoleCommand;
    if (eventData[P_ID].GetString() == GetTypeName())
        HandleInput(eventData[P_COMMAND].GetString());
}

void DatabaseDemo::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Check if there is input from stdin
    String input = GetConsoleInput();
    if (input.Length())
        HandleInput(input);
}

void DatabaseDemo::HandleEscKeyDown(StringHash eventType, VariantMap& eventData)
{
    // Unlike the other samples, exiting the engine when ESC is pressed instead of just closing the console
    if (eventData[KeyDown::P_KEY].GetInt() == KEY_ESC)
        engine_->Exit();
}

void DatabaseDemo::HandleDbCursor(StringHash eventType, VariantMap& eventData)
{
    ++row_;

    using namespace DbCursor;

    // In a real application the P_SQL can be used to do the logic branching in a shared event handler
    // However, this is not required in this sample demo
    int numCols = eventData[P_NUMCOLS].GetInt();
    const char** colValues = static_cast<const char**>(eventData[P_COLVALUES].GetVoidPtr());
    const char** colHeaders = static_cast<const char**>(eventData[P_COLHEADERS].GetVoidPtr());
    for (int i = 0; i < numCols; ++i)
        Print(ToString("Row #%d: %s = %s", row_, colHeaders[i], colValues[i]));
}

void DatabaseDemo::HandleInput(const String& input)
{
    // Echo input string to stdout
    Print(input);
    row_ = 0;
    if (input == "quit" || input == "exit")
        engine_->Exit();
    else
        connection_->Execute(input, true);
    Print(" ");
}

void DatabaseDemo::Print(const String& output)
{
    // Logging appears both in the engine console and stdout
    LOGRAW(output + "\n");
}
