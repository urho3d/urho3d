//
// Copyright (c) 2008-2015 the Urho3D project.
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

#pragma once

#include "../Graphics/GraphicsDefs.h"
#include "../UI/UIElement.h"

namespace Urho3D
{

class Texture;
class Texture2D;

/// %Image %UI element with optional border.
class URHO3D_API BorderImage : public UIElement
{
    URHO3D_OBJECT(BorderImage, UIElement);

public:
    /// Construct.
    BorderImage(Context* context);
    /// Destruct.
    virtual ~BorderImage();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Return UI rendering batches.
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);

    /// Set texture.
    void SetTexture(Texture* texture);
    /// Set part of texture to use as the image.
    void SetImageRect(const IntRect& rect);
    /// Use whole texture as the image.
    void SetFullImageRect();
    /// Set border dimensions on the screen.
    void SetBorder(const IntRect& rect);
    /// Set border dimensions on the image. If zero (default) uses the screen dimensions, resulting in pixel-perfect borders.
    void SetImageBorder(const IntRect& rect);
    /// Set offset to image rectangle used on hover.
    void SetHoverOffset(const IntVector2& offset);
    /// Set offset to image rectangle used on hover.
    void SetHoverOffset(int x, int y);
    /// Set blend mode.
    void SetBlendMode(BlendMode mode);
    /// Set tiled mode.
    void SetTiled(bool enable);

    /// Return texture.
    Texture* GetTexture() const { return texture_; }

    /// Return image rectangle.
    const IntRect& GetImageRect() const { return imageRect_; }

    /// Return border screen dimensions.
    const IntRect& GetBorder() const { return border_; }

    /// Return border image dimensions. Zero rect uses border screen dimensions.
    const IntRect& GetImageBorder() const { return imageBorder_; }

    /// Return offset to image rectangle used on hover.
    const IntVector2& GetHoverOffset() const { return hoverOffset_; }

    /// Return blend mode.
    BlendMode GetBlendMode() const { return blendMode_; }

    /// Return whether is tiled.
    bool IsTiled() const { return tiled_; }

    /// Set texture attribute.
    void SetTextureAttr(const ResourceRef& value);
    /// Return texture attribute.
    ResourceRef GetTextureAttr() const;

protected:
    /// Return UI rendering batches with offset to image rectangle.
    void GetBatches
        (PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor, const IntVector2& offset);

    /// Texture.
    SharedPtr<Texture> texture_;
    /// Image rectangle.
    IntRect imageRect_;
    /// Border dimensions on screen.
    IntRect border_;
    /// Border dimensions on the image.
    IntRect imageBorder_;
    /// Offset to image rectangle on hover.
    IntVector2 hoverOffset_;
    /// Blend mode flag.
    BlendMode blendMode_;
    /// Tiled flag.
    bool tiled_;
};

}
