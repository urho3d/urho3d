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

#pragma once

#include "../Scene/Component.h"

class dtCrowd;
struct dtCrowdAgent;
struct dtCrowdAgentDebugInfo;

namespace Urho3D
{

class CrowdAgent;
class NavigationMesh;

enum NavigationQuality
{
    NAVIGATIONQUALITY_LOW = 0,
    NAVIGATIONQUALITY_MEDIUM = 1,
    NAVIGATIONQUALITY_HIGH = 2
};

enum NavigationPushiness
{
    PUSHINESS_LOW = 0,
    PUSHINESS_MEDIUM,
    PUSHINESS_HIGH
};


/// Detour Crowd Simulation Scene Component. Should be added only to the root scene node. Agent's radius and height is set through the navigation mesh. \todo support multiple agent's radii and heights.
class URHO3D_API DetourCrowdManager : public Component
{
    OBJECT(DetourCrowdManager);
    friend class CrowdAgent;

public:
    /// Construct.
    DetourCrowdManager(Context* context);
    /// Destruct.
    virtual ~DetourCrowdManager();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Assigns the navigation mesh for the crowd.
    void SetNavigationMesh(NavigationMesh* navMesh);
    /// Set the cost of an area-type for the specified navigation filter type.
    void SetAreaCost(unsigned filterTypeID, unsigned areaID, float weight);
    /// Set the maximum number of agents.
    void SetMaxAgents(unsigned agentCt);
    /// Set the crowd move target. The move target is applied to all crowd agents within the id range, excluding crowd agent which does not have acceleration.
    void SetCrowdTarget(const Vector3& position, int startId = 0, int endId = M_MAX_INT);
    /// Reset the crowd move target to all crowd agents within the id range, excluding crowd agent which does not have acceleration.
    void ResetCrowdTarget(int startId = 0, int endId = M_MAX_INT);
    /// Set the crowd move velocity. The move velocity is applied to all crowd agents within the id range, excluding crowd agent which does not have acceleration.
    void SetCrowdVelocity(const Vector3& velocity, int startId = 0, int endId = M_MAX_INT);

    /// Get the Navigation mesh assigned to the crowd.
    NavigationMesh* GetNavigationMesh() const { return navigationMesh_; }
    /// Get the cost of an area-type for the specified navigation filter type.
    float GetAreaCost(unsigned filterTypeID, unsigned areaID) const;
    /// Get the maximum number of agents.
    unsigned GetMaxAgents() const { return maxAgents_; }
    /// Get the current number of active agents.
    unsigned GetAgentCount() const;

    /// Draw the agents' pathing debug data.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);
    /// Add debug geometry to the debug renderer.
    void DrawDebugGeometry(bool depthTest);
    /// Get the currently included agents.
    const PODVector<CrowdAgent*>& GetActiveAgents() const { return agents_; }
    /// Create detour crowd component for the specified navigation mesh.
    bool CreateCrowd();

protected:
    /// Create and adds an detour crowd agent, Agent's radius and height is set through the navigation mesh. Return -1 on error, agent ID on success.
    int AddAgent(CrowdAgent* agent, const Vector3& pos);
    /// Removes the detour crowd agent.
    void RemoveAgent(CrowdAgent* agent);

    /// Update the Navigation Agent's Avoidance Quality for the specified agent.
    void UpdateAgentNavigationQuality(CrowdAgent* agent, NavigationQuality nq);
    /// Update the Navigation Agent's Pushiness for the specified agent.
    void UpdateAgentPushiness(CrowdAgent* agent, NavigationPushiness pushiness);

    /// Set the move target for the specified agent.
    bool SetAgentTarget(CrowdAgent* agent, Vector3 target);
    /// Set the move target for the specified agent.
    bool SetAgentTarget(CrowdAgent* agent, Vector3 target, unsigned int& targetRef);

    /// Get the closest walkable position.
    Vector3 GetClosestWalkablePosition(Vector3 pos) const;

protected:
    /// Update the crowd simulation.
    void Update(float delta);
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Get the detour crowd agent.
    const dtCrowdAgent* GetCrowdAgent(int agent);
    /// Get the internal detour crowd component.
    dtCrowd* GetCrowd() const { return crowd_; }

private:
    /// Handle the scene subsystem update event.
    void HandleSceneSubsystemUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle full rebuilds of the navigation mesh.
    void HandleNavMeshFullRebuild(StringHash eventType, VariantMap& eventData);

    /// Internal crowd component.
    dtCrowd* crowd_;
    /// NavigationMesh for which the crowd was created.
    WeakPtr<NavigationMesh> navigationMesh_;
    /// Max agents for the crowd.
    unsigned maxAgents_;
    /// Internal debug information.
    dtCrowdAgentDebugInfo* agentDebug_;
    /// Container for fetching agents from DetourCrowd during update.
    PODVector<dtCrowdAgent*> agentBuffer_;
    /// Container for fetching agents from DetourCrowd during update.
    PODVector<CrowdAgent*> agents_;
};

}
