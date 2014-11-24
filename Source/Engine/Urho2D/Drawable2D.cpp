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
#include "Camera.h"
#include "Context.h"
#include "Drawable2D.h"
#include "Geometry.h"
#include "Log.h"
#include "Material.h"
#include "Node.h"
#include "Renderer2D.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "Sprite2D.h"
#include "SpriteSheet2D.h"
#include "Technique.h"
#include "Texture2D.h"
#include "VertexBuffer.h"

#include "DebugNew.h"

namespace Urho3D
{

const float PIXEL_SIZE = 0.01f;
extern const char* blendModeNames[];

Drawable2D::Drawable2D(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY),
    layer_(0),
    orderInLayer_(0),
    blendMode_(BLEND_ALPHA),
    verticesDirty_(true),
    materialUpdatePending_(false),
    visibility_(true)
{
}

Drawable2D::~Drawable2D()
{
}

void Drawable2D::RegisterObject(Context* context)
{
    ACCESSOR_ATTRIBUTE("Layer", GetLayer, SetLayer, int, 0, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Order in Layer", GetOrderInLayer, SetOrderInLayer, int, 0, AM_DEFAULT);
    ENUM_ACCESSOR_ATTRIBUTE("Blend Mode", GetBlendMode, SetBlendModeAttr, BlendMode, blendModeNames, BLEND_ALPHA, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(Drawable);
}

void Drawable2D::SetLayer(int layer)
{
    if (layer == layer_)
        return;

    layer_ = layer;

    MarkNetworkUpdate();
}

void Drawable2D::SetOrderInLayer(int orderInLayer)
{
    if (orderInLayer == orderInLayer_)
        return;

    orderInLayer_ = orderInLayer;

    MarkNetworkUpdate();
}

void Drawable2D::SetTexture(Texture2D* texture)
{
    if (texture == texture_)
        return;

    texture_ = texture;

    verticesDirty_ = true;
    defaultMaterial_ = 0;
    
    OnMarkedDirty(node_);
    MarkNetworkUpdate();
}

void Drawable2D::SetBlendMode(BlendMode blendMode)
{
    if (blendMode == blendMode_)
        return;

    blendMode_ = blendMode;
    defaultMaterial_ = 0;

    MarkNetworkUpdate();
}

Texture2D* Drawable2D::GetTexture() const
{
    return texture_;
}

void Drawable2D::SetDefaultMaterial(Material* material)
{
    defaultMaterial_ = material;
}

Material* Drawable2D::GetDefaultMaterial() const
{
    return defaultMaterial_;
}

const Vector<Vertex2D>& Drawable2D::GetVertices()
{
    if (verticesDirty_)
        UpdateVertices();
    return vertices_;
}

void Drawable2D::SetBlendModeAttr(BlendMode mode)
{
    // Delay applying material update
    materialUpdatePending_ = true;

    SetBlendMode(mode);
}

void Drawable2D::OnNodeSet(Node* node)
{
    Drawable::OnNodeSet(node);

    if (node)
    {
        Scene* scene = GetScene();
        if (scene)
            scene->GetOrCreateComponent<Renderer2D>();
    }
}

void Drawable2D::OnMarkedDirty(Node* node)
{
    Drawable::OnMarkedDirty(node);

    verticesDirty_ = true;
}

}
