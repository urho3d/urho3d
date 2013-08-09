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
#include "EngineEvents.h"
#include "File.h"
#include "Log.h"
#include "LuaScript.h"
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
extern int tolua_LuaScriptLuaAPI_open(lua_State*);

namespace Urho3D
{

static Context* currentContext_ = 0;

LuaScript::LuaScript(Context* context) :
    Object(context),
    luaState_(0)
{
    currentContext_ = context_;

    luaState_ = luaL_newstate();
    if (!luaState_)
    {
        ErrorDialog("Lua Error", "Could not create Lua state.");
        return;
    }

    luaL_openlibs(luaState_);
    RegisterLoader();
    ReplacePrint();

    tolua_AudioLuaAPI_open(luaState_);
    tolua_ContainerLuaAPI_open(luaState_);
    tolua_CoreLuaAPI_open(luaState_);
    tolua_EngineLuaAPI_open(luaState_);
    tolua_GraphicsLuaAPI_open(luaState_);
    tolua_InputLuaAPI_open(luaState_);
    tolua_IOLuaAPI_open(luaState_);
    tolua_MathLuaAPI_open(luaState_);
    tolua_NavigationLuaAPI_open(luaState_);
    tolua_NetworkLuaAPI_open(luaState_);
    tolua_PhysicsLuaAPI_open(luaState_);
    tolua_ResourceLuaAPI_open(luaState_);
    tolua_SceneLuaAPI_open(luaState_);
    tolua_UILuaAPI_open(luaState_);
    tolua_LuaScriptLuaAPI_open(luaState_);

    // Subscribe to console commands
    SubscribeToEvent(E_CONSOLECOMMAND, HANDLER(LuaScript, HandleConsoleCommand));
}

LuaScript::~LuaScript()
{
    if (luaState_)
        lua_close(luaState_);
}

bool LuaScript::ExecuteFile(const String& fileName)
{
    PROFILE(ExecuteFile);

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    if (!cache)
        return false;

    SharedPtr<File> file = cache->GetFile(fileName);
    if (!file)
        return false;

    unsigned size = file->GetSize();
    char* buffer = new char[size];
    file->Read(buffer, size);

    int top = lua_gettop(luaState_);
    int error = luaL_loadbuffer(luaState_, buffer, size, fileName.CString());
    delete [] buffer;

    if (error)
    {
        const char* message = lua_tostring(luaState_, -1);
        ErrorDialog("Execute Lua File Failed", message);
        lua_settop(luaState_, top);
        return false;
    }

    if (lua_pcall(luaState_, 0, 0, 0))
    {
        const char* message = lua_tostring(luaState_, -1);
        ErrorDialog("Execute Lua File Failed", message);
        lua_settop(luaState_, top);
        return false;
    }

    return true;
}

bool LuaScript::ExecuteString(const String& string)
{
    PROFILE(ExecuteString);

    int top = lua_gettop(luaState_);

    if (luaL_dostring(luaState_, string.CString()) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        ErrorDialog("Execute Lua String Failed", message);
        lua_settop(luaState_, top);
        return false;
    }

    return true;
}

bool LuaScript::ExecuteFunction(const String& functionName)
{
    PROFILE(ExecuteFunction);

    int top = lua_gettop(luaState_);

    if (!FindFunction(functionName))
    {
        lua_settop(luaState_, top);
        return false;
    }

    if (lua_pcall(luaState_, 0, 0, 0))
    {
        const char* message = lua_tostring(luaState_, -1);
        ErrorDialog("Execute Lua Function Failed", message);
        lua_settop(luaState_, top);
        return false;
    }

    return true;
}

void LuaScript::ScriptSendEvent(const String& eventName, VariantMap& eventData)
{
    SendEvent(StringHash(eventName), eventData);
}

void LuaScript::ScriptSubscribeToEvent(const String& eventName, const String& functionName)
{
    StringHash eventType(eventName);

    HashSet<Object*>* receivers = context_->GetEventReceivers(eventType);
    if (!receivers || !receivers->Contains(this))
        SubscribeToEvent(eventType, HANDLER(LuaScript, HandleEvent));

    eventTypeToFunctionNameMap_[eventType].Insert(functionName);
}

void LuaScript::ScriptSubscribeToEvent(Object* object, const String& eventName, const String& functionName)
{
    StringHash eventType(eventName);

    HashSet<Object*>* receivers = context_->GetEventReceivers(object, eventType);
    if (!receivers || !receivers->Contains(this))
        SubscribeToEvent(object, eventType, HANDLER(LuaScript, HandleObjectEvent));

    objectToEventTypeToFunctionNameMap_[object][eventType].Insert(functionName);
}

void LuaScript::RegisterLoader()
{
    lua_getglobal(luaState_, "package");

    lua_getfield(luaState_, -1, "loaders");

    // Replace first loader.
    lua_pushnumber(luaState_, 1);
    lua_pushcfunction(luaState_, &LuaScript::Loader);
    lua_settable(luaState_, -3);
}

int LuaScript::Loader(lua_State* L)
{
    ResourceCache* cache = currentContext_->GetSubsystem<ResourceCache>();
    if (!cache)
        return 0;

    const char* name = luaL_checkstring(L, 1);
    SharedPtr<File> file = cache->GetFile(String(name) + ".lua");
    if (!file)
        return 0;

    unsigned size = file->GetSize();
    char* buffer = new char[size];
    file->Read(buffer, size);

    int top = lua_gettop(L);
    int error = luaL_loadbuffer(L, buffer, size, name);
    delete [] buffer;

    if (error)
    {
        const char* message = lua_tostring(L, -1);
        ErrorDialog("Execute Lua File Failed", message);
        lua_settop(L, top);
        return 0;
    }

    return 1;
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
        lua_pushvalue(L, -1);  /* function to be called */
        lua_pushvalue(L, i);   /* value to print */
        lua_call(L, 1, 1);
        s = lua_tostring(L, -1);  /* get result */
        if (s == NULL)
            return luaL_error(L, LUA_QL("tostring") " must return a string to " LUA_QL("print"));

        if (i > 1)
            string.Append("    "); // fputs("\t", stdout);

        string.Append(s); // fputs(s, stdout);
        lua_pop(L, 1);  /* pop result */
    }

