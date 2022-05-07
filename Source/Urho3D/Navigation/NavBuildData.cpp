// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
