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

#pragma once

#include "Drawable.h"
#include "HashMap.h"
#include "MathDefs.h"
#include "Ptr.h"
#include "Rect.h"
#include "Vector4.h"

class Camera;
class Drawable;
class Geometry;
class Graphics;
class Light;
class Material;
class Matrix3x4;
class Pass;
class Renderer;
class ShaderVariation;
class Texture2D;
class VertexBuffer;
class Zone;
struct LightBatchQueue;

/// Queued 3D geometry draw call.
struct Batch
{
    /// Construct with defaults.
    Batch() :
        lightQueue_(0),
        isBase_(false)
    {
    }
    
    /// Construct from a drawable's source batch.
    Batch(const SourceBatch& rhs) :
        distance_(rhs.distance_),
        geometry_(rhs.geometry_),
        material_(rhs.material_),
        worldTransform_(rhs.worldTransform_),
        lightQueue_(0),
        shaderData_(rhs.shaderData_),
        shaderDataSize_(rhs.shaderDataSize_),
        geometryType_(rhs.geometryType_),
        overrideView_(rhs.overrideView_),
        isBase_(false)
    {
    }
    
    /// Calculate state sorting key, which consists of base pass flag, light, pass and geometry.
    void CalculateSortKey();
    /// Prepare for rendering.
    void Prepare(Graphics* graphics, Renderer* renderer, bool setModelTransform = true) const;
    /// Prepare and draw.
    void Draw(Graphics* graphics, Renderer* renderer) const;
    
    /// State sorting key.
    unsigned long long sortKey_;
    /// Distance from camera.
    float distance_;
    /// Geometry.
    Geometry* geometry_;
    /// Material.
    Material* material_;
    /// %Object's world transform.
    const Matrix3x4* worldTransform_;
    /// Camera.
    Camera* camera_;
    /// Zone.
    Zone* zone_;
    /// Light properties.
    LightBatchQueue* lightQueue_;
    /// Material pass.
    Pass* pass_;
    /// Vertex shader.
    ShaderVariation* vertexShader_;
    /// Pixel shader.
    ShaderVariation* pixelShader_;
    /// Vertex shader data.
    const float* shaderData_;
    /// Vertex shader data size in floats.
    unsigned shaderDataSize_;
    /// %Geometry type.
    GeometryType geometryType_;
    /// Override view transform flag.
    bool overrideView_;
    /// Base batch flag. This tells to draw the object fully without light optimizations.
    bool isBase_;
    /// 8-bit light mask for stencil marking in deferred rendering.
    unsigned char lightMask_;
};

/// Data for one geometry instance.
struct InstanceData
{
    /// Construct undefined.
    InstanceData()
    {
    }
    
    /// Construct with transform and distance.
    InstanceData(const Matrix3x4* worldTransform, float distance) :
        worldTransform_(worldTransform),
        distance_(distance)
    {
    }
    
    /// World transform.
    const Matrix3x4* worldTransform_;
    /// Distance from camera.
    float distance_;
};

/// Instanced 3D geometry draw call.
struct BatchGroup : public Batch
{
    /// Construct with defaults.
    BatchGroup() :
        startIndex_(M_MAX_UNSIGNED)
    {
    }
    
    /// Construct from a batch.
    BatchGroup(const Batch& batch) :
        Batch(batch),
        startIndex_(M_MAX_UNSIGNED)
    {
    }

    /// Destruct.
    ~BatchGroup()
    {
    }
    
    /// Pre-set the instance transforms. Buffer must be big enough to hold all transforms.
    void SetTransforms(Renderer* renderer, void* lockedData, unsigned& freeIndex);
    /// Prepare and draw.
    void Draw(Graphics* graphics, Renderer* renderer) const;
    
    /// Instance data.
    PODVector<InstanceData> instances_;
    /// Instance stream start index, or M_MAX_UNSIGNED if transforms not pre-set.
    unsigned startIndex_;
};

/// Instanced draw call grouping key.
struct BatchGroupKey
{
    /// Construct undefined.
    BatchGroupKey()
    {
    }
    
