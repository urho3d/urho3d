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
#include "CoreEvents.h"
#include "Context.h"
#include "Log.h"
#include "LuaFile.h"
#include "LuaScript.h"
#include "LuaScriptInstance.h"
#include "MemoryBuffer.h"
#include "PhysicsEvents.h"
#include "ResourceCache.h"
#include "ToluaUrho3DEx.h"
#include "ProcessUtils.h"
#include "VectorBuffer.h"

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include "tolua++.h"

namespace Urho3D
{

static const char* scriptObjectMethodNames[] = {
    ".Start",
    ".Stop",
    // ".DelayedStart",
    ".Update",
    ".PostUpdate",
    ".FixedUpdate",
    ".FixedPostUpdate",
    ".Load",
    ".Save",
    ".ReadNetworkUpdate",
    ".WriteNetworkUpdate",
    ".ApplyAttributes"
};

LuaScriptInstance::LuaScriptInstance(Context* context) : 
    Component(context),
    scriptObjectRef_(LUA_REFNIL)
{
    luaScript_ = GetSubsystem<LuaScript>();
    luaState_ = luaScript_->GetLuaState();

    for (unsigned i = 0; i < MAX_LUA_SCRIPT_OBJECT_METHODS; ++i)
        scriptObjectMethodRefs_[i] = LUA_REFNIL;
}

LuaScriptInstance::~LuaScriptInstance()
{
    ReleaseObject();
}

void LuaScriptInstance::RegisterObject(Context* context)
{
    context->RegisterFactory<LuaScriptInstance>(LOGIC_CATEGORY);

    // ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_BOOL, "Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_STRING, "Script File Name", GetScriptFileName, SetScriptFileName, String, String::EMPTY, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_STRING, "Script Object Type", GetScriptObjectType, SetScriptObjectType, String, String::EMPTY, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_BUFFER, "Script Data", GetScriptDataAttr, SetScriptDataAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_FILE | AM_NOEDIT);
    ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_BUFFER, "Script Network Data", GetScriptNetworkDataAttr, SetScriptNetworkDataAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_NET | AM_NOEDIT);
}

void LuaScriptInstance::ApplyAttributes()
{
    CallScriptObjectFunction(scriptObjectMethodRefs_[LSOM_APPLYATTRIBUTES]);
}

void LuaScriptInstance::OnSetEnabled()
{
    if (enabled_)
        SubscribeToEvents();    
    else
        UnsubscribeFromEvents();
}

bool LuaScriptInstance::CreateObject(const String& scriptObjectType)
{
    SetScriptFileName(String::EMPTY);
    SetScriptObjectType(scriptObjectType);
    return scriptObjectRef_ != LUA_REFNIL;
}

bool LuaScriptInstance::CreateObject(const String& scriptFileName, const String& scriptObjectType)
{
    SetScriptFileName(scriptFileName);
    SetScriptObjectType(scriptObjectType);
    return scriptObjectRef_ != LUA_REFNIL;
}

void LuaScriptInstance::SetScriptFileName(const String& scriptFileName)
{
    if (scriptFileName_ == scriptFileName)
        return;

    scriptFileName_ = scriptFileName;

    if (scriptFileName_.Empty())
        return;

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    LuaFile* luaFile = cache->GetResource<LuaFile>(scriptFileName_);
    if (!luaFile)
        return;

    if (!luaFile->LoadAndExecute(luaState_))
        LOGERROR("Execute Lua file failed: " + scriptFileName_);
}

