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
#include "Camera.h"
#include "Geometry.h"
#include "Log.h"
#include "Material.h"
#include "Model.h"
#include "OcclusionBuffer.h"
#include "OctreeQuery.h"
#include "Profiler.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "StaticModel.h"
#include "XMLElement.h"

#include "DebugNew.h"

StaticModel::StaticModel(Octant* octant, const std::string& name) :
    GeometryNode(NODE_STATICMODEL, octant, name)
{
}

StaticModel::StaticModel(unsigned flags, Octant* octant, const std::string& name) :
    GeometryNode(flags, octant, name)
{
}

StaticModel::~StaticModel()
{
}

void StaticModel::save(Serializer& dest)
{
    // Write GeometryNode properties
    GeometryNode::save(dest);
    
    // Write StaticModel properties
    dest.writeStringHash(getResourceHash(mModel));
    
    dest.writeVLE(mMaterials.size());
    for (unsigned i = 0; i < mMaterials.size(); ++i)
        dest.writeStringHash(getResourceHash(mMaterials[i]));
}

void StaticModel::load(Deserializer& source, ResourceCache* cache)
{
    // Read GeometryNode properties
    GeometryNode::load(source, cache);
    
    // Read StaticModel properties
    setModel(cache->getResource<Model>(source.readStringHash()));
    
    unsigned numMaterials = source.readVLE();
    for (unsigned i = 0; i < numMaterials; ++i)
        setMaterial(i, cache->getResource<Material>(source.readStringHash()));
}

void StaticModel::saveXML(XMLElement& dest)
{
    // Write GeometryNode properties
    GeometryNode::saveXML(dest);
    
    // Write StaticModel properties
    XMLElement modelElem = dest.createChildElement("model");
    modelElem.setString("name", getResourceName(mModel));
    
    for (unsigned i = 0; i < mMaterials.size(); ++i)
    {
        XMLElement materialElem = dest.createChildElement("material");
        materialElem.setInt("index", i);
        materialElem.setString("name", getResourceName(mMaterials[i]));
    }
}

void StaticModel::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read GeometryNode properties
    GeometryNode::loadXML(source, cache);
    
    // Read StaticModel properties
    XMLElement modelElem = source.getChildElement("model");
    setModel(cache->getResource<Model>(modelElem.getString("name")));
    
    XMLElement materialElem = source.getChildElement("material");
    while (materialElem)
    {
        unsigned index = materialElem.getInt("index");
        setMaterial(index, cache->getResource<Material>(materialElem.getString("name")));
        materialElem = materialElem.getNextElement("material");
    }
}

bool StaticModel::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    // Write GeometryNode properties and see if there were any changes
    bool prevBits = GeometryNode::writeNetUpdate(dest, destRevision, baseRevision, info);
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    checkStringHash(getResourceHash(mModel), baseRevision, bits, 1);
    unsigned numBaseMaterials = baseRevision.getSize() ? baseRevision.readVLE() : 0;
    if (mMaterials.size() != numBaseMaterials)
        bits |= 2;
    for (unsigned i = 0; i < numBaseMaterials; ++i)
    {
        if (i < mMaterials.size())
            checkStringHash(getResourceHash(mMaterials[i]), baseRevision, bits, 2);
        else
            baseRevision.readStringHash();
    }
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeStringHashDelta(getResourceHash(mModel), dest, destRevision, bits & 1);
    writeVLEDelta(mMaterials.size(), dest, destRevision, bits & 2);
    for (unsigned i = 0; i < mMaterials.size(); ++i)
        writeStringHashDelta(getResourceHash(mMaterials[i]), dest, destRevision, bits & 2);
    
    return prevBits || (bits != 0);
}

void StaticModel::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
    // Read GeometryNode properties
    GeometryNode::readNetUpdate(source, cache, info);
    
    unsigned char bits = source.readUByte();
    if (bits & 1)
        setModel(cache->getResource<Model>(source.readStringHash()));
    if (bits & 2)
    {
        unsigned numMaterials = source.readVLE();
        for (unsigned i = 0; i < numMaterials; ++i)
            setMaterial(i, cache->getResource<Material>(source.readStringHash()));
    }
}

void StaticModel::getResourceRefs(std::vector<Resource*>& dest)
{
    if (mModel)
        dest.push_back(mModel);
    for (unsigned i = 0; i < mMaterials.size(); ++i)
    {
        if (mMaterials[i])
            dest.push_back(mMaterials[i]);
    }
}

void StaticModel::processRayQuery(RayOctreeQuery& query, float initialDistance)
{
    PROFILE(StaticModel_Raycast);
    
    RayQueryLevel level = query.mLevel;
    
    switch (level)
    {
    case RAY_AABB_NOSUBOBJECTS:
    case RAY_AABB:
        {
            RayQueryResult result;
            result.mNode = this;
            result.mDistance = initialDistance;
            query.mResult.push_back(result);
        }
        break;
        
    case RAY_OBB:
        {
            Matrix4x3 inverse = getWorldTransform().getInverse();
            Ray localRay(inverse * query.mRay.mOrigin, inverse * Vector4(query.mRay.mDirection, 0.0f));
            float distance = mBoundingBox.getDistance(localRay);
            if (distance < query.mMaxDistance)
            {
                RayQueryResult result;
                result.mNode = this;
                result.mDistance = distance;
                query.mResult.push_back(result);
            }
        }
        break;
        
    case RAY_TRIANGLE:
        {
            // Do a pretest using the OBB
            Matrix4x3 inverse = getWorldTransform().getInverse();
            Ray localRay(inverse * query.mRay.mOrigin, inverse * Vector4(query.mRay.mDirection, 0.0f));
            float distance = mBoundingBox.getDistance(localRay);
            if (distance < query.mMaxDistance)
            {
                // Then the actual test using triangle geometry
                for (unsigned i = 0; i < mGeometries.size(); ++i)
                {
                    unsigned lodLevel = mModel->getRaycastLodLevel();
                    if (lodLevel >= mGeometries[i].size())
                        lodLevel = mLodLevels[i];
                    
                    Geometry* geom = mGeometries[i][lodLevel];
                    if (geom)
                    {
                        distance = geom->getDistance(localRay);
                        if (distance < query.mMaxDistance)
                        {
                            RayQueryResult result;
                            result.mNode = this;
                            result.mDistance = distance;
                            query.mResult.push_back(result);
                            break;
                        }
                    }
                }
            }
        }
        break;
    }
}

