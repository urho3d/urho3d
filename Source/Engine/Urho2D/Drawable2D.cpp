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
#include "Material.h"
#include "Node.h"
#include "ResourceCache.h"
#include "Sprite2D.h"
#include "SpriteSheet2D.h"
#include "Technique.h"
#include "Texture2D.h"
#include "VertexBuffer.h"

#include "DebugNew.h"
#include "Log.h"

namespace Urho3D
{

const float PIXEL_SIZE = 0.01f;
extern const char* blendModeNames[];

Drawable2D::Drawable2D(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY),
    zValue_(0.0f),
    blendMode_(BLEND_ALPHA),
    vertexBuffer_(new VertexBuffer(context_)),
    verticesDirty_(true),
    geometryDirty_(true),
    materialUpdatePending_(false)
{
    geometry_ = new Geometry(context);
    geometry_->SetVertexBuffer(0, vertexBuffer_, MASK_VERTEX2D);
    batches_.Resize(1);
    batches_[0].geometry_ = geometry_;
    CreateDefaultMaterial();
}

Drawable2D::~Drawable2D()
{
}

void Drawable2D::RegisterObject(Context* context)
{
    ACCESSOR_ATTRIBUTE(Drawable2D, VAR_FLOAT, "Z Value", GetZValue, SetZValue, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Drawable2D, VAR_RESOURCEREF, "Sprite", GetSpriteAttr, SetSpriteAttr, ResourceRef, ResourceRef(Sprite2D::GetTypeStatic()), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(Drawable2D, VAR_RESOURCEREF, "Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()), AM_DEFAULT);
    ENUM_ACCESSOR_ATTRIBUTE(Drawable2D, "Blend Mode", GetBlendMode, SetBlendModeAttr, BlendMode, blendModeNames, BLEND_ALPHA, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(Drawable2D, Drawable);
}

void Drawable2D::ApplyAttributes()
{
    if (materialUpdatePending_)
    {
        materialUpdatePending_ = false;
        UpdateMaterial();
    }
}

void Drawable2D::UpdateBatches(const FrameInfo& frame)
{
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    distance_ = frame.camera_->GetDistance(GetWorldBoundingBox().Center());

    batches_[0].distance_ = distance_;
    batches_[0].worldTransform_ = &worldTransform;
}

void Drawable2D::UpdateGeometry(const FrameInfo& frame)
{
    if (verticesDirty_)
        UpdateVertices();

    if (geometryDirty_ || vertexBuffer_->IsDataLost())
    {
        unsigned vertexCount = vertices_.Size() / 4 * 6;
        if (vertexCount)
        {
            vertexBuffer_->SetSize(vertexCount, MASK_VERTEX2D);
            Vertex2D* dest = reinterpret_cast<Vertex2D*>(vertexBuffer_->Lock(0, vertexCount, true));
            if (dest)
            {
                for (unsigned i = 0; i < vertices_.Size(); i += 4)
                {
                    dest[0] = vertices_[i + 0];
                    dest[1] = vertices_[i + 1];
                    dest[2] = vertices_[i + 2];

                    dest[3] = vertices_[i + 0];
                    dest[4] = vertices_[i + 2];
                    dest[5] = vertices_[i + 3];

                    dest += 6;
                }

                vertexBuffer_->Unlock();
            }
            else
                LOGERROR("Failed to lock vertex buffer");
        }
        geometry_->SetDrawRange(TRIANGLE_LIST, 0, 0, 0, vertexCount);

        vertexBuffer_->ClearDataLost();
        geometryDirty_ = false;
    }
}

UpdateGeometryType Drawable2D::GetUpdateGeometryType()
{
    if (geometryDirty_ || vertexBuffer_->IsDataLost())
        return UPDATE_MAIN_THREAD;
    else
        return UPDATE_NONE;
}

void Drawable2D::SetSprite(Sprite2D* sprite)
{
    if (sprite == sprite_)
        return;

    sprite_ = sprite;
    MarkDirty();
    UpdateMaterial();
    MarkNetworkUpdate();
}

void Drawable2D::SetMaterial(Material* material)
{
    if (material == material_)
        return;

    material_ = material;
    // If a null material was specified, create one with defaults, otherwise clone the material so that
    // the diffuse texture can be changed according to the sprite being used
    if (!material_)
        CreateDefaultMaterial();
    else
        batches_[0].material_ = material_->Clone();
    UpdateMaterial();
    MarkNetworkUpdate();
}

void Drawable2D::SetBlendMode(BlendMode mode)
{
    if (mode == blendMode_)
        return;

    blendMode_ = mode;
    UpdateMaterial();
    MarkNetworkUpdate();
}

void Drawable2D::SetZValue(float zValue)
{
    if (zValue == zValue_)
        return;

    zValue_ = zValue;
    MarkDirty();
    MarkNetworkUpdate();
}

Material* Drawable2D::GetMaterial() const
{
    return material_;
}

void Drawable2D::MarkDirty(bool markWorldBoundingBoxDirty)
{
    verticesDirty_ = true;
    geometryDirty_ = true;

    if (markWorldBoundingBoxDirty)
        OnMarkedDirty(node_);
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

void Drawable2D::SetBlendModeAttr(BlendMode mode)
{
    // Delay applying material update
    materialUpdatePending_ = true;

    SetBlendMode(mode);
}

void Drawable2D::OnWorldBoundingBoxUpdate()
{
    if (verticesDirty_)
    {
        UpdateVertices();

        boundingBox_.Clear();
        for (unsigned i = 0; i < vertices_.Size(); ++i)
            boundingBox_.Merge(vertices_[i].position_);
    }

    worldBoundingBox_ = boundingBox_.Transformed(node_->GetWorldTransform());
}

void Drawable2D::CreateDefaultMaterial()
{
    SharedPtr<Material> material(new Material(context_));
    
    Technique* tech = new Technique(context_);
    Pass* pass = tech->CreatePass(PASS_ALPHA);
    pass->SetVertexShader("Basic");
    pass->SetVertexShaderDefines("DIFFMAP VERTEXCOLOR");

    pass->SetPixelShader("Basic");
    pass->SetPixelShaderDefines("DIFFMAP VERTEXCOLOR");
    
    pass->SetDepthWrite(false);

    material->SetTechnique(0, tech);
    material->SetCullMode(CULL_NONE);

    batches_[0].material_ = material;
}

void Drawable2D::UpdateMaterial()
{
    // Delay the material update
    if (materialUpdatePending_)
        return;

    Material* material = batches_[0].material_;
    assert(material);
    
    // If we are using the default created material, we can update blend mode. Otherwise must respect what is set in the material
    if (!material_)
    {
        Technique* technique = material->GetTechnique(0);
        Pass* pass = technique->GetPass(PASS_ALPHA);
        if (pass)
            pass->SetBlendMode(blendMode_);
    }
    
    // Update diffuse texture from sprite
    if (sprite_)
    {
        Texture2D* texture = sprite_->GetTexture();
        material->SetTexture(TU_DIFFUSE, texture);
    }
}

}
