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

// template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
static UI* GetUI()
{
    return GetScriptContext()->GetSubsystem<UI>();
}

// This function is called after ASRegisterGenerated()
void ASRegisterManualLast_UI(asIScriptEngine* engine)
{
    // template <class T> T* Context::GetSubsystem() const | File: ../Core/Context.h
    engine->RegisterGlobalFunction("UI@+ get_ui()", AS_FUNCTION(GetUI), AS_CALL_CDECL);
}

// ========================================================================================

// SharedPtr<UIElement> UI::LoadLayout(Deserializer& source, XMLFile* styleFile = nullptr) | File: ../UI/UI.h
UIElement* UI_LoadLayout_File(File* file, UI* ptr)
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
UIElement* UI_LoadLayout_VectorBuffer(VectorBuffer& buffer, UI* ptr)
{
    SharedPtr<UIElement> root = ptr->LoadLayout(buffer);
    if (root)
        root->AddRef();
    return root.Get();
}

// SharedPtr<UIElement> UI::LoadLayout(Deserializer& source, XMLFile* styleFile = nullptr) | File: ../UI/UI.h
UIElement* UI_LoadLayout_File_Style(File* file, XMLFile* styleFile, UI* ptr)
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
UIElement* UI_LoadLayout_VectorBuffer_Style(VectorBuffer& buffer, XMLFile* styleFile, UI* ptr)
{
    SharedPtr<UIElement> root = ptr->LoadLayout(buffer, styleFile);
    if (root)
        root->AddRef();
    return root.Get();
}

// bool UI::SaveLayout(Serializer& dest, UIElement* element) | File: ../UI/UI.h
bool UI_SaveLayout_File(File* file, UIElement* element, UI* ptr)
{
    return file && ptr->SaveLayout(*file, element);
}

// bool UI::SaveLayout(Serializer& dest, UIElement* element) | File: ../UI/UI.h
bool UI_SaveLayout_VectorBuffer(VectorBuffer& buffer, UIElement* element, UI* ptr)
{
    return ptr->SaveLayout(buffer, element);
}

// const Vector<UIElement*> UI::GetDragElements() | File: ../UI/UI.h
CScriptArray* UI_GetDragElements(UI* ptr)
{
    return VectorToHandleArray(ptr->GetDragElements(), "const Array<UIElement@>@");
}

// void UI::SetFocusElement(UIElement* element, bool byKey = false) | File: ../UI/UI.h
void UI_SetFocusElement(UIElement* element, UI* ptr)
{
    ptr->SetFocusElement(element);
}

}
