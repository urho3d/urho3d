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

#ifdef URHO3D_PHYSICS
#include "../Physics/CollisionShape.h"
#endif
#include "../Core/Context.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/Geometry.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../Graphics/Model.h"
#include "../Navigation/Navigable.h"
#include "../Navigation/NavigationMesh.h"
#include "../Navigation/OffMeshConnection.h"
#include "../Core/Profiler.h"
#include "../Scene/Scene.h"
#include "../Graphics/StaticModel.h"
#include "../Graphics/TerrainPatch.h"
#include "../IO/VectorBuffer.h"

#include <cfloat>
#include <Detour/DetourNavMesh.h>
#include <Detour/DetourNavMeshBuilder.h>
#include <Detour/DetourNavMeshQuery.h>
#include <Recast/Recast.h>

#include "../DebugNew.h"

namespace Urho3D
{

const char* NAVIGATION_CATEGORY = "Navigation";

static const int DEFAULT_TILE_SIZE = 128;
static const float DEFAULT_CELL_SIZE = 0.3f;
static const float DEFAULT_CELL_HEIGHT = 0.2f;
static const float DEFAULT_AGENT_HEIGHT = 2.0f;
static const float DEFAULT_AGENT_RADIUS = 0.6f;
static const float DEFAULT_AGENT_MAX_CLIMB = 0.9f;
static const float DEFAULT_AGENT_MAX_SLOPE = 45.0f;
static const float DEFAULT_REGION_MIN_SIZE = 8.0f;
static const float DEFAULT_REGION_MERGE_SIZE = 20.0f;
static const float DEFAULT_EDGE_MAX_LENGTH = 12.0f;
static const float DEFAULT_EDGE_MAX_ERROR = 1.3f;
static const float DEFAULT_DETAIL_SAMPLE_DISTANCE = 6.0f;
static const float DEFAULT_DETAIL_SAMPLE_MAX_ERROR = 1.0f;

static const int MAX_POLYS = 2048;

/// Temporary data for building one tile of the navigation mesh.
struct NavigationBuildData
{
    /// Construct.
    NavigationBuildData() :
        ctx_(new rcContext(false)),
        heightField_(0),
        compactHeightField_(0),
        contourSet_(0),
        polyMesh_(0),
        polyMeshDetail_(0)
    {
    }

    /// Destruct.
    ~NavigationBuildData()
    {
        delete(ctx_);
        rcFreeHeightField(heightField_);
        rcFreeCompactHeightfield(compactHeightField_);
        rcFreeContourSet(contourSet_);
        rcFreePolyMesh(polyMesh_);
        rcFreePolyMeshDetail(polyMeshDetail_);

        ctx_ = 0;
        heightField_ = 0;
        compactHeightField_ = 0;
        contourSet_ = 0;
        polyMesh_ = 0;
        polyMeshDetail_ = 0;
    }

