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
    CROWD_AGENT_TARGET_WAITINGFORPATH,
    CROWD_AGENT_TARGET_WAITINGFORQUEUE,
    CROWD_AGENT_TARGET_VELOCITY,
    CROWD_AGENT_TARGET_ARRIVED
};

enum CrowdAgentState
{
    CROWD_AGENT_INVALID = 0,	///< The agent is not in a valid state.
    CROWD_AGENT_READY,			///< The agent is traversing a normal navigation mesh polygon
    CROWD_AGENT_TRAVERSINGLINK	///< The agent is traversing an off-mesh connection.
};

/// DetourCrowd Agent, requires a DetourCrowdManager in the scene
/// Agent's radius and height is set through the navigation mesh.
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
    /// Draw debug geometry
    void DrawDebugGeometry(bool);
    /// Draw debug feelers
    virtual void DrawDebugGeometry(DebugRenderer* debug, bool depthTest);

    /// Sets the navigation filter type the agent will use
    void SetNavigationFilterType(unsigned filterTypeID);
    /// Submits a new move request for this agent.
    bool SetMoveTarget(const Vector3& position);
    /// Submits a new move velocity request for this agent.
    bool SetMoveVelocity(const Vector3& velocity);
    /// Update the nodes position.
    void SetUpdateNodePosition(bool unodepos);
    /// Sets the agent's max acceleration.
    void SetMaxAccel(float val);
    /// Sets the agent's max velocity.
    void SetMaxSpeed(float val);
    /// Sets the agent's radius
    void SetRadius(float val);
    /// Sets the agent's height
    void SetHeight(float val);
    /// Sets the agent's navigation quality
    void SetNavigationQuality(NavigationQuality val);
    /// Sets the agent's navigation pushiness
    void SetNavigationPushiness(NavigationPushiness val);

    /// Gets the navigation filter type this agent is using
    unsigned GetNavigationFilterType() const { return filterType_; }
    /// Returns the agent's position.
    Vector3 GetPosition() const;
    /// Returns the agent's desired velocity.
    Vector3 GetDesiredVelocity() const;
    /// Returns the agent's actual velocity.
    Vector3 GetActualVelocity() const;
    /// Returns the agent's target position.
    const Vector3& GetTargetPosition() const;
    /// Returns the agent's  state.
    CrowdAgentState   GetAgentState() const;
    /// Returns the agent's target state.
    CrowdTargetState  GetTargetState() const;
    /// Returns if the node's position is updating because of the crowd.
    bool GetUpdateNodePosition();
    /// Returns the agent id.
    int GetAgentCrowdId() const { return agentCrowdId_; }
    /// Gets the agent's max velocity.
    float GetMaxSpeed() const { return maxSpeed_; }
    /// Gets the agent's max acceleration.
    float GetMaxAccel()	const { return maxAccel_; }
    /// Gets the agent's radius
    float GetRadius() const { return radius_; }
    /// Gets the agent's height
    float GetHeight() const { return height_; }
    /// Gets the agent's navigation quality
    NavigationQuality GetNavigationQuality() const {return navQuality_; }
    /// Gets the agent's navigation pushiness
    NavigationPushiness GetNavigationPushiness() const {return navPushiness_; }

    /// Get serialized data of internal state
    PODVector<unsigned char> GetAgentDataAttr() const;
    /// Set serialized data of internal state
    void SetAgentDataAttr(const PODVector<unsigned char>& value);

protected:
    /// Updates the nodes position if updateNodePosition is set. Is called in DetourCrowdManager::Update().
    virtual void OnCrowdAgentReposition(const Vector3& newPos, const Vector3& newDirection);
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// \todo Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);
private:
    /// Create or re-add 
    void AddAgentToCrowd();
    /// Remove 
    void RemoveAgentFromCrowd();

    WeakPtr<DetourCrowdManager> crowdManager_;
    /// in DetourCrowd ? 
    bool inCrowd_;
    /// DetourCrowd reference to this agent.
    int agentCrowdId_;
    /// Reference to poly closest to requested target position.
    unsigned int targetRef_;         
    /// Actual target position, closest to that requested.
    Vector3 targetPosition_;   
    /// update nodes position ?
    bool updateNodePosition_;
    /// Agent's max acceleration.
    float maxAccel_;
    /// Agent's max Velocity.
    float maxSpeed_;
    /// Agent's radius, if 0 the navigation mesh's setting will be used
    float radius_;
    /// Agent's height, if 0 the navigation mesh's setting will be used
    float height_;
    /// Agent's assigned navigation filter type, the actual filter is owned by the DetourCrowdManager the agent belongs to
    unsigned filterType_;
    /// Agent's NavigationAvoidanceQuality
    NavigationQuality navQuality_;
    /// Agent's Navigation Pushiness
    NavigationPushiness navPushiness_;
    /// Ignore transform changes, because it came from us
    bool ignoreTransformChanges_;
};

}
