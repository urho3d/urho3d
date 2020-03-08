//
// Copyright (c) 2008-2020 the Urho3D project.
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
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsEvents.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/IndexBuffer.h"
#include "../../Graphics/Shader.h"
#include "../../Graphics/ShaderPrecache.h"
#include "../../Graphics/ShaderProgram.h"
#include "../../Graphics/Texture2D.h"
#include "../../Graphics/TextureCube.h"
#include "../../Graphics/VertexBuffer.h"
#include "../../Graphics/VertexDeclaration.h"
#include "../../IO/File.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"

#include <SDL/SDL.h>
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

// Fix missing define in MinGW headers
#ifndef D3DPRESENT_LINEAR_CONTENT
#define D3DPRESENT_LINEAR_CONTENT 0x00000002L
#endif
#ifndef D3DSTREAMSOURCE_INDEXEDDATA
#define D3DSTREAMSOURCE_INDEXEDDATA (1<<30)
#endif
#ifndef D3DSTREAMSOURCE_INSTANCEDATA
#define D3DSTREAMSOURCE_INSTANCEDATA (2<<30)
#endif

namespace Urho3D
{

static const D3DCMPFUNC d3dCmpFunc[] =
{
    D3DCMP_ALWAYS,
    D3DCMP_EQUAL,
    D3DCMP_NOTEQUAL,
    D3DCMP_LESS,
    D3DCMP_LESSEQUAL,
    D3DCMP_GREATER,
    D3DCMP_GREATEREQUAL
};

static const D3DTEXTUREFILTERTYPE d3dMinFilter[] =
{
    D3DTEXF_POINT,
    D3DTEXF_LINEAR,
    D3DTEXF_LINEAR,
    D3DTEXF_ANISOTROPIC,
    D3DTEXF_ANISOTROPIC
};

static const D3DTEXTUREFILTERTYPE d3dMagFilter[] =
{
    D3DTEXF_POINT,
    D3DTEXF_LINEAR,
    D3DTEXF_LINEAR,
    D3DTEXF_ANISOTROPIC,
    D3DTEXF_POINT,
};

static const D3DTEXTUREFILTERTYPE d3dMipFilter[] =
{
    D3DTEXF_POINT,
    D3DTEXF_POINT,
    D3DTEXF_LINEAR,
    D3DTEXF_ANISOTROPIC,
    D3DTEXF_ANISOTROPIC
};

static const D3DTEXTUREADDRESS d3dAddressMode[] =
{
    D3DTADDRESS_WRAP,
    D3DTADDRESS_MIRROR,
    D3DTADDRESS_CLAMP,
    D3DTADDRESS_BORDER
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
    TRUE,
    TRUE
};

static const D3DBLEND d3dSrcBlend[] =
{
    D3DBLEND_ONE,
    D3DBLEND_ONE,
    D3DBLEND_DESTCOLOR,
    D3DBLEND_SRCALPHA,
    D3DBLEND_SRCALPHA,
    D3DBLEND_ONE,
    D3DBLEND_INVDESTALPHA,
    D3DBLEND_ONE,
    D3DBLEND_SRCALPHA,
};

static const D3DBLEND d3dDestBlend[] =
{
    D3DBLEND_ZERO,
    D3DBLEND_ONE,
    D3DBLEND_ZERO,
    D3DBLEND_INVSRCALPHA,
    D3DBLEND_ONE,
    D3DBLEND_INVSRCALPHA,
    D3DBLEND_DESTALPHA,
    D3DBLEND_ONE,
    D3DBLEND_ONE
};

static const D3DBLENDOP d3dBlendOp[] =
{
    D3DBLENDOP_ADD,
    D3DBLENDOP_ADD,
    D3DBLENDOP_ADD,
    D3DBLENDOP_ADD,
    D3DBLENDOP_ADD,
    D3DBLENDOP_ADD,
    D3DBLENDOP_ADD,
    D3DBLENDOP_REVSUBTRACT,
    D3DBLENDOP_REVSUBTRACT
};

static const D3DCULL d3dCullMode[] =
{
    D3DCULL_NONE,
    D3DCULL_CCW,
    D3DCULL_CW
};

static const D3DFILLMODE d3dFillMode[] =
{
    D3DFILL_SOLID,
    D3DFILL_WIREFRAME,
    D3DFILL_POINT
};

static const D3DSTENCILOP d3dStencilOp[] =
{
    D3DSTENCILOP_KEEP,
    D3DSTENCILOP_ZERO,
    D3DSTENCILOP_REPLACE,
    D3DSTENCILOP_INCR,
    D3DSTENCILOP_DECR
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
    D3DPRIMITIVETYPE& d3dPrimitiveType)
{
    switch (type)
    {
    case TRIANGLE_LIST:
        primitiveCount = elementCount / 3;
        d3dPrimitiveType = D3DPT_TRIANGLELIST;
        break;

    case LINE_LIST:
        primitiveCount = elementCount / 2;
        d3dPrimitiveType = D3DPT_LINELIST;
        break;

    case POINT_LIST:
        primitiveCount = elementCount;
        d3dPrimitiveType = D3DPT_POINTLIST;
        break;

    case TRIANGLE_STRIP:
        primitiveCount = elementCount - 2;
        d3dPrimitiveType = D3DPT_TRIANGLESTRIP;
        break;

    case LINE_STRIP:
        primitiveCount = elementCount - 1;
        d3dPrimitiveType = D3DPT_LINESTRIP;
        break;

    case TRIANGLE_FAN:
        primitiveCount = elementCount - 2;
        d3dPrimitiveType = D3DPT_TRIANGLEFAN;
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

static unsigned readableDepthFormat = 0;

const Vector2 Graphics::pixelUVOffset(0.5f, 0.5f);
bool Graphics::gl3Support = false;

Graphics::Graphics(Context* context) :
    Object(context),
    impl_(new GraphicsImpl()),
    position_(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED),
    shaderPath_("Shaders/HLSL/"),
    shaderExtension_(".hlsl"),
    orientations_("LandscapeLeft LandscapeRight"),
    apiName_("D3D9")
{
    SetTextureUnitMappings();

    context_->RequireSDL(SDL_INIT_VIDEO);

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

    impl_->vertexDeclarations_.Clear();

    URHO3D_SAFE_RELEASE(impl_->defaultColorSurface_);
    URHO3D_SAFE_RELEASE(impl_->defaultDepthStencilSurface_);
    URHO3D_SAFE_RELEASE(impl_->frameQuery_);
    URHO3D_SAFE_RELEASE(impl_->device_);
    URHO3D_SAFE_RELEASE(impl_->interface_);

    if (window_)
    {
        SDL_ShowCursor(SDL_TRUE);
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }

    delete impl_;
    impl_ = nullptr;

    context_->ReleaseSDL();
}

bool Graphics::SetScreenMode(int width, int height, const ScreenModeParams& params, bool maximize)
{
    URHO3D_PROFILE(SetScreenMode);

    // Ensure that parameters are properly filled
    ScreenModeParams newParams = params;
    AdjustScreenMode(width, height, newParams, maximize);

    // If nothing changes, do not reset the device
    if (width_ == width && height_ == height && screenParams_ == newParams)
        return true;

    // Find out the full screen mode display format (match desktop color depth)
    SDL_DisplayMode mode;
    SDL_GetDesktopDisplayMode(newParams.monitor_, &mode);
    const D3DFORMAT fullscreenFormat = SDL_BITSPERPIXEL(mode.format) == 16 ? D3DFMT_R5G6B5 : D3DFMT_X8R8G8B8;

    const bool monitorChanged = screenParams_.monitor_ != newParams.monitor_;

    SDL_SetHint(SDL_HINT_ORIENTATIONS, orientations_.CString());

    if (!window_)
    {
        if (!OpenWindow(width, height, newParams.resizable_, newParams.borderless_))
            return false;
    }

    if (!impl_->interface_)
    {
        if (!CreateInterface())
            return false;

        CheckFeatureSupport();
    }

    // Fall back to non-multisampled if unsupported multisampling mode
    if (newParams.multiSample_ > 1)
    {
        if (!impl_->CheckMultiSampleSupport(fullscreenFormat, newParams.multiSample_))
            newParams.multiSample_ = 1;
    }

    AdjustWindow(width, height, newParams.fullscreen_, newParams.borderless_, newParams.monitor_);

    if (maximize)
    {
        Maximize();
        SDL_GetWindowSize(window_, &width, &height);
    }

    if (newParams.fullscreen_)
    {
        impl_->presentParams_.BackBufferFormat = fullscreenFormat;
        impl_->presentParams_.Windowed = false;
    }
    else
    {
        impl_->presentParams_.BackBufferFormat = D3DFMT_UNKNOWN;
        impl_->presentParams_.Windowed = true;
    }

    impl_->presentParams_.BackBufferWidth = (UINT)width;
    impl_->presentParams_.BackBufferHeight = (UINT)height;
    impl_->presentParams_.BackBufferCount = newParams.tripleBuffer_ ? 2 : 1;
    impl_->presentParams_.MultiSampleType = newParams.multiSample_ > 1 ? static_cast<D3DMULTISAMPLE_TYPE>(newParams.multiSample_) : D3DMULTISAMPLE_NONE;
    impl_->presentParams_.MultiSampleQuality = 0;
    impl_->presentParams_.SwapEffect = D3DSWAPEFFECT_DISCARD;
    impl_->presentParams_.hDeviceWindow = GetWindowHandle(window_);
    impl_->presentParams_.EnableAutoDepthStencil = TRUE;
    impl_->presentParams_.AutoDepthStencilFormat = D3DFMT_D24S8;
    impl_->presentParams_.Flags = D3DPRESENT_LINEAR_CONTENT;
    impl_->presentParams_.FullScreen_RefreshRateInHz = newParams.fullscreen_ ? newParams.refreshRate_ : D3DPRESENT_RATE_DEFAULT;

    if (newParams.vsync_)
        impl_->presentParams_.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    else
        impl_->presentParams_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    width_ = width;
    height_ = height;
    screenParams_ = newParams;

    if (!impl_->device_)
    {
        unsigned adapter = SDL_Direct3D9GetAdapterIndex(screenParams_.monitor_);
        unsigned deviceType = D3DDEVTYPE_HAL;

        // Check for PerfHUD adapter
        for (unsigned i = 0; i < impl_->interface_->GetAdapterCount(); ++i)
        {
            D3DADAPTER_IDENTIFIER9 identifier;
            impl_->interface_->GetAdapterIdentifier(i, 0, &identifier);
            if (strstr(identifier.Description, "PerfHUD") != nullptr)
            {
                adapter = i;
                deviceType = D3DDEVTYPE_REF;
                break;
            }
        }

        impl_->interface_->GetAdapterIdentifier(adapter, 0, &impl_->adapterIdentifier_);
        if (!CreateDevice(adapter, deviceType))
            return false;
    }
    else
    {
        if (!monitorChanged)
            ResetDevice();
        else
        {
            URHO3D_LOGINFO("Destroying D3D9 device");
            // Monitor changed, re-create the D3D9 device on the new monitor
            impl_->vertexDeclarations_.Clear();
            OnDeviceLost();
            {
                MutexLock lock(gpuObjectMutex_);
                // Release all GPU objects that still exist
                for (PODVector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
                    (*i)->Release();
            }

            // destroy previous device
            URHO3D_SAFE_RELEASE(impl_->device_);

            // create new device on the specified monitor
            unsigned adapter = SDL_Direct3D9GetAdapterIndex(screenParams_.monitor_);
            unsigned deviceType = D3DDEVTYPE_HAL;
            if (!CreateDevice(adapter, deviceType))
                return false;
            ResetDevice();
        }
    }

    // Clear the initial window contents to black
    impl_->device_->BeginScene();
    Clear(CLEAR_COLOR);
    impl_->device_->EndScene();
    impl_->device_->Present(nullptr, nullptr, nullptr, nullptr);

#ifdef URHO3D_LOGGING
    D3DADAPTER_IDENTIFIER9 id = {0};
    HRESULT hr = impl_->interface_->GetAdapterIdentifier(SDL_Direct3D9GetAdapterIndex(screenParams_.monitor_), 0, &id);
    if (S_OK == hr)
        URHO3D_LOGINFOF("Adapter used %s", id.Description);
#endif

    OnScreenModeChanged();
    return true;
}

void Graphics::SetSRGB(bool enable)
{
    sRGB_ = enable && sRGBWriteSupport_;
}

void Graphics::SetDither(bool enable)
{
    // No effect on Direct3D9
}

void Graphics::SetFlushGPU(bool enable)
{
    flushGPU_ = enable;
}

void Graphics::SetForceGL2(bool enable)
{
    // No effect on Direct3D9
}

void Graphics::Close()
{
    if (window_)
    {
        SDL_ShowCursor(SDL_TRUE);
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
}

bool Graphics::TakeScreenShot(Image& destImage)
{
    URHO3D_PROFILE(TakeScreenShot);

    if (!impl_->device_)
        return false;

    if (IsDeviceLost())
    {
        URHO3D_LOGERROR("Can not take screenshot while device is lost");
        return false;
    }

    D3DSURFACE_DESC surfaceDesc;
    impl_->defaultColorSurface_->GetDesc(&surfaceDesc);

    // If possible, get the backbuffer data, because it is a lot faster.
    // However, if we are multisampled, need to use the front buffer
    bool useBackBuffer = true;
    unsigned surfaceWidth = (unsigned)width_;
    unsigned surfaceHeight = (unsigned)height_;

    if (impl_->presentParams_.MultiSampleType)
    {
        // If windowed and multisampled, must still capture the whole screen
        if (!screenParams_.fullscreen_)
        {
            IntVector2 desktopSize = GetDesktopResolution(screenParams_.monitor_);
            surfaceWidth = (unsigned)desktopSize.x_;
            surfaceHeight = (unsigned)desktopSize.y_;
        }
        useBackBuffer = false;
        surfaceDesc.Format = D3DFMT_A8R8G8B8;
    }

    IDirect3DSurface9* surface = nullptr;
    HRESULT hr = impl_->device_->CreateOffscreenPlainSurface(surfaceWidth, surfaceHeight, surfaceDesc.Format, D3DPOOL_SYSTEMMEM, &surface, nullptr);
    if (FAILED(hr))
    {
        URHO3D_SAFE_RELEASE(surface);
        URHO3D_LOGD3DERROR("Could not create surface for taking a screenshot", hr);
        return false;
    }

    if (useBackBuffer)
        hr = impl_->device_->GetRenderTargetData(impl_->defaultColorSurface_, surface);
    else
        hr = impl_->device_->GetFrontBufferData(0, surface);
    if (FAILED(hr))
    {
        URHO3D_SAFE_RELEASE(surface);
        URHO3D_LOGD3DERROR("Could not get rendertarget data for taking a screenshot", hr);
        return false;
    }

    // If capturing the whole screen, determine the window rect
    RECT sourceRect;
    if (surfaceHeight == height_ && surfaceWidth == width_)
    {
        sourceRect.left = 0;
        sourceRect.top = 0;
        sourceRect.right = width_;
        sourceRect.bottom = height_;
    }
    else
    {
        HWND hwnd = GetWindowHandle(window_);
        GetClientRect(hwnd, &sourceRect);
        ClientToScreen(hwnd, (LPPOINT)&sourceRect);
    }

    D3DLOCKED_RECT lockedRect;
    lockedRect.pBits = nullptr;
    hr = surface->LockRect(&lockedRect, &sourceRect, D3DLOCK_NOSYSLOCK | D3DLOCK_READONLY);
    if (FAILED(hr) || !lockedRect.pBits)
    {
        URHO3D_SAFE_RELEASE(surface);
        URHO3D_LOGD3DERROR("Could not lock surface for taking a screenshot", hr);
        return false;
    }

    destImage.SetSize(width_, height_, 3);
    unsigned char* destData = destImage.GetData();

    if (surfaceDesc.Format == D3DFMT_R5G6B5)
    {
        for (int y = 0; y < height_; ++y)
        {
            unsigned short* src = (unsigned short*)((unsigned char*)lockedRect.pBits + y * lockedRect.Pitch);
            unsigned char* dest = destData + y * width_ * 3;

            for (int x = 0; x < width_; ++x)
            {
                unsigned short rgb = *src++;
                int b = rgb & 31;
                int g = (rgb >> 5) & 63;
                int r = (rgb >> 11);

                dest[0] = (unsigned char)(r * 255.0f / 31.0f);
                dest[1] = (unsigned char)(g * 255.0f / 63.0f);
                dest[2] = (unsigned char)(b * 255.0f / 31.0f);
                dest += 3;
            }
        }
    }
    else
    {
        for (int y = 0; y < height_; ++y)
        {
            unsigned char* src = (unsigned char*)lockedRect.pBits + y * lockedRect.Pitch;
            unsigned char* dest = destData + y * width_ * 3;

            for (int x = 0; x < width_; ++x)
            {
                dest[0] = src[2];
                dest[1] = src[1];
                dest[2] = src[0];
                src += 4;
                dest += 3;
            }
        }
    }

    surface->UnlockRect();
    surface->Release();

    return true;
}

bool Graphics::BeginFrame()
{
    if (!IsInitialized())
        return false;

    // If using an external window, check it for size changes, and reset screen mode if necessary
    if (externalWindow_)
    {
        int width, height;

        SDL_GetWindowSize(window_, &width, &height);
        if (width != width_ || height != height_)
            SetMode(width, height);
    }
    else
    {
        // To prevent a loop of endless device loss and flicker, do not attempt to render when in fullscreen
        // and the window is minimized
        if (screenParams_.fullscreen_ && (SDL_GetWindowFlags(window_) & SDL_WINDOW_MINIMIZED))
            return false;
    }

    // Check for lost device before rendering
    HRESULT hr = impl_->device_->TestCooperativeLevel();
    if (hr != D3D_OK)
    {
        URHO3D_PROFILE(DeviceLost);

        impl_->deviceLost_ = true;

        // The device can not be reset yet, sleep and try again eventually
        if (hr == D3DERR_DEVICELOST)
        {
            Time::Sleep(20);
            return false;
        }
        // The device is lost, but ready to be reset. Reset device but do not render on this frame yet
        if (hr == D3DERR_DEVICENOTRESET)
        {
            ResetDevice();
            return false;
        }
    }

    impl_->device_->BeginScene();

    // Set default rendertarget and depth buffer
    ResetRenderTargets();

    // Cleanup textures from previous frame
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        SetTexture(i, nullptr);

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

        impl_->device_->EndScene();
        impl_->device_->Present(nullptr, nullptr, nullptr, nullptr);
    }

    // Optionally flush GPU buffer to avoid control lag or framerate fluctuations due to multiple frame buffering
    // If a query was issued on the previous frame, first wait for it to finish
    if (impl_->frameQuery_)
    {
        if (impl_->queryIssued_)
        {
            URHO3D_PROFILE(FlushGPU);

            while (impl_->frameQuery_->GetData(nullptr, 0, D3DGETDATA_FLUSH) == S_FALSE)
            {
            }

            impl_->queryIssued_ = false;
        }

        if (flushGPU_)
        {
            impl_->frameQuery_->Issue(D3DISSUE_END);
            impl_->queryIssued_ = true;
        }
    }

    // Clean up too large scratch buffers
    CleanupScratchBuffers();
}

void Graphics::Clear(ClearTargetFlags flags, const Color& color, float depth, unsigned stencil)
{
    DWORD d3dFlags = 0;
    if (flags & CLEAR_COLOR)
        d3dFlags |= D3DCLEAR_TARGET;
    if (flags & CLEAR_DEPTH)
        d3dFlags |= D3DCLEAR_ZBUFFER;
    if (flags & CLEAR_STENCIL)
        d3dFlags |= D3DCLEAR_STENCIL;

    impl_->device_->Clear(0, nullptr, d3dFlags, GetD3DColor(color), depth, stencil);
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

    RECT rect;
    rect.left = Clamp(vpCopy.left_, 0, width_);
    rect.top = Clamp(vpCopy.top_, 0, height_);
    rect.right = Clamp(vpCopy.right_, 0, width_);
    rect.bottom = Clamp(vpCopy.bottom_, 0, height_);

    RECT destRect;
    destRect.left = 0;
    destRect.top = 0;
    destRect.right = destination->GetWidth();
    destRect.bottom = destination->GetHeight();

    HRESULT hr = impl_->device_->StretchRect(impl_->defaultColorSurface_, &rect,
        (IDirect3DSurface9*)destination->GetRenderSurface()->GetSurface(), &destRect, D3DTEXF_NONE);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Failed to resolve to texture", hr);
        return false;
    }
    else
        return true;
}

bool Graphics::ResolveToTexture(Texture2D* texture)
{
    if (!texture || !texture->GetRenderSurface() || !texture->GetGPUObject() || texture->GetMultiSample() < 2)
        return false;

    URHO3D_PROFILE(ResolveToTexture);

    // Clear dirty flag already, because if resolve fails it's no use to retry (e.g. on the same frame)
    RenderSurface* surface = texture->GetRenderSurface();
    texture->SetResolveDirty(false);
    surface->SetResolveDirty(false);

    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = texture->GetWidth();
    rect.bottom = texture->GetHeight();

    IDirect3DSurface9* srcSurface = (IDirect3DSurface9*)surface->GetSurface();
    IDirect3DTexture9* destTexture = (IDirect3DTexture9*)texture->GetGPUObject();
    IDirect3DSurface9* destSurface = nullptr;
    HRESULT hr = destTexture->GetSurfaceLevel(0, &destSurface);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Failed to get destination surface for resolve", hr);
        URHO3D_SAFE_RELEASE(destSurface);
        return false;
    }

    hr = impl_->device_->StretchRect(srcSurface, &rect, destSurface, &rect, D3DTEXF_NONE);
    URHO3D_SAFE_RELEASE(destSurface);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Failed to resolve to texture", hr);
        return false;
    }
    else
        return true;
}

bool Graphics::ResolveToTexture(TextureCube* texture)
{
    if (!texture || !texture->GetRenderSurface(FACE_POSITIVE_X) || !texture->GetGPUObject() || texture->GetMultiSample() < 2)
        return false;

    URHO3D_PROFILE(ResolveToTexture);

    texture->SetResolveDirty(false);

    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = texture->GetWidth();
    rect.bottom = texture->GetHeight();

    for (unsigned i = 0; i < MAX_CUBEMAP_FACES; ++i)
    {
        // Resolve only the surface(s) that were actually rendered to
        RenderSurface* surface = texture->GetRenderSurface((CubeMapFace)i);
        if (!surface->IsResolveDirty())
            continue;

        surface->SetResolveDirty(false);
        IDirect3DSurface9* srcSurface = (IDirect3DSurface9*)surface->GetSurface();
        IDirect3DCubeTexture9* destTexture = (IDirect3DCubeTexture9*)texture->GetGPUObject();
        IDirect3DSurface9* destSurface = nullptr;
        HRESULT hr = destTexture->GetCubeMapSurface((D3DCUBEMAP_FACES)i, 0, &destSurface);
        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Failed to get destination surface for resolve", hr);
            URHO3D_SAFE_RELEASE(destSurface);
            return false;
        }

        hr = impl_->device_->StretchRect(srcSurface, &rect, destSurface, &rect, D3DTEXF_NONE);
        URHO3D_SAFE_RELEASE(destSurface);
        if (FAILED(hr))
        {
            URHO3D_LOGD3DERROR("Failed to resolve to texture", hr);
            return false;
        }
    }

