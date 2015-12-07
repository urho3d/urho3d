//
// Copyright (c) 2008-2015 the Urho3D project.
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
#include "../../Core/ProcessUtils.h"
#include "../../Core/Profiler.h"
#include "../../Graphics/AnimatedModel.h"
#include "../../Graphics/Animation.h"
#include "../../Graphics/AnimationController.h"
#include "../../Graphics/Camera.h"
#include "../../Graphics/ConstantBuffer.h"
#include "../../Graphics/CustomGeometry.h"
#include "../../Graphics/DebugRenderer.h"
#include "../../Graphics/DecalSet.h"
#include "../../Graphics/Geometry.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsEvents.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/IndexBuffer.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/Octree.h"
#include "../../Graphics/ParticleEffect.h"
#include "../../Graphics/ParticleEmitter.h"
#include "../../Graphics/Renderer.h"
#include "../../Graphics/Shader.h"
#include "../../Graphics/ShaderPrecache.h"
#include "../../Graphics/ShaderProgram.h"
#include "../../Graphics/Skybox.h"
#include "../../Graphics/StaticModelGroup.h"
#include "../../Graphics/Technique.h"
#include "../../Graphics/Terrain.h"
#include "../../Graphics/TerrainPatch.h"
#include "../../Graphics/Texture2D.h"
#include "../../Graphics/Texture3D.h"
#include "../../Graphics/TextureCube.h"
#include "../../Graphics/VertexBuffer.h"
#include "../../Graphics/VertexDeclaration.h"
#include "../../Graphics/Zone.h"
#include "../../IO/File.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"

#include <SDL/SDL_syswm.h>

#include "../../DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

