//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Navigation/NavigationMesh.h"

class dtTileCache;
struct dtTileCacheAlloc;
struct dtTileCacheCompressor;
struct dtTileCacheMeshProcess;
struct dtTileCacheLayer;
struct dtTileCacheContourSet;
struct dtTileCachePolyMesh;

namespace Urho3D
{

class OffMeshConnection;
class Obstacle;

class URHO3D_API DynamicNavigationMesh : public NavigationMesh
{
    URHO3D_OBJECT(DynamicNavigationMesh, NavigationMesh)

    friend class Obstacle;
    friend struct MeshProcess;

public:
    /// Constructor.
    DynamicNavigationMesh(Context*);
    /// Destructor.
    virtual ~DynamicNavigationMesh();

    /// Register with engine context.
    static void RegisterObject(Context*);

    /// Build/rebuild the entire navigation mesh.
    virtual bool Build();
    /// Build/rebuild a portion of the navigation mesh.
    virtual bool Build(const BoundingBox& boundingBox);
    /// Visualize the component as debug geometry.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);
    /// Add debug geometry to the debug renderer.
    void DrawDebugGeometry(bool depthTest);

    /// Set navigation data attribute.
    virtual void SetNavigationDataAttr(const PODVector<unsigned char>& value);
    /// Return navigation data attribute.
    virtual PODVector<unsigned char> GetNavigationDataAttr() const;

    /// Set the maximum number of obstacles allowed.
    void SetMaxObstacles(unsigned maxObstacles) { maxObstacles_ = maxObstacles; }
    /// Set the maximum number of layers that navigation construction can create.
    void SetMaxLayers(unsigned maxLayers);

    /// Return the maximum number of obstacles allowed.
    unsigned GetMaxObstacles() const { return maxObstacles_; }
    /// Return the maximum number of layers permitted to build.
    unsigned GetMaxLayers() const { return maxLayers_; }

    /// Draw debug geometry for Obstacles.
    void SetDrawObstacles(bool enable) { drawObstacles_ = enable; }

    /// Return whether to draw Obstacles.
    bool GetDrawObstacles() const { return drawObstacles_; }

protected:
    struct TileCacheData;

    /// Subscribe to events when assigned to a scene.
    virtual void OnSceneSet(Scene* scene);
    /// Trigger the tile cache to make updates to the nav mesh if necessary.
    void HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData);

    /// Used by Obstacle class to add itself to the tile cache, if 'silent' an event will not be raised.
    void AddObstacle(Obstacle* obstacle, bool silent = false);
    /// Used by Obstacle class to update itself.
    void ObstacleChanged(Obstacle* obstacle);
    /// Used by Obstacle class to remove itself from the tile cache, if 'silent' an event will not be raised.
    void RemoveObstacle(Obstacle*, bool silent = false);

    /// Build one tile of the navigation mesh. Return true if successful.
    int BuildTile(Vector<NavigationGeometryInfo>& geometryList, int x, int z, TileCacheData*);
    /// Off-mesh connections to be rebuilt in the mesh processor.
    PODVector<OffMeshConnection*> CollectOffMeshConnections(const BoundingBox& bounds);
    /// Release the navigation mesh, query, and tile cache.
    virtual void ReleaseNavigationMesh();

private:
    /// Free the tile cache.
    void ReleaseTileCache();

    /// Detour tile cache instance that works with the nav mesh.
    dtTileCache* tileCache_;
    /// Used by dtTileCache to allocate blocks of memory.
    dtTileCacheAlloc* allocator_;
    /// Used by dtTileCache to compress the original tiles to use when reconstructing for changes.
    dtTileCacheCompressor* compressor_;
    /// Mesh processer used by Detour, in this case a 'pass-through' processor.
    dtTileCacheMeshProcess* meshProcessor_;
    /// Maximum number of obstacle objects allowed.
    unsigned maxObstacles_;
    /// Maximum number of layers that are allowed to be constructed.
    unsigned maxLayers_;
    /// Debug draw Obstacles.
    bool drawObstacles_;
};

}
