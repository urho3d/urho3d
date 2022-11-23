// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../GraphicsAPI/GPUObject.h"
#include "../GraphicsAPI/GraphicsDefs.h"
#include "../Math/Color.h"
#include "../Resource/Resource.h"

namespace Urho3D
{

static const int MAX_TEXTURE_QUALITY_LEVELS = 3;

class XMLElement;
class XMLFile;

/// Base class for texture resources.
class URHO3D_API Texture : public ResourceWithMetadata, public GPUObject
{
    URHO3D_OBJECT(Texture, ResourceWithMetadata);

public:
    /// Construct.
    explicit Texture(Context* context);
    /// Destruct.
    ~Texture() override;

    /// Set number of requested mip levels. Needs to be called before setting size.
    /** The default value (0) allocates as many mip levels as necessary to reach 1x1 size. Set value 1 to disable mipmapping.
        Note that rendertargets need to regenerate mips dynamically after rendering, which may cost performance. Screen buffers
        and shadow maps allocated by Renderer will have mipmaps disabled.
     */
    void SetNumLevels(unsigned levels);
    /// Set filtering mode.
    /// @property
    void SetFilterMode(TextureFilterMode mode);
    /// Set addressing mode by texture coordinate.
    /// @property
    void SetAddressMode(TextureCoordinate coord, TextureAddressMode mode);
    /// Set texture max. anisotropy level. No effect if not using anisotropic filtering. Value 0 (default) uses the default setting from Renderer.
    /// @property
    void SetAnisotropy(unsigned level);
    /// Set shadow compare mode. Not used on Direct3D9.
    void SetShadowCompare(bool enable);
    /// Set border color for border addressing mode.
    /// @property
    void SetBorderColor(const Color& color);
    /// Set sRGB sampling and writing mode.
    /// @property
    void SetSRGB(bool enable);
    /// Set backup texture to use when rendering to this texture.
    /// @property
    void SetBackupTexture(Texture* texture);
    /// Set mip levels to skip on a quality setting when loading. Ensures higher quality levels do not skip more.
    /// @property
    void SetMipsToSkip(MaterialQuality quality, int toSkip);

    /// Return API-specific texture format.
    /// @property
    unsigned GetFormat() const { return format_; }

    /// Return whether the texture format is compressed.
    /// @property
    bool IsCompressed() const;

    /// Return number of mip levels.
    /// @property
    unsigned GetLevels() const { return levels_; }

    /// Return width.
    /// @property
    int GetWidth() const { return width_; }

    /// Return height.
    /// @property
    int GetHeight() const { return height_; }

    /// Return depth.
    int GetDepth() const { return depth_; }

    /// Return filtering mode.
    /// @property
    TextureFilterMode GetFilterMode() const { return filterMode_; }

    /// Return addressing mode by texture coordinate.
    /// @property
    TextureAddressMode GetAddressMode(TextureCoordinate coord) const { return addressModes_[coord]; }

    /// Return texture max. anisotropy level. Value 0 means to use the default value from Renderer.
    /// @property
    unsigned GetAnisotropy() const { return anisotropy_; }

    /// Return whether shadow compare is enabled. Not used on Direct3D9.
    bool GetShadowCompare() const { return shadowCompare_; }

    /// Return border color.
    /// @property
    const Color& GetBorderColor() const { return borderColor_; }

    /// Return whether is using sRGB sampling and writing.
    /// @property
    bool GetSRGB() const { return sRGB_; }

    /// Return texture multisampling level (1 = no multisampling).
    /// @property
    int GetMultiSample() const { return multiSample_; }

    /// Return texture multisampling autoresolve mode. When true, the texture is resolved before being sampled on SetTexture(). When false, the texture will not be resolved and must be read as individual samples in the shader.
    /// @property
    bool GetAutoResolve() const { return autoResolve_; }

    /// Return whether multisampled texture needs resolve.
    /// @property
    bool IsResolveDirty() const { return resolveDirty_; }

    /// Return whether rendertarget mipmap levels need regenration.
    /// @property
    bool GetLevelsDirty() const { return levelsDirty_; }

    /// Return backup texture.
    /// @property
    Texture* GetBackupTexture() const { return backupTexture_; }

    /// Return mip levels to skip on a quality setting when loading.
    /// @property
    int GetMipsToSkip(MaterialQuality quality) const;
    /// Return mip level width, or 0 if level does not exist.
    /// @property
    int GetLevelWidth(unsigned level) const;
    /// Return mip level width, or 0 if level does not exist.
    /// @property
    int GetLevelHeight(unsigned level) const;
    /// Return mip level depth, or 0 if level does not exist.
    int GetLevelDepth(unsigned level) const;

    /// Return texture usage type.
    /// @property
    TextureUsage GetUsage() const { return usage_; }

    /// Return data size in bytes for a rectangular region.
    unsigned GetDataSize(int width, int height) const;
    /// Return data size in bytes for a volume region.
    unsigned GetDataSize(int width, int height, int depth) const;
    /// Return data size in bytes for a pixel or block row.
    unsigned GetRowDataSize(int width) const;
    /// Return number of image components required to receive pixel data from GetData(), or 0 for compressed images.
    /// @property
    unsigned GetComponents() const;

    /// Return whether the parameters are dirty.
    bool GetParametersDirty() const;

    /// Set additional parameters from an XML file.
    void SetParameters(XMLFile* file);
    /// Set additional parameters from an XML element.
    void SetParameters(const XMLElement& element);
    /// Mark parameters dirty. Called by Graphics.
    void SetParametersDirty();
    /// Update dirty parameters to the texture object. Called by Graphics when assigning the texture.
    void UpdateParameters();

