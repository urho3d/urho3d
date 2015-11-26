//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../../Container/ArrayPtr.h"
#include "../../Container/HashSet.h"
#include "../../Core/Mutex.h"
#include "../../Core/Object.h"
#include "../../Graphics/GraphicsDefs.h"
#include "../../Math/Color.h"
#include "../../Math/Plane.h"
#include "../../Math/Rect.h"
#include "../../Resource/Image.h"

namespace Urho3D
{

class File;
class Image;
class IndexBuffer;
class GPUObject;
class GraphicsImpl;
class RenderSurface;
class Shader;
class ShaderPrecache;
class ShaderProgram;
class ShaderVariation;
class Texture;
class Texture2D;
class TextureCube;
class Vector3;
class Vector4;
class VertexBuffer;
class VertexDeclaration;

struct ShaderParameter;

typedef HashMap<Pair<ShaderVariation*, ShaderVariation*>, SharedPtr<ShaderProgram> > ShaderProgramMap;

/// CPU-side scratch buffer for vertex data updates.
struct ScratchBuffer
{
    ScratchBuffer() :
        size_(0),
        reserved_(false)
    {
    }

    /// Buffer data.
    SharedArrayPtr<unsigned char> data_;
    /// Data size.
    unsigned size_;
    /// Reserved flag.
    bool reserved_;
};

/// %Graphics subsystem. Manages the application window, rendering state and GPU resources.
class URHO3D_API Graphics : public Object
{
    URHO3D_OBJECT(Graphics, Object);

public:
    /// Construct.
    Graphics(Context* context);
    /// Destruct. Release the Direct3D9 device and close the window.
    virtual ~Graphics();

