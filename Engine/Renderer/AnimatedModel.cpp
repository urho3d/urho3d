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
#include "AnimatedModel.h"
#include "Animation.h"
#include "AnimationState.h"
#include "Camera.h"
#include "DebugRenderer.h"
#include "Geometry.h"
#include "IndexBuffer.h"
#include "Log.h"
#include "Material.h"
#include "Octree.h"
#include "OctreeQuery.h"
#include "Profiler.h"
#include "Renderer.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "VertexBuffer.h"

#include <algorithm>

#include "DebugNew.h"

static bool compareAnimationOrder(AnimationState* lhs, AnimationState* rhs)
{
    return lhs->getPriority() < rhs->getPriority();
}

AnimatedModel::AnimatedModel(Octant* octant, const std::string& name) :
    StaticModel(NODE_ANIMATEDMODEL, octant, name),
    mAnimationLodFrameNumber(M_MAX_UNSIGNED),
    mAnimationLodBias(1.0f),
    mAnimationLodTimer(-1.0f),
    mAnimationLodDistance(0.0f),
    mInvisibleLodFactor(0.0f),
    mLocalAnimation(false),
    mAnimationDirty(true),
    mAnimationOrderDirty(true),
    mMorphsDirty(true)
{
}

AnimatedModel::~AnimatedModel()
{
    removeAllAnimationStates();
}

void AnimatedModel::save(Serializer& dest)
{
    // Write GeometryNode properties
    GeometryNode::save(dest);
    
    // Write StaticModel properties
    dest.writeStringHash(getResourceHash(mModel));
    
    dest.writeVLE(mMaterials.size());
    for (unsigned i = 0; i < mMaterials.size(); ++i)
        dest.writeStringHash(getResourceHash(mMaterials[i]));
    
    // Write skeletal animation properties
    dest.writeFloat(mAnimationLodBias);
    dest.writeFloat(mInvisibleLodFactor);
    dest.writeBool(mLocalAnimation);
    // If this is the predicted component save, and local animation is enabled, do not store animation data
    bool localAnimation = (isProxy()) && (mLocalAnimation) && (checkPrediction());
    if (!localAnimation)
    {
        dest.writeVLE(mAnimationStates.size());
        for (unsigned i = 0; i < mAnimationStates.size(); ++i)
        {
            AnimationState* state = mAnimationStates[i];
            state->save(dest);
        }
        
        // Write morph properties
        dest.writeVLE(mMorphs.size());
        for (unsigned i = 0; i < mMorphs.size(); ++i)
            dest.writeFloat(mMorphs[i].mWeight);
    }
    else
    {
        dest.writeVLE(0);
        dest.writeVLE(0);
    }
}

void AnimatedModel::load(Deserializer& source, ResourceCache* cache)
{
    // Read GeometryNode properties
    GeometryNode::load(source, cache);
    
    // Read StaticModel properties
    // Note: can not use StaticModel::load() because we need to set the skeleton
    setModel(cache->getResource<Model>(source.readStringHash()));
    
    unsigned numMaterials = source.readVLE();
    for (unsigned i = 0; i < numMaterials; ++i)
        setMaterial(i, cache->getResource<Material>(source.readStringHash()));
    
    // Read skeletal animation properties
    // If this is the predicted component load, and local animation is enabled, do not overwrite the animations
    mAnimationLodBias = source.readFloat();
    mInvisibleLodFactor = source.readFloat();
    mLocalAnimation = source.readBool();
    bool localAnimation = (isProxy()) && (mLocalAnimation) && (checkPrediction());
    std::set<StringHash> processed;
    unsigned numAnimationStates = source.readVLE();
    for (unsigned i = 0; i < numAnimationStates; ++i)
    {
        StringHash animation = source.readStringHash();
        AnimationState* newState = addAnimationState(cache->getResource<Animation>(animation));
        newState->load(source);
        processed.insert(animation);
    }
    if (!localAnimation)
        removeExtraAnimations(processed);
    
    // Read morph properties
    unsigned numMorphs = source.readVLE();
    for (unsigned i = 0; i < numMorphs; ++i)
        setMorphWeight(i, source.readFloat());
}

void AnimatedModel::saveXML(XMLElement& dest)
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
    
    // Write skeletal animation properties
    XMLElement lodElem = dest.getChildElement("lod");
    lodElem.setFloat("animlodbias", mAnimationLodBias);
    lodElem.setFloat("invisiblelodfactor", mInvisibleLodFactor);
    lodElem.setBool("localanimation", mLocalAnimation);
    for (unsigned i = 0; i < mAnimationStates.size(); ++i)
    {
        XMLElement animationElem = dest.createChildElement("animation");
        mAnimationStates[i]->saveXML(animationElem);
    }
    
    // Write morph properties
    for (unsigned i = 0; i < mMorphs.size(); ++i)
    {
        XMLElement morphElem = dest.createChildElement("morph");
        morphElem.setInt("index", i);
        morphElem.setFloat("weight", mMorphs[i].mWeight);
    }
}

