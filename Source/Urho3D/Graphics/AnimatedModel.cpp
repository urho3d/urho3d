//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/AnimatedModel.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationState.h"
#include "../Graphics/Batch.h"
#include "../Graphics/Camera.h"
#include "../Graphics/DebugRenderer.h"
#include "../Graphics/DrawableEvents.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Material.h"
#include "../Graphics/Octree.h"
#include "../Graphics/VertexBuffer.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/ResourceEvents.h"
#include "../Scene/Scene.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;

static const StringVector animationStatesStructureElementNames =
{
    "Anim State Count",
    "   Animation",
    "   Start Bone",
    "   Is Looped",
    "   Weight",
    "   Time",
    "   Layer"
};

static bool CompareAnimationOrder(const SharedPtr<AnimationState>& lhs, const SharedPtr<AnimationState>& rhs)
{
    return lhs->GetLayer() < rhs->GetLayer();
}

static const unsigned MAX_ANIMATION_STATES = 256;

AnimatedModel::AnimatedModel(Context* context) :
    StaticModel(context),
    animationLodFrameNumber_(0),
    morphElementMask_(0),
    animationLodBias_(1.0f),
    animationLodTimer_(-1.0f),
    animationLodDistance_(0.0f),
    updateInvisible_(false),
    animationDirty_(false),
    animationOrderDirty_(false),
    morphsDirty_(false),
    skinningDirty_(true),
    boneBoundingBoxDirty_(true),
    isMaster_(true),
    loading_(false),
    assignBonesPending_(false),
    forceAnimationUpdate_(false)
{
}

AnimatedModel::~AnimatedModel()
{
    // When being destroyed, remove the bone hierarchy if appropriate (last AnimatedModel in the node)
    Bone* rootBone = skeleton_.GetRootBone();
    if (rootBone && rootBone->node_)
    {
        Node* parent = rootBone->node_->GetParent();
        if (parent && !parent->GetComponent<AnimatedModel>())
            RemoveRootBone();
    }
}

void AnimatedModel::RegisterObject(Context* context)
{
    context->RegisterFactory<AnimatedModel>(GEOMETRY_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Model", GetModelAttr, SetModelAttr, ResourceRef, ResourceRef(Model::GetTypeStatic()), AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Material", GetMaterialsAttr, SetMaterialsAttr, ResourceRefList, ResourceRefList(Material::GetTypeStatic()),
        AM_DEFAULT);
    URHO3D_ATTRIBUTE("Is Occluder", bool, occluder_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Cast Shadows", bool, castShadows_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Update When Invisible", GetUpdateInvisible, SetUpdateInvisible, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Shadow Distance", GetShadowDistance, SetShadowDistance, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("LOD Bias", GetLodBias, SetLodBias, float, 1.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Animation LOD Bias", GetAnimationLodBias, SetAnimationLodBias, float, 1.0f, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Drawable);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Bone Animation Enabled", GetBonesEnabledAttr, SetBonesEnabledAttr, VariantVector,
        Variant::emptyVariantVector, AM_FILE | AM_NOEDIT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Animation States", GetAnimationStatesAttr, SetAnimationStatesAttr,
        VariantVector, Variant::emptyVariantVector, AM_FILE)
        .SetMetadata(AttributeMetadata::P_VECTOR_STRUCT_ELEMENTS, animationStatesStructureElementNames);
    URHO3D_ACCESSOR_ATTRIBUTE("Morphs", GetMorphsAttr, SetMorphsAttr, PODVector<unsigned char>, Variant::emptyBuffer,
        AM_DEFAULT | AM_NOEDIT);
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

