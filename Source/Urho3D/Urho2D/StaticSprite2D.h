// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set sprite.
    /// @property
    void SetSprite(Sprite2D* sprite);
    /// Set draw rectangle.
    /// @property
    void SetDrawRect(const Rect &rect);
    /// Set texture rectangle.
    /// @property
    void SetTextureRect(const Rect &rect);
    /// Set blend mode.
    /// @property
    void SetBlendMode(BlendMode blendMode);
    /// Set flip.
    void SetFlip(bool flipX, bool flipY, bool swapXY = false);
    /// Set flip X.
    /// @property
    void SetFlipX(bool flipX);
    /// Set flip Y.
    /// @property
    void SetFlipY(bool flipY);
    /// Set swap X and Y.
    /// @property
    void SetSwapXY(bool swapXY);
    /// Set color.
    /// @property
    void SetColor(const Color& color);
    /// Set alpha.
    /// @property
    void SetAlpha(float alpha);
    /// Set whether to use custom-defined hot spot.
    /// @property
    void SetUseHotSpot(bool useHotSpot);
    /// Set whether to use custom-defined draw rectangle.
    /// @property
    void SetUseDrawRect(bool useDrawRect);
    /// Set whether to use custom-defined texture rectangle.
    /// @property
    void SetUseTextureRect(bool useTextureRect);
    /// Set hot spot.
    /// @property
    void SetHotSpot(const Vector2& hotspot);
    /// Set custom material.
    /// @property
    void SetCustomMaterial(Material* customMaterial);

    /// Return sprite.
    /// @property
    Sprite2D* GetSprite() const;

    /// Return draw rect.
    /// @property
    const Rect& GetDrawRect() const { return drawRect_; }

    /// Return texture rect.
    /// @property
    const Rect& GetTextureRect() const { return textureRect_; }

    /// Return blend mode.
    /// @property
    BlendMode GetBlendMode() const { return blendMode_; }

    /// Return flip X.
    /// @property
    bool GetFlipX() const { return flipX_; }

    /// Return flip Y.
    /// @property
    bool GetFlipY() const { return flipY_; }

    /// Return swap X and Y.
    /// @property
    bool GetSwapXY() const { return swapXY_; }

    /// Return color.
    /// @property
    const Color& GetColor() const { return color_; }

    /// Return alpha.
    /// @property
    float GetAlpha() const { return color_.a_; }

    /// Return whether to use custom-defined hot spot.
    /// @property
    bool GetUseHotSpot() const { return useHotSpot_; }

    /// Return whether to use custom-defined draw rectangle.
    /// @property
    bool GetUseDrawRect() const { return useDrawRect_; }

    /// Return whether to use custom-defined texture rectangle.
    /// @property
    bool GetUseTextureRect() const { return useTextureRect_; }

    /// Return hot spot.
    /// @property
    const Vector2& GetHotSpot() const { return hotSpot_; }

    /// Return custom material.
    /// @property
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
