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

#pragma once

#include "ArrayPtr.h"
#include "BoundingBox.h"
#include "Component.h"

class rcContext;
class dtNavMesh;

struct rcHeightfield;
struct rcCompactHeightfield;
struct rcContourSet;
struct rcPolyMesh;
struct rcPolyMeshDetail;

namespace Urho3D
{

class Geometry;

/// Navigation mesh component. Collects the navigation geometry from child nodes with the Navigable component and responds to path queries.
class NavigationMesh : public Component
{
    OBJECT(NavigationMesh);
    
public:
    /// Construct.
    NavigationMesh(Context* context);
    /// Destruct.
    virtual ~NavigationMesh();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Set cell size.
    void SetCellSize(float size);
    /// Set cell height.
    void SetCellHeight(float height);
    /// Set navigation agent height.
    void SetAgentHeight(float height);
    /// Set navigation agent radius.
    void SetAgentRadius(float radius);
    /// Set navigation agent max vertical climb.
    void SetAgentMaxClimb(float maxClimb);
    /// Set navigation agent max slope.
    void SetAgentMaxSlope(float maxSlope);
    /// Set region minimum size.
    void SetRegionMinSize(float size);
    /// Set region merge size.
    void SetRegionMergeSize(float size);
    /// Set edge max length.
    void SetEdgeMaxLength(float length);
    /// Set edge max error.
    void SetEdgeMaxError(float error);
    /// Set detail sampling distance.
    void SetDetailSampleDistance(float distance);
    /// Set detail sampling maximum error.
    void SetDetailSampleMaxError(float error);
    /// Rebuild the navigation data. Return true if successful.
    bool Build();
    
    /// Return cell size.
    float GetCellSize() const { return cellSize_; }
    /// Return cell height.
    float GetCellHeight() const { return cellHeight_; }
    /// Return navigation agent height.
    float GetAgentHeight() const { return agentHeight_; }
    /// Return navigation agent radius.
    float GetAgentRadius() const { return agentRadius_; }
    /// Return navigation agent max vertical climb.
    float GetAgentMaxClimb() const { return agentMaxClimb_; }
    /// Return navigation agent max slope.
    float GetAgentMaxSlope() const { return agentMaxSlope_; }
    /// Return region minimum size.
    float GetRegionMinSize() const { return regionMinSize_; }
    /// Return region merge size.
    float GetRegionMergeSize() const { return regionMergeSize_; }
    /// Return edge max length.
    float GetEdgeMaxLength() const { return edgeMaxLength_; }
    /// Return edge max error.
    float GetEdgeMaxError() const { return edgeMaxError_; }
    /// Return detail sampling distance.
    float GetDetailSampleDistance() const { return detailSampleDistance_; }
    /// Return detail sampling maximum error.
    float GetDetailSampleMaxError() const { return detailSampleMaxError_; }
    /// Return whether has been initialized with valid navigation data.
    bool IsInitialized() const { return navMesh_ != 0; }
    
    /// Set navigation data attribute.
    void SetNavigationDataAttr(const PODVector<unsigned char>& data);
    /// Get navigation data attribute.
    const PODVector<unsigned char>& GetNavigationDataAttr() const { return navigationDataAttr_; }
    
private:
    /// Visit nodes and collect navigable geometry.
    void CollectGeometries(Node* node, Node* baseNode);
    /// Add a geometry to the mesh.
    void AddGeometry(Node* node, Geometry* geometry);
    /// Create Detour navmesh. Return true if successful.
    bool CreateNavMesh(unsigned char* navData, unsigned navDataSize);
    /// Release Recast temporary data.
    void ReleaseBuildData();
    /// Release the Detour navmesh.
    void ReleaseNavMesh();
    
    /// Cell size.
    float cellSize_;
    /// Cell height.
    float cellHeight_;
    /// Navigation agent height.
    float agentHeight_;
    /// Navigation agent radius.
    float agentRadius_;
    /// Navigation agent max vertical climb.
    float agentMaxClimb_;
    /// Navigation agent max slope.
    float agentMaxSlope_;
    /// Region minimum size.
    float regionMinSize_;
    /// Region merge size.
    float regionMergeSize_;
    /// Edge max length.
    float edgeMaxLength_;
    /// Edge max error.
    float edgeMaxError_;
    /// Detail sampling distance.
    float detailSampleDistance_;
    /// Detail sampling maximum error.
    float detailSampleMaxError_;
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
    /// Detour navmesh.
    dtNavMesh* navMesh_;
    
    /// Navigation data attribute. Contains the unmodified Recast data.
    PODVector<unsigned char> navigationDataAttr_;
};

}
