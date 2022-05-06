// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Graphics/Drawable.h"
#include "../IO/VectorBuffer.h"
#include "../Math/Color.h"
#include "../Math/Matrix3x4.h"
#include "../Math/Rect.h"

namespace Urho3D
{

class IndexBuffer;
class VertexBuffer;

/// One billboard in the billboard set.
/// @nocount
struct URHO3D_API Billboard
{
    /// Position.
    Vector3 position_;
    /// Two-dimensional size. If BillboardSet has fixed screen size enabled, this is measured in pixels instead of world units.
    Vector2 size_;
    /// UV coordinates.
    Rect uv_;
    /// Color.
    Color color_;
    /// Rotation.
    float rotation_;
    /// Direction (For direction based billboard only).
    Vector3 direction_;
    /// Enabled flag.
    bool enabled_;
    /// Sort distance. Used internally.
    float sortDistance_;
    /// Scale factor for fixed screen size mode. Used internally.
    float screenScaleFactor_;
};

/// %Billboard component.
class URHO3D_API BillboardSet : public Drawable
{
    URHO3D_OBJECT(BillboardSet, Drawable);

public:
    /// Construct.
    explicit BillboardSet(Context* context);
    /// Destruct.
    ~BillboardSet() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Process octree raycast. May be called from a worker thread.
    void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override;
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    void UpdateBatches(const FrameInfo& frame) override;
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update).
    void UpdateGeometry(const FrameInfo& frame) override;
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    UpdateGeometryType GetUpdateGeometryType() override;

    /// Set material.
    /// @property
    void SetMaterial(Material* material);
    /// Set number of billboards.
    /// @property
    void SetNumBillboards(unsigned num);
    /// Set whether billboards are relative to the scene node. Default true.
    /// @property
    void SetRelative(bool enable);
    /// Set whether scene node scale affects billboards' size. Default true.
    /// @property
    void SetScaled(bool enable);
    /// Set whether billboards are sorted by distance. Default false.
    /// @property
    void SetSorted(bool enable);
    /// Set whether billboards have fixed size on screen (measured in pixels) regardless of distance to camera. Default false.
    /// @property
    void SetFixedScreenSize(bool enable);
    /// Set how the billboards should rotate in relation to the camera. Default is to follow camera rotation on all axes (FC_ROTATE_XYZ).
    /// @property
    void SetFaceCameraMode(FaceCameraMode mode);
    /// Set minimal angle between billboard normal and look-at direction.
    /// @property
    void SetMinAngle(float angle);
    /// Set animation LOD bias.
    /// @property
    void SetAnimationLodBias(float bias);
    /// Mark for bounding box and vertex buffer update. Call after modifying the billboards.
    void Commit();

    /// Return material.
    /// @property
    Material* GetMaterial() const;

    /// Return number of billboards.
    /// @property
    unsigned GetNumBillboards() const { return billboards_.Size(); }

    /// Return all billboards.
    PODVector<Billboard>& GetBillboards() { return billboards_; }

    /// Return billboard by index.
    /// @property{get_billboards}
    Billboard* GetBillboard(unsigned index);

    /// Return whether billboards are relative to the scene node.
    /// @property
    bool IsRelative() const { return relative_; }

    /// Return whether scene node scale affects billboards' size.
    /// @property
    bool IsScaled() const { return scaled_; }

    /// Return whether billboards are sorted.
    /// @property
    bool IsSorted() const { return sorted_; }

    /// Return whether billboards are fixed screen size.
    /// @property
    bool IsFixedScreenSize() const { return fixedScreenSize_; }

    /// Return how the billboards rotate in relation to the camera.
    /// @property
    FaceCameraMode GetFaceCameraMode() const { return faceCameraMode_; }

    /// Return minimal angle between billboard normal and look-at direction.
    /// @property
    float GetMinAngle() const { return minAngle_; }

    /// Return animation LOD bias.
    /// @property
    float GetAnimationLodBias() const { return animationLodBias_; }

    /// Set material attribute.
    void SetMaterialAttr(const ResourceRef& value);
    /// Set billboards attribute.
    void SetBillboardsAttr(const VariantVector& value);
    /// Set billboards attribute for network replication.
    void SetNetBillboardsAttr(const PODVector<unsigned char>& value);
    /// Return material attribute.
    ResourceRef GetMaterialAttr() const;
    /// Return billboards attribute.
    VariantVector GetBillboardsAttr() const;
    /// Return billboards attribute for network replication.
    const PODVector<unsigned char>& GetNetBillboardsAttr() const;

protected:
    /// Recalculate the world-space bounding box.
    void OnWorldBoundingBoxUpdate() override;
    /// Mark billboard vertex buffer to need an update.
    void MarkPositionsDirty();

    /// Billboards.
    PODVector<Billboard> billboards_;
    /// Animation LOD bias.
    float animationLodBias_;
    /// Animation LOD timer.
    float animationLodTimer_;
    /// Billboards relative flag.
    bool relative_;
    /// Scale affects billboard scale flag.
    bool scaled_;
    /// Billboards sorted flag.
    bool sorted_;
    /// Billboards fixed screen size flag.
    bool fixedScreenSize_;
    /// Billboard rotation mode in relation to the camera.
    FaceCameraMode faceCameraMode_;
    /// Minimal angle between billboard normal and look-at direction.
    float minAngle_;

private:
    /// Resize billboard vertex and index buffers.
    void UpdateBufferSize();
    /// Rewrite billboard vertex buffer.
    void UpdateVertexBuffer(const FrameInfo& frame);
    /// Calculate billboard scale factors in fixed screen size mode.
    void CalculateFixedScreenSize(const FrameInfo& frame);

    /// Geometry.
    SharedPtr<Geometry> geometry_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Index buffer.
    SharedPtr<IndexBuffer> indexBuffer_;
    /// Transform matrices for position and billboard orientation.
    Matrix3x4 transforms_[2];
    /// Buffers need resize flag.
    bool bufferSizeDirty_;
    /// Vertex buffer needs rewrite flag.
    bool bufferDirty_;
    /// Force update flag (ignore animation LOD momentarily).
    bool forceUpdate_;
    /// Update billboard geometry type.
    bool geometryTypeUpdate_;
    /// Sorting flag. Triggers a vertex buffer rewrite for each view this billboard set is rendered from.
    bool sortThisFrame_;
    /// Whether was last rendered from an ortho camera.
    bool hasOrthoCamera_;
    /// Frame number on which was last sorted.
    unsigned sortFrameNumber_;
    /// Previous offset to camera for determining whether sorting is necessary.
    Vector3 previousOffset_;
    /// Billboard pointers for sorting.
    Vector<Billboard*> sortedBillboards_;
    /// Attribute buffer for network replication.
    mutable VectorBuffer attrBuffer_;
};

}
