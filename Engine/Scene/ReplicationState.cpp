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
#include "ReplicationState.h"
#include "ReplicationUtils.h"

#include <cstring>

#include "DebugNew.h"

void RevisionBuffer::purgeOld(unsigned short frameNumber)
{
    // Remove revisions which are older than last ack, but make sure at least 1 revision remains
    if (!mRevisions.size())
        return;
    
    unsigned eraseCount = 0;
    for (std::vector<Revision>::iterator i = mRevisions.begin(); (i != mRevisions.end() - 1) &&
        (mRevisions.size() - eraseCount > 1); ++i)
    {
        // If oldest and second-oldest are both older than framenumber, or if the second-oldest is on the exact same frame,
        // can delete the oldest
        std::vector<Revision>::iterator j = i + 1;
        if ((j->mFrameNumber == frameNumber) || ((!checkFrameNumber(i->mFrameNumber, frameNumber)) &&
            (!checkFrameNumber(j->mFrameNumber, frameNumber))))
            eraseCount++;
        else
            break;
    }
    
    if (eraseCount)
    {
        mRevisions.erase(mRevisions.begin(), mRevisions.begin() + eraseCount);
        
        // Move the data and datapointers
        unsigned delta = mRevisions[0].mOffset;
        void* src = getModifiableData() + delta;
        void* dest = getModifiableData();
        memmove(dest, src, getSize() - delta);
        resize(getSize() - delta);
        
        for (std::vector<Revision>::iterator i = mRevisions.begin(); i != mRevisions.end(); ++i)
            i->mOffset -= delta;
    }
}

bool RevisionBuffer::hasUnacked(unsigned short frameNumber) const
{
    for (std::vector<Revision>::const_iterator i = mRevisions.begin(); i != mRevisions.end(); ++i)
    {
        if (checkFrameNumber(i->mFrameNumber, frameNumber, false))
            return true;
    }
    
    return false;
}

ComponentReplicationState::ComponentReplicationState() :
    mExists(true),
    mCreatedFrame(0),
    mRemovedFrame(0)
{
}

void ComponentReplicationState::created(unsigned short frameNumber)
{
    mExists = true;
    mCreatedFrame = frameNumber;
    mRemovedFrame = 0;
}

void ComponentReplicationState::removed(unsigned short frameNumber)
{
    mExists = false;
    mCreatedFrame = 0;
    mRemovedFrame = frameNumber;
    
    // Clear revisions in case this component gets recreated
    mRevisions.clear();
}

void ComponentReplicationState::acked(unsigned short lastAck)
{
    // If ack is newer or same age than the creation or removal event, reset it
    if ((mCreatedFrame) && (checkFrameNumber(lastAck, mCreatedFrame)))
        mCreatedFrame = 0;
    if ((mRemovedFrame) && (checkFrameNumber(lastAck, mRemovedFrame)))
        mRemovedFrame = 0;
    
    // Remove old data revisions
    mRevisions.purgeOld(lastAck);
}

bool ComponentReplicationState::canRemove() const
{
    // Can be removed from the replication state if no longer exists, and the remove has been acked
    return (!mExists) && (!mRemovedFrame);
}

EntityReplicationState::EntityReplicationState() :
    mExists(true),
    mCreatedFrame(0),
    mRemovedFrame(0),
    mStayRelevantTime(0)
{
}

void EntityReplicationState::created(unsigned short frameNumber)
{
    mExists = true;
    mCreatedFrame = frameNumber;
    mRemovedFrame = 0;
}

void EntityReplicationState::removed(unsigned short frameNumber)
{
    mExists = false;
    mCreatedFrame = 0;
    mRemovedFrame = frameNumber;
    
    // Clear property revisions & components in case this entity gets recreated
    mPropertyRevisions.clear();
    mComponents.clear();
}

void EntityReplicationState::acked(unsigned short lastAck)
{
    // If ack is newer or same age than the creation or removal event, reset it
    if ((mCreatedFrame) && (checkFrameNumber(lastAck, mCreatedFrame)))
        mCreatedFrame = 0;
    if ((mRemovedFrame) && (checkFrameNumber(lastAck, mRemovedFrame)))
        mRemovedFrame = 0;
    
    // Remove old property revisions
    mPropertyRevisions.purgeOld(lastAck);
    
    // Ack each component and remove if necessary
    for (std::map<ShortStringHash, ComponentReplicationState>::iterator j = mComponents.begin(); j != mComponents.end();)
    {
        std::map<ShortStringHash, ComponentReplicationState>::iterator component = j;
        ++j;
        
        component->second.acked(lastAck);
        if (component->second.canRemove())
            mComponents.erase(component);
    }
}

bool EntityReplicationState::hasUnacked(unsigned short frameNumber) const
{
    if (mPropertyRevisions.hasUnacked(frameNumber))
        return true;
    
    for (std::map<ShortStringHash, ComponentReplicationState>::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
    {
        if (i->second.mRevisions.hasUnacked(frameNumber))
            return true;
    }
    
    return false;
}

bool EntityReplicationState::canRemove() const
{
    // Can be removed from the replication state if no longer exists, and the remove has been acked
    return (!mExists) && (!mRemovedFrame);
}

unsigned EntityReplicationState::getRevisionCount() const
{
    // Return the highest of property revisions and component revisions
    int maxRevisions = mPropertyRevisions.getCount();
    
    for (std::map<ShortStringHash, ComponentReplicationState>::const_iterator i = mComponents.begin(); i != mComponents.end(); ++i)
        maxRevisions = max((int)maxRevisions, (int)i->second.getRevisionCount());
    
    return maxRevisions;
}

void SceneReplicationState::clear()
{
    mEntities.clear();
}

void SceneReplicationState::acked(unsigned short lastAck)
{
    // Ack each entity and remove if necessary
    for (std::map<EntityID, EntityReplicationState>::iterator i = mEntities.begin(); i != mEntities.end();)
    {
        std::map<EntityID, EntityReplicationState>::iterator entity = i;
        ++i;
        
        entity->second.acked(lastAck);
        if (entity->second.canRemove())
            mEntities.erase(entity);
    }
}

unsigned SceneReplicationState::getRevisionCount() const
{
    // Get the highest revision count of all entities;
    int maxRevisions = 0;
    
    for (std::map<EntityID, EntityReplicationState>::const_iterator i = mEntities.begin(); i != mEntities.end(); ++i)
        maxRevisions = max((int)maxRevisions, (int)i->second.getRevisionCount());
    
    return maxRevisions;
}
