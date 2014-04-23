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
    SharedPtr<FontFace> newFace(new FontFaceFreeType(this));
    if (!newFace->Load(&fontData_[0], fontDataSize_, pointSize))
        return 0;

    faces_[pointSize] = newFace;
    return newFace;
}

FontFace* Font::GetFaceBitmap(int pointSize)
{
    SharedPtr<FontFace> newFace(new FontFaceBitMap(this));
    if (!newFace->Load(&fontData_[0], fontDataSize_, pointSize))
        return 0;
    
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
    SharedPtr<FontFace> packedFontFace(new FontFaceBitMap((Font*)0));

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