void LuaScriptInstance::SetScriptObjectType(const String& scriptObjectType)
{
    if (scriptObjectType_ == scriptObjectType)
        return;

    ReleaseObject();

    int top = lua_gettop(luaState_);

    lua_getglobal(luaState_, "CreateScriptObjectInstance");
    if (!lua_isfunction(luaState_, -1))
    {
        LOGERROR("Could not find lua function CreateScriptObjectInstance");
        lua_settop(luaState_, top);
        return;
    }

    // Get table as first paramter.
    lua_getglobal(luaState_, scriptObjectType.CString());
    if (!lua_istable(luaState_, -1))
    {
        LOGERROR("Could not find lua table " + scriptObjectType);
        lua_settop(luaState_, top);
        return;
    }

    // Push this as second parameter.
    tolua_pushusertype(luaState_, (void*)this, "LuaScriptInstance");

    // Call ObjectType:new function.
    if (lua_pcall(luaState_, 2, 1, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState_, top);
        return;
    }

    scriptObjectType_ = scriptObjectType;
    scriptObjectRef_ = luaL_ref(luaState_, LUA_REGISTRYINDEX);

    // Find script object method refs.
    FindScriptObjectMethodRefs();
}

void LuaScriptInstance::SetScriptDataAttr(PODVector<unsigned char> data)
{
    int functionRef = scriptObjectMethodRefs_[LSOM_LOAD];
    if (scriptObjectRef_ == LUA_REFNIL || functionRef == LUA_REFNIL)
        return;

    MemoryBuffer buf(data);
    CallScriptObjectFunction(functionRef, (Deserializer&)buf);
}

void LuaScriptInstance::SetScriptNetworkDataAttr(PODVector<unsigned char> data)
{
    int functionRef = scriptObjectMethodRefs_[LSOM_READNETWORKUPDATE];
    if (scriptObjectRef_ == LUA_REFNIL || functionRef == LUA_REFNIL)
        return;

    MemoryBuffer buf(data);
    CallScriptObjectFunction(functionRef, (Deserializer&)buf);
}

