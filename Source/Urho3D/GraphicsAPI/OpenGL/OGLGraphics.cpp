// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Core/Context.h"
#include "../../Core/Mutex.h"
#include "../../Core/ProcessUtils.h"
#include "../../Core/Profiler.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsEvents.h"
#include "../../GraphicsAPI/ConstantBuffer.h"
#include "../../GraphicsAPI/IndexBuffer.h"
#include "../../GraphicsAPI/OpenGL/OGLGraphicsImpl.h"
#include "../../GraphicsAPI/OpenGL/OGLShaderProgram.h"
#include "../../GraphicsAPI/RenderSurface.h"
#include "../../GraphicsAPI/Shader.h"
#include "../../GraphicsAPI/ShaderPrecache.h"
#include "../../GraphicsAPI/ShaderVariation.h"
#include "../../GraphicsAPI/Texture2D.h"
#include "../../GraphicsAPI/TextureCube.h"
#include "../../GraphicsAPI/VertexBuffer.h"
#include "../../IO/File.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"

#include <SDL/SDL.h>

#include "../../DebugNew.h"

#ifdef GL_ES_VERSION_2_0
#define GL_DEPTH_COMPONENT24 GL_DEPTH_COMPONENT24_OES
#define glClearDepth glClearDepthf
#endif

#ifdef __EMSCRIPTEN__
#include "../../Input/Input.h"
#include "../../UI/Cursor.h"
#include "../../UI/UI.h"
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

// Emscripten provides even all GL extension functions via static linking. However there is
// no GLES2-specific extension header at the moment to include instanced rendering declarations,
// so declare them manually from GLES3 gl2ext.h. Emscripten will provide these when linking final output.
extern "C"
{
    GL_APICALL void GL_APIENTRY glDrawArraysInstancedANGLE (GLenum mode, GLint first, GLsizei count, GLsizei primcount);
    GL_APICALL void GL_APIENTRY glDrawElementsInstancedANGLE (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount);
    GL_APICALL void GL_APIENTRY glVertexAttribDivisorANGLE (GLuint index, GLuint divisor);
}

// Helper functions to support emscripten canvas resolution change
static const Urho3D::Context *appContext;

static void JSCanvasSize(int width, int height, bool fullscreen, float scale)
{
    URHO3D_LOGINFOF("JSCanvasSize: width=%d height=%d fullscreen=%d ui scale=%f", width, height, fullscreen, scale);

    using namespace Urho3D;

    if (appContext)
    {
        bool uiCursorVisible = false;
        bool systemCursorVisible = false;
        MouseMode mouseMode{};

        // Detect current system pointer state
        Input* input = appContext->GetSubsystem<Input>();
        if (input)
        {
            systemCursorVisible = input->IsMouseVisible();
            mouseMode = input->GetMouseMode();
        }

        UI* ui = appContext->GetSubsystem<UI>();
        if (ui)
        {
            ui->SetScale(scale);

            // Detect current UI pointer state
            Cursor* cursor = ui->GetCursor();
            if (cursor)
                uiCursorVisible = cursor->IsVisible();
        }

        // Apply new resolution
        appContext->GetSubsystem<Graphics>()->SetMode(width, height);

        // Reset the pointer state as it was before resolution change
        if (input)
        {
            if (uiCursorVisible)
                input->SetMouseVisible(false);
            else
                input->SetMouseVisible(systemCursorVisible);

            input->SetMouseMode(mouseMode);
        }

        if (ui)
        {
            Cursor* cursor = ui->GetCursor();
            if (cursor)
            {
                cursor->SetVisible(uiCursorVisible);

                IntVector2 pos = input->GetMousePosition();
                pos = ui->ConvertSystemToUI(pos);

                cursor->SetPosition(pos);
            }
        }
    }
}

using namespace emscripten;
EMSCRIPTEN_BINDINGS(Module) {
    function("JSCanvasSize", &JSCanvasSize);
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

void Graphics::Constructor_OGL()
{
    impl_ = new GraphicsImpl_OGL();
    position_ = IntVector2(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
    shadowMapFormat_ = GL_DEPTH_COMPONENT16;
    hiresShadowMapFormat_ = GL_DEPTH_COMPONENT24;
    shaderPath_ = "Shaders/GLSL/";
    shaderExtension_ = ".glsl";
    orientations_ = "LandscapeLeft LandscapeRight";
#ifndef GL_ES_VERSION_2_0
    apiName_ = "GL2";
#else
    apiName_ = "GLES2";
#endif

    Graphics::pixelUVOffset = Vector2(0.0f, 0.0f);
    Graphics::gl3Support = false;

    SetTextureUnitMappings_OGL();
    ResetCachedState_OGL();

    context_->RequireSDL(SDL_INIT_VIDEO);

    // Register Graphics library object factories
    RegisterGraphicsLibrary(context_);

#ifdef __EMSCRIPTEN__
    appContext = context_;
#endif
}

void Graphics::Destructor_OGL()
{
    Close_OGL();

    delete static_cast<GraphicsImpl_OGL*>(impl_);
    impl_ = nullptr;

    context_->ReleaseSDL();
}

bool Graphics::SetScreenMode_OGL(int width, int height, const ScreenModeParams& params, bool maximize)
{
    URHO3D_PROFILE(SetScreenMode_OGL);

    // Ensure that parameters are properly filled
    ScreenModeParams newParams = params;
    AdjustScreenMode(width, height, newParams, maximize);

    if (IsInitialized_OGL() && width == width_ && height == height_ && screenParams_ == newParams)
        return true;

    // If only vsync changes, do not destroy/recreate the context
    if (IsInitialized_OGL() && width == width_ && height == height_
        && screenParams_.EqualsExceptVSync(newParams) && screenParams_.vsync_ != newParams.vsync_)
    {
        SDL_GL_SetSwapInterval(newParams.vsync_ ? 1 : 0);
        screenParams_.vsync_ = newParams.vsync_;
        return true;
    }

    // Track if the window was repositioned and don't update window position in this case
    bool reposition = false;

    GraphicsImpl_OGL* impl = GetImpl_OGL();

    // With an external window, only the size can change after initial setup, so do not recreate context
    if (!externalWindow_ || !impl->context_)
    {
        // Close the existing window and OpenGL context, mark GPU objects as lost
        Release_OGL(false, true);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

#ifndef GL_ES_VERSION_2_0
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

        SDL_Rect display_rect;
        SDL_GetDisplayBounds(newParams.monitor_, &display_rect);
        reposition = newParams.fullscreen_ || (newParams.borderless_ && width >= display_rect.w && height >= display_rect.h);

        const int x = reposition ? display_rect.x : position_.x_;
        const int y = reposition ? display_rect.y : position_.y_;

        unsigned flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
        if (newParams.fullscreen_)
            flags |= SDL_WINDOW_FULLSCREEN;
        if (newParams.borderless_)
            flags |= SDL_WINDOW_BORDERLESS;
        if (newParams.resizable_)
            flags |= SDL_WINDOW_RESIZABLE;

#ifndef __EMSCRIPTEN__
        if (newParams.highDPI_)
            flags |= SDL_WINDOW_ALLOW_HIGHDPI;
#endif

        SDL_SetHint(SDL_HINT_ORIENTATIONS, orientations_.CString());

        // Try 24-bit depth first, fallback to 16-bit
        for (const int depthSize : { 24, 16 })
        {
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depthSize);

            // Try requested multisample level first, fallback to lower levels and no multisample
            for (int multiSample = newParams.multiSample_; multiSample > 0; multiSample /= 2)
            {
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

                if (!externalWindow_)
                    window_ = SDL_CreateWindow(windowTitle_.CString(), x, y, width, height, flags);
                else
                {
    #ifndef __EMSCRIPTEN__
                    if (!window_)
                        window_ = SDL_CreateWindowFrom(externalWindow_, SDL_WINDOW_OPENGL);
                    newParams.fullscreen_ = false;
    #endif
                }

                if (window_)
                {
                    // TODO: We probably want to keep depthSize as well
                    newParams.multiSample_ = multiSample;
                    break;
                }
            }

            if (window_)
                break;
        }

        if (!window_)
        {
            URHO3D_LOGERRORF("Could not create window, root cause: '%s'", SDL_GetError());
            return false;
        }

        // Reposition the window on the specified monitor
        if (reposition)
            SDL_SetWindowPosition(window_, display_rect.x, display_rect.y);

        CreateWindowIcon();

        if (maximize)
        {
            Maximize();
            SDL_GL_GetDrawableSize(window_, &width, &height);
        }

        // Create/restore context and GPU objects and set initial renderstate
        Restore_OGL();

        // Specific error message is already logged by Restore_OGL() when context creation or OpenGL extensions check fails
        if (!impl->context_)
            return false;
    }

    // Set vsync
    SDL_GL_SetSwapInterval(newParams.vsync_ ? 1 : 0);

    // Store the system FBO on iOS/tvOS now
#if defined(IOS) || defined(TVOS)
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&impl->systemFBO_);
#endif

    screenParams_ = newParams;

    SDL_GL_GetDrawableSize(window_, &width_, &height_);
    if (!reposition)
        SDL_GetWindowPosition(window_, &position_.x_, &position_.y_);

    int logicalWidth, logicalHeight;
    SDL_GetWindowSize(window_, &logicalWidth, &logicalHeight);
    screenParams_.highDPI_ = (width_ != logicalWidth) || (height_ != logicalHeight);

    // Reset rendertargets and viewport for the new screen mode
    ResetRenderTargets_OGL();

    // Clear the initial window contents to black
    Clear_OGL(CLEAR_COLOR);
    SDL_GL_SwapWindow(window_);

    CheckFeatureSupport_OGL();

#ifdef URHO3D_LOGGING
    URHO3D_LOGINFOF("Adapter used %s %s", (const char *) glGetString(GL_VENDOR), (const char *) glGetString(GL_RENDERER));
#endif

    OnScreenModeChanged();
    return true;
}

