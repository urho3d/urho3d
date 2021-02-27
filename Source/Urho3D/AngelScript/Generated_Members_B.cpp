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
static void BillboardSet_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(BillboardSet* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void BorderImage_AddTags_StringVector(BorderImage* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
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

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void BorderImage_SetTags_StringVector(BorderImage* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void BorderImage_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(BorderImage* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
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

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void Button_AddTags_StringVector(Button* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
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

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void Button_SetTags_StringVector(Button* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Button_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Button* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
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

void ASRegisterGenerated_Members_B(asIScriptEngine* engine)
{
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void AddLight(Light@+)", AS_METHODPR(BillboardSet, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("BillboardSet", asBEHAVE_ADDREF, "void f()", AS_METHODPR(BillboardSet, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void AddVertexLight(Light@+)", AS_METHODPR(BillboardSet, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void AllocateNetworkState()", AS_METHODPR(BillboardSet, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void ApplyAttributes()", AS_METHODPR(BillboardSet, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // explicit BillboardSet::BillboardSet(Context* context) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectBehaviour("BillboardSet", asBEHAVE_FACTORY, "BillboardSet@+ f()", AS_FUNCTION(BillboardSet_BillboardSet_Context), AS_CALL_CDECL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void BillboardSet::Commit() | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void Commit()", AS_METHODPR(BillboardSet, Commit, (), void), AS_CALL_THISCALL);
    // void Drawable::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(BillboardSet, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(BillboardSet, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "bool GetAnimationEnabled() const", AS_METHODPR(BillboardSet, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_animationEnabled() const", AS_METHODPR(BillboardSet, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // float BillboardSet::GetAnimationLodBias() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "float GetAnimationLodBias() const", AS_METHODPR(BillboardSet, GetAnimationLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "float get_animationLodBias() const", AS_METHODPR(BillboardSet, GetAnimationLodBias, () const, float), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "Variant GetAttribute(uint) const", AS_METHODPR(BillboardSet, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Variant get_attributes(uint) const", AS_METHODPR(BillboardSet, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "Variant GetAttribute(const String&in) const", AS_METHODPR(BillboardSet, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(BillboardSet, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(BillboardSet, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(BillboardSet, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(BillboardSet, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "Variant GetAttributeDefault(uint) const", AS_METHODPR(BillboardSet, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Variant get_attributeDefaults(uint) const", AS_METHODPR(BillboardSet, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(BillboardSet, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // Billboard* BillboardSet::GetBillboard(unsigned index) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "Billboard@+ GetBillboard(uint)", AS_METHODPR(BillboardSet, GetBillboard, (unsigned), Billboard*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Billboard@+ get_billboards(uint)", AS_METHODPR(BillboardSet, GetBillboard, (unsigned), Billboard*), AS_CALL_THISCALL);
    // PODVector<Billboard>& BillboardSet::GetBillboards() | File: ../Graphics/BillboardSet.h
    // Error: type "PODVector<Billboard>&" can not automatically bind
    // VariantVector BillboardSet::GetBillboardsAttr() const | File: ../Graphics/BillboardSet.h
    // Error: type "VariantVector" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "bool GetBlockEvents() const", AS_METHODPR(BillboardSet, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(BillboardSet, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "const BoundingBox& get_boundingBox() const", AS_METHODPR(BillboardSet, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool GetCastShadows() const", AS_METHODPR(BillboardSet, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_castShadows() const", AS_METHODPR(BillboardSet, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "const String& GetCategory() const", AS_METHODPR(BillboardSet, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "const String& get_category() const", AS_METHODPR(BillboardSet, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "Component@+ GetComponent(StringHash) const", AS_METHODPR(BillboardSet, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("BillboardSet", "float GetDistance() const", AS_METHODPR(BillboardSet, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint8 GetDrawableFlags() const", AS_METHODPR(BillboardSet, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetDrawDistance() const", AS_METHODPR(BillboardSet, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "float get_drawDistance() const", AS_METHODPR(BillboardSet, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "VariantMap& GetEventDataMap() const", AS_METHODPR(BillboardSet, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "Object@+ GetEventSender() const", AS_METHODPR(BillboardSet, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FaceCameraMode BillboardSet::GetFaceCameraMode() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "FaceCameraMode GetFaceCameraMode() const", AS_METHODPR(BillboardSet, GetFaceCameraMode, () const, FaceCameraMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "FaceCameraMode get_faceCameraMode() const", AS_METHODPR(BillboardSet, GetFaceCameraMode, () const, FaceCameraMode), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "Light@+ GetFirstLight() const", AS_METHODPR(BillboardSet, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(BillboardSet, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(BillboardSet, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "const VariantMap& GetGlobalVars() const", AS_METHODPR(BillboardSet, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "const VariantMap& get_globalVars() const", AS_METHODPR(BillboardSet, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetID() const", AS_METHODPR(BillboardSet, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_id() const", AS_METHODPR(BillboardSet, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(BillboardSet, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetLightMask() const", AS_METHODPR(BillboardSet, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_lightMask() const", AS_METHODPR(BillboardSet, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(BillboardSet_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetLodBias() const", AS_METHODPR(BillboardSet, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "float get_lodBias() const", AS_METHODPR(BillboardSet, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetLodDistance() const", AS_METHODPR(BillboardSet, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(BillboardSet, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // Material* BillboardSet::GetMaterial() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "Material@+ GetMaterial() const", AS_METHODPR(BillboardSet, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Material@+ get_material() const", AS_METHODPR(BillboardSet, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BillboardSet::GetMaterialAttr() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "ResourceRef GetMaterialAttr() const", AS_METHODPR(BillboardSet, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetMaxLights() const", AS_METHODPR(BillboardSet, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_maxLights() const", AS_METHODPR(BillboardSet, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetMaxZ() const", AS_METHODPR(BillboardSet, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float BillboardSet::GetMinAngle() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "float GetMinAngle() const", AS_METHODPR(BillboardSet, GetMinAngle, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "float get_minAngle() const", AS_METHODPR(BillboardSet, GetMinAngle, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetMinZ() const", AS_METHODPR(BillboardSet, GetMinZ, () const, float), AS_CALL_THISCALL);
    // const PODVector<unsigned char>& BillboardSet::GetNetBillboardsAttr() const | File: ../Graphics/BillboardSet.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "Node@+ GetNode() const", AS_METHODPR(BillboardSet, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Node@+ get_node() const", AS_METHODPR(BillboardSet, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetNumAttributes() const", AS_METHODPR(BillboardSet, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_numAttributes() const", AS_METHODPR(BillboardSet, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned BillboardSet::GetNumBillboards() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetNumBillboards() const", AS_METHODPR(BillboardSet, GetNumBillboards, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_numBillboards() const", AS_METHODPR(BillboardSet, GetNumBillboards, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetNumNetworkAttributes() const", AS_METHODPR(BillboardSet, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetNumOccluderTriangles()", AS_METHODPR(BillboardSet, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(BillboardSet, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(BillboardSet, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(BillboardSet, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "Scene@+ GetScene() const", AS_METHODPR(BillboardSet, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetShadowDistance() const", AS_METHODPR(BillboardSet, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "float get_shadowDistance() const", AS_METHODPR(BillboardSet, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetShadowMask() const", AS_METHODPR(BillboardSet, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_shadowMask() const", AS_METHODPR(BillboardSet, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "float GetSortValue() const", AS_METHODPR(BillboardSet, GetSortValue, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(BillboardSet, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "StringHash GetType() const", AS_METHODPR(BillboardSet, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "StringHash get_type() const", AS_METHODPR(BillboardSet, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "const String& GetTypeName() const", AS_METHODPR(BillboardSet, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "const String& get_typeName() const", AS_METHODPR(BillboardSet, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // UpdateGeometryType BillboardSet::GetUpdateGeometryType() override | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(BillboardSet, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(BillboardSet_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetViewMask() const", AS_METHODPR(BillboardSet, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_viewMask() const", AS_METHODPR(BillboardSet, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(BillboardSet, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(BillboardSet, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "Zone@+ GetZone() const", AS_METHODPR(BillboardSet, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "Zone@+ get_zone() const", AS_METHODPR(BillboardSet, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "uint GetZoneMask() const", AS_METHODPR(BillboardSet, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "uint get_zoneMask() const", AS_METHODPR(BillboardSet, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool HasBasePass(uint) const", AS_METHODPR(BillboardSet, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "bool HasEventHandlers() const", AS_METHODPR(BillboardSet, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(BillboardSet, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(BillboardSet, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsEnabled() const", AS_METHODPR(BillboardSet, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_enabled() const", AS_METHODPR(BillboardSet, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsEnabledEffective() const", AS_METHODPR(BillboardSet, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_enabledEffective() const", AS_METHODPR(BillboardSet, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool BillboardSet::IsFixedScreenSize() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsFixedScreenSize() const", AS_METHODPR(BillboardSet, IsFixedScreenSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_fixedScreenSize() const", AS_METHODPR(BillboardSet, IsFixedScreenSize, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsInstanceOf(StringHash) const", AS_METHODPR(BillboardSet, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsInView() const", AS_METHODPR(BillboardSet, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_inView() const", AS_METHODPR(BillboardSet, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsInView(Camera@+) const", AS_METHODPR(BillboardSet, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(BillboardSet, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsOccludee() const", AS_METHODPR(BillboardSet, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_occludee() const", AS_METHODPR(BillboardSet, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsOccluder() const", AS_METHODPR(BillboardSet, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_occluder() const", AS_METHODPR(BillboardSet, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool BillboardSet::IsRelative() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsRelative() const", AS_METHODPR(BillboardSet, IsRelative, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_relative() const", AS_METHODPR(BillboardSet, IsRelative, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsReplicated() const", AS_METHODPR(BillboardSet, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_replicated() const", AS_METHODPR(BillboardSet, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool BillboardSet::IsScaled() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsScaled() const", AS_METHODPR(BillboardSet, IsScaled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_scaled() const", AS_METHODPR(BillboardSet, IsScaled, () const, bool), AS_CALL_THISCALL);
    // bool BillboardSet::IsSorted() const | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsSorted() const", AS_METHODPR(BillboardSet, IsSorted, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_sorted() const", AS_METHODPR(BillboardSet, IsSorted, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsTemporary() const", AS_METHODPR(BillboardSet, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool get_temporary() const", AS_METHODPR(BillboardSet, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "bool IsZoneDirty() const", AS_METHODPR(BillboardSet, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void LimitLights()", AS_METHODPR(BillboardSet, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void LimitVertexLights(bool)", AS_METHODPR(BillboardSet, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool Load(Deserializer&)", AS_METHODPR(BillboardSet, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(BillboardSet, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "bool LoadXML(const XMLElement&in)", AS_METHODPR(BillboardSet, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void MarkForUpdate()", AS_METHODPR(BillboardSet, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void MarkInView(const FrameInfo&in)", AS_METHODPR(BillboardSet, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void MarkInView(uint)", AS_METHODPR(BillboardSet, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "void MarkNetworkUpdate()", AS_METHODPR(BillboardSet, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(BillboardSet, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(BillboardSet, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(BillboardSet, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void OnSetEnabled()", AS_METHODPR(BillboardSet, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "void PrepareNetworkUpdate()", AS_METHODPR(BillboardSet, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void BillboardSet::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/BillboardSet.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(BillboardSet, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(BillboardSet, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("BillboardSet", "int Refs() const", AS_METHODPR(BillboardSet, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "int get_refs() const", AS_METHODPR(BillboardSet, Refs, () const, int), AS_CALL_THISCALL);
    // static void BillboardSet::RegisterObject(Context* context) | File: ../Graphics/BillboardSet.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("BillboardSet", asBEHAVE_RELEASE, "void f()", AS_METHODPR(BillboardSet, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "void Remove()", AS_METHODPR(BillboardSet, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(BillboardSet, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void RemoveInstanceDefault()", AS_METHODPR(BillboardSet, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void RemoveObjectAnimation()", AS_METHODPR(BillboardSet, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void ResetToDefault()", AS_METHODPR(BillboardSet, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "bool Save(Serializer&) const", AS_METHODPR(BillboardSet, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool SaveDefaultAttributes() const", AS_METHODPR(BillboardSet, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "bool SaveJSON(JSONValue&) const", AS_METHODPR(BillboardSet, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "bool SaveXML(XMLElement&) const", AS_METHODPR(BillboardSet, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void SendEvent(StringHash)", AS_METHODPR(BillboardSet, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(BillboardSet, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAnimationEnabled(bool)", AS_METHODPR(BillboardSet, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_animationEnabled(bool)", AS_METHODPR(BillboardSet, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void BillboardSet::SetAnimationLodBias(float bias) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAnimationLodBias(float)", AS_METHODPR(BillboardSet, SetAnimationLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_animationLodBias(float)", AS_METHODPR(BillboardSet, SetAnimationLodBias, (float), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAnimationTime(float)", AS_METHODPR(BillboardSet, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(BillboardSet, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(BillboardSet, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(BillboardSet, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(BillboardSet, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(BillboardSet, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(BillboardSet, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(BillboardSet, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetBasePass(uint)", AS_METHODPR(BillboardSet, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void BillboardSet::SetBillboardsAttr(const VariantVector& value) | File: ../Graphics/BillboardSet.h
    // Error: type "const VariantVector&" can not automatically bind
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void SetBlockEvents(bool)", AS_METHODPR(BillboardSet, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetCastShadows(bool)", AS_METHODPR(BillboardSet, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_castShadows(bool)", AS_METHODPR(BillboardSet, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetDrawDistance(float)", AS_METHODPR(BillboardSet, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_drawDistance(float)", AS_METHODPR(BillboardSet, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("BillboardSet", "void SetEnabled(bool)", AS_METHODPR(BillboardSet, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_enabled(bool)", AS_METHODPR(BillboardSet, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void BillboardSet::SetFaceCameraMode(FaceCameraMode mode) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetFaceCameraMode(FaceCameraMode)", AS_METHODPR(BillboardSet, SetFaceCameraMode, (FaceCameraMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_faceCameraMode(FaceCameraMode)", AS_METHODPR(BillboardSet, SetFaceCameraMode, (FaceCameraMode), void), AS_CALL_THISCALL);
    // void BillboardSet::SetFixedScreenSize(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetFixedScreenSize(bool)", AS_METHODPR(BillboardSet, SetFixedScreenSize, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_fixedScreenSize(bool)", AS_METHODPR(BillboardSet, SetFixedScreenSize, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(BillboardSet, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(BillboardSet, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetInstanceDefault(bool)", AS_METHODPR(BillboardSet, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(BillboardSet, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetLightMask(uint)", AS_METHODPR(BillboardSet, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_lightMask(uint)", AS_METHODPR(BillboardSet, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetLodBias(float)", AS_METHODPR(BillboardSet, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_lodBias(float)", AS_METHODPR(BillboardSet, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void BillboardSet::SetMaterial(Material* material) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetMaterial(Material@+)", AS_METHODPR(BillboardSet, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_material(Material@+)", AS_METHODPR(BillboardSet, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BillboardSet::SetMaterialAttr(const ResourceRef& value) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(BillboardSet, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetMaxLights(uint)", AS_METHODPR(BillboardSet, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_maxLights(uint)", AS_METHODPR(BillboardSet, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void BillboardSet::SetMinAngle(float angle) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetMinAngle(float)", AS_METHODPR(BillboardSet, SetMinAngle, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_minAngle(float)", AS_METHODPR(BillboardSet, SetMinAngle, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetMinMaxZ(float, float)", AS_METHODPR(BillboardSet, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void BillboardSet::SetNetBillboardsAttr(const PODVector<unsigned char>& value) | File: ../Graphics/BillboardSet.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // void BillboardSet::SetNumBillboards(unsigned num) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetNumBillboards(uint)", AS_METHODPR(BillboardSet, SetNumBillboards, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_numBillboards(uint)", AS_METHODPR(BillboardSet, SetNumBillboards, (unsigned), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(BillboardSet, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(BillboardSet, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(BillboardSet, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetOccludee(bool)", AS_METHODPR(BillboardSet, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_occludee(bool)", AS_METHODPR(BillboardSet, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetOccluder(bool)", AS_METHODPR(BillboardSet, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_occluder(bool)", AS_METHODPR(BillboardSet, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void BillboardSet::SetRelative(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetRelative(bool)", AS_METHODPR(BillboardSet, SetRelative, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_relative(bool)", AS_METHODPR(BillboardSet, SetRelative, (bool), void), AS_CALL_THISCALL);
    // void BillboardSet::SetScaled(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetScaled(bool)", AS_METHODPR(BillboardSet, SetScaled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_scaled(bool)", AS_METHODPR(BillboardSet, SetScaled, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetShadowDistance(float)", AS_METHODPR(BillboardSet, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_shadowDistance(float)", AS_METHODPR(BillboardSet, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetShadowMask(uint)", AS_METHODPR(BillboardSet, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_shadowMask(uint)", AS_METHODPR(BillboardSet, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void BillboardSet::SetSorted(bool enable) | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void SetSorted(bool)", AS_METHODPR(BillboardSet, SetSorted, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_sorted(bool)", AS_METHODPR(BillboardSet, SetSorted, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetSortValue(float)", AS_METHODPR(BillboardSet, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetTemporary(bool)", AS_METHODPR(BillboardSet, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_temporary(bool)", AS_METHODPR(BillboardSet, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetViewMask(uint)", AS_METHODPR(BillboardSet, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_viewMask(uint)", AS_METHODPR(BillboardSet, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetZone(Zone@+, bool = false)", AS_METHODPR(BillboardSet, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void SetZoneMask(uint)", AS_METHODPR(BillboardSet, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "void set_zoneMask(uint)", AS_METHODPR(BillboardSet, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void UnsubscribeFromAllEvents()", AS_METHODPR(BillboardSet, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(BillboardSet_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(BillboardSet, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(BillboardSet, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BillboardSet", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(BillboardSet, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("BillboardSet", "void Update(const FrameInfo&in)", AS_METHODPR(BillboardSet, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void BillboardSet::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(BillboardSet, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void BillboardSet::UpdateGeometry(const FrameInfo& frame) override | File: ../Graphics/BillboardSet.h
    engine->RegisterObjectMethod("BillboardSet", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(BillboardSet, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("BillboardSet", "int WeakRefs() const", AS_METHODPR(BillboardSet, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BillboardSet", "int get_weakRefs() const", AS_METHODPR(BillboardSet, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(BillboardSet, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(BillboardSet, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BillboardSet", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(BillboardSet, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("BorderImage", "void AddChild(UIElement@+)", AS_METHODPR(BorderImage, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("BorderImage", asBEHAVE_ADDREF, "void f()", AS_METHODPR(BorderImage, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void AddTag(const String&in)", AS_METHODPR(BorderImage, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(BorderImage, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(BorderImage_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void AdjustScissor(IntRect&)", AS_METHODPR(BorderImage, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void AllocateNetworkState()", AS_METHODPR(BorderImage, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void ApplyAttributes()", AS_METHODPR(BorderImage, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // explicit BorderImage::BorderImage(Context* context) | File: ../UI/BorderImage.h
    engine->RegisterObjectBehaviour("BorderImage", asBEHAVE_FACTORY, "BorderImage@+ f()", AS_FUNCTION(BorderImage_BorderImage_Context), AS_CALL_CDECL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void BringToFront()", AS_METHODPR(BorderImage, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(BorderImage, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void DisableLayoutUpdate()", AS_METHODPR(BorderImage, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(BorderImage, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void EnableLayoutUpdate()", AS_METHODPR(BorderImage, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(BorderImage, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "uint FindChild(UIElement@+) const", AS_METHODPR(BorderImage, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "bool GetAnimationEnabled() const", AS_METHODPR(BorderImage, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_animationEnabled() const", AS_METHODPR(BorderImage, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const String& GetAppliedStyle() const", AS_METHODPR(BorderImage, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const String& get_style() const", AS_METHODPR(BorderImage, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "Variant GetAttribute(uint) const", AS_METHODPR(BorderImage, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "Variant get_attributes(uint) const", AS_METHODPR(BorderImage, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "Variant GetAttribute(const String&in) const", AS_METHODPR(BorderImage, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(BorderImage, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(BorderImage, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(BorderImage, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(BorderImage, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "Variant GetAttributeDefault(uint) const", AS_METHODPR(BorderImage, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "Variant get_attributeDefaults(uint) const", AS_METHODPR(BorderImage, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(BorderImage, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/BorderImage.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "BlendMode GetBlendMode() const", AS_METHODPR(BorderImage, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "BlendMode get_blendMode() const", AS_METHODPR(BorderImage, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "bool GetBlockEvents() const", AS_METHODPR(BorderImage, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "const IntRect& GetBorder() const", AS_METHODPR(BorderImage, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntRect& get_border() const", AS_METHODPR(BorderImage, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool GetBringToBack() const", AS_METHODPR(BorderImage, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_bringToBack() const", AS_METHODPR(BorderImage, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool GetBringToFront() const", AS_METHODPR(BorderImage, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_bringToFront() const", AS_METHODPR(BorderImage, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "const String& GetCategory() const", AS_METHODPR(BorderImage, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const String& get_category() const", AS_METHODPR(BorderImage, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ GetChild(uint) const", AS_METHODPR(BorderImage, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ get_children(uint) const", AS_METHODPR(BorderImage, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(BorderImage, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(BorderImage, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetChildOffset() const", AS_METHODPR(BorderImage, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_childOffset() const", AS_METHODPR(BorderImage, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(BorderImage_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(BorderImage_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(BorderImage_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntRect& GetClipBorder() const", AS_METHODPR(BorderImage, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntRect& get_clipBorder() const", AS_METHODPR(BorderImage, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool GetClipChildren() const", AS_METHODPR(BorderImage, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_clipChildren() const", AS_METHODPR(BorderImage, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Color& GetColor(Corner) const", AS_METHODPR(BorderImage, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const Color& get_colors(Corner) const", AS_METHODPR(BorderImage, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Color& GetColorAttr() const", AS_METHODPR(BorderImage, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "IntRect GetCombinedScreenRect()", AS_METHODPR(BorderImage, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "IntRect get_combinedScreenRect()", AS_METHODPR(BorderImage, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(BorderImage, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Color& GetDerivedColor() const", AS_METHODPR(BorderImage, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "float GetDerivedOpacity() const", AS_METHODPR(BorderImage, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "float get_derivedOpacity() const", AS_METHODPR(BorderImage, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetDisabledOffset() const", AS_METHODPR(BorderImage, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_disabledOffset() const", AS_METHODPR(BorderImage, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(BorderImage, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(BorderImage, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "uint GetDragButtonCount() const", AS_METHODPR(BorderImage, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "uint get_dragButtonCount() const", AS_METHODPR(BorderImage, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(BorderImage, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(BorderImage, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(BorderImage, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ GetElementEventSender() const", AS_METHODPR(BorderImage, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool GetEnableAnchor() const", AS_METHODPR(BorderImage, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_enableAnchor() const", AS_METHODPR(BorderImage, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "VariantMap& GetEventDataMap() const", AS_METHODPR(BorderImage, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "Object@+ GetEventSender() const", AS_METHODPR(BorderImage, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "FocusMode GetFocusMode() const", AS_METHODPR(BorderImage, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "FocusMode get_focusMode() const", AS_METHODPR(BorderImage, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(BorderImage, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(BorderImage, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "const VariantMap& GetGlobalVars() const", AS_METHODPR(BorderImage, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const VariantMap& get_globalVars() const", AS_METHODPR(BorderImage, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetHeight() const", AS_METHODPR(BorderImage, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_height() const", AS_METHODPR(BorderImage, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(BorderImage, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(BorderImage, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetHoverOffset() const", AS_METHODPR(BorderImage, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_hoverOffset() const", AS_METHODPR(BorderImage, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "const IntRect& GetImageBorder() const", AS_METHODPR(BorderImage, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntRect& get_imageBorder() const", AS_METHODPR(BorderImage, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "const IntRect& GetImageRect() const", AS_METHODPR(BorderImage, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntRect& get_imageRect() const", AS_METHODPR(BorderImage, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetIndent() const", AS_METHODPR(BorderImage, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_indent() const", AS_METHODPR(BorderImage, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetIndentSpacing() const", AS_METHODPR(BorderImage, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_indentSpacing() const", AS_METHODPR(BorderImage, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetIndentWidth() const", AS_METHODPR(BorderImage, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_indentWidth() const", AS_METHODPR(BorderImage, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(BorderImage, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntRect& GetLayoutBorder() const", AS_METHODPR(BorderImage, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntRect& get_layoutBorder() const", AS_METHODPR(BorderImage, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetLayoutElementMaxSize() const", AS_METHODPR(BorderImage, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(BorderImage, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(BorderImage, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "LayoutMode GetLayoutMode() const", AS_METHODPR(BorderImage, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "LayoutMode get_layoutMode() const", AS_METHODPR(BorderImage, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetLayoutSpacing() const", AS_METHODPR(BorderImage, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_layoutSpacing() const", AS_METHODPR(BorderImage, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "Material@+ GetMaterial() const", AS_METHODPR(BorderImage, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "Material@+ get_material() const", AS_METHODPR(BorderImage, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "ResourceRef GetMaterialAttr() const", AS_METHODPR(BorderImage, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Vector2& GetMaxAnchor() const", AS_METHODPR(BorderImage, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const Vector2& get_maxAnchor() const", AS_METHODPR(BorderImage, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetMaxHeight() const", AS_METHODPR(BorderImage, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_maxHeight() const", AS_METHODPR(BorderImage, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetMaxOffset() const", AS_METHODPR(BorderImage, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_maxOffset() const", AS_METHODPR(BorderImage, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetMaxSize() const", AS_METHODPR(BorderImage, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_maxSize() const", AS_METHODPR(BorderImage, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetMaxWidth() const", AS_METHODPR(BorderImage, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_maxWidth() const", AS_METHODPR(BorderImage, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Vector2& GetMinAnchor() const", AS_METHODPR(BorderImage, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const Vector2& get_minAnchor() const", AS_METHODPR(BorderImage, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetMinHeight() const", AS_METHODPR(BorderImage, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_minHeight() const", AS_METHODPR(BorderImage, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetMinOffset() const", AS_METHODPR(BorderImage, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_minOffset() const", AS_METHODPR(BorderImage, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetMinSize() const", AS_METHODPR(BorderImage, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_minSize() const", AS_METHODPR(BorderImage, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetMinWidth() const", AS_METHODPR(BorderImage, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_minWidth() const", AS_METHODPR(BorderImage, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const String& GetName() const", AS_METHODPR(BorderImage, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const String& get_name() const", AS_METHODPR(BorderImage, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "uint GetNumAttributes() const", AS_METHODPR(BorderImage, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "uint get_numAttributes() const", AS_METHODPR(BorderImage, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "uint GetNumChildren(bool = false) const", AS_METHODPR(BorderImage, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "uint get_numChildren(bool = false) const", AS_METHODPR(BorderImage, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "uint GetNumNetworkAttributes() const", AS_METHODPR(BorderImage, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(BorderImage, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(BorderImage, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(BorderImage, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "float GetOpacity() const", AS_METHODPR(BorderImage, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "float get_opacity() const", AS_METHODPR(BorderImage, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ GetParent() const", AS_METHODPR(BorderImage, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ get_parent() const", AS_METHODPR(BorderImage, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Vector2& GetPivot() const", AS_METHODPR(BorderImage, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const Vector2& get_pivot() const", AS_METHODPR(BorderImage, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetPosition() const", AS_METHODPR(BorderImage, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_position() const", AS_METHODPR(BorderImage, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetPriority() const", AS_METHODPR(BorderImage, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_priority() const", AS_METHODPR(BorderImage, GetPriority, () const, int), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ GetRoot() const", AS_METHODPR(BorderImage, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ get_root() const", AS_METHODPR(BorderImage, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetScreenPosition() const", AS_METHODPR(BorderImage, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_screenPosition() const", AS_METHODPR(BorderImage, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& GetSize() const", AS_METHODPR(BorderImage, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const IntVector2& get_size() const", AS_METHODPR(BorderImage, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool GetSortChildren() const", AS_METHODPR(BorderImage, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_sortChildren() const", AS_METHODPR(BorderImage, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(BorderImage, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(BorderImage_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("BorderImage", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(BorderImage_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "Texture@+ GetTexture() const", AS_METHODPR(BorderImage, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "Texture@+ get_texture() const", AS_METHODPR(BorderImage, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "ResourceRef GetTextureAttr() const", AS_METHODPR(BorderImage, GetTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "TraversalMode GetTraversalMode() const", AS_METHODPR(BorderImage, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "TraversalMode get_traversalMode() const", AS_METHODPR(BorderImage, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "StringHash GetType() const", AS_METHODPR(BorderImage, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "StringHash get_type() const", AS_METHODPR(BorderImage, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "const String& GetTypeName() const", AS_METHODPR(BorderImage, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "const String& get_typeName() const", AS_METHODPR(BorderImage, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool GetUseDerivedOpacity() const", AS_METHODPR(BorderImage, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_useDerivedOpacity() const", AS_METHODPR(BorderImage, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(BorderImage, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "const VariantMap& GetVars() const", AS_METHODPR(BorderImage, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(BorderImage, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(BorderImage, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "int GetWidth() const", AS_METHODPR(BorderImage, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_width() const", AS_METHODPR(BorderImage, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool HasColorGradient() const", AS_METHODPR(BorderImage, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_colorGradient() const", AS_METHODPR(BorderImage, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "bool HasEventHandlers() const", AS_METHODPR(BorderImage, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool HasFocus() const", AS_METHODPR(BorderImage, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_focus() const", AS_METHODPR(BorderImage, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(BorderImage, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(BorderImage, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool HasTag(const String&in) const", AS_METHODPR(BorderImage, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void InsertChild(uint, UIElement@+)", AS_METHODPR(BorderImage, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsChildOf(UIElement@+) const", AS_METHODPR(BorderImage, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsEditable() const", AS_METHODPR(BorderImage, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_editable() const", AS_METHODPR(BorderImage, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsElementEventSender() const", AS_METHODPR(BorderImage, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_elementEventSender() const", AS_METHODPR(BorderImage, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsEnabled() const", AS_METHODPR(BorderImage, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_enabled() const", AS_METHODPR(BorderImage, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsEnabledSelf() const", AS_METHODPR(BorderImage, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_enabledSelf() const", AS_METHODPR(BorderImage, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsFixedHeight() const", AS_METHODPR(BorderImage, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_fixedHeight() const", AS_METHODPR(BorderImage, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsFixedSize() const", AS_METHODPR(BorderImage, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_fixedSize() const", AS_METHODPR(BorderImage, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsFixedWidth() const", AS_METHODPR(BorderImage, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_fixedWidth() const", AS_METHODPR(BorderImage, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsHovering() const", AS_METHODPR(BorderImage, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_hovering() const", AS_METHODPR(BorderImage, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsInside(IntVector2, bool)", AS_METHODPR(BorderImage, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(BorderImage, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "bool IsInstanceOf(StringHash) const", AS_METHODPR(BorderImage, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsInternal() const", AS_METHODPR(BorderImage, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_internal() const", AS_METHODPR(BorderImage, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsSelected() const", AS_METHODPR(BorderImage, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_selected() const", AS_METHODPR(BorderImage, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool IsTemporary() const", AS_METHODPR(BorderImage, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_temporary() const", AS_METHODPR(BorderImage, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "bool IsTiled() const", AS_METHODPR(BorderImage, IsTiled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_tiled() const", AS_METHODPR(BorderImage, IsTiled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsVisible() const", AS_METHODPR(BorderImage, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_visible() const", AS_METHODPR(BorderImage, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsVisibleEffective() const", AS_METHODPR(BorderImage, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool get_visibleEffective() const", AS_METHODPR(BorderImage, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsWheelHandler() const", AS_METHODPR(BorderImage, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(BorderImage, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool Load(Deserializer&)", AS_METHODPR(BorderImage, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(BorderImage, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(BorderImage, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool LoadXML(const XMLElement&in)", AS_METHODPR(BorderImage, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(BorderImage, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool LoadXML(Deserializer&)", AS_METHODPR(BorderImage, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void MarkNetworkUpdate()", AS_METHODPR(BorderImage, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(BorderImage, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(BorderImage, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(BorderImage, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(BorderImage, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(BorderImage, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(BorderImage, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(BorderImage, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(BorderImage, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(BorderImage, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(BorderImage, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(BorderImage, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(BorderImage, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnIndentSet()", AS_METHODPR(BorderImage, OnIndentSet, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(BorderImage, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(BorderImage, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(BorderImage, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(BorderImage, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnSetEditable()", AS_METHODPR(BorderImage, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnTextInput(const String&in)", AS_METHODPR(BorderImage, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(BorderImage, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(BorderImage, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(BorderImage, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("BorderImage", "int Refs() const", AS_METHODPR(BorderImage, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_refs() const", AS_METHODPR(BorderImage, Refs, () const, int), AS_CALL_THISCALL);
    // static void BorderImage::RegisterObject(Context* context) | File: ../UI/BorderImage.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("BorderImage", asBEHAVE_RELEASE, "void f()", AS_METHODPR(BorderImage, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void Remove()", AS_METHODPR(BorderImage, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveAllChildren()", AS_METHODPR(BorderImage, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveAllTags()", AS_METHODPR(BorderImage, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(BorderImage, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(BorderImage, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveChildAtIndex(uint)", AS_METHODPR(BorderImage, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveInstanceDefault()", AS_METHODPR(BorderImage, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void RemoveObjectAnimation()", AS_METHODPR(BorderImage, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool RemoveTag(const String&in)", AS_METHODPR(BorderImage, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void ResetDeepEnabled()", AS_METHODPR(BorderImage, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void ResetToDefault()", AS_METHODPR(BorderImage, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool Save(Serializer&) const", AS_METHODPR(BorderImage, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool SaveDefaultAttributes() const", AS_METHODPR(BorderImage, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "bool SaveJSON(JSONValue&) const", AS_METHODPR(BorderImage, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool SaveXML(XMLElement&) const", AS_METHODPR(BorderImage, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(BorderImage, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(BorderImage, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void SendEvent(StringHash)", AS_METHODPR(BorderImage, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(BorderImage, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(BorderImage, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetAnimationEnabled(bool)", AS_METHODPR(BorderImage, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_animationEnabled(bool)", AS_METHODPR(BorderImage, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetAnimationTime(float)", AS_METHODPR(BorderImage, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(BorderImage, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(BorderImage, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(BorderImage, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(BorderImage, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(BorderImage, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(BorderImage, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(BorderImage, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetBlendMode(BlendMode)", AS_METHODPR(BorderImage, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_blendMode(BlendMode)", AS_METHODPR(BorderImage, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void SetBlockEvents(bool)", AS_METHODPR(BorderImage, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetBorder(const IntRect&in)", AS_METHODPR(BorderImage, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_border(const IntRect&in)", AS_METHODPR(BorderImage, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetBringToBack(bool)", AS_METHODPR(BorderImage, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_bringToBack(bool)", AS_METHODPR(BorderImage, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetBringToFront(bool)", AS_METHODPR(BorderImage, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_bringToFront(bool)", AS_METHODPR(BorderImage, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(BorderImage, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetClipBorder(const IntRect&in)", AS_METHODPR(BorderImage, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_clipBorder(const IntRect&in)", AS_METHODPR(BorderImage, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetClipChildren(bool)", AS_METHODPR(BorderImage, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_clipChildren(bool)", AS_METHODPR(BorderImage, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetColor(const Color&in)", AS_METHODPR(BorderImage, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_color(const Color&in)", AS_METHODPR(BorderImage, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetColor(Corner, const Color&in)", AS_METHODPR(BorderImage, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_colors(Corner, const Color&in)", AS_METHODPR(BorderImage, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetDeepEnabled(bool)", AS_METHODPR(BorderImage, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(BorderImage, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(BorderImage, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetDisabledOffset(const IntVector2&in)", AS_METHODPR(BorderImage, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_disabledOffset(const IntVector2&in)", AS_METHODPR(BorderImage, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetDisabledOffset(int, int)", AS_METHODPR(BorderImage, SetDisabledOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(BorderImage, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(BorderImage, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetEditable(bool)", AS_METHODPR(BorderImage, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_editable(bool)", AS_METHODPR(BorderImage, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetElementEventSender(bool)", AS_METHODPR(BorderImage, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_elementEventSender(bool)", AS_METHODPR(BorderImage, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetEnableAnchor(bool)", AS_METHODPR(BorderImage, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_enableAnchor(bool)", AS_METHODPR(BorderImage, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetEnabled(bool)", AS_METHODPR(BorderImage, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_enabled(bool)", AS_METHODPR(BorderImage, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetEnabledRecursive(bool)", AS_METHODPR(BorderImage, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetFixedHeight(int)", AS_METHODPR(BorderImage, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(BorderImage, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetFixedSize(int, int)", AS_METHODPR(BorderImage, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetFixedWidth(int)", AS_METHODPR(BorderImage, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetFocus(bool)", AS_METHODPR(BorderImage, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_focus(bool)", AS_METHODPR(BorderImage, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetFocusMode(FocusMode)", AS_METHODPR(BorderImage, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_focusMode(FocusMode)", AS_METHODPR(BorderImage, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetFullImageRect()", AS_METHODPR(BorderImage, SetFullImageRect, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(BorderImage, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(BorderImage, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetHeight(int)", AS_METHODPR(BorderImage, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_height(int)", AS_METHODPR(BorderImage, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(BorderImage, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(BorderImage, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetHovering(bool)", AS_METHODPR(BorderImage, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetHoverOffset(const IntVector2&in)", AS_METHODPR(BorderImage, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_hoverOffset(const IntVector2&in)", AS_METHODPR(BorderImage, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetHoverOffset(int, int)", AS_METHODPR(BorderImage, SetHoverOffset, (int, int), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetImageBorder(const IntRect&in)", AS_METHODPR(BorderImage, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_imageBorder(const IntRect&in)", AS_METHODPR(BorderImage, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetImageRect(const IntRect&in)", AS_METHODPR(BorderImage, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_imageRect(const IntRect&in)", AS_METHODPR(BorderImage, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetIndent(int)", AS_METHODPR(BorderImage, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_indent(int)", AS_METHODPR(BorderImage, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetIndentSpacing(int)", AS_METHODPR(BorderImage, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_indentSpacing(int)", AS_METHODPR(BorderImage, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void SetInstanceDefault(bool)", AS_METHODPR(BorderImage, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(BorderImage, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetInternal(bool)", AS_METHODPR(BorderImage, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_internal(bool)", AS_METHODPR(BorderImage, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(BorderImage, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(BorderImage, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(BorderImage, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(BorderImage, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(BorderImage, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetLayoutMode(LayoutMode)", AS_METHODPR(BorderImage, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_layoutMode(LayoutMode)", AS_METHODPR(BorderImage, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetLayoutSpacing(int)", AS_METHODPR(BorderImage, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_layoutSpacing(int)", AS_METHODPR(BorderImage, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaterial(Material@+)", AS_METHODPR(BorderImage, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_material(Material@+)", AS_METHODPR(BorderImage, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(BorderImage, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(BorderImage, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(BorderImage, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxAnchor(float, float)", AS_METHODPR(BorderImage, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxHeight(int)", AS_METHODPR(BorderImage, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_maxHeight(int)", AS_METHODPR(BorderImage, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(BorderImage, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(BorderImage, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(BorderImage, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_maxSize(const IntVector2&in)", AS_METHODPR(BorderImage, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxSize(int, int)", AS_METHODPR(BorderImage, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMaxWidth(int)", AS_METHODPR(BorderImage, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_maxWidth(int)", AS_METHODPR(BorderImage, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(BorderImage, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_minAnchor(const Vector2&in)", AS_METHODPR(BorderImage, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinAnchor(float, float)", AS_METHODPR(BorderImage, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinHeight(int)", AS_METHODPR(BorderImage, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_minHeight(int)", AS_METHODPR(BorderImage, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(BorderImage, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_minOffset(const IntVector2&in)", AS_METHODPR(BorderImage, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinSize(const IntVector2&in)", AS_METHODPR(BorderImage, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_minSize(const IntVector2&in)", AS_METHODPR(BorderImage, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinSize(int, int)", AS_METHODPR(BorderImage, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetMinWidth(int)", AS_METHODPR(BorderImage, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_minWidth(int)", AS_METHODPR(BorderImage, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetName(const String&in)", AS_METHODPR(BorderImage, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_name(const String&in)", AS_METHODPR(BorderImage, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(BorderImage, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(BorderImage, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("BorderImage", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(BorderImage, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetOpacity(float)", AS_METHODPR(BorderImage, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_opacity(float)", AS_METHODPR(BorderImage, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(BorderImage, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetPivot(const Vector2&in)", AS_METHODPR(BorderImage, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_pivot(const Vector2&in)", AS_METHODPR(BorderImage, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetPivot(float, float)", AS_METHODPR(BorderImage, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetPosition(const IntVector2&in)", AS_METHODPR(BorderImage, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_position(const IntVector2&in)", AS_METHODPR(BorderImage, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetPosition(int, int)", AS_METHODPR(BorderImage, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetPriority(int)", AS_METHODPR(BorderImage, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_priority(int)", AS_METHODPR(BorderImage, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(BorderImage, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetSelected(bool)", AS_METHODPR(BorderImage, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_selected(bool)", AS_METHODPR(BorderImage, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetSize(const IntVector2&in)", AS_METHODPR(BorderImage, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_size(const IntVector2&in)", AS_METHODPR(BorderImage, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetSize(int, int)", AS_METHODPR(BorderImage, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetSortChildren(bool)", AS_METHODPR(BorderImage, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_sortChildren(bool)", AS_METHODPR(BorderImage, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(BorderImage, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool SetStyle(const XMLElement&in)", AS_METHODPR(BorderImage, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(BorderImage, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(BorderImage_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void SetTemporary(bool)", AS_METHODPR(BorderImage, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_temporary(bool)", AS_METHODPR(BorderImage, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetTexture(Texture@+)", AS_METHODPR(BorderImage, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_texture(Texture@+)", AS_METHODPR(BorderImage, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetTextureAttr(const ResourceRef&in)", AS_METHODPR(BorderImage, SetTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("BorderImage", "void SetTiled(bool)", AS_METHODPR(BorderImage, SetTiled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_tiled(bool)", AS_METHODPR(BorderImage, SetTiled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetTraversalMode(TraversalMode)", AS_METHODPR(BorderImage, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_traversalMode(TraversalMode)", AS_METHODPR(BorderImage, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetUseDerivedOpacity(bool)", AS_METHODPR(BorderImage, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_useDerivedOpacity(bool)", AS_METHODPR(BorderImage, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(BorderImage, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(BorderImage, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(BorderImage, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetVisible(bool)", AS_METHODPR(BorderImage, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_visible(bool)", AS_METHODPR(BorderImage, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SetWidth(int)", AS_METHODPR(BorderImage, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "void set_width(int)", AS_METHODPR(BorderImage, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void SortChildren()", AS_METHODPR(BorderImage, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void UnsubscribeFromAllEvents()", AS_METHODPR(BorderImage, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(BorderImage_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(BorderImage, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(BorderImage, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("BorderImage", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(BorderImage, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void Update(float)", AS_METHODPR(BorderImage, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("BorderImage", "void UpdateLayout()", AS_METHODPR(BorderImage, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("BorderImage", "int WeakRefs() const", AS_METHODPR(BorderImage, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BorderImage", "int get_weakRefs() const", AS_METHODPR(BorderImage, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(BorderImage, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(BorderImage, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("BorderImage", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(BorderImage, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const BoundingBox&in)", AS_FUNCTION_OBJFIRST(BoundingBox_BoundingBox_BoundingBox), AS_CALL_CDECL_OBJFIRST);
    // explicit BoundingBox::BoundingBox(const Rect& rect) noexcept | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Rect&in)", AS_FUNCTION_OBJFIRST(BoundingBox_BoundingBox_Rect), AS_CALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(const Vector3& min, const Vector3& max) noexcept | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(BoundingBox_BoundingBox_Vector3_Vector3), AS_CALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(float min, float max) noexcept | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(float, float)", AS_FUNCTION_OBJFIRST(BoundingBox_BoundingBox_float_float), AS_CALL_CDECL_OBJFIRST);
    // BoundingBox::BoundingBox(const Vector3* vertices, unsigned count) | File: ../Math/BoundingBox.h
    // Error: type "const Vector3*" can not automatically bind
    // explicit BoundingBox::BoundingBox(const Frustum& frustum) | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Frustum&in)", AS_FUNCTION_OBJFIRST(BoundingBox_BoundingBox_Frustum), AS_CALL_CDECL_OBJFIRST);
    // explicit BoundingBox::BoundingBox(const Polyhedron& poly) | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Polyhedron&in)", AS_FUNCTION_OBJFIRST(BoundingBox_BoundingBox_Polyhedron), AS_CALL_CDECL_OBJFIRST);
    // explicit BoundingBox::BoundingBox(const Sphere& sphere) | File: ../Math/BoundingBox.h
    engine->RegisterObjectBehaviour("BoundingBox", asBEHAVE_CONSTRUCT, "void f(const Sphere&in)", AS_FUNCTION_OBJFIRST(BoundingBox_BoundingBox_Sphere), AS_CALL_CDECL_OBJFIRST);
    // Vector3 BoundingBox::Center() const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Vector3 Center() const", AS_METHODPR(BoundingBox, Center, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_center() const", AS_METHODPR(BoundingBox, Center, () const, Vector3), AS_CALL_THISCALL);
    // void BoundingBox::Clear() | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Clear()", AS_METHODPR(BoundingBox, Clear, (), void), AS_CALL_THISCALL);
    // void BoundingBox::Clip(const BoundingBox& box) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Clip(const BoundingBox&in)", AS_METHODPR(BoundingBox, Clip, (const BoundingBox&), void), AS_CALL_THISCALL);
    // void BoundingBox::Define(const BoundingBox& box) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const BoundingBox&in)", AS_METHODPR(BoundingBox, Define, (const BoundingBox&), void), AS_CALL_THISCALL);
    // void BoundingBox::Define(const Rect& rect) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Rect&in)", AS_METHODPR(BoundingBox, Define, (const Rect&), void), AS_CALL_THISCALL);
    // void BoundingBox::Define(const Vector3& min, const Vector3& max) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Vector3&in, const Vector3&in)", AS_METHODPR(BoundingBox, Define, (const Vector3&, const Vector3&), void), AS_CALL_THISCALL);
    // void BoundingBox::Define(float min, float max) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(float, float)", AS_METHODPR(BoundingBox, Define, (float, float), void), AS_CALL_THISCALL);
    // void BoundingBox::Define(const Vector3& point) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Vector3&in)", AS_METHODPR(BoundingBox, Define, (const Vector3&), void), AS_CALL_THISCALL);
    // void BoundingBox::Define(const Vector3* vertices, unsigned count) | File: ../Math/BoundingBox.h
    // Error: type "const Vector3*" can not automatically bind
    // void BoundingBox::Define(const Frustum& frustum) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Frustum&in)", AS_METHODPR(BoundingBox, Define, (const Frustum&), void), AS_CALL_THISCALL);
    // void BoundingBox::Define(const Polyhedron& poly) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Polyhedron&in)", AS_METHODPR(BoundingBox, Define, (const Polyhedron&), void), AS_CALL_THISCALL);
    // void BoundingBox::Define(const Sphere& sphere) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Define(const Sphere&in)", AS_METHODPR(BoundingBox, Define, (const Sphere&), void), AS_CALL_THISCALL);
    // bool BoundingBox::Defined() const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "bool Defined() const", AS_METHODPR(BoundingBox, Defined, () const, bool), AS_CALL_THISCALL);
    // float BoundingBox::DistanceToPoint(const Vector3& point) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "float DistanceToPoint(const Vector3&in) const", AS_METHODPR(BoundingBox, DistanceToPoint, (const Vector3&) const, float), AS_CALL_THISCALL);
    // Vector3 BoundingBox::HalfSize() const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Vector3 HalfSize() const", AS_METHODPR(BoundingBox, HalfSize, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_halfSize() const", AS_METHODPR(BoundingBox, HalfSize, () const, Vector3), AS_CALL_THISCALL);
    // Intersection BoundingBox::IsInside(const Vector3& point) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const Vector3&in) const", AS_METHODPR(BoundingBox, IsInside, (const Vector3&) const, Intersection), AS_CALL_THISCALL);
    // Intersection BoundingBox::IsInside(const BoundingBox& box) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const BoundingBox&in) const", AS_METHODPR(BoundingBox, IsInside, (const BoundingBox&) const, Intersection), AS_CALL_THISCALL);
    // Intersection BoundingBox::IsInside(const Sphere& sphere) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInside(const Sphere&in) const", AS_METHODPR(BoundingBox, IsInside, (const Sphere&) const, Intersection), AS_CALL_THISCALL);
    // Intersection BoundingBox::IsInsideFast(const BoundingBox& box) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInsideFast(const BoundingBox&in) const", AS_METHODPR(BoundingBox, IsInsideFast, (const BoundingBox&) const, Intersection), AS_CALL_THISCALL);
    // Intersection BoundingBox::IsInsideFast(const Sphere& sphere) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Intersection IsInsideFast(const Sphere&in) const", AS_METHODPR(BoundingBox, IsInsideFast, (const Sphere&) const, Intersection), AS_CALL_THISCALL);
    // void BoundingBox::Merge(const Vector3& point) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Vector3&in)", AS_METHODPR(BoundingBox, Merge, (const Vector3&), void), AS_CALL_THISCALL);
    // void BoundingBox::Merge(const BoundingBox& box) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const BoundingBox&in)", AS_METHODPR(BoundingBox, Merge, (const BoundingBox&), void), AS_CALL_THISCALL);
    // void BoundingBox::Merge(const Vector3* vertices, unsigned count) | File: ../Math/BoundingBox.h
    // Error: type "const Vector3*" can not automatically bind
    // void BoundingBox::Merge(const Frustum& frustum) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Frustum&in)", AS_METHODPR(BoundingBox, Merge, (const Frustum&), void), AS_CALL_THISCALL);
    // void BoundingBox::Merge(const Polyhedron& poly) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Polyhedron&in)", AS_METHODPR(BoundingBox, Merge, (const Polyhedron&), void), AS_CALL_THISCALL);
    // void BoundingBox::Merge(const Sphere& sphere) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Merge(const Sphere&in)", AS_METHODPR(BoundingBox, Merge, (const Sphere&), void), AS_CALL_THISCALL);
    // BoundingBox& BoundingBox::operator=(const BoundingBox& rhs) noexcept | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox& opAssign(const BoundingBox&in)", AS_METHODPR(BoundingBox, operator=, (const BoundingBox&), BoundingBox&), AS_CALL_THISCALL);
    // BoundingBox& BoundingBox::operator=(const Rect& rhs) noexcept | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox& opAssign(const Rect&in)", AS_METHODPR(BoundingBox, operator=, (const Rect&), BoundingBox&), AS_CALL_THISCALL);
    // bool BoundingBox::operator==(const BoundingBox& rhs) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "bool opEquals(const BoundingBox&in) const", AS_METHODPR(BoundingBox, operator==, (const BoundingBox&) const, bool), AS_CALL_THISCALL);
    // Rect BoundingBox::Projected(const Matrix4& projection) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Rect Projected(const Matrix4&in) const", AS_METHODPR(BoundingBox, Projected, (const Matrix4&) const, Rect), AS_CALL_THISCALL);
    // Vector3 BoundingBox::Size() const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "Vector3 Size() const", AS_METHODPR(BoundingBox, Size, () const, Vector3), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BoundingBox", "Vector3 get_size() const", AS_METHODPR(BoundingBox, Size, () const, Vector3), AS_CALL_THISCALL);
    // String BoundingBox::ToString() const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "String ToString() const", AS_METHODPR(BoundingBox, ToString, () const, String), AS_CALL_THISCALL);
    // void BoundingBox::Transform(const Matrix3& transform) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Transform(const Matrix3&in)", AS_METHODPR(BoundingBox, Transform, (const Matrix3&), void), AS_CALL_THISCALL);
    // void BoundingBox::Transform(const Matrix3x4& transform) | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "void Transform(const Matrix3x4&in)", AS_METHODPR(BoundingBox, Transform, (const Matrix3x4&), void), AS_CALL_THISCALL);
    // BoundingBox BoundingBox::Transformed(const Matrix3& transform) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox Transformed(const Matrix3&in) const", AS_METHODPR(BoundingBox, Transformed, (const Matrix3&) const, BoundingBox), AS_CALL_THISCALL);
    // BoundingBox BoundingBox::Transformed(const Matrix3x4& transform) const | File: ../Math/BoundingBox.h
    engine->RegisterObjectMethod("BoundingBox", "BoundingBox Transformed(const Matrix3x4&in) const", AS_METHODPR(BoundingBox, Transformed, (const Matrix3x4&) const, BoundingBox), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("BufferedSoundStream", asBEHAVE_ADDREF, "void f()", AS_METHODPR(BufferedSoundStream, AddRef, (), void), AS_CALL_THISCALL);
    // void BufferedSoundStream::Clear() | File: ../Audio/BufferedSoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "void Clear()", AS_METHODPR(BufferedSoundStream, Clear, (), void), AS_CALL_THISCALL);
    // float BufferedSoundStream::GetBufferLength() const | File: ../Audio/BufferedSoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "float GetBufferLength() const", AS_METHODPR(BufferedSoundStream, GetBufferLength, () const, float), AS_CALL_THISCALL);
    // unsigned BufferedSoundStream::GetBufferNumBytes() const | File: ../Audio/BufferedSoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "uint GetBufferNumBytes() const", AS_METHODPR(BufferedSoundStream, GetBufferNumBytes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned BufferedSoundStream::GetData(signed char* dest, unsigned numBytes) override | File: ../Audio/BufferedSoundStream.h
    // Error: type "signed char*" can not automatically bind
    // float SoundStream::GetFrequency() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "float GetFrequency() const", AS_METHODPR(BufferedSoundStream, GetFrequency, () const, float), AS_CALL_THISCALL);
    // unsigned SoundStream::GetIntFrequency() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "uint GetIntFrequency() const", AS_METHODPR(BufferedSoundStream, GetIntFrequency, () const, unsigned), AS_CALL_THISCALL);
    // unsigned SoundStream::GetSampleSize() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "uint GetSampleSize() const", AS_METHODPR(BufferedSoundStream, GetSampleSize, () const, unsigned), AS_CALL_THISCALL);
    // bool SoundStream::GetStopAtEnd() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "bool GetStopAtEnd() const", AS_METHODPR(BufferedSoundStream, GetStopAtEnd, () const, bool), AS_CALL_THISCALL);
    // bool SoundStream::IsSixteenBit() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "bool IsSixteenBit() const", AS_METHODPR(BufferedSoundStream, IsSixteenBit, () const, bool), AS_CALL_THISCALL);
    // bool SoundStream::IsStereo() const | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "bool IsStereo() const", AS_METHODPR(BufferedSoundStream, IsStereo, () const, bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("BufferedSoundStream", "int Refs() const", AS_METHODPR(BufferedSoundStream, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BufferedSoundStream", "int get_refs() const", AS_METHODPR(BufferedSoundStream, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("BufferedSoundStream", asBEHAVE_RELEASE, "void f()", AS_METHODPR(BufferedSoundStream, ReleaseRef, (), void), AS_CALL_THISCALL);
    // virtual bool SoundStream::Seek(unsigned sample_number) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "bool Seek(uint)", AS_METHODPR(BufferedSoundStream, Seek, (unsigned), bool), AS_CALL_THISCALL);
    // void SoundStream::SetFormat(unsigned frequency, bool sixteenBit, bool stereo) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "void SetFormat(uint, bool, bool)", AS_METHODPR(BufferedSoundStream, SetFormat, (unsigned, bool, bool), void), AS_CALL_THISCALL);
    // void SoundStream::SetStopAtEnd(bool enable) | File: ../Audio/SoundStream.h
    engine->RegisterObjectMethod("BufferedSoundStream", "void SetStopAtEnd(bool)", AS_METHODPR(BufferedSoundStream, SetStopAtEnd, (bool), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("BufferedSoundStream", "int WeakRefs() const", AS_METHODPR(BufferedSoundStream, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("BufferedSoundStream", "int get_weakRefs() const", AS_METHODPR(BufferedSoundStream, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Button", "void AddChild(UIElement@+)", AS_METHODPR(Button, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Button", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Button, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void AddTag(const String&in)", AS_METHODPR(Button, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(Button, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Button_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void AdjustScissor(IntRect&)", AS_METHODPR(Button, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void AllocateNetworkState()", AS_METHODPR(Button, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void ApplyAttributes()", AS_METHODPR(Button, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void BringToFront()", AS_METHODPR(Button, BringToFront, (), void), AS_CALL_THISCALL);
    // explicit Button::Button(Context* context) | File: ../UI/Button.h
    engine->RegisterObjectBehaviour("Button", asBEHAVE_FACTORY, "Button@+ f()", AS_FUNCTION(Button_Button_Context), AS_CALL_CDECL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(Button, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void DisableLayoutUpdate()", AS_METHODPR(Button, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(Button, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void EnableLayoutUpdate()", AS_METHODPR(Button, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(Button, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "uint FindChild(UIElement@+) const", AS_METHODPR(Button, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "bool GetAnimationEnabled() const", AS_METHODPR(Button, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_animationEnabled() const", AS_METHODPR(Button, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const String& GetAppliedStyle() const", AS_METHODPR(Button, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const String& get_style() const", AS_METHODPR(Button, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "Variant GetAttribute(uint) const", AS_METHODPR(Button, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "Variant get_attributes(uint) const", AS_METHODPR(Button, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "Variant GetAttribute(const String&in) const", AS_METHODPR(Button, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Button, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Button, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Button, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Button, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Button, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Button, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Button, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void Button::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Button.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "BlendMode GetBlendMode() const", AS_METHODPR(Button, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "BlendMode get_blendMode() const", AS_METHODPR(Button, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "bool GetBlockEvents() const", AS_METHODPR(Button, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "const IntRect& GetBorder() const", AS_METHODPR(Button, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntRect& get_border() const", AS_METHODPR(Button, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool GetBringToBack() const", AS_METHODPR(Button, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_bringToBack() const", AS_METHODPR(Button, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool GetBringToFront() const", AS_METHODPR(Button, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_bringToFront() const", AS_METHODPR(Button, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "const String& GetCategory() const", AS_METHODPR(Button, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const String& get_category() const", AS_METHODPR(Button, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ GetChild(uint) const", AS_METHODPR(Button, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "UIElement@+ get_children(uint) const", AS_METHODPR(Button, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(Button, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(Button, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetChildOffset() const", AS_METHODPR(Button, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_childOffset() const", AS_METHODPR(Button, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(Button_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(Button_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(Button_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntRect& GetClipBorder() const", AS_METHODPR(Button, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntRect& get_clipBorder() const", AS_METHODPR(Button, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool GetClipChildren() const", AS_METHODPR(Button, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_clipChildren() const", AS_METHODPR(Button, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Color& GetColor(Corner) const", AS_METHODPR(Button, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const Color& get_colors(Corner) const", AS_METHODPR(Button, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Color& GetColorAttr() const", AS_METHODPR(Button, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "IntRect GetCombinedScreenRect()", AS_METHODPR(Button, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "IntRect get_combinedScreenRect()", AS_METHODPR(Button, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(Button, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Color& GetDerivedColor() const", AS_METHODPR(Button, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "float GetDerivedOpacity() const", AS_METHODPR(Button, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "float get_derivedOpacity() const", AS_METHODPR(Button, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetDisabledOffset() const", AS_METHODPR(Button, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_disabledOffset() const", AS_METHODPR(Button, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(Button, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(Button, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "uint GetDragButtonCount() const", AS_METHODPR(Button, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "uint get_dragButtonCount() const", AS_METHODPR(Button, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(Button, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(Button, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(Button, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ GetElementEventSender() const", AS_METHODPR(Button, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool GetEnableAnchor() const", AS_METHODPR(Button, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_enableAnchor() const", AS_METHODPR(Button, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "VariantMap& GetEventDataMap() const", AS_METHODPR(Button, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "Object@+ GetEventSender() const", AS_METHODPR(Button, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "FocusMode GetFocusMode() const", AS_METHODPR(Button, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "FocusMode get_focusMode() const", AS_METHODPR(Button, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Button, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Button, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Button, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const VariantMap& get_globalVars() const", AS_METHODPR(Button, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetHeight() const", AS_METHODPR(Button, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_height() const", AS_METHODPR(Button, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(Button, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(Button, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetHoverOffset() const", AS_METHODPR(Button, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_hoverOffset() const", AS_METHODPR(Button, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "const IntRect& GetImageBorder() const", AS_METHODPR(Button, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntRect& get_imageBorder() const", AS_METHODPR(Button, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "const IntRect& GetImageRect() const", AS_METHODPR(Button, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntRect& get_imageRect() const", AS_METHODPR(Button, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetIndent() const", AS_METHODPR(Button, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_indent() const", AS_METHODPR(Button, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetIndentSpacing() const", AS_METHODPR(Button, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_indentSpacing() const", AS_METHODPR(Button, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetIndentWidth() const", AS_METHODPR(Button, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_indentWidth() const", AS_METHODPR(Button, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Button, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntRect& GetLayoutBorder() const", AS_METHODPR(Button, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntRect& get_layoutBorder() const", AS_METHODPR(Button, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetLayoutElementMaxSize() const", AS_METHODPR(Button, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(Button, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(Button, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "LayoutMode GetLayoutMode() const", AS_METHODPR(Button, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "LayoutMode get_layoutMode() const", AS_METHODPR(Button, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetLayoutSpacing() const", AS_METHODPR(Button, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_layoutSpacing() const", AS_METHODPR(Button, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "Material@+ GetMaterial() const", AS_METHODPR(Button, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "Material@+ get_material() const", AS_METHODPR(Button, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "ResourceRef GetMaterialAttr() const", AS_METHODPR(Button, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Vector2& GetMaxAnchor() const", AS_METHODPR(Button, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const Vector2& get_maxAnchor() const", AS_METHODPR(Button, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetMaxHeight() const", AS_METHODPR(Button, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_maxHeight() const", AS_METHODPR(Button, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetMaxOffset() const", AS_METHODPR(Button, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_maxOffset() const", AS_METHODPR(Button, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetMaxSize() const", AS_METHODPR(Button, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_maxSize() const", AS_METHODPR(Button, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetMaxWidth() const", AS_METHODPR(Button, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_maxWidth() const", AS_METHODPR(Button, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Vector2& GetMinAnchor() const", AS_METHODPR(Button, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const Vector2& get_minAnchor() const", AS_METHODPR(Button, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetMinHeight() const", AS_METHODPR(Button, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_minHeight() const", AS_METHODPR(Button, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetMinOffset() const", AS_METHODPR(Button, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_minOffset() const", AS_METHODPR(Button, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetMinSize() const", AS_METHODPR(Button, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_minSize() const", AS_METHODPR(Button, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetMinWidth() const", AS_METHODPR(Button, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_minWidth() const", AS_METHODPR(Button, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const String& GetName() const", AS_METHODPR(Button, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const String& get_name() const", AS_METHODPR(Button, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "uint GetNumAttributes() const", AS_METHODPR(Button, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "uint get_numAttributes() const", AS_METHODPR(Button, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "uint GetNumChildren(bool = false) const", AS_METHODPR(Button, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "uint get_numChildren(bool = false) const", AS_METHODPR(Button, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "uint GetNumNetworkAttributes() const", AS_METHODPR(Button, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Button, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Button, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Button, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "float GetOpacity() const", AS_METHODPR(Button, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "float get_opacity() const", AS_METHODPR(Button, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ GetParent() const", AS_METHODPR(Button, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "UIElement@+ get_parent() const", AS_METHODPR(Button, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Vector2& GetPivot() const", AS_METHODPR(Button, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const Vector2& get_pivot() const", AS_METHODPR(Button, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetPosition() const", AS_METHODPR(Button, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_position() const", AS_METHODPR(Button, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& Button::GetPressedChildOffset() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetPressedChildOffset() const", AS_METHODPR(Button, GetPressedChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_pressedChildOffset() const", AS_METHODPR(Button, GetPressedChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& Button::GetPressedOffset() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetPressedOffset() const", AS_METHODPR(Button, GetPressedOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_pressedOffset() const", AS_METHODPR(Button, GetPressedOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetPriority() const", AS_METHODPR(Button, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_priority() const", AS_METHODPR(Button, GetPriority, () const, int), AS_CALL_THISCALL);
    // float Button::GetRepeatDelay() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "float GetRepeatDelay() const", AS_METHODPR(Button, GetRepeatDelay, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "float get_repeatDelay() const", AS_METHODPR(Button, GetRepeatDelay, () const, float), AS_CALL_THISCALL);
    // float Button::GetRepeatRate() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "float GetRepeatRate() const", AS_METHODPR(Button, GetRepeatRate, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "float get_repeatRate() const", AS_METHODPR(Button, GetRepeatRate, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ GetRoot() const", AS_METHODPR(Button, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "UIElement@+ get_root() const", AS_METHODPR(Button, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetScreenPosition() const", AS_METHODPR(Button, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_screenPosition() const", AS_METHODPR(Button, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const IntVector2& GetSize() const", AS_METHODPR(Button, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const IntVector2& get_size() const", AS_METHODPR(Button, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool GetSortChildren() const", AS_METHODPR(Button, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_sortChildren() const", AS_METHODPR(Button, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Button, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(Button_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Button", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(Button_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "Texture@+ GetTexture() const", AS_METHODPR(Button, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "Texture@+ get_texture() const", AS_METHODPR(Button, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "ResourceRef GetTextureAttr() const", AS_METHODPR(Button, GetTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "TraversalMode GetTraversalMode() const", AS_METHODPR(Button, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "TraversalMode get_traversalMode() const", AS_METHODPR(Button, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "StringHash GetType() const", AS_METHODPR(Button, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "StringHash get_type() const", AS_METHODPR(Button, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "const String& GetTypeName() const", AS_METHODPR(Button, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "const String& get_typeName() const", AS_METHODPR(Button, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool GetUseDerivedOpacity() const", AS_METHODPR(Button, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_useDerivedOpacity() const", AS_METHODPR(Button, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(Button, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "const VariantMap& GetVars() const", AS_METHODPR(Button, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(Button, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(Button, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "int GetWidth() const", AS_METHODPR(Button, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_width() const", AS_METHODPR(Button, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool HasColorGradient() const", AS_METHODPR(Button, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_colorGradient() const", AS_METHODPR(Button, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "bool HasEventHandlers() const", AS_METHODPR(Button, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool HasFocus() const", AS_METHODPR(Button, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_focus() const", AS_METHODPR(Button, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Button, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Button, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool HasTag(const String&in) const", AS_METHODPR(Button, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void InsertChild(uint, UIElement@+)", AS_METHODPR(Button, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsChildOf(UIElement@+) const", AS_METHODPR(Button, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsEditable() const", AS_METHODPR(Button, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_editable() const", AS_METHODPR(Button, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsElementEventSender() const", AS_METHODPR(Button, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_elementEventSender() const", AS_METHODPR(Button, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsEnabled() const", AS_METHODPR(Button, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_enabled() const", AS_METHODPR(Button, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsEnabledSelf() const", AS_METHODPR(Button, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_enabledSelf() const", AS_METHODPR(Button, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsFixedHeight() const", AS_METHODPR(Button, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_fixedHeight() const", AS_METHODPR(Button, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsFixedSize() const", AS_METHODPR(Button, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_fixedSize() const", AS_METHODPR(Button, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsFixedWidth() const", AS_METHODPR(Button, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_fixedWidth() const", AS_METHODPR(Button, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsHovering() const", AS_METHODPR(Button, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_hovering() const", AS_METHODPR(Button, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsInside(IntVector2, bool)", AS_METHODPR(Button, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(Button, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Button, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsInternal() const", AS_METHODPR(Button, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_internal() const", AS_METHODPR(Button, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool Button::IsPressed() const | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "bool IsPressed() const", AS_METHODPR(Button, IsPressed, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_pressed() const", AS_METHODPR(Button, IsPressed, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsSelected() const", AS_METHODPR(Button, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_selected() const", AS_METHODPR(Button, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool IsTemporary() const", AS_METHODPR(Button, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_temporary() const", AS_METHODPR(Button, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "bool IsTiled() const", AS_METHODPR(Button, IsTiled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_tiled() const", AS_METHODPR(Button, IsTiled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsVisible() const", AS_METHODPR(Button, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_visible() const", AS_METHODPR(Button, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsVisibleEffective() const", AS_METHODPR(Button, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool get_visibleEffective() const", AS_METHODPR(Button, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsWheelHandler() const", AS_METHODPR(Button, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(Button, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool Load(Deserializer&)", AS_METHODPR(Button, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Button, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Button, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Button, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Button, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool LoadXML(Deserializer&)", AS_METHODPR(Button, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void MarkNetworkUpdate()", AS_METHODPR(Button, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void Button::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Button, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Button::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(Button, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Button, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Button, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Button, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(Button, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(Button, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Button, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Button::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Button, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Button, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Button, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Button, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnIndentSet()", AS_METHODPR(Button, OnIndentSet, (), void), AS_CALL_THISCALL);
    // void Button::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Button, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(Button, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(Button, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Button, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnSetEditable()", AS_METHODPR(Button, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnTextInput(const String&in)", AS_METHODPR(Button, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Button, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Button, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Button, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Button", "int Refs() const", AS_METHODPR(Button, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_refs() const", AS_METHODPR(Button, Refs, () const, int), AS_CALL_THISCALL);
    // static void Button::RegisterObject(Context* context) | File: ../UI/Button.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Button", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Button, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void Remove()", AS_METHODPR(Button, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void RemoveAllChildren()", AS_METHODPR(Button, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void RemoveAllTags()", AS_METHODPR(Button, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Button, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(Button, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void RemoveChildAtIndex(uint)", AS_METHODPR(Button, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void RemoveInstanceDefault()", AS_METHODPR(Button, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void RemoveObjectAnimation()", AS_METHODPR(Button, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool RemoveTag(const String&in)", AS_METHODPR(Button, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void ResetDeepEnabled()", AS_METHODPR(Button, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void ResetToDefault()", AS_METHODPR(Button, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool Save(Serializer&) const", AS_METHODPR(Button, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool SaveDefaultAttributes() const", AS_METHODPR(Button, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Button, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool SaveXML(XMLElement&) const", AS_METHODPR(Button, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(Button, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(Button, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void SendEvent(StringHash)", AS_METHODPR(Button, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Button, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(Button, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetAnimationEnabled(bool)", AS_METHODPR(Button, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_animationEnabled(bool)", AS_METHODPR(Button, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetAnimationTime(float)", AS_METHODPR(Button, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Button, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Button, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Button, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Button, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Button, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Button, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Button, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetBlendMode(BlendMode)", AS_METHODPR(Button, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_blendMode(BlendMode)", AS_METHODPR(Button, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void SetBlockEvents(bool)", AS_METHODPR(Button, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetBorder(const IntRect&in)", AS_METHODPR(Button, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_border(const IntRect&in)", AS_METHODPR(Button, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetBringToBack(bool)", AS_METHODPR(Button, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_bringToBack(bool)", AS_METHODPR(Button, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetBringToFront(bool)", AS_METHODPR(Button, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_bringToFront(bool)", AS_METHODPR(Button, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(Button, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetClipBorder(const IntRect&in)", AS_METHODPR(Button, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_clipBorder(const IntRect&in)", AS_METHODPR(Button, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetClipChildren(bool)", AS_METHODPR(Button, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_clipChildren(bool)", AS_METHODPR(Button, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetColor(const Color&in)", AS_METHODPR(Button, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_color(const Color&in)", AS_METHODPR(Button, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetColor(Corner, const Color&in)", AS_METHODPR(Button, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_colors(Corner, const Color&in)", AS_METHODPR(Button, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetDeepEnabled(bool)", AS_METHODPR(Button, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(Button, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(Button, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetDisabledOffset(const IntVector2&in)", AS_METHODPR(Button, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_disabledOffset(const IntVector2&in)", AS_METHODPR(Button, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetDisabledOffset(int, int)", AS_METHODPR(Button, SetDisabledOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(Button, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(Button, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetEditable(bool)", AS_METHODPR(Button, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_editable(bool)", AS_METHODPR(Button, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetElementEventSender(bool)", AS_METHODPR(Button, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_elementEventSender(bool)", AS_METHODPR(Button, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetEnableAnchor(bool)", AS_METHODPR(Button, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_enableAnchor(bool)", AS_METHODPR(Button, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetEnabled(bool)", AS_METHODPR(Button, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_enabled(bool)", AS_METHODPR(Button, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetEnabledRecursive(bool)", AS_METHODPR(Button, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetFixedHeight(int)", AS_METHODPR(Button, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(Button, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetFixedSize(int, int)", AS_METHODPR(Button, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetFixedWidth(int)", AS_METHODPR(Button, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetFocus(bool)", AS_METHODPR(Button, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_focus(bool)", AS_METHODPR(Button, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetFocusMode(FocusMode)", AS_METHODPR(Button, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_focusMode(FocusMode)", AS_METHODPR(Button, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetFullImageRect()", AS_METHODPR(Button, SetFullImageRect, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Button, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Button, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetHeight(int)", AS_METHODPR(Button, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_height(int)", AS_METHODPR(Button, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(Button, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(Button, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetHovering(bool)", AS_METHODPR(Button, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetHoverOffset(const IntVector2&in)", AS_METHODPR(Button, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_hoverOffset(const IntVector2&in)", AS_METHODPR(Button, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetHoverOffset(int, int)", AS_METHODPR(Button, SetHoverOffset, (int, int), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetImageBorder(const IntRect&in)", AS_METHODPR(Button, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_imageBorder(const IntRect&in)", AS_METHODPR(Button, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetImageRect(const IntRect&in)", AS_METHODPR(Button, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_imageRect(const IntRect&in)", AS_METHODPR(Button, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetIndent(int)", AS_METHODPR(Button, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_indent(int)", AS_METHODPR(Button, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetIndentSpacing(int)", AS_METHODPR(Button, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_indentSpacing(int)", AS_METHODPR(Button, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void SetInstanceDefault(bool)", AS_METHODPR(Button, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Button, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetInternal(bool)", AS_METHODPR(Button, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_internal(bool)", AS_METHODPR(Button, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(Button, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(Button, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(Button, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(Button, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(Button, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetLayoutMode(LayoutMode)", AS_METHODPR(Button, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_layoutMode(LayoutMode)", AS_METHODPR(Button, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetLayoutSpacing(int)", AS_METHODPR(Button, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_layoutSpacing(int)", AS_METHODPR(Button, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetMaterial(Material@+)", AS_METHODPR(Button, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_material(Material@+)", AS_METHODPR(Button, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(Button, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(Button, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(Button, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxAnchor(float, float)", AS_METHODPR(Button, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxHeight(int)", AS_METHODPR(Button, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_maxHeight(int)", AS_METHODPR(Button, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(Button, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(Button, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(Button, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_maxSize(const IntVector2&in)", AS_METHODPR(Button, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxSize(int, int)", AS_METHODPR(Button, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMaxWidth(int)", AS_METHODPR(Button, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_maxWidth(int)", AS_METHODPR(Button, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(Button, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_minAnchor(const Vector2&in)", AS_METHODPR(Button, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinAnchor(float, float)", AS_METHODPR(Button, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinHeight(int)", AS_METHODPR(Button, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_minHeight(int)", AS_METHODPR(Button, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(Button, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_minOffset(const IntVector2&in)", AS_METHODPR(Button, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinSize(const IntVector2&in)", AS_METHODPR(Button, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_minSize(const IntVector2&in)", AS_METHODPR(Button, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinSize(int, int)", AS_METHODPR(Button, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetMinWidth(int)", AS_METHODPR(Button, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_minWidth(int)", AS_METHODPR(Button, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetName(const String&in)", AS_METHODPR(Button, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_name(const String&in)", AS_METHODPR(Button, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Button, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Button, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Button", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Button, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetOpacity(float)", AS_METHODPR(Button, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_opacity(float)", AS_METHODPR(Button, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(Button, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetPivot(const Vector2&in)", AS_METHODPR(Button, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_pivot(const Vector2&in)", AS_METHODPR(Button, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetPivot(float, float)", AS_METHODPR(Button, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetPosition(const IntVector2&in)", AS_METHODPR(Button, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_position(const IntVector2&in)", AS_METHODPR(Button, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetPosition(int, int)", AS_METHODPR(Button, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void Button::SetPressedChildOffset(const IntVector2& offset) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetPressedChildOffset(const IntVector2&in)", AS_METHODPR(Button, SetPressedChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_pressedChildOffset(const IntVector2&in)", AS_METHODPR(Button, SetPressedChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Button::SetPressedChildOffset(int x, int y) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetPressedChildOffset(int, int)", AS_METHODPR(Button, SetPressedChildOffset, (int, int), void), AS_CALL_THISCALL);
    // void Button::SetPressedOffset(const IntVector2& offset) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetPressedOffset(const IntVector2&in)", AS_METHODPR(Button, SetPressedOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_pressedOffset(const IntVector2&in)", AS_METHODPR(Button, SetPressedOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Button::SetPressedOffset(int x, int y) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetPressedOffset(int, int)", AS_METHODPR(Button, SetPressedOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetPriority(int)", AS_METHODPR(Button, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_priority(int)", AS_METHODPR(Button, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(Button, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void Button::SetRepeat(float delay, float rate) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetRepeat(float, float)", AS_METHODPR(Button, SetRepeat, (float, float), void), AS_CALL_THISCALL);
    // void Button::SetRepeatDelay(float delay) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetRepeatDelay(float)", AS_METHODPR(Button, SetRepeatDelay, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_repeatDelay(float)", AS_METHODPR(Button, SetRepeatDelay, (float), void), AS_CALL_THISCALL);
    // void Button::SetRepeatRate(float rate) | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void SetRepeatRate(float)", AS_METHODPR(Button, SetRepeatRate, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_repeatRate(float)", AS_METHODPR(Button, SetRepeatRate, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetSelected(bool)", AS_METHODPR(Button, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_selected(bool)", AS_METHODPR(Button, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetSize(const IntVector2&in)", AS_METHODPR(Button, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_size(const IntVector2&in)", AS_METHODPR(Button, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetSize(int, int)", AS_METHODPR(Button, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetSortChildren(bool)", AS_METHODPR(Button, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_sortChildren(bool)", AS_METHODPR(Button, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(Button, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool SetStyle(const XMLElement&in)", AS_METHODPR(Button, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(Button, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Button_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void SetTemporary(bool)", AS_METHODPR(Button, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_temporary(bool)", AS_METHODPR(Button, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetTexture(Texture@+)", AS_METHODPR(Button, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_texture(Texture@+)", AS_METHODPR(Button, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetTextureAttr(const ResourceRef&in)", AS_METHODPR(Button, SetTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Button", "void SetTiled(bool)", AS_METHODPR(Button, SetTiled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_tiled(bool)", AS_METHODPR(Button, SetTiled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetTraversalMode(TraversalMode)", AS_METHODPR(Button, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_traversalMode(TraversalMode)", AS_METHODPR(Button, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetUseDerivedOpacity(bool)", AS_METHODPR(Button, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_useDerivedOpacity(bool)", AS_METHODPR(Button, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(Button, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(Button, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(Button, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetVisible(bool)", AS_METHODPR(Button, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_visible(bool)", AS_METHODPR(Button, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SetWidth(int)", AS_METHODPR(Button, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "void set_width(int)", AS_METHODPR(Button, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void SortChildren()", AS_METHODPR(Button, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void UnsubscribeFromAllEvents()", AS_METHODPR(Button, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Button_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Button, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Button, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Button", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Button, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void Button::Update(float timeStep) override | File: ../UI/Button.h
    engine->RegisterObjectMethod("Button", "void Update(float)", AS_METHODPR(Button, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Button", "void UpdateLayout()", AS_METHODPR(Button, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Button", "int WeakRefs() const", AS_METHODPR(Button, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Button", "int get_weakRefs() const", AS_METHODPR(Button, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Button, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Button, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Button", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Button, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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

    // HashSet<Pair<StringHash, StringHash>> BackgroundLoadItem::dependencies_ | File: ../Resource/BackgroundLoader.h
    // Error: type "HashSet<Pair<StringHash, StringHash>>" can not automatically bind
    // HashSet<Pair<StringHash, StringHash>> BackgroundLoadItem::dependents_ | File: ../Resource/BackgroundLoader.h
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
    engine->RegisterObjectBehaviour("Batch", asBEHAVE_CONSTRUCT, "void f(const SourceBatch&in)", AS_FUNCTION_OBJFIRST(Batch_Batch_SourceBatch), AS_CALL_CDECL_OBJFIRST);
    // void Batch::CalculateSortKey() | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("Batch", "void CalculateSortKey()", AS_METHODPR(Batch, CalculateSortKey, (), void), AS_CALL_THISCALL);
    // void Batch::Draw(View* view, Camera* camera, bool allowDepthWrite) const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("Batch", "void Draw(View@+, Camera@+, bool) const", AS_METHODPR(Batch, Draw, (View*, Camera*, bool) const, void), AS_CALL_THISCALL);
    // void Batch::Prepare(View* view, Camera* camera, bool setModelTransform, bool allowDepthWrite) const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("Batch", "void Prepare(View@+, Camera@+, bool, bool) const", AS_METHODPR(Batch, Prepare, (View*, Camera*, bool, bool) const, void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("BatchGroup", "void AddTransforms(const Batch&in)", AS_METHODPR(BatchGroup, AddTransforms, (const Batch&), void), AS_CALL_THISCALL);
    // explicit BatchGroup::BatchGroup(const Batch& batch) | File: ../Graphics/Batch.h
    engine->RegisterObjectBehaviour("BatchGroup", asBEHAVE_CONSTRUCT, "void f(const Batch&in)", AS_FUNCTION_OBJFIRST(BatchGroup_BatchGroup_Batch), AS_CALL_CDECL_OBJFIRST);
    // void Batch::CalculateSortKey() | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchGroup", "void CalculateSortKey()", AS_METHODPR(BatchGroup, CalculateSortKey, (), void), AS_CALL_THISCALL);
    // void BatchGroup::Draw(View* view, Camera* camera, bool allowDepthWrite) const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchGroup", "void Draw(View@+, Camera@+, bool) const", AS_METHODPR(BatchGroup, Draw, (View*, Camera*, bool) const, void), AS_CALL_THISCALL);
    // void Batch::Prepare(View* view, Camera* camera, bool setModelTransform, bool allowDepthWrite) const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchGroup", "void Prepare(View@+, Camera@+, bool, bool) const", AS_METHODPR(BatchGroup, Prepare, (View*, Camera*, bool, bool) const, void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("BatchGroupKey", asBEHAVE_CONSTRUCT, "void f(const Batch&in)", AS_FUNCTION_OBJFIRST(BatchGroupKey_BatchGroupKey_Batch), AS_CALL_CDECL_OBJFIRST);
    // bool BatchGroupKey::operator==(const BatchGroupKey& rhs) const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchGroupKey", "bool opEquals(const BatchGroupKey&in) const", AS_METHODPR(BatchGroupKey, operator==, (const BatchGroupKey&) const, bool), AS_CALL_THISCALL);
    // unsigned BatchGroupKey::ToHash() const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchGroupKey", "uint ToHash() const", AS_METHODPR(BatchGroupKey, ToHash, () const, unsigned), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("BatchQueue", "void Clear(int)", AS_METHODPR(BatchQueue, Clear, (int), void), AS_CALL_THISCALL);
    // void BatchQueue::Draw(View* view, Camera* camera, bool markToStencil, bool usingLightOptimization, bool allowDepthWrite) const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchQueue", "void Draw(View@+, Camera@+, bool, bool, bool) const", AS_METHODPR(BatchQueue, Draw, (View*, Camera*, bool, bool, bool) const, void), AS_CALL_THISCALL);
    // unsigned BatchQueue::GetNumInstances() const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchQueue", "uint GetNumInstances() const", AS_METHODPR(BatchQueue, GetNumInstances, () const, unsigned), AS_CALL_THISCALL);
    // bool BatchQueue::IsEmpty() const | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchQueue", "bool IsEmpty() const", AS_METHODPR(BatchQueue, IsEmpty, () const, bool), AS_CALL_THISCALL);
    // void BatchQueue::SetInstancingData(void* lockedData, unsigned stride, unsigned& freeIndex) | File: ../Graphics/Batch.h
    // Error: type "void*" can not automatically bind
    // void BatchQueue::SortBackToFront() | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchQueue", "void SortBackToFront()", AS_METHODPR(BatchQueue, SortBackToFront, (), void), AS_CALL_THISCALL);
    // void BatchQueue::SortFrontToBack() | File: ../Graphics/Batch.h
    engine->RegisterObjectMethod("BatchQueue", "void SortFrontToBack()", AS_METHODPR(BatchQueue, SortFrontToBack, (), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("BiasParameters", asBEHAVE_CONSTRUCT, "void f(float, float, float = 0.0f)", AS_FUNCTION_OBJFIRST(BiasParameters_BiasParameters_float_float_float), AS_CALL_CDECL_OBJFIRST);
    // void BiasParameters::Validate() | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("BiasParameters", "void Validate()", AS_METHODPR(BiasParameters, Validate, (), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Billboard", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Billboard", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
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
    // Bone& Bone::operator=(const Bone&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<Bone>(engine, "Bone");
    engine->RegisterObjectBehaviour("Bone", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Bone", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_Bone
    REGISTER_MANUAL_PART_Bone(Bone, "Bone")
#endif

}

}
