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
#include "Animation2D.h"
#include "Context.h"
#include "FileSystem.h"
#include "Log.h"
#include "ResourceCache.h"
#include "Sprite2D.h"
#include "Texture2D.h"
#include "TmxFile2D.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const float PIXEL_SIZE;

Properties2D::Properties2D()
{
}

Properties2D::~Properties2D()
{
}

void Properties2D::Load(const XMLElement& element)
{
    assert(element.GetName() == "properties");
    for (XMLElement propertyElem = element.GetChild("property"); propertyElem; propertyElem = propertyElem.GetNext("property"))
        properties_[propertyElem.GetAttribute("name")] = propertyElem.GetAttribute("value");
}

bool Properties2D::HasProperty(const String& name) const
{
    return properties_.Find(name) != properties_.End();
}

const String& Properties2D::GetProperty(const String& name) const
{
    HashMap<String, String>::ConstIterator i = properties_.Find(name);
    if (i == properties_.End())
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
    if (!properties_)
        return false;
    return properties_->HasProperty(name);
}

const String& Tile2D::GetProperty(const String& name) const
{
    if (!properties_)
        return String::EMPTY;

    return properties_->GetProperty(name);
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
    if (!properties_)
        return false;
    return properties_->HasProperty(name);
}

const String& TileObject2D::GetProperty(const String& name) const
{
    if (!properties_)
        return String::EMPTY;
    return properties_->GetProperty(name);
}

TmxLayer2D::TmxLayer2D(TmxFile2D* tmxFile, TmxLayerType2D type) :
    tmxFile_(tmxFile),
    type_(type)
{

}

TmxLayer2D::~TmxLayer2D()
{
}

TmxFile2D* TmxLayer2D::GetTmxFile() const
{
    return tmxFile_;
}

bool TmxLayer2D::HasProperty(const String& name) const
{
    if (!properties_)
        return false;
    return properties_->HasProperty(name);
}

const String& TmxLayer2D::GetProperty(const String& name) const
{
    if (!properties_)
        return String::EMPTY;
    return properties_->GetProperty(name);
}

void TmxLayer2D::LoadInfo(const XMLElement& element)
{
    name_ = element.GetAttribute("name");
    width_ = element.GetInt("width");
    height_ = element.GetInt("height");
    if (element.HasAttribute("visible"))
        visible_ = element.GetInt("visible") != 0;
    else
        visible_ = true;
}

void TmxLayer2D::LoadProperties(const XMLElement& element)
{
    properties_ = new Properties2D();
    properties_->Load(element);
}

TmxTileLayer2D::TmxTileLayer2D(TmxFile2D* tmxFile) :
    TmxLayer2D(tmxFile, LT_TILE_LAYER)
{
}

bool TmxTileLayer2D::Load(const XMLElement& element)
{
    LoadInfo(element);

    XMLElement dataElem = element.GetChild("data");
    if (!dataElem)
    {
        LOGERROR("Could not find data in layer");
        return false;
    }

    if (dataElem.HasAttribute("encoding") && dataElem.GetAttribute("encoding") != "xml")
    {
        LOGERROR("Encoding not support now");
        return false;
    }

    XMLElement tileElem = dataElem.GetChild("tile");
    tiles_.Resize(width_ * height_);

    // Flip y
    for (int y = height_ - 1; y >= 0; --y)
    {
        for (int x = 0; x < width_; ++x)
        {
            if (!tileElem)
                return false;

            int gid = tileElem.GetInt("gid");
            if (gid > 0)
            {
                SharedPtr<Tile2D> tile(new Tile2D());
                tile->gid_ = gid;
                tile->sprite_ = tmxFile_->GetTileSprite(gid);
                tile->properties_ = tmxFile_->GetTileProperties(gid);
                tiles_[y * width_ + x] = tile;
            }

            tileElem = tileElem.GetNext("tile");
        }
    }

    if (element.HasChild("properties"))
        LoadProperties(element.GetChild("properties"));
    
    return true;
}

Tile2D* TmxTileLayer2D::GetTile(int x, int y) const
{
    if (x < 0 || x > width_ || y < 0 || y > height_)
        return 0;

    return tiles_[y * width_ + x];
}




TmxObjectGroup2D::TmxObjectGroup2D(TmxFile2D* tmxFile) :
    TmxLayer2D(tmxFile, LT_OBJECT_GROUP)
{
}