    /// Construct from a batch.
    BatchGroupKey(const Batch& batch) :
        zone_(batch.zone_),
        lightQueue_(batch.lightQueue_),
        pass_(batch.pass_),
        material_(batch.material_),
        geometry_(batch.geometry_)
    {
    }
    
    /// Zone.
    Zone* zone_;
    /// Light properties.
    LightBatchQueue* lightQueue_;
    /// Material pass.
    Pass* pass_;
    /// Material.
    Material* material_;
    /// Geometry.
    Geometry* geometry_;
    
    /// Test for equality with another batch group key.
    bool operator == (const BatchGroupKey& rhs) const { return zone_ == rhs.zone_ && lightQueue_ == rhs.lightQueue_ && pass_ == rhs.pass_ && material_ == rhs.material_ && geometry_ == rhs.geometry_; }
    /// Test for inequality with another batch group key.
    bool operator != (const BatchGroupKey& rhs) const { return zone_ != rhs.zone_ || lightQueue_ != rhs.lightQueue_ || pass_ != rhs.pass_ || material_ != rhs.material_ || geometry_ != rhs.geometry_; }
    
    /// Return hash value.
    unsigned ToHash() const;
};

/// Queue that contains both instanced and non-instanced draw calls.
struct BatchQueue
{
public:
    /// Clear for new frame by clearing all groups and batches.
    void Clear(int maxSortedInstances);
    /// Sort non-instanced draw calls back to front.
    void SortBackToFront();
    /// Sort instanced and non-instanced draw calls front to back.
    void SortFrontToBack();
    /// Pre-set instance transforms of all groups. The vertex buffer must be big enough to hold all transforms.
    void SetTransforms(Renderer* renderer, void* lockedData, unsigned& freeIndex);
    /// Draw.
    void Draw(Graphics* graphics, Renderer* renderer, bool useScissor = false, bool markToStencil = false) const;
    /// Draw with forward light optimizations.
    void Draw(Light* light, Graphics* graphics, Renderer* renderer) const;
    /// Return the combined amount of instances.
    unsigned GetNumInstances(Renderer* renderer) const;
    /// Return whether the batch group is empty.
    bool IsEmpty() const { return batches_.Empty() && baseBatchGroups_.Empty() && batchGroups_.Empty(); }
    
    /// Instanced draw calls with base flag.
    HashMap<BatchGroupKey, BatchGroup> baseBatchGroups_;
    /// Instanced draw calls.
    HashMap<BatchGroupKey, BatchGroup> batchGroups_;
    /// Unsorted non-instanced draw calls.
    PODVector<Batch> batches_;
    /// Sorted non-instanced draw calls with base flag.
    PODVector<Batch*> sortedBaseBatches_;
    /// Sorted non-instanced draw calls.
    PODVector<Batch*> sortedBatches_;
    /// Sorted instanced draw calls with base flag.
    PODVector<BatchGroup*> sortedBaseBatchGroups_;
    /// Sorted instanced draw calls.
    PODVector<BatchGroup*> sortedBatchGroups_;
    /// Maximum sorted instances.
    unsigned maxSortedInstances_;
};

/// Queue for shadow map draw calls
struct ShadowBatchQueue
{
    /// Shadow map camera.
    Camera* shadowCamera_;
    /// Shadow map viewport.
    IntRect shadowViewport_;
    /// Shadow caster draw calls.
    BatchQueue shadowBatches_;
    /// Directional light cascade near split distance.
    float nearSplit_;
    /// Directional light cascade far split distance.
    float farSplit_;
};

/// Queue for light related draw calls.
struct LightBatchQueue
{
    /// Per-pixel light.
    Light* light_;
    /// Shadow map depth texture.
    Texture2D* shadowMap_;
    /// Lit geometry draw calls.
    BatchQueue litBatches_;
    /// Shadow map split queues.
    Vector<ShadowBatchQueue> shadowSplits_;
    /// Per-vertex lights.
    PODVector<Light*> vertexLights_;
    /// Light volume draw calls.
    PODVector<Batch> volumeBatches_;
};
