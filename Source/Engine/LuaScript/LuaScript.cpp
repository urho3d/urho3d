//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "EngineEvents.h"
#include "File.h"
#include "Log.h"
#include "LuaFile.h"
#include "LuaFunction.h"
#include "LuaScript.h"
#include "LuaScriptInstance.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Scene.h"

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include "tolua++.h"
#include "ToluaUtils.h"

#include "DebugNew.h"

extern int tolua_AudioLuaAPI_open(lua_State*);
extern int tolua_ContainerLuaAPI_open(lua_State*);
extern int tolua_CoreLuaAPI_open(lua_State*);
extern int tolua_EngineLuaAPI_open(lua_State*);
extern int tolua_GraphicsLuaAPI_open(lua_State*);
extern int tolua_InputLuaAPI_open(lua_State*);
extern int tolua_IOLuaAPI_open(lua_State*);
extern int tolua_MathLuaAPI_open(lua_State*);
extern int tolua_NavigationLuaAPI_open(lua_State*);
extern int tolua_NetworkLuaAPI_open(lua_State*);
extern int tolua_PhysicsLuaAPI_open(lua_State*);
extern int tolua_ResourceLuaAPI_open(lua_State*);
extern int tolua_SceneLuaAPI_open(lua_State*);
extern int tolua_UILuaAPI_open(lua_State*);
extern int tolua_Urho2DLuaAPI_open(lua_State*);
extern int tolua_LuaScriptLuaAPI_open(lua_State*);

