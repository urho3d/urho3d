// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/Ptr.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/Material.h"
#include "../Math/MathDefs.h"
#include "../Math/Matrix3x4.h"
#include "../Math/Rect.h"

namespace Urho3D
{

class Camera;
class Drawable;
class Geometry;
class Light;
class Material;
class Matrix3x4;
class Pass;
class ShaderVariation;
class Texture2D;
class VertexBuffer;
class View;
class Zone;
struct LightBatchQueue;

/// Queued 3D geometry draw call.
struct Batch
{
    /// Construct with defaults.
    Batch() = default;

    /// Construct from a drawable's source batch.
    explicit Batch(const SourceBatch& rhs) :
        distance_(rhs.distance_),
        renderOrder_(rhs.material_ ? rhs.material_->GetRenderOrder() : DEFAULT_RENDER_ORDER),
        isBase_(false),
        geometry_(rhs.geometry_),
        material_(rhs.material_),
        worldTransform_(rhs.worldTransform_),
        numWorldTransforms_(rhs.numWorldTransforms_),
        instancingData_(rhs.instancingData_),
        lightQueue_(nullptr),
        geometryType_(rhs.geometryType_)
    {
    }

    /// Calculate state sorting key, which consists of base pass flag, light, pass and geometry.
    void CalculateSortKey();
    /// Prepare for rendering.
    void Prepare(View* view, Camera* camera, bool setModelTransform, bool allowDepthWrite) const;
    /// Prepare and draw.
    void Draw(View* view, Camera* camera, bool allowDepthWrite) const;

    /// State sorting key.
    hash64 sortKey_{};
    /// Distance from camera.
    float distance_{};
    /// 8-bit render order modifier from material.
    i8 renderOrder_{};
    /// 8-bit light mask for stencil marking in deferred rendering.
    unsigned char lightMask_{};
    /// Base batch flag. This tells to draw the object fully without light optimizations.
    bool isBase_{};
    /// Geometry.
    Geometry* geometry_{};
    /// Material.
    Material* material_{};
    /// World transform(s). For a skinned model, these are the bone transforms.
    const Matrix3x4* worldTransform_{};
    /// Number of world transforms.
    i32 numWorldTransforms_{};
    /// Per-instance data. If not null, must contain enough data to fill instancing buffer.
    void* instancingData_{};
    /// Zone.
    Zone* zone_{};
    /// Light properties.
    LightBatchQueue* lightQueue_{};
    /// Material pass.
    Pass* pass_{};
    /// Vertex shader.
    ShaderVariation* vertexShader_{};
    /// Pixel shader.
    ShaderVariation* pixelShader_{};
    /// %Geometry type.
    GeometryType geometryType_{};
};

/// Data for one geometry instance.
struct InstanceData
{
    /// Construct undefined.
    InstanceData() = default;

    /// Construct with transform, instancing data and distance.
    InstanceData(const Matrix3x4* worldTransform, const void* instancingData, float distance) :
        worldTransform_(worldTransform),
        instancingData_(instancingData),
        distance_(distance)
    {
    }

    /// World transform.
    const Matrix3x4* worldTransform_{};
    /// Instancing data buffer.
    const void* instancingData_{};
    /// Distance from camera.
    float distance_{};
};

/// Instanced 3D geometry draw call.
struct BatchGroup : public Batch
{
    /// Construct with defaults.
    BatchGroup() :
        startIndex_(NINDEX)
    {
    }

    /// Construct from a batch.
    explicit BatchGroup(const Batch& batch) :
        Batch(batch),
        startIndex_(NINDEX)
    {
    }

    /// Destruct.
    ~BatchGroup() = default;

    /// Add world transform(s) from a batch.
    void AddTransforms(const Batch& batch)
    {
        InstanceData newInstance;
        newInstance.distance_ = batch.distance_;
        newInstance.instancingData_ = batch.instancingData_;

        for (i32 i = 0; i < batch.numWorldTransforms_; ++i)
        {
            newInstance.worldTransform_ = &batch.worldTransform_[i];
            instances_.Push(newInstance);
        }
    }

    /// Pre-set the instance data. Buffer must be big enough to hold all data.
    void SetInstancingData(void* lockedData, i32 stride, i32& freeIndex);
    /// Prepare and draw.
    void Draw(View* view, Camera* camera, bool allowDepthWrite) const;