void Graphics::SetSRGB_OGL(bool enable)
{
    enable &= sRGBWriteSupport_;

    if (enable != sRGB_)
    {
        sRGB_ = enable;
        GetImpl_OGL()->fboDirty_ = true;
    }
}

void Graphics::SetDither_OGL(bool enable)
{
    if (enable)
        glEnable(GL_DITHER);
    else
        glDisable(GL_DITHER);
}

void Graphics::SetFlushGPU_OGL(bool enable)
{
    // Currently unimplemented on OpenGL
}

void Graphics::SetForceGL2_OGL(bool enable)
{
    if (IsInitialized_OGL())
    {
        URHO3D_LOGERROR("OpenGL 2 can only be forced before setting the initial screen mode");
        return;
    }

    forceGL2_ = enable;
}

void Graphics::Close_OGL()
{
    if (!IsInitialized_OGL())
        return;

    // Actually close the window
    Release_OGL(true, true);
}

bool Graphics::TakeScreenShot_OGL(Image& destImage)
{
    URHO3D_PROFILE(TakeScreenShot_OGL);

    if (!IsInitialized_OGL())
        return false;

    if (IsDeviceLost_OGL())
    {
        URHO3D_LOGERROR("Can not take screenshot while device is lost");
        return false;
    }

    ResetRenderTargets_OGL();

#ifndef GL_ES_VERSION_2_0
    destImage.SetSize(width_, height_, 3);
    glReadPixels(0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, destImage.GetData());
#else
    // Use RGBA format on OpenGL ES, as otherwise (at least on Android) the produced image is all black
    destImage.SetSize(width_, height_, 4);
    glReadPixels(0, 0, width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, destImage.GetData());
#endif

    // On OpenGL we need to flip the image vertically after reading
    destImage.FlipVertical();

    return true;
}

bool Graphics::BeginFrame_OGL()
{
    if (!IsInitialized_OGL() || IsDeviceLost_OGL())
        return false;

    // If using an external window, check it for size changes, and reset screen mode if necessary
    if (externalWindow_)
    {
        int width, height;

        SDL_GL_GetDrawableSize(window_, &width, &height);
        if (width != width_ || height != height_)
            SetMode(width, height);
    }

    // Re-enable depth test and depth func in case a third party program has modified it
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(glCmpFunc[depthTestMode_]);

    // Set default rendertarget and depth buffer
    ResetRenderTargets_OGL();

    // Cleanup textures from previous frame
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        SetTexture_OGL(i, nullptr);

    // Enable color and depth write
    SetColorWrite_OGL(true);
    SetDepthWrite_OGL(true);

    numPrimitives_ = 0;
    numBatches_ = 0;

    SendEvent(E_BEGINRENDERING);

    return true;
}

void Graphics::EndFrame_OGL()
{
    if (!IsInitialized_OGL())
        return;

    URHO3D_PROFILE(Present);

    SendEvent(E_ENDRENDERING);

    SDL_GL_SwapWindow(window_);

    // Clean up too large scratch buffers
    CleanupScratchBuffers();
}

void Graphics::Clear_OGL(ClearTargetFlags flags, const Color& color, float depth, unsigned stencil)
{
    PrepareDraw_OGL();

#ifdef GL_ES_VERSION_2_0
    flags &= ~CLEAR_STENCIL;
#endif

    bool oldColorWrite = colorWrite_;
    bool oldDepthWrite = depthWrite_;

    if (flags & CLEAR_COLOR && !oldColorWrite)
        SetColorWrite_OGL(true);
    if (flags & CLEAR_DEPTH && !oldDepthWrite)
        SetDepthWrite_OGL(true);
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
    IntVector2 viewSize = GetRenderTargetDimensions_OGL();
    if (viewport_.left_ != 0 || viewport_.top_ != 0 || viewport_.right_ != viewSize.x_ || viewport_.bottom_ != viewSize.y_)
        SetScissorTest_OGL(true, IntRect(0, 0, viewport_.Width(), viewport_.Height()));
    else
        SetScissorTest_OGL(false);

    glClear(glFlags);

    SetScissorTest_OGL(false);
    SetColorWrite_OGL(oldColorWrite);
    SetDepthWrite_OGL(oldDepthWrite);
    if (flags & CLEAR_STENCIL && stencilWriteMask_ != M_MAX_UNSIGNED)
        glStencilMask(stencilWriteMask_);
}

bool Graphics::ResolveToTexture_OGL(Texture2D* destination, const IntRect& viewport)
{
    if (!destination || !destination->GetRenderSurface())
        return false;

    URHO3D_PROFILE(ResolveToTexture_OGL);

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
    ResetRenderTargets_OGL();

    // Use Direct3D convention with the vertical coordinates ie. 0 is top
    SetTextureForUpdate_OGL(destination);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, vpCopy.left_, height_ - vpCopy.bottom_, vpCopy.Width(), vpCopy.Height());
    SetTexture_OGL(0, nullptr);

    return true;
}

bool Graphics::ResolveToTexture_OGL(Texture2D* texture)
{
#ifndef GL_ES_VERSION_2_0
    if (!texture)
        return false;
    RenderSurface* surface = texture->GetRenderSurface();
    if (!surface || !surface->GetRenderBuffer())
        return false;

    URHO3D_PROFILE(ResolveToTexture_OGL);

    texture->SetResolveDirty(false);
    surface->SetResolveDirty(false);

    GraphicsImpl_OGL* impl = GetImpl_OGL();

    // Use separate FBOs for resolve to not disturb the currently set rendertarget(s)
    if (!impl->resolveSrcFBO_)
        impl->resolveSrcFBO_ = CreateFramebuffer_OGL();
    if (!impl->resolveDestFBO_)
        impl->resolveDestFBO_ = CreateFramebuffer_OGL();

    if (!gl3Support)
    {
        glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, impl->resolveSrcFBO_);
        glFramebufferRenderbufferEXT(GL_READ_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT,
            surface->GetRenderBuffer());
        glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, impl->resolveDestFBO_);
        glFramebufferTexture2DEXT(GL_DRAW_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture->GetGPUObjectName(),
            0);
        glBlitFramebufferEXT(0, 0, texture->GetWidth(), texture->GetHeight(), 0, 0, texture->GetWidth(), texture->GetHeight(),
            GL_COLOR_BUFFER_BIT, GL_NEAREST);
        glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, 0);
        glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0);
    }
    else
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, impl->resolveSrcFBO_);
        glFramebufferRenderbuffer(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, surface->GetRenderBuffer());
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, impl->resolveDestFBO_);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->GetGPUObjectName(), 0);
        glBlitFramebuffer(0, 0, texture->GetWidth(), texture->GetHeight(), 0, 0, texture->GetWidth(), texture->GetHeight(),
            GL_COLOR_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }

    // Restore previously bound FBO
    BindFramebuffer_OGL(impl->boundFBO_);
    return true;
#else
    // Not supported on GLES
    return false;
#endif
}

bool Graphics::ResolveToTexture_OGL(TextureCube* texture)
{
#ifndef GL_ES_VERSION_2_0
    if (!texture)
        return false;

    URHO3D_PROFILE(ResolveToTexture_OGL);

    texture->SetResolveDirty(false);

    GraphicsImpl_OGL* impl = GetImpl_OGL();

    // Use separate FBOs for resolve to not disturb the currently set rendertarget(s)
    if (!impl->resolveSrcFBO_)
        impl->resolveSrcFBO_ = CreateFramebuffer_OGL();
    if (!impl->resolveDestFBO_)
        impl->resolveDestFBO_ = CreateFramebuffer_OGL();

    if (!gl3Support)
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            // Resolve only the surface(s) that were actually rendered to
            RenderSurface* surface = texture->GetRenderSurface((CubeMapFace)i);
            if (!surface->IsResolveDirty())
                continue;

            surface->SetResolveDirty(false);
            glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, impl->resolveSrcFBO_);
            glFramebufferRenderbufferEXT(GL_READ_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT,
                surface->GetRenderBuffer());
            glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, impl->resolveDestFBO_);
            glFramebufferTexture2DEXT(GL_DRAW_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                texture->GetGPUObjectName(), 0);
            glBlitFramebufferEXT(0, 0, texture->GetWidth(), texture->GetHeight(), 0, 0, texture->GetWidth(), texture->GetHeight(),
                GL_COLOR_BUFFER_BIT, GL_NEAREST);
        }

        glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, 0);
        glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0);
    }
    else
    {
        for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
        {
            RenderSurface* surface = texture->GetRenderSurface((CubeMapFace)i);
            if (!surface->IsResolveDirty())
                continue;

            surface->SetResolveDirty(false);
            glBindFramebuffer(GL_READ_FRAMEBUFFER, impl->resolveSrcFBO_);
            glFramebufferRenderbuffer(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, surface->GetRenderBuffer());
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, impl->resolveDestFBO_);
            glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                texture->GetGPUObjectName(), 0);
            glBlitFramebuffer(0, 0, texture->GetWidth(), texture->GetHeight(), 0, 0, texture->GetWidth(), texture->GetHeight(),
                GL_COLOR_BUFFER_BIT, GL_NEAREST);
        }

        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }

    // Restore previously bound FBO
    BindFramebuffer_OGL(impl->boundFBO_);
    return true;
#else
    // Not supported on GLES
    return false;
#endif
}

