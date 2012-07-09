//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Batch.h"
#include "Camera.h"
#include "Context.h"
#include "DebugRenderer.h"
#include "DrawableEvents.h"
#include "Geometry.h"
#include "Graphics.h"
#include "IndexBuffer.h"
#include "Log.h"
#include "Material.h"
#include "MemoryBuffer.h"
#include "Octree.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "ResourceEvents.h"
#include "Scene.h"
#include "Sort.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

static const Vector3 DOT_SCALE(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);

static bool CompareAnimationOrder(const SharedPtr<AnimationState>& lhs, const SharedPtr<AnimationState>& rhs)
{
    return lhs->GetLayer() < rhs->GetLayer();
}

OBJECTTYPESTATIC(AnimatedModel);

AnimatedModel::AnimatedModel(Context* context) :
    StaticModel(context),
    animationLodFrameNumber_(0),
    animationLodBias_(1.0f),
    animationLodTimer_(-1.0f),
    animationLodDistance_(0.0f),
    invisibleLodFactor_(0.0f),
    animationDirty_(false),
    animationOrderDirty_(false),
    morphsDirty_(true),
    skinningDirty_(true),
    isMaster_(true),
    loading_(false),
    assignBonesPending_(false)
{
}

AnimatedModel::~AnimatedModel()
{
}

