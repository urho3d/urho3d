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
#include "Material.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererImpl.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "Texture.h"
#include "XMLFile.h"

#include "DebugNew.h"

int Texture::sQuality = QUALITY_HIGH;

Texture::Texture(Renderer* renderer, const std::string& name) :
    Resource(name),
    GPUObject(renderer),
    mFormat(D3DFMT_UNKNOWN),
    mUsage(0),
    mLevels(0),
    mRequestedLevels(0),
    mWidth(0),
    mHeight(0),
    mDataLost(false),
    mFilterMode(FILTER_DEFAULT)
{
    for (int i = 0; i < MAX_COORDS; ++i)
        mAddressMode[i] = ADDRESS_WRAP;
    for (int i = 0; i < MAX_TEXTURE_QUALITY_LEVELS; ++i)
        mMipsToSkip[i] = MAX_TEXTURE_QUALITY_LEVELS - 1 - i;
}

Texture::~Texture()
{
}

void Texture::setNumLevels(unsigned levels)
{
    if (mUsage & D3DUSAGE_DEPTHSTENCIL)
        mRequestedLevels = 1;
    else
        mRequestedLevels = levels;
}

void Texture::setFilterMode(TextureFilterMode mode)
{
    mFilterMode = mode;
}

void Texture::setAddressMode(TextureCoordinate coord, TextureAddressMode mode)
{
    mAddressMode[coord] = mode;
}

void Texture::setBorderColor(const Color& color)
{
    mBorderColor = color;
}

void Texture::setBackupTexture(Texture* texture)
{
    mBackupTexture = texture;
}

void Texture::clearDataLost()
{
    mDataLost = false;
}

TextureUsage Texture::getUsage() const
{
    if (mUsage & D3DUSAGE_DEPTHSTENCIL)
        return TEXTURE_DEPTHSTENCIL;
    
    if (mUsage & D3DUSAGE_RENDERTARGET)
        return TEXTURE_RENDERTARGET;
    
    if (mPool == D3DPOOL_DEFAULT)
        return TEXTURE_DYNAMIC;
    
    return TEXTURE_STATIC;
}

unsigned Texture::getCompressedD3DFormat(CompressedFormat format)
{
    switch (format)
    {
    case CF_DXT1:
        return D3DFMT_DXT1;
        
    case CF_DXT3:
        return D3DFMT_DXT3;
        
    case CF_DXT5:
        return D3DFMT_DXT5;
    }
    
    return D3DFMT_UNKNOWN;
}

void Texture::loadParameters(ResourceCache* cache)
{
    if (!cache)
        return;
    
    std::string texPath, texName, texExt;
    splitPath(getName(), texPath, texName, texExt);
    std::string xmlName = texPath + texName + ".xml";
    
    if (cache->exists(xmlName))
    {
        XMLFile* xml = cache->getResource<XMLFile>(xmlName);
        loadParameters(*xml);
    }
}

void Texture::loadParameters(XMLFile& xml)
{
    XMLElement rootElem = xml.getRootElement();
    XMLElement paramElem = rootElem.getChildElement("", false);
    
    while (paramElem.notNull())
    {
        std::string name = paramElem.getName();
        
        if (name == "address")
        {
            std::string coord = paramElem.getStringLower("coord");
            if (coord.length() >= 1)
            {
                TextureCoordinate coordIndex = (TextureCoordinate)(coord[0] - 'u');
                std::string mode = paramElem.getStringLower("mode");
                if (mode == "wrap")
                    setAddressMode(coordIndex, ADDRESS_WRAP);
                if (mode == "mirror")
                    setAddressMode(coordIndex, ADDRESS_MIRROR);
                if (mode == "clamp")
                    setAddressMode(coordIndex, ADDRESS_CLAMP);
                if (mode == "border")
                    setAddressMode(coordIndex, ADDRESS_BORDER);
            }
        }
        
        if (name == "border")
            setBorderColor(paramElem.getColor("color"));
        
        if (name == "filter")
        {
            std::string mode = paramElem.getStringLower("mode");
            if (mode == "nearest")
                setFilterMode(FILTER_NEAREST);
            if (mode == "bilinear")
                setFilterMode(FILTER_BILINEAR);
            if (mode == "trilinear")
                setFilterMode(FILTER_TRILINEAR);
            if (mode == "anisotropic")
                setFilterMode(FILTER_ANISOTROPIC);
        }
        
        if (name == "mipmap")
            setNumLevels(paramElem.getBool("enable") ? 0 : 1);
        
        if (name == "quality")
        {
            if (paramElem.hasAttribute("low"))
                mMipsToSkip[QUALITY_LOW] = max(paramElem.getInt("low"), 0);
            if (paramElem.hasAttribute("med"))
                mMipsToSkip[QUALITY_MEDIUM] = max(paramElem.getInt("med"), 0);
            if (paramElem.hasAttribute("medium"))
                mMipsToSkip[QUALITY_MEDIUM] = max(paramElem.getInt("medium"), 0);
            if (paramElem.hasAttribute("high"))
                mMipsToSkip[QUALITY_HIGH] = max(paramElem.getInt("high"), 0);
            
            // Make sure a higher quality level does not actually skip more mips
            for (int i = 1; i < MAX_TEXTURE_QUALITY_LEVELS; ++i)
            {
                if (mMipsToSkip[i] > mMipsToSkip[i - 1])
                    mMipsToSkip[i] = mMipsToSkip[i - 1];
            }
        }
        
        paramElem = paramElem.getNextElement();
    }
}

void Texture::setQuality(int quality)
{
    sQuality = clamp(quality, 0, MAX_TEXTURE_QUALITY_LEVELS - 1);
}

void Texture::checkTextureBudget(ShortStringHash type, ResourceCache* cache)
{
    if (!cache)
        return;
    
    unsigned textureBudget = cache->getMemoryBudget(type);
    unsigned textureUse = cache->getMemoryUse(type);
    if (!textureBudget)
        return;
    
    // If textures are over the budget, they likely can not be freed directly as materials still refer to them.
    // Therefore free unused materials first
    if (textureUse > textureBudget)
        cache->releaseResources(Material::getTypeStatic());
}
