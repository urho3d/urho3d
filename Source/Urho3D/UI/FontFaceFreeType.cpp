//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Texture2D.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../UI/Font.h"
#include "../UI/FontFaceFreeType.h"
#include "../UI/UI.h"

#include <cassert>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_TRUETYPE_TABLES_H

#include "../DebugNew.h"

namespace Urho3D
{

inline float FixedToFloat(FT_Pos value)
{
    return value / 64.0f;
}

/// FreeType library subsystem.
class FreeTypeLibrary : public Object
{
    URHO3D_OBJECT(FreeTypeLibrary, Object);

public:
    /// Construct.
    explicit FreeTypeLibrary(Context* context) :
        Object(context)
    {
        FT_Error error = FT_Init_FreeType(&library_);
        if (error)
            URHO3D_LOGERROR("Could not initialize FreeType library");
    }

    /// Destruct.
    ~FreeTypeLibrary() override
    {
        FT_Done_FreeType(library_);
    }

    FT_Library GetLibrary() const { return library_; }

private:
    /// FreeType library.
    FT_Library library_{};
};

FontFaceFreeType::FontFaceFreeType(Font* font) :
    FontFace(font),
    loadMode_(FT_LOAD_DEFAULT)
{
}

FontFaceFreeType::~FontFaceFreeType()
{
    if (face_)
    {
        FT_Done_Face((FT_Face)face_);
        face_ = nullptr;
    }
}

bool FontFaceFreeType::Load(const unsigned char* fontData, unsigned fontDataSize, float pointSize)
{
    Context* context = font_->GetContext();

    // Create & initialize FreeType library if it does not exist yet
    auto* freeType = font_->GetSubsystem<FreeTypeLibrary>();
    if (!freeType)
        context->RegisterSubsystem(freeType = new FreeTypeLibrary(context));

    // Ensure the FreeType library is kept alive as long as TTF font resources exist
    freeType_ = freeType;

    auto* ui = font_->GetSubsystem<UI>();
    const int maxTextureSize = ui->GetMaxFontTextureSize();
    const FontHintLevel hintLevel = ui->GetFontHintLevel();
    const float subpixelThreshold = ui->GetFontSubpixelThreshold();

    subpixel_ = (hintLevel <= FONT_HINT_LEVEL_LIGHT) && (pointSize <= subpixelThreshold);
    oversampling_ = subpixel_ ? ui->GetFontOversampling() : 1;

    FT_Face face;
    FT_Error error;
    FT_Library library = freeType->GetLibrary();

    if (pointSize <= 0)
    {
        URHO3D_LOGERROR("Zero or negative point size");
        return false;
    }

    if (!fontDataSize)
    {
        URHO3D_LOGERROR("Could not create font face from zero size data");
        return false;
    }

    error = FT_New_Memory_Face(library, fontData, fontDataSize, 0, &face);
    if (error)
    {
        URHO3D_LOGERROR("Could not create font face");
        return false;
    }
    error = FT_Set_Char_Size(face, 0, pointSize * 64, oversampling_ * FONT_DPI, FONT_DPI);
    if (error)
    {
        FT_Done_Face(face);
        URHO3D_LOGERROR("Could not set font point size " + String(pointSize));
        return false;
    }

    face_ = face;

    auto numGlyphs = (unsigned)face->num_glyphs;
    URHO3D_LOGDEBUGF("Font face %s (%fpt) has %d glyphs", GetFileName(font_->GetName()).CString(), pointSize, numGlyphs);

    PODVector<unsigned> charCodes(numGlyphs + 1, 0);

    // Attempt to load space glyph first regardless if it's listed or not
    // In some fonts (Consola) it is missing
    charCodes[0] = 32;

    FT_UInt glyphIndex;
    FT_ULong charCode = FT_Get_First_Char(face, &glyphIndex);
    while (glyphIndex != 0)
    {
        if (glyphIndex < numGlyphs)
            charCodes[glyphIndex + 1] = (unsigned)charCode;

        charCode = FT_Get_Next_Char(face, charCode, &glyphIndex);
    }

    // Load each of the glyphs to see the sizes & store other information
    loadMode_ = FT_LOAD_DEFAULT;
    if (ui->GetForceAutoHint())
    {
        loadMode_ |= FT_LOAD_FORCE_AUTOHINT;
    }
    if (ui->GetFontHintLevel() == FONT_HINT_LEVEL_NONE)
    {
        loadMode_ |= FT_LOAD_NO_HINTING;
    }
    if (ui->GetFontHintLevel() == FONT_HINT_LEVEL_LIGHT)
    {
        loadMode_ |= FT_LOAD_TARGET_LIGHT;
    }

    ascender_ = FixedToFloat(face->size->metrics.ascender);
    rowHeight_ = FixedToFloat(face->size->metrics.height);
    pointSize_ = pointSize;

    // Check if the font's OS/2 info gives different (larger) values for ascender & descender
    auto* os2Info = (TT_OS2*)FT_Get_Sfnt_Table(face, ft_sfnt_os2);
    if (os2Info)
    {
        float descender = FixedToFloat(face->size->metrics.descender);
        float unitsPerEm = face->units_per_EM;
        ascender_ = Max(ascender_, os2Info->usWinAscent * face->size->metrics.y_ppem / unitsPerEm);
        ascender_ = Max(ascender_, os2Info->sTypoAscender * face->size->metrics.y_ppem / unitsPerEm);
        descender = Max(descender, os2Info->usWinDescent * face->size->metrics.y_ppem / unitsPerEm);
        descender = Max(descender, os2Info->sTypoDescender * face->size->metrics.y_ppem / unitsPerEm);
        rowHeight_ = Max(rowHeight_, ascender_ + descender);
    }

    int textureWidth = maxTextureSize;
    int textureHeight = maxTextureSize;
    hasMutableGlyph_ = false;

    SharedPtr<Image> image(new Image(font_->GetContext()));
    image->SetSize(textureWidth, textureHeight, 1);
    unsigned char* imageData = image->GetData();
    memset(imageData, 0, (size_t)image->GetWidth() * image->GetHeight());
    allocator_.Reset(FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MIN_SIZE, textureWidth, textureHeight);

    for (unsigned i = 0; i < charCodes.Size(); ++i)
    {
        unsigned charCode = charCodes[i];
        if (charCode == 0)
            continue;

        if (!LoadCharGlyph(charCode, image))
        {
            hasMutableGlyph_ = true;
            break;
        }
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
        FT_ULong tagKern = FT_MAKE_TAG('k', 'e', 'r', 'n');
        FT_ULong kerningTableSize = 0;
        FT_Error error = FT_Load_Sfnt_Table(face, tagKern, 0, nullptr, &kerningTableSize);
        if (error)
        {
            URHO3D_LOGERROR("Could not get kerning table length");
            return false;
        }

        SharedArrayPtr<unsigned char> kerningTable(new unsigned char[kerningTableSize]);
        error = FT_Load_Sfnt_Table(face, tagKern, 0, kerningTable, &kerningTableSize);
        if (error)
        {
            URHO3D_LOGERROR("Could not load kerning table");
            return false;
        }

        // Convert big endian to little endian
        for (unsigned i = 0; i < kerningTableSize; i += 2)
            Swap(kerningTable[i], kerningTable[i + 1]);
        MemoryBuffer deserializer(kerningTable, (unsigned)kerningTableSize);

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
                    deserializer.Seek((unsigned)(deserializer.GetPosition() + 3 * sizeof(unsigned short)));

                    // x_scale is a 16.16 fixed-point value that converts font units -> 26.6 pixels (oversampled!)
                    auto xScale = (float)face->size->metrics.x_scale / (1u << 22u) / oversampling_;

                    for (unsigned j = 0; j < numKerningPairs; ++j)
                    {
                        unsigned leftIndex = deserializer.ReadUShort();
                        unsigned rightIndex = deserializer.ReadUShort();
                        float amount = deserializer.ReadShort() * xScale;

                        unsigned leftCharCode = leftIndex < numGlyphs ? charCodes[leftIndex + 1] : 0;
                        unsigned rightCharCode = rightIndex < numGlyphs ? charCodes[rightIndex + 1] : 0;
                        if (leftCharCode != 0 && rightCharCode != 0)
                        {
                            unsigned value = (leftCharCode << 16u) + rightCharCode;
                            kerningMapping_[value] = amount;
                        }
                    }
                }
                else
                {
                    // Kerning table contains information we do not support; skip and move to the next (length includes header)
                    deserializer.Seek((unsigned)(deserializer.GetPosition() + length - 3 * sizeof(unsigned short)));
                }
            }
        }
        else
            URHO3D_LOGWARNING("Can not read kerning information: not version 0");
    }

    if (!hasMutableGlyph_)
    {
        FT_Done_Face(face);
        face_ = nullptr;
    }

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

    return nullptr;
}

