// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#ifdef URHO3D_DATABASE

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../Database/Database.h"
//#include "../AngelScript/Generated_Templates.h"
//#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Generated_Members.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_Database(asIScriptEngine* engine)
{
    engine->RegisterObjectType("DbConnection", 0, asOBJ_REF);
    engine->RegisterObjectType("DbResult", sizeof(DbResult), asOBJ_VALUE | asOBJ_APP_CLASS_C);
}

// ========================================================================================

static void ConstructDbResult(DbResult* ptr)
{
    new(ptr) DbResult();
}

static void ConstructDbResultCopy(const DbResult& other, DbResult* ptr)
{
    new(ptr) DbResult(other);
}

static CScriptArray* DbResultGetColumns(DbResult* ptr)
{
    return VectorToArray<String>(ptr->GetColumns(), "Array<String>");
}

static CScriptArray* DbResultGetRow(unsigned index, DbResult* ptr)
{
    const Vector<VariantVector>& rows = ptr->GetRows();
    if (index >= rows.Size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return nullptr;
    }
    else
        return VectorToArray<Variant>(rows[index], "Array<Variant>");
}

static void RegisterDbResult(asIScriptEngine* engine)
{
    engine->RegisterObjectBehaviour("DbResult", asBEHAVE_CONSTRUCT, "void f()", AS_FUNCTION_OBJLAST(ConstructDbResult), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("DbResult", asBEHAVE_CONSTRUCT, "void f(const DbResult&in)", AS_FUNCTION_OBJLAST(ConstructDbResultCopy), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("DbResult", asBEHAVE_DESTRUCT, "void f()", AS_DESTRUCTOR(DbResult), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("DbResult", "DbResult& opAssign(const DbResult&in)", AS_METHODPR(DbResult, operator =, (const DbResult&), DbResult&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DbResult", "uint get_numColumns() const", AS_METHOD(DbResult, GetNumColumns), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DbResult", "uint get_numRows() const", AS_METHOD(DbResult, GetNumRows), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DbResult", "int64 get_numAffectedRows() const", AS_METHOD(DbResult, GetNumAffectedRows), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DbResult", "Array<String>@ get_columns() const", AS_FUNCTION_OBJLAST(DbResultGetColumns), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("DbResult", "Array<Variant>@ get_row(uint) const", AS_FUNCTION_OBJLAST(DbResultGetRow), AS_CALL_CDECL_OBJLAST);
}

// ========================================================================================

/*
static DbConnection* DbConnection_DbConnection_Context()
{
    Context* context = GetScriptContext();
    return new DbConnection(context);
}
*/

static void RegisterDbConnection(asIScriptEngine* engine)
{
    RegisterMembers_Object<DbConnection>(engine, "DbConnection");

    //engine->RegisterObjectBehaviour("DbConnection", asBEHAVE_FACTORY, "DbConnection@+ f()", AS_FUNCTION(DbConnection_DbConnection_Context), AS_CALL_CDECL);

    engine->RegisterObjectMethod("DbConnection", "DbResult Execute(const String&in, bool useCursorEvent = false)", AS_METHOD(DbConnection, Execute), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DbConnection", "const String& get_connectionString() const", AS_METHOD(DbConnection, GetConnectionString), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DbConnection", "bool get_connected() const", AS_METHOD(DbConnection, IsConnected), AS_CALL_THISCALL);

    /*
    RegisterObject<DbConnection>(engine, "DbConnection");
    engine->RegisterObjectMethod("DbConnection", "DbResult Execute(const String&in, bool useCursorEvent = false)", AS_METHOD(DbConnection, Execute), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DbConnection", "const String& get_connectionString() const", AS_METHOD(DbConnection, GetConnectionString), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("DbConnection", "bool get_connected() const", AS_METHOD(DbConnection, IsConnected), AS_CALL_THISCALL);
    */
}

// ========================================================================================

static Database* GetDatabase()
{
    return GetScriptContext()->GetSubsystem<Database>();
}

static DBAPI GetDBAPI()
{
    return Database::GetAPI();
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_Database(asIScriptEngine* engine)
{
    RegisterDbResult(engine);
    RegisterDbConnection(engine);

    engine->RegisterGlobalFunction("Database@+ get_database()", AS_FUNCTION(GetDatabase), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("DBAPI get_DBAPI()", AS_FUNCTION(GetDBAPI), AS_CALL_CDECL);
}

}

#endif // def URHO3D_DATABASE
