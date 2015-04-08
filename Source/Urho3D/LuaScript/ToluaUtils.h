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

#include "../Core/Context.h"
#include "../Graphics/OctreeQuery.h"
#ifdef URHO3D_PHYSICS
#include "../Physics/PhysicsWorld.h"
#endif
#ifdef URHO3D_URHO2D
#include "../Urho2D/PhysicsWorld2D.h"
#endif
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"

struct lua_State;

namespace Urho3D
{
class Context;
class Pass;
class SoundSource;
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

/// Set context.
void SetContext(lua_State* L, Context* context);
/// Return context.
Context* GetContext(lua_State* L);

/// Create object.
template<typename T> int ToluaNewObject(lua_State* tolua_S)
{
    T* object = Mtolua_new(T(GetContext(tolua_S)));
    tolua_pushusertype(tolua_S, (void*)object,T::GetTypeNameStatic().CString());
    return 1;
}
/// Create object with garbage collection.
template<typename T> int ToluaNewObjectGC(lua_State* tolua_S)
{
    T* object = Mtolua_new(T(GetContext(tolua_S)));
    tolua_pushusertype(tolua_S, (void*)object,T::GetTypeNameStatic().CString());
    tolua_register_gc(tolua_S, lua_gettop(tolua_S));
    return 1;
}

/// Return subsystem.
template<typename T> int ToluaGetSubsystem(lua_State* tolua_S)
{
    T* subsystem = GetContext(tolua_S)->GetSubsystem<T>();
    tolua_pushusertype(tolua_S, (void*)subsystem, T::GetTypeNameStatic().CString());
    return 1;
}

/// Check is Vector<T>.
template<typename T> int ToluaIsVector(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
/// Check is Vector<String>.
template<> int ToluaIsVector<String>(lua_State* L, int lo, const char* type, int def, tolua_Error* err);

/// Convert to Vector<T>.
template<typename T> void* ToluaToVector(lua_State* L, int narg, void* def);
/// Convert to Vector<String>.
template<> void* ToluaToVector<String>(lua_State* L, int narg, void* def);

/// Push Vector<T> to Lua as a table.
template<typename T> int ToluaPushVector(lua_State*L, void* data, const char* type);
/// Push Vector<String> to Lua as a table.
template<> int ToluaPushVector<String>(lua_State* L, void* data, const char* type);
/// Push Vector<StringHash> to Lua as a table.
template<> int ToluaPushVector<StringHash>(lua_State* L, void* data, const char* type);

/// Check is PODVector<T>.
template<typename T> int ToluaIsPODVector(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
/// Check is PODVector<unsigned>.
template<> int ToluaIsPODVector<unsigned>(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
/// Check is PODVector<Vector2>.
template<> int ToluaIsPODVector<Vector2>(lua_State* L, int lo, const char* type, int def, tolua_Error* err);

/// Convert to PODVector<T>.
template<typename T> void* ToluaToPODVector(lua_State* L, int narg, void* def);
/// Convert PODVector<unsigned>.
template<> void* ToluaToPODVector<unsigned>(lua_State* L, int narg, void* def);
/// Convert PODVector<Vector2>.
template<> void* ToluaToPODVector<Vector2>(lua_State* L, int narg, void* def);

/// Push PODVector<T> to Lua as a table.
template<typename T> int ToluaPushPODVector(lua_State* L, void* data, const char* type);
/// Push PODVector<int> to Lua as a table.
template<> int ToluaPushPODVector<int>(lua_State* L, void* data, const char* type);
/// Push PODVector<unsigned> to Lua as a table.
template<> int ToluaPushPODVector<unsigned>(lua_State* L, void* data, const char* type);
/// Push PODVector<SoundSource*> to Lua as a table.
template<> int ToluaPushPODVector<SoundSource*>(lua_State* L, void* data, const char* type);
/// Push PODVector<UIElement*> to Lua as a table.
template<> int ToluaPushPODVector<UIElement*>(lua_State* L, void* data, const char* type);
#ifdef URHO3D_PHYSICS
/// Push PODVector<RigidBody*> to Lua as a table.
template<> int ToluaPushPODVector<RigidBody*>(lua_State* L, void* data, const char* type);
#endif
#ifdef URHO3D_URHO2D
/// Push PODVector<RigidBody2D*> to Lua as a table.
template<> int ToluaPushPODVector<RigidBody2D*>(lua_State* L, void* data, const char* type);
#endif
/// Push PODVector<Vector3> to Lua as a table.
template<> int ToluaPushPODVector<Vector3>(lua_State* L, void* data, const char* type);
/// Push PODVector<IntVector2> to Lua as a table.
template<> int ToluaPushPODVector<IntVector2>(lua_State* L, void* data, const char* type);
/// Push PODVector<OctreeQueryResult> to Lua as a table.
template<> int ToluaPushPODVector<OctreeQueryResult>(lua_State* L, void* data, const char* type);
#ifdef URHO3D_PHYSICS
/// Push PODVector<PhysicsRaycastResult> to Lua as a table.
template<> int ToluaPushPODVector<PhysicsRaycastResult>(lua_State* L, void* data, const char* type);
#endif
#ifdef URHO3D_URHO2D
/// Push PODVector<PhysicsRaycastResult2D> to Lua as a table.
template<> int ToluaPushPODVector<PhysicsRaycastResult2D>(lua_State* L, void* data, const char* type);
#endif
/// Push PODVector<RayQueryResult> to Lua as a table.
template<> int ToluaPushPODVector<RayQueryResult>(lua_State* L, void* data, const char* type);
/// Push PODVector<Pass*> to Lua as a table.
template<> int ToluaPushPODVector<Pass*>(lua_State* L, void* data, const char* type);
/// Push Object to Lua.
void ToluaPushObject(lua_State*L, void* data, const char* type);