namespace Urho3D
{

LuaScript::LuaScript(Context* context) :
    Object(context),
    luaState_(0),
    executeConsoleCommands_(true)
{
    RegisterLuaScriptLibrary(context_);

    luaState_ = luaL_newstate();
    if (!luaState_)
    {
        LOGERROR("Could not create Lua state");
        return;
    }

    SetContext(luaState_, context_);

    lua_atpanic(luaState_, &LuaScript::AtPanic);

    luaL_openlibs(luaState_);
    RegisterLoader();
    ReplacePrint();

    tolua_ContainerLuaAPI_open(luaState_);
    tolua_MathLuaAPI_open(luaState_);
    tolua_CoreLuaAPI_open(luaState_);
    tolua_IOLuaAPI_open(luaState_);
    tolua_ResourceLuaAPI_open(luaState_);
    tolua_SceneLuaAPI_open(luaState_);
    tolua_AudioLuaAPI_open(luaState_);
    tolua_EngineLuaAPI_open(luaState_);
    tolua_GraphicsLuaAPI_open(luaState_);
    tolua_InputLuaAPI_open(luaState_);
    tolua_NavigationLuaAPI_open(luaState_);
    tolua_NetworkLuaAPI_open(luaState_);
    tolua_PhysicsLuaAPI_open(luaState_);
    tolua_UILuaAPI_open(luaState_);
    tolua_Urho2DLuaAPI_open(luaState_);
    tolua_LuaScriptLuaAPI_open(luaState_);

    coroutineUpdate_ = GetFunction("coroutine.update");

    // Subscribe to post update
    SubscribeToEvent(E_POSTUPDATE, HANDLER(LuaScript, HandlePostUpdate));

    // Subscribe to console commands
    SubscribeToEvent(E_CONSOLECOMMAND, HANDLER(LuaScript, HandleConsoleCommand));
    
    // Record the internally handled script functions so that UnsubscribeFromAllEvents doesn't destroy them
    internalEvents_.Push(E_POSTUPDATE);
    internalEvents_.Push(E_CONSOLECOMMAND);
}

LuaScript::~LuaScript()
{
    functionNameToFunctionMap_.Clear();

    lua_State* luaState = luaState_;
    luaState_ = 0;

    SetContext(luaState_, 0);

    if (luaState)
        lua_close(luaState);
}

bool LuaScript::ExecuteFile(const String& fileName)
{
    PROFILE(ExecuteFile);

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    LuaFile* luaFile = cache->GetResource<LuaFile>(fileName);
    return luaFile && luaFile->LoadAndExecute(luaState_);
}

bool LuaScript::ExecuteString(const String& string)
{
    PROFILE(ExecuteString);

    int top = lua_gettop(luaState_);

    if (luaL_dostring(luaState_, string.CString()) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        LOGERROR("Execute Lua string failed: " + String(message));
        lua_settop(luaState_, top);
        return false;
    }

    return true;
}

bool LuaScript::ExecuteFunction(const String& functionName)
{
    WeakPtr<LuaFunction> function = GetFunction(functionName);
    return function && function->BeginCall() && function->EndCall();
}

void LuaScript::ScriptSendEvent(const String& eventName, VariantMap& eventData)
{
    SendEvent(StringHash(eventName), eventData);
}

void LuaScript::ScriptSubscribeToEvent(const String& eventName, const String& functionName)
{
    StringHash eventType(eventName);

    WeakPtr<LuaFunction> function = GetFunction(functionName);
    if (function)
    {
        LuaFunctionVector& functions = eventHandleFunctions_[eventType];
        if (functions.Empty())
            SubscribeToEvent(eventType, HANDLER(LuaScript, HandleEvent));

        functions.Push(function);
    }
}

void LuaScript::ScriptUnsubscribeFromEvent(const String& eventName, const String& functionName)
{
    StringHash eventType(eventName);
    
    HashMap<StringHash, LuaFunctionVector>::Iterator i = eventHandleFunctions_.Find(eventType);
    if (i != eventHandleFunctions_.End())
    {
        LuaFunctionVector& functions = i->second_;
        if (!functionName.Empty())
        {   
            WeakPtr<LuaFunction> function = GetFunction(functionName);
            functions.Remove(function);
        }

        if (functionName.Empty() || functions.Empty())
        {
            UnsubscribeFromEvent(eventType);
            eventHandleFunctions_.Erase(i);
        }
    }
}

void LuaScript::ScriptUnsubscribeFromAllEvents()
{
    if (eventHandleFunctions_.Empty())
        return;
    
    UnsubscribeFromAllEventsExcept(internalEvents_, false);

    eventHandleFunctions_.Clear();
}

void LuaScript::ScriptSubscribeToEvent(void* sender, const String& eventName, const String& functionName)
{
    StringHash eventType(eventName);
    Object* object = (Object*)sender;

    WeakPtr<LuaFunction> function = GetFunction(functionName);
    if (function)
    {
        LuaFunctionVector& functions = objectHandleFunctions_[object][eventType];
        if (functions.Empty())
            SubscribeToEvent(object, eventType, HANDLER(LuaScript, HandleObjectEvent));

        functions.Push(function);
    }
}

void LuaScript::ScriptUnsubscribeFromEvent(void* sender, const String& eventName, const String& functionName)
{
    StringHash eventType(eventName);
    Object* object = (Object*)sender;

    HashMap<StringHash, LuaFunctionVector>::Iterator i = objectHandleFunctions_[object].Find(eventType);
    if (i != objectHandleFunctions_[object].End())
    {
        LuaFunctionVector& functions = i->second_;
        if (!functionName.Empty())
        {
            WeakPtr<LuaFunction> function = GetFunction(functionName);
            functions.Remove(function);
        }

        if (functionName.Empty() || functions.Empty())
        {
            UnsubscribeFromEvent(object, eventType);
            objectHandleFunctions_[object].Erase(i);
        }
    }
}

void LuaScript::ScriptUnsubscribeFromEvents(void* sender)
{
    Object* object = (Object*)sender;

    HashMap<Object*, HashMap<StringHash, LuaFunctionVector> >::Iterator it = objectHandleFunctions_.Find(object);
    if (it == objectHandleFunctions_.End())
        return;

    UnsubscribeFromEvents(object);
    objectHandleFunctions_.Erase(it);
}

void LuaScript::SetExecuteConsoleCommands(bool enable)
{
    executeConsoleCommands_ = enable;
}

void LuaScript::RegisterLoader()
{
    // Get package.loaders table
    lua_getglobal(luaState_, "package");
    lua_getfield(luaState_, -1, "loaders");

    // Add LuaScript::Loader to the end of the table
    lua_pushinteger(luaState_, lua_objlen(luaState_, -1) + 1);
    lua_pushcfunction(luaState_, &LuaScript::Loader);
    lua_settable(luaState_, -3);
    lua_pop(luaState_, 2);
}

int LuaScript::AtPanic(lua_State* L)
{
    String errorMessage = luaL_checkstring(L, -1);
    LOGERROR("Lua error: Error message = '" + errorMessage + "'");
    lua_pop(L, 1);
    return 0;
}

int LuaScript::Loader(lua_State* L)
{
    ResourceCache* cache = ::GetContext(L)->GetSubsystem<ResourceCache>();

    // Get module name
    const char* name = luaL_checkstring(L, 1);

    // Attempt to get .luc file first.
    String lucFileName = String(name) + ".luc";
    LuaFile* lucFile = cache->GetResource<LuaFile>(lucFileName, false);
    if (lucFile)
        return lucFile->LoadChunk(L) ? 1 : 0;

    // Then try to get .lua file. If this also fails, error is logged and resource not found event is sent
    String luaFileName = String(name) + ".lua";
    LuaFile* luaFile = cache->GetResource<LuaFile>(luaFileName);
    if (luaFile)
        return luaFile->LoadChunk(L) ? 1 : 0;

    return 0;
}

void LuaScript::ReplacePrint()
{
    static const struct luaL_reg reg[] =
    {
        {"print", &LuaScript::Print},
        { NULL, NULL}
    };

    lua_getglobal(luaState_, "_G");
    luaL_register(luaState_, NULL, reg);
    lua_pop(luaState_, 1);
}

int LuaScript::Print(lua_State *L)
{
    String string;
    int n = lua_gettop(L);
    lua_getglobal(L, "tostring");
    for (int i = 1; i <= n; i++)
    {
        const char *s;
        // Function to be called
        lua_pushvalue(L, -1);
        // Value to print
        lua_pushvalue(L, i);
        lua_call(L, 1, 1);
        // Get result
        s = lua_tostring(L, -1);
        if (s == NULL)
            return luaL_error(L, LUA_QL("tostring") " must return a string to " LUA_QL("print"));

        if (i > 1)
            string.Append("    ");

        string.Append(s);
        // Pop result
        lua_pop(L, 1);
    }

    LOGRAW("Lua: " + string);

    return 0;
}

WeakPtr<LuaFunction> LuaScript::GetFunction(const String& functionName, bool silentIfNotFound)
{
    if (!luaState_)
        return WeakPtr<LuaFunction>();

    HashMap<String, SharedPtr<LuaFunction> >::Iterator i = functionNameToFunctionMap_.Find(functionName);
    if (i != functionNameToFunctionMap_.End())
        return WeakPtr<LuaFunction>(i->second_);

    int top = lua_gettop(luaState_);

    SharedPtr<LuaFunction> function;
    if (PushScriptFunction(functionName, silentIfNotFound))
    {
        int ref = luaL_ref(luaState_, LUA_REGISTRYINDEX);
        function = new LuaFunction(luaState_, ref);
    }

    lua_settop(luaState_, top);

    functionNameToFunctionMap_[functionName] = function;

    return WeakPtr<LuaFunction>(function);
}

void LuaScript::HandleEvent(StringHash eventType, VariantMap& eventData)
{
    LuaFunctionVector& functions = eventHandleFunctions_[eventType];
    for (unsigned i = 0; i < functions.Size(); ++i)
    {
        WeakPtr<LuaFunction> function = functions[i];
        if (function && function->BeginCall())
        {
            function->PushUserType(eventType, "StringHash");
            function->PushUserType(eventData, "VariantMap");
            function->EndCall();
        }
    }
}

void LuaScript::HandleObjectEvent(StringHash eventType, VariantMap& eventData)
{
    Object* object = GetEventSender();
    LuaFunctionVector& functions = objectHandleFunctions_[object][eventType];
    for (unsigned i = 0; i < functions.Size(); ++i)
    {
        WeakPtr<LuaFunction> function = functions[i];
        if (function && function->BeginCall())
        {
            function->PushUserType(eventType, "StringHash");
            function->PushUserType(eventData, "VariantMap");
            function->EndCall();
        }
    }
}

void LuaScript::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    if (coroutineUpdate_ && coroutineUpdate_->BeginCall())
    {
        using namespace PostUpdate;
        float timeStep = eventData[P_TIMESTEP].GetFloat();
        coroutineUpdate_->PushFloat(timeStep);
        coroutineUpdate_->EndCall();
    }

