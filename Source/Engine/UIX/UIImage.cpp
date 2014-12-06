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
#include "DebugRenderer.h"
#include "Log.h"
#include "Node.h"
#include "Sprite2D.h"
#include "Texture2D.h"
#include "UIImage.h"
#include "UIRect.h"
#include "UIXEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* UIX_CATEGORY;

static const char* uiImageDrawModes[] = 
{
    "Simple",
    "Tiled",
    "Sliced",
    "Filled",
    0
};

static const char* uiFillTypes[] = 
{
    "Horizontal",
    "Vertical",
    "Radial",
    0
};

UIImage::UIImage(Context* context) :
    Drawable2D(context),
    color_(Color::WHITE),
    drawMode_(UIIDM_SIMPLE),
    xSliceSize_(4),
    ySliceSize_(4),
    fillType_(UIFT_HORIZONTAL),
    fillAmount_(1.0f),
    fillInverse_(false)
{
}

UIImage::~UIImage()
{
}

void UIImage::RegisterObject(Context* context)
{
    context->RegisterFactory<UIImage>(UIX_CATEGORY);

    ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    MIXED_ACCESSOR_ATTRIBUTE("Sprite", GetSpriteAttr, SetSpriteAttr, ResourceRef, ResourceRef(Sprite2D::GetTypeStatic()), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Color", GetColor, SetColor, Color, Color::WHITE, AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE("Draw Mode", GetDrawMode, SetDrawMode, UIImageDrawMode, uiImageDrawModes, UIIDM_SIMPLE, AM_FILE);
    ACCESSOR_ATTRIBUTE("X Slice Size", GetXSliceSize, SetXSliceSize, int, 4, AM_FILE);
    ACCESSOR_ATTRIBUTE("Y Slice Size", GetYSliceSize, SetYSliceSize, int, 4, AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE("Fill Type", GetFillType, SetFillType, UIFillType, uiFillTypes, UIFT_HORIZONTAL, AM_FILE);
    ACCESSOR_ATTRIBUTE("Fill Amount", GetFillAmount, SetFillAmount, float, 1.0f, AM_FILE);
    ACCESSOR_ATTRIBUTE("Fill Inverse", IsFillInverse, SetFillInverse, bool, false, AM_FILE);
    COPY_BASE_ATTRIBUTES(Drawable2D);
}

void UIImage::SetSprite(Sprite2D* sprite)
{
    if (sprite == sprite_)
        return;

    sprite_ = sprite;

    SetTexture(sprite_ ? sprite_->GetTexture() : 0);
}

void UIImage::SetColor(const Color& color)
{
    if (color == color_)
        return;

    color_ = color;

    verticesDirty_ = true;
}

void UIImage::SetDrawMode(UIImageDrawMode mode)
{
    if (mode == drawMode_)
        return;

    drawMode_ = mode;
    verticesDirty_ = true;
}

void UIImage::SetXSliceSize(int size)
{
    if (size < 0 || size == xSliceSize_)
        return;

    xSliceSize_ = size;

    if (drawMode_ == UIIDM_SLICED)
        verticesDirty_ = true;
}

void UIImage::SetYSliceSize(int size)
{
    if (size < 0 || size == ySliceSize_)
        return;

    ySliceSize_ = size;

    if (drawMode_ == UIIDM_SLICED)
        verticesDirty_ = true;
}

void UIImage::SetFillType(UIFillType fillType)
{
    if (fillType == fillType_)
        return;

    fillType_ = fillType;

    if (drawMode_ == UIIDM_FILLED)
        verticesDirty_ = true;
}

void UIImage::SetFillAmount(float amount)
{
    amount = Clamp(amount, 0.0f, 1.0f);

    if (amount == fillAmount_)
        return;

    fillAmount_ = amount;

    if (drawMode_ == UIIDM_FILLED)
        verticesDirty_ = true;
}

void UIImage::SetFillInverse(bool inverse)
{
    if (inverse == fillInverse_)
        return;

    fillInverse_ = inverse;

    if (drawMode_ == UIIDM_FILLED)
        verticesDirty_ = true;
}

Sprite2D* UIImage::GetSprite() const
{
    return sprite_;
}

void UIImage::SetSpriteAttr(const ResourceRef& value)
{
    Sprite2D* sprite = Sprite2D::LoadFromResourceRef(this, value);
    if (sprite)
        SetSprite(sprite);
}

ResourceRef UIImage::GetSpriteAttr() const
{
    return Sprite2D::SaveToResourceRef(sprite_);
}

void UIImage::OnNodeSet(Node* node)
{
    Drawable2D::OnNodeSet(node);

    if (node)
    {
        uiRect_ = node->GetComponent<UIRect>();
        if (uiRect_)
            SubscribeToEvent(uiRect_, E_UIRECTDIRTIED, HANDLER(UIImage, HandleRectDirtied));
        else
            LOGERROR("UIRect must by added first");
    }
}

void UIImage::OnWorldBoundingBoxUpdate()
{
    boundingBox_.Clear();

    if (uiRect_)
    {
        const Rect& rect = uiRect_->GetRect();
        boundingBox_.Merge(rect.min_);
        boundingBox_.Merge(rect.max_);
    }

    worldBoundingBox_ = boundingBox_;
}

void UIImage::UpdateVertices()
{
    if (!verticesDirty_)
        return;

    vertices_.Clear();

    if (!uiRect_)
        return;

    if (!texture_ || !sprite_)
        return;

    const IntRect& rect = sprite_->GetRectangle();
    if (rect.Width() == 0 || rect.Height() == 0)
        return;

    switch (drawMode_)
    {
    case UIIDM_SIMPLE:
        UpdateVerticesSimpleMode();
        break;
    case UIIDM_TILED:
        UpdateVerticesTiledMode();
        break;
    case UIIDM_SLICED:
        UpdateVerticesSlicedMode();
        break;
        case UIIDM_FILLED:
        UpdateVerticesFilledMode();
        break;
    }

    verticesDirty_ = false;
}

void UIImage::UpdateVerticesSimpleMode()
{
    float x = uiRect_->GetX();
    float y = uiRect_->GetY();

    const IntRect& intRect = sprite_->GetRectangle();
    float halfWidth = (float)intRect.Width() * PIXEL_SIZE * 0.5f;
    float halfHeight = (float)intRect.Height() * PIXEL_SIZE * 0.5f;

    float left = x - halfWidth;
    float right = x + halfWidth;
    float top = y + halfHeight;
    float bottom = y - halfHeight;
    
    float uLeft, uRight, vTop, vBottom;
    GetSpriteTextureCoords(uLeft, uRight, vTop, vBottom);

    AddQuad(left, right, top, bottom, uLeft, uRight, vTop, vBottom);
}

void UIImage::UpdateVerticesTiledMode()
{
    const Rect& rect = uiRect_->GetRect();
    float xStart = rect.min_.x_;
    float xEnd = rect.max_.x_;
    float yStart = rect.min_.y_;
    float yEnd = rect.max_.y_;

    const IntRect& intRect = sprite_->GetRectangle();
    float tileWidth = intRect.Width() * PIXEL_SIZE;
    float tileHeight = intRect.Height() * PIXEL_SIZE;

    float uLeft, uRight, vTop, vBottom;
    GetSpriteTextureCoords(uLeft, uRight, vTop, vBottom);

    for (float left = xStart; left < xEnd; left += tileWidth)
    {
        for (float top = yEnd; top > yStart; top -= tileHeight)
        {
            float right = left + tileWidth;
            float bottom = top - tileHeight;

            float uRight2 = uRight;
            float vBottom2 = vBottom;

            if (right > xEnd)
            {
                right = xEnd;
                uRight2 = uLeft + (right - left) / tileWidth * (uRight - uLeft);
            }

            if (bottom < yStart)
            {
                bottom = yStart;
                vBottom2 = vTop - (top - bottom) / tileHeight * (vTop - vBottom);
            }

            AddQuad(left, right, top, bottom, uLeft, uRight2, vTop, vBottom2);
        }
    }
}

void UIImage::UpdateVerticesSlicedMode()
{
    if (xSliceSize_ == 0 && ySliceSize_ == 0)
    {
        float left = uiRect_->GetLeft();
        float right = uiRect_->GetRight();
        float top = uiRect_->GetTop();
        float bottom = uiRect_->GetBottom();

        float uLeft, uRight, vTop, vBottom;
        GetSpriteTextureCoords(uLeft, uRight, vTop, vBottom);

        AddQuad(left, right, top, bottom, uLeft, uRight, vTop, vBottom);
        return;
    }

    const IntRect& intRect = sprite_->GetRectangle();
    int xSliceSize = Min(xSliceSize_, intRect.Width() / 2);
    int ySliceSize = Min(ySliceSize_, intRect.Height() / 2);

    float left = uiRect_->GetLeft();
    float right = uiRect_->GetRight();
    float top = uiRect_->GetTop();
    float bottom = uiRect_->GetBottom();

    float xDelta = (float)xSliceSize * PIXEL_SIZE;
    float yDelta = (float)ySliceSize * PIXEL_SIZE;

    float uLeft, uRight, vTop, vBottom;
    GetSpriteTextureCoords(uLeft, uRight, vTop, vBottom);

    float uDelta = (float)xSliceSize / (float)texture_->GetWidth();
    float vDelta = (float)ySliceSize / (float)texture_->GetHeight();

    float x1 = left + xDelta;
    float x2 = right - xDelta;
    float y1 = top - yDelta;
    float y2 = bottom + yDelta;

    float u1 = uLeft + uDelta;
    float u2 = uRight - uDelta;
    float v1 = vTop + vDelta;
    float v2 = vBottom - vDelta;

    AddQuad(left, x1   , top, y1, uLeft, u1    , vTop, v1);
    AddQuad(x1  , x2   , top, y1, u1   , u2    , vTop, v1);
    AddQuad(x2  , right, top, y1, u2   , uRight, vTop, v1);

    AddQuad(left, x1   , y1, y2, uLeft, u1    , v1, v2);
    AddQuad(x1  , x2   , y1, y2, u1   , u2    , v1, v2);
    AddQuad(x2  , right, y1, y2, u2   , uRight, v1, v2);

    AddQuad(left, x1   , y2, bottom, uLeft, u1    , v2, vBottom);
    AddQuad(x1  , x2   , y2, bottom, u1   , u2    , v2, vBottom);
    AddQuad(x2  , right, y2, bottom, u2   , uRight, v2, vBottom);
}

void UIImage::UpdateVerticesFilledMode()
{
    if (fillType_ != UIFT_RADIAL)
    {
        float left = uiRect_->GetLeft();
        float right = uiRect_->GetRight();
        float top = uiRect_->GetTop();
        float bottom = uiRect_->GetBottom();

        float uLeft, uRight, vTop, vBottom;
        GetSpriteTextureCoords(uLeft, uRight, vTop, vBottom);

        if (fillType_ == UIFT_HORIZONTAL)
        {
            if (!fillInverse_)
            {
                right = left + (right - left) * fillAmount_;
                uRight = uLeft + (uRight - uLeft) * fillAmount_;
            }
            else
            {
                left = right - (right - left) * fillAmount_;
                uLeft = uRight - (uRight - uLeft) * fillAmount_;
            }
        }
        else
        {
            if (!fillInverse_)
            {
                top = bottom + (top - bottom) * fillAmount_;
                vTop = vBottom + (vTop - vBottom) * fillAmount_;
            }
            else
            {
                bottom = top - (top - bottom) * fillAmount_;
                vBottom = vTop - (vTop - vBottom) * fillAmount_;
            }
        }
        AddQuad(left, right, top, bottom, uLeft, uRight, vTop, vBottom);
    }
    else
        UpdateVerticesFilledModeRadial();
}

void UIImage::UpdateVerticesFilledModeRadial()
{
    float x = uiRect_->GetX();
    float y = uiRect_->GetY();
    float left = uiRect_->GetLeft();
    float right = uiRect_->GetRight();
    float top = uiRect_->GetTop();
    float bottom = uiRect_->GetBottom();

    unsigned color = color_.ToUInt();

    float uLeft, uRight, vTop, vBottom;
    GetSpriteTextureCoords(uLeft, uRight, vTop, vBottom);
    float u = (uLeft + uRight) * 0.5f;
    float v = (vTop + vBottom) * 0.5f;

    // 5----1----2
    // | \  |a1 /|
    // |  \ | /  |
    // |    0    | 
    // |  /   \  |
    // |/       \|
    // 4---------3
    Vertex2D vertices[6] = 
    {
        { Vector3(x    , y     ),  color, Vector2(u     , v      ) }, // 0
        { Vector3(x    , top   ),  color, Vector2(u     , vTop   ) }, // 1
        { Vector3(right, top   ),  color, Vector2(uRight, vTop   ) }, // 2
        { Vector3(right, bottom),  color, Vector2(uRight, vBottom) }, // 3
        { Vector3(left , bottom),  color, Vector2(uLeft , vBottom) }, // 4
        { Vector3(left , top   ),  color, Vector2(uLeft , vTop   ) }, // 5
    };

    float angle = 360.0f * fillAmount_;
    float width = uiRect_->GetWidth();
    float height = uiRect_->GetHeight();
    float angle1 = Atan2(width, height);

    if (angle <= angle1)
    {
        float x1 = height * 0.5f * Tan(angle);
        if (fillInverse_)
            x1 = x + x1;
        else
            x1 = x - x1;
        float u1 = uLeft + (uRight - uLeft) /  width * (x1 - left);
        Vertex2D vertex = {Vector3(x1, top), color, Vector2(u1, vTop) };
        vertices_.Push(vertices[0]);
        vertices_.Push(vertices[1]);
        vertices_.Push(vertex);
        vertices_.Push(vertex);
        return;
    }

    if (angle <= 180.0f - angle1)
    {
        float y1 = y + width * 0.5f * Tan(90.0f - angle);
        float v1 = vBottom + (vTop - vBottom) / height * (y1 - bottom);
        vertices_.Push(vertices[0]);
        vertices_.Push(vertices[1]);
        if (fillInverse_)
        {
            Vertex2D vertex = { Vector3(right, y1), color, Vector2(uRight, v1) };
            vertices_.Push(vertices[2]);
            vertices_.Push(vertex);
        }
        else
        {
            Vertex2D vertex = { Vector3(left, y1), color, Vector2(uLeft, v1) };
            vertices_.Push(vertices[5]);
            vertices_.Push(vertex);
        }
        return;
    }
    
    vertices_.Push(vertices[0]);
    vertices_.Push(vertices[1]);
    if (fillInverse_)
    {
        vertices_.Push(vertices[2]);
        vertices_.Push(vertices[3]);
    }
    else
    {
        vertices_.Push(vertices[5]);
        vertices_.Push(vertices[4]);
    }

    if (angle <= 180.0f + angle1)
    {
        float x1 = height * 0.5f * Tan(180.0f - angle);
        if (fillInverse_)
            x1 = x + x1;
        else
            x1 = x - x1;
        float u1 = uLeft + (uRight - uLeft) /  width * (x1 - left);
        Vertex2D vertex = { Vector3(x1, bottom), color, Vector2(u1, vBottom) };
        vertices_.Push(vertices[0]);
        if (fillInverse_)
            vertices_.Push(vertices[3]);
        else
            vertices_.Push(vertices[4]);
        vertices_.Push(vertex);
        vertices_.Push(vertex);
        return;
    }

    if (angle <= 360.0f - angle1)
    {
        float y1 = y + width * 0.5f * Tan(angle - 270.0f);
        float v1 = vBottom + (vTop - vBottom) / height * (y1 - bottom);
        if (fillInverse_)
        {
            Vertex2D vertex = { Vector3(left, y1), color, Vector2(uLeft, v1) };
            vertices_.Push(vertices[0]);
            vertices_.Push(vertices[3]);
            vertices_.Push(vertices[4]);
            vertices_.Push(vertex);
        }
        else
        {
            Vertex2D vertex = { Vector3(right, y1), color, Vector2(uRight, v1) };
            vertices_.Push(vertices[0]);
            vertices_.Push(vertices[4]);
            vertices_.Push(vertices[3]);
            vertices_.Push(vertex);
        }
        return;
    }

    if (fillInverse_)
    {
        vertices_.Push(vertices[0]);
        vertices_.Push(vertices[3]);
        vertices_.Push(vertices[4]);
        vertices_.Push(vertices[5]);
    }
    else
    {
        vertices_.Push(vertices[0]);
        vertices_.Push(vertices[4]);
        vertices_.Push(vertices[3]);        
        vertices_.Push(vertices[2]);
    }

    float x1 = height * 0.5f * Tan(angle - 360.0f);
    if (fillInverse_)
        x1 = x + x1;
    else
        x1 = x - x1;
    float u1 = uLeft + (uRight - uLeft) /  width * (x1 - left);
    Vertex2D vertex = { Vector3(x1, top), color, Vector2(u1, vTop) };
    vertices_.Push(vertices[0]);
    if (fillInverse_)
        vertices_.Push(vertices[5]);
    else
        vertices_.Push(vertices[2]);
    vertices_.Push(vertex);
    vertices_.Push(vertex);
}

void UIImage::GetSpriteTextureCoords(float& left, float& right, float& top, float& bottom) const
{ 
    Texture2D* texture = GetTexture();
    float invTexW = 1.0f / (float)texture->GetWidth();
    float invTexH = 1.0f / (float)texture->GetHeight();

    const IntRect& intRect = sprite_->GetRectangle();
    left = (float)intRect.left_ * invTexW;
    right = (float)intRect.right_ * invTexW;
    top = (float)intRect.top_ * invTexH;
    bottom = (float)intRect.bottom_ * invTexH;
}

void UIImage::AddQuad(float left, float right, float top, float bottom, float uLeft, float uRight, float vTop, float vBottom)
{
    if (right - left <= 0.005f || top - bottom <= 0.005f)
        return;

    
    // V1---------V2
    // |         / |
    // |       /   |
    // |     /     |
    // |   /       |
    // | /         |
    // V0---------V3
    Vertex2D vertex0;
    Vertex2D vertex1;
    Vertex2D vertex2;
    Vertex2D vertex3;

    vertex0.position_ = Vector3(left, bottom);
    vertex1.position_ = Vector3(left, top);
    vertex2.position_ = Vector3(right, top);
    vertex3.position_ = Vector3(right, bottom);

    vertex0.uv_ = Vector2(uLeft, vBottom);
    vertex1.uv_ = Vector2(uLeft, vTop);
    vertex2.uv_ = Vector2(uRight, vTop);
    vertex3.uv_ = Vector2(uRight, vBottom);

    vertex0.color_ = vertex1.color_ = vertex2.color_  = vertex3.color_ = color_.ToUInt();

    vertices_.Push(vertex0);
    vertices_.Push(vertex1);
    vertices_.Push(vertex2);
    vertices_.Push(vertex3);
}

void UIImage::HandleRectDirtied(StringHash eventType, VariantMap& eventData)
{
    worldBoundingBoxDirty_ = true;
    verticesDirty_ = true;
}

}
