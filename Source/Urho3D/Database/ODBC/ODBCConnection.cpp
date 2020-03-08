//
// Copyright (c) 2008-2020 the Urho3D project.
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

#ifdef _WIN32
// Needs to be included above sql.h for windows
#define NOMINMAX
#include <windows.h>
#endif

#include <sqlext.h>

namespace Urho3D
{

DbConnection::DbConnection(Context* context, const String& connectionString) :
    Object(context),
    connectionString_(connectionString)
{
    try
    {
        connectionImpl_ = nanodbc::connection(connectionString.CString());
    }
    catch (std::runtime_error& e)
    {
        HandleRuntimeError("Could not connect", e.what());
    }
}

DbConnection::~DbConnection()
{
    try
    {
        Finalize();
        connectionImpl_.disconnect();
    }
    catch (std::runtime_error& e)
    {
        // This should not happen after finalizing the connection, log error in Release but assert in Debug
        HandleRuntimeError("Could not disconnect", e.what());
        assert(false);
    }
}

void DbConnection::Finalize()
{
    // TODO
}

DbResult DbConnection::Execute(const String& sql, bool useCursorEvent)
{
    DbResult result;

    try
    {
        result.resultImpl_ = nanodbc::execute(connectionImpl_, sql.Trimmed().CString());
        unsigned numCols = (unsigned)result.resultImpl_.columns();
        if (numCols)
        {
            result.columns_.Resize(numCols);
            for (unsigned i = 0; i < numCols; ++i)
                result.columns_[i] = result.resultImpl_.column_name((short)i).c_str();

            bool filtered = false;
            bool aborted = false;

            while (result.resultImpl_.next())
            {
                VariantVector colValues(numCols);
                for (unsigned i = 0; i < numCols; ++i)
                {
                    if (!result.resultImpl_.is_null((short)i))
                    {
                        // We can only bind primitive data type that our Variant class supports
                        switch (result.resultImpl_.column_c_datatype((short)i))
                        {
                        case SQL_C_LONG:
                            colValues[i] = result.resultImpl_.get<int>((short)i);
                            if (result.resultImpl_.column_datatype((short)i) == SQL_BIT)
                                colValues[i] = colValues[i] != 0;
                            break;

                        case SQL_C_FLOAT:
                            colValues[i] = result.resultImpl_.get<float>((short)i);
                            break;

                        case SQL_C_DOUBLE:
                            colValues[i] = result.resultImpl_.get<double>((short)i);
                            break;

                        default:
                            // All other types are stored using their string representation in the Variant
                            colValues[i] = result.resultImpl_.get<nanodbc::string>((short)i).c_str();
                            break;
                        }
                    }
                }

                if (useCursorEvent)
                {
                    using namespace DbCursor;

                    VariantMap& eventData = GetEventDataMap();
                    eventData[P_DBCONNECTION] = this;
                    eventData[P_RESULTIMPL] = &result.resultImpl_;
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
                    break;
            }
        }
        result.numAffectedRows_ = numCols ? -1 : result.resultImpl_.affected_rows();
    }
    catch (std::runtime_error& e)
    {
        HandleRuntimeError("Could not execute", e.what());
    }

    return result;
}

void DbConnection::HandleRuntimeError(const char* message, const char* cause)
{
    StringVector tokens = (String(cause) + "::").Split(':');      // Added "::" as sentinels against unexpected cause format
    URHO3D_LOGERRORF("%s: nanodbc:%s:%s", message, tokens[1].CString(), tokens[2].CString());
}

}