    // Collect garbage
    lua_gc(luaState_, LUA_GCCOLLECT, 0);
}

void LuaScript::HandleConsoleCommand(StringHash eventType, VariantMap& eventData)
{
    using namespace ConsoleCommand;
    
    if (executeConsoleCommands_)
        ExecuteString(eventData[P_COMMAND].GetString());
}

bool LuaScript::PushScriptFunction(const String& functionName, bool silentIfNotFound)
{
    Vector<String> splitedNames = functionName.Split('.');

    String currentName = splitedNames.Front();
    lua_getglobal(luaState_, currentName.CString());

    if (splitedNames.Size() > 1)
    {
        if (!lua_istable(luaState_, -1))
        {
            LOGERROR("Could not find Lua table: Table name = '" + currentName + "'");
            return false;
        }

        for (unsigned i = 1; i < splitedNames.Size() - 1; ++i)
        {
            currentName = currentName + "." + splitedNames[i];
            lua_getfield(luaState_, -1, splitedNames[i].CString());
            if (!lua_istable(luaState_, -1))
            {
                LOGERROR("Could not find Lua table: Table name = '" + currentName + "'");
                return false;
            }
        }

        currentName = currentName + "." + splitedNames.Back().CString();
        lua_getfield(luaState_, -1, splitedNames.Back().CString());
    }

    if (!lua_isfunction(luaState_, -1))
    {
        if (!silentIfNotFound)
            LOGERROR("Could not find Lua function: Function name = '" + currentName + "'");
        return false;
    }

    return true;
}

void RegisterLuaScriptLibrary(Context* context)
{
    LuaFile::RegisterObject(context);
    LuaScriptInstance::RegisterObject(context);
}

}
