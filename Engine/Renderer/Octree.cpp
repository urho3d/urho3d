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
#include "DebugRenderer.h"
#include "Deserializer.h"
#include "Profiler.h"
#include "Octree.h"
#include "OctreeQuery.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "Serializer.h"
#include "XMLElement.h"

#include <algorithm>

#include "DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

inline static bool compareRayQueryResults(const RayQueryResult& lhs, const RayQueryResult& rhs)
{
    return lhs.mDistance < rhs.mDistance;
}

Octant::Octant(const BoundingBox& box, unsigned level, Octant* parent, Octree* root) :
    mWorldBoundingBox(box),
    mLevel(level),
    mParent(parent),
    mRoot(root),
    mNumNodes(0)
{
    Vector3 halfSize = mWorldBoundingBox.getSize() * 0.5f;
    mCullingBox = BoundingBox(mWorldBoundingBox.mMin - halfSize, mWorldBoundingBox.mMax + halfSize);
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
        mChildren[i] = 0;
}

Octant::~Octant()
{
    release();
}

Octant* Octant::getOrCreateChild(unsigned index)
{
    if (mChildren[index])
        return mChildren[index];
    
    Vector3 newMin = mWorldBoundingBox.mMin;
    Vector3 newMax = mWorldBoundingBox.mMax;
    Vector3 oldCenter = mWorldBoundingBox.getCenter();
    
    if (index & 1)
        newMin.mX = oldCenter.mX;
    else
        newMax.mX = oldCenter.mX;
    
    if (index & 2)
        newMin.mY = oldCenter.mY;
    else
        newMax.mY = oldCenter.mY;
    
    if (index & 4)
        newMin.mZ = oldCenter.mZ;
    else
        newMax.mZ = oldCenter.mZ;
    
    mChildren[index] = new Octant(BoundingBox(newMin, newMax), mLevel + 1, this, mRoot);
    return mChildren[index];
}

void Octant::deleteChild(unsigned index)
{
    delete mChildren[index];
    mChildren[index] = 0;
}

void Octant::deleteChild(Octant* octant)
{
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (mChildren[i] == octant)
        {
            delete octant;
            mChildren[i] = 0;
            return;
        }
    }
}

void Octant::insertNode(VolumeNode* node)
{
    // If size OK or outside, stop recursion & insert here
    if ((checkNodeSize(node)) || (mCullingBox.isInside(node->getWorldBoundingBox()) != INSIDE))
    {
        if (node->mOctant != this)
        {
            // Add first, then remove, because node count going to zero deletes the octree branch in question
            Octant* oldOctant = node->mOctant;
            addNode(node);
            if (oldOctant)
                oldOctant->removeNode(node);
        }
        return;
    }
    
    Vector3 octantCenter = mWorldBoundingBox.getCenter();
    Vector3 nodeCenter = node->getWorldBoundingBox().getCenter();
    unsigned x = nodeCenter.mX < octantCenter.mX ? 0 : 1;
    unsigned y = nodeCenter.mY < octantCenter.mY ? 0 : 2;
    unsigned z = nodeCenter.mZ < octantCenter.mZ ? 0 : 4;
    getOrCreateChild(x + y + z)->insertNode(node);
}

bool Octant::checkNodeSize(VolumeNode* node) const
{
    // If max split level, size always OK
    if (mLevel == mRoot->getNumLevels())
        return true;
    
    Vector3 octantHalfSize = mWorldBoundingBox.getSize() * 0.5;
    Vector3 nodeSize = node->getWorldBoundingBox().getSize();
    
    return (nodeSize.mX >= octantHalfSize.mX) || (nodeSize.mY >= octantHalfSize.mY) || (nodeSize.mZ >= octantHalfSize.mZ);
}

void Octant::resetRoot()
{
    mRoot = 0;
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (mChildren[i])
            mChildren[i]->resetRoot();
    }
}

void Octant::drawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    debug->addBoundingBox(mWorldBoundingBox, Color(0.25f, 0.25f, 0.25f), depthTest);
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (mChildren[i])
            mChildren[i]->drawDebugGeometry(debug, depthTest);
    }
}

