// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Graphics/Model.h"
#include "../Graphics/Skeleton.h"
#include "../Graphics/StaticModel.h"

namespace Urho3D
{

class Animation;
class AnimationState;

/// Animated model component.
class URHO3D_API AnimatedModel : public StaticModel
{
    URHO3D_OBJECT(AnimatedModel, StaticModel);

    friend class AnimationState;

public:
    /// Construct.
    explicit AnimatedModel(Context* context);
    /// Destruct.
    ~AnimatedModel() override;
    /// Register object factory. Drawable must be registered first.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Load from binary data. Return true if successful.
    bool Load(Deserializer& source) override;
    /// Load from XML data. Return true if successful.
    bool LoadXML(const XMLElement& source) override;
    /// Load from JSON data. Return true if successful.
    bool LoadJSON(const JSONValue& source) override;
    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    void ApplyAttributes() override;
    /// Process octree raycast. May be called from a worker thread.
    void ProcessRayQuery(const RayOctreeQuery& query, Vector<RayQueryResult>& results) override;
    /// Update before octree reinsertion. Is called from a worker thread.
    void Update(const FrameInfo& frame) override;
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    void UpdateBatches(const FrameInfo& frame) override;
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update).
    void UpdateGeometry(const FrameInfo& frame) override;
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    UpdateGeometryType GetUpdateGeometryType() override;
    /// Visualize the component as debug geometry.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    /// Set model.
    void SetModel(Model* model, bool createBones = true);
    /// Add an animation.
    AnimationState* AddAnimationState(Animation* animation);
    /// Remove an animation by animation pointer.
    void RemoveAnimationState(Animation* animation);
    /// Remove an animation by animation name.
    void RemoveAnimationState(const String& animationName);
    /// Remove an animation by animation name hash.
    void RemoveAnimationState(StringHash animationNameHash);
    /// Remove an animation by AnimationState pointer.
    void RemoveAnimationState(AnimationState* state);
    /// Remove an animation by index.
    void RemoveAnimationState(unsigned index);
    /// Remove all animations.
    void RemoveAllAnimationStates();
    /// Set animation LOD bias.
    /// @property
    void SetAnimationLodBias(float bias);
    /// Set whether to update animation and the bounding box when not visible. Recommended to enable for physically controlled models like ragdolls.
    /// @property
    void SetUpdateInvisible(bool enable);
    /// Set vertex morph weight by index.
    void SetMorphWeight(unsigned index, float weight);
    /// Set vertex morph weight by name.
    /// @property{set_morphWeights}
    void SetMorphWeight(const String& name, float weight);
    /// Set vertex morph weight by name hash.
    void SetMorphWeight(StringHash nameHash, float weight);
    /// Reset all vertex morphs to zero.
    void ResetMorphWeights();
    /// Apply all animation states to nodes.
    void ApplyAnimation();

    /// Return skeleton.
    /// @property
    Skeleton& GetSkeleton() { return skeleton_; }

    /// Return all animation states.
    const Vector<SharedPtr<AnimationState>>& GetAnimationStates() const { return animationStates_; }

    /// Return number of animation states.
    /// @property
    unsigned GetNumAnimationStates() const { return animationStates_.Size(); }

    /// Return animation state by animation pointer.
    AnimationState* GetAnimationState(Animation* animation) const;
    /// Return animation state by animation name.
    /// @property{get_animationStates}
    AnimationState* GetAnimationState(const String& animationName) const;
    /// Return animation state by animation name hash.
    AnimationState* GetAnimationState(StringHash animationNameHash) const;
    /// Return animation state by index.
    AnimationState* GetAnimationState(unsigned index) const;

    /// Return animation LOD bias.
    /// @property
    float GetAnimationLodBias() const { return animationLodBias_; }

    /// Return whether to update animation when not visible.
    /// @property
    bool GetUpdateInvisible() const { return updateInvisible_; }

    /// Return all vertex morphs.
    const Vector<ModelMorph>& GetMorphs() const { return morphs_; }

    /// Return all morph vertex buffers.
    const Vector<SharedPtr<VertexBuffer>>& GetMorphVertexBuffers() const { return morphVertexBuffers_; }

    /// Return number of vertex morphs.
    /// @property
    unsigned GetNumMorphs() const { return morphs_.Size(); }

    /// Return vertex morph weight by index.
    float GetMorphWeight(unsigned index) const;
    /// Return vertex morph weight by name.
    /// @property{get_morphWeights}
    float GetMorphWeight(const String& name) const;
    /// Return vertex morph weight by name hash.
    float GetMorphWeight(StringHash nameHash) const;

    /// Return whether is the master (first) animated model.
    bool IsMaster() const { return isMaster_; }

    /// Set model attribute.
    void SetModelAttr(const ResourceRef& value);
    /// Set bones' animation enabled attribute.
    void SetBonesEnabledAttr(const VariantVector& value);
    /// Set animation states attribute.
    void SetAnimationStatesAttr(const VariantVector& value);
    /// Set morphs attribute.
    void SetMorphsAttr(const Vector<unsigned char>& value);
    /// Return model attribute.
    ResourceRef GetModelAttr() const;
    /// Return bones' animation enabled attribute.
    VariantVector GetBonesEnabledAttr() const;
    /// Return animation states attribute.
    VariantVector GetAnimationStatesAttr() const;
    /// Return morphs attribute.
    const Vector<unsigned char>& GetMorphsAttr() const;

