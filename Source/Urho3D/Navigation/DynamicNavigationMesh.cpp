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

#include "../Precompiled.h"


#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/DebugRenderer.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../Navigation/CrowdAgent.h"
#include "../Navigation/DynamicNavigationMesh.h"
#include "../Navigation/NavArea.h"
#include "../Navigation/NavBuildData.h"
#include "../Navigation/NavigationEvents.h"
#include "../Navigation/Obstacle.h"
#include "../Navigation/OffMeshConnection.h"
#include "../Scene/Node.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"

#include <LZ4/lz4.h>
#include <Detour/DetourNavMesh.h>
#include <Detour/DetourNavMeshBuilder.h>
#include <DetourTileCache/DetourTileCache.h>
#include <DetourTileCache/DetourTileCacheBuilder.h>
#include <Recast/Recast.h>

// DebugNew is deliberately not used because the macro 'free' conflicts with DetourTileCache's LinearAllocator interface
//#include "../DebugNew.h"

#define TILECACHE_MAXLAYERS 255

namespace Urho3D
{

extern const char* NAVIGATION_CATEGORY;

static const int DEFAULT_MAX_OBSTACLES = 1024;
static const int DEFAULT_MAX_LAYERS = 16;

struct DynamicNavigationMesh::TileCacheData
{
    unsigned char* data;
    int dataSize;
};

struct TileCompressor : public dtTileCacheCompressor
{
    virtual int maxCompressedSize(const int bufferSize)
    {
        return (int)(bufferSize * 1.05f);
    }

    virtual dtStatus compress(const unsigned char* buffer, const int bufferSize,
        unsigned char* compressed, const int /*maxCompressedSize*/, int* compressedSize)
    {
        *compressedSize = LZ4_compress((const char*)buffer, (char*)compressed, bufferSize);
        return DT_SUCCESS;
    }

    virtual dtStatus decompress(const unsigned char* compressed, const int compressedSize,
        unsigned char* buffer, const int maxBufferSize, int* bufferSize)
    {
        *bufferSize = LZ4_decompress_safe((const char*)compressed, (char*)buffer, compressedSize, maxBufferSize);
        return *bufferSize < 0 ? DT_FAILURE : DT_SUCCESS;
    }
};

struct MeshProcess : public dtTileCacheMeshProcess
{
    DynamicNavigationMesh* owner_;
    PODVector<Vector3> offMeshVertices_;
    PODVector<float> offMeshRadii_;
    PODVector<unsigned short> offMeshFlags_;
    PODVector<unsigned char> offMeshAreas_;
    PODVector<unsigned char> offMeshDir_;

    inline MeshProcess(DynamicNavigationMesh* owner) :
        owner_(owner)
    {
    }

    virtual void process(struct dtNavMeshCreateParams* params, unsigned char* polyAreas, unsigned short* polyFlags)
    {
        // Update poly flags from areas.
        // \todo Assignment of flags from areas?
        for (int i = 0; i < params->polyCount; ++i)
        {
            if (polyAreas[i] != RC_NULL_AREA)
                polyFlags[i] = RC_WALKABLE_AREA;
        }

        BoundingBox bounds;
        rcVcopy(&bounds.min_.x_, params->bmin);
        rcVcopy(&bounds.max_.x_, params->bmin);

        // collect off-mesh connections
        PODVector<OffMeshConnection*> offMeshConnections = owner_->CollectOffMeshConnections(bounds);

        if (offMeshConnections.Size() > 0)
        {
            if (offMeshConnections.Size() != offMeshRadii_.Size())
            {
                Matrix3x4 inverse = owner_->GetNode()->GetWorldTransform().Inverse();
                ClearConnectionData();
                for (unsigned i = 0; i < offMeshConnections.Size(); ++i)
                {
                    OffMeshConnection* connection = offMeshConnections[i];
                    Vector3 start = inverse * connection->GetNode()->GetWorldPosition();
                    Vector3 end = inverse * connection->GetEndPoint()->GetWorldPosition();

                    offMeshVertices_.Push(start);
                    offMeshVertices_.Push(end);
                    offMeshRadii_.Push(connection->GetRadius());
                    offMeshFlags_.Push((unsigned short)connection->GetMask());
                    offMeshAreas_.Push((unsigned char)connection->GetAreaID());
                    offMeshDir_.Push((unsigned char)(connection->IsBidirectional() ? DT_OFFMESH_CON_BIDIR : 0));
                }
            }
            params->offMeshConCount = offMeshRadii_.Size();
            params->offMeshConVerts = &offMeshVertices_[0].x_;
            params->offMeshConRad = &offMeshRadii_[0];
            params->offMeshConFlags = &offMeshFlags_[0];
            params->offMeshConAreas = &offMeshAreas_[0];
            params->offMeshConDir = &offMeshDir_[0];
        }
    }

