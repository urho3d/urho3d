//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Controls.h"
#include "Peer.h"
#include "RemoteEvent.h"
#include "ReplicationState.h"
#include "Timer.h"

class Scene;

static const int KEY_LENGTH = 256;

/// Client's scene join state
enum JoinState
{
    JS_NOTINSCENE = 0,
    JS_PREPARESCENE,
    JS_LOADSCENE,
    JS_SENDFULLUPDATE,
    JS_WAITFORACK,
    JS_SENDDELTAS
};

/// Multiplayer protocol connection
class Connection : public Object
{
    OBJECT(Connection);
    
public:
    /// Construct
    Connection(Context* context, Peer* peer);
    /// Destruct
    virtual ~Connection();
    
    /// Send a packet on the reliable channel
    void SendReliable(const VectorBuffer& packet);
    /// Send a packet on the unreliable channel
    void SendUnreliable(const VectorBuffer& packet);
    /// Attempt to receive a packet on the reliable channel. Return true if a packet was received
    bool ReceiveReliable(VectorBuffer& packet);
    /// Attempt to receive a packet on the unreliable channel. Return true if a packet was received
    bool ReceiveUnreliable(VectorBuffer& packet);
    /// Disconnect
    void Disconnect();
    /// Disconnect immediately
    void forceDisconnect();
    /// Set scene
    void SetScene(Scene* scene);
    /// Joined scene
    void JoinedScene();
    /// Left scene
    void LeftScene();
    /// Set login data
    void SetLoginData(const VariantMap& loginData);
    /// Set server challenge value
    void SetChallenge(unsigned challenge);
    /// Set client's join state
    void SetJoinState(JoinState state);
    /// Set remote frame number and last acked local frame number
    void SetFrameNumbers(unsigned short frameNumber, unsigned short frameAck);
    /// Set client controls
    void SetControls(const Controls& controls);
    /// Set client position for node relevancy calculations
    void SetPosition(const Vector3& position);
    /// Queue a remote event to be sent
    void addRemoteEvent(const RemoteEvent& remoteEvent);
    /// Check if a received remote event should be dispatched, or if it was dispatched already
    bool CheckRemoteEventFrame(const RemoteEvent& remoteEvent, unsigned short previousEventFrameNumber);
    /// Add unacked controls for possible client-side prediction / replay
    void AddUnackedControls(unsigned short frameNumber, const Controls& controls);
    /// Remove scene revisions the client has already received
    void PurgeAckedSceneState();
    //! Remove controls the server has already received
    void PurgeAckedControls();
    /// Remove events the remote end has already received
    void PurgeAckedRemoteEvents(unsigned short frameNumber);
    /// Remove all scene revision data
    void ClearSceneState();
    /// Remove all remote events
    void ClearRemoteEvents();
    /// Update the round trip time using a smoothed average
    void UpdateRoundTripTime(int netFps, unsigned short frameNumber);
    
    /// Return network peer
    Peer* GetPeer() const { return peer_; }
    /// Return scene the client has joined, if any
    Scene* GetScene() const { return scene_; }
    /// Return identity string (address:port)
    String GetIdentity() const;
    /// Return login data
    const VariantMap& GetLoginData() const { return loginData_; }
    /// Return challenge value
    unsigned GetChallenge() const { return challenge_; }
    /// Return whether connected
    bool IsConnected() const;
    /// Return whether a challenge has been assigned
    bool HasChallenge() const { return hasChallenge_; }
    /// Return the client's scene join state
    JoinState GetJoinState() const { return joinState_; }
    /// Return the remote frame number
    unsigned short GetFrameNumber() const { return frameNumber_; }
    /// Return the last acked local frame number
    unsigned short GetFrameAck() const { return frameNumber_; }
    /// Return the last processed remote event frame number
    unsigned short GetEventFrameNumber() const { return eventFrameNumber_; }
    /// Return the current estimated round trip time
    float GetRoundTripTime() const { return roundTripTime_; }
    /// Return client controls
    const Controls& GetControls() { return controls_; }
    /// Return client position
    const Vector3& GetPosition() { return position_; }
    /// Return unacked remote events
    Vector<RemoteEvent>& GetUnackedRemoteEvents() { return remoteEvents_; }
    /// Return unacked controls
    Vector<Pair<unsigned short, Controls> >& GetUnackedControls() { return unackedControls_; }
    /// Return unacked scene revisions
    SceneReplicationState& GetSceneState() { return sceneState_; }
    
private:
    /// Send a packet
    void Send(const VectorBuffer& packet, bool reliable);
    /// Return a packet
    bool Receive(VectorBuffer& packet, bool reliable);
    
    /// Network peer
    SharedPtr<Peer> peer_;
    /// Scene
    SharedPtr<Scene> scene_;
    /// Login data
    VariantMap loginData_;
    /// Challenge value
    unsigned challenge_;
    /// Challenge assigned flag
    bool hasChallenge_;
    /// Remote frame number
    unsigned short frameNumber_;
    /// Last acked local frame number
    unsigned short frameAck_;
    /// Last processed remote event frame number
    unsigned short eventFrameNumber_;
    /// Current estimated round trip time
    float roundTripTime_;
    /// Client's scene join state
    JoinState joinState_;
    /// Client controls
    Controls controls_;
    /// Client position
    Vector3 position_;
    /// Remote events currently being sent
    Vector<RemoteEvent> remoteEvents_;
    //! Unacked controls
    Vector<Pair<unsigned short, Controls> > unackedControls_;
    /// Unacked scene revisions
    SceneReplicationState sceneState_;
};
