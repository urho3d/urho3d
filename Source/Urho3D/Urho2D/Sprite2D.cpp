// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../GraphicsAPI/Texture2D.h"
#include "../IO/Deserializer.h"
#include "../Resource/ResourceCache.h"
#include "../Urho2D/Drawable2D.h"
#include "../Urho2D/Sprite2D.h"
#include "../Urho2D/SpriteSheet2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

Sprite2D::Sprite2D(Context* context) :
    Resource(context),
    hotSpot_(0.5f, 0.5f),
    offset_(0, 0),
    edgeOffset_(M_LARGE_EPSILON)
{

}

Sprite2D::~Sprite2D() = default;

void Sprite2D::RegisterObject(Context* context)
{
    context->RegisterFactory<Sprite2D>();
}

bool Sprite2D::BeginLoad(Deserializer& source)
{
    if (GetName().Empty())
        SetName(source.GetName());

    // Reload
    if (texture_)
        loadTexture_ = texture_;
    else
    {
        loadTexture_ = new Texture2D(context_);
        loadTexture_->SetName(GetName());
    }
    // In case we're async loading, only call BeginLoad() for the texture (load image but do not upload to GPU)
    if (!loadTexture_->BeginLoad(source))
    {
        // Reload failed
        if (loadTexture_ == texture_)
            texture_.Reset();

        loadTexture_.Reset();
        return false;
    }

    return true;
}

bool Sprite2D::EndLoad()
{
    // Finish loading of the texture in the main thread
    bool success = false;
    if (loadTexture_ && loadTexture_->EndLoad())
    {
        success = true;
        SetTexture(loadTexture_);

        if (texture_)
            SetRectangle(IntRect(0, 0, texture_->GetWidth(), texture_->GetHeight()));
    }
    else
    {
        // Reload failed
        if (loadTexture_ == texture_)
            texture_.Reset();
    }

    loadTexture_.Reset();
    return success;
}

void Sprite2D::SetTexture(Texture2D* texture)
{
    texture_ = texture;
    // Ensure the texture doesn't have wrap addressing as that will cause bleeding bugs on the edges.
    // Could also choose border mode, but in that case a universally good border color (without alpha bugs)
    // would be hard to choose. Ideal is for the user to configure the texture parameters in its parameter
    // XML file.
    if (texture_->GetAddressMode(COORD_U) == ADDRESS_WRAP)
    {
        texture_->SetAddressMode(COORD_U, ADDRESS_CLAMP);
        texture_->SetAddressMode(COORD_V, ADDRESS_CLAMP);
    }
}

void Sprite2D::SetRectangle(const IntRect& rectangle)
{
    rectangle_ = rectangle;
}

void Sprite2D::SetHotSpot(const Vector2& hotSpot)
{
    hotSpot_ = hotSpot;
}

void Sprite2D::SetOffset(const IntVector2& offset)
{
    offset_ = offset;
}

void Sprite2D::SetTextureEdgeOffset(float offset)
{
    edgeOffset_ = offset;
}

void Sprite2D::SetSpriteSheet(SpriteSheet2D* spriteSheet)
{
    spriteSheet_ = spriteSheet;
}

bool Sprite2D::GetDrawRectangle(Rect& rect, bool flipX, bool flipY) const
{
    return GetDrawRectangle(rect, hotSpot_, flipX, flipY);
}

bool Sprite2D::GetDrawRectangle(Rect& rect, const Vector2& hotSpot, bool flipX, bool flipY) const
{
    if (rectangle_.Width() == 0 || rectangle_.Height() == 0)
        return false;

    float width = (float)rectangle_.Width() * PIXEL_SIZE;
    float height = (float)rectangle_.Height() * PIXEL_SIZE;

    float hotSpotX = flipX ? (1.0f - hotSpot.x_) : hotSpot.x_;
    float hotSpotY = flipY ? (1.0f - hotSpot.y_) : hotSpot.y_;

    rect.min_.x_ = -width * hotSpotX;
    rect.max_.x_ = width * (1.0f - hotSpotX);
    rect.min_.y_ = -height * hotSpotY;
    rect.max_.y_ = height * (1.0f - hotSpotY);

    return true;
}

bool Sprite2D::GetTextureRectangle(Rect& rect, bool flipX, bool flipY) const
{
    if (!texture_)
        return false;

    float invWidth = 1.0f / (float)texture_->GetWidth();
    float invHeight = 1.0f / (float)texture_->GetHeight();

    rect.min_.x_ = ((float)rectangle_.left_ + edgeOffset_) * invWidth;
    rect.max_.x_ = ((float)rectangle_.right_ - edgeOffset_) * invWidth;

    rect.min_.y_ = ((float)rectangle_.bottom_ - edgeOffset_) * invHeight;
    rect.max_.y_ = ((float)rectangle_.top_ + edgeOffset_) * invHeight;

    if (flipX)
        Swap(rect.min_.x_, rect.max_.x_);

    if (flipY)
        Swap(rect.min_.y_, rect.max_.y_);

    return true;
}

ResourceRef Sprite2D::SaveToResourceRef(Sprite2D* sprite)
{
    SpriteSheet2D* spriteSheet = nullptr;
    if (sprite)
        spriteSheet = sprite->GetSpriteSheet();

    if (!spriteSheet)
        return GetResourceRef(sprite, Sprite2D::GetTypeStatic());

    // Combine sprite sheet name and sprite name as resource name.
    return ResourceRef(spriteSheet->GetType(), spriteSheet->GetName() + "@" + sprite->GetName());
}

Sprite2D* Sprite2D::LoadFromResourceRef(Object* object, const ResourceRef& value)
{
    if (!object)
        return nullptr;

    auto* cache = object->GetSubsystem<ResourceCache>();

    if (value.type_ == Sprite2D::GetTypeStatic())
        return cache->GetResource<Sprite2D>(value.name_);

    if (value.type_ == SpriteSheet2D::GetTypeStatic())
    {
        // value.name_ include sprite sheet name and sprite name.
        Vector<String> names = value.name_.Split('@');
        if (names.Size() != 2)
            return nullptr;

        const String& spriteSheetName = names[0];
        const String& spriteName = names[1];

        auto* spriteSheet = cache->GetResource<SpriteSheet2D>(spriteSheetName);
        if (!spriteSheet)
            return nullptr;

        return spriteSheet->GetSprite(spriteName);
    }

    return nullptr;
}

}
