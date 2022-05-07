// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

class LuaFunction;
class LuaScriptInstance;

/// Lua script event invoker.
class LuaScriptEventInvoker : public Object
{
    URHO3D_OBJECT(LuaScriptEventInvoker, Object);

public:
    /// Construct.
    explicit LuaScriptEventInvoker(Context* context);
    /// Construct from LuaScriptInstance.
    explicit LuaScriptEventInvoker(LuaScriptInstance* instance);
    /// Destruct.
    ~LuaScriptEventInvoker() override;

    /// Add a scripted event handler.
    void AddEventHandler(Object* sender, const StringHash& eventType, LuaFunction* function);

private:
    /// Handle script event in Lua script.
    void HandleLuaScriptEvent(StringHash eventType, VariantMap& eventData);

    /// Lua script instance.
    WeakPtr<LuaScriptInstance> instance_;
};

}
