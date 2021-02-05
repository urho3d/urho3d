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
    engine->RegisterObjectMethod("ToolTip", "void AddAltTarget(UIElement@+)", asMETHODPR(ToolTip, AddAltTarget, (UIElement*), void), asCALL_THISCALL);
    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void AddChild(UIElement@+)", asMETHODPR(ToolTip, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ToolTip", asBEHAVE_ADDREF, "void f()", asMETHODPR(ToolTip, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void AddTag(const String&in)", asMETHODPR(ToolTip, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void AddTags(const String&in, int8 = ';')", asMETHODPR(ToolTip, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void AddTags(Array<String>@+)", asFUNCTION(ToolTip_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void AdjustScissor(IntRect&)", asMETHODPR(ToolTip, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void AllocateNetworkState()", asMETHODPR(ToolTip, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void ApplyAttributes()", asMETHODPR(ToolTip, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void BringToFront()", asMETHODPR(ToolTip, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(ToolTip, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void DisableLayoutUpdate()", asMETHODPR(ToolTip, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(ToolTip, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void EnableLayoutUpdate()", asMETHODPR(ToolTip, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool FilterAttributes(XMLElement&) const", asMETHODPR(ToolTip, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "uint FindChild(UIElement@+) const", asMETHODPR(ToolTip, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "bool GetAnimationEnabled() const", asMETHODPR(ToolTip, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_animationEnabled() const", asMETHODPR(ToolTip, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const String& GetAppliedStyle() const", asMETHODPR(ToolTip, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const String& get_style() const", asMETHODPR(ToolTip, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "Variant GetAttribute(uint) const", asMETHODPR(ToolTip, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "Variant get_attributes(uint) const", asMETHODPR(ToolTip, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "Variant GetAttribute(const String&in) const", asMETHODPR(ToolTip, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(ToolTip, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(ToolTip, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(ToolTip, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(ToolTip, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "Variant GetAttributeDefault(uint) const", asMETHODPR(ToolTip, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "Variant get_attributeDefaults(uint) const", asMETHODPR(ToolTip, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(ToolTip, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // virtual void UIElement::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "bool GetBlockEvents() const", asMETHODPR(ToolTip, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool GetBringToBack() const", asMETHODPR(ToolTip, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_bringToBack() const", asMETHODPR(ToolTip, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool GetBringToFront() const", asMETHODPR(ToolTip, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_bringToFront() const", asMETHODPR(ToolTip, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "const String& GetCategory() const", asMETHODPR(ToolTip, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const String& get_category() const", asMETHODPR(ToolTip, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ GetChild(uint) const", asMETHODPR(ToolTip, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ get_children(uint) const", asMETHODPR(ToolTip, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(ToolTip, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(ToolTip, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetChildOffset() const", asMETHODPR(ToolTip, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_childOffset() const", asMETHODPR(ToolTip, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "Array<UIElement@>@ GetChildren() const", asFUNCTION(ToolTip_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(ToolTip_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(ToolTip_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntRect& GetClipBorder() const", asMETHODPR(ToolTip, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntRect& get_clipBorder() const", asMETHODPR(ToolTip, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool GetClipChildren() const", asMETHODPR(ToolTip, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_clipChildren() const", asMETHODPR(ToolTip, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Color& GetColor(Corner) const", asMETHODPR(ToolTip, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const Color& get_colors(Corner) const", asMETHODPR(ToolTip, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Color& GetColorAttr() const", asMETHODPR(ToolTip, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "IntRect GetCombinedScreenRect()", asMETHODPR(ToolTip, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "IntRect get_combinedScreenRect()", asMETHODPR(ToolTip, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(ToolTip, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // float ToolTip::GetDelay() const | File: ../UI/ToolTip.h
    engine->RegisterObjectMethod("ToolTip", "float GetDelay() const", asMETHODPR(ToolTip, GetDelay, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "float get_delay() const", asMETHODPR(ToolTip, GetDelay, () const, float), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Color& GetDerivedColor() const", asMETHODPR(ToolTip, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "float GetDerivedOpacity() const", asMETHODPR(ToolTip, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "float get_derivedOpacity() const", asMETHODPR(ToolTip, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(ToolTip, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(ToolTip, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "uint GetDragButtonCount() const", asMETHODPR(ToolTip, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "uint get_dragButtonCount() const", asMETHODPR(ToolTip, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(ToolTip, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(ToolTip, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(ToolTip, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ GetElementEventSender() const", asMETHODPR(ToolTip, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool GetEnableAnchor() const", asMETHODPR(ToolTip, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_enableAnchor() const", asMETHODPR(ToolTip, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "VariantMap& GetEventDataMap() const", asMETHODPR(ToolTip, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "Object@+ GetEventSender() const", asMETHODPR(ToolTip, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "FocusMode GetFocusMode() const", asMETHODPR(ToolTip, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "FocusMode get_focusMode() const", asMETHODPR(ToolTip, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(ToolTip, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const Variant& get_globalVar(StringHash) const", asMETHODPR(ToolTip, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "const VariantMap& GetGlobalVars() const", asMETHODPR(ToolTip, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const VariantMap& get_globalVars() const", asMETHODPR(ToolTip, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetHeight() const", asMETHODPR(ToolTip, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_height() const", asMETHODPR(ToolTip, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(ToolTip, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(ToolTip, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetIndent() const", asMETHODPR(ToolTip, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_indent() const", asMETHODPR(ToolTip, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetIndentSpacing() const", asMETHODPR(ToolTip, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_indentSpacing() const", asMETHODPR(ToolTip, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetIndentWidth() const", asMETHODPR(ToolTip, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_indentWidth() const", asMETHODPR(ToolTip, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(ToolTip, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntRect& GetLayoutBorder() const", asMETHODPR(ToolTip, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntRect& get_layoutBorder() const", asMETHODPR(ToolTip, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetLayoutElementMaxSize() const", asMETHODPR(ToolTip, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(ToolTip, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const Vector2& get_layoutFlexScale() const", asMETHODPR(ToolTip, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "LayoutMode GetLayoutMode() const", asMETHODPR(ToolTip, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "LayoutMode get_layoutMode() const", asMETHODPR(ToolTip, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetLayoutSpacing() const", asMETHODPR(ToolTip, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_layoutSpacing() const", asMETHODPR(ToolTip, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Vector2& GetMaxAnchor() const", asMETHODPR(ToolTip, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const Vector2& get_maxAnchor() const", asMETHODPR(ToolTip, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetMaxHeight() const", asMETHODPR(ToolTip, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_maxHeight() const", asMETHODPR(ToolTip, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetMaxOffset() const", asMETHODPR(ToolTip, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_maxOffset() const", asMETHODPR(ToolTip, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetMaxSize() const", asMETHODPR(ToolTip, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_maxSize() const", asMETHODPR(ToolTip, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetMaxWidth() const", asMETHODPR(ToolTip, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_maxWidth() const", asMETHODPR(ToolTip, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Vector2& GetMinAnchor() const", asMETHODPR(ToolTip, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const Vector2& get_minAnchor() const", asMETHODPR(ToolTip, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetMinHeight() const", asMETHODPR(ToolTip, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_minHeight() const", asMETHODPR(ToolTip, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetMinOffset() const", asMETHODPR(ToolTip, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_minOffset() const", asMETHODPR(ToolTip, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetMinSize() const", asMETHODPR(ToolTip, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_minSize() const", asMETHODPR(ToolTip, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetMinWidth() const", asMETHODPR(ToolTip, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_minWidth() const", asMETHODPR(ToolTip, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const String& GetName() const", asMETHODPR(ToolTip, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const String& get_name() const", asMETHODPR(ToolTip, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "uint GetNumAttributes() const", asMETHODPR(ToolTip, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "uint get_numAttributes() const", asMETHODPR(ToolTip, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "uint GetNumChildren(bool = false) const", asMETHODPR(ToolTip, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "uint get_numChildren(bool = false) const", asMETHODPR(ToolTip, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "uint GetNumNetworkAttributes() const", asMETHODPR(ToolTip, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(ToolTip, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(ToolTip, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(ToolTip, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "float GetOpacity() const", asMETHODPR(ToolTip, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "float get_opacity() const", asMETHODPR(ToolTip, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ GetParent() const", asMETHODPR(ToolTip, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ get_parent() const", asMETHODPR(ToolTip, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Vector2& GetPivot() const", asMETHODPR(ToolTip, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const Vector2& get_pivot() const", asMETHODPR(ToolTip, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetPosition() const", asMETHODPR(ToolTip, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_position() const", asMETHODPR(ToolTip, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetPriority() const", asMETHODPR(ToolTip, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_priority() const", asMETHODPR(ToolTip, GetPriority, () const, int), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ GetRoot() const", asMETHODPR(ToolTip, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ get_root() const", asMETHODPR(ToolTip, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetScreenPosition() const", asMETHODPR(ToolTip, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_screenPosition() const", asMETHODPR(ToolTip, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& GetSize() const", asMETHODPR(ToolTip, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const IntVector2& get_size() const", asMETHODPR(ToolTip, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool GetSortChildren() const", asMETHODPR(ToolTip, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_sortChildren() const", asMETHODPR(ToolTip, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(ToolTip, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "Array<String>@ GetTags() const", asFUNCTION(ToolTip_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("ToolTip", "Array<String>@ get_tags() const", asFUNCTION(ToolTip_GetTags_void), asCALL_CDECL_OBJFIRST);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "TraversalMode GetTraversalMode() const", asMETHODPR(ToolTip, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "TraversalMode get_traversalMode() const", asMETHODPR(ToolTip, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "StringHash GetType() const", asMETHODPR(ToolTip, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "StringHash get_type() const", asMETHODPR(ToolTip, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "const String& GetTypeName() const", asMETHODPR(ToolTip, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "const String& get_typeName() const", asMETHODPR(ToolTip, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool GetUseDerivedOpacity() const", asMETHODPR(ToolTip, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_useDerivedOpacity() const", asMETHODPR(ToolTip, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(ToolTip, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "const VariantMap& GetVars() const", asMETHODPR(ToolTip, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(ToolTip, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(ToolTip, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "int GetWidth() const", asMETHODPR(ToolTip, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_width() const", asMETHODPR(ToolTip, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool HasColorGradient() const", asMETHODPR(ToolTip, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_colorGradient() const", asMETHODPR(ToolTip, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "bool HasEventHandlers() const", asMETHODPR(ToolTip, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool HasFocus() const", asMETHODPR(ToolTip, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_focus() const", asMETHODPR(ToolTip, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(ToolTip, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(ToolTip, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool HasTag(const String&in) const", asMETHODPR(ToolTip, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void InsertChild(uint, UIElement@+)", asMETHODPR(ToolTip, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsChildOf(UIElement@+) const", asMETHODPR(ToolTip, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsEditable() const", asMETHODPR(ToolTip, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_editable() const", asMETHODPR(ToolTip, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsElementEventSender() const", asMETHODPR(ToolTip, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_elementEventSender() const", asMETHODPR(ToolTip, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsEnabled() const", asMETHODPR(ToolTip, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_enabled() const", asMETHODPR(ToolTip, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsEnabledSelf() const", asMETHODPR(ToolTip, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_enabledSelf() const", asMETHODPR(ToolTip, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsFixedHeight() const", asMETHODPR(ToolTip, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_fixedHeight() const", asMETHODPR(ToolTip, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsFixedSize() const", asMETHODPR(ToolTip, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_fixedSize() const", asMETHODPR(ToolTip, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsFixedWidth() const", asMETHODPR(ToolTip, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_fixedWidth() const", asMETHODPR(ToolTip, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsHovering() const", asMETHODPR(ToolTip, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_hovering() const", asMETHODPR(ToolTip, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsInside(IntVector2, bool)", asMETHODPR(ToolTip, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(ToolTip, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "bool IsInstanceOf(StringHash) const", asMETHODPR(ToolTip, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsInternal() const", asMETHODPR(ToolTip, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_internal() const", asMETHODPR(ToolTip, IsInternal, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsSelected() const", asMETHODPR(ToolTip, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_selected() const", asMETHODPR(ToolTip, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool IsTemporary() const", asMETHODPR(ToolTip, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_temporary() const", asMETHODPR(ToolTip, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsVisible() const", asMETHODPR(ToolTip, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_visible() const", asMETHODPR(ToolTip, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsVisibleEffective() const", asMETHODPR(ToolTip, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool get_visibleEffective() const", asMETHODPR(ToolTip, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsWheelHandler() const", asMETHODPR(ToolTip, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(ToolTip, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool Load(Deserializer&)", asMETHODPR(ToolTip, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(ToolTip, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "bool LoadJSON(const JSONValue&in)", asMETHODPR(ToolTip, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool LoadXML(const XMLElement&in)", asMETHODPR(ToolTip, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(ToolTip, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool LoadXML(Deserializer&)", asMETHODPR(ToolTip, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void MarkNetworkUpdate()", asMETHODPR(ToolTip, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ToolTip, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(ToolTip, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ToolTip, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ToolTip, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(ToolTip, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(ToolTip, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool OnDragDropTest(UIElement@+)", asMETHODPR(ToolTip, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(ToolTip, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ToolTip, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(ToolTip, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(ToolTip, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(ToolTip, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnIndentSet()", asMETHODPR(ToolTip, OnIndentSet, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(ToolTip, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnPositionSet(const IntVector2&in)", asMETHODPR(ToolTip, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(ToolTip, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(ToolTip, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnSetEditable()", asMETHODPR(ToolTip, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnTextInput(const String&in)", asMETHODPR(ToolTip, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(ToolTip, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(ToolTip, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(ToolTip, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ToolTip", "int Refs() const", asMETHODPR(ToolTip, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_refs() const", asMETHODPR(ToolTip, Refs, () const, int), asCALL_THISCALL);
    // static void ToolTip::RegisterObject(Context* context) | File: ../UI/ToolTip.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("ToolTip", asBEHAVE_RELEASE, "void f()", asMETHODPR(ToolTip, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void Remove()", asMETHODPR(ToolTip, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveAllChildren()", asMETHODPR(ToolTip, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveAllTags()", asMETHODPR(ToolTip, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(ToolTip, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(ToolTip, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveChildAtIndex(uint)", asMETHODPR(ToolTip, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveInstanceDefault()", asMETHODPR(ToolTip, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void RemoveObjectAnimation()", asMETHODPR(ToolTip, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool RemoveTag(const String&in)", asMETHODPR(ToolTip, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void ToolTip::Reset() | File: ../UI/ToolTip.h
    engine->RegisterObjectMethod("ToolTip", "void Reset()", asMETHODPR(ToolTip, Reset, (), void), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void ResetDeepEnabled()", asMETHODPR(ToolTip, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void ResetToDefault()", asMETHODPR(ToolTip, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool Save(Serializer&) const", asMETHODPR(ToolTip, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool SaveDefaultAttributes() const", asMETHODPR(ToolTip, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "bool SaveJSON(JSONValue&) const", asMETHODPR(ToolTip, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool SaveXML(XMLElement&) const", asMETHODPR(ToolTip, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(ToolTip, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(ToolTip, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void SendEvent(StringHash)", asMETHODPR(ToolTip, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(ToolTip, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(ToolTip, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetAnimationEnabled(bool)", asMETHODPR(ToolTip, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_animationEnabled(bool)", asMETHODPR(ToolTip, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetAnimationTime(float)", asMETHODPR(ToolTip, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(ToolTip, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "bool set_attributes(uint, const Variant&in)", asMETHODPR(ToolTip, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(ToolTip, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(ToolTip, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(ToolTip, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(ToolTip, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(ToolTip, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void SetBlockEvents(bool)", asMETHODPR(ToolTip, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetBringToBack(bool)", asMETHODPR(ToolTip, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_bringToBack(bool)", asMETHODPR(ToolTip, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetBringToFront(bool)", asMETHODPR(ToolTip, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_bringToFront(bool)", asMETHODPR(ToolTip, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetChildOffset(const IntVector2&in)", asMETHODPR(ToolTip, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetClipBorder(const IntRect&in)", asMETHODPR(ToolTip, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_clipBorder(const IntRect&in)", asMETHODPR(ToolTip, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetClipChildren(bool)", asMETHODPR(ToolTip, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_clipChildren(bool)", asMETHODPR(ToolTip, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetColor(const Color&in)", asMETHODPR(ToolTip, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_color(const Color&in)", asMETHODPR(ToolTip, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetColor(Corner, const Color&in)", asMETHODPR(ToolTip, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_colors(Corner, const Color&in)", asMETHODPR(ToolTip, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetDeepEnabled(bool)", asMETHODPR(ToolTip, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(ToolTip, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_defaultStyle(XMLFile@+)", asMETHODPR(ToolTip, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void ToolTip::SetDelay(float delay) | File: ../UI/ToolTip.h
    engine->RegisterObjectMethod("ToolTip", "void SetDelay(float)", asMETHODPR(ToolTip, SetDelay, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_delay(float)", asMETHODPR(ToolTip, SetDelay, (float), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(ToolTip, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(ToolTip, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetEditable(bool)", asMETHODPR(ToolTip, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_editable(bool)", asMETHODPR(ToolTip, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetElementEventSender(bool)", asMETHODPR(ToolTip, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_elementEventSender(bool)", asMETHODPR(ToolTip, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetEnableAnchor(bool)", asMETHODPR(ToolTip, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_enableAnchor(bool)", asMETHODPR(ToolTip, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetEnabled(bool)", asMETHODPR(ToolTip, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_enabled(bool)", asMETHODPR(ToolTip, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetEnabledRecursive(bool)", asMETHODPR(ToolTip, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetFixedHeight(int)", asMETHODPR(ToolTip, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetFixedSize(const IntVector2&in)", asMETHODPR(ToolTip, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetFixedSize(int, int)", asMETHODPR(ToolTip, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetFixedWidth(int)", asMETHODPR(ToolTip, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetFocus(bool)", asMETHODPR(ToolTip, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_focus(bool)", asMETHODPR(ToolTip, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetFocusMode(FocusMode)", asMETHODPR(ToolTip, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_focusMode(FocusMode)", asMETHODPR(ToolTip, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(ToolTip, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(ToolTip, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetHeight(int)", asMETHODPR(ToolTip, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_height(int)", asMETHODPR(ToolTip, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(ToolTip, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(ToolTip, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetHovering(bool)", asMETHODPR(ToolTip, SetHovering, (bool), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetIndent(int)", asMETHODPR(ToolTip, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_indent(int)", asMETHODPR(ToolTip, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetIndentSpacing(int)", asMETHODPR(ToolTip, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_indentSpacing(int)", asMETHODPR(ToolTip, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void SetInstanceDefault(bool)", asMETHODPR(ToolTip, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(ToolTip, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetInternal(bool)", asMETHODPR(ToolTip, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_internal(bool)", asMETHODPR(ToolTip, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(ToolTip, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(ToolTip, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_layoutBorder(const IntRect&in)", asMETHODPR(ToolTip, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(ToolTip, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(ToolTip, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetLayoutMode(LayoutMode)", asMETHODPR(ToolTip, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_layoutMode(LayoutMode)", asMETHODPR(ToolTip, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetLayoutSpacing(int)", asMETHODPR(ToolTip, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_layoutSpacing(int)", asMETHODPR(ToolTip, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(ToolTip, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_maxAnchor(const Vector2&in)", asMETHODPR(ToolTip, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxAnchor(float, float)", asMETHODPR(ToolTip, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxHeight(int)", asMETHODPR(ToolTip, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_maxHeight(int)", asMETHODPR(ToolTip, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(ToolTip, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_maxOffset(const IntVector2&in)", asMETHODPR(ToolTip, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxSize(const IntVector2&in)", asMETHODPR(ToolTip, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_maxSize(const IntVector2&in)", asMETHODPR(ToolTip, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxSize(int, int)", asMETHODPR(ToolTip, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMaxWidth(int)", asMETHODPR(ToolTip, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_maxWidth(int)", asMETHODPR(ToolTip, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinAnchor(const Vector2&in)", asMETHODPR(ToolTip, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_minAnchor(const Vector2&in)", asMETHODPR(ToolTip, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinAnchor(float, float)", asMETHODPR(ToolTip, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinHeight(int)", asMETHODPR(ToolTip, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_minHeight(int)", asMETHODPR(ToolTip, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinOffset(const IntVector2&in)", asMETHODPR(ToolTip, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_minOffset(const IntVector2&in)", asMETHODPR(ToolTip, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinSize(const IntVector2&in)", asMETHODPR(ToolTip, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_minSize(const IntVector2&in)", asMETHODPR(ToolTip, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinSize(int, int)", asMETHODPR(ToolTip, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetMinWidth(int)", asMETHODPR(ToolTip, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_minWidth(int)", asMETHODPR(ToolTip, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetName(const String&in)", asMETHODPR(ToolTip, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_name(const String&in)", asMETHODPR(ToolTip, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(ToolTip, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(ToolTip, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("ToolTip", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(ToolTip, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetOpacity(float)", asMETHODPR(ToolTip, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_opacity(float)", asMETHODPR(ToolTip, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(ToolTip, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetPivot(const Vector2&in)", asMETHODPR(ToolTip, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_pivot(const Vector2&in)", asMETHODPR(ToolTip, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetPivot(float, float)", asMETHODPR(ToolTip, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetPosition(const IntVector2&in)", asMETHODPR(ToolTip, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_position(const IntVector2&in)", asMETHODPR(ToolTip, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetPosition(int, int)", asMETHODPR(ToolTip, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetPriority(int)", asMETHODPR(ToolTip, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_priority(int)", asMETHODPR(ToolTip, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetRenderTexture(Texture2D@+)", asMETHODPR(ToolTip, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetSelected(bool)", asMETHODPR(ToolTip, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_selected(bool)", asMETHODPR(ToolTip, SetSelected, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetSize(const IntVector2&in)", asMETHODPR(ToolTip, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_size(const IntVector2&in)", asMETHODPR(ToolTip, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetSize(int, int)", asMETHODPR(ToolTip, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetSortChildren(bool)", asMETHODPR(ToolTip, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_sortChildren(bool)", asMETHODPR(ToolTip, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(ToolTip, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool SetStyle(const XMLElement&in)", asMETHODPR(ToolTip, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(ToolTip, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetTags(Array<String>@+)", asFUNCTION(ToolTip_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void SetTemporary(bool)", asMETHODPR(ToolTip, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_temporary(bool)", asMETHODPR(ToolTip, SetTemporary, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetTraversalMode(TraversalMode)", asMETHODPR(ToolTip, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_traversalMode(TraversalMode)", asMETHODPR(ToolTip, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetUseDerivedOpacity(bool)", asMETHODPR(ToolTip, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_useDerivedOpacity(bool)", asMETHODPR(ToolTip, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetVar(StringHash, const Variant&in)", asMETHODPR(ToolTip, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(ToolTip, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(ToolTip, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetVisible(bool)", asMETHODPR(ToolTip, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_visible(bool)", asMETHODPR(ToolTip, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SetWidth(int)", asMETHODPR(ToolTip, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "void set_width(int)", asMETHODPR(ToolTip, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void SortChildren()", asMETHODPR(ToolTip, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit ToolTip::ToolTip(Context* context) | File: ../UI/ToolTip.h
    engine->RegisterObjectBehaviour("ToolTip", asBEHAVE_FACTORY, "ToolTip@+ f()", asFUNCTION(ToolTip_ToolTip_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void UnsubscribeFromAllEvents()", asMETHODPR(ToolTip, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(ToolTip_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(ToolTip, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(ToolTip, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("ToolTip", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(ToolTip, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void ToolTip::Update(float timeStep) override | File: ../UI/ToolTip.h
    engine->RegisterObjectMethod("ToolTip", "void Update(float)", asMETHODPR(ToolTip, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("ToolTip", "void UpdateLayout()", asMETHODPR(ToolTip, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("ToolTip", "int WeakRefs() const", asMETHODPR(ToolTip, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("ToolTip", "int get_weakRefs() const", asMETHODPR(ToolTip, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(ToolTip, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(ToolTip, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("ToolTip", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(ToolTip, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("TouchState", "UIElement@+ GetTouchedElement()", asMETHODPR(TouchState, GetTouchedElement, (), UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("TouchState", "UIElement@+ get_touchedElement()", asMETHODPR(TouchState, GetTouchedElement, (), UIElement*), asCALL_THISCALL);
    // TouchState& TouchState::operator=(const TouchState&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<TouchState>(engine, "TouchState");
    engine->RegisterObjectBehaviour("TouchState", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("TouchState", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
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
    engine->RegisterObjectBehaviour("TrailPoint", asBEHAVE_CONSTRUCT, "void f(const Vector3&in, const Vector3&in)", asFUNCTION(TrailPoint_TrailPoint_Vector3_Vector3), asCALL_CDECL_OBJFIRST);
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
    engine->RegisterObjectBehaviour("TriangleMeshData", asBEHAVE_ADDREF, "void f()", asMETHODPR(TriangleMeshData, AddRef, (), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TriangleMeshData", "int Refs() const", asMETHODPR(TriangleMeshData, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TriangleMeshData", "int get_refs() const", asMETHODPR(TriangleMeshData, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("TriangleMeshData", asBEHAVE_RELEASE, "void f()", asMETHODPR(TriangleMeshData, ReleaseRef, (), void), asCALL_THISCALL);
    // TriangleMeshData::TriangleMeshData(Model* model, unsigned lodLevel) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("TriangleMeshData", asBEHAVE_FACTORY, "TriangleMeshData@+ f(Model@+, uint)", asFUNCTION(TriangleMeshData_TriangleMeshData_Model_unsigned), asCALL_CDECL);
    // explicit TriangleMeshData::TriangleMeshData(CustomGeometry* custom) | File: ../Physics/CollisionShape.h
    engine->RegisterObjectBehaviour("TriangleMeshData", asBEHAVE_FACTORY, "TriangleMeshData@+ f(CustomGeometry@+)", asFUNCTION(TriangleMeshData_TriangleMeshData_CustomGeometry), asCALL_CDECL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("TriangleMeshData", "int WeakRefs() const", asMETHODPR(TriangleMeshData, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("TriangleMeshData", "int get_weakRefs() const", asMETHODPR(TriangleMeshData, WeakRefs, () const, int), asCALL_THISCALL);
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
