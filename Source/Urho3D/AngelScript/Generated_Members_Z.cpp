// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* Zone_GetLights_void(Zone* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* Zone_GetVertexLights_void(Zone* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Zone_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Zone* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Zone::Zone(Context* context) | File: ../Graphics/Zone.h
static Zone* Zone_Zone_Context()
{
    return new Zone(GetScriptContext());
}

void ASRegisterGenerated_Members_Z(asIScriptEngine* engine)
{
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void AddLight(Light@+)", AS_METHODPR(Zone, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Zone", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Zone, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void AddVertexLight(Light@+)", AS_METHODPR(Zone, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void AllocateNetworkState()", AS_METHODPR(Zone, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void ApplyAttributes()", AS_METHODPR(Zone, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Zone::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Zone, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(Zone, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // const Color& Zone::GetAmbientColor() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "const Color& GetAmbientColor() const", AS_METHODPR(Zone, GetAmbientColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_ambientColor() const", AS_METHODPR(Zone, GetAmbientColor, () const, const Color&), AS_CALL_THISCALL);
    // const Color& Zone::GetAmbientEndColor() | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "const Color& GetAmbientEndColor()", AS_METHODPR(Zone, GetAmbientEndColor, (), const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_ambientEndColor()", AS_METHODPR(Zone, GetAmbientEndColor, (), const Color&), AS_CALL_THISCALL);
    // bool Zone::GetAmbientGradient() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "bool GetAmbientGradient() const", AS_METHODPR(Zone, GetAmbientGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_ambientGradient() const", AS_METHODPR(Zone, GetAmbientGradient, () const, bool), AS_CALL_THISCALL);
    // const Color& Zone::GetAmbientStartColor() | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "const Color& GetAmbientStartColor()", AS_METHODPR(Zone, GetAmbientStartColor, (), const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_ambientStartColor()", AS_METHODPR(Zone, GetAmbientStartColor, (), const Color&), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "bool GetAnimationEnabled() const", AS_METHODPR(Zone, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_animationEnabled() const", AS_METHODPR(Zone, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "Variant GetAttribute(uint) const", AS_METHODPR(Zone, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "Variant get_attributes(uint) const", AS_METHODPR(Zone, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "Variant GetAttribute(const String&in) const", AS_METHODPR(Zone, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Zone, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Zone, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Zone, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Zone, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Zone, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Zone, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Zone, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "bool GetBlockEvents() const", AS_METHODPR(Zone, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(Zone, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const BoundingBox& get_boundingBox() const", AS_METHODPR(Zone, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool GetCastShadows() const", AS_METHODPR(Zone, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_castShadows() const", AS_METHODPR(Zone, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "const String& GetCategory() const", AS_METHODPR(Zone, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const String& get_category() const", AS_METHODPR(Zone, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Zone, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Zone", "float GetDistance() const", AS_METHODPR(Zone, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint8 GetDrawableFlags() const", AS_METHODPR(Zone, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetDrawDistance() const", AS_METHODPR(Zone, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_drawDistance() const", AS_METHODPR(Zone, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "VariantMap& GetEventDataMap() const", AS_METHODPR(Zone, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "Object@+ GetEventSender() const", AS_METHODPR(Zone, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "Light@+ GetFirstLight() const", AS_METHODPR(Zone, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // const Color& Zone::GetFogColor() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "const Color& GetFogColor() const", AS_METHODPR(Zone, GetFogColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_fogColor() const", AS_METHODPR(Zone, GetFogColor, () const, const Color&), AS_CALL_THISCALL);
    // float Zone::GetFogEnd() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "float GetFogEnd() const", AS_METHODPR(Zone, GetFogEnd, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_fogEnd() const", AS_METHODPR(Zone, GetFogEnd, () const, float), AS_CALL_THISCALL);
    // float Zone::GetFogHeight() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "float GetFogHeight() const", AS_METHODPR(Zone, GetFogHeight, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_fogHeight() const", AS_METHODPR(Zone, GetFogHeight, () const, float), AS_CALL_THISCALL);
    // float Zone::GetFogHeightScale() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "float GetFogHeightScale() const", AS_METHODPR(Zone, GetFogHeightScale, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_fogHeightScale() const", AS_METHODPR(Zone, GetFogHeightScale, () const, float), AS_CALL_THISCALL);
    // float Zone::GetFogStart() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "float GetFogStart() const", AS_METHODPR(Zone, GetFogStart, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_fogStart() const", AS_METHODPR(Zone, GetFogStart, () const, float), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Zone, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Zone, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Zone, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const VariantMap& get_globalVars() const", AS_METHODPR(Zone, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // bool Zone::GetHeightFog() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "bool GetHeightFog() const", AS_METHODPR(Zone, GetHeightFog, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_heightFog() const", AS_METHODPR(Zone, GetHeightFog, () const, bool), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "uint GetID() const", AS_METHODPR(Zone, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_id() const", AS_METHODPR(Zone, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Zone, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const Matrix3x4& Zone::GetInverseWorldTransform() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "const Matrix3x4& GetInverseWorldTransform() const", AS_METHODPR(Zone, GetInverseWorldTransform, () const, const Matrix3x4&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Matrix3x4& get_inverseWorldTransform() const", AS_METHODPR(Zone, GetInverseWorldTransform, () const, const Matrix3x4&), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint GetLightMask() const", AS_METHODPR(Zone, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_lightMask() const", AS_METHODPR(Zone, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(Zone_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetLodBias() const", AS_METHODPR(Zone, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_lodBias() const", AS_METHODPR(Zone, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetLodDistance() const", AS_METHODPR(Zone, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(Zone, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint GetMaxLights() const", AS_METHODPR(Zone, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_maxLights() const", AS_METHODPR(Zone, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetMaxZ() const", AS_METHODPR(Zone, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetMinZ() const", AS_METHODPR(Zone, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "Node@+ GetNode() const", AS_METHODPR(Zone, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "Node@+ get_node() const", AS_METHODPR(Zone, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "uint GetNumAttributes() const", AS_METHODPR(Zone, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_numAttributes() const", AS_METHODPR(Zone, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "uint GetNumNetworkAttributes() const", AS_METHODPR(Zone, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint GetNumOccluderTriangles()", AS_METHODPR(Zone, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Zone, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Zone, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Zone, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // bool Zone::GetOverride() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "bool GetOverride() const", AS_METHODPR(Zone, GetOverride, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_override() const", AS_METHODPR(Zone, GetOverride, () const, bool), AS_CALL_THISCALL);
    // int Zone::GetPriority() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "int GetPriority() const", AS_METHODPR(Zone, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "int get_priority() const", AS_METHODPR(Zone, GetPriority, () const, int), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "Scene@+ GetScene() const", AS_METHODPR(Zone, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetShadowDistance() const", AS_METHODPR(Zone, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_shadowDistance() const", AS_METHODPR(Zone, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint GetShadowMask() const", AS_METHODPR(Zone, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_shadowMask() const", AS_METHODPR(Zone, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetSortValue() const", AS_METHODPR(Zone, GetSortValue, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Zone, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "StringHash GetType() const", AS_METHODPR(Zone, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "StringHash get_type() const", AS_METHODPR(Zone, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "const String& GetTypeName() const", AS_METHODPR(Zone, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const String& get_typeName() const", AS_METHODPR(Zone, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(Zone, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(Zone_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint GetViewMask() const", AS_METHODPR(Zone, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_viewMask() const", AS_METHODPR(Zone, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(Zone, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(Zone, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "Zone@+ GetZone() const", AS_METHODPR(Zone, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "Zone@+ get_zone() const", AS_METHODPR(Zone, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint GetZoneMask() const", AS_METHODPR(Zone, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_zoneMask() const", AS_METHODPR(Zone, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // Texture* Zone::GetZoneTexture() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "Texture@+ GetZoneTexture() const", AS_METHODPR(Zone, GetZoneTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "Texture@+ get_zoneTexture() const", AS_METHODPR(Zone, GetZoneTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef Zone::GetZoneTextureAttr() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "ResourceRef GetZoneTextureAttr() const", AS_METHODPR(Zone, GetZoneTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool HasBasePass(uint) const", AS_METHODPR(Zone, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "bool HasEventHandlers() const", AS_METHODPR(Zone, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Zone, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Zone, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "bool IsEnabled() const", AS_METHODPR(Zone, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_enabled() const", AS_METHODPR(Zone, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "bool IsEnabledEffective() const", AS_METHODPR(Zone, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_enabledEffective() const", AS_METHODPR(Zone, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Zone::IsInside(const Vector3& point) const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "bool IsInside(const Vector3&in) const", AS_METHODPR(Zone, IsInside, (const Vector3&) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Zone, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool IsInView() const", AS_METHODPR(Zone, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_inView() const", AS_METHODPR(Zone, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool IsInView(Camera@+) const", AS_METHODPR(Zone, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(Zone, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool IsOccludee() const", AS_METHODPR(Zone, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_occludee() const", AS_METHODPR(Zone, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool IsOccluder() const", AS_METHODPR(Zone, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_occluder() const", AS_METHODPR(Zone, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "bool IsReplicated() const", AS_METHODPR(Zone, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_replicated() const", AS_METHODPR(Zone, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool IsTemporary() const", AS_METHODPR(Zone, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_temporary() const", AS_METHODPR(Zone, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool IsZoneDirty() const", AS_METHODPR(Zone, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void LimitLights()", AS_METHODPR(Zone, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void LimitVertexLights(bool)", AS_METHODPR(Zone, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool Load(Deserializer&)", AS_METHODPR(Zone, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Zone, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Zone, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void MarkForUpdate()", AS_METHODPR(Zone, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void MarkInView(const FrameInfo&in)", AS_METHODPR(Zone, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void MarkInView(uint)", AS_METHODPR(Zone, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "void MarkNetworkUpdate()", AS_METHODPR(Zone, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Zone, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Zone, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Zone, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void OnSetEnabled()", AS_METHODPR(Zone, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "void PrepareNetworkUpdate()", AS_METHODPR(Zone, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Zone, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Zone, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Zone", "int Refs() const", AS_METHODPR(Zone, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "int get_refs() const", AS_METHODPR(Zone, Refs, () const, int), AS_CALL_THISCALL);
    // static void Zone::RegisterObject(Context* context) | File: ../Graphics/Zone.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Zone", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Zone, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "void Remove()", AS_METHODPR(Zone, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Zone, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void RemoveInstanceDefault()", AS_METHODPR(Zone, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void RemoveObjectAnimation()", AS_METHODPR(Zone, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void ResetToDefault()", AS_METHODPR(Zone, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "bool Save(Serializer&) const", AS_METHODPR(Zone, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool SaveDefaultAttributes() const", AS_METHODPR(Zone, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Zone, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "bool SaveXML(XMLElement&) const", AS_METHODPR(Zone, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void SendEvent(StringHash)", AS_METHODPR(Zone, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Zone, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Zone::SetAmbientColor(const Color& color) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetAmbientColor(const Color&in)", AS_METHODPR(Zone, SetAmbientColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_ambientColor(const Color&in)", AS_METHODPR(Zone, SetAmbientColor, (const Color&), void), AS_CALL_THISCALL);
    // void Zone::SetAmbientGradient(bool enable) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetAmbientGradient(bool)", AS_METHODPR(Zone, SetAmbientGradient, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_ambientGradient(bool)", AS_METHODPR(Zone, SetAmbientGradient, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetAnimationEnabled(bool)", AS_METHODPR(Zone, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_animationEnabled(bool)", AS_METHODPR(Zone, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetAnimationTime(float)", AS_METHODPR(Zone, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Zone, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Zone, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Zone, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Zone, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Zone, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Zone, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Zone, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetBasePass(uint)", AS_METHODPR(Zone, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void SetBlockEvents(bool)", AS_METHODPR(Zone, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Zone::SetBoundingBox(const BoundingBox& box) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetBoundingBox(const BoundingBox&in)", AS_METHODPR(Zone, SetBoundingBox, (const BoundingBox&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_boundingBox(const BoundingBox&in)", AS_METHODPR(Zone, SetBoundingBox, (const BoundingBox&), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetCastShadows(bool)", AS_METHODPR(Zone, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_castShadows(bool)", AS_METHODPR(Zone, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetDrawDistance(float)", AS_METHODPR(Zone, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_drawDistance(float)", AS_METHODPR(Zone, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "void SetEnabled(bool)", AS_METHODPR(Zone, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_enabled(bool)", AS_METHODPR(Zone, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Zone::SetFogColor(const Color& color) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetFogColor(const Color&in)", AS_METHODPR(Zone, SetFogColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogColor(const Color&in)", AS_METHODPR(Zone, SetFogColor, (const Color&), void), AS_CALL_THISCALL);
    // void Zone::SetFogEnd(float end) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetFogEnd(float)", AS_METHODPR(Zone, SetFogEnd, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogEnd(float)", AS_METHODPR(Zone, SetFogEnd, (float), void), AS_CALL_THISCALL);
    // void Zone::SetFogHeight(float height) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetFogHeight(float)", AS_METHODPR(Zone, SetFogHeight, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogHeight(float)", AS_METHODPR(Zone, SetFogHeight, (float), void), AS_CALL_THISCALL);
    // void Zone::SetFogHeightScale(float scale) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetFogHeightScale(float)", AS_METHODPR(Zone, SetFogHeightScale, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogHeightScale(float)", AS_METHODPR(Zone, SetFogHeightScale, (float), void), AS_CALL_THISCALL);
    // void Zone::SetFogStart(float start) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetFogStart(float)", AS_METHODPR(Zone, SetFogStart, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogStart(float)", AS_METHODPR(Zone, SetFogStart, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Zone, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Zone, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Zone::SetHeightFog(bool enable) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetHeightFog(bool)", AS_METHODPR(Zone, SetHeightFog, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_heightFog(bool)", AS_METHODPR(Zone, SetHeightFog, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void SetInstanceDefault(bool)", AS_METHODPR(Zone, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Zone, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetLightMask(uint)", AS_METHODPR(Zone, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_lightMask(uint)", AS_METHODPR(Zone, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetLodBias(float)", AS_METHODPR(Zone, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_lodBias(float)", AS_METHODPR(Zone, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetMaxLights(uint)", AS_METHODPR(Zone, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_maxLights(uint)", AS_METHODPR(Zone, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetMinMaxZ(float, float)", AS_METHODPR(Zone, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Zone, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Zone, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Zone, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetOccludee(bool)", AS_METHODPR(Zone, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_occludee(bool)", AS_METHODPR(Zone, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetOccluder(bool)", AS_METHODPR(Zone, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_occluder(bool)", AS_METHODPR(Zone, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void Zone::SetOverride(bool enable) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetOverride(bool)", AS_METHODPR(Zone, SetOverride, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_override(bool)", AS_METHODPR(Zone, SetOverride, (bool), void), AS_CALL_THISCALL);
    // void Zone::SetPriority(int priority) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetPriority(int)", AS_METHODPR(Zone, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_priority(int)", AS_METHODPR(Zone, SetPriority, (int), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetShadowDistance(float)", AS_METHODPR(Zone, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_shadowDistance(float)", AS_METHODPR(Zone, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetShadowMask(uint)", AS_METHODPR(Zone, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_shadowMask(uint)", AS_METHODPR(Zone, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetSortValue(float)", AS_METHODPR(Zone, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void SetTemporary(bool)", AS_METHODPR(Zone, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_temporary(bool)", AS_METHODPR(Zone, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetViewMask(uint)", AS_METHODPR(Zone, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_viewMask(uint)", AS_METHODPR(Zone, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetZone(Zone@+, bool = false)", AS_METHODPR(Zone, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetZoneMask(uint)", AS_METHODPR(Zone, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_zoneMask(uint)", AS_METHODPR(Zone, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Zone::SetZoneTexture(Texture* texture) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetZoneTexture(Texture@+)", AS_METHODPR(Zone, SetZoneTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_zoneTexture(Texture@+)", AS_METHODPR(Zone, SetZoneTexture, (Texture*), void), AS_CALL_THISCALL);
    // void Zone::SetZoneTextureAttr(const ResourceRef& value) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetZoneTextureAttr(const ResourceRef&in)", AS_METHODPR(Zone, SetZoneTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void UnsubscribeFromAllEvents()", AS_METHODPR(Zone, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Zone_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Zone, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Zone, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Zone, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void Update(const FrameInfo&in)", AS_METHODPR(Zone, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(Zone, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(Zone, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Zone", "int WeakRefs() const", AS_METHODPR(Zone, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "int get_weakRefs() const", AS_METHODPR(Zone, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Zone, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Zone, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Zone, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // explicit Zone::Zone(Context* context) | File: ../Graphics/Zone.h
    engine->RegisterObjectBehaviour("Zone", asBEHAVE_FACTORY, "Zone@+ f()", AS_FUNCTION(Zone_Zone_Context), AS_CALL_CDECL);
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(Zone, "Zone")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Zone, "Zone")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Zone, "Zone")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Zone, "Zone")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Zone, "Zone")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Zone, "Zone")
#endif
#ifdef REGISTER_MANUAL_PART_Zone
    REGISTER_MANUAL_PART_Zone(Zone, "Zone")
#endif
    RegisterSubclass<Drawable, Zone>(engine, "Drawable", "Zone");
    RegisterSubclass<Component, Zone>(engine, "Component", "Zone");
    RegisterSubclass<Animatable, Zone>(engine, "Animatable", "Zone");
    RegisterSubclass<Serializable, Zone>(engine, "Serializable", "Zone");
    RegisterSubclass<Object, Zone>(engine, "Object", "Zone");
    RegisterSubclass<RefCounted, Zone>(engine, "RefCounted", "Zone");

}

}
