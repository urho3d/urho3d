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
#include "HashMap.h"
#include "Matrix3x4.h"
#include "Object.h"
#include "Rect.h"
#include "GraphicsDefs.h"

class Image;
class IndexBuffer;
class Matrix3;
class Matrix4;
class Matrix3x4;
class GPUObject;
class GraphicsImpl;
class RenderSurface;
class ShaderProgram;
class ShaderVariation;
class Texture;
class Texture2D;
class TextureCube;
class Vector3;
class Vector4;
class VertexBuffer;

typedef Map<Pair<ShaderVariation*, ShaderVariation*>, SharedPtr<ShaderProgram> > ShaderProgramMap;

/// Graphics subsystem. Manages the application window, rendering state and GPU resources
class Graphics : public Object
{
    OBJECT(Graphics);
    
public:
    /// Construct
    Graphics(Context* context_);
    /// Destruct. Close the window and release the Direct3D9 device 
    virtual ~Graphics();
    
    /// Set window title
    void SetWindowTitle(const String& windowTitle);
    /// Set screen mode. In deferred rendering modes multisampling means edge filtering instead of MSAA
    bool SetMode(RenderMode mode, int width, int height, bool fullscreen, bool vsync, int multiSample);
    /// Set screen resolution only
    bool SetMode(int width, int height);
    /// Set rendering mode only
    bool SetMode(RenderMode mode);
    /// Toggle between full screen and windowed mode
    bool ToggleFullscreen();
    /// Close the window
    void Close();
    /// Take a screenshot
    bool TakeScreenShot(Image& destImage);
    /// Set whether to flush GPU command queue at the end of each frame. Default true
    void SetFlushGPU(bool enable);
    /// Begin frame rendering
    bool BeginFrame();
    /// End frame rendering and swap buffers
    void EndFrame();
    /// Clear any or all of render target, depth buffer and stencil buffer
    void Clear(unsigned flags, const Color& color = Color(0.0f, 0.0f, 0.0f, 0.0f), float depth = 1.0f, unsigned stencil = 0);
    /// Draw non-indexed geometry
    void Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount);
    /// Draw indexed geometry
    void Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount);
    /// Draw indexed, instanced geometry. No-op on OpenGL
    void DrawInstanced(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount, unsigned instanceCount);
    /// Set vertex buffer
    void SetVertexBuffer(VertexBuffer* buffer);
    /// Set multiple vertex buffers
    bool SetVertexBuffers(const Vector<VertexBuffer*>& buffers, const PODVector<unsigned>& elementMasks, unsigned instanceOffset = 0);
    /// Set multiple vertex buffers
    bool SetVertexBuffers(const Vector<SharedPtr<VertexBuffer> >& buffers, const PODVector<unsigned>& elementMasks, unsigned instanceOffset = 0);
    /// Set index buffer
    void SetIndexBuffer(IndexBuffer* buffer);
    /// Set shaders
    void SetShaders(ShaderVariation* vs, ShaderVariation* ps);
    /// Set shader bool constants
    void SetShaderParameter(ShaderParameter param, const bool* data, unsigned count);
    /// Set shader float constants
    void SetShaderParameter(ShaderParameter param, const float* data, unsigned count);
    /// Set shader int constants
    void SetShaderParameter(ShaderParameter param, const int* data, unsigned count);
    /// Set shader float constant
    void SetShaderParameter(ShaderParameter param, float value);
    /// Set shader color constant
    void SetShaderParameter(ShaderParameter param, const Color& color);
    /// Set shader 3x3 matrix constant
    void SetShaderParameter(ShaderParameter param, const Matrix3& matrix);
    /// Set shader 3D vector constant
    void SetShaderParameter(ShaderParameter param, const Vector3& vector);
    /// Set shader 4x4 matrix constant
    void SetShaderParameter(ShaderParameter param, const Matrix4& matrix);
    /// Set shader 4D vector constant
    void SetShaderParameter(ShaderParameter param, const Vector4& vector);
    /// Set shader 4x3 matrix constant
    void SetShaderParameter(ShaderParameter param, const Matrix3x4& matrix);
    /// Check whether a shader parameter in the currently set shaders needs update
    bool NeedParameterUpdate(ShaderParameter param, const void* source);
    /// Check whether the current pixel shader uses a texture unit
    bool NeedTextureUnit(TextureUnit unit);
    /// Clear remembered shader parameter sources
    void ClearParameterSources();
    /// Clear remembered transform shader parameter sources
    void ClearTransformSources();
    /// Clean up unused shader programs
    void CleanupShaderPrograms();
    /// Set texture
    void SetTexture(unsigned index, Texture* texture);
    /// Bind texture unit 0 for update. Called by Texture
    void SetTextureForUpdate(Texture* texture);
    /// Set default texture filtering mode
    void SetDefaultTextureFilterMode(TextureFilterMode mode);
    /// Set texture anisotropy
    void SetTextureAnisotropy(unsigned level);
    /// Dirty texture parameters of all textures (when global settings change)
    void SetTextureParametersDirty();
    /// Reset all render targets and depth buffer (render to back buffer and back buffer depth stencil)
    void ResetRenderTargets();
    /// Reset specific render target
    void ResetRenderTarget(unsigned index);
    /// Reset depth stencil
    void ResetDepthStencil();
    /// Set render target
    void SetRenderTarget(unsigned index, RenderSurface* renderTarget);
    /// Set render target
    void SetRenderTarget(unsigned index, Texture2D* renderTexture);
    /// Set depth stencil buffer
    void SetDepthStencil(RenderSurface* depthStencil);
    /// Set depth stencil buffer
    void SetDepthStencil(Texture2D* depthTexture);
    /// Set viewport
    void SetViewport(const IntRect& rect);
    /// Set "view texture" to prevent sampling from the destination render target
    void SetViewTexture(Texture* texture);
    /// Set alpha test
    void SetAlphaTest(bool enable, CompareMode mode = CMP_ALWAYS, float alphaRef = 0.5f);
    /// Set blending mode
    void SetBlendMode(BlendMode mode);
    /// Set color write on/off
    void SetColorWrite(bool enable);
    /// Set hardware culling mode
    void SetCullMode(CullMode mode);
    /// Set depth bias
    void SetDepthBias(float constantBias, float slopeScaledBias);
    /// Set depth compare
    void SetDepthTest(CompareMode mode);
    /// Set depth write on/off
    void SetDepthWrite(bool enable);
    /// Set polygon fill mode
    void SetFillMode(FillMode mode);
    /// Set scissor test
    void SetScissorTest(bool enable, const Rect& rect = Rect::FULL, bool borderInclusive = true);
    /// Set scissor test
    void SetScissorTest(bool enable, const IntRect& rect);
    /// Set stencil test
    void SetStencilTest(bool enable, CompareMode mode = CMP_ALWAYS, StencilOp pass = OP_KEEP, StencilOp fail = OP_KEEP, StencilOp zFail = OP_KEEP, unsigned stencilRef = 0, unsigned stencilMask = M_MAX_UNSIGNED);
    /// Set vertex buffer stream frequency. No-op on OpenGL
    void SetStreamFrequency(unsigned index, unsigned frequency);
    /// Reset stream frequencies. No-op on OpenGL
    void ResetStreamFrequencies();
    /// Begin immediate rendering command
    bool BeginImmediate(PrimitiveType type, unsigned vertexCount, unsigned elementMask);
    /// Define immediate vertex
    bool DefineVertex(const Vector3& vertex);
    /// Define immediate normal
    bool DefineNormal(const Vector3& normal);
    /// Define immediate texture coordinate
    bool DefineTexCoord(const Vector2& texCoord);
    /// Define immediate color
    bool DefineColor(const Color& color);
    /// Define immediate color
    bool DefineColor(unsigned color);
    /// End immediate rendering command and render
    void EndImmediate();
    /// Set force Shader Model 2 flag. No effect on OpenGL
    void SetForceSM2(bool enable);
    
    /// Return whether rendering initialized
    bool IsInitialized() const { return initialized_; }
    /// Return graphics implementation, which holds the actual API-specific resources
    GraphicsImpl* GetImpl() const { return impl_; }
    /// Return window title
    const String& GetWindowTitle() const { return windowTitle_; }
    /// Return rendering mode
    RenderMode GetRenderMode() const { return mode_; }
    /// Return window width
    int GetWidth() const { return width_; }
    /// Return window height
    int GetHeight() const { return height_; }
    /// Return multisample mode (1 = no multisampling)
    int GetMultiSample() const { return multiSample_; }
    /// Return whether window is fullscreen
    bool GetFullscreen() const { return fullscreen_; }
    /// Return whether vertical sync is on
    bool GetVSync() const { return vsync_; }
    /// Return whether GPU command queue is flushed at the end of each frame
    bool GetFlushGPU() const { return flushGPU_; }
    /// Return whether device is lost, and can not yet render. Always false on OpenGL
    bool IsDeviceLost() const { return false; }
    /// Return immediate rendering data pointer
    unsigned char* GetImmediateDataPtr() const;
    /// Return number of primitives drawn this frame
    unsigned GetNumPrimitives() const { return numPrimitives_; }
    /// Return number of batches drawn this frame
    unsigned GetNumBatches() const { return numBatches_; }
    /// Return dummy color texture format for shadow maps. Is always 0 on OpenGL
    unsigned GetDummyColorFormat() const { return 0; }
    /// Return shadow map depth texture format, or 0 if not supported
    unsigned GetShadowMapFormat() const { return shadowMapFormat_; }
    /// Return 24-bit shadow map depth texture format, or 0 if not supported
    unsigned GetHiresShadowMapFormat() const { return hiresShadowMapFormat_; }
    /// Return whether texture render targets are supported
    bool GetRenderTargetSupport() const { return renderTargetSupport_; }
    /// Return whether deferred rendering is supported
    bool GetDeferredSupport() const { return deferredSupport_; }
    /// Return whether Shader Model 3 is supported. Always false on OpenGL
    bool GetSM3Support() const { return false; }
    /// Return whether shadow map depth compare is done in hardware. Always false on OpenGL to avoid the HW suffix in shaders
    bool GetHardwareShadowSupport() const { return false; }
    /// Return whether 24-bit shadow maps are supported. Assume true on OpenGL
    bool GetHiresShadowSupport() const { return true; }
    /// Return whether stream offset is supported. Always false on OpenGL
    bool GetStreamOffsetSupport() const { return false; }
    /// Return supported fullscreen resolutions
    PODVector<IntVector2> GetResolutions() const;
    /// Return supported multisampling levels
    PODVector<int> GetMultiSampleLevels() const;
    /// Return vertex buffer by index
    VertexBuffer* GetVertexBuffer(unsigned index) const;
    /// Return index buffer
    IndexBuffer* GetIndexBuffer() const { return indexBuffer_; }
    /// Return vertex shader
    ShaderVariation* GetVertexShader() const { return vertexShader_; }
    /// Return pixel shader
    ShaderVariation* GetPixelShader() const { return pixelShader_; }
    /// Return shader program
    ShaderProgram* GetShaderProgram() const { return shaderProgram_; }
    /// Return shader parameter index by name
    ShaderParameter GetShaderParameter(const String& name);
    /// Return texture unit index by name
    TextureUnit GetTextureUnit(const String& name);
    /// Return shader parameter name by index
    const String& GetShaderParameterName(ShaderParameter parameter);
    /// Return texture unit name by index
    const String& GetTextureUnitName(TextureUnit unit);
    /// Return texture by texture unit index
    Texture* GetTexture(unsigned index) const;
    /// Return the "view texture"
    Texture* GetViewTexture() const { return viewTexture_; }
    /// Return default texture filtering mode
    TextureFilterMode GetDefaultTextureFilterMode() const { return defaultTextureFilterMode_; }
    /// Return render target by index
    RenderSurface* GetRenderTarget(unsigned index) const;
    /// Return depth stencil buffer
    RenderSurface* GetDepthStencil() const { return depthStencil_; }
    /// Return the viewport coordinates
    IntRect GetViewport() const { return viewport_; }
    /// Return whether alpha testing is enabled
    bool GetAlphaTest() const { return alphaTest_; }
    /// Return alpha test compare mode
    CompareMode GetAlphaTestMode() const { return alphaTestMode_; }
    /// Return texture anisotropy
    unsigned GetTextureAnisotropy() const { return textureAnisotropy_; }
    /// Return alpha test reference value
    float GetAlphaRef() const { return alphaRef_; }
    /// Return blending mode
    BlendMode GetBlendMode() const { return blendMode_; }
    /// Return whether color write is enabled
    bool GetColorWrite() const { return colorWrite_; }
    /// Return hardware culling mode
    CullMode GetCullMode() const { return cullMode_; }
    /// Return depth constant bias
    float GetDepthConstantBias() const { return constantDepthBias_; }
    /// Return depth slope scaled bias
    float GetDepthSlopeScaledBias() const { return slopeScaledDepthBias_; }
    /// Return depth compare mode
    CompareMode GetDepthTest() const { return depthTestMode_; }
    /// Return whether depth write is enabled
    bool GetDepthWrite() const { return depthWrite_; }
    /// Return polygon fill mode
    FillMode GetFillMode() const { return fillMode_; }
    /// Return whether stencil test is enabled
    bool GetStencilTest() const { return stencilTest_; }
    /// Return whether scissor test is enabled
    bool GetScissorTest() const { return scissorTest_; }
    /// Return scissor rectangle coordinates
    const IntRect& GetScissorRect() const { return scissorRect_; }
    /// Return stencil compare mode
    CompareMode GetStencilTestMode() const { return stencilTestMode_; }
    /// Return stencil operation to do if stencil test passes
    StencilOp GetStencilPass() const { return stencilPass_; }
    /// Return stencil operation to do if stencil test fails
    StencilOp GetStencilFail() const { return stencilFail_; }
    /// Return stencil operation to do if depth compare fails
    StencilOp GetStencilZFail() const { return stencilZFail_; }
    /// Return stencil reference value
    unsigned GetStencilRef() const { return stencilRef_; }
    /// Return stencil compare bitmask
    unsigned GetStencilMask() const { return stencilMask_; }
    /// Return stream frequency by vertex buffer index. Always returns 0 on OpenGL
    unsigned GetStreamFrequency(unsigned index) const { return 0; }
    /// Return render target width and height
    IntVector2 GetRenderTargetDimensions() const;
    /// Return diffuse buffer for deferred rendering
    Texture2D* GetDiffBuffer() const { return diffBuffer_; }
    /// Return normal buffer for deferred rendering
    Texture2D* GetNormalBuffer() const { return normalBuffer_; }
    /// Return depth buffer for deferred rendering. If reading hardware depth is supported, return a depth texture
    Texture2D* GetDepthBuffer() const { return depthBuffer_; }
    /// Return screen buffer for post-processing
    Texture2D* GetScreenBuffer() const { return screenBuffer_; }
    
    /// Add a GPU object to keep track of. Called by GPUObject.
    void AddGPUObject(GPUObject* object);
    /// Remove a GPU object. Called by GPUObject
    void RemoveGPUObject(GPUObject* object);
    
    /// Return the API-specific alpha texture format
    static unsigned GetAlphaFormat();
    /// Return the API-specific luminance texture format
    static unsigned GetLuminanceFormat();
    /// Return the API-specific luminance alpha texture format
    static unsigned GetLuminanceAlphaFormat();
    /// Return the API-specific RGB texture format
    static unsigned GetRGBFormat();
    /// Return the API-specific RGBA texture format
    static unsigned GetRGBAFormat();
    /// Return the API-specific deferred rendering depth texture format
    static unsigned GetDepthFormat();
    /// Return the API-specific depth stencil texture format
    static unsigned GetDepthStencilFormat();
    
