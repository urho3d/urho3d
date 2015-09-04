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

#include <DetourTileCache/DetourTileCacheBuilder.h>
#include <Recast/Recast.h>

namespace Urho3D
{

NavBuildData::NavBuildData() :
    ctx_(new rcContext(true)),
    heightField_(0),
    compactHeightField_(0)
{
}

NavBuildData::~NavBuildData()
{
    delete(ctx_);
    ctx_ = 0;
    rcFreeHeightField(heightField_);
    heightField_ = 0;
    rcFreeCompactHeightfield(compactHeightField_);
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
    contourSet_ = 0;
    rcFreePolyMesh(polyMesh_);
    polyMesh_ = 0;
    rcFreePolyMeshDetail(polyMeshDetail_);
    polyMeshDetail_ = 0;
}

DynamicNavBuildData::DynamicNavBuildData(dtTileCacheAlloc* allocator) :
    NavBuildData(),
    contourSet_(0),
    polyMesh_(0),
    heightFieldLayers_(0),
    alloc_(allocator)
{
    assert(allocator);
}

DynamicNavBuildData::~DynamicNavBuildData()
{
    dtFreeTileCacheContourSet(alloc_, contourSet_);
    contourSet_ = 0;
    dtFreeTileCachePolyMesh(alloc_, polyMesh_);
    polyMesh_ = 0;
    rcFreeHeightfieldLayerSet(heightFieldLayers_);
    heightFieldLayers_ = 0;
}

}
