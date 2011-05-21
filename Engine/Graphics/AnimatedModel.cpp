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
#include "Batch.h"
#include "Camera.h"
#include "Context.h"
#include "DebugRenderer.h"
#include "Geometry.h"
#include "Graphics.h"
#include "IndexBuffer.h"
#include "Log.h"
#include "Material.h"
#include "MemoryBuffer.h"
#include "Octree.h"
#include "OctreeQuery.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "ResourceEvents.h"
#include "Scene.h"
#include "Sort.h"
#include "VectorBuffer.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

static const Vector3 dotScale(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);

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
    animationDirty_(true),
    animationOrderDirty_(true),
    morphsDirty_(true),
    skinningDirty_(true),
    isMaster_(true)
{
}

AnimatedModel::~AnimatedModel()
{
}

void AnimatedModel::RegisterObject(Context* context)
{
    context->RegisterFactory<AnimatedModel>();
    context->CopyBaseAttributes<Drawable, AnimatedModel>();
    
    ATTRIBUTE(AnimatedModel, VAR_RESOURCEREF, "Model", model_, ResourceRef(Model::GetTypeStatic()));
    ATTRIBUTE(AnimatedModel, VAR_RESOURCEREFLIST, "Materials", materials_, ResourceRefList(Material::GetTypeStatic()));
    ATTRIBUTE(AnimatedModel, VAR_FLOAT, "Animation LOD Bias", animationLodBias_, 1.0f);
    ATTRIBUTE(AnimatedModel, VAR_INT, "Raycast/Occlusion LOD Level", softwareLodLevel_, M_MAX_UNSIGNED);
    ATTRIBUTE(AnimatedModel, VAR_BUFFER, "Bone Animation Enabled", skeleton_, PODVector<unsigned char>());
    ATTRIBUTE(AnimatedModel, VAR_BUFFER, "Animation States", animationStates_, PODVector<unsigned char>());
}

void AnimatedModel::OnSetAttribute(const AttributeInfo& attr, const Variant& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    switch (attr.offset_)
    {
    case offsetof(AnimatedModel, model_):
        // When loading a scene, set model without creating the bone nodes (will be assigned later during post-load)
        SetModel(cache->GetResource<Model>(value.GetResourceRef().id_), !inSerialization_);
        break;
        
    case offsetof(AnimatedModel, materials_):
        {
            const ResourceRefList& refs = value.GetResourceRefList();
            for (unsigned i = 0; i < refs.ids_.Size(); ++i)
                SetMaterial(i, cache->GetResource<Material>(refs.ids_[i]));
        }
        break;
        
    case offsetof(AnimatedModel, skeleton_):
        {
            MemoryBuffer buf(value.GetBuffer());
            Vector<Bone>& bones = skeleton_.GetModifiableBones();
            unsigned numBones = buf.ReadVLE();
            for (unsigned i = 0; (i < numBones) && (i < bones.Size()); ++i)
                bones[i].animated_ = buf.ReadBool();
        }
        break;
        
    case offsetof(AnimatedModel, animationStates_):
        {
            // The animation states will at first be created without bone node references as well
            /// \todo This format is unsuitable for network serialization
            RemoveAllAnimationStates();
            MemoryBuffer buf(value.GetBuffer());
            unsigned numAnimations = buf.ReadVLE();
            for (unsigned i = 0; i < numAnimations; ++i)
            {
                AnimationState* state = AddAnimationState(cache->GetResource<Animation>(buf.ReadStringHash()));
                if (state)
                {
                    state->SetStartBone(skeleton_.GetBone(buf.ReadStringHash()));
                    state->SetLooped(buf.ReadBool());
                    state->SetWeight(buf.ReadFloat());
                    state->SetTime(buf.ReadFloat());
                    state->SetLayer(buf.ReadInt());
                    state->SetUseNlerp(buf.ReadBool());
                }
                else
                    buf.Seek(sizeof(StringHash) + 1 + sizeof(float) + sizeof(float) + sizeof(int) + 1);
            }
        }
        break;
        
    default:
        Serializable::OnSetAttribute(attr, value);
        break;
    }
}