void AnimatedModel::RegisterObject(Context* context)
{
    context->RegisterFactory<AnimatedModel>();
    
    ACCESSOR_ATTRIBUTE(AnimatedModel, VAR_RESOURCEREF, "Model", GetModelAttr, SetModelAttr, ResourceRef, ResourceRef(Model::GetTypeStatic()), AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(AnimatedModel, VAR_RESOURCEREFLIST, "Material", GetMaterialsAttr, SetMaterialsAttr, ResourceRefList, ResourceRefList(Material::GetTypeStatic()), AM_DEFAULT);
    ATTRIBUTE(AnimatedModel, VAR_BOOL, "Is Visible", visible_, true, AM_DEFAULT);
    ATTRIBUTE(AnimatedModel, VAR_BOOL, "Is Occluder", occluder_, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimatedModel, VAR_BOOL, "Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    ATTRIBUTE(AnimatedModel, VAR_BOOL, "Cast Shadows", castShadows_, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimatedModel, VAR_FLOAT, "Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimatedModel, VAR_FLOAT, "Shadow Distance", GetShadowDistance, SetShadowDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimatedModel, VAR_FLOAT, "LOD Bias", GetLodBias, SetLodBias, float, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimatedModel, VAR_FLOAT, "Animation LOD Bias", GetAnimationLodBias, SetAnimationLodBias, float, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimatedModel, VAR_FLOAT, "Invisible Anim LOD Factor", GetInvisibleLodFactor, SetInvisibleLodFactor, float, 0.0f, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(AnimatedModel, Drawable);
    ATTRIBUTE(AnimatedModel, VAR_INT, "Ray/Occl. LOD Level", softwareLodLevel_, M_MAX_UNSIGNED, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(AnimatedModel, VAR_VARIANTVECTOR, "Bone Animation Enabled", GetBonesEnabledAttr, SetBonesEnabledAttr, VariantVector, VariantVector(), AM_FILE | AM_NOEDIT);
    ACCESSOR_ATTRIBUTE(AnimatedModel, VAR_VARIANTVECTOR, "Animation States", GetAnimationStatesAttr, SetAnimationStatesAttr, VariantVector, VariantVector(), AM_FILE | AM_NOEDIT);
    REF_ACCESSOR_ATTRIBUTE(AnimatedModel, VAR_BUFFER, "Morphs", GetMorphsAttr, SetMorphsAttr, PODVector<unsigned char>, PODVector<unsigned char>(), AM_DEFAULT | AM_NOEDIT);
}

bool AnimatedModel::Load(Deserializer& source)
{
    loading_ = true;
    bool success = Component::Load(source);
    loading_ = false;
    
    return success;
}

bool AnimatedModel::LoadXML(const XMLElement& source)
{
    loading_ = true;
    bool success = Component::LoadXML(source);
    loading_ = false;
    
    return success;
}

void AnimatedModel::ApplyAttributes()
{
    if (assignBonesPending_)
        AssignBoneNodes();
}

void AnimatedModel::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    // If no bones or no bone-level testing, use the Drawable test
    if (query.level_ < RAY_AABB || !skeleton_.GetRootBone() || !skeleton_.GetRootBone()->node_)
    {
        Drawable::ProcessRayQuery(query, results);
        return;
    }
    
    // Check ray hit distance to AABB before proceeding with bone-level tests
    if (query.ray_.HitDistance(GetWorldBoundingBox()) > query.maxDistance_)
        return;
    
    const Vector<Bone>& bones = skeleton_.GetBones();
    Sphere boneSphere;
    RayQueryLevel level = query.level_;
    
    for (unsigned i = 0; i < bones.Size(); ++i)
    {
        const Bone& bone = bones[i];
        if (!bone.node_)
            continue;
        
        // Use hitbox if available
        if (bone.collisionMask_ & BONECOLLISION_BOX)
        {
            // Do an initial crude test using the bone's AABB
            const BoundingBox& box = bone.boundingBox_;
            const Matrix3x4& transform = bone.node_->GetWorldTransform();
            float distance = query.ray_.HitDistance(box.Transformed(transform));
            if (distance <= query.maxDistance_)
            {
                if (level == RAY_AABB)
                {
                    RayQueryResult result;
                    result.drawable_ = this;
                    result.node_ = GetNode();
                    result.distance_ = distance;
                    result.subObject_ = i;
                    results.Push(result);
                }
                else
                {
                    // Follow with an OBB test if required
                    Matrix3x4 inverse = transform.Inverse();
                    Ray localRay(inverse * query.ray_.origin_, inverse * Vector4(query.ray_.direction_, 0.0f));
                    distance = localRay.HitDistance(box);
                    if (distance <= query.maxDistance_)
                    {
                        RayQueryResult result;
                        result.drawable_ = this;
                        result.node_ = GetNode();
                        result.distance_ = distance;
                        result.subObject_ = i;
                        results.Push(result);
                    }
                }
            }
        }
        else if (bone.collisionMask_ & BONECOLLISION_SPHERE)
        {
            boneSphere.center_ = bone.node_->GetWorldPosition();
            boneSphere.radius_ = bone.radius_;
            float distance = query.ray_.HitDistance(boneSphere);
            if (distance <= query.maxDistance_)
            {
                RayQueryResult result;
                result.drawable_ = this;
                result.node_ = GetNode();
                result.subObject_ = i;
                result.distance_ = distance;
                results.Push(result);
            }
        }
    }
}

void AnimatedModel::Update(const FrameInfo& frame)
{
    // Update animation here
    if (!animationDirty_ && !animationOrderDirty_)
        return;
    
    // If node was invisible last frame, need to decide animation LOD distance here
    // If headless, retain the current animation distance (should be 0)
    if (frame.camera_ && abs((int)frame.frameNumber_ - (int)viewFrameNumber_) > 1)
    {
        if (invisibleLodFactor_ == 0.0f)
            return;
        float distance = frame.camera_->GetDistance(node_->GetWorldPosition());
        // If distance is greater than draw distance, no need to update at all
        if (drawDistance_ > 0.0f && distance > drawDistance_)
            return;
        // Multiply the distance by a constant so that invisible nodes don't update that often
        float scale = GetWorldBoundingBox().Size().DotProduct(DOT_SCALE);
        animationLodDistance_ = frame.camera_->GetLodDistance(distance, scale, lodBias_) * invisibleLodFactor_;
    }
    
    UpdateAnimation(frame);
}

void AnimatedModel::UpdateBatches(const FrameInfo& frame)
{
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    distance_ = frame.camera_->GetDistance(GetWorldBoundingBox().Center());
    
    // Note: per-geometry distances do not take skinning into account
    if (batches_.Size() > 1)
    {
        for (unsigned i = 0; i < batches_.Size(); ++i)
        {
            batches_[i].distance_ = frame.camera_->GetDistance(worldTransform * geometryData_[i].center_);
            batches_[i].worldTransform_ = &worldTransform;
        }
    }
    else if (batches_.Size() == 1)
    {
        batches_[0].distance_ = distance_;
        batches_[0].worldTransform_ = &worldTransform;
    }
    
    float scale = GetWorldBoundingBox().Size().DotProduct(DOT_SCALE);
    float newLodDistance = frame.camera_->GetLodDistance(distance_, scale, lodBias_);
    
    // If model is rendered from several views, use the minimum LOD distance for animation LOD
    if (frame.frameNumber_ != animationLodFrameNumber_)
    {
        animationLodDistance_ = newLodDistance;
        animationLodFrameNumber_ = frame.frameNumber_;
    }
    else
        animationLodDistance_ = Min(animationLodDistance_, newLodDistance);
    
    if (newLodDistance != lodDistance_)
    {
        lodDistance_ = newLodDistance;
        CalculateLodLevels();
    }
    
    // If model has morphs, check if the morph vertex buffer(s) have lost data (only possible in OpenGL mode)
    if (morphs_.Size())
    {
        for (unsigned i = 0; i < morphVertexBuffers_.Size(); ++i)
        {
            if (morphVertexBuffers_[i] && morphVertexBuffers_[i]->IsDataLost())
            {
                morphsDirty_ = true;
                break;
            }
        }
    }
}

void AnimatedModel::UpdateGeometry(const FrameInfo& frame)
{
    if (morphsDirty_)
        UpdateMorphs();
    
    if (skinningDirty_)
        UpdateSkinning();
}

UpdateGeometryType AnimatedModel::GetUpdateGeometryType()
{
    if (morphsDirty_)
        return UPDATE_MAIN_THREAD;
    else if (skinningDirty_)
        return UPDATE_WORKER_THREAD;
    else
        return UPDATE_NONE;
}

void AnimatedModel::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug)
    {
        debug->AddBoundingBox(GetWorldBoundingBox(), Color(0.0f, 1.0f, 0.0f), depthTest);
        debug->AddSkeleton(skeleton_, Color(0.75f, 0.75f, 0.75f), depthTest);
    }
}

