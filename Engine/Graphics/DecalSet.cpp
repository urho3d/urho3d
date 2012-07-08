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
#include "Batch.h"
#include "Camera.h"
#include "Context.h"
#include "DecalSet.h"
#include "Geometry.h"
#include "GeometryUtils.h"
#include "Graphics.h"
#include "Log.h"
#include "Node.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "StaticModel.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

static const Vector3 DOT_SCALE(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);
static const unsigned DEFAULT_MAX_VERTICES = 1024;

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
    bufferSizeDirty_(true),
    bufferDirty_(true),
    boundingBoxDirty_(true)
{
    drawableFlags_ = DRAWABLE_GEOMETRY;
    
    geometry_->SetVertexBuffer(0, vertexBuffer_, MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1 | MASK_TANGENT);
    
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
}

UpdateGeometryType DecalSet::GetUpdateGeometryType()
{
    if (bufferDirty_ || bufferSizeDirty_ || vertexBuffer_->IsDataLost())
        return UPDATE_MAIN_THREAD;
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

bool DecalSet::AddDecal(Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive, float normalCutoff, float depthBias)
{
    PROFILE(AddDecal);
    
    if (!node_)
        return false;
    
    if (!target || !target->GetNode())
    {
        LOGERROR("Null target drawable for decal");
        return false;
    }
    
    Matrix3x4 targetTransform = target->GetNode()->GetWorldTransform().Inverse();
    
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
    
    // Special handling for static models, as they may use LOD: use the fixed software LOD level for decals
    StaticModel* staticModel = dynamic_cast<StaticModel*>(target);
    if (staticModel)
    {
        for (unsigned i = 0; i < staticModel->GetNumGeometries(); ++i)
            GetFaces(faces, staticModel->GetSoftwareGeometry(i), decalFrustum, decalNormal, normalCutoff);
    }
    else
    {
        // Else use the Drawable API to find out the source geometries
        const Vector<SourceBatch>& batches = target->GetBatches();
        for (unsigned i = 0; i < batches.Size(); ++i)
            GetFaces(faces, batches[i].geometry_, decalFrustum, decalNormal, normalCutoff);
    }
    
    // Clip the acquired faces against all frustum planes
    for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
    {
        for (unsigned j = 0; j < faces.Size(); ++j)
        {
            PODVector<DecalVertex>& face = faces[j];
            if (face.Empty())
                continue;
            
            tempFace.Resize(face.Size() + 2);
            unsigned outVertices = ClipPolygon((float*)&face[0], (float*)&tempFace[0], face.Size(), sizeof(DecalVertex), decalFrustum.planes_[i]);
            tempFace.Resize(outVertices);
            
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
    TransformVertices(newDecal, decalTransform, biasVector);
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
    Scene* scene = GetScene();
    
    RemoveAllDecals();
    
    unsigned index = 0;
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
        }
        
        newDecal.CalculateBoundingBox();
        numVertices_ += newDecal.vertices_.Size();
        
        // Subscribe to scene post-update if defined a time-limited decal
        if (newDecal.timeToLive_ > 0.0f && scene && !HasSubscribedToEvent(scene, E_SCENEPOSTUPDATE))
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(DecalSet, HandleScenePostUpdate));
    }
    
    MarkDecalsDirty();
}

ResourceRef DecalSet::GetMaterialAttr() const
{
    return GetResourceRef(batches_[0].material_, Material::GetTypeStatic());
}

VariantVector DecalSet::GetDecalsAttr() const
{
    VariantVector ret;
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
        }
    }
    
    return ret;
}

void DecalSet::OnWorldBoundingBoxUpdate()
{
    if (boundingBoxDirty_)
        CalculateBoundingBox();
    
    worldBoundingBox_ = boundingBox_.Transformed(node_->GetWorldTransform());
}

