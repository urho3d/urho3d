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

#pragma once

#include "Resource.h"
#include "Ptr.h"
#include "Sprite2D.h"

namespace Urho3D
{

class Sprite2D;
class Texture2D;
class TmxFile2D;
class XMLElement;
class XMLFile;

/// Peroperies.
class URHO3D_API Properties2D : public RefCounted
{
public:
    Properties2D();
    virtual ~Properties2D();

    /// Load from XML element.
    void Load(const XMLElement& element);
    /// Return has property (use for script).
    bool HasProperty(const String& name) const;
    /// Return property value (use for script).
    const String& GetProperty(const String& name) const;

protected:
    /// Properties.
    HashMap<String, String> properties_;
};

/// Tile.
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
    /// Properties.
    SharedPtr<Properties2D> properties_;
};

/// Tile object type.
enum TileObjectType2D
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

/// Tile map object.
class URHO3D_API TileObject2D : public RefCounted
{
public:
    TileObject2D();;
    /// Return type.
    TileObjectType2D GetType() const { return type_; }
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
    TileObjectType2D type_;
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
    /// Properties.
    SharedPtr<Properties2D> properties_;
};

/// Tmx layer type.
enum TmxLayerType2D
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

/// Tmx layer.
class TmxLayer2D : public RefCounted
{
public:
    TmxLayer2D(TmxFile2D* tmxFile, TmxLayerType2D type);
    virtual ~TmxLayer2D();

    /// Return tmx file.
    TmxFile2D* GetTmxFile() const;
    /// Return type.
    TmxLayerType2D GetType() const { return type_; }
    /// Return name.
    const String& GetName() const { return name_; }
    /// Return width.
    int GetWidth() const { return width_; }
    /// Return height.
    int GetHeight() const { return height_; }
    /// Return is visible.
    bool IsVisible() const { return visible_; }
    /// Return has property (use for script).
    bool HasProperty(const String& name) const;
    /// Return property value (use for script).
    const String& GetProperty(const String& name) const;


protected:
    /// Load layer info.
    void LoadInfo(const XMLElement& element);
    /// Load properties.
    void LoadProperties(const XMLElement& element);

    /// Tmx file.
    WeakPtr<TmxFile2D> tmxFile_;
    /// Layer type.
    TmxLayerType2D type_;
    /// Name.
    String name_;
    /// Width.
    int width_;
    /// Height.
    int height_;
    /// Visible.
    bool visible_;
    /// Properties.
    SharedPtr<Properties2D> properties_;
};

/// Tmx tile layer.
class TmxTileLayer2D : public TmxLayer2D
{
public:
    TmxTileLayer2D(TmxFile2D* tmxFile);

    /// Load from xml element.
    bool Load(const XMLElement& element);
    /// Return tile.
    Tile2D* GetTile(int x, int y) const;
protected:
    /// Tile.
    Vector<SharedPtr<Tile2D> > tileGids_;
};

/// Tmx image layer.
class TmxObjectGroup2D : public TmxLayer2D
{
public:
    TmxObjectGroup2D(TmxFile2D* tmxFile);

    /// Load from XML element.
    bool Load(const XMLElement& element);
    /// Return number of objects.
    unsigned GetNumObjects() const { return objects_.Size(); }
    /// Return object at index.
    TileObject2D* GetObject(unsigned index) const;

private:
    /// Objects.
    Vector<SharedPtr<TileObject2D> > objects_;
};

/// Tmx image layer.
class TmxImageLayer2D : public TmxLayer2D
{
public:
    TmxImageLayer2D(TmxFile2D* tmxFile);

    /// Load from XML element.
    bool Load(const XMLElement& element);
    /// Return sprite.
    Sprite2D* GetSprite() const;
    
private:
    /// Sprite.
    SharedPtr<Sprite2D> sprite_;
};

/// Tile map file.
class URHO3D_API TmxFile2D : public Resource
{
    OBJECT(TmxFile2D);

public:
    /// Construct.
    TmxFile2D(Context* context);
    /// Destruct.
    virtual ~TmxFile2D();
    /// Register object factory. 
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    virtual bool EndLoad();

    /// Return width.
    int GetWidth() const { return width_; }
    /// Return height.
    int GetHeight() const { return height_; }
    /// Return tile width.
    float GetTileWidth() const { return tileWidth_; }
    /// Return tile height.
    float GetTileHeight() const { return tileHeight_; }
    /// Return tile sprite by gid.
    Sprite2D* GetTileSprite(int gid) const;
    /// Return tile properties by gid.
    Properties2D* GetTileProperties(int gid) const;
    /// Return number of layers.
    unsigned GetNumLayers() const { return layers_.Size(); }
    /// Return layer at index.
    const TmxLayer2D* GetLayer(unsigned index) const;
    /// Return layer by name.
    const TmxLayer2D* GetLayerByName(const String& name) const;

private:
   /// Load tile set.
    bool LoadTileSet(const XMLElement& element);
    /// Load layer.
    bool LoadLayer(const XMLElement& element);
    /// Load object group.
    bool LoadObjectGroup(const XMLElement& element);
    /// Load image layer.
    bool LoadImageLayer(const XMLElement& element);

    /// XML file used during loading.
    SharedPtr<XMLFile> loadXMLFile_;
    /// Width.
    int width_;
    /// Height.
    int height_;
    /// Tile width.
    float tileWidth_;
    /// Tile height.
    float tileHeight_;
    /// Tile set textures.
    Vector<SharedPtr<Texture2D> > tileSetTextures_;
    /// Gid to tile sprite mapping.
    HashMap<int, SharedPtr<Sprite2D> > tileSprites_;
    /// Gid to tile properties mapping.
    HashMap<int, SharedPtr<Properties2D> > tileProperties_;
    /// Layers.
    Vector<TmxLayer2D*> layers_;
};

}

