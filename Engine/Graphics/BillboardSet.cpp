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
#include "BillboardSet.h"
#include "Camera.h"
#include "Context.h"
#include "Geometry.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "IndexBuffer.h"
#include "MemoryBuffer.h"
#include "Node.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Sort.h"
#include "VertexBuffer.h"
#include "XMLElement.h"

#include "DebugNew.h"

static const Vector3 DOT_SCALE(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);
static const float INV_SQRT_TWO = 1.0f / sqrtf(2.0f);

inline bool CompareBillboards(Billboard* lhs, Billboard* rhs)
{
    return lhs->sortDistance_ > rhs->sortDistance_;
}

OBJECTTYPESTATIC(BillboardSet);

BillboardSet::BillboardSet(Context* context) :
    Drawable(context),
    animationLodBias_(1.0f),
    animationLodTimer_(0.0f),
    relative_(true),
    scaled_(true),
    sorted_(false),
    geometry_(new Geometry(context)),
    vertexBuffer_(new VertexBuffer(context_)),
    indexBuffer_(new IndexBuffer(context_)),
    bufferSizeDirty_(true),
    bufferDirty_(true),
    forceUpdate_(false),
    sortFrameNumber_(0),
    previousOffset_(Vector3::ZERO)
{
    drawableFlags_ = DRAWABLE_GEOMETRY;
    
    geometry_->SetVertexBuffer(0, vertexBuffer_, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1 | MASK_TEXCOORD2);
    geometry_->SetIndexBuffer(indexBuffer_);
    
    batches_.Resize(1);
    batches_[0].geometry_ = geometry_;
    batches_[0].geometryType_ = GEOM_BILLBOARD;
}

BillboardSet::~BillboardSet()
{
}

void BillboardSet::RegisterObject(Context* context)
{
    context->RegisterFactory<BillboardSet>();
    
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_RESOURCEREF, "Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()), AM_DEFAULT);
    ATTRIBUTE(BillboardSet, VAR_BOOL, "Is Visible", visible_, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_BOOL, "Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    ATTRIBUTE(BillboardSet, VAR_BOOL, "Cast Shadows", castShadows_, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_BOOL, "Relative Position", IsRelative, SetRelative, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_BOOL, "Relative Scale", IsScaled, SetScaled, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_BOOL, "Sort By Distance", IsSorted, SetSorted, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_FLOAT, "Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_FLOAT, "Shadow Distance", GetShadowDistance, SetShadowDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_FLOAT, "Animation LOD Bias", GetAnimationLodBias, SetAnimationLodBias, float, 1.0f, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(BillboardSet, Drawable);
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_VARIANTVECTOR, "Billboards", GetBillboardsAttr, SetBillboardsAttr, VariantVector, VariantVector(), AM_FILE);
    REF_ACCESSOR_ATTRIBUTE(BillboardSet, VAR_BUFFER, "Network Billboards", GetNetBillboardsAttr, SetNetBillboardsAttr, PODVector<unsigned char>, PODVector<unsigned char>(), AM_NET | AM_NOEDIT);
}

void BillboardSet::UpdateBatches(const FrameInfo& frame)
{
    // Check if position relative to camera has changed, and re-sort in that case
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    Vector3 worldPos = worldTransform.Translation();
    Vector3 offset = (worldPos - frame.camera_->GetNode()->GetWorldPosition());
    if (offset != previousOffset_)
    {
        previousOffset_ = offset;
        if (sorted_)
        {
            // Sort billboards only once per frame. This means that secondary views will get
            // the same sorting as the main view
            if (frame.frameNumber_ != sortFrameNumber_)
            {
                sortFrameNumber_ = frame.frameNumber_;
                bufferDirty_ = true;
            }
        }
    }
    
    distance_ = frame.camera_->GetDistance(worldPos);
    
    // Calculate scaled distance for animation LOD
    float scale = GetWorldBoundingBox().Size().DotProduct(DOT_SCALE);
    // If there are no billboards, the size becomes zero, and LOD'ed updates no longer happen. Disable LOD in that case
    if (scale > M_EPSILON)
        lodDistance_ = frame.camera_->GetLodDistance(distance_, scale, lodBias_);
    else
        lodDistance_ = 0.0f;
    
    batches_[0].distance_ = distance_;
    batches_[0].worldTransform_ = relative_ ? &node_->GetWorldTransform() : &Matrix3x4::IDENTITY;
}