    LOGRAW(String("Lua: ") + string); // fputs("\n", stdout);

    return 0;
}

bool LuaScript::FindFunction(const String& functionName)
{
    Vector<String> splitedNames = functionName.Split('.');

    String currentName = splitedNames.Front();
    lua_getglobal(luaState_, currentName.CString());

    if (splitedNames.Size() > 1)
    {
        if (!lua_istable(luaState_, -1))
        {
            ErrorDialog("Can Not Find Lua Table", String("Table Name = '") + currentName + "'.");
            return false;
        }

        for (unsigned i = 1; i < splitedNames.Size() - 1; ++i)
        {
            currentName = currentName + "." + splitedNames[i];
            lua_getfield(luaState_, -1, splitedNames[i].CString());
            if (!lua_istable(luaState_, -1))
            {
                ErrorDialog("Can Not Find Lua Table", String("Table Name = '") + currentName + "'.");
                return false;
            }
        }

        currentName = currentName + "." + splitedNames.Back().CString();
        lua_getfield(luaState_, -1, splitedNames.Back().CString());
    }

    if (!lua_isfunction(luaState_, -1))
    {
        ErrorDialog("Can Not Find Lua Function", String("Function Name = '") + currentName + "'.");
        return false;
    }

    return true;
}

void LuaScript::HandleEvent(StringHash eventType, VariantMap& eventData)
{
    const HashSet<String>& functionNames = eventTypeToFunctionNameMap_[eventType];
    for (HashSet<String>::ConstIterator i = functionNames.Begin(); i != functionNames.End(); ++i)
        CallEventHandler(*i, eventType, eventData);
}

void LuaScript::HandleObjectEvent(StringHash eventType, VariantMap& eventData)
{
    Object* object = GetEventSender();
    const HashSet<String>& functionNames = objectToEventTypeToFunctionNameMap_[object][eventType];
    for (HashSet<String>::ConstIterator i = functionNames.Begin(); i != functionNames.End(); ++i)
        CallEventHandler(*i, eventType, eventData);
}

void LuaScript::HandleConsoleCommand(StringHash eventType, VariantMap& eventData)
{
    using namespace ConsoleCommand;
    ExecuteString(eventData[P_COMMAND].GetString());
}

void LuaScript::CallEventHandler(const String& functionName, StringHash eventType, VariantMap& eventData )
{
    int top = lua_gettop(luaState_);
    if (!FindFunction(functionName))
    {
        lua_settop(luaState_, top);
        return;
    }

    tolua_pushusertype(luaState_, (void*)&eventType, "StringHash");
    tolua_pushusertype(luaState_, (void*)&eventData, "VariantMap");

    if (lua_pcall(luaState_, 2, 0, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        ErrorDialog("Execute Lua Function Failed", message);
        lua_settop(luaState_, top);
        return;
    }
}

Context* GetContext()
{
    return currentContext_;
}

}