void Graphics::Draw_OGL(PrimitiveType type, unsigned vertexStart, unsigned vertexCount)
{
    if (!vertexCount)
        return;

    PrepareDraw_OGL();

    unsigned primitiveCount;
    GLenum glPrimitiveType;

    GetGLPrimitiveType(vertexCount, type, primitiveCount, glPrimitiveType);
    glDrawArrays(glPrimitiveType, vertexStart, vertexCount);

    numPrimitives_ += primitiveCount;
    ++numBatches_;
}

void Graphics::Draw_OGL(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount)
{
    if (!indexCount || !indexBuffer_ || !indexBuffer_->GetGPUObjectName())
        return;

    PrepareDraw_OGL();

    unsigned indexSize = indexBuffer_->GetIndexSize();
    unsigned primitiveCount;
    GLenum glPrimitiveType;

    GetGLPrimitiveType(indexCount, type, primitiveCount, glPrimitiveType);
    GLenum indexType = indexSize == sizeof(unsigned short) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
    glDrawElements(glPrimitiveType, indexCount, indexType, reinterpret_cast<const GLvoid*>(indexStart * indexSize));

    numPrimitives_ += primitiveCount;
    ++numBatches_;
}

void Graphics::Draw_OGL(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned baseVertexIndex, unsigned minVertex, unsigned vertexCount)
{
#ifndef GL_ES_VERSION_2_0
    if (!gl3Support || !indexCount || !indexBuffer_ || !indexBuffer_->GetGPUObjectName())
        return;

    PrepareDraw_OGL();

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

void Graphics::DrawInstanced_OGL(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount,
    unsigned instanceCount)
{
#if !defined(GL_ES_VERSION_2_0) || defined(__EMSCRIPTEN__)
    if (!indexCount || !indexBuffer_ || !indexBuffer_->GetGPUObjectName() || !instancingSupport_)
        return;

    PrepareDraw_OGL();

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

void Graphics::DrawInstanced_OGL(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned baseVertexIndex, unsigned minVertex,
        unsigned vertexCount, unsigned instanceCount)
{
#ifndef GL_ES_VERSION_2_0
    if (!gl3Support || !indexCount || !indexBuffer_ || !indexBuffer_->GetGPUObjectName() || !instancingSupport_)
        return;

    PrepareDraw_OGL();

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

void Graphics::SetVertexBuffer_OGL(VertexBuffer* buffer)
{
    // Note: this is not multi-instance safe
    static PODVector<VertexBuffer*> vertexBuffers(1);
    vertexBuffers[0] = buffer;
    SetVertexBuffers_OGL(vertexBuffers);
}

bool Graphics::SetVertexBuffers_OGL(const PODVector<VertexBuffer*>& buffers, unsigned instanceOffset)
{
    if (buffers.Size() > MAX_VERTEX_STREAMS)
    {
        URHO3D_LOGERROR("Too many vertex buffers");
        return false;
    }

    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (instanceOffset != impl->lastInstanceOffset_)
    {
        impl->lastInstanceOffset_ = instanceOffset;
        impl->vertexBuffersDirty_ = true;
    }

    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        VertexBuffer* buffer = nullptr;
        if (i < buffers.Size())
            buffer = buffers[i];
        if (buffer != vertexBuffers_[i])
        {
            vertexBuffers_[i] = buffer;
            impl->vertexBuffersDirty_ = true;
        }
    }

    return true;
}

bool Graphics::SetVertexBuffers_OGL(const Vector<SharedPtr<VertexBuffer> >& buffers, unsigned instanceOffset)
{
    return SetVertexBuffers_OGL(reinterpret_cast<const PODVector<VertexBuffer*>&>(buffers), instanceOffset);
}

void Graphics::SetIndexBuffer_OGL(IndexBuffer* buffer)
{
    if (indexBuffer_ == buffer)
        return;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer ? buffer->GetGPUObjectName() : 0);
    indexBuffer_ = buffer;
}

void Graphics::SetShaders_OGL(ShaderVariation* vs, ShaderVariation* ps)
{
    if (vs == vertexShader_ && ps == pixelShader_)
        return;

    // Compile the shaders now if not yet compiled. If already attempted, do not retry
    if (vs && !vs->GetGPUObjectName())
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
                vs = nullptr;
            }
        }
        else
            vs = nullptr;
    }

    if (ps && !ps->GetGPUObjectName())
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
                ps = nullptr;
            }
        }
        else
            ps = nullptr;
    }

    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (!vs || !ps)
    {
        glUseProgram(0);
        vertexShader_ = nullptr;
        pixelShader_ = nullptr;
        impl->shaderProgram_ = nullptr;
    }
    else
    {
        vertexShader_ = vs;
        pixelShader_ = ps;

        Pair<ShaderVariation*, ShaderVariation*> combination(vs, ps);
        ShaderProgramMap_OGL::Iterator i = impl->shaderPrograms_.Find(combination);

        if (i != impl->shaderPrograms_.End())
        {
            // Use the existing linked program
            if (i->second_->GetGPUObjectName())
            {
                glUseProgram(i->second_->GetGPUObjectName());
                impl->shaderProgram_ = i->second_;
            }
            else
            {
                glUseProgram(0);
                impl->shaderProgram_ = nullptr;
            }
        }
        else
        {
            // Link a new combination
            URHO3D_PROFILE(LinkShaders);

            SharedPtr<ShaderProgram_OGL> newProgram(new ShaderProgram_OGL(this, vs, ps));
            if (newProgram->Link())
            {
                URHO3D_LOGDEBUG("Linked vertex shader " + vs->GetFullName() + " and pixel shader " + ps->GetFullName());
                // Note: Link() calls glUseProgram() to set the texture sampler uniforms,
                // so it is not necessary to call it again
                impl->shaderProgram_ = newProgram;
            }
            else
            {
                URHO3D_LOGERROR("Failed to link vertex shader " + vs->GetFullName() + " and pixel shader " + ps->GetFullName() + ":\n" +
                         newProgram->GetLinkerOutput());
                glUseProgram(0);
                impl->shaderProgram_ = nullptr;
            }

            impl->shaderPrograms_[combination] = newProgram;
        }
    }

    // Update the clip plane uniform on GL3, and set constant buffers
#ifndef GL_ES_VERSION_2_0
    if (gl3Support && impl->shaderProgram_)
    {
        const SharedPtr<ConstantBuffer>* constantBuffers = impl->shaderProgram_->GetConstantBuffers();
        for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS * 2; ++i)
        {
            ConstantBuffer* buffer = constantBuffers[i].Get();
            if (buffer != impl->constantBuffers_[i])
            {
                unsigned object = buffer ? buffer->GetGPUObjectName() : 0;
                glBindBufferBase(GL_UNIFORM_BUFFER, i, object);
                // Calling glBindBufferBase also affects the generic buffer binding point
                impl->boundUBO_ = object;
                impl->constantBuffers_[i] = buffer;
                ShaderProgram_OGL::ClearGlobalParameterSource((ShaderParameterGroup)(i % MAX_SHADER_PARAMETER_GROUPS));
            }
        }

        SetShaderParameter_OGL(VSP_CLIPPLANE, useClipPlane_ ? clipPlane_ : Vector4(0.0f, 0.0f, 0.0f, 1.0f));
    }
#endif

    // Store shader combination if shader dumping in progress
    if (shaderPrecache_)
        shaderPrecache_->StoreShaders(vertexShader_, pixelShader_);

    if (impl->shaderProgram_)
    {
        impl->usedVertexAttributes_ = impl->shaderProgram_->GetUsedVertexAttributes();
        impl->vertexAttributes_ = &impl->shaderProgram_->GetVertexAttributes();
    }
    else
    {
        impl->usedVertexAttributes_ = 0;
        impl->vertexAttributes_ = nullptr;
    }

    impl->vertexBuffersDirty_ = true;
}

void Graphics::SetShaderParameter_OGL(StringHash param, const float* data, unsigned count)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (impl->shaderProgram_)
    {
        const ShaderParameter* info = impl->shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    impl->dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter(info->offset_, (unsigned)(count * sizeof(float)), data);
                return;
            }

            switch (info->glType_)
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

void Graphics::SetShaderParameter_OGL(StringHash param, float value)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (impl->shaderProgram_)
    {
        const ShaderParameter* info = impl->shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    impl->dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter(info->offset_, sizeof(float), &value);
                return;
            }

            glUniform1fv(info->location_, 1, &value);
        }
    }
}

void Graphics::SetShaderParameter_OGL(StringHash param, int value)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (impl->shaderProgram_)
    {
        const ShaderParameter* info = impl->shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    impl->dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter(info->offset_, sizeof(int), &value);
                return;
            }

            glUniform1i(info->location_, value);
        }
    }
}

void Graphics::SetShaderParameter_OGL(StringHash param, bool value)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    // \todo Not tested
    if (impl->shaderProgram_)
    {
        const ShaderParameter* info = impl->shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    impl->dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter(info->offset_, sizeof(bool), &value);
                return;
            }

            glUniform1i(info->location_, (int)value);
        }
    }
}

void Graphics::SetShaderParameter_OGL(StringHash param, const Color& color)
{
    SetShaderParameter_OGL(param, color.Data(), 4);
}

void Graphics::SetShaderParameter_OGL(StringHash param, const Vector2& vector)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (impl->shaderProgram_)
    {
        const ShaderParameter* info = impl->shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    impl->dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter(info->offset_, sizeof(Vector2), &vector);
                return;
            }

            // Check the uniform type to avoid mismatch
            switch (info->glType_)
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

void Graphics::SetShaderParameter_OGL(StringHash param, const Matrix3& matrix)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (impl->shaderProgram_)
    {
        const ShaderParameter* info = impl->shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    impl->dirtyConstantBuffers_.Push(buffer);
                buffer->SetVector3ArrayParameter(info->offset_, 3, &matrix);
                return;
            }

            glUniformMatrix3fv(info->location_, 1, GL_FALSE, matrix.Data());
        }
    }
}

