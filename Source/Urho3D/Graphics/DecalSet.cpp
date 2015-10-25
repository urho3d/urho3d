//
// Copyright (c) 2008-2015 the Urho3D project.
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
#include "../Graphics/Batch.h"
#include "../Graphics/Camera.h"
#include "../Graphics/DecalSet.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Material.h"
#include "../Graphics/Tangent.h"
#include "../Graphics/VertexBuffer.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"

#include "../DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:6293)
#endif

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;

static const unsigned MIN_VERTICES = 4;
static const unsigned MIN_INDICES = 6;
static const unsigned MAX_VERTICES = 65536;
static const unsigned DEFAULT_MAX_VERTICES = 512;
static const unsigned DEFAULT_MAX_INDICES = 1024;
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
        if (*((unsigned*)v0.blendIndices_) != *((unsigned*)v1.blendIndices_))
        {
            // Blend weights and indices: if indices are different, choose the vertex nearer to the split plane
            const DecalVertex& src = Abs(d0) < Abs(d1) ? v0 : v1;
            for (unsigned i = 0; i < 4; ++i)
            {
                ret.blendWeights_[i] = src.blendWeights_[i];
                ret.blendIndices_[i] = src.blendIndices_[i];
            }
        }
        else
        {
            // If indices are same, can interpolate the weights
            for (unsigned i = 0; i < 4; ++i)
            {
                ret.blendWeights_[i] = v0.blendWeights_[i] + t * (v1.blendWeights_[i] - v0.blendWeights_[i]);
                ret.blendIndices_[i] = v0.blendIndices_[i];
            }
        }
    }

    return ret;
}

static void ClipPolygon(PODVector<DecalVertex>& dest, const PODVector<DecalVertex>& src, const Plane& plane, bool skinned)
{
    unsigned last = 0;
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

void Decal::AddVertex(const DecalVertex& vertex)
{
    for (unsigned i = 0; i < vertices_.Size(); ++i)
    {
        if (vertex.position_.Equals(vertices_[i].position_) && vertex.normal_.Equals(vertices_[i].normal_))
        {
            indices_.Push((unsigned short)i);
            return;
        }
    }

    unsigned short newIndex = (unsigned short)vertices_.Size();
    vertices_.Push(vertex);
    indices_.Push(newIndex);
}

void Decal::CalculateBoundingBox()
{
    boundingBox_.Clear();
    for (unsigned i = 0; i < vertices_.Size(); ++i)
        boundingBox_.Merge(vertices_[i].position_);
}

DecalSet::DecalSet(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY),
    geometry_(new Geometry(context)),
    vertexBuffer_(new VertexBuffer(context_)),
    indexBuffer_(new IndexBuffer(context_)),
    numVertices_(0),
    numIndices_(0),
    maxVertices_(DEFAULT_MAX_VERTICES),
    maxIndices_(DEFAULT_MAX_INDICES),
    skinned_(false),
    bufferSizeDirty_(true),
    bufferDirty_(true),
    boundingBoxDirty_(true),
    skinningDirty_(false),
    assignBonesPending_(false),
    subscribed_(false)
{
    geometry_->SetIndexBuffer(indexBuffer_);

    batches_.Resize(1);
    batches_[0].geometry_ = geometry_;
    batches_[0].geometryType_ = GEOM_STATIC_NOINSTANCING;
}

DecalSet::~DecalSet()
{
}

void DecalSet::RegisterObject(Context* context)
{
    context->RegisterFactory<DecalSet>(GEOMETRY_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()),
        AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Vertices", GetMaxVertices, SetMaxVertices, unsigned, DEFAULT_MAX_VERTICES, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Max Indices", GetMaxIndices, SetMaxIndices, unsigned, DEFAULT_MAX_INDICES, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Drawable);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Decals", GetDecalsAttr, SetDecalsAttr, PODVector<unsigned char>, Variant::emptyBuffer,
        AM_FILE | AM_NOEDIT);
}

void DecalSet::ApplyAttributes()
{
    if (assignBonesPending_)
        AssignBoneNodes();
}

void DecalSet::OnSetEnabled()
{
    Drawable::OnSetEnabled();

    UpdateEventSubscription(true);
}

void DecalSet::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    // Do not return raycast hits
}