void LuaScriptInstance::ScriptSubscribeToEvent(const String& eventName, const String& functionName)
{
    String realFunctionName = functionName.Replaced(":", ".");

    int functionRef = luaScript_->GetScriptFunctionRef(realFunctionName);
    if (functionRef != LUA_REFNIL)
    {
        StringHash eventType(eventName);
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
        eventTypeToFunctionRefMap_.Erase(i);
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromAllEvents()
{
    if (eventTypeToFunctionRefMap_.Empty())
        return;

    UnsubscribeFromAllEvents();
    eventTypeToFunctionRefMap_.Clear();
}

void LuaScriptInstance::ScriptSubscribeToEvent(void* sender, const String& eventName, const String& functionName)
{
    String realFunctionName = functionName.Replaced(":", ".");

    int functionRef = luaScript_->GetScriptFunctionRef(realFunctionName);
    if (functionRef != LUA_REFNIL)
    {
        Object* object = (Object*)sender;
        StringHash eventType(eventName);
        SubscribeToEvent(object, eventType, HANDLER(LuaScriptInstance, HandleObjectEvent));
        objectToEventTypeToFunctionRefMap_[object][eventType] = functionRef;
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromEvent(void* sender, const String& eventName)
{
    StringHash eventType(eventName);
    Object* object = (Object*)sender ;

    HashMap<StringHash, int>::Iterator i = objectToEventTypeToFunctionRefMap_[object].Find(eventType);
    if (i != objectToEventTypeToFunctionRefMap_[object].End())
    {
        UnsubscribeFromEvent(object, eventType);
        objectToEventTypeToFunctionRefMap_[object].Erase(i);
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromEvents(void* sender)
{
    Object* object = (Object*)sender;

    HashMap<Object*, HashMap<StringHash, int> >::Iterator it = objectToEventTypeToFunctionRefMap_.Find(object);
    if (it == objectToEventTypeToFunctionRefMap_.End())
        return;

    UnsubscribeFromEvents(object);
    objectToEventTypeToFunctionRefMap_.Erase(it);
}

bool LuaScriptInstance::ExecuteFunction(const String& functionName, const VariantVector& parameters)
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return false;

    int functionRef = luaScript_->GetScriptFunctionRef(scriptObjectType_ + "." + functionName);
    if (functionRef == LUA_REFNIL)
        return false;
    
    return CallScriptObjectFunction(functionRef, parameters);
}

PODVector<unsigned char> LuaScriptInstance::GetScriptDataAttr() const
{
    int functionRef = scriptObjectMethodRefs_[LSOM_SAVE];
    if (scriptObjectRef_ == LUA_REFNIL || functionRef == LUA_REFNIL)
        return PODVector<unsigned char>();

    VectorBuffer buf;
    CallScriptObjectFunction(functionRef, (Serializer&)buf);

    return buf.GetBuffer();
}

PODVector<unsigned char> LuaScriptInstance::GetScriptNetworkDataAttr() const
{
    int functionRef = scriptObjectMethodRefs_[LSOM_WRITENETWORKUPDATE];
    if (scriptObjectRef_ == LUA_REFNIL || functionRef == LUA_REFNIL)
        return PODVector<unsigned char>();

    VectorBuffer buf;
    CallScriptObjectFunction(functionRef, (Serializer&)buf);

    return buf.GetBuffer();
}


void LuaScriptInstance::FindScriptObjectMethodRefs()
{
    for (unsigned i = 0; i < MAX_LUA_SCRIPT_OBJECT_METHODS; ++i)
        scriptObjectMethodRefs_[i] = luaScript_->GetScriptFunctionRef(scriptObjectType_ + scriptObjectMethodNames[i], true);

    if (enabled_)
        SubscribeToEvents();
}

void LuaScriptInstance::SubscribeToEvents()
{
    if (scriptObjectMethodRefs_[LSOM_UPDATE] != LUA_REFNIL)
        SubscribeToEvent(E_UPDATE, HANDLER(LuaScriptInstance, HandleUpdate));

    if (scriptObjectMethodRefs_[LSOM_POSTUPDATE] != LUA_REFNIL)
        SubscribeToEvent(E_POSTUPDATE, HANDLER(LuaScriptInstance, HandlePostUpdate));

    if (scriptObjectMethodRefs_[LSOM_FIXEDUPDATE] != LUA_REFNIL)
        SubscribeToEvent(E_PHYSICSPRESTEP, HANDLER(LuaScriptInstance, HandleFixedUpdate));

    if (scriptObjectMethodRefs_[LSOM_FIXEDPOSTUPDATE] != LUA_REFNIL)
        SubscribeToEvent(E_PHYSICSPOSTSTEP, HANDLER(LuaScriptInstance, HandlePostFixedUpdate));
}

void LuaScriptInstance::UnsubscribeFromEvents()
{
    if (scriptObjectMethodRefs_[LSOM_UPDATE] != LUA_REFNIL)
        UnsubscribeFromEvent(E_UPDATE);

    if (scriptObjectMethodRefs_[LSOM_POSTUPDATE] != LUA_REFNIL)
        UnsubscribeFromEvent(E_POSTUPDATE);

    if (scriptObjectMethodRefs_[LSOM_FIXEDUPDATE] != LUA_REFNIL)
        UnsubscribeFromEvent(E_PHYSICSPRESTEP);

    if (scriptObjectMethodRefs_[LSOM_FIXEDPOSTUPDATE] != LUA_REFNIL)
        UnsubscribeFromEvent(E_PHYSICSPOSTSTEP);
}

void LuaScriptInstance::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    CallScriptObjectFunction(scriptObjectMethodRefs_[LSOM_UPDATE], timeStep);
}

void LuaScriptInstance::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace PostUpdate;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    CallScriptObjectFunction(scriptObjectMethodRefs_[LSOM_POSTUPDATE], timeStep);
}

void LuaScriptInstance::HandleFixedUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPreStep;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    CallScriptObjectFunction(scriptObjectMethodRefs_[LSOM_FIXEDUPDATE], timeStep);
}

void LuaScriptInstance::HandlePostFixedUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPostStep;
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    CallScriptObjectFunction(scriptObjectMethodRefs_[LSOM_FIXEDPOSTUPDATE], timeStep);
}

void LuaScriptInstance::HandleEvent(StringHash eventType, VariantMap& eventData)
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return;

    int functionRef = eventTypeToFunctionRefMap_[eventType];
    if (functionRef == LUA_REFNIL)
        return;

    CallScriptObjectFunction(functionRef, eventType, eventData);
}

