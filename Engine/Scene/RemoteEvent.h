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

#ifndef SCENE_REMOTEEVENT_H
#define SCENE_REMOTEEVENT_H

#include "Entity.h"
#include "Event.h"

class Connection;
class Deserializer;
class Scene;
class Serializer;

//! An event to be sent over the network
struct RemoteEvent
{
    //! Construct as undefined
    RemoteEvent()
    {
    }
    
    //! Construct with parameters
    RemoteEvent(StringHash eventType, const VariantMap& eventData, Connection* receiver, float delay, unsigned short timeToLive) :
        mEntityID(0),
        mEventType(eventType),
        mEventData(eventData),
        mReceiver(receiver),
        mDelay(delay),
        mTimeToLive(timeToLive)
    {
    }
    
    //! Construct with target entity and parameters
    RemoteEvent(EntityID entityID, StringHash eventType, const VariantMap& eventData, Connection* receiver, float delay, unsigned short timeToLive) :
        mEntityID(entityID),
        mEventType(eventType),
        mEventData(eventData),
        mReceiver(receiver),
        mDelay(delay),
        mTimeToLive(timeToLive)
    {
    }
    
    //! Write to a stream
    void write(Serializer& dest) const;
    //! Read from a stream
    void read(Deserializer& source, bool hasEntity);
    //! Dispatch at the remote end
    bool dispatch(Connection* sender, Scene* scene);
    
    //! Frame number
    unsigned short mFrameNumber;
    //! Event type
    StringHash mEventType;
    //! Event parameters
    VariantMap mEventData;
    //! Target entity ID
    EntityID mEntityID;
    //! Receiving connection. If null on the server, broadcast to all. On client has no significance
    Connection* mReceiver;
    //! Delay until sending
    float mDelay;
    //! Time to live in network frames. If not acked when expires, will no longer be sent. 0 is infinite
    unsigned short mTimeToLive;
};

//! Register an event to be only sent locally
void registerLocalOnlyEvent(StringHash eventType);
//! Register an event to be only sent locally
void registerLocalOnlyEvent(const std::string& name);
//! Check if an event is allowed to be sent remotely
bool checkRemoteEvent(StringHash eventType);
//! Return remote event sender connection. Only non-null during the event handling
Connection* getRemoteEventSender();

#endif // SCENE_REMOTEEVENT_H