    return true;
}

void Graphics::Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount)
{
    if (!vertexCount)
        return;

    ResetStreamFrequencies();

    unsigned primitiveCount;
    D3DPRIMITIVETYPE d3dPrimitiveType;

    GetD3DPrimitiveType(vertexCount, type, primitiveCount, d3dPrimitiveType);
    impl_->device_->DrawPrimitive(d3dPrimitiveType, vertexStart, primitiveCount);

    numPrimitives_ += primitiveCount;
    ++numBatches_;
}

void Graphics::Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount)
{
    if (!indexCount)
        return;

    ResetStreamFrequencies();

    unsigned primitiveCount;
    D3DPRIMITIVETYPE d3dPrimitiveType;

    GetD3DPrimitiveType(indexCount, type, primitiveCount, d3dPrimitiveType);
    impl_->device_->DrawIndexedPrimitive(d3dPrimitiveType, 0, minVertex, vertexCount, indexStart, primitiveCount);

    numPrimitives_ += primitiveCount;
    ++numBatches_;
}

void Graphics::Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned baseVertexIndex, unsigned minVertex, unsigned vertexCount)
{
    if (!indexCount)
        return;

    ResetStreamFrequencies();

    unsigned primitiveCount;
    D3DPRIMITIVETYPE d3dPrimitiveType;

    GetD3DPrimitiveType(indexCount, type, primitiveCount, d3dPrimitiveType);
    impl_->device_->DrawIndexedPrimitive(d3dPrimitiveType, baseVertexIndex, minVertex, vertexCount, indexStart, primitiveCount);

    numPrimitives_ += primitiveCount;
    ++numBatches_;
}

