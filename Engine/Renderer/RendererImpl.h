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

#ifndef RENDERERIMPL_H
#define RENDERERIMPL_H

#include "Color.h"

#include <windows.h>
#include <d3d9.h>

//! Renderer implementation. Holds the Direct3D resources
class RendererImpl
{
    friend class Renderer;
    
public:
    //! Construct
    RendererImpl();
    
    //! Return Direct3D device
    IDirect3DDevice9* getDevice() const { return mDevice; }
    //! Return device capabilities
    const D3DCAPS9& getDeviceCaps() const { return mDeviceCaps; }
    //! Return window handle
    HWND getWindowHandle() const { return mWindow; }
    //! Return adapter identifier
    const D3DADAPTER_IDENTIFIER9& getAdapterIdentifier() const { return mAdapterIdentifier; }
    //! Return whether a texture format and usage is supported
    bool checkFormatSupport(D3DFORMAT format, DWORD usage, D3DRESOURCETYPE type);
    //! Return desktop texture format
    D3DFORMAT getDesktopFormat();
    //! Return desktop width/height
    IntVector2 getDesktopResolution();
    
private:
    //! Direct3D interface
    IDirect3D9* mInterface;
    //! Direct3D device
    IDirect3DDevice9* mDevice;
    //! Default color surface
    IDirect3DSurface9* mDefaultColorSurface;
    //! Default depth stencil surfac
    IDirect3DSurface9* mDefaultDepthStencilSurface;
    //! Frame query for flushing the GPU command queue
    IDirect3DQuery9* mFrameQuery;
    //! Adapter number
    DWORD mAdapter;
    //! Device type
    D3DDEVTYPE mDeviceType;
    //! Device capabilities
    D3DCAPS9 mDeviceCaps;
    //! Adapter identifier
    D3DADAPTER_IDENTIFIER9 mAdapterIdentifier;
    //! Application instance
    HINSTANCE mInstance;
    //! Application window
    HWND mWindow;
    //! Direct3D presentation parameters
    D3DPRESENT_PARAMETERS mPresentParams;
    //! Texture min/mag filter modes in use
    D3DTEXTUREFILTERTYPE mMinMagFilter[MAX_TEXTURE_UNITS];
    //! Texture mip filter modes in use
    D3DTEXTUREFILTERTYPE mMipFilter[MAX_TEXTURE_UNITS];
    //! Texture U coordinate addressing modes in use
    D3DTEXTUREADDRESS mUAddressMode[MAX_TEXTURE_UNITS];
    //! Texture V coordinate addressing modes in use
    D3DTEXTUREADDRESS mVAddressMode[MAX_TEXTURE_UNITS];
    //! Texture border colors in use
    Color mBorderColor[MAX_TEXTURE_UNITS];
    //! Color surfaces in use
    IDirect3DSurface9* mColorSurface[MAX_RENDERTARGETS];
    //! Depth stencil buffer in use
    IDirect3DSurface9* mDepthStencilSurface;
    //! Blending enabled flag
    DWORD mBlendEnable;
    //! Source blend mode
    D3DBLEND mSrcBlend;
    //! Destination blend mode
    D3DBLEND mDestBlend;
};

#endif // RENDERERIMPL_H
