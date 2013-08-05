//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "ArrayPtr.h"
#include "Resource.h"

namespace Urho3D
{

class Graphics;
class Image;
class Texture;

static const int FONT_TEXTURE_MIN_SIZE = 128;
static const int FONT_TEXTURE_MAX_SIZE = 2048;
static const int FONT_DPI = 96;

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
    /// Page.
    unsigned page_;
    /// Kerning information.
    HashMap<unsigned, unsigned> kerning_;
    /// Used flag.
    mutable bool used_;
};

/// %Font file type.
enum FONT_TYPE
{
    FONT_NONE = 0,
    FONT_TTF,
    FONT_BITMAP,
    MAX_FONT_TYPES
};

/// %Font face description.
class URHO3D_API FontFace : public RefCounted
{
public:
    /// Construct.
    FontFace();
    /// Destruct.
    ~FontFace();
    
    /// Return pointer to the glyph structure corresponding to a character. Return null if glyph not found.
    const FontGlyph* GetGlyph(unsigned c) const;
    /// Return the kerning for a character and the next character.
    short GetKerning(unsigned c, unsigned d) const;
    /// Return true when one of the texture has a data loss.
    bool IsDataLost() const;
    
    /// Texture.
    Vector<SharedPtr<Texture> > textures_;
    /// Glyphs.
    Vector<FontGlyph> glyphs_;
    /// Point size.
    int pointSize_;
    /// Row height.
    int rowHeight_;
    /// Glyph index mapping.
    HashMap<unsigned, unsigned> glyphMapping_;
    /// Kerning flag.
    bool hasKerning_;
};

/// %Font resource.
class URHO3D_API Font : public Resource
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
    /// Save resource as a new bitmap font type in XML format. Return true if successful.
    bool SaveXML(Serializer& dest, int pointSize, bool usedGlyphs = false);
    /// Return font face. Pack and render to a texture if not rendered yet. Return null on error.
    const FontFace* GetFace(int pointSize);
    
private:
    /// Return True-type font face. Called internally. Return null on error.
    const FontFace* GetFaceTTF(int pointSize);
    /// Return bitmap font face. Called internally. Return null on error.
    const FontFace* GetFaceBitmap(int pointSize);
    /// Convert graphics format to number of components.
    unsigned ConvertFormatToNumComponents(unsigned format);
    /// Pack used glyphs into smallest texture size and smallest number of texture.
    SharedPtr<FontFace> Pack(const FontFace* fontFace);
    /// Load font face texture from image resource.
    SharedPtr<Texture> LoadFaceTexture(SharedPtr<Image> image);
    /// Save font face texture as image resource.
    SharedPtr<Image> SaveFaceTexture(Texture* texture);
    /// Save font face texture as image file.
    bool SaveFaceTexture(Texture* texture, const String& fileName);
    
    /// Created faces.
    HashMap<int, SharedPtr<FontFace> > faces_;
    /// Font data.
    SharedArrayPtr<unsigned char> fontData_;
    /// Size of font data.
    unsigned fontDataSize_;
    /// Font type.
    FONT_TYPE fontType_;
};

}
