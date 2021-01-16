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

#pragma once

#ifdef URHO3D_NAVIGATION

#include "../Navigation/NavigationMesh.h"
#include "../Navigation/CrowdAgent.h"
#include "../Navigation/CrowdManager.h"

namespace Urho3D
{

// virtual PODVector<unsigned char> NavigationMesh::GetTileData(const IntVector2 &tile) const | File: ../Navigation/NavigationMesh.h
VectorBuffer NavigationMeshGetTileData(const IntVector2& tile, const NavigationMesh* ptr);
// virtual bool NavigationMesh::AddTile(const PODVector< unsigned char > &tileData) | File: ../Navigation/NavigationMesh.h
bool NavigationMeshAddTile(const VectorBuffer& tileData, NavigationMesh* ptr);
// Vector3 NavigationMesh::FindNearestPoint(const Vector3 &point, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr, dtPolyRef *nearestRef=nullptr) | File: ../Navigation/NavigationMesh.h
Vector3 NavigationMeshFindNearestPoint(const Vector3& point, const Vector3& extents, NavigationMesh* ptr);
// Vector3 NavigationMesh::GetRandomPoint(const dtQueryFilter *filter=nullptr, dtPolyRef *randomRef=nullptr) | File: ../Navigation/NavigationMesh.h
Vector3 NavigationMeshGetRandomPoint(NavigationMesh* ptr);
// Vector3 NavigationMesh::GetRandomPointInCircle(const Vector3 &center, float radius, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr, dtPolyRef *randomRef=nullptr) | File: ../Navigation/NavigationMesh.h
Vector3 NavigationMeshGetRandomPointInCircle(const Vector3& center, float radius, const Vector3& extents, NavigationMesh* ptr);
// float NavigationMesh::GetDistanceToWall(const Vector3 &point, float radius, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr, Vector3 *hitPos=nullptr, Vector3 *hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h
float NavigationMeshGetDistanceToWall(const Vector3& point, float radius, const Vector3& extents, NavigationMesh* ptr);
// Vector3 NavigationMesh::Raycast(const Vector3 &start, const Vector3 &end, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr, Vector3 *hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h
Vector3 NavigationMeshRaycast(const Vector3& start, const Vector3& end, const Vector3& extents, NavigationMesh* ptr);
// Vector3 NavigationMesh::MoveAlongSurface(const Vector3 &start, const Vector3 &end, const Vector3 &extents=Vector3::ONE, int maxVisited=3, const dtQueryFilter *filter=nullptr) | File: ../Navigation/NavigationMesh.h
Vector3 NavigationMeshMoveAlongSurface(const Vector3& start, const Vector3& end, const Vector3& extents, int maxVisited, NavigationMesh* ptr);
// void NavigationMesh::FindPath(PODVector< Vector3 > &dest, const Vector3 &start, const Vector3 &end, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr) | File: ../Navigation/NavigationMesh.h
CScriptArray* NavigationMeshFindPath(const Vector3& start, const Vector3& end, const Vector3& extents, NavigationMesh* ptr);

#define REGISTER_MANUAL_PART_NavigationMesh(T, className) \
    /* virtual PODVector<unsigned char> NavigationMesh::GetTileData(const IntVector2 &tile) const | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "VectorBuffer GetTileData(const IntVector2&) const", asFUNCTION(NavigationMeshGetTileData), asCALL_CDECL_OBJLAST); \
    /* virtual bool NavigationMesh::AddTile(const PODVector< unsigned char > &tileData) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "bool AddTile(const VectorBuffer&in) const", asFUNCTION(NavigationMeshAddTile), asCALL_CDECL_OBJLAST); \
    /* Vector3 NavigationMesh::FindNearestPoint(const Vector3 &point, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr, dtPolyRef *nearestRef=nullptr) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "Vector3 FindNearestPoint(const Vector3&in, const Vector3&in extents = Vector3(1.0, 1.0, 1.0))", asFUNCTION(NavigationMeshFindNearestPoint), asCALL_CDECL_OBJLAST); \
    /* Vector3 NavigationMesh::GetRandomPoint(const dtQueryFilter *filter=nullptr, dtPolyRef *randomRef=nullptr) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "Vector3 GetRandomPoint()", asFUNCTION(NavigationMeshGetRandomPoint), asCALL_CDECL_OBJLAST); \
    /* Vector3 NavigationMesh::GetRandomPointInCircle(const Vector3 &center, float radius, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr, dtPolyRef *randomRef=nullptr) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "Vector3 GetRandomPointInCircle(const Vector3&in, float, const Vector3&in extents = Vector3(1.0, 1.0, 1.0))", asFUNCTION(NavigationMeshGetRandomPointInCircle), asCALL_CDECL_OBJLAST); \
    /* float NavigationMesh::GetDistanceToWall(const Vector3 &point, float radius, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr, Vector3 *hitPos=nullptr, Vector3 *hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "float GetDistanceToWall(const Vector3&in, float, const Vector3&in extents = Vector3(1.0, 1.0, 1.0))", asFUNCTION(NavigationMeshGetDistanceToWall), asCALL_CDECL_OBJLAST); \
    /* Vector3 NavigationMesh::Raycast(const Vector3 &start, const Vector3 &end, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr, Vector3 *hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "Vector3 Raycast(const Vector3&in, const Vector3&in, const Vector3&in extents = Vector3(1.0, 1.0, 1.0))", asFUNCTION(NavigationMeshRaycast), asCALL_CDECL_OBJLAST); \
    /* Vector3 NavigationMesh::MoveAlongSurface(const Vector3 &start, const Vector3 &end, const Vector3 &extents=Vector3::ONE, int maxVisited=3, const dtQueryFilter *filter=nullptr) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "Vector3 MoveAlongSurface(const Vector3&in, const Vector3&in, const Vector3&in extents = Vector3(1.0, 1.0, 1.0), int maxVisited = 3)", asFUNCTION(NavigationMeshMoveAlongSurface), asCALL_CDECL_OBJLAST); \
    /* void NavigationMesh::FindPath(PODVector< Vector3 > &dest, const Vector3 &start, const Vector3 &end, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "Array<Vector3>@ FindPath(const Vector3&in, const Vector3&in, const Vector3&in extents = Vector3(1.0, 1.0, 1.0))", asFUNCTION(NavigationMeshFindPath), asCALL_CDECL_OBJLAST);

// ========================================================================================

// Vector3 CrowdManager::GetRandomPoint(int queryFilterType, dtPolyRef *randomRef=nullptr) | File: ../Navigation/CrowdManager.h
Vector3 CrowdManagerGetRandomPoint(int queryFilterType, CrowdManager* crowdManager);
// Vector3 CrowdManager::GetRandomPointInCircle(const Vector3 &center, float radius, int queryFilterType, dtPolyRef *randomRef=nullptr) | File: ../Navigation/CrowdManager.h
Vector3 CrowdManagerRandomPointInCircle(const Vector3& center, float radius, int queryFilterType, CrowdManager* manager);
// Vector3 CrowdManager::FindNearestPoint(const Vector3 &point, int queryFilterType, dtPolyRef *nearestRef=nullptr) | File: ../Navigation/CrowdManager.h
Vector3 CrowdManager_FindNearestPoint(const Vector3& point, int queryFilterType, CrowdManager* ptr);
// float CrowdManager::GetDistanceToWall(const Vector3 &point, float radius, int queryFilterType, Vector3 *hitPos=nullptr, Vector3 *hitNormal=nullptr) | File: ../Navigation/CrowdManager.h
float CrowdManager_GetDistanceToWall(const Vector3& point, float radius, int queryFilterType, CrowdManager* ptr);
// Vector3 CrowdManager::Raycast(const Vector3 &start, const Vector3 &end, int queryFilterType, Vector3 *hitNormal=nullptr) | File: ../Navigation/CrowdManager.h
Vector3 CrowdManager_Raycast(const Vector3& start, const Vector3& end, int queryFilterType, CrowdManager* ptr);

#define REGISTER_MANUAL_PART_CrowdManager(T, className) \
    /* Vector3 CrowdManager::GetRandomPoint(int queryFilterType, dtPolyRef *randomRef=nullptr) | File: ../Navigation/CrowdManager.h */ \
    engine->RegisterObjectMethod(className, "Vector3 GetRandomPoint(int)", asFUNCTION(CrowdManagerGetRandomPoint), asCALL_CDECL_OBJLAST); \
    /* Vector3 CrowdManager::GetRandomPointInCircle(const Vector3 &center, float radius, int queryFilterType, dtPolyRef *randomRef=nullptr) | File: ../Navigation/CrowdManager.h */ \
    engine->RegisterObjectMethod(className, "Vector3 GetRandomPointInCircle(const Vector3&in, float, int)", asFUNCTION(CrowdManagerRandomPointInCircle), asCALL_CDECL_OBJLAST); \
    /* Vector3 CrowdManager::FindNearestPoint(const Vector3 &point, int queryFilterType, dtPolyRef *nearestRef=nullptr) | File: ../Navigation/CrowdManager.h */ \
    engine->RegisterObjectMethod("CrowdManager", "Vector3 FindNearestPoint(const Vector3&in, int)", asFUNCTION(CrowdManager_FindNearestPoint), asCALL_CDECL_OBJLAST); \
    /* float CrowdManager::GetDistanceToWall(const Vector3 &point, float radius, int queryFilterType, Vector3 *hitPos=nullptr, Vector3 *hitNormal=nullptr) | File: ../Navigation/CrowdManager.h */ \
    engine->RegisterObjectMethod("CrowdManager", "float GetDistanceToWall(const Vector3&in, float, int)", asFUNCTION(CrowdManager_GetDistanceToWall), asCALL_CDECL_OBJLAST); \
    /* Vector3 CrowdManager::Raycast(const Vector3 &start, const Vector3 &end, int queryFilterType, Vector3 *hitNormal=nullptr) | File: ../Navigation/CrowdManager.h */ \
    engine->RegisterObjectMethod("CrowdManager", "Vector3 Raycast(const Vector3&in, const Vector3&in, int)", asFUNCTION(CrowdManager_Raycast), asCALL_CDECL_OBJLAST);

}

#endif // def URHO3D_NAVIGATION
