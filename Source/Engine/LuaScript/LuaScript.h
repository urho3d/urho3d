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

#pragma once

#include "Context.h"
#include "Object.h"

struct lua_State;

namespace Urho3D
{

extern const char* LOGIC_CATEGORY;

class LuaFunction;
class Scene;

/// Lua script subsystem.
class URHO3D_API LuaScript : public Object
{
    OBJECT(LuaScript);

public:
    /// Construct.
    LuaScript(Context* context);
    /// Destruct.
    ~LuaScript();

    /// Execute script file. Return true if successful.
    bool ExecuteFile(const String& fileName);
    /// Execute script string. Return true if successful.
    bool ExecuteString(const String& string);
    /// Execute script function.
    bool ExecuteFunction(const String& functionName);
    /// Script send event.
    void ScriptSendEvent(const String& eventName, VariantMap& eventData);
    /// Script subscribe to an event that can by send by any sender.
    void ScriptSubscribeToEvent(const String& eventName, const String& functionName);
    /// Script unsubscribe from an event.
    void ScriptUnsubscribeFromEvent(const String& eventName, const String& functionName = String::EMPTY);
    /// Script unsubscribe from all events.
    void ScriptUnsubscribeFromAllEvents();
    /// Script subscribe to a specific sender's event.
    void ScriptSubscribeToEvent(void* sender, const String& eventName, const String& functionName);
    /// Script unsubscribe from a specific sender's event.
    void ScriptUnsubscribeFromEvent(void* sender, const String& eventName, const String& functionName = String::EMPTY);
    /// Script unsubscribe from a specific sender's all events.
    void ScriptUnsubscribeFromEvents(void* sender);
    /// Set whether to execute engine console commands as script code. Default true.
    void SetExecuteConsoleCommands(bool enable);

    /// Return Lua state.
    lua_State* GetState() const { return luaState_; }
    /// Return Lua function.
    WeakPtr<LuaFunction> GetFunction(const String& functionName, bool silentIfNotfound = false);
    /// Return whether is executing engine console commands as script code.
    bool GetExecuteConsoleCommands() const { return executeConsoleCommands_; }
    
private:
    /// Register loader.
    void RegisterLoader();
    /// Replace print.
    void ReplacePrint();
    /// Handle event.
    void HandleEvent(StringHash eventType, VariantMap& eventData);
    /// Handle object event.
    void HandleObjectEvent(StringHash eventType, VariantMap& eventData);
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
    /// Coroutine update function.
    WeakPtr<LuaFunction> coroutineUpdate_;
    /// Function name to function map.
    HashMap<String, SharedPtr<LuaFunction> > functionNameToFunctionMap_;
    /// Typedef Lua function vector.
    typedef Vector<WeakPtr<LuaFunction> > LuaFunctionVector;
    /// Event handle functions.
    HashMap<StringHash, LuaFunctionVector> eventHandleFunctions_;
    /// Object event handle functions.
    HashMap<Object*, HashMap<StringHash, LuaFunctionVector> > objectHandleFunctions_;
    /// Internally used events, which should not be unsubscribed from.
    PODVector<StringHash> internalEvents_;
    /// Flag for executing engine console commands as script code.
    bool executeConsoleCommands_;
};

/// Register Lua script library objects.
void URHO3D_API RegisterLuaScriptLibrary(Context* context);

}
