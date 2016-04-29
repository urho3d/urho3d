//
// Copyright (c) 2008-2016 the Urho3D project.
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
URHO3D_DEFINE_APPLICATION_MAIN(DatabaseDemo)

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
    connection_ = 0;
}

void DatabaseDemo::Start()
{
    // Execute base class startup
    Sample::Start();

    // Subscribe to console commands and the frame update
    SubscribeToEvent(E_CONSOLECOMMAND, URHO3D_HANDLER(DatabaseDemo, HandleConsoleCommand));
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(DatabaseDemo, HandleUpdate));

    // Subscribe key down event
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(DatabaseDemo, HandleEscKeyDown));

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

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);

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
    //   and this is also the case when targeting Web platform

    // We could have used #ifdef to init the connection string during compile time, but below shows how it is done during runtime
    // The "URHO3D_DATABASE_ODBC" compiler define is set when URHO3D_DATABASE_ODBC build option is enabled
    // Connect to a temporary in-memory SQLite database
    connection_ =
        GetSubsystem<Database>()->Connect(Database::GetAPI() == DBAPI_ODBC ? "Driver=SQLite3;Database=:memory:" : "file://");

    // Subscribe to database cursor event to loop through query resultset
    SubscribeToEvent(E_DBCURSOR, URHO3D_HANDLER(DatabaseDemo, HandleDbCursor));

    // Show instruction
    Print("This demo connects to temporary in-memory database.\n"
        "All the tables and their data will be lost after exiting the demo.\n"
        "Enter a valid SQL statement in the console input and press Enter to execute.\n"
        "Enter 'get/set maxrows [number]' to get/set the maximum rows to be printed out.\n"
        "Enter 'get/set connstr [string]' to get/set the database connection string and establish a new connection to it.\n"
        "Enter 'quit' or 'exit' to exit the demo.\n"
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
    unsigned numCols = eventData[P_NUMCOLS].GetUInt();
    const VariantVector& colValues = eventData[P_COLVALUES].GetVariantVector();
    const Vector<String>& colHeaders = eventData[P_COLHEADERS].GetStringVector();

    // In this sample demo we just use db cursor to dump each row immediately so we can filter out the row to conserve memory
    // In a real application this can be used to perform the client-side filtering logic
    eventData[P_FILTER] = true;
    // In this sample demo we abort the further cursor movement when maximum rows being dumped has been reached
    eventData[P_ABORT] = ++row_ >= maxRows_;

    for (unsigned i = 0; i < numCols; ++i)
        Print(ToString("Row #%d: %s = %s", row_, colHeaders[i].CString(), colValues[i].ToString().CString()));
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
        Vector<String> tokens = input.Substring(3).Split(' ');
        String setting = tokens.Size() ? tokens[0] : "";
        if (input.StartsWith("set") && tokens.Size() > 1)
        {
            if (setting == "maxrows")
                maxRows_ = Max(ToUInt(tokens[1]), 1U);
            else if (setting == "connstr")
            {
                String newConnectionString(input.Substring(input.Find(" ", input.Find("connstr")) + 1));
                Database* database = GetSubsystem<Database>();
                DbConnection* newConnection = database->Connect(newConnectionString);
                if (newConnection)
                {
                    database->Disconnect(connection_);
                    connection_ = newConnection;
                }
            }
        }
        if (tokens.Size())
        {
            if (setting == "maxrows")
                Print(ToString("maximum rows is set to %d", maxRows_));
            else if (setting == "connstr")
                Print(ToString("connection string is set to %s", connection_->GetConnectionString().CString()));
            else
                Print(ToString("Unrecognized setting: %s", setting.CString()));
        }
        else
            Print("Missing setting paramater. Recognized settings are: maxrows, connstr");
    }
    else
    {
        // In this sample demo we use the dbCursor event to loop through each row as it is being fetched
        // Regardless of this event is being used or not, all the fetched rows will be made available in the DbResult object,
        //   unless the dbCursor event handler has instructed to filter out the fetched row from the final result
        DbResult result = connection_->Execute(input, true);

        // Number of affected rows is only meaningful for DML statements like insert/update/delete
        if (result.GetNumAffectedRows() != -1)
            Print(ToString("Number of affected rows: %d", result.GetNumAffectedRows()));
    }
    Print(" ");
}

void DatabaseDemo::Print(const String& output)
{
    // Logging appears both in the engine console and stdout
    URHO3D_LOGRAW(output + "\n");
}
