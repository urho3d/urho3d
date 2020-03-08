//
// Copyright (c) 2008-2020 the Urho3D project.
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

/// \file

#pragma once

#include "../Graphics/Drawable.h"

namespace Urho3D
{

enum TrailType
{
    TT_FACE_CAMERA = 0,
    TT_BONE
};

class IndexBuffer;
class VertexBuffer;

/// Trail is consisting of series of tails. Two connected points make a tail.
struct URHO3D_API TrailPoint
{
    /// Construct a zero-initialized TrailPoint.
    TrailPoint() = default;
    /// Construct a TrailPoint with the given position and forward vector.
    TrailPoint(const Vector3& position, const Vector3& forward);
    /// Position.
    Vector3 position_;
    /// Forward vector.
    Vector3 forward_;
    /// Parent position. Trail bone type uses this.
    Vector3 parentPos_;
    /// Elapsed length inside the trail.
    float elapsedLength_{};
    /// Next point to make a tail.
    TrailPoint* next_{};
    /// Tail time to live.
    float lifetime_{};
    /// Distance for sorting.
    float sortDistance_{};
};

/// Drawable component that creates a tail.
class URHO3D_API RibbonTrail : public Drawable
{
    URHO3D_OBJECT(RibbonTrail, Drawable);

public:
    /// Construct.
    explicit RibbonTrail(Context* context);
    /// Destruct.
    ~RibbonTrail() override;
    /// Register object factory.
    static void RegisterObject(Context* context);
    /// Process octree raycast. May be called from a worker thread.
    void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override;
    /// Handle enabled/disabled state change.
    void OnSetEnabled() override;
    /// Update before octree reinsertion. Is called from a main thread.
    void Update(const FrameInfo &frame) override;
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    void UpdateBatches(const FrameInfo& frame) override;
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update.)
    void UpdateGeometry(const FrameInfo& frame) override;
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    UpdateGeometryType GetUpdateGeometryType() override;

    /// Set material.
    void SetMaterial(Material* material);
    /// Set material attribute.
    void SetMaterialAttr(const ResourceRef& value);
    /// Set distance between points.
    void SetVertexDistance(float length);
    /// Set width of the tail. Only works for face camera trail type.
    void SetWidth(float width);
    /// Set vertex blended color for start of trail.
    void SetStartColor(const Color& color);
    /// Set vertex blended scale for end of trail.
    void SetEndColor(const Color& color);
    /// Set vertex blended color for start of trail.
    void SetStartScale(float startScale);
    /// Set vertex blended scale for end of trail.
    void SetEndScale(float endScale);
    /// Set how the trail behave.
    void SetTrailType(TrailType type);
    /// Set base velocity applied to the trail.
    void SetBaseVelocity(const Vector3& baseVelocity);
    /// Set whether tails are sorted by distance. Default false.
    void SetSorted(bool enable);
    /// Set tail time to live.
    void SetLifetime(float time);
    /// Set whether trail should be emitting.
    void SetEmitting(bool emitting);
    /// Set whether to update when trail emitter are not visible.
    void SetUpdateInvisible(bool enable);
    /// Set number of column for every tails. Can be useful for fixing distortion at high angle.
    void SetTailColumn(unsigned tailColumn);
    /// Set animation LOD bias.
    void SetAnimationLodBias(float bias);
    /// Mark for bounding box and vertex buffer update. Call after modifying the trails.
    void Commit();

    /// Return material.
    Material* GetMaterial() const;

    /// Return material attribute.
    ResourceRef GetMaterialAttr() const;

    /// Get distance between points.
    float GetVertexDistance() const { return vertexDistance_;  }

    /// Get width of the trail.
    float GetWidth() const { return width_; }

    /// Get vertex blended color for start of trail.
    const Color& GetStartColor() const { return startColor_; }

    /// Get vertex blended color for end of trail.
    const Color& GetEndColor() const { return endColor_;  }

    /// Get vertex blended scale for start of trail.
    float GetStartScale() const { return startScale_; }

    /// Get vertex blended scale for end of trail.
    float GetEndScale() const { return endScale_; }

    /// Return whether tails are sorted.
    bool IsSorted() const { return sorted_; }

    /// Return tail time to live.
    float GetLifetime() const {return lifetime_;}

    /// Return animation LOD bias.
    float GetAnimationLodBias() const { return animationLodBias_; }

    /// Return how the trail behave.
    TrailType GetTrailType() const { return trailType_; }

    /// Return base trail velocity.
    const Vector3& GetBaseVelocity() const { return baseVelocity_; }

    /// Return number of column for tails.
    unsigned GetTailColumn() const { return tailColumn_; }

    /// Return whether is currently emitting.
    bool IsEmitting() const { return emitting_ ; }

    /// Return whether to update when trail emitter are not visible.
    bool GetUpdateInvisible() const { return updateInvisible_; }

protected:
    /// Handle node being assigned.
    void OnSceneSet(Scene* scene) override;
    /// Recalculate the world-space bounding box.
    void OnWorldBoundingBoxUpdate() override;
    /// Mark vertex buffer to need an update.
    void MarkPositionsDirty();
    /// Tails.
    PODVector<TrailPoint> points_;
    /// Tails sorted flag.
    bool sorted_;
    /// Animation LOD bias.
    float animationLodBias_;
    /// Animation LOD timer.
    float animationLodTimer_;
    /// Trail type.
    TrailType trailType_;
    /// Base velocity applied to the trail.
    Vector3 baseVelocity_;

private:
    /// Handle scene post-update event.
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);

    /// Resize RibbonTrail vertex and index buffers.
    void UpdateBufferSize();
    /// Rewrite RibbonTrail vertex buffer.
    void UpdateVertexBuffer(const FrameInfo& frame);
    /// Update/Rebuild tail mesh only if position changed (called by UpdateBatches())
    void UpdateTail(float timeStep);
    /// Geometry.
    SharedPtr<Geometry> geometry_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Index buffer.
    SharedPtr<IndexBuffer> indexBuffer_;
    /// Transform matrices for position and orientation.
    Matrix3x4 transforms_;
    /// Buffers need resize flag.
    bool bufferSizeDirty_;
    /// Vertex buffer needs rewrite flag.
    bool bufferDirty_;
    /// Previous position of tail
    Vector3 previousPosition_;
    /// Distance between points. Basically is tail length.
    float vertexDistance_;
    /// Width of trail.
    float width_;
    /// Number of points.
    unsigned numPoints_;
    /// Color for start of trails.
    Color startColor_;
    /// Color for end of trails.
    Color endColor_;
    /// Scale for start of trails.
    float startScale_;
    /// End for start of trails.
    float endScale_;
    /// Last scene timestep.
    float lastTimeStep_;
    /// Lifetime
    float lifetime_;
    /// Number of columns for every tails.
    unsigned tailColumn_;
    /// Rendering framenumber on which was last updated.
    unsigned lastUpdateFrameNumber_;
    /// Need update flag.
    bool needUpdate_;
    /// Previous offset to camera for determining whether sorting is necessary.
    Vector3 previousOffset_;
    /// Trail pointers for sorting.
    Vector<TrailPoint*> sortedPoints_;
    /// Force update flag (ignore animation LOD momentarily.)
    bool forceUpdate_;
    /// Currently emitting flag.
    bool emitting_;
    /// Update when invisible flag.
    bool updateInvisible_;

    /// End of trail point for smoother tail disappearance.
    TrailPoint endTail_;
    /// The time the tail become end of trail.
    float startEndTailTime_;
};

}
