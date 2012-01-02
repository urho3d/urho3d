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
#include "StringUtils.h"
#include "Technique.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "VertexBuffer.h"
#include "Zone.h"

#include <stdio.h>

#include "DebugNew.h"

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
    GL_INCR_WRAP,
    GL_DECR_WRAP
};

static unsigned numInstances = 0;

static const String noParameter;

int CloseCallback(GLFWwindow window)
{
    // Do not let GLFW close the window, rather do it ourselves in a controlled fashion
    Context* context = GetWindowContext(window);
    if (context)
    {
        Graphics* graphics = context->GetSubsystem<Graphics>();
        if (graphics)
            graphics->Close();
    }

    return GL_FALSE;
}

OBJECTTYPESTATIC(Graphics);

Graphics::Graphics(Context* context_) :
    Object(context_),
    impl_(new GraphicsImpl()),
    width_(0),
    height_(0),
    multiSample_(1),
    fullscreen_(false),
    vsync_(false),
    tripleBuffer_(false),
    flushGPU_(true),
    lightPrepassSupport_(false),
    deferredSupport_(false),
    hardwareDepthSupport_(false),
    numPrimitives_(0),
    numBatches_(0),
    defaultTextureFilterMode_(FILTER_BILINEAR),
    shadowMapFormat_(GL_DEPTH_COMPONENT16),
    hiresShadowMapFormat_(GL_DEPTH_COMPONENT24),
    shaderParameterFrame_(0)
{
    ResetCachedState();
    SetTextureUnitMappings();
    
    {
        MutexLock lock(GetStaticMutex());
        if (!numInstances)
            glfwInit();
        
        ++numInstances;
    }
}

Graphics::~Graphics()
{
    Close();
    
    delete impl_;
    impl_ = 0;
    
    {
        MutexLock lock(GetStaticMutex());
        
        --numInstances;
        if (!numInstances)
            glfwTerminate();
    }
}

void Graphics::SetWindowTitle(const String& windowTitle)
{
    windowTitle_ = windowTitle;
    if (impl_->window_)
        glfwSetWindowTitle(impl_->window_, windowTitle_.CString());
}

