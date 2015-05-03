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

#include "../Container/Vector.h"
#include "../Math/BoundingBox.h"
#include "../Math/Vector3.h"

class rcContext;
struct rcHeightfield;
struct rcCompactHeightfield;
struct rcContourSet;
struct rcPolyMesh;
struct rcPolyMeshDetail;

struct rcHeightfieldLayerSet;
struct dtTileCacheContourSet;
struct dtTileCachePolyMesh;
struct dtTileCacheAlloc;

namespace Urho3D
{
    struct URHO3D_API NavAreaStub
    {
        BoundingBox bounds_;
        unsigned char areaID_;
    };

    struct URHO3D_API NavBuildData
    {
        NavBuildData();
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
        /// Recast heightfield
        rcHeightfield* heightField_;
        /// Recast compact heightfield.
        rcCompactHeightfield* compactHeightField_;
        /// Pretransformed navigation areas, no correlation to the geometry above
        PODVector<NavAreaStub> navAreas_;
    };

    struct SimpleNavBuildData : public NavBuildData
    {
        SimpleNavBuildData();
        virtual ~SimpleNavBuildData();

        /// Recast contour set.
        rcContourSet* contourSet_;
        /// Recast poly mesh.
        rcPolyMesh* polyMesh_;
        /// Recast detail poly mesh.
        rcPolyMeshDetail* polyMeshDetail_;
    };

    struct DynamicNavBuildData : public NavBuildData
    {
        DynamicNavBuildData(dtTileCacheAlloc* alloc);
        virtual ~DynamicNavBuildData();

        /// TileCache specific recast contour set
        dtTileCacheContourSet* contourSet_;
        /// TileCache specific recast poly mesh
        dtTileCachePolyMesh* polyMesh_;
        /// Recast heightfield layer set
        rcHeightfieldLayerSet* heightFieldLayers_;
        /// Allocator from DynamicNavigationMesh instance
        dtTileCacheAlloc* alloc_;
    };
}