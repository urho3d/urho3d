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
static void Window_AddTags_StringVector(Window* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* Window_GetChildren_void(Window* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* Window_GetChildren_bool(Window* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* Window_GetChildrenWithTag_String_bool(Window* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* Window_GetTags_void(Window* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void Window_SetTags_StringVector(Window* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void Window_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(Window* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit Window::Window(Context* context) | File: ../UI/Window.h
static Window* Window_Window_Context()
{
    return new Window(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void WorkQueue_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(WorkQueue* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit WorkQueue::WorkQueue(Context* context) | File: ../Core/WorkQueue.h
static WorkQueue* WorkQueue_WorkQueue_Context()
{
    return new WorkQueue(GetScriptContext());
}

void ASRegisterGenerated_Members_W(asIScriptEngine* engine)
{
    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void AddChild(UIElement@+)", AS_METHODPR(Window, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Window", asBEHAVE_ADDREF, "void f()", AS_METHODPR(Window, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void AddTag(const String&in)", AS_METHODPR(Window, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(Window, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Window_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void AdjustScissor(IntRect&)", AS_METHODPR(Window, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void AllocateNetworkState()", AS_METHODPR(Window, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void ApplyAttributes()", AS_METHODPR(Window, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void BringToFront()", AS_METHODPR(Window, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(Window, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void DisableLayoutUpdate()", AS_METHODPR(Window, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(Window, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void EnableLayoutUpdate()", AS_METHODPR(Window, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(Window, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "uint FindChild(UIElement@+) const", AS_METHODPR(Window, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "bool GetAnimationEnabled() const", AS_METHODPR(Window, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_animationEnabled() const", AS_METHODPR(Window, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const String& GetAppliedStyle() const", AS_METHODPR(Window, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const String& get_style() const", AS_METHODPR(Window, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "Variant GetAttribute(uint) const", AS_METHODPR(Window, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "Variant get_attributes(uint) const", AS_METHODPR(Window, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "Variant GetAttribute(const String&in) const", AS_METHODPR(Window, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(Window, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(Window, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(Window, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(Window, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "Variant GetAttributeDefault(uint) const", AS_METHODPR(Window, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "Variant get_attributeDefaults(uint) const", AS_METHODPR(Window, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(Window, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void Window::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Window.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "BlendMode GetBlendMode() const", AS_METHODPR(Window, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "BlendMode get_blendMode() const", AS_METHODPR(Window, GetBlendMode, () const, BlendMode), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "bool GetBlockEvents() const", AS_METHODPR(Window, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "const IntRect& GetBorder() const", AS_METHODPR(Window, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& get_border() const", AS_METHODPR(Window, GetBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool GetBringToBack() const", AS_METHODPR(Window, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_bringToBack() const", AS_METHODPR(Window, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool GetBringToFront() const", AS_METHODPR(Window, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_bringToFront() const", AS_METHODPR(Window, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "const String& GetCategory() const", AS_METHODPR(Window, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const String& get_category() const", AS_METHODPR(Window, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ GetChild(uint) const", AS_METHODPR(Window, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "UIElement@+ get_children(uint) const", AS_METHODPR(Window, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(Window, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(Window, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetChildOffset() const", AS_METHODPR(Window, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_childOffset() const", AS_METHODPR(Window, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(Window_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(Window_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(Window_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntRect& GetClipBorder() const", AS_METHODPR(Window, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& get_clipBorder() const", AS_METHODPR(Window, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool GetClipChildren() const", AS_METHODPR(Window, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_clipChildren() const", AS_METHODPR(Window, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Color& GetColor(Corner) const", AS_METHODPR(Window, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Color& get_colors(Corner) const", AS_METHODPR(Window, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Color& GetColorAttr() const", AS_METHODPR(Window, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "IntRect GetCombinedScreenRect()", AS_METHODPR(Window, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "IntRect get_combinedScreenRect()", AS_METHODPR(Window, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(Window, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Color& GetDerivedColor() const", AS_METHODPR(Window, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "float GetDerivedOpacity() const", AS_METHODPR(Window, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "float get_derivedOpacity() const", AS_METHODPR(Window, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetDisabledOffset() const", AS_METHODPR(Window, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_disabledOffset() const", AS_METHODPR(Window, GetDisabledOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(Window, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(Window, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "uint GetDragButtonCount() const", AS_METHODPR(Window, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "uint get_dragButtonCount() const", AS_METHODPR(Window, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(Window, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(Window, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(Window, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ GetElementEventSender() const", AS_METHODPR(Window, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool GetEnableAnchor() const", AS_METHODPR(Window, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_enableAnchor() const", AS_METHODPR(Window, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "VariantMap& GetEventDataMap() const", AS_METHODPR(Window, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "Object@+ GetEventSender() const", AS_METHODPR(Window, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // bool Window::GetFixedHeightResizing() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "bool GetFixedHeightResizing() const", AS_METHODPR(Window, GetFixedHeightResizing, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_fixedHeightResizing() const", AS_METHODPR(Window, GetFixedHeightResizing, () const, bool), AS_CALL_THISCALL);
    // bool Window::GetFixedWidthResizing() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "bool GetFixedWidthResizing() const", AS_METHODPR(Window, GetFixedWidthResizing, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_fixedWidthResizing() const", AS_METHODPR(Window, GetFixedWidthResizing, () const, bool), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "FocusMode GetFocusMode() const", AS_METHODPR(Window, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "FocusMode get_focusMode() const", AS_METHODPR(Window, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(Window, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(Window, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "const VariantMap& GetGlobalVars() const", AS_METHODPR(Window, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const VariantMap& get_globalVars() const", AS_METHODPR(Window, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetHeight() const", AS_METHODPR(Window, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_height() const", AS_METHODPR(Window, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(Window, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(Window, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetHoverOffset() const", AS_METHODPR(Window, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_hoverOffset() const", AS_METHODPR(Window, GetHoverOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "const IntRect& GetImageBorder() const", AS_METHODPR(Window, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& get_imageBorder() const", AS_METHODPR(Window, GetImageBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "const IntRect& GetImageRect() const", AS_METHODPR(Window, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& get_imageRect() const", AS_METHODPR(Window, GetImageRect, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetIndent() const", AS_METHODPR(Window, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_indent() const", AS_METHODPR(Window, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetIndentSpacing() const", AS_METHODPR(Window, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_indentSpacing() const", AS_METHODPR(Window, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetIndentWidth() const", AS_METHODPR(Window, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_indentWidth() const", AS_METHODPR(Window, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(Window, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntRect& GetLayoutBorder() const", AS_METHODPR(Window, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& get_layoutBorder() const", AS_METHODPR(Window, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetLayoutElementMaxSize() const", AS_METHODPR(Window, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(Window, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(Window, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "LayoutMode GetLayoutMode() const", AS_METHODPR(Window, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "LayoutMode get_layoutMode() const", AS_METHODPR(Window, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetLayoutSpacing() const", AS_METHODPR(Window, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_layoutSpacing() const", AS_METHODPR(Window, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "Material@+ GetMaterial() const", AS_METHODPR(Window, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "Material@+ get_material() const", AS_METHODPR(Window, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "ResourceRef GetMaterialAttr() const", AS_METHODPR(Window, GetMaterialAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Vector2& GetMaxAnchor() const", AS_METHODPR(Window, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Vector2& get_maxAnchor() const", AS_METHODPR(Window, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetMaxHeight() const", AS_METHODPR(Window, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_maxHeight() const", AS_METHODPR(Window, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetMaxOffset() const", AS_METHODPR(Window, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_maxOffset() const", AS_METHODPR(Window, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetMaxSize() const", AS_METHODPR(Window, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_maxSize() const", AS_METHODPR(Window, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetMaxWidth() const", AS_METHODPR(Window, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_maxWidth() const", AS_METHODPR(Window, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Vector2& GetMinAnchor() const", AS_METHODPR(Window, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Vector2& get_minAnchor() const", AS_METHODPR(Window, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetMinHeight() const", AS_METHODPR(Window, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_minHeight() const", AS_METHODPR(Window, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetMinOffset() const", AS_METHODPR(Window, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_minOffset() const", AS_METHODPR(Window, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetMinSize() const", AS_METHODPR(Window, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_minSize() const", AS_METHODPR(Window, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetMinWidth() const", AS_METHODPR(Window, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_minWidth() const", AS_METHODPR(Window, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // bool Window::GetModalAutoDismiss() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "bool GetModalAutoDismiss() const", AS_METHODPR(Window, GetModalAutoDismiss, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_modalAutoDismiss() const", AS_METHODPR(Window, GetModalAutoDismiss, () const, bool), AS_CALL_THISCALL);
    // const Color& Window::GetModalFrameColor() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "const Color& GetModalFrameColor() const", AS_METHODPR(Window, GetModalFrameColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Color& get_modalFrameColor() const", AS_METHODPR(Window, GetModalFrameColor, () const, const Color&), AS_CALL_THISCALL);
    // const IntVector2& Window::GetModalFrameSize() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetModalFrameSize() const", AS_METHODPR(Window, GetModalFrameSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_modalFrameSize() const", AS_METHODPR(Window, GetModalFrameSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Color& Window::GetModalShadeColor() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "const Color& GetModalShadeColor() const", AS_METHODPR(Window, GetModalShadeColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Color& get_modalShadeColor() const", AS_METHODPR(Window, GetModalShadeColor, () const, const Color&), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const String& GetName() const", AS_METHODPR(Window, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const String& get_name() const", AS_METHODPR(Window, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "uint GetNumAttributes() const", AS_METHODPR(Window, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "uint get_numAttributes() const", AS_METHODPR(Window, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "uint GetNumChildren(bool = false) const", AS_METHODPR(Window, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "uint get_numChildren(bool = false) const", AS_METHODPR(Window, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "uint GetNumNetworkAttributes() const", AS_METHODPR(Window, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(Window, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(Window, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(Window, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "float GetOpacity() const", AS_METHODPR(Window, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "float get_opacity() const", AS_METHODPR(Window, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ GetParent() const", AS_METHODPR(Window, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "UIElement@+ get_parent() const", AS_METHODPR(Window, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Vector2& GetPivot() const", AS_METHODPR(Window, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Vector2& get_pivot() const", AS_METHODPR(Window, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetPosition() const", AS_METHODPR(Window, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_position() const", AS_METHODPR(Window, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetPriority() const", AS_METHODPR(Window, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_priority() const", AS_METHODPR(Window, GetPriority, () const, int), AS_CALL_THISCALL);
    // const IntRect& Window::GetResizeBorder() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "const IntRect& GetResizeBorder() const", AS_METHODPR(Window, GetResizeBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& get_resizeBorder() const", AS_METHODPR(Window, GetResizeBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ GetRoot() const", AS_METHODPR(Window, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "UIElement@+ get_root() const", AS_METHODPR(Window, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetScreenPosition() const", AS_METHODPR(Window, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_screenPosition() const", AS_METHODPR(Window, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetSize() const", AS_METHODPR(Window, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_size() const", AS_METHODPR(Window, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool GetSortChildren() const", AS_METHODPR(Window, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_sortChildren() const", AS_METHODPR(Window, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(Window, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(Window_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Window", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(Window_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "Texture@+ GetTexture() const", AS_METHODPR(Window, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "Texture@+ get_texture() const", AS_METHODPR(Window, GetTexture, () const, Texture*), AS_CALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "ResourceRef GetTextureAttr() const", AS_METHODPR(Window, GetTextureAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "TraversalMode GetTraversalMode() const", AS_METHODPR(Window, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "TraversalMode get_traversalMode() const", AS_METHODPR(Window, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "StringHash GetType() const", AS_METHODPR(Window, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "StringHash get_type() const", AS_METHODPR(Window, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "const String& GetTypeName() const", AS_METHODPR(Window, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const String& get_typeName() const", AS_METHODPR(Window, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool GetUseDerivedOpacity() const", AS_METHODPR(Window, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_useDerivedOpacity() const", AS_METHODPR(Window, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(Window, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const VariantMap& GetVars() const", AS_METHODPR(Window, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(Window, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(Window, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetWidth() const", AS_METHODPR(Window, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_width() const", AS_METHODPR(Window, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool HasColorGradient() const", AS_METHODPR(Window, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_colorGradient() const", AS_METHODPR(Window, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "bool HasEventHandlers() const", AS_METHODPR(Window, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool HasFocus() const", AS_METHODPR(Window, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_focus() const", AS_METHODPR(Window, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(Window, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(Window, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool HasTag(const String&in) const", AS_METHODPR(Window, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void InsertChild(uint, UIElement@+)", AS_METHODPR(Window, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsChildOf(UIElement@+) const", AS_METHODPR(Window, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsEditable() const", AS_METHODPR(Window, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_editable() const", AS_METHODPR(Window, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsElementEventSender() const", AS_METHODPR(Window, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_elementEventSender() const", AS_METHODPR(Window, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsEnabled() const", AS_METHODPR(Window, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_enabled() const", AS_METHODPR(Window, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsEnabledSelf() const", AS_METHODPR(Window, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_enabledSelf() const", AS_METHODPR(Window, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsFixedHeight() const", AS_METHODPR(Window, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_fixedHeight() const", AS_METHODPR(Window, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsFixedSize() const", AS_METHODPR(Window, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_fixedSize() const", AS_METHODPR(Window, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsFixedWidth() const", AS_METHODPR(Window, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_fixedWidth() const", AS_METHODPR(Window, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsHovering() const", AS_METHODPR(Window, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_hovering() const", AS_METHODPR(Window, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsInside(IntVector2, bool)", AS_METHODPR(Window, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(Window, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "bool IsInstanceOf(StringHash) const", AS_METHODPR(Window, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsInternal() const", AS_METHODPR(Window, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_internal() const", AS_METHODPR(Window, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool Window::IsModal() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "bool IsModal() const", AS_METHODPR(Window, IsModal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_modal() const", AS_METHODPR(Window, IsModal, () const, bool), AS_CALL_THISCALL);
    // bool Window::IsMovable() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "bool IsMovable() const", AS_METHODPR(Window, IsMovable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_movable() const", AS_METHODPR(Window, IsMovable, () const, bool), AS_CALL_THISCALL);
    // bool Window::IsResizable() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "bool IsResizable() const", AS_METHODPR(Window, IsResizable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_resizable() const", AS_METHODPR(Window, IsResizable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsSelected() const", AS_METHODPR(Window, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_selected() const", AS_METHODPR(Window, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool IsTemporary() const", AS_METHODPR(Window, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_temporary() const", AS_METHODPR(Window, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "bool IsTiled() const", AS_METHODPR(Window, IsTiled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_tiled() const", AS_METHODPR(Window, IsTiled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsVisible() const", AS_METHODPR(Window, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_visible() const", AS_METHODPR(Window, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsVisibleEffective() const", AS_METHODPR(Window, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_visibleEffective() const", AS_METHODPR(Window, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsWheelHandler() const", AS_METHODPR(Window, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(Window, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool Load(Deserializer&)", AS_METHODPR(Window, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Window, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(Window, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool LoadXML(const XMLElement&in)", AS_METHODPR(Window, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(Window, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool LoadXML(Deserializer&)", AS_METHODPR(Window, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void MarkNetworkUpdate()", AS_METHODPR(Window, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Window, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(Window, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Window, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Window::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Window, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Window::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Window, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(Window, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(Window, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // void Window::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(Window, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // void Window::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Window, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(Window, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(Window, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // void Window::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(Window, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnIndentSet()", AS_METHODPR(Window, OnIndentSet, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Window, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(Window, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(Window, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(Window, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnSetEditable()", AS_METHODPR(Window, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnTextInput(const String&in)", AS_METHODPR(Window, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(Window, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(Window, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(Window, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Window", "int Refs() const", AS_METHODPR(Window, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_refs() const", AS_METHODPR(Window, Refs, () const, int), AS_CALL_THISCALL);
    // static void Window::RegisterObject(Context* context) | File: ../UI/Window.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Window", asBEHAVE_RELEASE, "void f()", AS_METHODPR(Window, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void Remove()", AS_METHODPR(Window, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void RemoveAllChildren()", AS_METHODPR(Window, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void RemoveAllTags()", AS_METHODPR(Window, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(Window, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(Window, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void RemoveChildAtIndex(uint)", AS_METHODPR(Window, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void RemoveInstanceDefault()", AS_METHODPR(Window, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void RemoveObjectAnimation()", AS_METHODPR(Window, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool RemoveTag(const String&in)", AS_METHODPR(Window, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void ResetDeepEnabled()", AS_METHODPR(Window, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void ResetToDefault()", AS_METHODPR(Window, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool Save(Serializer&) const", AS_METHODPR(Window, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool SaveDefaultAttributes() const", AS_METHODPR(Window, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "bool SaveJSON(JSONValue&) const", AS_METHODPR(Window, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool SaveXML(XMLElement&) const", AS_METHODPR(Window, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(Window, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(Window, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void SendEvent(StringHash)", AS_METHODPR(Window, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(Window, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(Window, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetAnimationEnabled(bool)", AS_METHODPR(Window, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_animationEnabled(bool)", AS_METHODPR(Window, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetAnimationTime(float)", AS_METHODPR(Window, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(Window, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(Window, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(Window, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(Window, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(Window, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(Window, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(Window, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetBlendMode(BlendMode)", AS_METHODPR(Window, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_blendMode(BlendMode)", AS_METHODPR(Window, SetBlendMode, (BlendMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void SetBlockEvents(bool)", AS_METHODPR(Window, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetBorder(const IntRect&in)", AS_METHODPR(Window, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_border(const IntRect&in)", AS_METHODPR(Window, SetBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetBringToBack(bool)", AS_METHODPR(Window, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_bringToBack(bool)", AS_METHODPR(Window, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetBringToFront(bool)", AS_METHODPR(Window, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_bringToFront(bool)", AS_METHODPR(Window, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(Window, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetClipBorder(const IntRect&in)", AS_METHODPR(Window, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_clipBorder(const IntRect&in)", AS_METHODPR(Window, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetClipChildren(bool)", AS_METHODPR(Window, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_clipChildren(bool)", AS_METHODPR(Window, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetColor(const Color&in)", AS_METHODPR(Window, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_color(const Color&in)", AS_METHODPR(Window, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetColor(Corner, const Color&in)", AS_METHODPR(Window, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_colors(Corner, const Color&in)", AS_METHODPR(Window, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetDeepEnabled(bool)", AS_METHODPR(Window, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(Window, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(Window, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetDisabledOffset(const IntVector2&in)", AS_METHODPR(Window, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_disabledOffset(const IntVector2&in)", AS_METHODPR(Window, SetDisabledOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetDisabledOffset(int, int)", AS_METHODPR(Window, SetDisabledOffset, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(Window, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(Window, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetEditable(bool)", AS_METHODPR(Window, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_editable(bool)", AS_METHODPR(Window, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetElementEventSender(bool)", AS_METHODPR(Window, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_elementEventSender(bool)", AS_METHODPR(Window, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetEnableAnchor(bool)", AS_METHODPR(Window, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_enableAnchor(bool)", AS_METHODPR(Window, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetEnabled(bool)", AS_METHODPR(Window, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_enabled(bool)", AS_METHODPR(Window, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetEnabledRecursive(bool)", AS_METHODPR(Window, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetFixedHeight(int)", AS_METHODPR(Window, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void Window::SetFixedHeightResizing(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetFixedHeightResizing(bool)", AS_METHODPR(Window, SetFixedHeightResizing, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_fixedHeightResizing(bool)", AS_METHODPR(Window, SetFixedHeightResizing, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(Window, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetFixedSize(int, int)", AS_METHODPR(Window, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetFixedWidth(int)", AS_METHODPR(Window, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void Window::SetFixedWidthResizing(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetFixedWidthResizing(bool)", AS_METHODPR(Window, SetFixedWidthResizing, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_fixedWidthResizing(bool)", AS_METHODPR(Window, SetFixedWidthResizing, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetFocus(bool)", AS_METHODPR(Window, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_focus(bool)", AS_METHODPR(Window, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetFocusMode(FocusMode)", AS_METHODPR(Window, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_focusMode(FocusMode)", AS_METHODPR(Window, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetFullImageRect()", AS_METHODPR(Window, SetFullImageRect, (), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(Window, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(Window, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetHeight(int)", AS_METHODPR(Window, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_height(int)", AS_METHODPR(Window, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(Window, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(Window, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetHovering(bool)", AS_METHODPR(Window, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetHoverOffset(const IntVector2&in)", AS_METHODPR(Window, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_hoverOffset(const IntVector2&in)", AS_METHODPR(Window, SetHoverOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetHoverOffset(int, int)", AS_METHODPR(Window, SetHoverOffset, (int, int), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetImageBorder(const IntRect&in)", AS_METHODPR(Window, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_imageBorder(const IntRect&in)", AS_METHODPR(Window, SetImageBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetImageRect(const IntRect&in)", AS_METHODPR(Window, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_imageRect(const IntRect&in)", AS_METHODPR(Window, SetImageRect, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetIndent(int)", AS_METHODPR(Window, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_indent(int)", AS_METHODPR(Window, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetIndentSpacing(int)", AS_METHODPR(Window, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_indentSpacing(int)", AS_METHODPR(Window, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void SetInstanceDefault(bool)", AS_METHODPR(Window, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(Window, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetInternal(bool)", AS_METHODPR(Window, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_internal(bool)", AS_METHODPR(Window, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(Window, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(Window, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(Window, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(Window, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(Window, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetLayoutMode(LayoutMode)", AS_METHODPR(Window, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_layoutMode(LayoutMode)", AS_METHODPR(Window, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetLayoutSpacing(int)", AS_METHODPR(Window, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_layoutSpacing(int)", AS_METHODPR(Window, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetMaterial(Material@+)", AS_METHODPR(Window, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_material(Material@+)", AS_METHODPR(Window, SetMaterial, (Material*), void), AS_CALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetMaterialAttr(const ResourceRef&in)", AS_METHODPR(Window, SetMaterialAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(Window, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(Window, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxAnchor(float, float)", AS_METHODPR(Window, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxHeight(int)", AS_METHODPR(Window, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_maxHeight(int)", AS_METHODPR(Window, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(Window, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(Window, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(Window, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_maxSize(const IntVector2&in)", AS_METHODPR(Window, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxSize(int, int)", AS_METHODPR(Window, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxWidth(int)", AS_METHODPR(Window, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_maxWidth(int)", AS_METHODPR(Window, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(Window, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_minAnchor(const Vector2&in)", AS_METHODPR(Window, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinAnchor(float, float)", AS_METHODPR(Window, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinHeight(int)", AS_METHODPR(Window, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_minHeight(int)", AS_METHODPR(Window, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(Window, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_minOffset(const IntVector2&in)", AS_METHODPR(Window, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinSize(const IntVector2&in)", AS_METHODPR(Window, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_minSize(const IntVector2&in)", AS_METHODPR(Window, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinSize(int, int)", AS_METHODPR(Window, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinWidth(int)", AS_METHODPR(Window, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_minWidth(int)", AS_METHODPR(Window, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void Window::SetModal(bool modal) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetModal(bool)", AS_METHODPR(Window, SetModal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_modal(bool)", AS_METHODPR(Window, SetModal, (bool), void), AS_CALL_THISCALL);
    // void Window::SetModalAutoDismiss(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetModalAutoDismiss(bool)", AS_METHODPR(Window, SetModalAutoDismiss, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_modalAutoDismiss(bool)", AS_METHODPR(Window, SetModalAutoDismiss, (bool), void), AS_CALL_THISCALL);
    // void Window::SetModalFrameColor(const Color& color) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetModalFrameColor(const Color&in)", AS_METHODPR(Window, SetModalFrameColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_modalFrameColor(const Color&in)", AS_METHODPR(Window, SetModalFrameColor, (const Color&), void), AS_CALL_THISCALL);
    // void Window::SetModalFrameSize(const IntVector2& size) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetModalFrameSize(const IntVector2&in)", AS_METHODPR(Window, SetModalFrameSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_modalFrameSize(const IntVector2&in)", AS_METHODPR(Window, SetModalFrameSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void Window::SetModalShadeColor(const Color& color) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetModalShadeColor(const Color&in)", AS_METHODPR(Window, SetModalShadeColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_modalShadeColor(const Color&in)", AS_METHODPR(Window, SetModalShadeColor, (const Color&), void), AS_CALL_THISCALL);
    // void Window::SetMovable(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetMovable(bool)", AS_METHODPR(Window, SetMovable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_movable(bool)", AS_METHODPR(Window, SetMovable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetName(const String&in)", AS_METHODPR(Window, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_name(const String&in)", AS_METHODPR(Window, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(Window, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(Window, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(Window, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetOpacity(float)", AS_METHODPR(Window, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_opacity(float)", AS_METHODPR(Window, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(Window, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetPivot(const Vector2&in)", AS_METHODPR(Window, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_pivot(const Vector2&in)", AS_METHODPR(Window, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetPivot(float, float)", AS_METHODPR(Window, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetPosition(const IntVector2&in)", AS_METHODPR(Window, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_position(const IntVector2&in)", AS_METHODPR(Window, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetPosition(int, int)", AS_METHODPR(Window, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetPriority(int)", AS_METHODPR(Window, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_priority(int)", AS_METHODPR(Window, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(Window, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void Window::SetResizable(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetResizable(bool)", AS_METHODPR(Window, SetResizable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_resizable(bool)", AS_METHODPR(Window, SetResizable, (bool), void), AS_CALL_THISCALL);
    // void Window::SetResizeBorder(const IntRect& rect) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetResizeBorder(const IntRect&in)", AS_METHODPR(Window, SetResizeBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_resizeBorder(const IntRect&in)", AS_METHODPR(Window, SetResizeBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetSelected(bool)", AS_METHODPR(Window, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_selected(bool)", AS_METHODPR(Window, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetSize(const IntVector2&in)", AS_METHODPR(Window, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_size(const IntVector2&in)", AS_METHODPR(Window, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetSize(int, int)", AS_METHODPR(Window, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetSortChildren(bool)", AS_METHODPR(Window, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_sortChildren(bool)", AS_METHODPR(Window, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(Window, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool SetStyle(const XMLElement&in)", AS_METHODPR(Window, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(Window, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(Window_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void SetTemporary(bool)", AS_METHODPR(Window, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_temporary(bool)", AS_METHODPR(Window, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetTexture(Texture@+)", AS_METHODPR(Window, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_texture(Texture@+)", AS_METHODPR(Window, SetTexture, (Texture*), void), AS_CALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetTextureAttr(const ResourceRef&in)", AS_METHODPR(Window, SetTextureAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetTiled(bool)", AS_METHODPR(Window, SetTiled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_tiled(bool)", AS_METHODPR(Window, SetTiled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetTraversalMode(TraversalMode)", AS_METHODPR(Window, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_traversalMode(TraversalMode)", AS_METHODPR(Window, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetUseDerivedOpacity(bool)", AS_METHODPR(Window, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_useDerivedOpacity(bool)", AS_METHODPR(Window, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(Window, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(Window, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(Window, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetVisible(bool)", AS_METHODPR(Window, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_visible(bool)", AS_METHODPR(Window, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetWidth(int)", AS_METHODPR(Window, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_width(int)", AS_METHODPR(Window, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SortChildren()", AS_METHODPR(Window, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void UnsubscribeFromAllEvents()", AS_METHODPR(Window, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(Window_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(Window, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(Window, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(Window, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void Update(float)", AS_METHODPR(Window, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void UpdateLayout()", AS_METHODPR(Window, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Window", "int WeakRefs() const", AS_METHODPR(Window, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_weakRefs() const", AS_METHODPR(Window, WeakRefs, () const, int), AS_CALL_THISCALL);
    // explicit Window::Window(Context* context) | File: ../UI/Window.h
    engine->RegisterObjectBehaviour("Window", asBEHAVE_FACTORY, "Window@+ f()", AS_FUNCTION(Window_Window_Context), AS_CALL_CDECL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(Window, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(Window, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(Window, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_BorderImage
    REGISTER_MANUAL_PART_BorderImage(Window, "Window")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(Window, "Window")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(Window, "Window")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(Window, "Window")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(Window, "Window")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(Window, "Window")
#endif
#ifdef REGISTER_MANUAL_PART_Window
    REGISTER_MANUAL_PART_Window(Window, "Window")
#endif
    RegisterSubclass<BorderImage, Window>(engine, "BorderImage", "Window");
    RegisterSubclass<UIElement, Window>(engine, "UIElement", "Window");
    RegisterSubclass<Animatable, Window>(engine, "Animatable", "Window");
    RegisterSubclass<Serializable, Window>(engine, "Serializable", "Window");
    RegisterSubclass<Object, Window>(engine, "Object", "Window");
    RegisterSubclass<RefCounted, Window>(engine, "RefCounted", "Window");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("WorkQueue", asBEHAVE_ADDREF, "void f()", AS_METHODPR(WorkQueue, AddRef, (), void), AS_CALL_THISCALL);
    // void WorkQueue::AddWorkItem(const SharedPtr<WorkItem>& item) | File: ../Core/WorkQueue.h
    // Error: type "const SharedPtr<WorkItem>&" can not automatically bind
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void WorkQueue::Complete(unsigned priority) | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "void Complete(uint)", AS_METHODPR(WorkQueue, Complete, (unsigned), void), AS_CALL_THISCALL);
    // void WorkQueue::CreateThreads(unsigned numThreads) | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "void CreateThreads(uint)", AS_METHODPR(WorkQueue, CreateThreads, (unsigned), void), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "bool GetBlockEvents() const", AS_METHODPR(WorkQueue, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "const String& GetCategory() const", AS_METHODPR(WorkQueue, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "const String& get_category() const", AS_METHODPR(WorkQueue, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "VariantMap& GetEventDataMap() const", AS_METHODPR(WorkQueue, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "Object@+ GetEventSender() const", AS_METHODPR(WorkQueue, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // SharedPtr<WorkItem> WorkQueue::GetFreeItem() | File: ../Core/WorkQueue.h
    // Error: type "SharedPtr<WorkItem>" can not automatically bind
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(WorkQueue, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(WorkQueue, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "const VariantMap& GetGlobalVars() const", AS_METHODPR(WorkQueue, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "const VariantMap& get_globalVars() const", AS_METHODPR(WorkQueue, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int WorkQueue::GetNonThreadedWorkMs() const | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "int GetNonThreadedWorkMs() const", AS_METHODPR(WorkQueue, GetNonThreadedWorkMs, () const, int), AS_CALL_THISCALL);
    // unsigned WorkQueue::GetNumThreads() const | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "uint GetNumThreads() const", AS_METHODPR(WorkQueue, GetNumThreads, () const, unsigned), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(WorkQueue, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // int WorkQueue::GetTolerance() const | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "int GetTolerance() const", AS_METHODPR(WorkQueue, GetTolerance, () const, int), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "StringHash GetType() const", AS_METHODPR(WorkQueue, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "StringHash get_type() const", AS_METHODPR(WorkQueue, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "const String& GetTypeName() const", AS_METHODPR(WorkQueue, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "const String& get_typeName() const", AS_METHODPR(WorkQueue, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "bool HasEventHandlers() const", AS_METHODPR(WorkQueue, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(WorkQueue, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(WorkQueue, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool WorkQueue::IsCompleted(unsigned priority) const | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "bool IsCompleted(uint) const", AS_METHODPR(WorkQueue, IsCompleted, (unsigned) const, bool), AS_CALL_THISCALL);
    // bool WorkQueue::IsCompleting() const | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "bool IsCompleting() const", AS_METHODPR(WorkQueue, IsCompleting, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "bool IsInstanceOf(StringHash) const", AS_METHODPR(WorkQueue, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(WorkQueue, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // void WorkQueue::Pause() | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "void Pause()", AS_METHODPR(WorkQueue, Pause, (), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("WorkQueue", "int Refs() const", AS_METHODPR(WorkQueue, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "int get_refs() const", AS_METHODPR(WorkQueue, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("WorkQueue", asBEHAVE_RELEASE, "void f()", AS_METHODPR(WorkQueue, ReleaseRef, (), void), AS_CALL_THISCALL);
    // bool WorkQueue::RemoveWorkItem(SharedPtr<WorkItem> item) | File: ../Core/WorkQueue.h
    // Error: type "SharedPtr<WorkItem>" can not automatically bind
    // unsigned WorkQueue::RemoveWorkItems(const Vector<SharedPtr<WorkItem>>& items) | File: ../Core/WorkQueue.h
    // Error: type "const Vector<SharedPtr<WorkItem>>&" can not automatically bind
    // void WorkQueue::Resume() | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "void Resume()", AS_METHODPR(WorkQueue, Resume, (), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void SendEvent(StringHash)", AS_METHODPR(WorkQueue, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(WorkQueue, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void SetBlockEvents(bool)", AS_METHODPR(WorkQueue, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(WorkQueue, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(WorkQueue, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void WorkQueue::SetNonThreadedWorkMs(int ms) | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "void SetNonThreadedWorkMs(int)", AS_METHODPR(WorkQueue, SetNonThreadedWorkMs, (int), void), AS_CALL_THISCALL);
    // void WorkQueue::SetTolerance(int tolerance) | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "void SetTolerance(int)", AS_METHODPR(WorkQueue, SetTolerance, (int), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void UnsubscribeFromAllEvents()", AS_METHODPR(WorkQueue, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(WorkQueue_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(WorkQueue, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(WorkQueue, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(WorkQueue, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("WorkQueue", "int WeakRefs() const", AS_METHODPR(WorkQueue, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "int get_weakRefs() const", AS_METHODPR(WorkQueue, WeakRefs, () const, int), AS_CALL_THISCALL);
    // explicit WorkQueue::WorkQueue(Context* context) | File: ../Core/WorkQueue.h
    engine->RegisterObjectBehaviour("WorkQueue", asBEHAVE_FACTORY, "WorkQueue@+ f()", AS_FUNCTION(WorkQueue_WorkQueue_Context), AS_CALL_CDECL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(WorkQueue, "WorkQueue")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(WorkQueue, "WorkQueue")
#endif
#ifdef REGISTER_MANUAL_PART_WorkQueue
    REGISTER_MANUAL_PART_WorkQueue(WorkQueue, "WorkQueue")
#endif
    RegisterSubclass<Object, WorkQueue>(engine, "Object", "WorkQueue");
    RegisterSubclass<RefCounted, WorkQueue>(engine, "RefCounted", "WorkQueue");

    // int WindowModeParams::height_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("WindowModeParams", "int height", offsetof(WindowModeParams, height_));
    // ScreenModeParams WindowModeParams::screenParams_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("WindowModeParams", "ScreenModeParams screenParams", offsetof(WindowModeParams, screenParams_));
    // int WindowModeParams::width_ | File: ../Graphics/Graphics.h
    engine->RegisterObjectProperty("WindowModeParams", "int width", offsetof(WindowModeParams, width_));
    // WindowModeParams& WindowModeParams::operator=(const WindowModeParams&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<WindowModeParams>(engine, "WindowModeParams");
#ifdef REGISTER_MANUAL_PART_WindowModeParams
    REGISTER_MANUAL_PART_WindowModeParams(WindowModeParams, "WindowModeParams")
#endif

}

}