bool AnimatedModel::LoadJSON(const JSONValue& source)
{
    loading_ = true;
    bool success = Component::LoadJSON(source);
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
    // If no bones or no bone-level testing, use the StaticModel test
    RayQueryLevel level = query.level_;
    if (level < RAY_TRIANGLE || !skeleton_.GetNumBones())
    {
        StaticModel::ProcessRayQuery(query, results);
        return;
    }

    // Check ray hit distance to AABB before proceeding with bone-level tests
    if (query.ray_.HitDistance(GetWorldBoundingBox()) >= query.maxDistance_)
        return;

    const Vector<Bone>& bones = skeleton_.GetBones();
    Sphere boneSphere;

    for (unsigned i = 0; i < bones.Size(); ++i)
    {
        const Bone& bone = bones[i];
        if (!bone.node_)
            continue;

        float distance;

        // Use hitbox if available
        if (bone.collisionMask_ & BONECOLLISION_BOX)
        {
            // Do an initial crude test using the bone's AABB
            const BoundingBox& box = bone.boundingBox_;
            const Matrix3x4& transform = bone.node_->GetWorldTransform();
            distance = query.ray_.HitDistance(box.Transformed(transform));
            if (distance >= query.maxDistance_)
                continue;
            if (level != RAY_AABB)
            {
                // Follow with an OBB test if required
                Matrix3x4 inverse = transform.Inverse();
                Ray localRay = query.ray_.Transformed(inverse);
                distance = localRay.HitDistance(box);
                if (distance >= query.maxDistance_)
                    continue;
            }
        }
        else if (bone.collisionMask_ & BONECOLLISION_SPHERE)
        {
            boneSphere.center_ = bone.node_->GetWorldPosition();
            boneSphere.radius_ = bone.radius_;
            distance = query.ray_.HitDistance(boneSphere);
            if (distance >= query.maxDistance_)
                continue;
        }
        else
            continue;

        // If the code reaches here then we have a hit
        RayQueryResult result;
        result.position_ = query.ray_.origin_ + distance * query.ray_.direction_;
        result.normal_ = -query.ray_.direction_;
        result.distance_ = distance;
        result.drawable_ = this;
        result.node_ = node_;
        result.subObject_ = i;
        results.Push(result);
    }
}

void AnimatedModel::Update(const FrameInfo& frame)
{
    // If node was invisible last frame, need to decide animation LOD distance here
    // If headless, retain the current animation distance (should be 0)
    if (frame.camera_ && abs((int)frame.frameNumber_ - (int)viewFrameNumber_) > 1)
    {
        // First check for no update at all when invisible. In that case reset LOD timer to ensure update
        // next time the model is in view
        if (!updateInvisible_)
        {
            if (animationDirty_)
            {
                animationLodTimer_ = -1.0f;
                forceAnimationUpdate_ = true;
            }
            return;
        }
        float distance = frame.camera_->GetDistance(node_->GetWorldPosition());
        // If distance is greater than draw distance, no need to update at all
        if (drawDistance_ > 0.0f && distance > drawDistance_)
            return;
        float scale = GetWorldBoundingBox().Size().DotProduct(DOT_SCALE);
        animationLodDistance_ = frame.camera_->GetLodDistance(distance, scale, lodBias_);
    }

    if (animationDirty_ || animationOrderDirty_)
        UpdateAnimation(frame);
    else if (boneBoundingBoxDirty_)
        UpdateBoneBoundingBox();
}

void AnimatedModel::UpdateBatches(const FrameInfo& frame)
{
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    const BoundingBox& worldBoundingBox = GetWorldBoundingBox();
    distance_ = frame.camera_->GetDistance(worldBoundingBox.Center());

    // Note: per-geometry distances do not take skinning into account. Especially in case of a ragdoll they may be
    // much off base if the node's own transform is not updated
    if (batches_.Size() == 1)
        batches_[0].distance_ = distance_;
    else
    {
        for (unsigned i = 0; i < batches_.Size(); ++i)
            batches_[i].distance_ = frame.camera_->GetDistance(worldTransform * geometryData_[i].center_);
    }

    // Use a transformed version of the model's bounding box instead of world bounding box for LOD scale
    // determination so that animation does not change the scale
    BoundingBox transformedBoundingBox = boundingBox_.Transformed(worldTransform);
    float scale = transformedBoundingBox.Size().DotProduct(DOT_SCALE);
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
}

void AnimatedModel::UpdateGeometry(const FrameInfo& frame)
{
    // Late update in case the model came into view and animation was dirtied in the meanwhile
    if (forceAnimationUpdate_)
    {
        UpdateAnimation(frame);
        forceAnimationUpdate_ = false;
    }

    if (morphsDirty_)
        UpdateMorphs();

    if (skinningDirty_)
        UpdateSkinning();
}