    /// World-space bounding box of the navigation mesh tile.
    BoundingBox worldBoundingBox_;
    /// Vertices from geometries.
    PODVector<Vector3> vertices_;
    /// Triangle indices from geometries.
    PODVector<int> indices_;
    /// Offmesh connection vertices.
    PODVector<Vector3> offMeshVertices_;
    /// Offmesh connection radii.
    PODVector<float> offMeshRadii_;
    /// Offmesh connection flags.
    PODVector<unsigned short> offMeshFlags_;
    /// Offmesh connection areas.
    PODVector<unsigned char> offMeshAreas_;
    /// Offmesh connection direction.
    PODVector<unsigned char> offMeshDir_;
    /// Recast context.
    rcContext* ctx_;
    /// Recast heightfield.
    rcHeightfield* heightField_;
    /// Recast compact heightfield.
    rcCompactHeightfield* compactHeightField_;
    /// Recast contour set.
    rcContourSet* contourSet_;
    /// Recast poly mesh.
    rcPolyMesh* polyMesh_;
    /// Recast detail poly mesh.
    rcPolyMeshDetail* polyMeshDetail_;
};

/// Temporary data for finding a path.
struct FindPathData
{
    // Polygons.
    dtPolyRef polys_[MAX_POLYS];
    // Polygons on the path.
    dtPolyRef pathPolys_[MAX_POLYS];
    // Points on the path.
    Vector3 pathPoints_[MAX_POLYS];
    // Flags on the path.
    unsigned char pathFlags_[MAX_POLYS];
};

NavigationMesh::NavigationMesh(Context* context) :
    Component(context),
    navMesh_(0),
    navMeshQuery_(0),
    queryFilter_(new dtQueryFilter()),
    pathData_(new FindPathData()),
    tileSize_(DEFAULT_TILE_SIZE),
    cellSize_(DEFAULT_CELL_SIZE),
    cellHeight_(DEFAULT_CELL_HEIGHT),
    agentHeight_(DEFAULT_AGENT_HEIGHT),
    agentRadius_(DEFAULT_AGENT_RADIUS),
    agentMaxClimb_(DEFAULT_AGENT_MAX_CLIMB),
    agentMaxSlope_(DEFAULT_AGENT_MAX_SLOPE),
    regionMinSize_(DEFAULT_REGION_MIN_SIZE),
    regionMergeSize_(DEFAULT_REGION_MERGE_SIZE),
    edgeMaxLength_(DEFAULT_EDGE_MAX_LENGTH),
    edgeMaxError_(DEFAULT_EDGE_MAX_ERROR),
    detailSampleDistance_(DEFAULT_DETAIL_SAMPLE_DISTANCE),
    detailSampleMaxError_(DEFAULT_DETAIL_SAMPLE_MAX_ERROR),
    padding_(Vector3::ONE),
    numTilesX_(0),
    numTilesZ_(0)
{
}

NavigationMesh::~NavigationMesh()
{
    ReleaseNavigationMesh();

    delete queryFilter_;
    queryFilter_ = 0;

    delete pathData_;
    pathData_ = 0;
}

void NavigationMesh::RegisterObject(Context* context)
{
    context->RegisterFactory<NavigationMesh>(NAVIGATION_CATEGORY);

    ACCESSOR_ATTRIBUTE("Tile Size", GetTileSize, SetTileSize, int, DEFAULT_TILE_SIZE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Cell Size", GetCellSize, SetCellSize, float, DEFAULT_CELL_SIZE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Cell Height", GetCellHeight, SetCellHeight, float, DEFAULT_CELL_HEIGHT, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Agent Height", GetAgentHeight, SetAgentHeight, float, DEFAULT_AGENT_HEIGHT, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Agent Radius", GetAgentRadius, SetAgentRadius, float, DEFAULT_AGENT_RADIUS, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Agent Max Climb", GetAgentMaxClimb, SetAgentMaxClimb, float, DEFAULT_AGENT_MAX_CLIMB, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Agent Max Slope", GetAgentMaxSlope, SetAgentMaxSlope, float, DEFAULT_AGENT_MAX_SLOPE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Region Min Size", GetRegionMinSize, SetRegionMinSize, float, DEFAULT_REGION_MIN_SIZE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Region Merge Size", GetRegionMergeSize, SetRegionMergeSize, float, DEFAULT_REGION_MERGE_SIZE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Edge Max Length", GetEdgeMaxLength, SetEdgeMaxLength, float, DEFAULT_EDGE_MAX_LENGTH, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Edge Max Error", GetEdgeMaxError, SetEdgeMaxError, float, DEFAULT_EDGE_MAX_ERROR, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Detail Sample Distance", GetDetailSampleDistance, SetDetailSampleDistance, float, DEFAULT_DETAIL_SAMPLE_DISTANCE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Detail Sample Max Error", GetDetailSampleMaxError, SetDetailSampleMaxError, float, DEFAULT_DETAIL_SAMPLE_MAX_ERROR, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Bounding Box Padding", GetPadding, SetPadding, Vector3, Vector3::ONE, AM_DEFAULT);
    MIXED_ACCESSOR_ATTRIBUTE("Navigation Data", GetNavigationDataAttr, SetNavigationDataAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_FILE | AM_NOEDIT);
}

void NavigationMesh::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (!debug || !navMesh_ || !node_)
        return;

    const Matrix3x4& worldTransform = node_->GetWorldTransform();

    const dtNavMesh* navMesh = navMesh_;

    for (int z = 0; z < numTilesZ_; ++z)
    {
        for (int x = 0; x < numTilesX_; ++x)
        {
            const dtMeshTile* tile = navMesh->getTileAt(x, z, 0);
            if (!tile)
                continue;

            for (int i = 0; i < tile->header->polyCount; ++i)
            {
                dtPoly* poly = tile->polys + i;
                for (unsigned j = 0; j < poly->vertCount; ++j)
                {
                    debug->AddLine(
                        worldTransform * *reinterpret_cast<const Vector3*>(&tile->verts[poly->verts[j] * 3]),
                        worldTransform * *reinterpret_cast<const Vector3*>(&tile->verts[poly->verts[(j + 1) % poly->vertCount] * 3]),
                        Color::YELLOW,
                        depthTest
                    );
                }
            }
        }
    }
}

void NavigationMesh::SetTileSize(int size)
{
    tileSize_ = Max(size, 16);

    MarkNetworkUpdate();
}

void NavigationMesh::SetCellSize(float size)
{
    cellSize_ = Max(size, M_EPSILON);

    MarkNetworkUpdate();
}

void NavigationMesh::SetCellHeight(float height)
{
    cellHeight_ = Max(height, M_EPSILON);

    MarkNetworkUpdate();
}

void NavigationMesh::SetAgentHeight(float height)
{
    agentHeight_ = Max(height, M_EPSILON);

    MarkNetworkUpdate();
}

void NavigationMesh::SetAgentRadius(float radius)
{
    agentRadius_ = Max(radius, M_EPSILON);

    MarkNetworkUpdate();
}

void NavigationMesh::SetAgentMaxClimb(float maxClimb)
{
    agentMaxClimb_ = Max(maxClimb, M_EPSILON);

    MarkNetworkUpdate();
}

void NavigationMesh::SetAgentMaxSlope(float maxSlope)
{
    agentMaxSlope_ = Max(maxSlope, 0.0f);

    MarkNetworkUpdate();
}

void NavigationMesh::SetRegionMinSize(float size)
{
    regionMinSize_ = Max(size, M_EPSILON);

    MarkNetworkUpdate();
}

void NavigationMesh::SetRegionMergeSize(float size)
{
    regionMergeSize_ = Max(size, M_EPSILON);

    MarkNetworkUpdate();
}

void NavigationMesh::SetEdgeMaxLength(float length)
{
    edgeMaxLength_ = Max(length, M_EPSILON);

    MarkNetworkUpdate();
}

void NavigationMesh::SetEdgeMaxError(float error)
{
    edgeMaxError_ = Max(error, M_EPSILON);

    MarkNetworkUpdate();
}

void NavigationMesh::SetDetailSampleDistance(float distance)
{
    detailSampleDistance_ = Max(distance, M_EPSILON);

    MarkNetworkUpdate();
}

void NavigationMesh::SetDetailSampleMaxError(float error)
{
    detailSampleMaxError_ = Max(error, M_EPSILON);

    MarkNetworkUpdate();
}

void NavigationMesh::SetPadding(const Vector3& padding)
{
    padding_ = padding;

    MarkNetworkUpdate();
}

bool NavigationMesh::Build()
{
    PROFILE(BuildNavigationMesh);

    // Release existing navigation data and zero the bounding box
    ReleaseNavigationMesh();

    if (!node_)
        return false;

    if (!node_->GetWorldScale().Equals(Vector3::ONE))
        LOGWARNING("Navigation mesh root node has scaling. Agent parameters may not work as intended");

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
        PROFILE(BuildNavigationMesh);

        // Calculate number of tiles
        int gridW = 0, gridH = 0;
        float tileEdgeLength = (float)tileSize_ * cellSize_;
        rcCalcGridSize(&boundingBox_.min_.x_, &boundingBox_.max_.x_, cellSize_, &gridW, &gridH);
        numTilesX_ = (gridW + tileSize_ - 1) / tileSize_;
        numTilesZ_ = (gridH + tileSize_ - 1) / tileSize_;

        // Calculate max. number of tiles and polygons, 22 bits available to identify both tile & polygon within tile
        unsigned maxTiles = NextPowerOfTwo(numTilesX_ * numTilesZ_);
        unsigned tileBits = 0;
        unsigned temp = maxTiles;
        while (temp > 1)
        {
            temp >>= 1;
            ++tileBits;
        }

        unsigned maxPolys = 1 << (22 - tileBits);

        dtNavMeshParams params;
        rcVcopy(params.orig, &boundingBox_.min_.x_);
        params.tileWidth = tileEdgeLength;
        params.tileHeight = tileEdgeLength;
        params.maxTiles = maxTiles;
        params.maxPolys = maxPolys;

        navMesh_ = dtAllocNavMesh();
        if (!navMesh_)
        {
            LOGERROR("Could not allocate navigation mesh");
            return false;
        }

        if (dtStatusFailed(navMesh_->init(&params)))
        {
            LOGERROR("Could not initialize navigation mesh");
            ReleaseNavigationMesh();
            return false;
        }

        // Build each tile
        unsigned numTiles = 0;

        for (int z = 0; z < numTilesZ_; ++z)
        {
            for (int x = 0; x < numTilesX_; ++x)
            {
                if (BuildTile(geometryList, x, z))
                    ++numTiles;
            }
        }

        LOGDEBUG("Built navigation mesh with " + String(numTiles) + " tiles");
        return true;
    }
}

