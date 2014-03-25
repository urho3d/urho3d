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

#include "Drawable.h"
#include "Sprite2D.h"

namespace Urho3D
{

class DrawableProxy2D;
class MaterialCache2D;
class VertexBuffer;

/// Pixel size (equal 0.01f).
extern URHO3D_API const float PIXEL_SIZE;

/// Base class for 2D visible components.
class URHO3D_API Drawable2D : public Drawable
{
    OBJECT(Drawable2D);

public:
    /// Construct.
    Drawable2D(Context* context);
    /// Destruct.
    ~Drawable2D();
    /// Register object factory. Drawable must be registered first.
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately.
    virtual void ApplyAttributes();
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateBatches(const FrameInfo& frame);
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update.)
    virtual void UpdateGeometry(const FrameInfo& frame);
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    virtual UpdateGeometryType GetUpdateGeometryType();

    /// Set layer.
    void SetLayer(int layer);
    /// Set order in layer.
    void SetOrderInLayer(int orderInLayer);
    /// Set sprite.
    void SetSprite(Sprite2D* sprite);
    /// Set blend mode.
    void SetBlendMode(BlendMode mode);
    /// Set material.
    void SetMaterial(Material* material);

    /// Return layer.
    int GetLayer() const { return layer_; }
    /// Return order in layer.
    int GetOrderInLayer() const { return orderInLayer_; }
    /// Return sprite.
    Sprite2D* GetSprite() const { return sprite_; }
    /// Return texture.
    Texture2D* GetTexture() const { return sprite_ ? sprite_->GetTexture() : 0; }
    /// Return blend mode.
    BlendMode GetBlendMode() const { return blendMode_; }
    /// Return material.
    Material* GetMaterial() const;

    /// Return used material.
    Material* GetUsedMaterial() const { return material_ ? material_ : defaultMaterial_; }
    /// Return all vertices.
    const Vector<Vertex2D>& GetVertices() const { return vertices_; }
    /// Mark vertices and geometry dirty.
    void MarkDirty(bool markWorldBoundingBoxDirty = true);

    /// Set sprite attribute.
    void SetSpriteAttr(ResourceRef value);
    /// Return sprite attribute.
    ResourceRef GetSpriteAttr() const;
    /// Set blend mode attribute.
    void SetBlendModeAttr(BlendMode mode);
    /// Set material attribute.
    void SetMaterialAttr(ResourceRef value);
    /// Return material attribute.
    ResourceRef GetMaterialAttr() const;

protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    /// Update vertices.
    virtual void UpdateVertices() = 0;
    /// Update the material's properties (blend mode and texture).
    void UpdateMaterial();

    /// Layer.
    int layer_;
    /// Order in layer.
    int orderInLayer_;
    /// Sprite.
    SharedPtr<Sprite2D> sprite_;
    /// Material. If null, use a default material. If non-null, use a clone of this for updating the diffuse texture.
    SharedPtr<Material> material_;
    /// Blend mode.
    BlendMode blendMode_;

    /// Vertices.
    Vector<Vertex2D> vertices_;
    /// Geometry.
    SharedPtr<Geometry> geometry_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Vertices dirty flag.
    bool verticesDirty_;
    /// Geometry dirty flag.
    bool geometryDirty_;
    /// Material update pending flag.
    bool materialUpdatePending_;
    /// Default material.
    SharedPtr<Material> defaultMaterial_;
    /// Material cache.
    WeakPtr<MaterialCache2D> materialCache_;
    /// Drawable proxy.
    WeakPtr<DrawableProxy2D> drawableProxy_;
};

inline bool CompareDrawable2Ds(Drawable2D* lhs, Drawable2D* rhs)
{
    return lhs->GetLayer() < rhs->GetLayer() || lhs->GetOrderInLayer() < rhs->GetOrderInLayer();
}

}
