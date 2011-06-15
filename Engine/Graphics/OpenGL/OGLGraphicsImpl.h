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

#pragma once

#include "Color.h"
#include "Map.h"

#include <Windows.h>

/// Graphics implementation
class GraphicsImpl
{
    friend class Graphics;
    
public:
    /// Construct
    GraphicsImpl();

    /// Return window handle
    HWND GetWindowHandle() const { return window_; }
    /// Return desktop bits per pixel
    unsigned GetDesktopBitsPerPixel();
    /// Return desktop width/height
    IntVector2 GetDesktopResolution();
    
private:
    /// Application instance
    HINSTANCE instance_;
    /// Application window
    HWND window_;
    /// Device context_
    HDC deviceContext_;
    /// OpenGL render context
    HGLRC renderContext_;
    /// Active texture unit
    unsigned activeTexture_;
    /// Active draw buffers
    unsigned drawBuffers_;
    /// Frame buffer object. Reused whenever rendering to a texture
    unsigned fbo_;
    /// Vertex attributes in use
    unsigned enabledAttributes_;
    /// Current pixel format
    int pixelFormat_;
    /// Current depth bits
    int depthBits_;
    /// Backbuffer depth bits
    int windowDepthBits_;
    /// FBO bound flag
    bool fboBound_;
};
