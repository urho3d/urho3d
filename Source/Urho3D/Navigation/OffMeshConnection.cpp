//
// Copyright (c) 2008-2016 the Urho3D project.
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

OffMeshConnection::~OffMeshConnection()
{
}

void OffMeshConnection::RegisterObject(Context* context)
{
    context->RegisterFactory<OffMeshConnection>(NAVIGATION_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Endpoint NodeID", int, endPointID_, 0, AM_DEFAULT | AM_NODEID);
    URHO3D_ATTRIBUTE("Radius", float, radius_, DEFAULT_RADIUS, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Bidirectional", bool, bidirectional_, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Flags Mask", unsigned, mask_, DEFAULT_MASK_FLAG, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Area Type", unsigned, areaId_, DEFAULT_AREA, AM_DEFAULT);
}

void OffMeshConnection::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    Serializable::OnSetAttribute(attr, src);

    if (attr.offset_ == offsetof(OffMeshConnection, endPointID_))
        endPointDirty_ = true;
}

void OffMeshConnection::ApplyAttributes()
{
    if (endPointDirty_)
    {
        Scene* scene = GetScene();
        endPoint_ = scene ? scene->GetNode(endPointID_) : (Node*)0;
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