bool Graphics::SetMode(int width, int height, bool fullscreen, bool vsync, bool tripleBuffer, int multiSample)
{
    PROFILE(SetScreenMode);
    
    multiSample = Clamp(multiSample, 1, 16);
    
    if (IsInitialized() && width == width_ && height == height_ && fullscreen == fullscreen_ &&
        vsync == vsync_ && tripleBuffer == tripleBuffer_ && multiSample == multiSample_)
        return true;
    
    // If only vsync changes, do not destroy/recreate the context
    if (IsInitialized() && width == width_ && height == height_ && fullscreen == fullscreen_ &&
        tripleBuffer == tripleBuffer_ && multiSample == multiSample_ && vsync != vsync_)
    {
        glfwSwapInterval(vsync ? 1 : 0);
        vsync_ = vsync;
        return true;
    }
    
    // If zero dimensions in windowed mode, set default. If zero in fullscreen, use desktop mode
    if (!width || !height)
    {
        if (!fullscreen)
        {
            width = 800;
            height = 600;
        }
        else
        {
            GLFWvidmode mode;
            glfwGetDesktopMode(&mode);
            width = mode.width;
            height = mode.height;
        }
    }
    
    // Close the existing window
    Release();
    
    {
        // GLFW window parameters and the window list are static, so need to operate under static lock
        MutexLock lock(GetStaticMutex());
        
        glfwOpenWindowHint(GLFW_RED_BITS, 8);
        glfwOpenWindowHint(GLFW_GREEN_BITS, 8);
        glfwOpenWindowHint(GLFW_BLUE_BITS, 8);
        glfwOpenWindowHint(GLFW_ALPHA_BITS, 0);
        glfwOpenWindowHint(GLFW_DEPTH_BITS, 24);
        glfwOpenWindowHint(GLFW_STENCIL_BITS, 8);
        glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
        if (multiSample > 1)
            glfwOpenWindowHint(GLFW_FSAA_SAMPLES, multiSample);
        else
            glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 0);
        
        impl_->window_ = glfwOpenWindow(width, height, fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOWED, windowTitle_.CString(), 0);
        if (!impl_->window_)
        {
            LOGERROR("Could not open window");
            return false;
        }
        
        // If OpenGL extensions not yet initialized, initialize now
        if (!GLeeInitialized())
            GLeeInit();
        
        if (!_GLEE_VERSION_2_0)
        {
            LOGERROR("OpenGL 2.0 is required");
            glfwCloseWindow(impl_->window_);
            return false;
        }
        
        if (!_GLEE_EXT_framebuffer_object || !_GLEE_EXT_packed_depth_stencil || !_GLEE_EXT_texture_compression_s3tc ||
            !_GLEE_EXT_texture_filter_anisotropic)
        {
            LOGERROR("EXT_framebuffer_object, EXT_packed_depth_stencil, EXT_texture_compression_s3tc and "
                "EXT_texture_filter_anisotropic OpenGL extensions are required");
            glfwCloseWindow(impl_->window_);
            return false;
        }
        
        // Set window close callback
        glfwSetWindowCloseCallback(CloseCallback);
        
        // Associate GLFW window with the execution context
        SetWindowContext(impl_->window_, context_);
    }
    
    // Set vsync
    glfwSwapInterval(vsync ? 1 : 0);
    
    // Query for system backbuffer depth
    glGetIntegerv(GL_DEPTH_BITS, &impl_->windowDepthBits_);
    impl_->depthBits_ = impl_->windowDepthBits_;
    
    // Create the FBO
    glGenFramebuffersEXT(1, &impl_->fbo_);
    
    // Set initial state to match Direct3D
    glEnable(GL_DEPTH_TEST);
    SetCullMode(CULL_CCW);
    SetDepthTest(CMP_LESSEQUAL);
    
    glfwGetWindowSize(impl_->window_, &width_, &height_);
    fullscreen_ = fullscreen;
    vsync_ = vsync;
    tripleBuffer_ = tripleBuffer;
    multiSample_ = multiSample;
    
    // Reset rendertargets and viewport for the new screen mode
    ResetRenderTargets();
    
    // Clear the window to black now, because GPU object restore may take time
    Clear(CLEAR_COLOR);
    glfwSwapBuffers();
    
    // Let GPU objects restore themselves
    for (Vector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
        (*i)->OnDeviceReset();
    
    CheckFeatureSupport();
    
    if (multiSample > 1)
        LOGINFO("Set screen mode " + String(width_) + "x" + String(height_) + " " + (fullscreen_ ? "fullscreen" : "windowed") +
        " multisample " + String(multiSample));
    else
        LOGINFO("Set screen mode " + String(width_) + "x" + String(height_) + " " + (fullscreen_ ? "fullscreen" : "windowed"));
    
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
    return SetMode(width, height, fullscreen_, vsync_, tripleBuffer_, multiSample_);
}

bool Graphics::ToggleFullscreen()
{
    return SetMode(width_, height_, !fullscreen_, vsync_, tripleBuffer_, multiSample_);
}

