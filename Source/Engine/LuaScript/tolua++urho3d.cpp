//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Precompiled.h"
#include "Ptr.h"
#include "tolua++.h"
#include "tolua++urho3d.h"

const char* tolua_tourho3dstring(lua_State* L, int narg, const char* str)
{
    const char* s = tolua_tostring(L, narg, str);
    return s ? s : "";
}

const char* tolua_tourho3dstring(lua_State* L, int narg, const String& str)
{
    return tolua_tourho3dstring(L, narg, str.CString());
}

template<> int tolua_isurho3dvector<String>(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
    if (lua_istable(L, lo))
    {
        int length = lua_objlen(L, lo);
        for (int i = 1; i <= length; ++i)
        {
            lua_pushinteger(L, i);
            lua_gettable(L, lo);
            if (!lua_isstring(L, -1))
            {
                lua_pop(L, 1);

                err->index = lo;
                err->array = 0;
                err->type = type;

                return 0;
            }

            lua_pop(L, 1);
        }

        return 1;
    }

    err->index = lo;
    err->array = 0;
    err->type = type;
    return 0;
}

template<> void* tolua_tourho3dvector<String>(lua_State* L, int narg, void* def)
{
    if (!lua_istable(L, narg))
        return 0;

    static Vector<String> result;
    result.Clear();

    int length = lua_objlen(L, narg);
    for (int i = 1; i <= length; ++i)
    {
        lua_pushinteger(L, i);
        lua_gettable(L, narg);

        if (!lua_isstring(L, -1))
        {
            lua_pop(L, 1);
            return 0;
        }

        String string = tolua_tourho3dstring(L, -1, "");
        result.Push(string);

        lua_pop(L, 1);
    }

    return &result;
}

template<> int tolua_pushurho3dvector<String>(lua_State* L, void* data, const char* type)
{
    const Vector<String>& vectorstring = *((const Vector<String>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vectorstring.Size(); ++i)
    {
        tolua_pushurho3dstring(L, vectorstring[i]);
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

template<> int tolua_isurho3dpodvector<unsigned>(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
    if (lua_istable(L, lo))
    {
        int length = lua_objlen(L, lo);
        for (int i = 1; i <= length; ++i)
        {
            lua_pushinteger(L, i);
            lua_gettable(L, lo);
            if (!lua_isnumber(L, -1))
            {
                lua_pop(L, 1);

                err->index = lo;
                err->array = 0;
                err->type = type;

                return 0;
            }

            lua_pop(L, 1);
        }

        return 1;
    }

    err->index = lo;
    err->array = 0;
    err->type = type;
    return 0;
}

template<> void* tolua_tourho3dpodvector<unsigned>(lua_State* L, int narg, void* def)
{
    if (!lua_istable(L, narg))
        return 0;

    static Vector<unsigned> result;
    result.Clear();

    int length = lua_objlen(L, narg);
    for (int i = 1; i <= length; ++i)
    {
        lua_pushinteger(L, i);
        lua_gettable(L, narg);

        if (!lua_isnumber(L, -1))
        {
            lua_pop(L, 1);
            return 0;
        }

        unsigned value = (unsigned)tolua_tonumber(L, -1, 0);
        result.Push(value);

        lua_pop(L, 1);
    }

    return &result;
}

template<> int tolua_pushurho3dpodvector<int>(lua_State* L, void* data, const char* type)
{
    const PODVector<int>& vector = *((const PODVector<int>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        lua_pushinteger(L, vector[i]);
        lua_rawseti(L, -2, i + 1);
    }

    return 1;
}

template<> int tolua_pushurho3dpodvector<IntVector2>(lua_State* L, void* data, const char* type)
{
    const PODVector<IntVector2>& vector = *((const PODVector<IntVector2>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        void* tolua_obj = Mtolua_new((IntVector2)(vector[i]));
        tolua_pushusertype(L,tolua_obj,"IntVector2");
        tolua_register_gc(L,lua_gettop(L));

        lua_rawseti(L, -2, i + 1);
    }

    return 1;
}

template<> int tolua_pushurho3dpodvector<OctreeQueryResult>(lua_State* L, void* data, const char* type)
{
    const PODVector<OctreeQueryResult>& vector = *((const PODVector<OctreeQueryResult>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        void* tolua_obj = Mtolua_new((OctreeQueryResult)(vector[i]));
        tolua_pushusertype(L,tolua_obj,"OctreeQueryResult");
        tolua_register_gc(L,lua_gettop(L));

        lua_rawseti(L, -2, i + 1);
    }

    return 1;
}

template<> int tolua_pushurho3dpodvector<PhysicsRaycastResult>(lua_State* L, void* data, const char* type)
{
    const PODVector<PhysicsRaycastResult>& vector = *((const PODVector<PhysicsRaycastResult>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        void* tolua_obj = Mtolua_new((PhysicsRaycastResult)(vector[i]));
        tolua_pushusertype(L,tolua_obj,"PhysicsRaycastResult");
        tolua_register_gc(L,lua_gettop(L));

        lua_rawseti(L, -2, i + 1);
    }

    return 1;
}

template<> int tolua_pushurho3dpodvector<RayQueryResult>(lua_State* L, void* data, const char* type)
{
    const PODVector<RayQueryResult>& vector = *((const PODVector<RayQueryResult>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        void* tolua_obj = Mtolua_new((RayQueryResult)(vector[i]));
        tolua_pushusertype(L,tolua_obj,"RayQueryResult");
        tolua_register_gc(L,lua_gettop(L));

        lua_rawseti(L, -2, i + 1);
    }

    return 1;
}

template<> int tolua_pushurho3dpodvector<UIElement*>(lua_State* L, void* data, const char* type)
{
    const PODVector<UIElement*>& vector = *((const PODVector<UIElement*>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        tolua_pushusertype(L, vector[i], "UIElement");
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

template<> int tolua_pushurho3dpodvector<unsigned>(lua_State* L, void* data, const char* type)
{
    const PODVector<unsigned>& vector = *((const PODVector<unsigned>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        lua_pushinteger(L, vector[i]);
        lua_rawseti(L, -2, i + 1);
    }

    return 1;
}

template<typename T> int PushPODVector(lua_State* L, const PODVector<T>& vector, const char* type)
{
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        void* tolua_obj = Mtolua_new((T)(vector[i]));
        tolua_pushusertype(L, tolua_obj, type);
        tolua_register_gc(L, lua_gettop(L));
        lua_rawseti(L, -2, i + 1);
    }

    return 1;
}

template<> int tolua_pushurho3dpodvector<Vector3>(lua_State* L, void* data, const char* type)
{
    const PODVector<Vector3>& vector = *((const PODVector<Vector3>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        void* tolua_obj = Mtolua_new((Vector3)(vector[i]));
        tolua_pushusertype(L,tolua_obj,"Vector3");
        tolua_register_gc(L,lua_gettop(L));

        lua_rawseti(L, -2, i + 1);
    }

    return 1;
}