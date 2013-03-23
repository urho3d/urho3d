//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Graphics.h"
#include "Matrix3x4.h"
#include "ShaderVariation.h"
#include "Texture.h"
#include "UIElement.h"

#include "DebugNew.h"

namespace Urho3D
{

#ifdef USE_OPENGL
static const Vector2 posAdjust(Vector2::ZERO);
#else
static const Vector2 posAdjust(0.5f, 0.5f);
#endif

UIQuad::UIQuad() :
    defined_(false)
{
}

UIQuad::UIQuad(const UIElement& element, int x, int y, int width, int height, int texOffsetX, int texOffsetY,
    int texWidth, int texHeight, Color* color) :
    defined_(false)
{
    if (color || !element.HasColorGradient())
    {
        unsigned uintColor = (color ? *color : element.GetDerivedColor()).ToUInt();
        
        // If alpha is 0, nothing will be rendered, so do not add the quad
        if (!(uintColor & 0xff000000))
            return;
        
        topLeftColor_ = uintColor;
        topRightColor_ = uintColor;
        bottomLeftColor_ = uintColor;
        bottomRightColor_ = uintColor;
    }
    else
    {
        topLeftColor_ = GetInterpolatedColor(element, x, y);
        topRightColor_ = GetInterpolatedColor(element, x + width, y);
        bottomLeftColor_ = GetInterpolatedColor(element, x, y + height);
        bottomRightColor_ = GetInterpolatedColor(element, x + width, y + height);
    }
    
    const IntVector2& screenPos = element.GetScreenPosition();
    
    float left = (float)(x + screenPos.x_);
    float right = left + (float)width;
    float top = (float)(y + screenPos.y_);
    float bottom = top + (float)height;
    topLeft_ = Vector2(left, top) - posAdjust;
    topRight_ = Vector2(right, top) - posAdjust;
    bottomLeft_ = Vector2(left, bottom) - posAdjust;
    bottomRight_ = Vector2(right, bottom) - posAdjust;
    
    leftUV_ = texOffsetX;
    topUV_ = texOffsetY;
    rightUV_ = texOffsetX + (texWidth ? texWidth : width);
    bottomUV_ = texOffsetY + (texHeight ? texHeight : height);
    
    defined_ = true;
}

UIQuad::UIQuad(const UIElement& element, const Matrix3x4& transform, int x, int y, int width, int height, int texOffsetX, int texOffsetY,
    int texWidth, int texHeight, Color* color) :
    defined_(false)
{
    if (color || !element.HasColorGradient())
    {
        unsigned uintColor = (color ? *color : element.GetDerivedColor()).ToUInt();
        
        // If alpha is 0, nothing will be rendered, so do not add the quad
        if (!(uintColor & 0xff000000))
            return;
        
        topLeftColor_ = uintColor;
        topRightColor_ = uintColor;
        bottomLeftColor_ = uintColor;
        bottomRightColor_ = uintColor;
    }
    else
    {
        topLeftColor_ = GetInterpolatedColor(element, x, y);
        topRightColor_ = GetInterpolatedColor(element, x + width, y);
        bottomLeftColor_ = GetInterpolatedColor(element, x, y + height);
        bottomRightColor_ = GetInterpolatedColor(element, x + width, y + height);
    }
    
    Vector3 v1 = transform * Vector3((float)x, (float)y, 0.0f);
    Vector3 v2 = transform * Vector3((float)x + (float)width, (float)y, 0.0f);
    Vector3 v3 = transform * Vector3((float)x, (float)y + (float)height, 0.0f);
    Vector3 v4 = transform * Vector3((float)x + (float)width, (float)y + (float)height, 0.0f);
    
    topLeft_.x_ = v1.x_; topLeft_.y_ = v1.y_;
    topRight_.x_ = v2.x_; topRight_.y_ = v2.y_;
    bottomLeft_.x_ = v3.x_; bottomLeft_.y_ = v3.y_;
    bottomRight_.x_ = v4.x_; bottomRight_.y_ = v4.y_;
    
    leftUV_ = texOffsetX;
    topUV_ = texOffsetY;
    rightUV_ = texOffsetX + (texWidth ? texWidth : (int)width);
    bottomUV_ = texOffsetY + (texHeight ? texHeight : (int)height);
    
    defined_ = true;
}

unsigned UIQuad::GetInterpolatedColor(const UIElement& element, int x, int y)
{
    const IntVector2& size = element.GetSize();
    
    if (size.x_ && size.y_)
    {
        float cLerpX = Clamp((float)x / (float)size.x_, 0.0f, 1.0f);
        float cLerpY = Clamp((float)y / (float)size.y_, 0.0f, 1.0f);
        
        Color topColor = element.GetColor(C_TOPLEFT).Lerp(element.GetColor(C_TOPRIGHT), cLerpX);
        Color bottomColor = element.GetColor(C_BOTTOMLEFT).Lerp(element.GetColor(C_BOTTOMRIGHT), cLerpX);
        Color color = topColor.Lerp(bottomColor, cLerpY);
        color.a_ *= element.GetDerivedOpacity();
        return color.ToUInt();
    }
    else
    {
        Color color = element.GetColor(C_TOPLEFT);
        color.a_ *= element.GetDerivedOpacity();
        return color.ToUInt();
    }
}

UIBatch::UIBatch() :
    blendMode_(BLEND_REPLACE),
    texture_(0),
    quads_(0),
    quadStart_(0),
    quadCount_(0)
{
}

UIBatch::UIBatch(BlendMode blendMode, const IntRect& scissor, Texture* texture, PODVector<UIQuad>* quads) :
    blendMode_(blendMode),
    scissor_(scissor),
    texture_(texture),
    quads_(0),
    quadStart_(0),
    quadCount_(0)
{
    Begin(quads);
}

void UIBatch::Begin(PODVector<UIQuad>* quads)
{
    quads_ = quads;
    quadStart_ = quads_->Size();
    quadCount_ = 0;
}

void UIBatch::AddQuad(const PODVector<UIQuad>& quads)
{
    if (quads.Empty())
        return;
    
    *quads_ += quads;
    quadCount_ += quads.Size();
}

void UIBatch::AddQuad(UIQuad quad)
{
    if (quad.defined_)
    {
        quads_->Push(quad);
        ++quadCount_;
    }
}

void UIBatch::AddQuad(const UIElement& element, int x, int y, int width, int height, int texOffsetX, int texOffsetY)
{
    AddQuad(UIQuad(element, x, y, width, height, texOffsetX, texOffsetY));
}

void UIBatch::AddQuad(const UIElement& element, int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth,
    int texHeight)
{
    AddQuad(UIQuad(element, x, y, width, height, texOffsetX, texOffsetY, texWidth, texHeight));
}

void UIBatch::AddQuad(const UIElement& element, int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth,
    int texHeight, bool tiled)
{
    if (!(element.HasColorGradient() || element.GetDerivedColor().ToUInt() & 0xff000000))
        return; // No gradient and alpha is 0, so do not add the quads
    
    if (!tiled)
    {
        AddQuad(element, x, y, width, height, texOffsetX, texOffsetY, texWidth, texHeight);
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
            
            AddQuad(element, x + tileX, y + tileY, tileW, tileH, texOffsetX, texOffsetY, tileW, tileH);
            
            tileX += tileW;
        }
        
        tileY += tileH;
    }
}

