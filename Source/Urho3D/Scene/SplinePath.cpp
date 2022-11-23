// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../IO/Log.h"
#include "../Scene/Scene.h"
#include "../Scene/SplinePath.h"

namespace Urho3D
{

extern const char* interpolationModeNames[];
extern const char* LOGIC_CATEGORY;

static const StringVector controlPointsStructureElementNames =
{
    "Control Point Count",
    "   NodeID"
};

SplinePath::SplinePath(Context* context) :
    Component(context),
    spline_(BEZIER_CURVE),
    speed_(1.f),
    elapsedTime_(0.f),
    traveled_(0.f),
    length_(0.f),
    dirty_(false),
    controlledIdAttr_(0)
{
    UpdateNodeIds();
}

void SplinePath::RegisterObject(Context* context)
{
    context->RegisterFactory<SplinePath>(LOGIC_CATEGORY);

    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Interpolation Mode", GetInterpolationMode, SetInterpolationMode,
        interpolationModeNames, BEZIER_CURVE, AM_FILE);
    URHO3D_ATTRIBUTE("Speed", speed_, 1.f, AM_FILE);
    URHO3D_ATTRIBUTE("Traveled", traveled_, 0.f, AM_FILE | AM_NOEDIT);
    URHO3D_ATTRIBUTE("Elapsed Time", elapsedTime_, 0.f, AM_FILE | AM_NOEDIT);
    URHO3D_ACCESSOR_ATTRIBUTE("Controlled", GetControlledIdAttr, SetControlledIdAttr, 0, AM_FILE | AM_NODEID);
    URHO3D_ACCESSOR_ATTRIBUTE("Control Points", GetControlPointIdsAttr, SetControlPointIdsAttr,
        Variant::emptyVariantVector, AM_FILE | AM_NODEIDVECTOR)
        .SetMetadata(AttributeMetadata::P_VECTOR_STRUCT_ELEMENTS, controlPointsStructureElementNames);
}

void SplinePath::ApplyAttributes()
{
    if (!dirty_)
        return;

    // Remove all old instance nodes before searching for new. Can not call RemoveAllInstances() as that would modify
    // the ID list on its own
    for (unsigned i = 0; i < controlPoints_.Size(); ++i)
    {
        Node* node = controlPoints_[i];
        if (node)
            node->RemoveListener(this);
    }

    controlPoints_.Clear();
    spline_.Clear();

    Scene* scene = GetScene();

    if (scene)
    {
        // The first index stores the number of IDs redundantly. This is for editing
        for (unsigned i = 1; i < controlPointIdsAttr_.Size(); ++i)
        {
            Node* node = scene->GetNode(controlPointIdsAttr_[i].GetU32());
            if (node)
            {
                WeakPtr<Node> controlPoint(node);
                node->AddListener(this);
                controlPoints_.Push(controlPoint);
                spline_.AddKnot(node->GetWorldPosition());
            }
        }

        Node* node = scene->GetNode(controlledIdAttr_);
        if (node)
        {
            WeakPtr<Node> controlled(node);
            controlledNode_ = controlled;
        }
    }

    CalculateLength();
    dirty_ = false;
}

void SplinePath::DrawDebugGeometry(DebugRenderer* debug, bool /*depthTest*/)
{
    if (debug && node_ && IsEnabledEffective())
    {
        if (spline_.GetKnots().Size() > 1)
        {
            Vector3 a = spline_.GetPoint(0.f).GetVector3();
            for (auto i = 1; i <= 100; ++i)
            {
                Vector3 b = spline_.GetPoint(i / 100.f).GetVector3();
                debug->AddLine(a, b, Color::GREEN);
                a = b;
            }
        }

        for (Vector<WeakPtr<Node>>::ConstIterator i = controlPoints_.Begin(); i != controlPoints_.End(); ++i)
            debug->AddNode(*i);

        if (controlledNode_)
            debug->AddNode(controlledNode_);
    }
}

void SplinePath::AddControlPoint(Node* point, unsigned index)
{
    if (!point)
        return;

    WeakPtr<Node> controlPoint(point);

    point->AddListener(this);
    controlPoints_.Insert(index, controlPoint);
    spline_.AddKnot(point->GetWorldPosition(), index);

    UpdateNodeIds();
    CalculateLength();
}

