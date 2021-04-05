// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

#ifdef URHO3D_NAVIGATION

// struct CrowdObstacleAvoidanceParams | File: ../Navigation/CrowdManager.h
void CollectMembers_CrowdObstacleAvoidanceParams(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("float CrowdObstacleAvoidanceParams::velBias", "float velBias", offsetof(CrowdObstacleAvoidanceParams, velBias)));
    members.fields_.Push(RegisterObjectPropertyArgs("float CrowdObstacleAvoidanceParams::weightDesVel", "float weightDesVel", offsetof(CrowdObstacleAvoidanceParams, weightDesVel)));
    members.fields_.Push(RegisterObjectPropertyArgs("float CrowdObstacleAvoidanceParams::weightCurVel", "float weightCurVel", offsetof(CrowdObstacleAvoidanceParams, weightCurVel)));
    members.fields_.Push(RegisterObjectPropertyArgs("float CrowdObstacleAvoidanceParams::weightSide", "float weightSide", offsetof(CrowdObstacleAvoidanceParams, weightSide)));
    members.fields_.Push(RegisterObjectPropertyArgs("float CrowdObstacleAvoidanceParams::weightToi", "float weightToi", offsetof(CrowdObstacleAvoidanceParams, weightToi)));
    members.fields_.Push(RegisterObjectPropertyArgs("float CrowdObstacleAvoidanceParams::horizTime", "float horizTime", offsetof(CrowdObstacleAvoidanceParams, horizTime)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char CrowdObstacleAvoidanceParams::gridSize", "uint8 gridSize", offsetof(CrowdObstacleAvoidanceParams, gridSize)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char CrowdObstacleAvoidanceParams::adaptiveDivs", "uint8 adaptiveDivs", offsetof(CrowdObstacleAvoidanceParams, adaptiveDivs)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char CrowdObstacleAvoidanceParams::adaptiveRings", "uint8 adaptiveRings", offsetof(CrowdObstacleAvoidanceParams, adaptiveRings)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char CrowdObstacleAvoidanceParams::adaptiveDepth", "uint8 adaptiveDepth", offsetof(CrowdObstacleAvoidanceParams, adaptiveDepth)));

}