void UIBatch::AddQuad(const UIElement& element, int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth,
    int texHeight, const Color& color)
{
    Color derivedColor(color.r_, color.g_, color.b_, color.a_ * element.GetDerivedOpacity());
    AddQuad(UIQuad(element, x, y, width, height, texOffsetX, texOffsetY, texWidth, texHeight, &derivedColor));
}

bool UIBatch::Merge(const UIBatch& batch)
{
    if (batch.blendMode_ != blendMode_ ||
        batch.scissor_ != scissor_ ||
        batch.texture_ != texture_ ||
        batch.quads_ != quads_ ||
        batch.quadStart_ != quadStart_ + quadCount_)
        return false;
    
    quadCount_ += batch.quadCount_;
    return true;
}

void UIBatch::UpdateGeometry(Graphics* graphics, void* lockedData)
{
    if (!quadCount_)
        return;
    
    float* dest = (float*)lockedData;
    
    if (texture_)
    {
        Vector2 invTextureSize(1.0f / (float)texture_->GetWidth(), 1.0f / (float)texture_->GetHeight());
        
        for (unsigned i = 0; i < quadCount_; ++i)
        {
            const UIQuad& quad = quads_->At(quadStart_ + i);
            
            Vector2 topLeftUV = Vector2((float)quad.leftUV_, (float)quad.topUV_) * invTextureSize;
            Vector2 bottomRightUV = Vector2((float)quad.rightUV_, (float)quad.bottomUV_) * invTextureSize;
            
            *dest++ = quad.topLeft_.x_; *dest++ = quad.topLeft_.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.topLeftColor_; dest++;
            *dest++ = topLeftUV.x_; *dest++ = topLeftUV.y_;
            
            *dest++ = quad.topRight_.x_; *dest++ = quad.topRight_.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.topRightColor_; dest++;
            *dest++ = bottomRightUV.x_; *dest++ = topLeftUV.y_;
            
            *dest++ = quad.bottomLeft_.x_; *dest++ = quad.bottomLeft_.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.bottomLeftColor_; dest++;
            *dest++ = topLeftUV.x_; *dest++ = bottomRightUV.y_;
            
            *dest++ = quad.topRight_.x_; *dest++ = quad.topRight_.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.topRightColor_; dest++;
            *dest++ = bottomRightUV.x_; *dest++ = topLeftUV.y_;
            
            *dest++ = quad.bottomRight_.x_; *dest++ = quad.bottomRight_.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.bottomRightColor_; dest++;
            *dest++ = bottomRightUV.x_; *dest++ = bottomRightUV.y_;
            
            *dest++ = quad.bottomLeft_.x_; *dest++ = quad.bottomLeft_.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.bottomLeftColor_; dest++;
            *dest++ = topLeftUV.x_; *dest++ = bottomRightUV.y_;
        }
    }
    else
    {
        for (unsigned i = 0; i < quadCount_; ++i)
        {
            const UIQuad& quad = quads_->At(quadStart_ + i);
            
            *dest++ = quad.topLeft_.x_; *dest++ = quad.topLeft_.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.topLeftColor_; dest++;
            dest += 2; // Jump over unused UV coordinates
            
            *dest++ = quad.topRight_.x_; *dest++ = quad.topRight_.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.topRightColor_; dest++;
            dest += 2;
            
            *dest++ = quad.bottomLeft_.x_; *dest++ = quad.bottomLeft_.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.bottomLeftColor_; dest++;
            dest += 2;
            
            *dest++ = quad.topRight_.x_; *dest++ = quad.topRight_.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.topRightColor_; dest++;
            dest += 2;
            
            *dest++ = quad.bottomRight_.x_; *dest++ = quad.bottomRight_.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.bottomRightColor_; dest++;
            dest += 2;
            
            *dest++ = quad.bottomLeft_.x_; *dest++ = quad.bottomLeft_.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.bottomLeftColor_; dest++;
            dest += 2;
        }
    }
}

void UIBatch::AddOrMerge(const UIBatch& batch, PODVector<UIBatch>& batches)
{
    if (!batch.quadCount_)
        return;
    
    if (!batches.Empty() && batches.Back().Merge(batch))
        return;
    
    batches.Push(batch);
}

}
