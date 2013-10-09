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
#include "StringUtils.h"
#include "Texture2D.h"
#include "XMLFile.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "DebugNew.h"

namespace Urho3D
{

static const int MIN_POINT_SIZE = 1;
static const int MAX_POINT_SIZE = 96;

/// FreeType library subsystem.
class FreeTypeLibrary : public Object
{
    OBJECT(FreeTypeLibrary);
    
public:
    /// Construct.
    FreeTypeLibrary(Context* context) :
        Object(context)
    {
        FT_Error error = FT_Init_FreeType(&library_);
        if (error)
            LOGERROR("Could not initialize FreeType library");
    }
    
    /// Destruct.
    virtual ~FreeTypeLibrary()
    {
        FT_Done_FreeType(library_);
    }
    
    FT_Library GetLibrary() const { return library_; }
    
private:
    /// FreeType library.
    FT_Library library_;
};

FontGlyph::FontGlyph() :
    used_(false)
{
}

FontFace::FontFace() :
    hasKerning_(false)
{
}

FontFace::~FontFace()
{
}

const FontGlyph* FontFace::GetGlyph(unsigned c) const
{
    HashMap<unsigned, unsigned>::ConstIterator i = glyphMapping_.Find(c);
    if (i != glyphMapping_.End())
    {
        const FontGlyph& glyph = glyphs_[i->second_];
        glyph.used_ = true;
        return &glyph;
    }
    else
        return NULL;
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
    if (leftIt != glyphMapping_.End())
        leftIndex = leftIt->second_;
    else
        return 0;
    HashMap<unsigned, unsigned>::ConstIterator rightIt = glyphMapping_.Find(d);
    if (rightIt != glyphMapping_.End())
        rightIndex = rightIt->second_;
    else
        return 0;
    
    HashMap<unsigned, unsigned>::ConstIterator kerningIt = glyphs_[leftIndex].kerning_.Find(rightIndex);
    if (kerningIt != glyphs_[leftIndex].kerning_.End())
        return kerningIt->second_;
    else
        return 0;
}

bool FontFace::IsDataLost() const
{
    for (unsigned i = 0; i < textures_.Size(); ++i)
    {
        if (textures_[i]->IsDataLost())
            return true;
    }
    return false;
}

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
    
    // In headless mode, do not actually load, just return success
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics)
        return true;
        
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

    String ext = GetExtension(GetName());
    if (ext == ".ttf")
        fontType_ = FONT_TTF;
    else if (ext == ".xml" || ext == ".fnt")
        fontType_ = FONT_BITMAP;

    SetMemoryUse(fontDataSize_);
    return true;
}