void AnimatedModel::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Read GeometryNode properties
    GeometryNode::loadXML(source, cache);
    
    // Read StaticModel properties
    // Note: can not use StaticModel::loadXML() because we need to set the skeleton
    XMLElement modelElem = source.getChildElement("model");
    setModel(cache->getResource<Model>(modelElem.getString("name")));
    
    XMLElement materialElem = source.getChildElement("material");
    while (materialElem)
    {
        unsigned index = materialElem.getInt("index");
        setMaterial(index, cache->getResource<Material>(materialElem.getString("name")));
        materialElem = materialElem.getNextElement("material");
    }
    
    // Read skeletal animation properties
    XMLElement lodElem = source.getChildElement("lod");
    mAnimationLodBias = lodElem.getFloat("animlodbias");
    mInvisibleLodFactor = lodElem.getFloat("invisiblelodfactor");
    mLocalAnimation = lodElem.getBool("localanimation");
    removeAllAnimationStates();
    XMLElement animationElem = source.getChildElement("animation");
    while (animationElem)
    {
        AnimationState* newState = addAnimationState(cache->getResource<Animation>(animationElem.getString("name")));
        newState->loadXML(animationElem);
        animationElem = animationElem.getNextElement("animation");
    }
    
    // Read morph properties
    XMLElement morphElem = source.getChildElement("morph");
    while (morphElem)
    {
        unsigned index = morphElem.getInt("index");
        setMorphWeight(index, morphElem.getFloat("weight"));
        morphElem = morphElem.getNextElement("morph");
    }
}

bool AnimatedModel::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    // Write GeometryNode properties and see if there were any changes
    bool prevBits = GeometryNode::writeNetUpdate(dest, destRevision, baseRevision, info);
    
    // Build bitmask of changed properties
    unsigned char bits = 0;
    // Model
    checkStringHash(getResourceHash(mModel), baseRevision, bits, 1);
    // Materials
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
    // Animation LOD bias and invisible animation LOD distance factor
    checkFloat(mAnimationLodBias, 1.0f, baseRevision, bits, 4);
    checkFloat(mInvisibleLodFactor, 0.0f, baseRevision, bits, 4);
    // Animations
    unsigned numBaseAnimations = baseRevision.getSize() ? baseRevision.readVLE() : 0;
    if (mAnimationStates.size() != numBaseAnimations)
        bits |= 8;
    static std::vector<unsigned char> animBits;
    animBits.resize(mAnimationStates.size());
    // Assume that animations are new ie. require update of all fields
    for (unsigned i = 0; i < mAnimationStates.size(); ++i)
        animBits[i] = 1 | 2 | 4 | 8 | 16 | 32;
    for (unsigned i = 0; i < numBaseAnimations; ++i)
    {
        StringHash animation = baseRevision.readStringHash();
        StringHash startBone = baseRevision.readStringHash();
        bool looped = baseRevision.readBool();
        float weight = baseRevision.readFloat();
        float time = baseRevision.readFloat();
        int priority = baseRevision.readUByte();
        bool useNlerp = baseRevision.readBool();
        
        bool found = false;
        for (unsigned j = 0; j < mAnimationStates.size(); ++j)
        {
            AnimationState* state = mAnimationStates[j];
            if (state->getAnimation()->getNameHash() == animation)
            {
                // If animation exists in base state, update only the necessary properties
                found = true;
                animBits[j] = 0;
                
                if (startBone != state->getStartBone()->getNameHash())
                    animBits[j] |= 1;
                if (looped != state->isLooped())
                    animBits[j] |= 2;
                if (weight != state->getWeight())
                    animBits[j] |= 4;
                if (time != state->getTime())
                    animBits[j] |= 8;
                if (priority != state->getPriority())
                    animBits[j] |= 16;
                if (useNlerp != state->getUseNlerp())
                    animBits[j] |= 32;
                if (animBits[j])
                    bits |= 8;
                break;
            }
        }
        // If not found, the number of animations has stayed same, but the animations are different
        if (!found)
            bits |= 8;
    }
    // Morphs
    unsigned numBaseMorphs = baseRevision.getSize() ? baseRevision.readVLE() : 0;
    if (mMorphs.size() != numBaseMorphs)
        bits |= 16;
    for (unsigned i = 0; i < numBaseMorphs; ++i)
    {
        if (i < mMorphs.size())
            checkUByte((unsigned char)(mMorphs[i].mWeight * 255.0f), baseRevision, bits, 16);
        else
            baseRevision.readUByte();
    }
    // Local animation flag
    checkBool(mLocalAnimation, false, baseRevision, bits, 32);
    
    // If local animation, do not send even if changed. It is slightly unoptimal to first check, then disable, but it ensures
    // that the base revision data stays the same (otherwise out of bounds reads might result when toggling local animation)
    if ((mLocalAnimation) && (checkPrediction(info.mConnection)))
        bits &= ~(8 | 16);
    
    // Update replication state fully, and network stream by delta
    dest.writeUByte(bits);
    writeStringHashDelta(getResourceHash(mModel), dest, destRevision, bits & 1);
    writeVLEDelta(mMaterials.size(), dest, destRevision, bits & 2);
    for (unsigned i = 0; i < mMaterials.size(); ++i)
        writeStringHashDelta(getResourceHash(mMaterials[i]), dest, destRevision, bits & 2);
    writeFloatDelta(mAnimationLodBias, dest, destRevision, bits & 4);
    writeFloatDelta(mInvisibleLodFactor, dest, destRevision, bits & 4);
    // Write all animations to the base replication state
    destRevision.writeVLE(mAnimationStates.size());
    for (unsigned i = 0; i < mAnimationStates.size(); ++i)
    {
        AnimationState* state = mAnimationStates[i];
        destRevision.writeStringHash(state->getAnimation()->getNameHash());
        destRevision.writeStringHash(state->getStartBone()->getNameHash());
        destRevision.writeBool(state->isLooped());
        destRevision.writeFloat(state->getWeight());
        destRevision.writeFloat(state->getTime());
        destRevision.writeUByte(state->getPriority());
        destRevision.writeBool(state->getUseNlerp());
    }
    // Then write delta of animations to the net stream
    if (bits & 8)
    {
        dest.writeVLE(mAnimationStates.size());
        for (unsigned i = 0; i < mAnimationStates.size(); ++i)
        {
            AnimationState* state = mAnimationStates[i];
            dest.writeStringHash(state->getAnimation()->getNameHash());
            dest.writeUByte(animBits[i]);
            if (animBits[i] & 1)
                dest.writeStringHash(state->getStartBone()->getNameHash());
            if (animBits[i] & 2)
                dest.writeBool(state->isLooped());
            if (animBits[i] & 4)
                dest.writeUByte((unsigned char)(state->getWeight() * 255.0f));
            if (animBits[i] & 8)
                dest.writeUShort((unsigned short)(state->getTime() * 65535.0f / state->getAnimation()->getLength()));
            if (animBits[i] & 16)
                dest.writeUByte(state->getPriority());
            if (animBits[i] & 32)
                dest.writeBool(state->getUseNlerp());
        }
    }
    writeVLEDelta(mMorphs.size(), dest, destRevision, bits & 16);
    for (unsigned i = 0; i < mMorphs.size(); ++i)
        writeUByteDelta((unsigned char)(mMorphs[i].mWeight * 255.0f), dest, destRevision, bits & 16);
    writeBoolDelta(mLocalAnimation, dest, destRevision, bits & 32);
    
    return prevBits || (bits != 0);
}

