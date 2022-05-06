// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Profiler.h"
#include "../Database/Database.h"

namespace Urho3D
{

Database::Database(Context* context) :
    Object(context),
#ifdef ODBC_3_OR_LATER
    poolSize_(0)
#else
    poolSize_(M_MAX_UNSIGNED)
#endif
{
}

DBAPI Database::GetAPI()
{
#ifdef URHO3D_DATABASE_ODBC
    return DBAPI_ODBC;
#else
    return DBAPI_SQLITE;
#endif
}

DbConnection* Database::Connect(const String& connectionString)
{
    URHO3D_PROFILE(DatabaseConnect);

    SharedPtr<DbConnection> connection;
    if (IsPooling())
    {
        Vector<SharedPtr<DbConnection> >& connectionsPool = connectionsPool_[connectionString];
        while (!connectionsPool.Empty())
        {
            connection = connectionsPool.Back();
            connectionsPool.Pop();
            if (connection->IsConnected())
                break;
            connection = nullptr;
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
        return nullptr;
}

void Database::Disconnect(DbConnection* connection)
{
    if (!connection)
        return;

    URHO3D_PROFILE(DatabaseDisconnect);

    SharedPtr<DbConnection> dbConnection(connection);
    connections_.Remove(dbConnection);

    // Must finalize the connection before closing the connection or returning it to the pool
    connection->Finalize();

    if (IsPooling())
    {
        Vector<SharedPtr<DbConnection> >& connectionsPool = connectionsPool_[connection->GetConnectionString()];
        if (connectionsPool.Size() < poolSize_)
            connectionsPool.Push(dbConnection);
    }
}

}