bool Font::SaveXML(Serializer& dest, int pointSize, bool usedGlyphs)
{
    const FontFace* fontFace = GetFace(pointSize);
    if (!fontFace)
        return false;
    
    PROFILE(FontSaveXML);
    
    SharedPtr<FontFace> packedFontFace;
    if (usedGlyphs)
    {
        // Save used glyphs only, try to pack them first
        packedFontFace = Pack(fontFace);
        if (packedFontFace)
            fontFace = packedFontFace;
        else
            return false;
    }
    
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    XMLElement rootElem = xml->CreateRoot("font");

    // Information
    XMLElement childElem = rootElem.CreateChild("info");
    String fileName = GetFileName(GetName());
    childElem.SetAttribute("face", fileName);
    childElem.SetAttribute("size", String(pointSize));
    
    // Common
    childElem = rootElem.CreateChild("common");
    childElem.SetInt("lineHeight", fontFace->rowHeight_);
    unsigned pages = fontFace->textures_.Size();
    childElem.SetInt("pages", pages);

    // Construct the path to store the texture
    String pathName;
    File* file = dynamic_cast<File*>(&dest);
    if (file)
        // If serialize to file, use the file's path
        pathName = GetPath(file->GetName());
    else
        // Otherwise, use the font resource's path
        pathName = "Data/" + GetPath(GetName());

    // Pages
    childElem = rootElem.CreateChild("pages");
    for (unsigned i = 0; i < pages; ++i)
    {
        XMLElement pageElem = childElem.CreateChild("page");
        pageElem.SetInt("id", i);
        String texFileName = fileName + "_" + String(i) + ".png";
        pageElem.SetAttribute("file", texFileName);
        
        // Save the font face texture to image file
        SaveFaceTexture(fontFace->textures_[i], pathName + texFileName);
    }
    
    // Chars and kernings
    XMLElement charsElem = rootElem.CreateChild("chars");
    unsigned numGlyphs = fontFace->glyphs_.Size();
    charsElem.SetInt("count", numGlyphs);
    XMLElement kerningsElem;
    bool hasKerning = fontFace->hasKerning_;
    if (hasKerning)
        kerningsElem = rootElem.CreateChild("kernings");
    for (HashMap<unsigned, unsigned>::ConstIterator i = fontFace->glyphMapping_.Begin(); i != fontFace->glyphMapping_.End(); ++i)
    {
        // Char
        XMLElement charElem = charsElem.CreateChild("char");
        charElem.SetInt("id", i->first_);
        FontGlyph glyph = fontFace->glyphs_[i->second_];
        charElem.SetInt("x", glyph.x_);
        charElem.SetInt("y", glyph.y_);
        charElem.SetInt("width", glyph.width_);
        charElem.SetInt("height", glyph.height_);
        charElem.SetInt("xoffset", glyph.offsetX_);
        charElem.SetInt("yoffset", glyph.offsetY_);
        charElem.SetInt("xadvance", glyph.advanceX_);
        charElem.SetInt("page", glyph.page_);
        
        // Kerning
        if (hasKerning)
        {
            for (HashMap<unsigned, unsigned>::ConstIterator j = glyph.kerning_.Begin(); j != glyph.kerning_.End(); ++j)
            {
                // To conserve space, only write when amount is non zero
                if (j->second_ == 0)
                    continue;
                
                XMLElement kerningElem = kerningsElem.CreateChild("kerning");
                kerningElem.SetInt("first", i->first_);
                kerningElem.SetInt("second", j->first_);
                kerningElem.SetInt("amount", j->second_);
            }
        }
    }
    
    return xml->Save(dest);
}

