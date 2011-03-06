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
#include "Geometry.h"
#include "IndexBuffer.h"
#include "Log.h"
#include "Matrix4x3.h"
#include "PixelShader.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererEvents.h"
#include "RendererImpl.h"
#include "StringUtils.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "VertexBuffer.h"
#include "VertexDeclaration.h"
#include "VertexShader.h"

#include <cstring>

#include "DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

static const DWORD windowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;

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

// These are for optimizing the case where user supplies a single vertex buffer in setVertexBuffer()
std::vector<VertexBuffer*> vertexBuffers;
std::vector<unsigned> elementMasks;

std::map<HWND, Renderer*> renderers;

static LRESULT CALLBACK wndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

Renderer::Renderer(const std::string& windowTitle) :
    mImpl(new RendererImpl()),
    mTitle(windowTitle),
    mMode(RENDER_FORWARD),
    mWidth(0),
    mHeight(0),
    mMultiSample(0),
    mWindowPosX(0),
    mWindowPosY(0),
    mFullscreen(false),
    mVsync(false),
    mClosed(false),
    mDeviceLost(false),
    mQueryIssued(false),
    mSystemDepthStencil(false),
    mDeferredSupport(false),
    mPrepassSupport(false),
    mSM3Support(false),
    mHardwareDepthSupport(false),
    mHardwareShadowSupport(false),
    mHiresShadowSupport(false),
    mForceSM2(false),
    mNumPrimitives(0),
    mNumBatches(0),
    mImmediateBuffer(0),
    mDefaultTextureFilterMode(FILTER_BILINEAR)
{
    LOGINFO("Renderer created");
    
    resetCachedState();
    
    vertexBuffers.resize(1);
    elementMasks.resize(1);
    elementMasks[0] = MASK_DEFAULT;
    
    subscribeToEvent(EVENT_WINDOWMESSAGE, EVENT_HANDLER(Renderer, handleWindowMessage));
}

Renderer::~Renderer()
{
    mVertexDeclarations.clear();
    
    if (mImpl->mFrameQuery)
    {
        mImpl->mFrameQuery->Release();
        mImpl->mFrameQuery = 0;
    }
    if (mImpl->mDefaultColorSurface)
    {
        mImpl->mDefaultColorSurface->Release();
        mImpl->mDefaultColorSurface = 0;
    }
    if (mImpl->mDefaultDepthStencilSurface)
    {
        if (mSystemDepthStencil)
            mImpl->mDefaultDepthStencilSurface->Release();
        mImpl->mDefaultDepthStencilSurface = 0;
    }
    
    if (mImpl->mDevice)
    {
        mImpl->mDevice->Release();
        mImpl->mDevice = 0;
    }
    if (mImpl->mInterface)
    {
        mImpl->mInterface->Release();
        mImpl->mInterface = 0;
    }
    if (mImpl->mWindow)
    {
        DestroyWindow(mImpl->mWindow);
        renderers.erase(mImpl->mWindow);
        mImpl->mWindow = 0;
    }
    
    delete mImpl;
    mImpl = 0;
    
    LOGINFO("Renderer shut down");
}

void Renderer::messagePump()
{
    MSG msg;
    
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        
        if (msg.message == WM_QUIT)
            mClosed = true;
    }
}

void Renderer::setMode(RenderMode mode, int width, int height, bool fullscreen, bool vsync, int multiSample)
{
    // Find out the full screen mode display format (match desktop color depth)
    D3DFORMAT fullscreenFormat = mImpl->getDesktopFormat();
    
    // If zero dimensions, use the desktop default
    if ((width <= 0) || (height <= 0))
    {
        if (fullscreen)
        {
            IntVector2 desktopResolution = mImpl->getDesktopResolution();
            width = desktopResolution.mX;
            height = desktopResolution.mY;
        }
        else
        {
            width = 640;
            height = 480;
        }
    }
    
    if ((mode == mMode) && (width == mWidth) && (height == mHeight) && (fullscreen == mFullscreen) && (vsync == mVsync)
        && (multiSample == mMultiSample))
        return;
    
    if (!mImpl->mWindow)
        createWindow(width, height);
    
    if (!mImpl->mInterface)
        createInterface();
    
    // Disable deferred / light prepass rendering if not supported
    // Note: we do not fall back from deferred to light prepass, because there might not be shaders / materials
    // defined for it. Instead fall back directly to forward rendering
    if ((mode == RENDER_DEFERRED) && (!mDeferredSupport))
        mode = RENDER_FORWARD;
    if ((mode == RENDER_PREPASS) && (!mPrepassSupport))
        mode = RENDER_FORWARD;
    
    if (multiSample >= (int)D3DMULTISAMPLE_2_SAMPLES)
        multiSample = clamp(multiSample, (int)D3DMULTISAMPLE_NONE, (int)D3DMULTISAMPLE_16_SAMPLES);
    else
        multiSample = 0;
    // Note: getMultiSample() will not reflect the actual hardware multisample mode, but rather what the caller wanted.
    // In deferred or light prepass mode, it is used to control the edge filter
    mMultiSample = multiSample;
    if (mode != RENDER_FORWARD)
        multiSample = 0;
    
    // Check fullscreen mode validity. If not valid, revert to windowed
    if (fullscreen)
    {
        std::vector<IntVector2> resolutions = getResolutions();
        fullscreen = false;
        for (unsigned i = 0; i < resolutions.size(); ++i)
        {
            if ((width == resolutions[i].mX) && (height == resolutions[i].mY))
            {
                fullscreen = true;
                break;
            }
        }
    }
    
    // Fall back to non-multisampled if unsupported multisampling mode
    if (multiSample)
    {
        if (FAILED(mImpl->mInterface->CheckDeviceMultiSampleType(mImpl->mAdapter, mImpl->mDeviceType, fullscreenFormat, FALSE,
            (D3DMULTISAMPLE_TYPE)multiSample, NULL)))
            multiSample = 0;
    }
    
    // Save window placement if currently windowed
    if (!mFullscreen)
    {
        WINDOWPLACEMENT wndpl;
        wndpl.length = sizeof wndpl;
        if (SUCCEEDED(GetWindowPlacement(mImpl->mWindow, &wndpl)))
        {
            mWindowPosX = wndpl.rcNormalPosition.left;
            mWindowPosY = wndpl.rcNormalPosition.top;
        }
    }
    
    if (fullscreen)
    {
        mImpl->mPresentParams.BackBufferFormat = fullscreenFormat;
        mImpl->mPresentParams.Windowed         = false;
    }
    else
    {
        mImpl->mPresentParams.BackBufferFormat = D3DFMT_UNKNOWN;
        mImpl->mPresentParams.Windowed         = true;
    }
    
    // Use autodepthstencil normally. However, if INTZ depth is available and deferred rendering is enabled,
    // create a depth texture instead
    bool autoDepthStencil = true;
    if ((mode != RENDER_FORWARD) && (mHardwareDepthSupport))
        autoDepthStencil = false;
    
    mImpl->mPresentParams.BackBufferWidth            = width;
    mImpl->mPresentParams.BackBufferHeight           = height;
    mImpl->mPresentParams.BackBufferCount            = 1;
    mImpl->mPresentParams.MultiSampleType            = (D3DMULTISAMPLE_TYPE)multiSample;
    mImpl->mPresentParams.MultiSampleQuality         = 0;
    mImpl->mPresentParams.SwapEffect                 = D3DSWAPEFFECT_DISCARD;
    mImpl->mPresentParams.hDeviceWindow              = mImpl->mWindow;
    mImpl->mPresentParams.EnableAutoDepthStencil     = autoDepthStencil;
    mImpl->mPresentParams.AutoDepthStencilFormat     = D3DFMT_D24S8;
    mImpl->mPresentParams.Flags                      = 0;
    mImpl->mPresentParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

    if (vsync)
        mImpl->mPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    else
        mImpl->mPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    
    mWidth = width;
    mHeight = height;
    mFullscreen = fullscreen;
    mVsync = vsync;
    mMode = mode;
    
    if (!mImpl->mDevice)
    {
        unsigned adapter = D3DADAPTER_DEFAULT;
        unsigned deviceType = D3DDEVTYPE_HAL;
        
        // Check for PerfHUD adapter
        for (unsigned i=0; i < mImpl->mInterface->GetAdapterCount(); ++i)
        {
            D3DADAPTER_IDENTIFIER9 identifier;
            mImpl->mInterface->GetAdapterIdentifier(i, 0, &identifier);
            if (strstr(identifier.Description, "PerfHUD") != 0)
            {
                adapter = i;
                deviceType = D3DDEVTYPE_REF;
                break;
            }
        }
        
        mImpl->mInterface->GetAdapterIdentifier(adapter, 0, &mImpl->mAdapterIdentifier);
        createDevice(adapter, deviceType);
    }
    else
        resetDevice();
    
    // Adjust window style/size now
    if (fullscreen)
    {
        SetWindowLongPtr(mImpl->mWindow, GWL_STYLE, WS_POPUP);
        SetWindowPos(mImpl->mWindow, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);
    }
    else
    {
        RECT rect = {0, 0, width, height};
        AdjustWindowRect(&rect, windowStyle, false);
        SetWindowLongPtr(mImpl->mWindow, GWL_STYLE, windowStyle);
        SetWindowPos(mImpl->mWindow, HWND_TOP, mWindowPosX, mWindowPosY, rect.right - rect.left, rect.bottom - rect.top,
            SWP_NOZORDER | SWP_SHOWWINDOW);
        
        // Clean up the desktop of the old window contents
        InvalidateRect(0, 0, true);
    }
    
    using namespace ScreenMode;
    
    VariantMap eventData;
    eventData[P_WIDTH] = mWidth;
    eventData[P_HEIGHT] = mHeight;
    eventData[P_FULLSCREEN] = mFullscreen;
    sendEvent(EVENT_SCREENMODE, eventData);
    
    if (!multiSample)
        LOGINFO("Set screen mode " + toString(mWidth) + "x" + toString(mHeight) + " " + (mFullscreen ? "fullscreen" : "windowed"));
    else
        LOGINFO("Set screen mode " + toString(mWidth) + "x" + toString(mHeight) + " " + (mFullscreen ? "fullscreen" : "windowed") +
        " multisample " + toString(multiSample));
}