void Graphics::SetShaderParameter_OGL(StringHash param, const Vector3& vector)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (impl->shaderProgram_)
    {
        const ShaderParameter* info = impl->shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    impl->dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter(info->offset_, sizeof(Vector3), &vector);
                return;
            }

            // Check the uniform type to avoid mismatch
            switch (info->glType_)
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

void Graphics::SetShaderParameter_OGL(StringHash param, const Matrix4& matrix)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (impl->shaderProgram_)
    {
        const ShaderParameter* info = impl->shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    impl->dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter(info->offset_, sizeof(Matrix4), &matrix);
                return;
            }

            glUniformMatrix4fv(info->location_, 1, GL_FALSE, matrix.Data());
        }
    }
}

void Graphics::SetShaderParameter_OGL(StringHash param, const Vector4& vector)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (impl->shaderProgram_)
    {
        const ShaderParameter* info = impl->shaderProgram_->GetParameter(param);
        if (info)
        {
            if (info->bufferPtr_)
            {
                ConstantBuffer* buffer = info->bufferPtr_;
                if (!buffer->IsDirty())
                    impl->dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter(info->offset_, sizeof(Vector4), &vector);
                return;
            }

            // Check the uniform type to avoid mismatch
            switch (info->glType_)
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

void Graphics::SetShaderParameter_OGL(StringHash param, const Matrix3x4& matrix)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (impl->shaderProgram_)
    {
        const ShaderParameter* info = impl->shaderProgram_->GetParameter(param);
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
                    impl->dirtyConstantBuffers_.Push(buffer);
                buffer->SetParameter(info->offset_, sizeof(Matrix4), &fullMatrix);
                return;
            }

            glUniformMatrix4fv(info->location_, 1, GL_FALSE, fullMatrix.Data());
        }
    }
}

bool Graphics::NeedParameterUpdate_OGL(ShaderParameterGroup group, const void* source)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();
    return impl->shaderProgram_ ? impl->shaderProgram_->NeedParameterUpdate(group, source) : false;
}

bool Graphics::HasShaderParameter_OGL(StringHash param)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();
    return impl->shaderProgram_ && impl->shaderProgram_->HasParameter(param);
}

bool Graphics::HasTextureUnit_OGL(TextureUnit unit)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();
    return impl->shaderProgram_ && impl->shaderProgram_->HasTextureUnit(unit);
}

void Graphics::ClearParameterSource_OGL(ShaderParameterGroup group)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();
    if (impl->shaderProgram_)
        impl->shaderProgram_->ClearParameterSource(group);
}

void Graphics::ClearParameterSources_OGL()
{
    ShaderProgram_OGL::ClearParameterSources();
}

void Graphics::ClearTransformSources_OGL()
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();
    if (impl->shaderProgram_)
    {
        impl->shaderProgram_->ClearParameterSource(SP_CAMERA);
        impl->shaderProgram_->ClearParameterSource(SP_OBJECT);
    }
}

void Graphics::SetTexture_OGL(unsigned index, Texture* texture)
{
    if (index >= MAX_TEXTURE_UNITS)
        return;

    // Check if texture is currently bound as a rendertarget. In that case, use its backup texture, or blank if not defined
    if (texture)
    {
        if (renderTargets_[0] && renderTargets_[0]->GetParentTexture() == texture)
            texture = texture->GetBackupTexture();
        else
        {
            // Resolve multisampled texture now as necessary
            if (texture->GetMultiSample() > 1 && texture->GetAutoResolve() && texture->IsResolveDirty())
            {
                if (texture->GetType() == Texture2D::GetTypeStatic())
                    ResolveToTexture_OGL(static_cast<Texture2D*>(texture));
                if (texture->GetType() == TextureCube::GetTypeStatic())
                    ResolveToTexture_OGL(static_cast<TextureCube*>(texture));
            }
        }
    }

    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (textures_[index] != texture)
    {
        if (impl->activeTexture_ != index)
        {
            glActiveTexture(GL_TEXTURE0 + index);
            impl->activeTexture_ = index;
        }

        if (texture)
        {
            unsigned glType = texture->GetTarget();
            // Unbind old texture type if necessary
            if (impl->textureTypes_[index] && impl->textureTypes_[index] != glType)
                glBindTexture(impl->textureTypes_[index], 0);
            glBindTexture(glType, texture->GetGPUObjectName());
            impl->textureTypes_[index] = glType;

            if (texture->GetParametersDirty())
                texture->UpdateParameters();
            if (texture->GetLevelsDirty())
                texture->RegenerateLevels();
        }
        else if (impl->textureTypes_[index])
        {
            glBindTexture(impl->textureTypes_[index], 0);
            impl->textureTypes_[index] = 0;
        }

        textures_[index] = texture;
    }
    else
    {
        if (texture && (texture->GetParametersDirty() || texture->GetLevelsDirty()))
        {
            if (impl->activeTexture_ != index)
            {
                glActiveTexture(GL_TEXTURE0 + index);
                impl->activeTexture_ = index;
            }

            glBindTexture(texture->GetTarget(), texture->GetGPUObjectName());
            if (texture->GetParametersDirty())
                texture->UpdateParameters();
            if (texture->GetLevelsDirty())
                texture->RegenerateLevels();
        }
    }
}

void Graphics::SetTextureForUpdate_OGL(Texture* texture)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (impl->activeTexture_ != 0)
    {
        glActiveTexture(GL_TEXTURE0);
        impl->activeTexture_ = 0;
    }

    unsigned glType = texture->GetTarget();
    // Unbind old texture type if necessary
    if (impl->textureTypes_[0] && impl->textureTypes_[0] != glType)
        glBindTexture(impl->textureTypes_[0], 0);
    glBindTexture(glType, texture->GetGPUObjectName());
    impl->textureTypes_[0] = glType;
    textures_[0] = texture;
}

void Graphics::SetDefaultTextureFilterMode_OGL(TextureFilterMode mode)
{
    if (mode != defaultTextureFilterMode_)
    {
        defaultTextureFilterMode_ = mode;
        SetTextureParametersDirty_OGL();
    }
}

void Graphics::SetDefaultTextureAnisotropy_OGL(unsigned level)
{
    level = Max(level, 1U);

    if (level != defaultTextureAnisotropy_)
    {
        defaultTextureAnisotropy_ = level;
        SetTextureParametersDirty_OGL();
    }
}

void Graphics::SetTextureParametersDirty_OGL()
{
    MutexLock lock(gpuObjectMutex_);

    for (PODVector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
    {
        auto* texture = dynamic_cast<Texture*>(*i);
        if (texture)
            texture->SetParametersDirty();
    }
}

void Graphics::ResetRenderTargets_OGL()
{
    for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        SetRenderTarget_OGL(i, (RenderSurface*)nullptr);
    SetDepthStencil_OGL((RenderSurface*)nullptr);
    SetViewport_OGL(IntRect(0, 0, width_, height_));
}

void Graphics::ResetRenderTarget_OGL(unsigned index)
{
    SetRenderTarget_OGL(index, (RenderSurface*)nullptr);
}

void Graphics::ResetDepthStencil_OGL()
{
    SetDepthStencil_OGL((RenderSurface*)nullptr);
}

void Graphics::SetRenderTarget_OGL(unsigned index, RenderSurface* renderTarget)
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
                    SetTexture_OGL(i, textures_[i]->GetBackupTexture());
            }

            // If multisampled, mark the texture & surface needing resolve
            if (parentTexture->GetMultiSample() > 1 && parentTexture->GetAutoResolve())
            {
                parentTexture->SetResolveDirty(true);
                renderTarget->SetResolveDirty(true);
            }

            // If mipmapped, mark the levels needing regeneration
            if (parentTexture->GetLevels() > 1)
                parentTexture->SetLevelsDirty();
        }

        GetImpl_OGL()->fboDirty_ = true;
    }
}

void Graphics::SetRenderTarget_OGL(unsigned index, Texture2D* texture)
{
    RenderSurface* renderTarget = nullptr;
    if (texture)
        renderTarget = texture->GetRenderSurface();

    SetRenderTarget_OGL(index, renderTarget);
}

void Graphics::SetDepthStencil_OGL(RenderSurface* depthStencil)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    // If we are using a rendertarget texture, it is required in OpenGL to also have an own depth-stencil
    // Create a new depth-stencil texture as necessary to be able to provide similar behaviour as Direct3D9
    // Only do this for non-multisampled rendertargets; when using multisampled target a similarly multisampled
    // depth-stencil should also be provided (backbuffer depth isn't compatible)
    if (renderTargets_[0] && renderTargets_[0]->GetMultiSample() == 1 && !depthStencil)
    {
        int width = renderTargets_[0]->GetWidth();
        int height = renderTargets_[0]->GetHeight();

        // Direct3D9 default depth-stencil can not be used when rendertarget is larger than the window.
        // Check size similarly
        if (width <= width_ && height <= height_)
        {
            unsigned searchKey = (width << 16u) | height;
            HashMap<unsigned, SharedPtr<Texture2D> >::Iterator i = impl->depthTextures_.Find(searchKey);
            if (i != impl->depthTextures_.End())
                depthStencil = i->second_->GetRenderSurface();
            else
            {
                SharedPtr<Texture2D> newDepthTexture(new Texture2D(context_));
                newDepthTexture->SetSize(width, height, GetDepthStencilFormat_OGL(), TEXTURE_DEPTHSTENCIL);
                impl->depthTextures_[searchKey] = newDepthTexture;
                depthStencil = newDepthTexture->GetRenderSurface();
            }
        }
    }

    if (depthStencil != depthStencil_)
    {
        depthStencil_ = depthStencil;
        impl->fboDirty_ = true;
    }
}

