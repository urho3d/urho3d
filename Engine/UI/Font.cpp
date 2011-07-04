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
#include "AreaAllocator.h"
#include "Context.h"
#include "Deserializer.h"
#include "Font.h"
#include "Graphics.h"
#include "Log.h"
#include "Profiler.h"
#include "Texture2D.h"

#include "ft2build.h"
#include FT_FREETYPE_H

#include "DebugNew.h"

/// FreeType library subsystem
class FreeTypeLibrary : public Object
{
    OBJECT(FreeTypeLibrary);
    
public:
    /// Construct
    FreeTypeLibrary(Context* context) :
        Object(context)
    {
        FT_Error error = FT_Init_FreeType(&mLibrary);
        if (error)
            LOGERROR("Could not initialize FreeType library");
    }
    
    /// Destruct
    virtual ~FreeTypeLibrary()
    {
        FT_Done_FreeType(mLibrary);
    }
    
    FT_Library getLibrary() const { return mLibrary; }
    
private:
    /// FreeType library
    FT_Library mLibrary;
};

OBJECTTYPESTATIC(FreeTypeLibrary);
OBJECTTYPESTATIC(Font);

Font::Font(Context* context) :
    Resource(context),
    fontDataSize_(0)
{
    // Create & initialize FreeType library if it does not exist yet
    if (!GetSubsystem<FreeTypeLibrary>())
        context_->RegisterSubsystem(new FreeTypeLibrary(context_));
}

Font::~Font()
{
}

void Font::RegisterObject(Context* context)
{
    context->RegisterFactory<Font>();
}

bool Font::Load(Deserializer& source)
{
    PROFILE(LoadFont);
    
    faces_.Clear();
    
    fontDataSize_ = source.GetSize();
    if (fontDataSize_)
    {
        fontData_ = new unsigned char[fontDataSize_];
        if (source.Read(&fontData_[0], fontDataSize_) != fontDataSize_)
            return false;
    }
    else
    {
        fontData_.Reset();
        return false;
    }
    
    SetMemoryUse(fontDataSize_);
    return true;
}

