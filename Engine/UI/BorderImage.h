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

#ifndef UI_BORDERIMAGE_H
#define UI_BORDERIMAGE_H

#include "UIElement.h"

class Texture;
class Texture2D;

//! An image UI element with optional border
class BorderImage : public UIElement
{
    DEFINE_TYPE(BorderImage);
    
    using UIElement::setStyle;
    
public:
    //! Construct with name
    BorderImage(const std::string& name = std::string());
    //! Destruct
    virtual ~BorderImage();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! Return UI rendering batches
    virtual void getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor);
    
    //! Set textures
    void setTexture(Texture* texture);
    //! Set part of texture to use as the image
    void setImageRect(const IntRect& rect);
    //! Set part of texture to use as the image
    void setImageRect(int left, int top, int right, int bottom);
    //! Use whole texture as the image
    void setFullImageRect();
    //! Set image border dimensions
    void setBorder(const IntRect& rect);
    //! Set image border dimensions
    void setBorder(int left, int top, int right, int bottom);
    //! Set offset to image rectangle used on hover
    void setHoverOffset(const IntVector2& offset);
    //! Set offset to image rectangle used on hover
    void setHoverOffset(int x, int y);
    
    //! Return texture
    Texture* getTexture() const { return mTexture; }
    //! Return image rectangle
    const IntRect& getImageRect() const { return mImageRect; }
    //! Return image border dimensions
    const IntRect& getBorder() const { return mBorder; }
    //! Return offset to image rectangle used on hover
    const IntVector2& getHoverOffset() const { return mHoverOffset; }
    
protected:
    //! Return UI rendering batches with offset to image rectangle
    void getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor, const IntVector2& offset);
    
    //! Texture
    SharedPtr<Texture> mTexture;
    //! Image rectangle
    IntRect mImageRect;
    //! Image border dimensions
    IntRect mBorder;
    //! Offset to image rectangle on hover
    IntVector2 mHoverOffset;
};

#endif // UI_BORDERIMAGE_H
