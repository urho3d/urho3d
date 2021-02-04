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
    engine->RegisterObjectBehaviour("Object", asBEHAVE_ADDREF, "void f()", asMETHODPR(Object, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "bool GetBlockEvents() const", asMETHODPR(Object, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "const String& GetCategory() const", asMETHODPR(Object, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Object", "const String& get_category() const", asMETHODPR(Object, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "VariantMap& GetEventDataMap() const", asMETHODPR(Object, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "Object@+ GetEventSender() const", asMETHODPR(Object, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Object, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Object", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Object, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "const VariantMap& GetGlobalVars() const", asMETHODPR(Object, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Object", "const VariantMap& get_globalVars() const", asMETHODPR(Object, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Object, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "StringHash GetType() const", asMETHODPR(Object, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Object", "StringHash get_type() const", asMETHODPR(Object, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "const String& GetTypeName() const", asMETHODPR(Object, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Object", "const String& get_typeName() const", asMETHODPR(Object, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "bool HasEventHandlers() const", asMETHODPR(Object, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Object, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Object, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "bool IsInstanceOf(StringHash) const", asMETHODPR(Object, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Object, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Object", "int Refs() const", asMETHODPR(Object, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Object", "int get_refs() const", asMETHODPR(Object, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Object", asBEHAVE_RELEASE, "void f()", asMETHODPR(Object, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void SendEvent(StringHash)", asMETHODPR(Object, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Object, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void SetBlockEvents(bool)", asMETHODPR(Object, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Object, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Object", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Object, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void UnsubscribeFromAllEvents()", asMETHODPR(Object, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Object_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Object, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Object, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Object", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Object, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Object", "int WeakRefs() const", asMETHODPR(Object, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Object", "int get_weakRefs() const", asMETHODPR(Object, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Object, "Object")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Object, "Object")
#endif
    RegisterSubclass<RefCounted, Object>(engine, "RefCounted", "Object");

    // void ObjectAnimation::AddAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "void AddAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ObjectAnimation, AddAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ObjectAnimation", asBEHAVE_ADDREF, "void f()", asMETHODPR(ObjectAnimation, AddRef, (), void), asCALL_THISCALL);
    // bool ObjectAnimation::BeginLoad(Deserializer& source) override | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool BeginLoad(Deserializer&)", asMETHODPR(ObjectAnimation, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool EndLoad()", asMETHODPR(ObjectAnimation, EndLoad, (), bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(ObjectAnimation, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // ValueAnimation* ObjectAnimation::GetAttributeAnimation(const String& name) const | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ObjectAnimation, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "ValueAnimation@+ get_attributeAnimations(const String&in) const", asMETHODPR(ObjectAnimation, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // ValueAnimationInfo* ObjectAnimation::GetAttributeAnimationInfo(const String& name) const | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "ValueAnimationInfo@+ GetAttributeAnimationInfo(const String&in) const", asMETHODPR(ObjectAnimation, GetAttributeAnimationInfo, (const String&) const, ValueAnimationInfo*), asCALL_THISCALL);
    // const HashMap<String, SharedPtr<ValueAnimationInfo>>& ObjectAnimation::GetAttributeAnimationInfos() const | File: ../Scene/ObjectAnimation.h
    // Error: type "const HashMap<String, SharedPtr<ValueAnimationInfo>>&" can not automatically bind
    // float ObjectAnimation::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ObjectAnimation, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "float get_speeds(const String&in) const", asMETHODPR(ObjectAnimation, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // WrapMode ObjectAnimation::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ObjectAnimation, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "WrapMode get_wrapModes(const String&in) const", asMETHODPR(ObjectAnimation, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool GetBlockEvents() const", asMETHODPR(ObjectAnimation, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "const String& GetCategory() const", asMETHODPR(ObjectAnimation, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "const String& get_category() const", asMETHODPR(ObjectAnimation, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "VariantMap& GetEventDataMap() const", asMETHODPR(ObjectAnimation, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "Object@+ GetEventSender() const", asMETHODPR(ObjectAnimation, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ObjectAnimation, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ObjectAnimation, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "const VariantMap& GetGlobalVars() const", asMETHODPR(ObjectAnimation, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "const VariantMap& get_globalVars() const", asMETHODPR(ObjectAnimation, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "uint GetMemoryUse() const", asMETHODPR(ObjectAnimation, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "uint get_memoryUse() const", asMETHODPR(ObjectAnimation, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "const String& GetName() const", asMETHODPR(ObjectAnimation, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "const String& get_name() const", asMETHODPR(ObjectAnimation, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "StringHash GetNameHash() const", asMETHODPR(ObjectAnimation, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ObjectAnimation, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "StringHash GetType() const", asMETHODPR(ObjectAnimation, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "StringHash get_type() const", asMETHODPR(ObjectAnimation, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "const String& GetTypeName() const", asMETHODPR(ObjectAnimation, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "const String& get_typeName() const", asMETHODPR(ObjectAnimation, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "uint GetUseTimer()", asMETHODPR(ObjectAnimation, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "uint get_useTimer()", asMETHODPR(ObjectAnimation, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool HasEventHandlers() const", asMETHODPR(ObjectAnimation, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ObjectAnimation, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ObjectAnimation, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool IsInstanceOf(StringHash) const", asMETHODPR(ObjectAnimation, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool Load(Deserializer&)", asMETHODPR(ObjectAnimation, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool LoadFile(const String&in)", asMETHODPR(ObjectAnimation, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "bool Load(const String&in)", asMETHODPR(ObjectAnimation, LoadFile, (const String&), bool), asCALL_THISCALL);
    // bool ObjectAnimation::LoadJSON(const JSONValue& source) | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ObjectAnimation, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool ObjectAnimation::LoadXML(const XMLElement& source) | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool LoadXML(const XMLElement&in)", asMETHODPR(ObjectAnimation, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // explicit ObjectAnimation::ObjectAnimation(Context* context) | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectBehaviour("ObjectAnimation", asBEHAVE_FACTORY, "ObjectAnimation@+ f()", asFUNCTION(ObjectAnimation_ObjectAnimation_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ObjectAnimation, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ObjectAnimation", "int Refs() const", asMETHODPR(ObjectAnimation, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "int get_refs() const", asMETHODPR(ObjectAnimation, Refs, () const, int), asCALL_THISCALL);
    // static void ObjectAnimation::RegisterObject(Context* context) | File: ../Scene/ObjectAnimation.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ObjectAnimation", asBEHAVE_RELEASE, "void f()", asMETHODPR(ObjectAnimation, ReleaseRef, (), void), asCALL_THISCALL);
    // void ObjectAnimation::RemoveAttributeAnimation(const String& name) | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ObjectAnimation, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void ObjectAnimation::RemoveAttributeAnimation(ValueAnimation* attributeAnimation) | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "void RemoveAttributeAnimation(ValueAnimation@+)", asMETHODPR(ObjectAnimation, RemoveAttributeAnimation, (ValueAnimation*), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "void ResetUseTimer()", asMETHODPR(ObjectAnimation, ResetUseTimer, (), void), asCALL_THISCALL);
    // bool ObjectAnimation::Save(Serializer& dest) const override | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool Save(Serializer&) const", asMETHODPR(ObjectAnimation, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool SaveFile(const String&in) const", asMETHODPR(ObjectAnimation, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "bool Save(const String&in) const", asMETHODPR(ObjectAnimation, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // bool ObjectAnimation::SaveJSON(JSONValue& dest) const | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool SaveJSON(JSONValue&) const", asMETHODPR(ObjectAnimation, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool ObjectAnimation::SaveXML(XMLElement& dest) const | File: ../Scene/ObjectAnimation.h
    engine->RegisterObjectMethod("ObjectAnimation", "bool SaveXML(XMLElement&) const", asMETHODPR(ObjectAnimation, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SendEvent(StringHash)", asMETHODPR(ObjectAnimation, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ObjectAnimation, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(ObjectAnimation, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SetBlockEvents(bool)", asMETHODPR(ObjectAnimation, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ObjectAnimation, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ObjectAnimation, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SetMemoryUse(uint)", asMETHODPR(ObjectAnimation, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ObjectAnimation", "void SetName(const String&in)", asMETHODPR(ObjectAnimation, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "void set_name(const String&in)", asMETHODPR(ObjectAnimation, SetName, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void UnsubscribeFromAllEvents()", asMETHODPR(ObjectAnimation, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ObjectAnimation_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ObjectAnimation, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ObjectAnimation, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectAnimation", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ObjectAnimation, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ObjectAnimation", "int WeakRefs() const", asMETHODPR(ObjectAnimation, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectAnimation", "int get_weakRefs() const", asMETHODPR(ObjectAnimation, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("ObjectFactory", asBEHAVE_ADDREF, "void f()", asMETHODPR(ObjectFactory, AddRef, (), void), asCALL_THISCALL);
    // virtual SharedPtr<Object> ObjectFactory::CreateObject()=0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectFactory", "Object@+ CreateObject()", asFUNCTION(ObjectFactory_CreateObject_void), asCALL_CDECL_OBJFIRST);
    // Context* ObjectFactory::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // StringHash ObjectFactory::GetType() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectFactory", "StringHash GetType() const", asMETHODPR(ObjectFactory, GetType, () const, StringHash), asCALL_THISCALL);
    // const TypeInfo* ObjectFactory::GetTypeInfo() const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // const String& ObjectFactory::GetTypeName() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ObjectFactory", "const String& GetTypeName() const", asMETHODPR(ObjectFactory, GetTypeName, () const, const String&), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ObjectFactory", "int Refs() const", asMETHODPR(ObjectFactory, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectFactory", "int get_refs() const", asMETHODPR(ObjectFactory, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ObjectFactory", asBEHAVE_RELEASE, "void f()", asMETHODPR(ObjectFactory, ReleaseRef, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ObjectFactory", "int WeakRefs() const", asMETHODPR(ObjectFactory, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ObjectFactory", "int get_weakRefs() const", asMETHODPR(ObjectFactory, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ObjectFactory, "ObjectFactory")
#endif
#ifdef REGISTER_MANUAL_PART_ObjectFactory
    REGISTER_MANUAL_PART_ObjectFactory(ObjectFactory, "ObjectFactory")
#endif
    RegisterSubclass<RefCounted, ObjectFactory>(engine, "RefCounted", "ObjectFactory");

#ifdef URHO3D_NAVIGATION
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Obstacle", asBEHAVE_ADDREF, "void f()", asMETHODPR(Obstacle, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void AllocateNetworkState()", asMETHODPR(Obstacle, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void ApplyAttributes()", asMETHODPR(Obstacle, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Obstacle::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Obstacle, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // void Obstacle::DrawDebugGeometry(bool depthTest) | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "void DrawDebugGeometry(bool)", asMETHODPR(Obstacle, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "bool GetAnimationEnabled() const", asMETHODPR(Obstacle, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "bool get_animationEnabled() const", asMETHODPR(Obstacle, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "Variant GetAttribute(uint) const", asMETHODPR(Obstacle, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "Variant get_attributes(uint) const", asMETHODPR(Obstacle, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "Variant GetAttribute(const String&in) const", asMETHODPR(Obstacle, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Obstacle, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Obstacle, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Obstacle, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Obstacle, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "Variant GetAttributeDefault(uint) const", asMETHODPR(Obstacle, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "Variant get_attributeDefaults(uint) const", asMETHODPR(Obstacle, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Obstacle, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "bool GetBlockEvents() const", asMETHODPR(Obstacle, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "const String& GetCategory() const", asMETHODPR(Obstacle, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "const String& get_category() const", asMETHODPR(Obstacle, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "Component@+ GetComponent(StringHash) const", asMETHODPR(Obstacle, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("Obstacle", "VariantMap& GetEventDataMap() const", asMETHODPR(Obstacle, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "Object@+ GetEventSender() const", asMETHODPR(Obstacle, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Obstacle, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Obstacle, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "const VariantMap& GetGlobalVars() const", asMETHODPR(Obstacle, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "const VariantMap& get_globalVars() const", asMETHODPR(Obstacle, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // float Obstacle::GetHeight() const | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "float GetHeight() const", asMETHODPR(Obstacle, GetHeight, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "float get_height() const", asMETHODPR(Obstacle, GetHeight, () const, float), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "uint GetID() const", asMETHODPR(Obstacle, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "uint get_id() const", asMETHODPR(Obstacle, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Obstacle, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "Node@+ GetNode() const", asMETHODPR(Obstacle, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "Node@+ get_node() const", asMETHODPR(Obstacle, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "uint GetNumAttributes() const", asMETHODPR(Obstacle, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "uint get_numAttributes() const", asMETHODPR(Obstacle, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "uint GetNumNetworkAttributes() const", asMETHODPR(Obstacle, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Obstacle, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Obstacle, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Obstacle, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned Obstacle::GetObstacleID() const | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "uint GetObstacleID() const", asMETHODPR(Obstacle, GetObstacleID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "uint get_obstacleId() const", asMETHODPR(Obstacle, GetObstacleID, () const, unsigned), asCALL_THISCALL);
    // float Obstacle::GetRadius() const | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "float GetRadius() const", asMETHODPR(Obstacle, GetRadius, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "float get_radius() const", asMETHODPR(Obstacle, GetRadius, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "Scene@+ GetScene() const", asMETHODPR(Obstacle, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Obstacle, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "StringHash GetType() const", asMETHODPR(Obstacle, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "StringHash get_type() const", asMETHODPR(Obstacle, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "const String& GetTypeName() const", asMETHODPR(Obstacle, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "const String& get_typeName() const", asMETHODPR(Obstacle, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "bool HasEventHandlers() const", asMETHODPR(Obstacle, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Obstacle, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Obstacle, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "bool IsEnabled() const", asMETHODPR(Obstacle, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "bool get_enabled() const", asMETHODPR(Obstacle, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "bool IsEnabledEffective() const", asMETHODPR(Obstacle, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "bool get_enabledEffective() const", asMETHODPR(Obstacle, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "bool IsInstanceOf(StringHash) const", asMETHODPR(Obstacle, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "bool IsReplicated() const", asMETHODPR(Obstacle, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "bool get_replicated() const", asMETHODPR(Obstacle, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool IsTemporary() const", asMETHODPR(Obstacle, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "bool get_temporary() const", asMETHODPR(Obstacle, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool Load(Deserializer&)", asMETHODPR(Obstacle, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Obstacle, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "bool LoadXML(const XMLElement&in)", asMETHODPR(Obstacle, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "void MarkNetworkUpdate()", asMETHODPR(Obstacle, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // explicit Obstacle::Obstacle(Context* context) | File: ../Navigation/Obstacle.h
    engine->RegisterObjectBehaviour("Obstacle", asBEHAVE_FACTORY, "Obstacle@+ f()", asFUNCTION(Obstacle_Obstacle_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Obstacle, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Obstacle, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Obstacle, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Obstacle::OnSetEnabled() override | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "void OnSetEnabled()", asMETHODPR(Obstacle, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "void PrepareNetworkUpdate()", asMETHODPR(Obstacle, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Obstacle, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Obstacle, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Obstacle", "int Refs() const", asMETHODPR(Obstacle, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "int get_refs() const", asMETHODPR(Obstacle, Refs, () const, int), asCALL_THISCALL);
    // static void Obstacle::RegisterObject(Context* context) | File: ../Navigation/Obstacle.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Obstacle", asBEHAVE_RELEASE, "void f()", asMETHODPR(Obstacle, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "void Remove()", asMETHODPR(Obstacle, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Obstacle, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void RemoveInstanceDefault()", asMETHODPR(Obstacle, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void RemoveObjectAnimation()", asMETHODPR(Obstacle, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void ResetToDefault()", asMETHODPR(Obstacle, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "bool Save(Serializer&) const", asMETHODPR(Obstacle, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool SaveDefaultAttributes() const", asMETHODPR(Obstacle, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "bool SaveJSON(JSONValue&) const", asMETHODPR(Obstacle, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "bool SaveXML(XMLElement&) const", asMETHODPR(Obstacle, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void SendEvent(StringHash)", asMETHODPR(Obstacle, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Obstacle, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetAnimationEnabled(bool)", asMETHODPR(Obstacle, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_animationEnabled(bool)", asMETHODPR(Obstacle, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetAnimationTime(float)", asMETHODPR(Obstacle, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Obstacle, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Obstacle, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Obstacle, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Obstacle, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Obstacle, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Obstacle, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Obstacle, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void SetBlockEvents(bool)", asMETHODPR(Obstacle, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Obstacle", "void SetEnabled(bool)", asMETHODPR(Obstacle, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_enabled(bool)", asMETHODPR(Obstacle, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Obstacle, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Obstacle, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Obstacle::SetHeight(float newHeight) | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "void SetHeight(float)", asMETHODPR(Obstacle, SetHeight, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_height(float)", asMETHODPR(Obstacle, SetHeight, (float), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void SetInstanceDefault(bool)", asMETHODPR(Obstacle, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Obstacle, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Obstacle, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Obstacle, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Obstacle", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Obstacle, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Obstacle::SetRadius(float newRadius) | File: ../Navigation/Obstacle.h
    engine->RegisterObjectMethod("Obstacle", "void SetRadius(float)", asMETHODPR(Obstacle, SetRadius, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_radius(float)", asMETHODPR(Obstacle, SetRadius, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void SetTemporary(bool)", asMETHODPR(Obstacle, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "void set_temporary(bool)", asMETHODPR(Obstacle, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void UnsubscribeFromAllEvents()", asMETHODPR(Obstacle, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Obstacle_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Obstacle, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Obstacle, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Obstacle", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Obstacle, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Obstacle", "int WeakRefs() const", asMETHODPR(Obstacle, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Obstacle", "int get_weakRefs() const", asMETHODPR(Obstacle, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Obstacle, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Obstacle, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Obstacle", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Obstacle, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("OcclusionBuffer", asBEHAVE_ADDREF, "void f()", asMETHODPR(OcclusionBuffer, AddRef, (), void), asCALL_THISCALL);
    // bool OcclusionBuffer::AddTriangles(const Matrix3x4& model, const void* vertexData, unsigned vertexSize, unsigned vertexStart, unsigned vertexCount) | File: ../Graphics/OcclusionBuffer.h
    // Error: type "const void*" can not automatically bind
    // bool OcclusionBuffer::AddTriangles(const Matrix3x4& model, const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount) | File: ../Graphics/OcclusionBuffer.h
    // Error: type "const void*" can not automatically bind
    // void OcclusionBuffer::BuildDepthHierarchy() | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void BuildDepthHierarchy()", asMETHODPR(OcclusionBuffer, BuildDepthHierarchy, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void OcclusionBuffer::Clear() | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void Clear()", asMETHODPR(OcclusionBuffer, Clear, (), void), asCALL_THISCALL);
    // void OcclusionBuffer::DrawBatch(const OcclusionBatch& batch, unsigned threadIndex) | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void DrawBatch(const OcclusionBatch&in, uint)", asMETHODPR(OcclusionBuffer, DrawBatch, (const OcclusionBatch&, unsigned), void), asCALL_THISCALL);
    // void OcclusionBuffer::DrawTriangles() | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void DrawTriangles()", asMETHODPR(OcclusionBuffer, DrawTriangles, (), void), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool GetBlockEvents() const", asMETHODPR(OcclusionBuffer, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // int* OcclusionBuffer::GetBuffer() const | File: ../Graphics/OcclusionBuffer.h
    // Error: type "int*" can not automatically bind
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "const String& GetCategory() const", asMETHODPR(OcclusionBuffer, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "const String& get_category() const", asMETHODPR(OcclusionBuffer, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // CullMode OcclusionBuffer::GetCullMode() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "CullMode GetCullMode() const", asMETHODPR(OcclusionBuffer, GetCullMode, () const, CullMode), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "VariantMap& GetEventDataMap() const", asMETHODPR(OcclusionBuffer, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "Object@+ GetEventSender() const", asMETHODPR(OcclusionBuffer, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(OcclusionBuffer, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "const Variant& get_globalVar(StringHash) const", asMETHODPR(OcclusionBuffer, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "const VariantMap& GetGlobalVars() const", asMETHODPR(OcclusionBuffer, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "const VariantMap& get_globalVars() const", asMETHODPR(OcclusionBuffer, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int OcclusionBuffer::GetHeight() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "int GetHeight() const", asMETHODPR(OcclusionBuffer, GetHeight, () const, int), asCALL_THISCALL);
    // unsigned OcclusionBuffer::GetMaxTriangles() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "uint GetMaxTriangles() const", asMETHODPR(OcclusionBuffer, GetMaxTriangles, () const, unsigned), asCALL_THISCALL);
    // unsigned OcclusionBuffer::GetNumTriangles() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "uint GetNumTriangles() const", asMETHODPR(OcclusionBuffer, GetNumTriangles, () const, unsigned), asCALL_THISCALL);
    // const Matrix4& OcclusionBuffer::GetProjection() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "const Matrix4& GetProjection() const", asMETHODPR(OcclusionBuffer, GetProjection, () const, const Matrix4&), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(OcclusionBuffer, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "StringHash GetType() const", asMETHODPR(OcclusionBuffer, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "StringHash get_type() const", asMETHODPR(OcclusionBuffer, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "const String& GetTypeName() const", asMETHODPR(OcclusionBuffer, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "const String& get_typeName() const", asMETHODPR(OcclusionBuffer, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned OcclusionBuffer::GetUseTimer() | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "uint GetUseTimer()", asMETHODPR(OcclusionBuffer, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // const Matrix3x4& OcclusionBuffer::GetView() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "const Matrix3x4& GetView() const", asMETHODPR(OcclusionBuffer, GetView, () const, const Matrix3x4&), asCALL_THISCALL);
    // int OcclusionBuffer::GetWidth() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "int GetWidth() const", asMETHODPR(OcclusionBuffer, GetWidth, () const, int), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool HasEventHandlers() const", asMETHODPR(OcclusionBuffer, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(OcclusionBuffer, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(OcclusionBuffer, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool IsInstanceOf(StringHash) const", asMETHODPR(OcclusionBuffer, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool OcclusionBuffer::IsThreaded() const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool IsThreaded() const", asMETHODPR(OcclusionBuffer, IsThreaded, () const, bool), asCALL_THISCALL);
    // bool OcclusionBuffer::IsVisible(const BoundingBox& worldSpaceBox) const | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool IsVisible(const BoundingBox&in) const", asMETHODPR(OcclusionBuffer, IsVisible, (const BoundingBox&) const, bool), asCALL_THISCALL);
    // explicit OcclusionBuffer::OcclusionBuffer(Context* context) | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectBehaviour("OcclusionBuffer", asBEHAVE_FACTORY, "OcclusionBuffer@+ f()", asFUNCTION(OcclusionBuffer_OcclusionBuffer_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(OcclusionBuffer, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("OcclusionBuffer", "int Refs() const", asMETHODPR(OcclusionBuffer, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "int get_refs() const", asMETHODPR(OcclusionBuffer, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("OcclusionBuffer", asBEHAVE_RELEASE, "void f()", asMETHODPR(OcclusionBuffer, ReleaseRef, (), void), asCALL_THISCALL);
    // void OcclusionBuffer::Reset() | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void Reset()", asMETHODPR(OcclusionBuffer, Reset, (), void), asCALL_THISCALL);
    // void OcclusionBuffer::ResetUseTimer() | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void ResetUseTimer()", asMETHODPR(OcclusionBuffer, ResetUseTimer, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SendEvent(StringHash)", asMETHODPR(OcclusionBuffer, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(OcclusionBuffer, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SetBlockEvents(bool)", asMETHODPR(OcclusionBuffer, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void OcclusionBuffer::SetCullMode(CullMode mode) | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SetCullMode(CullMode)", asMETHODPR(OcclusionBuffer, SetCullMode, (CullMode), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(OcclusionBuffer, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(OcclusionBuffer, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void OcclusionBuffer::SetMaxTriangles(unsigned triangles) | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SetMaxTriangles(uint)", asMETHODPR(OcclusionBuffer, SetMaxTriangles, (unsigned), void), asCALL_THISCALL);
    // bool OcclusionBuffer::SetSize(int width, int height, bool threaded) | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "bool SetSize(int, int, bool)", asMETHODPR(OcclusionBuffer, SetSize, (int, int, bool), bool), asCALL_THISCALL);
    // void OcclusionBuffer::SetView(Camera* camera) | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void SetView(Camera@+)", asMETHODPR(OcclusionBuffer, SetView, (Camera*), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void UnsubscribeFromAllEvents()", asMETHODPR(OcclusionBuffer, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(OcclusionBuffer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(OcclusionBuffer, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(OcclusionBuffer, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OcclusionBuffer", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(OcclusionBuffer, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("OcclusionBuffer", "int WeakRefs() const", asMETHODPR(OcclusionBuffer, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("OcclusionBuffer", "int get_weakRefs() const", asMETHODPR(OcclusionBuffer, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Octree", "void AddDrawable(Drawable@+)", asMETHODPR(Octree, AddDrawable, (Drawable*), void), asCALL_THISCALL);
    // void Octree::AddManualDrawable(Drawable* drawable) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void AddManualDrawable(Drawable@+)", asMETHODPR(Octree, AddManualDrawable, (Drawable*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Octree", asBEHAVE_ADDREF, "void f()", asMETHODPR(Octree, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void AllocateNetworkState()", asMETHODPR(Octree, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void ApplyAttributes()", asMETHODPR(Octree, ApplyAttributes, (), void), asCALL_THISCALL);
    // void Octree::CancelUpdate(Drawable* drawable) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void CancelUpdate(Drawable@+)", asMETHODPR(Octree, CancelUpdate, (Drawable*), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Octant::CheckDrawableFit(const BoundingBox& box) const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "bool CheckDrawableFit(const BoundingBox&in) const", asMETHODPR(Octree, CheckDrawableFit, (const BoundingBox&) const, bool), asCALL_THISCALL);
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Octant::DeleteChild(unsigned index) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void DeleteChild(uint)", asMETHODPR(Octree, DeleteChild, (unsigned), void), asCALL_THISCALL);
    // void Octree::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Octree, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // void Octree::DrawDebugGeometry(bool depthTest) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void DrawDebugGeometry(bool)", asMETHODPR(Octree, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "bool GetAnimationEnabled() const", asMETHODPR(Octree, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "bool get_animationEnabled() const", asMETHODPR(Octree, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "Variant GetAttribute(uint) const", asMETHODPR(Octree, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "Variant get_attributes(uint) const", asMETHODPR(Octree, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "Variant GetAttribute(const String&in) const", asMETHODPR(Octree, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Octree, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Octree, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Octree, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Octree, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "Variant GetAttributeDefault(uint) const", asMETHODPR(Octree, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "Variant get_attributeDefaults(uint) const", asMETHODPR(Octree, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Octree, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "bool GetBlockEvents() const", asMETHODPR(Octree, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "const String& GetCategory() const", asMETHODPR(Octree, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "const String& get_category() const", asMETHODPR(Octree, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "Component@+ GetComponent(StringHash) const", asMETHODPR(Octree, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // const BoundingBox& Octant::GetCullingBox() const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "const BoundingBox& GetCullingBox() const", asMETHODPR(Octree, GetCullingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // void Octree::GetDrawables(OctreeQuery& query) const | File: ../Graphics/Octree.h
    // Not registered because have @nobind mark
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "VariantMap& GetEventDataMap() const", asMETHODPR(Octree, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "Object@+ GetEventSender() const", asMETHODPR(Octree, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Octree, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Octree, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "const VariantMap& GetGlobalVars() const", asMETHODPR(Octree, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "const VariantMap& get_globalVars() const", asMETHODPR(Octree, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "uint GetID() const", asMETHODPR(Octree, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "uint get_id() const", asMETHODPR(Octree, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Octree, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Octant::GetLevel() const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "uint GetLevel() const", asMETHODPR(Octree, GetLevel, () const, unsigned), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "Node@+ GetNode() const", asMETHODPR(Octree, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "Node@+ get_node() const", asMETHODPR(Octree, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "uint GetNumAttributes() const", asMETHODPR(Octree, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "uint get_numAttributes() const", asMETHODPR(Octree, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Octant::GetNumDrawables() const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "uint GetNumDrawables() const", asMETHODPR(Octree, GetNumDrawables, () const, unsigned), asCALL_THISCALL);
    // unsigned Octree::GetNumLevels() const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "uint GetNumLevels() const", asMETHODPR(Octree, GetNumLevels, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "uint get_numLevels() const", asMETHODPR(Octree, GetNumLevels, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "uint GetNumNetworkAttributes() const", asMETHODPR(Octree, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Octree, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Octree, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Octree, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Octant::GetOrCreateChild(unsigned index) | File: ../Graphics/Octree.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Octant* Octant::GetParent() const | File: ../Graphics/Octree.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Octree* Octant::GetRoot() const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "Octree@+ GetRoot() const", asMETHODPR(Octree, GetRoot, () const, Octree*), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "Scene@+ GetScene() const", asMETHODPR(Octree, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Octree, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "StringHash GetType() const", asMETHODPR(Octree, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "StringHash get_type() const", asMETHODPR(Octree, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "const String& GetTypeName() const", asMETHODPR(Octree, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "const String& get_typeName() const", asMETHODPR(Octree, GetTypeName, () const, const String&), asCALL_THISCALL);
    // const BoundingBox& Octant::GetWorldBoundingBox() const | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "const BoundingBox& GetWorldBoundingBox() const", asMETHODPR(Octree, GetWorldBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "const BoundingBox& get_worldBoundingBox() const", asMETHODPR(Octree, GetWorldBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "bool HasEventHandlers() const", asMETHODPR(Octree, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Octree, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Octree, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // void Octant::InsertDrawable(Drawable* drawable) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void InsertDrawable(Drawable@+)", asMETHODPR(Octree, InsertDrawable, (Drawable*), void), asCALL_THISCALL);
    // bool Octant::IsEmpty() | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "bool IsEmpty()", asMETHODPR(Octree, IsEmpty, (), bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "bool IsEnabled() const", asMETHODPR(Octree, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "bool get_enabled() const", asMETHODPR(Octree, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "bool IsEnabledEffective() const", asMETHODPR(Octree, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "bool get_enabledEffective() const", asMETHODPR(Octree, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "bool IsInstanceOf(StringHash) const", asMETHODPR(Octree, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "bool IsReplicated() const", asMETHODPR(Octree, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "bool get_replicated() const", asMETHODPR(Octree, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool IsTemporary() const", asMETHODPR(Octree, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "bool get_temporary() const", asMETHODPR(Octree, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool Load(Deserializer&)", asMETHODPR(Octree, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Octree, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "bool LoadXML(const XMLElement&in)", asMETHODPR(Octree, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "void MarkNetworkUpdate()", asMETHODPR(Octree, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // explicit Octree::Octree(Context* context) | File: ../Graphics/Octree.h
    engine->RegisterObjectBehaviour("Octree", asBEHAVE_FACTORY, "Octree@+ f()", asFUNCTION(Octree_Octree_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Octree, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Octree, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Octree, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "void OnSetEnabled()", asMETHODPR(Octree, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "void PrepareNetworkUpdate()", asMETHODPR(Octree, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void Octree::QueueUpdate(Drawable* drawable) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void QueueUpdate(Drawable@+)", asMETHODPR(Octree, QueueUpdate, (Drawable*), void), asCALL_THISCALL);
    // void Octree::Raycast(RayOctreeQuery& query) const | File: ../Graphics/Octree.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // void Octree::RaycastSingle(RayOctreeQuery& query) const | File: ../Graphics/Octree.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Octree, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Octree, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Octree", "int Refs() const", asMETHODPR(Octree, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "int get_refs() const", asMETHODPR(Octree, Refs, () const, int), asCALL_THISCALL);
    // static void Octree::RegisterObject(Context* context) | File: ../Graphics/Octree.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Octree", asBEHAVE_RELEASE, "void f()", asMETHODPR(Octree, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "void Remove()", asMETHODPR(Octree, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Octree, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Octant::RemoveDrawable(Drawable* drawable, bool resetOctant=true) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void RemoveDrawable(Drawable@+, bool = true)", asMETHODPR(Octree, RemoveDrawable, (Drawable*, bool), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void RemoveInstanceDefault()", asMETHODPR(Octree, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Octree::RemoveManualDrawable(Drawable* drawable) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void RemoveManualDrawable(Drawable@+)", asMETHODPR(Octree, RemoveManualDrawable, (Drawable*), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void RemoveObjectAnimation()", asMETHODPR(Octree, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Octant::ResetRoot() | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void ResetRoot()", asMETHODPR(Octree, ResetRoot, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void ResetToDefault()", asMETHODPR(Octree, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "bool Save(Serializer&) const", asMETHODPR(Octree, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool SaveDefaultAttributes() const", asMETHODPR(Octree, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "bool SaveJSON(JSONValue&) const", asMETHODPR(Octree, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "bool SaveXML(XMLElement&) const", asMETHODPR(Octree, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void SendEvent(StringHash)", asMETHODPR(Octree, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Octree, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetAnimationEnabled(bool)", asMETHODPR(Octree, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void set_animationEnabled(bool)", asMETHODPR(Octree, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetAnimationTime(float)", asMETHODPR(Octree, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Octree, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Octree, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Octree, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Octree, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Octree, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Octree, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Octree, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void SetBlockEvents(bool)", asMETHODPR(Octree, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Octree", "void SetEnabled(bool)", asMETHODPR(Octree, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void set_enabled(bool)", asMETHODPR(Octree, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Octree, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Octree, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void SetInstanceDefault(bool)", asMETHODPR(Octree, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Octree, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Octree, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Octree, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Octree", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Octree, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Octree::SetSize(const BoundingBox& box, unsigned numLevels) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void SetSize(const BoundingBox&in, uint)", asMETHODPR(Octree, SetSize, (const BoundingBox&, unsigned), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void SetTemporary(bool)", asMETHODPR(Octree, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "void set_temporary(bool)", asMETHODPR(Octree, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void UnsubscribeFromAllEvents()", asMETHODPR(Octree, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Octree_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Octree, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Octree, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Octree", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Octree, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Octree::Update(const FrameInfo& frame) | File: ../Graphics/Octree.h
    engine->RegisterObjectMethod("Octree", "void Update(const FrameInfo&in)", asMETHODPR(Octree, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Octree", "int WeakRefs() const", asMETHODPR(Octree, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Octree", "int get_weakRefs() const", asMETHODPR(Octree, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Octree, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Octree, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Octree", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Octree, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("OffMeshConnection", asBEHAVE_ADDREF, "void f()", asMETHODPR(OffMeshConnection, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void AllocateNetworkState()", asMETHODPR(OffMeshConnection, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void OffMeshConnection::ApplyAttributes() override | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void ApplyAttributes()", asMETHODPR(OffMeshConnection, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void OffMeshConnection::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(OffMeshConnection, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool GetAnimationEnabled() const", asMETHODPR(OffMeshConnection, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool get_animationEnabled() const", asMETHODPR(OffMeshConnection, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // unsigned OffMeshConnection::GetAreaID() const | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "uint GetAreaID() const", asMETHODPR(OffMeshConnection, GetAreaID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "uint get_areaID() const", asMETHODPR(OffMeshConnection, GetAreaID, () const, unsigned), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "Variant GetAttribute(uint) const", asMETHODPR(OffMeshConnection, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "Variant get_attributes(uint) const", asMETHODPR(OffMeshConnection, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "Variant GetAttribute(const String&in) const", asMETHODPR(OffMeshConnection, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(OffMeshConnection, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(OffMeshConnection, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(OffMeshConnection, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(OffMeshConnection, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "Variant GetAttributeDefault(uint) const", asMETHODPR(OffMeshConnection, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "Variant get_attributeDefaults(uint) const", asMETHODPR(OffMeshConnection, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(OffMeshConnection, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool GetBlockEvents() const", asMETHODPR(OffMeshConnection, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "const String& GetCategory() const", asMETHODPR(OffMeshConnection, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "const String& get_category() const", asMETHODPR(OffMeshConnection, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "Component@+ GetComponent(StringHash) const", asMETHODPR(OffMeshConnection, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T*  Component::GetComponent() const | File: ../Scene/Component.h
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
    engine->RegisterObjectMethod("OffMeshConnection", "Node@+ GetEndPoint() const", asMETHODPR(OffMeshConnection, GetEndPoint, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "Node@+ get_endPoint() const", asMETHODPR(OffMeshConnection, GetEndPoint, () const, Node*), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "VariantMap& GetEventDataMap() const", asMETHODPR(OffMeshConnection, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "Object@+ GetEventSender() const", asMETHODPR(OffMeshConnection, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(OffMeshConnection, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "const Variant& get_globalVar(StringHash) const", asMETHODPR(OffMeshConnection, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "const VariantMap& GetGlobalVars() const", asMETHODPR(OffMeshConnection, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "const VariantMap& get_globalVars() const", asMETHODPR(OffMeshConnection, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "uint GetID() const", asMETHODPR(OffMeshConnection, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "uint get_id() const", asMETHODPR(OffMeshConnection, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(OffMeshConnection, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned OffMeshConnection::GetMask() const | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "uint GetMask() const", asMETHODPR(OffMeshConnection, GetMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "uint get_mask() const", asMETHODPR(OffMeshConnection, GetMask, () const, unsigned), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "Node@+ GetNode() const", asMETHODPR(OffMeshConnection, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "Node@+ get_node() const", asMETHODPR(OffMeshConnection, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "uint GetNumAttributes() const", asMETHODPR(OffMeshConnection, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "uint get_numAttributes() const", asMETHODPR(OffMeshConnection, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "uint GetNumNetworkAttributes() const", asMETHODPR(OffMeshConnection, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(OffMeshConnection, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(OffMeshConnection, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(OffMeshConnection, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float OffMeshConnection::GetRadius() const | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "float GetRadius() const", asMETHODPR(OffMeshConnection, GetRadius, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "float get_radius() const", asMETHODPR(OffMeshConnection, GetRadius, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "Scene@+ GetScene() const", asMETHODPR(OffMeshConnection, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(OffMeshConnection, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "StringHash GetType() const", asMETHODPR(OffMeshConnection, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "StringHash get_type() const", asMETHODPR(OffMeshConnection, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "const String& GetTypeName() const", asMETHODPR(OffMeshConnection, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "const String& get_typeName() const", asMETHODPR(OffMeshConnection, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool HasEventHandlers() const", asMETHODPR(OffMeshConnection, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(OffMeshConnection, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(OffMeshConnection, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool OffMeshConnection::IsBidirectional() const | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool IsBidirectional() const", asMETHODPR(OffMeshConnection, IsBidirectional, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool get_bidirectional() const", asMETHODPR(OffMeshConnection, IsBidirectional, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool IsEnabled() const", asMETHODPR(OffMeshConnection, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool get_enabled() const", asMETHODPR(OffMeshConnection, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool IsEnabledEffective() const", asMETHODPR(OffMeshConnection, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool get_enabledEffective() const", asMETHODPR(OffMeshConnection, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool IsInstanceOf(StringHash) const", asMETHODPR(OffMeshConnection, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool IsReplicated() const", asMETHODPR(OffMeshConnection, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool get_replicated() const", asMETHODPR(OffMeshConnection, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool IsTemporary() const", asMETHODPR(OffMeshConnection, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool get_temporary() const", asMETHODPR(OffMeshConnection, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool Load(Deserializer&)", asMETHODPR(OffMeshConnection, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool LoadJSON(const JSONValue&in)", asMETHODPR(OffMeshConnection, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool LoadXML(const XMLElement&in)", asMETHODPR(OffMeshConnection, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "void MarkNetworkUpdate()", asMETHODPR(OffMeshConnection, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // explicit OffMeshConnection::OffMeshConnection(Context* context) | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectBehaviour("OffMeshConnection", asBEHAVE_FACTORY, "OffMeshConnection@+ f()", asFUNCTION(OffMeshConnection_OffMeshConnection_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(OffMeshConnection, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(OffMeshConnection, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(OffMeshConnection, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "void OnSetEnabled()", asMETHODPR(OffMeshConnection, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "void PrepareNetworkUpdate()", asMETHODPR(OffMeshConnection, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(OffMeshConnection, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(OffMeshConnection, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("OffMeshConnection", "int Refs() const", asMETHODPR(OffMeshConnection, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "int get_refs() const", asMETHODPR(OffMeshConnection, Refs, () const, int), asCALL_THISCALL);
    // static void OffMeshConnection::RegisterObject(Context* context) | File: ../Navigation/OffMeshConnection.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("OffMeshConnection", asBEHAVE_RELEASE, "void f()", asMETHODPR(OffMeshConnection, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "void Remove()", asMETHODPR(OffMeshConnection, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(OffMeshConnection, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void RemoveInstanceDefault()", asMETHODPR(OffMeshConnection, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void RemoveObjectAnimation()", asMETHODPR(OffMeshConnection, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void ResetToDefault()", asMETHODPR(OffMeshConnection, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool Save(Serializer&) const", asMETHODPR(OffMeshConnection, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool SaveDefaultAttributes() const", asMETHODPR(OffMeshConnection, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool SaveJSON(JSONValue&) const", asMETHODPR(OffMeshConnection, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool SaveXML(XMLElement&) const", asMETHODPR(OffMeshConnection, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SendEvent(StringHash)", asMETHODPR(OffMeshConnection, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(OffMeshConnection, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAnimationEnabled(bool)", asMETHODPR(OffMeshConnection, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_animationEnabled(bool)", asMETHODPR(OffMeshConnection, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAnimationTime(float)", asMETHODPR(OffMeshConnection, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void OffMeshConnection::SetAreaID(unsigned newAreaID) | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAreaID(uint)", asMETHODPR(OffMeshConnection, SetAreaID, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_areaID(uint)", asMETHODPR(OffMeshConnection, SetAreaID, (unsigned), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(OffMeshConnection, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool set_attributes(uint, const Variant&in)", asMETHODPR(OffMeshConnection, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(OffMeshConnection, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(OffMeshConnection, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(OffMeshConnection, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(OffMeshConnection, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(OffMeshConnection, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void OffMeshConnection::SetBidirectional(bool enabled) | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetBidirectional(bool)", asMETHODPR(OffMeshConnection, SetBidirectional, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_bidirectional(bool)", asMETHODPR(OffMeshConnection, SetBidirectional, (bool), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetBlockEvents(bool)", asMETHODPR(OffMeshConnection, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetEnabled(bool)", asMETHODPR(OffMeshConnection, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_enabled(bool)", asMETHODPR(OffMeshConnection, SetEnabled, (bool), void), asCALL_THISCALL);
    // void OffMeshConnection::SetEndPoint(Node* node) | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetEndPoint(Node@+)", asMETHODPR(OffMeshConnection, SetEndPoint, (Node*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_endPoint(Node@+)", asMETHODPR(OffMeshConnection, SetEndPoint, (Node*), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(OffMeshConnection, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(OffMeshConnection, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetInstanceDefault(bool)", asMETHODPR(OffMeshConnection, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(OffMeshConnection, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void OffMeshConnection::SetMask(unsigned newMask) | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetMask(uint)", asMETHODPR(OffMeshConnection, SetMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_mask(uint)", asMETHODPR(OffMeshConnection, SetMask, (unsigned), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(OffMeshConnection, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(OffMeshConnection, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(OffMeshConnection, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void OffMeshConnection::SetRadius(float radius) | File: ../Navigation/OffMeshConnection.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetRadius(float)", asMETHODPR(OffMeshConnection, SetRadius, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_radius(float)", asMETHODPR(OffMeshConnection, SetRadius, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void SetTemporary(bool)", asMETHODPR(OffMeshConnection, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_temporary(bool)", asMETHODPR(OffMeshConnection, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void UnsubscribeFromAllEvents()", asMETHODPR(OffMeshConnection, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(OffMeshConnection_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(OffMeshConnection, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(OffMeshConnection, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("OffMeshConnection", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(OffMeshConnection, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("OffMeshConnection", "int WeakRefs() const", asMETHODPR(OffMeshConnection, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "int get_weakRefs() const", asMETHODPR(OffMeshConnection, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(OffMeshConnection, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(OffMeshConnection, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("OffMeshConnection", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(OffMeshConnection, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("OggVorbisSoundStream", asBEHAVE_ADDREF, "void f()", asMETHODPR(OggVorbisSoundStream, AddRef, (), void), asCALL_THISCALL);
    // unsigned OggVorbisSoundStream::GetData(signed char* dest, unsigned numBytes) override | File: ../Audio/OggVorbisSoundStream.h
    // Error: type "signed char*" can not automatically bind
    // float SoundStream::GetFrequency() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "float GetFrequency() const", asMETHODPR(OggVorbisSoundStream, GetFrequency, () const, float), asCALL_THISCALL);
    // unsigned SoundStream::GetIntFrequency() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "uint GetIntFrequency() const", asMETHODPR(OggVorbisSoundStream, GetIntFrequency, () const, unsigned), asCALL_THISCALL);
    // unsigned SoundStream::GetSampleSize() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "uint GetSampleSize() const", asMETHODPR(OggVorbisSoundStream, GetSampleSize, () const, unsigned), asCALL_THISCALL);
    // bool SoundStream::GetStopAtEnd() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "bool GetStopAtEnd() const", asMETHODPR(OggVorbisSoundStream, GetStopAtEnd, () const, bool), asCALL_THISCALL);
    // bool SoundStream::IsSixteenBit() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "bool IsSixteenBit() const", asMETHODPR(OggVorbisSoundStream, IsSixteenBit, () const, bool), asCALL_THISCALL);
    // bool SoundStream::IsStereo() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "bool IsStereo() const", asMETHODPR(OggVorbisSoundStream, IsStereo, () const, bool), asCALL_THISCALL);
    // explicit OggVorbisSoundStream::OggVorbisSoundStream(const Sound* sound) | File: ../Audio/OggVorbisSoundStream.h
    engine->RegisterObjectBehaviour("OggVorbisSoundStream", asBEHAVE_FACTORY, "OggVorbisSoundStream@+ f(Sound@+)", asFUNCTION(OggVorbisSoundStream_OggVorbisSoundStream_Sound), asCALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "int Refs() const", asMETHODPR(OggVorbisSoundStream, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("OggVorbisSoundStream", "int get_refs() const", asMETHODPR(OggVorbisSoundStream, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("OggVorbisSoundStream", asBEHAVE_RELEASE, "void f()", asMETHODPR(OggVorbisSoundStream, ReleaseRef, (), void), asCALL_THISCALL);
    // bool OggVorbisSoundStream::Seek(unsigned sample_number) override | File: ../Audio/OggVorbisSoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "bool Seek(uint)", asMETHODPR(OggVorbisSoundStream, Seek, (unsigned), bool), asCALL_THISCALL);
    // void SoundStream::SetFormat(unsigned frequency, bool sixteenBit, bool stereo) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "void SetFormat(uint, bool, bool)", asMETHODPR(OggVorbisSoundStream, SetFormat, (unsigned, bool, bool), void), asCALL_THISCALL);
    // void SoundStream::SetStopAtEnd(bool enable) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "void SetStopAtEnd(bool)", asMETHODPR(OggVorbisSoundStream, SetStopAtEnd, (bool), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("OggVorbisSoundStream", "int WeakRefs() const", asMETHODPR(OggVorbisSoundStream, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("OggVorbisSoundStream", "int get_weakRefs() const", asMETHODPR(OggVorbisSoundStream, WeakRefs, () const, int), asCALL_THISCALL);
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
