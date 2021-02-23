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
static void UI_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(UI* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// explicit UIComponent::UIComponent(Context* context) | File: ../UI/UIComponent.h
static UIComponent* UIComponent_UIComponent_Context()
{
    return new UIComponent(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void UIComponent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(UIComponent* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void UIElement_AddTags_StringVector(UIElement* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
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

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void UIElement_SetTags_StringVector(UIElement* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// explicit UIElement::UIElement(Context* context) | File: ../UI/UIElement.h
static UIElement* UIElement_UIElement_Context()
{
    return new UIElement(GetScriptContext());
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void UIElement_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(UIElement* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
static void UISelectable_AddTags_StringVector(UISelectable* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->AddTags(tags);
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

// void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
static void UISelectable_SetTags_StringVector(UISelectable* ptr, CScriptArray* tags_conv)
{
    StringVector tags = ArrayToVector<String>(tags_conv);
    ptr->SetTags(tags);
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void UISelectable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(UISelectable* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

// const Vector<String>& UnknownComponent::GetXMLAttributes() const | File: ../Scene/UnknownComponent.h
static CScriptArray* UnknownComponent_GetXMLAttributes_void(UnknownComponent* ptr)
{
    const Vector<String>& result = ptr->GetXMLAttributes();
    return VectorToArray<String>(result, "Array<String>");
}

// void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
static void UnknownComponent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool(UnknownComponent* ptr, CScriptArray* exceptions_conv, bool onlyUserData)
{
    PODVector<StringHash> exceptions = ArrayToPODVector<StringHash>(exceptions_conv);
    ptr->UnsubscribeFromAllEventsExcept(exceptions, onlyUserData);
}

void ASRegisterGenerated_Members_U(asIScriptEngine* engine)
{
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UI", asBEHAVE_ADDREF, "void f()", AS_METHODPR(UI, AddRef, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void UI::Clear() | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void Clear()", AS_METHODPR(UI, Clear, (), void), AS_CALL_THISCALL);
    // IntVector2 UI::ConvertSystemToUI(const IntVector2& systemPos) const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "IntVector2 ConvertSystemToUI(const IntVector2&in) const", AS_METHODPR(UI, ConvertSystemToUI, (const IntVector2&) const, IntVector2), AS_CALL_THISCALL);
    // IntVector2 UI::ConvertUIToSystem(const IntVector2& uiPos) const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "IntVector2 ConvertUIToSystem(const IntVector2&in) const", AS_METHODPR(UI, ConvertUIToSystem, (const IntVector2&) const, IntVector2), AS_CALL_THISCALL);
    // void UI::DebugDraw(UIElement* element) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void DebugDraw(UIElement@+)", AS_METHODPR(UI, DebugDraw, (UIElement*), void), AS_CALL_THISCALL);
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "bool GetBlockEvents() const", AS_METHODPR(UI, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "const String& GetCategory() const", AS_METHODPR(UI, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const String& get_category() const", AS_METHODPR(UI, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // const String& UI::GetClipboardText() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "const String& GetClipboardText() const", AS_METHODPR(UI, GetClipboardText, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const String& get_clipboardText() const", AS_METHODPR(UI, GetClipboardText, () const, const String&), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // Cursor* UI::GetCursor() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "Cursor@+ GetCursor() const", AS_METHODPR(UI, GetCursor, () const, Cursor*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "Cursor@+ get_cursor() const", AS_METHODPR(UI, GetCursor, () const, Cursor*), AS_CALL_THISCALL);
    // IntVector2 UI::GetCursorPosition() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "IntVector2 GetCursorPosition() const", AS_METHODPR(UI, GetCursorPosition, () const, IntVector2), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "IntVector2 get_cursorPosition() const", AS_METHODPR(UI, GetCursorPosition, () const, IntVector2), AS_CALL_THISCALL);
    // const IntVector2& UI::GetCustomSize() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "const IntVector2& GetCustomSize() const", AS_METHODPR(UI, GetCustomSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const IntVector2& get_customSize() const", AS_METHODPR(UI, GetCustomSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // float UI::GetDefaultToolTipDelay() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "float GetDefaultToolTipDelay() const", AS_METHODPR(UI, GetDefaultToolTipDelay, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_defaultToolTipDelay() const", AS_METHODPR(UI, GetDefaultToolTipDelay, () const, float), AS_CALL_THISCALL);
    // float UI::GetDoubleClickInterval() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "float GetDoubleClickInterval() const", AS_METHODPR(UI, GetDoubleClickInterval, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_doubleClickInterval() const", AS_METHODPR(UI, GetDoubleClickInterval, () const, float), AS_CALL_THISCALL);
    // int UI::GetDragBeginDistance() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "int GetDragBeginDistance() const", AS_METHODPR(UI, GetDragBeginDistance, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "int get_dragBeginDistance() const", AS_METHODPR(UI, GetDragBeginDistance, () const, int), AS_CALL_THISCALL);
    // float UI::GetDragBeginInterval() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "float GetDragBeginInterval() const", AS_METHODPR(UI, GetDragBeginInterval, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_dragBeginInterval() const", AS_METHODPR(UI, GetDragBeginInterval, () const, float), AS_CALL_THISCALL);
    // UIElement* UI::GetDragElement(unsigned index) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetDragElement(uint)", AS_METHODPR(UI, GetDragElement, (unsigned), UIElement*), AS_CALL_THISCALL);
    // const Vector<UIElement*> UI::GetDragElements() | File: ../UI/UI.h
    // Error: type "const Vector<UIElement*>" can not automatically bind
    // UIElement* UI::GetElementAt(const IntVector2& position, bool enabledOnly=true) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetElementAt(const IntVector2&in, bool = true)", AS_METHODPR(UI, GetElementAt, (const IntVector2&, bool), UIElement*), AS_CALL_THISCALL);
    // UIElement* UI::GetElementAt(int x, int y, bool enabledOnly=true) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetElementAt(int, int, bool = true)", AS_METHODPR(UI, GetElementAt, (int, int, bool), UIElement*), AS_CALL_THISCALL);
    // UIElement* UI::GetElementAt(UIElement* root, const IntVector2& position, bool enabledOnly=true) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetElementAt(UIElement@+, const IntVector2&in, bool = true)", AS_METHODPR(UI, GetElementAt, (UIElement*, const IntVector2&, bool), UIElement*), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "VariantMap& GetEventDataMap() const", AS_METHODPR(UI, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "Object@+ GetEventSender() const", AS_METHODPR(UI, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // UIElement* UI::GetFocusElement() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetFocusElement() const", AS_METHODPR(UI, GetFocusElement, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_focusElement() const", AS_METHODPR(UI, GetFocusElement, () const, UIElement*), AS_CALL_THISCALL);
    // FontHintLevel UI::GetFontHintLevel() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "FontHintLevel GetFontHintLevel() const", AS_METHODPR(UI, GetFontHintLevel, () const, FontHintLevel), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "FontHintLevel get_fontHintLevel() const", AS_METHODPR(UI, GetFontHintLevel, () const, FontHintLevel), AS_CALL_THISCALL);
    // int UI::GetFontOversampling() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "int GetFontOversampling() const", AS_METHODPR(UI, GetFontOversampling, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "int get_fontOversampling() const", AS_METHODPR(UI, GetFontOversampling, () const, int), AS_CALL_THISCALL);
    // float UI::GetFontSubpixelThreshold() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "float GetFontSubpixelThreshold() const", AS_METHODPR(UI, GetFontSubpixelThreshold, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_fontSubpixelThreshold() const", AS_METHODPR(UI, GetFontSubpixelThreshold, () const, float), AS_CALL_THISCALL);
    // bool UI::GetForceAutoHint() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool GetForceAutoHint() const", AS_METHODPR(UI, GetForceAutoHint, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_forceAutoHint() const", AS_METHODPR(UI, GetForceAutoHint, () const, bool), AS_CALL_THISCALL);
    // UIElement* UI::GetFrontElement() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetFrontElement() const", AS_METHODPR(UI, GetFrontElement, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_frontElement() const", AS_METHODPR(UI, GetFrontElement, () const, UIElement*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(UI, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(UI, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "const VariantMap& GetGlobalVars() const", AS_METHODPR(UI, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const VariantMap& get_globalVars() const", AS_METHODPR(UI, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // float UI::GetMaxDoubleClickDistance() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "float GetMaxDoubleClickDistance() const", AS_METHODPR(UI, GetMaxDoubleClickDistance, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_maxDoubleClickDistance() const", AS_METHODPR(UI, GetMaxDoubleClickDistance, () const, float), AS_CALL_THISCALL);
    // int UI::GetMaxFontTextureSize() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "int GetMaxFontTextureSize() const", AS_METHODPR(UI, GetMaxFontTextureSize, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "int get_maxFontTextureSize() const", AS_METHODPR(UI, GetMaxFontTextureSize, () const, int), AS_CALL_THISCALL);
    // unsigned UI::GetNumDragElements() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "uint GetNumDragElements() const", AS_METHODPR(UI, GetNumDragElements, () const, unsigned), AS_CALL_THISCALL);
    // UIElement* UI::GetRoot() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetRoot() const", AS_METHODPR(UI, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_root() const", AS_METHODPR(UI, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UI::GetRootModalElement() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ GetRootModalElement() const", AS_METHODPR(UI, GetRootModalElement, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "UIElement@+ get_modalRoot() const", AS_METHODPR(UI, GetRootModalElement, () const, UIElement*), AS_CALL_THISCALL);
    // float UI::GetScale() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "float GetScale() const", AS_METHODPR(UI, GetScale, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "float get_scale() const", AS_METHODPR(UI, GetScale, () const, float), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(UI, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "StringHash GetType() const", AS_METHODPR(UI, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "StringHash get_type() const", AS_METHODPR(UI, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "const String& GetTypeName() const", AS_METHODPR(UI, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "const String& get_typeName() const", AS_METHODPR(UI, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UI::GetUseMutableGlyphs() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool GetUseMutableGlyphs() const", AS_METHODPR(UI, GetUseMutableGlyphs, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_useMutableGlyphs() const", AS_METHODPR(UI, GetUseMutableGlyphs, () const, bool), AS_CALL_THISCALL);
    // bool UI::GetUseScreenKeyboard() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool GetUseScreenKeyboard() const", AS_METHODPR(UI, GetUseScreenKeyboard, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_useScreenKeyboard() const", AS_METHODPR(UI, GetUseScreenKeyboard, () const, bool), AS_CALL_THISCALL);
    // bool UI::GetUseSystemClipboard() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool GetUseSystemClipboard() const", AS_METHODPR(UI, GetUseSystemClipboard, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_useSystemClipboard() const", AS_METHODPR(UI, GetUseSystemClipboard, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "bool HasEventHandlers() const", AS_METHODPR(UI, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UI::HasModalElement() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool HasModalElement() const", AS_METHODPR(UI, HasModalElement, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(UI, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(UI, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UI::IsDragging() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool IsDragging() const", AS_METHODPR(UI, IsDragging, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "bool IsInstanceOf(StringHash) const", AS_METHODPR(UI, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UI::IsNonFocusedMouseWheel() const | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool IsNonFocusedMouseWheel() const", AS_METHODPR(UI, IsNonFocusedMouseWheel, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "bool get_nonFocusedMouseWheel() const", AS_METHODPR(UI, IsNonFocusedMouseWheel, () const, bool), AS_CALL_THISCALL);
    // SharedPtr<UIElement> UI::LoadLayout(Deserializer& source, XMLFile* styleFile=nullptr) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ LoadLayout(Deserializer&, XMLFile@+ = null)", AS_FUNCTION_OBJFIRST(UI_LoadLayout_Deserializer_XMLFile), AS_CALL_CDECL_OBJFIRST);
    // SharedPtr<UIElement> UI::LoadLayout(XMLFile* file, XMLFile* styleFile=nullptr) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "UIElement@+ LoadLayout(XMLFile@+, XMLFile@+ = null)", AS_FUNCTION_OBJFIRST(UI_LoadLayout_XMLFile_XMLFile), AS_CALL_CDECL_OBJFIRST);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(UI, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UI", "int Refs() const", AS_METHODPR(UI, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "int get_refs() const", AS_METHODPR(UI, Refs, () const, int), AS_CALL_THISCALL);
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UI", asBEHAVE_RELEASE, "void f()", AS_METHODPR(UI, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UI::Render(bool renderUICommand=false) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void Render(bool = false)", AS_METHODPR(UI, Render, (bool), void), AS_CALL_THISCALL);
    // void UI::RenderUpdate() | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void RenderUpdate()", AS_METHODPR(UI, RenderUpdate, (), void), AS_CALL_THISCALL);
    // bool UI::SaveLayout(Serializer& dest, UIElement* element) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool SaveLayout(Serializer&, UIElement@+)", AS_METHODPR(UI, SaveLayout, (Serializer&, UIElement*), bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void SendEvent(StringHash)", AS_METHODPR(UI, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(UI, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void SetBlockEvents(bool)", AS_METHODPR(UI, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void UI::SetClipboardText(const String& text) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetClipboardText(const String&in)", AS_METHODPR(UI, SetClipboardText, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_clipboardText(const String&in)", AS_METHODPR(UI, SetClipboardText, (const String&), void), AS_CALL_THISCALL);
    // void UI::SetCursor(Cursor* cursor) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetCursor(Cursor@+)", AS_METHODPR(UI, SetCursor, (Cursor*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_cursor(Cursor@+)", AS_METHODPR(UI, SetCursor, (Cursor*), void), AS_CALL_THISCALL);
    // void UI::SetCustomSize(const IntVector2& size) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetCustomSize(const IntVector2&in)", AS_METHODPR(UI, SetCustomSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_customSize(const IntVector2&in)", AS_METHODPR(UI, SetCustomSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UI::SetCustomSize(int width, int height) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetCustomSize(int, int)", AS_METHODPR(UI, SetCustomSize, (int, int), void), AS_CALL_THISCALL);
    // void UI::SetDefaultToolTipDelay(float delay) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetDefaultToolTipDelay(float)", AS_METHODPR(UI, SetDefaultToolTipDelay, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_defaultToolTipDelay(float)", AS_METHODPR(UI, SetDefaultToolTipDelay, (float), void), AS_CALL_THISCALL);
    // void UI::SetDoubleClickInterval(float interval) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetDoubleClickInterval(float)", AS_METHODPR(UI, SetDoubleClickInterval, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_doubleClickInterval(float)", AS_METHODPR(UI, SetDoubleClickInterval, (float), void), AS_CALL_THISCALL);
    // void UI::SetDragBeginDistance(int pixels) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetDragBeginDistance(int)", AS_METHODPR(UI, SetDragBeginDistance, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_dragBeginDistance(int)", AS_METHODPR(UI, SetDragBeginDistance, (int), void), AS_CALL_THISCALL);
    // void UI::SetDragBeginInterval(float interval) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetDragBeginInterval(float)", AS_METHODPR(UI, SetDragBeginInterval, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_dragBeginInterval(float)", AS_METHODPR(UI, SetDragBeginInterval, (float), void), AS_CALL_THISCALL);
    // void UI::SetElementRenderTexture(UIElement* element, Texture2D* texture) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetElementRenderTexture(UIElement@+, Texture2D@+)", AS_METHODPR(UI, SetElementRenderTexture, (UIElement*, Texture2D*), void), AS_CALL_THISCALL);
    // void UI::SetFocusElement(UIElement* element, bool byKey=false) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetFocusElement(UIElement@+, bool = false)", AS_METHODPR(UI, SetFocusElement, (UIElement*, bool), void), AS_CALL_THISCALL);
    // void UI::SetFontHintLevel(FontHintLevel level) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetFontHintLevel(FontHintLevel)", AS_METHODPR(UI, SetFontHintLevel, (FontHintLevel), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_fontHintLevel(FontHintLevel)", AS_METHODPR(UI, SetFontHintLevel, (FontHintLevel), void), AS_CALL_THISCALL);
    // void UI::SetFontOversampling(int oversampling) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetFontOversampling(int)", AS_METHODPR(UI, SetFontOversampling, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_fontOversampling(int)", AS_METHODPR(UI, SetFontOversampling, (int), void), AS_CALL_THISCALL);
    // void UI::SetFontSubpixelThreshold(float threshold) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetFontSubpixelThreshold(float)", AS_METHODPR(UI, SetFontSubpixelThreshold, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_fontSubpixelThreshold(float)", AS_METHODPR(UI, SetFontSubpixelThreshold, (float), void), AS_CALL_THISCALL);
    // void UI::SetForceAutoHint(bool enable) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetForceAutoHint(bool)", AS_METHODPR(UI, SetForceAutoHint, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_forceAutoHint(bool)", AS_METHODPR(UI, SetForceAutoHint, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(UI, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(UI, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UI::SetHeight(float height) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetHeight(float)", AS_METHODPR(UI, SetHeight, (float), void), AS_CALL_THISCALL);
    // void UI::SetMaxDoubleClickDistance(float distPixels) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetMaxDoubleClickDistance(float)", AS_METHODPR(UI, SetMaxDoubleClickDistance, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_maxDoubleClickDistance(float)", AS_METHODPR(UI, SetMaxDoubleClickDistance, (float), void), AS_CALL_THISCALL);
    // void UI::SetMaxFontTextureSize(int size) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetMaxFontTextureSize(int)", AS_METHODPR(UI, SetMaxFontTextureSize, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_maxFontTextureSize(int)", AS_METHODPR(UI, SetMaxFontTextureSize, (int), void), AS_CALL_THISCALL);
    // bool UI::SetModalElement(UIElement* modalElement, bool enable) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "bool SetModalElement(UIElement@+, bool)", AS_METHODPR(UI, SetModalElement, (UIElement*, bool), bool), AS_CALL_THISCALL);
    // void UI::SetNonFocusedMouseWheel(bool nonFocusedMouseWheel) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetNonFocusedMouseWheel(bool)", AS_METHODPR(UI, SetNonFocusedMouseWheel, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_nonFocusedMouseWheel(bool)", AS_METHODPR(UI, SetNonFocusedMouseWheel, (bool), void), AS_CALL_THISCALL);
    // void UI::SetScale(float scale) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetScale(float)", AS_METHODPR(UI, SetScale, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_scale(float)", AS_METHODPR(UI, SetScale, (float), void), AS_CALL_THISCALL);
    // void UI::SetUseMutableGlyphs(bool enable) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetUseMutableGlyphs(bool)", AS_METHODPR(UI, SetUseMutableGlyphs, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_useMutableGlyphs(bool)", AS_METHODPR(UI, SetUseMutableGlyphs, (bool), void), AS_CALL_THISCALL);
    // void UI::SetUseScreenKeyboard(bool enable) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetUseScreenKeyboard(bool)", AS_METHODPR(UI, SetUseScreenKeyboard, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_useScreenKeyboard(bool)", AS_METHODPR(UI, SetUseScreenKeyboard, (bool), void), AS_CALL_THISCALL);
    // void UI::SetUseSystemClipboard(bool enable) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetUseSystemClipboard(bool)", AS_METHODPR(UI, SetUseSystemClipboard, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "void set_useSystemClipboard(bool)", AS_METHODPR(UI, SetUseSystemClipboard, (bool), void), AS_CALL_THISCALL);
    // void UI::SetWidth(float width) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void SetWidth(float)", AS_METHODPR(UI, SetWidth, (float), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit UI::UI(Context* context) | File: ../UI/UI.h
    engine->RegisterObjectBehaviour("UI", asBEHAVE_FACTORY, "UI@+ f()", AS_FUNCTION(UI_UI_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void UnsubscribeFromAllEvents()", AS_METHODPR(UI, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(UI_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(UI, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(UI, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UI", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(UI, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // void UI::Update(float timeStep) | File: ../UI/UI.h
    engine->RegisterObjectMethod("UI", "void Update(float)", AS_METHODPR(UI, Update, (float), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UI", "int WeakRefs() const", AS_METHODPR(UI, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UI", "int get_weakRefs() const", AS_METHODPR(UI, WeakRefs, () const, int), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("UIBatch", "void AddQuad(float, float, float, float, int, int, int = 0, int = 0)", AS_METHODPR(UIBatch, AddQuad, (float, float, float, float, int, int, int, int), void), AS_CALL_THISCALL);
    // void UIBatch::AddQuad(const Matrix3x4& transform, int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth=0, int texHeight=0) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "void AddQuad(const Matrix3x4&in, int, int, int, int, int, int, int = 0, int = 0)", AS_METHODPR(UIBatch, AddQuad, (const Matrix3x4&, int, int, int, int, int, int, int, int), void), AS_CALL_THISCALL);
    // void UIBatch::AddQuad(int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth, int texHeight, bool tiled) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "void AddQuad(int, int, int, int, int, int, int, int, bool)", AS_METHODPR(UIBatch, AddQuad, (int, int, int, int, int, int, int, int, bool), void), AS_CALL_THISCALL);
    // void UIBatch::AddQuad(const Matrix3x4& transform, const IntVector2& a, const IntVector2& b, const IntVector2& c, const IntVector2& d, const IntVector2& texA, const IntVector2& texB, const IntVector2& texC, const IntVector2& texD) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "void AddQuad(const Matrix3x4&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in)", AS_METHODPR(UIBatch, AddQuad, (const Matrix3x4&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // void UIBatch::AddQuad(const Matrix3x4& transform, const IntVector2& a, const IntVector2& b, const IntVector2& c, const IntVector2& d, const IntVector2& texA, const IntVector2& texB, const IntVector2& texC, const IntVector2& texD, const Color& colA, const Color& colB, const Color& colC, const Color& colD) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "void AddQuad(const Matrix3x4&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const IntVector2&in, const Color&in, const Color&in, const Color&in, const Color&in)", AS_METHODPR(UIBatch, AddQuad, (const Matrix3x4&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const IntVector2&, const Color&, const Color&, const Color&, const Color&), void), AS_CALL_THISCALL);
    // unsigned UIBatch::GetInterpolatedColor(float x, float y) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "uint GetInterpolatedColor(float, float)", AS_METHODPR(UIBatch, GetInterpolatedColor, (float, float), unsigned), AS_CALL_THISCALL);
    // bool UIBatch::Merge(const UIBatch& batch) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "bool Merge(const UIBatch&in)", AS_METHODPR(UIBatch, Merge, (const UIBatch&), bool), AS_CALL_THISCALL);
    // void UIBatch::SetColor(const Color& color, bool overrideAlpha=false) | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "void SetColor(const Color&in, bool = false)", AS_METHODPR(UIBatch, SetColor, (const Color&, bool), void), AS_CALL_THISCALL);
    // void UIBatch::SetDefaultColor() | File: ../UI/UIBatch.h
    engine->RegisterObjectMethod("UIBatch", "void SetDefaultColor()", AS_METHODPR(UIBatch, SetDefaultColor, (), void), AS_CALL_THISCALL);
    // UIBatch::UIBatch(UIElement* element, BlendMode blendMode, const IntRect& scissor, Texture* texture, PODVector<float>* vertexData) | File: ../UI/UIBatch.h
    // Error: type "PODVector<float>*" can not automatically bind
    // UIBatch& UIBatch::operator=(const UIBatch&) | Possible implicitly-declared
    RegisterImplicitlyDeclaredAssignOperatorIfPossible<UIBatch>(engine, "UIBatch");
#ifdef REGISTER_MANUAL_PART_UIBatch
    REGISTER_MANUAL_PART_UIBatch(UIBatch, "UIBatch")
#endif

    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UIComponent", asBEHAVE_ADDREF, "void f()", AS_METHODPR(UIComponent, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void AllocateNetworkState()", AS_METHODPR(UIComponent, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void ApplyAttributes()", AS_METHODPR(UIComponent, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(UIComponent, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "bool GetAnimationEnabled() const", AS_METHODPR(UIComponent, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "bool get_animationEnabled() const", AS_METHODPR(UIComponent, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "Variant GetAttribute(uint) const", AS_METHODPR(UIComponent, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "Variant get_attributes(uint) const", AS_METHODPR(UIComponent, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "Variant GetAttribute(const String&in) const", AS_METHODPR(UIComponent, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(UIComponent, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(UIComponent, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(UIComponent, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(UIComponent, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "Variant GetAttributeDefault(uint) const", AS_METHODPR(UIComponent, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "Variant get_attributeDefaults(uint) const", AS_METHODPR(UIComponent, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(UIComponent, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "bool GetBlockEvents() const", AS_METHODPR(UIComponent, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "const String& GetCategory() const", AS_METHODPR(UIComponent, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "const String& get_category() const", AS_METHODPR(UIComponent, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "Component@+ GetComponent(StringHash) const", AS_METHODPR(UIComponent, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("UIComponent", "VariantMap& GetEventDataMap() const", AS_METHODPR(UIComponent, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "Object@+ GetEventSender() const", AS_METHODPR(UIComponent, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(UIComponent, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(UIComponent, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "const VariantMap& GetGlobalVars() const", AS_METHODPR(UIComponent, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "const VariantMap& get_globalVars() const", AS_METHODPR(UIComponent, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "uint GetID() const", AS_METHODPR(UIComponent, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "uint get_id() const", AS_METHODPR(UIComponent, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(UIComponent, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // Material* UIComponent::GetMaterial() const | File: ../UI/UIComponent.h
    engine->RegisterObjectMethod("UIComponent", "Material@+ GetMaterial() const", AS_METHODPR(UIComponent, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "Material@+ get_material() const", AS_METHODPR(UIComponent, GetMaterial, () const, Material*), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "Node@+ GetNode() const", AS_METHODPR(UIComponent, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "Node@+ get_node() const", AS_METHODPR(UIComponent, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "uint GetNumAttributes() const", AS_METHODPR(UIComponent, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "uint get_numAttributes() const", AS_METHODPR(UIComponent, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "uint GetNumNetworkAttributes() const", AS_METHODPR(UIComponent, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(UIComponent, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(UIComponent, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(UIComponent, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // UIElement* UIComponent::GetRoot() const | File: ../UI/UIComponent.h
    engine->RegisterObjectMethod("UIComponent", "UIElement@+ GetRoot() const", AS_METHODPR(UIComponent, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "UIElement@+ get_root() const", AS_METHODPR(UIComponent, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "Scene@+ GetScene() const", AS_METHODPR(UIComponent, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(UIComponent, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // Texture2D* UIComponent::GetTexture() const | File: ../UI/UIComponent.h
    engine->RegisterObjectMethod("UIComponent", "Texture2D@+ GetTexture() const", AS_METHODPR(UIComponent, GetTexture, () const, Texture2D*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "Texture2D@+ get_texture() const", AS_METHODPR(UIComponent, GetTexture, () const, Texture2D*), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "StringHash GetType() const", AS_METHODPR(UIComponent, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "StringHash get_type() const", AS_METHODPR(UIComponent, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "const String& GetTypeName() const", AS_METHODPR(UIComponent, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "const String& get_typeName() const", AS_METHODPR(UIComponent, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "bool HasEventHandlers() const", AS_METHODPR(UIComponent, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(UIComponent, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(UIComponent, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "bool IsEnabled() const", AS_METHODPR(UIComponent, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "bool get_enabled() const", AS_METHODPR(UIComponent, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "bool IsEnabledEffective() const", AS_METHODPR(UIComponent, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "bool get_enabledEffective() const", AS_METHODPR(UIComponent, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "bool IsInstanceOf(StringHash) const", AS_METHODPR(UIComponent, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "bool IsReplicated() const", AS_METHODPR(UIComponent, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "bool get_replicated() const", AS_METHODPR(UIComponent, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool IsTemporary() const", AS_METHODPR(UIComponent, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "bool get_temporary() const", AS_METHODPR(UIComponent, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool Load(Deserializer&)", AS_METHODPR(UIComponent, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(UIComponent, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool Animatable::LoadXML(const XMLElement& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "bool LoadXML(const XMLElement&in)", AS_METHODPR(UIComponent, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "void MarkNetworkUpdate()", AS_METHODPR(UIComponent, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(UIComponent, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(UIComponent, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(UIComponent, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "void OnSetEnabled()", AS_METHODPR(UIComponent, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "void PrepareNetworkUpdate()", AS_METHODPR(UIComponent, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(UIComponent, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(UIComponent, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UIComponent", "int Refs() const", AS_METHODPR(UIComponent, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "int get_refs() const", AS_METHODPR(UIComponent, Refs, () const, int), AS_CALL_THISCALL);
    // static void UIComponent::RegisterObject(Context* context) | File: ../UI/UIComponent.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UIComponent", asBEHAVE_RELEASE, "void f()", AS_METHODPR(UIComponent, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "void Remove()", AS_METHODPR(UIComponent, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(UIComponent, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void RemoveInstanceDefault()", AS_METHODPR(UIComponent, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void RemoveObjectAnimation()", AS_METHODPR(UIComponent, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void ResetToDefault()", AS_METHODPR(UIComponent, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool Component::Save(Serializer& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "bool Save(Serializer&) const", AS_METHODPR(UIComponent, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool SaveDefaultAttributes() const", AS_METHODPR(UIComponent, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Component::SaveJSON(JSONValue& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "bool SaveJSON(JSONValue&) const", AS_METHODPR(UIComponent, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool Component::SaveXML(XMLElement& dest) const override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "bool SaveXML(XMLElement&) const", AS_METHODPR(UIComponent, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void SendEvent(StringHash)", AS_METHODPR(UIComponent, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(UIComponent, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetAnimationEnabled(bool)", AS_METHODPR(UIComponent, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "void set_animationEnabled(bool)", AS_METHODPR(UIComponent, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetAnimationTime(float)", AS_METHODPR(UIComponent, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(UIComponent, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(UIComponent, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(UIComponent, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(UIComponent, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(UIComponent, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(UIComponent, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(UIComponent, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void SetBlockEvents(bool)", AS_METHODPR(UIComponent, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UIComponent", "void SetEnabled(bool)", AS_METHODPR(UIComponent, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "void set_enabled(bool)", AS_METHODPR(UIComponent, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(UIComponent, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(UIComponent, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void SetInstanceDefault(bool)", AS_METHODPR(UIComponent, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(UIComponent, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(UIComponent, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(UIComponent, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIComponent", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(UIComponent, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void SetTemporary(bool)", AS_METHODPR(UIComponent, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "void set_temporary(bool)", AS_METHODPR(UIComponent, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void UIComponent::SetViewportIndex(unsigned index) | File: ../UI/UIComponent.h
    engine->RegisterObjectMethod("UIComponent", "void SetViewportIndex(uint)", AS_METHODPR(UIComponent, SetViewportIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit UIComponent::UIComponent(Context* context) | File: ../UI/UIComponent.h
    engine->RegisterObjectBehaviour("UIComponent", asBEHAVE_FACTORY, "UIComponent@+ f()", AS_FUNCTION(UIComponent_UIComponent_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void UnsubscribeFromAllEvents()", AS_METHODPR(UIComponent, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(UIComponent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(UIComponent, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(UIComponent, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIComponent", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(UIComponent, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UIComponent", "int WeakRefs() const", AS_METHODPR(UIComponent, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIComponent", "int get_weakRefs() const", AS_METHODPR(UIComponent, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(UIComponent, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(UIComponent, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIComponent", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(UIComponent, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("UIElement", "void AddChild(UIElement@+)", AS_METHODPR(UIElement, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UIElement", asBEHAVE_ADDREF, "void f()", AS_METHODPR(UIElement, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void AddTag(const String&in)", AS_METHODPR(UIElement, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(UIElement, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(UIElement_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void AdjustScissor(IntRect&)", AS_METHODPR(UIElement, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void AllocateNetworkState()", AS_METHODPR(UIElement, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void ApplyAttributes()", AS_METHODPR(UIElement, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void BringToFront()", AS_METHODPR(UIElement, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(UIElement, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void DisableLayoutUpdate()", AS_METHODPR(UIElement, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(UIElement, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void EnableLayoutUpdate()", AS_METHODPR(UIElement, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(UIElement, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "uint FindChild(UIElement@+) const", AS_METHODPR(UIElement, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "bool GetAnimationEnabled() const", AS_METHODPR(UIElement, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_animationEnabled() const", AS_METHODPR(UIElement, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const String& GetAppliedStyle() const", AS_METHODPR(UIElement, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const String& get_style() const", AS_METHODPR(UIElement, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "Variant GetAttribute(uint) const", AS_METHODPR(UIElement, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "Variant get_attributes(uint) const", AS_METHODPR(UIElement, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "Variant GetAttribute(const String&in) const", AS_METHODPR(UIElement, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(UIElement, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(UIElement, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(UIElement, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(UIElement, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "Variant GetAttributeDefault(uint) const", AS_METHODPR(UIElement, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "Variant get_attributeDefaults(uint) const", AS_METHODPR(UIElement, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(UIElement, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // virtual void UIElement::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "bool GetBlockEvents() const", AS_METHODPR(UIElement, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool GetBringToBack() const", AS_METHODPR(UIElement, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_bringToBack() const", AS_METHODPR(UIElement, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool GetBringToFront() const", AS_METHODPR(UIElement, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_bringToFront() const", AS_METHODPR(UIElement, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "const String& GetCategory() const", AS_METHODPR(UIElement, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const String& get_category() const", AS_METHODPR(UIElement, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ GetChild(uint) const", AS_METHODPR(UIElement, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "UIElement@+ get_children(uint) const", AS_METHODPR(UIElement, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(UIElement, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(UIElement, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetChildOffset() const", AS_METHODPR(UIElement, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_childOffset() const", AS_METHODPR(UIElement, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(UIElement_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(UIElement_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(UIElement_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntRect& GetClipBorder() const", AS_METHODPR(UIElement, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntRect& get_clipBorder() const", AS_METHODPR(UIElement, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool GetClipChildren() const", AS_METHODPR(UIElement, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_clipChildren() const", AS_METHODPR(UIElement, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Color& GetColor(Corner) const", AS_METHODPR(UIElement, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const Color& get_colors(Corner) const", AS_METHODPR(UIElement, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Color& GetColorAttr() const", AS_METHODPR(UIElement, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "IntRect GetCombinedScreenRect()", AS_METHODPR(UIElement, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "IntRect get_combinedScreenRect()", AS_METHODPR(UIElement, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(UIElement, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Color& GetDerivedColor() const", AS_METHODPR(UIElement, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "float GetDerivedOpacity() const", AS_METHODPR(UIElement, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "float get_derivedOpacity() const", AS_METHODPR(UIElement, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(UIElement, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(UIElement, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "uint GetDragButtonCount() const", AS_METHODPR(UIElement, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "uint get_dragButtonCount() const", AS_METHODPR(UIElement, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(UIElement, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(UIElement, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(UIElement, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ GetElementEventSender() const", AS_METHODPR(UIElement, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool GetEnableAnchor() const", AS_METHODPR(UIElement, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_enableAnchor() const", AS_METHODPR(UIElement, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "VariantMap& GetEventDataMap() const", AS_METHODPR(UIElement, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "Object@+ GetEventSender() const", AS_METHODPR(UIElement, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "FocusMode GetFocusMode() const", AS_METHODPR(UIElement, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "FocusMode get_focusMode() const", AS_METHODPR(UIElement, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(UIElement, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(UIElement, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "const VariantMap& GetGlobalVars() const", AS_METHODPR(UIElement, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const VariantMap& get_globalVars() const", AS_METHODPR(UIElement, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetHeight() const", AS_METHODPR(UIElement, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_height() const", AS_METHODPR(UIElement, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(UIElement, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(UIElement, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetIndent() const", AS_METHODPR(UIElement, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_indent() const", AS_METHODPR(UIElement, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetIndentSpacing() const", AS_METHODPR(UIElement, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_indentSpacing() const", AS_METHODPR(UIElement, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetIndentWidth() const", AS_METHODPR(UIElement, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_indentWidth() const", AS_METHODPR(UIElement, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(UIElement, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntRect& GetLayoutBorder() const", AS_METHODPR(UIElement, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntRect& get_layoutBorder() const", AS_METHODPR(UIElement, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetLayoutElementMaxSize() const", AS_METHODPR(UIElement, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(UIElement, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(UIElement, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "LayoutMode GetLayoutMode() const", AS_METHODPR(UIElement, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "LayoutMode get_layoutMode() const", AS_METHODPR(UIElement, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetLayoutSpacing() const", AS_METHODPR(UIElement, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_layoutSpacing() const", AS_METHODPR(UIElement, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Vector2& GetMaxAnchor() const", AS_METHODPR(UIElement, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const Vector2& get_maxAnchor() const", AS_METHODPR(UIElement, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetMaxHeight() const", AS_METHODPR(UIElement, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_maxHeight() const", AS_METHODPR(UIElement, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetMaxOffset() const", AS_METHODPR(UIElement, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_maxOffset() const", AS_METHODPR(UIElement, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetMaxSize() const", AS_METHODPR(UIElement, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_maxSize() const", AS_METHODPR(UIElement, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetMaxWidth() const", AS_METHODPR(UIElement, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_maxWidth() const", AS_METHODPR(UIElement, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Vector2& GetMinAnchor() const", AS_METHODPR(UIElement, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const Vector2& get_minAnchor() const", AS_METHODPR(UIElement, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetMinHeight() const", AS_METHODPR(UIElement, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_minHeight() const", AS_METHODPR(UIElement, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetMinOffset() const", AS_METHODPR(UIElement, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_minOffset() const", AS_METHODPR(UIElement, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetMinSize() const", AS_METHODPR(UIElement, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_minSize() const", AS_METHODPR(UIElement, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetMinWidth() const", AS_METHODPR(UIElement, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_minWidth() const", AS_METHODPR(UIElement, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const String& GetName() const", AS_METHODPR(UIElement, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const String& get_name() const", AS_METHODPR(UIElement, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "uint GetNumAttributes() const", AS_METHODPR(UIElement, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "uint get_numAttributes() const", AS_METHODPR(UIElement, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "uint GetNumChildren(bool = false) const", AS_METHODPR(UIElement, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "uint get_numChildren(bool = false) const", AS_METHODPR(UIElement, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "uint GetNumNetworkAttributes() const", AS_METHODPR(UIElement, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(UIElement, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(UIElement, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(UIElement, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "float GetOpacity() const", AS_METHODPR(UIElement, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "float get_opacity() const", AS_METHODPR(UIElement, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ GetParent() const", AS_METHODPR(UIElement, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "UIElement@+ get_parent() const", AS_METHODPR(UIElement, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Vector2& GetPivot() const", AS_METHODPR(UIElement, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const Vector2& get_pivot() const", AS_METHODPR(UIElement, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetPosition() const", AS_METHODPR(UIElement, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_position() const", AS_METHODPR(UIElement, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetPriority() const", AS_METHODPR(UIElement, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_priority() const", AS_METHODPR(UIElement, GetPriority, () const, int), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ GetRoot() const", AS_METHODPR(UIElement, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "UIElement@+ get_root() const", AS_METHODPR(UIElement, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetScreenPosition() const", AS_METHODPR(UIElement, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_screenPosition() const", AS_METHODPR(UIElement, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const IntVector2& GetSize() const", AS_METHODPR(UIElement, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const IntVector2& get_size() const", AS_METHODPR(UIElement, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool GetSortChildren() const", AS_METHODPR(UIElement, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_sortChildren() const", AS_METHODPR(UIElement, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(UIElement, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(UIElement_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("UIElement", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(UIElement_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "TraversalMode GetTraversalMode() const", AS_METHODPR(UIElement, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "TraversalMode get_traversalMode() const", AS_METHODPR(UIElement, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "StringHash GetType() const", AS_METHODPR(UIElement, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "StringHash get_type() const", AS_METHODPR(UIElement, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "const String& GetTypeName() const", AS_METHODPR(UIElement, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "const String& get_typeName() const", AS_METHODPR(UIElement, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool GetUseDerivedOpacity() const", AS_METHODPR(UIElement, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_useDerivedOpacity() const", AS_METHODPR(UIElement, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(UIElement, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "const VariantMap& GetVars() const", AS_METHODPR(UIElement, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(UIElement, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(UIElement, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "int GetWidth() const", AS_METHODPR(UIElement, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_width() const", AS_METHODPR(UIElement, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool HasColorGradient() const", AS_METHODPR(UIElement, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_colorGradient() const", AS_METHODPR(UIElement, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "bool HasEventHandlers() const", AS_METHODPR(UIElement, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool HasFocus() const", AS_METHODPR(UIElement, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_focus() const", AS_METHODPR(UIElement, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(UIElement, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(UIElement, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool HasTag(const String&in) const", AS_METHODPR(UIElement, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void InsertChild(uint, UIElement@+)", AS_METHODPR(UIElement, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsChildOf(UIElement@+) const", AS_METHODPR(UIElement, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsEditable() const", AS_METHODPR(UIElement, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_editable() const", AS_METHODPR(UIElement, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsElementEventSender() const", AS_METHODPR(UIElement, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_elementEventSender() const", AS_METHODPR(UIElement, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsEnabled() const", AS_METHODPR(UIElement, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_enabled() const", AS_METHODPR(UIElement, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsEnabledSelf() const", AS_METHODPR(UIElement, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_enabledSelf() const", AS_METHODPR(UIElement, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsFixedHeight() const", AS_METHODPR(UIElement, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_fixedHeight() const", AS_METHODPR(UIElement, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsFixedSize() const", AS_METHODPR(UIElement, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_fixedSize() const", AS_METHODPR(UIElement, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsFixedWidth() const", AS_METHODPR(UIElement, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_fixedWidth() const", AS_METHODPR(UIElement, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsHovering() const", AS_METHODPR(UIElement, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_hovering() const", AS_METHODPR(UIElement, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsInside(IntVector2, bool)", AS_METHODPR(UIElement, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(UIElement, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "bool IsInstanceOf(StringHash) const", AS_METHODPR(UIElement, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsInternal() const", AS_METHODPR(UIElement, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_internal() const", AS_METHODPR(UIElement, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsSelected() const", AS_METHODPR(UIElement, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_selected() const", AS_METHODPR(UIElement, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool IsTemporary() const", AS_METHODPR(UIElement, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_temporary() const", AS_METHODPR(UIElement, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsVisible() const", AS_METHODPR(UIElement, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_visible() const", AS_METHODPR(UIElement, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsVisibleEffective() const", AS_METHODPR(UIElement, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool get_visibleEffective() const", AS_METHODPR(UIElement, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsWheelHandler() const", AS_METHODPR(UIElement, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(UIElement, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool Load(Deserializer&)", AS_METHODPR(UIElement, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(UIElement, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(UIElement, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool LoadXML(const XMLElement&in)", AS_METHODPR(UIElement, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(UIElement, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool LoadXML(Deserializer&)", AS_METHODPR(UIElement, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void MarkNetworkUpdate()", AS_METHODPR(UIElement, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(UIElement, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(UIElement, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(UIElement, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(UIElement, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(UIElement, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(UIElement, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(UIElement, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(UIElement, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(UIElement, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(UIElement, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(UIElement, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(UIElement, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnIndentSet()", AS_METHODPR(UIElement, OnIndentSet, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(UIElement, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(UIElement, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(UIElement, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(UIElement, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnSetEditable()", AS_METHODPR(UIElement, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnTextInput(const String&in)", AS_METHODPR(UIElement, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(UIElement, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(UIElement, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(UIElement, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UIElement", "int Refs() const", AS_METHODPR(UIElement, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_refs() const", AS_METHODPR(UIElement, Refs, () const, int), AS_CALL_THISCALL);
    // static void UIElement::RegisterObject(Context* context) | File: ../UI/UIElement.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UIElement", asBEHAVE_RELEASE, "void f()", AS_METHODPR(UIElement, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void Remove()", AS_METHODPR(UIElement, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void RemoveAllChildren()", AS_METHODPR(UIElement, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void RemoveAllTags()", AS_METHODPR(UIElement, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(UIElement, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(UIElement, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void RemoveChildAtIndex(uint)", AS_METHODPR(UIElement, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void RemoveInstanceDefault()", AS_METHODPR(UIElement, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void RemoveObjectAnimation()", AS_METHODPR(UIElement, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool RemoveTag(const String&in)", AS_METHODPR(UIElement, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void ResetDeepEnabled()", AS_METHODPR(UIElement, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void ResetToDefault()", AS_METHODPR(UIElement, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool Save(Serializer&) const", AS_METHODPR(UIElement, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool SaveDefaultAttributes() const", AS_METHODPR(UIElement, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "bool SaveJSON(JSONValue&) const", AS_METHODPR(UIElement, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool SaveXML(XMLElement&) const", AS_METHODPR(UIElement, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(UIElement, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(UIElement, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void SendEvent(StringHash)", AS_METHODPR(UIElement, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(UIElement, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(UIElement, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetAnimationEnabled(bool)", AS_METHODPR(UIElement, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_animationEnabled(bool)", AS_METHODPR(UIElement, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetAnimationTime(float)", AS_METHODPR(UIElement, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(UIElement, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(UIElement, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(UIElement, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(UIElement, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(UIElement, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(UIElement, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(UIElement, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void SetBlockEvents(bool)", AS_METHODPR(UIElement, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetBringToBack(bool)", AS_METHODPR(UIElement, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_bringToBack(bool)", AS_METHODPR(UIElement, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetBringToFront(bool)", AS_METHODPR(UIElement, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_bringToFront(bool)", AS_METHODPR(UIElement, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(UIElement, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetClipBorder(const IntRect&in)", AS_METHODPR(UIElement, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_clipBorder(const IntRect&in)", AS_METHODPR(UIElement, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetClipChildren(bool)", AS_METHODPR(UIElement, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_clipChildren(bool)", AS_METHODPR(UIElement, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetColor(const Color&in)", AS_METHODPR(UIElement, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_color(const Color&in)", AS_METHODPR(UIElement, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetColor(Corner, const Color&in)", AS_METHODPR(UIElement, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_colors(Corner, const Color&in)", AS_METHODPR(UIElement, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetDeepEnabled(bool)", AS_METHODPR(UIElement, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(UIElement, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(UIElement, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(UIElement, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(UIElement, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetEditable(bool)", AS_METHODPR(UIElement, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_editable(bool)", AS_METHODPR(UIElement, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetElementEventSender(bool)", AS_METHODPR(UIElement, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_elementEventSender(bool)", AS_METHODPR(UIElement, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetEnableAnchor(bool)", AS_METHODPR(UIElement, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_enableAnchor(bool)", AS_METHODPR(UIElement, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetEnabled(bool)", AS_METHODPR(UIElement, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_enabled(bool)", AS_METHODPR(UIElement, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetEnabledRecursive(bool)", AS_METHODPR(UIElement, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetFixedHeight(int)", AS_METHODPR(UIElement, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(UIElement, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetFixedSize(int, int)", AS_METHODPR(UIElement, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetFixedWidth(int)", AS_METHODPR(UIElement, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetFocus(bool)", AS_METHODPR(UIElement, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_focus(bool)", AS_METHODPR(UIElement, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetFocusMode(FocusMode)", AS_METHODPR(UIElement, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_focusMode(FocusMode)", AS_METHODPR(UIElement, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(UIElement, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(UIElement, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetHeight(int)", AS_METHODPR(UIElement, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_height(int)", AS_METHODPR(UIElement, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(UIElement, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(UIElement, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetHovering(bool)", AS_METHODPR(UIElement, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetIndent(int)", AS_METHODPR(UIElement, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_indent(int)", AS_METHODPR(UIElement, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetIndentSpacing(int)", AS_METHODPR(UIElement, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_indentSpacing(int)", AS_METHODPR(UIElement, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void SetInstanceDefault(bool)", AS_METHODPR(UIElement, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(UIElement, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetInternal(bool)", AS_METHODPR(UIElement, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_internal(bool)", AS_METHODPR(UIElement, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(UIElement, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(UIElement, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(UIElement, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(UIElement, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(UIElement, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetLayoutMode(LayoutMode)", AS_METHODPR(UIElement, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_layoutMode(LayoutMode)", AS_METHODPR(UIElement, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetLayoutSpacing(int)", AS_METHODPR(UIElement, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_layoutSpacing(int)", AS_METHODPR(UIElement, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(UIElement, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(UIElement, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxAnchor(float, float)", AS_METHODPR(UIElement, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxHeight(int)", AS_METHODPR(UIElement, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_maxHeight(int)", AS_METHODPR(UIElement, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(UIElement, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(UIElement, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(UIElement, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_maxSize(const IntVector2&in)", AS_METHODPR(UIElement, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxSize(int, int)", AS_METHODPR(UIElement, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMaxWidth(int)", AS_METHODPR(UIElement, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_maxWidth(int)", AS_METHODPR(UIElement, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(UIElement, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_minAnchor(const Vector2&in)", AS_METHODPR(UIElement, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinAnchor(float, float)", AS_METHODPR(UIElement, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinHeight(int)", AS_METHODPR(UIElement, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_minHeight(int)", AS_METHODPR(UIElement, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(UIElement, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_minOffset(const IntVector2&in)", AS_METHODPR(UIElement, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinSize(const IntVector2&in)", AS_METHODPR(UIElement, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_minSize(const IntVector2&in)", AS_METHODPR(UIElement, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinSize(int, int)", AS_METHODPR(UIElement, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetMinWidth(int)", AS_METHODPR(UIElement, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_minWidth(int)", AS_METHODPR(UIElement, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetName(const String&in)", AS_METHODPR(UIElement, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_name(const String&in)", AS_METHODPR(UIElement, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(UIElement, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(UIElement, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UIElement", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(UIElement, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetOpacity(float)", AS_METHODPR(UIElement, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_opacity(float)", AS_METHODPR(UIElement, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(UIElement, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetPivot(const Vector2&in)", AS_METHODPR(UIElement, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_pivot(const Vector2&in)", AS_METHODPR(UIElement, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetPivot(float, float)", AS_METHODPR(UIElement, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetPosition(const IntVector2&in)", AS_METHODPR(UIElement, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_position(const IntVector2&in)", AS_METHODPR(UIElement, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetPosition(int, int)", AS_METHODPR(UIElement, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetPriority(int)", AS_METHODPR(UIElement, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_priority(int)", AS_METHODPR(UIElement, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(UIElement, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetSelected(bool)", AS_METHODPR(UIElement, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_selected(bool)", AS_METHODPR(UIElement, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetSize(const IntVector2&in)", AS_METHODPR(UIElement, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_size(const IntVector2&in)", AS_METHODPR(UIElement, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetSize(int, int)", AS_METHODPR(UIElement, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetSortChildren(bool)", AS_METHODPR(UIElement, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_sortChildren(bool)", AS_METHODPR(UIElement, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(UIElement, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool SetStyle(const XMLElement&in)", AS_METHODPR(UIElement, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(UIElement, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(UIElement_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void SetTemporary(bool)", AS_METHODPR(UIElement, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_temporary(bool)", AS_METHODPR(UIElement, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetTraversalMode(TraversalMode)", AS_METHODPR(UIElement, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_traversalMode(TraversalMode)", AS_METHODPR(UIElement, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetUseDerivedOpacity(bool)", AS_METHODPR(UIElement, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_useDerivedOpacity(bool)", AS_METHODPR(UIElement, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(UIElement, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(UIElement, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(UIElement, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetVisible(bool)", AS_METHODPR(UIElement, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_visible(bool)", AS_METHODPR(UIElement, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SetWidth(int)", AS_METHODPR(UIElement, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "void set_width(int)", AS_METHODPR(UIElement, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void SortChildren()", AS_METHODPR(UIElement, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // explicit UIElement::UIElement(Context* context) | File: ../UI/UIElement.h
    engine->RegisterObjectBehaviour("UIElement", asBEHAVE_FACTORY, "UIElement@+ f()", AS_FUNCTION(UIElement_UIElement_Context), AS_CALL_CDECL);
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void UnsubscribeFromAllEvents()", AS_METHODPR(UIElement, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(UIElement_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(UIElement, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(UIElement, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UIElement", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(UIElement, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void Update(float)", AS_METHODPR(UIElement, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UIElement", "void UpdateLayout()", AS_METHODPR(UIElement, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UIElement", "int WeakRefs() const", AS_METHODPR(UIElement, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UIElement", "int get_weakRefs() const", AS_METHODPR(UIElement, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(UIElement, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(UIElement, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UIElement", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(UIElement, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("UISelectable", "void AddChild(UIElement@+)", AS_METHODPR(UISelectable, AddChild, (UIElement*), void), AS_CALL_THISCALL);
    // void RefCounted::AddRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UISelectable", asBEHAVE_ADDREF, "void f()", AS_METHODPR(UISelectable, AddRef, (), void), AS_CALL_THISCALL);
    // void UIElement::AddTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void AddTag(const String&in)", AS_METHODPR(UISelectable, AddTag, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const String& tags, char separator=';') | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void AddTags(const String&in, int8 = ';')", AS_METHODPR(UISelectable, AddTags, (const String&, char), void), AS_CALL_THISCALL);
    // void UIElement::AddTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void AddTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(UISelectable_AddTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::AdjustScissor(IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void AdjustScissor(IntRect&)", AS_METHODPR(UISelectable, AdjustScissor, (IntRect&), void), AS_CALL_THISCALL);
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void AllocateNetworkState()", AS_METHODPR(UISelectable, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // void UIElement::ApplyAttributes() override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void ApplyAttributes()", AS_METHODPR(UISelectable, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // void UIElement::BringToFront() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void BringToFront()", AS_METHODPR(UISelectable, BringToFront, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // UIElement* UIElement::CreateChild(StringHash type, const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ CreateChild(StringHash, const String&in = String::EMPTY, uint = M_MAX_UNSIGNED)", AS_METHODPR(UISelectable, CreateChild, (StringHash, const String&, unsigned), UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::CreateChild(const String& name=String::EMPTY, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    // Not registered because template
    // void UIElement::DisableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void DisableLayoutUpdate()", AS_METHODPR(UISelectable, DisableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "IntVector2 ElementToScreen(const IntVector2&in)", AS_METHODPR(UISelectable, ElementToScreen, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void UIElement::EnableLayoutUpdate() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void EnableLayoutUpdate()", AS_METHODPR(UISelectable, EnableLayoutUpdate, (), void), AS_CALL_THISCALL);
    // bool UIElement::FilterAttributes(XMLElement& dest) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool FilterAttributes(XMLElement&) const", AS_METHODPR(UISelectable, FilterAttributes, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // unsigned UIElement::FindChild(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "uint FindChild(UIElement@+) const", AS_METHODPR(UISelectable, FindChild, (UIElement*) const, unsigned), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "bool GetAnimationEnabled() const", AS_METHODPR(UISelectable, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_animationEnabled() const", AS_METHODPR(UISelectable, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // const String& UIElement::GetAppliedStyle() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const String& GetAppliedStyle() const", AS_METHODPR(UISelectable, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const String& get_style() const", AS_METHODPR(UISelectable, GetAppliedStyle, () const, const String&), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "Variant GetAttribute(uint) const", AS_METHODPR(UISelectable, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "Variant get_attributes(uint) const", AS_METHODPR(UISelectable, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "Variant GetAttribute(const String&in) const", AS_METHODPR(UISelectable, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(UISelectable, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(UISelectable, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(UISelectable, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(UISelectable, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "Variant GetAttributeDefault(uint) const", AS_METHODPR(UISelectable, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "Variant get_attributeDefaults(uint) const", AS_METHODPR(UISelectable, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(UISelectable, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // void UISelectable::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override | File: ../UI/UISelectable.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "bool GetBlockEvents() const", AS_METHODPR(UISelectable, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToBack() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool GetBringToBack() const", AS_METHODPR(UISelectable, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_bringToBack() const", AS_METHODPR(UISelectable, GetBringToBack, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::GetBringToFront() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool GetBringToFront() const", AS_METHODPR(UISelectable, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_bringToFront() const", AS_METHODPR(UISelectable, GetBringToFront, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "const String& GetCategory() const", AS_METHODPR(UISelectable, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const String& get_category() const", AS_METHODPR(UISelectable, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(unsigned index) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ GetChild(uint) const", AS_METHODPR(UISelectable, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ get_children(uint) const", AS_METHODPR(UISelectable, GetChild, (unsigned) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ GetChild(const String&in, bool = false) const", AS_METHODPR(UISelectable, GetChild, (const String&, bool) const, UIElement*), AS_CALL_THISCALL);
    // UIElement* UIElement::GetChild(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ GetChild(const StringHash&in, const Variant&in = Variant::EMPTY, bool = false) const", AS_METHODPR(UISelectable, GetChild, (const StringHash&, const Variant&, bool) const, UIElement*), AS_CALL_THISCALL);
    // template<class T> T* UIElement::GetChildDynamicCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntVector2& UIElement::GetChildOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetChildOffset() const", AS_METHODPR(UISelectable, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_childOffset() const", AS_METHODPR(UISelectable, GetChildOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Vector<SharedPtr<UIElement>>& UIElement::GetChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "Array<UIElement@>@ GetChildren() const", AS_FUNCTION_OBJFIRST(UISelectable_GetChildren_void), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildren(bool recursive) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "Array<UIElement@>@ GetChildren(bool) const", AS_FUNCTION_OBJFIRST(UISelectable_GetChildren_bool), AS_CALL_CDECL_OBJFIRST);
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // PODVector<UIElement*> UIElement::GetChildrenWithTag(const String& tag, bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "Array<UIElement@>@ GetChildrenWithTag(const String&in, bool = false) const", AS_FUNCTION_OBJFIRST(UISelectable_GetChildrenWithTag_String_bool), AS_CALL_CDECL_OBJFIRST);
    // template<class T> T* UIElement::GetChildStaticCast(unsigned index) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // template<class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value=Variant::EMPTY, bool recursive=false) const | File: ../UI/UIElement.h
    // Not registered because template
    // const IntRect& UIElement::GetClipBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntRect& GetClipBorder() const", AS_METHODPR(UISelectable, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntRect& get_clipBorder() const", AS_METHODPR(UISelectable, GetClipBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // bool UIElement::GetClipChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool GetClipChildren() const", AS_METHODPR(UISelectable, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_clipChildren() const", AS_METHODPR(UISelectable, GetClipChildren, () const, bool), AS_CALL_THISCALL);
    // const Color& UIElement::GetColor(Corner corner) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Color& GetColor(Corner) const", AS_METHODPR(UISelectable, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Color& get_colors(Corner) const", AS_METHODPR(UISelectable, GetColor, (Corner) const, const Color&), AS_CALL_THISCALL);
    // const Color& UIElement::GetColorAttr() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Color& GetColorAttr() const", AS_METHODPR(UISelectable, GetColorAttr, () const, const Color&), AS_CALL_THISCALL);
    // IntRect UIElement::GetCombinedScreenRect() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "IntRect GetCombinedScreenRect()", AS_METHODPR(UISelectable, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "IntRect get_combinedScreenRect()", AS_METHODPR(UISelectable, GetCombinedScreenRect, (), IntRect), AS_CALL_THISCALL);
    // Context* Object::GetContext() const | File: ../Core/Object.h
    // Error: type "Context*" can used only as function parameter
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) | File: ../UI/UIElement.h
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "XMLFile@+ GetDefaultStyle(bool = true) const", AS_METHODPR(UISelectable, GetDefaultStyle, (bool) const, XMLFile*), AS_CALL_THISCALL);
    // const Color& UIElement::GetDerivedColor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Color& GetDerivedColor() const", AS_METHODPR(UISelectable, GetDerivedColor, () const, const Color&), AS_CALL_THISCALL);
    // float UIElement::GetDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "float GetDerivedOpacity() const", AS_METHODPR(UISelectable, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "float get_derivedOpacity() const", AS_METHODPR(UISelectable, GetDerivedOpacity, () const, float), AS_CALL_THISCALL);
    // MouseButtonFlags UIElement::GetDragButtonCombo() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "MouseButtonFlags GetDragButtonCombo() const", AS_METHODPR(UISelectable, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "MouseButtonFlags get_dragButtonCombo() const", AS_METHODPR(UISelectable, GetDragButtonCombo, () const, MouseButtonFlags), AS_CALL_THISCALL);
    // unsigned UIElement::GetDragButtonCount() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "uint GetDragButtonCount() const", AS_METHODPR(UISelectable, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "uint get_dragButtonCount() const", AS_METHODPR(UISelectable, GetDragButtonCount, () const, unsigned), AS_CALL_THISCALL);
    // DragAndDropModeFlags UIElement::GetDragDropMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "DragAndDropModeFlags GetDragDropMode() const", AS_METHODPR(UISelectable, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "DragAndDropModeFlags get_dragDropMode() const", AS_METHODPR(UISelectable, GetDragDropMode, () const, DragAndDropModeFlags), AS_CALL_THISCALL);
    // IntVector2 UIElement::GetEffectiveMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "IntVector2 GetEffectiveMinSize() const", AS_METHODPR(UISelectable, GetEffectiveMinSize, () const, IntVector2), AS_CALL_THISCALL);
    // UIElement* UIElement::GetElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ GetElementEventSender() const", AS_METHODPR(UISelectable, GetElementEventSender, () const, UIElement*), AS_CALL_THISCALL);
    // bool UIElement::GetEnableAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool GetEnableAnchor() const", AS_METHODPR(UISelectable, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_enableAnchor() const", AS_METHODPR(UISelectable, GetEnableAnchor, () const, bool), AS_CALL_THISCALL);
    // VariantMap& Object::GetEventDataMap() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "VariantMap& GetEventDataMap() const", AS_METHODPR(UISelectable, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "Object@+ GetEventSender() const", AS_METHODPR(UISelectable, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // FocusMode UIElement::GetFocusMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "FocusMode GetFocusMode() const", AS_METHODPR(UISelectable, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "FocusMode get_focusMode() const", AS_METHODPR(UISelectable, GetFocusMode, () const, FocusMode), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(UISelectable, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(UISelectable, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "const VariantMap& GetGlobalVars() const", AS_METHODPR(UISelectable, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const VariantMap& get_globalVars() const", AS_METHODPR(UISelectable, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // int UIElement::GetHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetHeight() const", AS_METHODPR(UISelectable, GetHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_height() const", AS_METHODPR(UISelectable, GetHeight, () const, int), AS_CALL_THISCALL);
    // HorizontalAlignment UIElement::GetHorizontalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "HorizontalAlignment GetHorizontalAlignment() const", AS_METHODPR(UISelectable, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "HorizontalAlignment get_horizontalAlignment() const", AS_METHODPR(UISelectable, GetHorizontalAlignment, () const, HorizontalAlignment), AS_CALL_THISCALL);
    // const Color& UISelectable::GetHoverColor() const | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("UISelectable", "const Color& GetHoverColor() const", AS_METHODPR(UISelectable, GetHoverColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Color& get_hoverColor() const", AS_METHODPR(UISelectable, GetHoverColor, () const, const Color&), AS_CALL_THISCALL);
    // int UIElement::GetIndent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetIndent() const", AS_METHODPR(UISelectable, GetIndent, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_indent() const", AS_METHODPR(UISelectable, GetIndent, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetIndentSpacing() const", AS_METHODPR(UISelectable, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_indentSpacing() const", AS_METHODPR(UISelectable, GetIndentSpacing, () const, int), AS_CALL_THISCALL);
    // int UIElement::GetIndentWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetIndentWidth() const", AS_METHODPR(UISelectable, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_indentWidth() const", AS_METHODPR(UISelectable, GetIndentWidth, () const, int), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(UISelectable, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // const IntRect& UIElement::GetLayoutBorder() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntRect& GetLayoutBorder() const", AS_METHODPR(UISelectable, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntRect& get_layoutBorder() const", AS_METHODPR(UISelectable, GetLayoutBorder, () const, const IntRect&), AS_CALL_THISCALL);
    // int UIElement::GetLayoutElementMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetLayoutElementMaxSize() const", AS_METHODPR(UISelectable, GetLayoutElementMaxSize, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetLayoutFlexScale() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Vector2& GetLayoutFlexScale() const", AS_METHODPR(UISelectable, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Vector2& get_layoutFlexScale() const", AS_METHODPR(UISelectable, GetLayoutFlexScale, () const, const Vector2&), AS_CALL_THISCALL);
    // LayoutMode UIElement::GetLayoutMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "LayoutMode GetLayoutMode() const", AS_METHODPR(UISelectable, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "LayoutMode get_layoutMode() const", AS_METHODPR(UISelectable, GetLayoutMode, () const, LayoutMode), AS_CALL_THISCALL);
    // int UIElement::GetLayoutSpacing() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetLayoutSpacing() const", AS_METHODPR(UISelectable, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_layoutSpacing() const", AS_METHODPR(UISelectable, GetLayoutSpacing, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMaxAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Vector2& GetMaxAnchor() const", AS_METHODPR(UISelectable, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Vector2& get_maxAnchor() const", AS_METHODPR(UISelectable, GetMaxAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetMaxHeight() const", AS_METHODPR(UISelectable, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_maxHeight() const", AS_METHODPR(UISelectable, GetMaxHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetMaxOffset() const", AS_METHODPR(UISelectable, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_maxOffset() const", AS_METHODPR(UISelectable, GetMaxOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMaxSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetMaxSize() const", AS_METHODPR(UISelectable, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_maxSize() const", AS_METHODPR(UISelectable, GetMaxSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMaxWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetMaxWidth() const", AS_METHODPR(UISelectable, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_maxWidth() const", AS_METHODPR(UISelectable, GetMaxWidth, () const, int), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetMinAnchor() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Vector2& GetMinAnchor() const", AS_METHODPR(UISelectable, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Vector2& get_minAnchor() const", AS_METHODPR(UISelectable, GetMinAnchor, () const, const Vector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetMinHeight() const", AS_METHODPR(UISelectable, GetMinHeight, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_minHeight() const", AS_METHODPR(UISelectable, GetMinHeight, () const, int), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinOffset() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetMinOffset() const", AS_METHODPR(UISelectable, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_minOffset() const", AS_METHODPR(UISelectable, GetMinOffset, () const, const IntVector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetMinSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetMinSize() const", AS_METHODPR(UISelectable, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_minSize() const", AS_METHODPR(UISelectable, GetMinSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetMinWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetMinWidth() const", AS_METHODPR(UISelectable, GetMinWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_minWidth() const", AS_METHODPR(UISelectable, GetMinWidth, () const, int), AS_CALL_THISCALL);
    // const String& UIElement::GetName() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const String& GetName() const", AS_METHODPR(UISelectable, GetName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const String& get_name() const", AS_METHODPR(UISelectable, GetName, () const, const String&), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "uint GetNumAttributes() const", AS_METHODPR(UISelectable, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "uint get_numAttributes() const", AS_METHODPR(UISelectable, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "uint GetNumChildren(bool = false) const", AS_METHODPR(UISelectable, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "uint get_numChildren(bool = false) const", AS_METHODPR(UISelectable, GetNumChildren, (bool) const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "uint GetNumNetworkAttributes() const", AS_METHODPR(UISelectable, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(UISelectable, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(UISelectable, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(UISelectable, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // float UIElement::GetOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "float GetOpacity() const", AS_METHODPR(UISelectable, GetOpacity, () const, float), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "float get_opacity() const", AS_METHODPR(UISelectable, GetOpacity, () const, float), AS_CALL_THISCALL);
    // UIElement* UIElement::GetParent() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ GetParent() const", AS_METHODPR(UISelectable, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ get_parent() const", AS_METHODPR(UISelectable, GetParent, () const, UIElement*), AS_CALL_THISCALL);
    // const Vector2& UIElement::GetPivot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Vector2& GetPivot() const", AS_METHODPR(UISelectable, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Vector2& get_pivot() const", AS_METHODPR(UISelectable, GetPivot, () const, const Vector2&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetPosition() const", AS_METHODPR(UISelectable, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_position() const", AS_METHODPR(UISelectable, GetPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // int UIElement::GetPriority() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetPriority() const", AS_METHODPR(UISelectable, GetPriority, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_priority() const", AS_METHODPR(UISelectable, GetPriority, () const, int), AS_CALL_THISCALL);
    // UIElement* UIElement::GetRoot() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ GetRoot() const", AS_METHODPR(UISelectable, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ get_root() const", AS_METHODPR(UISelectable, GetRoot, () const, UIElement*), AS_CALL_THISCALL);
    // virtual const IntVector2& UIElement::GetScreenPosition() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetScreenPosition() const", AS_METHODPR(UISelectable, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_screenPosition() const", AS_METHODPR(UISelectable, GetScreenPosition, () const, const IntVector2&), AS_CALL_THISCALL);
    // const Color& UISelectable::GetSelectionColor() const | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("UISelectable", "const Color& GetSelectionColor() const", AS_METHODPR(UISelectable, GetSelectionColor, () const, const Color&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const Color& get_selectionColor() const", AS_METHODPR(UISelectable, GetSelectionColor, () const, const Color&), AS_CALL_THISCALL);
    // const IntVector2& UIElement::GetSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& GetSize() const", AS_METHODPR(UISelectable, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const IntVector2& get_size() const", AS_METHODPR(UISelectable, GetSize, () const, const IntVector2&), AS_CALL_THISCALL);
    // bool UIElement::GetSortChildren() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool GetSortChildren() const", AS_METHODPR(UISelectable, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_sortChildren() const", AS_METHODPR(UISelectable, GetSortChildren, () const, bool), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(UISelectable, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // const StringVector& UIElement::GetTags() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "Array<String>@ GetTags() const", AS_FUNCTION_OBJFIRST(UISelectable_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("UISelectable", "Array<String>@ get_tags() const", AS_FUNCTION_OBJFIRST(UISelectable_GetTags_void), AS_CALL_CDECL_OBJFIRST);
    // TraversalMode UIElement::GetTraversalMode() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "TraversalMode GetTraversalMode() const", AS_METHODPR(UISelectable, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "TraversalMode get_traversalMode() const", AS_METHODPR(UISelectable, GetTraversalMode, () const, TraversalMode), AS_CALL_THISCALL);
    // virtual StringHash Object::GetType() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "StringHash GetType() const", AS_METHODPR(UISelectable, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "StringHash get_type() const", AS_METHODPR(UISelectable, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // virtual const String& Object::GetTypeName() const =0 | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "const String& GetTypeName() const", AS_METHODPR(UISelectable, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "const String& get_typeName() const", AS_METHODPR(UISelectable, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // bool UIElement::GetUseDerivedOpacity() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool GetUseDerivedOpacity() const", AS_METHODPR(UISelectable, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_useDerivedOpacity() const", AS_METHODPR(UISelectable, GetUseDerivedOpacity, () const, bool), AS_CALL_THISCALL);
    // const Variant& UIElement::GetVar(const StringHash& key) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const Variant& GetVar(const StringHash&in) const", AS_METHODPR(UISelectable, GetVar, (const StringHash&) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "const VariantMap& GetVars() const", AS_METHODPR(UISelectable, GetVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // VerticalAlignment UIElement::GetVerticalAlignment() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "VerticalAlignment GetVerticalAlignment() const", AS_METHODPR(UISelectable, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "VerticalAlignment get_verticalAlignment() const", AS_METHODPR(UISelectable, GetVerticalAlignment, () const, VerticalAlignment), AS_CALL_THISCALL);
    // int UIElement::GetWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "int GetWidth() const", AS_METHODPR(UISelectable, GetWidth, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_width() const", AS_METHODPR(UISelectable, GetWidth, () const, int), AS_CALL_THISCALL);
    // bool UIElement::HasColorGradient() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool HasColorGradient() const", AS_METHODPR(UISelectable, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_colorGradient() const", AS_METHODPR(UISelectable, HasColorGradient, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "bool HasEventHandlers() const", AS_METHODPR(UISelectable, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasFocus() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool HasFocus() const", AS_METHODPR(UISelectable, HasFocus, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_focus() const", AS_METHODPR(UISelectable, HasFocus, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(UISelectable, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(UISelectable, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool UIElement::HasTag(const String& tag) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool HasTag(const String&in) const", AS_METHODPR(UISelectable, HasTag, (const String&) const, bool), AS_CALL_THISCALL);
    // void UIElement::InsertChild(unsigned index, UIElement* element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void InsertChild(uint, UIElement@+)", AS_METHODPR(UISelectable, InsertChild, (unsigned, UIElement*), void), AS_CALL_THISCALL);
    // bool UIElement::IsChildOf(UIElement* element) const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsChildOf(UIElement@+) const", AS_METHODPR(UISelectable, IsChildOf, (UIElement*) const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEditable() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsEditable() const", AS_METHODPR(UISelectable, IsEditable, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_editable() const", AS_METHODPR(UISelectable, IsEditable, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsElementEventSender() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsElementEventSender() const", AS_METHODPR(UISelectable, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_elementEventSender() const", AS_METHODPR(UISelectable, IsElementEventSender, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabled() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsEnabled() const", AS_METHODPR(UISelectable, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_enabled() const", AS_METHODPR(UISelectable, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsEnabledSelf() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsEnabledSelf() const", AS_METHODPR(UISelectable, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_enabledSelf() const", AS_METHODPR(UISelectable, IsEnabledSelf, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedHeight() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsFixedHeight() const", AS_METHODPR(UISelectable, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_fixedHeight() const", AS_METHODPR(UISelectable, IsFixedHeight, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedSize() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsFixedSize() const", AS_METHODPR(UISelectable, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_fixedSize() const", AS_METHODPR(UISelectable, IsFixedSize, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsFixedWidth() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsFixedWidth() const", AS_METHODPR(UISelectable, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_fixedWidth() const", AS_METHODPR(UISelectable, IsFixedWidth, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsHovering() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsHovering() const", AS_METHODPR(UISelectable, IsHovering, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_hovering() const", AS_METHODPR(UISelectable, IsHovering, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsInside(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsInside(IntVector2, bool)", AS_METHODPR(UISelectable, IsInside, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool UIElement::IsInsideCombined(IntVector2 position, bool isScreen) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsInsideCombined(IntVector2, bool)", AS_METHODPR(UISelectable, IsInsideCombined, (IntVector2, bool), bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "bool IsInstanceOf(StringHash) const", AS_METHODPR(UISelectable, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool UIElement::IsInternal() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsInternal() const", AS_METHODPR(UISelectable, IsInternal, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_internal() const", AS_METHODPR(UISelectable, IsInternal, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsSelected() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsSelected() const", AS_METHODPR(UISelectable, IsSelected, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_selected() const", AS_METHODPR(UISelectable, IsSelected, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool IsTemporary() const", AS_METHODPR(UISelectable, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_temporary() const", AS_METHODPR(UISelectable, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisible() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsVisible() const", AS_METHODPR(UISelectable, IsVisible, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_visible() const", AS_METHODPR(UISelectable, IsVisible, () const, bool), AS_CALL_THISCALL);
    // bool UIElement::IsVisibleEffective() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsVisibleEffective() const", AS_METHODPR(UISelectable, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool get_visibleEffective() const", AS_METHODPR(UISelectable, IsVisibleEffective, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWheelHandler() const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsWheelHandler() const", AS_METHODPR(UISelectable, IsWheelHandler, () const, bool), AS_CALL_THISCALL);
    // virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool IsWithinScissor(const IntRect&in)", AS_METHODPR(UISelectable, IsWithinScissor, (const IntRect&), bool), AS_CALL_THISCALL);
    // virtual bool Serializable::Load(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool Load(Deserializer&)", AS_METHODPR(UISelectable, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "UIElement@+ LoadChildXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(UISelectable, LoadChildXML, (const XMLElement&, XMLFile*), UIElement*), AS_CALL_THISCALL);
    // bool Animatable::LoadJSON(const JSONValue& source) override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(UISelectable, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool LoadXML(const XMLElement&in)", AS_METHODPR(UISelectable, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool LoadXML(const XMLElement&in, XMLFile@+)", AS_METHODPR(UISelectable, LoadXML, (const XMLElement&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool LoadXML(Deserializer&)", AS_METHODPR(UISelectable, LoadXML, (Deserializer&), bool), AS_CALL_THISCALL);
    // virtual void Serializable::MarkNetworkUpdate() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void MarkNetworkUpdate()", AS_METHODPR(UISelectable, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnClickBegin(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(UISelectable, OnClickBegin, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnClickEnd(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+, UIElement@+)", AS_METHODPR(UISelectable, OnClickEnd, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*, UIElement*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnDoubleClick(const IntVector2&in, const IntVector2&in, MouseButton, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(UISelectable, OnDoubleClick, (const IntVector2&, const IntVector2&, MouseButton, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnDragBegin(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(UISelectable, OnDragBegin, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnDragCancel(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(UISelectable, OnDragCancel, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropFinish(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool OnDragDropFinish(UIElement@+)", AS_METHODPR(UISelectable, OnDragDropFinish, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual bool UIElement::OnDragDropTest(UIElement* source) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool OnDragDropTest(UIElement@+)", AS_METHODPR(UISelectable, OnDragDropTest, (UIElement*), bool), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnDragEnd(const IntVector2&in, const IntVector2&in, MouseButtonFlags, MouseButtonFlags, Cursor@+)", AS_METHODPR(UISelectable, OnDragEnd, (const IntVector2&, const IntVector2&, MouseButtonFlags, MouseButtonFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnDragMove(const IntVector2&in, const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(UISelectable, OnDragMove, (const IntVector2&, const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(UISelectable, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(UISelectable, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnHover(const IntVector2&in, const IntVector2&in, MouseButtonFlags, QualifierFlags, Cursor@+)", AS_METHODPR(UISelectable, OnHover, (const IntVector2&, const IntVector2&, MouseButtonFlags, QualifierFlags, Cursor*), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnIndentSet() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnIndentSet()", AS_METHODPR(UISelectable, OnIndentSet, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnKey(Key, MouseButtonFlags, QualifierFlags)", AS_METHODPR(UISelectable, OnKey, (Key, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnPositionSet(const IntVector2& newPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnPositionSet(const IntVector2&in)", AS_METHODPR(UISelectable, OnPositionSet, (const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnResize(const IntVector2&in, const IntVector2&in)", AS_METHODPR(UISelectable, OnResize, (const IntVector2&, const IntVector2&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(UISelectable, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnSetEditable() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnSetEditable()", AS_METHODPR(UISelectable, OnSetEditable, (), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnTextInput(const String& text) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnTextInput(const String&in)", AS_METHODPR(UISelectable, OnTextInput, (const String&), void), AS_CALL_THISCALL);
    // virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void OnWheel(int, MouseButtonFlags, QualifierFlags)", AS_METHODPR(UISelectable, OnWheel, (int, MouseButtonFlags, QualifierFlags), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(UISelectable, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(UISelectable, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UISelectable", "int Refs() const", AS_METHODPR(UISelectable, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_refs() const", AS_METHODPR(UISelectable, Refs, () const, int), AS_CALL_THISCALL);
    // static void UISelectable::RegisterObject(Context* context) | File: ../UI/UISelectable.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UISelectable", asBEHAVE_RELEASE, "void f()", AS_METHODPR(UISelectable, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void UIElement::Remove() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void Remove()", AS_METHODPR(UISelectable, Remove, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveAllChildren()", AS_METHODPR(UISelectable, RemoveAllChildren, (), void), AS_CALL_THISCALL);
    // void UIElement::RemoveAllTags() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveAllTags()", AS_METHODPR(UISelectable, RemoveAllTags, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(UISelectable, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChild(UIElement* element, unsigned index=0) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveChild(UIElement@+, uint = 0)", AS_METHODPR(UISelectable, RemoveChild, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveChildAtIndex(uint)", AS_METHODPR(UISelectable, RemoveChildAtIndex, (unsigned), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveInstanceDefault()", AS_METHODPR(UISelectable, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void RemoveObjectAnimation()", AS_METHODPR(UISelectable, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // bool UIElement::RemoveTag(const String& tag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool RemoveTag(const String&in)", AS_METHODPR(UISelectable, RemoveTag, (const String&), bool), AS_CALL_THISCALL);
    // void UIElement::ResetDeepEnabled() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void ResetDeepEnabled()", AS_METHODPR(UISelectable, ResetDeepEnabled, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void ResetToDefault()", AS_METHODPR(UISelectable, ResetToDefault, (), void), AS_CALL_THISCALL);
    // virtual bool Serializable::Save(Serializer& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool Save(Serializer&) const", AS_METHODPR(UISelectable, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool SaveDefaultAttributes() const", AS_METHODPR(UISelectable, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool Animatable::SaveJSON(JSONValue& dest) const override | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "bool SaveJSON(JSONValue&) const", AS_METHODPR(UISelectable, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(XMLElement& dest) const override | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool SaveXML(XMLElement&) const", AS_METHODPR(UISelectable, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // bool UIElement::SaveXML(Serializer& dest, const String& indentation="\t") const | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool SaveXML(Serializer&, const String&in = \"\t\") const", AS_METHODPR(UISelectable, SaveXML, (Serializer&, const String&) const, bool), AS_CALL_THISCALL);
    // virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "IntVector2 ScreenToElement(const IntVector2&in)", AS_METHODPR(UISelectable, ScreenToElement, (const IntVector2&), IntVector2), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void SendEvent(StringHash)", AS_METHODPR(UISelectable, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(UISelectable, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void UIElement::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetAlignment(HorizontalAlignment, VerticalAlignment)", AS_METHODPR(UISelectable, SetAlignment, (HorizontalAlignment, VerticalAlignment), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetAnimationEnabled(bool)", AS_METHODPR(UISelectable, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_animationEnabled(bool)", AS_METHODPR(UISelectable, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetAnimationTime(float)", AS_METHODPR(UISelectable, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(UISelectable, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(UISelectable, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(UISelectable, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(UISelectable, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(UISelectable, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(UISelectable, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(UISelectable, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void SetBlockEvents(bool)", AS_METHODPR(UISelectable, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToBack(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetBringToBack(bool)", AS_METHODPR(UISelectable, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_bringToBack(bool)", AS_METHODPR(UISelectable, SetBringToBack, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetBringToFront(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetBringToFront(bool)", AS_METHODPR(UISelectable, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_bringToFront(bool)", AS_METHODPR(UISelectable, SetBringToFront, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetChildOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetChildOffset(const IntVector2&in)", AS_METHODPR(UISelectable, SetChildOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipBorder(const IntRect& rect) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetClipBorder(const IntRect&in)", AS_METHODPR(UISelectable, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_clipBorder(const IntRect&in)", AS_METHODPR(UISelectable, SetClipBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetClipChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetClipChildren(bool)", AS_METHODPR(UISelectable, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_clipChildren(bool)", AS_METHODPR(UISelectable, SetClipChildren, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetColor(const Color&in)", AS_METHODPR(UISelectable, SetColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_color(const Color&in)", AS_METHODPR(UISelectable, SetColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetColor(Corner corner, const Color& color) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetColor(Corner, const Color&in)", AS_METHODPR(UISelectable, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_colors(Corner, const Color&in)", AS_METHODPR(UISelectable, SetColor, (Corner, const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetDeepEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetDeepEnabled(bool)", AS_METHODPR(UISelectable, SetDeepEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetDefaultStyle(XMLFile* style) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetDefaultStyle(XMLFile@+)", AS_METHODPR(UISelectable, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_defaultStyle(XMLFile@+)", AS_METHODPR(UISelectable, SetDefaultStyle, (XMLFile*), void), AS_CALL_THISCALL);
    // void UIElement::SetDragDropMode(DragAndDropModeFlags mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetDragDropMode(DragAndDropModeFlags)", AS_METHODPR(UISelectable, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_dragDropMode(DragAndDropModeFlags)", AS_METHODPR(UISelectable, SetDragDropMode, (DragAndDropModeFlags), void), AS_CALL_THISCALL);
    // void UIElement::SetEditable(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetEditable(bool)", AS_METHODPR(UISelectable, SetEditable, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_editable(bool)", AS_METHODPR(UISelectable, SetEditable, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetElementEventSender(bool flag) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetElementEventSender(bool)", AS_METHODPR(UISelectable, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_elementEventSender(bool)", AS_METHODPR(UISelectable, SetElementEventSender, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnableAnchor(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetEnableAnchor(bool)", AS_METHODPR(UISelectable, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_enableAnchor(bool)", AS_METHODPR(UISelectable, SetEnableAnchor, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabled(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetEnabled(bool)", AS_METHODPR(UISelectable, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_enabled(bool)", AS_METHODPR(UISelectable, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetEnabledRecursive(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetEnabledRecursive(bool)", AS_METHODPR(UISelectable, SetEnabledRecursive, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetFixedHeight(int)", AS_METHODPR(UISelectable, SetFixedHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetFixedSize(const IntVector2&in)", AS_METHODPR(UISelectable, SetFixedSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetFixedSize(int, int)", AS_METHODPR(UISelectable, SetFixedSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetFixedWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetFixedWidth(int)", AS_METHODPR(UISelectable, SetFixedWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetFocus(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetFocus(bool)", AS_METHODPR(UISelectable, SetFocus, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_focus(bool)", AS_METHODPR(UISelectable, SetFocus, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetFocusMode(FocusMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetFocusMode(FocusMode)", AS_METHODPR(UISelectable, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_focusMode(FocusMode)", AS_METHODPR(UISelectable, SetFocusMode, (FocusMode), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(UISelectable, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(UISelectable, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetHeight(int)", AS_METHODPR(UISelectable, SetHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_height(int)", AS_METHODPR(UISelectable, SetHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetHorizontalAlignment(HorizontalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetHorizontalAlignment(HorizontalAlignment)", AS_METHODPR(UISelectable, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_horizontalAlignment(HorizontalAlignment)", AS_METHODPR(UISelectable, SetHorizontalAlignment, (HorizontalAlignment), void), AS_CALL_THISCALL);
    // void UISelectable::SetHoverColor(const Color& color) | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("UISelectable", "void SetHoverColor(const Color&in)", AS_METHODPR(UISelectable, SetHoverColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_hoverColor(const Color&in)", AS_METHODPR(UISelectable, SetHoverColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetHovering(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetHovering(bool)", AS_METHODPR(UISelectable, SetHovering, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetIndent(int indent) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetIndent(int)", AS_METHODPR(UISelectable, SetIndent, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_indent(int)", AS_METHODPR(UISelectable, SetIndent, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetIndentSpacing(int indentSpacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetIndentSpacing(int)", AS_METHODPR(UISelectable, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_indentSpacing(int)", AS_METHODPR(UISelectable, SetIndentSpacing, (int), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void SetInstanceDefault(bool)", AS_METHODPR(UISelectable, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(UISelectable, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void UIElement::SetInternal(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetInternal(bool)", AS_METHODPR(UISelectable, SetInternal, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_internal(bool)", AS_METHODPR(UISelectable, SetInternal, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetLayout(LayoutMode mode, int spacing=0, const IntRect& border=IntRect::ZERO) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetLayout(LayoutMode, int = 0, const IntRect&in = IntRect::ZERO)", AS_METHODPR(UISelectable, SetLayout, (LayoutMode, int, const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutBorder(const IntRect& border) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetLayoutBorder(const IntRect&in)", AS_METHODPR(UISelectable, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_layoutBorder(const IntRect&in)", AS_METHODPR(UISelectable, SetLayoutBorder, (const IntRect&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutFlexScale(const Vector2& scale) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetLayoutFlexScale(const Vector2&in)", AS_METHODPR(UISelectable, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_layoutFlexScale(const Vector2&in)", AS_METHODPR(UISelectable, SetLayoutFlexScale, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutMode(LayoutMode mode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetLayoutMode(LayoutMode)", AS_METHODPR(UISelectable, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_layoutMode(LayoutMode)", AS_METHODPR(UISelectable, SetLayoutMode, (LayoutMode), void), AS_CALL_THISCALL);
    // void UIElement::SetLayoutSpacing(int spacing) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetLayoutSpacing(int)", AS_METHODPR(UISelectable, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_layoutSpacing(int)", AS_METHODPR(UISelectable, SetLayoutSpacing, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxAnchor(const Vector2&in)", AS_METHODPR(UISelectable, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_maxAnchor(const Vector2&in)", AS_METHODPR(UISelectable, SetMaxAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxAnchor(float, float)", AS_METHODPR(UISelectable, SetMaxAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxHeight(int)", AS_METHODPR(UISelectable, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_maxHeight(int)", AS_METHODPR(UISelectable, SetMaxHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxOffset(const IntVector2&in)", AS_METHODPR(UISelectable, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_maxOffset(const IntVector2&in)", AS_METHODPR(UISelectable, SetMaxOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(const IntVector2& maxSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxSize(const IntVector2&in)", AS_METHODPR(UISelectable, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_maxSize(const IntVector2&in)", AS_METHODPR(UISelectable, SetMaxSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxSize(int, int)", AS_METHODPR(UISelectable, SetMaxSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMaxWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMaxWidth(int)", AS_METHODPR(UISelectable, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_maxWidth(int)", AS_METHODPR(UISelectable, SetMaxWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(const Vector2& anchor) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinAnchor(const Vector2&in)", AS_METHODPR(UISelectable, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_minAnchor(const Vector2&in)", AS_METHODPR(UISelectable, SetMinAnchor, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinAnchor(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinAnchor(float, float)", AS_METHODPR(UISelectable, SetMinAnchor, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetMinHeight(int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinHeight(int)", AS_METHODPR(UISelectable, SetMinHeight, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_minHeight(int)", AS_METHODPR(UISelectable, SetMinHeight, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinOffset(const IntVector2& offset) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinOffset(const IntVector2&in)", AS_METHODPR(UISelectable, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_minOffset(const IntVector2&in)", AS_METHODPR(UISelectable, SetMinOffset, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(const IntVector2& minSize) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinSize(const IntVector2&in)", AS_METHODPR(UISelectable, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_minSize(const IntVector2&in)", AS_METHODPR(UISelectable, SetMinSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetMinSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinSize(int, int)", AS_METHODPR(UISelectable, SetMinSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetMinWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetMinWidth(int)", AS_METHODPR(UISelectable, SetMinWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_minWidth(int)", AS_METHODPR(UISelectable, SetMinWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetName(const String& name) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetName(const String&in)", AS_METHODPR(UISelectable, SetName, (const String&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_name(const String&in)", AS_METHODPR(UISelectable, SetName, (const String&), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(UISelectable, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(UISelectable, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UISelectable", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(UISelectable, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void UIElement::SetOpacity(float opacity) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetOpacity(float)", AS_METHODPR(UISelectable, SetOpacity, (float), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_opacity(float)", AS_METHODPR(UISelectable, SetOpacity, (float), void), AS_CALL_THISCALL);
    // void UIElement::SetParent(UIElement* parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetParent(UIElement@+, uint = M_MAX_UNSIGNED)", AS_METHODPR(UISelectable, SetParent, (UIElement*, unsigned), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(const Vector2& pivot) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetPivot(const Vector2&in)", AS_METHODPR(UISelectable, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_pivot(const Vector2&in)", AS_METHODPR(UISelectable, SetPivot, (const Vector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPivot(float x, float y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetPivot(float, float)", AS_METHODPR(UISelectable, SetPivot, (float, float), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(const IntVector2& position) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetPosition(const IntVector2&in)", AS_METHODPR(UISelectable, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_position(const IntVector2&in)", AS_METHODPR(UISelectable, SetPosition, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetPosition(int x, int y) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetPosition(int, int)", AS_METHODPR(UISelectable, SetPosition, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetPriority(int priority) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetPriority(int)", AS_METHODPR(UISelectable, SetPriority, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_priority(int)", AS_METHODPR(UISelectable, SetPriority, (int), void), AS_CALL_THISCALL);
    // void UIElement::SetRenderTexture(Texture2D* texture) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetRenderTexture(Texture2D@+)", AS_METHODPR(UISelectable, SetRenderTexture, (Texture2D*), void), AS_CALL_THISCALL);
    // void UIElement::SetSelected(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetSelected(bool)", AS_METHODPR(UISelectable, SetSelected, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_selected(bool)", AS_METHODPR(UISelectable, SetSelected, (bool), void), AS_CALL_THISCALL);
    // void UISelectable::SetSelectionColor(const Color& color) | File: ../UI/UISelectable.h
    engine->RegisterObjectMethod("UISelectable", "void SetSelectionColor(const Color&in)", AS_METHODPR(UISelectable, SetSelectionColor, (const Color&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_selectionColor(const Color&in)", AS_METHODPR(UISelectable, SetSelectionColor, (const Color&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(const IntVector2& size) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetSize(const IntVector2&in)", AS_METHODPR(UISelectable, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_size(const IntVector2&in)", AS_METHODPR(UISelectable, SetSize, (const IntVector2&), void), AS_CALL_THISCALL);
    // void UIElement::SetSize(int width, int height) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetSize(int, int)", AS_METHODPR(UISelectable, SetSize, (int, int), void), AS_CALL_THISCALL);
    // void UIElement::SetSortChildren(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetSortChildren(bool)", AS_METHODPR(UISelectable, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_sortChildren(bool)", AS_METHODPR(UISelectable, SetSortChildren, (bool), void), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const String& styleName, XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool SetStyle(const String&in, XMLFile@+ = null)", AS_METHODPR(UISelectable, SetStyle, (const String&, XMLFile*), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyle(const XMLElement& element) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool SetStyle(const XMLElement&in)", AS_METHODPR(UISelectable, SetStyle, (const XMLElement&), bool), AS_CALL_THISCALL);
    // bool UIElement::SetStyleAuto(XMLFile* file=nullptr) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "bool SetStyleAuto(XMLFile@+ = null)", AS_METHODPR(UISelectable, SetStyleAuto, (XMLFile*), bool), AS_CALL_THISCALL);
    // void UIElement::SetTags(const StringVector& tags) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetTags(Array<String>@+)", AS_FUNCTION_OBJFIRST(UISelectable_SetTags_StringVector), AS_CALL_CDECL_OBJFIRST);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void SetTemporary(bool)", AS_METHODPR(UISelectable, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_temporary(bool)", AS_METHODPR(UISelectable, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetTraversalMode(TraversalMode traversalMode) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetTraversalMode(TraversalMode)", AS_METHODPR(UISelectable, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_traversalMode(TraversalMode)", AS_METHODPR(UISelectable, SetTraversalMode, (TraversalMode), void), AS_CALL_THISCALL);
    // void UIElement::SetUseDerivedOpacity(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetUseDerivedOpacity(bool)", AS_METHODPR(UISelectable, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_useDerivedOpacity(bool)", AS_METHODPR(UISelectable, SetUseDerivedOpacity, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetVar(StringHash key, const Variant& value) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetVar(StringHash, const Variant&in)", AS_METHODPR(UISelectable, SetVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void UIElement::SetVerticalAlignment(VerticalAlignment align) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetVerticalAlignment(VerticalAlignment)", AS_METHODPR(UISelectable, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_verticalAlignment(VerticalAlignment)", AS_METHODPR(UISelectable, SetVerticalAlignment, (VerticalAlignment), void), AS_CALL_THISCALL);
    // void UIElement::SetVisible(bool enable) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetVisible(bool)", AS_METHODPR(UISelectable, SetVisible, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_visible(bool)", AS_METHODPR(UISelectable, SetVisible, (bool), void), AS_CALL_THISCALL);
    // void UIElement::SetWidth(int width) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SetWidth(int)", AS_METHODPR(UISelectable, SetWidth, (int), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "void set_width(int)", AS_METHODPR(UISelectable, SetWidth, (int), void), AS_CALL_THISCALL);
    // void UIElement::SortChildren() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void SortChildren()", AS_METHODPR(UISelectable, SortChildren, (), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void UnsubscribeFromAllEvents()", AS_METHODPR(UISelectable, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(UISelectable_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(UISelectable, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(UISelectable, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UISelectable", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(UISelectable, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // virtual void UIElement::Update(float timeStep) | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void Update(float)", AS_METHODPR(UISelectable, Update, (float), void), AS_CALL_THISCALL);
    // void UIElement::UpdateLayout() | File: ../UI/UIElement.h
    engine->RegisterObjectMethod("UISelectable", "void UpdateLayout()", AS_METHODPR(UISelectable, UpdateLayout, (), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UISelectable", "int WeakRefs() const", AS_METHODPR(UISelectable, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UISelectable", "int get_weakRefs() const", AS_METHODPR(UISelectable, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(UISelectable, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(UISelectable, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UISelectable", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(UISelectable, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
    engine->RegisterObjectBehaviour("UnknownComponent", asBEHAVE_ADDREF, "void f()", AS_METHODPR(UnknownComponent, AddRef, (), void), AS_CALL_THISCALL);
    // void Component::AddReplicationState(ComponentReplicationState* state) | File: ../Scene/Component.h
    // Error: type "ComponentReplicationState*" can not automatically bind
    // void Serializable::AllocateNetworkState() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void AllocateNetworkState()", AS_METHODPR(UnknownComponent, AllocateNetworkState, (), void), AS_CALL_THISCALL);
    // virtual void Serializable::ApplyAttributes() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void ApplyAttributes()", AS_METHODPR(UnknownComponent, ApplyAttributes, (), void), AS_CALL_THISCALL);
    // template<typename T> T* Object::Cast() | File: ../Core/Object.h
    // Not registered because template
    // template<typename T> const T* Object::Cast() const | File: ../Core/Object.h
    // Not registered because template
    // void Component::CleanupConnection(Connection* connection) | File: ../Scene/Component.h
    // Not registered because have @manualbind mark
    // virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "void DrawDebugGeometry(DebugRenderer@+, bool)", AS_METHODPR(UnknownComponent, DrawDebugGeometry, (DebugRenderer*, bool), void), AS_CALL_THISCALL);
    // bool Animatable::GetAnimationEnabled() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool GetAnimationEnabled() const", AS_METHODPR(UnknownComponent, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "bool get_animationEnabled() const", AS_METHODPR(UnknownComponent, GetAnimationEnabled, () const, bool), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "Variant GetAttribute(uint) const", AS_METHODPR(UnknownComponent, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "Variant get_attributes(uint) const", AS_METHODPR(UnknownComponent, GetAttribute, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttribute(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "Variant GetAttribute(const String&in) const", AS_METHODPR(UnknownComponent, GetAttribute, (const String&) const, Variant), AS_CALL_THISCALL);
    // ValueAnimation* Animatable::GetAttributeAnimation(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "ValueAnimation@+ GetAttributeAnimation(const String&in) const", AS_METHODPR(UnknownComponent, GetAttributeAnimation, (const String&) const, ValueAnimation*), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationSpeed(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "float GetAttributeAnimationSpeed(const String&in) const", AS_METHODPR(UnknownComponent, GetAttributeAnimationSpeed, (const String&) const, float), AS_CALL_THISCALL);
    // float Animatable::GetAttributeAnimationTime(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "float GetAttributeAnimationTime(const String&in) const", AS_METHODPR(UnknownComponent, GetAttributeAnimationTime, (const String&) const, float), AS_CALL_THISCALL);
    // WrapMode Animatable::GetAttributeAnimationWrapMode(const String& name) const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "WrapMode GetAttributeAnimationWrapMode(const String&in) const", AS_METHODPR(UnknownComponent, GetAttributeAnimationWrapMode, (const String&) const, WrapMode), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(unsigned index) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "Variant GetAttributeDefault(uint) const", AS_METHODPR(UnknownComponent, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "Variant get_attributeDefaults(uint) const", AS_METHODPR(UnknownComponent, GetAttributeDefault, (unsigned) const, Variant), AS_CALL_THISCALL);
    // Variant Serializable::GetAttributeDefault(const String& name) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "Variant GetAttributeDefault(const String&in) const", AS_METHODPR(UnknownComponent, GetAttributeDefault, (const String&) const, Variant), AS_CALL_THISCALL);
    // const Vector<AttributeInfo>* UnknownComponent::GetAttributes() const override | File: ../Scene/UnknownComponent.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // const PODVector<unsigned char>& UnknownComponent::GetBinaryAttributes() const | File: ../Scene/UnknownComponent.h
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // bool Object::GetBlockEvents() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "bool GetBlockEvents() const", AS_METHODPR(UnknownComponent, GetBlockEvents, () const, bool), AS_CALL_THISCALL);
    // const String& Object::GetCategory() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "const String& GetCategory() const", AS_METHODPR(UnknownComponent, GetCategory, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "const String& get_category() const", AS_METHODPR(UnknownComponent, GetCategory, () const, const String&), AS_CALL_THISCALL);
    // Component* Component::GetComponent(StringHash type) const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "Component@+ GetComponent(StringHash) const", AS_METHODPR(UnknownComponent, GetComponent, (StringHash) const, Component*), AS_CALL_THISCALL);
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
    engine->RegisterObjectMethod("UnknownComponent", "VariantMap& GetEventDataMap() const", AS_METHODPR(UnknownComponent, GetEventDataMap, () const, VariantMap&), AS_CALL_THISCALL);
    // EventHandler* Object::GetEventHandler() const | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // Object* Object::GetEventSender() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "Object@+ GetEventSender() const", AS_METHODPR(UnknownComponent, GetEventSender, () const, Object*), AS_CALL_THISCALL);
    // const Variant& Object::GetGlobalVar(StringHash key) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "const Variant& GetGlobalVar(StringHash) const", AS_METHODPR(UnknownComponent, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "const Variant& get_globalVar(StringHash) const", AS_METHODPR(UnknownComponent, GetGlobalVar, (StringHash) const, const Variant&), AS_CALL_THISCALL);
    // const VariantMap& Object::GetGlobalVars() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "const VariantMap& GetGlobalVars() const", AS_METHODPR(UnknownComponent, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "const VariantMap& get_globalVars() const", AS_METHODPR(UnknownComponent, GetGlobalVars, () const, const VariantMap&), AS_CALL_THISCALL);
    // unsigned Component::GetID() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "uint GetID() const", AS_METHODPR(UnknownComponent, GetID, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "uint get_id() const", AS_METHODPR(UnknownComponent, GetID, () const, unsigned), AS_CALL_THISCALL);
    // bool Serializable::GetInterceptNetworkUpdate(const String& attributeName) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool GetInterceptNetworkUpdate(const String&in) const", AS_METHODPR(UnknownComponent, GetInterceptNetworkUpdate, (const String&) const, bool), AS_CALL_THISCALL);
    // virtual const Vector<AttributeInfo>* Serializable::GetNetworkAttributes() const | File: ../Scene/Serializable.h
    // Error: type "const Vector<AttributeInfo>*" can not automatically bind
    // NetworkState* Serializable::GetNetworkState() const | File: ../Scene/Serializable.h
    // Error: type "NetworkState*" can not automatically bind
    // Node* Component::GetNode() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "Node@+ GetNode() const", AS_METHODPR(UnknownComponent, GetNode, () const, Node*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "Node@+ get_node() const", AS_METHODPR(UnknownComponent, GetNode, () const, Node*), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "uint GetNumAttributes() const", AS_METHODPR(UnknownComponent, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "uint get_numAttributes() const", AS_METHODPR(UnknownComponent, GetNumAttributes, () const, unsigned), AS_CALL_THISCALL);
    // unsigned Serializable::GetNumNetworkAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "uint GetNumNetworkAttributes() const", AS_METHODPR(UnknownComponent, GetNumNetworkAttributes, () const, unsigned), AS_CALL_THISCALL);
    // ObjectAnimation* Animatable::GetObjectAnimation() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "ObjectAnimation@+ GetObjectAnimation() const", AS_METHODPR(UnknownComponent, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "ObjectAnimation@+ get_objectAnimation() const", AS_METHODPR(UnknownComponent, GetObjectAnimation, () const, ObjectAnimation*), AS_CALL_THISCALL);
    // ResourceRef Animatable::GetObjectAnimationAttr() const | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "ResourceRef GetObjectAnimationAttr() const", AS_METHODPR(UnknownComponent, GetObjectAnimationAttr, () const, ResourceRef), AS_CALL_THISCALL);
    // Scene* Component::GetScene() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "Scene@+ GetScene() const", AS_METHODPR(UnknownComponent, GetScene, () const, Scene*), AS_CALL_THISCALL);
    // Object* Object::GetSubsystem(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "Object@+ GetSubsystem(StringHash) const", AS_METHODPR(UnknownComponent, GetSubsystem, (StringHash) const, Object*), AS_CALL_THISCALL);
    // template<class T> T* Object::GetSubsystem() const | File: ../Core/Object.h
    // Not registered because template
    // StringHash UnknownComponent::GetType() const override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "StringHash GetType() const", AS_METHODPR(UnknownComponent, GetType, () const, StringHash), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "StringHash get_type() const", AS_METHODPR(UnknownComponent, GetType, () const, StringHash), AS_CALL_THISCALL);
    // virtual const TypeInfo* Object::GetTypeInfo() const =0 | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // static const TypeInfo* Object::GetTypeInfoStatic() | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // const String& UnknownComponent::GetTypeName() const override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "const String& GetTypeName() const", AS_METHODPR(UnknownComponent, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "const String& get_typeName() const", AS_METHODPR(UnknownComponent, GetTypeName, () const, const String&), AS_CALL_THISCALL);
    // static const Urho3D::String& UnknownComponent::GetTypeNameStatic() | File: ../Scene/UnknownComponent.h
    // Error: type "const Urho3D::String&" can not automatically bind
    // static Urho3D::StringHash UnknownComponent::GetTypeStatic() | File: ../Scene/UnknownComponent.h
    // Error: type "Urho3D::StringHash" can not automatically bind
    // bool UnknownComponent::GetUseXML() const | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool GetUseXML() const", AS_METHODPR(UnknownComponent, GetUseXML, () const, bool), AS_CALL_THISCALL);
    // const Vector<String>& UnknownComponent::GetXMLAttributes() const | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "Array<String>@ GetXMLAttributes() const", AS_FUNCTION_OBJFIRST(UnknownComponent_GetXMLAttributes_void), AS_CALL_CDECL_OBJFIRST);
    // bool Object::HasEventHandlers() const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "bool HasEventHandlers() const", AS_METHODPR(UnknownComponent, HasEventHandlers, () const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "bool HasSubscribedToEvent(StringHash) const", AS_METHODPR(UnknownComponent, HasSubscribedToEvent, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::HasSubscribedToEvent(Object* sender, StringHash eventType) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "bool HasSubscribedToEvent(Object@+, StringHash) const", AS_METHODPR(UnknownComponent, HasSubscribedToEvent, (Object*, StringHash) const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabled() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "bool IsEnabled() const", AS_METHODPR(UnknownComponent, IsEnabled, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "bool get_enabled() const", AS_METHODPR(UnknownComponent, IsEnabled, () const, bool), AS_CALL_THISCALL);
    // bool Component::IsEnabledEffective() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "bool IsEnabledEffective() const", AS_METHODPR(UnknownComponent, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "bool get_enabledEffective() const", AS_METHODPR(UnknownComponent, IsEnabledEffective, () const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(StringHash type) const | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "bool IsInstanceOf(StringHash) const", AS_METHODPR(UnknownComponent, IsInstanceOf, (StringHash) const, bool), AS_CALL_THISCALL);
    // bool Object::IsInstanceOf(const TypeInfo* typeInfo) const | File: ../Core/Object.h
    // Error: type "TypeInfo" can not automatically bind bacause have @nobind mark
    // template<typename T> bool Object::IsInstanceOf() const | File: ../Core/Object.h
    // Not registered because template
    // bool Component::IsReplicated() const | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "bool IsReplicated() const", AS_METHODPR(UnknownComponent, IsReplicated, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "bool get_replicated() const", AS_METHODPR(UnknownComponent, IsReplicated, () const, bool), AS_CALL_THISCALL);
    // bool Serializable::IsTemporary() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool IsTemporary() const", AS_METHODPR(UnknownComponent, IsTemporary, () const, bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "bool get_temporary() const", AS_METHODPR(UnknownComponent, IsTemporary, () const, bool), AS_CALL_THISCALL);
    // bool UnknownComponent::Load(Deserializer& source) override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool Load(Deserializer&)", AS_METHODPR(UnknownComponent, Load, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool UnknownComponent::LoadJSON(const JSONValue& source) override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool LoadJSON(const JSONValue&in)", AS_METHODPR(UnknownComponent, LoadJSON, (const JSONValue&), bool), AS_CALL_THISCALL);
    // bool UnknownComponent::LoadXML(const XMLElement& source) override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool LoadXML(const XMLElement&in)", AS_METHODPR(UnknownComponent, LoadXML, (const XMLElement&), bool), AS_CALL_THISCALL);
    // void Component::MarkNetworkUpdate() override | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "void MarkNetworkUpdate()", AS_METHODPR(UnknownComponent, MarkNetworkUpdate, (), void), AS_CALL_THISCALL);
    // virtual void Object::OnEvent(Object* sender, StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void OnEvent(Object@+, StringHash, VariantMap&)", AS_METHODPR(UnknownComponent, OnEvent, (Object*, StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // virtual void Serializable::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void OnGetAttribute(const AttributeInfo&in, Variant&) const", AS_METHODPR(UnknownComponent, OnGetAttribute, (const AttributeInfo&, Variant&) const, void), AS_CALL_THISCALL);
    // virtual void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& src) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void OnSetAttribute(const AttributeInfo&in, const Variant&in)", AS_METHODPR(UnknownComponent, OnSetAttribute, (const AttributeInfo&, const Variant&), void), AS_CALL_THISCALL);
    // virtual void Component::OnSetEnabled() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "void OnSetEnabled()", AS_METHODPR(UnknownComponent, OnSetEnabled, (), void), AS_CALL_THISCALL);
    // void Component::PrepareNetworkUpdate() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "void PrepareNetworkUpdate()", AS_METHODPR(UnknownComponent, PrepareNetworkUpdate, (), void), AS_CALL_THISCALL);
    // bool Serializable::ReadDeltaUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool ReadDeltaUpdate(Deserializer&)", AS_METHODPR(UnknownComponent, ReadDeltaUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // bool Serializable::ReadLatestDataUpdate(Deserializer& source) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool ReadLatestDataUpdate(Deserializer&)", AS_METHODPR(UnknownComponent, ReadLatestDataUpdate, (Deserializer&), bool), AS_CALL_THISCALL);
    // RefCount* RefCounted::RefCountPtr() | File: ../Container/RefCounted.h
    // Error: type "RefCount*" can not automatically bind
    // int RefCounted::Refs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UnknownComponent", "int Refs() const", AS_METHODPR(UnknownComponent, Refs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "int get_refs() const", AS_METHODPR(UnknownComponent, Refs, () const, int), AS_CALL_THISCALL);
    // static void UnknownComponent::RegisterObject(Context* context) | File: ../Scene/UnknownComponent.h
    // Not registered because have @nobind mark
    // void RefCounted::ReleaseRef() | File: ../Container/RefCounted.h
    engine->RegisterObjectBehaviour("UnknownComponent", asBEHAVE_RELEASE, "void f()", AS_METHODPR(UnknownComponent, ReleaseRef, (), void), AS_CALL_THISCALL);
    // void Component::Remove() | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "void Remove()", AS_METHODPR(UnknownComponent, Remove, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveAttributeAnimation(const String& name) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void RemoveAttributeAnimation(const String&in)", AS_METHODPR(UnknownComponent, RemoveAttributeAnimation, (const String&), void), AS_CALL_THISCALL);
    // void Serializable::RemoveInstanceDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void RemoveInstanceDefault()", AS_METHODPR(UnknownComponent, RemoveInstanceDefault, (), void), AS_CALL_THISCALL);
    // void Animatable::RemoveObjectAnimation() | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void RemoveObjectAnimation()", AS_METHODPR(UnknownComponent, RemoveObjectAnimation, (), void), AS_CALL_THISCALL);
    // void Serializable::ResetToDefault() | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void ResetToDefault()", AS_METHODPR(UnknownComponent, ResetToDefault, (), void), AS_CALL_THISCALL);
    // bool UnknownComponent::Save(Serializer& dest) const override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool Save(Serializer&) const", AS_METHODPR(UnknownComponent, Save, (Serializer&) const, bool), AS_CALL_THISCALL);
    // virtual bool Serializable::SaveDefaultAttributes() const | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool SaveDefaultAttributes() const", AS_METHODPR(UnknownComponent, SaveDefaultAttributes, () const, bool), AS_CALL_THISCALL);
    // bool UnknownComponent::SaveJSON(JSONValue& dest) const override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool SaveJSON(JSONValue&) const", AS_METHODPR(UnknownComponent, SaveJSON, (JSONValue&) const, bool), AS_CALL_THISCALL);
    // bool UnknownComponent::SaveXML(XMLElement& dest) const override | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "bool SaveXML(XMLElement&) const", AS_METHODPR(UnknownComponent, SaveXML, (XMLElement&) const, bool), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void SendEvent(StringHash)", AS_METHODPR(UnknownComponent, SendEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::SendEvent(StringHash eventType, VariantMap& eventData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void SendEvent(StringHash, VariantMap&)", AS_METHODPR(UnknownComponent, SendEvent, (StringHash, VariantMap&), void), AS_CALL_THISCALL);
    // template<typename... Args> void Object::SendEvent(StringHash eventType, Args... args) | File: ../Core/Object.h
    // Not registered because template
    // void Animatable::SetAnimationEnabled(bool enable) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetAnimationEnabled(bool)", AS_METHODPR(UnknownComponent, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "void set_animationEnabled(bool)", AS_METHODPR(UnknownComponent, SetAnimationEnabled, (bool), void), AS_CALL_THISCALL);
    // void Animatable::SetAnimationTime(float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetAnimationTime(float)", AS_METHODPR(UnknownComponent, SetAnimationTime, (float), void), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(unsigned index, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool SetAttribute(uint, const Variant&in)", AS_METHODPR(UnknownComponent, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "bool set_attributes(uint, const Variant&in)", AS_METHODPR(UnknownComponent, SetAttribute, (unsigned, const Variant&), bool), AS_CALL_THISCALL);
    // bool Serializable::SetAttribute(const String& name, const Variant& value) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "bool SetAttribute(const String&in, const Variant&in)", AS_METHODPR(UnknownComponent, SetAttribute, (const String&, const Variant&), bool), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode=WM_LOOP, float speed=1.0f) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetAttributeAnimation(const String&in, ValueAnimation@+, WrapMode = WM_LOOP, float = 1.0f)", AS_METHODPR(UnknownComponent, SetAttributeAnimation, (const String&, ValueAnimation*, WrapMode, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationSpeed(const String& name, float speed) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetAttributeAnimationSpeed(const String&in, float)", AS_METHODPR(UnknownComponent, SetAttributeAnimationSpeed, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationTime(const String& name, float time) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetAttributeAnimationTime(const String&in, float)", AS_METHODPR(UnknownComponent, SetAttributeAnimationTime, (const String&, float), void), AS_CALL_THISCALL);
    // void Animatable::SetAttributeAnimationWrapMode(const String& name, WrapMode wrapMode) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetAttributeAnimationWrapMode(const String&in, WrapMode)", AS_METHODPR(UnknownComponent, SetAttributeAnimationWrapMode, (const String&, WrapMode), void), AS_CALL_THISCALL);
    // void Object::SetBlockEvents(bool block) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetBlockEvents(bool)", AS_METHODPR(UnknownComponent, SetBlockEvents, (bool), void), AS_CALL_THISCALL);
    // void Component::SetEnabled(bool enable) | File: ../Scene/Component.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetEnabled(bool)", AS_METHODPR(UnknownComponent, SetEnabled, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "void set_enabled(bool)", AS_METHODPR(UnknownComponent, SetEnabled, (bool), void), AS_CALL_THISCALL);
    // void Object::SetGlobalVar(StringHash key, const Variant& value) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetGlobalVar(StringHash, const Variant&in)", AS_METHODPR(UnknownComponent, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "void set_globalVar(StringHash, const Variant&in)", AS_METHODPR(UnknownComponent, SetGlobalVar, (StringHash, const Variant&), void), AS_CALL_THISCALL);
    // void Serializable::SetInstanceDefault(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetInstanceDefault(bool)", AS_METHODPR(UnknownComponent, SetInstanceDefault, (bool), void), AS_CALL_THISCALL);
    // void Serializable::SetInterceptNetworkUpdate(const String& attributeName, bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetInterceptNetworkUpdate(const String&in, bool)", AS_METHODPR(UnknownComponent, SetInterceptNetworkUpdate, (const String&, bool), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimation(ObjectAnimation* objectAnimation) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetObjectAnimation(ObjectAnimation@+)", AS_METHODPR(UnknownComponent, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "void set_objectAnimation(ObjectAnimation@+)", AS_METHODPR(UnknownComponent, SetObjectAnimation, (ObjectAnimation*), void), AS_CALL_THISCALL);
    // void Animatable::SetObjectAnimationAttr(const ResourceRef& value) | File: ../Scene/Animatable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetObjectAnimationAttr(const ResourceRef&in)", AS_METHODPR(UnknownComponent, SetObjectAnimationAttr, (const ResourceRef&), void), AS_CALL_THISCALL);
    // void Serializable::SetTemporary(bool enable) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetTemporary(bool)", AS_METHODPR(UnknownComponent, SetTemporary, (bool), void), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "void set_temporary(bool)", AS_METHODPR(UnknownComponent, SetTemporary, (bool), void), AS_CALL_THISCALL);
    // void UnknownComponent::SetType(StringHash typeHash) | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetType(StringHash)", AS_METHODPR(UnknownComponent, SetType, (StringHash), void), AS_CALL_THISCALL);
    // void UnknownComponent::SetTypeName(const String& typeName) | File: ../Scene/UnknownComponent.h
    engine->RegisterObjectMethod("UnknownComponent", "void SetTypeName(const String&in)", AS_METHODPR(UnknownComponent, SetTypeName, (const String&), void), AS_CALL_THISCALL);
    // void Object::SubscribeToEvent(StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, EventHandler* handler) | File: ../Core/Object.h
    // Error: type "EventHandler*" can not automatically bind
    // void Object::SubscribeToEvent(StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::SubscribeToEvent(Object* sender, StringHash eventType, const std::function<void(StringHash, VariantMap&)>& function, void* userData=nullptr) | File: ../Core/Object.h
    // Error: type "const std::function<void(StringHash, VariantMap&)>&" can not automatically bind
    // void Object::UnsubscribeFromAllEvents() | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void UnsubscribeFromAllEvents()", AS_METHODPR(UnknownComponent, UnsubscribeFromAllEvents, (), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromAllEventsExcept(const PODVector<StringHash>& exceptions, bool onlyUserData) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void UnsubscribeFromAllEventsExcept(Array<StringHash>@+, bool)", AS_FUNCTION_OBJFIRST(UnknownComponent_UnsubscribeFromAllEventsExcept_PODVectorStringHash_bool), AS_CALL_CDECL_OBJFIRST);
    // void Object::UnsubscribeFromEvent(StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void UnsubscribeFromEvent(StringHash)", AS_METHODPR(UnknownComponent, UnsubscribeFromEvent, (StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvent(Object* sender, StringHash eventType) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void UnsubscribeFromEvent(Object@+, StringHash)", AS_METHODPR(UnknownComponent, UnsubscribeFromEvent, (Object*, StringHash), void), AS_CALL_THISCALL);
    // void Object::UnsubscribeFromEvents(Object* sender) | File: ../Core/Object.h
    engine->RegisterObjectMethod("UnknownComponent", "void UnsubscribeFromEvents(Object@+)", AS_METHODPR(UnknownComponent, UnsubscribeFromEvents, (Object*), void), AS_CALL_THISCALL);
    // int RefCounted::WeakRefs() const | File: ../Container/RefCounted.h
    engine->RegisterObjectMethod("UnknownComponent", "int WeakRefs() const", AS_METHODPR(UnknownComponent, WeakRefs, () const, int), AS_CALL_THISCALL);
    engine->RegisterObjectMethod("UnknownComponent", "int get_weakRefs() const", AS_METHODPR(UnknownComponent, WeakRefs, () const, int), AS_CALL_THISCALL);
    // void Serializable::WriteDeltaUpdate(Serializer& dest, const DirtyBits& attributeBits, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void WriteDeltaUpdate(Serializer&, const DirtyBits&in, uint8)", AS_METHODPR(UnknownComponent, WriteDeltaUpdate, (Serializer&, const DirtyBits&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteInitialDeltaUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void WriteInitialDeltaUpdate(Serializer&, uint8)", AS_METHODPR(UnknownComponent, WriteInitialDeltaUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
    // void Serializable::WriteLatestDataUpdate(Serializer& dest, unsigned char timeStamp) | File: ../Scene/Serializable.h
    engine->RegisterObjectMethod("UnknownComponent", "void WriteLatestDataUpdate(Serializer&, uint8)", AS_METHODPR(UnknownComponent, WriteLatestDataUpdate, (Serializer&, unsigned char), void), AS_CALL_THISCALL);
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
