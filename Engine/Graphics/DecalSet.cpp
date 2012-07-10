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
#include "Batch.h"
#include "Camera.h"
#include "Context.h"
#include "DecalSet.h"
#include "Geometry.h"
#include "Graphics.h"
#include "Log.h"
#include "Node.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

static const Vector3 DOT_SCALE(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);
static const unsigned DEFAULT_MAX_VERTICES = 512;
static const unsigned STATIC_ELEMENT_MASK = MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1 | MASK_TANGENT;
static const unsigned SKINNED_ELEMENT_MASK = MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1 | MASK_TANGENT | MASK_BLENDWEIGHTS |
    MASK_BLENDINDICES;

static DecalVertex ClipEdge(const DecalVertex& v0, const DecalVertex& v1, float d0, float d1, bool skinned)
{
    DecalVertex ret;
    float t = d0 / (d0 - d1);
    
    ret.position_ = v0.position_ + t * (v1.position_ - v0.position_);
    ret.normal_ = v0.normal_ + t * (v1.normal_ - v0.normal_);
    if (skinned)
    {
        // Blend weights / indices can not be easily interpolated, choose the one that is nearer to the split plane
        const DecalVertex& src = Abs(d0) < Abs(d1) ? v0 : v1;
        for (unsigned i = 0; i < 4; ++i)
        {
            ret.blendWeights_[i] = src.blendWeights_[i];
            ret.blendIndices_[i] = src.blendIndices_[i];
        }
    }
    
    return ret;
}

static void ClipPolygon(PODVector<DecalVertex>& dest, const PODVector<DecalVertex>& src, const Plane& plane, bool skinned)
{
    unsigned last;
    float lastDistance = 0.0f;
    dest.Clear();
    
    if (src.Empty())
        return;
    
    for (unsigned i = 0; i < src.Size(); ++i)
    {
        float distance = plane.Distance(src[i].position_);
        if (distance >= 0.0f)
        {
            if (lastDistance < 0.0f)
                dest.Push(ClipEdge(src[last], src[i], lastDistance, distance, skinned));
            
            dest.Push(src[i]);
        }
        else
        {
            if (lastDistance >= 0.0f && i != 0)
                dest.Push(ClipEdge(src[last], src[i], lastDistance, distance, skinned));
        }
        
        last = i;
        lastDistance = distance;
    }
    
    // Recheck the distances of the last and first vertices and add the final clipped vertex if applicable
    float distance = plane.Distance(src[0].position_);
    if ((lastDistance < 0.0f && distance >= 0.0f) || (lastDistance >= 0.0f && distance < 0.0f))
        dest.Push(ClipEdge(src[last], src[0], lastDistance, distance, skinned));
}

void Decal::CalculateBoundingBox()
{
    boundingBox_.Clear();
    for (unsigned i = 0; i < vertices_.Size(); ++i)
        boundingBox_.Merge(vertices_[i].position_);
}

OBJECTTYPESTATIC(DecalSet);

DecalSet::DecalSet(Context* context) :
    Drawable(context),
    geometry_(new Geometry(context)),
    vertexBuffer_(new VertexBuffer(context_)),
    numVertices_(0),
    maxVertices_(DEFAULT_MAX_VERTICES),
    skinned_(false),
    bufferSizeDirty_(true),
    bufferDirty_(true),
    boundingBoxDirty_(true),
    skinningDirty_(false),
    assignBonesPending_(false)
{
    drawableFlags_ = DRAWABLE_GEOMETRY;
    
    batches_.Resize(1);
    batches_[0].geometry_ = geometry_;
}

DecalSet::~DecalSet()
{
}

