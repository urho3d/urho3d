//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../../Container/HashMap.h"
#include "../../Core/Timer.h"
#include "../../Math/Color.h"

#if defined(ANDROID) || defined (RPI) || defined (__EMSCRIPTEN__)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined(IOS)
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#else
#include <GLEW/glew.h>
#endif

#ifndef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83f1
#endif
#ifndef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83f2
#endif
#ifndef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83f3
#endif
#ifndef GL_ETC1_RGB8_OES
#define GL_ETC1_RGB8_OES 0x8d64
#endif
#ifndef COMPRESSED_RGB_PVRTC_4BPPV1_IMG
#define COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8c00
#endif
#ifndef COMPRESSED_RGB_PVRTC_2BPPV1_IMG
#define COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8c01
#endif
#ifndef COMPRESSED_RGBA_PVRTC_4BPPV1_IMG
#define COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8c02
#endif
#ifndef COMPRESSED_RGBA_PVRTC_2BPPV1_IMG
#define COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8c03
#endif

#include <SDL/SDL.h>

namespace Urho3D
{

class Context;

/// Cached state of a frame buffer object
struct FrameBufferObject
{
    FrameBufferObject() :
        fbo_(0),
        depthAttachment_(0),
        readBuffers_(M_MAX_UNSIGNED),
        drawBuffers_(M_MAX_UNSIGNED)
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
};

/// %Graphics subsystem implementation. Holds API-specific objects.
class URHO3D_API GraphicsImpl
{
    friend class Graphics;

public:
    /// Construct.
    GraphicsImpl();

    /// Return the SDL window.
    SDL_Window* GetWindow() const { return window_; }
    /// Return the GL Context.
    const SDL_GLContext& GetGLContext() { return context_; }

private:
    /// SDL window.
    SDL_Window* window_;
    /// SDL OpenGL context.
    SDL_GLContext context_;
    /// IOS system framebuffer handle.
    unsigned systemFBO_;
    /// Active texture unit.
    unsigned activeTexture_;
    /// Enabled vertex attributes bitmask.
    unsigned enabledVertexAttributes_;
    /// Vertex attributes bitmask used by the current shader program.
    unsigned usedVertexAttributes_;
    /// Vertex attribute instancing bitmask for keeping track of divisors.
    unsigned instancingVertexAttributes_;
    /// Current mapping of vertex attribute locations by semantic. The map is owned by the shader program, so care must be taken to switch a null shader program when it's destroyed.
    const HashMap<Pair<unsigned char, unsigned char>, unsigned>* vertexAttributes_;
    /// Currently bound frame buffer object.
    unsigned boundFBO_;
    /// Currently bound vertex buffer object.
    unsigned boundVBO_;
    /// Currently bound uniform buffer object.
    unsigned boundUBO_;
    /// Current pixel format.
    int pixelFormat_;
    /// Map for FBO's per resolution and format.
    HashMap<unsigned long long, FrameBufferObject> frameBuffers_;
    /// Need FBO commit flag.
    bool fboDirty_;
    /// Need vertex attribute pointer update flag.
    bool vertexBuffersDirty_;
    /// sRGB write mode flag.
    bool sRGBWrite_;
};

}
