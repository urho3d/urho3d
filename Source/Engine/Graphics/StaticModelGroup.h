//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "StaticModel.h"

namespace Urho3D
{

/// Renders several instances of static models while culling and receiving light as one unit. Using this class is not necessary for instanced rendering, but can be used as a CPU-side optimization.
class URHO3D_API StaticModelGroup : public StaticModel
{
    OBJECT(StaticModelGroup);
    
public:
    /// Construct.
    StaticModelGroup(Context* context);
    /// Destruct.
    virtual ~StaticModelGroup();
    /// Register object factory. StaticModel must be registered first.
    static void RegisterObject(Context* context);
    
    /// Process octree raycast. May be called from a worker thread.
    //virtual void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results);
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateBatches(const FrameInfo& frame);
    /// Return number of occlusion geometry triangles.
    //virtual unsigned GetNumOccluderTriangles();
    /// Draw to occlusion buffer. Return true if did not run out of triangles.
    //virtual bool DrawOcclusion(OcclusionBuffer* buffer);
    
    /// Add an instance scene node. It does not need any drawable components of its own.
    void AddInstanceNode(Node* node);
    /// Remove an instance scene node.
    void RemoveInstanceNode(Node* node);
    
    /// Return number of instance nodes.
    unsigned GetNumInstanceNodes() const { return instanceNodes_.Size(); }
    /// Return instance node by index.
    Node* GetInstanceNode(unsigned index) const;
    
protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
   /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    
private:
    /// Gather the instances' transforms.
    void UpdateTransforms();
    /// Handle an instance node being enabled/disabled.
    void HandleNodeEnabledChanged(StringHash eventType, VariantMap& eventData);
    
    /// Instance nodes.
    Vector<WeakPtr<Node> > instanceNodes_;
    /// World transforms of enabled instances.
    PODVector<Matrix3x4> worldTransforms_;
    /// Instance transforms dirty flag.
    bool transformsDirty_;
};

}
