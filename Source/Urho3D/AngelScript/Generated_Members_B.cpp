// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// explicit BillboardSet::BillboardSet(Context* context) | File: ../Graphics/BillboardSet.h
static BillboardSet* BillboardSet_BillboardSet_Context()
{
    return new BillboardSet(GetScriptContext());
}

// const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
static CScriptArray* BillboardSet_GetLights_void(BillboardSet* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* BillboardSet_GetVertexLights_void(BillboardSet* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void BillboardSet_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(BillboardSet* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// explicit BorderImage::BorderImage(Context* context) | File: ../UI/BorderImage.h
static BorderImage* BorderImage_BorderImage_Context()
{
    return new BorderImage(GetScriptContext());
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* BorderImage_GetChildren_void(BorderImage* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* BorderImage_GetChildren_bool(BorderImage* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* BorderImage_GetChildrenWithTag_String_bool(BorderImage* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* BorderImage_GetTags_void(BorderImage* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void BorderImage_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(BorderImage* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// BoundingBox::BoundingBox(const BoundingBox& box) noexcept | File: ../Math/BoundingBox.h
static void BoundingBox_BoundingBox_BoundingBox(BoundingBox* ptr, const BoundingBox &box)
{
    new(ptr) BoundingBox(box);
}

// explicit BoundingBox::BoundingBox(const Rect& rect) noexcept | File: ../Math/BoundingBox.h
static void BoundingBox_BoundingBox_Rect(BoundingBox* ptr, const Rect &rect)
{
    new(ptr) BoundingBox(rect);
}

// BoundingBox::BoundingBox(const Vector3& min, const Vector3& max) noexcept | File: ../Math/BoundingBox.h
static void BoundingBox_BoundingBox_Vector3_Vector3(BoundingBox* ptr, const Vector3 &min, const Vector3 &max)
{
    new(ptr) BoundingBox(min, max);
}

// BoundingBox::BoundingBox(float min, float max) noexcept | File: ../Math/BoundingBox.h
static void BoundingBox_BoundingBox_float_float(BoundingBox* ptr, float min, float max)
{
    new(ptr) BoundingBox(min, max);
}

// explicit BoundingBox::BoundingBox(const Frustum& frustum) | File: ../Math/BoundingBox.h
static void BoundingBox_BoundingBox_Frustum(BoundingBox* ptr, const Frustum &frustum)
{
    new(ptr) BoundingBox(frustum);
}

// explicit BoundingBox::BoundingBox(const Polyhedron& poly) | File: ../Math/BoundingBox.h
static void BoundingBox_BoundingBox_Polyhedron(BoundingBox* ptr, const Polyhedron &poly)
{
    new(ptr) BoundingBox(poly);
}

// explicit BoundingBox::BoundingBox(const Sphere& sphere) | File: ../Math/BoundingBox.h
static void BoundingBox_BoundingBox_Sphere(BoundingBox* ptr, const Sphere &sphere)
{
    new(ptr) BoundingBox(sphere);
}

// BufferedSoundStream::BufferedSoundStream() | File: ../Audio/BufferedSoundStream.h
static BufferedSoundStream* BufferedSoundStream_BufferedSoundStream_void()
{
    return new BufferedSoundStream();
}

// explicit Button::Button(Context* context) | File: ../UI/Button.h
static Button* Button_Button_Context()
{
    return new Button(GetScriptContext());
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* Button_GetChildren_void(Button* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* Button_GetChildren_bool(Button* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* Button_GetChildrenWithTag_String_bool(Button* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* Button_GetTags_void(Button* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Button_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Button* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// explicit Batch::Batch(const SourceBatch& rhs) | File: ../Graphics/Batch.h
static void Batch_Batch_SourceBatch(Batch* ptr, const SourceBatch &rhs)
{
    new(ptr) Batch(rhs);
}

// explicit BatchGroup::BatchGroup(const Batch& batch) | File: ../Graphics/Batch.h
static void BatchGroup_BatchGroup_Batch(BatchGroup* ptr, const Batch &batch)
{
    new(ptr) BatchGroup(batch);
}

// explicit BatchGroupKey::BatchGroupKey(const Batch& batch) | File: ../Graphics/Batch.h
static void BatchGroupKey_BatchGroupKey_Batch(BatchGroupKey* ptr, const Batch &batch)
{
    new(ptr) BatchGroupKey(batch);
}

// BiasParameters::BiasParameters(float constantBias, float slopeScaledBias, float normalOffset=0.0f) | File: ../Graphics/Light.h
static void BiasParameters_BiasParameters_float_float_float(BiasParameters* ptr, float constantBias, float slopeScaledBias, float normalOffset=0.0f)
{
    new(ptr) BiasParameters(constantBias, slopeScaledBias, normalOffset);
}

// Bone::Bone() | File: ../Graphics/Skeleton.h
static Bone* Bone_Bone_void()
{
    return new Bone();
}

void ASRegisterGenerated_Members_B(asIScriptEngine* engine)
{
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void AddLight(Light@+)", asMETHODPR(BillboardSet, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("BillboardSet", asBEHAVE_ADDREF, "void f()", asMETHODPR(BillboardSet, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void AddVertexLight(Light@+)", asMETHODPR(BillboardSet, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void AllocateNetworkState()", asMETHODPR(BillboardSet, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void ApplyAttributes()", asMETHODPR(BillboardSet, ApplyAttributes, (), void), asCALL_THISCALL);
    // explicit BillboardSet::BillboardSet(Context* context) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectBehaviour("BillboardSet", asBEHAVE_FACTORY, "BillboardSet@+ f()", asFUNCTION(BillboardSet_BillboardSet_Context), asCALL_CDECL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void BillboardSet::Commit() | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void Commit()", asMETHODPR(BillboardSet, Commit, (), void), asCALL_THISCALL);
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(BillboardSet, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(BillboardSet, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "bool GetAnimationEnabled() const", asMETHODPR(BillboardSet, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_animationEnabled() const", asMETHODPR(BillboardSet, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // float BillboardSet::GetAnimationLodBias() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "float GetAnimationLodBias() const", asMETHODPR(BillboardSet, GetAnimationLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "float get_animationLodBias() const", asMETHODPR(BillboardSet, GetAnimationLodBias, () const, float), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "Variant GetAttribute(uint) const", asMETHODPR(BillboardSet, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Variant get_attributes(uint) const", asMETHODPR(BillboardSet, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "Variant GetAttribute(const String&in) const", asMETHODPR(BillboardSet, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(BillboardSet, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(BillboardSet, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(BillboardSet, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(BillboardSet, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "Variant GetAttributeDefault(uint) const", asMETHODPR(BillboardSet, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Variant get_attributeDefaults(uint) const", asMETHODPR(BillboardSet, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(BillboardSet, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // Billboard* BillboardSet::GetBillboard(unsigned index) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "Billboard@+ GetBillboard(uint)", asMETHODPR(BillboardSet, GetBillboard, (unsigned), Billboard*), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Billboard@+ get_billboards(uint)", asMETHODPR(BillboardSet, GetBillboard, (unsigned), Billboard*), asCALL_THISCALL);
    // PODVector<Billboard>& BillboardSet::GetBillboards() | File: ../Graphics/BillboardSet.h
    // Error: type "PODVector<Billboard>&" can not automatically bind
    // VariantVector BillboardSet::GetBillboardsAttr() const | File: ../Graphics/BillboardSet.h
    // Error: type "VariantVector" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "bool GetBlockEvents() const", asMETHODPR(BillboardSet, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "const BoundingBox& GetBoundingBox() const", asMETHODPR(BillboardSet, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "const BoundingBox& get_boundingBox() const", asMETHODPR(BillboardSet, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool GetCastShadows() const", asMETHODPR(BillboardSet, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_castShadows() const", asMETHODPR(BillboardSet, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "const String& GetCategory() const", asMETHODPR(BillboardSet, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "const String& get_category() const", asMETHODPR(BillboardSet, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "Component@+ GetComponent(StringHash) const", asMETHODPR(BillboardSet, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("BillboardSet", "float GetDistance() const", asMETHODPR(BillboardSet, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint8 GetDrawableFlags() const", asMETHODPR(BillboardSet, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetDrawDistance() const", asMETHODPR(BillboardSet, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "float get_drawDistance() const", asMETHODPR(BillboardSet, GetDrawDistance, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "VariantMap& GetEventDataMap() const", asMETHODPR(BillboardSet, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "Object@+ GetEventSender() const", asMETHODPR(BillboardSet, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FaceCameraMode BillboardSet::GetFaceCameraMode() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "FaceCameraMode GetFaceCameraMode() const", asMETHODPR(BillboardSet, GetFaceCameraMode, () const, FaceCameraMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "FaceCameraMode get_faceCameraMode() const", asMETHODPR(BillboardSet, GetFaceCameraMode, () const, FaceCameraMode), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "Light@+ GetFirstLight() const", asMETHODPR(BillboardSet, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(BillboardSet, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "const Variant& get_globalVar(StringHash) const", asMETHODPR(BillboardSet, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "const VariantMap& GetGlobalVars() const", asMETHODPR(BillboardSet, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "const VariantMap& get_globalVars() const", asMETHODPR(BillboardSet, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetID() const", asMETHODPR(BillboardSet, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_id() const", asMETHODPR(BillboardSet, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(BillboardSet, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetLightMask() const", asMETHODPR(BillboardSet, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_lightMask() const", asMETHODPR(BillboardSet, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "Array<Light@>@ GetLights() const", asFUNCTION(BillboardSet_GetLights_void), asCALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetLodBias() const", asMETHODPR(BillboardSet, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "float get_lodBias() const", asMETHODPR(BillboardSet, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetLodDistance() const", asMETHODPR(BillboardSet, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(BillboardSet, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // Material* BillboardSet::GetMaterial() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "Material@+ GetMaterial() const", asMETHODPR(BillboardSet, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Material@+ get_material() const", asMETHODPR(BillboardSet, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BillboardSet::GetMaterialAttr() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "ResourceRef GetMaterialAttr() const", asMETHODPR(BillboardSet, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetMaxLights() const", asMETHODPR(BillboardSet, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_maxLights() const", asMETHODPR(BillboardSet, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetMaxZ() const", asMETHODPR(BillboardSet, GetMaxZ, () const, float), asCALL_THISCALL);
    // float BillboardSet::GetMinAngle() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "float GetMinAngle() const", asMETHODPR(BillboardSet, GetMinAngle, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "float get_minAngle() const", asMETHODPR(BillboardSet, GetMinAngle, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetMinZ() const", asMETHODPR(BillboardSet, GetMinZ, () const, float), asCALL_THISCALL);
    // const PODVector<unsigned char>& BillboardSet::GetNetBillboardsAttr() const | File: ../Graphics/BillboardSet.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "Node@+ GetNode() const", asMETHODPR(BillboardSet, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Node@+ get_node() const", asMETHODPR(BillboardSet, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetNumAttributes() const", asMETHODPR(BillboardSet, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_numAttributes() const", asMETHODPR(BillboardSet, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned BillboardSet::GetNumBillboards() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetNumBillboards() const", asMETHODPR(BillboardSet, GetNumBillboards, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_numBillboards() const", asMETHODPR(BillboardSet, GetNumBillboards, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetNumNetworkAttributes() const", asMETHODPR(BillboardSet, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetNumOccluderTriangles()", asMETHODPR(BillboardSet, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(BillboardSet, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(BillboardSet, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(BillboardSet, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "Scene@+ GetScene() const", asMETHODPR(BillboardSet, GetScene, () const, Scene*), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetShadowDistance() const", asMETHODPR(BillboardSet, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "float get_shadowDistance() const", asMETHODPR(BillboardSet, GetShadowDistance, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetShadowMask() const", asMETHODPR(BillboardSet, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_shadowMask() const", asMETHODPR(BillboardSet, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetSortValue() const", asMETHODPR(BillboardSet, GetSortValue, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(BillboardSet, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "StringHash GetType() const", asMETHODPR(BillboardSet, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "StringHash get_type() const", asMETHODPR(BillboardSet, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "const String& GetTypeName() const", asMETHODPR(BillboardSet, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "const String& get_typeName() const", asMETHODPR(BillboardSet, GetTypeName, () const, const String&), asCALL_THISCALL);
    // UpdateGeometryType BillboardSet::GetUpdateGeometryType() override | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(BillboardSet, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "Array<Light@>@ GetVertexLights() const", asFUNCTION(BillboardSet_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetViewMask() const", asMETHODPR(BillboardSet, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_viewMask() const", asMETHODPR(BillboardSet, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(BillboardSet, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(BillboardSet, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "Zone@+ GetZone() const", asMETHODPR(BillboardSet, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Zone@+ get_zone() const", asMETHODPR(BillboardSet, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetZoneMask() const", asMETHODPR(BillboardSet, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_zoneMask() const", asMETHODPR(BillboardSet, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool HasBasePass(uint) const", asMETHODPR(BillboardSet, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "bool HasEventHandlers() const", asMETHODPR(BillboardSet, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(BillboardSet, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(BillboardSet, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsEnabled() const", asMETHODPR(BillboardSet, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_enabled() const", asMETHODPR(BillboardSet, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsEnabledEffective() const", asMETHODPR(BillboardSet, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_enabledEffective() const", asMETHODPR(BillboardSet, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool BillboardSet::IsFixedScreenSize() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsFixedScreenSize() const", asMETHODPR(BillboardSet, IsFixedScreenSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_fixedScreenSize() const", asMETHODPR(BillboardSet, IsFixedScreenSize, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsInstanceOf(StringHash) const", asMETHODPR(BillboardSet, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsInView() const", asMETHODPR(BillboardSet, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_inView() const", asMETHODPR(BillboardSet, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsInView(Camera@+) const", asMETHODPR(BillboardSet, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(BillboardSet, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsOccludee() const", asMETHODPR(BillboardSet, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_occludee() const", asMETHODPR(BillboardSet, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsOccluder() const", asMETHODPR(BillboardSet, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_occluder() const", asMETHODPR(BillboardSet, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool BillboardSet::IsRelative() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsRelative() const", asMETHODPR(BillboardSet, IsRelative, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_relative() const", asMETHODPR(BillboardSet, IsRelative, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsReplicated() const", asMETHODPR(BillboardSet, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_replicated() const", asMETHODPR(BillboardSet, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool BillboardSet::IsScaled() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsScaled() const", asMETHODPR(BillboardSet, IsScaled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_scaled() const", asMETHODPR(BillboardSet, IsScaled, () const, bool), asCALL_THISCALL);
    // bool BillboardSet::IsSorted() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsSorted() const", asMETHODPR(BillboardSet, IsSorted, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_sorted() const", asMETHODPR(BillboardSet, IsSorted, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsTemporary() const", asMETHODPR(BillboardSet, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_temporary() const", asMETHODPR(BillboardSet, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsZoneDirty() const", asMETHODPR(BillboardSet, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void LimitLights()", asMETHODPR(BillboardSet, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void LimitVertexLights(bool)", asMETHODPR(BillboardSet, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool Load(Deserializer&)", asMETHODPR(BillboardSet, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "bool LoadJSON(const JSONValue&in)", asMETHODPR(BillboardSet, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "bool LoadXML(const XMLElement&in)", asMETHODPR(BillboardSet, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void MarkForUpdate()", asMETHODPR(BillboardSet, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void MarkInView(const FrameInfo&in)", asMETHODPR(BillboardSet, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void MarkInView(uint)", asMETHODPR(BillboardSet, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "void MarkNetworkUpdate()", asMETHODPR(BillboardSet, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(BillboardSet, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(BillboardSet, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(BillboardSet, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void OnSetEnabled()", asMETHODPR(BillboardSet, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "void PrepareNetworkUpdate()", asMETHODPR(BillboardSet, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void BillboardSet::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/BillboardSet.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(BillboardSet, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(BillboardSet, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("BillboardSet", "int Refs() const", asMETHODPR(BillboardSet, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "int get_refs() const", asMETHODPR(BillboardSet, Refs, () const, int), asCALL_THISCALL);
    // static void BillboardSet::RegisterObject(Context* context) | File: ../Graphics/BillboardSet.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("BillboardSet", asBEHAVE_RELEASE, "void f()", asMETHODPR(BillboardSet, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "void Remove()", asMETHODPR(BillboardSet, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(BillboardSet, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void RemoveInstanceDefault()", asMETHODPR(BillboardSet, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void RemoveObjectAnimation()", asMETHODPR(BillboardSet, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void ResetToDefault()", asMETHODPR(BillboardSet, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "bool Save(Serializer&) const", asMETHODPR(BillboardSet, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool SaveDefaultAttributes() const", asMETHODPR(BillboardSet, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "bool SaveJSON(JSONValue&) const", asMETHODPR(BillboardSet, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "bool SaveXML(XMLElement&) const", asMETHODPR(BillboardSet, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void SendEvent(StringHash)", asMETHODPR(BillboardSet, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(BillboardSet, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAnimationEnabled(bool)", asMETHODPR(BillboardSet, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_animationEnabled(bool)", asMETHODPR(BillboardSet, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void BillboardSet::SetAnimationLodBias(float bias) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAnimationLodBias(float)", asMETHODPR(BillboardSet, SetAnimationLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_animationLodBias(float)", asMETHODPR(BillboardSet, SetAnimationLodBias, (float), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAnimationTime(float)", asMETHODPR(BillboardSet, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(BillboardSet, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool set_attributes(uint, const Variant&in)", asMETHODPR(BillboardSet, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(BillboardSet, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(BillboardSet, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(BillboardSet, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(BillboardSet, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(BillboardSet, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetBasePass(uint)", asMETHODPR(BillboardSet, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void BillboardSet::SetBillboardsAttr(const VariantVector& value) | File: ../Graphics/BillboardSet.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void SetBlockEvents(bool)", asMETHODPR(BillboardSet, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetCastShadows(bool)", asMETHODPR(BillboardSet, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_castShadows(bool)", asMETHODPR(BillboardSet, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetDrawDistance(float)", asMETHODPR(BillboardSet, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_drawDistance(float)", asMETHODPR(BillboardSet, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "void SetEnabled(bool)", asMETHODPR(BillboardSet, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_enabled(bool)", asMETHODPR(BillboardSet, SetEnabled, (bool), void), asCALL_THISCALL);
    // void BillboardSet::SetFaceCameraMode(FaceCameraMode mode) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetFaceCameraMode(FaceCameraMode)", asMETHODPR(BillboardSet, SetFaceCameraMode, (FaceCameraMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_faceCameraMode(FaceCameraMode)", asMETHODPR(BillboardSet, SetFaceCameraMode, (FaceCameraMode), void), asCALL_THISCALL);
    // void BillboardSet::SetFixedScreenSize(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetFixedScreenSize(bool)", asMETHODPR(BillboardSet, SetFixedScreenSize, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_fixedScreenSize(bool)", asMETHODPR(BillboardSet, SetFixedScreenSize, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(BillboardSet, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(BillboardSet, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetInstanceDefault(bool)", asMETHODPR(BillboardSet, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(BillboardSet, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetLightMask(uint)", asMETHODPR(BillboardSet, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_lightMask(uint)", asMETHODPR(BillboardSet, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetLodBias(float)", asMETHODPR(BillboardSet, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_lodBias(float)", asMETHODPR(BillboardSet, SetLodBias, (float), void), asCALL_THISCALL);
    // void BillboardSet::SetMaterial(Material* material) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetMaterial(Material@+)", asMETHODPR(BillboardSet, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_material(Material@+)", asMETHODPR(BillboardSet, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BillboardSet::SetMaterialAttr(const ResourceRef& value) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(BillboardSet, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetMaxLights(uint)", asMETHODPR(BillboardSet, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_maxLights(uint)", asMETHODPR(BillboardSet, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void BillboardSet::SetMinAngle(float angle) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetMinAngle(float)", asMETHODPR(BillboardSet, SetMinAngle, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_minAngle(float)", asMETHODPR(BillboardSet, SetMinAngle, (float), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetMinMaxZ(float, float)", asMETHODPR(BillboardSet, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void BillboardSet::SetNetBillboardsAttr(const PODVector<unsigned char>& value) | File: ../Graphics/BillboardSet.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void BillboardSet::SetNumBillboards(unsigned num) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetNumBillboards(uint)", asMETHODPR(BillboardSet, SetNumBillboards, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_numBillboards(uint)", asMETHODPR(BillboardSet, SetNumBillboards, (unsigned), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(BillboardSet, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(BillboardSet, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(BillboardSet, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetOccludee(bool)", asMETHODPR(BillboardSet, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_occludee(bool)", asMETHODPR(BillboardSet, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetOccluder(bool)", asMETHODPR(BillboardSet, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_occluder(bool)", asMETHODPR(BillboardSet, SetOccluder, (bool), void), asCALL_THISCALL);
    // void BillboardSet::SetRelative(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetRelative(bool)", asMETHODPR(BillboardSet, SetRelative, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_relative(bool)", asMETHODPR(BillboardSet, SetRelative, (bool), void), asCALL_THISCALL);
    // void BillboardSet::SetScaled(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetScaled(bool)", asMETHODPR(BillboardSet, SetScaled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_scaled(bool)", asMETHODPR(BillboardSet, SetScaled, (bool), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetShadowDistance(float)", asMETHODPR(BillboardSet, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_shadowDistance(float)", asMETHODPR(BillboardSet, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetShadowMask(uint)", asMETHODPR(BillboardSet, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_shadowMask(uint)", asMETHODPR(BillboardSet, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void BillboardSet::SetSorted(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetSorted(bool)", asMETHODPR(BillboardSet, SetSorted, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_sorted(bool)", asMETHODPR(BillboardSet, SetSorted, (bool), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetSortValue(float)", asMETHODPR(BillboardSet, SetSortValue, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetTemporary(bool)", asMETHODPR(BillboardSet, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_temporary(bool)", asMETHODPR(BillboardSet, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetViewMask(uint)", asMETHODPR(BillboardSet, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_viewMask(uint)", asMETHODPR(BillboardSet, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetZone(Zone@+, bool = false)", asMETHODPR(BillboardSet, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetZoneMask(uint)", asMETHODPR(BillboardSet, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_zoneMask(uint)", asMETHODPR(BillboardSet, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void UnsubscribeFromAllEvents()", asMETHODPR(BillboardSet, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(BillboardSet_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(BillboardSet, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(BillboardSet, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(BillboardSet, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void Update(const FrameInfo&in)", asMETHODPR(BillboardSet, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // void BillboardSet::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(BillboardSet, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // void BillboardSet::UpdateGeometry(const FrameInfo& frame) override | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(BillboardSet, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("BillboardSet", "int WeakRefs() const", asMETHODPR(BillboardSet, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "int get_weakRefs() const", asMETHODPR(BillboardSet, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(BillboardSet, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(BillboardSet, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(BillboardSet, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(BillboardSet, "BillboardSet")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(BillboardSet, "BillboardSet")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(BillboardSet, "BillboardSet")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(BillboardSet, "BillboardSet")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(BillboardSet, "BillboardSet")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(BillboardSet, "BillboardSet")
#endif
#ifdef REGISTER_MANUAL_PART_BillboardSet
    REGISTER_MANUAL_PART_BillboardSet(BillboardSet, "BillboardSet")
#endif
    RegisterSubclass<Drawable, BillboardSet>(engine, "Drawable", "BillboardSet");
    RegisterSubclass<Component, BillboardSet>(engine, "Component", "BillboardSet");
    RegisterSubclass<Animatable, BillboardSet>(engine, "Animatable", "BillboardSet");
    RegisterSubclass<Serializable, BillboardSet>(engine, "Serializable", "BillboardSet");
    RegisterSubclass<Object, BillboardSet>(engine, "Object", "BillboardSet");
    RegisterSubclass<RefCounted, BillboardSet>(engine, "RefCounted", "BillboardSet");

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void AddChild(UIElement@+)", asMETHODPR(BorderImage, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("BorderImage", asBEHAVE_ADDREF, "void f()", asMETHODPR(BorderImage, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void AddTag(const String&in)", asMETHODPR(BorderImage, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void AddTags(const String&in, int8 = ';')", asMETHODPR(BorderImage, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void AdjustScissor(IntRect&)", asMETHODPR(BorderImage, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void AllocateNetworkState()", asMETHODPR(BorderImage, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void ApplyAttributes()", asMETHODPR(BorderImage, ApplyAttributes, (), void), asCALL_THISCALL);
    // explicit BorderImage::BorderImage(Context* context) | File: ../UI/BorderImage.h
    engine->RegisterObjectBehaviour("BorderImage", asBEHAVE_FACTORY, "BorderImage@+ f()", asFUNCTION(BorderImage_BorderImage_Context), asCALL_CDECL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void BringToFront()", asMETHODPR(BorderImage, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(BorderImage, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void DisableLayoutUpdate()", asMETHODPR(BorderImage, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(BorderImage, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void EnableLayoutUpdate()", asMETHODPR(BorderImage, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool FilterAttributes(XMLElement&) const", asMETHODPR(BorderImage, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "uint FindChild(UIElement@+) const", asMETHODPR(BorderImage, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "bool GetAnimationEnabled() const", asMETHODPR(BorderImage, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_animationEnabled() const", asMETHODPR(BorderImage, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const String& GetAppliedStyle() const", asMETHODPR(BorderImage, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const String& get_style() const", asMETHODPR(BorderImage, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "Variant GetAttribute(uint) const", asMETHODPR(BorderImage, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "Variant get_attributes(uint) const", asMETHODPR(BorderImage, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "Variant GetAttribute(const String&in) const", asMETHODPR(BorderImage, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(BorderImage, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(BorderImage, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(BorderImage, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(BorderImage, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "Variant GetAttributeDefault(uint) const", asMETHODPR(BorderImage, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "Variant get_attributeDefaults(uint) const", asMETHODPR(BorderImage, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(BorderImage, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/BorderImage.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "BlendMode GetBlendMode() const", asMETHODPR(BorderImage, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "BlendMode get_blendMode() const", asMETHODPR(BorderImage, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "bool GetBlockEvents() const", asMETHODPR(BorderImage, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "const IntRect& GetBorder() const", asMETHODPR(BorderImage, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntRect& get_border() const", asMETHODPR(BorderImage, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool GetBringToBack() const", asMETHODPR(BorderImage, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_bringToBack() const", asMETHODPR(BorderImage, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool GetBringToFront() const", asMETHODPR(BorderImage, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_bringToFront() const", asMETHODPR(BorderImage, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "const String& GetCategory() const", asMETHODPR(BorderImage, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const String& get_category() const", asMETHODPR(BorderImage, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ GetChild(uint) const", asMETHODPR(BorderImage, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ get_children(uint) const", asMETHODPR(BorderImage, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(BorderImage, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(BorderImage, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetChildOffset() const", asMETHODPR(BorderImage, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_childOffset() const", asMETHODPR(BorderImage, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "Array<UIElement@>@ GetChildren() const", asFUNCTION(BorderImage_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(BorderImage_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(BorderImage_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntRect& GetClipBorder() const", asMETHODPR(BorderImage, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntRect& get_clipBorder() const", asMETHODPR(BorderImage, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool GetClipChildren() const", asMETHODPR(BorderImage, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_clipChildren() const", asMETHODPR(BorderImage, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Color& GetColor(Corner) const", asMETHODPR(BorderImage, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const Color& get_colors(Corner) const", asMETHODPR(BorderImage, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Color& GetColorAttr() const", asMETHODPR(BorderImage, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "IntRect GetCombinedScreenRect()", asMETHODPR(BorderImage, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "IntRect get_combinedScreenRect()", asMETHODPR(BorderImage, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(BorderImage, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Color& GetDerivedColor() const", asMETHODPR(BorderImage, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "float GetDerivedOpacity() const", asMETHODPR(BorderImage, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "float get_derivedOpacity() const", asMETHODPR(BorderImage, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetDisabledOffset() const", asMETHODPR(BorderImage, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_disabledOffset() const", asMETHODPR(BorderImage, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(BorderImage, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(BorderImage, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "uint GetDragButtonCount() const", asMETHODPR(BorderImage, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "uint get_dragButtonCount() const", asMETHODPR(BorderImage, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(BorderImage, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(BorderImage, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(BorderImage, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ GetElementEventSender() const", asMETHODPR(BorderImage, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool GetEnableAnchor() const", asMETHODPR(BorderImage, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_enableAnchor() const", asMETHODPR(BorderImage, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "VariantMap& GetEventDataMap() const", asMETHODPR(BorderImage, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "Object@+ GetEventSender() const", asMETHODPR(BorderImage, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "FocusMode GetFocusMode() const", asMETHODPR(BorderImage, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "FocusMode get_focusMode() const", asMETHODPR(BorderImage, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(BorderImage, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const Variant& get_globalVar(StringHash) const", asMETHODPR(BorderImage, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "const VariantMap& GetGlobalVars() const", asMETHODPR(BorderImage, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const VariantMap& get_globalVars() const", asMETHODPR(BorderImage, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetHeight() const", asMETHODPR(BorderImage, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_height() const", asMETHODPR(BorderImage, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(BorderImage, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(BorderImage, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetHoverOffset() const", asMETHODPR(BorderImage, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_hoverOffset() const", asMETHODPR(BorderImage, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "const IntRect& GetImageBorder() const", asMETHODPR(BorderImage, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntRect& get_imageBorder() const", asMETHODPR(BorderImage, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "const IntRect& GetImageRect() const", asMETHODPR(BorderImage, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntRect& get_imageRect() const", asMETHODPR(BorderImage, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetIndent() const", asMETHODPR(BorderImage, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_indent() const", asMETHODPR(BorderImage, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetIndentSpacing() const", asMETHODPR(BorderImage, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_indentSpacing() const", asMETHODPR(BorderImage, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetIndentWidth() const", asMETHODPR(BorderImage, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_indentWidth() const", asMETHODPR(BorderImage, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(BorderImage, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntRect& GetLayoutBorder() const", asMETHODPR(BorderImage, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntRect& get_layoutBorder() const", asMETHODPR(BorderImage, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetLayoutElementMaxSize() const", asMETHODPR(BorderImage, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(BorderImage, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const Vector2& get_layoutFlexScale() const", asMETHODPR(BorderImage, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "LayoutMode GetLayoutMode() const", asMETHODPR(BorderImage, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "LayoutMode get_layoutMode() const", asMETHODPR(BorderImage, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetLayoutSpacing() const", asMETHODPR(BorderImage, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_layoutSpacing() const", asMETHODPR(BorderImage, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "Material@+ GetMaterial() const", asMETHODPR(BorderImage, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "Material@+ get_material() const", asMETHODPR(BorderImage, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "ResourceRef GetMaterialAttr() const", asMETHODPR(BorderImage, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Vector2& GetMaxAnchor() const", asMETHODPR(BorderImage, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const Vector2& get_maxAnchor() const", asMETHODPR(BorderImage, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetMaxHeight() const", asMETHODPR(BorderImage, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_maxHeight() const", asMETHODPR(BorderImage, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetMaxOffset() const", asMETHODPR(BorderImage, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_maxOffset() const", asMETHODPR(BorderImage, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetMaxSize() const", asMETHODPR(BorderImage, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_maxSize() const", asMETHODPR(BorderImage, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetMaxWidth() const", asMETHODPR(BorderImage, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_maxWidth() const", asMETHODPR(BorderImage, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Vector2& GetMinAnchor() const", asMETHODPR(BorderImage, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const Vector2& get_minAnchor() const", asMETHODPR(BorderImage, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetMinHeight() const", asMETHODPR(BorderImage, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_minHeight() const", asMETHODPR(BorderImage, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetMinOffset() const", asMETHODPR(BorderImage, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_minOffset() const", asMETHODPR(BorderImage, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetMinSize() const", asMETHODPR(BorderImage, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_minSize() const", asMETHODPR(BorderImage, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetMinWidth() const", asMETHODPR(BorderImage, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_minWidth() const", asMETHODPR(BorderImage, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const String& GetName() const", asMETHODPR(BorderImage, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const String& get_name() const", asMETHODPR(BorderImage, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "uint GetNumAttributes() const", asMETHODPR(BorderImage, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "uint get_numAttributes() const", asMETHODPR(BorderImage, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "uint GetNumChildren(bool = false) const", asMETHODPR(BorderImage, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "uint get_numChildren(bool = false) const", asMETHODPR(BorderImage, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "uint GetNumNetworkAttributes() const", asMETHODPR(BorderImage, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(BorderImage, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(BorderImage, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(BorderImage, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "float GetOpacity() const", asMETHODPR(BorderImage, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "float get_opacity() const", asMETHODPR(BorderImage, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ GetParent() const", asMETHODPR(BorderImage, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ get_parent() const", asMETHODPR(BorderImage, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Vector2& GetPivot() const", asMETHODPR(BorderImage, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const Vector2& get_pivot() const", asMETHODPR(BorderImage, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetPosition() const", asMETHODPR(BorderImage, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_position() const", asMETHODPR(BorderImage, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetPriority() const", asMETHODPR(BorderImage, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_priority() const", asMETHODPR(BorderImage, GetPriority, () const, int), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ GetRoot() const", asMETHODPR(BorderImage, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ get_root() const", asMETHODPR(BorderImage, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetScreenPosition() const", asMETHODPR(BorderImage, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_screenPosition() const", asMETHODPR(BorderImage, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetSize() const", asMETHODPR(BorderImage, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_size() const", asMETHODPR(BorderImage, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool GetSortChildren() const", asMETHODPR(BorderImage, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_sortChildren() const", asMETHODPR(BorderImage, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(BorderImage, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "Array<String>@ GetTags() const", asFUNCTION(BorderImage_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("BorderImage", "Array<String>@ get_tags() const", asFUNCTION(BorderImage_GetTags_void), asCALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "Texture@+ GetTexture() const", asMETHODPR(BorderImage, GetTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "Texture@+ get_texture() const", asMETHODPR(BorderImage, GetTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "ResourceRef GetTextureAttr() const", asMETHODPR(BorderImage, GetTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "TraversalMode GetTraversalMode() const", asMETHODPR(BorderImage, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "TraversalMode get_traversalMode() const", asMETHODPR(BorderImage, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "StringHash GetType() const", asMETHODPR(BorderImage, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "StringHash get_type() const", asMETHODPR(BorderImage, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "const String& GetTypeName() const", asMETHODPR(BorderImage, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const String& get_typeName() const", asMETHODPR(BorderImage, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool GetUseDerivedOpacity() const", asMETHODPR(BorderImage, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_useDerivedOpacity() const", asMETHODPR(BorderImage, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(BorderImage, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const VariantMap& GetVars() const", asMETHODPR(BorderImage, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(BorderImage, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(BorderImage, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetWidth() const", asMETHODPR(BorderImage, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_width() const", asMETHODPR(BorderImage, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool HasColorGradient() const", asMETHODPR(BorderImage, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_colorGradient() const", asMETHODPR(BorderImage, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "bool HasEventHandlers() const", asMETHODPR(BorderImage, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool HasFocus() const", asMETHODPR(BorderImage, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_focus() const", asMETHODPR(BorderImage, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(BorderImage, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(BorderImage, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool HasTag(const String&in) const", asMETHODPR(BorderImage, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void InsertChild(uint, UIElement@+)", asMETHODPR(BorderImage, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsChildOf(UIElement@+) const", asMETHODPR(BorderImage, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsEditable() const", asMETHODPR(BorderImage, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_editable() const", asMETHODPR(BorderImage, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsElementEventSender() const", asMETHODPR(BorderImage, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_elementEventSender() const", asMETHODPR(BorderImage, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsEnabled() const", asMETHODPR(BorderImage, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_enabled() const", asMETHODPR(BorderImage, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsEnabledSelf() const", asMETHODPR(BorderImage, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_enabledSelf() const", asMETHODPR(BorderImage, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsFixedHeight() const", asMETHODPR(BorderImage, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_fixedHeight() const", asMETHODPR(BorderImage, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsFixedSize() const", asMETHODPR(BorderImage, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_fixedSize() const", asMETHODPR(BorderImage, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsFixedWidth() const", asMETHODPR(BorderImage, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_fixedWidth() const", asMETHODPR(BorderImage, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsHovering() const", asMETHODPR(BorderImage, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_hovering() const", asMETHODPR(BorderImage, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsInside(IntVector2, bool)", asMETHODPR(BorderImage, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(BorderImage, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "bool IsInstanceOf(StringHash) const", asMETHODPR(BorderImage, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsInternal() const", asMETHODPR(BorderImage, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_internal() const", asMETHODPR(BorderImage, IsInternal, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsSelected() const", asMETHODPR(BorderImage, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_selected() const", asMETHODPR(BorderImage, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool IsTemporary() const", asMETHODPR(BorderImage, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_temporary() const", asMETHODPR(BorderImage, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "bool IsTiled() const", asMETHODPR(BorderImage, IsTiled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_tiled() const", asMETHODPR(BorderImage, IsTiled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsVisible() const", asMETHODPR(BorderImage, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_visible() const", asMETHODPR(BorderImage, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsVisibleEffective() const", asMETHODPR(BorderImage, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_visibleEffective() const", asMETHODPR(BorderImage, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsWheelHandler() const", asMETHODPR(BorderImage, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(BorderImage, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool Load(Deserializer&)", asMETHODPR(BorderImage, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(BorderImage, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "bool LoadJSON(const JSONValue&in)", asMETHODPR(BorderImage, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool LoadXML(const XMLElement&in)", asMETHODPR(BorderImage, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(BorderImage, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool LoadXML(Deserializer&)", asMETHODPR(BorderImage, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void MarkNetworkUpdate()", asMETHODPR(BorderImage, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(BorderImage, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(BorderImage, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(BorderImage, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(BorderImage, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(BorderImage, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(BorderImage, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool OnDragDropTest(UIElement@+)", asMETHODPR(BorderImage, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(BorderImage, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(BorderImage, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(BorderImage, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(BorderImage, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(BorderImage, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnIndentSet()", asMETHODPR(BorderImage, OnIndentSet, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(BorderImage, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnPositionSet(const IntVector2&in)", asMETHODPR(BorderImage, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(BorderImage, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(BorderImage, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnSetEditable()", asMETHODPR(BorderImage, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnTextInput(const String&in)", asMETHODPR(BorderImage, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(BorderImage, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(BorderImage, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(BorderImage, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("BorderImage", "int Refs() const", asMETHODPR(BorderImage, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_refs() const", asMETHODPR(BorderImage, Refs, () const, int), asCALL_THISCALL);
    // static void BorderImage::RegisterObject(Context* context) | File: ../UI/BorderImage.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("BorderImage", asBEHAVE_RELEASE, "void f()", asMETHODPR(BorderImage, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void Remove()", asMETHODPR(BorderImage, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveAllChildren()", asMETHODPR(BorderImage, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveAllTags()", asMETHODPR(BorderImage, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(BorderImage, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(BorderImage, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveChildAtIndex(uint)", asMETHODPR(BorderImage, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveInstanceDefault()", asMETHODPR(BorderImage, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveObjectAnimation()", asMETHODPR(BorderImage, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool RemoveTag(const String&in)", asMETHODPR(BorderImage, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void ResetDeepEnabled()", asMETHODPR(BorderImage, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void ResetToDefault()", asMETHODPR(BorderImage, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool Save(Serializer&) const", asMETHODPR(BorderImage, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool SaveDefaultAttributes() const", asMETHODPR(BorderImage, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "bool SaveJSON(JSONValue&) const", asMETHODPR(BorderImage, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool SaveXML(XMLElement&) const", asMETHODPR(BorderImage, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(BorderImage, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(BorderImage, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void SendEvent(StringHash)", asMETHODPR(BorderImage, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(BorderImage, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(BorderImage, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetAnimationEnabled(bool)", asMETHODPR(BorderImage, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_animationEnabled(bool)", asMETHODPR(BorderImage, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetAnimationTime(float)", asMETHODPR(BorderImage, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(BorderImage, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool set_attributes(uint, const Variant&in)", asMETHODPR(BorderImage, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(BorderImage, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(BorderImage, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(BorderImage, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(BorderImage, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(BorderImage, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetBlendMode(BlendMode)", asMETHODPR(BorderImage, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_blendMode(BlendMode)", asMETHODPR(BorderImage, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void SetBlockEvents(bool)", asMETHODPR(BorderImage, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetBorder(const IntRect&in)", asMETHODPR(BorderImage, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_border(const IntRect&in)", asMETHODPR(BorderImage, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetBringToBack(bool)", asMETHODPR(BorderImage, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_bringToBack(bool)", asMETHODPR(BorderImage, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetBringToFront(bool)", asMETHODPR(BorderImage, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_bringToFront(bool)", asMETHODPR(BorderImage, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetChildOffset(const IntVector2&in)", asMETHODPR(BorderImage, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetClipBorder(const IntRect&in)", asMETHODPR(BorderImage, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_clipBorder(const IntRect&in)", asMETHODPR(BorderImage, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetClipChildren(bool)", asMETHODPR(BorderImage, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_clipChildren(bool)", asMETHODPR(BorderImage, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetColor(const Color&in)", asMETHODPR(BorderImage, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_color(const Color&in)", asMETHODPR(BorderImage, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetColor(Corner, const Color&in)", asMETHODPR(BorderImage, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_colors(Corner, const Color&in)", asMETHODPR(BorderImage, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetDeepEnabled(bool)", asMETHODPR(BorderImage, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(BorderImage, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_defaultStyle(XMLFile@+)", asMETHODPR(BorderImage, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetDisabledOffset(const IntVector2&in)", asMETHODPR(BorderImage, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_disabledOffset(const IntVector2&in)", asMETHODPR(BorderImage, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetDisabledOffset(int, int)", asMETHODPR(BorderImage, SetDisabledOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(BorderImage, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(BorderImage, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetEditable(bool)", asMETHODPR(BorderImage, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_editable(bool)", asMETHODPR(BorderImage, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetElementEventSender(bool)", asMETHODPR(BorderImage, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_elementEventSender(bool)", asMETHODPR(BorderImage, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetEnableAnchor(bool)", asMETHODPR(BorderImage, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_enableAnchor(bool)", asMETHODPR(BorderImage, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetEnabled(bool)", asMETHODPR(BorderImage, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_enabled(bool)", asMETHODPR(BorderImage, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetEnabledRecursive(bool)", asMETHODPR(BorderImage, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetFixedHeight(int)", asMETHODPR(BorderImage, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetFixedSize(const IntVector2&in)", asMETHODPR(BorderImage, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetFixedSize(int, int)", asMETHODPR(BorderImage, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetFixedWidth(int)", asMETHODPR(BorderImage, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetFocus(bool)", asMETHODPR(BorderImage, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_focus(bool)", asMETHODPR(BorderImage, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetFocusMode(FocusMode)", asMETHODPR(BorderImage, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_focusMode(FocusMode)", asMETHODPR(BorderImage, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetFullImageRect()", asMETHODPR(BorderImage, SetFullImageRect, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(BorderImage, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(BorderImage, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetHeight(int)", asMETHODPR(BorderImage, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_height(int)", asMETHODPR(BorderImage, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(BorderImage, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(BorderImage, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetHovering(bool)", asMETHODPR(BorderImage, SetHovering, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetHoverOffset(const IntVector2&in)", asMETHODPR(BorderImage, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_hoverOffset(const IntVector2&in)", asMETHODPR(BorderImage, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetHoverOffset(int, int)", asMETHODPR(BorderImage, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetImageBorder(const IntRect&in)", asMETHODPR(BorderImage, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_imageBorder(const IntRect&in)", asMETHODPR(BorderImage, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetImageRect(const IntRect&in)", asMETHODPR(BorderImage, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_imageRect(const IntRect&in)", asMETHODPR(BorderImage, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetIndent(int)", asMETHODPR(BorderImage, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_indent(int)", asMETHODPR(BorderImage, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetIndentSpacing(int)", asMETHODPR(BorderImage, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_indentSpacing(int)", asMETHODPR(BorderImage, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void SetInstanceDefault(bool)", asMETHODPR(BorderImage, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(BorderImage, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetInternal(bool)", asMETHODPR(BorderImage, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_internal(bool)", asMETHODPR(BorderImage, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(BorderImage, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(BorderImage, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_layoutBorder(const IntRect&in)", asMETHODPR(BorderImage, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(BorderImage, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(BorderImage, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetLayoutMode(LayoutMode)", asMETHODPR(BorderImage, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_layoutMode(LayoutMode)", asMETHODPR(BorderImage, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetLayoutSpacing(int)", asMETHODPR(BorderImage, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_layoutSpacing(int)", asMETHODPR(BorderImage, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaterial(Material@+)", asMETHODPR(BorderImage, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_material(Material@+)", asMETHODPR(BorderImage, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(BorderImage, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(BorderImage, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_maxAnchor(const Vector2&in)", asMETHODPR(BorderImage, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxAnchor(float, float)", asMETHODPR(BorderImage, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxHeight(int)", asMETHODPR(BorderImage, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_maxHeight(int)", asMETHODPR(BorderImage, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(BorderImage, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_maxOffset(const IntVector2&in)", asMETHODPR(BorderImage, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxSize(const IntVector2&in)", asMETHODPR(BorderImage, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_maxSize(const IntVector2&in)", asMETHODPR(BorderImage, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxSize(int, int)", asMETHODPR(BorderImage, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxWidth(int)", asMETHODPR(BorderImage, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_maxWidth(int)", asMETHODPR(BorderImage, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinAnchor(const Vector2&in)", asMETHODPR(BorderImage, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_minAnchor(const Vector2&in)", asMETHODPR(BorderImage, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinAnchor(float, float)", asMETHODPR(BorderImage, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinHeight(int)", asMETHODPR(BorderImage, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_minHeight(int)", asMETHODPR(BorderImage, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinOffset(const IntVector2&in)", asMETHODPR(BorderImage, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_minOffset(const IntVector2&in)", asMETHODPR(BorderImage, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinSize(const IntVector2&in)", asMETHODPR(BorderImage, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_minSize(const IntVector2&in)", asMETHODPR(BorderImage, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinSize(int, int)", asMETHODPR(BorderImage, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinWidth(int)", asMETHODPR(BorderImage, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_minWidth(int)", asMETHODPR(BorderImage, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetName(const String&in)", asMETHODPR(BorderImage, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_name(const String&in)", asMETHODPR(BorderImage, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(BorderImage, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(BorderImage, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(BorderImage, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetOpacity(float)", asMETHODPR(BorderImage, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_opacity(float)", asMETHODPR(BorderImage, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(BorderImage, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetPivot(const Vector2&in)", asMETHODPR(BorderImage, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_pivot(const Vector2&in)", asMETHODPR(BorderImage, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetPivot(float, float)", asMETHODPR(BorderImage, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetPosition(const IntVector2&in)", asMETHODPR(BorderImage, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_position(const IntVector2&in)", asMETHODPR(BorderImage, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetPosition(int, int)", asMETHODPR(BorderImage, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetPriority(int)", asMETHODPR(BorderImage, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_priority(int)", asMETHODPR(BorderImage, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetRenderTexture(Texture2D@+)", asMETHODPR(BorderImage, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetSelected(bool)", asMETHODPR(BorderImage, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_selected(bool)", asMETHODPR(BorderImage, SetSelected, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetSize(const IntVector2&in)", asMETHODPR(BorderImage, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_size(const IntVector2&in)", asMETHODPR(BorderImage, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetSize(int, int)", asMETHODPR(BorderImage, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetSortChildren(bool)", asMETHODPR(BorderImage, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_sortChildren(bool)", asMETHODPR(BorderImage, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(BorderImage, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool SetStyle(const XMLElement&in)", asMETHODPR(BorderImage, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(BorderImage, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void SetTemporary(bool)", asMETHODPR(BorderImage, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_temporary(bool)", asMETHODPR(BorderImage, SetTemporary, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetTexture(Texture@+)", asMETHODPR(BorderImage, SetTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_texture(Texture@+)", asMETHODPR(BorderImage, SetTexture, (Texture*), void), asCALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetTextureAttr(const ResourceRef&in)", asMETHODPR(BorderImage, SetTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetTiled(bool)", asMETHODPR(BorderImage, SetTiled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_tiled(bool)", asMETHODPR(BorderImage, SetTiled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetTraversalMode(TraversalMode)", asMETHODPR(BorderImage, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_traversalMode(TraversalMode)", asMETHODPR(BorderImage, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetUseDerivedOpacity(bool)", asMETHODPR(BorderImage, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_useDerivedOpacity(bool)", asMETHODPR(BorderImage, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetVar(StringHash, const Variant&in)", asMETHODPR(BorderImage, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(BorderImage, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(BorderImage, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetVisible(bool)", asMETHODPR(BorderImage, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_visible(bool)", asMETHODPR(BorderImage, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetWidth(int)", asMETHODPR(BorderImage, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_width(int)", asMETHODPR(BorderImage, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SortChildren()", asMETHODPR(BorderImage, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void UnsubscribeFromAllEvents()", asMETHODPR(BorderImage, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(BorderImage_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(BorderImage, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(BorderImage, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(BorderImage, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void Update(float)", asMETHODPR(BorderImage, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void UpdateLayout()", asMETHODPR(BorderImage, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("BorderImage", "int WeakRefs() const", asMETHODPR(BorderImage, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_weakRefs() const", asMETHODPR(BorderImage, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(BorderImage, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(BorderImage, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(BorderImage, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(BorderImage, "BorderImage")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(BorderImage, "BorderImage")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(BorderImage, "BorderImage")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(BorderImage, "BorderImage")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(BorderImage, "BorderImage")
#endif
#ifdef REGISTER_MANUAL_PART_BorderImage
    REGISTER_MANUAL_PART_BorderImage(BorderImage, "BorderImage")
#endif
    RegisterSubclass<UIElement, BorderImage>(engine, "UIElement", "BorderImage");
    RegisterSubclass<Animatable, BorderImage>(engine, "Animatable", "BorderImage");
    RegisterSubclass<Serializable, BorderImage>(engine, "Serializable", "BorderImage");
    RegisterSubclass<Object, BorderImage>(engine, "Object", "BorderImage");
    RegisterSubclass<RefCounted, BorderImage>(engine, "RefCounted", "BorderImage");

    // float BoundingBox::dummyMax_ | File: ../Math/BoundingBox.h
    engine->RegisterObjectProperty("BoundingBox", "float dummyMax", offsetof(BoundingBox, dummyMax_));
    // float BoundingBox::dummyMin_ | File: ../Math/BoundingBox.h
    engine->RegisterObjectProperty("BoundingBox", "float dummyMin", offsetof(BoundingBox, dummyMin_));
    // Vector3 BoundingBox::max_ | File: ../Math/BoundingBox.h
    engine->RegisterObjectProperty("BoundingBox", "Vector3 max", offsetof(BoundingBox, max_));
    // Vector3 BoundingBox::min_ | File: ../Math/BoundingBox.h
    engine->RegisterObjectProperty("BoundingBox", "Vector3 min", offsetof(BoundingBox, min_));
    // BoundingBox::BoundingBox(const BoundingBox& box) noexcept | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", asFUNCTION(BoundingBox_BoundingBox_BoundingBox), asCALL_CDECL_OBJFIRST);
    // explicit BoundingBox::BoundingBox(const Rect& rect) noexcept | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", asFUNCTION(BoundingBox_BoundingBox_Rect), asCALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(const Vector3& min, const Vector3& max) noexcept | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(BoundingBox_BoundingBox_Vector3_Vector3), asCALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(float min, float max) noexcept | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(BoundingBox_BoundingBox_float_float), asCALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(const Vector3* vertices, unsigned count) | File: ../Math/BoundingBox.h
    // Error: type "const Vector3*" can not automatically bind
    // explicit BoundingBox::BoundingBox(const Frustum& frustum) | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", asFUNCTION(BoundingBox_BoundingBox_Frustum), asCALL_CDECL_OBJFIRST);
    // explicit BoundingBox::BoundingBox(const Polyhedron& poly) | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", asFUNCTION(BoundingBox_BoundingBox_Polyhedron), asCALL_CDECL_OBJFIRST);
    // explicit BoundingBox::BoundingBox(const Sphere& sphere) | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Sphere&in)", asFUNCTION(BoundingBox_BoundingBox_Sphere), asCALL_CDECL_OBJFIRST);
    // Vector3 BoundingBox::Center() const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Vector3 Center() const", asMETHODPR(BoundingBox, Center, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_center() const", asMETHODPR(BoundingBox, Center, () const, Vector3), asCALL_THISCALL);
    // void BoundingBox::Clear() | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Clear()", asMETHODPR(BoundingBox, Clear, (), void), asCALL_THISCALL);
    // void BoundingBox::Clip(const BoundingBox& box) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Clip(const BoundingBox&in)", asMETHODPR(BoundingBox, Clip, (const BoundingBox&), void), asCALL_THISCALL);
    // void BoundingBox::Define(const BoundingBox& box) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const BoundingBox&in)", asMETHODPR(BoundingBox, Define, (const BoundingBox&), void), asCALL_THISCALL);
    // void BoundingBox::Define(const Rect& rect) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Rect&in)", asMETHODPR(BoundingBox, Define, (const Rect&), void), asCALL_THISCALL);
    // void BoundingBox::Define(const Vector3& min, const Vector3& max) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Vector3&in, const Vector3&in)", asMETHODPR(BoundingBox, Define, (const Vector3&, const Vector3&), void), asCALL_THISCALL);
    // void BoundingBox::Define(float min, float max) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(float, float)", asMETHODPR(BoundingBox, Define, (float, float), void), asCALL_THISCALL);
    // void BoundingBox::Define(const Vector3& point) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Vector3&in)", asMETHODPR(BoundingBox, Define, (const Vector3&), void), asCALL_THISCALL);
    // void BoundingBox::Define(const Vector3* vertices, unsigned count) | File: ../Math/BoundingBox.h
    // Error: type "const Vector3*" can not automatically bind
    // void BoundingBox::Define(const Frustum& frustum) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Frustum&in)", asMETHODPR(BoundingBox, Define, (const Frustum&), void), asCALL_THISCALL);
    // void BoundingBox::Define(const Polyhedron& poly) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Polyhedron&in)", asMETHODPR(BoundingBox, Define, (const Polyhedron&), void), asCALL_THISCALL);
    // void BoundingBox::Define(const Sphere& sphere) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Sphere&in)", asMETHODPR(BoundingBox, Define, (const Sphere&), void), asCALL_THISCALL);
    // bool BoundingBox::Defined() const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "bool Defined() const", asMETHODPR(BoundingBox, Defined, () const, bool), asCALL_THISCALL);
    // float BoundingBox::DistanceToPoint(const Vector3& point) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "float DistanceToPoint(const Vector3&in) const", asMETHODPR(BoundingBox, DistanceToPoint, (const Vector3&) const, float), asCALL_THISCALL);
    // Vector3 BoundingBox::HalfSize() const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Vector3 HalfSize() const", asMETHODPR(BoundingBox, HalfSize, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_halfSize() const", asMETHODPR(BoundingBox, HalfSize, () const, Vector3), asCALL_THISCALL);
    // Intersection BoundingBox::IsInside(const Vector3& point) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const Vector3&in) const", asMETHODPR(BoundingBox, IsInside, (const Vector3&) const, Intersection), asCALL_THISCALL);
    // Intersection BoundingBox::IsInside(const BoundingBox& box) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const BoundingBox&in) const", asMETHODPR(BoundingBox, IsInside, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    // Intersection BoundingBox::IsInside(const Sphere& sphere) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const Sphere&in) const", asMETHODPR(BoundingBox, IsInside, (const Sphere&) const, Intersection), asCALL_THISCALL);
    // Intersection BoundingBox::IsInsideFast(const BoundingBox& box) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInsideFast(const BoundingBox&in) const", asMETHODPR(BoundingBox, IsInsideFast, (const BoundingBox&) const, Intersection), asCALL_THISCALL);
    // Intersection BoundingBox::IsInsideFast(const Sphere& sphere) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInsideFast(const Sphere&in) const", asMETHODPR(BoundingBox, IsInsideFast, (const Sphere&) const, Intersection), asCALL_THISCALL);
    // void BoundingBox::Merge(const Vector3& point) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Vector3&in)", asMETHODPR(BoundingBox, Merge, (const Vector3&), void), asCALL_THISCALL);
    // void BoundingBox::Merge(const BoundingBox& box) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const BoundingBox&in)", asMETHODPR(BoundingBox, Merge, (const BoundingBox&), void), asCALL_THISCALL);
    // void BoundingBox::Merge(const Vector3* vertices, unsigned count) | File: ../Math/BoundingBox.h
    // Error: type "const Vector3*" can not automatically bind
    // void BoundingBox::Merge(const Frustum& frustum) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Frustum&in)", asMETHODPR(BoundingBox, Merge, (const Frustum&), void), asCALL_THISCALL);
    // void BoundingBox::Merge(const Polyhedron& poly) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Polyhedron&in)", asMETHODPR(BoundingBox, Merge, (const Polyhedron&), void), asCALL_THISCALL);
    // void BoundingBox::Merge(const Sphere& sphere) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Sphere&in)", asMETHODPR(BoundingBox, Merge, (const Sphere&), void), asCALL_THISCALL);
    // BoundingBox& BoundingBox::operator=(const BoundingBox& rhs) noexcept | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox& opAssign(const BoundingBox&in)", asMETHODPR(BoundingBox, operator=, (const BoundingBox&), BoundingBox&), asCALL_THISCALL);
    // BoundingBox& BoundingBox::operator=(const Rect& rhs) noexcept | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox& opAssign(const Rect&in)", asMETHODPR(BoundingBox, operator=, (const Rect&), BoundingBox&), asCALL_THISCALL);
    // bool BoundingBox::operator==(const BoundingBox& rhs) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "bool opEquals(const BoundingBox&in) const", asMETHODPR(BoundingBox, operator==, (const BoundingBox&) const, bool), asCALL_THISCALL);
    // Rect BoundingBox::Projected(const Matrix4& projection) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Rect Projected(const Matrix4&in) const", asMETHODPR(BoundingBox, Projected, (const Matrix4&) const, Rect), asCALL_THISCALL);
    // Vector3 BoundingBox::Size() const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Vector3 Size() const", asMETHODPR(BoundingBox, Size, () const, Vector3), asCALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_size() const", asMETHODPR(BoundingBox, Size, () const, Vector3), asCALL_THISCALL);
    // String BoundingBox::ToString() const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "String ToString() const", asMETHODPR(BoundingBox, ToString, () const, String), asCALL_THISCALL);
    // void BoundingBox::Transform(const Matrix3& transform) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Transform(const Matrix3&in)", asMETHODPR(BoundingBox, Transform, (const Matrix3&), void), asCALL_THISCALL);
    // void BoundingBox::Transform(const Matrix3x4& transform) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Transform(const Matrix3x4&in)", asMETHODPR(BoundingBox, Transform, (const Matrix3x4&), void), asCALL_THISCALL);
    // BoundingBox BoundingBox::Transformed(const Matrix3& transform) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox Transformed(const Matrix3&in) const", asMETHODPR(BoundingBox, Transformed, (const Matrix3&) const, BoundingBox), asCALL_THISCALL);
    // BoundingBox BoundingBox::Transformed(const Matrix3x4& transform) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox Transformed(const Matrix3x4&in) const", asMETHODPR(BoundingBox, Transformed, (const Matrix3x4&) const, BoundingBox), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_BoundingBox
    REGISTER_MANUAL_PART_BoundingBox(BoundingBox, "BoundingBox")
#endif

    // void BufferedSoundStream::AddData(void* data, unsigned numBytes) | File: ../Audio/BufferedSoundStream.h
    // Error: type "void*" can not automatically bind
    // void BufferedSoundStream::AddData(const SharedArrayPtr<signed char>& data, unsigned numBytes) | File: ../Audio/BufferedSoundStream.h
    // Error: type "const SharedArrayPtr<signed char>&" can not automatically bind
    // void BufferedSoundStream::AddData(const SharedArrayPtr<signed short>& data, unsigned numBytes) | File: ../Audio/BufferedSoundStream.h
    // Error: type "const SharedArrayPtr<signed short>&" can not automatically bind
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("BufferedSoundStream", asBEHAVE_ADDREF, "void f()", asMETHODPR(BufferedSoundStream, AddRef, (), void), asCALL_THISCALL);
    // BufferedSoundStream::BufferedSoundStream() | File: ../Audio/BufferedSoundStream.h
    engine->RegisterObjectBehaviour("BufferedSoundStream", asBEHAVE_FACTORY, "BufferedSoundStream@+ f()", asFUNCTION(BufferedSoundStream_BufferedSoundStream_void), asCALL_CDECL);
    // void BufferedSoundStream::Clear() | File: ../Audio/BufferedSoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "void Clear()", asMETHODPR(BufferedSoundStream, Clear, (), void), asCALL_THISCALL);
    // float BufferedSoundStream::GetBufferLength() const | File: ../Audio/BufferedSoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "float GetBufferLength() const", asMETHODPR(BufferedSoundStream, GetBufferLength, () const, float), asCALL_THISCALL);
    // unsigned BufferedSoundStream::GetBufferNumBytes() const | File: ../Audio/BufferedSoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "uint GetBufferNumBytes() const", asMETHODPR(BufferedSoundStream, GetBufferNumBytes, () const, unsigned), asCALL_THISCALL);
    // unsigned BufferedSoundStream::GetData(signed char* dest, unsigned numBytes) override | File: ../Audio/BufferedSoundStream.h
    // Error: type "signed char*" can not automatically bind
    // float SoundStream::GetFrequency() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "float GetFrequency() const", asMETHODPR(BufferedSoundStream, GetFrequency, () const, float), asCALL_THISCALL);
    // unsigned SoundStream::GetIntFrequency() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "uint GetIntFrequency() const", asMETHODPR(BufferedSoundStream, GetIntFrequency, () const, unsigned), asCALL_THISCALL);
    // unsigned SoundStream::GetSampleSize() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "uint GetSampleSize() const", asMETHODPR(BufferedSoundStream, GetSampleSize, () const, unsigned), asCALL_THISCALL);
    // bool SoundStream::GetStopAtEnd() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "bool GetStopAtEnd() const", asMETHODPR(BufferedSoundStream, GetStopAtEnd, () const, bool), asCALL_THISCALL);
    // bool SoundStream::IsSixteenBit() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "bool IsSixteenBit() const", asMETHODPR(BufferedSoundStream, IsSixteenBit, () const, bool), asCALL_THISCALL);
    // bool SoundStream::IsStereo() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "bool IsStereo() const", asMETHODPR(BufferedSoundStream, IsStereo, () const, bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("BufferedSoundStream", "int Refs() const", asMETHODPR(BufferedSoundStream, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BufferedSoundStream", "int get_refs() const", asMETHODPR(BufferedSoundStream, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("BufferedSoundStream", asBEHAVE_RELEASE, "void f()", asMETHODPR(BufferedSoundStream, ReleaseRef, (), void), asCALL_THISCALL);
    // virtual bool SoundStream::Seek(unsigned sample_number) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "bool Seek(uint)", asMETHODPR(BufferedSoundStream, Seek, (unsigned), bool), asCALL_THISCALL);
    // void SoundStream::SetFormat(unsigned frequency, bool sixteenBit, bool stereo) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "void SetFormat(uint, bool, bool)", asMETHODPR(BufferedSoundStream, SetFormat, (unsigned, bool, bool), void), asCALL_THISCALL);
    // void SoundStream::SetStopAtEnd(bool enable) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "void SetStopAtEnd(bool)", asMETHODPR(BufferedSoundStream, SetStopAtEnd, (bool), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("BufferedSoundStream", "int WeakRefs() const", asMETHODPR(BufferedSoundStream, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("BufferedSoundStream", "int get_weakRefs() const", asMETHODPR(BufferedSoundStream, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_SoundStream
    REGISTER_MANUAL_PART_SoundStream(BufferedSoundStream, "BufferedSoundStream")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(BufferedSoundStream, "BufferedSoundStream")
#endif
#ifdef REGISTER_MANUAL_PART_BufferedSoundStream
    REGISTER_MANUAL_PART_BufferedSoundStream(BufferedSoundStream, "BufferedSoundStream")
#endif
    RegisterSubclass<SoundStream, BufferedSoundStream>(engine, "SoundStream", "BufferedSoundStream");
    RegisterSubclass<RefCounted, BufferedSoundStream>(engine, "RefCounted", "BufferedSoundStream");

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void AddChild(UIElement@+)", asMETHODPR(Button, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Button", asBEHAVE_ADDREF, "void f()", asMETHODPR(Button, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void AddTag(const String&in)", asMETHODPR(Button, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void AddTags(const String&in, int8 = ';')", asMETHODPR(Button, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void AdjustScissor(IntRect&)", asMETHODPR(Button, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void AllocateNetworkState()", asMETHODPR(Button, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void ApplyAttributes()", asMETHODPR(Button, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void BringToFront()", asMETHODPR(Button, BringToFront, (), void), asCALL_THISCALL);
    // explicit Button::Button(Context* context) | File: ../UI/Button.h
    engine->RegisterObjectBehaviour("Button", asBEHAVE_FACTORY, "Button@+ f()", asFUNCTION(Button_Button_Context), asCALL_CDECL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(Button, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void DisableLayoutUpdate()", asMETHODPR(Button, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(Button, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void EnableLayoutUpdate()", asMETHODPR(Button, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool FilterAttributes(XMLElement&) const", asMETHODPR(Button, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "uint FindChild(UIElement@+) const", asMETHODPR(Button, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "bool GetAnimationEnabled() const", asMETHODPR(Button, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_animationEnabled() const", asMETHODPR(Button, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const String& GetAppliedStyle() const", asMETHODPR(Button, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const String& get_style() const", asMETHODPR(Button, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "Variant GetAttribute(uint) const", asMETHODPR(Button, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "Variant get_attributes(uint) const", asMETHODPR(Button, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "Variant GetAttribute(const String&in) const", asMETHODPR(Button, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Button, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Button, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Button, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Button, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "Variant GetAttributeDefault(uint) const", asMETHODPR(Button, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "Variant get_attributeDefaults(uint) const", asMETHODPR(Button, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Button, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void Button::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Button.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "BlendMode GetBlendMode() const", asMETHODPR(Button, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "BlendMode get_blendMode() const", asMETHODPR(Button, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "bool GetBlockEvents() const", asMETHODPR(Button, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "const IntRect& GetBorder() const", asMETHODPR(Button, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntRect& get_border() const", asMETHODPR(Button, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool GetBringToBack() const", asMETHODPR(Button, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_bringToBack() const", asMETHODPR(Button, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool GetBringToFront() const", asMETHODPR(Button, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_bringToFront() const", asMETHODPR(Button, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "const String& GetCategory() const", asMETHODPR(Button, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const String& get_category() const", asMETHODPR(Button, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ GetChild(uint) const", asMETHODPR(Button, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "UIElement@+ get_children(uint) const", asMETHODPR(Button, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(Button, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(Button, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetChildOffset() const", asMETHODPR(Button, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_childOffset() const", asMETHODPR(Button, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "Array<UIElement@>@ GetChildren() const", asFUNCTION(Button_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(Button_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(Button_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntRect& GetClipBorder() const", asMETHODPR(Button, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntRect& get_clipBorder() const", asMETHODPR(Button, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool GetClipChildren() const", asMETHODPR(Button, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_clipChildren() const", asMETHODPR(Button, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Color& GetColor(Corner) const", asMETHODPR(Button, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const Color& get_colors(Corner) const", asMETHODPR(Button, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Color& GetColorAttr() const", asMETHODPR(Button, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "IntRect GetCombinedScreenRect()", asMETHODPR(Button, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "IntRect get_combinedScreenRect()", asMETHODPR(Button, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(Button, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Color& GetDerivedColor() const", asMETHODPR(Button, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "float GetDerivedOpacity() const", asMETHODPR(Button, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "float get_derivedOpacity() const", asMETHODPR(Button, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetDisabledOffset() const", asMETHODPR(Button, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_disabledOffset() const", asMETHODPR(Button, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(Button, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(Button, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "uint GetDragButtonCount() const", asMETHODPR(Button, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "uint get_dragButtonCount() const", asMETHODPR(Button, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(Button, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(Button, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(Button, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ GetElementEventSender() const", asMETHODPR(Button, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool GetEnableAnchor() const", asMETHODPR(Button, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_enableAnchor() const", asMETHODPR(Button, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "VariantMap& GetEventDataMap() const", asMETHODPR(Button, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "Object@+ GetEventSender() const", asMETHODPR(Button, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "FocusMode GetFocusMode() const", asMETHODPR(Button, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "FocusMode get_focusMode() const", asMETHODPR(Button, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Button, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Button, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "const VariantMap& GetGlobalVars() const", asMETHODPR(Button, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const VariantMap& get_globalVars() const", asMETHODPR(Button, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetHeight() const", asMETHODPR(Button, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_height() const", asMETHODPR(Button, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(Button, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(Button, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetHoverOffset() const", asMETHODPR(Button, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_hoverOffset() const", asMETHODPR(Button, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "const IntRect& GetImageBorder() const", asMETHODPR(Button, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntRect& get_imageBorder() const", asMETHODPR(Button, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "const IntRect& GetImageRect() const", asMETHODPR(Button, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntRect& get_imageRect() const", asMETHODPR(Button, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetIndent() const", asMETHODPR(Button, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_indent() const", asMETHODPR(Button, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetIndentSpacing() const", asMETHODPR(Button, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_indentSpacing() const", asMETHODPR(Button, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetIndentWidth() const", asMETHODPR(Button, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_indentWidth() const", asMETHODPR(Button, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Button, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntRect& GetLayoutBorder() const", asMETHODPR(Button, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntRect& get_layoutBorder() const", asMETHODPR(Button, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetLayoutElementMaxSize() const", asMETHODPR(Button, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(Button, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const Vector2& get_layoutFlexScale() const", asMETHODPR(Button, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "LayoutMode GetLayoutMode() const", asMETHODPR(Button, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "LayoutMode get_layoutMode() const", asMETHODPR(Button, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetLayoutSpacing() const", asMETHODPR(Button, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_layoutSpacing() const", asMETHODPR(Button, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "Material@+ GetMaterial() const", asMETHODPR(Button, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "Material@+ get_material() const", asMETHODPR(Button, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "ResourceRef GetMaterialAttr() const", asMETHODPR(Button, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Vector2& GetMaxAnchor() const", asMETHODPR(Button, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const Vector2& get_maxAnchor() const", asMETHODPR(Button, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetMaxHeight() const", asMETHODPR(Button, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_maxHeight() const", asMETHODPR(Button, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetMaxOffset() const", asMETHODPR(Button, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_maxOffset() const", asMETHODPR(Button, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetMaxSize() const", asMETHODPR(Button, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_maxSize() const", asMETHODPR(Button, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetMaxWidth() const", asMETHODPR(Button, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_maxWidth() const", asMETHODPR(Button, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Vector2& GetMinAnchor() const", asMETHODPR(Button, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const Vector2& get_minAnchor() const", asMETHODPR(Button, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetMinHeight() const", asMETHODPR(Button, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_minHeight() const", asMETHODPR(Button, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetMinOffset() const", asMETHODPR(Button, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_minOffset() const", asMETHODPR(Button, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetMinSize() const", asMETHODPR(Button, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_minSize() const", asMETHODPR(Button, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetMinWidth() const", asMETHODPR(Button, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_minWidth() const", asMETHODPR(Button, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const String& GetName() const", asMETHODPR(Button, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const String& get_name() const", asMETHODPR(Button, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "uint GetNumAttributes() const", asMETHODPR(Button, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "uint get_numAttributes() const", asMETHODPR(Button, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "uint GetNumChildren(bool = false) const", asMETHODPR(Button, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "uint get_numChildren(bool = false) const", asMETHODPR(Button, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "uint GetNumNetworkAttributes() const", asMETHODPR(Button, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Button, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Button, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Button, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "float GetOpacity() const", asMETHODPR(Button, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "float get_opacity() const", asMETHODPR(Button, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ GetParent() const", asMETHODPR(Button, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "UIElement@+ get_parent() const", asMETHODPR(Button, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Vector2& GetPivot() const", asMETHODPR(Button, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const Vector2& get_pivot() const", asMETHODPR(Button, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetPosition() const", asMETHODPR(Button, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_position() const", asMETHODPR(Button, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& Button::GetPressedChildOffset() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetPressedChildOffset() const", asMETHODPR(Button, GetPressedChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_pressedChildOffset() const", asMETHODPR(Button, GetPressedChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& Button::GetPressedOffset() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetPressedOffset() const", asMETHODPR(Button, GetPressedOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_pressedOffset() const", asMETHODPR(Button, GetPressedOffset, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetPriority() const", asMETHODPR(Button, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_priority() const", asMETHODPR(Button, GetPriority, () const, int), asCALL_THISCALL);
    // float Button::GetRepeatDelay() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "float GetRepeatDelay() const", asMETHODPR(Button, GetRepeatDelay, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "float get_repeatDelay() const", asMETHODPR(Button, GetRepeatDelay, () const, float), asCALL_THISCALL);
    // float Button::GetRepeatRate() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "float GetRepeatRate() const", asMETHODPR(Button, GetRepeatRate, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "float get_repeatRate() const", asMETHODPR(Button, GetRepeatRate, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ GetRoot() const", asMETHODPR(Button, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "UIElement@+ get_root() const", asMETHODPR(Button, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetScreenPosition() const", asMETHODPR(Button, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_screenPosition() const", asMETHODPR(Button, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetSize() const", asMETHODPR(Button, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_size() const", asMETHODPR(Button, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool GetSortChildren() const", asMETHODPR(Button, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_sortChildren() const", asMETHODPR(Button, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Button, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "Array<String>@ GetTags() const", asFUNCTION(Button_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Button", "Array<String>@ get_tags() const", asFUNCTION(Button_GetTags_void), asCALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "Texture@+ GetTexture() const", asMETHODPR(Button, GetTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "Texture@+ get_texture() const", asMETHODPR(Button, GetTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "ResourceRef GetTextureAttr() const", asMETHODPR(Button, GetTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "TraversalMode GetTraversalMode() const", asMETHODPR(Button, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "TraversalMode get_traversalMode() const", asMETHODPR(Button, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "StringHash GetType() const", asMETHODPR(Button, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "StringHash get_type() const", asMETHODPR(Button, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "const String& GetTypeName() const", asMETHODPR(Button, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const String& get_typeName() const", asMETHODPR(Button, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool GetUseDerivedOpacity() const", asMETHODPR(Button, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_useDerivedOpacity() const", asMETHODPR(Button, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(Button, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const VariantMap& GetVars() const", asMETHODPR(Button, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(Button, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(Button, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetWidth() const", asMETHODPR(Button, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_width() const", asMETHODPR(Button, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool HasColorGradient() const", asMETHODPR(Button, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_colorGradient() const", asMETHODPR(Button, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "bool HasEventHandlers() const", asMETHODPR(Button, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool HasFocus() const", asMETHODPR(Button, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_focus() const", asMETHODPR(Button, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Button, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Button, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool HasTag(const String&in) const", asMETHODPR(Button, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void InsertChild(uint, UIElement@+)", asMETHODPR(Button, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsChildOf(UIElement@+) const", asMETHODPR(Button, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsEditable() const", asMETHODPR(Button, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_editable() const", asMETHODPR(Button, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsElementEventSender() const", asMETHODPR(Button, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_elementEventSender() const", asMETHODPR(Button, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsEnabled() const", asMETHODPR(Button, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_enabled() const", asMETHODPR(Button, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsEnabledSelf() const", asMETHODPR(Button, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_enabledSelf() const", asMETHODPR(Button, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsFixedHeight() const", asMETHODPR(Button, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_fixedHeight() const", asMETHODPR(Button, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsFixedSize() const", asMETHODPR(Button, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_fixedSize() const", asMETHODPR(Button, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsFixedWidth() const", asMETHODPR(Button, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_fixedWidth() const", asMETHODPR(Button, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsHovering() const", asMETHODPR(Button, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_hovering() const", asMETHODPR(Button, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsInside(IntVector2, bool)", asMETHODPR(Button, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(Button, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "bool IsInstanceOf(StringHash) const", asMETHODPR(Button, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsInternal() const", asMETHODPR(Button, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_internal() const", asMETHODPR(Button, IsInternal, () const, bool), asCALL_THISCALL);
    // bool Button::IsPressed() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "bool IsPressed() const", asMETHODPR(Button, IsPressed, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_pressed() const", asMETHODPR(Button, IsPressed, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsSelected() const", asMETHODPR(Button, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_selected() const", asMETHODPR(Button, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool IsTemporary() const", asMETHODPR(Button, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_temporary() const", asMETHODPR(Button, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "bool IsTiled() const", asMETHODPR(Button, IsTiled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_tiled() const", asMETHODPR(Button, IsTiled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsVisible() const", asMETHODPR(Button, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_visible() const", asMETHODPR(Button, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsVisibleEffective() const", asMETHODPR(Button, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_visibleEffective() const", asMETHODPR(Button, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsWheelHandler() const", asMETHODPR(Button, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(Button, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool Load(Deserializer&)", asMETHODPR(Button, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Button, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Button, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool LoadXML(const XMLElement&in)", asMETHODPR(Button, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Button, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool LoadXML(Deserializer&)", asMETHODPR(Button, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void MarkNetworkUpdate()", asMETHODPR(Button, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // void Button::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Button, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // void Button::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(Button, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Button, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Button, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Button, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(Button, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool OnDragDropTest(UIElement@+)", asMETHODPR(Button, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Button, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // void Button::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Button, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Button, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Button, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Button, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnIndentSet()", asMETHODPR(Button, OnIndentSet, (), void), asCALL_THISCALL);
    // void Button::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(Button, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnPositionSet(const IntVector2&in)", asMETHODPR(Button, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(Button, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Button, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnSetEditable()", asMETHODPR(Button, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnTextInput(const String&in)", asMETHODPR(Button, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(Button, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Button, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Button, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Button", "int Refs() const", asMETHODPR(Button, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_refs() const", asMETHODPR(Button, Refs, () const, int), asCALL_THISCALL);
    // static void Button::RegisterObject(Context* context) | File: ../UI/Button.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Button", asBEHAVE_RELEASE, "void f()", asMETHODPR(Button, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void Remove()", asMETHODPR(Button, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void RemoveAllChildren()", asMETHODPR(Button, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void RemoveAllTags()", asMETHODPR(Button, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Button, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(Button, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void RemoveChildAtIndex(uint)", asMETHODPR(Button, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void RemoveInstanceDefault()", asMETHODPR(Button, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void RemoveObjectAnimation()", asMETHODPR(Button, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool RemoveTag(const String&in)", asMETHODPR(Button, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void ResetDeepEnabled()", asMETHODPR(Button, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void ResetToDefault()", asMETHODPR(Button, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool Save(Serializer&) const", asMETHODPR(Button, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool SaveDefaultAttributes() const", asMETHODPR(Button, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "bool SaveJSON(JSONValue&) const", asMETHODPR(Button, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool SaveXML(XMLElement&) const", asMETHODPR(Button, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(Button, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(Button, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void SendEvent(StringHash)", asMETHODPR(Button, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Button, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(Button, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetAnimationEnabled(bool)", asMETHODPR(Button, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_animationEnabled(bool)", asMETHODPR(Button, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetAnimationTime(float)", asMETHODPR(Button, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Button, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Button, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Button, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Button, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Button, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Button, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Button, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetBlendMode(BlendMode)", asMETHODPR(Button, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_blendMode(BlendMode)", asMETHODPR(Button, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void SetBlockEvents(bool)", asMETHODPR(Button, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetBorder(const IntRect&in)", asMETHODPR(Button, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_border(const IntRect&in)", asMETHODPR(Button, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetBringToBack(bool)", asMETHODPR(Button, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_bringToBack(bool)", asMETHODPR(Button, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetBringToFront(bool)", asMETHODPR(Button, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_bringToFront(bool)", asMETHODPR(Button, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetChildOffset(const IntVector2&in)", asMETHODPR(Button, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetClipBorder(const IntRect&in)", asMETHODPR(Button, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_clipBorder(const IntRect&in)", asMETHODPR(Button, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetClipChildren(bool)", asMETHODPR(Button, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_clipChildren(bool)", asMETHODPR(Button, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetColor(const Color&in)", asMETHODPR(Button, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_color(const Color&in)", asMETHODPR(Button, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetColor(Corner, const Color&in)", asMETHODPR(Button, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_colors(Corner, const Color&in)", asMETHODPR(Button, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetDeepEnabled(bool)", asMETHODPR(Button, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(Button, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_defaultStyle(XMLFile@+)", asMETHODPR(Button, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetDisabledOffset(const IntVector2&in)", asMETHODPR(Button, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_disabledOffset(const IntVector2&in)", asMETHODPR(Button, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetDisabledOffset(int, int)", asMETHODPR(Button, SetDisabledOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(Button, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(Button, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetEditable(bool)", asMETHODPR(Button, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_editable(bool)", asMETHODPR(Button, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetElementEventSender(bool)", asMETHODPR(Button, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_elementEventSender(bool)", asMETHODPR(Button, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetEnableAnchor(bool)", asMETHODPR(Button, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_enableAnchor(bool)", asMETHODPR(Button, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetEnabled(bool)", asMETHODPR(Button, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_enabled(bool)", asMETHODPR(Button, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetEnabledRecursive(bool)", asMETHODPR(Button, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetFixedHeight(int)", asMETHODPR(Button, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetFixedSize(const IntVector2&in)", asMETHODPR(Button, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetFixedSize(int, int)", asMETHODPR(Button, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetFixedWidth(int)", asMETHODPR(Button, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetFocus(bool)", asMETHODPR(Button, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_focus(bool)", asMETHODPR(Button, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetFocusMode(FocusMode)", asMETHODPR(Button, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_focusMode(FocusMode)", asMETHODPR(Button, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetFullImageRect()", asMETHODPR(Button, SetFullImageRect, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Button, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Button, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetHeight(int)", asMETHODPR(Button, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_height(int)", asMETHODPR(Button, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(Button, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(Button, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetHovering(bool)", asMETHODPR(Button, SetHovering, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetHoverOffset(const IntVector2&in)", asMETHODPR(Button, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_hoverOffset(const IntVector2&in)", asMETHODPR(Button, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetHoverOffset(int, int)", asMETHODPR(Button, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetImageBorder(const IntRect&in)", asMETHODPR(Button, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_imageBorder(const IntRect&in)", asMETHODPR(Button, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetImageRect(const IntRect&in)", asMETHODPR(Button, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_imageRect(const IntRect&in)", asMETHODPR(Button, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetIndent(int)", asMETHODPR(Button, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_indent(int)", asMETHODPR(Button, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetIndentSpacing(int)", asMETHODPR(Button, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_indentSpacing(int)", asMETHODPR(Button, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void SetInstanceDefault(bool)", asMETHODPR(Button, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Button, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetInternal(bool)", asMETHODPR(Button, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_internal(bool)", asMETHODPR(Button, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(Button, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(Button, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_layoutBorder(const IntRect&in)", asMETHODPR(Button, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(Button, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(Button, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetLayoutMode(LayoutMode)", asMETHODPR(Button, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_layoutMode(LayoutMode)", asMETHODPR(Button, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetLayoutSpacing(int)", asMETHODPR(Button, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_layoutSpacing(int)", asMETHODPR(Button, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetMaterial(Material@+)", asMETHODPR(Button, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_material(Material@+)", asMETHODPR(Button, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(Button, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(Button, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_maxAnchor(const Vector2&in)", asMETHODPR(Button, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxAnchor(float, float)", asMETHODPR(Button, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxHeight(int)", asMETHODPR(Button, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_maxHeight(int)", asMETHODPR(Button, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(Button, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_maxOffset(const IntVector2&in)", asMETHODPR(Button, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxSize(const IntVector2&in)", asMETHODPR(Button, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_maxSize(const IntVector2&in)", asMETHODPR(Button, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxSize(int, int)", asMETHODPR(Button, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxWidth(int)", asMETHODPR(Button, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_maxWidth(int)", asMETHODPR(Button, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinAnchor(const Vector2&in)", asMETHODPR(Button, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_minAnchor(const Vector2&in)", asMETHODPR(Button, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinAnchor(float, float)", asMETHODPR(Button, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinHeight(int)", asMETHODPR(Button, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_minHeight(int)", asMETHODPR(Button, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinOffset(const IntVector2&in)", asMETHODPR(Button, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_minOffset(const IntVector2&in)", asMETHODPR(Button, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinSize(const IntVector2&in)", asMETHODPR(Button, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_minSize(const IntVector2&in)", asMETHODPR(Button, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinSize(int, int)", asMETHODPR(Button, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinWidth(int)", asMETHODPR(Button, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_minWidth(int)", asMETHODPR(Button, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetName(const String&in)", asMETHODPR(Button, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_name(const String&in)", asMETHODPR(Button, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Button, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Button, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Button, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetOpacity(float)", asMETHODPR(Button, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_opacity(float)", asMETHODPR(Button, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(Button, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetPivot(const Vector2&in)", asMETHODPR(Button, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_pivot(const Vector2&in)", asMETHODPR(Button, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetPivot(float, float)", asMETHODPR(Button, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetPosition(const IntVector2&in)", asMETHODPR(Button, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_position(const IntVector2&in)", asMETHODPR(Button, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetPosition(int, int)", asMETHODPR(Button, SetPosition, (int, int), void), asCALL_THISCALL);
    // void Button::SetPressedChildOffset(const IntVector2& offset) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetPressedChildOffset(const IntVector2&in)", asMETHODPR(Button, SetPressedChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_pressedChildOffset(const IntVector2&in)", asMETHODPR(Button, SetPressedChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void Button::SetPressedChildOffset(int x, int y) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetPressedChildOffset(int, int)", asMETHODPR(Button, SetPressedChildOffset, (int, int), void), asCALL_THISCALL);
    // void Button::SetPressedOffset(const IntVector2& offset) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetPressedOffset(const IntVector2&in)", asMETHODPR(Button, SetPressedOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_pressedOffset(const IntVector2&in)", asMETHODPR(Button, SetPressedOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void Button::SetPressedOffset(int x, int y) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetPressedOffset(int, int)", asMETHODPR(Button, SetPressedOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetPriority(int)", asMETHODPR(Button, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_priority(int)", asMETHODPR(Button, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetRenderTexture(Texture2D@+)", asMETHODPR(Button, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void Button::SetRepeat(float delay, float rate) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetRepeat(float, float)", asMETHODPR(Button, SetRepeat, (float, float), void), asCALL_THISCALL);
    // void Button::SetRepeatDelay(float delay) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetRepeatDelay(float)", asMETHODPR(Button, SetRepeatDelay, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_repeatDelay(float)", asMETHODPR(Button, SetRepeatDelay, (float), void), asCALL_THISCALL);
    // void Button::SetRepeatRate(float rate) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetRepeatRate(float)", asMETHODPR(Button, SetRepeatRate, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_repeatRate(float)", asMETHODPR(Button, SetRepeatRate, (float), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetSelected(bool)", asMETHODPR(Button, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_selected(bool)", asMETHODPR(Button, SetSelected, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetSize(const IntVector2&in)", asMETHODPR(Button, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_size(const IntVector2&in)", asMETHODPR(Button, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetSize(int, int)", asMETHODPR(Button, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetSortChildren(bool)", asMETHODPR(Button, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_sortChildren(bool)", asMETHODPR(Button, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(Button, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool SetStyle(const XMLElement&in)", asMETHODPR(Button, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(Button, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void SetTemporary(bool)", asMETHODPR(Button, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_temporary(bool)", asMETHODPR(Button, SetTemporary, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetTexture(Texture@+)", asMETHODPR(Button, SetTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_texture(Texture@+)", asMETHODPR(Button, SetTexture, (Texture*), void), asCALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetTextureAttr(const ResourceRef&in)", asMETHODPR(Button, SetTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetTiled(bool)", asMETHODPR(Button, SetTiled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_tiled(bool)", asMETHODPR(Button, SetTiled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetTraversalMode(TraversalMode)", asMETHODPR(Button, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_traversalMode(TraversalMode)", asMETHODPR(Button, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetUseDerivedOpacity(bool)", asMETHODPR(Button, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_useDerivedOpacity(bool)", asMETHODPR(Button, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetVar(StringHash, const Variant&in)", asMETHODPR(Button, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(Button, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(Button, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetVisible(bool)", asMETHODPR(Button, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_visible(bool)", asMETHODPR(Button, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetWidth(int)", asMETHODPR(Button, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_width(int)", asMETHODPR(Button, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SortChildren()", asMETHODPR(Button, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void UnsubscribeFromAllEvents()", asMETHODPR(Button, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Button_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Button, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Button, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Button, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void Button::Update(float timeStep) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void Update(float)", asMETHODPR(Button, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void UpdateLayout()", asMETHODPR(Button, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Button", "int WeakRefs() const", asMETHODPR(Button, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_weakRefs() const", asMETHODPR(Button, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Button, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Button, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Button, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_BorderImage
    REGISTER_MANUAL_PART_BorderImage(Button, "Button")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(Button, "Button")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Button, "Button")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Button, "Button")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Button, "Button")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Button, "Button")
#endif
#ifdef REGISTER_MANUAL_PART_Button
    REGISTER_MANUAL_PART_Button(Button, "Button")
#endif
    RegisterSubclass<BorderImage, Button>(engine, "BorderImage", "Button");
    RegisterSubclass<UIElement, Button>(engine, "UIElement", "Button");
    RegisterSubclass<Animatable, Button>(engine, "Animatable", "Button");
    RegisterSubclass<Serializable, Button>(engine, "Serializable", "Button");
    RegisterSubclass<Object, Button>(engine, "Object", "Button");
    RegisterSubclass<RefCounted, Button>(engine, "RefCounted", "Button");

    // HashSet<Pair<StringHash, StringHash> > BackgroundLoadItem::dependencies_ | File: ../Resource/BackgroundLoader.h
    // Error: type "HashSet<Pair<StringHash, StringHash>>" can not automatically bind
    // HashSet<Pair<StringHash, StringHash> > BackgroundLoadItem::dependents_ | File: ../Resource/BackgroundLoader.h
    // Error: type "HashSet<Pair<StringHash, StringHash>>" can not automatically bind
    // SharedPtr<Resource> BackgroundLoadItem::resource_ | File: ../Resource/BackgroundLoader.h
    // Error: type "SharedPtr<Resource>" can not automatically bind
    // bool BackgroundLoadItem::sendEventOnFailure_ | File: ../Resource/BackgroundLoader.h
    engine->RegisterObjectProperty("BackgroundLoadItem", "bool sendEventOnFailure", offsetof(BackgroundLoadItem, sendEventOnFailure_));
    // BackgroundLoadItem& BackgroundLoadItem::operator=(const BackgroundLoadItem&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<BackgroundLoadItem>(engine, "BackgroundLoadItem");
#ifdef REGISTER_MANUAL_PART_BackgroundLoadItem
    REGISTER_MANUAL_PART_BackgroundLoadItem(BackgroundLoadItem, "BackgroundLoadItem")
#endif

    // float Batch::distance_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("Batch", "float distance", offsetof(Batch, distance_));
    // Geometry* Batch::geometry_ | File: ../Graphics/Batch.h
    // Geometry* can not be registered
    // GeometryType Batch::geometryType_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("Batch", "GeometryType geometryType", offsetof(Batch, geometryType_));
    // void* Batch::instancingData_ | File: ../Graphics/Batch.h
    // void* can not be registered
    // bool Batch::isBase_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("Batch", "bool isBase", offsetof(Batch, isBase_));
    // unsigned char Batch::lightMask_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("Batch", "uint8 lightMask", offsetof(Batch, lightMask_));
    // LightBatchQueue* Batch::lightQueue_ | File: ../Graphics/Batch.h
    // LightBatchQueue* can not be registered
    // Material* Batch::material_ | File: ../Graphics/Batch.h
    // Material* can not be registered
    // unsigned Batch::numWorldTransforms_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("Batch", "uint numWorldTransforms", offsetof(Batch, numWorldTransforms_));
    // Pass* Batch::pass_ | File: ../Graphics/Batch.h
    // Pass* can not be registered
    // ShaderVariation* Batch::pixelShader_ | File: ../Graphics/Batch.h
    // ShaderVariation* can not be registered
    // unsigned char Batch::renderOrder_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("Batch", "uint8 renderOrder", offsetof(Batch, renderOrder_));
    // unsigned long long Batch::sortKey_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("Batch", "uint64 sortKey", offsetof(Batch, sortKey_));
    // ShaderVariation* Batch::vertexShader_ | File: ../Graphics/Batch.h
    // ShaderVariation* can not be registered
    // const Matrix3x4* Batch::worldTransform_ | File: ../Graphics/Batch.h
    // const Matrix3x4* can not be registered
    // Zone* Batch::zone_ | File: ../Graphics/Batch.h
    // Zone* can not be registered
    // explicit Batch::Batch(const SourceBatch& rhs) | File: ../Graphics/Batch.h
    engine->RegisterObjectBehaviour("Batch", asBEHAVE_CONSTRUCT, "void f(const SourceBatch&in)", asFUNCTION(Batch_Batch_SourceBatch), asCALL_CDECL_OBJFIRST);
    // void Batch::CalculateSortKey() | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("Batch", "void CalculateSortKey()", asMETHODPR(Batch, CalculateSortKey, (), void), asCALL_THISCALL);
    // void Batch::Draw(View* view, Camera* camera, bool allowDepthWrite) const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("Batch", "void Draw(View@+, Camera@+, bool) const", asMETHODPR(Batch, Draw, (View*, Camera*, bool) const, void), asCALL_THISCALL);
    // void Batch::Prepare(View* view, Camera* camera, bool setModelTransform, bool allowDepthWrite) const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("Batch", "void Prepare(View@+, Camera@+, bool, bool) const", asMETHODPR(Batch, Prepare, (View*, Camera*, bool, bool) const, void), asCALL_THISCALL);
    // Batch& Batch::operator=(const Batch&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Batch>(engine, "Batch");
#ifdef REGISTER_MANUAL_PART_Batch
    REGISTER_MANUAL_PART_Batch(Batch, "Batch")
#endif

    // float Batch::distance_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchGroup", "float distance", offsetof(BatchGroup, distance_));
    // Geometry* Batch::geometry_ | File: ../Graphics/Batch.h
    // Geometry* can not be registered
    // GeometryType Batch::geometryType_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchGroup", "GeometryType geometryType", offsetof(BatchGroup, geometryType_));
    // PODVector<InstanceData> BatchGroup::instances_ | File: ../Graphics/Batch.h
    // Error: type "PODVector<InstanceData>" can not automatically bind
    // void* Batch::instancingData_ | File: ../Graphics/Batch.h
    // void* can not be registered
    // bool Batch::isBase_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchGroup", "bool isBase", offsetof(BatchGroup, isBase_));
    // unsigned char Batch::lightMask_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchGroup", "uint8 lightMask", offsetof(BatchGroup, lightMask_));
    // LightBatchQueue* Batch::lightQueue_ | File: ../Graphics/Batch.h
    // LightBatchQueue* can not be registered
    // Material* Batch::material_ | File: ../Graphics/Batch.h
    // Material* can not be registered
    // unsigned Batch::numWorldTransforms_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchGroup", "uint numWorldTransforms", offsetof(BatchGroup, numWorldTransforms_));
    // Pass* Batch::pass_ | File: ../Graphics/Batch.h
    // Pass* can not be registered
    // ShaderVariation* Batch::pixelShader_ | File: ../Graphics/Batch.h
    // ShaderVariation* can not be registered
    // unsigned char Batch::renderOrder_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchGroup", "uint8 renderOrder", offsetof(BatchGroup, renderOrder_));
    // unsigned long long Batch::sortKey_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchGroup", "uint64 sortKey", offsetof(BatchGroup, sortKey_));
    // unsigned BatchGroup::startIndex_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchGroup", "uint startIndex", offsetof(BatchGroup, startIndex_));
    // ShaderVariation* Batch::vertexShader_ | File: ../Graphics/Batch.h
    // ShaderVariation* can not be registered
    // const Matrix3x4* Batch::worldTransform_ | File: ../Graphics/Batch.h
    // const Matrix3x4* can not be registered
    // Zone* Batch::zone_ | File: ../Graphics/Batch.h
    // Zone* can not be registered
    // void BatchGroup::AddTransforms(const Batch& batch) | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchGroup", "void AddTransforms(const Batch&in)", asMETHODPR(BatchGroup, AddTransforms, (const Batch&), void), asCALL_THISCALL);
    // explicit BatchGroup::BatchGroup(const Batch& batch) | File: ../Graphics/Batch.h
    engine->RegisterObjectBehaviour("BatchGroup", asBEHAVE_CONSTRUCT, "void f(const Batch&in)", asFUNCTION(BatchGroup_BatchGroup_Batch), asCALL_CDECL_OBJFIRST);
    // void Batch::CalculateSortKey() | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchGroup", "void CalculateSortKey()", asMETHODPR(BatchGroup, CalculateSortKey, (), void), asCALL_THISCALL);
    // void BatchGroup::Draw(View* view, Camera* camera, bool allowDepthWrite) const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchGroup", "void Draw(View@+, Camera@+, bool) const", asMETHODPR(BatchGroup, Draw, (View*, Camera*, bool) const, void), asCALL_THISCALL);
    // void Batch::Prepare(View* view, Camera* camera, bool setModelTransform, bool allowDepthWrite) const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchGroup", "void Prepare(View@+, Camera@+, bool, bool) const", asMETHODPR(BatchGroup, Prepare, (View*, Camera*, bool, bool) const, void), asCALL_THISCALL);
    // void BatchGroup::SetInstancingData(void* lockedData, unsigned stride, unsigned& freeIndex) | File: ../Graphics/Batch.h
    // Error: type "void*" can not automatically bind
    // BatchGroup& BatchGroup::operator=(const BatchGroup&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<BatchGroup>(engine, "BatchGroup");
#ifdef REGISTER_MANUAL_PART_Batch
    REGISTER_MANUAL_PART_Batch(BatchGroup, "BatchGroup")
#endif
#ifdef REGISTER_MANUAL_PART_BatchGroup
    REGISTER_MANUAL_PART_BatchGroup(BatchGroup, "BatchGroup")
#endif

    // Geometry* BatchGroupKey::geometry_ | File: ../Graphics/Batch.h
    // Geometry* can not be registered
    // LightBatchQueue* BatchGroupKey::lightQueue_ | File: ../Graphics/Batch.h
    // LightBatchQueue* can not be registered
    // Material* BatchGroupKey::material_ | File: ../Graphics/Batch.h
    // Material* can not be registered
    // Pass* BatchGroupKey::pass_ | File: ../Graphics/Batch.h
    // Pass* can not be registered
    // unsigned char BatchGroupKey::renderOrder_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchGroupKey", "uint8 renderOrder", offsetof(BatchGroupKey, renderOrder_));
    // Zone* BatchGroupKey::zone_ | File: ../Graphics/Batch.h
    // Zone* can not be registered
    // explicit BatchGroupKey::BatchGroupKey(const Batch& batch) | File: ../Graphics/Batch.h
    engine->RegisterObjectBehaviour("BatchGroupKey", asBEHAVE_CONSTRUCT, "void f(const Batch&in)", asFUNCTION(BatchGroupKey_BatchGroupKey_Batch), asCALL_CDECL_OBJFIRST);
    // bool BatchGroupKey::operator==(const BatchGroupKey& rhs) const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchGroupKey", "bool opEquals(const BatchGroupKey&in) const", asMETHODPR(BatchGroupKey, operator==, (const BatchGroupKey&) const, bool), asCALL_THISCALL);
    // unsigned BatchGroupKey::ToHash() const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchGroupKey", "uint ToHash() const", asMETHODPR(BatchGroupKey, ToHash, () const, unsigned), asCALL_THISCALL);
    // BatchGroupKey& BatchGroupKey::operator=(const BatchGroupKey&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<BatchGroupKey>(engine, "BatchGroupKey");
#ifdef REGISTER_MANUAL_PART_BatchGroupKey
    REGISTER_MANUAL_PART_BatchGroupKey(BatchGroupKey, "BatchGroupKey")
#endif

    // PODVector<Batch> BatchQueue::batches_ | File: ../Graphics/Batch.h
    // Error: type "PODVector<Batch>" can not automatically bind
    // HashMap<BatchGroupKey, BatchGroup> BatchQueue::batchGroups_ | File: ../Graphics/Batch.h
    // Error: type "HashMap<BatchGroupKey, BatchGroup>" can not automatically bind
    // HashMap<unsigned short, unsigned short> BatchQueue::geometryRemapping_ | File: ../Graphics/Batch.h
    // Error: type "HashMap<unsigned short, unsigned short>" can not automatically bind
    // bool BatchQueue::hasExtraDefines_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchQueue", "bool hasExtraDefines", offsetof(BatchQueue, hasExtraDefines_));
    // HashMap<unsigned short, unsigned short> BatchQueue::materialRemapping_ | File: ../Graphics/Batch.h
    // Error: type "HashMap<unsigned short, unsigned short>" can not automatically bind
    // unsigned BatchQueue::maxSortedInstances_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchQueue", "uint maxSortedInstances", offsetof(BatchQueue, maxSortedInstances_));
    // String BatchQueue::psExtraDefines_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchQueue", "String psExtraDefines", offsetof(BatchQueue, psExtraDefines_));
    // StringHash BatchQueue::psExtraDefinesHash_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchQueue", "StringHash psExtraDefinesHash", offsetof(BatchQueue, psExtraDefinesHash_));
    // HashMap<unsigned, unsigned> BatchQueue::shaderRemapping_ | File: ../Graphics/Batch.h
    // Error: type "HashMap<unsigned, unsigned>" can not automatically bind
    // PODVector<Batch*> BatchQueue::sortedBatches_ | File: ../Graphics/Batch.h
    // Error: type "PODVector<Batch*>" can not automatically bind
    // PODVector<BatchGroup*> BatchQueue::sortedBatchGroups_ | File: ../Graphics/Batch.h
    // Error: type "PODVector<BatchGroup*>" can not automatically bind
    // String BatchQueue::vsExtraDefines_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchQueue", "String vsExtraDefines", offsetof(BatchQueue, vsExtraDefines_));
    // StringHash BatchQueue::vsExtraDefinesHash_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("BatchQueue", "StringHash vsExtraDefinesHash", offsetof(BatchQueue, vsExtraDefinesHash_));
    // void BatchQueue::Clear(int maxSortedInstances) | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchQueue", "void Clear(int)", asMETHODPR(BatchQueue, Clear, (int), void), asCALL_THISCALL);
    // void BatchQueue::Draw(View* view, Camera* camera, bool markToStencil, bool usingLightOptimization, bool allowDepthWrite) const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchQueue", "void Draw(View@+, Camera@+, bool, bool, bool) const", asMETHODPR(BatchQueue, Draw, (View*, Camera*, bool, bool, bool) const, void), asCALL_THISCALL);
    // unsigned BatchQueue::GetNumInstances() const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchQueue", "uint GetNumInstances() const", asMETHODPR(BatchQueue, GetNumInstances, () const, unsigned), asCALL_THISCALL);
    // bool BatchQueue::IsEmpty() const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchQueue", "bool IsEmpty() const", asMETHODPR(BatchQueue, IsEmpty, () const, bool), asCALL_THISCALL);
    // void BatchQueue::SetInstancingData(void* lockedData, unsigned stride, unsigned& freeIndex) | File: ../Graphics/Batch.h
    // Error: type "void*" can not automatically bind
    // void BatchQueue::SortBackToFront() | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchQueue", "void SortBackToFront()", asMETHODPR(BatchQueue, SortBackToFront, (), void), asCALL_THISCALL);
    // void BatchQueue::SortFrontToBack() | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchQueue", "void SortFrontToBack()", asMETHODPR(BatchQueue, SortFrontToBack, (), void), asCALL_THISCALL);
    // void BatchQueue::SortFrontToBack2Pass(PODVector<Batch*>& batches) | File: ../Graphics/Batch.h
    // Error: type "PODVector<Batch*>&" can not automatically bind
    // BatchQueue& BatchQueue::operator=(const BatchQueue&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<BatchQueue>(engine, "BatchQueue");
#ifdef REGISTER_MANUAL_PART_BatchQueue
    REGISTER_MANUAL_PART_BatchQueue(BatchQueue, "BatchQueue")
#endif

    // float BiasParameters::constantBias_ | File: ../Graphics/Light.h
    engine->RegisterObjectProperty("BiasParameters", "float constantBias", offsetof(BiasParameters, constantBias_));
    // float BiasParameters::normalOffset_ | File: ../Graphics/Light.h
    engine->RegisterObjectProperty("BiasParameters", "float normalOffset", offsetof(BiasParameters, normalOffset_));
    // float BiasParameters::slopeScaledBias_ | File: ../Graphics/Light.h
    engine->RegisterObjectProperty("BiasParameters", "float slopeScaledBias", offsetof(BiasParameters, slopeScaledBias_));
    // BiasParameters::BiasParameters(float constantBias, float slopeScaledBias, float normalOffset=0.0f) | File: ../Graphics/Light.h
    engine->RegisterObjectBehaviour("BiasParameters", asBEHAVE_CONSTRUCT, "void f(float, float, float = 0.0f)", asFUNCTION(BiasParameters_BiasParameters_float_float_float), asCALL_CDECL_OBJFIRST);
    // void BiasParameters::Validate() | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("BiasParameters", "void Validate()", asMETHODPR(BiasParameters, Validate, (), void), asCALL_THISCALL);
    // BiasParameters& BiasParameters::operator=(const BiasParameters&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<BiasParameters>(engine, "BiasParameters");
#ifdef REGISTER_MANUAL_PART_BiasParameters
    REGISTER_MANUAL_PART_BiasParameters(BiasParameters, "BiasParameters")
#endif

    // Color Billboard::color_ | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectProperty("Billboard", "Color color", offsetof(Billboard, color_));
    // Vector3 Billboard::direction_ | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectProperty("Billboard", "Vector3 direction", offsetof(Billboard, direction_));
    // bool Billboard::enabled_ | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectProperty("Billboard", "bool enabled", offsetof(Billboard, enabled_));
    // Vector3 Billboard::position_ | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectProperty("Billboard", "Vector3 position", offsetof(Billboard, position_));
    // float Billboard::rotation_ | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectProperty("Billboard", "float rotation", offsetof(Billboard, rotation_));
    // float Billboard::screenScaleFactor_ | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectProperty("Billboard", "float screenScaleFactor", offsetof(Billboard, screenScaleFactor_));
    // Vector2 Billboard::size_ | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectProperty("Billboard", "Vector2 size", offsetof(Billboard, size_));
    // float Billboard::sortDistance_ | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectProperty("Billboard", "float sortDistance", offsetof(Billboard, sortDistance_));
    // Rect Billboard::uv_ | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectProperty("Billboard", "Rect uv", offsetof(Billboard, uv_));
    // Billboard& Billboard::operator=(const Billboard&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Billboard>(engine, "Billboard");
    engine->RegisterObjectBehaviour("Billboard", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Billboard", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_Billboard
    REGISTER_MANUAL_PART_Billboard(Billboard, "Billboard")
#endif

    // bool Bone::animated_ | File: ../Graphics/Skeleton.h
    engine->RegisterObjectProperty("Bone", "bool animated", offsetof(Bone, animated_));
    // BoundingBox Bone::boundingBox_ | File: ../Graphics/Skeleton.h
    engine->RegisterObjectProperty("Bone", "BoundingBox boundingBox", offsetof(Bone, boundingBox_));
    // BoneCollisionShapeFlags Bone::collisionMask_ | File: ../Graphics/Skeleton.h
    engine->RegisterObjectProperty("Bone", "BoneCollisionShapeFlags collisionMask", offsetof(Bone, collisionMask_));
    // Vector3 Bone::initialPosition_ | File: ../Graphics/Skeleton.h
    engine->RegisterObjectProperty("Bone", "Vector3 initialPosition", offsetof(Bone, initialPosition_));
    // Quaternion Bone::initialRotation_ | File: ../Graphics/Skeleton.h
    engine->RegisterObjectProperty("Bone", "Quaternion initialRotation", offsetof(Bone, initialRotation_));
    // Vector3 Bone::initialScale_ | File: ../Graphics/Skeleton.h
    engine->RegisterObjectProperty("Bone", "Vector3 initialScale", offsetof(Bone, initialScale_));
    // String Bone::name_ | File: ../Graphics/Skeleton.h
    engine->RegisterObjectProperty("Bone", "String name", offsetof(Bone, name_));
    // StringHash Bone::nameHash_ | File: ../Graphics/Skeleton.h
    engine->RegisterObjectProperty("Bone", "StringHash nameHash", offsetof(Bone, nameHash_));
    // WeakPtr<Node> Bone::node_ | File: ../Graphics/Skeleton.h
    // Error: type "WeakPtr<Node>" can not automatically bind
    // Matrix3x4 Bone::offsetMatrix_ | File: ../Graphics/Skeleton.h
    engine->RegisterObjectProperty("Bone", "Matrix3x4 offsetMatrix", offsetof(Bone, offsetMatrix_));
    // unsigned Bone::parentIndex_ | File: ../Graphics/Skeleton.h
    engine->RegisterObjectProperty("Bone", "uint parentIndex", offsetof(Bone, parentIndex_));
    // float Bone::radius_ | File: ../Graphics/Skeleton.h
    engine->RegisterObjectProperty("Bone", "float radius", offsetof(Bone, radius_));
    // Bone::Bone() | File: ../Graphics/Skeleton.h
    engine->RegisterObjectBehaviour("Bone", asBEHAVE_FACTORY, "Bone@+ f()", asFUNCTION(Bone_Bone_void), asCALL_CDECL);
    // Bone& Bone::operator=(const Bone&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Bone>(engine, "Bone");
    engine->RegisterObjectBehaviour("Bone", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Bone", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_Bone
    REGISTER_MANUAL_PART_Bone(Bone, "Bone")
#endif

}

}
