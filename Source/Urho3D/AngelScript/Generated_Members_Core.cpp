// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

// struct AttributeHandle | File: ../Core/Attribute.h
void CollectMembers_AttributeHandle(MemberCollection& members)
{
    // AttributeHandle& AttributeHandle::SetMetadata(StringHash key, const Variant& value)
    // Error: type "AttributeHandle" can not automatically bind bacause have @nobind mark

}

// struct AttributeInfo | File: ../Core/Attribute.h
void CollectMembers_AttributeInfo(MemberCollection& members)
{
    // template <class T> T AttributeInfo::GetMetadata(const StringHash& key) const
    // Not registered because template

    // const char** AttributeInfo::enumNames_
    // Error: type "const char**" can not automatically bind
    // SharedPtr<AttributeAccessor> AttributeInfo::accessor_
    // Error: type "SharedPtr<AttributeAccessor>" can not automatically bind
    // void* AttributeInfo::ptr_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("VariantType AttributeInfo::type_", "VariantType type", offsetof(AttributeInfo, type_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String AttributeInfo::name_", "String name", offsetof(AttributeInfo, name_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Variant AttributeInfo::defaultValue_", "Variant defaultValue", offsetof(AttributeInfo, defaultValue_)));
    members.fields_.Push(RegisterObjectPropertyArgs("AttributeModeFlags AttributeInfo::mode_", "AttributeModeFlags mode", offsetof(AttributeInfo, mode_)));
    members.fields_.Push(RegisterObjectPropertyArgs("VariantMap AttributeInfo::metadata_", "VariantMap metadata", offsetof(AttributeInfo, metadata_)));

}

// class AutoProfileBlock | File: ../Core/Profiler.h
void CollectMembers_AutoProfileBlock(MemberCollection& members)
{
}

// class Condition | File: ../Core/Condition.h
void CollectMembers_Condition(MemberCollection& members)
{
}

// class CustomVariantValue | File: ../Core/Variant.h
void CollectMembers_CustomVariantValue(MemberCollection& members)
{
    // virtual bool CustomVariantValue::Assign(const CustomVariantValue& rhs)
    // Error: type "CustomVariantValue" can not automatically bind bacause have @nobind mark
    // virtual CustomVariantValue* CustomVariantValue::Clone() const
    // Error: type "CustomVariantValue" can not automatically bind bacause have @nobind mark
    // virtual void CustomVariantValue::Clone(void* dest) const
    // Error: type "void*" can not automatically bind
    // virtual bool CustomVariantValue::Compare(const CustomVariantValue& rhs) const
    // Error: type "CustomVariantValue" can not automatically bind bacause have @nobind mark
    // const std::type_info& CustomVariantValue::GetTypeInfo() const
    // Error: type "const std::type_info&" can not automatically bind

    // template <class T> T* CustomVariantValue::GetValuePtr()
    // Not registered because template
    // template <class T> const T* CustomVariantValue::GetValuePtr() const
    // Not registered because template
    // template <class T> bool CustomVariantValue::IsType() const
    // Not registered because template

}

// class HiresTimer | File: ../Core/Timer.h
void CollectMembers_HiresTimer(MemberCollection& members)
{
}

// class Mutex | File: ../Core/Mutex.h
void CollectMembers_Mutex(MemberCollection& members)
{
}

// class MutexLock | File: ../Core/Mutex.h
void CollectMembers_MutexLock(MemberCollection& members)
{
    // MutexLock& MutexLock::operator =(const MutexLock& rhs) = delete
    // Not registered because deleted

}

