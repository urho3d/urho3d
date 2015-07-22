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

#include "../../Core/Profiler.h"
#include "../../Database/Database.h"

namespace Urho3D
{

Database::Database(Context* context_) :
    Object(context_),
    usePooling_(true)
{
    // Register Database library object factories
    RegisterDatabaseLibrary(context_);
}

Database::~Database()
{
    // Disconnect all the active and in-pool database connections
    DisconnectAll(connections_);
    for (HashMap<String, PODVector<DbConnection*> >::Iterator i = connectionsPool_.Begin(); i != connectionsPool_.End(); ++i)
        DisconnectAll(i->second_);
}

DbConnection* Database::Connect(const String& connectionString)
{
    PROFILE(DatabaseConnect);

    DbConnection* connection = 0;
    if (usePooling_)
    {
        PODVector<DbConnection*>& connectionsPool = connectionsPool_[connectionString];
        if (!connectionsPool.Empty())
        {
            connection = connectionsPool.Back();
            connectionsPool.Pop();
            assert(connection->IsConnected());
        }
    }
    if (!connection)
        connection = new DbConnection(context_, connectionString);
    if (connection->IsConnected())
    {
        connections_.Push(connection);
        return connection;
    }
    else
    {
        delete connection;
        return 0;
    }
}

void Database::Disconnect(DbConnection* connection)
{
    if (!connection)
        return;

    PROFILE(DatabaseDisconnect);

    connections_.Remove(connection);

    // Must finalize the connection before closing the connection or returning it to the pool
    connection->Finalize();

    if (usePooling_)
    {
        PODVector<DbConnection*>& connectionsPool = connectionsPool_[connection->GetConnectionString()];
        connectionsPool.Push(connection);
    }
    else
        delete connection;
}

void Database::DisconnectAll(PODVector<DbConnection*>& collection)
{
    PROFILE (DatabaseDisconnectAll);

    for (PODVector<DbConnection*>::Iterator i = collection.Begin(); i != collection.End(); ++i)
    {
        delete *i;  // The destructor ensures the connection is finalized and closed
        *i = 0;
    }
}

void URHO3D_API RegisterDatabaseLibrary(Context* context)
{
    // todo
}

}
