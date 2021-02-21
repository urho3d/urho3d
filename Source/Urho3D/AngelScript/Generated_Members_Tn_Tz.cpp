// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void ToolTip_AddTags_StringVector(ToolTip* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* ToolTip_GetChildren_void(ToolTip* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* ToolTip_GetChildren_bool(ToolTip* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* ToolTip_GetChildrenWithTag_String_bool(ToolTip* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* ToolTip_GetTags_void(ToolTip* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void ToolTip_SetTags_StringVector(ToolTip* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// explicit ToolTip::ToolTip(Context* context) | File: ../UI/ToolTip.h
static ToolTip* ToolTip_ToolTip_Context()
{
    return new ToolTip(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void ToolTip_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(ToolTip* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// TrailPoint::TrailPoint(const Vector3& position, const Vector3& forward) | File: ../Graphics/RibbonTrail.h
static void TrailPoint_TrailPoint_Vector3_Vector3(TrailPoint* ptr, const Vector3 &position, const Vector3 &forward)
{
    new(ptr) TrailPoint(position, forward);
}

#ifdef URHO3D_PHYSICS
// TriangleMeshData::TriangleMeshData(Model* model, unsigned lodLevel) | File: ../Physics/CollisionShape.h
static TriangleMeshData* TriangleMeshData_TriangleMeshData_Model_unsigned(Model *model, unsigned lodLevel)
{
    return new TriangleMeshData(model, lodLevel);
}
#endif

#ifdef URHO3D_PHYSICS
// explicit TriangleMeshData::TriangleMeshData(CustomGeometry* custom) | File: ../Physics/CollisionShape.h
static TriangleMeshData* TriangleMeshData_TriangleMeshData_CustomGeometry(CustomGeometry *custom)
{
    return new TriangleMeshData(custom);
}
#endif

void ASRegisterGenerated_Members_Tn_Tz(asIScriptEngine* engine)
{
    // void ToolTip::AddAltTarget(UIElement* target) | File: ../UI/ToolTip.h
    engine->RegisterObjectMethod("ToolTip", "void AddAltTarget(UIElement@+)", AS_METHODPR(ToolTip, AddAltTarget, (UIElement*), void), AS_CALL_THISCALL);
    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void AddChild(UIElement@+)", AS_METHODPR(ToolTip, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ToolTip", asBEHAVE_ADDREF, "void f()", AS_METHODPR(ToolTip, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void AddTag(const String&in)", AS_METHODPR(ToolTip, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(ToolTip, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(ToolTip_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void AdjustScissor(IntRect&)", AS_METHODPR(ToolTip, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void AllocateNetworkState()", AS_METHODPR(ToolTip, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void ApplyAttributes()", AS_METHODPR(ToolTip, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void BringToFront()", AS_METHODPR(ToolTip, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(ToolTip, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void DisableLayoutUpdate()", AS_METHODPR(ToolTip, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(ToolTip, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void EnableLayoutUpdate()", AS_METHODPR(ToolTip, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(ToolTip, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "uint FindChild(UIElement@+) const", AS_METHODPR(ToolTip, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "bool GetAnimationEnabled() const", AS_METHODPR(ToolTip, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_animationEnabled() const", AS_METHODPR(ToolTip, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const String& GetAppliedStyle() const", AS_METHODPR(ToolTip, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const String& get_style() const", AS_METHODPR(ToolTip, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "Variant GetAttribute(uint) const", AS_METHODPR(ToolTip, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "Variant get_attributes(uint) const", AS_METHODPR(ToolTip, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "Variant GetAttribute(const String&in) const", AS_METHODPR(ToolTip, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(ToolTip, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(ToolTip, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(ToolTip, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(ToolTip, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "Variant GetAttributeDefault(uint) const", AS_METHODPR(ToolTip, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "Variant get_attributeDefaults(uint) const", AS_METHODPR(ToolTip, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(ToolTip, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // virtual void UIElement::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "bool GetBlockEvents() const", AS_METHODPR(ToolTip, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool GetBringToBack() const", AS_METHODPR(ToolTip, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_bringToBack() const", AS_METHODPR(ToolTip, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool GetBringToFront() const", AS_METHODPR(ToolTip, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_bringToFront() const", AS_METHODPR(ToolTip, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "const String& GetCategory() const", AS_METHODPR(ToolTip, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const String& get_category() const", AS_METHODPR(ToolTip, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ GetChild(uint) const", AS_METHODPR(ToolTip, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ get_children(uint) const", AS_METHODPR(ToolTip, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(ToolTip, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(ToolTip, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetChildOffset() const", AS_METHODPR(ToolTip, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_childOffset() const", AS_METHODPR(ToolTip, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(ToolTip_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(ToolTip_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(ToolTip_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntRect& GetClipBorder() const", AS_METHODPR(ToolTip, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntRect& get_clipBorder() const", AS_METHODPR(ToolTip, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool GetClipChildren() const", AS_METHODPR(ToolTip, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_clipChildren() const", AS_METHODPR(ToolTip, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Color& GetColor(Corner) const", AS_METHODPR(ToolTip, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const Color& get_colors(Corner) const", AS_METHODPR(ToolTip, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Color& GetColorAttr() const", AS_METHODPR(ToolTip, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "IntRect GetCombinedScreenRect()", AS_METHODPR(ToolTip, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "IntRect get_combinedScreenRect()", AS_METHODPR(ToolTip, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(ToolTip, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // float ToolTip::GetDelay() const | File: ../UI/ToolTip.h
    engine->RegisterObjectMethod("ToolTip", "float GetDelay() const", AS_METHODPR(ToolTip, GetDelay, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "float get_delay() const", AS_METHODPR(ToolTip, GetDelay, () const, float), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Color& GetDerivedColor() const", AS_METHODPR(ToolTip, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "float GetDerivedOpacity() const", AS_METHODPR(ToolTip, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "float get_derivedOpacity() const", AS_METHODPR(ToolTip, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(ToolTip, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(ToolTip, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "uint GetDragButtonCount() const", AS_METHODPR(ToolTip, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "uint get_dragButtonCount() const", AS_METHODPR(ToolTip, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(ToolTip, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(ToolTip, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(ToolTip, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ GetElementEventSender() const", AS_METHODPR(ToolTip, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool GetEnableAnchor() const", AS_METHODPR(ToolTip, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_enableAnchor() const", AS_METHODPR(ToolTip, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "VariantMap& GetEventDataMap() const", AS_METHODPR(ToolTip, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "Object@+ GetEventSender() const", AS_METHODPR(ToolTip, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "FocusMode GetFocusMode() const", AS_METHODPR(ToolTip, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "FocusMode get_focusMode() const", AS_METHODPR(ToolTip, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(ToolTip, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(ToolTip, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "const VariantMap& GetGlobalVars() const", AS_METHODPR(ToolTip, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const VariantMap& get_globalVars() const", AS_METHODPR(ToolTip, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetHeight() const", AS_METHODPR(ToolTip, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_height() const", AS_METHODPR(ToolTip, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(ToolTip, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(ToolTip, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetIndent() const", AS_METHODPR(ToolTip, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_indent() const", AS_METHODPR(ToolTip, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetIndentSpacing() const", AS_METHODPR(ToolTip, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_indentSpacing() const", AS_METHODPR(ToolTip, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetIndentWidth() const", AS_METHODPR(ToolTip, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_indentWidth() const", AS_METHODPR(ToolTip, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(ToolTip, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntRect& GetLayoutBorder() const", AS_METHODPR(ToolTip, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntRect& get_layoutBorder() const", AS_METHODPR(ToolTip, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetLayoutElementMaxSize() const", AS_METHODPR(ToolTip, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(ToolTip, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(ToolTip, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "LayoutMode GetLayoutMode() const", AS_METHODPR(ToolTip, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "LayoutMode get_layoutMode() const", AS_METHODPR(ToolTip, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetLayoutSpacing() const", AS_METHODPR(ToolTip, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_layoutSpacing() const", AS_METHODPR(ToolTip, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Vector2& GetMaxAnchor() const", AS_METHODPR(ToolTip, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const Vector2& get_maxAnchor() const", AS_METHODPR(ToolTip, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetMaxHeight() const", AS_METHODPR(ToolTip, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_maxHeight() const", AS_METHODPR(ToolTip, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetMaxOffset() const", AS_METHODPR(ToolTip, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_maxOffset() const", AS_METHODPR(ToolTip, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetMaxSize() const", AS_METHODPR(ToolTip, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_maxSize() const", AS_METHODPR(ToolTip, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetMaxWidth() const", AS_METHODPR(ToolTip, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_maxWidth() const", AS_METHODPR(ToolTip, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Vector2& GetMinAnchor() const", AS_METHODPR(ToolTip, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const Vector2& get_minAnchor() const", AS_METHODPR(ToolTip, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetMinHeight() const", AS_METHODPR(ToolTip, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_minHeight() const", AS_METHODPR(ToolTip, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetMinOffset() const", AS_METHODPR(ToolTip, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_minOffset() const", AS_METHODPR(ToolTip, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetMinSize() const", AS_METHODPR(ToolTip, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_minSize() const", AS_METHODPR(ToolTip, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetMinWidth() const", AS_METHODPR(ToolTip, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_minWidth() const", AS_METHODPR(ToolTip, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const String& GetName() const", AS_METHODPR(ToolTip, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const String& get_name() const", AS_METHODPR(ToolTip, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "uint GetNumAttributes() const", AS_METHODPR(ToolTip, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "uint get_numAttributes() const", AS_METHODPR(ToolTip, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "uint GetNumChildren(bool = false) const", AS_METHODPR(ToolTip, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "uint get_numChildren(bool = false) const", AS_METHODPR(ToolTip, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "uint GetNumNetworkAttributes() const", AS_METHODPR(ToolTip, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(ToolTip, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(ToolTip, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(ToolTip, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "float GetOpacity() const", AS_METHODPR(ToolTip, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "float get_opacity() const", AS_METHODPR(ToolTip, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ GetParent() const", AS_METHODPR(ToolTip, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ get_parent() const", AS_METHODPR(ToolTip, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Vector2& GetPivot() const", AS_METHODPR(ToolTip, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const Vector2& get_pivot() const", AS_METHODPR(ToolTip, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetPosition() const", AS_METHODPR(ToolTip, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_position() const", AS_METHODPR(ToolTip, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetPriority() const", AS_METHODPR(ToolTip, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_priority() const", AS_METHODPR(ToolTip, GetPriority, () const, int), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ GetRoot() const", AS_METHODPR(ToolTip, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ get_root() const", AS_METHODPR(ToolTip, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetScreenPosition() const", AS_METHODPR(ToolTip, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_screenPosition() const", AS_METHODPR(ToolTip, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetSize() const", AS_METHODPR(ToolTip, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_size() const", AS_METHODPR(ToolTip, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool GetSortChildren() const", AS_METHODPR(ToolTip, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_sortChildren() const", AS_METHODPR(ToolTip, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(ToolTip, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(ToolTip_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ToolTip", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(ToolTip_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "TraversalMode GetTraversalMode() const", AS_METHODPR(ToolTip, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "TraversalMode get_traversalMode() const", AS_METHODPR(ToolTip, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "StringHash GetType() const", AS_METHODPR(ToolTip, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "StringHash get_type() const", AS_METHODPR(ToolTip, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "const String& GetTypeName() const", AS_METHODPR(ToolTip, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const String& get_typeName() const", AS_METHODPR(ToolTip, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool GetUseDerivedOpacity() const", AS_METHODPR(ToolTip, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_useDerivedOpacity() const", AS_METHODPR(ToolTip, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(ToolTip, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const VariantMap& GetVars() const", AS_METHODPR(ToolTip, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(ToolTip, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(ToolTip, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetWidth() const", AS_METHODPR(ToolTip, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_width() const", AS_METHODPR(ToolTip, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool HasColorGradient() const", AS_METHODPR(ToolTip, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_colorGradient() const", AS_METHODPR(ToolTip, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "bool HasEventHandlers() const", AS_METHODPR(ToolTip, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool HasFocus() const", AS_METHODPR(ToolTip, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_focus() const", AS_METHODPR(ToolTip, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(ToolTip, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(ToolTip, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool HasTag(const String&in) const", AS_METHODPR(ToolTip, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void InsertChild(uint, UIElement@+)", AS_METHODPR(ToolTip, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsChildOf(UIElement@+) const", AS_METHODPR(ToolTip, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsEditable() const", AS_METHODPR(ToolTip, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_editable() const", AS_METHODPR(ToolTip, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsElementEventSender() const", AS_METHODPR(ToolTip, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_elementEventSender() const", AS_METHODPR(ToolTip, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsEnabled() const", AS_METHODPR(ToolTip, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_enabled() const", AS_METHODPR(ToolTip, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsEnabledSelf() const", AS_METHODPR(ToolTip, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_enabledSelf() const", AS_METHODPR(ToolTip, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsFixedHeight() const", AS_METHODPR(ToolTip, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_fixedHeight() const", AS_METHODPR(ToolTip, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsFixedSize() const", AS_METHODPR(ToolTip, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_fixedSize() const", AS_METHODPR(ToolTip, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsFixedWidth() const", AS_METHODPR(ToolTip, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_fixedWidth() const", AS_METHODPR(ToolTip, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsHovering() const", AS_METHODPR(ToolTip, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_hovering() const", AS_METHODPR(ToolTip, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsInside(IntVector2, bool)", AS_METHODPR(ToolTip, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(ToolTip, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "bool IsInstanceOf(StringHash) const", AS_METHODPR(ToolTip, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsInternal() const", AS_METHODPR(ToolTip, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_internal() const", AS_METHODPR(ToolTip, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsSelected() const", AS_METHODPR(ToolTip, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_selected() const", AS_METHODPR(ToolTip, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool IsTemporary() const", AS_METHODPR(ToolTip, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_temporary() const", AS_METHODPR(ToolTip, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsVisible() const", AS_METHODPR(ToolTip, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_visible() const", AS_METHODPR(ToolTip, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsVisibleEffective() const", AS_METHODPR(ToolTip, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_visibleEffective() const", AS_METHODPR(ToolTip, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsWheelHandler() const", AS_METHODPR(ToolTip, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(ToolTip, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool Load(Deserializer&)", AS_METHODPR(ToolTip, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(ToolTip, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(ToolTip, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool LoadXML(const XMLElement&in)", AS_METHODPR(ToolTip, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(ToolTip, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool LoadXML(Deserializer&)", AS_METHODPR(ToolTip, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void MarkNetworkUpdate()", AS_METHODPR(ToolTip, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ToolTip, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(ToolTip, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ToolTip, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ToolTip, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(ToolTip, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(ToolTip, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(ToolTip, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(ToolTip, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ToolTip, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(ToolTip, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(ToolTip, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(ToolTip, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnIndentSet()", AS_METHODPR(ToolTip, OnIndentSet, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(ToolTip, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(ToolTip, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(ToolTip, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(ToolTip, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnSetEditable()", AS_METHODPR(ToolTip, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnTextInput(const String&in)", AS_METHODPR(ToolTip, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(ToolTip, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(ToolTip, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(ToolTip, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ToolTip", "int Refs() const", AS_METHODPR(ToolTip, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_refs() const", AS_METHODPR(ToolTip, Refs, () const, int), AS_CALL_THISCALL);
    // static void ToolTip::RegisterObject(Context* context) | File: ../UI/ToolTip.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ToolTip", asBEHAVE_RELEASE, "void f()", AS_METHODPR(ToolTip, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void Remove()", AS_METHODPR(ToolTip, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveAllChildren()", AS_METHODPR(ToolTip, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveAllTags()", AS_METHODPR(ToolTip, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(ToolTip, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(ToolTip, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveChildAtIndex(uint)", AS_METHODPR(ToolTip, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveInstanceDefault()", AS_METHODPR(ToolTip, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveObjectAnimation()", AS_METHODPR(ToolTip, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool RemoveTag(const String&in)", AS_METHODPR(ToolTip, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void ToolTip::Reset() | File: ../UI/ToolTip.h
    engine->RegisterObjectMethod("ToolTip", "void Reset()", AS_METHODPR(ToolTip, Reset, (), void), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void ResetDeepEnabled()", AS_METHODPR(ToolTip, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void ResetToDefault()", AS_METHODPR(ToolTip, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool Save(Serializer&) const", AS_METHODPR(ToolTip, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool SaveDefaultAttributes() const", AS_METHODPR(ToolTip, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "bool SaveJSON(JSONValue&) const", AS_METHODPR(ToolTip, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool SaveXML(XMLElement&) const", AS_METHODPR(ToolTip, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(ToolTip, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(ToolTip, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void SendEvent(StringHash)", AS_METHODPR(ToolTip, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(ToolTip, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(ToolTip, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetAnimationEnabled(bool)", AS_METHODPR(ToolTip, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_animationEnabled(bool)", AS_METHODPR(ToolTip, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetAnimationTime(float)", AS_METHODPR(ToolTip, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(ToolTip, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(ToolTip, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(ToolTip, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(ToolTip, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(ToolTip, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(ToolTip, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(ToolTip, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void SetBlockEvents(bool)", AS_METHODPR(ToolTip, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetBringToBack(bool)", AS_METHODPR(ToolTip, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_bringToBack(bool)", AS_METHODPR(ToolTip, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetBringToFront(bool)", AS_METHODPR(ToolTip, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_bringToFront(bool)", AS_METHODPR(ToolTip, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(ToolTip, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetClipBorder(const IntRect&in)", AS_METHODPR(ToolTip, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_clipBorder(const IntRect&in)", AS_METHODPR(ToolTip, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetClipChildren(bool)", AS_METHODPR(ToolTip, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_clipChildren(bool)", AS_METHODPR(ToolTip, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetColor(const Color&in)", AS_METHODPR(ToolTip, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_color(const Color&in)", AS_METHODPR(ToolTip, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetColor(Corner, const Color&in)", AS_METHODPR(ToolTip, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_colors(Corner, const Color&in)", AS_METHODPR(ToolTip, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetDeepEnabled(bool)", AS_METHODPR(ToolTip, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(ToolTip, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(ToolTip, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void ToolTip::SetDelay(float delay) | File: ../UI/ToolTip.h
    engine->RegisterObjectMethod("ToolTip", "void SetDelay(float)", AS_METHODPR(ToolTip, SetDelay, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_delay(float)", AS_METHODPR(ToolTip, SetDelay, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(ToolTip, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(ToolTip, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetEditable(bool)", AS_METHODPR(ToolTip, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_editable(bool)", AS_METHODPR(ToolTip, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetElementEventSender(bool)", AS_METHODPR(ToolTip, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_elementEventSender(bool)", AS_METHODPR(ToolTip, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetEnableAnchor(bool)", AS_METHODPR(ToolTip, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_enableAnchor(bool)", AS_METHODPR(ToolTip, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetEnabled(bool)", AS_METHODPR(ToolTip, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_enabled(bool)", AS_METHODPR(ToolTip, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetEnabledRecursive(bool)", AS_METHODPR(ToolTip, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetFixedHeight(int)", AS_METHODPR(ToolTip, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(ToolTip, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetFixedSize(int, int)", AS_METHODPR(ToolTip, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetFixedWidth(int)", AS_METHODPR(ToolTip, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetFocus(bool)", AS_METHODPR(ToolTip, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_focus(bool)", AS_METHODPR(ToolTip, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetFocusMode(FocusMode)", AS_METHODPR(ToolTip, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_focusMode(FocusMode)", AS_METHODPR(ToolTip, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(ToolTip, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(ToolTip, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetHeight(int)", AS_METHODPR(ToolTip, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_height(int)", AS_METHODPR(ToolTip, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(ToolTip, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(ToolTip, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetHovering(bool)", AS_METHODPR(ToolTip, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetIndent(int)", AS_METHODPR(ToolTip, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_indent(int)", AS_METHODPR(ToolTip, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetIndentSpacing(int)", AS_METHODPR(ToolTip, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_indentSpacing(int)", AS_METHODPR(ToolTip, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void SetInstanceDefault(bool)", AS_METHODPR(ToolTip, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(ToolTip, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetInternal(bool)", AS_METHODPR(ToolTip, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_internal(bool)", AS_METHODPR(ToolTip, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(ToolTip, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(ToolTip, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(ToolTip, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(ToolTip, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(ToolTip, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetLayoutMode(LayoutMode)", AS_METHODPR(ToolTip, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_layoutMode(LayoutMode)", AS_METHODPR(ToolTip, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetLayoutSpacing(int)", AS_METHODPR(ToolTip, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_layoutSpacing(int)", AS_METHODPR(ToolTip, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(ToolTip, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(ToolTip, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxAnchor(float, float)", AS_METHODPR(ToolTip, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxHeight(int)", AS_METHODPR(ToolTip, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_maxHeight(int)", AS_METHODPR(ToolTip, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(ToolTip, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(ToolTip, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(ToolTip, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_maxSize(const IntVector2&in)", AS_METHODPR(ToolTip, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxSize(int, int)", AS_METHODPR(ToolTip, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxWidth(int)", AS_METHODPR(ToolTip, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_maxWidth(int)", AS_METHODPR(ToolTip, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(ToolTip, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_minAnchor(const Vector2&in)", AS_METHODPR(ToolTip, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinAnchor(float, float)", AS_METHODPR(ToolTip, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinHeight(int)", AS_METHODPR(ToolTip, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_minHeight(int)", AS_METHODPR(ToolTip, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(ToolTip, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_minOffset(const IntVector2&in)", AS_METHODPR(ToolTip, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinSize(const IntVector2&in)", AS_METHODPR(ToolTip, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_minSize(const IntVector2&in)", AS_METHODPR(ToolTip, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinSize(int, int)", AS_METHODPR(ToolTip, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinWidth(int)", AS_METHODPR(ToolTip, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_minWidth(int)", AS_METHODPR(ToolTip, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetName(const String&in)", AS_METHODPR(ToolTip, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_name(const String&in)", AS_METHODPR(ToolTip, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(ToolTip, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(ToolTip, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(ToolTip, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetOpacity(float)", AS_METHODPR(ToolTip, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_opacity(float)", AS_METHODPR(ToolTip, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(ToolTip, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetPivot(const Vector2&in)", AS_METHODPR(ToolTip, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_pivot(const Vector2&in)", AS_METHODPR(ToolTip, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetPivot(float, float)", AS_METHODPR(ToolTip, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetPosition(const IntVector2&in)", AS_METHODPR(ToolTip, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_position(const IntVector2&in)", AS_METHODPR(ToolTip, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetPosition(int, int)", AS_METHODPR(ToolTip, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetPriority(int)", AS_METHODPR(ToolTip, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_priority(int)", AS_METHODPR(ToolTip, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(ToolTip, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetSelected(bool)", AS_METHODPR(ToolTip, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_selected(bool)", AS_METHODPR(ToolTip, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetSize(const IntVector2&in)", AS_METHODPR(ToolTip, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_size(const IntVector2&in)", AS_METHODPR(ToolTip, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetSize(int, int)", AS_METHODPR(ToolTip, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetSortChildren(bool)", AS_METHODPR(ToolTip, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_sortChildren(bool)", AS_METHODPR(ToolTip, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(ToolTip, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool SetStyle(const XMLElement&in)", AS_METHODPR(ToolTip, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(ToolTip, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(ToolTip_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void SetTemporary(bool)", AS_METHODPR(ToolTip, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_temporary(bool)", AS_METHODPR(ToolTip, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetTraversalMode(TraversalMode)", AS_METHODPR(ToolTip, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_traversalMode(TraversalMode)", AS_METHODPR(ToolTip, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetUseDerivedOpacity(bool)", AS_METHODPR(ToolTip, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_useDerivedOpacity(bool)", AS_METHODPR(ToolTip, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(ToolTip, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(ToolTip, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(ToolTip, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetVisible(bool)", AS_METHODPR(ToolTip, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_visible(bool)", AS_METHODPR(ToolTip, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetWidth(int)", AS_METHODPR(ToolTip, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_width(int)", AS_METHODPR(ToolTip, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SortChildren()", AS_METHODPR(ToolTip, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit ToolTip::ToolTip(Context* context) | File: ../UI/ToolTip.h
    engine->RegisterObjectBehaviour("ToolTip", asBEHAVE_FACTORY, "ToolTip@+ f()", AS_FUNCTION(ToolTip_ToolTip_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void UnsubscribeFromAllEvents()", AS_METHODPR(ToolTip, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(ToolTip_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(ToolTip, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(ToolTip, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(ToolTip, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void ToolTip::Update(float timeStep) override | File: ../UI/ToolTip.h
    engine->RegisterObjectMethod("ToolTip", "void Update(float)", AS_METHODPR(ToolTip, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void UpdateLayout()", AS_METHODPR(ToolTip, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ToolTip", "int WeakRefs() const", AS_METHODPR(ToolTip, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_weakRefs() const", AS_METHODPR(ToolTip, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(ToolTip, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(ToolTip, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(ToolTip, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(ToolTip, "ToolTip")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(ToolTip, "ToolTip")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(ToolTip, "ToolTip")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(ToolTip, "ToolTip")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(ToolTip, "ToolTip")
#endif
#ifdef REGISTER_MANUAL_PART_ToolTip
    REGISTER_MANUAL_PART_ToolTip(ToolTip, "ToolTip")
#endif
    RegisterSubclass<UIElement, ToolTip>(engine, "UIElement", "ToolTip");
    RegisterSubclass<Animatable, ToolTip>(engine, "Animatable", "ToolTip");
    RegisterSubclass<Serializable, ToolTip>(engine, "Serializable", "ToolTip");
    RegisterSubclass<Object, ToolTip>(engine, "Object", "ToolTip");
    RegisterSubclass<RefCounted, ToolTip>(engine, "RefCounted", "ToolTip");

    // IntVector2 TouchState::delta_ | File: ../Input/Input.h
    engine->RegisterObjectProperty("TouchState", "IntVector2 delta", offsetof(TouchState, delta_));
    // IntVector2 TouchState::lastPosition_ | File: ../Input/Input.h
    engine->RegisterObjectProperty("TouchState", "IntVector2 lastPosition", offsetof(TouchState, lastPosition_));
    // IntVector2 TouchState::position_ | File: ../Input/Input.h
    engine->RegisterObjectProperty("TouchState", "IntVector2 position", offsetof(TouchState, position_));
    // float TouchState::pressure_ | File: ../Input/Input.h
    engine->RegisterObjectProperty("TouchState", "float pressure", offsetof(TouchState, pressure_));
    // WeakPtr<UIElement> TouchState::touchedElement_ | File: ../Input/Input.h
    // Error: type "WeakPtr<UIElement>" can not automatically bind
    // int TouchState::touchID_ | File: ../Input/Input.h
    engine->RegisterObjectProperty("TouchState", "int touchID", offsetof(TouchState, touchID_));
    // UIElement* TouchState::GetTouchedElement() | File: ../Input/Input.h
    engine->RegisterObjectMethod("TouchState", "UIElement@+ GetTouchedElement()", AS_METHODPR(TouchState, GetTouchedElement, (), UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TouchState", "UIElement@+ get_touchedElement()", AS_METHODPR(TouchState, GetTouchedElement, (), UIElement*), AS_CALL_THISCALL);
    // TouchState& TouchState::operator=(const TouchState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TouchState>(engine, "TouchState");
    engine->RegisterObjectBehaviour("TouchState", asBEHAVE_ADDREF, "void f()", AS_FUNCTION_OBJLAST(FakeAddRef), AS_CALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("TouchState", asBEHAVE_RELEASE, "void f()", AS_FUNCTION_OBJLAST(FakeReleaseRef), AS_CALL_CDECL_OBJLAST);
#ifdef REGISTER_MANUAL_PART_TouchState
    REGISTER_MANUAL_PART_TouchState(TouchState, "TouchState")
#endif

    // float TrailPoint::elapsedLength_ | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectProperty("TrailPoint", "float elapsedLength", offsetof(TrailPoint, elapsedLength_));
    // Vector3 TrailPoint::forward_ | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectProperty("TrailPoint", "Vector3 forward", offsetof(TrailPoint, forward_));
    // float TrailPoint::lifetime_ | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectProperty("TrailPoint", "float lifetime", offsetof(TrailPoint, lifetime_));
    // TrailPoint* TrailPoint::next_ | File: ../Graphics/RibbonTrail.h
    // TrailPoint* can not be registered
    // Vector3 TrailPoint::parentPos_ | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectProperty("TrailPoint", "Vector3 parentPos", offsetof(TrailPoint, parentPos_));
    // Vector3 TrailPoint::position_ | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectProperty("TrailPoint", "Vector3 position", offsetof(TrailPoint, position_));
    // float TrailPoint::sortDistance_ | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectProperty("TrailPoint", "float sortDistance", offsetof(TrailPoint, sortDistance_));
    // TrailPoint::TrailPoint(const Vector3& position, const Vector3& forward) | File: ../Graphics/RibbonTrail.h
    engine->RegisterObjectBehaviour("TrailPoint", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", AS_FUNCTION_OBJFIRST(TrailPoint_TrailPoint_Vector3_Vector3), AS_CALL_CDECL_OBJFIRST);
    // TrailPoint& TrailPoint::operator=(const TrailPoint&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TrailPoint>(engine, "TrailPoint");
#ifdef REGISTER_MANUAL_PART_TrailPoint
    REGISTER_MANUAL_PART_TrailPoint(TrailPoint, "TrailPoint")
#endif

#ifdef URHO3D_PHYSICS
    // UniquePtr<btTriangleInfoMap> TriangleMeshData::infoMap_ | File: ../Physics/CollisionShape.h
    // Error: type "UniquePtr<btTriangleInfoMap>" can not automatically bind
    // UniquePtr<TriangleMeshInterface> TriangleMeshData::meshInterface_ | File: ../Physics/CollisionShape.h
    // Error: type "UniquePtr<TriangleMeshInterface>" can not automatically bind
    // UniquePtr<btBvhTriangleMeshShape> TriangleMeshData::shape_ | File: ../Physics/CollisionShape.h
    // Error: type "UniquePtr<btBvhTriangleMeshShape>" can not automatically bind
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TriangleMeshData", asBEHAVE_ADDREF, "void f()", AS_METHODPR(TriangleMeshData, AddRef, (), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TriangleMeshData", "int Refs() const", AS_METHODPR(TriangleMeshData, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TriangleMeshData", "int get_refs() const", AS_METHODPR(TriangleMeshData, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TriangleMeshData", asBEHAVE_RELEASE, "void f()", AS_METHODPR(TriangleMeshData, ReleaseRef, (), void), AS_CALL_THISCALL);
    // TriangleMeshData::TriangleMeshData(Model* model, unsigned lodLevel) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("TriangleMeshData", asBEHAVE_FACTORY, "TriangleMeshData@+ f(Model@+, uint)", AS_FUNCTION(TriangleMeshData_TriangleMeshData_Model_unsigned), AS_CALL_CDECL);
    // explicit TriangleMeshData::TriangleMeshData(CustomGeometry* custom) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("TriangleMeshData", asBEHAVE_FACTORY, "TriangleMeshData@+ f(CustomGeometry@+)", AS_FUNCTION(TriangleMeshData_TriangleMeshData_CustomGeometry), AS_CALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TriangleMeshData", "int WeakRefs() const", AS_METHODPR(TriangleMeshData, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("TriangleMeshData", "int get_weakRefs() const", AS_METHODPR(TriangleMeshData, WeakRefs, () const, int), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_CollisionGeometryData
    REGISTER_MANUAL_PART_CollisionGeometryData(TriangleMeshData, "TriangleMeshData")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(TriangleMeshData, "TriangleMeshData")
#endif
#ifdef REGISTER_MANUAL_PART_TriangleMeshData
    REGISTER_MANUAL_PART_TriangleMeshData(TriangleMeshData, "TriangleMeshData")
#endif
    RegisterSubclass<CollisionGeometryData, TriangleMeshData>(engine, "CollisionGeometryData", "TriangleMeshData");
    RegisterSubclass<RefCounted, TriangleMeshData>(engine, "RefCounted", "TriangleMeshData");
#endif

}

}