void DecalSet::UpdateBatches(const FrameInfo& frame)
{
    const BoundingBox& worldBoundingBox = GetWorldBoundingBox();
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    distance_ = frame.camera_->GetDistance(worldBoundingBox.Center());

    float scale = worldBoundingBox.Size().DotProduct(DOT_SCALE);
    lodDistance_ = frame.camera_->GetLodDistance(distance_, scale, lodBias_);

    batches_[0].distance_ = distance_;
    if (!skinned_)
        batches_[0].worldTransform_ = &worldTransform;
}

void DecalSet::UpdateGeometry(const FrameInfo& frame)
{
    if (bufferSizeDirty_)
        UpdateBufferSize();

    if (bufferDirty_ || vertexBuffer_->IsDataLost() || indexBuffer_->IsDataLost())
        UpdateBuffers();

    if (skinningDirty_)
        UpdateSkinning();
}

UpdateGeometryType DecalSet::GetUpdateGeometryType()
{
    if (bufferDirty_ || bufferSizeDirty_ || vertexBuffer_->IsDataLost() || indexBuffer_->IsDataLost())
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
    // Never expand to 32 bit indices
    num = (unsigned)Clamp((int)num, MIN_VERTICES, MAX_VERTICES);

    if (num != maxVertices_)
    {
        bufferSizeDirty_ = true;
        maxVertices_ = num;

        while (decals_.Size() && numVertices_ > maxVertices_)
            RemoveDecals(1);

        MarkNetworkUpdate();
    }
}

void DecalSet::SetMaxIndices(unsigned num)
{
    if (num < MIN_INDICES)
        num = MIN_INDICES;

    if (num != maxIndices_)
    {
        bufferSizeDirty_ = true;
        maxIndices_ = num;

        while (decals_.Size() && numIndices_ > maxIndices_)
            RemoveDecals(1);

        MarkNetworkUpdate();
    }
}