void AnimatedModel::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
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
    if (bits & 4)
    {
        mAnimationLodBias = source.readFloat();
        mInvisibleLodFactor = source.readFloat();
    }
    if (bits & 8)
    {
        unsigned numAnimations = source.readVLE();
        std::set<StringHash> processed;
        for (unsigned i = 0; i < numAnimations; ++i)
        {
            StringHash animation = source.readStringHash();
            unsigned char animBits = source.readUByte();
            processed.insert(animation);
            
            // Find the animation state. If not found, create new
            AnimationState* state = getAnimationState(animation);
            bool newState = false;
            if (!state)
            {
                state = addAnimationState(cache->getResource<Animation>(animation));
                newState = true;
            }
            
            if (state)
            {
                if (animBits & 1)
                    state->setStartBone(mSkeleton.getBone(source.readStringHash()));
                if (animBits & 2)
                    state->setLooped(source.readBool());
                if (animBits & 4)
                    state->setWeight(source.readUByte() / 255.0f);
                if (animBits & 8)
                    state->setTime(source.readUShort() * state->getAnimation()->getLength() / 65535.0f);
                if (animBits & 16)
                    state->setPriority(source.readUByte());
                if (animBits & 32)
                    state->setUseNlerp(source.readBool());
                
                // If state is new, interpolate directly to the end
                if (newState)
                    state->interpolate(true, mEntity->getScene()->getInterpolationLerpFactor());
            }
            else
            {
                // If state could not be added, just read the data to avoid desyncing the stream
                if (animBits & 1)
                    source.readStringHash();
                if (animBits & 2)
                    source.readBool();
                if (animBits & 4)
                    source.readUByte();
                if (animBits & 8)
                    source.readUShort();
                if (animBits & 16)
                    source.readUByte();
                if (animBits & 32)
                    source.readBool();
            }
        }
        
        removeExtraAnimations(processed);
    }
    if (bits & 16)
    {
        unsigned numMorphs = source.readVLE();
        for (unsigned i = 0; i < numMorphs; ++i)
            setMorphWeight(i, source.readUByte() / 255.0f);
    }
    readBoolDelta(mLocalAnimation, source, bits & 32);
}

void AnimatedModel::interpolate(bool snapToEnd)
{
    Node::interpolate(snapToEnd);
    
    float t = mEntity->getScene()->getInterpolationLerpFactor();
    
    for (std::vector<AnimationState*>::iterator i = mAnimationStates.begin(); i != mAnimationStates.end(); ++i)
        (*i)->interpolate(snapToEnd, t);
}

void AnimatedModel::getResourceRefs(std::vector<Resource*>& dest)
{
    StaticModel::getResourceRefs(dest);
    for (unsigned i = 0; i < mAnimationStates.size(); ++i)
        dest.push_back(mAnimationStates[i]->getAnimation());
}

