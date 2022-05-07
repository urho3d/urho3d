// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Graphics/DebugRenderer.h"
#include "../Navigation/OffMeshConnection.h"
#include "../Scene/Scene.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* NAVIGATION_CATEGORY;

static const float DEFAULT_RADIUS = 1.0f;
static const unsigned DEFAULT_MASK_FLAG = 1;
static const unsigned DEFAULT_AREA = 1;

OffMeshConnection::OffMeshConnection(Context* context) :
    Component(context),
    endPointID_(0),
    radius_(DEFAULT_RADIUS),
    bidirectional_(true),
    endPointDirty_(false),
    mask_(DEFAULT_MASK_FLAG),
    areaId_(DEFAULT_AREA)
{
}

OffMeshConnection::~OffMeshConnection() = default;

void OffMeshConnection::RegisterObject(Context* context)
{
    context->RegisterFactory<OffMeshConnection>(NAVIGATION_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE_EX("Endpoint NodeID", int, endPointID_, MarkEndPointDirty, 0, AM_DEFAULT | AM_NODEID);
    URHO3D_ATTRIBUTE("Radius", float, radius_, DEFAULT_RADIUS, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Bidirectional", bool, bidirectional_, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Flags Mask", unsigned, mask_, DEFAULT_MASK_FLAG, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Area Type", unsigned, areaId_, DEFAULT_AREA, AM_DEFAULT);
}

void OffMeshConnection::ApplyAttributes()
{
    if (endPointDirty_)
    {
        Scene* scene = GetScene();
        endPoint_ = scene ? scene->GetNode(endPointID_) : nullptr;
        endPointDirty_ = false;
    }
}

void OffMeshConnection::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (!node_ || !endPoint_)
        return;

    Vector3 start = node_->GetWorldPosition();
    Vector3 end = endPoint_->GetWorldPosition();

    debug->AddSphere(Sphere(start, radius_), Color::WHITE, depthTest);
    debug->AddSphere(Sphere(end, radius_), Color::WHITE, depthTest);
    debug->AddLine(start, end, Color::WHITE, depthTest);
}

void OffMeshConnection::SetRadius(float radius)
{
    radius_ = radius;
    MarkNetworkUpdate();
}

void OffMeshConnection::SetBidirectional(bool enabled)
{
    bidirectional_ = enabled;
    MarkNetworkUpdate();
}

void OffMeshConnection::SetMask(unsigned newMask)
{
    mask_ = newMask;
    MarkNetworkUpdate();
}

void OffMeshConnection::SetAreaID(unsigned newAreaID)
{
    areaId_ = newAreaID;
    MarkNetworkUpdate();
}

void OffMeshConnection::SetEndPoint(Node* node)
{
    endPoint_ = node;
    endPointID_ = node ? node->GetID() : 0;
    MarkNetworkUpdate();
}

Node* OffMeshConnection::GetEndPoint() const
{
    return endPoint_;
}

}
