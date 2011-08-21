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
#include "Batch.h"
#include "BillboardSet.h"
#include "Camera.h"
#include "Context.h"
#include "Geometry.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "IndexBuffer.h"
#include "Material.h"
#include "MemoryBuffer.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Sort.h"
#include "VertexBuffer.h"
#include "XMLElement.h"

#include "DebugNew.h"

static const Vector3 dotScale(1 / 3.0f, 1 / 3.0f, 1 / 3.0f);

inline bool CompareBillboards(Billboard* lhs, Billboard* rhs)
{
    return lhs->sortDistance_ > rhs->sortDistance_;
}

OBJECTTYPESTATIC(BillboardSet);

BillboardSet::BillboardSet(Context* context) :
    Drawable(context),
    geometry_(new Geometry(context_)),
    animationLodBias_(1.0f),
    animationLodTimer_(0.0f),
    relative_(true),
    scaled_(true),
    sorted_(false),
    bufferSizeDirty_(true),
    bufferDirty_(true),
    forceUpdate_(false),
    previousOffset_(Vector3::ZERO),
    sortFrameNumber_(0)
{
    drawableFlags_ = DRAWABLE_GEOMETRY;
}

BillboardSet::~BillboardSet()
{
}

void BillboardSet::RegisterObject(Context* context)
{
    context->RegisterFactory<BillboardSet>();
    context->CopyBaseAttributes<Drawable, BillboardSet>();
    
    ATTRIBUTE(BillboardSet, VAR_FLOAT, "Animation LOD Bias", animationLodBias_, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_BOOL, "Relative Position", IsRelative, SetRelative, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_BOOL, "Relative Scale", IsScaled, SetScaled, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_BOOL, "Sort By Distance", IsSorted, SetSorted, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_RESOURCEREF, "Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(BillboardSet, VAR_VARIANTVECTOR, "Billboards", GetBillboardsAttr, SetBillboardsAttr, VariantVector, VariantVector(), AM_FILE);
    ATTRIBUTE(BillboardSet, VAR_INT, "View Mask", viewMask_, DEFAULT_VIEWMASK, AM_DEFAULT);
    ATTRIBUTE(BillboardSet, VAR_INT, "Light Mask", lightMask_, DEFAULT_LIGHTMASK, AM_DEFAULT);
    ATTRIBUTE(BillboardSet, VAR_INT, "Max Lights", maxLights_, 0, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(BillboardSet, VAR_BUFFER, "Network Billboards", GetNetBillboardsAttr, SetNetBillboardsAttr, PODVector<unsigned char>, PODVector<unsigned char>(), AM_NET | AM_NOEDIT);
}

void BillboardSet::UpdateDistance(const FrameInfo& frame)
{
    // Check if position relative to camera has changed, and re-sort in that case
    const Vector3& worldPos = GetWorldPosition();
    Vector3 offset = (worldPos - frame.camera_->GetWorldPosition());
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
    float scale = GetWorldBoundingBox().Size().DotProduct(dotScale);
    // If there are no billboards, the size becomes zero, and LOD'ed updates no longer happen. Disable LOD in that case
    if (scale > M_EPSILON)
        lodDistance_ = frame.camera_->GetLodDistance(distance_, scale, lodBias_);
    else
        lodDistance_ = 0.0f;
}

void BillboardSet::UpdateGeometry(const FrameInfo& frame)
{
    if (bufferSizeDirty_)
    {
        UpdateBufferSize();
        forceUpdate_ = true;
    }
    if (vertexBuffer_->IsDataLost())
    {
        vertexBuffer_->ClearDataLost();
        forceUpdate_ = true;
    }
    
    if (bufferDirty_ || forceUpdate_)
        UpdateVertexBuffer(frame);
}

unsigned BillboardSet::GetNumBatches()
{
    return 1;
}

void BillboardSet::GetBatch(const FrameInfo& frame, unsigned batchIndex, Batch& batch)
{
    batch.geometry_ = geometry_;
    batch.geometryType_ = GEOM_BILLBOARD;
    batch.worldTransform_ = &GetWorldTransform();
    batch.material_ = material_;
}

void BillboardSet::SetMaterial(Material* material)
{
    material_ = material;
}

void BillboardSet::SetNumBillboards(unsigned num)
{
    unsigned oldNum = billboards_.Size();
    
    billboards_.Resize(num);
    
    // Set default values to new billboards
    for (unsigned i = oldNum; i < num; ++i)
    {
        billboards_[i].position_ = Vector3::ZERO;
        billboards_[i].size_ = Vector2::UNITY;
        billboards_[i].uv_ = Rect::POSITIVE;
        billboards_[i].color_ = Color(1.0f, 1.0f, 1.0f);
        billboards_[i].rotation_ = 0.0f;
        billboards_[i].enabled_ = false;
    }
    
    bufferSizeDirty_ = true;
    MarkPositionsDirty();
}

void BillboardSet::SetRelative(bool enable)
{
    relative_ = enable;
    MarkPositionsDirty();
}

void BillboardSet::SetScaled(bool enable)
{
    scaled_ = enable;
    MarkPositionsDirty();
}

void BillboardSet::SetSorted(bool enable)
{
    sorted_ = enable;
    MarkPositionsDirty();
}

void BillboardSet::SetAnimationLodBias(float bias)
{
    animationLodBias_ = Max(bias, 0.0f);
}

void BillboardSet::Updated()
{
    MarkPositionsDirty();
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
    return GetResourceRef(material_, Material::GetTypeStatic());
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

void BillboardSet::OnMarkedDirty(Node* node)
{
    if (node == node_)
    {
        Drawable::OnMarkedDirty(node);
        if (relative_)
            bufferDirty_ = true;
    }
}

void BillboardSet::OnWorldBoundingBoxUpdate()
{
    worldBoundingBox_.defined_ = false;
    
    unsigned enabledBillboards = 0;
    const Matrix3x4& worldTransform = GetWorldTransform();
    const Vector3& worldScale = worldTransform.Scale();
    
    for (unsigned i = 0; i < billboards_.Size(); ++i)
    {
        if (!billboards_[i].enabled_)
            continue;
        
        float maxSize;
        if (!scaled_)
            maxSize = Max(billboards_[i].size_.x_, billboards_[i].size_.y_);
        else
            maxSize = Max(billboards_[i].size_.x_ * worldScale.x_, billboards_[i].size_.y_ * worldScale.y_);
        
        if (!relative_)
            worldBoundingBox_.Merge(Sphere(billboards_[i].position_, maxSize));
        else
            worldBoundingBox_.Merge(Sphere(worldTransform * billboards_[i].position_, maxSize));
        
        ++enabledBillboards;
    }
    
    // If no billboards enabled, the bounding box is just the node's world position
    if (!enabledBillboards)
        worldBoundingBox_.Merge(GetWorldPosition());
}

void BillboardSet::UpdateBufferSize()
{
    if (!vertexBuffer_ || !indexBuffer_)
    {
        vertexBuffer_ = new VertexBuffer(context_);
        indexBuffer_ = new IndexBuffer(context_);
        
        geometry_->SetVertexBuffer(0, vertexBuffer_, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1 | MASK_TEXCOORD2);
        geometry_->SetIndexBuffer(indexBuffer_);
    }
    
    unsigned numBillboards = billboards_.Size();
    
    vertexBuffer_->SetSize(numBillboards * 4, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1 | MASK_TEXCOORD2, true);
    indexBuffer_->SetSize(numBillboards * 6, false);
    
    bufferSizeDirty_ = false;
    bufferDirty_ = true;
    if (!numBillboards)
        return;
    
    // Indices do not change for a given billboard capacity
    unsigned short* dest = (unsigned short*)indexBuffer_->Lock(0, numBillboards * 6, LOCK_DISCARD);
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
    
    PROFILE(UpdateBillboardSet);
    
    unsigned numBillboards = billboards_.Size();
    unsigned enabledBillboards = 0;
    const Matrix3x4& worldTransform = GetWorldTransform();
    
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
            {
                if (!relative_)
                    billboard.sortDistance_ = frame.camera_->GetDistanceSquared(billboards_[i].position_);
                else
                    billboard.sortDistance_ = frame.camera_->GetDistanceSquared(worldTransform * billboards_[i].position_);
            }
        }
    }
    
    geometry_->SetDrawRange(TRIANGLE_LIST, 0, enabledBillboards * 6, false);

    bufferDirty_ = false;
    forceUpdate_ = false;
    if (!enabledBillboards)
        return;
    
    if (sorted_)
        Sort(sortedBillboards_.Begin(), sortedBillboards_.End(), CompareBillboards);
    
    float* dest = (float*)vertexBuffer_->Lock(0, enabledBillboards * 4, LOCK_DISCARD);
    if (!dest)
        return;
    const Vector3& worldScale = GetWorldTransform().Scale();
    
    for (unsigned i = 0; i < enabledBillboards; ++i)
    {
        Billboard& billboard = *sortedBillboards_[i];
        if (!billboard.enabled_)
            continue;
        
        Vector3 position;
        if (!relative_)
            position = billboard.position_;
        else
            position = worldTransform * billboard.position_;
        
        Vector2 size;
        if (!scaled_)
            size = billboard.size_;
        else
            size = Vector2(billboard.size_.x_ * worldScale.x_, billboard.size_.y_ * worldScale.y_);
        
        unsigned color = billboard.color_.ToUInt();
        
        float rotationMatrix[2][2];
        float angleRad = billboard.rotation_ * M_DEGTORAD;
        rotationMatrix[0][0] = cosf(angleRad);
        rotationMatrix[0][1] = sinf(angleRad);
        rotationMatrix[1][0] = -rotationMatrix[0][1];
        rotationMatrix[1][1] = rotationMatrix[0][0];
        
        *dest++ = position.x_; *dest++ = position.y_; *dest++ = position.z_;
        *((unsigned*)dest) = color; dest++;
        *dest++ = billboard.uv_.min_.x_; *dest++ = billboard.uv_.max_.y_;
        *dest++ = -size.x_ * rotationMatrix[0][0] + size.y_ * rotationMatrix[0][1];
        *dest++ = -size.x_ * rotationMatrix[1][0] + size.y_ * rotationMatrix[1][1];
        
        *dest++ = position.x_; *dest++ = position.y_; *dest++ = position.z_;
        *((unsigned*)dest) = color; dest++;
        *dest++ = billboard.uv_.max_.x_; *dest++ = billboard.uv_.max_.y_;
        *dest++ = size.x_ * rotationMatrix[0][0] + size.y_ * rotationMatrix[0][1];
        *dest++ = size.x_ * rotationMatrix[1][0] + size.y_ * rotationMatrix[1][1];
        
        *dest++ = position.x_; *dest++ = position.y_; *dest++ = position.z_;
        *((unsigned*)dest) = color; dest++;
        *dest++ = billboard.uv_.max_.x_; *dest++ = billboard.uv_.min_.y_;
        *dest++ = size.x_ * rotationMatrix[0][0] - size.y_ * rotationMatrix[0][1];
        *dest++ = size.x_ * rotationMatrix[1][0] - size.y_ * rotationMatrix[1][1];
        
        *dest++ = position.x_; *dest++ = position.y_; *dest++ = position.z_;
        *((unsigned*)dest) = color; dest++;
        *dest++ = billboard.uv_.min_.x_; *dest++ = billboard.uv_.min_.y_;
        *dest++ = -size.x_ * rotationMatrix[0][0] - size.y_ * rotationMatrix[0][1];
        *dest++ = -size.x_ * rotationMatrix[1][0] - size.y_ * rotationMatrix[1][1];
    }
    
    vertexBuffer_->Unlock();
}

void BillboardSet::MarkPositionsDirty()
{
    Drawable::OnMarkedDirty(node_);
    bufferDirty_ = true;
}