// Prefer the high-performance GPU on switchable GPU systems
extern "C"
{
__declspec(dllexport) DWORD NvOptimusEnablement = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

namespace Urho3D
{

static const D3D11_COMPARISON_FUNC d3dCmpFunc[] =
{
    D3D11_COMPARISON_ALWAYS,
    D3D11_COMPARISON_EQUAL,
    D3D11_COMPARISON_NOT_EQUAL,
    D3D11_COMPARISON_LESS,
    D3D11_COMPARISON_LESS_EQUAL,
    D3D11_COMPARISON_GREATER,
    D3D11_COMPARISON_GREATER_EQUAL
};

static const DWORD d3dBlendEnable[] =
{
    FALSE,
    TRUE,
    TRUE,
    TRUE,
    TRUE,
    TRUE,
    TRUE,
    TRUE
};

static const D3D11_BLEND d3dSrcBlend[] =
{
    D3D11_BLEND_ONE,
    D3D11_BLEND_ONE,
    D3D11_BLEND_DEST_COLOR,
    D3D11_BLEND_SRC_ALPHA,
    D3D11_BLEND_SRC_ALPHA,
    D3D11_BLEND_ONE,
    D3D11_BLEND_INV_DEST_ALPHA,
    D3D11_BLEND_ONE,
    D3D11_BLEND_SRC_ALPHA,
};

static const D3D11_BLEND d3dDestBlend[] =
{
    D3D11_BLEND_ZERO,
    D3D11_BLEND_ONE,
    D3D11_BLEND_ZERO,
    D3D11_BLEND_INV_SRC_ALPHA,
    D3D11_BLEND_ONE,
    D3D11_BLEND_INV_SRC_ALPHA,
    D3D11_BLEND_DEST_ALPHA,
    D3D11_BLEND_ONE,
    D3D11_BLEND_ONE
};

static const D3D11_BLEND_OP d3dBlendOp[] =
{
    D3D11_BLEND_OP_ADD,
    D3D11_BLEND_OP_ADD,
    D3D11_BLEND_OP_ADD,
    D3D11_BLEND_OP_ADD,
    D3D11_BLEND_OP_ADD,
    D3D11_BLEND_OP_ADD,
    D3D11_BLEND_OP_ADD,
    D3D11_BLEND_OP_REV_SUBTRACT,
    D3D11_BLEND_OP_REV_SUBTRACT
};

static const D3D11_STENCIL_OP d3dStencilOp[] =
{
    D3D11_STENCIL_OP_KEEP,
    D3D11_STENCIL_OP_ZERO,
    D3D11_STENCIL_OP_REPLACE,
    D3D11_STENCIL_OP_INCR,
    D3D11_STENCIL_OP_DECR
};

static const D3D11_CULL_MODE d3dCullMode[] =
{
    D3D11_CULL_NONE,
    D3D11_CULL_BACK,
    D3D11_CULL_FRONT
};

static const D3D11_FILL_MODE d3dFillMode[] =
{
    D3D11_FILL_SOLID,
    D3D11_FILL_WIREFRAME,
    D3D11_FILL_WIREFRAME // Point fill mode not supported
};

static unsigned GetD3DColor(const Color& color)
{
    unsigned r = (unsigned)(Clamp(color.r_ * 255.0f, 0.0f, 255.0f));
    unsigned g = (unsigned)(Clamp(color.g_ * 255.0f, 0.0f, 255.0f));
    unsigned b = (unsigned)(Clamp(color.b_ * 255.0f, 0.0f, 255.0f));
    unsigned a = (unsigned)(Clamp(color.a_ * 255.0f, 0.0f, 255.0f));
    return (((a) & 0xff) << 24) | (((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff);
}

static void GetD3DPrimitiveType(unsigned elementCount, PrimitiveType type, unsigned& primitiveCount,
    D3D_PRIMITIVE_TOPOLOGY& d3dPrimitiveType)
{
    switch (type)
    {
    case TRIANGLE_LIST:
        primitiveCount = elementCount / 3;
        d3dPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        break;

    case LINE_LIST:
        primitiveCount = elementCount / 2;
        d3dPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
        break;

    case POINT_LIST:
        primitiveCount = elementCount;
        d3dPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
        break;

    case TRIANGLE_STRIP:
        primitiveCount = elementCount - 2;
        d3dPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
        break;

    case LINE_STRIP:
        primitiveCount = elementCount - 1;
        d3dPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
        break;

    case TRIANGLE_FAN:
        // Triangle fan is not supported on D3D11
        primitiveCount = 0;
        d3dPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
        break;
    }
}

static HWND GetWindowHandle(SDL_Window* window)
{
    SDL_SysWMinfo sysInfo;

    SDL_VERSION(&sysInfo.version);
    SDL_GetWindowWMInfo(window, &sysInfo);
    return sysInfo.info.win.window;
}

const Vector2 Graphics::pixelUVOffset(0.0f, 0.0f);

Graphics::Graphics(Context* context) :
    Object(context),
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
    vsync_(false),
    tripleBuffer_(false),
    flushGPU_(false),
    sRGB_(false),
    lightPrepassSupport_(false),
    deferredSupport_(false),
    instancingSupport_(false),
    sRGBSupport_(false),
    sRGBWriteSupport_(false),
    numPrimitives_(0),
    numBatches_(0),
    maxScratchBufferRequest_(0),
    defaultTextureFilterMode_(FILTER_TRILINEAR),
    shaderProgram_(0),
    shaderPath_("Shaders/HLSL/"),
    shaderExtension_(".hlsl"),
    orientations_("LandscapeLeft LandscapeRight"),
    apiName_("D3D11")
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
    {
        MutexLock lock(gpuObjectMutex_);

        // Release all GPU objects that still exist
        for (PODVector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
            (*i)->Release();
        gpuObjects_.Clear();
    }

    vertexDeclarations_.Clear();
    constantBuffers_.Clear();

    for (HashMap<unsigned, ID3D11BlendState*>::Iterator i = impl_->blendStates_.Begin(); i != impl_->blendStates_.End(); ++i)
    {
        if (i->second_)
            i->second_->Release();
    }
    impl_->blendStates_.Clear();

    for (HashMap<unsigned, ID3D11DepthStencilState*>::Iterator i = impl_->depthStates_.Begin(); i != impl_->depthStates_.End(); ++i)
    {
        if (i->second_)
            i->second_->Release();
    }
    impl_->depthStates_.Clear();

    for (HashMap<unsigned, ID3D11RasterizerState*>::Iterator i = impl_->rasterizerStates_.Begin();
         i != impl_->rasterizerStates_.End(); ++i)
    {
        if (i->second_)
            i->second_->Release();
    }
    impl_->rasterizerStates_.Clear();

    if (impl_->defaultRenderTargetView_)
    {
        impl_->defaultRenderTargetView_->Release();
        impl_->defaultRenderTargetView_ = 0;
    }
    if (impl_->defaultDepthStencilView_)
    {
        impl_->defaultDepthStencilView_->Release();
        impl_->defaultDepthStencilView_ = 0;
    }
    if (impl_->defaultDepthTexture_)
    {
        impl_->defaultDepthTexture_->Release();
        impl_->defaultDepthTexture_ = 0;
    }
    if (impl_->resolveTexture_)
    {
        impl_->resolveTexture_->Release();
        impl_->resolveTexture_ = 0;
    }
    if (impl_->swapChain_)
    {
        impl_->swapChain_->Release();
        impl_->swapChain_ = 0;
    }
    if (impl_->deviceContext_)
    {
        impl_->deviceContext_->Release();
        impl_->deviceContext_ = 0;
    }
    if (impl_->device_)
    {
        impl_->device_->Release();
        impl_->device_ = 0;
    }
    if (impl_->window_)
    {
        SDL_ShowCursor(SDL_TRUE);
        SDL_DestroyWindow(impl_->window_);
        impl_->window_ = 0;
    }

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
        position_ = position; // Sets as initial position for OpenWindow()
}

void Graphics::SetWindowPosition(int x, int y)
{
    SetWindowPosition(IntVector2(x, y));
}

bool Graphics::SetMode(int width, int height, bool fullscreen, bool borderless, bool resizable, bool vsync, bool tripleBuffer,
    int multiSample)
{
    URHO3D_PROFILE(SetScreenMode);

    bool maximize = false;

    // Find out the full screen mode display format (match desktop color depth)
    SDL_DisplayMode mode;
    SDL_GetDesktopDisplayMode(0, &mode);
    DXGI_FORMAT fullscreenFormat = SDL_BITSPERPIXEL(mode.format) == 16 ? DXGI_FORMAT_B5G6R5_UNORM : DXGI_FORMAT_R8G8B8A8_UNORM;

    // If zero dimensions in windowed mode, set windowed mode to maximize and set a predefined default restored window size. If zero in fullscreen, use desktop mode
    if (!width || !height)
    {
        if (fullscreen || borderless)
        {
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

    // Fullscreen or Borderless can not be resizable
    if (fullscreen || borderless)
        resizable = false;

    // Borderless cannot be fullscreen, they are mutually exclusive
    if (borderless)
        fullscreen = false;

    // If nothing changes, do not reset the device
    if (width == width_ && height == height_ && fullscreen == fullscreen_ && borderless == borderless_ && resizable == resizable_ &&
        vsync == vsync_ && tripleBuffer == tripleBuffer_ && multiSample == multiSample_)
        return true;

    SDL_SetHint(SDL_HINT_ORIENTATIONS, orientations_.CString());

    if (!impl_->window_)
    {
        if (!OpenWindow(width, height, resizable, borderless))
            return false;
    }

    // Check fullscreen mode validity. Use a closest match if not found
    if (fullscreen)
    {
        PODVector<IntVector2> resolutions = GetResolutions();
        if (resolutions.Size())
        {
            unsigned best = 0;
            unsigned bestError = M_MAX_UNSIGNED;

            for (unsigned i = 0; i < resolutions.Size(); ++i)
            {
                unsigned error = (unsigned)(Abs(resolutions[i].x_ - width) + Abs(resolutions[i].y_ - height));
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

    AdjustWindow(width, height, fullscreen, borderless);

    if (maximize)
    {
        Maximize();
        SDL_GetWindowSize(impl_->window_, &width, &height);
    }

    if (!impl_->device_ || multiSample_ != multiSample)
        CreateDevice(width, height, multiSample);
    UpdateSwapChain(width, height);

    fullscreen_ = fullscreen;
    borderless_ = borderless;
    resizable_ = resizable;
    vsync_ = vsync;
    tripleBuffer_ = tripleBuffer;

    // Clear the initial window contents to black
    Clear(CLEAR_COLOR);
    impl_->swapChain_->Present(0, 0);

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
    eventData[P_RESIZABLE] = resizable_;
    eventData[P_BORDERLESS] = borderless_;
    SendEvent(E_SCREENMODE, eventData);

    return true;
}

bool Graphics::SetMode(int width, int height)
{
    return SetMode(width, height, fullscreen_, borderless_, resizable_, vsync_, tripleBuffer_, multiSample_);
}

void Graphics::SetSRGB(bool enable)
{
    bool newEnable = enable && sRGBWriteSupport_;
    if (newEnable != sRGB_)
    {
        sRGB_ = newEnable;
        if (impl_->swapChain_)
        {
            // Recreate swap chain for the new backbuffer format
            CreateDevice(width_, height_, multiSample_);
            UpdateSwapChain(width_, height_);
        }
    }
}

void Graphics::SetFlushGPU(bool enable)
{
    flushGPU_ = enable;

    if (impl_->device_)
    {
        IDXGIDevice1* dxgiDevice;
        impl_->device_->QueryInterface(IID_IDXGIDevice1, (void**)&dxgiDevice);
        if (dxgiDevice)
        {
            dxgiDevice->SetMaximumFrameLatency(enable ? 1 : 3);
            dxgiDevice->Release();
        }
    }
}

void Graphics::SetOrientations(const String& orientations)
{
    orientations_ = orientations.Trimmed();
    SDL_SetHint(SDL_HINT_ORIENTATIONS, orientations_.CString());
}

bool Graphics::ToggleFullscreen()
{
    return SetMode(width_, height_, !fullscreen_, borderless_, resizable_, vsync_, tripleBuffer_, multiSample_);
}

void Graphics::Close()
{
    if (impl_->window_)
    {
        SDL_ShowCursor(SDL_TRUE);
        SDL_DestroyWindow(impl_->window_);
        impl_->window_ = 0;
    }
}

bool Graphics::TakeScreenShot(Image& destImage)
{
    URHO3D_PROFILE(TakeScreenShot);

    if (!impl_->device_)
        return false;

    D3D11_TEXTURE2D_DESC textureDesc;
    memset(&textureDesc, 0, sizeof textureDesc);
    textureDesc.Width = (UINT)width_;
    textureDesc.Height = (UINT)height_;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D11_USAGE_STAGING;
    textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

    ID3D11Texture2D* stagingTexture = 0;
    impl_->device_->CreateTexture2D(&textureDesc, 0, &stagingTexture);
    if (!stagingTexture)
    {
        URHO3D_LOGERROR("Could not create staging texture for screenshot");
        return false;
    }

    ID3D11Resource* source = 0;
    impl_->defaultRenderTargetView_->GetResource(&source);

    if (multiSample_ > 1)
    {
        // If backbuffer is multisampled, need another DEFAULT usage texture to resolve the data to first
        CreateResolveTexture();

        if (!impl_->resolveTexture_)
        {
            URHO3D_LOGERROR("Could not create intermediate texture for multisampled screenshot");
            stagingTexture->Release();
            source->Release();
            return false;
        }

        impl_->deviceContext_->ResolveSubresource(impl_->resolveTexture_, 0, source, 0, DXGI_FORMAT_R8G8B8A8_UNORM);
        impl_->deviceContext_->CopyResource(stagingTexture, impl_->resolveTexture_);
    }
    else
        impl_->deviceContext_->CopyResource(stagingTexture, source);

    source->Release();

    D3D11_MAPPED_SUBRESOURCE mappedData;
    mappedData.pData = 0;
    impl_->deviceContext_->Map(stagingTexture, 0, D3D11_MAP_READ, 0, &mappedData);

    destImage.SetSize(width_, height_, 3);
    unsigned char* destData = destImage.GetData();
    if (mappedData.pData)
    {
        for (int y = 0; y < height_; ++y)
        {
            unsigned char* src = (unsigned char*)mappedData.pData + y * mappedData.RowPitch;
            for (int x = 0; x < width_; ++x)
            {
                *destData++ = *src++;
                *destData++ = *src++;
                *destData++ = *src++;
                ++src;
            }
        }
        impl_->deviceContext_->Unmap(stagingTexture, 0);
        stagingTexture->Release();
        return true;
    }
    else
    {
        URHO3D_LOGERROR("Could not map staging texture for screenshot");
        stagingTexture->Release();
        return false;
    }
}

bool Graphics::BeginFrame()
{
    if (!IsInitialized())
        return false;

    // If using an external window, check it for size changes, and reset screen mode if necessary
    if (externalWindow_)
    {
        int width, height;

        SDL_GetWindowSize(impl_->window_, &width, &height);
        if (width != width_ || height != height_)
            SetMode(width, height);
    }
    else
    {
        // To prevent a loop of endless device loss and flicker, do not attempt to render when in fullscreen
        // and the window is minimized
        if (fullscreen_ && (SDL_GetWindowFlags(impl_->window_) & SDL_WINDOW_MINIMIZED))
            return false;
    }

    // Set default rendertarget and depth buffer
    ResetRenderTargets();

    // Cleanup textures from previous frame
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        SetTexture(i, 0);

    numPrimitives_ = 0;
    numBatches_ = 0;

    SendEvent(E_BEGINRENDERING);

    return true;
}

void Graphics::EndFrame()
{
    if (!IsInitialized())
        return;

    {
        URHO3D_PROFILE(Present);

        SendEvent(E_ENDRENDERING);

        impl_->swapChain_->Present(vsync_ ? 1 : 0, 0);
    }

    // Clean up too large scratch buffers
    CleanupScratchBuffers();
}

void Graphics::Clear(unsigned flags, const Color& color, float depth, unsigned stencil)
{
    IntVector2 rtSize = GetRenderTargetDimensions();

    bool oldColorWrite = colorWrite_;
    bool oldDepthWrite = depthWrite_;

    // D3D11 clear always clears the whole target regardless of viewport or scissor test settings
    // Emulate partial clear by rendering a quad
    if (!viewport_.left_ && !viewport_.top_ && viewport_.right_ == rtSize.x_ && viewport_.bottom_ == rtSize.y_)
    {
        // Make sure we use the read-write version of the depth stencil
        SetDepthWrite(true);
        PrepareDraw();

        if ((flags & CLEAR_COLOR) && impl_->renderTargetViews_[0])
            impl_->deviceContext_->ClearRenderTargetView(impl_->renderTargetViews_[0], color.Data());

        if ((flags & (CLEAR_DEPTH | CLEAR_STENCIL)) && impl_->depthStencilView_)
        {
            unsigned depthClearFlags = 0;
            if (flags & CLEAR_DEPTH)
                depthClearFlags |= D3D11_CLEAR_DEPTH;
            if (flags & CLEAR_STENCIL)
                depthClearFlags |= D3D11_CLEAR_STENCIL;
            impl_->deviceContext_->ClearDepthStencilView(impl_->depthStencilView_, depthClearFlags, depth, (UINT8)stencil);
        }
    }
    else
    {
        Renderer* renderer = GetSubsystem<Renderer>();
        if (!renderer)
            return;

        Geometry* geometry = renderer->GetQuadGeometry();

        Matrix3x4 model = Matrix3x4::IDENTITY;
        Matrix4 projection = Matrix4::IDENTITY;
        model.m23_ = Clamp(depth, 0.0f, 1.0f);

        SetBlendMode(BLEND_REPLACE);
        SetColorWrite((flags & CLEAR_COLOR) != 0);
        SetCullMode(CULL_NONE);
        SetDepthTest(CMP_ALWAYS);
        SetDepthWrite((flags & CLEAR_DEPTH) != 0);
        SetFillMode(FILL_SOLID);
        SetScissorTest(false);
        SetStencilTest((flags & CLEAR_STENCIL) != 0, CMP_ALWAYS, OP_REF, OP_KEEP, OP_KEEP, stencil);
        SetShaders(GetShader(VS, "ClearFramebuffer"), GetShader(PS, "ClearFramebuffer"));
        SetShaderParameter(VSP_MODEL, model);
        SetShaderParameter(VSP_VIEWPROJ, projection);
        SetShaderParameter(PSP_MATDIFFCOLOR, color);

        geometry->Draw(this);

        SetStencilTest(false);
        ClearParameterSources();
    }

    // Restore color & depth write state now
    SetColorWrite(oldColorWrite);
    SetDepthWrite(oldDepthWrite);
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

    D3D11_BOX srcBox;
    srcBox.left = Clamp(vpCopy.left_, 0, width_);
    srcBox.top = Clamp(vpCopy.top_, 0, height_);
    srcBox.right = Clamp(vpCopy.right_, 0, width_);
    srcBox.bottom = Clamp(vpCopy.bottom_, 0, height_);
    srcBox.front = 0;
    srcBox.back = 1;

    ID3D11Resource* source = 0;
    bool resolve = multiSample_ > 1;
    impl_->defaultRenderTargetView_->GetResource(&source);

    if (!resolve)
    {
        if (!srcBox.left && !srcBox.top && srcBox.right == width_ && srcBox.bottom == height_)
            impl_->deviceContext_->CopyResource((ID3D11Resource*)destination->GetGPUObject(), source);
        else
            impl_->deviceContext_->CopySubresourceRegion((ID3D11Resource*)destination->GetGPUObject(), 0, 0, 0, 0, source, 0, &srcBox);
    }
    else
    {
        if (!srcBox.left && !srcBox.top && srcBox.right == width_ && srcBox.bottom == height_)
        {
            impl_->deviceContext_->ResolveSubresource((ID3D11Resource*)destination->GetGPUObject(), 0, source, 0, (DXGI_FORMAT)
                destination->GetFormat());
        }
        else
        {
            CreateResolveTexture();

            if (impl_->resolveTexture_)
            {
                impl_->deviceContext_->ResolveSubresource(impl_->resolveTexture_, 0, source, 0, DXGI_FORMAT_R8G8B8A8_UNORM);
                impl_->deviceContext_->CopySubresourceRegion((ID3D11Resource*)destination->GetGPUObject(), 0, 0, 0, 0, impl_->resolveTexture_, 0, &srcBox);
            }
        }
    }

    source->Release();

    return true;
}

void Graphics::Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount)
{
    if (!vertexCount || !shaderProgram_)
        return;

    PrepareDraw();

    unsigned primitiveCount;
    D3D_PRIMITIVE_TOPOLOGY d3dPrimitiveType;

    if (fillMode_ == FILL_POINT)
        type = POINT_LIST;

    GetD3DPrimitiveType(vertexCount, type, primitiveCount, d3dPrimitiveType);
    if (d3dPrimitiveType != primitiveType_)
    {
        impl_->deviceContext_->IASetPrimitiveTopology(d3dPrimitiveType);
        primitiveType_ = d3dPrimitiveType;
    }
    impl_->deviceContext_->Draw(vertexCount, vertexStart);

    numPrimitives_ += primitiveCount;
    ++numBatches_;
}

void Graphics::Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount)
{
    if (!vertexCount || !shaderProgram_)
        return;

    PrepareDraw();

    unsigned primitiveCount;
    D3D_PRIMITIVE_TOPOLOGY d3dPrimitiveType;

    if (fillMode_ == FILL_POINT)
        type = POINT_LIST;

    GetD3DPrimitiveType(indexCount, type, primitiveCount, d3dPrimitiveType);
    if (d3dPrimitiveType != primitiveType_)
    {
        impl_->deviceContext_->IASetPrimitiveTopology(d3dPrimitiveType);
        primitiveType_ = d3dPrimitiveType;
    }
    impl_->deviceContext_->DrawIndexed(indexCount, indexStart, 0);

    numPrimitives_ += primitiveCount;
    ++numBatches_;
}

void Graphics::DrawInstanced(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount,
    unsigned instanceCount)
{
    if (!indexCount || !instanceCount || !shaderProgram_)
        return;

    PrepareDraw();

    unsigned primitiveCount;
    D3D_PRIMITIVE_TOPOLOGY d3dPrimitiveType;

    if (fillMode_ == FILL_POINT)
        type = POINT_LIST;

    GetD3DPrimitiveType(indexCount, type, primitiveCount, d3dPrimitiveType);
    if (d3dPrimitiveType != primitiveType_)
    {
        impl_->deviceContext_->IASetPrimitiveTopology(d3dPrimitiveType);
        primitiveType_ = d3dPrimitiveType;
    }
    impl_->deviceContext_->DrawIndexedInstanced(indexCount, instanceCount, indexStart, 0, 0);

    numPrimitives_ += instanceCount * primitiveCount;
    ++numBatches_;
}

void Graphics::SetVertexBuffer(VertexBuffer* buffer)
{
    // Note: this is not multi-instance safe
    static PODVector<VertexBuffer*> vertexBuffers(1);
    static PODVector<unsigned> elementMasks(1);
    vertexBuffers[0] = buffer;
    elementMasks[0] = MASK_DEFAULT;
    SetVertexBuffers(vertexBuffers, elementMasks);
}

bool Graphics::SetVertexBuffers(const PODVector<VertexBuffer*>& buffers, const PODVector<unsigned>& elementMasks,
    unsigned instanceOffset)
{
    if (buffers.Size() > MAX_VERTEX_STREAMS)
    {
        URHO3D_LOGERROR("Too many vertex buffers");
        return false;
    }
    if (buffers.Size() != elementMasks.Size())
    {
        URHO3D_LOGERROR("Amount of element masks and vertex buffers does not match");
        return false;
    }

    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        VertexBuffer* buffer = 0;
        bool changed = false;

        buffer = i < buffers.Size() ? buffers[i] : 0;
        if (buffer)
        {
            unsigned elementMask = buffer->GetElementMask() & elementMasks[i];
            unsigned offset = (elementMask & MASK_INSTANCEMATRIX1) ? instanceOffset * buffer->GetVertexSize() : 0;

            if (buffer != vertexBuffers_[i] || elementMask != elementMasks_[i] || offset != impl_->vertexOffsets_[i])
            {
                vertexBuffers_[i] = buffer;
                elementMasks_[i] = elementMask;
                impl_->vertexBuffers_[i] = (ID3D11Buffer*)buffer->GetGPUObject();
                impl_->vertexSizes_[i] = buffer->GetVertexSize();
                impl_->vertexOffsets_[i] = offset;
                changed = true;
            }
        }
        else if (vertexBuffers_[i])
        {
            vertexBuffers_[i] = 0;
            elementMasks_[i] = 0;
            impl_->vertexBuffers_[i] = 0;
            impl_->vertexSizes_[i] = 0;
            impl_->vertexOffsets_[i] = 0;
            changed = true;
        }

        if (changed)
        {
            vertexDeclarationDirty_ = true;

            if (firstDirtyVB_ == M_MAX_UNSIGNED)
                firstDirtyVB_ = lastDirtyVB_ = i;
            else
            {
                if (i < firstDirtyVB_)
                    firstDirtyVB_ = i;
                if (i > lastDirtyVB_)
                    lastDirtyVB_ = i;
            }
        }
    }

    return true;
}

bool Graphics::SetVertexBuffers(const Vector<SharedPtr<VertexBuffer> >& buffers, const PODVector<unsigned>& elementMasks,
    unsigned instanceOffset)
{
    return SetVertexBuffers(reinterpret_cast<const PODVector<VertexBuffer*>&>(buffers), elementMasks, instanceOffset);
}

void Graphics::SetIndexBuffer(IndexBuffer* buffer)
{
    if (buffer != indexBuffer_)
    {
        if (buffer)
            impl_->deviceContext_->IASetIndexBuffer((ID3D11Buffer*)buffer->GetGPUObject(),
                buffer->GetIndexSize() == sizeof(unsigned short) ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, 0);
        else
            impl_->deviceContext_->IASetIndexBuffer(0, DXGI_FORMAT_UNKNOWN, 0);

        indexBuffer_ = buffer;
    }
}

void Graphics::SetShaders(ShaderVariation* vs, ShaderVariation* ps)
{
    // Switch to the clip plane variations if necessary
    /// \todo Causes overhead and string manipulation per drawcall
    if (useClipPlane_)
    {
        if (vs)
            vs = vs->GetOwner()->GetVariation(VS, vs->GetDefines() + " CLIPPLANE");
        if (ps)
            ps = ps->GetOwner()->GetVariation(PS, ps->GetDefines() + " CLIPPLANE");
    }

    if (vs == vertexShader_ && ps == pixelShader_)
        return;

    if (vs != vertexShader_)
    {
        // Create the shader now if not yet created. If already attempted, do not retry
        if (vs && !vs->GetGPUObject())
        {
            if (vs->GetCompilerOutput().Empty())
            {
                URHO3D_PROFILE(CompileVertexShader);

                bool success = vs->Create();
                if (!success)
                {
                    URHO3D_LOGERROR("Failed to compile vertex shader " + vs->GetFullName() + ":\n" + vs->GetCompilerOutput());
                    vs = 0;
                }
            }
            else
                vs = 0;
        }

        impl_->deviceContext_->VSSetShader((ID3D11VertexShader*)(vs ? vs->GetGPUObject() : 0), 0, 0);
        vertexShader_ = vs;
        vertexDeclarationDirty_ = true;
    }

    if (ps != pixelShader_)
    {
        if (ps && !ps->GetGPUObject())
        {
            if (ps->GetCompilerOutput().Empty())
            {
                URHO3D_PROFILE(CompilePixelShader);

                bool success = ps->Create();
                if (!success)
                {
                    URHO3D_LOGERROR("Failed to compile pixel shader " + ps->GetFullName() + ":\n" + ps->GetCompilerOutput());
                    ps = 0;
                }
            }
            else
                ps = 0;
        }

        impl_->deviceContext_->PSSetShader((ID3D11PixelShader*)(ps ? ps->GetGPUObject() : 0), 0, 0);
        pixelShader_ = ps;
    }

    // Update current shader parameters & constant buffers
    if (vertexShader_ && pixelShader_)
    {
        Pair<ShaderVariation*, ShaderVariation*> key = MakePair(vertexShader_, pixelShader_);
        ShaderProgramMap::Iterator i = shaderPrograms_.Find(key);
        if (i != shaderPrograms_.End())
            shaderProgram_ = i->second_.Get();
        else
        {
            ShaderProgram* newProgram = shaderPrograms_[key] = new ShaderProgram(this, vertexShader_, pixelShader_);
            shaderProgram_ = newProgram;
        }

        bool vsBuffersChanged = false;
        bool psBuffersChanged = false;

        for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
        {
            ID3D11Buffer* vsBuffer = shaderProgram_->vsConstantBuffers_[i] ? (ID3D11Buffer*)shaderProgram_->vsConstantBuffers_[i]->
                GetGPUObject() : 0;
            if (vsBuffer != impl_->constantBuffers_[VS][i])
            {
                impl_->constantBuffers_[VS][i] = vsBuffer;
                shaderParameterSources_[i] = (const void*)M_MAX_UNSIGNED;
                vsBuffersChanged = true;
            }

            ID3D11Buffer* psBuffer = shaderProgram_->psConstantBuffers_[i] ? (ID3D11Buffer*)shaderProgram_->psConstantBuffers_[i]->
                GetGPUObject() : 0;
            if (psBuffer != impl_->constantBuffers_[PS][i])
            {
                impl_->constantBuffers_[PS][i] = psBuffer;
                shaderParameterSources_[i] = (const void*)M_MAX_UNSIGNED;
                psBuffersChanged = true;
            }
        }

        if (vsBuffersChanged)
            impl_->deviceContext_->VSSetConstantBuffers(0, MAX_SHADER_PARAMETER_GROUPS, &impl_->constantBuffers_[VS][0]);
        if (psBuffersChanged)
            impl_->deviceContext_->PSSetConstantBuffers(0, MAX_SHADER_PARAMETER_GROUPS, &impl_->constantBuffers_[PS][0]);
    }
    else
        shaderProgram_ = 0;

    // Store shader combination if shader dumping in progress
    if (shaderPrecache_)
        shaderPrecache_->StoreShaders(vertexShader_, pixelShader_);

    // Update clip plane parameter if necessary
    if (useClipPlane_)
        SetShaderParameter(VSP_CLIPPLANE, clipPlane_);
}

void Graphics::SetShaderParameter(StringHash param, const float* data, unsigned count)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!shaderProgram_ || (i = shaderProgram_->parameters_.Find(param)) == shaderProgram_->parameters_.End())
        return;

    ConstantBuffer* buffer = i->second_.bufferPtr_;
    if (!buffer->IsDirty())
        dirtyConstantBuffers_.Push(buffer);
    buffer->SetParameter(i->second_.offset_, (unsigned)(count * sizeof(float)), data);
}

void Graphics::SetShaderParameter(StringHash param, float value)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!shaderProgram_ || (i = shaderProgram_->parameters_.Find(param)) == shaderProgram_->parameters_.End())
        return;

    ConstantBuffer* buffer = i->second_.bufferPtr_;
    if (!buffer->IsDirty())
        dirtyConstantBuffers_.Push(buffer);
    buffer->SetParameter(i->second_.offset_, sizeof(float), &value);
}

void Graphics::SetShaderParameter(StringHash param, bool value)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!shaderProgram_ || (i = shaderProgram_->parameters_.Find(param)) == shaderProgram_->parameters_.End())
        return;

    ConstantBuffer* buffer = i->second_.bufferPtr_;
    if (!buffer->IsDirty())
        dirtyConstantBuffers_.Push(buffer);
    buffer->SetParameter(i->second_.offset_, sizeof(bool), &value);
}