    /// Set external window handle. Only effective before setting the initial screen mode.
    void SetExternalWindow(void* window);
    /// Set window title.
    void SetWindowTitle(const String& windowTitle);
    /// Set window icon.
    void SetWindowIcon(Image* windowIcon);
    /// Set window position. Sets initial position if window is not created yet.
    void SetWindowPosition(const IntVector2& position);
    /// Set window position. Sets initial position if window is not created yet.
    void SetWindowPosition(int x, int y);
    /// Set screen mode. Return true if successful.
    bool SetMode
        (int width, int height, bool fullscreen, bool borderless, bool resizable, bool vsync, bool tripleBuffer, int multiSample);
    /// Set screen resolution only. Return true if successful.
    bool SetMode(int width, int height);
    /// Set whether the main window uses sRGB conversion on write.
    void SetSRGB(bool enable);
    /// Set whether to flush the GPU command buffer to prevent multiple frames being queued and uneven frame timesteps. Default off, may decrease performance if enabled.
    void SetFlushGPU(bool enable);
    /// Set allowed screen orientations as a space-separated list of "LandscapeLeft", "LandscapeRight", "Portrait" and "PortraitUpsideDown". Affects currently only iOS platform.
    void SetOrientations(const String& orientations);
    /// Toggle between full screen and windowed mode. Return true if successful.
    bool ToggleFullscreen();
    /// Close the window.
    void Close();
    /// Take a screenshot. Return true if successful.
    bool TakeScreenShot(Image& destImage);
    /// Begin frame rendering. Return true if device available and can render.
    bool BeginFrame();
    /// End frame rendering and swap buffers.
    void EndFrame();
    /// Clear any or all of rendertarget, depth buffer and stencil buffer.
    void Clear(unsigned flags, const Color& color = Color(0.0f, 0.0f, 0.0f, 0.0f), float depth = 1.0f, unsigned stencil = 0);
    /// Resolve multisampled backbuffer to a texture rendertarget. The texture's size should match the viewport size.
    bool ResolveToTexture(Texture2D* destination, const IntRect& viewport);
    /// Draw non-indexed geometry.
    void Draw(PrimitiveType type, unsigned vertexStart, unsigned vertexCount);
    /// Draw indexed geometry.
    void Draw(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount);
    /// Draw indexed, instanced geometry. An instancing vertex buffer must be set.
    void DrawInstanced(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned minVertex, unsigned vertexCount,
        unsigned instanceCount);
    /// Set vertex buffer.
    void SetVertexBuffer(VertexBuffer* buffer);
    /// Set multiple vertex buffers.
    bool SetVertexBuffers
        (const PODVector<VertexBuffer*>& buffers, const PODVector<unsigned>& elementMasks, unsigned instanceOffset = 0);
    /// Set multiple vertex buffers.
    bool SetVertexBuffers
        (const Vector<SharedPtr<VertexBuffer> >& buffers, const PODVector<unsigned>& elementMasks, unsigned instanceOffset = 0);
    /// Set index buffer.
    void SetIndexBuffer(IndexBuffer* buffer);
    /// Set shaders.
    void SetShaders(ShaderVariation* vs, ShaderVariation* ps);
    /// Set shader float constants.
    void SetShaderParameter(StringHash param, const float* data, unsigned count);
    /// Set shader float constant.
    void SetShaderParameter(StringHash param, float value);
    /// Set shader boolean constant.
    void SetShaderParameter(StringHash param, bool value);
    /// Set shader color constant.
    void SetShaderParameter(StringHash param, const Color& color);
    /// Set shader 2D vector constant.
    void SetShaderParameter(StringHash param, const Vector2& vector);
    /// Set shader 3x3 matrix constant.
    void SetShaderParameter(StringHash param, const Matrix3& matrix);
    /// Set shader 3D vector constant.
    void SetShaderParameter(StringHash param, const Vector3& vector);
    /// Set shader 4x4 matrix constant.
    void SetShaderParameter(StringHash param, const Matrix4& matrix);
    /// Set shader 4D vector constant.
    void SetShaderParameter(StringHash param, const Vector4& vector);
    /// Set shader 3x4 matrix constant.
    void SetShaderParameter(StringHash param, const Matrix3x4& matrix);
    /// Set shader constant from a variant. Supported variant types: bool, float, vector2, vector3, vector4, color.
    void SetShaderParameter(StringHash param, const Variant& value);
    /// Check whether a shader parameter group needs update. Does not actually check whether parameters exist in the shaders.
    bool NeedParameterUpdate(ShaderParameterGroup group, const void* source);
    /// Check whether a shader parameter exists on the currently set shaders.
    bool HasShaderParameter(StringHash param);
    /// Check whether the current pixel shader uses a texture unit.
    bool HasTextureUnit(TextureUnit unit);
    /// Clear remembered shader parameter source group.
    void ClearParameterSource(ShaderParameterGroup group);
    /// Clear remembered shader parameter sources.
    void ClearParameterSources();
    /// Clear remembered transform shader parameter sources.
    void ClearTransformSources();
    /// Set texture.
    void SetTexture(unsigned index, Texture* texture);
    /// Set default texture filtering mode.
    void SetDefaultTextureFilterMode(TextureFilterMode mode);
    /// Set texture anisotropy.
    void SetTextureAnisotropy(unsigned level);
    /// Reset all rendertargets, depth-stencil surface and viewport.
    void ResetRenderTargets();
    /// Reset specific rendertarget.
    void ResetRenderTarget(unsigned index);
    /// Reset depth-stencil surface.
    void ResetDepthStencil();
    /// Set rendertarget.
    void SetRenderTarget(unsigned index, RenderSurface* renderTarget);
    /// Set rendertarget.
    void SetRenderTarget(unsigned index, Texture2D* texture);
    /// Set depth-stencil surface.
    void SetDepthStencil(RenderSurface* depthStencil);
    /// Set depth-stencil surface.
    void SetDepthStencil(Texture2D* texture);
    /// Set viewport.
    void SetViewport(const IntRect& rect);
    /// Set blending mode.
    void SetBlendMode(BlendMode mode);
    /// Set color write on/off.
    void SetColorWrite(bool enable);
    /// Set hardware culling mode.
    void SetCullMode(CullMode mode);
    /// Set depth bias.
    void SetDepthBias(float constantBias, float slopeScaledBias);
    /// Set depth compare.
    void SetDepthTest(CompareMode mode);
    /// Set depth write on/off.
    void SetDepthWrite(bool enable);
    /// Set polygon fill mode.
    void SetFillMode(FillMode mode);
    /// Set scissor test.
    void SetScissorTest(bool enable, const Rect& rect = Rect::FULL, bool borderInclusive = true);
    /// Set scissor test.
    void SetScissorTest(bool enable, const IntRect& rect);
    /// Set stencil test.
    void SetStencilTest
        (bool enable, CompareMode mode = CMP_ALWAYS, StencilOp pass = OP_KEEP, StencilOp fail = OP_KEEP, StencilOp zFail = OP_KEEP,
            unsigned stencilRef = 0, unsigned compareMask = M_MAX_UNSIGNED, unsigned writeMask = M_MAX_UNSIGNED);
    /// Set a custom clipping plane. The plane is specified in world space, but is dependent on the view and projection matrices.
    void SetClipPlane(bool enable, const Plane& clipPlane = Plane::UP, const Matrix3x4& view = Matrix3x4::IDENTITY,
        const Matrix4& projection = Matrix4::IDENTITY);
    /// Begin dumping shader variation names to an XML file for precaching.
    void BeginDumpShaders(const String& fileName);
    /// End dumping shader variations names.
    void EndDumpShaders();
    /// Precache shader variations from an XML file generated with BeginDumpShaders().
    void PrecacheShaders(Deserializer& source);