void Graphics::Close()
{
    if (!IsInitialized())
        return;
    
    // Release all GPU objects that still exist
    for (Vector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
        (*i)->Release();
    gpuObjects_.Clear();

    // Actually close the window
    Release();
}

bool Graphics::TakeScreenShot(Image& destImage)
{
    PROFILE(TakeScreenShot);
    
    ResetRenderTargets();
    
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

    // If we should be fullscreen, but are not currently active, do not render
    if (fullscreen_ && (!glfwGetWindowParam(impl_->window_, GLFW_ACTIVE) || glfwGetWindowParam(impl_->window_, GLFW_ICONIFIED)))
        return false;
    
    // Set default rendertarget and depth buffer
    ResetRenderTargets();
    
    // Cleanup textures from previous frame
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        SetTexture(i, 0);
    
    // Enable color and depth write
    SetColorWrite(true);
    SetDepthWrite(true);
    
    numPrimitives_ = 0;
    numBatches_ = 0;
    
    SendEvent(E_BEGINRENDERING);
    
    return true;
}

void Graphics::EndFrame()
{
    PROFILE(EndRendering);
    
    if (!IsInitialized())
        return;
    
    SendEvent(E_ENDRENDERING);
    
    glfwSwapBuffers();
}

void Graphics::Clear(unsigned flags, const Color& color, float depth, unsigned stencil)
{
    bool oldColorWrite = colorWrite_;
    bool oldDepthWrite = depthWrite_;

    if (flags & CLEAR_COLOR && !oldColorWrite)
        SetColorWrite(true);
    if (flags & CLEAR_DEPTH && !oldDepthWrite)
        SetDepthWrite(true);
    if (flags & CLEAR_STENCIL && stencilWriteMask_ != M_MAX_UNSIGNED)
        glStencilMask(M_MAX_UNSIGNED);
    
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
    
    // If viewport is less than full screen, set a scissor to limit the clear
    /// \todo Any user-set scissor test will be lost
    IntVector2 viewSize = GetRenderTargetDimensions();
    if (viewport_.left_ != 0 || viewport_.top_ != 0 || viewport_.right_ != viewSize.x_ || viewport_.bottom_ != viewSize.y_)
        SetScissorTest(true, IntRect(0, 0, viewport_.right_ - viewport_.left_, viewport_.bottom_ - viewport_.top_));
    else
        SetScissorTest(false);
    
    glClear(glFlags);
    
    SetScissorTest(false);
    SetColorWrite(oldColorWrite);
    SetDepthWrite(oldDepthWrite);
    if (flags & CLEAR_STENCIL && stencilWriteMask_ != M_MAX_UNSIGNED)
        glStencilMask(stencilWriteMask_);
}

bool Graphics::ResolveToTexture(Texture2D* destination, const IntRect& viewport)
{
    if (!destination || !destination->GetRenderSurface() || destination->GetWidth() != width_ ||
        destination->GetHeight() != height_)
        return false;
    
    IntRect vpCopy = viewport;
    if (vpCopy.right_ <= vpCopy.left_)
        vpCopy.right_ = vpCopy.left_ + 1;
    if (vpCopy.bottom_ <= vpCopy.top_)
        vpCopy.bottom_ = vpCopy.top_ + 1;
    vpCopy.left_ = Clamp(vpCopy.left_, 0, width_);
    vpCopy.top_ = Clamp(vpCopy.top_, 0, height_);
    vpCopy.right_ = Clamp(vpCopy.right_, 0, width_);
    vpCopy.bottom_ = Clamp(vpCopy.bottom_, 0, height_);
    
    // Make sure the FBO is not in use
    ResetRenderTargets();
    
    // Use Direct3D convention with the vertical coordinates ie. 0 is top
    SetTextureForUpdate(destination);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, vpCopy.left_, height_ - vpCopy.bottom_, vpCopy.left_, height_ - vpCopy.bottom_,
        vpCopy.right_ - vpCopy.left_, vpCopy.bottom_ - vpCopy.top_);
    SetTexture(0, 0);
    
    return true;
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
    if (!indexCount || !indexBuffer_)
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
            if (elementMask == MASK_DEFAULT && buffer)
                elementMask = buffers[i]->GetElementMask();
        }
        
        // If buffer and element mask have stayed the same, skip to the next buffer
        if (buffer == vertexBuffers_[i] && elementMask == elementMasks_[i])
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
            if (elementMask == MASK_DEFAULT && buffer)
                elementMask = buffers[i]->GetElementMask();
        }
        
        // If buffer and element mask have stayed the same, skip to the next buffer
        if (buffer == vertexBuffers_[i] && elementMask == elementMasks_[i])
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
    if (vs == vertexShader_ && ps == pixelShader_)
        return;
    
    // Compile the shaders now if not yet compiled. If already attempted, do not retry
    if (vs && !vs->IsCompiled())
    {
        if (vs->GetCompilerOutput().Empty())
        {
            PROFILE(CompileVertexShader);

            bool success = vs->Create();
            if (success)
                LOGDEBUG("Compiled vertex shader " + vs->GetName());
            else
            {
                LOGERROR("Failed to compile vertex shader " + vs->GetName() + ":\n" + vs->GetCompilerOutput());
                vs = 0;
            }
        }
        else
            vs = 0;
    }
    
    if (ps && !ps->IsCompiled())
    {
        if (ps->GetCompilerOutput().Empty())
        {
            PROFILE(CompilePixelShader);

            bool success = ps->Create();
            if (success)
                LOGDEBUG("Compiled pixel shader " + ps->GetName());
            else
            {
                LOGERROR("Failed to compile pixel shader " + ps->GetName() + ":\n" + ps->GetCompilerOutput());
                ps = 0;
            }
        }
        else
            ps = 0;
    }
    
    for (unsigned i = 0; i < MAX_VERTEX_STREAMS; ++i)
    {
        vertexBuffers_[i] = 0;
        elementMasks_[i] = 0;
    }
    
    if (!vs || !ps)
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
            if (newProgram->Link())
            {
                LOGDEBUG("Linked vertex shader " + vs->GetName() + " and pixel shader " + ps->GetName());
                // Note: Link() calls glUseProgram() to set the texture sampler uniforms,
                // so it is not necessary to call it again
                shaderProgram_ = newProgram;
            }
            else
            {
                LOGERROR("Failed to link vertex shader " + vs->GetName() + " and pixel shader " + ps->GetName() + ":\n" +
                    newProgram->GetLinkerOutput());
                glUseProgram(0);
                shaderProgram_ = 0;
            }
            
            shaderPrograms_[combination] = newProgram;
        }
    }
}