void Graphics::SetDepthStencil_OGL(Texture2D* texture)
{
    RenderSurface* depthStencil = nullptr;
    if (texture)
        depthStencil = texture->GetRenderSurface();

    SetDepthStencil_OGL(depthStencil);
}

void Graphics::SetViewport_OGL(const IntRect& rect)
{
    PrepareDraw_OGL();

    IntVector2 rtSize = GetRenderTargetDimensions_OGL();

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
    SetScissorTest_OGL(false);
}

void Graphics::SetBlendMode_OGL(BlendMode mode, bool alphaToCoverage)
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

    if (alphaToCoverage != alphaToCoverage_)
    {
        if (alphaToCoverage)
            glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        else
            glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

        alphaToCoverage_ = alphaToCoverage;
    }
}

void Graphics::SetColorWrite_OGL(bool enable)
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

void Graphics::SetCullMode_OGL(CullMode mode)
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

void Graphics::SetDepthBias_OGL(float constantBias, float slopeScaledBias)
{
    if (constantBias != constantDepthBias_ || slopeScaledBias != slopeScaledDepthBias_)
    {
#ifndef GL_ES_VERSION_2_0
        if (slopeScaledBias != 0.0f)
        {
            // OpenGL constant bias is unreliable and dependent on depth buffer bitdepth, apply in the projection matrix instead
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(slopeScaledBias, 0.0f);
        }
        else
            glDisable(GL_POLYGON_OFFSET_FILL);
#endif

        constantDepthBias_ = constantBias;
        slopeScaledDepthBias_ = slopeScaledBias;
        // Force update of the projection matrix shader parameter
        ClearParameterSource_OGL(SP_CAMERA);
    }
}

void Graphics::SetDepthTest_OGL(CompareMode mode)
{
    if (mode != depthTestMode_)
    {
        glDepthFunc(glCmpFunc[mode]);
        depthTestMode_ = mode;
    }
}

void Graphics::SetDepthWrite_OGL(bool enable)
{
    if (enable != depthWrite_)
    {
        glDepthMask(enable ? GL_TRUE : GL_FALSE);
        depthWrite_ = enable;
    }
}

void Graphics::SetFillMode_OGL(FillMode mode)
{
#ifndef GL_ES_VERSION_2_0
    if (mode != fillMode_)
    {
        glPolygonMode(GL_FRONT_AND_BACK, glFillMode[mode]);
        fillMode_ = mode;
    }
#endif
}

void Graphics::SetLineAntiAlias_OGL(bool enable)
{
#ifndef GL_ES_VERSION_2_0
    if (enable != lineAntiAlias_)
    {
        if (enable)
            glEnable(GL_LINE_SMOOTH);
        else
            glDisable(GL_LINE_SMOOTH);
        lineAntiAlias_ = enable;
    }
#endif
}

void Graphics::SetScissorTest_OGL(bool enable, const Rect& rect, bool borderInclusive)
{
    // During some light rendering loops, a full rect is toggled on/off repeatedly.
    // Disable scissor in that case to reduce state changes
    if (rect.min_.x_ <= 0.0f && rect.min_.y_ <= 0.0f && rect.max_.x_ >= 1.0f && rect.max_.y_ >= 1.0f)
        enable = false;

    if (enable)
    {
        IntVector2 rtSize(GetRenderTargetDimensions_OGL());
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

void Graphics::SetScissorTest_OGL(bool enable, const IntRect& rect)
{
    IntVector2 rtSize(GetRenderTargetDimensions_OGL());
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

void Graphics::SetClipPlane_OGL(bool enable, const Plane& clipPlane, const Matrix3x4& view, const Matrix4& projection)
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

void Graphics::SetStencilTest_OGL(bool enable, CompareMode mode, StencilOp pass, StencilOp fail, StencilOp zFail, unsigned stencilRef,
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

bool Graphics::IsInitialized_OGL() const
{
    return window_ != nullptr;
}

bool Graphics::GetDither_OGL() const
{
    return glIsEnabled(GL_DITHER) ? true : false;
}

bool Graphics::IsDeviceLost_OGL() const
{
    // On iOS and tvOS treat window minimization as device loss, as it is forbidden to access OpenGL when minimized
#if defined(IOS) || defined(TVOS)
    if (window_ && (SDL_GetWindowFlags(window_) & SDL_WINDOW_MINIMIZED) != 0)
        return true;
#endif

    return GetImpl_OGL()->context_ == nullptr;
}

PODVector<int> Graphics::GetMultiSampleLevels_OGL() const
{
    PODVector<int> ret;
    // No multisampling always supported
    ret.Push(1);

#ifndef GL_ES_VERSION_2_0
    int maxSamples = 0;
    glGetIntegerv(GL_MAX_SAMPLES, &maxSamples);
    for (int i = 2; i <= maxSamples && i <= 16; i *= 2)
        ret.Push(i);
#endif

    return ret;
}

unsigned Graphics::GetFormat_OGL(CompressedFormat format) const
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

    case CF_ETC2_RGB:
        return etc2TextureSupport_ ? GL_ETC2_RGB8_OES : 0;

    case CF_ETC2_RGBA:
        return etc2TextureSupport_ ? GL_ETC2_RGBA8_OES : 0;

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

unsigned Graphics::GetMaxBones_OGL()
{
#ifdef RPI
    // At the moment all RPI GPUs are low powered and only have limited number of uniforms
    return 32;
#else
    return gl3Support ? 128 : 64;
#endif
}

bool Graphics::GetGL3Support_OGL()
{
    return gl3Support;
}

ShaderVariation* Graphics::GetShader_OGL(ShaderType type, const String& name, const String& defines) const
{
    return GetShader_OGL(type, name.CString(), defines.CString());
}

ShaderVariation* Graphics::GetShader_OGL(ShaderType type, const char* name, const char* defines) const
{
    if (lastShaderName_ != name || !lastShader_)
    {
        auto* cache = GetSubsystem<ResourceCache>();

        String fullShaderName = shaderPath_ + name + shaderExtension_;
        // Try to reduce repeated error log prints because of missing shaders
        if (lastShaderName_ == name && !cache->Exists(fullShaderName))
            return nullptr;

        lastShader_ = cache->GetResource<Shader>(fullShaderName);
        lastShaderName_ = name;
    }

    return lastShader_ ? lastShader_->GetVariation(type, defines) : nullptr;
}

VertexBuffer* Graphics::GetVertexBuffer_OGL(unsigned index) const
{
    return index < MAX_VERTEX_STREAMS ? vertexBuffers_[index] : nullptr;
}

ShaderProgram_OGL* Graphics::GetShaderProgram_OGL() const
{
    return GetImpl_OGL()->shaderProgram_;
}

TextureUnit Graphics::GetTextureUnit_OGL(const String& name)
{
    HashMap<String, TextureUnit>::Iterator i = textureUnits_.Find(name);
    if (i != textureUnits_.End())
        return i->second_;
    else
        return MAX_TEXTURE_UNITS;
}

const String& Graphics::GetTextureUnitName_OGL(TextureUnit unit)
{
    for (HashMap<String, TextureUnit>::Iterator i = textureUnits_.Begin(); i != textureUnits_.End(); ++i)
    {
        if (i->second_ == unit)
            return i->first_;
    }
    return String::EMPTY;
}

Texture* Graphics::GetTexture_OGL(unsigned index) const
{
    return index < MAX_TEXTURE_UNITS ? textures_[index] : nullptr;
}

RenderSurface* Graphics::GetRenderTarget_OGL(unsigned index) const
{
    return index < MAX_RENDERTARGETS ? renderTargets_[index] : nullptr;
}

IntVector2 Graphics::GetRenderTargetDimensions_OGL() const
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

void Graphics::OnWindowResized_OGL()
{
    if (!window_)
        return;

    int newWidth, newHeight;

    SDL_GL_GetDrawableSize(window_, &newWidth, &newHeight);
    if (newWidth == width_ && newHeight == height_)
        return;

    width_ = newWidth;
    height_ = newHeight;

    int logicalWidth, logicalHeight;
    SDL_GetWindowSize(window_, &logicalWidth, &logicalHeight);
    screenParams_.highDPI_ = (width_ != logicalWidth) || (height_ != logicalHeight);

    // Reset rendertargets and viewport for the new screen size. Also clean up any FBO's, as they may be screen size dependent
    CleanupFramebuffers_OGL();
    ResetRenderTargets_OGL();

    URHO3D_LOGDEBUGF("Window was resized to %dx%d", width_, height_);

#ifdef __EMSCRIPTEN__
    EM_ASM({
        Module.SetRendererSize($0, $1);
    }, width_, height_);
#endif

    using namespace ScreenMode;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_WIDTH] = width_;
    eventData[P_HEIGHT] = height_;
    eventData[P_FULLSCREEN] = screenParams_.fullscreen_;
    eventData[P_RESIZABLE] = screenParams_.resizable_;
    eventData[P_BORDERLESS] = screenParams_.borderless_;
    eventData[P_HIGHDPI] = screenParams_.highDPI_;
    SendEvent(E_SCREENMODE, eventData);
}

void Graphics::OnWindowMoved_OGL()
{
    if (!window_ || screenParams_.fullscreen_)
        return;

    int newX, newY;

    SDL_GetWindowPosition(window_, &newX, &newY);
    if (newX == position_.x_ && newY == position_.y_)
        return;

    position_.x_ = newX;
    position_.y_ = newY;

    URHO3D_LOGTRACEF("Window was moved to %d,%d", position_.x_, position_.y_);

    using namespace WindowPos;

    VariantMap& eventData = GetEventDataMap();
    eventData[P_X] = position_.x_;
    eventData[P_Y] = position_.y_;
    SendEvent(E_WINDOWPOS, eventData);
}

void Graphics::CleanupRenderSurface_OGL(RenderSurface* surface)
{
    if (!surface)
        return;

    // Flush pending FBO changes first if any
    PrepareDraw_OGL();

    GraphicsImpl_OGL* impl = GetImpl_OGL();

    unsigned currentFBO = impl->boundFBO_;

    // Go through all FBOs and clean up the surface from them
    for (HashMap<unsigned long long, FrameBufferObject>::Iterator i = impl->frameBuffers_.Begin();
         i != impl->frameBuffers_.End(); ++i)
    {
        for (unsigned j = 0; j < MAX_RENDERTARGETS; ++j)
        {
            if (i->second_.colorAttachments_[j] == surface)
            {
                if (currentFBO != i->second_.fbo_)
                {
                    BindFramebuffer_OGL(i->second_.fbo_);
                    currentFBO = i->second_.fbo_;
                }
                BindColorAttachment_OGL(j, GL_TEXTURE_2D, 0, false);
                i->second_.colorAttachments_[j] = nullptr;
                // Mark drawbuffer bits to need recalculation
                i->second_.drawBuffers_ = M_MAX_UNSIGNED;
            }
        }
        if (i->second_.depthAttachment_ == surface)
        {
            if (currentFBO != i->second_.fbo_)
            {
                BindFramebuffer_OGL(i->second_.fbo_);
                currentFBO = i->second_.fbo_;
            }
            BindDepthAttachment_OGL(0, false);
            BindStencilAttachment_OGL(0, false);
            i->second_.depthAttachment_ = nullptr;
        }
    }

    // Restore previously bound FBO now if needed
    if (currentFBO != impl->boundFBO_)
        BindFramebuffer_OGL(impl->boundFBO_);
}

void Graphics::CleanupShaderPrograms_OGL(ShaderVariation* variation)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    for (ShaderProgramMap_OGL::Iterator i = impl->shaderPrograms_.Begin(); i != impl->shaderPrograms_.End();)
    {
        if (i->second_->GetVertexShader() == variation || i->second_->GetPixelShader() == variation)
            i = impl->shaderPrograms_.Erase(i);
        else
            ++i;
    }

    if (vertexShader_ == variation || pixelShader_ == variation)
        impl->shaderProgram_ = nullptr;
}

ConstantBuffer* Graphics::GetOrCreateConstantBuffer_OGL(ShaderType type,  unsigned index, unsigned size)
{
    // Note: shaderType parameter is not used on OpenGL, instead binding index should already use the PS range
    // for PS constant buffers

    GraphicsImpl_OGL* impl = GetImpl_OGL();

    unsigned key = (index << 16u) | size;
    HashMap<unsigned, SharedPtr<ConstantBuffer> >::Iterator i = impl->allConstantBuffers_.Find(key);
    if (i == impl->allConstantBuffers_.End())
    {
        i = impl->allConstantBuffers_.Insert(MakePair(key, SharedPtr<ConstantBuffer>(new ConstantBuffer(context_))));
        i->second_->SetSize(size);
    }
    return i->second_.Get();
}

void Graphics::Release_OGL(bool clearGPUObjects, bool closeWindow)
{
    if (!window_)
        return;

    GraphicsImpl_OGL* impl = GetImpl_OGL();

    {
        MutexLock lock(gpuObjectMutex_);

        if (clearGPUObjects)
        {
            // Shutting down: release all GPU objects that still exist
            // Shader programs are also GPU objects; clear them first to avoid list modification during iteration
            impl->shaderPrograms_.Clear();

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
            impl->shaderPrograms_.Clear();

            SendEvent(E_DEVICELOST);
        }
    }

    CleanupFramebuffers_OGL();
    impl->depthTextures_.Clear();

    // End fullscreen mode first to counteract transition and getting stuck problems on OS X
#if defined(__APPLE__) && !defined(IOS) && !defined(TVOS)
    if (closeWindow && screenParams_.fullscreen_ && !externalWindow_)
        SDL_SetWindowFullscreen(window_, 0);
#endif

    if (impl->context_)
    {
        // Do not log this message if we are exiting
        if (!clearGPUObjects)
            URHO3D_LOGINFO("OpenGL context lost");

        SDL_GL_DeleteContext(impl->context_);
        impl->context_ = nullptr;
    }

    if (closeWindow)
    {
        SDL_ShowCursor(SDL_TRUE);

        // Do not destroy external window except when shutting down
        if (!externalWindow_ || clearGPUObjects)
        {
            SDL_DestroyWindow(window_);
            window_ = nullptr;
        }
    }
}

void Graphics::Restore_OGL()
{
    if (!window_)
        return;

    GraphicsImpl_OGL* impl = GetImpl_OGL();

#ifdef __ANDROID__
    // On Android the context may be lost behind the scenes as the application is minimized
    if (impl->context_ && !SDL_GL_GetCurrentContext())
    {
        impl->context_ = 0;
        // Mark GPU objects lost without a current context. In this case they just mark their internal state lost
        // but do not perform OpenGL commands to delete the GL objects
        Release_OGL(false, false);
    }
#endif

    // Ensure first that the context exists
    if (!impl->context_)
    {
        impl->context_ = SDL_GL_CreateContext(window_);

#ifndef GL_ES_VERSION_2_0
        // If we're trying to use OpenGL 3, but context creation fails, retry with 2
        if (!forceGL2_ && !impl->context_)
        {
            forceGL2_ = true;
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 0);
            impl->context_ = SDL_GL_CreateContext(window_);
        }
#endif

#if defined(IOS) || defined(TVOS)
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&impl->systemFBO_);
#endif

        if (!impl->context_)
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
        // Note: even though we check the extension, this can lead to software fallback on some old GPU's
        // See https://github.com/urho3d/Urho3D/issues/1380 or
        // http://distrustsimplicity.net/articles/gl_texture_cube_map_seamless-on-os-x/
        // In case of trouble or for wanting maximum compatibility, simply remove the glEnable below.
        if (gl3Support || GLEW_ARB_seamless_cube_map)
            glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
#endif

        // Set up texture data read/write alignment. It is important that this is done before uploading any texture data
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        ResetCachedState_OGL();
    }

    {
        MutexLock lock(gpuObjectMutex_);

        for (PODVector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
            (*i)->OnDeviceReset();
    }

    SendEvent(E_DEVICERESET);
}

void Graphics::MarkFBODirty_OGL()
{
    GetImpl_OGL()->fboDirty_ = true;
}

void Graphics::SetVBO_OGL(unsigned object)
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (impl->boundVBO_ != object)
    {
        if (object)
            glBindBuffer(GL_ARRAY_BUFFER, object);
        impl->boundVBO_ = object;
    }
}

