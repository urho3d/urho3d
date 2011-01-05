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
#include "Hash.h"
#include "Log.h"
#include "Protocol.h"
#include "ProtocolEvents.h"
#include "ReplicationUtils.h"
#include "Scene.h"

#include "DebugNew.h"

// Initialization & update hashes for challenge/response
const StringHash Connection::sHashInit("Fish in the Dark");
const StringHash Connection::sHashUpdate("The Dark Side of Fish");

static const float RTT_LERP_FACTOR = 0.1f;

Connection::Connection(Peer* peer) :
    mPeer(peer),
    mFrameNumber(0),
    mFrameAck(0),
    mEventFrameNumber(0),
    mRoundTripTime(0.0f),
    mChallenge(0),
    mResponse(0),
    mHasChallenge(false),
    mJoinState(JS_NOTINSCENE),
    mPosition(Vector3::sZero)
{
    if (!peer)
        EXCEPTION("Null networking peer for Connection");
}

Connection::~Connection()
{
    // Make sure any references in the scene are cleared
    leftScene();
}

void Connection::sendReliable(const VectorBuffer& packet)
{
    send(packet, true);
}

void Connection::sendUnreliable(const VectorBuffer& packet)
{
    send(packet, false);
}

bool Connection::receiveReliable(VectorBuffer& packet)
{
    return receive(packet, true);
}

bool Connection::receiveUnreliable(VectorBuffer& packet)
{
    return receive(packet, false);
}

void Connection::disconnect()
{
    leftScene();
    mPeer->disconnect();
}

void Connection::forceDisconnect()
{
    leftScene();
    mPeer->forceDisconnect();
}

void Connection::setUserName(const std::string& userName)
{
    mUserName = userName;
}

void Connection::setScene(Scene* scene)
{
    // Leave previous scene first
    if ((mScene) && (mScene != scene))
        leftScene();
    
    mScene = scene;
    mJoinState = JS_PREPARESCENE;
    
    // Client: set the proxy flag to the scene
    if (mPeer->getType() == PEER_SERVER)
        mScene->setNetFlags(NET_PROXY);
}

void Connection::joinedScene()
{
    if (!mScene)
        return;
    
    if (mScene->isAuthority())
    {
        // Server: send event, so that game-specific code may create the player entity/entities
        using namespace ClientJoinedScene;
        
        VariantMap eventData;
        eventData[P_CONNECTION] = (void*)this;
        eventData[P_SCENE] = (void*)mScene.getPtr();
        sendEvent(EVENT_CLIENTJOINEDSCENE, eventData);
        
        LOGINFO("Client " + mUserName + " joined scene " + mScene->getName());
    }
    
    mJoinState = JS_SENDFULLUPDATE;
}

void Connection::leftScene()
{
    if (mScene)
    {
        if (mScene->isAuthority())
        {
            // Server: send event so that game-specific code may remove the player entity/entities
            using namespace ClientLeftScene;
            
            VariantMap eventData;
            eventData[P_CONNECTION] = (void*)this;
            eventData[P_SCENE] = (void*)mScene.getPtr();
            sendEvent(EVENT_CLIENTLEFTSCENE, eventData);
            
            LOGINFO("Client " + getUserName() + " left scene " + mScene->getName());
        }
        
        // Remove owner reference from any entities
        mScene->resetOwner(this);
        
        // Reset the client proxy flag if set (scene can now be reused as singleplayer again)
        if (mScene->isProxy())
        {
            mScene->setNetFlags(NET_NONE);
            mScene->removeAllEntities();
        }
    }
    
    mScene.reset();
    mRemoteEvents.clear();
    mSceneState.clear();
    mJoinState = JS_NOTINSCENE;
}

void Connection::setChallenge(unsigned challenge)
{
    mResponse = mChallenge = challenge;
    mHasChallenge = true;
}

void Connection::setJoinState(JoinState state)
{
    mJoinState = state;
}

