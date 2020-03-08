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

/// \file

#pragma once

#include "../Navigation/CrowdManager.h"
#include "../Scene/Component.h"

namespace Urho3D
{

enum CrowdAgentRequestedTarget
{
    CA_REQUESTEDTARGET_NONE = 0,
    CA_REQUESTEDTARGET_POSITION,
    CA_REQUESTEDTARGET_VELOCITY
};

enum CrowdAgentTargetState
{
    CA_TARGET_NONE = 0,
    CA_TARGET_FAILED,
    CA_TARGET_VALID,
    CA_TARGET_REQUESTING,
    CA_TARGET_WAITINGFORQUEUE,
    CA_TARGET_WAITINGFORPATH,
    CA_TARGET_VELOCITY
};

enum CrowdAgentState
{
    CA_STATE_INVALID = 0,   ///< The agent is not in a valid state.
    CA_STATE_WALKING,       ///< The agent is traversing a normal navigation mesh polygon.
    CA_STATE_OFFMESH        ///< The agent is traversing an off-mesh connection.
};

enum NavigationQuality
{
    NAVIGATIONQUALITY_LOW = 0,
    NAVIGATIONQUALITY_MEDIUM = 1,
    NAVIGATIONQUALITY_HIGH = 2
};

enum NavigationPushiness
{
    NAVIGATIONPUSHINESS_LOW = 0,
    NAVIGATIONPUSHINESS_MEDIUM,
    NAVIGATIONPUSHINESS_HIGH,
    NAVIGATIONPUSHINESS_NONE
};

/// Crowd agent component, requires a CrowdManager component in the scene. When not set explicitly, agent's radius and height are defaulted to navigation mesh's agent radius and height, respectively.
class URHO3D_API CrowdAgent : public Component
{
    URHO3D_OBJECT(CrowdAgent, Component);

    friend class CrowdManager;
    friend void CrowdAgentUpdateCallback(dtCrowdAgent* ag, float dt);

public:
    /// Construct.
    explicit CrowdAgent(Context* context);
    /// Destruct.
    ~CrowdAgent() override;
    /// Register object factory.
    static void RegisterObject(Context* context);
    /// Apply attribute changes that can not be applied immediately. Called after scene load or a network update.
    void ApplyAttributes() override;

    /// Handle enabled/disabled state change.
    void OnSetEnabled() override;
    /// Draw debug geometry.
    void DrawDebugGeometry(bool depthTest);
    /// Draw debug feelers.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    /// Submit a new target position request for this agent.
    void SetTargetPosition(const Vector3& position);
    /// Submit a new target velocity request for this agent.
    void SetTargetVelocity(const Vector3& velocity);
    /// Reset any target request for the specified agent. Note that the agent will continue to move into the current direction; set a zero target velocity to actually stop.
    void ResetTarget();
    /// Update the node position. When set to false, the node position should be updated by other means (e.g. using Physics) in response to the E_CROWD_AGENT_REPOSITION event.
    void SetUpdateNodePosition(bool unodepos);
    /// Set the agent's max acceleration.
    void SetMaxAccel(float maxAccel);
    /// Set the agent's max velocity.
    void SetMaxSpeed(float maxSpeed);
    /// Set the agent's radius.
    void SetRadius(float radius);
    /// Set the agent's height.
    void SetHeight(float height);
    /// Set the agent's query filter type.
    void SetQueryFilterType(unsigned queryFilterType);
    /// Set the agent's obstacle avoidance type.
    void SetObstacleAvoidanceType(unsigned obstacleAvoidanceType);
    /// Set the agent's navigation quality.
    void SetNavigationQuality(NavigationQuality val);
    /// Set the agent's navigation pushiness.
    void SetNavigationPushiness(NavigationPushiness val);

    /// Return the agent's position.
    Vector3 GetPosition() const;
    /// Return the agent's desired velocity.
    Vector3 GetDesiredVelocity() const;
    /// Return the agent's actual velocity.
    Vector3 GetActualVelocity() const;

    /// Return the agent's requested target position.
    const Vector3& GetTargetPosition() const { return targetPosition_; }

    /// Return the agent's requested target velocity.
    const Vector3& GetTargetVelocity() const { return targetVelocity_; }

    /// Return the agent's requested target type, if any.
    CrowdAgentRequestedTarget GetRequestedTargetType() const { return requestedTargetType_; }

