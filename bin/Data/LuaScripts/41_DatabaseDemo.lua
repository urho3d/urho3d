-- Database demo. This sample demonstrates how to use database subsystem to connect to a database and execute adhoc SQL statements.

require "LuaScripts/Utilities/Sample"

local connection
local row
local maxRows = 50

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Disable default execution of Lua from the console
    SetExecuteConsoleCommands(false)

    -- Subscribe to console commands and the frame update
    SubscribeToEvent("ConsoleCommand", "HandleConsoleCommand")
    SubscribeToEvent("Update", "HandleUpdate")

    -- Subscribe key down event
    SubscribeToEvent("KeyDown", "HandleEscKeyDown")

    -- Hide logo to make room for the console
    SetLogoVisible(false)

    -- Show the console by default, make it large
    console.numRows = graphics.height / 16
    console.numBufferedRows = 2 * console.numRows
    console.commandInterpreter = "LuaScriptEventInvoker"
    console.visible = true
    console.closeButton.visible = false

    -- Show OS mouse cursor
    input.mouseVisible = true

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)

    -- Open the operating system console window (for stdin / stdout) if not open yet
    -- Do not open in fullscreen, as this would cause constant device loss
    if not graphics.fullscreen then
        OpenConsoleWindow()
    end

    -- In general, the connection string is really the only thing that need to be changed when switching underlying database API
    --   and that when using ODBC API then the connection string must refer to an already installed ODBC driver
    -- Although it has not been tested yet but the ODBC API should be able to interface with any vendor provided ODBC drivers
    -- In this particular demo, however, when using ODBC API then the SQLite-ODBC driver need to be installed
    -- The SQLite-ODBC driver can be built from source downloaded from http:--www.ch-werner.de/sqliteodbc/
    -- You can try to install other ODBC driver and modify the connection string below to match your ODBC driver
    -- Both DSN and DSN-less connection string should work
    -- The ODBC API, i.e. URHO3D_DATABASE_ODBC build option, is only available for native (including RPI) platforms
    --   and it is designed for development of game server connecting to ODBC-compliant databases in mind

    -- This demo will always work when using SQLite API as the SQLite database engine is embedded inside Urho3D game engine
    --   and this is also the case when targeting Web platform

    -- We could have used #ifdef to init the connection string during compile time, but below shows how it is done during runtime
    -- The "URHO3D_DATABASE_ODBC" compiler define is set when URHO3D_DATABASE_ODBC build option is enabled
    -- Connect to a temporary in-memory SQLite database
    connection = database:Connect(GetDBAPI() == DBAPI_ODBC and "Driver=SQLite3;Database=:memory:" or "file://")

    -- Subscribe to database cursor event to loop through query resultset
    SubscribeToEvent("DbCursor", "HandleDbCursor")

    -- Show instruction
    print([[This demo connects to temporary in-memory database.
All the tables and their data will be lost after exiting the demo.
Enter a valid SQL statement in the console input and press Enter to execute.
Enter 'get/set maxrows [number]' to get/set the maximum rows to be printed out.
Enter 'get/set connstr [string]' to get/set the database connection string and establish a new connection to it.
Enter 'quit' or 'exit' to exit the demo.
For example:]])
    HandleInput("create table tbl1(col1 varchar(10), col2 smallint)")
    HandleInput("insert into tbl1 values('Hello', 10)")
    HandleInput("insert into tbl1 values('World', 20)")
    HandleInput("select * from tbl1")
end

function HandleConsoleCommand(eventType, eventData)
    if eventData["Id"]:GetString() == "LuaScriptEventInvoker" then
        HandleInput(eventData["Command"]:GetString())
    end
end

function HandleUpdate(eventType, eventData)
    -- Check if there is input from stdin
    local input = GetConsoleInput()
    if input:len() > 0 then
        HandleInput(input)
    end
end

function HandleEscKeyDown(eventType, eventData)
    -- Unlike the other samples, exiting the engine when ESC is pressed instead of just closing the console
    if eventData["Key"]:GetInt() == KEY_ESC then
        engine:Exit()
    end
end

function HandleDbCursor(eventType, eventData)
    -- In a real application the P_SQL can be used to do the logic branching in a shared event handler
    -- However, this is not required in this sample demo
    local colValues = eventData["ColValues"]:GetVariantVector()
    local colHeaders = eventData["ColHeaders"]:GetStringVector()

    -- In this sample demo we just use db cursor to dump each row immediately so we can filter out the row to conserve memory
    -- In a real application this can be used to perform the client-side filtering logic
    eventData["Filter"] = true
    -- In this sample demo we abort the further cursor movement when maximum rows being dumped has been reached
    row = row + 1
    eventData["Abort"] = row >= maxRows

    for i, colHeader in ipairs(colHeaders) do
        print("Row #" .. row .. ": " .. colHeader .. " = " .. colValues[i])
    end
end

function HandleInput(input)
    -- Echo input string to stdout
    print(input)
    row = 0
    if input == "quit" or input == "exit" then
        engine:Exit()
    elseif input:find("set") or input:find("get") then
        -- We expect a key/value pair for 'set' command
        local command, setting, value
        _, _, command, setting, value = input:find("([gs]et)%s*(%a*)%s*(.*)")
        if command == "set" and value ~= nil then
            if setting == "maxrows" then
                maxRows = Max(value, 1)
            elseif (setting == "connstr") then
                local newConnection = database:Connect(value)
                if newConnection ~= nil then
                    database:Disconnect(connection)
                    connection = newConnection
                end
            end
        end
        if setting ~= nil then
            if setting == "maxrows" then
                print("maximum rows is set to " .. maxRows)
            elseif setting == "connstr" then
                print("connection string is set to " .. connection.connectionString)
            else
                print("Unrecognized setting: " .. setting)
            end
        else
            print("Missing setting paramater. Recognized settings are: maxrows, connstr")
        end
    else
        -- In this sample demo we use the dbCursor event to loop through each row as it is being fetched
        -- Regardless of this event is being used or not, all the fetched rows will be made available in the DbResult object,
        --   unless the dbCursor event handler has instructed to filter out the fetched row from the final result
        local result = connection:Execute(input, true)

        -- Number of affected rows is only meaningful for DML statements like insert/update/delete
        if result.numAffectedRows ~= -1 then
            print("Number of affected rows: " .. result.numAffectedRows)
        end
    end
    print(" ")
end

-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
    "<patch>" ..
            "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button2']]\">" ..
            "        <attribute name=\"Is Visible\" value=\"false\" />" ..
            "    </add>" ..
            "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" ..
            "        <attribute name=\"Is Visible\" value=\"false\" />" ..
            "    </add>" ..
            "</patch>"
end
