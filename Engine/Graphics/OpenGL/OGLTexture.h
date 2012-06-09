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

#include "ArrayPtr.h"
#include "Color.h"
#include "GPUObject.h"
#include "GraphicsDefs.h"
#include "Image.h"
#include "Resource.h"

static const int MAX_TEXTURE_QUALITY_LEVELS = 3;

class XMLElement;
class XMLFile;

/// Base class for texture resources.
class Texture : public Resource, public GPUObject
{
public:
    /// Construct.
    Texture(Context* context);
    /// Destruct.
    virtual ~Texture();
    
    /// Set number of requested mipmap levels. Needs to be called before setting size.
    void SetNumLevels(unsigned levels);
    /// Set filtering mode.
    void SetFilterMode(TextureFilterMode filter);
    /// Set addressing mode by texture coordinate.
    void SetAddressMode(TextureCoordinate coord, TextureAddressMode address);
    /// Set shadow compare mode, OpenGL only.
    void SetShadowCompare(bool enable);
    /// Set border color for border addressing mode.
    void SetBorderColor(const Color& color);
    /// Set backup texture to use when rendering to this texture.
    void SetBackupTexture(Texture* texture);
    /// Dirty the parameters.
    void SetParametersDirty();
    /// Clear data lost flag. No-op on OpenGL.
    void ClearDataLost();
    /// Update changed parameters to OpenGL. Called by Graphics when binding the texture.
    void UpdateParameters();
    
    /// Return texture's OpenGL target.
    unsigned GetTarget() const { return target_; }
    /// Return texture format.
    unsigned GetFormat() const { return format_; }
    /// Return whether the texture format is compressed.
    bool IsCompressed() const;
    /// Return number of mipmap levels.
    unsigned GetLevels() const { return levels_; }
    /// Return width.
    int GetWidth() const { return width_; }
    /// Return height.
    int GetHeight() const { return height_; }
    /// Return whether data is lost due to context loss.
    bool IsDataLost() const { return dataLost_; }
    /// Return whether parameters are dirty.
    bool GetParametersDirty() const { return parametersDirty_; }
    /// Return filtering mode.
    TextureFilterMode GetFilterMode() const { return filterMode_; }
    /// Return addressing mode by texture coordinate.
    TextureAddressMode GetAddressMode(TextureCoordinate coord) const { return addressMode_[coord]; }
    /// Return whether shadow compare is enabled, OpenGL only.
    bool GetShadowCompare() const { return shadowCompare_; }
     /// Return border color.
    const Color& GetBorderColor() const { return borderColor_; }
    /// Return backup texture.
    Texture* GetBackupTexture() const { return backupTexture_; }
    /// Return mip level width, or 0 if level does not exist.
    int GetLevelWidth(unsigned level) const;
    /// Return mip level width, or 0 if level does not exist.
    int GetLevelHeight(unsigned level) const;
    /// Return texture usage type.
    TextureUsage GetUsage() const;
    /// Return data size in bytes for a rectangular region.
    unsigned GetDataSize(int width, int height) const;
    /// Return data size in bytes for a pixel or block row.
    unsigned GetRowDataSize(int width) const;
    /// Return API-specific compressed texture format.
    static unsigned GetDXTFormat(CompressedFormat format);
    /// Return the non-internal texture format corresponding to an OpenGL internal format.
    static unsigned GetExternalFormat(unsigned format);
    /// Return the data type corresponding to an OpenGL internal format.
    static unsigned GetDataType(unsigned format);
    
    /// Load parameters.
    void LoadParameters();
    /// Load parameters from an XML file.
    void LoadParameters(XMLFile* xml);
    /// Load parameters from an XML element.
    void LoadParameters(const XMLElement& elem);
    
protected:
    /// Check whether texture memory budget has been exceeded. Free unused materials in that case to release the texture references.
    void CheckTextureBudget(ShortStringHash type);
    
    /// OpenGL target.
    unsigned target_;
    /// Texture format.
    unsigned format_;
    /// Current mipmap levels.
    unsigned levels_;
    /// Requested mipmap levels.
    unsigned requestedLevels_;
    /// Texture width.
    int width_;
    /// Texture height.
    int height_;
    /// Dynamic flag.
    bool dynamic_;
    /// Shadow compare mode, OpenGL only.
    bool shadowCompare_;
    /// Parameters dirty flag.
    bool parametersDirty_;
    /// Data lost flag.
    bool dataLost_;
    /// Filtering mode.
    TextureFilterMode filterMode_;
    /// Addressing mode.
    TextureAddressMode addressMode_[MAX_COORDS];
    /// Mipmaps to skip when loading.
    unsigned mipsToSkip_[MAX_TEXTURE_QUALITY_LEVELS];
    /// Border color.
    Color borderColor_;
    /// Backup texture.
    SharedPtr<Texture> backupTexture_;
};
