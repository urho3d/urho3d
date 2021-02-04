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
    engine->RegisterObjectMethod("GPUObject", "void ClearDataLost()", asMETHODPR(GPUObject, ClearDataLost, (), void), asCALL_THISCALL);
    // void* GPUObject::GetGPUObject() const | File: ../Graphics/GPUObject.h
    // Error: type "void*" can not automatically bind
    // unsigned GPUObject::GetGPUObjectName() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "uint GetGPUObjectName() const", asMETHODPR(GPUObject, GetGPUObjectName, () const, unsigned), asCALL_THISCALL);
    // Graphics* GPUObject::GetGraphics() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "Graphics@+ GetGraphics() const", asMETHODPR(GPUObject, GetGraphics, () const, Graphics*), asCALL_THISCALL);
    // explicit GPUObject::GPUObject(Graphics* graphics) | File: ../Graphics/GPUObject.h
    engine->RegisterObjectBehaviour("GPUObject", asBEHAVE_CONSTRUCT, "void f(Graphics@+)", asFUNCTION(GPUObject_GPUObject_Graphics), asCALL_CDECL_OBJFIRST);
    // bool GPUObject::HasPendingData() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "bool HasPendingData() const", asMETHODPR(GPUObject, HasPendingData, () const, bool), asCALL_THISCALL);
    // bool GPUObject::IsDataLost() const | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "bool IsDataLost() const", asMETHODPR(GPUObject, IsDataLost, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("GPUObject", "bool get_dataLost() const", asMETHODPR(GPUObject, IsDataLost, () const, bool), asCALL_THISCALL);
    // virtual void GPUObject::OnDeviceLost() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "void OnDeviceLost()", asMETHODPR(GPUObject, OnDeviceLost, (), void), asCALL_THISCALL);
    // virtual void GPUObject::OnDeviceReset() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "void OnDeviceReset()", asMETHODPR(GPUObject, OnDeviceReset, (), void), asCALL_THISCALL);
    // virtual void GPUObject::Release() | File: ../Graphics/GPUObject.h
    engine->RegisterObjectMethod("GPUObject", "void Release()", asMETHODPR(GPUObject, Release, (), void), asCALL_THISCALL);
    // GPUObject& GPUObject::operator=(const GPUObject&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<GPUObject>(engine, "GPUObject");