const FontFace* Font::GetFace(int pointSize)
{
    // In headless mode, always return null
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics)
        return 0;
    
    // For bitmap font type, always return the same font face provided by the font's bitmap file regardless of the actual requested point size
    if (fontType_ == FONT_BITMAP)
        pointSize = 0;
    else
        pointSize = Clamp(pointSize, MIN_POINT_SIZE, MAX_POINT_SIZE);
    
    HashMap<int, SharedPtr<FontFace> >::Iterator i = faces_.Find(pointSize);
    if (i != faces_.End())
    {
        if (!i->second_->IsDataLost())
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
    FT_Library library = freeType->GetLibrary();
    
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
    
    LOGDEBUG(ToString("Font face %s (%dpt) has %d glyphs", GetFileName(GetName()).CString(), pointSize, numGlyphs));
    
    // Load each of the glyphs to see the sizes & store other information
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
    
    // Now try to pack into the smallest possible texture(s)
    Vector<SharedPtr<Image> > images;
    unsigned totalTextureSize = 0;
    unsigned page = 0;
    unsigned startIndex = 0;
    unsigned index;
    unsigned sumMaxOpacity = 0;
    unsigned samples = 0;
    
    while (startIndex < numGlyphs)
    {
        AreaAllocator allocator(FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MAX_SIZE, FONT_TEXTURE_MAX_SIZE);
        for (index = startIndex; index < numGlyphs; ++index)
        {
            if (newFace->glyphs_[index].width_ && newFace->glyphs_[index].height_)
            {
                int x, y;
                // Reserve an empty border between glyphs for filtering
                if (allocator.Allocate(newFace->glyphs_[index].width_ + 1, newFace->glyphs_[index].height_ + 1, x, y))
                {
                    newFace->glyphs_[index].x_ = x;
                    newFace->glyphs_[index].y_ = y;
                    newFace->glyphs_[index].page_ = page;
                }
                else
                    break;
            }
            else
            {
                newFace->glyphs_[index].x_ = 0;
                newFace->glyphs_[index].y_ = 0;
                newFace->glyphs_[index].page_ = 0;
            }
        }
        
        int texWidth = allocator.GetWidth();
        int texHeight = allocator.GetHeight();

        // Create the image for rendering the fonts
        SharedPtr<Image> image(new Image(context_));
        images.Push(image);
        image->SetSize(texWidth, texHeight, 1);
        
        // First clear the whole image
        unsigned char* imageData = image->GetData();
        for (int y = 0; y < texHeight; ++y)
        {
            unsigned char* dest = imageData + texWidth * y;
            memset(dest, 0, texWidth);
        }
        
        // Render glyphs into texture, and find out a scaling value in case font uses less than full opacity (thin outlines)
        for (unsigned i = startIndex; i < index; ++i)
        {
            if (!newFace->glyphs_[i].width_ || !newFace->glyphs_[i].height_)
                continue;
            
            FT_Load_Glyph(face, i, FT_LOAD_DEFAULT);
            FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);

            unsigned char glyphOpacity = 0;
            
            if (slot->bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
            {
                for (int y = 0; y < newFace->glyphs_[i].height_; ++y)
                {
                    unsigned char* src = slot->bitmap.buffer + slot->bitmap.pitch * y;
                    unsigned char* dest = imageData + texWidth * (y + newFace->glyphs_[i].y_) + newFace->glyphs_[i].x_;

                    for (int x = 0; x < newFace->glyphs_[i].width_; ++x)
                    {
                        dest[x] = (src[x >> 3] & (0x80 >> (x & 7))) ? 255 : 0;
                        glyphOpacity = 255;
                    }
                }
            }
            else
            {
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
            }
            if (glyphOpacity)
            {
                sumMaxOpacity += glyphOpacity;
                ++samples;
            }
        }
        
        ++page;
        startIndex = index;
    }
    
    // Clamp the minimum possible value to avoid overbrightening
    unsigned char avgMaxOpacity = 255;
    if (samples)
        avgMaxOpacity = Max(sumMaxOpacity / samples, 128);
    
    if (avgMaxOpacity < 255)
    {
        // Apply the scaling value if necessary
        float scale = 255.0f / avgMaxOpacity;
        for (unsigned i = 0; i < numGlyphs; ++i)
        {
            Image* image = images[newFace->glyphs_[i].page_];
            unsigned char* imageData = image->GetData();
            for (int y = 0; y < newFace->glyphs_[i].height_; ++y)
            {
                unsigned char* dest = imageData + image->GetWidth() * (y + newFace->glyphs_[i].y_) + newFace->glyphs_[i].x_;
                for (int x = 0; x < newFace->glyphs_[i].width_; ++x)
                {
                    int pixel = dest[x];
                    dest[x] = Min((int)(pixel * scale), 255);
                }
            }
        }
    }
    
    // Create the texture and load the image into it
    for (Vector<SharedPtr<Image> >::ConstIterator i = images.Begin(); i != images.End(); ++i)
    {
        int texWidth = i->Get()->GetWidth();
        int texHeight = i->Get()->GetHeight();
        
        SharedPtr<Texture> texture = LoadFaceTexture(*i);
        if (!texture)
            return 0;
        newFace->textures_.Push(texture);
        totalTextureSize += texWidth * texHeight;
    }
    
    FT_Done_Face(face);
    
    SetMemoryUse(GetMemoryUse() + totalTextureSize);
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
    
    SharedPtr<FontFace> newFace(new FontFace());
    
    XMLElement infoElem = root.GetChild("info");
    if (!infoElem.IsNull())
        newFace->pointSize_ = infoElem.GetInt("size");
        
    XMLElement commonElem = root.GetChild("common");
    newFace->rowHeight_ = commonElem.GetInt("lineHeight");
    unsigned pages = commonElem.GetInt("pages");
    newFace->textures_.Reserve(pages);

    ResourceCache* resourceCache = GetSubsystem<ResourceCache>();
    String fontPath = GetPath(GetName());
    unsigned totalTextureSize = 0;

    XMLElement pageElem = pagesElem.GetChild("page");
    for (unsigned i = 0; i < pages; ++i)
    {
        if (pageElem.IsNull())
        {
            LOGERROR("Could not find Page element for page: " + String(i));
            return 0;
        }

        // Assume the font image is in the same directory as the font description file
        String textureFile = fontPath + pageElem.GetAttribute("file");
        
        // Load texture manually to allow controlling the alpha channel mode
        SharedPtr<File> fontFile = resourceCache->GetFile(textureFile);
        SharedPtr<Image> fontImage(new Image(context_));
        if (!fontFile || !fontImage->Load(*fontFile))
        {
            LOGERROR("Failed to load font image file");
            return 0;
        }
        SharedPtr<Texture> texture = LoadFaceTexture(fontImage);
        if (!texture)
            return 0;
        newFace->textures_.Push(texture);
        totalTextureSize += fontImage->GetWidth() * fontImage->GetHeight() * fontImage->GetComponents();
        
        pageElem = pageElem.GetNext("page");
    }
    
    XMLElement charsElem = root.GetChild("chars");
    int count = charsElem.GetInt("count");
    newFace->glyphs_.Reserve(count);
    unsigned index = 0;
    
    XMLElement charElem = charsElem.GetChild("char");
    while (!charElem.IsNull())
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
        glyph.page_ = charElem.GetInt("page");
        newFace->glyphs_.Push(glyph);
        newFace->glyphMapping_[id] = index++;
        
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
                
                FontGlyph& glyph = newFace->glyphs_[i->second_];
                glyph.kerning_[second] = amount;
            }
            
            kerningElem = kerningElem.GetNext("kerning");
        }
    }
    
    LOGDEBUG(ToString("Bitmap font face %s has %d glyphs", GetFileName(GetName()).CString(), count));

    SetMemoryUse(GetMemoryUse() + totalTextureSize);
    faces_[pointSize] = newFace;
    return newFace;
}

