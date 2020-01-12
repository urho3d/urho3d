//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Urho2D/Drawable2D.h"

namespace Urho3D
{

class Sprite2D;

/// Static sprite component.
class URHO3D_API StaticSprite2D : public Drawable2D
{
    URHO3D_OBJECT(StaticSprite2D, Drawable2D);

public:
    /// Construct.
    explicit StaticSprite2D(Context* context);
    /// Destruct.
    ~StaticSprite2D() override;
    /// Register object factory. Drawable2D must be registered first.
    static void RegisterObject(Context* context);

    /// Set sprite.
    void SetSprite(Sprite2D* sprite);
    /// Set draw rectangle.
    void SetDrawRect(const Rect &rect);
    /// Set texture rectangle.
    void SetTextureRect(const Rect &rect);
    /// Set blend mode.
    void SetBlendMode(BlendMode blendMode);
    /// Set flip.
    void SetFlip(bool flipX, bool flipY, bool swapXY = false);
    /// Set flip X.
    void SetFlipX(bool flipX);
    /// Set flip Y.
    void SetFlipY(bool flipY);
    /// Set swap X and Y.
    void SetSwapXY(bool swapXY);
    /// Set color.
    void SetColor(const Color& color);
    /// Set alpha.
    void SetAlpha(float alpha);
    /// Set whether to use custom-defined hot spot.
    void SetUseHotSpot(bool useHotSpot);
    /// Set whether to use custom-defined draw rectangle.
    void SetUseDrawRect(bool useDrawRect);
    /// Set whether to use custom-defined texture rectangle.
    void SetUseTextureRect(bool useTextureRect);
    /// Set hot spot.
    void SetHotSpot(const Vector2& hotspot);
    /// Set custom material.
    void SetCustomMaterial(Material* customMaterial);

    /// Return sprite.
    Sprite2D* GetSprite() const;

    /// Return draw rect.
    const Rect& GetDrawRect() const { return drawRect_; }

    /// Return texture rect.
    const Rect& GetTextureRect() const { return textureRect_; }

    /// Return blend mode.
    BlendMode GetBlendMode() const { return blendMode_; }

    /// Return flip X.
    bool GetFlipX() const { return flipX_; }

    /// Return flip Y.
    bool GetFlipY() const { return flipY_; }

    /// Return swap X and Y.
    bool GetSwapXY() const { return swapXY_; }

    /// Return color.
    const Color& GetColor() const { return color_; }

    /// Return alpha.
    float GetAlpha() const { return color_.a_; }

    /// Return whether to use custom-defined hot spot.
    bool GetUseHotSpot() const { return useHotSpot_; }

    /// Return whether to use custom-defined draw rectangle.
    bool GetUseDrawRect() const { return useDrawRect_; }

    /// Return whether to use custom-defined texture rectangle.
    bool GetUseTextureRect() const { return useTextureRect_; }

    /// Return hot spot.
    const Vector2& GetHotSpot() const { return hotSpot_; }

    /// Return custom material.
    Material* GetCustomMaterial() const;

    /// Set sprite attribute.
    void SetSpriteAttr(const ResourceRef& value);
    /// Return sprite attribute.
    ResourceRef GetSpriteAttr() const;
    /// Set custom material attribute.
    void SetCustomMaterialAttr(const ResourceRef& value);
    /// Return custom material attribute.
    ResourceRef GetCustomMaterialAttr() const;


protected:

    /// Handle scene being assigned.
    void OnSceneSet(Scene* scene) override;
    /// Recalculate the world-space bounding box.
    void OnWorldBoundingBoxUpdate() override;
    /// Handle draw order changed.
    void OnDrawOrderChanged() override;
    /// Update source batches.
    void UpdateSourceBatches() override;
    /// Update material.
    void UpdateMaterial();
    /// Update drawRect.
    void UpdateDrawRect();

    /// Sprite.
    SharedPtr<Sprite2D> sprite_;
    /// Blend mode.
    BlendMode blendMode_;
    /// Flip X.
    bool flipX_;
    /// Flip Y.
    bool flipY_;
    /// Swap X and Y.
    bool swapXY_;
    /// Color.
    Color color_;
    /// Use hot spot flag.
    bool useHotSpot_;
    /// Use draw rectangle flag.
    bool useDrawRect_;
    /// Use texture rectangle flag.
    bool useTextureRect_;
    /// Hot spot.
    Vector2 hotSpot_;
    /// Draw rectangle.
    Rect drawRect_;
    /// Texture rectangle.
    Rect textureRect_;
    /// Custom material.
    SharedPtr<Material> customMaterial_;
};

}
