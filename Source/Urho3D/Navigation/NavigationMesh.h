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

#include "../Container/ArrayPtr.h"
#include "../Container/HashSet.h"
#include "../Math/BoundingBox.h"
#include "../Math/Matrix3x4.h"
#include "../Scene/Component.h"

#ifdef DT_POLYREF64
typedef uint64_t dtPolyRef;
#else
typedef unsigned int dtPolyRef;
#endif

class dtNavMesh;
class dtNavMeshQuery;
class dtQueryFilter;

namespace Urho3D
{

enum NavmeshPartitionType
{
    NAVMESH_PARTITION_WATERSHED = 0,
    NAVMESH_PARTITION_MONOTONE
};

class Geometry;

struct FindPathData;
struct NavBuildData;

/// Description of a navigation mesh geometry component, with transform and bounds information.
struct NavigationGeometryInfo
{
    /// Component.
    Component* component_;
    /// Geometry LOD level if applicable.
    unsigned lodLevel_;
    /// Transform relative to the navigation mesh root node.
    Matrix3x4 transform_;
    /// Bounding box relative to the navigation mesh root node.
    BoundingBox boundingBox_;
};

/// Navigation mesh component. Collects the navigation geometry from child nodes with the Navigable component and responds to path queries.
class URHO3D_API NavigationMesh : public Component
{
    URHO3D_OBJECT(NavigationMesh, Component);

    friend class CrowdManager;

public:
    /// Construct.
    NavigationMesh(Context* context);
    /// Destruct.
    virtual ~NavigationMesh();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Visualize the component as debug geometry.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

    /// Set tile size.
    void SetTileSize(int size);
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
    /// Set padding of the navigation mesh bounding box. Having enough padding allows to add geometry on the extremities of the navigation mesh when doing partial rebuilds.
    void SetPadding(const Vector3& padding);
    /// Set the cost of an area.
    void SetAreaCost(unsigned areaID, float cost);
    /// Rebuild the navigation mesh. Return true if successful.
    virtual bool Build();
    /// Rebuild part of the navigation mesh contained by the world-space bounding box. Return true if successful.
    virtual bool Build(const BoundingBox& boundingBox);
    /// Find the nearest point on the navigation mesh to a given point. Extents specifies how far out from the specified point to check along each axis.
    Vector3 FindNearestPoint
        (const Vector3& point, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = 0, dtPolyRef* nearestRef = 0);
    /// Try to move along the surface from one point to another.
    Vector3 MoveAlongSurface(const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, int maxVisited = 3,
        const dtQueryFilter* filter = 0);
    /// Find a path between world space points. Return non-empty list of points if successful. Extents specifies how far off the navigation mesh the points can be.
    void FindPath(PODVector<Vector3>& dest, const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE,
        const dtQueryFilter* filter = 0);
    /// Return a random point on the navigation mesh.
    Vector3 GetRandomPoint(const dtQueryFilter* filter = 0, dtPolyRef* randomRef = 0);
    /// Return a random point on the navigation mesh within a circle. The circle radius is only a guideline and in practice the returned point may be further away.
    Vector3 GetRandomPointInCircle
        (const Vector3& center, float radius, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = 0,
            dtPolyRef* randomRef = 0);
    /// Return distance to wall from a point. Maximum search radius must be specified.
    float GetDistanceToWall
        (const Vector3& point, float radius, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = 0,
            Vector3* hitPos = 0, Vector3* hitNormal = 0);
    /// Perform a walkability raycast on the navigation mesh between start and end and return the point where a wall was hit, or the end point if no walls.
    Vector3 Raycast
        (const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = 0,
            Vector3* hitNormal = 0);
    /// Add debug geometry to the debug renderer.
    void DrawDebugGeometry(bool depthTest);

    /// Return the given name of this navigation mesh.
    String GetMeshName() const { return meshName_; }

    /// Set the name of this navigation mesh.
    void SetMeshName(const String& newName);

