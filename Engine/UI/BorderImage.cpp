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
    mImageRect(0, 0, 0, 0),
    mBorder(0, 0, 0, 0)
{
}

BorderImage::~BorderImage()
{
}

XMLElement BorderImage::loadParameters(XMLFile* file, const std::string& elementName, ResourceCache* cache)
{
    XMLElement paramElem = UIElement::loadParameters(file, elementName, cache);
    
    if (paramElem.hasChildElement("texture"))
        setTexture(cache->getResource<Texture2D>(paramElem.getChildElement("texture").getString("name")));
    if (paramElem.hasChildElement("imagerect"))
        setImageRect(paramElem.getChildElement("imagerect").getIntRect("value"));
    if (paramElem.hasChildElement("border"))
        setBorder(paramElem.getChildElement("border").getIntRect("value"));
    
    return paramElem;
}

void BorderImage::getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor)
{
    UIBatch batch;
    batch.begin(&quads);
    batch.mBlendMode = getDerivedOpacity() == 1.0f ? BLEND_REPLACE : BLEND_ALPHA;
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

    // Top
    if (mBorder.mTop)
    {
        if (mBorder.mLeft)
            batch.addQuad(*this, 0, 0, mBorder.mLeft, mBorder.mTop, mImageRect.mLeft, mImageRect.mTop);
        if (innerSize.mX)
            batch.addQuad(*this, mBorder.mLeft, 0, innerSize.mX, mBorder.mTop,
            mImageRect.mLeft + mBorder.mLeft, mImageRect.mTop, innerTextureSize.mX, mBorder.mTop);
        if (mBorder.mRight)
            batch.addQuad(*this, mBorder.mLeft + innerSize.mX, 0, mBorder.mRight, mBorder.mTop,
            mImageRect.mLeft + mBorder.mLeft + innerTextureSize.mX, mImageRect.mTop);
    }
    // Middle
    if (innerSize.mY)
    {
        if (mBorder.mLeft)
            batch.addQuad(*this, 0, mBorder.mTop, mBorder.mLeft, innerSize.mY,
            mImageRect.mLeft, mImageRect.mTop + mBorder.mTop, mBorder.mLeft, innerTextureSize.mY);
        if (innerSize.mX)
            batch.addQuad(*this, mBorder.mLeft, mBorder.mTop, innerSize.mX, innerSize.mY,
            mImageRect.mLeft + mBorder.mLeft, mImageRect.mTop + mBorder.mTop, innerTextureSize.mX, innerTextureSize.mY);
        if (mBorder.mRight)
            batch.addQuad(*this, mBorder.mLeft + innerSize.mX, mBorder.mTop, mBorder.mRight,
            innerSize.mY, mImageRect.mLeft + mBorder.mLeft + innerTextureSize.mX, mImageRect.mTop + mBorder.mTop,
            mBorder.mRight, innerTextureSize.mY);
    }
    // Bottom
    if (mBorder.mBottom)
    {
        if (mBorder.mLeft)
            batch.addQuad(*this, 0, mBorder.mTop + innerSize.mY, mBorder.mLeft, mBorder.mBottom,
            mImageRect.mLeft, mImageRect.mTop + mBorder.mTop + innerTextureSize.mY);
        if (innerSize.mX)
            batch.addQuad(*this, mBorder.mLeft, mBorder.mTop + innerSize.mY, innerSize.mX,
            mBorder.mBottom, mImageRect.mLeft + mBorder.mLeft, mImageRect.mTop + mBorder.mTop + innerTextureSize.mY,
            innerTextureSize.mX, mBorder.mBottom);
        if (mBorder.mRight)
            batch.addQuad(*this, mBorder.mLeft + innerSize.mX, mBorder.mTop + innerSize.mY,
            mBorder.mRight, mBorder.mBottom, mImageRect.mLeft + mBorder.mLeft + innerTextureSize.mX, 
            mImageRect.mTop + mBorder.mTop + innerTextureSize.mY);
    }
    
    UIBatch::addOrMerge(batch, batches);
}

void BorderImage::setTexture(Texture* texture)
{
    mTexture = texture;
    if (mImageRect == IntRect::sZero)
        setFullImageRect();
}

void BorderImage::setImageRect(const IntRect& rect)
{
    mImageRect = rect;
}

void BorderImage::setImageRect(int left, int top, int right, int bottom)
{
    mImageRect.mLeft = left;
    mImageRect.mTop = top;
    mImageRect.mRight = right;
    mImageRect.mBottom = bottom;
}

void BorderImage::setFullImageRect()
{
    if (mTexture)
    {
        mImageRect.mLeft = 0;
        mImageRect.mTop = 0;
        mImageRect.mRight = mTexture->getWidth();
        mImageRect.mBottom = mTexture->getHeight();
    }
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
    mBorder.mLeft = max(left, 0);
    mBorder.mTop = max(top, 0);
    mBorder.mRight = max(right, 0);
    mBorder.mBottom = max(bottom, 0);
}
