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
static void Camera_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Camera* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void CheckBox_AddTags_StringVector(CheckBox* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
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

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void CheckBox_SetTags_StringVector(CheckBox* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void CheckBox_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(CheckBox* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// CascadeParameters::CascadeParameters(float split1, float split2, float split3, float split4, float fadeStart, float biasAutoAdjust=1.0f) | File: ../Graphics/Light.h
static void CascadeParameters_CascadeParameters_float_float_float_float_float_float(CascadeParameters* ptr, float split1, float split2, float split3, float split4, float fadeStart, float biasAutoAdjust=1.0f)
{
    new(ptr) CascadeParameters(split1, split2, split3, split4, fadeStart, biasAutoAdjust);
}

void ASRegisterGenerated_Members_Ca_Cm(asIScriptEngine* engine)
{
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Camera", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Camera, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void AllocateNetworkState()", AS_METHODPR(Camera, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void ApplyAttributes()", AS_METHODPR(Camera, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // explicit Camera::Camera(Context* context) | File: ../Graphics/Camera.h
    engine->RegisterObjectBehaviour("Camera", asBEHAVE_FACTORY, "Camera@+ f()", AS_FUNCTION(Camera_Camera_Context), AS_CALL_CDECL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Camera::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Camera, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "bool GetAnimationEnabled() const", AS_METHODPR(Camera, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_animationEnabled() const", AS_METHODPR(Camera, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // float Camera::GetAspectRatio() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetAspectRatio() const", AS_METHODPR(Camera, GetAspectRatio, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_aspectRatio() const", AS_METHODPR(Camera, GetAspectRatio, () const, float), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "Variant GetAttribute(uint) const", AS_METHODPR(Camera, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Variant get_attributes(uint) const", AS_METHODPR(Camera, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "Variant GetAttribute(const String&in) const", AS_METHODPR(Camera, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Camera, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Camera, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Camera, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Camera, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Camera, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Camera, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Camera, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Camera::GetAutoAspectRatio() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool GetAutoAspectRatio() const", AS_METHODPR(Camera, GetAutoAspectRatio, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_autoAspectRatio() const", AS_METHODPR(Camera, GetAutoAspectRatio, () const, bool), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "bool GetBlockEvents() const", AS_METHODPR(Camera, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "const String& GetCategory() const", AS_METHODPR(Camera, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const String& get_category() const", AS_METHODPR(Camera, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // const Plane& Camera::GetClipPlane() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "const Plane& GetClipPlane() const", AS_METHODPR(Camera, GetClipPlane, () const, const Plane&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Plane& get_clipPlane() const", AS_METHODPR(Camera, GetClipPlane, () const, const Plane&), AS_CALL_THISCALL);
    // Vector4 Camera::GetClipPlaneAttr() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Vector4 GetClipPlaneAttr() const", AS_METHODPR(Camera, GetClipPlaneAttr, () const, Vector4), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Camera, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    // float Camera::GetDistance(const Vector3& worldPos) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetDistance(const Vector3&in) const", AS_METHODPR(Camera, GetDistance, (const Vector3&) const, float), AS_CALL_THISCALL);
    // float Camera::GetDistanceSquared(const Vector3& worldPos) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetDistanceSquared(const Vector3&in) const", AS_METHODPR(Camera, GetDistanceSquared, (const Vector3&) const, float), AS_CALL_THISCALL);
    // Matrix3x4 Camera::GetEffectiveWorldTransform() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Matrix3x4 GetEffectiveWorldTransform() const", AS_METHODPR(Camera, GetEffectiveWorldTransform, () const, Matrix3x4), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Matrix3x4 get_effectiveWorldTransform() const", AS_METHODPR(Camera, GetEffectiveWorldTransform, () const, Matrix3x4), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "VariantMap& GetEventDataMap() const", AS_METHODPR(Camera, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "Object@+ GetEventSender() const", AS_METHODPR(Camera, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Quaternion Camera::GetFaceCameraRotation(const Vector3& position, const Quaternion& rotation, FaceCameraMode mode, float minAngle=0.0f) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Quaternion GetFaceCameraRotation(const Vector3&in, const Quaternion&in, FaceCameraMode, float = 0.0f)", AS_METHODPR(Camera, GetFaceCameraRotation, (const Vector3&, const Quaternion&, FaceCameraMode, float), Quaternion), AS_CALL_THISCALL);
    // float Camera::GetFarClip() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetFarClip() const", AS_METHODPR(Camera, GetFarClip, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_farClip() const", AS_METHODPR(Camera, GetFarClip, () const, float), AS_CALL_THISCALL);
    // FillMode Camera::GetFillMode() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "FillMode GetFillMode() const", AS_METHODPR(Camera, GetFillMode, () const, FillMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "FillMode get_fillMode() const", AS_METHODPR(Camera, GetFillMode, () const, FillMode), AS_CALL_THISCALL);
    // bool Camera::GetFlipVertical() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool GetFlipVertical() const", AS_METHODPR(Camera, GetFlipVertical, () const, bool), AS_CALL_THISCALL);
    // float Camera::GetFov() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetFov() const", AS_METHODPR(Camera, GetFov, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_fov() const", AS_METHODPR(Camera, GetFov, () const, float), AS_CALL_THISCALL);
    // const Frustum& Camera::GetFrustum() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "const Frustum& GetFrustum() const", AS_METHODPR(Camera, GetFrustum, () const, const Frustum&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Frustum& get_frustum() const", AS_METHODPR(Camera, GetFrustum, () const, const Frustum&), AS_CALL_THISCALL);
    // void Camera::GetFrustumSize(Vector3& near, Vector3& far) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void GetFrustumSize(Vector3&, Vector3&) const", AS_METHODPR(Camera, GetFrustumSize, (Vector3&, Vector3&) const, void), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Camera, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Camera, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Camera, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const VariantMap& get_globalVars() const", AS_METHODPR(Camera, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // Matrix4 Camera::GetGPUProjection() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Matrix4 GetGPUProjection() const", AS_METHODPR(Camera, GetGPUProjection, () const, Matrix4), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Matrix4 get_gPUProjection() const", AS_METHODPR(Camera, GetGPUProjection, () const, Matrix4), AS_CALL_THISCALL);
    // float Camera::GetHalfViewSize() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetHalfViewSize() const", AS_METHODPR(Camera, GetHalfViewSize, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_halfViewSize() const", AS_METHODPR(Camera, GetHalfViewSize, () const, float), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "uint GetID() const", AS_METHODPR(Camera, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "uint get_id() const", AS_METHODPR(Camera, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Camera, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // float Camera::GetLodBias() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetLodBias() const", AS_METHODPR(Camera, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_lodBias() const", AS_METHODPR(Camera, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Camera::GetLodDistance(float distance, float scale, float bias) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetLodDistance(float, float, float) const", AS_METHODPR(Camera, GetLodDistance, (float, float, float) const, float), AS_CALL_THISCALL);
    // float Camera::GetNearClip() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetNearClip() const", AS_METHODPR(Camera, GetNearClip, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_nearClip() const", AS_METHODPR(Camera, GetNearClip, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "Node@+ GetNode() const", AS_METHODPR(Camera, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Node@+ get_node() const", AS_METHODPR(Camera, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "uint GetNumAttributes() const", AS_METHODPR(Camera, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "uint get_numAttributes() const", AS_METHODPR(Camera, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "uint GetNumNetworkAttributes() const", AS_METHODPR(Camera, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Camera, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Camera, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Camera, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float Camera::GetOrthoSize() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetOrthoSize() const", AS_METHODPR(Camera, GetOrthoSize, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_orthoSize() const", AS_METHODPR(Camera, GetOrthoSize, () const, float), AS_CALL_THISCALL);
    // Matrix4 Camera::GetProjection() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Matrix4 GetProjection() const", AS_METHODPR(Camera, GetProjection, () const, Matrix4), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Matrix4 get_projection() const", AS_METHODPR(Camera, GetProjection, () const, Matrix4), AS_CALL_THISCALL);
    // const Vector2& Camera::GetProjectionOffset() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "const Vector2& GetProjectionOffset() const", AS_METHODPR(Camera, GetProjectionOffset, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Vector2& get_projectionOffset() const", AS_METHODPR(Camera, GetProjectionOffset, () const, const Vector2&), AS_CALL_THISCALL);
    // const Plane& Camera::GetReflectionPlane() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "const Plane& GetReflectionPlane() const", AS_METHODPR(Camera, GetReflectionPlane, () const, const Plane&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Plane& get_reflectionPlane() const", AS_METHODPR(Camera, GetReflectionPlane, () const, const Plane&), AS_CALL_THISCALL);
    // Vector4 Camera::GetReflectionPlaneAttr() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Vector4 GetReflectionPlaneAttr() const", AS_METHODPR(Camera, GetReflectionPlaneAttr, () const, Vector4), AS_CALL_THISCALL);
    // bool Camera::GetReverseCulling() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool GetReverseCulling() const", AS_METHODPR(Camera, GetReverseCulling, () const, bool), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "Scene@+ GetScene() const", AS_METHODPR(Camera, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Ray Camera::GetScreenRay(float x, float y) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Ray GetScreenRay(float, float) const", AS_METHODPR(Camera, GetScreenRay, (float, float) const, Ray), AS_CALL_THISCALL);
    // Frustum Camera::GetSplitFrustum(float nearClip, float farClip) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Frustum GetSplitFrustum(float, float) const", AS_METHODPR(Camera, GetSplitFrustum, (float, float) const, Frustum), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Camera, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "StringHash GetType() const", AS_METHODPR(Camera, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "StringHash get_type() const", AS_METHODPR(Camera, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "const String& GetTypeName() const", AS_METHODPR(Camera, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const String& get_typeName() const", AS_METHODPR(Camera, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Camera::GetUseClipping() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool GetUseClipping() const", AS_METHODPR(Camera, GetUseClipping, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_useClipping() const", AS_METHODPR(Camera, GetUseClipping, () const, bool), AS_CALL_THISCALL);
    // bool Camera::GetUseReflection() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool GetUseReflection() const", AS_METHODPR(Camera, GetUseReflection, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_useReflection() const", AS_METHODPR(Camera, GetUseReflection, () const, bool), AS_CALL_THISCALL);
    // const Matrix3x4& Camera::GetView() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "const Matrix3x4& GetView() const", AS_METHODPR(Camera, GetView, () const, const Matrix3x4&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "const Matrix3x4& get_view() const", AS_METHODPR(Camera, GetView, () const, const Matrix3x4&), AS_CALL_THISCALL);
    // unsigned Camera::GetViewMask() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "uint GetViewMask() const", AS_METHODPR(Camera, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "uint get_viewMask() const", AS_METHODPR(Camera, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // ViewOverrideFlags Camera::GetViewOverrideFlags() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "ViewOverrideFlags GetViewOverrideFlags() const", AS_METHODPR(Camera, GetViewOverrideFlags, () const, ViewOverrideFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "ViewOverrideFlags get_viewOverrideFlags() const", AS_METHODPR(Camera, GetViewOverrideFlags, () const, ViewOverrideFlags), AS_CALL_THISCALL);
    // Frustum Camera::GetViewSpaceFrustum() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Frustum GetViewSpaceFrustum() const", AS_METHODPR(Camera, GetViewSpaceFrustum, () const, Frustum), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "Frustum get_viewSpaceFrustum() const", AS_METHODPR(Camera, GetViewSpaceFrustum, () const, Frustum), AS_CALL_THISCALL);
    // Frustum Camera::GetViewSpaceSplitFrustum(float nearClip, float farClip) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Frustum GetViewSpaceSplitFrustum(float, float) const", AS_METHODPR(Camera, GetViewSpaceSplitFrustum, (float, float) const, Frustum), AS_CALL_THISCALL);
    // float Camera::GetZoom() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "float GetZoom() const", AS_METHODPR(Camera, GetZoom, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "float get_zoom() const", AS_METHODPR(Camera, GetZoom, () const, float), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "bool HasEventHandlers() const", AS_METHODPR(Camera, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Camera, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Camera, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "bool IsEnabled() const", AS_METHODPR(Camera, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_enabled() const", AS_METHODPR(Camera, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "bool IsEnabledEffective() const", AS_METHODPR(Camera, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_enabledEffective() const", AS_METHODPR(Camera, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Camera, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Camera::IsOrthographic() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool IsOrthographic() const", AS_METHODPR(Camera, IsOrthographic, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_orthographic() const", AS_METHODPR(Camera, IsOrthographic, () const, bool), AS_CALL_THISCALL);
    // bool Camera::IsProjectionValid() const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "bool IsProjectionValid() const", AS_METHODPR(Camera, IsProjectionValid, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "bool IsReplicated() const", AS_METHODPR(Camera, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_replicated() const", AS_METHODPR(Camera, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool IsTemporary() const", AS_METHODPR(Camera, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool get_temporary() const", AS_METHODPR(Camera, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool Load(Deserializer&)", AS_METHODPR(Camera, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Camera, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Camera, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "void MarkNetworkUpdate()", AS_METHODPR(Camera, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Camera, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Camera, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Camera, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "void OnSetEnabled()", AS_METHODPR(Camera, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "void PrepareNetworkUpdate()", AS_METHODPR(Camera, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Camera, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Camera, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Camera", "int Refs() const", AS_METHODPR(Camera, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "int get_refs() const", AS_METHODPR(Camera, Refs, () const, int), AS_CALL_THISCALL);
    // static void Camera::RegisterObject(Context* context) | File: ../Graphics/Camera.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Camera", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Camera, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "void Remove()", AS_METHODPR(Camera, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Camera, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void RemoveInstanceDefault()", AS_METHODPR(Camera, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void RemoveObjectAnimation()", AS_METHODPR(Camera, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void ResetToDefault()", AS_METHODPR(Camera, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "bool Save(Serializer&) const", AS_METHODPR(Camera, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool SaveDefaultAttributes() const", AS_METHODPR(Camera, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Camera, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "bool SaveXML(XMLElement&) const", AS_METHODPR(Camera, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // Vector3 Camera::ScreenToWorldPoint(const Vector3& screenPos) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Vector3 ScreenToWorldPoint(const Vector3&in) const", AS_METHODPR(Camera, ScreenToWorldPoint, (const Vector3&) const, Vector3), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void SendEvent(StringHash)", AS_METHODPR(Camera, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Camera, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetAnimationEnabled(bool)", AS_METHODPR(Camera, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_animationEnabled(bool)", AS_METHODPR(Camera, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetAnimationTime(float)", AS_METHODPR(Camera, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Camera::SetAspectRatio(float aspectRatio) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetAspectRatio(float)", AS_METHODPR(Camera, SetAspectRatio, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_aspectRatio(float)", AS_METHODPR(Camera, SetAspectRatio, (float), void), AS_CALL_THISCALL);
    // void Camera::SetAspectRatioInternal(float aspectRatio) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetAspectRatioInternal(float)", AS_METHODPR(Camera, SetAspectRatioInternal, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Camera, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Camera, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Camera, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Camera, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Camera, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Camera, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Camera, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Camera::SetAutoAspectRatio(bool enable) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetAutoAspectRatio(bool)", AS_METHODPR(Camera, SetAutoAspectRatio, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_autoAspectRatio(bool)", AS_METHODPR(Camera, SetAutoAspectRatio, (bool), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void SetBlockEvents(bool)", AS_METHODPR(Camera, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Camera::SetClipPlane(const Plane& plane) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetClipPlane(const Plane&in)", AS_METHODPR(Camera, SetClipPlane, (const Plane&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_clipPlane(const Plane&in)", AS_METHODPR(Camera, SetClipPlane, (const Plane&), void), AS_CALL_THISCALL);
    // void Camera::SetClipPlaneAttr(const Vector4& value) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetClipPlaneAttr(const Vector4&in)", AS_METHODPR(Camera, SetClipPlaneAttr, (const Vector4&), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Camera", "void SetEnabled(bool)", AS_METHODPR(Camera, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_enabled(bool)", AS_METHODPR(Camera, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Camera::SetFarClip(float farClip) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetFarClip(float)", AS_METHODPR(Camera, SetFarClip, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_farClip(float)", AS_METHODPR(Camera, SetFarClip, (float), void), AS_CALL_THISCALL);
    // void Camera::SetFillMode(FillMode mode) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetFillMode(FillMode)", AS_METHODPR(Camera, SetFillMode, (FillMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_fillMode(FillMode)", AS_METHODPR(Camera, SetFillMode, (FillMode), void), AS_CALL_THISCALL);
    // void Camera::SetFlipVertical(bool enable) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetFlipVertical(bool)", AS_METHODPR(Camera, SetFlipVertical, (bool), void), AS_CALL_THISCALL);
    // void Camera::SetFov(float fov) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetFov(float)", AS_METHODPR(Camera, SetFov, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_fov(float)", AS_METHODPR(Camera, SetFov, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Camera, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Camera, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void SetInstanceDefault(bool)", AS_METHODPR(Camera, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Camera, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Camera::SetLodBias(float bias) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetLodBias(float)", AS_METHODPR(Camera, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_lodBias(float)", AS_METHODPR(Camera, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void Camera::SetNearClip(float nearClip) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetNearClip(float)", AS_METHODPR(Camera, SetNearClip, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_nearClip(float)", AS_METHODPR(Camera, SetNearClip, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Camera, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Camera, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Camera", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Camera, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Camera::SetOrthographic(bool enable) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetOrthographic(bool)", AS_METHODPR(Camera, SetOrthographic, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_orthographic(bool)", AS_METHODPR(Camera, SetOrthographic, (bool), void), AS_CALL_THISCALL);
    // void Camera::SetOrthoSize(float orthoSize) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetOrthoSize(float)", AS_METHODPR(Camera, SetOrthoSize, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_orthoSize(float)", AS_METHODPR(Camera, SetOrthoSize, (float), void), AS_CALL_THISCALL);
    // void Camera::SetOrthoSize(const Vector2& orthoSize) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetOrthoSize(const Vector2&in)", AS_METHODPR(Camera, SetOrthoSize, (const Vector2&), void), AS_CALL_THISCALL);
    // void Camera::SetOrthoSizeAttr(float orthoSize) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetOrthoSizeAttr(float)", AS_METHODPR(Camera, SetOrthoSizeAttr, (float), void), AS_CALL_THISCALL);
    // void Camera::SetProjection(const Matrix4& projection) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetProjection(const Matrix4&in)", AS_METHODPR(Camera, SetProjection, (const Matrix4&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_projection(const Matrix4&in)", AS_METHODPR(Camera, SetProjection, (const Matrix4&), void), AS_CALL_THISCALL);
    // void Camera::SetProjectionOffset(const Vector2& offset) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetProjectionOffset(const Vector2&in)", AS_METHODPR(Camera, SetProjectionOffset, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_projectionOffset(const Vector2&in)", AS_METHODPR(Camera, SetProjectionOffset, (const Vector2&), void), AS_CALL_THISCALL);
    // void Camera::SetReflectionPlane(const Plane& plane) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetReflectionPlane(const Plane&in)", AS_METHODPR(Camera, SetReflectionPlane, (const Plane&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_reflectionPlane(const Plane&in)", AS_METHODPR(Camera, SetReflectionPlane, (const Plane&), void), AS_CALL_THISCALL);
    // void Camera::SetReflectionPlaneAttr(const Vector4& value) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetReflectionPlaneAttr(const Vector4&in)", AS_METHODPR(Camera, SetReflectionPlaneAttr, (const Vector4&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void SetTemporary(bool)", AS_METHODPR(Camera, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_temporary(bool)", AS_METHODPR(Camera, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Camera::SetUseClipping(bool enable) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetUseClipping(bool)", AS_METHODPR(Camera, SetUseClipping, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_useClipping(bool)", AS_METHODPR(Camera, SetUseClipping, (bool), void), AS_CALL_THISCALL);
    // void Camera::SetUseReflection(bool enable) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetUseReflection(bool)", AS_METHODPR(Camera, SetUseReflection, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_useReflection(bool)", AS_METHODPR(Camera, SetUseReflection, (bool), void), AS_CALL_THISCALL);
    // void Camera::SetViewMask(unsigned mask) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetViewMask(uint)", AS_METHODPR(Camera, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_viewMask(uint)", AS_METHODPR(Camera, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Camera::SetViewOverrideFlags(ViewOverrideFlags flags) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetViewOverrideFlags(ViewOverrideFlags)", AS_METHODPR(Camera, SetViewOverrideFlags, (ViewOverrideFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_viewOverrideFlags(ViewOverrideFlags)", AS_METHODPR(Camera, SetViewOverrideFlags, (ViewOverrideFlags), void), AS_CALL_THISCALL);
    // void Camera::SetZoom(float zoom) | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "void SetZoom(float)", AS_METHODPR(Camera, SetZoom, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "void set_zoom(float)", AS_METHODPR(Camera, SetZoom, (float), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void UnsubscribeFromAllEvents()", AS_METHODPR(Camera, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Camera_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Camera, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Camera, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Camera", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Camera, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Camera", "int WeakRefs() const", AS_METHODPR(Camera, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Camera", "int get_weakRefs() const", AS_METHODPR(Camera, WeakRefs, () const, int), AS_CALL_THISCALL);
    // Vector2 Camera::WorldToScreenPoint(const Vector3& worldPos) const | File: ../Graphics/Camera.h
    engine->RegisterObjectMethod("Camera", "Vector2 WorldToScreenPoint(const Vector3&in) const", AS_METHODPR(Camera, WorldToScreenPoint, (const Vector3&) const, Vector2), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Camera, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Camera, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Camera", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Camera, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("CheckBox", "void AddChild(UIElement@+)", AS_METHODPR(CheckBox, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CheckBox", asBEHAVE_ADDREF, "void f()", AS_METHODPR(CheckBox, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void AddTag(const String&in)", AS_METHODPR(CheckBox, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(CheckBox, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(CheckBox_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void AdjustScissor(IntRect&)", AS_METHODPR(CheckBox, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void AllocateNetworkState()", AS_METHODPR(CheckBox, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void ApplyAttributes()", AS_METHODPR(CheckBox, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void BringToFront()", AS_METHODPR(CheckBox, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // explicit CheckBox::CheckBox(Context* context) | File: ../UI/CheckBox.h
    engine->RegisterObjectBehaviour("CheckBox", asBEHAVE_FACTORY, "CheckBox@+ f()", AS_FUNCTION(CheckBox_CheckBox_Context), AS_CALL_CDECL);
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(CheckBox, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void DisableLayoutUpdate()", AS_METHODPR(CheckBox, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(CheckBox, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void EnableLayoutUpdate()", AS_METHODPR(CheckBox, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(CheckBox, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "uint FindChild(UIElement@+) const", AS_METHODPR(CheckBox, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "bool GetAnimationEnabled() const", AS_METHODPR(CheckBox, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_animationEnabled() const", AS_METHODPR(CheckBox, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const String& GetAppliedStyle() const", AS_METHODPR(CheckBox, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const String& get_style() const", AS_METHODPR(CheckBox, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "Variant GetAttribute(uint) const", AS_METHODPR(CheckBox, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "Variant get_attributes(uint) const", AS_METHODPR(CheckBox, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "Variant GetAttribute(const String&in) const", AS_METHODPR(CheckBox, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(CheckBox, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(CheckBox, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(CheckBox, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(CheckBox, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "Variant GetAttributeDefault(uint) const", AS_METHODPR(CheckBox, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "Variant get_attributeDefaults(uint) const", AS_METHODPR(CheckBox, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(CheckBox, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void CheckBox::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/CheckBox.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "BlendMode GetBlendMode() const", AS_METHODPR(CheckBox, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "BlendMode get_blendMode() const", AS_METHODPR(CheckBox, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "bool GetBlockEvents() const", AS_METHODPR(CheckBox, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "const IntRect& GetBorder() const", AS_METHODPR(CheckBox, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntRect& get_border() const", AS_METHODPR(CheckBox, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool GetBringToBack() const", AS_METHODPR(CheckBox, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_bringToBack() const", AS_METHODPR(CheckBox, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool GetBringToFront() const", AS_METHODPR(CheckBox, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_bringToFront() const", AS_METHODPR(CheckBox, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "const String& GetCategory() const", AS_METHODPR(CheckBox, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const String& get_category() const", AS_METHODPR(CheckBox, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // const IntVector2& CheckBox::GetCheckedOffset() const | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetCheckedOffset() const", AS_METHODPR(CheckBox, GetCheckedOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_checkedOffset() const", AS_METHODPR(CheckBox, GetCheckedOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ GetChild(uint) const", AS_METHODPR(CheckBox, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ get_children(uint) const", AS_METHODPR(CheckBox, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(CheckBox, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(CheckBox, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetChildOffset() const", AS_METHODPR(CheckBox, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_childOffset() const", AS_METHODPR(CheckBox, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(CheckBox_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(CheckBox_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(CheckBox_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntRect& GetClipBorder() const", AS_METHODPR(CheckBox, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntRect& get_clipBorder() const", AS_METHODPR(CheckBox, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool GetClipChildren() const", AS_METHODPR(CheckBox, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_clipChildren() const", AS_METHODPR(CheckBox, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Color& GetColor(Corner) const", AS_METHODPR(CheckBox, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const Color& get_colors(Corner) const", AS_METHODPR(CheckBox, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Color& GetColorAttr() const", AS_METHODPR(CheckBox, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "IntRect GetCombinedScreenRect()", AS_METHODPR(CheckBox, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "IntRect get_combinedScreenRect()", AS_METHODPR(CheckBox, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(CheckBox, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Color& GetDerivedColor() const", AS_METHODPR(CheckBox, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "float GetDerivedOpacity() const", AS_METHODPR(CheckBox, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "float get_derivedOpacity() const", AS_METHODPR(CheckBox, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetDisabledOffset() const", AS_METHODPR(CheckBox, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_disabledOffset() const", AS_METHODPR(CheckBox, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(CheckBox, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(CheckBox, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "uint GetDragButtonCount() const", AS_METHODPR(CheckBox, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "uint get_dragButtonCount() const", AS_METHODPR(CheckBox, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(CheckBox, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(CheckBox, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(CheckBox, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ GetElementEventSender() const", AS_METHODPR(CheckBox, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool GetEnableAnchor() const", AS_METHODPR(CheckBox, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_enableAnchor() const", AS_METHODPR(CheckBox, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "VariantMap& GetEventDataMap() const", AS_METHODPR(CheckBox, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "Object@+ GetEventSender() const", AS_METHODPR(CheckBox, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "FocusMode GetFocusMode() const", AS_METHODPR(CheckBox, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "FocusMode get_focusMode() const", AS_METHODPR(CheckBox, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(CheckBox, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(CheckBox, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "const VariantMap& GetGlobalVars() const", AS_METHODPR(CheckBox, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const VariantMap& get_globalVars() const", AS_METHODPR(CheckBox, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetHeight() const", AS_METHODPR(CheckBox, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_height() const", AS_METHODPR(CheckBox, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(CheckBox, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(CheckBox, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetHoverOffset() const", AS_METHODPR(CheckBox, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_hoverOffset() const", AS_METHODPR(CheckBox, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "const IntRect& GetImageBorder() const", AS_METHODPR(CheckBox, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntRect& get_imageBorder() const", AS_METHODPR(CheckBox, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "const IntRect& GetImageRect() const", AS_METHODPR(CheckBox, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntRect& get_imageRect() const", AS_METHODPR(CheckBox, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetIndent() const", AS_METHODPR(CheckBox, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_indent() const", AS_METHODPR(CheckBox, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetIndentSpacing() const", AS_METHODPR(CheckBox, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_indentSpacing() const", AS_METHODPR(CheckBox, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetIndentWidth() const", AS_METHODPR(CheckBox, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_indentWidth() const", AS_METHODPR(CheckBox, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(CheckBox, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntRect& GetLayoutBorder() const", AS_METHODPR(CheckBox, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntRect& get_layoutBorder() const", AS_METHODPR(CheckBox, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetLayoutElementMaxSize() const", AS_METHODPR(CheckBox, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(CheckBox, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(CheckBox, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "LayoutMode GetLayoutMode() const", AS_METHODPR(CheckBox, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "LayoutMode get_layoutMode() const", AS_METHODPR(CheckBox, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetLayoutSpacing() const", AS_METHODPR(CheckBox, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_layoutSpacing() const", AS_METHODPR(CheckBox, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "Material@+ GetMaterial() const", AS_METHODPR(CheckBox, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "Material@+ get_material() const", AS_METHODPR(CheckBox, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "ResourceRef GetMaterialAttr() const", AS_METHODPR(CheckBox, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Vector2& GetMaxAnchor() const", AS_METHODPR(CheckBox, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const Vector2& get_maxAnchor() const", AS_METHODPR(CheckBox, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetMaxHeight() const", AS_METHODPR(CheckBox, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_maxHeight() const", AS_METHODPR(CheckBox, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetMaxOffset() const", AS_METHODPR(CheckBox, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_maxOffset() const", AS_METHODPR(CheckBox, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetMaxSize() const", AS_METHODPR(CheckBox, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_maxSize() const", AS_METHODPR(CheckBox, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetMaxWidth() const", AS_METHODPR(CheckBox, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_maxWidth() const", AS_METHODPR(CheckBox, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Vector2& GetMinAnchor() const", AS_METHODPR(CheckBox, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const Vector2& get_minAnchor() const", AS_METHODPR(CheckBox, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetMinHeight() const", AS_METHODPR(CheckBox, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_minHeight() const", AS_METHODPR(CheckBox, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetMinOffset() const", AS_METHODPR(CheckBox, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_minOffset() const", AS_METHODPR(CheckBox, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetMinSize() const", AS_METHODPR(CheckBox, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_minSize() const", AS_METHODPR(CheckBox, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetMinWidth() const", AS_METHODPR(CheckBox, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_minWidth() const", AS_METHODPR(CheckBox, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const String& GetName() const", AS_METHODPR(CheckBox, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const String& get_name() const", AS_METHODPR(CheckBox, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "uint GetNumAttributes() const", AS_METHODPR(CheckBox, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "uint get_numAttributes() const", AS_METHODPR(CheckBox, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "uint GetNumChildren(bool = false) const", AS_METHODPR(CheckBox, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "uint get_numChildren(bool = false) const", AS_METHODPR(CheckBox, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "uint GetNumNetworkAttributes() const", AS_METHODPR(CheckBox, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(CheckBox, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(CheckBox, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(CheckBox, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "float GetOpacity() const", AS_METHODPR(CheckBox, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "float get_opacity() const", AS_METHODPR(CheckBox, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ GetParent() const", AS_METHODPR(CheckBox, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ get_parent() const", AS_METHODPR(CheckBox, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Vector2& GetPivot() const", AS_METHODPR(CheckBox, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const Vector2& get_pivot() const", AS_METHODPR(CheckBox, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetPosition() const", AS_METHODPR(CheckBox, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_position() const", AS_METHODPR(CheckBox, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetPriority() const", AS_METHODPR(CheckBox, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_priority() const", AS_METHODPR(CheckBox, GetPriority, () const, int), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ GetRoot() const", AS_METHODPR(CheckBox, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ get_root() const", AS_METHODPR(CheckBox, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetScreenPosition() const", AS_METHODPR(CheckBox, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_screenPosition() const", AS_METHODPR(CheckBox, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& GetSize() const", AS_METHODPR(CheckBox, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const IntVector2& get_size() const", AS_METHODPR(CheckBox, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool GetSortChildren() const", AS_METHODPR(CheckBox, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_sortChildren() const", AS_METHODPR(CheckBox, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(CheckBox, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(CheckBox_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("CheckBox", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(CheckBox_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "Texture@+ GetTexture() const", AS_METHODPR(CheckBox, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "Texture@+ get_texture() const", AS_METHODPR(CheckBox, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "ResourceRef GetTextureAttr() const", AS_METHODPR(CheckBox, GetTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "TraversalMode GetTraversalMode() const", AS_METHODPR(CheckBox, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "TraversalMode get_traversalMode() const", AS_METHODPR(CheckBox, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "StringHash GetType() const", AS_METHODPR(CheckBox, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "StringHash get_type() const", AS_METHODPR(CheckBox, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "const String& GetTypeName() const", AS_METHODPR(CheckBox, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "const String& get_typeName() const", AS_METHODPR(CheckBox, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool GetUseDerivedOpacity() const", AS_METHODPR(CheckBox, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_useDerivedOpacity() const", AS_METHODPR(CheckBox, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(CheckBox, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "const VariantMap& GetVars() const", AS_METHODPR(CheckBox, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(CheckBox, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(CheckBox, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "int GetWidth() const", AS_METHODPR(CheckBox, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_width() const", AS_METHODPR(CheckBox, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool HasColorGradient() const", AS_METHODPR(CheckBox, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_colorGradient() const", AS_METHODPR(CheckBox, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "bool HasEventHandlers() const", AS_METHODPR(CheckBox, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool HasFocus() const", AS_METHODPR(CheckBox, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_focus() const", AS_METHODPR(CheckBox, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(CheckBox, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(CheckBox, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool HasTag(const String&in) const", AS_METHODPR(CheckBox, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void InsertChild(uint, UIElement@+)", AS_METHODPR(CheckBox, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool CheckBox::IsChecked() const | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "bool IsChecked() const", AS_METHODPR(CheckBox, IsChecked, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_checked() const", AS_METHODPR(CheckBox, IsChecked, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsChildOf(UIElement@+) const", AS_METHODPR(CheckBox, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsEditable() const", AS_METHODPR(CheckBox, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_editable() const", AS_METHODPR(CheckBox, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsElementEventSender() const", AS_METHODPR(CheckBox, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_elementEventSender() const", AS_METHODPR(CheckBox, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsEnabled() const", AS_METHODPR(CheckBox, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_enabled() const", AS_METHODPR(CheckBox, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsEnabledSelf() const", AS_METHODPR(CheckBox, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_enabledSelf() const", AS_METHODPR(CheckBox, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsFixedHeight() const", AS_METHODPR(CheckBox, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_fixedHeight() const", AS_METHODPR(CheckBox, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsFixedSize() const", AS_METHODPR(CheckBox, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_fixedSize() const", AS_METHODPR(CheckBox, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsFixedWidth() const", AS_METHODPR(CheckBox, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_fixedWidth() const", AS_METHODPR(CheckBox, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsHovering() const", AS_METHODPR(CheckBox, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_hovering() const", AS_METHODPR(CheckBox, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsInside(IntVector2, bool)", AS_METHODPR(CheckBox, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(CheckBox, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "bool IsInstanceOf(StringHash) const", AS_METHODPR(CheckBox, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsInternal() const", AS_METHODPR(CheckBox, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_internal() const", AS_METHODPR(CheckBox, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsSelected() const", AS_METHODPR(CheckBox, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_selected() const", AS_METHODPR(CheckBox, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool IsTemporary() const", AS_METHODPR(CheckBox, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_temporary() const", AS_METHODPR(CheckBox, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "bool IsTiled() const", AS_METHODPR(CheckBox, IsTiled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_tiled() const", AS_METHODPR(CheckBox, IsTiled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsVisible() const", AS_METHODPR(CheckBox, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_visible() const", AS_METHODPR(CheckBox, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsVisibleEffective() const", AS_METHODPR(CheckBox, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool get_visibleEffective() const", AS_METHODPR(CheckBox, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsWheelHandler() const", AS_METHODPR(CheckBox, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(CheckBox, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool Load(Deserializer&)", AS_METHODPR(CheckBox, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(CheckBox, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(CheckBox, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool LoadXML(const XMLElement&in)", AS_METHODPR(CheckBox, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(CheckBox, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool LoadXML(Deserializer&)", AS_METHODPR(CheckBox, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void MarkNetworkUpdate()", AS_METHODPR(CheckBox, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void CheckBox::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(CheckBox, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(CheckBox, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(CheckBox, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(CheckBox, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(CheckBox, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(CheckBox, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(CheckBox, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(CheckBox, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(CheckBox, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(CheckBox, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(CheckBox, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(CheckBox, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnIndentSet()", AS_METHODPR(CheckBox, OnIndentSet, (), void), AS_CALL_THISCALL);
    // void CheckBox::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(CheckBox, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(CheckBox, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(CheckBox, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(CheckBox, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnSetEditable()", AS_METHODPR(CheckBox, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnTextInput(const String&in)", AS_METHODPR(CheckBox, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(CheckBox, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(CheckBox, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(CheckBox, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CheckBox", "int Refs() const", AS_METHODPR(CheckBox, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_refs() const", AS_METHODPR(CheckBox, Refs, () const, int), AS_CALL_THISCALL);
    // static void CheckBox::RegisterObject(Context* context) | File: ../UI/CheckBox.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("CheckBox", asBEHAVE_RELEASE, "void f()", AS_METHODPR(CheckBox, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void Remove()", AS_METHODPR(CheckBox, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveAllChildren()", AS_METHODPR(CheckBox, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveAllTags()", AS_METHODPR(CheckBox, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(CheckBox, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(CheckBox, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveChildAtIndex(uint)", AS_METHODPR(CheckBox, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveInstanceDefault()", AS_METHODPR(CheckBox, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void RemoveObjectAnimation()", AS_METHODPR(CheckBox, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool RemoveTag(const String&in)", AS_METHODPR(CheckBox, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void ResetDeepEnabled()", AS_METHODPR(CheckBox, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void ResetToDefault()", AS_METHODPR(CheckBox, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool Save(Serializer&) const", AS_METHODPR(CheckBox, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool SaveDefaultAttributes() const", AS_METHODPR(CheckBox, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "bool SaveJSON(JSONValue&) const", AS_METHODPR(CheckBox, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool SaveXML(XMLElement&) const", AS_METHODPR(CheckBox, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(CheckBox, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(CheckBox, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void SendEvent(StringHash)", AS_METHODPR(CheckBox, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(CheckBox, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(CheckBox, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetAnimationEnabled(bool)", AS_METHODPR(CheckBox, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_animationEnabled(bool)", AS_METHODPR(CheckBox, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetAnimationTime(float)", AS_METHODPR(CheckBox, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(CheckBox, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(CheckBox, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(CheckBox, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(CheckBox, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(CheckBox, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(CheckBox, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(CheckBox, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetBlendMode(BlendMode)", AS_METHODPR(CheckBox, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_blendMode(BlendMode)", AS_METHODPR(CheckBox, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void SetBlockEvents(bool)", AS_METHODPR(CheckBox, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetBorder(const IntRect&in)", AS_METHODPR(CheckBox, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_border(const IntRect&in)", AS_METHODPR(CheckBox, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetBringToBack(bool)", AS_METHODPR(CheckBox, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_bringToBack(bool)", AS_METHODPR(CheckBox, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetBringToFront(bool)", AS_METHODPR(CheckBox, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_bringToFront(bool)", AS_METHODPR(CheckBox, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void CheckBox::SetChecked(bool enable) | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "void SetChecked(bool)", AS_METHODPR(CheckBox, SetChecked, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_checked(bool)", AS_METHODPR(CheckBox, SetChecked, (bool), void), AS_CALL_THISCALL);
    // void CheckBox::SetCheckedOffset(const IntVector2& offset) | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "void SetCheckedOffset(const IntVector2&in)", AS_METHODPR(CheckBox, SetCheckedOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_checkedOffset(const IntVector2&in)", AS_METHODPR(CheckBox, SetCheckedOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void CheckBox::SetCheckedOffset(int x, int y) | File: ../UI/CheckBox.h
    engine->RegisterObjectMethod("CheckBox", "void SetCheckedOffset(int, int)", AS_METHODPR(CheckBox, SetCheckedOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(CheckBox, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetClipBorder(const IntRect&in)", AS_METHODPR(CheckBox, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_clipBorder(const IntRect&in)", AS_METHODPR(CheckBox, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetClipChildren(bool)", AS_METHODPR(CheckBox, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_clipChildren(bool)", AS_METHODPR(CheckBox, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetColor(const Color&in)", AS_METHODPR(CheckBox, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_color(const Color&in)", AS_METHODPR(CheckBox, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetColor(Corner, const Color&in)", AS_METHODPR(CheckBox, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_colors(Corner, const Color&in)", AS_METHODPR(CheckBox, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetDeepEnabled(bool)", AS_METHODPR(CheckBox, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(CheckBox, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(CheckBox, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetDisabledOffset(const IntVector2&in)", AS_METHODPR(CheckBox, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_disabledOffset(const IntVector2&in)", AS_METHODPR(CheckBox, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetDisabledOffset(int, int)", AS_METHODPR(CheckBox, SetDisabledOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(CheckBox, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(CheckBox, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetEditable(bool)", AS_METHODPR(CheckBox, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_editable(bool)", AS_METHODPR(CheckBox, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetElementEventSender(bool)", AS_METHODPR(CheckBox, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_elementEventSender(bool)", AS_METHODPR(CheckBox, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetEnableAnchor(bool)", AS_METHODPR(CheckBox, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_enableAnchor(bool)", AS_METHODPR(CheckBox, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetEnabled(bool)", AS_METHODPR(CheckBox, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_enabled(bool)", AS_METHODPR(CheckBox, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetEnabledRecursive(bool)", AS_METHODPR(CheckBox, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetFixedHeight(int)", AS_METHODPR(CheckBox, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(CheckBox, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetFixedSize(int, int)", AS_METHODPR(CheckBox, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetFixedWidth(int)", AS_METHODPR(CheckBox, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetFocus(bool)", AS_METHODPR(CheckBox, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_focus(bool)", AS_METHODPR(CheckBox, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetFocusMode(FocusMode)", AS_METHODPR(CheckBox, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_focusMode(FocusMode)", AS_METHODPR(CheckBox, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetFullImageRect()", AS_METHODPR(CheckBox, SetFullImageRect, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(CheckBox, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(CheckBox, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetHeight(int)", AS_METHODPR(CheckBox, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_height(int)", AS_METHODPR(CheckBox, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(CheckBox, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(CheckBox, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetHovering(bool)", AS_METHODPR(CheckBox, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetHoverOffset(const IntVector2&in)", AS_METHODPR(CheckBox, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_hoverOffset(const IntVector2&in)", AS_METHODPR(CheckBox, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetHoverOffset(int, int)", AS_METHODPR(CheckBox, SetHoverOffset, (int, int), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetImageBorder(const IntRect&in)", AS_METHODPR(CheckBox, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_imageBorder(const IntRect&in)", AS_METHODPR(CheckBox, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetImageRect(const IntRect&in)", AS_METHODPR(CheckBox, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_imageRect(const IntRect&in)", AS_METHODPR(CheckBox, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetIndent(int)", AS_METHODPR(CheckBox, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_indent(int)", AS_METHODPR(CheckBox, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetIndentSpacing(int)", AS_METHODPR(CheckBox, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_indentSpacing(int)", AS_METHODPR(CheckBox, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void SetInstanceDefault(bool)", AS_METHODPR(CheckBox, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(CheckBox, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetInternal(bool)", AS_METHODPR(CheckBox, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_internal(bool)", AS_METHODPR(CheckBox, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(CheckBox, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(CheckBox, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(CheckBox, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(CheckBox, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(CheckBox, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetLayoutMode(LayoutMode)", AS_METHODPR(CheckBox, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_layoutMode(LayoutMode)", AS_METHODPR(CheckBox, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetLayoutSpacing(int)", AS_METHODPR(CheckBox, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_layoutSpacing(int)", AS_METHODPR(CheckBox, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaterial(Material@+)", AS_METHODPR(CheckBox, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_material(Material@+)", AS_METHODPR(CheckBox, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(CheckBox, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(CheckBox, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(CheckBox, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxAnchor(float, float)", AS_METHODPR(CheckBox, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxHeight(int)", AS_METHODPR(CheckBox, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_maxHeight(int)", AS_METHODPR(CheckBox, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(CheckBox, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(CheckBox, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(CheckBox, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_maxSize(const IntVector2&in)", AS_METHODPR(CheckBox, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxSize(int, int)", AS_METHODPR(CheckBox, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMaxWidth(int)", AS_METHODPR(CheckBox, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_maxWidth(int)", AS_METHODPR(CheckBox, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(CheckBox, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_minAnchor(const Vector2&in)", AS_METHODPR(CheckBox, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinAnchor(float, float)", AS_METHODPR(CheckBox, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinHeight(int)", AS_METHODPR(CheckBox, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_minHeight(int)", AS_METHODPR(CheckBox, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(CheckBox, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_minOffset(const IntVector2&in)", AS_METHODPR(CheckBox, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinSize(const IntVector2&in)", AS_METHODPR(CheckBox, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_minSize(const IntVector2&in)", AS_METHODPR(CheckBox, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinSize(int, int)", AS_METHODPR(CheckBox, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetMinWidth(int)", AS_METHODPR(CheckBox, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_minWidth(int)", AS_METHODPR(CheckBox, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetName(const String&in)", AS_METHODPR(CheckBox, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_name(const String&in)", AS_METHODPR(CheckBox, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(CheckBox, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(CheckBox, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("CheckBox", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(CheckBox, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetOpacity(float)", AS_METHODPR(CheckBox, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_opacity(float)", AS_METHODPR(CheckBox, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(CheckBox, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetPivot(const Vector2&in)", AS_METHODPR(CheckBox, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_pivot(const Vector2&in)", AS_METHODPR(CheckBox, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetPivot(float, float)", AS_METHODPR(CheckBox, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetPosition(const IntVector2&in)", AS_METHODPR(CheckBox, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_position(const IntVector2&in)", AS_METHODPR(CheckBox, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetPosition(int, int)", AS_METHODPR(CheckBox, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetPriority(int)", AS_METHODPR(CheckBox, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_priority(int)", AS_METHODPR(CheckBox, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(CheckBox, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetSelected(bool)", AS_METHODPR(CheckBox, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_selected(bool)", AS_METHODPR(CheckBox, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetSize(const IntVector2&in)", AS_METHODPR(CheckBox, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_size(const IntVector2&in)", AS_METHODPR(CheckBox, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetSize(int, int)", AS_METHODPR(CheckBox, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetSortChildren(bool)", AS_METHODPR(CheckBox, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_sortChildren(bool)", AS_METHODPR(CheckBox, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(CheckBox, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool SetStyle(const XMLElement&in)", AS_METHODPR(CheckBox, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(CheckBox, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(CheckBox_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void SetTemporary(bool)", AS_METHODPR(CheckBox, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_temporary(bool)", AS_METHODPR(CheckBox, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetTexture(Texture@+)", AS_METHODPR(CheckBox, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_texture(Texture@+)", AS_METHODPR(CheckBox, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetTextureAttr(const ResourceRef&in)", AS_METHODPR(CheckBox, SetTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("CheckBox", "void SetTiled(bool)", AS_METHODPR(CheckBox, SetTiled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_tiled(bool)", AS_METHODPR(CheckBox, SetTiled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetTraversalMode(TraversalMode)", AS_METHODPR(CheckBox, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_traversalMode(TraversalMode)", AS_METHODPR(CheckBox, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetUseDerivedOpacity(bool)", AS_METHODPR(CheckBox, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_useDerivedOpacity(bool)", AS_METHODPR(CheckBox, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(CheckBox, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(CheckBox, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(CheckBox, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetVisible(bool)", AS_METHODPR(CheckBox, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_visible(bool)", AS_METHODPR(CheckBox, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SetWidth(int)", AS_METHODPR(CheckBox, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "void set_width(int)", AS_METHODPR(CheckBox, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void SortChildren()", AS_METHODPR(CheckBox, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void UnsubscribeFromAllEvents()", AS_METHODPR(CheckBox, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(CheckBox_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(CheckBox, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(CheckBox, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("CheckBox", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(CheckBox, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void Update(float)", AS_METHODPR(CheckBox, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("CheckBox", "void UpdateLayout()", AS_METHODPR(CheckBox, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("CheckBox", "int WeakRefs() const", AS_METHODPR(CheckBox, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("CheckBox", "int get_weakRefs() const", AS_METHODPR(CheckBox, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(CheckBox, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(CheckBox, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("CheckBox", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(CheckBox, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("CascadeParameters", asBEHAVE_CONSTRUCT, "void f(float, float, float, float, float, float = 1.0f)", AS_FUNCTION_OBJFIRST(CascadeParameters_CascadeParameters_float_float_float_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // float CascadeParameters::GetShadowRange() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("CascadeParameters", "float GetShadowRange() const", AS_METHODPR(CascadeParameters, GetShadowRange, () const, float), AS_CALL_THISCALL);
    // void CascadeParameters::Validate() | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("CascadeParameters", "void Validate()", AS_METHODPR(CascadeParameters, Validate, (), void), AS_CALL_THISCALL);
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
