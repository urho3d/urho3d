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

#include "../Graphics/Camera.h"
#include "../Core/Context.h"
#include "../Urho2D/Drawable2D.h"
#include "../Graphics/Material.h"
#include "../Urho2D/Renderer2D.h"
#include "../Scene/Scene.h"
#include "../Graphics/Texture2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

const float PIXEL_SIZE = 0.01f;
extern const char* blendModeNames[];

Drawable2D::Drawable2D(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY2D),
    layer_(0),
    orderInLayer_(0),
    blendMode_(BLEND_ALPHA),
    verticesDirty_(true)
{
}

Drawable2D::~Drawable2D()
{
    if (renderer_)
        renderer_->RemoveDrawable(this);
}

void Drawable2D::RegisterObject(Context* context)
{
    ACCESSOR_ATTRIBUTE("Layer", GetLayer, SetLayer, int, 0, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE("Order in Layer", GetOrderInLayer, SetOrderInLayer, int, 0, AM_DEFAULT);
    ENUM_ACCESSOR_ATTRIBUTE("Blend Mode", GetBlendMode, SetBlendMode, BlendMode, blendModeNames, BLEND_ALPHA, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(Drawable);
}

void Drawable2D::OnSetEnabled()
{
    bool enabled = IsEnabledEffective();

    if (enabled && renderer_)
        renderer_->AddDrawable(this);
    else if (!enabled && renderer_)
        renderer_->RemoveDrawable(this);
}

void Drawable2D::SetLayer(int layer)
{
    if (layer == layer_)
        return;

    layer_ = layer;

    OnLayerChanged();

    if (renderer_)
        renderer_->MarkOrderDirty();

    MarkNetworkUpdate();
}

void Drawable2D::SetOrderInLayer(int orderInLayer)
{
    if (orderInLayer == orderInLayer_)
        return;

    orderInLayer_ = orderInLayer;
    
    OnLayerChanged();

    if (renderer_)
        renderer_->MarkOrderDirty();

    MarkNetworkUpdate();
}

void Drawable2D::SetTexture(Texture2D* texture)
{
    if (texture == texture_)
        return;

    texture_ = texture;

    verticesDirty_ = true;
    material_ = 0;
    if (renderer_)
        renderer_->MarkMaterialDirty(this);

    OnMarkedDirty(node_);

    MarkNetworkUpdate();
}

void Drawable2D::SetBlendMode(BlendMode blendMode)
{
    if (blendMode == blendMode_)
        return;

    blendMode_ = blendMode;
    material_ = 0;
    if (renderer_)
        renderer_->MarkMaterialDirty(this);

    OnBlendModeChanged();

    MarkNetworkUpdate();
}

void Drawable2D::SetCustomMaterial(Material* customMaterial)
{
    if (customMaterial == customMaterial_)
        return;

    customMaterial_ = customMaterial;
    material_ = 0;
    if (renderer_)
        renderer_->MarkMaterialDirty(this);

    MarkNetworkUpdate();
}

Texture2D* Drawable2D::GetTexture() const
{
    return texture_;
}

Material* Drawable2D::GetCustomMaterial() const
{
    return customMaterial_;
}

void Drawable2D::SetMaterial(Material* material)
{
    material_ = material;
}

Material* Drawable2D::GetMaterial() const
{
    return customMaterial_ ? customMaterial_ : material_;
}

const Vector<Vertex2D>& Drawable2D::GetVertices()
{
    if (verticesDirty_)
        UpdateVertices();
    return vertices_;
}

void Drawable2D::OnNodeSet(Node* node)
{
    // Do not call Drawable::OnNodeSet(node)

    if (node)
    {
        Scene* scene = GetScene();
        if (scene)
        {
            renderer_ = scene->GetOrCreateComponent<Renderer2D>();
            if (IsEnabledEffective())
                renderer_->AddDrawable(this);
        }

        node->AddListener(this);
    }
    else
    {
        if (renderer_)
            renderer_->RemoveDrawable(this);
    }
}

void Drawable2D::OnMarkedDirty(Node* node)
{
    Drawable::OnMarkedDirty(node);

    verticesDirty_ = true;
}

void Drawable2D::OnLayerChanged()
{
}

void Drawable2D::OnBlendModeChanged()
{
}

}
