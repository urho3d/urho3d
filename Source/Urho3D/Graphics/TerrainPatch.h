// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Graphics/Drawable.h"

namespace Urho3D
{

class Geometry;
class Terrain;
class VertexBuffer;

/// Individually rendered part of a heightmap terrain.
class URHO3D_API TerrainPatch : public Drawable
{
    URHO3D_OBJECT(TerrainPatch, Drawable);

public:
    /// Construct.
    explicit TerrainPatch(Context* context);
    /// Destruct.
    ~TerrainPatch() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Process octree raycast. May be called from a worker thread.
    void ProcessRayQuery(const RayOctreeQuery& query, Vector<RayQueryResult>& results) override;
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    void UpdateBatches(const FrameInfo& frame) override;
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update).
    void UpdateGeometry(const FrameInfo& frame) override;
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    UpdateGeometryType GetUpdateGeometryType() override;
    /// Return the geometry for a specific LOD level.
    Geometry* GetLodGeometry(i32 batchIndex, i32 level) override;
    /// Return number of occlusion geometry triangles.
    i32 GetNumOccluderTriangles() override;
    /// Draw to occlusion buffer. Return true if did not run out of triangles.
    bool DrawOcclusion(OcclusionBuffer* buffer) override;
    /// Visualize the component as debug geometry.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    /// Set owner terrain.
    void SetOwner(Terrain* terrain);
    /// Set neighbor patches.
    void SetNeighbors(TerrainPatch* north, TerrainPatch* south, TerrainPatch* west, TerrainPatch* east);
    /// Set material.
    void SetMaterial(Material* material);
    /// Set local-space bounding box.
    void SetBoundingBox(const BoundingBox& box);
    /// Set patch coordinates.
    void SetCoordinates(const IntVector2& coordinates);
    /// Reset to LOD level 0.
    void ResetLod();

    /// Return visible geometry.
    Geometry* GetGeometry() const;
    /// Return max LOD geometry. Used for decals.
    Geometry* GetMaxLodGeometry() const;
    /// Return geometry used for occlusion.
    Geometry* GetOcclusionGeometry() const;
    /// Return vertex buffer.
    VertexBuffer* GetVertexBuffer() const;
    /// Return owner terrain.
    Terrain* GetOwner() const;

    /// Return north neighbor patch.
    TerrainPatch* GetNorthPatch() const { return north_; }

    /// Return south neighbor patch.
    TerrainPatch* GetSouthPatch() const { return south_; }

    /// Return west neighbor patch.
    TerrainPatch* GetWestPatch() const { return west_; }

    /// Return east neighbor patch.
    TerrainPatch* GetEastPatch() const { return east_; }

    /// Return geometrical error array.
    Vector<float>& GetLodErrors() { return lodErrors_; }

    /// Return patch coordinates.
    const IntVector2& GetCoordinates() const { return coordinates_; }

    /// Return current LOD level.
    i32 GetLodLevel() const { return lodLevel_; }

protected:
    /// Recalculate the world-space bounding box.
    void OnWorldBoundingBoxUpdate() override;

private:
    /// Return a corrected LOD level to ensure stitching can work correctly.
    i32 GetCorrectedLodLevel(i32 lodLevel);

    /// Geometry.
    SharedPtr<Geometry> geometry_;
    /// Geometry that is locked to the max LOD level. Used for decals.
    SharedPtr<Geometry> maxLodGeometry_;
    /// Geometry that is used for occlusion.
    SharedPtr<Geometry> occlusionGeometry_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Parent terrain.
    WeakPtr<Terrain> owner_;
    /// North neighbor patch.
    WeakPtr<TerrainPatch> north_;
    /// South neighbor patch.
    WeakPtr<TerrainPatch> south_;
    /// West neighbor patch.
    WeakPtr<TerrainPatch> west_;
    /// East neighbor patch.
    WeakPtr<TerrainPatch> east_;
    /// Geometrical error per LOD level.
    Vector<float> lodErrors_;
    /// Patch coordinates in the terrain. (0,0) is the northwest corner.
    IntVector2 coordinates_;
    /// Current LOD level.
    i32 lodLevel_;
};

}
