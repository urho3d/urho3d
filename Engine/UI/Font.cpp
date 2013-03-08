//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "FileSystem.h"
#include "Font.h"
#include "Graphics.h"
#include "Log.h"
#include "MemoryBuffer.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Texture2D.h"
#include "XMLFile.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "DebugNew.h"

namespace Urho3D
{

/// FreeType library subsystem.
class FreeTypeLibrary : public Object
{
    OBJECT(FreeTypeLibrary);
    
public:
    /// Construct.
    FreeTypeLibrary(Context* context) :
        Object(context)
    {
        FT_Error error = FT_Init_FreeType(&mLibrary);
        if (error)
            LOGERROR("Could not initialize FreeType library");
    }
    
    /// Destruct.
    virtual ~FreeTypeLibrary()
    {
        FT_Done_FreeType(mLibrary);
    }
    
    FT_Library getLibrary() const { return mLibrary; }
    
private:
    /// FreeType library.
    FT_Library mLibrary;
};

FontFace::FontFace() :
    hasKerning_(false)
{
}

FontFace::~FontFace()
{
}

const FontGlyph& FontFace::GetGlyph(unsigned c) const
{
    HashMap<unsigned, unsigned>::ConstIterator i = glyphMapping_.Find(c);
    if (i != glyphMapping_.End())
        return glyphs_[i->second_];
    else
        return glyphs_[0];
}

short FontFace::GetKerning(unsigned c, unsigned d) const
{
    if (!hasKerning_)
        return 0;
    
    if (c == '\n' || d == '\n')
        return 0;
    
    unsigned leftIndex = 0;
    unsigned rightIndex = 0;
    HashMap<unsigned, unsigned>::ConstIterator leftIt = glyphMapping_.Find(c);
    HashMap<unsigned, unsigned>::ConstIterator rightIt = glyphMapping_.Find(d);
    if (leftIt != glyphMapping_.End())
        leftIndex = leftIt->second_;
    if (rightIt != glyphMapping_.End())
        rightIndex = rightIt->second_;
    
    HashMap<unsigned, unsigned>::ConstIterator kerningIt = glyphs_[leftIndex].kerning_.Find(rightIndex);
    if (kerningIt != glyphs_[leftIndex].kerning_.End())
        return kerningIt->second_;
    else
        return 0;
}

OBJECTTYPESTATIC(FreeTypeLibrary);
OBJECTTYPESTATIC(Font);

Font::Font(Context* context) :
    Resource(context),
    fontDataSize_(0),
    fontType_(FONT_NONE)
{
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
    pathName_.Clear();
    
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

    pathName_ = source.GetName();
    String ext = GetExtension(pathName_).ToLower();
    if (ext == ".ttf")
        fontType_ = FONT_TTF;
    else if (ext == ".xml" || ext == ".fnt")
        fontType_ = FONT_BITMAP;

    SetMemoryUse(fontDataSize_);
    return true;
}

const FontFace* Font::GetFace( int pointSize )
{
    HashMap<int, SharedPtr<FontFace> >::Iterator i = faces_.Find(pointSize);
    if (i != faces_.End())
    {
        if (!i->second_->texture_->IsDataLost())
            return i->second_;
        else
        {
            // Erase and reload face if texture data lost (OpenGL mode only)
            faces_.Erase(i);
        }
    }
    
    PROFILE(GetFontFace);
    
    switch (fontType_)
    {
    case FONT_TTF:
        return GetFaceTTF(pointSize);

    case FONT_BITMAP:
        return GetFaceBitmap(pointSize);
    
    default:
        return 0;
    }
}

const FontFace* Font::GetFaceTTF(int pointSize)
{
    // Create & initialize FreeType library if it does not exist yet
    FreeTypeLibrary* freeType = GetSubsystem<FreeTypeLibrary>();
    if (!freeType)
        context_->RegisterSubsystem(freeType = new FreeTypeLibrary(context_));

    FT_Face face;
    FT_Error error;
    FT_Library library = freeType->getLibrary();
    
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
    
    SharedPtr<FontFace> newFace(new FontFace());
    
    FT_GlyphSlot slot = face->glyph;
    unsigned numGlyphs = 0;
    
    // Build glyph mapping
    FT_UInt glyphIndex;
    FT_ULong charCode = FT_Get_First_Char(face, &glyphIndex);
    while (glyphIndex != 0)
    {
        numGlyphs = Max((int)glyphIndex + 1, (int)numGlyphs);
        newFace->glyphMapping_[charCode] = glyphIndex;
        charCode = FT_Get_Next_Char(face, charCode, &glyphIndex);
    }
    
    LOGDEBUG("Font face has " + String(numGlyphs) + " glyphs");
    
    // Load each of the glyphs to see the sizes & store other information
    int maxOffsetY = 0;
    int maxHeight = 0;
    FT_Pos ascender = face->size->metrics.ascender;
    
    newFace->glyphs_.Reserve(numGlyphs);
    
    for (unsigned i = 0; i < numGlyphs; ++i)
    {
        FontGlyph newGlyph;
        
        error = FT_Load_Glyph(face, i, FT_LOAD_DEFAULT);
        if (!error)
        {
            // Note: position within texture will be filled later
            newGlyph.width_ = (short)((slot->metrics.width) >> 6);
            newGlyph.height_ = (short)((slot->metrics.height) >> 6);
            newGlyph.offsetX_ = (short)((slot->metrics.horiBearingX) >> 6);
            newGlyph.offsetY_ = (short)((ascender - slot->metrics.horiBearingY) >> 6);
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
        
        newFace->glyphs_.Push(newGlyph);
    }
    
    // Store kerning if face has kerning information
    if (FT_HAS_KERNING(face))
    {
        newFace->hasKerning_ = true;
        
        for (unsigned i = 0; i < numGlyphs; ++i)
        {
            for (unsigned j = 0; j < numGlyphs; ++j)
            {
                FT_Vector vector;
                FT_Get_Kerning(face, i, j, FT_KERNING_DEFAULT, &vector);
                newFace->glyphs_[i].kerning_[j] = (short)(vector.x >> 6);
            }
        }
    }
    
    // Store point size and the height of a row. Use the height of the tallest font if taller than the specified row height
    newFace->pointSize_ = pointSize;
    newFace->rowHeight_ = Max((face->size->metrics.height + 63) >> 6, maxHeight);
    
    // Now try to pack into the smallest possible texture
    int totalArea = 0;
    for (unsigned i = 0; i < numGlyphs; ++i)
        totalArea += (newFace->glyphs_[i].width_ + 1) * (newFace->glyphs_[i].height_ + 1);
    
    bool success = true;
    AreaAllocator allocator(FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MAX_SIZE, FONT_TEXTURE_MAX_SIZE);
    for (unsigned i = 0; i < numGlyphs; ++i)
    {
        if (newFace->glyphs_[i].width_ && newFace->glyphs_[i].height_)
        {
            int x, y;
            // Reserve an empty border between glyphs for filtering
            if (!allocator.Allocate(newFace->glyphs_[i].width_ + 1, newFace->glyphs_[i].height_ + 1, x, y))
            {
                success = false;
                break;
            }
            else
            {
                newFace->glyphs_[i].x_ = x;
                newFace->glyphs_[i].y_ = y;
            }
        }
        else
        {
            newFace->glyphs_[i].x_ = 0;
            newFace->glyphs_[i].y_ = 0;
        }
    }
    
    if (!success)
    {
        FT_Done_Face(face);
        LOGERROR("Font face could not be fit into the largest possible texture");
        return 0;
    }

    int texWidth = allocator.GetSize().x_;
    int texHeight = allocator.GetSize().y_;

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
    for (unsigned i = 0; i < numGlyphs; ++i)
    {
        if (!newFace->glyphs_[i].width_ || !newFace->glyphs_[i].height_)
            continue;
        
        FT_Load_Glyph(face, i, FT_LOAD_DEFAULT);
        FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
        
        unsigned char glyphOpacity = 0;
        for (int y = 0; y < newFace->glyphs_[i].height_; ++y)
        {
            unsigned char* src = slot->bitmap.buffer + slot->bitmap.pitch * y;
            unsigned char* dest = imageData + texWidth * (y + newFace->glyphs_[i].y_) + newFace->glyphs_[i].x_;
            
            for (int x = 0; x < newFace->glyphs_[i].width_; ++x)
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
        for (unsigned i = 0; i < numGlyphs; ++i)
        {
            for (int y = 0; y < newFace->glyphs_[i].height_; ++y)
            {
                unsigned char* dest = imageData + texWidth * (y + newFace->glyphs_[i].y_) + newFace->glyphs_[i].x_;
                for (int x = 0; x < newFace->glyphs_[i].width_; ++x)
                {
                    int pixel = dest[x];
                    dest[x] = Min((int)(pixel * scale), 255);
                }
            }
        }
    }
    
    FT_Done_Face(face);
    
    // Create the texture and load the image into it
    Texture2D* texture = new Texture2D(context_);
    texture->SetNumLevels(1); // No mipmaps
    texture->SetAddressMode(COORD_U, ADDRESS_BORDER);
    texture->SetAddressMode(COORD_V, ADDRESS_BORDER),
    texture->SetBorderColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
    if (!texture->SetSize(texWidth, texHeight, Graphics::GetAlphaFormat()) || !texture->Load(image, true))
    {
        delete texture;
        return 0;
    }
    
    SetMemoryUse(GetMemoryUse() + texWidth * texHeight);
    newFace->texture_ = texture;    // Pass the texture ownership to FontFace
    faces_[pointSize] = newFace;
    return newFace;
}

const FontFace* Font::GetFaceBitmap(int pointSize)
{
    SharedPtr<XMLFile> xmlReader(new XMLFile(context_));
    MemoryBuffer memoryBuffer(fontData_, fontDataSize_);
    if (!xmlReader->Load(memoryBuffer))
    {
        LOGERROR("Could not load XML file");
        return 0;
    }
    
    XMLElement root = xmlReader->GetRoot("font");
    if (root.IsNull())
    {
        LOGERROR("Could not find Font element");
        return 0;
    }

    XMLElement pagesElem = root.GetChild("pages");
    if (pagesElem.IsNull())
    {
        LOGERROR("Could not find Pages element");
        return 0;
    }
    
    /// \todo Support multiple pages
    XMLElement pageElem = pagesElem.GetChild("page");
    if (pageElem.IsNull())
    {
        LOGERROR("Could not find Page element");
        return 0;
    }
    
    SharedPtr<FontFace> newFace(new FontFace());
    
    XMLElement commonElem = root.GetChild("common");
    newFace->rowHeight_ = commonElem.GetInt("lineHeight");
    
    // \todo Does different point size always use the same bitmap file?
    String textureFile = pageElem.GetAttribute("file");

    // Assume the font image is in the same directory as the XML description
    textureFile = GetPath(pathName_) + textureFile;
    
    // Load texture manually to allow controlling the alpha channel mode
    ResourceCache* resourceCache = GetSubsystem<ResourceCache>();
    SharedPtr<File> fontFile = resourceCache->GetFile(textureFile);
    SharedPtr<Image> fontImage(new Image(context_));
    if (!fontFile || !fontImage->Load(*fontFile))
    {
        LOGERROR("Failed to load font image file");
        return 0;
    }
    Texture2D* texture = new Texture2D(context_);
    if (!texture->Load(fontImage, true))
    {
        LOGERROR("Failed to create font texture");
        delete texture;
        return 0;
    }
    newFace->texture_ = texture;
    
    XMLElement charsElem = root.GetChild("chars");
    int count = charsElem.GetInt("count");
    newFace->glyphs_.Reserve(count);
    
    XMLElement charElem = charsElem.GetChild("char");
    while(!charElem.IsNull())
    {
        int id = charElem.GetInt("id");
        FontGlyph glyph;
        glyph.x_ = charElem.GetInt("x");
        glyph.y_ = charElem.GetInt("y");
        glyph.width_ = charElem.GetInt("width");
        glyph.height_ = charElem.GetInt("height");
        glyph.offsetX_ = charElem.GetInt("xoffset");
        glyph.offsetY_ = charElem.GetInt("yoffset");
        glyph.advanceX_ = charElem.GetInt("xadvance");
        unsigned index = newFace->glyphs_.Size();
        newFace->glyphs_.Push(glyph);
        newFace->glyphMapping_[id] = index;
        
        charElem = charElem.GetNext("char");
    }
    
    XMLElement kerningsElem = root.GetChild("kernings");
    if (kerningsElem.IsNull())
        newFace->hasKerning_ = false;
    else
    {
        XMLElement kerningElem = kerningsElem.GetChild("kerning");
        while (!kerningElem.IsNull())
        {
            int first = kerningElem.GetInt("first");
            HashMap<unsigned, unsigned>::Iterator i = newFace->glyphMapping_.Find(first);
            if (i != newFace->glyphMapping_.End())
            {
                int second = kerningElem.GetInt("second");
                int amount = kerningElem.GetInt("amount");
                
                FontGlyph& fg = newFace->glyphs_[i->second_];
                fg.kerning_[second] = amount;
            }
            
            kerningElem = kerningElem.GetNext("kerning");
        }
    }
    
    SetMemoryUse(GetMemoryUse() + fontImage->GetWidth() * fontImage->GetHeight() * fontImage->GetComponents());
    faces_[pointSize] = newFace;
    return newFace;
}

}