    /// Return whether rendering initialized.
    bool IsInitialized() const;

    /// Return graphics implementation, which holds the actual API-specific resources.
    GraphicsImpl* GetImpl() const { return impl_; }

    /// Return OS-specific external window handle. Null if not in use.
    void* GetExternalWindow() const { return externalWindow_; }

    /// Return window title.
    const String& GetWindowTitle() const { return windowTitle_; }

    /// Return graphics API name.
    const String& GetApiName() const { return apiName_; }

    /// Return window position.
    IntVector2 GetWindowPosition() const;

    /// Return window width.
    int GetWidth() const { return width_; }

    /// Return window height.
    int GetHeight() const { return height_; }

    /// Return multisample mode (1 = no multisampling.)
    int GetMultiSample() const { return multiSample_; }

    /// Return whether window is fullscreen.
    bool GetFullscreen() const { return fullscreen_; }

    /// Return whether window is resizable.
    bool GetResizable() const { return resizable_; }

    /// Return whether window is borderless.
    bool GetBorderless() const { return borderless_; }

    /// Return whether vertical sync is on.
    bool GetVSync() const { return vsync_; }

    /// Return whether triple buffering is enabled.
    bool GetTripleBuffer() const { return tripleBuffer_; }

    /// Return whether the main window is using sRGB conversion on write.
    bool GetSRGB() const { return sRGB_; }

    /// Return whether the GPU command buffer is flushed each frame.
    bool GetFlushGPU() const { return flushGPU_; }

    /// Return allowed screen orientations.
    const String& GetOrientations() const { return orientations_; }

    /// Return whether Direct3D device is lost, and can not yet render. This happens during fullscreen resolution switching.
    bool IsDeviceLost() const { return deviceLost_; }

    /// Return number of primitives drawn this frame.
    unsigned GetNumPrimitives() const { return numPrimitives_; }

    /// Return number of batches drawn this frame.
    unsigned GetNumBatches() const { return numBatches_; }

    /// Return dummy color texture format for shadow maps. Is "NULL" (consume no video memory) if supported.
    unsigned GetDummyColorFormat() const { return dummyColorFormat_; }

    /// Return shadow map depth texture format, or 0 if not supported.
    unsigned GetShadowMapFormat() const { return shadowMapFormat_; }

    /// Return 24-bit shadow map depth texture format, or 0 if not supported.
    unsigned GetHiresShadowMapFormat() const { return hiresShadowMapFormat_; }

    /// Return whether hardware instancing is supported..
    bool GetInstancingSupport() const { return instancingSupport_; }

    /// Return whether light pre-pass rendering is supported.
    bool GetLightPrepassSupport() const { return lightPrepassSupport_; }

    /// Return whether deferred rendering is supported.
    bool GetDeferredSupport() const { return deferredSupport_; }

    /// Return whether shadow map depth compare is done in hardware.
    bool GetHardwareShadowSupport() const { return hardwareShadowSupport_; }

    /// Return whether a readable hardware depth format is available.
    bool GetReadableDepthSupport() const { return GetReadableDepthFormat() != 0; }

    /// Return whether sRGB conversion on texture sampling is supported.
    bool GetSRGBSupport() const { return sRGBSupport_; }

    /// Return whether sRGB conversion on rendertarget writing is supported.
    bool GetSRGBWriteSupport() const { return sRGBWriteSupport_; }

    /// Return supported fullscreen resolutions. Will be empty if listing the resolutions is not supported on the platform (e.g. HTML5.)
    PODVector<IntVector2> GetResolutions() const;
    /// Return supported multisampling levels.
    PODVector<int> GetMultiSampleLevels() const;
    /// Return the desktop resolution.
    IntVector2 GetDesktopResolution() const;
    /// Return hardware format for a compressed image format, or 0 if unsupported.
    unsigned GetFormat(CompressedFormat format) const;
    /// Return a shader variation by name and defines.
    ShaderVariation* GetShader(ShaderType type, const String& name, const String& defines = String::EMPTY) const;
    /// Return a shader variation by name and defines.
    ShaderVariation* GetShader(ShaderType type, const char* name, const char* defines) const;
    /// Return current vertex buffer by index.
    VertexBuffer* GetVertexBuffer(unsigned index) const;

