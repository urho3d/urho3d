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

#include "../Navigation/NavBuildData.h"

#include <Recast/Recast.h>
#include <Detour/DetourNavMesh.h>
#include <Detour/DetourNavMeshBuilder.h>
#include <Detour/DetourNavMeshQuery.h>
#include <DetourTileCache/DetourTileCache.h>
#include <DetourTileCache/DetourTileCacheBuilder.h>

namespace Urho3D
{

NavBuildData::NavBuildData() :
    ctx_(0),
    heightField_(0),
    compactHeightField_(0)
{
    ctx_ = new rcContext(true);
}

NavBuildData::~NavBuildData()
{
    if (ctx_)
        delete(ctx_);
    rcFreeHeightField(heightField_);
    rcFreeCompactHeightfield(compactHeightField_);

    ctx_ = 0;
    heightField_ = 0;
    compactHeightField_ = 0;
}

SimpleNavBuildData::SimpleNavBuildData() :
    NavBuildData(),
    contourSet_(0),
    polyMesh_(0),
    polyMeshDetail_(0)
{
}

SimpleNavBuildData::~SimpleNavBuildData()
{
    rcFreeContourSet(contourSet_);
    rcFreePolyMesh(polyMesh_);
    rcFreePolyMeshDetail(polyMeshDetail_);

    contourSet_ = 0;
    polyMesh_ = 0;
    polyMeshDetail_ = 0;
}

DynamicNavBuildData::DynamicNavBuildData(dtTileCacheAlloc* allocator) :
    contourSet_(0),
    heightFieldLayers_(0),
    polyMesh_(0),
    alloc_(allocator)
{
}

DynamicNavBuildData::~DynamicNavBuildData()
{
    if (contourSet_)
        dtFreeTileCacheContourSet(alloc_, contourSet_);
    if (polyMesh_)
        dtFreeTileCachePolyMesh(alloc_, polyMesh_);
    if (heightFieldLayers_)
        rcFreeHeightfieldLayerSet(heightFieldLayers_);

    contourSet_ = 0;
    polyMesh_ = 0;
    heightFieldLayers_ = 0;
}

}
