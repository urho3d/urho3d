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
CScriptArray* AttributeInfoGetEnumNames(AttributeInfo* ptr);

#define REGISTER_MANUAL_PART_AttributeInfo(T, className) \
    /* const char** AttributeInfo::enumNames_ | File: ../Core/Attribute.h */ \
    engine->RegisterObjectMethod(className, "Array<String>@ get_enumNames() const", asFUNCTION(AttributeInfoGetEnumNames), asCALL_CDECL_OBJLAST);

// ========================================================================================

// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
void ResourceRefListResize(unsigned size, ResourceRefList* ptr);
// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
unsigned ResourceRefListGetSize(ResourceRefList* ptr);
// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
bool ResourceRefListIsEmpty(ResourceRefList* ptr);
// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
void ResourceRefListSetName(unsigned index, const String& name, ResourceRefList* ptr);
// StringVector ResourceRefList::names_ | File: ../Core/Variant.h
const String& ResourceRefListGetName(unsigned index, ResourceRefList* ptr);

#define REGISTER_MANUAL_PART_ResourceRefList(T, className) \
    /* StringVector ResourceRefList::names_ | File: ../Core/Variant.h */ \
    engine->RegisterObjectMethod(className, "void Resize(uint)", asFUNCTION(ResourceRefListResize), asCALL_CDECL_OBJLAST); \
    /* StringVector ResourceRefList::names_ | File: ../Core/Variant.h */ \
    engine->RegisterObjectMethod(className, "uint get_length() const", asFUNCTION(ResourceRefListGetSize), asCALL_CDECL_OBJLAST); \
    /* StringVector ResourceRefList::names_ | File: ../Core/Variant.h */ \
    engine->RegisterObjectMethod(className, "bool get_empty() const", asFUNCTION(ResourceRefListIsEmpty), asCALL_CDECL_OBJLAST); \
    /* StringVector ResourceRefList::names_ | File: ../Core/Variant.h */ \
    engine->RegisterObjectMethod(className, "void set_names(uint, const String&in) const", asFUNCTION(ResourceRefListSetName), asCALL_CDECL_OBJLAST); \
    /* StringVector ResourceRefList::names_ | File: ../Core/Variant.h */ \
    engine->RegisterObjectMethod(className, "const String& get_names(uint) const", asFUNCTION(ResourceRefListGetName), asCALL_CDECL_OBJLAST);

// ========================================================================================

// explicit Spline::Spline(const Vector< Variant > &knots, InterpolationMode mode=BEZIER_CURVE) | File: ../Core/Spline.h
void ConstructSpline(CScriptArray* arr, InterpolationMode mode, Spline* ptr);
// const VariantVector& Spline::GetKnots() const | File: ../Core/Spline.h
CScriptArray* GetSplineKnots(Spline* ptr);
// void Spline::SetKnots(const Vector< Variant > &knots) | File: ../Core/Spline.h
void SetSplineKnots(CScriptArray* arr, Spline* ptr);
// void Spline::SetKnot(const Variant &knot, unsigned index) | File: ../Core/Spline.h
void SetSplineKnot(unsigned index, const Variant& in, Spline* ptr);

#define REGISTER_MANUAL_PART_Spline(T, className) \
    /* explicit Spline::Spline(const Vector< Variant > &knots, InterpolationMode mode=BEZIER_CURVE) | File: ../Core/Spline.h */ \
    engine->RegisterObjectBehaviour(className, asBEHAVE_CONSTRUCT, "void f(Array<Variant>@+, InterpolationMode = BEZIER_CURVE)", asFUNCTIONPR(ConstructSpline, (CScriptArray*, InterpolationMode, Spline*), void), asCALL_CDECL_OBJLAST); \
    /* const VariantVector& Spline::GetKnots() const | File: ../Core/Spline.h */ \
    engine->RegisterObjectMethod(className, "Array<Variant>@ get_knots() const", asFUNCTION(GetSplineKnots), asCALL_CDECL_OBJLAST); \
    /* void Spline::SetKnots(const Vector< Variant > &knots) | File: ../Core/Spline.h */ \
    engine->RegisterObjectMethod(className, "void set_knots(Array<Variant>@+)", asFUNCTION(SetSplineKnots), asCALL_CDECL_OBJLAST); \
    /* void Spline::SetKnot(const Variant &knot, unsigned index) | File: ../Core/Spline.h */ \
    engine->RegisterObjectMethod(className, "void set_knot(uint, const Variant&in)", asFUNCTION(SetSplineKnot), asCALL_CDECL_OBJLAST);

// ========================================================================================

// static unsigned GetSystemTime() | File: ../Core/Timer.h
unsigned TimeGetSystemTime(Time* time);
// static unsigned GetTimeSinceEpoch() | File: ../Core/Timer.h
unsigned TimeGetTimeSinceEpoch(Time* time);
// static String GetTimeStamp() | File: ../Core/Timer.h
String TimeGetTimeStamp(Time* time);

#define REGISTER_MANUAL_PART_Time(T, className) \
    /* static unsigned GetSystemTime() | File: ../Core/Timer.h */ \
    engine->RegisterObjectMethod(className, "uint get_systemTime() const", asFUNCTION(TimeGetSystemTime), asCALL_CDECL_OBJLAST); \
    /* static unsigned GetTimeSinceEpoch() | File: ../Core/Timer.h */ \
    engine->RegisterObjectMethod(className, "uint get_timeSinceEpoch() const", asFUNCTION(TimeGetTimeSinceEpoch), asCALL_CDECL_OBJLAST); \
    /* static String GetTimeStamp() | File: ../Core/Timer.h */ \
    engine->RegisterObjectMethod(className, "String get_timeStamp() const", asFUNCTION(TimeGetTimeStamp), asCALL_CDECL_OBJLAST);

}
