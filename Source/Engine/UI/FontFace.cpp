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
    face_(0),
    hasKerning_(false),
    bitmapSize_(0)
{
}

FontFace::~FontFace()
{
    if (face_)
    {
        FT_Done_Face((FT_Face)face_);
        face_ = 0;
    }

    if (font_)
    {
        // When a face is unloaded, deduct the used texture data size from the parent font
        unsigned totalTextureSize = 0;
        for (unsigned i = 0; i < textures_.Size(); ++i)
            totalTextureSize += textures_[i]->GetWidth() * textures_[i]->GetHeight();
        font_->SetMemoryUse(font_->GetMemoryUse() - totalTextureSize);
    }

    for (List<MutableGlyph*>::Iterator i = mutableGlyphs_.Begin(); i != mutableGlyphs_.End(); ++i)
        delete *i;
    mutableGlyphs_.Clear();
}

const FontGlyph* FontFace::GetGlyph(unsigned c)
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

bool FontFace::RenderAllGlyphs(int maxWidth, int maxHeight)
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

void FontFace::RenderGlyph(unsigned index)
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

void FontFace::RenderGlyphBitmap(unsigned index, unsigned char* dest, unsigned pitch, int loadMode)
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

void FontFace::SetupNextTexture(int width, int height)
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

void FontFace::SetupMutableGlyphs(int textureWidth, int textureHeight, int maxWidth, int maxHeight)
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

}
