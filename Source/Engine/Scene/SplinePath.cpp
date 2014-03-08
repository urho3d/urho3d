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
#include "ForEach.h"
#include "Log.h"
#include "Node.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "SplinePath.h"

namespace Urho3D
{

extern const char* interpolationModeNames[];
extern const char* LOGIC_CATEGORY;

SplinePath::SplinePath(Context* context) :
    Component(context),
    speed_(1.f),
    elapsedTime_(0.f),
    length_(0.f),
    traveled_(0.f),
    spline_(BEZIER_CURVE)
{
    SubscribeToEvent(E_SCENEPOSTUPDATE, HANDLER(SplinePath, PointsUpdated));
}

SplinePath::~SplinePath()
{
    UnsubscribeFromAllEvents();
}

void SplinePath::RegisterObject(Context* context)
{
    context->RegisterFactory<SplinePath>(LOGIC_CATEGORY);

    ATTRIBUTE(SplinePath, VAR_FLOAT, "Speed", speed_, 1.f, AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE(SplinePath, "Interpolation Mode", GetInterpolationMode, SetInterpolationMode, InterpolationMode, interpolationModeNames, BEZIER_CURVE, AM_FILE);
    ATTRIBUTE(SplinePath, VAR_FLOAT, "Traveled", traveled_, 0.f, AM_FILE | AM_NOEDIT);
    ATTRIBUTE(SplinePath, VAR_FLOAT, "Elapsed Time", elapsedTime_, 0.f, AM_FILE | AM_NOEDIT);
}

void SplinePath::ApplyAttributes()
{
    SubscribeToEvent(node_->GetScene(), E_NODEADDED, HANDLER(SplinePath, PointAdded));
    SubscribeToEvent(node_->GetScene(), E_NODEREMOVED, HANDLER(SplinePath, PointRemoved));

    foreach(SharedPtr<Node> child, node_->GetChildren())
        child->AddListener(this);

    UpdatePoints();
    CalculateLength();
}

void SplinePath::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && node_ && IsEnabledEffective())
    {
        if (spline_.GetKnots().Size() > 1)
        {
            Vector3 a = spline_.GetPoint(0.f);
            for (float f = 0.01f; f <= 1.0f; f = f + 0.01f)
            {
                Vector3 b = spline_.GetPoint(f);
                debug->AddLine(a, b, Color::GREEN);
                a = b;
            }
        }

        foreach(SharedPtr<Node> node, node_->GetChildren())
            debug->AddNode(node);
    }
}

void SplinePath::SetInterpolationMode(InterpolationMode interpolationMode) 
{ 
    spline_.SetInterpolationMode(interpolationMode); 
    dirty_ = true;
}

void SplinePath::SetPosition(float factor)
{
    float t = factor;

    if (t < 0.f)
        t = 0.0f;
    else if (t > 1.0f)
        t = 1.0f;

    traveled_ = t;
}

Vector3 SplinePath::GetPosition() const
{
    return GetPoint(traveled_);
}

Vector3 SplinePath::GetPoint(float factor) const
{
    return spline_.GetPoint(factor);
}

void SplinePath::Move(float timeStep)
{
    if (traveled_ >= 1.0f || length_ <= 0.0f)
        return;

    elapsedTime_ += timeStep;

    // Calculate where we should be on the spline based on length, speed and time. If that is less than the set traveled_ don't move till caught up.
    float distanceCovered = elapsedTime_ * speed_;
    traveled_ = distanceCovered / length_;

    GetPoint(traveled_);
}

void SplinePath::Reset()
{
    traveled_ = 0.f;
    elapsedTime_ = 0.f;
}

void SplinePath::OnMarkedDirty(Node* node)
{
    if (node)
        dirty_ = true;
}

void SplinePath::OnNodeSetEnabled(Node* node)
{
    if (node)
        dirty_ = true;
}

void SplinePath::CalculateLength()
{
    if (spline_.GetKnots().Size() <= 0)
        return;

    length_ = 0.f;

    Vector3 a = spline_.GetKnot(0);
    for (float f = 0.000f; f <= 1.000f; f += 0.001f)
    {
        Vector3 b = spline_.GetPoint(f);
        length_ += Abs((a - b).Length());
        a = b;
    }
}

void SplinePath::PointAdded(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeAdded;

    Node* parent = static_cast<Node*>(eventData[P_PARENT].GetPtr());
    Node* child = static_cast<Node*>(eventData[P_NODE].GetPtr());

    if (child != NULL && parent != NULL && parent == node_)
    {
        child->AddListener(this);
        dirty_ = true;
    }
}

void SplinePath::PointRemoved(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeRemoved;

    Node* parent = static_cast<Node*>(eventData[P_PARENT].GetPtr());

    if (parent != NULL && parent == node_)
        dirty_ = true;
}

void SplinePath::PointsUpdated(StringHash eventType, VariantMap& eventData)
{
    if (dirty_)
    {
        UpdatePoints();
        CalculateLength();

        dirty_ = false;
    }
}

void SplinePath::UpdatePoints()
{
    spline_.Clear();

    foreach(SharedPtr<Node> node, node_->GetChildren())
    {
        if (node->IsEnabled())
            spline_.AddKnot(node->GetWorldPosition());
    }
}

}