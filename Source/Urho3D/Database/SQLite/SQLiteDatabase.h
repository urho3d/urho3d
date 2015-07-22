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

#include "../../Core/Object.h"
#include "SQLiteConnection.h"

namespace Urho3D
{

class DbConnection;

/// %Database subsystem. Manage database connections.
class URHO3D_API Database : public Object
{
    OBJECT(Database);

public:
    /// Construct.
    Database(Context* context_);
    /// Destruct. Disconnect database connections.
    virtual ~Database();

    /// Create new database connection. Return 0 if failed.
    DbConnection* Connect(const String& connectionString);
    /// Disconnect a database connection.
    void Disconnect(DbConnection* connection);

    bool IsUsePooling() const { return usePooling_; }

    void SetUsePooling(bool usePooling) { usePooling_ = usePooling; }

private:
    /// Internal helper to disconnect all the database connections in the collection.
    void DisconnectAll(PODVector<DbConnection*>& collection);

    /// Using Database connection pool flag.
    bool usePooling_;
    /// Active database connections.
    PODVector<DbConnection*> connections_;
    /// Database connections pool.
    HashMap<String, PODVector<DbConnection*> > connectionsPool_;
};

/// Register Database library objects.
void URHO3D_API RegisterDatabaseLibrary(Context* context);

}
