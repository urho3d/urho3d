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

#include "Precompiled.h"

#include "../Navigation/Obstacle.h"

#include "../Core/Context.h"
#include "../Graphics/DebugRenderer.h"
#include "../Navigation/DynamicNavigationMesh.h"
#include "../IO/Log.h"
#include "../Navigation/NavigationEvents.h"
#include "../Scene/Scene.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* NAVIGATION_CATEGORY;

Obstacle::Obstacle(Context* context) :
    Component(context),
    height_(5.0f),
    radius_(5.0f),
    obstacleId_(0)
{

}

Obstacle::~Obstacle()
{
    if (obstacleId_ > 0 && !ownerMesh_.Expired())
        ownerMesh_.Get()->RemoveObstacle(this);
}

void Obstacle::RegisterObject(Context* context)
{
    context->RegisterFactory<Obstacle>(NAVIGATION_CATEGORY);
    COPY_BASE_ATTRIBUTES(Component);
    ACCESSOR_ATTRIBUTE("Radius", GetRadius, SetRadius, float, 5.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Height", GetHeight, SetHeight, float, 5.0f, AM_DEFAULT);
}

void Obstacle::OnSetEnabled()
{
    bool enabled = IsEnabledEffective();

    if (ownerMesh_)
    {
        if (enabled)
        {
            ownerMesh_.Get()->AddObstacle(this);
        }
        else
        {
            ownerMesh_.Get()->RemoveObstacle(this);
        }
    }
}

void Obstacle::SetHeight(float newHeight)
{
    height_ = newHeight;
    if (ownerMesh_)
        ownerMesh_->ObstacleChanged(this);
    MarkNetworkUpdate();
}

void Obstacle::SetRadius(float newRadius)
{
    radius_ = newRadius;
    if (ownerMesh_)
        ownerMesh_->ObstacleChanged(this);
    MarkNetworkUpdate();
}

void Obstacle::OnNodeSet(Node* node)
{
    if (node)
    {
        if (GetScene() == node)
        {
            LOGWARNING(GetTypeName() + " should not be created to the root scene node");
            return;
        }
        if (ownerMesh_)
            return;
        ownerMesh_ = GetScene()->GetComponent<DynamicNavigationMesh>();
        if (ownerMesh_)
        {
            ownerMesh_.Get()->AddObstacle(this);
        }
    }
}

void Obstacle::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (IsEnabledEffective())
    {
        debug->AddCylinder(node_->GetWorldPosition(), radius_, height_, Color(0.0f, 1.0f, 1.0f), depthTest);
    }
}

void Obstacle::DrawDebugGeometry(bool depthTest)
{
    Scene* scene = GetScene();
    if (scene)
    {
        DebugRenderer* debug = scene->GetComponent<DebugRenderer>();
        if (debug)
            DrawDebugGeometry(debug, depthTest);
    }
}

}