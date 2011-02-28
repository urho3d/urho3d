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
#include "Camera.h"
#include "Log.h"
#include "Renderer.h"
#include "RendererImpl.h"
#include "RenderSurface.h"
#include "Scene.h"
#include "Texture.h"

#include "DebugNew.h"

Viewport::Viewport() :
    mRect(IntRect::sZero)
{
}

Viewport::Viewport(Scene* scene, Camera* camera) :
    mScene(scene),
    mCamera(camera),
    mRect(IntRect::sZero)
{
}

Viewport::Viewport(Scene* scene, Camera* camera, const IntRect& rect) :
    mScene(scene),
    mCamera(camera),
    mRect(rect)
{
}

RenderSurface::RenderSurface(Texture* parentTexture) :
    mParentTexture(parentTexture),
    mSurface(0)
{
}

RenderSurface::~RenderSurface()
{
    release();
}

void RenderSurface::setViewport(const Viewport& viewport)
{
    mViewport = viewport;
}

void RenderSurface::setLinkedRenderTarget(RenderSurface* renderTarget)
{
    if (renderTarget == this)
        return;
    mLinkedRenderTarget = renderTarget;
}

void RenderSurface::setLinkedDepthBuffer(RenderSurface* depthBuffer)
{
    if (depthBuffer == this)
        return;
    mLinkedDepthBuffer = depthBuffer;
}

void RenderSurface::release()
{
    Renderer* renderer = mParentTexture->getRenderer();
    if (!renderer)
        return;
    
    if (mSurface)
    {
        for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        {
            if (renderer->getRenderTarget(i) == this)
                renderer->resetRenderTarget(i);
        }
        
        if (renderer->getDepthStencil() == this)
            renderer->resetDepthStencil();
        
        ((IDirect3DSurface9*)mSurface)->Release();
        mSurface = 0;
    }
}

int RenderSurface::getWidth() const
{
    return mParentTexture->getWidth();
}

int RenderSurface::getHeight() const
{
    return mParentTexture->getHeight();
}

TextureUsage RenderSurface::getUsage() const
{
    return mParentTexture->getUsage();
}
