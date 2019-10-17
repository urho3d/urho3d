//
// Copyright (c) 2008-2019 the Urho3D project.
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
#include "../Graphics/Texture2D.h"
#include "../Resource/ResourceCache.h"
#include "../UI/BorderImage.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* blendModeNames[];
extern const char* UI_CATEGORY;

BorderImage::BorderImage(Context* context) :
    UIElement(context),
    imageRect_(IntRect::ZERO),
    border_(IntRect::ZERO),
    imageBorder_(IntRect::ZERO),
    hoverOffset_(IntVector2::ZERO),
    disabledOffset_(IntVector2::ZERO),
    rotate_(0),
    flipH_(false),
    flipV_(false),
    blendMode_(BLEND_REPLACE),
    tiled_(false)
{
}

BorderImage::~BorderImage() = default;

void BorderImage::RegisterObject(Context* context)
{
    context->RegisterFactory<BorderImage>(UI_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Texture", GetTextureAttr, SetTextureAttr, ResourceRef, ResourceRef(Texture2D::GetTypeStatic()),
        AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Image Rect", GetImageRect, SetImageRect, IntRect, IntRect::ZERO, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Border", GetBorder, SetBorder, IntRect, IntRect::ZERO, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Image Border", GetImageBorder, SetImageBorder, IntRect, IntRect::ZERO, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Hover Image Offset", GetHoverOffset, SetHoverOffset, IntVector2, IntVector2::ZERO, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Disabled Image Offset", GetDisabledOffset, SetDisabledOffset, IntVector2, IntVector2::ZERO, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Tiled", IsTiled, SetTiled, bool, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Rotate", GetRotate, SetRotate, bool, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("FlipH", GetFlipH, SetFlipH, bool, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("FlipV", GetFlipV, SetFlipV, bool, false, AM_FILE);
    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Blend Mode", GetBlendMode, SetBlendMode, BlendMode, blendModeNames, 0, AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()),
        AM_FILE);
}

void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    if (enabled_)
        GetBatches(batches, vertexData, currentScissor, (hovering_ || selected_ || HasFocus()) ? hoverOffset_ : IntVector2::ZERO);
    else
        GetBatches(batches, vertexData, currentScissor, disabledOffset_);
}

void BorderImage::SetTexture(Texture* texture)
{
    texture_ = texture;
    if (imageRect_ == IntRect::ZERO)
        SetFullImageRect();
}

void BorderImage::SetImageRect(const IntRect& rect)
{
    if (rect != IntRect::ZERO)
        imageRect_ = rect;
}

void BorderImage::SetFullImageRect()
{
    if (texture_)
        SetImageRect(IntRect(0, 0, texture_->GetWidth(), texture_->GetHeight()));
}

void BorderImage::SetBorder(const IntRect& rect)
{
    border_.left_ = Max(rect.left_, 0);
    border_.top_ = Max(rect.top_, 0);
    border_.right_ = Max(rect.right_, 0);
    border_.bottom_ = Max(rect.bottom_, 0);
}

void BorderImage::SetImageBorder(const IntRect& rect)
{
    imageBorder_.left_ = Max(rect.left_, 0);
    imageBorder_.top_ = Max(rect.top_, 0);
    imageBorder_.right_ = Max(rect.right_, 0);
    imageBorder_.bottom_ = Max(rect.bottom_, 0);
}

void BorderImage::SetHoverOffset(const IntVector2& offset)
{
    hoverOffset_ = offset;
}

void BorderImage::SetHoverOffset(int x, int y)
{
    hoverOffset_ = IntVector2(x, y);
}

void BorderImage::SetDisabledOffset(const IntVector2& offset)
{
    disabledOffset_ = offset;
}

void BorderImage::SetDisabledOffset(int x, int y)
{
    disabledOffset_ = IntVector2(x, y);
}

void BorderImage::SetRotate(bool rotate)
{
    rotate_ = rotate;
}

void BorderImage::SetFlipH(bool flip)
{
    flipH_ = flip;
}

void BorderImage::SetFlipV(bool flip)
{
    flipV_ = flip;
}

void BorderImage::SetBlendMode(BlendMode mode)
{
    blendMode_ = mode;
}

void BorderImage::SetTiled(bool enable)
{
    tiled_ = enable;
}

