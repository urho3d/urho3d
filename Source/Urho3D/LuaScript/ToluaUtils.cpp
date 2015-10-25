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

#include "../IO/VectorBuffer.h"

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

void SetContext(lua_State* L, Context* context)
{
    assert(L && context);
    tolua_pushusertype(L, static_cast<void*>(context), "Context");
    lua_setglobal(L, ".context");   // This property is internal, the exposed 'context' property is obtained via GetContext() call
}

Context* GetContext(lua_State* L)
{
    lua_getglobal(L, ".context");
    if (lua_isnil(L, -1))
    {
        lua_State* L1 = lua_getmainthread(L);
        return (L == L1) ? 0 : GetContext(L1);
    }
    tolua_Error error;      // Ensure we are indeed getting a Context object before casting
    return tolua_isusertype(L, -1, "Context", 0, &error) ? static_cast<Context*>(tolua_tousertype(L, -1, 0)) : 0;
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

// Explicit template specialization only required for boolean

template <> int ToluaIsPODVector<bool>(double /*overload*/, lua_State* L, int lo, const char* /*type*/, int def, tolua_Error* err)
{
    return tolua_isbooleanarray(L, lo, -1, def, err);
}

template <> void* ToluaToPODVector<bool>(double /*overload*/, lua_State* L, int narg, void* /*def*/)
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

template <> int ToluaPushPODVector<bool>(double /*overload*/, lua_State* L, void* data, const char* /*type*/)
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

namespace Urho3D
{

template <> const VariantValue* Variant::Get<const VariantValue*>() const
{
    return &value_;
}

}

void ToluaToVariant(lua_State* L, int narg, void* def, Variant& variant)
{
    switch (lua_type(L, narg))   // Use the type of lua object to determine the final variant type
    {
    case LUA_TNIL:
        variant = Variant::EMPTY;
        break;

    case LUA_TBOOLEAN:
        variant = (bool)lua_toboolean(L, narg);     // Still need to cast to bool as Lua/LuaJIT return it as int
        break;

    case LUA_TNUMBER:
        {
            // Use the original variant type to further determine the final variant type
            // CAVEAT: if lhs has integral data type and double is desired then lhs needs to be reset first before assigning
            double value = lua_tonumber(L, narg);
            switch (variant.GetType())
            {
            case VAR_INT:
                variant = (int)value;
                break;

            case VAR_BOOL:
                variant = value != 0.0f;
                break;

            case VAR_FLOAT:
                variant = (float)value;
                break;

            default:
                variant = value;
            }
        }
        break;

    case LUA_TSTRING:
        variant = lua_tostring(L, narg);
        break;

    case LUA_TUSERDATA:
        {
            if (lua_getmetatable(L, narg))
            {
                lua_rawget(L, LUA_REGISTRYINDEX);     // registry[mt]
                const char* typeName = lua_tostring(L, -1);
                lua_pop(L, 1);

                void* value = tolua_tousertype(L, narg, def);
                switch (Variant::GetTypeFromName(typeName))
                {
                case VAR_NONE:
                    // Handle special cases
                    if (typeName)
                    {
                        tolua_Error error;
                        if (strcmp(typeName, "Variant") == 0)
                            variant = *static_cast<Variant*>(value);
                        else if (strcmp(typeName, "VectorBuffer") == 0)
                            variant = *static_cast<VectorBuffer*>(value);
                        else if (tolua_isusertype(L, narg, "RefCounted", 0, &error))
                            variant = static_cast<RefCounted*>(value);
                        else
                            variant = value;    // void*
                    }
                    break;

                case VAR_VECTOR2:
                    variant = *static_cast<Vector2*>(value);
                    break;

                case VAR_VECTOR3:
                    variant = *static_cast<Vector3*>(value);
                    break;

                case VAR_VECTOR4:
                    variant = *static_cast<Vector4*>(value);
                    break;

                case VAR_QUATERNION:
                    variant = *static_cast<Quaternion*>(value);
                    break;

                case VAR_COLOR:
                    variant = *static_cast<Color*>(value);
                    break;

                case VAR_INTRECT:
                    variant = *static_cast<IntRect*>(value);
                    break;

                case VAR_INTVECTOR2:
                    variant = *static_cast<IntVector2*>(value);
                    break;

                case VAR_MATRIX3:
                    variant = *static_cast<Matrix3*>(value);
                    break;

                case VAR_MATRIX3X4:
                    variant = *static_cast<Matrix3x4*>(value);
                    break;

                case VAR_MATRIX4:
                    variant = *static_cast<Matrix4*>(value);
                    break;

                case VAR_RESOURCEREF:
                    variant = *static_cast<ResourceRef*>(value);
                    break;

                case VAR_RESOURCEREFLIST:
                    variant = *static_cast<ResourceRefList*>(value);
                    break;

                case VAR_VARIANTMAP:
                    variant = *static_cast<VariantMap*>(value);
                    break;

                default: break;
                }
            };
        }
        break;

    case LUA_TTABLE:
        {
            tolua_Error error;
            if (ToluaIsPODVector<unsigned char>(0.f, L, narg, "unsigned char", 0, &error))
                variant = *static_cast<PODVector<unsigned char>*>(ToluaToPODVector<unsigned char>(0.f, L, narg, def));
            else if (ToluaIsVector<Variant>(L, narg, "Variant", 0, &error))
                variant = *static_cast<VariantVector*>(ToluaToVector<Variant>(L, narg, def));
            else if (ToluaIsVector<String>(L, narg, "String", 0, &error))
                variant = *static_cast<StringVector*>(ToluaToVector<String>(L, narg, def));
        }
        break;

    default: break;
    }
}

void ToluaPushVariant(lua_State* L, const Variant* variant, const char* type)
{
    String typeName(type);
    switch (variant->GetType())
    {
    case VAR_INT:
        if (typeName == "unsigned" || typeName == "unsigned int" || typeName == "UInt" || typeName == "uint")
            tolua_pushnumber(L, (lua_Number)variant->GetUInt());
        else if (typeName == "StringHash")
        {
            // Make a new local copy
            tolua_pushusertype(L, Mtolua_new(StringHash(variant->GetStringHash())), "StringHash");
            tolua_register_gc(L, lua_gettop(L));
        }
        else
            tolua_pushnumber(L, (lua_Number)variant->GetInt());
        break;

    case VAR_BOOL:
        tolua_pushboolean(L, (int)variant->GetBool());
        break;

    case VAR_FLOAT:
        tolua_pushnumber(L, (lua_Number)variant->GetFloat());
        break;

    case VAR_DOUBLE:
        tolua_pushnumber(L, (lua_Number)variant->GetDouble());
        break;

    case VAR_VECTOR2:
    case VAR_VECTOR3:
    case VAR_VECTOR4:
    case VAR_QUATERNION:
    case VAR_COLOR:
    case VAR_RESOURCEREF:
    case VAR_RESOURCEREFLIST:
    case VAR_VARIANTMAP:
    case VAR_INTRECT:
    case VAR_INTVECTOR2:
        tolua_pushusertype(L, (void*)variant->Get<const VariantValue*>(), variant->GetTypeName().CString());
        break;

    case VAR_STRING:
        tolua_pushurho3dstring(L, variant->GetString());
        break;

    case VAR_BUFFER:
        if (typeName == "VectorBuffer")
        {
            tolua_pushusertype(L, Mtolua_new(VectorBuffer(variant->GetVectorBuffer())), "VectorBuffer");
            tolua_register_gc(L, lua_gettop(L));
        }
        else
            ToluaPushPODVector<unsigned char>(0.f, L, (void*)&variant->GetBuffer(), "unsigned char");
        break;

    case VAR_VOIDPTR:
        ToluaPushRegisteredUserType(L, static_cast<void*>(variant->GetVoidPtr()), type);
        break;

    case VAR_PTR:
        ToluaPushRegisteredUserType(L, static_cast<void*>(variant->GetPtr()), type);
        break;

    case VAR_VARIANTVECTOR:
        ToluaPushVector<Variant>(L, (void*)&variant->GetVariantVector(), "Variant");
        break;

    case VAR_STRINGVECTOR:
        ToluaPushVector<String>(L, (void*)&variant->GetStringVector(), "String");
        break;

    case VAR_MATRIX3:
    case VAR_MATRIX3X4:
    case VAR_MATRIX4:
        tolua_pushusertype(L, variant->Get<const VariantValue*>()->ptr_, variant->GetTypeName().CString());
        break;

    default:
        lua_pushnil(L);
        break;
    }
}

void ToluaPushRegisteredUserType(lua_State* L, void* data, const char* type)
{
    if (type)
    {
        luaL_getmetatable(L, type);
        if (!lua_isnil(L, -1))
        {
            lua_pop(L, 1);
            tolua_pushusertype(L, data, type);
        }
    }
    else
        lua_pushnil(L);
}

void ToluaPushObject(lua_State* L, void* data, const char* type)
{
    tolua_pushusertype(L, data, data ? static_cast<Object*>(data)->GetTypeName().CString() : type);
}
