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

#include "../../Precompiled.h"

#include "../../Core/Context.h"
#include "../../Core/Mutex.h"
#include "../../Core/ProcessUtils.h"
#include "../../Core/Profiler.h"
#include "../../Graphics/AnimatedModel.h"
#include "../../Graphics/Animation.h"
#include "../../Graphics/AnimationController.h"
#include "../../Graphics/BillboardSet.h"
#include "../../Graphics/Camera.h"
#include "../../Graphics/ConstantBuffer.h"
#include "../../Graphics/CustomGeometry.h"
#include "../../Graphics/DebugRenderer.h"
#include "../../Graphics/DecalSet.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsEvents.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/IndexBuffer.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/Octree.h"
#include "../../Graphics/ParticleEffect.h"
#include "../../Graphics/ParticleEmitter.h"
#include "../../Graphics/RenderSurface.h"
#include "../../Graphics/Shader.h"
#include "../../Graphics/ShaderPrecache.h"
#include "../../Graphics/ShaderProgram.h"
#include "../../Graphics/ShaderVariation.h"
#include "../../Graphics/Skybox.h"
#include "../../Graphics/StaticModelGroup.h"
#include "../../Graphics/Technique.h"
#include "../../Graphics/Terrain.h"
#include "../../Graphics/TerrainPatch.h"
#include "../../Graphics/Texture2D.h"
#include "../../Graphics/Texture2DArray.h"
#include "../../Graphics/Texture3D.h"
#include "../../Graphics/TextureCube.h"
#include "../../Graphics/VertexBuffer.h"
#include "../../Graphics/Zone.h"
#include "../../IO/File.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"

#include "../../DebugNew.h"

#ifdef GL_ES_VERSION_2_0
#define GL_DEPTH_COMPONENT24 GL_DEPTH_COMPONENT24_OES
#define glClearDepth glClearDepthf
#endif

#ifdef __EMSCRIPTEN__
// Emscripten provides even all GL extension functions via static linking. However there is
// no GLES2-specific extension header at the moment to include instanced rendering declarations,
// so declare them manually from GLES3 gl2ext.h. Emscripten will provide these when linking final output.
extern "C"
{
    GL_APICALL void GL_APIENTRY glDrawArraysInstancedANGLE (GLenum mode, GLint first, GLsizei count, GLsizei primcount);
    GL_APICALL void GL_APIENTRY glDrawElementsInstancedANGLE (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount);
    GL_APICALL void GL_APIENTRY glVertexAttribDivisorANGLE (GLuint index, GLuint divisor);
}
#endif

#ifdef _WIN32
// Prefer the high-performance GPU on switchable GPU systems
#include <windows.h>
extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 1;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

namespace Urho3D
{

static const unsigned glCmpFunc[] =
{
    GL_ALWAYS,
    GL_EQUAL,
    GL_NOTEQUAL,
    GL_LESS,
    GL_LEQUAL,
    GL_GREATER,
    GL_GEQUAL
};

static const unsigned glSrcBlend[] =
{
    GL_ONE,
    GL_ONE,
    GL_DST_COLOR,
    GL_SRC_ALPHA,
    GL_SRC_ALPHA,
    GL_ONE,
    GL_ONE_MINUS_DST_ALPHA,
    GL_ONE,
    GL_SRC_ALPHA
};

static const unsigned glDestBlend[] =
{
    GL_ZERO,
    GL_ONE,
    GL_ZERO,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_ONE,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA,
    GL_ONE,
    GL_ONE
};

static const unsigned glBlendOp[] =
{
    GL_FUNC_ADD,
    GL_FUNC_ADD,
    GL_FUNC_ADD,
    GL_FUNC_ADD,
    GL_FUNC_ADD,
    GL_FUNC_ADD,
    GL_FUNC_ADD,
    GL_FUNC_REVERSE_SUBTRACT,
    GL_FUNC_REVERSE_SUBTRACT
};

#ifndef GL_ES_VERSION_2_0
static const unsigned glFillMode[] =
{
    GL_FILL,
    GL_LINE,
    GL_POINT
};

static const unsigned glStencilOps[] =
{
    GL_KEEP,
    GL_ZERO,
    GL_REPLACE,
    GL_INCR_WRAP,
    GL_DECR_WRAP
};
#endif

static const unsigned glElementTypes[] =
{
    GL_INT,
    GL_FLOAT,
    GL_FLOAT,
    GL_FLOAT,
    GL_FLOAT,
    GL_UNSIGNED_BYTE,
    GL_UNSIGNED_BYTE
};

static const unsigned glElementComponents[] =
{
    1,
    1,
    2,
    3,
    4,
    4,
    4
};

#ifdef GL_ES_VERSION_2_0
static unsigned glesDepthStencilFormat = GL_DEPTH_COMPONENT16;
static unsigned glesReadableDepthFormat = GL_DEPTH_COMPONENT;
#endif

static String extensions;

bool CheckExtension(const String& name)
{
    if (extensions.Empty())
        extensions = (const char*)glGetString(GL_EXTENSIONS);
    return extensions.Contains(name);
}

static void GetGLPrimitiveType(unsigned elementCount, PrimitiveType type, unsigned& primitiveCount, GLenum& glPrimitiveType)
{
    switch (type)
    {
    case TRIANGLE_LIST:
        primitiveCount = elementCount / 3;
        glPrimitiveType = GL_TRIANGLES;
        break;

    case LINE_LIST:
        primitiveCount = elementCount / 2;
        glPrimitiveType = GL_LINES;
        break;

    case POINT_LIST:
        primitiveCount = elementCount;
        glPrimitiveType = GL_POINTS;
        break;

    case TRIANGLE_STRIP:
        primitiveCount = elementCount - 2;
        glPrimitiveType = GL_TRIANGLE_STRIP;
        break;

    case LINE_STRIP:
        primitiveCount = elementCount - 1;
        glPrimitiveType = GL_LINE_STRIP;
        break;

    case TRIANGLE_FAN:
        primitiveCount = elementCount - 2;
        glPrimitiveType = GL_TRIANGLE_FAN;
        break;
    }
}

const Vector2 Graphics::pixelUVOffset(0.0f, 0.0f);
bool Graphics::gl3Support = false;

Graphics::Graphics(Context* context_) :
    Object(context_),
    impl_(new GraphicsImpl()),
    windowIcon_(0),
    externalWindow_(0),
    width_(0),
    height_(0),
    position_(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED),
    multiSample_(1),
    fullscreen_(false),
    borderless_(false),
    resizable_(false),
    highDPI_(false),
    vsync_(false),
    tripleBuffer_(false),
    sRGB_(false),
    forceGL2_(false),
    instancingSupport_(false),
    lightPrepassSupport_(false),
    deferredSupport_(false),
    anisotropySupport_(false),
    dxtTextureSupport_(false),
    etcTextureSupport_(false),
    pvrtcTextureSupport_(false),
    sRGBSupport_(false),
    sRGBWriteSupport_(false),
    numPrimitives_(0),
    numBatches_(0),
    maxScratchBufferRequest_(0),
    dummyColorFormat_(0),
    shadowMapFormat_(GL_DEPTH_COMPONENT16),
    hiresShadowMapFormat_(GL_DEPTH_COMPONENT24),
    defaultTextureFilterMode_(FILTER_TRILINEAR),
    shaderPath_("Shaders/GLSL/"),
    shaderExtension_(".glsl"),
    orientations_("LandscapeLeft LandscapeRight"),
#ifndef GL_ES_VERSION_2_0
    apiName_("GL2")
#else
    apiName_("GLES2")
#endif
{
    SetTextureUnitMappings();
    ResetCachedState();

    // Initialize SDL now. Graphics should be the first SDL-using subsystem to be created
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_NOPARACHUTE);

    // Register Graphics library object factories
    RegisterGraphicsLibrary(context_);
}

Graphics::~Graphics()
{
    Close();

    delete impl_;
    impl_ = 0;

    // Shut down SDL now. Graphics should be the last SDL-using subsystem to be destroyed
    SDL_Quit();
}

void Graphics::SetExternalWindow(void* window)
{
    if (!impl_->window_)
        externalWindow_ = window;
    else
        URHO3D_LOGERROR("Window already opened, can not set external window");
}

void Graphics::SetWindowTitle(const String& windowTitle)
{
    windowTitle_ = windowTitle;
    if (impl_->window_)
        SDL_SetWindowTitle(impl_->window_, windowTitle_.CString());
}

void Graphics::SetWindowIcon(Image* windowIcon)
{
    windowIcon_ = windowIcon;
    if (impl_->window_)
        CreateWindowIcon();
}

void Graphics::SetWindowPosition(const IntVector2& position)
{
    if (impl_->window_)
        SDL_SetWindowPosition(impl_->window_, position.x_, position.y_);
    else
        position_ = position; // Sets as initial position for future window creation
}

void Graphics::SetWindowPosition(int x, int y)
{
    SetWindowPosition(IntVector2(x, y));
}

bool Graphics::SetMode(int width, int height, bool fullscreen, bool borderless, bool resizable, bool highDPI, bool vsync,
    bool tripleBuffer, int multiSample)
{
    URHO3D_PROFILE(SetScreenMode);

    bool maximize = false;

#if defined(IOS) || defined(TVOS)
    // iOS and tvOS app always take the fullscreen (and with status bar hidden)
    fullscreen = true;
#endif

    // Fullscreen or Borderless can not be resizable
    if (fullscreen || borderless)
        resizable = false;

    // Borderless cannot be fullscreen, they are mutually exclusive
    if (borderless)
        fullscreen = false;

    multiSample = Clamp(multiSample, 1, 16);

    if (IsInitialized() && width == width_ && height == height_ && fullscreen == fullscreen_ && borderless == borderless_ &&
        resizable == resizable_ && vsync == vsync_ && tripleBuffer == tripleBuffer_ && multiSample == multiSample_)
        return true;

    // If only vsync changes, do not destroy/recreate the context
    if (IsInitialized() && width == width_ && height == height_ && fullscreen == fullscreen_ && borderless == borderless_ &&
        resizable == resizable_ && tripleBuffer == tripleBuffer_ && multiSample == multiSample_ && vsync != vsync_)
    {
        SDL_GL_SetSwapInterval(vsync ? 1 : 0);
        vsync_ = vsync;
        return true;
    }

    // If zero dimensions in windowed mode, set windowed mode to maximize and set a predefined default restored window size.
    // If zero in fullscreen, use desktop mode
    if (!width || !height)
    {
        if (fullscreen || borderless)
        {
            SDL_DisplayMode mode;
            SDL_GetDesktopDisplayMode(0, &mode);
            width = mode.w;
            height = mode.h;
        }
        else
        {
            maximize = resizable;
            width = 1024;
            height = 768;
        }
    }

    // Check fullscreen mode validity (desktop only). Use a closest match if not found
#ifdef DESKTOP_GRAPHICS
    if (fullscreen)
    {
        PODVector<IntVector2> resolutions = GetResolutions();
        if (resolutions.Size())
        {
            unsigned best = 0;
            unsigned bestError = M_MAX_UNSIGNED;

            for (unsigned i = 0; i < resolutions.Size(); ++i)
            {
                unsigned error = Abs(resolutions[i].x_ - width) + Abs(resolutions[i].y_ - height);
                if (error < bestError)
                {
                    best = i;
                    bestError = error;
                }
            }

            width = resolutions[best].x_;
            height = resolutions[best].y_;
        }
    }
#endif

    // With an external window, only the size can change after initial setup, so do not recreate context
    if (!externalWindow_ || !impl_->context_)
    {
        // Close the existing window and OpenGL context, mark GPU objects as lost
        Release(false, true);

#ifdef IOS
        // On iOS window needs to be resizable to handle orientation changes properly
        resizable = true;
#endif

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

#ifndef GL_ES_VERSION_2_0
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

        if (externalWindow_)
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        else
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);

        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        if (!forceGL2_)
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        }
        else
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 0);
        }
