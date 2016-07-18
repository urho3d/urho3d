//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Core/Context.h"

struct lua_State;

using namespace Urho3D;

/// Check is String.
#define tolua_isurho3dstring tolua_isstring
/// Push String.
#define tolua_pushurho3dstring(L, s) tolua_pushstring(L, s.CString())
/// Convert to String.
const char* tolua_tourho3dstring(lua_State* L, int narg, const char* str);
/// Convert to String.
const char* tolua_tourho3dstring(lua_State* L, int narg, const String& str);

/// Set context.
void SetContext(lua_State* L, Context* context);
/// Return context.
Context* GetContext(lua_State* L);

/// Create object.
template <typename T> int ToluaNewObject(lua_State* tolua_S)
{
    T* object = Mtolua_new(T(GetContext(tolua_S)));
    tolua_pushusertype(tolua_S, (void*)object, T::GetTypeNameStatic().CString());
    return 1;
}

/// Create object with garbage collection.
template <typename T> int ToluaNewObjectGC(lua_State* tolua_S)
{
    T* object = Mtolua_new(T(GetContext(tolua_S)));
    tolua_pushusertype(tolua_S, (void*)object, T::GetTypeNameStatic().CString());
    tolua_register_gc(tolua_S, lua_gettop(tolua_S));
    return 1;
}

/// Return subsystem.
template <typename T> int ToluaGetSubsystem(lua_State* tolua_S)
{
    T* subsystem = GetContext(tolua_S)->GetSubsystem<T>();
    tolua_pushusertype(tolua_S, (void*)subsystem, T::GetTypeNameStatic().CString());
    return 1;
}

/// Check is Vector<T>.
template <typename T> int ToluaIsVector(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
    return tolua_isusertypearray(L, lo, type, -1, def, err);
}

/// Convert to Vector<T>. This function is not thread-safe.
template <typename T> void* ToluaToVector(lua_State* L, int narg, void* def)
{
    if (!lua_istable(L, narg))
        return 0;
    static Vector<T> result;
    result.Clear();
    result.Resize((unsigned)lua_objlen(L, narg));
    for (unsigned i = 0; i < result.Size(); ++i)
    {
        lua_rawgeti(L, narg, i + 1);    // Lua index starts from 1
        result[i] = *static_cast<T*>(tolua_tousertype(L, -1, def));
        lua_pop(L, 1);
    }
    return &result;
}

/// Push Vector<T> to Lua as a table.
template <typename T> int ToluaPushVector(lua_State* L, void* data, const char* type)
{
    lua_newtable(L);
    Vector<T>& vector = *static_cast<Vector<T>*>(data);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        tolua_pushusertype(L, &vector[i], type);
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

/// Check is PODVector<T>.
template <typename T> int ToluaIsPODVector(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
    // Whether it is POD or non-POD, on Lua side they are just usertype object, so we can reuse the same function
    return ToluaIsVector<T>(L, lo, type, def, err);
}

/// Check is PODVector<T, is_arithmetic<T>>. Use template function overload as non-type partial template specialization is not allowed.
template <typename T> int ToluaIsPODVector(double /*overload*/, lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isnumberarray(L, lo, -1, def, err);
}

/// Convert to PODVector<T>. This function is not thread-safe.
template <typename T> void* ToluaToPODVector(lua_State* L, int narg, void* def)
{
    return ToluaToVector<T>(L, narg, def);
}

/// Convert to PODVector<T, is_arithmetic<T>>. This function is not thread-safe. Use template function overload as non-type partial template specialization is not allowed.
template <typename T> void* ToluaToPODVector(double /*overload*/, lua_State* L, int narg, void* /*def*/)
{
    if (!lua_istable(L, narg))
        return 0;
    static PODVector<T> result;
    result.Clear();
    result.Resize((unsigned)lua_objlen(L, narg));
    for (unsigned i = 0; i < result.Size(); ++i)
    {
        lua_rawgeti(L, narg, i + 1);
        result[i] = (T)tolua_tonumber(L, -1, 0);
        lua_pop(L, 1);
    }
    return &result;
}

/// Push PODVector<T> to Lua as a table.
template <typename T> int ToluaPushPODVector(lua_State* L, void* data, const char* type)
{
    return ToluaPushVector<T>(L, data, type);
}

/// Push PODVector<T, is_pointer<T>> to Lua as a table. Use template function overload as non-type partial template specialization is not allowed.
template <typename T> int ToluaPushPODVector(const char* /*overload*/, lua_State* L, void* data, const char* type)
{
    lua_newtable(L);
    const PODVector<T>& vector = *static_cast<const PODVector<T>*>(data);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        tolua_pushusertype(L, vector[i], type);
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

/// Push PODVector<T, is_arithmetic<T>> to Lua as a table. Use template function overload as non-type partial template specialization is not allowed.
template <typename T> int ToluaPushPODVector(double /*overload*/, lua_State* L, void* data, const char* /*type*/)
{
    lua_newtable(L);
    const PODVector<T>& vector = *static_cast<const PODVector<T>*>(data);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        lua_pushnumber(L, vector[i]);
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

// GCC and Clang does not follow the C++ standard in expecting explicit template specialization shall be declared before first use,
//   both compilers are able to avoid the multiple definitions of template instantiation symbol during linking by using weak symbol
// MSVC and MinGW, however, follow the standard strictly, hence we need to declare all the explicit template specializations below
//   to keep these two compilers happy
// We do not use #ifdef MSVC/MINGW here because GCC and Clang are happy to comply with the C++ standard too

template <> int ToluaIsVector<String>(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
template <> void* ToluaToVector<String>(lua_State* L, int narg, void* def);
template <> int ToluaPushVector<String>(lua_State* L, void* data, const char* type);

template <> int ToluaIsPODVector<bool>(double /*overload*/, lua_State* L, int lo, const char* type, int def, tolua_Error* err);
template <> void* ToluaToPODVector<bool>(double /*overload*/, lua_State* L, int narg, void* def);
template <> int ToluaPushPODVector<bool>(double /*overload*/, lua_State* L, void* data, const char* type);

/// Convert object at the given index and store it in Variant. This function is not thread-safe.
void ToluaToVariant(lua_State* L, int narg, void* def, Variant& variant);

/// Push object stored in a Variant to stack. Empty variant value is pushed as nil.
void ToluaPushVariant(lua_State* L, const Variant* variant, const char* type = 0);

/// Push a registered Lua user type to stack. If the specified type is not yet registered, a nil is pushed instead.
void ToluaPushRegisteredUserType(lua_State* L, void* data, const char* type);

/// Push Object to Lua.
void ToluaPushObject(lua_State* L, void* data, const char* type);