private:
    /// Create the application window. Return true if successful
    bool OpenWindow(int width, int height);
    /// Get the pixel format for a given multisample level. Return nonzero if successful
    int GetPixelFormat(RenderMode mode, int multiSample);
    /// Change to a fullscreen mode. Return true if successful
    bool SetScreenMode(int newWidth, int newHeight);
    /// Restore desktop mode
    void RestoreScreenMode();
    /// Adjust the window for new resolution and fullscreen mode
    void AdjustWindow(int newWidth, int newHeight, bool newFullscreen);
    /// Create deferred rendering render targets
    void CreateRenderTargets();
    /// Reset cached rendering state
    void ResetCachedState();
    /// Set draw buffer(s) on the FBO
    void SetDrawBuffers();
    /// Destroy the OpenGL rendering context and the window
    void Release();
    /// Initialize OpenGL extensions. Creates a dummy window and OpenGL context
    void InitializeExtensions();
    /// Initialize shader parameter and texture unit mappings
    void InitializeShaderParameters();
    
    /// Implementation
    GraphicsImpl* impl_;
    /// Window title
    String windowTitle_;
    /// Rendering mode
    RenderMode mode_;
    /// Window width
    int width_;
    /// Window height
    int height_;
    /// Multisampling mode
    int multiSample_;
    /// Initialized flag
    bool initialized_;
    /// Fullscreen flag
    bool fullscreen_;
    /// Vertical sync flag
    bool vsync_;
    /// Flush GPU command queue flag
    bool flushGPU_;
    /// Texture render target support flag
    bool renderTargetSupport_;
    /// Deferred rendering support flag
    bool deferredSupport_;
    /// Number of primitives this frame
    unsigned numPrimitives_;
    /// Number of batches this frame
    unsigned numBatches_;
    /// Immediate rendering primitive type
    PrimitiveType immediateType_;
    /// Immediate rendering total number of vertices
    unsigned immediateVertexCount_;
    /// Immediate rendering vertex size
    unsigned immediateVertexSize_;
    /// Immediate rendering vertex element mask
    unsigned immediateElementMask_;
    /// Immediate rendering current vertex number
    unsigned immediateCurrentVertex_;
    /// Immediate rendering data pointer
    unsigned char* immediateDataPtr_;
    /// Immediate rendering data buffer
    PODVector<unsigned char> immediateVertexData_;
    /// Immediate rendering element offsets
    unsigned immediateElementOffsets_[MAX_IMMEDIATE_ELEMENTS];
    /// GPU objects
    Vector<GPUObject*> gpuObjects_;
    /// Deferred rendering diffuse buffer
    SharedPtr<Texture2D> diffBuffer_;
    /// Deferred rendering normal buffer
    SharedPtr<Texture2D> normalBuffer_;
    /// Deferred rendering depth buffer
    SharedPtr<Texture2D> depthBuffer_;
    /// Screen buffer for post processing
    SharedPtr<Texture2D> screenBuffer_;
    /// Shadow map depth texture format
    unsigned shadowMapFormat_;
    /// Shadow map 24-bit depth texture format
    unsigned hiresShadowMapFormat_;
    /// Vertex buffers in use
    VertexBuffer* vertexBuffers_[MAX_VERTEX_STREAMS];
    /// Element mask in use
    unsigned elementMasks_[MAX_VERTEX_STREAMS];
    /// Index buffer in use
    IndexBuffer* indexBuffer_;
    /// Vertex shader in use
    ShaderVariation* vertexShader_;
    /// Pixel shader in use
    ShaderVariation* pixelShader_;
    /// Shader program in use
    ShaderProgram* shaderProgram_;
    /// Shader parameter mappings
    Map<String, ShaderParameter> shaderParameters_;
    /// Linked shader programs
    ShaderProgramMap shaderPrograms_;
    /// Shader parameters global frame number
    unsigned shaderParameterFrame_;
    /// Textures in use
    Texture* textures_[MAX_TEXTURE_UNITS];
    /// OpenGL texture types in use
    unsigned textureTypes_[MAX_TEXTURE_UNITS];
    /// "View texture" to prevent sampling the destination render target
    Texture* viewTexture_;
    /// Texture unit mappings
    Map<String, TextureUnit> textureUnits_;
    /// Render targets in use
    RenderSurface* renderTargets_[MAX_RENDERTARGETS];
    /// Depth stencil buffer in use
    RenderSurface* depthStencil_;
    /// Viewport coordinates
    IntRect viewport_;
    /// Alpha test enable flag
    bool alphaTest_;
    /// Alpha test compare mode
    CompareMode alphaTestMode_;
    /// Alpha test reference value
    float alphaRef_;
    /// Texture anisotropy level
    unsigned textureAnisotropy_;
    /// Blending mode
    BlendMode blendMode_;
    /// Color write enable
    bool colorWrite_;
    /// Hardware culling mode
    CullMode cullMode_;
    /// Depth constant bias
    float constantDepthBias_;
    /// Depth slope scaled bias
    float slopeScaledDepthBias_;
    /// Depth compare mode
    CompareMode depthTestMode_;
    /// Depth write enable flag
    bool depthWrite_;
    /// Polygon fill mode
    FillMode fillMode_;
    /// Scissor test rectangle
    IntRect scissorRect_;
    /// Scissor test enable flag
    bool scissorTest_;
    /// Stencil test compare mode
    CompareMode stencilTestMode_;
    /// Stencil operation on pass
    StencilOp stencilPass_;
    /// Stencil operation on fail
    StencilOp stencilFail_;
    /// Stencil operation on depth fail
    StencilOp stencilZFail_;
    /// Stencil test enable flag
    bool stencilTest_;
    /// Stencil test reference value
    unsigned stencilRef_;
    /// Stencil compare bitmask
    unsigned stencilMask_;
    /// Default texture filtering mode
    TextureFilterMode defaultTextureFilterMode_;
    /// Map for additional depth textures, to emulate Direct3D9 ability to mix rendertarget and backbuffer rendering
    HashMap<int, SharedPtr<Texture2D> > depthTextures_;
};

/// Register Graphics library objects
void RegisterGraphicsLibrary(Context* context_);
