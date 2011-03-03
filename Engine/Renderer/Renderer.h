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

#ifndef RENDERER_RENDERER_H
#define RENDERER_RENDERER_H

#include "Color.h"
#include "EventListener.h"
#include "Rect.h"
#include "RendererDefs.h"
#include "SharedPtr.h"

#include <map>
#include <string>
#include <vector>

class Image;
class IndexBuffer;
class Matrix3;
class Matrix4;
class Matrix4x3;
class PixelShader;
class GPUObject;
class RendererImpl;
class RenderSurface;
class Texture;
class Texture2D;
class TextureCube;
class Vector3;
class Vector4;
class VertexBuffer;
class VertexDeclaration;
class VertexShader;

static const int IMMEDIATE_BUFFER_DEFAULT_SIZE = 1024;

//! Manages the Direct3D9 device, application window, rendering state and GPU resources
class Renderer : public RefCounted, public EventListener
{
public:
    //! Construct with window title
    Renderer(const std::string& windowTitle);
    //! Destruct. Close the window and release the Direct3D9 device 
    virtual ~Renderer();
    
    //! Pump operating system messages
    void messagePump();
    //! Set screen mode. In deferred rendering modes multisampling means edge filtering instead of MSAA
    void setMode(RenderMode mode, int width, int height, bool fullscreen, bool vsync, int multiSample);
    //! Toggle between full screen and windowed mode
    void toggleFullscreen();
    //! Close the window
    void close();
    //! Take a screenshot
    bool takeScreenShot(Image& destImage);
    
