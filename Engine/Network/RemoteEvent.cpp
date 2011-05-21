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
#include "Scene.h"

#include "Set.h"

#include "DebugNew.h"

void RemoteEvent::Write(Serializer& dest) const
{
    dest.WriteUShort(frameNumber_);
    if (nodeID_)
        WriteNetID(dest, nodeID_);
    dest.WriteStringHash(eventType_);
    dest.WriteVariantMap(eventData_);
}

void RemoteEvent::Read(Deserializer& source, bool hasEntity)
{
    frameNumber_ = source.ReadUShort();
    if (hasEntity)
        nodeID_ = ReadNetID(source);
    else
        nodeID_ = 0;
    eventType_ = source.ReadStringHash();
    eventData_ = source.ReadVariantMap();
}

bool RemoteEvent::Dispatch(Connection* sender, Scene* scene)
{
    if ((!sender) || (!scene))
        return false;
    
    /// \todo Add fixed blacklist check for event type, so that it is not an internal engine event
    if (!nodeID_)
        sender->SendEvent(eventType_, eventData_);
    else
    {
        Node* node = scene->GetNodeByID(nodeID_);
        if (!node)
            return false;
        else
            sender->SendEvent(node, eventType_, eventData_);
    }
    return true;
}