bool TmxObjectGroup2D::Load(const XMLElement& element)
{
    LoadInfo(element);
   
    const float mapHeight = height_ * tmxFile_->GetTileHeight();

    for (XMLElement objectElem = element.GetChild("object"); objectElem; objectElem = objectElem.GetNext("object"))
    {
        SharedPtr<TileObject2D> object(new TileObject2D());
        
        object->position_ = Vector2(objectElem.GetInt("x") * PIXEL_SIZE, mapHeight - objectElem.GetInt("y") * PIXEL_SIZE);
        if (objectElem.HasAttribute("width") || objectElem.HasAttribute("height"))
        {
            if (!objectElem.HasChild("ellipse"))
                object->type_ = OT_RECTANGLE;
            else
                object->type_ = OT_ELLIPSE;

            object->size_ = Vector2(objectElem.GetInt("width") * PIXEL_SIZE, objectElem.GetInt("height") * PIXEL_SIZE);
            object->position_.y_ -= object->size_.y_;
        }
        else if (objectElem.HasAttribute("gid"))
        {
            object->type_ = OT_TILE;
            object->gid_ = objectElem.GetInt("gid");
            object->sprite_ = tmxFile_->GetTileSprite(object->gid_);
        }
        else
        {
            XMLElement childElem = objectElem.GetChild();
            if (childElem.GetName() == "polygon")
                object->type_ = OT_POLYGON;
            else if (childElem.GetName() == "polyline")
                object->type_ = OT_POLYLINE;
            else
                return false;

            Vector<String> points = childElem.GetAttribute("points").Split(' ');
            object->points_.Resize(points.Size());

            for (unsigned i = 0; i < points.Size(); ++i)
            {
                points[i].Replace(',', ' ');
                Vector2 point = ToVector2(points[i]) * PIXEL_SIZE;
                point.y_ = mapHeight - point.y_;
                object->points_[i] = point;
            }
        }

        if (objectElem.HasChild("properties"))
        {
            object->properties_ = new Properties2D();
            object->properties_->Load(objectElem.GetChild("properties"));
        }

        objects_.Push(object);
    }

    if (element.HasChild("properties"))
        LoadProperties(element.GetChild("properties"));

    return true;
}


TileObject2D* TmxObjectGroup2D::GetObject(unsigned index) const
{
    if (index >= objects_.Size())
        return 0;
    return objects_[index];
}


TmxImageLayer2D::TmxImageLayer2D(TmxFile2D* tmxFile) :
    TmxLayer2D(tmxFile, LT_IMAGE_LAYER)
{
}

bool TmxImageLayer2D::Load(const XMLElement& element)
{
    LoadInfo(element);

    XMLElement imageElem = element.GetChild("image");
    if (!imageElem)
        return false;

    source_ = imageElem.GetAttribute("source");
    String textureFilePath = GetParentPath(GetName()) + source_;
    ResourceCache* cache = tmxFile_->GetSubsystem<ResourceCache>();
    SharedPtr<Texture2D> texture(cache->GetResource<Texture2D>(textureFilePath));
    if (!texture)
    {
        LOGERROR("Could not load texture " + textureFilePath);
        return false;
    }

    sprite_ = new Sprite2D(tmxFile_->GetContext());
    sprite_->SetTexture(texture);
    sprite_->SetRectangle(IntRect(0, 0, texture->GetWidth(), texture->GetHeight()));
    // Left top
    sprite_->SetHotSpot(Vector2(0.0f, 1.0f));

    if (element.HasChild("properties"))
        LoadProperties(element.GetChild("properties"));

    return true;
}

Sprite2D* TmxImageLayer2D::GetSprite() const
{
    return sprite_;
}

TmxFile2D::TmxFile2D(Context* context) :
    Resource(context),
    width_(0),
    height_(0),
    tileWidth_(0.0f),
    tileHeight_(0.0f)
{
}

TmxFile2D::~TmxFile2D()
{
    for (unsigned i = 0; i < layers_.Size(); ++i)
        delete layers_[i];
}

void TmxFile2D::RegisterObject(Context* context)
{
    context->RegisterFactory<TmxFile2D>();
}

bool TmxFile2D::BeginLoad(Deserializer& source)
{
    loadXMLFile_ = new XMLFile(context_);
    if (!loadXMLFile_->Load(source))
    {
        LOGERROR("Load XML failed " + source.GetName());
        loadXMLFile_.Reset();
        return false;
    }

    XMLElement rootElem = loadXMLFile_->GetRoot("map");
    if (!rootElem)
    {
        LOGERROR("Invalid tmx file " + source.GetName());
        loadXMLFile_.Reset();
        return false;
    }

    // If we're async loading, request the texture now. Finish during EndLoad().
    if (GetAsyncLoadState() == ASYNC_LOADING)
    {
        for (XMLElement tileSetElem = rootElem.GetChild("tileset"); tileSetElem; tileSetElem = tileSetElem.GetNext("tileset"))
        {
            String textureFilePath = GetParentPath(GetName()) + tileSetElem.GetChild("image").GetAttribute("source");
            GetSubsystem<ResourceCache>()->BackgroundLoadResource<Texture2D>(textureFilePath, true, this);
        }

        for (XMLElement imageLayerElem = rootElem.GetChild("imagelayer"); imageLayerElem; imageLayerElem = imageLayerElem.GetNext("imagelayer"))
        {
            String textureFilePath = GetParentPath(GetName()) + imageLayerElem.GetChild("image").GetAttribute("source");
            GetSubsystem<ResourceCache>()->BackgroundLoadResource<Texture2D>(textureFilePath, true, this);
        }
    }

    return true;
}

