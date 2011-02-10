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

#ifndef SCRIPT_SCRIPTINSTANCE_H
#define SCRIPT_SCRIPTINSTANCE_H

#include "Component.h"
#include "EventListener.h"
#include "Quaternion.h"
#include "ScriptEventListener.h"
#include "SharedPtr.h"

class Entity;
class PhysicsWorld;
class Scene;
class ScriptEngine;
class ScriptFile;
class asIScriptFunction;
class asIScriptObject;

//! Inbuilt scripted component methods
enum ScriptInstanceMethod
{
    METHOD_START = 0,
    METHOD_STOP,
    METHOD_UPDATE,
    METHOD_POSTUPDATE,
    METHOD_UPDATEFIXED,
    METHOD_POSTUPDATEFIXED,
    METHOD_SAVE,
    METHOD_LOAD,
    METHOD_POSTLOAD,
    METHOD_SAVEXML,
    METHOD_LOADXML,
    METHOD_WRITENETUPDATE,
    METHOD_READNETUPDATE,
    METHOD_POSTNETUPDATE,
    METHOD_INTERPOLATE,
    METHOD_GETCOMPONENTREFS,
    METHOD_GETRESOURCEREFS,
    MAX_SCRIPT_METHODS
};

//! Delay-executed method call
struct DelayedMethodCall
{
    //! Delay time remaining until execution
    float mDelay;
    //! Method declaration
    std::string mDeclaration;
    //! Parameters
    std::vector<Variant> mParameters;
};

//! A scripted component
class ScriptInstance : public Component, public ScriptEventListener
{
    DEFINE_TYPE(ScriptInstance);
    
public:
    //! Construct with script engine pointer and name
    ScriptInstance(ScriptEngine* scriptEngine, const std::string& name = std::string());
    //! Destruct
    virtual ~ScriptInstance();
    
    //! Write component state to a stream
    virtual void save(Serializer& dest);
    //! Read component state from a stream
    virtual void load(Deserializer& source, ResourceCache* cache);
    //! Write component state to an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read component state from an XML element
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Resolve component references after loading
    virtual void postLoad(ResourceCache* cache);
    //! Write a network update
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    //! Read a network update
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    //! Resolve component references after a network update
    virtual void postNetUpdate(ResourceCache* cache);
    //! Perform client-side visual smoothing
    virtual void interpolate(bool snapToEnd);
    //! Return component references
    virtual void getComponentRefs(std::vector<ComponentRef>& dest);
    //! Return resource references
    virtual void getResourceRefs(std::vector<Resource*>& dest);
    //! Add an event handler. Called by script exposed version of subscribeToEvent()
    virtual void addEventHandler(StringHash eventType, const std::string& handlerName);
    
    //! Set script file and class
    bool setScriptClass(ScriptFile* scriptFile, const std::string& className);
    //! Enable or disable scripted updates and event handlers
    void setEnabled(bool enable);
    //! Set fixed updates per second. 0 (default) uses the physics frame rate
    void setFixedUpdateFps(int fps);
    //! Query for a method by declaration and execute if found
    bool execute(const std::string& declaration, const std::vector<Variant>& parameters = std::vector<Variant>());
    //! Execute a method
    bool execute(asIScriptFunction* method, const std::vector<Variant>& parameters = std::vector<Variant>());
    //! Add a delay-executed method call
    void delayedExecute(float delay, const std::string& declaration, const std::vector<Variant>& parameters = std::vector<Variant>());
    //! Clear pending delay-executed method calls
    void clearDelayedExecute();
    
    //! Return script engine
    ScriptEngine* getScriptEngine() const { return mScriptEngine; }
    //! Return script file
    ScriptFile* getScriptFile() const { return mScriptFile; }
    //! Return script object
    asIScriptObject* getScriptObject() const { return mScriptObject; }
    //! Return class name
    const std::string& getClassName() const { return mClassName; }
    //! Return whether scripted updates and event handlers are enabled
    bool isEnabled() const { return mEnabled; }
    //! Return fixed updates per second
    int getFixedUpdateFps() const { return mFixedUpdateFps; }
    
    //! Create the script object. Check for supported methods and register self to the ScriptFile if successful
    bool createObject();
    //! Release the script object and unregister self from the ScriptFile
    void releaseObject();
    
private:
    //! Clear supported methods
    void clearMethods();
    //! Check for supported methods
    void getSupportedMethods();
    //! Handle scene update event
    void handleSceneUpdate(StringHash eventType, VariantMap& eventData);
    //! Handle scene post-update event
    void handleScenePostUpdate(StringHash eventType, VariantMap& eventData);
    //! Handle physics pre-step event
    void handlePhysicsPreStep(StringHash eventType, VariantMap& eventData);
    //! Handle physics post-step event
    void handlePhysicsPostStep(StringHash eventType, VariantMap& eventData);
    //! Handle an event with a handler in script
    void handleScriptEvent(StringHash eventType, VariantMap& eventData);
    
    //! Script engine
    SharedPtr<ScriptEngine> mScriptEngine;
    //! Script file
    WeakPtr<ScriptFile> mScriptFile;
    //! Script object
    asIScriptObject* mScriptObject;
    //! Class name
    std::string mClassName;
    //! Pointers to supported inbuilt methods
    asIScriptFunction* mMethods[MAX_SCRIPT_METHODS];
    //! Enabled flag
    bool mEnabled;
    //! Fixed update FPS
    int mFixedUpdateFps;
    //! Fixed update time interval
    float mFixedUpdateInterval;
    //! Fixed update time accumulator
    float mFixedUpdateTimer;
    //! Fixed post update time accumulator
    float mFixedPostUpdateTimer;
    //! Delayed method calls
    std::vector<DelayedMethodCall> mDelayedMethodCalls;
};

//! Return the ScriptInstance of the active context
ScriptInstance* getScriptContextInstance();
//! Return the entity of the active context
Entity* getScriptContextEntity();
//! Return the event listener of the active context
ScriptEventListener* getScriptContextEventListener();

#endif // SCRIPT_SCRIPTINSTANCE_H