void Graphics::DrawInstanced(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount,
    unsigned instanceCount)
{
    if (!indexCount || !instanceCount)
        return;

    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        VertexBuffer* buffer = vertexBuffers_[i];
        if (buffer)
        {
            const PODVector<VertexElement>& elements = buffer->GetElements();
            // Check if buffer has per-instance data
            if (elements.Size() && elements[0].perInstance_)
                SetStreamFrequency(i, D3DSTREAMSOURCE_INSTANCEDATA | 1u);
            else
                SetStreamFrequency(i, D3DSTREAMSOURCE_INDEXEDDATA | instanceCount);
        }
    }

    unsigned primitiveCount;
    D3DPRIMITIVETYPE d3dPrimitiveType;

    GetD3DPrimitiveType(indexCount, type, primitiveCount, d3dPrimitiveType);
    impl_->device_->DrawIndexedPrimitive(d3dPrimitiveType, 0, minVertex, vertexCount, indexStart, primitiveCount);

    numPrimitives_ += instanceCount * primitiveCount;
    ++numBatches_;
}

void Graphics::DrawInstanced(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned baseVertexIndex, unsigned minVertex,
    unsigned vertexCount, unsigned instanceCount)
{
    if (!indexCount || !instanceCount)
        return;

    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        VertexBuffer* buffer = vertexBuffers_[i];
        if (buffer)
        {
            const PODVector<VertexElement>& elements = buffer->GetElements();
            // Check if buffer has per-instance data
            if (elements.Size() && elements[0].perInstance_)
                SetStreamFrequency(i, D3DSTREAMSOURCE_INSTANCEDATA | 1u);
            else
                SetStreamFrequency(i, D3DSTREAMSOURCE_INDEXEDDATA | instanceCount);
        }
    }

    unsigned primitiveCount;
    D3DPRIMITIVETYPE d3dPrimitiveType;

    GetD3DPrimitiveType(indexCount, type, primitiveCount, d3dPrimitiveType);
    impl_->device_->DrawIndexedPrimitive(d3dPrimitiveType, baseVertexIndex, minVertex, vertexCount, indexStart, primitiveCount);

    numPrimitives_ += instanceCount * primitiveCount;
    ++numBatches_;
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

    // Build vertex declaration hash code out of the buffers
    unsigned long long hash = 0;
    for (unsigned i = 0; i < buffers.Size(); ++i)
    {
        if (!buffers[i])
            continue;

        hash |= buffers[i]->GetBufferHash(i);
    }

    if (hash)
    {
        // If no previous vertex declaration for that hash, create new
        VertexDeclarationMap::Iterator i = impl_->vertexDeclarations_.Find(hash);
        if (i == impl_->vertexDeclarations_.End())
        {
            SharedPtr<VertexDeclaration> newDeclaration(new VertexDeclaration(this, buffers));
            if (!newDeclaration->GetDeclaration())
                return false;

            i = impl_->vertexDeclarations_.Insert(MakePair(hash, newDeclaration));
        }

        VertexDeclaration* declaration = i->second_;
        if (declaration != impl_->vertexDeclaration_)
        {
            impl_->device_->SetVertexDeclaration(declaration->GetDeclaration());
            impl_->vertexDeclaration_ = declaration;
        }
    }

    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        VertexBuffer* buffer = nullptr;
        unsigned offset = 0;

        if (i < buffers.Size() && buffers[i])
        {
            buffer = buffers[i];
            const PODVector<VertexElement>& elements = buffer->GetElements();
            // Check if buffer has per-instance data; add instance offset in that case
            if (elements.Size() && elements[0].perInstance_)
                offset = instanceOffset * buffer->GetVertexSize();
        }

        if (buffer != vertexBuffers_[i] || offset != impl_->streamOffsets_[i])
        {
            if (buffer)
                impl_->device_->SetStreamSource(i, (IDirect3DVertexBuffer9*)buffer->GetGPUObject(), offset,
                    buffer->GetVertexSize());
            else
                impl_->device_->SetStreamSource(i, nullptr, 0, 0);

            vertexBuffers_[i] = buffer;
            impl_->streamOffsets_[i] = offset;
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
    if (buffer != indexBuffer_)
    {
        if (buffer)
            impl_->device_->SetIndices((IDirect3DIndexBuffer9*)buffer->GetGPUObject());
        else
            impl_->device_->SetIndices(nullptr);

        indexBuffer_ = buffer;
    }
}

