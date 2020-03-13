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

#include "../Precompiled.h"

#include "../Resource/XMLElement.h"
#include "../Resource/JSONFile.h"
#include "../Urho2D/TileMapDefs2D.h"

#include "../DebugNew.h"

namespace Urho3D
{
extern URHO3D_API const float PIXEL_SIZE;

float TileMapInfo2D::GetMapWidth() const
{
    return width_ * tileWidth_;
}

float TileMapInfo2D::GetMapHeight() const
{
    if (orientation_ == O_STAGGERED)
        return (height_ + 1) * 0.5f * tileHeight_;
    else if (orientation_ == O_HEXAGONAL)
        return (height_) * 0.5f * (tileHeight_ + tileHeight_ * 0.5f);
    else
        return height_ * tileHeight_;
}

Vector2 TileMapInfo2D::ConvertPosition(const Vector2& position) const
{
    switch (orientation_)
    {
    case O_ISOMETRIC:
        {
            Vector2 index = position * PIXEL_SIZE / tileHeight_;
            return Vector2((width_ + index.x_ - index.y_) * tileWidth_ * 0.5f,
                (height_ * 2.0f - index.x_ - index.y_) * tileHeight_ * 0.5f);
        }

    case O_STAGGERED:
        return Vector2(position.x_ * PIXEL_SIZE, GetMapHeight() - position.y_ * PIXEL_SIZE);

    case O_HEXAGONAL:
    case O_ORTHOGONAL:
    default:
        return Vector2(position.x_ * PIXEL_SIZE, GetMapHeight() - position.y_ * PIXEL_SIZE);
    }
}

Vector2 TileMapInfo2D::TileIndexToPosition(int x, int y) const
{
    switch (orientation_)
    {
    case O_ISOMETRIC:
        return Vector2((width_ + x - y - 1) * tileWidth_ * 0.5f, (height_ * 2 - x - y - 2) * tileHeight_ * 0.5f);

    case O_STAGGERED:
        if (y % 2 == 0)
            return Vector2(x * tileWidth_, (height_ - 1 - y) * 0.5f * tileHeight_);
        else
            return Vector2((x + 0.5f) * tileWidth_, (height_ - 1 - y) * 0.5f * tileHeight_);

    case O_HEXAGONAL:
        if (y % 2 == 0)
            return Vector2(x * tileWidth_, (height_ - 1 - y) * 0.75f * tileHeight_);
        else
            return Vector2((x + 0.5f) * tileWidth_, (height_ - 1 - y)  * 0.75f * tileHeight_);

    case O_ORTHOGONAL:
    default:
        return Vector2(x * tileWidth_, (height_ - 1 - y) * tileHeight_);
    }
}

bool TileMapInfo2D::PositionToTileIndex(int& x, int& y, const Vector2& position) const
{
    switch (orientation_)
    {
    case O_ISOMETRIC:
    {
        float ox = position.x_ / tileWidth_ - height_ * 0.5f;
        float oy = position.y_ / tileHeight_;

        x = (int)(width_ - oy + ox);
        y = (int)(height_ - oy - ox);
    }
        break;

    case O_STAGGERED:
        y = (int)(height_ - 1 - position.y_ * 2.0f / tileHeight_);
        if (y % 2 == 0)
            x = (int)(position.x_ / tileWidth_);
        else
            x = (int)(position.x_ / tileWidth_ - 0.5f);

        break;

    case O_HEXAGONAL:
        y = (int)(height_ - 1 - position.y_ / 0.75f / tileHeight_);
        if (y % 2 == 0)
            x = (int)(position.x_ / tileWidth_);
        else
            x = (int)(position.x_ / tileWidth_ - 0.75f);
        break;

    case O_ORTHOGONAL:
    default:
        x = (int)(position.x_ / tileWidth_);
        y = height_ - 1 - int(position.y_ / tileHeight_);
        break;

    }

    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

PropertySet2D::PropertySet2D() = default;

PropertySet2D::~PropertySet2D() = default;

void PropertySet2D::Load(const XMLElement& element)
{
    assert(element.GetName() == "properties");
    for (XMLElement propertyElem = element.GetChild("property"); propertyElem; propertyElem = propertyElem.GetNext("property"))
        nameToValueMapping_[propertyElem.GetAttribute("name")] = propertyElem.GetAttribute("value");
}

bool PropertySet2D::HasProperty(const String& name) const
{
    return nameToValueMapping_.Find(name) != nameToValueMapping_.End();
}

const String& PropertySet2D::GetProperty(const String& name) const
{
    HashMap<String, String>::ConstIterator i = nameToValueMapping_.Find(name);
    if (i == nameToValueMapping_.End())
        return String::EMPTY;

    return i->second_;
}

Tile2D::Tile2D() :
    gid_(0)
{
}

Sprite2D* Tile2D::GetSprite() const
{
    return sprite_;
}

bool Tile2D::HasProperty(const String& name) const
{
    if (!propertySet_)
        return false;
    return propertySet_->HasProperty(name);
}

const String& Tile2D::GetProperty(const String& name) const
{
    if (!propertySet_)
        return String::EMPTY;

    return propertySet_->GetProperty(name);
}

TileMapObject2D::TileMapObject2D() = default;

unsigned TileMapObject2D::GetNumPoints() const
{
    return points_.Size();
}

const Vector2& TileMapObject2D::GetPoint(unsigned index) const
{
    if (index >= points_.Size())
        return Vector2::ZERO;

    return points_[index];
}

Sprite2D* TileMapObject2D::GetTileSprite() const
{
    return sprite_;
}

bool TileMapObject2D::HasProperty(const String& name) const
{
    if (!propertySet_)
        return false;
    return propertySet_->HasProperty(name);
}

const String& TileMapObject2D::GetProperty(const String& name) const
{
    if (!propertySet_)
        return String::EMPTY;
    return propertySet_->GetProperty(name);
}

}
