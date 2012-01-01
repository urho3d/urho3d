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
#include "Graphics.h"
#include "ShaderVariation.h"
#include "Texture.h"
#include "UIElement.h"

#include "DebugNew.h"

void UIBatch::Begin(PODVector<UIQuad>* quads)
{
    if (quads)
    {
        quads_ = quads;
        quadStart_ = quads_->Size();
        quadCount_ = 0;
    }
}

void UIBatch::AddQuad(UIElement& element, int x, int y, int width, int height, int texOffsetX, int texOffsetY)
{
    if (!quads_)
        return;
   
    UIQuad quad;
    const IntVector2& screenPos = element.GetScreenPosition();
    
    quad.left_ = x + screenPos.x_;
    quad.top_ = y + screenPos.y_;
    quad.right_ = quad.left_ + width;
    quad.bottom_ = quad.top_ + height;
    quad.leftUV_ = texOffsetX;
    quad.topUV_ = texOffsetY;
    quad.rightUV_ = texOffsetX + width;
    quad.bottomUV_ = texOffsetY + height;
    
    if (element.HasColorGradient())
    {
        quad.topLeftColor_ = GetInterpolatedColor(element, x, y);
        quad.topRightColor_ = GetInterpolatedColor(element, x + width, y);
        quad.bottomLeftColor_ = GetInterpolatedColor(element, x, y + height);
        quad.bottomRightColor_ = GetInterpolatedColor(element, x + width, y + height);
    }
    else
    {
        unsigned uintColor = element.GetUIntColor();
        // If alpha is 0, nothing will be rendered, so do not add the quad
        if (!(uintColor & 0xff000000))
            return;
        quad.topLeftColor_ = uintColor;
        quad.topRightColor_ = uintColor;
        quad.bottomLeftColor_ = uintColor;
        quad.bottomRightColor_ = uintColor;
    }
    
    quads_->Push(quad);
    quadCount_++;
}

void UIBatch::AddQuad(UIElement& element, int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth,
    int texHeight)
{
    if (!quads_)
        return;
    
    UIQuad quad;
    const IntVector2& screenPos = element.GetScreenPosition();
    
    quad.left_ = x + screenPos.x_;
    quad.top_ = y + screenPos.y_;
    quad.right_ = quad.left_ + width;
    quad.bottom_ = quad.top_ + height;
    quad.leftUV_ = texOffsetX;
    quad.topUV_ = texOffsetY;
    quad.rightUV_ = texOffsetX + texWidth;
    quad.bottomUV_ = texOffsetY + texHeight;
    
    if (element.HasColorGradient())
    {
        quad.topLeftColor_ = GetInterpolatedColor(element, x, y);
        quad.topRightColor_ = GetInterpolatedColor(element, x + width, y);
        quad.bottomLeftColor_ = GetInterpolatedColor(element, x, y + height);
        quad.bottomRightColor_ = GetInterpolatedColor(element, x + width, y + height);
    }
    else
    {
        unsigned uintColor = element.GetUIntColor();
        // If alpha is 0, nothing will be rendered, so do not add the quad
        if (!(uintColor & 0xff000000))
            return;
        quad.topLeftColor_ = uintColor;
        quad.topRightColor_ = uintColor;
        quad.bottomLeftColor_ = uintColor;
        quad.bottomRightColor_ = uintColor;
    }
    
    quads_->Push(quad);
    quadCount_++;
}

void UIBatch::AddQuad(UIElement& element, int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth,
    int texHeight, const Color& color)
{
    if (!quads_)
        return;
    
    UIQuad quad;
    const IntVector2& screenPos = element.GetScreenPosition();
    
    quad.left_ = x + screenPos.x_;
    quad.top_ = y + screenPos.y_;
    quad.right_ = quad.left_ + width;
    quad.bottom_ = quad.top_ + height;
    quad.leftUV_ = texOffsetX;
    quad.topUV_ = texOffsetY;
    quad.rightUV_ = texOffsetX + texWidth;
    quad.bottomUV_ = texOffsetY + texHeight;
    
    Color derivedColor(color.r_, color.g_, color.b_, color.a_ * element.GetDerivedOpacity());
    // If alpha is 0, nothing will be rendered, so exit without adding the quad
    if (derivedColor.a_ <= 0.0f)
        return;
    unsigned uintColor = derivedColor.ToUInt();
    quad.topLeftColor_ = uintColor;
    quad.topRightColor_ = uintColor;
    quad.bottomLeftColor_ = uintColor;
    quad.bottomRightColor_ = uintColor;
    
    quads_->Push(quad);
    quadCount_++;
}

bool UIBatch::Merge(const UIBatch& batch)
{
    if ((batch.blendMode_ != blendMode_) ||
        (batch.scissor_ != scissor_) ||
        (batch.texture_ != texture_) ||
        (batch.quads_ != quads_) ||
        (batch.quadStart_ != quadStart_ + quadCount_))
        return false;
    
    quadCount_ += batch.quadCount_;
    return true;
}