void Graphics::SetUBO_OGL(unsigned object)
{
#ifndef GL_ES_VERSION_2_0
    GraphicsImpl_OGL* impl = GetImpl_OGL();
    if (impl->boundUBO_ != object)
    {
        if (object)
            glBindBuffer(GL_UNIFORM_BUFFER, object);
        impl->boundUBO_ = object;
    }
#endif
}

unsigned Graphics::GetAlphaFormat_OGL()
{
#ifndef GL_ES_VERSION_2_0
    // Alpha format is deprecated on OpenGL 3+
    if (gl3Support)
        return GL_R8;
#endif
    return GL_ALPHA;
}

unsigned Graphics::GetLuminanceFormat_OGL()
{
#ifndef GL_ES_VERSION_2_0
    // Luminance format is deprecated on OpenGL 3+
    if (gl3Support)
        return GL_R8;
#endif
    return GL_LUMINANCE;
}

unsigned Graphics::GetLuminanceAlphaFormat_OGL()
{
#ifndef GL_ES_VERSION_2_0
    // Luminance alpha format is deprecated on OpenGL 3+
    if (gl3Support)
        return GL_RG8;
#endif
    return GL_LUMINANCE_ALPHA;
}

unsigned Graphics::GetRGBFormat_OGL()
{
    return GL_RGB;
}

unsigned Graphics::GetRGBAFormat_OGL()
{
    return GL_RGBA;
}

unsigned Graphics::GetRGBA16Format_OGL()
{
#ifndef GL_ES_VERSION_2_0
    return GL_RGBA16;
#else
    return GL_RGBA;
#endif
}

unsigned Graphics::GetRGBAFloat16Format_OGL()
{
#ifndef GL_ES_VERSION_2_0
    return GL_RGBA16F_ARB;
#else
    return GL_RGBA;
#endif
}

unsigned Graphics::GetRGBAFloat32Format_OGL()
{
#ifndef GL_ES_VERSION_2_0
    return GL_RGBA32F_ARB;
#else
    return GL_RGBA;
#endif
}

unsigned Graphics::GetRG16Format_OGL()
{
#ifndef GL_ES_VERSION_2_0
    return GL_RG16;
#else
    return GL_RGBA;
#endif
}

unsigned Graphics::GetRGFloat16Format_OGL()
{
#ifndef GL_ES_VERSION_2_0
    return GL_RG16F;
#else
    return GL_RGBA;
#endif
}

unsigned Graphics::GetRGFloat32Format_OGL()
{
#ifndef GL_ES_VERSION_2_0
    return GL_RG32F;
#else
    return GL_RGBA;
#endif
}

unsigned Graphics::GetFloat16Format_OGL()
{
#ifndef GL_ES_VERSION_2_0
    return GL_R16F;
#else
    return GL_LUMINANCE;
#endif
}

unsigned Graphics::GetFloat32Format_OGL()
{
#ifndef GL_ES_VERSION_2_0
    return GL_R32F;
#else
    return GL_LUMINANCE;
#endif
}

