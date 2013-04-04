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
#include "Drawable.h"
#include "Geometry.h"
#include "Log.h"
#include "Navigable.h"
#include "NavigationMesh.h"
#include "Scene.h"
#include "StaticModel.h"
#include "TerrainPatch.h"

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
    detailSampleMaxError_(DEFAULT_DETAIL_SAMPLE_MAX_ERROR)
{
}

NavigationMesh::~NavigationMesh()
{
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
    worldBoundingBox_.defined_ = false;
    vertices_.Clear();
    indices_.Clear();
    
    Scene* scene = GetScene();
    if (!scene)
        return false;
    
    PODVector<Navigable*> navigables;
    scene->GetComponents<Navigable>(navigables, true);
    
    for (unsigned i = 0; i < navigables.Size(); ++i)
        CollectGeometries(navigables[i]->GetNode(), navigables[i]->GetNode(), navigables[i]->GetFlags());
    
    LOGINFO("Navigation mesh has " + String(vertices_.Size()) + " vertices and " + String(indices_.Size()) + " indices");
    return true;
}

void NavigationMesh::CollectGeometries(Node* node, Node* baseNode, unsigned flags)
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
        unsigned numGeometries = drawable->GetBatches().Size();
        unsigned lodLevel;
        if (drawable->GetType() == StaticModel::GetTypeStatic())
            lodLevel = static_cast<StaticModel*>(drawable)->GetOcclusionLodLevel();
        else if (drawable->GetType() == TerrainPatch::GetTypeStatic())
            lodLevel = 0;
        else
            continue;
        
        for (unsigned j = 0; j < numGeometries; ++j)
            AddGeometry(node, drawable->GetLodGeometry(j, lodLevel));
    }
    
    const Vector<SharedPtr<Node> >& children = node->GetChildren();
    for(unsigned i = 0; i < children.Size(); ++i)
        CollectGeometries(children[i], baseNode, flags);
}

void NavigationMesh::AddGeometry(Node* node, Geometry* geometry)
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
    
    unsigned destVertexStart = vertices_.Size();
    
    // Copy needed vertices transformed into world space
    Matrix3x4 transform = node->GetWorldTransform();
    
    for (unsigned i = srcVertexStart; i < srcVertexStart + srcVertexCount; ++i)
    {
        Vector3 vertex = transform * *((const Vector3*)(&vertexData[i * vertexSize]));
        worldBoundingBox_.Merge(vertex);
        vertices_.Push(vertex);
    }
    
    // Copy remapped indices
    if (indexSize == sizeof(unsigned))
    {
        const unsigned short* indices = ((const unsigned short*)indexData) + srcIndexStart;
        const unsigned short* indicesEnd = indices + srcIndexCount;
        
        while (indices < indicesEnd)
        {
            indices_.Push(*indices - srcVertexStart + destVertexStart);
            ++indices;
        }
    }
    else
    {
        const unsigned* indices = ((const unsigned*)indexData) + srcIndexStart;
        const unsigned* indicesEnd = indices + srcIndexCount;
        
        while (indices < indicesEnd)
        {
            indices_.Push(*indices - srcVertexStart + destVertexStart);
            ++indices;
        }
    }
}

}
