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
#include "Deserializer.h"
#include "Log.h"
#include "Profiler.h"
#include "Octree.h"
#include "OctreeQuery.h"
#include "Serializer.h"
#include "StringUtils.h"
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
    Vector3 halfSize = mWorldBoundingBox.getSize() * 0.5;
    
    mCullingBox = BoundingBox(mWorldBoundingBox.mMin - halfSize, mWorldBoundingBox.mMax + halfSize); 
    
    for (unsigned x = 0; x < 2; ++x)
    {
        for (unsigned y = 0; y < 2; ++y)
        {
            for (unsigned z = 0; z < 2; ++z)
            {
                mChildren[x][y][z] = 0;
            }
        }
    }
}

Octant::~Octant()
{
    release();
}

Octant* Octant::getOrCreateChild(unsigned x, unsigned y, unsigned z)
{
    if (mChildren[x][y][z])
        return mChildren[x][y][z];
    
    Vector3 newMin = mWorldBoundingBox.mMin;
    Vector3 newMax = mWorldBoundingBox.mMax;
    Vector3 oldCenter = mWorldBoundingBox.getCenter();
    
    if (!x)
        newMax.mX = oldCenter.mX;
    else
        newMin.mX = oldCenter.mX;
    
    if (!y)
        newMax.mY = oldCenter.mY;
    else
        newMin.mY = oldCenter.mY;
    
    if (!z)
        newMax.mZ = oldCenter.mZ;
    else
        newMin.mZ = oldCenter.mZ;
    
    mChildren[x][y][z] = new Octant(BoundingBox(newMin, newMax), mLevel + 1, this, mRoot);
    return mChildren[x][y][z];
}

void Octant::deleteChild(unsigned x, unsigned y, unsigned z)
{
    delete mChildren[x][y][z];
    mChildren[x][y][z] = 0;
}

void Octant::deleteChild(Octant* octant)
{
    for (unsigned x = 0; x < 2; ++x)
    {
        for (unsigned y = 0; y < 2; ++y)
        {
            for (unsigned z = 0; z < 2; ++z)
            {
                if (mChildren[x][y][z] == octant)
                {
                    delete octant;
                    mChildren[x][y][z] = 0;
                    break;
                }
            }
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
            if (node->mOctant)
                node->mOctant->removeNode(node);
            addNode(node);
        }
        return;
    }
    
    Vector3 octantCenter = mWorldBoundingBox.getCenter();
    Vector3 nodeCenter = node->getWorldBoundingBox().getCenter();
    unsigned x, y, z;
    
    if (nodeCenter.mX < octantCenter.mX)
        x = 0;
    else
        x = 1;
    
    if (nodeCenter.mY < octantCenter.mY)
        y = 0;
    else
        y = 1;
    
    if (nodeCenter.mZ < octantCenter.mZ)
        z = 0;
    else
        z = 1;
    
    getOrCreateChild(x, y, z)->insertNode(node);
}

bool Octant::checkNodeSize(VolumeNode* node) const
{
    // If max split level, size always OK
    if (mLevel == mRoot->getNumLevels())
        return true;
    
    Vector3 octantHalfSize = mWorldBoundingBox.getSize() * 0.5;
    Vector3 nodeSize = node->getWorldBoundingBox().getSize();
    
    return (nodeSize.mX >= octantHalfSize.mX) ||(nodeSize.mY >= octantHalfSize.mY) || (nodeSize.mZ >= octantHalfSize.mZ);
}

void Octant::getNodes(OctreeQuery& query) const
{
    PROFILE(Octree_GetNodes);
    
    query.mResult.clear();
    getNodesInternal(query, 0);
}

