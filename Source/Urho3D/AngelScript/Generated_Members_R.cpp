// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// Ray::Ray(const Vector3& origin, const Vector3& direction) noexcept | File: ../Math/Ray.h
static void Ray_Ray_Vector3_Vector3(Ray* ptr, const Vector3 &origin, const Vector3 &direction)
{
    new(ptr) Ray(origin, direction);
}

// Ray::Ray(const Ray& ray) noexcept=default | File: ../Math/Ray.h
static void Ray_Ray_Ray(Ray* ptr, const Ray &ray)
{
    new(ptr) Ray(ray);
}

#ifdef URHO3D_PHYSICS
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void RaycastVehicle_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(RaycastVehicle* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// Rect::Rect(const Vector2& min, const Vector2& max) noexcept | File: ../Math/Rect.h
static void Rect_Rect_Vector2_Vector2(Rect* ptr, const Vector2 &min, const Vector2 &max)
{
    new(ptr) Rect(min, max);
}

// Rect::Rect(float left, float top, float right, float bottom) noexcept | File: ../Math/Rect.h
static void Rect_Rect_float_float_float_float(Rect* ptr, float left, float top, float right, float bottom)
{
    new(ptr) Rect(left, top, right, bottom);
}

// explicit Rect::Rect(const Vector4& vector) noexcept | File: ../Math/Rect.h
static void Rect_Rect_Vector4(Rect* ptr, const Vector4 &vector)
{
    new(ptr) Rect(vector);
}

// Rect::Rect(const Rect& rect) noexcept=default | File: ../Math/Rect.h
static void Rect_Rect_Rect(Rect* ptr, const Rect &rect)
{
    new(ptr) Rect(rect);
}

// SharedPtr<RenderPath> RenderPath::Clone() | File: ../Graphics/RenderPath.h
static RenderPath* RenderPath_Clone_void(RenderPath* ptr)
{
    SharedPtr<RenderPath> result = ptr->Clone();
    return result.Detach();
}

// explicit RenderSurface::RenderSurface(Texture* parentTexture) | File: ../Graphics/RenderSurface.h
static RenderSurface* RenderSurface_RenderSurface_Texture(Texture *parentTexture)
{
    return new RenderSurface(parentTexture);
}

// explicit Renderer::Renderer(Context* context) | File: ../Graphics/Renderer.h
static Renderer* Renderer_Renderer_Context()
{
    return new Renderer(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Renderer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Renderer* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_URHO2D
// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* Renderer2D_GetLights_void(Renderer2D* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}
#endif

#ifdef URHO3D_URHO2D
// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* Renderer2D_GetVertexLights_void(Renderer2D* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}
#endif

#ifdef URHO3D_URHO2D
// explicit Renderer2D::Renderer2D(Context* context) | File: ../Urho2D/Renderer2D.h
static Renderer2D* Renderer2D_Renderer2D_Context()
{
    return new Renderer2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Renderer2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Renderer2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// explicit Resource::Resource(Context* context) | File: ../Resource/Resource.h
static Resource* Resource_Resource_Context()
{
    return new Resource(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Resource_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Resource* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// SharedPtr<File> ResourceCache::GetFile(const String& name, bool sendEventOnFailure=true) | File: ../Resource/ResourceCache.h
static File* ResourceCache_GetFile_String_bool(ResourceCache* ptr, const String& name, bool sendEventOnFailure)
{
    SharedPtr<File> result = ptr->GetFile(name, sendEventOnFailure);
    return result.Detach();
}

// const Vector<SharedPtr<PackageFile>>& ResourceCache::GetPackageFiles() const | File: ../Resource/ResourceCache.h
static CScriptArray* ResourceCache_GetPackageFiles_void(ResourceCache* ptr)
{
    const Vector<SharedPtr<PackageFile>>& result = ptr->GetPackageFiles();
    return VectorToHandleArray(result, "Array<PackageFile@>");
}

// const Vector<String>& ResourceCache::GetResourceDirs() const | File: ../Resource/ResourceCache.h
static CScriptArray* ResourceCache_GetResourceDirs_void(ResourceCache* ptr)
{
    const Vector<String>& result = ptr->GetResourceDirs();
    return VectorToArray<String>(result, "Array<String>");
}

// SharedPtr<Resource> ResourceCache::GetTempResource(StringHash type, const String& name, bool sendEventOnFailure=true) | File: ../Resource/ResourceCache.h
static Resource* ResourceCache_GetTempResource_StringHash_String_bool(ResourceCache* ptr, StringHash type, const String& name, bool sendEventOnFailure)
{
    SharedPtr<Resource> result = ptr->GetTempResource(type, name, sendEventOnFailure);
    return result.Detach();
}

// explicit ResourceCache::ResourceCache(Context* context) | File: ../Resource/ResourceCache.h
static ResourceCache* ResourceCache_ResourceCache_Context()
{
    return new ResourceCache(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ResourceCache_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ResourceCache* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit ResourceWithMetadata::ResourceWithMetadata(Context* context) | File: ../Resource/Resource.h
static ResourceWithMetadata* ResourceWithMetadata_ResourceWithMetadata_Context()
{
    return new ResourceWithMetadata(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ResourceWithMetadata_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ResourceWithMetadata* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* RibbonTrail_GetLights_void(RibbonTrail* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* RibbonTrail_GetVertexLights_void(RibbonTrail* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// explicit RibbonTrail::RibbonTrail(Context* context) | File: ../Graphics/RibbonTrail.h
static RibbonTrail* RibbonTrail_RibbonTrail_Context()
{
    return new RibbonTrail(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void RibbonTrail_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(RibbonTrail* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

#ifdef URHO3D_PHYSICS
// explicit RigidBody::RigidBody(Context* context) | File: ../Physics/RigidBody.h
static RigidBody* RigidBody_RigidBody_Context()
{
    return new RigidBody(GetScriptContext());
}
#endif

#ifdef URHO3D_PHYSICS
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void RigidBody_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(RigidBody* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

#ifdef URHO3D_URHO2D
// explicit RigidBody2D::RigidBody2D(Context* context) | File: ../Urho2D/RigidBody2D.h
static RigidBody2D* RigidBody2D_RigidBody2D_Context()
{
    return new RigidBody2D(GetScriptContext());
}
#endif

#ifdef URHO3D_URHO2D
// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void RigidBody2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(RigidBody2D* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}
#endif

// explicit ResourceRef::ResourceRef(StringHash type) | File: ../Core/Variant.h
static void ResourceRef_ResourceRef_StringHash(ResourceRef* ptr, StringHash type)
{
    new(ptr) ResourceRef(type);
}

// ResourceRef::ResourceRef(StringHash type, const String& name) | File: ../Core/Variant.h
static void ResourceRef_ResourceRef_StringHash_String(ResourceRef* ptr, StringHash type, const String &name)
{
    new(ptr) ResourceRef(type, name);
}

// ResourceRef::ResourceRef(const String& type, const String& name) | File: ../Core/Variant.h
static void ResourceRef_ResourceRef_String_String(ResourceRef* ptr, const String &type, const String &name)
{
    new(ptr) ResourceRef(type, name);
}

// ResourceRef::ResourceRef(const ResourceRef& rhs)=default | File: ../Core/Variant.h
static void ResourceRef_ResourceRef_ResourceRef(ResourceRef* ptr, const ResourceRef &rhs)
{
    new(ptr) ResourceRef(rhs);
}

// explicit ResourceRefList::ResourceRefList(StringHash type) | File: ../Core/Variant.h
static void ResourceRefList_ResourceRefList_StringHash(ResourceRefList* ptr, StringHash type)
{
    new(ptr) ResourceRefList(type);
}

void ASRegisterGenerated_Members_R(asIScriptEngine* engine)
{
    // Vector3 Ray::direction_ | File: ../Math/Ray.h
    engine->RegisterObjectProperty("Ray", "Vector3 direction", offsetof(Ray, direction_));
    // Vector3 Ray::origin_ | File: ../Math/Ray.h
    engine->RegisterObjectProperty("Ray", "Vector3 origin", offsetof(Ray, origin_));
    // Vector3 Ray::ClosestPoint(const Ray& ray) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "Vector3 ClosestPoint(const Ray&in) const", AS_METHODPR(Ray, ClosestPoint, (const Ray&) const, Vector3), AS_CALL_THISCALL);
    // void Ray::Define(const Vector3& origin, const Vector3& direction) | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "void Define(const Vector3&in, const Vector3&in)", AS_METHODPR(Ray, Define, (const Vector3&, const Vector3&), void), AS_CALL_THISCALL);
    // float Ray::Distance(const Vector3& point) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "float Distance(const Vector3&in) const", AS_METHODPR(Ray, Distance, (const Vector3&) const, float), AS_CALL_THISCALL);
    // float Ray::HitDistance(const Plane& plane) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "float HitDistance(const Plane&in) const", AS_METHODPR(Ray, HitDistance, (const Plane&) const, float), AS_CALL_THISCALL);
    // float Ray::HitDistance(const BoundingBox& box) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "float HitDistance(const BoundingBox&in) const", AS_METHODPR(Ray, HitDistance, (const BoundingBox&) const, float), AS_CALL_THISCALL);
    // float Ray::HitDistance(const Frustum& frustum, bool solidInside=true) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "float HitDistance(const Frustum&in, bool = true) const", AS_METHODPR(Ray, HitDistance, (const Frustum&, bool) const, float), AS_CALL_THISCALL);
    // float Ray::HitDistance(const Sphere& sphere) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "float HitDistance(const Sphere&in) const", AS_METHODPR(Ray, HitDistance, (const Sphere&) const, float), AS_CALL_THISCALL);
    // float Ray::HitDistance(const Vector3& v0, const Vector3& v1, const Vector3& v2, Vector3* outNormal=nullptr, Vector3* outBary=nullptr) const | File: ../Math/Ray.h
    // Error: type "Vector3*" can not automatically bind
    // float Ray::HitDistance(const void* vertexData, unsigned vertexStride, unsigned vertexStart, unsigned vertexCount, Vector3* outNormal=nullptr, Vector2* outUV=nullptr, unsigned uvOffset=0) const | File: ../Math/Ray.h
    // Error: type "const void*" can not automatically bind
    // float Ray::HitDistance(const void* vertexData, unsigned vertexStride, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount, Vector3* outNormal=nullptr, Vector2* outUV=nullptr, unsigned uvOffset=0) const | File: ../Math/Ray.h
    // Error: type "const void*" can not automatically bind
    // bool Ray::InsideGeometry(const void* vertexData, unsigned vertexSize, unsigned vertexStart, unsigned vertexCount) const | File: ../Math/Ray.h
    // Error: type "const void*" can not automatically bind
    // bool Ray::InsideGeometry(const void* vertexData, unsigned vertexSize, const void* indexData, unsigned indexSize, unsigned indexStart, unsigned indexCount) const | File: ../Math/Ray.h
    // Error: type "const void*" can not automatically bind
    // Ray& Ray::operator=(const Ray& rhs) noexcept=default | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "Ray& opAssign(const Ray&in)", AS_METHODPR(Ray, operator=, (const Ray&), Ray&), AS_CALL_THISCALL);
    // bool Ray::operator==(const Ray& rhs) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "bool opEquals(const Ray&in) const", AS_METHODPR(Ray, operator==, (const Ray&) const, bool), AS_CALL_THISCALL);
    // Vector3 Ray::Project(const Vector3& point) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "Vector3 Project(const Vector3&in) const", AS_METHODPR(Ray, Project, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // Ray::Ray(const Vector3& origin, const Vector3& direction) noexcept | File: ../Math/Ray.h
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(Ray_Ray_Vector3_Vector3), AS_CALL_CDECL_OBJFIRST);
    // Ray::Ray(const Ray& ray) noexcept=default | File: ../Math/Ray.h
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f(const Ray&in)", AS_FUNCTION_OBJFIRST(Ray_Ray_Ray), AS_CALL_CDECL_OBJFIRST);
    // Ray Ray::Transformed(const Matrix3x4& transform) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "Ray Transformed(const Matrix3x4&in) const", AS_METHODPR(Ray, Transformed, (const Matrix3x4&) const, Ray), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Ray
    REGISTER_MANUAL_PART_Ray(Ray, "Ray")
#endif

#ifdef URHO3D_PHYSICS
    // const IntVector3 RaycastVehicle::FORWARD_RIGHT_UP | File: ../Physics/RaycastVehicle.h
    engine->SetDefaultNamespace("RaycastVehicle");
    engine->RegisterGlobalProperty("const IntVector3 FORWARD_RIGHT_UP", (void*)&RaycastVehicle::FORWARD_RIGHT_UP);
    engine->SetDefaultNamespace("");
    // const IntVector3 RaycastVehicle::FORWARD_UP_RIGHT | File: ../Physics/RaycastVehicle.h
    engine->SetDefaultNamespace("RaycastVehicle");
    engine->RegisterGlobalProperty("const IntVector3 FORWARD_UP_RIGHT", (void*)&RaycastVehicle::FORWARD_UP_RIGHT);
    engine->SetDefaultNamespace("");
    // const IntVector3 RaycastVehicle::RIGHT_FORWARD_UP | File: ../Physics/RaycastVehicle.h
    engine->SetDefaultNamespace("RaycastVehicle");
    engine->RegisterGlobalProperty("const IntVector3 RIGHT_FORWARD_UP", (void*)&RaycastVehicle::RIGHT_FORWARD_UP);
    engine->SetDefaultNamespace("");
    // const IntVector3 RaycastVehicle::RIGHT_UP_FORWARD | File: ../Physics/RaycastVehicle.h
    engine->SetDefaultNamespace("RaycastVehicle");
    engine->RegisterGlobalProperty("const IntVector3 RIGHT_UP_FORWARD", (void*)&RaycastVehicle::RIGHT_UP_FORWARD);
    engine->SetDefaultNamespace("");
    // const IntVector3 RaycastVehicle::UP_FORWARD_RIGHT | File: ../Physics/RaycastVehicle.h
    engine->SetDefaultNamespace("RaycastVehicle");
    engine->RegisterGlobalProperty("const IntVector3 UP_FORWARD_RIGHT", (void*)&RaycastVehicle::UP_FORWARD_RIGHT);
    engine->SetDefaultNamespace("");
    // const IntVector3 RaycastVehicle::UP_RIGHT_FORWARD | File: ../Physics/RaycastVehicle.h
    engine->SetDefaultNamespace("RaycastVehicle");
    engine->RegisterGlobalProperty("const IntVector3 UP_RIGHT_FORWARD", (void*)&RaycastVehicle::UP_RIGHT_FORWARD);
    engine->SetDefaultNamespace("");
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RaycastVehicle", asBEHAVE_ADDREF, "void f()", AS_METHODPR(RaycastVehicle, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void RaycastVehicle::AddWheel(Node* wheelNode, Vector3 wheelDirection, Vector3 wheelAxle, float restLength, float wheelRadius, bool frontWheel) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void AddWheel(Node@+, Vector3, Vector3, float, float, bool)", AS_METHODPR(RaycastVehicle, AddWheel, (Node*, Vector3, Vector3, float, float, bool), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void AllocateNetworkState()", AS_METHODPR(RaycastVehicle, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void RaycastVehicle::ApplyAttributes() override | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void ApplyAttributes()", AS_METHODPR(RaycastVehicle, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(RaycastVehicle, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // void RaycastVehicle::FixedPostUpdate(float timeStep) override | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void FixedPostUpdate(float)", AS_METHODPR(RaycastVehicle, FixedPostUpdate, (float), void), AS_CALL_THISCALL);
    // void RaycastVehicle::FixedUpdate(float timeStep) override | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void FixedUpdate(float)", AS_METHODPR(RaycastVehicle, FixedUpdate, (float), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool GetAnimationEnabled() const", AS_METHODPR(RaycastVehicle, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "bool get_animationEnabled() const", AS_METHODPR(RaycastVehicle, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "Variant GetAttribute(uint) const", AS_METHODPR(RaycastVehicle, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "Variant get_attributes(uint) const", AS_METHODPR(RaycastVehicle, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "Variant GetAttribute(const String&in) const", AS_METHODPR(RaycastVehicle, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(RaycastVehicle, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(RaycastVehicle, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(RaycastVehicle, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(RaycastVehicle, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "Variant GetAttributeDefault(uint) const", AS_METHODPR(RaycastVehicle, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "Variant get_attributeDefaults(uint) const", AS_METHODPR(RaycastVehicle, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(RaycastVehicle, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool GetBlockEvents() const", AS_METHODPR(RaycastVehicle, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // float RaycastVehicle::GetBrake(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetBrake(int) const", AS_METHODPR(RaycastVehicle, GetBrake, (int) const, float), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "const String& GetCategory() const", AS_METHODPR(RaycastVehicle, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "const String& get_category() const", AS_METHODPR(RaycastVehicle, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "Component@+ GetComponent(StringHash) const", AS_METHODPR(RaycastVehicle, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Vector3 RaycastVehicle::GetContactNormal(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetContactNormal(int) const", AS_METHODPR(RaycastVehicle, GetContactNormal, (int) const, Vector3), AS_CALL_THISCALL);
    // Vector3 RaycastVehicle::GetContactPosition(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetContactPosition(int) const", AS_METHODPR(RaycastVehicle, GetContactPosition, (int) const, Vector3), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // IntVector3 RaycastVehicle::GetCoordinateSystem() const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "IntVector3 GetCoordinateSystem() const", AS_METHODPR(RaycastVehicle, GetCoordinateSystem, () const, IntVector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "IntVector3 get_coordinateSystem() const", AS_METHODPR(RaycastVehicle, GetCoordinateSystem, () const, IntVector3), AS_CALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float RaycastVehicle::GetEngineForce(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetEngineForce(int) const", AS_METHODPR(RaycastVehicle, GetEngineForce, (int) const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "VariantMap& GetEventDataMap() const", AS_METHODPR(RaycastVehicle, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "Object@+ GetEventSender() const", AS_METHODPR(RaycastVehicle, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(RaycastVehicle, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(RaycastVehicle, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "const VariantMap& GetGlobalVars() const", AS_METHODPR(RaycastVehicle, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "const VariantMap& get_globalVars() const", AS_METHODPR(RaycastVehicle, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "uint GetID() const", AS_METHODPR(RaycastVehicle, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "uint get_id() const", AS_METHODPR(RaycastVehicle, GetID, () const, unsigned), AS_CALL_THISCALL);
    // float RaycastVehicle::GetInAirRPM() const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetInAirRPM() const", AS_METHODPR(RaycastVehicle, GetInAirRPM, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "float get_inAirRPM() const", AS_METHODPR(RaycastVehicle, GetInAirRPM, () const, float), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(RaycastVehicle, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // float RaycastVehicle::GetMaxSideSlipSpeed() const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetMaxSideSlipSpeed() const", AS_METHODPR(RaycastVehicle, GetMaxSideSlipSpeed, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "float get_maxSideSlipSpeed() const", AS_METHODPR(RaycastVehicle, GetMaxSideSlipSpeed, () const, float), AS_CALL_THISCALL);
    // float RaycastVehicle::GetMaxSuspensionTravel(int wheel) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetMaxSuspensionTravel(int)", AS_METHODPR(RaycastVehicle, GetMaxSuspensionTravel, (int), float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "Node@+ GetNode() const", AS_METHODPR(RaycastVehicle, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "Node@+ get_node() const", AS_METHODPR(RaycastVehicle, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "uint GetNumAttributes() const", AS_METHODPR(RaycastVehicle, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "uint get_numAttributes() const", AS_METHODPR(RaycastVehicle, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "uint GetNumNetworkAttributes() const", AS_METHODPR(RaycastVehicle, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // int RaycastVehicle::GetNumWheels() const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "int GetNumWheels() const", AS_METHODPR(RaycastVehicle, GetNumWheels, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "int get_numWheels() const", AS_METHODPR(RaycastVehicle, GetNumWheels, () const, int), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(RaycastVehicle, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(RaycastVehicle, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(RaycastVehicle, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "Scene@+ GetScene() const", AS_METHODPR(RaycastVehicle, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float RaycastVehicle::GetSteeringValue(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetSteeringValue(int) const", AS_METHODPR(RaycastVehicle, GetSteeringValue, (int) const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(RaycastVehicle, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "StringHash GetType() const", AS_METHODPR(RaycastVehicle, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "StringHash get_type() const", AS_METHODPR(RaycastVehicle, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "const String& GetTypeName() const", AS_METHODPR(RaycastVehicle, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "const String& get_typeName() const", AS_METHODPR(RaycastVehicle, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // Vector3 RaycastVehicle::GetWheelAxle(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetWheelAxle(int) const", AS_METHODPR(RaycastVehicle, GetWheelAxle, (int) const, Vector3), AS_CALL_THISCALL);
    // Vector3 RaycastVehicle::GetWheelConnectionPoint(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetWheelConnectionPoint(int) const", AS_METHODPR(RaycastVehicle, GetWheelConnectionPoint, (int) const, Vector3), AS_CALL_THISCALL);
    // float RaycastVehicle::GetWheelDampingCompression(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelDampingCompression(int) const", AS_METHODPR(RaycastVehicle, GetWheelDampingCompression, (int) const, float), AS_CALL_THISCALL);
    // float RaycastVehicle::GetWheelDampingRelaxation(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelDampingRelaxation(int) const", AS_METHODPR(RaycastVehicle, GetWheelDampingRelaxation, (int) const, float), AS_CALL_THISCALL);
    // VariantVector RaycastVehicle::GetWheelDataAttr() const | File: ../Physics/RaycastVehicle.h
    // Error: type "VariantVector" can not automatically bind
    // Vector3 RaycastVehicle::GetWheelDirection(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetWheelDirection(int) const", AS_METHODPR(RaycastVehicle, GetWheelDirection, (int) const, Vector3), AS_CALL_THISCALL);
    // float RaycastVehicle::GetWheelFrictionSlip(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelFrictionSlip(int) const", AS_METHODPR(RaycastVehicle, GetWheelFrictionSlip, (int) const, float), AS_CALL_THISCALL);
    // float RaycastVehicle::GetWheelMaxSuspensionForce(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelMaxSuspensionForce(int) const", AS_METHODPR(RaycastVehicle, GetWheelMaxSuspensionForce, (int) const, float), AS_CALL_THISCALL);
    // Node* RaycastVehicle::GetWheelNode(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Node@+ GetWheelNode(int) const", AS_METHODPR(RaycastVehicle, GetWheelNode, (int) const, Node*), AS_CALL_THISCALL);
    // Vector3 RaycastVehicle::GetWheelPosition(int wheel) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetWheelPosition(int)", AS_METHODPR(RaycastVehicle, GetWheelPosition, (int), Vector3), AS_CALL_THISCALL);
    // float RaycastVehicle::GetWheelRadius(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelRadius(int) const", AS_METHODPR(RaycastVehicle, GetWheelRadius, (int) const, float), AS_CALL_THISCALL);
    // float RaycastVehicle::GetWheelRestLength(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelRestLength(int) const", AS_METHODPR(RaycastVehicle, GetWheelRestLength, (int) const, float), AS_CALL_THISCALL);
    // float RaycastVehicle::GetWheelRollInfluence(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelRollInfluence(int) const", AS_METHODPR(RaycastVehicle, GetWheelRollInfluence, (int) const, float), AS_CALL_THISCALL);
    // Quaternion RaycastVehicle::GetWheelRotation(int wheel) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Quaternion GetWheelRotation(int)", AS_METHODPR(RaycastVehicle, GetWheelRotation, (int), Quaternion), AS_CALL_THISCALL);
    // float RaycastVehicle::GetWheelSideSlipSpeed(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelSideSlipSpeed(int) const", AS_METHODPR(RaycastVehicle, GetWheelSideSlipSpeed, (int) const, float), AS_CALL_THISCALL);
    // float RaycastVehicle::GetWheelSkidInfo(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelSkidInfo(int) const", AS_METHODPR(RaycastVehicle, GetWheelSkidInfo, (int) const, float), AS_CALL_THISCALL);
    // float RaycastVehicle::GetWheelSkidInfoCumulative(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelSkidInfoCumulative(int) const", AS_METHODPR(RaycastVehicle, GetWheelSkidInfoCumulative, (int) const, float), AS_CALL_THISCALL);
    // float RaycastVehicle::GetWheelSuspensionStiffness(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelSuspensionStiffness(int) const", AS_METHODPR(RaycastVehicle, GetWheelSuspensionStiffness, (int) const, float), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool HasEventHandlers() const", AS_METHODPR(RaycastVehicle, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(RaycastVehicle, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(RaycastVehicle, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // void RaycastVehicle::Init() | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void Init()", AS_METHODPR(RaycastVehicle, Init, (), void), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool IsEnabled() const", AS_METHODPR(RaycastVehicle, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "bool get_enabled() const", AS_METHODPR(RaycastVehicle, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool IsEnabledEffective() const", AS_METHODPR(RaycastVehicle, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "bool get_enabledEffective() const", AS_METHODPR(RaycastVehicle, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool RaycastVehicle::IsFrontWheel(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool IsFrontWheel(int) const", AS_METHODPR(RaycastVehicle, IsFrontWheel, (int) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool IsInstanceOf(StringHash) const", AS_METHODPR(RaycastVehicle, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool IsReplicated() const", AS_METHODPR(RaycastVehicle, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "bool get_replicated() const", AS_METHODPR(RaycastVehicle, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool IsTemporary() const", AS_METHODPR(RaycastVehicle, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "bool get_temporary() const", AS_METHODPR(RaycastVehicle, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool Load(Deserializer&)", AS_METHODPR(RaycastVehicle, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(RaycastVehicle, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool LoadXML(const XMLElement&in)", AS_METHODPR(RaycastVehicle, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "void MarkNetworkUpdate()", AS_METHODPR(RaycastVehicle, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(RaycastVehicle, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(RaycastVehicle, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(RaycastVehicle, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void RaycastVehicle::OnSetEnabled() override | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void OnSetEnabled()", AS_METHODPR(RaycastVehicle, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void RaycastVehicle::PostUpdate(float timeStep) override | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void PostUpdate(float)", AS_METHODPR(RaycastVehicle, PostUpdate, (float), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "void PrepareNetworkUpdate()", AS_METHODPR(RaycastVehicle, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // explicit RaycastVehicle::RaycastVehicle(Urho3D::Context* context) | File: ../Physics/RaycastVehicle.h
    // Error: context can be only first
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(RaycastVehicle, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(RaycastVehicle, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RaycastVehicle", "int Refs() const", AS_METHODPR(RaycastVehicle, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "int get_refs() const", AS_METHODPR(RaycastVehicle, Refs, () const, int), AS_CALL_THISCALL);
    // static void RaycastVehicle::RegisterObject(Context* context) | File: ../Physics/RaycastVehicle.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RaycastVehicle", asBEHAVE_RELEASE, "void f()", AS_METHODPR(RaycastVehicle, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "void Remove()", AS_METHODPR(RaycastVehicle, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(RaycastVehicle, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void RemoveInstanceDefault()", AS_METHODPR(RaycastVehicle, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void RemoveObjectAnimation()", AS_METHODPR(RaycastVehicle, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void RaycastVehicle::ResetSuspension() | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void ResetSuspension()", AS_METHODPR(RaycastVehicle, ResetSuspension, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void ResetToDefault()", AS_METHODPR(RaycastVehicle, ResetToDefault, (), void), AS_CALL_THISCALL);
    // void RaycastVehicle::ResetWheels() | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void ResetWheels()", AS_METHODPR(RaycastVehicle, ResetWheels, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool Save(Serializer&) const", AS_METHODPR(RaycastVehicle, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool SaveDefaultAttributes() const", AS_METHODPR(RaycastVehicle, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool SaveJSON(JSONValue&) const", AS_METHODPR(RaycastVehicle, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool SaveXML(XMLElement&) const", AS_METHODPR(RaycastVehicle, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SendEvent(StringHash)", AS_METHODPR(RaycastVehicle, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(RaycastVehicle, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetAnimationEnabled(bool)", AS_METHODPR(RaycastVehicle, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_animationEnabled(bool)", AS_METHODPR(RaycastVehicle, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetAnimationTime(float)", AS_METHODPR(RaycastVehicle, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(RaycastVehicle, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(RaycastVehicle, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(RaycastVehicle, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(RaycastVehicle, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(RaycastVehicle, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(RaycastVehicle, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(RaycastVehicle, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetBlockEvents(bool)", AS_METHODPR(RaycastVehicle, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetBrake(int wheel, float force) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetBrake(int, float)", AS_METHODPR(RaycastVehicle, SetBrake, (int, float), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetCoordinateSystem(const IntVector3& coordinateSystem=RIGHT_FORWARD_UP) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetCoordinateSystem(const IntVector3&in = RIGHT_FORWARD_UP)", AS_METHODPR(RaycastVehicle, SetCoordinateSystem, (const IntVector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_coordinateSystem(const IntVector3&in = RIGHT_FORWARD_UP)", AS_METHODPR(RaycastVehicle, SetCoordinateSystem, (const IntVector3&), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetEnabled(bool)", AS_METHODPR(RaycastVehicle, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_enabled(bool)", AS_METHODPR(RaycastVehicle, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetEngineForce(int wheel, float force) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetEngineForce(int, float)", AS_METHODPR(RaycastVehicle, SetEngineForce, (int, float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(RaycastVehicle, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(RaycastVehicle, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetInAirRPM(float rpm) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetInAirRPM(float)", AS_METHODPR(RaycastVehicle, SetInAirRPM, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_inAirRPM(float)", AS_METHODPR(RaycastVehicle, SetInAirRPM, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetInstanceDefault(bool)", AS_METHODPR(RaycastVehicle, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(RaycastVehicle, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetMaxSideSlipSpeed(float speed) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetMaxSideSlipSpeed(float)", AS_METHODPR(RaycastVehicle, SetMaxSideSlipSpeed, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_maxSideSlipSpeed(float)", AS_METHODPR(RaycastVehicle, SetMaxSideSlipSpeed, (float), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetMaxSuspensionTravel(int wheel, float maxSuspensionTravel) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetMaxSuspensionTravel(int, float)", AS_METHODPR(RaycastVehicle, SetMaxSuspensionTravel, (int, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(RaycastVehicle, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(RaycastVehicle, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(RaycastVehicle, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetSteeringValue(int wheel, float steeringValue) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetSteeringValue(int, float)", AS_METHODPR(RaycastVehicle, SetSteeringValue, (int, float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetTemporary(bool)", AS_METHODPR(RaycastVehicle, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_temporary(bool)", AS_METHODPR(RaycastVehicle, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetWheelAxle(int wheel, Vector3 axle) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelAxle(int, Vector3)", AS_METHODPR(RaycastVehicle, SetWheelAxle, (int, Vector3), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetWheelDampingCompression(int wheel, float compression) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelDampingCompression(int, float)", AS_METHODPR(RaycastVehicle, SetWheelDampingCompression, (int, float), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetWheelDampingRelaxation(int wheel, float damping) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelDampingRelaxation(int, float)", AS_METHODPR(RaycastVehicle, SetWheelDampingRelaxation, (int, float), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetWheelDataAttr(const VariantVector& value) | File: ../Physics/RaycastVehicle.h
    // Error: type "const VariantVector&" can not automatically bind
    // void RaycastVehicle::SetWheelDirection(int wheel, Vector3 direction) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelDirection(int, Vector3)", AS_METHODPR(RaycastVehicle, SetWheelDirection, (int, Vector3), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetWheelFrictionSlip(int wheel, float slip) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelFrictionSlip(int, float)", AS_METHODPR(RaycastVehicle, SetWheelFrictionSlip, (int, float), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetWheelMaxSuspensionForce(int wheel, float force) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelMaxSuspensionForce(int, float)", AS_METHODPR(RaycastVehicle, SetWheelMaxSuspensionForce, (int, float), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetWheelRadius(int wheel, float wheelRadius) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelRadius(int, float)", AS_METHODPR(RaycastVehicle, SetWheelRadius, (int, float), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetWheelRestLength(int wheel, float length) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelRestLength(int, float)", AS_METHODPR(RaycastVehicle, SetWheelRestLength, (int, float), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetWheelRollInfluence(int wheel, float rollInfluence) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelRollInfluence(int, float)", AS_METHODPR(RaycastVehicle, SetWheelRollInfluence, (int, float), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetWheelSkidInfo(int wheel, float factor) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelSkidInfo(int, float)", AS_METHODPR(RaycastVehicle, SetWheelSkidInfo, (int, float), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetWheelSkidInfoCumulative(int wheel, float skid) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelSkidInfoCumulative(int, float)", AS_METHODPR(RaycastVehicle, SetWheelSkidInfoCumulative, (int, float), void), AS_CALL_THISCALL);
    // void RaycastVehicle::SetWheelSuspensionStiffness(int wheel, float stiffness) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelSuspensionStiffness(int, float)", AS_METHODPR(RaycastVehicle, SetWheelSuspensionStiffness, (int, float), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void UnsubscribeFromAllEvents()", AS_METHODPR(RaycastVehicle, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(RaycastVehicle_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(RaycastVehicle, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(RaycastVehicle, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(RaycastVehicle, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void RaycastVehicle::UpdateWheelTransform(int wheel, bool interpolated) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void UpdateWheelTransform(int, bool)", AS_METHODPR(RaycastVehicle, UpdateWheelTransform, (int, bool), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RaycastVehicle", "int WeakRefs() const", AS_METHODPR(RaycastVehicle, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "int get_weakRefs() const", AS_METHODPR(RaycastVehicle, WeakRefs, () const, int), AS_CALL_THISCALL);
    // bool RaycastVehicle::WheelIsGrounded(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool WheelIsGrounded(int) const", AS_METHODPR(RaycastVehicle, WheelIsGrounded, (int) const, bool), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(RaycastVehicle, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(RaycastVehicle, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(RaycastVehicle, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_LogicComponent
    REGISTER_MANUAL_PART_LogicComponent(RaycastVehicle, "RaycastVehicle")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(RaycastVehicle, "RaycastVehicle")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(RaycastVehicle, "RaycastVehicle")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(RaycastVehicle, "RaycastVehicle")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(RaycastVehicle, "RaycastVehicle")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(RaycastVehicle, "RaycastVehicle")
#endif
#ifdef REGISTER_MANUAL_PART_RaycastVehicle
    REGISTER_MANUAL_PART_RaycastVehicle(RaycastVehicle, "RaycastVehicle")
#endif
    RegisterSubclass<LogicComponent, RaycastVehicle>(engine, "LogicComponent", "RaycastVehicle");
    RegisterSubclass<Component, RaycastVehicle>(engine, "Component", "RaycastVehicle");
    RegisterSubclass<Animatable, RaycastVehicle>(engine, "Animatable", "RaycastVehicle");
    RegisterSubclass<Serializable, RaycastVehicle>(engine, "Serializable", "RaycastVehicle");
    RegisterSubclass<Object, RaycastVehicle>(engine, "Object", "RaycastVehicle");
    RegisterSubclass<RefCounted, RaycastVehicle>(engine, "RefCounted", "RaycastVehicle");
#endif

    // const Rect Rect::FULL | File: ../Math/Rect.h
    engine->SetDefaultNamespace("Rect");
    engine->RegisterGlobalProperty("const Rect FULL", (void*)&Rect::FULL);
    engine->SetDefaultNamespace("");
    // Vector2 Rect::max_ | File: ../Math/Rect.h
    engine->RegisterObjectProperty("Rect", "Vector2 max", offsetof(Rect, max_));
    // Vector2 Rect::min_ | File: ../Math/Rect.h
    engine->RegisterObjectProperty("Rect", "Vector2 min", offsetof(Rect, min_));
    // const Rect Rect::POSITIVE | File: ../Math/Rect.h
    engine->SetDefaultNamespace("Rect");
    engine->RegisterGlobalProperty("const Rect POSITIVE", (void*)&Rect::POSITIVE);
    engine->SetDefaultNamespace("");
    // const Rect Rect::ZERO | File: ../Math/Rect.h
    engine->SetDefaultNamespace("Rect");
    engine->RegisterGlobalProperty("const Rect ZERO", (void*)&Rect::ZERO);
    engine->SetDefaultNamespace("");
    // float Rect::Bottom() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "float Bottom() const", AS_METHODPR(Rect, Bottom, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "float get_bottom() const", AS_METHODPR(Rect, Bottom, () const, float), AS_CALL_THISCALL);
    // Vector2 Rect::Center() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Vector2 Center() const", AS_METHODPR(Rect, Center, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "Vector2 get_center() const", AS_METHODPR(Rect, Center, () const, Vector2), AS_CALL_THISCALL);
    // void Rect::Clear() | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Clear()", AS_METHODPR(Rect, Clear, (), void), AS_CALL_THISCALL);
    // void Rect::Clip(const Rect& rect) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Clip(const Rect&in)", AS_METHODPR(Rect, Clip, (const Rect&), void), AS_CALL_THISCALL);
    // const float* Rect::Data() const | File: ../Math/Rect.h
    // Error: type "const float*" can not automatically bind
    // void Rect::Define(const Rect& rect) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Define(const Rect&in)", AS_METHODPR(Rect, Define, (const Rect&), void), AS_CALL_THISCALL);
    // void Rect::Define(const Vector2& min, const Vector2& max) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Define(const Vector2&in, const Vector2&in)", AS_METHODPR(Rect, Define, (const Vector2&, const Vector2&), void), AS_CALL_THISCALL);
    // void Rect::Define(const Vector2& point) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Define(const Vector2&in)", AS_METHODPR(Rect, Define, (const Vector2&), void), AS_CALL_THISCALL);
    // bool Rect::Defined() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "bool Defined() const", AS_METHODPR(Rect, Defined, () const, bool), AS_CALL_THISCALL);
    // bool Rect::Equals(const Rect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "bool Equals(const Rect&in) const", AS_METHODPR(Rect, Equals, (const Rect&) const, bool), AS_CALL_THISCALL);
    // Vector2 Rect::HalfSize() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Vector2 HalfSize() const", AS_METHODPR(Rect, HalfSize, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "Vector2 get_halfSize() const", AS_METHODPR(Rect, HalfSize, () const, Vector2), AS_CALL_THISCALL);
    // Intersection Rect::IsInside(const Vector2& point) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Intersection IsInside(const Vector2&in) const", AS_METHODPR(Rect, IsInside, (const Vector2&) const, Intersection), AS_CALL_THISCALL);
    // Intersection Rect::IsInside(const Rect& rect) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Intersection IsInside(const Rect&in) const", AS_METHODPR(Rect, IsInside, (const Rect&) const, Intersection), AS_CALL_THISCALL);
    // float Rect::Left() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "float Left() const", AS_METHODPR(Rect, Left, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "float get_left() const", AS_METHODPR(Rect, Left, () const, float), AS_CALL_THISCALL);
    // Vector2 Rect::Max() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Vector2 Max() const", AS_METHODPR(Rect, Max, () const, Vector2), AS_CALL_THISCALL);
    // void Rect::Merge(const Vector2& point) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Merge(const Vector2&in)", AS_METHODPR(Rect, Merge, (const Vector2&), void), AS_CALL_THISCALL);
    // void Rect::Merge(const Rect& rect) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Merge(const Rect&in)", AS_METHODPR(Rect, Merge, (const Rect&), void), AS_CALL_THISCALL);
    // Vector2 Rect::Min() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Vector2 Min() const", AS_METHODPR(Rect, Min, () const, Vector2), AS_CALL_THISCALL);
    // Rect Rect::operator*(float value) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect opMul(float) const", AS_METHODPR(Rect, operator*, (float) const, Rect), AS_CALL_THISCALL);
    // Rect& Rect::operator*=(float value) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect& opMulAssign(float)", AS_METHODPR(Rect, operator*=, (float), Rect&), AS_CALL_THISCALL);
    // Rect Rect::operator+(const Rect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect opAdd(const Rect&in) const", AS_METHODPR(Rect, operator+, (const Rect&) const, Rect), AS_CALL_THISCALL);
    // Rect& Rect::operator+=(const Rect& rhs) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect& opAddAssign(const Rect&in)", AS_METHODPR(Rect, operator+=, (const Rect&), Rect&), AS_CALL_THISCALL);
    // Rect Rect::operator-(const Rect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect opSub(const Rect&in) const", AS_METHODPR(Rect, operator-, (const Rect&) const, Rect), AS_CALL_THISCALL);
    // Rect& Rect::operator-=(const Rect& rhs) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect& opSubAssign(const Rect&in)", AS_METHODPR(Rect, operator-=, (const Rect&), Rect&), AS_CALL_THISCALL);
    // Rect Rect::operator/(float value) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect opDiv(float) const", AS_METHODPR(Rect, operator/, (float) const, Rect), AS_CALL_THISCALL);
    // Rect& Rect::operator/=(float value) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect& opDivAssign(float)", AS_METHODPR(Rect, operator/=, (float), Rect&), AS_CALL_THISCALL);
    // Rect& Rect::operator=(const Rect& rhs) noexcept=default | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect& opAssign(const Rect&in)", AS_METHODPR(Rect, operator=, (const Rect&), Rect&), AS_CALL_THISCALL);
    // bool Rect::operator==(const Rect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "bool opEquals(const Rect&in) const", AS_METHODPR(Rect, operator==, (const Rect&) const, bool), AS_CALL_THISCALL);
    // Rect::Rect(const Vector2& min, const Vector2& max) noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Vector2&in, const Vector2&in)", AS_FUNCTION_OBJFIRST(Rect_Rect_Vector2_Vector2), AS_CALL_CDECL_OBJFIRST);
    // Rect::Rect(float left, float top, float right, float bottom) noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", AS_FUNCTION_OBJFIRST(Rect_Rect_float_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // explicit Rect::Rect(const Vector4& vector) noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", AS_FUNCTION_OBJFIRST(Rect_Rect_Vector4), AS_CALL_CDECL_OBJFIRST);
    // explicit Rect::Rect(const float* data) noexcept | File: ../Math/Rect.h
    // Error: type "const float*" can not automatically bind
    // Rect::Rect(const Rect& rect) noexcept=default | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", AS_FUNCTION_OBJFIRST(Rect_Rect_Rect), AS_CALL_CDECL_OBJFIRST);
    // float Rect::Right() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "float Right() const", AS_METHODPR(Rect, Right, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "float get_right() const", AS_METHODPR(Rect, Right, () const, float), AS_CALL_THISCALL);
    // Vector2 Rect::Size() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Vector2 Size() const", AS_METHODPR(Rect, Size, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "Vector2 get_size() const", AS_METHODPR(Rect, Size, () const, Vector2), AS_CALL_THISCALL);
    // float Rect::Top() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "float Top() const", AS_METHODPR(Rect, Top, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "float get_top() const", AS_METHODPR(Rect, Top, () const, float), AS_CALL_THISCALL);
    // String Rect::ToString() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "String ToString() const", AS_METHODPR(Rect, ToString, () const, String), AS_CALL_THISCALL);
    // Vector4 Rect::ToVector4() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Vector4 ToVector4() const", AS_METHODPR(Rect, ToVector4, () const, Vector4), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Rect
    REGISTER_MANUAL_PART_Rect(Rect, "Rect")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RefCounted", asBEHAVE_ADDREF, "void f()", AS_METHODPR(RefCounted, AddRef, (), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RefCounted", "int Refs() const", AS_METHODPR(RefCounted, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RefCounted", "int get_refs() const", AS_METHODPR(RefCounted, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RefCounted", asBEHAVE_RELEASE, "void f()", AS_METHODPR(RefCounted, ReleaseRef, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RefCounted", "int WeakRefs() const", AS_METHODPR(RefCounted, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RefCounted", "int get_weakRefs() const", AS_METHODPR(RefCounted, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(RefCounted, "RefCounted")
#endif

    // Vector<RenderPathCommand> RenderPath::commands_ | File: ../Graphics/RenderPath.h
    // Error: type "Vector<RenderPathCommand>" can not automatically bind
    // Vector<RenderTargetInfo> RenderPath::renderTargets_ | File: ../Graphics/RenderPath.h
    // Error: type "Vector<RenderTargetInfo>" can not automatically bind
    // void RenderPath::AddCommand(const RenderPathCommand& command) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void AddCommand(const RenderPathCommand&in)", AS_METHODPR(RenderPath, AddCommand, (const RenderPathCommand&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RenderPath", asBEHAVE_ADDREF, "void f()", AS_METHODPR(RenderPath, AddRef, (), void), AS_CALL_THISCALL);
    // void RenderPath::AddRenderTarget(const RenderTargetInfo& info) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void AddRenderTarget(const RenderTargetInfo&in)", AS_METHODPR(RenderPath, AddRenderTarget, (const RenderTargetInfo&), void), AS_CALL_THISCALL);
    // bool RenderPath::Append(XMLFile* file) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "bool Append(XMLFile@+)", AS_METHODPR(RenderPath, Append, (XMLFile*), bool), AS_CALL_THISCALL);
    // SharedPtr<RenderPath> RenderPath::Clone() | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "RenderPath@+ Clone()", AS_FUNCTION_OBJFIRST(RenderPath_Clone_void), AS_CALL_CDECL_OBJFIRST);
    // RenderPathCommand* RenderPath::GetCommand(unsigned index) | File: ../Graphics/RenderPath.h
    // Error: type "RenderPathCommand*" can not automatically bind
    // unsigned RenderPath::GetNumCommands() const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "uint GetNumCommands() const", AS_METHODPR(RenderPath, GetNumCommands, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "uint get_numCommands() const", AS_METHODPR(RenderPath, GetNumCommands, () const, unsigned), AS_CALL_THISCALL);
    // unsigned RenderPath::GetNumRenderTargets() const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "uint GetNumRenderTargets() const", AS_METHODPR(RenderPath, GetNumRenderTargets, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "uint get_numRenderTargets() const", AS_METHODPR(RenderPath, GetNumRenderTargets, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& RenderPath::GetShaderParameter(const String& name) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "const Variant& GetShaderParameter(const String&in) const", AS_METHODPR(RenderPath, GetShaderParameter, (const String&) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "const Variant& get_shaderParameters(const String&in) const", AS_METHODPR(RenderPath, GetShaderParameter, (const String&) const, const Variant&), AS_CALL_THISCALL);
    // void RenderPath::InsertCommand(unsigned index, const RenderPathCommand& command) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void InsertCommand(uint, const RenderPathCommand&in)", AS_METHODPR(RenderPath, InsertCommand, (unsigned, const RenderPathCommand&), void), AS_CALL_THISCALL);
    // bool RenderPath::IsAdded(const String& tag) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "bool IsAdded(const String&in) const", AS_METHODPR(RenderPath, IsAdded, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "bool get_added(const String&in) const", AS_METHODPR(RenderPath, IsAdded, (const String&) const, bool), AS_CALL_THISCALL);
    // bool RenderPath::IsEnabled(const String& tag) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "bool IsEnabled(const String&in) const", AS_METHODPR(RenderPath, IsEnabled, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "bool get_enabled(const String&in) const", AS_METHODPR(RenderPath, IsEnabled, (const String&) const, bool), AS_CALL_THISCALL);
    // bool RenderPath::Load(XMLFile* file) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "bool Load(XMLFile@+)", AS_METHODPR(RenderPath, Load, (XMLFile*), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RenderPath", "int Refs() const", AS_METHODPR(RenderPath, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "int get_refs() const", AS_METHODPR(RenderPath, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RenderPath", asBEHAVE_RELEASE, "void f()", AS_METHODPR(RenderPath, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void RenderPath::RemoveCommand(unsigned index) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void RemoveCommand(uint)", AS_METHODPR(RenderPath, RemoveCommand, (unsigned), void), AS_CALL_THISCALL);
    // void RenderPath::RemoveCommands(const String& tag) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void RemoveCommands(const String&in)", AS_METHODPR(RenderPath, RemoveCommands, (const String&), void), AS_CALL_THISCALL);
    // void RenderPath::RemoveRenderTarget(unsigned index) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void RemoveRenderTarget(uint)", AS_METHODPR(RenderPath, RemoveRenderTarget, (unsigned), void), AS_CALL_THISCALL);
    // void RenderPath::RemoveRenderTarget(const String& name) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void RemoveRenderTarget(const String&in)", AS_METHODPR(RenderPath, RemoveRenderTarget, (const String&), void), AS_CALL_THISCALL);
    // void RenderPath::RemoveRenderTargets(const String& tag) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void RemoveRenderTargets(const String&in)", AS_METHODPR(RenderPath, RemoveRenderTargets, (const String&), void), AS_CALL_THISCALL);
    // void RenderPath::SetCommand(unsigned index, const RenderPathCommand& command) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void SetCommand(uint, const RenderPathCommand&in)", AS_METHODPR(RenderPath, SetCommand, (unsigned, const RenderPathCommand&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "void set_commands(uint, const RenderPathCommand&in)", AS_METHODPR(RenderPath, SetCommand, (unsigned, const RenderPathCommand&), void), AS_CALL_THISCALL);
    // void RenderPath::SetEnabled(const String& tag, bool active) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void SetEnabled(const String&in, bool)", AS_METHODPR(RenderPath, SetEnabled, (const String&, bool), void), AS_CALL_THISCALL);
    // void RenderPath::SetRenderTarget(unsigned index, const RenderTargetInfo& info) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void SetRenderTarget(uint, const RenderTargetInfo&in)", AS_METHODPR(RenderPath, SetRenderTarget, (unsigned, const RenderTargetInfo&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "void set_renderTargets(uint, const RenderTargetInfo&in)", AS_METHODPR(RenderPath, SetRenderTarget, (unsigned, const RenderTargetInfo&), void), AS_CALL_THISCALL);
    // void RenderPath::SetShaderParameter(const String& name, const Variant& value) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void SetShaderParameter(const String&in, const Variant&in)", AS_METHODPR(RenderPath, SetShaderParameter, (const String&, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "void set_shaderParameters(const String&in, const Variant&in)", AS_METHODPR(RenderPath, SetShaderParameter, (const String&, const Variant&), void), AS_CALL_THISCALL);
    // void RenderPath::ToggleEnabled(const String& tag) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void ToggleEnabled(const String&in)", AS_METHODPR(RenderPath, ToggleEnabled, (const String&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RenderPath", "int WeakRefs() const", AS_METHODPR(RenderPath, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "int get_weakRefs() const", AS_METHODPR(RenderPath, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(RenderPath, "RenderPath")
#endif
#ifdef REGISTER_MANUAL_PART_RenderPath
    REGISTER_MANUAL_PART_RenderPath(RenderPath, "RenderPath")
#endif
    RegisterSubclass<RefCounted, RenderPath>(engine, "RefCounted", "RenderPath");

    // void* RenderSurface::readOnlyView_ | File: ../Graphics/RenderSurface.h
    // Not registered because have @nobind mark
    // unsigned RenderSurface::renderBuffer_ | File: ../Graphics/RenderSurface.h
    // Not registered because have @nobind mark
    // void* RenderSurface::renderTargetView_ | File: ../Graphics/RenderSurface.h
    // Not registered because have @nobind mark
    // void* RenderSurface::surface_ | File: ../Graphics/RenderSurface.h
    // Not registered because have @nobind mark
    // unsigned RenderSurface::target_ | File: ../Graphics/RenderSurface.h
    // Not registered because have @nobind mark
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RenderSurface", asBEHAVE_ADDREF, "void f()", AS_METHODPR(RenderSurface, AddRef, (), void), AS_CALL_THISCALL);
    // bool RenderSurface::CreateRenderBuffer(unsigned width, unsigned height, unsigned format, int multiSample) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "bool CreateRenderBuffer(uint, uint, uint, int)", AS_METHODPR(RenderSurface, CreateRenderBuffer, (unsigned, unsigned, unsigned, int), bool), AS_CALL_THISCALL);
    // bool RenderSurface::GetAutoResolve() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "bool GetAutoResolve() const", AS_METHODPR(RenderSurface, GetAutoResolve, () const, bool), AS_CALL_THISCALL);
    // int RenderSurface::GetHeight() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "int GetHeight() const", AS_METHODPR(RenderSurface, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int get_height() const", AS_METHODPR(RenderSurface, GetHeight, () const, int), AS_CALL_THISCALL);
    // RenderSurface* RenderSurface::GetLinkedDepthStencil() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ GetLinkedDepthStencil() const", AS_METHODPR(RenderSurface, GetLinkedDepthStencil, () const, RenderSurface*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ get_linkedDepthStencil() const", AS_METHODPR(RenderSurface, GetLinkedDepthStencil, () const, RenderSurface*), AS_CALL_THISCALL);
    // RenderSurface* RenderSurface::GetLinkedRenderTarget() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ GetLinkedRenderTarget() const", AS_METHODPR(RenderSurface, GetLinkedRenderTarget, () const, RenderSurface*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ get_linkedRenderTarget() const", AS_METHODPR(RenderSurface, GetLinkedRenderTarget, () const, RenderSurface*), AS_CALL_THISCALL);
    // int RenderSurface::GetMultiSample() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "int GetMultiSample() const", AS_METHODPR(RenderSurface, GetMultiSample, () const, int), AS_CALL_THISCALL);
    // unsigned RenderSurface::GetNumViewports() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "uint GetNumViewports() const", AS_METHODPR(RenderSurface, GetNumViewports, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "uint get_numViewports() const", AS_METHODPR(RenderSurface, GetNumViewports, () const, unsigned), AS_CALL_THISCALL);
    // Texture* RenderSurface::GetParentTexture() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "Texture@+ GetParentTexture() const", AS_METHODPR(RenderSurface, GetParentTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "Texture@+ get_parentTexture() const", AS_METHODPR(RenderSurface, GetParentTexture, () const, Texture*), AS_CALL_THISCALL);
    // void* RenderSurface::GetReadOnlyView() const | File: ../Graphics/RenderSurface.h
    // Error: type "void*" can not automatically bind
    // unsigned RenderSurface::GetRenderBuffer() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "uint GetRenderBuffer() const", AS_METHODPR(RenderSurface, GetRenderBuffer, () const, unsigned), AS_CALL_THISCALL);
    // void* RenderSurface::GetRenderTargetView() const | File: ../Graphics/RenderSurface.h
    // Error: type "void*" can not automatically bind
    // void* RenderSurface::GetSurface() const | File: ../Graphics/RenderSurface.h
    // Error: type "void*" can not automatically bind
    // unsigned RenderSurface::GetTarget() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "uint GetTarget() const", AS_METHODPR(RenderSurface, GetTarget, () const, unsigned), AS_CALL_THISCALL);
    // RenderSurfaceUpdateMode RenderSurface::GetUpdateMode() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "RenderSurfaceUpdateMode GetUpdateMode() const", AS_METHODPR(RenderSurface, GetUpdateMode, () const, RenderSurfaceUpdateMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "RenderSurfaceUpdateMode get_updateMode() const", AS_METHODPR(RenderSurface, GetUpdateMode, () const, RenderSurfaceUpdateMode), AS_CALL_THISCALL);
    // TextureUsage RenderSurface::GetUsage() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "TextureUsage GetUsage() const", AS_METHODPR(RenderSurface, GetUsage, () const, TextureUsage), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "TextureUsage get_usage() const", AS_METHODPR(RenderSurface, GetUsage, () const, TextureUsage), AS_CALL_THISCALL);
    // Viewport* RenderSurface::GetViewport(unsigned index) const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "Viewport@+ GetViewport(uint) const", AS_METHODPR(RenderSurface, GetViewport, (unsigned) const, Viewport*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "Viewport@+ get_viewports(uint) const", AS_METHODPR(RenderSurface, GetViewport, (unsigned) const, Viewport*), AS_CALL_THISCALL);
    // int RenderSurface::GetWidth() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "int GetWidth() const", AS_METHODPR(RenderSurface, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int get_width() const", AS_METHODPR(RenderSurface, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool RenderSurface::IsResolveDirty() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "bool IsResolveDirty() const", AS_METHODPR(RenderSurface, IsResolveDirty, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "bool get_resolveDirty() const", AS_METHODPR(RenderSurface, IsResolveDirty, () const, bool), AS_CALL_THISCALL);
    // bool RenderSurface::IsUpdateQueued() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "bool IsUpdateQueued() const", AS_METHODPR(RenderSurface, IsUpdateQueued, () const, bool), AS_CALL_THISCALL);
    // void RenderSurface::OnDeviceLost() | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void OnDeviceLost()", AS_METHODPR(RenderSurface, OnDeviceLost, (), void), AS_CALL_THISCALL);
    // void RenderSurface::QueueUpdate() | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void QueueUpdate()", AS_METHODPR(RenderSurface, QueueUpdate, (), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RenderSurface", "int Refs() const", AS_METHODPR(RenderSurface, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int get_refs() const", AS_METHODPR(RenderSurface, Refs, () const, int), AS_CALL_THISCALL);
    // void RenderSurface::Release() | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void Release()", AS_METHODPR(RenderSurface, Release, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RenderSurface", asBEHAVE_RELEASE, "void f()", AS_METHODPR(RenderSurface, ReleaseRef, (), void), AS_CALL_THISCALL);
    // explicit RenderSurface::RenderSurface(Texture* parentTexture) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectBehaviour("RenderSurface", asBEHAVE_FACTORY, "RenderSurface@+ f(Texture@+)", AS_FUNCTION(RenderSurface_RenderSurface_Texture), AS_CALL_CDECL);
    // void RenderSurface::ResetUpdateQueued() | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void ResetUpdateQueued()", AS_METHODPR(RenderSurface, ResetUpdateQueued, (), void), AS_CALL_THISCALL);
    // void RenderSurface::SetLinkedDepthStencil(RenderSurface* depthStencil) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void SetLinkedDepthStencil(RenderSurface@+)", AS_METHODPR(RenderSurface, SetLinkedDepthStencil, (RenderSurface*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_linkedDepthStencil(RenderSurface@+)", AS_METHODPR(RenderSurface, SetLinkedDepthStencil, (RenderSurface*), void), AS_CALL_THISCALL);
    // void RenderSurface::SetLinkedRenderTarget(RenderSurface* renderTarget) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void SetLinkedRenderTarget(RenderSurface@+)", AS_METHODPR(RenderSurface, SetLinkedRenderTarget, (RenderSurface*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_linkedRenderTarget(RenderSurface@+)", AS_METHODPR(RenderSurface, SetLinkedRenderTarget, (RenderSurface*), void), AS_CALL_THISCALL);
    // void RenderSurface::SetNumViewports(unsigned num) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void SetNumViewports(uint)", AS_METHODPR(RenderSurface, SetNumViewports, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_numViewports(uint)", AS_METHODPR(RenderSurface, SetNumViewports, (unsigned), void), AS_CALL_THISCALL);
    // void RenderSurface::SetResolveDirty(bool enable) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void SetResolveDirty(bool)", AS_METHODPR(RenderSurface, SetResolveDirty, (bool), void), AS_CALL_THISCALL);
    // void RenderSurface::SetUpdateMode(RenderSurfaceUpdateMode mode) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void SetUpdateMode(RenderSurfaceUpdateMode)", AS_METHODPR(RenderSurface, SetUpdateMode, (RenderSurfaceUpdateMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_updateMode(RenderSurfaceUpdateMode)", AS_METHODPR(RenderSurface, SetUpdateMode, (RenderSurfaceUpdateMode), void), AS_CALL_THISCALL);
    // void RenderSurface::SetViewport(unsigned index, Viewport* viewport) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void SetViewport(uint, Viewport@+)", AS_METHODPR(RenderSurface, SetViewport, (unsigned, Viewport*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_viewports(uint, Viewport@+)", AS_METHODPR(RenderSurface, SetViewport, (unsigned, Viewport*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RenderSurface", "int WeakRefs() const", AS_METHODPR(RenderSurface, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int get_weakRefs() const", AS_METHODPR(RenderSurface, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(RenderSurface, "RenderSurface")
#endif
#ifdef REGISTER_MANUAL_PART_RenderSurface
    REGISTER_MANUAL_PART_RenderSurface(RenderSurface, "RenderSurface")
#endif
    RegisterSubclass<RefCounted, RenderSurface>(engine, "RefCounted", "RenderSurface");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Renderer", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Renderer, AddRef, (), void), AS_CALL_THISCALL);
    // void Renderer::ApplyShadowMapFilter(View* view, Texture2D* shadowMap, float blurScale) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void ApplyShadowMapFilter(View@+, Texture2D@+, float)", AS_METHODPR(Renderer, ApplyShadowMapFilter, (View*, Texture2D*, float), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Renderer::DrawDebugGeometry(bool depthTest) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void DrawDebugGeometry(bool)", AS_METHODPR(Renderer, DrawDebugGeometry, (bool), void), AS_CALL_THISCALL);
    // static View* Renderer::GetActualView(View* view) | File: ../Graphics/Renderer.h
    engine->SetDefaultNamespace("Renderer");
    engine->RegisterGlobalFunction("View@+ GetActualView(View@+)", AS_FUNCTIONPR(Renderer::GetActualView, (View*), View*), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "bool GetBlockEvents() const", AS_METHODPR(Renderer, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "const String& GetCategory() const", AS_METHODPR(Renderer, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "const String& get_category() const", AS_METHODPR(Renderer, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // Texture2D* Renderer::GetDefaultLightRamp() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Texture2D@+ GetDefaultLightRamp() const", AS_METHODPR(Renderer, GetDefaultLightRamp, () const, Texture2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Texture2D@+ get_defaultLightRamp() const", AS_METHODPR(Renderer, GetDefaultLightRamp, () const, Texture2D*), AS_CALL_THISCALL);
    // Texture2D* Renderer::GetDefaultLightSpot() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Texture2D@+ GetDefaultLightSpot() const", AS_METHODPR(Renderer, GetDefaultLightSpot, () const, Texture2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Texture2D@+ get_defaultLightSpot() const", AS_METHODPR(Renderer, GetDefaultLightSpot, () const, Texture2D*), AS_CALL_THISCALL);
    // Material* Renderer::GetDefaultMaterial() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Material@+ GetDefaultMaterial() const", AS_METHODPR(Renderer, GetDefaultMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Material@+ get_defaultMaterial() const", AS_METHODPR(Renderer, GetDefaultMaterial, () const, Material*), AS_CALL_THISCALL);
    // RenderPath* Renderer::GetDefaultRenderPath() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "RenderPath@+ GetDefaultRenderPath() const", AS_METHODPR(Renderer, GetDefaultRenderPath, () const, RenderPath*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "RenderPath@+ get_defaultRenderPath() const", AS_METHODPR(Renderer, GetDefaultRenderPath, () const, RenderPath*), AS_CALL_THISCALL);
    // Technique* Renderer::GetDefaultTechnique() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Technique@+ GetDefaultTechnique() const", AS_METHODPR(Renderer, GetDefaultTechnique, () const, Technique*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Technique@+ get_defaultTechnique() const", AS_METHODPR(Renderer, GetDefaultTechnique, () const, Technique*), AS_CALL_THISCALL);
    // Zone* Renderer::GetDefaultZone() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Zone@+ GetDefaultZone() const", AS_METHODPR(Renderer, GetDefaultZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Zone@+ get_defaultZone() const", AS_METHODPR(Renderer, GetDefaultZone, () const, Zone*), AS_CALL_THISCALL);
    // RenderSurface* Renderer::GetDepthStencil(int width, int height, int multiSample, bool autoResolve) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "RenderSurface@+ GetDepthStencil(int, int, int, bool)", AS_METHODPR(Renderer, GetDepthStencil, (int, int, int, bool), RenderSurface*), AS_CALL_THISCALL);
    // bool Renderer::GetDrawShadows() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool GetDrawShadows() const", AS_METHODPR(Renderer, GetDrawShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_drawShadows() const", AS_METHODPR(Renderer, GetDrawShadows, () const, bool), AS_CALL_THISCALL);
    // bool Renderer::GetDynamicInstancing() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool GetDynamicInstancing() const", AS_METHODPR(Renderer, GetDynamicInstancing, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_dynamicInstancing() const", AS_METHODPR(Renderer, GetDynamicInstancing, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "VariantMap& GetEventDataMap() const", AS_METHODPR(Renderer, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "Object@+ GetEventSender() const", AS_METHODPR(Renderer, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // TextureCube* Renderer::GetFaceSelectCubeMap() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "TextureCube@+ GetFaceSelectCubeMap() const", AS_METHODPR(Renderer, GetFaceSelectCubeMap, () const, TextureCube*), AS_CALL_THISCALL);
    // const FrameInfo& Renderer::GetFrameInfo() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "const FrameInfo& GetFrameInfo() const", AS_METHODPR(Renderer, GetFrameInfo, () const, const FrameInfo&), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Renderer, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Renderer, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Renderer, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "const VariantMap& get_globalVars() const", AS_METHODPR(Renderer, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // bool Renderer::GetHDRRendering() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool GetHDRRendering() const", AS_METHODPR(Renderer, GetHDRRendering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_hdrRendering() const", AS_METHODPR(Renderer, GetHDRRendering, () const, bool), AS_CALL_THISCALL);
    // TextureCube* Renderer::GetIndirectionCubeMap() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "TextureCube@+ GetIndirectionCubeMap() const", AS_METHODPR(Renderer, GetIndirectionCubeMap, () const, TextureCube*), AS_CALL_THISCALL);
    // VertexBuffer* Renderer::GetInstancingBuffer() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "VertexBuffer@+ GetInstancingBuffer() const", AS_METHODPR(Renderer, GetInstancingBuffer, () const, VertexBuffer*), AS_CALL_THISCALL);
    // Geometry* Renderer::GetLightGeometry(Light* light) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Geometry@+ GetLightGeometry(Light@+)", AS_METHODPR(Renderer, GetLightGeometry, (Light*), Geometry*), AS_CALL_THISCALL);
    // const Rect& Renderer::GetLightScissor(Light* light, Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "const Rect& GetLightScissor(Light@+, Camera@+)", AS_METHODPR(Renderer, GetLightScissor, (Light*, Camera*), const Rect&), AS_CALL_THISCALL);
    // MaterialQuality Renderer::GetMaterialQuality() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "MaterialQuality GetMaterialQuality() const", AS_METHODPR(Renderer, GetMaterialQuality, () const, MaterialQuality), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "MaterialQuality get_materialQuality() const", AS_METHODPR(Renderer, GetMaterialQuality, () const, MaterialQuality), AS_CALL_THISCALL);
    // int Renderer::GetMaxOccluderTriangles() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetMaxOccluderTriangles() const", AS_METHODPR(Renderer, GetMaxOccluderTriangles, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_maxOccluderTriangles() const", AS_METHODPR(Renderer, GetMaxOccluderTriangles, () const, int), AS_CALL_THISCALL);
    // int Renderer::GetMaxShadowMaps() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetMaxShadowMaps() const", AS_METHODPR(Renderer, GetMaxShadowMaps, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_maxShadowMaps() const", AS_METHODPR(Renderer, GetMaxShadowMaps, () const, int), AS_CALL_THISCALL);
    // int Renderer::GetMaxSortedInstances() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetMaxSortedInstances() const", AS_METHODPR(Renderer, GetMaxSortedInstances, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_maxSortedInstances() const", AS_METHODPR(Renderer, GetMaxSortedInstances, () const, int), AS_CALL_THISCALL);
    // int Renderer::GetMinInstances() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetMinInstances() const", AS_METHODPR(Renderer, GetMinInstances, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_minInstances() const", AS_METHODPR(Renderer, GetMinInstances, () const, int), AS_CALL_THISCALL);
    // float Renderer::GetMobileNormalOffsetMul() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "float GetMobileNormalOffsetMul() const", AS_METHODPR(Renderer, GetMobileNormalOffsetMul, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "float get_mobileNormalOffsetMul() const", AS_METHODPR(Renderer, GetMobileNormalOffsetMul, () const, float), AS_CALL_THISCALL);
    // float Renderer::GetMobileShadowBiasAdd() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "float GetMobileShadowBiasAdd() const", AS_METHODPR(Renderer, GetMobileShadowBiasAdd, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "float get_mobileShadowBiasAdd() const", AS_METHODPR(Renderer, GetMobileShadowBiasAdd, () const, float), AS_CALL_THISCALL);
    // float Renderer::GetMobileShadowBiasMul() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "float GetMobileShadowBiasMul() const", AS_METHODPR(Renderer, GetMobileShadowBiasMul, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "float get_mobileShadowBiasMul() const", AS_METHODPR(Renderer, GetMobileShadowBiasMul, () const, float), AS_CALL_THISCALL);
    // unsigned Renderer::GetNumBatches() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumBatches() const", AS_METHODPR(Renderer, GetNumBatches, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numBatches() const", AS_METHODPR(Renderer, GetNumBatches, () const, unsigned), AS_CALL_THISCALL);
    // int Renderer::GetNumExtraInstancingBufferElements() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetNumExtraInstancingBufferElements() const", AS_METHODPR(Renderer, GetNumExtraInstancingBufferElements, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_numExtraInstancingBufferElements() const", AS_METHODPR(Renderer, GetNumExtraInstancingBufferElements, () const, int), AS_CALL_THISCALL);
    // unsigned Renderer::GetNumGeometries(bool allViews=false) const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumGeometries(bool = false) const", AS_METHODPR(Renderer, GetNumGeometries, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numGeometries(bool = false) const", AS_METHODPR(Renderer, GetNumGeometries, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Renderer::GetNumLights(bool allViews=false) const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumLights(bool = false) const", AS_METHODPR(Renderer, GetNumLights, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numLights(bool = false) const", AS_METHODPR(Renderer, GetNumLights, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Renderer::GetNumOccluders(bool allViews=false) const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumOccluders(bool = false) const", AS_METHODPR(Renderer, GetNumOccluders, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numOccluders(bool = false) const", AS_METHODPR(Renderer, GetNumOccluders, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Renderer::GetNumPrimitives() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumPrimitives() const", AS_METHODPR(Renderer, GetNumPrimitives, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numPrimitives() const", AS_METHODPR(Renderer, GetNumPrimitives, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Renderer::GetNumShadowMaps(bool allViews=false) const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumShadowMaps(bool = false) const", AS_METHODPR(Renderer, GetNumShadowMaps, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numShadowMaps(bool = false) const", AS_METHODPR(Renderer, GetNumShadowMaps, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Renderer::GetNumViewports() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumViewports() const", AS_METHODPR(Renderer, GetNumViewports, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numViewports() const", AS_METHODPR(Renderer, GetNumViewports, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Renderer::GetNumViews() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumViews() const", AS_METHODPR(Renderer, GetNumViews, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numViews() const", AS_METHODPR(Renderer, GetNumViews, () const, unsigned), AS_CALL_THISCALL);
    // float Renderer::GetOccluderSizeThreshold() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "float GetOccluderSizeThreshold() const", AS_METHODPR(Renderer, GetOccluderSizeThreshold, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "float get_occluderSizeThreshold() const", AS_METHODPR(Renderer, GetOccluderSizeThreshold, () const, float), AS_CALL_THISCALL);
    // OcclusionBuffer* Renderer::GetOcclusionBuffer(Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "OcclusionBuffer@+ GetOcclusionBuffer(Camera@+)", AS_METHODPR(Renderer, GetOcclusionBuffer, (Camera*), OcclusionBuffer*), AS_CALL_THISCALL);
    // int Renderer::GetOcclusionBufferSize() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetOcclusionBufferSize() const", AS_METHODPR(Renderer, GetOcclusionBufferSize, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_occlusionBufferSize() const", AS_METHODPR(Renderer, GetOcclusionBufferSize, () const, int), AS_CALL_THISCALL);
    // View* Renderer::GetPreparedView(Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "View@+ GetPreparedView(Camera@+)", AS_METHODPR(Renderer, GetPreparedView, (Camera*), View*), AS_CALL_THISCALL);
    // Geometry* Renderer::GetQuadGeometry() | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Geometry@+ GetQuadGeometry()", AS_METHODPR(Renderer, GetQuadGeometry, (), Geometry*), AS_CALL_THISCALL);
    // bool Renderer::GetReuseShadowMaps() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool GetReuseShadowMaps() const", AS_METHODPR(Renderer, GetReuseShadowMaps, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_reuseShadowMaps() const", AS_METHODPR(Renderer, GetReuseShadowMaps, () const, bool), AS_CALL_THISCALL);
    // Texture* Renderer::GetScreenBuffer(int width, int height, unsigned format, int multiSample, bool autoResolve, bool cubemap, bool filtered, bool srgb, unsigned persistentKey=0) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Texture@+ GetScreenBuffer(int, int, uint, int, bool, bool, bool, bool, uint = 0)", AS_METHODPR(Renderer, GetScreenBuffer, (int, int, unsigned, int, bool, bool, bool, bool, unsigned), Texture*), AS_CALL_THISCALL);
    // Camera* Renderer::GetShadowCamera() | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Camera@+ GetShadowCamera()", AS_METHODPR(Renderer, GetShadowCamera, (), Camera*), AS_CALL_THISCALL);
    // Texture2D* Renderer::GetShadowMap(Light* light, Camera* camera, unsigned viewWidth, unsigned viewHeight) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Texture2D@+ GetShadowMap(Light@+, Camera@+, uint, uint)", AS_METHODPR(Renderer, GetShadowMap, (Light*, Camera*, unsigned, unsigned), Texture2D*), AS_CALL_THISCALL);
    // int Renderer::GetShadowMapSize() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetShadowMapSize() const", AS_METHODPR(Renderer, GetShadowMapSize, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_shadowMapSize() const", AS_METHODPR(Renderer, GetShadowMapSize, () const, int), AS_CALL_THISCALL);
    // ShadowQuality Renderer::GetShadowQuality() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "ShadowQuality GetShadowQuality() const", AS_METHODPR(Renderer, GetShadowQuality, () const, ShadowQuality), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "ShadowQuality get_shadowQuality() const", AS_METHODPR(Renderer, GetShadowQuality, () const, ShadowQuality), AS_CALL_THISCALL);
    // float Renderer::GetShadowSoftness() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "float GetShadowSoftness() const", AS_METHODPR(Renderer, GetShadowSoftness, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "float get_shadowSoftness() const", AS_METHODPR(Renderer, GetShadowSoftness, () const, float), AS_CALL_THISCALL);
    // bool Renderer::GetSpecularLighting() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool GetSpecularLighting() const", AS_METHODPR(Renderer, GetSpecularLighting, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_specularLighting() const", AS_METHODPR(Renderer, GetSpecularLighting, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Renderer, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // int Renderer::GetTextureAnisotropy() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetTextureAnisotropy() const", AS_METHODPR(Renderer, GetTextureAnisotropy, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_textureAnisotropy() const", AS_METHODPR(Renderer, GetTextureAnisotropy, () const, int), AS_CALL_THISCALL);
    // TextureFilterMode Renderer::GetTextureFilterMode() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "TextureFilterMode GetTextureFilterMode() const", AS_METHODPR(Renderer, GetTextureFilterMode, () const, TextureFilterMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "TextureFilterMode get_textureFilterMode() const", AS_METHODPR(Renderer, GetTextureFilterMode, () const, TextureFilterMode), AS_CALL_THISCALL);
    // MaterialQuality Renderer::GetTextureQuality() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "MaterialQuality GetTextureQuality() const", AS_METHODPR(Renderer, GetTextureQuality, () const, MaterialQuality), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "MaterialQuality get_textureQuality() const", AS_METHODPR(Renderer, GetTextureQuality, () const, MaterialQuality), AS_CALL_THISCALL);
    // bool Renderer::GetThreadedOcclusion() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool GetThreadedOcclusion() const", AS_METHODPR(Renderer, GetThreadedOcclusion, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_threadedOcclusion() const", AS_METHODPR(Renderer, GetThreadedOcclusion, () const, bool), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "StringHash GetType() const", AS_METHODPR(Renderer, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "StringHash get_type() const", AS_METHODPR(Renderer, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "const String& GetTypeName() const", AS_METHODPR(Renderer, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "const String& get_typeName() const", AS_METHODPR(Renderer, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // Viewport* Renderer::GetViewport(unsigned index) const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Viewport@+ GetViewport(uint) const", AS_METHODPR(Renderer, GetViewport, (unsigned) const, Viewport*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Viewport@+ get_viewports(uint) const", AS_METHODPR(Renderer, GetViewport, (unsigned) const, Viewport*), AS_CALL_THISCALL);
    // Viewport* Renderer::GetViewportForScene(Scene* scene, unsigned index) const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Viewport@+ GetViewportForScene(Scene@+, uint) const", AS_METHODPR(Renderer, GetViewportForScene, (Scene*, unsigned) const, Viewport*), AS_CALL_THISCALL);
    // int Renderer::GetVSMMultiSample() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetVSMMultiSample() const", AS_METHODPR(Renderer, GetVSMMultiSample, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_vsmMultiSample() const", AS_METHODPR(Renderer, GetVSMMultiSample, () const, int), AS_CALL_THISCALL);
    // Vector2 Renderer::GetVSMShadowParameters() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Vector2 GetVSMShadowParameters() const", AS_METHODPR(Renderer, GetVSMShadowParameters, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Vector2 get_vsmShadowParameters() const", AS_METHODPR(Renderer, GetVSMShadowParameters, () const, Vector2), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "bool HasEventHandlers() const", AS_METHODPR(Renderer, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Renderer, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Renderer, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Renderer, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Renderer, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // void Renderer::OptimizeLightByScissor(Light* light, Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void OptimizeLightByScissor(Light@+, Camera@+)", AS_METHODPR(Renderer, OptimizeLightByScissor, (Light*, Camera*), void), AS_CALL_THISCALL);
    // void Renderer::OptimizeLightByStencil(Light* light, Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void OptimizeLightByStencil(Light@+, Camera@+)", AS_METHODPR(Renderer, OptimizeLightByStencil, (Light*, Camera*), void), AS_CALL_THISCALL);
    // void Renderer::QueueRenderSurface(RenderSurface* renderTarget) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void QueueRenderSurface(RenderSurface@+)", AS_METHODPR(Renderer, QueueRenderSurface, (RenderSurface*), void), AS_CALL_THISCALL);
    // void Renderer::QueueViewport(RenderSurface* renderTarget, Viewport* viewport) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void QueueViewport(RenderSurface@+, Viewport@+)", AS_METHODPR(Renderer, QueueViewport, (RenderSurface*, Viewport*), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Renderer", "int Refs() const", AS_METHODPR(Renderer, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_refs() const", AS_METHODPR(Renderer, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Renderer", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Renderer, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Renderer::ReloadShaders() | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void ReloadShaders()", AS_METHODPR(Renderer, ReloadShaders, (), void), AS_CALL_THISCALL);
    // void Renderer::Render() | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void Render()", AS_METHODPR(Renderer, Render, (), void), AS_CALL_THISCALL);
    // explicit Renderer::Renderer(Context* context) | File: ../Graphics/Renderer.h
    engine->RegisterObjectBehaviour("Renderer", asBEHAVE_FACTORY, "Renderer@+ f()", AS_FUNCTION(Renderer_Renderer_Context), AS_CALL_CDECL);
    // bool Renderer::ResizeInstancingBuffer(unsigned numInstances) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool ResizeInstancingBuffer(uint)", AS_METHODPR(Renderer, ResizeInstancingBuffer, (unsigned), bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void SendEvent(StringHash)", AS_METHODPR(Renderer, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Renderer, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Renderer::SetBatchShaders(Batch& batch, Technique* tech, bool allowShadows, const BatchQueue& queue) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetBatchShaders(Batch&, Technique@+, bool, const BatchQueue&in)", AS_METHODPR(Renderer, SetBatchShaders, (Batch&, Technique*, bool, const BatchQueue&), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void SetBlockEvents(bool)", AS_METHODPR(Renderer, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Renderer::SetCullMode(CullMode mode, Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetCullMode(CullMode, Camera@+)", AS_METHODPR(Renderer, SetCullMode, (CullMode, Camera*), void), AS_CALL_THISCALL);
    // void Renderer::SetDefaultRenderPath(RenderPath* renderPath) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetDefaultRenderPath(RenderPath@+)", AS_METHODPR(Renderer, SetDefaultRenderPath, (RenderPath*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_defaultRenderPath(RenderPath@+)", AS_METHODPR(Renderer, SetDefaultRenderPath, (RenderPath*), void), AS_CALL_THISCALL);
    // void Renderer::SetDefaultRenderPath(XMLFile* xmlFile) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetDefaultRenderPath(XMLFile@+)", AS_METHODPR(Renderer, SetDefaultRenderPath, (XMLFile*), void), AS_CALL_THISCALL);
    // void Renderer::SetDefaultTechnique(Technique* technique) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetDefaultTechnique(Technique@+)", AS_METHODPR(Renderer, SetDefaultTechnique, (Technique*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_defaultTechnique(Technique@+)", AS_METHODPR(Renderer, SetDefaultTechnique, (Technique*), void), AS_CALL_THISCALL);
    // void Renderer::SetDrawShadows(bool enable) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetDrawShadows(bool)", AS_METHODPR(Renderer, SetDrawShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_drawShadows(bool)", AS_METHODPR(Renderer, SetDrawShadows, (bool), void), AS_CALL_THISCALL);
    // void Renderer::SetDynamicInstancing(bool enable) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetDynamicInstancing(bool)", AS_METHODPR(Renderer, SetDynamicInstancing, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_dynamicInstancing(bool)", AS_METHODPR(Renderer, SetDynamicInstancing, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Renderer, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Renderer, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Renderer::SetHDRRendering(bool enable) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetHDRRendering(bool)", AS_METHODPR(Renderer, SetHDRRendering, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_hdrRendering(bool)", AS_METHODPR(Renderer, SetHDRRendering, (bool), void), AS_CALL_THISCALL);
    // void Renderer::SetLightVolumeBatchShaders(Batch& batch, Camera* camera, const String& vsName, const String& psName, const String& vsDefines, const String& psDefines) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetLightVolumeBatchShaders(Batch&, Camera@+, const String&in, const String&in, const String&in, const String&in)", AS_METHODPR(Renderer, SetLightVolumeBatchShaders, (Batch&, Camera*, const String&, const String&, const String&, const String&), void), AS_CALL_THISCALL);
    // void Renderer::SetMaterialQuality(MaterialQuality quality) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMaterialQuality(MaterialQuality)", AS_METHODPR(Renderer, SetMaterialQuality, (MaterialQuality), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_materialQuality(MaterialQuality)", AS_METHODPR(Renderer, SetMaterialQuality, (MaterialQuality), void), AS_CALL_THISCALL);
    // void Renderer::SetMaxOccluderTriangles(int triangles) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMaxOccluderTriangles(int)", AS_METHODPR(Renderer, SetMaxOccluderTriangles, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_maxOccluderTriangles(int)", AS_METHODPR(Renderer, SetMaxOccluderTriangles, (int), void), AS_CALL_THISCALL);
    // void Renderer::SetMaxShadowMaps(int shadowMaps) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMaxShadowMaps(int)", AS_METHODPR(Renderer, SetMaxShadowMaps, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_maxShadowMaps(int)", AS_METHODPR(Renderer, SetMaxShadowMaps, (int), void), AS_CALL_THISCALL);
    // void Renderer::SetMaxSortedInstances(int instances) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMaxSortedInstances(int)", AS_METHODPR(Renderer, SetMaxSortedInstances, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_maxSortedInstances(int)", AS_METHODPR(Renderer, SetMaxSortedInstances, (int), void), AS_CALL_THISCALL);
    // void Renderer::SetMinInstances(int instances) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMinInstances(int)", AS_METHODPR(Renderer, SetMinInstances, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_minInstances(int)", AS_METHODPR(Renderer, SetMinInstances, (int), void), AS_CALL_THISCALL);
    // void Renderer::SetMobileNormalOffsetMul(float mul) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMobileNormalOffsetMul(float)", AS_METHODPR(Renderer, SetMobileNormalOffsetMul, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_mobileNormalOffsetMul(float)", AS_METHODPR(Renderer, SetMobileNormalOffsetMul, (float), void), AS_CALL_THISCALL);
    // void Renderer::SetMobileShadowBiasAdd(float add) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMobileShadowBiasAdd(float)", AS_METHODPR(Renderer, SetMobileShadowBiasAdd, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_mobileShadowBiasAdd(float)", AS_METHODPR(Renderer, SetMobileShadowBiasAdd, (float), void), AS_CALL_THISCALL);
    // void Renderer::SetMobileShadowBiasMul(float mul) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMobileShadowBiasMul(float)", AS_METHODPR(Renderer, SetMobileShadowBiasMul, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_mobileShadowBiasMul(float)", AS_METHODPR(Renderer, SetMobileShadowBiasMul, (float), void), AS_CALL_THISCALL);
    // void Renderer::SetNumExtraInstancingBufferElements(int elements) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetNumExtraInstancingBufferElements(int)", AS_METHODPR(Renderer, SetNumExtraInstancingBufferElements, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_numExtraInstancingBufferElements(int)", AS_METHODPR(Renderer, SetNumExtraInstancingBufferElements, (int), void), AS_CALL_THISCALL);
    // void Renderer::SetNumViewports(unsigned num) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetNumViewports(uint)", AS_METHODPR(Renderer, SetNumViewports, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_numViewports(uint)", AS_METHODPR(Renderer, SetNumViewports, (unsigned), void), AS_CALL_THISCALL);
    // void Renderer::SetOccluderSizeThreshold(float screenSize) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetOccluderSizeThreshold(float)", AS_METHODPR(Renderer, SetOccluderSizeThreshold, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_occluderSizeThreshold(float)", AS_METHODPR(Renderer, SetOccluderSizeThreshold, (float), void), AS_CALL_THISCALL);
    // void Renderer::SetOcclusionBufferSize(int size) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetOcclusionBufferSize(int)", AS_METHODPR(Renderer, SetOcclusionBufferSize, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_occlusionBufferSize(int)", AS_METHODPR(Renderer, SetOcclusionBufferSize, (int), void), AS_CALL_THISCALL);
    // void Renderer::SetReuseShadowMaps(bool enable) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetReuseShadowMaps(bool)", AS_METHODPR(Renderer, SetReuseShadowMaps, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_reuseShadowMaps(bool)", AS_METHODPR(Renderer, SetReuseShadowMaps, (bool), void), AS_CALL_THISCALL);
    // void Renderer::SetShadowMapFilter(Object* instance, ShadowMapFilter functionPtr) | File: ../Graphics/Renderer.h
    // Not registered because have @nobind mark
    // void Renderer::SetShadowMapSize(int size) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetShadowMapSize(int)", AS_METHODPR(Renderer, SetShadowMapSize, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_shadowMapSize(int)", AS_METHODPR(Renderer, SetShadowMapSize, (int), void), AS_CALL_THISCALL);
    // void Renderer::SetShadowQuality(ShadowQuality quality) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetShadowQuality(ShadowQuality)", AS_METHODPR(Renderer, SetShadowQuality, (ShadowQuality), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_shadowQuality(ShadowQuality)", AS_METHODPR(Renderer, SetShadowQuality, (ShadowQuality), void), AS_CALL_THISCALL);
    // void Renderer::SetShadowSoftness(float shadowSoftness) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetShadowSoftness(float)", AS_METHODPR(Renderer, SetShadowSoftness, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_shadowSoftness(float)", AS_METHODPR(Renderer, SetShadowSoftness, (float), void), AS_CALL_THISCALL);
    // void Renderer::SetSpecularLighting(bool enable) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetSpecularLighting(bool)", AS_METHODPR(Renderer, SetSpecularLighting, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_specularLighting(bool)", AS_METHODPR(Renderer, SetSpecularLighting, (bool), void), AS_CALL_THISCALL);
    // void Renderer::SetTextureAnisotropy(int level) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetTextureAnisotropy(int)", AS_METHODPR(Renderer, SetTextureAnisotropy, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_textureAnisotropy(int)", AS_METHODPR(Renderer, SetTextureAnisotropy, (int), void), AS_CALL_THISCALL);
    // void Renderer::SetTextureFilterMode(TextureFilterMode mode) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetTextureFilterMode(TextureFilterMode)", AS_METHODPR(Renderer, SetTextureFilterMode, (TextureFilterMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_textureFilterMode(TextureFilterMode)", AS_METHODPR(Renderer, SetTextureFilterMode, (TextureFilterMode), void), AS_CALL_THISCALL);
    // void Renderer::SetTextureQuality(MaterialQuality quality) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetTextureQuality(MaterialQuality)", AS_METHODPR(Renderer, SetTextureQuality, (MaterialQuality), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_textureQuality(MaterialQuality)", AS_METHODPR(Renderer, SetTextureQuality, (MaterialQuality), void), AS_CALL_THISCALL);
    // void Renderer::SetThreadedOcclusion(bool enable) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetThreadedOcclusion(bool)", AS_METHODPR(Renderer, SetThreadedOcclusion, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_threadedOcclusion(bool)", AS_METHODPR(Renderer, SetThreadedOcclusion, (bool), void), AS_CALL_THISCALL);
    // void Renderer::SetViewport(unsigned index, Viewport* viewport) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetViewport(uint, Viewport@+)", AS_METHODPR(Renderer, SetViewport, (unsigned, Viewport*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_viewports(uint, Viewport@+)", AS_METHODPR(Renderer, SetViewport, (unsigned, Viewport*), void), AS_CALL_THISCALL);
    // void Renderer::SetVSMMultiSample(int multiSample) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetVSMMultiSample(int)", AS_METHODPR(Renderer, SetVSMMultiSample, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_vsmMultiSample(int)", AS_METHODPR(Renderer, SetVSMMultiSample, (int), void), AS_CALL_THISCALL);
    // void Renderer::SetVSMShadowParameters(float minVariance, float lightBleedingReduction) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetVSMShadowParameters(float, float)", AS_METHODPR(Renderer, SetVSMShadowParameters, (float, float), void), AS_CALL_THISCALL);
    // void Renderer::StorePreparedView(View* view, Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void StorePreparedView(View@+, Camera@+)", AS_METHODPR(Renderer, StorePreparedView, (View*, Camera*), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void UnsubscribeFromAllEvents()", AS_METHODPR(Renderer, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Renderer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Renderer, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Renderer, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Renderer, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Renderer::Update(float timeStep) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void Update(float)", AS_METHODPR(Renderer, Update, (float), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Renderer", "int WeakRefs() const", AS_METHODPR(Renderer, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_weakRefs() const", AS_METHODPR(Renderer, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Renderer, "Renderer")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Renderer, "Renderer")
#endif
#ifdef REGISTER_MANUAL_PART_Renderer
    REGISTER_MANUAL_PART_Renderer(Renderer, "Renderer")
#endif
    RegisterSubclass<Object, Renderer>(engine, "Object", "Renderer");
    RegisterSubclass<RefCounted, Renderer>(engine, "RefCounted", "Renderer");

#ifdef URHO3D_URHO2D
    // void Renderer2D::AddDrawable(Drawable2D* drawable) | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectMethod("Renderer2D", "void AddDrawable(Drawable2D@+)", AS_METHODPR(Renderer2D, AddDrawable, (Drawable2D*), void), AS_CALL_THISCALL);
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void AddLight(Light@+)", AS_METHODPR(Renderer2D, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Renderer2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Renderer2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void AddVertexLight(Light@+)", AS_METHODPR(Renderer2D, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void AllocateNetworkState()", AS_METHODPR(Renderer2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void ApplyAttributes()", AS_METHODPR(Renderer2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Renderer2D::CheckVisibility(Drawable2D* drawable) const | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectMethod("Renderer2D", "bool CheckVisibility(Drawable2D@+) const", AS_METHODPR(Renderer2D, CheckVisibility, (Drawable2D*) const, bool), AS_CALL_THISCALL);
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Renderer2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(Renderer2D, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "bool GetAnimationEnabled() const", AS_METHODPR(Renderer2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_animationEnabled() const", AS_METHODPR(Renderer2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "Variant GetAttribute(uint) const", AS_METHODPR(Renderer2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "Variant get_attributes(uint) const", AS_METHODPR(Renderer2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(Renderer2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Renderer2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Renderer2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Renderer2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Renderer2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Renderer2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Renderer2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Renderer2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "bool GetBlockEvents() const", AS_METHODPR(Renderer2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(Renderer2D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "const BoundingBox& get_boundingBox() const", AS_METHODPR(Renderer2D, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool GetCastShadows() const", AS_METHODPR(Renderer2D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_castShadows() const", AS_METHODPR(Renderer2D, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "const String& GetCategory() const", AS_METHODPR(Renderer2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "const String& get_category() const", AS_METHODPR(Renderer2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Renderer2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetDistance() const", AS_METHODPR(Renderer2D, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint8 GetDrawableFlags() const", AS_METHODPR(Renderer2D, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetDrawDistance() const", AS_METHODPR(Renderer2D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "float get_drawDistance() const", AS_METHODPR(Renderer2D, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(Renderer2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "Object@+ GetEventSender() const", AS_METHODPR(Renderer2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "Light@+ GetFirstLight() const", AS_METHODPR(Renderer2D, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Renderer2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Renderer2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Renderer2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "const VariantMap& get_globalVars() const", AS_METHODPR(Renderer2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetID() const", AS_METHODPR(Renderer2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_id() const", AS_METHODPR(Renderer2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Renderer2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetLightMask() const", AS_METHODPR(Renderer2D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_lightMask() const", AS_METHODPR(Renderer2D, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(Renderer2D_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetLodBias() const", AS_METHODPR(Renderer2D, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "float get_lodBias() const", AS_METHODPR(Renderer2D, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetLodDistance() const", AS_METHODPR(Renderer2D, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(Renderer2D, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // Material* Renderer2D::GetMaterial(Texture2D* texture, BlendMode blendMode) | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectMethod("Renderer2D", "Material@+ GetMaterial(Texture2D@+, BlendMode)", AS_METHODPR(Renderer2D, GetMaterial, (Texture2D*, BlendMode), Material*), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetMaxLights() const", AS_METHODPR(Renderer2D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_maxLights() const", AS_METHODPR(Renderer2D, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetMaxZ() const", AS_METHODPR(Renderer2D, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetMinZ() const", AS_METHODPR(Renderer2D, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "Node@+ GetNode() const", AS_METHODPR(Renderer2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "Node@+ get_node() const", AS_METHODPR(Renderer2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetNumAttributes() const", AS_METHODPR(Renderer2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_numAttributes() const", AS_METHODPR(Renderer2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(Renderer2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetNumOccluderTriangles()", AS_METHODPR(Renderer2D, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Renderer2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Renderer2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Renderer2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "Scene@+ GetScene() const", AS_METHODPR(Renderer2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetShadowDistance() const", AS_METHODPR(Renderer2D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "float get_shadowDistance() const", AS_METHODPR(Renderer2D, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetShadowMask() const", AS_METHODPR(Renderer2D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_shadowMask() const", AS_METHODPR(Renderer2D, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetSortValue() const", AS_METHODPR(Renderer2D, GetSortValue, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Renderer2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "StringHash GetType() const", AS_METHODPR(Renderer2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "StringHash get_type() const", AS_METHODPR(Renderer2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "const String& GetTypeName() const", AS_METHODPR(Renderer2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "const String& get_typeName() const", AS_METHODPR(Renderer2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // UpdateGeometryType Renderer2D::GetUpdateGeometryType() override | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectMethod("Renderer2D", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(Renderer2D, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(Renderer2D_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetViewMask() const", AS_METHODPR(Renderer2D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_viewMask() const", AS_METHODPR(Renderer2D, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(Renderer2D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(Renderer2D, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "Zone@+ GetZone() const", AS_METHODPR(Renderer2D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "Zone@+ get_zone() const", AS_METHODPR(Renderer2D, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetZoneMask() const", AS_METHODPR(Renderer2D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_zoneMask() const", AS_METHODPR(Renderer2D, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool HasBasePass(uint) const", AS_METHODPR(Renderer2D, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "bool HasEventHandlers() const", AS_METHODPR(Renderer2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Renderer2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Renderer2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsEnabled() const", AS_METHODPR(Renderer2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_enabled() const", AS_METHODPR(Renderer2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsEnabledEffective() const", AS_METHODPR(Renderer2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_enabledEffective() const", AS_METHODPR(Renderer2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Renderer2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsInView() const", AS_METHODPR(Renderer2D, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_inView() const", AS_METHODPR(Renderer2D, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsInView(Camera@+) const", AS_METHODPR(Renderer2D, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(Renderer2D, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsOccludee() const", AS_METHODPR(Renderer2D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_occludee() const", AS_METHODPR(Renderer2D, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsOccluder() const", AS_METHODPR(Renderer2D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_occluder() const", AS_METHODPR(Renderer2D, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsReplicated() const", AS_METHODPR(Renderer2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_replicated() const", AS_METHODPR(Renderer2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsTemporary() const", AS_METHODPR(Renderer2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_temporary() const", AS_METHODPR(Renderer2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsZoneDirty() const", AS_METHODPR(Renderer2D, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void LimitLights()", AS_METHODPR(Renderer2D, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void LimitVertexLights(bool)", AS_METHODPR(Renderer2D, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool Load(Deserializer&)", AS_METHODPR(Renderer2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Renderer2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Renderer2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void MarkForUpdate()", AS_METHODPR(Renderer2D, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void MarkInView(const FrameInfo&in)", AS_METHODPR(Renderer2D, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void MarkInView(uint)", AS_METHODPR(Renderer2D, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "void MarkNetworkUpdate()", AS_METHODPR(Renderer2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Renderer2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Renderer2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Renderer2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void OnSetEnabled()", AS_METHODPR(Renderer2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "void PrepareNetworkUpdate()", AS_METHODPR(Renderer2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void Renderer2D::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Urho2D/Renderer2D.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Renderer2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Renderer2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Renderer2D", "int Refs() const", AS_METHODPR(Renderer2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "int get_refs() const", AS_METHODPR(Renderer2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void Renderer2D::RegisterObject(Context* context) | File: ../Urho2D/Renderer2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Renderer2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Renderer2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "void Remove()", AS_METHODPR(Renderer2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Renderer2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Renderer2D::RemoveDrawable(Drawable2D* drawable) | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectMethod("Renderer2D", "void RemoveDrawable(Drawable2D@+)", AS_METHODPR(Renderer2D, RemoveDrawable, (Drawable2D*), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void RemoveInstanceDefault()", AS_METHODPR(Renderer2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void RemoveObjectAnimation()", AS_METHODPR(Renderer2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // explicit Renderer2D::Renderer2D(Context* context) | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectBehaviour("Renderer2D", asBEHAVE_FACTORY, "Renderer2D@+ f()", AS_FUNCTION(Renderer2D_Renderer2D_Context), AS_CALL_CDECL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void ResetToDefault()", AS_METHODPR(Renderer2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "bool Save(Serializer&) const", AS_METHODPR(Renderer2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool SaveDefaultAttributes() const", AS_METHODPR(Renderer2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Renderer2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(Renderer2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void SendEvent(StringHash)", AS_METHODPR(Renderer2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Renderer2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetAnimationEnabled(bool)", AS_METHODPR(Renderer2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_animationEnabled(bool)", AS_METHODPR(Renderer2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetAnimationTime(float)", AS_METHODPR(Renderer2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Renderer2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Renderer2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Renderer2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Renderer2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Renderer2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Renderer2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Renderer2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetBasePass(uint)", AS_METHODPR(Renderer2D, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void SetBlockEvents(bool)", AS_METHODPR(Renderer2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetCastShadows(bool)", AS_METHODPR(Renderer2D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_castShadows(bool)", AS_METHODPR(Renderer2D, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetDrawDistance(float)", AS_METHODPR(Renderer2D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_drawDistance(float)", AS_METHODPR(Renderer2D, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "void SetEnabled(bool)", AS_METHODPR(Renderer2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_enabled(bool)", AS_METHODPR(Renderer2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Renderer2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Renderer2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetInstanceDefault(bool)", AS_METHODPR(Renderer2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Renderer2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetLightMask(uint)", AS_METHODPR(Renderer2D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_lightMask(uint)", AS_METHODPR(Renderer2D, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetLodBias(float)", AS_METHODPR(Renderer2D, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_lodBias(float)", AS_METHODPR(Renderer2D, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetMaxLights(uint)", AS_METHODPR(Renderer2D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_maxLights(uint)", AS_METHODPR(Renderer2D, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetMinMaxZ(float, float)", AS_METHODPR(Renderer2D, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Renderer2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Renderer2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Renderer2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetOccludee(bool)", AS_METHODPR(Renderer2D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_occludee(bool)", AS_METHODPR(Renderer2D, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetOccluder(bool)", AS_METHODPR(Renderer2D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_occluder(bool)", AS_METHODPR(Renderer2D, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetShadowDistance(float)", AS_METHODPR(Renderer2D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_shadowDistance(float)", AS_METHODPR(Renderer2D, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetShadowMask(uint)", AS_METHODPR(Renderer2D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_shadowMask(uint)", AS_METHODPR(Renderer2D, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetSortValue(float)", AS_METHODPR(Renderer2D, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetTemporary(bool)", AS_METHODPR(Renderer2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_temporary(bool)", AS_METHODPR(Renderer2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetViewMask(uint)", AS_METHODPR(Renderer2D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_viewMask(uint)", AS_METHODPR(Renderer2D, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetZone(Zone@+, bool = false)", AS_METHODPR(Renderer2D, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetZoneMask(uint)", AS_METHODPR(Renderer2D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_zoneMask(uint)", AS_METHODPR(Renderer2D, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(Renderer2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Renderer2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Renderer2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Renderer2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Renderer2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void Update(const FrameInfo&in)", AS_METHODPR(Renderer2D, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Renderer2D::UpdateBatches(const FrameInfo& frame) override | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectMethod("Renderer2D", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(Renderer2D, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Renderer2D::UpdateGeometry(const FrameInfo& frame) override | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectMethod("Renderer2D", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(Renderer2D, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Renderer2D", "int WeakRefs() const", AS_METHODPR(Renderer2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "int get_weakRefs() const", AS_METHODPR(Renderer2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Renderer2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Renderer2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Renderer2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(Renderer2D, "Renderer2D")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Renderer2D, "Renderer2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Renderer2D, "Renderer2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Renderer2D, "Renderer2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Renderer2D, "Renderer2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Renderer2D, "Renderer2D")
#endif
#ifdef REGISTER_MANUAL_PART_Renderer2D
    REGISTER_MANUAL_PART_Renderer2D(Renderer2D, "Renderer2D")
#endif
    RegisterSubclass<Drawable, Renderer2D>(engine, "Drawable", "Renderer2D");
    RegisterSubclass<Component, Renderer2D>(engine, "Component", "Renderer2D");
    RegisterSubclass<Animatable, Renderer2D>(engine, "Animatable", "Renderer2D");
    RegisterSubclass<Serializable, Renderer2D>(engine, "Serializable", "Renderer2D");
    RegisterSubclass<Object, Renderer2D>(engine, "Object", "Renderer2D");
    RegisterSubclass<RefCounted, Renderer2D>(engine, "RefCounted", "Renderer2D");
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Resource", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Resource, AddRef, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::BeginLoad(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "bool BeginLoad(Deserializer&)", AS_METHODPR(Resource, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "bool EndLoad()", AS_METHODPR(Resource, EndLoad, (), bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(Resource, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "bool GetBlockEvents() const", AS_METHODPR(Resource, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "const String& GetCategory() const", AS_METHODPR(Resource, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "const String& get_category() const", AS_METHODPR(Resource, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "VariantMap& GetEventDataMap() const", AS_METHODPR(Resource, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "Object@+ GetEventSender() const", AS_METHODPR(Resource, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Resource, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Resource, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Resource, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "const VariantMap& get_globalVars() const", AS_METHODPR(Resource, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "uint GetMemoryUse() const", AS_METHODPR(Resource, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "uint get_memoryUse() const", AS_METHODPR(Resource, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "const String& GetName() const", AS_METHODPR(Resource, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "const String& get_name() const", AS_METHODPR(Resource, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "StringHash GetNameHash() const", AS_METHODPR(Resource, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Resource, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "StringHash GetType() const", AS_METHODPR(Resource, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "StringHash get_type() const", AS_METHODPR(Resource, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "const String& GetTypeName() const", AS_METHODPR(Resource, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "const String& get_typeName() const", AS_METHODPR(Resource, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "uint GetUseTimer()", AS_METHODPR(Resource, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "uint get_useTimer()", AS_METHODPR(Resource, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "bool HasEventHandlers() const", AS_METHODPR(Resource, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Resource, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Resource, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Resource, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "bool Load(Deserializer&)", AS_METHODPR(Resource, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "bool LoadFile(const String&in)", AS_METHODPR(Resource, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "bool Load(const String&in)", AS_METHODPR(Resource, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Resource, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Resource", "int Refs() const", AS_METHODPR(Resource, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "int get_refs() const", AS_METHODPR(Resource, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Resource", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Resource, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "void ResetUseTimer()", AS_METHODPR(Resource, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // explicit Resource::Resource(Context* context) | File: ../Resource/Resource.h
    engine->RegisterObjectBehaviour("Resource", asBEHAVE_FACTORY, "Resource@+ f()", AS_FUNCTION(Resource_Resource_Context), AS_CALL_CDECL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "bool Save(Serializer&) const", AS_METHODPR(Resource, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "bool SaveFile(const String&in) const", AS_METHODPR(Resource, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "bool Save(const String&in) const", AS_METHODPR(Resource, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void SendEvent(StringHash)", AS_METHODPR(Resource, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Resource, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(Resource, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void SetBlockEvents(bool)", AS_METHODPR(Resource, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Resource, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Resource, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "void SetMemoryUse(uint)", AS_METHODPR(Resource, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "void SetName(const String&in)", AS_METHODPR(Resource, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "void set_name(const String&in)", AS_METHODPR(Resource, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void UnsubscribeFromAllEvents()", AS_METHODPR(Resource, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Resource_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Resource, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Resource, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Resource, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Resource", "int WeakRefs() const", AS_METHODPR(Resource, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "int get_weakRefs() const", AS_METHODPR(Resource, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Resource, "Resource")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Resource, "Resource")
#endif
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(Resource, "Resource")
#endif
    RegisterSubclass<Object, Resource>(engine, "Object", "Resource");
    RegisterSubclass<RefCounted, Resource>(engine, "RefCounted", "Resource");

    // bool ResourceCache::AddManualResource(Resource* resource) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool AddManualResource(Resource@+)", AS_METHODPR(ResourceCache, AddManualResource, (Resource*), bool), AS_CALL_THISCALL);
    // bool ResourceCache::AddPackageFile(PackageFile* package, unsigned priority=PRIORITY_LAST) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool AddPackageFile(PackageFile@+, uint = PRIORITY_LAST)", AS_METHODPR(ResourceCache, AddPackageFile, (PackageFile*, unsigned), bool), AS_CALL_THISCALL);
    // bool ResourceCache::AddPackageFile(const String& fileName, unsigned priority=PRIORITY_LAST) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool AddPackageFile(const String&in, uint = PRIORITY_LAST)", AS_METHODPR(ResourceCache, AddPackageFile, (const String&, unsigned), bool), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ResourceCache", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ResourceCache, AddRef, (), void), AS_CALL_THISCALL);
    // bool ResourceCache::AddResourceDir(const String& pathName, unsigned priority=PRIORITY_LAST) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool AddResourceDir(const String&in, uint = PRIORITY_LAST)", AS_METHODPR(ResourceCache, AddResourceDir, (const String&, unsigned), bool), AS_CALL_THISCALL);
    // void ResourceCache::AddResourceRouter(ResourceRouter* router, bool addAsFirst=false) | File: ../Resource/ResourceCache.h
    // Error: type "ResourceRouter" can not automatically bind bacause have @nobind mark
    // bool ResourceCache::BackgroundLoadResource(StringHash type, const String& name, bool sendEventOnFailure=true, Resource* caller=nullptr) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool BackgroundLoadResource(StringHash, const String&in, bool = true, Resource@+ = null)", AS_METHODPR(ResourceCache, BackgroundLoadResource, (StringHash, const String&, bool, Resource*), bool), AS_CALL_THISCALL);
    // template<class T> bool ResourceCache::BackgroundLoadResource(const String& name, bool sendEventOnFailure=true, Resource* caller=nullptr) | File: ../Resource/ResourceCache.h
    // Not registered because template
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool ResourceCache::Exists(const String& name) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool Exists(const String&in) const", AS_METHODPR(ResourceCache, Exists, (const String&) const, bool), AS_CALL_THISCALL);
    // const HashMap<StringHash, ResourceGroup>& ResourceCache::GetAllResources() const | File: ../Resource/ResourceCache.h
    // Error: type "const HashMap<StringHash, ResourceGroup>&" can not automatically bind
    // bool ResourceCache::GetAutoReloadResources() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool GetAutoReloadResources() const", AS_METHODPR(ResourceCache, GetAutoReloadResources, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool get_autoReloadResources() const", AS_METHODPR(ResourceCache, GetAutoReloadResources, () const, bool), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "bool GetBlockEvents() const", AS_METHODPR(ResourceCache, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "const String& GetCategory() const", AS_METHODPR(ResourceCache, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "const String& get_category() const", AS_METHODPR(ResourceCache, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "VariantMap& GetEventDataMap() const", AS_METHODPR(ResourceCache, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "Object@+ GetEventSender() const", AS_METHODPR(ResourceCache, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Resource* ResourceCache::GetExistingResource(StringHash type, const String& name) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetExistingResource(StringHash, const String&in)", AS_METHODPR(ResourceCache, GetExistingResource, (StringHash, const String&), Resource*), AS_CALL_THISCALL);
    // template<class T> T* ResourceCache::GetExistingResource(const String& name) | File: ../Resource/ResourceCache.h
    // Not registered because template
    // SharedPtr<File> ResourceCache::GetFile(const String& name, bool sendEventOnFailure=true) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "File@+ GetFile(const String&in, bool = true)", AS_FUNCTION_OBJFIRST(ResourceCache_GetFile_String_bool), AS_CALL_CDECL_OBJFIRST);
    // int ResourceCache::GetFinishBackgroundResourcesMs() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "int GetFinishBackgroundResourcesMs() const", AS_METHODPR(ResourceCache, GetFinishBackgroundResourcesMs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "int get_finishBackgroundResourcesMs() const", AS_METHODPR(ResourceCache, GetFinishBackgroundResourcesMs, () const, int), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ResourceCache, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ResourceCache, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ResourceCache, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "const VariantMap& get_globalVars() const", AS_METHODPR(ResourceCache, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned long long ResourceCache::GetMemoryBudget(StringHash type) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "uint64 GetMemoryBudget(StringHash) const", AS_METHODPR(ResourceCache, GetMemoryBudget, (StringHash) const, unsigned long long), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "uint64 get_memoryBudget(StringHash) const", AS_METHODPR(ResourceCache, GetMemoryBudget, (StringHash) const, unsigned long long), AS_CALL_THISCALL);
    // unsigned long long ResourceCache::GetMemoryUse(StringHash type) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "uint64 GetMemoryUse(StringHash) const", AS_METHODPR(ResourceCache, GetMemoryUse, (StringHash) const, unsigned long long), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "uint64 get_memoryUse(StringHash) const", AS_METHODPR(ResourceCache, GetMemoryUse, (StringHash) const, unsigned long long), AS_CALL_THISCALL);
    // unsigned ResourceCache::GetNumBackgroundLoadResources() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "uint GetNumBackgroundLoadResources() const", AS_METHODPR(ResourceCache, GetNumBackgroundLoadResources, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "uint get_numBackgroundLoadResources() const", AS_METHODPR(ResourceCache, GetNumBackgroundLoadResources, () const, unsigned), AS_CALL_THISCALL);
    // const Vector<SharedPtr<PackageFile>>& ResourceCache::GetPackageFiles() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "Array<PackageFile@>@ GetPackageFiles() const", AS_FUNCTION_OBJFIRST(ResourceCache_GetPackageFiles_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ResourceCache", "Array<PackageFile@>@ get_packageFiles() const", AS_FUNCTION_OBJFIRST(ResourceCache_GetPackageFiles_void), AS_CALL_CDECL_OBJFIRST);
    // String ResourceCache::GetPreferredResourceDir(const String& path) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "String GetPreferredResourceDir(const String&in) const", AS_METHODPR(ResourceCache, GetPreferredResourceDir, (const String&) const, String), AS_CALL_THISCALL);
    // Resource* ResourceCache::GetResource(StringHash type, const String& name, bool sendEventOnFailure=true) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetResource(StringHash, const String&in, bool = true)", AS_METHODPR(ResourceCache, GetResource, (StringHash, const String&, bool), Resource*), AS_CALL_THISCALL);
    // template<class T> T* ResourceCache::GetResource(const String& name, bool sendEventOnFailure=true) | File: ../Resource/ResourceCache.h
    // Not registered because template
    // const Vector<String>& ResourceCache::GetResourceDirs() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "Array<String>@ GetResourceDirs() const", AS_FUNCTION_OBJFIRST(ResourceCache_GetResourceDirs_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ResourceCache", "Array<String>@ get_resourceDirs() const", AS_FUNCTION_OBJFIRST(ResourceCache_GetResourceDirs_void), AS_CALL_CDECL_OBJFIRST);
    // String ResourceCache::GetResourceFileName(const String& name) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "String GetResourceFileName(const String&in) const", AS_METHODPR(ResourceCache, GetResourceFileName, (const String&) const, String), AS_CALL_THISCALL);
    // ResourceRouter* ResourceCache::GetResourceRouter(unsigned index) const | File: ../Resource/ResourceCache.h
    // Error: type "ResourceRouter" can not automatically bind bacause have @nobind mark
    // void ResourceCache::GetResources(PODVector<Resource*>& result, StringHash type) const | File: ../Resource/ResourceCache.h
    // Error: type "PODVector<Resource*>&" can not automatically bind
    // template<class T> void ResourceCache::GetResources(PODVector<T*>& result) const | File: ../Resource/ResourceCache.h
    // Not registered because template
    // bool ResourceCache::GetReturnFailedResources() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool GetReturnFailedResources() const", AS_METHODPR(ResourceCache, GetReturnFailedResources, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool get_returnFailedResources() const", AS_METHODPR(ResourceCache, GetReturnFailedResources, () const, bool), AS_CALL_THISCALL);
    // bool ResourceCache::GetSearchPackagesFirst() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool GetSearchPackagesFirst() const", AS_METHODPR(ResourceCache, GetSearchPackagesFirst, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool get_searchPackagesFirst() const", AS_METHODPR(ResourceCache, GetSearchPackagesFirst, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ResourceCache, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<Resource> ResourceCache::GetTempResource(StringHash type, const String& name, bool sendEventOnFailure=true) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetTempResource(StringHash, const String&in, bool = true)", AS_FUNCTION_OBJFIRST(ResourceCache_GetTempResource_StringHash_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> SharedPtr<T> ResourceCache::GetTempResource(const String& name, bool sendEventOnFailure=true) | File: ../Resource/ResourceCache.h
    // Not registered because template
    // unsigned long long ResourceCache::GetTotalMemoryUse() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "uint64 GetTotalMemoryUse() const", AS_METHODPR(ResourceCache, GetTotalMemoryUse, () const, unsigned long long), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "uint64 get_totalMemoryUse() const", AS_METHODPR(ResourceCache, GetTotalMemoryUse, () const, unsigned long long), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "StringHash GetType() const", AS_METHODPR(ResourceCache, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "StringHash get_type() const", AS_METHODPR(ResourceCache, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "const String& GetTypeName() const", AS_METHODPR(ResourceCache, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "const String& get_typeName() const", AS_METHODPR(ResourceCache, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "bool HasEventHandlers() const", AS_METHODPR(ResourceCache, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ResourceCache, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ResourceCache, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ResourceCache, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ResourceCache, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // String ResourceCache::PrintMemoryUsage() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "String PrintMemoryUsage() const", AS_METHODPR(ResourceCache, PrintMemoryUsage, () const, String), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ResourceCache", "int Refs() const", AS_METHODPR(ResourceCache, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "int get_refs() const", AS_METHODPR(ResourceCache, Refs, () const, int), AS_CALL_THISCALL);
    // void ResourceCache::ReleaseAllResources(bool force=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseAllResources(bool = false)", AS_METHODPR(ResourceCache, ReleaseAllResources, (bool), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ResourceCache", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ResourceCache, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ResourceCache::ReleaseResource(StringHash type, const String& name, bool force=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResource(StringHash, const String&in, bool = false)", AS_METHODPR(ResourceCache, ReleaseResource, (StringHash, const String&, bool), void), AS_CALL_THISCALL);
    // template<class T> void ResourceCache::ReleaseResource(const String& name, bool force=false) | File: ../Resource/ResourceCache.h
    // Not registered because template
    // void ResourceCache::ReleaseResources(StringHash type, bool force=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(StringHash, bool = false)", AS_METHODPR(ResourceCache, ReleaseResources, (StringHash, bool), void), AS_CALL_THISCALL);
    // void ResourceCache::ReleaseResources(StringHash type, const String& partialName, bool force=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(StringHash, const String&in, bool = false)", AS_METHODPR(ResourceCache, ReleaseResources, (StringHash, const String&, bool), void), AS_CALL_THISCALL);
    // void ResourceCache::ReleaseResources(const String& partialName, bool force=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(const String&in, bool = false)", AS_METHODPR(ResourceCache, ReleaseResources, (const String&, bool), void), AS_CALL_THISCALL);
    // bool ResourceCache::ReloadResource(Resource* resource) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool ReloadResource(Resource@+)", AS_METHODPR(ResourceCache, ReloadResource, (Resource*), bool), AS_CALL_THISCALL);
    // void ResourceCache::ReloadResourceWithDependencies(const String& fileName) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ReloadResourceWithDependencies(const String&in)", AS_METHODPR(ResourceCache, ReloadResourceWithDependencies, (const String&), void), AS_CALL_THISCALL);
    // void ResourceCache::RemovePackageFile(PackageFile* package, bool releaseResources=true, bool forceRelease=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void RemovePackageFile(PackageFile@+, bool = true, bool = false)", AS_METHODPR(ResourceCache, RemovePackageFile, (PackageFile*, bool, bool), void), AS_CALL_THISCALL);
    // void ResourceCache::RemovePackageFile(const String& fileName, bool releaseResources=true, bool forceRelease=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void RemovePackageFile(const String&in, bool = true, bool = false)", AS_METHODPR(ResourceCache, RemovePackageFile, (const String&, bool, bool), void), AS_CALL_THISCALL);
    // void ResourceCache::RemoveResourceDir(const String& pathName) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void RemoveResourceDir(const String&in)", AS_METHODPR(ResourceCache, RemoveResourceDir, (const String&), void), AS_CALL_THISCALL);
    // void ResourceCache::RemoveResourceRouter(ResourceRouter* router) | File: ../Resource/ResourceCache.h
    // Error: type "ResourceRouter" can not automatically bind bacause have @nobind mark
    // void ResourceCache::ResetDependencies(Resource* resource) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ResetDependencies(Resource@+)", AS_METHODPR(ResourceCache, ResetDependencies, (Resource*), void), AS_CALL_THISCALL);
    // explicit ResourceCache::ResourceCache(Context* context) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectBehaviour("ResourceCache", asBEHAVE_FACTORY, "ResourceCache@+ f()", AS_FUNCTION(ResourceCache_ResourceCache_Context), AS_CALL_CDECL);
    // String ResourceCache::SanitateResourceDirName(const String& name) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "String SanitateResourceDirName(const String&in) const", AS_METHODPR(ResourceCache, SanitateResourceDirName, (const String&) const, String), AS_CALL_THISCALL);
    // String ResourceCache::SanitateResourceName(const String& name) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "String SanitateResourceName(const String&in) const", AS_METHODPR(ResourceCache, SanitateResourceName, (const String&) const, String), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void SendEvent(StringHash)", AS_METHODPR(ResourceCache, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ResourceCache, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ResourceCache::SetAutoReloadResources(bool enable) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void SetAutoReloadResources(bool)", AS_METHODPR(ResourceCache, SetAutoReloadResources, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_autoReloadResources(bool)", AS_METHODPR(ResourceCache, SetAutoReloadResources, (bool), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void SetBlockEvents(bool)", AS_METHODPR(ResourceCache, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void ResourceCache::SetFinishBackgroundResourcesMs(int ms) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void SetFinishBackgroundResourcesMs(int)", AS_METHODPR(ResourceCache, SetFinishBackgroundResourcesMs, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_finishBackgroundResourcesMs(int)", AS_METHODPR(ResourceCache, SetFinishBackgroundResourcesMs, (int), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ResourceCache, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ResourceCache, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void ResourceCache::SetMemoryBudget(StringHash type, unsigned long long budget) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void SetMemoryBudget(StringHash, uint64)", AS_METHODPR(ResourceCache, SetMemoryBudget, (StringHash, unsigned long long), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_memoryBudget(StringHash, uint64)", AS_METHODPR(ResourceCache, SetMemoryBudget, (StringHash, unsigned long long), void), AS_CALL_THISCALL);
    // void ResourceCache::SetReturnFailedResources(bool enable) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void SetReturnFailedResources(bool)", AS_METHODPR(ResourceCache, SetReturnFailedResources, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_returnFailedResources(bool)", AS_METHODPR(ResourceCache, SetReturnFailedResources, (bool), void), AS_CALL_THISCALL);
    // void ResourceCache::SetSearchPackagesFirst(bool value) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void SetSearchPackagesFirst(bool)", AS_METHODPR(ResourceCache, SetSearchPackagesFirst, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_searchPackagesFirst(bool)", AS_METHODPR(ResourceCache, SetSearchPackagesFirst, (bool), void), AS_CALL_THISCALL);
    // void ResourceCache::StoreResourceDependency(Resource* resource, const String& dependency) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void StoreResourceDependency(Resource@+, const String&in)", AS_METHODPR(ResourceCache, StoreResourceDependency, (Resource*, const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void UnsubscribeFromAllEvents()", AS_METHODPR(ResourceCache, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ResourceCache_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ResourceCache, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ResourceCache, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ResourceCache, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ResourceCache", "int WeakRefs() const", AS_METHODPR(ResourceCache, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "int get_weakRefs() const", AS_METHODPR(ResourceCache, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ResourceCache, "ResourceCache")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ResourceCache, "ResourceCache")
#endif
#ifdef REGISTER_MANUAL_PART_ResourceCache
    REGISTER_MANUAL_PART_ResourceCache(ResourceCache, "ResourceCache")
#endif
    RegisterSubclass<Object, ResourceCache>(engine, "Object", "ResourceCache");
    RegisterSubclass<RefCounted, ResourceCache>(engine, "RefCounted", "ResourceCache");

    // void ResourceWithMetadata::AddMetadata(const String& name, const Variant& value) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void AddMetadata(const String&in, const Variant&in)", AS_METHODPR(ResourceWithMetadata, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "void set_metadata(const String&in, const Variant&in)", AS_METHODPR(ResourceWithMetadata, AddMetadata, (const String&, const Variant&), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ResourceWithMetadata", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ResourceWithMetadata, AddRef, (), void), AS_CALL_THISCALL);
    // virtual bool Resource::BeginLoad(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool BeginLoad(Deserializer&)", AS_METHODPR(ResourceWithMetadata, BeginLoad, (Deserializer&), bool), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool EndLoad()", AS_METHODPR(ResourceWithMetadata, EndLoad, (), bool), AS_CALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "AsyncLoadState GetAsyncLoadState() const", AS_METHODPR(ResourceWithMetadata, GetAsyncLoadState, () const, AsyncLoadState), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool GetBlockEvents() const", AS_METHODPR(ResourceWithMetadata, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "const String& GetCategory() const", AS_METHODPR(ResourceWithMetadata, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "const String& get_category() const", AS_METHODPR(ResourceWithMetadata, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "VariantMap& GetEventDataMap() const", AS_METHODPR(ResourceWithMetadata, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "Object@+ GetEventSender() const", AS_METHODPR(ResourceWithMetadata, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ResourceWithMetadata, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ResourceWithMetadata, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ResourceWithMetadata, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "const VariantMap& get_globalVars() const", AS_METHODPR(ResourceWithMetadata, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "uint GetMemoryUse() const", AS_METHODPR(ResourceWithMetadata, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "uint get_memoryUse() const", AS_METHODPR(ResourceWithMetadata, GetMemoryUse, () const, unsigned), AS_CALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "const Variant& GetMetadata(const String&in) const", AS_METHODPR(ResourceWithMetadata, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "const Variant& get_metadata(const String&in) const", AS_METHODPR(ResourceWithMetadata, GetMetadata, (const String&) const, const Variant&), AS_CALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "const String& GetName() const", AS_METHODPR(ResourceWithMetadata, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "const String& get_name() const", AS_METHODPR(ResourceWithMetadata, GetName, () const, const String&), AS_CALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "StringHash GetNameHash() const", AS_METHODPR(ResourceWithMetadata, GetNameHash, () const, StringHash), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ResourceWithMetadata, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "StringHash GetType() const", AS_METHODPR(ResourceWithMetadata, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "StringHash get_type() const", AS_METHODPR(ResourceWithMetadata, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "const String& GetTypeName() const", AS_METHODPR(ResourceWithMetadata, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "const String& get_typeName() const", AS_METHODPR(ResourceWithMetadata, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "uint GetUseTimer()", AS_METHODPR(ResourceWithMetadata, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "uint get_useTimer()", AS_METHODPR(ResourceWithMetadata, GetUseTimer, (), unsigned), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool HasEventHandlers() const", AS_METHODPR(ResourceWithMetadata, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool HasMetadata() const", AS_METHODPR(ResourceWithMetadata, HasMetadata, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool get_hasMetadata() const", AS_METHODPR(ResourceWithMetadata, HasMetadata, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ResourceWithMetadata, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ResourceWithMetadata, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ResourceWithMetadata, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool Load(Deserializer&)", AS_METHODPR(ResourceWithMetadata, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool LoadFile(const String&in)", AS_METHODPR(ResourceWithMetadata, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool Load(const String&in)", AS_METHODPR(ResourceWithMetadata, LoadFile, (const String&), bool), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ResourceWithMetadata, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "int Refs() const", AS_METHODPR(ResourceWithMetadata, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "int get_refs() const", AS_METHODPR(ResourceWithMetadata, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ResourceWithMetadata", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ResourceWithMetadata, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void RemoveAllMetadata()", AS_METHODPR(ResourceWithMetadata, RemoveAllMetadata, (), void), AS_CALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void RemoveMetadata(const String&in)", AS_METHODPR(ResourceWithMetadata, RemoveMetadata, (const String&), void), AS_CALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void ResetUseTimer()", AS_METHODPR(ResourceWithMetadata, ResetUseTimer, (), void), AS_CALL_THISCALL);
    // explicit ResourceWithMetadata::ResourceWithMetadata(Context* context) | File: ../Resource/Resource.h
    engine->RegisterObjectBehaviour("ResourceWithMetadata", asBEHAVE_FACTORY, "ResourceWithMetadata@+ f()", AS_FUNCTION(ResourceWithMetadata_ResourceWithMetadata_Context), AS_CALL_CDECL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool Save(Serializer&) const", AS_METHODPR(ResourceWithMetadata, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool SaveFile(const String&in) const", AS_METHODPR(ResourceWithMetadata, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool Save(const String&in) const", AS_METHODPR(ResourceWithMetadata, SaveFile, (const String&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SendEvent(StringHash)", AS_METHODPR(ResourceWithMetadata, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ResourceWithMetadata, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SetAsyncLoadState(AsyncLoadState)", AS_METHODPR(ResourceWithMetadata, SetAsyncLoadState, (AsyncLoadState), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SetBlockEvents(bool)", AS_METHODPR(ResourceWithMetadata, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ResourceWithMetadata, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ResourceWithMetadata, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SetMemoryUse(uint)", AS_METHODPR(ResourceWithMetadata, SetMemoryUse, (unsigned), void), AS_CALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SetName(const String&in)", AS_METHODPR(ResourceWithMetadata, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "void set_name(const String&in)", AS_METHODPR(ResourceWithMetadata, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void UnsubscribeFromAllEvents()", AS_METHODPR(ResourceWithMetadata, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ResourceWithMetadata_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ResourceWithMetadata, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ResourceWithMetadata, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ResourceWithMetadata, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "int WeakRefs() const", AS_METHODPR(ResourceWithMetadata, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "int get_weakRefs() const", AS_METHODPR(ResourceWithMetadata, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Resource
    REGISTER_MANUAL_PART_Resource(ResourceWithMetadata, "ResourceWithMetadata")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ResourceWithMetadata, "ResourceWithMetadata")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ResourceWithMetadata, "ResourceWithMetadata")
#endif
#ifdef REGISTER_MANUAL_PART_ResourceWithMetadata
    REGISTER_MANUAL_PART_ResourceWithMetadata(ResourceWithMetadata, "ResourceWithMetadata")
#endif
    RegisterSubclass<Resource, ResourceWithMetadata>(engine, "Resource", "ResourceWithMetadata");
    RegisterSubclass<Object, ResourceWithMetadata>(engine, "Object", "ResourceWithMetadata");
    RegisterSubclass<RefCounted, ResourceWithMetadata>(engine, "RefCounted", "ResourceWithMetadata");

    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void AddLight(Light@+)", AS_METHODPR(RibbonTrail, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RibbonTrail", asBEHAVE_ADDREF, "void f()", AS_METHODPR(RibbonTrail, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void AddVertexLight(Light@+)", AS_METHODPR(RibbonTrail, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void AllocateNetworkState()", AS_METHODPR(RibbonTrail, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void ApplyAttributes()", AS_METHODPR(RibbonTrail, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void RibbonTrail::Commit() | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void Commit()", AS_METHODPR(RibbonTrail, Commit, (), void), AS_CALL_THISCALL);
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(RibbonTrail, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(RibbonTrail, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool GetAnimationEnabled() const", AS_METHODPR(RibbonTrail, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_animationEnabled() const", AS_METHODPR(RibbonTrail, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // float RibbonTrail::GetAnimationLodBias() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetAnimationLodBias() const", AS_METHODPR(RibbonTrail, GetAnimationLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_animationLodBias() const", AS_METHODPR(RibbonTrail, GetAnimationLodBias, () const, float), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "Variant GetAttribute(uint) const", AS_METHODPR(RibbonTrail, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "Variant get_attributes(uint) const", AS_METHODPR(RibbonTrail, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "Variant GetAttribute(const String&in) const", AS_METHODPR(RibbonTrail, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(RibbonTrail, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(RibbonTrail, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(RibbonTrail, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(RibbonTrail, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "Variant GetAttributeDefault(uint) const", AS_METHODPR(RibbonTrail, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "Variant get_attributeDefaults(uint) const", AS_METHODPR(RibbonTrail, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(RibbonTrail, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector3& RibbonTrail::GetBaseVelocity() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "const Vector3& GetBaseVelocity() const", AS_METHODPR(RibbonTrail, GetBaseVelocity, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const Vector3& get_baseVelocity() const", AS_METHODPR(RibbonTrail, GetBaseVelocity, () const, const Vector3&), AS_CALL_THISCALL);
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "bool GetBlockEvents() const", AS_METHODPR(RibbonTrail, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(RibbonTrail, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const BoundingBox& get_boundingBox() const", AS_METHODPR(RibbonTrail, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool GetCastShadows() const", AS_METHODPR(RibbonTrail, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_castShadows() const", AS_METHODPR(RibbonTrail, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "const String& GetCategory() const", AS_METHODPR(RibbonTrail, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const String& get_category() const", AS_METHODPR(RibbonTrail, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "Component@+ GetComponent(StringHash) const", AS_METHODPR(RibbonTrail, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetDistance() const", AS_METHODPR(RibbonTrail, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint8 GetDrawableFlags() const", AS_METHODPR(RibbonTrail, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetDrawDistance() const", AS_METHODPR(RibbonTrail, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_drawDistance() const", AS_METHODPR(RibbonTrail, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // const Color& RibbonTrail::GetEndColor() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "const Color& GetEndColor() const", AS_METHODPR(RibbonTrail, GetEndColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const Color& get_endColor() const", AS_METHODPR(RibbonTrail, GetEndColor, () const, const Color&), AS_CALL_THISCALL);
    // float RibbonTrail::GetEndScale() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetEndScale() const", AS_METHODPR(RibbonTrail, GetEndScale, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_endScale() const", AS_METHODPR(RibbonTrail, GetEndScale, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "VariantMap& GetEventDataMap() const", AS_METHODPR(RibbonTrail, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "Object@+ GetEventSender() const", AS_METHODPR(RibbonTrail, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "Light@+ GetFirstLight() const", AS_METHODPR(RibbonTrail, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(RibbonTrail, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(RibbonTrail, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "const VariantMap& GetGlobalVars() const", AS_METHODPR(RibbonTrail, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const VariantMap& get_globalVars() const", AS_METHODPR(RibbonTrail, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetID() const", AS_METHODPR(RibbonTrail, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_id() const", AS_METHODPR(RibbonTrail, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(RibbonTrail, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // float RibbonTrail::GetLifetime() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetLifetime() const", AS_METHODPR(RibbonTrail, GetLifetime, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_lifetime() const", AS_METHODPR(RibbonTrail, GetLifetime, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetLightMask() const", AS_METHODPR(RibbonTrail, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_lightMask() const", AS_METHODPR(RibbonTrail, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(RibbonTrail_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetLodBias() const", AS_METHODPR(RibbonTrail, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_lodBias() const", AS_METHODPR(RibbonTrail, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetLodDistance() const", AS_METHODPR(RibbonTrail, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(RibbonTrail, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // Material* RibbonTrail::GetMaterial() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "Material@+ GetMaterial() const", AS_METHODPR(RibbonTrail, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "Material@+ get_material() const", AS_METHODPR(RibbonTrail, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef RibbonTrail::GetMaterialAttr() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "ResourceRef GetMaterialAttr() const", AS_METHODPR(RibbonTrail, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetMaxLights() const", AS_METHODPR(RibbonTrail, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_maxLights() const", AS_METHODPR(RibbonTrail, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetMaxZ() const", AS_METHODPR(RibbonTrail, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetMinZ() const", AS_METHODPR(RibbonTrail, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "Node@+ GetNode() const", AS_METHODPR(RibbonTrail, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "Node@+ get_node() const", AS_METHODPR(RibbonTrail, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetNumAttributes() const", AS_METHODPR(RibbonTrail, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_numAttributes() const", AS_METHODPR(RibbonTrail, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetNumNetworkAttributes() const", AS_METHODPR(RibbonTrail, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetNumOccluderTriangles()", AS_METHODPR(RibbonTrail, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(RibbonTrail, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(RibbonTrail, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(RibbonTrail, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "Scene@+ GetScene() const", AS_METHODPR(RibbonTrail, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetShadowDistance() const", AS_METHODPR(RibbonTrail, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_shadowDistance() const", AS_METHODPR(RibbonTrail, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetShadowMask() const", AS_METHODPR(RibbonTrail, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_shadowMask() const", AS_METHODPR(RibbonTrail, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetSortValue() const", AS_METHODPR(RibbonTrail, GetSortValue, () const, float), AS_CALL_THISCALL);
    // const Color& RibbonTrail::GetStartColor() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "const Color& GetStartColor() const", AS_METHODPR(RibbonTrail, GetStartColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const Color& get_startColor() const", AS_METHODPR(RibbonTrail, GetStartColor, () const, const Color&), AS_CALL_THISCALL);
    // float RibbonTrail::GetStartScale() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetStartScale() const", AS_METHODPR(RibbonTrail, GetStartScale, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_startScale() const", AS_METHODPR(RibbonTrail, GetStartScale, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(RibbonTrail, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned RibbonTrail::GetTailColumn() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetTailColumn() const", AS_METHODPR(RibbonTrail, GetTailColumn, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_tailColumn() const", AS_METHODPR(RibbonTrail, GetTailColumn, () const, unsigned), AS_CALL_THISCALL);
    // TrailType RibbonTrail::GetTrailType() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "TrailType GetTrailType() const", AS_METHODPR(RibbonTrail, GetTrailType, () const, TrailType), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "TrailType get_trailType() const", AS_METHODPR(RibbonTrail, GetTrailType, () const, TrailType), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "StringHash GetType() const", AS_METHODPR(RibbonTrail, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "StringHash get_type() const", AS_METHODPR(RibbonTrail, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "const String& GetTypeName() const", AS_METHODPR(RibbonTrail, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const String& get_typeName() const", AS_METHODPR(RibbonTrail, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // UpdateGeometryType RibbonTrail::GetUpdateGeometryType() override | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(RibbonTrail, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // bool RibbonTrail::GetUpdateInvisible() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "bool GetUpdateInvisible() const", AS_METHODPR(RibbonTrail, GetUpdateInvisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_updateInvisible() const", AS_METHODPR(RibbonTrail, GetUpdateInvisible, () const, bool), AS_CALL_THISCALL);
    // float RibbonTrail::GetVertexDistance() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetVertexDistance() const", AS_METHODPR(RibbonTrail, GetVertexDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_vertexDistance() const", AS_METHODPR(RibbonTrail, GetVertexDistance, () const, float), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(RibbonTrail_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetViewMask() const", AS_METHODPR(RibbonTrail, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_viewMask() const", AS_METHODPR(RibbonTrail, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // float RibbonTrail::GetWidth() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetWidth() const", AS_METHODPR(RibbonTrail, GetWidth, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_width() const", AS_METHODPR(RibbonTrail, GetWidth, () const, float), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(RibbonTrail, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(RibbonTrail, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "Zone@+ GetZone() const", AS_METHODPR(RibbonTrail, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "Zone@+ get_zone() const", AS_METHODPR(RibbonTrail, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetZoneMask() const", AS_METHODPR(RibbonTrail, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_zoneMask() const", AS_METHODPR(RibbonTrail, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool HasBasePass(uint) const", AS_METHODPR(RibbonTrail, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "bool HasEventHandlers() const", AS_METHODPR(RibbonTrail, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(RibbonTrail, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(RibbonTrail, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool RibbonTrail::IsEmitting() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsEmitting() const", AS_METHODPR(RibbonTrail, IsEmitting, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_emitting() const", AS_METHODPR(RibbonTrail, IsEmitting, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsEnabled() const", AS_METHODPR(RibbonTrail, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_enabled() const", AS_METHODPR(RibbonTrail, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsEnabledEffective() const", AS_METHODPR(RibbonTrail, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_enabledEffective() const", AS_METHODPR(RibbonTrail, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsInstanceOf(StringHash) const", AS_METHODPR(RibbonTrail, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsInView() const", AS_METHODPR(RibbonTrail, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_inView() const", AS_METHODPR(RibbonTrail, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsInView(Camera@+) const", AS_METHODPR(RibbonTrail, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(RibbonTrail, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsOccludee() const", AS_METHODPR(RibbonTrail, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_occludee() const", AS_METHODPR(RibbonTrail, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsOccluder() const", AS_METHODPR(RibbonTrail, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_occluder() const", AS_METHODPR(RibbonTrail, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsReplicated() const", AS_METHODPR(RibbonTrail, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_replicated() const", AS_METHODPR(RibbonTrail, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool RibbonTrail::IsSorted() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsSorted() const", AS_METHODPR(RibbonTrail, IsSorted, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_sorted() const", AS_METHODPR(RibbonTrail, IsSorted, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsTemporary() const", AS_METHODPR(RibbonTrail, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_temporary() const", AS_METHODPR(RibbonTrail, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsZoneDirty() const", AS_METHODPR(RibbonTrail, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void LimitLights()", AS_METHODPR(RibbonTrail, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void LimitVertexLights(bool)", AS_METHODPR(RibbonTrail, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool Load(Deserializer&)", AS_METHODPR(RibbonTrail, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(RibbonTrail, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool LoadXML(const XMLElement&in)", AS_METHODPR(RibbonTrail, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void MarkForUpdate()", AS_METHODPR(RibbonTrail, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void MarkInView(const FrameInfo&in)", AS_METHODPR(RibbonTrail, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void MarkInView(uint)", AS_METHODPR(RibbonTrail, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "void MarkNetworkUpdate()", AS_METHODPR(RibbonTrail, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(RibbonTrail, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(RibbonTrail, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(RibbonTrail, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void RibbonTrail::OnSetEnabled() override | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void OnSetEnabled()", AS_METHODPR(RibbonTrail, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "void PrepareNetworkUpdate()", AS_METHODPR(RibbonTrail, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void RibbonTrail::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/RibbonTrail.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(RibbonTrail, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(RibbonTrail, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RibbonTrail", "int Refs() const", AS_METHODPR(RibbonTrail, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "int get_refs() const", AS_METHODPR(RibbonTrail, Refs, () const, int), AS_CALL_THISCALL);
    // static void RibbonTrail::RegisterObject(Context* context) | File: ../Graphics/RibbonTrail.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RibbonTrail", asBEHAVE_RELEASE, "void f()", AS_METHODPR(RibbonTrail, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "void Remove()", AS_METHODPR(RibbonTrail, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(RibbonTrail, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void RemoveInstanceDefault()", AS_METHODPR(RibbonTrail, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void RemoveObjectAnimation()", AS_METHODPR(RibbonTrail, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void ResetToDefault()", AS_METHODPR(RibbonTrail, ResetToDefault, (), void), AS_CALL_THISCALL);
    // explicit RibbonTrail::RibbonTrail(Context* context) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectBehaviour("RibbonTrail", asBEHAVE_FACTORY, "RibbonTrail@+ f()", AS_FUNCTION(RibbonTrail_RibbonTrail_Context), AS_CALL_CDECL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "bool Save(Serializer&) const", AS_METHODPR(RibbonTrail, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool SaveDefaultAttributes() const", AS_METHODPR(RibbonTrail, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "bool SaveJSON(JSONValue&) const", AS_METHODPR(RibbonTrail, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "bool SaveXML(XMLElement&) const", AS_METHODPR(RibbonTrail, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void SendEvent(StringHash)", AS_METHODPR(RibbonTrail, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(RibbonTrail, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAnimationEnabled(bool)", AS_METHODPR(RibbonTrail, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_animationEnabled(bool)", AS_METHODPR(RibbonTrail, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetAnimationLodBias(float bias) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAnimationLodBias(float)", AS_METHODPR(RibbonTrail, SetAnimationLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_animationLodBias(float)", AS_METHODPR(RibbonTrail, SetAnimationLodBias, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAnimationTime(float)", AS_METHODPR(RibbonTrail, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(RibbonTrail, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(RibbonTrail, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(RibbonTrail, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(RibbonTrail, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(RibbonTrail, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(RibbonTrail, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(RibbonTrail, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetBasePass(uint)", AS_METHODPR(RibbonTrail, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetBaseVelocity(const Vector3& baseVelocity) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetBaseVelocity(const Vector3&in)", AS_METHODPR(RibbonTrail, SetBaseVelocity, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_baseVelocity(const Vector3&in)", AS_METHODPR(RibbonTrail, SetBaseVelocity, (const Vector3&), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetBlockEvents(bool)", AS_METHODPR(RibbonTrail, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetCastShadows(bool)", AS_METHODPR(RibbonTrail, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_castShadows(bool)", AS_METHODPR(RibbonTrail, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetDrawDistance(float)", AS_METHODPR(RibbonTrail, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_drawDistance(float)", AS_METHODPR(RibbonTrail, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetEmitting(bool emitting) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetEmitting(bool)", AS_METHODPR(RibbonTrail, SetEmitting, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_emitting(bool)", AS_METHODPR(RibbonTrail, SetEmitting, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetEnabled(bool)", AS_METHODPR(RibbonTrail, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_enabled(bool)", AS_METHODPR(RibbonTrail, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetEndColor(const Color& color) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetEndColor(const Color&in)", AS_METHODPR(RibbonTrail, SetEndColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_endColor(const Color&in)", AS_METHODPR(RibbonTrail, SetEndColor, (const Color&), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetEndScale(float endScale) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetEndScale(float)", AS_METHODPR(RibbonTrail, SetEndScale, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_endScale(float)", AS_METHODPR(RibbonTrail, SetEndScale, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(RibbonTrail, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(RibbonTrail, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetInstanceDefault(bool)", AS_METHODPR(RibbonTrail, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(RibbonTrail, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetLifetime(float time) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetLifetime(float)", AS_METHODPR(RibbonTrail, SetLifetime, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_lifetime(float)", AS_METHODPR(RibbonTrail, SetLifetime, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetLightMask(uint)", AS_METHODPR(RibbonTrail, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_lightMask(uint)", AS_METHODPR(RibbonTrail, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetLodBias(float)", AS_METHODPR(RibbonTrail, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_lodBias(float)", AS_METHODPR(RibbonTrail, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetMaterial(Material* material) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetMaterial(Material@+)", AS_METHODPR(RibbonTrail, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_material(Material@+)", AS_METHODPR(RibbonTrail, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetMaterialAttr(const ResourceRef& value) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(RibbonTrail, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetMaxLights(uint)", AS_METHODPR(RibbonTrail, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_maxLights(uint)", AS_METHODPR(RibbonTrail, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetMinMaxZ(float, float)", AS_METHODPR(RibbonTrail, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(RibbonTrail, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(RibbonTrail, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(RibbonTrail, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetOccludee(bool)", AS_METHODPR(RibbonTrail, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_occludee(bool)", AS_METHODPR(RibbonTrail, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetOccluder(bool)", AS_METHODPR(RibbonTrail, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_occluder(bool)", AS_METHODPR(RibbonTrail, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetShadowDistance(float)", AS_METHODPR(RibbonTrail, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_shadowDistance(float)", AS_METHODPR(RibbonTrail, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetShadowMask(uint)", AS_METHODPR(RibbonTrail, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_shadowMask(uint)", AS_METHODPR(RibbonTrail, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetSorted(bool enable) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetSorted(bool)", AS_METHODPR(RibbonTrail, SetSorted, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_sorted(bool)", AS_METHODPR(RibbonTrail, SetSorted, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetSortValue(float)", AS_METHODPR(RibbonTrail, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetStartColor(const Color& color) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetStartColor(const Color&in)", AS_METHODPR(RibbonTrail, SetStartColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_startColor(const Color&in)", AS_METHODPR(RibbonTrail, SetStartColor, (const Color&), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetStartScale(float startScale) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetStartScale(float)", AS_METHODPR(RibbonTrail, SetStartScale, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_startScale(float)", AS_METHODPR(RibbonTrail, SetStartScale, (float), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetTailColumn(unsigned tailColumn) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetTailColumn(uint)", AS_METHODPR(RibbonTrail, SetTailColumn, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_tailColumn(uint)", AS_METHODPR(RibbonTrail, SetTailColumn, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetTemporary(bool)", AS_METHODPR(RibbonTrail, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_temporary(bool)", AS_METHODPR(RibbonTrail, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetTrailType(TrailType type) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetTrailType(TrailType)", AS_METHODPR(RibbonTrail, SetTrailType, (TrailType), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_trailType(TrailType)", AS_METHODPR(RibbonTrail, SetTrailType, (TrailType), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetUpdateInvisible(bool enable) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetUpdateInvisible(bool)", AS_METHODPR(RibbonTrail, SetUpdateInvisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_updateInvisible(bool)", AS_METHODPR(RibbonTrail, SetUpdateInvisible, (bool), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetVertexDistance(float length) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetVertexDistance(float)", AS_METHODPR(RibbonTrail, SetVertexDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_vertexDistance(float)", AS_METHODPR(RibbonTrail, SetVertexDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetViewMask(uint)", AS_METHODPR(RibbonTrail, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_viewMask(uint)", AS_METHODPR(RibbonTrail, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void RibbonTrail::SetWidth(float width) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetWidth(float)", AS_METHODPR(RibbonTrail, SetWidth, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_width(float)", AS_METHODPR(RibbonTrail, SetWidth, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetZone(Zone@+, bool = false)", AS_METHODPR(RibbonTrail, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetZoneMask(uint)", AS_METHODPR(RibbonTrail, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_zoneMask(uint)", AS_METHODPR(RibbonTrail, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void UnsubscribeFromAllEvents()", AS_METHODPR(RibbonTrail, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(RibbonTrail_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(RibbonTrail, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(RibbonTrail, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(RibbonTrail, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void RibbonTrail::Update(const FrameInfo& frame) override | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void Update(const FrameInfo&in)", AS_METHODPR(RibbonTrail, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void RibbonTrail::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(RibbonTrail, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void RibbonTrail::UpdateGeometry(const FrameInfo& frame) override | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(RibbonTrail, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RibbonTrail", "int WeakRefs() const", AS_METHODPR(RibbonTrail, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "int get_weakRefs() const", AS_METHODPR(RibbonTrail, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(RibbonTrail, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(RibbonTrail, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(RibbonTrail, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(RibbonTrail, "RibbonTrail")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(RibbonTrail, "RibbonTrail")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(RibbonTrail, "RibbonTrail")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(RibbonTrail, "RibbonTrail")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(RibbonTrail, "RibbonTrail")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(RibbonTrail, "RibbonTrail")
#endif
#ifdef REGISTER_MANUAL_PART_RibbonTrail
    REGISTER_MANUAL_PART_RibbonTrail(RibbonTrail, "RibbonTrail")
#endif
    RegisterSubclass<Drawable, RibbonTrail>(engine, "Drawable", "RibbonTrail");
    RegisterSubclass<Component, RibbonTrail>(engine, "Component", "RibbonTrail");
    RegisterSubclass<Animatable, RibbonTrail>(engine, "Animatable", "RibbonTrail");
    RegisterSubclass<Serializable, RibbonTrail>(engine, "Serializable", "RibbonTrail");
    RegisterSubclass<Object, RibbonTrail>(engine, "Object", "RibbonTrail");
    RegisterSubclass<RefCounted, RibbonTrail>(engine, "RefCounted", "RibbonTrail");

#ifdef URHO3D_PHYSICS
    // void RigidBody::Activate() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void Activate()", AS_METHODPR(RigidBody, Activate, (), void), AS_CALL_THISCALL);
    // void RigidBody::AddConstraint(Constraint* constraint) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void AddConstraint(Constraint@+)", AS_METHODPR(RigidBody, AddConstraint, (Constraint*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RigidBody", asBEHAVE_ADDREF, "void f()", AS_METHODPR(RigidBody, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void AllocateNetworkState()", AS_METHODPR(RigidBody, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void RigidBody::ApplyAttributes() override | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyAttributes()", AS_METHODPR(RigidBody, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void RigidBody::ApplyForce(const Vector3& force) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyForce(const Vector3&in)", AS_METHODPR(RigidBody, ApplyForce, (const Vector3&), void), AS_CALL_THISCALL);
    // void RigidBody::ApplyForce(const Vector3& force, const Vector3& position) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyForce(const Vector3&in, const Vector3&in)", AS_METHODPR(RigidBody, ApplyForce, (const Vector3&, const Vector3&), void), AS_CALL_THISCALL);
    // void RigidBody::ApplyImpulse(const Vector3& impulse) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyImpulse(const Vector3&in)", AS_METHODPR(RigidBody, ApplyImpulse, (const Vector3&), void), AS_CALL_THISCALL);
    // void RigidBody::ApplyImpulse(const Vector3& impulse, const Vector3& position) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyImpulse(const Vector3&in, const Vector3&in)", AS_METHODPR(RigidBody, ApplyImpulse, (const Vector3&, const Vector3&), void), AS_CALL_THISCALL);
    // void RigidBody::ApplyTorque(const Vector3& torque) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyTorque(const Vector3&in)", AS_METHODPR(RigidBody, ApplyTorque, (const Vector3&), void), AS_CALL_THISCALL);
    // void RigidBody::ApplyTorqueImpulse(const Vector3& torque) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyTorqueImpulse(const Vector3&in)", AS_METHODPR(RigidBody, ApplyTorqueImpulse, (const Vector3&), void), AS_CALL_THISCALL);
    // void RigidBody::ApplyWorldTransform(const Vector3& newWorldPosition, const Quaternion& newWorldRotation) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyWorldTransform(const Vector3&in, const Quaternion&in)", AS_METHODPR(RigidBody, ApplyWorldTransform, (const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void RigidBody::DisableMassUpdate() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void DisableMassUpdate()", AS_METHODPR(RigidBody, DisableMassUpdate, (), void), AS_CALL_THISCALL);
    // void RigidBody::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(RigidBody, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // void RigidBody::EnableMassUpdate() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void EnableMassUpdate()", AS_METHODPR(RigidBody, EnableMassUpdate, (), void), AS_CALL_THISCALL);
    // float RigidBody::GetAngularDamping() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetAngularDamping() const", AS_METHODPR(RigidBody, GetAngularDamping, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_angularDamping() const", AS_METHODPR(RigidBody, GetAngularDamping, () const, float), AS_CALL_THISCALL);
    // Vector3 RigidBody::GetAngularFactor() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetAngularFactor() const", AS_METHODPR(RigidBody, GetAngularFactor, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_angularFactor() const", AS_METHODPR(RigidBody, GetAngularFactor, () const, Vector3), AS_CALL_THISCALL);
    // float RigidBody::GetAngularRestThreshold() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetAngularRestThreshold() const", AS_METHODPR(RigidBody, GetAngularRestThreshold, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_angularRestThreshold() const", AS_METHODPR(RigidBody, GetAngularRestThreshold, () const, float), AS_CALL_THISCALL);
    // Vector3 RigidBody::GetAngularVelocity() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetAngularVelocity() const", AS_METHODPR(RigidBody, GetAngularVelocity, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_angularVelocity() const", AS_METHODPR(RigidBody, GetAngularVelocity, () const, Vector3), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "bool GetAnimationEnabled() const", AS_METHODPR(RigidBody, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_animationEnabled() const", AS_METHODPR(RigidBody, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Vector3 RigidBody::GetAnisotropicFriction() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetAnisotropicFriction() const", AS_METHODPR(RigidBody, GetAnisotropicFriction, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_anisotropicFriction() const", AS_METHODPR(RigidBody, GetAnisotropicFriction, () const, Vector3), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "Variant GetAttribute(uint) const", AS_METHODPR(RigidBody, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Variant get_attributes(uint) const", AS_METHODPR(RigidBody, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "Variant GetAttribute(const String&in) const", AS_METHODPR(RigidBody, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(RigidBody, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(RigidBody, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(RigidBody, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(RigidBody, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "Variant GetAttributeDefault(uint) const", AS_METHODPR(RigidBody, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Variant get_attributeDefaults(uint) const", AS_METHODPR(RigidBody, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(RigidBody, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "bool GetBlockEvents() const", AS_METHODPR(RigidBody, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // btRigidBody* RigidBody::GetBody() const | File: ../Physics/RigidBody.h
    // Error: type "btRigidBody*" can not automatically bind
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "const String& GetCategory() const", AS_METHODPR(RigidBody, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const String& get_category() const", AS_METHODPR(RigidBody, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // float RigidBody::GetCcdMotionThreshold() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetCcdMotionThreshold() const", AS_METHODPR(RigidBody, GetCcdMotionThreshold, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_ccdMotionThreshold() const", AS_METHODPR(RigidBody, GetCcdMotionThreshold, () const, float), AS_CALL_THISCALL);
    // float RigidBody::GetCcdRadius() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetCcdRadius() const", AS_METHODPR(RigidBody, GetCcdRadius, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_ccdRadius() const", AS_METHODPR(RigidBody, GetCcdRadius, () const, float), AS_CALL_THISCALL);
    // const Vector3& RigidBody::GetCenterOfMass() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "const Vector3& GetCenterOfMass() const", AS_METHODPR(RigidBody, GetCenterOfMass, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const Vector3& get_centerOfMass() const", AS_METHODPR(RigidBody, GetCenterOfMass, () const, const Vector3&), AS_CALL_THISCALL);
    // void RigidBody::GetCollidingBodies(PODVector<RigidBody*>& result) const | File: ../Physics/RigidBody.h
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // CollisionEventMode RigidBody::GetCollisionEventMode() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "CollisionEventMode GetCollisionEventMode() const", AS_METHODPR(RigidBody, GetCollisionEventMode, () const, CollisionEventMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "CollisionEventMode get_collisionEventMode() const", AS_METHODPR(RigidBody, GetCollisionEventMode, () const, CollisionEventMode), AS_CALL_THISCALL);
    // unsigned RigidBody::GetCollisionLayer() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "uint GetCollisionLayer() const", AS_METHODPR(RigidBody, GetCollisionLayer, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint get_collisionLayer() const", AS_METHODPR(RigidBody, GetCollisionLayer, () const, unsigned), AS_CALL_THISCALL);
    // unsigned RigidBody::GetCollisionMask() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "uint GetCollisionMask() const", AS_METHODPR(RigidBody, GetCollisionMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint get_collisionMask() const", AS_METHODPR(RigidBody, GetCollisionMask, () const, unsigned), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "Component@+ GetComponent(StringHash) const", AS_METHODPR(RigidBody, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // btCompoundShape* RigidBody::GetCompoundShape() const | File: ../Physics/RigidBody.h
    // Error: type "btCompoundShape*" can not automatically bind
    // float RigidBody::GetContactProcessingThreshold() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetContactProcessingThreshold() const", AS_METHODPR(RigidBody, GetContactProcessingThreshold, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_contactProcessingThreshold() const", AS_METHODPR(RigidBody, GetContactProcessingThreshold, () const, float), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "VariantMap& GetEventDataMap() const", AS_METHODPR(RigidBody, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "Object@+ GetEventSender() const", AS_METHODPR(RigidBody, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // float RigidBody::GetFriction() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetFriction() const", AS_METHODPR(RigidBody, GetFriction, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_friction() const", AS_METHODPR(RigidBody, GetFriction, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(RigidBody, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(RigidBody, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "const VariantMap& GetGlobalVars() const", AS_METHODPR(RigidBody, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const VariantMap& get_globalVars() const", AS_METHODPR(RigidBody, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // const Vector3& RigidBody::GetGravityOverride() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "const Vector3& GetGravityOverride() const", AS_METHODPR(RigidBody, GetGravityOverride, () const, const Vector3&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const Vector3& get_gravityOverride() const", AS_METHODPR(RigidBody, GetGravityOverride, () const, const Vector3&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "uint GetID() const", AS_METHODPR(RigidBody, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint get_id() const", AS_METHODPR(RigidBody, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(RigidBody, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // float RigidBody::GetLinearDamping() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetLinearDamping() const", AS_METHODPR(RigidBody, GetLinearDamping, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_linearDamping() const", AS_METHODPR(RigidBody, GetLinearDamping, () const, float), AS_CALL_THISCALL);
    // Vector3 RigidBody::GetLinearFactor() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetLinearFactor() const", AS_METHODPR(RigidBody, GetLinearFactor, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_linearFactor() const", AS_METHODPR(RigidBody, GetLinearFactor, () const, Vector3), AS_CALL_THISCALL);
    // float RigidBody::GetLinearRestThreshold() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetLinearRestThreshold() const", AS_METHODPR(RigidBody, GetLinearRestThreshold, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_linearRestThreshold() const", AS_METHODPR(RigidBody, GetLinearRestThreshold, () const, float), AS_CALL_THISCALL);
    // Vector3 RigidBody::GetLinearVelocity() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetLinearVelocity() const", AS_METHODPR(RigidBody, GetLinearVelocity, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_linearVelocity() const", AS_METHODPR(RigidBody, GetLinearVelocity, () const, Vector3), AS_CALL_THISCALL);
    // float RigidBody::GetMass() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetMass() const", AS_METHODPR(RigidBody, GetMass, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_mass() const", AS_METHODPR(RigidBody, GetMass, () const, float), AS_CALL_THISCALL);
    // const PODVector<unsigned char>& RigidBody::GetNetAngularVelocityAttr() const | File: ../Physics/RigidBody.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "Node@+ GetNode() const", AS_METHODPR(RigidBody, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Node@+ get_node() const", AS_METHODPR(RigidBody, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "uint GetNumAttributes() const", AS_METHODPR(RigidBody, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint get_numAttributes() const", AS_METHODPR(RigidBody, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "uint GetNumNetworkAttributes() const", AS_METHODPR(RigidBody, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(RigidBody, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(RigidBody, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(RigidBody, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // PhysicsWorld* RigidBody::GetPhysicsWorld() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "PhysicsWorld@+ GetPhysicsWorld() const", AS_METHODPR(RigidBody, GetPhysicsWorld, () const, PhysicsWorld*), AS_CALL_THISCALL);
    // Vector3 RigidBody::GetPosition() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetPosition() const", AS_METHODPR(RigidBody, GetPosition, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_position() const", AS_METHODPR(RigidBody, GetPosition, () const, Vector3), AS_CALL_THISCALL);
    // float RigidBody::GetRestitution() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetRestitution() const", AS_METHODPR(RigidBody, GetRestitution, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_restitution() const", AS_METHODPR(RigidBody, GetRestitution, () const, float), AS_CALL_THISCALL);
    // float RigidBody::GetRollingFriction() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetRollingFriction() const", AS_METHODPR(RigidBody, GetRollingFriction, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_rollingFriction() const", AS_METHODPR(RigidBody, GetRollingFriction, () const, float), AS_CALL_THISCALL);
    // Quaternion RigidBody::GetRotation() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Quaternion GetRotation() const", AS_METHODPR(RigidBody, GetRotation, () const, Quaternion), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Quaternion get_rotation() const", AS_METHODPR(RigidBody, GetRotation, () const, Quaternion), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "Scene@+ GetScene() const", AS_METHODPR(RigidBody, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(RigidBody, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "StringHash GetType() const", AS_METHODPR(RigidBody, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "StringHash get_type() const", AS_METHODPR(RigidBody, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "const String& GetTypeName() const", AS_METHODPR(RigidBody, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const String& get_typeName() const", AS_METHODPR(RigidBody, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool RigidBody::GetUseGravity() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "bool GetUseGravity() const", AS_METHODPR(RigidBody, GetUseGravity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_useGravity() const", AS_METHODPR(RigidBody, GetUseGravity, () const, bool), AS_CALL_THISCALL);
    // Vector3 RigidBody::GetVelocityAtPoint(const Vector3& position) const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetVelocityAtPoint(const Vector3&in) const", AS_METHODPR(RigidBody, GetVelocityAtPoint, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // void RigidBody::getWorldTransform(btTransform& worldTrans) const override | File: ../Physics/RigidBody.h
    // Not registered because have @nobind mark
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "bool HasEventHandlers() const", AS_METHODPR(RigidBody, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(RigidBody, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(RigidBody, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool RigidBody::IsActive() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "bool IsActive() const", AS_METHODPR(RigidBody, IsActive, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_active() const", AS_METHODPR(RigidBody, IsActive, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "bool IsEnabled() const", AS_METHODPR(RigidBody, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_enabled() const", AS_METHODPR(RigidBody, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "bool IsEnabledEffective() const", AS_METHODPR(RigidBody, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_enabledEffective() const", AS_METHODPR(RigidBody, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "bool IsInstanceOf(StringHash) const", AS_METHODPR(RigidBody, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool RigidBody::IsKinematic() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "bool IsKinematic() const", AS_METHODPR(RigidBody, IsKinematic, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_kinematic() const", AS_METHODPR(RigidBody, IsKinematic, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "bool IsReplicated() const", AS_METHODPR(RigidBody, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_replicated() const", AS_METHODPR(RigidBody, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool IsTemporary() const", AS_METHODPR(RigidBody, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_temporary() const", AS_METHODPR(RigidBody, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool RigidBody::IsTrigger() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "bool IsTrigger() const", AS_METHODPR(RigidBody, IsTrigger, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_trigger() const", AS_METHODPR(RigidBody, IsTrigger, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool Load(Deserializer&)", AS_METHODPR(RigidBody, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(RigidBody, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "bool LoadXML(const XMLElement&in)", AS_METHODPR(RigidBody, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "void MarkNetworkUpdate()", AS_METHODPR(RigidBody, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(RigidBody, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(RigidBody, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(RigidBody, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void RigidBody::OnSetEnabled() override | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void OnSetEnabled()", AS_METHODPR(RigidBody, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "void PrepareNetworkUpdate()", AS_METHODPR(RigidBody, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void RigidBody::ReAddBodyToWorld() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ReAddBodyToWorld()", AS_METHODPR(RigidBody, ReAddBodyToWorld, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(RigidBody, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(RigidBody, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RigidBody", "int Refs() const", AS_METHODPR(RigidBody, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "int get_refs() const", AS_METHODPR(RigidBody, Refs, () const, int), AS_CALL_THISCALL);
    // static void RigidBody::RegisterObject(Context* context) | File: ../Physics/RigidBody.h
    // Not registered because have @nobind mark
    // void RigidBody::ReleaseBody() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ReleaseBody()", AS_METHODPR(RigidBody, ReleaseBody, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RigidBody", asBEHAVE_RELEASE, "void f()", AS_METHODPR(RigidBody, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "void Remove()", AS_METHODPR(RigidBody, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(RigidBody, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void RigidBody::RemoveConstraint(Constraint* constraint) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void RemoveConstraint(Constraint@+)", AS_METHODPR(RigidBody, RemoveConstraint, (Constraint*), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void RemoveInstanceDefault()", AS_METHODPR(RigidBody, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void RemoveObjectAnimation()", AS_METHODPR(RigidBody, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void RigidBody::ResetForces() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ResetForces()", AS_METHODPR(RigidBody, ResetForces, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void ResetToDefault()", AS_METHODPR(RigidBody, ResetToDefault, (), void), AS_CALL_THISCALL);
    // explicit RigidBody::RigidBody(Context* context) | File: ../Physics/RigidBody.h
    engine->RegisterObjectBehaviour("RigidBody", asBEHAVE_FACTORY, "RigidBody@+ f()", AS_FUNCTION(RigidBody_RigidBody_Context), AS_CALL_CDECL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "bool Save(Serializer&) const", AS_METHODPR(RigidBody, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool SaveDefaultAttributes() const", AS_METHODPR(RigidBody, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "bool SaveJSON(JSONValue&) const", AS_METHODPR(RigidBody, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "bool SaveXML(XMLElement&) const", AS_METHODPR(RigidBody, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void SendEvent(StringHash)", AS_METHODPR(RigidBody, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(RigidBody, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void RigidBody::SetAngularDamping(float damping) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetAngularDamping(float)", AS_METHODPR(RigidBody, SetAngularDamping, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularDamping(float)", AS_METHODPR(RigidBody, SetAngularDamping, (float), void), AS_CALL_THISCALL);
    // void RigidBody::SetAngularFactor(const Vector3& factor) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetAngularFactor(const Vector3&in)", AS_METHODPR(RigidBody, SetAngularFactor, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularFactor(const Vector3&in)", AS_METHODPR(RigidBody, SetAngularFactor, (const Vector3&), void), AS_CALL_THISCALL);
    // void RigidBody::SetAngularRestThreshold(float threshold) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetAngularRestThreshold(float)", AS_METHODPR(RigidBody, SetAngularRestThreshold, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularRestThreshold(float)", AS_METHODPR(RigidBody, SetAngularRestThreshold, (float), void), AS_CALL_THISCALL);
    // void RigidBody::SetAngularVelocity(const Vector3& velocity) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetAngularVelocity(const Vector3&in)", AS_METHODPR(RigidBody, SetAngularVelocity, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularVelocity(const Vector3&in)", AS_METHODPR(RigidBody, SetAngularVelocity, (const Vector3&), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetAnimationEnabled(bool)", AS_METHODPR(RigidBody, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_animationEnabled(bool)", AS_METHODPR(RigidBody, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetAnimationTime(float)", AS_METHODPR(RigidBody, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void RigidBody::SetAnisotropicFriction(const Vector3& friction) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetAnisotropicFriction(const Vector3&in)", AS_METHODPR(RigidBody, SetAnisotropicFriction, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_anisotropicFriction(const Vector3&in)", AS_METHODPR(RigidBody, SetAnisotropicFriction, (const Vector3&), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(RigidBody, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(RigidBody, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(RigidBody, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(RigidBody, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(RigidBody, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(RigidBody, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(RigidBody, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void SetBlockEvents(bool)", AS_METHODPR(RigidBody, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void RigidBody::SetCcdMotionThreshold(float threshold) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetCcdMotionThreshold(float)", AS_METHODPR(RigidBody, SetCcdMotionThreshold, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_ccdMotionThreshold(float)", AS_METHODPR(RigidBody, SetCcdMotionThreshold, (float), void), AS_CALL_THISCALL);
    // void RigidBody::SetCcdRadius(float radius) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetCcdRadius(float)", AS_METHODPR(RigidBody, SetCcdRadius, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_ccdRadius(float)", AS_METHODPR(RigidBody, SetCcdRadius, (float), void), AS_CALL_THISCALL);
    // void RigidBody::SetCollisionEventMode(CollisionEventMode mode) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetCollisionEventMode(CollisionEventMode)", AS_METHODPR(RigidBody, SetCollisionEventMode, (CollisionEventMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_collisionEventMode(CollisionEventMode)", AS_METHODPR(RigidBody, SetCollisionEventMode, (CollisionEventMode), void), AS_CALL_THISCALL);
    // void RigidBody::SetCollisionLayer(unsigned layer) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetCollisionLayer(uint)", AS_METHODPR(RigidBody, SetCollisionLayer, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_collisionLayer(uint)", AS_METHODPR(RigidBody, SetCollisionLayer, (unsigned), void), AS_CALL_THISCALL);
    // void RigidBody::SetCollisionLayerAndMask(unsigned layer, unsigned mask) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetCollisionLayerAndMask(uint, uint)", AS_METHODPR(RigidBody, SetCollisionLayerAndMask, (unsigned, unsigned), void), AS_CALL_THISCALL);
    // void RigidBody::SetCollisionMask(unsigned mask) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetCollisionMask(uint)", AS_METHODPR(RigidBody, SetCollisionMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_collisionMask(uint)", AS_METHODPR(RigidBody, SetCollisionMask, (unsigned), void), AS_CALL_THISCALL);
    // void RigidBody::SetContactProcessingThreshold(float threshold) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetContactProcessingThreshold(float)", AS_METHODPR(RigidBody, SetContactProcessingThreshold, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_contactProcessingThreshold(float)", AS_METHODPR(RigidBody, SetContactProcessingThreshold, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "void SetEnabled(bool)", AS_METHODPR(RigidBody, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_enabled(bool)", AS_METHODPR(RigidBody, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void RigidBody::SetFriction(float friction) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetFriction(float)", AS_METHODPR(RigidBody, SetFriction, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_friction(float)", AS_METHODPR(RigidBody, SetFriction, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(RigidBody, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(RigidBody, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void RigidBody::SetGravityOverride(const Vector3& gravity) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetGravityOverride(const Vector3&in)", AS_METHODPR(RigidBody, SetGravityOverride, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_gravityOverride(const Vector3&in)", AS_METHODPR(RigidBody, SetGravityOverride, (const Vector3&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void SetInstanceDefault(bool)", AS_METHODPR(RigidBody, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(RigidBody, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void RigidBody::SetKinematic(bool enable) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetKinematic(bool)", AS_METHODPR(RigidBody, SetKinematic, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_kinematic(bool)", AS_METHODPR(RigidBody, SetKinematic, (bool), void), AS_CALL_THISCALL);
    // void RigidBody::SetLinearDamping(float damping) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetLinearDamping(float)", AS_METHODPR(RigidBody, SetLinearDamping, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearDamping(float)", AS_METHODPR(RigidBody, SetLinearDamping, (float), void), AS_CALL_THISCALL);
    // void RigidBody::SetLinearFactor(const Vector3& factor) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetLinearFactor(const Vector3&in)", AS_METHODPR(RigidBody, SetLinearFactor, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearFactor(const Vector3&in)", AS_METHODPR(RigidBody, SetLinearFactor, (const Vector3&), void), AS_CALL_THISCALL);
    // void RigidBody::SetLinearRestThreshold(float threshold) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetLinearRestThreshold(float)", AS_METHODPR(RigidBody, SetLinearRestThreshold, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearRestThreshold(float)", AS_METHODPR(RigidBody, SetLinearRestThreshold, (float), void), AS_CALL_THISCALL);
    // void RigidBody::SetLinearVelocity(const Vector3& velocity) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetLinearVelocity(const Vector3&in)", AS_METHODPR(RigidBody, SetLinearVelocity, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearVelocity(const Vector3&in)", AS_METHODPR(RigidBody, SetLinearVelocity, (const Vector3&), void), AS_CALL_THISCALL);
    // void RigidBody::SetMass(float mass) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetMass(float)", AS_METHODPR(RigidBody, SetMass, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_mass(float)", AS_METHODPR(RigidBody, SetMass, (float), void), AS_CALL_THISCALL);
    // void RigidBody::SetNetAngularVelocityAttr(const PODVector<unsigned char>& value) | File: ../Physics/RigidBody.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(RigidBody, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(RigidBody, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(RigidBody, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void RigidBody::SetPosition(const Vector3& position) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetPosition(const Vector3&in)", AS_METHODPR(RigidBody, SetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_position(const Vector3&in)", AS_METHODPR(RigidBody, SetPosition, (const Vector3&), void), AS_CALL_THISCALL);
    // void RigidBody::SetRestitution(float restitution) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetRestitution(float)", AS_METHODPR(RigidBody, SetRestitution, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_restitution(float)", AS_METHODPR(RigidBody, SetRestitution, (float), void), AS_CALL_THISCALL);
    // void RigidBody::SetRollingFriction(float friction) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetRollingFriction(float)", AS_METHODPR(RigidBody, SetRollingFriction, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_rollingFriction(float)", AS_METHODPR(RigidBody, SetRollingFriction, (float), void), AS_CALL_THISCALL);
    // void RigidBody::SetRotation(const Quaternion& rotation) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetRotation(const Quaternion&in)", AS_METHODPR(RigidBody, SetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_rotation(const Quaternion&in)", AS_METHODPR(RigidBody, SetRotation, (const Quaternion&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void SetTemporary(bool)", AS_METHODPR(RigidBody, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_temporary(bool)", AS_METHODPR(RigidBody, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void RigidBody::SetTransform(const Vector3& position, const Quaternion& rotation) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetTransform(const Vector3&in, const Quaternion&in)", AS_METHODPR(RigidBody, SetTransform, (const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // void RigidBody::SetTrigger(bool enable) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetTrigger(bool)", AS_METHODPR(RigidBody, SetTrigger, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_trigger(bool)", AS_METHODPR(RigidBody, SetTrigger, (bool), void), AS_CALL_THISCALL);
    // void RigidBody::SetUseGravity(bool enable) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetUseGravity(bool)", AS_METHODPR(RigidBody, SetUseGravity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_useGravity(bool)", AS_METHODPR(RigidBody, SetUseGravity, (bool), void), AS_CALL_THISCALL);
    // void RigidBody::setWorldTransform(const btTransform& worldTrans) override | File: ../Physics/RigidBody.h
    // Not registered because have @nobind mark
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void UnsubscribeFromAllEvents()", AS_METHODPR(RigidBody, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(RigidBody_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(RigidBody, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(RigidBody, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(RigidBody, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void RigidBody::UpdateGravity() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void UpdateGravity()", AS_METHODPR(RigidBody, UpdateGravity, (), void), AS_CALL_THISCALL);
    // void RigidBody::UpdateMass() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void UpdateMass()", AS_METHODPR(RigidBody, UpdateMass, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RigidBody", "int WeakRefs() const", AS_METHODPR(RigidBody, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "int get_weakRefs() const", AS_METHODPR(RigidBody, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(RigidBody, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(RigidBody, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(RigidBody, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(RigidBody, "RigidBody")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(RigidBody, "RigidBody")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(RigidBody, "RigidBody")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(RigidBody, "RigidBody")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(RigidBody, "RigidBody")
#endif
#ifdef REGISTER_MANUAL_PART_RigidBody
    REGISTER_MANUAL_PART_RigidBody(RigidBody, "RigidBody")
#endif
    RegisterSubclass<Component, RigidBody>(engine, "Component", "RigidBody");
    RegisterSubclass<Animatable, RigidBody>(engine, "Animatable", "RigidBody");
    RegisterSubclass<Serializable, RigidBody>(engine, "Serializable", "RigidBody");
    RegisterSubclass<Object, RigidBody>(engine, "Object", "RigidBody");
    RegisterSubclass<RefCounted, RigidBody>(engine, "RefCounted", "RigidBody");
#endif

#ifdef URHO3D_URHO2D
    // void RigidBody2D::AddCollisionShape2D(CollisionShape2D* collisionShape) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void AddCollisionShape2D(CollisionShape2D@+)", AS_METHODPR(RigidBody2D, AddCollisionShape2D, (CollisionShape2D*), void), AS_CALL_THISCALL);
    // void RigidBody2D::AddConstraint2D(Constraint2D* constraint) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void AddConstraint2D(Constraint2D@+)", AS_METHODPR(RigidBody2D, AddConstraint2D, (Constraint2D*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RigidBody2D", asBEHAVE_ADDREF, "void f()", AS_METHODPR(RigidBody2D, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void AllocateNetworkState()", AS_METHODPR(RigidBody2D, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void RigidBody2D::ApplyAngularImpulse(float impulse, bool wake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyAngularImpulse(float, bool)", AS_METHODPR(RigidBody2D, ApplyAngularImpulse, (float, bool), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyAttributes()", AS_METHODPR(RigidBody2D, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void RigidBody2D::ApplyForce(const Vector2& force, const Vector2& point, bool wake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyForce(const Vector2&in, const Vector2&in, bool)", AS_METHODPR(RigidBody2D, ApplyForce, (const Vector2&, const Vector2&, bool), void), AS_CALL_THISCALL);
    // void RigidBody2D::ApplyForceToCenter(const Vector2& force, bool wake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyForceToCenter(const Vector2&in, bool)", AS_METHODPR(RigidBody2D, ApplyForceToCenter, (const Vector2&, bool), void), AS_CALL_THISCALL);
    // void RigidBody2D::ApplyLinearImpulse(const Vector2& impulse, const Vector2& point, bool wake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyLinearImpulse(const Vector2&in, const Vector2&in, bool)", AS_METHODPR(RigidBody2D, ApplyLinearImpulse, (const Vector2&, const Vector2&, bool), void), AS_CALL_THISCALL);
    // void RigidBody2D::ApplyLinearImpulseToCenter(const Vector2& impulse, bool wake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyLinearImpulseToCenter(const Vector2&in, bool)", AS_METHODPR(RigidBody2D, ApplyLinearImpulseToCenter, (const Vector2&, bool), void), AS_CALL_THISCALL);
    // void RigidBody2D::ApplyTorque(float torque, bool wake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyTorque(float, bool)", AS_METHODPR(RigidBody2D, ApplyTorque, (float, bool), void), AS_CALL_THISCALL);
    // void RigidBody2D::ApplyWorldTransform() | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyWorldTransform()", AS_METHODPR(RigidBody2D, ApplyWorldTransform, (), void), AS_CALL_THISCALL);
    // void RigidBody2D::ApplyWorldTransform(const Vector3& newWorldPosition, const Quaternion& newWorldRotation) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyWorldTransform(const Vector3&in, const Quaternion&in)", AS_METHODPR(RigidBody2D, ApplyWorldTransform, (const Vector3&, const Quaternion&), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void RigidBody2D::CreateBody() | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void CreateBody()", AS_METHODPR(RigidBody2D, CreateBody, (), void), AS_CALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(RigidBody2D, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // float RigidBody2D::GetAngularDamping() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetAngularDamping() const", AS_METHODPR(RigidBody2D, GetAngularDamping, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_angularDamping() const", AS_METHODPR(RigidBody2D, GetAngularDamping, () const, float), AS_CALL_THISCALL);
    // float RigidBody2D::GetAngularVelocity() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetAngularVelocity() const", AS_METHODPR(RigidBody2D, GetAngularVelocity, () const, float), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool GetAnimationEnabled() const", AS_METHODPR(RigidBody2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_animationEnabled() const", AS_METHODPR(RigidBody2D, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "Variant GetAttribute(uint) const", AS_METHODPR(RigidBody2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Variant get_attributes(uint) const", AS_METHODPR(RigidBody2D, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "Variant GetAttribute(const String&in) const", AS_METHODPR(RigidBody2D, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(RigidBody2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(RigidBody2D, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(RigidBody2D, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(RigidBody2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "Variant GetAttributeDefault(uint) const", AS_METHODPR(RigidBody2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Variant get_attributeDefaults(uint) const", AS_METHODPR(RigidBody2D, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(RigidBody2D, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "bool GetBlockEvents() const", AS_METHODPR(RigidBody2D, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // b2Body* RigidBody2D::GetBody() const | File: ../Urho2D/RigidBody2D.h
    // Error: type "b2Body*" can not automatically bind
    // BodyType2D RigidBody2D::GetBodyType() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "BodyType2D GetBodyType() const", AS_METHODPR(RigidBody2D, GetBodyType, () const, BodyType2D), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "BodyType2D get_bodyType() const", AS_METHODPR(RigidBody2D, GetBodyType, () const, BodyType2D), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "const String& GetCategory() const", AS_METHODPR(RigidBody2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "const String& get_category() const", AS_METHODPR(RigidBody2D, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "Component@+ GetComponent(StringHash) const", AS_METHODPR(RigidBody2D, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("RigidBody2D", "VariantMap& GetEventDataMap() const", AS_METHODPR(RigidBody2D, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "Object@+ GetEventSender() const", AS_METHODPR(RigidBody2D, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(RigidBody2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(RigidBody2D, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "const VariantMap& GetGlobalVars() const", AS_METHODPR(RigidBody2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "const VariantMap& get_globalVars() const", AS_METHODPR(RigidBody2D, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // float RigidBody2D::GetGravityScale() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetGravityScale() const", AS_METHODPR(RigidBody2D, GetGravityScale, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_gravityScale() const", AS_METHODPR(RigidBody2D, GetGravityScale, () const, float), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "uint GetID() const", AS_METHODPR(RigidBody2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "uint get_id() const", AS_METHODPR(RigidBody2D, GetID, () const, unsigned), AS_CALL_THISCALL);
    // float RigidBody2D::GetInertia() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetInertia() const", AS_METHODPR(RigidBody2D, GetInertia, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_inertia() const", AS_METHODPR(RigidBody2D, GetInertia, () const, float), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(RigidBody2D, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // float RigidBody2D::GetLinearDamping() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetLinearDamping() const", AS_METHODPR(RigidBody2D, GetLinearDamping, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_linearDamping() const", AS_METHODPR(RigidBody2D, GetLinearDamping, () const, float), AS_CALL_THISCALL);
    // Vector2 RigidBody2D::GetLinearVelocity() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "Vector2 GetLinearVelocity() const", AS_METHODPR(RigidBody2D, GetLinearVelocity, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Vector2 get_linearVelocity() const", AS_METHODPR(RigidBody2D, GetLinearVelocity, () const, Vector2), AS_CALL_THISCALL);
    // float RigidBody2D::GetMass() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetMass() const", AS_METHODPR(RigidBody2D, GetMass, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_mass() const", AS_METHODPR(RigidBody2D, GetMass, () const, float), AS_CALL_THISCALL);
    // Vector2 RigidBody2D::GetMassCenter() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "Vector2 GetMassCenter() const", AS_METHODPR(RigidBody2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Vector2 get_massCenter() const", AS_METHODPR(RigidBody2D, GetMassCenter, () const, Vector2), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "Node@+ GetNode() const", AS_METHODPR(RigidBody2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Node@+ get_node() const", AS_METHODPR(RigidBody2D, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "uint GetNumAttributes() const", AS_METHODPR(RigidBody2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "uint get_numAttributes() const", AS_METHODPR(RigidBody2D, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "uint GetNumNetworkAttributes() const", AS_METHODPR(RigidBody2D, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(RigidBody2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(RigidBody2D, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(RigidBody2D, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "Scene@+ GetScene() const", AS_METHODPR(RigidBody2D, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(RigidBody2D, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "StringHash GetType() const", AS_METHODPR(RigidBody2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "StringHash get_type() const", AS_METHODPR(RigidBody2D, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "const String& GetTypeName() const", AS_METHODPR(RigidBody2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "const String& get_typeName() const", AS_METHODPR(RigidBody2D, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool RigidBody2D::GetUseFixtureMass() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "bool GetUseFixtureMass() const", AS_METHODPR(RigidBody2D, GetUseFixtureMass, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_useFixtureMass() const", AS_METHODPR(RigidBody2D, GetUseFixtureMass, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "bool HasEventHandlers() const", AS_METHODPR(RigidBody2D, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(RigidBody2D, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(RigidBody2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool RigidBody2D::IsAllowSleep() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsAllowSleep() const", AS_METHODPR(RigidBody2D, IsAllowSleep, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_allowSleep() const", AS_METHODPR(RigidBody2D, IsAllowSleep, () const, bool), AS_CALL_THISCALL);
    // bool RigidBody2D::IsAwake() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsAwake() const", AS_METHODPR(RigidBody2D, IsAwake, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_awake() const", AS_METHODPR(RigidBody2D, IsAwake, () const, bool), AS_CALL_THISCALL);
    // bool RigidBody2D::IsBullet() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsBullet() const", AS_METHODPR(RigidBody2D, IsBullet, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_bullet() const", AS_METHODPR(RigidBody2D, IsBullet, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsEnabled() const", AS_METHODPR(RigidBody2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_enabled() const", AS_METHODPR(RigidBody2D, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsEnabledEffective() const", AS_METHODPR(RigidBody2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_enabledEffective() const", AS_METHODPR(RigidBody2D, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool RigidBody2D::IsFixedRotation() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsFixedRotation() const", AS_METHODPR(RigidBody2D, IsFixedRotation, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_fixedRotation() const", AS_METHODPR(RigidBody2D, IsFixedRotation, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsInstanceOf(StringHash) const", AS_METHODPR(RigidBody2D, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsReplicated() const", AS_METHODPR(RigidBody2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_replicated() const", AS_METHODPR(RigidBody2D, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsTemporary() const", AS_METHODPR(RigidBody2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_temporary() const", AS_METHODPR(RigidBody2D, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool Load(Deserializer&)", AS_METHODPR(RigidBody2D, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(RigidBody2D, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool LoadXML(const XMLElement&in)", AS_METHODPR(RigidBody2D, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "void MarkNetworkUpdate()", AS_METHODPR(RigidBody2D, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(RigidBody2D, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(RigidBody2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(RigidBody2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void RigidBody2D::OnSetEnabled() override | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void OnSetEnabled()", AS_METHODPR(RigidBody2D, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "void PrepareNetworkUpdate()", AS_METHODPR(RigidBody2D, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(RigidBody2D, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(RigidBody2D, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RigidBody2D", "int Refs() const", AS_METHODPR(RigidBody2D, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "int get_refs() const", AS_METHODPR(RigidBody2D, Refs, () const, int), AS_CALL_THISCALL);
    // static void RigidBody2D::RegisterObject(Context* context) | File: ../Urho2D/RigidBody2D.h
    // Not registered because have @nobind mark
    // void RigidBody2D::ReleaseBody() | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ReleaseBody()", AS_METHODPR(RigidBody2D, ReleaseBody, (), void), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RigidBody2D", asBEHAVE_RELEASE, "void f()", AS_METHODPR(RigidBody2D, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "void Remove()", AS_METHODPR(RigidBody2D, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(RigidBody2D, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void RigidBody2D::RemoveCollisionShape2D(CollisionShape2D* collisionShape) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void RemoveCollisionShape2D(CollisionShape2D@+)", AS_METHODPR(RigidBody2D, RemoveCollisionShape2D, (CollisionShape2D*), void), AS_CALL_THISCALL);
    // void RigidBody2D::RemoveConstraint2D(Constraint2D* constraint) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void RemoveConstraint2D(Constraint2D@+)", AS_METHODPR(RigidBody2D, RemoveConstraint2D, (Constraint2D*), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void RemoveInstanceDefault()", AS_METHODPR(RigidBody2D, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void RemoveObjectAnimation()", AS_METHODPR(RigidBody2D, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void ResetToDefault()", AS_METHODPR(RigidBody2D, ResetToDefault, (), void), AS_CALL_THISCALL);
    // explicit RigidBody2D::RigidBody2D(Context* context) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectBehaviour("RigidBody2D", asBEHAVE_FACTORY, "RigidBody2D@+ f()", AS_FUNCTION(RigidBody2D_RigidBody2D_Context), AS_CALL_CDECL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "bool Save(Serializer&) const", AS_METHODPR(RigidBody2D, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool SaveDefaultAttributes() const", AS_METHODPR(RigidBody2D, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "bool SaveJSON(JSONValue&) const", AS_METHODPR(RigidBody2D, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "bool SaveXML(XMLElement&) const", AS_METHODPR(RigidBody2D, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void SendEvent(StringHash)", AS_METHODPR(RigidBody2D, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(RigidBody2D, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void RigidBody2D::SetAllowSleep(bool allowSleep) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAllowSleep(bool)", AS_METHODPR(RigidBody2D, SetAllowSleep, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_allowSleep(bool)", AS_METHODPR(RigidBody2D, SetAllowSleep, (bool), void), AS_CALL_THISCALL);
    // void RigidBody2D::SetAngularDamping(float angularDamping) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAngularDamping(float)", AS_METHODPR(RigidBody2D, SetAngularDamping, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_angularDamping(float)", AS_METHODPR(RigidBody2D, SetAngularDamping, (float), void), AS_CALL_THISCALL);
    // void RigidBody2D::SetAngularVelocity(float angularVelocity) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAngularVelocity(float)", AS_METHODPR(RigidBody2D, SetAngularVelocity, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAnimationEnabled(bool)", AS_METHODPR(RigidBody2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_animationEnabled(bool)", AS_METHODPR(RigidBody2D, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAnimationTime(float)", AS_METHODPR(RigidBody2D, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(RigidBody2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(RigidBody2D, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(RigidBody2D, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(RigidBody2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(RigidBody2D, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(RigidBody2D, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(RigidBody2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void RigidBody2D::SetAwake(bool awake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAwake(bool)", AS_METHODPR(RigidBody2D, SetAwake, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_awake(bool)", AS_METHODPR(RigidBody2D, SetAwake, (bool), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetBlockEvents(bool)", AS_METHODPR(RigidBody2D, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void RigidBody2D::SetBodyType(BodyType2D type) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetBodyType(BodyType2D)", AS_METHODPR(RigidBody2D, SetBodyType, (BodyType2D), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_bodyType(BodyType2D)", AS_METHODPR(RigidBody2D, SetBodyType, (BodyType2D), void), AS_CALL_THISCALL);
    // void RigidBody2D::SetBullet(bool bullet) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetBullet(bool)", AS_METHODPR(RigidBody2D, SetBullet, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_bullet(bool)", AS_METHODPR(RigidBody2D, SetBullet, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetEnabled(bool)", AS_METHODPR(RigidBody2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_enabled(bool)", AS_METHODPR(RigidBody2D, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void RigidBody2D::SetFixedRotation(bool fixedRotation) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetFixedRotation(bool)", AS_METHODPR(RigidBody2D, SetFixedRotation, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_fixedRotation(bool)", AS_METHODPR(RigidBody2D, SetFixedRotation, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(RigidBody2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(RigidBody2D, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void RigidBody2D::SetGravityScale(float gravityScale) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetGravityScale(float)", AS_METHODPR(RigidBody2D, SetGravityScale, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_gravityScale(float)", AS_METHODPR(RigidBody2D, SetGravityScale, (float), void), AS_CALL_THISCALL);
    // void RigidBody2D::SetInertia(float inertia) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetInertia(float)", AS_METHODPR(RigidBody2D, SetInertia, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_inertia(float)", AS_METHODPR(RigidBody2D, SetInertia, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetInstanceDefault(bool)", AS_METHODPR(RigidBody2D, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(RigidBody2D, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void RigidBody2D::SetLinearDamping(float linearDamping) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetLinearDamping(float)", AS_METHODPR(RigidBody2D, SetLinearDamping, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_linearDamping(float)", AS_METHODPR(RigidBody2D, SetLinearDamping, (float), void), AS_CALL_THISCALL);
    // void RigidBody2D::SetLinearVelocity(const Vector2& linearVelocity) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetLinearVelocity(const Vector2&in)", AS_METHODPR(RigidBody2D, SetLinearVelocity, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_linearVelocity(const Vector2&in)", AS_METHODPR(RigidBody2D, SetLinearVelocity, (const Vector2&), void), AS_CALL_THISCALL);
    // void RigidBody2D::SetMass(float mass) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetMass(float)", AS_METHODPR(RigidBody2D, SetMass, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_mass(float)", AS_METHODPR(RigidBody2D, SetMass, (float), void), AS_CALL_THISCALL);
    // void RigidBody2D::SetMassCenter(const Vector2& center) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetMassCenter(const Vector2&in)", AS_METHODPR(RigidBody2D, SetMassCenter, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_massCenter(const Vector2&in)", AS_METHODPR(RigidBody2D, SetMassCenter, (const Vector2&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(RigidBody2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(RigidBody2D, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(RigidBody2D, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetTemporary(bool)", AS_METHODPR(RigidBody2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_temporary(bool)", AS_METHODPR(RigidBody2D, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void RigidBody2D::SetUseFixtureMass(bool useFixtureMass) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetUseFixtureMass(bool)", AS_METHODPR(RigidBody2D, SetUseFixtureMass, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_useFixtureMass(bool)", AS_METHODPR(RigidBody2D, SetUseFixtureMass, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void UnsubscribeFromAllEvents()", AS_METHODPR(RigidBody2D, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(RigidBody2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(RigidBody2D, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(RigidBody2D, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(RigidBody2D, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RigidBody2D", "int WeakRefs() const", AS_METHODPR(RigidBody2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "int get_weakRefs() const", AS_METHODPR(RigidBody2D, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(RigidBody2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(RigidBody2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(RigidBody2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(RigidBody2D, "RigidBody2D")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(RigidBody2D, "RigidBody2D")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(RigidBody2D, "RigidBody2D")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(RigidBody2D, "RigidBody2D")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(RigidBody2D, "RigidBody2D")
#endif
#ifdef REGISTER_MANUAL_PART_RigidBody2D
    REGISTER_MANUAL_PART_RigidBody2D(RigidBody2D, "RigidBody2D")
#endif
    RegisterSubclass<Component, RigidBody2D>(engine, "Component", "RigidBody2D");
    RegisterSubclass<Animatable, RigidBody2D>(engine, "Animatable", "RigidBody2D");
    RegisterSubclass<Serializable, RigidBody2D>(engine, "Serializable", "RigidBody2D");
    RegisterSubclass<Object, RigidBody2D>(engine, "Object", "RigidBody2D");
    RegisterSubclass<RefCounted, RigidBody2D>(engine, "RefCounted", "RigidBody2D");
#endif

    // float RayQueryResult::distance_ | File: ../Graphics/OctreeQuery.h
    engine->RegisterObjectProperty("RayQueryResult", "float distance", offsetof(RayQueryResult, distance_));
    // Drawable* RayQueryResult::drawable_ | File: ../Graphics/OctreeQuery.h
    // Drawable* can not be registered
    // Node* RayQueryResult::node_ | File: ../Graphics/OctreeQuery.h
    // Node* can not be registered
    // Vector3 RayQueryResult::normal_ | File: ../Graphics/OctreeQuery.h
    engine->RegisterObjectProperty("RayQueryResult", "Vector3 normal", offsetof(RayQueryResult, normal_));
    // Vector3 RayQueryResult::position_ | File: ../Graphics/OctreeQuery.h
    engine->RegisterObjectProperty("RayQueryResult", "Vector3 position", offsetof(RayQueryResult, position_));
    // unsigned RayQueryResult::subObject_ | File: ../Graphics/OctreeQuery.h
    engine->RegisterObjectProperty("RayQueryResult", "uint subObject", offsetof(RayQueryResult, subObject_));
    // Vector2 RayQueryResult::textureUV_ | File: ../Graphics/OctreeQuery.h
    engine->RegisterObjectProperty("RayQueryResult", "Vector2 textureUV", offsetof(RayQueryResult, textureUV_));
    // RayQueryResult& RayQueryResult::operator=(const RayQueryResult&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<RayQueryResult>(engine, "RayQueryResult");
#ifdef REGISTER_MANUAL_PART_RayQueryResult
    REGISTER_MANUAL_PART_RayQueryResult(RayQueryResult, "RayQueryResult")
#endif

    // int RefCount::refs_ | File: ../Container/RefCounted.h
    engine->RegisterObjectProperty("RefCount", "int refs", offsetof(RefCount, refs_));
    // int RefCount::weakRefs_ | File: ../Container/RefCounted.h
    engine->RegisterObjectProperty("RefCount", "int weakRefs", offsetof(RefCount, weakRefs_));
    // RefCount& RefCount::operator=(const RefCount&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<RefCount>(engine, "RefCount");
#ifdef REGISTER_MANUAL_PART_RefCount
    REGISTER_MANUAL_PART_RefCount(RefCount, "RefCount")
#endif

#ifdef URHO3D_NETWORK
    // VariantMap RemoteEvent::eventData_ | File: ../Network/Connection.h
    engine->RegisterObjectProperty("RemoteEvent", "VariantMap eventData", offsetof(RemoteEvent, eventData_));
    // StringHash RemoteEvent::eventType_ | File: ../Network/Connection.h
    engine->RegisterObjectProperty("RemoteEvent", "StringHash eventType", offsetof(RemoteEvent, eventType_));
    // bool RemoteEvent::inOrder_ | File: ../Network/Connection.h
    engine->RegisterObjectProperty("RemoteEvent", "bool inOrder", offsetof(RemoteEvent, inOrder_));
    // unsigned RemoteEvent::senderID_ | File: ../Network/Connection.h
    engine->RegisterObjectProperty("RemoteEvent", "uint senderID", offsetof(RemoteEvent, senderID_));
    // RemoteEvent& RemoteEvent::operator=(const RemoteEvent&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<RemoteEvent>(engine, "RemoteEvent");
#ifdef REGISTER_MANUAL_PART_RemoteEvent
    REGISTER_MANUAL_PART_RemoteEvent(RemoteEvent, "RemoteEvent")
#endif
#endif

    // BlendMode RenderPathCommand::blendMode_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "BlendMode blendMode", offsetof(RenderPathCommand, blendMode_));
    // Color RenderPathCommand::clearColor_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "Color clearColor", offsetof(RenderPathCommand, clearColor_));
    // float RenderPathCommand::clearDepth_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "float clearDepth", offsetof(RenderPathCommand, clearDepth_));
    // ClearTargetFlags RenderPathCommand::clearFlags_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "ClearTargetFlags clearFlags", offsetof(RenderPathCommand, clearFlags_));
    // unsigned RenderPathCommand::clearStencil_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "uint clearStencil", offsetof(RenderPathCommand, clearStencil_));
    // String RenderPathCommand::depthStencilName_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "String depthStencilName", offsetof(RenderPathCommand, depthStencilName_));
    // bool RenderPathCommand::enabled_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "bool enabled", offsetof(RenderPathCommand, enabled_));
    // String RenderPathCommand::eventName_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "String eventName", offsetof(RenderPathCommand, eventName_));
    // bool RenderPathCommand::markToStencil_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "bool markToStencil", offsetof(RenderPathCommand, markToStencil_));
    // String RenderPathCommand::metadata_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "String metadata", offsetof(RenderPathCommand, metadata_));
    // Vector<Pair<String, CubeMapFace>> RenderPathCommand::outputs_ | File: ../Graphics/RenderPath.h
    // Error: type "Vector<Pair<String, CubeMapFace>>" can not automatically bind
    // String RenderPathCommand::pass_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "String pass", offsetof(RenderPathCommand, pass_));
    // unsigned RenderPathCommand::passIndex_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "uint passIndex", offsetof(RenderPathCommand, passIndex_));
    // String RenderPathCommand::pixelShaderDefines_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "String pixelShaderDefines", offsetof(RenderPathCommand, pixelShaderDefines_));
    // String RenderPathCommand::pixelShaderName_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "String pixelShaderName", offsetof(RenderPathCommand, pixelShaderName_));
    // HashMap<StringHash, Variant> RenderPathCommand::shaderParameters_ | File: ../Graphics/RenderPath.h
    // Error: type "HashMap<StringHash, Variant>" can not automatically bind
    // RenderCommandSortMode RenderPathCommand::sortMode_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "RenderCommandSortMode sortMode", offsetof(RenderPathCommand, sortMode_));
    // String RenderPathCommand::tag_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "String tag", offsetof(RenderPathCommand, tag_));
    // String RenderPathCommand::textureNames_[MAX_TEXTURE_UNITS] | File: ../Graphics/RenderPath.h
    // Not registered because array
    // RenderCommandType RenderPathCommand::type_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "RenderCommandType type", offsetof(RenderPathCommand, type_));
    // bool RenderPathCommand::useFogColor_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "bool useFogColor", offsetof(RenderPathCommand, useFogColor_));
    // bool RenderPathCommand::useLitBase_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "bool useLitBase", offsetof(RenderPathCommand, useLitBase_));
    // bool RenderPathCommand::vertexLights_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "bool vertexLights", offsetof(RenderPathCommand, vertexLights_));
    // String RenderPathCommand::vertexShaderDefines_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "String vertexShaderDefines", offsetof(RenderPathCommand, vertexShaderDefines_));
    // String RenderPathCommand::vertexShaderName_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderPathCommand", "String vertexShaderName", offsetof(RenderPathCommand, vertexShaderName_));
    // const String& RenderPathCommand::GetDepthStencilName() const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "const String& GetDepthStencilName() const", AS_METHODPR(RenderPathCommand, GetDepthStencilName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "const String& get_depthStencilName() const", AS_METHODPR(RenderPathCommand, GetDepthStencilName, () const, const String&), AS_CALL_THISCALL);
    // unsigned RenderPathCommand::GetNumOutputs() const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "uint GetNumOutputs() const", AS_METHODPR(RenderPathCommand, GetNumOutputs, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "uint get_numOutputs() const", AS_METHODPR(RenderPathCommand, GetNumOutputs, () const, unsigned), AS_CALL_THISCALL);
    // CubeMapFace RenderPathCommand::GetOutputFace(unsigned index) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "CubeMapFace GetOutputFace(uint) const", AS_METHODPR(RenderPathCommand, GetOutputFace, (unsigned) const, CubeMapFace), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "CubeMapFace get_outputFaces(uint) const", AS_METHODPR(RenderPathCommand, GetOutputFace, (unsigned) const, CubeMapFace), AS_CALL_THISCALL);
    // const String& RenderPathCommand::GetOutputName(unsigned index) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "const String& GetOutputName(uint) const", AS_METHODPR(RenderPathCommand, GetOutputName, (unsigned) const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "const String& get_outputNames(uint) const", AS_METHODPR(RenderPathCommand, GetOutputName, (unsigned) const, const String&), AS_CALL_THISCALL);
    // const Variant& RenderPathCommand::GetShaderParameter(const String& name) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "const Variant& GetShaderParameter(const String&in) const", AS_METHODPR(RenderPathCommand, GetShaderParameter, (const String&) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "const Variant& get_shaderParameters(const String&in) const", AS_METHODPR(RenderPathCommand, GetShaderParameter, (const String&) const, const Variant&), AS_CALL_THISCALL);
    // const String& RenderPathCommand::GetTextureName(TextureUnit unit) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "const String& GetTextureName(TextureUnit) const", AS_METHODPR(RenderPathCommand, GetTextureName, (TextureUnit) const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "const String& get_textureNames(TextureUnit) const", AS_METHODPR(RenderPathCommand, GetTextureName, (TextureUnit) const, const String&), AS_CALL_THISCALL);
    // void RenderPathCommand::Load(const XMLElement& element) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void Load(const XMLElement&in)", AS_METHODPR(RenderPathCommand, Load, (const XMLElement&), void), AS_CALL_THISCALL);
    // void RenderPathCommand::RemoveShaderParameter(const String& name) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void RemoveShaderParameter(const String&in)", AS_METHODPR(RenderPathCommand, RemoveShaderParameter, (const String&), void), AS_CALL_THISCALL);
    // void RenderPathCommand::SetDepthStencilName(const String& name) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetDepthStencilName(const String&in)", AS_METHODPR(RenderPathCommand, SetDepthStencilName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "void set_depthStencilName(const String&in)", AS_METHODPR(RenderPathCommand, SetDepthStencilName, (const String&), void), AS_CALL_THISCALL);
    // void RenderPathCommand::SetNumOutputs(unsigned num) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetNumOutputs(uint)", AS_METHODPR(RenderPathCommand, SetNumOutputs, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "void set_numOutputs(uint)", AS_METHODPR(RenderPathCommand, SetNumOutputs, (unsigned), void), AS_CALL_THISCALL);
    // void RenderPathCommand::SetOutput(unsigned index, const String& name, CubeMapFace face=FACE_POSITIVE_X) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetOutput(uint, const String&in, CubeMapFace = FACE_POSITIVE_X)", AS_METHODPR(RenderPathCommand, SetOutput, (unsigned, const String&, CubeMapFace), void), AS_CALL_THISCALL);
    // void RenderPathCommand::SetOutputFace(unsigned index, CubeMapFace face) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetOutputFace(uint, CubeMapFace)", AS_METHODPR(RenderPathCommand, SetOutputFace, (unsigned, CubeMapFace), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "void set_outputFaces(uint, CubeMapFace)", AS_METHODPR(RenderPathCommand, SetOutputFace, (unsigned, CubeMapFace), void), AS_CALL_THISCALL);
    // void RenderPathCommand::SetOutputName(unsigned index, const String& name) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetOutputName(uint, const String&in)", AS_METHODPR(RenderPathCommand, SetOutputName, (unsigned, const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "void set_outputNames(uint, const String&in)", AS_METHODPR(RenderPathCommand, SetOutputName, (unsigned, const String&), void), AS_CALL_THISCALL);
    // void RenderPathCommand::SetShaderParameter(const String& name, const Variant& value) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetShaderParameter(const String&in, const Variant&in)", AS_METHODPR(RenderPathCommand, SetShaderParameter, (const String&, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "void set_shaderParameters(const String&in, const Variant&in)", AS_METHODPR(RenderPathCommand, SetShaderParameter, (const String&, const Variant&), void), AS_CALL_THISCALL);
    // void RenderPathCommand::SetTextureName(TextureUnit unit, const String& name) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetTextureName(TextureUnit, const String&in)", AS_METHODPR(RenderPathCommand, SetTextureName, (TextureUnit, const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "void set_textureNames(TextureUnit, const String&in)", AS_METHODPR(RenderPathCommand, SetTextureName, (TextureUnit, const String&), void), AS_CALL_THISCALL);
    // RenderPathCommand& RenderPathCommand::operator=(const RenderPathCommand&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<RenderPathCommand>(engine, "RenderPathCommand");
#ifdef REGISTER_MANUAL_PART_RenderPathCommand
    REGISTER_MANUAL_PART_RenderPathCommand(RenderPathCommand, "RenderPathCommand")
#endif

    // bool RenderTargetInfo::autoResolve_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderTargetInfo", "bool autoResolve", offsetof(RenderTargetInfo, autoResolve_));
    // bool RenderTargetInfo::cubemap_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderTargetInfo", "bool cubemap", offsetof(RenderTargetInfo, cubemap_));
    // bool RenderTargetInfo::enabled_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderTargetInfo", "bool enabled", offsetof(RenderTargetInfo, enabled_));
    // bool RenderTargetInfo::filtered_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderTargetInfo", "bool filtered", offsetof(RenderTargetInfo, filtered_));
    // unsigned RenderTargetInfo::format_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderTargetInfo", "uint format", offsetof(RenderTargetInfo, format_));
    // int RenderTargetInfo::multiSample_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderTargetInfo", "int multiSample", offsetof(RenderTargetInfo, multiSample_));
    // String RenderTargetInfo::name_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderTargetInfo", "String name", offsetof(RenderTargetInfo, name_));
    // bool RenderTargetInfo::persistent_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderTargetInfo", "bool persistent", offsetof(RenderTargetInfo, persistent_));
    // Vector2 RenderTargetInfo::size_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderTargetInfo", "Vector2 size", offsetof(RenderTargetInfo, size_));
    // RenderTargetSizeMode RenderTargetInfo::sizeMode_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderTargetInfo", "RenderTargetSizeMode sizeMode", offsetof(RenderTargetInfo, sizeMode_));
    // bool RenderTargetInfo::sRGB_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderTargetInfo", "bool sRGB", offsetof(RenderTargetInfo, sRGB_));
    // String RenderTargetInfo::tag_ | File: ../Graphics/RenderPath.h
    engine->RegisterObjectProperty("RenderTargetInfo", "String tag", offsetof(RenderTargetInfo, tag_));
    // void RenderTargetInfo::Load(const XMLElement& element) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderTargetInfo", "void Load(const XMLElement&in)", AS_METHODPR(RenderTargetInfo, Load, (const XMLElement&), void), AS_CALL_THISCALL);
    // RenderTargetInfo& RenderTargetInfo::operator=(const RenderTargetInfo&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<RenderTargetInfo>(engine, "RenderTargetInfo");
#ifdef REGISTER_MANUAL_PART_RenderTargetInfo
    REGISTER_MANUAL_PART_RenderTargetInfo(RenderTargetInfo, "RenderTargetInfo")
#endif

    // Connection* ReplicationState::connection_ | File: ../Scene/ReplicationState.h
    // Connection* can not be registered
    // ReplicationState& ReplicationState::operator=(const ReplicationState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ReplicationState>(engine, "ReplicationState");
#ifdef REGISTER_MANUAL_PART_ReplicationState
    REGISTER_MANUAL_PART_ReplicationState(ReplicationState, "ReplicationState")
#endif

    // unsigned long long ResourceGroup::memoryBudget_ | File: ../Resource/ResourceCache.h
    engine->RegisterObjectProperty("ResourceGroup", "uint64 memoryBudget", offsetof(ResourceGroup, memoryBudget_));
    // unsigned long long ResourceGroup::memoryUse_ | File: ../Resource/ResourceCache.h
    engine->RegisterObjectProperty("ResourceGroup", "uint64 memoryUse", offsetof(ResourceGroup, memoryUse_));
    // HashMap<StringHash, SharedPtr<Resource>> ResourceGroup::resources_ | File: ../Resource/ResourceCache.h
    // Error: type "HashMap<StringHash, SharedPtr<Resource>>" can not automatically bind
    // ResourceGroup& ResourceGroup::operator=(const ResourceGroup&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ResourceGroup>(engine, "ResourceGroup");
#ifdef REGISTER_MANUAL_PART_ResourceGroup
    REGISTER_MANUAL_PART_ResourceGroup(ResourceGroup, "ResourceGroup")
#endif

    // String ResourceRef::name_ | File: ../Core/Variant.h
    engine->RegisterObjectProperty("ResourceRef", "String name", offsetof(ResourceRef, name_));
    // StringHash ResourceRef::type_ | File: ../Core/Variant.h
    engine->RegisterObjectProperty("ResourceRef", "StringHash type", offsetof(ResourceRef, type_));
    // bool ResourceRef::operator==(const ResourceRef& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("ResourceRef", "bool opEquals(const ResourceRef&in) const", AS_METHODPR(ResourceRef, operator==, (const ResourceRef&) const, bool), AS_CALL_THISCALL);
    // explicit ResourceRef::ResourceRef(StringHash type) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(StringHash)", AS_FUNCTION_OBJFIRST(ResourceRef_ResourceRef_StringHash), AS_CALL_CDECL_OBJFIRST);
    // ResourceRef::ResourceRef(StringHash type, const String& name) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(StringHash, const String&in)", AS_FUNCTION_OBJFIRST(ResourceRef_ResourceRef_StringHash_String), AS_CALL_CDECL_OBJFIRST);
    // ResourceRef::ResourceRef(const String& type, const String& name) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(const String&in, const String&in)", AS_FUNCTION_OBJFIRST(ResourceRef_ResourceRef_String_String), AS_CALL_CDECL_OBJFIRST);
    // ResourceRef::ResourceRef(const char* type, const char* name) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // ResourceRef::ResourceRef(const ResourceRef& rhs)=default | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(const ResourceRef&in)", AS_FUNCTION_OBJFIRST(ResourceRef_ResourceRef_ResourceRef), AS_CALL_CDECL_OBJFIRST);
    // ResourceRef& ResourceRef::operator=(const ResourceRef&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ResourceRef>(engine, "ResourceRef");
#ifdef REGISTER_MANUAL_PART_ResourceRef
    REGISTER_MANUAL_PART_ResourceRef(ResourceRef, "ResourceRef")
#endif

    // StringVector ResourceRefList::names_ | File: ../Core/Variant.h
    // Error: type "StringVector" can not automatically bind
    // StringHash ResourceRefList::type_ | File: ../Core/Variant.h
    engine->RegisterObjectProperty("ResourceRefList", "StringHash type", offsetof(ResourceRefList, type_));
    // bool ResourceRefList::operator==(const ResourceRefList& rhs) const | File: ../Core/Variant.h
    engine->RegisterObjectMethod("ResourceRefList", "bool opEquals(const ResourceRefList&in) const", AS_METHODPR(ResourceRefList, operator==, (const ResourceRefList&) const, bool), AS_CALL_THISCALL);
    // explicit ResourceRefList::ResourceRefList(StringHash type) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_CONSTRUCT, "void f(StringHash)", AS_FUNCTION_OBJFIRST(ResourceRefList_ResourceRefList_StringHash), AS_CALL_CDECL_OBJFIRST);
    // ResourceRefList::ResourceRefList(StringHash type, const StringVector& names) | File: ../Core/Variant.h
    // Error: type "const StringVector&" can not automatically bind
    // ResourceRefList& ResourceRefList::operator=(const ResourceRefList&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ResourceRefList>(engine, "ResourceRefList");
#ifdef REGISTER_MANUAL_PART_ResourceRefList
    REGISTER_MANUAL_PART_ResourceRefList(ResourceRefList, "ResourceRefList")
#endif

}

}
