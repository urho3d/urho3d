// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// explicit GPUObject::GPUObject(Graphics* graphics) | File: ../Graphics/GPUObject.h
static void GPUObject_GPUObject_Graphics(GPUObject* ptr, Graphics *graphics)
{
    new(ptr) GPUObject(graphics);
}

// explicit Geometry::Geometry(Context* context) | File: ../Graphics/Geometry.h
static Geometry* Geometry_Geometry_Context()
{
    return new Geometry(GetScriptContext());
}

// const Vector<SharedPtr<VertexBuffer>>& Geometry::GetVertexBuffers() const | File: ../Graphics/Geometry.h
static CScriptArray* Geometry_GetVertexBuffers_void(Geometry* ptr)
{
    const Vector<SharedPtr<VertexBuffer>>& result = ptr->GetVertexBuffers();
    return VectorToHandleArray(result, "Array<VertexBuffer@>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Geometry_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Geometry* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// PODVector<int> Graphics::GetMultiSampleLevels() const | File: ../Graphics/Graphics.h
static CScriptArray* Graphics_GetMultiSampleLevels_void(Graphics* ptr)
{
    PODVector<int> result = ptr->GetMultiSampleLevels();
    return VectorToArray(result, "Array<int>");
}

// PODVector<IntVector3> Graphics::GetResolutions(int monitor) const | File: ../Graphics/Graphics.h
static CScriptArray* Graphics_GetResolutions_int(Graphics* ptr, int monitor)
{
    PODVector<IntVector3> result = ptr->GetResolutions(monitor);
    return VectorToArray(result, "Array<IntVector3>");
}

// explicit Graphics::Graphics(Context* context) | File: ../Graphics/Graphics.h
static Graphics* Graphics_Graphics_Context()
{
    return new Graphics(GetScriptContext());
}

// bool Graphics::SetVertexBuffers(const Vector<SharedPtr<VertexBuffer>>& buffers, unsigned instanceOffset=0) | File: ../Graphics/Graphics.h
static bool Graphics_SetVertexBuffers_VectorSharedPtrVertexBuffer_unsigned(Graphics* ptr, CScriptArray* buffers_conv, unsigned instanceOffset)
{
    Vector<SharedPtr<VertexBuffer>> buffers = HandleArrayToVector<VertexBuffer>(buffers_conv);
    bool result = ptr->SetVertexBuffers(buffers, instanceOffset);
    return result;
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Graphics_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Graphics* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_PHYSICS
// GImpactMeshData::GImpactMeshData(Model* model, unsigned lodLevel) | File: ../Physics/CollisionShape.h
static GImpactMeshData* GImpactMeshData_GImpactMeshData_Model_unsigned(Model *model, unsigned lodLevel)
{
    return new GImpactMeshData(model, lodLevel);
}
#endif

#ifdef URHO3D_PHYSICS
// explicit GImpactMeshData::GImpactMeshData(CustomGeometry* custom) | File: ../Physics/CollisionShape.h
static GImpactMeshData* GImpactMeshData_GImpactMeshData_CustomGeometry(CustomGeometry *custom)
{
    return new GImpactMeshData(custom);
}
#endif

void ASRegisterGenerated_Members_G(asIScriptEngine* engine)
{
    // void GPUObject::ClearDataLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "void ClearDataLost()", AS_METHODPR(GPUObject, ClearDataLost, (), void), AS_CALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "uint GetGPUObjectName() const", AS_METHODPR(GPUObject, GetGPUObjectName, () const, unsigned), AS_CALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "Graphics@+ GetGraphics() const", AS_METHODPR(GPUObject, GetGraphics, () const, Graphics*), AS_CALL_THISCALL);
    // explicit GPUObject::GPUObject(Graphics* graphics) | File: ../Graphics/GPUObject.h
    engine->RegisterObjectBehaviour("GPUObject", asBEHAVE_CONSTRUCT, "void f(Graphics@+)", AS_FUNCTION_OBJFIRST(GPUObject_GPUObject_Graphics), AS_CALL_CDECL_OBJFIRST);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "bool HasPendingData() const", AS_METHODPR(GPUObject, HasPendingData, () const, bool), AS_CALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "bool IsDataLost() const", AS_METHODPR(GPUObject, IsDataLost, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("GPUObject", "bool get_dataLost() const", AS_METHODPR(GPUObject, IsDataLost, () const, bool), AS_CALL_THISCALL);
    // virtual void GPUObject::OnDeviceLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "void OnDeviceLost()", AS_METHODPR(GPUObject, OnDeviceLost, (), void), AS_CALL_THISCALL);
    // virtual void GPUObject::OnDeviceReset() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "void OnDeviceReset()", AS_METHODPR(GPUObject, OnDeviceReset, (), void), AS_CALL_THISCALL);
    // virtual void GPUObject::Release() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "void Release()", AS_METHODPR(GPUObject, Release, (), void), AS_CALL_THISCALL);
    // GPUObject& GPUObject::operator=(const GPUObject&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<GPUObject>(engine, "GPUObject");
#ifdef REGISTER_MANUAL_PART_GPUObject
    REGISTER_MANUAL_PART_GPUObject(GPUObject, "GPUObject")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Geometry", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Geometry, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Geometry::Draw(Graphics* graphics) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "void Draw(Graphics@+)", AS_METHODPR(Geometry, Draw, (Graphics*), void), AS_CALL_THISCALL);
    // explicit Geometry::Geometry(Context* context) | File: ../Graphics/Geometry.h
    engine->RegisterObjectBehaviour("Geometry", asBEHAVE_FACTORY, "Geometry@+ f()", AS_FUNCTION(Geometry_Geometry_Context), AS_CALL_CDECL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "bool GetBlockEvents() const", AS_METHODPR(Geometry, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // unsigned short Geometry::GetBufferHash() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "uint16 GetBufferHash() const", AS_METHODPR(Geometry, GetBufferHash, () const, unsigned short), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "const String& GetCategory() const", AS_METHODPR(Geometry, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "const String& get_category() const", AS_METHODPR(Geometry, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "VariantMap& GetEventDataMap() const", AS_METHODPR(Geometry, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "Object@+ GetEventSender() const", AS_METHODPR(Geometry, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Geometry, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Geometry, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Geometry, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "const VariantMap& get_globalVars() const", AS_METHODPR(Geometry, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // float Geometry::GetHitDistance(const Ray& ray, Vector3* outNormal=nullptr, Vector2* outUV=nullptr) const | File: ../Graphics/Geometry.h
    // Error: type "Vector3*" can not automatically bind
    // IndexBuffer* Geometry::GetIndexBuffer() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "IndexBuffer@+ GetIndexBuffer() const", AS_METHODPR(Geometry, GetIndexBuffer, () const, IndexBuffer*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "IndexBuffer@+ get_indexBuffer() const", AS_METHODPR(Geometry, GetIndexBuffer, () const, IndexBuffer*), AS_CALL_THISCALL);
    // unsigned Geometry::GetIndexCount() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "uint GetIndexCount() const", AS_METHODPR(Geometry, GetIndexCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "uint get_indexCount() const", AS_METHODPR(Geometry, GetIndexCount, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Geometry::GetIndexStart() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "uint GetIndexStart() const", AS_METHODPR(Geometry, GetIndexStart, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "uint get_indexStart() const", AS_METHODPR(Geometry, GetIndexStart, () const, unsigned), AS_CALL_THISCALL);
    // float Geometry::GetLodDistance() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "float GetLodDistance() const", AS_METHODPR(Geometry, GetLodDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "float get_lodDistance() const", AS_METHODPR(Geometry, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Geometry::GetNumVertexBuffers() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "uint GetNumVertexBuffers() const", AS_METHODPR(Geometry, GetNumVertexBuffers, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "uint get_numVertexBuffers() const", AS_METHODPR(Geometry, GetNumVertexBuffers, () const, unsigned), AS_CALL_THISCALL);
    // PrimitiveType Geometry::GetPrimitiveType() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "PrimitiveType GetPrimitiveType() const", AS_METHODPR(Geometry, GetPrimitiveType, () const, PrimitiveType), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "PrimitiveType get_primitiveType() const", AS_METHODPR(Geometry, GetPrimitiveType, () const, PrimitiveType), AS_CALL_THISCALL);
    // void Geometry::GetRawData(const unsigned char*& vertexData, unsigned& vertexSize, const unsigned char*& indexData, unsigned& indexSize, const PODVector<VertexElement>*& elements) const | File: ../Graphics/Geometry.h
    // Error: type "const unsigned char*&" can not automatically bind
    // void Geometry::GetRawDataShared(SharedArrayPtr<unsigned char>& vertexData, unsigned& vertexSize, SharedArrayPtr<unsigned char>& indexData, unsigned& indexSize, const PODVector<VertexElement>*& elements) const | File: ../Graphics/Geometry.h
    // Error: type "SharedArrayPtr<unsigned char>&" can not automatically bind
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Geometry, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "StringHash GetType() const", AS_METHODPR(Geometry, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "StringHash get_type() const", AS_METHODPR(Geometry, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "const String& GetTypeName() const", AS_METHODPR(Geometry, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "const String& get_typeName() const", AS_METHODPR(Geometry, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // VertexBuffer* Geometry::GetVertexBuffer(unsigned index) const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "VertexBuffer@+ GetVertexBuffer(uint) const", AS_METHODPR(Geometry, GetVertexBuffer, (unsigned) const, VertexBuffer*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "VertexBuffer@+ get_vertexBuffers(uint) const", AS_METHODPR(Geometry, GetVertexBuffer, (unsigned) const, VertexBuffer*), AS_CALL_THISCALL);
    // const Vector<SharedPtr<VertexBuffer>>& Geometry::GetVertexBuffers() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "Array<VertexBuffer@>@ GetVertexBuffers() const", AS_FUNCTION_OBJFIRST(Geometry_GetVertexBuffers_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Geometry::GetVertexCount() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "uint GetVertexCount() const", AS_METHODPR(Geometry, GetVertexCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "uint get_vertexCount() const", AS_METHODPR(Geometry, GetVertexCount, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Geometry::GetVertexStart() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "uint GetVertexStart() const", AS_METHODPR(Geometry, GetVertexStart, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "uint get_vertexStart() const", AS_METHODPR(Geometry, GetVertexStart, () const, unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "bool HasEventHandlers() const", AS_METHODPR(Geometry, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Geometry, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Geometry, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Geometry::IsEmpty() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "bool IsEmpty() const", AS_METHODPR(Geometry, IsEmpty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "bool get_empty() const", AS_METHODPR(Geometry, IsEmpty, () const, bool), AS_CALL_THISCALL);
    // bool Geometry::IsInside(const Ray& ray) const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "bool IsInside(const Ray&in) const", AS_METHODPR(Geometry, IsInside, (const Ray&) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Geometry, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Geometry, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Geometry", "int Refs() const", AS_METHODPR(Geometry, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "int get_refs() const", AS_METHODPR(Geometry, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Geometry", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Geometry, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void SendEvent(StringHash)", AS_METHODPR(Geometry, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Geometry, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void SetBlockEvents(bool)", AS_METHODPR(Geometry, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // bool Geometry::SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, bool getUsedVertexRange=true) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "bool SetDrawRange(PrimitiveType, uint, uint, bool = true)", AS_METHODPR(Geometry, SetDrawRange, (PrimitiveType, unsigned, unsigned, bool), bool), AS_CALL_THISCALL);
    // bool Geometry::SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned vertexStart, unsigned vertexCount, bool checkIllegal=true) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "bool SetDrawRange(PrimitiveType, uint, uint, uint, uint, bool = true)", AS_METHODPR(Geometry, SetDrawRange, (PrimitiveType, unsigned, unsigned, unsigned, unsigned, bool), bool), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Geometry, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Geometry, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Geometry::SetIndexBuffer(IndexBuffer* buffer) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "void SetIndexBuffer(IndexBuffer@+)", AS_METHODPR(Geometry, SetIndexBuffer, (IndexBuffer*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "void set_indexBuffer(IndexBuffer@+)", AS_METHODPR(Geometry, SetIndexBuffer, (IndexBuffer*), void), AS_CALL_THISCALL);
    // void Geometry::SetLodDistance(float distance) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "void SetLodDistance(float)", AS_METHODPR(Geometry, SetLodDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "void set_lodDistance(float)", AS_METHODPR(Geometry, SetLodDistance, (float), void), AS_CALL_THISCALL);
    // bool Geometry::SetNumVertexBuffers(unsigned num) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "bool SetNumVertexBuffers(uint)", AS_METHODPR(Geometry, SetNumVertexBuffers, (unsigned), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "bool set_numVertexBuffers(uint)", AS_METHODPR(Geometry, SetNumVertexBuffers, (unsigned), bool), AS_CALL_THISCALL);
    // void Geometry::SetRawIndexData(const SharedArrayPtr<unsigned char>& data, unsigned indexSize) | File: ../Graphics/Geometry.h
    // Error: type "const SharedArrayPtr<unsigned char>&" can not automatically bind
    // void Geometry::SetRawVertexData(const SharedArrayPtr<unsigned char>& data, const PODVector<VertexElement>& elements) | File: ../Graphics/Geometry.h
    // Error: type "const SharedArrayPtr<unsigned char>&" can not automatically bind
    // void Geometry::SetRawVertexData(const SharedArrayPtr<unsigned char>& data, unsigned elementMask) | File: ../Graphics/Geometry.h
    // Error: type "const SharedArrayPtr<unsigned char>&" can not automatically bind
    // bool Geometry::SetVertexBuffer(unsigned index, VertexBuffer* buffer) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "bool SetVertexBuffer(uint, VertexBuffer@+)", AS_METHODPR(Geometry, SetVertexBuffer, (unsigned, VertexBuffer*), bool), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void UnsubscribeFromAllEvents()", AS_METHODPR(Geometry, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Geometry_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Geometry, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Geometry, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Geometry, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Geometry", "int WeakRefs() const", AS_METHODPR(Geometry, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "int get_weakRefs() const", AS_METHODPR(Geometry, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Geometry, "Geometry")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Geometry, "Geometry")
#endif
#ifdef REGISTER_MANUAL_PART_Geometry
    REGISTER_MANUAL_PART_Geometry(Geometry, "Geometry")
#endif
    RegisterSubclass<Object, Geometry>(engine, "Object", "Geometry");
    RegisterSubclass<RefCounted, Geometry>(engine, "RefCounted", "Geometry");

    // void Graphics::AddGPUObject(GPUObject* object) | File: ../Graphics/Graphics.h
    // Error: type "GPUObject*" can not automatically bind
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Graphics", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Graphics, AddRef, (), void), AS_CALL_THISCALL);
    // void Graphics::BeginDumpShaders(const String& fileName) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void BeginDumpShaders(const String&in)", AS_METHODPR(Graphics, BeginDumpShaders, (const String&), void), AS_CALL_THISCALL);
    // bool Graphics::BeginFrame() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool BeginFrame()", AS_METHODPR(Graphics, BeginFrame, (), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Graphics::CleanupRenderSurface(RenderSurface* surface) | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Graphics::CleanupScratchBuffers() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void CleanupScratchBuffers()", AS_METHODPR(Graphics, CleanupScratchBuffers, (), void), AS_CALL_THISCALL);
    // void Graphics::CleanupShaderPrograms(ShaderVariation* variation) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void CleanupShaderPrograms(ShaderVariation@+)", AS_METHODPR(Graphics, CleanupShaderPrograms, (ShaderVariation*), void), AS_CALL_THISCALL);
    // void Graphics::Clear(ClearTargetFlags flags, const Color& color=Color(0.0f, 0.0f, 0.0f, 0.0f), float depth=1.0f, unsigned stencil=0) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Clear(ClearTargetFlags, const Color&in = Color(0.0f, 0.0f, 0.0f, 0.0f), float = 1.0f, uint = 0)", AS_METHODPR(Graphics, Clear, (ClearTargetFlags, const Color&, float, unsigned), void), AS_CALL_THISCALL);
    // void Graphics::ClearParameterSource(ShaderParameterGroup group) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void ClearParameterSource(ShaderParameterGroup)", AS_METHODPR(Graphics, ClearParameterSource, (ShaderParameterGroup), void), AS_CALL_THISCALL);
    // void Graphics::ClearParameterSources() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void ClearParameterSources()", AS_METHODPR(Graphics, ClearParameterSources, (), void), AS_CALL_THISCALL);
    // void Graphics::ClearTransformSources() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void ClearTransformSources()", AS_METHODPR(Graphics, ClearTransformSources, (), void), AS_CALL_THISCALL);
    // void Graphics::Close() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Close()", AS_METHODPR(Graphics, Close, (), void), AS_CALL_THISCALL);
    // void Graphics::Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Draw(PrimitiveType, uint, uint)", AS_METHODPR(Graphics, Draw, (PrimitiveType, unsigned, unsigned), void), AS_CALL_THISCALL);
    // void Graphics::Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Draw(PrimitiveType, uint, uint, uint, uint)", AS_METHODPR(Graphics, Draw, (PrimitiveType, unsigned, unsigned, unsigned, unsigned), void), AS_CALL_THISCALL);
    // void Graphics::Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned baseVertexIndex, unsigned minVertex, unsigned vertexCount) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Draw(PrimitiveType, uint, uint, uint, uint, uint)", AS_METHODPR(Graphics, Draw, (PrimitiveType, unsigned, unsigned, unsigned, unsigned, unsigned), void), AS_CALL_THISCALL);
    // void Graphics::DrawInstanced(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount, unsigned instanceCount) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void DrawInstanced(PrimitiveType, uint, uint, uint, uint, uint)", AS_METHODPR(Graphics, DrawInstanced, (PrimitiveType, unsigned, unsigned, unsigned, unsigned, unsigned), void), AS_CALL_THISCALL);
    // void Graphics::DrawInstanced(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned baseVertexIndex, unsigned minVertex, unsigned vertexCount, unsigned instanceCount) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void DrawInstanced(PrimitiveType, uint, uint, uint, uint, uint, uint)", AS_METHODPR(Graphics, DrawInstanced, (PrimitiveType, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned), void), AS_CALL_THISCALL);
    // void Graphics::EndDumpShaders() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void EndDumpShaders()", AS_METHODPR(Graphics, EndDumpShaders, (), void), AS_CALL_THISCALL);
    // void Graphics::EndFrame() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void EndFrame()", AS_METHODPR(Graphics, EndFrame, (), void), AS_CALL_THISCALL);
    // unsigned Graphics::FindBestResolutionIndex(int monitor, int width, int height, int refreshRate) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint FindBestResolutionIndex(int, int, int, int) const", AS_METHODPR(Graphics, FindBestResolutionIndex, (int, int, int, int) const, unsigned), AS_CALL_THISCALL);
    // void Graphics::FreeScratchBuffer(void* buffer) | File: ../Graphics/Graphics.h
    // Error: type "void*" can not automatically bind
    // static unsigned Graphics::GetAlphaFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetAlphaFormat()", AS_FUNCTIONPR(Graphics::GetAlphaFormat, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Graphics::GetAlphaToCoverage() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetAlphaToCoverage() const", AS_METHODPR(Graphics, GetAlphaToCoverage, () const, bool), AS_CALL_THISCALL);
    // bool Graphics::GetAnisotropySupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetAnisotropySupport() const", AS_METHODPR(Graphics, GetAnisotropySupport, () const, bool), AS_CALL_THISCALL);
    // const String& Graphics::GetApiName() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const String& GetApiName() const", AS_METHODPR(Graphics, GetApiName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_apiName() const", AS_METHODPR(Graphics, GetApiName, () const, const String&), AS_CALL_THISCALL);
    // BlendMode Graphics::GetBlendMode() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "BlendMode GetBlendMode() const", AS_METHODPR(Graphics, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "bool GetBlockEvents() const", AS_METHODPR(Graphics, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // bool Graphics::GetBorderless() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetBorderless() const", AS_METHODPR(Graphics, GetBorderless, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_borderless() const", AS_METHODPR(Graphics, GetBorderless, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "const String& GetCategory() const", AS_METHODPR(Graphics, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_category() const", AS_METHODPR(Graphics, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // bool Graphics::GetColorWrite() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetColorWrite() const", AS_METHODPR(Graphics, GetColorWrite, () const, bool), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // CullMode Graphics::GetCullMode() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "CullMode GetCullMode() const", AS_METHODPR(Graphics, GetCullMode, () const, CullMode), AS_CALL_THISCALL);
    // int Graphics::GetCurrentMonitor() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetCurrentMonitor() const", AS_METHODPR(Graphics, GetCurrentMonitor, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_currentMonitor() const", AS_METHODPR(Graphics, GetCurrentMonitor, () const, int), AS_CALL_THISCALL);
    // unsigned Graphics::GetDefaultTextureAnisotropy() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetDefaultTextureAnisotropy() const", AS_METHODPR(Graphics, GetDefaultTextureAnisotropy, () const, unsigned), AS_CALL_THISCALL);
    // TextureFilterMode Graphics::GetDefaultTextureFilterMode() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "TextureFilterMode GetDefaultTextureFilterMode() const", AS_METHODPR(Graphics, GetDefaultTextureFilterMode, () const, TextureFilterMode), AS_CALL_THISCALL);
    // bool Graphics::GetDeferredSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetDeferredSupport() const", AS_METHODPR(Graphics, GetDeferredSupport, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_deferredSupport() const", AS_METHODPR(Graphics, GetDeferredSupport, () const, bool), AS_CALL_THISCALL);
    // float Graphics::GetDepthConstantBias() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "float GetDepthConstantBias() const", AS_METHODPR(Graphics, GetDepthConstantBias, () const, float), AS_CALL_THISCALL);
    // float Graphics::GetDepthSlopeScaledBias() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "float GetDepthSlopeScaledBias() const", AS_METHODPR(Graphics, GetDepthSlopeScaledBias, () const, float), AS_CALL_THISCALL);
    // RenderSurface* Graphics::GetDepthStencil() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "RenderSurface@+ GetDepthStencil() const", AS_METHODPR(Graphics, GetDepthStencil, () const, RenderSurface*), AS_CALL_THISCALL);
    // static unsigned Graphics::GetDepthStencilFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetDepthStencilFormat()", AS_FUNCTIONPR(Graphics::GetDepthStencilFormat, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // CompareMode Graphics::GetDepthTest() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "CompareMode GetDepthTest() const", AS_METHODPR(Graphics, GetDepthTest, () const, CompareMode), AS_CALL_THISCALL);
    // bool Graphics::GetDepthWrite() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetDepthWrite() const", AS_METHODPR(Graphics, GetDepthWrite, () const, bool), AS_CALL_THISCALL);
    // IntVector2 Graphics::GetDesktopResolution(int monitor) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "IntVector2 GetDesktopResolution(int) const", AS_METHODPR(Graphics, GetDesktopResolution, (int) const, IntVector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "IntVector2 get_desktopResolution(int) const", AS_METHODPR(Graphics, GetDesktopResolution, (int) const, IntVector2), AS_CALL_THISCALL);
    // Vector3 Graphics::GetDisplayDPI(int monitor=0) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "Vector3 GetDisplayDPI(int = 0) const", AS_METHODPR(Graphics, GetDisplayDPI, (int) const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "Vector3 get_displayDPI(int = 0) const", AS_METHODPR(Graphics, GetDisplayDPI, (int) const, Vector3), AS_CALL_THISCALL);
    // bool Graphics::GetDither() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetDither() const", AS_METHODPR(Graphics, GetDither, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_dither() const", AS_METHODPR(Graphics, GetDither, () const, bool), AS_CALL_THISCALL);
    // unsigned Graphics::GetDummyColorFormat() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetDummyColorFormat() const", AS_METHODPR(Graphics, GetDummyColorFormat, () const, unsigned), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "VariantMap& GetEventDataMap() const", AS_METHODPR(Graphics, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "Object@+ GetEventSender() const", AS_METHODPR(Graphics, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // void* Graphics::GetExternalWindow() const | File: ../Graphics/Graphics.h
    // Error: type "void*" can not automatically bind
    // FillMode Graphics::GetFillMode() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "FillMode GetFillMode() const", AS_METHODPR(Graphics, GetFillMode, () const, FillMode), AS_CALL_THISCALL);
    // static unsigned Graphics::GetFloat16Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetFloat16Format()", AS_FUNCTIONPR(Graphics::GetFloat16Format, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetFloat32Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetFloat32Format()", AS_FUNCTIONPR(Graphics::GetFloat32Format, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Graphics::GetFlushGPU() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetFlushGPU() const", AS_METHODPR(Graphics, GetFlushGPU, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_flushGPU() const", AS_METHODPR(Graphics, GetFlushGPU, () const, bool), AS_CALL_THISCALL);
    // bool Graphics::GetForceGL2() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetForceGL2() const", AS_METHODPR(Graphics, GetForceGL2, () const, bool), AS_CALL_THISCALL);
    // unsigned Graphics::GetFormat(CompressedFormat format) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetFormat(CompressedFormat) const", AS_METHODPR(Graphics, GetFormat, (CompressedFormat) const, unsigned), AS_CALL_THISCALL);
    // static unsigned Graphics::GetFormat(const String& formatName) | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetFormat(const String&in)", AS_FUNCTIONPR(Graphics::GetFormat, (const String&), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Graphics::GetFullscreen() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetFullscreen() const", AS_METHODPR(Graphics, GetFullscreen, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_fullscreen() const", AS_METHODPR(Graphics, GetFullscreen, () const, bool), AS_CALL_THISCALL);
    // static bool Graphics::GetGL3Support() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("bool GetGL3Support()", AS_FUNCTIONPR(Graphics::GetGL3Support, (), bool), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Graphics, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Graphics, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Graphics, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const VariantMap& get_globalVars() const", AS_METHODPR(Graphics, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // bool Graphics::GetHardwareShadowSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetHardwareShadowSupport() const", AS_METHODPR(Graphics, GetHardwareShadowSupport, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_hardwareShadowSupport() const", AS_METHODPR(Graphics, GetHardwareShadowSupport, () const, bool), AS_CALL_THISCALL);
    // int Graphics::GetHeight() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetHeight() const", AS_METHODPR(Graphics, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_height() const", AS_METHODPR(Graphics, GetHeight, () const, int), AS_CALL_THISCALL);
    // bool Graphics::GetHighDPI() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetHighDPI() const", AS_METHODPR(Graphics, GetHighDPI, () const, bool), AS_CALL_THISCALL);
    // unsigned Graphics::GetHiresShadowMapFormat() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetHiresShadowMapFormat() const", AS_METHODPR(Graphics, GetHiresShadowMapFormat, () const, unsigned), AS_CALL_THISCALL);
    // GraphicsImpl* Graphics::GetImpl() const | File: ../Graphics/Graphics.h
    // Error: type "GraphicsImpl*" can not automatically bind
    // IndexBuffer* Graphics::GetIndexBuffer() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "IndexBuffer@+ GetIndexBuffer() const", AS_METHODPR(Graphics, GetIndexBuffer, () const, IndexBuffer*), AS_CALL_THISCALL);
    // bool Graphics::GetInstancingSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetInstancingSupport() const", AS_METHODPR(Graphics, GetInstancingSupport, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_instancingSupport() const", AS_METHODPR(Graphics, GetInstancingSupport, () const, bool), AS_CALL_THISCALL);
    // bool Graphics::GetLightPrepassSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetLightPrepassSupport() const", AS_METHODPR(Graphics, GetLightPrepassSupport, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_lightPrepassSupport() const", AS_METHODPR(Graphics, GetLightPrepassSupport, () const, bool), AS_CALL_THISCALL);
    // bool Graphics::GetLineAntiAlias() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetLineAntiAlias() const", AS_METHODPR(Graphics, GetLineAntiAlias, () const, bool), AS_CALL_THISCALL);
    // static unsigned Graphics::GetLinearDepthFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetLinearDepthFormat()", AS_FUNCTIONPR(Graphics::GetLinearDepthFormat, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetLuminanceAlphaFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetLuminanceAlphaFormat()", AS_FUNCTIONPR(Graphics::GetLuminanceAlphaFormat, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetLuminanceFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetLuminanceFormat()", AS_FUNCTIONPR(Graphics::GetLuminanceFormat, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetMaxBones() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetMaxBones()", AS_FUNCTIONPR(Graphics::GetMaxBones, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Graphics::GetMaximized() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetMaximized() const", AS_METHODPR(Graphics, GetMaximized, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_maximized() const", AS_METHODPR(Graphics, GetMaximized, () const, bool), AS_CALL_THISCALL);
    // int Graphics::GetMonitor() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetMonitor() const", AS_METHODPR(Graphics, GetMonitor, () const, int), AS_CALL_THISCALL);
    // int Graphics::GetMonitorCount() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetMonitorCount() const", AS_METHODPR(Graphics, GetMonitorCount, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_monitorCount() const", AS_METHODPR(Graphics, GetMonitorCount, () const, int), AS_CALL_THISCALL);
    // int Graphics::GetMultiSample() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetMultiSample() const", AS_METHODPR(Graphics, GetMultiSample, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_multiSample() const", AS_METHODPR(Graphics, GetMultiSample, () const, int), AS_CALL_THISCALL);
    // PODVector<int> Graphics::GetMultiSampleLevels() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "Array<int>@ GetMultiSampleLevels() const", AS_FUNCTION_OBJFIRST(Graphics_GetMultiSampleLevels_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Graphics", "Array<int>@ get_multiSampleLevels() const", AS_FUNCTION_OBJFIRST(Graphics_GetMultiSampleLevels_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Graphics::GetNumBatches() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetNumBatches() const", AS_METHODPR(Graphics, GetNumBatches, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "uint get_numBatches() const", AS_METHODPR(Graphics, GetNumBatches, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Graphics::GetNumPrimitives() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetNumPrimitives() const", AS_METHODPR(Graphics, GetNumPrimitives, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "uint get_numPrimitives() const", AS_METHODPR(Graphics, GetNumPrimitives, () const, unsigned), AS_CALL_THISCALL);
    // ConstantBuffer* Graphics::GetOrCreateConstantBuffer(ShaderType type, unsigned index, unsigned size) | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // const String& Graphics::GetOrientations() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const String& GetOrientations() const", AS_METHODPR(Graphics, GetOrientations, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_orientations() const", AS_METHODPR(Graphics, GetOrientations, () const, const String&), AS_CALL_THISCALL);
    // ShaderVariation* Graphics::GetPixelShader() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "ShaderVariation@+ GetPixelShader() const", AS_METHODPR(Graphics, GetPixelShader, () const, ShaderVariation*), AS_CALL_THISCALL);
    // static const Vector2& Graphics::GetPixelUVOffset() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("const Vector2& GetPixelUVOffset()", AS_FUNCTIONPR(Graphics::GetPixelUVOffset, (), const Vector2&), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetReadableDepthFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetReadableDepthFormat()", AS_FUNCTIONPR(Graphics::GetReadableDepthFormat, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Graphics::GetReadableDepthSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetReadableDepthSupport() const", AS_METHODPR(Graphics, GetReadableDepthSupport, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_readableDepthSupport() const", AS_METHODPR(Graphics, GetReadableDepthSupport, () const, bool), AS_CALL_THISCALL);
    // int Graphics::GetRefreshRate() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetRefreshRate() const", AS_METHODPR(Graphics, GetRefreshRate, () const, int), AS_CALL_THISCALL);
    // RenderSurface* Graphics::GetRenderTarget(unsigned index) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "RenderSurface@+ GetRenderTarget(uint) const", AS_METHODPR(Graphics, GetRenderTarget, (unsigned) const, RenderSurface*), AS_CALL_THISCALL);
    // IntVector2 Graphics::GetRenderTargetDimensions() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "IntVector2 GetRenderTargetDimensions() const", AS_METHODPR(Graphics, GetRenderTargetDimensions, () const, IntVector2), AS_CALL_THISCALL);
    // bool Graphics::GetResizable() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetResizable() const", AS_METHODPR(Graphics, GetResizable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_resizable() const", AS_METHODPR(Graphics, GetResizable, () const, bool), AS_CALL_THISCALL);
    // PODVector<IntVector3> Graphics::GetResolutions(int monitor) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "Array<IntVector3>@ GetResolutions(int) const", AS_FUNCTION_OBJFIRST(Graphics_GetResolutions_int), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Graphics", "Array<IntVector3>@ get_resolutions(int) const", AS_FUNCTION_OBJFIRST(Graphics_GetResolutions_int), AS_CALL_CDECL_OBJFIRST);
    // static unsigned Graphics::GetRG16Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRG16Format()", AS_FUNCTIONPR(Graphics::GetRG16Format, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGBA16Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGBA16Format()", AS_FUNCTIONPR(Graphics::GetRGBA16Format, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGBAFloat16Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGBAFloat16Format()", AS_FUNCTIONPR(Graphics::GetRGBAFloat16Format, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGBAFloat32Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGBAFloat32Format()", AS_FUNCTIONPR(Graphics::GetRGBAFloat32Format, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGBAFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGBAFormat()", AS_FUNCTIONPR(Graphics::GetRGBAFormat, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGBFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGBFormat()", AS_FUNCTIONPR(Graphics::GetRGBFormat, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGFloat16Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGFloat16Format()", AS_FUNCTIONPR(Graphics::GetRGFloat16Format, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGFloat32Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGFloat32Format()", AS_FUNCTIONPR(Graphics::GetRGFloat32Format, (), unsigned), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // const IntRect& Graphics::GetScissorRect() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const IntRect& GetScissorRect() const", AS_METHODPR(Graphics, GetScissorRect, () const, const IntRect&), AS_CALL_THISCALL);
    // bool Graphics::GetScissorTest() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetScissorTest() const", AS_METHODPR(Graphics, GetScissorTest, () const, bool), AS_CALL_THISCALL);
    // const ScreenModeParams& Graphics::GetScreenModeParams() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const ScreenModeParams& GetScreenModeParams() const", AS_METHODPR(Graphics, GetScreenModeParams, () const, const ScreenModeParams&), AS_CALL_THISCALL);
    // ShaderVariation* Graphics::GetShader(ShaderType type, const String& name, const String& defines=String::EMPTY) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "ShaderVariation@+ GetShader(ShaderType, const String&in, const String&in = String::EMPTY) const", AS_METHODPR(Graphics, GetShader, (ShaderType, const String&, const String&) const, ShaderVariation*), AS_CALL_THISCALL);
    // ShaderVariation* Graphics::GetShader(ShaderType type, const char* name, const char* defines) const | File: ../Graphics/Graphics.h
    // Error: type "const char*" can not automatically bind
    // const String& Graphics::GetShaderCacheDir() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const String& GetShaderCacheDir() const", AS_METHODPR(Graphics, GetShaderCacheDir, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_shaderCacheDir() const", AS_METHODPR(Graphics, GetShaderCacheDir, () const, const String&), AS_CALL_THISCALL);
    // ShaderProgram* Graphics::GetShaderProgram() const | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // unsigned Graphics::GetShadowMapFormat() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetShadowMapFormat() const", AS_METHODPR(Graphics, GetShadowMapFormat, () const, unsigned), AS_CALL_THISCALL);
    // IntVector2 Graphics::GetSize() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "IntVector2 GetSize() const", AS_METHODPR(Graphics, GetSize, () const, IntVector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "IntVector2 get_size() const", AS_METHODPR(Graphics, GetSize, () const, IntVector2), AS_CALL_THISCALL);
    // bool Graphics::GetSRGB() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetSRGB() const", AS_METHODPR(Graphics, GetSRGB, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_sRGB() const", AS_METHODPR(Graphics, GetSRGB, () const, bool), AS_CALL_THISCALL);
    // bool Graphics::GetSRGBSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetSRGBSupport() const", AS_METHODPR(Graphics, GetSRGBSupport, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_sRGBSupport() const", AS_METHODPR(Graphics, GetSRGBSupport, () const, bool), AS_CALL_THISCALL);
    // bool Graphics::GetSRGBWriteSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetSRGBWriteSupport() const", AS_METHODPR(Graphics, GetSRGBWriteSupport, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_sRGBWriteSupport() const", AS_METHODPR(Graphics, GetSRGBWriteSupport, () const, bool), AS_CALL_THISCALL);
    // unsigned Graphics::GetStencilCompareMask() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetStencilCompareMask() const", AS_METHODPR(Graphics, GetStencilCompareMask, () const, unsigned), AS_CALL_THISCALL);
    // StencilOp Graphics::GetStencilFail() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "StencilOp GetStencilFail() const", AS_METHODPR(Graphics, GetStencilFail, () const, StencilOp), AS_CALL_THISCALL);
    // StencilOp Graphics::GetStencilPass() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "StencilOp GetStencilPass() const", AS_METHODPR(Graphics, GetStencilPass, () const, StencilOp), AS_CALL_THISCALL);
    // unsigned Graphics::GetStencilRef() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetStencilRef() const", AS_METHODPR(Graphics, GetStencilRef, () const, unsigned), AS_CALL_THISCALL);
    // bool Graphics::GetStencilTest() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetStencilTest() const", AS_METHODPR(Graphics, GetStencilTest, () const, bool), AS_CALL_THISCALL);
    // CompareMode Graphics::GetStencilTestMode() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "CompareMode GetStencilTestMode() const", AS_METHODPR(Graphics, GetStencilTestMode, () const, CompareMode), AS_CALL_THISCALL);
    // unsigned Graphics::GetStencilWriteMask() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetStencilWriteMask() const", AS_METHODPR(Graphics, GetStencilWriteMask, () const, unsigned), AS_CALL_THISCALL);
    // StencilOp Graphics::GetStencilZFail() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "StencilOp GetStencilZFail() const", AS_METHODPR(Graphics, GetStencilZFail, () const, StencilOp), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Graphics, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Texture* Graphics::GetTexture(unsigned index) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "Texture@+ GetTexture(uint) const", AS_METHODPR(Graphics, GetTexture, (unsigned) const, Texture*), AS_CALL_THISCALL);
    // TextureUnit Graphics::GetTextureUnit(const String& name) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "TextureUnit GetTextureUnit(const String&in)", AS_METHODPR(Graphics, GetTextureUnit, (const String&), TextureUnit), AS_CALL_THISCALL);
    // const String& Graphics::GetTextureUnitName(TextureUnit unit) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const String& GetTextureUnitName(TextureUnit)", AS_METHODPR(Graphics, GetTextureUnitName, (TextureUnit), const String&), AS_CALL_THISCALL);
    // bool Graphics::GetTripleBuffer() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetTripleBuffer() const", AS_METHODPR(Graphics, GetTripleBuffer, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_tripleBuffer() const", AS_METHODPR(Graphics, GetTripleBuffer, () const, bool), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "StringHash GetType() const", AS_METHODPR(Graphics, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "StringHash get_type() const", AS_METHODPR(Graphics, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "const String& GetTypeName() const", AS_METHODPR(Graphics, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_typeName() const", AS_METHODPR(Graphics, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Graphics::GetUseClipPlane() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetUseClipPlane() const", AS_METHODPR(Graphics, GetUseClipPlane, () const, bool), AS_CALL_THISCALL);
    // VertexBuffer* Graphics::GetVertexBuffer(unsigned index) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "VertexBuffer@+ GetVertexBuffer(uint) const", AS_METHODPR(Graphics, GetVertexBuffer, (unsigned) const, VertexBuffer*), AS_CALL_THISCALL);
    // ShaderVariation* Graphics::GetVertexShader() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "ShaderVariation@+ GetVertexShader() const", AS_METHODPR(Graphics, GetVertexShader, () const, ShaderVariation*), AS_CALL_THISCALL);
    // IntRect Graphics::GetViewport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "IntRect GetViewport() const", AS_METHODPR(Graphics, GetViewport, () const, IntRect), AS_CALL_THISCALL);
    // bool Graphics::GetVSync() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetVSync() const", AS_METHODPR(Graphics, GetVSync, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_vSync() const", AS_METHODPR(Graphics, GetVSync, () const, bool), AS_CALL_THISCALL);
    // int Graphics::GetWidth() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetWidth() const", AS_METHODPR(Graphics, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_width() const", AS_METHODPR(Graphics, GetWidth, () const, int), AS_CALL_THISCALL);
    // SDL_Window* Graphics::GetWindow() const | File: ../Graphics/Graphics.h
    // Error: type "SDL_Window*" can not automatically bind
    // IntVector2 Graphics::GetWindowPosition() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "IntVector2 GetWindowPosition() const", AS_METHODPR(Graphics, GetWindowPosition, () const, IntVector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "IntVector2 get_windowPosition() const", AS_METHODPR(Graphics, GetWindowPosition, () const, IntVector2), AS_CALL_THISCALL);
    // const String& Graphics::GetWindowTitle() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const String& GetWindowTitle() const", AS_METHODPR(Graphics, GetWindowTitle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_windowTitle() const", AS_METHODPR(Graphics, GetWindowTitle, () const, const String&), AS_CALL_THISCALL);
    // explicit Graphics::Graphics(Context* context) | File: ../Graphics/Graphics.h
    engine->RegisterObjectBehaviour("Graphics", asBEHAVE_FACTORY, "Graphics@+ f()", AS_FUNCTION(Graphics_Graphics_Context), AS_CALL_CDECL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "bool HasEventHandlers() const", AS_METHODPR(Graphics, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Graphics::HasShaderParameter(StringHash param) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool HasShaderParameter(StringHash)", AS_METHODPR(Graphics, HasShaderParameter, (StringHash), bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Graphics, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Graphics, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Graphics::HasTextureUnit(TextureUnit unit) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool HasTextureUnit(TextureUnit)", AS_METHODPR(Graphics, HasTextureUnit, (TextureUnit), bool), AS_CALL_THISCALL);
    // bool Graphics::IsDeviceLost() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool IsDeviceLost() const", AS_METHODPR(Graphics, IsDeviceLost, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_deviceLost() const", AS_METHODPR(Graphics, IsDeviceLost, () const, bool), AS_CALL_THISCALL);
    // bool Graphics::IsInitialized() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool IsInitialized() const", AS_METHODPR(Graphics, IsInitialized, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_initialized() const", AS_METHODPR(Graphics, IsInitialized, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Graphics, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // void Graphics::MarkFBODirty() | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Graphics::Maximize() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Maximize()", AS_METHODPR(Graphics, Maximize, (), void), AS_CALL_THISCALL);
    // void Graphics::Minimize() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Minimize()", AS_METHODPR(Graphics, Minimize, (), void), AS_CALL_THISCALL);
    // bool Graphics::NeedParameterUpdate(ShaderParameterGroup group, const void* source) | File: ../Graphics/Graphics.h
    // Error: type "const void*" can not automatically bind
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Graphics, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // void Graphics::OnWindowMoved() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void OnWindowMoved()", AS_METHODPR(Graphics, OnWindowMoved, (), void), AS_CALL_THISCALL);
    // void Graphics::OnWindowResized() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void OnWindowResized()", AS_METHODPR(Graphics, OnWindowResized, (), void), AS_CALL_THISCALL);
    // void Graphics::PrecacheShaders(Deserializer& source) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void PrecacheShaders(Deserializer&)", AS_METHODPR(Graphics, PrecacheShaders, (Deserializer&), void), AS_CALL_THISCALL);
    // void Graphics::Raise() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Raise() const", AS_METHODPR(Graphics, Raise, () const, void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Graphics", "int Refs() const", AS_METHODPR(Graphics, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_refs() const", AS_METHODPR(Graphics, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Graphics", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Graphics, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Graphics::RemoveGPUObject(GPUObject* object) | File: ../Graphics/Graphics.h
    // Error: type "GPUObject*" can not automatically bind
    // void* Graphics::ReserveScratchBuffer(unsigned size) | File: ../Graphics/Graphics.h
    // Error: type "void*" can not automatically bind
    // void Graphics::ResetDepthStencil() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void ResetDepthStencil()", AS_METHODPR(Graphics, ResetDepthStencil, (), void), AS_CALL_THISCALL);
    // void Graphics::ResetRenderTarget(unsigned index) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void ResetRenderTarget(uint)", AS_METHODPR(Graphics, ResetRenderTarget, (unsigned), void), AS_CALL_THISCALL);
    // void Graphics::ResetRenderTargets() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void ResetRenderTargets()", AS_METHODPR(Graphics, ResetRenderTargets, (), void), AS_CALL_THISCALL);
    // bool Graphics::ResolveToTexture(Texture2D* destination, const IntRect& viewport) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool ResolveToTexture(Texture2D@+, const IntRect&in)", AS_METHODPR(Graphics, ResolveToTexture, (Texture2D*, const IntRect&), bool), AS_CALL_THISCALL);
    // bool Graphics::ResolveToTexture(Texture2D* texture) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool ResolveToTexture(Texture2D@+)", AS_METHODPR(Graphics, ResolveToTexture, (Texture2D*), bool), AS_CALL_THISCALL);
    // bool Graphics::ResolveToTexture(TextureCube* texture) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool ResolveToTexture(TextureCube@+)", AS_METHODPR(Graphics, ResolveToTexture, (TextureCube*), bool), AS_CALL_THISCALL);
    // void Graphics::Restore() | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void SendEvent(StringHash)", AS_METHODPR(Graphics, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Graphics, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Graphics::SetBlendMode(BlendMode mode, bool alphaToCoverage=false) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetBlendMode(BlendMode, bool = false)", AS_METHODPR(Graphics, SetBlendMode, (BlendMode, bool), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void SetBlockEvents(bool)", AS_METHODPR(Graphics, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Graphics::SetClipPlane(bool enable, const Plane& clipPlane=Plane::UP, const Matrix3x4& view=Matrix3x4::IDENTITY, const Matrix4& projection=Matrix4::IDENTITY) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetClipPlane(bool, const Plane&in = Plane::UP, const Matrix3x4&in = Matrix3x4::IDENTITY, const Matrix4&in = Matrix4::IDENTITY)", AS_METHODPR(Graphics, SetClipPlane, (bool, const Plane&, const Matrix3x4&, const Matrix4&), void), AS_CALL_THISCALL);
    // void Graphics::SetColorWrite(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetColorWrite(bool)", AS_METHODPR(Graphics, SetColorWrite, (bool), void), AS_CALL_THISCALL);
    // void Graphics::SetCullMode(CullMode mode) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetCullMode(CullMode)", AS_METHODPR(Graphics, SetCullMode, (CullMode), void), AS_CALL_THISCALL);
    // void Graphics::SetDefaultTextureAnisotropy(unsigned level) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDefaultTextureAnisotropy(uint)", AS_METHODPR(Graphics, SetDefaultTextureAnisotropy, (unsigned), void), AS_CALL_THISCALL);
    // void Graphics::SetDefaultTextureFilterMode(TextureFilterMode mode) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDefaultTextureFilterMode(TextureFilterMode)", AS_METHODPR(Graphics, SetDefaultTextureFilterMode, (TextureFilterMode), void), AS_CALL_THISCALL);
    // bool Graphics::SetDefaultWindowModes(int width, int height, const ScreenModeParams& params) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetDefaultWindowModes(int, int, const ScreenModeParams&in)", AS_METHODPR(Graphics, SetDefaultWindowModes, (int, int, const ScreenModeParams&), bool), AS_CALL_THISCALL);
    // void Graphics::SetDepthBias(float constantBias, float slopeScaledBias) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDepthBias(float, float)", AS_METHODPR(Graphics, SetDepthBias, (float, float), void), AS_CALL_THISCALL);
    // void Graphics::SetDepthStencil(RenderSurface* depthStencil) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDepthStencil(RenderSurface@+)", AS_METHODPR(Graphics, SetDepthStencil, (RenderSurface*), void), AS_CALL_THISCALL);
    // void Graphics::SetDepthStencil(Texture2D* texture) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDepthStencil(Texture2D@+)", AS_METHODPR(Graphics, SetDepthStencil, (Texture2D*), void), AS_CALL_THISCALL);
    // void Graphics::SetDepthTest(CompareMode mode) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDepthTest(CompareMode)", AS_METHODPR(Graphics, SetDepthTest, (CompareMode), void), AS_CALL_THISCALL);
    // void Graphics::SetDepthWrite(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDepthWrite(bool)", AS_METHODPR(Graphics, SetDepthWrite, (bool), void), AS_CALL_THISCALL);
    // void Graphics::SetDither(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDither(bool)", AS_METHODPR(Graphics, SetDither, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_dither(bool)", AS_METHODPR(Graphics, SetDither, (bool), void), AS_CALL_THISCALL);
    // void Graphics::SetExternalWindow(void* window) | File: ../Graphics/Graphics.h
    // Error: type "void*" can not automatically bind
    // void Graphics::SetFillMode(FillMode mode) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetFillMode(FillMode)", AS_METHODPR(Graphics, SetFillMode, (FillMode), void), AS_CALL_THISCALL);
    // void Graphics::SetFlushGPU(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetFlushGPU(bool)", AS_METHODPR(Graphics, SetFlushGPU, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_flushGPU(bool)", AS_METHODPR(Graphics, SetFlushGPU, (bool), void), AS_CALL_THISCALL);
    // void Graphics::SetForceGL2(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetForceGL2(bool)", AS_METHODPR(Graphics, SetForceGL2, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Graphics, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Graphics, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Graphics::SetIndexBuffer(IndexBuffer* buffer) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetIndexBuffer(IndexBuffer@+)", AS_METHODPR(Graphics, SetIndexBuffer, (IndexBuffer*), void), AS_CALL_THISCALL);
    // void Graphics::SetLineAntiAlias(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetLineAntiAlias(bool)", AS_METHODPR(Graphics, SetLineAntiAlias, (bool), void), AS_CALL_THISCALL);
    // bool Graphics::SetMode(int width, int height, bool fullscreen, bool borderless, bool resizable, bool highDPI, bool vsync, bool tripleBuffer, int multiSample, int monitor, int refreshRate) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetMode(int, int, bool, bool, bool, bool, bool, bool, int, int, int)", AS_METHODPR(Graphics, SetMode, (int, int, bool, bool, bool, bool, bool, bool, int, int, int), bool), AS_CALL_THISCALL);
    // bool Graphics::SetMode(int width, int height) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetMode(int, int)", AS_METHODPR(Graphics, SetMode, (int, int), bool), AS_CALL_THISCALL);
    // void Graphics::SetOrientations(const String& orientations) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetOrientations(const String&in)", AS_METHODPR(Graphics, SetOrientations, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_orientations(const String&in)", AS_METHODPR(Graphics, SetOrientations, (const String&), void), AS_CALL_THISCALL);
    // void Graphics::SetRenderTarget(unsigned index, RenderSurface* renderTarget) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetRenderTarget(uint, RenderSurface@+)", AS_METHODPR(Graphics, SetRenderTarget, (unsigned, RenderSurface*), void), AS_CALL_THISCALL);
    // void Graphics::SetRenderTarget(unsigned index, Texture2D* texture) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetRenderTarget(uint, Texture2D@+)", AS_METHODPR(Graphics, SetRenderTarget, (unsigned, Texture2D*), void), AS_CALL_THISCALL);
    // void Graphics::SetScissorTest(bool enable, const Rect& rect=Rect::FULL, bool borderInclusive=true) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetScissorTest(bool, const Rect&in = Rect::FULL, bool = true)", AS_METHODPR(Graphics, SetScissorTest, (bool, const Rect&, bool), void), AS_CALL_THISCALL);
    // void Graphics::SetScissorTest(bool enable, const IntRect& rect) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetScissorTest(bool, const IntRect&in)", AS_METHODPR(Graphics, SetScissorTest, (bool, const IntRect&), void), AS_CALL_THISCALL);
    // bool Graphics::SetScreenMode(int width, int height, const ScreenModeParams& params, bool maximize=false) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetScreenMode(int, int, const ScreenModeParams&in, bool = false)", AS_METHODPR(Graphics, SetScreenMode, (int, int, const ScreenModeParams&, bool), bool), AS_CALL_THISCALL);
    // bool Graphics::SetScreenMode(int width, int height) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetScreenMode(int, int)", AS_METHODPR(Graphics, SetScreenMode, (int, int), bool), AS_CALL_THISCALL);
    // void Graphics::SetShaderCacheDir(const String& path) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderCacheDir(const String&in)", AS_METHODPR(Graphics, SetShaderCacheDir, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_shaderCacheDir(const String&in)", AS_METHODPR(Graphics, SetShaderCacheDir, (const String&), void), AS_CALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const float* data, unsigned count) | File: ../Graphics/Graphics.h
    // Error: type "const float*" can not automatically bind
    // void Graphics::SetShaderParameter(StringHash param, float value) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, float)", AS_METHODPR(Graphics, SetShaderParameter, (StringHash, float), void), AS_CALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, int value) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, int)", AS_METHODPR(Graphics, SetShaderParameter, (StringHash, int), void), AS_CALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, bool value) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, bool)", AS_METHODPR(Graphics, SetShaderParameter, (StringHash, bool), void), AS_CALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Color& color) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Color&in)", AS_METHODPR(Graphics, SetShaderParameter, (StringHash, const Color&), void), AS_CALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Vector2& vector) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Vector2&in)", AS_METHODPR(Graphics, SetShaderParameter, (StringHash, const Vector2&), void), AS_CALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Matrix3& matrix) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Matrix3&in)", AS_METHODPR(Graphics, SetShaderParameter, (StringHash, const Matrix3&), void), AS_CALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Vector3& vector) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Vector3&in)", AS_METHODPR(Graphics, SetShaderParameter, (StringHash, const Vector3&), void), AS_CALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Matrix4& matrix) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Matrix4&in)", AS_METHODPR(Graphics, SetShaderParameter, (StringHash, const Matrix4&), void), AS_CALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Vector4& vector) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Vector4&in)", AS_METHODPR(Graphics, SetShaderParameter, (StringHash, const Vector4&), void), AS_CALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Matrix3x4& matrix) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Matrix3x4&in)", AS_METHODPR(Graphics, SetShaderParameter, (StringHash, const Matrix3x4&), void), AS_CALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Variant& value) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Variant&in)", AS_METHODPR(Graphics, SetShaderParameter, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Graphics::SetShaders(ShaderVariation* vs, ShaderVariation* ps) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaders(ShaderVariation@+, ShaderVariation@+)", AS_METHODPR(Graphics, SetShaders, (ShaderVariation*, ShaderVariation*), void), AS_CALL_THISCALL);
    // void Graphics::SetSRGB(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetSRGB(bool)", AS_METHODPR(Graphics, SetSRGB, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_sRGB(bool)", AS_METHODPR(Graphics, SetSRGB, (bool), void), AS_CALL_THISCALL);
    // void Graphics::SetStencilTest(bool enable, CompareMode mode=CMP_ALWAYS, StencilOp pass=OP_KEEP, StencilOp fail=OP_KEEP, StencilOp zFail=OP_KEEP, unsigned stencilRef=0, unsigned compareMask=M_MAX_UNSIGNED, unsigned writeMask=M_MAX_UNSIGNED) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetStencilTest(bool, CompareMode = CMP_ALWAYS, StencilOp = OP_KEEP, StencilOp = OP_KEEP, StencilOp = OP_KEEP, uint = 0, uint = M_MAX_UNSIGNED, uint = M_MAX_UNSIGNED)", AS_METHODPR(Graphics, SetStencilTest, (bool, CompareMode, StencilOp, StencilOp, StencilOp, unsigned, unsigned, unsigned), void), AS_CALL_THISCALL);
    // void Graphics::SetTexture(unsigned index, Texture* texture) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetTexture(uint, Texture@+)", AS_METHODPR(Graphics, SetTexture, (unsigned, Texture*), void), AS_CALL_THISCALL);
    // void Graphics::SetTextureForUpdate(Texture* texture) | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Graphics::SetTextureParametersDirty() | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Graphics::SetUBO(unsigned object) | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Graphics::SetVBO(unsigned object) | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Graphics::SetVertexBuffer(VertexBuffer* buffer) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetVertexBuffer(VertexBuffer@+)", AS_METHODPR(Graphics, SetVertexBuffer, (VertexBuffer*), void), AS_CALL_THISCALL);
    // bool Graphics::SetVertexBuffers(const PODVector<VertexBuffer*>& buffers, unsigned instanceOffset=0) | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // bool Graphics::SetVertexBuffers(const Vector<SharedPtr<VertexBuffer>>& buffers, unsigned instanceOffset=0) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetVertexBuffers(Array<VertexBuffer@>@+, uint = 0)", AS_FUNCTION_OBJFIRST(Graphics_SetVertexBuffers_VectorSharedPtrVertexBuffer_unsigned), AS_CALL_CDECL_OBJFIRST);
    // void Graphics::SetViewport(const IntRect& rect) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetViewport(const IntRect&in)", AS_METHODPR(Graphics, SetViewport, (const IntRect&), void), AS_CALL_THISCALL);
    // void Graphics::SetWindowIcon(Image* windowIcon) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetWindowIcon(Image@+)", AS_METHODPR(Graphics, SetWindowIcon, (Image*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_windowIcon(Image@+)", AS_METHODPR(Graphics, SetWindowIcon, (Image*), void), AS_CALL_THISCALL);
    // bool Graphics::SetWindowModes(const WindowModeParams& windowMode, const WindowModeParams& secondaryWindowMode, bool maximize=false) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetWindowModes(const WindowModeParams&in, const WindowModeParams&in, bool = false)", AS_METHODPR(Graphics, SetWindowModes, (const WindowModeParams&, const WindowModeParams&, bool), bool), AS_CALL_THISCALL);
    // void Graphics::SetWindowPosition(const IntVector2& position) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetWindowPosition(const IntVector2&in)", AS_METHODPR(Graphics, SetWindowPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_windowPosition(const IntVector2&in)", AS_METHODPR(Graphics, SetWindowPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Graphics::SetWindowPosition(int x, int y) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetWindowPosition(int, int)", AS_METHODPR(Graphics, SetWindowPosition, (int, int), void), AS_CALL_THISCALL);
    // void Graphics::SetWindowTitle(const String& windowTitle) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetWindowTitle(const String&in)", AS_METHODPR(Graphics, SetWindowTitle, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_windowTitle(const String&in)", AS_METHODPR(Graphics, SetWindowTitle, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // bool Graphics::TakeScreenShot(Image& destImage) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool TakeScreenShot(Image&)", AS_METHODPR(Graphics, TakeScreenShot, (Image&), bool), AS_CALL_THISCALL);
    // bool Graphics::ToggleFullscreen() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool ToggleFullscreen()", AS_METHODPR(Graphics, ToggleFullscreen, (), bool), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void UnsubscribeFromAllEvents()", AS_METHODPR(Graphics, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Graphics_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Graphics, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Graphics, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Graphics, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Graphics", "int WeakRefs() const", AS_METHODPR(Graphics, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_weakRefs() const", AS_METHODPR(Graphics, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Graphics, "Graphics")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Graphics, "Graphics")
#endif
#ifdef REGISTER_MANUAL_PART_Graphics
    REGISTER_MANUAL_PART_Graphics(Graphics, "Graphics")
#endif
    RegisterSubclass<Object, Graphics>(engine, "Object", "Graphics");
    RegisterSubclass<RefCounted, Graphics>(engine, "RefCounted", "Graphics");

#ifdef URHO3D_PHYSICS
    // UniquePtr<TriangleMeshInterface> GImpactMeshData::meshInterface_ | File: ../Physics/CollisionShape.h
    // Error: type "UniquePtr<TriangleMeshInterface>" can not automatically bind
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("GImpactMeshData", asBEHAVE_ADDREF, "void f()", AS_METHODPR(GImpactMeshData, AddRef, (), void), AS_CALL_THISCALL);
    // GImpactMeshData::GImpactMeshData(Model* model, unsigned lodLevel) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("GImpactMeshData", asBEHAVE_FACTORY, "GImpactMeshData@+ f(Model@+, uint)", AS_FUNCTION(GImpactMeshData_GImpactMeshData_Model_unsigned), AS_CALL_CDECL);
    // explicit GImpactMeshData::GImpactMeshData(CustomGeometry* custom) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("GImpactMeshData", asBEHAVE_FACTORY, "GImpactMeshData@+ f(CustomGeometry@+)", AS_FUNCTION(GImpactMeshData_GImpactMeshData_CustomGeometry), AS_CALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("GImpactMeshData", "int Refs() const", AS_METHODPR(GImpactMeshData, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("GImpactMeshData", "int get_refs() const", AS_METHODPR(GImpactMeshData, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("GImpactMeshData", asBEHAVE_RELEASE, "void f()", AS_METHODPR(GImpactMeshData, ReleaseRef, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("GImpactMeshData", "int WeakRefs() const", AS_METHODPR(GImpactMeshData, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("GImpactMeshData", "int get_weakRefs() const", AS_METHODPR(GImpactMeshData, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_CollisionGeometryData
    REGISTER_MANUAL_PART_CollisionGeometryData(GImpactMeshData, "GImpactMeshData")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(GImpactMeshData, "GImpactMeshData")
#endif
#ifdef REGISTER_MANUAL_PART_GImpactMeshData
    REGISTER_MANUAL_PART_GImpactMeshData(GImpactMeshData, "GImpactMeshData")
#endif
    RegisterSubclass<CollisionGeometryData, GImpactMeshData>(engine, "CollisionGeometryData", "GImpactMeshData");
    RegisterSubclass<RefCounted, GImpactMeshData>(engine, "RefCounted", "GImpactMeshData");
#endif

    // unsigned GeometryDesc::ibRef_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("GeometryDesc", "uint ibRef", offsetof(GeometryDesc, ibRef_));
    // unsigned GeometryDesc::indexCount_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("GeometryDesc", "uint indexCount", offsetof(GeometryDesc, indexCount_));
    // unsigned GeometryDesc::indexStart_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("GeometryDesc", "uint indexStart", offsetof(GeometryDesc, indexStart_));
    // PrimitiveType GeometryDesc::type_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("GeometryDesc", "PrimitiveType type", offsetof(GeometryDesc, type_));
    // unsigned GeometryDesc::vbRef_ | File: ../Graphics/Model.h
    engine->RegisterObjectProperty("GeometryDesc", "uint vbRef", offsetof(GeometryDesc, vbRef_));
    // GeometryDesc& GeometryDesc::operator=(const GeometryDesc&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<GeometryDesc>(engine, "GeometryDesc");
#ifdef REGISTER_MANUAL_PART_GeometryDesc
    REGISTER_MANUAL_PART_GeometryDesc(GeometryDesc, "GeometryDesc")
#endif

}

}
