//
// Copyright (c) 2008-2020 the Urho3D project.
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
    heightField_(nullptr),
    compactHeightField_(nullptr)
{
}

NavBuildData::~NavBuildData()
{
    delete(ctx_);
    ctx_ = nullptr;
    rcFreeHeightField(heightField_);
    heightField_ = nullptr;
    rcFreeCompactHeightfield(compactHeightField_);
    compactHeightField_ = nullptr;
}

SimpleNavBuildData::SimpleNavBuildData() :
    NavBuildData(),
    contourSet_(nullptr),
    polyMesh_(nullptr),
    polyMeshDetail_(nullptr)
{
}

SimpleNavBuildData::~SimpleNavBuildData()
{
    rcFreeContourSet(contourSet_);
    contourSet_ = nullptr;
    rcFreePolyMesh(polyMesh_);
    polyMesh_ = nullptr;
    rcFreePolyMeshDetail(polyMeshDetail_);
    polyMeshDetail_ = nullptr;
}

DynamicNavBuildData::DynamicNavBuildData(dtTileCacheAlloc* allocator) :
    NavBuildData(),
    contourSet_(nullptr),
    polyMesh_(nullptr),
    heightFieldLayers_(nullptr),
    alloc_(allocator)
{
    assert(allocator);
}

DynamicNavBuildData::~DynamicNavBuildData()
{
    dtFreeTileCacheContourSet(alloc_, contourSet_);
    contourSet_ = nullptr;
    dtFreeTileCachePolyMesh(alloc_, polyMesh_);
    polyMesh_ = nullptr;
    rcFreeHeightfieldLayerSet(heightFieldLayers_);
    heightFieldLayers_ = nullptr;
}

}
