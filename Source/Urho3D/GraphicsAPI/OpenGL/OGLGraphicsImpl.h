// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../../Container/HashMap.h"
#include "../../Core/Timer.h"
#include "../../GraphicsAPI/ConstantBuffer.h"
#include "../../GraphicsAPI/OpenGL/OGLShaderProgram.h"
#include "../../GraphicsAPI/Texture2D.h"
#include "../../Math/Color.h"

#if defined(IOS) || defined(TVOS)
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif defined(__ANDROID__) || defined (__arm__) || defined(__aarch64__) || defined (__EMSCRIPTEN__)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
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
#ifndef GL_ETC2_RGB8_OES
#define GL_ETC2_RGB8_OES 0x9274
#endif
#ifndef GL_ETC2_RGBA8_OES
#define GL_ETC2_RGBA8_OES 0x9278
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

using SDL_GLContext = void *;

namespace Urho3D
{

class Context;

using ConstantBufferMap = HashMap<unsigned, SharedPtr<ConstantBuffer> >;
using ShaderProgramMap_OGL = HashMap<Pair<ShaderVariation*, ShaderVariation*>, SharedPtr<ShaderProgram_OGL> >;

/// Cached state of a frame buffer object.
struct FrameBufferObject
{
    /// Frame buffer handle.
    unsigned fbo_{};
    /// Bound color attachment textures.
    RenderSurface* colorAttachments_[MAX_RENDERTARGETS]{};
    /// Bound depth/stencil attachment.
    RenderSurface* depthAttachment_{};
    /// Read buffer bits.
    unsigned readBuffers_{M_MAX_UNSIGNED};
    /// Draw buffer bits.
    unsigned drawBuffers_{M_MAX_UNSIGNED};
};

/// %Graphics subsystem implementation. Holds API-specific objects.
class URHO3D_API GraphicsImpl_OGL
{
    friend class Graphics;

public:
    /// Construct.
    GraphicsImpl_OGL() = default;

    /// Return the GL Context.
    const SDL_GLContext& GetGLContext() { return context_; }

private:
    /// SDL OpenGL context.
    SDL_GLContext context_{};
    /// iOS/tvOS system framebuffer handle.
    unsigned systemFBO_{};
    /// Active texture unit.
    unsigned activeTexture_{};
    /// Enabled vertex attributes bitmask.
    unsigned enabledVertexAttributes_{};
    /// Vertex attributes bitmask used by the current shader program.
    unsigned usedVertexAttributes_{};
    /// Vertex attribute instancing bitmask for keeping track of divisors.
    unsigned instancingVertexAttributes_{};
    /// Current mapping of vertex attribute locations by semantic. The map is owned by the shader program, so care must be taken to switch a null shader program when it's destroyed.
    const HashMap<Pair<unsigned char, unsigned char>, unsigned>* vertexAttributes_{};
    /// Currently bound frame buffer object.
    unsigned boundFBO_{};
    /// Currently bound vertex buffer object.
    unsigned boundVBO_{};
    /// Currently bound uniform buffer object.
    unsigned boundUBO_{};
    /// Read frame buffer for multisampled texture resolves.
    unsigned resolveSrcFBO_{};
    /// Write frame buffer for multisampled texture resolves.
    unsigned resolveDestFBO_{};
    /// Current pixel format.
    int pixelFormat_{};
    /// Map for FBO's per resolution and format.
    HashMap<unsigned long long, FrameBufferObject> frameBuffers_;
    /// OpenGL texture types in use.
    unsigned textureTypes_[MAX_TEXTURE_UNITS]{};
    /// Constant buffer search map.
    ConstantBufferMap allConstantBuffers_;
    /// Currently bound constant buffers.
    ConstantBuffer* constantBuffers_[MAX_SHADER_PARAMETER_GROUPS * 2]{};
    /// Dirty constant buffers.
    PODVector<ConstantBuffer*> dirtyConstantBuffers_;
    /// Last used instance data offset.
    unsigned lastInstanceOffset_{};
    /// Map for additional depth textures, to emulate Direct3D9 ability to mix render texture and backbuffer rendering.
    HashMap<unsigned, SharedPtr<Texture2D> > depthTextures_;
    /// Shader program in use.
    ShaderProgram_OGL* shaderProgram_{};
    /// Linked shader programs.
    ShaderProgramMap_OGL shaderPrograms_;
    /// Need FBO commit flag.
    bool fboDirty_{};
    /// Need vertex attribute pointer update flag.
    bool vertexBuffersDirty_{};
    /// sRGB write mode flag.
    bool sRGBWrite_{};
};

}