unsigned Graphics::GetLinearDepthFormat_OGL()
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

unsigned Graphics::GetDepthStencilFormat_OGL()
{
#ifndef GL_ES_VERSION_2_0
    return GL_DEPTH24_STENCIL8_EXT;
#else
    return glesDepthStencilFormat;
#endif
}

unsigned Graphics::GetReadableDepthFormat_OGL()
{
#ifndef GL_ES_VERSION_2_0
    return GL_DEPTH_COMPONENT24;
#else
    return glesReadableDepthFormat;
#endif
}

unsigned Graphics::GetFormat_OGL(const String& formatName)
{
    String nameLower = formatName.ToLower().Trimmed();

    if (nameLower == "a")
        return GetAlphaFormat_OGL();
    if (nameLower == "l")
        return GetLuminanceFormat_OGL();
    if (nameLower == "la")
        return GetLuminanceAlphaFormat_OGL();
    if (nameLower == "rgb")
        return GetRGBFormat_OGL();
    if (nameLower == "rgba")
        return GetRGBAFormat_OGL();
    if (nameLower == "rgba16")
        return GetRGBA16Format_OGL();
    if (nameLower == "rgba16f")
        return GetRGBAFloat16Format_OGL();
    if (nameLower == "rgba32f")
        return GetRGBAFloat32Format_OGL();
    if (nameLower == "rg16")
        return GetRG16Format_OGL();
    if (nameLower == "rg16f")
        return GetRGFloat16Format_OGL();
    if (nameLower == "rg32f")
        return GetRGFloat32Format_OGL();
    if (nameLower == "r16f")
        return GetFloat16Format_OGL();
    if (nameLower == "r32f" || nameLower == "float")
        return GetFloat32Format_OGL();
    if (nameLower == "lineardepth" || nameLower == "depth")
        return GetLinearDepthFormat_OGL();
    if (nameLower == "d24s8")
        return GetDepthStencilFormat_OGL();
    if (nameLower == "readabledepth" || nameLower == "hwdepth")
        return GetReadableDepthFormat_OGL();

    return GetRGBFormat_OGL();
}

void Graphics::CheckFeatureSupport_OGL()
{
    // Check supported features: light pre-pass, deferred rendering and hardware depth texture
    lightPrepassSupport_ = false;
    deferredSupport_ = false;

#ifndef GL_ES_VERSION_2_0
    int numSupportedRTs = 1;
    if (gl3Support)
    {
        // Work around GLEW failure to check extensions properly from a GL3 context
        instancingSupport_ = glDrawElementsInstanced != nullptr && glVertexAttribDivisor != nullptr;
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

#if defined(__APPLE__) && !defined(IOS) && !defined(TVOS)
    // On macOS check for an Intel driver and use shadow map RGBA dummy color textures, because mixing
    // depth-only FBO rendering and backbuffer rendering will bug, resulting in a black screen in full
    // screen mode, and incomplete shadow maps in windowed mode
    String renderer((const char*)glGetString(GL_RENDERER));
    if (renderer.Contains("Intel", false))
        dummyColorFormat_ = GetRGBAFormat_OGL();
#endif
#else
    // Check for supported compressed texture formats
#ifdef __EMSCRIPTEN__
    dxtTextureSupport_ = CheckExtension("WEBGL_compressed_texture_s3tc"); // https://www.khronos.org/registry/webgl/extensions/WEBGL_compressed_texture_s3tc/
    etcTextureSupport_ = CheckExtension("WEBGL_compressed_texture_etc1"); // https://www.khronos.org/registry/webgl/extensions/WEBGL_compressed_texture_etc1/
    pvrtcTextureSupport_ = CheckExtension("WEBGL_compressed_texture_pvrtc"); // https://www.khronos.org/registry/webgl/extensions/WEBGL_compressed_texture_pvrtc/
    etc2TextureSupport_ = gl3Support || CheckExtension("WEBGL_compressed_texture_etc"); // https://www.khronos.org/registry/webgl/extensions/WEBGL_compressed_texture_etc/
    // Instancing is in core in WebGL 2, so the extension may not be present anymore. In WebGL 1, find https://www.khronos.org/registry/webgl/extensions/ANGLE_instanced_arrays/
    // TODO: In the distant future, this may break if WebGL 3 is introduced, so either improve the GL_VERSION parsing here, or keep track of which WebGL version we attempted to initialize.
    instancingSupport_ = (strstr((const char *)glGetString(GL_VERSION), "WebGL 2.") != 0) || CheckExtension("ANGLE_instanced_arrays");
#else
    dxtTextureSupport_ = CheckExtension("EXT_texture_compression_dxt1");
    etcTextureSupport_ = CheckExtension("OES_compressed_ETC1_RGB8_texture");
    etc2TextureSupport_ = gl3Support || CheckExtension("OES_compressed_ETC2_RGBA8_texture");
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
#if defined(IOS) || defined(TVOS)
        // iOS hack: depth renderbuffer seems to fail, so use depth textures for everything if supported
        glesDepthStencilFormat = GL_DEPTH_COMPONENT;
#endif
        shadowMapFormat_ = GL_DEPTH_COMPONENT;
        hiresShadowMapFormat_ = 0;
        // WebGL shadow map rendering seems to be extremely slow without an attached dummy color texture
        #ifdef __EMSCRIPTEN__
        dummyColorFormat_ = GetRGBAFormat_OGL();
#endif
    }
#endif

    // Consider OpenGL shadows always hardware sampled, if supported at all
    hardwareShadowSupport_ = shadowMapFormat_ != 0;
}

void Graphics::PrepareDraw_OGL()
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

#ifndef GL_ES_VERSION_2_0
    if (gl3Support)
    {
        for (PODVector<ConstantBuffer*>::Iterator i = impl->dirtyConstantBuffers_.Begin(); i != impl->dirtyConstantBuffers_.End(); ++i)
            (*i)->Apply();
        impl->dirtyConstantBuffers_.Clear();
    }
#endif

    if (impl->fboDirty_)
    {
        impl->fboDirty_ = false;

        // First check if no framebuffer is needed. In that case simply return to backbuffer rendering
        bool noFbo = !depthStencil_;
        if (noFbo)
        {
            for (auto& renderTarget : renderTargets_)
            {
                if (renderTarget)
                {
                    noFbo = false;
                    break;
                }
            }
        }

        if (noFbo)
        {
            if (impl->boundFBO_ != impl->systemFBO_)
            {
                BindFramebuffer_OGL(impl->systemFBO_);
                impl->boundFBO_ = impl->systemFBO_;
            }

#ifndef GL_ES_VERSION_2_0
            // Disable/enable sRGB write
            if (sRGBWriteSupport_)
            {
                bool sRGBWrite = sRGB_;
                if (sRGBWrite != impl->sRGBWrite_)
                {
                    if (sRGBWrite)
                        glEnable(GL_FRAMEBUFFER_SRGB_EXT);
                    else
                        glDisable(GL_FRAMEBUFFER_SRGB_EXT);
                    impl->sRGBWrite_ = sRGBWrite;
                }
            }
#endif

            return;
        }

        // Search for a new framebuffer based on format & size, or create new
        IntVector2 rtSize = Graphics::GetRenderTargetDimensions_OGL();
        unsigned format = 0;
        if (renderTargets_[0])
            format = renderTargets_[0]->GetParentTexture()->GetFormat();
        else if (depthStencil_)
            format = depthStencil_->GetParentTexture()->GetFormat();

        auto fboKey = (unsigned long long)format << 32u | rtSize.x_ << 16u | rtSize.y_;
        HashMap<unsigned long long, FrameBufferObject>::Iterator i = impl->frameBuffers_.Find(fboKey);
        if (i == impl->frameBuffers_.End())
        {
            FrameBufferObject newFbo;
            newFbo.fbo_ = CreateFramebuffer_OGL();
            i = impl->frameBuffers_.Insert(MakePair(fboKey, newFbo));
        }

        if (impl->boundFBO_ != i->second_.fbo_)
        {
            BindFramebuffer_OGL(i->second_.fbo_);
            impl->boundFBO_ = i->second_.fbo_;
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
                newDrawBuffers |= 1u << j;
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

                // Bind either a renderbuffer or texture, depending on what is available
                unsigned renderBufferID = renderTargets_[j]->GetRenderBuffer();
                if (!renderBufferID)
                {
                    // If texture's parameters are dirty, update before attaching
                    if (texture->GetParametersDirty())
                    {
                        SetTextureForUpdate_OGL(texture);
                        texture->UpdateParameters();
                        SetTexture_OGL(0, nullptr);
                    }

                    if (i->second_.colorAttachments_[j] != renderTargets_[j])
                    {
                        BindColorAttachment_OGL(j, renderTargets_[j]->GetTarget(), texture->GetGPUObjectName(), false);
                        i->second_.colorAttachments_[j] = renderTargets_[j];
                    }
                }
                else
                {
                    if (i->second_.colorAttachments_[j] != renderTargets_[j])
                    {
                        BindColorAttachment_OGL(j, renderTargets_[j]->GetTarget(), renderBufferID, true);
                        i->second_.colorAttachments_[j] = renderTargets_[j];
                    }
                }
            }
            else
            {
                if (i->second_.colorAttachments_[j])
                {
                    BindColorAttachment_OGL(j, GL_TEXTURE_2D, 0, false);
                    i->second_.colorAttachments_[j] = nullptr;
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
                    SetTextureForUpdate_OGL(texture);
                    texture->UpdateParameters();
                    SetTexture_OGL(0, nullptr);
                }

                if (i->second_.depthAttachment_ != depthStencil_)
                {
                    BindDepthAttachment_OGL(texture->GetGPUObjectName(), false);
                    BindStencilAttachment_OGL(hasStencil ? texture->GetGPUObjectName() : 0, false);
                    i->second_.depthAttachment_ = depthStencil_;
                }
            }
            else
            {
                if (i->second_.depthAttachment_ != depthStencil_)
                {
                    BindDepthAttachment_OGL(renderBufferID, true);
                    BindStencilAttachment_OGL(hasStencil ? renderBufferID : 0, true);
                    i->second_.depthAttachment_ = depthStencil_;
                }
            }
        }
        else
        {
            if (i->second_.depthAttachment_)
            {
                BindDepthAttachment_OGL(0, false);
                BindStencilAttachment_OGL(0, false);
                i->second_.depthAttachment_ = nullptr;
            }
        }