Variant AnimatedModel::OnGetAttribute(const AttributeInfo& attr)
{
    switch (attr.offset_)
    {
    case offsetof(AnimatedModel, model_):
        return GetResourceRef(model_, Model::GetTypeStatic());
        
    case offsetof(AnimatedModel, materials_):
        return GetResourceRefList(materials_);
        
    case offsetof(AnimatedModel, skeleton_):
        {
            VectorBuffer buf;
            const Vector<Bone>& bones = skeleton_.GetBones();
            buf.WriteVLE(bones.Size());
            for (Vector<Bone>::ConstIterator i = bones.Begin(); i != bones.End(); ++i)
                buf.WriteBool(i->animated_);
            return buf.GetBuffer();
        }
        
    case offsetof(AnimatedModel, animationStates_):
        {
            VectorBuffer buf;
            buf.WriteVLE(animationStates_.Size());
            for (Vector<SharedPtr<AnimationState> >::Iterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
            {
                AnimationState* state = *i;
                Bone* startBone = state->GetStartBone();
                buf.WriteStringHash(state->GetAnimation()->GetNameHash());
                buf.WriteStringHash(startBone ? startBone->nameHash_ : StringHash());
                buf.WriteBool(state->IsLooped());
                buf.WriteFloat(state->GetWeight());
                buf.WriteFloat(state->GetTime());
                buf.WriteInt(state->GetLayer());
                buf.WriteBool(state->GetUseNlerp());
            }
            return buf.GetBuffer();
        }
        
    default:
        return Serializable::OnGetAttribute(attr);
    }
}

void AnimatedModel::PostLoad()
{
    AssignBoneNodes();
}

void AnimatedModel::ProcessRayQuery(RayOctreeQuery& query, float initialDistance)
{
    // If no bones or no bone-level testing, use the Drawable test
    if ((!skeleton_.GetNumBones()) || (query.level_ < RAY_AABB))
    {
        Drawable::ProcessRayQuery(query, initialDistance);
        return;
    }
    
    PROFILE(RaycastAnimatedModel);
    
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
            const Matrix4x3& transform = bone.node_->GetWorldTransform();
            float distance = box.GetTransformed(transform).GetDistance(query.ray_);
            if (distance < query.maxDistance_)
            {
                if (level == RAY_AABB)
                {
                    RayQueryResult result;
                    result.drawable_ = this;
                    result.node_ = GetNode();
                    result.distance_ = distance;
                    result.subObject_ = i;
                    query.result_.Push(result);
                }
                else
                {
                    // Follow with an OBB test if required
                    Matrix4x3 inverse = transform.GetInverse();
                    Ray localRay(inverse * query.ray_.origin_, inverse * Vector4(query.ray_.direction_, 0.0f));
                    distance = box.GetDistance(localRay);
                    if (distance < query.maxDistance_)
                    {
                        RayQueryResult result;
                        result.drawable_ = this;
                        result.node_ = GetNode();
                        result.distance_ = distance;
                        result.subObject_ = i;
                        query.result_.Push(result);
                    }
                }
            }
        }
        else if (bone.collisionMask_ & BONECOLLISION_SPHERE)
        {
            boneSphere.center_ = bone.node_->GetWorldPosition();
            boneSphere.radius_ = bone.radius_;
            float distance = boneSphere.GetDistance(query.ray_);
            if (distance < query.maxDistance_)
            {
                RayQueryResult result;
                result.drawable_ = this;
                result.node_ = GetNode();
                result.subObject_ = i;
                result.distance_ = distance;
                query.result_.Push(result);
            }
        }
    }
}

