// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Core/Object.h"

namespace Urho3D
{

/// Lua script event listener.
class URHO3D_API LuaScriptEventListener
{
public:
    /// Destruct.
    virtual ~LuaScriptEventListener() = default;

    /// Add a scripted event handler by function at the given stack index.
    virtual void AddEventHandler(const String& eventName, int index) = 0;
    /// Add a scripted event handler by function name.
    virtual void AddEventHandler(const String& eventName, const String& functionName) = 0;
    /// Add a scripted event handler by function at the given stack index for a specific sender.
    virtual void AddEventHandler(Object* sender, const String& eventName, int index) = 0;
    /// Add a scripted event handler by function name for a specific sender.
    virtual void AddEventHandler(Object* sender, const String& eventName, const String& functionName) = 0;
    /// Remove a scripted event handler.
    virtual void RemoveEventHandler(const String& eventName) = 0;
    /// Remove a scripted event handler for a specific sender.
    virtual void RemoveEventHandler(Object* sender, const String& eventName) = 0;
    /// Remove all scripted event handlers for a specific sender.
    virtual void RemoveEventHandlers(Object* sender) = 0;
    /// Remove all scripted event handlers.
    virtual void RemoveAllEventHandlers() = 0;
    /// Remove all scripted event handlers, except those listed.
    virtual void RemoveEventHandlersExcept(const Vector<String>& exceptionNames) = 0;
    /// Return whether has subscribed to an event.
    virtual bool HasEventHandler(const String& eventName) const = 0;
    /// Return whether has subscribed to a specific sender's event.
    virtual bool HasEventHandler(Object* sender, const String& eventName) const = 0;
};

}
