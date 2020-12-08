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
static void Zone_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Zone* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// explicit Zone::Zone(Context* context) | File: ../Graphics/Zone.h
static Zone* Zone_Zone_Context()
{
    return new Zone(GetScriptContext());
}

void ASRegisterGenerated_Members_Z(asIScriptEngine* engine)
{
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void AddLight(Light@+)", asMETHODPR(Zone, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Zone", asBEHAVE_ADDREF, "void f()", asMETHODPR(Zone, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void AddVertexLight(Light@+)", asMETHODPR(Zone, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void AllocateNetworkState()", asMETHODPR(Zone, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void ApplyAttributes()", asMETHODPR(Zone, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Zone::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Zone, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(Zone, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // const Color& Zone::GetAmbientColor() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "const Color& GetAmbientColor() const", asMETHODPR(Zone, GetAmbientColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_ambientColor() const", asMETHODPR(Zone, GetAmbientColor, () const, const Color&), asCALL_THISCALL);
    // const Color& Zone::GetAmbientEndColor() | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "const Color& GetAmbientEndColor()", asMETHODPR(Zone, GetAmbientEndColor, (), const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_ambientEndColor()", asMETHODPR(Zone, GetAmbientEndColor, (), const Color&), asCALL_THISCALL);
    // bool Zone::GetAmbientGradient() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "bool GetAmbientGradient() const", asMETHODPR(Zone, GetAmbientGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_ambientGradient() const", asMETHODPR(Zone, GetAmbientGradient, () const, bool), asCALL_THISCALL);
    // const Color& Zone::GetAmbientStartColor() | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "const Color& GetAmbientStartColor()", asMETHODPR(Zone, GetAmbientStartColor, (), const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_ambientStartColor()", asMETHODPR(Zone, GetAmbientStartColor, (), const Color&), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "bool GetAnimationEnabled() const", asMETHODPR(Zone, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_animationEnabled() const", asMETHODPR(Zone, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "Variant GetAttribute(uint) const", asMETHODPR(Zone, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "Variant get_attributes(uint) const", asMETHODPR(Zone, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "Variant GetAttribute(const String&in) const", asMETHODPR(Zone, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Zone, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Zone, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Zone, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Zone, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "Variant GetAttributeDefault(uint) const", asMETHODPR(Zone, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "Variant get_attributeDefaults(uint) const", asMETHODPR(Zone, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Zone, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "bool GetBlockEvents() const", asMETHODPR(Zone, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "const BoundingBox& GetBoundingBox() const", asMETHODPR(Zone, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const BoundingBox& get_boundingBox() const", asMETHODPR(Zone, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool GetCastShadows() const", asMETHODPR(Zone, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_castShadows() const", asMETHODPR(Zone, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "const String& GetCategory() const", asMETHODPR(Zone, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const String& get_category() const", asMETHODPR(Zone, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "Component@+ GetComponent(StringHash) const", asMETHODPR(Zone, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    // float Drawable::GetDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetDistance() const", asMETHODPR(Zone, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint8 GetDrawableFlags() const", asMETHODPR(Zone, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetDrawDistance() const", asMETHODPR(Zone, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_drawDistance() const", asMETHODPR(Zone, GetDrawDistance, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "VariantMap& GetEventDataMap() const", asMETHODPR(Zone, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "Object@+ GetEventSender() const", asMETHODPR(Zone, GetEventSender, () const, Object*), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "Light@+ GetFirstLight() const", asMETHODPR(Zone, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // const Color& Zone::GetFogColor() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "const Color& GetFogColor() const", asMETHODPR(Zone, GetFogColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Color& get_fogColor() const", asMETHODPR(Zone, GetFogColor, () const, const Color&), asCALL_THISCALL);
    // float Zone::GetFogEnd() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "float GetFogEnd() const", asMETHODPR(Zone, GetFogEnd, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_fogEnd() const", asMETHODPR(Zone, GetFogEnd, () const, float), asCALL_THISCALL);
    // float Zone::GetFogHeight() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "float GetFogHeight() const", asMETHODPR(Zone, GetFogHeight, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_fogHeight() const", asMETHODPR(Zone, GetFogHeight, () const, float), asCALL_THISCALL);
    // float Zone::GetFogHeightScale() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "float GetFogHeightScale() const", asMETHODPR(Zone, GetFogHeightScale, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_fogHeightScale() const", asMETHODPR(Zone, GetFogHeightScale, () const, float), asCALL_THISCALL);
    // float Zone::GetFogStart() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "float GetFogStart() const", asMETHODPR(Zone, GetFogStart, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_fogStart() const", asMETHODPR(Zone, GetFogStart, () const, float), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Zone, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Zone, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "const VariantMap& GetGlobalVars() const", asMETHODPR(Zone, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const VariantMap& get_globalVars() const", asMETHODPR(Zone, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // bool Zone::GetHeightFog() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "bool GetHeightFog() const", asMETHODPR(Zone, GetHeightFog, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_heightFog() const", asMETHODPR(Zone, GetHeightFog, () const, bool), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "uint GetID() const", asMETHODPR(Zone, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_id() const", asMETHODPR(Zone, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Zone, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const Matrix3x4& Zone::GetInverseWorldTransform() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "const Matrix3x4& GetInverseWorldTransform() const", asMETHODPR(Zone, GetInverseWorldTransform, () const, const Matrix3x4&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const Matrix3x4& get_inverseWorldTransform() const", asMETHODPR(Zone, GetInverseWorldTransform, () const, const Matrix3x4&), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint GetLightMask() const", asMETHODPR(Zone, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_lightMask() const", asMETHODPR(Zone, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "Array<Light@>@ GetLights() const", asFUNCTION(Zone_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetLodBias() const", asMETHODPR(Zone, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_lodBias() const", asMETHODPR(Zone, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetLodDistance() const", asMETHODPR(Zone, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(Zone, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint GetMaxLights() const", asMETHODPR(Zone, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_maxLights() const", asMETHODPR(Zone, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetMaxZ() const", asMETHODPR(Zone, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetMinZ() const", asMETHODPR(Zone, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "Node@+ GetNode() const", asMETHODPR(Zone, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "Node@+ get_node() const", asMETHODPR(Zone, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "uint GetNumAttributes() const", asMETHODPR(Zone, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_numAttributes() const", asMETHODPR(Zone, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "uint GetNumNetworkAttributes() const", asMETHODPR(Zone, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint GetNumOccluderTriangles()", asMETHODPR(Zone, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Zone, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Zone, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Zone, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // bool Zone::GetOverride() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "bool GetOverride() const", asMETHODPR(Zone, GetOverride, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_override() const", asMETHODPR(Zone, GetOverride, () const, bool), asCALL_THISCALL);
    // int Zone::GetPriority() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "int GetPriority() const", asMETHODPR(Zone, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "int get_priority() const", asMETHODPR(Zone, GetPriority, () const, int), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "Scene@+ GetScene() const", asMETHODPR(Zone, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetShadowDistance() const", asMETHODPR(Zone, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "float get_shadowDistance() const", asMETHODPR(Zone, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint GetShadowMask() const", asMETHODPR(Zone, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_shadowMask() const", asMETHODPR(Zone, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "float GetSortValue() const", asMETHODPR(Zone, GetSortValue, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Zone, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "StringHash GetType() const", asMETHODPR(Zone, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "StringHash get_type() const", asMETHODPR(Zone, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "const String& GetTypeName() const", asMETHODPR(Zone, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const String& get_typeName() const", asMETHODPR(Zone, GetTypeName, () const, const String&), asCALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(Zone, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "Array<Light@>@ GetVertexLights() const", asFUNCTION(Zone_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint GetViewMask() const", asMETHODPR(Zone, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_viewMask() const", asMETHODPR(Zone, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(Zone, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(Zone, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "Zone@+ GetZone() const", asMETHODPR(Zone, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "Zone@+ get_zone() const", asMETHODPR(Zone, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "uint GetZoneMask() const", asMETHODPR(Zone, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "uint get_zoneMask() const", asMETHODPR(Zone, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // Texture* Zone::GetZoneTexture() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "Texture@+ GetZoneTexture() const", asMETHODPR(Zone, GetZoneTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "Texture@+ get_zoneTexture() const", asMETHODPR(Zone, GetZoneTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef Zone::GetZoneTextureAttr() const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "ResourceRef GetZoneTextureAttr() const", asMETHODPR(Zone, GetZoneTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool HasBasePass(uint) const", asMETHODPR(Zone, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "bool HasEventHandlers() const", asMETHODPR(Zone, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Zone, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Zone, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "bool IsEnabled() const", asMETHODPR(Zone, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_enabled() const", asMETHODPR(Zone, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "bool IsEnabledEffective() const", asMETHODPR(Zone, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_enabledEffective() const", asMETHODPR(Zone, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Zone::IsInside(const Vector3& point) const | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "bool IsInside(const Vector3&in) const", asMETHODPR(Zone, IsInside, (const Vector3&) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "bool IsInstanceOf(StringHash) const", asMETHODPR(Zone, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool IsInView() const", asMETHODPR(Zone, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_inView() const", asMETHODPR(Zone, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool IsInView(Camera@+) const", asMETHODPR(Zone, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(Zone, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool IsOccludee() const", asMETHODPR(Zone, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_occludee() const", asMETHODPR(Zone, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool IsOccluder() const", asMETHODPR(Zone, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_occluder() const", asMETHODPR(Zone, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "bool IsReplicated() const", asMETHODPR(Zone, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_replicated() const", asMETHODPR(Zone, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool IsTemporary() const", asMETHODPR(Zone, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool get_temporary() const", asMETHODPR(Zone, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "bool IsZoneDirty() const", asMETHODPR(Zone, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void LimitLights()", asMETHODPR(Zone, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void LimitVertexLights(bool)", asMETHODPR(Zone, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool Load(Deserializer&)", asMETHODPR(Zone, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Zone, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "bool LoadXML(const XMLElement&in)", asMETHODPR(Zone, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void MarkForUpdate()", asMETHODPR(Zone, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void MarkInView(const FrameInfo&in)", asMETHODPR(Zone, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void MarkInView(uint)", asMETHODPR(Zone, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "void MarkNetworkUpdate()", asMETHODPR(Zone, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Zone, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Zone, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Zone, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void OnSetEnabled()", asMETHODPR(Zone, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "void PrepareNetworkUpdate()", asMETHODPR(Zone, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Drawable::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) | File: ../Graphics/Drawable.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Zone, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Zone, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Zone", "int Refs() const", asMETHODPR(Zone, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "int get_refs() const", asMETHODPR(Zone, Refs, () const, int), asCALL_THISCALL);
    // static void Zone::RegisterObject(Context* context) | File: ../Graphics/Zone.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Zone", asBEHAVE_RELEASE, "void f()", asMETHODPR(Zone, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "void Remove()", asMETHODPR(Zone, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Zone, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void RemoveInstanceDefault()", asMETHODPR(Zone, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void RemoveObjectAnimation()", asMETHODPR(Zone, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void ResetToDefault()", asMETHODPR(Zone, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "bool Save(Serializer&) const", asMETHODPR(Zone, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool SaveDefaultAttributes() const", asMETHODPR(Zone, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "bool SaveJSON(JSONValue&) const", asMETHODPR(Zone, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "bool SaveXML(XMLElement&) const", asMETHODPR(Zone, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void SendEvent(StringHash)", asMETHODPR(Zone, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Zone, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Zone::SetAmbientColor(const Color& color) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetAmbientColor(const Color&in)", asMETHODPR(Zone, SetAmbientColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_ambientColor(const Color&in)", asMETHODPR(Zone, SetAmbientColor, (const Color&), void), asCALL_THISCALL);
    // void Zone::SetAmbientGradient(bool enable) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetAmbientGradient(bool)", asMETHODPR(Zone, SetAmbientGradient, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_ambientGradient(bool)", asMETHODPR(Zone, SetAmbientGradient, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetAnimationEnabled(bool)", asMETHODPR(Zone, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_animationEnabled(bool)", asMETHODPR(Zone, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetAnimationTime(float)", asMETHODPR(Zone, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Zone, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Zone, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Zone, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Zone, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Zone, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Zone, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Zone, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetBasePass(uint)", asMETHODPR(Zone, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void SetBlockEvents(bool)", asMETHODPR(Zone, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Zone::SetBoundingBox(const BoundingBox& box) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetBoundingBox(const BoundingBox&in)", asMETHODPR(Zone, SetBoundingBox, (const BoundingBox&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_boundingBox(const BoundingBox&in)", asMETHODPR(Zone, SetBoundingBox, (const BoundingBox&), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetCastShadows(bool)", asMETHODPR(Zone, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_castShadows(bool)", asMETHODPR(Zone, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetDrawDistance(float)", asMETHODPR(Zone, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_drawDistance(float)", asMETHODPR(Zone, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Zone", "void SetEnabled(bool)", asMETHODPR(Zone, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_enabled(bool)", asMETHODPR(Zone, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Zone::SetFogColor(const Color& color) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetFogColor(const Color&in)", asMETHODPR(Zone, SetFogColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogColor(const Color&in)", asMETHODPR(Zone, SetFogColor, (const Color&), void), asCALL_THISCALL);
    // void Zone::SetFogEnd(float end) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetFogEnd(float)", asMETHODPR(Zone, SetFogEnd, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogEnd(float)", asMETHODPR(Zone, SetFogEnd, (float), void), asCALL_THISCALL);
    // void Zone::SetFogHeight(float height) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetFogHeight(float)", asMETHODPR(Zone, SetFogHeight, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogHeight(float)", asMETHODPR(Zone, SetFogHeight, (float), void), asCALL_THISCALL);
    // void Zone::SetFogHeightScale(float scale) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetFogHeightScale(float)", asMETHODPR(Zone, SetFogHeightScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogHeightScale(float)", asMETHODPR(Zone, SetFogHeightScale, (float), void), asCALL_THISCALL);
    // void Zone::SetFogStart(float start) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetFogStart(float)", asMETHODPR(Zone, SetFogStart, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_fogStart(float)", asMETHODPR(Zone, SetFogStart, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Zone, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Zone, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Zone::SetHeightFog(bool enable) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetHeightFog(bool)", asMETHODPR(Zone, SetHeightFog, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_heightFog(bool)", asMETHODPR(Zone, SetHeightFog, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void SetInstanceDefault(bool)", asMETHODPR(Zone, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Zone, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetLightMask(uint)", asMETHODPR(Zone, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_lightMask(uint)", asMETHODPR(Zone, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetLodBias(float)", asMETHODPR(Zone, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_lodBias(float)", asMETHODPR(Zone, SetLodBias, (float), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetMaxLights(uint)", asMETHODPR(Zone, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_maxLights(uint)", asMETHODPR(Zone, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetMinMaxZ(float, float)", asMETHODPR(Zone, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Zone, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Zone, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Zone", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Zone, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetOccludee(bool)", asMETHODPR(Zone, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_occludee(bool)", asMETHODPR(Zone, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetOccluder(bool)", asMETHODPR(Zone, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_occluder(bool)", asMETHODPR(Zone, SetOccluder, (bool), void), asCALL_THISCALL);
    // void Zone::SetOverride(bool enable) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetOverride(bool)", asMETHODPR(Zone, SetOverride, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_override(bool)", asMETHODPR(Zone, SetOverride, (bool), void), asCALL_THISCALL);
    // void Zone::SetPriority(int priority) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetPriority(int)", asMETHODPR(Zone, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_priority(int)", asMETHODPR(Zone, SetPriority, (int), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetShadowDistance(float)", asMETHODPR(Zone, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_shadowDistance(float)", asMETHODPR(Zone, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetShadowMask(uint)", asMETHODPR(Zone, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_shadowMask(uint)", asMETHODPR(Zone, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetSortValue(float)", asMETHODPR(Zone, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void SetTemporary(bool)", asMETHODPR(Zone, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_temporary(bool)", asMETHODPR(Zone, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetViewMask(uint)", asMETHODPR(Zone, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_viewMask(uint)", asMETHODPR(Zone, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetZone(Zone@+, bool = false)", asMETHODPR(Zone, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void SetZoneMask(uint)", asMETHODPR(Zone, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_zoneMask(uint)", asMETHODPR(Zone, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Zone::SetZoneTexture(Texture* texture) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetZoneTexture(Texture@+)", asMETHODPR(Zone, SetZoneTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "void set_zoneTexture(Texture@+)", asMETHODPR(Zone, SetZoneTexture, (Texture*), void), asCALL_THISCALL);
    // void Zone::SetZoneTextureAttr(const ResourceRef& value) | File: ../Graphics/Zone.h
    engine->RegisterObjectMethod("Zone", "void SetZoneTextureAttr(const ResourceRef&in)", asMETHODPR(Zone, SetZoneTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void UnsubscribeFromAllEvents()", asMETHODPR(Zone, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Zone_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Zone, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Zone, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Zone", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Zone, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void Update(const FrameInfo&in)", asMETHODPR(Zone, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateBatches(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(Zone, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Zone", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(Zone, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Zone", "int WeakRefs() const", asMETHODPR(Zone, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Zone", "int get_weakRefs() const", asMETHODPR(Zone, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Zone, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Zone, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Zone", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Zone, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // explicit Zone::Zone(Context* context) | File: ../Graphics/Zone.h
    engine->RegisterObjectBehaviour("Zone", asBEHAVE_FACTORY, "Zone@+ f()", asFUNCTION(Zone_Zone_Context), asCALL_CDECL);
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
