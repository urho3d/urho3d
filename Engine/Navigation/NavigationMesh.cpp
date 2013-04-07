//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Precompiled.h"
#include "CollisionShape.h"
#include "Context.h"
#include "DebugRenderer.h"
#include "Drawable.h"
#include "Geometry.h"
#include "Log.h"
#include "Navigable.h"
#include "NavigationMesh.h"
#include "Profiler.h"
#include "Scene.h"
#include "StaticModel.h"
#include "TerrainPatch.h"

#include <DetourNavMesh.h>
#include <DetourNavMeshBuilder.h>
#include <Recast.h>

#include "DebugNew.h"

namespace Urho3D
{

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

/// Temporary data for building the Recast navigation mesh.
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
    
    /// World-space bounding box of the navigation mesh.
    BoundingBox worldBoundingBox_;
    /// Build phase vertices.
    PODVector<Vector3> vertices_;
    /// Build phase triangle indices.
    PODVector<int> indices_;
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

OBJECTTYPESTATIC(NavigationMesh);

NavigationMesh::NavigationMesh(Context* context) :
    Component(context),
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
    navMesh_(0)
{
}

NavigationMesh::~NavigationMesh()
{
    ReleaseNavMesh();
}

void NavigationMesh::RegisterObject(Context* context)
{
    context->RegisterFactory<NavigationMesh>();
    
    ACCESSOR_ATTRIBUTE(NavigationMesh, VAR_FLOAT, "Cell Size", GetCellSize, SetCellSize, float, DEFAULT_CELL_SIZE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(NavigationMesh, VAR_FLOAT, "Cell Height", GetCellHeight, SetCellHeight, float, DEFAULT_CELL_HEIGHT, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(NavigationMesh, VAR_FLOAT, "Agent Height", GetAgentHeight, SetAgentHeight, float, DEFAULT_AGENT_HEIGHT, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(NavigationMesh, VAR_FLOAT, "Agent Radius", GetAgentRadius, SetAgentRadius, float, DEFAULT_AGENT_RADIUS, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(NavigationMesh, VAR_FLOAT, "Agent Max Climb", GetAgentMaxClimb, SetAgentMaxClimb, float, DEFAULT_AGENT_MAX_CLIMB, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(NavigationMesh, VAR_FLOAT, "Agent Max Slope", GetAgentMaxSlope, SetAgentMaxSlope, float, DEFAULT_AGENT_MAX_SLOPE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(NavigationMesh, VAR_FLOAT, "Region Min Size", GetRegionMinSize, SetRegionMinSize, float, DEFAULT_REGION_MIN_SIZE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(NavigationMesh, VAR_FLOAT, "Region Merge Size", GetRegionMergeSize, SetRegionMergeSize, float, DEFAULT_REGION_MERGE_SIZE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(NavigationMesh, VAR_FLOAT, "Edge Max Length", GetEdgeMaxLength, SetEdgeMaxLength, float, DEFAULT_EDGE_MAX_LENGTH, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(NavigationMesh, VAR_FLOAT, "Edge Max Error", GetEdgeMaxError, SetEdgeMaxError, float, DEFAULT_EDGE_MAX_ERROR, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(NavigationMesh, VAR_FLOAT, "Detail Sample Distance", GetDetailSampleDistance, SetDetailSampleDistance, float, DEFAULT_DETAIL_SAMPLE_DISTANCE, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(NavigationMesh, VAR_FLOAT, "Detail Sample Max Error", GetDetailSampleMaxError, SetDetailSampleMaxError, float, DEFAULT_DETAIL_SAMPLE_MAX_ERROR, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(NavigationMesh, VAR_BUFFER, "Navigation Data", GetNavigationDataAttr, SetNavigationDataAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_FILE | AM_NOEDIT);
}

void NavigationMesh::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (!navMesh_)
        return;
    
    const dtNavMesh* navMesh = navMesh_;
    const dtMeshTile* tile = navMesh->getTile(0);
    if (!tile)
        return;
    
    for (int i = 0; i < tile->header->polyCount; ++i)
    {
        dtPoly* poly = tile->polys + i;
        for (unsigned j = 0; j < poly->vertCount; ++j)
        {
            debug->AddLine(
                *reinterpret_cast<const Vector3*>(&tile->verts[poly->verts[j] * 3]),
                *reinterpret_cast<const Vector3*>(&tile->verts[poly->verts[(j + 1) % poly->vertCount] * 3]),
                Color::YELLOW,
                depthTest
            );
        }
    }
}

void NavigationMesh::SetCellSize(float size)
{
    cellSize_ = Max(size, M_EPSILON);
}

void NavigationMesh::SetCellHeight(float height)
{
    cellHeight_ = Max(height, M_EPSILON);
}

void NavigationMesh::SetAgentHeight(float height)
{
    agentHeight_ = Max(height, M_EPSILON);
}

void NavigationMesh::SetAgentRadius(float radius)
{
    agentRadius_ = Max(radius, M_EPSILON);
}

void NavigationMesh::SetAgentMaxClimb(float maxClimb)
{
    agentMaxClimb_ = Max(maxClimb, M_EPSILON);
}

void NavigationMesh::SetAgentMaxSlope(float maxSlope)
{
    agentMaxSlope_ = Max(maxSlope, 0.0f);
}

void NavigationMesh::SetRegionMinSize(float size)
{
    regionMinSize_ = Max(size, M_EPSILON);
}

void NavigationMesh::SetRegionMergeSize(float size)
{
    regionMergeSize_ = Max(size, M_EPSILON);
}

void NavigationMesh::SetEdgeMaxLength(float length)
{
    edgeMaxLength_ = Max(length, M_EPSILON);
}

void NavigationMesh::SetEdgeMaxError(float error)
{
    edgeMaxError_ = Max(error, M_EPSILON);
}

void NavigationMesh::SetDetailSampleDistance(float distance)
{
    detailSampleDistance_ = Max(distance, M_EPSILON);
}

void NavigationMesh::SetDetailSampleMaxError(float error)
{
    detailSampleMaxError_ = Max(error, M_EPSILON);
}

bool NavigationMesh::Build()
{
    PROFILE(BuildNavigationMesh);
    
    ReleaseNavMesh();
    
    if (!node_)
        return false;
    
    NavigationBuildData build;
    
    {
        PROFILE(CollectNavigationGeometry);
        // Get Navigable components from child nodes, not from whole scene. This makes it theoretically possible to partition
        // the scene into several navigation meshes
        PODVector<Navigable*> navigables;
        node_->GetComponents<Navigable>(navigables, true);
        
        for (unsigned i = 0; i < navigables.Size(); ++i)
            CollectGeometries(build, navigables[i]->GetNode(), navigables[i]->GetNode());
        
        LOGDEBUG("Navigation mesh has " + String(build.vertices_.Size()) + " vertices and " + String(build.indices_.Size()) +
            " indices");
    }
    
    if (!build.vertices_.Size() || !build.indices_.Size())
        return true; // Nothing to do
    
    {
        PROFILE(ProcessNavigationGeometry);
        
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
        cfg.detailSampleDist = detailSampleDistance_ < 0.9f ? 0.0f : cellSize_ * detailSampleDistance_;
        cfg.detailSampleMaxError = cellHeight_ * detailSampleMaxError_;
        
        rcVcopy(cfg.bmin, &build.worldBoundingBox_.min_.x_);
        rcVcopy(cfg.bmax, &build.worldBoundingBox_.max_.x_);
        rcCalcGridSize(cfg.bmin, cfg.bmax, cfg.cs, &cfg.width, &cfg.height);
        
        build.heightField_ = rcAllocHeightfield();
        if (!build.heightField_)
        {
            LOGERROR("Could not allocate heightfield");
            return false;
        }
        
        if (!rcCreateHeightfield(build.ctx_, *build.heightField_, cfg.width, cfg.height, cfg.bmin, cfg.bmax, cfg.cs, cfg.ch))
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
        if (!rcBuildRegions(build.ctx_, *build.compactHeightField_, 0, cfg.minRegionArea, cfg.mergeRegionArea))
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
        rcVcopy(params.bmin, build.polyMesh_->bmin);
        rcVcopy(params.bmax, build.polyMesh_->bmax);
        params.cs = cfg.cs;
        params.ch = cfg.ch;
        params.buildBvTree = true;
        
        if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
        {
            LOGERROR("Could not build Detour navmesh");
            return false;
        }
        
        // Before creating the navmesh (which modifies the data) copy the data for serialization
        navigationDataAttr_.Resize(navDataSize);
        memcpy(&navigationDataAttr_[0], navData, navDataSize);
        
        return CreateNavMesh(navData, navDataSize);
    }
}

void NavigationMesh::SetNavigationDataAttr(const PODVector<unsigned char>& data)
{
    navigationDataAttr_ = data;
    if (!data.Size())
        return;
    
    /// \todo Would be preferable not to have to make a copy of the data, however Recast modifies it when creating the navmesh
    unsigned char* navData = (unsigned char*)dtAlloc(data.Size(), DT_ALLOC_PERM);
    memcpy(navData, &navigationDataAttr_[0], navigationDataAttr_.Size());
    
    CreateNavMesh(navData, data.Size());
}

void NavigationMesh::CollectGeometries(NavigationBuildData& build, Node* node, Node* baseNode)
{
    // If find a navigable from a child node that's not the current base node, abort so we're not going to add the geometry twice
    if (node != baseNode && node->HasComponent<Navigable>())
        return;
    
    /// \todo Prefer physics geometry if available
    PODVector<Drawable*> drawables;
    node->GetDerivedComponents<Drawable>(drawables);
    for (unsigned i = 0; i < drawables.Size(); ++i)
    {
        /// \todo Evaluate whether should handle other types. Now StaticModel & TerrainPatch are supported, others skipped
        Drawable* drawable = drawables[i];
        if (!drawable->IsEnabledEffective())
            continue;
        
        unsigned numGeometries = drawable->GetBatches().Size();
        unsigned lodLevel;
        if (drawable->GetType() == StaticModel::GetTypeStatic())
            lodLevel = static_cast<StaticModel*>(drawable)->GetOcclusionLodLevel();
        else if (drawable->GetType() == TerrainPatch::GetTypeStatic())
            lodLevel = 0;
        else
            continue;
        
        for (unsigned j = 0; j < numGeometries; ++j)
            AddGeometry(build, node, drawable->GetLodGeometry(j, lodLevel));
    }
    
    const Vector<SharedPtr<Node> >& children = node->GetChildren();
    for(unsigned i = 0; i < children.Size(); ++i)
        CollectGeometries(build, children[i], baseNode);
}

void NavigationMesh::AddGeometry(NavigationBuildData& build, Node* node, Geometry* geometry)
{
    const unsigned char* vertexData;
    const unsigned char* indexData;
    unsigned vertexSize;
    unsigned indexSize;
    unsigned elementMask;
    
    geometry->GetRawData(vertexData, vertexSize, indexData, indexSize, elementMask);
    if (!vertexData || !indexData || (elementMask & MASK_POSITION) == 0)
    {
        LOGERROR("Could not use geometry from node " + node->GetName() + ": vertex or index raw data null or positions missing");
        return;
    }
    
    unsigned srcIndexStart = geometry->GetIndexStart();
    unsigned srcIndexCount = geometry->GetIndexCount();
    unsigned srcVertexStart = geometry->GetVertexStart();
    unsigned srcVertexCount = geometry->GetVertexCount();
    
    if (!srcIndexCount)
    {
        LOGERROR("Could not use geometry from node " + node->GetName() + ": no indices");
        return;
    }
    
    unsigned destVertexStart = build.vertices_.Size();
    
    // Copy draw range vertices transformed into world space
    Matrix3x4 transform = node->GetWorldTransform();
    
    for (unsigned i = srcVertexStart; i < srcVertexStart + srcVertexCount; ++i)
    {
        Vector3 vertex = transform * *((const Vector3*)(&vertexData[i * vertexSize]));
        build.worldBoundingBox_.Merge(vertex);
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

bool NavigationMesh::CreateNavMesh(unsigned char* navData, unsigned navDataSize)
{
    ReleaseNavMesh();
    
    navMesh_ = dtAllocNavMesh();
    if (!navMesh_)
    {
        LOGERROR("Could not create Detour navmesh");
        dtFree(navData);
        return false;
    }
    
    dtStatus status;
    
    status = navMesh_->init(navData, navDataSize, DT_TILE_FREE_DATA);
    if (dtStatusFailed(status))
    {
        LOGERROR("Could not init Detour navmesh");
        ReleaseNavMesh();
        dtFree(navData);
        return false;
    }
    
    LOGDEBUG("Created Detour navmesh, data size " + String(navDataSize) + " bytes");
    return true;
}

void NavigationMesh::ReleaseNavMesh()
{
    dtFreeNavMesh(navMesh_);
    navMesh_ = 0;
}

}
