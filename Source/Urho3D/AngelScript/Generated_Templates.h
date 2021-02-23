// DO NOT EDIT. This file is generated

#pragma once

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"

#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// explicit Component::Component(Context* context) | File: ../Scene/Component.h
static Component* Component_Component_Context_template()
{
    return new Component(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Component_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool_template(Component* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Object_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool_template(Object* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Resource::Resource(Context* context) | File: ../Resource/Resource.h
static Resource* Resource_Resource_Context_template()
{
    return new Resource(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Resource_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool_template(Resource* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

template <class T> void RegisterComponent(asIScriptEngine* engine, const char* className)
{
    // class Component | File: ../Scene/Component.h
    engine->RegisterObjectType(className, 0, asOBJ_REF);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour(className, asBEHAVE_ADDREF, "void f()", AS_METHODPR(T, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void AllocateNetworkState()", AS_METHODPR(T, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void ApplyAttributes()", AS_METHODPR(T, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit Component::Component(Context* context) | File: ../Scene/Component.h
    {
        String declFactory(String(className) + "@ f()");
        engine->RegisterObjectBehaviour(className, asBEHAVE_FACTORY, declFactory.CString(), AS_FUNCTION(Component_Component_Context_template), AS_CALL_CDECL);
    }
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(T, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "bool GetAnimationEnabled() const", AS_METHODPR(T, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_animationEnabled() const", AS_METHODPR(T, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "Variant GetAttribute(uint) const", AS_METHODPR(T, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "Variant get_attributes(uint) const", AS_METHODPR(T, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "Variant GetAttribute(const String&in) const", AS_METHODPR(T, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(T, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(T, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(T, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(T, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "Variant GetAttributeDefault(uint) const", AS_METHODPR(T, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "Variant get_attributeDefaults(uint) const", AS_METHODPR(T, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(T, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool GetBlockEvents() const", AS_METHODPR(T, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const String& GetCategory() const", AS_METHODPR(T, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_category() const", AS_METHODPR(T, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "Component@+ GetComponent(StringHash) const", AS_METHODPR(T, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "VariantMap& GetEventDataMap() const", AS_METHODPR(T, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "Object@+ GetEventSender() const", AS_METHODPR(T, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(T, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Variant& get_globalVar(StringHash) const", AS_METHODPR(T, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const VariantMap& GetGlobalVars() const", AS_METHODPR(T, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "const VariantMap& get_globalVars() const", AS_METHODPR(T, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "uint GetID() const", AS_METHODPR(T, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_id() const", AS_METHODPR(T, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(T, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "Node@+ GetNode() const", AS_METHODPR(T, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "Node@+ get_node() const", AS_METHODPR(T, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "uint GetNumAttributes() const", AS_METHODPR(T, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_numAttributes() const", AS_METHODPR(T, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "uint GetNumNetworkAttributes() const", AS_METHODPR(T, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(T, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(T, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(T, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "Scene@+ GetScene() const", AS_METHODPR(T, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(T, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "StringHash GetType() const", AS_METHODPR(T, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "StringHash get_type() const", AS_METHODPR(T, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const String& GetTypeName() const", AS_METHODPR(T, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_typeName() const", AS_METHODPR(T, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasEventHandlers() const", AS_METHODPR(T, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(T, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(T, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "bool IsEnabled() const", AS_METHODPR(T, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_enabled() const", AS_METHODPR(T, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "bool IsEnabledEffective() const", AS_METHODPR(T, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_enabledEffective() const", AS_METHODPR(T, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool IsInstanceOf(StringHash) const", AS_METHODPR(T, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "bool IsReplicated() const", AS_METHODPR(T, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_replicated() const", AS_METHODPR(T, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool IsTemporary() const", AS_METHODPR(T, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_temporary() const", AS_METHODPR(T, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool Load(Deserializer&)", AS_METHODPR(T, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "bool LoadJSON(const JSONValue&in)", AS_METHODPR(T, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "bool LoadXML(const XMLElement&in)", AS_METHODPR(T, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "void MarkNetworkUpdate()", AS_METHODPR(T, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(T, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(T, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(T, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "void OnSetEnabled()", AS_METHODPR(T, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "void PrepareNetworkUpdate()", AS_METHODPR(T, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(T, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(T, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod(className, "int Refs() const", AS_METHODPR(T, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_refs() const", AS_METHODPR(T, Refs, () const, int), AS_CALL_THISCALL);
    // static void Animatable::RegisterObject(Context* context) | File: ../Scene/Animatable.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour(className, asBEHAVE_RELEASE, "void f()", AS_METHODPR(T, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "void Remove()", AS_METHODPR(T, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(T, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void RemoveInstanceDefault()", AS_METHODPR(T, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void RemoveObjectAnimation()", AS_METHODPR(T, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void ResetToDefault()", AS_METHODPR(T, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "bool Save(Serializer&) const", AS_METHODPR(T, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool SaveDefaultAttributes() const", AS_METHODPR(T, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "bool SaveJSON(JSONValue&) const", AS_METHODPR(T, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "bool SaveXML(XMLElement&) const", AS_METHODPR(T, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SendEvent(StringHash)", AS_METHODPR(T, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(T, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetAnimationEnabled(bool)", AS_METHODPR(T, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_animationEnabled(bool)", AS_METHODPR(T, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetAnimationTime(float)", AS_METHODPR(T, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(T, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool set_attributes(uint, const Variant&in)", AS_METHODPR(T, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(T, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(T, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(T, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(T, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(T, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SetBlockEvents(bool)", AS_METHODPR(T, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "void SetEnabled(bool)", AS_METHODPR(T, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_enabled(bool)", AS_METHODPR(T, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(T, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(T, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void SetInstanceDefault(bool)", AS_METHODPR(T, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(T, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(T, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(T, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(T, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void SetTemporary(bool)", AS_METHODPR(T, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_temporary(bool)", AS_METHODPR(T, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromAllEvents()", AS_METHODPR(T, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Component_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool_template), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(T, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(T, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(T, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod(className, "int WeakRefs() const", AS_METHODPR(T, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_weakRefs() const", AS_METHODPR(T, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(T, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(T, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(T, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(T, className)
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(T, className)
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(T, className)
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(T, className)
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(T, className)
#endif
    RegisterSubclass<Animatable, T>(engine, "Animatable", className);
    RegisterSubclass<Serializable, T>(engine, "Serializable", className);
    RegisterSubclass<Object, T>(engine, "Object", className);
    RegisterSubclass<RefCounted, T>(engine, "RefCounted", className);
    RegisterSubclass<Component, T>(engine, "Component", className);
}

template <class T> void RegisterObject(asIScriptEngine* engine, const char* className)
{
    // class Object | File: ../Core/Object.h
    engine->RegisterObjectType(className, 0, asOBJ_REF);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour(className, asBEHAVE_ADDREF, "void f()", AS_METHODPR(T, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool GetBlockEvents() const", AS_METHODPR(T, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const String& GetCategory() const", AS_METHODPR(T, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_category() const", AS_METHODPR(T, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "VariantMap& GetEventDataMap() const", AS_METHODPR(T, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "Object@+ GetEventSender() const", AS_METHODPR(T, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(T, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Variant& get_globalVar(StringHash) const", AS_METHODPR(T, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const VariantMap& GetGlobalVars() const", AS_METHODPR(T, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "const VariantMap& get_globalVars() const", AS_METHODPR(T, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(T, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "StringHash GetType() const", AS_METHODPR(T, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "StringHash get_type() const", AS_METHODPR(T, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const String& GetTypeName() const", AS_METHODPR(T, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_typeName() const", AS_METHODPR(T, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasEventHandlers() const", AS_METHODPR(T, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(T, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(T, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool IsInstanceOf(StringHash) const", AS_METHODPR(T, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(T, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod(className, "int Refs() const", AS_METHODPR(T, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_refs() const", AS_METHODPR(T, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour(className, asBEHAVE_RELEASE, "void f()", AS_METHODPR(T, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SendEvent(StringHash)", AS_METHODPR(T, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(T, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SetBlockEvents(bool)", AS_METHODPR(T, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(T, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(T, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromAllEvents()", AS_METHODPR(T, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Object_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool_template), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(T, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(T, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(T, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod(className, "int WeakRefs() const", AS_METHODPR(T, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_weakRefs() const", AS_METHODPR(T, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(T, className)
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(T, className)
#endif
    RegisterSubclass<RefCounted, T>(engine, "RefCounted", className);
    RegisterSubclass<Object, T>(engine, "Object", className);
}

template <class T> void RegisterResource(asIScriptEngine* engine, const char* className)
{
    // class Resource | File: ../Resource/Resource.h
    engine->RegisterObjectType(className, 0, asOBJ_REF);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour(className, asBEHAVE_ADDREF, "void f()", AS_METHODPR(T, AddRef, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::BeginLoad(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "bool BeginLoad(Deserializer&)", AS_METHODPR(T, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "bool EndLoad()", AS_METHODPR(T, EndLoad, (), bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(T, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool GetBlockEvents() const", AS_METHODPR(T, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const String& GetCategory() const", AS_METHODPR(T, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_category() const", AS_METHODPR(T, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "VariantMap& GetEventDataMap() const", AS_METHODPR(T, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "Object@+ GetEventSender() const", AS_METHODPR(T, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(T, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Variant& get_globalVar(StringHash) const", AS_METHODPR(T, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const VariantMap& GetGlobalVars() const", AS_METHODPR(T, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "const VariantMap& get_globalVars() const", AS_METHODPR(T, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "uint GetMemoryUse() const", AS_METHODPR(T, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_memoryUse() const", AS_METHODPR(T, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "const String& GetName() const", AS_METHODPR(T, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_name() const", AS_METHODPR(T, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "StringHash GetNameHash() const", AS_METHODPR(T, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(T, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "StringHash GetType() const", AS_METHODPR(T, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "StringHash get_type() const", AS_METHODPR(T, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const String& GetTypeName() const", AS_METHODPR(T, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_typeName() const", AS_METHODPR(T, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "uint GetUseTimer()", AS_METHODPR(T, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_useTimer()", AS_METHODPR(T, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasEventHandlers() const", AS_METHODPR(T, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(T, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(T, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool IsInstanceOf(StringHash) const", AS_METHODPR(T, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "bool Load(Deserializer&)", AS_METHODPR(T, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "bool LoadFile(const String&in)", AS_METHODPR(T, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool Load(const String&in)", AS_METHODPR(T, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(T, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod(className, "int Refs() const", AS_METHODPR(T, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_refs() const", AS_METHODPR(T, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour(className, asBEHAVE_RELEASE, "void f()", AS_METHODPR(T, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "void ResetUseTimer()", AS_METHODPR(T, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // explicit Resource::Resource(Context* context) | File: ../Resource/Resource.h
    {
        String declFactory(String(className) + "@ f()");
        engine->RegisterObjectBehaviour(className, asBEHAVE_FACTORY, declFactory.CString(), AS_FUNCTION(Resource_Resource_Context_template), AS_CALL_CDECL);
    }
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "bool Save(Serializer&) const", AS_METHODPR(T, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "bool SaveFile(const String&in) const", AS_METHODPR(T, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool Save(const String&in) const", AS_METHODPR(T, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SendEvent(StringHash)", AS_METHODPR(T, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(T, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(T, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SetBlockEvents(bool)", AS_METHODPR(T, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(T, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(T, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "void SetMemoryUse(uint)", AS_METHODPR(T, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "void SetName(const String&in)", AS_METHODPR(T, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_name(const String&in)", AS_METHODPR(T, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromAllEvents()", AS_METHODPR(T, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Resource_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool_template), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(T, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(T, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(T, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod(className, "int WeakRefs() const", AS_METHODPR(T, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_weakRefs() const", AS_METHODPR(T, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(T, className)
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(T, className)
#endif
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(T, className)
#endif
    RegisterSubclass<Object, T>(engine, "Object", className);
    RegisterSubclass<RefCounted, T>(engine, "RefCounted", className);
    RegisterSubclass<Resource, T>(engine, "Resource", className);
}

}