bool FontFaceFreeType::SetupNextTexture(int textureWidth, int textureHeight)
{
    SharedPtr<Image> image(new Image(font_->GetContext()));
    image->SetSize(textureWidth, textureHeight, 1);
    unsigned char* imageData = image->GetData();
    memset(imageData, 0, (size_t)image->GetWidth() * image->GetHeight());

    SharedPtr<Texture2D> texture = LoadFaceTexture(image);
    if (!texture)
        return false;

    textures_.Push(texture);
    allocator_.Reset(FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MIN_SIZE, textureWidth, textureHeight);

    font_->SetMemoryUse(font_->GetMemoryUse() + textureWidth * textureHeight);

    return true;
}

void FontFaceFreeType::BoxFilter(unsigned char* dest, size_t destSize, const unsigned char* src, size_t srcSize)
{
    const int filterSize = oversampling_;

    assert(filterSize > 0);
    assert(destSize == srcSize + filterSize - 1);

    if (filterSize == 1)
    {
        memcpy(dest, src, srcSize);
        return;
    }

    // "accumulator" holds the total value of filterSize samples. We add one sample
    // and remove one sample per step (with special cases for left and right edges).
    int accumulator = 0;

    // The divide might make these inner loops slow. If so, some possible optimizations:
    // a) Turn it into a fixed-point multiply-and-shift rather than an integer divide;
    // b) Make this function a template, with the filter size a compile-time constant.

    int i = 0;

    if (srcSize < filterSize)
    {
        for (; i < srcSize; ++i)
        {
            accumulator += src[i];
            dest[i] = accumulator / filterSize;
        }

        for (; i < filterSize; ++i)
        {
            dest[i] = accumulator / filterSize;
        }
    }
    else
    {
        for ( ; i < filterSize; ++i)
        {
            accumulator += src[i];
            dest[i] = accumulator / filterSize;
        }

        for (; i < srcSize; ++i)
        {
            accumulator += src[i];
            accumulator -= src[i - filterSize];
            dest[i] = accumulator / filterSize;
        }
    }

    for (; i < srcSize + filterSize - 1; ++i)
    {
        accumulator -= src[i - filterSize];
        dest[i] = accumulator / filterSize;
    }
}

