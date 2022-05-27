// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Scene/Component.h"
#include "../Urho2D/TileMapDefs2D.h"

#ifdef GetObject
#undef GetObject
#endif

namespace Urho3D
{

class DebugRenderer;
class Node;
class TileMap2D;
class TmxImageLayer2D;
class TmxLayer2D;
class TmxObjectGroup2D;
class TmxTileLayer2D;

/// Tile map component.
class URHO3D_API TileMapLayer2D : public Component
{
    URHO3D_OBJECT(TileMapLayer2D, Component);

public:
    /// Construct.
    explicit TileMapLayer2D(Context* context);
    /// Destruct.
    ~TileMapLayer2D() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Add debug geometry to the debug renderer.
    void DrawDebugGeometry(DebugRenderer* debug, bool depthTest) override;

    /// Initialize with tile map and tmx layer.
    void Initialize(TileMap2D* tileMap, const TmxLayer2D* tmxLayer);
    /// Set draw order.
    /// @property
    void SetDrawOrder(int drawOrder);
    /// Set visible.
    /// @property
    void SetVisible(bool visible);

    /// Return tile map.
    TileMap2D* GetTileMap() const;

    /// Return tmx layer.
    const TmxLayer2D* GetTmxLayer() const { return tmxLayer_; }

    /// Return draw order.
    /// @property
    int GetDrawOrder() const { return drawOrder_; }

    /// Return visible.
    /// @property
    bool IsVisible() const { return visible_; }

    /// Return has property.
    bool HasProperty(const String& name) const;
    /// Return property.
    const String& GetProperty(const String& name) const;
    /// Return layer type.
    /// @property
    TileMapLayerType2D GetLayerType() const;

    /// Return width (for tile layer only).
    /// @property
    int GetWidth() const;
    /// Return height (for tile layer only).
    /// @property
    int GetHeight() const;
    /// Return tile node (for tile layer only).
    Node* GetTileNode(int x, int y) const;
    /// Return tile (for tile layer only).
    Tile2D* GetTile(int x, int y) const;

    /// Return number of tile map objects (for object group only).
    /// @property
    unsigned GetNumObjects() const;
    /// Return tile map object (for object group only).
    TileMapObject2D* GetObject(unsigned index) const;
    /// Return object node (for object group only).
    Node* GetObjectNode(unsigned index) const;

    /// Return image node (for image layer only).
    /// @property
    Node* GetImageNode() const;

private:
    /// Set tile layer.
    void SetTileLayer(const TmxTileLayer2D* tileLayer);
    /// Set object group.
    void SetObjectGroup(const TmxObjectGroup2D* objectGroup);
    /// Set image layer.
    void SetImageLayer(const TmxImageLayer2D* imageLayer);

    /// Tile map.
    WeakPtr<TileMap2D> tileMap_;
    /// Tmx layer.
    const TmxLayer2D* tmxLayer_{};
    /// Tile layer.
    const TmxTileLayer2D* tileLayer_{};
    /// Object group.
    const TmxObjectGroup2D* objectGroup_{};
    /// Image layer.
    const TmxImageLayer2D* imageLayer_{};
    /// Draw order.
    int drawOrder_{};
    /// Visible.
    bool visible_{true};
    /// Tile node or image nodes.
    Vector<SharedPtr<Node>> nodes_;
};

}