#else
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

        if (multiSample > 1)
        {
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multiSample);
        }
        else
        {
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
        }

        int x = fullscreen ? 0 : position_.x_;
        int y = fullscreen ? 0 : position_.y_;

        unsigned flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
        if (fullscreen)
            flags |= SDL_WINDOW_FULLSCREEN;
        if (borderless)
            flags |= SDL_WINDOW_BORDERLESS;
        if (resizable)
            flags |= SDL_WINDOW_RESIZABLE;
        if (highDPI)
            flags |= SDL_WINDOW_ALLOW_HIGHDPI;

        SDL_SetHint(SDL_HINT_ORIENTATIONS, orientations_.CString());

        for (;;)
        {
            if (!externalWindow_)
                impl_->window_ = SDL_CreateWindow(windowTitle_.CString(), x, y, width, height, flags);
            else
            {
#ifndef __EMSCRIPTEN__
                if (!impl_->window_)
                    impl_->window_ = SDL_CreateWindowFrom(externalWindow_, SDL_WINDOW_OPENGL);
                fullscreen = false;
#endif
            }

            if (impl_->window_)
                break;
            else
            {
                if (multiSample > 1)
                {
                    // If failed with multisampling, retry first without
                    multiSample = 1;
                    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
                    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
                }
                else
                {
                    URHO3D_LOGERRORF("Could not create window, root cause: '%s'", SDL_GetError());
                    return false;
                }
            }
        }

        CreateWindowIcon();

        if (maximize)
        {
            Maximize();
            SDL_GL_GetDrawableSize(impl_->window_, &width, &height);
        }

        // Create/restore context and GPU objects and set initial renderstate
        Restore();

        // Specific error message is already logged by Restore() when context creation or OpenGL extensions check fails
        if (!impl_->context_)
            return false;
    }

    // Set vsync
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);

    // Store the system FBO on IOS now
#ifdef IOS
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&impl_->systemFBO_);
#endif

    fullscreen_ = fullscreen;
    borderless_ = borderless;
    resizable_ = resizable;
    highDPI_ = highDPI;
    vsync_ = vsync;
    tripleBuffer_ = tripleBuffer;
    multiSample_ = multiSample;

    SDL_GL_GetDrawableSize(impl_->window_, &width_, &height_);
    if (!fullscreen)
        SDL_GetWindowPosition(impl_->window_, &position_.x_, &position_.y_);

    // Reset rendertargets and viewport for the new screen mode
    ResetRenderTargets();

    // Clear the initial window contents to black
    Clear(CLEAR_COLOR);
    SDL_GL_SwapWindow(impl_->window_);

    CheckFeatureSupport();

#ifdef URHO3D_LOGGING
    String msg;
    msg.AppendWithFormat("Set screen mode %dx%d %s", width_, height_, (fullscreen_ ? "fullscreen" : "windowed"));
    if (borderless_)
        msg.Append(" borderless");
    if (resizable_)
        msg.Append(" resizable");
    if (multiSample > 1)
        msg.AppendWithFormat(" multisample %d", multiSample);
    URHO3D_LOGINFO(msg);
#endif

    using namespace ScreenMode;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_WIDTH] = width_;
    eventData[P_HEIGHT] = height_;
    eventData[P_FULLSCREEN] = fullscreen_;
    eventData[P_BORDERLESS] = borderless_;
    eventData[P_RESIZABLE] = resizable_;
    eventData[P_HIGHDPI] = highDPI_;
    SendEvent(E_SCREENMODE, eventData);

    return true;
}

bool Graphics::SetMode(int width, int height)
{
    return SetMode(width, height, fullscreen_, borderless_, resizable_, highDPI_, vsync_, tripleBuffer_, multiSample_);
}

void Graphics::SetSRGB(bool enable)
{
    enable &= sRGBWriteSupport_;

    if (enable != sRGB_)
    {
        sRGB_ = enable;
        impl_->fboDirty_ = true;
    }
}

void Graphics::SetFlushGPU(bool enable)
{
}

void Graphics::SetForceGL2(bool enable)
{
    if (IsInitialized())
    {
        URHO3D_LOGERROR("OpenGL 2 can only be forced before setting the initial screen mode");
        return;
    }

    forceGL2_ = enable;
}

void Graphics::SetOrientations(const String& orientations)
{
    orientations_ = orientations.Trimmed();
    SDL_SetHint(SDL_HINT_ORIENTATIONS, orientations_.CString());
}

bool Graphics::ToggleFullscreen()
{
    return SetMode(width_, height_, !fullscreen_, borderless_, resizable_, highDPI_, vsync_, tripleBuffer_, multiSample_);
}

void Graphics::Close()
{
    if (!IsInitialized())
        return;

    // Actually close the window
    Release(true, true);
}

bool Graphics::TakeScreenShot(Image& destImage)
{
    URHO3D_PROFILE(TakeScreenShot);

    if (!IsInitialized())
        return false;

    if (IsDeviceLost())
    {
        URHO3D_LOGERROR("Can not take screenshot while device is lost");
        return false;
    }

    ResetRenderTargets();

    destImage.SetSize(width_, height_, 3);
    glReadPixels(0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, destImage.GetData());
    // On OpenGL we need to flip the image vertically after reading
    destImage.FlipVertical();

    return true;
}

bool Graphics::BeginFrame()
{
    if (!IsInitialized() || IsDeviceLost())
        return false;

    // If using an external window, check it for size changes, and reset screen mode if necessary
    if (externalWindow_)
    {
        int width, height;

        SDL_GL_GetDrawableSize(impl_->window_, &width, &height);
        if (width != width_ || height != height_)
            SetMode(width, height);
    }

    // Re-enable depth test and depth func in case a third party program has modified it
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(glCmpFunc[depthTestMode_]);

    // Set default rendertarget and depth buffer
    ResetRenderTargets();

    // Cleanup textures from previous frame
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        SetTexture(i, 0);

    // Enable color and depth write
    SetColorWrite(true);
    SetDepthWrite(true);

    numPrimitives_ = 0;
    numBatches_ = 0;

    SendEvent(E_BEGINRENDERING);

    return true;
}

void Graphics::EndFrame()
{
    if (!IsInitialized())
        return;

    URHO3D_PROFILE(Present);

    SendEvent(E_ENDRENDERING);

    SDL_GL_SwapWindow(impl_->window_);

    // Clean up too large scratch buffers
    CleanupScratchBuffers();
}

void Graphics::Clear(unsigned flags, const Color& color, float depth, unsigned stencil)
{
    PrepareDraw();

#ifdef GL_ES_VERSION_2_0
    flags &= ~CLEAR_STENCIL;
#endif

    bool oldColorWrite = colorWrite_;
    bool oldDepthWrite = depthWrite_;

    if (flags & CLEAR_COLOR && !oldColorWrite)
        SetColorWrite(true);
    if (flags & CLEAR_DEPTH && !oldDepthWrite)
        SetDepthWrite(true);
    if (flags & CLEAR_STENCIL && stencilWriteMask_ != M_MAX_UNSIGNED)
        glStencilMask(M_MAX_UNSIGNED);

    unsigned glFlags = 0;
    if (flags & CLEAR_COLOR)
    {
        glFlags |= GL_COLOR_BUFFER_BIT;
        glClearColor(color.r_, color.g_, color.b_, color.a_);
    }
    if (flags & CLEAR_DEPTH)
    {
        glFlags |= GL_DEPTH_BUFFER_BIT;
        glClearDepth(depth);
    }
    if (flags & CLEAR_STENCIL)
    {
        glFlags |= GL_STENCIL_BUFFER_BIT;
        glClearStencil(stencil);
    }

    // If viewport is less than full screen, set a scissor to limit the clear
    /// \todo Any user-set scissor test will be lost
    IntVector2 viewSize = GetRenderTargetDimensions();
    if (viewport_.left_ != 0 || viewport_.top_ != 0 || viewport_.right_ != viewSize.x_ || viewport_.bottom_ != viewSize.y_)
        SetScissorTest(true, IntRect(0, 0, viewport_.Width(), viewport_.Height()));
    else
        SetScissorTest(false);

    glClear(glFlags);

    SetScissorTest(false);
    SetColorWrite(oldColorWrite);
    SetDepthWrite(oldDepthWrite);
    if (flags & CLEAR_STENCIL && stencilWriteMask_ != M_MAX_UNSIGNED)
        glStencilMask(stencilWriteMask_);
}

bool Graphics::ResolveToTexture(Texture2D* destination, const IntRect& viewport)
{
    if (!destination || !destination->GetRenderSurface())
        return false;

    URHO3D_PROFILE(ResolveToTexture);

    IntRect vpCopy = viewport;
    if (vpCopy.right_ <= vpCopy.left_)
        vpCopy.right_ = vpCopy.left_ + 1;
    if (vpCopy.bottom_ <= vpCopy.top_)
        vpCopy.bottom_ = vpCopy.top_ + 1;
    vpCopy.left_ = Clamp(vpCopy.left_, 0, width_);
    vpCopy.top_ = Clamp(vpCopy.top_, 0, height_);
    vpCopy.right_ = Clamp(vpCopy.right_, 0, width_);
    vpCopy.bottom_ = Clamp(vpCopy.bottom_, 0, height_);

    // Make sure the FBO is not in use
    ResetRenderTargets();

    // Use Direct3D convention with the vertical coordinates ie. 0 is top
    SetTextureForUpdate(destination);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, vpCopy.left_, height_ - vpCopy.bottom_, vpCopy.Width(), vpCopy.Height());
    SetTexture(0, 0);

    return true;
}

void Graphics::Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount)
{
    if (!vertexCount)
        return;

    PrepareDraw();

    unsigned primitiveCount;
    GLenum glPrimitiveType;

    GetGLPrimitiveType(vertexCount, type, primitiveCount, glPrimitiveType);
    glDrawArrays(glPrimitiveType, vertexStart, vertexCount);

    numPrimitives_ += primitiveCount;
    ++numBatches_;
}

void Graphics::Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount)
{
    if (!indexCount || !indexBuffer_ || !indexBuffer_->GetGPUObject())
        return;

    PrepareDraw();

    unsigned indexSize = indexBuffer_->GetIndexSize();
    unsigned primitiveCount;
    GLenum glPrimitiveType;

    GetGLPrimitiveType(indexCount, type, primitiveCount, glPrimitiveType);
    GLenum indexType = indexSize == sizeof(unsigned short) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
    glDrawElements(glPrimitiveType, indexCount, indexType, reinterpret_cast<const GLvoid*>(indexStart * indexSize));

    numPrimitives_ += primitiveCount;
    ++numBatches_;
}

void Graphics::Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned baseVertexIndex, unsigned minVertex, unsigned vertexCount)
{
#ifndef GL_ES_VERSION_2_0
    if (!gl3Support || !indexCount || !indexBuffer_ || !indexBuffer_->GetGPUObject())
        return;

    PrepareDraw();

    unsigned indexSize = indexBuffer_->GetIndexSize();
    unsigned primitiveCount;
    GLenum glPrimitiveType;

    GetGLPrimitiveType(indexCount, type, primitiveCount, glPrimitiveType);
    GLenum indexType = indexSize == sizeof(unsigned short) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
    glDrawElementsBaseVertex(glPrimitiveType, indexCount, indexType, reinterpret_cast<GLvoid*>(indexStart * indexSize), baseVertexIndex);

    numPrimitives_ += primitiveCount;
    ++numBatches_;
#endif
}

void Graphics::DrawInstanced(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount,
    unsigned instanceCount)
{
#if !defined(GL_ES_VERSION_2_0) || defined(__EMSCRIPTEN__)
    if (!indexCount || !indexBuffer_ || !indexBuffer_->GetGPUObject() || !instancingSupport_)
        return;

    PrepareDraw();

    unsigned indexSize = indexBuffer_->GetIndexSize();
    unsigned primitiveCount;
    GLenum glPrimitiveType;

    GetGLPrimitiveType(indexCount, type, primitiveCount, glPrimitiveType);
    GLenum indexType = indexSize == sizeof(unsigned short) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
#ifdef __EMSCRIPTEN__
    glDrawElementsInstancedANGLE(glPrimitiveType, indexCount, indexType, reinterpret_cast<const GLvoid*>(indexStart * indexSize),
        instanceCount);
#else
    if (gl3Support)
    {
        glDrawElementsInstanced(glPrimitiveType, indexCount, indexType, reinterpret_cast<const GLvoid*>(indexStart * indexSize),
            instanceCount);
    }
    else
    {
        glDrawElementsInstancedARB(glPrimitiveType, indexCount, indexType, reinterpret_cast<const GLvoid*>(indexStart * indexSize),
            instanceCount);
    }
#endif

    numPrimitives_ += instanceCount * primitiveCount;
    ++numBatches_;
#endif
}