void Graphics::SetShaders(ShaderVariation* vs, ShaderVariation* ps)
{
    if (vs == vertexShader_ && ps == pixelShader_)
        return;

    ClearParameterSources();

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
                    vs = nullptr;
                }
            }
            else
                vs = nullptr;
        }

        if (vs && vs->GetShaderType() == VS)
            impl_->device_->SetVertexShader((IDirect3DVertexShader9*)vs->GetGPUObject());
        else
        {
            impl_->device_->SetVertexShader(nullptr);
            vs = nullptr;
        }

        vertexShader_ = vs;
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
                    ps = nullptr;
                }
            }
            else
                ps = nullptr;
        }

        if (ps && ps->GetShaderType() == PS)
            impl_->device_->SetPixelShader((IDirect3DPixelShader9*)ps->GetGPUObject());
        else
        {
            impl_->device_->SetPixelShader(nullptr);
            ps = nullptr;
        }

        pixelShader_ = ps;
    }

    // Update current available shader parameters
    if (vertexShader_ && pixelShader_)
    {
        Pair<ShaderVariation*, ShaderVariation*> key = MakePair(vertexShader_, pixelShader_);
        ShaderProgramMap::Iterator i = impl_->shaderPrograms_.Find(key);
        if (i != impl_->shaderPrograms_.End())
            impl_->shaderProgram_ = i->second_.Get();
        else
        {
            ShaderProgram* newProgram = impl_->shaderPrograms_[key] = new ShaderProgram(vertexShader_, pixelShader_);
            impl_->shaderProgram_ = newProgram;
        }
    }
    else
        impl_->shaderProgram_ = nullptr;

    // Store shader combination if shader dumping in progress
    if (shaderPrecache_)
        shaderPrecache_->StoreShaders(vertexShader_, pixelShader_);
}

void Graphics::SetShaderParameter(StringHash param, const float* data, unsigned count)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!impl_->shaderProgram_ || (i = impl_->shaderProgram_->parameters_.Find(param)) == impl_->shaderProgram_->parameters_.End())
        return;

    if (i->second_.type_ == VS)
        impl_->device_->SetVertexShaderConstantF(i->second_.register_, data, count / 4);
    else
        impl_->device_->SetPixelShaderConstantF(i->second_.register_, data, count / 4);
}

void Graphics::SetShaderParameter(StringHash param, float value)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!impl_->shaderProgram_ || (i = impl_->shaderProgram_->parameters_.Find(param)) == impl_->shaderProgram_->parameters_.End())
        return;

    static Vector4 data(Vector4::ZERO);
    data.x_ = value;

    if (i->second_.type_ == VS)
        impl_->device_->SetVertexShaderConstantF(i->second_.register_, &data.x_, 1);
    else
        impl_->device_->SetPixelShaderConstantF(i->second_.register_, &data.x_, 1);
}

void Graphics::SetShaderParameter(StringHash param, int value)
{
    /// \todo Int constants seem to have no effect on Direct3D9
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!impl_->shaderProgram_ || (i = impl_->shaderProgram_->parameters_.Find(param)) == impl_->shaderProgram_->parameters_.End())
        return;

    if (i->second_.type_ == VS)
        impl_->device_->SetVertexShaderConstantI(i->second_.register_, &value, 1);
    else
        impl_->device_->SetPixelShaderConstantI(i->second_.register_, &value, 1);
}

void Graphics::SetShaderParameter(StringHash param, bool value)
{
    /// \todo Bool constants seem to have no effect on Direct3D9
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!impl_->shaderProgram_ || (i = impl_->shaderProgram_->parameters_.Find(param)) == impl_->shaderProgram_->parameters_.End())
        return;

    BOOL data = value;

    if (i->second_.type_ == VS)
        impl_->device_->SetVertexShaderConstantB(i->second_.register_, &data, 1);
    else
        impl_->device_->SetPixelShaderConstantB(i->second_.register_, &data, 1);
}

void Graphics::SetShaderParameter(StringHash param, const Color& color)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!impl_->shaderProgram_ || (i = impl_->shaderProgram_->parameters_.Find(param)) == impl_->shaderProgram_->parameters_.End())
        return;

    if (i->second_.type_ == VS)
        impl_->device_->SetVertexShaderConstantF(i->second_.register_, color.Data(), 1);
    else
        impl_->device_->SetPixelShaderConstantF(i->second_.register_, color.Data(), 1);
}

void Graphics::SetShaderParameter(StringHash param, const Vector2& vector)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!impl_->shaderProgram_ || (i = impl_->shaderProgram_->parameters_.Find(param)) == impl_->shaderProgram_->parameters_.End())
        return;

    static Vector4 data(Vector4::ZERO);
    data.x_ = vector.x_;
    data.y_ = vector.y_;

    if (i->second_.type_ == VS)
        impl_->device_->SetVertexShaderConstantF(i->second_.register_, &data.x_, 1);
    else
        impl_->device_->SetPixelShaderConstantF(i->second_.register_, &data.x_, 1);
}

void Graphics::SetShaderParameter(StringHash param, const Matrix3& matrix)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!impl_->shaderProgram_ || (i = impl_->shaderProgram_->parameters_.Find(param)) == impl_->shaderProgram_->parameters_.End())
        return;

    static Matrix3x4 data(Matrix3x4::ZERO);
    data.m00_ = matrix.m00_;
    data.m01_ = matrix.m01_;
    data.m02_ = matrix.m02_;
    data.m10_ = matrix.m10_;
    data.m11_ = matrix.m11_;
    data.m12_ = matrix.m12_;
    data.m20_ = matrix.m20_;
    data.m21_ = matrix.m21_;
    data.m22_ = matrix.m22_;

    if (i->second_.type_ == VS)
        impl_->device_->SetVertexShaderConstantF(i->second_.register_, &data.m00_, 3);
    else
        impl_->device_->SetPixelShaderConstantF(i->second_.register_, &data.m00_, 3);
}

void Graphics::SetShaderParameter(StringHash param, const Vector3& vector)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!impl_->shaderProgram_ || (i = impl_->shaderProgram_->parameters_.Find(param)) == impl_->shaderProgram_->parameters_.End())
        return;

    static Vector4 data(Vector4::ZERO);
    data.x_ = vector.x_;
    data.y_ = vector.y_;
    data.z_ = vector.z_;

    if (i->second_.type_ == VS)
        impl_->device_->SetVertexShaderConstantF(i->second_.register_, &data.x_, 1);
    else
        impl_->device_->SetPixelShaderConstantF(i->second_.register_, &data.x_, 1);
}

