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
#include "AnimatedModel.h"
#include "Animation.h"
#include "AnimationController.h"
#include "BillboardSet.h"
#include "Camera.h"
#include "Context.h"
#include "DebugRenderer.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "GraphicsImpl.h"
#include "IndexBuffer.h"
#include "Light.h"
#include "Log.h"
#include "Material.h"
#include "Mutex.h"
#include "Octree.h"
#include "ParticleEmitter.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "RenderSurface.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "ShaderVariation.h"
#include "Skybox.h"
#include "Technique.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "VertexBuffer.h"
#include "Zone.h"

#include <GLee.h>

#ifdef _MSC_VER
#include <float.h>
#endif

#include "DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

static const unsigned glCmpFunc[] =
{
    GL_ALWAYS,
    GL_EQUAL,
    GL_NOTEQUAL,
    GL_LESS,
    GL_LEQUAL,
    GL_GREATER,
    GL_GEQUAL
};

static const unsigned glSrcBlend[] =
{
    GL_ONE,
    GL_ONE,
    GL_DST_COLOR,
    GL_SRC_ALPHA,
    GL_SRC_ALPHA,
    GL_ONE,
    GL_ONE_MINUS_DST_ALPHA
};

static const unsigned glDestBlend[] =
{
    GL_ZERO,
    GL_ONE,
    GL_ZERO,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_ONE,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA
};

static const unsigned glStencilOps[] =
{
    GL_KEEP,
    GL_ZERO,
    GL_REPLACE,
    GL_INCR,
    GL_DECR
};

static const String noParameter;
static const DWORD windowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;

static LRESULT CALLBACK wndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

OBJECTTYPESTATIC(Graphics);

Graphics::Graphics(Context* context_) :
    Object(context_),
    impl_(new GraphicsImpl()),
    mode_(RENDER_FORWARD),
    width_(0),
    height_(0),
    multiSample_(0),
    windowPosX_(0),
    windowPosY_(0),
    fullscreen_(false),
    vsync_(false),
    flushGPU_(true),
    fullscreenModeSet_(false),
    inModeChange_(false),
    deferredSupport_(false),
    numPrimitives_(0),
    numBatches_(0),
    immediateVertexCount_(0),
    defaultTextureFilterMode_(FILTER_BILINEAR),
    shadowMapFormat_(0),
    hiresShadowMapFormat_(0)
{
    ResetCachedState();
    InitializeShaderParameters();
    
    SubscribeToEvent(E_WINDOWMESSAGE, HANDLER(Graphics, HandleWindowMessage));
    SubscribeToEvent(E_ACTIVATION, HANDLER(Graphics, HandleActivation));
}

Graphics::~Graphics()
{
    Close();
    
    delete impl_;
    impl_ = 0;
}

void Graphics::MessagePump()
{
    MSG msg;
    
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Graphics::SetWindowTitle(const String& windowTitle)
{
    windowTitle_ = windowTitle;
    if (impl_->window_)
        SetWindowText(impl_->window_, windowTitle_.CString());
}

bool Graphics::SetMode(RenderMode mode, int width, int height, bool fullscreen, bool vsync, int multiSample)
{
    PROFILE(SetScreenMode);
    
    /// \todo For now multisampling is not supported
    multiSample = 0;

    // If zero dimensions, use the desktop default
    if ((width <= 0) || (height <= 0))
    {
        if (fullscreen)
        {
            IntVector2 desktopResolution = impl_->GetDesktopResolution();
            width = desktopResolution.x_;
            height = desktopResolution.y_;
        }
        else
        {
            width = 800;
            height = 600;
        }
    }
    
    if ((mode == mode_) && (width == width_) && (height == height_) && (fullscreen == fullscreen_) && (vsync == vsync_)
        && (multiSample == multiSample_))
        return true;
    
    if (!impl_->window_)
    {
        if (!OpenWindow(width, height))
            return false;
    }
    
    // Save window placement if currently windowed
    if (!fullscreen_)
    {
        WINDOWPLACEMENT wndpl;
        wndpl.length = sizeof wndpl;
        if (SUCCEEDED(GetWindowPlacement(impl_->window_, &wndpl)))
        {
            windowPosX_ = wndpl.rcNormalPosition.left;
            windowPosY_ = wndpl.rcNormalPosition.top;
        }
    }
    
    // Create OpenGL context
    if (!impl_->renderContext_)
    {
        // Mimic Direct3D way of setting FPU into round-to-nearest, single precision mode
        #ifdef _MSC_VER
        _controlfp(_RC_NEAR | _PC_24, _MCW_RC | _MCW_PC);
        #endif
        
        impl_->renderContext_ = wglCreateContext(impl_->deviceContext_);
        wglMakeCurrent(impl_->deviceContext_, impl_->renderContext_);
        
        // Query for extensions now. Needs to happen under lock as the function pointers are static
        {
            MutexLock lock(GetStaticMutex());
            GLeeInit();
        }
        
        if (!_GLEE_VERSION_2_0)
        {
            LOGERROR("OpenGL 2.0 is required");
            return false;
        }
        
        // Create the FBO if supported
        if ((_GLEE_EXT_framebuffer_object) && (_GLEE_EXT_packed_depth_stencil))
        {
            glGenFramebuffersEXT(1, &impl_->fbo_);
            
            // If both FBO and packed depth stencil is supported, shadows and deferred rendering can be supported
            shadowMapFormat_ = GL_DEPTH_COMPONENT16;
            hiresShadowMapFormat_ = GL_DEPTH_COMPONENT24;
            deferredSupport_ = true;
        }
        
        // Set initial state to match Direct3D
        glEnable(GL_DEPTH_TEST);
        SetCullMode(CULL_CCW);
        SetDepthTest(CMP_LESSEQUAL);
    }
    
    // Change/restore desktop resolution as necessary
    if (fullscreen)
    {
        if (!SetScreenMode(width, height))
            fullscreen = false;
    }
    else
    {
        if (fullscreen_)
            RestoreScreenMode();
    }
    
    AdjustWindow(width, height, fullscreen);
    
    #ifdef WIN32
    if (wglSwapIntervalEXT)
        wglSwapIntervalEXT(vsync ? 1 : 0);
    #endif
    
    glGetIntegerv(GL_DEPTH_BITS, &impl_->windowDepthBits_);
    impl_->depthBits_ = impl_->windowDepthBits_;
    
    // Clear all additional depth buffers now, as they are possibly not needed any more
    depthTextures_.Clear();
    
    width_ = width;
    height_ = height;
    fullscreen_ = fullscreen;
    vsync_ = vsync;
    mode_ = mode;
    
    // Reset rendertargets and viewport for the new screen mode
    ResetRenderTargets();
    viewTexture_ = 0;
    
    // Get the system depth buffer's bit depth
    glGetIntegerv(GL_DEPTH_BITS, &impl_->depthBits_);
    
    // Create rendering buffers
    CreateRenderTargets();
    
    // Let screen mode dependent GPU objects update themselves
    for (Vector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
        (*i)->OnDeviceReset();
    
    if (!multiSample)
        LOGINFO("Set screen mode " + String(width_) + "x" + String(height_) + " " + (fullscreen_ ? "fullscreen" : "windowed"));
    else
        LOGINFO("Set screen mode " + String(width_) + "x" + String(height_) + " " + (fullscreen_ ? "fullscreen" : "windowed") +
        " multisample " + String(multiSample));
    
    using namespace ScreenMode;
    
    VariantMap eventData;
    eventData[P_WIDTH] = width_;
    eventData[P_HEIGHT] = height_;
    eventData[P_FULLSCREEN] = fullscreen_;
    SendEvent(E_SCREENMODE, eventData);
    
    return true;
}

bool Graphics::SetMode(int width, int height)
{
    return SetMode(mode_, width, height, fullscreen_, vsync_, multiSample_);
}

bool Graphics::SetMode(RenderMode mode)
{
    return SetMode(mode, width_, height_, fullscreen_, vsync_, multiSample_);
}

bool Graphics::ToggleFullscreen()
{
    return SetMode(mode_, width_, height_, !fullscreen_, vsync_, multiSample_);
}

void Graphics::Close()
{
    // Release all GPU objects that still exist
    for (Vector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
        (*i)->Release();
    gpuObjects_.Clear();
    
    if (impl_->renderContext_)
    {
        if (impl_->fbo_)
            glDeleteFramebuffersEXT(1, &impl_->fbo_);
        
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(impl_->renderContext_);
        impl_->renderContext_ = 0;
    }
    if (impl_->deviceContext_)
    {
        ReleaseDC(impl_->window_, impl_->deviceContext_);
        impl_->deviceContext_ = 0;
    }
    if (impl_->window_)
    {
        RestoreScreenMode();
        DestroyWindow(impl_->window_);
        impl_->window_ = 0;
    }
}

bool Graphics::TakeScreenShot(Image& destImage)
{
    PROFILE(TakeScreenShot);
    
    SetRenderTarget(0, (RenderSurface*)0);
    destImage.SetSize(width_, height_, 3);
    glReadPixels(0, 0, width_, height_, GL_RGB, GL_UNSIGNED_BYTE, destImage.GetData());
    
    return true;
}

void Graphics::SetFlushGPU(bool enable)
{
    flushGPU_ = enable;
}

bool Graphics::BeginFrame()
{
    PROFILE(BeginRendering);

    if (!IsInitialized())
        return false;
    
    // If we should be fullscreen, but the screen mode is not currently set, do not render
    if ((fullscreen_) && (!fullscreenModeSet_))
        return false;
    
    // Set default rendertarget and depth buffer
    ResetRenderTargets();
    viewTexture_ = 0;
    
    // Cleanup textures from previous frame
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        SetTexture(i, 0);
    
    // Enable color and depth write
    SetColorWrite(true);
    SetDepthWrite(true);
    
    numPrimitives_ = 0;
    numBatches_ = 0;
    
    SendEvent(E_BEGINRENDER);
    
    return true;
}

void Graphics::EndFrame()
{
    PROFILE(EndRendering);
    
    if (!IsInitialized())
        return;
    
    SendEvent(E_ENDRENDER);
    
    SwapBuffers(impl_->deviceContext_);
}

void Graphics::Clear(unsigned flags, const Color& color, float depth, unsigned stencil)
{
    bool oldColorWrite = colorWrite_;
    bool oldDepthWrite = depthWrite_;
    
    if ((flags & CLEAR_COLOR) && (!oldColorWrite))
        SetColorWrite(true);
    if ((flags & CLEAR_DEPTH) && (!oldDepthWrite))
        SetDepthWrite(true);
    
    unsigned glFlags = 0;
    if (flags & CLEAR_COLOR)
    {
        glFlags |= GL_COLOR_BUFFER_BIT;
        glClearColor(color.r_, color.g_, color.b_, color.a_);
    }
    if (flags & CLEAR_DEPTH)
    {
        glFlags |= GL_DEPTH_BUFFER_BIT;
        glClearDepth(depth);
    }
    if (flags & CLEAR_STENCIL)
    {
        glFlags |= GL_STENCIL_BUFFER_BIT;
        glClearStencil(stencil);
    }
    
    glClear(glFlags);
    
    SetColorWrite(oldColorWrite);
    SetDepthWrite(oldDepthWrite);
}

void Graphics::Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount)
{
    if (!vertexCount)
        return;
    
    unsigned primitiveCount = 0;
    
    switch (type)
    {
    case TRIANGLE_LIST:
        primitiveCount = vertexCount / 3;
        glDrawArrays(GL_TRIANGLES, vertexStart, vertexCount);
        break;
        
    case LINE_LIST:
        primitiveCount = vertexCount / 2;
        glDrawArrays(GL_LINES, vertexStart, vertexCount);
        break;
    }
    
    numPrimitives_ += primitiveCount;
    ++numBatches_;
}

void Graphics::Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount)
{
    if ((!indexCount) || (!indexBuffer_))
        return;
    
    unsigned primitiveCount = 0;
    unsigned indexSize = indexBuffer_->GetIndexSize();
    
    switch (type)
    {
    case TRIANGLE_LIST:
        primitiveCount = indexCount / 3;
        if (indexSize == sizeof(unsigned short))
            glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, (const GLvoid*)(indexStart * indexSize));
        else
            glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (const GLvoid*)(indexStart * indexSize));
        break;
        
    case LINE_LIST:
        primitiveCount = indexCount / 2;
        if (indexSize == sizeof(unsigned short))
            glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_SHORT, (const GLvoid*)(indexStart * indexSize));
        else
            glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, (const GLvoid*)(indexStart * indexSize));
        break;
    }
    
    numPrimitives_ += primitiveCount;
    ++numBatches_;
}