void AnimatedModel::Update(const FrameInfo& frame)
{
    // Update animation here
    if ((!animationDirty_) && (!animationOrderDirty_))
        return;
    
    // If node was invisible last frame, need to decide animation LOD distance here
    // If headless, retain the current animation distance (should be 0)
    if ((frame.camera_) && (abs((int)frame.frameNumber_ - (int)viewFrameNumber_) > 1))
    {
        if (invisibleLodFactor_ == 0.0f)
            return;
        float distance = frame.camera_->GetDistance(GetWorldPosition());
        // If distance is greater than draw distance, no need to update at all
        if ((drawDistance_ > 0.0f) && (distance > drawDistance_))
            return;
        // Multiply the distance by a constant so that invisible nodes don't update that often
        float scale = GetWorldBoundingBox().GetSize().DotProduct(dotScale);
        animationLodDistance_ = frame.camera_->GetLodDistance(distance, scale, lodBias_) * invisibleLodFactor_;
    }
    
    UpdateAnimation(frame);
}

void AnimatedModel::UpdateDistance(const FrameInfo& frame)
{
    distance_ = frame.camera_->GetDistance(GetWorldPosition());
    
    float scale = GetWorldBoundingBox().GetSize().DotProduct(dotScale);
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
        lodLevelsDirty_ = true;
    }
}

void AnimatedModel::UpdateGeometry(const FrameInfo& frame)
{
    if (lodLevelsDirty_)
        CalculateLodLevels();
    
    if ((morphsDirty_) && (morphs_.Size()))
        UpdateMorphs();
    
    if (skinningDirty_)
        UpdateSkinning();
}

void AnimatedModel::GetBatch(const FrameInfo& frame, unsigned batchIndex, Batch& batch)
{
    batch.geometry_ = geometries_[batchIndex][lodLevels_[batchIndex]];
    batch.geometryType_ = GEOM_SKINNED;
    batch.worldTransform_ = &GetWorldTransform();
    batch.material_ = materials_[batchIndex];
    
    if (skinMatrices_.Size())
    {
        // Check if model has per-geometry bone mappings
        if ((geometrySkinMatrices_.Size()) && (geometrySkinMatrices_[batchIndex].Size()))
        {
            batch.shaderData_ = geometrySkinMatrices_[batchIndex][0].GetData();
            batch.shaderDataSize_ = geometrySkinMatrices_[batchIndex].Size() * 12;
        }
        // If not, use the global skin matrices
        else
        {
            batch.shaderData_ = skinMatrices_[0].GetData();
            batch.shaderDataSize_ = skinMatrices_.Size() * 12;
        }
    }
}

void AnimatedModel::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    debug->AddBoundingBox(GetWorldBoundingBox(), Color(0.0f, 1.0f, 0.0f), depthTest);
    debug->AddSkeleton(skeleton_, Color(0.75f, 0.75f, 0.75f), depthTest);
}

void AnimatedModel::SetModel(Model* model, bool createBones)
{
    if ((!model) || (model == model_))
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
    for (unsigned i = 0; i < geometries.Size(); ++i)
        geometries_[i] = geometries[i];
    
    // Copy geometry bone mappings
    const Vector<PODVector<unsigned> >& geometryBoneMappings = model->GetGeometryBoneMappings();
    geometryBoneMappings_.Clear();
    for (unsigned i = 0; i < geometryBoneMappings.Size(); ++i)
        geometryBoneMappings_.Push(geometryBoneMappings[i]);
    
    // Copy morphs
    morphvertexBuffer_.Clear();
    morphs_.Clear();
    const Vector<ModelMorph>& morphs = model->GetMorphs();
    for (unsigned i = 0; i < morphs.Size(); ++i)
    {
        ModelMorph newMorph;
        newMorph.name_ = morphs[i].name_;
        newMorph.nameHash_ = morphs[i].nameHash_;
        newMorph.weight_ = 0.0f;
        newMorph.buffers_ = morphs[i].buffers_;
        morphs_.Push(newMorph);
    }
    
    // If model has morphs, must clone all geometries & vertex buffers that refer to morphable vertex data
    if (morphs.Size())
    {
        cloneGeometries();
        MarkMorphsDirty();
    }
    
    // Copy bounding box & skeleton
    SetBoundingBox(model->GetBoundingBox());
    SetSkeleton(model->GetSkeleton(), createBones);
}