    void ClearConnectionData()
    {
        offMeshVertices_.Clear();
        offMeshRadii_.Clear();
        offMeshFlags_.Clear();
        offMeshAreas_.Clear();
        offMeshDir_.Clear();
    }
};


// From the Detour/Recast Sample_TempObstacles.cpp
struct LinearAllocator : public dtTileCacheAlloc
{
    unsigned char* buffer;
    int capacity;
    int top;
    int high;

    LinearAllocator(const int cap) :
        buffer(0), capacity(0), top(0), high(0)
    {
        resize(cap);
    }

    ~LinearAllocator()
    {
        dtFree(buffer);
    }

    void resize(const int cap)
    {
        if (buffer)
            dtFree(buffer);
        buffer = (unsigned char*)dtAlloc(cap, DT_ALLOC_PERM);
        capacity = cap;
    }

    virtual void reset()
    {
        high = Max(high, top);
        top = 0;
    }

    virtual void* alloc(const int size)
    {
        if (!buffer)
            return 0;
        if (top + size > capacity)
            return 0;
        unsigned char* mem = &buffer[top];
        top += size;
        return mem;
    }

    virtual void free(void*)
    {
    }
};


DynamicNavigationMesh::DynamicNavigationMesh(Context* context) :
    NavigationMesh(context),
    tileCache_(0),
    maxObstacles_(1024),
    maxLayers_(DEFAULT_MAX_LAYERS),
    drawObstacles_(false)
{
    //64 is the largest tile-size that DetourTileCache will tolerate without silently failing
    tileSize_ = 64;
    partitionType_ = NAVMESH_PARTITION_MONOTONE;
    allocator_ = new LinearAllocator(32000); //32kb to start
    compressor_ = new TileCompressor();
    meshProcessor_ = new MeshProcess(this);
}

DynamicNavigationMesh::~DynamicNavigationMesh()
{
    ReleaseNavigationMesh();
    delete allocator_;
    allocator_ = 0;
    delete compressor_;
    compressor_ = 0;
    delete meshProcessor_;
    meshProcessor_ = 0;
}

void DynamicNavigationMesh::RegisterObject(Context* context)
{
    context->RegisterFactory<DynamicNavigationMesh>(NAVIGATION_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(NavigationMesh);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Obstacles", GetMaxObstacles, SetMaxObstacles, unsigned, DEFAULT_MAX_OBSTACLES, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Layers", GetMaxLayers, SetMaxLayers, unsigned, DEFAULT_MAX_LAYERS, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Obstacles", GetDrawObstacles, SetDrawObstacles, bool, false, AM_DEFAULT);
}

bool DynamicNavigationMesh::Build()
{
    URHO3D_PROFILE(BuildNavigationMesh);
    // Release existing navigation data and zero the bounding box
    ReleaseNavigationMesh();

    if (!node_)
        return false;

    if (!node_->GetWorldScale().Equals(Vector3::ONE))
        URHO3D_LOGWARNING("Navigation mesh root node has scaling. Agent parameters may not work as intended");

    Vector<NavigationGeometryInfo> geometryList;
    CollectGeometries(geometryList);

    if (geometryList.Empty())
        return true; // Nothing to do

    // Build the combined bounding box
    for (unsigned i = 0; i < geometryList.Size(); ++i)
        boundingBox_.Merge(geometryList[i].boundingBox_);

    // Expand bounding box by padding
    boundingBox_.min_ -= padding_;
    boundingBox_.max_ += padding_;

    {
        URHO3D_PROFILE(BuildNavigationMesh);

        // Calculate number of tiles
        int gridW = 0, gridH = 0;
        float tileEdgeLength = (float)tileSize_ * cellSize_;
        rcCalcGridSize(&boundingBox_.min_.x_, &boundingBox_.max_.x_, cellSize_, &gridW, &gridH);
        numTilesX_ = (gridW + tileSize_ - 1) / tileSize_;
        numTilesZ_ = (gridH + tileSize_ - 1) / tileSize_;

        // Calculate max. number of tiles and polygons, 22 bits available to identify both tile & polygon within tile
        unsigned maxTiles = NextPowerOfTwo((unsigned)(numTilesX_ * numTilesZ_)) * maxLayers_;
        unsigned tileBits = 0;
        unsigned temp = maxTiles;
        while (temp > 1)
        {
            temp >>= 1;
            ++tileBits;
        }

        unsigned maxPolys = (unsigned)(1 << (22 - tileBits));

        dtNavMeshParams params;
        rcVcopy(params.orig, &boundingBox_.min_.x_);
        params.tileWidth = tileEdgeLength;
        params.tileHeight = tileEdgeLength;
        params.maxTiles = maxTiles;
        params.maxPolys = maxPolys;

        navMesh_ = dtAllocNavMesh();
        if (!navMesh_)
        {
            URHO3D_LOGERROR("Could not allocate navigation mesh");
            return false;
        }

        if (dtStatusFailed(navMesh_->init(&params)))
        {
            URHO3D_LOGERROR("Could not initialize navigation mesh");
            ReleaseNavigationMesh();
            return false;
        }

        dtTileCacheParams tileCacheParams;
        memset(&tileCacheParams, 0, sizeof(tileCacheParams));
        rcVcopy(tileCacheParams.orig, &boundingBox_.min_.x_);
        tileCacheParams.ch = cellHeight_;
        tileCacheParams.cs = cellSize_;
        tileCacheParams.width = tileSize_;
        tileCacheParams.height = tileSize_;
        tileCacheParams.maxSimplificationError = edgeMaxError_;
        tileCacheParams.maxTiles = numTilesX_ * numTilesZ_ * maxLayers_;
        tileCacheParams.maxObstacles = maxObstacles_;
        // Settings from NavigationMesh
        tileCacheParams.walkableClimb = agentMaxClimb_;
        tileCacheParams.walkableHeight = agentHeight_;
        tileCacheParams.walkableRadius = agentRadius_;

        tileCache_ = dtAllocTileCache();
        if (!tileCache_)
        {
            URHO3D_LOGERROR("Could not allocate tile cache");
            ReleaseNavigationMesh();
            return false;
        }

        if (dtStatusFailed(tileCache_->init(&tileCacheParams, allocator_, compressor_, meshProcessor_)))
        {
            URHO3D_LOGERROR("Could not initialize tile cache");
            ReleaseNavigationMesh();
            return false;
        }

        // Build each tile
        unsigned numTiles = 0;

        for (int z = 0; z < numTilesZ_; ++z)
        {
            for (int x = 0; x < numTilesX_; ++x)
            {
                TileCacheData tiles[TILECACHE_MAXLAYERS];
                int layerCt = BuildTile(geometryList, x, z, tiles);
                for (int i = 0; i < layerCt; ++i)
                {
                    dtCompressedTileRef tileRef;
                    int status = tileCache_->addTile(tiles[i].data, tiles[i].dataSize, DT_COMPRESSEDTILE_FREE_DATA, &tileRef);
                    if (dtStatusFailed((dtStatus)status))
                    {
                        dtFree(tiles[i].data);
                        tiles[i].data = 0x0;
                    }
                }
                ++numTiles;
            }
            for (int x = 0; x < numTilesX_; ++x)
                tileCache_->buildNavMeshTilesAt(x, z, navMesh_);
        }

        // For a full build it's necessary to update the nav mesh
        // not doing so will cause dependent components to crash, like CrowdManager
        tileCache_->update(0, navMesh_);

        URHO3D_LOGDEBUG("Built navigation mesh with " + String(numTiles) + " tiles");

        // Send a notification event to concerned parties that we've been fully rebuilt
        {
            using namespace NavigationMeshRebuilt;
            VariantMap& buildEventParams = GetContext()->GetEventDataMap();
            buildEventParams[P_NODE] = node_;
            buildEventParams[P_MESH] = this;
            SendEvent(E_NAVIGATION_MESH_REBUILT, buildEventParams);
        }

        // Scan for obstacles to insert into us
        PODVector<Node*> obstacles;
        GetScene()->GetChildrenWithComponent<Obstacle>(obstacles, true);
        for (unsigned i = 0; i < obstacles.Size(); ++i)
        {
            Obstacle* obs = obstacles[i]->GetComponent<Obstacle>();
            if (obs && obs->IsEnabledEffective())
                AddObstacle(obs);
        }

        return true;
    }
}

bool DynamicNavigationMesh::Build(const BoundingBox& boundingBox)
{
    URHO3D_PROFILE(BuildPartialNavigationMesh);

    if (!node_)
        return false;

    if (!navMesh_)
    {
        URHO3D_LOGERROR("Navigation mesh must first be built fully before it can be partially rebuilt");
        return false;
    }

    if (!node_->GetWorldScale().Equals(Vector3::ONE))
        URHO3D_LOGWARNING("Navigation mesh root node has scaling. Agent parameters may not work as intended");

    BoundingBox localSpaceBox = boundingBox.Transformed(node_->GetWorldTransform().Inverse());

    float tileEdgeLength = (float)tileSize_ * cellSize_;

    Vector<NavigationGeometryInfo> geometryList;
    CollectGeometries(geometryList);

    int sx = Clamp((int)((localSpaceBox.min_.x_ - boundingBox_.min_.x_) / tileEdgeLength), 0, numTilesX_ - 1);
    int sz = Clamp((int)((localSpaceBox.min_.z_ - boundingBox_.min_.z_) / tileEdgeLength), 0, numTilesZ_ - 1);
    int ex = Clamp((int)((localSpaceBox.max_.x_ - boundingBox_.min_.x_) / tileEdgeLength), 0, numTilesX_ - 1);
    int ez = Clamp((int)((localSpaceBox.max_.z_ - boundingBox_.min_.z_) / tileEdgeLength), 0, numTilesZ_ - 1);

    unsigned numTiles = 0;

    for (int z = sz; z <= ez; ++z)
    {
        for (int x = sx; x <= ex; ++x)
        {
            dtCompressedTileRef existing[TILECACHE_MAXLAYERS];
            const int existingCt = tileCache_->getTilesAt(x, z, existing, maxLayers_);
            for (int i = 0; i < existingCt; ++i)
            {
                unsigned char* data = 0x0;
                if (!dtStatusFailed(tileCache_->removeTile(existing[i], &data, 0)) && data != 0x0)
                    dtFree(data);
            }

            TileCacheData tiles[TILECACHE_MAXLAYERS];
            int layerCt = BuildTile(geometryList, x, z, tiles);
            for (int i = 0; i < layerCt; ++i)
            {
                dtCompressedTileRef tileRef;
                int status = tileCache_->addTile(tiles[i].data, tiles[i].dataSize, DT_COMPRESSEDTILE_FREE_DATA, &tileRef);
                if (dtStatusFailed((dtStatus)status))
                {
                    dtFree(tiles[i].data);
                    tiles[i].data = 0x0;
                }
                else
                {
                    tileCache_->buildNavMeshTile(tileRef, navMesh_);
                    ++numTiles;
                }
            }
        }
    }

    URHO3D_LOGDEBUG("Rebuilt " + String(numTiles) + " tiles of the navigation mesh");
    return true;
}


void DynamicNavigationMesh::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (!debug || !navMesh_ || !node_)
        return;

    const Matrix3x4& worldTransform = node_->GetWorldTransform();

    const dtNavMesh* navMesh = navMesh_;

    for (int z = 0; z < numTilesZ_; ++z)
    {
        for (int x = 0; x < numTilesX_; ++x)
        {
            // Get the layers from the tile-cache
            const dtMeshTile* tiles[TILECACHE_MAXLAYERS];
            int tileCount = navMesh->getTilesAt(x, z, tiles, TILECACHE_MAXLAYERS);
            for (int i = 0; i < tileCount; ++i)
            {
                const dtMeshTile* tile = tiles[i];
                if (!tile)
                    continue;

                for (int i = 0; i < tile->header->polyCount; ++i)
                {
                    dtPoly* poly = tile->polys + i;
                    for (unsigned j = 0; j < poly->vertCount; ++j)
                    {
                        debug->AddLine(worldTransform * *reinterpret_cast<const Vector3*>(&tile->verts[poly->verts[j] * 3]),
                            worldTransform * *reinterpret_cast<const Vector3*>(&tile->verts[poly->verts[(j + 1) % poly->vertCount] * 3]),
                            Color::YELLOW, depthTest);
                    }
                }
            }
        }
    }

    Scene* scene = GetScene();
    if (scene)
    {
        // Draw Obstacle components
        if (drawObstacles_)
        {
            PODVector<Node*> obstacles;
            scene->GetChildrenWithComponent<Obstacle>(obstacles, true);
            for (unsigned i = 0; i < obstacles.Size(); ++i)
            {
                Obstacle* obstacle = obstacles[i]->GetComponent<Obstacle>();
                if (obstacle && obstacle->IsEnabledEffective())
                    obstacle->DrawDebugGeometry(debug, depthTest);
            }
        }

        // Draw OffMeshConnection components
        if (drawOffMeshConnections_)
        {
            PODVector<Node*> connections;
            scene->GetChildrenWithComponent<OffMeshConnection>(connections, true);
            for (unsigned i = 0; i < connections.Size(); ++i)
            {
                OffMeshConnection* connection = connections[i]->GetComponent<OffMeshConnection>();
                if (connection && connection->IsEnabledEffective())
                    connection->DrawDebugGeometry(debug, depthTest);
            }
        }

        // Draw NavArea components
        if (drawNavAreas_)
        {
            PODVector<Node*> areas;
            scene->GetChildrenWithComponent<NavArea>(areas, true);
            for (unsigned i = 0; i < areas.Size(); ++i)
            {
                NavArea* area = areas[i]->GetComponent<NavArea>();
                if (area && area->IsEnabledEffective())
                    area->DrawDebugGeometry(debug, depthTest);
            }
        }
    }
}

void DynamicNavigationMesh::DrawDebugGeometry(bool depthTest)
{
    Scene* scene = GetScene();
    if (scene)
    {
        DebugRenderer* debug = scene->GetComponent<DebugRenderer>();
        if (debug)
            DrawDebugGeometry(debug, depthTest);
    }
}

void DynamicNavigationMesh::SetNavigationDataAttr(const PODVector<unsigned char>& value)
{
    ReleaseNavigationMesh();

    if (value.Empty())
        return;

    MemoryBuffer buffer(value);
    boundingBox_ = buffer.ReadBoundingBox();
    numTilesX_ = buffer.ReadInt();
    numTilesZ_ = buffer.ReadInt();

    dtNavMeshParams params;
    buffer.Read(&params, sizeof(dtNavMeshParams));

    navMesh_ = dtAllocNavMesh();
    if (!navMesh_)
    {
        URHO3D_LOGERROR("Could not allocate navigation mesh");
        return;
    }

    if (dtStatusFailed(navMesh_->init(&params)))
    {
        URHO3D_LOGERROR("Could not initialize navigation mesh");
        ReleaseNavigationMesh();
        return;
    }

    dtTileCacheParams tcParams;
    buffer.Read(&tcParams, sizeof(tcParams));

    tileCache_ = dtAllocTileCache();
    if (!tileCache_)
    {
        URHO3D_LOGERROR("Could not allocate tile cache");
        ReleaseNavigationMesh();
        return;
    }
    if (dtStatusFailed(tileCache_->init(&tcParams, allocator_, compressor_, meshProcessor_)))
    {
        URHO3D_LOGERROR("Could not initialize tile cache");
        ReleaseNavigationMesh();
        return;
    }

    while (!buffer.IsEof())
    {
        dtTileCacheLayerHeader header;
        buffer.Read(&header, sizeof(dtTileCacheLayerHeader));
        const int dataSize = buffer.ReadInt();
        unsigned char* data = (unsigned char*)dtAlloc(dataSize, DT_ALLOC_PERM);
        buffer.Read(data, (unsigned)dataSize);

        if (dtStatusFailed(tileCache_->addTile(data, dataSize, DT_TILE_FREE_DATA, 0)))
        {
            URHO3D_LOGERROR("Failed to add tile");
            dtFree(data);
            return;
        }
    }

    for (int x = 0; x < numTilesX_; ++x)
    {
        for (int z = 0; z < numTilesZ_; ++z)
            tileCache_->buildNavMeshTilesAt(x, z, navMesh_);
    }

    tileCache_->update(0, navMesh_);
}

PODVector<unsigned char> DynamicNavigationMesh::GetNavigationDataAttr() const
{
    VectorBuffer ret;
    if (navMesh_ && tileCache_)
    {
        ret.WriteBoundingBox(boundingBox_);
        ret.WriteInt(numTilesX_);
        ret.WriteInt(numTilesZ_);

        const dtNavMeshParams* params = navMesh_->getParams();
        ret.Write(params, sizeof(dtNavMeshParams));

        const dtTileCacheParams* tcParams = tileCache_->getParams();
        ret.Write(tcParams, sizeof(dtTileCacheParams));

        for (int z = 0; z < numTilesZ_; ++z)
        {
            for (int x = 0; x < numTilesX_; ++x)
            {
                dtCompressedTileRef tiles[TILECACHE_MAXLAYERS];
                const int ct = tileCache_->getTilesAt(x, z, tiles, maxLayers_);
                for (int i = 0; i < ct; ++i)
                {
                    const dtCompressedTile* tile = tileCache_->getTileByRef(tiles[i]);
                    if (!tile || !tile->header || !tile->dataSize)
                        continue; // Don't write "void-space" tiles
                    // The header conveniently has the majority of the information required
                    ret.Write(tile->header, sizeof(dtTileCacheLayerHeader));
                    ret.WriteInt(tile->dataSize);
                    ret.Write(tile->data, (unsigned)tile->dataSize);
                }
            }
        }
    }
    return ret.GetBuffer();
}

void DynamicNavigationMesh::SetMaxLayers(unsigned maxLayers)
{
    // Set 3 as a minimum due to the tendency of layers to be constructed inside the hollow space of stacked objects
    // That behavior is unlikely to be expected by the end user
    maxLayers_ = Max(3, Min(maxLayers, TILECACHE_MAXLAYERS));
}

int DynamicNavigationMesh::BuildTile(Vector<NavigationGeometryInfo>& geometryList, int x, int z, TileCacheData* tiles)
{
    URHO3D_PROFILE(BuildNavigationMeshTile);

    tileCache_->removeTile(navMesh_->getTileRefAt(x, z, 0), 0, 0);

    float tileEdgeLength = (float)tileSize_ * cellSize_;

    BoundingBox tileBoundingBox(Vector3(
            boundingBox_.min_.x_ + tileEdgeLength * (float)x,
            boundingBox_.min_.y_,
            boundingBox_.min_.z_ + tileEdgeLength * (float)z),
        Vector3(
            boundingBox_.min_.x_ + tileEdgeLength * (float)(x + 1),
            boundingBox_.max_.y_,
            boundingBox_.min_.z_ + tileEdgeLength * (float)(z + 1)));

    DynamicNavBuildData build(allocator_);

    rcConfig cfg;
    memset(&cfg, 0, sizeof cfg);
    cfg.cs = cellSize_;
    cfg.ch = cellHeight_;
    cfg.walkableSlopeAngle = agentMaxSlope_;
    cfg.walkableHeight = (int)ceilf(agentHeight_ / cfg.ch);
    cfg.walkableClimb = (int)floorf(agentMaxClimb_ / cfg.ch);
    cfg.walkableRadius = (int)ceilf(agentRadius_ / cfg.cs);
    cfg.maxEdgeLen = (int)(edgeMaxLength_ / cellSize_);
    cfg.maxSimplificationError = edgeMaxError_;
    cfg.minRegionArea = (int)sqrtf(regionMinSize_);
    cfg.mergeRegionArea = (int)sqrtf(regionMergeSize_);
    cfg.maxVertsPerPoly = 6;
    cfg.tileSize = tileSize_;
    cfg.borderSize = cfg.walkableRadius + 3; // Add padding
    cfg.width = cfg.tileSize + cfg.borderSize * 2;
    cfg.height = cfg.tileSize + cfg.borderSize * 2;
    cfg.detailSampleDist = detailSampleDistance_ < 0.9f ? 0.0f : cellSize_ * detailSampleDistance_;
    cfg.detailSampleMaxError = cellHeight_ * detailSampleMaxError_;

    rcVcopy(cfg.bmin, &tileBoundingBox.min_.x_);
    rcVcopy(cfg.bmax, &tileBoundingBox.max_.x_);
    cfg.bmin[0] -= cfg.borderSize * cfg.cs;
    cfg.bmin[2] -= cfg.borderSize * cfg.cs;
    cfg.bmax[0] += cfg.borderSize * cfg.cs;
    cfg.bmax[2] += cfg.borderSize * cfg.cs;

    BoundingBox expandedBox(*reinterpret_cast<Vector3*>(cfg.bmin), *reinterpret_cast<Vector3*>(cfg.bmax));
    GetTileGeometry(&build, geometryList, expandedBox);

    if (build.vertices_.Empty() || build.indices_.Empty())
        return 0; // Nothing to do

    build.heightField_ = rcAllocHeightfield();
    if (!build.heightField_)
    {
        URHO3D_LOGERROR("Could not allocate heightfield");
        return 0;
    }

    if (!rcCreateHeightfield(build.ctx_, *build.heightField_, cfg.width, cfg.height, cfg.bmin, cfg.bmax, cfg.cs,
        cfg.ch))
    {
        URHO3D_LOGERROR("Could not create heightfield");
        return 0;
    }

    unsigned numTriangles = build.indices_.Size() / 3;
    SharedArrayPtr<unsigned char> triAreas(new unsigned char[numTriangles]);
    memset(triAreas.Get(), 0, numTriangles);

    rcMarkWalkableTriangles(build.ctx_, cfg.walkableSlopeAngle, &build.vertices_[0].x_, build.vertices_.Size(),
        &build.indices_[0], numTriangles, triAreas.Get());
    rcRasterizeTriangles(build.ctx_, &build.vertices_[0].x_, build.vertices_.Size(), &build.indices_[0],
        triAreas.Get(), numTriangles, *build.heightField_, cfg.walkableClimb);
    rcFilterLowHangingWalkableObstacles(build.ctx_, cfg.walkableClimb, *build.heightField_);

    rcFilterLedgeSpans(build.ctx_, cfg.walkableHeight, cfg.walkableClimb, *build.heightField_);
    rcFilterWalkableLowHeightSpans(build.ctx_, cfg.walkableHeight, *build.heightField_);

    build.compactHeightField_ = rcAllocCompactHeightfield();
    if (!build.compactHeightField_)
    {
        URHO3D_LOGERROR("Could not allocate create compact heightfield");
        return 0;
    }
    if (!rcBuildCompactHeightfield(build.ctx_, cfg.walkableHeight, cfg.walkableClimb, *build.heightField_,
        *build.compactHeightField_))
    {
        URHO3D_LOGERROR("Could not build compact heightfield");
        return 0;
    }
    if (!rcErodeWalkableArea(build.ctx_, cfg.walkableRadius, *build.compactHeightField_))
    {
        URHO3D_LOGERROR("Could not erode compact heightfield");
        return 0;
    }

    // area volumes
    for (unsigned i = 0; i < build.navAreas_.Size(); ++i)
        rcMarkBoxArea(build.ctx_, &build.navAreas_[i].bounds_.min_.x_, &build.navAreas_[i].bounds_.max_.x_,
            build.navAreas_[i].areaID_, *build.compactHeightField_);

    if (this->partitionType_ == NAVMESH_PARTITION_WATERSHED)
    {
        if (!rcBuildDistanceField(build.ctx_, *build.compactHeightField_))
        {
            URHO3D_LOGERROR("Could not build distance field");
            return 0;
        }
        if (!rcBuildRegions(build.ctx_, *build.compactHeightField_, cfg.borderSize, cfg.minRegionArea,
            cfg.mergeRegionArea))
        {
            URHO3D_LOGERROR("Could not build regions");
            return 0;
        }
    }
    else
    {
        if (!rcBuildRegionsMonotone(build.ctx_, *build.compactHeightField_, cfg.borderSize, cfg.minRegionArea, cfg.mergeRegionArea))
        {
            URHO3D_LOGERROR("Could not build monotone regions");
            return 0;
        }
    }

    build.heightFieldLayers_ = rcAllocHeightfieldLayerSet();
    if (!build.heightFieldLayers_)
    {
        URHO3D_LOGERROR("Could not allocate height field layer set");
        return 0;
    }

    if (!rcBuildHeightfieldLayers(build.ctx_, *build.compactHeightField_, cfg.borderSize, cfg.walkableHeight,
        *build.heightFieldLayers_))
    {
        URHO3D_LOGERROR("Could not build height field layers");
        return 0;
    }

    int retCt = 0;
    for (int i = 0; i < build.heightFieldLayers_->nlayers; ++i)
    {
        dtTileCacheLayerHeader header;
        header.magic = DT_TILECACHE_MAGIC;
        header.version = DT_TILECACHE_VERSION;
        header.tx = x;
        header.ty = z;
        header.tlayer = i;

        rcHeightfieldLayer* layer = &build.heightFieldLayers_->layers[i];

        // Tile info.
        rcVcopy(header.bmin, layer->bmin);
        rcVcopy(header.bmax, layer->bmax);
        header.width = (unsigned char)layer->width;
        header.height = (unsigned char)layer->height;
        header.minx = (unsigned char)layer->minx;
        header.maxx = (unsigned char)layer->maxx;
        header.miny = (unsigned char)layer->miny;
        header.maxy = (unsigned char)layer->maxy;
        header.hmin = (unsigned short)layer->hmin;
        header.hmax = (unsigned short)layer->hmax;

        if (dtStatusFailed(
            dtBuildTileCacheLayer(compressor_/*compressor*/, &header, layer->heights, layer->areas/*areas*/, layer->cons,
                &(tiles[retCt].data), &tiles[retCt].dataSize)))
        {
            URHO3D_LOGERROR("Failed to build tile cache layers");
            return 0;
        }
        else
            ++retCt;
    }

    // Send a notification of the rebuild of this tile to anyone interested
    {
        using namespace NavigationAreaRebuilt;
        VariantMap& eventData = GetContext()->GetEventDataMap();
        eventData[P_NODE] = GetNode();
        eventData[P_MESH] = this;
        eventData[P_BOUNDSMIN] = Variant(tileBoundingBox.min_);
        eventData[P_BOUNDSMAX] = Variant(tileBoundingBox.max_);
        SendEvent(E_NAVIGATION_AREA_REBUILT, eventData);
    }

    return retCt;
}

PODVector<OffMeshConnection*> DynamicNavigationMesh::CollectOffMeshConnections(const BoundingBox& bounds)
{
    PODVector<OffMeshConnection*> connections;
    node_->GetComponents<OffMeshConnection>(connections, true);
    for (unsigned i = 0; i < connections.Size(); ++i)
    {
        OffMeshConnection* connection = connections[i];
        if (!(connection->IsEnabledEffective() && connection->GetEndPoint()))
        {
            // discard this connection
            connections.Erase(i);
            --i;
        }
    }

    return connections;
}

void DynamicNavigationMesh::ReleaseNavigationMesh()
{
    NavigationMesh::ReleaseNavigationMesh();
    ReleaseTileCache();
}

void DynamicNavigationMesh::ReleaseTileCache()
{
    dtFreeTileCache(tileCache_);
    tileCache_ = 0;
}

void DynamicNavigationMesh::OnSceneSet(Scene* scene)
{
    // Subscribe to the scene subsystem update, which will trigger the tile cache to update the nav mesh
    if (scene)
        SubscribeToEvent(scene, E_SCENESUBSYSTEMUPDATE, URHO3D_HANDLER(DynamicNavigationMesh, HandleSceneSubsystemUpdate));
    else
        UnsubscribeFromEvent(E_SCENESUBSYSTEMUPDATE);
}

void DynamicNavigationMesh::AddObstacle(Obstacle* obstacle, bool silent)
{
    if (tileCache_)
    {
        float pos[3];
        Vector3 obsPos = obstacle->GetNode()->GetWorldPosition();
        rcVcopy(pos, &obsPos.x_);
        dtObstacleRef refHolder;

        // Because dtTileCache doesn't process obstacle requests while updating tiles
        // it's necessary update until sufficient request space is available
        while (tileCache_->isObstacleQueueFull())
            tileCache_->update(1, navMesh_);

        if (dtStatusFailed(tileCache_->addObstacle(pos, obstacle->GetRadius(), obstacle->GetHeight(), &refHolder)))
        {
            URHO3D_LOGERROR("Failed to add obstacle");
            return;
        }
        obstacle->obstacleId_ = refHolder;
        assert(refHolder > 0);

        if (!silent)
        {
            using namespace NavigationObstacleAdded;
            VariantMap& eventData = GetContext()->GetEventDataMap();
            eventData[P_NODE] = obstacle->GetNode();
            eventData[P_OBSTACLE] = obstacle;
            eventData[P_POSITION] = obstacle->GetNode()->GetWorldPosition();
            eventData[P_RADIUS] = obstacle->GetRadius();
            eventData[P_HEIGHT] = obstacle->GetHeight();
            SendEvent(E_NAVIGATION_OBSTACLE_ADDED, eventData);
        }
    }
}

void DynamicNavigationMesh::ObstacleChanged(Obstacle* obstacle)
{
    if (tileCache_)
    {
        RemoveObstacle(obstacle, true);
        AddObstacle(obstacle, true);
    }
}

void DynamicNavigationMesh::RemoveObstacle(Obstacle* obstacle, bool silent)
{
    if (tileCache_ && obstacle->obstacleId_ > 0)
    {
        // Because dtTileCache doesn't process obstacle requests while updating tiles
        // it's necessary update until sufficient request space is available
        while (tileCache_->isObstacleQueueFull())
            tileCache_->update(1, navMesh_);

        if (dtStatusFailed(tileCache_->removeObstacle(obstacle->obstacleId_)))
        {
            URHO3D_LOGERROR("Failed to remove obstacle");
            return;
        }
        obstacle->obstacleId_ = 0;
        // Require a node in order to send an event
        if (!silent && obstacle->GetNode())
        {
            using namespace NavigationObstacleRemoved;
            VariantMap& eventData = GetContext()->GetEventDataMap();
            eventData[P_NODE] = obstacle->GetNode();
            eventData[P_OBSTACLE] = obstacle;
            eventData[P_POSITION] = obstacle->GetNode()->GetWorldPosition();
            eventData[P_RADIUS] = obstacle->GetRadius();
            eventData[P_HEIGHT] = obstacle->GetHeight();
            SendEvent(E_NAVIGATION_OBSTACLE_REMOVED, eventData);
        }
    }
}

void DynamicNavigationMesh::HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace SceneSubsystemUpdate;

    if (tileCache_ && navMesh_ && IsEnabledEffective())
        tileCache_->update(eventData[P_TIMESTEP].GetFloat(), navMesh_);
}

}