void Renderer::toggleFullscreen()
{
    setMode(mMode, mWidth, mHeight, !mFullscreen, mVsync, mMultiSample);
}

void Renderer::close()
{
    if (mImpl->mWindow)
    {
        mDiffBuffer.reset();
        mNormalBuffer.reset();
        mDepthBuffer.reset();
        mImmediateVertexBuffers.clear();
        
        DestroyWindow(mImpl->mWindow);
        renderers.erase(mImpl->mWindow);
        mImpl->mWindow = 0;
        mClosed = true;
    }
}

bool Renderer::takeScreenShot(Image& destImage)
{
    PROFILE(Renderer_TakeScreenShot);
    
    if (!mImpl->mDevice)
        return false;
    
    D3DSURFACE_DESC surfaceDesc;
    mImpl->mDefaultColorSurface->GetDesc(&surfaceDesc);
    
    // If possible, get the backbuffer data, because it is a lot faster.
    // However, if we are multisampled, need to use the front buffer
    bool useBackBuffer = true;
    if (mImpl->mPresentParams.MultiSampleType)
    {
        useBackBuffer = false;
        surfaceDesc.Format = D3DFMT_A8R8G8B8;
    }
    
    IDirect3DSurface9* surface = 0;
    mImpl->mDevice->CreateOffscreenPlainSurface(mWidth, mHeight, surfaceDesc.Format, D3DPOOL_SYSTEMMEM, &surface, 0);
    if (!surface)
        return false;
    
    if (useBackBuffer)
        mImpl->mDevice->GetRenderTargetData(mImpl->mDefaultColorSurface, surface);
    else
        mImpl->mDevice->GetFrontBufferData(0, surface);
    
    D3DLOCKED_RECT lockedRect;
    lockedRect.pBits = 0;
    surface->LockRect(&lockedRect, 0, D3DLOCK_NOSYSLOCK | D3DLOCK_READONLY);
    if (!lockedRect.pBits)
    {
        surface->Release();
        return false;
    }
    
    destImage.setSize(mWidth, mHeight, 3);
    unsigned char* destData = destImage.getData();
    
    if (surfaceDesc.Format == D3DFMT_R5G6B5)
    {
        for (int y = 0; y < mHeight; ++y)
        {
            unsigned short* src = (unsigned short*)((unsigned char*)lockedRect.pBits + y * lockedRect.Pitch);
            unsigned char* dest = destData + y * mWidth * 3;
            
            for (int x = 0; x < mWidth; ++x)
            {
                unsigned short rgb = *src++;
                int b = rgb & 31;
                int g = (rgb >> 5) & 63;
                int r = (rgb >> 11);
                
                *dest++ = (int)(r * 255.0f / 31.0f);
                *dest++ = (int)(g * 255.0f / 63.0f);
                *dest++ = (int)(b * 255.0f / 31.0f);
            }
        }
    }
    else
    {
        for (int y = 0; y < mHeight; ++y)
        {
            unsigned char* src = (unsigned char*)lockedRect.pBits + y * lockedRect.Pitch;
            unsigned char* dest = destData + y * mWidth * 3;
            
            for (int x = 0; x < mWidth; ++x)
            {
                *dest++ = src[2];
                *dest++ = src[1];
                *dest++ = src[0];
                src += 4;
            }
        }
    }
    
    surface->UnlockRect();
    surface->Release();
    
    return true;
}

bool Renderer::beginFrame()
{
    PROFILE(Renderer_BeginFrame);
    
    if (!mImpl->mDevice)
        EXCEPTION("Must have initial screen mode set before rendering");
    
    if (mClosed)
        return false;
    
    // Check for lost device before rendering
    HRESULT hr = mImpl->mDevice->TestCooperativeLevel();
    if (hr != D3D_OK)
    {
        mDeviceLost = true;
        
        // The device can not be reset yet, sleep and try again eventually
        if (hr == D3DERR_DEVICELOST)
        {
            Sleep(20);
            return false;
        }
        // The device is lost, but ready to be reset. Reset device but do not render on this frame yet
        if (hr == D3DERR_DEVICENOTRESET)
        {
            resetDevice();
            return false;
        }
    }
    
    mImpl->mDevice->BeginScene();
    
    // If a query was issued on the previous frame, wait for it to finish before beginning the next
    if ((mImpl->mFrameQuery) && (mQueryIssued))
    {
        while (mImpl->mFrameQuery->GetData(0, 0, D3DGETDATA_FLUSH) == S_FALSE)
        {
        }
        
        mQueryIssued = false;
    }
    
    // Set default rendertarget and depth buffer
    resetRenderTargets();
    mViewTexture = 0;
    
    // Cleanup textures from previous frame
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        setTexture(i, 0);
    
    // Cleanup stream frequencies from previous frame
    resetStreamFrequencies();
    
    // Reset immediate mode vertex buffer positions
    for (std::map<unsigned, unsigned>::iterator i = mImmediateVertexBufferPos.begin(); i != mImmediateVertexBufferPos.end(); ++i)
        i->second = 0;
    
    mNumPrimitives = 0;
    mNumBatches = 0;
    
    sendEvent(EVENT_BEGINFRAME);
    
    return true;
}

void Renderer::endFrame(bool flushCommands)
{
    PROFILE(Renderer_EndFrame);
    
    if (mClosed)
        return;
    
    sendEvent(EVENT_ENDFRAME);
    
    // Optionally flush GPU buffer to avoid control lag or framerate fluctuations due to pre-render
    if ((mImpl->mFrameQuery) && (flushCommands))
    {
        mImpl->mFrameQuery->Issue(D3DISSUE_END);
        mQueryIssued = true;
    }
    
    mImpl->mDevice->EndScene();
    mImpl->mDevice->Present(0, 0, 0, 0);
}

void Renderer::clear(unsigned flags, const Color& color, float depth, unsigned stencil)
{
    DWORD d3dFlags = 0;
    if (flags & CLEAR_COLOR)
        d3dFlags |= D3DCLEAR_TARGET;
    if (flags & CLEAR_DEPTH)
        d3dFlags |= D3DCLEAR_ZBUFFER;
    if (flags & CLEAR_STENCIL)
        d3dFlags |= D3DCLEAR_STENCIL;

    mImpl->mDevice->Clear(0, 0, d3dFlags, getD3DColor(color), depth, stencil);
}

void Renderer::draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount,
    unsigned instanceCount)
{
    if (!indexCount)
        return;
    
    unsigned primitiveCount = 0;
    
    switch (type)
    {
    case TRIANGLE_LIST:
        primitiveCount = indexCount / 3;
        mImpl->mDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, minVertex, vertexCount, indexStart, primitiveCount);
        break;
        
    case LINE_LIST:
        primitiveCount = indexCount / 2;
        mImpl->mDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0, minVertex, vertexCount, indexStart, primitiveCount);
        break;
    }
    
    mNumPrimitives += primitiveCount * instanceCount;
    mNumBatches++;
}

void Renderer::draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount, unsigned instanceCount)
{
    if (!vertexCount)
        return;
    
    unsigned primitiveCount;
    
    switch (type)
    {
    case TRIANGLE_LIST:
        primitiveCount = vertexCount / 3;
        mImpl->mDevice->DrawPrimitive(D3DPT_TRIANGLELIST, vertexStart, primitiveCount);
        break;
        
    case LINE_LIST:
        primitiveCount = vertexCount / 2;
        mImpl->mDevice->DrawPrimitive(D3DPT_LINELIST, vertexStart, primitiveCount);
        break;
    }
    
    mNumPrimitives += primitiveCount * instanceCount;
    mNumBatches++;
}

