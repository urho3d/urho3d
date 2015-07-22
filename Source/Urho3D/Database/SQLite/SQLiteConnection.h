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

#include <SQLite/sqlite3.h>

namespace Urho3D
{

/// %Database connection.
class URHO3D_API DbConnection : public Object
{
    OBJECT(DbConnection);

public:
    /// Construct.
    DbConnection(Context* context, const String& connectionString);
    /// Destruct.
    ~DbConnection();
    /// Finalize all prepared statements, close all BLOB handles, and finish all sqlite3_backup objects
    void Finalize();

    /// Execute semicolon-separated SQL statements immediately. Return true when the execution was successfully. Send E_DBCURSOR event for each row in the resultset when useCursorEvent parameter is set to true.
    bool Execute(const String& sql, bool useCursorEvent = false);

    const String& GetConnectionString() const { return connectionString_; }

    sqlite3* GetConnection() const { return connection_; }

    bool IsConnected() const { return connection_ != 0; }

private:
    String connectionString_;
    sqlite3* connection_;
};

}