    /// Return current index buffer.
    IndexBuffer* GetIndexBuffer() const { return indexBuffer_; }

    /// Return current vertex shader.
    ShaderVariation* GetVertexShader() const { return vertexShader_; }

    /// Return current pixel shader.
    ShaderVariation* GetPixelShader() const { return pixelShader_; }

    /// Return texture unit index by name.
    TextureUnit GetTextureUnit(const String& name);
    /// Return texture unit name by index.
    const String& GetTextureUnitName(TextureUnit unit);
    /// Return current texture by texture unit index.
    Texture* GetTexture(unsigned index) const;

    /// Return default texture filtering mode.
    TextureFilterMode GetDefaultTextureFilterMode() const { return defaultTextureFilterMode_; }

    /// Return current rendertarget by index.
    RenderSurface* GetRenderTarget(unsigned index) const;

    /// Return current depth-stencil surface.
    RenderSurface* GetDepthStencil() const { return depthStencil_; }

    /// Return the viewport coordinates.
    IntRect GetViewport() const { return viewport_; }

    /// Return texture anisotropy.
    unsigned GetTextureAnisotropy() const { return textureAnisotropy_; }

    /// Return blending mode.
    BlendMode GetBlendMode() const { return blendMode_; }

    /// Return whether color write is enabled.
    bool GetColorWrite() const { return colorWrite_; }

    /// Return hardware culling mode.
    CullMode GetCullMode() const { return cullMode_; }

    /// Return depth constant bias.
    float GetDepthConstantBias() const { return constantDepthBias_; }

    /// Return depth slope scaled bias.
    float GetDepthSlopeScaledBias() const { return slopeScaledDepthBias_; }

    /// Return depth compare mode.
    CompareMode GetDepthTest() const { return depthTestMode_; }

    /// Return whether depth write is enabled.
    bool GetDepthWrite() const { return depthWrite_; }

    /// Return polygon fill mode.
    FillMode GetFillMode() const { return fillMode_; }

    /// Return whether stencil test is enabled.
    bool GetStencilTest() const { return stencilTest_; }

    /// Return whether scissor test is enabled.
    bool GetScissorTest() const { return scissorTest_; }

    /// Return scissor rectangle coordinates.
    const IntRect& GetScissorRect() const { return scissorRect_; }

    /// Return stencil compare mode.
    CompareMode GetStencilTestMode() const { return stencilTestMode_; }

    /// Return stencil operation to do if stencil test passes.
    StencilOp GetStencilPass() const { return stencilPass_; }

    /// Return stencil operation to do if stencil test fails.
    StencilOp GetStencilFail() const { return stencilFail_; }

    /// Return stencil operation to do if depth compare fails.
    StencilOp GetStencilZFail() const { return stencilZFail_; }

    /// Return stencil reference value.
    unsigned GetStencilRef() const { return stencilRef_; }

    /// Return stencil compare bitmask.
    unsigned GetStencilCompareMask() const { return stencilCompareMask_; }

    /// Return stencil write bitmask.
    unsigned GetStencilWriteMask() const { return stencilWriteMask_; }

    /// Return whether a custom clipping plane is in use.
    bool GetUseClipPlane() const { return useClipPlane_; }

    /// Return rendertarget width and height.
    IntVector2 GetRenderTargetDimensions() const;

    /// Window was resized through user interaction. Called by Input subsystem.
    void WindowResized();
    /// Window was moved through user interaction. Called by Input subsystem.
    void WindowMoved();
    /// Maximize the Window.
    void Maximize();
    /// Minimize the Window.
    void Minimize();
    /// Add a GPU object to keep track of. Called by GPUObject.
    void AddGPUObject(GPUObject* object);
    /// Remove a GPU object. Called by GPUObject.
    void RemoveGPUObject(GPUObject* object);
    /// Reserve a CPU-side scratch buffer.
    void* ReserveScratchBuffer(unsigned size);
    /// Free a CPU-side scratch buffer.
    void FreeScratchBuffer(void* buffer);
    /// Clean up too large scratch buffers.
    void CleanupScratchBuffers();
    /// Clean up shader programs when a shader variation is released or destroyed.
    void CleanupShaderPrograms(ShaderVariation* variation);

