//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Graphics/Drawable.h"

namespace Urho3D
{

class Geometry;
class Terrain;
class VertexBuffer;

/// Individually rendered part of a heightmap terrain.
class URHO3D_API TerrainPatch : public Drawable
{
    OBJECT(TerrainPatch);
    
public:
    /// Construct.
    TerrainPatch(Context* context);
    /// Destruct.
    ~TerrainPatch();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Process octree raycast. May be called from a worker thread.
    virtual void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results);
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateBatches(const FrameInfo& frame);
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update.)
    virtual void UpdateGeometry(const FrameInfo& frame);
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    virtual UpdateGeometryType GetUpdateGeometryType();
    /// Return the geometry for a specific LOD level.
    virtual Geometry* GetLodGeometry(unsigned batchIndex, unsigned level);
    /// Return number of occlusion geometry triangles.
    virtual unsigned GetNumOccluderTriangles();
    /// Draw to occlusion buffer. Return true if did not run out of triangles.
    virtual bool DrawOcclusion(OcclusionBuffer* buffer);
    /// Visualize the component as debug geometry.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);
    
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
    /// Set vertical offset for occlusion geometry. Should be negative.
    void SetOcclusionOffset(float offset);
    /// Reset to LOD level 0.
    void ResetLod();
    
    /// Return visible geometry.
    Geometry* GetGeometry() const;
    /// Return max LOD geometry.
    Geometry* GetMaxLodGeometry() const;
    /// Return min LOD geometry.
    Geometry* GetMinLodGeometry() const;
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
    PODVector<float>& GetLodErrors() { return lodErrors_; }
    /// Return patch coordinates.
    const IntVector2& GetCoordinates() const { return coordinates_; }
    /// Return current LOD level.
    unsigned GetLodLevel() const { return lodLevel_; }
    /// Return vertical offset for occlusion geometry..
    float GetOcclusionOffset() const { return occlusionOffset_; }
    
protected:
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    
private:
    /// Return a corrected LOD level to ensure stitching can work correctly.
    unsigned GetCorrectedLodLevel(unsigned lodLevel);
    
    /// Geometry.
    SharedPtr<Geometry> geometry_;
    /// Geometry that is locked to the max LOD level. Used for decals.
    SharedPtr<Geometry> maxLodGeometry_;
    /// Geometry that is locked to the minimum LOD level. Used for occlusion.
    SharedPtr<Geometry> minLodGeometry_;
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
    PODVector<float> lodErrors_;
    /// Patch coordinates in the terrain. (0,0) is the northwest corner.
    IntVector2 coordinates_;
    /// Current LOD level.
    unsigned lodLevel_;
    /// Vertical offset for occlusion geometry.
    float occlusionOffset_;
};

}