void Graphics::DrawInstanced(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned baseVertexIndex, unsigned minVertex,
        unsigned vertexCount, unsigned instanceCount)
{
#ifndef GL_ES_VERSION_2_0
    if (!gl3Support || !indexCount || !indexBuffer_ || !indexBuffer_->GetGPUObject() || !instancingSupport_)
        return;

    PrepareDraw();

    unsigned indexSize = indexBuffer_->GetIndexSize();
    unsigned primitiveCount;
    GLenum glPrimitiveType;

    GetGLPrimitiveType(indexCount, type, primitiveCount, glPrimitiveType);
    GLenum indexType = indexSize == sizeof(unsigned short) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;

    glDrawElementsInstancedBaseVertex(glPrimitiveType, indexCount, indexType, reinterpret_cast<const GLvoid*>(indexStart * indexSize),
        instanceCount, baseVertexIndex);

    numPrimitives_ += instanceCount * primitiveCount;
    ++numBatches_;
#endif
}

void Graphics::SetVertexBuffer(VertexBuffer* buffer)
{
    // Note: this is not multi-instance safe
    static PODVector<VertexBuffer*> vertexBuffers(1);
    vertexBuffers[0] = buffer;
    SetVertexBuffers(vertexBuffers);
}

bool Graphics::SetVertexBuffers(const PODVector<VertexBuffer*>& buffers, unsigned instanceOffset)
{
    if (buffers.Size() > MAX_VERTEX_STREAMS)
    {
        URHO3D_LOGERROR("Too many vertex buffers");
        return false;
    }

    if (instanceOffset != lastInstanceOffset_)
    {
        lastInstanceOffset_ = instanceOffset;
        impl_->vertexBuffersDirty_ = true;
    }

    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        VertexBuffer* buffer = 0;
        if (i < buffers.Size())
            buffer = buffers[i];
        if (buffer != vertexBuffers_[i])
        {
            vertexBuffers_[i] = buffer;
            impl_->vertexBuffersDirty_ = true;
        }
    }

    return true;
}

bool Graphics::SetVertexBuffers(const Vector<SharedPtr<VertexBuffer> >& buffers, unsigned instanceOffset)
{
    return SetVertexBuffers(reinterpret_cast<const PODVector<VertexBuffer*>&>(buffers), instanceOffset);
}

void Graphics::SetIndexBuffer(IndexBuffer* buffer)
{
    if (indexBuffer_ == buffer)
        return;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer ? buffer->GetGPUObject() : 0);
    indexBuffer_ = buffer;
}

void Graphics::SetShaders(ShaderVariation* vs, ShaderVariation* ps)
{
    if (vs == vertexShader_ && ps == pixelShader_)
        return;

    // Compile the shaders now if not yet compiled. If already attempted, do not retry
    if (vs && !vs->GetGPUObject())
    {
        if (vs->GetCompilerOutput().Empty())
        {
            URHO3D_PROFILE(CompileVertexShader);

            bool success = vs->Create();
            if (success)
                URHO3D_LOGDEBUG("Compiled vertex shader " + vs->GetFullName());
            else
            {
                URHO3D_LOGERROR("Failed to compile vertex shader " + vs->GetFullName() + ":\n" + vs->GetCompilerOutput());
                vs = 0;
            }
        }
        else
            vs = 0;
    }

    if (ps && !ps->GetGPUObject())
    {
        if (ps->GetCompilerOutput().Empty())
        {
            URHO3D_PROFILE(CompilePixelShader);

            bool success = ps->Create();
            if (success)
                URHO3D_LOGDEBUG("Compiled pixel shader " + ps->GetFullName());
            else
            {
                URHO3D_LOGERROR("Failed to compile pixel shader " + ps->GetFullName() + ":\n" + ps->GetCompilerOutput());
                ps = 0;
            }
        }
        else
            ps = 0;
    }

    if (!vs || !ps)
    {
        glUseProgram(0);
        vertexShader_ = 0;
        pixelShader_ = 0;
        shaderProgram_ = 0;
    }
    else
    {
        vertexShader_ = vs;
        pixelShader_ = ps;

        Pair<ShaderVariation*, ShaderVariation*> combination(vs, ps);
        ShaderProgramMap::Iterator i = shaderPrograms_.Find(combination);

        if (i != shaderPrograms_.End())
        {
            // Use the existing linked program
            if (i->second_->GetGPUObject())
            {
                glUseProgram(i->second_->GetGPUObject());
                shaderProgram_ = i->second_;
            }
            else
            {
                glUseProgram(0);
                shaderProgram_ = 0;
            }
        }
        else
        {
            // Link a new combination
            URHO3D_PROFILE(LinkShaders);

            SharedPtr<ShaderProgram> newProgram(new ShaderProgram(this, vs, ps));
            if (newProgram->Link())
            {
                URHO3D_LOGDEBUG("Linked vertex shader " + vs->GetFullName() + " and pixel shader " + ps->GetFullName());
                // Note: Link() calls glUseProgram() to set the texture sampler uniforms,
                // so it is not necessary to call it again
                shaderProgram_ = newProgram;
            }
            else
            {
                URHO3D_LOGERROR("Failed to link vertex shader " + vs->GetFullName() + " and pixel shader " + ps->GetFullName() + ":\n" +
                         newProgram->GetLinkerOutput());
                glUseProgram(0);
                shaderProgram_ = 0;
            }

            shaderPrograms_[combination] = newProgram;
        }
    }

    // Update the clip plane uniform on GL3, and set constant buffers
#ifndef GL_ES_VERSION_2_0
    if (gl3Support && shaderProgram_)
    {
        const SharedPtr<ConstantBuffer>* constantBuffers = shaderProgram_->GetConstantBuffers();
        for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS * 2; ++i)
        {
            ConstantBuffer* buffer = constantBuffers[i].Get();
            if (buffer != currentConstantBuffers_[i])
            {
                unsigned object = buffer ? buffer->GetGPUObject() : 0;
                glBindBufferBase(GL_UNIFORM_BUFFER, i, object);
                // Calling glBindBufferBase also affects the generic buffer binding point
                impl_->boundUBO_ = object;
                currentConstantBuffers_[i] = buffer;
                ShaderProgram::ClearGlobalParameterSource((ShaderParameterGroup)(i % MAX_SHADER_PARAMETER_GROUPS));
            }
        }

        SetShaderParameter(VSP_CLIPPLANE, useClipPlane_ ? clipPlane_ : Vector4(0.0f, 0.0f, 0.0f, 1.0f));
    }
#endif

    // Store shader combination if shader dumping in progress
    if (shaderPrecache_)
        shaderPrecache_->StoreShaders(vertexShader_, pixelShader_);

    if (shaderProgram_)
    {
        impl_->usedVertexAttributes_ = shaderProgram_->GetUsedVertexAttributes();
        impl_->vertexAttributes_ = &shaderProgram_->GetVertexAttributes();
    }
    else
    {
        impl_->usedVertexAttributes_ = 0;
        impl_->vertexAttributes_ = 0;
    }

    impl_->vertexBuffersDirty_ = true;
}

void Graphics::SetShaderParameter(StringHash param, const float* data, unsigned count)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter((unsigned)info->location_, (unsigned)(count * sizeof(float)), data);
                return;
            }

            switch (info->type_)
            {
            case GL_FLOAT:
                glUniform1fv(info->location_, count, data);
                break;

            case GL_FLOAT_VEC2:
                glUniform2fv(info->location_, count / 2, data);
                break;

            case GL_FLOAT_VEC3:
                glUniform3fv(info->location_, count / 3, data);
                break;

            case GL_FLOAT_VEC4:
                glUniform4fv(info->location_, count / 4, data);
                break;

            case GL_FLOAT_MAT3:
                glUniformMatrix3fv(info->location_, count / 9, GL_FALSE, data);
                break;

            case GL_FLOAT_MAT4:
                glUniformMatrix4fv(info->location_, count / 16, GL_FALSE, data);
                break;

            default: break;
            }
        }
    }
}

void Graphics::SetShaderParameter(StringHash param, float value)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter((unsigned)info->location_, sizeof(float), &value);
                return;
            }

            glUniform1fv(info->location_, 1, &value);
        }
    }
}

void Graphics::SetShaderParameter(StringHash param, const Color& color)
{
    SetShaderParameter(param, color.Data(), 4);
}

void Graphics::SetShaderParameter(StringHash param, const Vector2& vector)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter((unsigned)info->location_, sizeof(Vector2), &vector);
                return;
            }

            // Check the uniform type to avoid mismatch
            switch (info->type_)
            {
            case GL_FLOAT:
                glUniform1fv(info->location_, 1, vector.Data());
                break;

            case GL_FLOAT_VEC2:
                glUniform2fv(info->location_, 1, vector.Data());
                break;

            default: break;
            }
        }
    }
}

void Graphics::SetShaderParameter(StringHash param, const Matrix3& matrix)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    dirtyConstantBuffers_.Push(buffer);
                buffer->SetVector3ArrayParameter((unsigned)info->location_, 3, &matrix);
                return;
            }

            glUniformMatrix3fv(info->location_, 1, GL_FALSE, matrix.Data());
        }
    }
}

void Graphics::SetShaderParameter(StringHash param, const Vector3& vector)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter((unsigned)info->location_, sizeof(Vector3), &vector);
                return;
            }

            // Check the uniform type to avoid mismatch
            switch (info->type_)
            {
            case GL_FLOAT:
                glUniform1fv(info->location_, 1, vector.Data());
                break;

            case GL_FLOAT_VEC2:
                glUniform2fv(info->location_, 1, vector.Data());
                break;

            case GL_FLOAT_VEC3:
                glUniform3fv(info->location_, 1, vector.Data());
                break;

            default: break;
            }
        }
    }
}

void Graphics::SetShaderParameter(StringHash param, const Matrix4& matrix)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter((unsigned)info->location_, sizeof(Matrix4), &matrix);
                return;
            }

            glUniformMatrix4fv(info->location_, 1, GL_FALSE, matrix.Data());
        }
    }
}

void Graphics::SetShaderParameter(StringHash param, const Vector4& vector)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter((unsigned)info->location_, sizeof(Vector4), &vector);
                return;
            }

            // Check the uniform type to avoid mismatch
            switch (info->type_)
            {
            case GL_FLOAT:
                glUniform1fv(info->location_, 1, vector.Data());
                break;

            case GL_FLOAT_VEC2:
                glUniform2fv(info->location_, 1, vector.Data());
                break;

            case GL_FLOAT_VEC3:
                glUniform3fv(info->location_, 1, vector.Data());
                break;

            case GL_FLOAT_VEC4:
                glUniform4fv(info->location_, 1, vector.Data());
                break;

            default: break;
            }
        }
    }
}

void Graphics::SetShaderParameter(StringHash param, const Matrix3x4& matrix)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
        if (info)
        {
            // Expand to a full Matrix4
            static Matrix4 fullMatrix;
            fullMatrix.m00_ = matrix.m00_;
            fullMatrix.m01_ = matrix.m01_;
            fullMatrix.m02_ = matrix.m02_;
            fullMatrix.m03_ = matrix.m03_;
            fullMatrix.m10_ = matrix.m10_;
            fullMatrix.m11_ = matrix.m11_;
            fullMatrix.m12_ = matrix.m12_;
            fullMatrix.m13_ = matrix.m13_;
            fullMatrix.m20_ = matrix.m20_;
            fullMatrix.m21_ = matrix.m21_;
            fullMatrix.m22_ = matrix.m22_;
            fullMatrix.m23_ = matrix.m23_;

            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter((unsigned)info->location_, sizeof(Matrix4), &fullMatrix);
                return;
            }

            glUniformMatrix4fv(info->location_, 1, GL_FALSE, fullMatrix.Data());
        }
    }
}

void Graphics::SetShaderParameter(StringHash param, const Variant& value)
{
    switch (value.GetType())
    {
    case VAR_BOOL:
        SetShaderParameter(param, value.GetBool());
        break;

    case VAR_FLOAT:
        SetShaderParameter(param, value.GetFloat());
        break;

    case VAR_VECTOR2:
        SetShaderParameter(param, value.GetVector2());
        break;

    case VAR_VECTOR3:
        SetShaderParameter(param, value.GetVector3());
        break;

    case VAR_VECTOR4:
        SetShaderParameter(param, value.GetVector4());
        break;

    case VAR_COLOR:
        SetShaderParameter(param, value.GetColor());
        break;

    case VAR_MATRIX3:
        SetShaderParameter(param, value.GetMatrix3());
        break;

    case VAR_MATRIX3X4:
        SetShaderParameter(param, value.GetMatrix3x4());
        break;

    case VAR_MATRIX4:
        SetShaderParameter(param, value.GetMatrix4());
        break;

    case VAR_BUFFER:
        {
            const PODVector<unsigned char>& buffer = value.GetBuffer();
            if (buffer.Size() >= sizeof(float))
                SetShaderParameter(param, reinterpret_cast<const float*>(&buffer[0]), buffer.Size() / sizeof(float));
        }
        break;

    default:
        // Unsupported parameter type, do nothing
        break;
    }
}