// class ProfilerBlock | File: ../Core/Profiler.h
void CollectMembers_ProfilerBlock(MemberCollection& members)
{
    // ProfilerBlock* ProfilerBlock::GetChild(const char* name)
    // Error: type "const char*" can not automatically bind

    // char* ProfilerBlock::name_
    // Not registered because pointer
    // ProfilerBlock* ProfilerBlock::parent_
    // Not registered because pointer
    // PODVector<ProfilerBlock*> ProfilerBlock::children_
    // Error: type "PODVector<ProfilerBlock*>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("HiresTimer ProfilerBlock::timer_", "HiresTimer timer", offsetof(ProfilerBlock, timer_)));
    members.fields_.Push(RegisterObjectPropertyArgs("long long ProfilerBlock::time_", "int64 time", offsetof(ProfilerBlock, time_)));
    members.fields_.Push(RegisterObjectPropertyArgs("long long ProfilerBlock::maxTime_", "int64 maxTime", offsetof(ProfilerBlock, maxTime_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ProfilerBlock::count_", "uint count", offsetof(ProfilerBlock, count_)));
    members.fields_.Push(RegisterObjectPropertyArgs("long long ProfilerBlock::frameTime_", "int64 frameTime", offsetof(ProfilerBlock, frameTime_)));
    members.fields_.Push(RegisterObjectPropertyArgs("long long ProfilerBlock::frameMaxTime_", "int64 frameMaxTime", offsetof(ProfilerBlock, frameMaxTime_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ProfilerBlock::frameCount_", "uint frameCount", offsetof(ProfilerBlock, frameCount_)));
    members.fields_.Push(RegisterObjectPropertyArgs("long long ProfilerBlock::intervalTime_", "int64 intervalTime", offsetof(ProfilerBlock, intervalTime_)));
    members.fields_.Push(RegisterObjectPropertyArgs("long long ProfilerBlock::intervalMaxTime_", "int64 intervalMaxTime", offsetof(ProfilerBlock, intervalMaxTime_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ProfilerBlock::intervalCount_", "uint intervalCount", offsetof(ProfilerBlock, intervalCount_)));
    members.fields_.Push(RegisterObjectPropertyArgs("long long ProfilerBlock::totalTime_", "int64 totalTime", offsetof(ProfilerBlock, totalTime_)));
    members.fields_.Push(RegisterObjectPropertyArgs("long long ProfilerBlock::totalMaxTime_", "int64 totalMaxTime", offsetof(ProfilerBlock, totalMaxTime_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned ProfilerBlock::totalCount_", "uint totalCount", offsetof(ProfilerBlock, totalCount_)));

}

// struct ResourceRef | File: ../Core/Variant.h
void CollectMembers_ResourceRef(MemberCollection& members)
{
    // bool ResourceRef::operator !=(const ResourceRef& rhs) const
    // Only operator == is needed

    members.fields_.Push(RegisterObjectPropertyArgs("StringHash ResourceRef::type_", "StringHash type", offsetof(ResourceRef, type_)));
    members.fields_.Push(RegisterObjectPropertyArgs("String ResourceRef::name_", "String name", offsetof(ResourceRef, name_)));

}

// struct ResourceRefList | File: ../Core/Variant.h
void CollectMembers_ResourceRefList(MemberCollection& members)
{
    // bool ResourceRefList::operator !=(const ResourceRefList& rhs) const
    // Only operator == is needed

    // StringVector ResourceRefList::names_
    // Error: type "StringVector" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("StringHash ResourceRefList::type_", "StringHash type", offsetof(ResourceRefList, type_)));

}

// class Spline | File: ../Core/Spline.h
void CollectMembers_Spline(MemberCollection& members)
{
    // const VariantVector& Spline::GetKnots() const
    // Error: type "const VariantVector&" can not automatically bind
    // void Spline::SetKnots(const Vector<Variant>& knots)
    // Error: type "const Vector<Variant>&" can not automatically bind
    // bool Spline::operator !=(const Spline& rhs) const
    // Only operator == is needed

}

// class StringHashRegister | File: ../Core/StringHashRegister.h
void CollectMembers_StringHashRegister(MemberCollection& members)
{
    // const StringMap& StringHashRegister::GetInternalMap() const
    // Error: type "const StringMap&" can not automatically bind
    // StringHash StringHashRegister::RegisterString(const StringHash& hash, const char* string)
    // Error: type "const char*" can not automatically bind
    // StringHash StringHashRegister::RegisterString(const char* string)
    // Error: type "const char*" can not automatically bind

}

// class Thread | File: ../Core/Thread.h
void CollectMembers_Thread(MemberCollection& members)
{
    // static ThreadID Thread::GetCurrentThreadID()
    // Not registered because have @nobind mark

}

// class Timer | File: ../Core/Timer.h
void CollectMembers_Timer(MemberCollection& members)
{
}

// class TypeInfo | File: ../Core/Object.h
void CollectMembers_TypeInfo(MemberCollection& members)
{
    // const TypeInfo* TypeInfo::GetBaseTypeInfo() const
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // bool TypeInfo::IsTypeOf(const TypeInfo* typeInfo) const
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark

    // template <typename T> bool TypeInfo::IsTypeOf() const
    // Not registered because template

}

// class Variant | File: ../Core/Variant.h
void CollectMembers_Variant(MemberCollection& members)
{
    // void Variant::FromString(VariantType type, const char* value)
    // Error: type "const char*" can not automatically bind
    // void Variant::FromString(const char* type, const char* value)
    // Error: type "const char*" can not automatically bind
    // const PODVector<unsigned char>& Variant::GetBuffer() const
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // PODVector<unsigned char>* Variant::GetBufferPtr()
    // Error: type "PODVector<unsigned char>*" can not automatically bind
    // CustomVariantValue* Variant::GetCustomVariantValuePtr()
    // Error: type "CustomVariantValue" can not automatically bind bacause have @nobind mark
    // const CustomVariantValue* Variant::GetCustomVariantValuePtr() const
    // Error: type "CustomVariantValue" can not automatically bind bacause have @nobind mark
    // StringVector* Variant::GetStringVectorPtr()
    // Error: type "StringVector*" can not automatically bind
    // VariantMap* Variant::GetVariantMapPtr()
    // Error: type "VariantMap*" can not automatically bind
    // const VariantVector& Variant::GetVariantVector() const
    // Error: type "const VariantVector&" can not automatically bind
    // VariantVector* Variant::GetVariantVectorPtr()
    // Error: type "VariantVector*" can not automatically bind
    // void* Variant::GetVoidPtr() const
    // Error: type "void*" can not automatically bind
    // void Variant::SetBuffer(const void* data, unsigned size)
    // Error: type "const void*" can not automatically bind
    // void Variant::SetCustomVariantValue(const CustomVariantValue& value)
    // Error: type "CustomVariantValue" can not automatically bind bacause have @nobind mark
    // bool Variant::operator !=(RefCounted* rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(bool rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const IntRect& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const IntVector2& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const IntVector3& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const Matrix3& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const Matrix3x4& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const Matrix4& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const PODVector<unsigned char>& rhs) const
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Variant::operator !=(const Quaternion& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const Rect& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const ResourceRef& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const ResourceRefList& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const String& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const StringHash& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const StringVector& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const Variant& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const VariantMap& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const VariantVector& rhs) const
    // Error: type "const VariantVector&" can not automatically bind
    // bool Variant::operator !=(const Vector2& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const Vector3& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const Vector4& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(const VectorBuffer& rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(double rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(float rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(int rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(long long rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(unsigned long long rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(unsigned rhs) const
    // Only operator == is needed
    // bool Variant::operator !=(void* rhs) const
    // Error: type "void*" can not automatically bind
    // Variant& Variant::operator =(const PODVector<unsigned char>& rhs)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // Variant& Variant::operator =(const VariantVector& rhs)
    // Error: type "const VariantVector&" can not automatically bind
    // Variant& Variant::operator =(const char* rhs)
    // Error: type "const char*" can not automatically bind
    // Variant& Variant::operator =(void* rhs)
    // Error: type "void*" can not automatically bind
    // bool Variant::operator ==(const PODVector<unsigned char>& rhs) const
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Variant::operator ==(const VariantVector& rhs) const
    // Error: type "const VariantVector&" can not automatically bind
    // bool Variant::operator ==(void* rhs) const
    // Error: type "void*" can not automatically bind

    // template <class T> T Variant::Get() const
    // Not registered because template
    // template <> int Variant::Get() const
    // Not registered because template
    // template <> unsigned Variant::Get() const
    // Not registered because template
    // template <> long long Variant::Get() const
    // Not registered because template
    // template <> unsigned long long Variant::Get() const
    // Not registered because template
    // template <> StringHash Variant::Get() const
    // Not registered because template
    // template <> bool Variant::Get() const
    // Not registered because template
    // template <> float Variant::Get() const
    // Not registered because template
    // template <> double Variant::Get() const
    // Not registered because template
    // template <> const Vector2& Variant::Get() const
    // Not registered because template
    // template <> const Vector3& Variant::Get() const
    // Not registered because template
    // template <> const Vector4& Variant::Get() const
    // Not registered because template
    // template <> const Quaternion& Variant::Get() const
    // Not registered because template
    // template <> const Color& Variant::Get() const
    // Not registered because template
    // template <> const String& Variant::Get() const
    // Not registered because template
    // template <> const Rect& Variant::Get() const
    // Not registered because template
    // template <> const IntRect& Variant::Get() const
    // Not registered because template
    // template <> const IntVector2& Variant::Get() const
    // Not registered because template
    // template <> const IntVector3& Variant::Get() const
    // Not registered because template
    // template <> const PODVector<unsigned char>& Variant::Get() const
    // Not registered because template
    // template <> void* Variant::Get() const
    // Not registered because template
    // template <> RefCounted* Variant::Get() const
    // Not registered because template
    // template <> const Matrix3& Variant::Get() const
    // Not registered because template
    // template <> const Matrix3x4& Variant::Get() const
    // Not registered because template
    // template <> const Matrix4& Variant::Get() const
    // Not registered because template
    // template <> ResourceRef Variant::Get() const
    // Not registered because template
    // template <> ResourceRefList Variant::Get() const
    // Not registered because template
    // template <> VariantVector Variant::Get() const
    // Not registered because template
    // template <> StringVector Variant::Get() const
    // Not registered because template
    // template <> VariantMap Variant::Get() const
    // Not registered because template
    // template <> Vector2 Variant::Get() const
    // Not registered because template
    // template <> Vector3 Variant::Get() const
    // Not registered because template
    // template <> Vector4 Variant::Get() const
    // Not registered because template
    // template <> Quaternion Variant::Get() const
    // Not registered because template
    // template <> Color Variant::Get() const
    // Not registered because template
    // template <> String Variant::Get() const
    // Not registered because template
    // template <> Rect Variant::Get() const
    // Not registered because template
    // template <> IntRect Variant::Get() const
    // Not registered because template
    // template <> IntVector2 Variant::Get() const
    // Not registered because template
    // template <> IntVector3 Variant::Get() const
    // Not registered because template
    // template <> PODVector<unsigned char> Variant::Get() const
    // Not registered because template
    // template <> Matrix3 Variant::Get() const
    // Not registered because template
    // template <> Matrix3x4 Variant::Get() const
    // Not registered because template
    // template <> Matrix4 Variant::Get() const
    // Not registered because template
    // template <class T> T Variant::GetCustom() const
    // Not registered because template
    // template <class T> T* Variant::GetCustomPtr()
    // Not registered because template
    // template <class T> bool Variant::IsCustomType() const
    // Not registered because template
    // template <class T> Variant& Variant::operator =(const CustomVariantValueImpl<T>& value)
    // Not registered because template
    // template <class T> void Variant::SetCustom(const T& value)
    // Not registered because template
    // static VariantType Variant::GetTypeFromName(const char* typeName)
    // Error: type "const char*" can not automatically bind

    // static const PODVector<unsigned char> Variant::emptyBuffer
    // Error: type "const PODVector<unsigned char>" can not automatically bind
    // static const VariantVector Variant::emptyVariantVector
    // Error: type "const VariantVector" can not automatically bind
    // static const StringVector Variant::emptyStringVector
    // Error: type "const StringVector" can not automatically bind

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const Variant Variant::EMPTY", "const Variant EMPTY", (void*)&Variant::EMPTY));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const ResourceRef Variant::emptyResourceRef", "const ResourceRef emptyResourceRef", (void*)&Variant::emptyResourceRef));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const ResourceRefList Variant::emptyResourceRefList", "const ResourceRefList emptyResourceRefList", (void*)&Variant::emptyResourceRefList));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const VariantMap Variant::emptyVariantMap", "const VariantMap emptyVariantMap", (void*)&Variant::emptyVariantMap));

}

// class AttributeAccessor | File: ../Core/Attribute.h
void CollectMembers_AttributeAccessor(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

}

// class Context | File: ../Core/Context.h
void CollectMembers_Context(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

    // const HashMap<StringHash, Vector<AttributeInfo>>& Context::GetAllAttributes() const
    // Error: type "const HashMap<StringHash, Vector<AttributeInfo>>&" can not automatically bind
    // AttributeInfo* Context::GetAttribute(StringHash objectType, const char* name)
    // Error: type "const char*" can not automatically bind
    // const Vector<AttributeInfo>* Context::GetAttributes(StringHash type) const
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // EventHandler* Context::GetEventHandler() const
    // Error: type "EventHandler" can not bind bacause abstract value
    // const Vector<AttributeInfo>* Context::GetNetworkAttributes(StringHash type) const
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const HashMap<String, Vector<StringHash>>& Context::GetObjectCategories() const
    // Error: type "const HashMap<String, Vector<StringHash>>&" can not automatically bind
    // const HashMap<StringHash, SharedPtr<ObjectFactory>>& Context::GetObjectFactories() const
    // Error: type "const HashMap<StringHash, SharedPtr<ObjectFactory>>&" can not automatically bind
    // const HashMap<StringHash, SharedPtr<Object>>& Context::GetSubsystems() const
    // Error: type "const HashMap<StringHash, SharedPtr<Object>>&" can not automatically bind
    // AttributeHandle Context::RegisterAttribute(StringHash objectType, const AttributeInfo& attr)
    // Error: type "AttributeHandle" can not automatically bind bacause have @nobind mark
    // void Context::RegisterFactory(ObjectFactory* factory, const char* category)
    // Error: type "const char*" can not automatically bind
    // void Context::RemoveAttribute(StringHash objectType, const char* name)
    // Error: type "const char*" can not automatically bind
    // void Context::UpdateAttributeDefaultValue(StringHash objectType, const char* name, const Variant& defaultValue)
    // Error: type "const char*" can not automatically bind

    // template <class T, class U> void Context::CopyBaseAttributes()
    // Not registered because template
    // template <class T> SharedPtr<T> Context::CreateObject()
    // Not registered because template
    // template <class T> AttributeInfo* Context::GetAttribute(const char* name)
    // Not registered because template
    // template <class T> T* Context::GetSubsystem() const
    // Not registered because template
    // template <class T> AttributeHandle Context::RegisterAttribute(const AttributeInfo& attr)
    // Not registered because template
    // template <class T> void Context::RegisterFactory()
    // Not registered because template
    // template <class T> void Context::RegisterFactory(const char* category)
    // Not registered because template
    // template <class T> T* Context::RegisterSubsystem()
    // Not registered because template
    // template <class T> void Context::RemoveAllAttributes()
    // Not registered because template
    // template <class T> void Context::RemoveAttribute(const char* name)
    // Not registered because template
    // template <class T> void Context::RemoveSubsystem()
    // Not registered because template
    // template <class T> void Context::UpdateAttributeDefaultValue(const char* name, const Variant& defaultValue)
    // Not registered because template

}

// class EventHandler | File: ../Core/Object.h
void CollectMembers_EventHandler(MemberCollection& members)
{
    CollectMembers_LinkedListNode(members);

    // virtual EventHandler* EventHandler::Clone() const = 0
    // Error: type "EventHandler" can not bind bacause abstract value
    // void* EventHandler::GetUserData() const
    // Error: type "void*" can not automatically bind

}

// class EventProfilerBlock | File: ../Core/EventProfiler.h
void CollectMembers_EventProfilerBlock(MemberCollection& members)
{
    CollectMembers_ProfilerBlock(members);

    Remove(members.methods_, "ProfilerBlock* ProfilerBlock::GetChild(const char* name)");

    // EventProfilerBlock* EventProfilerBlock::GetChild(StringHash eventID)
    // Error: type "EventProfilerBlock" can not automatically bind bacause have @nobind mark

    members.fields_.Push(RegisterObjectPropertyArgs("StringHash EventProfilerBlock::eventID_", "StringHash eventID", offsetof(EventProfilerBlock, eventID_)));

}

// class EventReceiverGroup | File: ../Core/Context.h
void CollectMembers_EventReceiverGroup(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

    // PODVector<Object*> EventReceiverGroup::receivers_
    // Error: type "PODVector<Object*>" can not automatically bind

}

// class Object | File: ../Core/Object.h
void CollectMembers_Object(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

    // Context* Object::GetContext() const
    // Error: type "Context*" can used only as function parameter
    // EventHandler* Object::GetEventHandler() const
    // Error: type "EventHandler" can not bind bacause abstract value
    // virtual const TypeInfo* Object::GetTypeInfo() const = 0
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler)
    // Error: type "EventHandler" can not bind bacause abstract value
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData = nullptr)
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler)
    // Error: type "EventHandler" can not bind bacause abstract value
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData = nullptr)
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind

    // template <typename T> T* Object::Cast()
    // Not registered because template
    // template <typename T> const T* Object::Cast() const
    // Not registered because template
    // template <class T> T* Object::GetSubsystem() const
    // Not registered because template
    // template <typename T> bool Object::IsInstanceOf() const
    // Not registered because template
    // template <typename... Args> void Object::SendEvent(StringHash eventType, Args... args)
    // Not registered because template
    // static const TypeInfo* Object::GetTypeInfoStatic()
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark

}

// class ObjectFactory | File: ../Core/Object.h
void CollectMembers_ObjectFactory(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

    // Context* ObjectFactory::GetContext() const
    // Error: type "Context*" can used only as function parameter
    // const TypeInfo* ObjectFactory::GetTypeInfo() const
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark

}

// struct WorkItem | File: ../Core/WorkQueue.h
void CollectMembers_WorkItem(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

    // void(* WorkItem::workFunction_) (const WorkItem* , unsigned)
    // Not registered because pointer
    // void* WorkItem::start_
    // Not registered because pointer
    // void* WorkItem::end_
    // Not registered because pointer
    // void* WorkItem::aux_
    // Not registered because pointer
    // std::atomic<bool> WorkItem::completed_
    // Error: type "std::atomic<bool>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned WorkItem::priority_", "uint priority", offsetof(WorkItem, priority_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool WorkItem::sendEvent_", "bool sendEvent", offsetof(WorkItem, sendEvent_)));

}

// class EventHandler11Impl | File: ../Core/Object.h
void CollectMembers_EventHandler11Impl(MemberCollection& members)
{
    CollectMembers_EventHandler(members);

    Remove(members.methods_, "virtual EventHandler* EventHandler::Clone() const = 0");
    Remove(members.methods_, "virtual void EventHandler::Invoke(VariantMap& eventData) = 0");

}

// class Profiler | File: ../Core/Profiler.h
void CollectMembers_Profiler(MemberCollection& members)
{
    CollectMembers_Object(members);

    // void Profiler::BeginBlock(const char* name)
    // Error: type "const char*" can not automatically bind
    // const ProfilerBlock* Profiler::GetCurrentBlock()
    // Error: type "ProfilerBlock" can not automatically bind bacause have @nobind mark
    // const ProfilerBlock* Profiler::GetRootBlock()
    // Error: type "ProfilerBlock" can not automatically bind bacause have @nobind mark

}

// class Time | File: ../Core/Timer.h
void CollectMembers_Time(MemberCollection& members)
{
    CollectMembers_Object(members);

}

// class WorkQueue | File: ../Core/WorkQueue.h
void CollectMembers_WorkQueue(MemberCollection& members)
{
    CollectMembers_Object(members);

    // void WorkQueue::AddWorkItem(const SharedPtr<WorkItem>& item)
    // Error: type "const SharedPtr<WorkItem>&" can not automatically bind
    // SharedPtr<WorkItem> WorkQueue::GetFreeItem()
    // Error: type "SharedPtr<WorkItem>" can not automatically bind
    // bool WorkQueue::RemoveWorkItem(SharedPtr<WorkItem> item)
    // Error: type "SharedPtr<WorkItem>" can not automatically bind
    // unsigned WorkQueue::RemoveWorkItems(const Vector<SharedPtr<WorkItem>>& items)
    // Error: type "const Vector<SharedPtr<WorkItem>>&" can not automatically bind

}

// class EventProfiler | File: ../Core/EventProfiler.h
void CollectMembers_EventProfiler(MemberCollection& members)
{
    CollectMembers_Profiler(members);

    Remove(members.methods_, "void Profiler::BeginBlock(const char* name)");

}

} // namespace Urho3D
