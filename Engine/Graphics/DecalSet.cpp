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
#include "Batch.h"
#include "Camera.h"
#include "Context.h"
#include "DecalSet.h"
#include "Geometry.h"
#include "Graphics.h"
#include "Log.h"
#include "Node.h"
#include "Profiler.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

static const Vector3 DOT_SCALE(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);
static const unsigned DEFAULT_MAX_VERTICES = 256;

void Decal::CalculateBoundingBox()
{
    boundingBox_.Clear();
    for (unsigned i = 0; i < vertices_.Size(); ++i)
        boundingBox_.Merge(vertices_[i].position_);
}

OBJECTTYPESTATIC(DecalSet);

DecalSet::DecalSet(Context* context) :
    Drawable(context),
    geometry_(new Geometry(context)),
    vertexBuffer_(new VertexBuffer(context_)),
    numVertices_(0),
    maxVertices_(DEFAULT_MAX_VERTICES),
    bufferSizeDirty_(true),
    bufferDirty_(true),
    boundingBoxDirty_(true)
{
    drawableFlags_ = DRAWABLE_GEOMETRY;
    
    geometry_->SetVertexBuffer(0, vertexBuffer_, MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1);
    
    batches_.Resize(1);
    batches_[0].geometry_ = geometry_;
}

DecalSet::~DecalSet()
{
}

void DecalSet::RegisterObject(Context* context)
{
    context->RegisterFactory<DecalSet>();
    
    /// \todo Register attributes
}

void DecalSet::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    // Do not return raycast hits
}

void DecalSet::UpdateBatches(const FrameInfo& frame)
{
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    distance_ = frame.camera_->GetDistance(worldTransform.Translation());
    
    float scale = GetWorldBoundingBox().Size().DotProduct(DOT_SCALE);
    lodDistance_ = frame.camera_->GetLodDistance(distance_, scale, lodBias_);
    
    batches_[0].distance_ = distance_;
    batches_[0].worldTransform_ = &worldTransform;
}

void DecalSet::UpdateGeometry(const FrameInfo& frame)
{
    if (bufferSizeDirty_ || vertexBuffer_->IsDataLost())
        UpdateBufferSize();
    
    if (bufferDirty_)
        UpdateVertexBuffer();
}

UpdateGeometryType DecalSet::GetUpdateGeometryType()
{
    if (bufferDirty_ || bufferSizeDirty_ || vertexBuffer_->IsDataLost())
        return UPDATE_MAIN_THREAD;
    else
        return UPDATE_NONE;
}

void DecalSet::SetMaterial(Material* material)
{
    batches_[0].material_ = material;
    MarkNetworkUpdate();
}

void DecalSet::SetMaxVertices(unsigned num)
{
    if (num != maxVertices_)
    {
        bufferSizeDirty_ = true;
        maxVertices_ = num;
        
        while (decals_.Size() && numVertices_ > maxVertices_)
            RemoveDecals(1);
    }
}

bool DecalSet::AddDecal(Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, const BoundingBox& size, float depthBias, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive)
{
    PROFILE(AddDecal);
    
    if (!node_)
        return false;
        
    if (!target)
    {
        LOGERROR("Null target drawable for decal");
        return false;
    }
    
    Matrix3x4 worldToLocal = node_->GetWorldTransform().Inverse();
    
    Vector3 topLeft = worldToLocal * (worldPosition + worldRotation * (Vector3::UP * size.max_.y_ + Vector3::RIGHT * size.min_.x_));
    Vector3 topRight = worldToLocal * (worldPosition + worldRotation * (Vector3::UP * size.max_.y_ + Vector3::RIGHT * size.max_.x_));
    Vector3 bottomLeft = worldToLocal * (worldPosition + worldRotation * (Vector3::UP * size.min_.y_ + Vector3::RIGHT * size.min_.x_));
    Vector3 bottomRight = worldToLocal * (worldPosition + worldRotation * (Vector3::UP * size.min_.y_ + Vector3::RIGHT * size.max_.x_));
    
    decals_.Resize(decals_.Size() + 1);
    Decal& newDecal = decals_.Back();
    newDecal.timeToLive_ = timeToLive;
    
    /// \todo Wrap decal around target geometry, use depth bias parameter
    newDecal.vertices_.Push(DecalVertex(topLeft, Vector3::UP, topLeftUV));
    newDecal.vertices_.Push(DecalVertex(topRight, Vector3::UP, Vector2(bottomRightUV.x_, topLeftUV.y_)));
    newDecal.vertices_.Push(DecalVertex(bottomLeft, Vector3::UP, Vector2(topLeftUV.x_, bottomRightUV.y_)));
    newDecal.vertices_.Push(DecalVertex(topRight, Vector3::UP, Vector2(bottomRightUV.x_, topLeftUV.y_)));
    newDecal.vertices_.Push(DecalVertex(bottomRight, Vector3::UP, bottomRightUV));
    newDecal.vertices_.Push(DecalVertex(bottomLeft, Vector3::UP, Vector2(topLeftUV.x_, bottomRightUV.y_)));
    newDecal.CalculateBoundingBox();
    
    numVertices_ += newDecal.vertices_.Size();
    // Remove oldest decals if total vertices exceeded
    while (decals_.Size() && numVertices_ > maxVertices_)
        RemoveDecals(1);
    
    MarkDecalsDirty();
    return true;
}

