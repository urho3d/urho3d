// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// explicit Camera::Camera(Context* context) | File: ../Graphics/Camera.h
static Camera* Camera_Camera_Context()
{
    return new Camera(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Camera_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Camera* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// explicit CheckBox::CheckBox(Context* context) | File: ../UI/CheckBox.h
static CheckBox* CheckBox_CheckBox_Context()
{
    return new CheckBox(GetScriptContext());
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* CheckBox_GetChildren_void(CheckBox* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* CheckBox_GetChildren_bool(CheckBox* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* CheckBox_GetChildrenWithTag_String_bool(CheckBox* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* CheckBox_GetTags_void(CheckBox* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void CheckBox_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(CheckBox* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// CascadeParameters::CascadeParameters(float split1, float split2, float split3, float split4, float fadeStart, float biasAutoAdjust=1.0f) | File: ../Graphics/Light.h
static void CascadeParameters_CascadeParameters_float_float_float_float_float_float(CascadeParameters* ptr, float split1, float split2, float split3, float split4, float fadeStart, float biasAutoAdjust=1.0f)
{
    new(ptr) CascadeParameters(split1, split2, split3, split4, fadeStart, biasAutoAdjust);
}

void ASRegisterGenerated_Members_Ca_Cm(asIScriptEngine* engine)
{
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Camera", asBEHAVE_ADDREF, "void f()", asMETHODPR(Camera, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void AllocateNetworkState()", asMETHODPR(Camera, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void ApplyAttributes()", asMETHODPR(Camera, ApplyAttributes, (), void), asCALL_THISCALL);
    // explicit Camera::Camera(Context* context) | File: ../Graphics/Camera.h
    engine->RegisterObjectBehaviour("Camera", asBEHAVE_FACTORY, "Camera@+ f()", asFUNCTION(Camera_Camera_Context), asCALL_CDECL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Camera::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Camera, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "bool GetAnimationEnabled() const", asMETHODPR(Camera, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_animationEnabled() const", asMETHODPR(Camera, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // float Camera::GetAspectRatio() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetAspectRatio() const", asMETHODPR(Camera, GetAspectRatio, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_aspectRatio() const", asMETHODPR(Camera, GetAspectRatio, () const, float), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "Variant GetAttribute(uint) const", asMETHODPR(Camera, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Variant get_attributes(uint) const", asMETHODPR(Camera, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "Variant GetAttribute(const String&in) const", asMETHODPR(Camera, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Camera, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Camera, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Camera, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Camera, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "Variant GetAttributeDefault(uint) const", asMETHODPR(Camera, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Variant get_attributeDefaults(uint) const", asMETHODPR(Camera, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Camera, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Camera::GetAutoAspectRatio() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool GetAutoAspectRatio() const", asMETHODPR(Camera, GetAutoAspectRatio, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_autoAspectRatio() const", asMETHODPR(Camera, GetAutoAspectRatio, () const, bool), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "bool GetBlockEvents() const", asMETHODPR(Camera, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "const String& GetCategory() const", asMETHODPR(Camera, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const String& get_category() const", asMETHODPR(Camera, GetCategory, () const, const String&), asCALL_THISCALL);
    // const Plane& Camera::GetClipPlane() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "const Plane& GetClipPlane() const", asMETHODPR(Camera, GetClipPlane, () const, const Plane&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Plane& get_clipPlane() const", asMETHODPR(Camera, GetClipPlane, () const, const Plane&), asCALL_THISCALL);
    // Vector4 Camera::GetClipPlaneAttr() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Vector4 GetClipPlaneAttr() const", asMETHODPR(Camera, GetClipPlaneAttr, () const, Vector4), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "Component@+ GetComponent(StringHash) const", asMETHODPR(Camera, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    // float Camera::GetDistance(const Vector3& worldPos) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetDistance(const Vector3&in) const", asMETHODPR(Camera, GetDistance, (const Vector3&) const, float), asCALL_THISCALL);
    // float Camera::GetDistanceSquared(const Vector3& worldPos) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetDistanceSquared(const Vector3&in) const", asMETHODPR(Camera, GetDistanceSquared, (const Vector3&) const, float), asCALL_THISCALL);
    // Matrix3x4 Camera::GetEffectiveWorldTransform() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Matrix3x4 GetEffectiveWorldTransform() const", asMETHODPR(Camera, GetEffectiveWorldTransform, () const, Matrix3x4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Matrix3x4 get_effectiveWorldTransform() const", asMETHODPR(Camera, GetEffectiveWorldTransform, () const, Matrix3x4), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "VariantMap& GetEventDataMap() const", asMETHODPR(Camera, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "Object@+ GetEventSender() const", asMETHODPR(Camera, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Quaternion Camera::GetFaceCameraRotation(const Vector3& position, const Quaternion& rotation, FaceCameraMode mode, float minAngle=0.0f) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Quaternion GetFaceCameraRotation(const Vector3&in, const Quaternion&in, FaceCameraMode, float = 0.0f)", asMETHODPR(Camera, GetFaceCameraRotation, (const Vector3&, const Quaternion&, FaceCameraMode, float), Quaternion), asCALL_THISCALL);
    // float Camera::GetFarClip() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetFarClip() const", asMETHODPR(Camera, GetFarClip, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_farClip() const", asMETHODPR(Camera, GetFarClip, () const, float), asCALL_THISCALL);
    // FillMode Camera::GetFillMode() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "FillMode GetFillMode() const", asMETHODPR(Camera, GetFillMode, () const, FillMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "FillMode get_fillMode() const", asMETHODPR(Camera, GetFillMode, () const, FillMode), asCALL_THISCALL);
    // bool Camera::GetFlipVertical() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool GetFlipVertical() const", asMETHODPR(Camera, GetFlipVertical, () const, bool), asCALL_THISCALL);
    // float Camera::GetFov() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetFov() const", asMETHODPR(Camera, GetFov, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_fov() const", asMETHODPR(Camera, GetFov, () const, float), asCALL_THISCALL);
    // const Frustum& Camera::GetFrustum() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "const Frustum& GetFrustum() const", asMETHODPR(Camera, GetFrustum, () const, const Frustum&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Frustum& get_frustum() const", asMETHODPR(Camera, GetFrustum, () const, const Frustum&), asCALL_THISCALL);
    // void Camera::GetFrustumSize(Vector3& near, Vector3& far) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void GetFrustumSize(Vector3&, Vector3&) const", asMETHODPR(Camera, GetFrustumSize, (Vector3&, Vector3&) const, void), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Camera, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Camera, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "const VariantMap& GetGlobalVars() const", asMETHODPR(Camera, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const VariantMap& get_globalVars() const", asMETHODPR(Camera, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // Matrix4 Camera::GetGPUProjection() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Matrix4 GetGPUProjection() const", asMETHODPR(Camera, GetGPUProjection, () const, Matrix4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Matrix4 get_gPUProjection() const", asMETHODPR(Camera, GetGPUProjection, () const, Matrix4), asCALL_THISCALL);
    // float Camera::GetHalfViewSize() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetHalfViewSize() const", asMETHODPR(Camera, GetHalfViewSize, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_halfViewSize() const", asMETHODPR(Camera, GetHalfViewSize, () const, float), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "uint GetID() const", asMETHODPR(Camera, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "uint get_id() const", asMETHODPR(Camera, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Camera, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // float Camera::GetLodBias() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetLodBias() const", asMETHODPR(Camera, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_lodBias() const", asMETHODPR(Camera, GetLodBias, () const, float), asCALL_THISCALL);
    // float Camera::GetLodDistance(float distance, float scale, float bias) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetLodDistance(float, float, float) const", asMETHODPR(Camera, GetLodDistance, (float, float, float) const, float), asCALL_THISCALL);
    // float Camera::GetNearClip() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetNearClip() const", asMETHODPR(Camera, GetNearClip, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_nearClip() const", asMETHODPR(Camera, GetNearClip, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "Node@+ GetNode() const", asMETHODPR(Camera, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Node@+ get_node() const", asMETHODPR(Camera, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "uint GetNumAttributes() const", asMETHODPR(Camera, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "uint get_numAttributes() const", asMETHODPR(Camera, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "uint GetNumNetworkAttributes() const", asMETHODPR(Camera, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Camera, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Camera, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Camera, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float Camera::GetOrthoSize() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetOrthoSize() const", asMETHODPR(Camera, GetOrthoSize, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_orthoSize() const", asMETHODPR(Camera, GetOrthoSize, () const, float), asCALL_THISCALL);
    // Matrix4 Camera::GetProjection() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Matrix4 GetProjection() const", asMETHODPR(Camera, GetProjection, () const, Matrix4), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Matrix4 get_projection() const", asMETHODPR(Camera, GetProjection, () const, Matrix4), asCALL_THISCALL);
    // const Vector2& Camera::GetProjectionOffset() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "const Vector2& GetProjectionOffset() const", asMETHODPR(Camera, GetProjectionOffset, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Vector2& get_projectionOffset() const", asMETHODPR(Camera, GetProjectionOffset, () const, const Vector2&), asCALL_THISCALL);
    // const Plane& Camera::GetReflectionPlane() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "const Plane& GetReflectionPlane() const", asMETHODPR(Camera, GetReflectionPlane, () const, const Plane&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Plane& get_reflectionPlane() const", asMETHODPR(Camera, GetReflectionPlane, () const, const Plane&), asCALL_THISCALL);
    // Vector4 Camera::GetReflectionPlaneAttr() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Vector4 GetReflectionPlaneAttr() const", asMETHODPR(Camera, GetReflectionPlaneAttr, () const, Vector4), asCALL_THISCALL);
    // bool Camera::GetReverseCulling() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool GetReverseCulling() const", asMETHODPR(Camera, GetReverseCulling, () const, bool), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "Scene@+ GetScene() const", asMETHODPR(Camera, GetScene, () const, Scene*), asCALL_THISCALL);
    // Ray Camera::GetScreenRay(float x, float y) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Ray GetScreenRay(float, float) const", asMETHODPR(Camera, GetScreenRay, (float, float) const, Ray), asCALL_THISCALL);
    // Frustum Camera::GetSplitFrustum(float nearClip, float farClip) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Frustum GetSplitFrustum(float, float) const", asMETHODPR(Camera, GetSplitFrustum, (float, float) const, Frustum), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Camera, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "StringHash GetType() const", asMETHODPR(Camera, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "StringHash get_type() const", asMETHODPR(Camera, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "const String& GetTypeName() const", asMETHODPR(Camera, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const String& get_typeName() const", asMETHODPR(Camera, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Camera::GetUseClipping() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool GetUseClipping() const", asMETHODPR(Camera, GetUseClipping, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_useClipping() const", asMETHODPR(Camera, GetUseClipping, () const, bool), asCALL_THISCALL);
    // bool Camera::GetUseReflection() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool GetUseReflection() const", asMETHODPR(Camera, GetUseReflection, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_useReflection() const", asMETHODPR(Camera, GetUseReflection, () const, bool), asCALL_THISCALL);
    // const Matrix3x4& Camera::GetView() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "const Matrix3x4& GetView() const", asMETHODPR(Camera, GetView, () const, const Matrix3x4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Matrix3x4& get_view() const", asMETHODPR(Camera, GetView, () const, const Matrix3x4&), asCALL_THISCALL);
    // unsigned Camera::GetViewMask() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "uint GetViewMask() const", asMETHODPR(Camera, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "uint get_viewMask() const", asMETHODPR(Camera, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // ViewOverrideFlags Camera::GetViewOverrideFlags() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "ViewOverrideFlags GetViewOverrideFlags() const", asMETHODPR(Camera, GetViewOverrideFlags, () const, ViewOverrideFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "ViewOverrideFlags get_viewOverrideFlags() const", asMETHODPR(Camera, GetViewOverrideFlags, () const, ViewOverrideFlags), asCALL_THISCALL);
    // Frustum Camera::GetViewSpaceFrustum() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Frustum GetViewSpaceFrustum() const", asMETHODPR(Camera, GetViewSpaceFrustum, () const, Frustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Frustum get_viewSpaceFrustum() const", asMETHODPR(Camera, GetViewSpaceFrustum, () const, Frustum), asCALL_THISCALL);
    // Frustum Camera::GetViewSpaceSplitFrustum(float nearClip, float farClip) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Frustum GetViewSpaceSplitFrustum(float, float) const", asMETHODPR(Camera, GetViewSpaceSplitFrustum, (float, float) const, Frustum), asCALL_THISCALL);
    // float Camera::GetZoom() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetZoom() const", asMETHODPR(Camera, GetZoom, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_zoom() const", asMETHODPR(Camera, GetZoom, () const, float), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "bool HasEventHandlers() const", asMETHODPR(Camera, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Camera, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Camera, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "bool IsEnabled() const", asMETHODPR(Camera, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_enabled() const", asMETHODPR(Camera, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "bool IsEnabledEffective() const", asMETHODPR(Camera, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_enabledEffective() const", asMETHODPR(Camera, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "bool IsInstanceOf(StringHash) const", asMETHODPR(Camera, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Camera::IsOrthographic() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool IsOrthographic() const", asMETHODPR(Camera, IsOrthographic, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_orthographic() const", asMETHODPR(Camera, IsOrthographic, () const, bool), asCALL_THISCALL);
    // bool Camera::IsProjectionValid() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool IsProjectionValid() const", asMETHODPR(Camera, IsProjectionValid, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "bool IsReplicated() const", asMETHODPR(Camera, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_replicated() const", asMETHODPR(Camera, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool IsTemporary() const", asMETHODPR(Camera, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_temporary() const", asMETHODPR(Camera, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool Load(Deserializer&)", asMETHODPR(Camera, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Camera, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "bool LoadXML(const XMLElement&in)", asMETHODPR(Camera, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "void MarkNetworkUpdate()", asMETHODPR(Camera, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Camera, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Camera, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Camera, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "void OnSetEnabled()", asMETHODPR(Camera, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "void PrepareNetworkUpdate()", asMETHODPR(Camera, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Camera, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Camera, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Camera", "int Refs() const", asMETHODPR(Camera, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "int get_refs() const", asMETHODPR(Camera, Refs, () const, int), asCALL_THISCALL);
    // static void Camera::RegisterObject(Context* context) | File: ../Graphics/Camera.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Camera", asBEHAVE_RELEASE, "void f()", asMETHODPR(Camera, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "void Remove()", asMETHODPR(Camera, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Camera, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void RemoveInstanceDefault()", asMETHODPR(Camera, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void RemoveObjectAnimation()", asMETHODPR(Camera, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void ResetToDefault()", asMETHODPR(Camera, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "bool Save(Serializer&) const", asMETHODPR(Camera, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool SaveDefaultAttributes() const", asMETHODPR(Camera, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "bool SaveJSON(JSONValue&) const", asMETHODPR(Camera, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "bool SaveXML(XMLElement&) const", asMETHODPR(Camera, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // Vector3 Camera::ScreenToWorldPoint(const Vector3& screenPos) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Vector3 ScreenToWorldPoint(const Vector3&in) const", asMETHODPR(Camera, ScreenToWorldPoint, (const Vector3&) const, Vector3), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void SendEvent(StringHash)", asMETHODPR(Camera, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Camera, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetAnimationEnabled(bool)", asMETHODPR(Camera, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_animationEnabled(bool)", asMETHODPR(Camera, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetAnimationTime(float)", asMETHODPR(Camera, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Camera::SetAspectRatio(float aspectRatio) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetAspectRatio(float)", asMETHODPR(Camera, SetAspectRatio, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_aspectRatio(float)", asMETHODPR(Camera, SetAspectRatio, (float), void), asCALL_THISCALL);
    // void Camera::SetAspectRatioInternal(float aspectRatio) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetAspectRatioInternal(float)", asMETHODPR(Camera, SetAspectRatioInternal, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Camera, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Camera, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Camera, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Camera, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Camera, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Camera, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Camera, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Camera::SetAutoAspectRatio(bool enable) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetAutoAspectRatio(bool)", asMETHODPR(Camera, SetAutoAspectRatio, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_autoAspectRatio(bool)", asMETHODPR(Camera, SetAutoAspectRatio, (bool), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void SetBlockEvents(bool)", asMETHODPR(Camera, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Camera::SetClipPlane(const Plane& plane) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetClipPlane(const Plane&in)", asMETHODPR(Camera, SetClipPlane, (const Plane&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_clipPlane(const Plane&in)", asMETHODPR(Camera, SetClipPlane, (const Plane&), void), asCALL_THISCALL);
    // void Camera::SetClipPlaneAttr(const Vector4& value) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetClipPlaneAttr(const Vector4&in)", asMETHODPR(Camera, SetClipPlaneAttr, (const Vector4&), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "void SetEnabled(bool)", asMETHODPR(Camera, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_enabled(bool)", asMETHODPR(Camera, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Camera::SetFarClip(float farClip) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetFarClip(float)", asMETHODPR(Camera, SetFarClip, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_farClip(float)", asMETHODPR(Camera, SetFarClip, (float), void), asCALL_THISCALL);
    // void Camera::SetFillMode(FillMode mode) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetFillMode(FillMode)", asMETHODPR(Camera, SetFillMode, (FillMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_fillMode(FillMode)", asMETHODPR(Camera, SetFillMode, (FillMode), void), asCALL_THISCALL);
    // void Camera::SetFlipVertical(bool enable) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetFlipVertical(bool)", asMETHODPR(Camera, SetFlipVertical, (bool), void), asCALL_THISCALL);
    // void Camera::SetFov(float fov) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetFov(float)", asMETHODPR(Camera, SetFov, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_fov(float)", asMETHODPR(Camera, SetFov, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Camera, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Camera, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void SetInstanceDefault(bool)", asMETHODPR(Camera, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Camera, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Camera::SetLodBias(float bias) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetLodBias(float)", asMETHODPR(Camera, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_lodBias(float)", asMETHODPR(Camera, SetLodBias, (float), void), asCALL_THISCALL);
    // void Camera::SetNearClip(float nearClip) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetNearClip(float)", asMETHODPR(Camera, SetNearClip, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_nearClip(float)", asMETHODPR(Camera, SetNearClip, (float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Camera, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Camera, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Camera, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Camera::SetOrthographic(bool enable) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetOrthographic(bool)", asMETHODPR(Camera, SetOrthographic, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_orthographic(bool)", asMETHODPR(Camera, SetOrthographic, (bool), void), asCALL_THISCALL);
    // void Camera::SetOrthoSize(float orthoSize) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetOrthoSize(float)", asMETHODPR(Camera, SetOrthoSize, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_orthoSize(float)", asMETHODPR(Camera, SetOrthoSize, (float), void), asCALL_THISCALL);
    // void Camera::SetOrthoSize(const Vector2& orthoSize) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetOrthoSize(const Vector2&in)", asMETHODPR(Camera, SetOrthoSize, (const Vector2&), void), asCALL_THISCALL);
    // void Camera::SetOrthoSizeAttr(float orthoSize) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetOrthoSizeAttr(float)", asMETHODPR(Camera, SetOrthoSizeAttr, (float), void), asCALL_THISCALL);
    // void Camera::SetProjection(const Matrix4& projection) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetProjection(const Matrix4&in)", asMETHODPR(Camera, SetProjection, (const Matrix4&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_projection(const Matrix4&in)", asMETHODPR(Camera, SetProjection, (const Matrix4&), void), asCALL_THISCALL);
    // void Camera::SetProjectionOffset(const Vector2& offset) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetProjectionOffset(const Vector2&in)", asMETHODPR(Camera, SetProjectionOffset, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_projectionOffset(const Vector2&in)", asMETHODPR(Camera, SetProjectionOffset, (const Vector2&), void), asCALL_THISCALL);
    // void Camera::SetReflectionPlane(const Plane& plane) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetReflectionPlane(const Plane&in)", asMETHODPR(Camera, SetReflectionPlane, (const Plane&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_reflectionPlane(const Plane&in)", asMETHODPR(Camera, SetReflectionPlane, (const Plane&), void), asCALL_THISCALL);
    // void Camera::SetReflectionPlaneAttr(const Vector4& value) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetReflectionPlaneAttr(const Vector4&in)", asMETHODPR(Camera, SetReflectionPlaneAttr, (const Vector4&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void SetTemporary(bool)", asMETHODPR(Camera, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_temporary(bool)", asMETHODPR(Camera, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Camera::SetUseClipping(bool enable) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetUseClipping(bool)", asMETHODPR(Camera, SetUseClipping, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_useClipping(bool)", asMETHODPR(Camera, SetUseClipping, (bool), void), asCALL_THISCALL);
    // void Camera::SetUseReflection(bool enable) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetUseReflection(bool)", asMETHODPR(Camera, SetUseReflection, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_useReflection(bool)", asMETHODPR(Camera, SetUseReflection, (bool), void), asCALL_THISCALL);
    // void Camera::SetViewMask(unsigned mask) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetViewMask(uint)", asMETHODPR(Camera, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_viewMask(uint)", asMETHODPR(Camera, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Camera::SetViewOverrideFlags(ViewOverrideFlags flags) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetViewOverrideFlags(ViewOverrideFlags)", asMETHODPR(Camera, SetViewOverrideFlags, (ViewOverrideFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_viewOverrideFlags(ViewOverrideFlags)", asMETHODPR(Camera, SetViewOverrideFlags, (ViewOverrideFlags), void), asCALL_THISCALL);
    // void Camera::SetZoom(float zoom) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetZoom(float)", asMETHODPR(Camera, SetZoom, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_zoom(float)", asMETHODPR(Camera, SetZoom, (float), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void UnsubscribeFromAllEvents()", asMETHODPR(Camera, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Camera_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Camera, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Camera, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Camera, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Camera", "int WeakRefs() const", asMETHODPR(Camera, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "int get_weakRefs() const", asMETHODPR(Camera, WeakRefs, () const, int), asCALL_THISCALL);
    // Vector2 Camera::WorldToScreenPoint(const Vector3& worldPos) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Vector2 WorldToScreenPoint(const Vector3&in) const", asMETHODPR(Camera, WorldToScreenPoint, (const Vector3&) const, Vector2), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Camera, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Camera, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Camera, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Camera, "Camera")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Camera, "Camera")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Camera, "Camera")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Camera, "Camera")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Camera, "Camera")
#endif
#ifdef REGISTER_MANUAL_PART_Camera
    REGISTER_MANUAL_PART_Camera(Camera, "Camera")
#endif
    RegisterSubclass<Component, Camera>(engine, "Component", "Camera");
    RegisterSubclass<Animatable, Camera>(engine, "Animatable", "Camera");
    RegisterSubclass<Serializable, Camera>(engine, "Serializable", "Camera");
    RegisterSubclass<Object, Camera>(engine, "Object", "Camera");
    RegisterSubclass<RefCounted, Camera>(engine, "RefCounted", "Camera");

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void AddChild(UIElement@+)", asMETHODPR(CheckBox, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CheckBox", asBEHAVE_ADDREF, "void f()", asMETHODPR(CheckBox, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void AddTag(const String&in)", asMETHODPR(CheckBox, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void AddTags(const String&in, int8 = ';')", asMETHODPR(CheckBox, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void AdjustScissor(IntRect&)", asMETHODPR(CheckBox, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void AllocateNetworkState()", asMETHODPR(CheckBox, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void ApplyAttributes()", asMETHODPR(CheckBox, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void BringToFront()", asMETHODPR(CheckBox, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // explicit CheckBox::CheckBox(Context* context) | File: ../UI/CheckBox.h
    engine->RegisterObjectBehaviour("CheckBox", asBEHAVE_FACTORY, "CheckBox@+ f()", asFUNCTION(CheckBox_CheckBox_Context), asCALL_CDECL);
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(CheckBox, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void DisableLayoutUpdate()", asMETHODPR(CheckBox, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(CheckBox, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void EnableLayoutUpdate()", asMETHODPR(CheckBox, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool FilterAttributes(XMLElement&) const", asMETHODPR(CheckBox, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "uint FindChild(UIElement@+) const", asMETHODPR(CheckBox, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "bool GetAnimationEnabled() const", asMETHODPR(CheckBox, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_animationEnabled() const", asMETHODPR(CheckBox, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const String& GetAppliedStyle() const", asMETHODPR(CheckBox, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const String& get_style() const", asMETHODPR(CheckBox, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "Variant GetAttribute(uint) const", asMETHODPR(CheckBox, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "Variant get_attributes(uint) const", asMETHODPR(CheckBox, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "Variant GetAttribute(const String&in) const", asMETHODPR(CheckBox, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(CheckBox, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(CheckBox, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(CheckBox, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(CheckBox, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "Variant GetAttributeDefault(uint) const", asMETHODPR(CheckBox, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "Variant get_attributeDefaults(uint) const", asMETHODPR(CheckBox, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(CheckBox, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void CheckBox::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/CheckBox.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "BlendMode GetBlendMode() const", asMETHODPR(CheckBox, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "BlendMode get_blendMode() const", asMETHODPR(CheckBox, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "bool GetBlockEvents() const", asMETHODPR(CheckBox, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "const IntRect& GetBorder() const", asMETHODPR(CheckBox, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntRect& get_border() const", asMETHODPR(CheckBox, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool GetBringToBack() const", asMETHODPR(CheckBox, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_bringToBack() const", asMETHODPR(CheckBox, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool GetBringToFront() const", asMETHODPR(CheckBox, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_bringToFront() const", asMETHODPR(CheckBox, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "const String& GetCategory() const", asMETHODPR(CheckBox, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const String& get_category() const", asMETHODPR(CheckBox, GetCategory, () const, const String&), asCALL_THISCALL);
    // const IntVector2& CheckBox::GetCheckedOffset() const | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetCheckedOffset() const", asMETHODPR(CheckBox, GetCheckedOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_checkedOffset() const", asMETHODPR(CheckBox, GetCheckedOffset, () const, const IntVector2&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ GetChild(uint) const", asMETHODPR(CheckBox, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ get_children(uint) const", asMETHODPR(CheckBox, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(CheckBox, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(CheckBox, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetChildOffset() const", asMETHODPR(CheckBox, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_childOffset() const", asMETHODPR(CheckBox, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "Array<UIElement@>@ GetChildren() const", asFUNCTION(CheckBox_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(CheckBox_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(CheckBox_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntRect& GetClipBorder() const", asMETHODPR(CheckBox, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntRect& get_clipBorder() const", asMETHODPR(CheckBox, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool GetClipChildren() const", asMETHODPR(CheckBox, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_clipChildren() const", asMETHODPR(CheckBox, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Color& GetColor(Corner) const", asMETHODPR(CheckBox, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const Color& get_colors(Corner) const", asMETHODPR(CheckBox, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Color& GetColorAttr() const", asMETHODPR(CheckBox, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "IntRect GetCombinedScreenRect()", asMETHODPR(CheckBox, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "IntRect get_combinedScreenRect()", asMETHODPR(CheckBox, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(CheckBox, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Color& GetDerivedColor() const", asMETHODPR(CheckBox, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "float GetDerivedOpacity() const", asMETHODPR(CheckBox, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "float get_derivedOpacity() const", asMETHODPR(CheckBox, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetDisabledOffset() const", asMETHODPR(CheckBox, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_disabledOffset() const", asMETHODPR(CheckBox, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(CheckBox, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(CheckBox, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "uint GetDragButtonCount() const", asMETHODPR(CheckBox, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "uint get_dragButtonCount() const", asMETHODPR(CheckBox, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(CheckBox, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(CheckBox, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(CheckBox, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ GetElementEventSender() const", asMETHODPR(CheckBox, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool GetEnableAnchor() const", asMETHODPR(CheckBox, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_enableAnchor() const", asMETHODPR(CheckBox, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "VariantMap& GetEventDataMap() const", asMETHODPR(CheckBox, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "Object@+ GetEventSender() const", asMETHODPR(CheckBox, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "FocusMode GetFocusMode() const", asMETHODPR(CheckBox, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "FocusMode get_focusMode() const", asMETHODPR(CheckBox, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(CheckBox, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const Variant& get_globalVar(StringHash) const", asMETHODPR(CheckBox, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "const VariantMap& GetGlobalVars() const", asMETHODPR(CheckBox, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const VariantMap& get_globalVars() const", asMETHODPR(CheckBox, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetHeight() const", asMETHODPR(CheckBox, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_height() const", asMETHODPR(CheckBox, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(CheckBox, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(CheckBox, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetHoverOffset() const", asMETHODPR(CheckBox, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_hoverOffset() const", asMETHODPR(CheckBox, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "const IntRect& GetImageBorder() const", asMETHODPR(CheckBox, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntRect& get_imageBorder() const", asMETHODPR(CheckBox, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "const IntRect& GetImageRect() const", asMETHODPR(CheckBox, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntRect& get_imageRect() const", asMETHODPR(CheckBox, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetIndent() const", asMETHODPR(CheckBox, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_indent() const", asMETHODPR(CheckBox, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetIndentSpacing() const", asMETHODPR(CheckBox, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_indentSpacing() const", asMETHODPR(CheckBox, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetIndentWidth() const", asMETHODPR(CheckBox, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_indentWidth() const", asMETHODPR(CheckBox, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(CheckBox, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntRect& GetLayoutBorder() const", asMETHODPR(CheckBox, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntRect& get_layoutBorder() const", asMETHODPR(CheckBox, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetLayoutElementMaxSize() const", asMETHODPR(CheckBox, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(CheckBox, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const Vector2& get_layoutFlexScale() const", asMETHODPR(CheckBox, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "LayoutMode GetLayoutMode() const", asMETHODPR(CheckBox, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "LayoutMode get_layoutMode() const", asMETHODPR(CheckBox, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetLayoutSpacing() const", asMETHODPR(CheckBox, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_layoutSpacing() const", asMETHODPR(CheckBox, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "Material@+ GetMaterial() const", asMETHODPR(CheckBox, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "Material@+ get_material() const", asMETHODPR(CheckBox, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "ResourceRef GetMaterialAttr() const", asMETHODPR(CheckBox, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Vector2& GetMaxAnchor() const", asMETHODPR(CheckBox, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const Vector2& get_maxAnchor() const", asMETHODPR(CheckBox, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetMaxHeight() const", asMETHODPR(CheckBox, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_maxHeight() const", asMETHODPR(CheckBox, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetMaxOffset() const", asMETHODPR(CheckBox, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_maxOffset() const", asMETHODPR(CheckBox, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetMaxSize() const", asMETHODPR(CheckBox, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_maxSize() const", asMETHODPR(CheckBox, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetMaxWidth() const", asMETHODPR(CheckBox, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_maxWidth() const", asMETHODPR(CheckBox, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Vector2& GetMinAnchor() const", asMETHODPR(CheckBox, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const Vector2& get_minAnchor() const", asMETHODPR(CheckBox, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetMinHeight() const", asMETHODPR(CheckBox, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_minHeight() const", asMETHODPR(CheckBox, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetMinOffset() const", asMETHODPR(CheckBox, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_minOffset() const", asMETHODPR(CheckBox, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetMinSize() const", asMETHODPR(CheckBox, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_minSize() const", asMETHODPR(CheckBox, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetMinWidth() const", asMETHODPR(CheckBox, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_minWidth() const", asMETHODPR(CheckBox, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const String& GetName() const", asMETHODPR(CheckBox, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const String& get_name() const", asMETHODPR(CheckBox, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "uint GetNumAttributes() const", asMETHODPR(CheckBox, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "uint get_numAttributes() const", asMETHODPR(CheckBox, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "uint GetNumChildren(bool = false) const", asMETHODPR(CheckBox, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "uint get_numChildren(bool = false) const", asMETHODPR(CheckBox, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "uint GetNumNetworkAttributes() const", asMETHODPR(CheckBox, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(CheckBox, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(CheckBox, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(CheckBox, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "float GetOpacity() const", asMETHODPR(CheckBox, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "float get_opacity() const", asMETHODPR(CheckBox, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ GetParent() const", asMETHODPR(CheckBox, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ get_parent() const", asMETHODPR(CheckBox, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Vector2& GetPivot() const", asMETHODPR(CheckBox, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const Vector2& get_pivot() const", asMETHODPR(CheckBox, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetPosition() const", asMETHODPR(CheckBox, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_position() const", asMETHODPR(CheckBox, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetPriority() const", asMETHODPR(CheckBox, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_priority() const", asMETHODPR(CheckBox, GetPriority, () const, int), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ GetRoot() const", asMETHODPR(CheckBox, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ get_root() const", asMETHODPR(CheckBox, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetScreenPosition() const", asMETHODPR(CheckBox, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_screenPosition() const", asMETHODPR(CheckBox, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetSize() const", asMETHODPR(CheckBox, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_size() const", asMETHODPR(CheckBox, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool GetSortChildren() const", asMETHODPR(CheckBox, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_sortChildren() const", asMETHODPR(CheckBox, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(CheckBox, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "Array<String>@ GetTags() const", asFUNCTION(CheckBox_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("CheckBox", "Array<String>@ get_tags() const", asFUNCTION(CheckBox_GetTags_void), asCALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "Texture@+ GetTexture() const", asMETHODPR(CheckBox, GetTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "Texture@+ get_texture() const", asMETHODPR(CheckBox, GetTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "ResourceRef GetTextureAttr() const", asMETHODPR(CheckBox, GetTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "TraversalMode GetTraversalMode() const", asMETHODPR(CheckBox, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "TraversalMode get_traversalMode() const", asMETHODPR(CheckBox, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "StringHash GetType() const", asMETHODPR(CheckBox, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "StringHash get_type() const", asMETHODPR(CheckBox, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "const String& GetTypeName() const", asMETHODPR(CheckBox, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const String& get_typeName() const", asMETHODPR(CheckBox, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool GetUseDerivedOpacity() const", asMETHODPR(CheckBox, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_useDerivedOpacity() const", asMETHODPR(CheckBox, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(CheckBox, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const VariantMap& GetVars() const", asMETHODPR(CheckBox, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(CheckBox, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(CheckBox, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetWidth() const", asMETHODPR(CheckBox, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_width() const", asMETHODPR(CheckBox, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool HasColorGradient() const", asMETHODPR(CheckBox, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_colorGradient() const", asMETHODPR(CheckBox, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "bool HasEventHandlers() const", asMETHODPR(CheckBox, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool HasFocus() const", asMETHODPR(CheckBox, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_focus() const", asMETHODPR(CheckBox, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(CheckBox, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(CheckBox, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool HasTag(const String&in) const", asMETHODPR(CheckBox, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void InsertChild(uint, UIElement@+)", asMETHODPR(CheckBox, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool CheckBox::IsChecked() const | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "bool IsChecked() const", asMETHODPR(CheckBox, IsChecked, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_checked() const", asMETHODPR(CheckBox, IsChecked, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsChildOf(UIElement@+) const", asMETHODPR(CheckBox, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsEditable() const", asMETHODPR(CheckBox, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_editable() const", asMETHODPR(CheckBox, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsElementEventSender() const", asMETHODPR(CheckBox, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_elementEventSender() const", asMETHODPR(CheckBox, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsEnabled() const", asMETHODPR(CheckBox, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_enabled() const", asMETHODPR(CheckBox, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsEnabledSelf() const", asMETHODPR(CheckBox, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_enabledSelf() const", asMETHODPR(CheckBox, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsFixedHeight() const", asMETHODPR(CheckBox, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_fixedHeight() const", asMETHODPR(CheckBox, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsFixedSize() const", asMETHODPR(CheckBox, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_fixedSize() const", asMETHODPR(CheckBox, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsFixedWidth() const", asMETHODPR(CheckBox, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_fixedWidth() const", asMETHODPR(CheckBox, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsHovering() const", asMETHODPR(CheckBox, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_hovering() const", asMETHODPR(CheckBox, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsInside(IntVector2, bool)", asMETHODPR(CheckBox, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(CheckBox, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "bool IsInstanceOf(StringHash) const", asMETHODPR(CheckBox, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsInternal() const", asMETHODPR(CheckBox, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_internal() const", asMETHODPR(CheckBox, IsInternal, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsSelected() const", asMETHODPR(CheckBox, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_selected() const", asMETHODPR(CheckBox, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool IsTemporary() const", asMETHODPR(CheckBox, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_temporary() const", asMETHODPR(CheckBox, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "bool IsTiled() const", asMETHODPR(CheckBox, IsTiled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_tiled() const", asMETHODPR(CheckBox, IsTiled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsVisible() const", asMETHODPR(CheckBox, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_visible() const", asMETHODPR(CheckBox, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsVisibleEffective() const", asMETHODPR(CheckBox, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_visibleEffective() const", asMETHODPR(CheckBox, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsWheelHandler() const", asMETHODPR(CheckBox, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(CheckBox, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool Load(Deserializer&)", asMETHODPR(CheckBox, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(CheckBox, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "bool LoadJSON(const JSONValue&in)", asMETHODPR(CheckBox, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool LoadXML(const XMLElement&in)", asMETHODPR(CheckBox, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(CheckBox, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool LoadXML(Deserializer&)", asMETHODPR(CheckBox, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void MarkNetworkUpdate()", asMETHODPR(CheckBox, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // void CheckBox::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(CheckBox, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(CheckBox, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(CheckBox, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(CheckBox, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(CheckBox, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(CheckBox, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool OnDragDropTest(UIElement@+)", asMETHODPR(CheckBox, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(CheckBox, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(CheckBox, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(CheckBox, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(CheckBox, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(CheckBox, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnIndentSet()", asMETHODPR(CheckBox, OnIndentSet, (), void), asCALL_THISCALL);
    // void CheckBox::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(CheckBox, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnPositionSet(const IntVector2&in)", asMETHODPR(CheckBox, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(CheckBox, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(CheckBox, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnSetEditable()", asMETHODPR(CheckBox, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnTextInput(const String&in)", asMETHODPR(CheckBox, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(CheckBox, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(CheckBox, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(CheckBox, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CheckBox", "int Refs() const", asMETHODPR(CheckBox, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_refs() const", asMETHODPR(CheckBox, Refs, () const, int), asCALL_THISCALL);
    // static void CheckBox::RegisterObject(Context* context) | File: ../UI/CheckBox.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CheckBox", asBEHAVE_RELEASE, "void f()", asMETHODPR(CheckBox, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void Remove()", asMETHODPR(CheckBox, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveAllChildren()", asMETHODPR(CheckBox, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveAllTags()", asMETHODPR(CheckBox, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(CheckBox, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(CheckBox, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveChildAtIndex(uint)", asMETHODPR(CheckBox, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveInstanceDefault()", asMETHODPR(CheckBox, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveObjectAnimation()", asMETHODPR(CheckBox, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool RemoveTag(const String&in)", asMETHODPR(CheckBox, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void ResetDeepEnabled()", asMETHODPR(CheckBox, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void ResetToDefault()", asMETHODPR(CheckBox, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool Save(Serializer&) const", asMETHODPR(CheckBox, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool SaveDefaultAttributes() const", asMETHODPR(CheckBox, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "bool SaveJSON(JSONValue&) const", asMETHODPR(CheckBox, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool SaveXML(XMLElement&) const", asMETHODPR(CheckBox, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(CheckBox, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(CheckBox, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void SendEvent(StringHash)", asMETHODPR(CheckBox, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(CheckBox, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(CheckBox, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetAnimationEnabled(bool)", asMETHODPR(CheckBox, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_animationEnabled(bool)", asMETHODPR(CheckBox, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetAnimationTime(float)", asMETHODPR(CheckBox, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(CheckBox, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool set_attributes(uint, const Variant&in)", asMETHODPR(CheckBox, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(CheckBox, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(CheckBox, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(CheckBox, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(CheckBox, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(CheckBox, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetBlendMode(BlendMode)", asMETHODPR(CheckBox, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_blendMode(BlendMode)", asMETHODPR(CheckBox, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void SetBlockEvents(bool)", asMETHODPR(CheckBox, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetBorder(const IntRect&in)", asMETHODPR(CheckBox, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_border(const IntRect&in)", asMETHODPR(CheckBox, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetBringToBack(bool)", asMETHODPR(CheckBox, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_bringToBack(bool)", asMETHODPR(CheckBox, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetBringToFront(bool)", asMETHODPR(CheckBox, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_bringToFront(bool)", asMETHODPR(CheckBox, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void CheckBox::SetChecked(bool enable) | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "void SetChecked(bool)", asMETHODPR(CheckBox, SetChecked, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_checked(bool)", asMETHODPR(CheckBox, SetChecked, (bool), void), asCALL_THISCALL);
    // void CheckBox::SetCheckedOffset(const IntVector2& offset) | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "void SetCheckedOffset(const IntVector2&in)", asMETHODPR(CheckBox, SetCheckedOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_checkedOffset(const IntVector2&in)", asMETHODPR(CheckBox, SetCheckedOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void CheckBox::SetCheckedOffset(int x, int y) | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "void SetCheckedOffset(int, int)", asMETHODPR(CheckBox, SetCheckedOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetChildOffset(const IntVector2&in)", asMETHODPR(CheckBox, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetClipBorder(const IntRect&in)", asMETHODPR(CheckBox, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_clipBorder(const IntRect&in)", asMETHODPR(CheckBox, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetClipChildren(bool)", asMETHODPR(CheckBox, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_clipChildren(bool)", asMETHODPR(CheckBox, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetColor(const Color&in)", asMETHODPR(CheckBox, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_color(const Color&in)", asMETHODPR(CheckBox, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetColor(Corner, const Color&in)", asMETHODPR(CheckBox, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_colors(Corner, const Color&in)", asMETHODPR(CheckBox, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetDeepEnabled(bool)", asMETHODPR(CheckBox, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(CheckBox, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_defaultStyle(XMLFile@+)", asMETHODPR(CheckBox, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetDisabledOffset(const IntVector2&in)", asMETHODPR(CheckBox, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_disabledOffset(const IntVector2&in)", asMETHODPR(CheckBox, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetDisabledOffset(int, int)", asMETHODPR(CheckBox, SetDisabledOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(CheckBox, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(CheckBox, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetEditable(bool)", asMETHODPR(CheckBox, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_editable(bool)", asMETHODPR(CheckBox, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetElementEventSender(bool)", asMETHODPR(CheckBox, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_elementEventSender(bool)", asMETHODPR(CheckBox, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetEnableAnchor(bool)", asMETHODPR(CheckBox, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_enableAnchor(bool)", asMETHODPR(CheckBox, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetEnabled(bool)", asMETHODPR(CheckBox, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_enabled(bool)", asMETHODPR(CheckBox, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetEnabledRecursive(bool)", asMETHODPR(CheckBox, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetFixedHeight(int)", asMETHODPR(CheckBox, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetFixedSize(const IntVector2&in)", asMETHODPR(CheckBox, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetFixedSize(int, int)", asMETHODPR(CheckBox, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetFixedWidth(int)", asMETHODPR(CheckBox, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetFocus(bool)", asMETHODPR(CheckBox, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_focus(bool)", asMETHODPR(CheckBox, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetFocusMode(FocusMode)", asMETHODPR(CheckBox, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_focusMode(FocusMode)", asMETHODPR(CheckBox, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetFullImageRect()", asMETHODPR(CheckBox, SetFullImageRect, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(CheckBox, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(CheckBox, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetHeight(int)", asMETHODPR(CheckBox, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_height(int)", asMETHODPR(CheckBox, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(CheckBox, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(CheckBox, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetHovering(bool)", asMETHODPR(CheckBox, SetHovering, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetHoverOffset(const IntVector2&in)", asMETHODPR(CheckBox, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_hoverOffset(const IntVector2&in)", asMETHODPR(CheckBox, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetHoverOffset(int, int)", asMETHODPR(CheckBox, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetImageBorder(const IntRect&in)", asMETHODPR(CheckBox, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_imageBorder(const IntRect&in)", asMETHODPR(CheckBox, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetImageRect(const IntRect&in)", asMETHODPR(CheckBox, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_imageRect(const IntRect&in)", asMETHODPR(CheckBox, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetIndent(int)", asMETHODPR(CheckBox, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_indent(int)", asMETHODPR(CheckBox, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetIndentSpacing(int)", asMETHODPR(CheckBox, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_indentSpacing(int)", asMETHODPR(CheckBox, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void SetInstanceDefault(bool)", asMETHODPR(CheckBox, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(CheckBox, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetInternal(bool)", asMETHODPR(CheckBox, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_internal(bool)", asMETHODPR(CheckBox, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(CheckBox, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(CheckBox, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_layoutBorder(const IntRect&in)", asMETHODPR(CheckBox, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(CheckBox, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(CheckBox, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetLayoutMode(LayoutMode)", asMETHODPR(CheckBox, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_layoutMode(LayoutMode)", asMETHODPR(CheckBox, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetLayoutSpacing(int)", asMETHODPR(CheckBox, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_layoutSpacing(int)", asMETHODPR(CheckBox, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaterial(Material@+)", asMETHODPR(CheckBox, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_material(Material@+)", asMETHODPR(CheckBox, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(CheckBox, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(CheckBox, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_maxAnchor(const Vector2&in)", asMETHODPR(CheckBox, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxAnchor(float, float)", asMETHODPR(CheckBox, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxHeight(int)", asMETHODPR(CheckBox, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_maxHeight(int)", asMETHODPR(CheckBox, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(CheckBox, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_maxOffset(const IntVector2&in)", asMETHODPR(CheckBox, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxSize(const IntVector2&in)", asMETHODPR(CheckBox, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_maxSize(const IntVector2&in)", asMETHODPR(CheckBox, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxSize(int, int)", asMETHODPR(CheckBox, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxWidth(int)", asMETHODPR(CheckBox, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_maxWidth(int)", asMETHODPR(CheckBox, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinAnchor(const Vector2&in)", asMETHODPR(CheckBox, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_minAnchor(const Vector2&in)", asMETHODPR(CheckBox, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinAnchor(float, float)", asMETHODPR(CheckBox, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinHeight(int)", asMETHODPR(CheckBox, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_minHeight(int)", asMETHODPR(CheckBox, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinOffset(const IntVector2&in)", asMETHODPR(CheckBox, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_minOffset(const IntVector2&in)", asMETHODPR(CheckBox, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinSize(const IntVector2&in)", asMETHODPR(CheckBox, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_minSize(const IntVector2&in)", asMETHODPR(CheckBox, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinSize(int, int)", asMETHODPR(CheckBox, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinWidth(int)", asMETHODPR(CheckBox, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_minWidth(int)", asMETHODPR(CheckBox, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetName(const String&in)", asMETHODPR(CheckBox, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_name(const String&in)", asMETHODPR(CheckBox, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(CheckBox, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(CheckBox, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(CheckBox, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetOpacity(float)", asMETHODPR(CheckBox, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_opacity(float)", asMETHODPR(CheckBox, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(CheckBox, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetPivot(const Vector2&in)", asMETHODPR(CheckBox, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_pivot(const Vector2&in)", asMETHODPR(CheckBox, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetPivot(float, float)", asMETHODPR(CheckBox, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetPosition(const IntVector2&in)", asMETHODPR(CheckBox, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_position(const IntVector2&in)", asMETHODPR(CheckBox, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetPosition(int, int)", asMETHODPR(CheckBox, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetPriority(int)", asMETHODPR(CheckBox, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_priority(int)", asMETHODPR(CheckBox, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetRenderTexture(Texture2D@+)", asMETHODPR(CheckBox, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetSelected(bool)", asMETHODPR(CheckBox, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_selected(bool)", asMETHODPR(CheckBox, SetSelected, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetSize(const IntVector2&in)", asMETHODPR(CheckBox, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_size(const IntVector2&in)", asMETHODPR(CheckBox, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetSize(int, int)", asMETHODPR(CheckBox, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetSortChildren(bool)", asMETHODPR(CheckBox, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_sortChildren(bool)", asMETHODPR(CheckBox, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(CheckBox, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool SetStyle(const XMLElement&in)", asMETHODPR(CheckBox, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(CheckBox, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void SetTemporary(bool)", asMETHODPR(CheckBox, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_temporary(bool)", asMETHODPR(CheckBox, SetTemporary, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetTexture(Texture@+)", asMETHODPR(CheckBox, SetTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_texture(Texture@+)", asMETHODPR(CheckBox, SetTexture, (Texture*), void), asCALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetTextureAttr(const ResourceRef&in)", asMETHODPR(CheckBox, SetTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetTiled(bool)", asMETHODPR(CheckBox, SetTiled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_tiled(bool)", asMETHODPR(CheckBox, SetTiled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetTraversalMode(TraversalMode)", asMETHODPR(CheckBox, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_traversalMode(TraversalMode)", asMETHODPR(CheckBox, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetUseDerivedOpacity(bool)", asMETHODPR(CheckBox, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_useDerivedOpacity(bool)", asMETHODPR(CheckBox, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetVar(StringHash, const Variant&in)", asMETHODPR(CheckBox, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(CheckBox, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(CheckBox, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetVisible(bool)", asMETHODPR(CheckBox, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_visible(bool)", asMETHODPR(CheckBox, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetWidth(int)", asMETHODPR(CheckBox, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_width(int)", asMETHODPR(CheckBox, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SortChildren()", asMETHODPR(CheckBox, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void UnsubscribeFromAllEvents()", asMETHODPR(CheckBox, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(CheckBox_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(CheckBox, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(CheckBox, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(CheckBox, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void Update(float)", asMETHODPR(CheckBox, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void UpdateLayout()", asMETHODPR(CheckBox, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CheckBox", "int WeakRefs() const", asMETHODPR(CheckBox, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_weakRefs() const", asMETHODPR(CheckBox, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(CheckBox, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(CheckBox, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(CheckBox, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_BorderImage
    REGISTER_MANUAL_PART_BorderImage(CheckBox, "CheckBox")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(CheckBox, "CheckBox")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(CheckBox, "CheckBox")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(CheckBox, "CheckBox")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(CheckBox, "CheckBox")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(CheckBox, "CheckBox")
#endif
#ifdef REGISTER_MANUAL_PART_CheckBox
    REGISTER_MANUAL_PART_CheckBox(CheckBox, "CheckBox")
#endif
    RegisterSubclass<BorderImage, CheckBox>(engine, "BorderImage", "CheckBox");
    RegisterSubclass<UIElement, CheckBox>(engine, "UIElement", "CheckBox");
    RegisterSubclass<Animatable, CheckBox>(engine, "Animatable", "CheckBox");
    RegisterSubclass<Serializable, CheckBox>(engine, "Serializable", "CheckBox");
    RegisterSubclass<Object, CheckBox>(engine, "Object", "CheckBox");
    RegisterSubclass<RefCounted, CheckBox>(engine, "RefCounted", "CheckBox");

    // float CascadeParameters::biasAutoAdjust_ | File: ../Graphics/Light.h
    engine->RegisterObjectProperty("CascadeParameters", "float biasAutoAdjust", offsetof(CascadeParameters, biasAutoAdjust_));
    // float CascadeParameters::fadeStart_ | File: ../Graphics/Light.h
    engine->RegisterObjectProperty("CascadeParameters", "float fadeStart", offsetof(CascadeParameters, fadeStart_));
    // Vector4 CascadeParameters::splits_ | File: ../Graphics/Light.h
    engine->RegisterObjectProperty("CascadeParameters", "Vector4 splits", offsetof(CascadeParameters, splits_));
    // CascadeParameters::CascadeParameters(float split1, float split2, float split3, float split4, float fadeStart, float biasAutoAdjust=1.0f) | File: ../Graphics/Light.h
    engine->RegisterObjectBehaviour("CascadeParameters", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float = 1.0f)", asFUNCTION(CascadeParameters_CascadeParameters_float_float_float_float_float_float), asCALL_CDECL_OBJFIRST);
    // float CascadeParameters::GetShadowRange() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("CascadeParameters", "float GetShadowRange() const", asMETHODPR(CascadeParameters, GetShadowRange, () const, float), asCALL_THISCALL);
    // void CascadeParameters::Validate() | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("CascadeParameters", "void Validate()", asMETHODPR(CascadeParameters, Validate, (), void), asCALL_THISCALL);
    // CascadeParameters& CascadeParameters::operator=(const CascadeParameters&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<CascadeParameters>(engine, "CascadeParameters");
#ifdef REGISTER_MANUAL_PART_CascadeParameters
    REGISTER_MANUAL_PART_CascadeParameters(CascadeParameters, "CascadeParameters")
#endif

    // Vector2 CharLocation::position_ | File: ../UI/Text.h
    engine->RegisterObjectProperty("CharLocation", "Vector2 position", offsetof(CharLocation, position_));
    // Vector2 CharLocation::size_ | File: ../UI/Text.h
    engine->RegisterObjectProperty("CharLocation", "Vector2 size", offsetof(CharLocation, size_));
    // CharLocation& CharLocation::operator=(const CharLocation&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<CharLocation>(engine, "CharLocation");
#ifdef REGISTER_MANUAL_PART_CharLocation
    REGISTER_MANUAL_PART_CharLocation(CharLocation, "CharLocation")
#endif

}

}
