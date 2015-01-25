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
#include "../IO/File.h"
#include "../IO/FileSystem.h"
#include "../UI/Font.h"
#include "../UI/FontFaceBitmap.h"
#include "../Graphics/Graphics.h"
#include "../Resource/Image.h"
#include "../IO/Log.h"
#include "../IO/MemoryBuffer.h"
#include "../Resource/ResourceCache.h"
#include "../Graphics/Texture2D.h"
#include "../UI/UI.h"
#include "../Resource/XMLFile.h"

#include "../DebugNew.h"

namespace Urho3D
{

FontFaceBitmap::FontFaceBitmap(Font* font) :
    FontFace(font)
{
}

FontFaceBitmap::~FontFaceBitmap()
{
}

bool FontFaceBitmap::Load(const unsigned char* fontData, unsigned fontDataSize, int pointSize)
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

        // Add texture to resource cache
        texture->SetName(fontFile->GetName());
        resourceCache->AddManualResource(texture);

        totalTextureSize += fontImage->GetWidth() * fontImage->GetHeight() * fontImage->GetComponents();

        pageElem = pageElem.GetNext("page");
    }

    XMLElement charsElem = root.GetChild("chars");
    int count = charsElem.GetInt("count");

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

        glyphMapping_[id] = glyph;

        charElem = charElem.GetNext("char");
    }

    XMLElement kerningsElem = root.GetChild("kernings");
    if (kerningsElem.NotNull())
    {
        XMLElement kerningElem = kerningsElem.GetChild("kerning");
        while (!kerningElem.IsNull())
        {
            int first = kerningElem.GetInt("first");
            int second = kerningElem.GetInt("second");
            unsigned value = (first << 16) + second;
            kerningMapping_[value] = (short)kerningElem.GetInt("amount");

            kerningElem = kerningElem.GetNext("kerning");
        }
    }

    LOGDEBUGF("Bitmap font face %s has %d glyphs", GetFileName(font_->GetName()).CString(), count);

    font_->SetMemoryUse(font_->GetMemoryUse() + totalTextureSize);
    return true;
}

bool FontFaceBitmap::Load(FontFace* fontFace, bool usedGlyphs)
{
    if (this == fontFace)
        return true;

    if (!usedGlyphs)
    {
        glyphMapping_ = fontFace->glyphMapping_;
        kerningMapping_ = fontFace->kerningMapping_;
        textures_ = fontFace->textures_;
        pointSize_ = fontFace->pointSize_;
        rowHeight_ = fontFace->rowHeight_;

        return true;
    }

    pointSize_ = fontFace->pointSize_;
    rowHeight_ = fontFace->rowHeight_;

    int numPages = 1;
    int maxTextureSize = font_->GetSubsystem<UI>()->GetMaxFontTextureSize();
    AreaAllocator allocator(FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MIN_SIZE, maxTextureSize, maxTextureSize);

    for (HashMap<unsigned, FontGlyph>::ConstIterator i = fontFace->glyphMapping_.Begin(); i != fontFace->glyphMapping_.End(); ++i)
    {
        FontGlyph fontGlyph = i->second_;
        if (!fontGlyph.used_)
            continue;

        int x, y;
        if (!allocator.Allocate(fontGlyph.width_ + 1, fontGlyph.height_ + 1, x, y))
        {
            ++numPages;

            allocator = AreaAllocator(FONT_TEXTURE_MIN_SIZE, FONT_TEXTURE_MIN_SIZE, maxTextureSize, maxTextureSize);
            if (!allocator.Allocate(fontGlyph.width_ + 1, fontGlyph.height_ + 1, x, y))
                return false;
        }

        fontGlyph.x_ = x;
        fontGlyph.y_ = y;
        fontGlyph.page_ = numPages - 1;

        glyphMapping_[i->first_] = fontGlyph;
    }

    // Assume that format is the same for all textures and that bitmap font type may have more than one component
    unsigned components = ConvertFormatToNumComponents(fontFace->textures_[0]->GetFormat());

    // Save the existing textures as image resources
    Vector<SharedPtr<Image> > oldImages;
    for (unsigned i = 0; i < fontFace->textures_.Size(); ++i)
        oldImages.Push(SaveFaceTexture(fontFace->textures_[i]));

    Vector<SharedPtr<Image> > newImages(numPages);
    for (int i = 0; i < numPages; ++i)
    {
        SharedPtr<Image> image(new Image(font_->GetContext()));

        int width = maxTextureSize;
        int height = maxTextureSize;
        if (i == numPages - 1)
        {
            width = allocator.GetWidth();
            height = allocator.GetHeight();
        }

        image->SetSize(width, height, components);
        memset(image->GetData(), 0, width * height * components);

        newImages.Push(image);
    }

    for (HashMap<unsigned, FontGlyph>::Iterator i = glyphMapping_.Begin(); i != glyphMapping_.End(); ++i)
    {
        FontGlyph& newGlyph = i->second_;
        const FontGlyph& oldGlyph = fontFace->glyphMapping_[i->first_];
        Blit(newImages[newGlyph.page_], newGlyph.x_, newGlyph.y_, newGlyph.width_, newGlyph.height_, oldImages[oldGlyph.page_], oldGlyph.x_, oldGlyph.y_, components);
    }

    textures_.Resize(newImages.Size());
    for (unsigned i = 0; i < newImages.Size(); ++i)
        textures_[i] = LoadFaceTexture(newImages[i]);

    for (HashMap<unsigned, short>::ConstIterator i = fontFace->kerningMapping_.Begin(); i != fontFace->kerningMapping_.End(); ++i)
    {
        unsigned first = (i->first_) >> 16;
        unsigned second = (i->first_) & 0xffff;
        if (glyphMapping_.Find(first) != glyphMapping_.End() && glyphMapping_.Find(second) != glyphMapping_.End())
            kerningMapping_[i->first_] = i->second_;
    }

    return true;
}