void Graphics::SetShaderParameter(StringHash param, const Matrix4& matrix)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!impl_->shaderProgram_ || (i = impl_->shaderProgram_->parameters_.Find(param)) == impl_->shaderProgram_->parameters_.End())
        return;

    if (i->second_.type_ == VS)
        impl_->device_->SetVertexShaderConstantF(i->second_.register_, matrix.Data(), 4);
    else
        impl_->device_->SetPixelShaderConstantF(i->second_.register_, matrix.Data(), 4);
}

void Graphics::SetShaderParameter(StringHash param, const Vector4& vector)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!impl_->shaderProgram_ || (i = impl_->shaderProgram_->parameters_.Find(param)) == impl_->shaderProgram_->parameters_.End())
        return;

    if (i->second_.type_ == VS)
        impl_->device_->SetVertexShaderConstantF(i->second_.register_, vector.Data(), 1);
    else
        impl_->device_->SetPixelShaderConstantF(i->second_.register_, vector.Data(), 1);
}

void Graphics::SetShaderParameter(StringHash param, const Matrix3x4& matrix)
{
    HashMap<StringHash, ShaderParameter>::Iterator i;
    if (!impl_->shaderProgram_ || (i = impl_->shaderProgram_->parameters_.Find(param)) == impl_->shaderProgram_->parameters_.End())
        return;

    if (i->second_.type_ == VS)
        impl_->device_->SetVertexShaderConstantF(i->second_.register_, matrix.Data(), 3);
    else
        impl_->device_->SetPixelShaderConstantF(i->second_.register_, matrix.Data(), 3);
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
    return impl_->shaderProgram_ && impl_->shaderProgram_->parameters_.Find(param) != impl_->shaderProgram_->parameters_.End();
}

bool Graphics::HasTextureUnit(TextureUnit unit)
{
    return pixelShader_ && pixelShader_->HasTextureUnit(unit);
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

    if (texture)
    {
        // Check if texture is currently bound as a rendertarget. In that case, use its backup texture, or blank if not defined
        if (renderTargets_[0] && renderTargets_[0]->GetParentTexture() == texture)
            texture = texture->GetBackupTexture();
        else
        {
            // Resolve multisampled texture now as necessary
            if (texture->GetMultiSample() > 1 && texture->GetAutoResolve() && texture->IsResolveDirty())
            {
                if (texture->GetType() == Texture2D::GetTypeStatic())
                    ResolveToTexture(static_cast<Texture2D*>(texture));
                else if (texture->GetType() == TextureCube::GetTypeStatic())
                    ResolveToTexture(static_cast<TextureCube*>(texture));
            }
        }
    }

    if (texture != textures_[index])
    {
        if (texture)
            impl_->device_->SetTexture(index, (IDirect3DBaseTexture9*)texture->GetGPUObject());
        else
            impl_->device_->SetTexture(index, nullptr);

        textures_[index] = texture;
    }

    if (texture)
    {
        TextureFilterMode filterMode = texture->GetFilterMode();
        if (filterMode == FILTER_DEFAULT)
            filterMode = defaultTextureFilterMode_;

        D3DTEXTUREFILTERTYPE min, mag, mip;
        min = d3dMinFilter[filterMode];
        if (min != impl_->minFilters_[index])
        {
            impl_->device_->SetSamplerState(index, D3DSAMP_MINFILTER, min);
            impl_->minFilters_[index] = min;
        }
        mag = d3dMagFilter[filterMode];
        if (mag != impl_->magFilters_[index])
        {
            impl_->device_->SetSamplerState(index, D3DSAMP_MAGFILTER, mag);
            impl_->magFilters_[index] = mag;
        }
        mip = d3dMipFilter[filterMode];
        if (mip != impl_->mipFilters_[index])
        {
            impl_->device_->SetSamplerState(index, D3DSAMP_MIPFILTER, mip);
            impl_->mipFilters_[index] = mip;
        }
        D3DTEXTUREADDRESS u, v;
        u = d3dAddressMode[texture->GetAddressMode(COORD_U)];
        if (u != impl_->uAddressModes_[index])
        {
            impl_->device_->SetSamplerState(index, D3DSAMP_ADDRESSU, u);
            impl_->uAddressModes_[index] = u;
        }
        v = d3dAddressMode[texture->GetAddressMode(COORD_V)];
        if (v != impl_->vAddressModes_[index])
        {
            impl_->device_->SetSamplerState(index, D3DSAMP_ADDRESSV, v);
            impl_->vAddressModes_[index] = v;
        }
        if (texture->GetType() == TextureCube::GetTypeStatic())
        {
            D3DTEXTUREADDRESS w = d3dAddressMode[texture->GetAddressMode(COORD_W)];
            if (w != impl_->wAddressModes_[index])
            {
                impl_->device_->SetSamplerState(index, D3DSAMP_ADDRESSW, w);
                impl_->wAddressModes_[index] = w;
            }
        }
        unsigned maxAnisotropy = texture->GetAnisotropy();
        if (!maxAnisotropy)
            maxAnisotropy = defaultTextureAnisotropy_;
        if (maxAnisotropy != impl_->maxAnisotropy_[index])
        {
            impl_->device_->SetSamplerState(index, D3DSAMP_MAXANISOTROPY, maxAnisotropy);
            impl_->maxAnisotropy_[index] = maxAnisotropy;
        }
        if (u == D3DTADDRESS_BORDER || v == D3DTADDRESS_BORDER)
        {
            const Color& borderColor = texture->GetBorderColor();
            if (borderColor != impl_->borderColors_[index])
            {
                impl_->device_->SetSamplerState(index, D3DSAMP_BORDERCOLOR, GetD3DColor(borderColor));
                impl_->borderColors_[index] = borderColor;
            }
        }
        if (sRGBSupport_)
        {
            bool sRGB = texture->GetSRGB();
            if (sRGB != impl_->sRGBModes_[index])
            {
                impl_->device_->SetSamplerState(index, D3DSAMP_SRGBTEXTURE, sRGB ? TRUE : FALSE);
                impl_->sRGBModes_[index] = sRGB;
            }
        }
    }
}

void Graphics::SetDefaultTextureFilterMode(TextureFilterMode mode)
{
    defaultTextureFilterMode_ = mode;
}

void Graphics::SetDefaultTextureAnisotropy(unsigned level)
{
    defaultTextureAnisotropy_ = Max(level, 1U);
}

void Graphics::ResetRenderTargets()
{
    for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        SetRenderTarget(i, (RenderSurface*)nullptr);
    SetDepthStencil((RenderSurface*)nullptr);
    SetViewport(IntRect(0, 0, width_, height_));
}

void Graphics::ResetRenderTarget(unsigned index)
{
    SetRenderTarget(index, (RenderSurface*)nullptr);
}

void Graphics::ResetDepthStencil()
{
    SetDepthStencil((RenderSurface*)nullptr);
}

void Graphics::SetRenderTarget(unsigned index, RenderSurface* renderTarget)
{
    if (index >= MAX_RENDERTARGETS)
        return;

    IDirect3DSurface9* newColorSurface = nullptr;

    if (renderTarget)
    {
        if (renderTarget->GetUsage() != TEXTURE_RENDERTARGET)
            return;
        newColorSurface = (IDirect3DSurface9*)renderTarget->GetSurface();
    }
    else
    {
        if (!index)
            newColorSurface = impl_->defaultColorSurface_;
    }

    renderTargets_[index] = renderTarget;

    if (newColorSurface != impl_->colorSurfaces_[index])
    {
        impl_->device_->SetRenderTarget(index, newColorSurface);
        impl_->colorSurfaces_[index] = newColorSurface;
        // Setting the first rendertarget causes viewport to be reset
        if (!index)
        {
            IntVector2 rtSize = GetRenderTargetDimensions();
            viewport_ = IntRect(0, 0, rtSize.x_, rtSize.y_);
        }
    }

    if (renderTarget)
    {
        Texture* parentTexture = renderTarget->GetParentTexture();

        // If the rendertarget is also bound as a texture, replace with backup texture or null
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (textures_[i] == parentTexture)
                SetTexture(i, textures_[i]->GetBackupTexture());
        }

        // If multisampled, mark the texture & surface needing resolve
        if (parentTexture->GetMultiSample() > 1 && parentTexture->GetAutoResolve())
        {
            parentTexture->SetResolveDirty(true);
            renderTarget->SetResolveDirty(true);
        }
    }

    // First rendertarget controls sRGB write mode
    if (!index && sRGBWriteSupport_)
    {
        bool sRGBWrite = renderTarget ? renderTarget->GetParentTexture()->GetSRGB() : sRGB_;
        if (sRGBWrite != impl_->sRGBWrite_)
        {
            impl_->device_->SetRenderState(D3DRS_SRGBWRITEENABLE, sRGBWrite ? TRUE : FALSE);
            impl_->sRGBWrite_ = sRGBWrite;
        }
    }
}