    /// Return the API-specific alpha texture format.
    static unsigned GetAlphaFormat();
    /// Return the API-specific luminance texture format.
    static unsigned GetLuminanceFormat();
    /// Return the API-specific luminance alpha texture format.
    static unsigned GetLuminanceAlphaFormat();
    /// Return the API-specific RGB texture format.
    static unsigned GetRGBFormat();
    /// Return the API-specific RGBA texture format.
    static unsigned GetRGBAFormat();
    /// Return the API-specific RGBA 16-bit texture format.
    static unsigned GetRGBA16Format();
    /// Return the API-specific RGBA 16-bit float texture format.
    static unsigned GetRGBAFloat16Format();
    /// Return the API-specific RGBA 32-bit float texture format.
    static unsigned GetRGBAFloat32Format();
    /// Return the API-specific RG 16-bit texture format.
    static unsigned GetRG16Format();
    /// Return the API-specific RG 16-bit float texture format.
    static unsigned GetRGFloat16Format();
    /// Return the API-specific RG 32-bit float texture format.
    static unsigned GetRGFloat32Format();
    /// Return the API-specific single channel 16-bit float texture format.
    static unsigned GetFloat16Format();
    /// Return the API-specific single channel 32-bit float texture format.
    static unsigned GetFloat32Format();
    /// Return the API-specific linear depth texture format.
    static unsigned GetLinearDepthFormat();
    /// Return the API-specific hardware depth-stencil texture format.
    static unsigned GetDepthStencilFormat();
    /// Return the API-specific readable hardware depth format, or 0 if not supported.
    static unsigned GetReadableDepthFormat();
    /// Return the API-specific texture format from a textual description, for example "rgb".
    static unsigned GetFormat(const String& formatName);

    /// Return UV offset required for pixel perfect rendering.
    static const Vector2& GetPixelUVOffset() { return pixelUVOffset; }

    /// Return maximum number of supported bones for skinning.
    static unsigned GetMaxBones() { return 64; }

private:
    /// Set vertex buffer stream frequency.
    void SetStreamFrequency(unsigned index, unsigned frequency);
    /// Reset stream frequencies.
    void ResetStreamFrequencies();
    /// Create the application window.
    bool OpenWindow(int width, int height, bool resizable, bool borderless);
    /// Create the application window icon.
    void CreateWindowIcon();
    /// Adjust the window for new resolution and fullscreen mode.
    void AdjustWindow(int& newWidth, int& newHeight, bool& newFullscreen, bool& newBorderless);
    /// Create the Direct3D interface.
    bool CreateInterface();
    /// Create the Direct3D device.
    bool CreateDevice(unsigned adapter, unsigned deviceType);
    /// Check supported rendering features.
    void CheckFeatureSupport();
    /// Reset the Direct3D device.
    void ResetDevice();
    /// Notify all GPU resources so they can release themselves as needed.
    void OnDeviceLost();
    /// Notify all GPU resources so they can recreate themselves as needed.
    void OnDeviceReset();
    /// Reset cached rendering state.
    void ResetCachedState();
    /// Initialize texture unit mappings.
    void SetTextureUnitMappings();

