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
    if (!revisions_.Size())
        return;
    
    unsigned eraseCount = 0;
    for (Vector<Revision>::Iterator i = revisions_.Begin(); (i != revisions_.End() - 1) &&
        (revisions_.Size() - eraseCount > 1); ++i)
    {
        // If oldest and second-oldest are both older than framenumber, or if the second-oldest is on the exact same frame,
        // can delete the oldest
        Vector<Revision>::Iterator j = i + 1;
        if ((j->frameNumber_ == frameNumber) || ((!CheckFrameNumber(i->frameNumber_, frameNumber)) &&
            (!CheckFrameNumber(j->frameNumber_, frameNumber))))
            eraseCount++;
        else
            break;
    }
    
    if (eraseCount)
    {
        revisions_.Erase(revisions_.Begin(), revisions_.Begin() + eraseCount);
        
        // Move the data and datapointers
        unsigned delta = revisions_[0].offset_;
        void* src = GetModifiableData() + delta;
        void* dest = GetModifiableData();
        memmove(dest, src, GetSize() - delta);
        Resize(GetSize() - delta);
        
        for (Vector<Revision>::Iterator i = revisions_.Begin(); i != revisions_.End(); ++i)
            i->offset_ -= delta;
    }
}

bool RevisionBuffer::HasUnAcked(unsigned short frameNumber) const
{
    for (Vector<Revision>::ConstIterator i = revisions_.Begin(); i != revisions_.End(); ++i)
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
    components_.Clear();
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
    for (Map<ShortStringHash, ComponentReplicationState>::Iterator j = components_.Begin(); j != components_.End();)
    {
        Map<ShortStringHash, ComponentReplicationState>::Iterator component = j;
        ++j;
        
        component->second_.Acked(lastAck);
        if (component->second_.CanRemove())
            components_.Erase(component);
    }
}

bool NodeReplicationState::HasUnAcked(unsigned short frameNumber) const
{
    if (revisions_.HasUnAcked(frameNumber))
        return true;
    
    for (Map<ShortStringHash, ComponentReplicationState>::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
    {
        if (i->second_.revisions_.HasUnAcked(frameNumber))
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
    
    for (Map<ShortStringHash, ComponentReplicationState>::ConstIterator i = components_.Begin(); i != components_.End(); ++i)
        maxRevisions = Max((int)maxRevisions, (int)i->second_.GetRevisionCount());
    
    return maxRevisions;
}

void SceneReplicationState::Clear()
{
    nodes_.Clear();
}

void SceneReplicationState::Acked(unsigned short lastAck)
{
    // Ack each node and remove if necessary
    for (Map<unsigned, NodeReplicationState>::Iterator i = nodes_.Begin(); i != nodes_.End();)
    {
        Map<unsigned, NodeReplicationState>::Iterator node = i;
        ++i;
        
        node->second_.Acked(lastAck);
        if (node->second_.CanRemove())
            nodes_.Erase(node);
    }
}

unsigned SceneReplicationState::GetRevisionCount() const
{
    // Get the highest revision count of all nodes;
    int maxRevisions = 0;
    
    for (Map<unsigned, NodeReplicationState>::ConstIterator i = nodes_.Begin(); i != nodes_.End(); ++i)
        maxRevisions = Max((int)maxRevisions, (int)i->second_.GetRevisionCount());
    
    return maxRevisions;
}