#ifndef GL_ES_VERSION_2_0
        // Disable/enable sRGB write
        if (sRGBWriteSupport_)
        {
            bool sRGBWrite = renderTargets_[0] ? renderTargets_[0]->GetParentTexture()->GetSRGB() : sRGB_;
            if (sRGBWrite != impl->sRGBWrite_)
            {
                if (sRGBWrite)
                    glEnable(GL_FRAMEBUFFER_SRGB_EXT);
                else
                    glDisable(GL_FRAMEBUFFER_SRGB_EXT);
                impl->sRGBWrite_ = sRGBWrite;
            }
        }
#endif
    }

    if (impl->vertexBuffersDirty_)
    {
        // Go through currently bound vertex buffers and set the attribute pointers that are available & required
        // Use reverse order so that elements from higher index buffers will override lower index buffers
        unsigned assignedLocations = 0;

        for (unsigned i = MAX_VERTEX_STREAMS - 1; i < MAX_VERTEX_STREAMS; --i)
        {
            VertexBuffer* buffer = vertexBuffers_[i];
            // Beware buffers with missing OpenGL objects, as binding a zero buffer object means accessing CPU memory for vertex data,
            // in which case the pointer will be invalid and cause a crash
            if (!buffer || !buffer->GetGPUObjectName() || !impl->vertexAttributes_)
                continue;

            const PODVector<VertexElement>& elements = buffer->GetElements();

            for (PODVector<VertexElement>::ConstIterator j = elements.Begin(); j != elements.End(); ++j)
            {
                const VertexElement& element = *j;
                HashMap<Pair<unsigned char, unsigned char>, unsigned>::ConstIterator k =
                    impl->vertexAttributes_->Find(MakePair((unsigned char)element.semantic_, element.index_));

                if (k != impl->vertexAttributes_->End())
                {
                    unsigned location = k->second_;
                    unsigned locationMask = 1u << location;
                    if (assignedLocations & locationMask)
                        continue; // Already assigned by higher index vertex buffer
                    assignedLocations |= locationMask;

                    // Enable attribute if not enabled yet
                    if (!(impl->enabledVertexAttributes_ & locationMask))
                    {
                        glEnableVertexAttribArray(location);
                        impl->enabledVertexAttributes_ |= locationMask;
                    }

                    // Enable/disable instancing divisor as necessary
                    unsigned dataStart = element.offset_;
                    if (element.perInstance_)
                    {
                        dataStart += impl->lastInstanceOffset_ * buffer->GetVertexSize();
                        if (!(impl->instancingVertexAttributes_ & locationMask))
                        {
                            SetVertexAttribDivisor_OGL(location, 1);
                            impl->instancingVertexAttributes_ |= locationMask;
                        }
                    }
                    else
                    {
                        if (impl->instancingVertexAttributes_ & locationMask)
                        {
                            SetVertexAttribDivisor_OGL(location, 0);
                            impl->instancingVertexAttributes_ &= ~locationMask;
                        }
                    }

                    SetVBO_OGL(buffer->GetGPUObjectName());
                    glVertexAttribPointer(location, glElementComponents[element.type_], glElementTypes[element.type_],
                        element.type_ == TYPE_UBYTE4_NORM ? GL_TRUE : GL_FALSE, (unsigned)buffer->GetVertexSize(),
                        (const void *)(size_t)dataStart);
                }
            }
        }

        // Finally disable unnecessary vertex attributes
        unsigned disableVertexAttributes = impl->enabledVertexAttributes_ & (~impl->usedVertexAttributes_);
        unsigned location = 0;
        while (disableVertexAttributes)
        {
            if (disableVertexAttributes & 1u)
            {
                glDisableVertexAttribArray(location);
                impl->enabledVertexAttributes_ &= ~(1u << location);
            }
            ++location;
            disableVertexAttributes >>= 1;
        }

        impl->vertexBuffersDirty_ = false;
    }
}

void Graphics::CleanupFramebuffers_OGL()
{
    GraphicsImpl_OGL* impl = GetImpl_OGL();

    if (!IsDeviceLost_OGL())
    {
        BindFramebuffer_OGL(impl->systemFBO_);
        impl->boundFBO_ = impl->systemFBO_;
        impl->fboDirty_ = true;

        for (HashMap<unsigned long long, FrameBufferObject>::Iterator i = impl->frameBuffers_.Begin();
             i != impl->frameBuffers_.End(); ++i)
            DeleteFramebuffer_OGL(i->second_.fbo_);

        if (impl->resolveSrcFBO_)
            DeleteFramebuffer_OGL(impl->resolveSrcFBO_);
        if (impl->resolveDestFBO_)
            DeleteFramebuffer_OGL(impl->resolveDestFBO_);
    }
    else
        impl->boundFBO_ = 0;

    impl->resolveSrcFBO_ = 0;
    impl->resolveDestFBO_ = 0;

    impl->frameBuffers_.Clear();
}

void Graphics::ResetCachedState_OGL()
{
    for (auto& vertexBuffer : vertexBuffers_)
        vertexBuffer = nullptr;

    GraphicsImpl_OGL* impl = GetImpl_OGL();

    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
    {
        textures_[i] = nullptr;
        impl->textureTypes_[i] = 0;
    }

    for (auto& renderTarget : renderTargets_)
        renderTarget = nullptr;

    depthStencil_ = nullptr;
    viewport_ = IntRect(0, 0, 0, 0);
    indexBuffer_ = nullptr;
    vertexShader_ = nullptr;
    pixelShader_ = nullptr;
    blendMode_ = BLEND_REPLACE;
    alphaToCoverage_ = false;
    colorWrite_ = true;
    cullMode_ = CULL_NONE;
    constantDepthBias_ = 0.0f;
    slopeScaledDepthBias_ = 0.0f;
    depthTestMode_ = CMP_ALWAYS;
    depthWrite_ = false;
    lineAntiAlias_ = false;
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
    impl->shaderProgram_ = nullptr;
    impl->lastInstanceOffset_ = 0;
    impl->activeTexture_ = 0;
    impl->enabledVertexAttributes_ = 0;
    impl->usedVertexAttributes_ = 0;
    impl->instancingVertexAttributes_ = 0;
    impl->boundFBO_ = impl->systemFBO_;
    impl->boundVBO_ = 0;
    impl->boundUBO_ = 0;
    impl->sRGBWrite_ = false;

    // Set initial state to match Direct3D
    if (impl->context_)
    {
        glEnable(GL_DEPTH_TEST);
        SetCullMode_OGL(CULL_CCW);
        SetDepthTest_OGL(CMP_LESSEQUAL);
        SetDepthWrite_OGL(true);
    }

    for (auto& constantBuffer : impl->constantBuffers_)
        constantBuffer = nullptr;
    impl->dirtyConstantBuffers_.Clear();
}

void Graphics::SetTextureUnitMappings_OGL()
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
#ifndef GL_ES_VERSION_2_0
    textureUnits_["VolumeMap"] = TU_VOLUMEMAP;
    textureUnits_["FaceSelectCubeMap"] = TU_FACESELECT;
    textureUnits_["IndirectionCubeMap"] = TU_INDIRECTION;
    textureUnits_["DepthBuffer"] = TU_DEPTHBUFFER;
    textureUnits_["LightBuffer"] = TU_LIGHTBUFFER;
    textureUnits_["ZoneCubeMap"] = TU_ZONE;
    textureUnits_["ZoneVolumeMap"] = TU_ZONE;
#endif
}

unsigned Graphics::CreateFramebuffer_OGL()
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

void Graphics::DeleteFramebuffer_OGL(unsigned fbo)
{
#ifndef GL_ES_VERSION_2_0
    if (!gl3Support)
        glDeleteFramebuffersEXT(1, &fbo);
    else
#endif
        glDeleteFramebuffers(1, &fbo);
}

void Graphics::BindFramebuffer_OGL(unsigned fbo)
{
#ifndef GL_ES_VERSION_2_0
    if (!gl3Support)
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
    else
#endif
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Graphics::BindColorAttachment_OGL(unsigned index, unsigned target, unsigned object, bool isRenderBuffer)
{
    if (!object)
        isRenderBuffer = false;

#ifndef GL_ES_VERSION_2_0
    if (!gl3Support)
    {
        if (!isRenderBuffer)
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + index, target, object, 0);
        else
            glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + index, GL_RENDERBUFFER_EXT, object);
    }
    else
#endif
    {
        if (!isRenderBuffer)
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, target, object, 0);
        else
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_RENDERBUFFER, object);
    }
}

void Graphics::BindDepthAttachment_OGL(unsigned object, bool isRenderBuffer)
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

void Graphics::BindStencilAttachment_OGL(unsigned object, bool isRenderBuffer)
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

bool Graphics::CheckFramebuffer_OGL()
{
#ifndef GL_ES_VERSION_2_0
    if (!gl3Support)
        return glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) == GL_FRAMEBUFFER_COMPLETE_EXT;
    else
#endif
        return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void Graphics::SetVertexAttribDivisor_OGL(unsigned location, unsigned divisor)
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

}