void Graphics::SetShaderParameter(StringHash param, const Color& color)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!shaderProgram_ || (i = shaderProgram_->parameters_.Find(param)) == shaderProgram_->parameters_.End())
        return;

    ConstantBuffer* buffer = i->second_.bufferPtr_;
    if (!buffer->IsDirty())
        dirtyConstantBuffers_.Push(buffer);
    buffer->SetParameter(i->second_.offset_, sizeof(Color), &color);
}

void Graphics::SetShaderParameter(StringHash param, const Vector2& vector)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!shaderProgram_ || (i = shaderProgram_->parameters_.Find(param)) == shaderProgram_->parameters_.End())
        return;

    ConstantBuffer* buffer = i->second_.bufferPtr_;
    if (!buffer->IsDirty())
        dirtyConstantBuffers_.Push(buffer);
    buffer->SetParameter(i->second_.offset_, sizeof(Vector2), &vector);
}

void Graphics::SetShaderParameter(StringHash param, const Matrix3& matrix)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!shaderProgram_ || (i = shaderProgram_->parameters_.Find(param)) == shaderProgram_->parameters_.End())
        return;

    ConstantBuffer* buffer = i->second_.bufferPtr_;
    if (!buffer->IsDirty())
        dirtyConstantBuffers_.Push(buffer);
    buffer->SetVector3ArrayParameter(i->second_.offset_, 3, &matrix);
}

