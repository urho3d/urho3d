//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Geometry.h"
#include "Model.h"
#include "Node.h"
#include "PhysicsUtils.h"
#include "PhysicsWorld.h"
#include "ResourceCache.h"
#include "HeightfieldShape.h"

#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"

HeightfieldData::HeightfieldData(Model* model, unsigned lodLevel, IntVector2 numPoints)
{
    modelName_ = model->GetName();
    
    const Vector<Vector<SharedPtr<Geometry> > >& geometries = model->GetGeometries();
    
    if (!geometries.Size())
        return;
    
    lodLevel = Clamp(lodLevel, 0, geometries[0].Size());
    
    Geometry* geom = geometries[0][lodLevel];
    if (!geom)
        return;
    
    const unsigned char* vertexData;
    const unsigned char* indexData;
    unsigned vertexSize;
    unsigned indexSize;
    
    geom->GetRawData(vertexData, vertexSize, indexData, indexSize);
    if (!vertexData || !indexData)
        return;
    
    unsigned indexStart = geom->GetIndexStart();
    unsigned indexCount = geom->GetIndexCount();
    
    // If X & Z size not specified, try to guess them
    if (numPoints == IntVector2::ZERO)
        numPoints.x_ = numPoints.y_ = (int)sqrtf((float)geom->GetVertexCount());
    else
    {
        numPoints.x_ = Max(numPoints.x_, 2);
        numPoints.y_ = Max(numPoints.y_, 2);
    }
    
    unsigned dataSize = numPoints.x_ * numPoints.y_;
    numPoints_ = numPoints;
    
    // Then allocate the heightfield
    BoundingBox box = model->GetBoundingBox();
    heightData_ = new float[dataSize];
    
    // Calculate spacing from model's bounding box
    xSpacing_ = (box.max_.x_ - box.min_.x_) / (numPoints.x_ - 1);
    zSpacing_ = (box.max_.z_ - box.min_.z_) / (numPoints.y_ - 1);
    
    // Initialize the heightfield with minimum height
    for (unsigned i = 0; i < dataSize; ++i)
        heightData_[i] = box.min_.y_;
    
    unsigned vertexStart = geom->GetVertexStart();
    unsigned vertexCount = geom->GetVertexCount();
    
    // Now go through vertex data and fit the vertices into the heightfield
    for (unsigned i = vertexStart; i < vertexStart + vertexCount; ++i)
    {
        const Vector3& vertex = *((const Vector3*)(&vertexData[i * vertexSize]));
        int x = (int)((vertex.x_ - box.min_.x_) / xSpacing_ + 0.25f);
        int z = (int)((vertex.z_ - box.min_.z_) / zSpacing_ + 0.25f);
        if (x >= numPoints.x_)
            x = numPoints.x_ - 1;
        if (z >= numPoints.y_)
            z = numPoints.y_ - 1;
        if (vertex.y_ > heightData_[z * numPoints.x_ + x])
            heightData_[z * numPoints.x_ + x] = vertex.y_;
    }
}

HeightfieldData::~HeightfieldData()
{
}

OBJECTTYPESTATIC(HeightfieldShape);

HeightfieldShape::HeightfieldShape(Context* context) :
    CollisionShape(context),
    numPoints_(IntVector2::ZERO),
    size_(Vector3::ONE),
    lodLevel_(0),
    flipEdges_(false)
{
}

HeightfieldShape::~HeightfieldShape()
{
    // Release shape first before letting go of the geometry
    ReleaseShape();
    
    geometry_.Reset();
    if (physicsWorld_)
        physicsWorld_->CleanupGeometryCache();
}

