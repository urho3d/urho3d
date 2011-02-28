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

#ifndef RENDERER_OCTREE_H
#define RENDERER_OCTREE_H

#include "SceneExtension.h"
#include "VolumeNode.h"

#include <set>

class Octree;
class OctreeQuery;
class RayOctreeQuery;

static const unsigned NUM_OCTANTS = 8;

//! Octree octant
class Octant
{
public:
    //! Construct
    Octant(const BoundingBox& box, unsigned level, Octant* parent, Octree* root);
    //! Destruct. Move scene nodes to root if available (detach if not) and free child octants
    virtual ~Octant();
    
    //! Return or create a child octant
    Octant* getOrCreateChild(unsigned index);
    //! Delete child octant
    void deleteChild(unsigned index);
    //! Delete child octant by pointer
    void deleteChild(Octant* octant);
    //! Insert scene node by checking for fit recursively
    void insertNode(VolumeNode* node);
    //! Check if scene node fits
    bool checkNodeSize(VolumeNode* node) const;
    
    //! Add scene node to this octant
    void addNode(VolumeNode* node)
    {
        node->mOctant = this;
        mNodes.push_back(node);
        incNodeCount();
    }
    
    //! Remove scene node from this octant
    void removeNode(VolumeNode* node)
    {
        for (std::vector<VolumeNode*>::iterator i = mNodes.begin(); i != mNodes.end(); ++i)
        {
            if (*i == node)
            {
                node->mOctant = 0;
                mNodes.erase(i);
                decNodeCount();
                return;
            }
        }
    }
    
    //! Return world bounding box
    const BoundingBox& getWorldBoundingBox() const { return mWorldBoundingBox; }
    //! Return bounding box used for fitting nodes
    const BoundingBox& getCullingBox() const { return mCullingBox; }
    //! Return subdivision level
    unsigned getLevel() const { return mLevel; }
    //! Return parent octant
    Octant* getParent() const { return mParent; }
    //! Return octree root
    Octree* getRoot() const { return mRoot; }
    //! Return true if there are no nodes in this octant and child octants
    bool isEmpty() { return mNumNodes == 0; }
    
    //! Reset root pointer recursively. Called when the whole octree is being destroyed
    void resetRoot();
    
protected:
    //! Return scene nodes by a query, called internally
    void getNodesInternal(OctreeQuery& query, unsigned mask) const;
    //! Return scene nodes by a ray query, called internally
    void getNodesInternal(RayOctreeQuery& query) const;
    //! Free child octants. If scene nodes still exist, move them to root
    void release();
    
    //! Increase scene node count recursively
    void incNodeCount()
    {
        mNumNodes++;
        if (mParent)
            mParent->incNodeCount();
    }
    
    //! Decrease scene node count recursively
    void decNodeCount()
    {
        mNumNodes--;
        if (mParent)
            mParent->decNodeCount();
    }
    
    //! World bounding box
    BoundingBox mWorldBoundingBox;
    //! Bounding box used for node fitting
    BoundingBox mCullingBox;
    //! Subdivision level
    unsigned mLevel;
    //! Parent octant
    Octant* mParent;
    //! Child octants
    Octant* mChildren[NUM_OCTANTS];
    //! Octree root
    Octree* mRoot;
    //! Scene nodes
    std::vector<VolumeNode*> mNodes;
    //! Number of scene nodes in this octant and child octants
    unsigned mNumNodes;
    
private:
    Octant(const Octant& rhs);
    Octant& operator = (const Octant& rhs);
};

//! Octree root
class Octree : public SceneExtension, public Octant
{
    DEFINE_TYPE(Octree);
    
public:
    //! Construct
    Octree(const BoundingBox& box, unsigned numLevels, bool headless);
    //! Destruct
    ~Octree();
    
    //! Write scene extension properties to a stream
    virtual void save(Serializer& dest);
    //! Read scene extension properties from a stream
    virtual void load(Deserializer& source);
    //! Write scene extension properties into an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read scene extension properties from an XML element
    virtual void loadXML(const XMLElement& source);
    //! Scene extension update. Update octree when in headless mode
    virtual void update(float timeStep);
    
    //! Resize octree. If octree is not empty, scene nodes will be temporarily moved to the root
    void resize(const BoundingBox& box, unsigned numLevels);
    //! Set global exclude node flags for queries. For debugging/editing purposes only, will not be saved
    void setExcludeFlags(unsigned nodeFlags);
    //! Update and reinsert scene nodes. Called by Pipeline, or by update() if in headless mode
    void updateOctree(const FrameInfo& frame);
    
    //! Return scene nodes by a query
    void getNodes(OctreeQuery& query) const;
    //! Return scene nodes by a ray query
    void getNodes(RayOctreeQuery& query) const;
    //! Return subdivision levels
    unsigned getNumLevels() const { return mNumLevels; }
    //! Return global exclude node flags
    unsigned getExcludeFlags() const { return mExcludeFlags; }
    //! Return whether is in headless mode
    bool isHeadless() const { return mHeadless; }
    
    //! Mark scene node as requiring an update
    void markNodeForUpdate(VolumeNode* node);
    //! Remove scene node from update list
    void clearNodeUpdate(VolumeNode* node);
    //! Mark scene node as requiring a reinsertion
    void markNodeForReinsertion(VolumeNode* node);
    //! Remove scene node from reinsertion list
    void clearNodeReinsertion(VolumeNode* node);
    
private:
    //! Set of scene nodes that require update
    std::set<VolumeNode*> mNodeUpdates;
    //! Set of scene nodes that require reinsertion
    std::set<VolumeNode*> mNodeReinsertions;
    //! Subdivision level
    unsigned mNumLevels;
    //! Global query exclude flags
    unsigned mExcludeFlags;
    //! Headless mode flag
    bool mHeadless;
};

#endif // RENDERER_OCTREE_H