    //! Begin frame rendering
    bool beginFrame();
    //! End frame rendering and swap buffers. Optionally flush the GPU command queue
    void endFrame(bool flushCommands = false);
    //! Clear any or all of render target, depth buffer and stencil buffer
    void clear(unsigned flags, const Color& color = Color(0.0f, 0.0f, 0.0f, 0.0f), float depth = 1.0f, unsigned stencil = 0);
    //! Draw indexed geometry
    void draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount, unsigned instanceCount = 1);
    //! Draw non-indexed geometry
    void draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount, unsigned instanceCount = 1);
    //! Set vertex buffer
    void setVertexBuffer(VertexBuffer* buffer);
    //! Set multiple vertex buffers
    bool setVertexBuffers(const std::vector<VertexBuffer*>& buffers, const std::vector<unsigned>& elementMasks);
    //! Set multiple vertex buffers
    bool setVertexBuffers(const std::vector<SharedPtr<VertexBuffer> >& buffers, const std::vector<unsigned>& elementMasks);
    //! Set index buffer
    void setIndexBuffer(IndexBuffer* buffer);
    //! Set vertex shader
    void setVertexShader(VertexShader* shader);
    //! Set vertex shader bool constants
    void setVertexShaderConstant(unsigned index, const bool* data, unsigned count);
    //! Set vertex shader float constants
    void setVertexShaderConstant(unsigned index, const float* data, unsigned count);
    //! Set vertex shader int constants
    void setVertexShaderConstant(unsigned index, const int* data, unsigned count);
    //! Set vertex shader float constant
    void setVertexShaderConstant(unsigned index, float value);
    //! Set vertex shader color constant
    void setVertexShaderConstant(unsigned index, const Color& color);
    //! Set vertex shader 3x3 matrix constant
    void setVertexShaderConstant(unsigned index, const Matrix3& matrix);
    //! Set vertex shader 3D vector constant
    void setVertexShaderConstant(unsigned index, const Vector3& vector);
    //! Set vertex shader 4x4 matrix constant
    void setVertexShaderConstant(unsigned index, const Matrix4& matrix);
    //! Set vertex shader 4D vector constant
    void setVertexShaderConstant(unsigned index, const Vector4& vector);
    //! Set vertex shader 4x3 matrix constant
    void setVertexShaderConstant(unsigned index, const Matrix4x3& matrix);
    //! Set pixel shader
    void setPixelShader(PixelShader* shader);
    //! Set pixel shader bool constants
    void setPixelShaderConstant(unsigned index, const bool* data, unsigned count);
    //! Set pixel shader float constants
    void setPixelShaderConstant(unsigned index, const float* data, unsigned count);
    //! Set pixel shader int constants
    void setPixelShaderConstant(unsigned index, const int* data, unsigned count);
    //! Set pixel shader float constant
    void setPixelShaderConstant(unsigned index, float value);
    //! Set pixel shader color constant
    void setPixelShaderConstant(unsigned index, const Color& color);
    //! Set pixel shader 3x3 matrix constant
    void setPixelShaderConstant(unsigned index, const Matrix3& matrix);
    //! Set pixel shader 3D vector constant
    void setPixelShaderConstant(unsigned index, const Vector3& vector);
     //! Set pixel shader 4x4 matrix constant
    void setPixelShaderConstant(unsigned index, const Matrix4& matrix);
    //! Set pixel shader 3D vector constant
    void setPixelShaderConstant(unsigned index, const Vector4& vector);
    //! Set pixel shader 4x3 matrix constant
    void setPixelShaderConstant(unsigned index, const Matrix4x3& matrix);
    //! Set texture
    void setTexture(unsigned index, Texture* texture);
    //! Set default texture filtering mode
    void setDefaultTextureFilterMode(TextureFilterMode mode);
    //! Reset all render targets and depth buffer (render to back buffer and back buffer depth stencil)
    void resetRenderTargets();
    //! Reset specific render target
    void resetRenderTarget(unsigned index);
    //! Reset depth stencil
    void resetDepthStencil();
    //! Set render target
    void setRenderTarget(unsigned index, RenderSurface* renderTarget);
    //! Set render target
    void setRenderTarget(unsigned index, Texture2D* renderTexture);
    //! Set depth stencil buffer
    void setDepthStencil(RenderSurface* depthStencil);
    //! Set depth stencil buffer
    void setDepthStencil(Texture2D* depthTexture);
    //! Set viewport
    void setViewport(const IntRect& rect);
    //! Set "view texture" so that deferred rendering does not attempt to sample render target during G-buffer rendering
    void setViewTexture(Texture* texture);
    //! Set alpha test
    void setAlphaTest(bool enable, CompareMode mode = CMP_ALWAYS, float alphaRef = 0.5f);
    //! Set texture anisotropy
    void setTextureAnisotropy(unsigned level);
    //! Set blending mode
    void setBlendMode(BlendMode mode);
    //! Set color write on/off
    void setColorWrite(bool enable);
    //! Set hardware culling mode
    void setCullMode(CullMode mode);
    //! Set depth bias
    void setDepthBias(float constantBias, float slopeScaledBias);
    //! Set depth compare
    void setDepthTest(CompareMode mode);
    //! Set depth write on/off
    void setDepthWrite(bool enable);
    //! Set polygon fill mode
    void setFillMode(FillMode mode);
    //! Set scissor test
    void setScissorTest(bool enable, const Rect& rect = Rect::sFullRect, bool borderInclusive = true);
    //! Set scissor test
    void setScissorTest(bool enable, const IntRect& rect);
    //! Set stencil test
    void setStencilTest(bool enable, CompareMode mode = CMP_ALWAYS, StencilOp pass = OP_KEEP, StencilOp fail = OP_KEEP, StencilOp zFail = OP_KEEP, unsigned stencilRef = 0, unsigned stencilMask = 0xffffffff);
    //! Set vertex buffer stream frequency
    bool setStreamFrequency(unsigned index, unsigned frequency);
    //! Reset stream frequencies
    void resetStreamFrequencies();
    //! Begin immediate rendering command
    bool beginImmediate(PrimitiveType type, unsigned vertexCount, unsigned elementMask);
    //! Define immediate vertex
    bool defineVertex(const Vector3& vertex);
    //! Define immediate normal
    bool defineNormal(const Vector3& normal);
    //! Define immediate texture coordinate
    bool defineTexCoord(const Vector2& texCoord);
    //! Define immediate color
    bool defineColor(const Color& color);
    //! Define immediate color
    bool defineColor(unsigned color);
    //! End immediate rendering command and render
    void endImmediate();
    //! Set force Shader Model 2 flag. Needs to be set before setting initial screen mode to have effect.
    void setForceSM2(bool enable);
    
    //! Return renderer implementation, which holds the actual Direct3D resources
    RendererImpl* getImpl() const { return mImpl; }
    //! Return window title
    const std::string& getWindowTitle() const { return mTitle; }
    //! Return rendering mode
    RenderMode getRenderMode() const { return mMode; }
    //! Return window width
    int getWidth() const { return mWidth; }
    //! Return window height
    int getHeight() const { return mHeight; }
    //! Return multisample mode (0 = no multisampling)
    int getMultiSample() const { return mMultiSample; }
    //! Return whether window is fullscreen
    bool getFullscreen() const { return mFullscreen; }
    //! Return whether vertical sync is on
    bool getVsync() const { return mVsync; }
    //! Return whether window has been closed
    bool isClosed() const { return mClosed; }
    //! Return whether Direct3D device is lost, and can not yet render. This happens during fullscreen resolution switching
    bool isDeviceLost() const { return mDeviceLost; }
    //! Return immediate rendering data pointer
    unsigned char* getImmediateDataPtr() const;
    //! Return window handle
    unsigned getWindowHandle() const;
    //! Return number of primitives drawn this frame
    unsigned getNumPrimitives() const { return mNumPrimitives; }
    //! Return number of batches drawn this frame
    unsigned getNumBatches() const { return mNumBatches; }
    //! Return dummy color texture format for shadow maps. Is "NULL" (consume no video memory) if supported
    unsigned getDummyColorFormat() const { return mDummyColorFormat; }
    //! Return shadow map depth texture format, or D3DFMT_UNKNOWN if not supported
    unsigned getShadowMapFormat() const { return mShadowMapFormat; }
    //! Return 24-bit shadow map depth texture format, or D3DFMT_UNKNOWN if not supported
    unsigned getHiresShadowMapFormat() const { return mHiresShadowMapFormat; }
    //! Return whether deferred rendering is supported
    bool getDeferredSupport() const { return mDeferredSupport; }
    //! Return whether light prepass rendering is supported
    bool getPrepassSupport() const { return mPrepassSupport; }
    //! Return whether Shader Model 3 is supported
    bool getSM3Support() const { return mSM3Support; }
    //! Return whether sampling the depth buffer is supported. Removes need for one render target in deferred rendering
    bool getHardwareDepthSupport() const { return mHardwareDepthSupport; }
    //! Return whether shadow map depth compare is done in hardware
    bool getHardwareShadowSupport() const { return mHardwareShadowSupport; }
    //! Return whether 24-bit shadow maps are supported
    bool getHiresShadowSupport() const { return mHiresShadowSupport; }
    //! Return supported fullscreen resolutions
    std::vector<IntVector2> getResolutions() const;
    //! Return supported multisampling levels
    std::vector<int> getMultiSampleLevels() const;
    //! Return vertex buffer by index
    VertexBuffer* getVertexBuffer(unsigned index) const;
    //! Return index buffer
    IndexBuffer* getIndexBuffer() const { return mIndexBuffer; }
    //! Return vertex declaration
    VertexDeclaration* getVertexDeclaration() const { return mVertexDeclaration; }
    //! Return vertex shader
    VertexShader* getVertexShader() const { return mVertexShader; }
    //! Return pixel shader
    PixelShader* getPixelShader() const { return mPixelShader; }
    //! Return texture by texture unit index
    Texture* getTexture(unsigned index) const;
    //! Return the "view texture"
    Texture* getViewTexture() const { return mViewTexture; }
    //! Return default texture filtering mode
    TextureFilterMode getDefaultTextureFilterMode() const { return mDefaultTextureFilterMode; }
    //! Return render target by index
    RenderSurface* getRenderTarget(unsigned index) const;
    //! Return depth stencil buffer
    RenderSurface* getDepthStencil() const { return mDepthStencil; }
    //! Return the viewport coordinates
    IntRect getViewport() const { return mViewport; }
    //! Return whether alpha testing is enabled
    bool getAlphaTest() const { return mAlphaTest; }
    //! Return alpha test compare mode
    CompareMode getAlphaTestMode() const { return mAlphaTestMode; }
    //! Return texture anisotropy
    unsigned getTextureAnisotropy() const { return mTextureAnisotropy; }
    //! Return alpha test reference value
    float getAlphaRef() const { return mAlphaRef; }
    //! Return blending mode
    BlendMode getBlendMode() const { return mBlendMode; }
    //! Return whether color write is enabled
    bool getColorWrite() const { return mColorWrite; }
    //! Return hardware culling mode
    CullMode getCullMode() const { return mCullMode; }
    //! Return depth constant bias
    float getDepthConstantBias() const { return mDepthConstantBias; }
    //! Return depth slope scaled bias
    float getDepthSlopeScaledBias() const { return mDepthSlopeScaledBias; }
    //! Return depth compare mode
    CompareMode getDepthTest() const { return mDepthTestMode; }
    //! Return whether depth write is enabled
    bool getDepthWrite() const { return mDepthWrite; }
    //! Return polygon fill mode
    FillMode getFillMode() const { return mFillMode; }
    //! Return whether stencil test is enabled
    bool getStencilTest() const { return mStencilTest; }
    //! Return whether scissor test is enabled
    bool getScissorTest() const { return mScissorTest; }
    //! Return scissor rectangle coordinates
    const IntRect& getScissorRect() const { return mScissorRect; }
    //! Return stencil compare mode
    CompareMode getStencilTestMode() const { return mStencilTestMode; }
    //! Return stencil operation to do if stencil test passes
    StencilOp getStencilPass() const { return mStencilPass; }
    //! Return stencil operation to do if stencil test fails
    StencilOp getStencilFail() const { return mStencilFail; }
    //! Return stencil operation to do if depth compare fails
    StencilOp getStencilZFail() const { return mStencilZFail; }
    //! Return stencil reference value
    unsigned getStencilRef() const { return mStencilRef; }
    //! Return stencil compare bitmask
    unsigned getStencilMask() const { return mStencilMask; }
    //! Return stream frequency by vertex buffer index
    unsigned getStreamFrequency(unsigned index) const;
    //! Return render target width and height
    IntVector2 getRenderTargetDimensions() const;
    //! Return diffuse buffer for deferred rendering
    Texture2D* getDiffBuffer() const { return mDiffBuffer; }
    //! Return normal buffer for deferred rendering
    Texture2D* getNormalBuffer() const { return mNormalBuffer; }
    //! Return depth buffer for deferred rendering. If reading hardware depth is supported, return a depth texture
    Texture2D* getDepthBuffer() const { return mDepthBuffer; }
    //! Return screen buffer for post-processing
    Texture2D* getScreenBuffer() const { return mScreenBuffer; }
    
    //! Add a GPU object to keep track of. Called by GPUObject.
    void addGPUObject(GPUObject* object);
    //! Remove a GPU object. Called by GPUObject
    void removeGPUObject(GPUObject* object);
    
