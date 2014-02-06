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

#include "AreaAllocator.h"
#include "ArrayPtr.h"
#include "List.h"
#include "Resource.h"

namespace Urho3D
{

class Font;
class FreeTypeLibrary;
class Graphics;
class Image;
class Texture2D;

static const int FONT_TEXTURE_MIN_SIZE = 128;
static const int FONT_DPI = 96;

/// Mutable font glyph description.
struct MutableGlyph
{
    /// Construct.
    MutableGlyph();
    
    /// The actual glyph index that currently occupies this mutable slot. M_MAX_UNSIGNED if none.
    unsigned glyphIndex_;
    /// X position in texture.
    short x_;
    /// Y position in texture.
    short y_;
};

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
    /// Kerning information.
    HashMap<unsigned, unsigned> kerning_;
    /// Mutable glyph list iterator.
    List<MutableGlyph*>::Iterator iterator_;
};

/// %Font file type.
enum FONT_TYPE
{
    FONT_NONE = 0,
    FONT_FREETYPE,
    FONT_BITMAP,
    MAX_FONT_TYPES
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
    
    /// Return pointer to the glyph structure corresponding to a character. Return null if glyph not found.
    const FontGlyph* GetGlyph(unsigned c);
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
    /// Return if font face uses mutable glyphs.
    bool HasMutableGlyphs() const { return !mutableGlyphs_.Empty(); }
    
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
    
    /// Parent font.
    Font* font_;
    /// FreeType face. Non-null after creation only in dynamic mode.
    void* face_;
    /// Glyphs.
    Vector<FontGlyph> glyphs_;
    /// Glyph index mapping.
    HashMap<unsigned, unsigned> glyphMapping_;
    /// Glyph texture pages.
    Vector<SharedPtr<Texture2D> > textures_;
    /// Mutable glyph list.
    List<MutableGlyph*> mutableGlyphs_;
    /// Point size.
    int pointSize_;
    /// Row height.
    int rowHeight_;
    /// Mutable glyph cell width, including 1 pixel padding.
    int cellWidth_;
    /// Mutable glyph cell height, including 1 pixel padding.
    int cellHeight_;
    /// Kerning flag.
    bool hasKerning_;
    /// Glyph area allocator.
    AreaAllocator allocator_;
    /// Glyph rendering bitmap in dynamic mode.
    SharedArrayPtr<unsigned char> bitmap_;
    /// Glyph rendering bitmap byte size.
    unsigned bitmapSize_;
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
    FontFace* GetFace(int pointSize);
    
    /// Release font faces and recreate them next time when requested. Called when font textures lost or global font properties change.
    void ReleaseFaces();
    /// Create a texture for font rendering.
    SharedPtr<Texture2D> CreateFaceTexture();
    /// Load font face texture from image resource.
    SharedPtr<Texture2D> LoadFaceTexture(SharedPtr<Image> image);
    
private:
    /// Return font face using FreeTyp. Called internally. Return null on error.
    FontFace* GetFaceFreeType(int pointSize);
    /// Return bitmap font face. Called internally. Return null on error.
    FontFace* GetFaceBitmap(int pointSize);
    /// Convert graphics format to number of components.
    unsigned ConvertFormatToNumComponents(unsigned format);
    /// Pack used glyphs into smallest texture size and smallest number of texture.
    SharedPtr<FontFace> Pack(FontFace* fontFace);
    /// Save font face texture as image resource.
    SharedPtr<Image> SaveFaceTexture(Texture2D* texture);
    /// Save font face texture as image file.
    bool SaveFaceTexture(Texture2D* texture, const String& fileName);
    
    /// FreeType library.
    SharedPtr<FreeTypeLibrary> freeType_;
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
