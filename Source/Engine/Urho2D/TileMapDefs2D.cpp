//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "TileMapDefs2D.h"
#include "XMLElement.h"

#include "DebugNew.h"

namespace Urho3D
{

PropertySet2D::PropertySet2D()
{
}

PropertySet2D::~PropertySet2D()
{
}

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

TileObject2D::TileObject2D()
{
}

unsigned TileObject2D::GetNumPoints() const
{
    return points_.Size();
}

const Vector2& TileObject2D::GetPoint(unsigned index) const
{
    if (index >= points_.Size())
        return Vector2::ZERO;

    return points_[index];
}

Sprite2D* TileObject2D::GetTileSprite() const
{
    return sprite_;
}

bool TileObject2D::HasProperty(const String& name) const
{
    if (!propertySet_)
        return false;
    return propertySet_->HasProperty(name);
}

const String& TileObject2D::GetProperty(const String& name) const
{
    if (!propertySet_)
        return String::EMPTY;
    return propertySet_->GetProperty(name);
}

Vector2 IndexToPosition2D(int x, int y, const TileMapInfo2D& tileMapInfo)
{
    if (tileMapInfo.orientation_ == O_ORTHOGONAL)
        return Vector2((x + 0.5f) * tileMapInfo.tileWidth_, (y + 0.5f) * tileMapInfo.tileHeight_);
    else
        return Vector2(((x + y) + 0.5f) * tileMapInfo.tileWidth_ * 0.5f, (tileMapInfo.height_ - (x - y) + 0.5f) * tileMapInfo.tileHeight_ * 0.5f);
}

bool PositionToIndex2D(int& x, int& y, const Vector2& position, const TileMapInfo2D& tileMapInfo)
{
    if (tileMapInfo.orientation_ == O_ORTHOGONAL)
    {
        x = (int)(position.x_ / tileMapInfo.tileWidth_);
        y = (int)(position.y_ / tileMapInfo.tileHeight_);
    }
    else
    {
        int sum = (int)(position.x_ * 2.0f / tileMapInfo.tileWidth_);
        int dif = (int)(tileMapInfo.height_ - position.y_ * 2.0f / tileMapInfo.tileHeight_);
        x = (sum + dif) / 2;
        y = (sum - dif) / 2;
    }

    return x >= 0 && x < tileMapInfo.width_ && y >= 0 && y < tileMapInfo.height_;
}

}