void Renderer::setVertexBuffer(VertexBuffer* buffer)
{
    vertexBuffers[0] = buffer;
    setVertexBuffers(vertexBuffers, elementMasks);
}

bool Renderer::setVertexBuffers(const std::vector<VertexBuffer*>& buffers, const std::vector<unsigned>& elementMasks)
{
    if (buffers.size() > MAX_VERTEX_STREAMS)
    {
        LOGERROR("Too many vertex buffers");
        return false;
    }
    if (buffers.size() != elementMasks.size())
    {
        LOGERROR("Amount of element masks and vertex buffers does not match");
        return false;
    }
    
    // Build vertex declaration hash code out of the buffers & masks
    unsigned long long hash = 0;
    for (unsigned i = 0; i < buffers.size(); ++i)
    {
        if (!buffers[i])
            continue;
        
        hash |= buffers[i]->getHash(i, elementMasks[i]);
    }
    
    if (hash)
    {
        // If no previous vertex declaration for that hash, create new
        if (mVertexDeclarations.find(hash) == mVertexDeclarations.end())
            mVertexDeclarations[hash] = new VertexDeclaration(this, buffers, elementMasks);
        
        VertexDeclaration* declaration = mVertexDeclarations[hash];
        if (declaration != mVertexDeclaration)
        {
            mImpl->mDevice->SetVertexDeclaration(declaration->getDeclaration());
            mVertexDeclaration = declaration;
        }
    }
    
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        VertexBuffer* buffer = 0;
        
        if (i < buffers.size())
            buffer = buffers[i];
        
        if (buffer != mVertexBuffer[i])
        {
            if (buffer)
                mImpl->mDevice->SetStreamSource(i, (IDirect3DVertexBuffer9*)buffer->getObject(), 0, buffer->getVertexSize());
            else
                mImpl->mDevice->SetStreamSource(i, 0, 0, 0);
            
            mVertexBuffer[i] = buffer;
        }
    }
    
    return true;
}

bool Renderer::setVertexBuffers(const std::vector<SharedPtr<VertexBuffer> >& buffers, const std::vector<unsigned>&
    elementMasks)
{
   if (buffers.size() > MAX_VERTEX_STREAMS)
    {
        LOGERROR("Too many vertex buffers");
        return false;
    }
    if (buffers.size() != elementMasks.size())
    {
        LOGERROR("Amount of element masks and vertex buffers does not match");
        return false;
    }
    
    // Build vertex declaration hash code out of the buffers & masks
    unsigned long long hash = 0;
    for (unsigned i = 0; i < buffers.size(); ++i)
    {
        if (!buffers[i])
            continue;
        
        hash |= buffers[i]->getHash(i, elementMasks[i]);
    }
    
    if (hash)
    {
        // If no previous vertex declaration for that hash, create new
        if (mVertexDeclarations.find(hash) == mVertexDeclarations.end())
            mVertexDeclarations[hash] = new VertexDeclaration(this, buffers, elementMasks);
        
        VertexDeclaration* declaration = mVertexDeclarations[hash];
        if (declaration != mVertexDeclaration)
        {
            mImpl->mDevice->SetVertexDeclaration(declaration->getDeclaration());
            mVertexDeclaration = declaration;
        }
    }
    
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        VertexBuffer* buffer = 0;
        
        if (i < buffers.size())
            buffer = buffers[i];
        
        if (buffer != mVertexBuffer[i])
        {
            if (buffer)
                mImpl->mDevice->SetStreamSource(i, (IDirect3DVertexBuffer9*)buffer->getObject(), 0, buffer->getVertexSize());
            else
                mImpl->mDevice->SetStreamSource(i, 0, 0, 0);
            
            mVertexBuffer[i] = buffer;
        }
    }
    
    return true;
}

void Renderer::setIndexBuffer(IndexBuffer* buffer)
{
    if (buffer != mIndexBuffer)
    {
        if (buffer)
            mImpl->mDevice->SetIndices((IDirect3DIndexBuffer9*)buffer->getObject());
        else
            mImpl->mDevice->SetIndices(0);
            
        mIndexBuffer = buffer;
    }
}

void Renderer::setVertexShader(VertexShader* shader)
{
    if (shader != mVertexShader)
    {
        if (shader)
            mImpl->mDevice->SetVertexShader((IDirect3DVertexShader9*)shader->getObject());
        else
            mImpl->mDevice->SetVertexShader(0);
            
        mVertexShader = shader;
    }
}

void Renderer::setVertexShaderConstant(unsigned index, const bool* data, unsigned count)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetVertexShaderConstantB(index, (const BOOL*)data, count);
}

void Renderer::setVertexShaderConstant(unsigned index, const float* data, unsigned count)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetVertexShaderConstantF(index, data, count / 4);
}

void Renderer::setVertexShaderConstant(unsigned index, const int* data, unsigned count)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetVertexShaderConstantI(index, data, count / 4);
}

void Renderer::setVertexShaderConstant(unsigned index, float value)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    static float data[4] = 
    {
        0.0f,
        0.0f,
        0.0f,
        0.0f
    };
    
    data[0] = value;
    
    mImpl->mDevice->SetVertexShaderConstantF(index, &data[0], 1);
}

void Renderer::setVertexShaderConstant(unsigned index, const Color& color)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetVertexShaderConstantF(index, color.getData(), 1);
}

void Renderer::setVertexShaderConstant(unsigned index, const Matrix3& matrix)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    static float data[12];
    
    data[0] = matrix.m00;
    data[1] = matrix.m01;
    data[2] = matrix.m02;
    data[3] = 0.0f;
    data[4] = matrix.m10;
    data[5] = matrix.m11;
    data[6] = matrix.m12;
    data[7] = 0.0f;
    data[8] = matrix.m20;
    data[9] = matrix.m21;
    data[10] = matrix.m22;
    data[11] = 0.0f;
    
    mImpl->mDevice->SetVertexShaderConstantF(index, &data[0], 3);
}

void Renderer::setVertexShaderConstant(unsigned index, const Vector3& vector)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    static float data[4] =
    {
        0.0f,
        0.0f,
        0.0f,
        0.0f
    };

    data[0] = vector.mX;
    data[1] = vector.mY;
    data[2] = vector.mZ;
    
    mImpl->mDevice->SetVertexShaderConstantF(index, &data[0], 1);
}

void Renderer::setVertexShaderConstant(unsigned index, const Matrix4& matrix)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetVertexShaderConstantF(index, matrix.getData(), 4);
}

void Renderer::setVertexShaderConstant(unsigned index, const Vector4& vector)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetVertexShaderConstantF(index, vector.getData(), 1);
}

void Renderer::setVertexShaderConstant(unsigned index, const Matrix4x3& matrix)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetVertexShaderConstantF(index, matrix.getData(), 3);
}

void Renderer::setPixelShader(PixelShader* shader)
{
    if (shader != mPixelShader)
    {
        if (shader)
            mImpl->mDevice->SetPixelShader((IDirect3DPixelShader9*)shader->getObject());
        else
            mImpl->mDevice->SetPixelShader(0);
        
        mPixelShader = shader;
    }
}

void Renderer::setPixelShaderConstant(unsigned index, const bool* data, unsigned count)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetPixelShaderConstantB(index, (const BOOL*)data, count);
}

void Renderer::setPixelShaderConstant(unsigned index, const float* data, unsigned count)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetPixelShaderConstantF(index, data, count / 4);
}

void Renderer::setPixelShaderConstant(unsigned index, const int* data, unsigned count)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetPixelShaderConstantI(index, data, count / 4);
}

void Renderer::setPixelShaderConstant(unsigned index, float value)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    static float data[4] =
    {
        0.0f,
        0.0f,
        0.0f,
        0.0f
    };
    
    data[0] = value;
    
    mImpl->mDevice->SetPixelShaderConstantF(index, &data[0], 1);
}

void Renderer::setPixelShaderConstant(unsigned index, const Color& color)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetPixelShaderConstantF(index, color.getData(), 1);
}

void Renderer::setPixelShaderConstant(unsigned index, const Matrix3& matrix)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    static float data[12];
    
    data[0] = matrix.m00;
    data[1] = matrix.m01;
    data[2] = matrix.m02;
    data[3] = 0.0f;
    data[4] = matrix.m10;
    data[5] = matrix.m11;
    data[6] = matrix.m12;
    data[7] = 0.0f;
    data[8] = matrix.m20;
    data[9] = matrix.m21;
    data[10] = matrix.m22;
    data[11] = 0.0f;
    
    mImpl->mDevice->SetPixelShaderConstantF(index, &data[0], 3);
}

