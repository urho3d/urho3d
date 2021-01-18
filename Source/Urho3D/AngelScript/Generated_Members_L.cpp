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
static CScriptArray* Light_GetLights_void(Light* ptr)
{
    const PODVector<Light*>& result = ptr->GetLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
static CScriptArray* Light_GetVertexLights_void(Light* ptr)
{
    const PODVector<Light*>& result = ptr->GetVertexLights();
    return VectorToHandleArray(result, "Array<Light@>");
}

// explicit Light::Light(Context* context) | File: ../Graphics/Light.h
static Light* Light_Light_Context()
{
    return new Light(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Light_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Light* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* LineEdit_GetChildren_void(LineEdit* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* LineEdit_GetChildren_bool(LineEdit* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* LineEdit_GetChildrenWithTag_String_bool(LineEdit* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* LineEdit_GetTags_void(LineEdit* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// explicit LineEdit::LineEdit(Context* context) | File: ../UI/LineEdit.h
static LineEdit* LineEdit_LineEdit_Context()
{
    return new LineEdit(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void LineEdit_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(LineEdit* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* ListView_GetChildren_void(ListView* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* ListView_GetChildren_bool(ListView* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* ListView_GetChildrenWithTag_String_bool(ListView* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> ListView::GetItems() const | File: ../UI/ListView.h
static CScriptArray* ListView_GetItems_void(ListView* ptr)
{
    PODVector<UIElement*> result = ptr->GetItems();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> ListView::GetSelectedItems() const | File: ../UI/ListView.h
static CScriptArray* ListView_GetSelectedItems_void(ListView* ptr)
{
    PODVector<UIElement*> result = ptr->GetSelectedItems();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const PODVector<unsigned>& ListView::GetSelections() const | File: ../UI/ListView.h
static CScriptArray* ListView_GetSelections_void(ListView* ptr)
{
    const PODVector<unsigned>& result = ptr->GetSelections();
    return VectorToArray(result, "Array<uint>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* ListView_GetTags_void(ListView* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// explicit ListView::ListView(Context* context) | File: ../UI/ListView.h
static ListView* ListView_ListView_Context()
{
    return new ListView(GetScriptContext());
}

// void ListView::SetSelections(const PODVector<unsigned>& indices) | File: ../UI/ListView.h
static void ListView_SetSelections_PODVectorunsigned(ListView* ptr, CScriptArray* indices)
{
    PODVector<unsigned> param0 = ArrayToPODVector<unsigned>(indices);
    ptr->SetSelections(param0);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ListView_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ListView* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// explicit Localization::Localization(Context* context) | File: ../Resource/Localization.h
static Localization* Localization_Localization_Context()
{
    return new Localization(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Localization_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Localization* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// explicit Log::Log(Context* context) | File: ../IO/Log.h
static Log* Log_Log_Context()
{
    return new Log(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Log_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Log* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void LogicComponent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(LogicComponent* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

void ASRegisterGenerated_Members_L(asIScriptEngine* engine)
{
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void AddLight(Light@+)", asMETHODPR(Light, AddLight, (Light*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Light", asBEHAVE_ADDREF, "void f()", asMETHODPR(Light, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void AddVertexLight(Light@+)", asMETHODPR(Light, AddVertexLight, (Light*), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void AllocateNetworkState()", asMETHODPR(Light, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void ApplyAttributes()", asMETHODPR(Light, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Light::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(Light, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool DrawOcclusion(OcclusionBuffer@+)", asMETHODPR(Light, DrawOcclusion, (OcclusionBuffer*), bool), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "bool GetAnimationEnabled() const", asMETHODPR(Light, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_animationEnabled() const", asMETHODPR(Light, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // float Light::GetAspectRatio() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetAspectRatio() const", asMETHODPR(Light, GetAspectRatio, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_aspectRatio() const", asMETHODPR(Light, GetAspectRatio, () const, float), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "Variant GetAttribute(uint) const", asMETHODPR(Light, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Variant get_attributes(uint) const", asMETHODPR(Light, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "Variant GetAttribute(const String&in) const", asMETHODPR(Light, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Light, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Light, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Light, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Light, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "Variant GetAttributeDefault(uint) const", asMETHODPR(Light, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Variant get_attributeDefaults(uint) const", asMETHODPR(Light, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Light, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "bool GetBlockEvents() const", asMETHODPR(Light, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "const BoundingBox& GetBoundingBox() const", asMETHODPR(Light, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const BoundingBox& get_boundingBox() const", asMETHODPR(Light, GetBoundingBox, () const, const BoundingBox&), asCALL_THISCALL);
    // float Light::GetBrightness() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetBrightness() const", asMETHODPR(Light, GetBrightness, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_brightness() const", asMETHODPR(Light, GetBrightness, () const, float), asCALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool GetCastShadows() const", asMETHODPR(Light, GetCastShadows, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_castShadows() const", asMETHODPR(Light, GetCastShadows, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "const String& GetCategory() const", asMETHODPR(Light, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const String& get_category() const", asMETHODPR(Light, GetCategory, () const, const String&), asCALL_THISCALL);
    // const Color& Light::GetColor() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "const Color& GetColor() const", asMETHODPR(Light, GetColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const Color& get_color() const", asMETHODPR(Light, GetColor, () const, const Color&), asCALL_THISCALL);
    // Color Light::GetColorFromTemperature() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "Color GetColorFromTemperature() const", asMETHODPR(Light, GetColorFromTemperature, () const, Color), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Color get_colorFromTemperature() const", asMETHODPR(Light, GetColorFromTemperature, () const, Color), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "Component@+ GetComponent(StringHash) const", asMETHODPR(Light, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Light", "float GetDistance() const", asMETHODPR(Light, GetDistance, () const, float), asCALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint8 GetDrawableFlags() const", asMETHODPR(Light, GetDrawableFlags, () const, unsigned char), asCALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetDrawDistance() const", asMETHODPR(Light, GetDrawDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_drawDistance() const", asMETHODPR(Light, GetDrawDistance, () const, float), asCALL_THISCALL);
    // Color Light::GetEffectiveColor() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "Color GetEffectiveColor() const", asMETHODPR(Light, GetEffectiveColor, () const, Color), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Color get_effectiveColor() const", asMETHODPR(Light, GetEffectiveColor, () const, Color), asCALL_THISCALL);
    // float Light::GetEffectiveSpecularIntensity() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetEffectiveSpecularIntensity() const", asMETHODPR(Light, GetEffectiveSpecularIntensity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_effectiveSpecularIntensity() const", asMETHODPR(Light, GetEffectiveSpecularIntensity, () const, float), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "VariantMap& GetEventDataMap() const", asMETHODPR(Light, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "Object@+ GetEventSender() const", asMETHODPR(Light, GetEventSender, () const, Object*), asCALL_THISCALL);
    // float Light::GetFadeDistance() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetFadeDistance() const", asMETHODPR(Light, GetFadeDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_fadeDistance() const", asMETHODPR(Light, GetFadeDistance, () const, float), asCALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "Light@+ GetFirstLight() const", asMETHODPR(Light, GetFirstLight, () const, Light*), asCALL_THISCALL);
    // float Light::GetFov() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetFov() const", asMETHODPR(Light, GetFov, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_fov() const", asMETHODPR(Light, GetFov, () const, float), asCALL_THISCALL);
    // Frustum Light::GetFrustum() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "Frustum GetFrustum() const", asMETHODPR(Light, GetFrustum, () const, Frustum), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Frustum get_frustum() const", asMETHODPR(Light, GetFrustum, () const, Frustum), asCALL_THISCALL);
    // static Matrix3x4 Light::GetFullscreenQuadTransform(Camera* camera) | File: ../Graphics/Light.h
    engine->SetDefaultNamespace("Light");
    engine->RegisterGlobalFunction("Matrix3x4 GetFullscreenQuadTransform(Camera@+)", asFUNCTIONPR(Light::GetFullscreenQuadTransform, (Camera*), Matrix3x4), asCALL_CDECL);
    engine->SetDefaultNamespace("");
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Light, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Light, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "const VariantMap& GetGlobalVars() const", asMETHODPR(Light, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const VariantMap& get_globalVars() const", asMETHODPR(Light, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "uint GetID() const", asMETHODPR(Light, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_id() const", asMETHODPR(Light, GetID, () const, unsigned), asCALL_THISCALL);
    // float Light::GetIntensityDivisor(float attenuation=1.0f) const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetIntensityDivisor(float = 1.0f) const", asMETHODPR(Light, GetIntensityDivisor, (float) const, float), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Light, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // float Light::GetLength() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetLength() const", asMETHODPR(Light, GetLength, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_length() const", asMETHODPR(Light, GetLength, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint GetLightMask() const", asMETHODPR(Light, GetLightMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_lightMask() const", asMETHODPR(Light, GetLightMask, () const, unsigned), asCALL_THISCALL);
    // LightBatchQueue* Light::GetLightQueue() const | File: ../Graphics/Light.h
    // Error: type "LightBatchQueue*" can not automatically bind
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "Array<Light@>@ GetLights() const", asFUNCTION(Light_GetLights_void), asCALL_CDECL_OBJFIRST);
    // LightType Light::GetLightType() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "LightType GetLightType() const", asMETHODPR(Light, GetLightType, () const, LightType), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "LightType get_lightType() const", asMETHODPR(Light, GetLightType, () const, LightType), asCALL_THISCALL);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetLodBias() const", asMETHODPR(Light, GetLodBias, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_lodBias() const", asMETHODPR(Light, GetLodBias, () const, float), asCALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetLodDistance() const", asMETHODPR(Light, GetLodDistance, () const, float), asCALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "Geometry@+ GetLodGeometry(uint, uint)", asMETHODPR(Light, GetLodGeometry, (unsigned, unsigned), Geometry*), asCALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint GetMaxLights() const", asMETHODPR(Light, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_maxLights() const", asMETHODPR(Light, GetMaxLights, () const, unsigned), asCALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetMaxZ() const", asMETHODPR(Light, GetMaxZ, () const, float), asCALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetMinZ() const", asMETHODPR(Light, GetMinZ, () const, float), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "Node@+ GetNode() const", asMETHODPR(Light, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Node@+ get_node() const", asMETHODPR(Light, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "uint GetNumAttributes() const", asMETHODPR(Light, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_numAttributes() const", asMETHODPR(Light, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "uint GetNumNetworkAttributes() const", asMETHODPR(Light, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint GetNumOccluderTriangles()", asMETHODPR(Light, GetNumOccluderTriangles, (), unsigned), asCALL_THISCALL);
    // int Light::GetNumShadowSplits() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "int GetNumShadowSplits() const", asMETHODPR(Light, GetNumShadowSplits, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "int get_numShadowSplits() const", asMETHODPR(Light, GetNumShadowSplits, () const, int), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Light, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Light, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Light, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // bool Light::GetPerVertex() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "bool GetPerVertex() const", asMETHODPR(Light, GetPerVertex, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_perVertex() const", asMETHODPR(Light, GetPerVertex, () const, bool), asCALL_THISCALL);
    // float Light::GetRadius() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetRadius() const", asMETHODPR(Light, GetRadius, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_radius() const", asMETHODPR(Light, GetRadius, () const, float), asCALL_THISCALL);
    // Texture* Light::GetRampTexture() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "Texture@+ GetRampTexture() const", asMETHODPR(Light, GetRampTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Texture@+ get_rampTexture() const", asMETHODPR(Light, GetRampTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef Light::GetRampTextureAttr() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "ResourceRef GetRampTextureAttr() const", asMETHODPR(Light, GetRampTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // float Light::GetRange() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetRange() const", asMETHODPR(Light, GetRange, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_range() const", asMETHODPR(Light, GetRange, () const, float), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "Scene@+ GetScene() const", asMETHODPR(Light, GetScene, () const, Scene*), asCALL_THISCALL);
    // const BiasParameters& Light::GetShadowBias() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "const BiasParameters& GetShadowBias() const", asMETHODPR(Light, GetShadowBias, () const, const BiasParameters&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const BiasParameters& get_shadowBias() const", asMETHODPR(Light, GetShadowBias, () const, const BiasParameters&), asCALL_THISCALL);
    // const CascadeParameters& Light::GetShadowCascade() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "const CascadeParameters& GetShadowCascade() const", asMETHODPR(Light, GetShadowCascade, () const, const CascadeParameters&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const CascadeParameters& get_shadowCascade() const", asMETHODPR(Light, GetShadowCascade, () const, const CascadeParameters&), asCALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetShadowDistance() const", asMETHODPR(Light, GetShadowDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowDistance() const", asMETHODPR(Light, GetShadowDistance, () const, float), asCALL_THISCALL);
    // float Light::GetShadowFadeDistance() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetShadowFadeDistance() const", asMETHODPR(Light, GetShadowFadeDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowFadeDistance() const", asMETHODPR(Light, GetShadowFadeDistance, () const, float), asCALL_THISCALL);
    // const FocusParameters& Light::GetShadowFocus() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "const FocusParameters& GetShadowFocus() const", asMETHODPR(Light, GetShadowFocus, () const, const FocusParameters&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const FocusParameters& get_shadowFocus() const", asMETHODPR(Light, GetShadowFocus, () const, const FocusParameters&), asCALL_THISCALL);
    // float Light::GetShadowIntensity() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetShadowIntensity() const", asMETHODPR(Light, GetShadowIntensity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowIntensity() const", asMETHODPR(Light, GetShadowIntensity, () const, float), asCALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint GetShadowMask() const", asMETHODPR(Light, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_shadowMask() const", asMETHODPR(Light, GetShadowMask, () const, unsigned), asCALL_THISCALL);
    // float Light::GetShadowMaxExtrusion() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetShadowMaxExtrusion() const", asMETHODPR(Light, GetShadowMaxExtrusion, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowMaxExtrusion() const", asMETHODPR(Light, GetShadowMaxExtrusion, () const, float), asCALL_THISCALL);
    // float Light::GetShadowNearFarRatio() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetShadowNearFarRatio() const", asMETHODPR(Light, GetShadowNearFarRatio, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowNearFarRatio() const", asMETHODPR(Light, GetShadowNearFarRatio, () const, float), asCALL_THISCALL);
    // float Light::GetShadowResolution() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetShadowResolution() const", asMETHODPR(Light, GetShadowResolution, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowResolution() const", asMETHODPR(Light, GetShadowResolution, () const, float), asCALL_THISCALL);
    // Texture* Light::GetShapeTexture() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "Texture@+ GetShapeTexture() const", asMETHODPR(Light, GetShapeTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Texture@+ get_shapeTexture() const", asMETHODPR(Light, GetShapeTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef Light::GetShapeTextureAttr() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "ResourceRef GetShapeTextureAttr() const", asMETHODPR(Light, GetShapeTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetSortValue() const", asMETHODPR(Light, GetSortValue, () const, float), asCALL_THISCALL);
    // float Light::GetSpecularIntensity() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetSpecularIntensity() const", asMETHODPR(Light, GetSpecularIntensity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_specularIntensity() const", asMETHODPR(Light, GetSpecularIntensity, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Light, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // float Light::GetTemperature() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetTemperature() const", asMETHODPR(Light, GetTemperature, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_temperature() const", asMETHODPR(Light, GetTemperature, () const, float), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "StringHash GetType() const", asMETHODPR(Light, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "StringHash get_type() const", asMETHODPR(Light, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "const String& GetTypeName() const", asMETHODPR(Light, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const String& get_typeName() const", asMETHODPR(Light, GetTypeName, () const, const String&), asCALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "UpdateGeometryType GetUpdateGeometryType()", asMETHODPR(Light, GetUpdateGeometryType, (), UpdateGeometryType), asCALL_THISCALL);
    // bool Light::GetUsePhysicalValues() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "bool GetUsePhysicalValues() const", asMETHODPR(Light, GetUsePhysicalValues, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_usePhysicalValues() const", asMETHODPR(Light, GetUsePhysicalValues, () const, bool), asCALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "Array<Light@>@ GetVertexLights() const", asFUNCTION(Light_GetVertexLights_void), asCALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint GetViewMask() const", asMETHODPR(Light, GetViewMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_viewMask() const", asMETHODPR(Light, GetViewMask, () const, unsigned), asCALL_THISCALL);
    // Frustum Light::GetViewSpaceFrustum(const Matrix3x4& view) const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "Frustum GetViewSpaceFrustum(const Matrix3x4&in) const", asMETHODPR(Light, GetViewSpaceFrustum, (const Matrix3x4&) const, Frustum), asCALL_THISCALL);
    // const Matrix3x4& Light::GetVolumeTransform(Camera* camera) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "const Matrix3x4& GetVolumeTransform(Camera@+)", asMETHODPR(Light, GetVolumeTransform, (Camera*), const Matrix3x4&), asCALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "const BoundingBox& GetWorldBoundingBox()", asMETHODPR(Light, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const BoundingBox& get_worldBoundingBox()", asMETHODPR(Light, GetWorldBoundingBox, (), const BoundingBox&), asCALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "Zone@+ GetZone() const", asMETHODPR(Light, GetZone, () const, Zone*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Zone@+ get_zone() const", asMETHODPR(Light, GetZone, () const, Zone*), asCALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint GetZoneMask() const", asMETHODPR(Light, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_zoneMask() const", asMETHODPR(Light, GetZoneMask, () const, unsigned), asCALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool HasBasePass(uint) const", asMETHODPR(Light, HasBasePass, (unsigned) const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "bool HasEventHandlers() const", asMETHODPR(Light, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Light, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Light, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "bool IsEnabled() const", asMETHODPR(Light, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_enabled() const", asMETHODPR(Light, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "bool IsEnabledEffective() const", asMETHODPR(Light, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_enabledEffective() const", asMETHODPR(Light, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "bool IsInstanceOf(StringHash) const", asMETHODPR(Light, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool IsInView() const", asMETHODPR(Light, IsInView, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_inView() const", asMETHODPR(Light, IsInView, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool IsInView(Camera@+) const", asMETHODPR(Light, IsInView, (Camera*) const, bool), asCALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool IsInView(const FrameInfo&in, bool = false) const", asMETHODPR(Light, IsInView, (const FrameInfo&, bool) const, bool), asCALL_THISCALL);
    // bool Light::IsNegative() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "bool IsNegative() const", asMETHODPR(Light, IsNegative, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_negative() const", asMETHODPR(Light, IsNegative, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool IsOccludee() const", asMETHODPR(Light, IsOccludee, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_occludee() const", asMETHODPR(Light, IsOccludee, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool IsOccluder() const", asMETHODPR(Light, IsOccluder, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_occluder() const", asMETHODPR(Light, IsOccluder, () const, bool), asCALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "bool IsReplicated() const", asMETHODPR(Light, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_replicated() const", asMETHODPR(Light, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool IsTemporary() const", asMETHODPR(Light, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_temporary() const", asMETHODPR(Light, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool IsZoneDirty() const", asMETHODPR(Light, IsZoneDirty, () const, bool), asCALL_THISCALL);
    // explicit Light::Light(Context* context) | File: ../Graphics/Light.h
    engine->RegisterObjectBehaviour("Light", asBEHAVE_FACTORY, "Light@+ f()", asFUNCTION(Light_Light_Context), asCALL_CDECL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void LimitLights()", asMETHODPR(Light, LimitLights, (), void), asCALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void LimitVertexLights(bool)", asMETHODPR(Light, LimitVertexLights, (bool), void), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool Load(Deserializer&)", asMETHODPR(Light, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Light, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "bool LoadXML(const XMLElement&in)", asMETHODPR(Light, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void MarkForUpdate()", asMETHODPR(Light, MarkForUpdate, (), void), asCALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void MarkInView(const FrameInfo&in)", asMETHODPR(Light, MarkInView, (const FrameInfo&), void), asCALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void MarkInView(uint)", asMETHODPR(Light, MarkInView, (unsigned), void), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "void MarkNetworkUpdate()", asMETHODPR(Light, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Light, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Light, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Light, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void OnSetEnabled()", asMETHODPR(Light, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "void PrepareNetworkUpdate()", asMETHODPR(Light, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // void Light::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/Light.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Light, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Light, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Light", "int Refs() const", asMETHODPR(Light, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "int get_refs() const", asMETHODPR(Light, Refs, () const, int), asCALL_THISCALL);
    // static void Light::RegisterObject(Context* context) | File: ../Graphics/Light.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Light", asBEHAVE_RELEASE, "void f()", asMETHODPR(Light, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "void Remove()", asMETHODPR(Light, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Light, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void RemoveInstanceDefault()", asMETHODPR(Light, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void RemoveObjectAnimation()", asMETHODPR(Light, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void ResetToDefault()", asMETHODPR(Light, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "bool Save(Serializer&) const", asMETHODPR(Light, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool SaveDefaultAttributes() const", asMETHODPR(Light, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "bool SaveJSON(JSONValue&) const", asMETHODPR(Light, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "bool SaveXML(XMLElement&) const", asMETHODPR(Light, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void SendEvent(StringHash)", asMETHODPR(Light, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Light, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetAnimationEnabled(bool)", asMETHODPR(Light, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_animationEnabled(bool)", asMETHODPR(Light, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetAnimationTime(float)", asMETHODPR(Light, SetAnimationTime, (float), void), asCALL_THISCALL);
    // void Light::SetAspectRatio(float aspectRatio) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetAspectRatio(float)", asMETHODPR(Light, SetAspectRatio, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_aspectRatio(float)", asMETHODPR(Light, SetAspectRatio, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Light, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Light, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Light, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Light, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Light, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Light, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Light, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetBasePass(uint)", asMETHODPR(Light, SetBasePass, (unsigned), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void SetBlockEvents(bool)", asMETHODPR(Light, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Light::SetBrightness(float brightness) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetBrightness(float)", asMETHODPR(Light, SetBrightness, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_brightness(float)", asMETHODPR(Light, SetBrightness, (float), void), asCALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetCastShadows(bool)", asMETHODPR(Light, SetCastShadows, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_castShadows(bool)", asMETHODPR(Light, SetCastShadows, (bool), void), asCALL_THISCALL);
    // void Light::SetColor(const Color& color) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetColor(const Color&in)", asMETHODPR(Light, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_color(const Color&in)", asMETHODPR(Light, SetColor, (const Color&), void), asCALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetDrawDistance(float)", asMETHODPR(Light, SetDrawDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_drawDistance(float)", asMETHODPR(Light, SetDrawDistance, (float), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "void SetEnabled(bool)", asMETHODPR(Light, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_enabled(bool)", asMETHODPR(Light, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Light::SetFadeDistance(float distance) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetFadeDistance(float)", asMETHODPR(Light, SetFadeDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_fadeDistance(float)", asMETHODPR(Light, SetFadeDistance, (float), void), asCALL_THISCALL);
    // void Light::SetFov(float fov) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetFov(float)", asMETHODPR(Light, SetFov, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_fov(float)", asMETHODPR(Light, SetFov, (float), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Light, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Light, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void SetInstanceDefault(bool)", asMETHODPR(Light, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Light::SetIntensitySortValue(float distance) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetIntensitySortValue(float)", asMETHODPR(Light, SetIntensitySortValue, (float), void), asCALL_THISCALL);
    // void Light::SetIntensitySortValue(const BoundingBox& box) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetIntensitySortValue(const BoundingBox&in)", asMETHODPR(Light, SetIntensitySortValue, (const BoundingBox&), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Light, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Light::SetLength(float length) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetLength(float)", asMETHODPR(Light, SetLength, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_length(float)", asMETHODPR(Light, SetLength, (float), void), asCALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetLightMask(uint)", asMETHODPR(Light, SetLightMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_lightMask(uint)", asMETHODPR(Light, SetLightMask, (unsigned), void), asCALL_THISCALL);
    // void Light::SetLightQueue(LightBatchQueue* queue) | File: ../Graphics/Light.h
    // Error: type "LightBatchQueue*" can not automatically bind
    // void Light::SetLightType(LightType type) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetLightType(LightType)", asMETHODPR(Light, SetLightType, (LightType), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_lightType(LightType)", asMETHODPR(Light, SetLightType, (LightType), void), asCALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetLodBias(float)", asMETHODPR(Light, SetLodBias, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_lodBias(float)", asMETHODPR(Light, SetLodBias, (float), void), asCALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetMaxLights(uint)", asMETHODPR(Light, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_maxLights(uint)", asMETHODPR(Light, SetMaxLights, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetMinMaxZ(float, float)", asMETHODPR(Light, SetMinMaxZ, (float, float), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Light, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Light, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Light, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetOccludee(bool)", asMETHODPR(Light, SetOccludee, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_occludee(bool)", asMETHODPR(Light, SetOccludee, (bool), void), asCALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetOccluder(bool)", asMETHODPR(Light, SetOccluder, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_occluder(bool)", asMETHODPR(Light, SetOccluder, (bool), void), asCALL_THISCALL);
    // void Light::SetPerVertex(bool enable) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetPerVertex(bool)", asMETHODPR(Light, SetPerVertex, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_perVertex(bool)", asMETHODPR(Light, SetPerVertex, (bool), void), asCALL_THISCALL);
    // void Light::SetRadius(float radius) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetRadius(float)", asMETHODPR(Light, SetRadius, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_radius(float)", asMETHODPR(Light, SetRadius, (float), void), asCALL_THISCALL);
    // void Light::SetRampTexture(Texture* texture) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetRampTexture(Texture@+)", asMETHODPR(Light, SetRampTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_rampTexture(Texture@+)", asMETHODPR(Light, SetRampTexture, (Texture*), void), asCALL_THISCALL);
    // void Light::SetRampTextureAttr(const ResourceRef& value) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetRampTextureAttr(const ResourceRef&in)", asMETHODPR(Light, SetRampTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Light::SetRange(float range) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetRange(float)", asMETHODPR(Light, SetRange, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_range(float)", asMETHODPR(Light, SetRange, (float), void), asCALL_THISCALL);
    // void Light::SetShadowBias(const BiasParameters& parameters) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowBias(const BiasParameters&in)", asMETHODPR(Light, SetShadowBias, (const BiasParameters&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowBias(const BiasParameters&in)", asMETHODPR(Light, SetShadowBias, (const BiasParameters&), void), asCALL_THISCALL);
    // void Light::SetShadowCascade(const CascadeParameters& parameters) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowCascade(const CascadeParameters&in)", asMETHODPR(Light, SetShadowCascade, (const CascadeParameters&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowCascade(const CascadeParameters&in)", asMETHODPR(Light, SetShadowCascade, (const CascadeParameters&), void), asCALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetShadowDistance(float)", asMETHODPR(Light, SetShadowDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowDistance(float)", asMETHODPR(Light, SetShadowDistance, (float), void), asCALL_THISCALL);
    // void Light::SetShadowFadeDistance(float distance) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowFadeDistance(float)", asMETHODPR(Light, SetShadowFadeDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowFadeDistance(float)", asMETHODPR(Light, SetShadowFadeDistance, (float), void), asCALL_THISCALL);
    // void Light::SetShadowFocus(const FocusParameters& parameters) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowFocus(const FocusParameters&in)", asMETHODPR(Light, SetShadowFocus, (const FocusParameters&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowFocus(const FocusParameters&in)", asMETHODPR(Light, SetShadowFocus, (const FocusParameters&), void), asCALL_THISCALL);
    // void Light::SetShadowIntensity(float intensity) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowIntensity(float)", asMETHODPR(Light, SetShadowIntensity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowIntensity(float)", asMETHODPR(Light, SetShadowIntensity, (float), void), asCALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetShadowMask(uint)", asMETHODPR(Light, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowMask(uint)", asMETHODPR(Light, SetShadowMask, (unsigned), void), asCALL_THISCALL);
    // void Light::SetShadowMaxExtrusion(float extrusion) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowMaxExtrusion(float)", asMETHODPR(Light, SetShadowMaxExtrusion, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowMaxExtrusion(float)", asMETHODPR(Light, SetShadowMaxExtrusion, (float), void), asCALL_THISCALL);
    // void Light::SetShadowNearFarRatio(float nearFarRatio) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowNearFarRatio(float)", asMETHODPR(Light, SetShadowNearFarRatio, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowNearFarRatio(float)", asMETHODPR(Light, SetShadowNearFarRatio, (float), void), asCALL_THISCALL);
    // void Light::SetShadowResolution(float resolution) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowResolution(float)", asMETHODPR(Light, SetShadowResolution, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowResolution(float)", asMETHODPR(Light, SetShadowResolution, (float), void), asCALL_THISCALL);
    // void Light::SetShapeTexture(Texture* texture) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShapeTexture(Texture@+)", asMETHODPR(Light, SetShapeTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shapeTexture(Texture@+)", asMETHODPR(Light, SetShapeTexture, (Texture*), void), asCALL_THISCALL);
    // void Light::SetShapeTextureAttr(const ResourceRef& value) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShapeTextureAttr(const ResourceRef&in)", asMETHODPR(Light, SetShapeTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetSortValue(float)", asMETHODPR(Light, SetSortValue, (float), void), asCALL_THISCALL);
    // void Light::SetSpecularIntensity(float intensity) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetSpecularIntensity(float)", asMETHODPR(Light, SetSpecularIntensity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_specularIntensity(float)", asMETHODPR(Light, SetSpecularIntensity, (float), void), asCALL_THISCALL);
    // void Light::SetTemperature(float temperature) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetTemperature(float)", asMETHODPR(Light, SetTemperature, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_temperature(float)", asMETHODPR(Light, SetTemperature, (float), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void SetTemporary(bool)", asMETHODPR(Light, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_temporary(bool)", asMETHODPR(Light, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Light::SetUsePhysicalValues(bool enable) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetUsePhysicalValues(bool)", asMETHODPR(Light, SetUsePhysicalValues, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_usePhysicalValues(bool)", asMETHODPR(Light, SetUsePhysicalValues, (bool), void), asCALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetViewMask(uint)", asMETHODPR(Light, SetViewMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_viewMask(uint)", asMETHODPR(Light, SetViewMask, (unsigned), void), asCALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetZone(Zone@+, bool = false)", asMETHODPR(Light, SetZone, (Zone*, bool), void), asCALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetZoneMask(uint)", asMETHODPR(Light, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_zoneMask(uint)", asMETHODPR(Light, SetZoneMask, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void UnsubscribeFromAllEvents()", asMETHODPR(Light, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Light_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Light, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Light, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Light, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void Update(const FrameInfo&in)", asMETHODPR(Light, Update, (const FrameInfo&), void), asCALL_THISCALL);
    // void Light::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void UpdateBatches(const FrameInfo&in)", asMETHODPR(Light, UpdateBatches, (const FrameInfo&), void), asCALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void UpdateGeometry(const FrameInfo&in)", asMETHODPR(Light, UpdateGeometry, (const FrameInfo&), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Light", "int WeakRefs() const", asMETHODPR(Light, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Light", "int get_weakRefs() const", asMETHODPR(Light, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Light, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Light, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Light, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Drawable
    REGISTER_MANUAL_PART_Drawable(Light, "Light")
#endif
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(Light, "Light")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Light, "Light")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Light, "Light")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Light, "Light")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Light, "Light")
#endif
#ifdef REGISTER_MANUAL_PART_Light
    REGISTER_MANUAL_PART_Light(Light, "Light")
#endif
    RegisterSubclass<Drawable, Light>(engine, "Drawable", "Light");
    RegisterSubclass<Component, Light>(engine, "Component", "Light");
    RegisterSubclass<Animatable, Light>(engine, "Animatable", "Light");
    RegisterSubclass<Serializable, Light>(engine, "Serializable", "Light");
    RegisterSubclass<Object, Light>(engine, "Object", "Light");
    RegisterSubclass<RefCounted, Light>(engine, "RefCounted", "Light");

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void AddChild(UIElement@+)", asMETHODPR(LineEdit, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("LineEdit", asBEHAVE_ADDREF, "void f()", asMETHODPR(LineEdit, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void AddTag(const String&in)", asMETHODPR(LineEdit, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void AddTags(const String&in, int8 = ';')", asMETHODPR(LineEdit, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void AdjustScissor(IntRect&)", asMETHODPR(LineEdit, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void AllocateNetworkState()", asMETHODPR(LineEdit, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void LineEdit::ApplyAttributes() override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void ApplyAttributes()", asMETHODPR(LineEdit, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void BringToFront()", asMETHODPR(LineEdit, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(LineEdit, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void DisableLayoutUpdate()", asMETHODPR(LineEdit, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(LineEdit, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void EnableLayoutUpdate()", asMETHODPR(LineEdit, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool FilterAttributes(XMLElement&) const", asMETHODPR(LineEdit, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "uint FindChild(UIElement@+) const", asMETHODPR(LineEdit, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "bool GetAnimationEnabled() const", asMETHODPR(LineEdit, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_animationEnabled() const", asMETHODPR(LineEdit, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const String& GetAppliedStyle() const", asMETHODPR(LineEdit, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const String& get_style() const", asMETHODPR(LineEdit, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "Variant GetAttribute(uint) const", asMETHODPR(LineEdit, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "Variant get_attributes(uint) const", asMETHODPR(LineEdit, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "Variant GetAttribute(const String&in) const", asMETHODPR(LineEdit, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(LineEdit, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(LineEdit, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(LineEdit, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(LineEdit, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "Variant GetAttributeDefault(uint) const", asMETHODPR(LineEdit, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "Variant get_attributeDefaults(uint) const", asMETHODPR(LineEdit, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(LineEdit, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/BorderImage.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "BlendMode GetBlendMode() const", asMETHODPR(LineEdit, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "BlendMode get_blendMode() const", asMETHODPR(LineEdit, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "bool GetBlockEvents() const", asMETHODPR(LineEdit, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "const IntRect& GetBorder() const", asMETHODPR(LineEdit, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntRect& get_border() const", asMETHODPR(LineEdit, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool GetBringToBack() const", asMETHODPR(LineEdit, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_bringToBack() const", asMETHODPR(LineEdit, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool GetBringToFront() const", asMETHODPR(LineEdit, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_bringToFront() const", asMETHODPR(LineEdit, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "const String& GetCategory() const", asMETHODPR(LineEdit, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const String& get_category() const", asMETHODPR(LineEdit, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ GetChild(uint) const", asMETHODPR(LineEdit, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ get_children(uint) const", asMETHODPR(LineEdit, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(LineEdit, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(LineEdit, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetChildOffset() const", asMETHODPR(LineEdit, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_childOffset() const", asMETHODPR(LineEdit, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "Array<UIElement@>@ GetChildren() const", asFUNCTION(LineEdit_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(LineEdit_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(LineEdit_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntRect& GetClipBorder() const", asMETHODPR(LineEdit, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntRect& get_clipBorder() const", asMETHODPR(LineEdit, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool GetClipChildren() const", asMETHODPR(LineEdit, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_clipChildren() const", asMETHODPR(LineEdit, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Color& GetColor(Corner) const", asMETHODPR(LineEdit, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const Color& get_colors(Corner) const", asMETHODPR(LineEdit, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Color& GetColorAttr() const", asMETHODPR(LineEdit, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "IntRect GetCombinedScreenRect()", asMETHODPR(LineEdit, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "IntRect get_combinedScreenRect()", asMETHODPR(LineEdit, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // BorderImage* LineEdit::GetCursor() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "BorderImage@+ GetCursor() const", asMETHODPR(LineEdit, GetCursor, () const, BorderImage*), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "BorderImage@+ get_cursor() const", asMETHODPR(LineEdit, GetCursor, () const, BorderImage*), asCALL_THISCALL);
    // float LineEdit::GetCursorBlinkRate() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "float GetCursorBlinkRate() const", asMETHODPR(LineEdit, GetCursorBlinkRate, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "float get_cursorBlinkRate() const", asMETHODPR(LineEdit, GetCursorBlinkRate, () const, float), asCALL_THISCALL);
    // unsigned LineEdit::GetCursorPosition() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "uint GetCursorPosition() const", asMETHODPR(LineEdit, GetCursorPosition, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_cursorPosition() const", asMETHODPR(LineEdit, GetCursorPosition, () const, unsigned), asCALL_THISCALL);
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(LineEdit, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Color& GetDerivedColor() const", asMETHODPR(LineEdit, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "float GetDerivedOpacity() const", asMETHODPR(LineEdit, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "float get_derivedOpacity() const", asMETHODPR(LineEdit, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetDisabledOffset() const", asMETHODPR(LineEdit, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_disabledOffset() const", asMETHODPR(LineEdit, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(LineEdit, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(LineEdit, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "uint GetDragButtonCount() const", asMETHODPR(LineEdit, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_dragButtonCount() const", asMETHODPR(LineEdit, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(LineEdit, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(LineEdit, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // unsigned LineEdit::GetEchoCharacter() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "uint GetEchoCharacter() const", asMETHODPR(LineEdit, GetEchoCharacter, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_echoCharacter() const", asMETHODPR(LineEdit, GetEchoCharacter, () const, unsigned), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(LineEdit, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ GetElementEventSender() const", asMETHODPR(LineEdit, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool GetEnableAnchor() const", asMETHODPR(LineEdit, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_enableAnchor() const", asMETHODPR(LineEdit, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "VariantMap& GetEventDataMap() const", asMETHODPR(LineEdit, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "Object@+ GetEventSender() const", asMETHODPR(LineEdit, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "FocusMode GetFocusMode() const", asMETHODPR(LineEdit, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "FocusMode get_focusMode() const", asMETHODPR(LineEdit, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(LineEdit, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const Variant& get_globalVar(StringHash) const", asMETHODPR(LineEdit, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "const VariantMap& GetGlobalVars() const", asMETHODPR(LineEdit, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const VariantMap& get_globalVars() const", asMETHODPR(LineEdit, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetHeight() const", asMETHODPR(LineEdit, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_height() const", asMETHODPR(LineEdit, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(LineEdit, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(LineEdit, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetHoverOffset() const", asMETHODPR(LineEdit, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_hoverOffset() const", asMETHODPR(LineEdit, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "const IntRect& GetImageBorder() const", asMETHODPR(LineEdit, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntRect& get_imageBorder() const", asMETHODPR(LineEdit, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "const IntRect& GetImageRect() const", asMETHODPR(LineEdit, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntRect& get_imageRect() const", asMETHODPR(LineEdit, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetIndent() const", asMETHODPR(LineEdit, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_indent() const", asMETHODPR(LineEdit, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetIndentSpacing() const", asMETHODPR(LineEdit, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_indentSpacing() const", asMETHODPR(LineEdit, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetIndentWidth() const", asMETHODPR(LineEdit, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_indentWidth() const", asMETHODPR(LineEdit, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(LineEdit, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntRect& GetLayoutBorder() const", asMETHODPR(LineEdit, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntRect& get_layoutBorder() const", asMETHODPR(LineEdit, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetLayoutElementMaxSize() const", asMETHODPR(LineEdit, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(LineEdit, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const Vector2& get_layoutFlexScale() const", asMETHODPR(LineEdit, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "LayoutMode GetLayoutMode() const", asMETHODPR(LineEdit, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "LayoutMode get_layoutMode() const", asMETHODPR(LineEdit, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetLayoutSpacing() const", asMETHODPR(LineEdit, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_layoutSpacing() const", asMETHODPR(LineEdit, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "Material@+ GetMaterial() const", asMETHODPR(LineEdit, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "Material@+ get_material() const", asMETHODPR(LineEdit, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "ResourceRef GetMaterialAttr() const", asMETHODPR(LineEdit, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Vector2& GetMaxAnchor() const", asMETHODPR(LineEdit, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const Vector2& get_maxAnchor() const", asMETHODPR(LineEdit, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetMaxHeight() const", asMETHODPR(LineEdit, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_maxHeight() const", asMETHODPR(LineEdit, GetMaxHeight, () const, int), asCALL_THISCALL);
    // unsigned LineEdit::GetMaxLength() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "uint GetMaxLength() const", asMETHODPR(LineEdit, GetMaxLength, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_maxLength() const", asMETHODPR(LineEdit, GetMaxLength, () const, unsigned), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetMaxOffset() const", asMETHODPR(LineEdit, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_maxOffset() const", asMETHODPR(LineEdit, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetMaxSize() const", asMETHODPR(LineEdit, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_maxSize() const", asMETHODPR(LineEdit, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetMaxWidth() const", asMETHODPR(LineEdit, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_maxWidth() const", asMETHODPR(LineEdit, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Vector2& GetMinAnchor() const", asMETHODPR(LineEdit, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const Vector2& get_minAnchor() const", asMETHODPR(LineEdit, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetMinHeight() const", asMETHODPR(LineEdit, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_minHeight() const", asMETHODPR(LineEdit, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetMinOffset() const", asMETHODPR(LineEdit, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_minOffset() const", asMETHODPR(LineEdit, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetMinSize() const", asMETHODPR(LineEdit, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_minSize() const", asMETHODPR(LineEdit, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetMinWidth() const", asMETHODPR(LineEdit, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_minWidth() const", asMETHODPR(LineEdit, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const String& GetName() const", asMETHODPR(LineEdit, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const String& get_name() const", asMETHODPR(LineEdit, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "uint GetNumAttributes() const", asMETHODPR(LineEdit, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_numAttributes() const", asMETHODPR(LineEdit, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "uint GetNumChildren(bool = false) const", asMETHODPR(LineEdit, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_numChildren(bool = false) const", asMETHODPR(LineEdit, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "uint GetNumNetworkAttributes() const", asMETHODPR(LineEdit, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(LineEdit, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(LineEdit, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(LineEdit, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "float GetOpacity() const", asMETHODPR(LineEdit, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "float get_opacity() const", asMETHODPR(LineEdit, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ GetParent() const", asMETHODPR(LineEdit, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ get_parent() const", asMETHODPR(LineEdit, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Vector2& GetPivot() const", asMETHODPR(LineEdit, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const Vector2& get_pivot() const", asMETHODPR(LineEdit, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetPosition() const", asMETHODPR(LineEdit, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_position() const", asMETHODPR(LineEdit, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetPriority() const", asMETHODPR(LineEdit, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_priority() const", asMETHODPR(LineEdit, GetPriority, () const, int), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ GetRoot() const", asMETHODPR(LineEdit, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ get_root() const", asMETHODPR(LineEdit, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetScreenPosition() const", asMETHODPR(LineEdit, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_screenPosition() const", asMETHODPR(LineEdit, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetSize() const", asMETHODPR(LineEdit, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_size() const", asMETHODPR(LineEdit, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool GetSortChildren() const", asMETHODPR(LineEdit, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_sortChildren() const", asMETHODPR(LineEdit, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(LineEdit, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "Array<String>@ GetTags() const", asFUNCTION(LineEdit_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("LineEdit", "Array<String>@ get_tags() const", asFUNCTION(LineEdit_GetTags_void), asCALL_CDECL_OBJFIRST);
    // const String& LineEdit::GetText() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "const String& GetText() const", asMETHODPR(LineEdit, GetText, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const String& get_text() const", asMETHODPR(LineEdit, GetText, () const, const String&), asCALL_THISCALL);
    // Text* LineEdit::GetTextElement() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "Text@+ GetTextElement() const", asMETHODPR(LineEdit, GetTextElement, () const, Text*), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "Text@+ get_textElement() const", asMETHODPR(LineEdit, GetTextElement, () const, Text*), asCALL_THISCALL);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "Texture@+ GetTexture() const", asMETHODPR(LineEdit, GetTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "Texture@+ get_texture() const", asMETHODPR(LineEdit, GetTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "ResourceRef GetTextureAttr() const", asMETHODPR(LineEdit, GetTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "TraversalMode GetTraversalMode() const", asMETHODPR(LineEdit, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "TraversalMode get_traversalMode() const", asMETHODPR(LineEdit, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "StringHash GetType() const", asMETHODPR(LineEdit, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "StringHash get_type() const", asMETHODPR(LineEdit, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "const String& GetTypeName() const", asMETHODPR(LineEdit, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const String& get_typeName() const", asMETHODPR(LineEdit, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool GetUseDerivedOpacity() const", asMETHODPR(LineEdit, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_useDerivedOpacity() const", asMETHODPR(LineEdit, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(LineEdit, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const VariantMap& GetVars() const", asMETHODPR(LineEdit, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(LineEdit, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(LineEdit, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetWidth() const", asMETHODPR(LineEdit, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_width() const", asMETHODPR(LineEdit, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool HasColorGradient() const", asMETHODPR(LineEdit, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_colorGradient() const", asMETHODPR(LineEdit, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "bool HasEventHandlers() const", asMETHODPR(LineEdit, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool HasFocus() const", asMETHODPR(LineEdit, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_focus() const", asMETHODPR(LineEdit, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(LineEdit, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(LineEdit, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool HasTag(const String&in) const", asMETHODPR(LineEdit, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void InsertChild(uint, UIElement@+)", asMETHODPR(LineEdit, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsChildOf(UIElement@+) const", asMETHODPR(LineEdit, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool LineEdit::IsCursorMovable() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "bool IsCursorMovable() const", asMETHODPR(LineEdit, IsCursorMovable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_cursorMovable() const", asMETHODPR(LineEdit, IsCursorMovable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsEditable() const", asMETHODPR(LineEdit, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_editable() const", asMETHODPR(LineEdit, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsElementEventSender() const", asMETHODPR(LineEdit, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_elementEventSender() const", asMETHODPR(LineEdit, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsEnabled() const", asMETHODPR(LineEdit, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_enabled() const", asMETHODPR(LineEdit, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsEnabledSelf() const", asMETHODPR(LineEdit, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_enabledSelf() const", asMETHODPR(LineEdit, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsFixedHeight() const", asMETHODPR(LineEdit, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_fixedHeight() const", asMETHODPR(LineEdit, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsFixedSize() const", asMETHODPR(LineEdit, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_fixedSize() const", asMETHODPR(LineEdit, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsFixedWidth() const", asMETHODPR(LineEdit, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_fixedWidth() const", asMETHODPR(LineEdit, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsHovering() const", asMETHODPR(LineEdit, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_hovering() const", asMETHODPR(LineEdit, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsInside(IntVector2, bool)", asMETHODPR(LineEdit, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(LineEdit, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "bool IsInstanceOf(StringHash) const", asMETHODPR(LineEdit, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsInternal() const", asMETHODPR(LineEdit, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_internal() const", asMETHODPR(LineEdit, IsInternal, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsSelected() const", asMETHODPR(LineEdit, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_selected() const", asMETHODPR(LineEdit, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool IsTemporary() const", asMETHODPR(LineEdit, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_temporary() const", asMETHODPR(LineEdit, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool LineEdit::IsTextCopyable() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "bool IsTextCopyable() const", asMETHODPR(LineEdit, IsTextCopyable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_textCopyable() const", asMETHODPR(LineEdit, IsTextCopyable, () const, bool), asCALL_THISCALL);
    // bool LineEdit::IsTextSelectable() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "bool IsTextSelectable() const", asMETHODPR(LineEdit, IsTextSelectable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_textSelectable() const", asMETHODPR(LineEdit, IsTextSelectable, () const, bool), asCALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "bool IsTiled() const", asMETHODPR(LineEdit, IsTiled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_tiled() const", asMETHODPR(LineEdit, IsTiled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsVisible() const", asMETHODPR(LineEdit, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_visible() const", asMETHODPR(LineEdit, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsVisibleEffective() const", asMETHODPR(LineEdit, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_visibleEffective() const", asMETHODPR(LineEdit, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsWheelHandler() const", asMETHODPR(LineEdit, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(LineEdit, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // explicit LineEdit::LineEdit(Context* context) | File: ../UI/LineEdit.h
    engine->RegisterObjectBehaviour("LineEdit", asBEHAVE_FACTORY, "LineEdit@+ f()", asFUNCTION(LineEdit_LineEdit_Context), asCALL_CDECL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool Load(Deserializer&)", asMETHODPR(LineEdit, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(LineEdit, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "bool LoadJSON(const JSONValue&in)", asMETHODPR(LineEdit, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool LoadXML(const XMLElement&in)", asMETHODPR(LineEdit, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(LineEdit, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool LoadXML(Deserializer&)", asMETHODPR(LineEdit, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void MarkNetworkUpdate()", asMETHODPR(LineEdit, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // void LineEdit::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(LineEdit, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(LineEdit, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // void LineEdit::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(LineEdit, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // void LineEdit::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(LineEdit, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(LineEdit, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // bool LineEdit::OnDragDropFinish(UIElement* source) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(LineEdit, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // bool LineEdit::OnDragDropTest(UIElement* source) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "bool OnDragDropTest(UIElement@+)", asMETHODPR(LineEdit, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(LineEdit, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // void LineEdit::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(LineEdit, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(LineEdit, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(LineEdit, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(LineEdit, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnIndentSet()", asMETHODPR(LineEdit, OnIndentSet, (), void), asCALL_THISCALL);
    // void LineEdit::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(LineEdit, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnPositionSet(const IntVector2&in)", asMETHODPR(LineEdit, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(LineEdit, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(LineEdit, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnSetEditable()", asMETHODPR(LineEdit, OnSetEditable, (), void), asCALL_THISCALL);
    // void LineEdit::OnTextInput(const String& text) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void OnTextInput(const String&in)", asMETHODPR(LineEdit, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(LineEdit, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(LineEdit, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(LineEdit, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("LineEdit", "int Refs() const", asMETHODPR(LineEdit, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_refs() const", asMETHODPR(LineEdit, Refs, () const, int), asCALL_THISCALL);
    // static void LineEdit::RegisterObject(Context* context) | File: ../UI/LineEdit.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("LineEdit", asBEHAVE_RELEASE, "void f()", asMETHODPR(LineEdit, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void Remove()", asMETHODPR(LineEdit, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveAllChildren()", asMETHODPR(LineEdit, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveAllTags()", asMETHODPR(LineEdit, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(LineEdit, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(LineEdit, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveChildAtIndex(uint)", asMETHODPR(LineEdit, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveInstanceDefault()", asMETHODPR(LineEdit, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveObjectAnimation()", asMETHODPR(LineEdit, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool RemoveTag(const String&in)", asMETHODPR(LineEdit, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void ResetDeepEnabled()", asMETHODPR(LineEdit, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void ResetToDefault()", asMETHODPR(LineEdit, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool Save(Serializer&) const", asMETHODPR(LineEdit, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool SaveDefaultAttributes() const", asMETHODPR(LineEdit, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "bool SaveJSON(JSONValue&) const", asMETHODPR(LineEdit, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool SaveXML(XMLElement&) const", asMETHODPR(LineEdit, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(LineEdit, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(LineEdit, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void SendEvent(StringHash)", asMETHODPR(LineEdit, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(LineEdit, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(LineEdit, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetAnimationEnabled(bool)", asMETHODPR(LineEdit, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_animationEnabled(bool)", asMETHODPR(LineEdit, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetAnimationTime(float)", asMETHODPR(LineEdit, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(LineEdit, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool set_attributes(uint, const Variant&in)", asMETHODPR(LineEdit, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(LineEdit, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(LineEdit, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(LineEdit, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(LineEdit, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(LineEdit, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetBlendMode(BlendMode)", asMETHODPR(LineEdit, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_blendMode(BlendMode)", asMETHODPR(LineEdit, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void SetBlockEvents(bool)", asMETHODPR(LineEdit, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetBorder(const IntRect&in)", asMETHODPR(LineEdit, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_border(const IntRect&in)", asMETHODPR(LineEdit, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetBringToBack(bool)", asMETHODPR(LineEdit, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_bringToBack(bool)", asMETHODPR(LineEdit, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetBringToFront(bool)", asMETHODPR(LineEdit, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_bringToFront(bool)", asMETHODPR(LineEdit, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetChildOffset(const IntVector2&in)", asMETHODPR(LineEdit, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetClipBorder(const IntRect&in)", asMETHODPR(LineEdit, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_clipBorder(const IntRect&in)", asMETHODPR(LineEdit, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetClipChildren(bool)", asMETHODPR(LineEdit, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_clipChildren(bool)", asMETHODPR(LineEdit, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetColor(const Color&in)", asMETHODPR(LineEdit, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_color(const Color&in)", asMETHODPR(LineEdit, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetColor(Corner, const Color&in)", asMETHODPR(LineEdit, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_colors(Corner, const Color&in)", asMETHODPR(LineEdit, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void LineEdit::SetCursorBlinkRate(float rate) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetCursorBlinkRate(float)", asMETHODPR(LineEdit, SetCursorBlinkRate, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_cursorBlinkRate(float)", asMETHODPR(LineEdit, SetCursorBlinkRate, (float), void), asCALL_THISCALL);
    // void LineEdit::SetCursorMovable(bool enable) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetCursorMovable(bool)", asMETHODPR(LineEdit, SetCursorMovable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_cursorMovable(bool)", asMETHODPR(LineEdit, SetCursorMovable, (bool), void), asCALL_THISCALL);
    // void LineEdit::SetCursorPosition(unsigned position) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetCursorPosition(uint)", asMETHODPR(LineEdit, SetCursorPosition, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_cursorPosition(uint)", asMETHODPR(LineEdit, SetCursorPosition, (unsigned), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetDeepEnabled(bool)", asMETHODPR(LineEdit, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(LineEdit, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_defaultStyle(XMLFile@+)", asMETHODPR(LineEdit, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetDisabledOffset(const IntVector2&in)", asMETHODPR(LineEdit, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_disabledOffset(const IntVector2&in)", asMETHODPR(LineEdit, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetDisabledOffset(int, int)", asMETHODPR(LineEdit, SetDisabledOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(LineEdit, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(LineEdit, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void LineEdit::SetEchoCharacter(unsigned c) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetEchoCharacter(uint)", asMETHODPR(LineEdit, SetEchoCharacter, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_echoCharacter(uint)", asMETHODPR(LineEdit, SetEchoCharacter, (unsigned), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetEditable(bool)", asMETHODPR(LineEdit, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_editable(bool)", asMETHODPR(LineEdit, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetElementEventSender(bool)", asMETHODPR(LineEdit, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_elementEventSender(bool)", asMETHODPR(LineEdit, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetEnableAnchor(bool)", asMETHODPR(LineEdit, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_enableAnchor(bool)", asMETHODPR(LineEdit, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetEnabled(bool)", asMETHODPR(LineEdit, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_enabled(bool)", asMETHODPR(LineEdit, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetEnabledRecursive(bool)", asMETHODPR(LineEdit, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetFixedHeight(int)", asMETHODPR(LineEdit, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetFixedSize(const IntVector2&in)", asMETHODPR(LineEdit, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetFixedSize(int, int)", asMETHODPR(LineEdit, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetFixedWidth(int)", asMETHODPR(LineEdit, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetFocus(bool)", asMETHODPR(LineEdit, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_focus(bool)", asMETHODPR(LineEdit, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetFocusMode(FocusMode)", asMETHODPR(LineEdit, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_focusMode(FocusMode)", asMETHODPR(LineEdit, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetFullImageRect()", asMETHODPR(LineEdit, SetFullImageRect, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(LineEdit, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(LineEdit, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetHeight(int)", asMETHODPR(LineEdit, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_height(int)", asMETHODPR(LineEdit, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(LineEdit, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(LineEdit, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetHovering(bool)", asMETHODPR(LineEdit, SetHovering, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetHoverOffset(const IntVector2&in)", asMETHODPR(LineEdit, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_hoverOffset(const IntVector2&in)", asMETHODPR(LineEdit, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetHoverOffset(int, int)", asMETHODPR(LineEdit, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetImageBorder(const IntRect&in)", asMETHODPR(LineEdit, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_imageBorder(const IntRect&in)", asMETHODPR(LineEdit, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetImageRect(const IntRect&in)", asMETHODPR(LineEdit, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_imageRect(const IntRect&in)", asMETHODPR(LineEdit, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetIndent(int)", asMETHODPR(LineEdit, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_indent(int)", asMETHODPR(LineEdit, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetIndentSpacing(int)", asMETHODPR(LineEdit, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_indentSpacing(int)", asMETHODPR(LineEdit, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void SetInstanceDefault(bool)", asMETHODPR(LineEdit, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(LineEdit, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetInternal(bool)", asMETHODPR(LineEdit, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_internal(bool)", asMETHODPR(LineEdit, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(LineEdit, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(LineEdit, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_layoutBorder(const IntRect&in)", asMETHODPR(LineEdit, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(LineEdit, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(LineEdit, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetLayoutMode(LayoutMode)", asMETHODPR(LineEdit, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_layoutMode(LayoutMode)", asMETHODPR(LineEdit, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetLayoutSpacing(int)", asMETHODPR(LineEdit, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_layoutSpacing(int)", asMETHODPR(LineEdit, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaterial(Material@+)", asMETHODPR(LineEdit, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_material(Material@+)", asMETHODPR(LineEdit, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(LineEdit, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(LineEdit, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_maxAnchor(const Vector2&in)", asMETHODPR(LineEdit, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxAnchor(float, float)", asMETHODPR(LineEdit, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxHeight(int)", asMETHODPR(LineEdit, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_maxHeight(int)", asMETHODPR(LineEdit, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void LineEdit::SetMaxLength(unsigned length) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxLength(uint)", asMETHODPR(LineEdit, SetMaxLength, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_maxLength(uint)", asMETHODPR(LineEdit, SetMaxLength, (unsigned), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(LineEdit, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_maxOffset(const IntVector2&in)", asMETHODPR(LineEdit, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxSize(const IntVector2&in)", asMETHODPR(LineEdit, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_maxSize(const IntVector2&in)", asMETHODPR(LineEdit, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxSize(int, int)", asMETHODPR(LineEdit, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxWidth(int)", asMETHODPR(LineEdit, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_maxWidth(int)", asMETHODPR(LineEdit, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinAnchor(const Vector2&in)", asMETHODPR(LineEdit, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_minAnchor(const Vector2&in)", asMETHODPR(LineEdit, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinAnchor(float, float)", asMETHODPR(LineEdit, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinHeight(int)", asMETHODPR(LineEdit, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_minHeight(int)", asMETHODPR(LineEdit, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinOffset(const IntVector2&in)", asMETHODPR(LineEdit, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_minOffset(const IntVector2&in)", asMETHODPR(LineEdit, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinSize(const IntVector2&in)", asMETHODPR(LineEdit, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_minSize(const IntVector2&in)", asMETHODPR(LineEdit, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinSize(int, int)", asMETHODPR(LineEdit, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinWidth(int)", asMETHODPR(LineEdit, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_minWidth(int)", asMETHODPR(LineEdit, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetName(const String&in)", asMETHODPR(LineEdit, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_name(const String&in)", asMETHODPR(LineEdit, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(LineEdit, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(LineEdit, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(LineEdit, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetOpacity(float)", asMETHODPR(LineEdit, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_opacity(float)", asMETHODPR(LineEdit, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(LineEdit, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetPivot(const Vector2&in)", asMETHODPR(LineEdit, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_pivot(const Vector2&in)", asMETHODPR(LineEdit, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetPivot(float, float)", asMETHODPR(LineEdit, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetPosition(const IntVector2&in)", asMETHODPR(LineEdit, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_position(const IntVector2&in)", asMETHODPR(LineEdit, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetPosition(int, int)", asMETHODPR(LineEdit, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetPriority(int)", asMETHODPR(LineEdit, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_priority(int)", asMETHODPR(LineEdit, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetRenderTexture(Texture2D@+)", asMETHODPR(LineEdit, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetSelected(bool)", asMETHODPR(LineEdit, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_selected(bool)", asMETHODPR(LineEdit, SetSelected, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetSize(const IntVector2&in)", asMETHODPR(LineEdit, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_size(const IntVector2&in)", asMETHODPR(LineEdit, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetSize(int, int)", asMETHODPR(LineEdit, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetSortChildren(bool)", asMETHODPR(LineEdit, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_sortChildren(bool)", asMETHODPR(LineEdit, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(LineEdit, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool SetStyle(const XMLElement&in)", asMETHODPR(LineEdit, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(LineEdit, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void SetTemporary(bool)", asMETHODPR(LineEdit, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_temporary(bool)", asMETHODPR(LineEdit, SetTemporary, (bool), void), asCALL_THISCALL);
    // void LineEdit::SetText(const String& text) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetText(const String&in)", asMETHODPR(LineEdit, SetText, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_text(const String&in)", asMETHODPR(LineEdit, SetText, (const String&), void), asCALL_THISCALL);
    // void LineEdit::SetTextCopyable(bool enable) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetTextCopyable(bool)", asMETHODPR(LineEdit, SetTextCopyable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_textCopyable(bool)", asMETHODPR(LineEdit, SetTextCopyable, (bool), void), asCALL_THISCALL);
    // void LineEdit::SetTextSelectable(bool enable) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetTextSelectable(bool)", asMETHODPR(LineEdit, SetTextSelectable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_textSelectable(bool)", asMETHODPR(LineEdit, SetTextSelectable, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetTexture(Texture@+)", asMETHODPR(LineEdit, SetTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_texture(Texture@+)", asMETHODPR(LineEdit, SetTexture, (Texture*), void), asCALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetTextureAttr(const ResourceRef&in)", asMETHODPR(LineEdit, SetTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetTiled(bool)", asMETHODPR(LineEdit, SetTiled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_tiled(bool)", asMETHODPR(LineEdit, SetTiled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetTraversalMode(TraversalMode)", asMETHODPR(LineEdit, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_traversalMode(TraversalMode)", asMETHODPR(LineEdit, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetUseDerivedOpacity(bool)", asMETHODPR(LineEdit, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_useDerivedOpacity(bool)", asMETHODPR(LineEdit, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetVar(StringHash, const Variant&in)", asMETHODPR(LineEdit, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(LineEdit, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(LineEdit, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetVisible(bool)", asMETHODPR(LineEdit, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_visible(bool)", asMETHODPR(LineEdit, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetWidth(int)", asMETHODPR(LineEdit, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_width(int)", asMETHODPR(LineEdit, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SortChildren()", asMETHODPR(LineEdit, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void UnsubscribeFromAllEvents()", asMETHODPR(LineEdit, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(LineEdit_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(LineEdit, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(LineEdit, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(LineEdit, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void LineEdit::Update(float timeStep) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void Update(float)", asMETHODPR(LineEdit, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void UpdateLayout()", asMETHODPR(LineEdit, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("LineEdit", "int WeakRefs() const", asMETHODPR(LineEdit, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_weakRefs() const", asMETHODPR(LineEdit, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(LineEdit, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(LineEdit, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(LineEdit, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_BorderImage
    REGISTER_MANUAL_PART_BorderImage(LineEdit, "LineEdit")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(LineEdit, "LineEdit")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(LineEdit, "LineEdit")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(LineEdit, "LineEdit")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(LineEdit, "LineEdit")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(LineEdit, "LineEdit")
#endif
#ifdef REGISTER_MANUAL_PART_LineEdit
    REGISTER_MANUAL_PART_LineEdit(LineEdit, "LineEdit")
#endif
    RegisterSubclass<BorderImage, LineEdit>(engine, "BorderImage", "LineEdit");
    RegisterSubclass<UIElement, LineEdit>(engine, "UIElement", "LineEdit");
    RegisterSubclass<Animatable, LineEdit>(engine, "Animatable", "LineEdit");
    RegisterSubclass<Serializable, LineEdit>(engine, "Serializable", "LineEdit");
    RegisterSubclass<Object, LineEdit>(engine, "Object", "LineEdit");
    RegisterSubclass<RefCounted, LineEdit>(engine, "RefCounted", "LineEdit");

    // void ListBase::Swap(ListBase& rhs) | File: ../Container/ListBase.h
    engine->RegisterObjectMethod("ListBase", "void Swap(ListBase&)", asMETHODPR(ListBase, Swap, (ListBase&), void), asCALL_THISCALL);
    // ListBase& ListBase::operator=(const ListBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ListBase>(engine, "ListBase");
#ifdef REGISTER_MANUAL_PART_ListBase
    REGISTER_MANUAL_PART_ListBase(ListBase, "ListBase")
#endif

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void AddChild(UIElement@+)", asMETHODPR(ListView, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void ListView::AddItem(UIElement* item) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void AddItem(UIElement@+)", asMETHODPR(ListView, AddItem, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ListView", asBEHAVE_ADDREF, "void f()", asMETHODPR(ListView, AddRef, (), void), asCALL_THISCALL);
    // void ListView::AddSelection(unsigned index) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void AddSelection(uint)", asMETHODPR(ListView, AddSelection, (unsigned), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void AddTag(const String&in)", asMETHODPR(ListView, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void AddTags(const String&in, int8 = ';')", asMETHODPR(ListView, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void AdjustScissor(IntRect&)", asMETHODPR(ListView, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void AllocateNetworkState()", asMETHODPR(ListView, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void ScrollView::ApplyAttributes() override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void ApplyAttributes()", asMETHODPR(ListView, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void BringToFront()", asMETHODPR(ListView, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void ListView::ChangeSelection(int delta, bool additive=false) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void ChangeSelection(int, bool = false)", asMETHODPR(ListView, ChangeSelection, (int, bool), void), asCALL_THISCALL);
    // void ListView::ClearSelection() | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void ClearSelection()", asMETHODPR(ListView, ClearSelection, (), void), asCALL_THISCALL);
    // void ListView::CopySelectedItemsToClipboard() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void CopySelectedItemsToClipboard() const", asMETHODPR(ListView, CopySelectedItemsToClipboard, () const, void), asCALL_THISCALL);
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(ListView, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void ListView::DisableInternalLayoutUpdate() | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void DisableInternalLayoutUpdate()", asMETHODPR(ListView, DisableInternalLayoutUpdate, (), void), asCALL_THISCALL);
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void DisableLayoutUpdate()", asMETHODPR(ListView, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(ListView, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void ListView::EnableInternalLayoutUpdate() | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void EnableInternalLayoutUpdate()", asMETHODPR(ListView, EnableInternalLayoutUpdate, (), void), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void EnableLayoutUpdate()", asMETHODPR(ListView, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // void ListView::EnsureItemVisibility(unsigned index) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void EnsureItemVisibility(uint)", asMETHODPR(ListView, EnsureItemVisibility, (unsigned), void), asCALL_THISCALL);
    // void ListView::EnsureItemVisibility(UIElement* item) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void EnsureItemVisibility(UIElement@+)", asMETHODPR(ListView, EnsureItemVisibility, (UIElement*), void), asCALL_THISCALL);
    // void ListView::Expand(unsigned index, bool enable, bool recursive=false) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void Expand(uint, bool, bool = false)", asMETHODPR(ListView, Expand, (unsigned, bool, bool), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool FilterAttributes(XMLElement&) const", asMETHODPR(ListView, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "uint FindChild(UIElement@+) const", asMETHODPR(ListView, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // unsigned ListView::FindItem(UIElement* item) const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "uint FindItem(UIElement@+) const", asMETHODPR(ListView, FindItem, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "bool GetAnimationEnabled() const", asMETHODPR(ListView, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_animationEnabled() const", asMETHODPR(ListView, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const String& GetAppliedStyle() const", asMETHODPR(ListView, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const String& get_style() const", asMETHODPR(ListView, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "Variant GetAttribute(uint) const", asMETHODPR(ListView, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "Variant get_attributes(uint) const", asMETHODPR(ListView, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "Variant GetAttribute(const String&in) const", asMETHODPR(ListView, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ListView, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ListView, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ListView, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ListView, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "Variant GetAttributeDefault(uint) const", asMETHODPR(ListView, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "Variant get_attributeDefaults(uint) const", asMETHODPR(ListView, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ListView, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool ScrollView::GetAutoDisableChildren() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "bool GetAutoDisableChildren() const", asMETHODPR(ListView, GetAutoDisableChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_autoDisableChildren() const", asMETHODPR(ListView, GetAutoDisableChildren, () const, bool), asCALL_THISCALL);
    // float ScrollView::GetAutoDisableThreshold() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "float GetAutoDisableThreshold() const", asMETHODPR(ListView, GetAutoDisableThreshold, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_autoDisableThreshold() const", asMETHODPR(ListView, GetAutoDisableThreshold, () const, float), asCALL_THISCALL);
    // int ListView::GetBaseIndent() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "int GetBaseIndent() const", asMETHODPR(ListView, GetBaseIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_baseIndent() const", asMETHODPR(ListView, GetBaseIndent, () const, int), asCALL_THISCALL);
    // virtual void UIElement::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "bool GetBlockEvents() const", asMETHODPR(ListView, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool GetBringToBack() const", asMETHODPR(ListView, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_bringToBack() const", asMETHODPR(ListView, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool GetBringToFront() const", asMETHODPR(ListView, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_bringToFront() const", asMETHODPR(ListView, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "const String& GetCategory() const", asMETHODPR(ListView, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const String& get_category() const", asMETHODPR(ListView, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetChild(uint) const", asMETHODPR(ListView, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_children(uint) const", asMETHODPR(ListView, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(ListView, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(ListView, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetChildOffset() const", asMETHODPR(ListView, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_childOffset() const", asMETHODPR(ListView, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ GetChildren() const", asFUNCTION(ListView_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(ListView_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(ListView_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // bool ListView::GetClearSelectionOnDefocus() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "bool GetClearSelectionOnDefocus() const", asMETHODPR(ListView, GetClearSelectionOnDefocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_clearSelectionOnDefocus() const", asMETHODPR(ListView, GetClearSelectionOnDefocus, () const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntRect& GetClipBorder() const", asMETHODPR(ListView, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntRect& get_clipBorder() const", asMETHODPR(ListView, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool GetClipChildren() const", asMETHODPR(ListView, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_clipChildren() const", asMETHODPR(ListView, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Color& GetColor(Corner) const", asMETHODPR(ListView, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const Color& get_colors(Corner) const", asMETHODPR(ListView, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Color& GetColorAttr() const", asMETHODPR(ListView, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "IntRect GetCombinedScreenRect()", asMETHODPR(ListView, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "IntRect get_combinedScreenRect()", asMETHODPR(ListView, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // UIElement* ScrollView::GetContentElement() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetContentElement() const", asMETHODPR(ListView, GetContentElement, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_contentElement() const", asMETHODPR(ListView, GetContentElement, () const, UIElement*), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(ListView, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Color& GetDerivedColor() const", asMETHODPR(ListView, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "float GetDerivedOpacity() const", asMETHODPR(ListView, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_derivedOpacity() const", asMETHODPR(ListView, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(ListView, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(ListView, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "uint GetDragButtonCount() const", asMETHODPR(ListView, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "uint get_dragButtonCount() const", asMETHODPR(ListView, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(ListView, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(ListView, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(ListView, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetElementEventSender() const", asMETHODPR(ListView, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool GetEnableAnchor() const", asMETHODPR(ListView, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_enableAnchor() const", asMETHODPR(ListView, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "VariantMap& GetEventDataMap() const", asMETHODPR(ListView, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "Object@+ GetEventSender() const", asMETHODPR(ListView, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "FocusMode GetFocusMode() const", asMETHODPR(ListView, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "FocusMode get_focusMode() const", asMETHODPR(ListView, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ListView, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ListView, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "const VariantMap& GetGlobalVars() const", asMETHODPR(ListView, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const VariantMap& get_globalVars() const", asMETHODPR(ListView, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetHeight() const", asMETHODPR(ListView, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_height() const", asMETHODPR(ListView, GetHeight, () const, int), asCALL_THISCALL);
    // bool ListView::GetHierarchyMode() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "bool GetHierarchyMode() const", asMETHODPR(ListView, GetHierarchyMode, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_hierarchyMode() const", asMETHODPR(ListView, GetHierarchyMode, () const, bool), asCALL_THISCALL);
    // HighlightMode ListView::GetHighlightMode() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "HighlightMode GetHighlightMode() const", asMETHODPR(ListView, GetHighlightMode, () const, HighlightMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "HighlightMode get_highlightMode() const", asMETHODPR(ListView, GetHighlightMode, () const, HighlightMode), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(ListView, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(ListView, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // ScrollBar* ScrollView::GetHorizontalScrollBar() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "ScrollBar@+ GetHorizontalScrollBar() const", asMETHODPR(ListView, GetHorizontalScrollBar, () const, ScrollBar*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "ScrollBar@+ get_horizontalScrollBar() const", asMETHODPR(ListView, GetHorizontalScrollBar, () const, ScrollBar*), asCALL_THISCALL);
    // bool ScrollView::GetHorizontalScrollBarVisible() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "bool GetHorizontalScrollBarVisible() const", asMETHODPR(ListView, GetHorizontalScrollBarVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_horizontalScrollBarVisible() const", asMETHODPR(ListView, GetHorizontalScrollBarVisible, () const, bool), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetIndent() const", asMETHODPR(ListView, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_indent() const", asMETHODPR(ListView, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetIndentSpacing() const", asMETHODPR(ListView, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_indentSpacing() const", asMETHODPR(ListView, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetIndentWidth() const", asMETHODPR(ListView, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_indentWidth() const", asMETHODPR(ListView, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ListView, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // UIElement* ListView::GetItem(unsigned index) const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetItem(uint) const", asMETHODPR(ListView, GetItem, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_items(uint) const", asMETHODPR(ListView, GetItem, (unsigned) const, UIElement*), asCALL_THISCALL);
    // PODVector<UIElement*> ListView::GetItems() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ GetItems() const", asFUNCTION(ListView_GetItems_void), asCALL_CDECL_OBJFIRST);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntRect& GetLayoutBorder() const", asMETHODPR(ListView, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntRect& get_layoutBorder() const", asMETHODPR(ListView, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetLayoutElementMaxSize() const", asMETHODPR(ListView, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(ListView, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const Vector2& get_layoutFlexScale() const", asMETHODPR(ListView, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "LayoutMode GetLayoutMode() const", asMETHODPR(ListView, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "LayoutMode get_layoutMode() const", asMETHODPR(ListView, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetLayoutSpacing() const", asMETHODPR(ListView, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_layoutSpacing() const", asMETHODPR(ListView, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Vector2& GetMaxAnchor() const", asMETHODPR(ListView, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const Vector2& get_maxAnchor() const", asMETHODPR(ListView, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetMaxHeight() const", asMETHODPR(ListView, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_maxHeight() const", asMETHODPR(ListView, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetMaxOffset() const", asMETHODPR(ListView, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_maxOffset() const", asMETHODPR(ListView, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetMaxSize() const", asMETHODPR(ListView, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_maxSize() const", asMETHODPR(ListView, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetMaxWidth() const", asMETHODPR(ListView, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_maxWidth() const", asMETHODPR(ListView, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Vector2& GetMinAnchor() const", asMETHODPR(ListView, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const Vector2& get_minAnchor() const", asMETHODPR(ListView, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetMinHeight() const", asMETHODPR(ListView, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_minHeight() const", asMETHODPR(ListView, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetMinOffset() const", asMETHODPR(ListView, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_minOffset() const", asMETHODPR(ListView, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetMinSize() const", asMETHODPR(ListView, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_minSize() const", asMETHODPR(ListView, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetMinWidth() const", asMETHODPR(ListView, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_minWidth() const", asMETHODPR(ListView, GetMinWidth, () const, int), asCALL_THISCALL);
    // bool ListView::GetMultiselect() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "bool GetMultiselect() const", asMETHODPR(ListView, GetMultiselect, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_multiselect() const", asMETHODPR(ListView, GetMultiselect, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const String& GetName() const", asMETHODPR(ListView, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const String& get_name() const", asMETHODPR(ListView, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "uint GetNumAttributes() const", asMETHODPR(ListView, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "uint get_numAttributes() const", asMETHODPR(ListView, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "uint GetNumChildren(bool = false) const", asMETHODPR(ListView, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "uint get_numChildren(bool = false) const", asMETHODPR(ListView, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned ListView::GetNumItems() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "uint GetNumItems() const", asMETHODPR(ListView, GetNumItems, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "uint get_numItems() const", asMETHODPR(ListView, GetNumItems, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "uint GetNumNetworkAttributes() const", asMETHODPR(ListView, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ListView, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ListView, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ListView, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "float GetOpacity() const", asMETHODPR(ListView, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_opacity() const", asMETHODPR(ListView, GetOpacity, () const, float), asCALL_THISCALL);
    // float ScrollView::GetPageStep() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "float GetPageStep() const", asMETHODPR(ListView, GetPageStep, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_pageStep() const", asMETHODPR(ListView, GetPageStep, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetParent() const", asMETHODPR(ListView, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_parent() const", asMETHODPR(ListView, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Vector2& GetPivot() const", asMETHODPR(ListView, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const Vector2& get_pivot() const", asMETHODPR(ListView, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetPosition() const", asMETHODPR(ListView, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_position() const", asMETHODPR(ListView, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetPriority() const", asMETHODPR(ListView, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_priority() const", asMETHODPR(ListView, GetPriority, () const, int), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetRoot() const", asMETHODPR(ListView, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_root() const", asMETHODPR(ListView, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetScreenPosition() const", asMETHODPR(ListView, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_screenPosition() const", asMETHODPR(ListView, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // bool ScrollView::GetScrollBarsAutoVisible() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "bool GetScrollBarsAutoVisible() const", asMETHODPR(ListView, GetScrollBarsAutoVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_scrollBarsAutoVisible() const", asMETHODPR(ListView, GetScrollBarsAutoVisible, () const, bool), asCALL_THISCALL);
    // float ScrollView::GetScrollDeceleration() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "float GetScrollDeceleration() const", asMETHODPR(ListView, GetScrollDeceleration, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_scrollDeceleration() const", asMETHODPR(ListView, GetScrollDeceleration, () const, float), asCALL_THISCALL);
    // BorderImage* ScrollView::GetScrollPanel() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "BorderImage@+ GetScrollPanel() const", asMETHODPR(ListView, GetScrollPanel, () const, BorderImage*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "BorderImage@+ get_scrollPanel() const", asMETHODPR(ListView, GetScrollPanel, () const, BorderImage*), asCALL_THISCALL);
    // float ScrollView::GetScrollSnapEpsilon() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "float GetScrollSnapEpsilon() const", asMETHODPR(ListView, GetScrollSnapEpsilon, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_scrollSnapEpsilon() const", asMETHODPR(ListView, GetScrollSnapEpsilon, () const, float), asCALL_THISCALL);
    // float ScrollView::GetScrollStep() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "float GetScrollStep() const", asMETHODPR(ListView, GetScrollStep, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_scrollStep() const", asMETHODPR(ListView, GetScrollStep, () const, float), asCALL_THISCALL);
    // UIElement* ListView::GetSelectedItem() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetSelectedItem() const", asMETHODPR(ListView, GetSelectedItem, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_selectedItem() const", asMETHODPR(ListView, GetSelectedItem, () const, UIElement*), asCALL_THISCALL);
    // PODVector<UIElement*> ListView::GetSelectedItems() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ GetSelectedItems() const", asFUNCTION(ListView_GetSelectedItems_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ get_selectedItems() const", asFUNCTION(ListView_GetSelectedItems_void), asCALL_CDECL_OBJFIRST);
    // unsigned ListView::GetSelection() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "uint GetSelection() const", asMETHODPR(ListView, GetSelection, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "uint get_selection() const", asMETHODPR(ListView, GetSelection, () const, unsigned), asCALL_THISCALL);
    // const PODVector<unsigned>& ListView::GetSelections() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "Array<uint>@ GetSelections() const", asFUNCTION(ListView_GetSelections_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ListView", "Array<uint>@ get_selections() const", asFUNCTION(ListView_GetSelections_void), asCALL_CDECL_OBJFIRST);
    // bool ListView::GetSelectOnClickEnd() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "bool GetSelectOnClickEnd() const", asMETHODPR(ListView, GetSelectOnClickEnd, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_selectOnClickEnd() const", asMETHODPR(ListView, GetSelectOnClickEnd, () const, bool), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetSize() const", asMETHODPR(ListView, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_size() const", asMETHODPR(ListView, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool GetSortChildren() const", asMETHODPR(ListView, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_sortChildren() const", asMETHODPR(ListView, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ListView, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "Array<String>@ GetTags() const", asFUNCTION(ListView_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ListView", "Array<String>@ get_tags() const", asFUNCTION(ListView_GetTags_void), asCALL_CDECL_OBJFIRST);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "TraversalMode GetTraversalMode() const", asMETHODPR(ListView, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "TraversalMode get_traversalMode() const", asMETHODPR(ListView, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "StringHash GetType() const", asMETHODPR(ListView, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "StringHash get_type() const", asMETHODPR(ListView, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "const String& GetTypeName() const", asMETHODPR(ListView, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const String& get_typeName() const", asMETHODPR(ListView, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool GetUseDerivedOpacity() const", asMETHODPR(ListView, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_useDerivedOpacity() const", asMETHODPR(ListView, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(ListView, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const VariantMap& GetVars() const", asMETHODPR(ListView, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(ListView, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(ListView, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // ScrollBar* ScrollView::GetVerticalScrollBar() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "ScrollBar@+ GetVerticalScrollBar() const", asMETHODPR(ListView, GetVerticalScrollBar, () const, ScrollBar*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "ScrollBar@+ get_verticalScrollBar() const", asMETHODPR(ListView, GetVerticalScrollBar, () const, ScrollBar*), asCALL_THISCALL);
    // bool ScrollView::GetVerticalScrollBarVisible() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "bool GetVerticalScrollBarVisible() const", asMETHODPR(ListView, GetVerticalScrollBarVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_verticalScrollBarVisible() const", asMETHODPR(ListView, GetVerticalScrollBarVisible, () const, bool), asCALL_THISCALL);
    // const IntVector2& ScrollView::GetViewPosition() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetViewPosition() const", asMETHODPR(ListView, GetViewPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_viewPosition() const", asMETHODPR(ListView, GetViewPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetWidth() const", asMETHODPR(ListView, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_width() const", asMETHODPR(ListView, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool HasColorGradient() const", asMETHODPR(ListView, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_colorGradient() const", asMETHODPR(ListView, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "bool HasEventHandlers() const", asMETHODPR(ListView, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool HasFocus() const", asMETHODPR(ListView, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_focus() const", asMETHODPR(ListView, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ListView, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ListView, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool HasTag(const String&in) const", asMETHODPR(ListView, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void InsertChild(uint, UIElement@+)", asMETHODPR(ListView, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // void ListView::InsertItem(unsigned index, UIElement* item, UIElement* parentItem=nullptr) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void InsertItem(uint, UIElement@+, UIElement@+ = null)", asMETHODPR(ListView, InsertItem, (unsigned, UIElement*, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsChildOf(UIElement@+) const", asMETHODPR(ListView, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsEditable() const", asMETHODPR(ListView, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_editable() const", asMETHODPR(ListView, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsElementEventSender() const", asMETHODPR(ListView, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_elementEventSender() const", asMETHODPR(ListView, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsEnabled() const", asMETHODPR(ListView, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_enabled() const", asMETHODPR(ListView, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsEnabledSelf() const", asMETHODPR(ListView, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_enabledSelf() const", asMETHODPR(ListView, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool ListView::IsExpanded(unsigned index) const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "bool IsExpanded(uint) const", asMETHODPR(ListView, IsExpanded, (unsigned) const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsFixedHeight() const", asMETHODPR(ListView, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_fixedHeight() const", asMETHODPR(ListView, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsFixedSize() const", asMETHODPR(ListView, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_fixedSize() const", asMETHODPR(ListView, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsFixedWidth() const", asMETHODPR(ListView, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_fixedWidth() const", asMETHODPR(ListView, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsHovering() const", asMETHODPR(ListView, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_hovering() const", asMETHODPR(ListView, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsInside(IntVector2, bool)", asMETHODPR(ListView, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(ListView, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "bool IsInstanceOf(StringHash) const", asMETHODPR(ListView, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsInternal() const", asMETHODPR(ListView, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_internal() const", asMETHODPR(ListView, IsInternal, () const, bool), asCALL_THISCALL);
    // bool ListView::IsSelected(unsigned index) const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "bool IsSelected(uint) const", asMETHODPR(ListView, IsSelected, (unsigned) const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool IsTemporary() const", asMETHODPR(ListView, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_temporary() const", asMETHODPR(ListView, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsVisible() const", asMETHODPR(ListView, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_visible() const", asMETHODPR(ListView, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsVisibleEffective() const", asMETHODPR(ListView, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_visibleEffective() const", asMETHODPR(ListView, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // bool ScrollView::IsWheelHandler() const override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "bool IsWheelHandler() const", asMETHODPR(ListView, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(ListView, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // explicit ListView::ListView(Context* context) | File: ../UI/ListView.h
    engine->RegisterObjectBehaviour("ListView", asBEHAVE_FACTORY, "ListView@+ f()", asFUNCTION(ListView_ListView_Context), asCALL_CDECL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool Load(Deserializer&)", asMETHODPR(ListView, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(ListView, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ListView, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool LoadXML(const XMLElement&in)", asMETHODPR(ListView, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(ListView, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool LoadXML(Deserializer&)", asMETHODPR(ListView, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void MarkNetworkUpdate()", asMETHODPR(ListView, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ListView, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(ListView, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ListView, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ListView, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(ListView, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(ListView, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool OnDragDropTest(UIElement@+)", asMETHODPR(ListView, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(ListView, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ListView, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ListView, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ListView, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ListView, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnIndentSet()", asMETHODPR(ListView, OnIndentSet, (), void), asCALL_THISCALL);
    // void ListView::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(ListView, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnPositionSet(const IntVector2&in)", asMETHODPR(ListView, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // void ListView::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(ListView, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ListView, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnSetEditable()", asMETHODPR(ListView, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnTextInput(const String&in)", asMETHODPR(ListView, OnTextInput, (const String&), void), asCALL_THISCALL);
    // void ScrollView::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(ListView, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ListView, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ListView, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ListView", "int Refs() const", asMETHODPR(ListView, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_refs() const", asMETHODPR(ListView, Refs, () const, int), asCALL_THISCALL);
    // static void ListView::RegisterObject(Context* context) | File: ../UI/ListView.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ListView", asBEHAVE_RELEASE, "void f()", asMETHODPR(ListView, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void Remove()", asMETHODPR(ListView, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void RemoveAllChildren()", asMETHODPR(ListView, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void ListView::RemoveAllItems() | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void RemoveAllItems()", asMETHODPR(ListView, RemoveAllItems, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void RemoveAllTags()", asMETHODPR(ListView, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ListView, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(ListView, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void RemoveChildAtIndex(uint)", asMETHODPR(ListView, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void RemoveInstanceDefault()", asMETHODPR(ListView, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void ListView::RemoveItem(UIElement* item, unsigned index=0) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void RemoveItem(UIElement@+, uint = 0)", asMETHODPR(ListView, RemoveItem, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void ListView::RemoveItem(unsigned index) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void RemoveItem(uint)", asMETHODPR(ListView, RemoveItem, (unsigned), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void RemoveObjectAnimation()", asMETHODPR(ListView, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void ListView::RemoveSelection(unsigned index) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void RemoveSelection(uint)", asMETHODPR(ListView, RemoveSelection, (unsigned), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool RemoveTag(const String&in)", asMETHODPR(ListView, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void ResetDeepEnabled()", asMETHODPR(ListView, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void ResetToDefault()", asMETHODPR(ListView, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool Save(Serializer&) const", asMETHODPR(ListView, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool SaveDefaultAttributes() const", asMETHODPR(ListView, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "bool SaveJSON(JSONValue&) const", asMETHODPR(ListView, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool SaveXML(XMLElement&) const", asMETHODPR(ListView, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(ListView, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(ListView, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void SendEvent(StringHash)", asMETHODPR(ListView, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ListView, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(ListView, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetAnimationEnabled(bool)", asMETHODPR(ListView, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_animationEnabled(bool)", asMETHODPR(ListView, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetAnimationTime(float)", asMETHODPR(ListView, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ListView, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ListView, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ListView, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ListView, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ListView, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ListView, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ListView, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void ScrollView::SetAutoDisableChildren(bool disable) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetAutoDisableChildren(bool)", asMETHODPR(ListView, SetAutoDisableChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_autoDisableChildren(bool)", asMETHODPR(ListView, SetAutoDisableChildren, (bool), void), asCALL_THISCALL);
    // void ScrollView::SetAutoDisableThreshold(float amount) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetAutoDisableThreshold(float)", asMETHODPR(ListView, SetAutoDisableThreshold, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_autoDisableThreshold(float)", asMETHODPR(ListView, SetAutoDisableThreshold, (float), void), asCALL_THISCALL);
    // void ListView::SetBaseIndent(int baseIndent) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetBaseIndent(int)", asMETHODPR(ListView, SetBaseIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_baseIndent(int)", asMETHODPR(ListView, SetBaseIndent, (int), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void SetBlockEvents(bool)", asMETHODPR(ListView, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetBringToBack(bool)", asMETHODPR(ListView, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_bringToBack(bool)", asMETHODPR(ListView, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetBringToFront(bool)", asMETHODPR(ListView, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_bringToFront(bool)", asMETHODPR(ListView, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetChildOffset(const IntVector2&in)", asMETHODPR(ListView, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void ListView::SetClearSelectionOnDefocus(bool enable) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetClearSelectionOnDefocus(bool)", asMETHODPR(ListView, SetClearSelectionOnDefocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_clearSelectionOnDefocus(bool)", asMETHODPR(ListView, SetClearSelectionOnDefocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetClipBorder(const IntRect&in)", asMETHODPR(ListView, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_clipBorder(const IntRect&in)", asMETHODPR(ListView, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetClipChildren(bool)", asMETHODPR(ListView, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_clipChildren(bool)", asMETHODPR(ListView, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetColor(const Color&in)", asMETHODPR(ListView, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_color(const Color&in)", asMETHODPR(ListView, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetColor(Corner, const Color&in)", asMETHODPR(ListView, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_colors(Corner, const Color&in)", asMETHODPR(ListView, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void ScrollView::SetContentElement(UIElement* element) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetContentElement(UIElement@+)", asMETHODPR(ListView, SetContentElement, (UIElement*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_contentElement(UIElement@+)", asMETHODPR(ListView, SetContentElement, (UIElement*), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetDeepEnabled(bool)", asMETHODPR(ListView, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(ListView, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_defaultStyle(XMLFile@+)", asMETHODPR(ListView, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(ListView, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(ListView, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetEditable(bool)", asMETHODPR(ListView, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_editable(bool)", asMETHODPR(ListView, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetElementEventSender(bool)", asMETHODPR(ListView, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_elementEventSender(bool)", asMETHODPR(ListView, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetEnableAnchor(bool)", asMETHODPR(ListView, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_enableAnchor(bool)", asMETHODPR(ListView, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetEnabled(bool)", asMETHODPR(ListView, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_enabled(bool)", asMETHODPR(ListView, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetEnabledRecursive(bool)", asMETHODPR(ListView, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetFixedHeight(int)", asMETHODPR(ListView, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetFixedSize(const IntVector2&in)", asMETHODPR(ListView, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetFixedSize(int, int)", asMETHODPR(ListView, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetFixedWidth(int)", asMETHODPR(ListView, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetFocus(bool)", asMETHODPR(ListView, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_focus(bool)", asMETHODPR(ListView, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetFocusMode(FocusMode)", asMETHODPR(ListView, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_focusMode(FocusMode)", asMETHODPR(ListView, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ListView, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ListView, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetHeight(int)", asMETHODPR(ListView, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_height(int)", asMETHODPR(ListView, SetHeight, (int), void), asCALL_THISCALL);
    // void ListView::SetHierarchyMode(bool enable) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetHierarchyMode(bool)", asMETHODPR(ListView, SetHierarchyMode, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_hierarchyMode(bool)", asMETHODPR(ListView, SetHierarchyMode, (bool), void), asCALL_THISCALL);
    // void ListView::SetHighlightMode(HighlightMode mode) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetHighlightMode(HighlightMode)", asMETHODPR(ListView, SetHighlightMode, (HighlightMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_highlightMode(HighlightMode)", asMETHODPR(ListView, SetHighlightMode, (HighlightMode), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(ListView, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(ListView, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void ScrollView::SetHorizontalScrollBarVisible(bool visible) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetHorizontalScrollBarVisible(bool)", asMETHODPR(ListView, SetHorizontalScrollBarVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_horizontalScrollBarVisible(bool)", asMETHODPR(ListView, SetHorizontalScrollBarVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetHovering(bool)", asMETHODPR(ListView, SetHovering, (bool), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetIndent(int)", asMETHODPR(ListView, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_indent(int)", asMETHODPR(ListView, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetIndentSpacing(int)", asMETHODPR(ListView, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_indentSpacing(int)", asMETHODPR(ListView, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void SetInstanceDefault(bool)", asMETHODPR(ListView, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ListView, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetInternal(bool)", asMETHODPR(ListView, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_internal(bool)", asMETHODPR(ListView, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(ListView, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(ListView, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_layoutBorder(const IntRect&in)", asMETHODPR(ListView, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(ListView, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(ListView, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetLayoutMode(LayoutMode)", asMETHODPR(ListView, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_layoutMode(LayoutMode)", asMETHODPR(ListView, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetLayoutSpacing(int)", asMETHODPR(ListView, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_layoutSpacing(int)", asMETHODPR(ListView, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(ListView, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_maxAnchor(const Vector2&in)", asMETHODPR(ListView, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxAnchor(float, float)", asMETHODPR(ListView, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxHeight(int)", asMETHODPR(ListView, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_maxHeight(int)", asMETHODPR(ListView, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(ListView, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_maxOffset(const IntVector2&in)", asMETHODPR(ListView, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxSize(const IntVector2&in)", asMETHODPR(ListView, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_maxSize(const IntVector2&in)", asMETHODPR(ListView, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxSize(int, int)", asMETHODPR(ListView, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxWidth(int)", asMETHODPR(ListView, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_maxWidth(int)", asMETHODPR(ListView, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinAnchor(const Vector2&in)", asMETHODPR(ListView, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_minAnchor(const Vector2&in)", asMETHODPR(ListView, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinAnchor(float, float)", asMETHODPR(ListView, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinHeight(int)", asMETHODPR(ListView, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_minHeight(int)", asMETHODPR(ListView, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinOffset(const IntVector2&in)", asMETHODPR(ListView, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_minOffset(const IntVector2&in)", asMETHODPR(ListView, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinSize(const IntVector2&in)", asMETHODPR(ListView, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_minSize(const IntVector2&in)", asMETHODPR(ListView, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinSize(int, int)", asMETHODPR(ListView, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinWidth(int)", asMETHODPR(ListView, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_minWidth(int)", asMETHODPR(ListView, SetMinWidth, (int), void), asCALL_THISCALL);
    // void ListView::SetMultiselect(bool enable) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetMultiselect(bool)", asMETHODPR(ListView, SetMultiselect, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_multiselect(bool)", asMETHODPR(ListView, SetMultiselect, (bool), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetName(const String&in)", asMETHODPR(ListView, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_name(const String&in)", asMETHODPR(ListView, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ListView, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ListView, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ListView, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetOpacity(float)", asMETHODPR(ListView, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_opacity(float)", asMETHODPR(ListView, SetOpacity, (float), void), asCALL_THISCALL);
    // void ScrollView::SetPageStep(float step) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetPageStep(float)", asMETHODPR(ListView, SetPageStep, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_pageStep(float)", asMETHODPR(ListView, SetPageStep, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(ListView, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetPivot(const Vector2&in)", asMETHODPR(ListView, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_pivot(const Vector2&in)", asMETHODPR(ListView, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetPivot(float, float)", asMETHODPR(ListView, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetPosition(const IntVector2&in)", asMETHODPR(ListView, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_position(const IntVector2&in)", asMETHODPR(ListView, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetPosition(int, int)", asMETHODPR(ListView, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetPriority(int)", asMETHODPR(ListView, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_priority(int)", asMETHODPR(ListView, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetRenderTexture(Texture2D@+)", asMETHODPR(ListView, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void ScrollView::SetScrollBarsAutoVisible(bool enable) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetScrollBarsAutoVisible(bool)", asMETHODPR(ListView, SetScrollBarsAutoVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_scrollBarsAutoVisible(bool)", asMETHODPR(ListView, SetScrollBarsAutoVisible, (bool), void), asCALL_THISCALL);
    // void ScrollView::SetScrollBarsVisible(bool horizontal, bool vertical) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetScrollBarsVisible(bool, bool)", asMETHODPR(ListView, SetScrollBarsVisible, (bool, bool), void), asCALL_THISCALL);
    // void ScrollView::SetScrollDeceleration(float deceleration) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetScrollDeceleration(float)", asMETHODPR(ListView, SetScrollDeceleration, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_scrollDeceleration(float)", asMETHODPR(ListView, SetScrollDeceleration, (float), void), asCALL_THISCALL);
    // void ScrollView::SetScrollSnapEpsilon(float snap) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetScrollSnapEpsilon(float)", asMETHODPR(ListView, SetScrollSnapEpsilon, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_scrollSnapEpsilon(float)", asMETHODPR(ListView, SetScrollSnapEpsilon, (float), void), asCALL_THISCALL);
    // void ScrollView::SetScrollStep(float step) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetScrollStep(float)", asMETHODPR(ListView, SetScrollStep, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_scrollStep(float)", asMETHODPR(ListView, SetScrollStep, (float), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetSelected(bool)", asMETHODPR(ListView, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_selected(bool)", asMETHODPR(ListView, SetSelected, (bool), void), asCALL_THISCALL);
    // void ListView::SetSelection(unsigned index) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetSelection(uint)", asMETHODPR(ListView, SetSelection, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_selection(uint)", asMETHODPR(ListView, SetSelection, (unsigned), void), asCALL_THISCALL);
    // void ListView::SetSelections(const PODVector<unsigned>& indices) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetSelections(Array<uint>@+)", asFUNCTION(ListView_SetSelections_PODVectorunsigned), asCALL_CDECL_OBJFIRST);
    // void ListView::SetSelectOnClickEnd(bool enable) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetSelectOnClickEnd(bool)", asMETHODPR(ListView, SetSelectOnClickEnd, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_selectOnClickEnd(bool)", asMETHODPR(ListView, SetSelectOnClickEnd, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetSize(const IntVector2&in)", asMETHODPR(ListView, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_size(const IntVector2&in)", asMETHODPR(ListView, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetSize(int, int)", asMETHODPR(ListView, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetSortChildren(bool)", asMETHODPR(ListView, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_sortChildren(bool)", asMETHODPR(ListView, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(ListView, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool SetStyle(const XMLElement&in)", asMETHODPR(ListView, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(ListView, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void SetTemporary(bool)", asMETHODPR(ListView, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_temporary(bool)", asMETHODPR(ListView, SetTemporary, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetTraversalMode(TraversalMode)", asMETHODPR(ListView, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_traversalMode(TraversalMode)", asMETHODPR(ListView, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetUseDerivedOpacity(bool)", asMETHODPR(ListView, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_useDerivedOpacity(bool)", asMETHODPR(ListView, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetVar(StringHash, const Variant&in)", asMETHODPR(ListView, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(ListView, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(ListView, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void ScrollView::SetVerticalScrollBarVisible(bool visible) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetVerticalScrollBarVisible(bool)", asMETHODPR(ListView, SetVerticalScrollBarVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_verticalScrollBarVisible(bool)", asMETHODPR(ListView, SetVerticalScrollBarVisible, (bool), void), asCALL_THISCALL);
    // void ScrollView::SetViewPosition(const IntVector2& position) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetViewPosition(const IntVector2&in)", asMETHODPR(ListView, SetViewPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_viewPosition(const IntVector2&in)", asMETHODPR(ListView, SetViewPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void ScrollView::SetViewPosition(int x, int y) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetViewPosition(int, int)", asMETHODPR(ListView, SetViewPosition, (int, int), void), asCALL_THISCALL);
    // void ScrollView::SetViewPositionAttr(const IntVector2& value) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetViewPositionAttr(const IntVector2&in)", asMETHODPR(ListView, SetViewPositionAttr, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetVisible(bool)", asMETHODPR(ListView, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_visible(bool)", asMETHODPR(ListView, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetWidth(int)", asMETHODPR(ListView, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_width(int)", asMETHODPR(ListView, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SortChildren()", asMETHODPR(ListView, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void ListView::ToggleExpand(unsigned index, bool recursive=false) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void ToggleExpand(uint, bool = false)", asMETHODPR(ListView, ToggleExpand, (unsigned, bool), void), asCALL_THISCALL);
    // void ListView::ToggleSelection(unsigned index) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void ToggleSelection(uint)", asMETHODPR(ListView, ToggleSelection, (unsigned), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void UnsubscribeFromAllEvents()", asMETHODPR(ListView, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ListView_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ListView, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ListView, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ListView, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void ScrollView::Update(float timeStep) override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void Update(float)", asMETHODPR(ListView, Update, (float), void), asCALL_THISCALL);
    // void ListView::UpdateInternalLayout() | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void UpdateInternalLayout()", asMETHODPR(ListView, UpdateInternalLayout, (), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void UpdateLayout()", asMETHODPR(ListView, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ListView", "int WeakRefs() const", asMETHODPR(ListView, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_weakRefs() const", asMETHODPR(ListView, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ListView, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ListView, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ListView, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_ScrollView
    REGISTER_MANUAL_PART_ScrollView(ListView, "ListView")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(ListView, "ListView")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ListView, "ListView")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ListView, "ListView")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ListView, "ListView")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ListView, "ListView")
#endif
#ifdef REGISTER_MANUAL_PART_ListView
    REGISTER_MANUAL_PART_ListView(ListView, "ListView")
#endif
    RegisterSubclass<ScrollView, ListView>(engine, "ScrollView", "ListView");
    RegisterSubclass<UIElement, ListView>(engine, "UIElement", "ListView");
    RegisterSubclass<Animatable, ListView>(engine, "Animatable", "ListView");
    RegisterSubclass<Serializable, ListView>(engine, "Serializable", "ListView");
    RegisterSubclass<Object, ListView>(engine, "Object", "ListView");
    RegisterSubclass<RefCounted, ListView>(engine, "RefCounted", "ListView");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Localization", asBEHAVE_ADDREF, "void f()", asMETHODPR(Localization, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // String Localization::Get(const String& id) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "String Get(const String&in)", asMETHODPR(Localization, Get, (const String&), String), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "bool GetBlockEvents() const", asMETHODPR(Localization, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "const String& GetCategory() const", asMETHODPR(Localization, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "const String& get_category() const", asMETHODPR(Localization, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "VariantMap& GetEventDataMap() const", asMETHODPR(Localization, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "Object@+ GetEventSender() const", asMETHODPR(Localization, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Localization, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Localization, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "const VariantMap& GetGlobalVars() const", asMETHODPR(Localization, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "const VariantMap& get_globalVars() const", asMETHODPR(Localization, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // String Localization::GetLanguage() | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "String GetLanguage()", asMETHODPR(Localization, GetLanguage, (), String), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "String get_language()", asMETHODPR(Localization, GetLanguage, (), String), asCALL_THISCALL);
    // String Localization::GetLanguage(int index) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "String GetLanguage(int)", asMETHODPR(Localization, GetLanguage, (int), String), asCALL_THISCALL);
    // int Localization::GetLanguageIndex() const | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "int GetLanguageIndex() const", asMETHODPR(Localization, GetLanguageIndex, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "int get_languageIndex() const", asMETHODPR(Localization, GetLanguageIndex, () const, int), asCALL_THISCALL);
    // int Localization::GetLanguageIndex(const String& language) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "int GetLanguageIndex(const String&in)", asMETHODPR(Localization, GetLanguageIndex, (const String&), int), asCALL_THISCALL);
    // int Localization::GetNumLanguages() const | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "int GetNumLanguages() const", asMETHODPR(Localization, GetNumLanguages, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "int get_numLanguages() const", asMETHODPR(Localization, GetNumLanguages, () const, int), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Localization, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "StringHash GetType() const", asMETHODPR(Localization, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "StringHash get_type() const", asMETHODPR(Localization, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "const String& GetTypeName() const", asMETHODPR(Localization, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "const String& get_typeName() const", asMETHODPR(Localization, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "bool HasEventHandlers() const", asMETHODPR(Localization, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Localization, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Localization, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "bool IsInstanceOf(StringHash) const", asMETHODPR(Localization, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // void Localization::LoadJSONFile(const String& name, const String& language=String::EMPTY) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "void LoadJSONFile(const String&in, const String&in = String::EMPTY)", asMETHODPR(Localization, LoadJSONFile, (const String&, const String&), void), asCALL_THISCALL);
    // void Localization::LoadMultipleLanguageJSON(const JSONValue& source) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "void LoadMultipleLanguageJSON(const JSONValue&in)", asMETHODPR(Localization, LoadMultipleLanguageJSON, (const JSONValue&), void), asCALL_THISCALL);
    // void Localization::LoadSingleLanguageJSON(const JSONValue& source, const String& language=String::EMPTY) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "void LoadSingleLanguageJSON(const JSONValue&in, const String&in = String::EMPTY)", asMETHODPR(Localization, LoadSingleLanguageJSON, (const JSONValue&, const String&), void), asCALL_THISCALL);
    // explicit Localization::Localization(Context* context) | File: ../Resource/Localization.h
    engine->RegisterObjectBehaviour("Localization", asBEHAVE_FACTORY, "Localization@+ f()", asFUNCTION(Localization_Localization_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Localization, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Localization", "int Refs() const", asMETHODPR(Localization, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "int get_refs() const", asMETHODPR(Localization, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Localization", asBEHAVE_RELEASE, "void f()", asMETHODPR(Localization, ReleaseRef, (), void), asCALL_THISCALL);
    // void Localization::Reset() | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "void Reset()", asMETHODPR(Localization, Reset, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void SendEvent(StringHash)", asMETHODPR(Localization, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Localization, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void SetBlockEvents(bool)", asMETHODPR(Localization, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Localization, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Localization, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Localization::SetLanguage(int index) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "void SetLanguage(int)", asMETHODPR(Localization, SetLanguage, (int), void), asCALL_THISCALL);
    // void Localization::SetLanguage(const String& language) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "void SetLanguage(const String&in)", asMETHODPR(Localization, SetLanguage, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void UnsubscribeFromAllEvents()", asMETHODPR(Localization, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Localization_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Localization, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Localization, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Localization, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Localization", "int WeakRefs() const", asMETHODPR(Localization, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "int get_weakRefs() const", asMETHODPR(Localization, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Localization, "Localization")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Localization, "Localization")
#endif
#ifdef REGISTER_MANUAL_PART_Localization
    REGISTER_MANUAL_PART_Localization(Localization, "Localization")
#endif
    RegisterSubclass<Object, Localization>(engine, "Object", "Localization");
    RegisterSubclass<RefCounted, Localization>(engine, "RefCounted", "Localization");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Log", asBEHAVE_ADDREF, "void f()", asMETHODPR(Log, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Log::Close() | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "void Close()", asMETHODPR(Log, Close, (), void), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "bool GetBlockEvents() const", asMETHODPR(Log, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "const String& GetCategory() const", asMETHODPR(Log, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "const String& get_category() const", asMETHODPR(Log, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "VariantMap& GetEventDataMap() const", asMETHODPR(Log, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "Object@+ GetEventSender() const", asMETHODPR(Log, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Log, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Log, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "const VariantMap& GetGlobalVars() const", asMETHODPR(Log, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "const VariantMap& get_globalVars() const", asMETHODPR(Log, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // String Log::GetLastMessage() const | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "String GetLastMessage() const", asMETHODPR(Log, GetLastMessage, () const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "String get_lastMessage() const", asMETHODPR(Log, GetLastMessage, () const, String), asCALL_THISCALL);
    // int Log::GetLevel() const | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "int GetLevel() const", asMETHODPR(Log, GetLevel, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "int get_level() const", asMETHODPR(Log, GetLevel, () const, int), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Log, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // bool Log::GetTimeStamp() const | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "bool GetTimeStamp() const", asMETHODPR(Log, GetTimeStamp, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "bool get_timeStamp() const", asMETHODPR(Log, GetTimeStamp, () const, bool), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "StringHash GetType() const", asMETHODPR(Log, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "StringHash get_type() const", asMETHODPR(Log, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "const String& GetTypeName() const", asMETHODPR(Log, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "const String& get_typeName() const", asMETHODPR(Log, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "bool HasEventHandlers() const", asMETHODPR(Log, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Log, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Log, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "bool IsInstanceOf(StringHash) const", asMETHODPR(Log, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Log::IsQuiet() const | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "bool IsQuiet() const", asMETHODPR(Log, IsQuiet, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "bool get_quiet() const", asMETHODPR(Log, IsQuiet, () const, bool), asCALL_THISCALL);
    // explicit Log::Log(Context* context) | File: ../IO/Log.h
    engine->RegisterObjectBehaviour("Log", asBEHAVE_FACTORY, "Log@+ f()", asFUNCTION(Log_Log_Context), asCALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Log, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // void Log::Open(const String& fileName) | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "void Open(const String&in)", asMETHODPR(Log, Open, (const String&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Log", "int Refs() const", asMETHODPR(Log, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "int get_refs() const", asMETHODPR(Log, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Log", asBEHAVE_RELEASE, "void f()", asMETHODPR(Log, ReleaseRef, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void SendEvent(StringHash)", asMETHODPR(Log, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Log, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void SetBlockEvents(bool)", asMETHODPR(Log, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Log, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Log, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Log::SetLevel(int level) | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "void SetLevel(int)", asMETHODPR(Log, SetLevel, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "void set_level(int)", asMETHODPR(Log, SetLevel, (int), void), asCALL_THISCALL);
    // void Log::SetQuiet(bool quiet) | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "void SetQuiet(bool)", asMETHODPR(Log, SetQuiet, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "void set_quiet(bool)", asMETHODPR(Log, SetQuiet, (bool), void), asCALL_THISCALL);
    // void Log::SetTimeStamp(bool enable) | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "void SetTimeStamp(bool)", asMETHODPR(Log, SetTimeStamp, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "void set_timeStamp(bool)", asMETHODPR(Log, SetTimeStamp, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void UnsubscribeFromAllEvents()", asMETHODPR(Log, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Log_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Log, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Log, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Log, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Log", "int WeakRefs() const", asMETHODPR(Log, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Log", "int get_weakRefs() const", asMETHODPR(Log, WeakRefs, () const, int), asCALL_THISCALL);
    // static void Log::Write(int level, const String& message) | File: ../IO/Log.h
    // Not registered because have @nobind mark
    // static void Log::WriteFormat(int level, const char* format,...) | File: ../IO/Log.h
    // Error: type "const char*" can not automatically bind
    // static void Log::WriteRaw(const String& message, bool error=false) | File: ../IO/Log.h
    engine->SetDefaultNamespace("Log");
    engine->RegisterGlobalFunction("void WriteRaw(const String&in, bool = false)", asFUNCTIONPR(Log::WriteRaw, (const String&, bool), void), asCALL_CDECL);
    engine->SetDefaultNamespace("");
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Log, "Log")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Log, "Log")
#endif
#ifdef REGISTER_MANUAL_PART_Log
    REGISTER_MANUAL_PART_Log(Log, "Log")
#endif
    RegisterSubclass<Object, Log>(engine, "Object", "Log");
    RegisterSubclass<RefCounted, Log>(engine, "RefCounted", "Log");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("LogicComponent", asBEHAVE_ADDREF, "void f()", asMETHODPR(LogicComponent, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void AllocateNetworkState()", asMETHODPR(LogicComponent, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void ApplyAttributes()", asMETHODPR(LogicComponent, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(LogicComponent, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "bool GetAnimationEnabled() const", asMETHODPR(LogicComponent, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "bool get_animationEnabled() const", asMETHODPR(LogicComponent, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "Variant GetAttribute(uint) const", asMETHODPR(LogicComponent, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "Variant get_attributes(uint) const", asMETHODPR(LogicComponent, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "Variant GetAttribute(const String&in) const", asMETHODPR(LogicComponent, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(LogicComponent, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(LogicComponent, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(LogicComponent, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(LogicComponent, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "Variant GetAttributeDefault(uint) const", asMETHODPR(LogicComponent, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "Variant get_attributeDefaults(uint) const", asMETHODPR(LogicComponent, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(LogicComponent, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "bool GetBlockEvents() const", asMETHODPR(LogicComponent, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "const String& GetCategory() const", asMETHODPR(LogicComponent, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "const String& get_category() const", asMETHODPR(LogicComponent, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "Component@+ GetComponent(StringHash) const", asMETHODPR(LogicComponent, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "VariantMap& GetEventDataMap() const", asMETHODPR(LogicComponent, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "Object@+ GetEventSender() const", asMETHODPR(LogicComponent, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(LogicComponent, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "const Variant& get_globalVar(StringHash) const", asMETHODPR(LogicComponent, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "const VariantMap& GetGlobalVars() const", asMETHODPR(LogicComponent, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "const VariantMap& get_globalVars() const", asMETHODPR(LogicComponent, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "uint GetID() const", asMETHODPR(LogicComponent, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "uint get_id() const", asMETHODPR(LogicComponent, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(LogicComponent, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "Node@+ GetNode() const", asMETHODPR(LogicComponent, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "Node@+ get_node() const", asMETHODPR(LogicComponent, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "uint GetNumAttributes() const", asMETHODPR(LogicComponent, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "uint get_numAttributes() const", asMETHODPR(LogicComponent, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "uint GetNumNetworkAttributes() const", asMETHODPR(LogicComponent, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(LogicComponent, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(LogicComponent, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(LogicComponent, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "Scene@+ GetScene() const", asMETHODPR(LogicComponent, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(LogicComponent, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "StringHash GetType() const", asMETHODPR(LogicComponent, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "StringHash get_type() const", asMETHODPR(LogicComponent, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "const String& GetTypeName() const", asMETHODPR(LogicComponent, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "const String& get_typeName() const", asMETHODPR(LogicComponent, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "bool HasEventHandlers() const", asMETHODPR(LogicComponent, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(LogicComponent, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(LogicComponent, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "bool IsEnabled() const", asMETHODPR(LogicComponent, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "bool get_enabled() const", asMETHODPR(LogicComponent, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "bool IsEnabledEffective() const", asMETHODPR(LogicComponent, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "bool get_enabledEffective() const", asMETHODPR(LogicComponent, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "bool IsInstanceOf(StringHash) const", asMETHODPR(LogicComponent, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "bool IsReplicated() const", asMETHODPR(LogicComponent, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "bool get_replicated() const", asMETHODPR(LogicComponent, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool IsTemporary() const", asMETHODPR(LogicComponent, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "bool get_temporary() const", asMETHODPR(LogicComponent, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool Load(Deserializer&)", asMETHODPR(LogicComponent, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "bool LoadJSON(const JSONValue&in)", asMETHODPR(LogicComponent, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "bool LoadXML(const XMLElement&in)", asMETHODPR(LogicComponent, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "void MarkNetworkUpdate()", asMETHODPR(LogicComponent, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(LogicComponent, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(LogicComponent, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(LogicComponent, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "void PrepareNetworkUpdate()", asMETHODPR(LogicComponent, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(LogicComponent, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(LogicComponent, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("LogicComponent", "int Refs() const", asMETHODPR(LogicComponent, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "int get_refs() const", asMETHODPR(LogicComponent, Refs, () const, int), asCALL_THISCALL);
    // static void Animatable::RegisterObject(Context* context) | File: ../Scene/Animatable.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("LogicComponent", asBEHAVE_RELEASE, "void f()", asMETHODPR(LogicComponent, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "void Remove()", asMETHODPR(LogicComponent, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(LogicComponent, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void RemoveInstanceDefault()", asMETHODPR(LogicComponent, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void RemoveObjectAnimation()", asMETHODPR(LogicComponent, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void ResetToDefault()", asMETHODPR(LogicComponent, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "bool Save(Serializer&) const", asMETHODPR(LogicComponent, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool SaveDefaultAttributes() const", asMETHODPR(LogicComponent, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "bool SaveJSON(JSONValue&) const", asMETHODPR(LogicComponent, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "bool SaveXML(XMLElement&) const", asMETHODPR(LogicComponent, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void SendEvent(StringHash)", asMETHODPR(LogicComponent, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(LogicComponent, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetAnimationEnabled(bool)", asMETHODPR(LogicComponent, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "void set_animationEnabled(bool)", asMETHODPR(LogicComponent, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetAnimationTime(float)", asMETHODPR(LogicComponent, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(LogicComponent, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "bool set_attributes(uint, const Variant&in)", asMETHODPR(LogicComponent, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(LogicComponent, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(LogicComponent, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(LogicComponent, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(LogicComponent, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(LogicComponent, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void SetBlockEvents(bool)", asMETHODPR(LogicComponent, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "void SetEnabled(bool)", asMETHODPR(LogicComponent, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "void set_enabled(bool)", asMETHODPR(LogicComponent, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(LogicComponent, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(LogicComponent, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetInstanceDefault(bool)", asMETHODPR(LogicComponent, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(LogicComponent, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(LogicComponent, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(LogicComponent, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(LogicComponent, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetTemporary(bool)", asMETHODPR(LogicComponent, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "void set_temporary(bool)", asMETHODPR(LogicComponent, SetTemporary, (bool), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void UnsubscribeFromAllEvents()", asMETHODPR(LogicComponent, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(LogicComponent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(LogicComponent, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(LogicComponent, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(LogicComponent, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("LogicComponent", "int WeakRefs() const", asMETHODPR(LogicComponent, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "int get_weakRefs() const", asMETHODPR(LogicComponent, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(LogicComponent, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(LogicComponent, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(LogicComponent, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(LogicComponent, "LogicComponent")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(LogicComponent, "LogicComponent")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(LogicComponent, "LogicComponent")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(LogicComponent, "LogicComponent")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(LogicComponent, "LogicComponent")
#endif
#ifdef REGISTER_MANUAL_PART_LogicComponent
    REGISTER_MANUAL_PART_LogicComponent(LogicComponent, "LogicComponent")
#endif
    RegisterSubclass<Component, LogicComponent>(engine, "Component", "LogicComponent");
    RegisterSubclass<Animatable, LogicComponent>(engine, "Animatable", "LogicComponent");
    RegisterSubclass<Serializable, LogicComponent>(engine, "Serializable", "LogicComponent");
    RegisterSubclass<Object, LogicComponent>(engine, "Object", "LogicComponent");
    RegisterSubclass<RefCounted, LogicComponent>(engine, "RefCounted", "LogicComponent");

    // Light* LightBatchQueue::light_ | File: ../Graphics/Batch.h
    // Light* can not be registered
    // BatchQueue LightBatchQueue::litBaseBatches_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("LightBatchQueue", "BatchQueue litBaseBatches", offsetof(LightBatchQueue, litBaseBatches_));
    // BatchQueue LightBatchQueue::litBatches_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("LightBatchQueue", "BatchQueue litBatches", offsetof(LightBatchQueue, litBatches_));
    // bool LightBatchQueue::negative_ | File: ../Graphics/Batch.h
    engine->RegisterObjectProperty("LightBatchQueue", "bool negative", offsetof(LightBatchQueue, negative_));
    // Texture2D* LightBatchQueue::shadowMap_ | File: ../Graphics/Batch.h
    // Texture2D* can not be registered
    // Vector<ShadowBatchQueue> LightBatchQueue::shadowSplits_ | File: ../Graphics/Batch.h
    // Error: type "Vector<ShadowBatchQueue>" can not automatically bind
    // PODVector<Light*> LightBatchQueue::vertexLights_ | File: ../Graphics/Batch.h
    // Error: type "PODVector<Light*>" can not automatically bind
    // PODVector<Batch> LightBatchQueue::volumeBatches_ | File: ../Graphics/Batch.h
    // Error: type "PODVector<Batch>" can not automatically bind
    // LightBatchQueue& LightBatchQueue::operator=(const LightBatchQueue&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<LightBatchQueue>(engine, "LightBatchQueue");
#ifdef REGISTER_MANUAL_PART_LightBatchQueue
    REGISTER_MANUAL_PART_LightBatchQueue(LightBatchQueue, "LightBatchQueue")
#endif

    // Light* LightQueryResult::light_ | File: ../Graphics/View.h
    // Light* can not be registered
    // PODVector<Drawable*> LightQueryResult::litGeometries_ | File: ../Graphics/View.h
    // Error: type "PODVector<Drawable*>" can not automatically bind
    // unsigned LightQueryResult::numSplits_ | File: ../Graphics/View.h
    engine->RegisterObjectProperty("LightQueryResult", "uint numSplits", offsetof(LightQueryResult, numSplits_));
    // Camera* LightQueryResult::shadowCameras_[MAX_LIGHT_SPLITS] | File: ../Graphics/View.h
    // Not registered because array
    // unsigned LightQueryResult::shadowCasterBegin_[MAX_LIGHT_SPLITS] | File: ../Graphics/View.h
    // Not registered because array
    // BoundingBox LightQueryResult::shadowCasterBox_[MAX_LIGHT_SPLITS] | File: ../Graphics/View.h
    // Not registered because array
    // unsigned LightQueryResult::shadowCasterEnd_[MAX_LIGHT_SPLITS] | File: ../Graphics/View.h
    // Not registered because array
    // PODVector<Drawable*> LightQueryResult::shadowCasters_ | File: ../Graphics/View.h
    // Error: type "PODVector<Drawable*>" can not automatically bind
    // float LightQueryResult::shadowFarSplits_[MAX_LIGHT_SPLITS] | File: ../Graphics/View.h
    // Not registered because array
    // float LightQueryResult::shadowNearSplits_[MAX_LIGHT_SPLITS] | File: ../Graphics/View.h
    // Not registered because array
    // LightQueryResult& LightQueryResult::operator=(const LightQueryResult&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<LightQueryResult>(engine, "LightQueryResult");
#ifdef REGISTER_MANUAL_PART_LightQueryResult
    REGISTER_MANUAL_PART_LightQueryResult(LightQueryResult, "LightQueryResult")
#endif

    // LinkedListNode* LinkedListNode::next_ | File: ../Container/LinkedList.h
    // LinkedListNode* can not be registered
    // LinkedListNode& LinkedListNode::operator=(const LinkedListNode&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<LinkedListNode>(engine, "LinkedListNode");
#ifdef REGISTER_MANUAL_PART_LinkedListNode
    REGISTER_MANUAL_PART_LinkedListNode(LinkedListNode, "LinkedListNode")
#endif

    // ListNodeBase* ListIteratorBase::ptr_ | File: ../Container/ListBase.h
    // ListNodeBase* can not be registered
    // void ListIteratorBase::GotoNext() | File: ../Container/ListBase.h
    engine->RegisterObjectMethod("ListIteratorBase", "void GotoNext()", asMETHODPR(ListIteratorBase, GotoNext, (), void), asCALL_THISCALL);
    // void ListIteratorBase::GotoPrev() | File: ../Container/ListBase.h
    engine->RegisterObjectMethod("ListIteratorBase", "void GotoPrev()", asMETHODPR(ListIteratorBase, GotoPrev, (), void), asCALL_THISCALL);
    // explicit ListIteratorBase::ListIteratorBase(ListNodeBase* ptr) | File: ../Container/ListBase.h
    // Error: type "ListNodeBase*" can not automatically bind
    // bool ListIteratorBase::operator==(const ListIteratorBase& rhs) const | File: ../Container/ListBase.h
    engine->RegisterObjectMethod("ListIteratorBase", "bool opEquals(const ListIteratorBase&in) const", asMETHODPR(ListIteratorBase, operator==, (const ListIteratorBase&) const, bool), asCALL_THISCALL);
    // ListIteratorBase& ListIteratorBase::operator=(const ListIteratorBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ListIteratorBase>(engine, "ListIteratorBase");
#ifdef REGISTER_MANUAL_PART_ListIteratorBase
    REGISTER_MANUAL_PART_ListIteratorBase(ListIteratorBase, "ListIteratorBase")
#endif

    // ListNodeBase* ListNodeBase::next_ | File: ../Container/ListBase.h
    // ListNodeBase* can not be registered
    // ListNodeBase* ListNodeBase::prev_ | File: ../Container/ListBase.h
    // ListNodeBase* can not be registered
    // ListNodeBase& ListNodeBase::operator=(const ListNodeBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ListNodeBase>(engine, "ListNodeBase");
#ifdef REGISTER_MANUAL_PART_ListNodeBase
    REGISTER_MANUAL_PART_ListNodeBase(ListNodeBase, "ListNodeBase")
#endif

}

}