bool Graphics::NeedParameterUpdate(ShaderParameterGroup group, const void* source)
{
    return shaderProgram_ ? shaderProgram_->NeedParameterUpdate(group, source) : false;
}

bool Graphics::HasShaderParameter(StringHash param)
{
    return shaderProgram_ && shaderProgram_->HasParameter(param);
}

bool Graphics::HasTextureUnit(TextureUnit unit)
{
    return shaderProgram_ && shaderProgram_->HasTextureUnit(unit);
}

void Graphics::ClearParameterSource(ShaderParameterGroup group)
{
    if (shaderProgram_)
        shaderProgram_->ClearParameterSource(group);
}

void Graphics::ClearParameterSources()
{
    ShaderProgram::ClearParameterSources();
}

void Graphics::ClearTransformSources()
{
    if (shaderProgram_)
    {
        shaderProgram_->ClearParameterSource(SP_CAMERA);
        shaderProgram_->ClearParameterSource(SP_OBJECT);
    }
}

void Graphics::SetTexture(unsigned index, Texture* texture)
{
    if (index >= MAX_TEXTURE_UNITS)
        return;

    // Check if texture is currently bound as a rendertarget. In that case, use its backup texture, or blank if not defined
    if (texture)
    {
        if (renderTargets_[0] && renderTargets_[0]->GetParentTexture() == texture)
            texture = texture->GetBackupTexture();
    }

    if (textures_[index] != texture)
    {
        if (impl_->activeTexture_ != index)
        {
            glActiveTexture(GL_TEXTURE0 + index);
            impl_->activeTexture_ = index;
        }

        if (texture)
        {
            unsigned glType = texture->GetTarget();
            // Unbind old texture type if necessary
            if (textureTypes_[index] && textureTypes_[index] != glType)
                glBindTexture(textureTypes_[index], 0);
            glBindTexture(glType, texture->GetGPUObject());
            textureTypes_[index] = glType;

            if (texture->GetParametersDirty())
                texture->UpdateParameters();
        }
        else if (textureTypes_[index])
        {
            glBindTexture(textureTypes_[index], 0);
            textureTypes_[index] = 0;
        }

        textures_[index] = texture;
    }
    else
    {
        if (texture && texture->GetParametersDirty())
        {
            if (impl_->activeTexture_ != index)
            {
                glActiveTexture(GL_TEXTURE0 + index);
                impl_->activeTexture_ = index;
            }

            glBindTexture(texture->GetTarget(), texture->GetGPUObject());
            texture->UpdateParameters();
        }
    }
}

void Graphics::SetTextureForUpdate(Texture* texture)
{
    if (impl_->activeTexture_ != 0)
    {
        glActiveTexture(GL_TEXTURE0);
        impl_->activeTexture_ = 0;
    }

    unsigned glType = texture->GetTarget();
    // Unbind old texture type if necessary
    if (textureTypes_[0] && textureTypes_[0] != glType)
        glBindTexture(textureTypes_[0], 0);
    glBindTexture(glType, texture->GetGPUObject());
    textureTypes_[0] = glType;
    textures_[0] = texture;
}

void Graphics::SetDefaultTextureFilterMode(TextureFilterMode mode)
{
    if (mode != defaultTextureFilterMode_)
    {
        defaultTextureFilterMode_ = mode;
        SetTextureParametersDirty();
    }
}

void Graphics::SetTextureAnisotropy(unsigned level)
{
    if (level != textureAnisotropy_)
    {
        textureAnisotropy_ = level;
        SetTextureParametersDirty();
    }
}