void Octant::getNodesInternal(OctreeQuery& query, unsigned mask) const
{
    if (!mNumNodes)
        return;
    
    if (mask != M_MAX_UNSIGNED)
    {
        Intersection res = query.testOctant(mCullingBox, mask);
        
        if ((res == OUTSIDE) && (this != mRoot))
            // Fully outside, so cull this octant, its children & nodes
            return;
        if (res == INSIDE) 
            // Fully inside, no culling checks necessary for children & nodes
            mask = M_MAX_UNSIGNED;
    }
    
    for (std::vector<VolumeNode*>::const_iterator i = mNodes.begin(); i != mNodes.end(); ++i)
    {
        VolumeNode* node = *i;
        unsigned nodeFlags = node->getNodeFlags();
        
        if ((!(nodeFlags & query.mNodeFlags)) || (!node->isVisible()))
            continue;
        if ((query.mOccludersOnly) && (!node->isOccluder()))
            continue;
        if ((query.mShadowCastersOnly) && (!node->getCastShadows()))
            continue;
        
        if (query.testNode(node->getWorldBoundingBox(), mask) != OUTSIDE)
            query.mResult.push_back(node);
    }
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (mChildren[i])
            mChildren[i]->getNodesInternal(query, mask);
    }
}

void Octant::getNodesInternal(RayOctreeQuery& query) const
{
    if (!mNumNodes)
        return;
    
    float octantDist = mCullingBox.getDistance(query.mRay);
    if (octantDist >= query.mMaxDistance)
        return;
    
    for (std::vector<VolumeNode*>::const_iterator i = mNodes.begin(); i != mNodes.end(); ++i)
    {
        VolumeNode* node = *i;
        unsigned nodeFlags = node->getNodeFlags();
        
        if ((!(nodeFlags & query.mNodeFlags)) || (!node->isVisible()))
            continue;
        if ((query.mOccludersOnly) && (!node->isOccluder()))
            continue;
        if ((query.mShadowCastersOnly) && (!node->getCastShadows()))
            continue;
        
        float nodeDist = node->getWorldBoundingBox().getDistance(query.mRay);
        // The node will possibly do more accurate collision testing, then store the result(s)
        if (nodeDist < query.mMaxDistance)
            node->processRayQuery(query, nodeDist);
    }
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
    {
        if (mChildren[i])
            mChildren[i]->getNodesInternal(query);
    }
}

void Octant::release()
{
    if ((mRoot) && (this != mRoot))
    {
        // Remove the nodes (if any) from this octant to the root octant
        for (std::vector<VolumeNode*>::iterator i = mNodes.begin(); i != mNodes.end(); ++i)
        {
            (*i)->mOctant = mRoot;
            mRoot->mNodes.push_back(*i);
            mRoot->markNodeForReinsertion(*i);
        }
        mNodes.clear();
        mNumNodes = 0;
    }
    else if (!mRoot)
    {
        // If the whole octree is being destroyed, just detach the nodes
        for (std::vector<VolumeNode*>::iterator i = mNodes.begin(); i != mNodes.end(); ++i)
            (*i)->mOctant = 0;
    }
    
    for (unsigned i = 0; i < NUM_OCTANTS; ++i)
        deleteChild(i);
}

Octree::Octree(const BoundingBox& box, unsigned numLevels, bool headless) :
    Octant(box, 0, 0, this),
    mNumLevels(max((int)numLevels, 1)),
    mDrawDebugGeometry(false),
    mHeadless(headless)
{
}

Octree::~Octree()
{
    // Reset root pointer from all child octants now so that they do not move their scene nodes to root
    resetRoot();
}

void Octree::save(Serializer& dest)
{
    writeExtensionType(dest);
    dest.writeBoundingBox(mWorldBoundingBox);
    dest.writeUInt(mNumLevels);
}

void Octree::load(Deserializer& source)
{
    checkExtensionType(source);
    BoundingBox box = source.readBoundingBox();
    unsigned numLevels = source.readUInt();
    resize(box, numLevels);
}

