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

#include "../../Precompiled.h"

#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/RenderSurface.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"
#include "../../Resource/XMLFile.h"

#include "../../DebugNew.h"

namespace Urho3D
{

static GLenum glWrapModes[] =
{
    GL_REPEAT,
    GL_MIRRORED_REPEAT,
    GL_CLAMP_TO_EDGE,
#ifndef GL_ES_VERSION_2_0
    GL_CLAMP
#else
    GL_CLAMP_TO_EDGE
#endif
};

#ifndef GL_ES_VERSION_2_0
static GLenum gl3WrapModes[] =
{
    GL_REPEAT,
    GL_MIRRORED_REPEAT,
    GL_CLAMP_TO_EDGE,
    GL_CLAMP_TO_BORDER
};
#endif

static const char* addressModeNames[] =
{
    "wrap",
    "mirror",
    "clamp",
    "border",
    0
};

static const char* filterModeNames[] =
{
    "nearest",
    "bilinear",
    "trilinear",
    "anisotropic",
    "default",
    0
};

static GLenum GetWrapMode(TextureAddressMode mode)
{
#ifndef GL_ES_VERSION_2_0
    return Graphics::GetGL3Support() ? gl3WrapModes[mode] : glWrapModes[mode];
#else
    return glWrapModes[mode];
#endif
}

Texture::Texture(Context* context) :
    Resource(context),
    GPUObject(GetSubsystem<Graphics>()),
    usage_(TEXTURE_STATIC),
    format_(0),
    levels_(0),
    requestedLevels_(0),
    width_(0),
    height_(0),
    depth_(0),
    shadowCompare_(false),
    parametersDirty_(true),
    filterMode_(FILTER_DEFAULT),
    sRGB_(false)
{
    for (int i = 0; i < MAX_COORDS; ++i)
        addressMode_[i] = ADDRESS_WRAP;
    for (int i = 0; i < MAX_TEXTURE_QUALITY_LEVELS; ++i)
        mipsToSkip_[i] = (unsigned)(MAX_TEXTURE_QUALITY_LEVELS - 1 - i);
}

Texture::~Texture()
{
}

void Texture::SetNumLevels(unsigned levels)
{
    requestedLevels_ = levels;
}

void Texture::SetFilterMode(TextureFilterMode mode)
{
    filterMode_ = mode;
    parametersDirty_ = true;
}

void Texture::SetAddressMode(TextureCoordinate coord, TextureAddressMode mode)
{
    addressMode_[coord] = mode;
    parametersDirty_ = true;
}

void Texture::SetShadowCompare(bool enable)
{
    shadowCompare_ = enable;
    parametersDirty_ = true;
}

void Texture::SetBorderColor(const Color& color)
{
    borderColor_ = color;
    parametersDirty_ = true;
}

void Texture::SetSRGB(bool enable)
{
    if (graphics_)
        enable &= graphics_->GetSRGBSupport();

    if (enable != sRGB_)
    {
        sRGB_ = enable;
        // If texture had already been created, must recreate it to set the sRGB texture format
        if (object_)
            Create();

        // If texture in use in the framebuffer, mark it dirty
        if (graphics_ && graphics_->GetRenderTarget(0) && graphics_->GetRenderTarget(0)->GetParentTexture() == this)
            graphics_->MarkFBODirty();
    }
}

void Texture::SetBackupTexture(Texture* texture)
{
    backupTexture_ = texture;
}

void Texture::SetMipsToSkip(int quality, int toSkip)
{
    if (quality >= QUALITY_LOW && quality < MAX_TEXTURE_QUALITY_LEVELS)
    {
        mipsToSkip_[quality] = (unsigned)toSkip;

        // Make sure a higher quality level does not actually skip more mips
        for (int i = 1; i < MAX_TEXTURE_QUALITY_LEVELS; ++i)
        {
            if (mipsToSkip_[i] > mipsToSkip_[i - 1])
                mipsToSkip_[i] = mipsToSkip_[i - 1];
        }
    }
}

void Texture::SetParametersDirty()
{
    parametersDirty_ = true;
}

void Texture::UpdateParameters()
{
    if (!object_ || !graphics_)
        return;

    // Wrapping
    glTexParameteri(target_, GL_TEXTURE_WRAP_S, GetWrapMode(addressMode_[COORD_U]));
    glTexParameteri(target_, GL_TEXTURE_WRAP_T, GetWrapMode(addressMode_[COORD_V]));
#ifndef GL_ES_VERSION_2_0
    glTexParameteri(target_, GL_TEXTURE_WRAP_R, GetWrapMode(addressMode_[COORD_W]));
#endif

    TextureFilterMode filterMode = filterMode_;
    if (filterMode == FILTER_DEFAULT)
        filterMode = graphics_->GetDefaultTextureFilterMode();

    // Filtering
    switch (filterMode)
    {
    case FILTER_NEAREST:
        glTexParameteri(target_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(target_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;

    case FILTER_BILINEAR:
        if (levels_ < 2)
            glTexParameteri(target_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        else
            glTexParameteri(target_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(target_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;

    case FILTER_ANISOTROPIC:
    case FILTER_TRILINEAR:
        if (levels_ < 2)
            glTexParameteri(target_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        else
            glTexParameteri(target_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(target_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;

    default:
        break;
    }

#ifndef GL_ES_VERSION_2_0
    // Anisotropy
    if (graphics_->GetAnisotropySupport())
    {
        glTexParameterf(target_, GL_TEXTURE_MAX_ANISOTROPY_EXT,
            filterMode == FILTER_ANISOTROPIC ? (float)graphics_->GetTextureAnisotropy() : 1.0f);
    }

    // Shadow compare
    if (shadowCompare_)
    {
        glTexParameteri(target_, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
        glTexParameteri(target_, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    }
    else
        glTexParameteri(target_, GL_TEXTURE_COMPARE_MODE, GL_NONE);

    glTexParameterfv(target_, GL_TEXTURE_BORDER_COLOR, borderColor_.Data());
#endif

    parametersDirty_ = false;
}

int Texture::GetMipsToSkip(int quality) const
{
    return (quality >= QUALITY_LOW && quality < MAX_TEXTURE_QUALITY_LEVELS) ? mipsToSkip_[quality] : 0;
}

bool Texture::IsCompressed() const
{
    return format_ == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT || format_ == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT ||
           format_ == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT || format_ == GL_ETC1_RGB8_OES ||
           format_ == COMPRESSED_RGB_PVRTC_4BPPV1_IMG || format_ == COMPRESSED_RGBA_PVRTC_4BPPV1_IMG ||
           format_ == COMPRESSED_RGB_PVRTC_2BPPV1_IMG || format_ == COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
}

int Texture::GetLevelWidth(unsigned level) const
{
    if (level > levels_)
        return 0;
    return Max(width_ >> level, 1);
}

int Texture::GetLevelHeight(unsigned level) const
{
    if (level > levels_)
        return 0;
    return Max(height_ >> level, 1);
}

int Texture::GetLevelDepth(unsigned level) const
{
    if (level > levels_)
        return 0;
    return Max(depth_ >> level, 1);
}

unsigned Texture::GetDataSize(int width, int height) const
{
    if (IsCompressed())
    {
        if (format_ == COMPRESSED_RGB_PVRTC_4BPPV1_IMG || format_ == COMPRESSED_RGBA_PVRTC_4BPPV1_IMG)
            return (unsigned)((Max(width, 8) * Max(height, 8) * 4 + 7) >> 3);
        else if (format_ == COMPRESSED_RGB_PVRTC_2BPPV1_IMG || format_ == COMPRESSED_RGBA_PVRTC_2BPPV1_IMG)
            return (unsigned)((Max(width, 16) * Max(height, 8) * 2 + 7) >> 3);
        else
            return GetRowDataSize(width) * ((height + 3) >> 2);
    }
    else
        return GetRowDataSize(width) * height;
}

unsigned Texture::GetDataSize(int width, int height, int depth) const
{
    return depth * GetDataSize(width, height);
}

unsigned Texture::GetRowDataSize(int width) const
{
    switch (format_)
    {
    case GL_ALPHA:
    case GL_LUMINANCE:
        return (unsigned)width;

    case GL_LUMINANCE_ALPHA:
        return (unsigned)(width * 2);

    case GL_RGB:
        return (unsigned)(width * 3);

    case GL_RGBA:
#ifndef GL_ES_VERSION_2_0
    case GL_DEPTH24_STENCIL8_EXT:
    case GL_RG16:
    case GL_RG16F:
    case GL_R32F:
#endif
        return (unsigned)(width * 4);

#ifndef GL_ES_VERSION_2_0
    case GL_R8:
        return (unsigned)width;

    case GL_RG8:
    case GL_R16F:
        return (unsigned)(width * 2);

    case GL_RGBA16:
    case GL_RGBA16F_ARB:
        return (unsigned)(width * 8);

    case GL_RGBA32F_ARB:
        return (unsigned)(width * 16);
#endif

    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
        return (unsigned)(((width + 3) >> 2) * 8);

    case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
        return (unsigned)(((width + 3) >> 2) * 16);

    case GL_ETC1_RGB8_OES:
        return (unsigned)(((width + 3) >> 2) * 8);

    case COMPRESSED_RGB_PVRTC_4BPPV1_IMG:
    case COMPRESSED_RGBA_PVRTC_4BPPV1_IMG:
        return (unsigned)((width * 4 + 7) >> 3);

    case COMPRESSED_RGB_PVRTC_2BPPV1_IMG:
    case COMPRESSED_RGBA_PVRTC_2BPPV1_IMG:
        return (unsigned)((width * 2 + 7) >> 3);

    default:
        return 0;
    }
}

unsigned Texture::GetComponents() const
{
    if (!width_ || IsCompressed())
        return 0;
    else
        return GetRowDataSize(width_) / width_;
}

unsigned Texture::GetExternalFormat(unsigned format)
{
#ifndef GL_ES_VERSION_2_0
    if (format == GL_DEPTH_COMPONENT16 || format == GL_DEPTH_COMPONENT24 || format == GL_DEPTH_COMPONENT32)
        return GL_DEPTH_COMPONENT;
    else if (format == GL_DEPTH24_STENCIL8_EXT)
        return GL_DEPTH_STENCIL_EXT;
    else if (format == GL_SLUMINANCE_EXT)
        return GL_LUMINANCE;
    else if (format == GL_SLUMINANCE_ALPHA_EXT)
        return GL_LUMINANCE_ALPHA;
    else if (format == GL_R8 || format == GL_R16F || format == GL_R32F)
        return GL_RED;
    else if (format == GL_RG8 || format == GL_RG16 || format == GL_RG16F || format == GL_RG32F)
        return GL_RG;
    else if (format == GL_RGBA16 || format == GL_RGBA16F_ARB || format == GL_RGBA32F_ARB || format == GL_SRGB_ALPHA_EXT)
        return GL_RGBA;
    else if (format == GL_SRGB_EXT)
        return GL_RGB;
    else
        return format;
#else
    return format;
#endif
}

unsigned Texture::GetDataType(unsigned format)
{
#ifndef GL_ES_VERSION_2_0
    if (format == GL_DEPTH24_STENCIL8_EXT)
        return GL_UNSIGNED_INT_24_8_EXT;
    else if (format == GL_RG16 || format == GL_RGBA16)
        return GL_UNSIGNED_SHORT;
    else if (format == GL_RGBA32F_ARB || format == GL_RG32F || format == GL_R32F)
        return GL_FLOAT;
    else if (format == GL_RGBA16F_ARB || format == GL_RG16F || format == GL_R16F)
        return GL_HALF_FLOAT_ARB;
    else
        return GL_UNSIGNED_BYTE;
#else
    if (format == GL_DEPTH_COMPONENT || format == GL_DEPTH_COMPONENT24_OES)
        return GL_UNSIGNED_INT;
    else if (format == GL_DEPTH_COMPONENT16)
        return GL_UNSIGNED_SHORT;
    else
        return GL_UNSIGNED_BYTE;
#endif
}

void Texture::SetParameters(XMLFile* file)
{
    if (!file)
        return;

    XMLElement rootElem = file->GetRoot();
    SetParameters(rootElem);
}

void Texture::SetParameters(const XMLElement& elem)
{
    XMLElement paramElem = elem.GetChild();
    while (paramElem)
    {
        String name = paramElem.GetName();

        if (name == "address")
        {
            String coord = paramElem.GetAttributeLower("coord");
            if (coord.Length() >= 1)
            {
                TextureCoordinate coordIndex = (TextureCoordinate)(coord[0] - 'u');
                String mode = paramElem.GetAttributeLower("mode");
                SetAddressMode(coordIndex, (TextureAddressMode)GetStringListIndex(mode.CString(), addressModeNames, ADDRESS_WRAP));
            }
        }

        if (name == "border")
            SetBorderColor(paramElem.GetColor("color"));

        if (name == "filter")
        {
            String mode = paramElem.GetAttributeLower("mode");
            SetFilterMode((TextureFilterMode)GetStringListIndex(mode.CString(), filterModeNames, FILTER_DEFAULT));
        }

        if (name == "mipmap")
            SetNumLevels(paramElem.GetBool("enable") ? 0 : 1);

        if (name == "quality")
        {
            if (paramElem.HasAttribute("low"))
                SetMipsToSkip(QUALITY_LOW, paramElem.GetInt("low"));
            if (paramElem.HasAttribute("med"))
                SetMipsToSkip(QUALITY_MEDIUM, paramElem.GetInt("med"));
            if (paramElem.HasAttribute("medium"))
                SetMipsToSkip(QUALITY_MEDIUM, paramElem.GetInt("medium"));
            if (paramElem.HasAttribute("high"))
                SetMipsToSkip(QUALITY_HIGH, paramElem.GetInt("high"));
        }

        if (name == "srgb")
            SetSRGB(paramElem.GetBool("enable"));

        paramElem = paramElem.GetNext();
    }
}

unsigned Texture::GetSRGBFormat(unsigned format)
{
#ifndef GL_ES_VERSION_2_0
    if (!graphics_ || !graphics_->GetSRGBSupport())
        return format;

    switch (format)
    {
    case GL_RGB:
        return GL_SRGB_EXT;
    case GL_RGBA:
        return GL_SRGB_ALPHA_EXT;
    case GL_LUMINANCE:
        return GL_SLUMINANCE_EXT;
    case GL_LUMINANCE_ALPHA:
        return GL_SLUMINANCE_ALPHA_EXT;
    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
        return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
    case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
        return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
        return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;
    default:
        return format;
    }
#else
    return format;
#endif
}

void Texture::CheckTextureBudget(StringHash type)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    unsigned long long textureBudget = cache->GetMemoryBudget(type);
    unsigned long long textureUse = cache->GetMemoryUse(type);
    if (!textureBudget)
        return;

    // If textures are over the budget, they likely can not be freed directly as materials still refer to them.
    // Therefore free unused materials first
    if (textureUse > textureBudget)
        cache->ReleaseResources(Material::GetTypeStatic());
}

}