    /// Instance data.
    Vector<InstanceData> instances_;
    /// Instance stream start index, or NINDEX if transforms not pre-set.
    i32 startIndex_;
};

/// Instanced draw call grouping key.
struct BatchGroupKey
{
    /// Construct undefined.
    BatchGroupKey() = default;

    /// Construct from a batch.
    explicit BatchGroupKey(const Batch& batch) :
        zone_(batch.zone_),
        lightQueue_(batch.lightQueue_),
        pass_(batch.pass_),
        material_(batch.material_),
        geometry_(batch.geometry_),
        renderOrder_(batch.renderOrder_)
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
    /// 8-bit render order modifier from material.
    i8 renderOrder_;

    /// Test for equality with another batch group key.
    bool operator ==(const BatchGroupKey& rhs) const
    {
        return zone_ == rhs.zone_ && lightQueue_ == rhs.lightQueue_ && pass_ == rhs.pass_ && material_ == rhs.material_ &&
               geometry_ == rhs.geometry_ && renderOrder_ == rhs.renderOrder_;
    }

    /// Test for inequality with another batch group key.
    bool operator !=(const BatchGroupKey& rhs) const
    {
        return zone_ != rhs.zone_ || lightQueue_ != rhs.lightQueue_ || pass_ != rhs.pass_ || material_ != rhs.material_ ||
               geometry_ != rhs.geometry_ || renderOrder_ != rhs.renderOrder_;
    }

    /// Return hash value.
    hash32 ToHash() const;
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
    /// Sort batches front to back while also maintaining state sorting.
    void SortFrontToBack2Pass(Vector<Batch*>& batches);
    /// Pre-set instance data of all groups. The vertex buffer must be big enough to hold all data.
    void SetInstancingData(void* lockedData, i32 stride, i32& freeIndex);
    /// Draw.
    void Draw(View* view, Camera* camera, bool markToStencil, bool usingLightOptimization, bool allowDepthWrite) const;
    /// Return the combined amount of instances.
    i32 GetNumInstances() const;

    /// Return whether the batch group is empty.
    bool IsEmpty() const { return batches_.Empty() && batchGroups_.Empty(); }

    /// Instanced draw calls.
    HashMap<BatchGroupKey, BatchGroup> batchGroups_;
    /// Shader remapping table for 2-pass state and distance sort.
    HashMap<hash32, hash32> shaderRemapping_;
    /// Material remapping table for 2-pass state and distance sort.
    HashMap<hash16, hash16> materialRemapping_;
    /// Geometry remapping table for 2-pass state and distance sort.
    HashMap<hash16, hash16> geometryRemapping_;

    /// Unsorted non-instanced draw calls.
    Vector<Batch> batches_;
    /// Sorted non-instanced draw calls.
    Vector<Batch*> sortedBatches_;
    /// Sorted instanced draw calls.
    Vector<BatchGroup*> sortedBatchGroups_;
    /// Maximum sorted instances.
    i32 maxSortedInstances_;
    /// Whether the pass command contains extra shader defines.
    bool hasExtraDefines_;
    /// Vertex shader extra defines.
    String vsExtraDefines_;
    /// Pixel shader extra defines.
    String psExtraDefines_;
    /// Hash for vertex shader extra defines.
    StringHash vsExtraDefinesHash_;
    /// Hash for pixel shader extra defines.
    StringHash psExtraDefinesHash_;
};

/// Queue for shadow map draw calls.
struct ShadowBatchQueue
{
    /// Shadow map camera.
    Camera* shadowCamera_{};
    /// Shadow map viewport.
    IntRect shadowViewport_;
    /// Shadow caster draw calls.
    BatchQueue shadowBatches_;
    /// Directional light cascade near split distance.
    float nearSplit_{};
    /// Directional light cascade far split distance.
    float farSplit_{};
};

/// Queue for light related draw calls.
struct LightBatchQueue
{
    /// Per-pixel light.
    Light* light_;
    /// Light negative flag.
    bool negative_;
    /// Shadow map depth texture.
    Texture2D* shadowMap_;
    /// Lit geometry draw calls, base (replace blend mode).
    BatchQueue litBaseBatches_;
    /// Lit geometry draw calls, non-base (additive).
    BatchQueue litBatches_;
    /// Shadow map split queues.
    Vector<ShadowBatchQueue> shadowSplits_;
    /// Per-vertex lights.
    Vector<Light*> vertexLights_;
    /// Light volume draw calls.
    Vector<Batch> volumeBatches_;
};

}
