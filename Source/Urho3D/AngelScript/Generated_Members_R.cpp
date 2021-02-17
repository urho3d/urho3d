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

// RefCounted::RefCounted() | File: ../Container/RefCounted.h
static RefCounted* RefCounted_RefCounted_void()
{
    return new RefCounted();
}

// SharedPtr<RenderPath> RenderPath::Clone() | File: ../Graphics/RenderPath.h
static RenderPath* RenderPath_Clone_void(RenderPath* ptr)
{
    SharedPtr<RenderPath> result = ptr->Clone();
    return result.Detach();
}

// RenderPath::RenderPath() | File: ../Graphics/RenderPath.h
static RenderPath* RenderPath_RenderPath_void()
{
    return new RenderPath();
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
    engine->RegisterObjectMethod("Ray", "Vector3 ClosestPoint(const Ray&in) const", asMETHODPR(Ray, ClosestPoint, (const Ray&) const, Vector3), asCALL_THISCALL);
    // void Ray::Define(const Vector3& origin, const Vector3& direction) | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "void Define(const Vector3&in, const Vector3&in)", asMETHODPR(Ray, Define, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    // float Ray::Distance(const Vector3& point) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "float Distance(const Vector3&in) const", asMETHODPR(Ray, Distance, (const Vector3&) const, float), asCALL_THISCALL);
    // float Ray::HitDistance(const Plane& plane) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "float HitDistance(const Plane&in) const", asMETHODPR(Ray, HitDistance, (const Plane&) const, float), asCALL_THISCALL);
    // float Ray::HitDistance(const BoundingBox& box) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "float HitDistance(const BoundingBox&in) const", asMETHODPR(Ray, HitDistance, (const BoundingBox&) const, float), asCALL_THISCALL);
    // float Ray::HitDistance(const Frustum& frustum, bool solidInside=true) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "float HitDistance(const Frustum&in, bool = true) const", asMETHODPR(Ray, HitDistance, (const Frustum&, bool) const, float), asCALL_THISCALL);
    // float Ray::HitDistance(const Sphere& sphere) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "float HitDistance(const Sphere&in) const", asMETHODPR(Ray, HitDistance, (const Sphere&) const, float), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Ray", "Ray& opAssign(const Ray&in)", asMETHODPR(Ray, operator=, (const Ray&), Ray&), asCALL_THISCALL);
    // bool Ray::operator==(const Ray& rhs) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "bool opEquals(const Ray&in) const", asMETHODPR(Ray, operator==, (const Ray&) const, bool), asCALL_THISCALL);
    // Vector3 Ray::Project(const Vector3& point) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "Vector3 Project(const Vector3&in) const", asMETHODPR(Ray, Project, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // Ray::Ray(const Vector3& origin, const Vector3& direction) noexcept | File: ../Math/Ray.h
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(Ray_Ray_Vector3_Vector3), asCALL_CDECL_OBJFIRST);
    // Ray::Ray(const Ray& ray) noexcept=default | File: ../Math/Ray.h
    engine->RegisterObjectBehaviour("Ray", asBEHAVE_CONSTRUCT, "void f(const Ray&in)", asFUNCTION(Ray_Ray_Ray), asCALL_CDECL_OBJFIRST);
    // Ray Ray::Transformed(const Matrix3x4& transform) const | File: ../Math/Ray.h
    engine->RegisterObjectMethod("Ray", "Ray Transformed(const Matrix3x4&in) const", asMETHODPR(Ray, Transformed, (const Matrix3x4&) const, Ray), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("RaycastVehicle", asBEHAVE_ADDREF, "void f()", asMETHODPR(RaycastVehicle, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void RaycastVehicle::AddWheel(Node* wheelNode, Vector3 wheelDirection, Vector3 wheelAxle, float restLength, float wheelRadius, bool frontWheel) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void AddWheel(Node@+, Vector3, Vector3, float, float, bool)", asMETHODPR(RaycastVehicle, AddWheel, (Node*, Vector3, Vector3, float, float, bool), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void AllocateNetworkState()", asMETHODPR(RaycastVehicle, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void RaycastVehicle::ApplyAttributes() override | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void ApplyAttributes()", asMETHODPR(RaycastVehicle, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(RaycastVehicle, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // void RaycastVehicle::FixedPostUpdate(float timeStep) override | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void FixedPostUpdate(float)", asMETHODPR(RaycastVehicle, FixedPostUpdate, (float), void), asCALL_THISCALL);
    // void RaycastVehicle::FixedUpdate(float timeStep) override | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void FixedUpdate(float)", asMETHODPR(RaycastVehicle, FixedUpdate, (float), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool GetAnimationEnabled() const", asMETHODPR(RaycastVehicle, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "bool get_animationEnabled() const", asMETHODPR(RaycastVehicle, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "Variant GetAttribute(uint) const", asMETHODPR(RaycastVehicle, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "Variant get_attributes(uint) const", asMETHODPR(RaycastVehicle, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "Variant GetAttribute(const String&in) const", asMETHODPR(RaycastVehicle, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(RaycastVehicle, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(RaycastVehicle, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(RaycastVehicle, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(RaycastVehicle, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "Variant GetAttributeDefault(uint) const", asMETHODPR(RaycastVehicle, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "Variant get_attributeDefaults(uint) const", asMETHODPR(RaycastVehicle, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(RaycastVehicle, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool GetBlockEvents() const", asMETHODPR(RaycastVehicle, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // float RaycastVehicle::GetBrake(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetBrake(int) const", asMETHODPR(RaycastVehicle, GetBrake, (int) const, float), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "const String& GetCategory() const", asMETHODPR(RaycastVehicle, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "const String& get_category() const", asMETHODPR(RaycastVehicle, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "Component@+ GetComponent(StringHash) const", asMETHODPR(RaycastVehicle, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // Vector3 RaycastVehicle::GetContactNormal(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetContactNormal(int) const", asMETHODPR(RaycastVehicle, GetContactNormal, (int) const, Vector3), asCALL_THISCALL);
    // Vector3 RaycastVehicle::GetContactPosition(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetContactPosition(int) const", asMETHODPR(RaycastVehicle, GetContactPosition, (int) const, Vector3), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // IntVector3 RaycastVehicle::GetCoordinateSystem() const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "IntVector3 GetCoordinateSystem() const", asMETHODPR(RaycastVehicle, GetCoordinateSystem, () const, IntVector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "IntVector3 get_coordinateSystem() const", asMETHODPR(RaycastVehicle, GetCoordinateSystem, () const, IntVector3), asCALL_THISCALL);
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // float RaycastVehicle::GetEngineForce(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetEngineForce(int) const", asMETHODPR(RaycastVehicle, GetEngineForce, (int) const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "VariantMap& GetEventDataMap() const", asMETHODPR(RaycastVehicle, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "Object@+ GetEventSender() const", asMETHODPR(RaycastVehicle, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(RaycastVehicle, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "const Variant& get_globalVar(StringHash) const", asMETHODPR(RaycastVehicle, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "const VariantMap& GetGlobalVars() const", asMETHODPR(RaycastVehicle, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "const VariantMap& get_globalVars() const", asMETHODPR(RaycastVehicle, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "uint GetID() const", asMETHODPR(RaycastVehicle, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "uint get_id() const", asMETHODPR(RaycastVehicle, GetID, () const, unsigned), asCALL_THISCALL);
    // float RaycastVehicle::GetInAirRPM() const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetInAirRPM() const", asMETHODPR(RaycastVehicle, GetInAirRPM, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "float get_inAirRPM() const", asMETHODPR(RaycastVehicle, GetInAirRPM, () const, float), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(RaycastVehicle, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // float RaycastVehicle::GetMaxSideSlipSpeed() const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetMaxSideSlipSpeed() const", asMETHODPR(RaycastVehicle, GetMaxSideSlipSpeed, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "float get_maxSideSlipSpeed() const", asMETHODPR(RaycastVehicle, GetMaxSideSlipSpeed, () const, float), asCALL_THISCALL);
    // float RaycastVehicle::GetMaxSuspensionTravel(int wheel) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetMaxSuspensionTravel(int)", asMETHODPR(RaycastVehicle, GetMaxSuspensionTravel, (int), float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "Node@+ GetNode() const", asMETHODPR(RaycastVehicle, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "Node@+ get_node() const", asMETHODPR(RaycastVehicle, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "uint GetNumAttributes() const", asMETHODPR(RaycastVehicle, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "uint get_numAttributes() const", asMETHODPR(RaycastVehicle, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "uint GetNumNetworkAttributes() const", asMETHODPR(RaycastVehicle, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // int RaycastVehicle::GetNumWheels() const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "int GetNumWheels() const", asMETHODPR(RaycastVehicle, GetNumWheels, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "int get_numWheels() const", asMETHODPR(RaycastVehicle, GetNumWheels, () const, int), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(RaycastVehicle, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(RaycastVehicle, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(RaycastVehicle, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "Scene@+ GetScene() const", asMETHODPR(RaycastVehicle, GetScene, () const, Scene*), asCALL_THISCALL);
    // float RaycastVehicle::GetSteeringValue(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetSteeringValue(int) const", asMETHODPR(RaycastVehicle, GetSteeringValue, (int) const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(RaycastVehicle, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "StringHash GetType() const", asMETHODPR(RaycastVehicle, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "StringHash get_type() const", asMETHODPR(RaycastVehicle, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "const String& GetTypeName() const", asMETHODPR(RaycastVehicle, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "const String& get_typeName() const", asMETHODPR(RaycastVehicle, GetTypeName, () const, const String&), asCALL_THISCALL);
    // Vector3 RaycastVehicle::GetWheelAxle(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetWheelAxle(int) const", asMETHODPR(RaycastVehicle, GetWheelAxle, (int) const, Vector3), asCALL_THISCALL);
    // Vector3 RaycastVehicle::GetWheelConnectionPoint(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetWheelConnectionPoint(int) const", asMETHODPR(RaycastVehicle, GetWheelConnectionPoint, (int) const, Vector3), asCALL_THISCALL);
    // float RaycastVehicle::GetWheelDampingCompression(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelDampingCompression(int) const", asMETHODPR(RaycastVehicle, GetWheelDampingCompression, (int) const, float), asCALL_THISCALL);
    // float RaycastVehicle::GetWheelDampingRelaxation(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelDampingRelaxation(int) const", asMETHODPR(RaycastVehicle, GetWheelDampingRelaxation, (int) const, float), asCALL_THISCALL);
    // VariantVector RaycastVehicle::GetWheelDataAttr() const | File: ../Physics/RaycastVehicle.h
    // Error: type "VariantVector" can not automatically bind
    // Vector3 RaycastVehicle::GetWheelDirection(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetWheelDirection(int) const", asMETHODPR(RaycastVehicle, GetWheelDirection, (int) const, Vector3), asCALL_THISCALL);
    // float RaycastVehicle::GetWheelFrictionSlip(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelFrictionSlip(int) const", asMETHODPR(RaycastVehicle, GetWheelFrictionSlip, (int) const, float), asCALL_THISCALL);
    // float RaycastVehicle::GetWheelMaxSuspensionForce(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelMaxSuspensionForce(int) const", asMETHODPR(RaycastVehicle, GetWheelMaxSuspensionForce, (int) const, float), asCALL_THISCALL);
    // Node* RaycastVehicle::GetWheelNode(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Node@+ GetWheelNode(int) const", asMETHODPR(RaycastVehicle, GetWheelNode, (int) const, Node*), asCALL_THISCALL);
    // Vector3 RaycastVehicle::GetWheelPosition(int wheel) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Vector3 GetWheelPosition(int)", asMETHODPR(RaycastVehicle, GetWheelPosition, (int), Vector3), asCALL_THISCALL);
    // float RaycastVehicle::GetWheelRadius(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelRadius(int) const", asMETHODPR(RaycastVehicle, GetWheelRadius, (int) const, float), asCALL_THISCALL);
    // float RaycastVehicle::GetWheelRestLength(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelRestLength(int) const", asMETHODPR(RaycastVehicle, GetWheelRestLength, (int) const, float), asCALL_THISCALL);
    // float RaycastVehicle::GetWheelRollInfluence(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelRollInfluence(int) const", asMETHODPR(RaycastVehicle, GetWheelRollInfluence, (int) const, float), asCALL_THISCALL);
    // Quaternion RaycastVehicle::GetWheelRotation(int wheel) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "Quaternion GetWheelRotation(int)", asMETHODPR(RaycastVehicle, GetWheelRotation, (int), Quaternion), asCALL_THISCALL);
    // float RaycastVehicle::GetWheelSideSlipSpeed(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelSideSlipSpeed(int) const", asMETHODPR(RaycastVehicle, GetWheelSideSlipSpeed, (int) const, float), asCALL_THISCALL);
    // float RaycastVehicle::GetWheelSkidInfo(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelSkidInfo(int) const", asMETHODPR(RaycastVehicle, GetWheelSkidInfo, (int) const, float), asCALL_THISCALL);
    // float RaycastVehicle::GetWheelSkidInfoCumulative(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelSkidInfoCumulative(int) const", asMETHODPR(RaycastVehicle, GetWheelSkidInfoCumulative, (int) const, float), asCALL_THISCALL);
    // float RaycastVehicle::GetWheelSuspensionStiffness(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "float GetWheelSuspensionStiffness(int) const", asMETHODPR(RaycastVehicle, GetWheelSuspensionStiffness, (int) const, float), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool HasEventHandlers() const", asMETHODPR(RaycastVehicle, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(RaycastVehicle, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(RaycastVehicle, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // void RaycastVehicle::Init() | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void Init()", asMETHODPR(RaycastVehicle, Init, (), void), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool IsEnabled() const", asMETHODPR(RaycastVehicle, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "bool get_enabled() const", asMETHODPR(RaycastVehicle, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool IsEnabledEffective() const", asMETHODPR(RaycastVehicle, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "bool get_enabledEffective() const", asMETHODPR(RaycastVehicle, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool RaycastVehicle::IsFrontWheel(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool IsFrontWheel(int) const", asMETHODPR(RaycastVehicle, IsFrontWheel, (int) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool IsInstanceOf(StringHash) const", asMETHODPR(RaycastVehicle, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool IsReplicated() const", asMETHODPR(RaycastVehicle, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "bool get_replicated() const", asMETHODPR(RaycastVehicle, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool IsTemporary() const", asMETHODPR(RaycastVehicle, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "bool get_temporary() const", asMETHODPR(RaycastVehicle, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool Load(Deserializer&)", asMETHODPR(RaycastVehicle, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool LoadJSON(const JSONValue&in)", asMETHODPR(RaycastVehicle, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool LoadXML(const XMLElement&in)", asMETHODPR(RaycastVehicle, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "void MarkNetworkUpdate()", asMETHODPR(RaycastVehicle, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(RaycastVehicle, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(RaycastVehicle, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(RaycastVehicle, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void RaycastVehicle::OnSetEnabled() override | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void OnSetEnabled()", asMETHODPR(RaycastVehicle, OnSetEnabled, (), void), asCALL_THISCALL);
    // void RaycastVehicle::PostUpdate(float timeStep) override | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void PostUpdate(float)", asMETHODPR(RaycastVehicle, PostUpdate, (float), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "void PrepareNetworkUpdate()", asMETHODPR(RaycastVehicle, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // explicit RaycastVehicle::RaycastVehicle(Urho3D::Context* context) | File: ../Physics/RaycastVehicle.h
    // Error: context can be only first
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(RaycastVehicle, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(RaycastVehicle, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RaycastVehicle", "int Refs() const", asMETHODPR(RaycastVehicle, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "int get_refs() const", asMETHODPR(RaycastVehicle, Refs, () const, int), asCALL_THISCALL);
    // static void RaycastVehicle::RegisterObject(Context* context) | File: ../Physics/RaycastVehicle.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RaycastVehicle", asBEHAVE_RELEASE, "void f()", asMETHODPR(RaycastVehicle, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "void Remove()", asMETHODPR(RaycastVehicle, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(RaycastVehicle, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void RemoveInstanceDefault()", asMETHODPR(RaycastVehicle, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void RemoveObjectAnimation()", asMETHODPR(RaycastVehicle, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void RaycastVehicle::ResetSuspension() | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void ResetSuspension()", asMETHODPR(RaycastVehicle, ResetSuspension, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void ResetToDefault()", asMETHODPR(RaycastVehicle, ResetToDefault, (), void), asCALL_THISCALL);
    // void RaycastVehicle::ResetWheels() | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void ResetWheels()", asMETHODPR(RaycastVehicle, ResetWheels, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool Save(Serializer&) const", asMETHODPR(RaycastVehicle, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool SaveDefaultAttributes() const", asMETHODPR(RaycastVehicle, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool SaveJSON(JSONValue&) const", asMETHODPR(RaycastVehicle, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool SaveXML(XMLElement&) const", asMETHODPR(RaycastVehicle, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SendEvent(StringHash)", asMETHODPR(RaycastVehicle, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(RaycastVehicle, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetAnimationEnabled(bool)", asMETHODPR(RaycastVehicle, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_animationEnabled(bool)", asMETHODPR(RaycastVehicle, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetAnimationTime(float)", asMETHODPR(RaycastVehicle, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(RaycastVehicle, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "bool set_attributes(uint, const Variant&in)", asMETHODPR(RaycastVehicle, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(RaycastVehicle, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(RaycastVehicle, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(RaycastVehicle, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(RaycastVehicle, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(RaycastVehicle, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetBlockEvents(bool)", asMETHODPR(RaycastVehicle, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void RaycastVehicle::SetBrake(int wheel, float force) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetBrake(int, float)", asMETHODPR(RaycastVehicle, SetBrake, (int, float), void), asCALL_THISCALL);
    // void RaycastVehicle::SetCoordinateSystem(const IntVector3& coordinateSystem=RIGHT_FORWARD_UP) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetCoordinateSystem(const IntVector3&in = RIGHT_FORWARD_UP)", asMETHODPR(RaycastVehicle, SetCoordinateSystem, (const IntVector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_coordinateSystem(const IntVector3&in = RIGHT_FORWARD_UP)", asMETHODPR(RaycastVehicle, SetCoordinateSystem, (const IntVector3&), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetEnabled(bool)", asMETHODPR(RaycastVehicle, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_enabled(bool)", asMETHODPR(RaycastVehicle, SetEnabled, (bool), void), asCALL_THISCALL);
    // void RaycastVehicle::SetEngineForce(int wheel, float force) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetEngineForce(int, float)", asMETHODPR(RaycastVehicle, SetEngineForce, (int, float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(RaycastVehicle, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(RaycastVehicle, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void RaycastVehicle::SetInAirRPM(float rpm) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetInAirRPM(float)", asMETHODPR(RaycastVehicle, SetInAirRPM, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_inAirRPM(float)", asMETHODPR(RaycastVehicle, SetInAirRPM, (float), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetInstanceDefault(bool)", asMETHODPR(RaycastVehicle, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(RaycastVehicle, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void RaycastVehicle::SetMaxSideSlipSpeed(float speed) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetMaxSideSlipSpeed(float)", asMETHODPR(RaycastVehicle, SetMaxSideSlipSpeed, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_maxSideSlipSpeed(float)", asMETHODPR(RaycastVehicle, SetMaxSideSlipSpeed, (float), void), asCALL_THISCALL);
    // void RaycastVehicle::SetMaxSuspensionTravel(int wheel, float maxSuspensionTravel) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetMaxSuspensionTravel(int, float)", asMETHODPR(RaycastVehicle, SetMaxSuspensionTravel, (int, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(RaycastVehicle, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(RaycastVehicle, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(RaycastVehicle, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void RaycastVehicle::SetSteeringValue(int wheel, float steeringValue) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetSteeringValue(int, float)", asMETHODPR(RaycastVehicle, SetSteeringValue, (int, float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetTemporary(bool)", asMETHODPR(RaycastVehicle, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "void set_temporary(bool)", asMETHODPR(RaycastVehicle, SetTemporary, (bool), void), asCALL_THISCALL);
    // void RaycastVehicle::SetWheelAxle(int wheel, Vector3 axle) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelAxle(int, Vector3)", asMETHODPR(RaycastVehicle, SetWheelAxle, (int, Vector3), void), asCALL_THISCALL);
    // void RaycastVehicle::SetWheelDampingCompression(int wheel, float compression) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelDampingCompression(int, float)", asMETHODPR(RaycastVehicle, SetWheelDampingCompression, (int, float), void), asCALL_THISCALL);
    // void RaycastVehicle::SetWheelDampingRelaxation(int wheel, float damping) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelDampingRelaxation(int, float)", asMETHODPR(RaycastVehicle, SetWheelDampingRelaxation, (int, float), void), asCALL_THISCALL);
    // void RaycastVehicle::SetWheelDataAttr(const VariantVector& value) | File: ../Physics/RaycastVehicle.h
    // Error: type "const VariantVector&" can not automatically bind
    // void RaycastVehicle::SetWheelDirection(int wheel, Vector3 direction) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelDirection(int, Vector3)", asMETHODPR(RaycastVehicle, SetWheelDirection, (int, Vector3), void), asCALL_THISCALL);
    // void RaycastVehicle::SetWheelFrictionSlip(int wheel, float slip) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelFrictionSlip(int, float)", asMETHODPR(RaycastVehicle, SetWheelFrictionSlip, (int, float), void), asCALL_THISCALL);
    // void RaycastVehicle::SetWheelMaxSuspensionForce(int wheel, float force) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelMaxSuspensionForce(int, float)", asMETHODPR(RaycastVehicle, SetWheelMaxSuspensionForce, (int, float), void), asCALL_THISCALL);
    // void RaycastVehicle::SetWheelRadius(int wheel, float wheelRadius) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelRadius(int, float)", asMETHODPR(RaycastVehicle, SetWheelRadius, (int, float), void), asCALL_THISCALL);
    // void RaycastVehicle::SetWheelRestLength(int wheel, float length) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelRestLength(int, float)", asMETHODPR(RaycastVehicle, SetWheelRestLength, (int, float), void), asCALL_THISCALL);
    // void RaycastVehicle::SetWheelRollInfluence(int wheel, float rollInfluence) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelRollInfluence(int, float)", asMETHODPR(RaycastVehicle, SetWheelRollInfluence, (int, float), void), asCALL_THISCALL);
    // void RaycastVehicle::SetWheelSkidInfo(int wheel, float factor) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelSkidInfo(int, float)", asMETHODPR(RaycastVehicle, SetWheelSkidInfo, (int, float), void), asCALL_THISCALL);
    // void RaycastVehicle::SetWheelSkidInfoCumulative(int wheel, float skid) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelSkidInfoCumulative(int, float)", asMETHODPR(RaycastVehicle, SetWheelSkidInfoCumulative, (int, float), void), asCALL_THISCALL);
    // void RaycastVehicle::SetWheelSuspensionStiffness(int wheel, float stiffness) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void SetWheelSuspensionStiffness(int, float)", asMETHODPR(RaycastVehicle, SetWheelSuspensionStiffness, (int, float), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void UnsubscribeFromAllEvents()", asMETHODPR(RaycastVehicle, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(RaycastVehicle_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(RaycastVehicle, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(RaycastVehicle, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RaycastVehicle", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(RaycastVehicle, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void RaycastVehicle::UpdateWheelTransform(int wheel, bool interpolated) | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "void UpdateWheelTransform(int, bool)", asMETHODPR(RaycastVehicle, UpdateWheelTransform, (int, bool), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RaycastVehicle", "int WeakRefs() const", asMETHODPR(RaycastVehicle, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RaycastVehicle", "int get_weakRefs() const", asMETHODPR(RaycastVehicle, WeakRefs, () const, int), asCALL_THISCALL);
    // bool RaycastVehicle::WheelIsGrounded(int wheel) const | File: ../Physics/RaycastVehicle.h
    engine->RegisterObjectMethod("RaycastVehicle", "bool WheelIsGrounded(int) const", asMETHODPR(RaycastVehicle, WheelIsGrounded, (int) const, bool), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(RaycastVehicle, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(RaycastVehicle, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RaycastVehicle", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(RaycastVehicle, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Rect", "float Bottom() const", asMETHODPR(Rect, Bottom, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "float get_bottom() const", asMETHODPR(Rect, Bottom, () const, float), asCALL_THISCALL);
    // Vector2 Rect::Center() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Vector2 Center() const", asMETHODPR(Rect, Center, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "Vector2 get_center() const", asMETHODPR(Rect, Center, () const, Vector2), asCALL_THISCALL);
    // void Rect::Clear() | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Clear()", asMETHODPR(Rect, Clear, (), void), asCALL_THISCALL);
    // void Rect::Clip(const Rect& rect) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Clip(const Rect&in)", asMETHODPR(Rect, Clip, (const Rect&), void), asCALL_THISCALL);
    // const float* Rect::Data() const | File: ../Math/Rect.h
    // Error: type "const float*" can not automatically bind
    // void Rect::Define(const Rect& rect) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Define(const Rect&in)", asMETHODPR(Rect, Define, (const Rect&), void), asCALL_THISCALL);
    // void Rect::Define(const Vector2& min, const Vector2& max) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Define(const Vector2&in, const Vector2&in)", asMETHODPR(Rect, Define, (const Vector2&, const Vector2&), void), asCALL_THISCALL);
    // void Rect::Define(const Vector2& point) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Define(const Vector2&in)", asMETHODPR(Rect, Define, (const Vector2&), void), asCALL_THISCALL);
    // bool Rect::Defined() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "bool Defined() const", asMETHODPR(Rect, Defined, () const, bool), asCALL_THISCALL);
    // bool Rect::Equals(const Rect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "bool Equals(const Rect&in) const", asMETHODPR(Rect, Equals, (const Rect&) const, bool), asCALL_THISCALL);
    // Vector2 Rect::HalfSize() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Vector2 HalfSize() const", asMETHODPR(Rect, HalfSize, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "Vector2 get_halfSize() const", asMETHODPR(Rect, HalfSize, () const, Vector2), asCALL_THISCALL);
    // Intersection Rect::IsInside(const Vector2& point) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Intersection IsInside(const Vector2&in) const", asMETHODPR(Rect, IsInside, (const Vector2&) const, Intersection), asCALL_THISCALL);
    // Intersection Rect::IsInside(const Rect& rect) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Intersection IsInside(const Rect&in) const", asMETHODPR(Rect, IsInside, (const Rect&) const, Intersection), asCALL_THISCALL);
    // float Rect::Left() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "float Left() const", asMETHODPR(Rect, Left, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "float get_left() const", asMETHODPR(Rect, Left, () const, float), asCALL_THISCALL);
    // Vector2 Rect::Max() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Vector2 Max() const", asMETHODPR(Rect, Max, () const, Vector2), asCALL_THISCALL);
    // void Rect::Merge(const Vector2& point) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Merge(const Vector2&in)", asMETHODPR(Rect, Merge, (const Vector2&), void), asCALL_THISCALL);
    // void Rect::Merge(const Rect& rect) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "void Merge(const Rect&in)", asMETHODPR(Rect, Merge, (const Rect&), void), asCALL_THISCALL);
    // Vector2 Rect::Min() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Vector2 Min() const", asMETHODPR(Rect, Min, () const, Vector2), asCALL_THISCALL);
    // Rect Rect::operator*(float value) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect opMul(float) const", asMETHODPR(Rect, operator*, (float) const, Rect), asCALL_THISCALL);
    // Rect& Rect::operator*=(float value) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect& opMulAssign(float)", asMETHODPR(Rect, operator*=, (float), Rect&), asCALL_THISCALL);
    // Rect Rect::operator+(const Rect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect opAdd(const Rect&in) const", asMETHODPR(Rect, operator+, (const Rect&) const, Rect), asCALL_THISCALL);
    // Rect& Rect::operator+=(const Rect& rhs) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect& opAddAssign(const Rect&in)", asMETHODPR(Rect, operator+=, (const Rect&), Rect&), asCALL_THISCALL);
    // Rect Rect::operator-(const Rect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect opSub(const Rect&in) const", asMETHODPR(Rect, operator-, (const Rect&) const, Rect), asCALL_THISCALL);
    // Rect& Rect::operator-=(const Rect& rhs) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect& opSubAssign(const Rect&in)", asMETHODPR(Rect, operator-=, (const Rect&), Rect&), asCALL_THISCALL);
    // Rect Rect::operator/(float value) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect opDiv(float) const", asMETHODPR(Rect, operator/, (float) const, Rect), asCALL_THISCALL);
    // Rect& Rect::operator/=(float value) | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect& opDivAssign(float)", asMETHODPR(Rect, operator/=, (float), Rect&), asCALL_THISCALL);
    // Rect& Rect::operator=(const Rect& rhs) noexcept=default | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Rect& opAssign(const Rect&in)", asMETHODPR(Rect, operator=, (const Rect&), Rect&), asCALL_THISCALL);
    // bool Rect::operator==(const Rect& rhs) const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "bool opEquals(const Rect&in) const", asMETHODPR(Rect, operator==, (const Rect&) const, bool), asCALL_THISCALL);
    // Rect::Rect(const Vector2& min, const Vector2& max) noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Vector2&in, const Vector2&in)", asFUNCTION(Rect_Rect_Vector2_Vector2), asCALL_CDECL_OBJFIRST);
    // Rect::Rect(float left, float top, float right, float bottom) noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(Rect_Rect_float_float_float_float), asCALL_CDECL_OBJFIRST);
    // explicit Rect::Rect(const Vector4& vector) noexcept | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Vector4&in)", asFUNCTION(Rect_Rect_Vector4), asCALL_CDECL_OBJFIRST);
    // explicit Rect::Rect(const float* data) noexcept | File: ../Math/Rect.h
    // Error: type "const float*" can not automatically bind
    // Rect::Rect(const Rect& rect) noexcept=default | File: ../Math/Rect.h
    engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", asFUNCTION(Rect_Rect_Rect), asCALL_CDECL_OBJFIRST);
    // float Rect::Right() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "float Right() const", asMETHODPR(Rect, Right, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "float get_right() const", asMETHODPR(Rect, Right, () const, float), asCALL_THISCALL);
    // Vector2 Rect::Size() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Vector2 Size() const", asMETHODPR(Rect, Size, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "Vector2 get_size() const", asMETHODPR(Rect, Size, () const, Vector2), asCALL_THISCALL);
    // float Rect::Top() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "float Top() const", asMETHODPR(Rect, Top, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Rect", "float get_top() const", asMETHODPR(Rect, Top, () const, float), asCALL_THISCALL);
    // String Rect::ToString() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "String ToString() const", asMETHODPR(Rect, ToString, () const, String), asCALL_THISCALL);
    // Vector4 Rect::ToVector4() const | File: ../Math/Rect.h
    engine->RegisterObjectMethod("Rect", "Vector4 ToVector4() const", asMETHODPR(Rect, ToVector4, () const, Vector4), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Rect
    REGISTER_MANUAL_PART_Rect(Rect, "Rect")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RefCounted", asBEHAVE_ADDREF, "void f()", asMETHODPR(RefCounted, AddRef, (), void), asCALL_THISCALL);
    // RefCounted::RefCounted() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RefCounted", asBEHAVE_FACTORY, "RefCounted@+ f()", asFUNCTION(RefCounted_RefCounted_void), asCALL_CDECL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RefCounted", "int Refs() const", asMETHODPR(RefCounted, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RefCounted", "int get_refs() const", asMETHODPR(RefCounted, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RefCounted", asBEHAVE_RELEASE, "void f()", asMETHODPR(RefCounted, ReleaseRef, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RefCounted", "int WeakRefs() const", asMETHODPR(RefCounted, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RefCounted", "int get_weakRefs() const", asMETHODPR(RefCounted, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(RefCounted, "RefCounted")
#endif

    // Vector<RenderPathCommand> RenderPath::commands_ | File: ../Graphics/RenderPath.h
    // Error: type "Vector<RenderPathCommand>" can not automatically bind
    // Vector<RenderTargetInfo> RenderPath::renderTargets_ | File: ../Graphics/RenderPath.h
    // Error: type "Vector<RenderTargetInfo>" can not automatically bind
    // void RenderPath::AddCommand(const RenderPathCommand& command) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void AddCommand(const RenderPathCommand&in)", asMETHODPR(RenderPath, AddCommand, (const RenderPathCommand&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RenderPath", asBEHAVE_ADDREF, "void f()", asMETHODPR(RenderPath, AddRef, (), void), asCALL_THISCALL);
    // void RenderPath::AddRenderTarget(const RenderTargetInfo& info) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void AddRenderTarget(const RenderTargetInfo&in)", asMETHODPR(RenderPath, AddRenderTarget, (const RenderTargetInfo&), void), asCALL_THISCALL);
    // bool RenderPath::Append(XMLFile* file) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "bool Append(XMLFile@+)", asMETHODPR(RenderPath, Append, (XMLFile*), bool), asCALL_THISCALL);
    // SharedPtr<RenderPath> RenderPath::Clone() | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "RenderPath@+ Clone()", asFUNCTION(RenderPath_Clone_void), asCALL_CDECL_OBJFIRST);
    // RenderPathCommand* RenderPath::GetCommand(unsigned index) | File: ../Graphics/RenderPath.h
    // Error: type "RenderPathCommand*" can not automatically bind
    // unsigned RenderPath::GetNumCommands() const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "uint GetNumCommands() const", asMETHODPR(RenderPath, GetNumCommands, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "uint get_numCommands() const", asMETHODPR(RenderPath, GetNumCommands, () const, unsigned), asCALL_THISCALL);
    // unsigned RenderPath::GetNumRenderTargets() const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "uint GetNumRenderTargets() const", asMETHODPR(RenderPath, GetNumRenderTargets, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "uint get_numRenderTargets() const", asMETHODPR(RenderPath, GetNumRenderTargets, () const, unsigned), asCALL_THISCALL);
    // const Variant& RenderPath::GetShaderParameter(const String& name) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "const Variant& GetShaderParameter(const String&in) const", asMETHODPR(RenderPath, GetShaderParameter, (const String&) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "const Variant& get_shaderParameters(const String&in) const", asMETHODPR(RenderPath, GetShaderParameter, (const String&) const, const Variant&), asCALL_THISCALL);
    // void RenderPath::InsertCommand(unsigned index, const RenderPathCommand& command) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void InsertCommand(uint, const RenderPathCommand&in)", asMETHODPR(RenderPath, InsertCommand, (unsigned, const RenderPathCommand&), void), asCALL_THISCALL);
    // bool RenderPath::IsAdded(const String& tag) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "bool IsAdded(const String&in) const", asMETHODPR(RenderPath, IsAdded, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "bool get_added(const String&in) const", asMETHODPR(RenderPath, IsAdded, (const String&) const, bool), asCALL_THISCALL);
    // bool RenderPath::IsEnabled(const String& tag) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "bool IsEnabled(const String&in) const", asMETHODPR(RenderPath, IsEnabled, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "bool get_enabled(const String&in) const", asMETHODPR(RenderPath, IsEnabled, (const String&) const, bool), asCALL_THISCALL);
    // bool RenderPath::Load(XMLFile* file) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "bool Load(XMLFile@+)", asMETHODPR(RenderPath, Load, (XMLFile*), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RenderPath", "int Refs() const", asMETHODPR(RenderPath, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "int get_refs() const", asMETHODPR(RenderPath, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RenderPath", asBEHAVE_RELEASE, "void f()", asMETHODPR(RenderPath, ReleaseRef, (), void), asCALL_THISCALL);
    // void RenderPath::RemoveCommand(unsigned index) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void RemoveCommand(uint)", asMETHODPR(RenderPath, RemoveCommand, (unsigned), void), asCALL_THISCALL);
    // void RenderPath::RemoveCommands(const String& tag) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void RemoveCommands(const String&in)", asMETHODPR(RenderPath, RemoveCommands, (const String&), void), asCALL_THISCALL);
    // void RenderPath::RemoveRenderTarget(unsigned index) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void RemoveRenderTarget(uint)", asMETHODPR(RenderPath, RemoveRenderTarget, (unsigned), void), asCALL_THISCALL);
    // void RenderPath::RemoveRenderTarget(const String& name) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void RemoveRenderTarget(const String&in)", asMETHODPR(RenderPath, RemoveRenderTarget, (const String&), void), asCALL_THISCALL);
    // void RenderPath::RemoveRenderTargets(const String& tag) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void RemoveRenderTargets(const String&in)", asMETHODPR(RenderPath, RemoveRenderTargets, (const String&), void), asCALL_THISCALL);
    // RenderPath::RenderPath() | File: ../Graphics/RenderPath.h
    engine->RegisterObjectBehaviour("RenderPath", asBEHAVE_FACTORY, "RenderPath@+ f()", asFUNCTION(RenderPath_RenderPath_void), asCALL_CDECL);
    // void RenderPath::SetCommand(unsigned index, const RenderPathCommand& command) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void SetCommand(uint, const RenderPathCommand&in)", asMETHODPR(RenderPath, SetCommand, (unsigned, const RenderPathCommand&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "void set_commands(uint, const RenderPathCommand&in)", asMETHODPR(RenderPath, SetCommand, (unsigned, const RenderPathCommand&), void), asCALL_THISCALL);
    // void RenderPath::SetEnabled(const String& tag, bool active) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void SetEnabled(const String&in, bool)", asMETHODPR(RenderPath, SetEnabled, (const String&, bool), void), asCALL_THISCALL);
    // void RenderPath::SetRenderTarget(unsigned index, const RenderTargetInfo& info) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void SetRenderTarget(uint, const RenderTargetInfo&in)", asMETHODPR(RenderPath, SetRenderTarget, (unsigned, const RenderTargetInfo&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "void set_renderTargets(uint, const RenderTargetInfo&in)", asMETHODPR(RenderPath, SetRenderTarget, (unsigned, const RenderTargetInfo&), void), asCALL_THISCALL);
    // void RenderPath::SetShaderParameter(const String& name, const Variant& value) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void SetShaderParameter(const String&in, const Variant&in)", asMETHODPR(RenderPath, SetShaderParameter, (const String&, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "void set_shaderParameters(const String&in, const Variant&in)", asMETHODPR(RenderPath, SetShaderParameter, (const String&, const Variant&), void), asCALL_THISCALL);
    // void RenderPath::ToggleEnabled(const String& tag) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPath", "void ToggleEnabled(const String&in)", asMETHODPR(RenderPath, ToggleEnabled, (const String&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RenderPath", "int WeakRefs() const", asMETHODPR(RenderPath, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPath", "int get_weakRefs() const", asMETHODPR(RenderPath, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("RenderSurface", asBEHAVE_ADDREF, "void f()", asMETHODPR(RenderSurface, AddRef, (), void), asCALL_THISCALL);
    // bool RenderSurface::CreateRenderBuffer(unsigned width, unsigned height, unsigned format, int multiSample) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "bool CreateRenderBuffer(uint, uint, uint, int)", asMETHODPR(RenderSurface, CreateRenderBuffer, (unsigned, unsigned, unsigned, int), bool), asCALL_THISCALL);
    // bool RenderSurface::GetAutoResolve() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "bool GetAutoResolve() const", asMETHODPR(RenderSurface, GetAutoResolve, () const, bool), asCALL_THISCALL);
    // int RenderSurface::GetHeight() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "int GetHeight() const", asMETHODPR(RenderSurface, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int get_height() const", asMETHODPR(RenderSurface, GetHeight, () const, int), asCALL_THISCALL);
    // RenderSurface* RenderSurface::GetLinkedDepthStencil() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ GetLinkedDepthStencil() const", asMETHODPR(RenderSurface, GetLinkedDepthStencil, () const, RenderSurface*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ get_linkedDepthStencil() const", asMETHODPR(RenderSurface, GetLinkedDepthStencil, () const, RenderSurface*), asCALL_THISCALL);
    // RenderSurface* RenderSurface::GetLinkedRenderTarget() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ GetLinkedRenderTarget() const", asMETHODPR(RenderSurface, GetLinkedRenderTarget, () const, RenderSurface*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "RenderSurface@+ get_linkedRenderTarget() const", asMETHODPR(RenderSurface, GetLinkedRenderTarget, () const, RenderSurface*), asCALL_THISCALL);
    // int RenderSurface::GetMultiSample() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "int GetMultiSample() const", asMETHODPR(RenderSurface, GetMultiSample, () const, int), asCALL_THISCALL);
    // unsigned RenderSurface::GetNumViewports() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "uint GetNumViewports() const", asMETHODPR(RenderSurface, GetNumViewports, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "uint get_numViewports() const", asMETHODPR(RenderSurface, GetNumViewports, () const, unsigned), asCALL_THISCALL);
    // Texture* RenderSurface::GetParentTexture() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "Texture@+ GetParentTexture() const", asMETHODPR(RenderSurface, GetParentTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "Texture@+ get_parentTexture() const", asMETHODPR(RenderSurface, GetParentTexture, () const, Texture*), asCALL_THISCALL);
    // void* RenderSurface::GetReadOnlyView() const | File: ../Graphics/RenderSurface.h
    // Error: type "void*" can not automatically bind
    // unsigned RenderSurface::GetRenderBuffer() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "uint GetRenderBuffer() const", asMETHODPR(RenderSurface, GetRenderBuffer, () const, unsigned), asCALL_THISCALL);
    // void* RenderSurface::GetRenderTargetView() const | File: ../Graphics/RenderSurface.h
    // Error: type "void*" can not automatically bind
    // void* RenderSurface::GetSurface() const | File: ../Graphics/RenderSurface.h
    // Error: type "void*" can not automatically bind
    // unsigned RenderSurface::GetTarget() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "uint GetTarget() const", asMETHODPR(RenderSurface, GetTarget, () const, unsigned), asCALL_THISCALL);
    // RenderSurfaceUpdateMode RenderSurface::GetUpdateMode() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "RenderSurfaceUpdateMode GetUpdateMode() const", asMETHODPR(RenderSurface, GetUpdateMode, () const, RenderSurfaceUpdateMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "RenderSurfaceUpdateMode get_updateMode() const", asMETHODPR(RenderSurface, GetUpdateMode, () const, RenderSurfaceUpdateMode), asCALL_THISCALL);
    // TextureUsage RenderSurface::GetUsage() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "TextureUsage GetUsage() const", asMETHODPR(RenderSurface, GetUsage, () const, TextureUsage), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "TextureUsage get_usage() const", asMETHODPR(RenderSurface, GetUsage, () const, TextureUsage), asCALL_THISCALL);
    // Viewport* RenderSurface::GetViewport(unsigned index) const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "Viewport@+ GetViewport(uint) const", asMETHODPR(RenderSurface, GetViewport, (unsigned) const, Viewport*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "Viewport@+ get_viewports(uint) const", asMETHODPR(RenderSurface, GetViewport, (unsigned) const, Viewport*), asCALL_THISCALL);
    // int RenderSurface::GetWidth() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "int GetWidth() const", asMETHODPR(RenderSurface, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int get_width() const", asMETHODPR(RenderSurface, GetWidth, () const, int), asCALL_THISCALL);
    // bool RenderSurface::IsResolveDirty() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "bool IsResolveDirty() const", asMETHODPR(RenderSurface, IsResolveDirty, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "bool get_resolveDirty() const", asMETHODPR(RenderSurface, IsResolveDirty, () const, bool), asCALL_THISCALL);
    // bool RenderSurface::IsUpdateQueued() const | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "bool IsUpdateQueued() const", asMETHODPR(RenderSurface, IsUpdateQueued, () const, bool), asCALL_THISCALL);
    // void RenderSurface::OnDeviceLost() | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void OnDeviceLost()", asMETHODPR(RenderSurface, OnDeviceLost, (), void), asCALL_THISCALL);
    // void RenderSurface::QueueUpdate() | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void QueueUpdate()", asMETHODPR(RenderSurface, QueueUpdate, (), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RenderSurface", "int Refs() const", asMETHODPR(RenderSurface, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int get_refs() const", asMETHODPR(RenderSurface, Refs, () const, int), asCALL_THISCALL);
    // void RenderSurface::Release() | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void Release()", asMETHODPR(RenderSurface, Release, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RenderSurface", asBEHAVE_RELEASE, "void f()", asMETHODPR(RenderSurface, ReleaseRef, (), void), asCALL_THISCALL);
    // explicit RenderSurface::RenderSurface(Texture* parentTexture) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectBehaviour("RenderSurface", asBEHAVE_FACTORY, "RenderSurface@+ f(Texture@+)", asFUNCTION(RenderSurface_RenderSurface_Texture), asCALL_CDECL);
    // void RenderSurface::ResetUpdateQueued() | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void ResetUpdateQueued()", asMETHODPR(RenderSurface, ResetUpdateQueued, (), void), asCALL_THISCALL);
    // void RenderSurface::SetLinkedDepthStencil(RenderSurface* depthStencil) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void SetLinkedDepthStencil(RenderSurface@+)", asMETHODPR(RenderSurface, SetLinkedDepthStencil, (RenderSurface*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_linkedDepthStencil(RenderSurface@+)", asMETHODPR(RenderSurface, SetLinkedDepthStencil, (RenderSurface*), void), asCALL_THISCALL);
    // void RenderSurface::SetLinkedRenderTarget(RenderSurface* renderTarget) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void SetLinkedRenderTarget(RenderSurface@+)", asMETHODPR(RenderSurface, SetLinkedRenderTarget, (RenderSurface*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_linkedRenderTarget(RenderSurface@+)", asMETHODPR(RenderSurface, SetLinkedRenderTarget, (RenderSurface*), void), asCALL_THISCALL);
    // void RenderSurface::SetNumViewports(unsigned num) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void SetNumViewports(uint)", asMETHODPR(RenderSurface, SetNumViewports, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_numViewports(uint)", asMETHODPR(RenderSurface, SetNumViewports, (unsigned), void), asCALL_THISCALL);
    // void RenderSurface::SetResolveDirty(bool enable) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void SetResolveDirty(bool)", asMETHODPR(RenderSurface, SetResolveDirty, (bool), void), asCALL_THISCALL);
    // void RenderSurface::SetUpdateMode(RenderSurfaceUpdateMode mode) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void SetUpdateMode(RenderSurfaceUpdateMode)", asMETHODPR(RenderSurface, SetUpdateMode, (RenderSurfaceUpdateMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_updateMode(RenderSurfaceUpdateMode)", asMETHODPR(RenderSurface, SetUpdateMode, (RenderSurfaceUpdateMode), void), asCALL_THISCALL);
    // void RenderSurface::SetViewport(unsigned index, Viewport* viewport) | File: ../Graphics/RenderSurface.h
    engine->RegisterObjectMethod("RenderSurface", "void SetViewport(uint, Viewport@+)", asMETHODPR(RenderSurface, SetViewport, (unsigned, Viewport*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "void set_viewports(uint, Viewport@+)", asMETHODPR(RenderSurface, SetViewport, (unsigned, Viewport*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RenderSurface", "int WeakRefs() const", asMETHODPR(RenderSurface, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderSurface", "int get_weakRefs() const", asMETHODPR(RenderSurface, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(RenderSurface, "RenderSurface")
#endif
#ifdef REGISTER_MANUAL_PART_RenderSurface
    REGISTER_MANUAL_PART_RenderSurface(RenderSurface, "RenderSurface")
#endif
    RegisterSubclass<RefCounted, RenderSurface>(engine, "RefCounted", "RenderSurface");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Renderer", asBEHAVE_ADDREF, "void f()", asMETHODPR(Renderer, AddRef, (), void), asCALL_THISCALL);
    // void Renderer::ApplyShadowMapFilter(View* view, Texture2D* shadowMap, float blurScale) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void ApplyShadowMapFilter(View@+, Texture2D@+, float)", asMETHODPR(Renderer, ApplyShadowMapFilter, (View*, Texture2D*, float), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Renderer::DrawDebugGeometry(bool depthTest) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void DrawDebugGeometry(bool)", asMETHODPR(Renderer, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
    // static View* Renderer::GetActualView(View* view) | File: ../Graphics/Renderer.h
    engine->SetDefaultNamespace("Renderer");
    engine->RegisterGlobalFunction("View@+ GetActualView(View@+)", asFUNCTIONPR(Renderer::GetActualView, (View*), View*), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "bool GetBlockEvents() const", asMETHODPR(Renderer, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "const String& GetCategory() const", asMETHODPR(Renderer, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "const String& get_category() const", asMETHODPR(Renderer, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // Texture2D* Renderer::GetDefaultLightRamp() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Texture2D@+ GetDefaultLightRamp() const", asMETHODPR(Renderer, GetDefaultLightRamp, () const, Texture2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Texture2D@+ get_defaultLightRamp() const", asMETHODPR(Renderer, GetDefaultLightRamp, () const, Texture2D*), asCALL_THISCALL);
    // Texture2D* Renderer::GetDefaultLightSpot() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Texture2D@+ GetDefaultLightSpot() const", asMETHODPR(Renderer, GetDefaultLightSpot, () const, Texture2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Texture2D@+ get_defaultLightSpot() const", asMETHODPR(Renderer, GetDefaultLightSpot, () const, Texture2D*), asCALL_THISCALL);
    // Material* Renderer::GetDefaultMaterial() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Material@+ GetDefaultMaterial() const", asMETHODPR(Renderer, GetDefaultMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Material@+ get_defaultMaterial() const", asMETHODPR(Renderer, GetDefaultMaterial, () const, Material*), asCALL_THISCALL);
    // RenderPath* Renderer::GetDefaultRenderPath() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "RenderPath@+ GetDefaultRenderPath() const", asMETHODPR(Renderer, GetDefaultRenderPath, () const, RenderPath*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "RenderPath@+ get_defaultRenderPath() const", asMETHODPR(Renderer, GetDefaultRenderPath, () const, RenderPath*), asCALL_THISCALL);
    // Technique* Renderer::GetDefaultTechnique() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Technique@+ GetDefaultTechnique() const", asMETHODPR(Renderer, GetDefaultTechnique, () const, Technique*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Technique@+ get_defaultTechnique() const", asMETHODPR(Renderer, GetDefaultTechnique, () const, Technique*), asCALL_THISCALL);
    // Zone* Renderer::GetDefaultZone() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Zone@+ GetDefaultZone() const", asMETHODPR(Renderer, GetDefaultZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Zone@+ get_defaultZone() const", asMETHODPR(Renderer, GetDefaultZone, () const, Zone*), asCALL_THISCALL);
    // RenderSurface* Renderer::GetDepthStencil(int width, int height, int multiSample, bool autoResolve) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "RenderSurface@+ GetDepthStencil(int, int, int, bool)", asMETHODPR(Renderer, GetDepthStencil, (int, int, int, bool), RenderSurface*), asCALL_THISCALL);
    // bool Renderer::GetDrawShadows() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool GetDrawShadows() const", asMETHODPR(Renderer, GetDrawShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_drawShadows() const", asMETHODPR(Renderer, GetDrawShadows, () const, bool), asCALL_THISCALL);
    // bool Renderer::GetDynamicInstancing() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool GetDynamicInstancing() const", asMETHODPR(Renderer, GetDynamicInstancing, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_dynamicInstancing() const", asMETHODPR(Renderer, GetDynamicInstancing, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "VariantMap& GetEventDataMap() const", asMETHODPR(Renderer, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "Object@+ GetEventSender() const", asMETHODPR(Renderer, GetEventSender, () const, Object*), asCALL_THISCALL);
    // TextureCube* Renderer::GetFaceSelectCubeMap() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "TextureCube@+ GetFaceSelectCubeMap() const", asMETHODPR(Renderer, GetFaceSelectCubeMap, () const, TextureCube*), asCALL_THISCALL);
    // const FrameInfo& Renderer::GetFrameInfo() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "const FrameInfo& GetFrameInfo() const", asMETHODPR(Renderer, GetFrameInfo, () const, const FrameInfo&), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Renderer, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Renderer, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "const VariantMap& GetGlobalVars() const", asMETHODPR(Renderer, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "const VariantMap& get_globalVars() const", asMETHODPR(Renderer, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // bool Renderer::GetHDRRendering() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool GetHDRRendering() const", asMETHODPR(Renderer, GetHDRRendering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_hdrRendering() const", asMETHODPR(Renderer, GetHDRRendering, () const, bool), asCALL_THISCALL);
    // TextureCube* Renderer::GetIndirectionCubeMap() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "TextureCube@+ GetIndirectionCubeMap() const", asMETHODPR(Renderer, GetIndirectionCubeMap, () const, TextureCube*), asCALL_THISCALL);
    // VertexBuffer* Renderer::GetInstancingBuffer() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "VertexBuffer@+ GetInstancingBuffer() const", asMETHODPR(Renderer, GetInstancingBuffer, () const, VertexBuffer*), asCALL_THISCALL);
    // Geometry* Renderer::GetLightGeometry(Light* light) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Geometry@+ GetLightGeometry(Light@+)", asMETHODPR(Renderer, GetLightGeometry, (Light*), Geometry*), asCALL_THISCALL);
    // const Rect& Renderer::GetLightScissor(Light* light, Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "const Rect& GetLightScissor(Light@+, Camera@+)", asMETHODPR(Renderer, GetLightScissor, (Light*, Camera*), const Rect&), asCALL_THISCALL);
    // MaterialQuality Renderer::GetMaterialQuality() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "MaterialQuality GetMaterialQuality() const", asMETHODPR(Renderer, GetMaterialQuality, () const, MaterialQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "MaterialQuality get_materialQuality() const", asMETHODPR(Renderer, GetMaterialQuality, () const, MaterialQuality), asCALL_THISCALL);
    // int Renderer::GetMaxOccluderTriangles() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetMaxOccluderTriangles() const", asMETHODPR(Renderer, GetMaxOccluderTriangles, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_maxOccluderTriangles() const", asMETHODPR(Renderer, GetMaxOccluderTriangles, () const, int), asCALL_THISCALL);
    // int Renderer::GetMaxShadowMaps() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetMaxShadowMaps() const", asMETHODPR(Renderer, GetMaxShadowMaps, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_maxShadowMaps() const", asMETHODPR(Renderer, GetMaxShadowMaps, () const, int), asCALL_THISCALL);
    // int Renderer::GetMaxSortedInstances() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetMaxSortedInstances() const", asMETHODPR(Renderer, GetMaxSortedInstances, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_maxSortedInstances() const", asMETHODPR(Renderer, GetMaxSortedInstances, () const, int), asCALL_THISCALL);
    // int Renderer::GetMinInstances() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetMinInstances() const", asMETHODPR(Renderer, GetMinInstances, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_minInstances() const", asMETHODPR(Renderer, GetMinInstances, () const, int), asCALL_THISCALL);
    // float Renderer::GetMobileNormalOffsetMul() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "float GetMobileNormalOffsetMul() const", asMETHODPR(Renderer, GetMobileNormalOffsetMul, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "float get_mobileNormalOffsetMul() const", asMETHODPR(Renderer, GetMobileNormalOffsetMul, () const, float), asCALL_THISCALL);
    // float Renderer::GetMobileShadowBiasAdd() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "float GetMobileShadowBiasAdd() const", asMETHODPR(Renderer, GetMobileShadowBiasAdd, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "float get_mobileShadowBiasAdd() const", asMETHODPR(Renderer, GetMobileShadowBiasAdd, () const, float), asCALL_THISCALL);
    // float Renderer::GetMobileShadowBiasMul() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "float GetMobileShadowBiasMul() const", asMETHODPR(Renderer, GetMobileShadowBiasMul, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "float get_mobileShadowBiasMul() const", asMETHODPR(Renderer, GetMobileShadowBiasMul, () const, float), asCALL_THISCALL);
    // unsigned Renderer::GetNumBatches() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumBatches() const", asMETHODPR(Renderer, GetNumBatches, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numBatches() const", asMETHODPR(Renderer, GetNumBatches, () const, unsigned), asCALL_THISCALL);
    // int Renderer::GetNumExtraInstancingBufferElements() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetNumExtraInstancingBufferElements() const", asMETHODPR(Renderer, GetNumExtraInstancingBufferElements, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_numExtraInstancingBufferElements() const", asMETHODPR(Renderer, GetNumExtraInstancingBufferElements, () const, int), asCALL_THISCALL);
    // unsigned Renderer::GetNumGeometries(bool allViews=false) const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumGeometries(bool = false) const", asMETHODPR(Renderer, GetNumGeometries, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numGeometries(bool = false) const", asMETHODPR(Renderer, GetNumGeometries, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Renderer::GetNumLights(bool allViews=false) const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumLights(bool = false) const", asMETHODPR(Renderer, GetNumLights, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numLights(bool = false) const", asMETHODPR(Renderer, GetNumLights, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Renderer::GetNumOccluders(bool allViews=false) const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumOccluders(bool = false) const", asMETHODPR(Renderer, GetNumOccluders, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numOccluders(bool = false) const", asMETHODPR(Renderer, GetNumOccluders, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Renderer::GetNumPrimitives() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumPrimitives() const", asMETHODPR(Renderer, GetNumPrimitives, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numPrimitives() const", asMETHODPR(Renderer, GetNumPrimitives, () const, unsigned), asCALL_THISCALL);
    // unsigned Renderer::GetNumShadowMaps(bool allViews=false) const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumShadowMaps(bool = false) const", asMETHODPR(Renderer, GetNumShadowMaps, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numShadowMaps(bool = false) const", asMETHODPR(Renderer, GetNumShadowMaps, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Renderer::GetNumViewports() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumViewports() const", asMETHODPR(Renderer, GetNumViewports, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numViewports() const", asMETHODPR(Renderer, GetNumViewports, () const, unsigned), asCALL_THISCALL);
    // unsigned Renderer::GetNumViews() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "uint GetNumViews() const", asMETHODPR(Renderer, GetNumViews, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "uint get_numViews() const", asMETHODPR(Renderer, GetNumViews, () const, unsigned), asCALL_THISCALL);
    // float Renderer::GetOccluderSizeThreshold() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "float GetOccluderSizeThreshold() const", asMETHODPR(Renderer, GetOccluderSizeThreshold, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "float get_occluderSizeThreshold() const", asMETHODPR(Renderer, GetOccluderSizeThreshold, () const, float), asCALL_THISCALL);
    // OcclusionBuffer* Renderer::GetOcclusionBuffer(Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "OcclusionBuffer@+ GetOcclusionBuffer(Camera@+)", asMETHODPR(Renderer, GetOcclusionBuffer, (Camera*), OcclusionBuffer*), asCALL_THISCALL);
    // int Renderer::GetOcclusionBufferSize() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetOcclusionBufferSize() const", asMETHODPR(Renderer, GetOcclusionBufferSize, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_occlusionBufferSize() const", asMETHODPR(Renderer, GetOcclusionBufferSize, () const, int), asCALL_THISCALL);
    // View* Renderer::GetPreparedView(Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "View@+ GetPreparedView(Camera@+)", asMETHODPR(Renderer, GetPreparedView, (Camera*), View*), asCALL_THISCALL);
    // Geometry* Renderer::GetQuadGeometry() | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Geometry@+ GetQuadGeometry()", asMETHODPR(Renderer, GetQuadGeometry, (), Geometry*), asCALL_THISCALL);
    // bool Renderer::GetReuseShadowMaps() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool GetReuseShadowMaps() const", asMETHODPR(Renderer, GetReuseShadowMaps, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_reuseShadowMaps() const", asMETHODPR(Renderer, GetReuseShadowMaps, () const, bool), asCALL_THISCALL);
    // Texture* Renderer::GetScreenBuffer(int width, int height, unsigned format, int multiSample, bool autoResolve, bool cubemap, bool filtered, bool srgb, unsigned persistentKey=0) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Texture@+ GetScreenBuffer(int, int, uint, int, bool, bool, bool, bool, uint = 0)", asMETHODPR(Renderer, GetScreenBuffer, (int, int, unsigned, int, bool, bool, bool, bool, unsigned), Texture*), asCALL_THISCALL);
    // Camera* Renderer::GetShadowCamera() | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Camera@+ GetShadowCamera()", asMETHODPR(Renderer, GetShadowCamera, (), Camera*), asCALL_THISCALL);
    // Texture2D* Renderer::GetShadowMap(Light* light, Camera* camera, unsigned viewWidth, unsigned viewHeight) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Texture2D@+ GetShadowMap(Light@+, Camera@+, uint, uint)", asMETHODPR(Renderer, GetShadowMap, (Light*, Camera*, unsigned, unsigned), Texture2D*), asCALL_THISCALL);
    // int Renderer::GetShadowMapSize() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetShadowMapSize() const", asMETHODPR(Renderer, GetShadowMapSize, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_shadowMapSize() const", asMETHODPR(Renderer, GetShadowMapSize, () const, int), asCALL_THISCALL);
    // ShadowQuality Renderer::GetShadowQuality() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "ShadowQuality GetShadowQuality() const", asMETHODPR(Renderer, GetShadowQuality, () const, ShadowQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "ShadowQuality get_shadowQuality() const", asMETHODPR(Renderer, GetShadowQuality, () const, ShadowQuality), asCALL_THISCALL);
    // float Renderer::GetShadowSoftness() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "float GetShadowSoftness() const", asMETHODPR(Renderer, GetShadowSoftness, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "float get_shadowSoftness() const", asMETHODPR(Renderer, GetShadowSoftness, () const, float), asCALL_THISCALL);
    // bool Renderer::GetSpecularLighting() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool GetSpecularLighting() const", asMETHODPR(Renderer, GetSpecularLighting, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_specularLighting() const", asMETHODPR(Renderer, GetSpecularLighting, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Renderer, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // int Renderer::GetTextureAnisotropy() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetTextureAnisotropy() const", asMETHODPR(Renderer, GetTextureAnisotropy, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_textureAnisotropy() const", asMETHODPR(Renderer, GetTextureAnisotropy, () const, int), asCALL_THISCALL);
    // TextureFilterMode Renderer::GetTextureFilterMode() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "TextureFilterMode GetTextureFilterMode() const", asMETHODPR(Renderer, GetTextureFilterMode, () const, TextureFilterMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "TextureFilterMode get_textureFilterMode() const", asMETHODPR(Renderer, GetTextureFilterMode, () const, TextureFilterMode), asCALL_THISCALL);
    // MaterialQuality Renderer::GetTextureQuality() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "MaterialQuality GetTextureQuality() const", asMETHODPR(Renderer, GetTextureQuality, () const, MaterialQuality), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "MaterialQuality get_textureQuality() const", asMETHODPR(Renderer, GetTextureQuality, () const, MaterialQuality), asCALL_THISCALL);
    // bool Renderer::GetThreadedOcclusion() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool GetThreadedOcclusion() const", asMETHODPR(Renderer, GetThreadedOcclusion, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "bool get_threadedOcclusion() const", asMETHODPR(Renderer, GetThreadedOcclusion, () const, bool), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "StringHash GetType() const", asMETHODPR(Renderer, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "StringHash get_type() const", asMETHODPR(Renderer, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "const String& GetTypeName() const", asMETHODPR(Renderer, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "const String& get_typeName() const", asMETHODPR(Renderer, GetTypeName, () const, const String&), asCALL_THISCALL);
    // Viewport* Renderer::GetViewport(unsigned index) const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Viewport@+ GetViewport(uint) const", asMETHODPR(Renderer, GetViewport, (unsigned) const, Viewport*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Viewport@+ get_viewports(uint) const", asMETHODPR(Renderer, GetViewport, (unsigned) const, Viewport*), asCALL_THISCALL);
    // Viewport* Renderer::GetViewportForScene(Scene* scene, unsigned index) const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Viewport@+ GetViewportForScene(Scene@+, uint) const", asMETHODPR(Renderer, GetViewportForScene, (Scene*, unsigned) const, Viewport*), asCALL_THISCALL);
    // int Renderer::GetVSMMultiSample() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "int GetVSMMultiSample() const", asMETHODPR(Renderer, GetVSMMultiSample, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_vsmMultiSample() const", asMETHODPR(Renderer, GetVSMMultiSample, () const, int), asCALL_THISCALL);
    // Vector2 Renderer::GetVSMShadowParameters() const | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "Vector2 GetVSMShadowParameters() const", asMETHODPR(Renderer, GetVSMShadowParameters, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "Vector2 get_vsmShadowParameters() const", asMETHODPR(Renderer, GetVSMShadowParameters, () const, Vector2), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "bool HasEventHandlers() const", asMETHODPR(Renderer, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Renderer, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Renderer, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "bool IsInstanceOf(StringHash) const", asMETHODPR(Renderer, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Renderer, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // void Renderer::OptimizeLightByScissor(Light* light, Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void OptimizeLightByScissor(Light@+, Camera@+)", asMETHODPR(Renderer, OptimizeLightByScissor, (Light*, Camera*), void), asCALL_THISCALL);
    // void Renderer::OptimizeLightByStencil(Light* light, Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void OptimizeLightByStencil(Light@+, Camera@+)", asMETHODPR(Renderer, OptimizeLightByStencil, (Light*, Camera*), void), asCALL_THISCALL);
    // void Renderer::QueueRenderSurface(RenderSurface* renderTarget) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void QueueRenderSurface(RenderSurface@+)", asMETHODPR(Renderer, QueueRenderSurface, (RenderSurface*), void), asCALL_THISCALL);
    // void Renderer::QueueViewport(RenderSurface* renderTarget, Viewport* viewport) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void QueueViewport(RenderSurface@+, Viewport@+)", asMETHODPR(Renderer, QueueViewport, (RenderSurface*, Viewport*), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Renderer", "int Refs() const", asMETHODPR(Renderer, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_refs() const", asMETHODPR(Renderer, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Renderer", asBEHAVE_RELEASE, "void f()", asMETHODPR(Renderer, ReleaseRef, (), void), asCALL_THISCALL);
    // void Renderer::ReloadShaders() | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void ReloadShaders()", asMETHODPR(Renderer, ReloadShaders, (), void), asCALL_THISCALL);
    // void Renderer::Render() | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void Render()", asMETHODPR(Renderer, Render, (), void), asCALL_THISCALL);
    // explicit Renderer::Renderer(Context* context) | File: ../Graphics/Renderer.h
    engine->RegisterObjectBehaviour("Renderer", asBEHAVE_FACTORY, "Renderer@+ f()", asFUNCTION(Renderer_Renderer_Context), asCALL_CDECL);
    // bool Renderer::ResizeInstancingBuffer(unsigned numInstances) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "bool ResizeInstancingBuffer(uint)", asMETHODPR(Renderer, ResizeInstancingBuffer, (unsigned), bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void SendEvent(StringHash)", asMETHODPR(Renderer, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Renderer, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Renderer::SetBatchShaders(Batch& batch, Technique* tech, bool allowShadows, const BatchQueue& queue) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetBatchShaders(Batch&, Technique@+, bool, const BatchQueue&in)", asMETHODPR(Renderer, SetBatchShaders, (Batch&, Technique*, bool, const BatchQueue&), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void SetBlockEvents(bool)", asMETHODPR(Renderer, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Renderer::SetCullMode(CullMode mode, Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetCullMode(CullMode, Camera@+)", asMETHODPR(Renderer, SetCullMode, (CullMode, Camera*), void), asCALL_THISCALL);
    // void Renderer::SetDefaultRenderPath(RenderPath* renderPath) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetDefaultRenderPath(RenderPath@+)", asMETHODPR(Renderer, SetDefaultRenderPath, (RenderPath*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_defaultRenderPath(RenderPath@+)", asMETHODPR(Renderer, SetDefaultRenderPath, (RenderPath*), void), asCALL_THISCALL);
    // void Renderer::SetDefaultRenderPath(XMLFile* xmlFile) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetDefaultRenderPath(XMLFile@+)", asMETHODPR(Renderer, SetDefaultRenderPath, (XMLFile*), void), asCALL_THISCALL);
    // void Renderer::SetDefaultTechnique(Technique* technique) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetDefaultTechnique(Technique@+)", asMETHODPR(Renderer, SetDefaultTechnique, (Technique*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_defaultTechnique(Technique@+)", asMETHODPR(Renderer, SetDefaultTechnique, (Technique*), void), asCALL_THISCALL);
    // void Renderer::SetDrawShadows(bool enable) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetDrawShadows(bool)", asMETHODPR(Renderer, SetDrawShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_drawShadows(bool)", asMETHODPR(Renderer, SetDrawShadows, (bool), void), asCALL_THISCALL);
    // void Renderer::SetDynamicInstancing(bool enable) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetDynamicInstancing(bool)", asMETHODPR(Renderer, SetDynamicInstancing, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_dynamicInstancing(bool)", asMETHODPR(Renderer, SetDynamicInstancing, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Renderer, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Renderer, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Renderer::SetHDRRendering(bool enable) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetHDRRendering(bool)", asMETHODPR(Renderer, SetHDRRendering, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_hdrRendering(bool)", asMETHODPR(Renderer, SetHDRRendering, (bool), void), asCALL_THISCALL);
    // void Renderer::SetLightVolumeBatchShaders(Batch& batch, Camera* camera, const String& vsName, const String& psName, const String& vsDefines, const String& psDefines) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetLightVolumeBatchShaders(Batch&, Camera@+, const String&in, const String&in, const String&in, const String&in)", asMETHODPR(Renderer, SetLightVolumeBatchShaders, (Batch&, Camera*, const String&, const String&, const String&, const String&), void), asCALL_THISCALL);
    // void Renderer::SetMaterialQuality(MaterialQuality quality) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMaterialQuality(MaterialQuality)", asMETHODPR(Renderer, SetMaterialQuality, (MaterialQuality), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_materialQuality(MaterialQuality)", asMETHODPR(Renderer, SetMaterialQuality, (MaterialQuality), void), asCALL_THISCALL);
    // void Renderer::SetMaxOccluderTriangles(int triangles) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMaxOccluderTriangles(int)", asMETHODPR(Renderer, SetMaxOccluderTriangles, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_maxOccluderTriangles(int)", asMETHODPR(Renderer, SetMaxOccluderTriangles, (int), void), asCALL_THISCALL);
    // void Renderer::SetMaxShadowMaps(int shadowMaps) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMaxShadowMaps(int)", asMETHODPR(Renderer, SetMaxShadowMaps, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_maxShadowMaps(int)", asMETHODPR(Renderer, SetMaxShadowMaps, (int), void), asCALL_THISCALL);
    // void Renderer::SetMaxSortedInstances(int instances) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMaxSortedInstances(int)", asMETHODPR(Renderer, SetMaxSortedInstances, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_maxSortedInstances(int)", asMETHODPR(Renderer, SetMaxSortedInstances, (int), void), asCALL_THISCALL);
    // void Renderer::SetMinInstances(int instances) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMinInstances(int)", asMETHODPR(Renderer, SetMinInstances, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_minInstances(int)", asMETHODPR(Renderer, SetMinInstances, (int), void), asCALL_THISCALL);
    // void Renderer::SetMobileNormalOffsetMul(float mul) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMobileNormalOffsetMul(float)", asMETHODPR(Renderer, SetMobileNormalOffsetMul, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_mobileNormalOffsetMul(float)", asMETHODPR(Renderer, SetMobileNormalOffsetMul, (float), void), asCALL_THISCALL);
    // void Renderer::SetMobileShadowBiasAdd(float add) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMobileShadowBiasAdd(float)", asMETHODPR(Renderer, SetMobileShadowBiasAdd, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_mobileShadowBiasAdd(float)", asMETHODPR(Renderer, SetMobileShadowBiasAdd, (float), void), asCALL_THISCALL);
    // void Renderer::SetMobileShadowBiasMul(float mul) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetMobileShadowBiasMul(float)", asMETHODPR(Renderer, SetMobileShadowBiasMul, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_mobileShadowBiasMul(float)", asMETHODPR(Renderer, SetMobileShadowBiasMul, (float), void), asCALL_THISCALL);
    // void Renderer::SetNumExtraInstancingBufferElements(int elements) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetNumExtraInstancingBufferElements(int)", asMETHODPR(Renderer, SetNumExtraInstancingBufferElements, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_numExtraInstancingBufferElements(int)", asMETHODPR(Renderer, SetNumExtraInstancingBufferElements, (int), void), asCALL_THISCALL);
    // void Renderer::SetNumViewports(unsigned num) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetNumViewports(uint)", asMETHODPR(Renderer, SetNumViewports, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_numViewports(uint)", asMETHODPR(Renderer, SetNumViewports, (unsigned), void), asCALL_THISCALL);
    // void Renderer::SetOccluderSizeThreshold(float screenSize) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetOccluderSizeThreshold(float)", asMETHODPR(Renderer, SetOccluderSizeThreshold, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_occluderSizeThreshold(float)", asMETHODPR(Renderer, SetOccluderSizeThreshold, (float), void), asCALL_THISCALL);
    // void Renderer::SetOcclusionBufferSize(int size) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetOcclusionBufferSize(int)", asMETHODPR(Renderer, SetOcclusionBufferSize, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_occlusionBufferSize(int)", asMETHODPR(Renderer, SetOcclusionBufferSize, (int), void), asCALL_THISCALL);
    // void Renderer::SetReuseShadowMaps(bool enable) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetReuseShadowMaps(bool)", asMETHODPR(Renderer, SetReuseShadowMaps, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_reuseShadowMaps(bool)", asMETHODPR(Renderer, SetReuseShadowMaps, (bool), void), asCALL_THISCALL);
    // void Renderer::SetShadowMapFilter(Object* instance, ShadowMapFilter functionPtr) | File: ../Graphics/Renderer.h
    // Not registered because have @nobind mark
    // void Renderer::SetShadowMapSize(int size) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetShadowMapSize(int)", asMETHODPR(Renderer, SetShadowMapSize, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_shadowMapSize(int)", asMETHODPR(Renderer, SetShadowMapSize, (int), void), asCALL_THISCALL);
    // void Renderer::SetShadowQuality(ShadowQuality quality) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetShadowQuality(ShadowQuality)", asMETHODPR(Renderer, SetShadowQuality, (ShadowQuality), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_shadowQuality(ShadowQuality)", asMETHODPR(Renderer, SetShadowQuality, (ShadowQuality), void), asCALL_THISCALL);
    // void Renderer::SetShadowSoftness(float shadowSoftness) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetShadowSoftness(float)", asMETHODPR(Renderer, SetShadowSoftness, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_shadowSoftness(float)", asMETHODPR(Renderer, SetShadowSoftness, (float), void), asCALL_THISCALL);
    // void Renderer::SetSpecularLighting(bool enable) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetSpecularLighting(bool)", asMETHODPR(Renderer, SetSpecularLighting, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_specularLighting(bool)", asMETHODPR(Renderer, SetSpecularLighting, (bool), void), asCALL_THISCALL);
    // void Renderer::SetTextureAnisotropy(int level) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetTextureAnisotropy(int)", asMETHODPR(Renderer, SetTextureAnisotropy, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_textureAnisotropy(int)", asMETHODPR(Renderer, SetTextureAnisotropy, (int), void), asCALL_THISCALL);
    // void Renderer::SetTextureFilterMode(TextureFilterMode mode) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetTextureFilterMode(TextureFilterMode)", asMETHODPR(Renderer, SetTextureFilterMode, (TextureFilterMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_textureFilterMode(TextureFilterMode)", asMETHODPR(Renderer, SetTextureFilterMode, (TextureFilterMode), void), asCALL_THISCALL);
    // void Renderer::SetTextureQuality(MaterialQuality quality) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetTextureQuality(MaterialQuality)", asMETHODPR(Renderer, SetTextureQuality, (MaterialQuality), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_textureQuality(MaterialQuality)", asMETHODPR(Renderer, SetTextureQuality, (MaterialQuality), void), asCALL_THISCALL);
    // void Renderer::SetThreadedOcclusion(bool enable) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetThreadedOcclusion(bool)", asMETHODPR(Renderer, SetThreadedOcclusion, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_threadedOcclusion(bool)", asMETHODPR(Renderer, SetThreadedOcclusion, (bool), void), asCALL_THISCALL);
    // void Renderer::SetViewport(unsigned index, Viewport* viewport) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetViewport(uint, Viewport@+)", asMETHODPR(Renderer, SetViewport, (unsigned, Viewport*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_viewports(uint, Viewport@+)", asMETHODPR(Renderer, SetViewport, (unsigned, Viewport*), void), asCALL_THISCALL);
    // void Renderer::SetVSMMultiSample(int multiSample) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetVSMMultiSample(int)", asMETHODPR(Renderer, SetVSMMultiSample, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "void set_vsmMultiSample(int)", asMETHODPR(Renderer, SetVSMMultiSample, (int), void), asCALL_THISCALL);
    // void Renderer::SetVSMShadowParameters(float minVariance, float lightBleedingReduction) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void SetVSMShadowParameters(float, float)", asMETHODPR(Renderer, SetVSMShadowParameters, (float, float), void), asCALL_THISCALL);
    // void Renderer::StorePreparedView(View* view, Camera* camera) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void StorePreparedView(View@+, Camera@+)", asMETHODPR(Renderer, StorePreparedView, (View*, Camera*), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void UnsubscribeFromAllEvents()", asMETHODPR(Renderer, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Renderer_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Renderer, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Renderer, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Renderer, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Renderer::Update(float timeStep) | File: ../Graphics/Renderer.h
    engine->RegisterObjectMethod("Renderer", "void Update(float)", asMETHODPR(Renderer, Update, (float), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Renderer", "int WeakRefs() const", asMETHODPR(Renderer, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer", "int get_weakRefs() const", asMETHODPR(Renderer, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Renderer2D", "void AddDrawable(Drawable2D@+)", asMETHODPR(Renderer2D, AddDrawable, (Drawable2D*), void), asCALL_THISCALL);
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void AddLight(Light@+)", asMETHODPR(Renderer2D, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Renderer2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(Renderer2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void AddVertexLight(Light@+)", asMETHODPR(Renderer2D, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void AllocateNetworkState()", asMETHODPR(Renderer2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void ApplyAttributes()", asMETHODPR(Renderer2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool Renderer2D::CheckVisibility(Drawable2D* drawable) const | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectMethod("Renderer2D", "bool CheckVisibility(Drawable2D@+) const", asMETHODPR(Renderer2D, CheckVisibility, (Drawable2D*) const, bool), asCALL_THISCALL);
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Renderer2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(Renderer2D, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "bool GetAnimationEnabled() const", asMETHODPR(Renderer2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_animationEnabled() const", asMETHODPR(Renderer2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "Variant GetAttribute(uint) const", asMETHODPR(Renderer2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "Variant get_attributes(uint) const", asMETHODPR(Renderer2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "Variant GetAttribute(const String&in) const", asMETHODPR(Renderer2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Renderer2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Renderer2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Renderer2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Renderer2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(Renderer2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(Renderer2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Renderer2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "bool GetBlockEvents() const", asMETHODPR(Renderer2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "const BoundingBox& GetBoundingBox() const", asMETHODPR(Renderer2D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "const BoundingBox& get_boundingBox() const", asMETHODPR(Renderer2D, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool GetCastShadows() const", asMETHODPR(Renderer2D, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_castShadows() const", asMETHODPR(Renderer2D, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "const String& GetCategory() const", asMETHODPR(Renderer2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "const String& get_category() const", asMETHODPR(Renderer2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(Renderer2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Renderer2D", "float GetDistance() const", asMETHODPR(Renderer2D, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint8 GetDrawableFlags() const", asMETHODPR(Renderer2D, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetDrawDistance() const", asMETHODPR(Renderer2D, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "float get_drawDistance() const", asMETHODPR(Renderer2D, GetDrawDistance, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "VariantMap& GetEventDataMap() const", asMETHODPR(Renderer2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "Object@+ GetEventSender() const", asMETHODPR(Renderer2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "Light@+ GetFirstLight() const", asMETHODPR(Renderer2D, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Renderer2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Renderer2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(Renderer2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "const VariantMap& get_globalVars() const", asMETHODPR(Renderer2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetID() const", asMETHODPR(Renderer2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_id() const", asMETHODPR(Renderer2D, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Renderer2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetLightMask() const", asMETHODPR(Renderer2D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_lightMask() const", asMETHODPR(Renderer2D, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "Array<Light@>@ GetLights() const", asFUNCTION(Renderer2D_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetLodBias() const", asMETHODPR(Renderer2D, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "float get_lodBias() const", asMETHODPR(Renderer2D, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetLodDistance() const", asMETHODPR(Renderer2D, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(Renderer2D, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // Material* Renderer2D::GetMaterial(Texture2D* texture, BlendMode blendMode) | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectMethod("Renderer2D", "Material@+ GetMaterial(Texture2D@+, BlendMode)", asMETHODPR(Renderer2D, GetMaterial, (Texture2D*, BlendMode), Material*), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetMaxLights() const", asMETHODPR(Renderer2D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_maxLights() const", asMETHODPR(Renderer2D, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetMaxZ() const", asMETHODPR(Renderer2D, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetMinZ() const", asMETHODPR(Renderer2D, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "Node@+ GetNode() const", asMETHODPR(Renderer2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "Node@+ get_node() const", asMETHODPR(Renderer2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetNumAttributes() const", asMETHODPR(Renderer2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_numAttributes() const", asMETHODPR(Renderer2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetNumNetworkAttributes() const", asMETHODPR(Renderer2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetNumOccluderTriangles()", asMETHODPR(Renderer2D, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Renderer2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Renderer2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Renderer2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "Scene@+ GetScene() const", asMETHODPR(Renderer2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetShadowDistance() const", asMETHODPR(Renderer2D, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "float get_shadowDistance() const", asMETHODPR(Renderer2D, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetShadowMask() const", asMETHODPR(Renderer2D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_shadowMask() const", asMETHODPR(Renderer2D, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "float GetSortValue() const", asMETHODPR(Renderer2D, GetSortValue, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Renderer2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "StringHash GetType() const", asMETHODPR(Renderer2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "StringHash get_type() const", asMETHODPR(Renderer2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "const String& GetTypeName() const", asMETHODPR(Renderer2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "const String& get_typeName() const", asMETHODPR(Renderer2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // UpdateGeometryType Renderer2D::GetUpdateGeometryType() override | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectMethod("Renderer2D", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(Renderer2D, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "Array<Light@>@ GetVertexLights() const", asFUNCTION(Renderer2D_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetViewMask() const", asMETHODPR(Renderer2D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_viewMask() const", asMETHODPR(Renderer2D, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(Renderer2D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(Renderer2D, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "Zone@+ GetZone() const", asMETHODPR(Renderer2D, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "Zone@+ get_zone() const", asMETHODPR(Renderer2D, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "uint GetZoneMask() const", asMETHODPR(Renderer2D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "uint get_zoneMask() const", asMETHODPR(Renderer2D, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool HasBasePass(uint) const", asMETHODPR(Renderer2D, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "bool HasEventHandlers() const", asMETHODPR(Renderer2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Renderer2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Renderer2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsEnabled() const", asMETHODPR(Renderer2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_enabled() const", asMETHODPR(Renderer2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsEnabledEffective() const", asMETHODPR(Renderer2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_enabledEffective() const", asMETHODPR(Renderer2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(Renderer2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsInView() const", asMETHODPR(Renderer2D, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_inView() const", asMETHODPR(Renderer2D, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsInView(Camera@+) const", asMETHODPR(Renderer2D, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(Renderer2D, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsOccludee() const", asMETHODPR(Renderer2D, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_occludee() const", asMETHODPR(Renderer2D, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsOccluder() const", asMETHODPR(Renderer2D, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_occluder() const", asMETHODPR(Renderer2D, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsReplicated() const", asMETHODPR(Renderer2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_replicated() const", asMETHODPR(Renderer2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsTemporary() const", asMETHODPR(Renderer2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool get_temporary() const", asMETHODPR(Renderer2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "bool IsZoneDirty() const", asMETHODPR(Renderer2D, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void LimitLights()", asMETHODPR(Renderer2D, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void LimitVertexLights(bool)", asMETHODPR(Renderer2D, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool Load(Deserializer&)", asMETHODPR(Renderer2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Renderer2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(Renderer2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void MarkForUpdate()", asMETHODPR(Renderer2D, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void MarkInView(const FrameInfo&in)", asMETHODPR(Renderer2D, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void MarkInView(uint)", asMETHODPR(Renderer2D, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "void MarkNetworkUpdate()", asMETHODPR(Renderer2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Renderer2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Renderer2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Renderer2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void OnSetEnabled()", asMETHODPR(Renderer2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "void PrepareNetworkUpdate()", asMETHODPR(Renderer2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void Renderer2D::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Urho2D/Renderer2D.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Renderer2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Renderer2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Renderer2D", "int Refs() const", asMETHODPR(Renderer2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "int get_refs() const", asMETHODPR(Renderer2D, Refs, () const, int), asCALL_THISCALL);
    // static void Renderer2D::RegisterObject(Context* context) | File: ../Urho2D/Renderer2D.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Renderer2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(Renderer2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "void Remove()", asMETHODPR(Renderer2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Renderer2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Renderer2D::RemoveDrawable(Drawable2D* drawable) | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectMethod("Renderer2D", "void RemoveDrawable(Drawable2D@+)", asMETHODPR(Renderer2D, RemoveDrawable, (Drawable2D*), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void RemoveInstanceDefault()", asMETHODPR(Renderer2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void RemoveObjectAnimation()", asMETHODPR(Renderer2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // explicit Renderer2D::Renderer2D(Context* context) | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectBehaviour("Renderer2D", asBEHAVE_FACTORY, "Renderer2D@+ f()", asFUNCTION(Renderer2D_Renderer2D_Context), asCALL_CDECL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void ResetToDefault()", asMETHODPR(Renderer2D, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "bool Save(Serializer&) const", asMETHODPR(Renderer2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool SaveDefaultAttributes() const", asMETHODPR(Renderer2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(Renderer2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "bool SaveXML(XMLElement&) const", asMETHODPR(Renderer2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void SendEvent(StringHash)", asMETHODPR(Renderer2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Renderer2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetAnimationEnabled(bool)", asMETHODPR(Renderer2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_animationEnabled(bool)", asMETHODPR(Renderer2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetAnimationTime(float)", asMETHODPR(Renderer2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Renderer2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Renderer2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Renderer2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Renderer2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Renderer2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Renderer2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Renderer2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetBasePass(uint)", asMETHODPR(Renderer2D, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void SetBlockEvents(bool)", asMETHODPR(Renderer2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetCastShadows(bool)", asMETHODPR(Renderer2D, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_castShadows(bool)", asMETHODPR(Renderer2D, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetDrawDistance(float)", asMETHODPR(Renderer2D, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_drawDistance(float)", asMETHODPR(Renderer2D, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Renderer2D", "void SetEnabled(bool)", asMETHODPR(Renderer2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_enabled(bool)", asMETHODPR(Renderer2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Renderer2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Renderer2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetInstanceDefault(bool)", asMETHODPR(Renderer2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Renderer2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetLightMask(uint)", asMETHODPR(Renderer2D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_lightMask(uint)", asMETHODPR(Renderer2D, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetLodBias(float)", asMETHODPR(Renderer2D, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_lodBias(float)", asMETHODPR(Renderer2D, SetLodBias, (float), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetMaxLights(uint)", asMETHODPR(Renderer2D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_maxLights(uint)", asMETHODPR(Renderer2D, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetMinMaxZ(float, float)", asMETHODPR(Renderer2D, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Renderer2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Renderer2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Renderer2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetOccludee(bool)", asMETHODPR(Renderer2D, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_occludee(bool)", asMETHODPR(Renderer2D, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetOccluder(bool)", asMETHODPR(Renderer2D, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_occluder(bool)", asMETHODPR(Renderer2D, SetOccluder, (bool), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetShadowDistance(float)", asMETHODPR(Renderer2D, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_shadowDistance(float)", asMETHODPR(Renderer2D, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetShadowMask(uint)", asMETHODPR(Renderer2D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_shadowMask(uint)", asMETHODPR(Renderer2D, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetSortValue(float)", asMETHODPR(Renderer2D, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetTemporary(bool)", asMETHODPR(Renderer2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_temporary(bool)", asMETHODPR(Renderer2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetViewMask(uint)", asMETHODPR(Renderer2D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_viewMask(uint)", asMETHODPR(Renderer2D, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetZone(Zone@+, bool = false)", asMETHODPR(Renderer2D, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void SetZoneMask(uint)", asMETHODPR(Renderer2D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "void set_zoneMask(uint)", asMETHODPR(Renderer2D, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void UnsubscribeFromAllEvents()", asMETHODPR(Renderer2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Renderer2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Renderer2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Renderer2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Renderer2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Renderer2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Renderer2D", "void Update(const FrameInfo&in)", asMETHODPR(Renderer2D, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // void Renderer2D::UpdateBatches(const FrameInfo& frame) override | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectMethod("Renderer2D", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(Renderer2D, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // void Renderer2D::UpdateGeometry(const FrameInfo& frame) override | File: ../Urho2D/Renderer2D.h
    engine->RegisterObjectMethod("Renderer2D", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(Renderer2D, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Renderer2D", "int WeakRefs() const", asMETHODPR(Renderer2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Renderer2D", "int get_weakRefs() const", asMETHODPR(Renderer2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Renderer2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Renderer2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Renderer2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Renderer2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Resource", asBEHAVE_ADDREF, "void f()", asMETHODPR(Resource, AddRef, (), void), asCALL_THISCALL);
    // virtual bool Resource::BeginLoad(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "bool BeginLoad(Deserializer&)", asMETHODPR(Resource, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "bool EndLoad()", asMETHODPR(Resource, EndLoad, (), bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(Resource, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "bool GetBlockEvents() const", asMETHODPR(Resource, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "const String& GetCategory() const", asMETHODPR(Resource, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "const String& get_category() const", asMETHODPR(Resource, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "VariantMap& GetEventDataMap() const", asMETHODPR(Resource, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "Object@+ GetEventSender() const", asMETHODPR(Resource, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Resource, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Resource, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "const VariantMap& GetGlobalVars() const", asMETHODPR(Resource, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "const VariantMap& get_globalVars() const", asMETHODPR(Resource, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "uint GetMemoryUse() const", asMETHODPR(Resource, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "uint get_memoryUse() const", asMETHODPR(Resource, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "const String& GetName() const", asMETHODPR(Resource, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "const String& get_name() const", asMETHODPR(Resource, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "StringHash GetNameHash() const", asMETHODPR(Resource, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Resource, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "StringHash GetType() const", asMETHODPR(Resource, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "StringHash get_type() const", asMETHODPR(Resource, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "const String& GetTypeName() const", asMETHODPR(Resource, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "const String& get_typeName() const", asMETHODPR(Resource, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "uint GetUseTimer()", asMETHODPR(Resource, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "uint get_useTimer()", asMETHODPR(Resource, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "bool HasEventHandlers() const", asMETHODPR(Resource, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Resource, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Resource, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "bool IsInstanceOf(StringHash) const", asMETHODPR(Resource, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "bool Load(Deserializer&)", asMETHODPR(Resource, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "bool LoadFile(const String&in)", asMETHODPR(Resource, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "bool Load(const String&in)", asMETHODPR(Resource, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Resource, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Resource", "int Refs() const", asMETHODPR(Resource, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "int get_refs() const", asMETHODPR(Resource, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Resource", asBEHAVE_RELEASE, "void f()", asMETHODPR(Resource, ReleaseRef, (), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "void ResetUseTimer()", asMETHODPR(Resource, ResetUseTimer, (), void), asCALL_THISCALL);
    // explicit Resource::Resource(Context* context) | File: ../Resource/Resource.h
    engine->RegisterObjectBehaviour("Resource", asBEHAVE_FACTORY, "Resource@+ f()", asFUNCTION(Resource_Resource_Context), asCALL_CDECL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "bool Save(Serializer&) const", asMETHODPR(Resource, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "bool SaveFile(const String&in) const", asMETHODPR(Resource, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "bool Save(const String&in) const", asMETHODPR(Resource, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void SendEvent(StringHash)", asMETHODPR(Resource, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Resource, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(Resource, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void SetBlockEvents(bool)", asMETHODPR(Resource, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Resource, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Resource, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "void SetMemoryUse(uint)", asMETHODPR(Resource, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("Resource", "void SetName(const String&in)", asMETHODPR(Resource, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "void set_name(const String&in)", asMETHODPR(Resource, SetName, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void UnsubscribeFromAllEvents()", asMETHODPR(Resource, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Resource_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Resource, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Resource, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Resource", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Resource, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Resource", "int WeakRefs() const", asMETHODPR(Resource, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Resource", "int get_weakRefs() const", asMETHODPR(Resource, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ResourceCache", "bool AddManualResource(Resource@+)", asMETHODPR(ResourceCache, AddManualResource, (Resource*), bool), asCALL_THISCALL);
    // bool ResourceCache::AddPackageFile(PackageFile* package, unsigned priority=PRIORITY_LAST) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool AddPackageFile(PackageFile@+, uint = PRIORITY_LAST)", asMETHODPR(ResourceCache, AddPackageFile, (PackageFile*, unsigned), bool), asCALL_THISCALL);
    // bool ResourceCache::AddPackageFile(const String& fileName, unsigned priority=PRIORITY_LAST) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool AddPackageFile(const String&in, uint = PRIORITY_LAST)", asMETHODPR(ResourceCache, AddPackageFile, (const String&, unsigned), bool), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ResourceCache", asBEHAVE_ADDREF, "void f()", asMETHODPR(ResourceCache, AddRef, (), void), asCALL_THISCALL);
    // bool ResourceCache::AddResourceDir(const String& pathName, unsigned priority=PRIORITY_LAST) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool AddResourceDir(const String&in, uint = PRIORITY_LAST)", asMETHODPR(ResourceCache, AddResourceDir, (const String&, unsigned), bool), asCALL_THISCALL);
    // void ResourceCache::AddResourceRouter(ResourceRouter* router, bool addAsFirst=false) | File: ../Resource/ResourceCache.h
    // Error: type "ResourceRouter" can not automatically bind bacause have @nobind mark
    // bool ResourceCache::BackgroundLoadResource(StringHash type, const String& name, bool sendEventOnFailure=true, Resource* caller=nullptr) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool BackgroundLoadResource(StringHash, const String&in, bool = true, Resource@+ = null)", asMETHODPR(ResourceCache, BackgroundLoadResource, (StringHash, const String&, bool, Resource*), bool), asCALL_THISCALL);
    // template<class T> bool ResourceCache::BackgroundLoadResource(const String& name, bool sendEventOnFailure=true, Resource* caller=nullptr) | File: ../Resource/ResourceCache.h
    // Not registered because template
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // bool ResourceCache::Exists(const String& name) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool Exists(const String&in) const", asMETHODPR(ResourceCache, Exists, (const String&) const, bool), asCALL_THISCALL);
    // const HashMap<StringHash, ResourceGroup>& ResourceCache::GetAllResources() const | File: ../Resource/ResourceCache.h
    // Error: type "const HashMap<StringHash, ResourceGroup>&" can not automatically bind
    // bool ResourceCache::GetAutoReloadResources() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool GetAutoReloadResources() const", asMETHODPR(ResourceCache, GetAutoReloadResources, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool get_autoReloadResources() const", asMETHODPR(ResourceCache, GetAutoReloadResources, () const, bool), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "bool GetBlockEvents() const", asMETHODPR(ResourceCache, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "const String& GetCategory() const", asMETHODPR(ResourceCache, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "const String& get_category() const", asMETHODPR(ResourceCache, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "VariantMap& GetEventDataMap() const", asMETHODPR(ResourceCache, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "Object@+ GetEventSender() const", asMETHODPR(ResourceCache, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Resource* ResourceCache::GetExistingResource(StringHash type, const String& name) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetExistingResource(StringHash, const String&in)", asMETHODPR(ResourceCache, GetExistingResource, (StringHash, const String&), Resource*), asCALL_THISCALL);
    // template<class T> T* ResourceCache::GetExistingResource(const String& name) | File: ../Resource/ResourceCache.h
    // Not registered because template
    // SharedPtr<File> ResourceCache::GetFile(const String& name, bool sendEventOnFailure=true) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "File@+ GetFile(const String&in, bool = true)", asFUNCTION(ResourceCache_GetFile_String_bool), asCALL_CDECL_OBJFIRST);
    // int ResourceCache::GetFinishBackgroundResourcesMs() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "int GetFinishBackgroundResourcesMs() const", asMETHODPR(ResourceCache, GetFinishBackgroundResourcesMs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "int get_finishBackgroundResourcesMs() const", asMETHODPR(ResourceCache, GetFinishBackgroundResourcesMs, () const, int), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ResourceCache, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ResourceCache, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "const VariantMap& GetGlobalVars() const", asMETHODPR(ResourceCache, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "const VariantMap& get_globalVars() const", asMETHODPR(ResourceCache, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned long long ResourceCache::GetMemoryBudget(StringHash type) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "uint64 GetMemoryBudget(StringHash) const", asMETHODPR(ResourceCache, GetMemoryBudget, (StringHash) const, unsigned long long), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "uint64 get_memoryBudget(StringHash) const", asMETHODPR(ResourceCache, GetMemoryBudget, (StringHash) const, unsigned long long), asCALL_THISCALL);
    // unsigned long long ResourceCache::GetMemoryUse(StringHash type) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "uint64 GetMemoryUse(StringHash) const", asMETHODPR(ResourceCache, GetMemoryUse, (StringHash) const, unsigned long long), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "uint64 get_memoryUse(StringHash) const", asMETHODPR(ResourceCache, GetMemoryUse, (StringHash) const, unsigned long long), asCALL_THISCALL);
    // unsigned ResourceCache::GetNumBackgroundLoadResources() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "uint GetNumBackgroundLoadResources() const", asMETHODPR(ResourceCache, GetNumBackgroundLoadResources, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "uint get_numBackgroundLoadResources() const", asMETHODPR(ResourceCache, GetNumBackgroundLoadResources, () const, unsigned), asCALL_THISCALL);
    // const Vector<SharedPtr<PackageFile>>& ResourceCache::GetPackageFiles() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "Array<PackageFile@>@ GetPackageFiles() const", asFUNCTION(ResourceCache_GetPackageFiles_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ResourceCache", "Array<PackageFile@>@ get_packageFiles() const", asFUNCTION(ResourceCache_GetPackageFiles_void), asCALL_CDECL_OBJFIRST);
    // String ResourceCache::GetPreferredResourceDir(const String& path) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "String GetPreferredResourceDir(const String&in) const", asMETHODPR(ResourceCache, GetPreferredResourceDir, (const String&) const, String), asCALL_THISCALL);
    // Resource* ResourceCache::GetResource(StringHash type, const String& name, bool sendEventOnFailure=true) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetResource(StringHash, const String&in, bool = true)", asMETHODPR(ResourceCache, GetResource, (StringHash, const String&, bool), Resource*), asCALL_THISCALL);
    // template<class T> T* ResourceCache::GetResource(const String& name, bool sendEventOnFailure=true) | File: ../Resource/ResourceCache.h
    // Not registered because template
    // const Vector<String>& ResourceCache::GetResourceDirs() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "Array<String>@ GetResourceDirs() const", asFUNCTION(ResourceCache_GetResourceDirs_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ResourceCache", "Array<String>@ get_resourceDirs() const", asFUNCTION(ResourceCache_GetResourceDirs_void), asCALL_CDECL_OBJFIRST);
    // String ResourceCache::GetResourceFileName(const String& name) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "String GetResourceFileName(const String&in) const", asMETHODPR(ResourceCache, GetResourceFileName, (const String&) const, String), asCALL_THISCALL);
    // ResourceRouter* ResourceCache::GetResourceRouter(unsigned index) const | File: ../Resource/ResourceCache.h
    // Error: type "ResourceRouter" can not automatically bind bacause have @nobind mark
    // void ResourceCache::GetResources(PODVector<Resource*>& result, StringHash type) const | File: ../Resource/ResourceCache.h
    // Error: type "PODVector<Resource*>&" can not automatically bind
    // template<class T> void ResourceCache::GetResources(PODVector<T*>& result) const | File: ../Resource/ResourceCache.h
    // Not registered because template
    // bool ResourceCache::GetReturnFailedResources() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool GetReturnFailedResources() const", asMETHODPR(ResourceCache, GetReturnFailedResources, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool get_returnFailedResources() const", asMETHODPR(ResourceCache, GetReturnFailedResources, () const, bool), asCALL_THISCALL);
    // bool ResourceCache::GetSearchPackagesFirst() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool GetSearchPackagesFirst() const", asMETHODPR(ResourceCache, GetSearchPackagesFirst, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "bool get_searchPackagesFirst() const", asMETHODPR(ResourceCache, GetSearchPackagesFirst, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ResourceCache, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // SharedPtr<Resource> ResourceCache::GetTempResource(StringHash type, const String& name, bool sendEventOnFailure=true) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "Resource@+ GetTempResource(StringHash, const String&in, bool = true)", asFUNCTION(ResourceCache_GetTempResource_StringHash_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> SharedPtr<T> ResourceCache::GetTempResource(const String& name, bool sendEventOnFailure=true) | File: ../Resource/ResourceCache.h
    // Not registered because template
    // unsigned long long ResourceCache::GetTotalMemoryUse() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "uint64 GetTotalMemoryUse() const", asMETHODPR(ResourceCache, GetTotalMemoryUse, () const, unsigned long long), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "uint64 get_totalMemoryUse() const", asMETHODPR(ResourceCache, GetTotalMemoryUse, () const, unsigned long long), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "StringHash GetType() const", asMETHODPR(ResourceCache, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "StringHash get_type() const", asMETHODPR(ResourceCache, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "const String& GetTypeName() const", asMETHODPR(ResourceCache, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "const String& get_typeName() const", asMETHODPR(ResourceCache, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "bool HasEventHandlers() const", asMETHODPR(ResourceCache, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ResourceCache, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ResourceCache, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "bool IsInstanceOf(StringHash) const", asMETHODPR(ResourceCache, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ResourceCache, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // String ResourceCache::PrintMemoryUsage() const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "String PrintMemoryUsage() const", asMETHODPR(ResourceCache, PrintMemoryUsage, () const, String), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ResourceCache", "int Refs() const", asMETHODPR(ResourceCache, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "int get_refs() const", asMETHODPR(ResourceCache, Refs, () const, int), asCALL_THISCALL);
    // void ResourceCache::ReleaseAllResources(bool force=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseAllResources(bool = false)", asMETHODPR(ResourceCache, ReleaseAllResources, (bool), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ResourceCache", asBEHAVE_RELEASE, "void f()", asMETHODPR(ResourceCache, ReleaseRef, (), void), asCALL_THISCALL);
    // void ResourceCache::ReleaseResource(StringHash type, const String& name, bool force=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResource(StringHash, const String&in, bool = false)", asMETHODPR(ResourceCache, ReleaseResource, (StringHash, const String&, bool), void), asCALL_THISCALL);
    // template<class T> void ResourceCache::ReleaseResource(const String& name, bool force=false) | File: ../Resource/ResourceCache.h
    // Not registered because template
    // void ResourceCache::ReleaseResources(StringHash type, bool force=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(StringHash, bool = false)", asMETHODPR(ResourceCache, ReleaseResources, (StringHash, bool), void), asCALL_THISCALL);
    // void ResourceCache::ReleaseResources(StringHash type, const String& partialName, bool force=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(StringHash, const String&in, bool = false)", asMETHODPR(ResourceCache, ReleaseResources, (StringHash, const String&, bool), void), asCALL_THISCALL);
    // void ResourceCache::ReleaseResources(const String& partialName, bool force=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ReleaseResources(const String&in, bool = false)", asMETHODPR(ResourceCache, ReleaseResources, (const String&, bool), void), asCALL_THISCALL);
    // bool ResourceCache::ReloadResource(Resource* resource) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "bool ReloadResource(Resource@+)", asMETHODPR(ResourceCache, ReloadResource, (Resource*), bool), asCALL_THISCALL);
    // void ResourceCache::ReloadResourceWithDependencies(const String& fileName) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ReloadResourceWithDependencies(const String&in)", asMETHODPR(ResourceCache, ReloadResourceWithDependencies, (const String&), void), asCALL_THISCALL);
    // void ResourceCache::RemovePackageFile(PackageFile* package, bool releaseResources=true, bool forceRelease=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void RemovePackageFile(PackageFile@+, bool = true, bool = false)", asMETHODPR(ResourceCache, RemovePackageFile, (PackageFile*, bool, bool), void), asCALL_THISCALL);
    // void ResourceCache::RemovePackageFile(const String& fileName, bool releaseResources=true, bool forceRelease=false) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void RemovePackageFile(const String&in, bool = true, bool = false)", asMETHODPR(ResourceCache, RemovePackageFile, (const String&, bool, bool), void), asCALL_THISCALL);
    // void ResourceCache::RemoveResourceDir(const String& pathName) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void RemoveResourceDir(const String&in)", asMETHODPR(ResourceCache, RemoveResourceDir, (const String&), void), asCALL_THISCALL);
    // void ResourceCache::RemoveResourceRouter(ResourceRouter* router) | File: ../Resource/ResourceCache.h
    // Error: type "ResourceRouter" can not automatically bind bacause have @nobind mark
    // void ResourceCache::ResetDependencies(Resource* resource) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void ResetDependencies(Resource@+)", asMETHODPR(ResourceCache, ResetDependencies, (Resource*), void), asCALL_THISCALL);
    // explicit ResourceCache::ResourceCache(Context* context) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectBehaviour("ResourceCache", asBEHAVE_FACTORY, "ResourceCache@+ f()", asFUNCTION(ResourceCache_ResourceCache_Context), asCALL_CDECL);
    // String ResourceCache::SanitateResourceDirName(const String& name) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "String SanitateResourceDirName(const String&in) const", asMETHODPR(ResourceCache, SanitateResourceDirName, (const String&) const, String), asCALL_THISCALL);
    // String ResourceCache::SanitateResourceName(const String& name) const | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "String SanitateResourceName(const String&in) const", asMETHODPR(ResourceCache, SanitateResourceName, (const String&) const, String), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void SendEvent(StringHash)", asMETHODPR(ResourceCache, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ResourceCache, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void ResourceCache::SetAutoReloadResources(bool enable) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void SetAutoReloadResources(bool)", asMETHODPR(ResourceCache, SetAutoReloadResources, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_autoReloadResources(bool)", asMETHODPR(ResourceCache, SetAutoReloadResources, (bool), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void SetBlockEvents(bool)", asMETHODPR(ResourceCache, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void ResourceCache::SetFinishBackgroundResourcesMs(int ms) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void SetFinishBackgroundResourcesMs(int)", asMETHODPR(ResourceCache, SetFinishBackgroundResourcesMs, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_finishBackgroundResourcesMs(int)", asMETHODPR(ResourceCache, SetFinishBackgroundResourcesMs, (int), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ResourceCache, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ResourceCache, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void ResourceCache::SetMemoryBudget(StringHash type, unsigned long long budget) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void SetMemoryBudget(StringHash, uint64)", asMETHODPR(ResourceCache, SetMemoryBudget, (StringHash, unsigned long long), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_memoryBudget(StringHash, uint64)", asMETHODPR(ResourceCache, SetMemoryBudget, (StringHash, unsigned long long), void), asCALL_THISCALL);
    // void ResourceCache::SetReturnFailedResources(bool enable) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void SetReturnFailedResources(bool)", asMETHODPR(ResourceCache, SetReturnFailedResources, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_returnFailedResources(bool)", asMETHODPR(ResourceCache, SetReturnFailedResources, (bool), void), asCALL_THISCALL);
    // void ResourceCache::SetSearchPackagesFirst(bool value) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void SetSearchPackagesFirst(bool)", asMETHODPR(ResourceCache, SetSearchPackagesFirst, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "void set_searchPackagesFirst(bool)", asMETHODPR(ResourceCache, SetSearchPackagesFirst, (bool), void), asCALL_THISCALL);
    // void ResourceCache::StoreResourceDependency(Resource* resource, const String& dependency) | File: ../Resource/ResourceCache.h
    engine->RegisterObjectMethod("ResourceCache", "void StoreResourceDependency(Resource@+, const String&in)", asMETHODPR(ResourceCache, StoreResourceDependency, (Resource*, const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void UnsubscribeFromAllEvents()", asMETHODPR(ResourceCache, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ResourceCache_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ResourceCache, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ResourceCache, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceCache", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ResourceCache, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ResourceCache", "int WeakRefs() const", asMETHODPR(ResourceCache, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceCache", "int get_weakRefs() const", asMETHODPR(ResourceCache, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ResourceWithMetadata", "void AddMetadata(const String&in, const Variant&in)", asMETHODPR(ResourceWithMetadata, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "void set_metadata(const String&in, const Variant&in)", asMETHODPR(ResourceWithMetadata, AddMetadata, (const String&, const Variant&), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ResourceWithMetadata", asBEHAVE_ADDREF, "void f()", asMETHODPR(ResourceWithMetadata, AddRef, (), void), asCALL_THISCALL);
    // virtual bool Resource::BeginLoad(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool BeginLoad(Deserializer&)", asMETHODPR(ResourceWithMetadata, BeginLoad, (Deserializer&), bool), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // virtual bool Resource::EndLoad() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool EndLoad()", asMETHODPR(ResourceWithMetadata, EndLoad, (), bool), asCALL_THISCALL);
    // AsyncLoadState Resource::GetAsyncLoadState() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "AsyncLoadState GetAsyncLoadState() const", asMETHODPR(ResourceWithMetadata, GetAsyncLoadState, () const, AsyncLoadState), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool GetBlockEvents() const", asMETHODPR(ResourceWithMetadata, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "const String& GetCategory() const", asMETHODPR(ResourceWithMetadata, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "const String& get_category() const", asMETHODPR(ResourceWithMetadata, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "VariantMap& GetEventDataMap() const", asMETHODPR(ResourceWithMetadata, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "Object@+ GetEventSender() const", asMETHODPR(ResourceWithMetadata, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ResourceWithMetadata, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ResourceWithMetadata, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "const VariantMap& GetGlobalVars() const", asMETHODPR(ResourceWithMetadata, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "const VariantMap& get_globalVars() const", asMETHODPR(ResourceWithMetadata, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Resource::GetMemoryUse() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "uint GetMemoryUse() const", asMETHODPR(ResourceWithMetadata, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "uint get_memoryUse() const", asMETHODPR(ResourceWithMetadata, GetMemoryUse, () const, unsigned), asCALL_THISCALL);
    // const Variant& ResourceWithMetadata::GetMetadata(const String& name) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "const Variant& GetMetadata(const String&in) const", asMETHODPR(ResourceWithMetadata, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "const Variant& get_metadata(const String&in) const", asMETHODPR(ResourceWithMetadata, GetMetadata, (const String&) const, const Variant&), asCALL_THISCALL);
    // const String& Resource::GetName() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "const String& GetName() const", asMETHODPR(ResourceWithMetadata, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "const String& get_name() const", asMETHODPR(ResourceWithMetadata, GetName, () const, const String&), asCALL_THISCALL);
    // StringHash Resource::GetNameHash() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "StringHash GetNameHash() const", asMETHODPR(ResourceWithMetadata, GetNameHash, () const, StringHash), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ResourceWithMetadata, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "StringHash GetType() const", asMETHODPR(ResourceWithMetadata, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "StringHash get_type() const", asMETHODPR(ResourceWithMetadata, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "const String& GetTypeName() const", asMETHODPR(ResourceWithMetadata, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "const String& get_typeName() const", asMETHODPR(ResourceWithMetadata, GetTypeName, () const, const String&), asCALL_THISCALL);
    // unsigned Resource::GetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "uint GetUseTimer()", asMETHODPR(ResourceWithMetadata, GetUseTimer, (), unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "uint get_useTimer()", asMETHODPR(ResourceWithMetadata, GetUseTimer, (), unsigned), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool HasEventHandlers() const", asMETHODPR(ResourceWithMetadata, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool ResourceWithMetadata::HasMetadata() const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool HasMetadata() const", asMETHODPR(ResourceWithMetadata, HasMetadata, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool get_hasMetadata() const", asMETHODPR(ResourceWithMetadata, HasMetadata, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ResourceWithMetadata, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ResourceWithMetadata, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool IsInstanceOf(StringHash) const", asMETHODPR(ResourceWithMetadata, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Resource::Load(Deserializer& source) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool Load(Deserializer&)", asMETHODPR(ResourceWithMetadata, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Resource::LoadFile(const String& fileName) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool LoadFile(const String&in)", asMETHODPR(ResourceWithMetadata, LoadFile, (const String&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool Load(const String&in)", asMETHODPR(ResourceWithMetadata, LoadFile, (const String&), bool), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ResourceWithMetadata, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "int Refs() const", asMETHODPR(ResourceWithMetadata, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "int get_refs() const", asMETHODPR(ResourceWithMetadata, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ResourceWithMetadata", asBEHAVE_RELEASE, "void f()", asMETHODPR(ResourceWithMetadata, ReleaseRef, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveAllMetadata() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void RemoveAllMetadata()", asMETHODPR(ResourceWithMetadata, RemoveAllMetadata, (), void), asCALL_THISCALL);
    // void ResourceWithMetadata::RemoveMetadata(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void RemoveMetadata(const String&in)", asMETHODPR(ResourceWithMetadata, RemoveMetadata, (const String&), void), asCALL_THISCALL);
    // void Resource::ResetUseTimer() | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void ResetUseTimer()", asMETHODPR(ResourceWithMetadata, ResetUseTimer, (), void), asCALL_THISCALL);
    // explicit ResourceWithMetadata::ResourceWithMetadata(Context* context) | File: ../Resource/Resource.h
    engine->RegisterObjectBehaviour("ResourceWithMetadata", asBEHAVE_FACTORY, "ResourceWithMetadata@+ f()", asFUNCTION(ResourceWithMetadata_ResourceWithMetadata_Context), asCALL_CDECL);
    // virtual bool Resource::Save(Serializer& dest) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool Save(Serializer&) const", asMETHODPR(ResourceWithMetadata, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Resource::SaveFile(const String& fileName) const | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool SaveFile(const String&in) const", asMETHODPR(ResourceWithMetadata, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "bool Save(const String&in) const", asMETHODPR(ResourceWithMetadata, SaveFile, (const String&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SendEvent(StringHash)", asMETHODPR(ResourceWithMetadata, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ResourceWithMetadata, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Resource::SetAsyncLoadState(AsyncLoadState newState) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SetAsyncLoadState(AsyncLoadState)", asMETHODPR(ResourceWithMetadata, SetAsyncLoadState, (AsyncLoadState), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SetBlockEvents(bool)", asMETHODPR(ResourceWithMetadata, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ResourceWithMetadata, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ResourceWithMetadata, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Resource::SetMemoryUse(unsigned size) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SetMemoryUse(uint)", asMETHODPR(ResourceWithMetadata, SetMemoryUse, (unsigned), void), asCALL_THISCALL);
    // void Resource::SetName(const String& name) | File: ../Resource/Resource.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void SetName(const String&in)", asMETHODPR(ResourceWithMetadata, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "void set_name(const String&in)", asMETHODPR(ResourceWithMetadata, SetName, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void UnsubscribeFromAllEvents()", asMETHODPR(ResourceWithMetadata, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ResourceWithMetadata_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ResourceWithMetadata, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ResourceWithMetadata, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ResourceWithMetadata, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ResourceWithMetadata", "int WeakRefs() const", asMETHODPR(ResourceWithMetadata, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ResourceWithMetadata", "int get_weakRefs() const", asMETHODPR(ResourceWithMetadata, WeakRefs, () const, int), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("RibbonTrail", "void AddLight(Light@+)", asMETHODPR(RibbonTrail, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RibbonTrail", asBEHAVE_ADDREF, "void f()", asMETHODPR(RibbonTrail, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void AddVertexLight(Light@+)", asMETHODPR(RibbonTrail, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void AllocateNetworkState()", asMETHODPR(RibbonTrail, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void ApplyAttributes()", asMETHODPR(RibbonTrail, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void RibbonTrail::Commit() | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void Commit()", asMETHODPR(RibbonTrail, Commit, (), void), asCALL_THISCALL);
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(RibbonTrail, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(RibbonTrail, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool GetAnimationEnabled() const", asMETHODPR(RibbonTrail, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_animationEnabled() const", asMETHODPR(RibbonTrail, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // float RibbonTrail::GetAnimationLodBias() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetAnimationLodBias() const", asMETHODPR(RibbonTrail, GetAnimationLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_animationLodBias() const", asMETHODPR(RibbonTrail, GetAnimationLodBias, () const, float), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "Variant GetAttribute(uint) const", asMETHODPR(RibbonTrail, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "Variant get_attributes(uint) const", asMETHODPR(RibbonTrail, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "Variant GetAttribute(const String&in) const", asMETHODPR(RibbonTrail, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(RibbonTrail, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(RibbonTrail, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(RibbonTrail, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(RibbonTrail, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "Variant GetAttributeDefault(uint) const", asMETHODPR(RibbonTrail, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "Variant get_attributeDefaults(uint) const", asMETHODPR(RibbonTrail, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(RibbonTrail, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector3& RibbonTrail::GetBaseVelocity() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "const Vector3& GetBaseVelocity() const", asMETHODPR(RibbonTrail, GetBaseVelocity, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const Vector3& get_baseVelocity() const", asMETHODPR(RibbonTrail, GetBaseVelocity, () const, const Vector3&), asCALL_THISCALL);
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "bool GetBlockEvents() const", asMETHODPR(RibbonTrail, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "const BoundingBox& GetBoundingBox() const", asMETHODPR(RibbonTrail, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const BoundingBox& get_boundingBox() const", asMETHODPR(RibbonTrail, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool GetCastShadows() const", asMETHODPR(RibbonTrail, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_castShadows() const", asMETHODPR(RibbonTrail, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "const String& GetCategory() const", asMETHODPR(RibbonTrail, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const String& get_category() const", asMETHODPR(RibbonTrail, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "Component@+ GetComponent(StringHash) const", asMETHODPR(RibbonTrail, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("RibbonTrail", "float GetDistance() const", asMETHODPR(RibbonTrail, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint8 GetDrawableFlags() const", asMETHODPR(RibbonTrail, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetDrawDistance() const", asMETHODPR(RibbonTrail, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_drawDistance() const", asMETHODPR(RibbonTrail, GetDrawDistance, () const, float), asCALL_THISCALL);
    // const Color& RibbonTrail::GetEndColor() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "const Color& GetEndColor() const", asMETHODPR(RibbonTrail, GetEndColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const Color& get_endColor() const", asMETHODPR(RibbonTrail, GetEndColor, () const, const Color&), asCALL_THISCALL);
    // float RibbonTrail::GetEndScale() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetEndScale() const", asMETHODPR(RibbonTrail, GetEndScale, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_endScale() const", asMETHODPR(RibbonTrail, GetEndScale, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "VariantMap& GetEventDataMap() const", asMETHODPR(RibbonTrail, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "Object@+ GetEventSender() const", asMETHODPR(RibbonTrail, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "Light@+ GetFirstLight() const", asMETHODPR(RibbonTrail, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(RibbonTrail, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const Variant& get_globalVar(StringHash) const", asMETHODPR(RibbonTrail, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "const VariantMap& GetGlobalVars() const", asMETHODPR(RibbonTrail, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const VariantMap& get_globalVars() const", asMETHODPR(RibbonTrail, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetID() const", asMETHODPR(RibbonTrail, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_id() const", asMETHODPR(RibbonTrail, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(RibbonTrail, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // float RibbonTrail::GetLifetime() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetLifetime() const", asMETHODPR(RibbonTrail, GetLifetime, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_lifetime() const", asMETHODPR(RibbonTrail, GetLifetime, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetLightMask() const", asMETHODPR(RibbonTrail, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_lightMask() const", asMETHODPR(RibbonTrail, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "Array<Light@>@ GetLights() const", asFUNCTION(RibbonTrail_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetLodBias() const", asMETHODPR(RibbonTrail, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_lodBias() const", asMETHODPR(RibbonTrail, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetLodDistance() const", asMETHODPR(RibbonTrail, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(RibbonTrail, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // Material* RibbonTrail::GetMaterial() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "Material@+ GetMaterial() const", asMETHODPR(RibbonTrail, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "Material@+ get_material() const", asMETHODPR(RibbonTrail, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef RibbonTrail::GetMaterialAttr() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "ResourceRef GetMaterialAttr() const", asMETHODPR(RibbonTrail, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetMaxLights() const", asMETHODPR(RibbonTrail, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_maxLights() const", asMETHODPR(RibbonTrail, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetMaxZ() const", asMETHODPR(RibbonTrail, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetMinZ() const", asMETHODPR(RibbonTrail, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "Node@+ GetNode() const", asMETHODPR(RibbonTrail, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "Node@+ get_node() const", asMETHODPR(RibbonTrail, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetNumAttributes() const", asMETHODPR(RibbonTrail, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_numAttributes() const", asMETHODPR(RibbonTrail, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetNumNetworkAttributes() const", asMETHODPR(RibbonTrail, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetNumOccluderTriangles()", asMETHODPR(RibbonTrail, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(RibbonTrail, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(RibbonTrail, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(RibbonTrail, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "Scene@+ GetScene() const", asMETHODPR(RibbonTrail, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetShadowDistance() const", asMETHODPR(RibbonTrail, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_shadowDistance() const", asMETHODPR(RibbonTrail, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetShadowMask() const", asMETHODPR(RibbonTrail, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_shadowMask() const", asMETHODPR(RibbonTrail, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetSortValue() const", asMETHODPR(RibbonTrail, GetSortValue, () const, float), asCALL_THISCALL);
    // const Color& RibbonTrail::GetStartColor() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "const Color& GetStartColor() const", asMETHODPR(RibbonTrail, GetStartColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const Color& get_startColor() const", asMETHODPR(RibbonTrail, GetStartColor, () const, const Color&), asCALL_THISCALL);
    // float RibbonTrail::GetStartScale() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetStartScale() const", asMETHODPR(RibbonTrail, GetStartScale, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_startScale() const", asMETHODPR(RibbonTrail, GetStartScale, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(RibbonTrail, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // unsigned RibbonTrail::GetTailColumn() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetTailColumn() const", asMETHODPR(RibbonTrail, GetTailColumn, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_tailColumn() const", asMETHODPR(RibbonTrail, GetTailColumn, () const, unsigned), asCALL_THISCALL);
    // TrailType RibbonTrail::GetTrailType() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "TrailType GetTrailType() const", asMETHODPR(RibbonTrail, GetTrailType, () const, TrailType), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "TrailType get_trailType() const", asMETHODPR(RibbonTrail, GetTrailType, () const, TrailType), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "StringHash GetType() const", asMETHODPR(RibbonTrail, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "StringHash get_type() const", asMETHODPR(RibbonTrail, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "const String& GetTypeName() const", asMETHODPR(RibbonTrail, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const String& get_typeName() const", asMETHODPR(RibbonTrail, GetTypeName, () const, const String&), asCALL_THISCALL);
    // UpdateGeometryType RibbonTrail::GetUpdateGeometryType() override | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(RibbonTrail, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // bool RibbonTrail::GetUpdateInvisible() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "bool GetUpdateInvisible() const", asMETHODPR(RibbonTrail, GetUpdateInvisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_updateInvisible() const", asMETHODPR(RibbonTrail, GetUpdateInvisible, () const, bool), asCALL_THISCALL);
    // float RibbonTrail::GetVertexDistance() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetVertexDistance() const", asMETHODPR(RibbonTrail, GetVertexDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_vertexDistance() const", asMETHODPR(RibbonTrail, GetVertexDistance, () const, float), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "Array<Light@>@ GetVertexLights() const", asFUNCTION(RibbonTrail_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetViewMask() const", asMETHODPR(RibbonTrail, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_viewMask() const", asMETHODPR(RibbonTrail, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // float RibbonTrail::GetWidth() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "float GetWidth() const", asMETHODPR(RibbonTrail, GetWidth, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "float get_width() const", asMETHODPR(RibbonTrail, GetWidth, () const, float), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(RibbonTrail, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(RibbonTrail, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "Zone@+ GetZone() const", asMETHODPR(RibbonTrail, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "Zone@+ get_zone() const", asMETHODPR(RibbonTrail, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "uint GetZoneMask() const", asMETHODPR(RibbonTrail, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "uint get_zoneMask() const", asMETHODPR(RibbonTrail, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool HasBasePass(uint) const", asMETHODPR(RibbonTrail, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "bool HasEventHandlers() const", asMETHODPR(RibbonTrail, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(RibbonTrail, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(RibbonTrail, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool RibbonTrail::IsEmitting() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsEmitting() const", asMETHODPR(RibbonTrail, IsEmitting, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_emitting() const", asMETHODPR(RibbonTrail, IsEmitting, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsEnabled() const", asMETHODPR(RibbonTrail, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_enabled() const", asMETHODPR(RibbonTrail, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsEnabledEffective() const", asMETHODPR(RibbonTrail, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_enabledEffective() const", asMETHODPR(RibbonTrail, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsInstanceOf(StringHash) const", asMETHODPR(RibbonTrail, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsInView() const", asMETHODPR(RibbonTrail, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_inView() const", asMETHODPR(RibbonTrail, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsInView(Camera@+) const", asMETHODPR(RibbonTrail, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(RibbonTrail, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsOccludee() const", asMETHODPR(RibbonTrail, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_occludee() const", asMETHODPR(RibbonTrail, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsOccluder() const", asMETHODPR(RibbonTrail, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_occluder() const", asMETHODPR(RibbonTrail, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsReplicated() const", asMETHODPR(RibbonTrail, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_replicated() const", asMETHODPR(RibbonTrail, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool RibbonTrail::IsSorted() const | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsSorted() const", asMETHODPR(RibbonTrail, IsSorted, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_sorted() const", asMETHODPR(RibbonTrail, IsSorted, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsTemporary() const", asMETHODPR(RibbonTrail, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool get_temporary() const", asMETHODPR(RibbonTrail, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool IsZoneDirty() const", asMETHODPR(RibbonTrail, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void LimitLights()", asMETHODPR(RibbonTrail, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void LimitVertexLights(bool)", asMETHODPR(RibbonTrail, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool Load(Deserializer&)", asMETHODPR(RibbonTrail, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool LoadJSON(const JSONValue&in)", asMETHODPR(RibbonTrail, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool LoadXML(const XMLElement&in)", asMETHODPR(RibbonTrail, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void MarkForUpdate()", asMETHODPR(RibbonTrail, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void MarkInView(const FrameInfo&in)", asMETHODPR(RibbonTrail, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void MarkInView(uint)", asMETHODPR(RibbonTrail, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "void MarkNetworkUpdate()", asMETHODPR(RibbonTrail, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(RibbonTrail, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(RibbonTrail, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(RibbonTrail, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void RibbonTrail::OnSetEnabled() override | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void OnSetEnabled()", asMETHODPR(RibbonTrail, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "void PrepareNetworkUpdate()", asMETHODPR(RibbonTrail, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void RibbonTrail::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/RibbonTrail.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(RibbonTrail, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(RibbonTrail, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RibbonTrail", "int Refs() const", asMETHODPR(RibbonTrail, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "int get_refs() const", asMETHODPR(RibbonTrail, Refs, () const, int), asCALL_THISCALL);
    // static void RibbonTrail::RegisterObject(Context* context) | File: ../Graphics/RibbonTrail.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RibbonTrail", asBEHAVE_RELEASE, "void f()", asMETHODPR(RibbonTrail, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "void Remove()", asMETHODPR(RibbonTrail, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(RibbonTrail, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void RemoveInstanceDefault()", asMETHODPR(RibbonTrail, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void RemoveObjectAnimation()", asMETHODPR(RibbonTrail, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void ResetToDefault()", asMETHODPR(RibbonTrail, ResetToDefault, (), void), asCALL_THISCALL);
    // explicit RibbonTrail::RibbonTrail(Context* context) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectBehaviour("RibbonTrail", asBEHAVE_FACTORY, "RibbonTrail@+ f()", asFUNCTION(RibbonTrail_RibbonTrail_Context), asCALL_CDECL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "bool Save(Serializer&) const", asMETHODPR(RibbonTrail, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool SaveDefaultAttributes() const", asMETHODPR(RibbonTrail, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "bool SaveJSON(JSONValue&) const", asMETHODPR(RibbonTrail, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "bool SaveXML(XMLElement&) const", asMETHODPR(RibbonTrail, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void SendEvent(StringHash)", asMETHODPR(RibbonTrail, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(RibbonTrail, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAnimationEnabled(bool)", asMETHODPR(RibbonTrail, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_animationEnabled(bool)", asMETHODPR(RibbonTrail, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void RibbonTrail::SetAnimationLodBias(float bias) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAnimationLodBias(float)", asMETHODPR(RibbonTrail, SetAnimationLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_animationLodBias(float)", asMETHODPR(RibbonTrail, SetAnimationLodBias, (float), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAnimationTime(float)", asMETHODPR(RibbonTrail, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(RibbonTrail, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "bool set_attributes(uint, const Variant&in)", asMETHODPR(RibbonTrail, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(RibbonTrail, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(RibbonTrail, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(RibbonTrail, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(RibbonTrail, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(RibbonTrail, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetBasePass(uint)", asMETHODPR(RibbonTrail, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void RibbonTrail::SetBaseVelocity(const Vector3& baseVelocity) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetBaseVelocity(const Vector3&in)", asMETHODPR(RibbonTrail, SetBaseVelocity, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_baseVelocity(const Vector3&in)", asMETHODPR(RibbonTrail, SetBaseVelocity, (const Vector3&), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetBlockEvents(bool)", asMETHODPR(RibbonTrail, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetCastShadows(bool)", asMETHODPR(RibbonTrail, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_castShadows(bool)", asMETHODPR(RibbonTrail, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetDrawDistance(float)", asMETHODPR(RibbonTrail, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_drawDistance(float)", asMETHODPR(RibbonTrail, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void RibbonTrail::SetEmitting(bool emitting) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetEmitting(bool)", asMETHODPR(RibbonTrail, SetEmitting, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_emitting(bool)", asMETHODPR(RibbonTrail, SetEmitting, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetEnabled(bool)", asMETHODPR(RibbonTrail, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_enabled(bool)", asMETHODPR(RibbonTrail, SetEnabled, (bool), void), asCALL_THISCALL);
    // void RibbonTrail::SetEndColor(const Color& color) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetEndColor(const Color&in)", asMETHODPR(RibbonTrail, SetEndColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_endColor(const Color&in)", asMETHODPR(RibbonTrail, SetEndColor, (const Color&), void), asCALL_THISCALL);
    // void RibbonTrail::SetEndScale(float endScale) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetEndScale(float)", asMETHODPR(RibbonTrail, SetEndScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_endScale(float)", asMETHODPR(RibbonTrail, SetEndScale, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(RibbonTrail, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(RibbonTrail, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetInstanceDefault(bool)", asMETHODPR(RibbonTrail, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(RibbonTrail, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void RibbonTrail::SetLifetime(float time) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetLifetime(float)", asMETHODPR(RibbonTrail, SetLifetime, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_lifetime(float)", asMETHODPR(RibbonTrail, SetLifetime, (float), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetLightMask(uint)", asMETHODPR(RibbonTrail, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_lightMask(uint)", asMETHODPR(RibbonTrail, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetLodBias(float)", asMETHODPR(RibbonTrail, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_lodBias(float)", asMETHODPR(RibbonTrail, SetLodBias, (float), void), asCALL_THISCALL);
    // void RibbonTrail::SetMaterial(Material* material) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetMaterial(Material@+)", asMETHODPR(RibbonTrail, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_material(Material@+)", asMETHODPR(RibbonTrail, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void RibbonTrail::SetMaterialAttr(const ResourceRef& value) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(RibbonTrail, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetMaxLights(uint)", asMETHODPR(RibbonTrail, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_maxLights(uint)", asMETHODPR(RibbonTrail, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetMinMaxZ(float, float)", asMETHODPR(RibbonTrail, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(RibbonTrail, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(RibbonTrail, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(RibbonTrail, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetOccludee(bool)", asMETHODPR(RibbonTrail, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_occludee(bool)", asMETHODPR(RibbonTrail, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetOccluder(bool)", asMETHODPR(RibbonTrail, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_occluder(bool)", asMETHODPR(RibbonTrail, SetOccluder, (bool), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetShadowDistance(float)", asMETHODPR(RibbonTrail, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_shadowDistance(float)", asMETHODPR(RibbonTrail, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetShadowMask(uint)", asMETHODPR(RibbonTrail, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_shadowMask(uint)", asMETHODPR(RibbonTrail, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void RibbonTrail::SetSorted(bool enable) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetSorted(bool)", asMETHODPR(RibbonTrail, SetSorted, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_sorted(bool)", asMETHODPR(RibbonTrail, SetSorted, (bool), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetSortValue(float)", asMETHODPR(RibbonTrail, SetSortValue, (float), void), asCALL_THISCALL);
    // void RibbonTrail::SetStartColor(const Color& color) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetStartColor(const Color&in)", asMETHODPR(RibbonTrail, SetStartColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_startColor(const Color&in)", asMETHODPR(RibbonTrail, SetStartColor, (const Color&), void), asCALL_THISCALL);
    // void RibbonTrail::SetStartScale(float startScale) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetStartScale(float)", asMETHODPR(RibbonTrail, SetStartScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_startScale(float)", asMETHODPR(RibbonTrail, SetStartScale, (float), void), asCALL_THISCALL);
    // void RibbonTrail::SetTailColumn(unsigned tailColumn) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetTailColumn(uint)", asMETHODPR(RibbonTrail, SetTailColumn, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_tailColumn(uint)", asMETHODPR(RibbonTrail, SetTailColumn, (unsigned), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetTemporary(bool)", asMETHODPR(RibbonTrail, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_temporary(bool)", asMETHODPR(RibbonTrail, SetTemporary, (bool), void), asCALL_THISCALL);
    // void RibbonTrail::SetTrailType(TrailType type) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetTrailType(TrailType)", asMETHODPR(RibbonTrail, SetTrailType, (TrailType), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_trailType(TrailType)", asMETHODPR(RibbonTrail, SetTrailType, (TrailType), void), asCALL_THISCALL);
    // void RibbonTrail::SetUpdateInvisible(bool enable) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetUpdateInvisible(bool)", asMETHODPR(RibbonTrail, SetUpdateInvisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_updateInvisible(bool)", asMETHODPR(RibbonTrail, SetUpdateInvisible, (bool), void), asCALL_THISCALL);
    // void RibbonTrail::SetVertexDistance(float length) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetVertexDistance(float)", asMETHODPR(RibbonTrail, SetVertexDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_vertexDistance(float)", asMETHODPR(RibbonTrail, SetVertexDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetViewMask(uint)", asMETHODPR(RibbonTrail, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_viewMask(uint)", asMETHODPR(RibbonTrail, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void RibbonTrail::SetWidth(float width) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetWidth(float)", asMETHODPR(RibbonTrail, SetWidth, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_width(float)", asMETHODPR(RibbonTrail, SetWidth, (float), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetZone(Zone@+, bool = false)", asMETHODPR(RibbonTrail, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("RibbonTrail", "void SetZoneMask(uint)", asMETHODPR(RibbonTrail, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "void set_zoneMask(uint)", asMETHODPR(RibbonTrail, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void UnsubscribeFromAllEvents()", asMETHODPR(RibbonTrail, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(RibbonTrail_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(RibbonTrail, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(RibbonTrail, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RibbonTrail", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(RibbonTrail, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void RibbonTrail::Update(const FrameInfo& frame) override | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void Update(const FrameInfo&in)", asMETHODPR(RibbonTrail, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // void RibbonTrail::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(RibbonTrail, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // void RibbonTrail::UpdateGeometry(const FrameInfo& frame) override | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectMethod("RibbonTrail", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(RibbonTrail, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RibbonTrail", "int WeakRefs() const", asMETHODPR(RibbonTrail, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RibbonTrail", "int get_weakRefs() const", asMETHODPR(RibbonTrail, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(RibbonTrail, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(RibbonTrail, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RibbonTrail", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(RibbonTrail, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("RigidBody", "void Activate()", asMETHODPR(RigidBody, Activate, (), void), asCALL_THISCALL);
    // void RigidBody::AddConstraint(Constraint* constraint) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void AddConstraint(Constraint@+)", asMETHODPR(RigidBody, AddConstraint, (Constraint*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RigidBody", asBEHAVE_ADDREF, "void f()", asMETHODPR(RigidBody, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void AllocateNetworkState()", asMETHODPR(RigidBody, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void RigidBody::ApplyAttributes() override | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyAttributes()", asMETHODPR(RigidBody, ApplyAttributes, (), void), asCALL_THISCALL);
    // void RigidBody::ApplyForce(const Vector3& force) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyForce(const Vector3&in)", asMETHODPR(RigidBody, ApplyForce, (const Vector3&), void), asCALL_THISCALL);
    // void RigidBody::ApplyForce(const Vector3& force, const Vector3& position) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyForce(const Vector3&in, const Vector3&in)", asMETHODPR(RigidBody, ApplyForce, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    // void RigidBody::ApplyImpulse(const Vector3& impulse) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyImpulse(const Vector3&in)", asMETHODPR(RigidBody, ApplyImpulse, (const Vector3&), void), asCALL_THISCALL);
    // void RigidBody::ApplyImpulse(const Vector3& impulse, const Vector3& position) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyImpulse(const Vector3&in, const Vector3&in)", asMETHODPR(RigidBody, ApplyImpulse, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    // void RigidBody::ApplyTorque(const Vector3& torque) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyTorque(const Vector3&in)", asMETHODPR(RigidBody, ApplyTorque, (const Vector3&), void), asCALL_THISCALL);
    // void RigidBody::ApplyTorqueImpulse(const Vector3& torque) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyTorqueImpulse(const Vector3&in)", asMETHODPR(RigidBody, ApplyTorqueImpulse, (const Vector3&), void), asCALL_THISCALL);
    // void RigidBody::ApplyWorldTransform(const Vector3& newWorldPosition, const Quaternion& newWorldRotation) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ApplyWorldTransform(const Vector3&in, const Quaternion&in)", asMETHODPR(RigidBody, ApplyWorldTransform, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void RigidBody::DisableMassUpdate() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void DisableMassUpdate()", asMETHODPR(RigidBody, DisableMassUpdate, (), void), asCALL_THISCALL);
    // void RigidBody::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(RigidBody, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // void RigidBody::EnableMassUpdate() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void EnableMassUpdate()", asMETHODPR(RigidBody, EnableMassUpdate, (), void), asCALL_THISCALL);
    // float RigidBody::GetAngularDamping() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetAngularDamping() const", asMETHODPR(RigidBody, GetAngularDamping, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_angularDamping() const", asMETHODPR(RigidBody, GetAngularDamping, () const, float), asCALL_THISCALL);
    // Vector3 RigidBody::GetAngularFactor() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetAngularFactor() const", asMETHODPR(RigidBody, GetAngularFactor, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_angularFactor() const", asMETHODPR(RigidBody, GetAngularFactor, () const, Vector3), asCALL_THISCALL);
    // float RigidBody::GetAngularRestThreshold() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetAngularRestThreshold() const", asMETHODPR(RigidBody, GetAngularRestThreshold, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_angularRestThreshold() const", asMETHODPR(RigidBody, GetAngularRestThreshold, () const, float), asCALL_THISCALL);
    // Vector3 RigidBody::GetAngularVelocity() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetAngularVelocity() const", asMETHODPR(RigidBody, GetAngularVelocity, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_angularVelocity() const", asMETHODPR(RigidBody, GetAngularVelocity, () const, Vector3), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "bool GetAnimationEnabled() const", asMETHODPR(RigidBody, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_animationEnabled() const", asMETHODPR(RigidBody, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Vector3 RigidBody::GetAnisotropicFriction() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetAnisotropicFriction() const", asMETHODPR(RigidBody, GetAnisotropicFriction, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_anisotropicFriction() const", asMETHODPR(RigidBody, GetAnisotropicFriction, () const, Vector3), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "Variant GetAttribute(uint) const", asMETHODPR(RigidBody, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Variant get_attributes(uint) const", asMETHODPR(RigidBody, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "Variant GetAttribute(const String&in) const", asMETHODPR(RigidBody, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(RigidBody, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(RigidBody, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(RigidBody, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(RigidBody, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "Variant GetAttributeDefault(uint) const", asMETHODPR(RigidBody, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Variant get_attributeDefaults(uint) const", asMETHODPR(RigidBody, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(RigidBody, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "bool GetBlockEvents() const", asMETHODPR(RigidBody, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // btRigidBody* RigidBody::GetBody() const | File: ../Physics/RigidBody.h
    // Error: type "btRigidBody*" can not automatically bind
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "const String& GetCategory() const", asMETHODPR(RigidBody, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const String& get_category() const", asMETHODPR(RigidBody, GetCategory, () const, const String&), asCALL_THISCALL);
    // float RigidBody::GetCcdMotionThreshold() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetCcdMotionThreshold() const", asMETHODPR(RigidBody, GetCcdMotionThreshold, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_ccdMotionThreshold() const", asMETHODPR(RigidBody, GetCcdMotionThreshold, () const, float), asCALL_THISCALL);
    // float RigidBody::GetCcdRadius() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetCcdRadius() const", asMETHODPR(RigidBody, GetCcdRadius, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_ccdRadius() const", asMETHODPR(RigidBody, GetCcdRadius, () const, float), asCALL_THISCALL);
    // const Vector3& RigidBody::GetCenterOfMass() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "const Vector3& GetCenterOfMass() const", asMETHODPR(RigidBody, GetCenterOfMass, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const Vector3& get_centerOfMass() const", asMETHODPR(RigidBody, GetCenterOfMass, () const, const Vector3&), asCALL_THISCALL);
    // void RigidBody::GetCollidingBodies(PODVector<RigidBody*>& result) const | File: ../Physics/RigidBody.h
    // Error: type "PODVector<RigidBody*>&" can not automatically bind
    // CollisionEventMode RigidBody::GetCollisionEventMode() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "CollisionEventMode GetCollisionEventMode() const", asMETHODPR(RigidBody, GetCollisionEventMode, () const, CollisionEventMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "CollisionEventMode get_collisionEventMode() const", asMETHODPR(RigidBody, GetCollisionEventMode, () const, CollisionEventMode), asCALL_THISCALL);
    // unsigned RigidBody::GetCollisionLayer() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "uint GetCollisionLayer() const", asMETHODPR(RigidBody, GetCollisionLayer, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint get_collisionLayer() const", asMETHODPR(RigidBody, GetCollisionLayer, () const, unsigned), asCALL_THISCALL);
    // unsigned RigidBody::GetCollisionMask() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "uint GetCollisionMask() const", asMETHODPR(RigidBody, GetCollisionMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint get_collisionMask() const", asMETHODPR(RigidBody, GetCollisionMask, () const, unsigned), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "Component@+ GetComponent(StringHash) const", asMETHODPR(RigidBody, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
    // template<class T> T* Component::GetComponent() const | File: ../Scene/Component.h
    // Not registered because template
    // void Component::GetComponents(PODVector<Component*>& dest, StringHash type) const | File: ../Scene/Component.h
    // Error: type "PODVector<Component*>&" can not automatically bind
    // template<class T> void Component::GetComponents(PODVector<T*>& dest) const | File: ../Scene/Component.h
    // Not registered because template
    // btCompoundShape* RigidBody::GetCompoundShape() const | File: ../Physics/RigidBody.h
    // Error: type "btCompoundShape*" can not automatically bind
    // float RigidBody::GetContactProcessingThreshold() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetContactProcessingThreshold() const", asMETHODPR(RigidBody, GetContactProcessingThreshold, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_contactProcessingThreshold() const", asMETHODPR(RigidBody, GetContactProcessingThreshold, () const, float), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void Component::GetDependencyNodes(PODVector<Node*>& dest) | File: ../Scene/Component.h
    // Error: type "PODVector<Node*>&" can not automatically bind
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "VariantMap& GetEventDataMap() const", asMETHODPR(RigidBody, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "Object@+ GetEventSender() const", asMETHODPR(RigidBody, GetEventSender, () const, Object*), asCALL_THISCALL);
    // float RigidBody::GetFriction() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetFriction() const", asMETHODPR(RigidBody, GetFriction, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_friction() const", asMETHODPR(RigidBody, GetFriction, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(RigidBody, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const Variant& get_globalVar(StringHash) const", asMETHODPR(RigidBody, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "const VariantMap& GetGlobalVars() const", asMETHODPR(RigidBody, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const VariantMap& get_globalVars() const", asMETHODPR(RigidBody, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // const Vector3& RigidBody::GetGravityOverride() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "const Vector3& GetGravityOverride() const", asMETHODPR(RigidBody, GetGravityOverride, () const, const Vector3&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const Vector3& get_gravityOverride() const", asMETHODPR(RigidBody, GetGravityOverride, () const, const Vector3&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "uint GetID() const", asMETHODPR(RigidBody, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint get_id() const", asMETHODPR(RigidBody, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(RigidBody, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // float RigidBody::GetLinearDamping() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetLinearDamping() const", asMETHODPR(RigidBody, GetLinearDamping, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_linearDamping() const", asMETHODPR(RigidBody, GetLinearDamping, () const, float), asCALL_THISCALL);
    // Vector3 RigidBody::GetLinearFactor() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetLinearFactor() const", asMETHODPR(RigidBody, GetLinearFactor, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_linearFactor() const", asMETHODPR(RigidBody, GetLinearFactor, () const, Vector3), asCALL_THISCALL);
    // float RigidBody::GetLinearRestThreshold() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetLinearRestThreshold() const", asMETHODPR(RigidBody, GetLinearRestThreshold, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_linearRestThreshold() const", asMETHODPR(RigidBody, GetLinearRestThreshold, () const, float), asCALL_THISCALL);
    // Vector3 RigidBody::GetLinearVelocity() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetLinearVelocity() const", asMETHODPR(RigidBody, GetLinearVelocity, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_linearVelocity() const", asMETHODPR(RigidBody, GetLinearVelocity, () const, Vector3), asCALL_THISCALL);
    // float RigidBody::GetMass() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetMass() const", asMETHODPR(RigidBody, GetMass, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_mass() const", asMETHODPR(RigidBody, GetMass, () const, float), asCALL_THISCALL);
    // const PODVector<unsigned char>& RigidBody::GetNetAngularVelocityAttr() const | File: ../Physics/RigidBody.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "Node@+ GetNode() const", asMETHODPR(RigidBody, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Node@+ get_node() const", asMETHODPR(RigidBody, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "uint GetNumAttributes() const", asMETHODPR(RigidBody, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "uint get_numAttributes() const", asMETHODPR(RigidBody, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "uint GetNumNetworkAttributes() const", asMETHODPR(RigidBody, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(RigidBody, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(RigidBody, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(RigidBody, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // PhysicsWorld* RigidBody::GetPhysicsWorld() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "PhysicsWorld@+ GetPhysicsWorld() const", asMETHODPR(RigidBody, GetPhysicsWorld, () const, PhysicsWorld*), asCALL_THISCALL);
    // Vector3 RigidBody::GetPosition() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetPosition() const", asMETHODPR(RigidBody, GetPosition, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Vector3 get_position() const", asMETHODPR(RigidBody, GetPosition, () const, Vector3), asCALL_THISCALL);
    // float RigidBody::GetRestitution() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetRestitution() const", asMETHODPR(RigidBody, GetRestitution, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_restitution() const", asMETHODPR(RigidBody, GetRestitution, () const, float), asCALL_THISCALL);
    // float RigidBody::GetRollingFriction() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "float GetRollingFriction() const", asMETHODPR(RigidBody, GetRollingFriction, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "float get_rollingFriction() const", asMETHODPR(RigidBody, GetRollingFriction, () const, float), asCALL_THISCALL);
    // Quaternion RigidBody::GetRotation() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Quaternion GetRotation() const", asMETHODPR(RigidBody, GetRotation, () const, Quaternion), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "Quaternion get_rotation() const", asMETHODPR(RigidBody, GetRotation, () const, Quaternion), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "Scene@+ GetScene() const", asMETHODPR(RigidBody, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(RigidBody, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "StringHash GetType() const", asMETHODPR(RigidBody, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "StringHash get_type() const", asMETHODPR(RigidBody, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "const String& GetTypeName() const", asMETHODPR(RigidBody, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "const String& get_typeName() const", asMETHODPR(RigidBody, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool RigidBody::GetUseGravity() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "bool GetUseGravity() const", asMETHODPR(RigidBody, GetUseGravity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_useGravity() const", asMETHODPR(RigidBody, GetUseGravity, () const, bool), asCALL_THISCALL);
    // Vector3 RigidBody::GetVelocityAtPoint(const Vector3& position) const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "Vector3 GetVelocityAtPoint(const Vector3&in) const", asMETHODPR(RigidBody, GetVelocityAtPoint, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // void RigidBody::getWorldTransform(btTransform& worldTrans) const override | File: ../Physics/RigidBody.h
    // Not registered because have @nobind mark
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "bool HasEventHandlers() const", asMETHODPR(RigidBody, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(RigidBody, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(RigidBody, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool RigidBody::IsActive() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "bool IsActive() const", asMETHODPR(RigidBody, IsActive, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_active() const", asMETHODPR(RigidBody, IsActive, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "bool IsEnabled() const", asMETHODPR(RigidBody, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_enabled() const", asMETHODPR(RigidBody, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "bool IsEnabledEffective() const", asMETHODPR(RigidBody, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_enabledEffective() const", asMETHODPR(RigidBody, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "bool IsInstanceOf(StringHash) const", asMETHODPR(RigidBody, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool RigidBody::IsKinematic() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "bool IsKinematic() const", asMETHODPR(RigidBody, IsKinematic, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_kinematic() const", asMETHODPR(RigidBody, IsKinematic, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "bool IsReplicated() const", asMETHODPR(RigidBody, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_replicated() const", asMETHODPR(RigidBody, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool IsTemporary() const", asMETHODPR(RigidBody, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_temporary() const", asMETHODPR(RigidBody, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool RigidBody::IsTrigger() const | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "bool IsTrigger() const", asMETHODPR(RigidBody, IsTrigger, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool get_trigger() const", asMETHODPR(RigidBody, IsTrigger, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool Load(Deserializer&)", asMETHODPR(RigidBody, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "bool LoadJSON(const JSONValue&in)", asMETHODPR(RigidBody, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "bool LoadXML(const XMLElement&in)", asMETHODPR(RigidBody, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "void MarkNetworkUpdate()", asMETHODPR(RigidBody, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(RigidBody, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(RigidBody, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(RigidBody, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void RigidBody::OnSetEnabled() override | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void OnSetEnabled()", asMETHODPR(RigidBody, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "void PrepareNetworkUpdate()", asMETHODPR(RigidBody, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void RigidBody::ReAddBodyToWorld() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ReAddBodyToWorld()", asMETHODPR(RigidBody, ReAddBodyToWorld, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(RigidBody, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(RigidBody, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RigidBody", "int Refs() const", asMETHODPR(RigidBody, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "int get_refs() const", asMETHODPR(RigidBody, Refs, () const, int), asCALL_THISCALL);
    // static void RigidBody::RegisterObject(Context* context) | File: ../Physics/RigidBody.h
    // Not registered because have @nobind mark
    // void RigidBody::ReleaseBody() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ReleaseBody()", asMETHODPR(RigidBody, ReleaseBody, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RigidBody", asBEHAVE_RELEASE, "void f()", asMETHODPR(RigidBody, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "void Remove()", asMETHODPR(RigidBody, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(RigidBody, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void RigidBody::RemoveConstraint(Constraint* constraint) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void RemoveConstraint(Constraint@+)", asMETHODPR(RigidBody, RemoveConstraint, (Constraint*), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void RemoveInstanceDefault()", asMETHODPR(RigidBody, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void RemoveObjectAnimation()", asMETHODPR(RigidBody, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void RigidBody::ResetForces() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void ResetForces()", asMETHODPR(RigidBody, ResetForces, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void ResetToDefault()", asMETHODPR(RigidBody, ResetToDefault, (), void), asCALL_THISCALL);
    // explicit RigidBody::RigidBody(Context* context) | File: ../Physics/RigidBody.h
    engine->RegisterObjectBehaviour("RigidBody", asBEHAVE_FACTORY, "RigidBody@+ f()", asFUNCTION(RigidBody_RigidBody_Context), asCALL_CDECL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "bool Save(Serializer&) const", asMETHODPR(RigidBody, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool SaveDefaultAttributes() const", asMETHODPR(RigidBody, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "bool SaveJSON(JSONValue&) const", asMETHODPR(RigidBody, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "bool SaveXML(XMLElement&) const", asMETHODPR(RigidBody, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void SendEvent(StringHash)", asMETHODPR(RigidBody, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(RigidBody, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void RigidBody::SetAngularDamping(float damping) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetAngularDamping(float)", asMETHODPR(RigidBody, SetAngularDamping, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularDamping(float)", asMETHODPR(RigidBody, SetAngularDamping, (float), void), asCALL_THISCALL);
    // void RigidBody::SetAngularFactor(const Vector3& factor) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetAngularFactor(const Vector3&in)", asMETHODPR(RigidBody, SetAngularFactor, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularFactor(const Vector3&in)", asMETHODPR(RigidBody, SetAngularFactor, (const Vector3&), void), asCALL_THISCALL);
    // void RigidBody::SetAngularRestThreshold(float threshold) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetAngularRestThreshold(float)", asMETHODPR(RigidBody, SetAngularRestThreshold, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularRestThreshold(float)", asMETHODPR(RigidBody, SetAngularRestThreshold, (float), void), asCALL_THISCALL);
    // void RigidBody::SetAngularVelocity(const Vector3& velocity) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetAngularVelocity(const Vector3&in)", asMETHODPR(RigidBody, SetAngularVelocity, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_angularVelocity(const Vector3&in)", asMETHODPR(RigidBody, SetAngularVelocity, (const Vector3&), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetAnimationEnabled(bool)", asMETHODPR(RigidBody, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_animationEnabled(bool)", asMETHODPR(RigidBody, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetAnimationTime(float)", asMETHODPR(RigidBody, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void RigidBody::SetAnisotropicFriction(const Vector3& friction) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetAnisotropicFriction(const Vector3&in)", asMETHODPR(RigidBody, SetAnisotropicFriction, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_anisotropicFriction(const Vector3&in)", asMETHODPR(RigidBody, SetAnisotropicFriction, (const Vector3&), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(RigidBody, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "bool set_attributes(uint, const Variant&in)", asMETHODPR(RigidBody, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(RigidBody, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(RigidBody, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(RigidBody, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(RigidBody, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(RigidBody, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void SetBlockEvents(bool)", asMETHODPR(RigidBody, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void RigidBody::SetCcdMotionThreshold(float threshold) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetCcdMotionThreshold(float)", asMETHODPR(RigidBody, SetCcdMotionThreshold, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_ccdMotionThreshold(float)", asMETHODPR(RigidBody, SetCcdMotionThreshold, (float), void), asCALL_THISCALL);
    // void RigidBody::SetCcdRadius(float radius) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetCcdRadius(float)", asMETHODPR(RigidBody, SetCcdRadius, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_ccdRadius(float)", asMETHODPR(RigidBody, SetCcdRadius, (float), void), asCALL_THISCALL);
    // void RigidBody::SetCollisionEventMode(CollisionEventMode mode) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetCollisionEventMode(CollisionEventMode)", asMETHODPR(RigidBody, SetCollisionEventMode, (CollisionEventMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_collisionEventMode(CollisionEventMode)", asMETHODPR(RigidBody, SetCollisionEventMode, (CollisionEventMode), void), asCALL_THISCALL);
    // void RigidBody::SetCollisionLayer(unsigned layer) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetCollisionLayer(uint)", asMETHODPR(RigidBody, SetCollisionLayer, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_collisionLayer(uint)", asMETHODPR(RigidBody, SetCollisionLayer, (unsigned), void), asCALL_THISCALL);
    // void RigidBody::SetCollisionLayerAndMask(unsigned layer, unsigned mask) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetCollisionLayerAndMask(uint, uint)", asMETHODPR(RigidBody, SetCollisionLayerAndMask, (unsigned, unsigned), void), asCALL_THISCALL);
    // void RigidBody::SetCollisionMask(unsigned mask) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetCollisionMask(uint)", asMETHODPR(RigidBody, SetCollisionMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_collisionMask(uint)", asMETHODPR(RigidBody, SetCollisionMask, (unsigned), void), asCALL_THISCALL);
    // void RigidBody::SetContactProcessingThreshold(float threshold) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetContactProcessingThreshold(float)", asMETHODPR(RigidBody, SetContactProcessingThreshold, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_contactProcessingThreshold(float)", asMETHODPR(RigidBody, SetContactProcessingThreshold, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody", "void SetEnabled(bool)", asMETHODPR(RigidBody, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_enabled(bool)", asMETHODPR(RigidBody, SetEnabled, (bool), void), asCALL_THISCALL);
    // void RigidBody::SetFriction(float friction) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetFriction(float)", asMETHODPR(RigidBody, SetFriction, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_friction(float)", asMETHODPR(RigidBody, SetFriction, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(RigidBody, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(RigidBody, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void RigidBody::SetGravityOverride(const Vector3& gravity) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetGravityOverride(const Vector3&in)", asMETHODPR(RigidBody, SetGravityOverride, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_gravityOverride(const Vector3&in)", asMETHODPR(RigidBody, SetGravityOverride, (const Vector3&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void SetInstanceDefault(bool)", asMETHODPR(RigidBody, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(RigidBody, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void RigidBody::SetKinematic(bool enable) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetKinematic(bool)", asMETHODPR(RigidBody, SetKinematic, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_kinematic(bool)", asMETHODPR(RigidBody, SetKinematic, (bool), void), asCALL_THISCALL);
    // void RigidBody::SetLinearDamping(float damping) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetLinearDamping(float)", asMETHODPR(RigidBody, SetLinearDamping, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearDamping(float)", asMETHODPR(RigidBody, SetLinearDamping, (float), void), asCALL_THISCALL);
    // void RigidBody::SetLinearFactor(const Vector3& factor) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetLinearFactor(const Vector3&in)", asMETHODPR(RigidBody, SetLinearFactor, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearFactor(const Vector3&in)", asMETHODPR(RigidBody, SetLinearFactor, (const Vector3&), void), asCALL_THISCALL);
    // void RigidBody::SetLinearRestThreshold(float threshold) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetLinearRestThreshold(float)", asMETHODPR(RigidBody, SetLinearRestThreshold, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearRestThreshold(float)", asMETHODPR(RigidBody, SetLinearRestThreshold, (float), void), asCALL_THISCALL);
    // void RigidBody::SetLinearVelocity(const Vector3& velocity) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetLinearVelocity(const Vector3&in)", asMETHODPR(RigidBody, SetLinearVelocity, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_linearVelocity(const Vector3&in)", asMETHODPR(RigidBody, SetLinearVelocity, (const Vector3&), void), asCALL_THISCALL);
    // void RigidBody::SetMass(float mass) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetMass(float)", asMETHODPR(RigidBody, SetMass, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_mass(float)", asMETHODPR(RigidBody, SetMass, (float), void), asCALL_THISCALL);
    // void RigidBody::SetNetAngularVelocityAttr(const PODVector<unsigned char>& value) | File: ../Physics/RigidBody.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(RigidBody, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(RigidBody, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(RigidBody, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void RigidBody::SetPosition(const Vector3& position) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetPosition(const Vector3&in)", asMETHODPR(RigidBody, SetPosition, (const Vector3&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_position(const Vector3&in)", asMETHODPR(RigidBody, SetPosition, (const Vector3&), void), asCALL_THISCALL);
    // void RigidBody::SetRestitution(float restitution) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetRestitution(float)", asMETHODPR(RigidBody, SetRestitution, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_restitution(float)", asMETHODPR(RigidBody, SetRestitution, (float), void), asCALL_THISCALL);
    // void RigidBody::SetRollingFriction(float friction) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetRollingFriction(float)", asMETHODPR(RigidBody, SetRollingFriction, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_rollingFriction(float)", asMETHODPR(RigidBody, SetRollingFriction, (float), void), asCALL_THISCALL);
    // void RigidBody::SetRotation(const Quaternion& rotation) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetRotation(const Quaternion&in)", asMETHODPR(RigidBody, SetRotation, (const Quaternion&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_rotation(const Quaternion&in)", asMETHODPR(RigidBody, SetRotation, (const Quaternion&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void SetTemporary(bool)", asMETHODPR(RigidBody, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_temporary(bool)", asMETHODPR(RigidBody, SetTemporary, (bool), void), asCALL_THISCALL);
    // void RigidBody::SetTransform(const Vector3& position, const Quaternion& rotation) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetTransform(const Vector3&in, const Quaternion&in)", asMETHODPR(RigidBody, SetTransform, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // void RigidBody::SetTrigger(bool enable) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetTrigger(bool)", asMETHODPR(RigidBody, SetTrigger, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_trigger(bool)", asMETHODPR(RigidBody, SetTrigger, (bool), void), asCALL_THISCALL);
    // void RigidBody::SetUseGravity(bool enable) | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void SetUseGravity(bool)", asMETHODPR(RigidBody, SetUseGravity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "void set_useGravity(bool)", asMETHODPR(RigidBody, SetUseGravity, (bool), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("RigidBody", "void UnsubscribeFromAllEvents()", asMETHODPR(RigidBody, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(RigidBody_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(RigidBody, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(RigidBody, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(RigidBody, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void RigidBody::UpdateGravity() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void UpdateGravity()", asMETHODPR(RigidBody, UpdateGravity, (), void), asCALL_THISCALL);
    // void RigidBody::UpdateMass() | File: ../Physics/RigidBody.h
    engine->RegisterObjectMethod("RigidBody", "void UpdateMass()", asMETHODPR(RigidBody, UpdateMass, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RigidBody", "int WeakRefs() const", asMETHODPR(RigidBody, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody", "int get_weakRefs() const", asMETHODPR(RigidBody, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(RigidBody, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(RigidBody, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(RigidBody, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("RigidBody2D", "void AddCollisionShape2D(CollisionShape2D@+)", asMETHODPR(RigidBody2D, AddCollisionShape2D, (CollisionShape2D*), void), asCALL_THISCALL);
    // void RigidBody2D::AddConstraint2D(Constraint2D* constraint) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void AddConstraint2D(Constraint2D@+)", asMETHODPR(RigidBody2D, AddConstraint2D, (Constraint2D*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RigidBody2D", asBEHAVE_ADDREF, "void f()", asMETHODPR(RigidBody2D, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void AllocateNetworkState()", asMETHODPR(RigidBody2D, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void RigidBody2D::ApplyAngularImpulse(float impulse, bool wake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyAngularImpulse(float, bool)", asMETHODPR(RigidBody2D, ApplyAngularImpulse, (float, bool), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyAttributes()", asMETHODPR(RigidBody2D, ApplyAttributes, (), void), asCALL_THISCALL);
    // void RigidBody2D::ApplyForce(const Vector2& force, const Vector2& point, bool wake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyForce(const Vector2&in, const Vector2&in, bool)", asMETHODPR(RigidBody2D, ApplyForce, (const Vector2&, const Vector2&, bool), void), asCALL_THISCALL);
    // void RigidBody2D::ApplyForceToCenter(const Vector2& force, bool wake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyForceToCenter(const Vector2&in, bool)", asMETHODPR(RigidBody2D, ApplyForceToCenter, (const Vector2&, bool), void), asCALL_THISCALL);
    // void RigidBody2D::ApplyLinearImpulse(const Vector2& impulse, const Vector2& point, bool wake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyLinearImpulse(const Vector2&in, const Vector2&in, bool)", asMETHODPR(RigidBody2D, ApplyLinearImpulse, (const Vector2&, const Vector2&, bool), void), asCALL_THISCALL);
    // void RigidBody2D::ApplyLinearImpulseToCenter(const Vector2& impulse, bool wake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyLinearImpulseToCenter(const Vector2&in, bool)", asMETHODPR(RigidBody2D, ApplyLinearImpulseToCenter, (const Vector2&, bool), void), asCALL_THISCALL);
    // void RigidBody2D::ApplyTorque(float torque, bool wake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyTorque(float, bool)", asMETHODPR(RigidBody2D, ApplyTorque, (float, bool), void), asCALL_THISCALL);
    // void RigidBody2D::ApplyWorldTransform() | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyWorldTransform()", asMETHODPR(RigidBody2D, ApplyWorldTransform, (), void), asCALL_THISCALL);
    // void RigidBody2D::ApplyWorldTransform(const Vector3& newWorldPosition, const Quaternion& newWorldRotation) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyWorldTransform(const Vector3&in, const Quaternion&in)", asMETHODPR(RigidBody2D, ApplyWorldTransform, (const Vector3&, const Quaternion&), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void RigidBody2D::CreateBody() | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void CreateBody()", asMETHODPR(RigidBody2D, CreateBody, (), void), asCALL_THISCALL);
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(RigidBody2D, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // float RigidBody2D::GetAngularDamping() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetAngularDamping() const", asMETHODPR(RigidBody2D, GetAngularDamping, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_angularDamping() const", asMETHODPR(RigidBody2D, GetAngularDamping, () const, float), asCALL_THISCALL);
    // float RigidBody2D::GetAngularVelocity() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetAngularVelocity() const", asMETHODPR(RigidBody2D, GetAngularVelocity, () const, float), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool GetAnimationEnabled() const", asMETHODPR(RigidBody2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_animationEnabled() const", asMETHODPR(RigidBody2D, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "Variant GetAttribute(uint) const", asMETHODPR(RigidBody2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Variant get_attributes(uint) const", asMETHODPR(RigidBody2D, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "Variant GetAttribute(const String&in) const", asMETHODPR(RigidBody2D, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(RigidBody2D, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(RigidBody2D, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(RigidBody2D, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(RigidBody2D, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "Variant GetAttributeDefault(uint) const", asMETHODPR(RigidBody2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Variant get_attributeDefaults(uint) const", asMETHODPR(RigidBody2D, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(RigidBody2D, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "bool GetBlockEvents() const", asMETHODPR(RigidBody2D, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // b2Body* RigidBody2D::GetBody() const | File: ../Urho2D/RigidBody2D.h
    // Error: type "b2Body*" can not automatically bind
    // BodyType2D RigidBody2D::GetBodyType() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "BodyType2D GetBodyType() const", asMETHODPR(RigidBody2D, GetBodyType, () const, BodyType2D), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "BodyType2D get_bodyType() const", asMETHODPR(RigidBody2D, GetBodyType, () const, BodyType2D), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "const String& GetCategory() const", asMETHODPR(RigidBody2D, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "const String& get_category() const", asMETHODPR(RigidBody2D, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "Component@+ GetComponent(StringHash) const", asMETHODPR(RigidBody2D, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("RigidBody2D", "VariantMap& GetEventDataMap() const", asMETHODPR(RigidBody2D, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "Object@+ GetEventSender() const", asMETHODPR(RigidBody2D, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(RigidBody2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "const Variant& get_globalVar(StringHash) const", asMETHODPR(RigidBody2D, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "const VariantMap& GetGlobalVars() const", asMETHODPR(RigidBody2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "const VariantMap& get_globalVars() const", asMETHODPR(RigidBody2D, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // float RigidBody2D::GetGravityScale() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetGravityScale() const", asMETHODPR(RigidBody2D, GetGravityScale, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_gravityScale() const", asMETHODPR(RigidBody2D, GetGravityScale, () const, float), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "uint GetID() const", asMETHODPR(RigidBody2D, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "uint get_id() const", asMETHODPR(RigidBody2D, GetID, () const, unsigned), asCALL_THISCALL);
    // float RigidBody2D::GetInertia() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetInertia() const", asMETHODPR(RigidBody2D, GetInertia, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_inertia() const", asMETHODPR(RigidBody2D, GetInertia, () const, float), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(RigidBody2D, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // float RigidBody2D::GetLinearDamping() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetLinearDamping() const", asMETHODPR(RigidBody2D, GetLinearDamping, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_linearDamping() const", asMETHODPR(RigidBody2D, GetLinearDamping, () const, float), asCALL_THISCALL);
    // Vector2 RigidBody2D::GetLinearVelocity() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "Vector2 GetLinearVelocity() const", asMETHODPR(RigidBody2D, GetLinearVelocity, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Vector2 get_linearVelocity() const", asMETHODPR(RigidBody2D, GetLinearVelocity, () const, Vector2), asCALL_THISCALL);
    // float RigidBody2D::GetMass() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "float GetMass() const", asMETHODPR(RigidBody2D, GetMass, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_mass() const", asMETHODPR(RigidBody2D, GetMass, () const, float), asCALL_THISCALL);
    // Vector2 RigidBody2D::GetMassCenter() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "Vector2 GetMassCenter() const", asMETHODPR(RigidBody2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Vector2 get_massCenter() const", asMETHODPR(RigidBody2D, GetMassCenter, () const, Vector2), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "Node@+ GetNode() const", asMETHODPR(RigidBody2D, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Node@+ get_node() const", asMETHODPR(RigidBody2D, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "uint GetNumAttributes() const", asMETHODPR(RigidBody2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "uint get_numAttributes() const", asMETHODPR(RigidBody2D, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "uint GetNumNetworkAttributes() const", asMETHODPR(RigidBody2D, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(RigidBody2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(RigidBody2D, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(RigidBody2D, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "Scene@+ GetScene() const", asMETHODPR(RigidBody2D, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(RigidBody2D, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "StringHash GetType() const", asMETHODPR(RigidBody2D, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "StringHash get_type() const", asMETHODPR(RigidBody2D, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "const String& GetTypeName() const", asMETHODPR(RigidBody2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "const String& get_typeName() const", asMETHODPR(RigidBody2D, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool RigidBody2D::GetUseFixtureMass() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "bool GetUseFixtureMass() const", asMETHODPR(RigidBody2D, GetUseFixtureMass, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_useFixtureMass() const", asMETHODPR(RigidBody2D, GetUseFixtureMass, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "bool HasEventHandlers() const", asMETHODPR(RigidBody2D, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(RigidBody2D, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(RigidBody2D, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool RigidBody2D::IsAllowSleep() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsAllowSleep() const", asMETHODPR(RigidBody2D, IsAllowSleep, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_allowSleep() const", asMETHODPR(RigidBody2D, IsAllowSleep, () const, bool), asCALL_THISCALL);
    // bool RigidBody2D::IsAwake() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsAwake() const", asMETHODPR(RigidBody2D, IsAwake, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_awake() const", asMETHODPR(RigidBody2D, IsAwake, () const, bool), asCALL_THISCALL);
    // bool RigidBody2D::IsBullet() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsBullet() const", asMETHODPR(RigidBody2D, IsBullet, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_bullet() const", asMETHODPR(RigidBody2D, IsBullet, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsEnabled() const", asMETHODPR(RigidBody2D, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_enabled() const", asMETHODPR(RigidBody2D, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsEnabledEffective() const", asMETHODPR(RigidBody2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_enabledEffective() const", asMETHODPR(RigidBody2D, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool RigidBody2D::IsFixedRotation() const | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsFixedRotation() const", asMETHODPR(RigidBody2D, IsFixedRotation, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_fixedRotation() const", asMETHODPR(RigidBody2D, IsFixedRotation, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsInstanceOf(StringHash) const", asMETHODPR(RigidBody2D, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsReplicated() const", asMETHODPR(RigidBody2D, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_replicated() const", asMETHODPR(RigidBody2D, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool IsTemporary() const", asMETHODPR(RigidBody2D, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_temporary() const", asMETHODPR(RigidBody2D, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool Load(Deserializer&)", asMETHODPR(RigidBody2D, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool LoadJSON(const JSONValue&in)", asMETHODPR(RigidBody2D, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool LoadXML(const XMLElement&in)", asMETHODPR(RigidBody2D, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "void MarkNetworkUpdate()", asMETHODPR(RigidBody2D, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(RigidBody2D, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(RigidBody2D, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(RigidBody2D, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void RigidBody2D::OnSetEnabled() override | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void OnSetEnabled()", asMETHODPR(RigidBody2D, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "void PrepareNetworkUpdate()", asMETHODPR(RigidBody2D, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(RigidBody2D, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(RigidBody2D, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RigidBody2D", "int Refs() const", asMETHODPR(RigidBody2D, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "int get_refs() const", asMETHODPR(RigidBody2D, Refs, () const, int), asCALL_THISCALL);
    // static void RigidBody2D::RegisterObject(Context* context) | File: ../Urho2D/RigidBody2D.h
    // Not registered because have @nobind mark
    // void RigidBody2D::ReleaseBody() | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void ReleaseBody()", asMETHODPR(RigidBody2D, ReleaseBody, (), void), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("RigidBody2D", asBEHAVE_RELEASE, "void f()", asMETHODPR(RigidBody2D, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "void Remove()", asMETHODPR(RigidBody2D, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(RigidBody2D, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void RigidBody2D::RemoveCollisionShape2D(CollisionShape2D* collisionShape) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void RemoveCollisionShape2D(CollisionShape2D@+)", asMETHODPR(RigidBody2D, RemoveCollisionShape2D, (CollisionShape2D*), void), asCALL_THISCALL);
    // void RigidBody2D::RemoveConstraint2D(Constraint2D* constraint) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void RemoveConstraint2D(Constraint2D@+)", asMETHODPR(RigidBody2D, RemoveConstraint2D, (Constraint2D*), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void RemoveInstanceDefault()", asMETHODPR(RigidBody2D, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void RemoveObjectAnimation()", asMETHODPR(RigidBody2D, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void ResetToDefault()", asMETHODPR(RigidBody2D, ResetToDefault, (), void), asCALL_THISCALL);
    // explicit RigidBody2D::RigidBody2D(Context* context) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectBehaviour("RigidBody2D", asBEHAVE_FACTORY, "RigidBody2D@+ f()", asFUNCTION(RigidBody2D_RigidBody2D_Context), asCALL_CDECL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "bool Save(Serializer&) const", asMETHODPR(RigidBody2D, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool SaveDefaultAttributes() const", asMETHODPR(RigidBody2D, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "bool SaveJSON(JSONValue&) const", asMETHODPR(RigidBody2D, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "bool SaveXML(XMLElement&) const", asMETHODPR(RigidBody2D, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void SendEvent(StringHash)", asMETHODPR(RigidBody2D, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(RigidBody2D, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void RigidBody2D::SetAllowSleep(bool allowSleep) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAllowSleep(bool)", asMETHODPR(RigidBody2D, SetAllowSleep, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_allowSleep(bool)", asMETHODPR(RigidBody2D, SetAllowSleep, (bool), void), asCALL_THISCALL);
    // void RigidBody2D::SetAngularDamping(float angularDamping) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAngularDamping(float)", asMETHODPR(RigidBody2D, SetAngularDamping, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_angularDamping(float)", asMETHODPR(RigidBody2D, SetAngularDamping, (float), void), asCALL_THISCALL);
    // void RigidBody2D::SetAngularVelocity(float angularVelocity) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAngularVelocity(float)", asMETHODPR(RigidBody2D, SetAngularVelocity, (float), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAnimationEnabled(bool)", asMETHODPR(RigidBody2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_animationEnabled(bool)", asMETHODPR(RigidBody2D, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAnimationTime(float)", asMETHODPR(RigidBody2D, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(RigidBody2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool set_attributes(uint, const Variant&in)", asMETHODPR(RigidBody2D, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(RigidBody2D, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(RigidBody2D, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(RigidBody2D, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(RigidBody2D, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(RigidBody2D, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void RigidBody2D::SetAwake(bool awake) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetAwake(bool)", asMETHODPR(RigidBody2D, SetAwake, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_awake(bool)", asMETHODPR(RigidBody2D, SetAwake, (bool), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetBlockEvents(bool)", asMETHODPR(RigidBody2D, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void RigidBody2D::SetBodyType(BodyType2D type) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetBodyType(BodyType2D)", asMETHODPR(RigidBody2D, SetBodyType, (BodyType2D), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_bodyType(BodyType2D)", asMETHODPR(RigidBody2D, SetBodyType, (BodyType2D), void), asCALL_THISCALL);
    // void RigidBody2D::SetBullet(bool bullet) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetBullet(bool)", asMETHODPR(RigidBody2D, SetBullet, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_bullet(bool)", asMETHODPR(RigidBody2D, SetBullet, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetEnabled(bool)", asMETHODPR(RigidBody2D, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_enabled(bool)", asMETHODPR(RigidBody2D, SetEnabled, (bool), void), asCALL_THISCALL);
    // void RigidBody2D::SetFixedRotation(bool fixedRotation) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetFixedRotation(bool)", asMETHODPR(RigidBody2D, SetFixedRotation, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_fixedRotation(bool)", asMETHODPR(RigidBody2D, SetFixedRotation, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(RigidBody2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(RigidBody2D, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void RigidBody2D::SetGravityScale(float gravityScale) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetGravityScale(float)", asMETHODPR(RigidBody2D, SetGravityScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_gravityScale(float)", asMETHODPR(RigidBody2D, SetGravityScale, (float), void), asCALL_THISCALL);
    // void RigidBody2D::SetInertia(float inertia) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetInertia(float)", asMETHODPR(RigidBody2D, SetInertia, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_inertia(float)", asMETHODPR(RigidBody2D, SetInertia, (float), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetInstanceDefault(bool)", asMETHODPR(RigidBody2D, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(RigidBody2D, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void RigidBody2D::SetLinearDamping(float linearDamping) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetLinearDamping(float)", asMETHODPR(RigidBody2D, SetLinearDamping, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_linearDamping(float)", asMETHODPR(RigidBody2D, SetLinearDamping, (float), void), asCALL_THISCALL);
    // void RigidBody2D::SetLinearVelocity(const Vector2& linearVelocity) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetLinearVelocity(const Vector2&in)", asMETHODPR(RigidBody2D, SetLinearVelocity, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_linearVelocity(const Vector2&in)", asMETHODPR(RigidBody2D, SetLinearVelocity, (const Vector2&), void), asCALL_THISCALL);
    // void RigidBody2D::SetMass(float mass) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetMass(float)", asMETHODPR(RigidBody2D, SetMass, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_mass(float)", asMETHODPR(RigidBody2D, SetMass, (float), void), asCALL_THISCALL);
    // void RigidBody2D::SetMassCenter(const Vector2& center) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetMassCenter(const Vector2&in)", asMETHODPR(RigidBody2D, SetMassCenter, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_massCenter(const Vector2&in)", asMETHODPR(RigidBody2D, SetMassCenter, (const Vector2&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(RigidBody2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(RigidBody2D, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(RigidBody2D, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetTemporary(bool)", asMETHODPR(RigidBody2D, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_temporary(bool)", asMETHODPR(RigidBody2D, SetTemporary, (bool), void), asCALL_THISCALL);
    // void RigidBody2D::SetUseFixtureMass(bool useFixtureMass) | File: ../Urho2D/RigidBody2D.h
    engine->RegisterObjectMethod("RigidBody2D", "void SetUseFixtureMass(bool)", asMETHODPR(RigidBody2D, SetUseFixtureMass, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_useFixtureMass(bool)", asMETHODPR(RigidBody2D, SetUseFixtureMass, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void UnsubscribeFromAllEvents()", asMETHODPR(RigidBody2D, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(RigidBody2D_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(RigidBody2D, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(RigidBody2D, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("RigidBody2D", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(RigidBody2D, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("RigidBody2D", "int WeakRefs() const", asMETHODPR(RigidBody2D, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "int get_weakRefs() const", asMETHODPR(RigidBody2D, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(RigidBody2D, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(RigidBody2D, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("RigidBody2D", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(RigidBody2D, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("RenderPathCommand", "const String& GetDepthStencilName() const", asMETHODPR(RenderPathCommand, GetDepthStencilName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "const String& get_depthStencilName() const", asMETHODPR(RenderPathCommand, GetDepthStencilName, () const, const String&), asCALL_THISCALL);
    // unsigned RenderPathCommand::GetNumOutputs() const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "uint GetNumOutputs() const", asMETHODPR(RenderPathCommand, GetNumOutputs, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "uint get_numOutputs() const", asMETHODPR(RenderPathCommand, GetNumOutputs, () const, unsigned), asCALL_THISCALL);
    // CubeMapFace RenderPathCommand::GetOutputFace(unsigned index) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "CubeMapFace GetOutputFace(uint) const", asMETHODPR(RenderPathCommand, GetOutputFace, (unsigned) const, CubeMapFace), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "CubeMapFace get_outputFaces(uint) const", asMETHODPR(RenderPathCommand, GetOutputFace, (unsigned) const, CubeMapFace), asCALL_THISCALL);
    // const String& RenderPathCommand::GetOutputName(unsigned index) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "const String& GetOutputName(uint) const", asMETHODPR(RenderPathCommand, GetOutputName, (unsigned) const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "const String& get_outputNames(uint) const", asMETHODPR(RenderPathCommand, GetOutputName, (unsigned) const, const String&), asCALL_THISCALL);
    // const Variant& RenderPathCommand::GetShaderParameter(const String& name) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "const Variant& GetShaderParameter(const String&in) const", asMETHODPR(RenderPathCommand, GetShaderParameter, (const String&) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "const Variant& get_shaderParameters(const String&in) const", asMETHODPR(RenderPathCommand, GetShaderParameter, (const String&) const, const Variant&), asCALL_THISCALL);
    // const String& RenderPathCommand::GetTextureName(TextureUnit unit) const | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "const String& GetTextureName(TextureUnit) const", asMETHODPR(RenderPathCommand, GetTextureName, (TextureUnit) const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "const String& get_textureNames(TextureUnit) const", asMETHODPR(RenderPathCommand, GetTextureName, (TextureUnit) const, const String&), asCALL_THISCALL);
    // void RenderPathCommand::Load(const XMLElement& element) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void Load(const XMLElement&in)", asMETHODPR(RenderPathCommand, Load, (const XMLElement&), void), asCALL_THISCALL);
    // void RenderPathCommand::RemoveShaderParameter(const String& name) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void RemoveShaderParameter(const String&in)", asMETHODPR(RenderPathCommand, RemoveShaderParameter, (const String&), void), asCALL_THISCALL);
    // void RenderPathCommand::SetDepthStencilName(const String& name) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetDepthStencilName(const String&in)", asMETHODPR(RenderPathCommand, SetDepthStencilName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "void set_depthStencilName(const String&in)", asMETHODPR(RenderPathCommand, SetDepthStencilName, (const String&), void), asCALL_THISCALL);
    // void RenderPathCommand::SetNumOutputs(unsigned num) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetNumOutputs(uint)", asMETHODPR(RenderPathCommand, SetNumOutputs, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "void set_numOutputs(uint)", asMETHODPR(RenderPathCommand, SetNumOutputs, (unsigned), void), asCALL_THISCALL);
    // void RenderPathCommand::SetOutput(unsigned index, const String& name, CubeMapFace face=FACE_POSITIVE_X) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetOutput(uint, const String&in, CubeMapFace = FACE_POSITIVE_X)", asMETHODPR(RenderPathCommand, SetOutput, (unsigned, const String&, CubeMapFace), void), asCALL_THISCALL);
    // void RenderPathCommand::SetOutputFace(unsigned index, CubeMapFace face) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetOutputFace(uint, CubeMapFace)", asMETHODPR(RenderPathCommand, SetOutputFace, (unsigned, CubeMapFace), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "void set_outputFaces(uint, CubeMapFace)", asMETHODPR(RenderPathCommand, SetOutputFace, (unsigned, CubeMapFace), void), asCALL_THISCALL);
    // void RenderPathCommand::SetOutputName(unsigned index, const String& name) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetOutputName(uint, const String&in)", asMETHODPR(RenderPathCommand, SetOutputName, (unsigned, const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "void set_outputNames(uint, const String&in)", asMETHODPR(RenderPathCommand, SetOutputName, (unsigned, const String&), void), asCALL_THISCALL);
    // void RenderPathCommand::SetShaderParameter(const String& name, const Variant& value) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetShaderParameter(const String&in, const Variant&in)", asMETHODPR(RenderPathCommand, SetShaderParameter, (const String&, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "void set_shaderParameters(const String&in, const Variant&in)", asMETHODPR(RenderPathCommand, SetShaderParameter, (const String&, const Variant&), void), asCALL_THISCALL);
    // void RenderPathCommand::SetTextureName(TextureUnit unit, const String& name) | File: ../Graphics/RenderPath.h
    engine->RegisterObjectMethod("RenderPathCommand", "void SetTextureName(TextureUnit, const String&in)", asMETHODPR(RenderPathCommand, SetTextureName, (TextureUnit, const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("RenderPathCommand", "void set_textureNames(TextureUnit, const String&in)", asMETHODPR(RenderPathCommand, SetTextureName, (TextureUnit, const String&), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("RenderTargetInfo", "void Load(const XMLElement&in)", asMETHODPR(RenderTargetInfo, Load, (const XMLElement&), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("ResourceRef", "bool opEquals(const ResourceRef&in) const", asMETHODPR(ResourceRef, operator==, (const ResourceRef&) const, bool), asCALL_THISCALL);
    // explicit ResourceRef::ResourceRef(StringHash type) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(StringHash)", asFUNCTION(ResourceRef_ResourceRef_StringHash), asCALL_CDECL_OBJFIRST);
    // ResourceRef::ResourceRef(StringHash type, const String& name) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(StringHash, const String&in)", asFUNCTION(ResourceRef_ResourceRef_StringHash_String), asCALL_CDECL_OBJFIRST);
    // ResourceRef::ResourceRef(const String& type, const String& name) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(const String&in, const String&in)", asFUNCTION(ResourceRef_ResourceRef_String_String), asCALL_CDECL_OBJFIRST);
    // ResourceRef::ResourceRef(const char* type, const char* name) | File: ../Core/Variant.h
    // Error: type "const char*" can not automatically bind
    // ResourceRef::ResourceRef(const ResourceRef& rhs)=default | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRef", asBEHAVE_CONSTRUCT, "void f(const ResourceRef&in)", asFUNCTION(ResourceRef_ResourceRef_ResourceRef), asCALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectMethod("ResourceRefList", "bool opEquals(const ResourceRefList&in) const", asMETHODPR(ResourceRefList, operator==, (const ResourceRefList&) const, bool), asCALL_THISCALL);
    // explicit ResourceRefList::ResourceRefList(StringHash type) | File: ../Core/Variant.h
    engine->RegisterObjectBehaviour("ResourceRefList", asBEHAVE_CONSTRUCT, "void f(StringHash)", asFUNCTION(ResourceRefList_ResourceRefList_StringHash), asCALL_CDECL_OBJFIRST);
    // ResourceRefList::ResourceRefList(StringHash type, const StringVector& names) | File: ../Core/Variant.h
    // Error: type "const StringVector&" can not automatically bind
    // ResourceRefList& ResourceRefList::operator=(const ResourceRefList&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ResourceRefList>(engine, "ResourceRefList");
#ifdef REGISTER_MANUAL_PART_ResourceRefList
    REGISTER_MANUAL_PART_ResourceRefList(ResourceRefList, "ResourceRefList")
#endif

}

}
