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

#include "../Precompiled.h"

#include <toluapp/tolua++.h>

#include "../LuaScript/ToluaUtils.h"

const char* tolua_tourho3dstring(lua_State* L, int narg, const char* str)
{
    return tolua_tostring(L, narg, str);
}

const char* tolua_tourho3dstring(lua_State* L, int narg, const String& str)
{
    return tolua_tourho3dstring(L, narg, str.CString());
}

// Lua state to context mapping
static HashMap<void*, Context*> contextMapping;

void SetContext(lua_State* L, Context* context)
{
    if (context == 0)
        contextMapping.Erase(L);
    else
        contextMapping[L] = context;
}

Context* GetContext(lua_State* L)
{
    HashMap<void*, Context*>::ConstIterator i = contextMapping.Find(L);
    if (i == contextMapping.End())
    {
        lua_State* L1 = lua_getmainthread(L);
        return (L == L1) ? 0 : GetContext(L1);
    }

    return i->second_;
}

// Explicit template specialization only required for StringVector

template <> int ToluaIsVector<String>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isstringarray(L, lo, -1, def, err);
}

template <> void* ToluaToVector<String>(lua_State* L, int narg, void* /*def*/)
{
    if (!lua_istable(L, narg))
        return 0;
    static Vector<String> result;
    result.Clear();
    result.Resize((unsigned)lua_objlen(L, narg));
    for (unsigned i = 0; i < result.Size(); ++i)
    {
        lua_rawgeti(L, narg, i + 1);
        result[i] = tolua_tourho3dstring(L, -1, "");
        lua_pop(L, 1);
    }
    return &result;
}

template <> int ToluaPushVector<String>(lua_State* L, void* data, const char* /*type*/)
{
    lua_newtable(L);
    const Vector<String>& vector = *static_cast<const Vector<String>*>(data);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        tolua_pushurho3dstring(L, vector[i]);
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

// Explicit template specialization only required for Lua number and boolean types

template <> int ToluaIsPODVector<char>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isnumberarray(L, lo, -1, def, err);
}

template <> int ToluaIsPODVector<unsigned char>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isnumberarray(L, lo, -1, def, err);
}

template <> int ToluaIsPODVector<short>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isnumberarray(L, lo, -1, def, err);
}

template <> int ToluaIsPODVector<unsigned short>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isnumberarray(L, lo, -1, def, err);
}

template <> int ToluaIsPODVector<int>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isnumberarray(L, lo, -1, def, err);
}

template <> int ToluaIsPODVector<unsigned>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isnumberarray(L, lo, -1, def, err);
}

template <> int ToluaIsPODVector<long>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isnumberarray(L, lo, -1, def, err);
}

template <> int ToluaIsPODVector<unsigned long>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isnumberarray(L, lo, -1, def, err);
}

template <> int ToluaIsPODVector<long long>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isnumberarray(L, lo, -1, def, err);
}

template <> int ToluaIsPODVector<unsigned long long>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isnumberarray(L, lo, -1, def, err);
}

template <> int ToluaIsPODVector<float>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isnumberarray(L, lo, -1, def, err);
}

template <> int ToluaIsPODVector<double>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isnumberarray(L, lo, -1, def, err);
}

template <> int ToluaIsPODVector<bool>(lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isbooleanarray(L, lo, -1, def, err);
}

template <typename T> void* ToluaToNumberVector(lua_State* L, int narg, void* def)
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

void* ToluaToBooleanVector(lua_State* L, int narg, void* def)
{
    if (!lua_istable(L, narg))
        return 0;
    static PODVector<bool> result;
    result.Clear();
    result.Resize((unsigned)lua_objlen(L, narg));
    for (unsigned i = 0; i < result.Size(); ++i)
    {
        lua_rawgeti(L, narg, i + 1);
        result[i] = (bool)tolua_toboolean(L, -1, 0);
        lua_pop(L, 1);
    }
    return &result;
}

template <> void* ToluaToPODVector<char>(lua_State* L, int narg, void* def)
{
    return ToluaToNumberVector<char>(L, narg, def);
}

