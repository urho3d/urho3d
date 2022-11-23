// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Scene/Component.h"

#ifdef DT_POLYREF64
using dtPolyRef = uint64_t;
#else
using dtPolyRef = unsigned int;
#endif

class dtCrowd;
class dtQueryFilter;
struct dtCrowdAgent;

namespace Urho3D
{

class CrowdAgent;
class NavigationMesh;

/// Parameter structure for obstacle avoidance params (copied from DetourObstacleAvoidance.h in order to hide Detour header from Urho3D library users).
/// @pod
struct CrowdObstacleAvoidanceParams
{
    float velBias;
    float weightDesVel;
    float weightCurVel;
    float weightSide;
    float weightToi;
    float horizTime;
    unsigned char gridSize;         ///< grid
    unsigned char adaptiveDivs;     ///< adaptive
    unsigned char adaptiveRings;    ///< adaptive
    unsigned char adaptiveDepth;    ///< adaptive
};

/// Crowd manager scene component. Should be added only to the root scene node.
class URHO3D_API CrowdManager : public Component
{
    URHO3D_OBJECT(CrowdManager, Component);

    friend class CrowdAgent;

public:
    /// Construct.
    explicit CrowdManager(Context* context);
    /// Destruct.
    ~CrowdManager() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);
    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    void ApplyAttributes() override;

    /// Draw the agents' pathing debug data.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;
    /// Add debug geometry to the debug renderer.
    void DrawDebugGeometry(bool depthTest);

    /// Set the crowd target position. The target position is set to all crowd agents found in the specified node. Defaulted to scene node.
    void SetCrowdTarget(const Vector3& position, Node* node = nullptr);
    /// Set the crowd move velocity. The move velocity is applied to all crowd agents found in the specified node. Defaulted to scene node.
    void SetCrowdVelocity(const Vector3& velocity, Node* node = nullptr);
    /// Reset any crowd target for all crowd agents found in the specified node. Defaulted to scene node.
    void ResetCrowdTarget(Node* node = nullptr);
    /// Set the maximum number of agents.
    /// @property
    void SetMaxAgents(unsigned maxAgents);
    /// Set the maximum radius of any agent.
    /// @property
    void SetMaxAgentRadius(float maxAgentRadius);
    /// Assigns the navigation mesh for the crowd.
    /// @property{set_navMesh}
    void SetNavigationMesh(NavigationMesh* navMesh);
    /// Set all the query filter types configured in the crowd based on the corresponding attribute.
    void SetQueryFilterTypesAttr(const VariantVector& value);
    /// Set the include flags for the specified query filter type.
    void SetIncludeFlags(unsigned queryFilterType, unsigned short flags);
    /// Set the exclude flags for the specified query filter type.
    void SetExcludeFlags(unsigned queryFilterType, unsigned short flags);
    /// Set the cost of an area for the specified query filter type.
    void SetAreaCost(unsigned queryFilterType, unsigned areaID, float cost);
    /// Set all the obstacle avoidance types configured in the crowd based on the corresponding attribute.
    void SetObstacleAvoidanceTypesAttr(const VariantVector& value);
    /// Set the params for the specified obstacle avoidance type.
    void SetObstacleAvoidanceParams(unsigned obstacleAvoidanceType, const CrowdObstacleAvoidanceParams& params);

    /// Get all the crowd agent components in the specified node hierarchy. If the node is not specified then use scene node. When inCrowdFilter is set to true then only get agents that are in the crowd.
    Vector<CrowdAgent*> GetAgents(Node* node = nullptr, bool inCrowdFilter = true) const;
    /// Find the nearest point on the navigation mesh to a given point using the crowd initialized query extent (based on maxAgentRadius) and the specified query filter type.
    Vector3 FindNearestPoint(const Vector3& point, int queryFilterType, dtPolyRef* nearestRef = nullptr);
    /// Try to move along the surface from one point to another using the crowd initialized query extent (based on maxAgentRadius) and the specified query filter type.
    Vector3 MoveAlongSurface(const Vector3& start, const Vector3& end, int queryFilterType, int maxVisited = 3);
    /// Find a path between world space points using the crowd initialized query extent (based on maxAgentRadius) and the specified query filter type. Return non-empty list of points if successful.
    void FindPath(Vector<Vector3>& dest, const Vector3& start, const Vector3& end, int queryFilterType);
    /// Return a random point on the navigation mesh using the crowd initialized query extent (based on maxAgentRadius) and the specified query filter type.
    Vector3 GetRandomPoint(int queryFilterType, dtPolyRef* randomRef = nullptr);
    /// Return a random point on the navigation mesh within a circle using the crowd initialized query extent (based on maxAgentRadius) and the specified query filter type. The circle radius is only a guideline and in practice the returned point may be further away.
    Vector3 GetRandomPointInCircle(const Vector3& center, float radius, int queryFilterType, dtPolyRef* randomRef = nullptr);
    /// Return distance to wall from a point using the crowd initialized query extent (based on maxAgentRadius) and the specified query filter type. Maximum search radius must be specified.
    float GetDistanceToWall(const Vector3& point, float radius, int queryFilterType, Vector3* hitPos = nullptr, Vector3* hitNormal = nullptr);
    /// Perform a walkability raycast on the navigation mesh between start and end using the crowd initialized query extent (based on maxAgentRadius) and the specified query filter type. Return the point where a wall was hit, or the end point if no walls.
    Vector3 Raycast(const Vector3& start, const Vector3& end, int queryFilterType, Vector3* hitNormal = nullptr);

