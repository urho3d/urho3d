// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

/// \file

#pragma once

#include "../UI/UISelectable.h"

namespace Urho3D
{

inline constexpr float DEFAULT_FONT_SIZE = 12;

class Font;
class FontFace;
struct FontGlyph;

/// Text effect.
enum TextEffect
{
    TE_NONE = 0,
    TE_SHADOW,
    TE_STROKE
};

/// Cached character location and size within text. Used for queries related to text editing.
struct CharLocation
{
    /// Position.
    Vector2 position_;
    /// Size.
    Vector2 size_;
};

/// Glyph and its location within the text. Used when preparing text rendering.
/// @nobind
struct GlyphLocation
{
    /// Fields are not initialized.
    GlyphLocation() = default;

    /// Construct.
    GlyphLocation(float x, float y, const FontGlyph* glyph) :
        x_(x),
        y_(y),
        glyph_(glyph)
    {
    }

    /// X coordinate.
    float x_;
    /// Y coordinate.
    float y_;
    /// Glyph.
    const FontGlyph* glyph_;
};

/// %Text %UI element.
class URHO3D_API Text : public UISelectable
{
    URHO3D_OBJECT(Text, UISelectable);

    friend class Text3D;

public:
    /// Construct.
    explicit Text(Context* context);
    /// Destruct.
    ~Text() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately.
    void ApplyAttributes() override;
    /// Return UI rendering batches.
    void GetBatches(Vector<UIBatch>& batches, Vector<float>& vertexData, const IntRect& currentScissor) override;
    /// React to resize.
    void OnResize(const IntVector2& newSize, const IntVector2& delta) override;
    /// React to indent change.
    void OnIndentSet() override;

    /// Set font by looking from resource cache by name and font size. Return true if successful.
    bool SetFont(const String& fontName, float size = DEFAULT_FONT_SIZE);
    /// Set font and font size. Return true if successful.
    bool SetFont(Font* font, float size = DEFAULT_FONT_SIZE);
    /// Set font size only while retaining the existing font. Return true if successful.
    /// @property
    bool SetFontSize(float size);
    /// Set text. Text is assumed to be either ASCII or UTF8-encoded.
    /// @property
    void SetText(const String& text);
    /// Set row alignment.
    /// @property
    void SetTextAlignment(HorizontalAlignment align);
    /// Set row spacing, 1.0 for original font spacing.
    /// @property
    void SetRowSpacing(float spacing);
    /// Set wordwrap. In wordwrap mode the text element will respect its current width. Otherwise it resizes itself freely.
    /// @property
    void SetWordwrap(bool enable);
    /// The text will be automatically translated. The text value used as string identifier.
    /// @property
    void SetAutoLocalizable(bool enable);
    /// Set selection. When length is not provided, select until the text ends.
    void SetSelection(i32 start, i32 length = M_MAX_INT);
    /// Clear selection.
    void ClearSelection();
    /// Set text effect.
    /// @property
    void SetTextEffect(TextEffect textEffect);
    /// Set shadow offset.
    /// @property
    void SetEffectShadowOffset(const IntVector2& offset);
    /// Set stroke thickness.
    /// @property
    void SetEffectStrokeThickness(int thickness);
    /// Set stroke rounding. Corners of the font will be rounded off in the stroke so the stroke won't have corners.
    /// @property
    void SetEffectRoundStroke(bool roundStroke);
    /// Set effect color.
    /// @property
    void SetEffectColor(const Color& effectColor);

    /// Return font.
    /// @property
    Font* GetFont() const { return font_; }

    /// Return font size.
    /// @property
    float GetFontSize() const { return fontSize_; }

    /// Return text.
    /// @property
    const String& GetText() const { return text_; }

    /// Return row alignment.
    /// @property
    HorizontalAlignment GetTextAlignment() const { return textAlignment_; }

    /// Return row spacing.
    /// @property
    float GetRowSpacing() const { return rowSpacing_; }

    /// Return wordwrap mode.
    /// @property
    bool GetWordwrap() const { return wordWrap_; }

    /// Return auto localizable mode.
    /// @property
    bool GetAutoLocalizable() const { return autoLocalizable_; }

    /// Return selection start.
    /// @property
    i32 GetSelectionStart() const { return selectionStart_; }

    /// Return selection length.
    /// @property
    i32 GetSelectionLength() const { return selectionLength_; }