#ifdef REGISTER_MANUAL_PART_GPUObject
    REGISTER_MANUAL_PART_GPUObject(GPUObject, "GPUObject")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Geometry", asBEHAVE_ADDREF, "void f()", asMETHODPR(Geometry, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Geometry::Draw(Graphics* graphics) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "void Draw(Graphics@+)", asMETHODPR(Geometry, Draw, (Graphics*), void), asCALL_THISCALL);
    // explicit Geometry::Geometry(Context* context) | File: ../Graphics/Geometry.h
    engine->RegisterObjectBehaviour("Geometry", asBEHAVE_FACTORY, "Geometry@+ f()", asFUNCTION(Geometry_Geometry_Context), asCALL_CDECL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "bool GetBlockEvents() const", asMETHODPR(Geometry, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // unsigned short Geometry::GetBufferHash() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "uint16 GetBufferHash() const", asMETHODPR(Geometry, GetBufferHash, () const, unsigned short), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "const String& GetCategory() const", asMETHODPR(Geometry, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "const String& get_category() const", asMETHODPR(Geometry, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "VariantMap& GetEventDataMap() const", asMETHODPR(Geometry, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "Object@+ GetEventSender() const", asMETHODPR(Geometry, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Geometry, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Geometry, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "const VariantMap& GetGlobalVars() const", asMETHODPR(Geometry, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "const VariantMap& get_globalVars() const", asMETHODPR(Geometry, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // float Geometry::GetHitDistance(const Ray& ray, Vector3* outNormal=nullptr, Vector2* outUV=nullptr) const | File: ../Graphics/Geometry.h
    // Error: type "Vector3*" can not automatically bind
    // IndexBuffer* Geometry::GetIndexBuffer() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "IndexBuffer@+ GetIndexBuffer() const", asMETHODPR(Geometry, GetIndexBuffer, () const, IndexBuffer*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "IndexBuffer@+ get_indexBuffer() const", asMETHODPR(Geometry, GetIndexBuffer, () const, IndexBuffer*), asCALL_THISCALL);
    // unsigned Geometry::GetIndexCount() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "uint GetIndexCount() const", asMETHODPR(Geometry, GetIndexCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "uint get_indexCount() const", asMETHODPR(Geometry, GetIndexCount, () const, unsigned), asCALL_THISCALL);
    // unsigned Geometry::GetIndexStart() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "uint GetIndexStart() const", asMETHODPR(Geometry, GetIndexStart, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "uint get_indexStart() const", asMETHODPR(Geometry, GetIndexStart, () const, unsigned), asCALL_THISCALL);
    // float Geometry::GetLodDistance() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "float GetLodDistance() const", asMETHODPR(Geometry, GetLodDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "float get_lodDistance() const", asMETHODPR(Geometry, GetLodDistance, () const, float), asCALL_THISCALL);
    // unsigned Geometry::GetNumVertexBuffers() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "uint GetNumVertexBuffers() const", asMETHODPR(Geometry, GetNumVertexBuffers, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "uint get_numVertexBuffers() const", asMETHODPR(Geometry, GetNumVertexBuffers, () const, unsigned), asCALL_THISCALL);
    // PrimitiveType Geometry::GetPrimitiveType() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "PrimitiveType GetPrimitiveType() const", asMETHODPR(Geometry, GetPrimitiveType, () const, PrimitiveType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "PrimitiveType get_primitiveType() const", asMETHODPR(Geometry, GetPrimitiveType, () const, PrimitiveType), asCALL_THISCALL);
    // void Geometry::GetRawData(const unsigned char*& vertexData, unsigned& vertexSize, const unsigned char*& indexData, unsigned& indexSize, const PODVector<VertexElement>*& elements) const | File: ../Graphics/Geometry.h
    // Error: type "const unsigned char*&" can not automatically bind
    // void Geometry::GetRawDataShared(SharedArrayPtr<unsigned char>& vertexData, unsigned& vertexSize, SharedArrayPtr<unsigned char>& indexData, unsigned& indexSize, const PODVector<VertexElement>*& elements) const | File: ../Graphics/Geometry.h
    // Error: type "SharedArrayPtr<unsigned char>&" can not automatically bind
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Geometry, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "StringHash GetType() const", asMETHODPR(Geometry, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "StringHash get_type() const", asMETHODPR(Geometry, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "const String& GetTypeName() const", asMETHODPR(Geometry, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "const String& get_typeName() const", asMETHODPR(Geometry, GetTypeName, () const, const String&), asCALL_THISCALL);
    // VertexBuffer* Geometry::GetVertexBuffer(unsigned index) const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "VertexBuffer@+ GetVertexBuffer(uint) const", asMETHODPR(Geometry, GetVertexBuffer, (unsigned) const, VertexBuffer*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "VertexBuffer@+ get_vertexBuffers(uint) const", asMETHODPR(Geometry, GetVertexBuffer, (unsigned) const, VertexBuffer*), asCALL_THISCALL);
    // const Vector<SharedPtr<VertexBuffer>>& Geometry::GetVertexBuffers() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "Array<VertexBuffer@>@ GetVertexBuffers() const", asFUNCTION(Geometry_GetVertexBuffers_void), asCALL_CDECL_OBJFIRST);
    // unsigned Geometry::GetVertexCount() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "uint GetVertexCount() const", asMETHODPR(Geometry, GetVertexCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "uint get_vertexCount() const", asMETHODPR(Geometry, GetVertexCount, () const, unsigned), asCALL_THISCALL);
    // unsigned Geometry::GetVertexStart() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "uint GetVertexStart() const", asMETHODPR(Geometry, GetVertexStart, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "uint get_vertexStart() const", asMETHODPR(Geometry, GetVertexStart, () const, unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "bool HasEventHandlers() const", asMETHODPR(Geometry, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Geometry, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Geometry, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Geometry::IsEmpty() const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "bool IsEmpty() const", asMETHODPR(Geometry, IsEmpty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "bool get_empty() const", asMETHODPR(Geometry, IsEmpty, () const, bool), asCALL_THISCALL);
    // bool Geometry::IsInside(const Ray& ray) const | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "bool IsInside(const Ray&in) const", asMETHODPR(Geometry, IsInside, (const Ray&) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "bool IsInstanceOf(StringHash) const", asMETHODPR(Geometry, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Geometry, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Geometry", "int Refs() const", asMETHODPR(Geometry, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "int get_refs() const", asMETHODPR(Geometry, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Geometry", asBEHAVE_RELEASE, "void f()", asMETHODPR(Geometry, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void SendEvent(StringHash)", asMETHODPR(Geometry, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Geometry, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void SetBlockEvents(bool)", asMETHODPR(Geometry, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // bool Geometry::SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, bool getUsedVertexRange=true) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "bool SetDrawRange(PrimitiveType, uint, uint, bool = true)", asMETHODPR(Geometry, SetDrawRange, (PrimitiveType, unsigned, unsigned, bool), bool), asCALL_THISCALL);
    // bool Geometry::SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned vertexStart, unsigned vertexCount, bool checkIllegal=true) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "bool SetDrawRange(PrimitiveType, uint, uint, uint, uint, bool = true)", asMETHODPR(Geometry, SetDrawRange, (PrimitiveType, unsigned, unsigned, unsigned, unsigned, bool), bool), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Geometry, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Geometry, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Geometry::SetIndexBuffer(IndexBuffer* buffer) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "void SetIndexBuffer(IndexBuffer@+)", asMETHODPR(Geometry, SetIndexBuffer, (IndexBuffer*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "void set_indexBuffer(IndexBuffer@+)", asMETHODPR(Geometry, SetIndexBuffer, (IndexBuffer*), void), asCALL_THISCALL);
    // void Geometry::SetLodDistance(float distance) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "void SetLodDistance(float)", asMETHODPR(Geometry, SetLodDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "void set_lodDistance(float)", asMETHODPR(Geometry, SetLodDistance, (float), void), asCALL_THISCALL);
    // bool Geometry::SetNumVertexBuffers(unsigned num) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "bool SetNumVertexBuffers(uint)", asMETHODPR(Geometry, SetNumVertexBuffers, (unsigned), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "bool set_numVertexBuffers(uint)", asMETHODPR(Geometry, SetNumVertexBuffers, (unsigned), bool), asCALL_THISCALL);
    // void Geometry::SetRawIndexData(const SharedArrayPtr<unsigned char>& data, unsigned indexSize) | File: ../Graphics/Geometry.h
    // Error: type "const SharedArrayPtr<unsigned char>&" can not automatically bind
    // void Geometry::SetRawVertexData(const SharedArrayPtr<unsigned char>& data, const PODVector<VertexElement>& elements) | File: ../Graphics/Geometry.h
    // Error: type "const SharedArrayPtr<unsigned char>&" can not automatically bind
    // void Geometry::SetRawVertexData(const SharedArrayPtr<unsigned char>& data, unsigned elementMask) | File: ../Graphics/Geometry.h
    // Error: type "const SharedArrayPtr<unsigned char>&" can not automatically bind
    // bool Geometry::SetVertexBuffer(unsigned index, VertexBuffer* buffer) | File: ../Graphics/Geometry.h
    engine->RegisterObjectMethod("Geometry", "bool SetVertexBuffer(uint, VertexBuffer@+)", asMETHODPR(Geometry, SetVertexBuffer, (unsigned, VertexBuffer*), bool), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void UnsubscribeFromAllEvents()", asMETHODPR(Geometry, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Geometry_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Geometry, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Geometry, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Geometry", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Geometry, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Geometry", "int WeakRefs() const", asMETHODPR(Geometry, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Geometry", "int get_weakRefs() const", asMETHODPR(Geometry, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Graphics", asBEHAVE_ADDREF, "void f()", asMETHODPR(Graphics, AddRef, (), void), asCALL_THISCALL);
    // void Graphics::BeginDumpShaders(const String& fileName) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void BeginDumpShaders(const String&in)", asMETHODPR(Graphics, BeginDumpShaders, (const String&), void), asCALL_THISCALL);
    // bool Graphics::BeginFrame() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool BeginFrame()", asMETHODPR(Graphics, BeginFrame, (), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Graphics::CleanupRenderSurface(RenderSurface* surface) | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Graphics::CleanupScratchBuffers() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void CleanupScratchBuffers()", asMETHODPR(Graphics, CleanupScratchBuffers, (), void), asCALL_THISCALL);
    // void Graphics::CleanupShaderPrograms(ShaderVariation* variation) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void CleanupShaderPrograms(ShaderVariation@+)", asMETHODPR(Graphics, CleanupShaderPrograms, (ShaderVariation*), void), asCALL_THISCALL);
    // void Graphics::Clear(ClearTargetFlags flags, const Color& color=Color(0.0f, 0.0f, 0.0f, 0.0f), float depth=1.0f, unsigned stencil=0) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Clear(ClearTargetFlags, const Color&in = Color(0.0f, 0.0f, 0.0f, 0.0f), float = 1.0f, uint = 0)", asMETHODPR(Graphics, Clear, (ClearTargetFlags, const Color&, float, unsigned), void), asCALL_THISCALL);
    // void Graphics::ClearParameterSource(ShaderParameterGroup group) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void ClearParameterSource(ShaderParameterGroup)", asMETHODPR(Graphics, ClearParameterSource, (ShaderParameterGroup), void), asCALL_THISCALL);
    // void Graphics::ClearParameterSources() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void ClearParameterSources()", asMETHODPR(Graphics, ClearParameterSources, (), void), asCALL_THISCALL);
    // void Graphics::ClearTransformSources() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void ClearTransformSources()", asMETHODPR(Graphics, ClearTransformSources, (), void), asCALL_THISCALL);
    // void Graphics::Close() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Close()", asMETHODPR(Graphics, Close, (), void), asCALL_THISCALL);
    // void Graphics::Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Draw(PrimitiveType, uint, uint)", asMETHODPR(Graphics, Draw, (PrimitiveType, unsigned, unsigned), void), asCALL_THISCALL);
    // void Graphics::Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Draw(PrimitiveType, uint, uint, uint, uint)", asMETHODPR(Graphics, Draw, (PrimitiveType, unsigned, unsigned, unsigned, unsigned), void), asCALL_THISCALL);
    // void Graphics::Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned baseVertexIndex, unsigned minVertex, unsigned vertexCount) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Draw(PrimitiveType, uint, uint, uint, uint, uint)", asMETHODPR(Graphics, Draw, (PrimitiveType, unsigned, unsigned, unsigned, unsigned, unsigned), void), asCALL_THISCALL);
    // void Graphics::DrawInstanced(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount, unsigned instanceCount) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void DrawInstanced(PrimitiveType, uint, uint, uint, uint, uint)", asMETHODPR(Graphics, DrawInstanced, (PrimitiveType, unsigned, unsigned, unsigned, unsigned, unsigned), void), asCALL_THISCALL);
    // void Graphics::DrawInstanced(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned baseVertexIndex, unsigned minVertex, unsigned vertexCount, unsigned instanceCount) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void DrawInstanced(PrimitiveType, uint, uint, uint, uint, uint, uint)", asMETHODPR(Graphics, DrawInstanced, (PrimitiveType, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned), void), asCALL_THISCALL);
    // void Graphics::EndDumpShaders() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void EndDumpShaders()", asMETHODPR(Graphics, EndDumpShaders, (), void), asCALL_THISCALL);
    // void Graphics::EndFrame() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void EndFrame()", asMETHODPR(Graphics, EndFrame, (), void), asCALL_THISCALL);
    // unsigned Graphics::FindBestResolutionIndex(int monitor, int width, int height, int refreshRate) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint FindBestResolutionIndex(int, int, int, int) const", asMETHODPR(Graphics, FindBestResolutionIndex, (int, int, int, int) const, unsigned), asCALL_THISCALL);
    // void Graphics::FreeScratchBuffer(void* buffer) | File: ../Graphics/Graphics.h
    // Error: type "void*" can not automatically bind
    // static unsigned Graphics::GetAlphaFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetAlphaFormat()", asFUNCTIONPR(Graphics::GetAlphaFormat, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Graphics::GetAlphaToCoverage() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetAlphaToCoverage() const", asMETHODPR(Graphics, GetAlphaToCoverage, () const, bool), asCALL_THISCALL);
    // bool Graphics::GetAnisotropySupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetAnisotropySupport() const", asMETHODPR(Graphics, GetAnisotropySupport, () const, bool), asCALL_THISCALL);
    // const String& Graphics::GetApiName() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const String& GetApiName() const", asMETHODPR(Graphics, GetApiName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_apiName() const", asMETHODPR(Graphics, GetApiName, () const, const String&), asCALL_THISCALL);
    // BlendMode Graphics::GetBlendMode() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "BlendMode GetBlendMode() const", asMETHODPR(Graphics, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "bool GetBlockEvents() const", asMETHODPR(Graphics, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // bool Graphics::GetBorderless() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetBorderless() const", asMETHODPR(Graphics, GetBorderless, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_borderless() const", asMETHODPR(Graphics, GetBorderless, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "const String& GetCategory() const", asMETHODPR(Graphics, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_category() const", asMETHODPR(Graphics, GetCategory, () const, const String&), asCALL_THISCALL);
    // bool Graphics::GetColorWrite() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetColorWrite() const", asMETHODPR(Graphics, GetColorWrite, () const, bool), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // CullMode Graphics::GetCullMode() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "CullMode GetCullMode() const", asMETHODPR(Graphics, GetCullMode, () const, CullMode), asCALL_THISCALL);
    // int Graphics::GetCurrentMonitor() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetCurrentMonitor() const", asMETHODPR(Graphics, GetCurrentMonitor, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_currentMonitor() const", asMETHODPR(Graphics, GetCurrentMonitor, () const, int), asCALL_THISCALL);
    // unsigned Graphics::GetDefaultTextureAnisotropy() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetDefaultTextureAnisotropy() const", asMETHODPR(Graphics, GetDefaultTextureAnisotropy, () const, unsigned), asCALL_THISCALL);
    // TextureFilterMode Graphics::GetDefaultTextureFilterMode() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "TextureFilterMode GetDefaultTextureFilterMode() const", asMETHODPR(Graphics, GetDefaultTextureFilterMode, () const, TextureFilterMode), asCALL_THISCALL);
    // bool Graphics::GetDeferredSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetDeferredSupport() const", asMETHODPR(Graphics, GetDeferredSupport, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_deferredSupport() const", asMETHODPR(Graphics, GetDeferredSupport, () const, bool), asCALL_THISCALL);
    // float Graphics::GetDepthConstantBias() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "float GetDepthConstantBias() const", asMETHODPR(Graphics, GetDepthConstantBias, () const, float), asCALL_THISCALL);
    // float Graphics::GetDepthSlopeScaledBias() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "float GetDepthSlopeScaledBias() const", asMETHODPR(Graphics, GetDepthSlopeScaledBias, () const, float), asCALL_THISCALL);
    // RenderSurface* Graphics::GetDepthStencil() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "RenderSurface@+ GetDepthStencil() const", asMETHODPR(Graphics, GetDepthStencil, () const, RenderSurface*), asCALL_THISCALL);
    // static unsigned Graphics::GetDepthStencilFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetDepthStencilFormat()", asFUNCTIONPR(Graphics::GetDepthStencilFormat, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // CompareMode Graphics::GetDepthTest() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "CompareMode GetDepthTest() const", asMETHODPR(Graphics, GetDepthTest, () const, CompareMode), asCALL_THISCALL);
    // bool Graphics::GetDepthWrite() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetDepthWrite() const", asMETHODPR(Graphics, GetDepthWrite, () const, bool), asCALL_THISCALL);
    // IntVector2 Graphics::GetDesktopResolution(int monitor) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "IntVector2 GetDesktopResolution(int) const", asMETHODPR(Graphics, GetDesktopResolution, (int) const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "IntVector2 get_desktopResolution(int) const", asMETHODPR(Graphics, GetDesktopResolution, (int) const, IntVector2), asCALL_THISCALL);
    // Vector3 Graphics::GetDisplayDPI(int monitor=0) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "Vector3 GetDisplayDPI(int = 0) const", asMETHODPR(Graphics, GetDisplayDPI, (int) const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "Vector3 get_displayDPI(int = 0) const", asMETHODPR(Graphics, GetDisplayDPI, (int) const, Vector3), asCALL_THISCALL);
    // bool Graphics::GetDither() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetDither() const", asMETHODPR(Graphics, GetDither, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_dither() const", asMETHODPR(Graphics, GetDither, () const, bool), asCALL_THISCALL);
    // unsigned Graphics::GetDummyColorFormat() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetDummyColorFormat() const", asMETHODPR(Graphics, GetDummyColorFormat, () const, unsigned), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "VariantMap& GetEventDataMap() const", asMETHODPR(Graphics, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "Object@+ GetEventSender() const", asMETHODPR(Graphics, GetEventSender, () const, Object*), asCALL_THISCALL);
    // void* Graphics::GetExternalWindow() const | File: ../Graphics/Graphics.h
    // Error: type "void*" can not automatically bind
    // FillMode Graphics::GetFillMode() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "FillMode GetFillMode() const", asMETHODPR(Graphics, GetFillMode, () const, FillMode), asCALL_THISCALL);
    // static unsigned Graphics::GetFloat16Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetFloat16Format()", asFUNCTIONPR(Graphics::GetFloat16Format, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetFloat32Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetFloat32Format()", asFUNCTIONPR(Graphics::GetFloat32Format, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Graphics::GetFlushGPU() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetFlushGPU() const", asMETHODPR(Graphics, GetFlushGPU, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_flushGPU() const", asMETHODPR(Graphics, GetFlushGPU, () const, bool), asCALL_THISCALL);
    // bool Graphics::GetForceGL2() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetForceGL2() const", asMETHODPR(Graphics, GetForceGL2, () const, bool), asCALL_THISCALL);
    // unsigned Graphics::GetFormat(CompressedFormat format) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetFormat(CompressedFormat) const", asMETHODPR(Graphics, GetFormat, (CompressedFormat) const, unsigned), asCALL_THISCALL);
    // static unsigned Graphics::GetFormat(const String& formatName) | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetFormat(const String&in)", asFUNCTIONPR(Graphics::GetFormat, (const String&), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Graphics::GetFullscreen() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetFullscreen() const", asMETHODPR(Graphics, GetFullscreen, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_fullscreen() const", asMETHODPR(Graphics, GetFullscreen, () const, bool), asCALL_THISCALL);
    // static bool Graphics::GetGL3Support() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("bool GetGL3Support()", asFUNCTIONPR(Graphics::GetGL3Support, (), bool), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Graphics, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Graphics, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "const VariantMap& GetGlobalVars() const", asMETHODPR(Graphics, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const VariantMap& get_globalVars() const", asMETHODPR(Graphics, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // bool Graphics::GetHardwareShadowSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetHardwareShadowSupport() const", asMETHODPR(Graphics, GetHardwareShadowSupport, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_hardwareShadowSupport() const", asMETHODPR(Graphics, GetHardwareShadowSupport, () const, bool), asCALL_THISCALL);
    // int Graphics::GetHeight() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetHeight() const", asMETHODPR(Graphics, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_height() const", asMETHODPR(Graphics, GetHeight, () const, int), asCALL_THISCALL);
    // bool Graphics::GetHighDPI() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetHighDPI() const", asMETHODPR(Graphics, GetHighDPI, () const, bool), asCALL_THISCALL);
    // unsigned Graphics::GetHiresShadowMapFormat() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetHiresShadowMapFormat() const", asMETHODPR(Graphics, GetHiresShadowMapFormat, () const, unsigned), asCALL_THISCALL);
    // GraphicsImpl* Graphics::GetImpl() const | File: ../Graphics/Graphics.h
    // Error: type "GraphicsImpl*" can not automatically bind
    // IndexBuffer* Graphics::GetIndexBuffer() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "IndexBuffer@+ GetIndexBuffer() const", asMETHODPR(Graphics, GetIndexBuffer, () const, IndexBuffer*), asCALL_THISCALL);
    // bool Graphics::GetInstancingSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetInstancingSupport() const", asMETHODPR(Graphics, GetInstancingSupport, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_instancingSupport() const", asMETHODPR(Graphics, GetInstancingSupport, () const, bool), asCALL_THISCALL);
    // bool Graphics::GetLightPrepassSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetLightPrepassSupport() const", asMETHODPR(Graphics, GetLightPrepassSupport, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_lightPrepassSupport() const", asMETHODPR(Graphics, GetLightPrepassSupport, () const, bool), asCALL_THISCALL);
    // bool Graphics::GetLineAntiAlias() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetLineAntiAlias() const", asMETHODPR(Graphics, GetLineAntiAlias, () const, bool), asCALL_THISCALL);
    // static unsigned Graphics::GetLinearDepthFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetLinearDepthFormat()", asFUNCTIONPR(Graphics::GetLinearDepthFormat, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetLuminanceAlphaFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetLuminanceAlphaFormat()", asFUNCTIONPR(Graphics::GetLuminanceAlphaFormat, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetLuminanceFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetLuminanceFormat()", asFUNCTIONPR(Graphics::GetLuminanceFormat, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetMaxBones() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetMaxBones()", asFUNCTIONPR(Graphics::GetMaxBones, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Graphics::GetMaximized() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetMaximized() const", asMETHODPR(Graphics, GetMaximized, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_maximized() const", asMETHODPR(Graphics, GetMaximized, () const, bool), asCALL_THISCALL);
    // int Graphics::GetMonitor() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetMonitor() const", asMETHODPR(Graphics, GetMonitor, () const, int), asCALL_THISCALL);
    // int Graphics::GetMonitorCount() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetMonitorCount() const", asMETHODPR(Graphics, GetMonitorCount, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_monitorCount() const", asMETHODPR(Graphics, GetMonitorCount, () const, int), asCALL_THISCALL);
    // int Graphics::GetMultiSample() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetMultiSample() const", asMETHODPR(Graphics, GetMultiSample, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_multiSample() const", asMETHODPR(Graphics, GetMultiSample, () const, int), asCALL_THISCALL);
    // PODVector<int> Graphics::GetMultiSampleLevels() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "Array<int>@ GetMultiSampleLevels() const", asFUNCTION(Graphics_GetMultiSampleLevels_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Graphics", "Array<int>@ get_multiSampleLevels() const", asFUNCTION(Graphics_GetMultiSampleLevels_void), asCALL_CDECL_OBJFIRST);
    // unsigned Graphics::GetNumBatches() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetNumBatches() const", asMETHODPR(Graphics, GetNumBatches, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "uint get_numBatches() const", asMETHODPR(Graphics, GetNumBatches, () const, unsigned), asCALL_THISCALL);
    // unsigned Graphics::GetNumPrimitives() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetNumPrimitives() const", asMETHODPR(Graphics, GetNumPrimitives, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "uint get_numPrimitives() const", asMETHODPR(Graphics, GetNumPrimitives, () const, unsigned), asCALL_THISCALL);
    // ConstantBuffer* Graphics::GetOrCreateConstantBuffer(ShaderType type, unsigned index, unsigned size) | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // const String& Graphics::GetOrientations() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const String& GetOrientations() const", asMETHODPR(Graphics, GetOrientations, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_orientations() const", asMETHODPR(Graphics, GetOrientations, () const, const String&), asCALL_THISCALL);
    // ShaderVariation* Graphics::GetPixelShader() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "ShaderVariation@+ GetPixelShader() const", asMETHODPR(Graphics, GetPixelShader, () const, ShaderVariation*), asCALL_THISCALL);
    // static const Vector2& Graphics::GetPixelUVOffset() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("const Vector2& GetPixelUVOffset()", asFUNCTIONPR(Graphics::GetPixelUVOffset, (), const Vector2&), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetReadableDepthFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetReadableDepthFormat()", asFUNCTIONPR(Graphics::GetReadableDepthFormat, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Graphics::GetReadableDepthSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetReadableDepthSupport() const", asMETHODPR(Graphics, GetReadableDepthSupport, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_readableDepthSupport() const", asMETHODPR(Graphics, GetReadableDepthSupport, () const, bool), asCALL_THISCALL);
    // int Graphics::GetRefreshRate() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetRefreshRate() const", asMETHODPR(Graphics, GetRefreshRate, () const, int), asCALL_THISCALL);
    // RenderSurface* Graphics::GetRenderTarget(unsigned index) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "RenderSurface@+ GetRenderTarget(uint) const", asMETHODPR(Graphics, GetRenderTarget, (unsigned) const, RenderSurface*), asCALL_THISCALL);
    // IntVector2 Graphics::GetRenderTargetDimensions() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "IntVector2 GetRenderTargetDimensions() const", asMETHODPR(Graphics, GetRenderTargetDimensions, () const, IntVector2), asCALL_THISCALL);
    // bool Graphics::GetResizable() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetResizable() const", asMETHODPR(Graphics, GetResizable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_resizable() const", asMETHODPR(Graphics, GetResizable, () const, bool), asCALL_THISCALL);
    // PODVector<IntVector3> Graphics::GetResolutions(int monitor) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "Array<IntVector3>@ GetResolutions(int) const", asFUNCTION(Graphics_GetResolutions_int), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Graphics", "Array<IntVector3>@ get_resolutions(int) const", asFUNCTION(Graphics_GetResolutions_int), asCALL_CDECL_OBJFIRST);
    // static unsigned Graphics::GetRG16Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRG16Format()", asFUNCTIONPR(Graphics::GetRG16Format, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGBA16Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGBA16Format()", asFUNCTIONPR(Graphics::GetRGBA16Format, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGBAFloat16Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGBAFloat16Format()", asFUNCTIONPR(Graphics::GetRGBAFloat16Format, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGBAFloat32Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGBAFloat32Format()", asFUNCTIONPR(Graphics::GetRGBAFloat32Format, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGBAFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGBAFormat()", asFUNCTIONPR(Graphics::GetRGBAFormat, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGBFormat() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGBFormat()", asFUNCTIONPR(Graphics::GetRGBFormat, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGFloat16Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGFloat16Format()", asFUNCTIONPR(Graphics::GetRGFloat16Format, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // static unsigned Graphics::GetRGFloat32Format() | File: ../Graphics/Graphics.h
    engine->SetDefaultNamespace("Graphics");
    engine->RegisterGlobalFunction("uint GetRGFloat32Format()", asFUNCTIONPR(Graphics::GetRGFloat32Format, (), unsigned), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // const IntRect& Graphics::GetScissorRect() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const IntRect& GetScissorRect() const", asMETHODPR(Graphics, GetScissorRect, () const, const IntRect&), asCALL_THISCALL);
    // bool Graphics::GetScissorTest() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetScissorTest() const", asMETHODPR(Graphics, GetScissorTest, () const, bool), asCALL_THISCALL);
    // const ScreenModeParams& Graphics::GetScreenModeParams() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const ScreenModeParams& GetScreenModeParams() const", asMETHODPR(Graphics, GetScreenModeParams, () const, const ScreenModeParams&), asCALL_THISCALL);
    // ShaderVariation* Graphics::GetShader(ShaderType type, const String& name, const String& defines=String::EMPTY) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "ShaderVariation@+ GetShader(ShaderType, const String&in, const String&in = String::EMPTY) const", asMETHODPR(Graphics, GetShader, (ShaderType, const String&, const String&) const, ShaderVariation*), asCALL_THISCALL);
    // ShaderVariation* Graphics::GetShader(ShaderType type, const char* name, const char* defines) const | File: ../Graphics/Graphics.h
    // Error: type "const char*" can not automatically bind
    // const String& Graphics::GetShaderCacheDir() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const String& GetShaderCacheDir() const", asMETHODPR(Graphics, GetShaderCacheDir, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_shaderCacheDir() const", asMETHODPR(Graphics, GetShaderCacheDir, () const, const String&), asCALL_THISCALL);
    // ShaderProgram* Graphics::GetShaderProgram() const | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // unsigned Graphics::GetShadowMapFormat() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetShadowMapFormat() const", asMETHODPR(Graphics, GetShadowMapFormat, () const, unsigned), asCALL_THISCALL);
    // IntVector2 Graphics::GetSize() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "IntVector2 GetSize() const", asMETHODPR(Graphics, GetSize, () const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "IntVector2 get_size() const", asMETHODPR(Graphics, GetSize, () const, IntVector2), asCALL_THISCALL);
    // bool Graphics::GetSRGB() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetSRGB() const", asMETHODPR(Graphics, GetSRGB, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_sRGB() const", asMETHODPR(Graphics, GetSRGB, () const, bool), asCALL_THISCALL);
    // bool Graphics::GetSRGBSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetSRGBSupport() const", asMETHODPR(Graphics, GetSRGBSupport, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_sRGBSupport() const", asMETHODPR(Graphics, GetSRGBSupport, () const, bool), asCALL_THISCALL);
    // bool Graphics::GetSRGBWriteSupport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetSRGBWriteSupport() const", asMETHODPR(Graphics, GetSRGBWriteSupport, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_sRGBWriteSupport() const", asMETHODPR(Graphics, GetSRGBWriteSupport, () const, bool), asCALL_THISCALL);
    // unsigned Graphics::GetStencilCompareMask() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetStencilCompareMask() const", asMETHODPR(Graphics, GetStencilCompareMask, () const, unsigned), asCALL_THISCALL);
    // StencilOp Graphics::GetStencilFail() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "StencilOp GetStencilFail() const", asMETHODPR(Graphics, GetStencilFail, () const, StencilOp), asCALL_THISCALL);
    // StencilOp Graphics::GetStencilPass() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "StencilOp GetStencilPass() const", asMETHODPR(Graphics, GetStencilPass, () const, StencilOp), asCALL_THISCALL);
    // unsigned Graphics::GetStencilRef() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetStencilRef() const", asMETHODPR(Graphics, GetStencilRef, () const, unsigned), asCALL_THISCALL);
    // bool Graphics::GetStencilTest() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetStencilTest() const", asMETHODPR(Graphics, GetStencilTest, () const, bool), asCALL_THISCALL);
    // CompareMode Graphics::GetStencilTestMode() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "CompareMode GetStencilTestMode() const", asMETHODPR(Graphics, GetStencilTestMode, () const, CompareMode), asCALL_THISCALL);
    // unsigned Graphics::GetStencilWriteMask() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "uint GetStencilWriteMask() const", asMETHODPR(Graphics, GetStencilWriteMask, () const, unsigned), asCALL_THISCALL);
    // StencilOp Graphics::GetStencilZFail() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "StencilOp GetStencilZFail() const", asMETHODPR(Graphics, GetStencilZFail, () const, StencilOp), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Graphics, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Texture* Graphics::GetTexture(unsigned index) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "Texture@+ GetTexture(uint) const", asMETHODPR(Graphics, GetTexture, (unsigned) const, Texture*), asCALL_THISCALL);
    // TextureUnit Graphics::GetTextureUnit(const String& name) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "TextureUnit GetTextureUnit(const String&in)", asMETHODPR(Graphics, GetTextureUnit, (const String&), TextureUnit), asCALL_THISCALL);
    // const String& Graphics::GetTextureUnitName(TextureUnit unit) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const String& GetTextureUnitName(TextureUnit)", asMETHODPR(Graphics, GetTextureUnitName, (TextureUnit), const String&), asCALL_THISCALL);
    // bool Graphics::GetTripleBuffer() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetTripleBuffer() const", asMETHODPR(Graphics, GetTripleBuffer, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_tripleBuffer() const", asMETHODPR(Graphics, GetTripleBuffer, () const, bool), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "StringHash GetType() const", asMETHODPR(Graphics, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "StringHash get_type() const", asMETHODPR(Graphics, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "const String& GetTypeName() const", asMETHODPR(Graphics, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_typeName() const", asMETHODPR(Graphics, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Graphics::GetUseClipPlane() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetUseClipPlane() const", asMETHODPR(Graphics, GetUseClipPlane, () const, bool), asCALL_THISCALL);
    // VertexBuffer* Graphics::GetVertexBuffer(unsigned index) const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "VertexBuffer@+ GetVertexBuffer(uint) const", asMETHODPR(Graphics, GetVertexBuffer, (unsigned) const, VertexBuffer*), asCALL_THISCALL);
    // ShaderVariation* Graphics::GetVertexShader() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "ShaderVariation@+ GetVertexShader() const", asMETHODPR(Graphics, GetVertexShader, () const, ShaderVariation*), asCALL_THISCALL);
    // IntRect Graphics::GetViewport() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "IntRect GetViewport() const", asMETHODPR(Graphics, GetViewport, () const, IntRect), asCALL_THISCALL);
    // bool Graphics::GetVSync() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool GetVSync() const", asMETHODPR(Graphics, GetVSync, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_vSync() const", asMETHODPR(Graphics, GetVSync, () const, bool), asCALL_THISCALL);
    // int Graphics::GetWidth() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "int GetWidth() const", asMETHODPR(Graphics, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_width() const", asMETHODPR(Graphics, GetWidth, () const, int), asCALL_THISCALL);
    // SDL_Window* Graphics::GetWindow() const | File: ../Graphics/Graphics.h
    // Error: type "SDL_Window*" can not automatically bind
    // IntVector2 Graphics::GetWindowPosition() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "IntVector2 GetWindowPosition() const", asMETHODPR(Graphics, GetWindowPosition, () const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "IntVector2 get_windowPosition() const", asMETHODPR(Graphics, GetWindowPosition, () const, IntVector2), asCALL_THISCALL);
    // const String& Graphics::GetWindowTitle() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "const String& GetWindowTitle() const", asMETHODPR(Graphics, GetWindowTitle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "const String& get_windowTitle() const", asMETHODPR(Graphics, GetWindowTitle, () const, const String&), asCALL_THISCALL);
    // explicit Graphics::Graphics(Context* context) | File: ../Graphics/Graphics.h
    engine->RegisterObjectBehaviour("Graphics", asBEHAVE_FACTORY, "Graphics@+ f()", asFUNCTION(Graphics_Graphics_Context), asCALL_CDECL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "bool HasEventHandlers() const", asMETHODPR(Graphics, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Graphics::HasShaderParameter(StringHash param) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool HasShaderParameter(StringHash)", asMETHODPR(Graphics, HasShaderParameter, (StringHash), bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Graphics, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Graphics, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Graphics::HasTextureUnit(TextureUnit unit) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool HasTextureUnit(TextureUnit)", asMETHODPR(Graphics, HasTextureUnit, (TextureUnit), bool), asCALL_THISCALL);
    // bool Graphics::IsDeviceLost() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool IsDeviceLost() const", asMETHODPR(Graphics, IsDeviceLost, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_deviceLost() const", asMETHODPR(Graphics, IsDeviceLost, () const, bool), asCALL_THISCALL);
    // bool Graphics::IsInitialized() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool IsInitialized() const", asMETHODPR(Graphics, IsInitialized, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "bool get_initialized() const", asMETHODPR(Graphics, IsInitialized, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "bool IsInstanceOf(StringHash) const", asMETHODPR(Graphics, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // void Graphics::MarkFBODirty() | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Graphics::Maximize() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Maximize()", asMETHODPR(Graphics, Maximize, (), void), asCALL_THISCALL);
    // void Graphics::Minimize() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Minimize()", asMETHODPR(Graphics, Minimize, (), void), asCALL_THISCALL);
    // bool Graphics::NeedParameterUpdate(ShaderParameterGroup group, const void* source) | File: ../Graphics/Graphics.h
    // Error: type "const void*" can not automatically bind
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Graphics, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // void Graphics::OnWindowMoved() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void OnWindowMoved()", asMETHODPR(Graphics, OnWindowMoved, (), void), asCALL_THISCALL);
    // void Graphics::OnWindowResized() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void OnWindowResized()", asMETHODPR(Graphics, OnWindowResized, (), void), asCALL_THISCALL);
    // void Graphics::PrecacheShaders(Deserializer& source) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void PrecacheShaders(Deserializer&)", asMETHODPR(Graphics, PrecacheShaders, (Deserializer&), void), asCALL_THISCALL);
    // void Graphics::Raise() const | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void Raise() const", asMETHODPR(Graphics, Raise, () const, void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Graphics", "int Refs() const", asMETHODPR(Graphics, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_refs() const", asMETHODPR(Graphics, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Graphics", asBEHAVE_RELEASE, "void f()", asMETHODPR(Graphics, ReleaseRef, (), void), asCALL_THISCALL);
    // void Graphics::RemoveGPUObject(GPUObject* object) | File: ../Graphics/Graphics.h
    // Error: type "GPUObject*" can not automatically bind
    // void* Graphics::ReserveScratchBuffer(unsigned size) | File: ../Graphics/Graphics.h
    // Error: type "void*" can not automatically bind
    // void Graphics::ResetDepthStencil() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void ResetDepthStencil()", asMETHODPR(Graphics, ResetDepthStencil, (), void), asCALL_THISCALL);
    // void Graphics::ResetRenderTarget(unsigned index) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void ResetRenderTarget(uint)", asMETHODPR(Graphics, ResetRenderTarget, (unsigned), void), asCALL_THISCALL);
    // void Graphics::ResetRenderTargets() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void ResetRenderTargets()", asMETHODPR(Graphics, ResetRenderTargets, (), void), asCALL_THISCALL);
    // bool Graphics::ResolveToTexture(Texture2D* destination, const IntRect& viewport) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool ResolveToTexture(Texture2D@+, const IntRect&in)", asMETHODPR(Graphics, ResolveToTexture, (Texture2D*, const IntRect&), bool), asCALL_THISCALL);
    // bool Graphics::ResolveToTexture(Texture2D* texture) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool ResolveToTexture(Texture2D@+)", asMETHODPR(Graphics, ResolveToTexture, (Texture2D*), bool), asCALL_THISCALL);
    // bool Graphics::ResolveToTexture(TextureCube* texture) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool ResolveToTexture(TextureCube@+)", asMETHODPR(Graphics, ResolveToTexture, (TextureCube*), bool), asCALL_THISCALL);
    // void Graphics::Restore() | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void SendEvent(StringHash)", asMETHODPR(Graphics, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Graphics, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Graphics::SetBlendMode(BlendMode mode, bool alphaToCoverage=false) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetBlendMode(BlendMode, bool = false)", asMETHODPR(Graphics, SetBlendMode, (BlendMode, bool), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void SetBlockEvents(bool)", asMETHODPR(Graphics, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Graphics::SetClipPlane(bool enable, const Plane& clipPlane=Plane::UP, const Matrix3x4& view=Matrix3x4::IDENTITY, const Matrix4& projection=Matrix4::IDENTITY) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetClipPlane(bool, const Plane&in = Plane::UP, const Matrix3x4&in = Matrix3x4::IDENTITY, const Matrix4&in = Matrix4::IDENTITY)", asMETHODPR(Graphics, SetClipPlane, (bool, const Plane&, const Matrix3x4&, const Matrix4&), void), asCALL_THISCALL);
    // void Graphics::SetColorWrite(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetColorWrite(bool)", asMETHODPR(Graphics, SetColorWrite, (bool), void), asCALL_THISCALL);
    // void Graphics::SetCullMode(CullMode mode) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetCullMode(CullMode)", asMETHODPR(Graphics, SetCullMode, (CullMode), void), asCALL_THISCALL);
    // void Graphics::SetDefaultTextureAnisotropy(unsigned level) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDefaultTextureAnisotropy(uint)", asMETHODPR(Graphics, SetDefaultTextureAnisotropy, (unsigned), void), asCALL_THISCALL);
    // void Graphics::SetDefaultTextureFilterMode(TextureFilterMode mode) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDefaultTextureFilterMode(TextureFilterMode)", asMETHODPR(Graphics, SetDefaultTextureFilterMode, (TextureFilterMode), void), asCALL_THISCALL);
    // bool Graphics::SetDefaultWindowModes(int width, int height, const ScreenModeParams& params) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetDefaultWindowModes(int, int, const ScreenModeParams&in)", asMETHODPR(Graphics, SetDefaultWindowModes, (int, int, const ScreenModeParams&), bool), asCALL_THISCALL);
    // void Graphics::SetDepthBias(float constantBias, float slopeScaledBias) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDepthBias(float, float)", asMETHODPR(Graphics, SetDepthBias, (float, float), void), asCALL_THISCALL);
    // void Graphics::SetDepthStencil(RenderSurface* depthStencil) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDepthStencil(RenderSurface@+)", asMETHODPR(Graphics, SetDepthStencil, (RenderSurface*), void), asCALL_THISCALL);
    // void Graphics::SetDepthStencil(Texture2D* texture) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDepthStencil(Texture2D@+)", asMETHODPR(Graphics, SetDepthStencil, (Texture2D*), void), asCALL_THISCALL);
    // void Graphics::SetDepthTest(CompareMode mode) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDepthTest(CompareMode)", asMETHODPR(Graphics, SetDepthTest, (CompareMode), void), asCALL_THISCALL);
    // void Graphics::SetDepthWrite(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDepthWrite(bool)", asMETHODPR(Graphics, SetDepthWrite, (bool), void), asCALL_THISCALL);
    // void Graphics::SetDither(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetDither(bool)", asMETHODPR(Graphics, SetDither, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_dither(bool)", asMETHODPR(Graphics, SetDither, (bool), void), asCALL_THISCALL);
    // void Graphics::SetExternalWindow(void* window) | File: ../Graphics/Graphics.h
    // Error: type "void*" can not automatically bind
    // void Graphics::SetFillMode(FillMode mode) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetFillMode(FillMode)", asMETHODPR(Graphics, SetFillMode, (FillMode), void), asCALL_THISCALL);
    // void Graphics::SetFlushGPU(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetFlushGPU(bool)", asMETHODPR(Graphics, SetFlushGPU, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_flushGPU(bool)", asMETHODPR(Graphics, SetFlushGPU, (bool), void), asCALL_THISCALL);
    // void Graphics::SetForceGL2(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetForceGL2(bool)", asMETHODPR(Graphics, SetForceGL2, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Graphics, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Graphics, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Graphics::SetIndexBuffer(IndexBuffer* buffer) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetIndexBuffer(IndexBuffer@+)", asMETHODPR(Graphics, SetIndexBuffer, (IndexBuffer*), void), asCALL_THISCALL);
    // void Graphics::SetLineAntiAlias(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetLineAntiAlias(bool)", asMETHODPR(Graphics, SetLineAntiAlias, (bool), void), asCALL_THISCALL);
    // bool Graphics::SetMode(int width, int height, bool fullscreen, bool borderless, bool resizable, bool highDPI, bool vsync, bool tripleBuffer, int multiSample, int monitor, int refreshRate) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetMode(int, int, bool, bool, bool, bool, bool, bool, int, int, int)", asMETHODPR(Graphics, SetMode, (int, int, bool, bool, bool, bool, bool, bool, int, int, int), bool), asCALL_THISCALL);
    // bool Graphics::SetMode(int width, int height) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetMode(int, int)", asMETHODPR(Graphics, SetMode, (int, int), bool), asCALL_THISCALL);
    // void Graphics::SetOrientations(const String& orientations) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetOrientations(const String&in)", asMETHODPR(Graphics, SetOrientations, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_orientations(const String&in)", asMETHODPR(Graphics, SetOrientations, (const String&), void), asCALL_THISCALL);
    // void Graphics::SetRenderTarget(unsigned index, RenderSurface* renderTarget) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetRenderTarget(uint, RenderSurface@+)", asMETHODPR(Graphics, SetRenderTarget, (unsigned, RenderSurface*), void), asCALL_THISCALL);
    // void Graphics::SetRenderTarget(unsigned index, Texture2D* texture) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetRenderTarget(uint, Texture2D@+)", asMETHODPR(Graphics, SetRenderTarget, (unsigned, Texture2D*), void), asCALL_THISCALL);
    // void Graphics::SetScissorTest(bool enable, const Rect& rect=Rect::FULL, bool borderInclusive=true) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetScissorTest(bool, const Rect&in = Rect::FULL, bool = true)", asMETHODPR(Graphics, SetScissorTest, (bool, const Rect&, bool), void), asCALL_THISCALL);
    // void Graphics::SetScissorTest(bool enable, const IntRect& rect) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetScissorTest(bool, const IntRect&in)", asMETHODPR(Graphics, SetScissorTest, (bool, const IntRect&), void), asCALL_THISCALL);
    // bool Graphics::SetScreenMode(int width, int height, const ScreenModeParams& params, bool maximize=false) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetScreenMode(int, int, const ScreenModeParams&in, bool = false)", asMETHODPR(Graphics, SetScreenMode, (int, int, const ScreenModeParams&, bool), bool), asCALL_THISCALL);
    // bool Graphics::SetScreenMode(int width, int height) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetScreenMode(int, int)", asMETHODPR(Graphics, SetScreenMode, (int, int), bool), asCALL_THISCALL);
    // void Graphics::SetShaderCacheDir(const String& path) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderCacheDir(const String&in)", asMETHODPR(Graphics, SetShaderCacheDir, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_shaderCacheDir(const String&in)", asMETHODPR(Graphics, SetShaderCacheDir, (const String&), void), asCALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const float* data, unsigned count) | File: ../Graphics/Graphics.h
    // Error: type "const float*" can not automatically bind
    // void Graphics::SetShaderParameter(StringHash param, float value) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, float)", asMETHODPR(Graphics, SetShaderParameter, (StringHash, float), void), asCALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, int value) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, int)", asMETHODPR(Graphics, SetShaderParameter, (StringHash, int), void), asCALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, bool value) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, bool)", asMETHODPR(Graphics, SetShaderParameter, (StringHash, bool), void), asCALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Color& color) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Color&in)", asMETHODPR(Graphics, SetShaderParameter, (StringHash, const Color&), void), asCALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Vector2& vector) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Vector2&in)", asMETHODPR(Graphics, SetShaderParameter, (StringHash, const Vector2&), void), asCALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Matrix3& matrix) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Matrix3&in)", asMETHODPR(Graphics, SetShaderParameter, (StringHash, const Matrix3&), void), asCALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Vector3& vector) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Vector3&in)", asMETHODPR(Graphics, SetShaderParameter, (StringHash, const Vector3&), void), asCALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Matrix4& matrix) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Matrix4&in)", asMETHODPR(Graphics, SetShaderParameter, (StringHash, const Matrix4&), void), asCALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Vector4& vector) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Vector4&in)", asMETHODPR(Graphics, SetShaderParameter, (StringHash, const Vector4&), void), asCALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Matrix3x4& matrix) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Matrix3x4&in)", asMETHODPR(Graphics, SetShaderParameter, (StringHash, const Matrix3x4&), void), asCALL_THISCALL);
    // void Graphics::SetShaderParameter(StringHash param, const Variant& value) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaderParameter(StringHash, const Variant&in)", asMETHODPR(Graphics, SetShaderParameter, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Graphics::SetShaders(ShaderVariation* vs, ShaderVariation* ps) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetShaders(ShaderVariation@+, ShaderVariation@+)", asMETHODPR(Graphics, SetShaders, (ShaderVariation*, ShaderVariation*), void), asCALL_THISCALL);
    // void Graphics::SetSRGB(bool enable) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetSRGB(bool)", asMETHODPR(Graphics, SetSRGB, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_sRGB(bool)", asMETHODPR(Graphics, SetSRGB, (bool), void), asCALL_THISCALL);
    // void Graphics::SetStencilTest(bool enable, CompareMode mode=CMP_ALWAYS, StencilOp pass=OP_KEEP, StencilOp fail=OP_KEEP, StencilOp zFail=OP_KEEP, unsigned stencilRef=0, unsigned compareMask=M_MAX_UNSIGNED, unsigned writeMask=M_MAX_UNSIGNED) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetStencilTest(bool, CompareMode = CMP_ALWAYS, StencilOp = OP_KEEP, StencilOp = OP_KEEP, StencilOp = OP_KEEP, uint = 0, uint = M_MAX_UNSIGNED, uint = M_MAX_UNSIGNED)", asMETHODPR(Graphics, SetStencilTest, (bool, CompareMode, StencilOp, StencilOp, StencilOp, unsigned, unsigned, unsigned), void), asCALL_THISCALL);
    // void Graphics::SetTexture(unsigned index, Texture* texture) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetTexture(uint, Texture@+)", asMETHODPR(Graphics, SetTexture, (unsigned, Texture*), void), asCALL_THISCALL);
    // void Graphics::SetTextureForUpdate(Texture* texture) | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Graphics::SetTextureParametersDirty() | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Graphics::SetUBO(unsigned object) | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Graphics::SetVBO(unsigned object) | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // void Graphics::SetVertexBuffer(VertexBuffer* buffer) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetVertexBuffer(VertexBuffer@+)", asMETHODPR(Graphics, SetVertexBuffer, (VertexBuffer*), void), asCALL_THISCALL);
    // bool Graphics::SetVertexBuffers(const PODVector<VertexBuffer*>& buffers, unsigned instanceOffset=0) | File: ../Graphics/Graphics.h
    // Not registered because have @nobind mark
    // bool Graphics::SetVertexBuffers(const Vector<SharedPtr<VertexBuffer>>& buffers, unsigned instanceOffset=0) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetVertexBuffers(Array<VertexBuffer@>@+, uint = 0)", asFUNCTION(Graphics_SetVertexBuffers_VectorSharedPtrVertexBuffer_unsigned), asCALL_CDECL_OBJFIRST);
    // void Graphics::SetViewport(const IntRect& rect) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetViewport(const IntRect&in)", asMETHODPR(Graphics, SetViewport, (const IntRect&), void), asCALL_THISCALL);
    // void Graphics::SetWindowIcon(Image* windowIcon) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetWindowIcon(Image@+)", asMETHODPR(Graphics, SetWindowIcon, (Image*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_windowIcon(Image@+)", asMETHODPR(Graphics, SetWindowIcon, (Image*), void), asCALL_THISCALL);
    // bool Graphics::SetWindowModes(const WindowModeParams& windowMode, const WindowModeParams& secondaryWindowMode, bool maximize=false) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool SetWindowModes(const WindowModeParams&in, const WindowModeParams&in, bool = false)", asMETHODPR(Graphics, SetWindowModes, (const WindowModeParams&, const WindowModeParams&, bool), bool), asCALL_THISCALL);
    // void Graphics::SetWindowPosition(const IntVector2& position) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetWindowPosition(const IntVector2&in)", asMETHODPR(Graphics, SetWindowPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_windowPosition(const IntVector2&in)", asMETHODPR(Graphics, SetWindowPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void Graphics::SetWindowPosition(int x, int y) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetWindowPosition(int, int)", asMETHODPR(Graphics, SetWindowPosition, (int, int), void), asCALL_THISCALL);
    // void Graphics::SetWindowTitle(const String& windowTitle) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "void SetWindowTitle(const String&in)", asMETHODPR(Graphics, SetWindowTitle, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "void set_windowTitle(const String&in)", asMETHODPR(Graphics, SetWindowTitle, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // bool Graphics::TakeScreenShot(Image& destImage) | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool TakeScreenShot(Image&)", asMETHODPR(Graphics, TakeScreenShot, (Image&), bool), asCALL_THISCALL);
    // bool Graphics::ToggleFullscreen() | File: ../Graphics/Graphics.h
    engine->RegisterObjectMethod("Graphics", "bool ToggleFullscreen()", asMETHODPR(Graphics, ToggleFullscreen, (), bool), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void UnsubscribeFromAllEvents()", asMETHODPR(Graphics, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Graphics_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Graphics, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Graphics, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Graphics", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Graphics, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Graphics", "int WeakRefs() const", asMETHODPR(Graphics, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Graphics", "int get_weakRefs() const", asMETHODPR(Graphics, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("GImpactMeshData", asBEHAVE_ADDREF, "void f()", asMETHODPR(GImpactMeshData, AddRef, (), void), asCALL_THISCALL);
    // GImpactMeshData::GImpactMeshData(Model* model, unsigned lodLevel) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("GImpactMeshData", asBEHAVE_FACTORY, "GImpactMeshData@+ f(Model@+, uint)", asFUNCTION(GImpactMeshData_GImpactMeshData_Model_unsigned), asCALL_CDECL);
    // explicit GImpactMeshData::GImpactMeshData(CustomGeometry* custom) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("GImpactMeshData", asBEHAVE_FACTORY, "GImpactMeshData@+ f(CustomGeometry@+)", asFUNCTION(GImpactMeshData_GImpactMeshData_CustomGeometry), asCALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("GImpactMeshData", "int Refs() const", asMETHODPR(GImpactMeshData, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("GImpactMeshData", "int get_refs() const", asMETHODPR(GImpactMeshData, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("GImpactMeshData", asBEHAVE_RELEASE, "void f()", asMETHODPR(GImpactMeshData, ReleaseRef, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("GImpactMeshData", "int WeakRefs() const", asMETHODPR(GImpactMeshData, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("GImpactMeshData", "int get_weakRefs() const", asMETHODPR(GImpactMeshData, WeakRefs, () const, int), asCALL_THISCALL);
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