void Graphics::DrawInstanced(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount, unsigned instanceCount)
{
}

void Graphics::SetVertexBuffer(VertexBuffer* buffer)
{
    Vector<VertexBuffer*> vertexBuffers(1);
    PODVector<unsigned> elementMasks(1);
    vertexBuffers[0] = buffer;
    elementMasks[0] = MASK_DEFAULT;
    SetVertexBuffers(vertexBuffers, elementMasks);
}

bool Graphics::SetVertexBuffers(const Vector<VertexBuffer*>& buffers, const PODVector<unsigned>& elementMasks,
    unsigned instanceOffset)
{
    if (buffers.Size() > MAX_VERTEX_STREAMS)
    {
        LOGERROR("Too many vertex buffers");
        return false;
    }
    if (buffers.Size() != elementMasks.Size())
    {
        LOGERROR("Amount of element masks and vertex buffers does not match");
        return false;
    }
    
    // If no valid shader to determine the attribute bindings, can not set vertex buffers
    if (!shaderProgram_)
        return false;
    const int* attributeLocations = shaderProgram_->GetAttributeLocations();
    
    bool changed = false;
    unsigned newAttributes = 0;
    
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        VertexBuffer* buffer = 0;
        unsigned elementMask = 0;
        
        if (i < buffers.Size())
        {
            buffer = buffers[i];
            elementMask = elementMasks[i];
            if ((elementMask == MASK_DEFAULT) && (buffer))
                elementMask = buffers[i]->GetElementMask();
        }
        
        // If buffer and element mask have stayed the same, skip to the next buffer
        if ((buffer == vertexBuffers_[i]) && (elementMask == elementMasks_[i]))
            continue;
        
        vertexBuffers_[i] = buffer;
        elementMasks_[i] = elementMask;
        changed = true;
        
        if (!buffer)
            continue;
        
        glBindBuffer(GL_ARRAY_BUFFER, buffer->GetGPUObject());
        unsigned vertexSize = buffer->GetVertexSize();
        
        for (unsigned j = 0; j < MAX_VERTEX_ELEMENTS; ++j)
        {
            // If shader does not use the attribute, do not bind it (bandwidth optimization)
            int attributeIndex = attributeLocations[j];
            if (attributeIndex < 0)
                continue;
            
            unsigned elementBit = 1 << j;
            unsigned attributeBit = 1 << attributeIndex;
            
            if (elementMask & elementBit)
            {
                newAttributes |= attributeBit;
                
                // Enable attribute if not enabled yet
                if ((impl_->enabledAttributes_ & attributeBit) == 0)
                {
                    glEnableVertexAttribArray(attributeIndex);
                    impl_->enabledAttributes_ |= attributeBit;
                }
                
                // Set the attribute pointer
                glVertexAttribPointer(attributeIndex, VertexBuffer::elementComponents[j], VertexBuffer::elementType[j],
                    VertexBuffer::elementNormalize[j], vertexSize, (const GLvoid*)(buffer->GetElementOffset((VertexElement)j)));
            }
        }
    }
    
    if (!changed)
        return true;
    
    // Now check which vertex attributes should be disabled
    unsigned disableAttributes = impl_->enabledAttributes_ & (~newAttributes);
    int disableIndex = 0;
    while (disableAttributes)
    {
        if (disableAttributes & 1)
        {
            glDisableVertexAttribArray(disableIndex);
            impl_->enabledAttributes_ &= ~(1 << disableIndex);
        }
        disableAttributes >>= 1;
        ++disableIndex;
    }
    
    return true;
}

