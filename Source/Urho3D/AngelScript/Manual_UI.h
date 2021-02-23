//
// Copyright (c) 2008-2020 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "../UI/Font.h"
#include "../UI/ListView.h"
#include "../UI/DropDownList.h"
#include "../UI/FileSelector.h"
#include "../UI/UI.h"

namespace Urho3D
{

// bool Font::SaveXML(Serializer &dest, int pointSize, bool usedGlyphs=false, const String &indentation="\t") | File: ../UI/Font.h
bool FontSaveXMLVectorBuffer(VectorBuffer& buffer, int pointSize, bool usedGlyphs, const String& indentation, Font* ptr);
// bool Font::SaveXML(Serializer &dest, int pointSize, bool usedGlyphs=false, const String &indentation="\t") | File: ../UI/Font.h
bool FontSaveXML(const String& fileName, int pointSize, bool usedGlyphs, const String& indentation, Font* ptr);
// bool Font::SaveXML(Serializer &dest, int pointSize, bool usedGlyphs=false, const String &indentation="\t") | File: ../UI/Font.h
bool FontSaveXMLFile(File* file, int pointSize, bool usedGlyphs, const String& indentation, Font* ptr);

#define REGISTER_MANUAL_PART_Font(T, className) \
    /* bool Font::SaveXML(Serializer &dest, int pointSize, bool usedGlyphs=false, const String &indentation="\t") | File: ../UI/Font.h */ \
    engine->RegisterObjectMethod(className, "bool SaveXML(File@+, int, bool usedGlyphs = false, const String&in indentation = \"\t\")", AS_FUNCTION_OBJLAST(FontSaveXMLFile), AS_CALL_CDECL_OBJLAST); \
    /* bool Font::SaveXML(Serializer &dest, int pointSize, bool usedGlyphs=false, const String &indentation="\t") | File: ../UI/Font.h */ \
    engine->RegisterObjectMethod(className, "bool SaveXML(VectorBuffer&, int, bool usedGlyphs = false, const String&in indentation = \"\t\")", AS_FUNCTION_OBJLAST(FontSaveXMLVectorBuffer), AS_CALL_CDECL_OBJLAST); \
    /* bool Font::SaveXML(Serializer &dest, int pointSize, bool usedGlyphs=false, const String &indentation="\t") | File: ../UI/Font.h */ \
    engine->RegisterObjectMethod(className, "bool SaveXML(const String&in, int, bool usedGlyphs = false, const String&in indentation = \"\t\")", AS_FUNCTION_OBJLAST(FontSaveXML), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// bool UIElement::LoadXML(Deserializer &source) | File: ../UI/UIElement.h
bool UIElementLoadXML(File* file, UIElement* ptr);
// bool UIElement::LoadXML(Deserializer &source) | File: ../UI/UIElement.h
bool UIElementLoadXMLVectorBuffer(VectorBuffer& buffer, UIElement* ptr);
// bool UIElement::LoadXML(Deserializer &source) | File: ../UI/UIElement.h
bool UIElementLoadXML(XMLFile* file, XMLFile* styleFile, UIElement* ptr);
// virtual UIElement* UIElement::LoadChildXML(const XMLElement &childElem, XMLFile *styleFile) | File: ../UI/UIElement.h
UIElement* UIElementLoadChildXML(XMLFile* file, XMLFile* styleFile, UIElement* ptr);
// bool UIElement::SaveXML(Serializer &dest, const String &indentation="\t") const | File: ../UI/UIElement.h
bool UIElementSaveXML(File* file, const String& indentation, UIElement* ptr);
// bool UIElement::SaveXML(Serializer &dest, const String &indentation="\t") const | File: ../UI/UIElement.h
bool UIElementSaveXMLVectorBuffer(VectorBuffer& buffer, const String& indentation, UIElement* ptr);
// void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
void UIElementRemoveChild(unsigned index, UIElement* ptr);
// bool UIElement::SetStyle(const String &styleName, XMLFile *file=nullptr) | File: ../UI/UIElement.h
void UIElementSetStyle(const String& styleName, UIElement* ptr);
// unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
unsigned UIElementGetNumChildrenNonRecursive(UIElement* ptr);
// unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
unsigned UIElementGetNumChildrenRecursive(UIElement* ptr);
// void UIElement::SetParent(UIElement *parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
void UIElementSetParent(UIElement* parent, UIElement* ptr);
// XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
XMLFile* UIElementGetDefaultStyle(UIElement* ptr);
// const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
VariantMap& UIElementGetVars(UIElement* ptr);

// TODO: Check LoadXML 3 versions and SaveXML 3 versions

#define REGISTER_MANUAL_PART_UIElement(T, className) \
    RegisterNamedObjectConstructor<T>(engine, className); \
    /* bool UIElement::LoadXML(Deserializer &source) | File: ../UI/UIElement.h */ \
    /*engine->RegisterObjectMethod(className, "bool LoadXML(File@+)", AS_FUNCTION_OBJLAST(UIElementLoadXML), AS_CALL_CDECL_OBJLAST); */\
    /* bool UIElement::LoadXML(Deserializer &source) | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "bool LoadXML(VectorBuffer&)", AS_FUNCTION_OBJLAST(UIElementLoadXMLVectorBuffer), AS_CALL_CDECL_OBJLAST); \
    /* bool UIElement::LoadXML(Deserializer &source) | File: ../UI/UIElement.h */ \
    /*engine->RegisterObjectMethod(className, "bool LoadXML(XMLFile@+, XMLFile@+)", AS_FUNCTION_OBJLAST(UIElementLoadXML), AS_CALL_CDECL_OBJLAST); */\
    /* virtual UIElement* UIElement::LoadChildXML(const XMLElement &childElem, XMLFile *styleFile) | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "UIElement@+ LoadChildXML(XMLFile@+, XMLFile@+)", AS_FUNCTION_OBJLAST(UIElementLoadChildXML), AS_CALL_CDECL_OBJLAST); \
    /* bool UIElement::SaveXML(Serializer &dest, const String &indentation="\t") const | File: ../UI/UIElement.h */ \
    /*engine->RegisterObjectMethod(className, "bool SaveXML(File@+, const String&in indentation = \"\t\")", AS_FUNCTION_OBJLAST(UIElementSaveXML), AS_CALL_CDECL_OBJLAST); */\
    /* bool UIElement::SaveXML(Serializer &dest, const String &indentation="\t") const | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "bool SaveXML(VectorBuffer&, const String&in indentation = \"\t\")", AS_FUNCTION_OBJLAST(UIElementSaveXMLVectorBuffer), AS_CALL_CDECL_OBJLAST); \
    /* void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "void RemoveChild(uint)", AS_FUNCTION_OBJLAST(UIElementRemoveChild), AS_CALL_CDECL_OBJLAST); \
    /* bool UIElement::SetStyle(const String &styleName, XMLFile *file=nullptr) | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "void set_style(const String&in)", AS_FUNCTION_OBJLAST(UIElementSetStyle), AS_CALL_CDECL_OBJLAST); \
    /* unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "uint get_numChildren() const", AS_FUNCTION_OBJLAST(UIElementGetNumChildrenNonRecursive), AS_CALL_CDECL_OBJLAST); \
    /* unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "uint get_numAllChildren() const", AS_FUNCTION_OBJLAST(UIElementGetNumChildrenRecursive), AS_CALL_CDECL_OBJLAST); \
    /* void UIElement::SetParent(UIElement *parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "void set_parent(UIElement@+)", AS_FUNCTION_OBJLAST(UIElementSetParent), AS_CALL_CDECL_OBJLAST); \
    /* XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "XMLFile@+ get_defaultStyle() const", AS_FUNCTION_OBJLAST(UIElementGetDefaultStyle), AS_CALL_CDECL_OBJLAST); \
    /* const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "VariantMap& get_vars()", AS_FUNCTION_OBJLAST(UIElementGetVars), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// SharedPtr<UIElement> UI::LoadLayout(Deserializer &source, XMLFile *styleFile=nullptr) | File: ../UI/UI.h
UIElement* UILoadLayoutFromFile(File* file, UI* ptr);
// SharedPtr<UIElement> UI::LoadLayout(Deserializer &source, XMLFile *styleFile=nullptr) | File: ../UI/UI.h
UIElement* UILoadLayoutFromVectorBuffer(VectorBuffer& buffer, UI* ptr);
// SharedPtr<UIElement> UI::LoadLayout(Deserializer &source, XMLFile *styleFile=nullptr) | File: ../UI/UI.h
UIElement* UILoadLayoutFromFileWithStyle(File* file, XMLFile* styleFile, UI* ptr);
// SharedPtr<UIElement> UI::LoadLayout(Deserializer &source, XMLFile *styleFile=nullptr) | File: ../UI/UI.h
UIElement* UILoadLayoutFromVectorBufferWithStyle(VectorBuffer& buffer, XMLFile* styleFile, UI* ptr);
// bool UI::SaveLayout(Serializer &dest, UIElement *element) | File: ../UI/UI.h
bool UISaveLayout(File* file, UIElement* element, UI* ptr);
// bool UI::SaveLayout(Serializer &dest, UIElement *element) | File: ../UI/UI.h
bool UISaveLayoutVectorBuffer(VectorBuffer& buffer, UIElement* element, UI* ptr);
// const Vector<UIElement*> UI::GetDragElements() | File: ../UI/UI.h
CScriptArray* UIGetDragElements(UI* ptr);
// void UI::SetFocusElement(UIElement *element, bool byKey=false) | File: ../UI/UI.h
void UISetFocusElement(UIElement* element, UI* ptr);

#define REGISTER_MANUAL_PART_UI(T, className) \
    /* SharedPtr<UIElement> UI::LoadLayout(Deserializer &source, XMLFile *styleFile=nullptr) | File: ../UI/UI.h */ \
    engine->RegisterObjectMethod(className, "UIElement@ LoadLayout(File@+)", AS_FUNCTION_OBJLAST(UILoadLayoutFromFile), AS_CALL_CDECL_OBJLAST); \
    /* SharedPtr<UIElement> UI::LoadLayout(Deserializer &source, XMLFile *styleFile=nullptr) | File: ../UI/UI.h */ \
    engine->RegisterObjectMethod(className, "UIElement@ LoadLayout(File@+, XMLFile@+)", AS_FUNCTION_OBJLAST(UILoadLayoutFromFileWithStyle), AS_CALL_CDECL_OBJLAST); \
    /* SharedPtr<UIElement> UI::LoadLayout(Deserializer &source, XMLFile *styleFile=nullptr) | File: ../UI/UI.h */ \
    engine->RegisterObjectMethod(className, "UIElement@ LoadLayout(VectorBuffer&)", AS_FUNCTION_OBJLAST(UILoadLayoutFromVectorBuffer), AS_CALL_CDECL_OBJLAST); \
    /* SharedPtr<UIElement> UI::LoadLayout(Deserializer &source, XMLFile *styleFile=nullptr) | File: ../UI/UI.h */ \
    engine->RegisterObjectMethod(className, "UIElement@ LoadLayout(VectorBuffer&, XMLFile@+)", AS_FUNCTION_OBJLAST(UILoadLayoutFromVectorBufferWithStyle), AS_CALL_CDECL_OBJLAST); \
    /* bool UI::SaveLayout(Serializer &dest, UIElement *element) | File: ../UI/UI.h */ \
    engine->RegisterObjectMethod(className, "bool SaveLayout(File@+, UIElement@+)", AS_FUNCTION_OBJLAST(UISaveLayout), AS_CALL_CDECL_OBJLAST); \
    /* bool UI::SaveLayout(Serializer &dest, UIElement *element) | File: ../UI/UI.h */ \
    engine->RegisterObjectMethod(className, "bool SaveLayout(VectorBuffer&, UIElement@+)", AS_FUNCTION_OBJLAST(UISaveLayoutVectorBuffer), AS_CALL_CDECL_OBJLAST); \
    /* const Vector<UIElement*> UI::GetDragElements() | File: ../UI/UI.h */ \
    engine->RegisterObjectMethod(className, "const Array<UIElement@>@ GetDragElements()", AS_FUNCTION_OBJLAST(UIGetDragElements), AS_CALL_CDECL_OBJLAST); \
    /* void UI::SetFocusElement(UIElement *element, bool byKey=false) | File: ../UI/UI.h */ \
    engine->RegisterObjectMethod(className, "void set_focusElement(UIElement@+)", AS_FUNCTION_OBJLAST(UISetFocusElement), AS_CALL_CDECL_OBJLAST);

}