void Graphics::SetTextureParametersDirty()
{
    MutexLock lock(gpuObjectMutex_);

    for (PODVector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
    {
        Texture* texture = dynamic_cast<Texture*>(*i);
        if (texture)
            texture->SetParametersDirty();
    }
}

void Graphics::ResetRenderTargets()
{
    for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        SetRenderTarget(i, (RenderSurface*)0);
    SetDepthStencil((RenderSurface*)0);
    SetViewport(IntRect(0, 0, width_, height_));
}

void Graphics::ResetRenderTarget(unsigned index)
{
    SetRenderTarget(index, (RenderSurface*)0);
}

void Graphics::ResetDepthStencil()
{
    SetDepthStencil((RenderSurface*)0);
}

void Graphics::SetRenderTarget(unsigned index, RenderSurface* renderTarget)
{
    if (index >= MAX_RENDERTARGETS)
        return;

    if (renderTarget != renderTargets_[index])
    {
        renderTargets_[index] = renderTarget;

        // If the rendertarget is also bound as a texture, replace with backup texture or null
        if (renderTarget)
        {
            Texture* parentTexture = renderTarget->GetParentTexture();

            for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
            {
                if (textures_[i] == parentTexture)
                    SetTexture(i, textures_[i]->GetBackupTexture());
            }
        }

        impl_->fboDirty_ = true;
    }
}

void Graphics::SetRenderTarget(unsigned index, Texture2D* texture)
{
    RenderSurface* renderTarget = 0;
    if (texture)
        renderTarget = texture->GetRenderSurface();

    SetRenderTarget(index, renderTarget);
}

void Graphics::SetDepthStencil(RenderSurface* depthStencil)
{
    // If we are using a rendertarget texture, it is required in OpenGL to also have an own depth-stencil
    // Create a new depth-stencil texture as necessary to be able to provide similar behaviour as Direct3D9
    if (renderTargets_[0] && !depthStencil)
    {
        int width = renderTargets_[0]->GetWidth();
        int height = renderTargets_[0]->GetHeight();

        // Direct3D9 default depth-stencil can not be used when rendertarget is larger than the window.
        // Check size similarly
        if (width <= width_ && height <= height_)
        {
            int searchKey = (width << 16) | height;
            HashMap<int, SharedPtr<Texture2D> >::Iterator i = depthTextures_.Find(searchKey);
            if (i != depthTextures_.End())
                depthStencil = i->second_->GetRenderSurface();
            else
            {
                SharedPtr<Texture2D> newDepthTexture(new Texture2D(context_));
                newDepthTexture->SetSize(width, height, GetDepthStencilFormat(), TEXTURE_DEPTHSTENCIL);
                depthTextures_[searchKey] = newDepthTexture;
                depthStencil = newDepthTexture->GetRenderSurface();
            }
        }
    }

    if (depthStencil != depthStencil_)
    {
        depthStencil_ = depthStencil;
        impl_->fboDirty_ = true;
    }
}

void Graphics::SetDepthStencil(Texture2D* texture)
{
    RenderSurface* depthStencil = 0;
    if (texture)
        depthStencil = texture->GetRenderSurface();

    SetDepthStencil(depthStencil);
}

void Graphics::SetViewport(const IntRect& rect)
{
    PrepareDraw();

    IntVector2 rtSize = GetRenderTargetDimensions();

    IntRect rectCopy = rect;

    if (rectCopy.right_ <= rectCopy.left_)
        rectCopy.right_ = rectCopy.left_ + 1;
    if (rectCopy.bottom_ <= rectCopy.top_)
        rectCopy.bottom_ = rectCopy.top_ + 1;
    rectCopy.left_ = Clamp(rectCopy.left_, 0, rtSize.x_);
    rectCopy.top_ = Clamp(rectCopy.top_, 0, rtSize.y_);
    rectCopy.right_ = Clamp(rectCopy.right_, 0, rtSize.x_);
    rectCopy.bottom_ = Clamp(rectCopy.bottom_, 0, rtSize.y_);

    // Use Direct3D convention with the vertical coordinates ie. 0 is top
    glViewport(rectCopy.left_, rtSize.y_ - rectCopy.bottom_, rectCopy.Width(), rectCopy.Height());
    viewport_ = rectCopy;

    // Disable scissor test, needs to be re-enabled by the user
    SetScissorTest(false);
}

void Graphics::SetBlendMode(BlendMode mode)
{
    if (mode != blendMode_)
    {
        if (mode == BLEND_REPLACE)
            glDisable(GL_BLEND);
        else
        {
            glEnable(GL_BLEND);
            glBlendFunc(glSrcBlend[mode], glDestBlend[mode]);
            glBlendEquation(glBlendOp[mode]);
        }

        blendMode_ = mode;
    }
}

void Graphics::SetColorWrite(bool enable)
{
    if (enable != colorWrite_)
    {
        if (enable)
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        else
            glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

        colorWrite_ = enable;
    }
}

void Graphics::SetCullMode(CullMode mode)
{
    if (mode != cullMode_)
    {
        if (mode == CULL_NONE)
            glDisable(GL_CULL_FACE);
        else
        {
            // Use Direct3D convention, ie. clockwise vertices define a front face
            glEnable(GL_CULL_FACE);
            glCullFace(mode == CULL_CCW ? GL_FRONT : GL_BACK);
        }

        cullMode_ = mode;
    }
}

void Graphics::SetDepthBias(float constantBias, float slopeScaledBias)
{
    if (constantBias != constantDepthBias_ || slopeScaledBias != slopeScaledDepthBias_)
    {
#ifndef GL_ES_VERSION_2_0
        if (slopeScaledBias != 0.0f)
        {
            // OpenGL constant bias is unreliable and dependant on depth buffer bitdepth, apply in the projection matrix instead
            float adjustedSlopeScaledBias = slopeScaledBias + 1.0f;
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(adjustedSlopeScaledBias, 0.0f);
        }
        else
            glDisable(GL_POLYGON_OFFSET_FILL);
#endif

        constantDepthBias_ = constantBias;
        slopeScaledDepthBias_ = slopeScaledBias;
        // Force update of the projection matrix shader parameter
        ClearParameterSource(SP_CAMERA);
    }
}

void Graphics::SetDepthTest(CompareMode mode)
{
    if (mode != depthTestMode_)
    {
        glDepthFunc(glCmpFunc[mode]);
        depthTestMode_ = mode;
    }
}

void Graphics::SetDepthWrite(bool enable)
{
    if (enable != depthWrite_)
    {
        glDepthMask(enable ? GL_TRUE : GL_FALSE);
        depthWrite_ = enable;
    }
}

void Graphics::SetFillMode(FillMode mode)
{
#ifndef GL_ES_VERSION_2_0
    if (mode != fillMode_)
    {
        glPolygonMode(GL_FRONT_AND_BACK, glFillMode[mode]);
        fillMode_ = mode;
    }
#endif
}

void Graphics::SetScissorTest(bool enable, const Rect& rect, bool borderInclusive)
{
    // During some light rendering loops, a full rect is toggled on/off repeatedly.
    // Disable scissor in that case to reduce state changes
    if (rect.min_.x_ <= 0.0f && rect.min_.y_ <= 0.0f && rect.max_.x_ >= 1.0f && rect.max_.y_ >= 1.0f)
        enable = false;

    if (enable)
    {
        IntVector2 rtSize(GetRenderTargetDimensions());
        IntVector2 viewSize(viewport_.Size());
        IntVector2 viewPos(viewport_.left_, viewport_.top_);
        IntRect intRect;
        int expand = borderInclusive ? 1 : 0;

        intRect.left_ = Clamp((int)((rect.min_.x_ + 1.0f) * 0.5f * viewSize.x_) + viewPos.x_, 0, rtSize.x_ - 1);
        intRect.top_ = Clamp((int)((-rect.max_.y_ + 1.0f) * 0.5f * viewSize.y_) + viewPos.y_, 0, rtSize.y_ - 1);
        intRect.right_ = Clamp((int)((rect.max_.x_ + 1.0f) * 0.5f * viewSize.x_) + viewPos.x_ + expand, 0, rtSize.x_);
        intRect.bottom_ = Clamp((int)((-rect.min_.y_ + 1.0f) * 0.5f * viewSize.y_) + viewPos.y_ + expand, 0, rtSize.y_);

        if (intRect.right_ == intRect.left_)
            intRect.right_++;
        if (intRect.bottom_ == intRect.top_)
            intRect.bottom_++;

        if (intRect.right_ < intRect.left_ || intRect.bottom_ < intRect.top_)
            enable = false;

        if (enable && scissorRect_ != intRect)
        {
            // Use Direct3D convention with the vertical coordinates ie. 0 is top
            glScissor(intRect.left_, rtSize.y_ - intRect.bottom_, intRect.Width(), intRect.Height());
            scissorRect_ = intRect;
        }
    }
    else
        scissorRect_ = IntRect::ZERO;

    if (enable != scissorTest_)
    {
        if (enable)
            glEnable(GL_SCISSOR_TEST);
        else
            glDisable(GL_SCISSOR_TEST);
        scissorTest_ = enable;
    }
}

void Graphics::SetScissorTest(bool enable, const IntRect& rect)
{
    IntVector2 rtSize(GetRenderTargetDimensions());
    IntVector2 viewPos(viewport_.left_, viewport_.top_);

    if (enable)
    {
        IntRect intRect;
        intRect.left_ = Clamp(rect.left_ + viewPos.x_, 0, rtSize.x_ - 1);
        intRect.top_ = Clamp(rect.top_ + viewPos.y_, 0, rtSize.y_ - 1);
        intRect.right_ = Clamp(rect.right_ + viewPos.x_, 0, rtSize.x_);
        intRect.bottom_ = Clamp(rect.bottom_ + viewPos.y_, 0, rtSize.y_);

        if (intRect.right_ == intRect.left_)
            intRect.right_++;
        if (intRect.bottom_ == intRect.top_)
            intRect.bottom_++;

        if (intRect.right_ < intRect.left_ || intRect.bottom_ < intRect.top_)
            enable = false;

        if (enable && scissorRect_ != intRect)
        {
            // Use Direct3D convention with the vertical coordinates ie. 0 is top
            glScissor(intRect.left_, rtSize.y_ - intRect.bottom_, intRect.Width(), intRect.Height());
            scissorRect_ = intRect;
        }
    }
    else
        scissorRect_ = IntRect::ZERO;

    if (enable != scissorTest_)
    {
        if (enable)
            glEnable(GL_SCISSOR_TEST);
        else
            glDisable(GL_SCISSOR_TEST);
        scissorTest_ = enable;
    }
}

void Graphics::SetClipPlane(bool enable, const Plane& clipPlane, const Matrix3x4& view, const Matrix4& projection)
{
#ifndef GL_ES_VERSION_2_0
    if (enable != useClipPlane_)
    {
        if (enable)
            glEnable(GL_CLIP_PLANE0);
        else
            glDisable(GL_CLIP_PLANE0);

        useClipPlane_ = enable;
    }

    if (enable)
    {
        Matrix4 viewProj = projection * view;
        clipPlane_ = clipPlane.Transformed(viewProj).ToVector4();

        if (!gl3Support)
        {
            GLdouble planeData[4];
            planeData[0] = clipPlane_.x_;
            planeData[1] = clipPlane_.y_;
            planeData[2] = clipPlane_.z_;
            planeData[3] = clipPlane_.w_;

            glClipPlane(GL_CLIP_PLANE0, &planeData[0]);
        }
    }
#endif
}

void Graphics::SetStencilTest(bool enable, CompareMode mode, StencilOp pass, StencilOp fail, StencilOp zFail, unsigned stencilRef,
    unsigned compareMask, unsigned writeMask)
{
#ifndef GL_ES_VERSION_2_0
    if (enable != stencilTest_)
    {
        if (enable)
            glEnable(GL_STENCIL_TEST);
        else
            glDisable(GL_STENCIL_TEST);
        stencilTest_ = enable;
    }

    if (enable)
    {
        if (mode != stencilTestMode_ || stencilRef != stencilRef_ || compareMask != stencilCompareMask_)
        {
            glStencilFunc(glCmpFunc[mode], stencilRef, compareMask);
            stencilTestMode_ = mode;
            stencilRef_ = stencilRef;
            stencilCompareMask_ = compareMask;
        }
        if (writeMask != stencilWriteMask_)
        {
            glStencilMask(writeMask);
            stencilWriteMask_ = writeMask;
        }
        if (pass != stencilPass_ || fail != stencilFail_ || zFail != stencilZFail_)
        {
            glStencilOp(glStencilOps[fail], glStencilOps[zFail], glStencilOps[pass]);
            stencilPass_ = pass;
            stencilFail_ = fail;
            stencilZFail_ = zFail;
        }
    }
#endif
}

void Graphics::BeginDumpShaders(const String& fileName)
{
    shaderPrecache_ = new ShaderPrecache(context_, fileName);
}

void Graphics::EndDumpShaders()
{
    shaderPrecache_.Reset();
}

void Graphics::PrecacheShaders(Deserializer& source)
{
    URHO3D_PROFILE(PrecacheShaders);

    ShaderPrecache::LoadShaders(this, source);
}

bool Graphics::IsInitialized() const
{
    return impl_->window_ != 0;
}

bool Graphics::IsDeviceLost() const
{
    // On iOS treat window minimization as device loss, as it is forbidden to access OpenGL when minimized
#ifdef IOS
    if (impl_->window_ && (SDL_GetWindowFlags(impl_->window_) & SDL_WINDOW_MINIMIZED) != 0)
        return true;
#endif

    return impl_->context_ == 0;
}

IntVector2 Graphics::GetWindowPosition() const
{
    if (impl_->window_)
        return position_;
    return IntVector2::ZERO;
}

PODVector<IntVector2> Graphics::GetResolutions() const
{
    PODVector<IntVector2> ret;
    // Emscripten is not able to return a valid list
#ifndef __EMSCRIPTEN__
    unsigned numModes = (unsigned)SDL_GetNumDisplayModes(0);

    for (unsigned i = 0; i < numModes; ++i)
    {
        SDL_DisplayMode mode;
        SDL_GetDisplayMode(0, i, &mode);
        int width = mode.w;
        int height = mode.h;

        // Store mode if unique
        bool unique = true;
        for (unsigned j = 0; j < ret.Size(); ++j)
        {
            if (ret[j].x_ == width && ret[j].y_ == height)
            {
                unique = false;
                break;
            }
        }

        if (unique)
            ret.Push(IntVector2(width, height));
    }
#endif

    return ret;
}

PODVector<int> Graphics::GetMultiSampleLevels() const
{
    PODVector<int> ret;
    // No multisampling always supported
    ret.Push(1);
    /// \todo Implement properly, if possible

    return ret;
}

IntVector2 Graphics::GetDesktopResolution() const
{
#if !defined(ANDROID) && !defined(IOS)
    SDL_DisplayMode mode;
    SDL_GetDesktopDisplayMode(0, &mode);
    return IntVector2(mode.w, mode.h);
#else
    // SDL_GetDesktopDisplayMode() may not work correctly on mobile platforms. Rather return the window size
    return IntVector2(width_, height_);
#endif
}

unsigned Graphics::GetFormat(CompressedFormat format) const
{
    switch (format)
    {
    case CF_RGBA:
        return GL_RGBA;

    case CF_DXT1:
        return dxtTextureSupport_ ? GL_COMPRESSED_RGBA_S3TC_DXT1_EXT : 0;

#if !defined(GL_ES_VERSION_2_0) || defined(__EMSCRIPTEN__)
    case CF_DXT3:
        return dxtTextureSupport_ ? GL_COMPRESSED_RGBA_S3TC_DXT3_EXT : 0;

    case CF_DXT5:
        return dxtTextureSupport_ ? GL_COMPRESSED_RGBA_S3TC_DXT5_EXT : 0;
#endif
#ifdef GL_ES_VERSION_2_0
    case CF_ETC1:
        return etcTextureSupport_ ? GL_ETC1_RGB8_OES : 0;

    case CF_PVRTC_RGB_2BPP:
        return pvrtcTextureSupport_ ? COMPRESSED_RGB_PVRTC_2BPPV1_IMG : 0;

    case CF_PVRTC_RGB_4BPP:
        return pvrtcTextureSupport_ ? COMPRESSED_RGB_PVRTC_4BPPV1_IMG : 0;

    case CF_PVRTC_RGBA_2BPP:
        return pvrtcTextureSupport_ ? COMPRESSED_RGBA_PVRTC_2BPPV1_IMG : 0;

    case CF_PVRTC_RGBA_4BPP:
        return pvrtcTextureSupport_ ? COMPRESSED_RGBA_PVRTC_4BPPV1_IMG : 0;
#endif

    default:
        return 0;
    }
}

unsigned Graphics::GetMaxBones()
{
#ifdef RPI
    return 32;
#else
    return gl3Support ? 128 : 64;
#endif
}

ShaderVariation* Graphics::GetShader(ShaderType type, const String& name, const String& defines) const
{
    return GetShader(type, name.CString(), defines.CString());
}

ShaderVariation* Graphics::GetShader(ShaderType type, const char* name, const char* defines) const
{
    if (lastShaderName_ != name || !lastShader_)
    {
        ResourceCache* cache = GetSubsystem<ResourceCache>();

        String fullShaderName = shaderPath_ + name + shaderExtension_;
        // Try to reduce repeated error log prints because of missing shaders
        if (lastShaderName_ == name && !cache->Exists(fullShaderName))
            return 0;

        lastShader_ = cache->GetResource<Shader>(fullShaderName);
        lastShaderName_ = name;
    }

    return lastShader_ ? lastShader_->GetVariation(type, defines) : (ShaderVariation*)0;
}

VertexBuffer* Graphics::GetVertexBuffer(unsigned index) const
{
    return index < MAX_VERTEX_STREAMS ? vertexBuffers_[index] : 0;
}

TextureUnit Graphics::GetTextureUnit(const String& name)
{
    HashMap<String, TextureUnit>::Iterator i = textureUnits_.Find(name);
    if (i != textureUnits_.End())
        return i->second_;
    else
        return MAX_TEXTURE_UNITS;
}

const String& Graphics::GetTextureUnitName(TextureUnit unit)
{
    for (HashMap<String, TextureUnit>::Iterator i = textureUnits_.Begin(); i != textureUnits_.End(); ++i)
    {
        if (i->second_ == unit)
            return i->first_;
    }
    return String::EMPTY;
}

Texture* Graphics::GetTexture(unsigned index) const
{
    return index < MAX_TEXTURE_UNITS ? textures_[index] : 0;
}

RenderSurface* Graphics::GetRenderTarget(unsigned index) const
{
    return index < MAX_RENDERTARGETS ? renderTargets_[index] : 0;
}

IntVector2 Graphics::GetRenderTargetDimensions() const
{
    int width, height;

    if (renderTargets_[0])
    {
        width = renderTargets_[0]->GetWidth();
        height = renderTargets_[0]->GetHeight();
    }
    else if (depthStencil_)
    {
        width = depthStencil_->GetWidth();
        height = depthStencil_->GetHeight();
    }
    else
    {
        width = width_;
        height = height_;
    }

    return IntVector2(width, height);
}

void Graphics::WindowResized()
{
    if (!impl_->window_)
        return;

    int newWidth, newHeight;

    SDL_GL_GetDrawableSize(impl_->window_, &newWidth, &newHeight);
    if (newWidth == width_ && newHeight == height_)
        return;

    width_ = newWidth;
    height_ = newHeight;

    // Reset rendertargets and viewport for the new screen size. Also clean up any FBO's, as they may be screen size dependent
    CleanupFramebuffers();
    ResetRenderTargets();

    URHO3D_LOGDEBUGF("Window was resized to %dx%d", width_, height_);

    using namespace ScreenMode;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_WIDTH] = width_;
    eventData[P_HEIGHT] = height_;
    eventData[P_FULLSCREEN] = fullscreen_;
    eventData[P_RESIZABLE] = resizable_;
    eventData[P_BORDERLESS] = borderless_;
    SendEvent(E_SCREENMODE, eventData);
}

void Graphics::WindowMoved()
{
    if (!impl_->window_ || fullscreen_)
        return;

    int newX, newY;

    SDL_GetWindowPosition(impl_->window_, &newX, &newY);
    if (newX == position_.x_ && newY == position_.y_)
        return;

    position_.x_ = newX;
    position_.y_ = newY;

    URHO3D_LOGDEBUGF("Window was moved to %d,%d", position_.x_, position_.y_);

    using namespace WindowPos;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_X] = position_.x_;
    eventData[P_Y] = position_.y_;
    SendEvent(E_WINDOWPOS, eventData);
}

void Graphics::AddGPUObject(GPUObject* object)
{
    MutexLock lock(gpuObjectMutex_);

    gpuObjects_.Push(object);
}

void Graphics::RemoveGPUObject(GPUObject* object)
{
    MutexLock lock(gpuObjectMutex_);

    gpuObjects_.Remove(object);
}

