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
#include <Urho3D/Database/DbResult.h>
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
    row_(0),
    maxRows_(50)
{
}

DatabaseDemo::~DatabaseDemo()
{
    // Although the managed database connection will be disconnected by Database subsystem automatically in its destructor,
    // it is a good practice for a class to balance the number of connect() and disconnect() calls.
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

    // In general, the connection string is really the only thing that need to be changed when switching underlying database API
    //   and that when using ODBC API then the connection string must refer to an already installed ODBC driver
    // Although it has not been tested yet but the ODBC API should be able to interface with any vendor provided ODBC drivers
    // In this particular demo, however, when using ODBC API then the SQLite-ODBC driver need to be installed
    // The SQLite-ODBC driver can be built from source downloaded from http://www.ch-werner.de/sqliteodbc/
    // You can try to install other ODBC driver and modify the connection string below to match your ODBC driver
    // Both DSN and DSN-less connection string should work
    // The ODBC API, i.e. URHO3D_DATABASE_ODBC build option, is only available for native (including RPI) platforms
    //   and it is designed for development of game server connecting to ODBC-compliant databases in mind

    // This demo will always work when using SQLite API as the SQLite database engine is embedded inside Urho3D game engine
    //   and this is also the case when targeting HTML5 in Emscripten build

    // Connect to a temporary in-memory SQLite database
    connection_ =
        GetSubsystem<Database>()->Connect(Database::GetAPI() == DBAPI_ODBC ? "Driver=SQLITE3;Database=:memory:" : "file://");

    // Subscribe to database cursor event to loop through query resultset
    SubscribeToEvent(connection_, E_DBCURSOR, HANDLER(DatabaseDemo, HandleDbCursor));

    // Show instruction
    Print("This demo connects to temporary in-memory database.\n"
        "All the tables and their data will be lost after exiting the demo.\n"
        "Enter 'quit' or 'exit' to exit the demo. Enter 'set maxrows=n' to set the maximum rows to be printed out.\n"
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
    using namespace DbCursor;

    // In a real application the P_SQL can be used to do the logic branching in a shared event handler
    // However, this is not required in this sample demo
    int numCols = eventData[P_NUMCOLS].GetInt();
    VariantVector* colValues = static_cast<VariantVector* >(eventData[P_COLVALUES].GetVoidPtr());
    Vector<String>* colHeaders = static_cast<Vector<String>* >(eventData[P_COLHEADERS].GetVoidPtr());

    // In this sample demo we just use db cursor to dump each row immediately so we can filter out the row to conserve memory
    // In a real application this can be used to perform the client-side filtering logic
    eventData[P_FILTER] = true;
    // In this sample demo we abort the further cursor movement when maximum rows being dumped has been reached
    eventData[P_ABORT] = ++row_ >= maxRows_;

    for (int i = 0; i < numCols; ++i)
        Print(ToString("Row #%d: %s = %s", row_, colHeaders->At(i).CString(), colValues->At(i).ToString().CString()));
}

void DatabaseDemo::HandleInput(const String& input)
{
    // Echo input string to stdout
    Print(input);
    row_ = 0;
    if (input == "quit" || input == "exit")
        engine_->Exit();
    else if (input.StartsWith("set") || input.StartsWith("get"))
    {
        // We expect a key/value pair for 'set' command
        Vector<String> tokens = input.Substring(3).Trimmed().Split('=');
        if (input.StartsWith("set"))
        {
            if (tokens[0].Trimmed() == "maxrows")
                maxRows_ = (unsigned)Max(ToUInt(tokens[1]), 1);
        }
        if (tokens[0].Trimmed() == "maxrows")
            Print(ToString("maxrows is set to %d", maxRows_));
        else
            Print("Unrecognize setting");
    }
    else
    {
        DbResult result = connection_->Execute(input, true);
        if (result.NumAffectedRows() > 0)
            Print(ToString("Number of affected rows: %d", result.NumAffectedRows()));
    }
    Print(" ");
}

void DatabaseDemo::Print(const String& output)
{
    // Logging appears both in the engine console and stdout
    LOGRAW(output + "\n");
}
