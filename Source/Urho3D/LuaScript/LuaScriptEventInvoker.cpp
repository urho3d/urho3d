// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../LuaScript/LuaFunction.h"
#include "../LuaScript/LuaScriptEventInvoker.h"
#include "../LuaScript/LuaScriptInstance.h"

#include "../DebugNew.h"

namespace Urho3D
{

LuaScriptEventInvoker::LuaScriptEventInvoker(Context* context) :
    Object(context)
{
}

LuaScriptEventInvoker::LuaScriptEventInvoker(LuaScriptInstance* instance) :
    Object(instance->GetContext()),
    instance_(instance)
{
}

LuaScriptEventInvoker::~LuaScriptEventInvoker() = default;

void LuaScriptEventInvoker::AddEventHandler(Object* sender, const StringHash& eventType, LuaFunction* function)
{
    if (!function)
        return;

    if (sender)
        SubscribeToEvent(sender, eventType, URHO3D_HANDLER_USERDATA(LuaScriptEventInvoker, HandleLuaScriptEvent, function));
    else
        SubscribeToEvent(eventType, URHO3D_HANDLER_USERDATA(LuaScriptEventInvoker, HandleLuaScriptEvent, function));
}

void LuaScriptEventInvoker::HandleLuaScriptEvent(StringHash eventType, VariantMap& eventData)
{
    auto* function = static_cast<LuaFunction*>(GetEventHandler()->GetUserData());
    if (!function)
        return;

    // Keep instance alive during invoking
    SharedPtr<LuaScriptInstance> instance(instance_);
    if (function->BeginCall(instance))      // instance may be null when invoking a procedural event handler
    {
        function->PushUserType(eventType, "StringHash");
        function->PushUserType(eventData, "VariantMap");
        function->EndCall();
    }
}

}
