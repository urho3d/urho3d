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

#ifndef UI_CURSOR_H
#define UI_CURSOR_H

#include "BorderImage.h"

enum CursorShape
{
    CS_NORMAL = 0,
    CS_RESIZEVERTICAL,
    CS_RESIZEDIAGONAL_TOPRIGHT,
    CS_RESIZEHORIZONTAL,
    CS_RESIZEDIAGONAL_TOPLEFT,
    CS_ACCEPTDROP,
    CS_REJECTDROP,
    CS_MAX_SHAPES
};

//! Cursor image and hotspot information
struct CursorShapeData
{
    SharedPtr<Texture> mTexture;
    IntRect mImageRect;
    IntVector2 mHotSpot;
};

//! An image with hotspot coordinates
class Cursor : public BorderImage
{
    DEFINE_TYPE(Cursor);
    
    using UIElement::setStyle;
    
public:
    //! Construct with name
    Cursor(const std::string& name = std::string());
    //! Destruct
    virtual ~Cursor();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! Return UI rendering batches
    virtual void getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor);
    
    //! Define a shape
    void defineShape(CursorShape shape, Texture* texture, const IntRect& imageRect, const IntVector2& hotSpot);
    //! Set shape
    void setShape(CursorShape shape);
    
    //! Get current shape
    CursorShape getShape() const { return mShape; }
    
protected:
    //! Current shape index
    CursorShape mShape;
    //! Shape datas
    CursorShapeData mShapeData[CS_MAX_SHAPES];
};

#endif // UI_CURSOR_H
