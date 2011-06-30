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
#include "Context.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "GraphicsImpl.h"
#include "Mutex.h"
#include "ProcessUtils.h"

static HashMap<GLFWwindow, Context*> windowContexts;

GraphicsImpl::GraphicsImpl() :
    window_(0),
    activeTexture_(0),
    drawBuffers_(M_MAX_UNSIGNED),
    fbo_(0),
    enabledAttributes_(0),
    pixelFormat_(0),
    depthBits_(0),
    windowDepthBits_(0),
    fboBound_(false)
{
}

void SetWindowContext(GLFWwindow window, Context* context)
{
    MutexLock lock(GetStaticMutex());
    
    if (context)
        windowContexts[window] = context;
    else
        windowContexts.Erase(context);
}

Context* GetWindowContext(GLFWwindow window)
{
    MutexLock lock(GetStaticMutex());
    
    HashMap<GLFWwindow, Context*>::ConstIterator i = windowContexts.Find(window);
    if (i != windowContexts.End())
        return i->second_;
    else
        return 0;
}
