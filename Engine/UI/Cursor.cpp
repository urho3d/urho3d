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
#include "Cursor.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "Texture2D.h"

#include "DebugNew.h"

static std::string shapeNames[] =
{
    "normal",
    "resizevertical",
    "resizediagonal_topright",
    "resizehorizontal",
    "resizediagonal_topleft",
    "acceptdrop",
    "rejectdrop"
};

Cursor::Cursor(const std::string& name) :
    BorderImage(name),
    mShape(CS_NORMAL)
{
    // Show on top of all other UI elements
    mPriority = M_MAX_INT;
    
    for (unsigned i = 0; i < CS_MAX_SHAPES; ++i)
    {
        CursorShapeData& data = mShapeData[i];
        data.mImageRect = IntRect::sZero;
        data.mHotSpot = IntVector2::sZero;
    }
}

Cursor::~Cursor()
{
}

void Cursor::setStyle(const XMLElement& element, ResourceCache* cache)
{
    UIElement::setStyle(element, cache);
    
    XMLElement shapeElem = element.getChildElement("shape");
    while (shapeElem)
    {
        CursorShape shape = (CursorShape)getIndexFromStringList(shapeElem.getStringLower("name"), shapeNames, 7, 0);
        defineShape(shape, cache->getResource<Texture2D>(shapeElem.getString("texture")), shapeElem.getIntRect("imagerect"),
            shapeElem.getIntVector2("hotspot"));
        shapeElem = shapeElem.getNextElement("shape");
    }
}

void Cursor::defineShape(CursorShape shape, Texture* texture, const IntRect& imageRect, const IntVector2& hotSpot)
{
    CursorShapeData& data = mShapeData[shape];
    data.mTexture = texture;
    data.mImageRect = imageRect;
    data.mHotSpot = hotSpot;
    
    // Reset current shape if it was edited
    if (shape == mShape)
        setShape(mShape);
}

void Cursor::setShape(CursorShape shape)
{
    mShape = shape;
    
    CursorShapeData& data = mShapeData[mShape];
    mTexture = data.mTexture;
    mImageRect = data.mImageRect;
    setSize(data.mImageRect.mRight - data.mImageRect.mLeft, data.mImageRect.mBottom - data.mImageRect.mTop);
}

void Cursor::getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor)
{
    unsigned initialSize = quads.size();
    const IntVector2& offset = mShapeData[mShape].mHotSpot;
    
    BorderImage::getBatches(batches, quads, currentScissor);
    for (unsigned i = initialSize; i < quads.size(); ++i)
    {
        quads[i].mLeft -= offset.mX;
        quads[i].mTop -= offset.mY;
        quads[i].mRight -= offset.mX;
        quads[i].mBottom -= offset.mY;
    }
}
