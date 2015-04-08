//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../IO/Log.h"
#include "../Core/Spline.h"

namespace Urho3D
{

const char* interpolationModeNames[] =
{
    "Bezier",
    0
};

Spline::Spline() :
    interpolationMode_(BEZIER_CURVE)
{
}

Spline::Spline(InterpolationMode mode) :
    interpolationMode_(mode)
{
}

Spline::Spline(const Vector<Variant>& knots, InterpolationMode mode) :
    interpolationMode_(mode),
    knots_(knots)
{
}

Spline::Spline(const Spline& rhs) :
    interpolationMode_(rhs.interpolationMode_),
    knots_(rhs.knots_)
{
}

Variant Spline::GetPoint(float f) const
{
    if (knots_.Size() < 2)
        return knots_.Size() == 1 ? knots_[0] : Variant::EMPTY;

    if (f > 1.f)
        f = 1.f;
    else if (f < 0.f)
        f = 0.f;

    switch (interpolationMode_)
    {
    case BEZIER_CURVE:
        return BezierInterpolation(knots_, f);

    default:
        LOGERROR("Unsupported interpolation mode");
        return Variant::EMPTY;
    }
}

void Spline::SetKnot(const Variant& knot, unsigned index)
{
    if (index < knots_.Size())
    {
        if (knots_.Size() > 0 && knots_[0].GetType() == knot.GetType())
            knots_[index] = knot;
        else if (knots_.Empty())
            knots_.Push(knot);
        else
            LOGERRORF("Attempted to set a Spline's Knot value of type %s where elements are already using %s", knot.GetTypeName().CString(), knots_[0].GetTypeName().CString());
    }
}

void Spline::AddKnot(const Variant& knot) 
{ 
    if (knots_.Size() > 0 && knots_[0].GetType() == knot.GetType())
        knots_.Push(knot);
    else if (knots_.Empty())
        knots_.Push(knot);
    else
        LOGERRORF("Attempted to add Knot to Spline of type %s where elements are already using %s", knot.GetTypeName().CString(), knots_[0].GetTypeName().CString());
}

void Spline::AddKnot(const Variant& knot, unsigned index) 
{ 
    if (index > knots_.Size())
        index = knots_.Size();

    if (knots_.Size() > 0 && knots_[0].GetType() == knot.GetType())
        knots_.Insert(index, knot);
    else if (knots_.Empty())
        knots_.Push(knot);
    else
        LOGERRORF("Attempted to add Knot to Spline of type %s where elements are already using %s", knot.GetTypeName().CString(), knots_[0].GetTypeName().CString());
}

Variant Spline::BezierInterpolation(const Vector<Variant>& knots, float t) const
{
    if (knots.Size() == 2)
    {
        switch (knots[0].GetType())
        {
        case VAR_FLOAT:
        case VAR_VECTOR2:
        case VAR_VECTOR3:
        case VAR_VECTOR4:
        case VAR_COLOR:
            return LinearInterpolation(knots[0], knots[1], t);
        default:
            return Variant::EMPTY;
        }
    }
    else
    {
        Vector<Variant> interpolatedKnots;
        for (unsigned i = 1; i < knots.Size(); i++)
        {
            switch (knots[0].GetType())
            {
            case VAR_FLOAT:
            case VAR_VECTOR2:
            case VAR_VECTOR3:
            case VAR_VECTOR4:
            case VAR_COLOR:
                interpolatedKnots.Push(LinearInterpolation(knots[i - 1], knots[i], t));
                break;
            default:
                return Variant::EMPTY;
            }
        }
        return BezierInterpolation(interpolatedKnots, t);
    }
}

Variant Spline::LinearInterpolation(const Variant& lhs, const Variant& rhs, float t) const
{
    switch (lhs.GetType())
    {
    case VAR_FLOAT:
        return Lerp(lhs.GetFloat(), rhs.GetFloat(), t);
    case VAR_VECTOR2:
        return lhs.GetVector2().Lerp(rhs.GetVector2(), t);
    case VAR_VECTOR3:
        return lhs.GetVector3().Lerp(rhs.GetVector3(), t);
    case VAR_VECTOR4:
        return lhs.GetVector4().Lerp(rhs.GetVector4(), t);
    case VAR_COLOR:
        return lhs.GetColor().Lerp(rhs.GetColor(), t);
    default:
        return Variant::EMPTY;
    }
}

}