void Graphics::SetRenderTarget(unsigned index, Texture2D* texture)
{
    RenderSurface* renderTarget = nullptr;
    if (texture)
        renderTarget = texture->GetRenderSurface();

    SetRenderTarget(index, renderTarget);
}

void Graphics::SetDepthStencil(RenderSurface* depthStencil)
{
    IDirect3DSurface9* newDepthStencilSurface = nullptr;
    if (depthStencil && depthStencil->GetUsage() == TEXTURE_DEPTHSTENCIL)
    {
        newDepthStencilSurface = (IDirect3DSurface9*)depthStencil->GetSurface();
        depthStencil_ = depthStencil;
    }
    if (!newDepthStencilSurface)
    {
        newDepthStencilSurface = impl_->defaultDepthStencilSurface_;
        depthStencil_ = nullptr;
    }
    if (newDepthStencilSurface != impl_->depthStencilSurface_)
    {
        impl_->device_->SetDepthStencilSurface(newDepthStencilSurface);
        impl_->depthStencilSurface_ = newDepthStencilSurface;
    }
}

void Graphics::SetDepthStencil(Texture2D* texture)
{
    RenderSurface* depthStencil = nullptr;
    if (texture)
        depthStencil = texture->GetRenderSurface();

    SetDepthStencil(depthStencil);
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

    D3DVIEWPORT9 vp;
    vp.MinZ = 0.0f;
    vp.MaxZ = 1.0f;
    vp.X = (DWORD)rectCopy.left_;
    vp.Y = (DWORD)rectCopy.top_;
    vp.Width = (DWORD)rectCopy.Width();
    vp.Height = (DWORD)rectCopy.Height();

    impl_->device_->SetViewport(&vp);
    viewport_ = rectCopy;

    // Disable scissor test, needs to be re-enabled by the user
    SetScissorTest(false);
}

void Graphics::SetBlendMode(BlendMode mode, bool /* alphaToCoverage */)
{
    if (mode != blendMode_)
    {
        if (d3dBlendEnable[mode] != impl_->blendEnable_)
        {
            impl_->device_->SetRenderState(D3DRS_ALPHABLENDENABLE, d3dBlendEnable[mode]);
            impl_->blendEnable_ = d3dBlendEnable[mode];
        }

        if (impl_->blendEnable_)
        {
            if (d3dSrcBlend[mode] != impl_->srcBlend_)
            {
                impl_->device_->SetRenderState(D3DRS_SRCBLEND, d3dSrcBlend[mode]);
                impl_->srcBlend_ = d3dSrcBlend[mode];
            }
            if (d3dDestBlend[mode] != impl_->destBlend_)
            {
                impl_->device_->SetRenderState(D3DRS_DESTBLEND, d3dDestBlend[mode]);
                impl_->destBlend_ = d3dDestBlend[mode];
            }
            if (d3dBlendOp[mode] != impl_->blendOp_)
            {
                impl_->device_->SetRenderState(D3DRS_BLENDOP, d3dBlendOp[mode]);
                impl_->blendOp_ = d3dBlendOp[mode];
            }
        }

        blendMode_ = mode;
    }
}

void Graphics::SetColorWrite(bool enable)
{
    if (enable != colorWrite_)
    {
        impl_->device_->SetRenderState(D3DRS_COLORWRITEENABLE,
            enable ? D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA :
                0);
        colorWrite_ = enable;
    }
}

void Graphics::SetCullMode(CullMode mode)
{
    if (mode != cullMode_)
    {
        impl_->device_->SetRenderState(D3DRS_CULLMODE, d3dCullMode[mode]);
        cullMode_ = mode;
    }
}

void Graphics::SetDepthBias(float constantBias, float slopeScaledBias)
{
    if (constantBias != constantDepthBias_)
    {
        impl_->device_->SetRenderState(D3DRS_DEPTHBIAS, *((DWORD*)&constantBias));
        constantDepthBias_ = constantBias;
    }
    if (slopeScaledBias != slopeScaledDepthBias_)
    {
        impl_->device_->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, *((DWORD*)&slopeScaledBias));
        slopeScaledDepthBias_ = slopeScaledBias;
    }
}

void Graphics::SetDepthTest(CompareMode mode)
{
    if (mode != depthTestMode_)
    {
        impl_->device_->SetRenderState(D3DRS_ZFUNC, d3dCmpFunc[mode]);
        depthTestMode_ = mode;
    }
}

void Graphics::SetDepthWrite(bool enable)
{
    if (enable != depthWrite_)
    {
        impl_->device_->SetRenderState(D3DRS_ZWRITEENABLE, enable ? TRUE : FALSE);
        depthWrite_ = enable;
    }
}

void Graphics::SetFillMode(FillMode mode)
{
    if (mode != fillMode_)
    {
        impl_->device_->SetRenderState(D3DRS_FILLMODE, d3dFillMode[mode]);
        fillMode_ = mode;
    }
}

void Graphics::SetLineAntiAlias(bool enable)
{
    if (enable != lineAntiAlias_)
    {
        impl_->device_->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, enable ? TRUE : FALSE);
        lineAntiAlias_ = enable;
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

        if (enable && scissorRect_ != intRect)
        {
            RECT d3dRect;
            d3dRect.left = intRect.left_;
            d3dRect.top = intRect.top_;
            d3dRect.right = intRect.right_;
            d3dRect.bottom = intRect.bottom_;

            impl_->device_->SetScissorRect(&d3dRect);
            scissorRect_ = intRect;
        }
    }
    else
        scissorRect_ = IntRect::ZERO;

    if (enable != scissorTest_)
    {
        impl_->device_->SetRenderState(D3DRS_SCISSORTESTENABLE, enable ? TRUE : FALSE);
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
            RECT d3dRect;
            d3dRect.left = intRect.left_;
            d3dRect.top = intRect.top_;
            d3dRect.right = intRect.right_;
            d3dRect.bottom = intRect.bottom_;

            impl_->device_->SetScissorRect(&d3dRect);
            scissorRect_ = intRect;
        }
    }
    else
        scissorRect_ = IntRect::ZERO;

    if (enable != scissorTest_)
    {
        impl_->device_->SetRenderState(D3DRS_SCISSORTESTENABLE, enable ? TRUE : FALSE);
        scissorTest_ = enable;
    }
}

void Graphics::SetStencilTest(bool enable, CompareMode mode, StencilOp pass, StencilOp fail, StencilOp zFail, unsigned stencilRef,
    unsigned compareMask, unsigned writeMask)
{
    if (enable != stencilTest_)
    {
        impl_->device_->SetRenderState(D3DRS_STENCILENABLE, enable ? TRUE : FALSE);
        stencilTest_ = enable;
    }

    if (enable)
    {
        if (mode != stencilTestMode_)
        {
            impl_->device_->SetRenderState(D3DRS_STENCILFUNC, d3dCmpFunc[mode]);
            stencilTestMode_ = mode;
        }
        if (pass != stencilPass_)
        {
            impl_->device_->SetRenderState(D3DRS_STENCILPASS, d3dStencilOp[pass]);
            stencilPass_ = pass;
        }
        if (fail != stencilFail_)
        {
            impl_->device_->SetRenderState(D3DRS_STENCILFAIL, d3dStencilOp[fail]);
            stencilFail_ = fail;
        }
        if (zFail != stencilZFail_)
        {
            impl_->device_->SetRenderState(D3DRS_STENCILZFAIL, d3dStencilOp[zFail]);
            stencilZFail_ = zFail;
        }
        if (stencilRef != stencilRef_)
        {
            impl_->device_->SetRenderState(D3DRS_STENCILREF, stencilRef);
            stencilRef_ = stencilRef;
        }
        if (compareMask != stencilCompareMask_)
        {
            impl_->device_->SetRenderState(D3DRS_STENCILMASK, compareMask);
            stencilCompareMask_ = compareMask;
        }
        if (writeMask != stencilWriteMask_)
        {
            impl_->device_->SetRenderState(D3DRS_STENCILWRITEMASK, writeMask);
            stencilWriteMask_ = writeMask;
        }
    }
}

void Graphics::SetClipPlane(bool enable, const Plane& clipPlane, const Matrix3x4& view, const Matrix4& projection)
{
    if (enable != useClipPlane_)
    {
        impl_->device_->SetRenderState(D3DRS_CLIPPLANEENABLE, enable ? 1 : 0);
        useClipPlane_ = enable;
    }

    if (enable)
    {
        Matrix4 viewProj = projection * view;
        impl_->device_->SetClipPlane(0, clipPlane.Transformed(viewProj).ToVector4().Data());
    }
}

bool Graphics::IsInitialized() const
{
    return window_ != nullptr && impl_->GetDevice() != nullptr;
}

