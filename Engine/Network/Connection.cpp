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

#include "Precompiled.h"
#include "Connection.h"
#include "Log.h"
#include "Protocol.h"
#include "ProtocolEvents.h"
#include "Scene.h"

#include "DebugNew.h"

static const float RTT_LERP_FACTOR = 0.1f;

OBJECTTYPESTATIC(Connection);

Connection::Connection(Context* context, Peer* peer) :
    Object(context),
    peer_(peer),
    frameNumber_(0),
    frameAck_(0),
    eventFrameNumber_(0),
    roundTripTime_(0.0f),
    challenge_(0),
    hasChallenge_(false),
    joinState_(JS_NOTINSCENE),
    position_(Vector3::ZERO)
{
}

Connection::~Connection()
{
    // Make sure any references in the scene are cleared
    LeftScene();
}

void Connection::SendReliable(const VectorBuffer& packet)
{
    Send(packet, true);
}

void Connection::SendUnreliable(const VectorBuffer& packet)
{
    Send(packet, false);
}

bool Connection::ReceiveReliable(VectorBuffer& packet)
{
    return Receive(packet, true);
}

bool Connection::ReceiveUnreliable(VectorBuffer& packet)
{
    return Receive(packet, false);
}

void Connection::Disconnect()
{
    LeftScene();
    peer_->Disconnect();
}

void Connection::forceDisconnect()
{
    LeftScene();
    peer_->ForceDisconnect();
}

void Connection::SetLoginData(const VariantMap& loginData)
{
    loginData_ = loginData;
}

void Connection::SetScene(Scene* scene)
{
    // Leave previous scene first
    if (scene_ && scene_ != scene)
        LeftScene();
    
    scene_ = scene;
    joinState_ = JS_PREPARESCENE;
    
    // Client: set the proxy flag to the scene
    if (peer_->GetPeerType() == PEER_SERVER)
        scene_->SetNetworkMode(NM_CLIENT);
}

void Connection::JoinedScene()
{
    if (!scene_)
        return;
    
    if (scene_->GetNetworkMode() == NM_SERVER)
    {
        // Server: send event, so that game-specific code may create the player node/nodes
        using namespace ClientJoinedScene;
        
        VariantMap eventData;
        eventData[P_CONNECTION] = (void*)this;
        eventData[P_SCENE] = (void*)scene_.Ptr();
        SendEvent(E_CLIENTJOINEDSCENE, eventData);
        
        LOGINFO("Client " + GetIdentity() + " joined scene " + scene_->GetName());
    }
    
    joinState_ = JS_SENDFULLUPDATE;
}

void Connection::LeftScene()
{
    if (scene_)
    {
        NetworkMode mode = scene_->GetNetworkMode();
        
        if (mode == NM_SERVER)
        {
            // Server: send event so that game-specific code may remove the player node/nodes
            using namespace ClientLeftScene;
            
            VariantMap eventData;
            eventData[P_CONNECTION] = (void*)this;
            eventData[P_SCENE] = (void*)scene_.Ptr();
            SendEvent(E_CLIENTLEFTSCENE, eventData);
            
            LOGINFO("Client " + GetIdentity() + " left scene " + scene_->GetName());
        }
        
        // Remove owner reference from any nodes
        scene_->ResetOwner(this);
        
        // Reset the client mode if set (scene can now be reused as singleplayer again)
        if (mode == NM_CLIENT)
        {
            scene_->Clear();
            scene_->SetNetworkMode(NM_NONETWORK);
        }
    }
    
    scene_.Reset();
    remoteEvents_.Clear();
    sceneState_.Clear();
    joinState_ = JS_NOTINSCENE;
}

void Connection::SetChallenge(unsigned challenge)
{
    challenge_ = challenge;
    hasChallenge_ = true;
}

void Connection::SetJoinState(JoinState state)
{
    joinState_ = state;
}

void Connection::SetFrameNumbers(unsigned short frameNumber, unsigned short frameAck)
{
    frameNumber_ = frameNumber;
    frameAck_ = frameAck;
}

void Connection::UpdateRoundTripTime(int netFps, unsigned short frameNumber)
{
    unsigned short frameDiff = frameNumber - frameAck_;
    if (frameDiff >= 0x8000)
        frameDiff = frameAck_ - frameNumber;
    
    float newRtt = (1.0f / netFps) * frameDiff;
    roundTripTime_ = Lerp(roundTripTime_, newRtt, RTT_LERP_FACTOR);
}

void Connection::SetControls(const Controls& controls)
{
    controls_ = controls;
}

void Connection::SetPosition(const Vector3& position)
{
    position_ = position;
}

void Connection::addRemoteEvent(const RemoteEvent& remoteEvent)
{
    remoteEvents_.Push(remoteEvent);
}

bool Connection::CheckRemoteEventFrame(const RemoteEvent& remoteEvent, unsigned short previousEventFrameNumber)
{
    // Check against previous event framenumber, and update current
    if (!CheckFrameNumber(remoteEvent.frameNumber_, previousEventFrameNumber, false))
        return false;
    if (CheckFrameNumber(remoteEvent.frameNumber_, eventFrameNumber_))
        eventFrameNumber_ = remoteEvent.frameNumber_;
    return true;
}

void Connection::PurgeAckedSceneState()
{
    sceneState_.Acked(frameAck_);
}

void Connection::PurgeAckedRemoteEvents(unsigned short frameNumber)
{
    for (Vector<RemoteEvent>::Iterator i = remoteEvents_.Begin(); i != remoteEvents_.End();)
    {
        bool erase = false;
        
        if (!CheckFrameNumber(i->frameNumber_, frameAck_, false))
            erase = true;
        else if (i->timeToLive_)
        {
            unsigned short expiryFrameNumber = i->frameNumber_ + i->timeToLive_;
            if (!expiryFrameNumber)
                ++expiryFrameNumber;
            if (!CheckFrameNumber(expiryFrameNumber, frameNumber))
                erase = true;
        }
        
        if (erase)
            i = remoteEvents_.Erase(i);
        else
            ++i;
    }
}

void Connection::ClearSceneState()
{
    sceneState_.Clear();
}

void Connection::ClearRemoteEvents()
{
    remoteEvents_.Clear();
}

String Connection::GetIdentity() const
{
    if (peer_)
        return peer_->GetAddress() + ":" + String(peer_->GetPort());
    else
        return "Unknown";
}

bool Connection::IsConnected() const
{
    return peer_->GetConnectionState() == CS_CONNECTED;
}

void Connection::Send(const VectorBuffer& packet, bool reliable)
{
    if (packet.GetSize() && peer_->GetConnectionState() == CS_CONNECTED)
        peer_->Send(packet, reliable ? CHN_RELIABLE : CHN_UNRELIABLE, reliable);
}

bool Connection::Receive(VectorBuffer& packet, bool reliable)
{
    if (peer_->GetConnectionState() == CS_CONNECTED)
        return peer_->Receive(packet, reliable ? CHN_RELIABLE : CHN_UNRELIABLE);
    else
    {
        peer_->FlushPackets();
        return false;
    }
}
