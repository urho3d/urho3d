// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
    explicit FontFaceFreeType(Font* font);
    /// Destruct.
    ~FontFaceFreeType() override;

    /// Load font face.
    bool Load(const unsigned char* fontData, unsigned fontDataSize, float pointSize) override;
    /// Return pointer to the glyph structure corresponding to a character. Return null if glyph not found.
    const FontGlyph* GetGlyph(unsigned c) override;

    /// Return if font face uses mutable glyphs.
    bool HasMutableGlyphs() const override { return hasMutableGlyph_; }

private:
    /// Setup next texture.
    bool SetupNextTexture(int textureWidth, int textureHeight);
    /// Load char glyph.
    bool LoadCharGlyph(unsigned charCode, Image* image = nullptr);
    /// Smooth one row of a horizontally oversampled glyph image.
    void BoxFilter(unsigned char* dest, size_t destSize, const unsigned char* src, size_t srcSize);

    /// FreeType library.
    SharedPtr<FreeTypeLibrary> freeType_;
    /// FreeType face. Non-null after creation only in dynamic mode.
    void* face_{};
    /// Load mode.
    int loadMode_{};
    /// Use subpixel glyph positioning?
    bool subpixel_{};
    /// Oversampling level.
    int oversampling_{};
    /// Ascender.
    float ascender_{};
    /// Has mutable glyph.
    bool hasMutableGlyph_{};
    /// Glyph area allocator.
    AreaAllocator allocator_;
};

}