void DecalSet::RegisterObject(Context* context)
{
    context->RegisterFactory<DecalSet>();
    
    ACCESSOR_ATTRIBUTE(DecalSet, VAR_RESOURCEREF, "Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()), AM_DEFAULT);
    ATTRIBUTE(DecalSet, VAR_BOOL, "Is Visible", visible_, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(DecalSet, VAR_BOOL, "Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(DecalSet, VAR_FLOAT, "Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(DecalSet, VAR_INT, "Max Vertices", GetMaxVertices, SetMaxVertices, unsigned, DEFAULT_MAX_VERTICES, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(DecalSet, Drawable);
    ACCESSOR_ATTRIBUTE(DecalSet, VAR_VARIANTVECTOR, "Decals", GetDecalsAttr, SetDecalsAttr, VariantVector, VariantVector(), AM_FILE | AM_NOEDIT);
}

void DecalSet::ApplyAttributes()
{
    if (assignBonesPending_)
        AssignBoneNodes();
}

void DecalSet::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    // Do not return raycast hits
}

void DecalSet::UpdateBatches(const FrameInfo& frame)
{
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    distance_ = frame.camera_->GetDistance(GetWorldBoundingBox().Center());
    
    float scale = GetWorldBoundingBox().Size().DotProduct(DOT_SCALE);
    lodDistance_ = frame.camera_->GetLodDistance(distance_, scale, lodBias_);
    
    batches_[0].distance_ = distance_;
    batches_[0].worldTransform_ = &worldTransform;
}

void DecalSet::UpdateGeometry(const FrameInfo& frame)
{
    if (bufferSizeDirty_)
        UpdateBufferSize();
    
    if (bufferDirty_ || vertexBuffer_->IsDataLost())
        UpdateVertexBuffer();
    
    if (skinningDirty_)
        UpdateSkinning();
}

UpdateGeometryType DecalSet::GetUpdateGeometryType()
{
    if (bufferDirty_ || bufferSizeDirty_ || vertexBuffer_->IsDataLost())
        return UPDATE_MAIN_THREAD;
    else if (skinningDirty_)
        return UPDATE_WORKER_THREAD;
    else
        return UPDATE_NONE;
}

void DecalSet::SetMaterial(Material* material)
{
    batches_[0].material_ = material;
    MarkNetworkUpdate();
}

void DecalSet::SetMaxVertices(unsigned num)
{
    if (num != maxVertices_)
    {
        bufferSizeDirty_ = true;
        maxVertices_ = num;
        
        while (decals_.Size() && numVertices_ > maxVertices_)
            RemoveDecals(1);
        
        MarkNetworkUpdate();
    }
}

bool DecalSet::AddDecal(Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size,
    float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive, float normalCutoff,
    float depthBias)
{
    PROFILE(AddDecal);
    
    if (!node_)
        return false;
    
    if (!target || !target->GetNode())
    {
        LOGERROR("Null target drawable for decal");
        return false;
    }
    
    // Check for animated target and switch into skinned/static mode if necessary
    AnimatedModel* animatedModel = dynamic_cast<AnimatedModel*>(target);
    if ((animatedModel && !skinned_) || (!animatedModel && skinned_))
    {
        RemoveAllDecals();
        skinned_ = animatedModel != 0;
        bufferSizeDirty_ = true;
    }
    
    Matrix3x4 targetTransform = target->GetNode()->GetWorldTransform().Inverse();
    
    // For an animated model, adjust the decal position back to the bind pose
    // To do this, need to find the bone the decal is colliding with
    if (animatedModel)
    {
        Skeleton& skeleton = animatedModel->GetSkeleton();
        unsigned numBones = skeleton.GetNumBones();
        unsigned bestIndex = M_MAX_UNSIGNED;
        float bestDistance = M_INFINITY;
        
        for (unsigned i = 0; i < numBones; ++i)
        {
            Bone* bone = skeleton.GetBone(i);
            if (!bone->node_ || !bone->collisionMask_)
                continue;
            
            // Represent the decal as a sphere, try to find the closest match
            Sphere decalSphere(bone->node_->GetWorldTransform().Inverse() * (worldPosition + worldRotation * (0.5f * depth *
                Vector3::FORWARD)), size);
            float distance = (worldPosition - bone->node_->GetWorldPosition()).Length();
            
            if (bone->collisionMask_ & BONECOLLISION_BOX)
            {
                if (bone->boundingBox_.IsInside(decalSphere) != OUTSIDE && distance < bestDistance)
                {
                    bestIndex = i;
                    bestDistance = distance;
                }
            }
            else if (bone->collisionMask_ & BONECOLLISION_SPHERE)
            {
                Sphere boneSphere(Vector3::ZERO, bone->radius_);
                if (boneSphere.IsInside(decalSphere) != OUTSIDE && distance < bestDistance)
                {
                    bestIndex = i;
                    bestDistance = distance;
                }
            }
        }
        
        if (bestIndex < numBones)
        {
            Bone* bone = skeleton.GetBone(bestIndex);
            targetTransform = (bone->node_->GetWorldTransform() * bone->offsetMatrix_).Inverse();
        }
    }
    
    // Build the decal frustum
    Frustum decalFrustum;
    Matrix3x4 frustumTransform = targetTransform * Matrix3x4(worldPosition, worldRotation, 1.0f);
    decalFrustum.DefineOrtho(size, aspectRatio, 1.0, 0.0f, depth, frustumTransform);
    
    Vector3 biasVector = targetTransform * Vector4(worldRotation * (Vector3::BACK * depthBias), 0.0f);
    Vector3 decalNormal = (targetTransform * Vector4(worldRotation * Vector3::BACK, 0.0f)).Normalized();
    
    decals_.Resize(decals_.Size() + 1);
    Decal& newDecal = decals_.Back();
    newDecal.timeToLive_ = timeToLive;
    
    Vector<PODVector<DecalVertex> > faces;
    PODVector<DecalVertex> tempFace;
    
    unsigned numBatches = target->GetBatches().Size();
    for (unsigned i = 0; i < numBatches; ++i)
        GetFaces(faces, target, i, decalFrustum, decalNormal, normalCutoff);
    
    // Clip the acquired faces against all frustum planes
    for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
    {
        for (unsigned j = 0; j < faces.Size(); ++j)
        {
            PODVector<DecalVertex>& face = faces[j];
            if (face.Empty())
                continue;
            
            ClipPolygon(tempFace, face, decalFrustum.planes_[i], skinned_);
            face = tempFace;
        }
    }
    
    // Now triangulate the resulting faces into decal vertices
    for (unsigned i = 0; i < faces.Size(); ++i)
    {
        PODVector<DecalVertex>& face = faces[i];
        if (face.Size() < 3)
            continue;
        
        for (unsigned j = 2; j < face.Size(); ++j)
        {
            newDecal.vertices_.Push(face[0]);
            newDecal.vertices_.Push(face[j - 1]);
            newDecal.vertices_.Push(face[j]);
        }
    }
    
    // Check if resulted in no triangles
    if (newDecal.vertices_.Empty())
    {
        decals_.Pop();
        return true;
    }
    
    if (newDecal.vertices_.Size() > maxVertices_)
    {
        LOGWARNING("Can not add decal, vertex count " + String(newDecal.vertices_.Size()) + " exceeds maximum " +
            String(maxVertices_));
        decals_.Pop();
        return false;
    }
    
    // Finally transform vertices to this node's local space
    Matrix3x4 decalTransform = node_->GetWorldTransform().Inverse() * target->GetNode()->GetWorldTransform();
    CalculateUVs(newDecal, frustumTransform.Inverse(), size, aspectRatio, depth, topLeftUV, bottomRightUV);
    TransformVertices(newDecal, skinned_ ? Matrix3x4::IDENTITY : decalTransform, biasVector);
    CalculateTangents(newDecal);
    
    newDecal.CalculateBoundingBox();
    numVertices_ += newDecal.vertices_.Size();
    
    // Subscribe to scene post-update if defined a time-limited decal
    Scene* scene = GetScene();
    if (newDecal.timeToLive_ > 0.0f && scene && !HasSubscribedToEvent(scene, E_SCENEPOSTUPDATE))
        SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(DecalSet, HandleScenePostUpdate));
    
    // Remove oldest decals if total vertices exceeded
    while (decals_.Size() && numVertices_ > maxVertices_)
        RemoveDecals(1);
    
    LOGDEBUG("Added decal with " + String(newDecal.vertices_.Size()) + " vertices");
    
    MarkDecalsDirty();
    return true;
}

void DecalSet::RemoveDecals(unsigned num)
{
    while (decals_.Size() && num)
    {
        RemoveDecal(decals_.Begin());
        --num;
    }
}

void DecalSet::RemoveAllDecals()
{
    if (!decals_.Empty())
    {
        decals_.Clear();
        numVertices_ = 0;
        MarkDecalsDirty();
    }
    
    // Remove all bones and skinning matrices and stop listening to the bone nodes
    for (Vector<Bone>::Iterator i = bones_.Begin(); i != bones_.End(); ++i)
    {
        if (i->node_)
            i->node_->RemoveListener(this);
    }
    
    bones_.Clear();
    skinMatrices_.Clear();
    UpdateBatch();
}

Material* DecalSet::GetMaterial() const
{
    return batches_[0].material_;
}

void DecalSet::SetMaterialAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetMaterial(cache->GetResource<Material>(value.id_));
}

void DecalSet::SetDecalsAttr(VariantVector value)
{
    unsigned index = 0;
    
    Scene* scene = GetScene();
    RemoveAllDecals();
    
    skinned_ = value[index++].GetBool();
    unsigned numDecals = value[index++].GetInt();
    
    while (numDecals--)
    {
        decals_.Resize(decals_.Size() + 1);
        Decal& newDecal = decals_.Back();
        
        newDecal.timer_ = value[index++].GetFloat();
        newDecal.timeToLive_ = value[index++].GetFloat();
        newDecal.vertices_.Resize(value[index++].GetInt());
        
        for (PODVector<DecalVertex>::Iterator i = newDecal.vertices_.Begin(); i != newDecal.vertices_.End(); ++i)
        {
            i->position_ = value[index++].GetVector3();
            i->normal_ = value[index++].GetVector3();
            i->texCoord_ = value[index++].GetVector2();
            i->tangent_ = value[index++].GetVector4();
            if (skinned_)
            {
                Vector4 weights = value[index++].GetVector4();
                unsigned indices = value[index++].GetInt();
                i->blendWeights_[0] = weights.x_;
                i->blendWeights_[1] = weights.y_;
                i->blendWeights_[2] = weights.z_;
                i->blendWeights_[3] = weights.w_;
                *((unsigned*)i->blendIndices_) = indices;
            }
        }
        
        newDecal.CalculateBoundingBox();
        numVertices_ += newDecal.vertices_.Size();
        
        // Subscribe to scene post-update if defined a time-limited decal
        if (newDecal.timeToLive_ > 0.0f && scene && !HasSubscribedToEvent(scene, E_SCENEPOSTUPDATE))
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(DecalSet, HandleScenePostUpdate));
    }
    
    if (skinned_)
    {
        unsigned numBones = value[index++].GetInt();
        skinMatrices_.Resize(numBones);
        
        while (numBones--)
        {
            bones_.Resize(bones_.Size() + 1);
            Bone& newBone = bones_.Back();
            
            newBone.name_ = value[index++].GetString();
            newBone.collisionMask_ = value[index++].GetInt();
            if (newBone.collisionMask_ & BONECOLLISION_SPHERE)
                newBone.radius_ = value[index++].GetFloat();
            if (newBone.collisionMask_ & BONECOLLISION_BOX)
            {
                newBone.boundingBox_.min_ = value[index++].GetVector3();
                newBone.boundingBox_.max_ = value[index++].GetVector3();
                newBone.boundingBox_.defined_ = true;
            }
            
            Vector4* offsetMatrix = (Vector4*)newBone.offsetMatrix_.Data();
            offsetMatrix[0] = value[index++].GetVector4();
            offsetMatrix[1] = value[index++].GetVector4();
            offsetMatrix[2] = value[index++].GetVector4();
        }
        
        assignBonesPending_ = true;
        skinningDirty_ = true;
    }
    
    UpdateBatch();
    MarkDecalsDirty();
    bufferSizeDirty_ = true;
}