AnimationState* AnimatedModel::AddAnimationState(Animation* animation)
{
    if (!isMaster_)
    {
        LOGERROR("Can not add animation state to non-master model");
        return 0;
    }
    
    if ((!animation) || (!skeleton_.GetNumBones()))
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
        if ((animation->GetNameHash() == animationNameHash) || (animation->GetAnimationNameHash() == animationNameHash))
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
}

void AnimatedModel::SetInvisibleLodFactor(float factor)
{
    if (factor < 0.0f)
        factor = 0.0f;
    else if ((factor != 0.0f) && (factor < 1.0f))
        factor = 1.0f;
    invisibleLodFactor_ = factor;
}

void AnimatedModel::SetMorphWeight(unsigned index, float weight)
{
    if (index >= morphs_.Size())
        return;
    
    weight = Clamp(weight, 0.0f, 1.0f);
    
    if (weight != morphs_[index].weight_)
    {
        morphs_[index].weight_ = weight;
        MarkMorphsDirty();
        
        // For a master model, set the same morph weight on non-master models
        if (isMaster_)
        {
            PODVector<AnimatedModel*> models;
            GetComponents<AnimatedModel>(models);
            
            // Indexing might not be the same, so use the name hash instead
            for (unsigned i = 1; i < models.Size(); ++i)
                models[i]->SetMorphWeight(morphs_[index].nameHash_, weight);
        }
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
    
    MarkMorphsDirty();

    // For a master model, reset weights on non-master models
    if (isMaster_)
    {
        PODVector<AnimatedModel*> models;
        GetComponents<AnimatedModel>(models);
        
        // Indexing might not be the same, so use the name hash instead
        for (unsigned i = 1; i < models.Size(); ++i)
            models[i]->ResetMorphWeights();
    }
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
        if ((animation->GetName() == animationName) || (animation->GetAnimationName() == animationName))
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
        if ((animation->GetNameHash() == animationNameHash) || (animation->GetAnimationNameHash() == animationNameHash))
            return *i;
    }
    
    return 0;
}

AnimationState* AnimatedModel::GetAnimationState(unsigned index) const
{
    return index < animationStates_.Size() ? animationStates_[index].GetPtr() : 0;
}

