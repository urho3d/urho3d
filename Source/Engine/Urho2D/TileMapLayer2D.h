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

#include "Component.h"
#include "TmxFile2D.h"

namespace Urho3D
{

class Node;

/// Tile map component.
class URHO3D_API TileMapLayer2D : public Component
{
    OBJECT(TileMapLayer2D);

public:
    /// Construct.
    TileMapLayer2D(Context* context);
    /// Destruct.
    ~TileMapLayer2D();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Set tmx layer.
    void SetTmxLayer(const TmxLayer2D* tmxLayer);
    /// Set draw order
    void SetDrawOrder(int drawOrder);

    /// Return tmx layer.
    const TmxLayer2D* GetTmxLayer() const { return tmxLayer_; }
    /// Return draw order.
    int GetDrawOrder() const { return drawOrder_; }

    /// Return layer type.
    TmxLayerType2D GetLayerType() const;
    /// Return name.
    const String& GetName() const;
    /// Return width.
    int GetWidth() const;
    /// Return height.
    int GetHeight() const;

    /// Return tile node (for tile layer only).
    Node* GetTileNode(int x, int y) const;
    /// Return image node (for image layer only).
    Node* GetImageNode() const;

private:
    /// Set tile layer.
    void SetTileLayer(const TmxTileLayer2D* tileLayer);
    /// Set object group.
    void SetObjectGroup(const TmxObjectGroup2D* objectGroup);
    /// Set image layer.
    void SetImageLayer(const TmxImageLayer2D* imageLayer);

    /// Tmx layer.
    const TmxLayer2D* tmxLayer_;
    /// Draw order.
    int drawOrder_;
    /// Tile or image nodes.
    Vector<SharedPtr<Node> > nodes_;
};

}
