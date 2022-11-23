// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Resource/Resource.h"
#include "../Urho2D/Urho2D.h"

namespace Urho3D
{

class SpriteSheet2D;
class Texture2D;

/// Sprite.
class URHO3D_API Sprite2D : public Resource
{
    URHO3D_OBJECT(Sprite2D, Resource);

public:
    /// Construct.
    explicit Sprite2D(Context* context);
    /// Destruct.
    ~Sprite2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    bool BeginLoad(Deserializer& source) override;
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    bool EndLoad() override;

    /// Set texture.
    /// @property
    void SetTexture(Texture2D* texture);
    /// Set rectangle.
    /// @property
    void SetRectangle(const IntRect& rectangle);
    /// Set hot spot.
    /// @property
    void SetHotSpot(const Vector2& hotSpot);
    /// Set offset.
    /// @property
    void SetOffset(const IntVector2& offset);
    /// Set texture edge offset in pixels. This affects the left/right and top/bottom edges equally to prevent edge sampling artifacts. Default 0.
    /// @property
    void SetTextureEdgeOffset(float offset);
    /// Set sprite sheet.
    void SetSpriteSheet(SpriteSheet2D* spriteSheet);

    /// Return texture.
    /// @property
    Texture2D* GetTexture() const { return texture_; }

    /// Return rectangle.
    /// @property
    const IntRect& GetRectangle() const { return rectangle_; }

    /// Return hot spot.
    /// @property
    const Vector2& GetHotSpot() const { return hotSpot_; }

    /// Return offset.
    /// @property
    const IntVector2& GetOffset() const { return offset_; }

    /// Return texture edge offset.
    /// @property
    float GetTextureEdgeOffset() const { return edgeOffset_; }

    /// Return sprite sheet.
    SpriteSheet2D* GetSpriteSheet() const { return spriteSheet_; }


    /// Return draw rectangle.
    bool GetDrawRectangle(Rect& rect, bool flipX = false, bool flipY = false) const;
    /// Return draw rectangle with custom hot spot.
    bool GetDrawRectangle(Rect& rect, const Vector2& hotSpot, bool flipX = false, bool flipY = false) const;
    /// Return texture rectangle.
    bool GetTextureRectangle(Rect& rect, bool flipX = false, bool flipY = false) const;

    /// Save sprite to ResourceRef.
    static ResourceRef SaveToResourceRef(Sprite2D* sprite);
    /// Load sprite from ResourceRef.
    static Sprite2D* LoadFromResourceRef(Object* object, const ResourceRef& value);

private:
    /// Texture.
    SharedPtr<Texture2D> texture_;
    /// Rectangle.
    IntRect rectangle_;
    /// Hot spot.
    Vector2 hotSpot_;
    /// Offset (for trimmed sprite).
    IntVector2 offset_;
    /// Sprite sheet.
    WeakPtr<SpriteSheet2D> spriteSheet_;
    /// Texture used while loading.
    SharedPtr<Texture2D> loadTexture_;
    /// Offset to fix texture edge bleeding.
    float edgeOffset_;
};

}
