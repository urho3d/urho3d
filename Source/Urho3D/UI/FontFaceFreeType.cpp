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

#include "../Core/Context.h"
#include "../IO/FileSystem.h"
#include "../UI/Font.h"
#include "../UI/FontFaceFreeType.h"
#include "../Graphics/Graphics.h"
#include "../Resource/Image.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../Graphics/Texture2D.h"
#include "../UI/UI.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_TRUETYPE_TABLES_H

#include "../DebugNew.h"

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

FontFaceFreeType::FontFaceFreeType(Font* font) :
FontFace(font),
    face_(0)
{

}

FontFaceFreeType::~FontFaceFreeType()
{
    if (face_)
    {
        FT_Done_Face((FT_Face)face_);
        face_ = 0;
    }
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

    FT_UInt glyphIndex;
    unsigned numGlyphs = 0;
    HashMap<unsigned, unsigned> indexToCharMapping;

    FT_ULong charCode = FT_Get_First_Char(face, &glyphIndex);
    while (glyphIndex != 0)
    {
        numGlyphs = Max((int)glyphIndex + 1, (int)numGlyphs);
        indexToCharMapping[glyphIndex] = charCode;
        charCode = FT_Get_Next_Char(face, charCode, &glyphIndex);
    }

    LOGDEBUGF("Font face %s (%dpt) has %d glyphs", GetFileName(font_->GetName()).CString(), pointSize, numGlyphs);

    // Load each of the glyphs to see the sizes & store other information
    int loadMode = ui->GetForceAutoHint() ? FT_LOAD_FORCE_AUTOHINT : FT_LOAD_DEFAULT;
    ascender_ = face->size->metrics.ascender >> 6;
    int descender = face->size->metrics.descender >> 6;

    // Check if the font's OS/2 info gives different (larger) values for ascender & descender
    TT_OS2* os2Info = (TT_OS2*)FT_Get_Sfnt_Table(face, ft_sfnt_os2);
    if (os2Info)
    {
        ascender_ = Max(ascender_, os2Info->usWinAscent * face->size->metrics.y_ppem / face->units_per_EM);
        ascender_ = Max(ascender_, os2Info->sTypoAscender * face->size->metrics.y_ppem / face->units_per_EM);
        descender = Max(descender, os2Info->usWinDescent * face->size->metrics.y_ppem / face->units_per_EM);
        descender = Max(descender, os2Info->sTypoDescender * face->size->metrics.y_ppem / face->units_per_EM);
    }

    // Store point size and row height. Use the maximum of ascender + descender, or the face's stored default row height
    pointSize_ = pointSize;
    rowHeight_ = Max(ascender_ + descender, face->size->metrics.height >> 6);

    int textureWidth = maxTextureSize;
    int textureHeight = maxTextureSize;
    bool loadAllGlyphs = CanLoadAllGlyphs(numGlyphs, loadMode, textureWidth, textureHeight);

    SharedPtr<Image> image(new Image(font_->GetContext()));
    image->SetSize(textureWidth, textureHeight, 1);
    unsigned char* imageData = image->GetData();
    memset(imageData, 0, image->GetWidth() * image->GetHeight());
    allocator_.Reset(FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MIN_SIZE, textureWidth, textureHeight);

    for (unsigned i = 0; i < numGlyphs; ++i)
    {
        unsigned charCode = indexToCharMapping[i];
        if (!loadAllGlyphs && (charCode > 0xff))
            break;

        if (!LoadCharGlyph(charCode, image))
            return false;
    }

    SharedPtr<Texture2D> texture = LoadFaceTexture(image);
    if (!texture)
        return false;

    textures_.Push(texture);
    font_->SetMemoryUse(font_->GetMemoryUse() + textureWidth * textureHeight);

    // Store kerning if face has kerning information
    if (FT_HAS_KERNING(face))
    {
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

                        HashMap<unsigned, unsigned>::ConstIterator leftIter = indexToCharMapping.Find(leftIndex);
                        HashMap<unsigned, unsigned>::ConstIterator rightIter = indexToCharMapping.Find(rightIndex);
                        if (leftIter != indexToCharMapping.End() && rightIter != indexToCharMapping.End())
                        {
                            unsigned value = (leftIter->second_ << 16) + rightIter->second_;
                            kerningMapping_[value] = amount;
                        }
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

    if (loadAllGlyphs)
    {
        FT_Done_Face(face);
        face_ = 0;
        hasMutableGlyph_ = false;
    }
    else
        hasMutableGlyph_ = true;

    return true;
}

const FontGlyph* FontFaceFreeType::GetGlyph(unsigned c)
{
    HashMap<unsigned, FontGlyph>::Iterator i = glyphMapping_.Find(c);
    if (i != glyphMapping_.End())
    {
        FontGlyph& glyph = i->second_;
        glyph.used_ = true;
        return &glyph;
    }

    if (LoadCharGlyph(c))
    {
        HashMap<unsigned, FontGlyph>::Iterator i = glyphMapping_.Find(c);
        if (i != glyphMapping_.End())
        {
            FontGlyph& glyph = i->second_;
            glyph.used_ = true;
            return &glyph;
        }
    }

    return 0;
}

bool FontFaceFreeType::CanLoadAllGlyphs(unsigned numGlyphs, int loadMode, int& textureWidth, int& textureHeight) const
{
    FT_Face face = (FT_Face)face_;
    FT_GlyphSlot slot = face->glyph;
    AreaAllocator allocator(FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MIN_SIZE, textureWidth, textureHeight);

    for (unsigned i = 0; i < numGlyphs; ++i)
    {
        FT_Error error = FT_Load_Glyph(face, i, loadMode);
        if (!error)
        {
            int width = Max(slot->metrics.width >> 6, slot->bitmap.width);
            int height = Max(slot->metrics.height >> 6, slot->bitmap.rows);
            int x, y;
            if (!allocator.Allocate(width + 1, height + 1, x, y))
                return false;
        }
    }

    textureWidth = allocator.GetWidth();
    textureHeight = allocator.GetHeight();
    return true;
}

bool FontFaceFreeType::SetupNextTexture(int textureWidth, int textureHeight)
{
    SharedPtr<Image> image(new Image(font_->GetContext()));
    image->SetSize(textureWidth, textureHeight, 1);
    unsigned char* imageData = image->GetData();
    memset(imageData, 0, image->GetWidth() * image->GetHeight());

    SharedPtr<Texture2D> texture = LoadFaceTexture(image);
    if (!texture)
        return false;

    textures_.Push(texture);
    allocator_.Reset(FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MIN_SIZE, textureWidth, textureHeight);

    font_->SetMemoryUse(font_->GetMemoryUse() + textureWidth * textureHeight);

    return true;
}

bool FontFaceFreeType::LoadCharGlyph(unsigned charCode, Image* image)
{
    if (!face_)
        return false;

    FT_Face face = (FT_Face)face_;
    FT_GlyphSlot slot = face->glyph;

    UI* ui = font_->GetSubsystem<UI>();
    int loadMode = ui->GetForceAutoHint() ? FT_LOAD_FORCE_AUTOHINT : FT_LOAD_DEFAULT;

    FontGlyph fontGlyph;
    FT_Error error = FT_Load_Char(face, charCode, loadMode);
    if (!error)
    {
        // Note: position within texture will be filled later
        fontGlyph.width_ = (short)Max(slot->metrics.width >> 6, slot->bitmap.width);
        fontGlyph.height_ = (short)Max(slot->metrics.height >> 6, slot->bitmap.rows);
        fontGlyph.offsetX_ = (short)(slot->metrics.horiBearingX >> 6);
        fontGlyph.offsetY_ = (short)(ascender_ - (slot->metrics.horiBearingY >> 6));
        fontGlyph.advanceX_ = (short)(slot->metrics.horiAdvance >> 6);

        if (fontGlyph.width_ > 0 && fontGlyph.height_ > 0)
        {
            int x, y;
            if (!allocator_.Allocate(fontGlyph.width_ + 1, fontGlyph.height_ + 1, x, y))
            {
                int textureSize = ui->GetMaxFontTextureSize();
                if (!SetupNextTexture(textureSize, textureSize))
                    return false;

                if (!allocator_.Allocate(fontGlyph.width_ + 1, fontGlyph.height_ + 1, x, y))
                    return false;
            }

            fontGlyph.x_ = x;
            fontGlyph.y_ = y;

            unsigned char* dest = 0;
            unsigned pitch = 0;
            if (image)
            {
                fontGlyph.page_ = 0;
                dest = image->GetData() + fontGlyph.y_ * image->GetWidth() + fontGlyph.x_;
                pitch = image->GetWidth();
            }
            else
            {
                fontGlyph.page_ = textures_.Size() - 1;
                dest = new unsigned char[fontGlyph.width_ * fontGlyph.height_];
                pitch = fontGlyph.width_;
            }

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

            if (!image)
            {
                textures_.Back()->SetData(0, fontGlyph.x_, fontGlyph.y_, fontGlyph.width_, fontGlyph.height_, dest);
                delete [] dest;
            }
        }
        else
        {
            fontGlyph.x_ = 0;
            fontGlyph.y_ = 0;
            fontGlyph.page_ = 0;
        }
    }
    else
    {
        fontGlyph.width_ = 0;
        fontGlyph.height_ = 0;
        fontGlyph.offsetX_ = 0;
        fontGlyph.offsetY_ = 0;
        fontGlyph.advanceX_ = 0;
        fontGlyph.page_ = 0;
    }

    glyphMapping_[charCode] = fontGlyph;

    return true;
}



}
