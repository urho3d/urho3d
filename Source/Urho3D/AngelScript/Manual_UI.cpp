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

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Manual_UI.h"

namespace Urho3D
{

// This function is called before ASRegisterGenerated()
void ASRegisterManualFirst_UI(asIScriptEngine* engine)
{
}

// ========================================================================================

// template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
static UI* GetUI()
{
    return GetScriptContext()->GetSubsystem<UI>();
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_UI(asIScriptEngine* engine)
{
    // template<class T> T * Object::GetSubsystem() const | File: ../Core/Object.h
    engine->RegisterGlobalFunction("UI@+ get_ui()", asFUNCTION(GetUI), asCALL_CDECL);
}

// ========================================================================================

// bool Font::SaveXML(Serializer &dest, int pointSize, bool usedGlyphs=false, const String &indentation="\t") | File: ../UI/Font.h
bool FontSaveXMLVectorBuffer(VectorBuffer& buffer, int pointSize, bool usedGlyphs, const String& indentation, Font* ptr)
{
    return ptr->SaveXML(buffer, pointSize, usedGlyphs, indentation);
}

// bool Font::SaveXML(Serializer &dest, int pointSize, bool usedGlyphs=false, const String &indentation="\t") | File: ../UI/Font.h
bool FontSaveXML(const String& fileName, int pointSize, bool usedGlyphs, const String& indentation, Font* ptr)
{
    if (fileName.Empty())
        return false;

    File file(ptr->GetContext(), fileName, FILE_WRITE);
    return ptr->SaveXML(file, pointSize, usedGlyphs, indentation);
}

// bool Font::SaveXML(Serializer &dest, int pointSize, bool usedGlyphs=false, const String &indentation="\t") | File: ../UI/Font.h
bool FontSaveXMLFile(File* file, int pointSize, bool usedGlyphs, const String& indentation, Font* ptr)
{
    return ptr->SaveXML(*file, pointSize, usedGlyphs, indentation);
}

// ========================================================================================

// SharedPtr<UIElement> UI::LoadLayout(Deserializer &source, XMLFile *styleFile=nullptr) | File: ../UI/UI.h
UIElement* UILoadLayoutFromFile(File* file, UI* ptr)
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

// SharedPtr<UIElement> UI::LoadLayout(Deserializer &source, XMLFile *styleFile=nullptr) | File: ../UI/UI.h
UIElement* UILoadLayoutFromVectorBuffer(VectorBuffer& buffer, UI* ptr)
{
    SharedPtr<UIElement> root = ptr->LoadLayout(buffer);
    if (root)
        root->AddRef();
    return root.Get();
}

// SharedPtr<UIElement> UI::LoadLayout(Deserializer &source, XMLFile *styleFile=nullptr) | File: ../UI/UI.h
UIElement* UILoadLayoutFromFileWithStyle(File* file, XMLFile* styleFile, UI* ptr)
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

// SharedPtr<UIElement> UI::LoadLayout(Deserializer &source, XMLFile *styleFile=nullptr) | File: ../UI/UI.h
UIElement* UILoadLayoutFromVectorBufferWithStyle(VectorBuffer& buffer, XMLFile* styleFile, UI* ptr)
{
    SharedPtr<UIElement> root = ptr->LoadLayout(buffer, styleFile);
    if (root)
        root->AddRef();
    return root.Get();
}

// bool UI::SaveLayout(Serializer &dest, UIElement *element) | File: ../UI/UI.h
bool UISaveLayout(File* file, UIElement* element, UI* ptr)
{
    return file && ptr->SaveLayout(*file, element);
}

// bool UI::SaveLayout(Serializer &dest, UIElement *element) | File: ../UI/UI.h
bool UISaveLayoutVectorBuffer(VectorBuffer& buffer, UIElement* element, UI* ptr)
{
    return ptr->SaveLayout(buffer, element);
}

// const Vector<UIElement*> UI::GetDragElements() | File: ../UI/UI.h
CScriptArray* UIGetDragElements(UI* ptr)
{
    return VectorToHandleArray(ptr->GetDragElements(), "const Array<UIElement@>@");
}

// void UI::SetFocusElement(UIElement *element, bool byKey=false) | File: ../UI/UI.h
void UISetFocusElement(UIElement* element, UI* ptr)
{
    ptr->SetFocusElement(element);
}

// ========================================================================================

// bool UIElement::LoadXML(Deserializer &source) | File: ../UI/UIElement.h
bool UIElementLoadXML(File* file, UIElement* ptr)
{
    return file && ptr->LoadXML(*file);
}

// bool UIElement::LoadXML(Deserializer &source) | File: ../UI/UIElement.h
bool UIElementLoadXMLVectorBuffer(VectorBuffer& buffer, UIElement* ptr)
{
    return ptr->LoadXML(buffer);
}

// bool UIElement::LoadXML(Deserializer &source) | File: ../UI/UIElement.h
bool UIElementLoadXML(XMLFile* file, XMLFile* styleFile, UIElement* ptr)
{
    if (file)
    {
        XMLElement rootElem = file->GetRoot("element");
        return rootElem && ptr->LoadXML(rootElem, styleFile);
    }
    else
        return false;
}

// virtual UIElement* UIElement::LoadChildXML(const XMLElement &childElem, XMLFile *styleFile) | File: ../UI/UIElement.h
UIElement* UIElementLoadChildXML(XMLFile* file, XMLFile* styleFile, UIElement* ptr)
{
    if (!file)
        return nullptr;

    XMLElement rootElem = file->GetRoot("element");
    if (rootElem)
        return ptr->LoadChildXML(rootElem, styleFile);
    else
        return nullptr;
}

// bool UIElement::SaveXML(Serializer &dest, const String &indentation="\t") const | File: ../UI/UIElement.h
bool UIElementSaveXML(File* file, const String& indentation, UIElement* ptr)
{
    return file && ptr->SaveXML(*file);
}

// bool UIElement::SaveXML(Serializer &dest, const String &indentation="\t") const | File: ../UI/UIElement.h
bool UIElementSaveXMLVectorBuffer(VectorBuffer& buffer, const String& indentation, UIElement* ptr)
{
    return ptr->SaveXML(buffer);
}

// void UIElement::RemoveChildAtIndex(unsigned index) | File: ../UI/UIElement.h
void UIElementRemoveChild(unsigned index, UIElement* ptr)
{
    ptr->RemoveChildAtIndex(index);
}

// bool UIElement::SetStyle(const String &styleName, XMLFile *file=nullptr) | File: ../UI/UIElement.h
void UIElementSetStyle(const String& styleName, UIElement* ptr)
{
    if (styleName.Empty())
        ptr->SetStyleAuto();
    else
        ptr->SetStyle(styleName);
}

// unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
unsigned UIElementGetNumChildrenNonRecursive(UIElement* ptr)
{
    return ptr->GetNumChildren(false);
}

// unsigned UIElement::GetNumChildren(bool recursive=false) const | File: ../UI/UIElement.h
unsigned UIElementGetNumChildrenRecursive(UIElement* ptr)
{
    return ptr->GetNumChildren(true);
}

// void UIElement::SetParent(UIElement *parent, unsigned index=M_MAX_UNSIGNED) | File: ../UI/UIElement.h
void UIElementSetParent(UIElement* parent, UIElement* ptr)
{
    ptr->SetParent(parent);
}

// XMLFile* UIElement::GetDefaultStyle(bool recursiveUp=true) const | File: ../UI/UIElement.h
XMLFile* UIElementGetDefaultStyle(UIElement* ptr)
{
    return ptr->GetDefaultStyle();
}

// const VariantMap& UIElement::GetVars() const | File: ../UI/UIElement.h
VariantMap& UIElementGetVars(UIElement* ptr)
{
    return const_cast<VariantMap&>(ptr->GetVars());
}

}