void BillboardSet::UpdateGeometry(const FrameInfo& frame)
{
    if (bufferSizeDirty_ || vertexBuffer_->IsDataLost() || indexBuffer_->IsDataLost())
        UpdateBufferSize();
    
    if (bufferDirty_)
        UpdateVertexBuffer(frame);
}

UpdateGeometryType BillboardSet::GetUpdateGeometryType()
{
    if (bufferDirty_ || bufferSizeDirty_ || vertexBuffer_->IsDataLost() || indexBuffer_->IsDataLost())
        return UPDATE_MAIN_THREAD;
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
        billboards_[i].enabled_ = false;
    }
    
    bufferSizeDirty_ = true;
    MarkPositionsDirty();
    MarkNetworkUpdate();
}

void BillboardSet::SetRelative(bool enable)
{
    relative_ = enable;
    MarkPositionsDirty();
    MarkNetworkUpdate();
}

void BillboardSet::SetScaled(bool enable)
{
    scaled_ = enable;
    MarkPositionsDirty();
    MarkNetworkUpdate();
}

void BillboardSet::SetSorted(bool enable)
{
    sorted_ = enable;
    MarkPositionsDirty();
    MarkNetworkUpdate();
}

void BillboardSet::SetAnimationLodBias(float bias)
{
    animationLodBias_ = Max(bias, 0.0f);
    MarkNetworkUpdate();
}

void BillboardSet::Updated()
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

void BillboardSet::SetMaterialAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetMaterial(cache->GetResource<Material>(value.id_));
}

void BillboardSet::SetBillboardsAttr(VariantVector value)
{
    unsigned index = 0;
    SetNumBillboards(value[index++].GetInt());
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
    Updated();
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
        i->enabled_ = buf.ReadBool();
    }
    Updated();
}

ResourceRef BillboardSet::GetMaterialAttr() const
{
    return GetResourceRef(batches_[0].material_, Material::GetTypeStatic());
}

VariantVector BillboardSet::GetBillboardsAttr() const
{
    VariantVector ret;
    ret.Push(billboards_.Size());
    for (PODVector<Billboard>::ConstIterator i = billboards_.Begin(); i != billboards_.End(); ++i)
    {
        ret.Push(i->position_);
        ret.Push(i->size_);
        ret.Push(Vector4(i->uv_.min_.x_, i->uv_.min_.y_, i->uv_.max_.x_, i->uv_.max_.y_));
        ret.Push(i->color_);
        ret.Push(i->rotation_);
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
        attrBuffer_.WriteBool(i->enabled_);
    }
    return attrBuffer_.GetBuffer();
}

void BillboardSet::OnWorldBoundingBoxUpdate()
{
    worldBoundingBox_.defined_ = false;
    
    unsigned enabledBillboards = 0;
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    Matrix3x4 billboardTransform = relative_ ? worldTransform : Matrix3x4::IDENTITY;
    Vector3 billboardScale = scaled_ ? worldTransform.Scale() : Vector3::ONE;
    
    for (unsigned i = 0; i < billboards_.Size(); ++i)
    {
        if (!billboards_[i].enabled_)
            continue;
        
        float size = INV_SQRT_TWO * (billboards_[i].size_.x_ * billboardScale.x_ + billboards_[i].size_.y_ * billboardScale.y_);
        Vector3 center = billboardTransform * billboards_[i].position_;
        Vector3 edge = Vector3::ONE * size;
        worldBoundingBox_.Merge(BoundingBox(center - edge, center + edge));
        
        ++enabledBillboards;
    }
    
    // If no billboards enabled, the bounding box is just the node's world position
    if (!enabledBillboards)
        worldBoundingBox_.Merge(node_->GetWorldPosition());
}

