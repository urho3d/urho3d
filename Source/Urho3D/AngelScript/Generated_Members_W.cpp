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
    engine->RegisterObjectMethod("Window", "void AddChild(UIElement@+)", asMETHODPR(Window, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Window", asBEHAVE_ADDREF, "void f()", asMETHODPR(Window, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void AddTag(const String&in)", asMETHODPR(Window, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void AddTags(const String&in, int8 = ';')", asMETHODPR(Window, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void AddTags(Array<String>@+)", asFUNCTION(Window_AddTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void AdjustScissor(IntRect&)", asMETHODPR(Window, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void AllocateNetworkState()", asMETHODPR(Window, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void ApplyAttributes()", asMETHODPR(Window, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void BringToFront()", asMETHODPR(Window, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(Window, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void DisableLayoutUpdate()", asMETHODPR(Window, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(Window, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void EnableLayoutUpdate()", asMETHODPR(Window, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool FilterAttributes(XMLElement&) const", asMETHODPR(Window, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "uint FindChild(UIElement@+) const", asMETHODPR(Window, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "bool GetAnimationEnabled() const", asMETHODPR(Window, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_animationEnabled() const", asMETHODPR(Window, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const String& GetAppliedStyle() const", asMETHODPR(Window, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const String& get_style() const", asMETHODPR(Window, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "Variant GetAttribute(uint) const", asMETHODPR(Window, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "Variant get_attributes(uint) const", asMETHODPR(Window, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "Variant GetAttribute(const String&in) const", asMETHODPR(Window, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(Window, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(Window, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(Window, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(Window, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "Variant GetAttributeDefault(uint) const", asMETHODPR(Window, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "Variant get_attributeDefaults(uint) const", asMETHODPR(Window, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(Window, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void Window::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/Window.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // BlendMode BorderImage::GetBlendMode() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "BlendMode GetBlendMode() const", asMETHODPR(Window, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "BlendMode get_blendMode() const", asMETHODPR(Window, GetBlendMode, () const, BlendMode), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "bool GetBlockEvents() const", asMETHODPR(Window, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const IntRect& BorderImage::GetBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "const IntRect& GetBorder() const", asMETHODPR(Window, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& get_border() const", asMETHODPR(Window, GetBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool GetBringToBack() const", asMETHODPR(Window, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_bringToBack() const", asMETHODPR(Window, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool GetBringToFront() const", asMETHODPR(Window, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_bringToFront() const", asMETHODPR(Window, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "const String& GetCategory() const", asMETHODPR(Window, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const String& get_category() const", asMETHODPR(Window, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ GetChild(uint) const", asMETHODPR(Window, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "UIElement@+ get_children(uint) const", asMETHODPR(Window, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(Window, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(Window, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetChildOffset() const", asMETHODPR(Window, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_childOffset() const", asMETHODPR(Window, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "Array<UIElement@>@ GetChildren() const", asFUNCTION(Window_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(Window_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(Window_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntRect& GetClipBorder() const", asMETHODPR(Window, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& get_clipBorder() const", asMETHODPR(Window, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool GetClipChildren() const", asMETHODPR(Window, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_clipChildren() const", asMETHODPR(Window, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Color& GetColor(Corner) const", asMETHODPR(Window, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Color& get_colors(Corner) const", asMETHODPR(Window, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Color& GetColorAttr() const", asMETHODPR(Window, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "IntRect GetCombinedScreenRect()", asMETHODPR(Window, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "IntRect get_combinedScreenRect()", asMETHODPR(Window, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(Window, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Color& GetDerivedColor() const", asMETHODPR(Window, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "float GetDerivedOpacity() const", asMETHODPR(Window, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "float get_derivedOpacity() const", asMETHODPR(Window, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetDisabledOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetDisabledOffset() const", asMETHODPR(Window, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_disabledOffset() const", asMETHODPR(Window, GetDisabledOffset, () const, const IntVector2&), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(Window, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(Window, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "uint GetDragButtonCount() const", asMETHODPR(Window, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "uint get_dragButtonCount() const", asMETHODPR(Window, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(Window, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(Window, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(Window, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ GetElementEventSender() const", asMETHODPR(Window, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool GetEnableAnchor() const", asMETHODPR(Window, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_enableAnchor() const", asMETHODPR(Window, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "VariantMap& GetEventDataMap() const", asMETHODPR(Window, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "Object@+ GetEventSender() const", asMETHODPR(Window, GetEventSender, () const, Object*), asCALL_THISCALL);
    // bool Window::GetFixedHeightResizing() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "bool GetFixedHeightResizing() const", asMETHODPR(Window, GetFixedHeightResizing, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_fixedHeightResizing() const", asMETHODPR(Window, GetFixedHeightResizing, () const, bool), asCALL_THISCALL);
    // bool Window::GetFixedWidthResizing() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "bool GetFixedWidthResizing() const", asMETHODPR(Window, GetFixedWidthResizing, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_fixedWidthResizing() const", asMETHODPR(Window, GetFixedWidthResizing, () const, bool), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "FocusMode GetFocusMode() const", asMETHODPR(Window, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "FocusMode get_focusMode() const", asMETHODPR(Window, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(Window, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Variant& get_globalVar(StringHash) const", asMETHODPR(Window, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "const VariantMap& GetGlobalVars() const", asMETHODPR(Window, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const VariantMap& get_globalVars() const", asMETHODPR(Window, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetHeight() const", asMETHODPR(Window, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_height() const", asMETHODPR(Window, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(Window, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(Window, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const IntVector2& BorderImage::GetHoverOffset() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetHoverOffset() const", asMETHODPR(Window, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_hoverOffset() const", asMETHODPR(Window, GetHoverOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageBorder() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "const IntRect& GetImageBorder() const", asMETHODPR(Window, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& get_imageBorder() const", asMETHODPR(Window, GetImageBorder, () const, const IntRect&), asCALL_THISCALL);
    // const IntRect& BorderImage::GetImageRect() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "const IntRect& GetImageRect() const", asMETHODPR(Window, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& get_imageRect() const", asMETHODPR(Window, GetImageRect, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetIndent() const", asMETHODPR(Window, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_indent() const", asMETHODPR(Window, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetIndentSpacing() const", asMETHODPR(Window, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_indentSpacing() const", asMETHODPR(Window, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetIndentWidth() const", asMETHODPR(Window, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_indentWidth() const", asMETHODPR(Window, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(Window, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntRect& GetLayoutBorder() const", asMETHODPR(Window, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& get_layoutBorder() const", asMETHODPR(Window, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetLayoutElementMaxSize() const", asMETHODPR(Window, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(Window, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Vector2& get_layoutFlexScale() const", asMETHODPR(Window, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "LayoutMode GetLayoutMode() const", asMETHODPR(Window, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "LayoutMode get_layoutMode() const", asMETHODPR(Window, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetLayoutSpacing() const", asMETHODPR(Window, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_layoutSpacing() const", asMETHODPR(Window, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // Material* BorderImage::GetMaterial() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "Material@+ GetMaterial() const", asMETHODPR(Window, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "Material@+ get_material() const", asMETHODPR(Window, GetMaterial, () const, Material*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetMaterialAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "ResourceRef GetMaterialAttr() const", asMETHODPR(Window, GetMaterialAttr, () const, ResourceRef), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Vector2& GetMaxAnchor() const", asMETHODPR(Window, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Vector2& get_maxAnchor() const", asMETHODPR(Window, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetMaxHeight() const", asMETHODPR(Window, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_maxHeight() const", asMETHODPR(Window, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetMaxOffset() const", asMETHODPR(Window, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_maxOffset() const", asMETHODPR(Window, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetMaxSize() const", asMETHODPR(Window, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_maxSize() const", asMETHODPR(Window, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetMaxWidth() const", asMETHODPR(Window, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_maxWidth() const", asMETHODPR(Window, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Vector2& GetMinAnchor() const", asMETHODPR(Window, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Vector2& get_minAnchor() const", asMETHODPR(Window, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetMinHeight() const", asMETHODPR(Window, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_minHeight() const", asMETHODPR(Window, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetMinOffset() const", asMETHODPR(Window, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_minOffset() const", asMETHODPR(Window, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetMinSize() const", asMETHODPR(Window, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_minSize() const", asMETHODPR(Window, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetMinWidth() const", asMETHODPR(Window, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_minWidth() const", asMETHODPR(Window, GetMinWidth, () const, int), asCALL_THISCALL);
    // bool Window::GetModalAutoDismiss() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "bool GetModalAutoDismiss() const", asMETHODPR(Window, GetModalAutoDismiss, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_modalAutoDismiss() const", asMETHODPR(Window, GetModalAutoDismiss, () const, bool), asCALL_THISCALL);
    // const Color& Window::GetModalFrameColor() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "const Color& GetModalFrameColor() const", asMETHODPR(Window, GetModalFrameColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Color& get_modalFrameColor() const", asMETHODPR(Window, GetModalFrameColor, () const, const Color&), asCALL_THISCALL);
    // const IntVector2& Window::GetModalFrameSize() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetModalFrameSize() const", asMETHODPR(Window, GetModalFrameSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_modalFrameSize() const", asMETHODPR(Window, GetModalFrameSize, () const, const IntVector2&), asCALL_THISCALL);
    // const Color& Window::GetModalShadeColor() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "const Color& GetModalShadeColor() const", asMETHODPR(Window, GetModalShadeColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Color& get_modalShadeColor() const", asMETHODPR(Window, GetModalShadeColor, () const, const Color&), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const String& GetName() const", asMETHODPR(Window, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const String& get_name() const", asMETHODPR(Window, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "uint GetNumAttributes() const", asMETHODPR(Window, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "uint get_numAttributes() const", asMETHODPR(Window, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "uint GetNumChildren(bool = false) const", asMETHODPR(Window, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "uint get_numChildren(bool = false) const", asMETHODPR(Window, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "uint GetNumNetworkAttributes() const", asMETHODPR(Window, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(Window, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(Window, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(Window, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "float GetOpacity() const", asMETHODPR(Window, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "float get_opacity() const", asMETHODPR(Window, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ GetParent() const", asMETHODPR(Window, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "UIElement@+ get_parent() const", asMETHODPR(Window, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Vector2& GetPivot() const", asMETHODPR(Window, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const Vector2& get_pivot() const", asMETHODPR(Window, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetPosition() const", asMETHODPR(Window, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_position() const", asMETHODPR(Window, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetPriority() const", asMETHODPR(Window, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_priority() const", asMETHODPR(Window, GetPriority, () const, int), asCALL_THISCALL);
    // const IntRect& Window::GetResizeBorder() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "const IntRect& GetResizeBorder() const", asMETHODPR(Window, GetResizeBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntRect& get_resizeBorder() const", asMETHODPR(Window, GetResizeBorder, () const, const IntRect&), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ GetRoot() const", asMETHODPR(Window, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "UIElement@+ get_root() const", asMETHODPR(Window, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetScreenPosition() const", asMETHODPR(Window, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_screenPosition() const", asMETHODPR(Window, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const IntVector2& GetSize() const", asMETHODPR(Window, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const IntVector2& get_size() const", asMETHODPR(Window, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool GetSortChildren() const", asMETHODPR(Window, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_sortChildren() const", asMETHODPR(Window, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(Window, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "Array<String>@ GetTags() const", asFUNCTION(Window_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("Window", "Array<String>@ get_tags() const", asFUNCTION(Window_GetTags_void), asCALL_CDECL_OBJFIRST);
    // Texture* BorderImage::GetTexture() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "Texture@+ GetTexture() const", asMETHODPR(Window, GetTexture, () const, Texture*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "Texture@+ get_texture() const", asMETHODPR(Window, GetTexture, () const, Texture*), asCALL_THISCALL);
    // ResourceRef BorderImage::GetTextureAttr() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "ResourceRef GetTextureAttr() const", asMETHODPR(Window, GetTextureAttr, () const, ResourceRef), asCALL_THISCALL);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "TraversalMode GetTraversalMode() const", asMETHODPR(Window, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "TraversalMode get_traversalMode() const", asMETHODPR(Window, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "StringHash GetType() const", asMETHODPR(Window, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "StringHash get_type() const", asMETHODPR(Window, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "const String& GetTypeName() const", asMETHODPR(Window, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "const String& get_typeName() const", asMETHODPR(Window, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool GetUseDerivedOpacity() const", asMETHODPR(Window, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_useDerivedOpacity() const", asMETHODPR(Window, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(Window, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "const VariantMap& GetVars() const", asMETHODPR(Window, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(Window, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(Window, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "int GetWidth() const", asMETHODPR(Window, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_width() const", asMETHODPR(Window, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool HasColorGradient() const", asMETHODPR(Window, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_colorGradient() const", asMETHODPR(Window, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "bool HasEventHandlers() const", asMETHODPR(Window, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool HasFocus() const", asMETHODPR(Window, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_focus() const", asMETHODPR(Window, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(Window, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(Window, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool HasTag(const String&in) const", asMETHODPR(Window, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void InsertChild(uint, UIElement@+)", asMETHODPR(Window, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsChildOf(UIElement@+) const", asMETHODPR(Window, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsEditable() const", asMETHODPR(Window, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_editable() const", asMETHODPR(Window, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsElementEventSender() const", asMETHODPR(Window, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_elementEventSender() const", asMETHODPR(Window, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsEnabled() const", asMETHODPR(Window, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_enabled() const", asMETHODPR(Window, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsEnabledSelf() const", asMETHODPR(Window, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_enabledSelf() const", asMETHODPR(Window, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsFixedHeight() const", asMETHODPR(Window, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_fixedHeight() const", asMETHODPR(Window, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsFixedSize() const", asMETHODPR(Window, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_fixedSize() const", asMETHODPR(Window, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsFixedWidth() const", asMETHODPR(Window, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_fixedWidth() const", asMETHODPR(Window, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsHovering() const", asMETHODPR(Window, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_hovering() const", asMETHODPR(Window, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsInside(IntVector2, bool)", asMETHODPR(Window, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(Window, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "bool IsInstanceOf(StringHash) const", asMETHODPR(Window, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsInternal() const", asMETHODPR(Window, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_internal() const", asMETHODPR(Window, IsInternal, () const, bool), asCALL_THISCALL);
    // bool Window::IsModal() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "bool IsModal() const", asMETHODPR(Window, IsModal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_modal() const", asMETHODPR(Window, IsModal, () const, bool), asCALL_THISCALL);
    // bool Window::IsMovable() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "bool IsMovable() const", asMETHODPR(Window, IsMovable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_movable() const", asMETHODPR(Window, IsMovable, () const, bool), asCALL_THISCALL);
    // bool Window::IsResizable() const | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "bool IsResizable() const", asMETHODPR(Window, IsResizable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_resizable() const", asMETHODPR(Window, IsResizable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsSelected() const", asMETHODPR(Window, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_selected() const", asMETHODPR(Window, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool IsTemporary() const", asMETHODPR(Window, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_temporary() const", asMETHODPR(Window, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool BorderImage::IsTiled() const | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "bool IsTiled() const", asMETHODPR(Window, IsTiled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_tiled() const", asMETHODPR(Window, IsTiled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsVisible() const", asMETHODPR(Window, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_visible() const", asMETHODPR(Window, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsVisibleEffective() const", asMETHODPR(Window, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool get_visibleEffective() const", asMETHODPR(Window, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsWheelHandler() const", asMETHODPR(Window, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(Window, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool Load(Deserializer&)", asMETHODPR(Window, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Window, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "bool LoadJSON(const JSONValue&in)", asMETHODPR(Window, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool LoadXML(const XMLElement&in)", asMETHODPR(Window, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(Window, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool LoadXML(Deserializer&)", asMETHODPR(Window, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void MarkNetworkUpdate()", asMETHODPR(Window, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Window, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(Window, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Window, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // void Window::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Window, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // void Window::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Window, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(Window, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool OnDragDropTest(UIElement@+)", asMETHODPR(Window, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // void Window::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(Window, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // void Window::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Window, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(Window, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(Window, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // void Window::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(Window, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnIndentSet()", asMETHODPR(Window, OnIndentSet, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(Window, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnPositionSet(const IntVector2&in)", asMETHODPR(Window, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(Window, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(Window, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnSetEditable()", asMETHODPR(Window, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnTextInput(const String&in)", asMETHODPR(Window, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(Window, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(Window, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(Window, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Window", "int Refs() const", asMETHODPR(Window, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_refs() const", asMETHODPR(Window, Refs, () const, int), asCALL_THISCALL);
    // static void Window::RegisterObject(Context* context) | File: ../UI/Window.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("Window", asBEHAVE_RELEASE, "void f()", asMETHODPR(Window, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void Remove()", asMETHODPR(Window, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void RemoveAllChildren()", asMETHODPR(Window, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void RemoveAllTags()", asMETHODPR(Window, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(Window, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(Window, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void RemoveChildAtIndex(uint)", asMETHODPR(Window, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void RemoveInstanceDefault()", asMETHODPR(Window, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void RemoveObjectAnimation()", asMETHODPR(Window, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool RemoveTag(const String&in)", asMETHODPR(Window, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void ResetDeepEnabled()", asMETHODPR(Window, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void ResetToDefault()", asMETHODPR(Window, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool Save(Serializer&) const", asMETHODPR(Window, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool SaveDefaultAttributes() const", asMETHODPR(Window, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "bool SaveJSON(JSONValue&) const", asMETHODPR(Window, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool SaveXML(XMLElement&) const", asMETHODPR(Window, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(Window, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(Window, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void SendEvent(StringHash)", asMETHODPR(Window, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(Window, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(Window, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetAnimationEnabled(bool)", asMETHODPR(Window, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_animationEnabled(bool)", asMETHODPR(Window, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetAnimationTime(float)", asMETHODPR(Window, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(Window, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "bool set_attributes(uint, const Variant&in)", asMETHODPR(Window, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(Window, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(Window, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(Window, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(Window, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(Window, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void BorderImage::SetBlendMode(BlendMode mode) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetBlendMode(BlendMode)", asMETHODPR(Window, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_blendMode(BlendMode)", asMETHODPR(Window, SetBlendMode, (BlendMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void SetBlockEvents(bool)", asMETHODPR(Window, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetBorder(const IntRect&in)", asMETHODPR(Window, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_border(const IntRect&in)", asMETHODPR(Window, SetBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetBringToBack(bool)", asMETHODPR(Window, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_bringToBack(bool)", asMETHODPR(Window, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetBringToFront(bool)", asMETHODPR(Window, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_bringToFront(bool)", asMETHODPR(Window, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetChildOffset(const IntVector2&in)", asMETHODPR(Window, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetClipBorder(const IntRect&in)", asMETHODPR(Window, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_clipBorder(const IntRect&in)", asMETHODPR(Window, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetClipChildren(bool)", asMETHODPR(Window, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_clipChildren(bool)", asMETHODPR(Window, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetColor(const Color&in)", asMETHODPR(Window, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_color(const Color&in)", asMETHODPR(Window, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetColor(Corner, const Color&in)", asMETHODPR(Window, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_colors(Corner, const Color&in)", asMETHODPR(Window, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetDeepEnabled(bool)", asMETHODPR(Window, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(Window, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_defaultStyle(XMLFile@+)", asMETHODPR(Window, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetDisabledOffset(const IntVector2&in)", asMETHODPR(Window, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_disabledOffset(const IntVector2&in)", asMETHODPR(Window, SetDisabledOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetDisabledOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetDisabledOffset(int, int)", asMETHODPR(Window, SetDisabledOffset, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(Window, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(Window, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetEditable(bool)", asMETHODPR(Window, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_editable(bool)", asMETHODPR(Window, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetElementEventSender(bool)", asMETHODPR(Window, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_elementEventSender(bool)", asMETHODPR(Window, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetEnableAnchor(bool)", asMETHODPR(Window, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_enableAnchor(bool)", asMETHODPR(Window, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetEnabled(bool)", asMETHODPR(Window, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_enabled(bool)", asMETHODPR(Window, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetEnabledRecursive(bool)", asMETHODPR(Window, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetFixedHeight(int)", asMETHODPR(Window, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void Window::SetFixedHeightResizing(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetFixedHeightResizing(bool)", asMETHODPR(Window, SetFixedHeightResizing, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_fixedHeightResizing(bool)", asMETHODPR(Window, SetFixedHeightResizing, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetFixedSize(const IntVector2&in)", asMETHODPR(Window, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetFixedSize(int, int)", asMETHODPR(Window, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetFixedWidth(int)", asMETHODPR(Window, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void Window::SetFixedWidthResizing(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetFixedWidthResizing(bool)", asMETHODPR(Window, SetFixedWidthResizing, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_fixedWidthResizing(bool)", asMETHODPR(Window, SetFixedWidthResizing, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetFocus(bool)", asMETHODPR(Window, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_focus(bool)", asMETHODPR(Window, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetFocusMode(FocusMode)", asMETHODPR(Window, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_focusMode(FocusMode)", asMETHODPR(Window, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void BorderImage::SetFullImageRect() | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetFullImageRect()", asMETHODPR(Window, SetFullImageRect, (), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(Window, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(Window, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetHeight(int)", asMETHODPR(Window, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_height(int)", asMETHODPR(Window, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(Window, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(Window, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetHovering(bool)", asMETHODPR(Window, SetHovering, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(const IntVector2& offset) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetHoverOffset(const IntVector2&in)", asMETHODPR(Window, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_hoverOffset(const IntVector2&in)", asMETHODPR(Window, SetHoverOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void BorderImage::SetHoverOffset(int x, int y) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetHoverOffset(int, int)", asMETHODPR(Window, SetHoverOffset, (int, int), void), asCALL_THISCALL);
    // void BorderImage::SetImageBorder(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetImageBorder(const IntRect&in)", asMETHODPR(Window, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_imageBorder(const IntRect&in)", asMETHODPR(Window, SetImageBorder, (const IntRect&), void), asCALL_THISCALL);
    // void BorderImage::SetImageRect(const IntRect& rect) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetImageRect(const IntRect&in)", asMETHODPR(Window, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_imageRect(const IntRect&in)", asMETHODPR(Window, SetImageRect, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetIndent(int)", asMETHODPR(Window, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_indent(int)", asMETHODPR(Window, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetIndentSpacing(int)", asMETHODPR(Window, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_indentSpacing(int)", asMETHODPR(Window, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void SetInstanceDefault(bool)", asMETHODPR(Window, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(Window, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetInternal(bool)", asMETHODPR(Window, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_internal(bool)", asMETHODPR(Window, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(Window, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(Window, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_layoutBorder(const IntRect&in)", asMETHODPR(Window, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(Window, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(Window, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetLayoutMode(LayoutMode)", asMETHODPR(Window, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_layoutMode(LayoutMode)", asMETHODPR(Window, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetLayoutSpacing(int)", asMETHODPR(Window, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_layoutSpacing(int)", asMETHODPR(Window, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void BorderImage::SetMaterial(Material* material) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetMaterial(Material@+)", asMETHODPR(Window, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_material(Material@+)", asMETHODPR(Window, SetMaterial, (Material*), void), asCALL_THISCALL);
    // void BorderImage::SetMaterialAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetMaterialAttr(const ResourceRef&in)", asMETHODPR(Window, SetMaterialAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(Window, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_maxAnchor(const Vector2&in)", asMETHODPR(Window, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxAnchor(float, float)", asMETHODPR(Window, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxHeight(int)", asMETHODPR(Window, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_maxHeight(int)", asMETHODPR(Window, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(Window, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_maxOffset(const IntVector2&in)", asMETHODPR(Window, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxSize(const IntVector2&in)", asMETHODPR(Window, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_maxSize(const IntVector2&in)", asMETHODPR(Window, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxSize(int, int)", asMETHODPR(Window, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMaxWidth(int)", asMETHODPR(Window, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_maxWidth(int)", asMETHODPR(Window, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinAnchor(const Vector2&in)", asMETHODPR(Window, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_minAnchor(const Vector2&in)", asMETHODPR(Window, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinAnchor(float, float)", asMETHODPR(Window, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinHeight(int)", asMETHODPR(Window, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_minHeight(int)", asMETHODPR(Window, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinOffset(const IntVector2&in)", asMETHODPR(Window, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_minOffset(const IntVector2&in)", asMETHODPR(Window, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinSize(const IntVector2&in)", asMETHODPR(Window, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_minSize(const IntVector2&in)", asMETHODPR(Window, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinSize(int, int)", asMETHODPR(Window, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetMinWidth(int)", asMETHODPR(Window, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_minWidth(int)", asMETHODPR(Window, SetMinWidth, (int), void), asCALL_THISCALL);
    // void Window::SetModal(bool modal) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetModal(bool)", asMETHODPR(Window, SetModal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_modal(bool)", asMETHODPR(Window, SetModal, (bool), void), asCALL_THISCALL);
    // void Window::SetModalAutoDismiss(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetModalAutoDismiss(bool)", asMETHODPR(Window, SetModalAutoDismiss, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_modalAutoDismiss(bool)", asMETHODPR(Window, SetModalAutoDismiss, (bool), void), asCALL_THISCALL);
    // void Window::SetModalFrameColor(const Color& color) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetModalFrameColor(const Color&in)", asMETHODPR(Window, SetModalFrameColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_modalFrameColor(const Color&in)", asMETHODPR(Window, SetModalFrameColor, (const Color&), void), asCALL_THISCALL);
    // void Window::SetModalFrameSize(const IntVector2& size) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetModalFrameSize(const IntVector2&in)", asMETHODPR(Window, SetModalFrameSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_modalFrameSize(const IntVector2&in)", asMETHODPR(Window, SetModalFrameSize, (const IntVector2&), void), asCALL_THISCALL);
    // void Window::SetModalShadeColor(const Color& color) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetModalShadeColor(const Color&in)", asMETHODPR(Window, SetModalShadeColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_modalShadeColor(const Color&in)", asMETHODPR(Window, SetModalShadeColor, (const Color&), void), asCALL_THISCALL);
    // void Window::SetMovable(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetMovable(bool)", asMETHODPR(Window, SetMovable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_movable(bool)", asMETHODPR(Window, SetMovable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetName(const String&in)", asMETHODPR(Window, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_name(const String&in)", asMETHODPR(Window, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(Window, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(Window, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("Window", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(Window, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetOpacity(float)", asMETHODPR(Window, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_opacity(float)", asMETHODPR(Window, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(Window, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetPivot(const Vector2&in)", asMETHODPR(Window, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_pivot(const Vector2&in)", asMETHODPR(Window, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetPivot(float, float)", asMETHODPR(Window, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetPosition(const IntVector2&in)", asMETHODPR(Window, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_position(const IntVector2&in)", asMETHODPR(Window, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetPosition(int, int)", asMETHODPR(Window, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetPriority(int)", asMETHODPR(Window, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_priority(int)", asMETHODPR(Window, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetRenderTexture(Texture2D@+)", asMETHODPR(Window, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void Window::SetResizable(bool enable) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetResizable(bool)", asMETHODPR(Window, SetResizable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_resizable(bool)", asMETHODPR(Window, SetResizable, (bool), void), asCALL_THISCALL);
    // void Window::SetResizeBorder(const IntRect& rect) | File: ../UI/Window.h
    engine->RegisterObjectMethod("Window", "void SetResizeBorder(const IntRect&in)", asMETHODPR(Window, SetResizeBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_resizeBorder(const IntRect&in)", asMETHODPR(Window, SetResizeBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetSelected(bool)", asMETHODPR(Window, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_selected(bool)", asMETHODPR(Window, SetSelected, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetSize(const IntVector2&in)", asMETHODPR(Window, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_size(const IntVector2&in)", asMETHODPR(Window, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetSize(int, int)", asMETHODPR(Window, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetSortChildren(bool)", asMETHODPR(Window, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_sortChildren(bool)", asMETHODPR(Window, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(Window, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool SetStyle(const XMLElement&in)", asMETHODPR(Window, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(Window, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetTags(Array<String>@+)", asFUNCTION(Window_SetTags_StringVector), asCALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void SetTemporary(bool)", asMETHODPR(Window, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_temporary(bool)", asMETHODPR(Window, SetTemporary, (bool), void), asCALL_THISCALL);
    // void BorderImage::SetTexture(Texture* texture) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetTexture(Texture@+)", asMETHODPR(Window, SetTexture, (Texture*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_texture(Texture@+)", asMETHODPR(Window, SetTexture, (Texture*), void), asCALL_THISCALL);
    // void BorderImage::SetTextureAttr(const ResourceRef& value) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetTextureAttr(const ResourceRef&in)", asMETHODPR(Window, SetTextureAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void BorderImage::SetTiled(bool enable) | File: ../UI/BorderImage.h
    engine->RegisterObjectMethod("Window", "void SetTiled(bool)", asMETHODPR(Window, SetTiled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_tiled(bool)", asMETHODPR(Window, SetTiled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetTraversalMode(TraversalMode)", asMETHODPR(Window, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_traversalMode(TraversalMode)", asMETHODPR(Window, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetUseDerivedOpacity(bool)", asMETHODPR(Window, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_useDerivedOpacity(bool)", asMETHODPR(Window, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetVar(StringHash, const Variant&in)", asMETHODPR(Window, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(Window, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(Window, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetVisible(bool)", asMETHODPR(Window, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_visible(bool)", asMETHODPR(Window, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SetWidth(int)", asMETHODPR(Window, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "void set_width(int)", asMETHODPR(Window, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void SortChildren()", asMETHODPR(Window, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void UnsubscribeFromAllEvents()", asMETHODPR(Window, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(Window_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(Window, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(Window, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("Window", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(Window, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void Update(float)", asMETHODPR(Window, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("Window", "void UpdateLayout()", asMETHODPR(Window, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("Window", "int WeakRefs() const", asMETHODPR(Window, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Window", "int get_weakRefs() const", asMETHODPR(Window, WeakRefs, () const, int), asCALL_THISCALL);
    // explicit Window::Window(Context* context) | File: ../UI/Window.h
    engine->RegisterObjectBehaviour("Window", asBEHAVE_FACTORY, "Window@+ f()", asFUNCTION(Window_Window_Context), asCALL_CDECL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(Window, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(Window, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("Window", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(Window, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
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
    engine->RegisterObjectBehaviour("WorkQueue", asBEHAVE_ADDREF, "void f()", asMETHODPR(WorkQueue, AddRef, (), void), asCALL_THISCALL);
    // void WorkQueue::AddWorkItem(const SharedPtr<WorkItem>& item) | File: ../Core/WorkQueue.h
    // Error: type "const SharedPtr<WorkItem>&" can not automatically bind
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void WorkQueue::Complete(unsigned priority) | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "void Complete(uint)", asMETHODPR(WorkQueue, Complete, (unsigned), void), asCALL_THISCALL);
    // void WorkQueue::CreateThreads(unsigned numThreads) | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "void CreateThreads(uint)", asMETHODPR(WorkQueue, CreateThreads, (unsigned), void), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "bool GetBlockEvents() const", asMETHODPR(WorkQueue, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "const String& GetCategory() const", asMETHODPR(WorkQueue, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "const String& get_category() const", asMETHODPR(WorkQueue, GetCategory, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "VariantMap& GetEventDataMap() const", asMETHODPR(WorkQueue, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "Object@+ GetEventSender() const", asMETHODPR(WorkQueue, GetEventSender, () const, Object*), asCALL_THISCALL);
    // SharedPtr<WorkItem> WorkQueue::GetFreeItem() | File: ../Core/WorkQueue.h
    // Error: type "SharedPtr<WorkItem>" can not automatically bind
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(WorkQueue, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "const Variant& get_globalVar(StringHash) const", asMETHODPR(WorkQueue, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "const VariantMap& GetGlobalVars() const", asMETHODPR(WorkQueue, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "const VariantMap& get_globalVars() const", asMETHODPR(WorkQueue, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int WorkQueue::GetNonThreadedWorkMs() const | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "int GetNonThreadedWorkMs() const", asMETHODPR(WorkQueue, GetNonThreadedWorkMs, () const, int), asCALL_THISCALL);
    // unsigned WorkQueue::GetNumThreads() const | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "uint GetNumThreads() const", asMETHODPR(WorkQueue, GetNumThreads, () const, unsigned), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(WorkQueue, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // int WorkQueue::GetTolerance() const | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "int GetTolerance() const", asMETHODPR(WorkQueue, GetTolerance, () const, int), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "StringHash GetType() const", asMETHODPR(WorkQueue, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "StringHash get_type() const", asMETHODPR(WorkQueue, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "const String& GetTypeName() const", asMETHODPR(WorkQueue, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "const String& get_typeName() const", asMETHODPR(WorkQueue, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "bool HasEventHandlers() const", asMETHODPR(WorkQueue, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(WorkQueue, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(WorkQueue, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool WorkQueue::IsCompleted(unsigned priority) const | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "bool IsCompleted(uint) const", asMETHODPR(WorkQueue, IsCompleted, (unsigned) const, bool), asCALL_THISCALL);
    // bool WorkQueue::IsCompleting() const | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "bool IsCompleting() const", asMETHODPR(WorkQueue, IsCompleting, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "bool IsInstanceOf(StringHash) const", asMETHODPR(WorkQueue, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(WorkQueue, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // void WorkQueue::Pause() | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "void Pause()", asMETHODPR(WorkQueue, Pause, (), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("WorkQueue", "int Refs() const", asMETHODPR(WorkQueue, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "int get_refs() const", asMETHODPR(WorkQueue, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("WorkQueue", asBEHAVE_RELEASE, "void f()", asMETHODPR(WorkQueue, ReleaseRef, (), void), asCALL_THISCALL);
    // bool WorkQueue::RemoveWorkItem(SharedPtr<WorkItem> item) | File: ../Core/WorkQueue.h
    // Error: type "SharedPtr<WorkItem>" can not automatically bind
    // unsigned WorkQueue::RemoveWorkItems(const Vector<SharedPtr<WorkItem>>& items) | File: ../Core/WorkQueue.h
    // Error: type "const Vector<SharedPtr<WorkItem>>&" can not automatically bind
    // void WorkQueue::Resume() | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "void Resume()", asMETHODPR(WorkQueue, Resume, (), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void SendEvent(StringHash)", asMETHODPR(WorkQueue, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(WorkQueue, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void SetBlockEvents(bool)", asMETHODPR(WorkQueue, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(WorkQueue, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(WorkQueue, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void WorkQueue::SetNonThreadedWorkMs(int ms) | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "void SetNonThreadedWorkMs(int)", asMETHODPR(WorkQueue, SetNonThreadedWorkMs, (int), void), asCALL_THISCALL);
    // void WorkQueue::SetTolerance(int tolerance) | File: ../Core/WorkQueue.h
    engine->RegisterObjectMethod("WorkQueue", "void SetTolerance(int)", asMETHODPR(WorkQueue, SetTolerance, (int), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void UnsubscribeFromAllEvents()", asMETHODPR(WorkQueue, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(WorkQueue_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(WorkQueue, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(WorkQueue, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("WorkQueue", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(WorkQueue, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("WorkQueue", "int WeakRefs() const", asMETHODPR(WorkQueue, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("WorkQueue", "int get_weakRefs() const", asMETHODPR(WorkQueue, WeakRefs, () const, int), asCALL_THISCALL);
    // explicit WorkQueue::WorkQueue(Context* context) | File: ../Core/WorkQueue.h
    engine->RegisterObjectBehaviour("WorkQueue", asBEHAVE_FACTORY, "WorkQueue@+ f()", asFUNCTION(WorkQueue_WorkQueue_Context), asCALL_CDECL);
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
