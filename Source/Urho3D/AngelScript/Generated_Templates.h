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
static void Component_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool_template(Component* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Object_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool_template(Object* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// explicit Resource::Resource(Context* context) | File: ../Resource/Resource.h
static Resource* Resource_Resource_Context_template()
{
    return new Resource(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Resource_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool_template(Resource* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

template <class T> void RegisterComponent(asIScriptEngine* engine, const char* className)
{
    // class Component | File: ../Scene/Component.h
    engine->RegisterObjectType(className, 0, asOBJ_REF);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour(className, asBEHAVE_ADDREF, "void f()", asMETHODPR(T, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void AllocateNetworkState()", asMETHODPR(T, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void ApplyAttributes()", asMETHODPR(T, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // explicit Component::Component(Context* context) | File: ../Scene/Component.h
    {
        String declFactory(String(className) + "@ f()");
        engine->RegisterObjectBehaviour(className, asBEHAVE_FACTORY, declFactory.CString(), asFUNCTION(Component_Component_Context_template), asCALL_CDECL);
    }
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(T, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "bool GetAnimationEnabled() const", asMETHODPR(T, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_animationEnabled() const", asMETHODPR(T, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "Variant GetAttribute(uint) const", asMETHODPR(T, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Variant get_attributes(uint) const", asMETHODPR(T, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "Variant GetAttribute(const String&in) const", asMETHODPR(T, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(T, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(T, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(T, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(T, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "Variant GetAttributeDefault(uint) const", asMETHODPR(T, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Variant get_attributeDefaults(uint) const", asMETHODPR(T, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "Variant GetAttributeDefault(const String&in) const", asMETHODPR(T, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool GetBlockEvents() const", asMETHODPR(T, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const String& GetCategory() const", asMETHODPR(T, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_category() const", asMETHODPR(T, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "Component@+ GetComponent(StringHash) const", asMETHODPR(T, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "VariantMap& GetEventDataMap() const", asMETHODPR(T, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "Object@+ GetEventSender() const", asMETHODPR(T, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(T, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Variant& get_globalVar(StringHash) const", asMETHODPR(T, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const VariantMap& GetGlobalVars() const", asMETHODPR(T, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const VariantMap& get_globalVars() const", asMETHODPR(T, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "uint GetID() const", asMETHODPR(T, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_id() const", asMETHODPR(T, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(T, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "Node@+ GetNode() const", asMETHODPR(T, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Node@+ get_node() const", asMETHODPR(T, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "uint GetNumAttributes() const", asMETHODPR(T, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_numAttributes() const", asMETHODPR(T, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "uint GetNumNetworkAttributes() const", asMETHODPR(T, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(T, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(T, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(T, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "Scene@+ GetScene() const", asMETHODPR(T, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "Object@+ GetSubsystem(StringHash) const", asMETHODPR(T, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "StringHash GetType() const", asMETHODPR(T, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "StringHash get_type() const", asMETHODPR(T, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const String& GetTypeName() const", asMETHODPR(T, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_typeName() const", asMETHODPR(T, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasEventHandlers() const", asMETHODPR(T, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(T, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(T, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "bool IsEnabled() const", asMETHODPR(T, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_enabled() const", asMETHODPR(T, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "bool IsEnabledEffective() const", asMETHODPR(T, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_enabledEffective() const", asMETHODPR(T, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool IsInstanceOf(StringHash) const", asMETHODPR(T, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "bool IsReplicated() const", asMETHODPR(T, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_replicated() const", asMETHODPR(T, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool IsTemporary() const", asMETHODPR(T, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_temporary() const", asMETHODPR(T, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool Load(Deserializer&)", asMETHODPR(T, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "bool LoadJSON(const JSONValue&in)", asMETHODPR(T, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "bool LoadXML(const XMLElement&in)", asMETHODPR(T, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "void MarkNetworkUpdate()", asMETHODPR(T, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(T, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(T, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(T, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "void OnSetEnabled()", asMETHODPR(T, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "void PrepareNetworkUpdate()", asMETHODPR(T, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(T, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(T, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod(className, "int Refs() const", asMETHODPR(T, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_refs() const", asMETHODPR(T, Refs, () const, int), asCALL_THISCALL);
    // static void Animatable::RegisterObject(Context* context) | File: ../Scene/Animatable.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour(className, asBEHAVE_RELEASE, "void f()", asMETHODPR(T, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "void Remove()", asMETHODPR(T, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void RemoveAttributeAnimation(const String&in)", asMETHODPR(T, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void RemoveInstanceDefault()", asMETHODPR(T, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void RemoveObjectAnimation()", asMETHODPR(T, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void ResetToDefault()", asMETHODPR(T, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "bool Save(Serializer&) const", asMETHODPR(T, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool SaveDefaultAttributes() const", asMETHODPR(T, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "bool SaveJSON(JSONValue&) const", asMETHODPR(T, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "bool SaveXML(XMLElement&) const", asMETHODPR(T, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SendEvent(StringHash)", asMETHODPR(T, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SendEvent(StringHash, VariantMap&)", asMETHODPR(T, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetAnimationEnabled(bool)", asMETHODPR(T, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_animationEnabled(bool)", asMETHODPR(T, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetAnimationTime(float)", asMETHODPR(T, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool SetAttribute(uint, const Variant&in)", asMETHODPR(T, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool set_attributes(uint, const Variant&in)", asMETHODPR(T, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(T, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(T, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(T, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(T, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(T, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SetBlockEvents(bool)", asMETHODPR(T, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod(className, "void SetEnabled(bool)", asMETHODPR(T, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_enabled(bool)", asMETHODPR(T, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(T, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(T, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void SetInstanceDefault(bool)", asMETHODPR(T, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(T, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(T, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(T, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod(className, "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(T, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void SetTemporary(bool)", asMETHODPR(T, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_temporary(bool)", asMETHODPR(T, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromAllEvents()", asMETHODPR(T, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Component_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool_template), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvent(StringHash)", asMETHODPR(T, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(T, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvents(Object@+)", asMETHODPR(T, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod(className, "int WeakRefs() const", asMETHODPR(T, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_weakRefs() const", asMETHODPR(T, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(T, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(T, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod(className, "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(T, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour(className, asBEHAVE_ADDREF, "void f()", asMETHODPR(T, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool GetBlockEvents() const", asMETHODPR(T, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const String& GetCategory() const", asMETHODPR(T, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_category() const", asMETHODPR(T, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "VariantMap& GetEventDataMap() const", asMETHODPR(T, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "Object@+ GetEventSender() const", asMETHODPR(T, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(T, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Variant& get_globalVar(StringHash) const", asMETHODPR(T, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const VariantMap& GetGlobalVars() const", asMETHODPR(T, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const VariantMap& get_globalVars() const", asMETHODPR(T, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "Object@+ GetSubsystem(StringHash) const", asMETHODPR(T, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "StringHash GetType() const", asMETHODPR(T, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "StringHash get_type() const", asMETHODPR(T, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const String& GetTypeName() const", asMETHODPR(T, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_typeName() const", asMETHODPR(T, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasEventHandlers() const", asMETHODPR(T, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(T, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(T, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool IsInstanceOf(StringHash) const", asMETHODPR(T, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(T, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod(className, "int Refs() const", asMETHODPR(T, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_refs() const", asMETHODPR(T, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour(className, asBEHAVE_RELEASE, "void f()", asMETHODPR(T, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SendEvent(StringHash)", asMETHODPR(T, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SendEvent(StringHash, VariantMap&)", asMETHODPR(T, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SetBlockEvents(bool)", asMETHODPR(T, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(T, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(T, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromAllEvents()", asMETHODPR(T, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Object_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool_template), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvent(StringHash)", asMETHODPR(T, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(T, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvents(Object@+)", asMETHODPR(T, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod(className, "int WeakRefs() const", asMETHODPR(T, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_weakRefs() const", asMETHODPR(T, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour(className, asBEHAVE_ADDREF, "void f()", asMETHODPR(T, AddRef, (), void), asCALL_THISCALL);
    // virtual bool Resource::BeginLoad(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "bool BeginLoad(Deserializer&)", asMETHODPR(T, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "bool EndLoad()", asMETHODPR(T, EndLoad, (), bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(T, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool GetBlockEvents() const", asMETHODPR(T, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const String& GetCategory() const", asMETHODPR(T, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_category() const", asMETHODPR(T, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "VariantMap& GetEventDataMap() const", asMETHODPR(T, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "Object@+ GetEventSender() const", asMETHODPR(T, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(T, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Variant& get_globalVar(StringHash) const", asMETHODPR(T, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const VariantMap& GetGlobalVars() const", asMETHODPR(T, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const VariantMap& get_globalVars() const", asMETHODPR(T, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "uint GetMemoryUse() const", asMETHODPR(T, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_memoryUse() const", asMETHODPR(T, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "const String& GetName() const", asMETHODPR(T, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_name() const", asMETHODPR(T, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "StringHash GetNameHash() const", asMETHODPR(T, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "Object@+ GetSubsystem(StringHash) const", asMETHODPR(T, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "StringHash GetType() const", asMETHODPR(T, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "StringHash get_type() const", asMETHODPR(T, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "const String& GetTypeName() const", asMETHODPR(T, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const String& get_typeName() const", asMETHODPR(T, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "uint GetUseTimer()", asMETHODPR(T, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "uint get_useTimer()", asMETHODPR(T, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasEventHandlers() const", asMETHODPR(T, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(T, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(T, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "bool IsInstanceOf(StringHash) const", asMETHODPR(T, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "bool Load(Deserializer&)", asMETHODPR(T, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "bool LoadFile(const String&in)", asMETHODPR(T, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool Load(const String&in)", asMETHODPR(T, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(T, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod(className, "int Refs() const", asMETHODPR(T, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_refs() const", asMETHODPR(T, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour(className, asBEHAVE_RELEASE, "void f()", asMETHODPR(T, ReleaseRef, (), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "void ResetUseTimer()", asMETHODPR(T, ResetUseTimer, (), void), asCALL_THISCALL);
    // explicit Resource::Resource(Context* context) | File: ../Resource/Resource.h
    {
        String declFactory(String(className) + "@ f()");
        engine->RegisterObjectBehaviour(className, asBEHAVE_FACTORY, declFactory.CString(), asFUNCTION(Resource_Resource_Context_template), asCALL_CDECL);
    }
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "bool Save(Serializer&) const", asMETHODPR(T, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "bool SaveFile(const String&in) const", asMETHODPR(T, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool Save(const String&in) const", asMETHODPR(T, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SendEvent(StringHash)", asMETHODPR(T, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SendEvent(StringHash, VariantMap&)", asMETHODPR(T, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(T, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SetBlockEvents(bool)", asMETHODPR(T, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(T, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(T, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "void SetMemoryUse(uint)", asMETHODPR(T, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod(className, "void SetName(const String&in)", asMETHODPR(T, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_name(const String&in)", asMETHODPR(T, SetName, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromAllEvents()", asMETHODPR(T, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Resource_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool_template), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvent(StringHash)", asMETHODPR(T, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(T, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod(className, "void UnsubscribeFromEvents(Object@+)", asMETHODPR(T, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod(className, "int WeakRefs() const", asMETHODPR(T, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_weakRefs() const", asMETHODPR(T, WeakRefs, () const, int), asCALL_THISCALL);
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