bool DecalSet::AddDecal(Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size,
    float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive, float normalCutoff,
    unsigned subGeometry)
{
    URHO3D_PROFILE(AddDecal);

    // Do not add decals in headless mode
    if (!node_ || !GetSubsystem<Graphics>())
        return false;

    if (!target || !target->GetNode())
    {
        URHO3D_LOGERROR("Null target drawable for decal");
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

    // Center the decal frustum on the world position
    Vector3 adjustedWorldPosition = worldPosition - 0.5f * depth * (worldRotation * Vector3::FORWARD);
    /// \todo target transform is not right if adding a decal to StaticModelGroup
    Matrix3x4 targetTransform = target->GetNode()->GetWorldTransform().Inverse();

    // For an animated model, adjust the decal position back to the bind pose
    // To do this, need to find the bone the decal is colliding with
    if (animatedModel)
    {
        Skeleton& skeleton = animatedModel->GetSkeleton();
        unsigned numBones = skeleton.GetNumBones();
        Bone* bestBone = 0;
        float bestSize = 0.0f;

        for (unsigned i = 0; i < numBones; ++i)
        {
            Bone* bone = skeleton.GetBone(i);
            if (!bone->node_ || !bone->collisionMask_)
                continue;

            // Represent the decal as a sphere, try to find the biggest colliding bone
            Sphere decalSphere
                (bone->node_->GetWorldTransform().Inverse() * worldPosition, 0.5f * size / bone->node_->GetWorldScale().Length());

            if (bone->collisionMask_ & BONECOLLISION_BOX)
            {
                float size = bone->boundingBox_.HalfSize().Length();
                if (bone->boundingBox_.IsInside(decalSphere) && size > bestSize)
                {
                    bestBone = bone;
                    bestSize = size;
                }
            }
            else if (bone->collisionMask_ & BONECOLLISION_SPHERE)
            {
                Sphere boneSphere(Vector3::ZERO, bone->radius_);
                float size = bone->radius_;
                if (boneSphere.IsInside(decalSphere) && size > bestSize)
                {
                    bestBone = bone;
                    bestSize = size;
                }
            }
        }

        if (bestBone)
            targetTransform = (bestBone->node_->GetWorldTransform() * bestBone->offsetMatrix_).Inverse();
    }

    // Build the decal frustum
    Frustum decalFrustum;
    Matrix3x4 frustumTransform = targetTransform * Matrix3x4(adjustedWorldPosition, worldRotation, 1.0f);
    decalFrustum.DefineOrtho(size, aspectRatio, 1.0, 0.0f, depth, frustumTransform);

    Vector3 decalNormal = (targetTransform * Vector4(worldRotation * Vector3::BACK, 0.0f)).Normalized();

    decals_.Resize(decals_.Size() + 1);
    Decal& newDecal = decals_.Back();
    newDecal.timeToLive_ = timeToLive;

    Vector<PODVector<DecalVertex> > faces;
    PODVector<DecalVertex> tempFace;

    unsigned numBatches = target->GetBatches().Size();

    // Use either a specified subgeometry in the target, or all
    if (subGeometry < numBatches)
        GetFaces(faces, target, subGeometry, decalFrustum, decalNormal, normalCutoff);
    else
    {
        for (unsigned i = 0; i < numBatches; ++i)
            GetFaces(faces, target, i, decalFrustum, decalNormal, normalCutoff);
    }

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
            newDecal.AddVertex(face[0]);
            newDecal.AddVertex(face[j - 1]);
            newDecal.AddVertex(face[j]);
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
        URHO3D_LOGWARNING("Can not add decal, vertex count " + String(newDecal.vertices_.Size()) + " exceeds maximum " +
                   String(maxVertices_));
        decals_.Pop();
        return false;
    }
    if (newDecal.indices_.Size() > maxIndices_)
    {
        URHO3D_LOGWARNING("Can not add decal, index count " + String(newDecal.indices_.Size()) + " exceeds maximum " +
                   String(maxIndices_));
        decals_.Pop();
        return false;
    }

    // Calculate UVs
    Matrix4 projection(Matrix4::ZERO);
    projection.m11_ = (1.0f / (size * 0.5f));
    projection.m00_ = projection.m11_ / aspectRatio;
    projection.m22_ = 1.0f / depth;
    projection.m33_ = 1.0f;

    CalculateUVs(newDecal, frustumTransform.Inverse(), projection, topLeftUV, bottomRightUV);

    // Transform vertices to this node's local space and generate tangents
    Matrix3x4 decalTransform = node_->GetWorldTransform().Inverse() * target->GetNode()->GetWorldTransform();
    TransformVertices(newDecal, skinned_ ? Matrix3x4::IDENTITY : decalTransform);
    GenerateTangents(&newDecal.vertices_[0], sizeof(DecalVertex), &newDecal.indices_[0], sizeof(unsigned short), 0,
        newDecal.indices_.Size(), offsetof(DecalVertex, normal_), offsetof(DecalVertex, texCoord_), offsetof(DecalVertex,
        tangent_));

    newDecal.CalculateBoundingBox();
    numVertices_ += newDecal.vertices_.Size();
    numIndices_ += newDecal.indices_.Size();

    // Remove oldest decals if total vertices exceeded
    while (decals_.Size() && (numVertices_ > maxVertices_ || numIndices_ > maxIndices_))
        RemoveDecals(1);

    URHO3D_LOGDEBUG("Added decal with " + String(newDecal.vertices_.Size()) + " vertices");

    // If new decal is time limited, subscribe to scene post-update
    if (newDecal.timeToLive_ > 0.0f && !subscribed_)
        UpdateEventSubscription(false);

    MarkDecalsDirty();
    return true;
}

void DecalSet::RemoveDecals(unsigned num)
{
    while (num-- && decals_.Size())
        RemoveDecal(decals_.Begin());
}