    /// Return text effect.
    /// @property
    TextEffect GetTextEffect() const { return textEffect_; }

    /// Return effect shadow offset.
    /// @property
    const IntVector2& GetEffectShadowOffset() const { return shadowOffset_; }

    /// Return effect stroke thickness.
    /// @property
    int GetEffectStrokeThickness() const { return strokeThickness_; }

    /// Return effect round stroke.
    /// @property
    bool GetEffectRoundStroke() const { return roundStroke_; }

    /// Return effect color.
    /// @property
    const Color& GetEffectColor() const { return effectColor_; }

    /// Return row height.
    /// @property
    float GetRowHeight() const { return rowHeight_; }

    /// Return number of rows.
    /// @property
    i32 GetNumRows() const { return rowWidths_.Size(); }

    /// Return number of characters.
    /// @property
    i32 GetNumChars() const { return unicodeText_.Size(); }

    /// Return width of row by index.
    /// @property{get_rowWidths}
    float GetRowWidth(i32 index) const;
    /// Return position of character by index relative to the text element origin.
    /// @property{get_charPositions}
    Vector2 GetCharPosition(i32 index);
    /// Return size of character by index.
    /// @property{get_charSizes}
    Vector2 GetCharSize(i32 index);

    /// Set text effect Z bias. Zero by default, adjusted only in 3D mode.
    void SetEffectDepthBias(float bias);

    /// Return effect Z bias.
    float GetEffectDepthBias() const { return effectDepthBias_; }

    /// Set font attribute.
    void SetFontAttr(const ResourceRef& value);
    /// Return font attribute.
    ResourceRef GetFontAttr() const;
    /// Set text attribute.
    void SetTextAttr(const String& value);
    /// Return text attribute.
    String GetTextAttr() const;

protected:
    /// Filter implicit attributes in serialization process.
    bool FilterImplicitAttributes(XMLElement& dest) const override;
    /// Update text when text, font or spacing changed.
    void UpdateText(bool onResize = false);
    /// Update cached character locations after text update, or when text alignment or indent has changed.
    void UpdateCharLocations();
    /// Validate text selection to be within the text.
    void ValidateSelection();
    /// Return row start X position.
    int GetRowStartPosition(i32 rowIndex) const;
    /// Construct batch.
    void ConstructBatch
        (UIBatch& pageBatch, const Vector<GlyphLocation>& pageGlyphLocation, float dx = 0, float dy = 0, Color* color = nullptr,
            float depthBias = 0.0f);

    /// Font.
    SharedPtr<Font> font_;
    /// Current face.
    WeakPtr<FontFace> fontFace_;
    /// Font size.
    float fontSize_;
    /// UTF-8 encoded text.
    String text_;
    /// Row alignment.
    HorizontalAlignment textAlignment_;
    /// Row spacing.
    float rowSpacing_;
    /// Wordwrap mode.
    bool wordWrap_;
    /// Char positions dirty flag.
    bool charLocationsDirty_;
    /// Selection start.
    i32 selectionStart_;
    /// Selection length.
    i32 selectionLength_;
    /// Text effect.
    TextEffect textEffect_;
    /// Text effect shadow offset.
    IntVector2 shadowOffset_;
    /// Text effect stroke thickness.
    int strokeThickness_;
    /// Text effect stroke rounding flag.
    bool roundStroke_;
    /// Effect color.
    Color effectColor_;
    /// Text effect Z bias.
    float effectDepthBias_;
    /// Row height.
    float rowHeight_;
    /// Text as Unicode characters.
    Vector<c32> unicodeText_;
    /// Text modified into printed form.
    Vector<c32> printText_;
    /// Mapping of printed form back to original char indices.
    Vector<i32> printToText_;
    /// Row widths.
    Vector<float> rowWidths_;
    /// Glyph locations per each texture in the font.
    Vector<Vector<GlyphLocation>> pageGlyphLocations_;
    /// Cached locations of each character in the text.
    Vector<CharLocation> charLocations_;
    /// The text will be automatically translated.
    bool autoLocalizable_;
    /// Localization string id storage. Used when autoLocalizable flag is set.
    String stringId_;
    /// Handle change Language.
    void HandleChangeLanguage(StringHash eventType, VariantMap& eventData);
    /// UTF8 to Unicode.
    void DecodeToUnicode();
};

}
