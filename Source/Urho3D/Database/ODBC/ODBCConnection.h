// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
    /// Finalize all prepared statements, close all BLOB handles, and finish all sqlite3_backup objects.
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
