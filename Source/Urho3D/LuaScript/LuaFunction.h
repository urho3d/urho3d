// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/RefCounted.h"

struct lua_State;
using lua_CFunction = int (*) (lua_State *L);

namespace Urho3D
{

class LuaScript;
class LuaScriptInstance;
class Variant;

/// C++ representation of Lua function object.
class URHO3D_API LuaFunction : public RefCounted
{
public:
    /// Construct from a Lua function object at the specified stack index.
    LuaFunction(lua_State* L, int index);
    /// Construct from a C function.
    LuaFunction(lua_State* L, lua_CFunction func);
    /// Destruct.
    ~LuaFunction() override;

    /// Check that function is valid.
    bool IsValid() const;
    /// Begin function call. When a script object is given then pass it as self argument (first parameter) to the function call.
    bool BeginCall(const LuaScriptInstance* instance = nullptr);
    /// End call and actually execute the function. The return values, if any, are still left in the stack when this call returns.
    bool EndCall(int numReturns = 0);
    /// Push int to stack.
    void PushInt(int value);
    /// Push bool to stack.
    void PushBool(bool value);
    /// Push float to stack.
    void PushFloat(float value);
    /// Push double to stack.
    void PushDouble(double value);
    /// Push string to stack.
    void PushString(const String& string);
    /// Push user type to stack.
    void PushUserType(void* userType, const char* typeName);

    /// Push user type to stack.
    template <typename T> void PushUserType(const T* userType)
    {
        PushUserType((void*)userType, T::GetTypeName().CString());
    }

    /// Push user type to stack.
    template <typename T> void PushUserType(const T& userType)
    {
        PushUserType((void*)&userType, T::GetTypeName().CString());
    }

    /// Push user type to stack.
    template <typename T> void PushUserType(const T* userType, const char* typeName)
    {
        PushUserType((void*)userType, typeName);
    }

    /// Push user type to stack.
    template <typename T> void PushUserType(const T& userType, const char* typeName)
    {
        PushUserType((void*)&userType, typeName);
    }

    /// Push variant to stack.
    void PushVariant(const Variant& variant, const char* asType = nullptr);
    /// Push Lua table to stack. When the specified table is not found then a nil is pushed instead.
    void PushLuaTable(const char* tableName);
    /// Push Lua table to stack. When the specified table is not found then a nil is pushed instead.
    void PushLuaTable(const String& tableName) { PushLuaTable(tableName.CString()); }

    /// Return function ref.
    int GetFunctionRef() const { return functionRef_; }

private:
    /// Lua state.
    lua_State* luaState_;
    /// Number of arguments being pushed so far. For internal use only.
    int numArguments_;
    /// Lua reference to function object.
    int functionRef_;
};

}