bool Graphics::SetVertexBuffers(const Vector<SharedPtr<VertexBuffer> >& buffers, const PODVector<unsigned>&
    elementMasks, unsigned instanceOffset)
{
    if (buffers.Size() > MAX_VERTEX_STREAMS)
    {
        LOGERROR("Too many vertex buffers");
        return false;
    }
    if (buffers.Size() != elementMasks.Size())
    {
        LOGERROR("Amount of element masks and vertex buffers does not match");
        return false;
    }
    
    // If no valid shader to determine the attribute bindings, can not set vertex buffers
    if (!shaderProgram_)
        return false;
    const int* attributeLocations = shaderProgram_->GetAttributeLocations();
    
    bool changed = false;
    unsigned newAttributes = 0;
    
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        VertexBuffer* buffer = 0;
        unsigned elementMask = 0;
        
        if (i < buffers.Size())
        {
            buffer = buffers[i];
            elementMask = elementMasks[i];
            if ((elementMask == MASK_DEFAULT) && (buffer))
                elementMask = buffers[i]->GetElementMask();
        }
        
        // If buffer and element mask have stayed the same, skip to the next buffer
        if ((buffer == vertexBuffers_[i]) && (elementMask == elementMasks_[i]))
            continue;
        
        vertexBuffers_[i] = buffer;
        elementMasks_[i] = elementMask;
        changed = true;
        
        if (!buffer)
            continue;
        
        glBindBuffer(GL_ARRAY_BUFFER, buffer->GetGPUObject());
        unsigned vertexSize = buffer->GetVertexSize();
        
        for (unsigned j = 0; j < MAX_VERTEX_ELEMENTS; ++j)
        {
            // If shader does not use the attribute, do not bind it (bandwidth optimization)
            int attributeIndex = attributeLocations[j];
            if (attributeIndex < 0)
                continue;
            
            unsigned elementBit = 1 << j;
            unsigned attributeBit = 1 << attributeIndex;
            
            if (elementMask & elementBit)
            {
                newAttributes |= attributeBit;
                
                // Enable attribute if not enabled yet
                if ((impl_->enabledAttributes_ & attributeBit) == 0)
                {
                    glEnableVertexAttribArray(attributeIndex);
                    impl_->enabledAttributes_ |= attributeBit;
                }
                
                // Set the attribute pointer
                glVertexAttribPointer(attributeIndex, VertexBuffer::elementComponents[j], VertexBuffer::elementType[j],
                    VertexBuffer::elementNormalize[j], vertexSize, (const GLvoid*)(buffer->GetElementOffset((VertexElement)j)));
            }
        }
    }
    
    if (!changed)
        return true;
    
    // Now check which vertex attributes should be disabled
    unsigned disableAttributes = impl_->enabledAttributes_ & (~newAttributes);
    int disableIndex = 0;
    while (disableAttributes)
    {
        if (disableAttributes & 1)
        {
            glDisableVertexAttribArray(disableIndex);
            impl_->enabledAttributes_ &= ~(1 << disableIndex);
        }
        disableAttributes >>= 1;
        ++disableIndex;
    }
    
    return true;
}

void Graphics::SetIndexBuffer(IndexBuffer* buffer)
{
    if (indexBuffer_ == buffer)
        return;
    
    if (buffer)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->GetGPUObject());
    else
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    indexBuffer_ = buffer;
}

void Graphics::SetShaders(ShaderVariation* vs, ShaderVariation* ps)
{
    if ((vs == vertexShader_) && (ps == pixelShader_))
        return;
    
    // All vertex attributes must be re-bound after shader change, and uniforms need to be reassigned
    ClearLastParameterSources();
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        vertexBuffers_[i] = 0;
        elementMasks_[i] = 0;
    }
    
    if ((!vs) || (!ps))
    {
        glUseProgram(0);
        vertexShader_ = 0;
        pixelShader_ = 0;
        shaderProgram_ = 0;
    }
    else
    {
        vertexShader_ = vs;
        pixelShader_ = ps;
        
        Pair<ShaderVariation*, ShaderVariation*> combination(vs, ps);
        ShaderProgramMap::Iterator i = shaderPrograms_.Find(combination);
        
        if (i != shaderPrograms_.End())
        {
            // Use the existing linked program
            if (i->second_->IsLinked())
            {
                glUseProgram(i->second_->GetGPUObject());
                shaderProgram_ = i->second_;
            }
            else
            {
                glUseProgram(0);
                shaderProgram_ = 0;
            }
        }
        else
        {
            // Link a new combination
            SharedPtr<ShaderProgram> newProgram(new ShaderProgram(this, vs, ps));
            if (!newProgram->Link())
            {
                LOGERROR("Failed to link shader " + vs->GetShader()->GetName() + ":\n" +
                    newProgram->GetLinkerOutput());
                glUseProgram(0);
                shaderProgram_ = 0;
            }
            else
            {
                // Note: Link() calls glUseProgram() to set the texture sampler uniforms,
                // so it is not necessary to call it again
                shaderProgram_ = newProgram;
            }
            
            shaderPrograms_[combination] = newProgram;
        }
    }
}

void Graphics::SetShaderParameter(ShaderParameter param, const bool* data, unsigned count)
{
    // Not supported
}

void Graphics::SetShaderParameter(ShaderParameter param, const float* data, unsigned count)
{
    if (shaderProgram_)
    {
        const UniformInfo* info = shaderProgram_->GetUniformInfo(param);
        if (info)
        {
            switch (info->type_)
            {
            case GL_FLOAT:
                glUniform1fv(info->location_, count, data);
                break;
                
            case GL_FLOAT_VEC2:
                glUniform2fv(info->location_, count / 2, data);
                break;
                
            case GL_FLOAT_VEC3:
                glUniform3fv(info->location_, count / 3, data);
                break;
                
            case GL_FLOAT_VEC4:
                glUniform4fv(info->location_, count / 4, data);
                break;
                
            case GL_FLOAT_MAT3:
                glUniformMatrix3fv(info->location_, count / 9, GL_TRUE, data);
                break;
                
            case GL_FLOAT_MAT4:
                glUniformMatrix4fv(info->location_, count / 16, GL_TRUE, data);
                break;
            }
        }
    }
}

void Graphics::SetShaderParameter(ShaderParameter param, const int* data, unsigned count)
{
    if (shaderProgram_)
    {
        const UniformInfo* info = shaderProgram_->GetUniformInfo(param);
        if (info)
        {
            switch (info->type_)
            {
            case GL_INT:
                glUniform1iv(info->location_, count, data);
                break;
                
            case GL_INT_VEC2:
                glUniform2iv(info->location_, count / 2, data);
                break;
                
            case GL_INT_VEC3:
                glUniform3iv(info->location_, count / 3, data);
                break;
                
            case GL_INT_VEC4:
                glUniform4iv(info->location_, count / 4, data);
                break;
            }
        }
    }
}

void Graphics::SetShaderParameter(ShaderParameter param, float value)
{
    if (shaderProgram_)
    {
        const UniformInfo* info = shaderProgram_->GetUniformInfo(param);
        if (info)
            glUniform1fv(info->location_, 1, &value);
    }
}

void Graphics::SetShaderParameter(ShaderParameter param, const Color& color)
{
    SetShaderParameter(param, color.GetData(), 4);
}

void Graphics::SetShaderParameter(ShaderParameter param, const Matrix3& matrix)
{
    if (shaderProgram_)
    {
        const UniformInfo* info = shaderProgram_->GetUniformInfo(param);
        if (info)
            glUniformMatrix3fv(info->location_, 1, GL_TRUE, matrix.GetData());
    }
}


void Graphics::SetShaderParameter(ShaderParameter param, const Vector3& vector)
{
    if (shaderProgram_)
    {
        const UniformInfo* info = shaderProgram_->GetUniformInfo(param);
        if (info)
        {
            // Check the uniform type to avoid mismatch
            switch (info->type_)
            {
            case GL_FLOAT:
                glUniform1fv(info->location_, 1, vector.GetData());
                break;
                
            case GL_FLOAT_VEC2:
                glUniform2fv(info->location_, 1, vector.GetData());
                break;
                
            case GL_FLOAT_VEC3:
                glUniform3fv(info->location_, 1, vector.GetData());
                break;
            }
        }
    }
}

void Graphics::SetShaderParameter(ShaderParameter param, const Matrix4& matrix)
{
    if (shaderProgram_)
    {
        const UniformInfo* info = shaderProgram_->GetUniformInfo(param);
        if (info)
            glUniformMatrix4fv(info->location_, 1, GL_TRUE, matrix.GetData());
    }
}