PODVector<int> Graphics::GetMultiSampleLevels() const
{
    PODVector<int> ret;
    // No multisampling always supported
    ret.Push(1);

    if (!impl_->interface_)
        return ret;

    SDL_DisplayMode mode;
    SDL_GetDesktopDisplayMode(0, &mode);
    D3DFORMAT fullscreenFormat = SDL_BITSPERPIXEL(mode.format) == 16 ? D3DFMT_R5G6B5 : D3DFMT_X8R8G8B8;

    for (int i = (int)D3DMULTISAMPLE_2_SAMPLES; i < (int)D3DMULTISAMPLE_16_SAMPLES; ++i)
    {
        if (impl_->CheckMultiSampleSupport(fullscreenFormat, i))
            ret.Push(i);
    }

    return ret;
}

unsigned Graphics::GetFormat(CompressedFormat format) const
{
    switch (format)
    {
    case CF_RGBA:
        return D3DFMT_A8R8G8B8;

    case CF_DXT1:
        return D3DFMT_DXT1;

    case CF_DXT3:
        return D3DFMT_DXT3;

    case CF_DXT5:
        return D3DFMT_DXT5;

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
            return nullptr;

        lastShader_ = cache->GetResource<Shader>(fullShaderName);
        lastShaderName_ = name;
    }

    return lastShader_ ? lastShader_->GetVariation(type, defines) : nullptr;
}

VertexBuffer* Graphics::GetVertexBuffer(unsigned index) const
{
    return index < MAX_VERTEX_STREAMS ? vertexBuffers_[index] : nullptr;
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
    return index < MAX_TEXTURE_UNITS ? textures_[index] : nullptr;
}

RenderSurface* Graphics::GetRenderTarget(unsigned index) const
{
    return index < MAX_RENDERTARGETS ? renderTargets_[index] : nullptr;
}

IntVector2 Graphics::GetRenderTargetDimensions() const
{
    int width, height;

    if (renderTargets_[0])
    {
        width = renderTargets_[0]->GetWidth();
        height = renderTargets_[0]->GetHeight();
    }
    else
    {
        width = width_;
        height = height_;
    }

    return IntVector2(width, height);
}

bool Graphics::GetDither() const
{
    return false;
}

bool Graphics::IsDeviceLost() const
{
    return impl_->deviceLost_;
}

void Graphics::OnWindowResized()
{
    if (!impl_->device_ || !window_)
        return;

    int newWidth, newHeight;

    SDL_GetWindowSize(window_, &newWidth, &newHeight);
    if (newWidth == width_ && newHeight == height_)
        return;

    width_ = newWidth;
    height_ = newHeight;

    impl_->presentParams_.BackBufferWidth = (UINT)width_;
    impl_->presentParams_.BackBufferHeight = (UINT)height_;
    ResetDevice();

    // Reset rendertargets and viewport for the new screen size
    ResetRenderTargets();

    URHO3D_LOGDEBUGF("Window was resized to %dx%d", width_, height_);

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

void Graphics::OnWindowMoved()
{
    if (!impl_->device_ || !window_ || screenParams_.fullscreen_)
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

void Graphics::CleanupShaderPrograms(ShaderVariation* variation)
{
    for (ShaderProgramMap::Iterator i = impl_->shaderPrograms_.Begin(); i != impl_->shaderPrograms_.End();)
    {
        if (i->first_.first_ == variation || i->first_.second_ == variation)
            i = impl_->shaderPrograms_.Erase(i);
        else
            ++i;
    }

    if (vertexShader_ == variation || pixelShader_ == variation)
        impl_->shaderProgram_ = nullptr;
}

unsigned Graphics::GetAlphaFormat()
{
    return D3DFMT_A8;
}

unsigned Graphics::GetLuminanceFormat()
{
    return D3DFMT_L8;
}

unsigned Graphics::GetLuminanceAlphaFormat()
{
    return D3DFMT_A8L8;
}

unsigned Graphics::GetRGBFormat()
{
    return D3DFMT_X8R8G8B8;
}

unsigned Graphics::GetRGBAFormat()
{
    return D3DFMT_A8R8G8B8;
}

unsigned Graphics::GetRGBA16Format()
{
    return D3DFMT_A16B16G16R16;
}

unsigned Graphics::GetRGBAFloat16Format()
{
    return D3DFMT_A16B16G16R16F;
}

unsigned Graphics::GetRGBAFloat32Format()
{
    return D3DFMT_A32B32G32R32F;
}

unsigned Graphics::GetRG16Format()
{
    return D3DFMT_G16R16;
}

unsigned Graphics::GetRGFloat16Format()
{
    return D3DFMT_G16R16F;
}

unsigned Graphics::GetRGFloat32Format()
{
    return D3DFMT_G32R32F;
}

unsigned Graphics::GetFloat16Format()
{
    return D3DFMT_R16F;
}

unsigned Graphics::GetFloat32Format()
{
    return D3DFMT_R32F;
}

unsigned Graphics::GetLinearDepthFormat()
{
    return D3DFMT_R32F;
}

unsigned Graphics::GetDepthStencilFormat()
{
    return D3DFMT_D24S8;
}

unsigned Graphics::GetReadableDepthFormat()
{
    return readableDepthFormat;
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

unsigned Graphics::GetMaxBones()
{
    return 64;
}

bool Graphics::GetGL3Support()
{
    return gl3Support;
}

void Graphics::SetStreamFrequency(unsigned index, unsigned frequency)
{
    if (index < MAX_VERTEX_STREAMS && impl_->streamFrequencies_[index] != frequency)
    {
        impl_->device_->SetStreamSourceFreq(index, frequency);
        impl_->streamFrequencies_[index] = frequency;
    }
}

void Graphics::ResetStreamFrequencies()
{
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        if (impl_->streamFrequencies_[i] != 1)
        {
            impl_->device_->SetStreamSourceFreq(i, 1);
            impl_->streamFrequencies_[i] = 1;
        }
    }
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

        window_ = SDL_CreateWindow(windowTitle_.CString(), position_.x_, position_.y_, width, height, flags);
    }
    else
        window_ = SDL_CreateWindowFrom(externalWindow_, 0);

    if (!window_)
    {
        URHO3D_LOGERRORF("Could not create window, root cause: '%s'", SDL_GetError());
        return false;
    }

    SDL_GetWindowPosition(window_, &position_.x_, &position_.y_);

    CreateWindowIcon();

    return true;
}

void Graphics::AdjustWindow(int& newWidth, int& newHeight, bool& newFullscreen, bool& newBorderless, int& monitor)
{
    if (!externalWindow_)
    {
        // Keep current window position because it may change in intermediate callbacks
        const IntVector2 oldPosition = position_;
        bool reposition = false;
        bool resizePostponed = false;
        if (!newWidth || !newHeight)
        {
            SDL_MaximizeWindow(window_);
            SDL_GetWindowSize(window_, &newWidth, &newHeight);
        }
        else {
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(monitor, &display_rect);

            reposition = newFullscreen || (newBorderless && newWidth >= display_rect.w && newHeight >= display_rect.h);
            if (reposition)
            {
                // Reposition the window on the specified monitor if it's supposed to cover the entire monitor
                SDL_SetWindowPosition(window_, display_rect.x, display_rect.y);
            }

            // Postpone window resize if exiting fullscreen to avoid redundant resolution change
            if (!newFullscreen && screenParams_.fullscreen_)
                resizePostponed = true;
            else
                SDL_SetWindowSize(window_, newWidth, newHeight);
        }

        // Hack fix: on SDL 2.0.4 a fullscreen->windowed transition results in a maximized window when the D3D device is reset, so hide before
        if (!newFullscreen) SDL_HideWindow(window_);
        SDL_SetWindowFullscreen(window_, newFullscreen ? SDL_WINDOW_FULLSCREEN : 0);
        SDL_SetWindowBordered(window_, newBorderless ? SDL_FALSE : SDL_TRUE);
        if (!newFullscreen) SDL_ShowWindow(window_);

        // Resize now if was postponed
        if (resizePostponed)
            SDL_SetWindowSize(window_, newWidth, newHeight);

        // Ensure that window keeps its position
        if (!reposition)
            SDL_SetWindowPosition(window_, oldPosition.x_, oldPosition.y_);
        else
            position_ = oldPosition;
    }
    else
    {
        // If external window, must ask its dimensions instead of trying to set them
        SDL_GetWindowSize(window_, &newWidth, &newHeight);
        newFullscreen = false;
    }
}

bool Graphics::CreateInterface()
{
    impl_->interface_ = Direct3DCreate9(D3D_SDK_VERSION);
    if (!impl_->interface_)
    {
        URHO3D_LOGERROR("Could not create Direct3D9 interface");
        return false;
    }

    HRESULT hr = impl_->interface_->GetDeviceCaps(impl_->adapter_, impl_->deviceType_, &impl_->deviceCaps_);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Could not get Direct3D capabilities", hr);
        return false;
    }

    hr = impl_->interface_->GetAdapterIdentifier(impl_->adapter_, 0, &impl_->adapterIdentifier_);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Could not get Direct3D adapter identifier", hr);
        return false;
    }

    if (impl_->deviceCaps_.PixelShaderVersion < D3DPS_VERSION(3, 0))
    {
        URHO3D_LOGERROR("Shader model 3.0 display adapter is required");
        return false;
    }

    return true;
}