void BillboardSet::UpdateBufferSize()
{
    unsigned numBillboards = billboards_.Size();
    
    if (vertexBuffer_->GetVertexCount() != numBillboards * 4)
        vertexBuffer_->SetSize(numBillboards * 4, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1 | MASK_TEXCOORD2, true);
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
        *dest++ = vertexIndex; *dest++ = vertexIndex + 1; *dest++ = vertexIndex + 2;
        *dest++ = vertexIndex + 2; *dest++ = vertexIndex + 3; *dest++ = vertexIndex;
        
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
        animationLodTimer_ += animationLodBias_ * frame.timeStep_ * frame.viewSize_.y_ * ANIMATION_LOD_BASESCALE;
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
    Vector3 worldScale = worldTransform.Scale();
    
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
        Sort(sortedBillboards_.Begin(), sortedBillboards_.End(), CompareBillboards);
    
    float* dest = (float*)vertexBuffer_->Lock(0, enabledBillboards * 4, true);
    if (!dest)
        return;
    
    for (unsigned i = 0; i < enabledBillboards; ++i)
    {
        Billboard& billboard = *sortedBillboards_[i];
        
        Vector2 size(billboard.size_.x_ * billboardScale.x_, billboard.size_.y_ * billboardScale.y_);
        unsigned color = billboard.color_.ToUInt();
        float angleRad = billboard.rotation_ * M_DEGTORAD;
        
        float rotationMatrix[2][2];
        rotationMatrix[0][0] = cosf(angleRad);
        rotationMatrix[0][1] = sinf(angleRad);
        rotationMatrix[1][0] = -rotationMatrix[0][1];
        rotationMatrix[1][1] = rotationMatrix[0][0];
        
        *dest++ = billboard.position_.x_; *dest++ = billboard.position_.y_; *dest++ = billboard.position_.z_;
        *((unsigned*)dest) = color; dest++;
        *dest++ = billboard.uv_.min_.x_; *dest++ = billboard.uv_.max_.y_;
        *dest++ = -size.x_ * rotationMatrix[0][0] + size.y_ * rotationMatrix[0][1];
        *dest++ = -size.x_ * rotationMatrix[1][0] + size.y_ * rotationMatrix[1][1];
        
        *dest++ = billboard.position_.x_; *dest++ = billboard.position_.y_; *dest++ = billboard.position_.z_;
        *((unsigned*)dest) = color; dest++;
        *dest++ = billboard.uv_.max_.x_; *dest++ = billboard.uv_.max_.y_;
        *dest++ = size.x_ * rotationMatrix[0][0] + size.y_ * rotationMatrix[0][1];
        *dest++ = size.x_ * rotationMatrix[1][0] + size.y_ * rotationMatrix[1][1];
        
        *dest++ = billboard.position_.x_; *dest++ = billboard.position_.y_; *dest++ = billboard.position_.z_;
        *((unsigned*)dest) = color; dest++;
        *dest++ = billboard.uv_.max_.x_; *dest++ = billboard.uv_.min_.y_;
        *dest++ = size.x_ * rotationMatrix[0][0] - size.y_ * rotationMatrix[0][1];
        *dest++ = size.x_ * rotationMatrix[1][0] - size.y_ * rotationMatrix[1][1];
        
        *dest++ = billboard.position_.x_; *dest++ = billboard.position_.y_; *dest++ = billboard.position_.z_;
        *((unsigned*)dest) = color; dest++;
        *dest++ = billboard.uv_.min_.x_; *dest++ = billboard.uv_.min_.y_;
        *dest++ = -size.x_ * rotationMatrix[0][0] - size.y_ * rotationMatrix[0][1];
        *dest++ = -size.x_ * rotationMatrix[1][0] - size.y_ * rotationMatrix[1][1];
    }
    
    vertexBuffer_->Unlock();
    vertexBuffer_->ClearDataLost();
}

void BillboardSet::MarkPositionsDirty()
{
    Drawable::OnMarkedDirty(node_);
    bufferDirty_ = true;
}