void Graphics::SetShaderParameter(ShaderParameter param, const Vector4& vector)
{
    if (shaderProgram_)
    {
        const UniformInfo* info = shaderProgram_->GetUniformInfo(param);
        if (info)
        {
            // Check the uniform type to avoid mismatch
            switch (info->type_)
            {
            case GL_FLOAT:
                glUniform1fv(info->location_, 1, vector.GetData());
                break;
                
            case GL_FLOAT_VEC2:
                glUniform2fv(info->location_, 1, vector.GetData());
                break;
                
            case GL_FLOAT_VEC3:
                glUniform3fv(info->location_, 1, vector.GetData());
                break;
                
            case GL_FLOAT_VEC4:
                glUniform4fv(info->location_, 1, vector.GetData());
                break;
            }
        }
    }
}

void Graphics::SetShaderParameter(ShaderParameter param, const Matrix3x4& matrix)
{
    if (shaderProgram_)
    {
        const UniformInfo* info = shaderProgram_->GetUniformInfo(param);
        if (info)
        {
            float data[16];
            data[0] = matrix.m00_;
            data[1] = matrix.m01_;
            data[2] = matrix.m02_;
            data[3] = matrix.m03_;
            data[4] = matrix.m10_;
            data[5] = matrix.m11_;
            data[6] = matrix.m12_;
            data[7] = matrix.m13_;
            data[8] = matrix.m20_;
            data[9] = matrix.m21_;
            data[10] = matrix.m22_;
            data[11] = matrix.m23_;
            data[12] = 0.0f;
            data[13] = 0.0f;
            data[14] = 0.0f;
            data[15] = 1.0f;
            
            glUniformMatrix4fv(info->location_, 1, GL_TRUE, data);
        }
    }
}

bool Graphics::NeedParameterUpdate(ShaderParameter param, const void* source)
{
    if ((shaderProgram_) && (shaderProgram_->HasParameter(param)) && (lastShaderParameterSources_[param] != source))
    {
        lastShaderParameterSources_[param] = source;
        return true;
    }
    
    return false;
}

bool Graphics::NeedTextureUnit(TextureUnit unit)
{
    if ((shaderProgram_) && (shaderProgram_->HasTextureUnit(unit)))
        return true;
    
    return false;
}

void Graphics::ClearLastParameterSources()
{
    for (unsigned i = 0; i < MAX_SHADER_PARAMETERS; ++i)
        lastShaderParameterSources_[i] = (const void*)M_MAX_UNSIGNED;
}

void Graphics::ClearTransformSources()
{
    lastShaderParameterSources_[VSP_MODEL] = (const void*)M_MAX_UNSIGNED;
    lastShaderParameterSources_[VSP_VIEWPROJ] = (const void*)M_MAX_UNSIGNED;
}

void Graphics::CleanupShaderPrograms()
{
    for (ShaderProgramMap::Iterator i = shaderPrograms_.Begin(); i != shaderPrograms_.End();)
    {
        ShaderProgramMap::Iterator current = i++;
        if (!current->second_->GetGPUObject())
        {
            if (shaderProgram_ == current->second_)
                shaderProgram_ = 0;
            shaderPrograms_.Erase(current);
        }
    }
}

void Graphics::SetTexture(unsigned index, Texture* texture)
{
    if (index >= MAX_TEXTURE_UNITS)
        return;
    
    // Check if texture is currently bound as a render target. In that case, use its backup texture, or blank if not defined
    if (texture)
    {
        if ((renderTargets_[0]) && (renderTargets_[0]->GetParentTexture() == texture))
            texture = texture->GetBackupTexture();
        // Check also for the view texture, in case a specific rendering pass does not bind the destination render target,
        // but should still not sample it either
        else if (texture == viewTexture_)
            texture = texture->GetBackupTexture();
    }
    
    if (textures_[index] != texture)
    {
        if (impl_->activeTexture_ != index)
        {
            glActiveTexture(GL_TEXTURE0 + index);
            impl_->activeTexture_ = index;
        }
        
        if (texture)
        {
            unsigned glType = texture->GetTarget();
            if (glType != textureTypes_[index])
            {
                if (textureTypes_[index])
                    glDisable(textureTypes_[index]);
                
                glEnable(glType);
                textureTypes_[index] = glType;
            }
            
            glBindTexture(glType, texture->GetGPUObject());
            
            if (texture->GetParametersDirty())
                texture->UpdateParameters();
        }
        else
        {
            if (textureTypes_[index])
                glBindTexture(textureTypes_[index], 0);
        }
        
        textures_[index] = texture;
    }
    else
    {
        if ((texture) && (texture->GetParametersDirty()))
        {
            if (impl_->activeTexture_ != index)
            {
                glActiveTexture(GL_TEXTURE0 + index);
                impl_->activeTexture_ = index;
            }
            
            glBindTexture(texture->GetTarget(), texture->GetGPUObject());
            texture->UpdateParameters();
        }
    }
}

void Graphics::SetTextureForUpdate(Texture* texture)
{
    if (impl_->activeTexture_ != 0)
    {
        glActiveTexture(GL_TEXTURE0);
        impl_->activeTexture_ = 0;
    }
    
    glBindTexture(texture->GetTarget(), texture->GetGPUObject());
    textures_[0] = texture;
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
    for (Vector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
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
    if ((index >= MAX_RENDERTARGETS) || (!impl_->fbo_))
        return;
    
    if (renderTarget != renderTargets_[index])
    {
        renderTargets_[index] = renderTarget;
        
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
        
        // Bind the FBO to be able to make changes to it
        if (!impl_->fboBound_)
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, impl_->fbo_);
            impl_->fboBound_ = true;
        }
        
        if (renderTarget)
        {
            Texture* texture = renderTarget->GetParentTexture();
            
            // If texture's parameters are dirty, update before attaching
            if (texture->GetParametersDirty())
            {
                SetTextureForUpdate(texture);
                texture->UpdateParameters();
                SetTexture(0, 0);
            }
            
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + index, renderTarget->GetTarget(), texture->GetGPUObject(), 0);
        }
        else
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + index, GL_TEXTURE_2D, 0, 0);
        
        // Disable color buffer writing/reading if only a depth texture is to be used:
        // otherwise it is an OpenGL error (incomplete framebuffer)
        SetDrawBuffers();
        
        // If all rendertargets and the depth buffer are not textures, revert to backbuffer rendering
        bool noFBO = (depthStencil_ == 0);
        for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        {
            if (renderTargets_[i])
            {
                noFBO = false;
                break;
            }
        }
        
        if ((noFBO) && (impl_->fboBound_))
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
            impl_->fboBound_ = false;
        }
    }
}

void Graphics::SetRenderTarget(unsigned index, Texture2D* renderTexture)
{
    RenderSurface* renderTarget = 0;
    if (renderTexture)
        renderTarget = renderTexture->GetRenderSurface();
    
    SetRenderTarget(index, renderTarget);
}

void Graphics::SetDepthStencil(RenderSurface* depthStencil)
{
    if ((impl_->fbo_) && (depthStencil != depthStencil_))
    {
        // If we are using a rendertarget texture, it is required in OpenGL to also have an own depth stencil
        // Create a new depth stencil texture as necessary to be able to provide similar behaviour.
        if ((renderTargets_[0]) && (!depthStencil))
        {
            int width = renderTargets_[0]->GetWidth();
            int height = renderTargets_[0]->GetHeight();
            // Reuse the deferred depth buffer if possible
            if ((depthBuffer_) && (width == width_) && (height == height_))
                depthStencil = depthBuffer_->GetRenderSurface();
            else
            {
                int searchKey = (width << 16) | height;
                Map<int, SharedPtr<Texture2D> >::Iterator i = depthTextures_.Find(searchKey);
                if (i != depthTextures_.End())
                    depthStencil = i->second_->GetRenderSurface();
                else
                {
                    SharedPtr<Texture2D> newDepthTexture(new Texture2D(context_));
                    newDepthTexture->SetSize(width, height, GetDepthStencilFormat(), TEXTURE_DEPTHSTENCIL);
                    depthTextures_[searchKey] = newDepthTexture;
                    depthStencil = newDepthTexture->GetRenderSurface();
                }
            }
        }
        
        /// \todo Should check if the texture actually is in depth format
        depthStencil_ = depthStencil;
        
        // Bind the FBO to be able to make changes to it
        if (!impl_->fboBound_)
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, impl_->fbo_);
            impl_->fboBound_ = true;
        }
        
        if (depthStencil)
        {
            Texture* texture = depthStencil->GetParentTexture();
            
            // If texture's parameters are dirty, update before attaching
            if (texture->GetParametersDirty())
            {
                SetTextureForUpdate(texture);
                texture->UpdateParameters();
                SetTexture(0, 0);
            }
            
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, texture->GetGPUObject(), 0);
            impl_->depthBits_ = texture->GetDepthBits();
        }
        else
        {
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, 0, 0);
            impl_->depthBits_ = impl_->windowDepthBits_;
        }
        
        // Disable color buffer writing/reading if only a depth texture is to be used:
        // otherwise it is an OpenGL error (incomplete framebuffer)
        SetDrawBuffers();
        
        // If all rendertargets and the depth buffer are not textures, revert to backbuffer rendering
        bool noFBO = (depthStencil_ == 0);
        for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        {
            if (renderTargets_[i])
            {
                noFBO = false;
                break;
            }
        }
        
        if ((noFBO) && (impl_->fboBound_))
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
            impl_->fboBound_ = false;
        }
    }
    
    // Reset viewport and scissor test
    IntVector2 viewSize = GetRenderTargetDimensions();
    SetViewport(IntRect(0, 0, viewSize.x_, viewSize.y_));
    SetScissorTest(false);
}

