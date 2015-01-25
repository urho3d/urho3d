//
// Copyright (c) 2008-2014 the Urho3D project.
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

#ifdef URHO3D_NAVIGATION
#include "../Script/APITemplates.h"
#include "../Navigation/Navigable.h"
#include "../Navigation/NavigationMesh.h"
#include "../Navigation/OffMeshConnection.h"

namespace Urho3D
{

void RegisterNavigable(asIScriptEngine* engine)
{
    RegisterComponent<Navigable>(engine, "Navigable");
    engine->RegisterObjectMethod("Navigable", "void set_recursive(bool)", asMETHOD(Navigable, SetRecursive), asCALL_THISCALL);
    engine->RegisterObjectMethod("Navigable", "bool get_recursive() const", asMETHOD(Navigable, IsRecursive), asCALL_THISCALL);
}

static CScriptArray* NavigationMeshFindPath(const Vector3& start, const Vector3& end, const Vector3& extents, NavigationMesh* ptr)
{
    PODVector<Vector3> dest;
    ptr->FindPath(dest, start, end, extents);
    return VectorToArray<Vector3>(dest, "Array<Vector3>");
}

void RegisterNavigationMesh(asIScriptEngine* engine)
{
    RegisterComponent<NavigationMesh>(engine, "NavigationMesh");
    engine->RegisterObjectMethod("NavigationMesh", "bool Build()", asMETHODPR(NavigationMesh, Build, (void), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool Build(const BoundingBox&in)", asMETHODPR(NavigationMesh, Build, (const BoundingBox&), bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "Vector3 FindNearestPoint(const Vector3&in, const Vector3&in extents = Vector3(1.0, 1.0, 1.0))", asMETHOD(NavigationMesh, FindNearestPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "Vector3 MoveAlongSurface(const Vector3&in, const Vector3&in, const Vector3&in extents = Vector3(1.0, 1.0, 1.0), uint = 3)", asMETHOD(NavigationMesh, MoveAlongSurface), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "Array<Vector3>@ FindPath(const Vector3&in, const Vector3&in, const Vector3&in extents = Vector3(1.0, 1.0, 1.0))", asFUNCTION(NavigationMeshFindPath), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("NavigationMesh", "Vector3 GetRandomPoint()", asMETHOD(NavigationMesh, GetRandomPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "Vector3 GetRandomPointInCircle(const Vector3&in, float, const Vector3&in extents = Vector3(1.0, 1.0, 1.0))", asMETHOD(NavigationMesh, GetRandomPointInCircle), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float GetDistanceToWall(const Vector3&in, float, const Vector3&in extents = Vector3(1.0, 1.0, 1.0))", asMETHOD(NavigationMesh, GetDistanceToWall), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "Vector3 Raycast(const Vector3&in, const Vector3&in, const Vector3&in extents = Vector3(1.0, 1.0, 1.0))", asMETHOD(NavigationMesh, Raycast), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void DrawDebugGeometry(bool)", asMETHODPR(NavigationMesh, DrawDebugGeometry, (bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_tileSize(int)", asMETHOD(NavigationMesh, SetTileSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "int get_tileSize() const", asMETHOD(NavigationMesh, GetTileSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_cellSize(float)", asMETHOD(NavigationMesh, SetCellSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_cellSize() const", asMETHOD(NavigationMesh, GetCellSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_cellHeight(float)", asMETHOD(NavigationMesh, SetCellHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_cellHeight() const", asMETHOD(NavigationMesh, GetCellHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentHeight(float)", asMETHOD(NavigationMesh, SetAgentHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentHeight() const", asMETHOD(NavigationMesh, GetAgentHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentRadius(float)", asMETHOD(NavigationMesh, SetAgentRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentRadius() const", asMETHOD(NavigationMesh, GetAgentRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentMaxClimb(float)", asMETHOD(NavigationMesh, SetAgentMaxClimb), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentMaxClimb() const", asMETHOD(NavigationMesh, GetAgentMaxClimb), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_agentMaxSlope(float)", asMETHOD(NavigationMesh, SetAgentMaxSlope), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_agentMaxSlope() const", asMETHOD(NavigationMesh, GetAgentMaxSlope), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_regionMinSize(float)", asMETHOD(NavigationMesh, SetRegionMinSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_regionMinSize() const", asMETHOD(NavigationMesh, GetRegionMinSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_regionMergeSize(float)", asMETHOD(NavigationMesh, SetRegionMergeSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_regionMergeSize() const", asMETHOD(NavigationMesh, GetRegionMergeSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_edgeMaxLength(float)", asMETHOD(NavigationMesh, SetEdgeMaxLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_edgeMaxLength() const", asMETHOD(NavigationMesh, GetEdgeMaxLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_edgeMaxError(float)", asMETHOD(NavigationMesh, SetEdgeMaxError), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_edgeMaxError() const", asMETHOD(NavigationMesh, GetEdgeMaxError), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_detailSampleDistance(float)", asMETHOD(NavigationMesh, SetDetailSampleDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_detailSampleDistance() const", asMETHOD(NavigationMesh, GetDetailSampleDistance), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_detailSampleMaxError(float)", asMETHOD(NavigationMesh, SetDetailSampleMaxError), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "float get_detailSampleMaxError() const", asMETHOD(NavigationMesh, GetDetailSampleMaxError), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "void set_padding(const Vector3&in)", asMETHOD(NavigationMesh, SetPadding), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const Vector3& get_padding() const", asMETHOD(NavigationMesh, GetPadding), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "bool get_initialized() const", asMETHOD(NavigationMesh, IsInitialized), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "const BoundingBox& get_boundingBox() const", asMETHOD(NavigationMesh, GetBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "BoundingBox get_worldBoundingBox() const", asMETHOD(NavigationMesh, GetWorldBoundingBox), asCALL_THISCALL);
    engine->RegisterObjectMethod("NavigationMesh", "IntVector2 get_numTiles() const", asMETHOD(NavigationMesh, GetNumTiles), asCALL_THISCALL);
}

void RegisterOffMeshConnection(asIScriptEngine* engine)
{
    RegisterComponent<OffMeshConnection>(engine, "OffMeshConnection");
    engine->RegisterObjectMethod("OffMeshConnection", "void set_endPoint(Node@+)", asMETHOD(OffMeshConnection, SetEndPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "Node@+ get_endPoint() const", asMETHOD(OffMeshConnection, GetEndPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_radius(float)", asMETHOD(OffMeshConnection, SetRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "float get_radius() const", asMETHOD(OffMeshConnection, GetRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "void set_bidirectional(bool)", asMETHOD(OffMeshConnection, SetBidirectional), asCALL_THISCALL);
    engine->RegisterObjectMethod("OffMeshConnection", "bool get_bidirectional() const", asMETHOD(OffMeshConnection, IsBidirectional), asCALL_THISCALL);
}

void RegisterNavigationAPI(asIScriptEngine* engine)
{
    RegisterNavigable(engine);
    RegisterNavigationMesh(engine);
    RegisterOffMeshConnection(engine);
}

}
#endif