private:
    //! Create the application window
    void createWindow(int width, int height);
    //! Create the Direct3D interface
    void createInterface();
    //! Create the Direct3D device
    void createDevice(unsigned adapter, unsigned deviceType);
    //! Create deferred rendering render targets
    void createRenderTargets();
    //! Reset the Direct3D device
    void resetDevice();
    //! Notify all GPU resources so they can release themselves as needed
    void onDeviceLost();
    //! Notify all GPU resources so they can recreate themselves as needed
    void onDeviceReset();
    //! Reset cached rendering state
    void resetCachedState();
    //! Handle operating system window message
    void handleWindowMessage(StringHash eventType, VariantMap& eventData);
    
    //! Implementation
    RendererImpl* mImpl;
    //! Window title
    std::string mTitle;
    //! Rendering mode
    RenderMode mMode;
    //! Window width
    int mWidth;
    //! Window height
    int mHeight;
    //! Multisampling mode
    int mMultiSample;
    //! Stored window X-position
    int mWindowPosX;
    //! Stored window Y-position
    int mWindowPosY;
    //! Fullscreen flag
    bool mFullscreen;
    //! Vertical sync flag
    bool mVsync;
    //! Window closed flag
    bool mClosed;
    //! Direct3D device lost flag
    bool mDeviceLost;
    //! Query issued (used to flush the GPU command queue) flag
    bool mQueryIssued;
    //! Use auto depth stencil flag
    bool mSystemDepthStencil;
    //! Deferred rendering support flag
    bool mDeferredSupport;
    //! Light prepass support flag
    bool mPrepassSupport;
    //! Shader Model 3 flag
    bool mSM3Support;
    //! Hardware depth buffer reading support flag
    bool mHardwareDepthSupport;
    //! Hardware shadow map depth compare support flag
    bool mHardwareShadowSupport;
    //! 24-bit shadow map support flag
    bool mHiresShadowSupport;
    //! Force Shader Model 2 flag
    bool mForceSM2;
    //! Number of primitives this frame
    unsigned mNumPrimitives;
    //! Number of batches this frame
    unsigned mNumBatches;
    //! Immediate rendering primitive type
    PrimitiveType mImmediateType;
    //! Immediate vertex buffer start position
    unsigned mImmediateStartPos;
    //! Immediate rendering vertex buffer size
    unsigned mImmediateVertexCount;
    //! Immediate rendering vertex number
    unsigned mImmediateCurrentVertex;
    //! Immediate rendering vertex buffer in use
    VertexBuffer* mImmediateBuffer;
    //! Immediate rendering data pointer
    unsigned char* mImmediateDataPtr;
    //! GPU objects
    std::vector<GPUObject*> mGPUObjects;
    //! Vertex declarations
    std::map<unsigned long long, SharedPtr<VertexDeclaration> > mVertexDeclarations;
    //! Immediate rendering vertex buffers by vertex declaration
    std::map<unsigned, SharedPtr<VertexBuffer> > mImmediateVertexBuffers;
    //! Immediate rendering vertex buffer start positions
    std::map<unsigned, unsigned> mImmediateVertexBufferPos;
    //! Deferred rendering diffuse buffer
    SharedPtr<Texture2D> mDiffBuffer;
    //! Deferred rendering normal buffer
    SharedPtr<Texture2D> mNormalBuffer;
    //! Deferred rendering depth buffer
    SharedPtr<Texture2D> mDepthBuffer;
    //! Screen buffer for post processing
    SharedPtr<Texture2D> mScreenBuffer;
    //! Shadow map dummy color texture format
    unsigned mDummyColorFormat;
    //! Shadow map depth texture format
    unsigned mShadowMapFormat;
    //! Shadow map 24-bit depth texture format
    unsigned mHiresShadowMapFormat;
    //! Vertex buffers in use
    VertexBuffer* mVertexBuffer[MAX_VERTEX_STREAMS];
    //! Stream frequencies by vertex buffer
    unsigned mStreamFrequency[MAX_VERTEX_STREAMS];
    //! Index buffer in use
    IndexBuffer* mIndexBuffer;
    //! Vertex declaration in use
    VertexDeclaration* mVertexDeclaration;
    //! Vertex shader in use
    VertexShader* mVertexShader;
    //! Pixel shader in use
    PixelShader* mPixelShader;
    //! Textures in use
    Texture* mTexture[MAX_TEXTURE_UNITS];
    //! "View texture" to prevent deferred rendering of sampling the destination render target during G-buffer rendering
    Texture* mViewTexture;
    //! Render targets in use
    RenderSurface* mRenderTarget[MAX_RENDERTARGETS];
    //! Depth stencil buffer in use
    RenderSurface* mDepthStencil;
    //! Viewport coordinates
    IntRect mViewport;
    //! Alpha test enable flag
    bool mAlphaTest;
    //! Alpha test compare mode
    CompareMode mAlphaTestMode;
    //! Alpha test reference value
    float mAlphaRef;
    //! Texture anisotropy level
    unsigned mTextureAnisotropy;
    //! Blending mode
    BlendMode mBlendMode;
    //! Color write enable
    bool mColorWrite;
    //! Hardware culling mode
    CullMode mCullMode;
    //! Depth constant bias
    float mDepthConstantBias;
    //! Depth slope scaled bias
    float mDepthSlopeScaledBias;
    //! Depth compare mode
    CompareMode mDepthTestMode;
    //! Depth write enable flag
    bool mDepthWrite;
    //! Polygon fill mode
    FillMode mFillMode;
    //! Scissor test rectangle
    IntRect mScissorRect;
    //! Scissor test enable flag
    bool mScissorTest;
    //! Stencil test compare mode
    CompareMode mStencilTestMode;
    //! Stencil operation on pass
    StencilOp mStencilPass;
    //! Stencil operation on fail
    StencilOp mStencilFail;
    //! Stencil operation on depth fail
    StencilOp mStencilZFail;
    //! Stencil test enable flag
    bool mStencilTest;
    //! Stencil test reference value
    unsigned mStencilRef;
    //! Stencil compare bitmask
    unsigned mStencilMask;
    //! Default texture filtering mode
    TextureFilterMode mDefaultTextureFilterMode;
};

#endif // RENDERER_RENDERER_H