void Graphics::SetShaderParameter(StringHash param, const float* data, unsigned count)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
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

void Graphics::SetShaderParameter(StringHash param, float value)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
        if (info)
            glUniform1fv(info->location_, 1, &value);
    }
}

void Graphics::SetShaderParameter(StringHash param, const Color& color)
{
    SetShaderParameter(param, color.Data(), 4);
}

void Graphics::SetShaderParameter(StringHash param, const Matrix3& matrix)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
        if (info)
            glUniformMatrix3fv(info->location_, 1, GL_TRUE, matrix.Data());
    }
}

void Graphics::SetShaderParameter(StringHash param, const Vector3& vector)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
        if (info)
        {
            // Check the uniform type to avoid mismatch
            switch (info->type_)
            {
            case GL_FLOAT:
                glUniform1fv(info->location_, 1, vector.Data());
                break;
                
            case GL_FLOAT_VEC2:
                glUniform2fv(info->location_, 1, vector.Data());
                break;
                
            case GL_FLOAT_VEC3:
                glUniform3fv(info->location_, 1, vector.Data());
                break;
            }
        }
    }
}

void Graphics::SetShaderParameter(StringHash param, const Matrix4& matrix)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
        if (info)
            glUniformMatrix4fv(info->location_, 1, GL_TRUE, matrix.Data());
    }
}

void Graphics::SetShaderParameter(StringHash param, const Vector4& vector)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
        if (info)
        {
            // Check the uniform type to avoid mismatch
            switch (info->type_)
            {
            case GL_FLOAT:
                glUniform1fv(info->location_, 1, vector.Data());
                break;
                
            case GL_FLOAT_VEC2:
                glUniform2fv(info->location_, 1, vector.Data());
                break;
                
            case GL_FLOAT_VEC3:
                glUniform3fv(info->location_, 1, vector.Data());
                break;
                
            case GL_FLOAT_VEC4:
                glUniform4fv(info->location_, 1, vector.Data());
                break;
            }
        }
    }
}

