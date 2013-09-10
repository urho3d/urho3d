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

#include "Component.h"

struct lua_State;

namespace Urho3D
{

class LuaScript;

/// Lua instance.
class URHO3D_API LuaScriptInstance : public Component
{
    OBJECT(LuaScriptInstance);

public:
    /// Construct.
    LuaScriptInstance(Context* context);
    /// Destruct.
    ~LuaScriptInstance();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Create script object.
    bool CreateObject(const String& objectType);

    /// Script subscribe event.
    void ScriptSubscribeToEvent(const String& eventName, const String& functionName);

protected:
    /// Handle event.
    void HandleEvent(StringHash eventType, VariantMap& eventData);

    /// Call event handler.
    void CallEventHandler(int functionRef, StringHash eventType, VariantMap& eventData);

private:
    // Lua Script.
    LuaScript* luaScript_;

    /// Lua state.
    lua_State* luaState_;

    /// Object type.
    String objectType_;

    /// Script object ref.
    int scriptObjectRef_;

    /// Event type to function ref map.
    HashMap<StringHash, int> eventTypeToFunctionRefMap_;
};

}
