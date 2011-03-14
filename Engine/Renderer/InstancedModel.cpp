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
#include "IndexBuffer.h"
#include "InstancedModel.h"
#include "Log.h"
#include "Material.h"
#include "Model.h"
#include "OcclusionBuffer.h"
#include "OctreeQuery.h"
#include "Profiler.h"
#include "Renderer.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "ResourceEvents.h"
#include "VertexBuffer.h"
#include "XMLElement.h"

#include <cstring>

#include "DebugNew.h"

InstancingMode InstancedModel::sMode = SHADER_INSTANCING;
std::map<const VertexBuffer*, SharedPtr<VertexBuffer> > InstancedModel::sInstanceVertexBuffers;
std::map<std::pair<const IndexBuffer*, unsigned>, SharedPtr<IndexBuffer> > InstancedModel::sInstanceIndexBuffers;

InstancedModel::InstancedModel(Octant* octant, const std::string& name) :
    GeometryNode(NODE_INSTANCEDMODEL, octant, name),
    mMode(sMode),
    mAverageInstanceScale(1.0f),
    mInstancesRelative(true),
    mInstancesDirty(true),
    mInstanceTransformsDirty(true),
    mHWInstancingBufferDirty(true)
{
}

InstancedModel::~InstancedModel()
{
    mGeometries.clear();
    cleanupInstanceBuffers();
}

void InstancedModel::save(Serializer& dest)
{
    // Write GeometryNode properties
    GeometryNode::save(dest);
    
    // Write InstanceModel properties
    dest.writeStringHash(getResourceHash(mModel));
    
    dest.writeVLE(mOriginalMaterials.size());
    for (unsigned i = 0; i < mOriginalMaterials.size(); ++i)
        dest.writeStringHash(getResourceHash(mOriginalMaterials[i]));
    
    dest.writeBool(mInstancesRelative);
    dest.writeVLE(mInstances.size());
    for (unsigned i = 0; i < mInstances.size(); ++i)
    {
        dest.writeVector3(mInstances[i].mPosition);
        dest.writeQuaternion(mInstances[i].mRotation);
        dest.writeVector3(mInstances[i].mScale);
    }
}

void InstancedModel::load(Deserializer& source, ResourceCache* cache)
{
    // Read GeometryNode properties
    GeometryNode::load(source, cache);
    
    // Read InstancedModel properties
    setModel(cache->getResource<Model>(source.readStringHash()));
    
    unsigned numMaterials = source.readVLE();
    for (unsigned i = 0; i < numMaterials; ++i)
        setMaterial(i, cache->getResource<Material>(source.readStringHash()));
    
    mInstancesRelative = source.readBool();
    setNumInstances(source.readVLE());
    for (unsigned i = 0; i < mInstances.size(); ++i)
    {
        mInstances[i].mPosition = source.readVector3();
        mInstances[i].mRotation = source.readQuaternion();
        mInstances[i].mScale = source.readVector3();
    }
}

void InstancedModel::saveXML(XMLElement& dest)
{
    // Write GeometryNode properties
    GeometryNode::saveXML(dest);
    
    // Write InstancedModel properties
    XMLElement modelElem = dest.createChildElement("model");
    modelElem.setString("name", getResourceName(mModel));
    
    for (unsigned i = 0; i < mOriginalMaterials.size(); ++i)
    {
        XMLElement materialElem = dest.createChildElement("material");
        materialElem.setString("name", getResourceName(mOriginalMaterials[i]));
    }
    
    XMLElement instancesElem = dest.createChildElement("instances");
    instancesElem.setBool("relative", mInstancesRelative);
    instancesElem.setInt("count", mInstances.size());
    
    for (unsigned i = 0; i < mInstances.size(); ++i)
    {
        XMLElement instanceElem = dest.createChildElement("instance");
        const Instance& instance = mInstances[i];
        instanceElem.setVector3("pos", instance.mPosition);
        instanceElem.setVector3("rot", instance.mRotation.getEulerAngles());
        instanceElem.setVector3("scale", instance.mScale);
    }
}