void DecalSet::GetFaces(Vector<PODVector<DecalVertex> >& faces, Geometry* geometry, const Frustum& frustum, const Vector3& decalNormal, float normalCutoff)
{
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
    bool hasNormals = (elementMask & MASK_NORMAL) != 0;
    
    const unsigned char* srcData = (const unsigned char*)vertexData;
    
    // 16-bit indices
    if (indexSize == sizeof(unsigned short))
    {
        const unsigned short* indices = ((const unsigned short*)indexData) + indexStart;
        const unsigned short* indicesEnd = indices + indexCount;
        
        while (indices < indicesEnd)
        {
            const Vector3& v0 = *((const Vector3*)(&srcData[indices[0] * vertexSize]));
            const Vector3& v1 = *((const Vector3*)(&srcData[indices[1] * vertexSize]));
            const Vector3& v2 = *((const Vector3*)(&srcData[indices[2] * vertexSize]));
            const Vector3& n0 = hasNormals ? *((const Vector3*)(&srcData[indices[0] * vertexSize + 3 * sizeof(float)])) :
                Vector3::ZERO;
            const Vector3& n1 = hasNormals ? *((const Vector3*)(&srcData[indices[1] * vertexSize + 3 * sizeof(float)])) :
                Vector3::ZERO;
            const Vector3& n2 = hasNormals ? *((const Vector3*)(&srcData[indices[2] * vertexSize + 3 * sizeof(float)])) :
                Vector3::ZERO;
            
            if (!hasNormals || decalNormal.DotProduct((n0 + n1 + n2) / 3.0f) >= normalCutoff)
            {
                // First check coarsely against all planes to avoid adding unnecessary faces to the clipping algorithm
                bool outside = false;
                for (unsigned i = PLANE_FAR; i < NUM_FRUSTUM_PLANES; --i)
                {
                    const Plane& plane = frustum.planes_[i];
                    if (plane.Distance(v0) < 0.0f && plane.Distance(v1) < 0.0f && plane.Distance(v2) < 0.0f)
                    {
                        outside = true;
                        break;
                    }
                }
                
                if (!outside)
                {
                    faces.Resize(faces.Size() + 1);
                    PODVector<DecalVertex>& face = faces.Back();
                    face.Push(DecalVertex(v0, n0));
                    face.Push(DecalVertex(v1, n1));
                    face.Push(DecalVertex(v2, n2));
                }
            }
            
            indices += 3;
        }
    }
    // 32-bit indices
    else
    {
        const unsigned* indices = ((const unsigned*)indexData) + indexStart;
        const unsigned* indicesEnd = indices + indexCount;
        
        while (indices < indicesEnd)
        {
            const Vector3& v0 = *((const Vector3*)(&srcData[indices[0] * vertexSize]));
            const Vector3& v1 = *((const Vector3*)(&srcData[indices[1] * vertexSize]));
            const Vector3& v2 = *((const Vector3*)(&srcData[indices[2] * vertexSize]));
            const Vector3& n0 = hasNormals ? *((const Vector3*)(&srcData[indices[0] * vertexSize + 3 * sizeof(float)])) :
                Vector3::ZERO;
            const Vector3& n1 = hasNormals ? *((const Vector3*)(&srcData[indices[1] * vertexSize + 3 * sizeof(float)])) :
                Vector3::ZERO;
            const Vector3& n2 = hasNormals ? *((const Vector3*)(&srcData[indices[2] * vertexSize + 3 * sizeof(float)])) :
                Vector3::ZERO;
            
            if (!hasNormals || decalNormal.DotProduct((n0 + n1 + n2) / 3.0f) >= normalCutoff)
            {
                bool outside = false;
                for (unsigned i = PLANE_FAR; i < NUM_FRUSTUM_PLANES; --i)
                {
                    const Plane& plane = frustum.planes_[i];
                    if (plane.Distance(v0) < 0.0f && plane.Distance(v1) < 0.0f && plane.Distance(v2) < 0.0f)
                    {
                        outside = true;
                        break;
                    }
                }
                
                if (!outside)
                {
                    faces.Resize(faces.Size() + 1);
                    PODVector<DecalVertex>& face = faces.Back();
                    face.Push(DecalVertex(v0, n0));
                    face.Push(DecalVertex(v1, n1));
                    face.Push(DecalVertex(v2, n2));
                }
            }
            
            indices += 3;
        }
    }
}

void DecalSet::CalculateUVs(Decal& decal, const Matrix3x4& view, float size, float aspectRatio, float depth, const Vector2& topLeftUV, const Vector2& bottomRightUV)
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
    if (vertexBuffer_->GetVertexCount() != maxVertices_)
    {
        vertexBuffer_->SetSize(maxVertices_, MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1 | MASK_TANGENT);
        bufferDirty_ = true;
    }
    
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
            }
        }
        
        vertexBuffer_->Unlock();
    }
    
    vertexBuffer_->ClearDataLost();
    bufferDirty_ = false;
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
