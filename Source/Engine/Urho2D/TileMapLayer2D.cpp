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
#include "Context.h"
#include "Node.h"
#include "ResourceCache.h"
#include "StaticSprite2D.h"
#include "TileMapLayer2D.h"
#include "TileMapLayer2D.h"
#include "TmxFile2D.h"

#include "DebugNew.h"

namespace Urho3D
{

TileMapLayer2D::TileMapLayer2D(Context* context) :
    Component(context),
    tmxLayer_(0),
    drawOrder_(0),
    visible_(true)
{
}

TileMapLayer2D::~TileMapLayer2D()
{
}

void TileMapLayer2D::RegisterObject(Context* context)
{
    context->RegisterFactory<TileMapLayer2D>();
}

void TileMapLayer2D::SetTmxLayer(const TmxLayer2D* tmxLayer)
{
    if (tmxLayer == tmxLayer_)
        return;

    if (tmxLayer_)
    {
        for (unsigned i = 0; i < nodes_.Size(); ++i)
        {
            if (nodes_[i])
                nodes_[i]->Remove();
        }

        nodes_.Clear();
    }

    tileLayer_ = 0;
    objectGroup_ = 0;
    imageLayer_ = 0;
    
    tmxLayer_ = tmxLayer;
    
    if (!tmxLayer_)
        return;

    switch (tmxLayer_->GetType())
    {
    case LT_TILE_LAYER:
        SetTileLayer((const TmxTileLayer2D*)tmxLayer_);
        break;

    case LT_OBJECT_GROUP:
        SetObjectGroup((const TmxObjectGroup2D*)tmxLayer_);
        break;

    case LT_IMAGE_LAYER:
        SetImageLayer((const TmxImageLayer2D*)tmxLayer_);
        break;

    default:
        break;
    }

    SetVisible(tmxLayer_->IsVisible());
}

void TileMapLayer2D::SetDrawOrder(int drawOrder)
{
    if (drawOrder == drawOrder_)
        return;

    drawOrder_ = drawOrder;

    for (unsigned i = 0; i < nodes_.Size(); ++i)
    {
        if (!nodes_[i])
            continue;

        StaticSprite2D* staticSprite = nodes_[i]->GetComponent<StaticSprite2D>();
        if (staticSprite)
            staticSprite->SetLayer(drawOrder_);
    }
}

void TileMapLayer2D::SetVisible(bool visible)
{
    if (visible == visible_)
        return;

    visible_ = visible;

    for (unsigned i = 0; i < nodes_.Size(); ++i)
    {
        if (nodes_[i])
            nodes_[i]->SetEnabled(visible_);
    }
}

int TileMapLayer2D::GetWidth() const
{
    return tmxLayer_ ? tmxLayer_->GetWidth(): 0;
}

int TileMapLayer2D::GetHeight() const
{
    return tmxLayer_ ? tmxLayer_->GetHeight(): 0;
}

bool TileMapLayer2D::HasProperty(const String& name) const
{
    if (!tmxLayer_)
        return false;

    return tmxLayer_->HasProperty(name);
}

const String& TileMapLayer2D::GetProperty(const String& name) const
{
    if (!tmxLayer_)
        return String::EMPTY;
    return tmxLayer_->GetProperty(name);
}

TileMapLayerType2D TileMapLayer2D::GetLayerType() const
{
    return tmxLayer_ ? tmxLayer_->GetType() : LT_INVALID;
}

Node* TileMapLayer2D::GetTileNode(int x, int y) const
{
    if (!tileLayer_)
        return 0;
    
    if (x < 0 || x >= tileLayer_->GetWidth() || y < 0 || y >= tileLayer_->GetHeight())
        return 0;
    
    return nodes_[y * tileLayer_->GetWidth() + x];
}

Tile2D* TileMapLayer2D::GetTile(int x, int y) const
{
    if (!tileLayer_)
        return 0;
    
    return tileLayer_->GetTile(x, y);
}

unsigned TileMapLayer2D::GetNumObjectNodes() const
{
    if (!objectGroup_)
        return 0;

    return nodes_.Size();
}

Node* TileMapLayer2D::GetObjectNode(unsigned index) const
{
    if (!objectGroup_)
        return 0;

    if (index >= nodes_.Size())
        return 0;

    return nodes_[index];
}

unsigned TileMapLayer2D::GetNumObjects() const
{
    if (!objectGroup_)
        return 0;

    return objectGroup_->GetNumObjects();
}

TileObject2D* TileMapLayer2D::GetObject(unsigned index) const
{
    if (objectGroup_)
        return 0;

    return objectGroup_->GetObject(index);
}

Node* TileMapLayer2D::GetImageNode() const
{
    if (!imageLayer_)
        return 0;

    if (nodes_.Empty())
        return 0;

    return nodes_[0];
}

void TileMapLayer2D::SetTileLayer(const TmxTileLayer2D* tileLayer)
{
    tmxLayer_ = tileLayer;

    int width = tileLayer->GetWidth();
    int height = tileLayer->GetHeight();
    nodes_.Resize(width * height);

    TmxFile2D* tmxFile = tileLayer->GetTmxFile();
    float tileWidth = tmxFile->GetTileWidth();
    float tileHeight = tmxFile->GetTileHeight();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            const Tile2D* tile = tileLayer->GetTile(x, y);
            if (!tile)
                continue;

            SharedPtr<Node> tileNode(GetNode()->CreateChild("Tile"));
            tileNode->SetTemporary(true);
            tileNode->SetPosition(Vector3((x + 0.5f) * tileWidth, (y + 0.5f) * tileHeight, 0.0f));

            StaticSprite2D* staticSprite = tileNode->CreateComponent<StaticSprite2D>();
            staticSprite->SetSprite(tile->GetSprite());
            staticSprite->SetLayer(drawOrder_);
            staticSprite->SetOrderInLayer((height - 1 - y) * width + x);

            nodes_[y * width + x] = tileNode;
        }
    }
}