bool FontFaceBitmap::Save(Serializer& dest, int pointSize)
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
    unsigned numGlyphs = glyphMapping_.Size();
    charsElem.SetInt("count", numGlyphs);

    for (HashMap<unsigned, FontGlyph>::ConstIterator i = glyphMapping_.Begin(); i != glyphMapping_.End(); ++i)
    {
        // Char
        XMLElement charElem = charsElem.CreateChild("char");
        charElem.SetInt("id", i->first_);

        const FontGlyph& glyph = i->second_;
        charElem.SetInt("x", glyph.x_);
        charElem.SetInt("y", glyph.y_);
        charElem.SetInt("width", glyph.width_);
        charElem.SetInt("height", glyph.height_);
        charElem.SetInt("xoffset", glyph.offsetX_);
        charElem.SetInt("yoffset", glyph.offsetY_);
        charElem.SetInt("xadvance", glyph.advanceX_);
        charElem.SetInt("page", glyph.page_);
    }

    if (!kerningMapping_.Empty())
    {
        XMLElement kerningsElem = rootElem.CreateChild("kernings");
        for (HashMap<unsigned, short>::ConstIterator i = kerningMapping_.Begin(); i != kerningMapping_.End(); ++i)
        {
            XMLElement kerningElem = kerningsElem.CreateChild("kerning");
            kerningElem.SetInt("first", i->first_ >> 16);
            kerningElem.SetInt("second", i->first_ & 0xffff);
            kerningElem.SetInt("amount", i->second_);
        }
    }

    return xml->Save(dest);
}

unsigned FontFaceBitmap::ConvertFormatToNumComponents(unsigned format)
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

SharedPtr<Image> FontFaceBitmap::SaveFaceTexture(Texture2D* texture)
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

bool FontFaceBitmap::SaveFaceTexture(Texture2D* texture, const String& fileName)
{
    SharedPtr<Image> image = SaveFaceTexture(texture);
    return image ? image->SavePNG(fileName) : false;
}

void FontFaceBitmap::Blit(Image* dest, int x, int y, int width, int height, Image* source, int sourceX, int sourceY, int components)
{
    unsigned char* destData = dest->GetData() + (y * dest->GetWidth() + x) * components;
    unsigned char* sourceData = source->GetData() + (sourceY * source->GetWidth() + sourceX) * components;
    for (int i = 0; i < height; ++i)
    {
        memcpy(destData, sourceData, width * components);
        destData += dest->GetWidth() * components;
        sourceData += source->GetWidth() * components;
    }
}

}
