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

#pragma once

#include "Component.h"
#include "ScriptEventListener.h"

class Script;
class ScriptFile;
class asIScriptFunction;
class asIScriptObject;

/// Inbuilt scripted component methods
enum ScriptInstanceMethod
{
    METHOD_START = 0,
    METHOD_STOP,
    METHOD_UPDATE,
    METHOD_POSTUPDATE,
    METHOD_FIXEDUPDATE,
    METHOD_FIXEDPOSTUPDATE,
    METHOD_LOAD,
    METHOD_SAVE,
    METHOD_POSTLOAD,
    MAX_SCRIPT_METHODS
};

/// Delay-executed method call
struct DelayedMethodCall
{
    /// Delay time remaining until execution
    float delay_;
    /// Method declaration
    std::string declaration_;
    /// Parameters
    VariantVector parameters_;
};

/// Scripted component
class ScriptInstance : public Component, public ScriptEventListener
{
    OBJECT(ScriptInstance);
    
public:
    /// Construct
    ScriptInstance(Context* context);
    /// Destruct
    virtual ~ScriptInstance();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Handle attribute write access
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& value);
    /// Handle attribute read access
    virtual Variant OnGetAttribute(const AttributeInfo& attr);
    /// Perform post-load after the whole scene has been loaded
    virtual void PostLoad();
    /// Add an event handler. Called by script exposed version of SubscribeToEvent()
    virtual void AddEventHandler(StringHash eventType, const std::string& handlerName);
    /// Add an event handler for a specific sender. Called by script exposed version of SubscribeToEvent()
    virtual void AddEventHandler(Object* sender, StringHash eventType, const std::string& handlerName);
    
    /// Create object of certain class from the script file. Return true if successful
    bool CreateObject(ScriptFile* scriptFile, const std::string& className);
    /// Set script file only. Recreate object if necessary
    void SetScriptFile(ScriptFile* scriptFile);
    /// Set class name only. Recreate object if necessary
    void SetClassName(const std::string& className);
    /// Enable or disable scripted updates and event handlers
    void SetActive(bool active);
    /// Set fixed updates per second. 0 (default) uses the physics frame rate
    void SetFixedUpdateFps(int fps);
    /// Query for a method by declaration and execute if found
    bool Execute(const std::string& declaration, const VariantVector& parameters = VariantVector());
    /// Execute a method
    bool Execute(asIScriptFunction* method, const VariantVector& parameters = VariantVector());
    /// Add a delay-executed method call
    void DelayedExecute(float delay, const std::string& declaration, const VariantVector& parameters = VariantVector());
    /// Clear pending delay-executed method calls
    void ClearDelayedExecute();
    
    /// Return script file
    ScriptFile* GetScriptFile() const { return scriptFile_; }
    /// Return script object
    asIScriptObject* GetScriptObject() const { return scriptObject_; }
    /// Return class name
    const std::string& GetClassName() const { return className_; }
    /// Return whether scripted updates and event handlers are enabled
    bool IsActive() const { return active_; }
    /// Return fixed updates per second
    int GetFixedUpdateFps() const { return fixedUpdateFps_; }
    
private:
    /// (Re)create the script object and check for supported methods if successfully created
    void CreateObject();
    /// Release the script object
    void ReleaseObject();
    /// Clear supported methods
    void ClearMethods();
    /// Check for supported methods
    void GetSupportedMethods();
    /// Get script object's serialization data by calling a script function
    std::vector<unsigned char> GetScriptData() const;
    /// Set script object's serialization data by calling a script function
    void SetScriptData(std::vector<unsigned char> data);
    /// Handle scene update event
    void HandleSceneUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle scene post-update event
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle physics pre-step event
    void HandlePhysicsPreStep(StringHash eventType, VariantMap& eventData);
    /// Handle physics post-step event
    void HandlePhysicsPostStep(StringHash eventType, VariantMap& eventData);
    /// Handle an event in script
    void HandleScriptEvent(StringHash eventType, VariantMap& eventData);
    /// Handle script file reload start
    void HandleScriptFileReload(StringHash eventType, VariantMap& eventData);
    /// Handle script file reload finished
    void HandleScriptFileReloadFinished(StringHash eventType, VariantMap& eventData);
    
    /// Script subsystem
    SharedPtr<Script> script_;
    /// Script file
    WeakPtr<ScriptFile> scriptFile_;
    /// Script object
    asIScriptObject* scriptObject_;
    /// Class name
    std::string className_;
    /// Pointers to supported inbuilt methods
    asIScriptFunction* methods_[MAX_SCRIPT_METHODS];
    /// Active flag
    bool active_;
    /// Fixed update FPS
    int fixedUpdateFps_;
    /// Fixed update time interval
    float fixedUpdateInterval_;
    /// Fixed update time accumulator
    float fixedUpdateAcc_;
    /// Fixed post update time accumulator
    float fixedPostUpdateAcc_;
    /// Delayed method calls
    std::vector<DelayedMethodCall> delayedMethodCalls_;
};

/// Return the Urho3D context of the active script context
Context* GetScriptContext();
/// Return the ScriptInstance of the active script context
ScriptInstance* GetScriptContextInstance();
/// Return the scene node of the active script context
Node* GetScriptContextNode();
/// Return the scene of the active script context
Scene* GetScriptContextScene();
/// Return the event listener of the active script context
ScriptEventListener* GetScriptContextEventListener();
/// Return the event listener of the active script context as an Object pointer
Object* GetScriptContextEventListenerObject();
