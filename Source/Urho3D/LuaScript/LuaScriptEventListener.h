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

#include "../Core/Object.h"

namespace Urho3D
{

/// Lua script event listener.
class URHO3D_API LuaScriptEventListener
{
public:
    /// Destruct.
    virtual ~LuaScriptEventListener() {};

    /// Add a scripted event handler by function.
    virtual void AddEventHandler(const String& eventName, int functionIndex) = 0;
    /// Add a scripted event handler by function name.
    virtual void AddEventHandler(const String& eventName, const String& functionName) = 0;
    /// Add a scripted event handler by function for a specific sender.
    virtual void AddEventHandler(Object* sender, const String& eventName, int functionIndex) = 0;
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
};

}
