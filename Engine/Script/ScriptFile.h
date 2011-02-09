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

#include <set>
#include <vector>

class ScriptEngine;
class ScriptInstance;
class Variant;
class asIObjectType;
class asIScriptContext;
class asIScriptEngine;
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
    
    //! Load resource. Throw exception on error
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    //! Add an event handler. Called by script exposed version of subscribeToEvent()
    virtual void addEventHandler(StringHash eventType, const std::string& handlerName);
    
    //! Query for a function by declaration and execute if found
    bool execute(const std::string& declaration, const std::vector<Variant>& parameters = std::vector<Variant>());
    //! Execute a function
    bool execute(asIScriptFunction* function, const std::vector<Variant>& parameters = std::vector<Variant>());
    //! Query for an object method by declaration and execute if found
    bool execute(asIScriptObject* object, const std::string& declaration, const std::vector<Variant>& parameters =
        std::vector<Variant>());
    //! Execute an object method
    bool execute(asIScriptObject* object, asIScriptFunction* method, const std::vector<Variant>& parameters = std::vector<Variant>());
    //! Create a script object
    asIScriptObject* createObject(const std::string& className);
    
    //! Return script engine
    ScriptEngine* getScriptEngine() const { return mScriptEngine; }
    //! Return script module
    asIScriptModule* getScriptModule() const { return mScriptModule; }
    //! Return a function by declaration. Will be stored to a search cache so that further searches should be faster
    asIScriptFunction* getFunction(const std::string& declaration);
    //! Return an object method by declaration
    asIScriptFunction* getMethod(asIScriptObject* object, const std::string& declaration);
    //! Return whether script compiled successfully
    bool isCompiled() const { return mCompiled; }
    
    //! Add script instance to keep track of in case of script reload
    void addScriptInstance(ScriptInstance* instance);
    //! Remove script instance to keep track of
    void removeScriptInstance(ScriptInstance* instance);
    
private:
    //! Add a script section, checking for includes recursively
    void addScriptSection(asIScriptEngine* engine, Deserializer& source, ResourceCache* cache);
    //! Set parameters for a function or method
    void setParameters(asIScriptContext* context, asIScriptFunction* function, const std::vector<Variant>& parameters);
    //! Handle an event with a handler in script
    void handleScriptEvent(StringHash eventType, VariantMap& eventData);
    //! Clear function-to-file mappings when script module is discarded
    void clearFunctionToFileMappings();
    
    //! Script engine
    SharedPtr<ScriptEngine> mScriptEngine;
    //! Script module
    asIScriptModule* mScriptModule;
    //! Compiled flag
    bool mCompiled;
    //! Encountered include files during script file loading
    std::set<std::string> mAllIncludeFiles;
    //! Search cache for checking whether script classes implement "ScriptObject" interface
    std::map<asIObjectType*, bool> mCheckedClasses;
    //! Search cache for functions
    std::map<std::string, asIScriptFunction*> mFunctions;
    //! Search cache for methods
    std::map<asIObjectType*, std::map<std::string, asIScriptFunction*> > mMethods;
    //! ScriptInstances that have created objects from this script file
    std::vector<ScriptInstance*> mScriptInstances;
};

//! Get currently executing script file
ScriptFile* getScriptContextFile();
//! Get current script execution nesting level
unsigned getScriptNestingLevel();
//! Return highest script execution nesting level, optionally reset it
unsigned getHighestScriptNestingLevel(bool reset = true);

#endif // SCRIPT_SCRIPTFILE_H
