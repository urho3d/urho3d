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
#include "Log.h"
#include "ReplicationUtils.h"
#include "Scene.h"
#include "StringUtils.h"

#include <set>

#include "DebugNew.h"

static std::set<StringHash> remoteEvents;
Connection* remoteEventSender = 0;

void RemoteEvent::write(Serializer& dest) const
{
    dest.writeUShort(mFrameNumber);
    if (mEntityID)
        dest.writeUInt(mEntityID);
    dest.writeStringHash(mEventType);
    dest.writeVariantMap(mEventData);
}

void RemoteEvent::read(Deserializer& source, bool hasEntity)
{
    mFrameNumber = source.readUShort();
    if (hasEntity)
        mEntityID = source.readUInt();
    else
        mEntityID = 0;
    mEventType = source.readStringHash();
    mEventData = source.readVariantMap();
}

bool RemoteEvent::dispatch(Connection* sender, Scene* scene)
{
    if ((!sender) || (!scene))
        return false;
    
    if (!checkRemoteEvent(mEventType))
    {
        LOGWARNING("Remote event " + toString(mEventType) + " not allowed");
        return false;
    }
    
    // Note: because the Connection object is not known in the Scene library, we must use Scene as the sender
    
    remoteEventSender = sender;
    if (!mEntityID)
        scene->sendEvent(mEventType, mEventData);
    else
    {
        Entity* entity = scene->getEntity(mEntityID);
        if (!entity)
            LOGWARNING("Entity ID " + toString(mEntityID) + " not found for remote event " + toString(mEventType));
        else
            scene->sendEvent(entity, mEventType, mEventData);
    }
    remoteEventSender = 0;
    return true;
}

void registerRemoteEvent(StringHash eventType)
{
    remoteEvents.insert(eventType);
}

void registerRemoteEvent(const std::string& name)
{
    registerHash(name, false);
    remoteEvents.insert(StringHash(name));
}

void unregisterRemoteEvent(StringHash eventType)
{
    remoteEvents.erase(eventType);
}

void unregisterRemoteEvent(const std::string& name)
{
    remoteEvents.erase(StringHash(name));
}

void unregisterAllRemoteEvents()
{
    remoteEvents.clear();
}

bool checkRemoteEvent(StringHash eventType)
{
    return remoteEvents.find(eventType) != remoteEvents.end();
}

Connection* getRemoteEventSender()
{
    return remoteEventSender;
}

