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
#include "ToluaUrho3DEx.h"

const char* tolua_tourho3dstring(lua_State* L, int narg, const char* def)
{
    const char* s = tolua_tostring(L, narg, def);
    return s?s:"";
}

const char* tolua_tourho3dstring(lua_State* L, int narg, const String& def)
{
    return tolua_tourho3dstring(L, narg, def.CString());
}

int tolua_isurho3dconstvectorstring(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
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

void* tolua_tourho3dconstvectorstring(lua_State* L, int narg, void* def)
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

int tolua_pushurho3dconstvectorstring(lua_State*L, void* data, const char* type)
{
#ifndef TOLUA_RELEASE
    assert(strcmp(type, "const Vector<String>") == 0);
#endif

    const Vector<String>& vectorstring = *((const Vector<String>*)data);
    lua_newtable(L);
    for (unsigned i = 0; i < vectorstring.Size(); ++i)
    {
        tolua_pushurho3dstring(L, vectorstring[i]);
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}
