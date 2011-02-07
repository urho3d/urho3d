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
#include "PixelShader.h"
#include "Renderer.h"
#include "Texture.h"
#include "UIElement.h"
#include "VertexShader.h"

#include "DebugNew.h"

void UIBatch::begin(std::vector<UIQuad>* quads)
{
    if (quads)
    {
        mQuads = quads;
        mQuadStart = mQuads->size();
        mQuadCount = 0;
    }
}

void UIBatch::addQuad(UIElement& element, int x, int y, int width, int height, int texOffsetX, int texOffsetY)
{
    if (!mQuads)
        return;
    
    static UIQuad quad;
    const IntVector2& screenPos = element.getScreenPosition();
    
    quad.mLeft = x + screenPos.mX;
    quad.mTop = y + screenPos.mY;
    quad.mRight = quad.mLeft + width;
    quad.mBottom = quad.mTop + height;
    quad.mLeftUV = texOffsetX;
    quad.mTopUV = texOffsetY;
    quad.mRightUV = texOffsetX + width;
    quad.mBottomUV = texOffsetY + height;
    
    if (element.hasColorGradient())
    {
        quad.mTopLeftColor = getInterpolatedColor(element, x, y);
        quad.mTopRightColor = getInterpolatedColor(element, x + width, y);
        quad.mBottomLeftColor = getInterpolatedColor(element, x, y + height);
        quad.mBottomRightColor = getInterpolatedColor(element, x + width, y + height);
    }
    else
    {
        Color color = element.getColor(C_TOPLEFT);
        color.mA *= element.getDerivedOpacity();
        // If alpha is 0, nothing will be rendered, so exit without adding the quad
        if (color.mA <= 0.0f)
            return;
        unsigned uintColor = getD3DColor(color);
        quad.mTopLeftColor = uintColor;
        quad.mTopRightColor = uintColor;
        quad.mBottomLeftColor = uintColor;
        quad.mBottomRightColor = uintColor;
    }
    
    mQuads->push_back(quad);
    mQuadCount++;
}

void UIBatch::addQuad(UIElement& element, int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth, int texHeight)
{
    if (!mQuads)
        return;
    
    static UIQuad quad;
    const IntVector2& screenPos = element.getScreenPosition();
    
    quad.mLeft = x + screenPos.mX;
    quad.mTop = y + screenPos.mY;
    quad.mRight = quad.mLeft + width;
    quad.mBottom = quad.mTop + height;
    quad.mLeftUV = texOffsetX;
    quad.mTopUV = texOffsetY;
    quad.mRightUV = texOffsetX + texWidth;
    quad.mBottomUV = texOffsetY + texHeight;
    
    if (element.hasColorGradient())
    {
        quad.mTopLeftColor = getInterpolatedColor(element, x, y);
        quad.mTopRightColor = getInterpolatedColor(element, x + width, y);
        quad.mBottomLeftColor = getInterpolatedColor(element, x, y + height);
        quad.mBottomRightColor = getInterpolatedColor(element, x + width, y + height);
    }
    else
    {
        Color color = element.getColor(C_TOPLEFT);
        color.mA *= element.getDerivedOpacity();
        // If alpha is 0, nothing will be rendered, so exit without adding the quad
        if (color.mA <= 0.0f)
            return;
        unsigned uintColor = getD3DColor(color);
        quad.mTopLeftColor = uintColor;
        quad.mTopRightColor = uintColor;
        quad.mBottomLeftColor = uintColor;
        quad.mBottomRightColor = uintColor;
    }
    
    mQuads->push_back(quad);
    mQuadCount++;
}

bool UIBatch::merge(const UIBatch& batch)
{
    if ((batch.mBlendMode != mBlendMode) ||
        (batch.mScissor != mScissor) ||
        (batch.mTexture != mTexture) ||
        (batch.mQuads != mQuads) ||
        (batch.mQuadStart != mQuadStart + mQuadCount))
        return false;
    
    mQuadCount += batch.mQuadCount;
    return true;
}