void Graphics::SetShaderParameter(StringHash param, const Vector3& vector)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!shaderProgram_ || (i = shaderProgram_->parameters_.Find(param)) == shaderProgram_->parameters_.End())
        return;

    ConstantBuffer* buffer = i->second_.bufferPtr_;
    if (!buffer->IsDirty())
        dirtyConstantBuffers_.Push(buffer);
    buffer->SetParameter(i->second_.offset_, sizeof(Vector3), &vector);
}

void Graphics::SetShaderParameter(StringHash param, const Matrix4& matrix)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!shaderProgram_ || (i = shaderProgram_->parameters_.Find(param)) == shaderProgram_->parameters_.End())
        return;

    ConstantBuffer* buffer = i->second_.bufferPtr_;
    if (!buffer->IsDirty())
        dirtyConstantBuffers_.Push(buffer);
    buffer->SetParameter(i->second_.offset_, sizeof(Matrix4), &matrix);
}

void Graphics::SetShaderParameter(StringHash param, const Vector4& vector)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!shaderProgram_ || (i = shaderProgram_->parameters_.Find(param)) == shaderProgram_->parameters_.End())
        return;

    ConstantBuffer* buffer = i->second_.bufferPtr_;
    if (!buffer->IsDirty())
        dirtyConstantBuffers_.Push(buffer);
    buffer->SetParameter(i->second_.offset_, sizeof(Vector4), &vector);
}

void Graphics::SetShaderParameter(StringHash param, const Matrix3x4& matrix)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!shaderProgram_ || (i = shaderProgram_->parameters_.Find(param)) == shaderProgram_->parameters_.End())
        return;

    ConstantBuffer* buffer = i->second_.bufferPtr_;
    if (!buffer->IsDirty())
        dirtyConstantBuffers_.Push(buffer);
    buffer->SetParameter(i->second_.offset_, sizeof(Matrix3x4), &matrix);
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

    default:
        // Unsupported parameter type, do nothing
        break;
    }
}

