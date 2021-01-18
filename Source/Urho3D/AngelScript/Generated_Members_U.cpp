// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

void FakeAddRef(void* ptr);
void FakeReleaseRef(void* ptr);

// SharedPtr<UIElement> UI::LoadLayout(Deserializer& source, XMLFile* styleFile=nullptr) | File: ../UI/UI.h
static UIElement* UI_LoadLayout_Deserializer_XMLFile(UI* ptr, Deserializer& source, XMLFile* styleFile)
{
    SharedPtr<UIElement> result = ptr->LoadLayout(source, styleFile);
    return result.Detach();
}

// SharedPtr<UIElement> UI::LoadLayout(XMLFile* file, XMLFile* styleFile=nullptr) | File: ../UI/UI.h
static UIElement* UI_LoadLayout_XMLFile_XMLFile(UI* ptr, XMLFile* file, XMLFile* styleFile)
{
    SharedPtr<UIElement> result = ptr->LoadLayout(file, styleFile);
    return result.Detach();
}

// explicit UI::UI(Context* context) | File: ../UI/UI.h
static UI* UI_UI_Context()
{
    return new UI(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void UI_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(UI* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// explicit UIComponent::UIComponent(Context* context) | File: ../UI/UIComponent.h
static UIComponent* UIComponent_UIComponent_Context()
{
    return new UIComponent(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void UIComponent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(UIComponent* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* UIElement_GetChildren_void(UIElement* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* UIElement_GetChildren_bool(UIElement* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* UIElement_GetChildrenWithTag_String_bool(UIElement* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* UIElement_GetTags_void(UIElement* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// explicit UIElement::UIElement(Context* context) | File: ../UI/UIElement.h
static UIElement* UIElement_UIElement_Context()
{
    return new UIElement(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void UIElement_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(UIElement* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
static CScriptArray* UISelectable_GetChildren_void(UISelectable* ptr)
{
    const Vector<SharedPtr<UIElement>>& result = ptr->GetChildren();
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
static CScriptArray* UISelectable_GetChildren_bool(UISelectable* ptr, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildren(recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
static CScriptArray* UISelectable_GetChildrenWithTag_String_bool(UISelectable* ptr, const String& tag, bool recursive)
{
    PODVector<UIElement*> result = ptr->GetChildrenWithTag(tag, recursive);
    return VectorToHandleArray(result, "Array<UIElement@>");
}

// const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
static CScriptArray* UISelectable_GetTags_void(UISelectable* ptr)
{
    const StringVector& result = ptr->GetTags();
    return VectorToArray<String>(result, "Array<String>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void UISelectable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(UISelectable* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

// const Vector<String>& UnknownComponent::GetXMLAttributes() const | File: ../Scene/UnknownComponent.h
static CScriptArray* UnknownComponent_GetXMLAttributes_void(UnknownComponent* ptr)
{
    const Vector<String>& result = ptr->GetXMLAttributes();
    return VectorToArray<String>(result, "Array<String>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void UnknownComponent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(UnknownComponent* ptr, CScriptArray* exceptions, bool onlyUserData)
{
    PODVector<StringHash> param0 = ArrayToPODVector<StringHash>(exceptions);
    ptr->UnsubscribeFromAllEventsExcept(param0, onlyUserData);
}

void ASRegisterGenerated_Members_U(asIScriptEngine* engine)
{
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UI", asBEHAVE_ADDREF, "void f()", asMETHODPR(UI, AddRef, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void UI::Clear() | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void Clear()", asMETHODPR(UI, Clear, (), void), asCALL_THISCALL);
    // IntVector2 UI::ConvertSystemToUI(const IntVector2& systemPos) const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "IntVector2 ConvertSystemToUI(const IntVector2&in) const", asMETHODPR(UI, ConvertSystemToUI, (const IntVector2&) const, IntVector2), asCALL_THISCALL);
    // IntVector2 UI::ConvertUIToSystem(const IntVector2& uiPos) const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "IntVector2 ConvertUIToSystem(const IntVector2&in) const", asMETHODPR(UI, ConvertUIToSystem, (const IntVector2&) const, IntVector2), asCALL_THISCALL);
    // void UI::DebugDraw(UIElement* element) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void DebugDraw(UIElement@+)", asMETHODPR(UI, DebugDraw, (UIElement*), void), asCALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "bool GetBlockEvents() const", asMETHODPR(UI, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "const String& GetCategory() const", asMETHODPR(UI, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const String& get_category() const", asMETHODPR(UI, GetCategory, () const, const String&), asCALL_THISCALL);
    // const String& UI::GetClipboardText() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "const String& GetClipboardText() const", asMETHODPR(UI, GetClipboardText, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const String& get_clipboardText() const", asMETHODPR(UI, GetClipboardText, () const, const String&), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // Cursor* UI::GetCursor() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "Cursor@+ GetCursor() const", asMETHODPR(UI, GetCursor, () const, Cursor*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "Cursor@+ get_cursor() const", asMETHODPR(UI, GetCursor, () const, Cursor*), asCALL_THISCALL);
    // IntVector2 UI::GetCursorPosition() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "IntVector2 GetCursorPosition() const", asMETHODPR(UI, GetCursorPosition, () const, IntVector2), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "IntVector2 get_cursorPosition() const", asMETHODPR(UI, GetCursorPosition, () const, IntVector2), asCALL_THISCALL);
    // const IntVector2& UI::GetCustomSize() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "const IntVector2& GetCustomSize() const", asMETHODPR(UI, GetCustomSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const IntVector2& get_customSize() const", asMETHODPR(UI, GetCustomSize, () const, const IntVector2&), asCALL_THISCALL);
    // float UI::GetDefaultToolTipDelay() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "float GetDefaultToolTipDelay() const", asMETHODPR(UI, GetDefaultToolTipDelay, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_defaultToolTipDelay() const", asMETHODPR(UI, GetDefaultToolTipDelay, () const, float), asCALL_THISCALL);
    // float UI::GetDoubleClickInterval() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "float GetDoubleClickInterval() const", asMETHODPR(UI, GetDoubleClickInterval, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_doubleClickInterval() const", asMETHODPR(UI, GetDoubleClickInterval, () const, float), asCALL_THISCALL);
    // int UI::GetDragBeginDistance() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "int GetDragBeginDistance() const", asMETHODPR(UI, GetDragBeginDistance, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "int get_dragBeginDistance() const", asMETHODPR(UI, GetDragBeginDistance, () const, int), asCALL_THISCALL);
    // float UI::GetDragBeginInterval() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "float GetDragBeginInterval() const", asMETHODPR(UI, GetDragBeginInterval, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_dragBeginInterval() const", asMETHODPR(UI, GetDragBeginInterval, () const, float), asCALL_THISCALL);
    // UIElement* UI::GetDragElement(unsigned index) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetDragElement(uint)", asMETHODPR(UI, GetDragElement, (unsigned), UIElement*), asCALL_THISCALL);
    // const Vector<UIElement*> UI::GetDragElements() | File: ../UI/UI.h
    // Error: type "const Vector<UIElement*>" can not automatically bind
    // UIElement* UI::GetElementAt(const IntVector2& position, bool enabledOnly=true) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetElementAt(const IntVector2&in, bool = true)", asMETHODPR(UI, GetElementAt, (const IntVector2&, bool), UIElement*), asCALL_THISCALL);
    // UIElement* UI::GetElementAt(int x, int y, bool enabledOnly=true) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetElementAt(int, int, bool = true)", asMETHODPR(UI, GetElementAt, (int, int, bool), UIElement*), asCALL_THISCALL);
    // UIElement* UI::GetElementAt(UIElement* root, const IntVector2& position, bool enabledOnly=true) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetElementAt(UIElement@+, const IntVector2&in, bool = true)", asMETHODPR(UI, GetElementAt, (UIElement*, const IntVector2&, bool), UIElement*), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "VariantMap& GetEventDataMap() const", asMETHODPR(UI, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "Object@+ GetEventSender() const", asMETHODPR(UI, GetEventSender, () const, Object*), asCALL_THISCALL);
    // UIElement* UI::GetFocusElement() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetFocusElement() const", asMETHODPR(UI, GetFocusElement, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_focusElement() const", asMETHODPR(UI, GetFocusElement, () const, UIElement*), asCALL_THISCALL);
    // FontHintLevel UI::GetFontHintLevel() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "FontHintLevel GetFontHintLevel() const", asMETHODPR(UI, GetFontHintLevel, () const, FontHintLevel), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "FontHintLevel get_fontHintLevel() const", asMETHODPR(UI, GetFontHintLevel, () const, FontHintLevel), asCALL_THISCALL);
    // int UI::GetFontOversampling() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "int GetFontOversampling() const", asMETHODPR(UI, GetFontOversampling, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "int get_fontOversampling() const", asMETHODPR(UI, GetFontOversampling, () const, int), asCALL_THISCALL);
    // float UI::GetFontSubpixelThreshold() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "float GetFontSubpixelThreshold() const", asMETHODPR(UI, GetFontSubpixelThreshold, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_fontSubpixelThreshold() const", asMETHODPR(UI, GetFontSubpixelThreshold, () const, float), asCALL_THISCALL);
    // bool UI::GetForceAutoHint() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool GetForceAutoHint() const", asMETHODPR(UI, GetForceAutoHint, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_forceAutoHint() const", asMETHODPR(UI, GetForceAutoHint, () const, bool), asCALL_THISCALL);
    // UIElement* UI::GetFrontElement() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetFrontElement() const", asMETHODPR(UI, GetFrontElement, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_frontElement() const", asMETHODPR(UI, GetFrontElement, () const, UIElement*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(UI, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const Variant& get_globalVar(StringHash) const", asMETHODPR(UI, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "const VariantMap& GetGlobalVars() const", asMETHODPR(UI, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const VariantMap& get_globalVars() const", asMETHODPR(UI, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // float UI::GetMaxDoubleClickDistance() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "float GetMaxDoubleClickDistance() const", asMETHODPR(UI, GetMaxDoubleClickDistance, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_maxDoubleClickDistance() const", asMETHODPR(UI, GetMaxDoubleClickDistance, () const, float), asCALL_THISCALL);
    // int UI::GetMaxFontTextureSize() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "int GetMaxFontTextureSize() const", asMETHODPR(UI, GetMaxFontTextureSize, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "int get_maxFontTextureSize() const", asMETHODPR(UI, GetMaxFontTextureSize, () const, int), asCALL_THISCALL);
    // unsigned UI::GetNumDragElements() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "uint GetNumDragElements() const", asMETHODPR(UI, GetNumDragElements, () const, unsigned), asCALL_THISCALL);
    // UIElement* UI::GetRoot() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetRoot() const", asMETHODPR(UI, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_root() const", asMETHODPR(UI, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // UIElement* UI::GetRootModalElement() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetRootModalElement() const", asMETHODPR(UI, GetRootModalElement, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_modalRoot() const", asMETHODPR(UI, GetRootModalElement, () const, UIElement*), asCALL_THISCALL);
    // float UI::GetScale() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "float GetScale() const", asMETHODPR(UI, GetScale, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_scale() const", asMETHODPR(UI, GetScale, () const, float), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(UI, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "StringHash GetType() const", asMETHODPR(UI, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "StringHash get_type() const", asMETHODPR(UI, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "const String& GetTypeName() const", asMETHODPR(UI, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const String& get_typeName() const", asMETHODPR(UI, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UI::GetUseMutableGlyphs() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool GetUseMutableGlyphs() const", asMETHODPR(UI, GetUseMutableGlyphs, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_useMutableGlyphs() const", asMETHODPR(UI, GetUseMutableGlyphs, () const, bool), asCALL_THISCALL);
    // bool UI::GetUseScreenKeyboard() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool GetUseScreenKeyboard() const", asMETHODPR(UI, GetUseScreenKeyboard, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_useScreenKeyboard() const", asMETHODPR(UI, GetUseScreenKeyboard, () const, bool), asCALL_THISCALL);
    // bool UI::GetUseSystemClipboard() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool GetUseSystemClipboard() const", asMETHODPR(UI, GetUseSystemClipboard, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_useSystemClipboard() const", asMETHODPR(UI, GetUseSystemClipboard, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "bool HasEventHandlers() const", asMETHODPR(UI, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UI::HasModalElement() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool HasModalElement() const", asMETHODPR(UI, HasModalElement, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(UI, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(UI, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UI::IsDragging() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool IsDragging() const", asMETHODPR(UI, IsDragging, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "bool IsInstanceOf(StringHash) const", asMETHODPR(UI, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UI::IsNonFocusedMouseWheel() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool IsNonFocusedMouseWheel() const", asMETHODPR(UI, IsNonFocusedMouseWheel, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_nonFocusedMouseWheel() const", asMETHODPR(UI, IsNonFocusedMouseWheel, () const, bool), asCALL_THISCALL);
    // SharedPtr<UIElement> UI::LoadLayout(Deserializer& source, XMLFile* styleFile=nullptr) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ LoadLayout(Deserializer&, XMLFile@+ = null)", asFUNCTION(UI_LoadLayout_Deserializer_XMLFile), asCALL_CDECL_OBJFIRST);
    // SharedPtr<UIElement> UI::LoadLayout(XMLFile* file, XMLFile* styleFile=nullptr) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ LoadLayout(XMLFile@+, XMLFile@+ = null)", asFUNCTION(UI_LoadLayout_XMLFile_XMLFile), asCALL_CDECL_OBJFIRST);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(UI, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UI", "int Refs() const", asMETHODPR(UI, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "int get_refs() const", asMETHODPR(UI, Refs, () const, int), asCALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UI", asBEHAVE_RELEASE, "void f()", asMETHODPR(UI, ReleaseRef, (), void), asCALL_THISCALL);
    // void UI::Render(bool renderUICommand=false) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void Render(bool = false)", asMETHODPR(UI, Render, (bool), void), asCALL_THISCALL);
    // void UI::RenderUpdate() | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void RenderUpdate()", asMETHODPR(UI, RenderUpdate, (), void), asCALL_THISCALL);
    // bool UI::SaveLayout(Serializer& dest, UIElement* element) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool SaveLayout(Serializer&, UIElement@+)", asMETHODPR(UI, SaveLayout, (Serializer&, UIElement*), bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void SendEvent(StringHash)", asMETHODPR(UI, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(UI, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void SetBlockEvents(bool)", asMETHODPR(UI, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void UI::SetClipboardText(const String& text) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetClipboardText(const String&in)", asMETHODPR(UI, SetClipboardText, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_clipboardText(const String&in)", asMETHODPR(UI, SetClipboardText, (const String&), void), asCALL_THISCALL);
    // void UI::SetCursor(Cursor* cursor) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetCursor(Cursor@+)", asMETHODPR(UI, SetCursor, (Cursor*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_cursor(Cursor@+)", asMETHODPR(UI, SetCursor, (Cursor*), void), asCALL_THISCALL);
    // void UI::SetCustomSize(const IntVector2& size) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetCustomSize(const IntVector2&in)", asMETHODPR(UI, SetCustomSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_customSize(const IntVector2&in)", asMETHODPR(UI, SetCustomSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UI::SetCustomSize(int width, int height) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetCustomSize(int, int)", asMETHODPR(UI, SetCustomSize, (int, int), void), asCALL_THISCALL);
    // void UI::SetDefaultToolTipDelay(float delay) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetDefaultToolTipDelay(float)", asMETHODPR(UI, SetDefaultToolTipDelay, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_defaultToolTipDelay(float)", asMETHODPR(UI, SetDefaultToolTipDelay, (float), void), asCALL_THISCALL);
    // void UI::SetDoubleClickInterval(float interval) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetDoubleClickInterval(float)", asMETHODPR(UI, SetDoubleClickInterval, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_doubleClickInterval(float)", asMETHODPR(UI, SetDoubleClickInterval, (float), void), asCALL_THISCALL);
    // void UI::SetDragBeginDistance(int pixels) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetDragBeginDistance(int)", asMETHODPR(UI, SetDragBeginDistance, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_dragBeginDistance(int)", asMETHODPR(UI, SetDragBeginDistance, (int), void), asCALL_THISCALL);
    // void UI::SetDragBeginInterval(float interval) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetDragBeginInterval(float)", asMETHODPR(UI, SetDragBeginInterval, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_dragBeginInterval(float)", asMETHODPR(UI, SetDragBeginInterval, (float), void), asCALL_THISCALL);
    // void UI::SetElementRenderTexture(UIElement* element, Texture2D* texture) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetElementRenderTexture(UIElement@+, Texture2D@+)", asMETHODPR(UI, SetElementRenderTexture, (UIElement*, Texture2D*), void), asCALL_THISCALL);
    // void UI::SetFocusElement(UIElement* element, bool byKey=false) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetFocusElement(UIElement@+, bool = false)", asMETHODPR(UI, SetFocusElement, (UIElement*, bool), void), asCALL_THISCALL);
    // void UI::SetFontHintLevel(FontHintLevel level) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetFontHintLevel(FontHintLevel)", asMETHODPR(UI, SetFontHintLevel, (FontHintLevel), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_fontHintLevel(FontHintLevel)", asMETHODPR(UI, SetFontHintLevel, (FontHintLevel), void), asCALL_THISCALL);
    // void UI::SetFontOversampling(int oversampling) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetFontOversampling(int)", asMETHODPR(UI, SetFontOversampling, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_fontOversampling(int)", asMETHODPR(UI, SetFontOversampling, (int), void), asCALL_THISCALL);
    // void UI::SetFontSubpixelThreshold(float threshold) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetFontSubpixelThreshold(float)", asMETHODPR(UI, SetFontSubpixelThreshold, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_fontSubpixelThreshold(float)", asMETHODPR(UI, SetFontSubpixelThreshold, (float), void), asCALL_THISCALL);
    // void UI::SetForceAutoHint(bool enable) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetForceAutoHint(bool)", asMETHODPR(UI, SetForceAutoHint, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_forceAutoHint(bool)", asMETHODPR(UI, SetForceAutoHint, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(UI, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(UI, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UI::SetHeight(float height) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetHeight(float)", asMETHODPR(UI, SetHeight, (float), void), asCALL_THISCALL);
    // void UI::SetMaxDoubleClickDistance(float distPixels) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetMaxDoubleClickDistance(float)", asMETHODPR(UI, SetMaxDoubleClickDistance, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_maxDoubleClickDistance(float)", asMETHODPR(UI, SetMaxDoubleClickDistance, (float), void), asCALL_THISCALL);
    // void UI::SetMaxFontTextureSize(int size) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetMaxFontTextureSize(int)", asMETHODPR(UI, SetMaxFontTextureSize, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_maxFontTextureSize(int)", asMETHODPR(UI, SetMaxFontTextureSize, (int), void), asCALL_THISCALL);
    // bool UI::SetModalElement(UIElement* modalElement, bool enable) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool SetModalElement(UIElement@+, bool)", asMETHODPR(UI, SetModalElement, (UIElement*, bool), bool), asCALL_THISCALL);
    // void UI::SetNonFocusedMouseWheel(bool nonFocusedMouseWheel) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetNonFocusedMouseWheel(bool)", asMETHODPR(UI, SetNonFocusedMouseWheel, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_nonFocusedMouseWheel(bool)", asMETHODPR(UI, SetNonFocusedMouseWheel, (bool), void), asCALL_THISCALL);
    // void UI::SetScale(float scale) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetScale(float)", asMETHODPR(UI, SetScale, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_scale(float)", asMETHODPR(UI, SetScale, (float), void), asCALL_THISCALL);
    // void UI::SetUseMutableGlyphs(bool enable) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetUseMutableGlyphs(bool)", asMETHODPR(UI, SetUseMutableGlyphs, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_useMutableGlyphs(bool)", asMETHODPR(UI, SetUseMutableGlyphs, (bool), void), asCALL_THISCALL);
    // void UI::SetUseScreenKeyboard(bool enable) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetUseScreenKeyboard(bool)", asMETHODPR(UI, SetUseScreenKeyboard, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_useScreenKeyboard(bool)", asMETHODPR(UI, SetUseScreenKeyboard, (bool), void), asCALL_THISCALL);
    // void UI::SetUseSystemClipboard(bool enable) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetUseSystemClipboard(bool)", asMETHODPR(UI, SetUseSystemClipboard, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_useSystemClipboard(bool)", asMETHODPR(UI, SetUseSystemClipboard, (bool), void), asCALL_THISCALL);
    // void UI::SetWidth(float width) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetWidth(float)", asMETHODPR(UI, SetWidth, (float), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit UI::UI(Context* context) | File: ../UI/UI.h
    engine->RegisterObjectBehaviour("UI", asBEHAVE_FACTORY, "UI@+ f()", asFUNCTION(UI_UI_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void UnsubscribeFromAllEvents()", asMETHODPR(UI, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(UI_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(UI, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(UI, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(UI, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // void UI::Update(float timeStep) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void Update(float)", asMETHODPR(UI, Update, (float), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UI", "int WeakRefs() const", asMETHODPR(UI, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UI", "int get_weakRefs() const", asMETHODPR(UI, WeakRefs, () const, int), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(UI, "UI")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(UI, "UI")
#endif
#ifdef REGISTER_MANUAL_PART_UI
    REGISTER_MANUAL_PART_UI(UI, "UI")
#endif
    RegisterSubclass<Object, UI>(engine, "Object", "UI");
    RegisterSubclass<RefCounted, UI>(engine, "RefCounted", "UI");

    // BlendMode UIBatch::blendMode_ | File: ../UI/UIBatch.h
    engine->RegisterObjectProperty("UIBatch", "BlendMode blendMode", offsetof(UIBatch, blendMode_));
    // unsigned UIBatch::color_ | File: ../UI/UIBatch.h
    engine->RegisterObjectProperty("UIBatch", "uint color", offsetof(UIBatch, color_));
    // Material* UIBatch::customMaterial_ | File: ../UI/UIBatch.h
    // Material* can not be registered
    // UIElement* UIBatch::element_ | File: ../UI/UIBatch.h
    // UIElement* can not be registered
    // Vector2 UIBatch::invTextureSize_ | File: ../UI/UIBatch.h
    engine->RegisterObjectProperty("UIBatch", "Vector2 invTextureSize", offsetof(UIBatch, invTextureSize_));
    // Vector3 UIBatch::posAdjust | File: ../UI/UIBatch.h
    engine->SetDefaultNamespace("UIBatch");
    engine->RegisterGlobalProperty("Vector3 posAdjust", (void*)&UIBatch::posAdjust);
    engine->SetDefaultNamespace("");
    // IntRect UIBatch::scissor_ | File: ../UI/UIBatch.h
    engine->RegisterObjectProperty("UIBatch", "IntRect scissor", offsetof(UIBatch, scissor_));
    // Texture* UIBatch::texture_ | File: ../UI/UIBatch.h
    // Texture* can not be registered
    // bool UIBatch::useGradient_ | File: ../UI/UIBatch.h
    engine->RegisterObjectProperty("UIBatch", "bool useGradient", offsetof(UIBatch, useGradient_));
    // PODVector<float>* UIBatch::vertexData_ | File: ../UI/UIBatch.h
    // PODVector<float>* can not be registered
    // unsigned UIBatch::vertexEnd_ | File: ../UI/UIBatch.h
    engine->RegisterObjectProperty("UIBatch", "uint vertexEnd", offsetof(UIBatch, vertexEnd_));
    // unsigned UIBatch::vertexStart_ | File: ../UI/UIBatch.h
    engine->RegisterObjectProperty("UIBatch", "uint vertexStart", offsetof(UIBatch, vertexStart_));
    // static void UIBatch::AddOrMerge(const UIBatch& batch, PODVector<UIBatch>& batches) | File: ../UI/UIBatch.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIBatch::AddQuad(float x, float y, float width, float height, int texOffsetX, int texOffsetY, int texWidth=0, int texHeight=0) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "void AddQuad(float, float, float, float, int, int, int = 0, int = 0)", asMETHODPR(UIBatch, AddQuad, (float, float, float, float, int, int, int, int), void), asCALL_THISCALL);
    // void UIBatch::AddQuad(const Matrix3x4& transform, int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth=0, int texHeight=0) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "void AddQuad(const Matrix3x4&in, int, int, int, int, int, int, int = 0, int = 0)", asMETHODPR(UIBatch, AddQuad, (const Matrix3x4&, int, int, int, int, int, int, int, int), void), asCALL_THISCALL);
    // void UIBatch::AddQuad(int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth, int texHeight, bool tiled) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "void AddQuad(int, int, int, int, int, int, int, int, bool)", asMETHODPR(UIBatch, AddQuad, (int, int, int, int, int, int, int, int, bool), void), asCALL_THISCALL);
    // void UIBatch::AddQuad(const Matrix3x4& transform, const IntVector2& a, const IntVector2& b, const IntVector2& c, const IntVector2& d, const IntVector2& texA, const IntVector2& texB, const IntVector2& texC, const IntVector2& texD) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "void AddQuad(const Matrix3x4&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in)", asMETHODPR(UIBatch, AddQuad, (const Matrix3x4&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // void UIBatch::AddQuad(const Matrix3x4& transform, const IntVector2& a, const IntVector2& b, const IntVector2& c, const IntVector2& d, const IntVector2& texA, const IntVector2& texB, const IntVector2& texC, const IntVector2& texD, const Color& colA, const Color& colB, const Color& colC, const Color& colD) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "void AddQuad(const Matrix3x4&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const Color&in, const Color&in, const Color&in, const Color&in)", asMETHODPR(UIBatch, AddQuad, (const Matrix3x4&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const Color&, const Color&, const Color&, const Color&), void), asCALL_THISCALL);
    // unsigned UIBatch::GetInterpolatedColor(float x, float y) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "uint GetInterpolatedColor(float, float)", asMETHODPR(UIBatch, GetInterpolatedColor, (float, float), unsigned), asCALL_THISCALL);
    // bool UIBatch::Merge(const UIBatch& batch) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "bool Merge(const UIBatch&in)", asMETHODPR(UIBatch, Merge, (const UIBatch&), bool), asCALL_THISCALL);
    // void UIBatch::SetColor(const Color& color, bool overrideAlpha=false) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "void SetColor(const Color&in, bool = false)", asMETHODPR(UIBatch, SetColor, (const Color&, bool), void), asCALL_THISCALL);
    // void UIBatch::SetDefaultColor() | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "void SetDefaultColor()", asMETHODPR(UIBatch, SetDefaultColor, (), void), asCALL_THISCALL);
    // UIBatch::UIBatch(UIElement* element, BlendMode blendMode, const IntRect& scissor, Texture* texture, PODVector<float>* vertexData) | File: ../UI/UIBatch.h
    // Error: type "PODVector<float>*" can not automatically bind
    // UIBatch& UIBatch::operator=(const UIBatch&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<UIBatch>(engine, "UIBatch");
#ifdef REGISTER_MANUAL_PART_UIBatch
    REGISTER_MANUAL_PART_UIBatch(UIBatch, "UIBatch")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UIComponent", asBEHAVE_ADDREF, "void f()", asMETHODPR(UIComponent, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void AllocateNetworkState()", asMETHODPR(UIComponent, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void ApplyAttributes()", asMETHODPR(UIComponent, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(UIComponent, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "bool GetAnimationEnabled() const", asMETHODPR(UIComponent, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "bool get_animationEnabled() const", asMETHODPR(UIComponent, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "Variant GetAttribute(uint) const", asMETHODPR(UIComponent, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "Variant get_attributes(uint) const", asMETHODPR(UIComponent, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "Variant GetAttribute(const String&in) const", asMETHODPR(UIComponent, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(UIComponent, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(UIComponent, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(UIComponent, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(UIComponent, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "Variant GetAttributeDefault(uint) const", asMETHODPR(UIComponent, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "Variant get_attributeDefaults(uint) const", asMETHODPR(UIComponent, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(UIComponent, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "bool GetBlockEvents() const", asMETHODPR(UIComponent, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "const String& GetCategory() const", asMETHODPR(UIComponent, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "const String& get_category() const", asMETHODPR(UIComponent, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "Component@+ GetComponent(StringHash) const", asMETHODPR(UIComponent, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("UIComponent", "VariantMap& GetEventDataMap() const", asMETHODPR(UIComponent, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "Object@+ GetEventSender() const", asMETHODPR(UIComponent, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(UIComponent, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "const Variant& get_globalVar(StringHash) const", asMETHODPR(UIComponent, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "const VariantMap& GetGlobalVars() const", asMETHODPR(UIComponent, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "const VariantMap& get_globalVars() const", asMETHODPR(UIComponent, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "uint GetID() const", asMETHODPR(UIComponent, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "uint get_id() const", asMETHODPR(UIComponent, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(UIComponent, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // Material* UIComponent::GetMaterial() const | File: ../UI/UIComponent.h
    engine->RegisterObjectMethod("UIComponent", "Material@+ GetMaterial() const", asMETHODPR(UIComponent, GetMaterial, () const, Material*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "Material@+ get_material() const", asMETHODPR(UIComponent, GetMaterial, () const, Material*), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "Node@+ GetNode() const", asMETHODPR(UIComponent, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "Node@+ get_node() const", asMETHODPR(UIComponent, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "uint GetNumAttributes() const", asMETHODPR(UIComponent, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "uint get_numAttributes() const", asMETHODPR(UIComponent, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "uint GetNumNetworkAttributes() const", asMETHODPR(UIComponent, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(UIComponent, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(UIComponent, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(UIComponent, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // UIElement* UIComponent::GetRoot() const | File: ../UI/UIComponent.h
    engine->RegisterObjectMethod("UIComponent", "UIElement@+ GetRoot() const", asMETHODPR(UIComponent, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "UIElement@+ get_root() const", asMETHODPR(UIComponent, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "Scene@+ GetScene() const", asMETHODPR(UIComponent, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(UIComponent, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Texture2D* UIComponent::GetTexture() const | File: ../UI/UIComponent.h
    engine->RegisterObjectMethod("UIComponent", "Texture2D@+ GetTexture() const", asMETHODPR(UIComponent, GetTexture, () const, Texture2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "Texture2D@+ get_texture() const", asMETHODPR(UIComponent, GetTexture, () const, Texture2D*), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "StringHash GetType() const", asMETHODPR(UIComponent, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "StringHash get_type() const", asMETHODPR(UIComponent, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "const String& GetTypeName() const", asMETHODPR(UIComponent, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "const String& get_typeName() const", asMETHODPR(UIComponent, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "bool HasEventHandlers() const", asMETHODPR(UIComponent, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(UIComponent, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(UIComponent, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "bool IsEnabled() const", asMETHODPR(UIComponent, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "bool get_enabled() const", asMETHODPR(UIComponent, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "bool IsEnabledEffective() const", asMETHODPR(UIComponent, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "bool get_enabledEffective() const", asMETHODPR(UIComponent, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "bool IsInstanceOf(StringHash) const", asMETHODPR(UIComponent, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "bool IsReplicated() const", asMETHODPR(UIComponent, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "bool get_replicated() const", asMETHODPR(UIComponent, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool IsTemporary() const", asMETHODPR(UIComponent, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "bool get_temporary() const", asMETHODPR(UIComponent, IsTemporary, () const, bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool Load(Deserializer&)", asMETHODPR(UIComponent, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "bool LoadJSON(const JSONValue&in)", asMETHODPR(UIComponent, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "bool LoadXML(const XMLElement&in)", asMETHODPR(UIComponent, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "void MarkNetworkUpdate()", asMETHODPR(UIComponent, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(UIComponent, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(UIComponent, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(UIComponent, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "void OnSetEnabled()", asMETHODPR(UIComponent, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "void PrepareNetworkUpdate()", asMETHODPR(UIComponent, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(UIComponent, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(UIComponent, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UIComponent", "int Refs() const", asMETHODPR(UIComponent, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "int get_refs() const", asMETHODPR(UIComponent, Refs, () const, int), asCALL_THISCALL);
    // static void UIComponent::RegisterObject(Context* context) | File: ../UI/UIComponent.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UIComponent", asBEHAVE_RELEASE, "void f()", asMETHODPR(UIComponent, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "void Remove()", asMETHODPR(UIComponent, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(UIComponent, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void RemoveInstanceDefault()", asMETHODPR(UIComponent, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void RemoveObjectAnimation()", asMETHODPR(UIComponent, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void ResetToDefault()", asMETHODPR(UIComponent, ResetToDefault, (), void), asCALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "bool Save(Serializer&) const", asMETHODPR(UIComponent, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool SaveDefaultAttributes() const", asMETHODPR(UIComponent, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "bool SaveJSON(JSONValue&) const", asMETHODPR(UIComponent, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "bool SaveXML(XMLElement&) const", asMETHODPR(UIComponent, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void SendEvent(StringHash)", asMETHODPR(UIComponent, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(UIComponent, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetAnimationEnabled(bool)", asMETHODPR(UIComponent, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "void set_animationEnabled(bool)", asMETHODPR(UIComponent, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetAnimationTime(float)", asMETHODPR(UIComponent, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(UIComponent, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "bool set_attributes(uint, const Variant&in)", asMETHODPR(UIComponent, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(UIComponent, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(UIComponent, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(UIComponent, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(UIComponent, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(UIComponent, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void SetBlockEvents(bool)", asMETHODPR(UIComponent, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "void SetEnabled(bool)", asMETHODPR(UIComponent, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "void set_enabled(bool)", asMETHODPR(UIComponent, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(UIComponent, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(UIComponent, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void SetInstanceDefault(bool)", asMETHODPR(UIComponent, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(UIComponent, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(UIComponent, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(UIComponent, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(UIComponent, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void SetTemporary(bool)", asMETHODPR(UIComponent, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "void set_temporary(bool)", asMETHODPR(UIComponent, SetTemporary, (bool), void), asCALL_THISCALL);
    // void UIComponent::SetViewportIndex(unsigned index) | File: ../UI/UIComponent.h
    engine->RegisterObjectMethod("UIComponent", "void SetViewportIndex(uint)", asMETHODPR(UIComponent, SetViewportIndex, (unsigned), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit UIComponent::UIComponent(Context* context) | File: ../UI/UIComponent.h
    engine->RegisterObjectBehaviour("UIComponent", asBEHAVE_FACTORY, "UIComponent@+ f()", asFUNCTION(UIComponent_UIComponent_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void UnsubscribeFromAllEvents()", asMETHODPR(UIComponent, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(UIComponent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(UIComponent, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(UIComponent, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(UIComponent, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UIComponent", "int WeakRefs() const", asMETHODPR(UIComponent, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "int get_weakRefs() const", asMETHODPR(UIComponent, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(UIComponent, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(UIComponent, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(UIComponent, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(UIComponent, "UIComponent")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(UIComponent, "UIComponent")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(UIComponent, "UIComponent")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(UIComponent, "UIComponent")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(UIComponent, "UIComponent")
#endif
#ifdef REGISTER_MANUAL_PART_UIComponent
    REGISTER_MANUAL_PART_UIComponent(UIComponent, "UIComponent")
#endif
    RegisterSubclass<Component, UIComponent>(engine, "Component", "UIComponent");
    RegisterSubclass<Animatable, UIComponent>(engine, "Animatable", "UIComponent");
    RegisterSubclass<Serializable, UIComponent>(engine, "Serializable", "UIComponent");
    RegisterSubclass<Object, UIComponent>(engine, "Object", "UIComponent");
    RegisterSubclass<RefCounted, UIComponent>(engine, "RefCounted", "UIComponent");

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void AddChild(UIElement@+)", asMETHODPR(UIElement, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UIElement", asBEHAVE_ADDREF, "void f()", asMETHODPR(UIElement, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void AddTag(const String&in)", asMETHODPR(UIElement, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void AddTags(const String&in, int8 = ';')", asMETHODPR(UIElement, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void AdjustScissor(IntRect&)", asMETHODPR(UIElement, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void AllocateNetworkState()", asMETHODPR(UIElement, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void ApplyAttributes()", asMETHODPR(UIElement, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void BringToFront()", asMETHODPR(UIElement, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(UIElement, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void DisableLayoutUpdate()", asMETHODPR(UIElement, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(UIElement, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void EnableLayoutUpdate()", asMETHODPR(UIElement, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool FilterAttributes(XMLElement&) const", asMETHODPR(UIElement, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "uint FindChild(UIElement@+) const", asMETHODPR(UIElement, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "bool GetAnimationEnabled() const", asMETHODPR(UIElement, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_animationEnabled() const", asMETHODPR(UIElement, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const String& GetAppliedStyle() const", asMETHODPR(UIElement, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const String& get_style() const", asMETHODPR(UIElement, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "Variant GetAttribute(uint) const", asMETHODPR(UIElement, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "Variant get_attributes(uint) const", asMETHODPR(UIElement, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "Variant GetAttribute(const String&in) const", asMETHODPR(UIElement, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(UIElement, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(UIElement, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(UIElement, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(UIElement, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "Variant GetAttributeDefault(uint) const", asMETHODPR(UIElement, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "Variant get_attributeDefaults(uint) const", asMETHODPR(UIElement, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(UIElement, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // virtual void UIElement::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "bool GetBlockEvents() const", asMETHODPR(UIElement, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool GetBringToBack() const", asMETHODPR(UIElement, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_bringToBack() const", asMETHODPR(UIElement, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool GetBringToFront() const", asMETHODPR(UIElement, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_bringToFront() const", asMETHODPR(UIElement, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "const String& GetCategory() const", asMETHODPR(UIElement, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const String& get_category() const", asMETHODPR(UIElement, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ GetChild(uint) const", asMETHODPR(UIElement, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "UIElement@+ get_children(uint) const", asMETHODPR(UIElement, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(UIElement, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(UIElement, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetChildOffset() const", asMETHODPR(UIElement, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_childOffset() const", asMETHODPR(UIElement, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "Array<UIElement@>@ GetChildren() const", asFUNCTION(UIElement_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(UIElement_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(UIElement_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntRect& GetClipBorder() const", asMETHODPR(UIElement, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntRect& get_clipBorder() const", asMETHODPR(UIElement, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool GetClipChildren() const", asMETHODPR(UIElement, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_clipChildren() const", asMETHODPR(UIElement, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Color& GetColor(Corner) const", asMETHODPR(UIElement, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const Color& get_colors(Corner) const", asMETHODPR(UIElement, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Color& GetColorAttr() const", asMETHODPR(UIElement, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "IntRect GetCombinedScreenRect()", asMETHODPR(UIElement, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "IntRect get_combinedScreenRect()", asMETHODPR(UIElement, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(UIElement, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Color& GetDerivedColor() const", asMETHODPR(UIElement, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "float GetDerivedOpacity() const", asMETHODPR(UIElement, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "float get_derivedOpacity() const", asMETHODPR(UIElement, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(UIElement, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(UIElement, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "uint GetDragButtonCount() const", asMETHODPR(UIElement, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "uint get_dragButtonCount() const", asMETHODPR(UIElement, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(UIElement, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(UIElement, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(UIElement, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ GetElementEventSender() const", asMETHODPR(UIElement, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool GetEnableAnchor() const", asMETHODPR(UIElement, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_enableAnchor() const", asMETHODPR(UIElement, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "VariantMap& GetEventDataMap() const", asMETHODPR(UIElement, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "Object@+ GetEventSender() const", asMETHODPR(UIElement, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "FocusMode GetFocusMode() const", asMETHODPR(UIElement, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "FocusMode get_focusMode() const", asMETHODPR(UIElement, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(UIElement, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const Variant& get_globalVar(StringHash) const", asMETHODPR(UIElement, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "const VariantMap& GetGlobalVars() const", asMETHODPR(UIElement, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const VariantMap& get_globalVars() const", asMETHODPR(UIElement, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetHeight() const", asMETHODPR(UIElement, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_height() const", asMETHODPR(UIElement, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(UIElement, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(UIElement, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetIndent() const", asMETHODPR(UIElement, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_indent() const", asMETHODPR(UIElement, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetIndentSpacing() const", asMETHODPR(UIElement, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_indentSpacing() const", asMETHODPR(UIElement, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetIndentWidth() const", asMETHODPR(UIElement, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_indentWidth() const", asMETHODPR(UIElement, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(UIElement, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntRect& GetLayoutBorder() const", asMETHODPR(UIElement, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntRect& get_layoutBorder() const", asMETHODPR(UIElement, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetLayoutElementMaxSize() const", asMETHODPR(UIElement, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(UIElement, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const Vector2& get_layoutFlexScale() const", asMETHODPR(UIElement, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "LayoutMode GetLayoutMode() const", asMETHODPR(UIElement, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "LayoutMode get_layoutMode() const", asMETHODPR(UIElement, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetLayoutSpacing() const", asMETHODPR(UIElement, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_layoutSpacing() const", asMETHODPR(UIElement, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Vector2& GetMaxAnchor() const", asMETHODPR(UIElement, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const Vector2& get_maxAnchor() const", asMETHODPR(UIElement, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetMaxHeight() const", asMETHODPR(UIElement, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_maxHeight() const", asMETHODPR(UIElement, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetMaxOffset() const", asMETHODPR(UIElement, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_maxOffset() const", asMETHODPR(UIElement, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetMaxSize() const", asMETHODPR(UIElement, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_maxSize() const", asMETHODPR(UIElement, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetMaxWidth() const", asMETHODPR(UIElement, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_maxWidth() const", asMETHODPR(UIElement, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Vector2& GetMinAnchor() const", asMETHODPR(UIElement, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const Vector2& get_minAnchor() const", asMETHODPR(UIElement, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetMinHeight() const", asMETHODPR(UIElement, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_minHeight() const", asMETHODPR(UIElement, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetMinOffset() const", asMETHODPR(UIElement, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_minOffset() const", asMETHODPR(UIElement, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetMinSize() const", asMETHODPR(UIElement, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_minSize() const", asMETHODPR(UIElement, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetMinWidth() const", asMETHODPR(UIElement, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_minWidth() const", asMETHODPR(UIElement, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const String& GetName() const", asMETHODPR(UIElement, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const String& get_name() const", asMETHODPR(UIElement, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "uint GetNumAttributes() const", asMETHODPR(UIElement, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "uint get_numAttributes() const", asMETHODPR(UIElement, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "uint GetNumChildren(bool = false) const", asMETHODPR(UIElement, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "uint get_numChildren(bool = false) const", asMETHODPR(UIElement, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "uint GetNumNetworkAttributes() const", asMETHODPR(UIElement, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(UIElement, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(UIElement, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(UIElement, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "float GetOpacity() const", asMETHODPR(UIElement, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "float get_opacity() const", asMETHODPR(UIElement, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ GetParent() const", asMETHODPR(UIElement, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "UIElement@+ get_parent() const", asMETHODPR(UIElement, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Vector2& GetPivot() const", asMETHODPR(UIElement, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const Vector2& get_pivot() const", asMETHODPR(UIElement, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetPosition() const", asMETHODPR(UIElement, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_position() const", asMETHODPR(UIElement, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetPriority() const", asMETHODPR(UIElement, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_priority() const", asMETHODPR(UIElement, GetPriority, () const, int), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ GetRoot() const", asMETHODPR(UIElement, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "UIElement@+ get_root() const", asMETHODPR(UIElement, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetScreenPosition() const", asMETHODPR(UIElement, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_screenPosition() const", asMETHODPR(UIElement, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetSize() const", asMETHODPR(UIElement, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_size() const", asMETHODPR(UIElement, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool GetSortChildren() const", asMETHODPR(UIElement, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_sortChildren() const", asMETHODPR(UIElement, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(UIElement, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "Array<String>@ GetTags() const", asFUNCTION(UIElement_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("UIElement", "Array<String>@ get_tags() const", asFUNCTION(UIElement_GetTags_void), asCALL_CDECL_OBJFIRST);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "TraversalMode GetTraversalMode() const", asMETHODPR(UIElement, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "TraversalMode get_traversalMode() const", asMETHODPR(UIElement, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "StringHash GetType() const", asMETHODPR(UIElement, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "StringHash get_type() const", asMETHODPR(UIElement, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "const String& GetTypeName() const", asMETHODPR(UIElement, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const String& get_typeName() const", asMETHODPR(UIElement, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool GetUseDerivedOpacity() const", asMETHODPR(UIElement, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_useDerivedOpacity() const", asMETHODPR(UIElement, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(UIElement, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const VariantMap& GetVars() const", asMETHODPR(UIElement, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(UIElement, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(UIElement, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetWidth() const", asMETHODPR(UIElement, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_width() const", asMETHODPR(UIElement, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool HasColorGradient() const", asMETHODPR(UIElement, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_colorGradient() const", asMETHODPR(UIElement, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "bool HasEventHandlers() const", asMETHODPR(UIElement, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool HasFocus() const", asMETHODPR(UIElement, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_focus() const", asMETHODPR(UIElement, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(UIElement, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(UIElement, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool HasTag(const String&in) const", asMETHODPR(UIElement, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void InsertChild(uint, UIElement@+)", asMETHODPR(UIElement, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsChildOf(UIElement@+) const", asMETHODPR(UIElement, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsEditable() const", asMETHODPR(UIElement, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_editable() const", asMETHODPR(UIElement, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsElementEventSender() const", asMETHODPR(UIElement, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_elementEventSender() const", asMETHODPR(UIElement, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsEnabled() const", asMETHODPR(UIElement, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_enabled() const", asMETHODPR(UIElement, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsEnabledSelf() const", asMETHODPR(UIElement, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_enabledSelf() const", asMETHODPR(UIElement, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsFixedHeight() const", asMETHODPR(UIElement, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_fixedHeight() const", asMETHODPR(UIElement, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsFixedSize() const", asMETHODPR(UIElement, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_fixedSize() const", asMETHODPR(UIElement, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsFixedWidth() const", asMETHODPR(UIElement, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_fixedWidth() const", asMETHODPR(UIElement, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsHovering() const", asMETHODPR(UIElement, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_hovering() const", asMETHODPR(UIElement, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsInside(IntVector2, bool)", asMETHODPR(UIElement, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(UIElement, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "bool IsInstanceOf(StringHash) const", asMETHODPR(UIElement, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsInternal() const", asMETHODPR(UIElement, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_internal() const", asMETHODPR(UIElement, IsInternal, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsSelected() const", asMETHODPR(UIElement, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_selected() const", asMETHODPR(UIElement, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool IsTemporary() const", asMETHODPR(UIElement, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_temporary() const", asMETHODPR(UIElement, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsVisible() const", asMETHODPR(UIElement, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_visible() const", asMETHODPR(UIElement, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsVisibleEffective() const", asMETHODPR(UIElement, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_visibleEffective() const", asMETHODPR(UIElement, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsWheelHandler() const", asMETHODPR(UIElement, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(UIElement, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool Load(Deserializer&)", asMETHODPR(UIElement, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(UIElement, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "bool LoadJSON(const JSONValue&in)", asMETHODPR(UIElement, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool LoadXML(const XMLElement&in)", asMETHODPR(UIElement, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(UIElement, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool LoadXML(Deserializer&)", asMETHODPR(UIElement, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void MarkNetworkUpdate()", asMETHODPR(UIElement, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(UIElement, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(UIElement, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(UIElement, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(UIElement, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(UIElement, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(UIElement, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool OnDragDropTest(UIElement@+)", asMETHODPR(UIElement, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(UIElement, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(UIElement, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(UIElement, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(UIElement, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(UIElement, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnIndentSet()", asMETHODPR(UIElement, OnIndentSet, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(UIElement, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnPositionSet(const IntVector2&in)", asMETHODPR(UIElement, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(UIElement, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(UIElement, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnSetEditable()", asMETHODPR(UIElement, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnTextInput(const String&in)", asMETHODPR(UIElement, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(UIElement, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(UIElement, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(UIElement, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UIElement", "int Refs() const", asMETHODPR(UIElement, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_refs() const", asMETHODPR(UIElement, Refs, () const, int), asCALL_THISCALL);
    // static void UIElement::RegisterObject(Context* context) | File: ../UI/UIElement.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UIElement", asBEHAVE_RELEASE, "void f()", asMETHODPR(UIElement, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void Remove()", asMETHODPR(UIElement, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void RemoveAllChildren()", asMETHODPR(UIElement, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void RemoveAllTags()", asMETHODPR(UIElement, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(UIElement, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(UIElement, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void RemoveChildAtIndex(uint)", asMETHODPR(UIElement, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void RemoveInstanceDefault()", asMETHODPR(UIElement, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void RemoveObjectAnimation()", asMETHODPR(UIElement, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool RemoveTag(const String&in)", asMETHODPR(UIElement, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void ResetDeepEnabled()", asMETHODPR(UIElement, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void ResetToDefault()", asMETHODPR(UIElement, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool Save(Serializer&) const", asMETHODPR(UIElement, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool SaveDefaultAttributes() const", asMETHODPR(UIElement, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "bool SaveJSON(JSONValue&) const", asMETHODPR(UIElement, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool SaveXML(XMLElement&) const", asMETHODPR(UIElement, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(UIElement, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(UIElement, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void SendEvent(StringHash)", asMETHODPR(UIElement, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(UIElement, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(UIElement, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetAnimationEnabled(bool)", asMETHODPR(UIElement, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_animationEnabled(bool)", asMETHODPR(UIElement, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetAnimationTime(float)", asMETHODPR(UIElement, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(UIElement, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool set_attributes(uint, const Variant&in)", asMETHODPR(UIElement, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(UIElement, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(UIElement, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(UIElement, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(UIElement, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(UIElement, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void SetBlockEvents(bool)", asMETHODPR(UIElement, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetBringToBack(bool)", asMETHODPR(UIElement, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_bringToBack(bool)", asMETHODPR(UIElement, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetBringToFront(bool)", asMETHODPR(UIElement, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_bringToFront(bool)", asMETHODPR(UIElement, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetChildOffset(const IntVector2&in)", asMETHODPR(UIElement, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetClipBorder(const IntRect&in)", asMETHODPR(UIElement, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_clipBorder(const IntRect&in)", asMETHODPR(UIElement, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetClipChildren(bool)", asMETHODPR(UIElement, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_clipChildren(bool)", asMETHODPR(UIElement, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetColor(const Color&in)", asMETHODPR(UIElement, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_color(const Color&in)", asMETHODPR(UIElement, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetColor(Corner, const Color&in)", asMETHODPR(UIElement, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_colors(Corner, const Color&in)", asMETHODPR(UIElement, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetDeepEnabled(bool)", asMETHODPR(UIElement, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(UIElement, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_defaultStyle(XMLFile@+)", asMETHODPR(UIElement, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(UIElement, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(UIElement, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetEditable(bool)", asMETHODPR(UIElement, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_editable(bool)", asMETHODPR(UIElement, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetElementEventSender(bool)", asMETHODPR(UIElement, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_elementEventSender(bool)", asMETHODPR(UIElement, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetEnableAnchor(bool)", asMETHODPR(UIElement, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_enableAnchor(bool)", asMETHODPR(UIElement, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetEnabled(bool)", asMETHODPR(UIElement, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_enabled(bool)", asMETHODPR(UIElement, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetEnabledRecursive(bool)", asMETHODPR(UIElement, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetFixedHeight(int)", asMETHODPR(UIElement, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetFixedSize(const IntVector2&in)", asMETHODPR(UIElement, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetFixedSize(int, int)", asMETHODPR(UIElement, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetFixedWidth(int)", asMETHODPR(UIElement, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetFocus(bool)", asMETHODPR(UIElement, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_focus(bool)", asMETHODPR(UIElement, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetFocusMode(FocusMode)", asMETHODPR(UIElement, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_focusMode(FocusMode)", asMETHODPR(UIElement, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(UIElement, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(UIElement, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetHeight(int)", asMETHODPR(UIElement, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_height(int)", asMETHODPR(UIElement, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(UIElement, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(UIElement, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetHovering(bool)", asMETHODPR(UIElement, SetHovering, (bool), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetIndent(int)", asMETHODPR(UIElement, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_indent(int)", asMETHODPR(UIElement, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetIndentSpacing(int)", asMETHODPR(UIElement, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_indentSpacing(int)", asMETHODPR(UIElement, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void SetInstanceDefault(bool)", asMETHODPR(UIElement, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(UIElement, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetInternal(bool)", asMETHODPR(UIElement, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_internal(bool)", asMETHODPR(UIElement, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(UIElement, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(UIElement, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_layoutBorder(const IntRect&in)", asMETHODPR(UIElement, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(UIElement, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(UIElement, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetLayoutMode(LayoutMode)", asMETHODPR(UIElement, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_layoutMode(LayoutMode)", asMETHODPR(UIElement, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetLayoutSpacing(int)", asMETHODPR(UIElement, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_layoutSpacing(int)", asMETHODPR(UIElement, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(UIElement, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_maxAnchor(const Vector2&in)", asMETHODPR(UIElement, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxAnchor(float, float)", asMETHODPR(UIElement, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxHeight(int)", asMETHODPR(UIElement, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_maxHeight(int)", asMETHODPR(UIElement, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(UIElement, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_maxOffset(const IntVector2&in)", asMETHODPR(UIElement, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxSize(const IntVector2&in)", asMETHODPR(UIElement, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_maxSize(const IntVector2&in)", asMETHODPR(UIElement, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxSize(int, int)", asMETHODPR(UIElement, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxWidth(int)", asMETHODPR(UIElement, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_maxWidth(int)", asMETHODPR(UIElement, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinAnchor(const Vector2&in)", asMETHODPR(UIElement, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_minAnchor(const Vector2&in)", asMETHODPR(UIElement, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinAnchor(float, float)", asMETHODPR(UIElement, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinHeight(int)", asMETHODPR(UIElement, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_minHeight(int)", asMETHODPR(UIElement, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinOffset(const IntVector2&in)", asMETHODPR(UIElement, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_minOffset(const IntVector2&in)", asMETHODPR(UIElement, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinSize(const IntVector2&in)", asMETHODPR(UIElement, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_minSize(const IntVector2&in)", asMETHODPR(UIElement, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinSize(int, int)", asMETHODPR(UIElement, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinWidth(int)", asMETHODPR(UIElement, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_minWidth(int)", asMETHODPR(UIElement, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetName(const String&in)", asMETHODPR(UIElement, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_name(const String&in)", asMETHODPR(UIElement, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(UIElement, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(UIElement, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(UIElement, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetOpacity(float)", asMETHODPR(UIElement, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_opacity(float)", asMETHODPR(UIElement, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(UIElement, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetPivot(const Vector2&in)", asMETHODPR(UIElement, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_pivot(const Vector2&in)", asMETHODPR(UIElement, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetPivot(float, float)", asMETHODPR(UIElement, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetPosition(const IntVector2&in)", asMETHODPR(UIElement, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_position(const IntVector2&in)", asMETHODPR(UIElement, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetPosition(int, int)", asMETHODPR(UIElement, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetPriority(int)", asMETHODPR(UIElement, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_priority(int)", asMETHODPR(UIElement, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetRenderTexture(Texture2D@+)", asMETHODPR(UIElement, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetSelected(bool)", asMETHODPR(UIElement, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_selected(bool)", asMETHODPR(UIElement, SetSelected, (bool), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetSize(const IntVector2&in)", asMETHODPR(UIElement, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_size(const IntVector2&in)", asMETHODPR(UIElement, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetSize(int, int)", asMETHODPR(UIElement, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetSortChildren(bool)", asMETHODPR(UIElement, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_sortChildren(bool)", asMETHODPR(UIElement, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(UIElement, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool SetStyle(const XMLElement&in)", asMETHODPR(UIElement, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(UIElement, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void SetTemporary(bool)", asMETHODPR(UIElement, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_temporary(bool)", asMETHODPR(UIElement, SetTemporary, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetTraversalMode(TraversalMode)", asMETHODPR(UIElement, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_traversalMode(TraversalMode)", asMETHODPR(UIElement, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetUseDerivedOpacity(bool)", asMETHODPR(UIElement, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_useDerivedOpacity(bool)", asMETHODPR(UIElement, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetVar(StringHash, const Variant&in)", asMETHODPR(UIElement, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(UIElement, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(UIElement, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetVisible(bool)", asMETHODPR(UIElement, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_visible(bool)", asMETHODPR(UIElement, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetWidth(int)", asMETHODPR(UIElement, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_width(int)", asMETHODPR(UIElement, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SortChildren()", asMETHODPR(UIElement, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit UIElement::UIElement(Context* context) | File: ../UI/UIElement.h
    engine->RegisterObjectBehaviour("UIElement", asBEHAVE_FACTORY, "UIElement@+ f()", asFUNCTION(UIElement_UIElement_Context), asCALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void UnsubscribeFromAllEvents()", asMETHODPR(UIElement, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(UIElement_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(UIElement, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(UIElement, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(UIElement, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void Update(float)", asMETHODPR(UIElement, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void UpdateLayout()", asMETHODPR(UIElement, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UIElement", "int WeakRefs() const", asMETHODPR(UIElement, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_weakRefs() const", asMETHODPR(UIElement, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(UIElement, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(UIElement, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(UIElement, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(UIElement, "UIElement")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(UIElement, "UIElement")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(UIElement, "UIElement")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(UIElement, "UIElement")
#endif
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(UIElement, "UIElement")
#endif
    RegisterSubclass<Animatable, UIElement>(engine, "Animatable", "UIElement");
    RegisterSubclass<Serializable, UIElement>(engine, "Serializable", "UIElement");
    RegisterSubclass<Object, UIElement>(engine, "Object", "UIElement");
    RegisterSubclass<RefCounted, UIElement>(engine, "RefCounted", "UIElement");

    // void UIElement::AddChild(UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void AddChild(UIElement@+)", asMETHODPR(UISelectable, AddChild, (UIElement*), void), asCALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UISelectable", asBEHAVE_ADDREF, "void f()", asMETHODPR(UISelectable, AddRef, (), void), asCALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void AddTag(const String&in)", asMETHODPR(UISelectable, AddTag, (const String&), void), asCALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void AddTags(const String&in, int8 = ';')", asMETHODPR(UISelectable, AddTags, (const String&, char), void), asCALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void AdjustScissor(IntRect&)", asMETHODPR(UISelectable, AdjustScissor, (IntRect&), void), asCALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void AllocateNetworkState()", asMETHODPR(UISelectable, AllocateNetworkState, (), void), asCALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void ApplyAttributes()", asMETHODPR(UISelectable, ApplyAttributes, (), void), asCALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void BringToFront()", asMETHODPR(UISelectable, BringToFront, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", asMETHODPR(UISelectable, CreateChild, (StringHash, const String&, unsigned), UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void DisableLayoutUpdate()", asMETHODPR(UISelectable, DisableLayoutUpdate, (), void), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "IntVector2 ElementToScreen(const IntVector2&in)", asMETHODPR(UISelectable, ElementToScreen, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void EnableLayoutUpdate()", asMETHODPR(UISelectable, EnableLayoutUpdate, (), void), asCALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool FilterAttributes(XMLElement&) const", asMETHODPR(UISelectable, FilterAttributes, (XMLElement&) const, bool), asCALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "uint FindChild(UIElement@+) const", asMETHODPR(UISelectable, FindChild, (UIElement*) const, unsigned), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "bool GetAnimationEnabled() const", asMETHODPR(UISelectable, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_animationEnabled() const", asMETHODPR(UISelectable, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const String& GetAppliedStyle() const", asMETHODPR(UISelectable, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const String& get_style() const", asMETHODPR(UISelectable, GetAppliedStyle, () const, const String&), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "Variant GetAttribute(uint) const", asMETHODPR(UISelectable, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "Variant get_attributes(uint) const", asMETHODPR(UISelectable, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "Variant GetAttribute(const String&in) const", asMETHODPR(UISelectable, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(UISelectable, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(UISelectable, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(UISelectable, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(UISelectable, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "Variant GetAttributeDefault(uint) const", asMETHODPR(UISelectable, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "Variant get_attributeDefaults(uint) const", asMETHODPR(UISelectable, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(UISelectable, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void UISelectable::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/UISelectable.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "bool GetBlockEvents() const", asMETHODPR(UISelectable, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool GetBringToBack() const", asMETHODPR(UISelectable, GetBringToBack, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_bringToBack() const", asMETHODPR(UISelectable, GetBringToBack, () const, bool), asCALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool GetBringToFront() const", asMETHODPR(UISelectable, GetBringToFront, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_bringToFront() const", asMETHODPR(UISelectable, GetBringToFront, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "const String& GetCategory() const", asMETHODPR(UISelectable, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const String& get_category() const", asMETHODPR(UISelectable, GetCategory, () const, const String&), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ GetChild(uint) const", asMETHODPR(UISelectable, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ get_children(uint) const", asMETHODPR(UISelectable, GetChild, (unsigned) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ GetChild(const String&in, bool = false) const", asMETHODPR(UISelectable, GetChild, (const String&, bool) const, UIElement*), asCALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", asMETHODPR(UISelectable, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), asCALL_THISCALL);
    // template<class T> T*  UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetChildOffset() const", asMETHODPR(UISelectable, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_childOffset() const", asMETHODPR(UISelectable, GetChildOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "Array<UIElement@>@ GetChildren() const", asFUNCTION(UISelectable_GetChildren_void), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "Array<UIElement@>@ GetChildren(bool) const", asFUNCTION(UISelectable_GetChildren_bool), asCALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", asFUNCTION(UISelectable_GetChildrenWithTag_String_bool), asCALL_CDECL_OBJFIRST);
    // template<class T> T*  UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T*  UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntRect& GetClipBorder() const", asMETHODPR(UISelectable, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntRect& get_clipBorder() const", asMETHODPR(UISelectable, GetClipBorder, () const, const IntRect&), asCALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool GetClipChildren() const", asMETHODPR(UISelectable, GetClipChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_clipChildren() const", asMETHODPR(UISelectable, GetClipChildren, () const, bool), asCALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Color& GetColor(Corner) const", asMETHODPR(UISelectable, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Color& get_colors(Corner) const", asMETHODPR(UISelectable, GetColor, (Corner) const, const Color&), asCALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Color& GetColorAttr() const", asMETHODPR(UISelectable, GetColorAttr, () const, const Color&), asCALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "IntRect GetCombinedScreenRect()", asMETHODPR(UISelectable, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "IntRect get_combinedScreenRect()", asMETHODPR(UISelectable, GetCombinedScreenRect, (), IntRect), asCALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can not be returned
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "XMLFile@+ GetDefaultStyle(bool = true) const", asMETHODPR(UISelectable, GetDefaultStyle, (bool) const, XMLFile*), asCALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Color& GetDerivedColor() const", asMETHODPR(UISelectable, GetDerivedColor, () const, const Color&), asCALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "float GetDerivedOpacity() const", asMETHODPR(UISelectable, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "float get_derivedOpacity() const", asMETHODPR(UISelectable, GetDerivedOpacity, () const, float), asCALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "MouseButtonFlags GetDragButtonCombo() const", asMETHODPR(UISelectable, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "MouseButtonFlags get_dragButtonCombo() const", asMETHODPR(UISelectable, GetDragButtonCombo, () const, MouseButtonFlags), asCALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "uint GetDragButtonCount() const", asMETHODPR(UISelectable, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "uint get_dragButtonCount() const", asMETHODPR(UISelectable, GetDragButtonCount, () const, unsigned), asCALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "DragAndDropModeFlags GetDragDropMode() const", asMETHODPR(UISelectable, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "DragAndDropModeFlags get_dragDropMode() const", asMETHODPR(UISelectable, GetDragDropMode, () const, DragAndDropModeFlags), asCALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "IntVector2 GetEffectiveMinSize() const", asMETHODPR(UISelectable, GetEffectiveMinSize, () const, IntVector2), asCALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ GetElementEventSender() const", asMETHODPR(UISelectable, GetElementEventSender, () const, UIElement*), asCALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool GetEnableAnchor() const", asMETHODPR(UISelectable, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_enableAnchor() const", asMETHODPR(UISelectable, GetEnableAnchor, () const, bool), asCALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "VariantMap& GetEventDataMap() const", asMETHODPR(UISelectable, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "Object@+ GetEventSender() const", asMETHODPR(UISelectable, GetEventSender, () const, Object*), asCALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "FocusMode GetFocusMode() const", asMETHODPR(UISelectable, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "FocusMode get_focusMode() const", asMETHODPR(UISelectable, GetFocusMode, () const, FocusMode), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(UISelectable, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Variant& get_globalVar(StringHash) const", asMETHODPR(UISelectable, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "const VariantMap& GetGlobalVars() const", asMETHODPR(UISelectable, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const VariantMap& get_globalVars() const", asMETHODPR(UISelectable, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetHeight() const", asMETHODPR(UISelectable, GetHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_height() const", asMETHODPR(UISelectable, GetHeight, () const, int), asCALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "HorizontalAlignment GetHorizontalAlignment() const", asMETHODPR(UISelectable, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "HorizontalAlignment get_horizontalAlignment() const", asMETHODPR(UISelectable, GetHorizontalAlignment, () const, HorizontalAlignment), asCALL_THISCALL);
    // const Color& UISelectable::GetHoverColor() const | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("UISelectable", "const Color& GetHoverColor() const", asMETHODPR(UISelectable, GetHoverColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Color& get_hoverColor() const", asMETHODPR(UISelectable, GetHoverColor, () const, const Color&), asCALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetIndent() const", asMETHODPR(UISelectable, GetIndent, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_indent() const", asMETHODPR(UISelectable, GetIndent, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetIndentSpacing() const", asMETHODPR(UISelectable, GetIndentSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_indentSpacing() const", asMETHODPR(UISelectable, GetIndentSpacing, () const, int), asCALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetIndentWidth() const", asMETHODPR(UISelectable, GetIndentWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_indentWidth() const", asMETHODPR(UISelectable, GetIndentWidth, () const, int), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(UISelectable, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntRect& GetLayoutBorder() const", asMETHODPR(UISelectable, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntRect& get_layoutBorder() const", asMETHODPR(UISelectable, GetLayoutBorder, () const, const IntRect&), asCALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetLayoutElementMaxSize() const", asMETHODPR(UISelectable, GetLayoutElementMaxSize, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Vector2& GetLayoutFlexScale() const", asMETHODPR(UISelectable, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Vector2& get_layoutFlexScale() const", asMETHODPR(UISelectable, GetLayoutFlexScale, () const, const Vector2&), asCALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "LayoutMode GetLayoutMode() const", asMETHODPR(UISelectable, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "LayoutMode get_layoutMode() const", asMETHODPR(UISelectable, GetLayoutMode, () const, LayoutMode), asCALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetLayoutSpacing() const", asMETHODPR(UISelectable, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_layoutSpacing() const", asMETHODPR(UISelectable, GetLayoutSpacing, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Vector2& GetMaxAnchor() const", asMETHODPR(UISelectable, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Vector2& get_maxAnchor() const", asMETHODPR(UISelectable, GetMaxAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetMaxHeight() const", asMETHODPR(UISelectable, GetMaxHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_maxHeight() const", asMETHODPR(UISelectable, GetMaxHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetMaxOffset() const", asMETHODPR(UISelectable, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_maxOffset() const", asMETHODPR(UISelectable, GetMaxOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetMaxSize() const", asMETHODPR(UISelectable, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_maxSize() const", asMETHODPR(UISelectable, GetMaxSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetMaxWidth() const", asMETHODPR(UISelectable, GetMaxWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_maxWidth() const", asMETHODPR(UISelectable, GetMaxWidth, () const, int), asCALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Vector2& GetMinAnchor() const", asMETHODPR(UISelectable, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Vector2& get_minAnchor() const", asMETHODPR(UISelectable, GetMinAnchor, () const, const Vector2&), asCALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetMinHeight() const", asMETHODPR(UISelectable, GetMinHeight, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_minHeight() const", asMETHODPR(UISelectable, GetMinHeight, () const, int), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetMinOffset() const", asMETHODPR(UISelectable, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_minOffset() const", asMETHODPR(UISelectable, GetMinOffset, () const, const IntVector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetMinSize() const", asMETHODPR(UISelectable, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_minSize() const", asMETHODPR(UISelectable, GetMinSize, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetMinWidth() const", asMETHODPR(UISelectable, GetMinWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_minWidth() const", asMETHODPR(UISelectable, GetMinWidth, () const, int), asCALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const String& GetName() const", asMETHODPR(UISelectable, GetName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const String& get_name() const", asMETHODPR(UISelectable, GetName, () const, const String&), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "uint GetNumAttributes() const", asMETHODPR(UISelectable, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "uint get_numAttributes() const", asMETHODPR(UISelectable, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "uint GetNumChildren(bool = false) const", asMETHODPR(UISelectable, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "uint get_numChildren(bool = false) const", asMETHODPR(UISelectable, GetNumChildren, (bool) const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "uint GetNumNetworkAttributes() const", asMETHODPR(UISelectable, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(UISelectable, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(UISelectable, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(UISelectable, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "float GetOpacity() const", asMETHODPR(UISelectable, GetOpacity, () const, float), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "float get_opacity() const", asMETHODPR(UISelectable, GetOpacity, () const, float), asCALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ GetParent() const", asMETHODPR(UISelectable, GetParent, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ get_parent() const", asMETHODPR(UISelectable, GetParent, () const, UIElement*), asCALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Vector2& GetPivot() const", asMETHODPR(UISelectable, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Vector2& get_pivot() const", asMETHODPR(UISelectable, GetPivot, () const, const Vector2&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetPosition() const", asMETHODPR(UISelectable, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_position() const", asMETHODPR(UISelectable, GetPosition, () const, const IntVector2&), asCALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetPriority() const", asMETHODPR(UISelectable, GetPriority, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_priority() const", asMETHODPR(UISelectable, GetPriority, () const, int), asCALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ GetRoot() const", asMETHODPR(UISelectable, GetRoot, () const, UIElement*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ get_root() const", asMETHODPR(UISelectable, GetRoot, () const, UIElement*), asCALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetScreenPosition() const", asMETHODPR(UISelectable, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_screenPosition() const", asMETHODPR(UISelectable, GetScreenPosition, () const, const IntVector2&), asCALL_THISCALL);
    // const Color& UISelectable::GetSelectionColor() const | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("UISelectable", "const Color& GetSelectionColor() const", asMETHODPR(UISelectable, GetSelectionColor, () const, const Color&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Color& get_selectionColor() const", asMETHODPR(UISelectable, GetSelectionColor, () const, const Color&), asCALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetSize() const", asMETHODPR(UISelectable, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_size() const", asMETHODPR(UISelectable, GetSize, () const, const IntVector2&), asCALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool GetSortChildren() const", asMETHODPR(UISelectable, GetSortChildren, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_sortChildren() const", asMETHODPR(UISelectable, GetSortChildren, () const, bool), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(UISelectable, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "Array<String>@ GetTags() const", asFUNCTION(UISelectable_GetTags_void), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("UISelectable", "Array<String>@ get_tags() const", asFUNCTION(UISelectable_GetTags_void), asCALL_CDECL_OBJFIRST);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "TraversalMode GetTraversalMode() const", asMETHODPR(UISelectable, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "TraversalMode get_traversalMode() const", asMETHODPR(UISelectable, GetTraversalMode, () const, TraversalMode), asCALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "StringHash GetType() const", asMETHODPR(UISelectable, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "StringHash get_type() const", asMETHODPR(UISelectable, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "const String& GetTypeName() const", asMETHODPR(UISelectable, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const String& get_typeName() const", asMETHODPR(UISelectable, GetTypeName, () const, const String&), asCALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool GetUseDerivedOpacity() const", asMETHODPR(UISelectable, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_useDerivedOpacity() const", asMETHODPR(UISelectable, GetUseDerivedOpacity, () const, bool), asCALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Variant& GetVar(const StringHash&in) const", asMETHODPR(UISelectable, GetVar, (const StringHash&) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const VariantMap& GetVars() const", asMETHODPR(UISelectable, GetVars, () const, const VariantMap&), asCALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "VerticalAlignment GetVerticalAlignment() const", asMETHODPR(UISelectable, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "VerticalAlignment get_verticalAlignment() const", asMETHODPR(UISelectable, GetVerticalAlignment, () const, VerticalAlignment), asCALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetWidth() const", asMETHODPR(UISelectable, GetWidth, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_width() const", asMETHODPR(UISelectable, GetWidth, () const, int), asCALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool HasColorGradient() const", asMETHODPR(UISelectable, HasColorGradient, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_colorGradient() const", asMETHODPR(UISelectable, HasColorGradient, () const, bool), asCALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "bool HasEventHandlers() const", asMETHODPR(UISelectable, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool HasFocus() const", asMETHODPR(UISelectable, HasFocus, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_focus() const", asMETHODPR(UISelectable, HasFocus, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(UISelectable, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(UISelectable, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool HasTag(const String&in) const", asMETHODPR(UISelectable, HasTag, (const String&) const, bool), asCALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void InsertChild(uint, UIElement@+)", asMETHODPR(UISelectable, InsertChild, (unsigned, UIElement*), void), asCALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsChildOf(UIElement@+) const", asMETHODPR(UISelectable, IsChildOf, (UIElement*) const, bool), asCALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsEditable() const", asMETHODPR(UISelectable, IsEditable, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_editable() const", asMETHODPR(UISelectable, IsEditable, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsElementEventSender() const", asMETHODPR(UISelectable, IsElementEventSender, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_elementEventSender() const", asMETHODPR(UISelectable, IsElementEventSender, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsEnabled() const", asMETHODPR(UISelectable, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_enabled() const", asMETHODPR(UISelectable, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsEnabledSelf() const", asMETHODPR(UISelectable, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_enabledSelf() const", asMETHODPR(UISelectable, IsEnabledSelf, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsFixedHeight() const", asMETHODPR(UISelectable, IsFixedHeight, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_fixedHeight() const", asMETHODPR(UISelectable, IsFixedHeight, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsFixedSize() const", asMETHODPR(UISelectable, IsFixedSize, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_fixedSize() const", asMETHODPR(UISelectable, IsFixedSize, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsFixedWidth() const", asMETHODPR(UISelectable, IsFixedWidth, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_fixedWidth() const", asMETHODPR(UISelectable, IsFixedWidth, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsHovering() const", asMETHODPR(UISelectable, IsHovering, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_hovering() const", asMETHODPR(UISelectable, IsHovering, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsInside(IntVector2, bool)", asMETHODPR(UISelectable, IsInside, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsInsideCombined(IntVector2, bool)", asMETHODPR(UISelectable, IsInsideCombined, (IntVector2, bool), bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "bool IsInstanceOf(StringHash) const", asMETHODPR(UISelectable, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsInternal() const", asMETHODPR(UISelectable, IsInternal, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_internal() const", asMETHODPR(UISelectable, IsInternal, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsSelected() const", asMETHODPR(UISelectable, IsSelected, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_selected() const", asMETHODPR(UISelectable, IsSelected, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool IsTemporary() const", asMETHODPR(UISelectable, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_temporary() const", asMETHODPR(UISelectable, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsVisible() const", asMETHODPR(UISelectable, IsVisible, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_visible() const", asMETHODPR(UISelectable, IsVisible, () const, bool), asCALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsVisibleEffective() const", asMETHODPR(UISelectable, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_visibleEffective() const", asMETHODPR(UISelectable, IsVisibleEffective, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsWheelHandler() const", asMETHODPR(UISelectable, IsWheelHandler, () const, bool), asCALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsWithinScissor(const IntRect&in)", asMETHODPR(UISelectable, IsWithinScissor, (const IntRect&), bool), asCALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool Load(Deserializer&)", asMETHODPR(UISelectable, Load, (Deserializer&), bool), asCALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", asMETHODPR(UISelectable, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), asCALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "bool LoadJSON(const JSONValue&in)", asMETHODPR(UISelectable, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool LoadXML(const XMLElement&in)", asMETHODPR(UISelectable, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool LoadXML(const XMLElement&in, XMLFile@+)", asMETHODPR(UISelectable, LoadXML, (const XMLElement&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool LoadXML(Deserializer&)", asMETHODPR(UISelectable, LoadXML, (Deserializer&), bool), asCALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void MarkNetworkUpdate()", asMETHODPR(UISelectable, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(UISelectable, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", asMETHODPR(UISelectable, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(UISelectable, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(UISelectable, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(UISelectable, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool OnDragDropFinish(UIElement@+)", asMETHODPR(UISelectable, OnDragDropFinish, (UIElement*), bool), asCALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool OnDragDropTest(UIElement@+)", asMETHODPR(UISelectable, OnDragDropTest, (UIElement*), bool), asCALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", asMETHODPR(UISelectable, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(UISelectable, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(UISelectable, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(UISelectable, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", asMETHODPR(UISelectable, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), asCALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnIndentSet()", asMETHODPR(UISelectable, OnIndentSet, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", asMETHODPR(UISelectable, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnPositionSet(const IntVector2&in)", asMETHODPR(UISelectable, OnPositionSet, (const IntVector2&), void), asCALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnResize(const IntVector2&in, const IntVector2&in)", asMETHODPR(UISelectable, OnResize, (const IntVector2&, const IntVector2&), void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(UISelectable, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnSetEditable()", asMETHODPR(UISelectable, OnSetEditable, (), void), asCALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnTextInput(const String&in)", asMETHODPR(UISelectable, OnTextInput, (const String&), void), asCALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", asMETHODPR(UISelectable, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(UISelectable, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(UISelectable, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UISelectable", "int Refs() const", asMETHODPR(UISelectable, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_refs() const", asMETHODPR(UISelectable, Refs, () const, int), asCALL_THISCALL);
    // static void UISelectable::RegisterObject(Context* context) | File: ../UI/UISelectable.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UISelectable", asBEHAVE_RELEASE, "void f()", asMETHODPR(UISelectable, ReleaseRef, (), void), asCALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void Remove()", asMETHODPR(UISelectable, Remove, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveAllChildren()", asMETHODPR(UISelectable, RemoveAllChildren, (), void), asCALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveAllTags()", asMETHODPR(UISelectable, RemoveAllTags, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(UISelectable, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveChild(UIElement@+, uint = 0)", asMETHODPR(UISelectable, RemoveChild, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveChildAtIndex(uint)", asMETHODPR(UISelectable, RemoveChildAtIndex, (unsigned), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveInstanceDefault()", asMETHODPR(UISelectable, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveObjectAnimation()", asMETHODPR(UISelectable, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool RemoveTag(const String&in)", asMETHODPR(UISelectable, RemoveTag, (const String&), bool), asCALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void ResetDeepEnabled()", asMETHODPR(UISelectable, ResetDeepEnabled, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void ResetToDefault()", asMETHODPR(UISelectable, ResetToDefault, (), void), asCALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool Save(Serializer&) const", asMETHODPR(UISelectable, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool SaveDefaultAttributes() const", asMETHODPR(UISelectable, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "bool SaveJSON(JSONValue&) const", asMETHODPR(UISelectable, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool SaveXML(XMLElement&) const", asMETHODPR(UISelectable, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool SaveXML(Serializer&, const String&in = \"\t\") const", asMETHODPR(UISelectable, SaveXML, (Serializer&, const String&) const, bool), asCALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "IntVector2 ScreenToElement(const IntVector2&in)", asMETHODPR(UISelectable, ScreenToElement, (const IntVector2&), IntVector2), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void SendEvent(StringHash)", asMETHODPR(UISelectable, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(UISelectable, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", asMETHODPR(UISelectable, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), asCALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetAnimationEnabled(bool)", asMETHODPR(UISelectable, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_animationEnabled(bool)", asMETHODPR(UISelectable, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetAnimationTime(float)", asMETHODPR(UISelectable, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(UISelectable, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool set_attributes(uint, const Variant&in)", asMETHODPR(UISelectable, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(UISelectable, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(UISelectable, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(UISelectable, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(UISelectable, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(UISelectable, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void SetBlockEvents(bool)", asMETHODPR(UISelectable, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetBringToBack(bool)", asMETHODPR(UISelectable, SetBringToBack, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_bringToBack(bool)", asMETHODPR(UISelectable, SetBringToBack, (bool), void), asCALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetBringToFront(bool)", asMETHODPR(UISelectable, SetBringToFront, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_bringToFront(bool)", asMETHODPR(UISelectable, SetBringToFront, (bool), void), asCALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetChildOffset(const IntVector2&in)", asMETHODPR(UISelectable, SetChildOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetClipBorder(const IntRect&in)", asMETHODPR(UISelectable, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_clipBorder(const IntRect&in)", asMETHODPR(UISelectable, SetClipBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetClipChildren(bool)", asMETHODPR(UISelectable, SetClipChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_clipChildren(bool)", asMETHODPR(UISelectable, SetClipChildren, (bool), void), asCALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetColor(const Color&in)", asMETHODPR(UISelectable, SetColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_color(const Color&in)", asMETHODPR(UISelectable, SetColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetColor(Corner, const Color&in)", asMETHODPR(UISelectable, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_colors(Corner, const Color&in)", asMETHODPR(UISelectable, SetColor, (Corner, const Color&), void), asCALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetDeepEnabled(bool)", asMETHODPR(UISelectable, SetDeepEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetDefaultStyle(XMLFile@+)", asMETHODPR(UISelectable, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_defaultStyle(XMLFile@+)", asMETHODPR(UISelectable, SetDefaultStyle, (XMLFile*), void), asCALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetDragDropMode(DragAndDropModeFlags)", asMETHODPR(UISelectable, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_dragDropMode(DragAndDropModeFlags)", asMETHODPR(UISelectable, SetDragDropMode, (DragAndDropModeFlags), void), asCALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetEditable(bool)", asMETHODPR(UISelectable, SetEditable, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_editable(bool)", asMETHODPR(UISelectable, SetEditable, (bool), void), asCALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetElementEventSender(bool)", asMETHODPR(UISelectable, SetElementEventSender, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_elementEventSender(bool)", asMETHODPR(UISelectable, SetElementEventSender, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetEnableAnchor(bool)", asMETHODPR(UISelectable, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_enableAnchor(bool)", asMETHODPR(UISelectable, SetEnableAnchor, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetEnabled(bool)", asMETHODPR(UISelectable, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_enabled(bool)", asMETHODPR(UISelectable, SetEnabled, (bool), void), asCALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetEnabledRecursive(bool)", asMETHODPR(UISelectable, SetEnabledRecursive, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetFixedHeight(int)", asMETHODPR(UISelectable, SetFixedHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetFixedSize(const IntVector2&in)", asMETHODPR(UISelectable, SetFixedSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetFixedSize(int, int)", asMETHODPR(UISelectable, SetFixedSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetFixedWidth(int)", asMETHODPR(UISelectable, SetFixedWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetFocus(bool)", asMETHODPR(UISelectable, SetFocus, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_focus(bool)", asMETHODPR(UISelectable, SetFocus, (bool), void), asCALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetFocusMode(FocusMode)", asMETHODPR(UISelectable, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_focusMode(FocusMode)", asMETHODPR(UISelectable, SetFocusMode, (FocusMode), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(UISelectable, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(UISelectable, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetHeight(int)", asMETHODPR(UISelectable, SetHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_height(int)", asMETHODPR(UISelectable, SetHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetHorizontalAlignment(HorizontalAlignment)", asMETHODPR(UISelectable, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_horizontalAlignment(HorizontalAlignment)", asMETHODPR(UISelectable, SetHorizontalAlignment, (HorizontalAlignment), void), asCALL_THISCALL);
    // void UISelectable::SetHoverColor(const Color& color) | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("UISelectable", "void SetHoverColor(const Color&in)", asMETHODPR(UISelectable, SetHoverColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_hoverColor(const Color&in)", asMETHODPR(UISelectable, SetHoverColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetHovering(bool)", asMETHODPR(UISelectable, SetHovering, (bool), void), asCALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetIndent(int)", asMETHODPR(UISelectable, SetIndent, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_indent(int)", asMETHODPR(UISelectable, SetIndent, (int), void), asCALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetIndentSpacing(int)", asMETHODPR(UISelectable, SetIndentSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_indentSpacing(int)", asMETHODPR(UISelectable, SetIndentSpacing, (int), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void SetInstanceDefault(bool)", asMETHODPR(UISelectable, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(UISelectable, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetInternal(bool)", asMETHODPR(UISelectable, SetInternal, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_internal(bool)", asMETHODPR(UISelectable, SetInternal, (bool), void), asCALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", asMETHODPR(UISelectable, SetLayout, (LayoutMode, int, const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetLayoutBorder(const IntRect&in)", asMETHODPR(UISelectable, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_layoutBorder(const IntRect&in)", asMETHODPR(UISelectable, SetLayoutBorder, (const IntRect&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetLayoutFlexScale(const Vector2&in)", asMETHODPR(UISelectable, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_layoutFlexScale(const Vector2&in)", asMETHODPR(UISelectable, SetLayoutFlexScale, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetLayoutMode(LayoutMode)", asMETHODPR(UISelectable, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_layoutMode(LayoutMode)", asMETHODPR(UISelectable, SetLayoutMode, (LayoutMode), void), asCALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetLayoutSpacing(int)", asMETHODPR(UISelectable, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_layoutSpacing(int)", asMETHODPR(UISelectable, SetLayoutSpacing, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxAnchor(const Vector2&in)", asMETHODPR(UISelectable, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_maxAnchor(const Vector2&in)", asMETHODPR(UISelectable, SetMaxAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxAnchor(float, float)", asMETHODPR(UISelectable, SetMaxAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxHeight(int)", asMETHODPR(UISelectable, SetMaxHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_maxHeight(int)", asMETHODPR(UISelectable, SetMaxHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxOffset(const IntVector2&in)", asMETHODPR(UISelectable, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_maxOffset(const IntVector2&in)", asMETHODPR(UISelectable, SetMaxOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxSize(const IntVector2&in)", asMETHODPR(UISelectable, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_maxSize(const IntVector2&in)", asMETHODPR(UISelectable, SetMaxSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxSize(int, int)", asMETHODPR(UISelectable, SetMaxSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxWidth(int)", asMETHODPR(UISelectable, SetMaxWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_maxWidth(int)", asMETHODPR(UISelectable, SetMaxWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinAnchor(const Vector2&in)", asMETHODPR(UISelectable, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_minAnchor(const Vector2&in)", asMETHODPR(UISelectable, SetMinAnchor, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinAnchor(float, float)", asMETHODPR(UISelectable, SetMinAnchor, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinHeight(int)", asMETHODPR(UISelectable, SetMinHeight, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_minHeight(int)", asMETHODPR(UISelectable, SetMinHeight, (int), void), asCALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinOffset(const IntVector2&in)", asMETHODPR(UISelectable, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_minOffset(const IntVector2&in)", asMETHODPR(UISelectable, SetMinOffset, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinSize(const IntVector2&in)", asMETHODPR(UISelectable, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_minSize(const IntVector2&in)", asMETHODPR(UISelectable, SetMinSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinSize(int, int)", asMETHODPR(UISelectable, SetMinSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinWidth(int)", asMETHODPR(UISelectable, SetMinWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_minWidth(int)", asMETHODPR(UISelectable, SetMinWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetName(const String&in)", asMETHODPR(UISelectable, SetName, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_name(const String&in)", asMETHODPR(UISelectable, SetName, (const String&), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(UISelectable, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(UISelectable, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(UISelectable, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetOpacity(float)", asMETHODPR(UISelectable, SetOpacity, (float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_opacity(float)", asMETHODPR(UISelectable, SetOpacity, (float), void), asCALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", asMETHODPR(UISelectable, SetParent, (UIElement*, unsigned), void), asCALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetPivot(const Vector2&in)", asMETHODPR(UISelectable, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_pivot(const Vector2&in)", asMETHODPR(UISelectable, SetPivot, (const Vector2&), void), asCALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetPivot(float, float)", asMETHODPR(UISelectable, SetPivot, (float, float), void), asCALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetPosition(const IntVector2&in)", asMETHODPR(UISelectable, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_position(const IntVector2&in)", asMETHODPR(UISelectable, SetPosition, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetPosition(int, int)", asMETHODPR(UISelectable, SetPosition, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetPriority(int)", asMETHODPR(UISelectable, SetPriority, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_priority(int)", asMETHODPR(UISelectable, SetPriority, (int), void), asCALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetRenderTexture(Texture2D@+)", asMETHODPR(UISelectable, SetRenderTexture, (Texture2D*), void), asCALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetSelected(bool)", asMETHODPR(UISelectable, SetSelected, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_selected(bool)", asMETHODPR(UISelectable, SetSelected, (bool), void), asCALL_THISCALL);
    // void UISelectable::SetSelectionColor(const Color& color) | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("UISelectable", "void SetSelectionColor(const Color&in)", asMETHODPR(UISelectable, SetSelectionColor, (const Color&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_selectionColor(const Color&in)", asMETHODPR(UISelectable, SetSelectionColor, (const Color&), void), asCALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetSize(const IntVector2&in)", asMETHODPR(UISelectable, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_size(const IntVector2&in)", asMETHODPR(UISelectable, SetSize, (const IntVector2&), void), asCALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetSize(int, int)", asMETHODPR(UISelectable, SetSize, (int, int), void), asCALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetSortChildren(bool)", asMETHODPR(UISelectable, SetSortChildren, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_sortChildren(bool)", asMETHODPR(UISelectable, SetSortChildren, (bool), void), asCALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool SetStyle(const String&in, XMLFile@+ = null)", asMETHODPR(UISelectable, SetStyle, (const String&, XMLFile*), bool), asCALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool SetStyle(const XMLElement&in)", asMETHODPR(UISelectable, SetStyle, (const XMLElement&), bool), asCALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool SetStyleAuto(XMLFile@+ = null)", asMETHODPR(UISelectable, SetStyleAuto, (XMLFile*), bool), asCALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    // Error: type "const StringVector&" can not automatically bind
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void SetTemporary(bool)", asMETHODPR(UISelectable, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_temporary(bool)", asMETHODPR(UISelectable, SetTemporary, (bool), void), asCALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetTraversalMode(TraversalMode)", asMETHODPR(UISelectable, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_traversalMode(TraversalMode)", asMETHODPR(UISelectable, SetTraversalMode, (TraversalMode), void), asCALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetUseDerivedOpacity(bool)", asMETHODPR(UISelectable, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_useDerivedOpacity(bool)", asMETHODPR(UISelectable, SetUseDerivedOpacity, (bool), void), asCALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetVar(StringHash, const Variant&in)", asMETHODPR(UISelectable, SetVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetVerticalAlignment(VerticalAlignment)", asMETHODPR(UISelectable, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_verticalAlignment(VerticalAlignment)", asMETHODPR(UISelectable, SetVerticalAlignment, (VerticalAlignment), void), asCALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetVisible(bool)", asMETHODPR(UISelectable, SetVisible, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_visible(bool)", asMETHODPR(UISelectable, SetVisible, (bool), void), asCALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetWidth(int)", asMETHODPR(UISelectable, SetWidth, (int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_width(int)", asMETHODPR(UISelectable, SetWidth, (int), void), asCALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SortChildren()", asMETHODPR(UISelectable, SortChildren, (), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void UnsubscribeFromAllEvents()", asMETHODPR(UISelectable, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(UISelectable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(UISelectable, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(UISelectable, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(UISelectable, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void Update(float)", asMETHODPR(UISelectable, Update, (float), void), asCALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void UpdateLayout()", asMETHODPR(UISelectable, UpdateLayout, (), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UISelectable", "int WeakRefs() const", asMETHODPR(UISelectable, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_weakRefs() const", asMETHODPR(UISelectable, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(UISelectable, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(UISelectable, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(UISelectable, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_UIElement
    REGISTER_MANUAL_PART_UIElement(UISelectable, "UISelectable")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(UISelectable, "UISelectable")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(UISelectable, "UISelectable")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(UISelectable, "UISelectable")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(UISelectable, "UISelectable")
#endif
#ifdef REGISTER_MANUAL_PART_UISelectable
    REGISTER_MANUAL_PART_UISelectable(UISelectable, "UISelectable")
#endif
    RegisterSubclass<UIElement, UISelectable>(engine, "UIElement", "UISelectable");
    RegisterSubclass<Animatable, UISelectable>(engine, "Animatable", "UISelectable");
    RegisterSubclass<Serializable, UISelectable>(engine, "Serializable", "UISelectable");
    RegisterSubclass<Object, UISelectable>(engine, "Object", "UISelectable");
    RegisterSubclass<RefCounted, UISelectable>(engine, "RefCounted", "UISelectable");

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UnknownComponent", asBEHAVE_ADDREF, "void f()", asMETHODPR(UnknownComponent, AddRef, (), void), asCALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void AllocateNetworkState()", asMETHODPR(UnknownComponent, AllocateNetworkState, (), void), asCALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void ApplyAttributes()", asMETHODPR(UnknownComponent, ApplyAttributes, (), void), asCALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "void DrawDebugGeometry(DebugRenderer@+, bool)", asMETHODPR(UnknownComponent, DrawDebugGeometry, (DebugRenderer*, bool), void), asCALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool GetAnimationEnabled() const", asMETHODPR(UnknownComponent, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "bool get_animationEnabled() const", asMETHODPR(UnknownComponent, GetAnimationEnabled, () const, bool), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "Variant GetAttribute(uint) const", asMETHODPR(UnknownComponent, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "Variant get_attributes(uint) const", asMETHODPR(UnknownComponent, GetAttribute, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "Variant GetAttribute(const String&in) const", asMETHODPR(UnknownComponent, GetAttribute, (const String&) const, Variant), asCALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", asMETHODPR(UnknownComponent, GetAttributeAnimation, (const String&) const, ValueAnimation*), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "float GetAttributeAnimationSpeed(const String&in) const", asMETHODPR(UnknownComponent, GetAttributeAnimationSpeed, (const String&) const, float), asCALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "float GetAttributeAnimationTime(const String&in) const", asMETHODPR(UnknownComponent, GetAttributeAnimationTime, (const String&) const, float), asCALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", asMETHODPR(UnknownComponent, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "Variant GetAttributeDefault(uint) const", asMETHODPR(UnknownComponent, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "Variant get_attributeDefaults(uint) const", asMETHODPR(UnknownComponent, GetAttributeDefault, (unsigned) const, Variant), asCALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "Variant GetAttributeDefault(const String&in) const", asMETHODPR(UnknownComponent, GetAttributeDefault, (const String&) const, Variant), asCALL_THISCALL);
    // const Vector<AttributeInfo>* UnknownComponent::GetAttributes() const override | File: ../Scene/UnknownComponent.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const PODVector<unsigned char>& UnknownComponent::GetBinaryAttributes() const | File: ../Scene/UnknownComponent.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "bool GetBlockEvents() const", asMETHODPR(UnknownComponent, GetBlockEvents, () const, bool), asCALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "const String& GetCategory() const", asMETHODPR(UnknownComponent, GetCategory, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "const String& get_category() const", asMETHODPR(UnknownComponent, GetCategory, () const, const String&), asCALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "Component@+ GetComponent(StringHash) const", asMETHODPR(UnknownComponent, GetComponent, (StringHash) const, Component*), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("UnknownComponent", "VariantMap& GetEventDataMap() const", asMETHODPR(UnknownComponent, GetEventDataMap, () const, VariantMap&), asCALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "Object@+ GetEventSender() const", asMETHODPR(UnknownComponent, GetEventSender, () const, Object*), asCALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "const Variant& GetGlobalVar(StringHash) const", asMETHODPR(UnknownComponent, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "const Variant& get_globalVar(StringHash) const", asMETHODPR(UnknownComponent, GetGlobalVar, (StringHash) const, const Variant&), asCALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "const VariantMap& GetGlobalVars() const", asMETHODPR(UnknownComponent, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "const VariantMap& get_globalVars() const", asMETHODPR(UnknownComponent, GetGlobalVars, () const, const VariantMap&), asCALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "uint GetID() const", asMETHODPR(UnknownComponent, GetID, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "uint get_id() const", asMETHODPR(UnknownComponent, GetID, () const, unsigned), asCALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool GetInterceptNetworkUpdate(const String&in) const", asMETHODPR(UnknownComponent, GetInterceptNetworkUpdate, (const String&) const, bool), asCALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "Node@+ GetNode() const", asMETHODPR(UnknownComponent, GetNode, () const, Node*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "Node@+ get_node() const", asMETHODPR(UnknownComponent, GetNode, () const, Node*), asCALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "uint GetNumAttributes() const", asMETHODPR(UnknownComponent, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "uint get_numAttributes() const", asMETHODPR(UnknownComponent, GetNumAttributes, () const, unsigned), asCALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "uint GetNumNetworkAttributes() const", asMETHODPR(UnknownComponent, GetNumNetworkAttributes, () const, unsigned), asCALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "ObjectAnimation@+ GetObjectAnimation() const", asMETHODPR(UnknownComponent, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "ObjectAnimation@+ get_objectAnimation() const", asMETHODPR(UnknownComponent, GetObjectAnimation, () const, ObjectAnimation*), asCALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "ResourceRef GetObjectAnimationAttr() const", asMETHODPR(UnknownComponent, GetObjectAnimationAttr, () const, ResourceRef), asCALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "Scene@+ GetScene() const", asMETHODPR(UnknownComponent, GetScene, () const, Scene*), asCALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "Object@+ GetSubsystem(StringHash) const", asMETHODPR(UnknownComponent, GetSubsystem, (StringHash) const, Object*), asCALL_THISCALL);
    // template<class T> T*  Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // StringHash UnknownComponent::GetType() const override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "StringHash GetType() const", asMETHODPR(UnknownComponent, GetType, () const, StringHash), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "StringHash get_type() const", asMETHODPR(UnknownComponent, GetType, () const, StringHash), asCALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // const String& UnknownComponent::GetTypeName() const override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "const String& GetTypeName() const", asMETHODPR(UnknownComponent, GetTypeName, () const, const String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "const String& get_typeName() const", asMETHODPR(UnknownComponent, GetTypeName, () const, const String&), asCALL_THISCALL);
    // static const Urho3D::String& UnknownComponent::GetTypeNameStatic() | File: ../Scene/UnknownComponent.h
    // Error: type "const Urho3D::String&" can not automatically bind
    // static Urho3D::StringHash UnknownComponent::GetTypeStatic() | File: ../Scene/UnknownComponent.h
    // Error: type "Urho3D::StringHash" can not automatically bind
    // bool UnknownComponent::GetUseXML() const | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool GetUseXML() const", asMETHODPR(UnknownComponent, GetUseXML, () const, bool), asCALL_THISCALL);
    // const Vector<String>& UnknownComponent::GetXMLAttributes() const | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "Array<String>@ GetXMLAttributes() const", asFUNCTION(UnknownComponent_GetXMLAttributes_void), asCALL_CDECL_OBJFIRST);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "bool HasEventHandlers() const", asMETHODPR(UnknownComponent, HasEventHandlers, () const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "bool HasSubscribedToEvent(StringHash) const", asMETHODPR(UnknownComponent, HasSubscribedToEvent, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "bool HasSubscribedToEvent(Object@+, StringHash) const", asMETHODPR(UnknownComponent, HasSubscribedToEvent, (Object*, StringHash) const, bool), asCALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "bool IsEnabled() const", asMETHODPR(UnknownComponent, IsEnabled, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "bool get_enabled() const", asMETHODPR(UnknownComponent, IsEnabled, () const, bool), asCALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "bool IsEnabledEffective() const", asMETHODPR(UnknownComponent, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "bool get_enabledEffective() const", asMETHODPR(UnknownComponent, IsEnabledEffective, () const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "bool IsInstanceOf(StringHash) const", asMETHODPR(UnknownComponent, IsInstanceOf, (StringHash) const, bool), asCALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "bool IsReplicated() const", asMETHODPR(UnknownComponent, IsReplicated, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "bool get_replicated() const", asMETHODPR(UnknownComponent, IsReplicated, () const, bool), asCALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool IsTemporary() const", asMETHODPR(UnknownComponent, IsTemporary, () const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "bool get_temporary() const", asMETHODPR(UnknownComponent, IsTemporary, () const, bool), asCALL_THISCALL);
    // bool UnknownComponent::Load(Deserializer& source) override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool Load(Deserializer&)", asMETHODPR(UnknownComponent, Load, (Deserializer&), bool), asCALL_THISCALL);
    // bool UnknownComponent::LoadJSON(const JSONValue& source) override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool LoadJSON(const JSONValue&in)", asMETHODPR(UnknownComponent, LoadJSON, (const JSONValue&), bool), asCALL_THISCALL);
    // bool UnknownComponent::LoadXML(const XMLElement& source) override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool LoadXML(const XMLElement&in)", asMETHODPR(UnknownComponent, LoadXML, (const XMLElement&), bool), asCALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "void MarkNetworkUpdate()", asMETHODPR(UnknownComponent, MarkNetworkUpdate, (), void), asCALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void OnEvent(Object@+, StringHash, VariantMap&)", asMETHODPR(UnknownComponent, OnEvent, (Object*, StringHash, VariantMap&), void), asCALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", asMETHODPR(UnknownComponent, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), asCALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", asMETHODPR(UnknownComponent, OnSetAttribute, (const AttributeInfo&, const Variant&), void), asCALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "void OnSetEnabled()", asMETHODPR(UnknownComponent, OnSetEnabled, (), void), asCALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "void PrepareNetworkUpdate()", asMETHODPR(UnknownComponent, PrepareNetworkUpdate, (), void), asCALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool ReadDeltaUpdate(Deserializer&)", asMETHODPR(UnknownComponent, ReadDeltaUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool ReadLatestDataUpdate(Deserializer&)", asMETHODPR(UnknownComponent, ReadLatestDataUpdate, (Deserializer&), bool), asCALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UnknownComponent", "int Refs() const", asMETHODPR(UnknownComponent, Refs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "int get_refs() const", asMETHODPR(UnknownComponent, Refs, () const, int), asCALL_THISCALL);
    // static void UnknownComponent::RegisterObject(Context* context) | File: ../Scene/UnknownComponent.h
    // Context can be used as firs parameter of constructors only
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UnknownComponent", asBEHAVE_RELEASE, "void f()", asMETHODPR(UnknownComponent, ReleaseRef, (), void), asCALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "void Remove()", asMETHODPR(UnknownComponent, Remove, (), void), asCALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void RemoveAttributeAnimation(const String&in)", asMETHODPR(UnknownComponent, RemoveAttributeAnimation, (const String&), void), asCALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void RemoveInstanceDefault()", asMETHODPR(UnknownComponent, RemoveInstanceDefault, (), void), asCALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void RemoveObjectAnimation()", asMETHODPR(UnknownComponent, RemoveObjectAnimation, (), void), asCALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void ResetToDefault()", asMETHODPR(UnknownComponent, ResetToDefault, (), void), asCALL_THISCALL);
    // bool UnknownComponent::Save(Serializer& dest) const override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool Save(Serializer&) const", asMETHODPR(UnknownComponent, Save, (Serializer&) const, bool), asCALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool SaveDefaultAttributes() const", asMETHODPR(UnknownComponent, SaveDefaultAttributes, () const, bool), asCALL_THISCALL);
    // bool UnknownComponent::SaveJSON(JSONValue& dest) const override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool SaveJSON(JSONValue&) const", asMETHODPR(UnknownComponent, SaveJSON, (JSONValue&) const, bool), asCALL_THISCALL);
    // bool UnknownComponent::SaveXML(XMLElement& dest) const override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool SaveXML(XMLElement&) const", asMETHODPR(UnknownComponent, SaveXML, (XMLElement&) const, bool), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void SendEvent(StringHash)", asMETHODPR(UnknownComponent, SendEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void SendEvent(StringHash, VariantMap&)", asMETHODPR(UnknownComponent, SendEvent, (StringHash, VariantMap&), void), asCALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetAnimationEnabled(bool)", asMETHODPR(UnknownComponent, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "void set_animationEnabled(bool)", asMETHODPR(UnknownComponent, SetAnimationEnabled, (bool), void), asCALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetAnimationTime(float)", asMETHODPR(UnknownComponent, SetAnimationTime, (float), void), asCALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool SetAttribute(uint, const Variant&in)", asMETHODPR(UnknownComponent, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "bool set_attributes(uint, const Variant&in)", asMETHODPR(UnknownComponent, SetAttribute, (unsigned, const Variant&), bool), asCALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool SetAttribute(const String&in, const Variant&in)", asMETHODPR(UnknownComponent, SetAttribute, (const String&, const Variant&), bool), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", asMETHODPR(UnknownComponent, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetAttributeAnimationSpeed(const String&in, float)", asMETHODPR(UnknownComponent, SetAttributeAnimationSpeed, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetAttributeAnimationTime(const String&in, float)", asMETHODPR(UnknownComponent, SetAttributeAnimationTime, (const String&, float), void), asCALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", asMETHODPR(UnknownComponent, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), asCALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetBlockEvents(bool)", asMETHODPR(UnknownComponent, SetBlockEvents, (bool), void), asCALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetEnabled(bool)", asMETHODPR(UnknownComponent, SetEnabled, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "void set_enabled(bool)", asMETHODPR(UnknownComponent, SetEnabled, (bool), void), asCALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetGlobalVar(StringHash, const Variant&in)", asMETHODPR(UnknownComponent, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "void set_globalVar(StringHash, const Variant&in)", asMETHODPR(UnknownComponent, SetGlobalVar, (StringHash, const Variant&), void), asCALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetInstanceDefault(bool)", asMETHODPR(UnknownComponent, SetInstanceDefault, (bool), void), asCALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetInterceptNetworkUpdate(const String&in, bool)", asMETHODPR(UnknownComponent, SetInterceptNetworkUpdate, (const String&, bool), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetObjectAnimation(ObjectAnimation@+)", asMETHODPR(UnknownComponent, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "void set_objectAnimation(ObjectAnimation@+)", asMETHODPR(UnknownComponent, SetObjectAnimation, (ObjectAnimation*), void), asCALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetObjectAnimationAttr(const ResourceRef&in)", asMETHODPR(UnknownComponent, SetObjectAnimationAttr, (const ResourceRef&), void), asCALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetTemporary(bool)", asMETHODPR(UnknownComponent, SetTemporary, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "void set_temporary(bool)", asMETHODPR(UnknownComponent, SetTemporary, (bool), void), asCALL_THISCALL);
    // void UnknownComponent::SetType(StringHash typeHash) | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetType(StringHash)", asMETHODPR(UnknownComponent, SetType, (StringHash), void), asCALL_THISCALL);
    // void UnknownComponent::SetTypeName(const String& typeName) | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetTypeName(const String&in)", asMETHODPR(UnknownComponent, SetTypeName, (const String&), void), asCALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void UnsubscribeFromAllEvents()", asMETHODPR(UnknownComponent, UnsubscribeFromAllEvents, (), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", asFUNCTION(UnknownComponent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), asCALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void UnsubscribeFromEvent(StringHash)", asMETHODPR(UnknownComponent, UnsubscribeFromEvent, (StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void UnsubscribeFromEvent(Object@+, StringHash)", asMETHODPR(UnknownComponent, UnsubscribeFromEvent, (Object*, StringHash), void), asCALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void UnsubscribeFromEvents(Object@+)", asMETHODPR(UnknownComponent, UnsubscribeFromEvents, (Object*), void), asCALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UnknownComponent", "int WeakRefs() const", asMETHODPR(UnknownComponent, WeakRefs, () const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "int get_weakRefs() const", asMETHODPR(UnknownComponent, WeakRefs, () const, int), asCALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", asMETHODPR(UnknownComponent, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void WriteInitialDeltaUpdate(Serializer&, uint8)", asMETHODPR(UnknownComponent, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void WriteLatestDataUpdate(Serializer&, uint8)", asMETHODPR(UnknownComponent, WriteLatestDataUpdate, (Serializer&, unsigned char), void), asCALL_THISCALL);
#ifdef REGISTER_MANUAL_PART_Component
    REGISTER_MANUAL_PART_Component(UnknownComponent, "UnknownComponent")
#endif
#ifdef REGISTER_MANUAL_PART_Animatable
    REGISTER_MANUAL_PART_Animatable(UnknownComponent, "UnknownComponent")
#endif
#ifdef REGISTER_MANUAL_PART_Serializable
    REGISTER_MANUAL_PART_Serializable(UnknownComponent, "UnknownComponent")
#endif
#ifdef REGISTER_MANUAL_PART_Object
    REGISTER_MANUAL_PART_Object(UnknownComponent, "UnknownComponent")
#endif
#ifdef REGISTER_MANUAL_PART_RefCounted
    REGISTER_MANUAL_PART_RefCounted(UnknownComponent, "UnknownComponent")
#endif
#ifdef REGISTER_MANUAL_PART_UnknownComponent
    REGISTER_MANUAL_PART_UnknownComponent(UnknownComponent, "UnknownComponent")
#endif
    RegisterSubclass<Component, UnknownComponent>(engine, "Component", "UnknownComponent");
    RegisterSubclass<Animatable, UnknownComponent>(engine, "Animatable", "UnknownComponent");
    RegisterSubclass<Serializable, UnknownComponent>(engine, "Serializable", "UnknownComponent");
    RegisterSubclass<Object, UnknownComponent>(engine, "Object", "UnknownComponent");
    RegisterSubclass<RefCounted, UnknownComponent>(engine, "RefCounted", "UnknownComponent");

}

}
