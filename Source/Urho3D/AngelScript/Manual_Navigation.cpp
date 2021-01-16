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

#ifdef URHO3D_NAVIGATION

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Manual_Navigation.h"

namespace Urho3D
{

// virtual PODVector<unsigned char> NavigationMesh::GetTileData(const IntVector2 &tile) const | File: ../Navigation/NavigationMesh.h
VectorBuffer NavigationMeshGetTileData(const IntVector2& tile, const NavigationMesh* ptr)
{
    VectorBuffer buffer;
    buffer.SetData(ptr->GetTileData(tile));
    return buffer;
}

// virtual bool NavigationMesh::AddTile(const PODVector< unsigned char > &tileData) | File: ../Navigation/NavigationMesh.h
bool NavigationMeshAddTile(const VectorBuffer& tileData, NavigationMesh* ptr)
{
    return ptr->AddTile(tileData.GetBuffer());
}

// Vector3 NavigationMesh::FindNearestPoint(const Vector3 &point, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr, dtPolyRef *nearestRef=nullptr) | File: ../Navigation/NavigationMesh.h
Vector3 NavigationMeshFindNearestPoint(const Vector3& point, const Vector3& extents, NavigationMesh* ptr)
{
    return ptr->FindNearestPoint(point, extents);
}

// Vector3 NavigationMesh::GetRandomPoint(const dtQueryFilter *filter=nullptr, dtPolyRef *randomRef=nullptr) | File: ../Navigation/NavigationMesh.h
Vector3 NavigationMeshGetRandomPoint(NavigationMesh* ptr)
{
    return ptr->GetRandomPoint();
}

// Vector3 NavigationMesh::GetRandomPointInCircle(const Vector3 &center, float radius, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr, dtPolyRef *randomRef=nullptr) | File: ../Navigation/NavigationMesh.h
Vector3 NavigationMeshGetRandomPointInCircle(const Vector3& center, float radius, const Vector3& extents, NavigationMesh* ptr)
{
    return ptr->GetRandomPointInCircle(center, radius, extents);
}

// float NavigationMesh::GetDistanceToWall(const Vector3 &point, float radius, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr, Vector3 *hitPos=nullptr, Vector3 *hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h
float NavigationMeshGetDistanceToWall(const Vector3& point, float radius, const Vector3& extents, NavigationMesh* ptr)
{
    return ptr->GetDistanceToWall(point, radius, extents);
}

// Vector3 NavigationMesh::Raycast(const Vector3 &start, const Vector3 &end, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr, Vector3 *hitNormal=nullptr) | File: ../Navigation/NavigationMesh.h
Vector3 NavigationMeshRaycast(const Vector3& start, const Vector3& end, const Vector3& extents, NavigationMesh* ptr)
{
    return ptr->Raycast(start, end, extents);
}

// Vector3 NavigationMesh::MoveAlongSurface(const Vector3 &start, const Vector3 &end, const Vector3 &extents=Vector3::ONE, int maxVisited=3, const dtQueryFilter *filter=nullptr) | File: ../Navigation/NavigationMesh.h
Vector3 NavigationMeshMoveAlongSurface(const Vector3& start, const Vector3& end, const Vector3& extents, int maxVisited, NavigationMesh* ptr)
{
    return ptr->MoveAlongSurface(start, end, extents, maxVisited);
}

// void NavigationMesh::FindPath(PODVector< Vector3 > &dest, const Vector3 &start, const Vector3 &end, const Vector3 &extents=Vector3::ONE, const dtQueryFilter *filter=nullptr) | File: ../Navigation/NavigationMesh.h
CScriptArray* NavigationMeshFindPath(const Vector3& start, const Vector3& end, const Vector3& extents, NavigationMesh* ptr)
{
    PODVector<Vector3> dest;
    ptr->FindPath(dest, start, end, extents);
    return VectorToArray<Vector3>(dest, "Array<Vector3>");
}

// ========================================================================================

// Vector3 CrowdManager::GetRandomPoint(int queryFilterType, dtPolyRef *randomRef=nullptr) | File: ../Navigation/CrowdManager.h
Vector3 CrowdManagerGetRandomPoint(int queryFilterType, CrowdManager* crowdManager)
{
    return crowdManager->GetRandomPoint(queryFilterType);
}

// Vector3 CrowdManager::GetRandomPointInCircle(const Vector3 &center, float radius, int queryFilterType, dtPolyRef *randomRef=nullptr) | File: ../Navigation/CrowdManager.h
Vector3 CrowdManagerRandomPointInCircle(const Vector3& center, float radius, int queryFilterType, CrowdManager* manager)
{
    return manager->GetRandomPointInCircle(center, radius, queryFilterType);
}

// Vector3 CrowdManager::FindNearestPoint(const Vector3 &point, int queryFilterType, dtPolyRef *nearestRef=nullptr) | File: ../Navigation/CrowdManager.h
Vector3 CrowdManager_FindNearestPoint(const Vector3& point, int queryFilterType, CrowdManager* ptr)
{
    return ptr->FindNearestPoint(point, queryFilterType);
}

// float CrowdManager::GetDistanceToWall(const Vector3 &point, float radius, int queryFilterType, Vector3 *hitPos=nullptr, Vector3 *hitNormal=nullptr) | File: ../Navigation/CrowdManager.h
float CrowdManager_GetDistanceToWall(const Vector3& point, float radius, int queryFilterType, CrowdManager* ptr)
{
    return ptr->GetDistanceToWall(point, radius, queryFilterType);
}

// Vector3 CrowdManager::Raycast(const Vector3 &start, const Vector3 &end, int queryFilterType, Vector3 *hitNormal=nullptr) | File: ../Navigation/CrowdManager.h
Vector3 CrowdManager_Raycast(const Vector3& start, const Vector3& end, int queryFilterType, CrowdManager* ptr)
{
    return ptr->Raycast(start, end, queryFilterType);
}

}

#endif // def URHO3D_NAVIGATION
