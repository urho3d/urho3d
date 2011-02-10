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

#ifndef ENGINE_CONNECTION_H
#define ENGINE_CONNECTION_H

#include "Controls.h"
#include "Peer.h"
#include "RemoteEvent.h"
#include "ReplicationState.h"
#include "SharedPtr.h"
#include "Timer.h"

class Scene;

static const int KEY_LENGTH = 256;

//! Client's scene join state
enum JoinState
{
    JS_NOTINSCENE = 0,
    JS_PREPARESCENE,
    JS_LOADSCENE,
    JS_SENDFULLUPDATE,
    JS_WAITFORACK,
    JS_SENDDELTAS
};

//! A remote connection in the high-level networking protocol
class Connection : public RefCounted, public EventListener
{
public:
    //! Construct with a pointer to the network peer
    Connection(Peer* peer);
    //! Destruct
    virtual ~Connection();
    
    //! Send a packet on the reliable channel
    void sendReliable(const VectorBuffer& packet);
    //! Send a packet on the unreliable channel
    void sendUnreliable(const VectorBuffer& packet);
    //! Attempt to receive a packet on the reliable channel. Return true if a packet was received
    bool receiveReliable(VectorBuffer& packet);
    //! Attempt to receive a packet on the unreliable channel. Return true if a packet was received
    bool receiveUnreliable(VectorBuffer& packet);
    //! Disconnect
    void disconnect();
    //! Disconnect immediately
    void forceDisconnect();
    //! Set scene
    void setScene(Scene* scene);
    //! Joined scene
    void joinedScene();
    //! Left scene
    void leftScene();
    //! Set username
    void setUserName(const std::string& userName);
    //! Set server challenge value
    void setChallenge(unsigned challenge);
    //! Set client's join state
    void setJoinState(JoinState state);
    //! Set remote frame number and last acked local frame number
    void setFrameNumbers(unsigned short frameNumber, unsigned short frameAck);
    //! Set client controls
    void setControls(const Controls& controls);
    //! Set client position for entity relevancy calculations
    void setPosition(const Vector3& position);
    //! Queue a remote event to be sent
    void addRemoteEvent(const RemoteEvent& remoteEvent);
    //! Check if a received remote event should be dispatched, or if it was dispatched already
    bool checkRemoteEventFrame(const RemoteEvent& remoteEvent, unsigned short previousEventFrameNumber);
    //! Add unacked controls to be used in client-side prediction
    void addUnackedControls(unsigned short frameNumber, const Controls& controls);
    //! Remove scene revisions the client has already received
    void purgeAckedSceneState();
    //! Remove controls the server has already received
    void purgeAckedControls();
    //! Remove events the remote end has already received
    void purgeAckedRemoteEvents(unsigned short frameNumber);
    //! Remove all scene revision data
    void clearSceneState();
    //! Remove all remote events
    void clearRemoteEvents();
    //! Check if a response to the challenge (sent in each reliable client packet) is right
    bool checkResponse(unsigned response);
    //! Update the response for the next reliable client packet
    void updateResponse();
    //! Update the round trip time using a smoothed average
    void updateRoundTripTime(int netFps, unsigned short frameNumber);
    
    //! Return network peer
    Peer* getPeer() const { return mPeer; }
    //! Return scene the client has joined, if any
    Scene* getScene() const { return mScene; }
    //! Return username
    const std::string& getUserName() const { return mUserName; }
    //! Return challenge value
    unsigned getChallenge() const { return mChallenge; }
    //! Return response value
    unsigned getResponse() const { return mResponse; }
    //! Return whether connected
    bool isConnected() const;
    //! Return whether a challenge has been assigned
    bool hasChallenge() const { return mHasChallenge; }
    //! Return the client's scene join state
    JoinState getJoinState() const { return mJoinState; }
    //! Return the remote frame number
    unsigned short getFrameNumber() const { return mFrameNumber; }
    //! Return the last acked local frame number
    unsigned short getFrameAck() const { return mFrameNumber; }
    //! Return the last processed remote event frame number
    unsigned short getEventFrameNumber() const { return mEventFrameNumber; }
    //! Return the current estimated round trip time
    float getRoundTripTime() const { return mRoundTripTime; }
    //! Return client controls
    const Controls& getControls() { return mControls; }
    //! Return client position
    const Vector3& getPosition() { return mPosition; }
    //! Return unacked remote events
    std::vector<RemoteEvent>& getUnackedRemoteEvents() { return mRemoteEvents; }
    //! Return unacked controls
    std::vector<std::pair<unsigned short, Controls> >& getUnackedControls() { return mUnackedControls; }
    //! Return unacked scene revisions
    SceneReplicationState& getSceneState() { return mSceneState; }
    
    //! Challenge/response initialization hash
    static const StringHash sHashInit;
    //! Challenge/response update hash
    static const StringHash sHashUpdate;
    
private:
    //! Send a packet
    void send(const VectorBuffer& packet, bool reliable);
    //! Return a packet
    bool receive(VectorBuffer& packet, bool reliable);
    
    //! Network peer
    SharedPtr<Peer> mPeer;
    //! Scene
    SharedPtr<Scene> mScene;
    //! Username
    std::string mUserName;
    //! Challenge value
    unsigned mChallenge;
    //! Response value
    unsigned mResponse;
    //! Challenge assigned flag
    bool mHasChallenge;
    //! Remote frame number
    unsigned short mFrameNumber;
    //! Last acked local frame number
    unsigned short mFrameAck;
    //! Last processed remote event frame number
    unsigned short mEventFrameNumber;
    //! Current estimated round trip time
    float mRoundTripTime;
    //! Client's scene join state
    JoinState mJoinState;
    //! Client controls
    Controls mControls;
    //! Client position
    Vector3 mPosition;
    //! Remote events currently being sent
    std::vector<RemoteEvent> mRemoteEvents;
    //! Unacked controls
    std::vector<std::pair<unsigned short, Controls> > mUnackedControls;
    //! Unacked scene revisions
    SceneReplicationState mSceneState;
};

#endif // ENGINE_CONNECTION_H