bool Graphics::NeedParameterUpdate(ShaderParameterGroup group, const void* source)
{
    if ((unsigned)(size_t)shaderParameterSources_[group] == M_MAX_UNSIGNED || shaderParameterSources_[group] != source)
    {
        shaderParameterSources_[group] = source;
        return true;
    }
    else
        return false;
}

bool Graphics::HasShaderParameter(StringHash param)
{
    return shaderProgram_ && shaderProgram_->parameters_.Find(param) != shaderProgram_->parameters_.End();
}

bool Graphics::HasTextureUnit(TextureUnit unit)
{
    return (vertexShader_ && vertexShader_->HasTextureUnit(unit)) || (pixelShader_ && pixelShader_->HasTextureUnit(unit));
}

void Graphics::ClearParameterSource(ShaderParameterGroup group)
{
    shaderParameterSources_[group] = (const void*)M_MAX_UNSIGNED;
}

void Graphics::ClearParameterSources()
{
    for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
        shaderParameterSources_[i] = (const void*)M_MAX_UNSIGNED;
}

void Graphics::ClearTransformSources()
{
    shaderParameterSources_[SP_CAMERA] = (const void*)M_MAX_UNSIGNED;
    shaderParameterSources_[SP_OBJECT] = (const void*)M_MAX_UNSIGNED;
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

    if (texture && texture->GetParametersDirty())
    {
        texture->UpdateParameters();
        textures_[index] = 0; // Force reassign
    }

    if (texture != textures_[index])
    {
        if (firstDirtyTexture_ == M_MAX_UNSIGNED)
            firstDirtyTexture_ = lastDirtyTexture_ = index;
        else
        {
            if (index < firstDirtyTexture_)
                firstDirtyTexture_ = index;
            if (index > lastDirtyTexture_)
                lastDirtyTexture_ = index;
        }

        textures_[index] = texture;
        impl_->shaderResourceViews_[index] = texture ? (ID3D11ShaderResourceView*)texture->GetShaderResourceView() : 0;
        impl_->samplers_[index] = texture ? (ID3D11SamplerState*)texture->GetSampler() : 0;
        texturesDirty_ = true;
    }
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
        renderTargetsDirty_ = true;

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
    if (depthStencil != depthStencil_)
    {
        depthStencil_ = depthStencil;
        renderTargetsDirty_ = true;
    }
}

void Graphics::SetDepthStencil(Texture2D* texture)
{
    RenderSurface* depthStencil = 0;
    if (texture)
        depthStencil = texture->GetRenderSurface();

    SetDepthStencil(depthStencil);
    // Constant depth bias depends on the bitdepth
    rasterizerStateDirty_ = true;
}

void Graphics::SetViewport(const IntRect& rect)
{
    IntVector2 size = GetRenderTargetDimensions();

    IntRect rectCopy = rect;

    if (rectCopy.right_ <= rectCopy.left_)
        rectCopy.right_ = rectCopy.left_ + 1;
    if (rectCopy.bottom_ <= rectCopy.top_)
        rectCopy.bottom_ = rectCopy.top_ + 1;
    rectCopy.left_ = Clamp(rectCopy.left_, 0, size.x_);
    rectCopy.top_ = Clamp(rectCopy.top_, 0, size.y_);
    rectCopy.right_ = Clamp(rectCopy.right_, 0, size.x_);
    rectCopy.bottom_ = Clamp(rectCopy.bottom_, 0, size.y_);

    static D3D11_VIEWPORT d3dViewport;
    d3dViewport.TopLeftX = (float)rectCopy.left_;
    d3dViewport.TopLeftY = (float)rectCopy.top_;
    d3dViewport.Width = (float)(rectCopy.right_ - rectCopy.left_);
    d3dViewport.Height = (float)(rectCopy.bottom_ - rectCopy.top_);
    d3dViewport.MinDepth = 0.0f;
    d3dViewport.MaxDepth = 1.0f;

    impl_->deviceContext_->RSSetViewports(1, &d3dViewport);

    viewport_ = rectCopy;

    // Disable scissor test, needs to be re-enabled by the user
    SetScissorTest(false);
}

void Graphics::SetBlendMode(BlendMode mode)
{
    if (mode != blendMode_)
    {
        blendMode_ = mode;
        blendStateDirty_ = true;
    }
}

void Graphics::SetColorWrite(bool enable)
{
    if (enable != colorWrite_)
    {
        colorWrite_ = enable;
        blendStateDirty_ = true;
    }
}

void Graphics::SetCullMode(CullMode mode)
{
    if (mode != cullMode_)
    {
        cullMode_ = mode;
        rasterizerStateDirty_ = true;
    }
}

void Graphics::SetDepthBias(float constantBias, float slopeScaledBias)
{
    if (constantBias != constantDepthBias_ || slopeScaledBias != slopeScaledDepthBias_)
    {
        constantDepthBias_ = constantBias;
        slopeScaledDepthBias_ = slopeScaledBias;
        rasterizerStateDirty_ = true;
    }
}

void Graphics::SetDepthTest(CompareMode mode)
{
    if (mode != depthTestMode_)
    {
        depthTestMode_ = mode;
        depthStateDirty_ = true;
    }
}

void Graphics::SetDepthWrite(bool enable)
{
    if (enable != depthWrite_)
    {
        depthWrite_ = enable;
        depthStateDirty_ = true;
        // Also affects whether a read-only version of depth-stencil should be bound, to allow sampling
        renderTargetsDirty_ = true;
    }
}

void Graphics::SetFillMode(FillMode mode)
{
    if (mode != fillMode_)
    {
        fillMode_ = mode;
        rasterizerStateDirty_ = true;
    }
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

        if (enable && intRect != scissorRect_)
        {
            scissorRect_ = intRect;
            scissorRectDirty_ = true;
        }
    }

    if (enable != scissorTest_)
    {
        scissorTest_ = enable;
        rasterizerStateDirty_ = true;
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

        if (enable && intRect != scissorRect_)
        {
            scissorRect_ = intRect;
            scissorRectDirty_ = true;
        }
    }

    if (enable != scissorTest_)
    {
        scissorTest_ = enable;
        rasterizerStateDirty_ = true;
    }
}

void Graphics::SetStencilTest(bool enable, CompareMode mode, StencilOp pass, StencilOp fail, StencilOp zFail, unsigned stencilRef,
    unsigned compareMask, unsigned writeMask)
{
    if (enable != stencilTest_)
    {
        stencilTest_ = enable;
        depthStateDirty_ = true;
    }

    if (enable)
    {
        if (mode != stencilTestMode_)
        {
            stencilTestMode_ = mode;
            depthStateDirty_ = true;
        }
        if (pass != stencilPass_)
        {
            stencilPass_ = pass;
            depthStateDirty_ = true;
        }
        if (fail != stencilFail_)
        {
            stencilFail_ = fail;
            depthStateDirty_ = true;
        }
        if (zFail != stencilZFail_)
        {
            stencilZFail_ = zFail;
            depthStateDirty_ = true;
        }
        if (compareMask != stencilCompareMask_)
        {
            stencilCompareMask_ = compareMask;
            depthStateDirty_ = true;
        }
        if (writeMask != stencilWriteMask_)
        {
            stencilWriteMask_ = writeMask;
            depthStateDirty_ = true;
        }
        if (stencilRef != stencilRef_)
        {
            stencilRef_ = stencilRef;
            stencilRefDirty_ = true;
            depthStateDirty_ = true;
        }
    }
}

void Graphics::SetClipPlane(bool enable, const Plane& clipPlane, const Matrix3x4& view, const Matrix4& projection)
{
    useClipPlane_ = enable;

    if (enable)
    {
        Matrix4 viewProj = projection * view;
        clipPlane_ = clipPlane.Transformed(viewProj).ToVector4();
        SetShaderParameter(VSP_CLIPPLANE, clipPlane_);
    }
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
    return impl_->window_ != 0 && impl_->GetDevice() != 0;
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

    return ret;
}

PODVector<int> Graphics::GetMultiSampleLevels() const
{
    PODVector<int> ret;
    ret.Push(1);

    if (impl_->device_)
    {
        for (unsigned i = 2; i <= 16; ++i)
        {
            unsigned levels = 0;
            impl_->device_->CheckMultisampleQualityLevels(sRGB_ ? DXGI_FORMAT_R8G8B8A8_UNORM_SRGB : DXGI_FORMAT_R8G8B8A8_UNORM,
                i, &levels);
            if (levels)
                ret.Push(i);
        }
    }

    return ret;
}

IntVector2 Graphics::GetDesktopResolution() const
{
    SDL_DisplayMode mode;
    SDL_GetDesktopDisplayMode(0, &mode);
    return IntVector2(mode.w, mode.h);
}