ResourceRef DecalSet::GetMaterialAttr() const
{
    return GetResourceRef(batches_[0].material_, Material::GetTypeStatic());
}

VariantVector DecalSet::GetDecalsAttr() const
{
    VariantVector ret;
    ret.Push(skinned_);
    ret.Push(decals_.Size());
    
    for (List<Decal>::ConstIterator i = decals_.Begin(); i != decals_.End(); ++i)
    {
        ret.Push(i->timer_);
        ret.Push(i->timeToLive_);
        ret.Push(i->vertices_.Size());
        
        for (PODVector<DecalVertex>::ConstIterator j = i->vertices_.Begin(); j != i->vertices_.End(); ++j)
        {
            ret.Push(j->position_);
            ret.Push(j->normal_);
            ret.Push(j->texCoord_);
            ret.Push(j->tangent_);
            if (skinned_)
            {
                unsigned* indices = (unsigned*)j->blendIndices_;
                ret.Push(Vector4(j->blendWeights_[0], j->blendWeights_[1], j->blendWeights_[2], j->blendWeights_[3]));
                ret.Push(*indices);
            }
        }
    }
    
    if (skinned_)
    {
        ret.Push(bones_.Size());
        
        for (Vector<Bone>::ConstIterator i = bones_.Begin(); i != bones_.End(); ++i)
        {
            ret.Push(i->name_);
            ret.Push((int)i->collisionMask_);
            if (i->collisionMask_ & BONECOLLISION_SPHERE)
                ret.Push(i->radius_);
            if (i->collisionMask_ & BONECOLLISION_BOX)
            {
                ret.Push(i->boundingBox_.min_);
                ret.Push(i->boundingBox_.max_);
            }
            const Vector4* offsetMatrix = (const Vector4*)i->offsetMatrix_.Data();
            ret.Push(offsetMatrix[0]);
            ret.Push(offsetMatrix[1]);
            ret.Push(offsetMatrix[2]);
        }
    }
    
    return ret;
}

