//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include "Color.h"
#include "Map.h"
#include "Timer.h"

#ifndef ANDROID
#include <GLee.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include <SDL.h>

class Context;

/// Cached state of a frame buffer object
struct FrameBufferObject
{
    FrameBufferObject() :
        fbo_(0),
        readBuffers_(M_MAX_UNSIGNED),
        drawBuffers_(M_MAX_UNSIGNED),
        depthAttachment_(0)
    {
        for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
            colorAttachments_[i] = 0;
    }
    
    /// Frame buffer handle.
    unsigned fbo_;
    /// Bound color attachment textures.
    RenderSurface* colorAttachments_[MAX_RENDERTARGETS];
    /// Bound depth/stencil attachment.
    RenderSurface* depthAttachment_;
    /// Read buffer bits.
    unsigned readBuffers_;
    /// Draw buffer bits.
    unsigned drawBuffers_;
    /// Use timer for cleaning up.
    Timer useTimer_;
};

/// %Graphics subsystem implementation. Holds API-specific objects.
class GraphicsImpl
{
    friend class Graphics;
    
public:
    /// Construct.
    GraphicsImpl();
    /// Return the SDL window.
    SDL_Window* GetWindow() const { return window_; }
    
private:
    /// SDL window.
    SDL_Window* window_;
    /// SDL OpenGL context
    SDL_GLContext context_;
    /// Active texture unit.
    unsigned activeTexture_;
    /// Vertex attributes in use.
    unsigned enabledAttributes_;
    /// Currently bound frame buffer object.
    unsigned boundFbo_;
    /// Current pixel format.
    int pixelFormat_;
    /// Current depth bits.
    int depthBits_;
    /// Backbuffer depth bits.
    int windowDepthBits_;
    /// Map for FBO's per resolution and format.
    Map<unsigned long long, FrameBufferObject> frameBuffers_;
    /// Need FBO commit flag.
    bool fboDirty_;
};
