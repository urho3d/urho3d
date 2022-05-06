// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#ifdef URHO3D_NAVIGATION

#include "../Navigation/CrowdAgent.h"
#include "../Navigation/CrowdManager.h"
#include "../Navigation/DynamicNavigationMesh.h"
#include "../Navigation/NavigationMesh.h"

namespace Urho3D
{

// virtual PODVector<unsigned char> NavigationMesh::GetTileData(const IntVector2& tile) const | File: ../Navigation/NavigationMesh.h
template <class T> VectorBuffer NavigationMesh_GetTileData(const IntVector2& tile, const T* ptr)
{
    VectorBuffer buffer;
    buffer.SetData(ptr->GetTileData(tile));
    return buffer;
}

// virtual bool NavigationMesh::AddTile(const PODVector<unsigned char>& tileData) | File: ../Navigation/NavigationMesh.h
template <class T> bool NavigationMesh_AddTile(const VectorBuffer& tileData, T* ptr)
{
    return ptr->AddTile(tileData.GetBuffer());
}

// Vector3 NavigationMesh::FindNearestPoint(const Vector3& point, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr, dtPolyRef* nearestRef = nullptr) | File: ../Navigation/NavigationMesh.h
template <class T> Vector3 NavigationMesh_FindNearestPoint(const Vector3& point, const Vector3& extents, T* ptr)
{
    return ptr->FindNearestPoint(point, extents);
}

// Vector3 NavigationMesh::GetRandomPoint(const dtQueryFilter* filter = nullptr, dtPolyRef* randomRef = nullptr) | File: ../Navigation/NavigationMesh.h
template <class T> Vector3 NavigationMesh_GetRandomPoint(T* ptr)
{
    return ptr->GetRandomPoint();
}

// Vector3 NavigationMesh::GetRandomPointInCircle(const Vector3& center, float radius, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr, dtPolyRef* randomRef = nullptr) | File: ../Navigation/NavigationMesh.h
template <class T> Vector3 NavigationMesh_GetRandomPointInCircle(const Vector3& center, float radius, const Vector3& extents, T* ptr)
{
    return ptr->GetRandomPointInCircle(center, radius, extents);
}

// float NavigationMesh::GetDistanceToWall(const Vector3& point, float radius, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr, Vector3* hitPos = nullptr, Vector3* hitNormal = nullptr) | File: ../Navigation/NavigationMesh.h
template <class T> float NavigationMesh_GetDistanceToWall(const Vector3& point, float radius, const Vector3& extents, T* ptr)
{
    return ptr->GetDistanceToWall(point, radius, extents);
}

// Vector3 NavigationMesh::Raycast(const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr, Vector3* hitNormal = nullptr) | File: ../Navigation/NavigationMesh.h
template <class T> Vector3 NavigationMesh_Raycast(const Vector3& start, const Vector3& end, const Vector3& extents, T* ptr)
{
    return ptr->Raycast(start, end, extents);
}

// Vector3 NavigationMesh::MoveAlongSurface(const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, int maxVisited = 3, const dtQueryFilter* filter = nullptr)  | File: ../Navigation/NavigationMesh.h
template <class T> Vector3 NavigationMesh_MoveAlongSurface(const Vector3& start, const Vector3& end, const Vector3& extents, int maxVisited, T* ptr)
{
    return ptr->MoveAlongSurface(start, end, extents, maxVisited);
}

// void NavigationMesh::FindPath(PODVector<Vector3>& dest, const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr) | File: ../Navigation/NavigationMesh.h
template <class T> CScriptArray* NavigationMesh_FindPath(const Vector3& start, const Vector3& end, const Vector3& extents, T* ptr)
{
    PODVector<Vector3> dest;
    ptr->FindPath(dest, start, end, extents);
    return VectorToArray<Vector3>(dest, "Array<Vector3>");
}

#define REGISTER_MEMBERS_MANUAL_PART_NavigationMesh() \
    /* virtual PODVector<unsigned char> NavigationMesh::GetTileData(const IntVector2& tile) const | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "VectorBuffer GetTileData(const IntVector2&) const", AS_FUNCTION_OBJLAST(NavigationMesh_GetTileData<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* virtual bool NavigationMesh::AddTile(const PODVector<unsigned char>& tileData) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "bool AddTile(const VectorBuffer&in) const", AS_FUNCTION_OBJLAST(NavigationMesh_AddTile<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Vector3 NavigationMesh::FindNearestPoint(const Vector3& point, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr, dtPolyRef* nearestRef = nullptr) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "Vector3 FindNearestPoint(const Vector3&in, const Vector3&in = Vector3::ONE)", AS_FUNCTION_OBJLAST(NavigationMesh_FindNearestPoint<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Vector3 NavigationMesh::GetRandomPoint(const dtQueryFilter* filter = nullptr, dtPolyRef* randomRef = nullptr) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "Vector3 GetRandomPoint()", AS_FUNCTION_OBJLAST(NavigationMesh_GetRandomPoint<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Vector3 NavigationMesh::GetRandomPointInCircle(const Vector3& center, float radius, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr, dtPolyRef* randomRef = nullptr) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "Vector3 GetRandomPointInCircle(const Vector3&in, float, const Vector3&in = Vector3::ONE)", AS_FUNCTION_OBJLAST(NavigationMesh_GetRandomPointInCircle<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* float NavigationMesh::GetDistanceToWall(const Vector3& point, float radius, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr, Vector3* hitPos = nullptr, Vector3* hitNormal = nullptr) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "float GetDistanceToWall(const Vector3&in, float, const Vector3&in = Vector3::ONE)", AS_FUNCTION_OBJLAST(NavigationMesh_GetDistanceToWall<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Vector3 NavigationMesh::Raycast(const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr, Vector3* hitNormal = nullptr) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "Vector3 Raycast(const Vector3&in, const Vector3&in, const Vector3&in = Vector3::ONE)", AS_FUNCTION_OBJLAST(NavigationMesh_Raycast<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Vector3 NavigationMesh::MoveAlongSurface(const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, int maxVisited = 3, const dtQueryFilter* filter = nullptr)  | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "Vector3 MoveAlongSurface(const Vector3&in, const Vector3&in, const Vector3&in = Vector3::ONE, int = 3)", AS_FUNCTION_OBJLAST(NavigationMesh_MoveAlongSurface<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* void NavigationMesh::FindPath(PODVector<Vector3>& dest, const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr) | File: ../Navigation/NavigationMesh.h */ \
    engine->RegisterObjectMethod(className, "Array<Vector3>@ FindPath(const Vector3&in, const Vector3&in, const Vector3&in extents = Vector3::ONE)", AS_FUNCTION_OBJLAST(NavigationMesh_FindPath<T>), AS_CALL_CDECL_OBJLAST);

// ========================================================================================

// Vector3 CrowdManager::GetRandomPoint(int queryFilterType, dtPolyRef* randomRef = nullptr) | File: ../Navigation/CrowdManager.h
template <class T> Vector3 CrowdManager_GetRandomPoint(int queryFilterType, T* crowdManager)
{
    return crowdManager->GetRandomPoint(queryFilterType);
}

// Vector3 CrowdManager::GetRandomPointInCircle(const Vector3& center, float radius, int queryFilterType, dtPolyRef* randomRef = nullptr) | File: ../Navigation/CrowdManager.h
template <class T> Vector3 CrowdManager_RandomPointInCircle(const Vector3& center, float radius, int queryFilterType, T* manager)
{
    return manager->GetRandomPointInCircle(center, radius, queryFilterType);
}

// Vector3 CrowdManager::FindNearestPoint(const Vector3& point, int queryFilterType, dtPolyRef* nearestRef = nullptr) | File: ../Navigation/CrowdManager.h
template <class T> Vector3 CrowdManager_FindNearestPoint(const Vector3& point, int queryFilterType, T* ptr)
{
    return ptr->FindNearestPoint(point, queryFilterType);
}

// float CrowdManager::GetDistanceToWall(const Vector3& point, float radius, int queryFilterType, Vector3* hitPos = nullptr, Vector3* hitNormal = nullptr) | File: ../Navigation/CrowdManager.h
template <class T> float CrowdManager_GetDistanceToWall(const Vector3& point, float radius, int queryFilterType, T* ptr)
{
    return ptr->GetDistanceToWall(point, radius, queryFilterType);
}

// Vector3 CrowdManager::Raycast(const Vector3& start, const Vector3& end, int queryFilterType, Vector3* hitNormal = nullptr) | File: ../Navigation/CrowdManager.h
template <class T> Vector3 CrowdManager_Raycast(const Vector3& start, const Vector3& end, int queryFilterType, T* ptr)
{
    return ptr->Raycast(start, end, queryFilterType);
}

#define REGISTER_MEMBERS_MANUAL_PART_CrowdManager() \
    /* Vector3 CrowdManager::GetRandomPoint(int queryFilterType, dtPolyRef* randomRef = nullptr) | File: ../Navigation/CrowdManager.h */ \
    engine->RegisterObjectMethod(className, "Vector3 GetRandomPoint(int)", AS_FUNCTION_OBJLAST(CrowdManager_GetRandomPoint<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Vector3 CrowdManager::GetRandomPointInCircle(const Vector3& center, float radius, int queryFilterType, dtPolyRef* randomRef = nullptr) | File: ../Navigation/CrowdManager.h */ \
    engine->RegisterObjectMethod(className, "Vector3 GetRandomPointInCircle(const Vector3&in, float, int)", AS_FUNCTION_OBJLAST(CrowdManager_RandomPointInCircle<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Vector3 CrowdManager::FindNearestPoint(const Vector3& point, int queryFilterType, dtPolyRef* nearestRef = nullptr) | File: ../Navigation/CrowdManager.h */ \
    engine->RegisterObjectMethod(className, "Vector3 FindNearestPoint(const Vector3&in, int)", AS_FUNCTION_OBJLAST(CrowdManager_FindNearestPoint<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* float CrowdManager::GetDistanceToWall(const Vector3& point, float radius, int queryFilterType, Vector3* hitPos = nullptr, Vector3* hitNormal = nullptr) | File: ../Navigation/CrowdManager.h */ \
    engine->RegisterObjectMethod(className, "float GetDistanceToWall(const Vector3&in, float, int)", AS_FUNCTION_OBJLAST(CrowdManager_GetDistanceToWall<T>), AS_CALL_CDECL_OBJLAST); \
    \
    /* Vector3 CrowdManager::Raycast(const Vector3& start, const Vector3& end, int queryFilterType, Vector3* hitNormal = nullptr) | File: ../Navigation/CrowdManager.h */ \
    engine->RegisterObjectMethod(className, "Vector3 Raycast(const Vector3&in, const Vector3&in, int)", AS_FUNCTION_OBJLAST(CrowdManager_Raycast<T>), AS_CALL_CDECL_OBJLAST);

}

#endif // def URHO3D_NAVIGATION