void AnimatedModel::processRayQuery(RayOctreeQuery& query, float initialDistance)
{
    // If no bones or no bone-level testing, use the GeometryNode test
    if ((!mSkeleton.getNumBones()) || (query.mLevel < RAY_AABB))
    {
        GeometryNode::processRayQuery(query, initialDistance);
        return;
    }
    
    PROFILE(AnimatedModel_Raycast);
    
    const std::vector<SharedPtr<Bone> >& bones = mSkeleton.getBones();
    Sphere boneSphere;
    RayQueryLevel level = query.mLevel;
    
    for (unsigned i = 0; i < bones.size(); ++i)
    {
        Bone* bone = bones[i];
        unsigned collisionMask = bone->getCollisionMask();
        
        // Use hitbox if available
        if (collisionMask & BONECOLLISION_BOX)
        {
            // Do an initial crude test using the bone's AABB
            const Matrix4x3& transform = bone->getWorldTransform();
            const BoundingBox& box = bone->getBoundingBox();
            float distance = box.getTransformed(transform).getDistance(query.mRay);
            if (distance < query.mMaxDistance)
            {
                if (level == RAY_AABB)
                {
                    RayQueryResult result;
                    result.mNode = this;
                    result.mDistance = distance;
                    result.mSubObject = i;
                    query.mResult.push_back(result);
                }
                else
                {
                    // Follow with an OBB test if required
                    Matrix4x3 inverse = transform.getInverse();
                    Ray localRay(inverse * query.mRay.mOrigin, inverse * Vector4(query.mRay.mDirection, 0.0f));
                    distance = box.getDistance(localRay);
                    if (distance < query.mMaxDistance)
                    {
                        RayQueryResult result;
                        result.mNode = this;
                        result.mDistance = distance;
                        result.mSubObject = i;
                        query.mResult.push_back(result);
                    }
                }
            }
        }
        else if (collisionMask & BONECOLLISION_SPHERE)
        {
            boneSphere.mCenter = bone->getWorldPosition();
            boneSphere.mRadius = bone->getRadius();
            float distance = boneSphere.getDistance(query.mRay);
            if (distance < query.mMaxDistance)
            {
                RayQueryResult result;
                result.mNode = this;
                result.mSubObject = i;
                result.mDistance = distance;
                query.mResult.push_back(result);
            }
        }
    }
}

void AnimatedModel::updateNode(const FrameInfo& frame)
{
    // Update animation here
    if ((!mAnimationDirty) && (!mAnimationOrderDirty))
        return;
    
    // If node was invisible last frame, need to decide animation LOD distance here
    // If headless, retain the current animation distance (should be 0)
    if ((frame.mCamera) && (abs((int)frame.mFrameNumber - (int)mAnimationLodFrameNumber) > 1))
    {
        if (mInvisibleLodFactor == 0.0f)
            return;
        float distance = frame.mCamera->getDistance(getWorldPosition());
        // If distance is greater than draw distance, no need to update at all
        if ((mDrawDistance != 0.0f) && (distance > mDrawDistance))
            return;
        // Multiply the distance by a constant so that invisible nodes don't update that often
        static const Vector3 dotScale(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);
        float scale = getWorldBoundingBox().getSize().dotProduct(dotScale);
        mAnimationLodDistance = frame.mCamera->getLodDistance(distance, scale, mLodBias) * mInvisibleLodFactor;
    }
    
    updateAnimation(frame);
}

void AnimatedModel::updateDistance(const FrameInfo& frame)
{
    mDistance = frame.mCamera->getDistance(getWorldPosition());
    
    static const Vector3 dotScale(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);
    float scale = getWorldBoundingBox().getSize().dotProduct(dotScale);
    float newLodDistance = frame.mCamera->getLodDistance(mDistance, scale, mLodBias);
    
    // If model is rendered from several views, use the minimum LOD distance for animation LOD
    if (frame.mFrameNumber != mAnimationLodFrameNumber)
    {
        mAnimationLodDistance = newLodDistance;
        mAnimationLodFrameNumber = frame.mFrameNumber;
    }
    else
        mAnimationLodDistance = min(mAnimationLodDistance, newLodDistance);
    
    if (newLodDistance != mLodDistance)
    {
        mLodDistance = newLodDistance;
        mLodLevelsDirty = true;
    }
}

void AnimatedModel::updateGeometry(const FrameInfo& frame, Renderer* renderer)
{
    if (mLodLevelsDirty)
        calculateLodLevels();
    
    if ((mMorphsDirty) && (mMorphs.size()))
        updateMorphs();
    
    if ((mSkeleton.getNumBones()) && (mSkeleton.getRootBone()->isSkinningDirty()))
        updateSkinning();
}

bool AnimatedModel::getVertexShaderParameter(unsigned batchIndex, VSParameter parameter, const float** data, unsigned* count)
{
    if ((parameter == VSP_MODELSKINMATRICES) && (mSkinMatrices.size()))
    {
        // Check if model has per-geometry bone mappings
        if ((mGeometrySkinMatrices.size()) && (mGeometrySkinMatrices[batchIndex].size()))
        {
            *count = mGeometrySkinMatrices[batchIndex].size() * 12;
            *data = mGeometrySkinMatrices[batchIndex][0].getData();
        }
        // If not, use the global skin matrices
        else
        {
            *count = mSkinMatrices.size() * 12;
            *data = mSkinMatrices[0].getData();
        }
        
        return true;
    }
    
    return false;
}

void AnimatedModel::drawDebugGeometry(DebugRenderer* debug)
{
    debug->addBoundingBox(getWorldBoundingBox(), Color(0.0f, 1.0f, 0.0f), false);
    debug->addSkeleton(mSkeleton, Color(0.75f, 0.75f, 0.75f), false);
}