void DecalSet::OnMarkedDirty(Node* node)
{
    Drawable::OnMarkedDirty(node);
    
    if (skinned_)
    {
        // If the scene node or any of the bone nodes move, mark skinning dirty
        skinningDirty_ = true;
    }
}

void DecalSet::OnWorldBoundingBoxUpdate()
{
    if (!skinned_)
    {
        if (boundingBoxDirty_)
            CalculateBoundingBox();
        
        worldBoundingBox_ = boundingBox_.Transformed(node_->GetWorldTransform());
    }
    else
    {
        // When using skinning, update world bounding box based on the bones
        worldBoundingBox_.defined_ = false;
        
        for (Vector<Bone>::ConstIterator i = bones_.Begin(); i != bones_.End(); ++i)
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

void DecalSet::GetFaces(Vector<PODVector<DecalVertex> >& faces, Drawable* target, unsigned batchIndex, const Frustum& frustum,
    const Vector3& decalNormal, float normalCutoff)
{
    Geometry* geometry;
    
    // Special handling for static/animated models, as they may use LOD: use the fixed software LOD level for decals
    StaticModel* staticModel = dynamic_cast<StaticModel*>(target);
    if (staticModel)
        geometry = staticModel->GetSoftwareGeometry(batchIndex);
    else
        geometry = target->GetBatches()[batchIndex].geometry_;
    
    if (!geometry)
        return;
    
    const unsigned char* vertexData;
    unsigned vertexSize;
    const unsigned char* indexData;
    unsigned indexSize;
    unsigned elementMask;
    
    geometry->GetRawData(vertexData, vertexSize, indexData, indexSize, elementMask);
    if (!vertexData || !indexData)
    {
        LOGWARNING("Can not add decal, object does not have CPU-side geometry data");
        return;
    }
    
    unsigned indexStart = geometry->GetIndexStart();
    unsigned indexCount = geometry->GetIndexCount();
    const unsigned char* srcData = (const unsigned char*)vertexData;
    
    // 16-bit indices
    if (indexSize == sizeof(unsigned short))
    {
        const unsigned short* indices = ((const unsigned short*)indexData) + indexStart;
        const unsigned short* indicesEnd = indices + indexCount;
        
        while (indices < indicesEnd)
        {
            GetFace(faces, target, batchIndex, srcData, indices[0], indices[1], indices[2], vertexSize, elementMask, frustum,
                decalNormal, normalCutoff);
            indices += 3;
        }
    }
    else
    // 32-bit indices
    {
        const unsigned* indices = ((const unsigned*)indexData) + indexStart;
        const unsigned* indicesEnd = indices + indexCount;
        
        while (indices < indicesEnd)
        {
            GetFace(faces, target, batchIndex, srcData, indices[0], indices[1], indices[2], vertexSize, elementMask, frustum,
                decalNormal, normalCutoff);
            indices += 3;
        }
    }
}

void DecalSet::GetFace(Vector<PODVector<DecalVertex> >& faces, Drawable* target, unsigned batchIndex, const unsigned char* srcData,
    unsigned i0, unsigned i1, unsigned i2, unsigned vertexSize, unsigned elementMask, const Frustum& frustum,
    const Vector3& decalNormal, float normalCutoff)
{
    bool hasNormals = (elementMask & MASK_NORMAL) != 0;
    bool hasSkinning = skinned_ && (elementMask & MASK_BLENDWEIGHTS) != 0;
    unsigned normalOffset = VertexBuffer::GetElementOffset(elementMask, ELEMENT_NORMAL);
    unsigned skinningOffset = VertexBuffer::GetElementOffset(elementMask, ELEMENT_BLENDWEIGHTS);
    
    const Vector3& v0 = *((const Vector3*)(&srcData[i0 * vertexSize]));
    const Vector3& v1 = *((const Vector3*)(&srcData[i1 * vertexSize]));
    const Vector3& v2 = *((const Vector3*)(&srcData[i2 * vertexSize]));
    const Vector3& n0 = hasNormals ? *((const Vector3*)(&srcData[i0 * vertexSize + normalOffset])) : Vector3::ZERO;
    const Vector3& n1 = hasNormals ? *((const Vector3*)(&srcData[i1 * vertexSize + normalOffset])) : Vector3::ZERO;
    const Vector3& n2 = hasNormals ? *((const Vector3*)(&srcData[i2 * vertexSize + normalOffset])) : Vector3::ZERO;
    const void* s0 = hasSkinning ? (const void*)(&srcData[i0 * vertexSize + skinningOffset]) : (const void*)0;
    const void* s1 = hasSkinning ? (const void*)(&srcData[i1 * vertexSize + skinningOffset]) : (const void*)0;
    const void* s2 = hasSkinning ? (const void*)(&srcData[i2 * vertexSize + skinningOffset]) : (const void*)0;
    
    // Check if face is too much away from the decal normal
    if (hasNormals && decalNormal.DotProduct((n0 + n1 + n2) / 3.0f) < normalCutoff)
        return;
    
    // Check if face is culled completely by any of the planes
    for (unsigned i = PLANE_FAR; i < NUM_FRUSTUM_PLANES; --i)
    {
        const Plane& plane = frustum.planes_[i];
        if (plane.Distance(v0) < 0.0f && plane.Distance(v1) < 0.0f && plane.Distance(v2) < 0.0f)
            return;
    }
    
    faces.Resize(faces.Size() + 1);
    PODVector<DecalVertex>& face = faces.Back();
    if (!hasSkinning)
    {
        face.Push(DecalVertex(v0, n0));
        face.Push(DecalVertex(v1, n1));
        face.Push(DecalVertex(v2, n2));
    }
    else
    {
        const float* bw0 = (const float*)s0;
        const float* bw1 = (const float*)s1;
        const float* bw2 = (const float*)s2;
        const unsigned char* bi0 = ((const unsigned char*)s0) + sizeof(float) * 4;
        const unsigned char* bi1 = ((const unsigned char*)s1) + sizeof(float) * 4;
        const unsigned char* bi2 = ((const unsigned char*)s2) + sizeof(float) * 4;
        unsigned char nbi0[4];
        unsigned char nbi1[4];
        unsigned char nbi2[4];
        
        // Make sure all bones are found and that there is room in the skinning matrices
        if (!GetBones(target, batchIndex, bw0, bi0, nbi0) || !GetBones(target, batchIndex, bw1, bi1, nbi1) ||
            !GetBones(target, batchIndex, bw2, bi2, nbi2))
            return;
        
        face.Push(DecalVertex(v0, n0, bw0, nbi0));
        face.Push(DecalVertex(v1, n1, bw1, nbi1));
        face.Push(DecalVertex(v2, n2, bw2, nbi2));
    }
}

bool DecalSet::GetBones(Drawable* target, unsigned batchIndex, const float* blendWeights, const unsigned char* blendIndices,
    unsigned char* newBlendIndices)
{
    AnimatedModel* animatedModel = dynamic_cast<AnimatedModel*>(target);
    if (!animatedModel)
        return false;
    
    // Check whether target is using global or per-geometry skinning
    const Vector<PODVector<Matrix3x4> >& geometrySkinMatrices = animatedModel->GetGeometrySkinMatrices();
    const Vector<PODVector<unsigned> >& geometryBoneMappings = animatedModel->GetGeometryBoneMappings();
    
    for (unsigned i = 0; i < 4; ++i)
    {
        if (blendWeights[i] > 0.0f)
        {
            Bone* bone = 0;
            if (geometrySkinMatrices.Empty())
                bone = animatedModel->GetSkeleton().GetBone(blendIndices[i]);
            else if (blendIndices[i] < geometryBoneMappings[batchIndex].Size())
                bone = animatedModel->GetSkeleton().GetBone(geometryBoneMappings[batchIndex][blendIndices[i]]);
            
            if (!bone)
            {
                LOGWARNING("Out of range bone index for skinned decal");
                return false;
            }
            
            bool found = false;
            unsigned index;
            
            for (index = 0; index < bones_.Size(); ++index)
            {
                if (bones_[index].node_ == bone->node_)
                {
                    // Check also that the offset matrix matches, in case we for example have a separate attachment AnimatedModel
                    // with a different bind pose
                    const float* offsetA = bones_[index].offsetMatrix_.Data();
                    const float* offsetB = bone->offsetMatrix_.Data();
                    unsigned j;
                    for (j = 0; j < 12; ++j)
                    {
                        if (!Equals(offsetA[j], offsetB[j]))
                            break;
                    }
                    if (j == 12)
                    {
                        found = true;
                        break;
                    }
                }
            }
            
            if (!found)
            {
                if (bones_.Size() >= MAX_SKIN_MATRICES)
                {
                    LOGWARNING("Maximum skinned decal bone count reached");
                    return false;
                }
                else
                {
                    // Copy the bone from the model to the decal
                    index = bones_.Size();
                    bones_.Resize(bones_.Size() + 1);
                    bones_[index] = *bone;
                    skinMatrices_.Resize(skinMatrices_.Size() + 1);
                    skinningDirty_ = true;
                    
                    // Start listening to bone transform changes to update skinning, update amount of shader data in the batch
                    bone->node_->AddListener(this);
                    UpdateBatch();
                }
            }
            
            newBlendIndices[i] = index;
        }
        else
            newBlendIndices[i] = 0;
    }
    
    return true;
}

void DecalSet::CalculateUVs(Decal& decal, const Matrix3x4& view, float size, float aspectRatio, float depth,
    const Vector2& topLeftUV, const Vector2& bottomRightUV)
{
    Matrix4 projection(Matrix4::ZERO);
    
    float h = (1.0f / (size * 0.5f));
    float w = h / aspectRatio;
    float q = 1.0f / depth;
    float r = 0.0f;
    
    projection.m00_ = w;
    projection.m11_ = h;
    projection.m22_ = q;
    projection.m23_ = r;
    projection.m33_ = 1.0f;
    
    Matrix4 viewProj = projection * view;
    
    for (PODVector<DecalVertex>::Iterator i = decal.vertices_.Begin(); i != decal.vertices_.End(); ++i)
    {
        Vector3 projected = viewProj * i->position_;
        i->texCoord_ = Vector2(
            Lerp(topLeftUV.x_, bottomRightUV.x_, projected.x_ * 0.5f + 0.5f),
            Lerp(bottomRightUV.y_, topLeftUV.y_, projected.y_ * 0.5f + 0.5f)
        );
    }
}

void DecalSet::CalculateTangents(Decal& decal)
{
    for (unsigned i = 0; i < decal.vertices_.Size(); i += 3)
    {
        // Tangent generation from
        // http://www.terathon.com/code/tangent.html
        const Vector3& v1 = decal.vertices_[i].position_;
        const Vector3& v2 = decal.vertices_[i + 1].position_;
        const Vector3& v3 = decal.vertices_[i + 2].position_;
        
        const Vector2& w1 = decal.vertices_[i].texCoord_;
        const Vector2& w2 = decal.vertices_[i + 1].texCoord_;
        const Vector2& w3 = decal.vertices_[i + 2].texCoord_;
        
        float x1 = v2.x_ - v1.x_;
        float x2 = v3.x_ - v1.x_;
        float y1 = v2.y_ - v1.y_;
        float y2 = v3.y_ - v1.y_;
        float z1 = v2.z_ - v1.z_;
        float z2 = v3.z_ - v1.z_;
        
        float s1 = w2.x_ - w1.x_;
        float s2 = w3.x_ - w1.x_;
        float t1 = w2.y_ - w1.y_;
        float t2 = w3.y_ - w1.y_;
        
        float r = 1.0f / (s1 * t2 - s2 * t1);
        Vector3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
                (t2 * z1 - t1 * z2) * r);
        Vector3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
                (s1 * z2 - s2 * z1) * r);
        
        for (unsigned j = i; j < i + 3; ++j)
        {
            const Vector3& n = decal.vertices_[j].normal_;
            Vector3 xyz;
            float w;
            
            // Gram-Schmidt orthogonalize
            xyz = (sdir - n * n.DotProduct(sdir)).Normalized();
            
            // Calculate handedness
            w = n.CrossProduct(sdir).DotProduct(tdir) < 0.0f ? -1.0f : 1.0f;
            
            decal.vertices_[j].tangent_ = Vector4(xyz, w);
        }
    }
}

