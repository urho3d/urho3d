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

LuaScriptInstance::LuaScriptInstance(Context* context) : 
    Component(context), 
    scriptObjectRef_(LUA_REFNIL)
{
    luaScript_ = GetSubsystem<LuaScript>();
    luaState_ = luaScript_->GetLuaState();
}

LuaScriptInstance::~LuaScriptInstance()
{
    // Unref script object.
    if (scriptObjectRef_ != LUA_REFNIL)
        luaL_unref(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);

    // Unref Lua function.
    for (HashMap<StringHash, int>::Iterator i = eventTypeToFunctionRefMap_.Begin(); i != eventTypeToFunctionRefMap_.End(); ++i)
        luaL_unref(luaState_, LUA_REGISTRYINDEX, i->second_);
    
    int top = lua_gettop(luaState_);

    lua_getglobal(luaState_, "DestroyScriptObjectInstance");
    if (!lua_isfunction(luaState_, -1))
    {
        LOGERROR("Can not find lua function DestroyScriptObjectInstance.");
        lua_settop(luaState_, top);
        return;
    }

    // Push this as second parameter.
    tolua_pushusertype(luaState_, (void*)this, "LuaScriptInstance");

    // Call ObjectType:new function.
    if (lua_pcall(luaState_, 1, 0, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState_, top);
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

    int top = lua_gettop(luaState_);

    lua_getglobal(luaState_, "CreateScriptObjectInstance");
    if (!lua_isfunction(luaState_, -1))
    {
        LOGERROR("Can not find lua function CreateScriptObjectInstance.");
        lua_settop(luaState_, top);
        return false;
    }

    // Get table as first paramter.
    lua_getglobal(luaState_, objectType.CString());
    if (!lua_istable(luaState_, -1))
    {
        LOGERROR("Can not find lua table " + objectType + ".");
        lua_settop(luaState_, top);
        return false;
    }

    // Push this as second parameter.
    tolua_pushusertype(luaState_, (void*)this, "LuaScriptInstance");
    
    // Call ObjectType:new function.
    if (lua_pcall(luaState_, 2, 1, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState_, top);
        return false;
    }

    objectType_ = objectType;
    scriptObjectRef_ = luaL_ref(luaState_, LUA_REGISTRYINDEX);

    return true;
}

void LuaScriptInstance::ScriptSubscribeToEvent(const String& eventName, const String& functionName)
{
    StringHash eventType(eventName);
    String realFunctionName = functionName.Replaced(":", ".");

    HashSet<Object*>* receivers = context_->GetEventReceivers(eventType);
    if (!receivers || !receivers->Contains(this))
        SubscribeToEvent(eventType, HANDLER(LuaScriptInstance, HandleEvent));

    int functionRef = LUA_REFNIL;
    if (luaScript_->FindFunction(realFunctionName))
        functionRef = luaL_ref(luaState_, LUA_REGISTRYINDEX);

    eventTypeToFunctionRefMap_[eventType] = functionRef;
}

void LuaScriptInstance::ScriptSubscribeToEvent(void* object, const String& eventName, const String& functionName)
{
    StringHash eventType(eventName);
    String realFunctionName = functionName.Replaced(":", ".");
    Object* sender = (Object*)object;
    
    HashSet<Object*>* receivers = context_->GetEventReceivers(sender, eventType);
    if (!receivers || !receivers->Contains(this))
        SubscribeToEvent(sender, eventType, HANDLER(LuaScriptInstance, HandleObjectEvent));

    int functionRef = LUA_REFNIL;
    if (luaScript_->FindFunction(realFunctionName))
        functionRef = luaL_ref(luaState_, LUA_REGISTRYINDEX);

    objectToEventTypeToFunctionRefMap_[sender][eventType] = functionRef;
}

void LuaScriptInstance::HandleEvent(StringHash eventType, VariantMap& eventData)
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return;

    int functionRef = eventTypeToFunctionRefMap_[eventType];
    if (functionRef == LUA_REFNIL)
        return;

    CallEventHandler(functionRef, eventType, eventData);
}

void LuaScriptInstance::HandleObjectEvent(StringHash eventType, VariantMap& eventData)
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return;

    Object* object = GetEventSender();
    int functionRef = objectToEventTypeToFunctionRefMap_[object][eventType];
    if (functionRef == LUA_REFNIL)
        return;

    CallEventHandler(functionRef, eventType, eventData);
}

void LuaScriptInstance::CallEventHandler(int functionRef, StringHash eventType, VariantMap& eventData )
{
    int top = lua_gettop(luaState_);

    // Push function.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, functionRef);  

    // Push script object.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);

    // Push event type.
    tolua_pushusertype(luaState_, (void*)&eventType, "StringHash");

    // Push event data.
    tolua_pushusertype(luaState_, (void*)&eventData, "VariantMap");

    if (lua_pcall(luaState_, 3, 0, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState_, top);
        return;
    }

}

}
