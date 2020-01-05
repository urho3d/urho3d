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

#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"

#include "../../DebugNew.h"

namespace Urho3D
{

GraphicsImpl::GraphicsImpl() :
    interface_(nullptr),
    device_(nullptr),
    defaultColorSurface_(nullptr),
    defaultDepthStencilSurface_(nullptr),
    frameQuery_(nullptr),
    adapter_(D3DADAPTER_DEFAULT),
    deviceType_(D3DDEVTYPE_HAL),
    shaderProgram_(nullptr),
    deviceLost_(false),
    queryIssued_(false)
{
    memset(&presentParams_, 0, sizeof presentParams_);
}

bool GraphicsImpl::CheckFormatSupport(D3DFORMAT format, DWORD usage, D3DRESOURCETYPE type)
{
    return interface_ ? SUCCEEDED(interface_->CheckDeviceFormat(adapter_, deviceType_, D3DFMT_X8R8G8B8, usage, type, format)) :
        false;
}

bool GraphicsImpl::CheckMultiSampleSupport(D3DFORMAT format, int level)
{
    return interface_ ? SUCCEEDED(interface_->CheckDeviceMultiSampleType(adapter_, deviceType_, format, FALSE,
        (D3DMULTISAMPLE_TYPE)level, nullptr)) : false;
}

}
