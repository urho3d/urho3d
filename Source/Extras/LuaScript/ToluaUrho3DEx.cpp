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
#include "Log.h"
#include "ToluaUrho3DEx.h"

const char* tolua_tourho3dstring(lua_State* L, int narg, const char* def)
{
    const char* s = tolua_tostring(L, narg, def);
    return s?s:"";
}

const char* tolua_tourho3dstring(lua_State* L, int narg, const Urho3D::String& def)
{
    return tolua_tourho3dstring(L, narg, def.CString());
}

int tolua_pushurho3dstringvector(lua_State* L, const Urho3D::Vector<Urho3D::String>& strings)
{
    lua_newtable(L);
    for (unsigned i = 0; i < strings.Size(); ++i)
    {
        tolua_pushurho3dstring(L, strings[i]);
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

bool tolua_pushurho3dvariantvector(lua_State* L, const Urho3D::VariantVector& variants)
{
    using namespace Urho3D;
    for (unsigned i = 0; i < variants.Size(); ++i)
    {
        switch (variants[i].GetType())
        {
        case VAR_INT:
            tolua_pushnumber(L, (double)variants[i].GetInt());
            break;

        case VAR_BOOL:
            tolua_pushboolean(L, variants[i].GetBool() ? 1 : 0);
            break;

        case VAR_FLOAT:
            tolua_pushnumber(L, variants[i].GetFloat());
            break;

        case VAR_VECTOR2:
            tolua_pushusertype(L, &const_cast<Vector2&>(variants[i].GetVector2()), variants[i].GetTypeName().CString());
            break;

        case VAR_VECTOR3:
            tolua_pushusertype(L, &const_cast<Vector3&>(variants[i].GetVector3()), variants[i].GetTypeName().CString());
            break;

        case VAR_VECTOR4:
            tolua_pushusertype(L, &const_cast<Vector4&>(variants[i].GetVector4()), variants[i].GetTypeName().CString());
            break;

        case VAR_QUATERNION:
            tolua_pushusertype(L, &const_cast<Quaternion&>(variants[i].GetQuaternion()), variants[i].GetTypeName().CString());
            break;

        case VAR_COLOR:
            tolua_pushusertype(L, &const_cast<Color&>(variants[i].GetColor()), variants[i].GetTypeName().CString());
            break;
        
        case VAR_STRING:
            tolua_pushurho3dstring(L, variants[i].GetString());
            break;

        case VAR_INTRECT:
            tolua_pushusertype(L, &const_cast<IntRect&>(variants[i].GetIntRect()), variants[i].GetTypeName().CString());
            break;

        case VAR_INTVECTOR2:
            tolua_pushusertype(L, &const_cast<IntVector2&>(variants[i].GetIntVector2()), variants[i].GetTypeName().CString());
            break;

        default:
            LOGERROR("Unsupported data type");
            return false;
        }
    }

    return true;
}
