//
// Copyright (c) 2008-2016 the Urho3D project.
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

LuaScriptEventInvoker::~LuaScriptEventInvoker()
{
}

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
    LuaFunction* function = static_cast<LuaFunction*>(GetEventHandler()->GetUserData());
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
