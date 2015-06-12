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
#include "../Navigation/DetourCrowdManager.h"

namespace Urho3D
{

enum CrowdTargetState
{
    CROWD_AGENT_TARGET_NONE = 0,
    CROWD_AGENT_TARGET_FAILED,
    CROWD_AGENT_TARGET_VALID,
    CROWD_AGENT_TARGET_REQUESTING,
    CROWD_AGENT_TARGET_WAITINGFORQUEUE,
    CROWD_AGENT_TARGET_WAITINGFORPATH,
    CROWD_AGENT_TARGET_VELOCITY
};

enum CrowdAgentState
{
    CROWD_AGENT_INVALID = 0,      ///< The agent is not in a valid state.
    CROWD_AGENT_READY,            ///< The agent is traversing a normal navigation mesh polygon.
    CROWD_AGENT_TRAVERSINGLINK    ///< The agent is traversing an off-mesh connection.
};

/// DetourCrowd Agent, requires a DetourCrowdManager in the scene. Agent's radius and height is set through the navigation mesh.
class URHO3D_API CrowdAgent : public Component
{
    OBJECT(CrowdAgent);
    friend class DetourCrowdManager;

public:
    /// Construct.
    CrowdAgent(Context* context);
    /// Destruct.
    virtual ~CrowdAgent();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled();
    /// Draw debug geometry.
    void DrawDebugGeometry(bool);
    /// Draw debug feelers.
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

    /// Set the navigation filter type the agent will use.
    void SetNavigationFilterType(unsigned filterTypeID);
    /// Submit a new move request for this agent.
    void SetMoveTarget(const Vector3& position);
    /// Reset any request for the specified agent.
    void ResetMoveTarget();
    /// Submit a new move velocity request for this agent.
    void SetMoveVelocity(const Vector3& velocity);
    /// Update the node position. When set to false, the node position should be updated by other means (e.g. using Physics) in response to the E_CROWD_AGENT_REPOSITION event.
    void SetUpdateNodePosition(bool unodepos);
    /// Set the agent's max acceleration.
    void SetMaxAccel(float val);
    /// Set the agent's max velocity.
    void SetMaxSpeed(float val);
    /// Set the agent's radius.
    void SetRadius(float val);
    /// Set the agent's height.
    void SetHeight(float val);
    /// Set the agent's navigation quality.
    void SetNavigationQuality(NavigationQuality val);
    /// Set the agent's navigation pushiness.
    void SetNavigationPushiness(NavigationPushiness val);

    /// Get the navigation filter type this agent is using.
    unsigned GetNavigationFilterType() const { return filterType_; }
    /// Return the agent's position.
    Vector3 GetPosition() const;
    /// Return the agent's desired velocity.
    Vector3 GetDesiredVelocity() const;
    /// Return the agent's actual velocity.
    Vector3 GetActualVelocity() const;
    /// Return the agent's target position.
    const Vector3& GetTargetPosition() const { return targetPosition_; }
    /// Return the agent's  state.
    CrowdAgentState GetAgentState() const;
    /// Return the agent's target state.
    CrowdTargetState GetTargetState() const;
    /// Return true when the node's position should be updated by the CrowdManager.
    bool GetUpdateNodePosition() const { return updateNodePosition_; }
    /// Return the agent id.
    int GetAgentCrowdId() const { return agentCrowdId_; }
    /// Get the agent's max velocity.
    float GetMaxSpeed() const { return maxSpeed_; }
    /// Get the agent's max acceleration.
    float GetMaxAccel() const { return maxAccel_; }
    /// Get the agent's radius.
    float GetRadius() const { return radius_; }
    /// Get the agent's height.
    float GetHeight() const { return height_; }
    /// Get the agent's navigation quality.
    NavigationQuality GetNavigationQuality() const {return navQuality_; }
    /// Get the agent's navigation pushiness.
    NavigationPushiness GetNavigationPushiness() const {return navPushiness_; }
    /// Return true when the agent has arrived at its target.
    bool HasArrived() const;

    /// Get serialized data of internal state.
    PODVector<unsigned char> GetAgentDataAttr() const;
    /// Set serialized data of internal state.
    void SetAgentDataAttr(const PODVector<unsigned char>& value);

protected:
    /// Update the nodes position if updateNodePosition is set. Is called in DetourCrowdManager::Update().
    virtual void OnCrowdAgentReposition(const Vector3& newPos, const Vector3& newVel);
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// \todo Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);
    /// Get internal Detour crowd agent.
    const dtCrowdAgent* GetDetourCrowdAgent() const;
private:
    /// Create or re-add.
    void AddAgentToCrowd();
    /// Remove.
    void RemoveAgentFromCrowd();
    /// Detour crowd manager.
    WeakPtr<DetourCrowdManager> crowdManager_;
    /// Flag indicating agent is in DetourCrowd.
    bool inCrowd_;
    /// DetourCrowd reference to this agent.
    int agentCrowdId_;
    /// Reference to poly closest to requested target position.
    unsigned int targetRef_;
    /// Actual target position, closest to that requested.
    Vector3 targetPosition_;
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
    /// Agent's assigned navigation filter type, the actual filter is owned by the DetourCrowdManager the agent belongs to.
    unsigned filterType_;
    /// Agent's NavigationAvoidanceQuality.
    NavigationQuality navQuality_;
    /// Agent's Navigation Pushiness.
    NavigationPushiness navPushiness_;
    /// Agent's previous position used to check for position changes.
    Vector3 previousPosition_;
    /// Agent's previous target state used to check for state changes.
    CrowdTargetState previousTargetState_;
    /// Agent's previous agent state used to check for state changes.
    CrowdAgentState previousAgentState_;
    /// Internal flag to ignore transform changes because it came from us, used in OnCrowdAgentReposition().
    bool ignoreTransformChanges_;
};

}
