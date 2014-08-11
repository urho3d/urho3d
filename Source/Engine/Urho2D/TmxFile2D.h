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
#include "TileMapDefs2D.h"

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
    virtual ~TmxLayer2D();

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
    int width_;
    /// Height.
    int height_;
    /// Visible.
    bool visible_;
    /// Property set.
    SharedPtr<PropertySet2D> propertySet_;
};

/// Tmx tile layer.
class TmxTileLayer2D : public TmxLayer2D
{
public:
    TmxTileLayer2D(TmxFile2D* tmxFile);

    /// Load from XML element.
    bool Load(const XMLElement& element);
    /// Return tile.
    Tile2D* GetTile(int x, int y) const;

protected:
    /// Tile.
    Vector<SharedPtr<Tile2D> > tiles_;
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
    /// Return source.
    const String& GetSource() const { return source_; }
    /// Return sprite.
    Sprite2D* GetSprite() const;
    
private:
    /// Source.
    String source_;
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

    /// Return width in tiles.
    int GetWidth() const { return width_; }
    /// Return height in tiles.
    int GetHeight() const { return height_; }
    /// Return tile width.
    float GetTileWidth() const { return tileWidth_; }
    /// Return tile height.
    float GetTileHeight() const { return tileHeight_; }
    /// Return tile sprite by gid, if not exist return 0.
    Sprite2D* GetTileSprite(int gid) const;
    /// Return tile property set by gid, if not exist return 0.
    PropertySet2D* GetTilePropertySet(int gid) const;
    /// Return number of layers.
    unsigned GetNumLayers() const { return layers_.Size(); }
    /// Return layer at index.
    const TmxLayer2D* GetLayer(unsigned index) const;

private:
   /// Load tile set.
    bool LoadTileSet(const XMLElement& element);
    
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
    HashMap<int, SharedPtr<Sprite2D> > gidToSpriteMapping_;
    /// Gid to tile property set mapping.
    HashMap<int, SharedPtr<PropertySet2D> > gidToPropertySetMapping_;
    /// Layers.
    Vector<TmxLayer2D*> layers_;
};

}

