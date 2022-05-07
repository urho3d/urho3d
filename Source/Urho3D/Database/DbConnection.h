// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#ifdef URHO3D_DATABASE_ODBC
#include "ODBC/ODBCConnection.h"
#elif defined(URHO3D_DATABASE_SQLITE)
#include "SQLite/SQLiteConnection.h"
#else
#error "Database subsystem not enabled"
#endif
