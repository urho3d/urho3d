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

#ifdef URHO3D_DATABASE

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../Database/Database.h"
#include "../AngelScript/Generated_Templates.h"

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

static void DestructDbResult(DbResult* ptr)
{
    ptr->~DbResult();
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
    engine->RegisterObjectBehaviour("DbResult", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructDbResult), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("DbResult", asBEHAVE_CONSTRUCT, "void f(const DbResult&in)", asFUNCTION(ConstructDbResultCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("DbResult", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructDbResult), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("DbResult", "DbResult& opAssign(const DbResult&in)", asMETHODPR(DbResult, operator =, (const DbResult&), DbResult&), asCALL_THISCALL);
    engine->RegisterObjectMethod("DbResult", "uint get_numColumns() const", asMETHOD(DbResult, GetNumColumns), asCALL_THISCALL);
    engine->RegisterObjectMethod("DbResult", "uint get_numRows() const", asMETHOD(DbResult, GetNumRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("DbResult", "int64 get_numAffectedRows() const", asMETHOD(DbResult, GetNumAffectedRows), asCALL_THISCALL);
    engine->RegisterObjectMethod("DbResult", "Array<String>@ get_columns() const", asFUNCTION(DbResultGetColumns), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("DbResult", "Array<Variant>@ get_row(uint) const", asFUNCTION(DbResultGetRow), asCALL_CDECL_OBJLAST);
}

// ========================================================================================

static void RegisterDbConnection(asIScriptEngine* engine)
{
    RegisterObject<DbConnection>(engine, "DbConnection");
    engine->RegisterObjectMethod("DbConnection", "DbResult Execute(const String&in, bool useCursorEvent = false)", asMETHOD(DbConnection, Execute), asCALL_THISCALL);
    engine->RegisterObjectMethod("DbConnection", "const String& get_connectionString() const", asMETHOD(DbConnection, GetConnectionString), asCALL_THISCALL);
    engine->RegisterObjectMethod("DbConnection", "bool get_connected() const", asMETHOD(DbConnection, IsConnected), asCALL_THISCALL);
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

    engine->RegisterGlobalFunction("Database@+ get_database()", asFUNCTION(GetDatabase), asCALL_CDECL);
    engine->RegisterGlobalFunction("DBAPI get_DBAPI()", asFUNCTION(GetDBAPI), asCALL_CDECL);
}

}

#endif // def URHO3D_DATABASE