bool NavigationMesh::Build(const BoundingBox& boundingBox)
{
    PROFILE(BuildPartialNavigationMesh);

    if (!node_)
        return false;

    if (!navMesh_)
    {
        LOGERROR("Navigation mesh must first be built fully before it can be partially rebuilt");
        return false;
    }

    if (!node_->GetWorldScale().Equals(Vector3::ONE))
        LOGWARNING("Navigation mesh root node has scaling. Agent parameters may not work as intended");

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
            if (BuildTile(geometryList, x, z))
                ++numTiles;
        }
    }

    LOGDEBUG("Rebuilt " + String(numTiles) + " tiles of the navigation mesh");
    return true;
}

Vector3 NavigationMesh::FindNearestPoint(const Vector3& point, const Vector3& extents)
{
    if(!InitializeQuery())
        return point;

    const Matrix3x4& transform = node_->GetWorldTransform();
    Matrix3x4 inverse = transform.Inverse();

    Vector3 localPoint = inverse * point;
    Vector3 nearestPoint;

    dtPolyRef pointRef;
    navMeshQuery_->findNearestPoly(&localPoint.x_, &extents.x_, queryFilter_, &pointRef, &nearestPoint.x_);
    if (!pointRef)
        return point;

    return transform*nearestPoint;
}

Vector3 NavigationMesh::MoveAlongSurface(const Vector3& start, const Vector3& end, const Vector3& extents, int maxVisited)
{
    if (!InitializeQuery())
        return end;

    const Matrix3x4& transform = node_->GetWorldTransform();
    Matrix3x4 inverse = transform.Inverse();

    Vector3 localStart = inverse * start;
    Vector3 localEnd = inverse * end;

    dtPolyRef startRef;
    navMeshQuery_->findNearestPoly(&localStart.x_, &extents.x_, queryFilter_, &startRef, 0);
    if (!startRef)
        return end;

    Vector3 resultPos;
    int visitedCount = 0;
    maxVisited = Max(maxVisited, 0);
    PODVector<dtPolyRef> visited(maxVisited);
    navMeshQuery_->moveAlongSurface(startRef, &localStart.x_, &localEnd.x_, queryFilter_, &resultPos.x_, maxVisited ?
        &visited[0] : (dtPolyRef*)0, &visitedCount, maxVisited);
    return transform * resultPos;
}

