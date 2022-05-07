// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Graphics/Camera.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/Renderer.h"
#include "../../GraphicsAPI/GraphicsImpl.h"
#include "../../GraphicsAPI/RenderSurface.h"
#include "../../GraphicsAPI/Texture.h"

#include "../../DebugNew.h"

#ifdef GL_ES_VERSION_2_0
#define GL_RENDERBUFFER_EXT GL_RENDERBUFFER
#define glGenRenderbuffersEXT glGenRenderbuffers
#define glBindRenderbufferEXT glBindRenderbuffer
#define glRenderbufferStorageEXT glRenderbufferStorage
#define glDeleteRenderbuffersEXT glDeleteRenderbuffers
#endif

namespace Urho3D
{

void RenderSurface::Constructor_OGL(Texture* parentTexture)
{
    parentTexture_ = parentTexture;
    target_ = GL_TEXTURE_2D;
    renderBuffer_ = 0;
}

bool RenderSurface::CreateRenderBuffer_OGL(unsigned width, unsigned height, unsigned format, int multiSample)
{
    Graphics* graphics = parentTexture_->GetGraphics();
    if (!graphics)
        return false;

    Release_OGL();

#ifndef GL_ES_VERSION_2_0
    if (Graphics::GetGL3Support())
    {
        glGenRenderbuffers(1, &renderBuffer_);
        glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer_);
        if (multiSample > 1)
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, multiSample, format, width, height);
        else
            glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
    else
#endif
    {
        glGenRenderbuffersEXT(1, &renderBuffer_);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, renderBuffer_);
#ifndef GL_ES_VERSION_2_0
        if (multiSample > 1)
            glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, multiSample, format, width, height);
        else
#endif
            glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, format, width, height);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
    }

    return true;
}

void RenderSurface::OnDeviceLost_OGL()
{
    Graphics* graphics = parentTexture_->GetGraphics();
    if (!graphics)
        return;

    for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
    {
        if (graphics->GetRenderTarget(i) == this)
            graphics->ResetRenderTarget(i);
    }

    if (graphics->GetDepthStencil() == this)
        graphics->ResetDepthStencil();

    // Clean up also from non-active FBOs
    graphics->CleanupRenderSurface_OGL(this);

    if (renderBuffer_ && !graphics->IsDeviceLost())
        glDeleteRenderbuffersEXT(1, &renderBuffer_);

    renderBuffer_ = 0;
}

void RenderSurface::Release_OGL()
{
    Graphics* graphics = parentTexture_->GetGraphics();
    if (!graphics)
        return;

    if (!graphics->IsDeviceLost())
    {
        for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        {
            if (graphics->GetRenderTarget(i) == this)
                graphics->ResetRenderTarget(i);
        }

        if (graphics->GetDepthStencil() == this)
            graphics->ResetDepthStencil();

        // Clean up also from non-active FBOs
        graphics->CleanupRenderSurface_OGL(this);

        if (renderBuffer_)
            glDeleteRenderbuffersEXT(1, &renderBuffer_);
    }

    renderBuffer_ = 0;
}

}
