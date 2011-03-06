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
#include "BorderImage.h"
#include "ResourceCache.h"
#include "Texture2D.h"

#include "DebugNew.h"

BorderImage::BorderImage(const std::string& name) :
    UIElement(name),
    mImageRect(IntRect::sZero),
    mBorder(IntRect::sZero),
    mHoverOffset(IntVector2::sZero)
{
}

BorderImage::~BorderImage()
{
}

void BorderImage::setStyle(const XMLElement& element, ResourceCache* cache)
{
    if (!cache)
        return;
    
    UIElement::setStyle(element, cache);
    
    if (element.hasChildElement("texture"))
        setTexture(cache->getResource<Texture2D>(element.getChildElement("texture").getString("name")));
    if (element.hasChildElement("imagerect"))
    {
        XMLElement imageElem = element.getChildElement("imagerect");
        if (imageElem.hasAttribute("value"))
            setImageRect(imageElem.getIntRect("value"));
    }
    if (element.hasChildElement("border"))
        setBorder(element.getChildElement("border").getIntRect("value"));
    if (element.hasChildElement("hoveroffset"))
        setHoverOffset(element.getChildElement("hoveroffset").getIntVector2("value"));
}

void BorderImage::getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor)
{
    if ((mHovering) || (mSelected))
        getBatches(batches, quads, currentScissor, mHoverOffset);
    else
        getBatches(batches, quads, currentScissor, IntVector2::sZero);
}

void BorderImage::setTexture(Texture* texture)
{
    mTexture = texture;
    if (mImageRect == IntRect::sZero)
        setFullImageRect();
}

void BorderImage::setImageRect(const IntRect& rect)
{
    if (rect != IntRect::sZero)
        mImageRect = rect;
}

void BorderImage::setImageRect(int left, int top, int right, int bottom)
{
    setImageRect(IntRect(left, top, right, bottom));
}

void BorderImage::setFullImageRect()
{
    if (mTexture)
        setImageRect(IntRect(0, 0, mTexture->getWidth(), mTexture->getHeight()));
}

void BorderImage::setBorder(const IntRect& rect)
{
    mBorder.mLeft = max(rect.mLeft, 0);
    mBorder.mTop = max(rect.mTop, 0);
    mBorder.mRight = max(rect.mRight, 0);
    mBorder.mBottom = max(rect.mBottom, 0);
}

void BorderImage::setBorder(int left, int top, int right, int bottom)
{
    setBorder(IntRect(left, top, right, bottom));
}

void BorderImage::setHoverOffset(const IntVector2& offset)
{
    mHoverOffset = offset;
}

void BorderImage::setHoverOffset(int x, int y)
{
    mHoverOffset = IntVector2(x, y);
}

void BorderImage::getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor, const IntVector2& offset)
{
    bool allOpaque = true;
    if ((getDerivedOpacity() < 1.0f) || (mColor[C_TOPLEFT].mA < 1.0f) || (mColor[C_TOPRIGHT].mA < 1.0f) ||
        (mColor[C_BOTTOMLEFT].mA < 1.0f) || (mColor[C_BOTTOMRIGHT].mA < 1.0f))
        allOpaque = false;
        
    UIBatch batch;
    batch.begin(&quads);
    batch.mBlendMode = allOpaque ? BLEND_REPLACE : BLEND_ALPHA;
    batch.mScissor = currentScissor;
    batch.mTexture = mTexture;
    
    // Calculate size of the inner rect, and texture dimensions of the inner rect
    const IntVector2& size = getSize();
    IntVector2 innerSize(
        max(size.mX - mBorder.mLeft - mBorder.mRight, 0), 
        max(size.mY - mBorder.mTop - mBorder.mBottom, 0));
    IntVector2 innerTextureSize(
        max(mImageRect.mRight - mImageRect.mLeft - mBorder.mLeft - mBorder.mRight, 0),
        max(mImageRect.mBottom - mImageRect.mTop - mBorder.mTop - mBorder.mBottom, 0));
    
    IntVector2 topLeft(mImageRect.mLeft, mImageRect.mTop);
    topLeft += offset;
    
    // Top
    if (mBorder.mTop)
    {
        if (mBorder.mLeft)
            batch.addQuad(*this, 0, 0, mBorder.mLeft, mBorder.mTop, topLeft.mX, topLeft.mY);
        if (innerSize.mX)
            batch.addQuad(*this, mBorder.mLeft, 0, innerSize.mX, mBorder.mTop,
            topLeft.mX + mBorder.mLeft, topLeft.mY, innerTextureSize.mX, mBorder.mTop);
        if (mBorder.mRight)
            batch.addQuad(*this, mBorder.mLeft + innerSize.mX, 0, mBorder.mRight, mBorder.mTop,
            topLeft.mX + mBorder.mLeft + innerTextureSize.mX, topLeft.mY);
    }
    // Middle
    if (innerSize.mY)
    {
        if (mBorder.mLeft)
            batch.addQuad(*this, 0, mBorder.mTop, mBorder.mLeft, innerSize.mY,
            topLeft.mX, topLeft.mY + mBorder.mTop, mBorder.mLeft, innerTextureSize.mY);
        if (innerSize.mX)
            batch.addQuad(*this, mBorder.mLeft, mBorder.mTop, innerSize.mX, innerSize.mY,
            topLeft.mX + mBorder.mLeft, topLeft.mY + mBorder.mTop, innerTextureSize.mX, innerTextureSize.mY);
        if (mBorder.mRight)
            batch.addQuad(*this, mBorder.mLeft + innerSize.mX, mBorder.mTop, mBorder.mRight,
            innerSize.mY, topLeft.mX + mBorder.mLeft + innerTextureSize.mX, topLeft.mY + mBorder.mTop,
            mBorder.mRight, innerTextureSize.mY);
    }
    // Bottom
    if (mBorder.mBottom)
    {
        if (mBorder.mLeft)
            batch.addQuad(*this, 0, mBorder.mTop + innerSize.mY, mBorder.mLeft, mBorder.mBottom,
            topLeft.mX, topLeft.mY + mBorder.mTop + innerTextureSize.mY);
        if (innerSize.mX)
            batch.addQuad(*this, mBorder.mLeft, mBorder.mTop + innerSize.mY, innerSize.mX,
            mBorder.mBottom, topLeft.mX + mBorder.mLeft, topLeft.mY + mBorder.mTop + innerTextureSize.mY,
            innerTextureSize.mX, mBorder.mBottom);
        if (mBorder.mRight)
            batch.addQuad(*this, mBorder.mLeft + innerSize.mX, mBorder.mTop + innerSize.mY,
            mBorder.mRight, mBorder.mBottom, topLeft.mX + mBorder.mLeft + innerTextureSize.mX, 
            topLeft.mY + mBorder.mTop + innerTextureSize.mY);
    }
    
    UIBatch::addOrMerge(batch, batches);
    
    // Reset hovering for next frame
    mHovering = false;
}