bool FontFaceFreeType::LoadCharGlyph(unsigned charCode, Image* image)
{
    if (!face_)
        return false;

    auto face = (FT_Face)face_;
    FT_GlyphSlot slot = face->glyph;

    FontGlyph fontGlyph;
    FT_Error error = FT_Load_Char(face, charCode, loadMode_ | FT_LOAD_RENDER);
    if (error)
    {
        const char* family = face->family_name ? face->family_name : "NULL";
        URHO3D_LOGERRORF("FT_Load_Char failed (family: %s, char code: %u)", family, charCode);
        fontGlyph.texWidth_ = 0;
        fontGlyph.texHeight_ = 0;
        fontGlyph.width_ = 0;
        fontGlyph.height_ = 0;
        fontGlyph.offsetX_ = 0;
        fontGlyph.offsetY_ = 0;
        fontGlyph.advanceX_ = 0;
        fontGlyph.page_ = 0;
    }
    else
    {
        // Note: position within texture will be filled later
        fontGlyph.texWidth_ = slot->bitmap.width + oversampling_ - 1;
        fontGlyph.texHeight_ = slot->bitmap.rows;
        fontGlyph.width_ = slot->bitmap.width + oversampling_ - 1;
        fontGlyph.height_ = slot->bitmap.rows;
        fontGlyph.offsetX_ = slot->bitmap_left - (oversampling_ - 1) / 2.0f;
        fontGlyph.offsetY_ = floorf(ascender_ + 0.5f) - slot->bitmap_top;

        if (subpixel_ && slot->linearHoriAdvance)
        {
            // linearHoriAdvance is stored in 16.16 fixed point, not the usual 26.6
            fontGlyph.advanceX_ = slot->linearHoriAdvance / 65536.0;
        }
        else
        {
            // Round to nearest pixel (only necessary when hinting is disabled)
            fontGlyph.advanceX_ = floorf(FixedToFloat(slot->metrics.horiAdvance) + 0.5f);
        }

        fontGlyph.width_ /= oversampling_;
        fontGlyph.offsetX_ /= oversampling_;
        fontGlyph.advanceX_ /= oversampling_;
    }

    int x = 0, y = 0;
    if (fontGlyph.texWidth_ > 0 && fontGlyph.texHeight_ > 0)
    {
        if (!allocator_.Allocate(fontGlyph.texWidth_ + 1, fontGlyph.texHeight_ + 1, x, y))
        {
            if (image)
            {
                // We're rendering into a fixed image and we ran out of room.
                return false;
            }

            int w = allocator_.GetWidth();
            int h = allocator_.GetHeight();
            if (!SetupNextTexture(w, h))
            {
                URHO3D_LOGWARNINGF("FontFaceFreeType::LoadCharGlyph: failed to allocate new %dx%d texture", w, h);
                return false;
            }

            if (!allocator_.Allocate(fontGlyph.texWidth_ + 1, fontGlyph.texHeight_ + 1, x, y))
            {
                URHO3D_LOGWARNINGF("FontFaceFreeType::LoadCharGlyph: failed to position char code %u in blank page", charCode);
                return false;
            }
        }

        fontGlyph.x_ = (short)x;
        fontGlyph.y_ = (short)y;

        unsigned char* dest = nullptr;
        unsigned pitch = 0;
        if (image)
        {
            fontGlyph.page_ = 0;
            dest = image->GetData() + fontGlyph.y_ * image->GetWidth() + fontGlyph.x_;
            pitch = (unsigned)image->GetWidth();
        }
        else
        {
            fontGlyph.page_ = textures_.Size() - 1;
            dest = new unsigned char[fontGlyph.texWidth_ * fontGlyph.texHeight_];
            pitch = (unsigned)fontGlyph.texWidth_;
        }

        if (slot->bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
        {
            for (unsigned y = 0; y < (unsigned)slot->bitmap.rows; ++y)
            {
                unsigned char* src = slot->bitmap.buffer + slot->bitmap.pitch * y;
                unsigned char* rowDest = dest + (oversampling_ - 1)/2 + y * pitch;

                // Don't do any oversampling, just unpack the bits directly.
                for (unsigned x = 0; x < (unsigned)slot->bitmap.width; ++x)
                    rowDest[x] = (unsigned char)((src[x >> 3u] & (0x80u >> (x & 7u))) ? 255 : 0);
            }
        }
        else
        {
            for (unsigned y = 0; y < (unsigned)slot->bitmap.rows; ++y)
            {
                unsigned char* src = slot->bitmap.buffer + slot->bitmap.pitch * y;
                unsigned char* rowDest = dest + y * pitch;
                BoxFilter(rowDest, fontGlyph.texWidth_, src, slot->bitmap.width);
            }
        }

        if (!image)
        {
            textures_.Back()->SetData(0, fontGlyph.x_, fontGlyph.y_, fontGlyph.texWidth_, fontGlyph.texHeight_, dest);
            delete[] dest;
        }
    }
    else
    {
        fontGlyph.x_ = 0;
        fontGlyph.y_ = 0;
        fontGlyph.page_ = 0;
    }

    glyphMapping_[charCode] = fontGlyph;

    return true;
}

}
