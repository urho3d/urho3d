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
#include "Context.h"
#include "Log.h"
#include "LuaScript.h"
#include "LuaScriptInstance.h"
#include "ResourceCache.h"
#include "ProcessUtils.h"

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include "tolua++.h"

namespace Urho3D
{

LuaScriptInstance::LuaScriptInstance(Context* context) : Component(context)
{
    
}

LuaScriptInstance::~LuaScriptInstance()
{
    if (objectType_.Empty())
        return;

    LuaScript* luaScript = GetSubsystem<LuaScript>();
    lua_State* luaState = luaScript->GetLuaState();

    int top = lua_gettop(luaState);

    lua_getglobal(luaState, "DestroyScriptObjectInstance");
    if (!lua_isfunction(luaState, -1))
    {
        LOGERROR("Can not find lua function DestroyScriptObjectInstance.");
        lua_settop(luaState, top);
        return;
    }

    // Push this as second parameter.
    tolua_pushusertype(luaState, (void*)this, "LuaScriptInstance");

    // Call ObjectType:new function.
    if (lua_pcall(luaState, 1, 0, 0) != 0)
    {
        const char* message = lua_tostring(luaState, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState, top);
        return;
    }
}

void LuaScriptInstance::RegisterObject(Context* context)
{
    context->RegisterFactory<LuaScriptInstance>();
}

bool LuaScriptInstance::CreateObject(const String& objectType)
{
    if (objectType_ == objectType)
        return true;

    LuaScript* luaScript = GetSubsystem<LuaScript>();
    lua_State* luaState = luaScript->GetLuaState();

    int top = lua_gettop(luaState);

    lua_getglobal(luaState, "CreateScriptObjectInstance");
    if (!lua_isfunction(luaState, -1))
    {
        LOGERROR("Can not find lua function CreateScriptObjectInstance.");
        lua_settop(luaState, top);
        return false;
    }

    // Get table as first paramter.
    lua_getglobal(luaState, objectType.CString());
    if (!lua_istable(luaState, -1))
    {
        LOGERROR("Can not find lua table " + objectType + ".");
        lua_settop(luaState, top);
        return false;
    }

    // Push this as second parameter.
    tolua_pushusertype(luaState, (void*)this, "LuaScriptInstance");
    
    // Call ObjectType:new function.
    if (lua_pcall(luaState, 2, 1, 0) != 0)
    {
        const char* message = lua_tostring(luaState, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState, top);
        return false;
    }

    objectType_ = objectType;

    return true;
}

void LuaScriptInstance::ScriptSubscribeToEvent(const String& eventName, const String& functionName)
{
    StringHash eventType(eventName);
    String realFunctionName = functionName.Replaced(":", ".");

    HashSet<Object*>* receivers = context_->GetEventReceivers(eventType);
    if (!receivers || !receivers->Contains(this))
        SubscribeToEvent(eventType, HANDLER(LuaScriptInstance, HandleEvent));

    eventTypeToFunctionNameMap_[eventType].Insert(realFunctionName);
}

bool LuaScriptInstance::PushScriptObject(lua_State* luaState)
{
    tolua_pushusertype(luaState, (void*)this, "LuaScriptInstance");
    tolua_pushstring(luaState, "object");

    lua_gettable(luaState, -2);
    if (!lua_istable(luaState, -1))
    {
        return false;
    }

    lua_remove(luaState, -2);

    return true;
}

void LuaScriptInstance::HandleEvent(StringHash eventType, VariantMap& eventData)
{
    const HashSet<String>& functionNames = eventTypeToFunctionNameMap_[eventType];
    for (HashSet<String>::ConstIterator i = functionNames.Begin(); i != functionNames.End(); ++i)
        CallEventHandler(*i, eventType, eventData);
}

void LuaScriptInstance::CallEventHandler(const String& functionName, StringHash eventType, VariantMap& eventData )
{
    LuaScript* luaScript = GetSubsystem<LuaScript>();
    lua_State* luaState = luaScript->GetLuaState();

    int top = lua_gettop(luaState);
    
    if (!luaScript->FindFunction(functionName))
    {
        lua_settop(luaState, top);
        return;
    }

    if (!PushScriptObject(luaState))
    {
        lua_settop(luaState, top);
        return;
    }

    tolua_pushusertype(luaState, (void*)&eventType, "StringHash");
    tolua_pushusertype(luaState, (void*)&eventData, "VariantMap");

    if (lua_pcall(luaState, 3, 0, 0) != 0)
    {
        const char* message = lua_tostring(luaState, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState, top);
        return;
    }
}

}
