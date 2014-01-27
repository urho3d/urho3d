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

#pragma once

#include "OctreeQuery.h"
#include "PhysicsWorld.h"
#include "Vector2.h"
#include "Vector3.h"

struct lua_State;

namespace Urho3D
{
    class UIElement;
}

using namespace Urho3D;

/// Check is String.
#define tolua_isurho3dstring tolua_isstring
/// Push String.
#define tolua_pushurho3dstring(x, y) tolua_pushstring(x, y.CString())
/// Convert to String.
const char* tolua_tourho3dstring(lua_State* L, int narg, const char* str);
/// Convert to String.
const char* tolua_tourho3dstring(lua_State* L, int narg, const String& str);

/// Check Lua table is Vector<T>.
template<typename T> int tolua_isurho3dvector(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
/// Check Lua table is Vector<String>.
template<> int tolua_isurho3dvector<String>(lua_State* L, int lo, const char* type, int def, tolua_Error* err);

/// Convert Lua  table to Vector<T>.
template<typename T> void* tolua_tourho3dvector(lua_State* L, int narg, void* def);
/// Convert Lua  table to Vector<String>.
template<> void* tolua_tourho3dvector<String>(lua_State* L, int narg, void* def);

/// Push Vector<T> to Lua as a table.
template<typename T> int tolua_pushurho3dvector(lua_State*L, void* data, const char* type);
/// Push Vector<String> to Lua as a table.
template<> int tolua_pushurho3dvector<String>(lua_State* L, void* data, const char* type);

/// Check Lua table is Vector<T>.
template<typename T> int tolua_isurho3dpodvector(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
/// Check Lua table is Vector<unsigned>.
template<> int tolua_isurho3dpodvector<unsigned>(lua_State* L, int lo, const char* type, int def, tolua_Error* err);

/// Convert Lua  table to PODVector<T>.
template<typename T> void* tolua_tourho3dpodvector(lua_State* L, int narg, void* def);
/// Convert Lua  table to PODVector<unsigned>.
template<> void* tolua_tourho3dpodvector<unsigned>(lua_State* L, int narg, void* def);

/// Push PODVector<T> to Lua as a table.
template<typename T> int tolua_pushurho3dpodvector(lua_State* L, void* data, const char* type);
/// Push PODVector<int> to Lua as a table.
template<> int tolua_pushurho3dpodvector<int>(lua_State* L, void* data, const char* type);
/// Push PODVector<unsigned> to Lua as a table.
template<> int tolua_pushurho3dpodvector<unsigned>(lua_State* L, void* data, const char* type);
/// Push PODVector<UIElement*> to Lua as a table.
template<> int tolua_pushurho3dpodvector<UIElement*>(lua_State* L, void* data, const char* type);
/// Push PODVector<Vector3> to Lua as a table.
template<> int tolua_pushurho3dpodvector<Vector3>(lua_State* L, void* data, const char* type);
/// Push PODVector<IntVector2> to Lua as a table.
template<> int tolua_pushurho3dpodvector<IntVector2>(lua_State* L, void* data, const char* type);
/// Push PODVector<OctreeQueryResult> to Lua as a table.
template<> int tolua_pushurho3dpodvector<OctreeQueryResult>(lua_State* L, void* data, const char* type);
/// Push PODVector<PhysicsRaycastResult> to Lua as a table.
template<> int tolua_pushurho3dpodvector<PhysicsRaycastResult>(lua_State* L, void* data, const char* type);
/// Push PODVector<RayQueryResult> to Lua as a table.
template<> int tolua_pushurho3dpodvector<RayQueryResult>(lua_State* L, void* data, const char* type);