void Renderer::setPixelShaderConstant(unsigned index, const Vector3& vector)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    static float data[4] =
    {
        0.0f,
        0.0f,
        0.0f,
        0.0f
    };
    
    data[0] = vector.mX;
    data[1] = vector.mY;
    data[2] = vector.mZ;
    
    mImpl->mDevice->SetPixelShaderConstantF(index, &data[0], 1);
}

void Renderer::setPixelShaderConstant(unsigned index, const Matrix4& matrix)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetPixelShaderConstantF(index, matrix.getData(), 4);
}

void Renderer::setPixelShaderConstant(unsigned index, const Vector4& vector)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetPixelShaderConstantF(index, vector.getData(), 1);
}

void Renderer::setPixelShaderConstant(unsigned index, const Matrix4x3& matrix)
{
    if (index >= MAX_CONSTANT_REGISTERS)
        return;
    
    mImpl->mDevice->SetPixelShaderConstantF(index, matrix.getData(), 3);
}

void Renderer::setTexture(unsigned index, Texture* texture)
{
    if (index >= MAX_TEXTURE_UNITS)
        return;
    
    // Check if texture is currently bound as a render target. In that case, use its backup texture, or blank if not defined
    if (texture)
    {
        if ((mRenderTarget[0]) && (mRenderTarget[0]->getParentTexture() == texture))
            texture = texture->getBackupTexture();
        // Check also for an user-specifiable view texture: this is to make forward & deferred rendering behave similarly
        // (during G-buffer rendering it would otherwise be valid to have the final rendertarget texture bound)
        else if (texture == mViewTexture)
            texture = texture->getBackupTexture();
    }
    
    if (texture != mTexture[index])
    {
        if (texture)
            mImpl->mDevice->SetTexture(index, (IDirect3DBaseTexture9*)texture->getObject());
        else
            mImpl->mDevice->SetTexture(index, 0);
        
        mTexture[index] = texture;
    }
    
    if (texture)
    {
        static const D3DTEXTUREFILTERTYPE d3dMinMagFilter[] =
        {
            D3DTEXF_POINT,
            D3DTEXF_LINEAR,
            D3DTEXF_LINEAR,
            D3DTEXF_ANISOTROPIC
        };
        
        static const D3DTEXTUREFILTERTYPE d3dMipFilter[] =
        {
            D3DTEXF_POINT,
            D3DTEXF_POINT,
            D3DTEXF_LINEAR,
            D3DTEXF_ANISOTROPIC
        };
        
        static const D3DTEXTUREADDRESS d3dAddressMode[] =
        {
            D3DTADDRESS_WRAP,
            D3DTADDRESS_MIRROR,
            D3DTADDRESS_CLAMP,
            D3DTADDRESS_BORDER
        };
        
        TextureFilterMode filterMode = texture->getFilterMode();
        if (filterMode == FILTER_DEFAULT)
            filterMode = mDefaultTextureFilterMode;
        
        D3DTEXTUREFILTERTYPE minMag, mip;
        minMag = d3dMinMagFilter[filterMode];
        if (minMag != mImpl->mMinMagFilter[index])
        {
            mImpl->mDevice->SetSamplerState(index, D3DSAMP_MAGFILTER, minMag);
            mImpl->mDevice->SetSamplerState(index, D3DSAMP_MINFILTER, minMag);
            mImpl->mMinMagFilter[index] = minMag;
        }
        mip = d3dMipFilter[filterMode];
        if (mip != mImpl->mMipFilter[index])
        {
            mImpl->mDevice->SetSamplerState(index, D3DSAMP_MIPFILTER, mip);
            mImpl->mMipFilter[index] = mip;
        }
        D3DTEXTUREADDRESS u, v;
        u = d3dAddressMode[texture->getAddressMode(COORD_U)];
        if (u != mImpl->mUAddressMode[index])
        {
            mImpl->mDevice->SetSamplerState(index, D3DSAMP_ADDRESSU, u);
            mImpl->mUAddressMode[index] = u;
        }
        v = d3dAddressMode[texture->getAddressMode(COORD_V)];
        if (v != mImpl->mVAddressMode[index])
        {
            mImpl->mDevice->SetSamplerState(index, D3DSAMP_ADDRESSV, v);
            mImpl->mVAddressMode[index] = v;
        }
        if ((u == D3DTADDRESS_BORDER) || (v == D3DTADDRESS_BORDER))
        {
            const Color& borderColor = texture->getBorderColor();
            if (borderColor != mImpl->mBorderColor[index])
            {
                mImpl->mDevice->SetSamplerState(index, D3DSAMP_BORDERCOLOR, getD3DColor(borderColor));
                mImpl->mBorderColor[index] = borderColor;
            }
        }
    }
}

void Renderer::setDefaultTextureFilterMode(TextureFilterMode mode)
{
    mDefaultTextureFilterMode = mode;
}

void Renderer::resetRenderTargets()
{
    for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        setRenderTarget(i, (RenderSurface*)0);
    setDepthStencil((RenderSurface*)0);
    setViewport(IntRect(0, 0, mWidth, mHeight));
}

void Renderer::resetRenderTarget(unsigned index)
{
    setRenderTarget(index, (RenderSurface*)0);
}

void Renderer::resetDepthStencil()
{
    setDepthStencil((RenderSurface*)0);
}

void Renderer::setRenderTarget(unsigned index, RenderSurface* renderTarget)
{
    if (index >= MAX_RENDERTARGETS)
        return;
    
    IDirect3DSurface9* newColorSurface = 0;
    
    if (renderTarget)
    {
        if (renderTarget->getUsage() != TEXTURE_RENDERTARGET)
            return;
        newColorSurface = (IDirect3DSurface9*)renderTarget->getSurface();
    }
    else
    {
        if (!index)
            newColorSurface = mImpl->mDefaultColorSurface;
    }
    
    mRenderTarget[index] = renderTarget;
    
    if (newColorSurface != mImpl->mColorSurface[index])
    {
        mImpl->mDevice->SetRenderTarget(index, newColorSurface);
        mImpl->mColorSurface[index] = newColorSurface;
    }
    
    // If the rendertarget is also bound as a texture, replace with backup texture or null
    if (renderTarget)
    {
        Texture* parentTexture = renderTarget->getParentTexture();
        
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (mTexture[i] == parentTexture)
                setTexture(i, mTexture[i]->getBackupTexture());
        }
    }
    
    if (!index)
    {
        // Viewport has been reset
        IntVector2 rtSize = getRenderTargetDimensions();
        mViewport = IntRect(0, 0, rtSize.mX, rtSize.mY);
        
        // Disable scissor test, needs to be re-enabled by the user
        setScissorTest(false);
    }
}

void Renderer::setRenderTarget(unsigned index, Texture2D* renderTexture)
{
    RenderSurface* renderTarget = 0;
    if (renderTexture)
        renderTarget = renderTexture->getRenderSurface();
    
    setRenderTarget(index, renderTarget);
}

void Renderer::setDepthStencil(RenderSurface* depthStencil)
{
    IDirect3DSurface9* newDepthStencilSurface = 0;
    if ((depthStencil) && (depthStencil->getUsage() == TEXTURE_DEPTHSTENCIL))
    {
        newDepthStencilSurface = (IDirect3DSurface9*)depthStencil->getSurface();
        mDepthStencil = depthStencil;
    }
    if (!newDepthStencilSurface)
    {
        newDepthStencilSurface = mImpl->mDefaultDepthStencilSurface;
        mDepthStencil = 0;
    }
    if (newDepthStencilSurface != mImpl->mDepthStencilSurface)
    {
        mImpl->mDevice->SetDepthStencilSurface(newDepthStencilSurface);
        mImpl->mDepthStencilSurface = newDepthStencilSurface;
    }
}

void Renderer::setDepthStencil(Texture2D* depthTexture)
{
    RenderSurface* depthStencil = 0;
    if (depthTexture)
        depthStencil = depthTexture->getRenderSurface();
    
    setDepthStencil(depthStencil);
}

void Renderer::setViewport(const IntRect& rect)
{
    IntVector2 size = getRenderTargetDimensions();
    
    IntRect rectCopy = rect;
    
    if (rectCopy.mRight <= rectCopy.mLeft)
        rectCopy.mRight = rectCopy.mLeft + 1;
    if (rectCopy.mBottom <= rectCopy.mTop)
        rectCopy.mBottom = rectCopy.mTop + 1;
    rectCopy.mLeft = clamp(rectCopy.mLeft, 0, size.mX);
    rectCopy.mTop = clamp(rectCopy.mTop, 0, size.mY);
    rectCopy.mRight = clamp(rectCopy.mRight, 0, size.mX);
    rectCopy.mBottom = clamp(rectCopy.mBottom, 0, size.mY);
    
    D3DVIEWPORT9 vp;
    vp.MinZ = 0.0f;
    vp.MaxZ = 1.0f;
    vp.X = rectCopy.mLeft;
    vp.Y = rectCopy.mTop;
    vp.Width = rectCopy.mRight - rectCopy.mLeft;
    vp.Height = rectCopy.mBottom - rectCopy.mTop;
    
    mImpl->mDevice->SetViewport(&vp);
    mViewport = rectCopy;
    
    // Disable scissor test, needs to be re-enabled by the user
    setScissorTest(false);
}

