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

#include "../Core/Object.h"
#include "../Container/Ptr.h"

#include <toluapp/tolua++.h>
#include "../LuaScript/ToluaUtils.h"

const char* tolua_tourho3dstring(lua_State* L, int narg, const char* str)
{
    const char* s = tolua_tostring(L, narg, str);
    return s ? s : "";
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

template<> int ToluaIsVector<String>(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
    if (lua_istable(L, lo))
    {
        size_t length = lua_objlen(L, lo);
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

template<> void* ToluaToVector<String>(lua_State* L, int narg, void* def)
{
    if (!lua_istable(L, narg))
        return 0;

    static Vector<String> result;
    result.Clear();

    size_t length = lua_objlen(L, narg);
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

template<> int ToluaPushVector<String>(lua_State* L, void* data, const char* type)
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

template<> int ToluaPushVector<StringHash>(lua_State* L, void* data, const char* type)
{
    Vector<StringHash>& vector = *((Vector<StringHash>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        tolua_pushusertype(L, &vector[i], "StringHash");
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

template<> int ToluaIsPODVector<unsigned>(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
    if (lua_istable(L, lo))
    {
        size_t length = lua_objlen(L, lo);
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

template<> int ToluaIsPODVector<Vector2>(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
    if (lua_istable(L, lo))
    {
        size_t length = lua_objlen(L, lo);
        for (int i = 1; i <= length; ++i)
        {
            lua_pushinteger(L, i);
            lua_gettable(L, lo);
            if (!tolua_isusertype(L, -1, "Vector2", 0, err))
            {
                lua_pop(L, 1);
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

template<> void* ToluaToPODVector<unsigned>(lua_State* L, int narg, void* def)
{
    if (!lua_istable(L, narg))
        return 0;

    static PODVector<unsigned> result;
    result.Clear();

    size_t length = lua_objlen(L, narg);
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

template<> void* ToluaToPODVector<Vector2>(lua_State* L, int narg, void* def)
{
    if (!lua_istable(L, narg))
        return 0;

    static PODVector<Vector2> result;
    result.Clear();

    tolua_Error tolua_err;

    size_t length = lua_objlen(L, narg);
    for (int i = 1; i <= length; ++i)
    {
        lua_pushinteger(L, i);
        lua_gettable(L, narg);

        if (!tolua_isusertype(L, -1, "Vector2", 0, &tolua_err))
        {
            lua_pop(L, 1);
            return 0;
        }

        Vector2* value = (Vector2*)tolua_touserdata(L, -1, 0);
        result.Push(*value);

        lua_pop(L, 1);
    }

    return &result;
}

template<> int ToluaPushPODVector<int>(lua_State* L, void* data, const char*)
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

template<> int ToluaPushPODVector<unsigned>(lua_State* L, void* data, const char*)
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

template<> int ToluaPushPODVector<Component*>(lua_State* L, void* data, const char*)
{
    const PODVector<Component*>& vector = *((const PODVector<Component*>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        tolua_pushusertype(L, vector[i], "Component");
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

template<> int ToluaPushPODVector<Node*>(lua_State* L, void* data, const char*)
{
    const PODVector<Node*>& vector = *((const PODVector<Node*>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        tolua_pushusertype(L, vector[i], "Node");
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

template<> int ToluaPushPODVector<SoundSource*>(lua_State* L, void* data, const char*)
{
    const PODVector<SoundSource*>& vector = *((const PODVector<SoundSource*>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        tolua_pushusertype(L, vector[i], "SoundSource");
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

template<> int ToluaPushPODVector<UIElement*>(lua_State* L, void* data, const char*)
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

#ifdef URHO3D_NAVIGATION
template<> int ToluaPushPODVector<CrowdAgent*>(lua_State* L, void* data, const char*)
{
    const PODVector<CrowdAgent*>& vector = *((const PODVector<CrowdAgent*>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        tolua_pushusertype(L, vector[i], "CrowdAgent");
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}
#endif

#ifdef URHO3D_PHYSICS
template<> int ToluaPushPODVector<RigidBody*>(lua_State* L, void* data, const char*)
{
    const PODVector<RigidBody*>& vector = *((const PODVector<RigidBody*>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        tolua_pushusertype(L, vector[i], "RigidBody");
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}
#endif

#ifdef URHO3D_URHO2D
template<> int ToluaPushPODVector<RigidBody2D*>(lua_State* L, void* data, const char*)
{
    const PODVector<RigidBody2D*>& vector = *((const PODVector<RigidBody2D*>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        tolua_pushusertype(L, vector[i], "RigidBody2D");
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}
#endif

template<typename T> int tolua_pushurho3dpodvectorusertype(lua_State* L, const PODVector<T>& vector, const char* typeName)
{
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        void* tolua_obj = Mtolua_new((T)(vector[i]));
        tolua_pushusertype(L, tolua_obj, typeName);
        tolua_register_gc(L,lua_gettop(L));

        lua_rawseti(L, -2, i + 1);
    }

    return 1;
}

template<> int ToluaPushPODVector<Vector3>(lua_State* L, void* data, const char*)
{
    return tolua_pushurho3dpodvectorusertype(L, *((const PODVector<Vector3>*)data), "Vector3");
}

template<> int ToluaPushPODVector<IntVector2>(lua_State* L, void* data, const char*)
{
    return tolua_pushurho3dpodvectorusertype(L, *((const PODVector<IntVector2>*)data), "IntVector2");
}

template<> int ToluaPushPODVector<OctreeQueryResult>(lua_State* L, void* data, const char*)
{
    return tolua_pushurho3dpodvectorusertype(L, *((const PODVector<OctreeQueryResult>*)data), "OctreeQueryResult");
}

#ifdef URHO3D_PHYSICS
template<> int ToluaPushPODVector<PhysicsRaycastResult>(lua_State* L, void* data, const char*)
{
    return tolua_pushurho3dpodvectorusertype(L, *((const PODVector<PhysicsRaycastResult>*)data), "PhysicsRaycastResult");
}
#endif

#ifdef URHO3D_URHO2D
template<> int ToluaPushPODVector<PhysicsRaycastResult2D>(lua_State* L, void* data, const char*)
{
    return tolua_pushurho3dpodvectorusertype(L, *((const PODVector<PhysicsRaycastResult2D>*)data), "PhysicsRaycastResult2D");
}
#endif

template<> int ToluaPushPODVector<RayQueryResult>(lua_State* L, void* data, const char*)
{
    return tolua_pushurho3dpodvectorusertype(L, *((const PODVector<RayQueryResult>*)data), "RayQueryResult");
}

template<> int ToluaPushPODVector<Pass*>(lua_State* L, void* data, const char*)
{
    const PODVector<Pass*>& vector = *((const PODVector<Pass*>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vector.Size(); ++i)
    {
        tolua_pushusertype(L, vector[i], "Pass");
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

void ToluaPushObject(lua_State*L, void* data, const char* type)
{
    tolua_pushusertype(L, data, data ? static_cast<Object*>(data)->GetTypeName().CString() : type);
}