unsigned Font::ConvertFormatToNumComponents(unsigned format)
{
    if (format == Graphics::GetRGBAFormat())
        return 4;
    else if (format == Graphics::GetRGBFormat())
        return 3;
    else if (format == Graphics::GetLuminanceAlphaFormat())
        return 2;
    else
        return 1;
}

SharedPtr<FontFace> Font::Pack(const FontFace* fontFace)
{
    SharedPtr<FontFace> packedFontFace(new FontFace());
    
    // Clone properties
    packedFontFace->pointSize_ = fontFace->pointSize_;
    packedFontFace->rowHeight_ = fontFace->rowHeight_;
    packedFontFace->hasKerning_ = fontFace->hasKerning_;
    
    // Assume that format is the same for all textures and that bitmap font type may have more than one component
    unsigned components = ConvertFormatToNumComponents(fontFace->textures_[0]->GetFormat());
    
    // Save the existing textures as image resources
    Vector<SharedPtr<Image> > images(fontFace->textures_.Size());
    for (unsigned i = 0; i < fontFace->textures_.Size(); ++i)
        images[i] = SaveFaceTexture(fontFace->textures_[i]);
    
    // Reallocate used glyphs to new texture(s)
    unsigned page = 0;
    unsigned index = 0;
    unsigned startIndex = 0;
    HashMap<unsigned, unsigned>::ConstIterator startIter = fontFace->glyphMapping_.Begin();
    HashMap<unsigned, unsigned>::ConstIterator i;
    while (startIter != fontFace->glyphMapping_.End())
    {
        AreaAllocator allocator(FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MAX_SIZE, FONT_TEXTURE_MAX_SIZE);
        for (i = startIter; i != fontFace->glyphMapping_.End(); ++i)
        {
            FontGlyph glyph = fontFace->glyphs_[i->second_];
            if (!glyph.used_)
                continue;

            if (glyph.width_ && glyph.height_)
            {
                int x, y;
                // Reserve an empty border between glyphs for filtering
                if (allocator.Allocate(glyph.width_ + 1, glyph.height_ + 1, x, y))
                {
                    glyph.x_ = x;
                    glyph.y_ = y;
                    glyph.page_ = page;
                }
                else
                    break;
            }
            
            packedFontFace->glyphs_.Push(glyph);
            packedFontFace->glyphMapping_[i->first_] = index++;
        }
        
        int texWidth = allocator.GetWidth();
        int texHeight = allocator.GetHeight();
        
        // Create the image for rendering the fonts
        SharedPtr<Image> image(new Image(context_));
        image->SetSize(texWidth, texHeight, components);
        
        // First clear the whole image
        unsigned char* imageData = image->GetData();
        for (int y = 0; y < texHeight; ++y)
        {
            unsigned char* dest = imageData + components * texWidth * y;
            memset(dest, 0, components * texWidth);
        }
        
        // Then render the glyphs into new image
        for (HashMap<unsigned, unsigned>::ConstIterator j = startIter; j != i; ++j)
        {
            FontGlyph glyph = fontFace->glyphs_[j->second_];
            if (!glyph.used_)
                continue;
            
            if (!glyph.width_ || !glyph.height_)
            {
                ++startIndex;
                continue;
            }
            
            FontGlyph packedGlyph = packedFontFace->glyphs_[startIndex++];
            
            Image* image = images[glyph.page_];
            unsigned char* source = image->GetData() + components * (image->GetWidth() * glyph.y_ + glyph.x_);
            unsigned char* destination = imageData + components * (texWidth * packedGlyph.y_ + packedGlyph.x_);
            for (int i = 0; i < glyph.height_; ++i)
            {
                memcpy(destination, source, components * glyph.width_);
                source += components * image->GetWidth();
                destination += components * texWidth;
            }
        }
        
        // Finally load image into the texture
        SharedPtr<Texture> texture = LoadFaceTexture(image);
        if (!texture)
            return SharedPtr<FontFace>();
        packedFontFace->textures_.Push(texture);

        ++page;
        startIter = i;
        assert(index == startIndex);
    }
    
    return packedFontFace;
}