void DecalSet::TransformVertices(Decal& decal, const Matrix3x4& transform, const Vector3& biasVector)
{
    for (PODVector<DecalVertex>::Iterator i = decal.vertices_.Begin(); i != decal.vertices_.End(); ++i)
    {
        i->position_ = transform * (i->position_ + biasVector);
        i->normal_ = (transform * i->normal_).Normalized();
    }
}

List<Decal>::Iterator DecalSet::RemoveDecal(List<Decal>::Iterator i)
{
    numVertices_ -= i->vertices_.Size();
    MarkDecalsDirty();
    return decals_.Erase(i);
}

void DecalSet::MarkDecalsDirty()
{
    if (!boundingBoxDirty_)
    {
        boundingBoxDirty_ = true;
        OnMarkedDirty(node_);
    }
    bufferDirty_ = true;
}

void DecalSet::CalculateBoundingBox()
{
    boundingBox_.Clear();
    for (List<Decal>::ConstIterator i = decals_.Begin(); i != decals_.End(); ++i)
        boundingBox_.Merge(i->boundingBox_);
    
    boundingBoxDirty_ = false;
}

void DecalSet::UpdateBufferSize()
{
    if (!skinned_)
        vertexBuffer_->SetSize(maxVertices_, STATIC_ELEMENT_MASK);
    else
        vertexBuffer_->SetSize(maxVertices_, SKINNED_ELEMENT_MASK);
    
    geometry_->SetVertexBuffer(0, vertexBuffer_);
    bufferDirty_ = true;
    bufferSizeDirty_ = false;
}