UpdateGeometryType AnimatedModel::GetUpdateGeometryType()
{
    if (morphsDirty_ || forceAnimationUpdate_)
        return UPDATE_MAIN_THREAD;
    else if (skinningDirty_)
        return UPDATE_WORKER_THREAD;
    else
        return UPDATE_NONE;
}

void AnimatedModel::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (debug && IsEnabledEffective())
    {
        debug->AddBoundingBox(GetWorldBoundingBox(), Color::GREEN, depthTest);
        debug->AddSkeleton(skeleton_, Color(0.75f, 0.75f, 0.75f), depthTest);
    }
}

void AnimatedModel::SetModel(Model* model, bool createBones)
{
    if (model == model_)
        return;

    if (!node_)
    {
        URHO3D_LOGERROR("Can not set model while model component is not attached to a scene node");
        return;
    }

    // Unsubscribe from the reload event of previous model (if any), then subscribe to the new
    if (model_)
        UnsubscribeFromEvent(model_, E_RELOADFINISHED);

    model_ = model;

    if (model)
    {
        SubscribeToEvent(model, E_RELOADFINISHED, URHO3D_HANDLER(AnimatedModel, HandleModelReloadFinished));

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
        geometryBoneMappings_.Reserve(geometryBoneMappings.Size());
        for (unsigned i = 0; i < geometryBoneMappings.Size(); ++i)
            geometryBoneMappings_.Push(geometryBoneMappings[i]);

        // Copy morphs. Note: morph vertex buffers will be created later on-demand
        morphVertexBuffers_.Clear();
        morphs_.Clear();
        const Vector<ModelMorph>& morphs = model->GetMorphs();
        morphs_.Reserve(morphs.Size());
        morphElementMask_ = MASK_NONE;
        for (unsigned i = 0; i < morphs.Size(); ++i)
        {
            ModelMorph newMorph;
            newMorph.name_ = morphs[i].name_;
            newMorph.nameHash_ = morphs[i].nameHash_;
            newMorph.weight_ = 0.0f;
            newMorph.buffers_ = morphs[i].buffers_;
            for (HashMap<unsigned, VertexBufferMorph>::ConstIterator j = morphs[i].buffers_.Begin();
                 j != morphs[i].buffers_.End(); ++j)
                morphElementMask_ |= j->second_.elementMask_;
            morphs_.Push(newMorph);
        }

        // Copy bounding box & skeleton
        SetBoundingBox(model->GetBoundingBox());
        // Initial bone bounding box is just the one stored in the model
        boneBoundingBox_ = boundingBox_;
        boneBoundingBoxDirty_ = true;
        SetSkeleton(model->GetSkeleton(), createBones);
        ResetLodLevels();

        // Reserve space for skinning matrices
        skinMatrices_.Resize(skeleton_.GetNumBones());
        SetGeometryBoneMappings();

        // Enable skinning in batches
        for (unsigned i = 0; i < batches_.Size(); ++i)
        {
            if (skinMatrices_.Size())
            {
                batches_[i].geometryType_ = GEOM_SKINNED;
                // Check if model has per-geometry bone mappings
                if (geometrySkinMatrices_.Size() && geometrySkinMatrices_[i].Size())
                {
                    batches_[i].worldTransform_ = &geometrySkinMatrices_[i][0];
                    batches_[i].numWorldTransforms_ = geometrySkinMatrices_[i].Size();
                }
                // If not, use the global skin matrices
                else
                {
                    batches_[i].worldTransform_ = &skinMatrices_[0];
                    batches_[i].numWorldTransforms_ = skinMatrices_.Size();
                }
            }
            else
            {
                batches_[i].geometryType_ = GEOM_STATIC;
                batches_[i].worldTransform_ = &node_->GetWorldTransform();
                batches_[i].numWorldTransforms_ = 1;
            }
        }
    }
    else
    {
        RemoveRootBone(); // Remove existing root bone if any
        SetNumGeometries(0);
        geometryBoneMappings_.Clear();
        morphVertexBuffers_.Clear();
        morphs_.Clear();
        morphElementMask_ = MASK_NONE;
        SetBoundingBox(BoundingBox());
        SetSkeleton(Skeleton(), false);
    }

    MarkNetworkUpdate();
}