void DecalSet::RemoveDecals(unsigned num)
{
    while (decals_.Size() && num)
    {
        RemoveDecal(decals_.Begin());
        --num;
    }
}

void DecalSet::RemoveAllDecals()
{
    if (!decals_.Empty())
    {
        decals_.Clear();
        numVertices_ = 0;
        MarkDecalsDirty();
    }
}

Material* DecalSet::GetMaterial() const
{
    return batches_[0].material_;
}

void DecalSet::OnNodeSet(Node* node)
{
    Drawable::OnNodeSet(node);
    
    if (node)
    {
        Scene* scene = GetScene();
        if (scene)
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(DecalSet, HandleScenePostUpdate));
    }
}

void DecalSet::OnWorldBoundingBoxUpdate()
{
    if (boundingBoxDirty_)
        CalculateBoundingBox();
    
    worldBoundingBox_ = boundingBox_.Transformed(node_->GetWorldTransform());
}

List<Decal>::Iterator DecalSet::RemoveDecal(List<Decal>::Iterator i)
{
    numVertices_ -= i->vertices_.Size();
    MarkDecalsDirty();
    return decals_.Erase(i);
}

void DecalSet::MarkDecalsDirty()
{
    if (!boundingBoxDirty_)
    {
        boundingBoxDirty_ = true;
        OnMarkedDirty(node_);
    }
    bufferDirty_ = true;
}

void DecalSet::CalculateBoundingBox()
{
    boundingBox_.Clear();
    for (List<Decal>::ConstIterator i = decals_.Begin(); i != decals_.End(); ++i)
        boundingBox_.Merge(i->boundingBox_);
    
    boundingBoxDirty_ = false;
}

void DecalSet::UpdateBufferSize()
{
    if (vertexBuffer_->GetVertexCount() != maxVertices_)
    {
        vertexBuffer_->SetSize(maxVertices_, MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1);
        bufferDirty_ = true;
    }
    
    bufferSizeDirty_ = false;
}

void DecalSet::UpdateVertexBuffer()
{
    geometry_->SetDrawRange(TRIANGLE_LIST, 0, 0, 0, numVertices_);
    float* dest = (float*)vertexBuffer_->Lock(0, numVertices_);
    if (dest)
    {
        for (List<Decal>::ConstIterator i = decals_.Begin(); i != decals_.End(); ++i)
        {
            for (unsigned j = 0; j < i->vertices_.Size(); ++j)
            {
                const DecalVertex& vertex = i->vertices_[j];
                *dest++ = vertex.position_.x_;
                *dest++ = vertex.position_.y_;
                *dest++ = vertex.position_.z_;
                *dest++ = vertex.normal_.x_;
                *dest++ = vertex.normal_.y_;
                *dest++ = vertex.normal_.z_;
                *dest++ = vertex.texCoord_.x_;
                *dest++ = vertex.texCoord_.y_;
            }
        }
        
        vertexBuffer_->Unlock();
    }
    
    vertexBuffer_->ClearDataLost();
    bufferDirty_ = false;
}

void DecalSet::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    
    for (List<Decal>::Iterator i = decals_.Begin(); i != decals_.End();)
    {
        i->timer_ += timeStep;
        
        // Remove the decal if time to live expired
        if (i->timeToLive_ > 0.0f && i->timer_ > i->timeToLive_)
            i = RemoveDecal(i);
        else
            ++i;
    }
}