void Connection::setFrameNumbers(unsigned short frameNumber, unsigned short frameAck)
{
    mFrameNumber = frameNumber;
    mFrameAck = frameAck;
}

void Connection::updateRoundTripTime(int netFps, unsigned short frameNumber)
{
    unsigned short frameDiff = frameNumber - mFrameAck;
    if (frameDiff >= 0x8000)
        frameDiff = mFrameAck - frameNumber;
    
    float newRtt = (1.0f / netFps) * frameDiff;
    mRoundTripTime = lerp(mRoundTripTime, newRtt, RTT_LERP_FACTOR);
}

void Connection::setControls(const Controls& controls)
{
    mControls = controls;
}

void Connection::setPosition(const Vector3& position)
{
    mPosition = position;
}

void Connection::addRemoteEvent(const RemoteEvent& remoteEvent)
{
    mRemoteEvents.push_back(remoteEvent);
}

bool Connection::checkRemoteEventFrame(const RemoteEvent& remoteEvent, unsigned short previousEventFrameNumber)
{
    // Check against previous event framenumber, and update current
    if (!checkFrameNumber(remoteEvent.mFrameNumber, previousEventFrameNumber, false))
        return false;
    if (checkFrameNumber(remoteEvent.mFrameNumber, mEventFrameNumber))
        mEventFrameNumber = remoteEvent.mFrameNumber;
    return true;
}

void Connection::addUnackedControls(unsigned short frameNumber, const Controls& controls)
{
    mUnackedControls.push_back(std::make_pair(frameNumber, controls));
}

void Connection::purgeAckedSceneState()
{
    mSceneState.acked(mFrameAck);
}

void Connection::purgeAckedControls()
{
    for (std::vector<std::pair<unsigned short, Controls> >::iterator i = mUnackedControls.begin(); i != mUnackedControls.end();)
    {
        if (!checkFrameNumber(i->first, mFrameAck, true))
            i = mUnackedControls.erase(i);
        else
            ++i;
    }
}

void Connection::purgeAckedRemoteEvents(unsigned short frameNumber)
{
    for (std::vector<RemoteEvent>::iterator i = mRemoteEvents.begin(); i != mRemoteEvents.end();)
    {
        bool erase = false;
        
        if (!checkFrameNumber(i->mFrameNumber, mFrameAck, false))
            erase = true;
        else if (i->mTimeToLive)
        {
            unsigned short expiryFrameNumber = i->mFrameNumber + i->mTimeToLive;
            if (!expiryFrameNumber)
                ++expiryFrameNumber;
            if (!checkFrameNumber(expiryFrameNumber, frameNumber))
                erase = true;
        }
        
        if (erase)
            i = mRemoteEvents.erase(i);
        else
            ++i;
    }
}

void Connection::clearSceneState()
{
    mSceneState.clear();
}

void Connection::clearRemoteEvents()
{
    mRemoteEvents.clear();
}

bool Connection::checkResponse(unsigned response)
{
    if (mResponse != response)
        return false;
    
    // Expect the next response next time
    updateResponse();
    return true;
}

void Connection::updateResponse()
{
    unsigned char value = (mResponse ^ mChallenge ^ sHashUpdate.mData);
    updateHash(mResponse, value);
}

bool Connection::isConnected() const
{
    return mPeer->getConnectionState() == CS_CONNECTED;
}

void Connection::send(const VectorBuffer& packet, bool reliable)
{
    if ((packet.getSize()) && (mPeer->getConnectionState() == CS_CONNECTED))
        mPeer->send(packet, reliable ? CHN_RELIABLE : CHN_UNRELIABLE, reliable);
}

bool Connection::receive(VectorBuffer& packet, bool reliable)
{
    if (mPeer->getConnectionState() == CS_CONNECTED)
        return mPeer->receive(packet, reliable ? CHN_RELIABLE : CHN_UNRELIABLE);
    else
    {
        mPeer->flushPackets();
        return false;
    }
}
