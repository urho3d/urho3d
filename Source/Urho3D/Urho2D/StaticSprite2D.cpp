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
#include "../Graphics/Material.h"
#include "../Graphics/Texture2D.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Scene.h"
#include "../Urho2D/Renderer2D.h"
#include "../Urho2D/Sprite2D.h"
#include "../Urho2D/StaticSprite2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;
extern const char* blendModeNames[];

StaticSprite2D::StaticSprite2D(Context* context) :
    Drawable2D(context),
    blendMode_(BLEND_ALPHA),
    flipX_(false),
    flipY_(false),
    color_(Color::WHITE),
    useHotSpot_(false),
    hotSpot_(0.5f, 0.5f)
{
    sourceBatches_.Resize(1);
}

StaticSprite2D::~StaticSprite2D()
{
}

void StaticSprite2D::RegisterObject(Context* context)
{
    context->RegisterFactory<StaticSprite2D>(URHO2D_CATEGORY);

    ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(Drawable2D);
    MIXED_ACCESSOR_ATTRIBUTE("Sprite", GetSpriteAttr, SetSpriteAttr, ResourceRef, ResourceRef(Sprite2D::GetTypeStatic()),
        AM_DEFAULT);
    ENUM_ACCESSOR_ATTRIBUTE("Blend Mode", GetBlendMode, SetBlendMode, BlendMode, blendModeNames, BLEND_ALPHA, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Flip X", GetFlipX, SetFlipX, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Flip Y", GetFlipY, SetFlipY, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Color", GetColor, SetColor, Color, Color::WHITE, AM_DEFAULT);
    MIXED_ACCESSOR_ATTRIBUTE("Custom material", GetCustomMaterialAttr, SetCustomMaterialAttr, ResourceRef,
        ResourceRef(Material::GetTypeStatic()), AM_DEFAULT);
}

void StaticSprite2D::SetSprite(Sprite2D* sprite)
{
    if (sprite == sprite_)
        return;

    sprite_ = sprite;
    UpdateMaterial();

    sourceBatchesDirty_ = true;
    MarkNetworkUpdate();
}

void StaticSprite2D::SetBlendMode(BlendMode blendMode)
{
    if (blendMode == blendMode_)
        return;

    blendMode_ = blendMode;

    UpdateMaterial();
    MarkNetworkUpdate();
}

void StaticSprite2D::SetFlip(bool flipX, bool flipY)
{
    if (flipX == flipX_ && flipY == flipY_)
        return;

    flipX_ = flipX;
    flipY_ = flipY;
    sourceBatchesDirty_ = true;

    OnFlipChanged();

    MarkNetworkUpdate();
}

void StaticSprite2D::SetFlipX(bool flipX)
{
    SetFlip(flipX, flipY_);
}

void StaticSprite2D::SetFlipY(bool flipY)
{
    SetFlip(flipX_, flipY);
}

void StaticSprite2D::SetColor(const Color& color)
{
    if (color == color_)
        return;

    color_ = color;
    sourceBatchesDirty_ = true;
    MarkNetworkUpdate();
}

void StaticSprite2D::SetAlpha(float alpha)
{
    if (alpha == color_.a_)
        return;

    color_.a_ = alpha;
    sourceBatchesDirty_ = true;
    MarkNetworkUpdate();
}

void StaticSprite2D::SetUseHotSpot(bool useHotSpot)
{
    if (useHotSpot == useHotSpot_)
        return;

    useHotSpot_ = useHotSpot;
    sourceBatchesDirty_ = true;
    MarkNetworkUpdate();
}

void StaticSprite2D::SetHotSpot(const Vector2& hotspot)
{
    if (hotspot == hotSpot_)
        return;

    hotSpot_ = hotspot;

    if (useHotSpot_)
    {
        sourceBatchesDirty_ = true;
        MarkNetworkUpdate();
    }
}

void StaticSprite2D::SetCustomMaterial(Material* customMaterial)
{
    if (customMaterial == customMaterial_)
        return;

    customMaterial_ = customMaterial;
    sourceBatchesDirty_ = true;

    UpdateMaterial();
    MarkNetworkUpdate();
}

Sprite2D* StaticSprite2D::GetSprite() const
{
    return sprite_;
}


Material* StaticSprite2D::GetCustomMaterial() const
{
    return customMaterial_;
}

void StaticSprite2D::SetSpriteAttr(const ResourceRef& value)
{
    Sprite2D* sprite = Sprite2D::LoadFromResourceRef(this, value);
    if (sprite)
        SetSprite(sprite);
}

ResourceRef StaticSprite2D::GetSpriteAttr() const
{
    return Sprite2D::SaveToResourceRef(sprite_);
}

void StaticSprite2D::SetCustomMaterialAttr(const ResourceRef& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetCustomMaterial(cache->GetResource<Material>(value.name_));
}

ResourceRef StaticSprite2D::GetCustomMaterialAttr() const
{
    return GetResourceRef(customMaterial_, Material::GetTypeStatic());
}

void StaticSprite2D::OnWorldBoundingBoxUpdate()
{
    boundingBox_.Clear();

    if (sprite_)
    {
        const IntRect& rectangle_ = sprite_->GetRectangle();
        float width = (float)rectangle_.Width() * PIXEL_SIZE;     // Compute width and height in pixels
        float height = (float)rectangle_.Height() * PIXEL_SIZE;

        const Vector2& hotSpot = sprite_->GetHotSpot();
        float hotSpotX = flipX_ ? (1.0f - hotSpot.x_) : hotSpot.x_;
        float hotSpotY = flipY_ ? (1.0f - hotSpot.y_) : hotSpot.y_;

        float leftX = -width * hotSpotX;
        float rightX = width * (1.0f - hotSpotX);
        float bottomY = -height * hotSpotY;
        float topY = height * (1.0f - hotSpotY);

        boundingBox_.Merge(Vector3(leftX, bottomY, 0.0f));
        boundingBox_.Merge(Vector3(rightX, topY, 0.0f));
    }

    worldBoundingBox_ = boundingBox_.Transformed(node_->GetWorldTransform());
}

void StaticSprite2D::OnDrawOrderChanged()
{
    sourceBatches_[0].drawOrder_ = GetDrawOrder();
}

void StaticSprite2D::UpdateSourceBatches()
{
    if (!sourceBatchesDirty_)
        return;

    Vector<Vertex2D>& vertices = sourceBatches_[0].vertices_;
    vertices.Clear();

    if (!sprite_)
        return;

    Rect drawRect;
    if (useHotSpot_)
    {
        if (!sprite_->GetDrawRectangle(drawRect, hotSpot_, flipX_, flipY_))
            return;
    }
    else
    {
        if (!sprite_->GetDrawRectangle(drawRect, flipX_, flipY_))
            return;
    }

    Rect textureRect;
    if (!sprite_->GetTextureRectangle(textureRect, flipX_, flipY_))
        return;

    /*
    V1---------V2
    |         / |
    |       /   |
    |     /     |
    |   /       |
    | /         |
    V0---------V3
    */
    Vertex2D vertex0;
    Vertex2D vertex1;
    Vertex2D vertex2;
    Vertex2D vertex3;

    // Convert to world space
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    vertex0.position_ = worldTransform * Vector3(drawRect.min_.x_, drawRect.min_.y_, 0.0f);
    vertex1.position_ = worldTransform * Vector3(drawRect.min_.x_, drawRect.max_.y_, 0.0f);
    vertex2.position_ = worldTransform * Vector3(drawRect.max_.x_, drawRect.max_.y_, 0.0f);
    vertex3.position_ = worldTransform * Vector3(drawRect.max_.x_, drawRect.min_.y_, 0.0f);

    vertex0.uv_ = textureRect.min_;
    vertex1.uv_ = Vector2(textureRect.min_.x_, textureRect.max_.y_);
    vertex2.uv_ = textureRect.max_;
    vertex3.uv_ = Vector2(textureRect.max_.x_, textureRect.min_.y_);

    vertex0.color_ = vertex1.color_ = vertex2.color_ = vertex3.color_ = color_.ToUInt();

    vertices.Push(vertex0);
    vertices.Push(vertex1);
    vertices.Push(vertex2);
    vertices.Push(vertex3);

    sourceBatchesDirty_ = false;
}

void StaticSprite2D::OnFlipChanged()
{

}

void StaticSprite2D::UpdateMaterial()
{
    if (customMaterial_)
        sourceBatches_[0].material_ = customMaterial_;
    else
    {
        if (sprite_)
            sourceBatches_[0].material_ = renderer_->GetMaterial(sprite_->GetTexture(), blendMode_);
        else
            sourceBatches_[0].material_ = 0;
    }
}

}
