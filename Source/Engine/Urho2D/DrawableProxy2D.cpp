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
#include "Context.h"
#include "Drawable2D.h"
#include "DrawableProxy2D.h"
#include "Material.h"
#include "Scene.h"
#include "Technique.h"
#include "Texture2D.h"

#include "DebugNew.h"

namespace Urho3D
{

DrawableProxy2D::DrawableProxy2D(Context* context) :
    Component(context)
{
}

DrawableProxy2D::~DrawableProxy2D()
{
}

void DrawableProxy2D::RegisterObject(Context* context)
{
    context->RegisterFactory<DrawableProxy2D>();
}

void DrawableProxy2D::AddDrawable(Drawable2D* drawable)
{
    if (!drawable)
        return;

    WeakPtr<Drawable2D> drawablePtr(drawable);
    if (drawables_.Contains(drawablePtr))
        return;

    drawables_.Push(drawablePtr);
}

void DrawableProxy2D::RemoveDrawable(Drawable2D* drawable)
{
    if (!drawable)
        return;

    WeakPtr<Drawable2D> drawablePtr(drawable);
    drawables_.Remove(drawablePtr);
}

Material* DrawableProxy2D::GetMaterial(Drawable2D* drawable)
{
    if (!drawable)
        return 0;

    Texture2D* texture = drawable->GetTexture();
    if (!texture)
        return 0;

    BlendMode blendMode = drawable->GetBlendMode();
    HashMap<Texture2D*, HashMap<int, SharedPtr<Material> > >::Iterator t = materials_.Find(texture);
    if (t == materials_.End())
    {
        Material* material(CreateMaterial(texture, blendMode));
        materials_[texture][blendMode] = material;
        return material;
    }

    HashMap<int, SharedPtr<Material> >& materials = t->second_;
    HashMap<int, SharedPtr<Material> >::Iterator b = materials.Find(blendMode);
    if (b != materials.End())
        return b->second_;

    Material* material(CreateMaterial(texture, blendMode));
    materials[blendMode] = material;

    return material;
}

Material* DrawableProxy2D::CreateMaterial(Texture2D* texture, BlendMode blendMode) const
{
    Material* material = new Material(context_);
    
    Technique* tech = new Technique(context_);
    Pass* pass = tech->CreatePass(PASS_ALPHA);
    pass->SetBlendMode(blendMode);

    pass->SetVertexShader("Basic");
    pass->SetVertexShaderDefines("DIFFMAP VERTEXCOLOR");

    pass->SetPixelShader("Basic");
    pass->SetPixelShaderDefines("DIFFMAP VERTEXCOLOR");
    
    pass->SetDepthWrite(false);

    material->SetTechnique(0, tech);
    material->SetCullMode(CULL_NONE);

    material->SetTexture(TU_DIFFUSE, texture);

    return material;
}

}
