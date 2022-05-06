// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/Vector.h"
#include "../Math/BoundingBox.h"
#include "../Math/Vector3.h"

class rcContext;

struct dtTileCacheContourSet;
struct dtTileCachePolyMesh;
struct dtTileCacheAlloc;
struct rcCompactHeightfield;
struct rcContourSet;
struct rcHeightfield;
struct rcHeightfieldLayerSet;
struct rcPolyMesh;
struct rcPolyMeshDetail;

namespace Urho3D
{

/// Navigation area stub.
struct URHO3D_API NavAreaStub
{
    /// Area bounding box.
    BoundingBox bounds_;
    /// Area ID.
    unsigned char areaID_;
};

/// Navigation build data.
struct URHO3D_API NavBuildData
{
    /// Constructor.
    NavBuildData();
    /// Destructor.
    virtual ~NavBuildData();

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
    /// Pretransformed navigation areas, no correlation to the geometry above.
    PODVector<NavAreaStub> navAreas_;
};

struct SimpleNavBuildData : public NavBuildData
{
    /// Constructor.
    SimpleNavBuildData();
    /// Descturctor.
    ~SimpleNavBuildData() override;

    /// Recast contour set.
    rcContourSet* contourSet_;
    /// Recast poly mesh.
    rcPolyMesh* polyMesh_;
    /// Recast detail poly mesh.
    rcPolyMeshDetail* polyMeshDetail_;
};

/// @nobind
struct DynamicNavBuildData : public NavBuildData
{
    /// Constructor.
    explicit DynamicNavBuildData(dtTileCacheAlloc* allocator);
    /// Destructor.
    ~DynamicNavBuildData() override;

    /// TileCache specific recast contour set.
    dtTileCacheContourSet* contourSet_;
    /// TileCache specific recast poly mesh.
    dtTileCachePolyMesh* polyMesh_;
    /// Recast heightfield layer set.
    rcHeightfieldLayerSet* heightFieldLayers_;
    /// Allocator from DynamicNavigationMesh instance.
    dtTileCacheAlloc* alloc_;
};

}