void DecalSet::UpdateVertexBuffer()
{
    geometry_->SetDrawRange(TRIANGLE_LIST, 0, 0, 0, numVertices_);
    
    float* dest = (float*)vertexBuffer_->Lock(0, numVertices_);
    if (dest)
    {
        for (List<Decal>::ConstIterator i = decals_.Begin(); i != decals_.End(); ++i)
        {
            for (unsigned j = 0; j < i->vertices_.Size(); ++j)
            {
                const DecalVertex& vertex = i->vertices_[j];
                *dest++ = vertex.position_.x_;
                *dest++ = vertex.position_.y_;
                *dest++ = vertex.position_.z_;
                *dest++ = vertex.normal_.x_;
                *dest++ = vertex.normal_.y_;
                *dest++ = vertex.normal_.z_;
                *dest++ = vertex.texCoord_.x_;
                *dest++ = vertex.texCoord_.y_;
                *dest++ = vertex.tangent_.x_;
                *dest++ = vertex.tangent_.y_;
                *dest++ = vertex.tangent_.z_;
                *dest++ = vertex.tangent_.w_;
                if (skinned_)
                {
                    *dest++ = vertex.blendWeights_[0];
                    *dest++ = vertex.blendWeights_[1];
                    *dest++ = vertex.blendWeights_[2];
                    *dest++ = vertex.blendWeights_[3];
                    *dest++ = *((float*)vertex.blendIndices_);
                }
            }
        }
        
        vertexBuffer_->Unlock();
    }
    
    vertexBuffer_->ClearDataLost();
    bufferDirty_ = false;
}