unsigned Graphics::GetFormat(CompressedFormat format) const
{
    switch (format)
    {
    case CF_RGBA:
        return DXGI_FORMAT_R8G8B8A8_UNORM;

    case CF_DXT1:
        return DXGI_FORMAT_BC1_UNORM;

    case CF_DXT3:
        return DXGI_FORMAT_BC2_UNORM;

    case CF_DXT5:
        return DXGI_FORMAT_BC3_UNORM;

    default:
        return 0;
    }
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
    else if (depthStencil_) // Depth-only rendering
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
    if (!impl_->device_ || !impl_->window_)
        return;

    int newWidth, newHeight;

    SDL_GetWindowSize(impl_->window_, &newWidth, &newHeight);
    if (newWidth == width_ && newHeight == height_)
        return;

    UpdateSwapChain(newWidth, newHeight);

    // Reset rendertargets and viewport for the new screen size
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
    if (!impl_->device_ || !impl_->window_ || fullscreen_)
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

            URHO3D_LOGDEBUG("Resized scratch buffer to size " + String(size));

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

    URHO3D_LOGDEBUG("Allocated scratch buffer with size " + String(size));
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

            URHO3D_LOGDEBUG("Resized scratch buffer to size " + String(maxScratchBufferRequest_));
        }
    }

    maxScratchBufferRequest_ = 0;
}

void Graphics::CleanUpShaderPrograms(ShaderVariation* variation)
{
    for (ShaderProgramMap::Iterator i = shaderPrograms_.Begin(); i != shaderPrograms_.End();)
    {
        if (i->first_.first_ == variation || i->first_.second_ == variation)
            i = shaderPrograms_.Erase(i);
        else
            ++i;
    }

    if (vertexShader_ == variation || pixelShader_ == variation)
        shaderProgram_ = 0;
}

ConstantBuffer* Graphics::GetOrCreateConstantBuffer(ShaderType type, unsigned index, unsigned size)
{
    // Ensure that different shader types and index slots get unique buffers, even if the size is same
    unsigned key = type | (index << 1) | (size << 4);
    HashMap<unsigned, SharedPtr<ConstantBuffer> >::Iterator i = constantBuffers_.Find(key);
    if (i != constantBuffers_.End())
        return i->second_.Get();
    else
    {
        SharedPtr<ConstantBuffer> newConstantBuffer(new ConstantBuffer(context_));
        newConstantBuffer->SetSize(size);
        constantBuffers_[key] = newConstantBuffer;
        return newConstantBuffer.Get();
    }
}

unsigned Graphics::GetAlphaFormat()
{
    return DXGI_FORMAT_A8_UNORM;
}

unsigned Graphics::GetLuminanceFormat()
{
    // Note: not same sampling behavior as on D3D9; need to sample the R channel only
    return DXGI_FORMAT_R8_UNORM;
}

unsigned Graphics::GetLuminanceAlphaFormat()
{
    // Note: not same sampling behavior as on D3D9; need to sample the RG channels
    return DXGI_FORMAT_R8G8_UNORM;
}

unsigned Graphics::GetRGBFormat()
{
    return DXGI_FORMAT_R8G8B8A8_UNORM;
}

unsigned Graphics::GetRGBAFormat()
{
    return DXGI_FORMAT_R8G8B8A8_UNORM;
}

unsigned Graphics::GetRGBA16Format()
{
    return DXGI_FORMAT_R16G16B16A16_UNORM;
}

unsigned Graphics::GetRGBAFloat16Format()
{
    return DXGI_FORMAT_R16G16B16A16_FLOAT;
}

unsigned Graphics::GetRGBAFloat32Format()
{
    return DXGI_FORMAT_R32G32B32A32_FLOAT;
}

unsigned Graphics::GetRG16Format()
{
    return DXGI_FORMAT_R16G16_UNORM;
}

unsigned Graphics::GetRGFloat16Format()
{
    return DXGI_FORMAT_R16G16_FLOAT;
}

unsigned Graphics::GetRGFloat32Format()
{
    return DXGI_FORMAT_R32G32_FLOAT;
}

unsigned Graphics::GetFloat16Format()
{
    return DXGI_FORMAT_R16_FLOAT;
}

unsigned Graphics::GetFloat32Format()
{
    return DXGI_FORMAT_R32_FLOAT;
}

unsigned Graphics::GetLinearDepthFormat()
{
    return DXGI_FORMAT_R32_FLOAT;
}

unsigned Graphics::GetDepthStencilFormat()
{
    return DXGI_FORMAT_R24G8_TYPELESS;
}

