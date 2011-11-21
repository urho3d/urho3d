//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "GraphicsDefs.h"
#include "HashMap.h"
#include "Map.h"
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

/// Description of a 3D geometry draw call.
struct Batch
{
    /// Construct with defaults.
    Batch() :
        lightQueue_(0),
        shaderData_(0),
        shaderDataSize_(0),
        geometryType_(GEOM_STATIC),
        overrideView_(false),
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
    /// Model world transform.
    const Matrix3x4* worldTransform_;
    /// Camera.
    Camera* camera_;
    /// Zone.
    Zone* zone_;
    /// Light properties.
    LightBatchQueue* lightQueue_;
    /// Material.
    Material* material_;
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
    /// Geometry type.
    GeometryType geometryType_;
    /// Override view transform flag.
    bool overrideView_;
    /// Base batch flag. This tells to draw the object fully without light optimizations.
    bool isBase_;
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

/// Instanced draw call key.
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
    
    /// Test if less than another batch group key.
    bool operator < (const BatchGroupKey& rhs) const
    {
        if (zone_ == rhs.zone_)
        {
            if (lightQueue_ == rhs.lightQueue_)
            {
                if (pass_ == rhs.pass_)
                {
                    if (material_ == rhs.material_)
                        return geometry_ < rhs.geometry_;
                    else
                        return material_ < rhs.material_;
                }
                else
                    return pass_ < rhs.pass_;
            }
            else
                return lightQueue_ < rhs.lightQueue_;
        }
        else
            return zone_ < rhs.zone_;
    }
    
    /// Test if greater than another batch group key.
    bool operator > (const BatchGroupKey& rhs) const
    {
        if (zone_ == rhs.zone_)
        {
            if (lightQueue_ == rhs.lightQueue_)
            {
                if (pass_ == rhs.pass_)
                {
                    if (material_ == rhs.material_)
                        return geometry_ > rhs.geometry_;
                    else
                        return material_ > rhs.material_;
                }
                else
                    return pass_ > rhs.pass_;
            }
            else
                return lightQueue_ > rhs.lightQueue_;
        }
        else
            return zone_ > rhs.zone_;
    }
};

/// Queue that contains both instanced and non-instanced draw calls.
struct BatchQueue
{
public:
    /// Clear everything.
    void Clear();
    /// Add a batch.
    void AddBatch(const Batch& batch);
    /// Sort non-instanced draw calls back to front.
    void SortBackToFront();
    /// Sort instanced and non-instanced draw calls front to back.
    void SortFrontToBack();
    /// Pre-set instance transforms of all groups. The vertex buffer must be big enough to hold all transforms.
    void SetTransforms(Renderer* renderer, void* lockedData, unsigned& freeIndex);
    
    /// Return the combined amount of instances.
    unsigned GetNumInstances(Renderer* renderer) const;
    /// Return whether the batch group is empty.
    bool IsEmpty() const { return batches_.Empty() && baseBatchGroups_.Empty() && batchGroups_.Empty(); }
    /// Unsorted non-instanced draw calls.
    PODVector<Batch> batches_;
    /// Instanced draw calls with base flag.
    Map<BatchGroupKey, BatchGroup> baseBatchGroups_;
    /// Instanced draw calls.
    Map<BatchGroupKey, BatchGroup> batchGroups_;
    /// Sorted non-instanced draw calls with base flag.
    PODVector<Batch*> sortedBaseBatches_;
    /// Sorted non-instanced draw calls.
    PODVector<Batch*> sortedBatches_;
    /// Sorted instanced draw calls with base flag.
    PODVector<BatchGroup*> sortedBaseBatchGroups_;
    /// Sorted instanced draw calls.
    PODVector<BatchGroup*> sortedBatchGroups_;
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

/// Queue for light related draw calls
struct LightBatchQueue
{
    /// Per-pixel light.
    Light* light_;
    /// Lit geometry draw calls.
    BatchQueue litBatches_;
    /// Shadow map depth texture.
    Texture2D* shadowMap_;
    /// Shadow map split queues.
    Vector<ShadowBatchQueue> shadowSplits_;
    /// Per-vertex lights.
    PODVector<Light*> vertexLights_;
};