void* Graphics::ReserveScratchBuffer(unsigned size)
{
    if (!size)
        return 0;

    if (size > maxScratchBufferRequest_)
        maxScratchBufferRequest_ = size;

    // First check for a free buffer that is large enough
    for (Vector<ScratchBuffer>::Iterator i = scratchBuffers_.Begin(); i != scratchBuffers_.End(); ++i)
    {
        if (!i->reserved_ && i->size_ >= size)
        {
            i->reserved_ = true;
            return i->data_.Get();
        }
    }

    // Then check if a free buffer can be resized
    for (Vector<ScratchBuffer>::Iterator i = scratchBuffers_.Begin(); i != scratchBuffers_.End(); ++i)
    {
        if (!i->reserved_)
        {
            i->data_ = new unsigned char[size];
            i->size_ = size;
            i->reserved_ = true;
            return i->data_.Get();
        }
    }

    // Finally allocate a new buffer
    ScratchBuffer newBuffer;
    newBuffer.data_ = new unsigned char[size];
    newBuffer.size_ = size;
    newBuffer.reserved_ = true;
    scratchBuffers_.Push(newBuffer);
    return newBuffer.data_.Get();
}

void Graphics::FreeScratchBuffer(void* buffer)
{
    if (!buffer)
        return;

    for (Vector<ScratchBuffer>::Iterator i = scratchBuffers_.Begin(); i != scratchBuffers_.End(); ++i)
    {
        if (i->reserved_ && i->data_.Get() == buffer)
        {
            i->reserved_ = false;
            return;
        }
    }

    URHO3D_LOGWARNING("Reserved scratch buffer " + ToStringHex((unsigned)(size_t)buffer) + " not found");
}

void Graphics::CleanupScratchBuffers()
{
    for (Vector<ScratchBuffer>::Iterator i = scratchBuffers_.Begin(); i != scratchBuffers_.End(); ++i)
    {
        if (!i->reserved_ && i->size_ > maxScratchBufferRequest_ * 2)
        {
            i->data_ = maxScratchBufferRequest_ > 0 ? new unsigned char[maxScratchBufferRequest_] : 0;
            i->size_ = maxScratchBufferRequest_;
        }
    }

    maxScratchBufferRequest_ = 0;
}

void Graphics::CleanupRenderSurface(RenderSurface* surface)
{
    if (!surface)
        return;

    // Flush pending FBO changes first if any
    PrepareDraw();

    unsigned currentFBO = impl_->boundFBO_;

    // Go through all FBOs and clean up the surface from them
    for (HashMap<unsigned long long, FrameBufferObject>::Iterator i = impl_->frameBuffers_.Begin();
         i != impl_->frameBuffers_.End(); ++i)
    {
        for (unsigned j = 0; j < MAX_RENDERTARGETS; ++j)
        {
            if (i->second_.colorAttachments_[j] == surface)
            {
                if (currentFBO != i->second_.fbo_)
                {
                    BindFramebuffer(i->second_.fbo_);
                    currentFBO = i->second_.fbo_;
                }
                BindColorAttachment(j, GL_TEXTURE_2D, 0);
                i->second_.colorAttachments_[j] = 0;
                // Mark drawbuffer bits to need recalculation
                i->second_.drawBuffers_ = M_MAX_UNSIGNED;
            }
        }
        if (i->second_.depthAttachment_ == surface)
        {
            if (currentFBO != i->second_.fbo_)
            {
                BindFramebuffer(i->second_.fbo_);
                currentFBO = i->second_.fbo_;
            }
            BindDepthAttachment(0, false);
            BindStencilAttachment(0, false);
            i->second_.depthAttachment_ = 0;
        }
    }

    // Restore previously bound FBO now if needed
    if (currentFBO != impl_->boundFBO_)
        BindFramebuffer(impl_->boundFBO_);
}

void Graphics::CleanupShaderPrograms(ShaderVariation* variation)
{
    for (ShaderProgramMap::Iterator i = shaderPrograms_.Begin(); i != shaderPrograms_.End();)
    {
        if (i->second_->GetVertexShader() == variation || i->second_->GetPixelShader() == variation)
            i = shaderPrograms_.Erase(i);
        else
            ++i;
    }

    if (vertexShader_ == variation || pixelShader_ == variation)
        shaderProgram_ = 0;
}

ConstantBuffer* Graphics::GetOrCreateConstantBuffer(unsigned bindingIndex, unsigned size)
{
    unsigned key = (bindingIndex << 16) | size;
    HashMap<unsigned, SharedPtr<ConstantBuffer> >::Iterator i = constantBuffers_.Find(key);
    if (i == constantBuffers_.End())
    {
        i = constantBuffers_.Insert(MakePair(key, SharedPtr<ConstantBuffer>(new ConstantBuffer(context_))));
        i->second_->SetSize(size);
    }
    return i->second_.Get();
}

void Graphics::Release(bool clearGPUObjects, bool closeWindow)
{
    if (!impl_->window_)
        return;

    {
        MutexLock lock(gpuObjectMutex_);

        if (clearGPUObjects)
        {
            // Shutting down: release all GPU objects that still exist
            // Shader programs are also GPU objects; clear them first to avoid list modification during iteration
            shaderPrograms_.Clear();

            for (PODVector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
                (*i)->Release();
            gpuObjects_.Clear();
        }
        else
        {
            // We are not shutting down, but recreating the context: mark GPU objects lost
            for (PODVector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
                (*i)->OnDeviceLost();

            // In this case clear shader programs last so that they do not attempt to delete their OpenGL program
            // from a context that may no longer exist
            shaderPrograms_.Clear();

            SendEvent(E_DEVICELOST);
        }
    }

    CleanupFramebuffers();
    depthTextures_.Clear();

    // End fullscreen mode first to counteract transition and getting stuck problems on OS X
#if defined(__APPLE__) && !defined(IOS)
    if (closeWindow && fullscreen_ && !externalWindow_)
        SDL_SetWindowFullscreen(impl_->window_, 0);
#endif

    if (impl_->context_)
    {
        // Do not log this message if we are exiting
        if (!clearGPUObjects)
            URHO3D_LOGINFO("OpenGL context lost");

        SDL_GL_DeleteContext(impl_->context_);
        impl_->context_ = 0;
    }

    if (closeWindow)
    {
        SDL_ShowCursor(SDL_TRUE);

        // Do not destroy external window except when shutting down
        if (!externalWindow_ || clearGPUObjects)
        {
            SDL_DestroyWindow(impl_->window_);
            impl_->window_ = 0;
        }
    }
}

void Graphics::Restore()
{
    if (!impl_->window_)
        return;

#ifdef ANDROID
    // On Android the context may be lost behind the scenes as the application is minimized
    if (impl_->context_ && !SDL_GL_GetCurrentContext())
    {
        impl_->context_ = 0;
        // Mark GPU objects lost without a current context. In this case they just mark their internal state lost
        // but do not perform OpenGL commands to delete the GL objects
        Release(false, false);
    }
#endif

    // Ensure first that the context exists
    if (!impl_->context_)
    {
        impl_->context_ = SDL_GL_CreateContext(impl_->window_);

#ifndef GL_ES_VERSION_2_0
        // If we're trying to use OpenGL 3, but context creation fails, retry with 2
        if (!forceGL2_ && !impl_->context_)
        {
            forceGL2_ = true;
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 0);
            impl_->context_ = SDL_GL_CreateContext(impl_->window_);
        }
#endif

#ifdef IOS
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&impl_->systemFBO_);
#endif

        if (!impl_->context_)
        {
            URHO3D_LOGERRORF("Could not create OpenGL context, root cause '%s'", SDL_GetError());
            return;
        }

        // Clear cached extensions string from the previous context
        extensions.Clear();

        // Initialize OpenGL extensions library (desktop only)
#ifndef GL_ES_VERSION_2_0
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            URHO3D_LOGERRORF("Could not initialize OpenGL extensions, root cause: '%s'", glewGetErrorString(err));
            return;
        }

        if (!forceGL2_ && GLEW_VERSION_3_2)
        {
            gl3Support = true;
            apiName_ = "GL3";

            // Create and bind a vertex array object that will stay in use throughout
            unsigned vertexArrayObject;
            glGenVertexArrays(1, &vertexArrayObject);
            glBindVertexArray(vertexArrayObject);
        }
        else if (GLEW_VERSION_2_0)
        {
            if (!GLEW_EXT_framebuffer_object || !GLEW_EXT_packed_depth_stencil)
            {
                URHO3D_LOGERROR("EXT_framebuffer_object and EXT_packed_depth_stencil OpenGL extensions are required");
                return;
            }

            gl3Support = false;
            apiName_ = "GL2";
        }
        else
        {
            URHO3D_LOGERROR("OpenGL 2.0 is required");
            return;
        }

        // Enable seamless cubemap if possible
        if (gl3Support || GLEW_ARB_seamless_cube_map)
            glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
#endif

        // Set up texture data read/write alignment. It is important that this is done before uploading any texture data
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        ResetCachedState();
    }

    {
        MutexLock lock(gpuObjectMutex_);

        for (PODVector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
            (*i)->OnDeviceReset();
    }

    SendEvent(E_DEVICERESET);
}

void Graphics::Maximize()
{
    if (!impl_->window_)
        return;

    SDL_MaximizeWindow(impl_->window_);
}

void Graphics::Minimize()
{
    if (!impl_->window_)
        return;

    SDL_MinimizeWindow(impl_->window_);
}

void Graphics::MarkFBODirty()
{
    impl_->fboDirty_ = true;
}

void Graphics::SetVBO(unsigned object)
{
    if (impl_->boundVBO_ != object)
    {
        if (object)
            glBindBuffer(GL_ARRAY_BUFFER, object);
        impl_->boundVBO_ = object;
    }
}

void Graphics::SetUBO(unsigned object)
{
#ifndef GL_ES_VERSION_2_0
    if (impl_->boundUBO_ != object)
    {
        if (object)
            glBindBuffer(GL_UNIFORM_BUFFER, object);
        impl_->boundUBO_ = object;
    }
#endif
}

unsigned Graphics::GetAlphaFormat()
{
#ifndef GL_ES_VERSION_2_0
    // Alpha format is deprecated on OpenGL 3+
    if (gl3Support)
        return GL_R8;
#endif
    return GL_ALPHA;
}

unsigned Graphics::GetLuminanceFormat()
{
#ifndef GL_ES_VERSION_2_0
    // Luminance format is deprecated on OpenGL 3+
    if (gl3Support)
        return GL_R8;
#endif
    return GL_LUMINANCE;
}

unsigned Graphics::GetLuminanceAlphaFormat()
{
#ifndef GL_ES_VERSION_2_0
    // Luminance alpha format is deprecated on OpenGL 3+
    if (gl3Support)
        return GL_RG8;
#endif
    return GL_LUMINANCE_ALPHA;
}

unsigned Graphics::GetRGBFormat()
{
    return GL_RGB;
}

unsigned Graphics::GetRGBAFormat()
{
    return GL_RGBA;
}

unsigned Graphics::GetRGBA16Format()
{
#ifndef GL_ES_VERSION_2_0
    return GL_RGBA16;
#else
    return GL_RGBA;
#endif
}

unsigned Graphics::GetRGBAFloat16Format()
{
#ifndef GL_ES_VERSION_2_0
    return GL_RGBA16F_ARB;
#else
    return GL_RGBA;
#endif
}

unsigned Graphics::GetRGBAFloat32Format()
{
#ifndef GL_ES_VERSION_2_0
    return GL_RGBA32F_ARB;
#else
    return GL_RGBA;
#endif
}

unsigned Graphics::GetRG16Format()
{
#ifndef GL_ES_VERSION_2_0
    return GL_RG16;
#else
    return GL_RGBA;
#endif
}

unsigned Graphics::GetRGFloat16Format()
{
#ifndef GL_ES_VERSION_2_0
    return GL_RG16F;
#else
    return GL_RGBA;
#endif
}

unsigned Graphics::GetRGFloat32Format()
{
#ifndef GL_ES_VERSION_2_0
    return GL_RG32F;
#else
    return GL_RGBA;
#endif
}

unsigned Graphics::GetFloat16Format()
{
#ifndef GL_ES_VERSION_2_0
    return GL_R16F;
#else
    return GL_LUMINANCE;
#endif
}

unsigned Graphics::GetFloat32Format()
{
#ifndef GL_ES_VERSION_2_0
    return GL_R32F;
#else
    return GL_LUMINANCE;
#endif
}

unsigned Graphics::GetLinearDepthFormat()
{
#ifndef GL_ES_VERSION_2_0
    // OpenGL 3 can use different color attachment formats
    if (gl3Support)
        return GL_R32F;
#endif
    // OpenGL 2 requires color attachments to have the same format, therefore encode deferred depth to RGBA manually
    // if not using a readable hardware depth texture
    return GL_RGBA;
}

