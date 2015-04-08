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

#include "../Container/RefCounted.h"

struct lua_State;

namespace Urho3D
{

class LuaScript;
class LuaScriptInstance;
class Variant;

/// Lua function.
class URHO3D_API LuaFunction : public RefCounted
{
public:
    /// Construct.
    LuaFunction(lua_State* lusState, int functionRef, bool needUnref = true);
    /// Destruct.
    ~LuaFunction();

    /// Check that function is valid.
    bool IsValid() const;
    /// Begin function call.
    bool BeginCall();
    /// Begin script object's function call.
    bool BeginCall(const LuaScriptInstance* instance);
    /// End call and actually execute the function.
    bool EndCall(int numReturns = 0);
    /// Push int to stack.
    void PushInt(int value);
    /// Push bool to stack.
    void PushBool(bool value);
    /// Push float to stack.
    void PushFloat(float value);
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
    bool PushVariant(const Variant& variant);
    /// Push Lua table to stack.
    bool PushLuaTable(const String& tableName);

    /// Return function ref.
    int GetFunctionRef() const { return functionRef_; }

private:
    /// Lua state.
    lua_State* luaState_;
    /// Function ref.
    int functionRef_;
    /// Need unref.
    bool needUnref_;
    /// Lua stack top.
    int stackTop_;
    /// Number of arguments.
    int numArguments_;
};

}
