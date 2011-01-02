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
#include "Renderer.h"
#include "RendererEvents.h"
#include "RendererImpl.h"

RendererImpl::RendererImpl() :
    mInterface(0),
    mDevice(0),
    mDefaultColorSurface(0),
    mFrameQuery(0),
    mAdapter(D3DADAPTER_DEFAULT),
    mDeviceType(D3DDEVTYPE_HAL),
    mInstance(GetModuleHandle(0)),
    mWindow(0)
{
    memset(&mPresentParams, 0, sizeof mPresentParams);
}

bool RendererImpl::checkFormatSupport(D3DFORMAT format, DWORD usage, D3DRESOURCETYPE type)
{
    if (!mInterface)
        EXCEPTION("Initial display mode not set, could not check format support");
    
    if (SUCCEEDED(mInterface->CheckDeviceFormat(
        mAdapter,
        mDeviceType,
        D3DFMT_X8R8G8B8,
        usage,
        type,
        format)))
        return true;
    else
        return false;
}