unsigned Graphics::GetDepthStencilFormat()
{
#ifndef GL_ES_VERSION_2_0
    return GL_DEPTH24_STENCIL8_EXT;
#else
    return glesDepthStencilFormat;
#endif
}

unsigned Graphics::GetReadableDepthFormat()
{
#ifndef GL_ES_VERSION_2_0
    return GL_DEPTH_COMPONENT24;
#else
    return glesReadableDepthFormat;
#endif
}

unsigned Graphics::GetFormat(const String& formatName)
{
    String nameLower = formatName.ToLower().Trimmed();

    if (nameLower == "a")
        return GetAlphaFormat();
    if (nameLower == "l")
        return GetLuminanceFormat();
    if (nameLower == "la")
        return GetLuminanceAlphaFormat();
    if (nameLower == "rgb")
        return GetRGBFormat();
    if (nameLower == "rgba")
        return GetRGBAFormat();
    if (nameLower == "rgba16")
        return GetRGBA16Format();
    if (nameLower == "rgba16f")
        return GetRGBAFloat16Format();
    if (nameLower == "rgba32f")
        return GetRGBAFloat32Format();
    if (nameLower == "rg16")
        return GetRG16Format();
    if (nameLower == "rg16f")
        return GetRGFloat16Format();
    if (nameLower == "rg32f")
        return GetRGFloat32Format();
    if (nameLower == "r16f")
        return GetFloat16Format();
    if (nameLower == "r32f" || nameLower == "float")
        return GetFloat32Format();
    if (nameLower == "lineardepth" || nameLower == "depth")
        return GetLinearDepthFormat();
    if (nameLower == "d24s8")
        return GetDepthStencilFormat();
    if (nameLower == "readabledepth" || nameLower == "hwdepth")
        return GetReadableDepthFormat();

    return GetRGBFormat();
}

void Graphics::CreateWindowIcon()
{
    if (windowIcon_)
    {
        SDL_Surface* surface = windowIcon_->GetSDLSurface();
        if (surface)
        {
            SDL_SetWindowIcon(impl_->window_, surface);
            SDL_FreeSurface(surface);
        }
    }
}

void Graphics::CheckFeatureSupport()
{
    // Check supported features: light pre-pass, deferred rendering and hardware depth texture
    lightPrepassSupport_ = false;
    deferredSupport_ = false;

#ifndef GL_ES_VERSION_2_0
    int numSupportedRTs = 1;
    if (gl3Support)
    {
        // Work around GLEW failure to check extensions properly from a GL3 context
        instancingSupport_ = glDrawElementsInstanced != 0 && glVertexAttribDivisor != 0;
        dxtTextureSupport_ = true;
        anisotropySupport_ = true;
        sRGBSupport_ = true;
        sRGBWriteSupport_ = true;

        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &numSupportedRTs);
    }
    else
    {
        instancingSupport_ = GLEW_ARB_instanced_arrays != 0;
        dxtTextureSupport_ = GLEW_EXT_texture_compression_s3tc != 0;
        anisotropySupport_ = GLEW_EXT_texture_filter_anisotropic != 0;
        sRGBSupport_ = GLEW_EXT_texture_sRGB != 0;
        sRGBWriteSupport_ = GLEW_EXT_framebuffer_sRGB != 0;

        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &numSupportedRTs);
    }

    // Must support 2 rendertargets for light pre-pass, and 4 for deferred
    if (numSupportedRTs >= 2)
        lightPrepassSupport_ = true;
    if (numSupportedRTs >= 4)
        deferredSupport_ = true;

#if defined(__APPLE__) && !defined(IOS)
    // On OS X check for an Intel driver and use shadow map RGBA dummy color textures, because mixing
    // depth-only FBO rendering and backbuffer rendering will bug, resulting in a black screen in full
    // screen mode, and incomplete shadow maps in windowed mode
    String renderer((const char*)glGetString(GL_RENDERER));
    if (renderer.Contains("Intel", false))
        dummyColorFormat_ = GetRGBAFormat();
#endif
#else
    // Check for supported compressed texture formats
#ifdef __EMSCRIPTEN__
    dxtTextureSupport_ = CheckExtension("WEBGL_compressed_texture_s3tc"); // https://www.khronos.org/registry/webgl/extensions/WEBGL_compressed_texture_s3tc/
    etcTextureSupport_ = CheckExtension("WEBGL_compressed_texture_etc1"); // https://www.khronos.org/registry/webgl/extensions/WEBGL_compressed_texture_etc1/
    pvrtcTextureSupport_ = CheckExtension("WEBGL_compressed_texture_pvrtc"); // https://www.khronos.org/registry/webgl/extensions/WEBGL_compressed_texture_pvrtc/
    // Instancing is in core in WebGL 2, so the extension may not be present anymore. In WebGL 1, find https://www.khronos.org/registry/webgl/extensions/ANGLE_instanced_arrays/
    // TODO: In the distant future, this may break if WebGL 3 is introduced, so either improve the GL_VERSION parsing here, or keep track of which WebGL version we attempted to initialize.
    instancingSupport_ = (strstr((const char *)glGetString(GL_VERSION), "WebGL 2.") != 0) || CheckExtension("ANGLE_instanced_arrays");
#else
    dxtTextureSupport_ = CheckExtension("EXT_texture_compression_dxt1");
    etcTextureSupport_ = CheckExtension("OES_compressed_ETC1_RGB8_texture");
    pvrtcTextureSupport_ = CheckExtension("IMG_texture_compression_pvrtc");
#endif

    // Check for best supported depth renderbuffer format for GLES2
    if (CheckExtension("GL_OES_depth24"))
        glesDepthStencilFormat = GL_DEPTH_COMPONENT24_OES;
    if (CheckExtension("GL_OES_packed_depth_stencil"))
        glesDepthStencilFormat = GL_DEPTH24_STENCIL8_OES;
    #ifdef __EMSCRIPTEN__
    if (!CheckExtension("WEBGL_depth_texture"))
#else
    if (!CheckExtension("GL_OES_depth_texture"))
#endif
    {
        shadowMapFormat_ = 0;
        hiresShadowMapFormat_ = 0;
        glesReadableDepthFormat = 0;
    }
    else
    {
        #ifdef IOS
        // iOS hack: depth renderbuffer seems to fail, so use depth textures for everything
        // if supported
        glesDepthStencilFormat = GL_DEPTH_COMPONENT;
#endif
        shadowMapFormat_ = GL_DEPTH_COMPONENT;
        hiresShadowMapFormat_ = 0;
        // WebGL shadow map rendering seems to be extremely slow without an attached dummy color texture
        #ifdef __EMSCRIPTEN__
        dummyColorFormat_ = GetRGBAFormat();
#endif
    }
#endif
}

void Graphics::PrepareDraw()
{
#ifndef GL_ES_VERSION_2_0
    if (gl3Support)
    {
        for (PODVector<ConstantBuffer*>::Iterator i = dirtyConstantBuffers_.Begin(); i != dirtyConstantBuffers_.End(); ++i)
            (*i)->Apply();
        dirtyConstantBuffers_.Clear();
    }
#endif

    if (impl_->fboDirty_)
    {
        impl_->fboDirty_ = false;

        // First check if no framebuffer is needed. In that case simply return to backbuffer rendering
        bool noFbo = !depthStencil_;
        if (noFbo)
        {
            for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
            {
                if (renderTargets_[i])
                {
                    noFbo = false;
                    break;
                }
            }
        }

        if (noFbo)
        {
            if (impl_->boundFBO_ != impl_->systemFBO_)
            {
                BindFramebuffer(impl_->systemFBO_);
                impl_->boundFBO_ = impl_->systemFBO_;
            }

#ifndef GL_ES_VERSION_2_0
            // Disable/enable sRGB write
            if (sRGBWriteSupport_)
            {
                bool sRGBWrite = sRGB_;
                if (sRGBWrite != impl_->sRGBWrite_)
                {
                    if (sRGBWrite)
                        glEnable(GL_FRAMEBUFFER_SRGB_EXT);
                    else
                        glDisable(GL_FRAMEBUFFER_SRGB_EXT);
                    impl_->sRGBWrite_ = sRGBWrite;
                }
            }
#endif

            return;
        }

        // Search for a new framebuffer based on format & size, or create new
        IntVector2 rtSize = Graphics::GetRenderTargetDimensions();
        unsigned format = 0;
        if (renderTargets_[0])
            format = renderTargets_[0]->GetParentTexture()->GetFormat();
        else if (depthStencil_)
            format = depthStencil_->GetParentTexture()->GetFormat();

        unsigned long long fboKey = (rtSize.x_ << 16 | rtSize.y_) | (((unsigned long long)format) << 32);

        HashMap<unsigned long long, FrameBufferObject>::Iterator i = impl_->frameBuffers_.Find(fboKey);
        if (i == impl_->frameBuffers_.End())
        {
            FrameBufferObject newFbo;
            newFbo.fbo_ = CreateFramebuffer();
            i = impl_->frameBuffers_.Insert(MakePair(fboKey, newFbo));
        }

        if (impl_->boundFBO_ != i->second_.fbo_)
        {
            BindFramebuffer(i->second_.fbo_);
            impl_->boundFBO_ = i->second_.fbo_;
        }

#ifndef GL_ES_VERSION_2_0
        // Setup readbuffers & drawbuffers if needed
        if (i->second_.readBuffers_ != GL_NONE)
        {
            glReadBuffer(GL_NONE);
            i->second_.readBuffers_ = GL_NONE;
        }

        // Calculate the bit combination of non-zero color rendertargets to first check if the combination changed
        unsigned newDrawBuffers = 0;
        for (unsigned j = 0; j < MAX_RENDERTARGETS; ++j)
        {
            if (renderTargets_[j])
                newDrawBuffers |= 1 << j;
        }

        if (newDrawBuffers != i->second_.drawBuffers_)
        {
            // Check for no color rendertargets (depth rendering only)
            if (!newDrawBuffers)
                glDrawBuffer(GL_NONE);
            else
            {
                int drawBufferIds[MAX_RENDERTARGETS];
                unsigned drawBufferCount = 0;

                for (unsigned j = 0; j < MAX_RENDERTARGETS; ++j)
                {
                    if (renderTargets_[j])
                    {
                        if (!gl3Support)
                            drawBufferIds[drawBufferCount++] = GL_COLOR_ATTACHMENT0_EXT + j;
                        else
                            drawBufferIds[drawBufferCount++] = GL_COLOR_ATTACHMENT0 + j;
                    }
                }
                glDrawBuffers(drawBufferCount, (const GLenum*)drawBufferIds);
            }

            i->second_.drawBuffers_ = newDrawBuffers;
        }
#endif

        for (unsigned j = 0; j < MAX_RENDERTARGETS; ++j)
        {
            if (renderTargets_[j])
            {
                Texture* texture = renderTargets_[j]->GetParentTexture();

                // If texture's parameters are dirty, update before attaching
                if (texture->GetParametersDirty())
                {
                    SetTextureForUpdate(texture);
                    texture->UpdateParameters();
                    SetTexture(0, 0);
                }

                if (i->second_.colorAttachments_[j] != renderTargets_[j])
                {
                    BindColorAttachment(j, renderTargets_[j]->GetTarget(), texture->GetGPUObject());
                    i->second_.colorAttachments_[j] = renderTargets_[j];
                }
            }
            else
            {
                if (i->second_.colorAttachments_[j])
                {
                    BindColorAttachment(j, GL_TEXTURE_2D, 0);
                    i->second_.colorAttachments_[j] = 0;
                }
            }
        }

        if (depthStencil_)
        {
            // Bind either a renderbuffer or a depth texture, depending on what is available
            Texture* texture = depthStencil_->GetParentTexture();
#ifndef GL_ES_VERSION_2_0
            bool hasStencil = texture->GetFormat() == GL_DEPTH24_STENCIL8_EXT;
#else
            bool hasStencil = texture->GetFormat() == GL_DEPTH24_STENCIL8_OES;
#endif
            unsigned renderBufferID = depthStencil_->GetRenderBuffer();
            if (!renderBufferID)
            {
                // If texture's parameters are dirty, update before attaching
                if (texture->GetParametersDirty())
                {
                    SetTextureForUpdate(texture);
                    texture->UpdateParameters();
                    SetTexture(0, 0);
                }

                if (i->second_.depthAttachment_ != depthStencil_)
                {
                    BindDepthAttachment(texture->GetGPUObject(), false);
                    BindStencilAttachment(hasStencil ? texture->GetGPUObject() : 0, false);
                    i->second_.depthAttachment_ = depthStencil_;
                }
            }
            else
            {
                if (i->second_.depthAttachment_ != depthStencil_)
                {
                    BindDepthAttachment(renderBufferID, true);
                    BindStencilAttachment(hasStencil ? renderBufferID : 0, true);
                    i->second_.depthAttachment_ = depthStencil_;
                }
            }
        }
        else
        {
            if (i->second_.depthAttachment_)
            {
                BindDepthAttachment(0, false);
                BindStencilAttachment(0, false);
                i->second_.depthAttachment_ = 0;
            }
        }

#ifndef GL_ES_VERSION_2_0
        // Disable/enable sRGB write
        if (sRGBWriteSupport_)
        {
            bool sRGBWrite = renderTargets_[0] ? renderTargets_[0]->GetParentTexture()->GetSRGB() : sRGB_;
            if (sRGBWrite != impl_->sRGBWrite_)
            {
                if (sRGBWrite)
                    glEnable(GL_FRAMEBUFFER_SRGB_EXT);
                else
                    glDisable(GL_FRAMEBUFFER_SRGB_EXT);
                impl_->sRGBWrite_ = sRGBWrite;
            }
        }
#endif
    }

    if (impl_->vertexBuffersDirty_)
    {
        // Go through currently bound vertex buffers and set the attribute pointers that are available & required
        // Use reverse order so that elements from higher index buffers will override lower index buffers
        unsigned assignedLocations = 0;

        for (unsigned i = MAX_VERTEX_STREAMS - 1; i < MAX_VERTEX_STREAMS; --i)
        {
            VertexBuffer* buffer = vertexBuffers_[i];
            // Beware buffers with missing OpenGL objects, as binding a zero buffer object means accessing CPU memory for vertex data,
            // in which case the pointer will be invalid and cause a crash
            if (!buffer || !buffer->GetGPUObject() || !impl_->vertexAttributes_)
                continue;

            const PODVector<VertexElement>& elements = buffer->GetElements();

            for (PODVector<VertexElement>::ConstIterator j = elements.Begin(); j != elements.End(); ++j)
            {
                const VertexElement& element = *j;
                HashMap<Pair<unsigned char, unsigned char>, unsigned>::ConstIterator k =
                    impl_->vertexAttributes_->Find(MakePair((unsigned char)element.semantic_, element.index_));

                if (k != impl_->vertexAttributes_->End())
                {
                    unsigned location = k->second_;
                    unsigned locationMask = 1 << location;
                    if (assignedLocations & locationMask)
                        continue; // Already assigned by higher index vertex buffer
                    assignedLocations |= locationMask;

                    // Enable attribute if not enabled yet
                    if (!(impl_->enabledVertexAttributes_ & locationMask))
                    {
                        glEnableVertexAttribArray(location);
                        impl_->enabledVertexAttributes_ |= locationMask;
                    }

                    // Enable/disable instancing divisor as necessary
                    unsigned dataStart = element.offset_;
                    if (element.perInstance_)
                    {
                        dataStart += lastInstanceOffset_ * buffer->GetVertexSize();
                        if (!(impl_->instancingVertexAttributes_ & locationMask))
                        {
                            SetVertexAttribDivisor(location, 1);
                            impl_->instancingVertexAttributes_ |= locationMask;
                        }
                    }
                    else
                    {
                        if (impl_->instancingVertexAttributes_ & locationMask)
                        {
                            SetVertexAttribDivisor(location, 0);
                            impl_->instancingVertexAttributes_ &= ~locationMask;
                        }
                    }

                    SetVBO(buffer->GetGPUObject());
                    glVertexAttribPointer(location, glElementComponents[element.type_], glElementTypes[element.type_],
                        element.type_ == TYPE_UBYTE4_NORM ? GL_TRUE : GL_FALSE, (unsigned)buffer->GetVertexSize(),
                        (const void *)(size_t)dataStart);
                }
            }
        }

        // Finally disable unnecessary vertex attributes
        unsigned disableVertexAttributes = impl_->enabledVertexAttributes_ & (~impl_->usedVertexAttributes_);
        unsigned location = 0;
        while (disableVertexAttributes)
        {
            if (disableVertexAttributes & 1)
            {
                glDisableVertexAttribArray(location);
                impl_->enabledVertexAttributes_ &= ~(1 << location);
            }
            ++location;
            disableVertexAttributes >>= 1;
        }

        impl_->vertexBuffersDirty_ = false;
    }
}

