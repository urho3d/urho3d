//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#ifndef SCRIPT_SCRIPTFILE_H
#define SCRIPT_SCRIPTFILE_H

#include "Resource.h"
#include "ScriptEventListener.h"
#include "SharedPtr.h"
#include "Variant.h"

#include <vector>

class ScriptEngine;
class Variant;
class asIScriptContext;
class asIScriptFunction;
class asIScriptModule;
class asIScriptObject;

//! A script file resource
class ScriptFile : public Resource, public ScriptEventListener
{
    DEFINE_TYPE(ScriptFile);
    
public:
    //! Construct with script engine pointer and name
    ScriptFile(ScriptEngine* scriptEngine, const std::string& name = std::string());
    //! Destruct
    virtual ~ScriptFile();
    
    //! Load resource
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    //! Add an event handler. Called by script exposed subscribeToEvent() function
    virtual void addEventHandler(StringHash eventType, const std::string& handlerName);
    
    //! Query for a function by declaration and execute if found. If context is null, use the immediate context
    bool execute(const std::string& declaration, asIScriptContext* context = 0, const std::vector<Variant>& parameters = std::vector<Variant>());
    //! Execute a function. If context is null, use the immediate context
    bool execute(asIScriptFunction* function, asIScriptContext* context = 0, const std::vector<Variant>& parameters = std::vector<Variant>());
    //! Query for an object method by declaration and execute if found. If context is null, use the immediate context
    bool execute(asIScriptObject* object, const std::string& declaration, asIScriptContext* context = 0, const std::vector<Variant>& parameters = std::vector<Variant>());
    //! Execute an object method. If context is null, use the immediate context
    bool execute(asIScriptObject* object, asIScriptFunction* method, asIScriptContext* context = 0, const std::vector<Variant>& parameters = std::vector<Variant>());
    //! Create a script object. If context is null, use the immediate context
    asIScriptObject* createObject(const std::string& className, asIScriptContext* context = 0);
    
    //! Return script engine
    ScriptEngine* getScriptEngine() const { return mScriptEngine; }
    //! Return script module
    asIScriptModule* getScriptModule() const { return mScriptModule; }
    //! Return a function by declaration
    asIScriptFunction* getFunction(const std::string& declaration) const;
    //! Return an object method by declaration
    asIScriptFunction* getMethod(asIScriptObject* object, const std::string& declaration) const;
    //! Return whether script compiled successfully
    bool isCompiled() const { return mCompiled; }
    
private:
    //! Set parameters for a function or method
    void setParameters(asIScriptContext* context, asIScriptFunction* function, const std::vector<Variant>& parameters);
    //! Handle an event with a handler in script
    void handleScriptEvent(StringHash eventType, VariantMap& eventData);
    
    //! Script engine
    SharedPtr<ScriptEngine> mScriptEngine;
    //! Script module
    asIScriptModule* mScriptModule;
    //! Event handler script context
    asIScriptContext* mScriptContext;
    //! Compiled flag
    bool mCompiled;
};

//! Get last script file that is executing or has executed script code
ScriptFile* getLastScriptFile();

#endif // SCRIPT_SCRIPTFILE_H
