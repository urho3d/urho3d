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
#include "Protocol.h"
#include "ReplicationState.h"

#include <cstring>

#include "DebugNew.h"

VectorBuffer RevisionBuffer::emptyBaseRevision;

void RevisionBuffer::PurgeOld(unsigned short frameNumber)
{
    // Remove revisions which are older than last ack, but make sure at least 1 revision remains
    if (!revisions_.size())
        return;
    
    unsigned eraseCount = 0;
    for (std::vector<Revision>::iterator i = revisions_.begin(); (i != revisions_.end() - 1) &&
        (revisions_.size() - eraseCount > 1); ++i)
    {
        // If oldest and second-oldest are both older than framenumber, or if the second-oldest is on the exact same frame,
        // can delete the oldest
        std::vector<Revision>::iterator j = i + 1;
        if ((j->frameNumber_ == frameNumber) || ((!CheckFrameNumber(i->frameNumber_, frameNumber)) &&
            (!CheckFrameNumber(j->frameNumber_, frameNumber))))
            eraseCount++;
        else
            break;
    }
    
    if (eraseCount)
    {
        revisions_.erase(revisions_.begin(), revisions_.begin() + eraseCount);
        
        // Move the data and datapointers
        unsigned delta = revisions_[0].offset_;
        void* src = GetModifiableData() + delta;
        void* dest = GetModifiableData();
        memmove(dest, src, GetSize() - delta);
        Resize(GetSize() - delta);
        
        for (std::vector<Revision>::iterator i = revisions_.begin(); i != revisions_.end(); ++i)
            i->offset_ -= delta;
    }
}

bool RevisionBuffer::HasUnAcked(unsigned short frameNumber) const
{
    for (std::vector<Revision>::const_iterator i = revisions_.begin(); i != revisions_.end(); ++i)
    {
        if (CheckFrameNumber(i->frameNumber_, frameNumber, false))
            return true;
    }
    
    return false;
}

ComponentReplicationState::ComponentReplicationState() :
    exists_(true),
    createdFrame_(0),
    removedFrame_(0)
{
}

void ComponentReplicationState::Created(unsigned short frameNumber)
{
    exists_ = true;
    createdFrame_ = frameNumber;
    removedFrame_ = 0;
}

void ComponentReplicationState::Removed(unsigned short frameNumber)
{
    exists_ = false;
    createdFrame_ = 0;
    removedFrame_ = frameNumber;
    
    // Clear revisions in case this component gets recreated
    revisions_.Clear();
}

void ComponentReplicationState::Acked(unsigned short lastAck)
{
    // If ack is newer or same age than the creation or removal event, reset it
    if ((createdFrame_) && (CheckFrameNumber(lastAck, createdFrame_)))
        createdFrame_ = 0;
    if ((removedFrame_) && (CheckFrameNumber(lastAck, removedFrame_)))
        removedFrame_ = 0;
    
    // Remove old data revisions
    revisions_.PurgeOld(lastAck);
}

bool ComponentReplicationState::CanRemove() const
{
    // Can be removed from the replication state if no longer exists, and the remove has been acked
    return (!exists_) && (!removedFrame_);
}

NodeReplicationState::NodeReplicationState() :
    exists_(true),
    createdFrame_(0),
    removedFrame_(0),
    stayRelevantTime_(0)
{
}

void NodeReplicationState::Created(unsigned short frameNumber)
{
    exists_ = true;
    createdFrame_ = frameNumber;
    removedFrame_ = 0;
}

void NodeReplicationState::Removed(unsigned short frameNumber)
{
    exists_ = false;
    createdFrame_ = 0;
    removedFrame_ = frameNumber;
    
    // Clear property revisions & components in case this node gets recreated
    revisions_.Clear();
    components_.clear();
}

void NodeReplicationState::Acked(unsigned short lastAck)
{
    // If ack is newer or same age than the creation or removal event, reset it
    if ((createdFrame_) && (CheckFrameNumber(lastAck, createdFrame_)))
        createdFrame_ = 0;
    if ((removedFrame_) && (CheckFrameNumber(lastAck, removedFrame_)))
        removedFrame_ = 0;
    
    // Remove old property revisions
    revisions_.PurgeOld(lastAck);
    
    // Ack each component and remove if necessary
    for (std::map<ShortStringHash, ComponentReplicationState>::iterator j = components_.begin(); j != components_.end();)
    {
        std::map<ShortStringHash, ComponentReplicationState>::iterator component = j;
        ++j;
        
        component->second.Acked(lastAck);
        if (component->second.CanRemove())
            components_.erase(component);
    }
}

bool NodeReplicationState::HasUnAcked(unsigned short frameNumber) const
{
    if (revisions_.HasUnAcked(frameNumber))
        return true;
    
    for (std::map<ShortStringHash, ComponentReplicationState>::const_iterator i = components_.begin(); i != components_.end(); ++i)
    {
        if (i->second.revisions_.HasUnAcked(frameNumber))
            return true;
    }
    
    return false;
}

bool NodeReplicationState::CanRemove() const
{
    // Can be removed from the replication state if no longer exists, and the remove has been acked
    return (!exists_) && (!removedFrame_);
}

unsigned NodeReplicationState::GetRevisionCount() const
{
    // Return the highest of property revisions and component revisions
    int maxRevisions = revisions_.GetCount();
    
    for (std::map<ShortStringHash, ComponentReplicationState>::const_iterator i = components_.begin(); i != components_.end(); ++i)
        maxRevisions = Max((int)maxRevisions, (int)i->second.GetRevisionCount());
    
    return maxRevisions;
}

void SceneReplicationState::Clear()
{
    nodes_.clear();
}

void SceneReplicationState::Acked(unsigned short lastAck)
{
    // Ack each node and remove if necessary
    for (std::map<unsigned, NodeReplicationState>::iterator i = nodes_.begin(); i != nodes_.end();)
    {
        std::map<unsigned, NodeReplicationState>::iterator node = i;
        ++i;
        
        node->second.Acked(lastAck);
        if (node->second.CanRemove())
            nodes_.erase(node);
    }
}

unsigned SceneReplicationState::GetRevisionCount() const
{
    // Get the highest revision count of all nodes;
    int maxRevisions = 0;
    
    for (std::map<unsigned, NodeReplicationState>::const_iterator i = nodes_.begin(); i != nodes_.end(); ++i)
        maxRevisions = Max((int)maxRevisions, (int)i->second.GetRevisionCount());
    
    return maxRevisions;
}