void NavigationMesh::FindPath(PODVector<Vector3>& dest, const Vector3& start, const Vector3& end, const Vector3& extents)
{
    PROFILE(FindPath);

    dest.Clear();

    if (!InitializeQuery())
        return;

    // Navigation data is in local space. Transform path points from world to local
    const Matrix3x4& transform = node_->GetWorldTransform();
    Matrix3x4 inverse = transform.Inverse();

    Vector3 localStart = inverse * start;
    Vector3 localEnd = inverse * end;

    dtPolyRef startRef;
    dtPolyRef endRef;
    navMeshQuery_->findNearestPoly(&localStart.x_, &extents.x_, queryFilter_, &startRef, 0);
    navMeshQuery_->findNearestPoly(&localEnd.x_, &extents.x_, queryFilter_, &endRef, 0);

    if (!startRef || !endRef)
        return;

    int numPolys = 0;
    int numPathPoints = 0;

    navMeshQuery_->findPath(startRef, endRef, &localStart.x_, &localEnd.x_, queryFilter_, pathData_->polys_, &numPolys,
        MAX_POLYS);
    if (!numPolys)
        return;

    Vector3 actualLocalEnd = localEnd;

    // If full path was not found, clamp end point to the end polygon
    if (pathData_->polys_[numPolys - 1] != endRef)
        navMeshQuery_->closestPointOnPoly(pathData_->polys_[numPolys - 1], &localEnd.x_, &actualLocalEnd.x_, 0);

    navMeshQuery_->findStraightPath(&localStart.x_, &actualLocalEnd.x_, pathData_->polys_, numPolys,
        &pathData_->pathPoints_[0].x_, pathData_->pathFlags_, pathData_->pathPolys_, &numPathPoints, MAX_POLYS);

    // Transform path result back to world space
    for (int i = 0; i < numPathPoints; ++i)
        dest.Push(transform * pathData_->pathPoints_[i]);
}

Vector3 NavigationMesh::GetRandomPoint()
{
    if (!InitializeQuery())
        return Vector3::ZERO;

    dtPolyRef polyRef;
    Vector3 point(Vector3::ZERO);

    navMeshQuery_->findRandomPoint(queryFilter_, Random, &polyRef, &point.x_);

    return node_->GetWorldTransform() * point;
}

Vector3 NavigationMesh::GetRandomPointInCircle(const Vector3& center, float radius, const Vector3& extents)
{
    if (!InitializeQuery())
        return center;

    const Matrix3x4& transform = node_->GetWorldTransform();
    Matrix3x4 inverse = transform.Inverse();
    Vector3 localCenter = inverse * center;

    dtPolyRef startRef;
    navMeshQuery_->findNearestPoly(&localCenter.x_, &extents.x_, queryFilter_, &startRef, 0);
    if (!startRef)
        return center;

    dtPolyRef polyRef;
    Vector3 point(localCenter);

    navMeshQuery_->findRandomPointAroundCircle(startRef, &localCenter.x_, radius, queryFilter_, Random, &polyRef, &point.x_);

    return transform * point;
}

float NavigationMesh::GetDistanceToWall(const Vector3& point, float radius, const Vector3& extents)
{
    if (!InitializeQuery())
        return radius;

    const Matrix3x4& transform = node_->GetWorldTransform();
    Matrix3x4 inverse = transform.Inverse();
    Vector3 localPoint = inverse * point;

    dtPolyRef startRef;
    navMeshQuery_->findNearestPoly(&localPoint.x_, &extents.x_, queryFilter_, &startRef, 0);
    if (!startRef)
        return radius;

    float hitDist = radius;
    Vector3 hitPos;
    Vector3 hitNormal;

    navMeshQuery_->findDistanceToWall(startRef, &localPoint.x_, radius, queryFilter_, &hitDist, &hitPos.x_, &hitNormal.x_);
    return hitDist;
}

Vector3 NavigationMesh::Raycast(const Vector3& start, const Vector3& end, const Vector3& extents)
{
    if (!InitializeQuery())
        return end;

    const Matrix3x4& transform = node_->GetWorldTransform();
    Matrix3x4 inverse = transform.Inverse();

    Vector3 localStart = inverse * start;
    Vector3 localEnd = inverse * end;

    dtPolyRef startRef;
    navMeshQuery_->findNearestPoly(&localStart.x_, &extents.x_, queryFilter_, &startRef, 0);
    if (!startRef)
        return end;

    Vector3 localHitNormal;
    float t;
    int numPolys;

    navMeshQuery_->raycast(startRef, &localStart.x_, &localEnd.x_, queryFilter_, &t, &localHitNormal.x_, pathData_->polys_, &numPolys, MAX_POLYS);
    if (t == FLT_MAX)
        t = 1.0f;

    return start.Lerp(end, t);
}

void NavigationMesh::DrawDebugGeometry(bool depthTest)
{
    Scene* scene = GetScene();
    if (scene)
    {
        DebugRenderer* debug = scene->GetComponent<DebugRenderer>();
        if (debug)
            DrawDebugGeometry(debug, depthTest);
    }
}

