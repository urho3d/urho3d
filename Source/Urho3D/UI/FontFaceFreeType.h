//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../UI/FontFace.h"

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
    virtual bool HasMutableGlyphs() const { return hasMutableGlyph_; }

private:
    /// Check can load all glyph in one texture, return true and texture size if can load.
    bool CanLoadAllGlyphs(const PODVector<unsigned>& charCodes, int& textureWidth, int& textureHeight) const;
    /// Setup next texture.
    bool SetupNextTexture(int textureWidth, int textureHeight);
    /// Load char glyph.
    bool LoadCharGlyph(unsigned charCode, Image* image = 0);

    /// FreeType library.
    SharedPtr<FreeTypeLibrary> freeType_;
    /// FreeType face. Non-null after creation only in dynamic mode.
    void* face_;
    /// Load mode.
    int loadMode_;
    /// Ascender.
    int ascender_;
    /// Has mutable glyph.
    bool hasMutableGlyph_;
    /// Glyph area allocator.
    AreaAllocator allocator_;
};

}
