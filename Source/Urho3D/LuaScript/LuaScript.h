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
#include "../Core/Object.h"
#include "../LuaScript/LuaScriptEventListener.h"

struct lua_State;

namespace Urho3D
{

extern const char* LOGIC_CATEGORY;

class LuaFunction;
class LuaScriptEventInvoker;
class Scene;

/// Lua script subsystem.
class URHO3D_API LuaScript : public Object, public LuaScriptEventListener
{
    OBJECT(LuaScript);

public:
    /// Construct.
    LuaScript(Context* context);
    /// Destruct.
    ~LuaScript();

    /// Add a scripted event handler by function.
    virtual void AddEventHandler(const String& eventName, int functionIndex);
    /// Add a scripted event handler by function name.
    virtual void AddEventHandler(const String& eventName, const String& functionName);
    /// Add a scripted event handler by function for a specific sender.
    virtual void AddEventHandler(Object* sender, const String& eventName, int functionIndex);
    /// Add a scripted event handler by function name for a specific sender.
    virtual void AddEventHandler(Object* sender, const String& eventName, const String& functionName);
    /// Remove a scripted event handler.
    virtual void RemoveEventHandler(const String& eventName);
    /// Remove a scripted event handler for a specific sender.
    virtual void RemoveEventHandler(Object* sender, const String& eventName);
    /// Remove all scripted event handlers for a specific sender.
    virtual void RemoveEventHandlers(Object* sender);
    /// Remove all scripted event handlers.
    virtual void RemoveAllEventHandlers();
    /// Remove all scripted event handlers, except those listed.
    virtual void RemoveEventHandlersExcept(const Vector<String>& exceptionNames);

    /// Execute script file. Return true if successful.
    bool ExecuteFile(const String& fileName);
    /// Execute script string. Return true if successful.
    bool ExecuteString(const String& string);
    /// Load script file on file system (i.e. not from resource cache). Return true if successful.
    bool LoadRawFile(const String& fileName);
    /// Load and execute script file on file system (i.e. not from resource cache). Return true if successful.
    bool ExecuteRawFile(const String& fileName);
    /// Execute script function.
    bool ExecuteFunction(const String& functionName);
    /// Send event.
    void SendEvent(const String& eventName, VariantMap& eventData);
    /// Set whether to execute engine console commands as script code.
    void SetExecuteConsoleCommands(bool enable);

    /// Return Lua state.
    lua_State* GetState() const { return luaState_; }
    /// Return Lua function by function stack index.
    LuaFunction* GetFunction(int functionIndex);
    /// Return Lua function by function name.
    LuaFunction* GetFunction(const String& functionName, bool silentIfNotfound = false);
    /// Return whether is executing engine console commands as script code.
    bool GetExecuteConsoleCommands() const { return executeConsoleCommands_; }

private:
    /// Register loader.
    void RegisterLoader();
    /// Replace print.
    void ReplacePrint();
    /// Handle post update.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle a console command event.
    void HandleConsoleCommand(StringHash eventType, VariantMap& eventData);
    /// Push script function.
    bool PushScriptFunction(const String& functionName, bool silentIfNotfound = false);

    /// At panic.
    static int AtPanic(lua_State* L);
    /// Loader.
    static int Loader(lua_State* L);
    /// Print function.
    static int Print(lua_State* L);

    /// Lua state.
    lua_State* luaState_;
    /// Event invoker.
    SharedPtr<LuaScriptEventInvoker> eventInvoker_;
    /// Coroutine update function.
    LuaFunction* coroutineUpdate_;
    /// Flag for executing engine console commands as script code. Default to true.
    bool executeConsoleCommands_;
    /// Function pointer to function map.
    HashMap<const void*, SharedPtr<LuaFunction> > functionPointerToFunctionMap_;
    /// Function name to function map.
    HashMap<String, SharedPtr<LuaFunction> > functionNameToFunctionMap_;
};

/// Register Lua script library objects.
void URHO3D_API RegisterLuaScriptLibrary(Context* context);

}
