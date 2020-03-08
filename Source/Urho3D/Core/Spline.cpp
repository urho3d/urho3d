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

#include "../Core/Spline.h"
#include "../IO/Log.h"

namespace Urho3D
{

const char* interpolationModeNames[] =
{
    "Bezier",
    "Catmull-Rom",
    "Linear",
    "Catmull-Rom Full",
    nullptr
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
    case CATMULL_ROM_CURVE:
        return CatmullRomInterpolation(knots_, f);
    case LINEAR_CURVE:
        return LinearInterpolation(knots_, f);
    case CATMULL_ROM_FULL_CURVE:
        {
            /// \todo Do not allocate a new vector each time
            Vector<Variant> fullKnots;
            if (knots_.Size() > 1)
            {
                // Non-cyclic case: duplicate start and end
                if (knots_.Front() != knots_.Back())
                {
                    fullKnots.Push(knots_.Front());
                    fullKnots.Push(knots_);
                    fullKnots.Push(knots_.Back());
                }
                // Cyclic case: smooth the tangents
                else
                {
                    fullKnots.Push(knots_[knots_.Size() - 2]);
                    fullKnots.Push(knots_);
                    fullKnots.Push(knots_[1]);
                }
            }
            return CatmullRomInterpolation(fullKnots, f);
        }

    default:
        URHO3D_LOGERROR("Unsupported interpolation mode");
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
            URHO3D_LOGERRORF("Attempted to set a Spline's Knot value of type %s where elements are already using %s",
                knot.GetTypeName().CString(), knots_[0].GetTypeName().CString());
    }
}

void Spline::AddKnot(const Variant& knot)
{
    if (knots_.Size() > 0 && knots_[0].GetType() == knot.GetType())
        knots_.Push(knot);
    else if (knots_.Empty())
        knots_.Push(knot);
    else
        URHO3D_LOGERRORF("Attempted to add Knot to Spline of type %s where elements are already using %s", knot.GetTypeName().CString(),
            knots_[0].GetTypeName().CString());
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
        URHO3D_LOGERRORF("Attempted to add Knot to Spline of type %s where elements are already using %s", knot.GetTypeName().CString(),
            knots_[0].GetTypeName().CString());
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
        case VAR_DOUBLE:
            return LinearInterpolation(knots[0], knots[1], t);
        default:
            return Variant::EMPTY;
        }
    }
    else
    {
        /// \todo Do not allocate a new vector each time
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
            case VAR_DOUBLE:
                interpolatedKnots.Push(LinearInterpolation(knots[i - 1], knots[i], t));
                break;
            default:
                return Variant::EMPTY;
            }
        }
        return BezierInterpolation(interpolatedKnots, t);
    }
}

template <typename T> Variant CalculateCatmullRom(const T& p0, const T& p1, const T& p2, const T& p3, float t, float t2, float t3)
{
    return Variant(0.5f * ((2.0f * p1) + (-p0 + p2) * t +
        (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2 +
        (-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t3));
}

Variant Spline::CatmullRomInterpolation(const Vector<Variant>& knots, float t) const
{
    if (knots.Size() < 4)
        return Variant::EMPTY;
    else
    {
        if (t >= 1.f)
            return knots[knots.Size() - 2];

        auto originIndex = static_cast<int>(t * (knots.Size() - 3));
        t = fmodf(t * (knots.Size() - 3), 1.f);
        float t2 = t * t;
        float t3 = t2 * t;

        switch (knots[originIndex].GetType())
        {
        case VAR_FLOAT:
            return CalculateCatmullRom(knots[originIndex].GetFloat(), knots[originIndex + 1].GetFloat(),
                knots[originIndex + 2].GetFloat(), knots[originIndex + 3].GetFloat(), t, t2, t3);
        case VAR_VECTOR2:
            return CalculateCatmullRom(knots[originIndex].GetVector2(), knots[originIndex + 1].GetVector2(),
                knots[originIndex + 2].GetVector2(), knots[originIndex + 3].GetVector2(), t, t2, t3);
        case VAR_VECTOR3:
            return CalculateCatmullRom(knots[originIndex].GetVector3(), knots[originIndex + 1].GetVector3(),
                knots[originIndex + 2].GetVector3(), knots[originIndex + 3].GetVector3(), t, t2, t3);
        case VAR_VECTOR4:
            return CalculateCatmullRom(knots[originIndex].GetVector4(), knots[originIndex + 1].GetVector4(),
                knots[originIndex + 2].GetVector4(), knots[originIndex + 3].GetVector4(), t, t2, t3);
        case VAR_COLOR:
            return CalculateCatmullRom(knots[originIndex].GetColor(), knots[originIndex + 1].GetColor(),
                knots[originIndex + 2].GetColor(), knots[originIndex + 3].GetColor(), t, t2, t3);
        case VAR_DOUBLE:
            return CalculateCatmullRom(knots[originIndex].GetDouble(), knots[originIndex + 1].GetDouble(),
                knots[originIndex + 2].GetDouble(), knots[originIndex + 3].GetDouble(), t, t2, t3);
        default:
            return Variant::EMPTY;
        }
    }
}

Variant Spline::LinearInterpolation(const Vector<Variant>& knots, float t) const
{
    if (knots.Size() < 2)
        return Variant::EMPTY;
    else
    {
        if (t >= 1.f)
            return knots.Back();

        int originIndex = Clamp((int)(t * (knots.Size() - 1)), 0, (int)(knots.Size() - 2));
        t = fmodf(t * (knots.Size() - 1), 1.f);
        return LinearInterpolation(knots[originIndex], knots[originIndex + 1], t);
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
    case VAR_DOUBLE:
        return Lerp(lhs.GetDouble(), rhs.GetDouble(), t);
    default:
        return Variant::EMPTY;
    }
}

}