void Graphics::SetShaderParameter(StringHash param, const Matrix3x4& matrix)
{
    if (shaderProgram_)
    {
        const ShaderParameter* info = shaderProgram_->GetParameter(param);
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

bool Graphics::NeedParameterUpdate(StringHash param, const void* source)
{
    if (shaderProgram_)
        return shaderProgram_->NeedParameterUpdate(param, source, shaderParameterFrame_);
    
    return false;
}

bool Graphics::NeedTextureUnit(TextureUnit unit)
{
    if (shaderProgram_ && shaderProgram_->HasTextureUnit(unit))
        return true;
    
    return false;
}

void Graphics::ClearParameterSource(StringHash param)
{
    if (shaderProgram_)
        shaderProgram_->ClearParameterSource(param);
}

void Graphics::ClearParameterSources()
{
    ++shaderParameterFrame_;
}

void Graphics::ClearTransformSources()
{
    if (shaderProgram_)
    {
        shaderProgram_->ClearParameterSource(VSP_MODEL);
        shaderProgram_->ClearParameterSource(VSP_VIEWPROJ);
    }
}

void Graphics::CleanupShaderPrograms()
{
    for (ShaderProgramMap::Iterator i = shaderPrograms_.Begin(); i != shaderPrograms_.End();)
    {
        ShaderProgramMap::Iterator current = i++;
        ShaderVariation* vs = current->second_->GetVertexShader();
        ShaderVariation* ps = current->second_->GetPixelShader();
        
        if (!vs || !ps || !vs->GetGPUObject() || !ps->GetGPUObject())
            shaderPrograms_.Erase(current);
    }
}

void Graphics::SetTexture(unsigned index, Texture* texture)
{
    if (index >= MAX_TEXTURE_UNITS)
        return;
    
    // Check if texture is currently bound as a rendertarget. In that case, use its backup texture, or blank if not defined
    if (texture)
    {
        if (texture == viewTexture_ || (renderTargets_[0] && renderTargets_[0]->GetParentTexture() == texture))
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
        if (texture && texture->GetParametersDirty())
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
    SetViewport(IntRect(0, 0, width_, height_));
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
    if (index >= MAX_RENDERTARGETS)
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
        
        if (noFBO && impl_->fboBound_)
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
            impl_->fboBound_ = false;
        }
    }
}

void Graphics::SetRenderTarget(unsigned index, Texture2D* texture)
{
    RenderSurface* renderTarget = 0;
    if (texture)
        renderTarget = texture->GetRenderSurface();
    
    SetRenderTarget(index, renderTarget);
}

void Graphics::SetDepthStencil(RenderSurface* depthStencil)
{
    // If we are using a rendertarget texture, it is required in OpenGL to also have an own depth-stencil
    // Create a new depth-stencil texture as necessary to be able to provide similar behaviour as Direct3D9
    if (renderTargets_[0] && !depthStencil)
    {
        int width = renderTargets_[0]->GetWidth();
        int height = renderTargets_[0]->GetHeight();
        
        // Direct3D9 default depth-stencil can not be used when rendertarget is larger than the window.
        // Check size similarly
        if (width <= width_ && height <= height_)
        {
            int searchKey = (width << 16) | height;
            HashMap<int, SharedPtr<Texture2D> >::Iterator i = depthTextures_.Find(searchKey);
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
    
    if (depthStencil != depthStencil_)
    {
        /// \todo Should check that the texture actually is in depth format
        depthStencil_ = depthStencil;
        
        // Bind the FBO to be able to make changes to it
        if (!impl_->fboBound_)
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, impl_->fbo_);
            impl_->fboBound_ = true;
        }
        
        if (depthStencil)
        {
            // Bind either a renderbuffer or a depth texture, depending on what is available
            Texture* texture = depthStencil->GetParentTexture();
            bool hasStencil = texture->GetFormat() == GetDepthStencilFormat();
            unsigned renderBufferID = depthStencil->GetRenderBuffer();
            if (!renderBufferID)
            {
                // If texture's parameters are dirty, update before attaching
                if (texture->GetParametersDirty())
                {
                    SetTextureForUpdate(texture);
                    texture->UpdateParameters();
                    SetTexture(0, 0);
                }
                
                glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, texture->GetGPUObject(), 0);
                if (hasStencil)
                    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_TEXTURE_2D, texture->GetGPUObject(), 0);
                else
                    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_TEXTURE_2D, 0, 0);
                
                impl_->depthBits_ = texture->GetDepthBits();
            }
            else
            {
                glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, renderBufferID);
                if (hasStencil)
                    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, renderBufferID);
                else
                    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_TEXTURE_2D, 0, 0);
                impl_->depthBits_ = 24;
            }
        }
        else
        {
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, 0, 0);
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_TEXTURE_2D, 0, 0);
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
        
        if (noFBO && impl_->fboBound_)
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
            impl_->fboBound_ = false;
        }
    }
}

