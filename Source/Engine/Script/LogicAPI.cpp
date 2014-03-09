//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "Precompiled.h"
#include "APITemplates.h"
#include "Spline.h"
#include "SplinePath.h"

namespace Urho3D
{

static void ConstructSpline(Spline* ptr)
{
    new (ptr) Spline();
}

static void ConstructSpline(InterpolationMode mode, Spline* ptr)
{
    new (ptr) Spline(mode);
}

static void ConstructSpline(CScriptArray* arr, InterpolationMode mode, Spline* ptr)
{
    new (ptr) Spline(ArrayToVector<Variant>(arr), mode);
}

static void ConstructSpline(const Spline& rhs, Spline* ptr)
{
    new (ptr) Spline(rhs);
}

static CScriptArray* GetSplineKnots(Spline* ptr)
{
    return VectorToArray(ptr->GetKnots(), "Array<Variant>");
}

static void SetSplineKnots(CScriptArray* arr, Spline* ptr)
{
    ptr->SetKnots(ArrayToVector<Variant>(arr));
}

static void SetSplineKnot(unsigned index, const Variant& in, Spline* ptr)
{
    ptr->SetKnot(in, index);
}

static void RegisterSpline(asIScriptEngine* engine)
{
    engine->RegisterEnum("InterpolationMode");
    engine->RegisterEnumValue("InterpolationMode", "BEZIER_CURVE", BEZIER_CURVE);

    engine->RegisterObjectType("Spline", sizeof(Spline), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK);
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f()", asFUNCTIONPR(ConstructSpline, (Spline*), void), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f(InterpolationMode)", asFUNCTIONPR(ConstructSpline, (InterpolationMode, Spline*), void), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f(Array<Variant>@+, InterpolationMode = BEZIER_CURVE)", asFUNCTIONPR(ConstructSpline, (CScriptArray*, InterpolationMode, Spline*), void), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("Spline", asBEHAVE_CONSTRUCT, "void f(const Spline&in)", asFUNCTIONPR(ConstructSpline, (const Spline&, Spline*), void), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Spline", "Spline& opAssign(const Spline&in)", asMETHOD(Spline, operator =), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "bool opEquals(const Spline&in) const", asMETHOD(Spline, operator ==), asCALL_THISCALL);

    engine->RegisterObjectMethod("Spline", "InterpolationMode get_interpolationMode() const", asMETHOD(Spline, GetInterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void set_interpolationMode(InterpolationMode)", asMETHOD(Spline, SetInterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "Array<Variant>@ get_knots() const", asFUNCTION(GetSplineKnots), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Spline", "void set_knots(Array<Variant>@+)", asFUNCTION(SetSplineKnots), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Spline", "Variant get_knot(uint) const", asMETHOD(Spline, GetKnot), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void set_knot(uint, const Variant&in)", asFUNCTION(SetSplineKnot), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Spline", "void AddKnot(const Variant&in)", asMETHODPR(Spline, AddKnot, (const Variant&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void AddKnot(const Variant&in, uint)", asMETHODPR(Spline, AddKnot, (const Variant&, unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void RemoveKnot()", asMETHODPR(Spline, RemoveKnot, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void RemoveKnot(uint)", asMETHODPR(Spline, RemoveKnot, (unsigned), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "void Clear()", asMETHOD(Spline, Clear), asCALL_THISCALL);
    engine->RegisterObjectMethod("Spline", "Variant GetPoint(float)", asMETHOD(Spline, GetPoint), asCALL_THISCALL);
}

static void RegisterSplinePath(asIScriptEngine* engine)
{
    RegisterComponent<SplinePath>(engine, "SplinePath");
    engine->RegisterObjectMethod("SplinePath", "void AddControlPoint(Node@+ point, uint index = M_MAX_UNSIGNED)", asMETHOD(SplinePath, AddControlPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void RemoveControlPoint(Node@+ point)", asMETHOD(SplinePath, RemoveControlPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void ClearControlPoints()", asMETHOD(SplinePath, ClearControlPoints), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Vector3 GetPoint(float) const", asMETHOD(SplinePath, GetPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_interpolationMode(InterpolationMode)", asMETHOD(SplinePath, SetInterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_speed(float)", asMETHOD(SplinePath, SetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_position(float)", asMETHOD(SplinePath, SetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void set_controlledNode(Node@+)", asMETHOD(SplinePath, GetControlledNode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "InterpolationMode get_interpolationMode() const", asMETHOD(SplinePath, GetInterpolationMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "float get_speed() const", asMETHOD(SplinePath, GetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Vector3 get_position() const", asMETHOD(SplinePath, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "Node@ get_controlledNode() const", asMETHOD(SplinePath, GetControlledNode), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void Move(float)", asMETHOD(SplinePath, Move), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "void Reset()", asMETHOD(SplinePath, Reset), asCALL_THISCALL);
    engine->RegisterObjectMethod("SplinePath", "bool get_isFinished() const", asMETHOD(SplinePath, IsFinished), asCALL_THISCALL);
}


void RegisterLogicAPI(asIScriptEngine* engine)
{
    // Register this here instead of MathAPI as it requires variant which requires math, even though technically its a math class.
    RegisterSpline(engine);
    RegisterSplinePath(engine);
}
}