//
// Copyright (c) 2008-2016 the Urho3D project.
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
#include "../Graphics/Batch.h"
#include "../Graphics/BillboardSet.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Material.h"
#include "../Graphics/OctreeQuery.h"
#include "../Graphics/VertexBuffer.h"
#include "../IO/MemoryBuffer.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Node.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;

static const float INV_SQRT_TWO = 1.0f / sqrtf(2.0f);

const char* faceCameraModeNames[] =
{
    "None",
    "Rotate XYZ",
    "Rotate Y",
    "LookAt XYZ",
    "LookAt Y",
    "Direction",
    0
};

inline bool CompareBillboards(Billboard* lhs, Billboard* rhs)
{
    return lhs->sortDistance_ > rhs->sortDistance_;
}

BillboardSet::BillboardSet(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY),
    animationLodBias_(1.0f),
    animationLodTimer_(0.0f),
    relative_(true),
    scaled_(true),
    sorted_(false),
    faceCameraMode_(FC_ROTATE_XYZ),
    geometry_(new Geometry(context)),
    vertexBuffer_(new VertexBuffer(context_)),
    indexBuffer_(new IndexBuffer(context_)),
    bufferSizeDirty_(true),
    bufferDirty_(true),
    forceUpdate_(false),
    geometryTypeUpdate_(false),
    sortThisFrame_(false),
    sortFrameNumber_(0),
    previousOffset_(Vector3::ZERO)
{
    geometry_->SetVertexBuffer(0, vertexBuffer_);
    geometry_->SetIndexBuffer(indexBuffer_);

    batches_.Resize(1);
    batches_[0].geometry_ = geometry_;
    batches_[0].geometryType_ = GEOM_BILLBOARD;
    batches_[0].worldTransform_ = &transforms_[0];
}

BillboardSet::~BillboardSet()
{
}

void BillboardSet::RegisterObject(Context* context)
{
    context->RegisterFactory<BillboardSet>(GEOMETRY_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()),
        AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Relative Position", IsRelative, SetRelative, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Relative Scale", IsScaled, SetScaled, bool, true, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Sort By Distance", IsSorted, SetSorted, bool, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Cast Shadows", bool, castShadows_, false, AM_DEFAULT);
    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Face Camera Mode", GetFaceCameraMode, SetFaceCameraMode, FaceCameraMode, faceCameraModeNames, FC_ROTATE_XYZ, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Shadow Distance", GetShadowDistance, SetShadowDistance, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Animation LOD Bias", GetAnimationLodBias, SetAnimationLodBias, float, 1.0f, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Drawable);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Billboards", GetBillboardsAttr, SetBillboardsAttr, VariantVector, Variant::emptyVariantVector,
        AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Network Billboards", GetNetBillboardsAttr, SetNetBillboardsAttr, PODVector<unsigned char>,
        Variant::emptyBuffer, AM_NET | AM_NOEDIT);
}