    /// Return the agent's  state.
    CrowdAgentState GetAgentState() const;
    /// Return the agent's target state.
    CrowdAgentTargetState GetTargetState() const;

    /// Return true when the node's position should be updated by the CrowdManager.
    bool GetUpdateNodePosition() const { return updateNodePosition_; }

    /// Return the agent id.
    int GetAgentCrowdId() const { return agentCrowdId_; }

    /// Get the agent's max acceleration.
    float GetMaxAccel() const { return maxAccel_; }

    /// Get the agent's max velocity.
    float GetMaxSpeed() const { return maxSpeed_; }

    /// Get the agent's radius.
    float GetRadius() const { return radius_; }

    /// Get the agent's height.
    float GetHeight() const { return height_; }

    /// Get the agent's query filter type.
    unsigned GetQueryFilterType() const { return queryFilterType_; }

    /// Get the agent's obstacle avoidance type.
    unsigned GetObstacleAvoidanceType() const { return obstacleAvoidanceType_; }

    /// Get the agent's navigation quality.
    NavigationQuality GetNavigationQuality() const { return navQuality_; }

    /// Get the agent's navigation pushiness.
    NavigationPushiness GetNavigationPushiness() const { return navPushiness_; }

    /// Return true when the agent has a target.
    bool HasRequestedTarget() const { return requestedTargetType_ != CA_REQUESTEDTARGET_NONE; }

    /// Return true when the agent has arrived at its target.
    bool HasArrived() const;
    /// Return true when the agent is in crowd (being managed by a crowd manager).
    bool IsInCrowd() const;

protected:
    /// Handle crowd agent being updated. It is called by CrowdManager::Update() via callback.
    virtual void OnCrowdUpdate(dtCrowdAgent* ag, float dt);
    /// Handle node being assigned.
    void OnNodeSet(Node* node) override;
    /// Handle node being assigned.
    void OnSceneSet(Scene* scene) override;
    /// \todo Handle node transform being dirtied.
    void OnMarkedDirty(Node* node) override;
    /// Get internal Detour crowd agent.
    const dtCrowdAgent* GetDetourCrowdAgent() const;
    /// Handle navigation mesh tile added.
    void HandleNavigationTileAdded(StringHash eventType, VariantMap& eventData);

private:
    /// Update Detour crowd agent parameter.
    void UpdateParameters(unsigned scope = M_MAX_UNSIGNED);
    /// Add agent into crowd.
    int AddAgentToCrowd(bool force = false);
    /// Remove agent from crowd.
    void RemoveAgentFromCrowd();
    /// Crowd manager.
    WeakPtr<CrowdManager> crowdManager_;
    /// Crowd manager reference to this agent.
    int agentCrowdId_;
    /// Requested target position.
    Vector3 targetPosition_;
    /// Requested target velocity.
    Vector3 targetVelocity_;
    /// Requested target type.
    CrowdAgentRequestedTarget requestedTargetType_;
    /// Flag indicating the node's position should be updated by Detour crowd manager.
    bool updateNodePosition_;
    /// Agent's max acceleration.
    float maxAccel_;
    /// Agent's max Velocity.
    float maxSpeed_;
    /// Agent's radius, if 0 the navigation mesh's setting will be used.
    float radius_;
    /// Agent's height, if 0 the navigation mesh's setting will be used.
    float height_;
    /// Agent's query filter type, it is an index to the query filter buffer configured in Detour crowd manager.
    unsigned queryFilterType_;
    /// Agent's obstacle avoidance type, it is an index to the obstacle avoidance array configured in Detour crowd manager. It is ignored when agent's navigation quality is not set to "NAVIGATIONQUALITY_HIGH".
    unsigned obstacleAvoidanceType_;
    /// Agent's navigation quality. The higher the setting, the higher the CPU usage during crowd simulation.
    NavigationQuality navQuality_;
    /// Agent's navigation pushiness. The higher the setting, the stronger the agent pushes its colliding neighbours around.
    NavigationPushiness navPushiness_;
    /// Agent's previous position used to check for position changes.
    Vector3 previousPosition_;
    /// Agent's previous target state used to check for state changes.
    CrowdAgentTargetState previousTargetState_;
    /// Agent's previous agent state used to check for state changes.
    CrowdAgentState previousAgentState_;
    /// Internal flag to ignore transform changes because it came from us, used in OnCrowdAgentReposition().
    bool ignoreTransformChanges_;
};

}