void TileMapLayer2D::SetObjectGroup(const TmxObjectGroup2D* objectGroup)
{
    objectGroup_ = objectGroup;

    TmxFile2D* tmxFile = objectGroup->GetTmxFile();
    nodes_.Resize(objectGroup->GetNumObjects());

    for (unsigned i = 0; i < objectGroup->GetNumObjects(); ++i)
    {
        const TileObject2D* object = objectGroup->GetObject(i);

        // Create dummy node for all object
        SharedPtr<Node> objectNode(GetNode()->CreateChild("Object"));
        objectNode->SetTemporary(true);
        objectNode->SetPosition(object->GetPosition());

        // If object is tile, create static sprite component
        if (object->GetType() == OT_TILE && object->GetTileGid() && object->GetTileSprite())
        {
            StaticSprite2D* staticSprite = objectNode->CreateComponent<StaticSprite2D>();
            staticSprite->SetSprite(object->GetTileSprite());
            staticSprite->SetLayer(drawOrder_);
            staticSprite->SetOrderInLayer((int)((10.0f - object->GetPosition().y_) * 100));
        }

        nodes_[i] = objectNode;
    }
}

void TileMapLayer2D::SetImageLayer(const TmxImageLayer2D* imageLayer)
{
    imageLayer_ = imageLayer;

    if (!imageLayer->GetSprite())
        return;

    TmxFile2D* tmxFile = imageLayer->GetTmxFile();
    int height = tmxFile->GetHeight();
    float tileHeight = tmxFile->GetTileHeight();

    SharedPtr<Node> imageNode(GetNode()->CreateChild("Tile"));
    imageNode->SetTemporary(true);
    imageNode->SetPosition(Vector3(0.0f, height * tileHeight, 0.0f));

    StaticSprite2D* staticSprite = imageNode->CreateComponent<StaticSprite2D>();
    staticSprite->SetSprite(imageLayer->GetSprite());
    staticSprite->SetOrderInLayer(0);

    nodes_.Push(imageNode);
}

}
