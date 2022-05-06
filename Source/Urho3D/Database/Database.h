// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../Core/Object.h"
#include "../Database/DbConnection.h"

namespace Urho3D
{

/// Supported database API.
enum DBAPI
{
    DBAPI_SQLITE = 0,
    DBAPI_ODBC
};

class DbConnection;

/// %Database subsystem. Manage database connections.
class URHO3D_API Database : public Object
{
    URHO3D_OBJECT(Database, Object);

public:
    /// Construct.
    explicit Database(Context* context);
    /// Return the underlying database API.
    static DBAPI GetAPI();

    /// Create new database connection. Return 0 if failed.
    DbConnection* Connect(const String& connectionString);
    /// Disconnect a database connection. The connection object pointer should not be used anymore after this.
    void Disconnect(DbConnection* connection);

    /// Return true when using internal database connection pool. The internal database pool is managed by the Database subsystem itself and should not be confused with ODBC connection pool option when ODBC is being used.
    /// @property
    bool IsPooling() const { return (bool)poolSize_; }

    /// Get internal database connection pool size.
    /// @property
    unsigned GetPoolSize() const { return poolSize_; }

    /// Set internal database connection pool size.
    /// @property
    void SetPoolSize(unsigned poolSize) { poolSize_ = poolSize; }

private:
    /// %Database connection pool size. Default to 0 when using ODBC 3.0 or later as ODBC 3.0 driver manager could manage its own database connection pool.
    unsigned poolSize_;
    /// Active database connections.
    Vector<SharedPtr<DbConnection> > connections_;
    ///%Database connections pool.
    HashMap<String, Vector<SharedPtr<DbConnection> > > connectionsPool_;
};

}