void DecalSet::RemoveAllDecals()
{
    if (!decals_.Empty())
    {
        decals_.Clear();
        numVertices_ = 0;
        numIndices_ = 0;
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

void DecalSet::SetMaterialAttr(const ResourceRef& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetMaterial(cache->GetResource<Material>(value.name_));
}

void DecalSet::SetDecalsAttr(const PODVector<unsigned char>& value)
{
    RemoveAllDecals();

    if (value.Empty())
        return;

    MemoryBuffer buffer(value);

    skinned_ = buffer.ReadBool();
    unsigned numDecals = buffer.ReadVLE();

    while (numDecals--)
    {
        decals_.Resize(decals_.Size() + 1);
        Decal& newDecal = decals_.Back();

        newDecal.timer_ = buffer.ReadFloat();
        newDecal.timeToLive_ = buffer.ReadFloat();
        newDecal.vertices_.Resize(buffer.ReadVLE());
        newDecal.indices_.Resize(buffer.ReadVLE());

        for (PODVector<DecalVertex>::Iterator i = newDecal.vertices_.Begin(); i != newDecal.vertices_.End(); ++i)
        {
            i->position_ = buffer.ReadVector3();
            i->normal_ = buffer.ReadVector3();
            i->texCoord_ = buffer.ReadVector2();
            i->tangent_ = buffer.ReadVector4();
            if (skinned_)
            {
                for (unsigned j = 0; j < 4; ++j)
                    i->blendWeights_[j] = buffer.ReadFloat();
                for (unsigned j = 0; j < 4; ++j)
                    i->blendIndices_[j] = buffer.ReadUByte();
            }
        }

        for (PODVector<unsigned short>::Iterator i = newDecal.indices_.Begin(); i != newDecal.indices_.End(); ++i)
            *i = buffer.ReadUShort();

        newDecal.CalculateBoundingBox();
        numVertices_ += newDecal.vertices_.Size();
        numIndices_ += newDecal.indices_.Size();
    }

    if (skinned_)
    {
        unsigned numBones = buffer.ReadVLE();
        skinMatrices_.Resize(numBones);
        bones_.Resize(numBones);

        for (unsigned i = 0; i < numBones; ++i)
        {
            Bone& newBone = bones_[i];

            newBone.name_ = buffer.ReadString();
            newBone.collisionMask_ = buffer.ReadUByte();
            if (newBone.collisionMask_ & BONECOLLISION_SPHERE)
                newBone.radius_ = buffer.ReadFloat();
            if (newBone.collisionMask_ & BONECOLLISION_BOX)
                newBone.boundingBox_ = buffer.ReadBoundingBox();
            buffer.Read(&newBone.offsetMatrix_.m00_, sizeof(Matrix3x4));
        }

        assignBonesPending_ = true;
        skinningDirty_ = true;
    }

    UpdateEventSubscription(true);
    UpdateBatch();
    MarkDecalsDirty();
    bufferSizeDirty_ = true;
}

ResourceRef DecalSet::GetMaterialAttr() const
{
    return GetResourceRef(batches_[0].material_, Material::GetTypeStatic());
}

PODVector<unsigned char> DecalSet::GetDecalsAttr() const
{
    VectorBuffer ret;

    ret.WriteBool(skinned_);
    ret.WriteVLE(decals_.Size());

    for (List<Decal>::ConstIterator i = decals_.Begin(); i != decals_.End(); ++i)
    {
        ret.WriteFloat(i->timer_);
        ret.WriteFloat(i->timeToLive_);
        ret.WriteVLE(i->vertices_.Size());
        ret.WriteVLE(i->indices_.Size());

        for (PODVector<DecalVertex>::ConstIterator j = i->vertices_.Begin(); j != i->vertices_.End(); ++j)
        {
            ret.WriteVector3(j->position_);
            ret.WriteVector3(j->normal_);
            ret.WriteVector2(j->texCoord_);
            ret.WriteVector4(j->tangent_);
            if (skinned_)
            {
                for (unsigned k = 0; k < 4; ++k)
                    ret.WriteFloat(j->blendWeights_[k]);
                for (unsigned k = 0; k < 4; ++k)
                    ret.WriteUByte(j->blendIndices_[k]);
            }
        }

        for (PODVector<unsigned short>::ConstIterator j = i->indices_.Begin(); j != i->indices_.End(); ++j)
            ret.WriteUShort(*j);
    }

    if (skinned_)
    {
        ret.WriteVLE(bones_.Size());

        for (Vector<Bone>::ConstIterator i = bones_.Begin(); i != bones_.End(); ++i)
        {
            ret.WriteString(i->name_);
            ret.WriteUByte(i->collisionMask_);
            if (i->collisionMask_ & BONECOLLISION_SPHERE)
                ret.WriteFloat(i->radius_);
            if (i->collisionMask_ & BONECOLLISION_BOX)
                ret.WriteBoundingBox(i->boundingBox_);
            ret.Write(i->offsetMatrix_.Data(), sizeof(Matrix3x4));
        }
    }

    return ret.GetBuffer();
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
        BoundingBox worldBox;

        for (Vector<Bone>::ConstIterator i = bones_.Begin(); i != bones_.End(); ++i)
        {
            Node* boneNode = i->node_;
            if (!boneNode)
                continue;

            // Use hitbox if available. If not, use only half of the sphere radius
            /// \todo The sphere radius should be multiplied with bone scale
            if (i->collisionMask_ & BONECOLLISION_BOX)
                worldBox.Merge(i->boundingBox_.Transformed(boneNode->GetWorldTransform()));
            else if (i->collisionMask_ & BONECOLLISION_SPHERE)
                worldBox.Merge(Sphere(boneNode->GetWorldPosition(), i->radius_ * 0.5f));
        }

        worldBoundingBox_ = worldBox;
    }
}

void DecalSet::GetFaces(Vector<PODVector<DecalVertex> >& faces, Drawable* target, unsigned batchIndex, const Frustum& frustum,
    const Vector3& decalNormal, float normalCutoff)
{
    // Try to use the most accurate LOD level if possible
    Geometry* geometry = target->GetLodGeometry(batchIndex, 0);
    if (!geometry || geometry->GetPrimitiveType() != TRIANGLE_LIST)
        return;

    const unsigned char* positionData = 0;
    const unsigned char* normalData = 0;
    const unsigned char* skinningData = 0;
    const unsigned char* indexData = 0;
    unsigned positionStride = 0;
    unsigned normalStride = 0;
    unsigned skinningStride = 0;
    unsigned indexStride = 0;

    IndexBuffer* ib = geometry->GetIndexBuffer();
    if (ib)
    {
        indexData = ib->GetShadowData();
        indexStride = ib->GetIndexSize();
    }

    // For morphed models positions, normals and skinning may be in different buffers
    for (unsigned i = 0; i < geometry->GetNumVertexBuffers(); ++i)
    {
        VertexBuffer* vb = geometry->GetVertexBuffer(i);
        if (!vb)
            continue;

        unsigned elementMask = geometry->GetVertexElementMask(i);
        unsigned char* data = vb->GetShadowData();
        if (!data)
            continue;

        if (elementMask & MASK_POSITION)
        {
            positionData = data;
            positionStride = vb->GetVertexSize();
        }
        if (elementMask & MASK_NORMAL)
        {
            normalData = data + vb->GetElementOffset(ELEMENT_NORMAL);
            normalStride = vb->GetVertexSize();
        }
        if (elementMask & MASK_BLENDWEIGHTS)
        {
            skinningData = data + vb->GetElementOffset(ELEMENT_BLENDWEIGHTS);
            skinningStride = vb->GetVertexSize();
        }
    }

    // Positions and indices are needed
    if (!positionData)
    {
        // As a fallback, try to get the geometry's raw vertex/index data
        unsigned elementMask;
        geometry->GetRawData(positionData, positionStride, indexData, indexStride, elementMask);
        if (!positionData)
        {
            URHO3D_LOGWARNING("Can not add decal, target drawable has no CPU-side geometry data");
            return;
        }
    }

    if (indexData)
    {
        unsigned indexStart = geometry->GetIndexStart();
        unsigned indexCount = geometry->GetIndexCount();

        // 16-bit indices
        if (indexStride == sizeof(unsigned short))
        {
            const unsigned short* indices = ((const unsigned short*)indexData) + indexStart;
            const unsigned short* indicesEnd = indices + indexCount;

            while (indices < indicesEnd)
            {
                GetFace(faces, target, batchIndex, indices[0], indices[1], indices[2], positionData, normalData, skinningData,
                    positionStride, normalStride, skinningStride, frustum, decalNormal, normalCutoff);
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
                GetFace(faces, target, batchIndex, indices[0], indices[1], indices[2], positionData, normalData, skinningData,
                    positionStride, normalStride, skinningStride, frustum, decalNormal, normalCutoff);
                indices += 3;
            }
        }
    }
    else
    {
        // Non-indexed geometry
        unsigned indices = geometry->GetVertexStart();
        unsigned indicesEnd = indices + geometry->GetVertexCount();

        while (indices + 2 < indicesEnd)
        {
            GetFace(faces, target, batchIndex, indices, indices + 1, indices + 2, positionData, normalData, skinningData,
                positionStride, normalStride, skinningStride, frustum, decalNormal, normalCutoff);
            indices += 3;
        }
    }
}

void DecalSet::GetFace(Vector<PODVector<DecalVertex> >& faces, Drawable* target, unsigned batchIndex, unsigned i0, unsigned i1,
    unsigned i2, const unsigned char* positionData, const unsigned char* normalData, const unsigned char* skinningData,
    unsigned positionStride, unsigned normalStride, unsigned skinningStride, const Frustum& frustum, const Vector3& decalNormal,
    float normalCutoff)
{
    bool hasNormals = normalData != 0;
    bool hasSkinning = skinned_ && skinningData != 0;

    const Vector3& v0 = *((const Vector3*)(&positionData[i0 * positionStride]));
    const Vector3& v1 = *((const Vector3*)(&positionData[i1 * positionStride]));
    const Vector3& v2 = *((const Vector3*)(&positionData[i2 * positionStride]));

    // Calculate unsmoothed face normals if no normal data
    Vector3 faceNormal = Vector3::ZERO;
    if (!hasNormals)
    {
        Vector3 dist1 = v1 - v0;
        Vector3 dist2 = v2 - v0;
        faceNormal = (dist1.CrossProduct(dist2)).Normalized();
    }

    const Vector3& n0 = hasNormals ? *((const Vector3*)(&normalData[i0 * normalStride])) : faceNormal;
    const Vector3& n1 = hasNormals ? *((const Vector3*)(&normalData[i1 * normalStride])) : faceNormal;
    const Vector3& n2 = hasNormals ? *((const Vector3*)(&normalData[i2 * normalStride])) : faceNormal;

    const unsigned char* s0 = hasSkinning ? &skinningData[i0 * skinningStride] : (const unsigned char*)0;
    const unsigned char* s1 = hasSkinning ? &skinningData[i1 * skinningStride] : (const unsigned char*)0;
    const unsigned char* s2 = hasSkinning ? &skinningData[i2 * skinningStride] : (const unsigned char*)0;

    // Check if face is too much away from the decal normal
    if (decalNormal.DotProduct((n0 + n1 + n2) / 3.0f) < normalCutoff)
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
        face.Reserve(3);
        face.Push(DecalVertex(v0, n0));
        face.Push(DecalVertex(v1, n1));
        face.Push(DecalVertex(v2, n2));
    }
    else
    {
        const float* bw0 = (const float*)s0;
        const float* bw1 = (const float*)s1;
        const float* bw2 = (const float*)s2;
        const unsigned char* bi0 = s0 + sizeof(float) * 4;
        const unsigned char* bi1 = s1 + sizeof(float) * 4;
        const unsigned char* bi2 = s2 + sizeof(float) * 4;
        unsigned char nbi0[4];
        unsigned char nbi1[4];
        unsigned char nbi2[4];

        // Make sure all bones are found and that there is room in the skinning matrices
        if (!GetBones(target, batchIndex, bw0, bi0, nbi0) || !GetBones(target, batchIndex, bw1, bi1, nbi1) ||
            !GetBones(target, batchIndex, bw2, bi2, nbi2))
            return;

        face.Reserve(3);
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
                URHO3D_LOGWARNING("Out of range bone index for skinned decal");
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
                    if (bones_[index].offsetMatrix_.Equals(bone->offsetMatrix_))
                    {
                        found = true;
                        break;
                    }
                }
            }

            if (!found)
            {
                if (bones_.Size() >= Graphics::GetMaxBones())
                {
                    URHO3D_LOGWARNING("Maximum skinned decal bone count reached");
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

                    // Start listening to bone transform changes to update skinning
                    bone->node_->AddListener(this);
                }
            }

            newBlendIndices[i] = (unsigned char)index;
        }
        else
            newBlendIndices[i] = 0;
    }

    // Update amount of shader data in the decal batch
    UpdateBatch();
    return true;
}

