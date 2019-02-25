#pragma once

#include "../UI/RichBatch.h"
#include "../Graphics/Material.h"
#include "../UI/Font.h"

namespace Urho3D
{

/// A mesh that displays text quads with a single font/size.
class RichWidgetText: public RichWidgetBatch
{
    URHO3D_OBJECT(RichWidgetText, RichWidgetBatch)
public:
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Contructor.
    RichWidgetText(Context* context);
    /// Destructor.
    virtual ~RichWidgetText();

    /// Draw a quad.
    void DrawQuad(const Rect& vertices, float z, const Rect& texCoords, const Color& color);
    /// Draw a glyph.
    void DrawGlyph(const Rect& texCoords, float x, float y, float z, float width, float height, const Color& color);
    /// Draw a glyph, scaled depending on the bitmap font and pointsize.
    void DrawGlyphScaled(const Rect& texCoords, float x, float y, float z, float width, float height, const Vector2& scale, const Color& color);
    /// Add text.
    void AddText(const String& text, const Vector3& pos, const Color& color);
    /// Set the font.
    void SetFont(const String& fontname, int pointsize);
    /// Get the font face (only valid after SetFont).
    FontFace* GetFontFace() const { return font_face_; }
    /// Calculate text extents with the current font
    Vector2 CalculateTextExtents(const String& text);
    /// Row height
    float GetRowHeight() const;
private:
    Font* font_;
    FontFace* font_face_;
    int pointsize_;
    Vector2 bitmap_font_rescale_;
};

} // namespace Urho3D