void StaticModel::updateGeometry(const FrameInfo& frame, Renderer* renderer)
{
    if (mLodLevelsDirty)
        calculateLodLevels();
}

unsigned StaticModel::getNumBatches()
{
    return mGeometries.size();
}

Geometry* StaticModel::getBatchGeometry(unsigned batchIndex)
{
    return mGeometries[batchIndex][mLodLevels[batchIndex]];
}

Material* StaticModel::getBatchMaterial(unsigned batchIndex)
{
    return mMaterials[batchIndex];
}

bool StaticModel::drawOcclusion(OcclusionBuffer* buffer)
{
    bool success = true;
    
    for (unsigned i = 0; i < mGeometries.size(); ++i)
    {
        // Use designated LOD level for occlusion, or if out of range, same as visible
        unsigned lodLevel = mModel->getOcclusionLodLevel();
        if (lodLevel >= mGeometries[i].size())
            lodLevel = mLodLevels[i];
        
        Geometry* geom = mGeometries[i][lodLevel];
        if (!geom)
            continue;
        
        // Check that the material is suitable for occlusion (default material always is)
        // and set culling mode
        Material* mat = mMaterials[i];
        if (mat)
        {
            if (!mat->getOcclusion())
                continue;
            buffer->setCullMode(mat->getOcclusionCullMode());
        }
        else
            buffer->setCullMode(CULL_CCW);
        
        const unsigned char* vertexData;
        unsigned vertexSize;
        const unsigned char* indexData;
        unsigned indexSize;
        
        geom->lockRawData(vertexData, vertexSize, indexData, indexSize);
        // Check for valid geometry data
        if ((!vertexData) || (!indexData))
            continue;
        
        unsigned indexStart = geom->getIndexStart();
        unsigned indexCount = geom->getIndexCount();
        
        // Draw and check for running out of triangles
        if (!buffer->draw(getWorldTransform(), vertexData, vertexSize, indexData, indexSize, indexStart, indexCount))
            success = false;
        
        geom->unlockRawData();
        
        if (!success)
            break;
    }
    
    return success;
}

void StaticModel::setModel(Model* model)
{
    if (model == mModel)
        return;
      
    PROFILE(StaticModel_SetModel);
    
    if (!model)
        return;
    
    mModel = model;
    
    // Copy the subgeometry & LOD level structure
    setNumGeometries(model->getNumGeometries());
    const std::vector<std::vector<SharedPtr<Geometry> > >& geometries = model->getGeometries();
    for (unsigned i = 0; i < geometries.size(); ++i)
        mGeometries[i] = geometries[i];
    
    setBoundingBox(model->getBoundingBox());
    resetLodLevels();
}

void StaticModel::setMaterial(Material* material)
{
    for (unsigned i = 0; i < mMaterials.size(); ++i)
        mMaterials[i] = material;
}

bool StaticModel::setMaterial(unsigned index, Material* material)
{
    if (index >= mMaterials.size())
    {
        LOGERROR("Illegal material index");
        return false;
    }
    
    mMaterials[index] = material;
    return true;
}

Material* StaticModel::getMaterial(unsigned index) const
{
    if (index >= mMaterials.size())
        return 0;
    
    return mMaterials[index];
}

void StaticModel::setBoundingBox(const BoundingBox& box)
{
    mBoundingBox = box;
    VolumeNode::onMarkedDirty();
}

void StaticModel::setNumGeometries(unsigned num)
{
    mGeometries.resize(num);
    mMaterials.resize(num);
    resetLodLevels();
}

void StaticModel::onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox)
{
    worldBoundingBox = mBoundingBox.getTransformed(getWorldTransform());
}

void StaticModel::resetLodLevels()
{
    // Ensure that each subgeometry has at least one LOD level, and reset the current LOD level
    mLodLevels.resize(mGeometries.size());
    for (unsigned i = 0; i < mGeometries.size(); ++i)
    {
        if (!mGeometries[i].size())
            mGeometries[i].resize(1);
        mLodLevels[i] = 0;
    }
    
    // Find out the real LOD levels on next geometry update
    mLodLevelsDirty = true;
}

void StaticModel::calculateLodLevels()
{
    for (unsigned i = 0; i < mGeometries.size(); ++i)
    {
        unsigned j;
        for (j = 1; j < mGeometries[i].size(); ++j)
        {
            if ((mGeometries[i][j]) && (mLodDistance <= mGeometries[i][j]->getLodDistance()))
                break;
        }
        mLodLevels[i] = j - 1;
    }
    
    mLodLevelsDirty = false;
}
