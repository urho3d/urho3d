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
#include "ResourceCache.h"
#include "TileMapLayer2D.h"
#include "TmxFile2D.h"
#include "TileMapLayer2D.h"
#include "Node.h"
#include "StaticSprite2D.h"

#include "DebugNew.h"

namespace Urho3D
{

TileMapLayer2D::TileMapLayer2D(Context* context) :
    Component(context),
    tmxLayer_(0),
    drawOrder_(0)
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

    tmxLayer_ = tmxLayer;

    if (!tmxLayer_)
        return;

    if (tmxLayer_->type_ == LT_TILE_LAYER)
        SetTileLayer((TmxTileLayer2D*)tmxLayer_);
    else if (tmxLayer_->type_ == LT_IMAGE_LAYER)
        SetImageLayer((TmxImageLayer2D*)tmxLayer_);
}

void TileMapLayer2D::SetDrawOrder(int drawOrder)
{
    if (drawOrder == drawOrder_)
        return;

    drawOrder_ = drawOrder;

    for (unsigned i = 0; i < nodes_.Size(); ++i)
    {
        if (nodes_[i])
            nodes_[i]->GetComponent<StaticSprite2D>()->SetLayer(drawOrder_);
    }
}

TmxLayerType2D TileMapLayer2D::GetLayerType() const
{
    return tmxLayer_ ? tmxLayer_->type_ : LT_INVALID;
}

const String& TileMapLayer2D::GetName() const
{
    return tmxLayer_ ? tmxLayer_->name_ : String::EMPTY;
}

int TileMapLayer2D::GetWidth() const
{
    return tmxLayer_ ? tmxLayer_->width_ : 0;
}

int TileMapLayer2D::GetHeight() const
{
    return tmxLayer_ ? tmxLayer_->height_ : 0;
}

Node* TileMapLayer2D::GetTileNode(int x, int y) const
{
    if (!tmxLayer_ || tmxLayer_->type_ != LT_TILE_LAYER)
        return 0;

    const TmxTileLayer2D* tileLayer = (const TmxTileLayer2D*)tmxLayer_;
    if (x < 0 || x >= tileLayer->width_ || y < 0 || y >= tileLayer->height_)
        return 0;

    return nodes_[y * tileLayer->width_ + x];
}

Node* TileMapLayer2D::GetImageNode() const
{
    if (!tmxLayer_ || tmxLayer_->type_ != LT_IMAGE_LAYER)
        return 0;

    if (nodes_.Empty())
        return 0;

    return nodes_[0];
}

void TileMapLayer2D::SetTileLayer(const TmxTileLayer2D* tileLayer)
{
    int width = tileLayer->width_;
    int height = tileLayer->height_;
    nodes_.Resize(width * height);

    TmxFile2D* tmxFile = tileLayer->tmxFile_;
    float tileWidth = tmxFile->GetTileWidth();
    float tileHeight = tmxFile->GetTileHeight();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int gid = tileLayer->tileGids_[y * width + x];
            if (gid <= 0)
                continue;

            Sprite2D* sprite = tmxFile->GetTileSprite(gid);
            if (!sprite)
                continue;

            SharedPtr<Node> tileNode(GetNode()->CreateChild("Tile"));
            tileNode->SetTemporary(true);
            tileNode->SetPosition(Vector3(x * tileWidth, y * tileHeight, 0.0f));

            StaticSprite2D* staticSprite = tileNode->CreateComponent<StaticSprite2D>();
            staticSprite->SetSprite(sprite);
            staticSprite->SetLayer(drawOrder_);
            staticSprite->SetOrderInLayer((height - 1 - y) * width + x);

            nodes_[y * width + x] = tileNode;
        }
    }
}

void TileMapLayer2D::SetImageLayer(const TmxImageLayer2D* imageLayer)
{
    if (!imageLayer->sprite_)
        return;

    TmxFile2D* tmxFile = imageLayer->tmxFile_;
    int height = tmxFile->GetHeight();
    float tileHeight = tmxFile->GetTileHeight();

    SharedPtr<Node> imageNode(GetNode()->CreateChild("Tile"));
    imageNode->SetTemporary(true);
    imageNode->SetPosition(Vector3(0.0f, height * tileHeight, 0.0f));

    StaticSprite2D* staticSprite = imageNode->CreateComponent<StaticSprite2D>();
    staticSprite->SetSprite(imageLayer->sprite_);
    staticSprite->SetOrderInLayer(0);

    nodes_.Push(imageNode);
}

}