void Graphics::CleanupFramebuffers()
{
    if (!IsDeviceLost())
    {
        BindFramebuffer(impl_->systemFBO_);
        impl_->boundFBO_ = impl_->systemFBO_;
        impl_->fboDirty_ = true;

        for (HashMap<unsigned long long, FrameBufferObject>::Iterator i = impl_->frameBuffers_.Begin();
             i != impl_->frameBuffers_.End(); ++i)
            DeleteFramebuffer(i->second_.fbo_);
    }
    else
        impl_->boundFBO_ = 0;

    impl_->frameBuffers_.Clear();
}

void Graphics::ResetCachedState()
{
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        vertexBuffers_[i] = 0;
        elementMasks_[i] = 0;
    }

    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
    {
        textures_[i] = 0;
        textureTypes_[i] = 0;
    }

    for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        renderTargets_[i] = 0;

    depthStencil_ = 0;
    viewport_ = IntRect(0, 0, 0, 0);
    indexBuffer_ = 0;
    vertexShader_ = 0;
    pixelShader_ = 0;
    shaderProgram_ = 0;
    blendMode_ = BLEND_REPLACE;
    textureAnisotropy_ = 1;
    colorWrite_ = true;
    cullMode_ = CULL_NONE;
    constantDepthBias_ = 0.0f;
    slopeScaledDepthBias_ = 0.0f;
    depthTestMode_ = CMP_ALWAYS;
    depthWrite_ = false;
    fillMode_ = FILL_SOLID;
    scissorTest_ = false;
    scissorRect_ = IntRect::ZERO;
    stencilTest_ = false;
    stencilTestMode_ = CMP_ALWAYS;
    stencilPass_ = OP_KEEP;
    stencilFail_ = OP_KEEP;
    stencilZFail_ = OP_KEEP;
    stencilRef_ = 0;
    stencilCompareMask_ = M_MAX_UNSIGNED;
    stencilWriteMask_ = M_MAX_UNSIGNED;
    useClipPlane_ = false;
    lastInstanceOffset_ = 0;
    impl_->activeTexture_ = 0;
    impl_->enabledVertexAttributes_ = 0;
    impl_->usedVertexAttributes_ = 0;
    impl_->instancingVertexAttributes_ = 0;
    impl_->boundFBO_ = impl_->systemFBO_;
    impl_->boundVBO_ = 0;
    impl_->boundUBO_ = 0;
    impl_->sRGBWrite_ = false;

    // Set initial state to match Direct3D
    if (impl_->context_)
    {
        glEnable(GL_DEPTH_TEST);
        SetCullMode(CULL_CCW);
        SetDepthTest(CMP_LESSEQUAL);
        SetDepthWrite(true);
    }

    for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS * 2; ++i)
        currentConstantBuffers_[i] = 0;
    dirtyConstantBuffers_.Clear();
}

void Graphics::SetTextureUnitMappings()
{
    textureUnits_["DiffMap"] = TU_DIFFUSE;
    textureUnits_["DiffCubeMap"] = TU_DIFFUSE;
    textureUnits_["AlbedoBuffer"] = TU_ALBEDOBUFFER;
    textureUnits_["NormalMap"] = TU_NORMAL;
    textureUnits_["NormalBuffer"] = TU_NORMALBUFFER;
    textureUnits_["SpecMap"] = TU_SPECULAR;
    textureUnits_["EmissiveMap"] = TU_EMISSIVE;
    textureUnits_["EnvMap"] = TU_ENVIRONMENT;
    textureUnits_["EnvCubeMap"] = TU_ENVIRONMENT;
    textureUnits_["LightRampMap"] = TU_LIGHTRAMP;
    textureUnits_["LightSpotMap"] = TU_LIGHTSHAPE;
    textureUnits_["LightCubeMap"] = TU_LIGHTSHAPE;
    textureUnits_["ShadowMap"] = TU_SHADOWMAP;
#ifdef DESKTOP_GRAPHICS
    textureUnits_["VolumeMap"] = TU_VOLUMEMAP;
    textureUnits_["FaceSelectCubeMap"] = TU_FACESELECT;
    textureUnits_["IndirectionCubeMap"] = TU_INDIRECTION;
    textureUnits_["DepthBuffer"] = TU_DEPTHBUFFER;
    textureUnits_["LightBuffer"] = TU_LIGHTBUFFER;
    textureUnits_["ZoneCubeMap"] = TU_ZONE;
    textureUnits_["ZoneVolumeMap"] = TU_ZONE;
#endif
}

unsigned Graphics::CreateFramebuffer()
{
    unsigned newFbo = 0;
#ifndef GL_ES_VERSION_2_0
    if (!gl3Support)
        glGenFramebuffersEXT(1, &newFbo);
    else
#endif
        glGenFramebuffers(1, &newFbo);
    return newFbo;
}

void Graphics::DeleteFramebuffer(unsigned fbo)
{
#ifndef GL_ES_VERSION_2_0
    if (!gl3Support)
        glDeleteFramebuffersEXT(1, &fbo);
    else
#endif
        glDeleteFramebuffers(1, &fbo);
}

void Graphics::BindFramebuffer(unsigned fbo)
{
#ifndef GL_ES_VERSION_2_0
    if (!gl3Support)
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
    else
#endif
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Graphics::BindColorAttachment(unsigned index, unsigned target, unsigned object)
{
#ifndef GL_ES_VERSION_2_0
    if (!gl3Support)
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + index, target, object, 0);
    else
#endif
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, target, object, 0);
}

void Graphics::BindDepthAttachment(unsigned object, bool isRenderBuffer)
{
    if (!object)
        isRenderBuffer = false;

#ifndef GL_ES_VERSION_2_0
    if (!gl3Support)
    {
        if (!isRenderBuffer)
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, object, 0);
        else
            glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, object);
    }
    else
#endif
    {
        if (!isRenderBuffer)
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, object, 0);
        else
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, object);
    }
}

void Graphics::BindStencilAttachment(unsigned object, bool isRenderBuffer)
{
    if (!object)
        isRenderBuffer = false;

#ifndef GL_ES_VERSION_2_0
    if (!gl3Support)
    {
        if (!isRenderBuffer)
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_TEXTURE_2D, object, 0);
        else
            glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, object);
    }
    else
#endif
    {
        if (!isRenderBuffer)
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, object, 0);
        else
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, object);
    }
}

bool Graphics::CheckFramebuffer()
{
#ifndef GL_ES_VERSION_2_0
    if (!gl3Support)
        return glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) == GL_FRAMEBUFFER_COMPLETE_EXT;
    else
#endif
        return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void Graphics::SetVertexAttribDivisor(unsigned location, unsigned divisor)
{
#ifndef GL_ES_VERSION_2_0
    if (gl3Support && instancingSupport_)
        glVertexAttribDivisor(location, divisor);
    else if (instancingSupport_)
        glVertexAttribDivisorARB(location, divisor);
#else
#ifdef __EMSCRIPTEN__
    if (instancingSupport_)
        glVertexAttribDivisorANGLE(location, divisor);
#endif
#endif
}

void RegisterGraphicsLibrary(Context* context)
{
    Animation::RegisterObject(context);
    Material::RegisterObject(context);
    Model::RegisterObject(context);
    Shader::RegisterObject(context);
    Technique::RegisterObject(context);
    Texture2D::RegisterObject(context);
    Texture2DArray::RegisterObject(context);
    Texture3D::RegisterObject(context);
    TextureCube::RegisterObject(context);
    Camera::RegisterObject(context);
    Drawable::RegisterObject(context);
    Light::RegisterObject(context);
    StaticModel::RegisterObject(context);
    StaticModelGroup::RegisterObject(context);
    Skybox::RegisterObject(context);
    AnimatedModel::RegisterObject(context);
    AnimationController::RegisterObject(context);
    BillboardSet::RegisterObject(context);
    ParticleEffect::RegisterObject(context);
    ParticleEmitter::RegisterObject(context);
    CustomGeometry::RegisterObject(context);
    DecalSet::RegisterObject(context);
    Terrain::RegisterObject(context);
    TerrainPatch::RegisterObject(context);
    DebugRenderer::RegisterObject(context);
    Octree::RegisterObject(context);
    Zone::RegisterObject(context);
}

}
