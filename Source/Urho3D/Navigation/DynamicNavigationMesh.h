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
    explicit DynamicNavigationMesh(Context*);
    /// Destructor.
    ~DynamicNavigationMesh() override;

    /// Register with engine context.
    static void RegisterObject(Context*);

    /// Allocate the navigation mesh without building any tiles. Bounding box is not padded. Return true if successful.
    bool Allocate(const BoundingBox& boundingBox, unsigned maxTiles) override;
    /// Build/rebuild the entire navigation mesh.
    bool Build() override;
    /// Build/rebuild a portion of the navigation mesh.
    bool Build(const BoundingBox& boundingBox) override;
    /// Rebuild part of the navigation mesh in the rectangular area. Return true if successful.
    bool Build(const IntVector2& from, const IntVector2& to) override;
    /// Return tile data.
    PODVector<unsigned char> GetTileData(const IntVector2& tile) const override;
    /// Return whether the Obstacle is touching the given tile.
    bool IsObstacleInTile(Obstacle* obstacle, const IntVector2& tile) const;
    /// Add tile to navigation mesh.
    bool AddTile(const PODVector<unsigned char>& tileData) override;
    /// Remove tile from navigation mesh.
    void RemoveTile(const IntVector2& tile) override;
    /// Remove all tiles from navigation mesh.
    void RemoveAllTiles() override;
    /// Visualize the component as debug geometry.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;
    /// Add debug geometry to the debug renderer.
    void DrawDebugGeometry(bool depthTest);

    /// Set navigation data attribute.
    void SetNavigationDataAttr(const PODVector<unsigned char>& value) override;
    /// Return navigation data attribute.
    PODVector<unsigned char> GetNavigationDataAttr() const override;

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
    void OnSceneSet(Scene* scene) override;
    /// Trigger the tile cache to make updates to the nav mesh if necessary.
    void HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData);

    /// Used by Obstacle class to add itself to the tile cache, if 'silent' an event will not be raised.
    void AddObstacle(Obstacle* obstacle, bool silent = false);
    /// Used by Obstacle class to update itself.
    void ObstacleChanged(Obstacle* obstacle);
    /// Used by Obstacle class to remove itself from the tile cache, if 'silent' an event will not be raised.
    void RemoveObstacle(Obstacle*, bool silent = false);

    /// Build one tile of the navigation mesh. Return true if successful.
    int BuildTile(Vector<NavigationGeometryInfo>& geometryList, int x, int z, TileCacheData* tiles);
    /// Build tiles in the rectangular area. Return number of built tiles.
    unsigned BuildTiles(Vector<NavigationGeometryInfo>& geometryList, const IntVector2& from, const IntVector2& to);
    /// Off-mesh connections to be rebuilt in the mesh processor.
    PODVector<OffMeshConnection*> CollectOffMeshConnections(const BoundingBox& bounds);
    /// Release the navigation mesh, query, and tile cache.
    void ReleaseNavigationMesh() override;

private:
    /// Write tiles data.
    void WriteTiles(Serializer& dest, int x, int z) const;
    /// Read tiles data to the navigation mesh.
    bool ReadTiles(Deserializer& source, bool silent);
    /// Free the tile cache.
    void ReleaseTileCache();

    /// Detour tile cache instance that works with the nav mesh.
    dtTileCache* tileCache_{};
    /// Used by dtTileCache to allocate blocks of memory.
    UniquePtr<dtTileCacheAlloc> allocator_;
    /// Used by dtTileCache to compress the original tiles to use when reconstructing for changes.
    UniquePtr<dtTileCacheCompressor> compressor_;
    /// Mesh processor used by Detour, in this case a 'pass-through' processor.
    UniquePtr<dtTileCacheMeshProcess> meshProcessor_;
    /// Maximum number of obstacle objects allowed.
    unsigned maxObstacles_{1024};
    /// Maximum number of layers that are allowed to be constructed.
    unsigned maxLayers_{};
    /// Debug draw Obstacles.
    bool drawObstacles_{};
    /// Queue of tiles to be built.
    PODVector<IntVector2> tileQueue_;
};

}