void Graphics::SetDepthStencil(Texture2D* depthTexture)
{
    RenderSurface* depthStencil = 0;
    if (depthTexture)
        depthStencil = depthTexture->GetRenderSurface();
    
    SetDepthStencil(depthStencil);
}

void Graphics::SetViewport(const IntRect& rect)
{
    IntVector2 rtSize = GetRenderTargetDimensions();
    
    IntRect rectCopy = rect;
    
    if (rectCopy.right_ <= rectCopy.left_)
        rectCopy.right_ = rectCopy.left_ + 1;
    if (rectCopy.bottom_ <= rectCopy.top_)
        rectCopy.bottom_ = rectCopy.top_ + 1;
    rectCopy.left_ = Clamp(rectCopy.left_, 0, rtSize.x_);
    rectCopy.top_ = Clamp(rectCopy.top_, 0, rtSize.y_);
    rectCopy.right_ = Clamp(rectCopy.right_, 0, rtSize.x_);
    rectCopy.bottom_ = Clamp(rectCopy.bottom_, 0, rtSize.y_);
    
    if (rectCopy != viewport_)
    {
        // Use Direct3D convention with the vertical coordinates ie. 0 is top
        glViewport(rectCopy.left_, rtSize.y_ - rectCopy.bottom_, rectCopy.right_ - rectCopy.left_, rectCopy.bottom_ - rectCopy.top_);
        viewport_ = rectCopy;
    }
    
    // Disable scissor test, needs to be re-enabled by the user
    SetScissorTest(false);
}

void Graphics::SetViewTexture(Texture* texture)
{
    viewTexture_ = texture;
    
    // Check for the view texture being currently bound
    if (texture)
    {
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (textures_[i] == texture)
                SetTexture(i, textures_[i]->GetBackupTexture());
        }
    }
}

void Graphics::SetAlphaTest(bool enable, CompareMode mode, float alphaRef)
{
    if (enable != alphaTest_)
    {
        if (enable)
            glEnable(GL_ALPHA_TEST);
        else
            glDisable(GL_ALPHA_TEST);
        alphaTest_ = enable;
    }
    
    if (enable)
    {
        alphaRef = Clamp(alphaRef, 0.0f, 1.0f);
        if ((mode != alphaTestMode_) || (alphaRef != alphaRef_))
        {
            glAlphaFunc(glCmpFunc[mode], alphaRef);
            alphaTestMode_ = mode;
            alphaRef_ = alphaRef;
        }
    }
}

void Graphics::SetBlendMode(BlendMode mode)
{
    if (mode != blendMode_)
    {
        if (mode == BLEND_REPLACE)
            glDisable(GL_BLEND);
        else
        {
            glEnable(GL_BLEND);
            glBlendFunc(glSrcBlend[mode], glDestBlend[mode]);
        }
        
        blendMode_ = mode;
    }
}

void Graphics::SetColorWrite(bool enable)
{
    if (enable != colorWrite_)
    {
        if (enable)
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        else
            glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        
        colorWrite_ = enable;
    }
}

void Graphics::SetCullMode(CullMode mode)
{
    if (mode != cullMode_)
    {
        if (mode == CULL_NONE)
            glDisable(GL_CULL_FACE);
        else
        {
            // Use Direct3D convention, ie. clockwise vertices define a front face
            glEnable(GL_CULL_FACE);
            glCullFace(mode == CULL_CCW ? GL_FRONT : GL_BACK);
        }
        
        cullMode_ = mode;
    }
}

void Graphics::SetDepthBias(float constantBias, float slopeScaledBias)
{
    if ((constantBias != constantDepthBias_) || (slopeScaledBias != slopeScaledDepthBias_))
    {
        if ((constantBias != 0.0f) || (slopeScaledBias != 0.0f))
        {
            // Bring the constant bias from Direct3D9 scale to OpenGL (depends on depth buffer bitdepth)
            // Zero depth bits may be returned if using the packed depth stencil format. Assume 24bit in that case
            int depthBits = min(impl_->depthBits_, 23);
            if (!depthBits)
                depthBits = 23;
            float adjustedConstantBias = constantBias * (float)(1 << (depthBits - 1));
            float adjustedSlopeScaledBias = slopeScaledBias + 1.0f;
            
            glEnable(GL_POLYGON_OFFSET_FILL);
            glEnable(GL_POLYGON_OFFSET_LINE);
            glPolygonOffset(adjustedSlopeScaledBias, adjustedConstantBias);
        }
        else
        {
            glDisable(GL_POLYGON_OFFSET_FILL);
            glDisable(GL_POLYGON_OFFSET_LINE);
        }
        
        constantDepthBias_ = constantBias;
        slopeScaledDepthBias_ = slopeScaledBias;
    }
}

void Graphics::SetDepthTest(CompareMode mode)
{
    if (mode != depthTestMode_)
    {
        glDepthFunc(glCmpFunc[mode]);
        depthTestMode_ = mode;
    }
}

void Graphics::SetDepthWrite(bool enable)
{
    if (enable != depthWrite_)
    {
        glDepthMask(enable ? GL_TRUE : GL_FALSE);
        depthWrite_ = enable;
    }
}

void Graphics::SetFillMode(FillMode mode)
{
    if (mode != fillMode_)
    {
        glPolygonMode(GL_FRONT_AND_BACK, mode == FILL_SOLID ? GL_FILL : GL_LINE);
        fillMode_ = mode;
    }
}

void Graphics::SetScissorTest(bool enable, const Rect& rect, bool borderInclusive)
{
     // During some light rendering loops, a full rect is toggled on/off repeatedly.
    // Disable scissor in that case to reduce state changes
    if ((rect.min_.x_ <= 0.0f) && (rect.min_.y_ <= 0.0f) && (rect.max_.y_ >= 1.0f) && (rect.max_.y_ >= 1.0f))
        enable = false;
    
    // Check for illegal rect, disable in that case
    if ((rect.max_.x_ < rect.min_.x_) || (rect.max_.y_ < rect.min_.y_))
        enable = false;
    
    if (enable)
    {
        IntVector2 rtSize(GetRenderTargetDimensions());
        IntVector2 viewSize(viewport_.right_ - viewport_.left_, viewport_.bottom_ - viewport_.top_);
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
        
        if ((intRect.right_ < intRect.left_) || (intRect.bottom_ < intRect.top_))
            enable = false;
        
        if ((enable) && (scissorRect_ != intRect))
        {
            // Use Direct3D convention with the vertical coordinates ie. 0 is top
            glScissor(intRect.left_, rtSize.y_ - intRect.bottom_, intRect.right_ - intRect.left_, intRect.bottom_ - intRect.top_);
            scissorRect_ = intRect;
        }
    }
    else
        scissorRect_ = IntRect::ZERO;
    
    if (enable != scissorTest_)
    {
        if (enable)
            glEnable(GL_SCISSOR_TEST);
        else
            glDisable(GL_SCISSOR_TEST);
        scissorTest_ = enable;
    }
}