// struct NavAreaStub | File: ../Navigation/NavBuildData.h
void CollectMembers_NavAreaStub(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("BoundingBox NavAreaStub::bounds_", "BoundingBox bounds", offsetof(NavAreaStub, bounds_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char NavAreaStub::areaID_", "uint8 areaID", offsetof(NavAreaStub, areaID_)));

}

// struct NavBuildData | File: ../Navigation/NavBuildData.h
void CollectMembers_NavBuildData(MemberCollection& members)
{
    // PODVector<Vector3> NavBuildData::vertices_
    // Error: type "PODVector<Vector3>" can not automatically bind
    // PODVector<int> NavBuildData::indices_
    // Error: type "PODVector<int>" can not automatically bind
    // PODVector<Vector3> NavBuildData::offMeshVertices_
    // Error: type "PODVector<Vector3>" can not automatically bind
    // PODVector<float> NavBuildData::offMeshRadii_
    // Error: type "PODVector<float>" can not automatically bind
    // PODVector<unsigned short> NavBuildData::offMeshFlags_
    // Error: type "PODVector<unsigned short>" can not automatically bind
    // PODVector<unsigned char> NavBuildData::offMeshAreas_
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // PODVector<unsigned char> NavBuildData::offMeshDir_
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // rcContext* NavBuildData::ctx_
    // Not registered because pointer
    // rcHeightfield* NavBuildData::heightField_
    // Not registered because pointer
    // rcCompactHeightfield* NavBuildData::compactHeightField_
    // Not registered because pointer
    // PODVector<NavAreaStub> NavBuildData::navAreas_
    // Error: type "PODVector<NavAreaStub>" can not automatically bind

    members.fields_.Push(RegisterObjectPropertyArgs("BoundingBox NavBuildData::worldBoundingBox_", "BoundingBox worldBoundingBox", offsetof(NavBuildData, worldBoundingBox_)));

}

// struct NavigationGeometryInfo | File: ../Navigation/NavigationMesh.h
void CollectMembers_NavigationGeometryInfo(MemberCollection& members)
{
    // Component* NavigationGeometryInfo::component_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned NavigationGeometryInfo::lodLevel_", "uint lodLevel", offsetof(NavigationGeometryInfo, lodLevel_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Matrix3x4 NavigationGeometryInfo::transform_", "Matrix3x4 transform", offsetof(NavigationGeometryInfo, transform_)));
    members.fields_.Push(RegisterObjectPropertyArgs("BoundingBox NavigationGeometryInfo::boundingBox_", "BoundingBox boundingBox", offsetof(NavigationGeometryInfo, boundingBox_)));

}

// struct NavigationPathPoint | File: ../Navigation/NavigationMesh.h
void CollectMembers_NavigationPathPoint(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Vector3 NavigationPathPoint::position_", "Vector3 position", offsetof(NavigationPathPoint, position_)));
    members.fields_.Push(RegisterObjectPropertyArgs("NavigationPathPointFlag NavigationPathPoint::flag_", "NavigationPathPointFlag flag", offsetof(NavigationPathPoint, flag_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned char NavigationPathPoint::areaID_", "uint8 areaID", offsetof(NavigationPathPoint, areaID_)));

}

// struct DynamicNavBuildData | File: ../Navigation/NavBuildData.h
void CollectMembers_DynamicNavBuildData(MemberCollection& members)
{
    CollectMembers_NavBuildData(members);

    // dtTileCacheContourSet* DynamicNavBuildData::contourSet_
    // Not registered because pointer
    // dtTileCachePolyMesh* DynamicNavBuildData::polyMesh_
    // Not registered because pointer
    // rcHeightfieldLayerSet* DynamicNavBuildData::heightFieldLayers_
    // Not registered because pointer
    // dtTileCacheAlloc* DynamicNavBuildData::alloc_
    // Not registered because pointer

}

// struct SimpleNavBuildData | File: ../Navigation/NavBuildData.h
void CollectMembers_SimpleNavBuildData(MemberCollection& members)
{
    CollectMembers_NavBuildData(members);

    // rcContourSet* SimpleNavBuildData::contourSet_
    // Not registered because pointer
    // rcPolyMesh* SimpleNavBuildData::polyMesh_
    // Not registered because pointer
    // rcPolyMeshDetail* SimpleNavBuildData::polyMeshDetail_
    // Not registered because pointer

}

// class CrowdAgent | File: ../Navigation/CrowdAgent.h
void CollectMembers_CrowdAgent(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");
    Remove(members.methods_, "virtual void Component::OnSetEnabled()");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

}

// class CrowdManager | File: ../Navigation/CrowdManager.h
void CollectMembers_CrowdManager(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // Vector3 CrowdManager::FindNearestPoint(const Vector3& point, int queryFilterType, dtPolyRef* nearestRef = nullptr)
    // Error: type "dtPolyRef*" can not automatically bind
    // void CrowdManager::FindPath(PODVector<Vector3>& dest, const Vector3& start, const Vector3& end, int queryFilterType)
    // Error: type "PODVector<Vector3>&" can not automatically bind
    // float CrowdManager::GetDistanceToWall(const Vector3& point, float radius, int queryFilterType, Vector3* hitPos = nullptr, Vector3* hitNormal = nullptr)
    // Error: type "Vector3*" can not automatically bind
    // VariantVector CrowdManager::GetObstacleAvoidanceTypesAttr() const
    // Error: type "VariantVector" can not automatically bind
    // VariantVector CrowdManager::GetQueryFilterTypesAttr() const
    // Error: type "VariantVector" can not automatically bind
    // Vector3 CrowdManager::GetRandomPoint(int queryFilterType, dtPolyRef* randomRef = nullptr)
    // Error: type "dtPolyRef*" can not automatically bind
    // Vector3 CrowdManager::GetRandomPointInCircle(const Vector3& center, float radius, int queryFilterType, dtPolyRef* randomRef = nullptr)
    // Error: type "dtPolyRef*" can not automatically bind
    // Vector3 CrowdManager::Raycast(const Vector3& start, const Vector3& end, int queryFilterType, Vector3* hitNormal = nullptr)
    // Error: type "Vector3*" can not automatically bind
    // void CrowdManager::SetObstacleAvoidanceTypesAttr(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind
    // void CrowdManager::SetQueryFilterTypesAttr(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind

}

// class NavArea | File: ../Navigation/NavArea.h
void CollectMembers_NavArea(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

}

// class Navigable | File: ../Navigation/Navigable.h
void CollectMembers_Navigable(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

}

// class NavigationMesh | File: ../Navigation/NavigationMesh.h
void CollectMembers_NavigationMesh(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // virtual bool NavigationMesh::AddTile(const PODVector<unsigned char>& tileData)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind
    // Vector3 NavigationMesh::FindNearestPoint(const Vector3& point, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr, dtPolyRef* nearestRef = nullptr)
    // Error: type "const dtQueryFilter*" can not automatically bind
    // void NavigationMesh::FindPath(PODVector<NavigationPathPoint>& dest, const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr)
    // Error: type "PODVector<NavigationPathPoint>&" can not automatically bind
    // void NavigationMesh::FindPath(PODVector<Vector3>& dest, const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr)
    // Error: type "PODVector<Vector3>&" can not automatically bind
    // float NavigationMesh::GetDistanceToWall(const Vector3& point, float radius, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr, Vector3* hitPos = nullptr, Vector3* hitNormal = nullptr)
    // Error: type "const dtQueryFilter*" can not automatically bind
    // virtual PODVector<unsigned char> NavigationMesh::GetNavigationDataAttr() const
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // Vector3 NavigationMesh::GetRandomPoint(const dtQueryFilter* filter = nullptr, dtPolyRef* randomRef = nullptr)
    // Error: type "const dtQueryFilter*" can not automatically bind
    // Vector3 NavigationMesh::GetRandomPointInCircle(const Vector3& center, float radius, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr, dtPolyRef* randomRef = nullptr)
    // Error: type "const dtQueryFilter*" can not automatically bind
    // virtual PODVector<unsigned char> NavigationMesh::GetTileData(const IntVector2& tile) const
    // Error: type "PODVector<unsigned char>" can not automatically bind
    // Vector3 NavigationMesh::MoveAlongSurface(const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, int maxVisited = 3, const dtQueryFilter* filter = nullptr)
    // Error: type "const dtQueryFilter*" can not automatically bind
    // Vector3 NavigationMesh::Raycast(const Vector3& start, const Vector3& end, const Vector3& extents = Vector3::ONE, const dtQueryFilter* filter = nullptr, Vector3* hitNormal = nullptr)
    // Error: type "const dtQueryFilter*" can not automatically bind
    // virtual void NavigationMesh::SetNavigationDataAttr(const PODVector<unsigned char>& value)
    // Error: type "const PODVector<unsigned char>&" can not automatically bind

}

// class Obstacle | File: ../Navigation/Obstacle.h
void CollectMembers_Obstacle(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");
    Remove(members.methods_, "virtual void Component::OnSetEnabled()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

}

// class OffMeshConnection | File: ../Navigation/OffMeshConnection.h
void CollectMembers_OffMeshConnection(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.methods_, "virtual void Component::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

}

// class DynamicNavigationMesh | File: ../Navigation/DynamicNavigationMesh.h
void CollectMembers_DynamicNavigationMesh(MemberCollection& members)
{
    CollectMembers_NavigationMesh(members);

    Remove(members.methods_, "virtual PODVector<unsigned char> NavigationMesh::GetNavigationDataAttr() const");
    Remove(members.methods_, "virtual PODVector<unsigned char> NavigationMesh::GetTileData(const IntVector2& tile) const");
    Remove(members.methods_, "virtual bool NavigationMesh::AddTile(const PODVector<unsigned char>& tileData)");
    Remove(members.methods_, "virtual bool NavigationMesh::Allocate(const BoundingBox& boundingBox, unsigned maxTiles)");
    Remove(members.methods_, "virtual bool NavigationMesh::Build()");
    Remove(members.methods_, "virtual bool NavigationMesh::Build(const BoundingBox& boundingBox)");
    Remove(members.methods_, "virtual bool NavigationMesh::Build(const IntVector2& from, const IntVector2& to)");
    Remove(members.methods_, "virtual void NavigationMesh::RemoveAllTiles()");
    Remove(members.methods_, "virtual void NavigationMesh::RemoveTile(const IntVector2& tile)");
    Remove(members.methods_, "virtual void NavigationMesh::SetNavigationDataAttr(const PODVector<unsigned char>& value)");
    Remove(members.methods_, "void NavigationMesh::DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override");
    Remove(members.methods_, "void NavigationMesh::DrawDebugGeometry(bool depthTest)");

    Remove(members.staticMethods_, "static void NavigationMesh::RegisterObject(Context* context)");

}

#endif // def URHO3D_NAVIGATION

} // namespace Urho3D