void AnimatedModel::setModel(Model* model)
{
    if (model == mModel)
        return;
    
    PROFILE(AnimatedModel_SetModel);
    
    if (!model)
        return;
    
    mModel = model;
    
    // Copy the subgeometry & LOD level structure
    setNumGeometries(model->getNumGeometries());
    const std::vector<std::vector<SharedPtr<Geometry> > >& geometries = model->getGeometries();
    for (unsigned i = 0; i < geometries.size(); ++i)
        mGeometries[i] = geometries[i];
    
    // Copy geometry bone mappings
    const std::vector<std::vector<unsigned> >& geometryBoneMappings = model->getGeometryBoneMappings();
    mGeometryBoneMappings.clear();
    for (unsigned i = 0; i < geometryBoneMappings.size(); ++i)
        mGeometryBoneMappings.push_back(geometryBoneMappings[i]);
    
    // Copy morphs
    mMorphVertexBuffers.clear();
    mMorphs.clear();
    const std::vector<ModelMorph>& morphs = model->getMorphs();
    for (unsigned i = 0; i < morphs.size(); ++i)
    {
        ModelMorph newMorph;
        newMorph.mName = morphs[i].mName;
        newMorph.mNameHash = morphs[i].mNameHash;
        newMorph.mWeight = 0.0f;
        newMorph.mBuffers = morphs[i].mBuffers;
        mMorphs.push_back(newMorph);
    }
    
    // If model has morphs, must clone all geometries & vertex buffers that refer to morphable vertex data
    if (morphs.size())
    {
        cloneGeometries();
        markMorphsDirty();
    }
    
    // Copy bounding box & skeleton
    setBoundingBox(model->getBoundingBox());
    setSkeleton(model->getSkeleton());
}

AnimationState* AnimatedModel::addAnimationState(Animation* animation)
{
    if (!animation)
        return 0;
    
    if (!mSkeleton.getNumBones())
        return 0;
    
    // Check for not adding twice
    AnimationState* existing = getAnimationState(animation);
    if (existing)
        return existing;
    
    AnimationState* newState = new AnimationState(this, animation);
    mAnimationStates.push_back(newState);
    markAnimationOrderDirty();
    return newState;
}

void AnimatedModel::removeAnimationState(Animation* animation)
{
    if (animation)
        removeAnimationState(animation->getNameHash());
}

void AnimatedModel::removeAnimationState(const std::string& animationName)
{
    removeAnimationState(StringHash(animationName));
}

void AnimatedModel::removeAnimationState(StringHash animationNameHash)
{
    for (std::vector<AnimationState*>::iterator i = mAnimationStates.begin(); i != mAnimationStates.end(); ++i)
    {
        AnimationState* state = *i;
        Animation* animation = state->getAnimation();
        // Check both the animation and the resource name
        if ((animation->getNameHash() == animationNameHash) || (animation->getAnimationNameHash() == animationNameHash))
        {
            // If animation is still interpolating, do not remove immediately, but set target weight to zero
            if ((isProxy()) && (state->isInterpolating()))
                state->setWeight(0.0f);
            else
            {
                delete state;
                mAnimationStates.erase(i);
                markAnimationDirty();
            }
            return;
        }
    }
}

void AnimatedModel::removeAnimationState(AnimationState* state)
{
    for (std::vector<AnimationState*>::iterator i = mAnimationStates.begin(); i != mAnimationStates.end(); ++i)
    {
        if (*i == state)
        {
            // If animation is still interpolating, do not remove immediately, but set target weight to zero
            if ((isProxy()) && (state->isInterpolating()))
                state->setWeight(0.0f);
            else
            {
                delete state;
                mAnimationStates.erase(i);
                markAnimationDirty();
            }
            return;
        }
    }
}

void AnimatedModel::removeAllAnimationStates()
{
    for (std::vector<AnimationState*>::iterator i = mAnimationStates.begin(); i != mAnimationStates.end(); ++i)
        delete *i;
    
    mAnimationStates.clear();
    markAnimationDirty();
}

void AnimatedModel::setAnimationLodBias(float bias)
{
    mAnimationLodBias = max(bias, 0.0f);
}

void AnimatedModel::setInvisibleLodFactor(float factor)
{
    if (factor < 0.0f)
        factor = 0.0f;
    else if ((factor != 0.0f) && (factor < 1.0f))
        factor = 1.0f;
    mInvisibleLodFactor = factor;
}

void AnimatedModel::setLocalAnimation(bool enable)
{
    mLocalAnimation = enable;
}

void AnimatedModel::setMorphWeight(unsigned index, float weight)
{
    if (index >= mMorphs.size())
        return;
    
    weight = clamp(weight, 0.0f, 1.0f);
    
    if (weight != mMorphs[index].mWeight)
    {
        mMorphs[index].mWeight = weight;
        markMorphsDirty();
    }
}

void AnimatedModel::setMorphWeight(const std::string& name, float weight)
{
    weight = clamp(weight, 0.0f, 1.0f);
    
    for (std::vector<ModelMorph>::iterator i = mMorphs.begin(); i != mMorphs.end(); ++i)
    {
        if (i->mName == name)
        {
            if (weight != i->mWeight)
            {
                i->mWeight = weight;
                markMorphsDirty();
            }
            return;
        }
    }
}

void AnimatedModel::setMorphWeight(StringHash nameHash, float weight)
{
    weight = clamp(weight, 0.0f, 1.0f);
    
    for (std::vector<ModelMorph>::iterator i = mMorphs.begin(); i != mMorphs.end(); ++i)
    {
        if (i->mNameHash == nameHash)
        {
            if (weight != i->mWeight)
            {
                i->mWeight = weight;
                markMorphsDirty();
            }
            return;
        }
    }
}

void AnimatedModel::resetMorphWeights()
{
    for (std::vector<ModelMorph>::iterator i = mMorphs.begin(); i != mMorphs.end(); ++i)
        i->mWeight = 0.0f;
    
    markMorphsDirty();
}

