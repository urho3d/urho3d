//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
#include "Animation.h"
#include "Material.h"
#include "Model.h"
#include "PixelShader.h"
#include "Renderer.h"
#include "RendererResourceFactory.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "VertexShader.h"

#include "DebugNew.h"

RendererResourceFactory::RendererResourceFactory(Renderer* renderer) :
    mRenderer(renderer)
{
}

Resource* RendererResourceFactory::createResource(ShortStringHash type, const std::string& name)
{
    if (type == Material::getTypeStatic())
        return new Material(name);
    
    if (type == Texture2D::getTypeStatic())
        return new Texture2D(mRenderer, TEXTURE_STATIC, name);
    
    if (type == TextureCube::getTypeStatic())
        return new TextureCube(mRenderer, TEXTURE_STATIC, name);
    
    if (type == VertexShader::getTypeStatic())
        return new VertexShader(mRenderer, name);
    
    if (type == PixelShader::getTypeStatic())
        return new PixelShader(mRenderer, name);
    
    if (type == Model::getTypeStatic())
        return new Model(mRenderer, name);
    
    if (type == Animation::getTypeStatic())
        return new Animation(name);
    
    return 0;
}