void Renderer::setViewTexture(Texture* texture)
{
    mViewTexture = texture;
    
    // Check for the view texture being currently bound
    if (texture)
    {
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (mTexture[i] == texture)
                setTexture(i, mTexture[i]->getBackupTexture());
        }
    }
}

void Renderer::setAlphaTest(bool enable, CompareMode mode, float alphaRef)
{
    if (enable != mAlphaTest)
    {
        mImpl->mDevice->SetRenderState(D3DRS_ALPHATESTENABLE, enable ? TRUE : FALSE);
        mAlphaTest = enable;
    }
    
    if (enable)
    {
        if (mode != mAlphaTestMode)
        {
            mImpl->mDevice->SetRenderState(D3DRS_ALPHAFUNC, d3dCmpFunc[mode]);
            mAlphaTestMode = mode;
        }
        
        if (alphaRef < 0.0f)
            alphaRef = 0.0f;
        if (alphaRef > 1.0f) 
            alphaRef = 1.0f;
        
        if (alphaRef != mAlphaRef)
        {
            mImpl->mDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(alphaRef * 255.0f));
            mAlphaRef = alphaRef;
        }
    }
}

void Renderer::setTextureAnisotropy(unsigned level)
{
    if (level < 1)
        level = 1;
    
    if (level != mTextureAnisotropy)
    {
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
            mImpl->mDevice->SetSamplerState(i, D3DSAMP_MAXANISOTROPY, level);
        
        mTextureAnisotropy = level;
    }
}

void Renderer::setBlendMode(BlendMode mode)
{
    if (mode != mBlendMode)
    {
        static const DWORD d3dBlendEnable[] =
        {
            FALSE,
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
        };

        static const D3DBLEND d3dDestBlend[] =
        {
            D3DBLEND_ZERO,
            D3DBLEND_ONE,
            D3DBLEND_ZERO,
            D3DBLEND_INVSRCALPHA,
            D3DBLEND_ONE,
            D3DBLEND_INVSRCALPHA,
            D3DBLEND_DESTALPHA
        };

        if (d3dBlendEnable[mode] != mImpl->mBlendEnable)
        {
            mImpl->mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, d3dBlendEnable[mode]);
            mImpl->mBlendEnable = d3dBlendEnable[mode];
        }
        
        if (mImpl->mBlendEnable)
        {
            if (d3dSrcBlend[mode] != mImpl->mSrcBlend)
            {
                mImpl->mDevice->SetRenderState(D3DRS_SRCBLEND, d3dSrcBlend[mode]);
                mImpl->mSrcBlend = d3dSrcBlend[mode];
            }
            if (d3dDestBlend[mode] != mImpl->mDestBlend)
            {
                mImpl->mDevice->SetRenderState(D3DRS_DESTBLEND, d3dDestBlend[mode]);
                mImpl->mDestBlend = d3dDestBlend[mode];
            }
        }
        
        mBlendMode = mode;
    }
}

void Renderer::setColorWrite(bool enable)
{
    if (enable != mColorWrite)
    {
        mImpl->mDevice->SetRenderState(D3DRS_COLORWRITEENABLE, enable ? D3DCOLORWRITEENABLE_RED |
            D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA : 0);
        mColorWrite = enable;
    }
}

void Renderer::setCullMode(CullMode mode)
{
    if (mode != mCullMode)
    {
        static const D3DCULL d3dCullMode[] =
        {
            D3DCULL_NONE,
            D3DCULL_CCW,
            D3DCULL_CW
        };
        
        mImpl->mDevice->SetRenderState(D3DRS_CULLMODE, d3dCullMode[mode]);
        mCullMode = mode;
    }
}

void Renderer::setDepthBias(float constantBias, float slopeScaledBias)
{
    if (constantBias != mDepthConstantBias)
    {
        mImpl->mDevice->SetRenderState(D3DRS_DEPTHBIAS, *((DWORD*)&constantBias));
        mDepthConstantBias = constantBias;
    }
    if (slopeScaledBias != mDepthSlopeScaledBias)
    {
        mImpl->mDevice->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, *((DWORD*)&slopeScaledBias));
        mDepthSlopeScaledBias = slopeScaledBias;
    }
}

void Renderer::setDepthTest(CompareMode mode)
{
    if (mode != mDepthTestMode)
    {
        mImpl->mDevice->SetRenderState(D3DRS_ZFUNC, d3dCmpFunc[mode]);
        mDepthTestMode = mode;
    }
}

void Renderer::setDepthWrite(bool enable)
{
    if (enable != mDepthWrite)
    {
        mImpl->mDevice->SetRenderState(D3DRS_ZWRITEENABLE, enable ? TRUE : FALSE);
        mDepthWrite = enable;
    }
}

void Renderer::setFillMode(FillMode mode)
{
    if (mode != mFillMode)
    {
        static const D3DFILLMODE d3dFillMode[] =
        {
            D3DFILL_SOLID,
            D3DFILL_WIREFRAME
        };
        
        mImpl->mDevice->SetRenderState(D3DRS_FILLMODE, d3dFillMode[mode]);
        mFillMode = mode;
    }
}

void Renderer::setScissorTest(bool enable, const Rect& rect, bool borderInclusive)
{
    // During some light rendering loops, a full rect is toggled on/off repeatedly.
    // Disable scissor in that case to reduce state changes
    if (rect == Rect::sFullRect)
        enable = false;
    
    // Check for illegal rect, disable in that case
    if ((rect.mMax.mX < rect.mMin.mX) || (rect.mMax.mY < rect.mMin.mY))
        enable = false;
    
    if (enable)
    {
        IntVector2 rtSize(getRenderTargetDimensions());
        IntVector2 viewSize(mViewport.mRight - mViewport.mLeft, mViewport.mBottom - mViewport.mTop);
        IntVector2 viewPos(mViewport.mLeft, mViewport.mTop);
        IntRect intRect;
        int expand = borderInclusive ? 1 : 0;
        
        intRect.mLeft = clamp((int)((rect.mMin.mX + 1.0f) * 0.5f * viewSize.mX) + viewPos.mX, 0, rtSize.mX - 1);
        intRect.mTop = clamp((int)((-rect.mMax.mY + 1.0f) * 0.5f * viewSize.mY) + viewPos.mY, 0, rtSize.mY - 1);
        intRect.mRight = clamp((int)((rect.mMax.mX + 1.0f) * 0.5f * viewSize.mX) + viewPos.mX + expand, 0, rtSize.mX);
        intRect.mBottom = clamp((int)((-rect.mMin.mY + 1.0f) * 0.5f * viewSize.mY) + viewPos.mY + expand, 0, rtSize.mY);
        
        if (intRect.mRight == intRect.mLeft)
            intRect.mRight++;
        if (intRect.mBottom == intRect.mTop)
            intRect.mBottom++;
        
        if ((intRect.mRight < intRect.mLeft) || (intRect.mBottom < intRect.mTop))
            enable = false;
        
        if ((enable) && (mScissorRect != intRect))
        {
            RECT d3dRect;
            d3dRect.left = intRect.mLeft;
            d3dRect.top = intRect.mTop;
            d3dRect.right = intRect.mRight;
            d3dRect.bottom = intRect.mBottom;
            
            mImpl->mDevice->SetScissorRect(&d3dRect);
            mScissorRect = intRect;
        }
    }
    else
        mScissorRect = IntRect::sZero;
    
    if (enable != mScissorTest)
    {
        mImpl->mDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, enable ? TRUE : FALSE);
        mScissorTest = enable;
    }
}

