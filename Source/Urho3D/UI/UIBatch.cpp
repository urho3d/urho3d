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

#include "../Graphics/Graphics.h"
#include "../Graphics/Texture.h"
#include "../UI/UIElement.h"

#include "../DebugNew.h"

namespace Urho3D
{

Vector3 UIBatch::posAdjust(0.0f, 0.0f, 0.0f);

UIBatch::UIBatch()
{
    SetDefaultColor();
}

UIBatch::UIBatch(UIElement* element, BlendMode blendMode, const IntRect& scissor, Texture* texture, PODVector<float>* vertexData) :     // NOLINT(modernize-pass-by-value)
    element_(element),
    blendMode_(blendMode),
    scissor_(scissor),
    texture_(texture),
    invTextureSize_(texture ? Vector2(1.0f / (float)texture->GetWidth(), 1.0f / (float)texture->GetHeight()) : Vector2::ONE),
    vertexData_(vertexData),
    vertexStart_(vertexData->Size()),
    vertexEnd_(vertexData->Size())
{
    SetDefaultColor();
}

void UIBatch::SetColor(const Color& color, bool overrideAlpha)
{
    if (!element_)
        overrideAlpha = true;

    useGradient_ = false;
    color_ =
        overrideAlpha ? color.ToUInt() : Color(color.r_, color.g_, color.b_, color.a_ * element_->GetDerivedOpacity()).ToUInt();
}

void UIBatch::SetDefaultColor()
{
    if (element_)
    {
        color_ = element_->GetDerivedColor().ToUInt();
        useGradient_ = element_->HasColorGradient();
    }
    else
    {
        color_ = 0xffffffff;
        useGradient_ = false;
    }
}

void UIBatch::AddQuad(float x, float y, float width, float height, int texOffsetX, int texOffsetY, int texWidth, int texHeight)
{
    unsigned topLeftColor, topRightColor, bottomLeftColor, bottomRightColor;

    if (!useGradient_)
    {
        // If alpha is 0, nothing will be rendered, so do not add the quad
        if (!(color_ & 0xff000000))
            return;

        topLeftColor = color_;
        topRightColor = color_;
        bottomLeftColor = color_;
        bottomRightColor = color_;
    }
    else
    {
        topLeftColor = GetInterpolatedColor(x, y);
        topRightColor = GetInterpolatedColor(x + width, y);
        bottomLeftColor = GetInterpolatedColor(x, y + height);
        bottomRightColor = GetInterpolatedColor(x + width, y + height);
    }

    const IntVector2& screenPos = element_->GetScreenPosition();

    float left = x + screenPos.x_ - posAdjust.x_;
    float right = left + width;
    float top = y + screenPos.y_ - posAdjust.x_;
    float bottom = top + height;

    float leftUV = texOffsetX * invTextureSize_.x_;
    float topUV = texOffsetY * invTextureSize_.y_;
    float rightUV = (texOffsetX + (texWidth ? texWidth : width)) * invTextureSize_.x_;
    float bottomUV = (texOffsetY + (texHeight ? texHeight : height)) * invTextureSize_.y_;

    unsigned begin = vertexData_->Size();
    vertexData_->Resize(begin + 6 * UI_VERTEX_SIZE);
    float* dest = &(vertexData_->At(begin));
    vertexEnd_ = vertexData_->Size();

    dest[0] = left;
    dest[1] = top;
    dest[2] = 0.0f;
    ((unsigned&)dest[3]) = topLeftColor;
    dest[4] = leftUV;
    dest[5] = topUV;

    dest[6] = right;
    dest[7] = top;
    dest[8] = 0.0f;
    ((unsigned&)dest[9]) = topRightColor;
    dest[10] = rightUV;
    dest[11] = topUV;

    dest[12] = left;
    dest[13] = bottom;
    dest[14] = 0.0f;
    ((unsigned&)dest[15]) = bottomLeftColor;
    dest[16] = leftUV;
    dest[17] = bottomUV;

    dest[18] = right;
    dest[19] = top;
    dest[20] = 0.0f;
    ((unsigned&)dest[21]) = topRightColor;
    dest[22] = rightUV;
    dest[23] = topUV;

    dest[24] = right;
    dest[25] = bottom;
    dest[26] = 0.0f;
    ((unsigned&)dest[27]) = bottomRightColor;
    dest[28] = rightUV;
    dest[29] = bottomUV;

    dest[30] = left;
    dest[31] = bottom;
    dest[32] = 0.0f;
    ((unsigned&)dest[33]) = bottomLeftColor;
    dest[34] = leftUV;
    dest[35] = bottomUV;
}

void UIBatch::AddQuad(const Matrix3x4& transform, int x, int y, int width, int height, int texOffsetX, int texOffsetY,
    int texWidth, int texHeight)
{
    unsigned topLeftColor, topRightColor, bottomLeftColor, bottomRightColor;

    if (!useGradient_)
    {
        // If alpha is 0, nothing will be rendered, so do not add the quad
        if (!(color_ & 0xff000000))
            return;

        topLeftColor = color_;
        topRightColor = color_;
        bottomLeftColor = color_;
        bottomRightColor = color_;
    }
    else
    {
        topLeftColor = GetInterpolatedColor(x, y);
        topRightColor = GetInterpolatedColor(x + width, y);
        bottomLeftColor = GetInterpolatedColor(x, y + height);
        bottomRightColor = GetInterpolatedColor(x + width, y + height);
    }

    Vector3 v1 = (transform * Vector3((float)x, (float)y, 0.0f)) - posAdjust;
    Vector3 v2 = (transform * Vector3((float)x + (float)width, (float)y, 0.0f)) - posAdjust;
    Vector3 v3 = (transform * Vector3((float)x, (float)y + (float)height, 0.0f)) - posAdjust;
    Vector3 v4 = (transform * Vector3((float)x + (float)width, (float)y + (float)height, 0.0f)) - posAdjust;

    float leftUV = ((float)texOffsetX) * invTextureSize_.x_;
    float topUV = ((float)texOffsetY) * invTextureSize_.y_;
    float rightUV = ((float)(texOffsetX + (texWidth ? texWidth : width))) * invTextureSize_.x_;
    float bottomUV = ((float)(texOffsetY + (texHeight ? texHeight : height))) * invTextureSize_.y_;

    unsigned begin = vertexData_->Size();
    vertexData_->Resize(begin + 6 * UI_VERTEX_SIZE);
    float* dest = &(vertexData_->At(begin));
    vertexEnd_ = vertexData_->Size();

    dest[0] = v1.x_;
    dest[1] = v1.y_;
    dest[2] = 0.0f;
    ((unsigned&)dest[3]) = topLeftColor;
    dest[4] = leftUV;
    dest[5] = topUV;

    dest[6] = v2.x_;
    dest[7] = v2.y_;
    dest[8] = 0.0f;
    ((unsigned&)dest[9]) = topRightColor;
    dest[10] = rightUV;
    dest[11] = topUV;

    dest[12] = v3.x_;
    dest[13] = v3.y_;
    dest[14] = 0.0f;
    ((unsigned&)dest[15]) = bottomLeftColor;
    dest[16] = leftUV;
    dest[17] = bottomUV;

    dest[18] = v2.x_;
    dest[19] = v2.y_;
    dest[20] = 0.0f;
    ((unsigned&)dest[21]) = topRightColor;
    dest[22] = rightUV;
    dest[23] = topUV;

    dest[24] = v4.x_;
    dest[25] = v4.y_;
    dest[26] = 0.0f;
    ((unsigned&)dest[27]) = bottomRightColor;
    dest[28] = rightUV;
    dest[29] = bottomUV;

    dest[30] = v3.x_;
    dest[31] = v3.y_;
    dest[32] = 0.0f;
    ((unsigned&)dest[33]) = bottomLeftColor;
    dest[34] = leftUV;
    dest[35] = bottomUV;
}

void UIBatch::AddQuad(int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth, int texHeight, bool tiled)
{
    if (!(element_->HasColorGradient() || element_->GetDerivedColor().ToUInt() & 0xff000000))
        return; // No gradient and alpha is 0, so do not add the quad

    if (!tiled)
    {
        AddQuad(x, y, width, height, texOffsetX, texOffsetY, texWidth, texHeight);
        return;
    }

    int tileX = 0;
    int tileY = 0;
    int tileW = 0;
    int tileH = 0;

    while (tileY < height)
    {
        tileX = 0;
        tileH = Min(height - tileY, texHeight);

        while (tileX < width)
        {
            tileW = Min(width - tileX, texWidth);

            AddQuad(x + tileX, y + tileY, tileW, tileH, texOffsetX, texOffsetY, tileW, tileH);

            tileX += tileW;
        }

        tileY += tileH;
    }
}

void UIBatch::AddQuad(const Matrix3x4& transform, const IntVector2& a, const IntVector2& b, const IntVector2& c, const IntVector2& d,
    const IntVector2& texA, const IntVector2& texB, const IntVector2& texC, const IntVector2& texD)
{
    Vector3 v1 = (transform * Vector3((float)a.x_, (float)a.y_, 0.0f)) - posAdjust;
    Vector3 v2 = (transform * Vector3((float)b.x_, (float)b.y_, 0.0f)) - posAdjust;
    Vector3 v3 = (transform * Vector3((float)c.x_, (float)c.y_, 0.0f)) - posAdjust;
    Vector3 v4 = (transform * Vector3((float)d.x_, (float)d.y_, 0.0f)) - posAdjust;

    Vector2 uv1((float)texA.x_ * invTextureSize_.x_, (float)texA.y_ * invTextureSize_.y_);
    Vector2 uv2((float)texB.x_ * invTextureSize_.x_, (float)texB.y_ * invTextureSize_.y_);
    Vector2 uv3((float)texC.x_ * invTextureSize_.x_, (float)texC.y_ * invTextureSize_.y_);
    Vector2 uv4((float)texD.x_ * invTextureSize_.x_, (float)texD.y_ * invTextureSize_.y_);

    unsigned begin = vertexData_->Size();
    vertexData_->Resize(begin + 6 * UI_VERTEX_SIZE);
    float* dest = &(vertexData_->At(begin));
    vertexEnd_ = vertexData_->Size();

    dest[0] = v1.x_;
    dest[1] = v1.y_;
    dest[2] = 0.0f;
    ((unsigned&)dest[3]) = color_;
    dest[4] = uv1.x_;
    dest[5] = uv1.y_;

    dest[6] = v2.x_;
    dest[7] = v2.y_;
    dest[8] = 0.0f;
    ((unsigned&)dest[9]) = color_;
    dest[10] = uv2.x_;
    dest[11] = uv2.y_;

    dest[12] = v3.x_;
    dest[13] = v3.y_;
    dest[14] = 0.0f;
    ((unsigned&)dest[15]) = color_;
    dest[16] = uv3.x_;
    dest[17] = uv3.y_;

    dest[18] = v1.x_;
    dest[19] = v1.y_;
    dest[20] = 0.0f;
    ((unsigned&)dest[21]) = color_;
    dest[22] = uv1.x_;
    dest[23] = uv1.y_;

    dest[24] = v3.x_;
    dest[25] = v3.y_;
    dest[26] = 0.0f;
    ((unsigned&)dest[27]) = color_;
    dest[28] = uv3.x_;
    dest[29] = uv3.y_;

    dest[30] = v4.x_;
    dest[31] = v4.y_;
    dest[32] = 0.0f;
    ((unsigned&)dest[33]) = color_;
    dest[34] = uv4.x_;
    dest[35] = uv4.y_;
}

void UIBatch::AddQuad(const Matrix3x4& transform, const IntVector2& a, const IntVector2& b, const IntVector2& c, const IntVector2& d,
    const IntVector2& texA, const IntVector2& texB, const IntVector2& texC, const IntVector2& texD, const Color& colA,
    const Color& colB, const Color& colC, const Color& colD)
{
    Vector3 v1 = (transform * Vector3((float)a.x_, (float)a.y_, 0.0f)) - posAdjust;
    Vector3 v2 = (transform * Vector3((float)b.x_, (float)b.y_, 0.0f)) - posAdjust;
    Vector3 v3 = (transform * Vector3((float)c.x_, (float)c.y_, 0.0f)) - posAdjust;
    Vector3 v4 = (transform * Vector3((float)d.x_, (float)d.y_, 0.0f)) - posAdjust;

    Vector2 uv1((float)texA.x_ * invTextureSize_.x_, (float)texA.y_ * invTextureSize_.y_);
    Vector2 uv2((float)texB.x_ * invTextureSize_.x_, (float)texB.y_ * invTextureSize_.y_);
    Vector2 uv3((float)texC.x_ * invTextureSize_.x_, (float)texC.y_ * invTextureSize_.y_);
    Vector2 uv4((float)texD.x_ * invTextureSize_.x_, (float)texD.y_ * invTextureSize_.y_);

    unsigned c1 = colA.ToUInt();
    unsigned c2 = colB.ToUInt();
    unsigned c3 = colC.ToUInt();
    unsigned c4 = colD.ToUInt();

    unsigned begin = vertexData_->Size();
    vertexData_->Resize(begin + 6 * UI_VERTEX_SIZE);
    float* dest = &(vertexData_->At(begin));
    vertexEnd_ = vertexData_->Size();

    dest[0] = v1.x_;
    dest[1] = v1.y_;
    dest[2] = 0.0f;
    ((unsigned&)dest[3]) = c1;
    dest[4] = uv1.x_;
    dest[5] = uv1.y_;

    dest[6] = v2.x_;
    dest[7] = v2.y_;
    dest[8] = 0.0f;
    ((unsigned&)dest[9]) = c2;
    dest[10] = uv2.x_;
    dest[11] = uv2.y_;

    dest[12] = v3.x_;
    dest[13] = v3.y_;
    dest[14] = 0.0f;
    ((unsigned&)dest[15]) = c3;
    dest[16] = uv3.x_;
    dest[17] = uv3.y_;

    dest[18] = v1.x_;
    dest[19] = v1.y_;
    dest[20] = 0.0f;
    ((unsigned&)dest[21]) = c1;
    dest[22] = uv1.x_;
    dest[23] = uv1.y_;

    dest[24] = v3.x_;
    dest[25] = v3.y_;
    dest[26] = 0.0f;
    ((unsigned&)dest[27]) = c3;
    dest[28] = uv3.x_;
    dest[29] = uv3.y_;

    dest[30] = v4.x_;
    dest[31] = v4.y_;
    dest[32] = 0.0f;
    ((unsigned&)dest[33]) = c4;
    dest[34] = uv4.x_;
    dest[35] = uv4.y_;
}

void UIBatch::TransformUV(bool rotate, bool mirrorH, bool mirrorV, const IntRect& imageRect)
{
    float* begin = &(vertexData_->At(vertexStart_));
    float* end = begin + (vertexEnd_ - vertexStart_);
    float width = imageRect.right_ - imageRect.left_;
    float height = imageRect.bottom_ - imageRect.top_;
    for(float* data = begin; data != end; data += 6)
    {
        if(mirrorH)
            data[4] = imageRect.right_ * invTextureSize_.x_ - (data[4] - imageRect.left_ * invTextureSize_.x_);
        if(mirrorV)
            data[5] = imageRect.bottom_ * invTextureSize_.y_ - (data[5] - imageRect.top_ * invTextureSize_.y_);
        if(rotate)
        {
            float localU = (data[4] / invTextureSize_.x_ - imageRect.left_) / width;
            float localV = (data[5] / invTextureSize_.y_ - imageRect.top_) / height;
            data[4] = (imageRect.left_ + (1 - localV) * width) * invTextureSize_.x_;
            data[5] = (imageRect.top_ + localU * height) * invTextureSize_.y_;
        }
    }
}

bool UIBatch::Merge(const UIBatch& batch)
{
    if (batch.blendMode_ != blendMode_ ||
        batch.scissor_ != scissor_ ||
        batch.texture_ != texture_ ||
        batch.vertexData_ != vertexData_ ||
        batch.vertexStart_ != vertexEnd_)
        return false;

    vertexEnd_ = batch.vertexEnd_;
    return true;
}

unsigned UIBatch::GetInterpolatedColor(float x, float y)
{
    const IntVector2& size = element_->GetSize();

    if (size.x_ && size.y_)
    {
        float cLerpX = Clamp(x / (float)size.x_, 0.0f, 1.0f);
        float cLerpY = Clamp(y / (float)size.y_, 0.0f, 1.0f);

        Color topColor = element_->GetColor(C_TOPLEFT).Lerp(element_->GetColor(C_TOPRIGHT), cLerpX);
        Color bottomColor = element_->GetColor(C_BOTTOMLEFT).Lerp(element_->GetColor(C_BOTTOMRIGHT), cLerpX);
        Color color = topColor.Lerp(bottomColor, cLerpY);
        color.a_ *= element_->GetDerivedOpacity();
        return color.ToUInt();
    }
    else
    {
        Color color = element_->GetColor(C_TOPLEFT);
        color.a_ *= element_->GetDerivedOpacity();
        return color.ToUInt();
    }
}

void UIBatch::AddOrMerge(const UIBatch& batch, PODVector<UIBatch>& batches)
{
    if (batch.vertexEnd_ == batch.vertexStart_)
        return;

    if (!batches.Empty() && batches.Back().Merge(batch))
        return;

    batches.Push(batch);
}

}