void LuaScriptInstance::HandleObjectEvent(StringHash eventType, VariantMap& eventData)
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return;

    Object* object = GetEventSender();
    int functionRef = objectToEventTypeToFunctionRefMap_[object][eventType];
    if (functionRef == LUA_REFNIL)
        return;

    CallScriptObjectFunction(functionRef, eventType, eventData);
}

void LuaScriptInstance::ReleaseObject()
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return;

    if (enabled_)
        UnsubscribeFromEvents();

    // Unref script object.
    luaL_unref(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);
    scriptObjectRef_ = LUA_REFNIL;

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
    }
}

void LuaScriptInstance::CallScriptObjectFunction(int functionRef)
{
    if (functionRef == LUA_REFNIL)
        return;

    int top = lua_gettop(luaState_);

    // Push function.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, functionRef);

    // Push script object.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);

    // Call script object function.
    if (lua_pcall(luaState_, 1, 0, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState_, top);
        return;
    }
}

void LuaScriptInstance::CallScriptObjectFunction(int functionRef, float timeStep)
{
    if (functionRef == LUA_REFNIL)
        return;

    int top = lua_gettop(luaState_);

    // Push function.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, functionRef);

    // Push script object.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);

    // Push time step.
    tolua_pushnumber(luaState_, timeStep);

    // Call script object function.
    if (lua_pcall(luaState_, 2, 0, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState_, top);
        return;
    }
}

void LuaScriptInstance::CallScriptObjectFunction(int functionRef, Deserializer& deserializer)
{
    if (functionRef == LUA_REFNIL)
        return;

    int top = lua_gettop(luaState_);

    // Push function.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, functionRef);

    // Push script object.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);

    // Push Deserializer.
    tolua_pushusertype(luaState_, (void*)&deserializer, "Deserializer");

    // Call script object function.
    if (lua_pcall(luaState_, 2, 0, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState_, top);
    }
}

void LuaScriptInstance::CallScriptObjectFunction(int functionRef, Serializer& serializer) const
{
    if (functionRef == LUA_REFNIL)
        return;

    int top = lua_gettop(luaState_);

    // Push function.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, functionRef);

    // Push script object.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);

    // Push Deserializer.
    tolua_pushusertype(luaState_, (void*)&serializer, "Serializer");

    // Call script object function.
    if (lua_pcall(luaState_, 2, 0, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState_, top);
    }
}

void LuaScriptInstance::CallScriptObjectFunction(int functionRef, StringHash eventType, VariantMap& eventData)
{
    if (functionRef == LUA_REFNIL)
        return;
    
    int top = lua_gettop(luaState_);

    // Push function.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, functionRef);

    // Push script object.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);

    // Push event type.
    tolua_pushusertype(luaState_, (void*)&eventType, "StringHash");

    // Push event data.
    tolua_pushusertype(luaState_, (void*)&eventData, "VariantMap");

    // Call script object function.
    if (lua_pcall(luaState_, 3, 0, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState_, top);
    }
}

bool LuaScriptInstance::CallScriptObjectFunction(int functionRef, const VariantVector& parameters)
{
    if (functionRef == LUA_REFNIL)
        return false;

    int top = lua_gettop(luaState_);

    // Push function.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, functionRef);

    // Push script object.
    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);

    // Push parameters.
    if (!tolua_pushurho3dvariantvector(luaState_, parameters))
    {
        lua_settop(luaState_, top);
        return false;
    }
    
    // Call script object function.
    if (lua_pcall(luaState_, 1 + parameters.Size(), 0, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        LOGERROR("Execute Lua function failed: " + String(message));
        lua_settop(luaState_, top);
        return false;
    }
    
    return true;
}

}