    /// Return tile size.
    int GetTileSize() const { return tileSize_; }

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

    /// Return navigation mesh bounding box padding.
    const Vector3& GetPadding() const { return padding_; }

    /// Get the current cost of an area
    float GetAreaCost(unsigned areaID) const;

    /// Return whether has been initialized with valid navigation data.
    bool IsInitialized() const { return navMesh_ != 0; }

    /// Return local space bounding box of the navigation mesh.
    const BoundingBox& GetBoundingBox() const { return boundingBox_; }

    /// Return world space bounding box of the navigation mesh.
    BoundingBox GetWorldBoundingBox() const;

    /// Return number of tiles.
    IntVector2 GetNumTiles() const { return IntVector2(numTilesX_, numTilesZ_); }

    /// Set the partition type used for polygon generation.
    void SetPartitionType(NavmeshPartitionType aType);

    /// Return Partition Type.
    NavmeshPartitionType GetPartitionType() const { return partitionType_; }

    /// Set navigation data attribute.
    virtual void SetNavigationDataAttr(const PODVector<unsigned char>& value);
    /// Return navigation data attribute.
    virtual PODVector<unsigned char> GetNavigationDataAttr() const;

    /// Draw debug geometry for OffMeshConnection components.
    void SetDrawOffMeshConnections(bool enable) { drawOffMeshConnections_ = enable; }

    /// Return whether to draw OffMeshConnection components.
    bool GetDrawOffMeshConnections() const { return drawOffMeshConnections_; }

    /// Draw debug geometry for NavArea components.
    void SetDrawNavAreas(bool enable) { drawNavAreas_ = enable; }

    /// Return whether to draw NavArea components.
    bool GetDrawNavAreas() const { return drawNavAreas_; }

protected:
    /// Collect geometry from under Navigable components.
    void CollectGeometries(Vector<NavigationGeometryInfo>& geometryList);
    /// Visit nodes and collect navigable geometry.
    void
        CollectGeometries(Vector<NavigationGeometryInfo>& geometryList, Node* node, HashSet<Node*>& processedNodes, bool recursive);
    /// Get geometry data within a bounding box.
    void GetTileGeometry(NavBuildData* build, Vector<NavigationGeometryInfo>& geometryList, BoundingBox& box);
    /// Add a triangle mesh to the geometry data.
    void AddTriMeshGeometry(NavBuildData* build, Geometry* geometry, const Matrix3x4& transform);
    /// Build one tile of the navigation mesh. Return true if successful.
    virtual bool BuildTile(Vector<NavigationGeometryInfo>& geometryList, int x, int z);
    /// Ensure that the navigation mesh query is initialized. Return true if successful.
    bool InitializeQuery();
    /// Release the navigation mesh and the query.
    virtual void ReleaseNavigationMesh();

    /// Identifying name for this navigation mesh.
    String meshName_;
    /// Detour navigation mesh.
    dtNavMesh* navMesh_;
    /// Detour navigation mesh query.
    dtNavMeshQuery* navMeshQuery_;
    /// Detour navigation mesh query filter.
    dtQueryFilter* queryFilter_;
    /// Temporary data for finding a path.
    FindPathData* pathData_;
    /// Tile size.
    int tileSize_;
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
    /// Bounding box padding.
    Vector3 padding_;
    /// Number of tiles in X direction.
    int numTilesX_;
    /// Number of tiles in Z direction.
    int numTilesZ_;
    /// Whole navigation mesh bounding box.
    BoundingBox boundingBox_;

    /// Type of the heightfield partitioning.
    NavmeshPartitionType partitionType_;
    /// Keep internal build resources for debug draw modes.
    bool keepInterResults_;

    /// Debug draw OffMeshConnection components.
    bool drawOffMeshConnections_;
    /// Debug draw NavArea components.
    bool drawNavAreas_;
};

/// Register Navigation library objects.
void URHO3D_API RegisterNavigationLibrary(Context* context);

}