BoundingBox NavigationMesh::GetWorldBoundingBox() const
{
    return node_ ? boundingBox_.Transformed(node_->GetWorldTransform()) : boundingBox_;
}

void NavigationMesh::SetNavigationDataAttr(const PODVector<unsigned char>& value)
{
    ReleaseNavigationMesh();

    if (value.Empty())
        return;

    MemoryBuffer buffer(value);

    boundingBox_ = buffer.ReadBoundingBox();
    numTilesX_ = buffer.ReadInt();
    numTilesZ_ = buffer.ReadInt();

    dtNavMeshParams params;
    rcVcopy(params.orig, &boundingBox_.min_.x_);
    params.tileWidth = buffer.ReadFloat();
    params.tileHeight = buffer.ReadFloat();
    params.maxTiles = buffer.ReadInt();
    params.maxPolys = buffer.ReadInt();

    navMesh_ = dtAllocNavMesh();
    if (!navMesh_)
    {
        LOGERROR("Could not allocate navigation mesh");
        return;
    }

    if (dtStatusFailed(navMesh_->init(&params)))
    {
        LOGERROR("Could not initialize navigation mesh");
        ReleaseNavigationMesh();
        return;
    }

    unsigned numTiles = 0;

    while (!buffer.IsEof())
    {
        /*int x =*/ buffer.ReadInt();
        /*int z =*/ buffer.ReadInt();
        /*dtTileRef tileRef =*/ buffer.ReadUInt();
        unsigned navDataSize = buffer.ReadUInt();

        unsigned char* navData = (unsigned char*)dtAlloc(navDataSize, DT_ALLOC_PERM);
        if (!navData)
        {
            LOGERROR("Could not allocate data for navigation mesh tile");
            return;
        }

        buffer.Read(navData, navDataSize);
        if (dtStatusFailed(navMesh_->addTile(navData, navDataSize, DT_TILE_FREE_DATA, 0, 0)))
        {
            LOGERROR("Failed to add navigation mesh tile");
            dtFree(navData);
            return;
        }
        else
            ++numTiles;
    }

    LOGDEBUG("Created navigation mesh with " + String(numTiles) + " tiles from serialized data");
}

PODVector<unsigned char> NavigationMesh::GetNavigationDataAttr() const
{
    VectorBuffer ret;

    if (navMesh_)
    {
        ret.WriteBoundingBox(boundingBox_);
        ret.WriteInt(numTilesX_);
        ret.WriteInt(numTilesZ_);

        const dtNavMeshParams* params = navMesh_->getParams();
        ret.WriteFloat(params->tileWidth);
        ret.WriteFloat(params->tileHeight);
        ret.WriteInt(params->maxTiles);
        ret.WriteInt(params->maxPolys);

        const dtNavMesh* navMesh = navMesh_;

        for (int z = 0; z < numTilesZ_; ++z)
        {
            for (int x = 0; x < numTilesX_; ++x)
            {
                const dtMeshTile* tile = navMesh->getTileAt(x, z, 0);
                if (!tile)
                    continue;

                ret.WriteInt(x);
                ret.WriteInt(z);
                ret.WriteUInt(navMesh->getTileRef(tile));
                ret.WriteUInt(tile->dataSize);
                ret.Write(tile->data, tile->dataSize);
            }
        }
    }

    return ret.GetBuffer();
}

void NavigationMesh::CollectGeometries(Vector<NavigationGeometryInfo>& geometryList)
{
    PROFILE(CollectNavigationGeometry);

    // Get Navigable components from child nodes, not from whole scene. This makes it possible to partition
    // the scene into several navigation meshes
    PODVector<Navigable*> navigables;
    node_->GetComponents<Navigable>(navigables, true);

    HashSet<Node*> processedNodes;
    for (unsigned i = 0; i < navigables.Size(); ++i)
    {
        if (navigables[i]->IsEnabledEffective())
            CollectGeometries(geometryList, navigables[i]->GetNode(), processedNodes, navigables[i]->IsRecursive());
    }

    // Get offmesh connections
    Matrix3x4 inverse = node_->GetWorldTransform().Inverse();
    PODVector<OffMeshConnection*> connections;
    node_->GetComponents<OffMeshConnection>(connections, true);

    for (unsigned i = 0; i < connections.Size(); ++i)
    {
        OffMeshConnection* connection = connections[i];
        if (connection->IsEnabledEffective() && connection->GetEndPoint())
        {
            const Matrix3x4& transform = connection->GetNode()->GetWorldTransform();

            NavigationGeometryInfo info;
            info.component_ = connection;
            info.boundingBox_ = BoundingBox(Sphere(transform.Translation(), connection->GetRadius())).Transformed(inverse);

            geometryList.Push(info);
        }
    }
}