void Renderer::setScissorTest(bool enable, const IntRect& rect)
{
    IntVector2 rtSize(getRenderTargetDimensions());
    IntVector2 viewSize(mViewport.mRight - mViewport.mLeft, mViewport.mBottom - mViewport.mTop);
    IntVector2 viewPos(mViewport.mLeft, mViewport.mTop);
    
    // Full scissor is same as disabling the test
    if ((rect.mLeft <= 0) && (rect.mRight >= viewSize.mX) && (rect.mTop <= 0) && (rect.mBottom >= viewSize.mY))
        enable = false;
    
    // Check for illegal rect, disable in that case
    if ((rect.mRight < rect.mLeft) || (rect.mBottom < rect.mTop))
        enable = false;
    
    if (enable)
    {
        IntRect intRect;
        intRect.mLeft = clamp(rect.mLeft + viewPos.mX, 0, rtSize.mX - 1);
        intRect.mTop = clamp(rect.mTop + viewPos.mY, 0, rtSize.mY - 1);
        intRect.mRight = clamp(rect.mRight + viewPos.mX, 0, rtSize.mX);
        intRect.mBottom = clamp(rect.mBottom + viewPos.mY, 0, rtSize.mY);
        
        if (intRect.mRight == intRect.mLeft)
            intRect.mRight++;
        if (intRect.mBottom == intRect.mTop)
            intRect.mBottom++;
        
        if ((intRect.mRight < intRect.mLeft) || (intRect.mBottom < intRect.mTop))
            enable = false;
        
        if ((enable) && (mScissorRect != intRect))
        {
            RECT d3dRect;
            d3dRect.left = intRect.mLeft;
            d3dRect.top = intRect.mTop;
            d3dRect.right = intRect.mRight;
            d3dRect.bottom = intRect.mBottom;
            
            mImpl->mDevice->SetScissorRect(&d3dRect);
            mScissorRect = intRect;
        }
    }
    else
        mScissorRect = IntRect::sZero;
    
    if (enable != mScissorTest)
    {
        mImpl->mDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, enable ? TRUE : FALSE);
        mScissorTest = enable;
    }
}

void Renderer::setStencilTest(bool enable, CompareMode mode, StencilOp pass, StencilOp fail, StencilOp zFail, unsigned stencilRef, unsigned stencilMask)
{
    if (enable != mStencilTest)
    {
        mImpl->mDevice->SetRenderState(D3DRS_STENCILENABLE, enable ? TRUE : FALSE);
        mStencilTest = enable;
    }
    
    if (enable)
    {
        static const D3DSTENCILOP d3dStencilOp[] =
        {
            D3DSTENCILOP_KEEP,
            D3DSTENCILOP_ZERO,
            D3DSTENCILOP_REPLACE,
            D3DSTENCILOP_INCR,
            D3DSTENCILOP_DECR
        };
        
        if (mode != mStencilTestMode)
        {
            mImpl->mDevice->SetRenderState(D3DRS_STENCILFUNC, d3dCmpFunc[mode]);
            mStencilTestMode = mode;
        }
        if (pass != mStencilPass)
        {
            mImpl->mDevice->SetRenderState(D3DRS_STENCILPASS, d3dStencilOp[pass]);
            mStencilPass = pass;
        }
        if (fail != mStencilFail)
        {
            mImpl->mDevice->SetRenderState(D3DRS_STENCILFAIL, d3dStencilOp[fail]);
            mStencilFail = fail;
        }
        if (zFail != mStencilZFail)
        {
            mImpl->mDevice->SetRenderState(D3DRS_STENCILZFAIL, d3dStencilOp[zFail]);
            mStencilZFail = zFail;
        }
        if (stencilRef != mStencilRef)
        {
            mImpl->mDevice->SetRenderState(D3DRS_STENCILREF, stencilRef);
            mStencilRef = stencilRef;
        }
        if (stencilMask != mStencilMask)
        {
            mImpl->mDevice->SetRenderState(D3DRS_STENCILMASK, stencilMask);
            mStencilMask = stencilMask;
        }
    }
}

bool Renderer::setStreamFrequency(unsigned index, unsigned frequency)
{
    if (index >= MAX_VERTEX_STREAMS)
    {
        LOGERROR("Illegal vertex stream index");
        return false;
    }
    
    if (mStreamFrequency[index] != frequency)
    {
        mImpl->mDevice->SetStreamSourceFreq(index, frequency);
        mStreamFrequency[index] = frequency;
    }
    
    return true;
}

void Renderer::resetStreamFrequencies()
{
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        if (mStreamFrequency[i] != 1)
        {
            mImpl->mDevice->SetStreamSourceFreq(i, 1);
            mStreamFrequency[i] = 1;
        }
    }
}

bool Renderer::beginImmediate(PrimitiveType type, unsigned vertexCount, unsigned elementMask)
{
    if (mImmediateBuffer)
    {
        LOGERROR("New immediate draw operation started before ending the last one");
        return false;
    }
    if (!(elementMask & MASK_POSITION))
    {
        LOGERROR("Immediate draw operation must contain vertex positions");
        return false;
    }
    if (!vertexCount)
        return true;

    // See if buffer exists for this vertex format. If not, create new
    if (mImmediateVertexBuffers.find(elementMask) == mImmediateVertexBuffers.end())
    {
        VertexBuffer* newBuffer = new VertexBuffer(this, true);
        unsigned size = vertexCount > IMMEDIATE_BUFFER_DEFAULT_SIZE ? vertexCount : IMMEDIATE_BUFFER_DEFAULT_SIZE;
        newBuffer->setSize(size, elementMask);
        mImmediateVertexBuffers[elementMask] = newBuffer;
        mImmediateVertexBufferPos[elementMask] = 0;
    }
    
    // Resize buffer if it is too small
    VertexBuffer* buffer = mImmediateVertexBuffers[elementMask];
    if (buffer->getVertexCount() < vertexCount)
    {
        buffer->setSize(vertexCount, elementMask);
        mImmediateVertexBufferPos[elementMask] = 0;
    }
    
    // Get the current lock position for the buffer
    unsigned bufferPos = mImmediateVertexBufferPos[elementMask];
    if (bufferPos + vertexCount >= buffer->getVertexCount())
        bufferPos = 0;
    
    LockMode lockMode = LOCK_DISCARD;
    if (bufferPos != 0)
        lockMode = LOCK_NOOVERWRITE;
    
    // Note: the data pointer gets pre-decremented here, because the first call to defineVertex() will increment it
    mImmediateDataPtr = ((unsigned char*)buffer->lock(bufferPos, vertexCount, lockMode)) - buffer->getVertexSize();
    mImmediateBuffer = buffer;
    mImmediateType= type;
    mImmediateStartPos = bufferPos;
    mImmediateVertexCount = vertexCount;
    mImmediateCurrentVertex = 0;
    
    // Store new buffer position for next lock into the same buffer
    bufferPos += vertexCount;
    if (bufferPos >= buffer->getVertexCount())
        bufferPos = 0;
    mImmediateVertexBufferPos[elementMask] = bufferPos;
    
    return true;
}

bool Renderer::defineVertex(const Vector3& vertex)
{
    if ((!mImmediateBuffer) || (mImmediateCurrentVertex >= mImmediateVertexCount))
        return false;
    
    mImmediateDataPtr += mImmediateBuffer->getVertexSize();
    ++mImmediateCurrentVertex;
    
    float* dest = (float*)(mImmediateDataPtr + mImmediateBuffer->getElementOffset(ELEMENT_POSITION));
    const float* src = vertex.getData();
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    
    return true;
}

bool Renderer::defineNormal(const Vector3& normal)
{
    if ((!mImmediateBuffer) ||(!(mImmediateBuffer->getElementMask() & MASK_NORMAL)) || (!mImmediateCurrentVertex))
        return false;
    
    float* dest = (float*)(mImmediateDataPtr + mImmediateBuffer->getElementOffset(ELEMENT_NORMAL));
    const float* src = normal.getData();
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    
    return true;
}

bool Renderer::defineTexCoord(const Vector2& texCoord)
{
    if ((!mImmediateBuffer) || (!(mImmediateBuffer->getElementMask() & MASK_TEXCOORD1)) || (!mImmediateCurrentVertex))
        return false;
    
    float* dest = (float*)(mImmediateDataPtr + mImmediateBuffer->getElementOffset(ELEMENT_TEXCOORD1));
    const float* src = texCoord.getData();
    dest[0] = src[0];
    dest[1] = src[1];
    
    return true;
}

bool Renderer::defineColor(const Color& color)
{
    if ((!mImmediateBuffer) || (!(mImmediateBuffer->getElementMask() & MASK_COLOR)) || (!mImmediateCurrentVertex))
        return false;
    
    unsigned* dest = (unsigned*)(mImmediateDataPtr + mImmediateBuffer->getElementOffset(ELEMENT_COLOR));
    *dest = getD3DColor(color);
    
    return true;
}

bool Renderer::defineColor(unsigned color)
{
    if ((!mImmediateBuffer) || (!(mImmediateBuffer->getElementMask() & MASK_COLOR)) || (!mImmediateCurrentVertex))
        return false;
    
    unsigned* dest = (unsigned*)(mImmediateDataPtr + mImmediateBuffer->getElementOffset(ELEMENT_COLOR));
    *dest = color;
    
    return true;
}

void Renderer::endImmediate()
{
    if (mImmediateBuffer)
    {
        mImmediateBuffer->unlock();
        setVertexBuffer(mImmediateBuffer);
        draw(mImmediateType, mImmediateStartPos, mImmediateVertexCount);
        mImmediateBuffer = 0;
    }
}

void Renderer::setForceSM2(bool enable)
{
    // Note: this only has effect before calling setMode() for the first time
    mForceSM2 = enable;
}