void AnimatedModel::syncAnimation(AnimatedModel* srcNode)
{
    if (!srcNode)
        return;
    
    // Make sure the animation proceeds at the same rate as in the source
    mAnimationLodBias = srcNode->mAnimationLodBias;
    mAnimationLodDistance = srcNode->mAnimationLodDistance;
    mAnimationLodFrameNumber = srcNode->mAnimationLodFrameNumber;
    
    const std::vector<AnimationState*>& srcStates = srcNode->getAnimationStates();
    std::set<Animation*> srcAnimations;
    
    for (unsigned i = 0; i < srcStates.size(); ++i)
    {
        AnimationState* src = srcStates[i];
        Animation* anim = src->getAnimation();
        srcAnimations.insert(anim);
        
        AnimationState* dest = getAnimationState(anim);
        if (!dest)
            dest = addAnimationState(anim);
        dest->sync(src);
    }
    
    // Check for extra states in destination and remove them
    if (mAnimationStates.size() > srcStates.size())
    {
        for (unsigned i = 0; i < mAnimationStates.size(); ++i)
        {
            AnimationState* state = mAnimationStates[i];
            if (srcAnimations.find(state->getAnimation()) == srcAnimations.end())
                removeAnimationState(state);
        }
    }
}

void AnimatedModel::syncMorphs(AnimatedModel* srcNode)
{
    for (unsigned i = 0; i < mMorphs.size(); ++i)
    {
        float srcWeight = srcNode->getMorphWeight(mMorphs[i].mName);
        setMorphWeight(i, srcWeight);
    }
}

float AnimatedModel::getMorphWeight(unsigned index) const
{
    if (index >= mMorphs.size())
        return 0.0f;
    
    return mMorphs[index].mWeight;
}

float AnimatedModel::getMorphWeight(const std::string& name) const
{
    for (std::vector<ModelMorph>::const_iterator i = mMorphs.begin(); i != mMorphs.end(); ++i)
    {
        if (i->mName == name)
            return i->mWeight;
    }
    
    return 0.0f;
}

float AnimatedModel::getMorphWeight(StringHash nameHash) const
{
    for (std::vector<ModelMorph>::const_iterator i = mMorphs.begin(); i != mMorphs.end(); ++i)
    {
        if (i->mNameHash == nameHash)
            return i->mWeight;
    }
    
    return 0.0f;
}

AnimationState* AnimatedModel::getAnimationState(Animation* animation) const
{
    for (std::vector<AnimationState*>::const_iterator i = mAnimationStates.begin(); i != mAnimationStates.end(); ++i)
    {
        if ((*i)->getAnimation() == animation)
            return *i;
    }
    
    return 0;
}

AnimationState* AnimatedModel::getAnimationState(const std::string& animationName) const
{
    for (std::vector<AnimationState*>::const_iterator i = mAnimationStates.begin(); i != mAnimationStates.end(); ++i)
    {
        Animation* animation = (*i)->getAnimation();
        
        // Check both the animation and the resource name
        if ((animation->getName() == animationName) || (animation->getAnimationName() == animationName))
            return *i;
    }
    
    return 0;
}

AnimationState* AnimatedModel::getAnimationState(StringHash animationNameHash) const
{
    for (std::vector<AnimationState*>::const_iterator i = mAnimationStates.begin(); i != mAnimationStates.end(); ++i)
    {
        Animation* animation = (*i)->getAnimation();
        
        // Check both the animation and the resource name
        if ((animation->getNameHash() == animationNameHash) || (animation->getAnimationNameHash() == animationNameHash))
            return *i;
    }
    
    return 0;
}

AnimationState* AnimatedModel::getAnimationState(unsigned index) const
{
    if (index >= mAnimationStates.size())
        return 0;
    return mAnimationStates[index];
}

void AnimatedModel::setSkeleton(const Skeleton& skeleton)
{
    PROFILE(AnimatedModel_SetSkeleton);
    
    removeAllAnimationStates();
    mSkeleton.define(skeleton.getBones());
    
    // Parent the root bone to the this node, so that objects can further be properly attached to bones
    Bone* rootBone = mSkeleton.getRootBone();
    if (rootBone)
        addChild(rootBone);
    
    // Reserve space for skinning matrices
    mSkinMatrices.resize(mSkeleton.getNumBones());
    refreshGeometryBoneMappings();
}

void AnimatedModel::onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox)
{
    if (!mSkeleton.getNumBones())
        worldBoundingBox = mBoundingBox.getTransformed(getWorldTransform());
    else
    {
        // If has bones, update world bounding box based on them
        worldBoundingBox.mDefined = false;
        
        const std::vector<SharedPtr<Bone> >& bones = mSkeleton.getBones();
        for (std::vector<SharedPtr<Bone> >::const_iterator i = bones.begin(); i != bones.end(); ++i)
        {
            Bone* bone = *i;
            unsigned collisionMask = bone->getCollisionMask();
            
            // Use hitbox if available. If not, use only half of the sphere radius
            if (collisionMask & BONECOLLISION_BOX)
                worldBoundingBox.merge(bone->getBoundingBox().getTransformed(bone->getWorldTransform()));
            else if (collisionMask & BONECOLLISION_SPHERE)
                worldBoundingBox.merge(Sphere(bone->getWorldPosition(), bone->getRadius() * 0.5f));
        }
    }
}

void AnimatedModel::markAnimationDirty()
{
    mAnimationDirty = true;
    // Mark for octree update, as animation is updated before octree reinsertion
    if (mOctant)
        mOctant->getRoot()->markNodeForUpdate(this);
}

