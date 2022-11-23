// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Database/DatabaseEvents.h"
#include "../../IO/Log.h"

namespace Urho3D
{

DbConnection::DbConnection(Context* context, const String& connectionString) :
    Object(context),
    connectionString_(connectionString),
    connectionImpl_(nullptr)
{
    if (sqlite3_open(connectionString.CString(), &connectionImpl_) != SQLITE_OK)
    {
        URHO3D_LOGERRORF("Could not connect: %s", sqlite3_errmsg(connectionImpl_));
        sqlite3_close(connectionImpl_);
        connectionImpl_ = nullptr;
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
    connectionImpl_ = nullptr;
}

void DbConnection::Finalize()
{
    // TODO
}

DbResult DbConnection::Execute(const String& sql, bool useCursorEvent)
{
    DbResult result;
    const char* zLeftover = nullptr;
    sqlite3_stmt* pStmt = nullptr;
    assert(connectionImpl_);

    // 2016-10-09: Prevent string corruption when trimmed is returned.
    String trimmedSqlStr = sql.Trimmed();

    int rc = sqlite3_prepare_v2(connectionImpl_, trimmedSqlStr.CString(), -1, &pStmt, &zLeftover);
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

    auto numCols = (unsigned)sqlite3_column_count(pStmt);
    result.columns_.Resize(numCols);
    for (unsigned i = 0; i < numCols; ++i)
        result.columns_[i] = sqlite3_column_name(pStmt, i);

    bool filtered = false;
    bool aborted = false;

    while (true)
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
