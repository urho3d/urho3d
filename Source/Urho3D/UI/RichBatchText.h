#ifndef __RICH_WIDGET_TEXT_H__
#define __RICH_WIDGET_TEXT_H__
#pragma once

#include "../UI/RichBatch.h"
#include "../Graphics/Material.h"
#include "../UI/Font.h"

namespace Urho3D {

// A mesh that displays text quads with a single font/size
class RichWidgetText: public RichWidgetBatch {
  URHO3D_OBJECT(RichWidgetText, RichWidgetBatch)
public:
  /// Register object factory.
  static void RegisterObject(Context* context);

  RichWidgetText(Context* context);
  virtual ~RichWidgetText();

  void DrawQuad(const FloatRect& vertices,
		float z, 
		const FloatRect& texCoords, 
		const Color& color);

  // draw a glyph
  void DrawGlyph(const FloatRect& texCoords,
		float x, 
		float y, 
		float z, 
		float width, 
		float height, 
		const Color& color);

  // draws a glyph, scaled depending on the bitmap font and pointsize
  void DrawGlyphScaled(const FloatRect& texCoords,
    float x,
    float y,
    float z,
    float width,
    float height,
    const Vector2& scale,
    const Color& color);

  // Add text
  void AddText(const String& text,
					const Vector3& pos, 
					const Color& color);

  void SetFont(const String& fontname, int pointsize);

  FontFace* GetFontFace() const { return font_face_; }

  // Calculate text extents with the current font
  IntVector2 CalculateTextExtents(const String& text);

  // Row height
  int GetRowHeight() const;
private:
  Font* font_;
  FontFace* font_face_;
  int pointsize_;
  Vector2 bitmap_font_rescale_;
};

} // namespace engine

#endif
