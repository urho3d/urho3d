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
#include "Log.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererImpl.h"
#include "StringUtils.h"
#include "Texture2D.h"

#include "ft2build.h"
#include FT_FREETYPE_H

#include "DebugNew.h"

bool freeTypeInitialized = false;
unsigned numFonts = 0;
static FT_Library library;

Font::Font(Renderer* renderer, const std::string& name) :
    Resource(name),
    mRenderer(renderer),
    mFontDataSize(0)
{
    ++numFonts;
}

Font::~Font()
{
    --numFonts;
    
    // Uninitialize FreeType when no more fonts in existence
    if ((!numFonts) && (freeTypeInitialized))
    {
        FT_Done_FreeType(library);
        freeTypeInitialized = false;
    }
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
    
    FT_Face face;
    FT_Error error;
    
    try
    {
        PROFILE(Font_GetFace);
        
        if (pointSize <= 0)
            EXCEPTION("Zero or negative point size");
        
        if (!mFontDataSize)
            EXCEPTION("Font not loaded");
        
        if (!freeTypeInitialized)
        {
            error = FT_Init_FreeType(&library);
            if (error)
                EXCEPTION("Could not initialize FreeType library");
            freeTypeInitialized = true;
        }
        
        error = FT_New_Memory_Face(library, &mFontData[0], mFontDataSize, 0, &face);
        if (error)
            EXCEPTION("Could not create font face");
        error = FT_Set_Char_Size(face, 0, pointSize * 64, FONT_DPI, FONT_DPI);
        if (error)
        {
            FT_Done_Face(face);
            EXCEPTION("Could not set font point size " + toString(pointSize));
        }
        
        FontFace newFace;
        
        FT_GlyphSlot slot = face->glyph;
        unsigned freeIndex = 0;
        std::map<unsigned, unsigned> toRemapped;
        std::vector<unsigned> toOriginal;
        
        // Build glyph mapping. Only render the glyphs needed by the charset
        for (unsigned i = 0; i < MAX_FONT_CHARS; ++i)
        {
            unsigned index = FT_Get_Char_Index(face, i);
            if (toRemapped.find(index) == toRemapped.end())
            {
                newFace.mGlyphIndex[i] = freeIndex;
                toRemapped[index] = freeIndex;
                toOriginal.push_back(index);
                ++freeIndex;
            }
            else
                newFace.mGlyphIndex[i] = toRemapped[index];
        }
        
        // Load each of the glyphs to see the sizes & store other information
        int maxOffsetY = 0;
        int maxHeight = 0;
        
        for (unsigned i = 0; i < toOriginal.size(); ++i)
        {
            FontGlyph newGlyph;
            
            error = FT_Load_Glyph(face, toOriginal[i], FT_LOAD_DEFAULT);
            if (!error)
            {
                // Note: position within texture will be filled later
                newGlyph.mWidth = (short)((slot->metrics.width) >> 6);
                newGlyph.mHeight = (short)((slot->metrics.height) >> 6);
                newGlyph.mOffsetX = (short)((slot->metrics.horiBearingX) >> 6);
                newGlyph.mOffsetY = (short)((face->size->metrics.ascender - slot->metrics.horiBearingY) >> 6);
                newGlyph.mAdvanceX = (short)((slot->metrics.horiAdvance) >> 6);
                
                maxOffsetY = max(maxOffsetY, newGlyph.mOffsetY);
                maxHeight = max(maxHeight, newGlyph.mHeight);
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
        
        // Store the height of a row
        newFace.mRowHeight = (face->size->metrics.height + 63) >> 6;
        
        // Now try to pack into the smallest possible texture
        int texWidth = FONT_TEXTURE_MIN_SIZE;
        int texHeight = FONT_TEXTURE_MIN_SIZE;
        bool doubleHorizontal = true;
        
        for (;;)
        {
            PROFILE(Font_PackToTexture);
            
            bool success = true;
            
            // Check first for theoretical possible fit. If it fails, there is no need to try to fit
            int totalArea = 0;
            for (unsigned i = 0; i < newFace.mGlyphs.size(); ++i)
                totalArea += (newFace.mGlyphs[i].mWidth + 1) * (newFace.mGlyphs[i].mHeight + 1);
            
            if (totalArea > texWidth * texHeight)
                success = false;
            else
            {
                AreaAllocator allocator(texWidth, texHeight);
                for (unsigned i = 0; i < newFace.mGlyphs.size(); ++i)
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
                {
                    FT_Done_Face(face);
                    EXCEPTION("Font face could not be fit into the largest possible texture");
                }
                doubleHorizontal = !doubleHorizontal;
            }
            else
                break;
        }
        
        // Create the texture
        SharedPtr<Texture2D> texture(new Texture2D(mRenderer, TEXTURE_STATIC));
        try
        {
            PROFILE(Font_RenderToTexture);
            
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
            unsigned char avgMaxOpacity = 255;
            unsigned sumMaxOpacity = 0;
            unsigned samples = 0;
            for (unsigned i = 0; i < newFace.mGlyphs.size(); ++i)
            {
                FT_Load_Glyph(face, toOriginal[i], FT_LOAD_DEFAULT);
                FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
                
                unsigned char glyphOpacity = 0;
                for (int y = 0; y < newFace.mGlyphs[i].mHeight; ++y)
                {
                    unsigned char* src = slot->bitmap.buffer + slot->bitmap.pitch * y;
                    unsigned char* dest = (unsigned char*)hwRect.pBits + hwRect.Pitch * (y + newFace.mGlyphs[i].mY) + newFace.mGlyphs[i].mX;
                    
                    for (int x = 0; x < newFace.mGlyphs[i].mWidth; ++x)
                    {
                        dest[x] = src[x];
                        glyphOpacity = max(glyphOpacity, src[x]);
                    }
                }
                if (glyphOpacity)
                {
                    sumMaxOpacity += glyphOpacity;
                    ++samples;
                }
            }
            
            // Clamp the minimum possible value to avoid overbrightening
            if (samples)
                avgMaxOpacity = max(sumMaxOpacity / samples, 128);
            
            if (avgMaxOpacity < 255)
            {
                // Apply the scaling value if necessary
                float scale = 255.0f / avgMaxOpacity;
                for (unsigned i = 0; i < newFace.mGlyphs.size(); ++i)
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
            FT_Done_Face(face);
            setMemoryUse(getMemoryUse() + texWidth * texHeight);
        }
        catch (...)
        {
            FT_Done_Face(face);
            throw;
        }
        
        newFace.mTexture = staticCast<Texture>(texture);
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

