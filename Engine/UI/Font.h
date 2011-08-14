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

#pragma once

#include "Resource.h"
#include "ArrayPtr.h"

class Graphics;
class Texture;

static const int MAX_FONT_CHARS = 256;
static const int FONT_TEXTURE_MIN_SIZE = 128;
static const int FONT_TEXTURE_MAX_SIZE = 2048;
static const int FONT_DPI = 96;

/// %Font glyph description.
struct FontGlyph
{
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
};

/// %Font face description.
struct FontFace
{
    /// Point size.
    int pointSize_;
    /// Row height.
    int rowHeight_;
    /// Texture.
    SharedPtr<Texture> texture_;
    /// Glyph index mapping.
    unsigned short glyphIndex_[MAX_FONT_CHARS];
    /// Glyphs.
    PODVector<FontGlyph> glyphs_;
};

/// %Font resource.
class Font : public Resource
{
    OBJECT(Font);
    
public:
    /// Construct.
    Font(Context* context);
    /// Destruct.
    virtual ~Font();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful.
    virtual bool Load(Deserializer& source);
    
    /// Return font face. Pack and render to a texture if not rendered yet. Return null on error.
    const FontFace* GetFace(int pointSize);
    
private:
    /// Created faces.
    Map<int, FontFace> faces_;
    /// Font data.
    SharedArrayPtr<unsigned char> fontData_;
    /// Size of font data.
    unsigned fontDataSize_;
};