    /// Mutex for accessing the GPU objects vector from several threads.
    Mutex gpuObjectMutex_;
    /// Implementation.
    GraphicsImpl* impl_;
    /// Window title.
    String windowTitle_;
    /// Window Icon File Name
    Image* windowIcon_;
    /// External window, null if not in use (default.)
    void* externalWindow_;
    /// Window width.
    int width_;
    /// Window height.
    int height_;
    /// Window position.
    IntVector2 position_;
    /// Multisampling mode.
    int multiSample_;
    /// Fullscreen flag.
    bool fullscreen_;
    /// Borderless flag.
    bool borderless_;
    /// Resizable flag.
    bool resizable_;
    /// Vertical sync flag.
    bool vsync_;
    /// Triple buffering flag.
    bool tripleBuffer_;
    /// Flush GPU command buffer flag.
    bool flushGPU_;
    /// sRGB conversion on write flag for the main window.
    bool sRGB_;
    /// Direct3D device lost flag.
    bool deviceLost_;
    /// Flush query issued flag.
    bool queryIssued_;
    /// Light pre-pass rendering support flag.
    bool lightPrepassSupport_;
    /// Deferred rendering support flag.
    bool deferredSupport_;
    /// Hardware shadow map depth compare support flag.
    bool hardwareShadowSupport_;
    /// Instancing support flag.
    bool instancingSupport_;
    /// sRGB conversion on read support flag.
    bool sRGBSupport_;
    /// sRGB conversion on write support flag.
    bool sRGBWriteSupport_;
    /// Number of primitives this frame.
    unsigned numPrimitives_;
    /// Number of batches this frame.
    unsigned numBatches_;
    /// Largest scratch buffer request this frame.
    unsigned maxScratchBufferRequest_;
    /// GPU objects.
    PODVector<GPUObject*> gpuObjects_;
    /// Scratch buffers.
    Vector<ScratchBuffer> scratchBuffers_;
    /// Vertex declarations.
    HashMap<unsigned long long, SharedPtr<VertexDeclaration> > vertexDeclarations_;
    /// Shadow map dummy color texture format.
    unsigned dummyColorFormat_;
    /// Shadow map depth texture format.
    unsigned shadowMapFormat_;
    /// Shadow map 24-bit depth texture format.
    unsigned hiresShadowMapFormat_;
    /// Vertex buffers in use.
    VertexBuffer* vertexBuffers_[MAX_VERTEX_STREAMS];
    /// Stream frequencies by vertex buffer.
    unsigned streamFrequencies_[MAX_VERTEX_STREAMS];
    /// Stream offsets by vertex buffer.
    unsigned streamOffsets_[MAX_VERTEX_STREAMS];
    /// Index buffer in use.
    IndexBuffer* indexBuffer_;
    /// Vertex declaration in use.
    VertexDeclaration* vertexDeclaration_;
    /// Vertex shader in use.
    ShaderVariation* vertexShader_;
    /// Pixel shader in use.
    ShaderVariation* pixelShader_;
    /// Textures in use.
    Texture* textures_[MAX_TEXTURE_UNITS];
    /// Texture unit mappings.
    HashMap<String, TextureUnit> textureUnits_;
    /// Rendertargets in use.
    RenderSurface* renderTargets_[MAX_RENDERTARGETS];
    /// Depth-stencil surface in use.
    RenderSurface* depthStencil_;
    /// Viewport coordinates.
    IntRect viewport_;
    /// Texture anisotropy level.
    unsigned textureAnisotropy_;
    /// Blending mode.
    BlendMode blendMode_;
    /// Color write enable.
    bool colorWrite_;
    /// Hardware culling mode.
    CullMode cullMode_;
    /// Depth constant bias.
    float constantDepthBias_;
    /// Depth slope scaled bias.
    float slopeScaledDepthBias_;
    /// Depth compare mode.
    CompareMode depthTestMode_;
    /// Depth write enable flag.
    bool depthWrite_;
    /// Polygon fill mode.
    FillMode fillMode_;
    /// Scissor test rectangle.
    IntRect scissorRect_;
    /// Scissor test enable flag.
    bool scissorTest_;
    /// Stencil test compare mode.
    CompareMode stencilTestMode_;
    /// Stencil operation on pass.
    StencilOp stencilPass_;
    /// Stencil operation on fail.
    StencilOp stencilFail_;
    /// Stencil operation on depth fail.
    StencilOp stencilZFail_;
    /// Stencil test reference value.
    unsigned stencilRef_;
    /// Stencil compare bitmask.
    unsigned stencilCompareMask_;
    /// Stencil write bitmask.
    unsigned stencilWriteMask_;
    /// Stencil test enable flag.
    bool stencilTest_;
    /// Custom clip plane enable flag.
    bool useClipPlane_;
    /// Default texture filtering mode.
    TextureFilterMode defaultTextureFilterMode_;
    /// Shader programs.
    ShaderProgramMap shaderPrograms_;
    /// Shader program in use.
    ShaderProgram* shaderProgram_;
    /// Remembered shader parameter sources.
    const void* shaderParameterSources_[MAX_SHADER_PARAMETER_GROUPS];
    /// Base directory for shaders.
    String shaderPath_;
    /// File extension for shaders.
    String shaderExtension_;
    /// Last used shader in shader variation query.
    mutable WeakPtr<Shader> lastShader_;
    /// Last used shader name in shader variation query.
    mutable String lastShaderName_;
    /// Shader precache utility.
    SharedPtr<ShaderPrecache> shaderPrecache_;
    /// Allowed screen orientations.
    String orientations_;
    /// Graphics API name.
    String apiName_;

    /// Pixel perfect UV offset.
    static const Vector2 pixelUVOffset;
};

/// Register Graphics library objects.
void URHO3D_API RegisterGraphicsLibrary(Context* context);

}
