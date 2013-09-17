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
#include "LuaFile.h"
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
    ReleaseObject();
}

void LuaScriptInstance::RegisterObject(Context* context)
{
    context->RegisterFactory<LuaScriptInstance>();
}

bool LuaScriptInstance::CreateObject(const String& scriptObjectType)
{
    if (scriptObjectType_ == scriptObjectType)
        return true;

    ReleaseObject();

    int top = lua_gettop(luaState_);

    lua_getglobal(luaState_, "CreateScriptObjectInstance");
    if (!lua_isfunction(luaState_, -1))
    {
        LOGERROR("Could not find lua function CreateScriptObjectInstance");
        lua_settop(luaState_, top);
        return false;
    }

    // Get table as first paramter.
    lua_getglobal(luaState_, scriptObjectType.CString());
    if (!lua_istable(luaState_, -1))
    {
        LOGERROR("Could not find lua table " + scriptObjectType);
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

    scriptObjectType_ = scriptObjectType;
    scriptObjectRef_ = luaL_ref(luaState_, LUA_REGISTRYINDEX);

    return true;
}

bool LuaScriptInstance::CreateObject(const String& fileName, const String& scriptObjectType)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    LuaFile* luaFile = cache->GetResource<LuaFile>(fileName);
    if (!luaFile)
        return false;

    if (!luaFile->LoadAndExecute(luaState_))
        return false;

    return CreateObject(scriptObjectType);
}

void LuaScriptInstance::ScriptSubscribeToEvent(const String& eventName, const String& functionName)
{
    StringHash eventType(eventName);
    String realFunctionName = functionName.Replaced(":", ".");

    int functionRef = LUA_REFNIL;
    if (luaScript_->FindFunction(realFunctionName))
        functionRef = luaL_ref(luaState_, LUA_REGISTRYINDEX);

    if (functionRef != LUA_REFNIL)
    {
        SubscribeToEvent(eventType, HANDLER(LuaScriptInstance, HandleEvent));
        eventTypeToFunctionRefMap_[eventType] = functionRef;
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromEvent(const String& eventName)
{
    StringHash eventType(eventName);

    HashMap<StringHash, int>::Iterator i = eventTypeToFunctionRefMap_.Find(eventType);
    if (i != eventTypeToFunctionRefMap_.End())
    {
        UnsubscribeFromEvent(eventType);

        if (i->second_ != LUA_REFNIL)
            luaL_unref(luaState_, LUA_REGISTRYINDEX, i->second_);

        eventTypeToFunctionRefMap_.Erase(i);
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromAllEvents()
{
    if (eventTypeToFunctionRefMap_.Empty())
        return;

    UnsubscribeFromAllEvents();

    for (HashMap<StringHash, int>::Iterator i = eventTypeToFunctionRefMap_.Begin(); i != eventTypeToFunctionRefMap_.End(); ++i)
        if (i->second_ != LUA_REFNIL)
            luaL_unref(luaState_, LUA_REGISTRYINDEX, i->second_);

    eventTypeToFunctionRefMap_.Clear();
}

void LuaScriptInstance::ScriptSubscribeToEvent(void* object, const String& eventName, const String& functionName)
{
    StringHash eventType(eventName);
    String realFunctionName = functionName.Replaced(":", ".");
    Object* sender = (Object*)object;

    int functionRef = LUA_REFNIL;
    if (luaScript_->FindFunction(realFunctionName))
        functionRef = luaL_ref(luaState_, LUA_REGISTRYINDEX);

    if (functionRef != LUA_REFNIL)
    {
        SubscribeToEvent(sender, eventType, HANDLER(LuaScriptInstance, HandleObjectEvent));
        objectToEventTypeToFunctionRefMap_[sender][eventType] = functionRef;
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromEvent(void* object, const String& eventName)
{
    StringHash eventType(eventName);
    Object* sender = (Object*)object;

    HashMap<StringHash, int>::Iterator i = objectToEventTypeToFunctionRefMap_[sender].Find(eventType);
    if (i != objectToEventTypeToFunctionRefMap_[sender].End())
    {
        UnsubscribeFromEvent(sender, eventType);

        if (i->second_ != LUA_REFNIL)
            luaL_unref(luaState_, LUA_REGISTRYINDEX, i->second_);

        objectToEventTypeToFunctionRefMap_[sender].Erase(i);
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromEvents(void* object)
{
    Object* sender = (Object*)object;

    HashMap<Object*, HashMap<StringHash, int> >::Iterator it = objectToEventTypeToFunctionRefMap_.Find(sender);
    if (it == objectToEventTypeToFunctionRefMap_.End())
        return;

    UnsubscribeFromEvents(sender);

    HashMap<StringHash, int>& eventTypeToFunctionRefMap = it->second_;
    for (HashMap<StringHash, int>::Iterator i = eventTypeToFunctionRefMap.Begin(); i != eventTypeToFunctionRefMap.End(); ++i)
    {
        if (i->second_ != LUA_REFNIL)
            luaL_unref(luaState_, LUA_REGISTRYINDEX, i->second_);
    }

    objectToEventTypeToFunctionRefMap_.Erase(it);
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

void LuaScriptInstance::ReleaseObject()
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return;
    
    // Unref script object.
    luaL_unref(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);
    scriptObjectRef_ = LUA_REFNIL;
    
    // Unref Lua function.
    for (HashMap<StringHash, int>::Iterator i = eventTypeToFunctionRefMap_.Begin(); i != eventTypeToFunctionRefMap_.End(); ++i)
        luaL_unref(luaState_, LUA_REGISTRYINDEX, i->second_);
    for (HashMap<Object*, HashMap<StringHash, int> >::Iterator i = objectToEventTypeToFunctionRefMap_.Begin(); 
        i != objectToEventTypeToFunctionRefMap_.End(); ++i)
    {
        for (HashMap<StringHash, int>::Iterator j = i->second_.Begin(); j != i->second_.End(); ++j)
            luaL_unref(luaState_, LUA_REGISTRYINDEX, j->second_);
    }
    
    int top = lua_gettop(luaState_);

    lua_getglobal(luaState_, "DestroyScriptObjectInstance");
    if (!lua_isfunction(luaState_, -1))
    {
        LOGERROR("Could not find lua function DestroyScriptObjectInstance");
        lua_settop(luaState_, top);
        return;
    }

    // Push this as second parameter.
    tolua_pushusertype(luaState_, (void*)this, "LuaScriptInstance");

    if (lua_pcall(luaState_, 1, 0, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState_, top);
        return;
    }
}

}
