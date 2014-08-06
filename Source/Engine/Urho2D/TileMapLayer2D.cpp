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

void TileMapLayer2D::SetTmxLayer(const TmxLayer2D* tmxLayer, int drawOrder)
{
    if (tmxLayer == tmxLayer_)
        return;

    if (tmxLayer_)
    {
        for (unsigned i = 0; i < tileNodes_.Size(); ++i)
        {
            if (tileNodes_[i])
                tileNodes_[i]->Remove();
        }

        tileNodes_.Clear();
    }

    tmxLayer_ = tmxLayer;
    drawOrder_ = drawOrder;

    if (!tmxLayer_)
        return;

    int width = tmxLayer_->width_;
    int height = tmxLayer->height_;
    tileNodes_.Resize(width * height);

    TmxFile2D* tmxFile = tmxLayer_->tmxFile_;
    float tileWidth = tmxFile->GetTileWidth();
    float tileHeight = tmxFile->GetTileHeight();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int gid = tmxLayer->tileGids_[y * width + x];
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

            tileNodes_[y * width + x] = tileNode;
        }
    }
}

void TileMapLayer2D::SetDrawOrder(int drawOrder)
{
    if (drawOrder == drawOrder_)
        return;

    drawOrder_ = drawOrder;

    for (unsigned i = 0; i < tileNodes_.Size(); ++i)
    {
        if (tileNodes_[i])
            tileNodes_[i]->GetComponent<StaticSprite2D>()->SetLayer(drawOrder_);
    }
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
    if (!tmxLayer_)
        return 0;

    if (x < 0 || x >= tmxLayer_->width_ || y < 0 || y >= tmxLayer_->height_)
        return 0;

    return tileNodes_[y * tmxLayer_->width_ + x];
}

}
