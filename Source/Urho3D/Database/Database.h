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
    Database(Context* context_);
    /// Return the underlying database API.
    static DBAPI GetAPI();

    /// Create new database connection. Return 0 if failed.
    DbConnection* Connect(const String& connectionString);
    /// Disconnect a database connection. The connection object pointer should not be used anymore after this.
    void Disconnect(DbConnection* connection);

    /// Return true when using internal database connection pool. The internal database pool is managed by the Database subsystem itself and should not be confused with ODBC connection pool option when ODBC is being used.
    bool IsPooling() const { return (bool)poolSize_; }

    /// Get internal database connection pool size.
    unsigned GetPoolSize() const { return poolSize_; }

    /// Set internal database connection pool size.
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