unsigned Graphics::GetReadableDepthFormat()
{
    return DXGI_FORMAT_R24G8_TYPELESS;
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

bool Graphics::OpenWindow(int width, int height, bool resizable, bool borderless)
{
    if (!externalWindow_)
    {
        unsigned flags = 0;
        if (resizable)
            flags |= SDL_WINDOW_RESIZABLE;
        if (borderless)
            flags |= SDL_WINDOW_BORDERLESS;

        impl_->window_ = SDL_CreateWindow(windowTitle_.CString(), position_.x_, position_.y_, width, height, flags);
    }
    else
        impl_->window_ = SDL_CreateWindowFrom(externalWindow_, 0);

    if (!impl_->window_)
    {
        URHO3D_LOGERRORF("Could not create window, root cause: '%s'", SDL_GetError());
        return false;
    }

    SDL_GetWindowPosition(impl_->window_, &position_.x_, &position_.y_);

    CreateWindowIcon();

    return true;
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

void Graphics::AdjustWindow(int& newWidth, int& newHeight, bool& newFullscreen, bool& newBorderless)
{
    if (!externalWindow_)
    {
        if (!newWidth || !newHeight)
        {
            SDL_MaximizeWindow(impl_->window_);
            SDL_GetWindowSize(impl_->window_, &newWidth, &newHeight);
        }
        else
            SDL_SetWindowSize(impl_->window_, newWidth, newHeight);

        SDL_SetWindowFullscreen(impl_->window_, newFullscreen ? SDL_TRUE : SDL_FALSE);
        SDL_SetWindowBordered(impl_->window_, newBorderless ? SDL_FALSE : SDL_TRUE);
    }
    else
    {
        // If external window, must ask its dimensions instead of trying to set them
        SDL_GetWindowSize(impl_->window_, &newWidth, &newHeight);
        newFullscreen = false;
    }
}

bool Graphics::CreateDevice(int width, int height, int multiSample)
{
    // Device needs only to be created once
    if (!impl_->device_)
    {
        D3D11CreateDevice(
            0,
            D3D_DRIVER_TYPE_HARDWARE,
            0,
            0,
            0,
            0,
            D3D11_SDK_VERSION,
            &impl_->device_,
            0,
            &impl_->deviceContext_
        );

        if (!impl_->device_ || !impl_->deviceContext_)
        {
            URHO3D_LOGERROR("Failed to create D3D11 device");
            return false;
        }

        CheckFeatureSupport();
        // Set the flush mode now as the device has been created
        SetFlushGPU(flushGPU_);
    }

    // Check that multisample level is supported
    PODVector<int> multiSampleLevels = GetMultiSampleLevels();
    if (!multiSampleLevels.Contains(multiSample))
        multiSample = 1;

    // Create swap chain. Release old if necessary
    if (impl_->swapChain_)
    {
        impl_->swapChain_->Release();
        impl_->swapChain_ = 0;
    }

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    memset(&swapChainDesc, 0, sizeof swapChainDesc);
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = (UINT)width;
    swapChainDesc.BufferDesc.Height = (UINT)height;
    swapChainDesc.BufferDesc.Format = sRGB_ ? DXGI_FORMAT_R8G8B8A8_UNORM_SRGB : DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = GetWindowHandle(impl_->window_);
    swapChainDesc.SampleDesc.Count = (UINT)multiSample;
    swapChainDesc.SampleDesc.Quality = multiSample > 1 ? 0xffffffff : 0;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    IDXGIDevice* dxgiDevice = 0;
    impl_->device_->QueryInterface(IID_IDXGIDevice, (void**)&dxgiDevice);
    IDXGIAdapter* dxgiAdapter = 0;
    dxgiDevice->GetParent(IID_IDXGIAdapter, (void**)&dxgiAdapter);
    IDXGIFactory* dxgiFactory = 0;
    dxgiAdapter->GetParent(IID_IDXGIFactory, (void**)&dxgiFactory);
    dxgiFactory->CreateSwapChain(impl_->device_, &swapChainDesc, &impl_->swapChain_);
    // After creating the swap chain, disable automatic Alt-Enter fullscreen/windowed switching
    // (the application will switch manually if it wants to)
    dxgiFactory->MakeWindowAssociation(GetWindowHandle(impl_->window_), DXGI_MWA_NO_ALT_ENTER);

    dxgiFactory->Release();
    dxgiAdapter->Release();
    dxgiDevice->Release();

    if (impl_->swapChain_)
    {
        multiSample_ = multiSample;
        return true;
    }
    else
    {
        URHO3D_LOGERROR("Failed to create D3D11 swap chain");
        return false;
    }
}

bool Graphics::UpdateSwapChain(int width, int height)
{
    bool success = true;

    ID3D11RenderTargetView* nullView = 0;
    impl_->deviceContext_->OMSetRenderTargets(1, &nullView, 0);
    if (impl_->defaultRenderTargetView_)
    {
        impl_->defaultRenderTargetView_->Release();
        impl_->defaultRenderTargetView_ = 0;
    }
    if (impl_->defaultDepthStencilView_)
    {
        impl_->defaultDepthStencilView_->Release();
        impl_->defaultDepthStencilView_ = 0;
    }
    if (impl_->defaultDepthTexture_)
    {
        impl_->defaultDepthTexture_->Release();
        impl_->defaultDepthTexture_ = 0;
    }
    if (impl_->resolveTexture_)
    {
        impl_->resolveTexture_->Release();
        impl_->resolveTexture_ = 0;
    }

    impl_->depthStencilView_ = 0;
    for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        impl_->renderTargetViews_[i] = 0;
    renderTargetsDirty_ = true;

    impl_->swapChain_->ResizeBuffers(1, (UINT)width, (UINT)height, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

    // Create default rendertarget view representing the backbuffer
    ID3D11Texture2D* backbufferTexture;
    impl_->swapChain_->GetBuffer(0, IID_ID3D11Texture2D, (void**)&backbufferTexture);
    if (backbufferTexture)
    {
        impl_->device_->CreateRenderTargetView(backbufferTexture, 0, &impl_->defaultRenderTargetView_);
        backbufferTexture->Release();
    }
    else
    {
        URHO3D_LOGERROR("Failed to get backbuffer texture");
        success = false;
    }

    // Create default depth-stencil texture and view
    D3D11_TEXTURE2D_DESC depthDesc;
    memset(&depthDesc, 0, sizeof depthDesc);
    depthDesc.Width = (UINT)width;
    depthDesc.Height = (UINT)height;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count = (UINT)multiSample_;
    depthDesc.SampleDesc.Quality = multiSample_ > 1 ? 0xffffffff : 0;
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthDesc.CPUAccessFlags = 0;
    depthDesc.MiscFlags = 0;
    impl_->device_->CreateTexture2D(&depthDesc, 0, &impl_->defaultDepthTexture_);
    if (impl_->defaultDepthTexture_)
        impl_->device_->CreateDepthStencilView(impl_->defaultDepthTexture_, 0, &impl_->defaultDepthStencilView_);
    else
    {
        URHO3D_LOGERROR("Failed to create backbuffer depth-stencil texture");
        success = false;
    }

    // Update internally held backbuffer size
    width_ = width;
    height_ = height;

    ResetRenderTargets();
    return success;
}

void Graphics::CheckFeatureSupport()
{
    lightPrepassSupport_ = true;
    deferredSupport_ = true;
    hardwareShadowSupport_ = true;
    instancingSupport_ = true;
    shadowMapFormat_ = DXGI_FORMAT_R16_TYPELESS;
    hiresShadowMapFormat_ = DXGI_FORMAT_R32_TYPELESS;
    dummyColorFormat_ = DXGI_FORMAT_UNKNOWN;
    sRGBSupport_ = true;
    sRGBWriteSupport_ = true;
}

void Graphics::ResetCachedState()
{
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        vertexBuffers_[i] = 0;
        elementMasks_[i] = 0;
        impl_->vertexBuffers_[i] = 0;
        impl_->vertexSizes_[i] = 0;
        impl_->vertexOffsets_[i] = 0;
    }

    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
    {
        textures_[i] = 0;
        impl_->shaderResourceViews_[i] = 0;
        impl_->samplers_[i] = 0;
    }

    for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
    {
        renderTargets_[i] = 0;
        impl_->renderTargetViews_[i] = 0;
    }

    for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
    {
        impl_->constantBuffers_[VS][i] = 0;
        impl_->constantBuffers_[PS][i] = 0;
    }

    depthStencil_ = 0;
    impl_->depthStencilView_ = 0;
    viewport_ = IntRect(0, 0, width_, height_);

    indexBuffer_ = 0;
    vertexDeclarationHash_ = 0;
    primitiveType_ = 0;
    vertexShader_ = 0;
    pixelShader_ = 0;
    shaderProgram_ = 0;
    blendMode_ = BLEND_REPLACE;
    textureAnisotropy_ = 1;
    colorWrite_ = true;
    cullMode_ = CULL_CCW;
    constantDepthBias_ = 0.0f;
    slopeScaledDepthBias_ = 0.0f;
    depthTestMode_ = CMP_LESSEQUAL;
    depthWrite_ = true;
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
    renderTargetsDirty_ = true;
    texturesDirty_ = true;
    vertexDeclarationDirty_ = true;
    blendStateDirty_ = true;
    depthStateDirty_ = true;
    rasterizerStateDirty_ = true;
    scissorRectDirty_ = true;
    stencilRefDirty_ = true;
    blendStateHash_ = M_MAX_UNSIGNED;
    depthStateHash_ = M_MAX_UNSIGNED;
    rasterizerStateHash_ = M_MAX_UNSIGNED;
    firstDirtyTexture_ = lastDirtyTexture_ = M_MAX_UNSIGNED;
    firstDirtyVB_ = lastDirtyVB_ = M_MAX_UNSIGNED;
    dirtyConstantBuffers_.Clear();
}

void Graphics::PrepareDraw()
{
    if (renderTargetsDirty_)
    {
        impl_->depthStencilView_ =
            depthStencil_ ? (ID3D11DepthStencilView*)depthStencil_->GetRenderTargetView() : impl_->defaultDepthStencilView_;

        // If possible, bind a read-only depth stencil view to allow reading depth in shader
        if (!depthWrite_ && depthStencil_)
            impl_->depthStencilView_ = (ID3D11DepthStencilView*)depthStencil_->GetReadOnlyView();

        for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
            impl_->renderTargetViews_[i] =
                renderTargets_[i] ? (ID3D11RenderTargetView*)renderTargets_[i]->GetRenderTargetView() : 0;
        // If rendertarget 0 is null and not doing depth-only rendering, render to the backbuffer
        // Special case: if rendertarget 0 is null and depth stencil has same size as backbuffer, assume the intention is to do
        // backbuffer rendering with a custom depth stencil
        if (!renderTargets_[0] &&
            (!depthStencil_ || (depthStencil_ && depthStencil_->GetWidth() == width_ && depthStencil_->GetHeight() == height_)))
            impl_->renderTargetViews_[0] = impl_->defaultRenderTargetView_;

        impl_->deviceContext_->OMSetRenderTargets(MAX_RENDERTARGETS, &impl_->renderTargetViews_[0], impl_->depthStencilView_);
        renderTargetsDirty_ = false;
    }

    if (texturesDirty_ && firstDirtyTexture_ < M_MAX_UNSIGNED)
    {
        // Set also VS textures to enable vertex texture fetch to work the same way as on OpenGL
        impl_->deviceContext_->VSSetShaderResources(firstDirtyTexture_, lastDirtyTexture_ - firstDirtyTexture_ + 1,
            &impl_->shaderResourceViews_[firstDirtyTexture_]);
        impl_->deviceContext_->VSSetSamplers(firstDirtyTexture_, lastDirtyTexture_ - firstDirtyTexture_ + 1,
            &impl_->samplers_[firstDirtyTexture_]);
        impl_->deviceContext_->PSSetShaderResources(firstDirtyTexture_, lastDirtyTexture_ - firstDirtyTexture_ + 1,
            &impl_->shaderResourceViews_[firstDirtyTexture_]);
        impl_->deviceContext_->PSSetSamplers(firstDirtyTexture_, lastDirtyTexture_ - firstDirtyTexture_ + 1,
            &impl_->samplers_[firstDirtyTexture_]);

        firstDirtyTexture_ = lastDirtyTexture_ = M_MAX_UNSIGNED;
        texturesDirty_ = false;
    }

    if (vertexDeclarationDirty_ && vertexShader_ && vertexShader_->GetByteCode().Size())
    {
        if (firstDirtyVB_ < M_MAX_UNSIGNED)
        {
            impl_->deviceContext_->IASetVertexBuffers(firstDirtyVB_, lastDirtyVB_ - firstDirtyVB_ + 1,
                &impl_->vertexBuffers_[firstDirtyVB_], &impl_->vertexSizes_[firstDirtyVB_], &impl_->vertexOffsets_[firstDirtyVB_]);

            firstDirtyVB_ = lastDirtyVB_ = M_MAX_UNSIGNED;
        }

        unsigned long long newVertexDeclarationHash = 0;
        for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
            newVertexDeclarationHash |= (unsigned long long)elementMasks_[i] << (i * 13);

        // Do not create input layout if no vertex buffers / elements
        if (newVertexDeclarationHash)
        {
            newVertexDeclarationHash |= (unsigned long long)vertexShader_->GetElementMask() << 51;
            if (newVertexDeclarationHash != vertexDeclarationHash_)
            {
                HashMap<unsigned long long, SharedPtr<VertexDeclaration> >::Iterator
                    i = vertexDeclarations_.Find(newVertexDeclarationHash);
                if (i == vertexDeclarations_.End())
                {
                    SharedPtr<VertexDeclaration> newVertexDeclaration(new VertexDeclaration(this, vertexShader_, vertexBuffers_,
                        elementMasks_));
                    i = vertexDeclarations_.Insert(MakePair(newVertexDeclarationHash, newVertexDeclaration));
                }

                impl_->deviceContext_->IASetInputLayout((ID3D11InputLayout*)i->second_->GetInputLayout());
                vertexDeclarationHash_ = newVertexDeclarationHash;
            }
        }

        vertexDeclarationDirty_ = false;
    }

    if (blendStateDirty_)
    {
        unsigned newBlendStateHash = (unsigned)((colorWrite_ ? 1 : 0) | (blendMode_ << 1));
        if (newBlendStateHash != blendStateHash_)
        {
            HashMap<unsigned, ID3D11BlendState*>::Iterator i = impl_->blendStates_.Find(newBlendStateHash);
            if (i == impl_->blendStates_.End())
            {
                URHO3D_PROFILE(CreateBlendState);

                D3D11_BLEND_DESC stateDesc;
                memset(&stateDesc, 0, sizeof stateDesc);
                stateDesc.AlphaToCoverageEnable = false;
                stateDesc.IndependentBlendEnable = false;
                stateDesc.RenderTarget[0].BlendEnable = d3dBlendEnable[blendMode_];
                stateDesc.RenderTarget[0].SrcBlend = d3dSrcBlend[blendMode_];
                stateDesc.RenderTarget[0].DestBlend = d3dDestBlend[blendMode_];
                stateDesc.RenderTarget[0].BlendOp = d3dBlendOp[blendMode_];
                stateDesc.RenderTarget[0].SrcBlendAlpha = d3dSrcBlend[blendMode_];
                stateDesc.RenderTarget[0].DestBlendAlpha = d3dDestBlend[blendMode_];
                stateDesc.RenderTarget[0].BlendOpAlpha = d3dBlendOp[blendMode_];
                stateDesc.RenderTarget[0].RenderTargetWriteMask = colorWrite_ ? D3D11_COLOR_WRITE_ENABLE_ALL : 0x0;

                ID3D11BlendState* newBlendState = 0;
                impl_->device_->CreateBlendState(&stateDesc, &newBlendState);
                if (!newBlendState)
                    URHO3D_LOGERROR("Failed to create blend state");

                i = impl_->blendStates_.Insert(MakePair(newBlendStateHash, newBlendState));
            }

            impl_->deviceContext_->OMSetBlendState(i->second_, 0, M_MAX_UNSIGNED);
            blendStateHash_ = newBlendStateHash;
        }

        blendStateDirty_ = false;
    }

    if (depthStateDirty_)
    {
        unsigned newDepthStateHash =
            (depthWrite_ ? 1 : 0) | (stencilTest_ ? 2 : 0) | (depthTestMode_ << 2) | ((stencilCompareMask_ & 0xff) << 5) |
            ((stencilWriteMask_ & 0xff) << 13) | (stencilTestMode_ << 21) |
            ((stencilFail_ + stencilZFail_ * 5 + stencilPass_ * 25) << 24);
        if (newDepthStateHash != depthStateHash_ || stencilRefDirty_)
        {
            HashMap<unsigned, ID3D11DepthStencilState*>::Iterator i = impl_->depthStates_.Find(newDepthStateHash);
            if (i == impl_->depthStates_.End())
            {
                URHO3D_PROFILE(CreateDepthState);

                D3D11_DEPTH_STENCIL_DESC stateDesc;
                memset(&stateDesc, 0, sizeof stateDesc);
                stateDesc.DepthEnable = TRUE;
                stateDesc.DepthWriteMask = depthWrite_ ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
                stateDesc.DepthFunc = d3dCmpFunc[depthTestMode_];
                stateDesc.StencilEnable = stencilTest_ ? TRUE : FALSE;
                stateDesc.StencilReadMask = (unsigned char)stencilCompareMask_;
                stateDesc.StencilWriteMask = (unsigned char)stencilWriteMask_;
                stateDesc.FrontFace.StencilFailOp = d3dStencilOp[stencilFail_];
                stateDesc.FrontFace.StencilDepthFailOp = d3dStencilOp[stencilZFail_];
                stateDesc.FrontFace.StencilPassOp = d3dStencilOp[stencilPass_];
                stateDesc.FrontFace.StencilFunc = d3dCmpFunc[stencilTestMode_];
                stateDesc.BackFace.StencilFailOp = d3dStencilOp[stencilFail_];
                stateDesc.BackFace.StencilDepthFailOp = d3dStencilOp[stencilZFail_];
                stateDesc.BackFace.StencilPassOp = d3dStencilOp[stencilPass_];
                stateDesc.BackFace.StencilFunc = d3dCmpFunc[stencilTestMode_];

                ID3D11DepthStencilState* newDepthState = 0;
                impl_->device_->CreateDepthStencilState(&stateDesc, &newDepthState);
                if (!newDepthState)
                    URHO3D_LOGERROR("Failed to create depth state");

                i = impl_->depthStates_.Insert(MakePair(newDepthStateHash, newDepthState));
            }

            impl_->deviceContext_->OMSetDepthStencilState(i->second_, stencilRef_);
            depthStateHash_ = newDepthStateHash;
        }

        depthStateDirty_ = false;
        stencilRefDirty_ = false;
    }

    if (rasterizerStateDirty_)
    {
        unsigned depthBits = 24;
        if (depthStencil_ && depthStencil_->GetParentTexture()->GetFormat() == DXGI_FORMAT_R16_TYPELESS)
            depthBits = 16;
        int scaledDepthBias = (int)(constantDepthBias_ * (1 << depthBits));

        unsigned newRasterizerStateHash =
            (scissorTest_ ? 1 : 0) | (fillMode_ << 1) | (cullMode_ << 3) | ((scaledDepthBias & 0x1fff) << 5) |
            ((*((unsigned*)&slopeScaledDepthBias_) & 0x1fff) << 18);
        if (newRasterizerStateHash != rasterizerStateHash_)
        {
            HashMap<unsigned, ID3D11RasterizerState*>::Iterator i = impl_->rasterizerStates_.Find(newRasterizerStateHash);
            if (i == impl_->rasterizerStates_.End())
            {
                URHO3D_PROFILE(CreateRasterizerState);

                D3D11_RASTERIZER_DESC stateDesc;
                memset(&stateDesc, 0, sizeof stateDesc);
                stateDesc.FillMode = d3dFillMode[fillMode_];
                stateDesc.CullMode = d3dCullMode[cullMode_];
                stateDesc.FrontCounterClockwise = FALSE;
                stateDesc.DepthBias = scaledDepthBias;
                stateDesc.DepthBiasClamp = M_INFINITY;
                stateDesc.SlopeScaledDepthBias = slopeScaledDepthBias_;
                stateDesc.DepthClipEnable = TRUE;
                stateDesc.ScissorEnable = scissorTest_ ? TRUE : FALSE;
                stateDesc.MultisampleEnable = TRUE;
                stateDesc.AntialiasedLineEnable = FALSE;

                ID3D11RasterizerState* newRasterizerState = 0;
                impl_->device_->CreateRasterizerState(&stateDesc, &newRasterizerState);
                if (!newRasterizerState)
                    URHO3D_LOGERROR("Failed to create rasterizer state");

                i = impl_->rasterizerStates_.Insert(MakePair(newRasterizerStateHash, newRasterizerState));
            }

            impl_->deviceContext_->RSSetState(i->second_);
            rasterizerStateHash_ = newRasterizerStateHash;
        }

        rasterizerStateDirty_ = false;
    }

    if (scissorRectDirty_)
    {
        D3D11_RECT d3dRect;
        d3dRect.left = scissorRect_.left_;
        d3dRect.top = scissorRect_.top_;
        d3dRect.right = scissorRect_.right_;
        d3dRect.bottom = scissorRect_.bottom_;
        impl_->deviceContext_->RSSetScissorRects(1, &d3dRect);
        scissorRectDirty_ = false;
    }

    for (unsigned i = 0; i < dirtyConstantBuffers_.Size(); ++i)
        dirtyConstantBuffers_[i]->Apply();
    dirtyConstantBuffers_.Clear();
}

void Graphics::CreateResolveTexture()
{
    if (impl_->resolveTexture_)
        return;

    D3D11_TEXTURE2D_DESC textureDesc;
    memset(&textureDesc, 0, sizeof textureDesc);
    textureDesc.Width = (UINT)width_;
    textureDesc.Height = (UINT)height_;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.CPUAccessFlags = 0;

    impl_->device_->CreateTexture2D(&textureDesc, 0, &impl_->resolveTexture_);
}

void Graphics::SetTextureUnitMappings()
{
    textureUnits_["DiffMap"] = TU_DIFFUSE;
    textureUnits_["DiffCubeMap"] = TU_DIFFUSE;
    textureUnits_["NormalMap"] = TU_NORMAL;
    textureUnits_["SpecMap"] = TU_SPECULAR;
    textureUnits_["EmissiveMap"] = TU_EMISSIVE;
    textureUnits_["EnvMap"] = TU_ENVIRONMENT;
    textureUnits_["EnvCubeMap"] = TU_ENVIRONMENT;
    textureUnits_["LightRampMap"] = TU_LIGHTRAMP;
    textureUnits_["LightSpotMap"] = TU_LIGHTSHAPE;
    textureUnits_["LightCubeMap"] = TU_LIGHTSHAPE;
    textureUnits_["ShadowMap"] = TU_SHADOWMAP;
    textureUnits_["FaceSelectCubeMap"] = TU_FACESELECT;
    textureUnits_["IndirectionCubeMap"] = TU_INDIRECTION;
    textureUnits_["VolumeMap"] = TU_VOLUMEMAP;
    textureUnits_["ZoneCubeMap"] = TU_ZONE;
    textureUnits_["ZoneVolumeMap"] = TU_ZONE;
}

void RegisterGraphicsLibrary(Context* context)
{
    Animation::RegisterObject(context);
    Material::RegisterObject(context);
    Model::RegisterObject(context);
    Shader::RegisterObject(context);
    Technique::RegisterObject(context);
    Texture2D::RegisterObject(context);
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