void HeightfieldShape::RegisterObject(Context* context)
{
    context->RegisterFactory<HeightfieldShape>();
    
    ACCESSOR_ATTRIBUTE(HeightfieldShape, VAR_RESOURCEREF, "Model", GetModelAttr, SetModelAttr, ResourceRef, ResourceRef(Model::GetTypeStatic()), AM_DEFAULT);
    ATTRIBUTE(HeightfieldShape, VAR_INT, "LOD Level", lodLevel_, 0, AM_DEFAULT);
    ATTRIBUTE(HeightfieldShape, VAR_INT, "Num Points X", numPoints_.x_, 0, AM_DEFAULT);
    ATTRIBUTE(HeightfieldShape, VAR_INT, "Num Points Z", numPoints_.y_, 0, AM_DEFAULT);
    ATTRIBUTE(HeightfieldShape, VAR_VECTOR3, "Offset Position", position_, Vector3::ZERO, AM_DEFAULT);
    ATTRIBUTE(HeightfieldShape, VAR_QUATERNION, "Offset Rotation", rotation_, Quaternion::IDENTITY, AM_DEFAULT);
    ATTRIBUTE(HeightfieldShape, VAR_VECTOR3, "Size", size_, Vector3::ONE, AM_DEFAULT);
    ATTRIBUTE(HeightfieldShape, VAR_BOOL, "Flip Edges", flipEdges_, false, AM_DEFAULT);
}

void HeightfieldShape::SetModel(Model* model)
{
    if (model != model_)
    {
        model_ = model;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void HeightfieldShape::SetLodLevel(unsigned lodLevel)
{
    if (lodLevel != lodLevel_)
    {
        lodLevel_ = lodLevel;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void HeightfieldShape::SetNumPoints(const IntVector2& numPoints)
{
    if (numPoints != numPoints_)
    {
        numPoints_ = numPoints;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void HeightfieldShape::SetSize(const Vector3& size)
{
    if (size != size_)
    {
        size_ = size;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

void HeightfieldShape::SetFlipEdges(bool enable)
{
    if (enable != flipEdges_)
    {
        flipEdges_ = enable;
        UpdateCollisionShape();
        NotifyRigidBody();
    }
}

Model* HeightfieldShape::GetModel() const
{
    return model_;
}

void HeightfieldShape::SetModelAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    model_ = cache->GetResource<Model>(value.id_);
    dirty_ = true;
}

ResourceRef HeightfieldShape::GetModelAttr() const
{
    return GetResourceRef(model_, Model::GetTypeStatic());
}

void HeightfieldShape::OnMarkedDirty(Node* node)
{
    Vector3 newWorldScale = node_->GetWorldScale();
    if (newWorldScale != cachedWorldScale_)
    {
        if (shape_ && geometry_)
        {
            shape_->setLocalScaling(ToBtVector3(newWorldScale * Vector3(geometry_->xSpacing_, 1.0f, geometry_->zSpacing_)
                * size_));
            NotifyRigidBody();
        }
        
        cachedWorldScale_ = newWorldScale;
    }
}

void HeightfieldShape::UpdateCollisionShape()
{
    ReleaseShape();
    
    if (node_ && model_ && physicsWorld_)
    {
        // Check the geometry cache
        String id = model_->GetName() + "_" + String(lodLevel_) + String(numPoints_) + "_" + String(flipEdges_);
        
        Map<String, SharedPtr<HeightfieldData> >& cache = physicsWorld_->GetHeightfieldCache();
        Map<String, SharedPtr<HeightfieldData> >::Iterator j = cache.Find(id);
        if (j != cache.End())
            geometry_ = j->second_;
        else
        {
            geometry_ = new HeightfieldData(model_, lodLevel_, numPoints_);
            cache[id] = geometry_;
        }
        
        shape_ = new btHeightfieldTerrainShape(geometry_->numPoints_.x_, geometry_->numPoints_.y_, geometry_->heightData_.Get(),
            1.0f, geometry_->boundingBox_.min_.y_, geometry_->boundingBox_.max_.y_, 1, PHY_FLOAT, flipEdges_);
        shape_->setLocalScaling(ToBtVector3(node_->GetWorldScale() * Vector3(geometry_->xSpacing_, 1.0f, geometry_->zSpacing_)
            * size_));
    }
    else
        geometry_.Reset();
    
    if (physicsWorld_)
        physicsWorld_->CleanupGeometryCache();
}