void AnimatedModel::markAnimationOrderDirty()
{
    mAnimationOrderDirty = true;
    // Mark for octree update, as animation is updated before octree reinsertion
    if (mOctant)
        mOctant->getRoot()->markNodeForUpdate(this);
}

void AnimatedModel::markMorphsDirty()
{
    mMorphsDirty = true;
}

void AnimatedModel::cloneGeometries()
{
    PROFILE(AnimatedModel_CloneGeometries);
    
    // Clone vertex buffers as necessary
    const std::vector<SharedPtr<VertexBuffer> >& originalVertexBuffers = mModel->getVertexBuffers();
    std::map<VertexBuffer*, SharedPtr<VertexBuffer> > clonedVertexBuffers;
    
    mMorphVertexBuffers.resize(originalVertexBuffers.size());
    
    for (unsigned i = 0; i < originalVertexBuffers.size(); ++i)
    {
        VertexBuffer* original = originalVertexBuffers[i];
        if (original->hasMorphRange())
        {
            SharedPtr<VertexBuffer> clone(new VertexBuffer(original->getRenderer()));
            clone->setSize(original->getVertexCount(), original->getElementMask());
            void* originalData = original->lock(0, original->getVertexCount(), LOCK_NORMAL);
            clone->setData(originalData);
            original->unlock();
            
            clone->setMorphRange(original->getMorphRangeStart(), original->getMorphRangeCount());
            clone->setMorphRangeResetData(original->getMorphRangeResetData());
            
            clonedVertexBuffers[original] = clone;
            mMorphVertexBuffers[i] = clone;
        }
    }
    
    // Geometries will always be cloned fully. They contain only references to buffer, so they are relatively light
    for (unsigned i = 0; i < mGeometries.size(); ++i)
    {
        for (unsigned j = 0; j < mGeometries[i].size(); ++j)
        {
            SharedPtr<Geometry> original = mGeometries[i][j];
            
            const std::vector<SharedPtr<VertexBuffer> >& originalBuffers = original->getVertexBuffers();
            
            SharedPtr<Geometry> clone(new Geometry());
            clone->setNumVertexBuffers(originalVertexBuffers.size());
            for (unsigned k = 0; k < originalVertexBuffers.size(); ++k)
            {
                VertexBuffer* originalBuffer = originalBuffers[k];
                if (clonedVertexBuffers.find(originalBuffer) != clonedVertexBuffers.end())
                    clone->setVertexBuffer(k, clonedVertexBuffers[originalBuffer], original->getVertexElementMask(k));
                else
                    clone->setVertexBuffer(k, originalBuffers[k], original->getVertexElementMask(k));
            }
            
            clone->setIndexBuffer(original->getIndexBuffer());
            clone->setDrawRange(original->getPrimitiveType(), original->getIndexStart(), original->getIndexCount());
            clone->setLodDistance(original->getLodDistance());
            
            mGeometries[i][j] = clone;
        }
    }
}

void AnimatedModel::refreshGeometryBoneMappings()
{
    mGeometrySkinMatrices.clear();
    mGeometrySkinMatrixPtrs.clear();
    
    if (!mGeometryBoneMappings.size())
        return;
    
    // Check if all mappings are empty, then we do not need to use mapped skinning
    bool allEmpty = true;
    for (unsigned i = 0; i < mGeometryBoneMappings.size(); ++i)
        if (mGeometryBoneMappings[i].size())
            allEmpty = false;
    
    if (allEmpty)
        return;
    
    // Reserve space for per-geometry skinning matrices
    mGeometrySkinMatrices.resize(mGeometryBoneMappings.size());
    for (unsigned i = 0; i < mGeometryBoneMappings.size(); ++i)
        mGeometrySkinMatrices[i].resize(mGeometryBoneMappings[i].size());
    
    // Build original-to-skinindex matrix pointer mapping for fast copying
    // Note: at this point layout of mGeometrySkinMatrices cannot be modified or pointers become invalid
    mGeometrySkinMatrixPtrs.resize(mSkeleton.getNumBones());
    for (unsigned i = 0; i < mGeometryBoneMappings.size(); ++i)
    {
        for (unsigned j = 0; j < mGeometryBoneMappings[i].size(); ++j)
            mGeometrySkinMatrixPtrs[mGeometryBoneMappings[i][j]].push_back(&mGeometrySkinMatrices[i][j]);
    }
}

void AnimatedModel::updateAnimation(const FrameInfo& frame)
{
    // If using animation LOD, accumulate time and see if it is time to update
    if ((mAnimationLodBias > 0.0f) && (mAnimationLodDistance > 0.0f))
    {
        // Check for first time update
        if (mAnimationLodTimer >= 0.0f)
        {
            mAnimationLodTimer += mAnimationLodBias * frame.mTimeStep * ANIMATION_LOD_BASESCALE;
            if (mAnimationLodTimer >= mAnimationLodDistance)
                mAnimationLodTimer = fmodf(mAnimationLodTimer, mAnimationLodDistance);
            else
                return;
        }
        else
            mAnimationLodTimer = 0.0f;
    }
    
    PROFILE(AnimatedModel_UpdateAnimation);
    
    // Make sure animations are in ascending priority order
    if (mAnimationOrderDirty)
    {
        std::sort(mAnimationStates.begin(), mAnimationStates.end(), compareAnimationOrder);
        mAnimationOrderDirty = false;
    }
    
    // Reset skeleton, then apply all animations
    mSkeleton.reset();
    for (std::vector<AnimationState*>::iterator i = mAnimationStates.begin(); i != mAnimationStates.end(); ++i)
        (*i)->apply();
    
    // Animation has changed the bounding box: mark node for octree reinsertion
    VolumeNode::onMarkedDirty();
    mAnimationDirty = false;
}