unsigned char* Renderer::getImmediateDataPtr() const
{
    if (!mImmediateBuffer)
    {
        LOGERROR("Immediate draw operation not started");
        return 0;
    }
    // Pointer was pre-decremented in beginImmediate(). Undo that now
    return mImmediateDataPtr + mImmediateBuffer->getVertexSize();
}

unsigned Renderer::getWindowHandle() const
{
    return (unsigned)mImpl->mWindow;
}

std::vector<IntVector2> Renderer::getResolutions() const
{
    std::vector<IntVector2> ret;
    if (!mImpl->mInterface)
        return ret;
    
    D3DFORMAT fullscreenFormat = mImpl->getDesktopFormat();
    unsigned numModes = mImpl->mInterface->GetAdapterModeCount(mImpl->mAdapter, fullscreenFormat);
    D3DDISPLAYMODE displayMode;
    
    for (unsigned i = 0; i < numModes; ++i)
    {
        if (FAILED(mImpl->mInterface->EnumAdapterModes(mImpl->mAdapter, fullscreenFormat, i, &displayMode)))
            continue;
        if (displayMode.Format != fullscreenFormat)
            continue;
        IntVector2 newMode(displayMode.Width, displayMode.Height);
        
        // Check for duplicate before storing
        bool unique = true;
        for (unsigned j = 0; j < ret.size(); ++j)
        {
            if (ret[j] == newMode)
            {
                unique = false;
                break;
            }
        }
        if (unique)
            ret.push_back(newMode);
    }
    
    return ret;
}

std::vector<int> Renderer::getMultiSampleLevels() const
{
    std::vector<int> ret;
    // No multisampling always supported
    ret.push_back(0);
    
    if (!mImpl->mInterface)
        return ret;
    
    for (unsigned i = (int)D3DMULTISAMPLE_2_SAMPLES; i < (int)D3DMULTISAMPLE_16_SAMPLES; ++i)
    {
        if (SUCCEEDED(mImpl->mInterface->CheckDeviceMultiSampleType(mImpl->mAdapter, mImpl->mDeviceType, D3DFMT_R8G8B8, FALSE,
            (D3DMULTISAMPLE_TYPE)i, NULL)))
            ret.push_back(i);
    }
    
    return ret;
}

VertexBuffer* Renderer::getVertexBuffer(unsigned index) const
{
    return index < MAX_VERTEX_STREAMS ? mVertexBuffer[index] : 0;
}

Texture* Renderer::getTexture(unsigned index) const
{
    return index < MAX_TEXTURE_UNITS ? mTexture[index] : 0;
}

RenderSurface* Renderer::getRenderTarget(unsigned index) const
{
    return index < MAX_RENDERTARGETS ? mRenderTarget[index] : 0;
}

unsigned Renderer::getStreamFrequency(unsigned index) const
{
    return index < MAX_VERTEX_STREAMS ? mStreamFrequency[index] : 0;
}

IntVector2 Renderer::getRenderTargetDimensions() const
{
    int width, height;
    
    if (mRenderTarget[0])
    {
        width = mRenderTarget[0]->getWidth();
        height = mRenderTarget[0]->getHeight();
    }
    else
    {
        width = mWidth;
        height = mHeight;
    }
    
    return IntVector2(width, height);
}

void Renderer::addGPUObject(GPUObject* object)
{
    mGPUObjects.push_back(object);
}

void Renderer::removeGPUObject(GPUObject* object)
{
    for (unsigned i = 0; i < mGPUObjects.size(); ++i)
    {
        if (mGPUObjects[i] == object)
        {
            mGPUObjects.erase(mGPUObjects.begin() + i);
            return;
        }
    }
}

void Renderer::createWindow(int width, int height)
{
    WNDCLASS wc;
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = wndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = mImpl->mInstance;
    wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = 0;
    wc.lpszMenuName  = 0;
    wc.lpszClassName = "D3DWindow";
    
    RegisterClass(&wc);
    
    RECT rect = {0, 0, width, height};
    AdjustWindowRect(&rect, windowStyle, false);
    mImpl->mWindow = CreateWindow("D3DWindow", mTitle.c_str(), windowStyle, CW_USEDEFAULT, CW_USEDEFAULT, 
        rect.right, rect.bottom, 0, 0, mImpl->mInstance, 0); 
    
    if (!mImpl->mWindow)
        EXCEPTION("Could not create window");
    
    // Save window placement
    WINDOWPLACEMENT wndpl;
    wndpl.length = sizeof wndpl;
    if (SUCCEEDED(GetWindowPlacement(mImpl->mWindow, &wndpl)))
    {
        mWindowPosX = wndpl.rcNormalPosition.left;
        mWindowPosY = wndpl.rcNormalPosition.top;
    }
    
    renderers[mImpl->mWindow] = this;
}

void Renderer::createInterface()
{
    mImpl->mInterface = Direct3DCreate9(D3D9b_SDK_VERSION);
    if (!mImpl->mInterface)
        EXCEPTION("Could not create Direct3D9 interface");
    
    if (FAILED(mImpl->mInterface->GetDeviceCaps(mImpl->mAdapter, mImpl->mDeviceType, &mImpl->mDeviceCaps)))
        EXCEPTION("Could not get Direct3D capabilities");
    
    if (FAILED(mImpl->mInterface->GetAdapterIdentifier(mImpl->mAdapter, 0, &mImpl->mAdapterIdentifier)))
        EXCEPTION("Could not get Direct3D adapter identifier");
    
    if (mImpl->mDeviceCaps.PixelShaderVersion < D3DPS_VERSION(2, 0))
        EXCEPTION("Shader model 2.0 display adapter is required");
    
    // Check supported features: Shader Model 3, deferred / light prepass rendering, hardware depth texture, shadow map,
    // dummy color surface
    if (!mForceSM2)
    {
        if ((mImpl->mDeviceCaps.VertexShaderVersion >= D3DVS_VERSION(3, 0)) && (mImpl->mDeviceCaps.PixelShaderVersion >=
            D3DPS_VERSION(3, 0)))
            mSM3Support = true;
    }
    
    if (mImpl->checkFormatSupport(D3DFMT_R32F, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE))
    {
        if (mImpl->mDeviceCaps.NumSimultaneousRTs >= 3)
            mDeferredSupport = true;
        if (mImpl->mDeviceCaps.NumSimultaneousRTs >= 2)
            mPrepassSupport = true;
    }
    
    if (mImpl->checkFormatSupport((D3DFORMAT)MAKEFOURCC('I', 'N', 'T', 'Z'), D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE))
    {
        // Sampling INTZ buffer directly while also using it for depth test results in performance loss on ATI GPUs
        // at least on Vista/Win7 (see http://aras-p.info/texts/D3D9GPUHacks.html). So, use INTZ buffer only with
        // other vendors, or on Windows XP
        unsigned windowsVersion = GetVersion() & 0xff;
        if ((mImpl->mAdapterIdentifier.VendorId != 0x1002) || (windowsVersion < 6))
            mHardwareDepthSupport = true;
    }
    
    // Prefer NVIDIA style hardware depth compared shadow maps if available
    mShadowMapFormat = D3DFMT_D16;
    if (mImpl->checkFormatSupport((D3DFORMAT)mShadowMapFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE))
    {
        mHardwareShadowSupport = true;
        
        // Check for hires depth support
        mHiresShadowMapFormat = D3DFMT_D24X8;
        if (mImpl->checkFormatSupport((D3DFORMAT)mHiresShadowMapFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE))
            mHiresShadowSupport = true;
        else
            mHiresShadowMapFormat = mShadowMapFormat;
    }
    else
    {
        // ATI DF16 format needs manual depth compare in the shader
        mShadowMapFormat = MAKEFOURCC('D', 'F', '1', '6');
        if (mImpl->checkFormatSupport((D3DFORMAT)mShadowMapFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE))
        {
            // Check for hires depth support
            mHiresShadowMapFormat = MAKEFOURCC('D', 'F', '2', '4');
            if (mImpl->checkFormatSupport((D3DFORMAT)mHiresShadowMapFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_TEXTURE))
                mHiresShadowSupport = true;
            else
                mHiresShadowMapFormat = mShadowMapFormat;
        }
        else
        {
            // No depth texture shadow map support -> no shadows at all
            mShadowMapFormat = D3DFMT_UNKNOWN;
            mHiresShadowMapFormat = D3DFMT_UNKNOWN;
        }
    }
    
    // Check for Intel 4 Series with an old driver, enable manual shadow map compare in that case
    if (mShadowMapFormat == D3DFMT_D16)
    {
        if ((mImpl->mAdapterIdentifier.VendorId == 0x8086) && (mImpl->mAdapterIdentifier.DeviceId == 0x2a42) &&
            (mImpl->mAdapterIdentifier.DriverVersion.QuadPart <= 0x0007000f000a05d0ULL))
            mHardwareShadowSupport = false;
    }
    
    mDummyColorFormat = D3DFMT_A8R8G8B8;
    D3DFORMAT nullFormat = (D3DFORMAT)MAKEFOURCC('N', 'U', 'L', 'L');
    if (mImpl->checkFormatSupport(nullFormat, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE))
        mDummyColorFormat = nullFormat;
    else if (mImpl->checkFormatSupport(D3DFMT_R16F, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE))
        mDummyColorFormat = D3DFMT_R16F;
    else if (mImpl->checkFormatSupport(D3DFMT_R5G6B5, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE))
        mDummyColorFormat = D3DFMT_R5G6B5;
    else if (mImpl->checkFormatSupport(D3DFMT_A4R4G4B4, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE))
        mDummyColorFormat = D3DFMT_A4R4G4B4;
}

