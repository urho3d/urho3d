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

#include "Object.h"

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
    RemoteEvent(StringHash eventType, const VariantMap& eventData, Connection* receiver, unsigned short timeToLive) :
        nodeID_(0),
        eventType_(eventType),
        eventData_(eventData),
        receiver_(receiver),
        timeToLive_(timeToLive)
    {
    }
    
    //! Construct with target entity and parameters
    RemoteEvent(unsigned nodeID, StringHash eventType, const VariantMap& eventData, Connection* receiver, unsigned short timeToLive) :
        nodeID_(nodeID),
        eventType_(eventType),
        eventData_(eventData),
        receiver_(receiver),
        timeToLive_(timeToLive)
    {
    }
    
    //! Write to a stream
    void Write(Serializer& dest) const;
    //! Read from a stream
    void Read(Deserializer& source, bool hasEntity);
    //! Dispatch at the remote end
    bool Dispatch(Connection* sender, Scene* scene);
    
    //! Frame number
    unsigned short frameNumber_;
    //! Event type
    StringHash eventType_;
    //! Event parameters
    VariantMap eventData_;
    //! Target entity ID
    unsigned nodeID_;
    //! Receiving connection. If null on the server, broadcast to all. On client has no significance
    Connection* receiver_;
    //! Time to live in network frames. If not acked when expires, will no longer be sent. 0 is infinite
    unsigned short timeToLive_;
};

#endif // SCENE_REMOTEEVENT_H