void NavigationMesh::CollectGeometries(Vector<NavigationGeometryInfo>& geometryList, Node* node, HashSet<Node*>& processedNodes, bool recursive)
{
    // Make sure nodes are not included twice
    if (processedNodes.Contains(node))
        return;
    processedNodes.Insert(node);

    Matrix3x4 inverse = node_->GetWorldTransform().Inverse();

#ifdef URHO3D_PHYSICS
    // Prefer compatible physics collision shapes (triangle mesh, convex hull, box) if found.
    // Then fallback to visible geometry
    PODVector<CollisionShape*> collisionShapes;
    node->GetComponents<CollisionShape>(collisionShapes);
    bool collisionShapeFound = false;

    for (unsigned i = 0; i < collisionShapes.Size(); ++i)
    {
        CollisionShape* shape = collisionShapes[i];
        if (!shape->IsEnabledEffective())
            continue;

        ShapeType type = shape->GetShapeType();
        if ((type == SHAPE_BOX || type == SHAPE_TRIANGLEMESH || type == SHAPE_CONVEXHULL) && shape->GetCollisionShape())
        {
            Matrix3x4 shapeTransform(shape->GetPosition(), shape->GetRotation(), shape->GetSize());

            NavigationGeometryInfo info;
            info.component_ = shape;
            info.transform_ = inverse * node->GetWorldTransform() * shapeTransform;
            info.boundingBox_ = shape->GetWorldBoundingBox().Transformed(inverse);

            geometryList.Push(info);
            collisionShapeFound = true;
        }
    }
    if (!collisionShapeFound)
#endif
    {
        PODVector<Drawable*> drawables;
        node->GetDerivedComponents<Drawable>(drawables);

        for (unsigned i = 0; i < drawables.Size(); ++i)
        {
            /// \todo Evaluate whether should handle other types. Now StaticModel & TerrainPatch are supported, others skipped
            Drawable* drawable = drawables[i];
            if (!drawable->IsEnabledEffective())
                continue;

            NavigationGeometryInfo info;

            if (drawable->GetType() == StaticModel::GetTypeStatic())
                info.lodLevel_ = static_cast<StaticModel*>(drawable)->GetOcclusionLodLevel();
            else if (drawable->GetType() == TerrainPatch::GetTypeStatic())
                info.lodLevel_ = 0;
            else
                continue;

            info.component_ = drawable;
            info.transform_ = inverse * node->GetWorldTransform();
            info.boundingBox_ = drawable->GetWorldBoundingBox().Transformed(inverse);

            geometryList.Push(info);
        }
    }

    if (recursive)
    {
        const Vector<SharedPtr<Node> >& children = node->GetChildren();
        for(unsigned i = 0; i < children.Size(); ++i)
            CollectGeometries(geometryList, children[i], processedNodes, recursive);
    }
}

void NavigationMesh::GetTileGeometry(NavigationBuildData& build, Vector<NavigationGeometryInfo>& geometryList, BoundingBox& box)
{
    Matrix3x4 inverse = node_->GetWorldTransform().Inverse();

    for (unsigned i = 0; i < geometryList.Size(); ++i)
    {
        if (box.IsInsideFast(geometryList[i].boundingBox_) != OUTSIDE)
        {
            const Matrix3x4& transform = geometryList[i].transform_;

            if (geometryList[i].component_->GetType() == OffMeshConnection::GetTypeStatic())
            {
                OffMeshConnection* connection = static_cast<OffMeshConnection*>(geometryList[i].component_);
                Vector3 start = inverse * connection->GetNode()->GetWorldPosition();
                Vector3 end = inverse * connection->GetEndPoint()->GetWorldPosition();

                build.offMeshVertices_.Push(start);
                build.offMeshVertices_.Push(end);
                build.offMeshRadii_.Push(connection->GetRadius());
                /// \todo Allow to define custom flags
                build.offMeshFlags_.Push(0x1);

                build.offMeshAreas_.Push(0);
                build.offMeshDir_.Push(connection->IsBidirectional() ? DT_OFFMESH_CON_BIDIR : 0);
                continue;
            }

#ifdef URHO3D_PHYSICS
            CollisionShape* shape = dynamic_cast<CollisionShape*>(geometryList[i].component_);
            if (shape)
            {
                switch (shape->GetShapeType())
                {
                case SHAPE_TRIANGLEMESH:
                    {
                        Model* model = shape->GetModel();
                        if (!model)
                            continue;

                        unsigned lodLevel = shape->GetLodLevel();
                        for (unsigned j = 0; j < model->GetNumGeometries(); ++j)
                            AddTriMeshGeometry(build, model->GetGeometry(j, lodLevel), transform);
                    }
                    break;

                case SHAPE_CONVEXHULL:
                    {
                        ConvexData* data = static_cast<ConvexData*>(shape->GetGeometryData());
                        if (!data)
                            continue;

                        unsigned numVertices = data->vertexCount_;
                        unsigned numIndices = data->indexCount_;
                        unsigned destVertexStart = build.vertices_.Size();

                        for (unsigned j = 0; j < numVertices; ++j)
                            build.vertices_.Push(transform * data->vertexData_[j]);

                        for (unsigned j = 0; j < numIndices; ++j)
                            build.indices_.Push(data->indexData_[j] + destVertexStart);
                    }
                    break;

                case SHAPE_BOX:
                    {
                        unsigned destVertexStart = build.vertices_.Size();

                        build.vertices_.Push(transform * Vector3(-0.5f, 0.5f, -0.5f));
                        build.vertices_.Push(transform * Vector3(0.5f, 0.5f, -0.5f));
                        build.vertices_.Push(transform * Vector3(0.5f, -0.5f, -0.5f));
                        build.vertices_.Push(transform * Vector3(-0.5f, -0.5f, -0.5f));
                        build.vertices_.Push(transform * Vector3(-0.5f, 0.5f, 0.5f));
                        build.vertices_.Push(transform * Vector3(0.5f, 0.5f, 0.5f));
                        build.vertices_.Push(transform * Vector3(0.5f, -0.5f, 0.5f));
                        build.vertices_.Push(transform * Vector3(-0.5f, -0.5f, 0.5f));

                        const unsigned indices[] = {
                            0, 1, 2, 0, 2, 3, 1, 5, 6, 1, 6, 2, 4, 5, 1, 4, 1, 0, 5, 4, 7, 5, 7, 6,
                            4, 0, 3, 4, 3, 7, 1, 0, 4, 1, 4, 5
                        };

                        for (unsigned j = 0; j < 36; ++j)
                            build.indices_.Push(indices[j] + destVertexStart);
                    }
                    break;

                default:
                    break;
                }

                continue;
            }
#endif
            Drawable* drawable = dynamic_cast<Drawable*>(geometryList[i].component_);
            if (drawable)
            {
                const Vector<SourceBatch>& batches = drawable->GetBatches();

                for (unsigned j = 0; j < batches.Size(); ++j)
                    AddTriMeshGeometry(build, drawable->GetLodGeometry(j, geometryList[i].lodLevel_), transform);
            }
        }
    }
}

