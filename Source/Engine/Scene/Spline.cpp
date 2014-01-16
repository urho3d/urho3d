//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Timer.h"

namespace Urho3D
{

extern const char* SCENE_CATEGORY;

Spline::Spline(Context* context) :
    Component(context),
    interpolationMode_(BEZIER_CURVE),
    speed_(1.f),
    startTime_(-1.f),
    elapsedTime_(0.f),
    length_(0.f),
    traveled_(0.f),
    attached_(false)
{
}

void Spline::RegisterObject(Context* context)
{
    context->RegisterFactory<Spline>(SCENE_CATEGORY);

    ACCESSOR_ATTRIBUTE(Spline, VAR_VARIANTVECTOR, "Control Points", GetControlPointsAttr, SetControlPointsAttr, VariantVector, Variant::emptyVariantVector, AM_FILE);
    ATTRIBUTE(Spline, VAR_FLOAT, "Speed", speed_, 1.f, AM_FILE);
    ATTRIBUTE(Spline, VAR_INT, "Interpolation Mode", interpolationMode_, BEZIER_CURVE, AM_FILE);
    ATTRIBUTE(Spline, VAR_FLOAT, "Traveled", traveled_, 0.f, AM_FILE | AM_NOEDIT);
    ATTRIBUTE(Spline, VAR_FLOAT, "Start Time", startTime_, -1.f, AM_FILE | AM_NOEDIT);
    ATTRIBUTE(Spline, VAR_FLOAT, "Elapsed Time", elapsedTime_, 0.f, AM_FILE | AM_NOEDIT);
    ATTRIBUTE(Spline, VAR_FLOAT, "Length", length_, 0.f, AM_FILE | AM_NOEDIT);
    ATTRIBUTE(Spline, VAR_BOOL, "Attached", attached_, false, AM_FILE | AM_NOEDIT);
}

void Spline::SetControlPoints(const Vector<Vector3> controlPoints)
{
    controlPoints_ = controlPoints;
}

void Spline::SetInterpolationMode(InterpolationMode interpolationMode)
{
    interpolationMode_ = interpolationMode;
}

void Spline::Push(const Vector3& controlPoint)
{
    controlPoints_.Push(controlPoint);
}

void Spline::Pop()
{
    controlPoints_.Pop();
}

void Spline::Attach()
{
    if (controlPoints_.Size() > 0)
    {
        CalculateLength();

        GetNode()->SetPosition(BezierMove(controlPoints_,traveled_));

        attached_ = true;
    }
}

void Spline::Move()
{
    if (!attached_ || traveled_ >= 1.0f)
        return;

    if (startTime_ <= -1.f)
        startTime_ = GetSubsystem<Time>()->GetElapsedTime();

    elapsedTime_ += GetSubsystem<Time>()->GetElapsedTime() - startTime_;

    float distanceCovered = elapsedTime_ * speed_;
    traveled_ = distanceCovered / length_;

    switch (interpolationMode_)
    {
    case BEZIER_CURVE:
        if (controlPoints_.Size() < 2)
        {
            LOGERRORF("Spline on Node[%d,%s] in Beizer Curve mode attempted with less than two control points.", GetNode()->GetID(), GetNode()->GetName().CString());
            return;
        }
        GetNode()->SetPosition(BezierMove(controlPoints_,traveled_));
        break;
    }
}

void Spline::Detach()
{
    attached_ = false;
    startTime_ = -1.f;
}

void Spline::Reset()
{
    attached_ = false;
    traveled_ = 0.f;
    startTime_ = -1.f;
    elapsedTime_ = 0.f;
}

Urho3D::VariantVector Spline::GetControlPointsAttr() const
{
    VariantVector ret;
    for (unsigned i = 0; i < controlPoints_.Size(); i++)
        ret.Push(controlPoints_[i]);
    return ret;
}

void Spline::SetControlPointsAttr(VariantVector value)
{
    for (unsigned i = 0; i < value.Size(); i++)
        controlPoints_.Push(value[i].GetVector3());
}

void Spline::CalculateLength()
{
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
            length_ += (a - b).Length();
            a = b;
        }
        break;
    }
}

Vector3 Spline::BezierMove(Vector<Vector3>& controlPoints, float t)
{
    if (controlPoints.Size() == 2)
    {
        return controlPoints[0].Lerp(controlPoints[1], t);
    }
    else
    {
        Vector<Vector3> newControlPoints;
        for (unsigned i = 1; i < controlPoints.Size(); i++)
        {
            newControlPoints.Push(controlPoints[i - 1].Lerp(controlPoints[i], t));
        }
        return BezierMove(newControlPoints, t);
    }
}

}