void InstancedModel::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read GeometryNode properties
    GeometryNode::loadXML(source, cache);
    
    // Read InstancedModel properties
    XMLElement modelElem = source.getChildElement("model");
    setModel(cache->getResource<Model>(modelElem.getString("name")));
    
    XMLElement materialElem = source.getChildElement("material");
    unsigned index = 0;
    while (materialElem)
    {
        setMaterial(index, cache->getResource<Material>(materialElem.getString("name")));
        ++index;
        materialElem = materialElem.getNextElement("material");
    }
    
    XMLElement instancesElem = source.getChildElement("instances");
    mInstancesRelative = instancesElem.getBool("relative");
    setNumInstances(instancesElem.getInt("count"));
    
    XMLElement instanceElem = source.getChildElement("instance");
    index = 0;
    while ((instanceElem) && (index < mInstances.size()))
    {
        Instance& instance = mInstances[index];
        instance.mPosition = instanceElem.getVector3("pos");
        instance.mRotation = instanceElem.getQuaternion("rot");
        instance.mScale = instanceElem.getVector3("scale");
        instanceElem = instanceElem.getNextElement("instance");
        ++index;
    }
}

bool InstancedModel::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    // Write GeometryNode properties and see if there were any changes
    bool prevBits = GeometryNode::writeNetUpdate(dest, destRevision, baseRevision, info);
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    // Model and materials
    checkStringHash(getResourceHash(mModel), baseRevision, bits, 1);
    unsigned numBaseMaterials = baseRevision.getSize() ? baseRevision.readVLE() : 0;
    if (mMaterials.size() != numBaseMaterials)
        bits |= 2;
    for (unsigned i = 0; i < numBaseMaterials; ++i)
    {
        if (i < mMaterials.size())
            checkStringHash(getResourceHash(mOriginalMaterials[i]), baseRevision, bits, 2);
        else
            baseRevision.readStringHash();
    }
    // Instances
    checkBool(mInstancesRelative, baseRevision, bits, 4);
    unsigned numBaseInstances = baseRevision.getSize() ? baseRevision.readVLE() : 0;
    if (mInstances.size() != numBaseInstances)
        bits |= 8;
    static std::vector<unsigned char> instanceBits;
    instanceBits.resize(mInstances.size());
    // Compare against the base instances first
    for (unsigned i = 0; i < numBaseInstances; ++i)
    {
        if (i < mInstances.size())
        {
            instanceBits[i] = 0;
            checkVector3(mInstances[i].mPosition, baseRevision, instanceBits[i], 1);
            checkQuaternion(mInstances[i].mRotation, baseRevision, instanceBits[i], 2);
            checkVector3(mInstances[i].mScale, baseRevision, instanceBits[i], 4);
            if (instanceBits[i])
                bits |= 8;
        }
        else
        {
            baseRevision.readVector3();
            baseRevision.readQuaternion();
            baseRevision.readVector3();
        }
    }
    // Then check possible new instances against defaults
    for (unsigned i = numBaseInstances; i < mInstances.size(); ++i)
    {
        instanceBits[i] = 0;
        if (mInstances[i].mPosition != Vector3::sZero)
            instanceBits[i] |= 1;
        if (mInstances[i].mRotation != Quaternion::sIdentity)
            instanceBits[i] |= 2;
        if (mInstances[i].mScale != Vector3::sUnity)
            instanceBits[i] |= 4;
        if (instanceBits[i])
            bits |= 8;
    }
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeStringHashDelta(getResourceHash(mModel), dest, destRevision, bits & 1);
    writeVLEDelta(mMaterials.size(), dest, destRevision, bits & 2);
    for (unsigned i = 0; i < mMaterials.size(); ++i)
        writeStringHashDelta(getResourceHash(mOriginalMaterials[i]), dest, destRevision, bits & 2);
    writeBoolDelta(mInstancesRelative, dest, destRevision, bits & 4);
    // Write all instances to the base revision
    destRevision.writeVLE(mInstances.size());
    for (unsigned i = 0; i < mInstances.size(); ++i)
    {
        destRevision.writeVector3(mInstances[i].mPosition);
        destRevision.writeQuaternion(mInstances[i].mRotation);
        destRevision.writeVector3(mInstances[i].mScale);
    }
    // Then write changed properties of instances to the network stream
    if (bits & 8)
    {
        dest.writeVLE(mInstances.size());
        for (unsigned i = 0; i < mInstances.size(); ++i)
        {
            dest.writeUByte(instanceBits[i]);
            if (instanceBits[i] & 1)
                dest.writeVector3(mInstances[i].mPosition);
            if (instanceBits[i] & 2)
                dest.writePackedQuaternion(mInstances[i].mRotation);
            if (instanceBits[i] & 4)
                dest.writeVector3(mInstances[i].mScale);
        }
    }
    
    return prevBits || (bits != 0);
}

