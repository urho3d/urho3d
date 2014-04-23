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
#include "File.h"
#include "FileSystem.h"
#include "Font.h"
#include "FontFaceBitMap.h"
#include "Graphics.h"
#include "Image.h"
#include "Log.h"
#include "MemoryBuffer.h"
#include "ResourceCache.h"
#include "Texture2D.h"
#include "UI.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

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
        SharedPtr<Texture2D> texture = LoadFaceTexture(fontImage);
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

bool FontFaceBitMap::Load(FontFace* fontFace, bool usedGlyphs)
{
    Context* context = font_->GetContext();
    int maxTextureSize = font_->GetSubsystem<UI>()->GetMaxFontTextureSize();

    // Clone properties
    pointSize_ = fontFace->pointSize_;
    rowHeight_ = fontFace->rowHeight_;
    hasKerning_ = fontFace->hasKerning_;

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

            glyphs_.Push(glyph);
            glyphMapping_[i->first_] = index++;
        }

        int texWidth = allocator.GetWidth();
        int texHeight = allocator.GetHeight();

        // Create the image for rendering the fonts
        SharedPtr<Image> image(new Image(context));
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

            FontGlyph packedGlyph = glyphs_[startIndex++];

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
            return false;
        textures_.Push(texture);

        ++page;
        startIter = i;
        assert(index == startIndex);
    }

    return true;
}

bool FontFaceBitMap::Save(Serializer& dest, int pointSize)
{
    Context* context = font_->GetContext();

    SharedPtr<XMLFile> xml(new XMLFile(context));
    XMLElement rootElem = xml->CreateRoot("font");

    // Information
    XMLElement childElem = rootElem.CreateChild("info");
    String fileName = GetFileName(font_->GetName());
    childElem.SetAttribute("face", fileName);
    childElem.SetAttribute("size", String(pointSize));

    // Common
    childElem = rootElem.CreateChild("common");
    childElem.SetInt("lineHeight", rowHeight_);
    unsigned pages = textures_.Size();
    childElem.SetInt("pages", pages);

    // Construct the path to store the texture
    String pathName;
    File* file = dynamic_cast<File*>(&dest);
    if (file)
        // If serialize to file, use the file's path
            pathName = GetPath(file->GetName());
    else
        // Otherwise, use the font resource's path
        pathName = "Data/" + GetPath(font_->GetName());

    // Pages
    childElem = rootElem.CreateChild("pages");
    for (unsigned i = 0; i < pages; ++i)
    {
        XMLElement pageElem = childElem.CreateChild("page");
        pageElem.SetInt("id", i);
        String texFileName = fileName + "_" + String(i) + ".png";
        pageElem.SetAttribute("file", texFileName);

        // Save the font face texture to image file
        SaveFaceTexture(textures_[i], pathName + texFileName);
    }

    // Chars and kernings
    XMLElement charsElem = rootElem.CreateChild("chars");
    unsigned numGlyphs = glyphs_.Size();
    charsElem.SetInt("count", numGlyphs);
    XMLElement kerningsElem;
    bool hasKerning = hasKerning_;
    if (hasKerning)
        kerningsElem = rootElem.CreateChild("kernings");
    for (HashMap<unsigned, unsigned>::ConstIterator i = glyphMapping_.Begin(); i != glyphMapping_.End(); ++i)
    {
        // Char
        XMLElement charElem = charsElem.CreateChild("char");
        charElem.SetInt("id", i->first_);
        FontGlyph glyph = glyphs_[i->second_];
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

unsigned FontFaceBitMap::ConvertFormatToNumComponents(unsigned format)
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


SharedPtr<Image> FontFaceBitMap::SaveFaceTexture(Texture2D* texture)
{
    Image* image = new Image(font_->GetContext());
    image->SetSize(texture->GetWidth(), texture->GetHeight(), ConvertFormatToNumComponents(texture->GetFormat()));
    if (!static_cast<Texture2D*>(texture)->GetData(0, image->GetData()))
    {
        delete image;
        LOGERROR("Could not save texture to image resource");
        return SharedPtr<Image>();
    }
    return SharedPtr<Image>(image);
}

bool FontFaceBitMap::SaveFaceTexture(Texture2D* texture, const String& fileName)
{
    SharedPtr<Image> image = SaveFaceTexture(texture);
    return image ? image->SavePNG(fileName) : false;
}

}