    /// Get the maximum number of agents.
    /// @property
    unsigned GetMaxAgents() const { return maxAgents_; }

    /// Get the maximum radius of any agent.
    /// @property
    float GetMaxAgentRadius() const { return maxAgentRadius_; }

    /// Get the Navigation mesh assigned to the crowd.
    /// @property{get_navMesh}
    NavigationMesh* GetNavigationMesh() const { return navigationMesh_; }

    /// Get the number of configured query filter types.
    /// @property
    unsigned GetNumQueryFilterTypes() const { return numQueryFilterTypes_; }

    /// Get the number of configured area in the specified query filter type.
    /// @property
    unsigned GetNumAreas(unsigned queryFilterType) const;
    /// Return all the filter types configured in the crowd as attribute.
    VariantVector GetQueryFilterTypesAttr() const;
    /// Get the include flags for the specified query filter type.
    unsigned short GetIncludeFlags(unsigned queryFilterType) const;
    /// Get the exclude flags for the specified query filter type.
    unsigned short GetExcludeFlags(unsigned queryFilterType) const;
    /// Get the cost of an area for the specified query filter type.
    float GetAreaCost(unsigned queryFilterType, unsigned areaID) const;

    /// Get the number of configured obstacle avoidance types.
    /// @property
    unsigned GetNumObstacleAvoidanceTypes() const { return numObstacleAvoidanceTypes_; }

    /// Return all the obstacle avoidance types configured in the crowd as attribute.
    VariantVector GetObstacleAvoidanceTypesAttr() const;
    /// Get the params for the specified obstacle avoidance type.
    const CrowdObstacleAvoidanceParams& GetObstacleAvoidanceParams(unsigned obstacleAvoidanceType) const;

protected:
    /// Create and initialized internal Detour crowd object. When it is a recreate, it preserves the configuration and attempts to re-add existing agents in the previous crowd back to the newly created crowd.
    bool CreateCrowd();
    /// Create and adds an detour crowd agent, Agent's radius and height is set through the navigation mesh. Return -1 on error, agent ID on success.
    int AddAgent(CrowdAgent* agent, const Vector3& pos);
    /// Removes the detour crowd agent.
    void RemoveAgent(CrowdAgent* agent);

protected:
    /// Handle scene being assigned.
    void OnSceneSet(Scene* scene) override;
    /// Update the crowd simulation.
    void Update(float delta);
    /// Get the detour crowd agent.
    const dtCrowdAgent* GetDetourCrowdAgent(int agent) const;
    /// Get the detour query filter.
    const dtQueryFilter* GetDetourQueryFilter(unsigned queryFilterType) const;

    /// Get the internal detour crowd component.
    dtCrowd* GetCrowd() const { return crowd_; }

private:
    /// Handle the scene subsystem update event.
    void HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle navigation mesh changed event. It can be navmesh being rebuilt or being removed from its node.
    void HandleNavMeshChanged(StringHash eventType, VariantMap& eventData);
    /// Handle component added in the scene to check for late addition of the navmesh.
    void HandleComponentAdded(StringHash eventType, VariantMap& eventData);

    /// Internal Detour crowd object.
    dtCrowd* crowd_{};
    /// NavigationMesh for which the crowd was created.
    WeakPtr<NavigationMesh> navigationMesh_;
    /// The NavigationMesh component Id for pending crowd creation.
    unsigned navigationMeshId_{};
    /// The maximum number of agents the crowd can manage.
    unsigned maxAgents_{};
    /// The maximum radius of any agent that will be added to the crowd.
    float maxAgentRadius_{};
    /// Number of query filter types configured in the crowd. Limit to DT_CROWD_MAX_QUERY_FILTER_TYPE.
    unsigned numQueryFilterTypes_{};
    /// Number of configured area in each filter type. Limit to DT_MAX_AREAS.
    Vector<unsigned> numAreas_;
    /// Number of obstacle avoidance types configured in the crowd. Limit to DT_CROWD_MAX_OBSTAVOIDANCE_PARAMS.
    unsigned numObstacleAvoidanceTypes_{};
};

}