void AnimatedModel::SetSkeleton(const Skeleton& skeleton, bool createBones)
{
    if ((!node_) && (createBones))
    {
        LOGWARNING("AnimatedModel not attached to a scene node, can not create bone nodes");
        return;
    }
    
    if (isMaster_)
    {
        // Detach the rootbone of the previous model if any
        if (createBones)
        {
            Bone* rootBone = skeleton_.GetRootBone();
            if (rootBone)
                node_->RemoveChild(rootBone->node_);
        }
        
        RemoveAllAnimationStates();
        
        skeleton_.Define(skeleton);
        
        // Create scene nodes for the bones, or get from the master model if not master
        if (createBones)
        {
            Vector<Bone>& bones = skeleton_.GetModifiableBones();
            for (Vector<Bone>::Iterator i = bones.Begin(); i != bones.End(); ++i)
            {
                // Create bones as local, as they are never to be directly synchronized over the network
                Node* boneNode = node_->CreateChild(i->name_, true);
                boneNode->AddListener(this);
                boneNode->SetTransform(i->initialPosition_, i->initialRotation_, i->initialScale_);
                i->node_ = boneNode;
            }
            
            for (unsigned i = 0; i < bones.Size(); ++i)
            {
                unsigned parentIndex = bones[i].parentIndex_;
                if ((parentIndex != i) && (parentIndex < bones.Size()))
                    bones[parentIndex].node_->AddChild(bones[i].node_);
            }
        }
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
    RefreshGeometryBoneMappings();
}

void AnimatedModel::OnNodeSet(Node* node)
{
    Drawable::OnNodeSet(node);
    
    // If this AnimatedModel is the first in the node, it is the master which controls animation & morphs
    isMaster_ = GetComponent<AnimatedModel>(0) == this;
}

void AnimatedModel::OnMarkedDirty(Node* node)
{
    // If the scene node or any of the bone nodes move, mark skinning dirty
    skinningDirty_ = true;
    if (node == node_)
    {
        worldBoundingBoxDirty_ = true;
        if (octant_)
            octant_->GetRoot()->QueueReinsertion(this);
    }
}

void AnimatedModel::OnWorldBoundingBoxUpdate()
{
    if (!skeleton_.GetNumBones())
        worldBoundingBox_ = boundingBox_.GetTransformed(GetWorldTransform());
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
                worldBoundingBox_.Merge(i->boundingBox_.GetTransformed(boneNode->GetWorldTransform()));
            else if (i->collisionMask_ & BONECOLLISION_SPHERE)
                worldBoundingBox_.Merge(Sphere(boneNode->GetWorldPosition(), i->radius_ * 0.5f));
        }
    }
}

void AnimatedModel::AssignBoneNodes()
{
    if (!node_)
        return;
    
    // Find the bone nodes from the node hierarchy and add listeners
    Vector<Bone>& bones = skeleton_.GetModifiableBones();
    for (Vector<Bone>::Iterator i = bones.Begin(); i != bones.End(); ++i)
    {
        Node* boneNode = node_->GetChild(i->name_, true);
        if (boneNode)
            boneNode->AddListener(this);
        i->node_ = boneNode;
    }
    
    // Re-assign the same start bone to get the proper bone node this time
    for (Vector<SharedPtr<AnimationState> >::Iterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
    {
        AnimationState* state = *i;
        state->SetStartBone(state->GetStartBone());
    }
}

void AnimatedModel::MarkAnimationDirty()
{
    if (!isMaster_)
        return;
    
    animationDirty_ = true;
    // Mark for octree update, as animation is updated before octree reinsertion
    MarkForUpdate();
}

void AnimatedModel::MarkAnimationOrderDirty()
{
    if (!isMaster_)
        return;
    
    animationOrderDirty_ = true;
    // Mark for octree update, as animation is updated before octree reinsertion
    MarkForUpdate();
}

void AnimatedModel::MarkMorphsDirty()
{
    morphsDirty_ = true;
}

void AnimatedModel::cloneGeometries()
{
    // Clone vertex buffers as necessary
    const Vector<SharedPtr<VertexBuffer> >& originalVertexBuffers = model_->GetVertexBuffers();
    Map<VertexBuffer*, SharedPtr<VertexBuffer> > clonedVertexBuffers;
    
    morphvertexBuffer_.Resize(originalVertexBuffers.Size());
    
    for (unsigned i = 0; i < originalVertexBuffers.Size(); ++i)
    {
        VertexBuffer* original = originalVertexBuffers[i];
        if (original->HasMorphRange())
        {
            SharedPtr<VertexBuffer> clone(new VertexBuffer(context_));
            clone->SetSize(original->GetVertexCount(), original->GetElementMask(), true);
            void* originalData = original->Lock(0, original->GetVertexCount(), LOCK_NORMAL);
            if (originalData)
            {
                clone->SetData(originalData);
                original->Unlock();
            }
            
            clone->SetMorphRange(original->GetMorphRangeStart(), original->GetMorphRangeCount());
            clone->SetMorphRangeResetData(original->GetMorphRangeResetData());
            
            clonedVertexBuffers[original] = clone;
            morphvertexBuffer_[i] = clone;
        }
    }
    
    // Geometries will always be cloned fully. They contain only references to buffer, so they are relatively light
    for (unsigned i = 0; i < geometries_.Size(); ++i)
    {
        for (unsigned j = 0; j < geometries_[i].Size(); ++j)
        {
            SharedPtr<Geometry> original = geometries_[i][j];
            
            const Vector<SharedPtr<VertexBuffer> >& originalBuffers = original->GetVertexBuffers();
            
            SharedPtr<Geometry> clone(new Geometry(context_));
            clone->SetNumVertexBuffers(originalVertexBuffers.Size());
            for (unsigned k = 0; k < originalVertexBuffers.Size(); ++k)
            {
                VertexBuffer* originalBuffer = originalBuffers[k];
                if (clonedVertexBuffers.Find(originalBuffer) != clonedVertexBuffers.End())
                    clone->SetVertexBuffer(k, clonedVertexBuffers[originalBuffer], original->GetVertexElementMask(k));
                else
                    clone->SetVertexBuffer(k, originalBuffers[k], original->GetVertexElementMask(k));
            }
            
            clone->SetIndexBuffer(original->GetIndexBuffer());
            clone->SetDrawRange(original->GetPrimitiveType(), original->GetIndexStart(), original->GetIndexCount());
            clone->SetLodDistance(original->GetLodDistance());
            
            geometries_[i][j] = clone;
        }
    }
}

void AnimatedModel::RefreshGeometryBoneMappings()
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
    if ((animationLodBias_ > 0.0f) && (animationLodDistance_ > 0.0f))
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
    
    PROFILE(UpdateAnimation);
    
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
    animationDirty_ = false;
}

