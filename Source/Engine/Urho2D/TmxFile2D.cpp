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

    // Load tile set
    for (XMLElement tileSetElem = rootElem.GetChild("tileset"); tileSetElem; tileSetElem = tileSetElem.GetNext("tileset"))
    {
        if (!LoadTileSet(tileSetElem))
        {
            loadXMLFile_.Reset();
            return false;
        }
    }

    // Load layer
    for (XMLElement layerElem = rootElem.GetChild("layer"); layerElem; layerElem = layerElem.GetNext("layer"))
    {
        if (!LoadLayer(layerElem))
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

    return &layers_[index];
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
        loadXMLFile_.Reset();
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
    layers_.Push(TmxLayer2D());
    TmxLayer2D& layer = layers_.Back();
    layer.tmxFile_ = this;

    layer.name_ = element.GetAttribute("name");

    layer.width_ = element.GetInt("width");
    layer.height_ = element.GetInt("height");

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
    layer.tileGids_.Resize(layer.width_ * layer.height_);
    
    // Flip y
    for (int y = layer.height_ - 1; y >= 0; --y)
    {
        for (int x = 0; x < layer.width_; ++x)
        {
            if (!tileElem)
                return false;

            int gid = tileElem.GetInt("gid");
            tileElem = tileElem.GetNext("tile");
            layer.tileGids_[y * layer.width_ + x] = gid;
        }
    }

    return true;
}

}
