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

#include "../../Precompiled.h"

#include "../../Database/DatabaseEvents.h"
#include "../../IO/Log.h"

namespace Urho3D
{

DbConnection::DbConnection(Context* context, const String& connectionString) :
    Object(context),
    connectionString_(connectionString),
    connectionImpl_(0)
{
    if (sqlite3_open(connectionString.CString(), &connectionImpl_) != SQLITE_OK)
    {
        URHO3D_LOGERRORF("Could not connect: %s", sqlite3_errmsg(connectionImpl_));
        sqlite3_close(connectionImpl_);
        connectionImpl_ = 0;
    }
}

DbConnection::~DbConnection()
{
    Finalize();
    if (sqlite3_close(connectionImpl_) != SQLITE_OK)
    {
        // This should not happen after finalizing the connection, log error in Release but assert in Debug
        URHO3D_LOGERRORF("Could not disconnect: %s", sqlite3_errmsg(connectionImpl_));
        assert(false);
    }
    connectionImpl_ = 0;
}

void DbConnection::Finalize()
{
    // TODO
}

DbResult DbConnection::Execute(const String& sql, bool useCursorEvent)
{
    DbResult result;
    const char* zLeftover = 0;
    sqlite3_stmt* pStmt = 0;
    assert(connectionImpl_);
    int rc = sqlite3_prepare_v2(connectionImpl_, sql.Trimmed().CString(), -1, &pStmt, &zLeftover);
    if (rc != SQLITE_OK)
    {
        URHO3D_LOGERRORF("Could not execute: %s", sqlite3_errmsg(connectionImpl_));
        assert(!pStmt);
        return result;
    }
    if (*zLeftover)
    {
        URHO3D_LOGERROR("Could not execute: only one SQL statement is allowed");
        sqlite3_finalize(pStmt);
        return result;
    }

    unsigned numCols = (unsigned)sqlite3_column_count(pStmt);
    result.columns_.Resize(numCols);
    for (unsigned i = 0; i < numCols; ++i)
        result.columns_[i] = sqlite3_column_name(pStmt, i);

    bool filtered = false;
    bool aborted = false;

    while (1)
    {
        rc = sqlite3_step(pStmt);
        if (rc == SQLITE_ROW)
        {
            VariantVector colValues(numCols);
            for (unsigned i = 0; i < numCols; ++i)
            {
                int type = sqlite3_column_type(pStmt, i);
                if (type != SQLITE_NULL)
                {
                    // We can only bind primitive data type that our Variant class supports
                    switch (type)
                    {
                    case SQLITE_INTEGER:
                        colValues[i] = sqlite3_column_int(pStmt, i);
                        if (String(sqlite3_column_decltype(pStmt, i)).Compare("BOOLEAN", false) == 0)
                            colValues[i] = colValues[i] != 0;
                        break;

                    case SQLITE_FLOAT:
                        colValues[i] = sqlite3_column_double(pStmt, i);
                        break;

                    default:
                        // All other types are stored using their string representation in the Variant
                        colValues[i] = (const char*)sqlite3_column_text(pStmt, i);
                        break;
                    }
                }
            }

            if (useCursorEvent)
            {
                using namespace DbCursor;

                VariantMap& eventData = GetEventDataMap();
                eventData[P_DBCONNECTION] = this;
                eventData[P_RESULTIMPL] = pStmt;
                eventData[P_SQL] = sql;
                eventData[P_NUMCOLS] = numCols;
                eventData[P_COLVALUES] = colValues;
                eventData[P_COLHEADERS] = result.columns_;
                eventData[P_FILTER] = false;
                eventData[P_ABORT] = false;

                SendEvent(E_DBCURSOR, eventData);

                filtered = eventData[P_FILTER].GetBool();
                aborted = eventData[P_ABORT].GetBool();
            }

            if (!filtered)
                result.rows_.Push(colValues);
            if (aborted)
            {
                sqlite3_finalize(pStmt);
                break;
            }
        }
        else if (rc != SQLITE_DONE)
            URHO3D_LOGERRORF("Could not execute: %s", sqlite3_errmsg(connectionImpl_));
        if (rc != SQLITE_ROW)
        {
            sqlite3_finalize(pStmt);
            break;
        }
    }

    result.numAffectedRows_ = numCols ? -1 : sqlite3_changes(connectionImpl_);
    return result;
}

}