void AnimatedModel::updateSkinning()
{
    PROFILE(AnimatedModel_UpdateSkinning);
    
    // Note: the model's world transform will be baked in the skin matrices
    const std::vector<SharedPtr<Bone > >& bones = mSkeleton.getBones();
    
    // Skinning with global matrices only
    if (!mGeometrySkinMatrices.size())
    {
        for (unsigned i = 0; i < bones.size(); ++i)
        {
            Bone* bone = bones[i];
            
            if (bone->isSkinningDirty())
            {
                mSkinMatrices[i] = bone->getWorldTransform() * bone->getOffsetMatrix();
                bone->clearSkinningDirty();
            }
        }
    }
    // Skinning with per-geometry matrices
    else
    {
        for (unsigned i = 0; i < bones.size(); ++i)
        {
            Bone* bone = bones[i];
            
            if (bone->isSkinningDirty())
            {
                mSkinMatrices[i] = bone->getWorldTransform() * bone->getOffsetMatrix();
                
                // Copy the skin matrix to per-geometry matrices as needed
                for (unsigned j = 0; j < mGeometrySkinMatrixPtrs[i].size(); ++j)
                    *mGeometrySkinMatrixPtrs[i][j] = mSkinMatrices[i];
                
                bone->clearSkinningDirty();
            }
        }
    }
}

void AnimatedModel::updateMorphs()
{
    PROFILE(AnimatedModel_UpdateMorphs);
    
    if (mMorphs.size())
    {
        try
        {
            // Reset the morph data range from all morphable vertex buffers, then apply morphs
            for (unsigned i = 0; i < mMorphVertexBuffers.size(); ++i)
            {
                VertexBuffer* buffer = mMorphVertexBuffers[i];
                if (buffer)
                {
                    void* lockedMorphRange = buffer->lockMorphRange();
                    buffer->resetMorphRange(lockedMorphRange);
                    
                    for (unsigned j = 0; j < mMorphs.size(); ++j)
                    {
                        if (mMorphs[j].mWeight > 0.0f)
                        {
                            std::map<unsigned, VertexBufferMorph>::iterator k = mMorphs[j].mBuffers.find(i);
                            if (k != mMorphs[j].mBuffers.end())
                                applyMorph(buffer, lockedMorphRange, k->second, mMorphs[j].mWeight);
                        }
                    }
                    
                    buffer->unlock();
                }
            }
        }
        catch (...)
        {
        }
    }
    
    mMorphsDirty = false;
}

void AnimatedModel::applyMorph(VertexBuffer* buffer, void* lockedMorphRange, const VertexBufferMorph& morph, float weight)
{
    unsigned elementMask = morph.mElementMask;
    unsigned vertexCount = morph.mVertexCount;
    unsigned normalOffset = buffer->getElementOffset(ELEMENT_NORMAL);
    unsigned tangentOffset = buffer->getElementOffset(ELEMENT_TANGENT);
    unsigned morphRangeStart = buffer->getMorphRangeStart();
    unsigned vertexSize = buffer->getVertexSize();
    
    unsigned char* srcData = morph.mMorphData;
    unsigned char* destData = (unsigned char*)lockedMorphRange;
    
    while (vertexCount--)
    {
        unsigned vertexIndex = *((unsigned*)srcData) - morphRangeStart;
        srcData += sizeof(unsigned);
        
        if (elementMask & MASK_POSITION)
        {
            float* dest = (float*)(destData + vertexIndex * vertexSize);
            float* src = (float*)srcData;
            dest[0] += src[0] * weight;
            dest[1] += src[1] * weight;
            dest[2] += src[2] * weight;
            srcData += 3 * sizeof(float);
        }
        if (elementMask & MASK_NORMAL)
        {
            float* dest = (float*)(destData + vertexIndex * vertexSize + normalOffset);
            float* src = (float*)srcData;
            dest[0] += src[0] * weight;
            dest[1] += src[1] * weight;
            dest[2] += src[2] * weight;
            srcData += 3 * sizeof(float);
        }
        if (elementMask & MASK_TANGENT)
        {
            float* dest = (float*)(destData + vertexIndex * vertexSize + tangentOffset);
            float* src = (float*)srcData;
            dest[0] += src[0] * weight;
            dest[1] += src[1] * weight;
            dest[2] += src[2] * weight;
            srcData += 3 * sizeof(float);
        }
    }
}

void AnimatedModel::removeExtraAnimations(const std::set<StringHash>& animations)
{
    bool removedAny = false;
    for (std::vector<AnimationState*>::iterator i = mAnimationStates.begin(); i != mAnimationStates.end();)
    {
        AnimationState* state = *i;
        
        if (animations.find(state->getAnimation()->getNameHash()) == animations.end())
        {
            // If animation is still interpolating, do not remove immediately, but set target weight to zero
            if ((isProxy()) && (state->isInterpolating()))
            {
                state->setWeight(0.0f);
                ++i;
            }
            else
            {
                delete state;
                i = mAnimationStates.erase(i);
                removedAny = true;
            }
        }
        else
            ++i;
    }
    
    if (removedAny)
        markAnimationDirty();
}
