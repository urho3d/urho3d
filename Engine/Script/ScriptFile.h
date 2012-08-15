//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include "HashSet.h"
#include "Resource.h"
#include "ScriptEventListener.h"

class asIObjectType;
class asIScriptContext;
class asIScriptEngine;
class asIScriptFunction;
class asIScriptModule;
class asIScriptObject;

namespace Urho3D
{

class Script;
class ScriptInstance;
class Variant;

/// %Script file resource.
class ScriptFile : public Resource, public ScriptEventListener
{
    OBJECT(ScriptFile);
    
public:
    /// Construct.
    ScriptFile(Context* context);
    /// Destruct.
    virtual ~ScriptFile();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful.
    virtual bool Load(Deserializer& source);
    /// Add an event handler. Called by script exposed version of SubscribeToEvent().
    virtual void AddEventHandler(StringHash eventType, const String& handlerName);
    /// Add an event handler for a specific sender. Called by script exposed version of SubscribeToEvent().
    virtual void AddEventHandler(Object* sender, StringHash eventType, const String& handlerName);
    
    /// Query for a function by declaration and execute if found.
    bool Execute(const String& declaration, const VariantVector& parameters = VariantVector(), bool unprepare = true);
    /// Execute a function.
    bool Execute(asIScriptFunction* function, const VariantVector& parameters = VariantVector(), bool unprepare = true);
    /// Query for an object method by declaration and execute if found.
    bool Execute(asIScriptObject* object, const String& declaration, const VariantVector& parameters =
        VariantVector(), bool unprepare = true);
    /// Execute an object method.
    bool Execute(asIScriptObject* object, asIScriptFunction* method, const VariantVector& parameters = VariantVector(),
        bool unprepare = true);
    /// Create a script object.
    asIScriptObject* CreateObject(const String& className);
    
    /// Return script module.
    asIScriptModule* GetScriptModule() const { return scriptModule_; }
    /// Return a function by declaration. Will be stored to a search cache so that further searches should be faster.
    asIScriptFunction* GetFunction(const String& declaration);
    /// Return an object method by declaration.
    asIScriptFunction* GetMethod(asIScriptObject* object, const String& declaration);
    /// Return whether script compiled successfully.
    bool IsCompiled() const { return compiled_; }
    
private:
    /// Add a script section, checking for includes recursively. Return true if successful.
    bool AddScriptSection(asIScriptEngine* engine, Deserializer& source);
    /// Set parameters for a function or method.
    void SetParameters(asIScriptContext* context, asIScriptFunction* function, const VariantVector& parameters);
    /// Release the script module.
    void ReleaseModule();
    /// Handle an event in script.
    void HandleScriptEvent(StringHash eventType, VariantMap& eventData);
    
    /// Script subsystem.
    SharedPtr<Script> script_;
    /// Script module.
    asIScriptModule* scriptModule_;
    /// Compiled flag.
    bool compiled_;
    /// Encountered include files during script file loading.
    HashSet<String> includeFiles_;
    /// Search cache for checking whether script classes implement "ScriptObject" interface.
    HashMap<asIObjectType*, bool> validClasses_;
    /// Search cache for functions.
    HashMap<String, asIScriptFunction*> functions_;
    /// Search cache for methods.
    HashMap<asIObjectType*, HashMap<String, asIScriptFunction*> > methods_;
};

/// Get currently executing script file.
ScriptFile* GetScriptContextFile();

}
