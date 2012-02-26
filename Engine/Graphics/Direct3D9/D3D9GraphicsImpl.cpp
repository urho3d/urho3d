//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "GraphicsImpl.h"

GraphicsImpl::GraphicsImpl() :
    interface_(0),
    device_(0),
    defaultColorSurface_(0),
    adapter_(D3DADAPTER_DEFAULT),
    deviceType_(D3DDEVTYPE_HAL),
    instance_(GetModuleHandle(0)),
    window_(0)
{
    memset(&presentParams_, 0, sizeof presentParams_);
}

bool GraphicsImpl::CheckFormatSupport(D3DFORMAT format, DWORD usage, D3DRESOURCETYPE type)
{
    if (!interface_)
        return false;
    
    if (SUCCEEDED(interface_->CheckDeviceFormat(
        adapter_,
        deviceType_,
        D3DFMT_X8R8G8B8,
        usage,
        type,
        format)))
        return true;
    else
        return false;
}

D3DFORMAT GraphicsImpl::GetDesktopFormat()
{
    DEVMODE settings;
    EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &settings);
    return settings.dmBitsPerPel <= 16 ? D3DFMT_R5G6B5 : D3DFMT_X8R8G8B8;
}

IntVector2 GraphicsImpl::GetDesktopResolution()
{
    DEVMODE settings;
    EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &settings);
    return IntVector2(settings.dmPelsWidth, settings.dmPelsHeight);
}
