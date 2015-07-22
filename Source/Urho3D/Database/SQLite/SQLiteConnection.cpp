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

#include "../../Precompiled.h"

#include "../../Database/DatabaseEvents.h"
#include "../../IO/Log.h"

namespace Urho3D
{

struct DbConnectionExecuteCallbackData
{
    DbConnection* connection;
    String sql;
};

int DbConnectionExecuteCallback(void* data, int numCols, char** colValues, char** colHeaders)
{
    DbConnectionExecuteCallbackData* callbackData = static_cast<DbConnectionExecuteCallbackData*>(data);
    DbConnection* connection = callbackData->connection;

    using namespace DbCursor;

    VariantMap& eventData = connection->GetEventDataMap();
    eventData[P_DBCONNECTION] = connection;
    eventData[P_SQL] = callbackData->sql;
    eventData[P_NUMCOLS] = numCols;
    eventData[P_COLVALUES] = colValues;
    eventData[P_COLHEADERS] = colHeaders;
    eventData[P_ABORT] = false;     // Expect the event handler would set this to true to abort further cursor events

    connection->SendEvent(E_DBCURSOR, eventData);

    return eventData[P_ABORT].GetBool();
}

DbConnection::DbConnection(Context* context, const String& connectionString) :
    Object(context),
    connectionString_(connectionString),
    connection_(0)
{
    if (sqlite3_open(connectionString.CString(), &connection_) != SQLITE_OK)
    {
        LOGERRORF("Could not connect: %s", sqlite3_errmsg(connection_));
        sqlite3_close(connection_);
        connection_ = 0;
    }
}

DbConnection::~DbConnection()
{
    Finalize();
    if (sqlite3_close(connection_) != SQLITE_OK)
    {
        // This should not happen after finalizing the connection, log error in Release but assert in Debug
        LOGERRORF("Could not disconnect: %s", sqlite3_errmsg(connection_));
        assert(false);
    }
    connection_ = 0;
}

void DbConnection::Finalize()
{
    // TODO
}

bool DbConnection::Execute(const String& sql, bool useCursorEvent)
{
    assert(connection_);
    DbConnectionExecuteCallbackData data;
    data.connection = this;
    data.sql = sql;
    char* msg;

    bool rc = sqlite3_exec(connection_, sql.CString(), useCursorEvent ? &DbConnectionExecuteCallback : 0, &data, &msg) == SQLITE_OK;
    if (!rc)
    {
        LOGERRORF("Could not execute: %s", msg);
        sqlite3_free(msg);
    }
    return rc;
}

}