void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor,
    const IntVector2& offset)
{
    bool allOpaque = true;
    if (GetDerivedOpacity() < 1.0f || colors_[C_TOPLEFT].a_ < 1.0f || colors_[C_TOPRIGHT].a_ < 1.0f ||
        colors_[C_BOTTOMLEFT].a_ < 1.0f || colors_[C_BOTTOMRIGHT].a_ < 1.0f)
        allOpaque = false;

    UIBatch
        batch(this, blendMode_ == BLEND_REPLACE && !allOpaque ? BLEND_ALPHA : blendMode_, currentScissor, texture_, &vertexData);

    if (material_)
        batch.custom_material_ = material_;

    // Calculate size of the inner rect, and texture dimensions of the inner rect
    const IntRect& uvBorder = (imageBorder_ == IntRect::ZERO) ? border_ : imageBorder_;
    int x = GetIndentWidth();
    IntVector2 size = GetSize();
    size.x_ -= x;
    IntVector2 innerSize(
        Max(size.x_ - border_.left_ - border_.right_, 0),
        Max(size.y_ - border_.top_ - border_.bottom_, 0));
    IntVector2 innerUvSize(
        Max(imageRect_.right_ - imageRect_.left_ - uvBorder.left_ - uvBorder.right_, 0),
        Max(imageRect_.bottom_ - imageRect_.top_ - uvBorder.top_ - uvBorder.bottom_, 0));

    IntVector2 uvTopLeft(imageRect_.left_, imageRect_.top_);
    uvTopLeft += offset;

    // Top
    if (border_.top_)
    {
        if (border_.left_)
            batch.AddQuad(x, 0, border_.left_, border_.top_, uvTopLeft.x_, uvTopLeft.y_, uvBorder.left_, uvBorder.top_);
        if (innerSize.x_)
            batch.AddQuad(x + border_.left_, 0, innerSize.x_, border_.top_, uvTopLeft.x_ + uvBorder.left_, uvTopLeft.y_,
                innerUvSize.x_, uvBorder.top_, tiled_);
        if (border_.right_)
            batch.AddQuad(x + border_.left_ + innerSize.x_, 0, border_.right_, border_.top_,
                uvTopLeft.x_ + uvBorder.left_ + innerUvSize.x_, uvTopLeft.y_, uvBorder.right_, uvBorder.top_);
    }
    // Middle
    if (innerSize.y_)
    {
        if (border_.left_)
            batch.AddQuad(x, border_.top_, border_.left_, innerSize.y_, uvTopLeft.x_, uvTopLeft.y_ + uvBorder.top_,
                uvBorder.left_, innerUvSize.y_, tiled_);
        if (innerSize.x_)
            batch.AddQuad(x + border_.left_, border_.top_, innerSize.x_, innerSize.y_, uvTopLeft.x_ + uvBorder.left_,
                uvTopLeft.y_ + uvBorder.top_, innerUvSize.x_, innerUvSize.y_, tiled_);
        if (border_.right_)
            batch.AddQuad(x + border_.left_ + innerSize.x_, border_.top_, border_.right_, innerSize.y_,
                uvTopLeft.x_ + uvBorder.left_ + innerUvSize.x_, uvTopLeft.y_ + uvBorder.top_, uvBorder.right_, innerUvSize.y_,
                tiled_);
    }
    // Bottom
    if (border_.bottom_)
    {
        if (border_.left_)
            batch.AddQuad(x, border_.top_ + innerSize.y_, border_.left_, border_.bottom_, uvTopLeft.x_,
                uvTopLeft.y_ + uvBorder.top_ + innerUvSize.y_, uvBorder.left_, uvBorder.bottom_);
        if (innerSize.x_)
            batch.AddQuad(x + border_.left_, border_.top_ + innerSize.y_, innerSize.x_, border_.bottom_,
                uvTopLeft.x_ + uvBorder.left_, uvTopLeft.y_ + uvBorder.top_ + innerUvSize.y_, innerUvSize.x_, uvBorder.bottom_,
                tiled_);
        if (border_.right_)
            batch.AddQuad(x + border_.left_ + innerSize.x_, border_.top_ + innerSize.y_, border_.right_, border_.bottom_,
                uvTopLeft.x_ + uvBorder.left_ + innerUvSize.x_, uvTopLeft.y_ + uvBorder.top_ + innerUvSize.y_, uvBorder.right_,
                uvBorder.bottom_);
    }

    if(rotate_ || flipH_ || flipV_)
    {
        IntRect localRect = imageRect_;
        localRect.left_ += offset.x_;
        localRect.right_ += offset.x_;
        localRect.top_ += offset.y_;
        localRect.bottom_ += offset.y_;
        batch.TransformUV(rotate_, flipH_, flipV_, localRect);
    }

    UIBatch::AddOrMerge(batch, batches);

    // Reset hovering for next frame
    hovering_ = false;
}

void BorderImage::SetTextureAttr(const ResourceRef& value)
{
    auto* cache = GetSubsystem<ResourceCache>();
    SetTexture(cache->GetResource<Texture2D>(value.name_));
}

ResourceRef BorderImage::GetTextureAttr() const
{
    return GetResourceRef(texture_, Texture2D::GetTypeStatic());
}

void BorderImage::SetMaterialAttr(const ResourceRef& value)
{
    auto* cache = GetSubsystem<ResourceCache>();
    SetMaterial(cache->GetResource<Material>(value.name_));
}

ResourceRef BorderImage::GetMaterialAttr() const
{
    return GetResourceRef(material_, Material::GetTypeStatic());
}

void BorderImage::SetMaterial(Material* material)
{
    material_ = material;
}

Material* BorderImage::GetMaterial() const
{
    return material_;
}

}