template <> void* ToluaToPODVector<unsigned char>(lua_State* L, int narg, void* def)
{
    return ToluaToNumberVector<unsigned char>(L, narg, def);
}

template <> void* ToluaToPODVector<short>(lua_State* L, int narg, void* def)
{
    return ToluaToNumberVector<short>(L, narg, def);
}

template <> void* ToluaToPODVector<unsigned short>(lua_State* L, int narg, void* def)
{
    return ToluaToNumberVector<unsigned short>(L, narg, def);
}

template <> void* ToluaToPODVector<int>(lua_State* L, int narg, void* def)
{
    return ToluaToNumberVector<int>(L, narg, def);
}

template <> void* ToluaToPODVector<unsigned>(lua_State* L, int narg, void* def)
{
    return ToluaToNumberVector<unsigned>(L, narg, def);
}

template <> void* ToluaToPODVector<long>(lua_State* L, int narg, void* def)
{
    return ToluaToNumberVector<long>(L, narg, def);
}

template <> void* ToluaToPODVector<unsigned long>(lua_State* L, int narg, void* def)
{
    return ToluaToNumberVector<unsigned long>(L, narg, def);
}

template <> void* ToluaToPODVector<float>(lua_State* L, int narg, void* def)
{
    return ToluaToNumberVector<float>(L, narg, def);
}

template <> void* ToluaToPODVector<double>(lua_State* L, int narg, void* def)
{
    return ToluaToNumberVector<double>(L, narg, def);
}

template <> void* ToluaToPODVector<bool>(lua_State* L, int narg, void* def)
{
    return ToluaToBooleanVector(L, narg, def);
}

template <typename T> int ToluaPushNumberVector(lua_State* L, void* data, const char* /*type*/)
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

int ToluaPushBooleanVector(lua_State* L, void* data, const char* /*type*/)
{
    lua_newtable(L);
    const PODVector<bool>& vector = *static_cast<const PODVector<bool>*>(data);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        lua_pushboolean(L, vector[i]);
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

template <> int ToluaPushPODVector<char>(lua_State* L, void* data, const char* type)
{
    return ToluaPushNumberVector<char>(L, data, type);
}

template <> int ToluaPushPODVector<unsigned char>(lua_State* L, void* data, const char* type)
{
    return ToluaPushNumberVector<unsigned char>(L, data, type);
}

template <> int ToluaPushPODVector<short>(lua_State* L, void* data, const char* type)
{
    return ToluaPushNumberVector<short>(L, data, type);
}

template <> int ToluaPushPODVector<unsigned short>(lua_State* L, void* data, const char* type)
{
    return ToluaPushNumberVector<unsigned short>(L, data, type);
}

template <> int ToluaPushPODVector<int>(lua_State* L, void* data, const char* type)
{
    return ToluaPushNumberVector<int>(L, data, type);
}

template <> int ToluaPushPODVector<unsigned>(lua_State* L, void* data, const char* type)
{
    return ToluaPushNumberVector<unsigned>(L, data, type);
}

template <> int ToluaPushPODVector<long>(lua_State* L, void* data, const char* type)
{
    return ToluaPushNumberVector<long>(L, data, type);
}

template <> int ToluaPushPODVector<unsigned long>(lua_State* L, void* data, const char* type)
{
    return ToluaPushNumberVector<unsigned long>(L, data, type);
}

template <> int ToluaPushPODVector<float>(lua_State* L, void* data, const char* type)
{
    return ToluaPushNumberVector<float>(L, data, type);
}

template <> int ToluaPushPODVector<double>(lua_State* L, void* data, const char* type)
{
    return ToluaPushNumberVector<double>(L, data, type);
}

template <> int ToluaPushPODVector<bool>(lua_State* L, void* data, const char* type)
{
    return ToluaPushBooleanVector(L, data, type);
}

void ToluaPushObject(lua_State* L, void* data, const char* type)
{
    tolua_pushusertype(L, data, data ? static_cast<Object*>(data)->GetTypeName().CString() : type);
}
