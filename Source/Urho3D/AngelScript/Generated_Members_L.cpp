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
static void Light_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Light* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void LineEdit_AddTags_StringVector(LineEdit* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
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

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void LineEdit_SetTags_StringVector(LineEdit* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void LineEdit_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(LineEdit* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void ListView_AddTags_StringVector(ListView* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
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
static void ListView_SetSelections_PODVectorunsigned(ListView* ptr, CScriptArray* indices_conv)
{
    PODVector<unsigned> indices = ArrayToPODVector<unsigned>(indices_conv);
    ptr->SetSelections(indices);
}

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void ListView_SetTags_StringVector(ListView* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ListView_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ListView* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Localization::Localization(Context* context) | File: ../Resource/Localization.h
static Localization* Localization_Localization_Context()
{
    return new Localization(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Localization_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Localization* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Log::Log(Context* context) | File: ../IO/Log.h
static Log* Log_Log_Context()
{
    return new Log(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Log_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Log* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void LogicComponent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(LogicComponent* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

void ASRegisterGenerated_Members_L(asIScriptEngine* engine)
{
    // void Drawable::AddLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void AddLight(Light@+)", AS_METHODPR(Light, AddLight, (Light*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Light", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Light, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Drawable::AddVertexLight(Light* light) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void AddVertexLight(Light@+)", AS_METHODPR(Light, AddVertexLight, (Light*), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void AllocateNetworkState()", AS_METHODPR(Light, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void ApplyAttributes()", AS_METHODPR(Light, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // void Light::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(Light, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // virtual bool Drawable::DrawOcclusion(OcclusionBuffer* buffer) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool DrawOcclusion(OcclusionBuffer@+)", AS_METHODPR(Light, DrawOcclusion, (OcclusionBuffer*), bool), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "bool GetAnimationEnabled() const", AS_METHODPR(Light, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_animationEnabled() const", AS_METHODPR(Light, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // float Light::GetAspectRatio() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetAspectRatio() const", AS_METHODPR(Light, GetAspectRatio, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_aspectRatio() const", AS_METHODPR(Light, GetAspectRatio, () const, float), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "Variant GetAttribute(uint) const", AS_METHODPR(Light, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Variant get_attributes(uint) const", AS_METHODPR(Light, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "Variant GetAttribute(const String&in) const", AS_METHODPR(Light, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Light, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Light, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Light, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Light, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Light, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Light, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Light, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const Vector<SourceBatch>& Drawable::GetBatches() const | File: ../Graphics/Drawable.h
    // Error: type "const Vector<SourceBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "bool GetBlockEvents() const", AS_METHODPR(Light, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetBoundingBox() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "const BoundingBox& GetBoundingBox() const", AS_METHODPR(Light, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const BoundingBox& get_boundingBox() const", AS_METHODPR(Light, GetBoundingBox, () const, const BoundingBox&), AS_CALL_THISCALL);
    // float Light::GetBrightness() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetBrightness() const", AS_METHODPR(Light, GetBrightness, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_brightness() const", AS_METHODPR(Light, GetBrightness, () const, float), AS_CALL_THISCALL);
    // bool Drawable::GetCastShadows() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool GetCastShadows() const", AS_METHODPR(Light, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_castShadows() const", AS_METHODPR(Light, GetCastShadows, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "const String& GetCategory() const", AS_METHODPR(Light, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const String& get_category() const", AS_METHODPR(Light, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // const Color& Light::GetColor() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "const Color& GetColor() const", AS_METHODPR(Light, GetColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const Color& get_color() const", AS_METHODPR(Light, GetColor, () const, const Color&), AS_CALL_THISCALL);
    // Color Light::GetColorFromTemperature() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "Color GetColorFromTemperature() const", AS_METHODPR(Light, GetColorFromTemperature, () const, Color), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Color get_colorFromTemperature() const", AS_METHODPR(Light, GetColorFromTemperature, () const, Color), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "Component@+ GetComponent(StringHash) const", AS_METHODPR(Light, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("Light", "float GetDistance() const", AS_METHODPR(Light, GetDistance, () const, float), AS_CALL_THISCALL);
    // unsigned char Drawable::GetDrawableFlags() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint8 GetDrawableFlags() const", AS_METHODPR(Light, GetDrawableFlags, () const, unsigned char), AS_CALL_THISCALL);
    // float Drawable::GetDrawDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetDrawDistance() const", AS_METHODPR(Light, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_drawDistance() const", AS_METHODPR(Light, GetDrawDistance, () const, float), AS_CALL_THISCALL);
    // Color Light::GetEffectiveColor() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "Color GetEffectiveColor() const", AS_METHODPR(Light, GetEffectiveColor, () const, Color), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Color get_effectiveColor() const", AS_METHODPR(Light, GetEffectiveColor, () const, Color), AS_CALL_THISCALL);
    // float Light::GetEffectiveSpecularIntensity() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetEffectiveSpecularIntensity() const", AS_METHODPR(Light, GetEffectiveSpecularIntensity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_effectiveSpecularIntensity() const", AS_METHODPR(Light, GetEffectiveSpecularIntensity, () const, float), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "VariantMap& GetEventDataMap() const", AS_METHODPR(Light, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "Object@+ GetEventSender() const", AS_METHODPR(Light, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // float Light::GetFadeDistance() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetFadeDistance() const", AS_METHODPR(Light, GetFadeDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_fadeDistance() const", AS_METHODPR(Light, GetFadeDistance, () const, float), AS_CALL_THISCALL);
    // Light* Drawable::GetFirstLight() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "Light@+ GetFirstLight() const", AS_METHODPR(Light, GetFirstLight, () const, Light*), AS_CALL_THISCALL);
    // float Light::GetFov() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetFov() const", AS_METHODPR(Light, GetFov, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_fov() const", AS_METHODPR(Light, GetFov, () const, float), AS_CALL_THISCALL);
    // Frustum Light::GetFrustum() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "Frustum GetFrustum() const", AS_METHODPR(Light, GetFrustum, () const, Frustum), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Frustum get_frustum() const", AS_METHODPR(Light, GetFrustum, () const, Frustum), AS_CALL_THISCALL);
    // static Matrix3x4 Light::GetFullscreenQuadTransform(Camera* camera) | File: ../Graphics/Light.h
    engine->SetDefaultNamespace("Light");
    engine->RegisterGlobalFunction("Matrix3x4 GetFullscreenQuadTransform(Camera@+)", AS_FUNCTIONPR(Light::GetFullscreenQuadTransform, (Camera*), Matrix3x4), AS_CALL_CDECL);
    engine->SetDefaultNamespace("");
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Light, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Light, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Light, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const VariantMap& get_globalVars() const", AS_METHODPR(Light, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "uint GetID() const", AS_METHODPR(Light, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_id() const", AS_METHODPR(Light, GetID, () const, unsigned), AS_CALL_THISCALL);
    // float Light::GetIntensityDivisor(float attenuation=1.0f) const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetIntensityDivisor(float = 1.0f) const", AS_METHODPR(Light, GetIntensityDivisor, (float) const, float), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Light, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // float Light::GetLength() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetLength() const", AS_METHODPR(Light, GetLength, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_length() const", AS_METHODPR(Light, GetLength, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetLightMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint GetLightMask() const", AS_METHODPR(Light, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_lightMask() const", AS_METHODPR(Light, GetLightMask, () const, unsigned), AS_CALL_THISCALL);
    // LightBatchQueue* Light::GetLightQueue() const | File: ../Graphics/Light.h
    // Error: type "LightBatchQueue*" can not automatically bind
    // const PODVector<Light*>& Drawable::GetLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "Array<Light@>@ GetLights() const", AS_FUNCTION_OBJFIRST(Light_GetLights_void), AS_CALL_CDECL_OBJFIRST);
    // LightType Light::GetLightType() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "LightType GetLightType() const", AS_METHODPR(Light, GetLightType, () const, LightType), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "LightType get_lightType() const", AS_METHODPR(Light, GetLightType, () const, LightType), AS_CALL_THISCALL);
    // float Drawable::GetLodBias() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetLodBias() const", AS_METHODPR(Light, GetLodBias, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_lodBias() const", AS_METHODPR(Light, GetLodBias, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetLodDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetLodDistance() const", AS_METHODPR(Light, GetLodDistance, () const, float), AS_CALL_THISCALL);
    // virtual Geometry* Drawable::GetLodGeometry(unsigned batchIndex, unsigned level) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "Geometry@+ GetLodGeometry(uint, uint)", AS_METHODPR(Light, GetLodGeometry, (unsigned, unsigned), Geometry*), AS_CALL_THISCALL);
    // unsigned Drawable::GetMaxLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint GetMaxLights() const", AS_METHODPR(Light, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_maxLights() const", AS_METHODPR(Light, GetMaxLights, () const, unsigned), AS_CALL_THISCALL);
    // float Drawable::GetMaxZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetMaxZ() const", AS_METHODPR(Light, GetMaxZ, () const, float), AS_CALL_THISCALL);
    // float Drawable::GetMinZ() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetMinZ() const", AS_METHODPR(Light, GetMinZ, () const, float), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "Node@+ GetNode() const", AS_METHODPR(Light, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Node@+ get_node() const", AS_METHODPR(Light, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "uint GetNumAttributes() const", AS_METHODPR(Light, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_numAttributes() const", AS_METHODPR(Light, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "uint GetNumNetworkAttributes() const", AS_METHODPR(Light, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // virtual unsigned Drawable::GetNumOccluderTriangles() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint GetNumOccluderTriangles()", AS_METHODPR(Light, GetNumOccluderTriangles, (), unsigned), AS_CALL_THISCALL);
    // int Light::GetNumShadowSplits() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "int GetNumShadowSplits() const", AS_METHODPR(Light, GetNumShadowSplits, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "int get_numShadowSplits() const", AS_METHODPR(Light, GetNumShadowSplits, () const, int), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Light, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Light, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Light, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Octant* Drawable::GetOctant() const | File: ../Graphics/Drawable.h
    // Error: type "Octant" can not automatically bind bacause have @nobind mark
    // bool Light::GetPerVertex() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "bool GetPerVertex() const", AS_METHODPR(Light, GetPerVertex, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_perVertex() const", AS_METHODPR(Light, GetPerVertex, () const, bool), AS_CALL_THISCALL);
    // float Light::GetRadius() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetRadius() const", AS_METHODPR(Light, GetRadius, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_radius() const", AS_METHODPR(Light, GetRadius, () const, float), AS_CALL_THISCALL);
    // Texture* Light::GetRampTexture() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "Texture@+ GetRampTexture() const", AS_METHODPR(Light, GetRampTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Texture@+ get_rampTexture() const", AS_METHODPR(Light, GetRampTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef Light::GetRampTextureAttr() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "ResourceRef GetRampTextureAttr() const", AS_METHODPR(Light, GetRampTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float Light::GetRange() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetRange() const", AS_METHODPR(Light, GetRange, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_range() const", AS_METHODPR(Light, GetRange, () const, float), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "Scene@+ GetScene() const", AS_METHODPR(Light, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // const BiasParameters& Light::GetShadowBias() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "const BiasParameters& GetShadowBias() const", AS_METHODPR(Light, GetShadowBias, () const, const BiasParameters&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const BiasParameters& get_shadowBias() const", AS_METHODPR(Light, GetShadowBias, () const, const BiasParameters&), AS_CALL_THISCALL);
    // const CascadeParameters& Light::GetShadowCascade() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "const CascadeParameters& GetShadowCascade() const", AS_METHODPR(Light, GetShadowCascade, () const, const CascadeParameters&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const CascadeParameters& get_shadowCascade() const", AS_METHODPR(Light, GetShadowCascade, () const, const CascadeParameters&), AS_CALL_THISCALL);
    // float Drawable::GetShadowDistance() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetShadowDistance() const", AS_METHODPR(Light, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowDistance() const", AS_METHODPR(Light, GetShadowDistance, () const, float), AS_CALL_THISCALL);
    // float Light::GetShadowFadeDistance() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetShadowFadeDistance() const", AS_METHODPR(Light, GetShadowFadeDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowFadeDistance() const", AS_METHODPR(Light, GetShadowFadeDistance, () const, float), AS_CALL_THISCALL);
    // const FocusParameters& Light::GetShadowFocus() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "const FocusParameters& GetShadowFocus() const", AS_METHODPR(Light, GetShadowFocus, () const, const FocusParameters&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const FocusParameters& get_shadowFocus() const", AS_METHODPR(Light, GetShadowFocus, () const, const FocusParameters&), AS_CALL_THISCALL);
    // float Light::GetShadowIntensity() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetShadowIntensity() const", AS_METHODPR(Light, GetShadowIntensity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowIntensity() const", AS_METHODPR(Light, GetShadowIntensity, () const, float), AS_CALL_THISCALL);
    // unsigned Drawable::GetShadowMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint GetShadowMask() const", AS_METHODPR(Light, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_shadowMask() const", AS_METHODPR(Light, GetShadowMask, () const, unsigned), AS_CALL_THISCALL);
    // float Light::GetShadowMaxExtrusion() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetShadowMaxExtrusion() const", AS_METHODPR(Light, GetShadowMaxExtrusion, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowMaxExtrusion() const", AS_METHODPR(Light, GetShadowMaxExtrusion, () const, float), AS_CALL_THISCALL);
    // float Light::GetShadowNearFarRatio() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetShadowNearFarRatio() const", AS_METHODPR(Light, GetShadowNearFarRatio, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowNearFarRatio() const", AS_METHODPR(Light, GetShadowNearFarRatio, () const, float), AS_CALL_THISCALL);
    // float Light::GetShadowResolution() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetShadowResolution() const", AS_METHODPR(Light, GetShadowResolution, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_shadowResolution() const", AS_METHODPR(Light, GetShadowResolution, () const, float), AS_CALL_THISCALL);
    // Texture* Light::GetShapeTexture() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "Texture@+ GetShapeTexture() const", AS_METHODPR(Light, GetShapeTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Texture@+ get_shapeTexture() const", AS_METHODPR(Light, GetShapeTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef Light::GetShapeTextureAttr() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "ResourceRef GetShapeTextureAttr() const", AS_METHODPR(Light, GetShapeTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float Drawable::GetSortValue() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "float GetSortValue() const", AS_METHODPR(Light, GetSortValue, () const, float), AS_CALL_THISCALL);
    // float Light::GetSpecularIntensity() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetSpecularIntensity() const", AS_METHODPR(Light, GetSpecularIntensity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_specularIntensity() const", AS_METHODPR(Light, GetSpecularIntensity, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Light, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // float Light::GetTemperature() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "float GetTemperature() const", AS_METHODPR(Light, GetTemperature, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "float get_temperature() const", AS_METHODPR(Light, GetTemperature, () const, float), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "StringHash GetType() const", AS_METHODPR(Light, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "StringHash get_type() const", AS_METHODPR(Light, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "const String& GetTypeName() const", AS_METHODPR(Light, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const String& get_typeName() const", AS_METHODPR(Light, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // virtual UpdateGeometryType Drawable::GetUpdateGeometryType() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "UpdateGeometryType GetUpdateGeometryType()", AS_METHODPR(Light, GetUpdateGeometryType, (), UpdateGeometryType), AS_CALL_THISCALL);
    // bool Light::GetUsePhysicalValues() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "bool GetUsePhysicalValues() const", AS_METHODPR(Light, GetUsePhysicalValues, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_usePhysicalValues() const", AS_METHODPR(Light, GetUsePhysicalValues, () const, bool), AS_CALL_THISCALL);
    // const PODVector<Light*>& Drawable::GetVertexLights() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "Array<Light@>@ GetVertexLights() const", AS_FUNCTION_OBJFIRST(Light_GetVertexLights_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned Drawable::GetViewMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint GetViewMask() const", AS_METHODPR(Light, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_viewMask() const", AS_METHODPR(Light, GetViewMask, () const, unsigned), AS_CALL_THISCALL);
    // Frustum Light::GetViewSpaceFrustum(const Matrix3x4& view) const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "Frustum GetViewSpaceFrustum(const Matrix3x4&in) const", AS_METHODPR(Light, GetViewSpaceFrustum, (const Matrix3x4&) const, Frustum), AS_CALL_THISCALL);
    // const Matrix3x4& Light::GetVolumeTransform(Camera* camera) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "const Matrix3x4& GetVolumeTransform(Camera@+)", AS_METHODPR(Light, GetVolumeTransform, (Camera*), const Matrix3x4&), AS_CALL_THISCALL);
    // const BoundingBox& Drawable::GetWorldBoundingBox() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "const BoundingBox& GetWorldBoundingBox()", AS_METHODPR(Light, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "const BoundingBox& get_worldBoundingBox()", AS_METHODPR(Light, GetWorldBoundingBox, (), const BoundingBox&), AS_CALL_THISCALL);
    // Zone* Drawable::GetZone() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "Zone@+ GetZone() const", AS_METHODPR(Light, GetZone, () const, Zone*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "Zone@+ get_zone() const", AS_METHODPR(Light, GetZone, () const, Zone*), AS_CALL_THISCALL);
    // unsigned Drawable::GetZoneMask() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "uint GetZoneMask() const", AS_METHODPR(Light, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "uint get_zoneMask() const", AS_METHODPR(Light, GetZoneMask, () const, unsigned), AS_CALL_THISCALL);
    // bool Drawable::HasBasePass(unsigned batchIndex) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool HasBasePass(uint) const", AS_METHODPR(Light, HasBasePass, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "bool HasEventHandlers() const", AS_METHODPR(Light, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Light, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Light, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "bool IsEnabled() const", AS_METHODPR(Light, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_enabled() const", AS_METHODPR(Light, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "bool IsEnabledEffective() const", AS_METHODPR(Light, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_enabledEffective() const", AS_METHODPR(Light, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Light, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Drawable::IsInView() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool IsInView() const", AS_METHODPR(Light, IsInView, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_inView() const", AS_METHODPR(Light, IsInView, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(Camera* camera) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool IsInView(Camera@+) const", AS_METHODPR(Light, IsInView, (Camera*) const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsInView(const FrameInfo& frame, bool anyCamera=false) const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool IsInView(const FrameInfo&in, bool = false) const", AS_METHODPR(Light, IsInView, (const FrameInfo&, bool) const, bool), AS_CALL_THISCALL);
    // bool Light::IsNegative() const | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "bool IsNegative() const", AS_METHODPR(Light, IsNegative, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_negative() const", AS_METHODPR(Light, IsNegative, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccludee() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool IsOccludee() const", AS_METHODPR(Light, IsOccludee, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_occludee() const", AS_METHODPR(Light, IsOccludee, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsOccluder() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool IsOccluder() const", AS_METHODPR(Light, IsOccluder, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_occluder() const", AS_METHODPR(Light, IsOccluder, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "bool IsReplicated() const", AS_METHODPR(Light, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_replicated() const", AS_METHODPR(Light, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool IsTemporary() const", AS_METHODPR(Light, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool get_temporary() const", AS_METHODPR(Light, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool Drawable::IsZoneDirty() const | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "bool IsZoneDirty() const", AS_METHODPR(Light, IsZoneDirty, () const, bool), AS_CALL_THISCALL);
    // explicit Light::Light(Context* context) | File: ../Graphics/Light.h
    engine->RegisterObjectBehaviour("Light", asBEHAVE_FACTORY, "Light@+ f()", AS_FUNCTION(Light_Light_Context), AS_CALL_CDECL);
    // void Drawable::LimitLights() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void LimitLights()", AS_METHODPR(Light, LimitLights, (), void), AS_CALL_THISCALL);
    // void Drawable::LimitVertexLights(bool removeConvertedLights) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void LimitVertexLights(bool)", AS_METHODPR(Light, LimitVertexLights, (bool), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool Load(Deserializer&)", AS_METHODPR(Light, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Light, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Light, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Drawable::MarkForUpdate() | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void MarkForUpdate()", AS_METHODPR(Light, MarkForUpdate, (), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void MarkInView(const FrameInfo&in)", AS_METHODPR(Light, MarkInView, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Drawable::MarkInView(unsigned frameNumber) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void MarkInView(uint)", AS_METHODPR(Light, MarkInView, (unsigned), void), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "void MarkNetworkUpdate()", AS_METHODPR(Light, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Light, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Light, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Light, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Drawable::OnSetEnabled() override | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void OnSetEnabled()", AS_METHODPR(Light, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "void PrepareNetworkUpdate()", AS_METHODPR(Light, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void Light::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override | File: ../Graphics/Light.h
    // Error: type "RayOctreeQuery" can not automatically bind bacause have @nobind mark
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Light, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Light, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Light", "int Refs() const", AS_METHODPR(Light, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "int get_refs() const", AS_METHODPR(Light, Refs, () const, int), AS_CALL_THISCALL);
    // static void Light::RegisterObject(Context* context) | File: ../Graphics/Light.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Light", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Light, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "void Remove()", AS_METHODPR(Light, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Light, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void RemoveInstanceDefault()", AS_METHODPR(Light, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void RemoveObjectAnimation()", AS_METHODPR(Light, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void ResetToDefault()", AS_METHODPR(Light, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "bool Save(Serializer&) const", AS_METHODPR(Light, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool SaveDefaultAttributes() const", AS_METHODPR(Light, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Light, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "bool SaveXML(XMLElement&) const", AS_METHODPR(Light, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void SendEvent(StringHash)", AS_METHODPR(Light, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Light, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetAnimationEnabled(bool)", AS_METHODPR(Light, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_animationEnabled(bool)", AS_METHODPR(Light, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetAnimationTime(float)", AS_METHODPR(Light, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // void Light::SetAspectRatio(float aspectRatio) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetAspectRatio(float)", AS_METHODPR(Light, SetAspectRatio, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_aspectRatio(float)", AS_METHODPR(Light, SetAspectRatio, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Light, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Light, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Light, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Light, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Light, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Light, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Light, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Drawable::SetBasePass(unsigned batchIndex) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetBasePass(uint)", AS_METHODPR(Light, SetBasePass, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void SetBlockEvents(bool)", AS_METHODPR(Light, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Light::SetBrightness(float brightness) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetBrightness(float)", AS_METHODPR(Light, SetBrightness, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_brightness(float)", AS_METHODPR(Light, SetBrightness, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetCastShadows(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetCastShadows(bool)", AS_METHODPR(Light, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_castShadows(bool)", AS_METHODPR(Light, SetCastShadows, (bool), void), AS_CALL_THISCALL);
    // void Light::SetColor(const Color& color) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetColor(const Color&in)", AS_METHODPR(Light, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_color(const Color&in)", AS_METHODPR(Light, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void Drawable::SetDrawDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetDrawDistance(float)", AS_METHODPR(Light, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_drawDistance(float)", AS_METHODPR(Light, SetDrawDistance, (float), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("Light", "void SetEnabled(bool)", AS_METHODPR(Light, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_enabled(bool)", AS_METHODPR(Light, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Light::SetFadeDistance(float distance) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetFadeDistance(float)", AS_METHODPR(Light, SetFadeDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_fadeDistance(float)", AS_METHODPR(Light, SetFadeDistance, (float), void), AS_CALL_THISCALL);
    // void Light::SetFov(float fov) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetFov(float)", AS_METHODPR(Light, SetFov, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_fov(float)", AS_METHODPR(Light, SetFov, (float), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Light, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Light, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void SetInstanceDefault(bool)", AS_METHODPR(Light, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Light::SetIntensitySortValue(float distance) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetIntensitySortValue(float)", AS_METHODPR(Light, SetIntensitySortValue, (float), void), AS_CALL_THISCALL);
    // void Light::SetIntensitySortValue(const BoundingBox& box) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetIntensitySortValue(const BoundingBox&in)", AS_METHODPR(Light, SetIntensitySortValue, (const BoundingBox&), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Light, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Light::SetLength(float length) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetLength(float)", AS_METHODPR(Light, SetLength, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_length(float)", AS_METHODPR(Light, SetLength, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetLightMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetLightMask(uint)", AS_METHODPR(Light, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_lightMask(uint)", AS_METHODPR(Light, SetLightMask, (unsigned), void), AS_CALL_THISCALL);
    // void Light::SetLightQueue(LightBatchQueue* queue) | File: ../Graphics/Light.h
    // Error: type "LightBatchQueue*" can not automatically bind
    // void Light::SetLightType(LightType type) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetLightType(LightType)", AS_METHODPR(Light, SetLightType, (LightType), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_lightType(LightType)", AS_METHODPR(Light, SetLightType, (LightType), void), AS_CALL_THISCALL);
    // void Drawable::SetLodBias(float bias) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetLodBias(float)", AS_METHODPR(Light, SetLodBias, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_lodBias(float)", AS_METHODPR(Light, SetLodBias, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetMaxLights(unsigned num) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetMaxLights(uint)", AS_METHODPR(Light, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_maxLights(uint)", AS_METHODPR(Light, SetMaxLights, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetMinMaxZ(float minZ, float maxZ) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetMinMaxZ(float, float)", AS_METHODPR(Light, SetMinMaxZ, (float, float), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Light, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Light, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Light", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Light, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetOccludee(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetOccludee(bool)", AS_METHODPR(Light, SetOccludee, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_occludee(bool)", AS_METHODPR(Light, SetOccludee, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetOccluder(bool enable) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetOccluder(bool)", AS_METHODPR(Light, SetOccluder, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_occluder(bool)", AS_METHODPR(Light, SetOccluder, (bool), void), AS_CALL_THISCALL);
    // void Light::SetPerVertex(bool enable) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetPerVertex(bool)", AS_METHODPR(Light, SetPerVertex, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_perVertex(bool)", AS_METHODPR(Light, SetPerVertex, (bool), void), AS_CALL_THISCALL);
    // void Light::SetRadius(float radius) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetRadius(float)", AS_METHODPR(Light, SetRadius, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_radius(float)", AS_METHODPR(Light, SetRadius, (float), void), AS_CALL_THISCALL);
    // void Light::SetRampTexture(Texture* texture) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetRampTexture(Texture@+)", AS_METHODPR(Light, SetRampTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_rampTexture(Texture@+)", AS_METHODPR(Light, SetRampTexture, (Texture*), void), AS_CALL_THISCALL);
    // void Light::SetRampTextureAttr(const ResourceRef& value) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetRampTextureAttr(const ResourceRef&in)", AS_METHODPR(Light, SetRampTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Light::SetRange(float range) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetRange(float)", AS_METHODPR(Light, SetRange, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_range(float)", AS_METHODPR(Light, SetRange, (float), void), AS_CALL_THISCALL);
    // void Light::SetShadowBias(const BiasParameters& parameters) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowBias(const BiasParameters&in)", AS_METHODPR(Light, SetShadowBias, (const BiasParameters&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowBias(const BiasParameters&in)", AS_METHODPR(Light, SetShadowBias, (const BiasParameters&), void), AS_CALL_THISCALL);
    // void Light::SetShadowCascade(const CascadeParameters& parameters) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowCascade(const CascadeParameters&in)", AS_METHODPR(Light, SetShadowCascade, (const CascadeParameters&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowCascade(const CascadeParameters&in)", AS_METHODPR(Light, SetShadowCascade, (const CascadeParameters&), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowDistance(float distance) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetShadowDistance(float)", AS_METHODPR(Light, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowDistance(float)", AS_METHODPR(Light, SetShadowDistance, (float), void), AS_CALL_THISCALL);
    // void Light::SetShadowFadeDistance(float distance) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowFadeDistance(float)", AS_METHODPR(Light, SetShadowFadeDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowFadeDistance(float)", AS_METHODPR(Light, SetShadowFadeDistance, (float), void), AS_CALL_THISCALL);
    // void Light::SetShadowFocus(const FocusParameters& parameters) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowFocus(const FocusParameters&in)", AS_METHODPR(Light, SetShadowFocus, (const FocusParameters&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowFocus(const FocusParameters&in)", AS_METHODPR(Light, SetShadowFocus, (const FocusParameters&), void), AS_CALL_THISCALL);
    // void Light::SetShadowIntensity(float intensity) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowIntensity(float)", AS_METHODPR(Light, SetShadowIntensity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowIntensity(float)", AS_METHODPR(Light, SetShadowIntensity, (float), void), AS_CALL_THISCALL);
    // void Drawable::SetShadowMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetShadowMask(uint)", AS_METHODPR(Light, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowMask(uint)", AS_METHODPR(Light, SetShadowMask, (unsigned), void), AS_CALL_THISCALL);
    // void Light::SetShadowMaxExtrusion(float extrusion) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowMaxExtrusion(float)", AS_METHODPR(Light, SetShadowMaxExtrusion, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowMaxExtrusion(float)", AS_METHODPR(Light, SetShadowMaxExtrusion, (float), void), AS_CALL_THISCALL);
    // void Light::SetShadowNearFarRatio(float nearFarRatio) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowNearFarRatio(float)", AS_METHODPR(Light, SetShadowNearFarRatio, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowNearFarRatio(float)", AS_METHODPR(Light, SetShadowNearFarRatio, (float), void), AS_CALL_THISCALL);
    // void Light::SetShadowResolution(float resolution) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShadowResolution(float)", AS_METHODPR(Light, SetShadowResolution, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shadowResolution(float)", AS_METHODPR(Light, SetShadowResolution, (float), void), AS_CALL_THISCALL);
    // void Light::SetShapeTexture(Texture* texture) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShapeTexture(Texture@+)", AS_METHODPR(Light, SetShapeTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_shapeTexture(Texture@+)", AS_METHODPR(Light, SetShapeTexture, (Texture*), void), AS_CALL_THISCALL);
    // void Light::SetShapeTextureAttr(const ResourceRef& value) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetShapeTextureAttr(const ResourceRef&in)", AS_METHODPR(Light, SetShapeTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Drawable::SetSortValue(float value) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetSortValue(float)", AS_METHODPR(Light, SetSortValue, (float), void), AS_CALL_THISCALL);
    // void Light::SetSpecularIntensity(float intensity) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetSpecularIntensity(float)", AS_METHODPR(Light, SetSpecularIntensity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_specularIntensity(float)", AS_METHODPR(Light, SetSpecularIntensity, (float), void), AS_CALL_THISCALL);
    // void Light::SetTemperature(float temperature) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetTemperature(float)", AS_METHODPR(Light, SetTemperature, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_temperature(float)", AS_METHODPR(Light, SetTemperature, (float), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void SetTemporary(bool)", AS_METHODPR(Light, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_temporary(bool)", AS_METHODPR(Light, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Light::SetUsePhysicalValues(bool enable) | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void SetUsePhysicalValues(bool)", AS_METHODPR(Light, SetUsePhysicalValues, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_usePhysicalValues(bool)", AS_METHODPR(Light, SetUsePhysicalValues, (bool), void), AS_CALL_THISCALL);
    // void Drawable::SetViewMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetViewMask(uint)", AS_METHODPR(Light, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_viewMask(uint)", AS_METHODPR(Light, SetViewMask, (unsigned), void), AS_CALL_THISCALL);
    // void Drawable::SetZone(Zone* zone, bool temporary=false) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetZone(Zone@+, bool = false)", AS_METHODPR(Light, SetZone, (Zone*, bool), void), AS_CALL_THISCALL);
    // void Drawable::SetZoneMask(unsigned mask) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void SetZoneMask(uint)", AS_METHODPR(Light, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "void set_zoneMask(uint)", AS_METHODPR(Light, SetZoneMask, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void UnsubscribeFromAllEvents()", AS_METHODPR(Light, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Light_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Light, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Light, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Light", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Light, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void Drawable::Update(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void Update(const FrameInfo&in)", AS_METHODPR(Light, Update, (const FrameInfo&), void), AS_CALL_THISCALL);
    // void Light::UpdateBatches(const FrameInfo& frame) override | File: ../Graphics/Light.h
    engine->RegisterObjectMethod("Light", "void UpdateBatches(const FrameInfo&in)", AS_METHODPR(Light, UpdateBatches, (const FrameInfo&), void), AS_CALL_THISCALL);
    // virtual void Drawable::UpdateGeometry(const FrameInfo& frame) | File: ../Graphics/Drawable.h
    engine->RegisterObjectMethod("Light", "void UpdateGeometry(const FrameInfo&in)", AS_METHODPR(Light, UpdateGeometry, (const FrameInfo&), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Light", "int WeakRefs() const", AS_METHODPR(Light, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Light", "int get_weakRefs() const", AS_METHODPR(Light, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Light, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Light, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Light", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Light, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("LineEdit", "void AddChild(UIElement@+)", AS_METHODPR(LineEdit, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("LineEdit", asBEHAVE_ADDREF, "void f()", AS_METHODPR(LineEdit, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void AddTag(const String&in)", AS_METHODPR(LineEdit, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(LineEdit, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(LineEdit_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void AdjustScissor(IntRect&)", AS_METHODPR(LineEdit, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void AllocateNetworkState()", AS_METHODPR(LineEdit, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void LineEdit::ApplyAttributes() override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void ApplyAttributes()", AS_METHODPR(LineEdit, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void BringToFront()", AS_METHODPR(LineEdit, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(LineEdit, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void DisableLayoutUpdate()", AS_METHODPR(LineEdit, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(LineEdit, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void EnableLayoutUpdate()", AS_METHODPR(LineEdit, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(LineEdit, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "uint FindChild(UIElement@+) const", AS_METHODPR(LineEdit, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "bool GetAnimationEnabled() const", AS_METHODPR(LineEdit, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_animationEnabled() const", AS_METHODPR(LineEdit, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const String& GetAppliedStyle() const", AS_METHODPR(LineEdit, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const String& get_style() const", AS_METHODPR(LineEdit, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "Variant GetAttribute(uint) const", AS_METHODPR(LineEdit, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "Variant get_attributes(uint) const", AS_METHODPR(LineEdit, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "Variant GetAttribute(const String&in) const", AS_METHODPR(LineEdit, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(LineEdit, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(LineEdit, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(LineEdit, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(LineEdit, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "Variant GetAttributeDefault(uint) const", AS_METHODPR(LineEdit, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "Variant get_attributeDefaults(uint) const", AS_METHODPR(LineEdit, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(LineEdit, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/BorderImage.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "BlendMode GetBlendMode() const", AS_METHODPR(LineEdit, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "BlendMode get_blendMode() const", AS_METHODPR(LineEdit, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "bool GetBlockEvents() const", AS_METHODPR(LineEdit, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "const IntRect& GetBorder() const", AS_METHODPR(LineEdit, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntRect& get_border() const", AS_METHODPR(LineEdit, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool GetBringToBack() const", AS_METHODPR(LineEdit, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_bringToBack() const", AS_METHODPR(LineEdit, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool GetBringToFront() const", AS_METHODPR(LineEdit, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_bringToFront() const", AS_METHODPR(LineEdit, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "const String& GetCategory() const", AS_METHODPR(LineEdit, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const String& get_category() const", AS_METHODPR(LineEdit, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ GetChild(uint) const", AS_METHODPR(LineEdit, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ get_children(uint) const", AS_METHODPR(LineEdit, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(LineEdit, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(LineEdit, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetChildOffset() const", AS_METHODPR(LineEdit, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_childOffset() const", AS_METHODPR(LineEdit, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(LineEdit_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(LineEdit_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(LineEdit_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntRect& GetClipBorder() const", AS_METHODPR(LineEdit, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntRect& get_clipBorder() const", AS_METHODPR(LineEdit, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool GetClipChildren() const", AS_METHODPR(LineEdit, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_clipChildren() const", AS_METHODPR(LineEdit, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Color& GetColor(Corner) const", AS_METHODPR(LineEdit, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const Color& get_colors(Corner) const", AS_METHODPR(LineEdit, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Color& GetColorAttr() const", AS_METHODPR(LineEdit, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "IntRect GetCombinedScreenRect()", AS_METHODPR(LineEdit, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "IntRect get_combinedScreenRect()", AS_METHODPR(LineEdit, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // BorderImage* LineEdit::GetCursor() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "BorderImage@+ GetCursor() const", AS_METHODPR(LineEdit, GetCursor, () const, BorderImage*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "BorderImage@+ get_cursor() const", AS_METHODPR(LineEdit, GetCursor, () const, BorderImage*), AS_CALL_THISCALL);
    // float LineEdit::GetCursorBlinkRate() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "float GetCursorBlinkRate() const", AS_METHODPR(LineEdit, GetCursorBlinkRate, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "float get_cursorBlinkRate() const", AS_METHODPR(LineEdit, GetCursorBlinkRate, () const, float), AS_CALL_THISCALL);
    // unsigned LineEdit::GetCursorPosition() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "uint GetCursorPosition() const", AS_METHODPR(LineEdit, GetCursorPosition, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_cursorPosition() const", AS_METHODPR(LineEdit, GetCursorPosition, () const, unsigned), AS_CALL_THISCALL);
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(LineEdit, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Color& GetDerivedColor() const", AS_METHODPR(LineEdit, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "float GetDerivedOpacity() const", AS_METHODPR(LineEdit, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "float get_derivedOpacity() const", AS_METHODPR(LineEdit, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetDisabledOffset() const", AS_METHODPR(LineEdit, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_disabledOffset() const", AS_METHODPR(LineEdit, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(LineEdit, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(LineEdit, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "uint GetDragButtonCount() const", AS_METHODPR(LineEdit, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_dragButtonCount() const", AS_METHODPR(LineEdit, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(LineEdit, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(LineEdit, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // unsigned LineEdit::GetEchoCharacter() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "uint GetEchoCharacter() const", AS_METHODPR(LineEdit, GetEchoCharacter, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_echoCharacter() const", AS_METHODPR(LineEdit, GetEchoCharacter, () const, unsigned), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(LineEdit, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ GetElementEventSender() const", AS_METHODPR(LineEdit, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool GetEnableAnchor() const", AS_METHODPR(LineEdit, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_enableAnchor() const", AS_METHODPR(LineEdit, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "VariantMap& GetEventDataMap() const", AS_METHODPR(LineEdit, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "Object@+ GetEventSender() const", AS_METHODPR(LineEdit, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "FocusMode GetFocusMode() const", AS_METHODPR(LineEdit, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "FocusMode get_focusMode() const", AS_METHODPR(LineEdit, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(LineEdit, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(LineEdit, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "const VariantMap& GetGlobalVars() const", AS_METHODPR(LineEdit, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const VariantMap& get_globalVars() const", AS_METHODPR(LineEdit, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetHeight() const", AS_METHODPR(LineEdit, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_height() const", AS_METHODPR(LineEdit, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(LineEdit, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(LineEdit, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetHoverOffset() const", AS_METHODPR(LineEdit, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_hoverOffset() const", AS_METHODPR(LineEdit, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "const IntRect& GetImageBorder() const", AS_METHODPR(LineEdit, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntRect& get_imageBorder() const", AS_METHODPR(LineEdit, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "const IntRect& GetImageRect() const", AS_METHODPR(LineEdit, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntRect& get_imageRect() const", AS_METHODPR(LineEdit, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetIndent() const", AS_METHODPR(LineEdit, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_indent() const", AS_METHODPR(LineEdit, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetIndentSpacing() const", AS_METHODPR(LineEdit, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_indentSpacing() const", AS_METHODPR(LineEdit, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetIndentWidth() const", AS_METHODPR(LineEdit, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_indentWidth() const", AS_METHODPR(LineEdit, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(LineEdit, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntRect& GetLayoutBorder() const", AS_METHODPR(LineEdit, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntRect& get_layoutBorder() const", AS_METHODPR(LineEdit, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetLayoutElementMaxSize() const", AS_METHODPR(LineEdit, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(LineEdit, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(LineEdit, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "LayoutMode GetLayoutMode() const", AS_METHODPR(LineEdit, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "LayoutMode get_layoutMode() const", AS_METHODPR(LineEdit, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetLayoutSpacing() const", AS_METHODPR(LineEdit, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_layoutSpacing() const", AS_METHODPR(LineEdit, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "Material@+ GetMaterial() const", AS_METHODPR(LineEdit, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "Material@+ get_material() const", AS_METHODPR(LineEdit, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "ResourceRef GetMaterialAttr() const", AS_METHODPR(LineEdit, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Vector2& GetMaxAnchor() const", AS_METHODPR(LineEdit, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const Vector2& get_maxAnchor() const", AS_METHODPR(LineEdit, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetMaxHeight() const", AS_METHODPR(LineEdit, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_maxHeight() const", AS_METHODPR(LineEdit, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // unsigned LineEdit::GetMaxLength() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "uint GetMaxLength() const", AS_METHODPR(LineEdit, GetMaxLength, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_maxLength() const", AS_METHODPR(LineEdit, GetMaxLength, () const, unsigned), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetMaxOffset() const", AS_METHODPR(LineEdit, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_maxOffset() const", AS_METHODPR(LineEdit, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetMaxSize() const", AS_METHODPR(LineEdit, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_maxSize() const", AS_METHODPR(LineEdit, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetMaxWidth() const", AS_METHODPR(LineEdit, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_maxWidth() const", AS_METHODPR(LineEdit, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Vector2& GetMinAnchor() const", AS_METHODPR(LineEdit, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const Vector2& get_minAnchor() const", AS_METHODPR(LineEdit, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetMinHeight() const", AS_METHODPR(LineEdit, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_minHeight() const", AS_METHODPR(LineEdit, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetMinOffset() const", AS_METHODPR(LineEdit, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_minOffset() const", AS_METHODPR(LineEdit, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetMinSize() const", AS_METHODPR(LineEdit, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_minSize() const", AS_METHODPR(LineEdit, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetMinWidth() const", AS_METHODPR(LineEdit, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_minWidth() const", AS_METHODPR(LineEdit, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const String& GetName() const", AS_METHODPR(LineEdit, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const String& get_name() const", AS_METHODPR(LineEdit, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "uint GetNumAttributes() const", AS_METHODPR(LineEdit, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_numAttributes() const", AS_METHODPR(LineEdit, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "uint GetNumChildren(bool = false) const", AS_METHODPR(LineEdit, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "uint get_numChildren(bool = false) const", AS_METHODPR(LineEdit, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "uint GetNumNetworkAttributes() const", AS_METHODPR(LineEdit, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(LineEdit, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(LineEdit, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(LineEdit, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "float GetOpacity() const", AS_METHODPR(LineEdit, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "float get_opacity() const", AS_METHODPR(LineEdit, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ GetParent() const", AS_METHODPR(LineEdit, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ get_parent() const", AS_METHODPR(LineEdit, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Vector2& GetPivot() const", AS_METHODPR(LineEdit, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const Vector2& get_pivot() const", AS_METHODPR(LineEdit, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetPosition() const", AS_METHODPR(LineEdit, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_position() const", AS_METHODPR(LineEdit, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetPriority() const", AS_METHODPR(LineEdit, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_priority() const", AS_METHODPR(LineEdit, GetPriority, () const, int), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ GetRoot() const", AS_METHODPR(LineEdit, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ get_root() const", AS_METHODPR(LineEdit, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetScreenPosition() const", AS_METHODPR(LineEdit, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_screenPosition() const", AS_METHODPR(LineEdit, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& GetSize() const", AS_METHODPR(LineEdit, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const IntVector2& get_size() const", AS_METHODPR(LineEdit, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool GetSortChildren() const", AS_METHODPR(LineEdit, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_sortChildren() const", AS_METHODPR(LineEdit, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(LineEdit, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(LineEdit_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("LineEdit", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(LineEdit_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // const String& LineEdit::GetText() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "const String& GetText() const", AS_METHODPR(LineEdit, GetText, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const String& get_text() const", AS_METHODPR(LineEdit, GetText, () const, const String&), AS_CALL_THISCALL);
    // Text* LineEdit::GetTextElement() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "Text@+ GetTextElement() const", AS_METHODPR(LineEdit, GetTextElement, () const, Text*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "Text@+ get_textElement() const", AS_METHODPR(LineEdit, GetTextElement, () const, Text*), AS_CALL_THISCALL);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "Texture@+ GetTexture() const", AS_METHODPR(LineEdit, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "Texture@+ get_texture() const", AS_METHODPR(LineEdit, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "ResourceRef GetTextureAttr() const", AS_METHODPR(LineEdit, GetTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "TraversalMode GetTraversalMode() const", AS_METHODPR(LineEdit, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "TraversalMode get_traversalMode() const", AS_METHODPR(LineEdit, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "StringHash GetType() const", AS_METHODPR(LineEdit, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "StringHash get_type() const", AS_METHODPR(LineEdit, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "const String& GetTypeName() const", AS_METHODPR(LineEdit, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "const String& get_typeName() const", AS_METHODPR(LineEdit, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool GetUseDerivedOpacity() const", AS_METHODPR(LineEdit, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_useDerivedOpacity() const", AS_METHODPR(LineEdit, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(LineEdit, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "const VariantMap& GetVars() const", AS_METHODPR(LineEdit, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(LineEdit, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(LineEdit, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "int GetWidth() const", AS_METHODPR(LineEdit, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_width() const", AS_METHODPR(LineEdit, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool HasColorGradient() const", AS_METHODPR(LineEdit, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_colorGradient() const", AS_METHODPR(LineEdit, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "bool HasEventHandlers() const", AS_METHODPR(LineEdit, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool HasFocus() const", AS_METHODPR(LineEdit, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_focus() const", AS_METHODPR(LineEdit, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(LineEdit, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(LineEdit, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool HasTag(const String&in) const", AS_METHODPR(LineEdit, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void InsertChild(uint, UIElement@+)", AS_METHODPR(LineEdit, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsChildOf(UIElement@+) const", AS_METHODPR(LineEdit, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool LineEdit::IsCursorMovable() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "bool IsCursorMovable() const", AS_METHODPR(LineEdit, IsCursorMovable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_cursorMovable() const", AS_METHODPR(LineEdit, IsCursorMovable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsEditable() const", AS_METHODPR(LineEdit, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_editable() const", AS_METHODPR(LineEdit, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsElementEventSender() const", AS_METHODPR(LineEdit, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_elementEventSender() const", AS_METHODPR(LineEdit, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsEnabled() const", AS_METHODPR(LineEdit, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_enabled() const", AS_METHODPR(LineEdit, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsEnabledSelf() const", AS_METHODPR(LineEdit, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_enabledSelf() const", AS_METHODPR(LineEdit, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsFixedHeight() const", AS_METHODPR(LineEdit, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_fixedHeight() const", AS_METHODPR(LineEdit, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsFixedSize() const", AS_METHODPR(LineEdit, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_fixedSize() const", AS_METHODPR(LineEdit, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsFixedWidth() const", AS_METHODPR(LineEdit, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_fixedWidth() const", AS_METHODPR(LineEdit, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsHovering() const", AS_METHODPR(LineEdit, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_hovering() const", AS_METHODPR(LineEdit, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsInside(IntVector2, bool)", AS_METHODPR(LineEdit, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(LineEdit, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "bool IsInstanceOf(StringHash) const", AS_METHODPR(LineEdit, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsInternal() const", AS_METHODPR(LineEdit, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_internal() const", AS_METHODPR(LineEdit, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsSelected() const", AS_METHODPR(LineEdit, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_selected() const", AS_METHODPR(LineEdit, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool IsTemporary() const", AS_METHODPR(LineEdit, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_temporary() const", AS_METHODPR(LineEdit, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool LineEdit::IsTextCopyable() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "bool IsTextCopyable() const", AS_METHODPR(LineEdit, IsTextCopyable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_textCopyable() const", AS_METHODPR(LineEdit, IsTextCopyable, () const, bool), AS_CALL_THISCALL);
    // bool LineEdit::IsTextSelectable() const | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "bool IsTextSelectable() const", AS_METHODPR(LineEdit, IsTextSelectable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_textSelectable() const", AS_METHODPR(LineEdit, IsTextSelectable, () const, bool), AS_CALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "bool IsTiled() const", AS_METHODPR(LineEdit, IsTiled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_tiled() const", AS_METHODPR(LineEdit, IsTiled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsVisible() const", AS_METHODPR(LineEdit, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_visible() const", AS_METHODPR(LineEdit, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsVisibleEffective() const", AS_METHODPR(LineEdit, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool get_visibleEffective() const", AS_METHODPR(LineEdit, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsWheelHandler() const", AS_METHODPR(LineEdit, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(LineEdit, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // explicit LineEdit::LineEdit(Context* context) | File: ../UI/LineEdit.h
    engine->RegisterObjectBehaviour("LineEdit", asBEHAVE_FACTORY, "LineEdit@+ f()", AS_FUNCTION(LineEdit_LineEdit_Context), AS_CALL_CDECL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool Load(Deserializer&)", AS_METHODPR(LineEdit, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(LineEdit, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(LineEdit, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool LoadXML(const XMLElement&in)", AS_METHODPR(LineEdit, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(LineEdit, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool LoadXML(Deserializer&)", AS_METHODPR(LineEdit, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void MarkNetworkUpdate()", AS_METHODPR(LineEdit, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // void LineEdit::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(LineEdit, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(LineEdit, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // void LineEdit::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(LineEdit, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // void LineEdit::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(LineEdit, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(LineEdit, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // bool LineEdit::OnDragDropFinish(UIElement* source) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(LineEdit, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // bool LineEdit::OnDragDropTest(UIElement* source) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(LineEdit, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(LineEdit, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // void LineEdit::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(LineEdit, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(LineEdit, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(LineEdit, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(LineEdit, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnIndentSet()", AS_METHODPR(LineEdit, OnIndentSet, (), void), AS_CALL_THISCALL);
    // void LineEdit::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(LineEdit, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(LineEdit, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(LineEdit, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(LineEdit, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnSetEditable()", AS_METHODPR(LineEdit, OnSetEditable, (), void), AS_CALL_THISCALL);
    // void LineEdit::OnTextInput(const String& text) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void OnTextInput(const String&in)", AS_METHODPR(LineEdit, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(LineEdit, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(LineEdit, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(LineEdit, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("LineEdit", "int Refs() const", AS_METHODPR(LineEdit, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_refs() const", AS_METHODPR(LineEdit, Refs, () const, int), AS_CALL_THISCALL);
    // static void LineEdit::RegisterObject(Context* context) | File: ../UI/LineEdit.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("LineEdit", asBEHAVE_RELEASE, "void f()", AS_METHODPR(LineEdit, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void Remove()", AS_METHODPR(LineEdit, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveAllChildren()", AS_METHODPR(LineEdit, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveAllTags()", AS_METHODPR(LineEdit, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(LineEdit, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(LineEdit, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveChildAtIndex(uint)", AS_METHODPR(LineEdit, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveInstanceDefault()", AS_METHODPR(LineEdit, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void RemoveObjectAnimation()", AS_METHODPR(LineEdit, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool RemoveTag(const String&in)", AS_METHODPR(LineEdit, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void ResetDeepEnabled()", AS_METHODPR(LineEdit, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void ResetToDefault()", AS_METHODPR(LineEdit, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool Save(Serializer&) const", AS_METHODPR(LineEdit, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool SaveDefaultAttributes() const", AS_METHODPR(LineEdit, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "bool SaveJSON(JSONValue&) const", AS_METHODPR(LineEdit, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool SaveXML(XMLElement&) const", AS_METHODPR(LineEdit, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(LineEdit, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(LineEdit, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void SendEvent(StringHash)", AS_METHODPR(LineEdit, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(LineEdit, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(LineEdit, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetAnimationEnabled(bool)", AS_METHODPR(LineEdit, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_animationEnabled(bool)", AS_METHODPR(LineEdit, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetAnimationTime(float)", AS_METHODPR(LineEdit, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(LineEdit, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(LineEdit, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(LineEdit, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(LineEdit, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(LineEdit, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(LineEdit, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(LineEdit, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetBlendMode(BlendMode)", AS_METHODPR(LineEdit, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_blendMode(BlendMode)", AS_METHODPR(LineEdit, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void SetBlockEvents(bool)", AS_METHODPR(LineEdit, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetBorder(const IntRect&in)", AS_METHODPR(LineEdit, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_border(const IntRect&in)", AS_METHODPR(LineEdit, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetBringToBack(bool)", AS_METHODPR(LineEdit, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_bringToBack(bool)", AS_METHODPR(LineEdit, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetBringToFront(bool)", AS_METHODPR(LineEdit, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_bringToFront(bool)", AS_METHODPR(LineEdit, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(LineEdit, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetClipBorder(const IntRect&in)", AS_METHODPR(LineEdit, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_clipBorder(const IntRect&in)", AS_METHODPR(LineEdit, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetClipChildren(bool)", AS_METHODPR(LineEdit, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_clipChildren(bool)", AS_METHODPR(LineEdit, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetColor(const Color&in)", AS_METHODPR(LineEdit, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_color(const Color&in)", AS_METHODPR(LineEdit, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetColor(Corner, const Color&in)", AS_METHODPR(LineEdit, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_colors(Corner, const Color&in)", AS_METHODPR(LineEdit, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void LineEdit::SetCursorBlinkRate(float rate) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetCursorBlinkRate(float)", AS_METHODPR(LineEdit, SetCursorBlinkRate, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_cursorBlinkRate(float)", AS_METHODPR(LineEdit, SetCursorBlinkRate, (float), void), AS_CALL_THISCALL);
    // void LineEdit::SetCursorMovable(bool enable) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetCursorMovable(bool)", AS_METHODPR(LineEdit, SetCursorMovable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_cursorMovable(bool)", AS_METHODPR(LineEdit, SetCursorMovable, (bool), void), AS_CALL_THISCALL);
    // void LineEdit::SetCursorPosition(unsigned position) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetCursorPosition(uint)", AS_METHODPR(LineEdit, SetCursorPosition, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_cursorPosition(uint)", AS_METHODPR(LineEdit, SetCursorPosition, (unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetDeepEnabled(bool)", AS_METHODPR(LineEdit, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(LineEdit, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(LineEdit, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetDisabledOffset(const IntVector2&in)", AS_METHODPR(LineEdit, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_disabledOffset(const IntVector2&in)", AS_METHODPR(LineEdit, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetDisabledOffset(int, int)", AS_METHODPR(LineEdit, SetDisabledOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(LineEdit, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(LineEdit, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void LineEdit::SetEchoCharacter(unsigned c) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetEchoCharacter(uint)", AS_METHODPR(LineEdit, SetEchoCharacter, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_echoCharacter(uint)", AS_METHODPR(LineEdit, SetEchoCharacter, (unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetEditable(bool)", AS_METHODPR(LineEdit, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_editable(bool)", AS_METHODPR(LineEdit, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetElementEventSender(bool)", AS_METHODPR(LineEdit, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_elementEventSender(bool)", AS_METHODPR(LineEdit, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetEnableAnchor(bool)", AS_METHODPR(LineEdit, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_enableAnchor(bool)", AS_METHODPR(LineEdit, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetEnabled(bool)", AS_METHODPR(LineEdit, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_enabled(bool)", AS_METHODPR(LineEdit, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetEnabledRecursive(bool)", AS_METHODPR(LineEdit, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetFixedHeight(int)", AS_METHODPR(LineEdit, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(LineEdit, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetFixedSize(int, int)", AS_METHODPR(LineEdit, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetFixedWidth(int)", AS_METHODPR(LineEdit, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetFocus(bool)", AS_METHODPR(LineEdit, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_focus(bool)", AS_METHODPR(LineEdit, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetFocusMode(FocusMode)", AS_METHODPR(LineEdit, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_focusMode(FocusMode)", AS_METHODPR(LineEdit, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetFullImageRect()", AS_METHODPR(LineEdit, SetFullImageRect, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(LineEdit, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(LineEdit, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetHeight(int)", AS_METHODPR(LineEdit, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_height(int)", AS_METHODPR(LineEdit, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(LineEdit, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(LineEdit, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetHovering(bool)", AS_METHODPR(LineEdit, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetHoverOffset(const IntVector2&in)", AS_METHODPR(LineEdit, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_hoverOffset(const IntVector2&in)", AS_METHODPR(LineEdit, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetHoverOffset(int, int)", AS_METHODPR(LineEdit, SetHoverOffset, (int, int), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetImageBorder(const IntRect&in)", AS_METHODPR(LineEdit, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_imageBorder(const IntRect&in)", AS_METHODPR(LineEdit, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetImageRect(const IntRect&in)", AS_METHODPR(LineEdit, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_imageRect(const IntRect&in)", AS_METHODPR(LineEdit, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetIndent(int)", AS_METHODPR(LineEdit, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_indent(int)", AS_METHODPR(LineEdit, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetIndentSpacing(int)", AS_METHODPR(LineEdit, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_indentSpacing(int)", AS_METHODPR(LineEdit, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void SetInstanceDefault(bool)", AS_METHODPR(LineEdit, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(LineEdit, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetInternal(bool)", AS_METHODPR(LineEdit, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_internal(bool)", AS_METHODPR(LineEdit, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(LineEdit, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(LineEdit, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(LineEdit, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(LineEdit, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(LineEdit, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetLayoutMode(LayoutMode)", AS_METHODPR(LineEdit, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_layoutMode(LayoutMode)", AS_METHODPR(LineEdit, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetLayoutSpacing(int)", AS_METHODPR(LineEdit, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_layoutSpacing(int)", AS_METHODPR(LineEdit, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaterial(Material@+)", AS_METHODPR(LineEdit, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_material(Material@+)", AS_METHODPR(LineEdit, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(LineEdit, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(LineEdit, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(LineEdit, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxAnchor(float, float)", AS_METHODPR(LineEdit, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxHeight(int)", AS_METHODPR(LineEdit, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_maxHeight(int)", AS_METHODPR(LineEdit, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void LineEdit::SetMaxLength(unsigned length) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxLength(uint)", AS_METHODPR(LineEdit, SetMaxLength, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_maxLength(uint)", AS_METHODPR(LineEdit, SetMaxLength, (unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(LineEdit, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(LineEdit, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(LineEdit, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_maxSize(const IntVector2&in)", AS_METHODPR(LineEdit, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxSize(int, int)", AS_METHODPR(LineEdit, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMaxWidth(int)", AS_METHODPR(LineEdit, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_maxWidth(int)", AS_METHODPR(LineEdit, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(LineEdit, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_minAnchor(const Vector2&in)", AS_METHODPR(LineEdit, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinAnchor(float, float)", AS_METHODPR(LineEdit, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinHeight(int)", AS_METHODPR(LineEdit, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_minHeight(int)", AS_METHODPR(LineEdit, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(LineEdit, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_minOffset(const IntVector2&in)", AS_METHODPR(LineEdit, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinSize(const IntVector2&in)", AS_METHODPR(LineEdit, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_minSize(const IntVector2&in)", AS_METHODPR(LineEdit, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinSize(int, int)", AS_METHODPR(LineEdit, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetMinWidth(int)", AS_METHODPR(LineEdit, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_minWidth(int)", AS_METHODPR(LineEdit, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetName(const String&in)", AS_METHODPR(LineEdit, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_name(const String&in)", AS_METHODPR(LineEdit, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(LineEdit, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(LineEdit, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LineEdit", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(LineEdit, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetOpacity(float)", AS_METHODPR(LineEdit, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_opacity(float)", AS_METHODPR(LineEdit, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(LineEdit, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetPivot(const Vector2&in)", AS_METHODPR(LineEdit, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_pivot(const Vector2&in)", AS_METHODPR(LineEdit, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetPivot(float, float)", AS_METHODPR(LineEdit, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetPosition(const IntVector2&in)", AS_METHODPR(LineEdit, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_position(const IntVector2&in)", AS_METHODPR(LineEdit, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetPosition(int, int)", AS_METHODPR(LineEdit, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetPriority(int)", AS_METHODPR(LineEdit, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_priority(int)", AS_METHODPR(LineEdit, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(LineEdit, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetSelected(bool)", AS_METHODPR(LineEdit, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_selected(bool)", AS_METHODPR(LineEdit, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetSize(const IntVector2&in)", AS_METHODPR(LineEdit, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_size(const IntVector2&in)", AS_METHODPR(LineEdit, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetSize(int, int)", AS_METHODPR(LineEdit, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetSortChildren(bool)", AS_METHODPR(LineEdit, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_sortChildren(bool)", AS_METHODPR(LineEdit, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(LineEdit, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool SetStyle(const XMLElement&in)", AS_METHODPR(LineEdit, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(LineEdit, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(LineEdit_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void SetTemporary(bool)", AS_METHODPR(LineEdit, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_temporary(bool)", AS_METHODPR(LineEdit, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void LineEdit::SetText(const String& text) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetText(const String&in)", AS_METHODPR(LineEdit, SetText, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_text(const String&in)", AS_METHODPR(LineEdit, SetText, (const String&), void), AS_CALL_THISCALL);
    // void LineEdit::SetTextCopyable(bool enable) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetTextCopyable(bool)", AS_METHODPR(LineEdit, SetTextCopyable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_textCopyable(bool)", AS_METHODPR(LineEdit, SetTextCopyable, (bool), void), AS_CALL_THISCALL);
    // void LineEdit::SetTextSelectable(bool enable) | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void SetTextSelectable(bool)", AS_METHODPR(LineEdit, SetTextSelectable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_textSelectable(bool)", AS_METHODPR(LineEdit, SetTextSelectable, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetTexture(Texture@+)", AS_METHODPR(LineEdit, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_texture(Texture@+)", AS_METHODPR(LineEdit, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetTextureAttr(const ResourceRef&in)", AS_METHODPR(LineEdit, SetTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("LineEdit", "void SetTiled(bool)", AS_METHODPR(LineEdit, SetTiled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_tiled(bool)", AS_METHODPR(LineEdit, SetTiled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetTraversalMode(TraversalMode)", AS_METHODPR(LineEdit, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_traversalMode(TraversalMode)", AS_METHODPR(LineEdit, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetUseDerivedOpacity(bool)", AS_METHODPR(LineEdit, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_useDerivedOpacity(bool)", AS_METHODPR(LineEdit, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(LineEdit, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(LineEdit, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(LineEdit, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetVisible(bool)", AS_METHODPR(LineEdit, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_visible(bool)", AS_METHODPR(LineEdit, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SetWidth(int)", AS_METHODPR(LineEdit, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "void set_width(int)", AS_METHODPR(LineEdit, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void SortChildren()", AS_METHODPR(LineEdit, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void UnsubscribeFromAllEvents()", AS_METHODPR(LineEdit, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(LineEdit_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(LineEdit, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(LineEdit, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LineEdit", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(LineEdit, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void LineEdit::Update(float timeStep) override | File: ../UI/LineEdit.h
    engine->RegisterObjectMethod("LineEdit", "void Update(float)", AS_METHODPR(LineEdit, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("LineEdit", "void UpdateLayout()", AS_METHODPR(LineEdit, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("LineEdit", "int WeakRefs() const", AS_METHODPR(LineEdit, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LineEdit", "int get_weakRefs() const", AS_METHODPR(LineEdit, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(LineEdit, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(LineEdit, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LineEdit", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(LineEdit, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("ListBase", "void Swap(ListBase&)", AS_METHODPR(ListBase, Swap, (ListBase&), void), AS_CALL_THISCALL);
    // ListBase& ListBase::operator=(const ListBase&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<ListBase>(engine, "ListBase");
#ifdef REGISTER_MANUAL_PART_ListBase
    REGISTER_MANUAL_PART_ListBase(ListBase, "ListBase")
#endif

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void AddChild(UIElement@+)", AS_METHODPR(ListView, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void ListView::AddItem(UIElement* item) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void AddItem(UIElement@+)", AS_METHODPR(ListView, AddItem, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ListView", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ListView, AddRef, (), void), AS_CALL_THISCALL);
    // void ListView::AddSelection(unsigned index) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void AddSelection(uint)", AS_METHODPR(ListView, AddSelection, (unsigned), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void AddTag(const String&in)", AS_METHODPR(ListView, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(ListView, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(ListView_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void AdjustScissor(IntRect&)", AS_METHODPR(ListView, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void AllocateNetworkState()", AS_METHODPR(ListView, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void ScrollView::ApplyAttributes() override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void ApplyAttributes()", AS_METHODPR(ListView, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void BringToFront()", AS_METHODPR(ListView, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void ListView::ChangeSelection(int delta, bool additive=false) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void ChangeSelection(int, bool = false)", AS_METHODPR(ListView, ChangeSelection, (int, bool), void), AS_CALL_THISCALL);
    // void ListView::ClearSelection() | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void ClearSelection()", AS_METHODPR(ListView, ClearSelection, (), void), AS_CALL_THISCALL);
    // void ListView::CopySelectedItemsToClipboard() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void CopySelectedItemsToClipboard() const", AS_METHODPR(ListView, CopySelectedItemsToClipboard, () const, void), AS_CALL_THISCALL);
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(ListView, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void ListView::DisableInternalLayoutUpdate() | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void DisableInternalLayoutUpdate()", AS_METHODPR(ListView, DisableInternalLayoutUpdate, (), void), AS_CALL_THISCALL);
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void DisableLayoutUpdate()", AS_METHODPR(ListView, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(ListView, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void ListView::EnableInternalLayoutUpdate() | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void EnableInternalLayoutUpdate()", AS_METHODPR(ListView, EnableInternalLayoutUpdate, (), void), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void EnableLayoutUpdate()", AS_METHODPR(ListView, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // void ListView::EnsureItemVisibility(unsigned index) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void EnsureItemVisibility(uint)", AS_METHODPR(ListView, EnsureItemVisibility, (unsigned), void), AS_CALL_THISCALL);
    // void ListView::EnsureItemVisibility(UIElement* item) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void EnsureItemVisibility(UIElement@+)", AS_METHODPR(ListView, EnsureItemVisibility, (UIElement*), void), AS_CALL_THISCALL);
    // void ListView::Expand(unsigned index, bool enable, bool recursive=false) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void Expand(uint, bool, bool = false)", AS_METHODPR(ListView, Expand, (unsigned, bool, bool), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(ListView, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "uint FindChild(UIElement@+) const", AS_METHODPR(ListView, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // unsigned ListView::FindItem(UIElement* item) const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "uint FindItem(UIElement@+) const", AS_METHODPR(ListView, FindItem, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "bool GetAnimationEnabled() const", AS_METHODPR(ListView, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_animationEnabled() const", AS_METHODPR(ListView, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const String& GetAppliedStyle() const", AS_METHODPR(ListView, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const String& get_style() const", AS_METHODPR(ListView, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "Variant GetAttribute(uint) const", AS_METHODPR(ListView, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "Variant get_attributes(uint) const", AS_METHODPR(ListView, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "Variant GetAttribute(const String&in) const", AS_METHODPR(ListView, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ListView, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ListView, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ListView, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ListView, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ListView, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ListView, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ListView, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool ScrollView::GetAutoDisableChildren() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "bool GetAutoDisableChildren() const", AS_METHODPR(ListView, GetAutoDisableChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_autoDisableChildren() const", AS_METHODPR(ListView, GetAutoDisableChildren, () const, bool), AS_CALL_THISCALL);
    // float ScrollView::GetAutoDisableThreshold() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "float GetAutoDisableThreshold() const", AS_METHODPR(ListView, GetAutoDisableThreshold, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_autoDisableThreshold() const", AS_METHODPR(ListView, GetAutoDisableThreshold, () const, float), AS_CALL_THISCALL);
    // int ListView::GetBaseIndent() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "int GetBaseIndent() const", AS_METHODPR(ListView, GetBaseIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_baseIndent() const", AS_METHODPR(ListView, GetBaseIndent, () const, int), AS_CALL_THISCALL);
    // virtual void UIElement::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "bool GetBlockEvents() const", AS_METHODPR(ListView, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool GetBringToBack() const", AS_METHODPR(ListView, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_bringToBack() const", AS_METHODPR(ListView, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool GetBringToFront() const", AS_METHODPR(ListView, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_bringToFront() const", AS_METHODPR(ListView, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "const String& GetCategory() const", AS_METHODPR(ListView, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const String& get_category() const", AS_METHODPR(ListView, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetChild(uint) const", AS_METHODPR(ListView, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_children(uint) const", AS_METHODPR(ListView, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(ListView, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(ListView, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetChildOffset() const", AS_METHODPR(ListView, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_childOffset() const", AS_METHODPR(ListView, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(ListView_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(ListView_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(ListView_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // bool ListView::GetClearSelectionOnDefocus() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "bool GetClearSelectionOnDefocus() const", AS_METHODPR(ListView, GetClearSelectionOnDefocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_clearSelectionOnDefocus() const", AS_METHODPR(ListView, GetClearSelectionOnDefocus, () const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntRect& GetClipBorder() const", AS_METHODPR(ListView, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntRect& get_clipBorder() const", AS_METHODPR(ListView, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool GetClipChildren() const", AS_METHODPR(ListView, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_clipChildren() const", AS_METHODPR(ListView, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Color& GetColor(Corner) const", AS_METHODPR(ListView, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const Color& get_colors(Corner) const", AS_METHODPR(ListView, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Color& GetColorAttr() const", AS_METHODPR(ListView, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "IntRect GetCombinedScreenRect()", AS_METHODPR(ListView, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "IntRect get_combinedScreenRect()", AS_METHODPR(ListView, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // UIElement* ScrollView::GetContentElement() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetContentElement() const", AS_METHODPR(ListView, GetContentElement, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_contentElement() const", AS_METHODPR(ListView, GetContentElement, () const, UIElement*), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(ListView, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Color& GetDerivedColor() const", AS_METHODPR(ListView, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "float GetDerivedOpacity() const", AS_METHODPR(ListView, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_derivedOpacity() const", AS_METHODPR(ListView, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(ListView, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(ListView, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "uint GetDragButtonCount() const", AS_METHODPR(ListView, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "uint get_dragButtonCount() const", AS_METHODPR(ListView, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(ListView, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(ListView, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(ListView, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetElementEventSender() const", AS_METHODPR(ListView, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool GetEnableAnchor() const", AS_METHODPR(ListView, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_enableAnchor() const", AS_METHODPR(ListView, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "VariantMap& GetEventDataMap() const", AS_METHODPR(ListView, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "Object@+ GetEventSender() const", AS_METHODPR(ListView, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "FocusMode GetFocusMode() const", AS_METHODPR(ListView, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "FocusMode get_focusMode() const", AS_METHODPR(ListView, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ListView, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ListView, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ListView, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const VariantMap& get_globalVars() const", AS_METHODPR(ListView, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetHeight() const", AS_METHODPR(ListView, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_height() const", AS_METHODPR(ListView, GetHeight, () const, int), AS_CALL_THISCALL);
    // bool ListView::GetHierarchyMode() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "bool GetHierarchyMode() const", AS_METHODPR(ListView, GetHierarchyMode, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_hierarchyMode() const", AS_METHODPR(ListView, GetHierarchyMode, () const, bool), AS_CALL_THISCALL);
    // HighlightMode ListView::GetHighlightMode() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "HighlightMode GetHighlightMode() const", AS_METHODPR(ListView, GetHighlightMode, () const, HighlightMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "HighlightMode get_highlightMode() const", AS_METHODPR(ListView, GetHighlightMode, () const, HighlightMode), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(ListView, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(ListView, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // ScrollBar* ScrollView::GetHorizontalScrollBar() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "ScrollBar@+ GetHorizontalScrollBar() const", AS_METHODPR(ListView, GetHorizontalScrollBar, () const, ScrollBar*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "ScrollBar@+ get_horizontalScrollBar() const", AS_METHODPR(ListView, GetHorizontalScrollBar, () const, ScrollBar*), AS_CALL_THISCALL);
    // bool ScrollView::GetHorizontalScrollBarVisible() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "bool GetHorizontalScrollBarVisible() const", AS_METHODPR(ListView, GetHorizontalScrollBarVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_horizontalScrollBarVisible() const", AS_METHODPR(ListView, GetHorizontalScrollBarVisible, () const, bool), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetIndent() const", AS_METHODPR(ListView, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_indent() const", AS_METHODPR(ListView, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetIndentSpacing() const", AS_METHODPR(ListView, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_indentSpacing() const", AS_METHODPR(ListView, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetIndentWidth() const", AS_METHODPR(ListView, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_indentWidth() const", AS_METHODPR(ListView, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ListView, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // UIElement* ListView::GetItem(unsigned index) const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetItem(uint) const", AS_METHODPR(ListView, GetItem, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_items(uint) const", AS_METHODPR(ListView, GetItem, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // PODVector<UIElement*> ListView::GetItems() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ GetItems() const", AS_FUNCTION_OBJFIRST(ListView_GetItems_void), AS_CALL_CDECL_OBJFIRST);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntRect& GetLayoutBorder() const", AS_METHODPR(ListView, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntRect& get_layoutBorder() const", AS_METHODPR(ListView, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetLayoutElementMaxSize() const", AS_METHODPR(ListView, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(ListView, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(ListView, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "LayoutMode GetLayoutMode() const", AS_METHODPR(ListView, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "LayoutMode get_layoutMode() const", AS_METHODPR(ListView, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetLayoutSpacing() const", AS_METHODPR(ListView, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_layoutSpacing() const", AS_METHODPR(ListView, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Vector2& GetMaxAnchor() const", AS_METHODPR(ListView, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const Vector2& get_maxAnchor() const", AS_METHODPR(ListView, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetMaxHeight() const", AS_METHODPR(ListView, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_maxHeight() const", AS_METHODPR(ListView, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetMaxOffset() const", AS_METHODPR(ListView, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_maxOffset() const", AS_METHODPR(ListView, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetMaxSize() const", AS_METHODPR(ListView, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_maxSize() const", AS_METHODPR(ListView, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetMaxWidth() const", AS_METHODPR(ListView, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_maxWidth() const", AS_METHODPR(ListView, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Vector2& GetMinAnchor() const", AS_METHODPR(ListView, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const Vector2& get_minAnchor() const", AS_METHODPR(ListView, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetMinHeight() const", AS_METHODPR(ListView, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_minHeight() const", AS_METHODPR(ListView, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetMinOffset() const", AS_METHODPR(ListView, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_minOffset() const", AS_METHODPR(ListView, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetMinSize() const", AS_METHODPR(ListView, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_minSize() const", AS_METHODPR(ListView, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetMinWidth() const", AS_METHODPR(ListView, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_minWidth() const", AS_METHODPR(ListView, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // bool ListView::GetMultiselect() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "bool GetMultiselect() const", AS_METHODPR(ListView, GetMultiselect, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_multiselect() const", AS_METHODPR(ListView, GetMultiselect, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const String& GetName() const", AS_METHODPR(ListView, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const String& get_name() const", AS_METHODPR(ListView, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "uint GetNumAttributes() const", AS_METHODPR(ListView, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "uint get_numAttributes() const", AS_METHODPR(ListView, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "uint GetNumChildren(bool = false) const", AS_METHODPR(ListView, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "uint get_numChildren(bool = false) const", AS_METHODPR(ListView, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned ListView::GetNumItems() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "uint GetNumItems() const", AS_METHODPR(ListView, GetNumItems, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "uint get_numItems() const", AS_METHODPR(ListView, GetNumItems, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "uint GetNumNetworkAttributes() const", AS_METHODPR(ListView, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ListView, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ListView, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ListView, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "float GetOpacity() const", AS_METHODPR(ListView, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_opacity() const", AS_METHODPR(ListView, GetOpacity, () const, float), AS_CALL_THISCALL);
    // float ScrollView::GetPageStep() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "float GetPageStep() const", AS_METHODPR(ListView, GetPageStep, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_pageStep() const", AS_METHODPR(ListView, GetPageStep, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetParent() const", AS_METHODPR(ListView, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_parent() const", AS_METHODPR(ListView, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Vector2& GetPivot() const", AS_METHODPR(ListView, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const Vector2& get_pivot() const", AS_METHODPR(ListView, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetPosition() const", AS_METHODPR(ListView, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_position() const", AS_METHODPR(ListView, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetPriority() const", AS_METHODPR(ListView, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_priority() const", AS_METHODPR(ListView, GetPriority, () const, int), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetRoot() const", AS_METHODPR(ListView, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_root() const", AS_METHODPR(ListView, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetScreenPosition() const", AS_METHODPR(ListView, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_screenPosition() const", AS_METHODPR(ListView, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool ScrollView::GetScrollBarsAutoVisible() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "bool GetScrollBarsAutoVisible() const", AS_METHODPR(ListView, GetScrollBarsAutoVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_scrollBarsAutoVisible() const", AS_METHODPR(ListView, GetScrollBarsAutoVisible, () const, bool), AS_CALL_THISCALL);
    // float ScrollView::GetScrollDeceleration() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "float GetScrollDeceleration() const", AS_METHODPR(ListView, GetScrollDeceleration, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_scrollDeceleration() const", AS_METHODPR(ListView, GetScrollDeceleration, () const, float), AS_CALL_THISCALL);
    // BorderImage* ScrollView::GetScrollPanel() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "BorderImage@+ GetScrollPanel() const", AS_METHODPR(ListView, GetScrollPanel, () const, BorderImage*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "BorderImage@+ get_scrollPanel() const", AS_METHODPR(ListView, GetScrollPanel, () const, BorderImage*), AS_CALL_THISCALL);
    // float ScrollView::GetScrollSnapEpsilon() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "float GetScrollSnapEpsilon() const", AS_METHODPR(ListView, GetScrollSnapEpsilon, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_scrollSnapEpsilon() const", AS_METHODPR(ListView, GetScrollSnapEpsilon, () const, float), AS_CALL_THISCALL);
    // float ScrollView::GetScrollStep() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "float GetScrollStep() const", AS_METHODPR(ListView, GetScrollStep, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "float get_scrollStep() const", AS_METHODPR(ListView, GetScrollStep, () const, float), AS_CALL_THISCALL);
    // UIElement* ListView::GetSelectedItem() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ GetSelectedItem() const", AS_METHODPR(ListView, GetSelectedItem, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "UIElement@+ get_selectedItem() const", AS_METHODPR(ListView, GetSelectedItem, () const, UIElement*), AS_CALL_THISCALL);
    // PODVector<UIElement*> ListView::GetSelectedItems() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ GetSelectedItems() const", AS_FUNCTION_OBJFIRST(ListView_GetSelectedItems_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ListView", "Array<UIElement@>@ get_selectedItems() const", AS_FUNCTION_OBJFIRST(ListView_GetSelectedItems_void), AS_CALL_CDECL_OBJFIRST);
    // unsigned ListView::GetSelection() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "uint GetSelection() const", AS_METHODPR(ListView, GetSelection, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "uint get_selection() const", AS_METHODPR(ListView, GetSelection, () const, unsigned), AS_CALL_THISCALL);
    // const PODVector<unsigned>& ListView::GetSelections() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "Array<uint>@ GetSelections() const", AS_FUNCTION_OBJFIRST(ListView_GetSelections_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ListView", "Array<uint>@ get_selections() const", AS_FUNCTION_OBJFIRST(ListView_GetSelections_void), AS_CALL_CDECL_OBJFIRST);
    // bool ListView::GetSelectOnClickEnd() const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "bool GetSelectOnClickEnd() const", AS_METHODPR(ListView, GetSelectOnClickEnd, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_selectOnClickEnd() const", AS_METHODPR(ListView, GetSelectOnClickEnd, () const, bool), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetSize() const", AS_METHODPR(ListView, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_size() const", AS_METHODPR(ListView, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool GetSortChildren() const", AS_METHODPR(ListView, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_sortChildren() const", AS_METHODPR(ListView, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ListView, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(ListView_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ListView", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(ListView_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "TraversalMode GetTraversalMode() const", AS_METHODPR(ListView, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "TraversalMode get_traversalMode() const", AS_METHODPR(ListView, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "StringHash GetType() const", AS_METHODPR(ListView, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "StringHash get_type() const", AS_METHODPR(ListView, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "const String& GetTypeName() const", AS_METHODPR(ListView, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const String& get_typeName() const", AS_METHODPR(ListView, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool GetUseDerivedOpacity() const", AS_METHODPR(ListView, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_useDerivedOpacity() const", AS_METHODPR(ListView, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(ListView, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "const VariantMap& GetVars() const", AS_METHODPR(ListView, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(ListView, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(ListView, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // ScrollBar* ScrollView::GetVerticalScrollBar() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "ScrollBar@+ GetVerticalScrollBar() const", AS_METHODPR(ListView, GetVerticalScrollBar, () const, ScrollBar*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "ScrollBar@+ get_verticalScrollBar() const", AS_METHODPR(ListView, GetVerticalScrollBar, () const, ScrollBar*), AS_CALL_THISCALL);
    // bool ScrollView::GetVerticalScrollBarVisible() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "bool GetVerticalScrollBarVisible() const", AS_METHODPR(ListView, GetVerticalScrollBarVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_verticalScrollBarVisible() const", AS_METHODPR(ListView, GetVerticalScrollBarVisible, () const, bool), AS_CALL_THISCALL);
    // const IntVector2& ScrollView::GetViewPosition() const | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "const IntVector2& GetViewPosition() const", AS_METHODPR(ListView, GetViewPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "const IntVector2& get_viewPosition() const", AS_METHODPR(ListView, GetViewPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "int GetWidth() const", AS_METHODPR(ListView, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_width() const", AS_METHODPR(ListView, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool HasColorGradient() const", AS_METHODPR(ListView, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_colorGradient() const", AS_METHODPR(ListView, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "bool HasEventHandlers() const", AS_METHODPR(ListView, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool HasFocus() const", AS_METHODPR(ListView, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_focus() const", AS_METHODPR(ListView, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ListView, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ListView, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool HasTag(const String&in) const", AS_METHODPR(ListView, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void InsertChild(uint, UIElement@+)", AS_METHODPR(ListView, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // void ListView::InsertItem(unsigned index, UIElement* item, UIElement* parentItem=nullptr) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void InsertItem(uint, UIElement@+, UIElement@+ = null)", AS_METHODPR(ListView, InsertItem, (unsigned, UIElement*, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsChildOf(UIElement@+) const", AS_METHODPR(ListView, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsEditable() const", AS_METHODPR(ListView, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_editable() const", AS_METHODPR(ListView, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsElementEventSender() const", AS_METHODPR(ListView, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_elementEventSender() const", AS_METHODPR(ListView, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsEnabled() const", AS_METHODPR(ListView, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_enabled() const", AS_METHODPR(ListView, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsEnabledSelf() const", AS_METHODPR(ListView, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_enabledSelf() const", AS_METHODPR(ListView, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool ListView::IsExpanded(unsigned index) const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "bool IsExpanded(uint) const", AS_METHODPR(ListView, IsExpanded, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsFixedHeight() const", AS_METHODPR(ListView, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_fixedHeight() const", AS_METHODPR(ListView, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsFixedSize() const", AS_METHODPR(ListView, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_fixedSize() const", AS_METHODPR(ListView, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsFixedWidth() const", AS_METHODPR(ListView, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_fixedWidth() const", AS_METHODPR(ListView, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsHovering() const", AS_METHODPR(ListView, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_hovering() const", AS_METHODPR(ListView, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsInside(IntVector2, bool)", AS_METHODPR(ListView, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(ListView, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ListView, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsInternal() const", AS_METHODPR(ListView, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_internal() const", AS_METHODPR(ListView, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool ListView::IsSelected(unsigned index) const | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "bool IsSelected(uint) const", AS_METHODPR(ListView, IsSelected, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool IsTemporary() const", AS_METHODPR(ListView, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_temporary() const", AS_METHODPR(ListView, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsVisible() const", AS_METHODPR(ListView, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_visible() const", AS_METHODPR(ListView, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsVisibleEffective() const", AS_METHODPR(ListView, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool get_visibleEffective() const", AS_METHODPR(ListView, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // bool ScrollView::IsWheelHandler() const override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "bool IsWheelHandler() const", AS_METHODPR(ListView, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(ListView, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // explicit ListView::ListView(Context* context) | File: ../UI/ListView.h
    engine->RegisterObjectBehaviour("ListView", asBEHAVE_FACTORY, "ListView@+ f()", AS_FUNCTION(ListView_ListView_Context), AS_CALL_CDECL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool Load(Deserializer&)", AS_METHODPR(ListView, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(ListView, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ListView, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ListView, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(ListView, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool LoadXML(Deserializer&)", AS_METHODPR(ListView, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void MarkNetworkUpdate()", AS_METHODPR(ListView, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ListView, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(ListView, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ListView, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ListView, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(ListView, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(ListView, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(ListView, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(ListView, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ListView, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ListView, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ListView, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ListView, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnIndentSet()", AS_METHODPR(ListView, OnIndentSet, (), void), AS_CALL_THISCALL);
    // void ListView::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(ListView, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(ListView, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // void ListView::OnResize(const IntVector2& newSize, const IntVector2& delta) override | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(ListView, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ListView, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnSetEditable()", AS_METHODPR(ListView, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void OnTextInput(const String&in)", AS_METHODPR(ListView, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // void ScrollView::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(ListView, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ListView, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ListView, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ListView", "int Refs() const", AS_METHODPR(ListView, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_refs() const", AS_METHODPR(ListView, Refs, () const, int), AS_CALL_THISCALL);
    // static void ListView::RegisterObject(Context* context) | File: ../UI/ListView.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ListView", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ListView, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void Remove()", AS_METHODPR(ListView, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void RemoveAllChildren()", AS_METHODPR(ListView, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void ListView::RemoveAllItems() | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void RemoveAllItems()", AS_METHODPR(ListView, RemoveAllItems, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void RemoveAllTags()", AS_METHODPR(ListView, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ListView, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(ListView, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void RemoveChildAtIndex(uint)", AS_METHODPR(ListView, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void RemoveInstanceDefault()", AS_METHODPR(ListView, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void ListView::RemoveItem(UIElement* item, unsigned index=0) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void RemoveItem(UIElement@+, uint = 0)", AS_METHODPR(ListView, RemoveItem, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void ListView::RemoveItem(unsigned index) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void RemoveItem(uint)", AS_METHODPR(ListView, RemoveItem, (unsigned), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void RemoveObjectAnimation()", AS_METHODPR(ListView, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void ListView::RemoveSelection(unsigned index) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void RemoveSelection(uint)", AS_METHODPR(ListView, RemoveSelection, (unsigned), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool RemoveTag(const String&in)", AS_METHODPR(ListView, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void ResetDeepEnabled()", AS_METHODPR(ListView, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void ResetToDefault()", AS_METHODPR(ListView, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool Save(Serializer&) const", AS_METHODPR(ListView, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool SaveDefaultAttributes() const", AS_METHODPR(ListView, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ListView, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool SaveXML(XMLElement&) const", AS_METHODPR(ListView, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(ListView, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(ListView, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void SendEvent(StringHash)", AS_METHODPR(ListView, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ListView, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(ListView, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetAnimationEnabled(bool)", AS_METHODPR(ListView, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_animationEnabled(bool)", AS_METHODPR(ListView, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetAnimationTime(float)", AS_METHODPR(ListView, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ListView, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ListView, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ListView, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ListView, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ListView, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ListView, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ListView, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void ScrollView::SetAutoDisableChildren(bool disable) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetAutoDisableChildren(bool)", AS_METHODPR(ListView, SetAutoDisableChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_autoDisableChildren(bool)", AS_METHODPR(ListView, SetAutoDisableChildren, (bool), void), AS_CALL_THISCALL);
    // void ScrollView::SetAutoDisableThreshold(float amount) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetAutoDisableThreshold(float)", AS_METHODPR(ListView, SetAutoDisableThreshold, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_autoDisableThreshold(float)", AS_METHODPR(ListView, SetAutoDisableThreshold, (float), void), AS_CALL_THISCALL);
    // void ListView::SetBaseIndent(int baseIndent) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetBaseIndent(int)", AS_METHODPR(ListView, SetBaseIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_baseIndent(int)", AS_METHODPR(ListView, SetBaseIndent, (int), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void SetBlockEvents(bool)", AS_METHODPR(ListView, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetBringToBack(bool)", AS_METHODPR(ListView, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_bringToBack(bool)", AS_METHODPR(ListView, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetBringToFront(bool)", AS_METHODPR(ListView, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_bringToFront(bool)", AS_METHODPR(ListView, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(ListView, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void ListView::SetClearSelectionOnDefocus(bool enable) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetClearSelectionOnDefocus(bool)", AS_METHODPR(ListView, SetClearSelectionOnDefocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_clearSelectionOnDefocus(bool)", AS_METHODPR(ListView, SetClearSelectionOnDefocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetClipBorder(const IntRect&in)", AS_METHODPR(ListView, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_clipBorder(const IntRect&in)", AS_METHODPR(ListView, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetClipChildren(bool)", AS_METHODPR(ListView, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_clipChildren(bool)", AS_METHODPR(ListView, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetColor(const Color&in)", AS_METHODPR(ListView, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_color(const Color&in)", AS_METHODPR(ListView, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetColor(Corner, const Color&in)", AS_METHODPR(ListView, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_colors(Corner, const Color&in)", AS_METHODPR(ListView, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void ScrollView::SetContentElement(UIElement* element) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetContentElement(UIElement@+)", AS_METHODPR(ListView, SetContentElement, (UIElement*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_contentElement(UIElement@+)", AS_METHODPR(ListView, SetContentElement, (UIElement*), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetDeepEnabled(bool)", AS_METHODPR(ListView, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(ListView, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(ListView, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(ListView, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(ListView, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetEditable(bool)", AS_METHODPR(ListView, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_editable(bool)", AS_METHODPR(ListView, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetElementEventSender(bool)", AS_METHODPR(ListView, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_elementEventSender(bool)", AS_METHODPR(ListView, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetEnableAnchor(bool)", AS_METHODPR(ListView, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_enableAnchor(bool)", AS_METHODPR(ListView, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetEnabled(bool)", AS_METHODPR(ListView, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_enabled(bool)", AS_METHODPR(ListView, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetEnabledRecursive(bool)", AS_METHODPR(ListView, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetFixedHeight(int)", AS_METHODPR(ListView, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(ListView, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetFixedSize(int, int)", AS_METHODPR(ListView, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetFixedWidth(int)", AS_METHODPR(ListView, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetFocus(bool)", AS_METHODPR(ListView, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_focus(bool)", AS_METHODPR(ListView, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetFocusMode(FocusMode)", AS_METHODPR(ListView, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_focusMode(FocusMode)", AS_METHODPR(ListView, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ListView, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ListView, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetHeight(int)", AS_METHODPR(ListView, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_height(int)", AS_METHODPR(ListView, SetHeight, (int), void), AS_CALL_THISCALL);
    // void ListView::SetHierarchyMode(bool enable) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetHierarchyMode(bool)", AS_METHODPR(ListView, SetHierarchyMode, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_hierarchyMode(bool)", AS_METHODPR(ListView, SetHierarchyMode, (bool), void), AS_CALL_THISCALL);
    // void ListView::SetHighlightMode(HighlightMode mode) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetHighlightMode(HighlightMode)", AS_METHODPR(ListView, SetHighlightMode, (HighlightMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_highlightMode(HighlightMode)", AS_METHODPR(ListView, SetHighlightMode, (HighlightMode), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(ListView, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(ListView, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void ScrollView::SetHorizontalScrollBarVisible(bool visible) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetHorizontalScrollBarVisible(bool)", AS_METHODPR(ListView, SetHorizontalScrollBarVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_horizontalScrollBarVisible(bool)", AS_METHODPR(ListView, SetHorizontalScrollBarVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetHovering(bool)", AS_METHODPR(ListView, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetIndent(int)", AS_METHODPR(ListView, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_indent(int)", AS_METHODPR(ListView, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetIndentSpacing(int)", AS_METHODPR(ListView, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_indentSpacing(int)", AS_METHODPR(ListView, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void SetInstanceDefault(bool)", AS_METHODPR(ListView, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ListView, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetInternal(bool)", AS_METHODPR(ListView, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_internal(bool)", AS_METHODPR(ListView, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(ListView, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(ListView, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(ListView, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(ListView, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(ListView, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetLayoutMode(LayoutMode)", AS_METHODPR(ListView, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_layoutMode(LayoutMode)", AS_METHODPR(ListView, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetLayoutSpacing(int)", AS_METHODPR(ListView, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_layoutSpacing(int)", AS_METHODPR(ListView, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(ListView, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(ListView, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxAnchor(float, float)", AS_METHODPR(ListView, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxHeight(int)", AS_METHODPR(ListView, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_maxHeight(int)", AS_METHODPR(ListView, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(ListView, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(ListView, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(ListView, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_maxSize(const IntVector2&in)", AS_METHODPR(ListView, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxSize(int, int)", AS_METHODPR(ListView, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMaxWidth(int)", AS_METHODPR(ListView, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_maxWidth(int)", AS_METHODPR(ListView, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(ListView, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_minAnchor(const Vector2&in)", AS_METHODPR(ListView, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinAnchor(float, float)", AS_METHODPR(ListView, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinHeight(int)", AS_METHODPR(ListView, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_minHeight(int)", AS_METHODPR(ListView, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(ListView, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_minOffset(const IntVector2&in)", AS_METHODPR(ListView, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinSize(const IntVector2&in)", AS_METHODPR(ListView, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_minSize(const IntVector2&in)", AS_METHODPR(ListView, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinSize(int, int)", AS_METHODPR(ListView, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetMinWidth(int)", AS_METHODPR(ListView, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_minWidth(int)", AS_METHODPR(ListView, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void ListView::SetMultiselect(bool enable) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetMultiselect(bool)", AS_METHODPR(ListView, SetMultiselect, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_multiselect(bool)", AS_METHODPR(ListView, SetMultiselect, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetName(const String&in)", AS_METHODPR(ListView, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_name(const String&in)", AS_METHODPR(ListView, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ListView, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ListView, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ListView", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ListView, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetOpacity(float)", AS_METHODPR(ListView, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_opacity(float)", AS_METHODPR(ListView, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void ScrollView::SetPageStep(float step) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetPageStep(float)", AS_METHODPR(ListView, SetPageStep, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_pageStep(float)", AS_METHODPR(ListView, SetPageStep, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(ListView, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetPivot(const Vector2&in)", AS_METHODPR(ListView, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_pivot(const Vector2&in)", AS_METHODPR(ListView, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetPivot(float, float)", AS_METHODPR(ListView, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetPosition(const IntVector2&in)", AS_METHODPR(ListView, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_position(const IntVector2&in)", AS_METHODPR(ListView, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetPosition(int, int)", AS_METHODPR(ListView, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetPriority(int)", AS_METHODPR(ListView, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_priority(int)", AS_METHODPR(ListView, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(ListView, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void ScrollView::SetScrollBarsAutoVisible(bool enable) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetScrollBarsAutoVisible(bool)", AS_METHODPR(ListView, SetScrollBarsAutoVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_scrollBarsAutoVisible(bool)", AS_METHODPR(ListView, SetScrollBarsAutoVisible, (bool), void), AS_CALL_THISCALL);
    // void ScrollView::SetScrollBarsVisible(bool horizontal, bool vertical) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetScrollBarsVisible(bool, bool)", AS_METHODPR(ListView, SetScrollBarsVisible, (bool, bool), void), AS_CALL_THISCALL);
    // void ScrollView::SetScrollDeceleration(float deceleration) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetScrollDeceleration(float)", AS_METHODPR(ListView, SetScrollDeceleration, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_scrollDeceleration(float)", AS_METHODPR(ListView, SetScrollDeceleration, (float), void), AS_CALL_THISCALL);
    // void ScrollView::SetScrollSnapEpsilon(float snap) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetScrollSnapEpsilon(float)", AS_METHODPR(ListView, SetScrollSnapEpsilon, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_scrollSnapEpsilon(float)", AS_METHODPR(ListView, SetScrollSnapEpsilon, (float), void), AS_CALL_THISCALL);
    // void ScrollView::SetScrollStep(float step) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetScrollStep(float)", AS_METHODPR(ListView, SetScrollStep, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_scrollStep(float)", AS_METHODPR(ListView, SetScrollStep, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetSelected(bool)", AS_METHODPR(ListView, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_selected(bool)", AS_METHODPR(ListView, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void ListView::SetSelection(unsigned index) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetSelection(uint)", AS_METHODPR(ListView, SetSelection, (unsigned), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_selection(uint)", AS_METHODPR(ListView, SetSelection, (unsigned), void), AS_CALL_THISCALL);
    // void ListView::SetSelections(const PODVector<unsigned>& indices) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetSelections(Array<uint>@+)", AS_FUNCTION_OBJFIRST(ListView_SetSelections_PODVectorunsigned), AS_CALL_CDECL_OBJFIRST);
    // void ListView::SetSelectOnClickEnd(bool enable) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void SetSelectOnClickEnd(bool)", AS_METHODPR(ListView, SetSelectOnClickEnd, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_selectOnClickEnd(bool)", AS_METHODPR(ListView, SetSelectOnClickEnd, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetSize(const IntVector2&in)", AS_METHODPR(ListView, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_size(const IntVector2&in)", AS_METHODPR(ListView, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetSize(int, int)", AS_METHODPR(ListView, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetSortChildren(bool)", AS_METHODPR(ListView, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_sortChildren(bool)", AS_METHODPR(ListView, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(ListView, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool SetStyle(const XMLElement&in)", AS_METHODPR(ListView, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(ListView, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(ListView_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void SetTemporary(bool)", AS_METHODPR(ListView, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_temporary(bool)", AS_METHODPR(ListView, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetTraversalMode(TraversalMode)", AS_METHODPR(ListView, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_traversalMode(TraversalMode)", AS_METHODPR(ListView, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetUseDerivedOpacity(bool)", AS_METHODPR(ListView, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_useDerivedOpacity(bool)", AS_METHODPR(ListView, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(ListView, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(ListView, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(ListView, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void ScrollView::SetVerticalScrollBarVisible(bool visible) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetVerticalScrollBarVisible(bool)", AS_METHODPR(ListView, SetVerticalScrollBarVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_verticalScrollBarVisible(bool)", AS_METHODPR(ListView, SetVerticalScrollBarVisible, (bool), void), AS_CALL_THISCALL);
    // void ScrollView::SetViewPosition(const IntVector2& position) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetViewPosition(const IntVector2&in)", AS_METHODPR(ListView, SetViewPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_viewPosition(const IntVector2&in)", AS_METHODPR(ListView, SetViewPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void ScrollView::SetViewPosition(int x, int y) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetViewPosition(int, int)", AS_METHODPR(ListView, SetViewPosition, (int, int), void), AS_CALL_THISCALL);
    // void ScrollView::SetViewPositionAttr(const IntVector2& value) | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void SetViewPositionAttr(const IntVector2&in)", AS_METHODPR(ListView, SetViewPositionAttr, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetVisible(bool)", AS_METHODPR(ListView, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_visible(bool)", AS_METHODPR(ListView, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SetWidth(int)", AS_METHODPR(ListView, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "void set_width(int)", AS_METHODPR(ListView, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void SortChildren()", AS_METHODPR(ListView, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void ListView::ToggleExpand(unsigned index, bool recursive=false) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void ToggleExpand(uint, bool = false)", AS_METHODPR(ListView, ToggleExpand, (unsigned, bool), void), AS_CALL_THISCALL);
    // void ListView::ToggleSelection(unsigned index) | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void ToggleSelection(uint)", AS_METHODPR(ListView, ToggleSelection, (unsigned), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void UnsubscribeFromAllEvents()", AS_METHODPR(ListView, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ListView_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ListView, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ListView, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ListView", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ListView, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void ScrollView::Update(float timeStep) override | File: ../UI/ScrollView.h
    engine->RegisterObjectMethod("ListView", "void Update(float)", AS_METHODPR(ListView, Update, (float), void), AS_CALL_THISCALL);
    // void ListView::UpdateInternalLayout() | File: ../UI/ListView.h
    engine->RegisterObjectMethod("ListView", "void UpdateInternalLayout()", AS_METHODPR(ListView, UpdateInternalLayout, (), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ListView", "void UpdateLayout()", AS_METHODPR(ListView, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ListView", "int WeakRefs() const", AS_METHODPR(ListView, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ListView", "int get_weakRefs() const", AS_METHODPR(ListView, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ListView, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ListView, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ListView", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ListView, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Localization", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Localization, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // String Localization::Get(const String& id) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "String Get(const String&in)", AS_METHODPR(Localization, Get, (const String&), String), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "bool GetBlockEvents() const", AS_METHODPR(Localization, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "const String& GetCategory() const", AS_METHODPR(Localization, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "const String& get_category() const", AS_METHODPR(Localization, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "VariantMap& GetEventDataMap() const", AS_METHODPR(Localization, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "Object@+ GetEventSender() const", AS_METHODPR(Localization, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Localization, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Localization, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Localization, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "const VariantMap& get_globalVars() const", AS_METHODPR(Localization, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // String Localization::GetLanguage() | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "String GetLanguage()", AS_METHODPR(Localization, GetLanguage, (), String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "String get_language()", AS_METHODPR(Localization, GetLanguage, (), String), AS_CALL_THISCALL);
    // String Localization::GetLanguage(int index) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "String GetLanguage(int)", AS_METHODPR(Localization, GetLanguage, (int), String), AS_CALL_THISCALL);
    // int Localization::GetLanguageIndex() const | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "int GetLanguageIndex() const", AS_METHODPR(Localization, GetLanguageIndex, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "int get_languageIndex() const", AS_METHODPR(Localization, GetLanguageIndex, () const, int), AS_CALL_THISCALL);
    // int Localization::GetLanguageIndex(const String& language) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "int GetLanguageIndex(const String&in)", AS_METHODPR(Localization, GetLanguageIndex, (const String&), int), AS_CALL_THISCALL);
    // int Localization::GetNumLanguages() const | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "int GetNumLanguages() const", AS_METHODPR(Localization, GetNumLanguages, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "int get_numLanguages() const", AS_METHODPR(Localization, GetNumLanguages, () const, int), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Localization, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "StringHash GetType() const", AS_METHODPR(Localization, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "StringHash get_type() const", AS_METHODPR(Localization, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "const String& GetTypeName() const", AS_METHODPR(Localization, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "const String& get_typeName() const", AS_METHODPR(Localization, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "bool HasEventHandlers() const", AS_METHODPR(Localization, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Localization, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Localization, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Localization, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // void Localization::LoadJSONFile(const String& name, const String& language=String::EMPTY) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "void LoadJSONFile(const String&in, const String&in = String::EMPTY)", AS_METHODPR(Localization, LoadJSONFile, (const String&, const String&), void), AS_CALL_THISCALL);
    // void Localization::LoadMultipleLanguageJSON(const JSONValue& source) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "void LoadMultipleLanguageJSON(const JSONValue&in)", AS_METHODPR(Localization, LoadMultipleLanguageJSON, (const JSONValue&), void), AS_CALL_THISCALL);
    // void Localization::LoadSingleLanguageJSON(const JSONValue& source, const String& language=String::EMPTY) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "void LoadSingleLanguageJSON(const JSONValue&in, const String&in = String::EMPTY)", AS_METHODPR(Localization, LoadSingleLanguageJSON, (const JSONValue&, const String&), void), AS_CALL_THISCALL);
    // explicit Localization::Localization(Context* context) | File: ../Resource/Localization.h
    engine->RegisterObjectBehaviour("Localization", asBEHAVE_FACTORY, "Localization@+ f()", AS_FUNCTION(Localization_Localization_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Localization, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Localization", "int Refs() const", AS_METHODPR(Localization, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "int get_refs() const", AS_METHODPR(Localization, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Localization", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Localization, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Localization::Reset() | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "void Reset()", AS_METHODPR(Localization, Reset, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void SendEvent(StringHash)", AS_METHODPR(Localization, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Localization, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void SetBlockEvents(bool)", AS_METHODPR(Localization, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Localization, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Localization, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Localization::SetLanguage(int index) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "void SetLanguage(int)", AS_METHODPR(Localization, SetLanguage, (int), void), AS_CALL_THISCALL);
    // void Localization::SetLanguage(const String& language) | File: ../Resource/Localization.h
    engine->RegisterObjectMethod("Localization", "void SetLanguage(const String&in)", AS_METHODPR(Localization, SetLanguage, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void UnsubscribeFromAllEvents()", AS_METHODPR(Localization, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Localization_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Localization, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Localization, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Localization", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Localization, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Localization", "int WeakRefs() const", AS_METHODPR(Localization, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Localization", "int get_weakRefs() const", AS_METHODPR(Localization, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("Log", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Log, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Log::Close() | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "void Close()", AS_METHODPR(Log, Close, (), void), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "bool GetBlockEvents() const", AS_METHODPR(Log, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "const String& GetCategory() const", AS_METHODPR(Log, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "const String& get_category() const", AS_METHODPR(Log, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "VariantMap& GetEventDataMap() const", AS_METHODPR(Log, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "Object@+ GetEventSender() const", AS_METHODPR(Log, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Log, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Log, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Log, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "const VariantMap& get_globalVars() const", AS_METHODPR(Log, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // String Log::GetLastMessage() const | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "String GetLastMessage() const", AS_METHODPR(Log, GetLastMessage, () const, String), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "String get_lastMessage() const", AS_METHODPR(Log, GetLastMessage, () const, String), AS_CALL_THISCALL);
    // int Log::GetLevel() const | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "int GetLevel() const", AS_METHODPR(Log, GetLevel, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "int get_level() const", AS_METHODPR(Log, GetLevel, () const, int), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Log, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // bool Log::GetTimeStamp() const | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "bool GetTimeStamp() const", AS_METHODPR(Log, GetTimeStamp, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "bool get_timeStamp() const", AS_METHODPR(Log, GetTimeStamp, () const, bool), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "StringHash GetType() const", AS_METHODPR(Log, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "StringHash get_type() const", AS_METHODPR(Log, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "const String& GetTypeName() const", AS_METHODPR(Log, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "const String& get_typeName() const", AS_METHODPR(Log, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "bool HasEventHandlers() const", AS_METHODPR(Log, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Log, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Log, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Log, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Log::IsQuiet() const | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "bool IsQuiet() const", AS_METHODPR(Log, IsQuiet, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "bool get_quiet() const", AS_METHODPR(Log, IsQuiet, () const, bool), AS_CALL_THISCALL);
    // explicit Log::Log(Context* context) | File: ../IO/Log.h
    engine->RegisterObjectBehaviour("Log", asBEHAVE_FACTORY, "Log@+ f()", AS_FUNCTION(Log_Log_Context), AS_CALL_CDECL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Log, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // void Log::Open(const String& fileName) | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "void Open(const String&in)", AS_METHODPR(Log, Open, (const String&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Log", "int Refs() const", AS_METHODPR(Log, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "int get_refs() const", AS_METHODPR(Log, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Log", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Log, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void SendEvent(StringHash)", AS_METHODPR(Log, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Log, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void SetBlockEvents(bool)", AS_METHODPR(Log, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Log, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Log, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Log::SetLevel(int level) | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "void SetLevel(int)", AS_METHODPR(Log, SetLevel, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "void set_level(int)", AS_METHODPR(Log, SetLevel, (int), void), AS_CALL_THISCALL);
    // void Log::SetQuiet(bool quiet) | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "void SetQuiet(bool)", AS_METHODPR(Log, SetQuiet, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "void set_quiet(bool)", AS_METHODPR(Log, SetQuiet, (bool), void), AS_CALL_THISCALL);
    // void Log::SetTimeStamp(bool enable) | File: ../IO/Log.h
    engine->RegisterObjectMethod("Log", "void SetTimeStamp(bool)", AS_METHODPR(Log, SetTimeStamp, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "void set_timeStamp(bool)", AS_METHODPR(Log, SetTimeStamp, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void UnsubscribeFromAllEvents()", AS_METHODPR(Log, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Log_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Log, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Log, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Log", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Log, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Log", "int WeakRefs() const", AS_METHODPR(Log, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Log", "int get_weakRefs() const", AS_METHODPR(Log, WeakRefs, () const, int), AS_CALL_THISCALL);
    // static void Log::Write(int level, const String& message) | File: ../IO/Log.h
    // Not registered because have @nobind mark
    // static void Log::WriteFormat(int level, const char* format,...) | File: ../IO/Log.h
    // Error: type "const char*" can not automatically bind
    // static void Log::WriteRaw(const String& message, bool error=false) | File: ../IO/Log.h
    engine->SetDefaultNamespace("Log");
    engine->RegisterGlobalFunction("void WriteRaw(const String&in, bool = false)", AS_FUNCTIONPR(Log::WriteRaw, (const String&, bool), void), AS_CALL_CDECL);
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
    engine->RegisterObjectBehaviour("LogicComponent", asBEHAVE_ADDREF, "void f()", AS_METHODPR(LogicComponent, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void AllocateNetworkState()", AS_METHODPR(LogicComponent, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void ApplyAttributes()", AS_METHODPR(LogicComponent, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(LogicComponent, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "bool GetAnimationEnabled() const", AS_METHODPR(LogicComponent, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "bool get_animationEnabled() const", AS_METHODPR(LogicComponent, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "Variant GetAttribute(uint) const", AS_METHODPR(LogicComponent, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "Variant get_attributes(uint) const", AS_METHODPR(LogicComponent, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "Variant GetAttribute(const String&in) const", AS_METHODPR(LogicComponent, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(LogicComponent, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(LogicComponent, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(LogicComponent, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(LogicComponent, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "Variant GetAttributeDefault(uint) const", AS_METHODPR(LogicComponent, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "Variant get_attributeDefaults(uint) const", AS_METHODPR(LogicComponent, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(LogicComponent, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "bool GetBlockEvents() const", AS_METHODPR(LogicComponent, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "const String& GetCategory() const", AS_METHODPR(LogicComponent, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "const String& get_category() const", AS_METHODPR(LogicComponent, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "Component@+ GetComponent(StringHash) const", AS_METHODPR(LogicComponent, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("LogicComponent", "VariantMap& GetEventDataMap() const", AS_METHODPR(LogicComponent, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "Object@+ GetEventSender() const", AS_METHODPR(LogicComponent, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(LogicComponent, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(LogicComponent, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "const VariantMap& GetGlobalVars() const", AS_METHODPR(LogicComponent, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "const VariantMap& get_globalVars() const", AS_METHODPR(LogicComponent, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "uint GetID() const", AS_METHODPR(LogicComponent, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "uint get_id() const", AS_METHODPR(LogicComponent, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(LogicComponent, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "Node@+ GetNode() const", AS_METHODPR(LogicComponent, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "Node@+ get_node() const", AS_METHODPR(LogicComponent, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "uint GetNumAttributes() const", AS_METHODPR(LogicComponent, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "uint get_numAttributes() const", AS_METHODPR(LogicComponent, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "uint GetNumNetworkAttributes() const", AS_METHODPR(LogicComponent, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(LogicComponent, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(LogicComponent, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(LogicComponent, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "Scene@+ GetScene() const", AS_METHODPR(LogicComponent, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(LogicComponent, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "StringHash GetType() const", AS_METHODPR(LogicComponent, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "StringHash get_type() const", AS_METHODPR(LogicComponent, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "const String& GetTypeName() const", AS_METHODPR(LogicComponent, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "const String& get_typeName() const", AS_METHODPR(LogicComponent, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "bool HasEventHandlers() const", AS_METHODPR(LogicComponent, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(LogicComponent, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(LogicComponent, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "bool IsEnabled() const", AS_METHODPR(LogicComponent, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "bool get_enabled() const", AS_METHODPR(LogicComponent, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "bool IsEnabledEffective() const", AS_METHODPR(LogicComponent, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "bool get_enabledEffective() const", AS_METHODPR(LogicComponent, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "bool IsInstanceOf(StringHash) const", AS_METHODPR(LogicComponent, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "bool IsReplicated() const", AS_METHODPR(LogicComponent, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "bool get_replicated() const", AS_METHODPR(LogicComponent, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool IsTemporary() const", AS_METHODPR(LogicComponent, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "bool get_temporary() const", AS_METHODPR(LogicComponent, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool Load(Deserializer&)", AS_METHODPR(LogicComponent, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(LogicComponent, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "bool LoadXML(const XMLElement&in)", AS_METHODPR(LogicComponent, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "void MarkNetworkUpdate()", AS_METHODPR(LogicComponent, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(LogicComponent, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(LogicComponent, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(LogicComponent, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "void PrepareNetworkUpdate()", AS_METHODPR(LogicComponent, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(LogicComponent, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(LogicComponent, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("LogicComponent", "int Refs() const", AS_METHODPR(LogicComponent, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "int get_refs() const", AS_METHODPR(LogicComponent, Refs, () const, int), AS_CALL_THISCALL);
    // static void Animatable::RegisterObject(Context* context) | File: ../Scene/Animatable.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("LogicComponent", asBEHAVE_RELEASE, "void f()", AS_METHODPR(LogicComponent, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "void Remove()", AS_METHODPR(LogicComponent, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(LogicComponent, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void RemoveInstanceDefault()", AS_METHODPR(LogicComponent, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void RemoveObjectAnimation()", AS_METHODPR(LogicComponent, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void ResetToDefault()", AS_METHODPR(LogicComponent, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "bool Save(Serializer&) const", AS_METHODPR(LogicComponent, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool SaveDefaultAttributes() const", AS_METHODPR(LogicComponent, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "bool SaveJSON(JSONValue&) const", AS_METHODPR(LogicComponent, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "bool SaveXML(XMLElement&) const", AS_METHODPR(LogicComponent, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void SendEvent(StringHash)", AS_METHODPR(LogicComponent, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(LogicComponent, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetAnimationEnabled(bool)", AS_METHODPR(LogicComponent, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "void set_animationEnabled(bool)", AS_METHODPR(LogicComponent, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetAnimationTime(float)", AS_METHODPR(LogicComponent, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(LogicComponent, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(LogicComponent, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(LogicComponent, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(LogicComponent, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(LogicComponent, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(LogicComponent, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(LogicComponent, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void SetBlockEvents(bool)", AS_METHODPR(LogicComponent, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("LogicComponent", "void SetEnabled(bool)", AS_METHODPR(LogicComponent, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "void set_enabled(bool)", AS_METHODPR(LogicComponent, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(LogicComponent, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(LogicComponent, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetInstanceDefault(bool)", AS_METHODPR(LogicComponent, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(LogicComponent, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(LogicComponent, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(LogicComponent, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(LogicComponent, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void SetTemporary(bool)", AS_METHODPR(LogicComponent, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "void set_temporary(bool)", AS_METHODPR(LogicComponent, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void UnsubscribeFromAllEvents()", AS_METHODPR(LogicComponent, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(LogicComponent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(LogicComponent, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(LogicComponent, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("LogicComponent", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(LogicComponent, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("LogicComponent", "int WeakRefs() const", AS_METHODPR(LogicComponent, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("LogicComponent", "int get_weakRefs() const", AS_METHODPR(LogicComponent, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(LogicComponent, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(LogicComponent, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("LogicComponent", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(LogicComponent, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("ListIteratorBase", "void GotoNext()", AS_METHODPR(ListIteratorBase, GotoNext, (), void), AS_CALL_THISCALL);
    // void ListIteratorBase::GotoPrev() | File: ../Container/ListBase.h
    engine->RegisterObjectMethod("ListIteratorBase", "void GotoPrev()", AS_METHODPR(ListIteratorBase, GotoPrev, (), void), AS_CALL_THISCALL);
    // explicit ListIteratorBase::ListIteratorBase(ListNodeBase* ptr) | File: ../Container/ListBase.h
    // Error: type "ListNodeBase*" can not automatically bind
    // bool ListIteratorBase::operator==(const ListIteratorBase& rhs) const | File: ../Container/ListBase.h
    engine->RegisterObjectMethod("ListIteratorBase", "bool opEquals(const ListIteratorBase&in) const", AS_METHODPR(ListIteratorBase, operator==, (const ListIteratorBase&) const, bool), AS_CALL_THISCALL);
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
