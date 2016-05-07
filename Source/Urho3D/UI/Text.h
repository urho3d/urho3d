//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../UI/UIElement.h"

namespace Urho3D
{

static const int DEFAULT_FONT_SIZE = 12;

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
    IntVector2 position_;
    /// Size.
    IntVector2 size_;
};

/// Glyph and its location within the text. Used when preparing text rendering.
struct GlyphLocation
{
    // Construct.
    GlyphLocation(int x, int y, const FontGlyph* glyph) :
        x_(x),
        y_(y),
        glyph_(glyph)
    {
    }

    /// X coordinate.
    int x_;
    /// Y coordinate.
    int y_;
    /// Glyph.
    const FontGlyph* glyph_;
};

/// %Text %UI element.
class URHO3D_API Text : public UIElement
{
    URHO3D_OBJECT(Text, UIElement);

    friend class Text3D;

public:
    /// Construct.
    Text(Context* context);
    /// Destruct.
    virtual ~Text();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Apply attribute changes that can not be applied immediately.
    virtual void ApplyAttributes();
    /// Return UI rendering batches.
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);
    /// React to resize.
    virtual void OnResize();
    /// React to indent change.
    virtual void OnIndentSet();

    /// Set font and font size and use signed distance field.
    bool SetFont(const String& fontName, int size = DEFAULT_FONT_SIZE);
    /// Set font and font size and use signed distance field.
    bool SetFont(Font* font, int size = DEFAULT_FONT_SIZE);
    /// Set text. Text is assumed to be either ASCII or UTF8-encoded.
    void SetText(const String& text);
    /// Set row alignment.
    void SetTextAlignment(HorizontalAlignment align);
    /// Set row spacing, 1.0 for original font spacing.
    void SetRowSpacing(float spacing);
    /// Set wordwrap. In wordwrap mode the text element will respect its current width. Otherwise it resizes itself freely.
    void SetWordwrap(bool enable);
    /// The text will be automatically translated. The text value used as string identifier.
    void SetAutoLocalizable(bool enable);
    /// Set selection. When length is not provided, select until the text ends.
    void SetSelection(unsigned start, unsigned length = M_MAX_UNSIGNED);
    /// Clear selection.
    void ClearSelection();
    /// Set selection background color. Color with 0 alpha (default) disables.
    void SetSelectionColor(const Color& color);
    /// Set hover background color. Color with 0 alpha (default) disables.
    void SetHoverColor(const Color& color);
    /// Set text effect.
    void SetTextEffect(TextEffect textEffect);
    /// Set effect color.
    void SetEffectColor(const Color& effectColor);

    /// Return font.
    Font* GetFont() const { return font_; }

    /// Return font size.
    int GetFontSize() const { return fontSize_; }

    /// Return text.
    const String& GetText() const { return text_; }

    /// Return row alignment.
    HorizontalAlignment GetTextAlignment() const { return textAlignment_; }

    /// Return row spacing.
    float GetRowSpacing() const { return rowSpacing_; }

    /// Return wordwrap mode.
    bool GetWordwrap() const { return wordWrap_; }

    /// Return auto localizable mode.
    bool GetAutoLocalizable() const { return autoLocalizable_; }

    /// Return selection start.
    unsigned GetSelectionStart() const { return selectionStart_; }

    /// Return selection length.
    unsigned GetSelectionLength() const { return selectionLength_; }

    /// Return selection background color.
    const Color& GetSelectionColor() const { return selectionColor_; }

    /// Return hover background color.
    const Color& GetHoverColor() const { return hoverColor_; }

    /// Return text effect.
    TextEffect GetTextEffect() const { return textEffect_; }

    /// Return effect color.
    const Color& GetEffectColor() const { return effectColor_; }

    /// Return row height.
    int GetRowHeight() const { return rowHeight_; }

    /// Return number of rows.
    unsigned GetNumRows() const { return rowWidths_.Size(); }

    /// Return number of characters.
    unsigned GetNumChars() const { return unicodeText_.Size(); }

    /// Return width of row by index.
    int GetRowWidth(unsigned index) const;
    /// Return position of character by index relative to the text element origin.
    IntVector2 GetCharPosition(unsigned index);
    /// Return size of character by index.
    IntVector2 GetCharSize(unsigned index);

    /// Set text effect Z bias. Zero by default, adjusted only in 3D mode.
    void SetEffectDepthBias(float bias);

    /// Return effect Z bias.
    float GetEffectDepthBias() const { return effectDepthBias_; }

    /// Set font attribute.
    void SetFontAttr(const ResourceRef& value);
    /// Return font attribute.
    ResourceRef GetFontAttr() const;

protected:
    /// Filter implicit attributes in serialization process.
    virtual bool FilterImplicitAttributes(XMLElement& dest) const;
    /// Update text when text, font or spacing changed.
    void UpdateText(bool onResize = false);
    /// Update cached character locations after text update, or when text alignment or indent has changed.
    void UpdateCharLocations();
    /// Validate text selection to be within the text.
    void ValidateSelection();
    /// Return row start X position.
    int GetRowStartPosition(unsigned rowIndex) const;
    /// Contruct batch.
    void ConstructBatch
        (UIBatch& pageBatch, const PODVector<GlyphLocation>& pageGlyphLocation, int dx = 0, int dy = 0, Color* color = 0,
            float depthBias = 0.0f);

    /// Font.
    SharedPtr<Font> font_;
    /// Current face.
    WeakPtr<FontFace> fontFace_;
    /// Font size.
    int fontSize_;
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
    unsigned selectionStart_;
    /// Selection length.
    unsigned selectionLength_;
    /// Selection background color.
    Color selectionColor_;
    /// Hover background color.
    Color hoverColor_;
    /// Text effect.
    TextEffect textEffect_;
    /// Effect color.
    Color effectColor_;
    /// Text effect Z bias.
    float effectDepthBias_;
    /// Row height.
    int rowHeight_;
    /// Text as Unicode characters.
    PODVector<unsigned> unicodeText_;
    /// Text modified into printed form.
    PODVector<unsigned> printText_;
    /// Mapping of printed form back to original char indices.
    PODVector<unsigned> printToText_;
    /// Row widths.
    PODVector<int> rowWidths_;
    /// Glyph locations per each texture in the font.
    Vector<PODVector<GlyphLocation> > pageGlyphLocations_;
    /// Cached locations of each character in the text.
    PODVector<CharLocation> charLocations_;
    /// The text will be automatically translated.
    bool autoLocalizable_;
    /// Storage string id. Used when enabled autoLocalizable.
    String stringId_;
    /// Handle change Language.
    void HandleChangeLanguage(StringHash eventType, VariantMap& eventData);
    /// UTF8 to Unicode.
    void DecodeToUnicode();
};

}
