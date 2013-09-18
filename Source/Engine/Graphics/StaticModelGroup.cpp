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
#include "Batch.h"
#include "Camera.h"
#include "Context.h"
#include "Scene.h"
#include "StaticModelGroup.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;

StaticModelGroup::StaticModelGroup(Context* context) :
    StaticModel(context)
{
}

StaticModelGroup::~StaticModelGroup()
{
}

void StaticModelGroup::RegisterObject(Context* context)
{
    context->RegisterFactory<StaticModelGroup>(GEOMETRY_CATEGORY);

    COPY_BASE_ATTRIBUTES(StaticModelGroup, StaticModel);
    /// \todo Define an attribute for instance node ID's
}

void StaticModelGroup::UpdateBatches(const FrameInfo& frame)
{
    // Getting the world bounding box ensures the transforms are updated
    const BoundingBox& worldBoundingBox = GetWorldBoundingBox();
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    distance_ = frame.camera_->GetDistance(worldBoundingBox.Center());
    
    if (batches_.Size() > 1)
    {
        for (unsigned i = 0; i < batches_.Size(); ++i)
        {
            batches_[i].distance_ = frame.camera_->GetDistance(worldTransform * geometryData_[i].center_);
            batches_[i].worldTransform_ = worldTransforms_.Size() ? &worldTransforms_[0] : &Matrix3x4::IDENTITY;
            batches_[i].numWorldTransforms_ = worldTransforms_.Size();
        }
    }
    else if (batches_.Size() == 1)
    {
        batches_[0].distance_ = distance_;
        batches_[0].worldTransform_ = worldTransforms_.Size() ? &worldTransforms_[0] : &Matrix3x4::IDENTITY;
        batches_[0].numWorldTransforms_ = worldTransforms_.Size();
    }
    
    float scale = worldBoundingBox.Size().DotProduct(DOT_SCALE);
    float newLodDistance = frame.camera_->GetLodDistance(distance_, scale, lodBias_);
    
    if (newLodDistance != lodDistance_)
    {
        lodDistance_ = newLodDistance;
        CalculateLodLevels();
    }
}

void StaticModelGroup::AddInstanceNode(Node* node)
{
    if (!node)
        return;

    WeakPtr<Node> instanceWeak(node);
    if (instanceNodes_.Contains(instanceWeak))
        return;
    
    // Add as a listener for the instance node, so that we know to dirty the transforms when the node moves or is enabled/disabled
    node->AddListener(this);
    instanceNodes_.Push(instanceWeak);
}

void StaticModelGroup::RemoveInstanceNode(Node* node)
{
    if (!node)
        return;

    WeakPtr<Node> instanceWeak(node);
    node->RemoveListener(this);
    instanceNodes_.Remove(instanceWeak);
}

Node* StaticModelGroup::GetInstanceNode(unsigned index) const
{
    return index < instanceNodes_.Size() ? instanceNodes_[index] : (Node*)0;
}

void StaticModelGroup::OnNodeSetEnabled(Node* node)
{
    Drawable::OnMarkedDirty(node);
}

void StaticModelGroup::OnWorldBoundingBoxUpdate()
{
    // Update transforms and bounding box at the same time to have to go through the objects only once
    worldBoundingBox_.defined_ = false;
    worldTransforms_.Resize(instanceNodes_.Size());
    unsigned index = 0;

    for (unsigned i = 0; i < instanceNodes_.Size(); ++i)
    {
        Node* node = instanceNodes_[i];
        if (!node || !node->IsEnabled())
            continue;
        
        const Matrix3x4& worldTransform = node->GetWorldTransform();
        worldTransforms_[index++] = worldTransform;
        worldBoundingBox_.Merge(boundingBox_.Transformed(worldTransform));
    }
    
    worldTransforms_.Resize(index);
}

}