void InstancedModel::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
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
    readBoolDelta(mInstancesRelative, source, bits & 4);
    if (bits & 8)
    {
        unsigned numInstances = source.readVLE();
        if (numInstances != mInstances.size())
            setNumInstances(numInstances);
        for (unsigned i = 0; i < numInstances; ++i)
        {
            unsigned char instanceBits = source.readUByte();
            readVector3Delta(mInstances[i].mPosition, source, instanceBits & 1);
            readPackedQuaternionDelta(mInstances[i].mRotation, source, instanceBits & 2);
            readVector3Delta(mInstances[i].mScale, source, instanceBits & 4);
        }
    }
}

void InstancedModel::getResourceRefs(std::vector<Resource*>& dest)
{
    if (mModel)
        dest.push_back(mModel);
    for (unsigned i = 0; i < mOriginalMaterials.size(); ++i)
    {
        if (mOriginalMaterials[i])
            dest.push_back(mOriginalMaterials[i]);
    }
}

void InstancedModel::processRayQuery(RayOctreeQuery& query, float initialDistance)
{
    PROFILE(InstancedModel_Raycast);
    
    RayQueryLevel level = query.mLevel;
    
    float nearest = M_INFINITY;
    unsigned nearestInstance = 0;
    
    switch (level)
    {
    case RAY_AABB_NOSUBOBJECTS:
        {
            RayQueryResult result;
            result.mNode = this;
            result.mDistance = initialDistance;
            query.mResult.push_back(result);
            return;
        }
        
    case RAY_AABB:
        for (unsigned i = 0; i < mInstances.size(); ++i)
        {
            Matrix4x3 transform(mInstances[i].mPosition, mInstances[i].mRotation, mInstances[i].mScale);
            if (mInstancesRelative)
                transform = getWorldTransform() * transform;
            
            BoundingBox instanceBox = mBoundingBox.getTransformed(transform);
            float distance = instanceBox.getDistance(query.mRay);
            if ((distance < query.mMaxDistance) && (distance < nearest))
            {
                nearest = distance;
                nearestInstance = i;
            }
        }
        break;
        
    case RAY_OBB:
        for (unsigned i = 0; i < mInstances.size(); ++i)
        {
            Matrix4x3 transform(mInstances[i].mPosition, mInstances[i].mRotation, mInstances[i].mScale);
            if (mInstancesRelative)
                transform = getWorldTransform() * transform;
            
            // Do an initial AABB test
            float distance = mBoundingBox.getTransformed(transform).getDistance(query.mRay);
            if ((distance < query.mMaxDistance) && (distance < nearest))
            {
                Matrix4x3 inverse = transform.getInverse();
                Ray localRay(inverse * query.mRay.mOrigin, inverse * Vector4(query.mRay.mDirection, 0.0f));
                distance = mBoundingBox.getDistance(localRay);
                if ((distance < query.mMaxDistance) && (distance < nearest))
                {
                    nearest = distance;
                    nearestInstance = i;
                }
            }
        }
        break;
        
    case RAY_TRIANGLE:
        for (unsigned i = 0; i < mInstances.size(); ++i)
        {
            Matrix4x3 transform(mInstances[i].mPosition, mInstances[i].mRotation, mInstances[i].mScale);
            if (mInstancesRelative)
                transform = getWorldTransform() * transform;
            
            // Do an initial AABB test
            float distance = mBoundingBox.getTransformed(transform).getDistance(query.mRay);
            if ((distance < query.mMaxDistance) && (distance < nearest))
            {
                // Then an OBB test
                Matrix4x3 inverse = transform.getInverse();
                Ray localRay(inverse * query.mRay.mOrigin, inverse * Vector4(query.mRay.mDirection, 0.0f));
                distance = mBoundingBox.getDistance(localRay);
                if ((distance < query.mMaxDistance) && (distance < nearest))
                {
                    // And finally the triangle-level test
                    for (unsigned j = 0; j < mOriginalGeometries.size(); ++j)
                    {
                        unsigned lodLevel = mModel->getRaycastLodLevel();
                        if (lodLevel >= mOriginalGeometries[j].size())
                            lodLevel = mOriginalLodLevels[j];
                        
                        Geometry* geom = mOriginalGeometries[j][lodLevel];
                        if (geom)
                        {
                            distance = geom->getDistance(localRay);
                            if ((distance < query.mMaxDistance) && (distance < nearest))
                            {
                                nearest = distance;
                                nearestInstance = i;
                                break;
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    
    // Return the nearest hit against an instance
    if (nearest < M_INFINITY)
    {
        RayQueryResult result;
        result.mNode = this;
        result.mDistance = nearest;
        result.mSubObject = nearestInstance;
        query.mResult.push_back(result);
    }
}

void InstancedModel::updateDistance(const FrameInfo& frame)
{
    mDistance = frame.mCamera->getDistance(getWorldPosition());
    
    static const Vector3 dotScale(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);
    float scale = mAverageInstanceScale;
    if (mInstancesRelative)
        scale *= getWorldScale().dotProduct(dotScale);
    float newLodDistance = frame.mCamera->getLodDistance(mDistance, scale, mLodBias);
    
    if (newLodDistance != mLodDistance)
    {
        mLodDistance = newLodDistance;
        mLodLevelsDirty = true;
    }
}

void InstancedModel::updateGeometry(const FrameInfo& frame, Renderer* renderer)
{
    if (sMode != mMode)
    {
        mMode = sMode;
        mInstancesDirty = true;
    }
    
    if (mInstancesDirty)
        buildInstances(renderer);
    
    if (mInstanceTransformsDirty)
        updateInstanceTransforms();
    
    if ((mMode == HARDWARE_INSTANCING) && (mHWInstancingBufferDirty))
        updateHWInstancingBuffer();
    
    if (mLodLevelsDirty)
        calculateLodLevels();
}

unsigned InstancedModel::getNumBatches()
{
    return mGeometries.size();
}

Geometry* InstancedModel::getBatchGeometry(unsigned batchIndex)
{
    return mGeometries[batchIndex][mLodLevels[batchIndex]];
}

Material* InstancedModel::getBatchMaterial(unsigned batchIndex)
{
    return mMaterials[batchIndex];
}

bool InstancedModel::getVertexShaderParameter(unsigned batchIndex, VSParameter parameter, const float** data,
    unsigned* count)
{
    if ((parameter == VSP_MODELINSTANCES) && (mMode == SHADER_INSTANCING) && (mOriginalGeometries.size()))
    {
        unsigned batchNumber = batchIndex / mOriginalGeometries.size();
        *data = mInstanceTransforms[mBatchStarts[batchNumber]].getData();
        *count = mBatchCounts[batchNumber] * 12;
        
        return true;
    }
    
    return false;
}

bool InstancedModel::drawOcclusion(OcclusionBuffer* buffer)
{
    bool success = true;
    
    for (unsigned i = 0; i < mOriginalGeometries.size(); ++i)
    {
        // Use designated LOD level for occlusion, or if out of range, same as visible
        unsigned lodLevel = mModel->getOcclusionLodLevel();
        if (lodLevel >= mGeometries[i].size())
            lodLevel = mOriginalLodLevels[i];
        
        Geometry* geom = mOriginalGeometries[i][lodLevel];
        if (!geom)
            continue;
        
        // Check that the material is suitable for occlusion (default material always is)
        // and set culling mode
        Material* mat = mOriginalMaterials[i];
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
        
        for (unsigned j = 0; j < mInstances.size(); ++j)
        {
            // Draw and check for running out of triangles
            if (!buffer->draw(mInstanceTransforms[j], vertexData, vertexSize, indexData, indexSize, indexStart, indexCount))
            {
                success = false;
                break;
            }
        }
        
        geom->unlockRawData();
        
        if (!success)
            break;
    }
    
    return success;
}

void InstancedModel::setModel(Model* model)
{
    if (model == mModel)
        return;
    
    PROFILE(InstancedModel_SetModel);
    
    if (!model)
        return;
    
    // Unsubscribe from the reload event of previous model (if any), then subscribe to the new
    if (mModel)
        unsubscribeFromEvent(mModel, EVENT_RELOADFINISHED);
    if (model)
        subscribeToEvent(model, EVENT_RELOADFINISHED, EVENT_HANDLER(InstancedModel, handleModelReloadFinished));
    
    mModel = model;
    mOriginalGeometries.clear();
    
    // Copy the subgeometry & LOD level structure
    const std::vector<std::vector<SharedPtr<Geometry> > >& geometries = model->getGeometries();
    mOriginalMaterials.resize(geometries.size());
    for (unsigned i = 0; i < geometries.size(); ++i)
        mOriginalGeometries.push_back(geometries[i]);
    
    // Set the bounding box
    setBoundingBox(model->getBoundingBox());
    markInstancesDirty();
    resetLodLevels();
}

void InstancedModel::setMaterial(Material* material)
{
    for (unsigned i = 0; i < mOriginalMaterials.size(); ++i)
        mOriginalMaterials[i] = material;
    markInstancesDirty();
}

bool InstancedModel::setMaterial(unsigned index, Material* material)
{
    if (index >= mOriginalMaterials.size())
    {
        LOGERROR("Illegal material index");
        return false;
    }
    
    mOriginalMaterials[index] = material;
    markInstancesDirty();
    return true;
}

void InstancedModel::setNumInstances(unsigned num)
{
    unsigned oldNum = mInstances.size();
    mInstances.resize(num);
    mInstanceTransforms.resize(num);
    
    // Set default values for new instances
    for (unsigned i = oldNum; i < num; ++i)
    {
        mInstances[i].mPosition = Vector3::sZero;
        mInstances[i].mRotation = Quaternion::sIdentity;
        mInstances[i].mScale = Vector3::sUnity;
    }
    
    markInstancesDirty();
}

void InstancedModel::setInstancesRelative(bool enable)
{
    mInstancesRelative = enable;
    markInstanceTransformsDirty();
}

void InstancedModel::updated()
{
    markInstanceTransformsDirty();
}

Material* InstancedModel::getMaterial(unsigned index) const
{
    return index < mOriginalMaterials.size() ? mOriginalMaterials[index] : (Material*)0;
}

Instance* InstancedModel::getInstance(unsigned index)
{
    return index < mInstances.size() ? &mInstances[index] : (Instance*)0;
}

void InstancedModel::onMarkedDirty()
{
    VolumeNode::onMarkedDirty();
    
    if (mInstancesRelative)
        mInstanceTransformsDirty = true;
}

void InstancedModel::onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox)
{
    if (mInstanceTransformsDirty)
        updateInstanceTransforms();
    
    worldBoundingBox.mDefined = false;
    
    for (unsigned i = 0; i < mInstanceTransforms.size(); ++i)
        worldBoundingBox.merge(mBoundingBox.getTransformed(mInstanceTransforms[i]));
    
    if (!mInstances.size())
        worldBoundingBox.merge(getWorldPosition());
}

void InstancedModel::buildInstances(Renderer* renderer)
{
    PROFILE(InstancedModel_Build);
    
    mInstancesDirty = false;
    
    mGeometries.clear();
    mMaterials.clear();
    mBatchStarts.clear();
    mBatchCounts.clear();
    
    if ((!mOriginalGeometries.size()) || (!mOriginalGeometries[0].size()))
        return;
    
    unsigned numInstances = mInstances.size();
    mInstanceTransformsDirty = true;
    
    if (mMode == SHADER_INSTANCING)
    {
        mHWInstancingBuffer.reset();
        
        unsigned instanceIndex = 0;
        while (numInstances)
        {
            // Check how many vertices in the original geometry. Avoid having to convert to 32bit indices
            unsigned maxVertices = 0;
            for (unsigned i = 0; i < mOriginalGeometries.size(); ++i)
            {
                if (!mOriginalGeometries[i][0])
                    continue;
                unsigned vertices = mOriginalGeometries[i][0]->getVertexBuffer(0)->getVertexCount();
                if (vertices > maxVertices)
                    maxVertices = vertices;
            }
            
            maxVertices = max(maxVertices, 1);
            unsigned instanceCount = 65536 / maxVertices;
            if (instanceCount < 2)
            {
                LOGERROR("Too many vertices in original geometry for instancing");
                mInstances.clear();
                return;
            }
            
            if (instanceCount > MAX_INSTANCES_PER_BATCH)
                instanceCount = MAX_INSTANCES_PER_BATCH;
            if (instanceCount > numInstances)
                instanceCount = numInstances;
            
            mBatchStarts.push_back(instanceIndex);
            mBatchCounts.push_back(instanceCount);
            
            for (unsigned i = 0; i < mOriginalGeometries.size(); ++i)
            {
                std::vector<SharedPtr<Geometry> > lodLevels;
                lodLevels.resize(mOriginalGeometries[i].size());
                
                for (unsigned j = 0; j < mOriginalGeometries[i].size(); ++j)
                {
                    Geometry* original = mOriginalGeometries[i][j];
                    if (!original)
                        continue;
                    
                    SharedPtr<Geometry> clone(new Geometry());
                    
                    clone->setNumVertexBuffers(original->getNumVertexBuffers());
                    for (unsigned k = 0; k < original->getNumVertexBuffers(); ++k)
                        clone->setVertexBuffer(k, createInstanceVertexBuffer(original->getVertexBuffer(k), instanceCount),
                            original->getVertexElementMask(k) | MASK_INSTANCENUMBER);
                    unsigned indexStart;
                    clone->setIndexBuffer(createInstanceIndexBuffer(mOriginalGeometries, i, j, instanceCount, indexStart));
                    clone->setDrawRange(original->getPrimitiveType(), indexStart, instanceCount * original->getIndexCount());
                    clone->setLodDistance(original->getLodDistance());
                    lodLevels[j] = clone;
                }
                
                mGeometries.push_back(lodLevels);
                mMaterials.push_back(mOriginalMaterials[i]);
            }
            
            instanceIndex += instanceCount;
            numInstances -= instanceCount;
        }
    }
    else
    {
        cleanupInstanceBuffers();
        
        if (!mHWInstancingBuffer)
            mHWInstancingBuffer = new VertexBuffer(renderer);
        mHWInstancingBuffer->setSize(numInstances, MASK_INSTANCEMATRIX1 | MASK_INSTANCEMATRIX2 | MASK_INSTANCEMATRIX3);
        mHWInstancingBufferDirty = true;
        
        for (unsigned i = 0; i < mOriginalGeometries.size(); ++i)
        {
            std::vector<SharedPtr<Geometry> > lodLevels;
            
            for (unsigned j = 0; j < mOriginalGeometries[i].size(); ++j)
            {
                SharedPtr<Geometry> clone(new Geometry());
                Geometry* original = mOriginalGeometries[i][j];
                
                unsigned numVBs = original->getNumVertexBuffers();
                if (numVBs >= MAX_VERTEX_STREAMS)
                {
                    LOGERROR("No room for instance vertex stream");
                    mInstances.clear();
                    return;
                }
                
                clone->setNumVertexBuffers(numVBs + 1);
                for (unsigned k = 0; k < numVBs; ++k)
                    clone->setVertexBuffer(k, original->getVertexBuffer(k), original->getVertexElementMask(k));
                clone->setVertexBuffer(numVBs, mHWInstancingBuffer);
                
                clone->setIndexBuffer(original->getIndexBuffer());
                clone->setDrawRange(original->getPrimitiveType(), original->getIndexStart(), original->getIndexCount());
                clone->setInstanceCount(numInstances);
                clone->setLodDistance(original->getLodDistance());
                lodLevels.push_back(clone);
            }
            
            mGeometries.push_back(lodLevels);
            mMaterials.push_back(mOriginalMaterials[i]);
        }
    }
    
    resetLodLevels();
}

void InstancedModel::updateInstanceTransforms()
{
    PROFILE(InstancedModel_UpdateTransforms);
    
    if (!mInstanceTransforms.size())
        return;
    
    Matrix4x3 transform;
    const Matrix4x3& worldTransform = getWorldTransform();
    
    static const Vector3 dotScale(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);
    float scaleAcc = 0.0f;
    
    for (unsigned i = 0; i < mInstanceTransforms.size(); ++i)
    {
        transform.define(mInstances[i].mPosition, mInstances[i].mRotation, mInstances[i].mScale);
        scaleAcc += mInstances[i].mScale.dotProduct(dotScale);
        
        if (!mInstancesRelative)
            mInstanceTransforms[i] = transform;
        else
            mInstanceTransforms[i] = worldTransform * transform;
    }
    
    mAverageInstanceScale = scaleAcc / mInstanceTransforms.size();
    
    mInstanceTransformsDirty = false;
    if (mMode == HARDWARE_INSTANCING)
        mHWInstancingBufferDirty = true;
}

void InstancedModel::updateHWInstancingBuffer()
{
    if ((mHWInstancingBuffer) && (mHWInstancingBuffer->getVertexCount() == mInstanceTransforms.size()))
    {
        PROFILE(InstancedModel_UpdateVertexBuffer);
        
        mHWInstancingBuffer->setData(mInstanceTransforms[0].getData());
        mHWInstancingBufferDirty = false;
    }
}

const SharedPtr<VertexBuffer>& InstancedModel::createInstanceVertexBuffer(VertexBuffer* original, unsigned instanceCount)
{
    std::map<const VertexBuffer*, SharedPtr<VertexBuffer> >::iterator i = sInstanceVertexBuffers.find(original);
    // If there already exists a buffer with enough copies of the original, return it
    if ((i != sInstanceVertexBuffers.end()) && (i->second->getVertexCount() >= original->getVertexCount() * instanceCount))
        return i->second;
    // Otherwise have to (re)create the buffer
    if (i == sInstanceVertexBuffers.end())
    {
        sInstanceVertexBuffers[original] = new VertexBuffer(original->getRenderer());
        i = sInstanceVertexBuffers.find(original);
    }
    
    // Copy the vertices as many times as necessary and add the instance number data
    i->second->setSize(original->getVertexCount() * instanceCount, original->getElementMask() | MASK_INSTANCENUMBER);
    unsigned char* srcData = (unsigned char*)original->lock(0, original->getVertexCount(), LOCK_READONLY);
    unsigned char* destData = (unsigned char*)i->second->lock(0, i->second->getVertexCount(), LOCK_DISCARD);
    unsigned srcVertexSize = original->getVertexSize();
    float instanceIndex = 0.0f;
    for (unsigned j = 0; j < instanceCount; ++j)
    {
        for (unsigned k = 0; k < original->getVertexCount(); ++k)
        {
            memcpy(destData, &srcData[k * srcVertexSize], srcVertexSize);
            destData += srcVertexSize;
            *((float*)destData) = instanceIndex;
            destData += sizeof(float);
        }
        instanceIndex += 1.0f;
    }
    i->second->unlock();
    original->unlock();
    
    return i->second;
}

const SharedPtr<IndexBuffer>& InstancedModel::createInstanceIndexBuffer(
    const std::vector<std::vector<SharedPtr<Geometry> > >& geometries, unsigned subGeometry, unsigned lodLevel,
    unsigned instanceCount, unsigned& indexStart)
{
    IndexBuffer* original = geometries[subGeometry][lodLevel]->getIndexBuffer();
    // Build the geometry part of search key by adding the total amount of used indices. Not foolproof,
    // but should suffice in cases where an indexbuffer is generally not shared between different models
    unsigned totalIndices = 0;
    for (unsigned i = 0; i < geometries.size(); ++i)
    {
        for (unsigned j = 0; j < geometries[i].size(); ++j)
        {
            if (geometries[i][j]->getIndexBuffer() == original)
                totalIndices += geometries[i][j]->getIndexCount();
        }
    }
    
    std::pair<const IndexBuffer*, unsigned> searchKey = std::make_pair(original, totalIndices);
    std::map<std::pair<const IndexBuffer*, unsigned>, SharedPtr<IndexBuffer> >::iterator i = 
        sInstanceIndexBuffers.find(searchKey);
    // If there already exists a buffer with enough copies of the original, return it
    if ((i != sInstanceIndexBuffers.end()) && (i->second->getIndexCount() >= totalIndices * instanceCount))
    {
        unsigned currentInstanceCount = i->second->getIndexCount() / totalIndices;
        unsigned destIndex = 0;
        for (unsigned j = 0; j < geometries.size(); ++j)
        {
            for (unsigned k = 0; k < geometries[j].size(); ++k)
            {
                if ((j == subGeometry) && (k == lodLevel))
                    indexStart = destIndex;
                if (geometries[j][k]->getIndexBuffer() == original)
                    destIndex += currentInstanceCount * geometries[j][k]->getIndexCount();
            }
        }
        return i->second;
    }
    // Otherwise have to (re)create the buffer
    if (i == sInstanceIndexBuffers.end())
    {
        sInstanceIndexBuffers[searchKey] = new IndexBuffer(original->getRenderer());
        i = sInstanceIndexBuffers.find(searchKey);
    }
    
    i->second->setSize(totalIndices * instanceCount, original->getIndexSize() == sizeof(unsigned));
    // 16-bit indices
    if (original->getIndexSize() == sizeof(unsigned short))
    {
        unsigned short* srcData = (unsigned short*)original->lock(0, original->getIndexCount(), LOCK_READONLY);
        unsigned short* destData = (unsigned short*)i->second->lock(0, i->second->getIndexCount(), LOCK_DISCARD);
        unsigned destIndex = 0;
        
        for (unsigned j = 0; j < geometries.size(); ++j)
        {
            for (unsigned k = 0; k < geometries[j].size(); ++k)
            {
                unsigned vertexCount = geometries[j][k]->getVertexBuffer(0)->getVertexCount();
                if (geometries[j][k]->getIndexBuffer() == original)
                {
                    if ((j == subGeometry) && (k == lodLevel))
                        indexStart = destIndex;
                    
                    unsigned indexStart = geometries[j][k]->getIndexStart();
                    unsigned indexEnd = indexStart + geometries[j][k]->getIndexCount();
                    
                    for (unsigned l = 0; l < instanceCount; ++l)
                    {
                        for (unsigned m = indexStart; m < indexEnd; ++m)
                        {
                            *destData = srcData[m] + l * vertexCount;
                            ++destData;
                        }
                    }
                    
                    destIndex += instanceCount * (indexEnd - indexStart);
                }
            }
        }
        i->second->unlock();
        original->unlock();
    }
    // 32-bit indices
    else
    {
        unsigned* srcData = (unsigned*)original->lock(0, original->getIndexCount(), LOCK_READONLY);
        unsigned* destData = (unsigned*)i->second->lock(0, i->second->getIndexCount(), LOCK_DISCARD);
        unsigned destIndex = 0;
        
        for (unsigned j = 0; j < geometries.size(); ++j)
        {
            for (unsigned k = 0; k < geometries[j].size(); ++k)
            {
                unsigned vertexCount = geometries[j][k]->getVertexBuffer(0)->getVertexCount();
                if (geometries[j][k]->getIndexBuffer() == original)
                {
                    if ((j == subGeometry) && (k == lodLevel))
                        indexStart = destIndex;
                    
                    unsigned indexStart = geometries[j][k]->getIndexStart();
                    unsigned indexEnd = indexStart + geometries[j][k]->getIndexCount();
                    
                    for (unsigned l = 0; l < instanceCount; ++l)
                    {
                        for (unsigned m = indexStart; m < indexEnd; ++m)
                        {
                            *destData = srcData[m] + l * vertexCount;
                            ++destData;
                        }
                    }
                    
                    destIndex += instanceCount * (indexEnd - indexStart);
                }
            }
        }
        i->second->unlock();
        original->unlock();
    }
    
    return i->second;
}

void InstancedModel::cleanupInstanceBuffers()
{
    // Remove buffers that are only referenced in the static maps, and no longer used by any InstancedModels
    for (std::map<const VertexBuffer*, SharedPtr<VertexBuffer> >::iterator i = sInstanceVertexBuffers.begin();
        i != sInstanceVertexBuffers.end();)
    {
        std::map<const VertexBuffer*, SharedPtr<VertexBuffer> >::iterator current = i++;
        if (current->second.getRefCount() == 1)
            sInstanceVertexBuffers.erase(current);
    }
    
    for (std::map<std::pair<const IndexBuffer*, unsigned>, SharedPtr<IndexBuffer> >::iterator i = sInstanceIndexBuffers.begin();
        i != sInstanceIndexBuffers.end();)
    {
        std::map<std::pair<const IndexBuffer*, unsigned>, SharedPtr<IndexBuffer> >::iterator current = i++;
        if (current->second.getRefCount() == 1)
            sInstanceIndexBuffers.erase(current);
    }
}

void InstancedModel::markInstancesDirty()
{
    mInstancesDirty = true;
    markInstanceTransformsDirty();
}

void InstancedModel::markInstanceTransformsDirty()
{
    VolumeNode::onMarkedDirty();
    mInstanceTransformsDirty = true;
}

void InstancedModel::setBoundingBox(const BoundingBox& box)
{
    mBoundingBox = box;
    VolumeNode::onMarkedDirty();
}

void InstancedModel::resetLodLevels()
{
    // Ensure that each subgeometry has at least one LOD level, and reset the current LOD level
    mOriginalLodLevels.resize(mOriginalGeometries.size());
    mLodLevels.resize(mGeometries.size());
    
    for (unsigned i = 0; i < mOriginalGeometries.size(); ++i)
    {
        if (!mOriginalGeometries[i].size())
            mOriginalGeometries[i].resize(1);
        mOriginalLodLevels[i] = 0;
    }
    
    for (unsigned i = 0; i < mGeometries.size(); ++i)
    {
        if (!mGeometries[i].size())
            mGeometries[i].resize(1);
        mLodLevels[i] = 0;
    }
    
    // Find out the real LOD levels on next geometry update
    mLodLevelsDirty = true;
}

void InstancedModel::calculateLodLevels()
{
    for (unsigned i = 0; i < mOriginalGeometries.size(); ++i)
    {
        unsigned j;
        for (j = 1; j < mOriginalGeometries[i].size(); ++j)
        {
            if ((mOriginalGeometries[i][j]) && (mLodDistance <= mOriginalGeometries[i][j]->getLodDistance()))
                break;
        }
        mOriginalLodLevels[i] = j - 1;
    }
    
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

void InstancedModel::handleModelReloadFinished(StringHash eventType, VariantMap& eventData)
{
    Model* currentModel = mModel;
    mModel = 0; // Set null to allow to be re-set
    setModel(currentModel);
}