void Graphics::SetScissorTest(bool enable, const IntRect& rect)
{
    IntVector2 rtSize(GetRenderTargetDimensions());
    IntVector2 viewSize(viewport_.right_ - viewport_.left_, viewport_.bottom_ - viewport_.top_);
    IntVector2 viewPos(viewport_.left_, viewport_.top_);
    
    // Full scissor is same as disabling the test
    if ((rect.left_ <= 0) && (rect.right_ >= viewSize.x_) && (rect.top_ <= 0) && (rect.bottom_ >= viewSize.y_))
        enable = false;
    
    // Check for illegal rect, disable in that case
    if ((rect.right_ < rect.left_) || (rect.bottom_ < rect.top_))
        enable = false;
    
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
        
        if ((intRect.right_ < intRect.left_) || (intRect.bottom_ < intRect.top_))
            enable = false;
        
        if ((enable) && (scissorRect_ != intRect))
        {
            // Use Direct3D convention with the vertical coordinates ie. 0 is top
            glScissor(intRect.left_, rtSize.y_ - intRect.bottom_, intRect.right_ - intRect.left_, intRect.bottom_ - intRect.top_);
            scissorRect_ = intRect;
        }
    }
    else
        scissorRect_ = IntRect::ZERO;
    
    if (enable != scissorTest_)
    {
        if (enable)
            glEnable(GL_SCISSOR_TEST);
        else
            glDisable(GL_SCISSOR_TEST);
        scissorTest_ = enable;
    }
}

void Graphics::SetStreamFrequency(unsigned index, unsigned frequency)
{
}

void Graphics::ResetStreamFrequencies()
{
}

void Graphics::SetStencilTest(bool enable, CompareMode mode, StencilOp pass, StencilOp fail, StencilOp zFail, unsigned stencilRef, unsigned stencilMask)
{
    if (enable != stencilTest_)
    {
        if (enable)
            glEnable(GL_STENCIL_TEST);
        else
            glDisable(GL_STENCIL_TEST);
        stencilTest_ = enable;
    }
    
    if (enable)
    {
        if ((mode != stencilTestMode_) || (stencilRef != stencilRef_) || (stencilMask != stencilMask_))
        {
            glStencilFunc(glCmpFunc[mode], stencilRef, stencilMask);
            stencilTestMode_ = mode;
            stencilRef_ = stencilRef;
            stencilMask_ = stencilMask;
        }
        if ((pass != stencilPass_) || (fail != stencilFail_) || (!zFail != stencilZFail_))
        {
            glStencilOp(glStencilOps[fail], glStencilOps[zFail], glStencilOps[pass]);
            stencilPass_ = pass;
            stencilFail_ = fail;
            stencilZFail_ = zFail;
        }
    }
}

bool Graphics::BeginImmediate(PrimitiveType type, unsigned vertexCount, unsigned elementMask)
{
    if (immediateVertexCount_)
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
    
    // Resize the buffer if it is too small
    unsigned vertexSize = VertexBuffer::GetVertexSize(elementMask);
    if (immediateVertexData_.Size() < vertexCount * vertexSize)
        immediateVertexData_.Resize(vertexCount * vertexSize);
    
    // Note: the data pointer gets pre-decremented here, because the first call to DefineVertex() will increment it
    immediateDataPtr_ = &immediateVertexData_[0] - vertexSize;
    immediateType_= type;
    immediateVertexCount_ = vertexCount;
    immediateVertexSize_ = vertexSize;
    immediateElementMask_ = elementMask;
    immediateCurrentVertex_ = 0;
    
    unsigned dataOffset = 0;
    for (unsigned i = ELEMENT_POSITION; i <= ELEMENT_TEXCOORD1; ++i)
    {
        immediateElementOffsets_[i] = dataOffset;
        if (elementMask & (1 << i))
            dataOffset += VertexBuffer::elementSize[i];
    }
    
    return true;
}

bool Graphics::DefineVertex(const Vector3& vertex)
{
    if ((!immediateVertexCount_) || (immediateCurrentVertex_ >= immediateVertexCount_))
        return false;
    
    immediateDataPtr_ += immediateVertexSize_;
    ++immediateCurrentVertex_;
    
    float* dest = (float*)(immediateDataPtr_ + immediateElementOffsets_[ELEMENT_POSITION]);
    const float* src = vertex.GetData();
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    
    return true;
}

bool Graphics::DefineNormal(const Vector3& normal)
{
    if ((!immediateVertexCount_) || (!(immediateElementMask_ & MASK_NORMAL)) || (!immediateCurrentVertex_))
        return false;
    
    float* dest = (float*)(immediateDataPtr_ + immediateElementOffsets_[ELEMENT_NORMAL]);
    const float* src = normal.GetData();
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    
    return true;
}

bool Graphics::DefineTexCoord(const Vector2& texCoord)
{
    if ((!immediateVertexCount_) || (!(immediateElementMask_ & MASK_TEXCOORD1)) || (!immediateCurrentVertex_))
        return false;
    
    float* dest = (float*)(immediateDataPtr_ + immediateElementOffsets_[ELEMENT_TEXCOORD1]);
    const float* src = texCoord.GetData();
    dest[0] = src[0];
    dest[1] = src[1];
    
    return true;
}

bool Graphics::DefineColor(const Color& color)
{
    if ((!immediateVertexCount_) || (!(immediateElementMask_ & MASK_COLOR)) || (!immediateCurrentVertex_))
        return false;
    
    unsigned* dest = (unsigned*)(immediateDataPtr_ + immediateElementOffsets_[ELEMENT_COLOR]);
    *dest = color.ToUInt();
    
    return true;
}

bool Graphics::DefineColor(unsigned color)
{
    if ((!immediateVertexCount_) || (!(immediateElementMask_ & MASK_COLOR)) || (!immediateCurrentVertex_))
        return false;
    
    unsigned* dest = (unsigned*)(immediateDataPtr_ + immediateElementOffsets_[ELEMENT_COLOR]);
    *dest = color;
    
    return true;
}

void Graphics::EndImmediate()
{
    if (immediateVertexCount_)
    {
        SetVertexBuffer(0);
        SetIndexBuffer(0);
        
        if (shaderProgram_)
        {
            const int* attributeLocations = shaderProgram_->GetAttributeLocations();
            unsigned vertexSize = VertexBuffer::GetVertexSize(immediateElementMask_);
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            for (unsigned i = ELEMENT_POSITION; i <= ELEMENT_TEXCOORD1; ++i)
            {
                unsigned attributeIndex = attributeLocations[i];
                unsigned attributeBit = 1 << attributeIndex;
                unsigned elementBit = 1 << i;
                
                if (immediateElementMask_ & elementBit)
                {
                    if ((impl_->enabledAttributes_ & attributeBit) == 0)
                    {
                        glEnableVertexAttribArray(attributeIndex);
                        impl_->enabledAttributes_ |= attributeBit;
                    }
                    
                    glVertexAttribPointer(attributeIndex, VertexBuffer::elementComponents[i], VertexBuffer::elementType[i],
                        VertexBuffer::elementNormalize[i], vertexSize, (const GLvoid*)&immediateVertexData_[immediateElementOffsets_[i]]);
                }
                else if (impl_->enabledAttributes_ & attributeBit)
                {
                    glDisableVertexAttribArray(attributeIndex);
                    impl_->enabledAttributes_ &= ~attributeBit;
                }
            }
            
            Draw(immediateType_, 0, immediateVertexCount_);
        }
        
        immediateVertexCount_ = 0;
    }
}

void Graphics::SetForceSM2(bool enable)
{
}

unsigned char* Graphics::GetImmediateDataPtr() const
{
    if (!immediateVertexCount_)
    {
        LOGERROR("Immediate draw operation not started");
        return 0;
    }
    
    return const_cast<unsigned char*>(&immediateVertexData_[0]);
}

PODVector<IntVector2> Graphics::GetResolutions() const
{
    PODVector<IntVector2> ret;
    
    return ret;
}

PODVector<int> Graphics::GetMultiSampleLevels() const
{
    PODVector<int> ret;
    // No multisampling always supported
    ret.Push(0);
    
    return ret;
}

VertexBuffer* Graphics::GetVertexBuffer(unsigned index) const
{
    return index < MAX_VERTEX_STREAMS ? vertexBuffers_[index] : 0;
}

ShaderParameter Graphics::GetShaderParameter(const String& name)
{
    Map<String, ShaderParameter>::Iterator i = shaderParameters_.Find(name);
    if (i != shaderParameters_.End())
        return i->second_;
    else
        return MAX_SHADER_PARAMETERS;
}