void SplinePath::RemoveControlPoint(Node* point)
{
    if (!point)
        return;

    WeakPtr<Node> controlPoint(point);

    point->RemoveListener(this);

    for (unsigned i = 0; i < controlPoints_.Size(); ++i)
    {
        if (controlPoints_[i] == controlPoint)
        {
            controlPoints_.Erase(i);
            spline_.RemoveKnot(i);
            break;
        }
    }

    UpdateNodeIds();
    CalculateLength();
}

void SplinePath::ClearControlPoints()
{
    for (unsigned i = 0; i < controlPoints_.Size(); ++i)
    {
        Node* node = controlPoints_[i];
        if (node)
            node->RemoveListener(this);
    }

    controlPoints_.Clear();
    spline_.Clear();

    UpdateNodeIds();
    CalculateLength();
}

void SplinePath::SetControlledNode(Node* controlled)
{
    if (controlled)
        controlledNode_ = WeakPtr<Node>(controlled);
}

void SplinePath::SetInterpolationMode(InterpolationMode interpolationMode)
{
    spline_.SetInterpolationMode(interpolationMode);
    CalculateLength();
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

Vector3 SplinePath::GetPoint(float factor) const
{
    return spline_.GetPoint(factor).GetVector3();
}

void SplinePath::Move(float timeStep)
{
    if (traveled_ >= 1.0f || length_ <= 0.0f || controlledNode_.Null())
        return;

    elapsedTime_ += timeStep;

    // Calculate where we should be on the spline based on length, speed and time. If that is less than the set traveled_ don't move till caught up.
    float distanceCovered = elapsedTime_ * speed_;
    traveled_ = distanceCovered / length_;

    controlledNode_->SetWorldPosition(GetPoint(traveled_));
}

void SplinePath::Reset()
{
    traveled_ = 0.f;
    elapsedTime_ = 0.f;
}

void SplinePath::SetControlPointIdsAttr(const VariantVector& value)
{
    // Just remember the node IDs. They need to go through the SceneResolver, and we actually find the nodes during
    // ApplyAttributes()
    if (value.Size())
    {
        controlPointIdsAttr_.Clear();

        unsigned index = 0;
        unsigned numInstances = value[index++].GetU32();
        // Prevent crash on entering negative value in the editor
        if (numInstances > M_MAX_INT)
            numInstances = 0;

        controlPointIdsAttr_.Push(numInstances);
        while (numInstances--)
        {
            // If vector contains less IDs than should, fill the rest with zeros
            if (index < value.Size())
                controlPointIdsAttr_.Push(value[index++].GetU32());
            else
                controlPointIdsAttr_.Push(0);
        }

        dirty_ = true;
    }
    else
    {
        controlPointIdsAttr_.Clear();
        controlPointIdsAttr_.Push(0);

        dirty_ = true;
    }
}

void SplinePath::SetControlledIdAttr(unsigned value)
{
    if (value > 0 && value < M_MAX_UNSIGNED)
        controlledIdAttr_ = value;

    dirty_ = true;
}

void SplinePath::OnMarkedDirty(Node* point)
{
    if (!point)
        return;

    WeakPtr<Node> controlPoint(point);

    for (unsigned i = 0; i < controlPoints_.Size(); ++i)
    {
        if (controlPoints_[i] == controlPoint)
        {
            spline_.SetKnot(point->GetWorldPosition(), i);
            break;
        }
    }

    CalculateLength();
}

void SplinePath::OnNodeSetEnabled(Node* point)
{
    if (!point)
        return;

    WeakPtr<Node> controlPoint(point);

    for (unsigned i = 0; i < controlPoints_.Size(); ++i)
    {
        if (controlPoints_[i] == controlPoint)
        {
            if (point->IsEnabled())
                spline_.AddKnot(point->GetWorldPosition(), i);
            else
                spline_.RemoveKnot(i);

            break;
        }
    }

    CalculateLength();
}

void SplinePath::UpdateNodeIds()
{
    unsigned numInstances = controlPoints_.Size();

    controlPointIdsAttr_.Clear();
    controlPointIdsAttr_.Push(numInstances);

    for (unsigned i = 0; i < numInstances; ++i)
    {
        Node* node = controlPoints_[i];
        controlPointIdsAttr_.Push(node ? node->GetID() : 0);
    }
}

void SplinePath::CalculateLength()
{
    if (spline_.GetKnots().Size() <= 0)
        return;

    length_ = 0.f;

    Vector3 a = spline_.GetKnot(0).GetVector3();
    for (auto i = 0; i <= 1000; ++i)
    {
        Vector3 b = spline_.GetPoint(i / 1000.f).GetVector3();
        length_ += Abs((a - b).Length());
        a = b;
    }
}

}
