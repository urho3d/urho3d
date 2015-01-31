//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Graphics/Drawable.h"
#include "../Graphics/GraphicsDefs.h"

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
    /// Set custom material. 
    void SetCustomMaterial(Material* customMaterial);
    
    /// Return layer.
    int GetLayer() const { return layer_; }
    /// Return order in layer.
    int GetOrderInLayer() const { return orderInLayer_; }
    /// Return texture.
    Texture2D* GetTexture() const;
    /// Return blend mode.
    BlendMode GetBlendMode() const { return blendMode_; }
    /// Return custom material.
    Material* GetCustomMaterial() const;

    /// Set material (called by Renderer2D).
    void SetMaterial(Material* material);
    /// Return custom material or material (called by Renderer2D).
    Material* GetMaterial() const;
    /// Return all vertices (called by Renderer2D).
    const Vector<Vertex2D>& GetVertices();

protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Handle node transform being dirtied.
    virtual void OnMarkedDirty(Node* node);
    /// Handle layer changed.
    virtual void OnLayerChanged();
    /// Handle blend mode changed.
    virtual void OnBlendModeChanged();
    /// Update vertices.
    virtual void UpdateVertices() = 0;
    

    /// Layer.
    int layer_;
    /// Order in layer.
    int orderInLayer_;
    /// Texture.
    SharedPtr<Texture2D> texture_;
    /// Blend mode.
    BlendMode blendMode_;
    /// Custom material.
    SharedPtr<Material> customMaterial_;

    /// Vertices.
    Vector<Vertex2D> vertices_;
    /// Vertices dirty flag.
    bool verticesDirty_;
    /// Material.
    SharedPtr<Material> material_;
    /// Renderer2D.
    WeakPtr<Renderer2D> renderer_;
};

}
