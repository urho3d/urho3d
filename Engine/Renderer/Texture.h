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

#ifndef RENDERER_TEXTURE_H
#define RENDERER_TEXTURE_H

#include "Color.h"
#include "GPUObject.h"
#include "Image.h"
#include "RendererDefs.h"
#include "Resource.h"

static const int MAX_TEXTURE_QUALITY_LEVELS = 3;

class XMLFile;

//! Base class for texture resources
class Texture : public Resource, public GPUObject
{
public:
    //! Construct with renderer subsystem pointer and name
    Texture(Renderer* renderer, const std::string& name);
    //! Destruct
    virtual ~Texture();
    
    //! Set number of requested mipmap levels. Needs to be called before setting size
    void setNumLevels(unsigned levels);
    //! Set filtering mode
    void setFilterMode(TextureFilterMode filter);
    //! Set addressing mode by texture coordinate
    void setAddressMode(TextureCoordinate coord, TextureAddressMode address);
    //! Set border color for border addressing mode
    void setBorderColor(const Color& color);
    //! Set backup texture to use when rendering to this texture
    void setBackupTexture(Texture* texture);
    //! Clear default pool data lost flag
    void clearDataLost();
    
    //! Return texture usage type
    TextureUsage getUsage() const;
    //! Return texture format
    unsigned getFormat() const { return mFormat; }
    //! Return number of mipmap levels
    unsigned getLevels() const { return mLevels; }
    //! Return width
    int getWidth() const { return mWidth; }
    //! Return height
    int getHeight() const { return mHeight; }
    //! Return whether default pool data is lost
    bool isDataLost() const { return mDataLost; }
    //! Return filtering mode
    TextureFilterMode getFilterMode() const { return mFilterMode; }
    //! Return addressing mode by texture coordinate
    TextureAddressMode getAddressMode(TextureCoordinate coord) const { return mAddressMode[coord]; }
    //! Return border color
    const Color& getBorderColor() const { return mBorderColor; }
    //! Return backup texture
    Texture* getBackupTexture() const { return mBackupTexture; }
    //! Return compressed format
    static unsigned getCompressedD3DFormat(CompressedFormat format);
    //! Set global texture quality level
    static void setQuality(int quality);
    //! Return global texture quality level
    static int getQuality() { return sQuality; }
    
protected:
    //! Load parameters
    void loadParameters(ResourceCache* cache);
    //! Load parameters from an XML file
    void loadParameters(XMLFile* xml);
    //! Check whether texture memory budget has been exceeded. Free unused materials in that case to release the texture references
    void checkTextureBudget(ShortStringHash type, ResourceCache* cache);
    
    //! Texture format
    unsigned mFormat;
    //! Memory pool
    unsigned mPool;
    //! Texture usage type
    unsigned mUsage;
    //! Current mipmap levels
    unsigned mLevels;
    //! Requested mipmap levels
    unsigned mRequestedLevels;
    //! Texture width
    int mWidth;
    //! Texture height
    int mHeight;
    //! Default pool data lost flag
    bool mDataLost;
    //! Filtering mode
    TextureFilterMode mFilterMode;
    //! Addressing mode
    TextureAddressMode mAddressMode[MAX_COORDS];
    //! Mipmaps to skip when loading
    unsigned mMipsToSkip[MAX_TEXTURE_QUALITY_LEVELS];
    //! Border color
    Color mBorderColor;
    //! Backup texture
    SharedPtr<Texture> mBackupTexture;
    
    //! Global texture quality setting
    static int sQuality;
};

#endif // RENDERER_TEXTURE_H