    /// Return shader resource view. Only used on Direct3D11.
    void* GetShaderResourceView() const { return shaderResourceView_; }

    /// Return sampler state object. Only used on Direct3D11.
    void* GetSampler() const { return sampler_; }

    /// Return resolve texture. Only used on Direct3D11.
    void* GetResolveTexture() const { return resolveTexture_; }

    /// Return texture's target. Only used on OpenGL.
    unsigned GetTarget() const { return target_; }

    /// Set or clear the need resolve flag. Called internally by Graphics.
    void SetResolveDirty(bool enable) { resolveDirty_ = enable; }

    /// Set the mipmap levels dirty flag. Called internally by Graphics.
    void SetLevelsDirty();
    /// Regenerate mipmap levels for a rendertarget after rendering and before sampling. Called internally by Graphics. No-op on Direct3D9. On OpenGL the texture must have been bound to work properly.
    void RegenerateLevels();

    /// Check maximum allowed mip levels for a specific texture size.
    static unsigned CheckMaxLevels(int width, int height, unsigned requestedLevels);
    /// Check maximum allowed mip levels for a specific 3D texture size.
    static unsigned CheckMaxLevels(int width, int height, int depth, unsigned requestedLevels);

#ifdef URHO3D_OPENGL
    /// Return the data type corresponding to an OpenGL internal format.
    static unsigned GetDataType_OGL(unsigned format);
#endif

protected:
#ifdef URHO3D_OPENGL
    /// Convert format to sRGB. Not used on Direct3D9.
    unsigned GetSRGBFormat_OGL(unsigned format);

    /// Return the non-internal texture format corresponding to an OpenGL internal format.
    static unsigned GetExternalFormat_OGL(unsigned format);
#endif // def URHO3D_OPENGL

#ifdef URHO3D_D3D11
    /// Convert format to sRGB. Not used on Direct3D9.
    unsigned GetSRGBFormat_D3D11(unsigned format);

    /// Return the shader resource view format corresponding to a texture format. Handles conversion of typeless depth texture formats. Only used on Direct3D11.
    static unsigned GetSRVFormat_D3D11(unsigned format);

    /// Return the depth-stencil view format corresponding to a texture format. Handles conversion of typeless depth texture formats. Only used on Direct3D11.
    static unsigned GetDSVFormat_D3D11(unsigned format);
#endif // def URHO3D_D3D11

    // For proxy functions

#ifdef URHO3D_OPENGL
    void SetSRGB_OGL(bool enable);
    void UpdateParameters_OGL();
    bool GetParametersDirty_OGL() const;
    bool IsCompressed_OGL() const;
    unsigned GetRowDataSize_OGL(int width) const;
    void RegenerateLevels_OGL();
#endif // def URHO3D_OPENGL

#ifdef URHO3D_D3D9
    void SetSRGB_D3D9(bool enable);
    void UpdateParameters_D3D9();
    bool GetParametersDirty_D3D9() const;
    bool IsCompressed_D3D9() const;
    unsigned GetRowDataSize_D3D9(int width) const;
    void RegenerateLevels_D3D9();
#endif // def URHO3D_D3D9

#ifdef URHO3D_D3D11
    void SetSRGB_D3D11(bool enable);
    void UpdateParameters_D3D11();
    bool GetParametersDirty_D3D11() const;
    bool IsCompressed_D3D11() const;
    unsigned GetRowDataSize_D3D11(int width) const;
    void RegenerateLevels_D3D11();
#endif // def URHO3D_D3D11

    /// Check whether texture memory budget has been exceeded. Free unused materials in that case to release the texture references.
    void CheckTextureBudget(StringHash type);
    /// Create the GPU texture. Implemented in subclasses.
    virtual bool Create() { return true; }

    /// OpenGL target.
    unsigned target_{};

    /// Direct3D11 shader resource view.
    void* shaderResourceView_{};
    /// Direct3D11 sampler state object.
    void* sampler_{};
    /// Direct3D11 resolve texture object when multisample with autoresolve is used.
    void* resolveTexture_{};

    /// Texture format.
    unsigned format_{};
    /// Texture usage type.
    TextureUsage usage_{TEXTURE_STATIC};
    /// Current mip levels.
    unsigned levels_{};
    /// Requested mip levels.
    unsigned requestedLevels_{};
    /// Texture width.
    int width_{};
    /// Texture height.
    int height_{};
    /// Texture depth.
    int depth_{};
    /// Shadow compare mode.
    bool shadowCompare_{};
    /// Filtering mode.
    TextureFilterMode filterMode_{FILTER_DEFAULT};
    /// Addressing mode.
    TextureAddressMode addressModes_[MAX_COORDS]{ADDRESS_WRAP, ADDRESS_WRAP, ADDRESS_WRAP};
    /// Texture anisotropy level.
    unsigned anisotropy_{};
    /// Mip levels to skip when loading per texture quality setting.
    unsigned mipsToSkip_[MAX_TEXTURE_QUALITY_LEVELS]{2, 1, 0};
    /// Border color.
    Color borderColor_;
    /// Multisampling level.
    int multiSample_{1};
    /// sRGB sampling and writing mode flag.
    bool sRGB_{};
    /// Parameters dirty flag.
    bool parametersDirty_{true};
    /// Multisampling autoresolve flag.
    bool autoResolve_{};
    /// Multisampling resolve needed -flag.
    bool resolveDirty_{};
    /// Mipmap levels regeneration needed -flag.
    bool levelsDirty_{};
    /// Backup texture.
    SharedPtr<Texture> backupTexture_;
};

}
