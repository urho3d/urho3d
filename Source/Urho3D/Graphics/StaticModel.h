// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Graphics/Drawable.h"

namespace Urho3D
{

class Model;

/// Static model per-geometry extra data.
struct StaticModelGeometryData
{
    /// Geometry center.
    Vector3 center_;
    /// Current LOD level.
    unsigned lodLevel_;
};

/// Static model component.
class URHO3D_API StaticModel : public Drawable
{
    URHO3D_OBJECT(StaticModel, Drawable);

public:
    /// Construct.
    explicit StaticModel(Context* context);
    /// Destruct.
    ~StaticModel() override;
    /// Register object factory. Drawable must be registered first.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Process octree raycast. May be called from a worker thread.
    void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results) override;
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    void UpdateBatches(const FrameInfo& frame) override;
    /// Return the geometry for a specific LOD level.
    Geometry* GetLodGeometry(unsigned batchIndex, unsigned level) override;
    /// Return number of occlusion geometry triangles.
    unsigned GetNumOccluderTriangles() override;
    /// Draw to occlusion buffer. Return true if did not run out of triangles.
    bool DrawOcclusion(OcclusionBuffer* buffer) override;

    /// Set model.
    /// @manualbind
    virtual void SetModel(Model* model);
    /// Set material on all geometries.
    /// @property
    virtual void SetMaterial(Material* material);
    /// Set material on one geometry. Return true if successful.
    /// @property{set_materials}
    virtual bool SetMaterial(unsigned index, Material* material);
    /// Set occlusion LOD level. By default (M_MAX_UNSIGNED) same as visible.
    /// @property
    void SetOcclusionLodLevel(unsigned level);
    /// Apply default materials from a material list file. If filename is empty (default), the model's resource name with extension .txt will be used.
    void ApplyMaterialList(const String& fileName = String::EMPTY);

    /// Return model.
    /// @property
    Model* GetModel() const { return model_; }

    /// Return number of geometries.
    /// @property
    unsigned GetNumGeometries() const { return geometries_.Size(); }

    /// Return material from the first geometry, assuming all the geometries use the same material.
    /// @property
    virtual Material* GetMaterial() const { return GetMaterial(0); }
    /// Return material by geometry index.
    /// @property{get_materials}
    virtual Material* GetMaterial(unsigned index) const;

    /// Return occlusion LOD level.
    /// @property
    unsigned GetOcclusionLodLevel() const { return occlusionLodLevel_; }

    /// Determines if the given world space point is within the model geometry.
    bool IsInside(const Vector3& point) const;
    /// Determines if the given local space point is within the model geometry.
    bool IsInsideLocal(const Vector3& point) const;

    /// Set model attribute.
    void SetModelAttr(const ResourceRef& value);
    /// Set materials attribute.
    void SetMaterialsAttr(const ResourceRefList& value);
    /// Return model attribute.
    ResourceRef GetModelAttr() const;
    /// Return materials attribute.
    const ResourceRefList& GetMaterialsAttr() const;

protected:
    /// Recalculate the world-space bounding box.
    void OnWorldBoundingBoxUpdate() override;
    /// Set local-space bounding box.
    void SetBoundingBox(const BoundingBox& box);
    /// Set number of geometries.
    void SetNumGeometries(unsigned num);
    /// Reset LOD levels.
    void ResetLodLevels();
    /// Choose LOD levels based on distance.
    void CalculateLodLevels();

    /// Extra per-geometry data.
    PODVector<StaticModelGeometryData> geometryData_;
    /// All geometries.
    Vector<Vector<SharedPtr<Geometry> > > geometries_;
    /// Model.
    SharedPtr<Model> model_;
    /// Occlusion LOD level.
    unsigned occlusionLodLevel_;
    /// Material list attribute.
    mutable ResourceRefList materialsAttr_;

private:
    /// Handle model reload finished.
    void HandleModelReloadFinished(StringHash eventType, VariantMap& eventData);
};

}