void AnimatedModel::SetModel(Model* model, bool createBones)
{
    if (!model || model == model_)
        return;
    
    // Unsubscribe from the reload event of previous model (if any), then subscribe to the new
    if (model_)
        UnsubscribeFromEvent(model_, E_RELOADFINISHED);
    if (model)
        SubscribeToEvent(model, E_RELOADFINISHED, HANDLER(AnimatedModel, HandleModelReloadFinished));
    
    model_ = model;
    
    // Copy the subgeometry & LOD level structure
    SetNumGeometries(model->GetNumGeometries());
    const Vector<Vector<SharedPtr<Geometry> > >& geometries = model->GetGeometries();
    const PODVector<Vector3>& geometryCenters = model->GetGeometryCenters();
    for (unsigned i = 0; i < geometries.Size(); ++i)
    {
        geometries_[i] = geometries[i];
        geometryData_[i].center_ = geometryCenters[i];
    }
    
    // Copy geometry bone mappings
    const Vector<PODVector<unsigned> >& geometryBoneMappings = model->GetGeometryBoneMappings();
    geometryBoneMappings_.Clear();
    for (unsigned i = 0; i < geometryBoneMappings.Size(); ++i)
        geometryBoneMappings_.Push(geometryBoneMappings[i]);
    
    // Copy morphs
    morphVertexBuffers_.Clear();
    morphs_.Clear();
    const Vector<ModelMorph>& morphs = model->GetMorphs();
    unsigned morphElementMask = 0;
    for (unsigned i = 0; i < morphs.Size(); ++i)
    {
        ModelMorph newMorph;
        newMorph.name_ = morphs[i].name_;
        newMorph.nameHash_ = morphs[i].nameHash_;
        newMorph.weight_ = 0.0f;
        newMorph.buffers_ = morphs[i].buffers_;
        for (Map<unsigned, VertexBufferMorph>::ConstIterator j = morphs[i].buffers_.Begin(); j != morphs[i].buffers_.End(); ++j)
            morphElementMask |= j->second_.elementMask_;
        morphs_.Push(newMorph);
    }
    
    // If model has morphs, must clone all geometries & vertex buffers that refer to morphable vertex data
    if (morphs.Size())
    {
        CloneGeometries(morphElementMask);
        MarkMorphsDirty();
    }
    
    // Copy bounding box & skeleton
    SetBoundingBox(model->GetBoundingBox());
    SetSkeleton(model->GetSkeleton(), createBones);
    ResetLodLevels();
    
    // Enable skinning in batches
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        if (skinMatrices_.Size())
        {
            batches_[i].geometryType_ = GEOM_SKINNED;
            // Check if model has per-geometry bone mappings
            if (geometrySkinMatrices_.Size() && geometrySkinMatrices_[i].Size())
            {
                batches_[i].shaderData_ = geometrySkinMatrices_[i][0].Data();
                batches_[i].shaderDataSize_ = geometrySkinMatrices_[i].Size() * 12;
            }
            // If not, use the global skin matrices
            else
            {
                batches_[i].shaderData_ = skinMatrices_[0].Data();
                batches_[i].shaderDataSize_ = skinMatrices_.Size() * 12;
            }
        }
        else
        {
            batches_[i].geometryType_ = GEOM_STATIC;
            batches_[i].shaderData_ = 0;
            batches_[i].shaderDataSize_ = 0;
        }
    }
    
    MarkNetworkUpdate();
}

AnimationState* AnimatedModel::AddAnimationState(Animation* animation)
{
    if (!isMaster_)
    {
        LOGERROR("Can not add animation state to non-master model");
        return 0;
    }
    
    if (!animation || !skeleton_.GetNumBones())
        return 0;
    
    // Check for not adding twice
    AnimationState* existing = GetAnimationState(animation);
    if (existing)
        return existing;
    
    SharedPtr<AnimationState> newState(new AnimationState(this, animation));
    animationStates_.Push(newState);
    MarkAnimationOrderDirty();
    return newState;
}

void AnimatedModel::RemoveAnimationState(Animation* animation)
{
    if (animation)
        RemoveAnimationState(animation->GetNameHash());
}

void AnimatedModel::RemoveAnimationState(const String& animationName)
{
    RemoveAnimationState(StringHash(animationName));
}