void AnimatedModel::UpdateSkinning()
{
    PROFILE(UpdateSkinning);
    
    // Note: the model's world transform will be baked in the skin matrices
    const Vector<Bone>& bones = skeleton_.GetBones();
    // Use model's world transform in case a bone is missing
    const Matrix4x3& worldTransform = node_->GetWorldTransform();
    
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
    if (morphs_.Size())
    {
        PROFILE(UpdateMorphs);
        
        // Reset the morph data range from all morphable vertex buffers, then apply morphs
        for (unsigned i = 0; i < morphvertexBuffer_.Size(); ++i)
        {
            VertexBuffer* buffer = morphvertexBuffer_[i];
            if (buffer)
            {
                void* lockedMorphRange = buffer->LockMorphRange();
                if (!lockedMorphRange)
                    continue;
                buffer->ResetMorphRange(lockedMorphRange);
                
                for (unsigned j = 0; j < morphs_.Size(); ++j)
                {
                    if (morphs_[j].weight_ > 0.0f)
                    {
                        Map<unsigned, VertexBufferMorph>::Iterator k = morphs_[j].buffers_.Find(i);
                        if (k != morphs_[j].buffers_.End())
                            ApplyMorph(buffer, lockedMorphRange, k->second_, morphs_[j].weight_);
                    }
                }
                
                buffer->Unlock();
            }
        }
    }
    
    morphsDirty_ = false;
}

void AnimatedModel::ApplyMorph(VertexBuffer* buffer, void* lockedMorphRange, const VertexBufferMorph& morph, float weight)
{
    unsigned elementMask = morph.elementMask_;
    unsigned vertexCount = morph.vertexCount_;
    unsigned normalOffset = buffer->GetElementOffset(ELEMENT_NORMAL);
    unsigned tangentOffset = buffer->GetElementOffset(ELEMENT_TANGENT);
    unsigned morphRangeStart = buffer->GetMorphRangeStart();
    unsigned vertexSize = buffer->GetVertexSize();
    
    unsigned char* srcData = morph.morphData_;
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

void AnimatedModel::HandleModelReloadFinished(StringHash eventType, VariantMap& eventData)
{
    Model* currentModel = model_;
    model_ = 0; // Set null to allow to be re-set
    SetModel(currentModel);
}