void NavigationMesh::AddTriMeshGeometry(NavigationBuildData& build, Geometry* geometry, const Matrix3x4& transform)
{
    if (!geometry)
        return;

    const unsigned char* vertexData;
    const unsigned char* indexData;
    unsigned vertexSize;
    unsigned indexSize;
    unsigned elementMask;

    geometry->GetRawData(vertexData, vertexSize, indexData, indexSize, elementMask);
    if (!vertexData || !indexData || (elementMask & MASK_POSITION) == 0)
        return;

    unsigned srcIndexStart = geometry->GetIndexStart();
    unsigned srcIndexCount = geometry->GetIndexCount();
    unsigned srcVertexStart = geometry->GetVertexStart();
    unsigned srcVertexCount = geometry->GetVertexCount();

    if (!srcIndexCount)
        return;

    unsigned destVertexStart = build.vertices_.Size();

    for (unsigned k = srcVertexStart; k < srcVertexStart + srcVertexCount; ++k)
    {
        Vector3 vertex = transform * *((const Vector3*)(&vertexData[k * vertexSize]));
        build.vertices_.Push(vertex);
    }

    // Copy remapped indices
    if (indexSize == sizeof(unsigned short))
    {
        const unsigned short* indices = ((const unsigned short*)indexData) + srcIndexStart;
        const unsigned short* indicesEnd = indices + srcIndexCount;

        while (indices < indicesEnd)
        {
            build.indices_.Push(*indices - srcVertexStart + destVertexStart);
            ++indices;
        }
    }
    else
    {
        const unsigned* indices = ((const unsigned*)indexData) + srcIndexStart;
        const unsigned* indicesEnd = indices + srcIndexCount;

        while (indices < indicesEnd)
        {
            build.indices_.Push(*indices - srcVertexStart + destVertexStart);
            ++indices;
        }
    }
}

