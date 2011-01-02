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

#ifndef UI_UIBATCH_H
#define UI_UIBATCH_H

#include "Color.h"
#include "Rect.h"
#include "RendererDefs.h"

#include <vector>

class PixelShader;
class Renderer;
class Texture;
class UIElement;
class VertexShader;

//! UI rendering quad
struct UIQuad
{
    //! Left coordinate
    int mLeft;
    //! Top coordinate
    int mTop;
    //! Right coordinate
    int mRight;
    //! Bottom coordinate
    int mBottom;
    //! Left texture coordinate
    short mLeftUV;
    //! Top texture coordinate
    short mTopUV;
    //! Right texture coordinate
    short mRightUV;
    //! Bottom texture coordinate
    short mBottomUV;
    //! Top left color
    unsigned mTopLeftColor;
    //! Top right color
    unsigned mTopRightColor;
    //! Bottom left color
    unsigned mBottomLeftColor;
    //! Bottom right color
    unsigned mBottomRightColor;
};

//! Describes an UI rendering draw call
class UIBatch
{
public:
    //! Construct with defaults
    UIBatch() :
        mTexture(0),
        mQuads(0),
        mQuadStart(0),
        mQuadCount(0)
    {
    }
    
    //! Begin adding quads
    void begin(std::vector<UIQuad>* quads);
    //! Add a quad
    void addQuad(UIElement& element, int x, int y, int width, int height, int texOffsetX, int texOffsetY);
    //! Add a quad with scaled texture
    void addQuad(UIElement& element, int x, int y, int width, int height, int texOffsetX, int texOffsetY, int texWidth, int texHeight);
    //! Merge with another batch
    bool merge(const UIBatch& batch);
    //! Draw
    void draw(Renderer* renderer, VertexShader* vs, PixelShader* ps) const;
    
    //! Add or merge a batch
    static void addOrMerge(const UIBatch& batch, std::vector<UIBatch>& batches);
    //! Return an interpolated color for an UI element
    static unsigned getInterpolatedColor(UIElement& element, int x, int y);
    
    //! Blending mode
    BlendMode mBlendMode;
    //! Scissor rectangle
    IntRect mScissor;
    //! Texture
    Texture* mTexture;
    //! Quads
    std::vector<UIQuad>* mQuads;
    //! Quad start index
    unsigned mQuadStart;
    //! Number of quads
    unsigned mQuadCount;
};

#endif // UI_UIBATCH_H
