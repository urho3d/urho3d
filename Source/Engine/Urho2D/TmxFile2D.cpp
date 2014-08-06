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
            ret = LoadLayer(childElement);
        else if (name == "objectgroup")
            ret = LoadObjectGroup(childElement);
        else if (name == "imagelayer")
            ret = LoadImageLayer(childElement);

        if (!ret)
        {
            loadXMLFile_.Reset();
            return false;
        }
    }
   
    loadXMLFile_.Reset();
    return true;
}

const TmxLayer2D* TmxFile2D::GetLayer(unsigned index) const
{
    if (index >= layers_.Size())
        return 0;

    return layers_[index];
}

Sprite2D* TmxFile2D::GetTileSprite(int gid) const
{
    HashMap<int, SharedPtr<Sprite2D> >::ConstIterator i = tileSprites_.Find(gid);
    if (i == tileSprites_.End())
        return 0;

    return i->second_;
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

    int gid = element.GetInt("firstgid");
    int tileWidth = element.GetInt("tilewidth");
    int tileHeight = element.GetInt("tileheight");
    int spacing = element.GetInt("spacing");
    int margin = element.GetInt("margin");
    int imageWidth = imageElem.GetInt("width");
    int imageHeight = imageElem.GetInt("height");

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

    return true;
}

bool TmxFile2D::LoadLayer(const XMLElement& element)
{
    TmxTileLayer2D* tileLayer = new TmxTileLayer2D(this);
    layers_.Push(tileLayer);

    tileLayer->name_ = element.GetAttribute("name");
    tileLayer->width_ = element.GetInt("width");
    tileLayer->height_ = element.GetInt("height");

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
    tileLayer->tileGids_.Resize(tileLayer->width_ * tileLayer->height_);
    
    // Flip y
    for (int y = tileLayer->height_ - 1; y >= 0; --y)
    {
        for (int x = 0; x < tileLayer->width_; ++x)
        {
            if (!tileElem)
                return false;

            int gid = tileElem.GetInt("gid");
            tileElem = tileElem.GetNext("tile");
            tileLayer->tileGids_[y * tileLayer->width_ + x] = gid;
        }
    }

    return true;
}

bool TmxFile2D::LoadObjectGroup(const XMLElement& element)
{
    TmxObjectGroup2D* objectGroup = new TmxObjectGroup2D(this);
    layers_.Push(objectGroup);

    objectGroup->name_ = element.GetAttribute("name");
    objectGroup->width_ = element.GetInt("width");
    objectGroup->height_ = element.GetInt("height");

    const float mapHeight = height_ * tileHeight_;

    for (XMLElement objectElem = element.GetChild("object"); objectElem; objectElem = objectElem.GetNext("object"))
    {
        objectGroup->objects_.Push(TmxObject());
        TmxObject& object = objectGroup->objects_.Back();

        object.x_ = objectElem.GetInt("x") * PIXEL_SIZE;
        // Flip y
        object.y_ = mapHeight - objectElem.GetInt("y") * PIXEL_SIZE;

        if (objectElem.HasAttribute("width") || objectElem.HasAttribute("height"))
        {
            if (!objectElem.HasChild("ellipse"))
                object.type_ = OT_RECTANGLE;
            else
                object.type_ = OT_ELLIPSE;

            object.width_ = objectElem.GetInt("width") * PIXEL_SIZE;
            object.height_ = objectElem.GetInt("height") * PIXEL_SIZE;

            object.y_ -= object.height_;
        }
        else if (objectElem.HasAttribute("gid"))
        {
            object.type_ = OT_TILE;
            object.gid_ = objectElem.GetInt("gid");
        }
        else
        {
            XMLElement childElem = objectElem.GetChild();
            if (childElem.GetName() == "polygon")
                object.type_ = OT_POLYGON;
            else if (childElem.GetName() == "polyline")
                object.type_ = OT_POLYLINE;
            else
                return false;

            Vector<String> points = childElem.GetAttribute("points").Split(' ');
            object.points_.Resize(points.Size());
            
            for (unsigned i = 0; i < points.Size(); ++i)
            {
                points[i].Replace(',', ' ');
                Vector2 point = ToVector2(points[i]) * PIXEL_SIZE;
                point.y_ = mapHeight - point.y_;
                object.points_[i] = point;
            }
        }
    }

    return true;
}

bool TmxFile2D::LoadImageLayer(const XMLElement& element)
{
    TmxImageLayer2D* imageLayer = new TmxImageLayer2D(this);
    layers_.Push(imageLayer);

    imageLayer->name_ = element.GetAttribute("name");
    imageLayer->width_ = element.GetInt("width");
    imageLayer->height_ = element.GetInt("height");

    XMLElement imageElem = element.GetChild("image");
    if (!imageElem)
        return false;

    String textureFilePath = GetParentPath(GetName()) + imageElem.GetAttribute("source");
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SharedPtr<Texture2D> texture(cache->GetResource<Texture2D>(textureFilePath));
    if (!texture)
    {
        LOGERROR("Could not load texture " + textureFilePath);
        return false;
    }

    SharedPtr<Sprite2D> sprite(new Sprite2D(context_));
    sprite->SetTexture(texture);
    sprite->SetRectangle(IntRect(0, 0, texture->GetWidth(), texture->GetHeight()));
    // Left top
    sprite->SetHotSpot(Vector2(0.0f, 1.0f));
    
    imageLayer->sprite_ = sprite;

    return true;
}

}