bool Graphics::CreateDevice(unsigned adapter, unsigned deviceType)
{
#ifdef URHO3D_LUAJIT
    DWORD behaviorFlags = D3DCREATE_FPU_PRESERVE;
#else
    DWORD behaviorFlags = 0;
#endif
    if (impl_->deviceCaps_.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
    {
        behaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
        if (impl_->deviceCaps_.DevCaps & D3DDEVCAPS_PUREDEVICE)
            behaviorFlags |= D3DCREATE_PUREDEVICE;
    }
    else
        behaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

    HRESULT hr = impl_->interface_->CreateDevice(
        adapter,
        (D3DDEVTYPE)deviceType,
        GetWindowHandle(window_),
        behaviorFlags,
        &impl_->presentParams_,
        &impl_->device_);
    if (FAILED(hr))
    {
        URHO3D_LOGD3DERROR("Could not create Direct3D9 device", hr);
        return false;
    }

    impl_->adapter_ = adapter;
    impl_->deviceType_ = (D3DDEVTYPE)deviceType;

    OnDeviceReset();

    URHO3D_LOGINFO("Created Direct3D9 device");
    return true;
}

void Graphics::CheckFeatureSupport()
{
    anisotropySupport_ = true;
    dxtTextureSupport_ = true;

    // Reset features first
    lightPrepassSupport_ = false;
    deferredSupport_ = false;
    hardwareShadowSupport_ = false;
    instancingSupport_ = false;
    readableDepthFormat = 0;

    // Check hardware shadow map support: prefer NVIDIA style hardware depth compared shadow maps if available
    shadowMapFormat_ = D3DFMT_D16;
    if (impl_->CheckFormatSupport((D3DFORMAT)shadowMapFormat_, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE))
    {
        hardwareShadowSupport_ = true;

        // Check for hires depth support
        hiresShadowMapFormat_ = D3DFMT_D24X8;
        if (!impl_->CheckFormatSupport((D3DFORMAT)hiresShadowMapFormat_, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE))
            hiresShadowMapFormat_ = 0;
    }
    else
    {
        // ATI DF16 format needs manual depth compare in the shader
        shadowMapFormat_ = MAKEFOURCC('D', 'F', '1', '6');
        if (impl_->CheckFormatSupport((D3DFORMAT)shadowMapFormat_, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE))
        {
            // Check for hires depth support
            hiresShadowMapFormat_ = MAKEFOURCC('D', 'F', '2', '4');
            if (!impl_->CheckFormatSupport((D3DFORMAT)hiresShadowMapFormat_, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE))
                hiresShadowMapFormat_ = 0;
        }
        else
        {
            // No shadow map support
            shadowMapFormat_ = 0;
            hiresShadowMapFormat_ = 0;
        }
    }

    // Check for Intel 4 Series with an old driver, enable manual shadow map compare in that case
    if (shadowMapFormat_ == D3DFMT_D16)
    {
        if (impl_->adapterIdentifier_.VendorId == 0x8086 && impl_->adapterIdentifier_.DeviceId == 0x2a42 &&
            impl_->adapterIdentifier_.DriverVersion.QuadPart <= 0x0007000f000a05d0ULL)
            hardwareShadowSupport_ = false;
    }

    // Check for readable depth (INTZ hack)
    D3DFORMAT intZFormat = (D3DFORMAT)MAKEFOURCC('I', 'N', 'T', 'Z');
    if (impl_->CheckFormatSupport(intZFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE))
        readableDepthFormat = intZFormat;

    // Check for dummy color rendertarget format used with hardware shadow maps
    dummyColorFormat_ = D3DFMT_A8R8G8B8;
    D3DFORMAT nullFormat = (D3DFORMAT)MAKEFOURCC('N', 'U', 'L', 'L');
    if (impl_->CheckFormatSupport(nullFormat, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE))
        dummyColorFormat_ = nullFormat;
    else if (impl_->CheckFormatSupport(D3DFMT_R16F, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE))
        dummyColorFormat_ = D3DFMT_R16F;
    else if (impl_->CheckFormatSupport(D3DFMT_R5G6B5, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE))
        dummyColorFormat_ = D3DFMT_R5G6B5;
    else if (impl_->CheckFormatSupport(D3DFMT_A4R4G4B4, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE))
        dummyColorFormat_ = D3DFMT_A4R4G4B4;

    // Check for light prepass and deferred rendering support
    if (impl_->deviceCaps_.NumSimultaneousRTs >= 2 && impl_->CheckFormatSupport(D3DFMT_R32F, D3DUSAGE_RENDERTARGET,
        D3DRTYPE_TEXTURE))
    {
        lightPrepassSupport_ = true;
        if (impl_->deviceCaps_.NumSimultaneousRTs >= 4)
            deferredSupport_ = true;
    }

    // Check for stream offset (needed for instancing)
    if (impl_->deviceCaps_.DevCaps2 & D3DDEVCAPS2_STREAMOFFSET)
        instancingSupport_ = true;

    // Check for sRGB read & write
    /// \todo Should be checked for each texture format separately
    sRGBSupport_ = impl_->CheckFormatSupport(D3DFMT_X8R8G8B8, D3DUSAGE_QUERY_SRGBREAD, D3DRTYPE_TEXTURE);
    sRGBWriteSupport_ = impl_->CheckFormatSupport(D3DFMT_X8R8G8B8, D3DUSAGE_QUERY_SRGBWRITE, D3DRTYPE_TEXTURE);
}

void Graphics::ResetDevice()
{
    OnDeviceLost();

    if (SUCCEEDED(impl_->device_->Reset(&impl_->presentParams_)))
    {
        impl_->deviceLost_ = false;
        OnDeviceReset();
    }
}

void Graphics::OnDeviceLost()
{
    URHO3D_LOGINFO("Device lost");

    if (impl_->defaultColorSurface_)
    {
        impl_->defaultColorSurface_->Release();
        impl_->defaultColorSurface_ = nullptr;
    }
    if (impl_->defaultDepthStencilSurface_)
    {
        impl_->defaultDepthStencilSurface_->Release();
        impl_->defaultDepthStencilSurface_ = nullptr;
    }
    if (impl_->frameQuery_)
    {
        impl_->frameQuery_->Release();
        impl_->frameQuery_ = nullptr;
    }

    {
        MutexLock lock(gpuObjectMutex_);

        for (PODVector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
            (*i)->OnDeviceLost();
    }

    SendEvent(E_DEVICELOST);
}

void Graphics::OnDeviceReset()
{
    {
        MutexLock lock(gpuObjectMutex_);

        for (PODVector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
            (*i)->OnDeviceReset();
    }

    // Get default surfaces
    impl_->device_->GetRenderTarget(0, &impl_->defaultColorSurface_);
    impl_->device_->GetDepthStencilSurface(&impl_->defaultDepthStencilSurface_);

    // Create frame query for flushing the GPU command buffer
    impl_->device_->CreateQuery(D3DQUERYTYPE_EVENT, &impl_->frameQuery_);

    ResetCachedState();

    SendEvent(E_DEVICERESET);
}

void Graphics::ResetCachedState()
{
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        vertexBuffers_[i] = nullptr;
        impl_->streamOffsets_[i] = 0;
    }

    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
    {
        textures_[i] = nullptr;
        impl_->minFilters_[i] = D3DTEXF_POINT;
        impl_->magFilters_[i] = D3DTEXF_POINT;
        impl_->mipFilters_[i] = D3DTEXF_NONE;
        impl_->uAddressModes_[i] = D3DTADDRESS_WRAP;
        impl_->vAddressModes_[i] = D3DTADDRESS_WRAP;
        impl_->wAddressModes_[i] = D3DTADDRESS_WRAP;
        impl_->maxAnisotropy_[i] = M_MAX_UNSIGNED;
        impl_->borderColors_[i] = Color(0.0f, 0.0f, 0.0f, 0.0f);
        impl_->sRGBModes_[i] = false;
    }

    for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
    {
        renderTargets_[i] = nullptr;
        impl_->colorSurfaces_[i] = nullptr;
    }

    depthStencil_ = nullptr;
    impl_->depthStencilSurface_ = nullptr;
    viewport_ = IntRect(0, 0, width_, height_);
    impl_->sRGBWrite_ = false;

    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
        impl_->streamFrequencies_[i] = 1;

    indexBuffer_ = nullptr;
    vertexShader_ = nullptr;
    pixelShader_ = nullptr;
    blendMode_ = BLEND_REPLACE;
    alphaToCoverage_ = false;
    colorWrite_ = true;
    cullMode_ = CULL_CCW;
    constantDepthBias_ = 0.0f;
    slopeScaledDepthBias_ = 0.0f;
    depthTestMode_ = CMP_LESSEQUAL;
    depthWrite_ = true;
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
    impl_->blendEnable_ = FALSE;
    impl_->srcBlend_ = D3DBLEND_ONE;
    impl_->destBlend_ = D3DBLEND_ZERO;
    impl_->blendOp_ = D3DBLENDOP_ADD;
    impl_->vertexDeclaration_ = nullptr;
    impl_->queryIssued_ = false;
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

}
