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
#include "Context.h"
#include "Log.h"
#include "Node.h"
#include "Scene.h"
#include "Spline.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* LOGIC_CATEGORY;

static const char* interpolationModeNames[] =
{
    "Bezier",
    0
};

Spline::Spline(Context* context) :
    Component(context),
    interpolationMode_(BEZIER_CURVE),
    speed_(1.f),
    elapsedTime_(0.f),
    length_(0.f),
    traveled_(0.f),
    dirty_(false)
{
}

void Spline::RegisterObject(Context* context)
{
    context->RegisterFactory<Spline>(LOGIC_CATEGORY);

    ATTRIBUTE(Spline, VAR_FLOAT, "Speed", speed_, 1.f, AM_FILE);
    ENUM_ATTRIBUTE(Spline, "Interpolation Mode", interpolationMode_, interpolationModeNames, BEZIER_CURVE, AM_FILE);
    ATTRIBUTE(Spline, VAR_FLOAT, "Traveled", traveled_, 0.f, AM_FILE | AM_NOEDIT);
    ATTRIBUTE(Spline, VAR_FLOAT, "Elapsed Time", elapsedTime_, 0.f, AM_FILE | AM_NOEDIT);
    ACCESSOR_ATTRIBUTE(Spline, VAR_VARIANTVECTOR, "Control Points", GetControlPointsAttr, SetControlPointsAttr, VariantVector, Variant::emptyVariantVector, AM_FILE);
}

void Spline::SetControlPoints(const PODVector<Vector3>& controlPoints)
{
    controlPoints_ = controlPoints;

    // We can calculate the length here because all the control points have changed so it shouldn't be too expensive.
    CalculateLength();
}

void Spline::SetPosition(float factor)
{
    float t = factor;

    if (t < 0.f)
        t = 0.0f;
    else if (t > 1.0f)
        t = 1.0f;

    traveled_ = t;
}

Vector3 Spline::GetPosition() const
{
    return GetPoint(traveled_);
}

Vector3 Spline::GetPoint(float factor) const
{
    float t = factor;

    if (t < 0.f)
        t = 0.0f;
    else if (t > 1.0f)
        t = 1.0f;

    switch (interpolationMode_)
    {
    case BEZIER_CURVE:
        return BezierMove(controlPoints_, t);

    default:
        return Vector3::ZERO;
    }
}

void Spline::Push(const Vector3& controlPoint)
{
    controlPoints_.Push(controlPoint);

    // Calculate the length at the next move so we don't recalculate the entire length multiple times if more than one control point is changed.
    dirty_ = true;
}

void Spline::Pop()
{
    controlPoints_.Pop();

    // Calculate the length at the next move so we don't recalculate the entire length multiple times if more than one control point is changed.
    dirty_ = true;
}

void Spline::Move(float timeStep)
{
    if (dirty_)
        CalculateLength();

    if (traveled_ >= 1.0f || length_ <= 0.0f)
        return;

    elapsedTime_ += timeStep;

    // Calculate where we should be on the spline based on length, speed and time. If that is less than the set traveled_ don't move till caught up.
    float distanceCovered = elapsedTime_ * speed_;
    traveled_ = distanceCovered / length_;

    switch (interpolationMode_)
    {
    case BEZIER_CURVE:
        if (controlPoints_.Size() < 2)
        {
            LOGERRORF("Spline on Node[%d,%s] in Bezier Curve mode attempted with less than two control points.", GetNode()->GetID(), GetNode()->GetName().CString());
            return;
        }
        GetNode()->SetPosition(BezierMove(controlPoints_,traveled_));
        break;
    }
}

void Spline::Reset()
{
    traveled_ = 0.f;
    elapsedTime_ = 0.f;
}

Urho3D::VariantVector Spline::GetControlPointsAttr() const
{
    VariantVector ret;
    // Store number of points first for editing
    ret.Push(controlPoints_.Size());
    for (unsigned i = 0; i < controlPoints_.Size(); i++)
        ret.Push(controlPoints_[i]);
    return ret;
}

void Spline::SetControlPointsAttr(VariantVector value)
{
    controlPoints_.Clear();
    unsigned index = 0;
    unsigned numPoints = index < value.Size() ? value[index++].GetUInt() : 0;
    // Prevent negative value being assigned from the editor
    if (numPoints > M_MAX_INT)
        numPoints = 0;
    for (unsigned i = 0; i < numPoints; ++i)
    {
        Vector3 point = index < value.Size() ? value[index++].GetVector3() : Vector3::ZERO;
        controlPoints_.Push(point);
    }

    CalculateLength();
}

void Spline::CalculateLength()
{
    if (dirty_)
        dirty_ = false;

    length_ = 0.f;

    if (controlPoints_.Size() <= 0)
    {
        return;
    }

    switch (interpolationMode_)
    {
    case BEZIER_CURVE:
        Vector3 a = controlPoints_[0];
        for (float f = 0.000f; f <= 1.000f; f += 0.001f)
        {
            Vector3 b = BezierMove(controlPoints_, f);
            length_ += Abs((a - b).Length());
            a = b;
        }
        break;
    }
}

Vector3 Spline::BezierMove(const PODVector<Vector3>& controlPoints, float t) const
{
    if (controlPoints.Size() == 2)
    {
        return controlPoints[0].Lerp(controlPoints[1], t);
    }
    else
    {
        PODVector<Vector3> newControlPoints;
        for (unsigned i = 1; i < controlPoints.Size(); i++)
        {
            newControlPoints.Push(controlPoints[i - 1].Lerp(controlPoints[i], t));
        }
        return BezierMove(newControlPoints, t);
    }
}

}