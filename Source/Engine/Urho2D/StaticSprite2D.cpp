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
#include "Context.h"
#include "Scene.h"
#include "Sprite2D.h"
#include "StaticSprite2D.h"
#include "Texture2D.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* URHO2D_CATEGORY;

StaticSprite2D::StaticSprite2D(Context* context) :
    Drawable2D(context),
    flipX_(false),
    flipY_(false),
    color_(Color::WHITE)
{
    vertices_.Reserve(6);
}

StaticSprite2D::~StaticSprite2D()
{
}

void StaticSprite2D::RegisterObject(Context* context)
{
    context->RegisterFactory<StaticSprite2D>(URHO2D_CATEGORY);
    ACCESSOR_ATTRIBUTE(StaticSprite2D, VAR_BOOL, "Flip X", GetFlipX, SetFlipX, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(StaticSprite2D, VAR_BOOL, "Flip Y", GetFlipY, SetFlipY, bool, false, AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(StaticSprite2D, VAR_COLOR, "Color", GetColor, SetColor, Color, Color::WHITE, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(StaticSprite2D, Drawable2D);
}

void StaticSprite2D::SetFlip(bool flipX, bool flipY)
{
    if (flipX_ == flipX && flipY_ == flipY)
        return;

    flipX_ = flipX;
    flipY_ = flipY;
    // Assume flipping does not invalidate bounding box
    MarkDirty(false);
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
    MarkDirty(false);
    MarkNetworkUpdate();
}

void StaticSprite2D::UpdateVertices()
{
    if (!verticesDirty_)
        return;

    Scene* scene = GetScene();
    if (!scene)
        return;

    vertices_.Clear();

    if (!sprite_)
        return;

    Texture2D* texture = sprite_->GetTexture();
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

    float pixelsPerUnit = scene->GetPixelsPerUnit();
    float width = (float)rectangle_.Width() / pixelsPerUnit;     // Compute width and height in pixels
    float height = (float)rectangle_.Height() / pixelsPerUnit;

    const Vector2& hotSpot = sprite_->GetHotSpot();
    float hotSpotX = flipX_ ? (1.0f - hotSpot.x_) : hotSpot.x_;
    float hotSpotY = flipY_ ? (1.0f - hotSpot.y_) : hotSpot.y_;

    float leftX = -width * hotSpotX;
    float rightX = width * (1.0f - hotSpotX);
    float bottomY = -height * hotSpotY;
    float topY = height * (1.0f - hotSpotY);
    vertex0.position_ = Vector3(leftX, bottomY, zValue_);
    vertex1.position_ = Vector3(leftX, topY, zValue_);
    vertex2.position_ = Vector3(rightX, topY, zValue_);
    vertex3.position_ = Vector3(rightX, bottomY, zValue_);

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

    geometryDirty_ = true;
    verticesDirty_ = false;
}

}
