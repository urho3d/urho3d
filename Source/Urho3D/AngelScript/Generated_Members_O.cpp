// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Object_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Object* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit ObjectAnimation::ObjectAnimation(Context* context) | File: ../Scene/ObjectAnimation.h
static ObjectAnimation* ObjectAnimation_ObjectAnimation_Context()
{
    return new ObjectAnimation(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ObjectAnimation_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ObjectAnimation* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// virtual SharedPtr<Object> ObjectFactory::CreateObject()=0 | File: ../Core/Object.h
static Object* ObjectFactory_CreateObject_void(ObjectFactory* ptr)
{
    SharedPtr<Object> result = ptr->CreateObject();
    return result.Detach();
}

#ifdef URHO3D_NAVIGATION
// explicit Obstacle::Obstacle(Context* context) | File: ../Navigation/Obstacle.h
static Obstacle* Obstacle_Obstacle_Context()
{
    return new Obstacle(GetScriptContext());
}
#endif

#ifdef URHO3D_NAVIGATION
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Obstacle_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Obstacle* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// explicit OcclusionBuffer::OcclusionBuffer(Context* context) | File: ../Graphics/OcclusionBuffer.h
static OcclusionBuffer* OcclusionBuffer_OcclusionBuffer_Context()
{
    return new OcclusionBuffer(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void OcclusionBuffer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(OcclusionBuffer* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Octree::Octree(Context* context) | File: ../Graphics/Octree.h
static Octree* Octree_Octree_Context()
{
    return new Octree(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Octree_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Octree* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_NAVIGATION
// explicit OffMeshConnection::OffMeshConnection(Context* context) | File: ../Navigation/OffMeshConnection.h
static OffMeshConnection* OffMeshConnection_OffMeshConnection_Context()
{
    return new OffMeshConnection(GetScriptContext());
}
#endif

#ifdef URHO3D_NAVIGATION
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void OffMeshConnection_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(OffMeshConnection* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// explicit OggVorbisSoundStream::OggVorbisSoundStream(const Sound* sound) | File: ../Audio/OggVorbisSoundStream.h
static OggVorbisSoundStream* OggVorbisSoundStream_OggVorbisSoundStream_Sound(const Sound *sound)
{
    return new OggVorbisSoundStream(sound);
}

void ASRegisterGenerated_Members_O(asIScriptEngine* engine)
{
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Object", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Object, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "bool GetBlockEvents() const", AS_METHODPR(Object, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "const String& GetCategory() const", AS_METHODPR(Object, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Object", "const String& get_category() const", AS_METHODPR(Object, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "VariantMap& GetEventDataMap() const", AS_METHODPR(Object, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "Object@+ GetEventSender() const", AS_METHODPR(Object, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Object, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Object", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Object, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Object, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Object", "const VariantMap& get_globalVars() const", AS_METHODPR(Object, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Object, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "StringHash GetType() const", AS_METHODPR(Object, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Object", "StringHash get_type() const", AS_METHODPR(Object, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "const String& GetTypeName() const", AS_METHODPR(Object, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Object", "const String& get_typeName() const", AS_METHODPR(Object, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "bool HasEventHandlers() const", AS_METHODPR(Object, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Object, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Object, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Object, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Object, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Object", "int Refs() const", AS_METHODPR(Object, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Object", "int get_refs() const", AS_METHODPR(Object, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Object", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Object, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void SendEvent(StringHash)", AS_METHODPR(Object, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Object, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void SetBlockEvents(bool)", AS_METHODPR(Object, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Object, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Object", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Object, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void UnsubscribeFromAllEvents()", AS_METHODPR(Object, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Object_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Object, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Object, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Object, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Object", "int WeakRefs() const", AS_METHODPR(Object, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Object", "int get_weakRefs() const", AS_METHODPR(Object, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Object, "Object")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Object, "Object")
#endif
    RegisterSubclass<RefCounted, Object>(engine, "RefCounted", "Object");

    // void ObjectAnimation::AddAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "void AddAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ObjectAnimation, AddAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ObjectAnimation", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ObjectAnimation, AddRef, (), void), AS_CALL_THISCALL);
    // bool ObjectAnimation::BeginLoad(Deserializer& source) override | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool BeginLoad(Deserializer&)", AS_METHODPR(ObjectAnimation, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool EndLoad()", AS_METHODPR(ObjectAnimation, EndLoad, (), bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(ObjectAnimation, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // ValueAnimation* ObjectAnimation::GetAttributeAnimation(const String& name) const | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ObjectAnimation, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "ValueAnimation@+ get_attributeAnimations(const String&in) const", AS_METHODPR(ObjectAnimation, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // ValueAnimationInfo* ObjectAnimation::GetAttributeAnimationInfo(const String& name) const | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "ValueAnimationInfo@+ GetAttributeAnimationInfo(const String&in) const", AS_METHODPR(ObjectAnimation, GetAttributeAnimationInfo, (const String&) const, ValueAnimationInfo*), AS_CALL_THISCALL);
    // const HashMap<String, SharedPtr<ValueAnimationInfo>>& ObjectAnimation::GetAttributeAnimationInfos() const | File: ../Scene/ObjectAnimation.h
    // Error: type "const HashMap<String, SharedPtr<ValueAnimationInfo>>&" can not automatically bind
    // float ObjectAnimation::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ObjectAnimation, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "float get_speeds(const String&in) const", AS_METHODPR(ObjectAnimation, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode ObjectAnimation::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ObjectAnimation, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "WrapMode get_wrapModes(const String&in) const", AS_METHODPR(ObjectAnimation, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool GetBlockEvents() const", AS_METHODPR(ObjectAnimation, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "const String& GetCategory() const", AS_METHODPR(ObjectAnimation, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "const String& get_category() const", AS_METHODPR(ObjectAnimation, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "VariantMap& GetEventDataMap() const", AS_METHODPR(ObjectAnimation, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "Object@+ GetEventSender() const", AS_METHODPR(ObjectAnimation, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ObjectAnimation, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ObjectAnimation, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ObjectAnimation, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "const VariantMap& get_globalVars() const", AS_METHODPR(ObjectAnimation, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "uint GetMemoryUse() const", AS_METHODPR(ObjectAnimation, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "uint get_memoryUse() const", AS_METHODPR(ObjectAnimation, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "const String& GetName() const", AS_METHODPR(ObjectAnimation, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "const String& get_name() const", AS_METHODPR(ObjectAnimation, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "StringHash GetNameHash() const", AS_METHODPR(ObjectAnimation, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ObjectAnimation, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "StringHash GetType() const", AS_METHODPR(ObjectAnimation, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "StringHash get_type() const", AS_METHODPR(ObjectAnimation, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "const String& GetTypeName() const", AS_METHODPR(ObjectAnimation, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "const String& get_typeName() const", AS_METHODPR(ObjectAnimation, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "uint GetUseTimer()", AS_METHODPR(ObjectAnimation, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "uint get_useTimer()", AS_METHODPR(ObjectAnimation, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool HasEventHandlers() const", AS_METHODPR(ObjectAnimation, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ObjectAnimation, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ObjectAnimation, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ObjectAnimation, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool Load(Deserializer&)", AS_METHODPR(ObjectAnimation, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool LoadFile(const String&in)", AS_METHODPR(ObjectAnimation, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "bool Load(const String&in)", AS_METHODPR(ObjectAnimation, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // bool ObjectAnimation::LoadJSON(const JSONValue& source) | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ObjectAnimation, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool ObjectAnimation::LoadXML(const XMLElement& source) | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ObjectAnimation, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // explicit ObjectAnimation::ObjectAnimation(Context* context) | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectBehaviour("ObjectAnimation", asBEHAVE_FACTORY, "ObjectAnimation@+ f()", AS_FUNCTION(ObjectAnimation_ObjectAnimation_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ObjectAnimation, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ObjectAnimation", "int Refs() const", AS_METHODPR(ObjectAnimation, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "int get_refs() const", AS_METHODPR(ObjectAnimation, Refs, () const, int), AS_CALL_THISCALL);
    // static void ObjectAnimation::RegisterObject(Context* context) | File: ../Scene/ObjectAnimation.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ObjectAnimation", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ObjectAnimation, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ObjectAnimation::RemoveAttributeAnimation(const String& name) | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ObjectAnimation, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void ObjectAnimation::RemoveAttributeAnimation(ValueAnimation* attributeAnimation) | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "void RemoveAttributeAnimation(ValueAnimation@+)", AS_METHODPR(ObjectAnimation, RemoveAttributeAnimation, (ValueAnimation*), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "void ResetUseTimer()", AS_METHODPR(ObjectAnimation, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // bool ObjectAnimation::Save(Serializer& dest) const override | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool Save(Serializer&) const", AS_METHODPR(ObjectAnimation, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool SaveFile(const String&in) const", AS_METHODPR(ObjectAnimation, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "bool Save(const String&in) const", AS_METHODPR(ObjectAnimation, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // bool ObjectAnimation::SaveJSON(JSONValue& dest) const | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ObjectAnimation, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool ObjectAnimation::SaveXML(XMLElement& dest) const | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool SaveXML(XMLElement&) const", AS_METHODPR(ObjectAnimation, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SendEvent(StringHash)", AS_METHODPR(ObjectAnimation, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ObjectAnimation, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(ObjectAnimation, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SetBlockEvents(bool)", AS_METHODPR(ObjectAnimation, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ObjectAnimation, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ObjectAnimation, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SetMemoryUse(uint)", AS_METHODPR(ObjectAnimation, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SetName(const String&in)", AS_METHODPR(ObjectAnimation, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "void set_name(const String&in)", AS_METHODPR(ObjectAnimation, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void UnsubscribeFromAllEvents()", AS_METHODPR(ObjectAnimation, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ObjectAnimation_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ObjectAnimation, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ObjectAnimation, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ObjectAnimation, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ObjectAnimation", "int WeakRefs() const", AS_METHODPR(ObjectAnimation, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "int get_weakRefs() const", AS_METHODPR(ObjectAnimation, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(ObjectAnimation, "ObjectAnimation")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ObjectAnimation, "ObjectAnimation")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ObjectAnimation, "ObjectAnimation")
#endif
#ifdef REGISTER_MANUAL_PART_ObjectAnimation
    REGISTER_MANUAL_PART_ObjectAnimation(ObjectAnimation, "ObjectAnimation")
#endif
    RegisterSubclass<Resource, ObjectAnimation>(engine, "Resource", "ObjectAnimation");
    RegisterSubclass<Object, ObjectAnimation>(engine, "Object", "ObjectAnimation");
    RegisterSubclass<RefCounted, ObjectAnimation>(engine, "RefCounted", "ObjectAnimation");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ObjectFactory", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ObjectFactory, AddRef, (), void), AS_CALL_THISCALL);
    // virtual SharedPtr<Object> ObjectFactory::CreateObject()=0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectFactory", "Object@+ CreateObject()", AS_FUNCTION_OBJFIRST(ObjectFactory_CreateObject_void), AS_CALL_CDECL_OBJFIRST);
    // Context* ObjectFactory::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // StringHash ObjectFactory::GetType() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectFactory", "StringHash GetType() const", AS_METHODPR(ObjectFactory, GetType, () const, StringHash), AS_CALL_THISCALL);
    // const TypeInfo* ObjectFactory::GetTypeInfo() const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // const String& ObjectFactory::GetTypeName() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectFactory", "const String& GetTypeName() const", AS_METHODPR(ObjectFactory, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ObjectFactory", "int Refs() const", AS_METHODPR(ObjectFactory, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectFactory", "int get_refs() const", AS_METHODPR(ObjectFactory, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ObjectFactory", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ObjectFactory, ReleaseRef, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ObjectFactory", "int WeakRefs() const", AS_METHODPR(ObjectFactory, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ObjectFactory", "int get_weakRefs() const", AS_METHODPR(ObjectFactory, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ObjectFactory, "ObjectFactory")
#endif
#ifdef REGISTER_MANUAL_PART_ObjectFactory
    REGISTER_MANUAL_PART_ObjectFactory(ObjectFactory, "ObjectFactory")
#endif
    RegisterSubclass<RefCounted, ObjectFactory>(engine, "RefCounted", "ObjectFactory");

#ifdef URHO3D_NAVIGATION
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Obstacle", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Obstacle, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void AllocateNetworkState()", AS_METHODPR(Obstacle, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void ApplyAttributes()", AS_METHODPR(Obstacle, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Obstacle::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Obstacle, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // void Obstacle::DrawDebugGeometry(bool depthTest) | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "void DrawDebugGeometry(bool)", AS_METHODPR(Obstacle, DrawDebugGeometry, (bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "bool GetAnimationEnabled() const", AS_METHODPR(Obstacle, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "bool get_animationEnabled() const", AS_METHODPR(Obstacle, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "Variant GetAttribute(uint) const", AS_METHODPR(Obstacle, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "Variant get_attributes(uint) const", AS_METHODPR(Obstacle, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "Variant GetAttribute(const String&in) const", AS_METHODPR(Obstacle, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Obstacle, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Obstacle, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Obstacle, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Obstacle, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Obstacle, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Obstacle, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Obstacle, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "bool GetBlockEvents() const", AS_METHODPR(Obstacle, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "const String& GetCategory() const", AS_METHODPR(Obstacle, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "const String& get_category() const", AS_METHODPR(Obstacle, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Obstacle, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Obstacle", "VariantMap& GetEventDataMap() const", AS_METHODPR(Obstacle, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "Object@+ GetEventSender() const", AS_METHODPR(Obstacle, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Obstacle, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Obstacle, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Obstacle, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "const VariantMap& get_globalVars() const", AS_METHODPR(Obstacle, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // float Obstacle::GetHeight() const | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "float GetHeight() const", AS_METHODPR(Obstacle, GetHeight, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "float get_height() const", AS_METHODPR(Obstacle, GetHeight, () const, float), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "uint GetID() const", AS_METHODPR(Obstacle, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "uint get_id() const", AS_METHODPR(Obstacle, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Obstacle, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "Node@+ GetNode() const", AS_METHODPR(Obstacle, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "Node@+ get_node() const", AS_METHODPR(Obstacle, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "uint GetNumAttributes() const", AS_METHODPR(Obstacle, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "uint get_numAttributes() const", AS_METHODPR(Obstacle, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "uint GetNumNetworkAttributes() const", AS_METHODPR(Obstacle, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Obstacle, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Obstacle, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Obstacle, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned Obstacle::GetObstacleID() const | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "uint GetObstacleID() const", AS_METHODPR(Obstacle, GetObstacleID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "uint get_obstacleId() const", AS_METHODPR(Obstacle, GetObstacleID, () const, unsigned), AS_CALL_THISCALL);
    // float Obstacle::GetRadius() const | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "float GetRadius() const", AS_METHODPR(Obstacle, GetRadius, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "float get_radius() const", AS_METHODPR(Obstacle, GetRadius, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "Scene@+ GetScene() const", AS_METHODPR(Obstacle, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Obstacle, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "StringHash GetType() const", AS_METHODPR(Obstacle, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "StringHash get_type() const", AS_METHODPR(Obstacle, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "const String& GetTypeName() const", AS_METHODPR(Obstacle, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "const String& get_typeName() const", AS_METHODPR(Obstacle, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "bool HasEventHandlers() const", AS_METHODPR(Obstacle, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Obstacle, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Obstacle, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "bool IsEnabled() const", AS_METHODPR(Obstacle, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "bool get_enabled() const", AS_METHODPR(Obstacle, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "bool IsEnabledEffective() const", AS_METHODPR(Obstacle, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "bool get_enabledEffective() const", AS_METHODPR(Obstacle, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Obstacle, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "bool IsReplicated() const", AS_METHODPR(Obstacle, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "bool get_replicated() const", AS_METHODPR(Obstacle, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool IsTemporary() const", AS_METHODPR(Obstacle, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "bool get_temporary() const", AS_METHODPR(Obstacle, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool Load(Deserializer&)", AS_METHODPR(Obstacle, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Obstacle, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Obstacle, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "void MarkNetworkUpdate()", AS_METHODPR(Obstacle, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // explicit Obstacle::Obstacle(Context* context) | File: ../Navigation/Obstacle.h
    engine->RegisterObjectBehaviour("Obstacle", asBEHAVE_FACTORY, "Obstacle@+ f()", AS_FUNCTION(Obstacle_Obstacle_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Obstacle, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Obstacle, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Obstacle, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Obstacle::OnSetEnabled() override | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "void OnSetEnabled()", AS_METHODPR(Obstacle, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "void PrepareNetworkUpdate()", AS_METHODPR(Obstacle, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Obstacle, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Obstacle, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Obstacle", "int Refs() const", AS_METHODPR(Obstacle, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "int get_refs() const", AS_METHODPR(Obstacle, Refs, () const, int), AS_CALL_THISCALL);
    // static void Obstacle::RegisterObject(Context* context) | File: ../Navigation/Obstacle.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Obstacle", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Obstacle, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "void Remove()", AS_METHODPR(Obstacle, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Obstacle, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void RemoveInstanceDefault()", AS_METHODPR(Obstacle, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void RemoveObjectAnimation()", AS_METHODPR(Obstacle, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void ResetToDefault()", AS_METHODPR(Obstacle, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "bool Save(Serializer&) const", AS_METHODPR(Obstacle, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool SaveDefaultAttributes() const", AS_METHODPR(Obstacle, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Obstacle, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "bool SaveXML(XMLElement&) const", AS_METHODPR(Obstacle, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void SendEvent(StringHash)", AS_METHODPR(Obstacle, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Obstacle, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetAnimationEnabled(bool)", AS_METHODPR(Obstacle, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_animationEnabled(bool)", AS_METHODPR(Obstacle, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetAnimationTime(float)", AS_METHODPR(Obstacle, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Obstacle, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Obstacle, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Obstacle, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Obstacle, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Obstacle, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Obstacle, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Obstacle, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void SetBlockEvents(bool)", AS_METHODPR(Obstacle, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "void SetEnabled(bool)", AS_METHODPR(Obstacle, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_enabled(bool)", AS_METHODPR(Obstacle, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Obstacle, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Obstacle, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Obstacle::SetHeight(float newHeight) | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "void SetHeight(float)", AS_METHODPR(Obstacle, SetHeight, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_height(float)", AS_METHODPR(Obstacle, SetHeight, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void SetInstanceDefault(bool)", AS_METHODPR(Obstacle, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Obstacle, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Obstacle, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Obstacle, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Obstacle, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Obstacle::SetRadius(float newRadius) | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "void SetRadius(float)", AS_METHODPR(Obstacle, SetRadius, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_radius(float)", AS_METHODPR(Obstacle, SetRadius, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void SetTemporary(bool)", AS_METHODPR(Obstacle, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_temporary(bool)", AS_METHODPR(Obstacle, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void UnsubscribeFromAllEvents()", AS_METHODPR(Obstacle, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Obstacle_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Obstacle, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Obstacle, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Obstacle, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Obstacle", "int WeakRefs() const", AS_METHODPR(Obstacle, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "int get_weakRefs() const", AS_METHODPR(Obstacle, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Obstacle, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Obstacle, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Obstacle, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Obstacle, "Obstacle")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Obstacle, "Obstacle")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Obstacle, "Obstacle")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Obstacle, "Obstacle")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Obstacle, "Obstacle")
#endif
#ifdef REGISTER_MANUAL_PART_Obstacle
    REGISTER_MANUAL_PART_Obstacle(Obstacle, "Obstacle")
#endif
    RegisterSubclass<Component, Obstacle>(engine, "Component", "Obstacle");
    RegisterSubclass<Animatable, Obstacle>(engine, "Animatable", "Obstacle");
    RegisterSubclass<Serializable, Obstacle>(engine, "Serializable", "Obstacle");
    RegisterSubclass<Object, Obstacle>(engine, "Object", "Obstacle");
    RegisterSubclass<RefCounted, Obstacle>(engine, "RefCounted", "Obstacle");
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("OcclusionBuffer", asBEHAVE_ADDREF, "void f()", AS_METHODPR(OcclusionBuffer, AddRef, (), void), AS_CALL_THISCALL);
    // bool OcclusionBuffer::AddTriangles(const Matrix3x4& model, const void* vertexData, unsigned vertexSize, unsigned vertexStart, unsigned vertexCount) | File: ../Graphics/OcclusionBuffer.h
    // Error: type "const void*" can not automatically bind
    // bool OcclusionBuffer::AddTriangles(const Matrix3x4& model, const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount) | File: ../Graphics/OcclusionBuffer.h
    // Error: type "const void*" can not automatically bind
    // void OcclusionBuffer::BuildDepthHierarchy() | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void BuildDepthHierarchy()", AS_METHODPR(OcclusionBuffer, BuildDepthHierarchy, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void OcclusionBuffer::Clear() | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void Clear()", AS_METHODPR(OcclusionBuffer, Clear, (), void), AS_CALL_THISCALL);
    // void OcclusionBuffer::DrawBatch(const OcclusionBatch& batch, unsigned threadIndex) | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void DrawBatch(const OcclusionBatch&in, uint)", AS_METHODPR(OcclusionBuffer, DrawBatch, (const OcclusionBatch&, unsigned), void), AS_CALL_THISCALL);
    // void OcclusionBuffer::DrawTriangles() | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void DrawTriangles()", AS_METHODPR(OcclusionBuffer, DrawTriangles, (), void), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool GetBlockEvents() const", AS_METHODPR(OcclusionBuffer, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // int* OcclusionBuffer::GetBuffer() const | File: ../Graphics/OcclusionBuffer.h
    // Error: type "int*" can not automatically bind
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "const String& GetCategory() const", AS_METHODPR(OcclusionBuffer, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "const String& get_category() const", AS_METHODPR(OcclusionBuffer, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // CullMode OcclusionBuffer::GetCullMode() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "CullMode GetCullMode() const", AS_METHODPR(OcclusionBuffer, GetCullMode, () const, CullMode), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "VariantMap& GetEventDataMap() const", AS_METHODPR(OcclusionBuffer, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "Object@+ GetEventSender() const", AS_METHODPR(OcclusionBuffer, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(OcclusionBuffer, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(OcclusionBuffer, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "const VariantMap& GetGlobalVars() const", AS_METHODPR(OcclusionBuffer, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "const VariantMap& get_globalVars() const", AS_METHODPR(OcclusionBuffer, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int OcclusionBuffer::GetHeight() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "int GetHeight() const", AS_METHODPR(OcclusionBuffer, GetHeight, () const, int), AS_CALL_THISCALL);
    // unsigned OcclusionBuffer::GetMaxTriangles() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "uint GetMaxTriangles() const", AS_METHODPR(OcclusionBuffer, GetMaxTriangles, () const, unsigned), AS_CALL_THISCALL);
    // unsigned OcclusionBuffer::GetNumTriangles() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "uint GetNumTriangles() const", AS_METHODPR(OcclusionBuffer, GetNumTriangles, () const, unsigned), AS_CALL_THISCALL);
    // const Matrix4& OcclusionBuffer::GetProjection() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "const Matrix4& GetProjection() const", AS_METHODPR(OcclusionBuffer, GetProjection, () const, const Matrix4&), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(OcclusionBuffer, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "StringHash GetType() const", AS_METHODPR(OcclusionBuffer, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "StringHash get_type() const", AS_METHODPR(OcclusionBuffer, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "const String& GetTypeName() const", AS_METHODPR(OcclusionBuffer, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "const String& get_typeName() const", AS_METHODPR(OcclusionBuffer, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned OcclusionBuffer::GetUseTimer() | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "uint GetUseTimer()", AS_METHODPR(OcclusionBuffer, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // const Matrix3x4& OcclusionBuffer::GetView() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "const Matrix3x4& GetView() const", AS_METHODPR(OcclusionBuffer, GetView, () const, const Matrix3x4&), AS_CALL_THISCALL);
    // int OcclusionBuffer::GetWidth() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "int GetWidth() const", AS_METHODPR(OcclusionBuffer, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool HasEventHandlers() const", AS_METHODPR(OcclusionBuffer, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(OcclusionBuffer, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(OcclusionBuffer, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool IsInstanceOf(StringHash) const", AS_METHODPR(OcclusionBuffer, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool OcclusionBuffer::IsThreaded() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool IsThreaded() const", AS_METHODPR(OcclusionBuffer, IsThreaded, () const, bool), AS_CALL_THISCALL);
    // bool OcclusionBuffer::IsVisible(const BoundingBox& worldSpaceBox) const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool IsVisible(const BoundingBox&in) const", AS_METHODPR(OcclusionBuffer, IsVisible, (const BoundingBox&) const, bool), AS_CALL_THISCALL);
    // explicit OcclusionBuffer::OcclusionBuffer(Context* context) | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectBehaviour("OcclusionBuffer", asBEHAVE_FACTORY, "OcclusionBuffer@+ f()", AS_FUNCTION(OcclusionBuffer_OcclusionBuffer_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(OcclusionBuffer, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("OcclusionBuffer", "int Refs() const", AS_METHODPR(OcclusionBuffer, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "int get_refs() const", AS_METHODPR(OcclusionBuffer, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("OcclusionBuffer", asBEHAVE_RELEASE, "void f()", AS_METHODPR(OcclusionBuffer, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void OcclusionBuffer::Reset() | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void Reset()", AS_METHODPR(OcclusionBuffer, Reset, (), void), AS_CALL_THISCALL);
    // void OcclusionBuffer::ResetUseTimer() | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void ResetUseTimer()", AS_METHODPR(OcclusionBuffer, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SendEvent(StringHash)", AS_METHODPR(OcclusionBuffer, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(OcclusionBuffer, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SetBlockEvents(bool)", AS_METHODPR(OcclusionBuffer, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void OcclusionBuffer::SetCullMode(CullMode mode) | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SetCullMode(CullMode)", AS_METHODPR(OcclusionBuffer, SetCullMode, (CullMode), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(OcclusionBuffer, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(OcclusionBuffer, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void OcclusionBuffer::SetMaxTriangles(unsigned triangles) | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SetMaxTriangles(uint)", AS_METHODPR(OcclusionBuffer, SetMaxTriangles, (unsigned), void), AS_CALL_THISCALL);
    // bool OcclusionBuffer::SetSize(int width, int height, bool threaded) | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool SetSize(int, int, bool)", AS_METHODPR(OcclusionBuffer, SetSize, (int, int, bool), bool), AS_CALL_THISCALL);
    // void OcclusionBuffer::SetView(Camera* camera) | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SetView(Camera@+)", AS_METHODPR(OcclusionBuffer, SetView, (Camera*), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void UnsubscribeFromAllEvents()", AS_METHODPR(OcclusionBuffer, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(OcclusionBuffer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(OcclusionBuffer, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(OcclusionBuffer, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(OcclusionBuffer, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("OcclusionBuffer", "int WeakRefs() const", AS_METHODPR(OcclusionBuffer, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "int get_weakRefs() const", AS_METHODPR(OcclusionBuffer, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(OcclusionBuffer, "OcclusionBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(OcclusionBuffer, "OcclusionBuffer")
#endif
#ifdef REGISTER_MANUAL_PART_OcclusionBuffer
    REGISTER_MANUAL_PART_OcclusionBuffer(OcclusionBuffer, "OcclusionBuffer")
#endif
    RegisterSubclass<Object, OcclusionBuffer>(engine, "Object", "OcclusionBuffer");
    RegisterSubclass<RefCounted, OcclusionBuffer>(engine, "RefCounted", "OcclusionBuffer");

    // void Octant::AddDrawable(Drawable* drawable) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void AddDrawable(Drawable@+)", AS_METHODPR(Octree, AddDrawable, (Drawable*), void), AS_CALL_THISCALL);
    // void Octree::AddManualDrawable(Drawable* drawable) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void AddManualDrawable(Drawable@+)", AS_METHODPR(Octree, AddManualDrawable, (Drawable*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Octree", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Octree, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void AllocateNetworkState()", AS_METHODPR(Octree, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void ApplyAttributes()", AS_METHODPR(Octree, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void Octree::CancelUpdate(Drawable* drawable) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void CancelUpdate(Drawable@+)", AS_METHODPR(Octree, CancelUpdate, (Drawable*), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Octant::CheckDrawableFit(const BoundingBox& box) const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "bool CheckDrawableFit(const BoundingBox&in) const", AS_METHODPR(Octree, CheckDrawableFit, (const BoundingBox&) const, bool), AS_CALL_THISCALL);
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Octant::DeleteChild(unsigned index) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void DeleteChild(uint)", AS_METHODPR(Octree, DeleteChild, (unsigned), void), AS_CALL_THISCALL);
    // void Octree::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Octree, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // void Octree::DrawDebugGeometry(bool depthTest) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void DrawDebugGeometry(bool)", AS_METHODPR(Octree, DrawDebugGeometry, (bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "bool GetAnimationEnabled() const", AS_METHODPR(Octree, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "bool get_animationEnabled() const", AS_METHODPR(Octree, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "Variant GetAttribute(uint) const", AS_METHODPR(Octree, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "Variant get_attributes(uint) const", AS_METHODPR(Octree, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "Variant GetAttribute(const String&in) const", AS_METHODPR(Octree, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Octree, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Octree, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Octree, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Octree, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Octree, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Octree, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Octree, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "bool GetBlockEvents() const", AS_METHODPR(Octree, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "const String& GetCategory() const", AS_METHODPR(Octree, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "const String& get_category() const", AS_METHODPR(Octree, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Octree, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const BoundingBox& Octant::GetCullingBox() const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "const BoundingBox& GetCullingBox() const", AS_METHODPR(Octree, GetCullingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // void Octree::GetDrawables(OctreeQuery& query) const | File: ../Graphics/Octree.h
    // Not registered because have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "VariantMap& GetEventDataMap() const", AS_METHODPR(Octree, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "Object@+ GetEventSender() const", AS_METHODPR(Octree, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Octree, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Octree, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Octree, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "const VariantMap& get_globalVars() const", AS_METHODPR(Octree, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "uint GetID() const", AS_METHODPR(Octree, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "uint get_id() const", AS_METHODPR(Octree, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Octree, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Octant::GetLevel() const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "uint GetLevel() const", AS_METHODPR(Octree, GetLevel, () const, unsigned), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "Node@+ GetNode() const", AS_METHODPR(Octree, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "Node@+ get_node() const", AS_METHODPR(Octree, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "uint GetNumAttributes() const", AS_METHODPR(Octree, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "uint get_numAttributes() const", AS_METHODPR(Octree, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Octant::GetNumDrawables() const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "uint GetNumDrawables() const", AS_METHODPR(Octree, GetNumDrawables, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Octree::GetNumLevels() const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "uint GetNumLevels() const", AS_METHODPR(Octree, GetNumLevels, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "uint get_numLevels() const", AS_METHODPR(Octree, GetNumLevels, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "uint GetNumNetworkAttributes() const", AS_METHODPR(Octree, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Octree, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Octree, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Octree, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Octant::GetOrCreateChild(unsigned index) | File: ../Graphics/Octree.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Octant* Octant::GetParent() const | File: ../Graphics/Octree.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Octree* Octant::GetRoot() const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "Octree@+ GetRoot() const", AS_METHODPR(Octree, GetRoot, () const, Octree*), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "Scene@+ GetScene() const", AS_METHODPR(Octree, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Octree, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "StringHash GetType() const", AS_METHODPR(Octree, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "StringHash get_type() const", AS_METHODPR(Octree, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "const String& GetTypeName() const", AS_METHODPR(Octree, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "const String& get_typeName() const", AS_METHODPR(Octree, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // const BoundingBox& Octant::GetWorldBoundingBox() const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "const BoundingBox& GetWorldBoundingBox() const", AS_METHODPR(Octree, GetWorldBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "const BoundingBox& get_worldBoundingBox() const", AS_METHODPR(Octree, GetWorldBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "bool HasEventHandlers() const", AS_METHODPR(Octree, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Octree, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Octree, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // void Octant::InsertDrawable(Drawable* drawable) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void InsertDrawable(Drawable@+)", AS_METHODPR(Octree, InsertDrawable, (Drawable*), void), AS_CALL_THISCALL);
    // bool Octant::IsEmpty() | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "bool IsEmpty()", AS_METHODPR(Octree, IsEmpty, (), bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "bool IsEnabled() const", AS_METHODPR(Octree, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "bool get_enabled() const", AS_METHODPR(Octree, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "bool IsEnabledEffective() const", AS_METHODPR(Octree, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "bool get_enabledEffective() const", AS_METHODPR(Octree, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Octree, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "bool IsReplicated() const", AS_METHODPR(Octree, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "bool get_replicated() const", AS_METHODPR(Octree, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool IsTemporary() const", AS_METHODPR(Octree, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "bool get_temporary() const", AS_METHODPR(Octree, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool Load(Deserializer&)", AS_METHODPR(Octree, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Octree, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Octree, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "void MarkNetworkUpdate()", AS_METHODPR(Octree, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // explicit Octree::Octree(Context* context) | File: ../Graphics/Octree.h
    engine->RegisterObjectBehaviour("Octree", asBEHAVE_FACTORY, "Octree@+ f()", AS_FUNCTION(Octree_Octree_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Octree, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Octree, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Octree, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "void OnSetEnabled()", AS_METHODPR(Octree, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "void PrepareNetworkUpdate()", AS_METHODPR(Octree, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void Octree::QueueUpdate(Drawable* drawable) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void QueueUpdate(Drawable@+)", AS_METHODPR(Octree, QueueUpdate, (Drawable*), void), AS_CALL_THISCALL);
    // void Octree::Raycast(RayOctreeQuery& query) const | File: ../Graphics/Octree.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // void Octree::RaycastSingle(RayOctreeQuery& query) const | File: ../Graphics/Octree.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Octree, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Octree, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Octree", "int Refs() const", AS_METHODPR(Octree, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "int get_refs() const", AS_METHODPR(Octree, Refs, () const, int), AS_CALL_THISCALL);
    // static void Octree::RegisterObject(Context* context) | File: ../Graphics/Octree.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Octree", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Octree, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "void Remove()", AS_METHODPR(Octree, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Octree, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Octant::RemoveDrawable(Drawable* drawable, bool resetOctant=true) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void RemoveDrawable(Drawable@+, bool = true)", AS_METHODPR(Octree, RemoveDrawable, (Drawable*, bool), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void RemoveInstanceDefault()", AS_METHODPR(Octree, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Octree::RemoveManualDrawable(Drawable* drawable) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void RemoveManualDrawable(Drawable@+)", AS_METHODPR(Octree, RemoveManualDrawable, (Drawable*), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void RemoveObjectAnimation()", AS_METHODPR(Octree, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Octant::ResetRoot() | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void ResetRoot()", AS_METHODPR(Octree, ResetRoot, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void ResetToDefault()", AS_METHODPR(Octree, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "bool Save(Serializer&) const", AS_METHODPR(Octree, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool SaveDefaultAttributes() const", AS_METHODPR(Octree, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Octree, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "bool SaveXML(XMLElement&) const", AS_METHODPR(Octree, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void SendEvent(StringHash)", AS_METHODPR(Octree, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Octree, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetAnimationEnabled(bool)", AS_METHODPR(Octree, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void set_animationEnabled(bool)", AS_METHODPR(Octree, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetAnimationTime(float)", AS_METHODPR(Octree, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Octree, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Octree, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Octree, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Octree, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Octree, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Octree, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Octree, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void SetBlockEvents(bool)", AS_METHODPR(Octree, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "void SetEnabled(bool)", AS_METHODPR(Octree, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void set_enabled(bool)", AS_METHODPR(Octree, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Octree, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Octree, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void SetInstanceDefault(bool)", AS_METHODPR(Octree, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Octree, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Octree, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Octree, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Octree, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Octree::SetSize(const BoundingBox& box, unsigned numLevels) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void SetSize(const BoundingBox&in, uint)", AS_METHODPR(Octree, SetSize, (const BoundingBox&, unsigned), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void SetTemporary(bool)", AS_METHODPR(Octree, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void set_temporary(bool)", AS_METHODPR(Octree, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void UnsubscribeFromAllEvents()", AS_METHODPR(Octree, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Octree_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Octree, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Octree, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Octree, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Octree::Update(const FrameInfo& frame) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void Update(const FrameInfo&in)", AS_METHODPR(Octree, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Octree", "int WeakRefs() const", AS_METHODPR(Octree, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "int get_weakRefs() const", AS_METHODPR(Octree, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Octree, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Octree, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Octree, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Octree, "Octree")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Octree, "Octree")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Octree, "Octree")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Octree, "Octree")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Octree, "Octree")
#endif
#ifdef REGISTER_MANUAL_PART_Octant
    REGISTER_MANUAL_PART_Octant(Octree, "Octree")
#endif
#ifdef REGISTER_MANUAL_PART_Octree
    REGISTER_MANUAL_PART_Octree(Octree, "Octree")
#endif
    RegisterSubclass<Component, Octree>(engine, "Component", "Octree");
    RegisterSubclass<Animatable, Octree>(engine, "Animatable", "Octree");
    RegisterSubclass<Serializable, Octree>(engine, "Serializable", "Octree");
    RegisterSubclass<Object, Octree>(engine, "Object", "Octree");
    RegisterSubclass<RefCounted, Octree>(engine, "RefCounted", "Octree");

#ifdef URHO3D_NAVIGATION
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("OffMeshConnection", asBEHAVE_ADDREF, "void f()", AS_METHODPR(OffMeshConnection, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void AllocateNetworkState()", AS_METHODPR(OffMeshConnection, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void OffMeshConnection::ApplyAttributes() override | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void ApplyAttributes()", AS_METHODPR(OffMeshConnection, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void OffMeshConnection::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(OffMeshConnection, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool GetAnimationEnabled() const", AS_METHODPR(OffMeshConnection, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool get_animationEnabled() const", AS_METHODPR(OffMeshConnection, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // unsigned OffMeshConnection::GetAreaID() const | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "uint GetAreaID() const", AS_METHODPR(OffMeshConnection, GetAreaID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "uint get_areaID() const", AS_METHODPR(OffMeshConnection, GetAreaID, () const, unsigned), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "Variant GetAttribute(uint) const", AS_METHODPR(OffMeshConnection, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "Variant get_attributes(uint) const", AS_METHODPR(OffMeshConnection, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "Variant GetAttribute(const String&in) const", AS_METHODPR(OffMeshConnection, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(OffMeshConnection, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(OffMeshConnection, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(OffMeshConnection, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(OffMeshConnection, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "Variant GetAttributeDefault(uint) const", AS_METHODPR(OffMeshConnection, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "Variant get_attributeDefaults(uint) const", AS_METHODPR(OffMeshConnection, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(OffMeshConnection, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool GetBlockEvents() const", AS_METHODPR(OffMeshConnection, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "const String& GetCategory() const", AS_METHODPR(OffMeshConnection, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "const String& get_category() const", AS_METHODPR(OffMeshConnection, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "Component@+ GetComponent(StringHash) const", AS_METHODPR(OffMeshConnection, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    // Node* OffMeshConnection::GetEndPoint() const | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "Node@+ GetEndPoint() const", AS_METHODPR(OffMeshConnection, GetEndPoint, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "Node@+ get_endPoint() const", AS_METHODPR(OffMeshConnection, GetEndPoint, () const, Node*), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "VariantMap& GetEventDataMap() const", AS_METHODPR(OffMeshConnection, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "Object@+ GetEventSender() const", AS_METHODPR(OffMeshConnection, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(OffMeshConnection, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(OffMeshConnection, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "const VariantMap& GetGlobalVars() const", AS_METHODPR(OffMeshConnection, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "const VariantMap& get_globalVars() const", AS_METHODPR(OffMeshConnection, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "uint GetID() const", AS_METHODPR(OffMeshConnection, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "uint get_id() const", AS_METHODPR(OffMeshConnection, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(OffMeshConnection, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned OffMeshConnection::GetMask() const | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "uint GetMask() const", AS_METHODPR(OffMeshConnection, GetMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "uint get_mask() const", AS_METHODPR(OffMeshConnection, GetMask, () const, unsigned), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "Node@+ GetNode() const", AS_METHODPR(OffMeshConnection, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "Node@+ get_node() const", AS_METHODPR(OffMeshConnection, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "uint GetNumAttributes() const", AS_METHODPR(OffMeshConnection, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "uint get_numAttributes() const", AS_METHODPR(OffMeshConnection, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "uint GetNumNetworkAttributes() const", AS_METHODPR(OffMeshConnection, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(OffMeshConnection, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(OffMeshConnection, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(OffMeshConnection, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float OffMeshConnection::GetRadius() const | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "float GetRadius() const", AS_METHODPR(OffMeshConnection, GetRadius, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "float get_radius() const", AS_METHODPR(OffMeshConnection, GetRadius, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "Scene@+ GetScene() const", AS_METHODPR(OffMeshConnection, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(OffMeshConnection, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "StringHash GetType() const", AS_METHODPR(OffMeshConnection, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "StringHash get_type() const", AS_METHODPR(OffMeshConnection, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "const String& GetTypeName() const", AS_METHODPR(OffMeshConnection, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "const String& get_typeName() const", AS_METHODPR(OffMeshConnection, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool HasEventHandlers() const", AS_METHODPR(OffMeshConnection, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(OffMeshConnection, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(OffMeshConnection, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool OffMeshConnection::IsBidirectional() const | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool IsBidirectional() const", AS_METHODPR(OffMeshConnection, IsBidirectional, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool get_bidirectional() const", AS_METHODPR(OffMeshConnection, IsBidirectional, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool IsEnabled() const", AS_METHODPR(OffMeshConnection, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool get_enabled() const", AS_METHODPR(OffMeshConnection, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool IsEnabledEffective() const", AS_METHODPR(OffMeshConnection, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool get_enabledEffective() const", AS_METHODPR(OffMeshConnection, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool IsInstanceOf(StringHash) const", AS_METHODPR(OffMeshConnection, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool IsReplicated() const", AS_METHODPR(OffMeshConnection, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool get_replicated() const", AS_METHODPR(OffMeshConnection, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool IsTemporary() const", AS_METHODPR(OffMeshConnection, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool get_temporary() const", AS_METHODPR(OffMeshConnection, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool Load(Deserializer&)", AS_METHODPR(OffMeshConnection, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(OffMeshConnection, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool LoadXML(const XMLElement&in)", AS_METHODPR(OffMeshConnection, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "void MarkNetworkUpdate()", AS_METHODPR(OffMeshConnection, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // explicit OffMeshConnection::OffMeshConnection(Context* context) | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectBehaviour("OffMeshConnection", asBEHAVE_FACTORY, "OffMeshConnection@+ f()", AS_FUNCTION(OffMeshConnection_OffMeshConnection_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(OffMeshConnection, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(OffMeshConnection, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(OffMeshConnection, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "void OnSetEnabled()", AS_METHODPR(OffMeshConnection, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "void PrepareNetworkUpdate()", AS_METHODPR(OffMeshConnection, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(OffMeshConnection, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(OffMeshConnection, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("OffMeshConnection", "int Refs() const", AS_METHODPR(OffMeshConnection, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "int get_refs() const", AS_METHODPR(OffMeshConnection, Refs, () const, int), AS_CALL_THISCALL);
    // static void OffMeshConnection::RegisterObject(Context* context) | File: ../Navigation/OffMeshConnection.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("OffMeshConnection", asBEHAVE_RELEASE, "void f()", AS_METHODPR(OffMeshConnection, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "void Remove()", AS_METHODPR(OffMeshConnection, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(OffMeshConnection, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void RemoveInstanceDefault()", AS_METHODPR(OffMeshConnection, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void RemoveObjectAnimation()", AS_METHODPR(OffMeshConnection, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void ResetToDefault()", AS_METHODPR(OffMeshConnection, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool Save(Serializer&) const", AS_METHODPR(OffMeshConnection, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool SaveDefaultAttributes() const", AS_METHODPR(OffMeshConnection, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool SaveJSON(JSONValue&) const", AS_METHODPR(OffMeshConnection, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool SaveXML(XMLElement&) const", AS_METHODPR(OffMeshConnection, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SendEvent(StringHash)", AS_METHODPR(OffMeshConnection, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(OffMeshConnection, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAnimationEnabled(bool)", AS_METHODPR(OffMeshConnection, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_animationEnabled(bool)", AS_METHODPR(OffMeshConnection, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAnimationTime(float)", AS_METHODPR(OffMeshConnection, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void OffMeshConnection::SetAreaID(unsigned newAreaID) | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAreaID(uint)", AS_METHODPR(OffMeshConnection, SetAreaID, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_areaID(uint)", AS_METHODPR(OffMeshConnection, SetAreaID, (unsigned), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(OffMeshConnection, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(OffMeshConnection, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(OffMeshConnection, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(OffMeshConnection, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(OffMeshConnection, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(OffMeshConnection, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(OffMeshConnection, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void OffMeshConnection::SetBidirectional(bool enabled) | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetBidirectional(bool)", AS_METHODPR(OffMeshConnection, SetBidirectional, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_bidirectional(bool)", AS_METHODPR(OffMeshConnection, SetBidirectional, (bool), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetBlockEvents(bool)", AS_METHODPR(OffMeshConnection, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetEnabled(bool)", AS_METHODPR(OffMeshConnection, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_enabled(bool)", AS_METHODPR(OffMeshConnection, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void OffMeshConnection::SetEndPoint(Node* node) | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetEndPoint(Node@+)", AS_METHODPR(OffMeshConnection, SetEndPoint, (Node*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_endPoint(Node@+)", AS_METHODPR(OffMeshConnection, SetEndPoint, (Node*), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(OffMeshConnection, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(OffMeshConnection, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetInstanceDefault(bool)", AS_METHODPR(OffMeshConnection, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(OffMeshConnection, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void OffMeshConnection::SetMask(unsigned newMask) | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetMask(uint)", AS_METHODPR(OffMeshConnection, SetMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_mask(uint)", AS_METHODPR(OffMeshConnection, SetMask, (unsigned), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(OffMeshConnection, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(OffMeshConnection, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(OffMeshConnection, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void OffMeshConnection::SetRadius(float radius) | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetRadius(float)", AS_METHODPR(OffMeshConnection, SetRadius, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_radius(float)", AS_METHODPR(OffMeshConnection, SetRadius, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetTemporary(bool)", AS_METHODPR(OffMeshConnection, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_temporary(bool)", AS_METHODPR(OffMeshConnection, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void UnsubscribeFromAllEvents()", AS_METHODPR(OffMeshConnection, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(OffMeshConnection_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(OffMeshConnection, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(OffMeshConnection, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(OffMeshConnection, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("OffMeshConnection", "int WeakRefs() const", AS_METHODPR(OffMeshConnection, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "int get_weakRefs() const", AS_METHODPR(OffMeshConnection, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(OffMeshConnection, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(OffMeshConnection, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(OffMeshConnection, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(OffMeshConnection, "OffMeshConnection")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(OffMeshConnection, "OffMeshConnection")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(OffMeshConnection, "OffMeshConnection")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(OffMeshConnection, "OffMeshConnection")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(OffMeshConnection, "OffMeshConnection")
#endif
#ifdef REGISTER_MANUAL_PART_OffMeshConnection
    REGISTER_MANUAL_PART_OffMeshConnection(OffMeshConnection, "OffMeshConnection")
#endif
    RegisterSubclass<Component, OffMeshConnection>(engine, "Component", "OffMeshConnection");
    RegisterSubclass<Animatable, OffMeshConnection>(engine, "Animatable", "OffMeshConnection");
    RegisterSubclass<Serializable, OffMeshConnection>(engine, "Serializable", "OffMeshConnection");
    RegisterSubclass<Object, OffMeshConnection>(engine, "Object", "OffMeshConnection");
    RegisterSubclass<RefCounted, OffMeshConnection>(engine, "RefCounted", "OffMeshConnection");
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("OggVorbisSoundStream", asBEHAVE_ADDREF, "void f()", AS_METHODPR(OggVorbisSoundStream, AddRef, (), void), AS_CALL_THISCALL);
    // unsigned OggVorbisSoundStream::GetData(signed char* dest, unsigned numBytes) override | File: ../Audio/OggVorbisSoundStream.h
    // Error: type "signed char*" can not automatically bind
    // float SoundStream::GetFrequency() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "float GetFrequency() const", AS_METHODPR(OggVorbisSoundStream, GetFrequency, () const, float), AS_CALL_THISCALL);
    // unsigned SoundStream::GetIntFrequency() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "uint GetIntFrequency() const", AS_METHODPR(OggVorbisSoundStream, GetIntFrequency, () const, unsigned), AS_CALL_THISCALL);
    // unsigned SoundStream::GetSampleSize() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "uint GetSampleSize() const", AS_METHODPR(OggVorbisSoundStream, GetSampleSize, () const, unsigned), AS_CALL_THISCALL);
    // bool SoundStream::GetStopAtEnd() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "bool GetStopAtEnd() const", AS_METHODPR(OggVorbisSoundStream, GetStopAtEnd, () const, bool), AS_CALL_THISCALL);
    // bool SoundStream::IsSixteenBit() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "bool IsSixteenBit() const", AS_METHODPR(OggVorbisSoundStream, IsSixteenBit, () const, bool), AS_CALL_THISCALL);
    // bool SoundStream::IsStereo() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "bool IsStereo() const", AS_METHODPR(OggVorbisSoundStream, IsStereo, () const, bool), AS_CALL_THISCALL);
    // explicit OggVorbisSoundStream::OggVorbisSoundStream(const Sound* sound) | File: ../Audio/OggVorbisSoundStream.h
    engine->RegisterObjectBehaviour("OggVorbisSoundStream", asBEHAVE_FACTORY, "OggVorbisSoundStream@+ f(Sound@+)", AS_FUNCTION(OggVorbisSoundStream_OggVorbisSoundStream_Sound), AS_CALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "int Refs() const", AS_METHODPR(OggVorbisSoundStream, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OggVorbisSoundStream", "int get_refs() const", AS_METHODPR(OggVorbisSoundStream, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("OggVorbisSoundStream", asBEHAVE_RELEASE, "void f()", AS_METHODPR(OggVorbisSoundStream, ReleaseRef, (), void), AS_CALL_THISCALL);
    // bool OggVorbisSoundStream::Seek(unsigned sample_number) override | File: ../Audio/OggVorbisSoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "bool Seek(uint)", AS_METHODPR(OggVorbisSoundStream, Seek, (unsigned), bool), AS_CALL_THISCALL);
    // void SoundStream::SetFormat(unsigned frequency, bool sixteenBit, bool stereo) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "void SetFormat(uint, bool, bool)", AS_METHODPR(OggVorbisSoundStream, SetFormat, (unsigned, bool, bool), void), AS_CALL_THISCALL);
    // void SoundStream::SetStopAtEnd(bool enable) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "void SetStopAtEnd(bool)", AS_METHODPR(OggVorbisSoundStream, SetStopAtEnd, (bool), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "int WeakRefs() const", AS_METHODPR(OggVorbisSoundStream, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("OggVorbisSoundStream", "int get_weakRefs() const", AS_METHODPR(OggVorbisSoundStream, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_SoundStream
    REGISTER_MANUAL_PART_SoundStream(OggVorbisSoundStream, "OggVorbisSoundStream")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(OggVorbisSoundStream, "OggVorbisSoundStream")
#endif
#ifdef REGISTER_MANUAL_PART_OggVorbisSoundStream
    REGISTER_MANUAL_PART_OggVorbisSoundStream(OggVorbisSoundStream, "OggVorbisSoundStream")
#endif
    RegisterSubclass<SoundStream, OggVorbisSoundStream>(engine, "SoundStream", "OggVorbisSoundStream");
    RegisterSubclass<RefCounted, OggVorbisSoundStream>(engine, "RefCounted", "OggVorbisSoundStream");

    // unsigned OcclusionBatch::drawCount_ | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectProperty("OcclusionBatch", "uint drawCount", offsetof(OcclusionBatch, drawCount_));
    // unsigned OcclusionBatch::drawStart_ | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectProperty("OcclusionBatch", "uint drawStart", offsetof(OcclusionBatch, drawStart_));
    // const void* OcclusionBatch::indexData_ | File: ../Graphics/OcclusionBuffer.h
    // const void* can not be registered
    // unsigned OcclusionBatch::indexSize_ | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectProperty("OcclusionBatch", "uint indexSize", offsetof(OcclusionBatch, indexSize_));
    // Matrix3x4 OcclusionBatch::model_ | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectProperty("OcclusionBatch", "Matrix3x4 model", offsetof(OcclusionBatch, model_));
    // const void* OcclusionBatch::vertexData_ | File: ../Graphics/OcclusionBuffer.h
    // const void* can not be registered
    // unsigned OcclusionBatch::vertexSize_ | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectProperty("OcclusionBatch", "uint vertexSize", offsetof(OcclusionBatch, vertexSize_));
    // OcclusionBatch& OcclusionBatch::operator=(const OcclusionBatch&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<OcclusionBatch>(engine, "OcclusionBatch");
#ifdef REGISTER_MANUAL_PART_OcclusionBatch
    REGISTER_MANUAL_PART_OcclusionBatch(OcclusionBatch, "OcclusionBatch")
#endif

    // int* OcclusionBufferData::data_ | File: ../Graphics/OcclusionBuffer.h
    // int* can not be registered
    // SharedArrayPtr<int> OcclusionBufferData::dataWithSafety_ | File: ../Graphics/OcclusionBuffer.h
    // Error: type "SharedArrayPtr<int>" can not automatically bind
    // bool OcclusionBufferData::used_ | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectProperty("OcclusionBufferData", "bool used", offsetof(OcclusionBufferData, used_));
    // OcclusionBufferData& OcclusionBufferData::operator=(const OcclusionBufferData&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<OcclusionBufferData>(engine, "OcclusionBufferData");
#ifdef REGISTER_MANUAL_PART_OcclusionBufferData
    REGISTER_MANUAL_PART_OcclusionBufferData(OcclusionBufferData, "OcclusionBufferData")
#endif

    // Drawable* OctreeQueryResult::drawable_ | File: ../Graphics/OctreeQuery.h
    // Drawable* can not be registered
    // Node* OctreeQueryResult::node_ | File: ../Graphics/OctreeQuery.h
    // Node* can not be registered
    // OctreeQueryResult& OctreeQueryResult::operator=(const OctreeQueryResult&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<OctreeQueryResult>(engine, "OctreeQueryResult");
#ifdef REGISTER_MANUAL_PART_OctreeQueryResult
    REGISTER_MANUAL_PART_OctreeQueryResult(OctreeQueryResult, "OctreeQueryResult")
#endif

}

}
