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

#pragma once

#include "Color.h"
#include "Map.h"

#include <GLee.h>
#include <GL/glfw3.h>

class Context;

/// %Graphics subsystem implementation. Holds API-specific objects.
class GraphicsImpl
{
    friend class Graphics;
    
public:
    /// Construct.
    GraphicsImpl();
    
private:
    /// GLFW window.
    GLFWwindow window_;
    /// Active texture unit.
    unsigned activeTexture_;
    /// Active draw buffers.
    unsigned drawBuffers_;
    /// Frame buffer object. Reused whenever rendering to a texture.
    unsigned fbo_;
    /// Vertex attributes in use.
    unsigned enabledAttributes_;
    /// Current pixel format.
    int pixelFormat_;
    /// Current depth bits.
    int depthBits_;
    /// Backbuffer depth bits.
    int windowDepthBits_;
    /// FBO bound flag.
    bool fboBound_;
};

/// Store execution context specific to the GLFW window
void SetWindowContext(GLFWwindow window, Context* context);
/// Return execution context specific to the GLFW window
Context* GetWindowContext(GLFWwindow window);
