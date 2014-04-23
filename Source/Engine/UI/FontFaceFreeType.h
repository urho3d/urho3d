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

#pragma once

#include "FontFace.h"

namespace Urho3D
{

class FreeTypeLibrary;
class Texture2D;

/// Free type font face description.
class URHO3D_API FontFaceFreeType : public FontFace
{
public:
    /// Construct.
    FontFaceFreeType(Font* font);
    /// Destruct.
    ~FontFaceFreeType();

    /// Load font face.
    virtual bool Load(const unsigned char* fontData, unsigned fontDataSize, int pointSize);
    /// Return pointer to the glyph structure corresponding to a character. Return null if glyph not found.
    virtual const FontGlyph* GetGlyph(unsigned c);
    /// Return if font face uses mutable glyphs.
    virtual bool HasMutableGlyphs() const { return !mutableGlyphs_.Empty(); }

private:
    /// Render all glyphs of the face into a single texture. Return true if could fit them. Called by Font.
    bool RenderAllGlyphs(int maxWidth, int maxHeight);
    /// Render one glyph on demand into the current texture.
    void RenderGlyph(unsigned index);
    /// Render a glyph bitmap into a memory buffer.
    void RenderGlyphBitmap(unsigned index, unsigned char* dest, unsigned pitch, int loadMode);
    /// Setup next texture for dynamic glyph rendering.
    void SetupNextTexture(int width, int height);
    /// Setup mutable glyph rendering, in which glyphs form a regular-sized grid.
    void SetupMutableGlyphs(int textureWidth, int textureHeight, int maxGlyphWidth, int maxGlyphHeight);

    /// FreeType library.
    SharedPtr<FreeTypeLibrary> freeType_;
    /// FreeType face. Non-null after creation only in dynamic mode.
    void* face_;
    /// Mutable glyph list.
    List<MutableGlyph*> mutableGlyphs_;
    /// Mutable glyph cell width, including 1 pixel padding.
    int cellWidth_;
    /// Mutable glyph cell height, including 1 pixel padding.
    int cellHeight_;
    /// Glyph area allocator.
    AreaAllocator allocator_;
    /// Glyph rendering bitmap in dynamic mode.
    SharedArrayPtr<unsigned char> bitmap_;
    /// Glyph rendering bitmap byte size.
    unsigned bitmapSize_;
};

}