void DecalSet::CalculateUVs(Decal& decal, const Matrix3x4& view, const Matrix4& projection, const Vector2& topLeftUV,
    const Vector2& bottomRightUV)
{
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

void DecalSet::TransformVertices(Decal& decal, const Matrix3x4& transform)
{
    for (PODVector<DecalVertex>::Iterator i = decal.vertices_.Begin(); i != decal.vertices_.End(); ++i)
    {
        i->position_ = transform * i->position_;
        i->normal_ = (transform * i->normal_).Normalized();
    }
}

List<Decal>::Iterator DecalSet::RemoveDecal(List<Decal>::Iterator i)
{
    numVertices_ -= i->vertices_.Size();
    numIndices_ -= i->indices_.Size();
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
    vertexBuffer_->SetSize(maxVertices_, skinned_ ? SKINNED_ELEMENT_MASK : STATIC_ELEMENT_MASK);
    indexBuffer_->SetSize(maxIndices_, false);
    geometry_->SetVertexBuffer(0, vertexBuffer_);

    bufferDirty_ = true;
    bufferSizeDirty_ = false;
}

void DecalSet::UpdateBuffers()
{
    geometry_->SetDrawRange(TRIANGLE_LIST, 0, numIndices_, 0, numVertices_);

    float* vertices = (float*)vertexBuffer_->Lock(0, numVertices_);
    unsigned short* indices = (unsigned short*)indexBuffer_->Lock(0, numIndices_);

    if (vertices && indices)
    {
        unsigned short indexStart = 0;

        for (List<Decal>::ConstIterator i = decals_.Begin(); i != decals_.End(); ++i)
        {
            for (unsigned j = 0; j < i->vertices_.Size(); ++j)
            {
                const DecalVertex& vertex = i->vertices_[j];
                *vertices++ = vertex.position_.x_;
                *vertices++ = vertex.position_.y_;
                *vertices++ = vertex.position_.z_;
                *vertices++ = vertex.normal_.x_;
                *vertices++ = vertex.normal_.y_;
                *vertices++ = vertex.normal_.z_;
                *vertices++ = vertex.texCoord_.x_;
                *vertices++ = vertex.texCoord_.y_;
                *vertices++ = vertex.tangent_.x_;
                *vertices++ = vertex.tangent_.y_;
                *vertices++ = vertex.tangent_.z_;
                *vertices++ = vertex.tangent_.w_;
                if (skinned_)
                {
                    *vertices++ = vertex.blendWeights_[0];
                    *vertices++ = vertex.blendWeights_[1];
                    *vertices++ = vertex.blendWeights_[2];
                    *vertices++ = vertex.blendWeights_[3];
                    *vertices++ = *((float*)vertex.blendIndices_);
                }
            }

            for (unsigned j = 0; j < i->indices_.Size(); ++j)
                *indices++ = i->indices_[j] + indexStart;

            indexStart += i->vertices_.Size();
        }
    }

    vertexBuffer_->Unlock();
    vertexBuffer_->ClearDataLost();
    indexBuffer_->Unlock();
    indexBuffer_->ClearDataLost();
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
        batches_[0].worldTransform_ = &skinMatrices_[0];
        batches_[0].numWorldTransforms_ = skinMatrices_.Size();
    }
    else
    {
        batches_[0].geometryType_ = GEOM_STATIC;
        batches_[0].worldTransform_ = &node_->GetWorldTransform();
        batches_[0].numWorldTransforms_ = 1;
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

void DecalSet::UpdateEventSubscription(bool checkAllDecals)
{
    Scene* scene = GetScene();
    if (!scene)
        return;

    bool enabled = IsEnabledEffective();

    if (enabled && checkAllDecals)
    {
        bool hasTimeLimitedDecals = false;

        for (List<Decal>::ConstIterator i = decals_.Begin(); i != decals_.End(); ++i)
        {
            if (i->timeToLive_ > 0.0f)
            {
                hasTimeLimitedDecals = true;
                break;
            }
        }

        // If no time limited decals, no need to subscribe to scene update
        enabled = hasTimeLimitedDecals;
    }

    if (enabled && !subscribed_)
    {
        SubscribeToEvent(scene, E_SCENEPOSTUPDATE, URHO3D_HANDLER(DecalSet, HandleScenePostUpdate));
        subscribed_ = true;
    }
    else if (!enabled && subscribed_)
    {
        UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
        subscribed_ = false;
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

}