    /// Return per-geometry bone mappings.
    const Vector<Vector<unsigned>>& GetGeometryBoneMappings() const { return geometryBoneMappings_; }

    /// Return per-geometry skin matrices. If empty, uses global skinning.
    const Vector<Vector<Matrix3x4>>& GetGeometrySkinMatrices() const { return geometrySkinMatrices_; }

    /// Recalculate the bone bounding box. Normally called internally, but can also be manually called if up-to-date information before rendering is necessary.
    void UpdateBoneBoundingBox();

protected:
    /// Handle node being assigned.
    void OnNodeSet(Node* node) override;
    /// Handle node transform being dirtied.
    void OnMarkedDirty(Node* node) override;
    /// Recalculate the world-space bounding box.
    void OnWorldBoundingBoxUpdate() override;

private:
    /// Assign skeleton and animation bone node references as a postprocess. Called by ApplyAttributes.
    void AssignBoneNodes();
    /// Finalize master model bone bounding boxes by merging from matching non-master bones.. Performed whenever any of the AnimatedModels in the same node changes its model.
    void FinalizeBoneBoundingBoxes();
    /// Remove (old) skeleton root bone.
    void RemoveRootBone();
    /// Mark animation and skinning to require an update.
    void MarkAnimationDirty();
    /// Mark animation and skinning to require a forced update (blending order changed).
    void MarkAnimationOrderDirty();
    /// Mark morphs to require an update.
    void MarkMorphsDirty();
    /// Set skeleton.
    void SetSkeleton(const Skeleton& skeleton, bool createBones);
    /// Set mapping of subgeometry bone indices.
    void SetGeometryBoneMappings();
    /// Clone geometries for vertex morphing.
    void CloneGeometries();
    /// Copy morph vertices.
    void CopyMorphVertices(void* destVertexData, void* srcVertexData, unsigned vertexCount, VertexBuffer* destBuffer, VertexBuffer* srcBuffer);
    /// Recalculate animations. Called from Update().
    void UpdateAnimation(const FrameInfo& frame);
    /// Recalculate skinning.
    void UpdateSkinning();
    /// Reapply all vertex morphs.
    void UpdateMorphs();
    /// Apply a vertex morph.
    void ApplyMorph
        (VertexBuffer* buffer, void* destVertexData, unsigned morphRangeStart, const VertexBufferMorph& morph, float weight);
    /// Handle model reload finished.
    void HandleModelReloadFinished(StringHash eventType, VariantMap& eventData);

    /// Skeleton.
    Skeleton skeleton_;
    /// Morph vertex buffers.
    Vector<SharedPtr<VertexBuffer>> morphVertexBuffers_;
    /// Vertex morphs.
    Vector<ModelMorph> morphs_;
    /// Animation states.
    Vector<SharedPtr<AnimationState>> animationStates_;
    /// Skinning matrices.
    Vector<Matrix3x4> skinMatrices_;
    /// Mapping of subgeometry bone indices, used if more bones than skinning shader can manage.
    Vector<Vector<unsigned>> geometryBoneMappings_;
    /// Subgeometry skinning matrices, used if more bones than skinning shader can manage.
    Vector<Vector<Matrix3x4>> geometrySkinMatrices_;
    /// Subgeometry skinning matrix pointers, if more bones than skinning shader can manage.
    Vector<Vector<Matrix3x4*>> geometrySkinMatrixPtrs_;
    /// Bounding box calculated from bones.
    BoundingBox boneBoundingBox_;
    /// Attribute buffer.
    mutable VectorBuffer attrBuffer_;
    /// The frame number animation LOD distance was last calculated on.
    i32 animationLodFrameNumber_;
    /// Morph vertex element mask.
    VertexMaskFlags morphElementMask_;
    /// Animation LOD bias.
    float animationLodBias_;
    /// Animation LOD timer.
    float animationLodTimer_;
    /// Animation LOD distance, the minimum of all LOD view distances last frame.
    float animationLodDistance_;
    /// Update animation when invisible flag.
    bool updateInvisible_;
    /// Animation dirty flag.
    bool animationDirty_;
    /// Animation order dirty flag.
    bool animationOrderDirty_;
    /// Vertex morphs dirty flag.
    bool morphsDirty_;
    /// Skinning dirty flag.
    bool skinningDirty_;
    /// Bone bounding box dirty flag.
    bool boneBoundingBoxDirty_;
    /// Master model flag.
    bool isMaster_;
    /// Loading flag. During loading bone nodes are not created, as they will be serialized as child nodes.
    bool loading_;
    /// Bone nodes assignment pending flag.
    bool assignBonesPending_;
    /// Force animation update after becoming visible flag.
    bool forceAnimationUpdate_;
};

}