void DecalSet::UpdateSkinning()
{
    // Use model's world transform in case a bone is missing
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    
    for (unsigned i = 0; i < bones_.Size(); ++i)
    {
        const Bone& bone = bones_[i];
        if (bone.node_)
            skinMatrices_[i] = bone.node_->GetWorldTransform() * bone.offsetMatrix_;
        else
            skinMatrices_[i] = worldTransform;
    }
    
    skinningDirty_ = false;
}

void DecalSet::UpdateBatch()
{
    if (skinMatrices_.Size())
    {
        batches_[0].geometryType_ = GEOM_SKINNED;
        batches_[0].shaderData_ = skinMatrices_[0].Data();
        batches_[0].shaderDataSize_ = skinMatrices_.Size() * 12;
    }
    else
    {
        batches_[0].geometryType_ = GEOM_STATIC;
        batches_[0].shaderData_ = 0;
        batches_[0].shaderDataSize_ = 0;
    }
}

void DecalSet::AssignBoneNodes()
{
    assignBonesPending_ = false;
    
    if (!node_)
        return;
    
    // Find the bone nodes from the node hierarchy and add listeners
    for (Vector<Bone>::Iterator i = bones_.Begin(); i != bones_.End(); ++i)
    {
        Node* boneNode = node_->GetChild(i->name_, true);
        if (boneNode)
            boneNode->AddListener(this);
        i->node_ = boneNode;
    }
}

void DecalSet::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    
    for (List<Decal>::Iterator i = decals_.Begin(); i != decals_.End();)
    {
        i->timer_ += timeStep;
        
        // Remove the decal if time to live expired
        if (i->timeToLive_ > 0.0f && i->timer_ > i->timeToLive_)
            i = RemoveDecal(i);
        else
            ++i;
    }
}
