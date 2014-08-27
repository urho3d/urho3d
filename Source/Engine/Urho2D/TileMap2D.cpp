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
#include "DebugRenderer.h"
#include "Node.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "TileMap2D.h"
#include "TileMapLayer2D.h"
#include "TmxFile2D.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const float PIXEL_SIZE;
extern const char* URHO2D_CATEGORY;

TileMap2D::TileMap2D(Context* context) :
    Component(context)
{
}

TileMap2D::~TileMap2D()
{
}

void TileMap2D::RegisterObject(Context* context)
{
    context->RegisterFactory<TileMap2D>(URHO2D_CATEGORY);
    ACCESSOR_ATTRIBUTE(TileMap2D, VAR_RESOURCEREF, "Tmx File", GetTmxFileAttr, SetTmxFileAttr, ResourceRef, ResourceRef(TmxFile2D::GetTypeStatic()), AM_DEFAULT);
}

void TileMap2D::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
{
    const Color& color = Color::RED;
    float mapW = info_.GetMapWidth();
    float mapH = info_.GetMapHeight();
    if (info_.orientation_ == O_ORTHOGONAL)
    {
        debug->AddLine(Vector2(0.0f, 0.0f), Vector2(mapW, 0.0f), color);
        debug->AddLine(Vector2(mapW, 0.0f), Vector2(mapW, mapH), color);
        debug->AddLine(Vector2(mapW, mapH), Vector2(0.0f, mapH), color);
        debug->AddLine(Vector2(0.0f, mapH), Vector2(0.0f, 0.0f), color);
    }
    else
    {
        debug->AddLine(Vector2(0.0f, mapH * 0.5f), Vector2(mapW * 0.5f, 0.0f), color);
        debug->AddLine(Vector2(mapW * 0.5f, 0.0f), Vector2(mapW, mapH * 0.5f), color);
        debug->AddLine(Vector2(mapW, mapH * 0.5f), Vector2(mapW * 0.5f, mapH), color);
        debug->AddLine(Vector2(mapW * 0.5f, mapH), Vector2(0.0f, mapH * 0.5f), color);
    }

    for (unsigned i = 0; i < layers_.Size(); ++i)
        layers_[i]->DrawDebugGeometry(debug, depthTest);
}

void TileMap2D::DrawDebugGeometry()
{
    Scene* scene = GetScene();
    if (!scene)
        return;

    DebugRenderer* debug = scene->GetComponent<DebugRenderer>();
    if (!debug)
        return;

    DrawDebugGeometry(debug, false);
}

void TileMap2D::SetTmxFile(TmxFile2D* tmxFile)
{
    if (tmxFile == tmxFile_)
        return;

    if (tmxFile_)
    {
        for (unsigned i = 0; i < layers_.Size(); ++i)
            layers_[i]->GetNode()->Remove();
        layers_.Clear();
    }

    tmxFile_ = tmxFile;
    if (!tmxFile_)
        return;

    info_ = tmxFile_->GetInfo();

    unsigned numLayers = tmxFile_->GetNumLayers();
    layers_.Resize(numLayers);

    for (unsigned i = 0; i < numLayers; ++i)
    {
        const TmxLayer2D* tmxLayer = tmxFile_->GetLayer(i);

        SharedPtr<Node> layerNode(GetNode()->CreateChild(tmxLayer->GetName(), LOCAL));
        layerNode->SetTemporary(true);

        SharedPtr<TileMapLayer2D> layer(layerNode->CreateComponent<TileMapLayer2D>());
        layer->Initialize(this, tmxLayer);
        layer->SetDrawOrder(i * 10);

        layers_[i] = layer;
    }
}

TmxFile2D* TileMap2D::GetTmxFile() const
{
    return tmxFile_;
}

TileMapLayer2D* TileMap2D::GetLayer(unsigned index) const
{
    if (index >= layers_.Size())
        return 0;

    return layers_[index];
}

Vector2 TileMap2D::IndexToPosition(int x, int y) const
{
    return info_.TileIndexToPosition(x, y);
}

bool TileMap2D::PositionToIndex(int& x, int& y, const Vector2& position) const
{
    return info_.PositionToTileIndex(x, y, position);
}


void TileMap2D::SetTmxFileAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetTmxFile(cache->GetResource<TmxFile2D>(value.name_));
}

ResourceRef TileMap2D::GetTmxFileAttr() const
{
    return GetResourceRef(tmxFile_, TmxFile2D::GetTypeStatic());
}

}
