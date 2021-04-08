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

// bool Font::SaveXML(Serializer& dest, int pointSize, bool usedGlyphs = false, const String& indentation = "\t") | File: ../UI/Font.h
template <class T> bool Font_SaveXML_File(File* file, int pointSize, bool usedGlyphs, const String& indentation, T* ptr)
{
    return ptr->SaveXML(*file, pointSize, usedGlyphs, indentation);
}

// bool Font::SaveXML(Serializer& dest, int pointSize, bool usedGlyphs = false, const String& indentation = "\t") | File: ../UI/Font.h
template <class T> bool Font_SaveXML_VectorBuffer(VectorBuffer& buffer, int pointSize, bool usedGlyphs, const String& indentation, T* ptr)
{
    return ptr->SaveXML(buffer, pointSize, usedGlyphs, indentation);
}

// bool Font::SaveXML(Serializer& dest, int pointSize, bool usedGlyphs = false, const String& indentation = "\t") | File: ../UI/Font.h
template <class T> bool Font_SaveXML_FileName(const String& fileName, int pointSize, bool usedGlyphs, const String& indentation, T* ptr)
{
    if (fileName.Empty())
        return false;

    File file(ptr->GetContext(), fileName, FILE_WRITE);
    return ptr->SaveXML(file, pointSize, usedGlyphs, indentation);
}

