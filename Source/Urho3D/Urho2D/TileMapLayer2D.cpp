//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Graphics/DebugRenderer.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Node.h"
#include "../Urho2D/StaticSprite2D.h"
#include "../Urho2D/TileMap2D.h"
#include "../Urho2D/TileMapLayer2D.h"
#include "../Urho2D/TmxFile2D.h"

#include "../DebugNew.h"

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

void TileMapLayer2D::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    if (!debug)
        return;

    if (objectGroup_)
    {
        for (unsigned i = 0; i < objectGroup_->GetNumObjects(); ++i)
        {
            TileMapObject2D* object = objectGroup_->GetObject(i);
            const Color& color = Color::YELLOW;

            switch (object->GetObjectType())
            {
            case OT_RECTANGLE:
                {
                    const Vector2& lb = object->GetPosition();
                    const Vector2& rt = lb + object->GetSize();

                    debug->AddLine(Vector2(lb.x_, lb.y_), Vector2(rt.x_, lb.y_), color, depthTest);
                    debug->AddLine(Vector2(rt.x_, lb.y_), Vector2(rt.x_, rt.y_), color, depthTest);
                    debug->AddLine(Vector2(rt.x_, rt.y_), Vector2(lb.x_, rt.y_), color, depthTest);
                    debug->AddLine(Vector2(lb.x_, rt.y_), Vector2(lb.x_, lb.y_), color, depthTest);
                }
                break;

            case OT_ELLIPSE:
                {
                    const Vector2 halfSize = object->GetSize() * 0.5f;
                    const Vector2 center = object->GetPosition() + halfSize;
                    for (unsigned i = 0; i < 360; i += 30)
                    {
                        unsigned j = i + 30;
                        float x1 = halfSize.x_ * Cos((float)i);
                        float y1 = halfSize.y_ * Sin((float)i);
                        float x2 = halfSize.x_ * Cos((float)j);
                        float y2 = halfSize.y_ * Sin((float)j);
                        debug->AddLine(center + Vector2(x1, y1), center + Vector2(x2, y2), color, depthTest);
                    }
                }
                break;

            case OT_POLYGON:
            case OT_POLYLINE:
                {
                    for (unsigned j = 0; j < object->GetNumPoints() - 1; ++j)
                        debug->AddLine(object->GetPoint(j), object->GetPoint(j + 1), color, depthTest);

                    if (object->GetObjectType() == OT_POLYGON)
                        debug->AddLine(object->GetPoint(0), object->GetPoint(object->GetNumPoints() - 1), color, depthTest);
                }
                break;

            default: break;
            }
        }
    }
}

void TileMapLayer2D::Initialize(TileMap2D* tileMap, const TmxLayer2D* tmxLayer)
{
    if (tileMap == tileMap_ && tmxLayer == tmxLayer_)
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

    tileMap_ = tileMap;
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

TileMap2D* TileMapLayer2D::GetTileMap() const
{
    return tileMap_;
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

int TileMapLayer2D::GetWidth() const
{
    return tmxLayer_ ? tmxLayer_->GetWidth() : 0;
}

int TileMapLayer2D::GetHeight() const
{
    return tmxLayer_ ? tmxLayer_->GetHeight() : 0;
}

Tile2D* TileMapLayer2D::GetTile(int x, int y) const
{
    if (!tileLayer_)
        return 0;

    return tileLayer_->GetTile(x, y);
}

Node* TileMapLayer2D::GetTileNode(int x, int y) const
{
    if (!tileLayer_)
        return 0;

    if (x < 0 || x >= tileLayer_->GetWidth() || y < 0 || y >= tileLayer_->GetHeight())
        return 0;

    return nodes_[y * tileLayer_->GetWidth() + x];
}

unsigned TileMapLayer2D::GetNumObjects() const
{
    if (!objectGroup_)
        return 0;

    return objectGroup_->GetNumObjects();
}

TileMapObject2D* TileMapLayer2D::GetObject(unsigned index) const
{
    if (!objectGroup_)
        return 0;

    return objectGroup_->GetObject(index);
}

Node* TileMapLayer2D::GetObjectNode(unsigned index) const
{
    if (!objectGroup_)
        return 0;

    if (index >= nodes_.Size())
        return 0;

    return nodes_[index];
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
    tileLayer_ = tileLayer;

    int width = tileLayer->GetWidth();
    int height = tileLayer->GetHeight();
    nodes_.Resize((unsigned)(width * height));

    const TileMapInfo2D& info = tileMap_->GetInfo();
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            const Tile2D* tile = tileLayer->GetTile(x, y);
            if (!tile)
                continue;

            SharedPtr<Node> tileNode(GetNode()->CreateChild("Tile"));
            tileNode->SetTemporary(true);
            tileNode->SetPosition(info.TileIndexToPosition(x, y));

            StaticSprite2D* staticSprite = tileNode->CreateComponent<StaticSprite2D>();
            staticSprite->SetSprite(tile->GetSprite());
            staticSprite->SetLayer(drawOrder_);
            staticSprite->SetOrderInLayer(y * width + x);

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
        const TileMapObject2D* object = objectGroup->GetObject(i);

        // Create dummy node for all object
        SharedPtr<Node> objectNode(GetNode()->CreateChild("Object"));
        objectNode->SetTemporary(true);
        objectNode->SetPosition(object->GetPosition());

        // If object is tile, create static sprite component
        if (object->GetObjectType() == OT_TILE && object->GetTileGid() && object->GetTileSprite())
        {
            StaticSprite2D* staticSprite = objectNode->CreateComponent<StaticSprite2D>();
            staticSprite->SetSprite(object->GetTileSprite());
            staticSprite->SetLayer(drawOrder_);
            staticSprite->SetOrderInLayer((int)((10.0f - object->GetPosition().y_) * 100));

            if (tmxFile->GetInfo().orientation_ == O_ISOMETRIC)
            {
                staticSprite->SetUseHotSpot(true);
                staticSprite->SetHotSpot(Vector2(0.5f, 0.0f));
            }
        }

        nodes_[i] = objectNode;
    }
}

void TileMapLayer2D::SetImageLayer(const TmxImageLayer2D* imageLayer)
{
    imageLayer_ = imageLayer;

    if (!imageLayer->GetSprite())
        return;

    SharedPtr<Node> imageNode(GetNode()->CreateChild("Tile"));
    imageNode->SetTemporary(true);
    imageNode->SetPosition(imageLayer->GetPosition());

    StaticSprite2D* staticSprite = imageNode->CreateComponent<StaticSprite2D>();
    staticSprite->SetSprite(imageLayer->GetSprite());
    staticSprite->SetOrderInLayer(0);

    nodes_.Push(imageNode);
}

}
