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
#include "Deserializer.h"
#include "Font.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererImpl.h"
#include "Texture2D.h"

#include <stb_truetype.h>
#include <windows.h>

#include "DebugNew.h"

Font::Font(Renderer* renderer, const std::string& name) :
    Resource(name),
    mRenderer(renderer),
    mFontDataSize(0)
{
}

Font::~Font()
{
}

void Font::load(Deserializer& source, ResourceCache* cache)
{
    mFaces.clear();
    
    mFontDataSize = source.getSize();
    if (source.getSize())
    {
        mFontData = new unsigned char[mFontDataSize];
        source.read(&mFontData[0], source.getSize());
    }
    else
        mFontData.reset();
    
    setMemoryUse(mFontDataSize);
}

const FontFace* Font::getFace(int pointSize)
{
    std::map<int, FontFace>::const_iterator i = mFaces.find(pointSize);
    if (i != mFaces.end())
        return &i->second;
    
    try
    {
        PROFILE(Font_GetFace);
        
        if (pointSize <= 0)
            EXCEPTION("Zero or negative font point size");
        
        if (!mFontData)
            EXCEPTION("Font not loaded");
        
        FontFace newFace;
        
        stbtt_fontinfo fontInfo;
        
        // Assume 1 font per file for now
        if (!stbtt_InitFont(&fontInfo, &mFontData[0], 0))
            EXCEPTION("Could not initialize font");
        
        std::vector<bool> glyphUsed;
        glyphUsed.resize(fontInfo.numGlyphs);
        for (int i = 0; i < fontInfo.numGlyphs; ++i)
            glyphUsed[i] = false;
        
        // Build glyph mapping and mark used glyphs
        for (int i = 0; i < MAX_FONT_CHARS; ++i)
        {
            newFace.mGlyphIndex[i] = stbtt_FindGlyphIndex(&fontInfo, i);
            glyphUsed[newFace.mGlyphIndex[i]] = true;
        }
        
        // Get row height
        int ascent, descent, lineGap;
        stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);
        
        // Calculate scale (use ascent only)
        float scale = (float)pointSize / ascent;
        
        // Go through glyphs to get their dimensions & offsets
        for (int i = 0; i < fontInfo.numGlyphs; ++i)
        {
            FontGlyph newGlyph;
            
            int ix0, iy0, ix1, iy1;
            int advanceWidth, leftSideBearing;
            
            if (glyphUsed[i])
            {
                stbtt_GetGlyphBitmapBox(&fontInfo, i, scale, scale, &ix0, &iy0, &ix1, &iy1);
                stbtt_GetGlyphHMetrics(&fontInfo, i, &advanceWidth, &leftSideBearing);
                newGlyph.mWidth = ix1 - ix0;
                newGlyph.mHeight = iy1 - iy0;
                newGlyph.mOffsetX = (int)(leftSideBearing * scale);
                newGlyph.mOffsetY = iy0;
                newGlyph.mAdvanceX = (int)(advanceWidth * scale);
            }
            else
            {
                newGlyph.mWidth = 0;
                newGlyph.mHeight = 0;
                newGlyph.mOffsetX = 0;
                newGlyph.mOffsetY = 0;
                newGlyph.mAdvanceX = 0;
            }
            
            newFace.mGlyphs.push_back(newGlyph);
        }
        
        // Adjust the Y-offset so that the fonts are top-aligned
        int scaledAscent = (int)(scale * ascent);
        for (int i = 0; i < fontInfo.numGlyphs; ++i)
        {
            if (glyphUsed[i])
                newFace.mGlyphs[i].mOffsetY += scaledAscent;
        }
        
        // Calculate row advance
        newFace.mRowHeight = (int)(scale * (ascent - descent + lineGap));
        
        // Now try to pack into the smallest possible texture
        int texWidth = FONT_TEXTURE_MIN_SIZE;
        int texHeight = FONT_TEXTURE_MIN_SIZE;
        bool doubleHorizontal = true;
        for (;;)
        {
            bool success = true;
            
            // Check first for theoretical possible fit. If it fails, there is no need to try to fit
            int totalArea = 0;
            for (int i = 0; i < fontInfo.numGlyphs; ++i)
            {
                if ((newFace.mGlyphs[i].mWidth) && (newFace.mGlyphs[i].mHeight))
                    totalArea += (newFace.mGlyphs[i].mWidth + 1) * (newFace.mGlyphs[i].mHeight + 1);
            }
            
            if (totalArea > texWidth * texHeight)
                success = false;
            else
            {
                PROFILE(Font_FitToTexture);
                
                AreaAllocator allocator(texWidth, texHeight);
                for (int i = 0; i < fontInfo.numGlyphs; ++i)
                {
                    if ((newFace.mGlyphs[i].mWidth) && (newFace.mGlyphs[i].mHeight))
                    {
                        int x, y;
                        // Reserve an empty border between glyphs for filtering
                        if (!allocator.reserve(newFace.mGlyphs[i].mWidth + 1, newFace.mGlyphs[i].mHeight + 1, x, y))
                        {
                            success = false;
                            break;
                        }
                        else
                        {
                            newFace.mGlyphs[i].mX = x;
                            newFace.mGlyphs[i].mY = y;
                        }
                    }
                    else
                    {
                        newFace.mGlyphs[i].mX = 0;
                        newFace.mGlyphs[i].mY = 0;
                    }
                }
            }
            
            if (!success)
            {
                // Alternate between doubling the horizontal and the vertical dimension
                if (doubleHorizontal)
                    texWidth <<= 1;
                else
                    texHeight <<= 1;
                
                if ((texWidth > FONT_TEXTURE_MAX_SIZE) || (texHeight > FONT_TEXTURE_MAX_SIZE))
                    EXCEPTION("Font face could not be fit into the largest possible texture");
                
                doubleHorizontal = !doubleHorizontal;
            }
            else
                break;
        }
        
        // Create the texture
        if (mRenderer)
        {
            SharedPtr<Texture2D> texture(new Texture2D(mRenderer, TEXTURE_STATIC));
            
            texture->setNumLevels(1); // No mipmaps
            texture->setAddressMode(COORD_U, ADDRESS_BORDER);
            texture->setAddressMode(COORD_V, ADDRESS_BORDER),
            texture->setBorderColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
            texture->setSize(texWidth, texHeight, D3DFMT_A8);
            
            D3DLOCKED_RECT hwRect;
            texture->lock(0, 0, &hwRect);
            
            // First clear the whole texture
            for (int y = 0; y < texHeight; ++y)
            {
                unsigned char* dest = (unsigned char*)hwRect.pBits + hwRect.Pitch * y;
                memset(dest, 0, texWidth);
            }
            
            // Render glyphs into texture, and find out a scaling value in case font uses less than full opacity (thin outlines)
            int sumOpacity = 0;
            int nonEmptyGlyphs = 0;
            for (int i = 0; i < fontInfo.numGlyphs; ++i)
            {
                if ((newFace.mGlyphs[i].mWidth) && (newFace.mGlyphs[i].mHeight))
                {
                    stbtt_MakeGlyphBitmap(&fontInfo, (unsigned char*)hwRect.pBits + hwRect.Pitch * newFace.mGlyphs[i].mY + newFace.mGlyphs[i].mX, newFace.mGlyphs[i].mWidth, newFace.mGlyphs[i].mHeight, hwRect.Pitch, scale, scale, i);
                    
                    int glyphMaxOpacity = 0;
                    for (int y = 0; y < newFace.mGlyphs[i].mHeight; ++y)
                    {
                        unsigned char* pixels = (unsigned char*)hwRect.pBits + hwRect.Pitch * (y + newFace.mGlyphs[i].mY) + newFace.mGlyphs[i].mX;
                        
                        for (int x = 0; x < newFace.mGlyphs[i].mWidth; ++x)
                            glyphMaxOpacity = max(glyphMaxOpacity, pixels[x]);
                    }
                    
                    if (glyphMaxOpacity > 0)
                    {
                        sumOpacity += glyphMaxOpacity;
                        ++nonEmptyGlyphs;
                    }
                }
            }
            
            // Apply the scaling if necessary
            int avgOpacity = nonEmptyGlyphs ? sumOpacity / nonEmptyGlyphs : 255;
            if (avgOpacity < 255)
            {
                float scale = 255.0f / avgOpacity;
                
                for (int i = 0; i < fontInfo.numGlyphs; ++i)
                {
                    for (int y = 0; y < newFace.mGlyphs[i].mHeight; ++y)
                    {
                        unsigned char* dest = (unsigned char*)hwRect.pBits + hwRect.Pitch * (y + newFace.mGlyphs[i].mY) + newFace.mGlyphs[i].mX;
                        for (int x = 0; x < newFace.mGlyphs[i].mWidth; ++x)
                        {
                            int pixel = dest[x];
                            dest[x] = min((int)(pixel * scale), 255);
                        }
                    }
                }
            }
            
            texture->unlock();
            setMemoryUse(getMemoryUse() + texWidth * texHeight);
            newFace.mTexture = staticCast<Texture>(texture);
        }
        
        mFaces[pointSize] = newFace;
        return &mFaces[pointSize];
    }
    catch (...)
    {
        // An error occurred. Store and return an empty font face
        FontFace emptyFace;
        FontGlyph emptyGlyph;
        emptyGlyph.mX = 0;
        emptyGlyph.mY = 0;
        emptyGlyph.mWidth = 0;
        emptyGlyph.mHeight = 0;
        emptyGlyph.mOffsetX = 0;
        emptyGlyph.mOffsetY = 0;
        emptyGlyph.mAdvanceX = 0;
        emptyFace.mGlyphs.push_back(emptyGlyph);
        for (unsigned i = 0; i < MAX_FONT_CHARS; ++i)
            emptyFace.mGlyphIndex[i] = 0;
        
        mFaces[pointSize] = emptyFace;
        return &mFaces[pointSize];
    }
}

std::string getSystemFontDirectory()
{
    char expandedSystemPath[256];
    
    if (!ExpandEnvironmentStrings("%WinDir%", expandedSystemPath, 256))
        return std::string();
    
    return std::string(expandedSystemPath) + "\\Fonts";
}