const FontFace* Font::GetFace(int pointSize)
{
    Map<int, FontFace>::ConstIterator i = faces_.Find(pointSize);
    if (i != faces_.End())
        return &i->second_;
    
    PROFILE(GetFontFace);
    
    FT_Face face;
    FT_Error error;
    FT_Library library = GetSubsystem<FreeTypeLibrary>()->getLibrary();
    
    if (pointSize <= 0)
    {
        LOGERROR("Zero or negative point size");
        return 0;
    }
    
    if (!fontDataSize_)
    {
        LOGERROR("Font not loaded");
        return 0;
    }
    
    error = FT_New_Memory_Face(library, &fontData_[0], fontDataSize_, 0, &face);
    if (error)
    {
        LOGERROR("Could not create font face");
        return 0;
    }
    error = FT_Set_Char_Size(face, 0, pointSize * 64, FONT_DPI, FONT_DPI);
    if (error)
    {
        FT_Done_Face(face);
        LOGERROR("Could not set font point size " + String(pointSize));
        return 0;
    }
    
    FontFace newFace;
    
    FT_GlyphSlot slot = face->glyph;
    unsigned freeIndex = 0;
    Map<unsigned, unsigned> toRemapped;
    PODVector<unsigned> toOriginal;
    
    // Build glyph mapping. Only render the glyphs needed by the charset
    for (unsigned i = 0; i < MAX_FONT_CHARS; ++i)
    {
        unsigned index = FT_Get_Char_Index(face, i);
        if (toRemapped.Find(index) == toRemapped.End())
        {
            newFace.glyphIndex_[i] = freeIndex;
            toRemapped[index] = freeIndex;
            toOriginal.Push(index);
            ++freeIndex;
        }
        else
            newFace.glyphIndex_[i] = toRemapped[index];
    }
    
    // Load each of the glyphs to see the sizes & store other information
    int maxOffsetY = 0;
    int maxHeight = 0;
    
    for (unsigned i = 0; i < toOriginal.Size(); ++i)
    {
        FontGlyph newGlyph;
        
        error = FT_Load_Glyph(face, toOriginal[i], FT_LOAD_DEFAULT);
        if (!error)
        {
            // Note: position within texture will be filled later
            newGlyph.width_ = (short)((slot->metrics.width) >> 6);
            newGlyph.height_ = (short)((slot->metrics.height) >> 6);
            newGlyph.offsetX_ = (short)((slot->metrics.horiBearingX) >> 6);
            newGlyph.offsetY_ = (short)((face->size->metrics.ascender - slot->metrics.horiBearingY) >> 6);
            newGlyph.advanceX_ = (short)((slot->metrics.horiAdvance) >> 6);
            
            maxOffsetY = Max(maxOffsetY, newGlyph.offsetY_);
            maxHeight = Max(maxHeight, newGlyph.height_);
        }
        else
        {
            newGlyph.width_ = 0;
            newGlyph.height_ = 0;
            newGlyph.offsetX_ = 0;
            newGlyph.offsetY_ = 0;
            newGlyph.advanceX_ = 0;
        }
        
        newFace.glyphs_.Push(newGlyph);
    }
    
    // Store point size and the height of a row. Use the height of the tallest font if taller than the specified row height
    newFace.pointSize_ = pointSize;
    newFace.rowHeight_ = Max((face->size->metrics.height + 63) >> 6, maxHeight);
    
    // Now try to pack into the smallest possible texture
    int texWidth = FONT_TEXTURE_MIN_SIZE;
    int texHeight = FONT_TEXTURE_MIN_SIZE;
    bool doubleHorizontal = true;
    
    for (;;)
    {
        bool success = true;
        
        // Check first for theoretical possible fit. If it fails, there is no need to try to fit
        int totalArea = 0;
        for (unsigned i = 0; i < newFace.glyphs_.Size(); ++i)
            totalArea += (newFace.glyphs_[i].width_ + 1) * (newFace.glyphs_[i].height_ + 1);
        
        if (totalArea > texWidth * texHeight)
            success = false;
        else
        {
            AreaAllocator allocator(texWidth, texHeight);
            for (unsigned i = 0; i < newFace.glyphs_.Size(); ++i)
            {
                if (newFace.glyphs_[i].width_ && newFace.glyphs_[i].height_)
                {
                    int x, y;
                    // Reserve an empty border between glyphs for filtering
                    if (!allocator.Allocate(newFace.glyphs_[i].width_ + 1, newFace.glyphs_[i].height_ + 1, x, y))
                    {
                        success = false;
                        break;
                    }
                    else
                    {
                        newFace.glyphs_[i].x_ = x;
                        newFace.glyphs_[i].y_ = y;
                    }
                }
                else
                {
                    newFace.glyphs_[i].x_ = 0;
                    newFace.glyphs_[i].y_ = 0;
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
            
            if (texWidth > FONT_TEXTURE_MAX_SIZE || texHeight > FONT_TEXTURE_MAX_SIZE)
            {
                FT_Done_Face(face);
                LOGERROR("Font face could not be fit into the largest possible texture");
                return 0;
            }
            doubleHorizontal = !doubleHorizontal;
        }
        else
            break;
    }
    
    // Create the image for rendering the fonts
    SharedPtr<Image> image(new Image(context_));
    image->SetSize(texWidth, texHeight, 1);
    
    // First clear the whole image
    unsigned char* imageData = image->GetData();
    for (int y = 0; y < texHeight; ++y)
    {
        unsigned char* dest = imageData + texWidth * y;
        memset(dest, 0, texWidth);
    }
    
    // Render glyphs into texture, and find out a scaling value in case font uses less than full opacity (thin outlines)
    unsigned char avgMaxOpacity = 255;
    unsigned sumMaxOpacity = 0;
    unsigned samples = 0;
    for (unsigned i = 0; i < newFace.glyphs_.Size(); ++i)
    {
        FT_Load_Glyph(face, toOriginal[i], FT_LOAD_DEFAULT);
        FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
        
        unsigned char glyphOpacity = 0;
        for (int y = 0; y < newFace.glyphs_[i].height_; ++y)
        {
            unsigned char* src = slot->bitmap.buffer + slot->bitmap.pitch * y;
            unsigned char* dest = imageData + texWidth * (y + newFace.glyphs_[i].y_) + newFace.glyphs_[i].x_;
            
            for (int x = 0; x < newFace.glyphs_[i].width_; ++x)
            {
                dest[x] = src[x];
                glyphOpacity = Max(glyphOpacity, src[x]);
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
        avgMaxOpacity = Max(sumMaxOpacity / samples, 128);
    
    if (avgMaxOpacity < 255)
    {
        // Apply the scaling value if necessary
        float scale = 255.0f / avgMaxOpacity;
        for (unsigned i = 0; i < newFace.glyphs_.Size(); ++i)
        {
            for (int y = 0; y < newFace.glyphs_[i].height_; ++y)
            {
                unsigned char* dest = imageData + texWidth * (y + newFace.glyphs_[i].y_) + newFace.glyphs_[i].x_;
                for (int x = 0; x < newFace.glyphs_[i].width_; ++x)
                {
                    int pixel = dest[x];
                    dest[x] = Min((int)(pixel * scale), 255);
                }
            }
        }
    }
    
    FT_Done_Face(face);
    
    // Create the texture and load the image into it
    SharedPtr<Texture2D> texture(new Texture2D(context_));
    texture->SetNumLevels(1); // No mipmaps
    texture->SetAddressMode(COORD_U, ADDRESS_BORDER);
    texture->SetAddressMode(COORD_V, ADDRESS_BORDER),
    texture->SetBorderColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
    if (!texture->SetSize(texWidth, texHeight, Graphics::GetAlphaFormat()) || !texture->Load(image, true))
        return 0;
    
    SetMemoryUse(GetMemoryUse() + texWidth * texHeight);
    newFace.texture_ = StaticCast<Texture>(texture);
    faces_[pointSize] = newFace;
    return &faces_[pointSize];
}
