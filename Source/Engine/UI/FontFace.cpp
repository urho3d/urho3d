//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "Context.h"
#include "FileSystem.h"
#include "Font.h"
#include "FontFace.h"
#include "Graphics.h"
#include "Log.h"
#include "MemoryBuffer.h"
#include "ResourceCache.h"
#include "Texture2D.h"
#include "UI.h"
#include "XMLFile.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_TRUETYPE_TABLES_H

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

MutableGlyph::MutableGlyph() :
    glyphIndex_(M_MAX_UNSIGNED)
{
}

FontGlyph::FontGlyph() :
    used_(false),
    page_(M_MAX_UNSIGNED)
{
}

FontFace::FontFace(Font* font) :
    font_(font),
    hasKerning_(false)
{
}

FontFace::~FontFace()
{
    if (font_)
    {
        // When a face is unloaded, deduct the used texture data size from the parent font
        unsigned totalTextureSize = 0;
        for (unsigned i = 0; i < textures_.Size(); ++i)
            totalTextureSize += textures_[i]->GetWidth() * textures_[i]->GetHeight();
        font_->SetMemoryUse(font_->GetMemoryUse() - totalTextureSize);
    }
}

const FontGlyph* FontFace::GetGlyph(unsigned c)
{
    HashMap<unsigned, unsigned>::ConstIterator i = glyphMapping_.Find(c);
    if (i != glyphMapping_.End())
    {
        FontGlyph& glyph = glyphs_[i->second_];
        glyph.used_ = true;
        return &glyph;
    }
    else
        return 0;
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

FontFaceFreeType::FontFaceFreeType(Font* font) :
    FontFace(font),
    face_(0),
    bitmapSize_(0)
{

}

FontFaceFreeType::~FontFaceFreeType()
{
    if (face_)
    {
        FT_Done_Face((FT_Face)face_);
        face_ = 0;
    }

    for (List<MutableGlyph*>::Iterator i = mutableGlyphs_.Begin(); i != mutableGlyphs_.End(); ++i)
        delete *i;
    mutableGlyphs_.Clear();
}

bool FontFaceFreeType::Load(const unsigned char* fontData, unsigned fontDataSize, int pointSize)
{
    Context* context = font_->GetContext();
    // Create & initialize FreeType library if it does not exist yet
    FreeTypeLibrary* freeType = font_->GetSubsystem<FreeTypeLibrary>();
    if (!freeType)
        context->RegisterSubsystem(freeType = new FreeTypeLibrary(context));
    // Ensure the FreeType library is kept alive as long as TTF font resources exist
    freeType_ = freeType;

    UI* ui = font_->GetSubsystem<UI>();
    int maxTextureSize = ui->GetMaxFontTextureSize();

    FT_Face face;
    FT_Error error;
    FT_Library library = freeType->GetLibrary();

    if (pointSize <= 0)
    {
        LOGERROR("Zero or negative point size");
        return false;
    }

    if (!fontDataSize)
    {
        LOGERROR("Could not create font face from zero size data");
        return false;
    }

    error = FT_New_Memory_Face(library, fontData, fontDataSize, 0, &face);
    if (error)
    {
        LOGERROR("Could not create font face");
        return false;
    }
    error = FT_Set_Char_Size(face, 0, pointSize * 64, FONT_DPI, FONT_DPI);
    if (error)
    {
        FT_Done_Face(face);
        LOGERROR("Could not set font point size " + String(pointSize));
        return false;
    }

    face_ = face;

    FT_GlyphSlot slot = face->glyph;
    unsigned numGlyphs = 0;

    // Build glyph mapping
    FT_UInt glyphIndex;
    FT_ULong charCode = FT_Get_First_Char(face, &glyphIndex);
    while (glyphIndex != 0)
    {
        numGlyphs = Max((int)glyphIndex + 1, (int)numGlyphs);
        glyphMapping_[charCode] = glyphIndex;
        charCode = FT_Get_Next_Char(face, charCode, &glyphIndex);
    }

    LOGDEBUGF("Font face %s (%dpt) has %d glyphs", GetFileName(font_->GetName()).CString(), pointSize, numGlyphs);

    // Load each of the glyphs to see the sizes & store other information
    int maxWidth = 0;
    int maxHeight = 0;
    int loadMode = ui->GetForceAutoHint() ? FT_LOAD_FORCE_AUTOHINT : FT_LOAD_DEFAULT;
    int ascender = face->size->metrics.ascender >> 6;
    int descender = face->size->metrics.descender >> 6;

    // Check if the font's OS/2 info gives different (larger) values for ascender & descender
    TT_OS2* os2Info = (TT_OS2*)FT_Get_Sfnt_Table(face, ft_sfnt_os2);
    if (os2Info)
    {
        ascender = Max(ascender, os2Info->usWinAscent * face->size->metrics.y_ppem / face->units_per_EM);
        ascender = Max(ascender, os2Info->sTypoAscender * face->size->metrics.y_ppem / face->units_per_EM);
        descender = Max(descender, os2Info->usWinDescent * face->size->metrics.y_ppem / face->units_per_EM);
        descender = Max(descender, os2Info->sTypoDescender * face->size->metrics.y_ppem / face->units_per_EM);
    }

    // Store point size and row height. Use the maximum of ascender + descender, or the face's stored default row height
    pointSize_ = pointSize;
    rowHeight_ = Max(ascender + descender, face->size->metrics.height >> 6);

    glyphs_.Reserve(numGlyphs);

    for (unsigned i = 0; i < numGlyphs; ++i)
    {
        FontGlyph newGlyph;

        error = FT_Load_Glyph(face, i, loadMode);
        if (!error)
        {
            // Note: position within texture will be filled later
            newGlyph.width_ = (short)Max(slot->metrics.width >> 6, slot->bitmap.width);
            newGlyph.height_ = (short)Max(slot->metrics.height >> 6, slot->bitmap.rows);
            newGlyph.offsetX_ = (short)(slot->metrics.horiBearingX >> 6);
            newGlyph.offsetY_ = (short)(ascender - (slot->metrics.horiBearingY >> 6));
            newGlyph.advanceX_ = (short)(slot->metrics.horiAdvance >> 6);

            maxWidth = Max(maxWidth, newGlyph.width_);
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

        glyphs_.Push(newGlyph);
    }

    // Store kerning if face has kerning information
    if (FT_HAS_KERNING(face))
    {
        hasKerning_ = true;

        // Read kerning manually to be more efficient and avoid out of memory crash when use large font file, for example there
        // are 29354 glyphs in msyh.ttf
        FT_ULong tag = FT_MAKE_TAG('k', 'e', 'r', 'n');
        FT_ULong kerningTableSize = 0;
        FT_Error error = FT_Load_Sfnt_Table(face, tag, 0, NULL, &kerningTableSize);
        if (error)
        {
            LOGERROR("Could not get kerning table length");
            return false;
        }

        SharedArrayPtr<unsigned char> kerningTable(new unsigned char[kerningTableSize]);
        error = FT_Load_Sfnt_Table(face, tag, 0, kerningTable, &kerningTableSize);
        if (error)
        {
            LOGERROR("Could not load kerning table");
            return false;
        }

        // Convert big endian to little endian
        for (unsigned i = 0; i < kerningTableSize; i += 2)
            Swap(kerningTable[i], kerningTable[i + 1]);
        MemoryBuffer deserializer(kerningTable, kerningTableSize);

        unsigned short version = deserializer.ReadUShort();
        if (version == 0)
        {
            unsigned numKerningTables = deserializer.ReadUShort();
            for (unsigned i = 0; i < numKerningTables; ++i)
            {
                unsigned short version = deserializer.ReadUShort();
                unsigned short length = deserializer.ReadUShort();
                unsigned short coverage = deserializer.ReadUShort();

                if (version == 0 && coverage == 1)
                {
                    unsigned numKerningPairs = deserializer.ReadUShort();
                    // Skip searchRange, entrySelector and rangeShift
                    deserializer.Seek(deserializer.GetPosition() + 3 * sizeof(unsigned short));

                    for (unsigned j = 0; j < numKerningPairs; ++j)
                    {
                        unsigned leftIndex = deserializer.ReadUShort();
                        unsigned rightIndex = deserializer.ReadUShort();
                        short amount = (short)(deserializer.ReadShort() >> 6);
                        if (leftIndex < numGlyphs && rightIndex < numGlyphs)
                            glyphs_[leftIndex].kerning_[rightIndex] = amount;
                        else
                            LOGWARNING("Out of range glyph index in kerning information");
                    }
                }
                else
                {
                    // Kerning table contains information we do not support; skip and move to the next (length includes header)
                    deserializer.Seek(deserializer.GetPosition() + length - 3 * sizeof(unsigned short));
                }
            }
        }
        else
            LOGWARNING("Can not read kerning information: not version 0");
    }

    // Now try to pack into the smallest possible texture. If face does not fit into one texture, enable dynamic mode where
    // glyphs are only created as necessary
    if (RenderAllGlyphs(maxTextureSize, maxTextureSize))
    {
        FT_Done_Face(face);
        face_ = 0;
    }
    else
    {
        if (ui->GetUseMutableGlyphs())
            SetupMutableGlyphs(maxTextureSize, maxTextureSize, maxWidth, maxHeight);
        else
            SetupNextTexture(maxTextureSize, maxTextureSize);
    }

    return true;
}

const FontGlyph* FontFaceFreeType::GetGlyph(unsigned c)
{
    HashMap<unsigned, unsigned>::ConstIterator i = glyphMapping_.Find(c);
    if (i != glyphMapping_.End())
    {
        FontGlyph& glyph = glyphs_[i->second_];
        // Render glyph if not yet resident in a page texture (FreeType mode only)
        if (glyph.page_ == M_MAX_UNSIGNED)
            RenderGlyph(i->second_);
        // If mutable glyphs in use, move to the front of the list
        if (mutableGlyphs_.Size() && glyph.iterator_ != mutableGlyphs_.End())
        {
            MutableGlyph* mutableGlyph = *glyph.iterator_;
            mutableGlyphs_.Erase(glyph.iterator_);
            mutableGlyphs_.PushFront(mutableGlyph);
            glyph.iterator_ = mutableGlyphs_.Begin();
        }

        glyph.used_ = true;
        return &glyph;
    }
    else
        return 0;
}

bool FontFaceFreeType::RenderAllGlyphs(int maxWidth, int maxHeight)
{
    assert(font_ && face_ && textures_.Empty());

    allocator_ = AreaAllocator(FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MIN_SIZE, maxWidth, maxHeight);

    for (unsigned i = 0; i < glyphs_.Size(); ++i)
    {
        if (glyphs_[i].width_ && glyphs_[i].height_)
        {
            int x, y;
            // Reserve an empty border between glyphs for filtering
            if (allocator_.Allocate(glyphs_[i].width_ + 1, glyphs_[i].height_ + 1, x, y))
            {
                glyphs_[i].x_ = x;
                glyphs_[i].y_ = y;
                glyphs_[i].page_ = 0;
            }
            else
            {
                // When allocation fails, reset the page of all glyphs allocated so far
                for (unsigned j = 0; j <= i; ++j)
                    glyphs_[j].page_ = M_MAX_UNSIGNED;
                return false;
            }
        }
        else
        {
            glyphs_[i].x_ = 0;
            glyphs_[i].y_ = 0;
            glyphs_[i].page_ = 0;
        }
    }

    // Create image for rendering all the glyphs, clear to black
    SharedPtr<Image> image(new Image(font_->GetContext()));
    image->SetSize(allocator_.GetWidth(), allocator_.GetHeight(), 1);
    unsigned char* imageData = image->GetData();
    memset(imageData, 0, image->GetWidth() * image->GetHeight());

    int loadMode = font_->GetSubsystem<UI>()->GetForceAutoHint() ? FT_LOAD_FORCE_AUTOHINT : FT_LOAD_DEFAULT;

    // Render glyphs
    for (unsigned i = 0; i < glyphs_.Size(); ++i)
        RenderGlyphBitmap(i, imageData + glyphs_[i].y_ * image->GetWidth() + glyphs_[i].x_, image->GetWidth(), loadMode);

    // Load image into a texture, increment memory usage of the parent font
    SharedPtr<Texture2D> texture = font_->LoadFaceTexture(image);
    if (!texture)
    {
        for (unsigned i = 0; i < glyphs_.Size(); ++i)
            glyphs_[i].page_ = M_MAX_UNSIGNED;
        return false;
    }

    textures_.Push(texture);
    font_->SetMemoryUse(font_->GetMemoryUse() + image->GetWidth() * image->GetHeight());

    LOGDEBUGF("Font face %s (%dpt) uses a static page texture of size %dx%d", GetFileName(font_->GetName()).CString(), pointSize_, texture->GetWidth(), texture->GetHeight());
    return true;
}

void FontFaceFreeType::RenderGlyph(unsigned index)
{
    assert(font_ && face_);

    FontGlyph& glyph = glyphs_[index];

    // If glyph is empty, just set the current page
    if (!glyph.width_ || !glyph.height_)
    {
        glyph.x_ = 0;
        glyph.y_ = 0;
        glyph.page_ = textures_.Size() - 1;
        return;
    }

    int loadMode = font_->GetSubsystem<UI>()->GetForceAutoHint() ? FT_LOAD_FORCE_AUTOHINT : FT_LOAD_DEFAULT;

    if (!mutableGlyphs_.Size())
    {
        // Not using mutable glyphs: try to allocate from current page, reserve next page if fails
        int x, y;
        if (!allocator_.Allocate(glyph.width_ + 1, glyph.height_ + 1, x, y))
        {
            SetupNextTexture(textures_[0]->GetWidth(), textures_[0]->GetHeight());
            // This always succeeds, as it is the first allocation of an empty page
            allocator_.Allocate(glyph.width_ + 1, glyph.height_ + 1, x, y);
        }

        glyph.x_ = x;
        glyph.y_ = y;
        glyph.page_ = textures_.Size() - 1;

        if (!bitmap_ || (int)bitmapSize_ < glyph.width_ * glyph.height_)
        {
            bitmapSize_ = glyph.width_ * glyph.height_;
            bitmap_ = new unsigned char[bitmapSize_];
        }

        RenderGlyphBitmap(index, bitmap_.Get(), glyph.width_, loadMode);
        textures_.Back()->SetData(0, glyph.x_, glyph.y_, glyph.width_, glyph.height_, bitmap_.Get());
    }
    else
    {
        // Using mutable glyphs: overwrite the least recently used glyph
        List<MutableGlyph*>::Iterator it = --mutableGlyphs_.End();
        MutableGlyph* mutableGlyph = *it;
        if (mutableGlyph->glyphIndex_ != M_MAX_UNSIGNED)
            glyphs_[mutableGlyph->glyphIndex_].page_ = M_MAX_UNSIGNED;
        glyph.x_ = mutableGlyph->x_;
        glyph.y_ = mutableGlyph->y_;
        glyph.page_ = 0;
        glyph.iterator_ = it;
        mutableGlyph->glyphIndex_ = index;

        if (!bitmap_)
        {
            bitmapSize_ = cellWidth_ * cellHeight_;
            bitmap_ = new unsigned char[bitmapSize_];
        }

        // Clear the cell bitmap before rendering to ensure padding
        memset(bitmap_.Get(), 0, cellWidth_ * cellHeight_);
        RenderGlyphBitmap(index, bitmap_.Get(), cellWidth_, loadMode);
        textures_[0]->SetData(0, glyph.x_, glyph.y_, cellWidth_, cellHeight_, bitmap_.Get());
    }
}

void FontFaceFreeType::RenderGlyphBitmap(unsigned index, unsigned char* dest, unsigned pitch, int loadMode)
{
    const FontGlyph& glyph = glyphs_[index];
    if (!glyph.width_ || !glyph.height_)
        return;

    FT_Face face = (FT_Face)face_;
    FT_GlyphSlot slot = face->glyph;
    FT_Load_Glyph(face, index, loadMode);
    FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);

    if (slot->bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
    {
        for (int y = 0; y < slot->bitmap.rows; ++y)
        {
            unsigned char* src = slot->bitmap.buffer + slot->bitmap.pitch * y;
            unsigned char* rowDest = dest + y * pitch;

            for (int x = 0; x < slot->bitmap.width; ++x)
                rowDest[x] = (src[x >> 3] & (0x80 >> (x & 7))) ? 255 : 0;
        }
    }
    else
    {
        for (int y = 0; y < slot->bitmap.rows; ++y)
        {
            unsigned char* src = slot->bitmap.buffer + slot->bitmap.pitch * y;
            unsigned char* rowDest = dest + y * pitch;

            for (int x = 0; x < slot->bitmap.width; ++x)
                rowDest[x] = src[x];
        }
    }
}

void FontFaceFreeType::SetupNextTexture(int width, int height)
{
    // If several dynamic textures are needed, use the maximum size to pack as many as possible to one texture
    allocator_ = AreaAllocator(width, height);

    SharedPtr<Texture2D> texture = font_->CreateFaceTexture();
    texture->SetSize(width, height, Graphics::GetAlphaFormat());
    SharedArrayPtr<unsigned char> emptyBitmap(new unsigned char[width * height]);
    memset(emptyBitmap.Get(), 0, width * height);
    texture->SetData(0, 0, 0, width, height, emptyBitmap.Get());

    textures_.Push(texture);
    font_->SetMemoryUse(font_->GetMemoryUse() + width * height);

    LOGDEBUGF("Font face %s (%dpt) is using %d dynamic page textures of size %dx%d", GetFileName(font_->GetName()).CString(), pointSize_, textures_.Size(), width, height);
}

void FontFaceFreeType::SetupMutableGlyphs(int textureWidth, int textureHeight, int maxWidth, int maxHeight)
{
    assert(mutableGlyphs_.Empty());

    SetupNextTexture(textureWidth, textureHeight);

    cellWidth_ = maxWidth + 1;
    cellHeight_ = maxHeight + 1;

    // Allocate as many mutable glyphs as possible
    int x, y;
    while (allocator_.Allocate(cellWidth_, cellHeight_, x, y))
    {
        MutableGlyph* glyph = new MutableGlyph();
        glyph->x_ = x;
        glyph->y_ = y;
        mutableGlyphs_.Push(glyph);
    }

    LOGDEBUGF("Font face %s (%dpt) is using %d mutable glyphs", GetFileName(font_->GetName()).CString(), pointSize_, mutableGlyphs_.Size());
}

FontFaceBitMap::FontFaceBitMap(Font* font) :
    FontFace(font)
{

}

FontFaceBitMap::~FontFaceBitMap()
{

}

bool FontFaceBitMap::Load(const unsigned char* fontData, unsigned fontDataSize, int pointSize)
{
    Context* context = font_->GetContext();

    SharedPtr<XMLFile> xmlReader(new XMLFile(context));
    MemoryBuffer memoryBuffer(fontData, fontDataSize);
    if (!xmlReader->Load(memoryBuffer))
    {
        LOGERROR("Could not load XML file");
        return false;
    }

    XMLElement root = xmlReader->GetRoot("font");
    if (root.IsNull())
    {
        LOGERROR("Could not find Font element");
        return false;
    }

    XMLElement pagesElem = root.GetChild("pages");
    if (pagesElem.IsNull())
    {
        LOGERROR("Could not find Pages element");
        return false;
    }

    XMLElement infoElem = root.GetChild("info");
    if (!infoElem.IsNull())
        pointSize_ = infoElem.GetInt("size");

    XMLElement commonElem = root.GetChild("common");
    rowHeight_ = commonElem.GetInt("lineHeight");
    unsigned pages = commonElem.GetInt("pages");
    textures_.Reserve(pages);

    ResourceCache* resourceCache = font_->GetSubsystem<ResourceCache>();
    String fontPath = GetPath(font_->GetName());
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
        SharedPtr<Image> fontImage(new Image(context));
        if (!fontFile || !fontImage->Load(*fontFile))
        {
            LOGERROR("Failed to load font image file");
            return 0;
        }
        SharedPtr<Texture2D> texture = font_->LoadFaceTexture(fontImage);
        if (!texture)
            return 0;
        textures_.Push(texture);
        totalTextureSize += fontImage->GetWidth() * fontImage->GetHeight() * fontImage->GetComponents();

        pageElem = pageElem.GetNext("page");
    }

    XMLElement charsElem = root.GetChild("chars");
    int count = charsElem.GetInt("count");
    glyphs_.Reserve(count);
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
        glyphs_.Push(glyph);
        glyphMapping_[id] = index++;

        charElem = charElem.GetNext("char");
    }

    XMLElement kerningsElem = root.GetChild("kernings");
    if (kerningsElem.IsNull())
        hasKerning_ = false;
    else
    {
        XMLElement kerningElem = kerningsElem.GetChild("kerning");
        while (!kerningElem.IsNull())
        {
            int first = kerningElem.GetInt("first");
            HashMap<unsigned, unsigned>::Iterator i = glyphMapping_.Find(first);
            if (i != glyphMapping_.End())
            {
                int second = kerningElem.GetInt("second");
                int amount = kerningElem.GetInt("amount");

                FontGlyph& glyph = glyphs_[i->second_];
                glyph.kerning_[second] = amount;
            }

            kerningElem = kerningElem.GetNext("kerning");
        }
    }

    LOGDEBUGF("Bitmap font face %s has %d glyphs", GetFileName(font_->GetName()).CString(), count);

    font_->SetMemoryUse(font_->GetMemoryUse() + totalTextureSize);
    return true;
}

}