void AnimatedModel::RemoveAnimationState(StringHash animationNameHash)
{
    for (Vector<SharedPtr<AnimationState> >::Iterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
    {
        AnimationState* state = *i;
        Animation* animation = state->GetAnimation();
        // Check both the animation and the resource name
        if (animation->GetNameHash() == animationNameHash || animation->GetAnimationNameHash() == animationNameHash)
        {
            animationStates_.Erase(i);
            MarkAnimationDirty();
        }
    }
}

void AnimatedModel::RemoveAnimationState(AnimationState* state)
{
    for (Vector<SharedPtr<AnimationState> >::Iterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
    {
        if (*i == state)
        {
            animationStates_.Erase(i);
            MarkAnimationDirty();
            return;
        }
    }
}

void AnimatedModel::RemoveAllAnimationStates()
{
    animationStates_.Clear();
    MarkAnimationDirty();
}

void AnimatedModel::SetAnimationLodBias(float bias)
{
    animationLodBias_ = Max(bias, 0.0f);
    MarkNetworkUpdate();
}

void AnimatedModel::SetInvisibleLodFactor(float factor)
{
    if (factor < 0.0f)
        factor = 0.0f;
    else if (factor != 0.0f && factor < 1.0f)
        factor = 1.0f;
    
    invisibleLodFactor_ = factor;
    MarkNetworkUpdate();
}

void AnimatedModel::SetMorphWeight(unsigned index, float weight)
{
    if (index >= morphs_.Size())
        return;
    
    weight = Clamp(weight, 0.0f, 1.0f);
    
    if (weight != morphs_[index].weight_)
    {
        morphs_[index].weight_ = weight;
        
        // For a master model, set the same morph weight on non-master models
        if (isMaster_)
        {
            PODVector<AnimatedModel*> models;
            GetComponents<AnimatedModel>(models);
            
            // Indexing might not be the same, so use the name hash instead
            for (unsigned i = 1; i < models.Size(); ++i)
            {
                if (!models[i]->isMaster_)
                    models[i]->SetMorphWeight(morphs_[index].nameHash_, weight);
            }
        }
        
        MarkMorphsDirty();
        MarkNetworkUpdate();
    }
}

void AnimatedModel::SetMorphWeight(const String& name, float weight)
{
    for (unsigned i = 0; i < morphs_.Size(); ++i)
    {
        if (morphs_[i].name_ == name)
        {
            SetMorphWeight(i, weight);
            return;
        }
    }
}

void AnimatedModel::SetMorphWeight(StringHash nameHash, float weight)
{
    for (unsigned i = 0; i < morphs_.Size(); ++i)
    {
        if (morphs_[i].nameHash_ == nameHash)
        {
            SetMorphWeight(i, weight);
            return;
        }
    }
}

void AnimatedModel::ResetMorphWeights()
{
    for (Vector<ModelMorph>::Iterator i = morphs_.Begin(); i != morphs_.End(); ++i)
        i->weight_ = 0.0f;
    
    // For a master model, reset weights on non-master models
    if (isMaster_)
    {
        PODVector<AnimatedModel*> models;
        GetComponents<AnimatedModel>(models);
        
        // Indexing might not be the same, so use the name hash instead
        for (unsigned i = 1; i < models.Size(); ++i)
        {
            if (!models[i]->isMaster_)
                models[i]->ResetMorphWeights();
        }
    }
    
    MarkMorphsDirty();
    MarkNetworkUpdate();
}

float AnimatedModel::GetMorphWeight(unsigned index) const
{
    return index < morphs_.Size() ? morphs_[index].weight_ : 0.0f;
}

float AnimatedModel::GetMorphWeight(const String& name) const
{
    for (Vector<ModelMorph>::ConstIterator i = morphs_.Begin(); i != morphs_.End(); ++i)
    {
        if (i->name_ == name)
            return i->weight_;
    }
    
    return 0.0f;
}

float AnimatedModel::GetMorphWeight(StringHash nameHash) const
{
    for (Vector<ModelMorph>::ConstIterator i = morphs_.Begin(); i != morphs_.End(); ++i)
    {
        if (i->nameHash_ == nameHash)
            return i->weight_;
    }
    
    return 0.0f;
}

AnimationState* AnimatedModel::GetAnimationState(Animation* animation) const
{
    for (Vector<SharedPtr<AnimationState> >::ConstIterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
    {
        if ((*i)->GetAnimation() == animation)
            return *i;
    }
    
    return 0;
}

AnimationState* AnimatedModel::GetAnimationState(const String& animationName) const
{
    for (Vector<SharedPtr<AnimationState> >::ConstIterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
    {
        Animation* animation = (*i)->GetAnimation();
        
        // Check both the animation and the resource name
        if (animation->GetName() == animationName || animation->GetAnimationName() == animationName)
            return *i;
    }
    
    return 0;
}

AnimationState* AnimatedModel::GetAnimationState(StringHash animationNameHash) const
{
    for (Vector<SharedPtr<AnimationState> >::ConstIterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
    {
        Animation* animation = (*i)->GetAnimation();
        
        // Check both the animation and the resource name
        if (animation->GetNameHash() == animationNameHash || animation->GetAnimationNameHash() == animationNameHash)
            return *i;
    }
    
    return 0;
}

AnimationState* AnimatedModel::GetAnimationState(unsigned index) const
{
    return index < animationStates_.Size() ? animationStates_[index].Get() : 0;
}

void AnimatedModel::SetSkeleton(const Skeleton& skeleton, bool createBones)
{
    if (!node_ && createBones)
    {
        LOGERROR("AnimatedModel not attached to a scene node, can not create bone nodes");
        return;
    }
    
    if (isMaster_)
    {
        // Check if bone structure has stayed compatible (reloading the model.) In that case retain the old bones and animations
        if (skeleton_.GetNumBones() == skeleton.GetNumBones())
        {
            Vector<Bone>& destBones = skeleton_.GetModifiableBones();
            const Vector<Bone>& srcBones = skeleton.GetBones();
            bool compatible = true;
            
            for (unsigned i = 0; i < destBones.Size(); ++i)
            {
                if (destBones[i].node_ && destBones[i].name_ == srcBones[i].name_ && destBones[i].parentIndex_ ==
                    srcBones[i].parentIndex_)
                {
                    // If compatible, just copy the values and retain the old node and animated status
                    Node* boneNode = destBones[i].node_;
                    bool animated = destBones[i].animated_;
                    destBones[i] = srcBones[i];
                    destBones[i].node_ = boneNode;
                    destBones[i].animated_ = animated;
                }
                else
                {
                    compatible = false;
                    break;
                }
            }
            if (compatible)
                return;
        }
        
        RemoveAllAnimationStates();
        
        // Detach the rootbone of the previous model if any
        if (createBones)
        {
            Bone* rootBone = skeleton_.GetRootBone();
            if (rootBone)
                node_->RemoveChild(rootBone->node_);
        }
        
        skeleton_.Define(skeleton);
        
        // Remove collision information from dummy bones that do not affect skinning, to prevent them from being merged
        // to the bounding box
        Vector<Bone>& bones = skeleton_.GetModifiableBones();
        for (Vector<Bone>::Iterator i = bones.Begin(); i != bones.End(); ++i)
        {
            if (i->collisionMask_ & BONECOLLISION_BOX && i->boundingBox_.Size().Length() < M_EPSILON)
                i->collisionMask_ &= ~BONECOLLISION_BOX;
            if (i->collisionMask_ & BONECOLLISION_SPHERE && i->radius_ < M_EPSILON)
                i->collisionMask_ &= ~BONECOLLISION_SPHERE;
        }
        
        // Create scene nodes for the bones
        if (createBones)
        {
            for (Vector<Bone>::Iterator i = bones.Begin(); i != bones.End(); ++i)
            {
                // Create bones as local, as they are never to be directly synchronized over the network
                Node* boneNode = node_->CreateChild(i->name_, LOCAL);
                boneNode->AddListener(this);
                boneNode->SetTransform(i->initialPosition_, i->initialRotation_, i->initialScale_);
                i->node_ = boneNode;
            }
            
            for (unsigned i = 0; i < bones.Size(); ++i)
            {
                unsigned parentIndex = bones[i].parentIndex_;
                if (parentIndex != i && parentIndex < bones.Size())
                    bones[parentIndex].node_->AddChild(bones[i].node_);
            }
        }
        
        MarkAnimationDirty();
        
        using namespace BoneHierarchyCreated;
        
        VariantMap eventData;
        eventData[P_NODE] = (void*)node_;
        SendEvent(E_BONEHIERARCHYCREATED, eventData);
    }
    else
    {
        // For non-master models: use the bone nodes of the master model
        skeleton_.Define(skeleton);
        
        if (createBones)
        {
            Vector<Bone>& bones = skeleton_.GetModifiableBones();
            for (Vector<Bone>::Iterator i = bones.Begin(); i != bones.End(); ++i)
            {
                Node* boneNode = node_->GetChild(i->name_, true);
                if (boneNode)
                    boneNode->AddListener(this);
                i->node_ = boneNode;
            }
        }
    }
    
    // Reserve space for skinning matrices
    skinMatrices_.Resize(skeleton_.GetNumBones());
    SetGeometryBoneMappings();
    
    assignBonesPending_ = !createBones;
}

void AnimatedModel::SetModelAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    // When loading a scene, set model without creating the bone nodes (will be assigned later during post-load)
    SetModel(cache->GetResource<Model>(value.id_), !loading_);
}

void AnimatedModel::SetBonesEnabledAttr(VariantVector value)
{
    Vector<Bone>& bones = skeleton_.GetModifiableBones();
    for (unsigned i = 0; i < bones.Size() && i < value.Size(); ++i)
        bones[i].animated_ = value[i].GetBool();
}

void AnimatedModel::SetAnimationStatesAttr(VariantVector value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    RemoveAllAnimationStates();
    unsigned index = 0;
    while (index < value.Size())
    {
        const ResourceRef& animRef = value[index++].GetResourceRef();
        AnimationState* state = AddAnimationState(cache->GetResource<Animation>(animRef.id_));
        if (state)
        {
            state->SetStartBone(skeleton_.GetBone(value[index++].GetStringHash()));
            state->SetLooped(value[index++].GetBool());
            state->SetWeight(value[index++].GetFloat());
            state->SetTime(value[index++].GetFloat());
            state->SetLayer(value[index++].GetInt());
        }
        else
            index += 5;
    }
}

void AnimatedModel::SetMorphsAttr(const PODVector<unsigned char>& value)
{
    unsigned index = 0;
    while (index < value.Size())
        SetMorphWeight(index, (float)value[index] / 255.0f);
}

ResourceRef AnimatedModel::GetModelAttr() const
{
    return GetResourceRef(model_, Model::GetTypeStatic());
}

VariantVector AnimatedModel::GetBonesEnabledAttr() const
{
    VariantVector ret;
    const Vector<Bone>& bones = skeleton_.GetBones();
    for (Vector<Bone>::ConstIterator i = bones.Begin(); i != bones.End(); ++i)
        ret.Push(i->animated_);
    return ret;
}

VariantVector AnimatedModel::GetAnimationStatesAttr() const
{
    VariantVector ret;
    for (Vector<SharedPtr<AnimationState> >::ConstIterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
    {
        AnimationState* state = *i;
        Bone* startBone = state->GetStartBone();
        ret.Push(ResourceRef(Animation::GetTypeStatic(), state->GetAnimation()->GetNameHash()));
        ret.Push(startBone ? startBone->nameHash_ : StringHash());
        ret.Push(state->IsLooped());
        ret.Push(state->GetWeight());
        ret.Push(state->GetTime());
        ret.Push((int)state->GetLayer());
    }
    return ret;
}

const PODVector<unsigned char>& AnimatedModel::GetMorphsAttr() const
{
    attrBuffer_.Clear();
    for (Vector<ModelMorph>::ConstIterator i = morphs_.Begin(); i != morphs_.End(); ++i)
        attrBuffer_.WriteUByte((unsigned char)(i->weight_ * 255.0f));
    
    return attrBuffer_.GetBuffer();
}

void AnimatedModel::OnNodeSet(Node* node)
{
    Drawable::OnNodeSet(node);
    
    // If this AnimatedModel is the first in the node, it is the master which controls animation & morphs
    isMaster_ = GetComponent<AnimatedModel>() == this;
}

void AnimatedModel::OnMarkedDirty(Node* node)
{
    Drawable::OnMarkedDirty(node);
    
    // If the scene node or any of the bone nodes move, mark skinning dirty
    skinningDirty_ = true;
}

void AnimatedModel::OnWorldBoundingBoxUpdate()
{
    if (!skeleton_.GetNumBones())
        worldBoundingBox_ = boundingBox_.Transformed(node_->GetWorldTransform());
    else
    {
        // If has bones, update world bounding box based on them
        worldBoundingBox_.defined_ = false;
        
        const Vector<Bone>& bones = skeleton_.GetBones();
        for (Vector<Bone>::ConstIterator i = bones.Begin(); i != bones.End(); ++i)
        {
            Node* boneNode = i->node_;
            if (!boneNode)
                continue;
            
            // Use hitbox if available. If not, use only half of the sphere radius
            if (i->collisionMask_ & BONECOLLISION_BOX)
                worldBoundingBox_.Merge(i->boundingBox_.Transformed(boneNode->GetWorldTransform()));
            else if (i->collisionMask_ & BONECOLLISION_SPHERE)
                worldBoundingBox_.Merge(Sphere(boneNode->GetWorldPosition(), i->radius_ * 0.5f));
        }
    }
}

void AnimatedModel::AssignBoneNodes()
{
    assignBonesPending_ = false;
    
    if (!node_)
        return;
    
    // Find the bone nodes from the node hierarchy and add listeners
    Vector<Bone>& bones = skeleton_.GetModifiableBones();
    bool boneFound = false;
    for (Vector<Bone>::Iterator i = bones.Begin(); i != bones.End(); ++i)
    {
        Node* boneNode = node_->GetChild(i->name_, true);
        if (boneNode)
        {
            boneFound = true;
            boneNode->AddListener(this);
        }
        i->node_ = boneNode;
    }
    
    // If no bones found, this may be a prefab where the bone information was left out.
    // In that case reassign the skeleton now if possible
    if (!boneFound && model_)
        SetSkeleton(model_->GetSkeleton(), true);
    
    // Re-assign the same start bone to animations to get the proper bone node this time
    for (Vector<SharedPtr<AnimationState> >::Iterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
    {
        AnimationState* state = *i;
        state->SetStartBone(state->GetStartBone());
    }
    
    MarkAnimationDirty();
}

void AnimatedModel::MarkAnimationDirty()
{
    if (isMaster_)
    {
        animationDirty_ = true;
        // Mark for pre-octree reinsertion update (threaded)
        MarkForUpdate();
    }
}

void AnimatedModel::MarkAnimationOrderDirty()
{
    if (isMaster_)
    {
        animationOrderDirty_ = true;
        // Mark for pre-octree reinsertion update (threaded)
        MarkForUpdate();
    }
}

void AnimatedModel::MarkMorphsDirty()
{
    morphsDirty_ = true;
}

void AnimatedModel::CloneGeometries(unsigned morphElementMask)
{
    // Clone vertex buffers as necessary
    const Vector<SharedPtr<VertexBuffer> >& originalVertexBuffers = model_->GetVertexBuffers();
    Map<VertexBuffer*, SharedPtr<VertexBuffer> > clonedVertexBuffers;
    morphVertexBuffers_.Resize(originalVertexBuffers.Size());
    
    for (unsigned i = 0; i < originalVertexBuffers.Size(); ++i)
    {
        VertexBuffer* original = originalVertexBuffers[i];
        if (model_->GetMorphRangeCount(i))
        {
            SharedPtr<VertexBuffer> clone(new VertexBuffer(context_));
            clone->SetSize(original->GetVertexCount(), morphElementMask & original->GetElementMask(), true);
            void* dest = clone->Lock(0, original->GetVertexCount());
            if (dest)
            {
                CopyMorphVertices(dest, original->GetShadowData(), original->GetVertexCount(), clone, original);
                clone->Unlock();
            }
            clonedVertexBuffers[original] = clone;
            morphVertexBuffers_[i] = clone;
        }
        else
            morphVertexBuffers_[i].Reset();
    }
    
    // Geometries will always be cloned fully. They contain only references to buffer, so they are relatively light
    for (unsigned i = 0; i < geometries_.Size(); ++i)
    {
        for (unsigned j = 0; j < geometries_[i].Size(); ++j)
        {
            SharedPtr<Geometry> original = geometries_[i][j];
            SharedPtr<Geometry> clone(new Geometry(context_));
            
            // Add an additional vertex stream into the clone, which supplies only the morphable vertex data, while the static
            // data comes from the original vertex buffer(s)
            const Vector<SharedPtr<VertexBuffer> >& originalBuffers = original->GetVertexBuffers();
            unsigned totalBuf = originalBuffers.Size();
            for (unsigned k = 0; k < originalBuffers.Size(); ++k)
            {
                VertexBuffer* originalBuffer = originalBuffers[k];
                if (clonedVertexBuffers.Contains(originalBuffer))
                    ++totalBuf;
            }
            clone->SetNumVertexBuffers(totalBuf);
            
            unsigned l = 0;
            for (unsigned k = 0; k < originalBuffers.Size(); ++k)
            {
                VertexBuffer* originalBuffer = originalBuffers[k];
                unsigned originalMask = original->GetVertexElementMask(k);
                
                if (clonedVertexBuffers.Contains(originalBuffer))
                {
                    VertexBuffer* clonedBuffer = clonedVertexBuffers[originalBuffer];
                    clone->SetVertexBuffer(l, originalBuffer, originalMask & ~clonedBuffer->GetElementMask());
                    ++l;
                    clone->SetVertexBuffer(l, clonedBuffer, originalMask & clonedBuffer->GetElementMask());
                    ++l;
                }
                else
                {
                    clone->SetVertexBuffer(l, originalBuffer, originalMask);
                    ++l;
                }
            }
            
            clone->SetIndexBuffer(original->GetIndexBuffer());
            clone->SetDrawRange(original->GetPrimitiveType(), original->GetIndexStart(), original->GetIndexCount());
            clone->SetLodDistance(original->GetLodDistance());
            
            geometries_[i][j] = clone;
        }
    }
}

void AnimatedModel::CopyMorphVertices(void* destVertexData, void* srcVertexData, unsigned vertexCount, VertexBuffer* destBuffer, VertexBuffer* srcBuffer)
{
    unsigned mask = destBuffer->GetElementMask() & srcBuffer->GetElementMask();
    unsigned normalOffset = srcBuffer->GetElementOffset(ELEMENT_NORMAL);
    unsigned tangentOffset = srcBuffer->GetElementOffset(ELEMENT_TANGENT);
    unsigned vertexSize = srcBuffer->GetVertexSize();
    float* dest = (float*)destVertexData;
    unsigned char* src = (unsigned char*)srcVertexData;
    
    while (vertexCount--)
    {
        if (mask & MASK_POSITION)
        {
            float* posSrc = (float*)src;
            *dest++ = posSrc[0];
            *dest++ = posSrc[1];
            *dest++ = posSrc[2];
        }
        if (mask & MASK_NORMAL)
        {
            float* normalSrc = (float*)(src + normalOffset);
            *dest++ = normalSrc[0];
            *dest++ = normalSrc[1];
            *dest++ = normalSrc[2];
        }
        if (mask & MASK_TANGENT)
        {
            float* tangentSrc = (float*)(src + tangentOffset);
            *dest++ = tangentSrc[0];
            *dest++ = tangentSrc[1];
            *dest++ = tangentSrc[2];
            *dest++ = tangentSrc[3];
        }
        
        src += vertexSize;
    }
}

void AnimatedModel::SetGeometryBoneMappings()
{
    geometrySkinMatrices_.Clear();
    geometrySkinMatrixPtrs_.Clear();
    
    if (!geometryBoneMappings_.Size())
        return;
    
    // Check if all mappings are empty, then we do not need to use mapped skinning
    bool allEmpty = true;
    for (unsigned i = 0; i < geometryBoneMappings_.Size(); ++i)
        if (geometryBoneMappings_[i].Size())
            allEmpty = false;
    
    if (allEmpty)
        return;
    
    // Reserve space for per-geometry skinning matrices
    geometrySkinMatrices_.Resize(geometryBoneMappings_.Size());
    for (unsigned i = 0; i < geometryBoneMappings_.Size(); ++i)
        geometrySkinMatrices_[i].Resize(geometryBoneMappings_[i].Size());
    
    // Build original-to-skinindex matrix pointer mapping for fast copying
    // Note: at this point layout of geometrySkinMatrices_ cannot be modified or pointers become invalid
    geometrySkinMatrixPtrs_.Resize(skeleton_.GetNumBones());
    for (unsigned i = 0; i < geometryBoneMappings_.Size(); ++i)
    {
        for (unsigned j = 0; j < geometryBoneMappings_[i].Size(); ++j)
            geometrySkinMatrixPtrs_[geometryBoneMappings_[i][j]].Push(&geometrySkinMatrices_[i][j]);
    }
}

void AnimatedModel::UpdateAnimation(const FrameInfo& frame)
{
    // If using animation LOD, accumulate time and see if it is time to update
    if (animationLodBias_ > 0.0f && animationLodDistance_ > 0.0f)
    {
        // Check for first time update
        if (animationLodTimer_ >= 0.0f)
        {
            animationLodTimer_ += animationLodBias_ * frame.timeStep_ * frame.viewSize_.y_ * ANIMATION_LOD_BASESCALE;
            if (animationLodTimer_ >= animationLodDistance_)
                animationLodTimer_ = fmodf(animationLodTimer_, animationLodDistance_);
            else
                return;
        }
        else
            animationLodTimer_ = 0.0f;
    }
    
    // Make sure animations are in ascending priority order
    if (animationOrderDirty_)
    {
        Sort(animationStates_.Begin(), animationStates_.End(), CompareAnimationOrder);
        animationOrderDirty_ = false;
    }
    
    // Reset skeleton, then apply all animations
    skeleton_.Reset();
    for (Vector<SharedPtr<AnimationState> >::Iterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
        (*i)->Apply();
    
    // Animation has changed the bounding box: mark node for octree reinsertion
    Drawable::OnMarkedDirty(node_);
    // For optimization, recalculate world bounding box already here (during the threaded update)
    GetWorldBoundingBox();
    animationDirty_ = false;
}

void AnimatedModel::UpdateSkinning()
{
    // Note: the model's world transform will be baked in the skin matrices
    const Vector<Bone>& bones = skeleton_.GetBones();
    // Use model's world transform in case a bone is missing
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    
    // Skinning with global matrices only
    if (!geometrySkinMatrices_.Size())
    {
        for (unsigned i = 0; i < bones.Size(); ++i)
        {
            const Bone& bone = bones[i];
            if (bone.node_)
                skinMatrices_[i] = bone.node_->GetWorldTransform() * bone.offsetMatrix_;
            else
                skinMatrices_[i] = worldTransform;
        }
    }
    // Skinning with per-geometry matrices
    else
    {
        for (unsigned i = 0; i < bones.Size(); ++i)
        {
            const Bone& bone = bones[i];
            if (bone.node_)
                skinMatrices_[i] = bone.node_->GetWorldTransform() * bone.offsetMatrix_;
            else
                skinMatrices_[i] = worldTransform;
            
            // Copy the skin matrix to per-geometry matrices as needed
            for (unsigned j = 0; j < geometrySkinMatrixPtrs_[i].Size(); ++j)
                *geometrySkinMatrixPtrs_[i][j] = skinMatrices_[i];
        }
    }
    
    skinningDirty_ = false;
}

void AnimatedModel::UpdateMorphs()
{
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics)
        return;
    
    if (morphs_.Size())
    {
        // Reset the morph data range from all morphable vertex buffers, then apply morphs
        for (unsigned i = 0; i < morphVertexBuffers_.Size(); ++i)
        {
            VertexBuffer* buffer = morphVertexBuffers_[i];
            if (buffer)
            {
                VertexBuffer* originalBuffer = model_->GetVertexBuffers()[i];
                unsigned morphStart = model_->GetMorphRangeStart(i);
                unsigned morphCount = model_->GetMorphRangeCount(i);
                
                if (!buffer->IsDataLost())
                {
                    void* dest = buffer->Lock(morphStart, morphCount);
                    if (dest)
                    {
                        // Reset morph range by copying data from the original vertex buffer
                        CopyMorphVertices(dest, originalBuffer->GetShadowData() + morphStart * originalBuffer->GetVertexSize(),
                            morphCount, buffer, originalBuffer);
                        
                        for (unsigned j = 0; j < morphs_.Size(); ++j)
                        {
                            if (morphs_[j].weight_ > 0.0f)
                            {
                                Map<unsigned, VertexBufferMorph>::Iterator k = morphs_[j].buffers_.Find(i);
                                if (k != morphs_[j].buffers_.End())
                                    ApplyMorph(buffer, dest, morphStart, k->second_, morphs_[j].weight_);
                            }
                        }
                        
                        buffer->Unlock();
                    }
                }
                else
                {
                    // Data is lost, need to copy whole original buffer
                    unsigned vertexCount = buffer->GetVertexCount();
                    void* dest = buffer->Lock(0, vertexCount, true);
                    if (dest)
                    {
                        CopyMorphVertices(dest, originalBuffer->GetShadowData(), vertexCount, buffer, originalBuffer);
                        
                        dest = ((unsigned char*)dest) + morphStart * buffer->GetVertexSize();
                        for (unsigned j = 0; j < morphs_.Size(); ++j)
                        {
                            if (morphs_[j].weight_ > 0.0f)
                            {
                                Map<unsigned, VertexBufferMorph>::Iterator k = morphs_[j].buffers_.Find(i);
                                if (k != morphs_[j].buffers_.End())
                                    ApplyMorph(buffer, dest, morphStart, k->second_, morphs_[j].weight_);
                            }
                        }
                        
                        buffer->Unlock();
                    }
                    
                    buffer->ClearDataLost();
                }
            }
        }
    }
    
    morphsDirty_ = false;
}

void AnimatedModel::ApplyMorph(VertexBuffer* buffer, void* destVertexData, unsigned morphRangeStart, const VertexBufferMorph& morph, float weight)
{
    unsigned elementMask = morph.elementMask_ & buffer->GetElementMask();
    unsigned vertexCount = morph.vertexCount_;
    unsigned normalOffset = buffer->GetElementOffset(ELEMENT_NORMAL);
    unsigned tangentOffset = buffer->GetElementOffset(ELEMENT_TANGENT);
    unsigned vertexSize = buffer->GetVertexSize();
    
    unsigned char* srcData = morph.morphData_;
    unsigned char* destData = (unsigned char*)destVertexData;
    
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

void AnimatedModel::HandleModelReloadFinished(StringHash eventType, VariantMap& eventData)
{
    Model* currentModel = model_;
    model_ = 0; // Set null to allow to be re-set
    SetModel(currentModel);
}