void BillboardSet::ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results)
{
    // If no billboard-level testing, use the Drawable test
    if (query.level_ < RAY_TRIANGLE)
    {
        Drawable::ProcessRayQuery(query, results);
        return;
    }

    // Check ray hit distance to AABB before proceeding with billboard-level tests
    if (query.ray_.HitDistance(GetWorldBoundingBox()) >= query.maxDistance_)
        return;

    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    Matrix3x4 billboardTransform = relative_ ? worldTransform : Matrix3x4::IDENTITY;
    Vector3 billboardScale = scaled_ ? worldTransform.Scale() : Vector3::ONE;

    for (unsigned i = 0; i < billboards_.Size(); ++i)
    {
        if (!billboards_[i].enabled_)
            continue;

        // Approximate the billboards as spheres for raycasting
        float size = INV_SQRT_TWO * (billboards_[i].size_.x_ * billboardScale.x_ + billboards_[i].size_.y_ * billboardScale.y_);
        Vector3 center = billboardTransform * billboards_[i].position_;
        Sphere billboardSphere(center, size);

        float distance = query.ray_.HitDistance(billboardSphere);
        if (distance < query.maxDistance_)
        {
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
}

void BillboardSet::UpdateBatches(const FrameInfo& frame)
{
    // If beginning a new frame, assume no sorting first
    if (frame.frameNumber_ != sortFrameNumber_)
    {
        sortThisFrame_ = false;
        sortFrameNumber_ = frame.frameNumber_;
    }

    Vector3 worldPos = node_->GetWorldPosition();
    Vector3 offset = (worldPos - frame.camera_->GetNode()->GetWorldPosition());
    // Sort if position relative to camera has changed
    if (offset != previousOffset_)
    {
        if(sorted_)
            sortThisFrame_ = true;
        if(faceCameraMode_ == FC_DIRECTION)
            bufferDirty_ = true;
    }

    distance_ = frame.camera_->GetDistance(GetWorldBoundingBox().Center());

    // Calculate scaled distance for animation LOD
    float scale = GetWorldBoundingBox().Size().DotProduct(DOT_SCALE);
    // If there are no billboards, the size becomes zero, and LOD'ed updates no longer happen. Disable LOD in that case
    if (scale > M_EPSILON)
        lodDistance_ = frame.camera_->GetLodDistance(distance_, scale, lodBias_);
    else
        lodDistance_ = 0.0f;

    batches_[0].distance_ = distance_;
    batches_[0].numWorldTransforms_ = 2;
    // Billboard positioning
    transforms_[0] = relative_ ? node_->GetWorldTransform() : Matrix3x4::IDENTITY;
    // Billboard rotation
    transforms_[1] = Matrix3x4(Vector3::ZERO, faceCameraMode_ != FC_NONE ? frame.camera_->GetFaceCameraRotation(
        node_->GetWorldPosition(), node_->GetWorldRotation(), faceCameraMode_) : node_->GetWorldRotation(), Vector3::ONE);
}

void BillboardSet::UpdateGeometry(const FrameInfo& frame)
{
    if (bufferSizeDirty_ || indexBuffer_->IsDataLost())
        UpdateBufferSize();

    if (bufferDirty_ || sortThisFrame_ || vertexBuffer_->IsDataLost())
        UpdateVertexBuffer(frame);

    // If using camera facing, re-update the rotation for the current view now
    if (faceCameraMode_ != FC_NONE)
    {
        transforms_[1] = Matrix3x4(Vector3::ZERO, frame.camera_->GetFaceCameraRotation(node_->GetWorldPosition(),
            node_->GetWorldRotation(), faceCameraMode_), Vector3::ONE);
    }
}

UpdateGeometryType BillboardSet::GetUpdateGeometryType()
{
    // If using camera facing, always need some kind of geometry update, in case the billboard set is rendered from several views
    if (bufferDirty_ || bufferSizeDirty_ || vertexBuffer_->IsDataLost() || indexBuffer_->IsDataLost() || sortThisFrame_)
        return UPDATE_MAIN_THREAD;
    else if (faceCameraMode_ != FC_NONE)
        return UPDATE_WORKER_THREAD;
    else
        return UPDATE_NONE;
}

void BillboardSet::SetMaterial(Material* material)
{
    batches_[0].material_ = material;
    MarkNetworkUpdate();
}

void BillboardSet::SetNumBillboards(unsigned num)
{
    // Prevent negative value being assigned from the editor
    if (num > M_MAX_INT)
        num = 0;
    if (num > MAX_BILLBOARDS)
        num = MAX_BILLBOARDS;

    unsigned oldNum = billboards_.Size();

    billboards_.Resize(num);

    // Set default values to new billboards
    for (unsigned i = oldNum; i < num; ++i)
    {
        billboards_[i].position_ = Vector3::ZERO;
        billboards_[i].size_ = Vector2::ONE;
        billboards_[i].uv_ = Rect::POSITIVE;
        billboards_[i].color_ = Color(1.0f, 1.0f, 1.0f);
        billboards_[i].rotation_ = 0.0f;
        billboards_[i].direction_ = Vector3::UP;
        billboards_[i].enabled_ = false;
    }

    bufferSizeDirty_ = true;
    Commit();
}

void BillboardSet::SetRelative(bool enable)
{
    relative_ = enable;
    Commit();
}

void BillboardSet::SetScaled(bool enable)
{
    scaled_ = enable;
    Commit();
}

void BillboardSet::SetSorted(bool enable)
{
    sorted_ = enable;
    Commit();
}

void BillboardSet::SetFaceCameraMode(FaceCameraMode mode)
{
    if ((faceCameraMode_ != FC_DIRECTION && mode == FC_DIRECTION) || (faceCameraMode_ == FC_DIRECTION && mode != FC_DIRECTION))
    {
        faceCameraMode_ = mode;
        if (faceCameraMode_ == FC_DIRECTION)
            batches_[0].geometryType_ = GEOM_DIRBILLBOARD;
        else
            batches_[0].geometryType_ = GEOM_BILLBOARD;
        geometryTypeUpdate_ = true;
        bufferSizeDirty_ = true;
        Commit();
    }
    else
    {
        faceCameraMode_ = mode;
        MarkNetworkUpdate();
    }
}

void BillboardSet::SetAnimationLodBias(float bias)
{
    animationLodBias_ = Max(bias, 0.0f);
    MarkNetworkUpdate();
}

void BillboardSet::Commit()
{
    MarkPositionsDirty();
    MarkNetworkUpdate();
}

Material* BillboardSet::GetMaterial() const
{
    return batches_[0].material_;
}

Billboard* BillboardSet::GetBillboard(unsigned index)
{
    return index < billboards_.Size() ? &billboards_[index] : (Billboard*)0;
}

void BillboardSet::SetMaterialAttr(const ResourceRef& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetMaterial(cache->GetResource<Material>(value.name_));
}

void BillboardSet::SetBillboardsAttr(const VariantVector& value)
{
    unsigned index = 0;
    unsigned numBillboards = index < value.Size() ? value[index++].GetUInt() : 0;
    SetNumBillboards(numBillboards);

    // Dealing with old billboard format
    if (value.Size() == billboards_.Size() * 6 + 1)
    {
        for (PODVector<Billboard>::Iterator i = billboards_.Begin(); i != billboards_.End() && index < value.Size(); ++i)
        {
            i->position_ = value[index++].GetVector3();
            i->size_ = value[index++].GetVector2();
            Vector4 uv = value[index++].GetVector4();
            i->uv_ = Rect(uv.x_, uv.y_, uv.z_, uv.w_);
            i->color_ = value[index++].GetColor();
            i->rotation_ = value[index++].GetFloat();
            i->enabled_ = value[index++].GetBool();
        }
    }
    // New billboard format
    else
    {
        for (PODVector<Billboard>::Iterator i = billboards_.Begin(); i != billboards_.End() && index < value.Size(); ++i)
        {
            i->position_ = value[index++].GetVector3();
            i->size_ = value[index++].GetVector2();
            Vector4 uv = value[index++].GetVector4();
            i->uv_ = Rect(uv.x_, uv.y_, uv.z_, uv.w_);
            i->color_ = value[index++].GetColor();
            i->rotation_ = value[index++].GetFloat();
            i->direction_ = value[index++].GetVector3();
            i->enabled_ = value[index++].GetBool();
        }
    }

    Commit();
}

void BillboardSet::SetNetBillboardsAttr(const PODVector<unsigned char>& value)
{
    MemoryBuffer buf(value);
    unsigned numBillboards = buf.ReadVLE();
    SetNumBillboards(numBillboards);

    for (PODVector<Billboard>::Iterator i = billboards_.Begin(); i != billboards_.End(); ++i)
    {
        i->position_ = buf.ReadVector3();
        i->size_ = buf.ReadVector2();
        i->uv_ = buf.ReadRect();
        i->color_ = buf.ReadColor();
        i->rotation_ = buf.ReadFloat();
        i->direction_ = buf.ReadVector3();
        i->enabled_ = buf.ReadBool();
    }

    Commit();
}

ResourceRef BillboardSet::GetMaterialAttr() const
{
    return GetResourceRef(batches_[0].material_, Material::GetTypeStatic());
}

VariantVector BillboardSet::GetBillboardsAttr() const
{
    VariantVector ret;
    ret.Reserve(billboards_.Size() * 7 + 1);
    ret.Push(billboards_.Size());

    for (PODVector<Billboard>::ConstIterator i = billboards_.Begin(); i != billboards_.End(); ++i)
    {
        ret.Push(i->position_);
        ret.Push(i->size_);
        ret.Push(Vector4(i->uv_.min_.x_, i->uv_.min_.y_, i->uv_.max_.x_, i->uv_.max_.y_));
        ret.Push(i->color_);
        ret.Push(i->rotation_);
        ret.Push(i->direction_);
        ret.Push(i->enabled_);
    }

    return ret;
}

const PODVector<unsigned char>& BillboardSet::GetNetBillboardsAttr() const
{
    attrBuffer_.Clear();
    attrBuffer_.WriteVLE(billboards_.Size());

    for (PODVector<Billboard>::ConstIterator i = billboards_.Begin(); i != billboards_.End(); ++i)
    {
        attrBuffer_.WriteVector3(i->position_);
        attrBuffer_.WriteVector2(i->size_);
        attrBuffer_.WriteRect(i->uv_);
        attrBuffer_.WriteColor(i->color_);
        attrBuffer_.WriteFloat(i->rotation_);
        attrBuffer_.WriteVector3(i->direction_);
        attrBuffer_.WriteBool(i->enabled_);
    }

    return attrBuffer_.GetBuffer();
}

void BillboardSet::OnWorldBoundingBoxUpdate()
{
    unsigned enabledBillboards = 0;
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    Matrix3x4 billboardTransform = relative_ ? worldTransform : Matrix3x4::IDENTITY;
    Vector3 billboardScale = scaled_ ? worldTransform.Scale() : Vector3::ONE;
    BoundingBox worldBox;

    for (unsigned i = 0; i < billboards_.Size(); ++i)
    {
        if (!billboards_[i].enabled_)
            continue;

        float size = INV_SQRT_TWO * (billboards_[i].size_.x_ * billboardScale.x_ + billboards_[i].size_.y_ * billboardScale.y_);
        Vector3 center = billboardTransform * billboards_[i].position_;
        Vector3 edge = Vector3::ONE * size;
        worldBox.Merge(BoundingBox(center - edge, center + edge));

        ++enabledBillboards;
    }

    // Always merge the node's own position to ensure particle emitter updates continue when the relative mode is switched
    worldBox.Merge(node_->GetWorldPosition());

    worldBoundingBox_ = worldBox;
}

void BillboardSet::UpdateBufferSize()
{
    unsigned numBillboards = billboards_.Size();

    if (vertexBuffer_->GetVertexCount() != numBillboards * 4 || geometryTypeUpdate_)
    {
        if (faceCameraMode_ == FC_DIRECTION)
        {
            vertexBuffer_->SetSize(numBillboards * 4, MASK_POSITION | MASK_NORMAL | MASK_COLOR | MASK_TEXCOORD1 | MASK_TEXCOORD2 | MASK_TANGENT, true);
            geometry_->SetVertexBuffer(0, vertexBuffer_);

        } 
        else 
        {
            vertexBuffer_->SetSize(numBillboards * 4, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1 | MASK_TEXCOORD2, true);
            geometry_->SetVertexBuffer(0, vertexBuffer_);
        }
        geometryTypeUpdate_ = false;
    }
    if (indexBuffer_->GetIndexCount() != numBillboards * 6)
        indexBuffer_->SetSize(numBillboards * 6, false);

    bufferSizeDirty_ = false;
    bufferDirty_ = true;
    forceUpdate_ = true;

    if (!numBillboards)
        return;

    // Indices do not change for a given billboard capacity
    unsigned short* dest = (unsigned short*)indexBuffer_->Lock(0, numBillboards * 6, true);
    if (!dest)
        return;

    unsigned vertexIndex = 0;
    while (numBillboards--)
    {
        dest[0] = (unsigned short)vertexIndex;
        dest[1] = (unsigned short)(vertexIndex + 1);
        dest[2] = (unsigned short)(vertexIndex + 2);
        dest[3] = (unsigned short)(vertexIndex + 2);
        dest[4] = (unsigned short)(vertexIndex + 3);
        dest[5] = (unsigned short)vertexIndex;

        dest += 6;
        vertexIndex += 4;
    }

    indexBuffer_->Unlock();
    indexBuffer_->ClearDataLost();
}

void BillboardSet::UpdateVertexBuffer(const FrameInfo& frame)
{
    // If using animation LOD, accumulate time and see if it is time to update
    if (animationLodBias_ > 0.0f && lodDistance_ > 0.0f)
    {
        animationLodTimer_ += animationLodBias_ * frame.timeStep_ * ANIMATION_LOD_BASESCALE;
        if (animationLodTimer_ >= lodDistance_)
            animationLodTimer_ = fmodf(animationLodTimer_, lodDistance_);
        else
        {
            // No LOD if immediate update forced
            if (!forceUpdate_)
                return;
        }
    }

    unsigned numBillboards = billboards_.Size();
    unsigned enabledBillboards = 0;
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    Matrix3x4 billboardTransform = relative_ ? worldTransform : Matrix3x4::IDENTITY;
    Vector3 billboardScale = scaled_ ? worldTransform.Scale() : Vector3::ONE;

    // First check number of enabled billboards
    for (unsigned i = 0; i < numBillboards; ++i)
    {
        if (billboards_[i].enabled_)
            ++enabledBillboards;
    }

    sortedBillboards_.Resize(enabledBillboards);
    unsigned index = 0;

    // Then set initial sort order and distances
    for (unsigned i = 0; i < numBillboards; ++i)
    {
        Billboard& billboard = billboards_[i];
        if (billboard.enabled_)
        {
            sortedBillboards_[index++] = &billboard;
            if (sorted_)
                billboard.sortDistance_ = frame.camera_->GetDistanceSquared(billboardTransform * billboards_[i].position_);
        }
    }

    batches_[0].geometry_->SetDrawRange(TRIANGLE_LIST, 0, enabledBillboards * 6, false);

    bufferDirty_ = false;
    forceUpdate_ = false;
    if (!enabledBillboards)
        return;

    if (sorted_)
    {
        Sort(sortedBillboards_.Begin(), sortedBillboards_.End(), CompareBillboards);
        Vector3 worldPos = node_->GetWorldPosition();
        // Store the "last sorted position" now
        previousOffset_ = (worldPos - frame.camera_->GetNode()->GetWorldPosition());
    }

    float* dest = (float*)vertexBuffer_->Lock(0, enabledBillboards * 4, true);
    if (!dest)
        return;

    if (faceCameraMode_ != FC_DIRECTION)
    {
        for (unsigned i = 0; i < enabledBillboards; ++i)
        {
            Billboard& billboard = *sortedBillboards_[i];

            Vector2 size(billboard.size_.x_ * billboardScale.x_, billboard.size_.y_ * billboardScale.y_);
            unsigned color = billboard.color_.ToUInt();

            float rotationMatrix[2][2];
            SinCos(billboard.rotation_, rotationMatrix[0][1], rotationMatrix[0][0]);
            rotationMatrix[1][0] = -rotationMatrix[0][1];
            rotationMatrix[1][1] = rotationMatrix[0][0];

            dest[0] = billboard.position_.x_;
            dest[1] = billboard.position_.y_;
            dest[2] = billboard.position_.z_;
            ((unsigned&)dest[3]) = color;
            dest[4] = billboard.uv_.min_.x_;
            dest[5] = billboard.uv_.min_.y_;
            dest[6] = -size.x_ * rotationMatrix[0][0] + size.y_ * rotationMatrix[0][1];
            dest[7] = -size.x_ * rotationMatrix[1][0] + size.y_ * rotationMatrix[1][1];

            dest[8] = billboard.position_.x_;
            dest[9] = billboard.position_.y_;
            dest[10] = billboard.position_.z_;
            ((unsigned&)dest[11]) = color;
            dest[12] = billboard.uv_.max_.x_;
            dest[13] = billboard.uv_.min_.y_;
            dest[14] = size.x_ * rotationMatrix[0][0] + size.y_ * rotationMatrix[0][1];
            dest[15] = size.x_ * rotationMatrix[1][0] + size.y_ * rotationMatrix[1][1];

            dest[16] = billboard.position_.x_;
            dest[17] = billboard.position_.y_;
            dest[18] = billboard.position_.z_;
            ((unsigned&)dest[19]) = color;
            dest[20] = billboard.uv_.max_.x_;
            dest[21] = billboard.uv_.max_.y_;
            dest[22] = size.x_ * rotationMatrix[0][0] - size.y_ * rotationMatrix[0][1];
            dest[23] = size.x_ * rotationMatrix[1][0] - size.y_ * rotationMatrix[1][1];

            dest[24] = billboard.position_.x_;
            dest[25] = billboard.position_.y_;
            dest[26] = billboard.position_.z_;
            ((unsigned&)dest[27]) = color;
            dest[28] = billboard.uv_.min_.x_;
            dest[29] = billboard.uv_.max_.y_;
            dest[30] = -size.x_ * rotationMatrix[0][0] - size.y_ * rotationMatrix[0][1];
            dest[31] = -size.x_ * rotationMatrix[1][0] - size.y_ * rotationMatrix[1][1];

            dest += 32;
        }
    } 
    else
    {
        Vector3 cameraWorldPosition = frame.camera_->GetNode()->GetWorldPosition();

        for (unsigned i = 0; i < enabledBillboards; ++i)
        {
            Billboard& billboard = *sortedBillboards_[i];

            Vector2 size(billboard.size_.x_ * billboardScale.x_, billboard.size_.y_ * billboardScale.y_);
            unsigned color = billboard.color_.ToUInt();

            float rot2D[2][2];
            SinCos(billboard.rotation_, rot2D[0][1], rot2D[0][0]);
            rot2D[1][0] = -rot2D[0][1];
            rot2D[1][1] = rot2D[0][0];

            dest[0] = billboard.position_.x_;
            dest[1] = billboard.position_.y_;
            dest[2] = billboard.position_.z_;
            dest[3] = billboard.direction_.x_;
            dest[4] = billboard.direction_.y_;
            dest[5] = billboard.direction_.z_;
            ((unsigned&)dest[6]) = color;
            dest[7] = billboard.uv_.min_.x_;
            dest[8] = billboard.uv_.min_.y_;
            dest[9] = -size.x_ * rot2D[0][0] + size.y_ * rot2D[0][1];
            dest[10] = -size.x_ * rot2D[1][0] + size.y_ * rot2D[1][1];
            dest[11] = cameraWorldPosition.x_;
            dest[12] = cameraWorldPosition.y_;
            dest[13] = cameraWorldPosition.z_;
            dest[14] = 1.0f;

            dest[15] = billboard.position_.x_;
            dest[16] = billboard.position_.y_;
            dest[17] = billboard.position_.z_;
            dest[18] = billboard.direction_.x_;
            dest[19] = billboard.direction_.y_;
            dest[20] = billboard.direction_.z_;
            ((unsigned&)dest[21]) = color;
            dest[22] = billboard.uv_.max_.x_;
            dest[23] = billboard.uv_.min_.y_;
            dest[24] = size.x_ * rot2D[0][0] + size.y_ * rot2D[0][1];
            dest[25] = size.x_ * rot2D[1][0] + size.y_ * rot2D[1][1];
            dest[26] = cameraWorldPosition.x_;
            dest[27] = cameraWorldPosition.y_;
            dest[28] = cameraWorldPosition.z_;
            dest[29] = 1.0f;

            dest[30] = billboard.position_.x_;
            dest[31] = billboard.position_.y_;
            dest[32] = billboard.position_.z_;
            dest[33] = billboard.direction_.x_;
            dest[34] = billboard.direction_.y_;
            dest[35] = billboard.direction_.z_;
            ((unsigned&)dest[36]) = color;
            dest[37] = billboard.uv_.max_.x_;
            dest[38] = billboard.uv_.max_.y_;
            dest[39] = size.x_ * rot2D[0][0] - size.y_ * rot2D[0][1];
            dest[40] = size.x_ * rot2D[1][0] - size.y_ * rot2D[1][1];
            dest[41] = cameraWorldPosition.x_;
            dest[42] = cameraWorldPosition.y_;
            dest[43] = cameraWorldPosition.z_;
            dest[44] = 1.0f;

            dest[45] = billboard.position_.x_;
            dest[46] = billboard.position_.y_;
            dest[47] = billboard.position_.z_;
            dest[48] = billboard.direction_.x_;
            dest[49] = billboard.direction_.y_;
            dest[50] = billboard.direction_.z_;
            ((unsigned&)dest[51]) = color;
            dest[52] = billboard.uv_.min_.x_;
            dest[53] = billboard.uv_.max_.y_;
            dest[54] = -size.x_ * rot2D[0][0] - size.y_ * rot2D[0][1];
            dest[55] = -size.x_ * rot2D[1][0] - size.y_ * rot2D[1][1];
            dest[56] = cameraWorldPosition.x_;
            dest[57] = cameraWorldPosition.y_;
            dest[58] = cameraWorldPosition.z_;
            dest[59] = 1.0f;

            dest += 60;
        }
    }

    vertexBuffer_->Unlock();
    vertexBuffer_->ClearDataLost();
}

void BillboardSet::MarkPositionsDirty()
{
    Drawable::OnMarkedDirty(node_);
    bufferDirty_ = true;
}

}
