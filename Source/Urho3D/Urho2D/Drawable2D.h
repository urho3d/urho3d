// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Graphics/Drawable.h"
#include "../GraphicsAPI/GraphicsDefs.h"
#include "../Urho2D/Urho2D.h"

namespace Urho3D
{

class Drawable2D;
class Renderer2D;
class Texture2D;
class VertexBuffer;

/// 2D vertex.
struct Vertex2D
{
    /// Position.
    Vector3 position_;
    /// Color.
    unsigned color_;
    /// UV.
    Vector2 uv_;
};

/// 2D source batch.
struct SourceBatch2D
{
    /// Construct.
    SourceBatch2D();

    /// Owner.
    WeakPtr<Drawable2D> owner_;
    /// Distance to camera.
    mutable float distance_;
    /// Draw order.
    int drawOrder_;
    /// Material.
    SharedPtr<Material> material_;
    /// Vertices.
    Vector<Vertex2D> vertices_;
};

/// Base class for 2D visible components.
class URHO3D_API Drawable2D : public Drawable
{
    URHO3D_OBJECT(Drawable2D, Drawable);

public:
    /// Construct.
    explicit Drawable2D(Context* context);
    /// Destruct.
    ~Drawable2D() override;
    /// Register object factory. Drawable must be registered first.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Handle enabled/disabled state change.
    void OnSetEnabled() override;

    /// Set layer.
    /// @property
    void SetLayer(int layer);
    /// Set order in layer.
    /// @property
    void SetOrderInLayer(int orderInLayer);

    /// Return layer.
    /// @property
    int GetLayer() const { return layer_; }

    /// Return order in layer.
    /// @property
    int GetOrderInLayer() const { return orderInLayer_; }

    /// Return all source batches (called by Renderer2D).
    const Vector<SourceBatch2D>& GetSourceBatches();

protected:
    /// Handle scene being assigned.
    void OnSceneSet(Scene* scene) override;
    /// Handle node transform being dirtied.
    void OnMarkedDirty(Node* node) override;
    /// Handle draw order changed.
    virtual void OnDrawOrderChanged() = 0;
    /// Update source batches.
    virtual void UpdateSourceBatches() = 0;

    /// Return draw order by layer and order in layer.
    int GetDrawOrder() const { return layer_ << 16u | orderInLayer_; }

    /// Layer.
    int layer_;
    /// Order in layer.
    int orderInLayer_;
    /// Source batches.
    Vector<SourceBatch2D> sourceBatches_;
    /// Source batches dirty flag.
    bool sourceBatchesDirty_;
    /// Renderer2D.
    WeakPtr<Renderer2D> renderer_;
};

}
