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

#pragma once

#include "Node.h"
#include "VectorBuffer.h"

#include <list>

/// A revision in the buffer
struct Revision
{
    /// Frame number stored on
    unsigned short frameNumber_;
    /// Offset in buffer
    unsigned offset_;
};

/// A buffer that can store several data revisions
class RevisionBuffer : public VectorBuffer
{
public:
    /// Return oldest revision
    Deserializer& GetBase()
    {
        if (revisions_.Empty())
            return emptyBaseRevision;
        else
        {
            Seek(revisions_[0].offset_);
            return *this;
        }
    }
    
    /// Commit a revision
    void Commit(unsigned short frameNumber, VectorBuffer& data)
    {
        // Do not make zero-length commits
        if (!data.GetPosition())
            return;
        
        Revision newRevision;
        newRevision.frameNumber_ = frameNumber;
        newRevision.offset_ = GetSize();
        Seek(newRevision.offset_);
        
        // Note: write only up to source's current position, so that can use Seek() instead of resize() to write multiple commits
        // to the same buffer
        Write(data.GetData(), data.GetPosition());
        revisions_.Push(newRevision);
    }
    
    /// Clear revisions
    void Clear()
    {
        VectorBuffer::Clear();
        revisions_.Clear();
    }
    
    /// Purge revisions that are older than frame
    void PurgeOld(unsigned short frameNumber);
    
    /// Return whether has unacked revisions newer than frame
    bool HasUnAcked(unsigned short frameNumber) const;
    /// Return number of revisions
    unsigned GetCount() const { return revisions_.Size(); }
    
private:
    /// Revision information
    PODVector<Revision> revisions_;
    
    /// Empty revision
    static VectorBuffer emptyBaseRevision;
};

/// Per-client component state for delta updates
class ComponentReplicationState
{
public:
    /// Construct
    ComponentReplicationState();
    
    /// Mark that component was created
    void Created(unsigned short frameNumber);
    /// Mark that component was removed
    void Removed(unsigned short frameNumber);
    /// Mark that client acked state up to a specific frame
    void Acked(unsigned short lastAck);
    /// Return whether exists currently
    bool Exists() const { return exists_; }
    /// Return whether has no unsent changes and can be removed
    bool CanRemove() const;
    /// Return number of revisions
    unsigned GetRevisionCount() const { return revisions_.GetCount(); }
    
    /// Exists flag
    bool exists_;
    /// Frame number was created on
    unsigned short createdFrame_;
    /// Frame number was removed on
    unsigned short removedFrame_;
    /// Stored state revisions
    RevisionBuffer revisions_;
};

/// Per-client node state for delta updates
class NodeReplicationState
{
public:
    /// Construct
    NodeReplicationState();
    
    /// Return per-client state for a component, or null if not found
    ComponentReplicationState* FindComponent(ShortStringHash combinedHash)
    {
        Map<ShortStringHash, ComponentReplicationState>::Iterator i = components_.Find(combinedHash);
        if (i != components_.End())
            return &i->second_;
        else
            return 0;
    }
    
    /// Mark that node was created
    void Created(unsigned short frameNumber);
    /// Mark that node was removed
    void Removed(unsigned short frameNumber);
    /// Mark that client acked state up to a specific frame
    void Acked(unsigned short lastAck);
    /// Return whether node exists currently
    bool Exists() const { return exists_; }
    /// Return whether has unacked state newer than frame
    bool HasUnAcked(unsigned short frameNumber) const;
    /// Return whether has no unsent changes and can be removed
    bool CanRemove() const;
    /// Return highest number of state revisions
    unsigned GetRevisionCount() const;
    
    /// Exists flag
    bool exists_;
    /// Frame number was created on
    unsigned short createdFrame_;
    /// Frame number was removed on
    unsigned short removedFrame_;
    /// Relevancy time counter in server frames
    int stayRelevantTime_;
    /// Stored state revisions
    RevisionBuffer revisions_;
    /// Component states
    Map<ShortStringHash, ComponentReplicationState> components_;
};

/// Per-client scene state for delta updates
class SceneReplicationState
{
public:
    /// Return per-client state for an node, or null if not found
    NodeReplicationState* FindNode(unsigned id)
    {
        Map<unsigned, NodeReplicationState>::Iterator i = nodes_.Find(id);
        if (i != nodes_.End())
            return &(i->second_);
        else
            return 0;
    }
    
    /// Clear all stored state
    void Clear();
    /// Mark that client acked state up to a specific frame
    void Acked(unsigned short lastAck);
    /// Return highest number of revisions between all nodes
    unsigned GetRevisionCount() const;
    
    /// Node states
    Map<unsigned, NodeReplicationState> nodes_;
};
