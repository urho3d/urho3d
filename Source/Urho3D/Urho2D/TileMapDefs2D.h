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

#include "../Container/RefCounted.h"
#include "../Urho2D/Sprite2D.h"

namespace Urho3D
{

class XMLElement;

/// Orientation.
enum Orientation2D
{
    /// Orthogonal.
    O_ORTHOGONAL = 0,
    /// Isometric.
    O_ISOMETRIC,
    /// Staggered.
    O_STAGGERED
};

/// Tile map infomation.
struct URHO3D_API TileMapInfo2D
{
    /// Orientation.
    Orientation2D orientation_;
    /// Width.
    int width_;
    /// Height.
    int height_;
    /// Tile width.
    float tileWidth_;
    /// Tile height.
    float tileHeight_;

    /// Return map width.
    float GetMapWidth() const;
    /// return map height.
    float GetMapHeight() const;
    /// Convert tmx position to Urho position.
    Vector2 ConvertPosition(const Vector2& position) const;
    /// Convert tile index to position.
    Vector2 TileIndexToPosition(int x, int y) const;
    /// Convert position to tile index, if out of map return false.
    bool PositionToTileIndex(int& x, int& y, const Vector2& positon) const;
};

/// Tile map layer type.
enum TileMapLayerType2D
{
    /// Tile layer.
    LT_TILE_LAYER = 0,
    /// Object group.
    LT_OBJECT_GROUP,
    /// Image layer.
    LT_IMAGE_LAYER,
    /// Invalid.
    LT_INVALID = 0xffff
};

/// Tile map object type.
enum TileMapObjectType2D
{
    /// Rectangle.
    OT_RECTANGLE = 0,
    /// Ellipse.
    OT_ELLIPSE,
    /// Polygon.
    OT_POLYGON,
    /// Polyline.
    OT_POLYLINE,
    /// Tile.
    OT_TILE,
    /// Invalid.
    OT_INVALID = 0xffff
};

/// Property set.
class URHO3D_API PropertySet2D : public RefCounted
{
public:
    PropertySet2D();
    virtual ~PropertySet2D();

    /// Load from XML element.
    void Load(const XMLElement& element);
    /// Return has property.
    bool HasProperty(const String& name) const;
    /// Return property value.
    const String& GetProperty(const String& name) const;

protected:
    /// Property name to property value mapping.
    HashMap<String, String> nameToValueMapping_;
};

/// Tile define.
class URHO3D_API Tile2D : public RefCounted
{
public:
    /// Construct.
    Tile2D();

    /// Return gid.
    int GetGid() const { return gid_; }
    /// Return sprite.
    Sprite2D* GetSprite() const;
    /// Return has property.
    bool HasProperty(const String& name) const;
    /// Return property.
    const String& GetProperty(const String& name) const;

private:
    friend class TmxTileLayer2D;

    /// Gid.
    int gid_;
    /// Sprite.
    SharedPtr<Sprite2D> sprite_;
    /// Property set.
    SharedPtr<PropertySet2D> propertySet_;
};

/// Tile map object.
class URHO3D_API TileMapObject2D : public RefCounted
{
public:
    TileMapObject2D();

    /// Return type.
    TileMapObjectType2D GetObjectType() const { return objectType_; }
    /// Return name.
    const String& GetName() const { return name_; }
    /// Return type.
    const String& GetType() const { return type_; }
    /// Return position.
    const Vector2& GetPosition() const { return position_; }
    /// Return size (for rectangle and ellipse).
    const Vector2& GetSize() const { return size_; }
    /// Return number of points (use for script).
    unsigned GetNumPoints() const;
    /// Return point at index (use for script).
    const Vector2& GetPoint(unsigned index) const;
    /// Return tile Gid.
    int GetTileGid() const { return gid_; }
    /// Return tile sprite.
    Sprite2D* GetTileSprite() const;
    /// Return has property.
    bool HasProperty(const String& name) const;
    /// Return property value.
    const String& GetProperty(const String& name) const;

private:
    friend class TmxObjectGroup2D;

    /// Object type.
    TileMapObjectType2D objectType_;
    /// Name.
    String name_;
    /// Type.
    String type_;
    /// Position.
    Vector2 position_;
    /// Size (for rectangle and ellipse).
    Vector2 size_;
    /// Points(for polygon and polyline).
    Vector<Vector2> points_;
    /// Gid (for tile).
    int gid_;
    /// Sprite (for tile).
    SharedPtr<Sprite2D> sprite_;
    /// Property set.
    SharedPtr<PropertySet2D> propertySet_;
};

}
