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

#include "../Core/Spline.h"
#include "../Core/Variant.h"

namespace Urho3D
{

// const char** AttributeInfo::enumNames_ | File: ../Core/Attribute.h
template <class T> CScriptArray* AttributeInfo_GetEnumNames(T* ptr)
{
    Vector<String> enumNames;
    const char** enumNamePtrs = ptr->enumNames_;
    while (enumNamePtrs && *enumNamePtrs)
        enumNames.Push(*enumNamePtrs++);
    return VectorToArray<String>(enumNames, "Array<String>");
}

#define REGISTER_MEMBERS_MANUAL_PART_AttributeInfo() \
    /* const char** AttributeInfo::enumNames_ | File: ../Core/Attribute.h */ \
    engine->RegisterObjectMethod(className, "Array<String>@ get_enumNames() const", AS_FUNCTION_OBJLAST(AttributeInfo_GetEnumNames<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
template <class T> void ResourceRefList_Resize(unsigned size, ResourceRefList* ptr)
{
    ptr->names_.Resize(size);
}

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
template <class T> unsigned ResourceRefList_GetSize(ResourceRefList* ptr)
{
    return ptr->names_.Size();
}

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
template <class T> bool ResourceRefList_IsEmpty(ResourceRefList* ptr)
{
    return ptr->names_.Size() == 0;
}

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
template <class T> void ResourceRefList_SetName(unsigned index, const String& name, ResourceRefList* ptr)
{
    if (index >= ptr->names_.Size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return;
    }

    ptr->names_[index] = name;
}

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
template <class T> const String& ResourceRefList_GetName(unsigned index, ResourceRefList* ptr)
{
    if (index >= ptr->names_.Size())
    {
        asGetActiveContext()->SetException("Index out of bounds");
        return String::EMPTY;
    }

    return ptr->names_[index];
}

#define REGISTER_MEMBERS_MANUAL_PART_ResourceRefList() \
    /* StringVector ResourceRefList::names_ | File: ../Core/Variant.h */ \
    engine->RegisterObjectMethod(className, "void Resize(uint)", AS_FUNCTION_OBJLAST(ResourceRefList_Resize<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "uint get_length() const", AS_FUNCTION_OBJLAST(ResourceRefList_GetSize<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "bool get_empty() const", AS_FUNCTION_OBJLAST(ResourceRefList_IsEmpty<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "void set_names(uint, const String&in) const", AS_FUNCTION_OBJLAST(ResourceRefList_SetName<T>), AS_CALL_CDECL_OBJLAST); \
    engine->RegisterObjectMethod(className, "const String& get_names(uint) const", AS_FUNCTION_OBJLAST(ResourceRefList_GetName<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// explicit Spline::Spline(const Vector<Variant>& knots, InterpolationMode mode = BEZIER_CURVE) | File: ../Core/Spline.h
static void Spline_Spline(CScriptArray* arr, InterpolationMode mode, Spline* ptr)
{
    new(ptr) Spline(ArrayToVector<Variant>(arr), mode);
}

#define REGISTER_CLASS_MANUAL_PART_Spline() \
    /* explicit Spline::Spline(const Vector<Variant>& knots, InterpolationMode mode = BEZIER_CURVE) | File: ../Core/Spline.h */ \
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f(Array<Variant>@+, InterpolationMode = BEZIER_CURVE)", AS_FUNCTION(Spline_Spline), AS_CALL_CDECL_OBJLAST);

// const VariantVector& Spline::GetKnots() const | File: ../Core/Spline.h
template <class T> CScriptArray* Spline_GetKnots(T* ptr)
{
    return VectorToArray(ptr->GetKnots(), "Array<Variant>");
}

// void Spline::SetKnots(const Vector<Variant>& knots) | File: ../Core/Spline.h
template <class T> void Spline_SetKnots(CScriptArray* arr, T* ptr)
{
    ptr->SetKnots(ArrayToVector<Variant>(arr));
}

// void Spline::SetKnot(const Variant& knot, unsigned index) | File: ../Core/Spline.h
template <class T> void Spline_SetKnot(unsigned index, const Variant& in, T* ptr)
{
    ptr->SetKnot(in, index);
}

#define REGISTER_MEMBERS_MANUAL_PART_Spline() \
    /* const VariantVector& Spline::GetKnots() const | File: ../Core/Spline.h */ \
    engine->RegisterObjectMethod(className, "Array<Variant>@ get_knots() const", AS_FUNCTION_OBJLAST(Spline_GetKnots<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void Spline::SetKnots(const Vector<Variant>& knots) | File: ../Core/Spline.h */ \
    engine->RegisterObjectMethod(className, "void set_knots(Array<Variant>@+)", AS_FUNCTION_OBJLAST(Spline_SetKnots<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void Spline::SetKnot(const Variant& knot, unsigned index) | File: ../Core/Spline.h */ \
    engine->RegisterObjectMethod(className, "void set_knot(uint, const Variant&in)", AS_FUNCTION_OBJLAST(Spline_SetKnot<T>), AS_CALL_CDECL_OBJLAST);

}