AnimationState* AnimatedModel::AddAnimationState(Animation* animation)
{
    if (!isMaster_)
    {
        URHO3D_LOGERROR("Can not add animation state to non-master model");
        return nullptr;
    }

    if (!animation || !skeleton_.GetNumBones())
        return nullptr;

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
    else
    {
        for (Vector<SharedPtr<AnimationState> >::Iterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
        {
            AnimationState* state = *i;
            if (!state->GetAnimation())
            {
                animationStates_.Erase(i);
                MarkAnimationDirty();
                return;
            }
        }
    }
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
        if (animation)
        {
            // Check both the animation and the resource name
            if (animation->GetNameHash() == animationNameHash || animation->GetAnimationNameHash() == animationNameHash)
            {
                animationStates_.Erase(i);
                MarkAnimationDirty();
                return;
            }
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

void AnimatedModel::RemoveAnimationState(unsigned index)
{
    if (index < animationStates_.Size())
    {
        animationStates_.Erase(index);
        MarkAnimationDirty();
    }
}

void AnimatedModel::RemoveAllAnimationStates()
{
    if (animationStates_.Size())
    {
        animationStates_.Clear();
        MarkAnimationDirty();
    }
}

void AnimatedModel::SetAnimationLodBias(float bias)
{
    animationLodBias_ = Max(bias, 0.0f);
    MarkNetworkUpdate();
}

void AnimatedModel::SetUpdateInvisible(bool enable)
{
    updateInvisible_ = enable;
    MarkNetworkUpdate();
}


void AnimatedModel::SetMorphWeight(unsigned index, float weight)
{
    if (index >= morphs_.Size())
        return;

    // If morph vertex buffers have not been created yet, create now
    if (weight != 0.0f && morphVertexBuffers_.Empty())
        CloneGeometries();

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

    return nullptr;
}

AnimationState* AnimatedModel::GetAnimationState(const String& animationName) const
{
    return GetAnimationState(StringHash(animationName));
}

AnimationState* AnimatedModel::GetAnimationState(StringHash animationNameHash) const
{
    for (Vector<SharedPtr<AnimationState> >::ConstIterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
    {
        Animation* animation = (*i)->GetAnimation();
        if (animation)
        {
            // Check both the animation and the resource name
            if (animation->GetNameHash() == animationNameHash || animation->GetAnimationNameHash() == animationNameHash)
                return *i;
        }
    }

    return nullptr;
}

AnimationState* AnimatedModel::GetAnimationState(unsigned index) const
{
    return index < animationStates_.Size() ? animationStates_[index].Get() : nullptr;
}

void AnimatedModel::SetSkeleton(const Skeleton& skeleton, bool createBones)
{
    if (!node_ && createBones)
    {
        URHO3D_LOGERROR("AnimatedModel not attached to a scene node, can not create bone nodes");
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
            RemoveRootBone();

        skeleton_.Define(skeleton);

        // Merge bounding boxes from non-master models
        FinalizeBoneBoundingBoxes();

        Vector<Bone>& bones = skeleton_.GetModifiableBones();
        // Create scene nodes for the bones
        if (createBones)
        {
            for (Vector<Bone>::Iterator i = bones.Begin(); i != bones.End(); ++i)
            {
                // Create bones as local, as they are never to be directly synchronized over the network
                Node* boneNode = node_->CreateChild(i->name_, LOCAL);
                boneNode->AddListener(this);
                boneNode->SetTransform(i->initialPosition_, i->initialRotation_, i->initialScale_);
                // Copy the model component's temporary status
                boneNode->SetTemporary(IsTemporary());
                i->node_ = boneNode;
            }

            for (unsigned i = 0; i < bones.Size(); ++i)
            {
                unsigned parentIndex = bones[i].parentIndex_;
                if (parentIndex != i && parentIndex < bones.Size())
                    bones[parentIndex].node_->AddChild(bones[i].node_);
            }
        }

        using namespace BoneHierarchyCreated;

        VariantMap& eventData = GetEventDataMap();
        eventData[P_NODE] = node_;
        node_->SendEvent(E_BONEHIERARCHYCREATED, eventData);
    }
    else
    {
        // For non-master models: use the bone nodes of the master model
        skeleton_.Define(skeleton);

        // Instruct the master model to refresh (merge) its bone bounding boxes
        auto* master = node_->GetComponent<AnimatedModel>();
        if (master && master != this)
            master->FinalizeBoneBoundingBoxes();

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

    assignBonesPending_ = !createBones;
}

void AnimatedModel::SetModelAttr(const ResourceRef& value)
{
    auto* cache = GetSubsystem<ResourceCache>();
    // When loading a scene, set model without creating the bone nodes (will be assigned later during post-load)
    SetModel(cache->GetResource<Model>(value.name_), !loading_);
}

void AnimatedModel::SetBonesEnabledAttr(const VariantVector& value)
{
    Vector<Bone>& bones = skeleton_.GetModifiableBones();
    for (unsigned i = 0; i < bones.Size() && i < value.Size(); ++i)
        bones[i].animated_ = value[i].GetBool();
}

void AnimatedModel::SetAnimationStatesAttr(const VariantVector& value)
{
    auto* cache = GetSubsystem<ResourceCache>();
    RemoveAllAnimationStates();
    unsigned index = 0;
    unsigned numStates = index < value.Size() ? value[index++].GetUInt() : 0;
    // Prevent negative or overly large value being assigned from the editor
    if (numStates > M_MAX_INT)
        numStates = 0;
    if (numStates > MAX_ANIMATION_STATES)
        numStates = MAX_ANIMATION_STATES;

    animationStates_.Reserve(numStates);
    while (numStates--)
    {
        if (index + 5 < value.Size())
        {
            // Note: null animation is allowed here for editing
            const ResourceRef& animRef = value[index++].GetResourceRef();
            SharedPtr<AnimationState> newState(new AnimationState(this, cache->GetResource<Animation>(animRef.name_)));
            animationStates_.Push(newState);

            newState->SetStartBone(skeleton_.GetBone(value[index++].GetString()));
            newState->SetLooped(value[index++].GetBool());
            newState->SetWeight(value[index++].GetFloat());
            newState->SetTime(value[index++].GetFloat());
            newState->SetLayer((unsigned char)value[index++].GetInt());
        }
        else
        {
            // If not enough data, just add an empty animation state
            SharedPtr<AnimationState> newState(new AnimationState(this, nullptr));
            animationStates_.Push(newState);
        }
    }

    if (animationStates_.Size())
    {
        MarkAnimationDirty();
        MarkAnimationOrderDirty();
    }
}

void AnimatedModel::SetMorphsAttr(const PODVector<unsigned char>& value)
{
    for (unsigned index = 0; index < value.Size(); ++index)
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
    ret.Reserve(bones.Size());
    for (Vector<Bone>::ConstIterator i = bones.Begin(); i != bones.End(); ++i)
        ret.Push(i->animated_);
    return ret;
}

VariantVector AnimatedModel::GetAnimationStatesAttr() const
{
    VariantVector ret;
    ret.Reserve(animationStates_.Size() * 6 + 1);
    ret.Push(animationStates_.Size());
    for (Vector<SharedPtr<AnimationState> >::ConstIterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
    {
        AnimationState* state = *i;
        Animation* animation = state->GetAnimation();
        Bone* startBone = state->GetStartBone();
        ret.Push(GetResourceRef(animation, Animation::GetTypeStatic()));
        ret.Push(startBone ? startBone->name_ : String::EMPTY);
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

void AnimatedModel::UpdateBoneBoundingBox()
{
    if (skeleton_.GetNumBones())
    {
        // The bone bounding box is in local space, so need the node's inverse transform
        boneBoundingBox_.Clear();
        Matrix3x4 inverseNodeTransform = node_->GetWorldTransform().Inverse();

        const Vector<Bone>& bones = skeleton_.GetBones();
        for (Vector<Bone>::ConstIterator i = bones.Begin(); i != bones.End(); ++i)
        {
            Node* boneNode = i->node_;
            if (!boneNode)
                continue;

            // Use hitbox if available. If not, use only half of the sphere radius
            /// \todo The sphere radius should be multiplied with bone scale
            if (i->collisionMask_ & BONECOLLISION_BOX)
                boneBoundingBox_.Merge(i->boundingBox_.Transformed(inverseNodeTransform * boneNode->GetWorldTransform()));
            else if (i->collisionMask_ & BONECOLLISION_SPHERE)
                boneBoundingBox_.Merge(Sphere(inverseNodeTransform * boneNode->GetWorldPosition(), i->radius_ * 0.5f));
        }
    }

    boneBoundingBoxDirty_ = false;
    worldBoundingBoxDirty_ = true;
}

void AnimatedModel::OnNodeSet(Node* node)
{
    Drawable::OnNodeSet(node);

    if (node)
    {
        // If this AnimatedModel is the first in the node, it is the master which controls animation & morphs
        isMaster_ = GetComponent<AnimatedModel>() == this;
    }
}

void AnimatedModel::OnMarkedDirty(Node* node)
{
    Drawable::OnMarkedDirty(node);

    // If the scene node or any of the bone nodes move, mark skinning dirty
    if (skeleton_.GetNumBones())
    {
        skinningDirty_ = true;
        // Bone bounding box doesn't need to be marked dirty when only the base scene node moves
        if (node != node_)
            boneBoundingBoxDirty_ = true;
    }
}

void AnimatedModel::OnWorldBoundingBoxUpdate()
{
    if (isMaster_)
    {
        // Note: do not update bone bounding box here, instead do it in either of the threaded updates
        worldBoundingBox_ = boneBoundingBox_.Transformed(node_->GetWorldTransform());
    }
    else
    {
        // Non-master animated models get the bounding box from the master
        /// \todo If it's a skinned attachment that does not cover the whole body, it will have unnecessarily large bounds
        auto* master = node_->GetComponent<AnimatedModel>();
        // Check if we've become the new master model in case the original was deleted
        if (master == this)
            isMaster_ = true;
        if (master)
            worldBoundingBox_ = master->GetWorldBoundingBox();
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
}

void AnimatedModel::FinalizeBoneBoundingBoxes()
{
    Vector<Bone>& bones = skeleton_.GetModifiableBones();
    PODVector<AnimatedModel*> models;
    GetComponents<AnimatedModel>(models);

    if (models.Size() > 1)
    {
        // Reset first to the model resource's original bone bounding information if available (should be)
        if (model_)
        {
            const Vector<Bone>& modelBones = model_->GetSkeleton().GetBones();
            for (unsigned i = 0; i < bones.Size() && i < modelBones.Size(); ++i)
            {
                bones[i].collisionMask_ = modelBones[i].collisionMask_;
                bones[i].radius_ = modelBones[i].radius_;
                bones[i].boundingBox_ = modelBones[i].boundingBox_;
            }
        }

        // Get matching bones from all non-master models and merge their bone bounding information
        // to prevent culling errors (master model may not have geometry in all bones, or the bounds are smaller)
        for (PODVector<AnimatedModel*>::Iterator i = models.Begin(); i != models.End(); ++i)
        {
            if ((*i) == this)
                continue;

            Skeleton& otherSkeleton = (*i)->GetSkeleton();
            for (Vector<Bone>::Iterator j = bones.Begin(); j != bones.End(); ++j)
            {
                Bone* otherBone = otherSkeleton.GetBone(j->nameHash_);
                if (otherBone)
                {
                    if (otherBone->collisionMask_ & BONECOLLISION_SPHERE)
                    {
                        j->collisionMask_ |= BONECOLLISION_SPHERE;
                        j->radius_ = Max(j->radius_, otherBone->radius_);
                    }
                    if (otherBone->collisionMask_ & BONECOLLISION_BOX)
                    {
                        j->collisionMask_ |= BONECOLLISION_BOX;
                        if (j->boundingBox_.Defined())
                            j->boundingBox_.Merge(otherBone->boundingBox_);
                        else
                            j->boundingBox_.Define(otherBone->boundingBox_);
                    }
                }
            }
        }
    }

    // Remove collision information from dummy bones that do not affect skinning, to prevent them from being merged
    // to the bounding box and making it artificially large
    for (Vector<Bone>::Iterator i = bones.Begin(); i != bones.End(); ++i)
    {
        if (i->collisionMask_ & BONECOLLISION_BOX && i->boundingBox_.Size().Length() < M_EPSILON)
            i->collisionMask_ &= ~BONECOLLISION_BOX;
        if (i->collisionMask_ & BONECOLLISION_SPHERE && i->radius_ < M_EPSILON)
            i->collisionMask_ &= ~BONECOLLISION_SPHERE;
    }
}

void AnimatedModel::RemoveRootBone()
{
    Bone* rootBone = skeleton_.GetRootBone();
    if (rootBone && rootBone->node_)
        rootBone->node_->Remove();
}

void AnimatedModel::MarkAnimationDirty()
{
    if (isMaster_)
    {
        animationDirty_ = true;
        MarkForUpdate();
    }
}

void AnimatedModel::MarkAnimationOrderDirty()
{
    if (isMaster_)
    {
        animationOrderDirty_ = true;
        MarkForUpdate();
    }
}

void AnimatedModel::MarkMorphsDirty()
{
    morphsDirty_ = true;
}

void AnimatedModel::CloneGeometries()
{
    const Vector<SharedPtr<VertexBuffer> >& originalVertexBuffers = model_->GetVertexBuffers();
    HashMap<VertexBuffer*, SharedPtr<VertexBuffer> > clonedVertexBuffers;
    morphVertexBuffers_.Resize(originalVertexBuffers.Size());

    for (unsigned i = 0; i < originalVertexBuffers.Size(); ++i)
    {
        VertexBuffer* original = originalVertexBuffers[i];
        if (model_->GetMorphRangeCount(i))
        {
            SharedPtr<VertexBuffer> clone(new VertexBuffer(context_));
            clone->SetShadowed(true);
            clone->SetSize(original->GetVertexCount(), morphElementMask_ & original->GetElementMask(), true);
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

                if (clonedVertexBuffers.Contains(originalBuffer))
                {
                    VertexBuffer* clonedBuffer = clonedVertexBuffers[originalBuffer];
                    clone->SetVertexBuffer(l++, originalBuffer);
                    // Specify the morph buffer at a greater index to override the model's original positions/normals/tangents
                    clone->SetVertexBuffer(l++, clonedBuffer);
                }
                else
                    clone->SetVertexBuffer(l++, originalBuffer);
            }

            clone->SetIndexBuffer(original->GetIndexBuffer());
            clone->SetDrawRange(original->GetPrimitiveType(), original->GetIndexStart(), original->GetIndexCount());
            clone->SetLodDistance(original->GetLodDistance());

            geometries_[i][j] = clone;
        }
    }

    // Make sure the rendering batches use the new cloned geometries
    ResetLodLevels();
    MarkMorphsDirty();
}

void AnimatedModel::CopyMorphVertices(void* destVertexData, void* srcVertexData, unsigned vertexCount, VertexBuffer* destBuffer,
    VertexBuffer* srcBuffer)
{
    unsigned mask = destBuffer->GetElementMask() & srcBuffer->GetElementMask();
    unsigned normalOffset = srcBuffer->GetElementOffset(SEM_NORMAL);
    unsigned tangentOffset = srcBuffer->GetElementOffset(SEM_TANGENT);
    unsigned vertexSize = srcBuffer->GetVertexSize();
    auto* dest = (float*)destVertexData;
    auto* src = (unsigned char*)srcVertexData;

    while (vertexCount--)
    {
        if (mask & MASK_POSITION)
        {
            auto* posSrc = (float*)src;
            dest[0] = posSrc[0];
            dest[1] = posSrc[1];
            dest[2] = posSrc[2];
            dest += 3;
        }
        if (mask & MASK_NORMAL)
        {
            auto* normalSrc = (float*)(src + normalOffset);
            dest[0] = normalSrc[0];
            dest[1] = normalSrc[1];
            dest[2] = normalSrc[2];
            dest += 3;
        }
        if (mask & MASK_TANGENT)
        {
            auto* tangentSrc = (float*)(src + tangentOffset);
            dest[0] = tangentSrc[0];
            dest[1] = tangentSrc[1];
            dest[2] = tangentSrc[2];
            dest[3] = tangentSrc[3];
            dest += 4;
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
        // Perform the first update always regardless of LOD timer
        if (animationLodTimer_ >= 0.0f)
        {
            animationLodTimer_ += animationLodBias_ * frame.timeStep_ * ANIMATION_LOD_BASESCALE;
            if (animationLodTimer_ >= animationLodDistance_)
                animationLodTimer_ = fmodf(animationLodTimer_, animationLodDistance_);
            else
                return;
        }
        else
            animationLodTimer_ = 0.0f;
    }

    ApplyAnimation();
}

void AnimatedModel::ApplyAnimation()
{
    // Make sure animations are in ascending priority order
    if (animationOrderDirty_)
    {
        Sort(animationStates_.Begin(), animationStates_.End(), CompareAnimationOrder);
        animationOrderDirty_ = false;
    }

    // Reset skeleton, apply all animations, calculate bones' bounding box. Make sure this is only done for the master model
    // (first AnimatedModel in a node)
    if (isMaster_)
    {
        skeleton_.ResetSilent();
        for (Vector<SharedPtr<AnimationState> >::Iterator i = animationStates_.Begin(); i != animationStates_.End(); ++i)
            (*i)->Apply();

        // Skeleton reset and animations apply the node transforms "silently" to avoid repeated marking dirty. Mark dirty now
        node_->MarkDirty();

        // Calculate new bone bounding box
        UpdateBoneBoundingBox();
    }

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
    auto* graphics = GetSubsystem<Graphics>();
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

                void* dest = buffer->Lock(morphStart, morphCount);
                if (dest)
                {
                    // Reset morph range by copying data from the original vertex buffer
                    CopyMorphVertices(dest, originalBuffer->GetShadowData() + morphStart * originalBuffer->GetVertexSize(),
                        morphCount, buffer, originalBuffer);

                    for (unsigned j = 0; j < morphs_.Size(); ++j)
                    {
                        if (morphs_[j].weight_ != 0.0f)
                        {
                            HashMap<unsigned, VertexBufferMorph>::Iterator k = morphs_[j].buffers_.Find(i);
                            if (k != morphs_[j].buffers_.End())
                                ApplyMorph(buffer, dest, morphStart, k->second_, morphs_[j].weight_);
                        }
                    }

                    buffer->Unlock();
                }
            }
        }
    }

    morphsDirty_ = false;
}

void AnimatedModel::ApplyMorph(VertexBuffer* buffer, void* destVertexData, unsigned morphRangeStart, const VertexBufferMorph& morph,
    float weight)
{
    const VertexMaskFlags elementMask = morph.elementMask_ & buffer->GetElementMask();
    unsigned vertexCount = morph.vertexCount_;
    unsigned normalOffset = buffer->GetElementOffset(SEM_NORMAL);
    unsigned tangentOffset = buffer->GetElementOffset(SEM_TANGENT);
    unsigned vertexSize = buffer->GetVertexSize();

    unsigned char* srcData = morph.morphData_;
    auto* destData = (unsigned char*)destVertexData;

    while (vertexCount--)
    {
        unsigned vertexIndex = *((unsigned*)srcData) - morphRangeStart;
        srcData += sizeof(unsigned);

        if (elementMask & MASK_POSITION)
        {
            auto* dest = (float*)(destData + vertexIndex * vertexSize);
            auto* src = (float*)srcData;
            dest[0] += src[0] * weight;
            dest[1] += src[1] * weight;
            dest[2] += src[2] * weight;
            srcData += 3 * sizeof(float);
        }
        if (elementMask & MASK_NORMAL)
        {
            auto* dest = (float*)(destData + vertexIndex * vertexSize + normalOffset);
            auto* src = (float*)srcData;
            dest[0] += src[0] * weight;
            dest[1] += src[1] * weight;
            dest[2] += src[2] * weight;
            srcData += 3 * sizeof(float);
        }
        if (elementMask & MASK_TANGENT)
        {
            auto* dest = (float*)(destData + vertexIndex * vertexSize + tangentOffset);
            auto* src = (float*)srcData;
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
    model_.Reset(); // Set null to allow to be re-set
    SetModel(currentModel);
}

}
