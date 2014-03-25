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
#include "DrawableProxy2D.h"
#include "Geometry.h"
#include "Log.h"
#include "Material.h"
#include "MaterialCache2D.h"
#include "Node.h"
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
    materialUpdatePending_(false)
{   
}

Drawable2D::~Drawable2D()
{
}

void Drawable2D::RegisterObject(Context* context)
{
    ACCESSOR_ATTRIBUTE(Drawable2D, VAR_INT, "Layer", GetLayer, SetLayer, int, 0, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Drawable2D, VAR_INT, "Order in Layer", GetOrderInLayer, SetOrderInLayer, int, 0, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Drawable2D, VAR_RESOURCEREF, "Sprite", GetSpriteAttr, SetSpriteAttr, ResourceRef, ResourceRef(Sprite2D::GetTypeStatic()), AM_DEFAULT);
    ENUM_ACCESSOR_ATTRIBUTE(Drawable2D, "Blend Mode", GetBlendMode, SetBlendModeAttr, BlendMode, blendModeNames, BLEND_ALPHA, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Drawable2D, VAR_RESOURCEREF, "Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()), AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(Drawable2D, Drawable);
}

void Drawable2D::ApplyAttributes()
{
    if (materialUpdatePending_)
    {
        materialUpdatePending_ = false;
        UpdateDefaultMaterial();
    }
}

void Drawable2D::OnSetEnabled()
{
    if (!drawableProxy_)
        return;

    if (IsEnabledEffective())
        drawableProxy_->AddDrawable(this);
    else
        drawableProxy_->RemoveDrawable(this);
}

void Drawable2D::SetLayer(int layer)
{
    if (layer == layer_)
        return;

    layer_ = layer;

    if (drawableProxy_)
        drawableProxy_->MarkOrderDirty();

    MarkNetworkUpdate();
}

void Drawable2D::SetOrderInLayer(int orderInLayer)
{
    if (orderInLayer == orderInLayer_)
        return;

    orderInLayer_ = orderInLayer;
    
    if (drawableProxy_)
        drawableProxy_->MarkOrderDirty();

    MarkNetworkUpdate();
}

void Drawable2D::SetSprite(Sprite2D* sprite)
{
    if (sprite == sprite_)
        return;

    sprite_ = sprite;    
    
    verticesDirty_ = true;
    OnMarkedDirty(node_);
    UpdateDefaultMaterial();
    MarkNetworkUpdate();
}

void Drawable2D::SetBlendMode(BlendMode blendMode)
{
    if (blendMode == blendMode_)
        return;

    blendMode_ = blendMode;

    UpdateDefaultMaterial();
    MarkNetworkUpdate();
}

void Drawable2D::SetMaterial(Material* material)
{
    if (material == material_)
        return;

    material_ = material;

    MarkNetworkUpdate();
}

Material* Drawable2D::GetMaterial() const
{
    return material_;
}

Material* Drawable2D::GetUsedMaterial() const
{
    return material_ ? material_ : defaultMaterial_;
}

const Vector<Vertex2D>& Drawable2D::GetVertices()
{
    if (verticesDirty_)
        UpdateVertices();
    return vertices_;
}

void Drawable2D::SetSpriteAttr(ResourceRef value)
{
    // Delay applying material update
    materialUpdatePending_ = true;

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    if (value.type_ == Sprite2D::GetTypeStatic())
    {
        SetSprite(cache->GetResource<Sprite2D>(value.name_));
        return;
    }

    if (value.type_ == SpriteSheet2D::GetTypeStatic())
    {
        // value.name_ include sprite speet name and sprite name.
        Vector<String> names = value.name_.Split('@');
        if (names.Size() != 2)
            return;

        const String& spriteSheetName = names[0];
        const String& spriteName = names[1];

        SpriteSheet2D* spriteSheet = cache->GetResource<SpriteSheet2D>(spriteSheetName);
        if (!spriteSheet)
            return;

        SetSprite(spriteSheet->GetSprite(spriteName));
    }
}

ResourceRef Drawable2D::GetSpriteAttr() const
{
    SpriteSheet2D* spriteSheet = 0;
    if (sprite_)
        spriteSheet = sprite_->GetSpriteSheet();

    if (!spriteSheet)
        return GetResourceRef(sprite_, Sprite2D::GetTypeStatic());

    // Combine sprite sheet name and sprite name as resource name.
    return ResourceRef(spriteSheet->GetType(), spriteSheet->GetName() + "@" + sprite_->GetName());
}

void Drawable2D::SetBlendModeAttr(BlendMode mode)
{
    // Delay applying material update
    materialUpdatePending_ = true;

    SetBlendMode(mode);
}

void Drawable2D::SetMaterialAttr(ResourceRef value)
{
    // Delay applying material update
    materialUpdatePending_ = true;

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetMaterial(cache->GetResource<Material>(value.name_));
}

ResourceRef Drawable2D::GetMaterialAttr() const
{
    return GetResourceRef(material_, Material::GetTypeStatic());
}

void Drawable2D::OnNodeSet(Node* node)
{
    Drawable::OnNodeSet(node);

    if (node)
    {
        node->AddListener(this);

        Scene* scene = GetScene();
        if (scene)
        {
            materialCache_ = scene->GetOrCreateComponent<MaterialCache2D>();
            drawableProxy_ = scene->GetOrCreateComponent<DrawableProxy2D>();
            if (IsEnabledEffective())
                drawableProxy_->AddDrawable(this);
        }
    }
}

void Drawable2D::OnMarkedDirty(Node* node)
{
    Drawable::OnMarkedDirty(node);

    verticesDirty_ = true;
}

void Drawable2D::UpdateDefaultMaterial()
{
    // Delay the material update
    if (materialUpdatePending_)
        return;
    
    defaultMaterial_ = materialCache_->GetMaterial(GetTexture(), blendMode_);
}

}
