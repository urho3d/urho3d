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

namespace Urho3D
{

class Sprite2D;
class Texture2D;
class TmxFile2D;
class XMLElement;
class XMLFile;

/// Tile map layer.
struct TmxLayer2D
{
    /// Tmx file.
    WeakPtr<TmxFile2D> tmxFile_;
    /// Name.
    String name_;
    /// Width.
    int width_;
    /// Height.
    int height_;
    /// Tiles.
    PODVector<int> tiles_;
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
    int GetTileWidth() const { return tileWidth_; }
    /// Return tile height.
    int GetTileHeight() const { return tileHeight_; }
    /// Return number of layers.
    unsigned GetNumLayers() const { return layers_.Size(); }
    /// Return layer at index.
    const TmxLayer2D* GetLayer(unsigned index) const;
    /// Return tile sprite by gid.
    Sprite2D* GetTileSprite(int gid) const;

private:
    /// Load tile set.
    bool LoadTileSet(const XMLElement& element);
    /// Load layer.
    bool LoadLayer(const XMLElement& element);
    
    /// XML file used during loading.
    SharedPtr<XMLFile> loadXMLFile_;
    /// Width.
    int width_;
    /// Height.
    int height_;
    /// Tile width.
    int tileWidth_;
    /// Tile height.
    int tileHeight_;
    /// Textures.
    Vector<SharedPtr<Texture2D> > textures_;
    /// Gid to tile sprite mapping.
    HashMap<int, SharedPtr<Sprite2D> > tileSprites_;
    /// Layers.
    Vector<TmxLayer2D> layers_;
};

}

