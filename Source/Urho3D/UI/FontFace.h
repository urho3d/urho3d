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

#include "../Math/AreaAllocator.h"
#include "../Container/ArrayPtr.h"
#include "../Container/List.h"

namespace Urho3D
{

class Font;
class Image;
class Texture2D;

/// %Font glyph description.
struct FontGlyph
{
    /// Construct.
    FontGlyph();

    /// X position in texture.
    short x_;
    /// Y position in texture.
    short y_;
    /// Width.
    short width_;
    /// Height.
    short height_;
    /// Glyph X offset from origin.
    short offsetX_;
    /// Glyph Y offset from origin.
    short offsetY_;
    /// Horizontal advance.
    short advanceX_;
    /// Texture page. M_MAX_UNSIGNED if not yet resident on any texture.
    unsigned page_;
    /// Used flag.
    bool used_;
};

/// %Font face description.
class URHO3D_API FontFace : public RefCounted
{
    friend class Font;

public:
    /// Construct.
    FontFace(Font* font);
    /// Destruct.
    ~FontFace();

    /// Load font face.
    virtual bool Load(const unsigned char* fontData, unsigned fontDataSize, int pointSize) = 0;
    /// Return pointer to the glyph structure corresponding to a character. Return null if glyph not found.
    virtual const FontGlyph* GetGlyph(unsigned c);
    /// Return if font face uses mutable glyphs.
    virtual bool HasMutableGlyphs() const { return false; }
    /// Return the kerning for a character and the next character.
    short GetKerning(unsigned c, unsigned d) const;
    /// Return true when one of the texture has a data loss.
    bool IsDataLost() const;
    /// Return point size.
    int GetPointSize() const { return pointSize_; }
    /// Return row height.
    int GetRowHeight() const { return rowHeight_; }
    /// Return textures.
    const Vector<SharedPtr<Texture2D> >& GetTextures() const { return textures_; }

protected:
    friend class FontFaceBitmap;
    /// Create a texture for font rendering.
    SharedPtr<Texture2D> CreateFaceTexture();
    /// Load font face texture from image resource.
    SharedPtr<Texture2D> LoadFaceTexture(SharedPtr<Image> image);

    /// Parent font.
    Font* font_;
    /// Glyph mapping.
    HashMap<unsigned, FontGlyph> glyphMapping_;
    /// Kerning mapping.
    HashMap<unsigned, short> kerningMapping_;
    /// Glyph texture pages.
    Vector<SharedPtr<Texture2D> > textures_;
    /// Point size.
    int pointSize_;
    /// Row height.
    int rowHeight_;
};

}