TextureUnit Graphics::GetTextureUnit(const String& name)
{
    Map<String, TextureUnit>::Iterator i = textureUnits_.Find(name);
    if (i != textureUnits_.End())
        return i->second_;
    else
        return MAX_TEXTURE_UNITS;
}

const String& Graphics::GetShaderParameterName(ShaderParameter parameter)
{
    for (Map<String, ShaderParameter>::Iterator i = shaderParameters_.Begin(); i != shaderParameters_.End(); ++i)
    {
        if (i->second_ == parameter)
            return i->first_;
    }
    return noParameter;
}

const String& Graphics::GetTextureUnitName(TextureUnit unit)
{
    for (Map<String, TextureUnit>::Iterator i = textureUnits_.Begin(); i != textureUnits_.End(); ++i)
    {
        if (i->second_ == unit)
            return i->first_;
    }
    return noParameter;
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
    else if (depthStencil_)
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

void Graphics::AddGPUObject(GPUObject* object)
{
    gpuObjects_.Push(object);
}

void Graphics::RemoveGPUObject(GPUObject* object)
{
    for (Vector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
    {
        if ((*i) == object)
        {
            gpuObjects_.Erase(i);
            return;
        }
    }
}

unsigned Graphics::GetAlphaFormat()
{
    return GL_ALPHA;
}

unsigned Graphics::GetLuminanceFormat()
{
    return GL_LUMINANCE;
}

unsigned Graphics::GetLuminanceAlphaFormat()
{
    return GL_LUMINANCE_ALPHA;
}

unsigned Graphics::GetRGBFormat()
{
    return GL_RGB;
}

unsigned Graphics::GetRGBAFormat()
{
    return GL_RGBA;
}

unsigned Graphics::GetDepthFormat()
{
    return GL_DEPTH_COMPONENT24;
}

unsigned Graphics::GetDepthStencilFormat()
{
    return GL_DEPTH24_STENCIL8_EXT;
}

bool Graphics::IsInitialized() const
{
    return ((impl_->window_ != 0) && (impl_->renderContext_ != 0));
}

unsigned Graphics::GetWindowHandle() const
{
    return (unsigned)impl_->window_;
}

bool Graphics::GetRenderTextureSupport() const
{
    return impl_->fbo_ != 0;
}

bool Graphics::OpenWindow(int width, int height)
{
    WNDCLASS wc;
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc   = wndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = impl_->instance_;
    wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = 0;
    wc.lpszMenuName  = 0;
    wc.lpszClassName = "OpenGL";
    
    RegisterClass(&wc);
    
    RECT rect = {0, 0, width, height};
    AdjustWindowRect(&rect, windowStyle, false);
    impl_->window_ = CreateWindow("OpenGL", windowTitle_.CString(), windowStyle, CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right, rect.bottom, 0, 0, impl_->instance_, 0); 
    
    if (!impl_->window_)
    {
        LOGERROR("Could not create window");
        return false;
    }
    
    SetWindowLongPtr(impl_->window_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    
    // Save window placement
    WINDOWPLACEMENT wndpl;
    wndpl.length = sizeof wndpl;
    if (SUCCEEDED(GetWindowPlacement(impl_->window_, &wndpl)))
    {
        windowPosX_ = wndpl.rcNormalPosition.left;
        windowPosY_ = wndpl.rcNormalPosition.top;
    }
    
    // Save the device context, then set the pixel format
    impl_->deviceContext_ = GetDC(impl_->window_);
    
    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(pfd));
    
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    
    int iFormat = ChoosePixelFormat(impl_->deviceContext_, &pfd);
    if (!iFormat)
    {
        LOGERROR("Failed to choose pixel format");
        return false;
    }
    if (SetPixelFormat(impl_->deviceContext_, iFormat, &pfd) == FALSE)
    {
        LOGERROR("Failed to set pixel format");
        return false;
    }
    
    LOGINFO("Created application window");
    return true;
}

bool Graphics::SetScreenMode(int newWidth, int newHeight)
{
    inModeChange_ = true;
    
    DEVMODE dmScreenSettings;
    ZeroMemory(&dmScreenSettings, sizeof(dmScreenSettings));
    dmScreenSettings.dmSize = sizeof(dmScreenSettings);
    dmScreenSettings.dmPelsWidth = newWidth;
    dmScreenSettings.dmPelsHeight = newHeight;
    dmScreenSettings.dmBitsPerPel = 32;
    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
    
    bool success = ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL;
    if (success)
        fullscreenModeSet_ = true;

    inModeChange_ = false;
    return success;
}

void Graphics::RestoreScreenMode()
{
    if (fullscreenModeSet_)
    {
        inModeChange_ = true;
        ChangeDisplaySettings(NULL, 0);
        fullscreenModeSet_ = false;
        inModeChange_ = false;
    }
}

void Graphics::AdjustWindow(int newWidth, int newHeight, bool newFullscreen)
{
    inModeChange_ = true;
    
    if (newFullscreen)
    {
        SetWindowLongPtr(impl_->window_, GWL_STYLE, WS_POPUP);
        SetWindowPos(impl_->window_, HWND_TOP, 0, 0, newWidth, newHeight, SWP_NOZORDER | SWP_SHOWWINDOW);
    }
    else
    {
        RECT rect = {0, 0, newWidth, newHeight};
        AdjustWindowRect(&rect, windowStyle, false);
        SetWindowLongPtr(impl_->window_, GWL_STYLE, windowStyle);
        SetWindowPos(impl_->window_, HWND_TOP, windowPosX_, windowPosY_, rect.right - rect.left, rect.bottom - rect.top,
            SWP_NOZORDER | SWP_SHOWWINDOW);
        
        // Clean up the desktop of the old window contents
        InvalidateRect(0, 0, true);
    }
    
    inModeChange_ = false;
}

void Graphics::CreateRenderTargets()
{
    if (mode_ != RENDER_FORWARD)
    {
        if (!diffBuffer_)
        {
            diffBuffer_ = new Texture2D(context_);
            diffBuffer_->SetSize(0, 0, GetRGBAFormat(), TEXTURE_RENDERTARGET);
        }
        
        if (!normalBuffer_)
        {
            normalBuffer_ = new Texture2D(context_);
            normalBuffer_->SetSize(0, 0, GetRGBAFormat(), TEXTURE_RENDERTARGET);
        }
        
        if (!depthBuffer_)
        {
            depthBuffer_ = new Texture2D(context_);
            depthBuffer_->SetSize(0, 0, GetDepthFormat(), TEXTURE_DEPTHSTENCIL);
        }
        
        // If deferred mode temporal AA is used, reserve screen buffers
        // (later we will probably want the screen buffer reserved in any case, to do for example distortion effects,
        // which will also be useful in forward rendering)
        if (multiSample_)
        {
            for (unsigned i = 0; i < NUM_SCREEN_BUFFERS; ++i)
            {
                screenBuffers_[i] = new Texture2D(context_);
                screenBuffers_[i]->SetSize(0, 0, GetRGBAFormat(), TEXTURE_RENDERTARGET);
            }
        }
        else
        {
            for (unsigned i = 0; i < NUM_SCREEN_BUFFERS; ++i)
                screenBuffers_[i].Reset();
        }
    }
    else
    {
        diffBuffer_.Reset();
        normalBuffer_.Reset();
        depthBuffer_.Reset();
        for (unsigned i = 0; i < NUM_SCREEN_BUFFERS; ++i)
            screenBuffers_[i].Reset();
    }
}

void Graphics::ResetCachedState()
{
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        vertexBuffers_[i] = 0;
        elementMasks_[i] = 0;
    }
    
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
    {
        textures_[i] = 0;
        textureTypes_[i] = 0;
    }
    
    for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        renderTargets_[i] = 0;
    
    depthStencil_ = 0;
    viewport_ = IntRect(0, 0, 0, 0);
    viewTexture_ = 0;
    indexBuffer_ = 0;
    vertexShader_ = 0;
    pixelShader_ = 0;
    shaderProgram_ = 0;
    blendMode_ = BLEND_REPLACE;
    alphaTest_ = false;
    alphaTestMode_ = CMP_ALWAYS;
    alphaRef_ = 0.0f;
    textureAnisotropy_ = 1;
    colorWrite_ = true;
    cullMode_ = CULL_NONE;
    constantDepthBias_ = 0.0f;
    slopeScaledDepthBias_ = 0.0f;
    depthTestMode_ = CMP_ALWAYS;
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
    stencilMask_ = M_MAX_UNSIGNED;
}

void Graphics::SetDrawBuffers()
{
    // Calculate the bit combination of non-zero color rendertargets to first check if the combination changed
    unsigned newDrawBuffers = 0;
    for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
    {
        if (renderTargets_[i])
            newDrawBuffers |= 1 << i;
    }
    
    if (newDrawBuffers == impl_->drawBuffers_)
        return;
    
    // Check for no color rendertargets (depth rendering only)
    if (!newDrawBuffers)
        glDrawBuffer(GL_NONE);
    else
    {
        int drawBufferIds[4];
        unsigned drawBufferCount = 0;
        
        for (unsigned i = 0; i < MAX_RENDERTARGETS; ++i)
        {
            if (renderTargets_[i])
                drawBufferIds[drawBufferCount++] = GL_COLOR_ATTACHMENT0_EXT + i;
        }
        glDrawBuffers(drawBufferCount, (const GLenum*)drawBufferIds);
    }
    
    glReadBuffer(GL_NONE);
}

void Graphics::InitializeShaderParameters()
{
    // Map parameter names
    shaderParameters_["CameraPos"] = VSP_CAMERAPOS;
    shaderParameters_["CameraRot"] = VSP_CAMERAROT;
    shaderParameters_["DepthMode"] = VSP_DEPTHMODE;
    shaderParameters_["ElapsedTime"] = VSP_ELAPSEDTIME;
    shaderParameters_["FrustumSize"] = VSP_FRUSTUMSIZE;
    shaderParameters_["GBufferOffsets"] = VSP_GBUFFEROFFSETS;
    shaderParameters_["Model"] = VSP_MODEL;
    shaderParameters_["ShadowProj"] = VSP_SHADOWPROJ;
    shaderParameters_["SpotProj"] = VSP_SPOTPROJ;
    shaderParameters_["ViewProj"] = VSP_VIEWPROJ;
    shaderParameters_["UOffset"] = VSP_UOFFSET;
    shaderParameters_["VOffset"] = VSP_VOFFSET;
    shaderParameters_["ViewRightVector"] = VSP_VIEWRIGHTVECTOR;
    shaderParameters_["ViewUpVector"] = VSP_VIEWUPVECTOR;
    shaderParameters_["SkinMatrices"] = VSP_SKINMATRICES;
    
    shaderParameters_["AmbientColor"] = PSP_AMBIENTCOLOR;
    shaderParameters_["AntiAliasWeights"] = PSP_ANTIALIASWEIGHTS;
    shaderParameters_["CameraPosPS"] = PSP_CAMERAPOS;
    shaderParameters_["DepthReconstruct"] = PSP_DEPTHRECONSTRUCT;
    shaderParameters_["ElapsedTimePS"] = PSP_ELAPSEDTIME;
    shaderParameters_["FogColor"] = PSP_FOGCOLOR;
    shaderParameters_["FogParams"] = PSP_FOGPARAMS;
    shaderParameters_["GBufferOffsetsPS"] = PSP_GBUFFEROFFSETS;
    shaderParameters_["GBufferViewport"] = PSP_GBUFFERVIEWPORT;
    shaderParameters_["LightAtten"] = PSP_LIGHTATTEN;
    shaderParameters_["LightColor"] = PSP_LIGHTCOLOR;
    shaderParameters_["LightDir"] = PSP_LIGHTDIR;
    shaderParameters_["LightPos"] = PSP_LIGHTPOS;
    shaderParameters_["LightSplits"] = PSP_LIGHTSPLITS;
    shaderParameters_["LightVecRot"] = PSP_LIGHTVECROT;
    shaderParameters_["MatDiffColor"] = PSP_MATDIFFCOLOR;
    shaderParameters_["MatEmissiveColor"] = PSP_MATEMISSIVECOLOR;
    shaderParameters_["MatSpecProperties"] = PSP_MATSPECPROPERTIES;
    shaderParameters_["SampleOffsets"] = PSP_SAMPLEOFFSETS;
    shaderParameters_["ShadowIntensity"] = PSP_SHADOWINTENSITY;
    shaderParameters_["ShadowProjPS"] = PSP_SHADOWPROJ;
    shaderParameters_["SpotProjPS"] = PSP_SPOTPROJ;
    shaderParameters_["ViewProjPS"] = PSP_VIEWPROJ;
    
    // Map texture units
    textureUnits_["NormalMap"] = TU_NORMAL;
    textureUnits_["DiffMap"] = TU_DIFFUSE;
    textureUnits_["DiffCubeMap"] = TU_DIFFUSE;
    textureUnits_["SpecMap"] = TU_SPECULAR;
    textureUnits_["EmissiveMap"] = TU_EMISSIVE;
    textureUnits_["DetailMap"] = TU_DETAIL;
    textureUnits_["EnvironmentMap"] = TU_ENVIRONMENT;
    textureUnits_["EnvironmentCubeMap"] = TU_ENVIRONMENT;
    textureUnits_["LightRampMap"] = TU_LIGHTRAMP;
    textureUnits_["LightSpotMap"] = TU_LIGHTSPOT;
    textureUnits_["LightCubeMap"]  = TU_LIGHTSPOT;
    textureUnits_["ShadowMap"] = TU_SHADOWMAP;
    textureUnits_["DiffBuffer"] = TU_DIFFBUFFER;
    textureUnits_["NormalBuffer"] = TU_NORMALBUFFER;
    textureUnits_["DepthBuffer"] = TU_DEPTHBUFFER;
}

void Graphics::HandleWindowMessage(StringHash eventType, VariantMap& eventData)
{
    using namespace WindowMessage;
    
    if (eventData[P_WINDOW].GetInt() != (int)impl_->window_)
        return;
    
    switch (eventData[P_MSG].GetInt())
    {
    case WM_CLOSE:
        Close();
        eventData[P_HANDLED] = true;
        break;
        
    case WM_DESTROY:
        eventData[P_HANDLED] = true;
        break;
    }
}

void Graphics::HandleActivation(StringHash eventType, VariantMap& eventData)
{
    if ((inModeChange_) || (!impl_->window_) || (!fullscreen_))
        return;
    
    using namespace Activation;
    
    if (eventData[P_ACTIVE].GetBool())
    {
        // If we were activated and are not minimized, change back to the custom mode
        if ((!eventData[P_MINIMIZED].GetBool()) && (!fullscreenModeSet_))
        {
            if (!SetScreenMode(width_, height_))
                fullscreen_ = false;
            AdjustWindow(width_, height_, fullscreen_);
        }
    }
    else
    {
        // Reset to desktop resolution on inactivation
        inModeChange_ = true;
        ShowWindow(impl_->window_, SW_MINIMIZE);
        inModeChange_ = false;
        RestoreScreenMode();
    }
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    using namespace WindowMessage;
    
    Graphics* graphics = reinterpret_cast<Graphics*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    
    if ((graphics) && (graphics->IsInitialized()))
    {
        VariantMap eventData;
        eventData[P_WINDOW] = (int)hwnd;
        eventData[P_MSG] = (int)msg;
        eventData[P_WPARAM] = (int)wParam;
        eventData[P_LPARAM] = (int)lParam;
        eventData[P_HANDLED] = false;
        
        graphics->SendEvent(E_WINDOWMESSAGE, eventData);
        if (eventData[P_HANDLED].GetBool())
            return 0;
    }
    
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void RegisterGraphicsLibrary(Context* context)
{
    Animation::RegisterObject(context);
    Material::RegisterObject(context);
    Model::RegisterObject(context);
    Shader::RegisterObject(context);
    Technique::RegisterObject(context);
    Texture2D::RegisterObject(context);
    TextureCube::RegisterObject(context);
    Camera::RegisterObject(context);
    Drawable::RegisterObject(context);
    Light::RegisterObject(context);
    StaticModel::RegisterObject(context);
    Skybox::RegisterObject(context);
    AnimatedModel::RegisterObject(context);
    AnimationController::RegisterObject(context);
    BillboardSet::RegisterObject(context);
    ParticleEmitter::RegisterObject(context);
    DebugRenderer::RegisterObject(context);
    Octree::RegisterObject(context);
    Zone::RegisterObject(context);
}
