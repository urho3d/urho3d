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

#include "../Scene/Component.h"
#include "../Script/ScriptEventListener.h"

class asIScriptFunction;
class asIScriptObject;

namespace Urho3D
{

class Script;
class ScriptFile;

/// Inbuilt scripted component methods.
enum ScriptInstanceMethod
{
    METHOD_START = 0,
    METHOD_STOP,
    METHOD_DELAYEDSTART,
    METHOD_UPDATE,
    METHOD_POSTUPDATE,
    METHOD_FIXEDUPDATE,
    METHOD_FIXEDPOSTUPDATE,
    METHOD_LOAD,
    METHOD_SAVE,
    METHOD_READNETWORKUPDATE,
    METHOD_WRITENETWORKUPDATE,
    METHOD_APPLYATTRIBUTES,
    METHOD_TRANSFORMCHANGED,
    MAX_SCRIPT_METHODS
};

/// %Script object component.
class URHO3D_API ScriptInstance : public Component, public ScriptEventListener
{
    OBJECT(ScriptInstance);

public:
    /// Construct.
    ScriptInstance(Context* context);
    /// Destruct.
    virtual ~ScriptInstance();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Handle attribute write access.
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& src);
    /// Handle attribute read access.
    virtual void OnGetAttribute(const AttributeInfo& attr, Variant& dest) const;
    /// Return attribute descriptions, or null if none defined.
    virtual const Vector<AttributeInfo>* GetAttributes() const { return &attributeInfos_; }
    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    virtual void ApplyAttributes();
    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled();

    /// Add a scripted event handler.
    virtual void AddEventHandler(StringHash eventType, const String& handlerName);
    /// Add a scripted event handler for a specific sender.
    virtual void AddEventHandler(Object* sender, StringHash eventType, const String& handlerName);
    /// Remove a scripted event handler.
    virtual void RemoveEventHandler(StringHash eventType);
    /// Remove a scripted event handler for a specific sender.
    virtual void RemoveEventHandler(Object* sender, StringHash eventType);
    /// Remove all scripted event handlers for a specific sender.
    virtual void RemoveEventHandlers(Object* sender);
    /// Remove all scripted event handlers.
    virtual void RemoveEventHandlers();
    /// Remove all scripted event handlers, except those listed.
    virtual void RemoveEventHandlersExcept(const PODVector<StringHash>& exceptions);

    /// Create object of certain class from the script file. Return true if successful.
    bool CreateObject(ScriptFile* scriptFile, const String& className);
    /// Set script file only. Recreate object if necessary.
    void SetScriptFile(ScriptFile* scriptFile);
    /// Set class name only. Recreate object if necessary.
    void SetClassName(const String& className);
    /// Query for a method by declaration and execute. Log an error if not found.
    bool Execute(const String& declaration, const VariantVector& parameters = Variant::emptyVariantVector);
    /// Execute a method.
    bool Execute(asIScriptFunction* method, const VariantVector& parameters = Variant::emptyVariantVector);
    /// Add a delay-executed method call, optionally repeating.
    void DelayedExecute(float delay, bool repeat, const String& declaration, const VariantVector& parameters = Variant::emptyVariantVector);
    /// Clear pending delay-executed method calls. If empty declaration given, clears all.
    void ClearDelayedExecute(const String& declaration = String::EMPTY);

    /// Return script file.
    ScriptFile* GetScriptFile() const { return scriptFile_; }
    /// Return script object.
    asIScriptObject* GetScriptObject() const { return scriptObject_; }
    /// Return class name.
    const String& GetClassName() const { return className_; }
    /// Check if the object is derived from a class.
    bool IsA(const String& className) const;
    /// Check if has a method.
    bool HasMethod(const String& declaration) const;

    /// Set script file attribute.
    void SetScriptFileAttr(const ResourceRef& value);
    /// Set delayed method calls attribute.
    void SetDelayedCallsAttr(const PODVector<unsigned char>& value);
    /// Set fixed update time accumulator attribute.
    void SetFixedUpdateAccAttr(float value);
    /// Set script file serialization attribute by calling a script function.
    void SetScriptDataAttr(const PODVector<unsigned char>& data);
    /// Set script network serialization attribute by calling a script function.
    void SetScriptNetworkDataAttr(const PODVector<unsigned char>& data);
    /// Return script file attribute.
    ResourceRef GetScriptFileAttr() const;
    /// Return delayed method calls attribute.
    PODVector<unsigned char> GetDelayedCallsAttr() const;
    /// Return fixed update time accumulator attribute.
    float GetFixedUpdateAccAttr() const;
    /// Get script file serialization attribute by calling a script function.
    PODVector<unsigned char> GetScriptDataAttr() const;
    /// Get script network serialization attribute by calling a script function.
    PODVector<unsigned char> GetScriptNetworkDataAttr() const;

protected:
    /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);

private:
    /// (Re)create the script object and check for supported methods if successfully created.
    void CreateObject();
    /// Release the script object.
    void ReleaseObject();
    /// Check for supported script methods.
    void GetScriptMethods();
    /// Check for script attributes.
    void GetScriptAttributes();
    /// Clear supported script methods.
    void ClearScriptMethods();
    /// Clear attributes to C++ side attributes only.
    void ClearScriptAttributes();
    /// Subscribe/unsubscribe from scene updates as necessary.
    void UpdateEventSubscription();
    /// Handle scene update event.
    void HandleSceneUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle scene post-update event.
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);
#ifdef URHO3D_PHYSICS
    /// Handle physics pre-step event.
    void HandlePhysicsPreStep(StringHash eventType, VariantMap& eventData);
    /// Handle physics post-step event.
    void HandlePhysicsPostStep(StringHash eventType, VariantMap& eventData);
#endif
    /// Handle an event in script.
    void HandleScriptEvent(StringHash eventType, VariantMap& eventData);
    /// Handle script file reload start.
    void HandleScriptFileReload(StringHash eventType, VariantMap& eventData);
    /// Handle script file reload finished.
    void HandleScriptFileReloadFinished(StringHash eventType, VariantMap& eventData);

    /// Script subsystem.
    SharedPtr<Script> script_;
    /// Script file.
    WeakPtr<ScriptFile> scriptFile_;
    /// Script object.
    asIScriptObject* scriptObject_;
    /// Class name.
    String className_;
    /// Pointers to supported inbuilt methods.
    asIScriptFunction* methods_[MAX_SCRIPT_METHODS];
    /// Delayed method calls.
    Vector<DelayedCall> delayedCalls_;
    /// Attributes, including script object variables.
    Vector<AttributeInfo> attributeInfos_;
    /// Storage for unapplied node and component ID attributes
    HashMap<AttributeInfo*, unsigned> idAttributes_;
    /// Subscribed to scene update events flag.
    bool subscribed_;
    /// Subscribed to scene post and fixed update events flag.
    bool subscribedPostFixed_;
};

/// Return the Urho3D context of the active script context.
URHO3D_API Context* GetScriptContext();
/// Return the ScriptInstance of the active script context.
URHO3D_API ScriptInstance* GetScriptContextInstance();
/// Return the scene node of the active script context.
URHO3D_API Node* GetScriptContextNode();
/// Return the scene of the active script context.
URHO3D_API Scene* GetScriptContextScene();
/// Return the event listener of the active script context.
URHO3D_API ScriptEventListener* GetScriptContextEventListener();
/// Return the event listener of the active script context as an Object pointer.
URHO3D_API Object* GetScriptContextEventListenerObject();

}