void UIBatch::draw(Renderer* renderer, VertexShader* vs, PixelShader* ps) const
{
    if ((!mQuads) || (!mQuadCount))
        return;
    
    // Use alpha test if not alpha blending
    if ((mBlendMode != BLEND_ALPHA) && (mBlendMode != BLEND_ADDALPHA) && (mBlendMode != BLEND_PREMULALPHA))
        renderer->setAlphaTest(true, CMP_GREATEREQUAL, 0.5f);
    else
        renderer->setAlphaTest(false);
    
    renderer->setBlendMode(mBlendMode);
    renderer->setScissorTest(true, mScissor);
    renderer->setTexture(0, mTexture);
    renderer->setVertexShader(vs);
    renderer->setPixelShader(ps);
    
    static const Vector2 posAdjust(0.5f, 0.5f);
    Vector2 invScreenSize(1.0f / (float)renderer->getWidth(), 1.0f / (float)renderer->getHeight());
    
    const std::vector<UIQuad>& quads = *mQuads;
    
    if (mTexture)
    {
        Vector2 invTextureSize(1.0f / (float)mTexture->getWidth(), 1.0f / (float)mTexture->getHeight());
        
        renderer->beginImmediate(TRIANGLE_LIST, mQuadCount * 6, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1);
        float* dest = (float*)renderer->getImmediateDataPtr();
        
        for (unsigned i = mQuadStart; i < mQuadStart + mQuadCount; ++i)
        {
            const UIQuad& quad = quads[i];
            static Vector2 topLeft, bottomRight, topLeftUV, bottomRightUV;
            
            topLeft = (Vector2((float)quad.mLeft, (float)quad.mTop) - posAdjust) * invScreenSize;
            bottomRight = (Vector2((float)quad.mRight, (float)quad.mBottom) - posAdjust) * invScreenSize;
            topLeftUV = Vector2((float)quad.mLeftUV, (float)quad.mTopUV) * invTextureSize;
            bottomRightUV = Vector2((float)quad.mRightUV, (float)quad.mBottomUV) * invTextureSize;
            
            *dest++ = topLeft.mX; *dest++ = topLeft.mY; *dest++ = 0.0f;
            *((unsigned*)dest) = quads[i].mTopLeftColor; dest++;
            *dest++ = topLeftUV.mX; *dest++ = topLeftUV.mY;
            
            *dest++ = bottomRight.mX; *dest++ = topLeft.mY; *dest++ = 0.0f;
            *((unsigned*)dest) = quads[i].mTopRightColor; dest++;
            *dest++ = bottomRightUV.mX; *dest++ = topLeftUV.mY;
            
            *dest++ = topLeft.mX; *dest++ = bottomRight.mY; *dest++ = 0.0f;
            *((unsigned*)dest) = quads[i].mBottomLeftColor; dest++;
            *dest++ = topLeftUV.mX; *dest++ = bottomRightUV.mY;
            
            *dest++ = bottomRight.mX; *dest++ = topLeft.mY; *dest++ = 0.0f;
            *((unsigned*)dest) = quads[i].mTopRightColor; dest++;
            *dest++ = bottomRightUV.mX; *dest++ = topLeftUV.mY;
            
            *dest++ = bottomRight.mX; *dest++ = bottomRight.mY; *dest++ = 0.0f;
            *((unsigned*)dest) = quads[i].mBottomRightColor; dest++;
            *dest++ = bottomRightUV.mX; *dest++ = bottomRightUV.mY;
            
            *dest++ = topLeft.mX; *dest++ = bottomRight.mY; *dest++ = 0.0f;
            *((unsigned*)dest) = quads[i].mBottomLeftColor; dest++;
            *dest++ = topLeftUV.mX; *dest++ = bottomRightUV.mY;
        }
        
        renderer->endImmediate();
    }
    else
    {
        renderer->beginImmediate(TRIANGLE_LIST, mQuadCount * 6, MASK_POSITION | MASK_COLOR);
        float* dest = (float*)renderer->getImmediateDataPtr();
        
        for (unsigned i = mQuadStart; i < mQuadStart + mQuadCount; ++i)
        {
            const UIQuad& quad = quads[i];
            static Vector2 topLeft, bottomRight, topLeftUV, bottomRightUV;
            
            topLeft = (Vector2((float)quad.mLeft, (float)quad.mTop) - posAdjust) * invScreenSize;
            bottomRight = (Vector2((float)quad.mRight, (float)quad.mBottom) - posAdjust) * invScreenSize;
            
            *dest++ = topLeft.mX; *dest++ = topLeft.mY; *dest++ = 0.0f;
            *((unsigned*)dest) = quads[i].mTopLeftColor; dest++;
            
            *dest++ = bottomRight.mX; *dest++ = topLeft.mY; *dest++ = 0.0f;
            *((unsigned*)dest) = quads[i].mTopRightColor; dest++;
            
            *dest++ = topLeft.mX; *dest++ = bottomRight.mY; *dest++ = 0.0f;
            *((unsigned*)dest) = quads[i].mBottomLeftColor; dest++;
            
            *dest++ = bottomRight.mX; *dest++ = topLeft.mY; *dest++ = 0.0f;
            *((unsigned*)dest) = quads[i].mTopRightColor; dest++;
            
            *dest++ = bottomRight.mX; *dest++ = bottomRight.mY; *dest++ = 0.0f;
            *((unsigned*)dest) = quads[i].mBottomRightColor; dest++;
            
            *dest++ = topLeft.mX; *dest++ = bottomRight.mY; *dest++ = 0.0f;
            *((unsigned*)dest) = quads[i].mBottomLeftColor; dest++;
        }
        
        renderer->endImmediate();
    }
}

void UIBatch::addOrMerge(const UIBatch& batch, std::vector<UIBatch>& batches)
{
    if (!batches.size())
        batches.push_back(batch);
    else
    {
        if (batches.back().merge(batch))
            return;
        else
            batches.push_back(batch);
    }
}

unsigned UIBatch::getInterpolatedColor(UIElement& element, int x, int y)
{
    const IntVector2& size = element.getSize();
    
    if ((size.mX) && (size.mY))
    {
        float cLerpX = clamp((float)x / (float)size.mX, 0.0f, 1.0f);
        float cLerpY = clamp((float)y / (float)size.mY, 0.0f, 1.0f);
        
        Color topColor = element.getColor(C_TOPLEFT).lerp(element.getColor(C_TOPRIGHT), cLerpX);
        Color bottomColor = element.getColor(C_BOTTOMLEFT).lerp(element.getColor(C_BOTTOMRIGHT), cLerpX);
        Color color = topColor.lerp(bottomColor, cLerpY);
        color.mA *= element.getDerivedOpacity();
        return getD3DColor(color);
    }
    else
    {
        Color color = element.getColor(C_TOPLEFT);
        color.mA *= element.getDerivedOpacity();
        return getD3DColor(color);
    }
}
