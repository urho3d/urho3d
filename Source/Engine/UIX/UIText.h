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

#include "Drawable2D.h"
#include "Text.h"

namespace Urho3D
{

class UIRect;

/// UI Line glyphs.
struct UITextLineInfo
{
    /// Construct.
    UITextLineInfo() : lineWidth_(0.0f)
    {
    }

    /// Clear.
    void Clear();
    /// Add font flyph
    void Add(const FontGlyph* glyph, short kerning);

    /// Width.
    float lineWidth_;
    /// Font glyphs.
    PODVector<const FontGlyph*> fontGlyphs_;
    /// Advances;
    PODVector<float> glyphAdvances_;
};

/// %Text %UI element.
class URHO3D_API UIText : public Drawable2D
{
    OBJECT(UIText);

public:
    /// Construct.
    UIText(Context* context);
    /// Destruct.
    virtual ~UIText();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Set font and font size and use signed distance field.
    bool SetFont(const String& fontName, int size = DEFAULT_FONT_SIZE);
    /// Set font and font size and use signed distance field.
    bool SetFont(Font* font, int size = DEFAULT_FONT_SIZE);
    /// Set font size.
    void SetFontSize(int fontSize = DEFAULT_FONT_SIZE);
    /// Set text. Text is assumed to be either ASCII or UTF8-encoded.
    void SetText(const String& text);
    /// Set row alignment.
    void SetTextAlignment(HorizontalAlignment align);
    /// Set row spacing, 1.0 for original font spacing.
    void SetRowSpacing(float spacing);
    /// Set color.
    void SetColor(const Color& color);
    /// Set selection. When length is not provided, select until the text ends.
    void SetSelection(unsigned start, unsigned length = M_MAX_UNSIGNED);
    /// Clear selection.
    void ClearSelection();
    /// Set selection background color. Color with 0 alpha (default) disables.
    void SetSelectionColor(const Color& color);
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
    /// Return color.
    const Color& GetColor() const { return color_; }
    /// Return selection start.
    unsigned GetSelectionStart() const { return selectionStart_; }
    /// Return selection length.
    unsigned GetSelectionLength() const { return selectionLength_; }
    /// Return selection background color.
    const Color& GetSelectionColor() const { return selectionColor_; }
    /// Return text effect.
    TextEffect GetTextEffect() const { return textEffect_; }
    /// Return effect color.
    const Color& GetEffectColor() const { return effectColor_; }

    /// Return number of characters.
    unsigned GetNumChars() const { return numChars_; }
    /// Return number of rows.
    unsigned GetNumRows() const { return textLineInfo_.Size(); }
    /// Return row width.
    float GetRowWidth(unsigned row) const { return row < textLineInfo_.Size() ? textLineInfo_[row].lineWidth_ : 0.0f; }
    /// Return row height.
    float GetRowHeight() const { return rowHeight_; }

    /// Set font attribute.
    void SetFontAttr(const ResourceRef& value);
    /// Return font attribute.
    ResourceRef GetFontAttr() const;

protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    /// Update vertices.
    virtual void UpdateVertices();
    /// handle rect changed.
    void HandleRectDirtied(StringHash eventType, VariantMap& eventData);
    /// Update material.
    void UpdateMaterial(bool newFont = false);
    /// Update text when text, font or spacing changed.
    void UpdateText();
    /// Validate text selection to be within the text.
    void ValidateSelection();
    /// Contruct batch.
    void UpdateTextLineVertices(const UITextLineInfo& lineInfo, float x, float y, unsigned color);

    /// UIRect
    WeakPtr<UIRect> uiRect_;
    /// Used in Text3D.
    bool usedInText3D_;
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
    /// Color.
    Color color_;
    /// Selection background color.
    Color selectionColor_;
    /// Selection start.
    unsigned selectionStart_;
    /// Selection length.
    unsigned selectionLength_;
    /// Text effect.
    TextEffect textEffect_;
    /// Effect color.
    Color effectColor_;
    /// Number of characters.
    unsigned numChars_;
    /// Text line info.
    Vector<UITextLineInfo> textLineInfo_;
    /// Row height.
    float rowHeight_;
};

}