SharedPtr<Texture> Font::LoadFaceTexture(SharedPtr<Image> image)
{
    Texture2D* texture = new Texture2D(context_);
    texture->SetMipsToSkip(QUALITY_LOW, 0); // No quality reduction
    texture->SetNumLevels(1); // No mipmaps
    texture->SetAddressMode(COORD_U, ADDRESS_BORDER);
    texture->SetAddressMode(COORD_V, ADDRESS_BORDER),
    texture->SetBorderColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
    if (!texture->Load(image, true))
    {
        delete texture;
        LOGERROR("Could not load texture from image resource");
        return SharedPtr<Texture>();
    }
    return SharedPtr<Texture>(texture);
}

SharedPtr<Image> Font::SaveFaceTexture(Texture* texture)
{
    Image* image = new Image(context_);
    image->SetSize(texture->GetWidth(), texture->GetHeight(), ConvertFormatToNumComponents(texture->GetFormat()));
    if (!static_cast<Texture2D*>(texture)->GetData(0, image->GetData()))
    {
        delete image;
        LOGERROR("Could not save texture to image resource");
        return SharedPtr<Image>();
    }
    return SharedPtr<Image>(image);
}

bool Font::SaveFaceTexture(Texture* texture, const String& fileName)
{
    SharedPtr<Image> image = SaveFaceTexture(texture);
    return image ? image->SavePNG(fileName) : false;
}

}