void Renderer::createDevice(unsigned adapter, unsigned deviceType)
{
    DWORD behaviorFlags = 0;
    if (mImpl->mDeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
    {
        behaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
        if (mImpl->mDeviceCaps.DevCaps & D3DDEVCAPS_PUREDEVICE)
            behaviorFlags |= D3DCREATE_PUREDEVICE;
    }
    else
        behaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    
    if (FAILED(mImpl->mInterface->CreateDevice(
        adapter,                    // adapter
        (D3DDEVTYPE)deviceType,     // device type
        mImpl->mWindow,             // window associated with device
        behaviorFlags,              // vertex processing
        &mImpl->mPresentParams,     // present parameters
        &mImpl->mDevice)))          // return created device
        EXCEPTION("Could not create Direct3D device");
    
    mImpl->mAdapter = adapter;
    mImpl->mDeviceType = (D3DDEVTYPE)deviceType;
    
    onDeviceReset();
}

void Renderer::createRenderTargets()
{
    if (mMode != RENDER_FORWARD)
    {
        // In deferred rendering, the diffuse buffer stores diffuse albedo. In light prepass, it is used for light accumulation
        if (!mDiffBuffer)
        {
            mDiffBuffer = new Texture2D(this, TEXTURE_RENDERTARGET);
            mDiffBuffer->setSize(0, 0, D3DFMT_A8R8G8B8);
        }
        
        if (!mNormalBuffer)
        {
            mNormalBuffer = new Texture2D(this, TEXTURE_RENDERTARGET);
            mNormalBuffer->setSize(0, 0, D3DFMT_A8R8G8B8);
        }
        
        if (!mDepthBuffer)
        {
            if (!mHardwareDepthSupport)
            {
                mDepthBuffer = new Texture2D(this, TEXTURE_RENDERTARGET);
                mDepthBuffer->setSize(0, 0, D3DFMT_R32F);
            }
            else
            {
                mDepthBuffer = new Texture2D(this, TEXTURE_DEPTHSTENCIL);
                mDepthBuffer->setSize(0, 0, (D3DFORMAT)MAKEFOURCC('I', 'N', 'T', 'Z'));
            }
        }
        
        // If edge filtering is used, reserve screen buffer
        // (later we will probably want the screen buffer reserved in any case, to do for example distortion effects,
        // which will also be useful in forward rendering)
        if (mMultiSample)
        {
            mScreenBuffer = new Texture2D(this, TEXTURE_RENDERTARGET);
            mScreenBuffer->setSize(0, 0, D3DFMT_X8R8G8B8);
            mScreenBuffer->setFilterMode(FILTER_BILINEAR);
        }
        else
            mScreenBuffer.reset();
    }
    else
    {
        mDiffBuffer.reset();
        mNormalBuffer.reset();
        mDepthBuffer.reset();
        mScreenBuffer.reset();
    }
}

void Renderer::resetDevice()
{
    onDeviceLost();
    
    if (SUCCEEDED(mImpl->mDevice->Reset(&mImpl->mPresentParams)))
    {
        mDeviceLost = false;
        onDeviceReset();
    }
}

void Renderer::onDeviceLost()
{
    if (mImpl->mFrameQuery)
    {
        mImpl->mFrameQuery->Release();
        mImpl->mFrameQuery = 0;
    }
    if (mImpl->mDefaultColorSurface)
    {
        mImpl->mDefaultColorSurface->Release();
        mImpl->mDefaultColorSurface = 0;
    }
    if (mImpl->mDefaultDepthStencilSurface)
    {
        if (mSystemDepthStencil)
            mImpl->mDefaultDepthStencilSurface->Release();
        mImpl->mDefaultDepthStencilSurface = 0;
    }
    
    for (unsigned i = 0; i < mGPUObjects.size(); ++i)
        mGPUObjects[i]->onDeviceLost();
}

void Renderer::onDeviceReset()
{
    resetCachedState();
    
    // Create frame query
    mImpl->mDevice->CreateQuery(D3DQUERYTYPE_EVENT, &mImpl->mFrameQuery);
    
    // In case AutoDepthStencil is not used, depth buffering must be enabled manually
    mImpl->mDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    
    // Create deferred rendering buffers now
    createRenderTargets();
    
    for (unsigned i = 0; i < mGPUObjects.size(); ++i)
        mGPUObjects[i]->onDeviceReset();
    
    // Get default surfaces
    mImpl->mDevice->GetRenderTarget(0, &mImpl->mDefaultColorSurface);
    if (mImpl->mPresentParams.EnableAutoDepthStencil)
    {
        mImpl->mDevice->GetDepthStencilSurface(&mImpl->mDefaultDepthStencilSurface);
        mSystemDepthStencil = true;
    }
    else
    {
        mImpl->mDefaultDepthStencilSurface = (IDirect3DSurface9*)mDepthBuffer->getRenderSurface()->getSurface();
        mSystemDepthStencil = false;
    }
    
    mImmediateBuffer = 0;
}

void Renderer::resetCachedState()
{
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
        mVertexBuffer[i] = 0;
    
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
    {
        mTexture[i] = 0;
        mImpl->mMinMagFilter[i] = D3DTEXF_POINT;
        mImpl->mMipFilter[i] = D3DTEXF_NONE;
        mImpl->mUAddressMode[i] = D3DTADDRESS_WRAP;
        mImpl->mVAddressMode[i] = D3DTADDRESS_WRAP;
        mImpl->mBorderColor[i] = Color(0.0f, 0.0f, 0.0f, 0.0f);
    }
    
    for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
    {
        mRenderTarget[i] = 0;
        mImpl->mColorSurface[i] = 0;
    }
    mDepthStencil = 0;
    mImpl->mDepthStencilSurface = 0;
    mViewport = IntRect(0, 0, mWidth, mHeight);
    mViewTexture = 0;
    
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
        mStreamFrequency[i] = 0;
    
    mIndexBuffer = 0;
    mVertexDeclaration = 0;
    mVertexShader = 0;
    mPixelShader = 0;
    mBlendMode = BLEND_REPLACE;
    mAlphaTest = false;
    mAlphaTestMode = CMP_ALWAYS;
    mAlphaRef = 0.0f;
    mTextureAnisotropy = 1;
    mColorWrite = true;
    mCullMode = CULL_CCW;
    mDepthConstantBias = 0.0f;
    mDepthSlopeScaledBias = 0.0f;
    mDepthTestMode = CMP_LESSEQUAL;
    mDepthWrite = true;
    mFillMode = FILL_SOLID;
    mScissorTest = false;
    mScissorRect = IntRect::sZero;
    mStencilTest = false;
    mStencilTestMode = CMP_ALWAYS;
    mStencilPass = OP_KEEP;
    mStencilFail = OP_KEEP;
    mStencilZFail = OP_KEEP;
    mStencilRef = 0;
    mStencilMask = M_MAX_UNSIGNED;
    mImpl->mBlendEnable = FALSE;
    mImpl->mSrcBlend = D3DBLEND_ONE;
    mImpl->mDestBlend = D3DBLEND_ZERO;
    
    mQueryIssued = false;
}

void Renderer::handleWindowMessage(StringHash eventType, VariantMap& eventData)
{
    using namespace WindowMessage;
    
    if (eventData[P_WINDOW].getInt() != (int)mImpl->mWindow)
        return;
    
    switch (eventData[P_MSG].getInt())
    {
    case WM_CLOSE:
        close();
        eventData[P_HANDLED] = true;
        break;
        
    case WM_DESTROY:
        mClosed = true;
        eventData[P_HANDLED] = true;
        break;
    }
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    using namespace WindowMessage;
    
    std::map<HWND, Renderer*>::const_iterator i = renderers.find(hwnd);
    if (i != renderers.end())
    {
        VariantMap eventData;
        eventData[P_WINDOW] = (int)hwnd;
        eventData[P_MSG] = (int)msg;
        eventData[P_WPARAM] = (int)wParam;
        eventData[P_LPARAM] = (int)lParam;
        eventData[P_HANDLED] = false;
        
        i->second->sendEvent(EVENT_WINDOWMESSAGE, eventData);
        if (eventData[P_HANDLED].getBool())
            return 0;
    }
    
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
