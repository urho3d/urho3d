// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/ArrayPtr.h"
#include "../Math/AreaAllocator.h"

namespace Urho3D
{

class Font;
class Image;
class Texture2D;

/// %Font glyph description.
struct URHO3D_API FontGlyph
{
    /// X position in texture.
    short x_{};
    /// Y position in texture.
    short y_{};
    /// Width in texture.
    short texWidth_{};
    /// Height in texture.
    short texHeight_{};
    /// Width on screen.
    float width_{};
    /// Height on screen.
    float height_{};
    /// Glyph X offset from origin.
    float offsetX_{};
    /// Glyph Y offset from origin.
    float offsetY_{};
    /// Horizontal advance.
    float advanceX_{};
    /// Texture page. M_MAX_UNSIGNED if not yet resident on any texture.
    unsigned page_{M_MAX_UNSIGNED};
    /// Used flag.
    bool used_{};
};

/// %Font face description.
class URHO3D_API FontFace : public RefCounted
{
    friend class Font;

public:
    /// Construct.
    explicit FontFace(Font* font);
    /// Destruct.
    ~FontFace() override;

    /// Load font face.
    virtual bool Load(const unsigned char* fontData, unsigned fontDataSize, float pointSize) = 0;
    /// Return pointer to the glyph structure corresponding to a character. Return null if glyph not found.
    virtual const FontGlyph* GetGlyph(c32 c);

    /// Return if font face uses mutable glyphs.
    virtual bool HasMutableGlyphs() const { return false; }

    /// Return the kerning for a character and the next character.
    float GetKerning(c32 c, c32 d) const;
    /// Return true when one of the texture has a data loss.
    bool IsDataLost() const;

    /// Return point size.
    float GetPointSize() const { return pointSize_; }

    /// Return row height.
    float GetRowHeight() const { return rowHeight_; }

    /// Return textures.
    const Vector<SharedPtr<Texture2D> >& GetTextures() const { return textures_; }

protected:
    friend class FontFaceBitmap;
    /// Create a texture for font rendering.
    SharedPtr<Texture2D> CreateFaceTexture();
    /// Load font face texture from image resource.
    SharedPtr<Texture2D> LoadFaceTexture(const SharedPtr<Image>& image);

    /// Parent font.
    Font* font_{};
    /// Glyph mapping.
    HashMap<c32, FontGlyph> glyphMapping_;
    /// Kerning mapping.
    HashMap<u32, float> kerningMapping_;
    /// Glyph texture pages.
    Vector<SharedPtr<Texture2D> > textures_;
    /// Point size.
    float pointSize_{};
    /// Row height.
    float rowHeight_{};
};

}
