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

class asIScriptObject;

namespace Urho3D
{

/// Delay-executed function or method call.
struct DelayedCall
{
   /// Period for repeating calls.
    float period_;
    /// Delay time remaining until execution.
    float delay_;
    /// Repeat flag.
    bool repeat_;
    /// Function declaration.
    String declaration_;
    /// Parameters.
    VariantVector parameters_;
};

/// Interface class for event listeners that forward events to script.
class URHO3D_API ScriptEventListener
{
public:
    /// Destruct
    virtual ~ScriptEventListener() {};

    /// Add an event handler. Called by script exposed version of SubscribeToEvent().
    virtual void AddEventHandler(StringHash eventType, const String& handlerName, asIScriptObject* receiver = 0) = 0;
    /// Add an event handler for a specific sender. Called by script exposed version of SubscribeToEvent().
    virtual void AddEventHandler(Object* sender, StringHash eventType, const String& handlerName, asIScriptObject* receiver = 0) = 0;
};

}
