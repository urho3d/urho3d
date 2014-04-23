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
#include "Deserializer.h"
#include "FileSystem.h"
#include "Font.h"
#include "FontFace.h"
#include "Graphics.h"
#include "Log.h"
#include "MemoryBuffer.h"
#include "Profiler.h"
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

Font::Font(Context* context) :
    Resource(context),
    fontDataSize_(0),
    fontType_(FONT_NONE)
{
}

Font::~Font()
{
    // To ensure FreeType deallocates properly, first clear all faces, then release the raw font data
    ReleaseFaces();
    fontData_.Reset();
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

    fontType_ = FONT_NONE;
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
    if (ext == ".ttf" || ext == ".otf" || ext == ".woff")
        fontType_ = FONT_FREETYPE;
    else if (ext == ".xml" || ext == ".fnt")
        fontType_ = FONT_BITMAP;

    SetMemoryUse(fontDataSize_);
    return true;
}

bool Font::SaveXML(Serializer& dest, int pointSize, bool usedGlyphs)
{
    FontFace* fontFace = GetFace(pointSize);
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

FontFace* Font::GetFace(int pointSize)
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
    case FONT_FREETYPE:
        return GetFaceFreeType(pointSize);

    case FONT_BITMAP:
        return GetFaceBitmap(pointSize);

    default:
        return 0;
    }
}

void Font::ReleaseFaces()
{
    faces_.Clear();
}

SharedPtr<Texture2D> Font::CreateFaceTexture()
{
    SharedPtr<Texture2D> texture(new Texture2D(context_));
    texture->SetMipsToSkip(QUALITY_LOW, 0); // No quality reduction
    texture->SetNumLevels(1); // No mipmaps
    texture->SetAddressMode(COORD_U, ADDRESS_BORDER);
    texture->SetAddressMode(COORD_V, ADDRESS_BORDER),
    texture->SetBorderColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
    return texture;
}

SharedPtr<Texture2D> Font::LoadFaceTexture(SharedPtr<Image> image)
{
    SharedPtr<Texture2D> texture = CreateFaceTexture();
    if (!texture->Load(image, true))
    {
        LOGERROR("Could not load texture from image resource");
        return SharedPtr<Texture2D>();
    }
    return texture;
}

FontFace* Font::GetFaceFreeType(int pointSize)
{
    // Create & initialize FreeType library if it does not exist yet
    FreeTypeLibrary* freeType = GetSubsystem<FreeTypeLibrary>();
    if (!freeType)
        context_->RegisterSubsystem(freeType = new FreeTypeLibrary(context_));
    // Ensure the FreeType library is kept alive as long as TTF font resources exist
    freeType_ = freeType;

    UI* ui = GetSubsystem<UI>();
    int maxTextureSize = ui->GetMaxFontTextureSize();

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
        LOGERROR("Could not create font face from zero size data");
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

    SharedPtr<FontFace> newFace(new FontFace(this));
    newFace->face_ = face;

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

    LOGDEBUGF("Font face %s (%dpt) has %d glyphs", GetFileName(GetName()).CString(), pointSize, numGlyphs);

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
    newFace->pointSize_ = pointSize;
    newFace->rowHeight_ = Max(ascender + descender, face->size->metrics.height >> 6);

    newFace->glyphs_.Reserve(numGlyphs);

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

        newFace->glyphs_.Push(newGlyph);
    }

    // Store kerning if face has kerning information
    if (FT_HAS_KERNING(face))
    {
        newFace->hasKerning_ = true;

        // Read kerning manually to be more efficient and avoid out of memory crash when use large font file, for example there
        // are 29354 glyphs in msyh.ttf
        FT_ULong tag = FT_MAKE_TAG('k', 'e', 'r', 'n');
        FT_ULong kerningTableSize = 0;
        FT_Error error = FT_Load_Sfnt_Table(face, tag, 0, NULL, &kerningTableSize);
        if (error)
        {
            LOGERROR("Could not get kerning table length");
            return 0;
        }

        SharedArrayPtr<unsigned char> kerningTable(new unsigned char[kerningTableSize]);
        error = FT_Load_Sfnt_Table(face, tag, 0, kerningTable, &kerningTableSize);
        if (error)
        {
            LOGERROR("Could not load kerning table");
            return 0;
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
                            newFace->glyphs_[leftIndex].kerning_[rightIndex] = amount;
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
    if (newFace->RenderAllGlyphs(maxTextureSize, maxTextureSize))
    {
        FT_Done_Face(face);
        newFace->face_ = 0;
    }
    else
    {
        if (ui->GetUseMutableGlyphs())
            newFace->SetupMutableGlyphs(maxTextureSize, maxTextureSize, maxWidth, maxHeight);
        else
            newFace->SetupNextTexture(maxTextureSize, maxTextureSize);
    }

    faces_[pointSize] = newFace;
    return newFace;
}

FontFace* Font::GetFaceBitmap(int pointSize)
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

    SharedPtr<FontFace> newFace(new FontFace(this));

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
        SharedPtr<Texture2D> texture = LoadFaceTexture(fontImage);
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

    LOGDEBUGF("Bitmap font face %s has %d glyphs", GetFileName(GetName()).CString(), count);

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

SharedPtr<FontFace> Font::Pack(FontFace* fontFace)
{
    // Set parent font as null for the packed face so that it does not attempt to manage the font's total memory use
    SharedPtr<FontFace> packedFontFace(new FontFace((Font*)0));

    int maxTextureSize = GetSubsystem<UI>()->GetMaxFontTextureSize();

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
        AreaAllocator allocator(FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MIN_SIZE, maxTextureSize, maxTextureSize);
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
        SharedPtr<Texture2D> texture = LoadFaceTexture(image);
        if (!texture)
            return SharedPtr<FontFace>();
        packedFontFace->textures_.Push(texture);

        ++page;
        startIter = i;
        assert(index == startIndex);
    }

    return packedFontFace;
}

SharedPtr<Image> Font::SaveFaceTexture(Texture2D* texture)
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

bool Font::SaveFaceTexture(Texture2D* texture, const String& fileName)
{
    SharedPtr<Image> image = SaveFaceTexture(texture);
    return image ? image->SavePNG(fileName) : false;
}

}