bool TmxFile2D::EndLoad()
{
    if (!loadXMLFile_)
        return false;

    XMLElement rootElem = loadXMLFile_->GetRoot("map");
    String version = rootElem.GetAttribute("version");
    if (version != "1.0")
    {
        LOGERROR("Invalid version");
        return false;
    }

    String orientation = rootElem.GetAttribute("orientation");
    if (orientation != "orthogonal")
    {
        LOGERROR("Unsupported orientation now");
        return false;
    }

    width_ = rootElem.GetInt("width");
    height_ = rootElem.GetInt("height");
    tileWidth_ = rootElem.GetFloat("tilewidth") * PIXEL_SIZE;
    tileHeight_ = rootElem.GetFloat("tileheight") * PIXEL_SIZE;

    for (unsigned i = 0; i < layers_.Size(); ++i)
        delete layers_[i];
    layers_.Clear();

    for (XMLElement childElement = rootElem.GetChild(); childElement; childElement = childElement.GetNext())
    {
        bool ret = true;
        String name = childElement.GetName();
        if (name == "tileset")
            ret = LoadTileSet(childElement);
        else if (name == "layer")
        {
            TmxTileLayer2D* tileLayer = new TmxTileLayer2D(this);
            ret = tileLayer->Load(childElement);
            
            layers_.Push(tileLayer);
        }
        else if (name == "objectgroup")
        {
            TmxObjectGroup2D* objectGroup = new TmxObjectGroup2D(this);
            ret = objectGroup->Load(childElement);
            
            layers_.Push(objectGroup);

        }
        else if (name == "imagelayer")
        {
            TmxImageLayer2D* imageLayer = new TmxImageLayer2D(this);
            ret = imageLayer->Load(childElement);

            layers_.Push(imageLayer);
        }

        if (!ret)
        {
            loadXMLFile_.Reset();
            return false;
        }
    }
   
    loadXMLFile_.Reset();
    return true;
}

Sprite2D* TmxFile2D::GetTileSprite(int gid) const
{
    HashMap<int, SharedPtr<Sprite2D> >::ConstIterator i = tileSprites_.Find(gid);
    if (i == tileSprites_.End())
        return 0;

    return i->second_;
}

Properties2D* TmxFile2D::GetTileProperties(int gid) const
{
    HashMap<int, SharedPtr<Properties2D> >::ConstIterator i = tileProperties_.Find(gid);
    if (i == tileProperties_.End())
        return 0;
    return i->second_;
}

const TmxLayer2D* TmxFile2D::GetLayer(unsigned index) const
{
    if (index >= layers_.Size())
        return 0;

    return layers_[index];
}

bool TmxFile2D::LoadTileSet(const XMLElement& element)
{
    XMLElement imageElem = element.GetChild("image");
    String textureFilePath = GetParentPath(GetName()) + imageElem.GetAttribute("source");
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SharedPtr<Texture2D> texture(cache->GetResource<Texture2D>(textureFilePath));
    if (!texture)
    {
        LOGERROR("Could not load texture " + textureFilePath);
        return false;
    }

    tileSetTextures_.Push(texture);

    int firstgid = element.GetInt("firstgid"); 
    int tileWidth = element.GetInt("tilewidth");
    int tileHeight = element.GetInt("tileheight");
    int spacing = element.GetInt("spacing");
    int margin = element.GetInt("margin");
    int imageWidth = imageElem.GetInt("width");
    int imageHeight = imageElem.GetInt("height");

    int gid = firstgid;
    for (int y = margin; y < imageHeight - margin; y += tileHeight + spacing)
    {
        for (int x = margin; x < imageWidth - margin; x += tileWidth + spacing)
        {
            SharedPtr<Sprite2D> sprite(new Sprite2D(context_));
            sprite->SetTexture(texture);
            sprite->SetRectangle(IntRect(x, y, x + tileWidth, y + tileHeight));
            // Set hot spot at left bottom
            sprite->SetHotSpot(Vector2(0.0f, 0.0f));

            tileSprites_[gid++] = sprite;
        }
    }

    for (XMLElement tileElem = element.GetChild("tile"); tileElem; tileElem = tileElem.GetNext("tile"))
    {
        if (tileElem.HasChild("properties"))
        {
            SharedPtr<Properties2D> properties(new Properties2D());
            properties->Load(tileElem.GetChild("properties"));
            tileProperties_[firstgid + tileElem.GetInt("id")] = properties;
        }
    }

    return true;
}

}
