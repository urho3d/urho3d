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

#ifndef SCENE_REPLICATIONSTATE_H
#define SCENE_REPLICATIONSTATE_H

#include "Entity.h"
#include "VectorBuffer.h"

#include <list>

//! A revision in the buffer
struct Revision
{
    //! Frame number stored on
    unsigned short mFrameNumber;
    //! Offset in buffer
    unsigned mOffset;
};

//! A buffer that can store several data revisions
class RevisionBuffer : public VectorBuffer
{
public:
    //! Return oldest revision
    Deserializer& getBase()
    {
        static VectorBuffer emptyBaseRevision;
        if (mRevisions.empty())
            return emptyBaseRevision;
        else
        {
            seek(mRevisions[0].mOffset);
            return *this;
        }
    }
    
    //! Commit a revision
    void commit(unsigned short frameNumber, VectorBuffer& data)
    {
        // Do not make zero-length commits
        if (!data.getPosition())
            return;
        
        Revision newRevision;
        newRevision.mFrameNumber = frameNumber;
        newRevision.mOffset = getSize();
        seek(newRevision.mOffset);
        
        // Note: write only up to source's current position, so that can use seek() instead of resize() to write multiple commits
        // to the same buffer
        write(data.getData(), data.getPosition());
        mRevisions.push_back(newRevision);
    }
    
    //! Clear revisions
    void clear()
    {
        VectorBuffer::clear();
        mRevisions.clear();
    }
    
    //! Purge revisions that are older than frame
    void purgeOld(unsigned short frameNumber);
    
    //! Return whether has unacked revisions newer than frame
    bool hasUnacked(unsigned short frameNumber) const;
    //! Return number of revisions
    unsigned getCount() const { return mRevisions.size(); }
    
private:
    //! Revision information
    std::vector<Revision> mRevisions;
};

//! Per-client component state for delta updates
class ComponentReplicationState
{
public:
    //! Construct
    ComponentReplicationState();
    
    //! Mark that component was created
    void created(unsigned short frameNumber);
    //! Mark that component was removed
    void removed(unsigned short frameNumber);
    //! Mark that client acked state up to a specific frame
    void acked(unsigned short lastAck);
    //! Return whether exists currently
    bool exists() const { return mExists; }
    //! Return whether has no unsent changes and can be removed
    bool canRemove() const;
    //! Return number of revisions
    unsigned getRevisionCount() const { return mRevisions.getCount(); }
    
    //! Exists flag
    bool mExists;
    //! Frame number was created on
    unsigned short mCreatedFrame;
    //! Frame number was removed on
    unsigned short mRemovedFrame;
    //! Stored state revisions
    RevisionBuffer mRevisions;
};

//! Per-client entity state for delta updates
class EntityReplicationState
{
public:
    //! Construct
    EntityReplicationState();
    
    //! Return per-client state for a component, or null if not found
    ComponentReplicationState* findComponent(ShortStringHash combinedHash)
    {
        std::map<ShortStringHash, ComponentReplicationState>::iterator i = mComponents.find(combinedHash);
        if (i != mComponents.end())
            return &i->second;
        else
            return 0;
    }
    
    //! Mark that entity was created
    void created(unsigned short frameNumber);
    //! Mark that entity was removed
    void removed(unsigned short frameNumber);
    //! Mark that client acked state up to a specific frame
    void acked(unsigned short lastAck);
    //! Return whether entity exists currently
    bool exists() const { return mExists; }
    //! Return whether has unacked state newer than frame
    bool hasUnacked(unsigned short frameNumber) const;
    //! Return whether has no unsent changes and can be removed
    bool canRemove() const;
    //! Return highest number of revisions between properties and components
    unsigned getRevisionCount() const;
    
    //! Exists flag
    bool mExists;
    //! Frame number was created on
    unsigned short mCreatedFrame;
    //! Frame number was removed on
    unsigned short mRemovedFrame;
    //! Relevancy time counter in server frames
    int mStayRelevantTime;
    //! Stored property revisions
    RevisionBuffer mPropertyRevisions;
    //! Component states
    std::map<ShortStringHash, ComponentReplicationState> mComponents;
};

//! Per-client scene state for delta updates
class SceneReplicationState
{
public:
    //! Return per-client state for an entity, or null if not found
    EntityReplicationState* findEntity(EntityID id)
    {
        std::map<EntityID, EntityReplicationState>::iterator i = mEntities.find(id);
        if (i != mEntities.end())
            return &(i->second);
        else
            return 0;
    }
    
    //! Clear all stored state
    void clear();
    //! Mark that client acked state up to a specific frame
    void acked(unsigned short lastAck);
    //! Return highest number of revisions between all entities
    unsigned getRevisionCount() const;
    
    //! Entity states
    std::map<EntityID, EntityReplicationState> mEntities;
};

#endif // SCENE_REPLICATIONSTATE_H