void UIBatch::UpdateGeometry(Graphics* graphics, void* lockedData)
{
    if (!quadCount_)
        return;
    
    #ifdef USE_OPENGL
    Vector2 posAdjust(Vector2::ZERO);
    #else
    Vector2 posAdjust(0.5f, 0.5f);
    #endif
    Vector2 invScreenSize(1.0f / (float)graphics->GetWidth(), 1.0f / (float)graphics->GetHeight());
    
    float* dest = (float*)lockedData;
    
    if (texture_)
    {
        Vector2 invTextureSize(1.0f / (float)texture_->GetWidth(), 1.0f / (float)texture_->GetHeight());
        
        for (unsigned i = 0; i < quadCount_; ++i)
        {
            const UIQuad& quad = quads_->At(quadStart_ + i);
            Vector2 topLeft, bottomRight, topLeftUV, bottomRightUV;
            
            topLeft = (Vector2((float)quad.left_, (float)quad.top_) - posAdjust) * invScreenSize;
            bottomRight = (Vector2((float)quad.right_, (float)quad.bottom_) - posAdjust) * invScreenSize;
            topLeftUV = Vector2((float)quad.leftUV_, (float)quad.topUV_) * invTextureSize;
            bottomRightUV = Vector2((float)quad.rightUV_, (float)quad.bottomUV_) * invTextureSize;
            
            *dest++ = topLeft.x_; *dest++ = topLeft.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.topLeftColor_; dest++;
            *dest++ = topLeftUV.x_; *dest++ = topLeftUV.y_;
            
            *dest++ = bottomRight.x_; *dest++ = topLeft.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.topRightColor_; dest++;
            *dest++ = bottomRightUV.x_; *dest++ = topLeftUV.y_;
            
            *dest++ = topLeft.x_; *dest++ = bottomRight.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.bottomLeftColor_; dest++;
            *dest++ = topLeftUV.x_; *dest++ = bottomRightUV.y_;
            
            *dest++ = bottomRight.x_; *dest++ = topLeft.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.topRightColor_; dest++;
            *dest++ = bottomRightUV.x_; *dest++ = topLeftUV.y_;
            
            *dest++ = bottomRight.x_; *dest++ = bottomRight.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.bottomRightColor_; dest++;
            *dest++ = bottomRightUV.x_; *dest++ = bottomRightUV.y_;
            
            *dest++ = topLeft.x_; *dest++ = bottomRight.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.bottomLeftColor_; dest++;
            *dest++ = topLeftUV.x_; *dest++ = bottomRightUV.y_;
        }
    }
    else
    {
        for (unsigned i = 0; i < quadCount_; ++i)
        {
            const UIQuad& quad = quads_->At(quadStart_ + i);
            Vector2 topLeft, bottomRight, topLeftUV, bottomRightUV;
            
            topLeft = (Vector2((float)quad.left_, (float)quad.top_) - posAdjust) * invScreenSize;
            bottomRight = (Vector2((float)quad.right_, (float)quad.bottom_) - posAdjust) * invScreenSize;
            
            *dest++ = topLeft.x_; *dest++ = topLeft.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.topLeftColor_; dest++;
            dest += 2; // Jump over unused UV coordinates
            
            *dest++ = bottomRight.x_; *dest++ = topLeft.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.topRightColor_; dest++;
            dest += 2;
            
            *dest++ = topLeft.x_; *dest++ = bottomRight.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.bottomLeftColor_; dest++;
            dest += 2;
            
            *dest++ = bottomRight.x_; *dest++ = topLeft.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.topRightColor_; dest++;
            dest += 2;
            
            *dest++ = bottomRight.x_; *dest++ = bottomRight.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.bottomRightColor_; dest++;
            dest += 2;
            
            *dest++ = topLeft.x_; *dest++ = bottomRight.y_; *dest++ = 0.0f;
            *((unsigned*)dest) = quad.bottomLeftColor_; dest++;
            dest += 2;
        }
    }
}

void UIBatch::AddOrMerge(const UIBatch& batch, PODVector<UIBatch>& batches)
{
    if (!batch.quadCount_)
        return;
    
    if (!batches.Size())
        batches.Push(batch);
    else
    {
        if (batches.Back().Merge(batch))
            return;
        else
            batches.Push(batch);
    }
}

unsigned UIBatch::GetInterpolatedColor(UIElement& element, int x, int y)
{
    const IntVector2& size = element.GetSize();
    
    if (size.x_ && size.y_)
    {
        float cLerpX = Clamp((float)x / (float)size.x_, 0.0f, 1.0f);
        float cLerpY = Clamp((float)y / (float)size.y_, 0.0f, 1.0f);
        
        Color topColor = element.GetColor(C_TOPLEFT).Lerp(element.GetColor(C_TOPRIGHT), cLerpX);
        Color bottocolor_ = element.GetColor(C_BOTTOMLEFT).Lerp(element.GetColor(C_BOTTOMRIGHT), cLerpX);
        Color color = topColor.Lerp(bottocolor_, cLerpY);
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
