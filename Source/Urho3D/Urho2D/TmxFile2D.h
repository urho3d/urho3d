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

#include "../Resource/Resource.h"
#include "../Urho2D/TileMapDefs2D.h"

namespace Urho3D
{

class Sprite2D;
class Texture2D;
class TmxFile2D;
class XMLElement;
class XMLFile;

/// Tmx layer.
class TmxLayer2D : public RefCounted
{
public:
    TmxLayer2D(TmxFile2D* tmxFile, TileMapLayerType2D type);
    ~TmxLayer2D() override = default;

    /// Return tmx file.
    TmxFile2D* GetTmxFile() const;

    /// Return type.
    TileMapLayerType2D GetType() const { return type_; }

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
    /// Load property set.
    void LoadPropertySet(const XMLElement& element);

    /// Tmx file.
    WeakPtr<TmxFile2D> tmxFile_;
    /// Layer type.
    TileMapLayerType2D type_;
    /// Name.
    String name_;
    /// Width.
    int width_{};
    /// Height.
    int height_{};
    /// Visible.
    bool visible_{};
    /// Property set.
    SharedPtr<PropertySet2D> propertySet_;
};

/// Tmx tile layer.
class TmxTileLayer2D : public TmxLayer2D
{
public:
    explicit TmxTileLayer2D(TmxFile2D* tmxFile);

    /// Load from XML element.
    bool Load(const XMLElement& element, const TileMapInfo2D& info);
    /// Return tile.
    Tile2D* GetTile(int x, int y) const;

protected:
    /// Tiles.
    Vector<SharedPtr<Tile2D> > tiles_;
};

/// Tmx objects layer.
class TmxObjectGroup2D : public TmxLayer2D
{
public:
    explicit TmxObjectGroup2D(TmxFile2D* tmxFile);

    /// Load from XML element.
    bool Load(const XMLElement& element, const TileMapInfo2D& info);

    /// Store object.
    void StoreObject(const XMLElement& objectElem, const SharedPtr<TileMapObject2D>& object, const TileMapInfo2D& info, bool isTile = false);

    /// Return number of objects.
    unsigned GetNumObjects() const { return objects_.Size(); }

    /// Return tile map object at index.
    TileMapObject2D* GetObject(unsigned index) const;

private:
    /// Objects.
    Vector<SharedPtr<TileMapObject2D> > objects_;
};

/// Tmx image layer.
class TmxImageLayer2D : public TmxLayer2D
{
public:
    explicit TmxImageLayer2D(TmxFile2D* tmxFile);

    /// Load from XML element.
    bool Load(const XMLElement& element, const TileMapInfo2D& info);

    /// Return position.
    const Vector2& GetPosition() const { return position_; }

    /// Return source.
    const String& GetSource() const { return source_; }

    /// Return sprite.
    Sprite2D* GetSprite() const;

private:
    /// Position.
    Vector2 position_;
    /// Source.
    String source_;
    /// Sprite.
    SharedPtr<Sprite2D> sprite_;
};

/// Tile map file.
class URHO3D_API TmxFile2D : public Resource
{
    URHO3D_OBJECT(TmxFile2D, Resource);

public:
    /// Construct.
    explicit TmxFile2D(Context* context);
    /// Destruct.
    ~TmxFile2D() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    bool BeginLoad(Deserializer& source) override;
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    bool EndLoad() override;

    /// Set Tilemap information.
    bool SetInfo(Orientation2D orientation, int width, int height, float tileWidth, float tileHeight);

    /// Add layer at index, if index > number of layers then append to end.
    void AddLayer(unsigned index, TmxLayer2D *layer);

    /// Append layer to end.
    void AddLayer(Urho3D::TmxLayer2D* layer);

    /// Return Tilemap information.
    const TileMapInfo2D& GetInfo() const { return info_; }

    /// Return tile sprite by gid, if not exist return 0.
    Sprite2D* GetTileSprite(unsigned gid) const;

    /// Return tile collision shapes for a given gid.
    Vector<SharedPtr<TileMapObject2D> > GetTileCollisionShapes(unsigned gid) const;

    /// Return tile property set by gid, if not exist return 0.
    PropertySet2D* GetTilePropertySet(unsigned gid) const;

    /// Return number of layers.
    unsigned GetNumLayers() const { return layers_.Size(); }

    /// Return layer at index.
    const TmxLayer2D* GetLayer(unsigned index) const;

    /// Set texture edge offset for all sprites, in pixels.
    void SetSpriteTextureEdgeOffset(float offset);

    /// Return texture edge offset, in pixels.
    float GetSpriteTextureEdgeOffset() const { return edgeOffset_; }

private:
    /// Load TSX file.
    SharedPtr<XMLFile> LoadTSXFile(const String& source);
    /// Load tile set.
    bool LoadTileSet(const XMLElement& element);

    /// XML file used during loading.
    SharedPtr<XMLFile> loadXMLFile_;
    /// TSX name to XML file mapping.
    HashMap<String, SharedPtr<XMLFile> > tsxXMLFiles_;
    /// Tile map information.
    TileMapInfo2D info_{};
    /// Gid to tile sprite mapping.
    HashMap<unsigned, SharedPtr<Sprite2D> > gidToSpriteMapping_;
    /// Gid to tile property set mapping.
    HashMap<unsigned, SharedPtr<PropertySet2D> > gidToPropertySetMapping_;
    /// Gid to tile collision shape mapping.
    HashMap<unsigned, Vector<SharedPtr<TileMapObject2D> > > gidToCollisionShapeMapping_;
    /// Layers.
    Vector<TmxLayer2D*> layers_;
    /// Texture edge offset.
    float edgeOffset_;
};

}