void Octree::saveXML(XMLElement& dest)
{
    XMLElement octreeElem = dest.createChildElement("octree");
    
    // Write octree properties
    octreeElem.setBoundingBox(mWorldBoundingBox);
    octreeElem.setInt("levels", mNumLevels);
}

void Octree::loadXML(const XMLElement& source)
{
    XMLElement octreeElem = source.getChildElement("octree");
    
    BoundingBox box = octreeElem.getBoundingBox();
    unsigned numLevels = octreeElem.getInt("levels");
    resize(box, numLevels);
}

void Octree::update(float timeStep)
{
    // If in headless mode, run an update now to update and reinsert nodes
    if (mHeadless)
    {
        FrameInfo frame;
        frame.mCamera = 0;
        frame.mFrameNumber = 0;
        frame.mTimeStep = timeStep;
        updateOctree(frame);
    }
}

void Octree::resize(const BoundingBox& box, unsigned numLevels)
{
    numLevels = max((int)numLevels, 1);
    if ((numLevels == mNumLevels) && (box.mMin == mWorldBoundingBox.mMin) && (box.mMax == mWorldBoundingBox.mMax))
        return;
    
    // If nodes exist, they are temporarily moved to the root
    release();
    mNumNodes = mNodes.size();
    
    mWorldBoundingBox = box;
    mNumLevels = numLevels;
    
    Vector3 halfSize = mWorldBoundingBox.getSize() * 0.5f;
    mCullingBox = BoundingBox(mWorldBoundingBox.mMin - halfSize, mWorldBoundingBox.mMax + halfSize);
}

void Octree::updateOctree(const FrameInfo& frame)
{
    {
        PROFILE(Octree_UpdateNodes);
        
        // Let nodes update themselves before reinsertion
        for (std::set<VolumeNode*>::iterator i = mNodeUpdates.begin(); i != mNodeUpdates.end(); ++i)
            (*i)->updateNode(frame);
    }
    
    {
        PROFILE(Octree_ReinsertNodes);
        
        // Reinsert nodes into the octree
        for (std::set<VolumeNode*>::iterator i = mNodeReinsertions.begin(); i != mNodeReinsertions.end(); ++i)
        {
            VolumeNode* node = *i;
            Octant* octant = node->mOctant;
            
            if (octant)
            {
                bool reinsert = false;
                
                if (octant == this)
                {
                    // Handle root octant as special case: if outside the root, do not reinsert
                    if ((getCullingBox().isInside(node->getWorldBoundingBox()) == INSIDE) && (!checkNodeSize(node)))
                        reinsert = true;
                }
                else
                {
                    // Otherwise reinsert if outside current octant or if size does not fit octant size
                    if ((octant->getCullingBox().isInside(node->getWorldBoundingBox()) != INSIDE) || (!octant->checkNodeSize(node)))
                        reinsert = true;
                }
                
                if (reinsert)
                    insertNode(node);
            }
            else
                insertNode(node);
        }
    }
    
    mNodeUpdates.clear();
    mNodeReinsertions.clear();
}

void Octree::getNodes(OctreeQuery& query) const
{
    PROFILE(Octree_GetNodes);
    
    query.mResult.clear();
    getNodesInternal(query, 0);
}

void Octree::getNodes(RayOctreeQuery& query) const
{
    PROFILE(Octree_Raycast);
    
    query.mResult.clear();
    getNodesInternal(query);
    std::sort(query.mResult.begin(), query.mResult.end(), compareRayQueryResults);
}

void Octree::markNodeForUpdate(VolumeNode* node)
{
    mNodeUpdates.insert(node);
}

void Octree::clearNodeUpdate(VolumeNode* node)
{
    mNodeUpdates.erase(node);
}

void Octree::markNodeForReinsertion(VolumeNode* node)
{
    mNodeReinsertions.insert(node);
}

void Octree::clearNodeReinsertion(VolumeNode* node)
{
    mNodeReinsertions.erase(node);
}

void Octree::drawDebugGeometry(bool depthTest)
{
    DebugRenderer* debug = mScene->getExtension<DebugRenderer>();
    if (!debug)
        return;
    
    PROFILE(Octree_DrawDebugGeometry);
    
    Octant::drawDebugGeometry(debug, depthTest);
}
