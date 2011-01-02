//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#ifndef UI_FONT_H
#define UI_FONT_H

#include "AreaAllocator.h"
#include "Resource.h"
#include "SharedPtr.h"
#include "SharedArrayPtr.h"

class Renderer;
class Texture;

static const int MAX_FONT_CHARS = 256;
static const unsigned FONT_TEXTURE_MIN_SIZE = 128;
static const unsigned FONT_TEXTURE_MAX_SIZE = 2048;

//! Font glyph description
struct FontGlyph
{
    //! X position in texture
    short mX;
    //! Y position in texture
    short mY;
    //! Width
    short mWidth;
    //! Height
    short mHeight;
    //! Glyph X offset from origin
    short mOffsetX;
    //! Glyph Y offset from origin
    short mOffsetY;
    //! Horizontal advance
    short mAdvanceX;
};

//! Font face description
struct FontFace
{
    //! Point size
    int mPointSize;
    //! Row height
    int mRowHeight;
    //! Texture
    SharedPtr<Texture> mTexture;
    //! Glyph index mapping
    unsigned short mGlyphIndex[MAX_FONT_CHARS];
    //! Glyphs
    std::vector<FontGlyph> mGlyphs;
};

//! Font resource
class Font : public Resource
{
    DEFINE_TYPE(Font);
    
public:
    //! Construct with renderer subsystem pointer and name
    Font(Renderer* renderer, const std::string& name = std::string());
    //! Destruct
    virtual ~Font();
    
    //! Load resource
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    //! Return font face. Pack and render to a texture if not rendered yet
    const FontFace* getFace(int pointSize);
    
private:
    //! Renderer subsystem
    WeakPtr<Renderer> mRenderer;
    //! Created faces
    std::map<int, FontFace> mFaces;
    //! Font data
    SharedArrayPtr<unsigned char> mFontData;
    //! Size of font data
    unsigned mFontDataSize;
};

std::string getSystemFontDirectory();

#endif // UI_FONT_H
