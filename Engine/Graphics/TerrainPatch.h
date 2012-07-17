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

class Geometry;
class Terrain;
class VertexBuffer;

class TerrainPatch : public Drawable
{
    friend class Terrain;
    
    OBJECT(TerrainPatch);
    
public:
    /// Construct.
    TerrainPatch(Context* context);
    /// Destruct.
    ~TerrainPatch();
    
    /// Process octree raycast. May be called from a worker thread.
    virtual void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results);
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateBatches(const FrameInfo& frame);
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update.)
    virtual void UpdateGeometry(const FrameInfo& frame);
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    virtual UpdateGeometryType GetUpdateGeometryType();
    
protected:
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    
private:
    /// Geometry.
    SharedPtr<Geometry> geometry_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Parent terrain.
    Terrain* owner_;
    /// North neighbor patch.
    TerrainPatch* north_;
    /// South neighbor patch.
    TerrainPatch* south_;
    /// West neighbor patch.
    TerrainPatch* west_;
    /// East neighbor patch.
    TerrainPatch* east_;
    /// Local-space bounding box.
    BoundingBox boundingBox_;
    /// Patch X-coordinate in the terrain.
    unsigned x_;
    /// Patch Z-coordinate in the terrain.
    unsigned z_;
    /// Current LOD level.
    unsigned lodLevel_;
    /// Geometrical error per LOD level.
    PODVector<float> lodErrors_;
    /// LOD level dirty flag.
    bool lodDirty_;
};