void Graphics::SetDepthStencil(Texture2D* texture)
{
    RenderSurface* depthStencil = 0;
    if (texture)
        depthStencil = texture->GetRenderSurface();
    
    SetDepthStencil(depthStencil);
}

void Graphics::SetViewTexture(Texture* texture)
{
    viewTexture_ = texture;
    
    if (viewTexture_)
    {
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        {
            if (textures_[i] == viewTexture_)
                SetTexture(i, textures_[i]->GetBackupTexture());
        }
    }
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
    
    // Use Direct3D convention with the vertical coordinates ie. 0 is top
    glViewport(rectCopy.left_, rtSize.y_ - rectCopy.bottom_, rectCopy.right_ - rectCopy.left_, rectCopy.bottom_ - rectCopy.top_);
    viewport_ = rectCopy;
    
    // Disable scissor test, needs to be re-enabled by the user
    SetScissorTest(false);
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
        if (mode != alphaTestMode_ || alphaRef != alphaRef_)
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
    if (constantBias != constantDepthBias_ || slopeScaledBias != slopeScaledDepthBias_)
    {
        if (constantBias != 0.0f || slopeScaledBias != 0.0f)
        {
            // Bring the constant bias from Direct3D9 scale to OpenGL (depends on depth buffer bitdepth)
            // Zero depth bits may be returned if using the packed depth-stencil format. Assume 24bit in that case
            int depthBits = Min(impl_->depthBits_, 23);
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
    if (rect.min_.x_ <= 0.0f && rect.min_.y_ <= 0.0f && rect.max_.x_ >= 1.0f && rect.max_.y_ >= 1.0f)
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
        
        if (intRect.right_ < intRect.left_ || intRect.bottom_ < intRect.top_)
            enable = false;
        
        if (enable && scissorRect_ != intRect)
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

void Graphics::SetStencilTest(bool enable, CompareMode mode, StencilOp pass, StencilOp fail, StencilOp zFail, unsigned stencilRef, unsigned compareMask, unsigned writeMask)
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
        if (mode != stencilTestMode_ || stencilRef != stencilRef_ || compareMask != stencilCompareMask_)
        {
            glStencilFunc(glCmpFunc[mode], stencilRef, compareMask);
            stencilTestMode_ = mode;
            stencilRef_ = stencilRef;
            stencilCompareMask_ = compareMask;
        }
        if (writeMask != stencilWriteMask_)
        {
            glStencilMask(writeMask);
            stencilWriteMask_ = writeMask;
        }
        if (pass != stencilPass_ || fail != stencilFail_ || zFail != stencilZFail_)
        {
            glStencilOp(glStencilOps[fail], glStencilOps[zFail], glStencilOps[pass]);
            stencilPass_ = pass;
            stencilFail_ = fail;
            stencilZFail_ = zFail;
        }
    }
}

void Graphics::SetForceSM2(bool enable)
{
}

bool Graphics::IsInitialized() const
{
    return impl_->window_ != 0;
}

void* Graphics::GetWindowHandle() const
{
    return impl_->window_;
}

PODVector<IntVector2> Graphics::GetResolutions() const
{
    static const unsigned MAX_MODES = 256;
    GLFWvidmode modes[MAX_MODES];
    
    unsigned count = glfwGetVideoModes(modes, MAX_MODES);
    PODVector<IntVector2> ret;
    
    for (unsigned i = 0; i < count; ++i)
    {
        int width = modes[i].width;
        int height  = modes[i].height;
        
        // Store mode if unique
        bool unique = true;
        for (unsigned j = 0; j < ret.Size(); ++i)
        {
            if (ret[j].x_ == width && ret[j].y_ == height)
            {
                unique = false;
                break;
            }
        }
        
        if (unique)
            ret.Push(IntVector2(width, height));
    }
    
    return ret;
}

PODVector<int> Graphics::GetMultiSampleLevels() const
{
    PODVector<int> ret;
    // No multisampling always supported
    ret.Push(1);
    /// \todo Implement properly, if possible
    
    return ret;
}

VertexBuffer* Graphics::GetVertexBuffer(unsigned index) const
{
    return index < MAX_VERTEX_STREAMS ? vertexBuffers_[index] : 0;
}

TextureUnit Graphics::GetTextureUnit(const String& name)
{
    Map<String, TextureUnit>::Iterator i = textureUnits_.Find(name);
    if (i != textureUnits_.End())
        return i->second_;
    else
        return MAX_TEXTURE_UNITS;
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
    Vector<GPUObject*>::Iterator i = gpuObjects_.Find(object);
    if (i != gpuObjects_.End())
        gpuObjects_.Erase(i);
}

void* Graphics::ReserveDiscardLockBuffer(unsigned size)
{
    // First check for a free buffer that is large enough
    for (Vector<DiscardLockBuffer>::Iterator i = discardLockBuffers_.Begin(); i != discardLockBuffers_.End(); ++i)
    {
        if (!i->reserved_ && i->size_ >= size)
        {
            i->reserved_ = true;
            return i->data_.Get();
        }
    }
    
    // Then check if a free buffer can be resized
    for (Vector<DiscardLockBuffer>::Iterator i = discardLockBuffers_.Begin(); i != discardLockBuffers_.End(); ++i)
    {
        if (!i->reserved_)
        {
            i->data_ = new unsigned char[size];
            i->size_ = size;
            i->reserved_ = true;
            return i->data_.Get();
        }
    }
    
    // Finally allocate a new buffer
    DiscardLockBuffer newBuffer;
    newBuffer.data_ = new unsigned char[size];
    newBuffer.size_ = size;
    newBuffer.reserved_ = true;
    discardLockBuffers_.Push(newBuffer);
    return newBuffer.data_.Get();
}

void Graphics::FreeDiscardLockBuffer(void* buffer)
{
    for (Vector<DiscardLockBuffer>::Iterator i = discardLockBuffers_.Begin(); i != discardLockBuffers_.End(); ++i)
    {
        if (i->reserved_ && i->data_.Get() == buffer)
        {
            i->reserved_ = false;
            return;
        }
    }
    
    LOGWARNING("Reserved discard lock buffer " + ToStringHex((unsigned)buffer) + " not found");
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

unsigned Graphics::GetFloatFormat()
{
    return GL_LUMINANCE32F_ARB;
}

unsigned Graphics::GetLinearDepthFormat()
{
    // OpenGL FBO specs state that color attachments must have the same format; therefore must encode linear depth to RGBA
    // manually if not using a readable hardware depth texture
    return GL_RGBA;
}

unsigned Graphics::GetDepthStencilFormat()
{
    return GL_DEPTH24_STENCIL8_EXT;
}

void Graphics::CheckFeatureSupport()
{
    // Check supported features: light pre-pass and deferred rendering and hardware depth texture
    lightPrepassSupport_ = false;
    deferredSupport_ = false;
    hardwareDepthSupport_ = false;

    int numSupportedRTs = 1;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &numSupportedRTs);

    // For now hardware depth texture is only tested for on NVIDIA hardware because of visual artifacts and slowdown on ATI
    String vendorString = String((const char*)glGetString(GL_VENDOR)).ToUpper();
    if (vendorString.Find("NVIDIA") != String::NPOS)
    {
        SharedPtr<Texture2D> depthTexture(new Texture2D(context_));
        
        hardwareDepthSupport_ = true;
        // Note: Texture2D::SetSize() requires hardwareDepthSupport_ == true to create a texture instead of a renderbuffer
        depthTexture->SetSize(256, 256, GetDepthStencilFormat(), TEXTURE_DEPTHSTENCIL);
        SetDepthStencil(depthTexture);
        
        // If hardware depth textures work, this means also light pre-pass is automatically supported
        if (CheckFramebuffer())
        {
            lightPrepassSupport_ = true;
            if (numSupportedRTs >= 3)
                deferredSupport_ = true;
        }
        else
            hardwareDepthSupport_ = false;
        
        ResetDepthStencil();
    }
    
    if (!hardwareDepthSupport_)
    {
        // If hardware depth is not supported, must support 2 rendertargets for light pre-pass, and 4 for deferred
        if (numSupportedRTs >= 2)
            lightPrepassSupport_ = true;
        if (numSupportedRTs >= 4)
            deferredSupport_ = true;
    }
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

bool Graphics::CheckFramebuffer()
{
    return glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) == GL_FRAMEBUFFER_COMPLETE_EXT;
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
    viewTexture_ = 0;
    viewport_ = IntRect(0, 0, 0, 0);
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
    stencilCompareMask_ = M_MAX_UNSIGNED;
    stencilWriteMask_ = M_MAX_UNSIGNED;
    
    impl_->activeTexture_ = 0;
    impl_->drawBuffers_ = M_MAX_UNSIGNED;
    impl_->enabledAttributes_ = 0;
    impl_->fboBound_ = false;
}

void Graphics::Release()
{
    if (!impl_->window_)
        return;
    
    depthTextures_.Clear();
    
    // If GPU objects exist ie. it's a context delete/recreate, not Close(), tell them to save and release themselves
    for (Vector<GPUObject*>::Iterator i = gpuObjects_.Begin(); i != gpuObjects_.End(); ++i)
        (*i)->OnDeviceLost();
    
    if (impl_->fbo_)
    {
        glDeleteFramebuffersEXT(1, &impl_->fbo_);
        impl_->fbo_ = 0;
    }
    
    // When the new context is initialized, it will have default state again
    ResetCachedState();
    ClearParameterSources();
    
    {
        MutexLock lock(GetStaticMutex());
        
        SetWindowContext(impl_->window_, 0);
        glfwCloseWindow(impl_->window_);
        impl_->window_ = 0;
    }
}

void Graphics::SetTextureUnitMappings()
{
    textureUnits_["DiffMap"] = TU_DIFFUSE;
    textureUnits_["DiffCubeMap"] = TU_DIFFUSE;
    textureUnits_["NormalMap"] = TU_NORMAL;
    textureUnits_["EmissiveMap"] = TU_EMISSIVE;
    textureUnits_["DetailMap"] = TU_DETAIL;
    textureUnits_["EnvironmentMap"] = TU_ENVIRONMENT;
    textureUnits_["EnvironmentCubeMap"] = TU_ENVIRONMENT;
    textureUnits_["LightRampMap"] = TU_LIGHTRAMP;
    textureUnits_["LightSpotMap"] = TU_LIGHTSHAPE;
    textureUnits_["LightCubeMap"]  = TU_LIGHTSHAPE;
    textureUnits_["ShadowMap"] = TU_SHADOWMAP;
    textureUnits_["FaceSelectCubeMap"] = TU_FACESELECT;
    textureUnits_["IndirectionCubeMap"] = TU_INDIRECTION;
    textureUnits_["AlbedoBuffer"] = TU_ALBEDOBUFFER;
    textureUnits_["NormalBuffer"] = TU_NORMALBUFFER;
    textureUnits_["DepthBuffer"] = TU_DEPTHBUFFER;
    textureUnits_["LightBuffer"] = TU_LIGHTBUFFER;
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
