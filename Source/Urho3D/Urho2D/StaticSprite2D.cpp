//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "../Core/Context.h"
#include "../Scene/Scene.h"
#include "../Urho2D/Sprite2D.h"
#include "../Urho2D/StaticSprite2D.h"
#include "../Graphics/Texture2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;

StaticSprite2D::StaticSprite2D(Context* context) :
    Drawable2D(context),
    flipX_(false),
    flipY_(false),
    color_(Color::WHITE),
    useHotSpot_(false),
    hotSpot_(0.5f, 0.5f)
{
    vertices_.Reserve(6);
}

StaticSprite2D::~StaticSprite2D()
{
}

void StaticSprite2D::RegisterObject(Context* context)
{
    context->RegisterFactory<StaticSprite2D>(URHO2D_CATEGORY);

    ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    MIXED_ACCESSOR_ATTRIBUTE("Sprite", GetSpriteAttr, SetSpriteAttr, ResourceRef, ResourceRef(Sprite2D::GetTypeStatic()), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Flip X", GetFlipX, SetFlipX, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Flip Y", GetFlipY, SetFlipY, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Color", GetColor, SetColor, Color, Color::WHITE, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(Drawable2D);
}

void StaticSprite2D::SetSprite(Sprite2D* sprite)
{
    if (sprite == sprite_)
        return;

    sprite_ = sprite;
    if (sprite)
        verticesDirty_ = true;


    SetTexture(sprite_ ? sprite_->GetTexture() : 0);
}

void StaticSprite2D::SetFlip(bool flipX, bool flipY)
{
    if (flipX == flipX_ && flipY == flipY_)
        return;

    flipX_ = flipX;
    flipY_ = flipY;
    verticesDirty_ = true;

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
    verticesDirty_ = true;
    MarkNetworkUpdate();
}

void StaticSprite2D::SetUseHotSpot(bool useHotSpot)
{
    if (useHotSpot == useHotSpot_)
        return;

    useHotSpot_ = useHotSpot;
    verticesDirty_ = true;
    MarkNetworkUpdate();
}

void StaticSprite2D::SetHotSpot(const Vector2& hotspot)
{
    if (hotspot == hotSpot_)
        return;

    hotSpot_ = hotspot;

    if (useHotSpot_)
    {
        verticesDirty_ = true;
        MarkNetworkUpdate();
    }
}

Sprite2D* StaticSprite2D::GetSprite() const
{
    return sprite_;
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

void StaticSprite2D::UpdateVertices()
{
    if (!verticesDirty_)
        return;

    vertices_.Clear();

    Texture2D* texture = GetTexture();
    if (!texture)
        return;

    const IntRect& rectangle_ = sprite_->GetRectangle();
    if (rectangle_.Width() == 0 || rectangle_.Height() == 0)
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

    float width = (float)rectangle_.Width() * PIXEL_SIZE;     // Compute width and height in pixels
    float height = (float)rectangle_.Height() * PIXEL_SIZE;

    float hotSpotX;
    float hotSpotY;

    if (useHotSpot_)
    {
        hotSpotX = flipX_ ? (1.0f - hotSpot_.x_) : hotSpot_.x_;
        hotSpotY = flipY_ ? (1.0f - hotSpot_.y_) : hotSpot_.y_;
    }
    else
    {
        const Vector2& hotSpot = sprite_->GetHotSpot();
        hotSpotX = flipX_ ? (1.0f - hotSpot.x_) : hotSpot.x_;
        hotSpotY = flipY_ ? (1.0f - hotSpot.y_) : hotSpot.y_;
    }

#ifdef URHO3D_OPENGL
    float leftX = -width * hotSpotX;
    float rightX = width * (1.0f - hotSpotX);
    float bottomY = -height * hotSpotY;
    float topY = height * (1.0f - hotSpotY);
#else
    const float halfPixelOffset = 0.5f * PIXEL_SIZE;
    float leftX = -width * hotSpotX + halfPixelOffset;
    float rightX = width * (1.0f - hotSpotX) + halfPixelOffset;
    float bottomY = -height * hotSpotY + halfPixelOffset;
    float topY = height * (1.0f - hotSpotY) + halfPixelOffset;
#endif

    const Matrix3x4& worldTransform = node_->GetWorldTransform();

    vertex0.position_ = worldTransform * Vector3(leftX, bottomY, 0.0f);
    vertex1.position_ = worldTransform * Vector3(leftX, topY, 0.0f);
    vertex2.position_ = worldTransform * Vector3(rightX, topY, 0.0f);
    vertex3.position_ = worldTransform * Vector3(rightX, bottomY, 0.0f);

    float invTexW = 1.0f / (float)texture->GetWidth();
    float invTexH = 1.0f / (float)texture->GetHeight();

    float leftU = rectangle_.left_ * invTexW;
    float rightU = rectangle_.right_ * invTexW;
    float topV = rectangle_.top_ * invTexH;
    float bottomV = rectangle_.bottom_ * invTexH;
    vertex0.uv_ = Vector2(leftU, bottomV);
    vertex1.uv_ = Vector2(leftU, topV);
    vertex2.uv_ = Vector2(rightU, topV);
    vertex3.uv_ = Vector2(rightU, bottomV);

    if (flipX_)
    {
        Swap(vertex0.uv_.x_, vertex3.uv_.x_);
        Swap(vertex1.uv_.x_, vertex2.uv_.x_);
    }
    
    if (flipY_)
    {
        Swap(vertex0.uv_.y_, vertex1.uv_.y_);
        Swap(vertex2.uv_.y_, vertex3.uv_.y_);
    }

    vertex0.color_ = vertex1.color_ = vertex2.color_  = vertex3.color_ = color_.ToUInt();

    vertices_.Push(vertex0);
    vertices_.Push(vertex1);
    vertices_.Push(vertex2);
    vertices_.Push(vertex3);

    verticesDirty_ = false;
}

void StaticSprite2D::OnFlipChanged()
{

}

}