bool NavigationMesh::BuildTile(Vector<NavigationGeometryInfo>& geometryList, int x, int z)
{
    PROFILE(BuildNavigationMeshTile);

    // Remove previous tile (if any)
    navMesh_->removeTile(navMesh_->getTileRefAt(x, z, 0), 0, 0);

    float tileEdgeLength = (float)tileSize_ * cellSize_;

    BoundingBox tileBoundingBox(Vector3(
        boundingBox_.min_.x_ + tileEdgeLength * (float)x,
        boundingBox_.min_.y_,
        boundingBox_.min_.z_ + tileEdgeLength * (float)z
    ),
    Vector3(
        boundingBox_.min_.x_ + tileEdgeLength * (float)(x + 1),
        boundingBox_.max_.y_,
        boundingBox_.min_.z_ + tileEdgeLength * (float)(z + 1)
    ));

    NavigationBuildData build;

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
    GetTileGeometry(build, geometryList, expandedBox);

    if (build.vertices_.Empty() || build.indices_.Empty())
        return true; // Nothing to do

    build.heightField_ = rcAllocHeightfield();
    if (!build.heightField_)
    {
        LOGERROR("Could not allocate heightfield");
        return false;
    }

    if (!rcCreateHeightfield(build.ctx_, *build.heightField_, cfg.width, cfg.height, cfg.bmin, cfg.bmax, cfg.cs,
        cfg.ch))
    {
        LOGERROR("Could not create heightfield");
        return false;
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
        LOGERROR("Could not allocate create compact heightfield");
        return false;
    }
    if (!rcBuildCompactHeightfield(build.ctx_, cfg.walkableHeight, cfg.walkableClimb, *build.heightField_,
        *build.compactHeightField_))
    {
        LOGERROR("Could not build compact heightfield");
        return false;
    }
    if (!rcErodeWalkableArea(build.ctx_, cfg.walkableRadius, *build.compactHeightField_))
    {
        LOGERROR("Could not erode compact heightfield");
        return false;
    }
    if (!rcBuildDistanceField(build.ctx_, *build.compactHeightField_))
    {
        LOGERROR("Could not build distance field");
        return false;
    }
    if (!rcBuildRegions(build.ctx_, *build.compactHeightField_, cfg.borderSize, cfg.minRegionArea,
        cfg.mergeRegionArea))
    {
        LOGERROR("Could not build regions");
        return false;
    }

    build.contourSet_ = rcAllocContourSet();
    if (!build.contourSet_)
    {
        LOGERROR("Could not allocate contour set");
        return false;
    }
    if (!rcBuildContours(build.ctx_, *build.compactHeightField_, cfg.maxSimplificationError, cfg.maxEdgeLen,
        *build.contourSet_))
    {
        LOGERROR("Could not create contours");
        return false;
    }

    build.polyMesh_ = rcAllocPolyMesh();
    if (!build.polyMesh_)
    {
        LOGERROR("Could not allocate poly mesh");
        return false;
    }
    if (!rcBuildPolyMesh(build.ctx_, *build.contourSet_, cfg.maxVertsPerPoly, *build.polyMesh_))
    {
        LOGERROR("Could not triangulate contours");
        return false;
    }

    build.polyMeshDetail_ = rcAllocPolyMeshDetail();
    if (!build.polyMeshDetail_)
    {
        LOGERROR("Could not allocate detail mesh");
        return false;
    }
    if (!rcBuildPolyMeshDetail(build.ctx_, *build.polyMesh_, *build.compactHeightField_, cfg.detailSampleDist,
        cfg.detailSampleMaxError, *build.polyMeshDetail_))
    {
        LOGERROR("Could not build detail mesh");
        return false;
    }

    // Set polygon flags
    /// \todo Allow to define custom flags
    for (int i = 0; i < build.polyMesh_->npolys; ++i)
    {
        if (build.polyMesh_->areas[i] == RC_WALKABLE_AREA)
            build.polyMesh_->flags[i] = 0x1;
    }

    unsigned char* navData = 0;
    int navDataSize = 0;

    dtNavMeshCreateParams params;
    memset(&params, 0, sizeof params);
    params.verts = build.polyMesh_->verts;
    params.vertCount = build.polyMesh_->nverts;
    params.polys = build.polyMesh_->polys;
    params.polyAreas = build.polyMesh_->areas;
    params.polyFlags = build.polyMesh_->flags;
    params.polyCount = build.polyMesh_->npolys;
    params.nvp = build.polyMesh_->nvp;
    params.detailMeshes = build.polyMeshDetail_->meshes;
    params.detailVerts = build.polyMeshDetail_->verts;
    params.detailVertsCount = build.polyMeshDetail_->nverts;
    params.detailTris = build.polyMeshDetail_->tris;
    params.detailTriCount = build.polyMeshDetail_->ntris;
    params.walkableHeight = agentHeight_;
    params.walkableRadius = agentRadius_;
    params.walkableClimb = agentMaxClimb_;
    params.tileX = x;
    params.tileY = z;
    rcVcopy(params.bmin, build.polyMesh_->bmin);
    rcVcopy(params.bmax, build.polyMesh_->bmax);
    params.cs = cfg.cs;
    params.ch = cfg.ch;
    params.buildBvTree = true;

    // Add off-mesh connections if have them
    if (build.offMeshRadii_.Size())
    {
        params.offMeshConCount = build.offMeshRadii_.Size();
        params.offMeshConVerts = &build.offMeshVertices_[0].x_;
        params.offMeshConRad = &build.offMeshRadii_[0];
        params.offMeshConFlags = &build.offMeshFlags_[0];
        params.offMeshConAreas = &build.offMeshAreas_[0];
        params.offMeshConDir = &build.offMeshDir_[0];
    }

    if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
    {
        LOGERROR("Could not build navigation mesh tile data");
        return false;
    }

    if (dtStatusFailed(navMesh_->addTile(navData, navDataSize, DT_TILE_FREE_DATA, 0, 0)))
    {
        LOGERROR("Failed to add navigation mesh tile");
        dtFree(navData);
        return false;
    }

    return true;
}

bool NavigationMesh::InitializeQuery()
{
    if (!navMesh_ || !node_)
        return false;

    if (navMeshQuery_)
        return true;

    navMeshQuery_ = dtAllocNavMeshQuery();
    if (!navMeshQuery_)
    {
        LOGERROR("Could not create navigation mesh query");
        return false;
    }

    if (dtStatusFailed(navMeshQuery_->init(navMesh_, MAX_POLYS)))
    {
        LOGERROR("Could not init navigation mesh query");
        return false;
    }

    return true;
}

void NavigationMesh::ReleaseNavigationMesh()
{
    dtFreeNavMesh(navMesh_);
    navMesh_ = 0;

    dtFreeNavMeshQuery(navMeshQuery_);
    navMeshQuery_ = 0;

    numTilesX_ = 0;
    numTilesZ_ = 0;
    boundingBox_.min_ = boundingBox_.max_ = Vector3::ZERO;
    boundingBox_.defined_ = false;
}

void RegisterNavigationLibrary(Context* context)
{
    Navigable::RegisterObject(context);
    NavigationMesh::RegisterObject(context);
    OffMeshConnection::RegisterObject(context);
}

}