void Octant::getNodes(RayOctreeQuery& query) const
{
    PROFILE(Octree_Raycast);
    
    query.mResult.clear();
    getNodesInternal(query);
    std::sort(query.mResult.begin(), query.mResult.end(), compareRayQueryResults);
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
        
        if ((!(nodeFlags & query.mIncludeFlags)) || (nodeFlags & query.mExcludeFlags))
            continue;
        if (!node->isVisible())
            continue;
        if ((query.mOccludersOnly) && (!node->isOccluder()))
            continue;
        if ((query.mShadowCastersOnly) && (!node->getCastShadows()))
            continue;
        
        if (query.testNode(node->getWorldBoundingBox(), mask) != OUTSIDE)
            query.mResult.push_back(node);
    }
    
    if (mChildren[0][0][0])
        mChildren[0][0][0]->getNodesInternal(query, mask);
    if (mChildren[0][0][1])
        mChildren[0][0][1]->getNodesInternal(query, mask);
    if (mChildren[0][1][0])
        mChildren[0][1][0]->getNodesInternal(query, mask);
    if (mChildren[0][1][1])
        mChildren[0][1][1]->getNodesInternal(query, mask);
    if (mChildren[1][0][0])
        mChildren[1][0][0]->getNodesInternal(query, mask);
    if (mChildren[1][0][1])
        mChildren[1][0][1]->getNodesInternal(query, mask);
    if (mChildren[1][1][0])
        mChildren[1][1][0]->getNodesInternal(query, mask);
    if (mChildren[1][1][1])
        mChildren[1][1][1]->getNodesInternal(query, mask);
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
        
        if ((!(nodeFlags & query.mIncludeFlags)) || (nodeFlags & query.mExcludeFlags))
            continue;
        if (!node->isVisible())
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
    
    if (mChildren[0][0][0])
        mChildren[0][0][0]->getNodesInternal(query);
    if (mChildren[0][0][1])
        mChildren[0][0][1]->getNodesInternal(query);
    if (mChildren[0][1][0])
        mChildren[0][1][0]->getNodesInternal(query);
    if (mChildren[0][1][1])
        mChildren[0][1][1]->getNodesInternal(query);
    if (mChildren[1][0][0])
        mChildren[1][0][0]->getNodesInternal(query);
    if (mChildren[1][0][1])
        mChildren[1][0][1]->getNodesInternal(query);
    if (mChildren[1][1][0])
        mChildren[1][1][0]->getNodesInternal(query);
    if (mChildren[1][1][1])
        mChildren[1][1][1]->getNodesInternal(query);
}

void Octant::release()
{
    // Remove the nodes from this octant, if any
    for (std::vector<VolumeNode*>::iterator i = mNodes.begin(); i != mNodes.end(); ++i)
        (*i)->mOctant = 0;
    
    mNodes.clear();
    mNumNodes = 0;
    
    for (unsigned x = 0; x < 2; ++x)
    {
        for (unsigned y = 0; y < 2; ++y)
        {
            for (unsigned z = 0; z < 2; ++z)
            {
                delete mChildren[x][y][z];
                mChildren[x][y][z] = 0;
            }
        }
    }
}

Octree::Octree(const BoundingBox& box, unsigned numLevels, bool headless) :
    Octant(box, 0, 0, this),
    mNumLevels(numLevels),
    mHeadless(headless)
{
}

void Octree::save(Serializer& dest)
{
    writeExtensionType(dest);
    dest.writeBoundingBox(mWorldBoundingBox);
    dest.writeVLE(mNumLevels);
}

void Octree::load(Deserializer& source)
{
    checkExtensionType(source);
    BoundingBox box = source.readBoundingBox();
    unsigned numLevels = source.readVLE();
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
    // If in headless mode, run a dummy update now to sync skeletally attached objects
    if (mHeadless)
    {
        FrameInfo frame;
        frame.mCamera = 0;
        frame.mFrameNumber = 0;
        frame.mTimeStep = timeStep;
        updateNodes(frame);
    }
}

void Octree::resize(const BoundingBox& box, unsigned numLevels)
{
    if ((numLevels == mNumLevels) && (box.mMin == mWorldBoundingBox.mMin) && (box.mMax == mWorldBoundingBox.mMax))
        return;
    
    if (mNumNodes)
        LOGWARNING("Resizing octree while nodes still exist");
    
    release();
    
    mWorldBoundingBox = box;
    mNumLevels = numLevels;
    
    LOGINFO("Resized octree to " + toString(box.getSize()) + " with " + toString(numLevels) + " levels");
}

void Octree::markNodeForUpdate(VolumeNode* node)
{
    mNodeUpdates.insert(node);
}

void Octree::clearNodeUpdate(VolumeNode* node)
{
    mNodeUpdates.erase(node);
}

void Octree::updateNodes(const FrameInfo& frame)
{
    PROFILE(Octree_UpdateNodes);
    
    // Let nodes update themselves before re-insertion
    for (std::set<VolumeNode*>::iterator i = mNodeUpdates.begin(); i != mNodeUpdates.end(); ++i)
        (*i)->updateNode(frame);
    
    // Go through nodes which may have to be re-inserted into the octree
    for (std::set<VolumeNode*>::iterator i = mNodeUpdates.begin(); i != mNodeUpdates.end(); ++i)
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
            {
                insertNode(node);
                
                // If old octant (not root) has become empty, delete it
                while ((octant != this) && (octant->isEmpty()))
                {
                    Octant* parent = octant->getParent();
                    parent->deleteChild(octant);
                    octant = parent;
                }
            }
        }
        else
            insertNode(node);
    }
    
    mNodeUpdates.clear();
}
