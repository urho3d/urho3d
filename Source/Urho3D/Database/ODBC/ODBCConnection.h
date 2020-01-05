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

#pragma once

#include "../../Core/Object.h"
#include "../../Database/DbResult.h"

#include <nanodbc/nanodbc.h>

namespace Urho3D
{

/// %Database connection.
class URHO3D_API DbConnection : public Object
{
    URHO3D_OBJECT(DbConnection, Object);

public:
    /// Construct.
    DbConnection(Context* context, const String& connectionString);
    /// Destruct.
    virtual ~DbConnection() override;
    /// Finalize all prepared statements, close all BLOB handles, and finish all sqlite3_backup objects
    void Finalize();

    /// Execute an SQL statements immediately. Send E_DBCURSOR event for each row in the resultset when useCursorEvent parameter is set to true.
    DbResult Execute(const String& sql, bool useCursorEvent = false);

    /// Return database connection string. The connection string for SQLite3 is using the URI format described in https://www.sqlite.org/uri.html, while the connection string for ODBC is using DSN format as per ODBC standard.
    const String& GetConnectionString() const { return connectionString_; }

    /// Return the underlying implementation connection object pointer. It is sqlite* when using SQLite3 or nanodbc::connection* when using ODBC.
    const nanodbc::connection* GetConnectionImpl() const { return &connectionImpl_; }

    /// Return true when the connection object is connected to the associated database.
    bool IsConnected() const { return connectionImpl_.connected(); }

private:
    /// Internal helper method to handle runtime exception by logging it to stderr stream.
    void HandleRuntimeError(const char* message, const char* cause);

    /// The connection string for SQLite3 is using the URI format described in https://www.sqlite.org/uri.html, while the connection string for ODBC is using DSN format as per ODBC standard.
    String connectionString_;
    /// The underlying implementation connection object.
    nanodbc::connection connectionImpl_;
};

}
