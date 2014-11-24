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
#include "GraphicsDefs.h"

namespace Urho3D
{

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

static const unsigned MASK_VERTEX2D = MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1;

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
    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled();

    /// Set layer.
    void SetLayer(int layer);
    /// Set order in layer.
    void SetOrderInLayer(int orderInLayer);
    /// Set texture.
    void SetTexture(Texture2D* texture);
    /// Set blend mode.
    void SetBlendMode(BlendMode mode);
    /// Set material.
    void SetMaterial(Material* material);

    /// Return layer.
    int GetLayer() const { return layer_; }
    /// Return order in layer.
    int GetOrderInLayer() const { return orderInLayer_; }
    /// Return texture.
    Texture2D* GetTexture() const;
    /// Return blend mode.
    BlendMode GetBlendMode() const { return blendMode_; }
    /// Return material.
    Material* GetMaterial() const;

    /// Return used material.
    Material* GetUsedMaterial() const;
    /// Return all vertices.
    const Vector<Vertex2D>& GetVertices();
    /// Set visibility.
    void SetVisibility(bool visibility) { visibility_ = visibility; }
    /// Return visibility.
    bool GetVisibility() const { return visibility_; }

    /// Set blend mode attribute.
    void SetBlendModeAttr(BlendMode mode);
    /// Set material attribute.
    void SetMaterialAttr(const ResourceRef& value);
    /// Return material attribute.
    ResourceRef GetMaterialAttr() const;

protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);
    /// Update vertices.
    virtual void UpdateVertices() = 0;
    /// Update the material's properties (blend mode and texture).
    void UpdateDefaultMaterial();

    /// Layer.
    int layer_;
    /// Order in layer.
    int orderInLayer_;
    /// Texture.
    SharedPtr<Texture2D> texture_;
    /// Material. If null, use a default material. If non-null, use a clone of this for updating the diffuse texture.
    SharedPtr<Material> material_;
    /// Blend mode.
    BlendMode blendMode_;

    /// Vertices.
    Vector<Vertex2D> vertices_;
    /// Vertices dirty flag.
    bool verticesDirty_;
    /// Material update pending flag.
    bool materialUpdatePending_;
    /// Default material.
    SharedPtr<Material> defaultMaterial_;
    /// 2D rendererer.
    WeakPtr<Renderer2D> renderer_;
    /// Test visible.
    bool visibility_;
};

}