#define REGISTER_MEMBERS_MANUAL_PART_Font() \
    /* bool Font::SaveXML(Serializer& dest, int pointSize, bool usedGlyphs = false, const String& indentation = "\t") | File: ../UI/Font.h */ \
    engine->RegisterObjectMethod(className, "bool SaveXML(File@+, int, bool usedGlyphs = false, const String&in indentation = \"\t\")", AS_FUNCTION_OBJLAST(Font_SaveXML_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool SaveXML(VectorBuffer&, int, bool usedGlyphs = false, const String&in indentation = \"\t\")", AS_FUNCTION_OBJLAST(Font_SaveXML_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool SaveXML(const String&in, int, bool usedGlyphs = false, const String&in indentation = \"\t\")", AS_FUNCTION_OBJLAST(Font_SaveXML_FileName<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

#define REGISTER_CLASS_MANUAL_PART_UIElement() \
    RegisterNamedObjectConstructor<UIElement>(engine, "UIElement");

// bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
template <class T> bool UIElement_LoadXML_File(File* file, T* ptr)
{
    return file && ptr->LoadXML(*file);
}

// bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h
template <class T> bool UIElement_LoadXML_VectorBuffer(VectorBuffer& buffer, T* ptr)
{
    return ptr->LoadXML(buffer);
}

// bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h
template <class T> bool UIElement_LoadXML_XMLFile(XMLFile* file, XMLFile* styleFile, T* ptr)
{
    if (file)
    {
        XMLElement rootElem = file->GetRoot("element");
        return rootElem && ptr->LoadXML(rootElem, styleFile);
    }
    else
        return false;
}

// virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h
template <class T> UIElement* UIElement_LoadChildXML(XMLFile* file, XMLFile* styleFile, T* ptr)
{
    if (!file)
        return nullptr;

    XMLElement rootElem = file->GetRoot("element");
    if (rootElem)
        return ptr->LoadChildXML(rootElem, styleFile);
    else
        return nullptr;
}

// bool UIElement::SaveXML(Serializer& dest, const String& indentation = "\t") const | File: ../UI/UIElement.h
template <class T> bool UIElement_SaveXML_File(File* file, const String& indentation, T* ptr)
{
    return file && ptr->SaveXML(*file, indentation);
}

// bool UIElement::SaveXML(Serializer& dest, const String& indentation = "\t") const | File: ../UI/UIElement.h
template <class T> bool UIElement_SaveXML_VectorBuffer(VectorBuffer& buffer, const String& indentation, T* ptr)
{
    return ptr->SaveXML(buffer, indentation);
}

// void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
template <class T> void UIElement_RemoveChild(unsigned index, T* ptr)
{
    ptr->RemoveChildAtIndex(index);
}

// bool UIElement::SetStyle(const String& styleName, XMLFile* file = nullptr) | File: ../UI/UIElement.h
template <class T> void UIElement_SetStyle(const String& styleName, T* ptr)
{
    if (styleName.Empty())
        ptr->SetStyleAuto();
    else
        ptr->SetStyle(styleName);
}

// unsigned UIElement::GetNumChildren(bool recursive = false) const | File: ../UI/UIElement.h
template <class T> unsigned UIElement_GetNumChildren_NonRecursive(T* ptr)
{
    return ptr->GetNumChildren(false);
}

// unsigned UIElement::GetNumChildren(bool recursive = false) const | File: ../UI/UIElement.h
template <class T> unsigned UIElement_GetNumChildren_Recursive(T* ptr)
{
    return ptr->GetNumChildren(true);
}

// void UIElement::SetParent(UIElement* parent, unsigned index = M_MAX_UNSIGNED) | File: ../UI/UIElement.h
template <class T> void UIElement_SetParent(UIElement* parent, T* ptr)
{
    ptr->SetParent(parent);
}

// XMLFile* UIElement::GetDefaultStyle(bool recursiveUp = true) const | File: ../UI/UIElement.h
template <class T> XMLFile* UIElement_GetDefaultStyle(T* ptr)
{
    return ptr->GetDefaultStyle();
}

// const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
template <class T> VariantMap& UIElement_GetVars(T* ptr)
{
    return const_cast<VariantMap&>(ptr->GetVars());
}

#define REGISTER_MEMBERS_MANUAL_PART_UIElement() \
    /* bool UIElement::LoadXML(Deserializer& source) | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "bool LoadXML(File@+)", AS_FUNCTION_OBJLAST(UIElement_LoadXML_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool LoadXML(VectorBuffer&)", AS_FUNCTION_OBJLAST(UIElement_LoadXML_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* bool UIElement::LoadXML(const XMLElement& source) override | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "bool LoadXML(XMLFile@+, XMLFile@+)", AS_FUNCTION_OBJLAST(UIElement_LoadXML_XMLFile<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* virtual UIElement* UIElement::LoadChildXML(const XMLElement& childElem, XMLFile* styleFile) | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "UIElement@+ LoadChildXML(XMLFile@+, XMLFile@+)", AS_FUNCTION_OBJLAST(UIElement_LoadChildXML<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* bool UIElement::SaveXML(Serializer& dest, const String& indentation = "\t") const | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "bool SaveXML(File@+, const String&in indentation = \"\t\")", AS_FUNCTION_OBJLAST(UIElement_SaveXML_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool SaveXML(VectorBuffer&, const String&in indentation = \"\t\")", AS_FUNCTION_OBJLAST(UIElement_SaveXML_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "void RemoveChild(uint)", AS_FUNCTION_OBJLAST(UIElement_RemoveChild<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* bool UIElement::SetStyle(const String& styleName, XMLFile* file = nullptr) | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "void set_style(const String&in)", AS_FUNCTION_OBJLAST(UIElement_SetStyle<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* unsigned UIElement::GetNumChildren(bool recursive = false) const | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "uint get_numChildren() const", AS_FUNCTION_OBJLAST(UIElement_GetNumChildren_NonRecursive<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "uint get_numAllChildren() const", AS_FUNCTION_OBJLAST(UIElement_GetNumChildren_Recursive<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void UIElement::SetParent(UIElement* parent, unsigned index = M_MAX_UNSIGNED) | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "void set_parent(UIElement@+)", AS_FUNCTION_OBJLAST(UIElement_SetParent<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* XMLFile* UIElement::GetDefaultStyle(bool recursiveUp = true) const | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "XMLFile@+ get_defaultStyle() const", AS_FUNCTION_OBJLAST(UIElement_GetDefaultStyle<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h */ \
    engine->RegisterObjectMethod(className, "VariantMap& get_vars()", AS_FUNCTION_OBJLAST(UIElement_GetVars<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// SharedPtr<UIElement> UI::LoadLayout(Deserializer& source, XMLFile* styleFile = nullptr) | File: ../UI/UI.h
template <class T> UIElement* UI_LoadLayout_File(File* file, UI* ptr)
{
    if (file)
    {
        SharedPtr<UIElement> root = ptr->LoadLayout(*file);
        if (root)
            root->AddRef();
        return root.Get();
    }
    else
        return nullptr;
}

// SharedPtr<UIElement> UI::LoadLayout(Deserializer& source, XMLFile* styleFile = nullptr) | File: ../UI/UI.h
template <class T> UIElement* UI_LoadLayout_VectorBuffer(VectorBuffer& buffer, UI* ptr)
{
    SharedPtr<UIElement> root = ptr->LoadLayout(buffer);
    if (root)
        root->AddRef();
    return root.Get();
}

// SharedPtr<UIElement> UI::LoadLayout(Deserializer& source, XMLFile* styleFile = nullptr) | File: ../UI/UI.h
template <class T> UIElement* UI_LoadLayout_File_Style(File* file, XMLFile* styleFile, UI* ptr)
{
    if (file)
    {
        SharedPtr<UIElement> root = ptr->LoadLayout(*file, styleFile);
        if (root)
            root->AddRef();
        return root.Get();
    }
    else
        return nullptr;
}

// SharedPtr<UIElement> UI::LoadLayout(Deserializer& source, XMLFile* styleFile = nullptr) | File: ../UI/UI.h
template <class T> UIElement* UI_LoadLayout_VectorBuffer_Style(VectorBuffer& buffer, XMLFile* styleFile, UI* ptr)
{
    SharedPtr<UIElement> root = ptr->LoadLayout(buffer, styleFile);
    if (root)
        root->AddRef();
    return root.Get();
}

// bool UI::SaveLayout(Serializer& dest, UIElement* element) | File: ../UI/UI.h
template <class T> bool UI_SaveLayout_File(File* file, UIElement* element, UI* ptr)
{
    return file && ptr->SaveLayout(*file, element);
}

// bool UI::SaveLayout(Serializer& dest, UIElement* element) | File: ../UI/UI.h
template <class T> bool UI_SaveLayout_VectorBuffer(VectorBuffer& buffer, UIElement* element, UI* ptr)
{
    return ptr->SaveLayout(buffer, element);
}

// const Vector<UIElement*> UI::GetDragElements() | File: ../UI/UI.h
template <class T> CScriptArray* UI_GetDragElements(UI* ptr)
{
    return VectorToHandleArray(ptr->GetDragElements(), "const Array<UIElement@>@");
}

// void UI::SetFocusElement(UIElement* element, bool byKey = false) | File: ../UI/UI.h
template <class T> void UI_SetFocusElement(UIElement* element, UI* ptr)
{
    ptr->SetFocusElement(element);
}

#define REGISTER_MEMBERS_MANUAL_PART_UI() \
    /* SharedPtr<UIElement> UI::LoadLayout(Deserializer& source, XMLFile* styleFile = nullptr) | File: ../UI/UI.h */ \
    engine->RegisterObjectMethod(className, "UIElement@ LoadLayout(File@+)", AS_FUNCTION_OBJLAST(UI_LoadLayout_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "UIElement@ LoadLayout(File@+, XMLFile@+)", AS_FUNCTION_OBJLAST(UI_LoadLayout_File_Style<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "UIElement@ LoadLayout(VectorBuffer&)", AS_FUNCTION_OBJLAST(UI_LoadLayout_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "UIElement@ LoadLayout(VectorBuffer&, XMLFile@+)", AS_FUNCTION_OBJLAST(UI_LoadLayout_VectorBuffer_Style<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* bool UI::SaveLayout(Serializer& dest, UIElement* element) | File: ../UI/UI.h */ \
    engine->RegisterObjectMethod(className, "bool SaveLayout(File@+, UIElement@+)", AS_FUNCTION_OBJLAST(UI_SaveLayout_File<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool SaveLayout(VectorBuffer&, UIElement@+)", AS_FUNCTION_OBJLAST(UI_SaveLayout_VectorBuffer<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* const Vector<UIElement*> UI::GetDragElements() | File: ../UI/UI.h */ \
    engine->RegisterObjectMethod(className, "const Array<UIElement@>@ GetDragElements()", AS_FUNCTION_OBJLAST(UI_GetDragElements<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void UI::SetFocusElement(UIElement* element, bool byKey = false) | File: ../UI/UI.h */ \
    engine->RegisterObjectMethod(className, "void set_focusElement(UIElement@+)", AS_FUNCTION_OBJLAST(UI_SetFocusElement<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

#define REGISTER_CLASS_MANUAL_PART_BorderImage() \
    RegisterNamedObjectConstructor<BorderImage>(engine, "BorderImage");

#define REGISTER_CLASS_MANUAL_PART_Button() \
    RegisterNamedObjectConstructor<Button>(engine, "Button");

#define REGISTER_CLASS_MANUAL_PART_CheckBox() \
    RegisterNamedObjectConstructor<CheckBox>(engine, "CheckBox");

#define REGISTER_CLASS_MANUAL_PART_Cursor() \
    RegisterNamedObjectConstructor<Cursor>(engine, "Cursor");

#define REGISTER_CLASS_MANUAL_PART_Menu() \
    RegisterNamedObjectConstructor<Menu>(engine, "Menu");

}
