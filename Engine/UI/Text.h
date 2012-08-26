//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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

#include "UIElement.h"

namespace Urho3D
{

static const int DEFAULT_FONT_SIZE = 12;

class Font;

/// %Text %UI element.
class Text : public UIElement
{
    OBJECT(Text);
    
    using UIElement::SetStyle;
    
public:
    /// Construct.
    Text(Context* context);
    /// Destruct.
    virtual ~Text();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Apply attribute changes that can not be applied immediately.
    virtual void ApplyAttributes();
    /// Set UI element style from XML data.
    virtual void SetStyle(const XMLElement& element);
    /// Return UI rendering batches.
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<UIQuad>& quads, const IntRect& currentScissor);
    /// React to resize.
    virtual void OnResize();
    
    /// Set font and font size.
    bool SetFont(const String& fontName, int size = DEFAULT_FONT_SIZE);
    /// Set font and font size.
    bool SetFont(Font* font, int size = DEFAULT_FONT_SIZE);
    /// Set text. Text is assumed to be either ASCII or UTF8-encoded.
    void SetText(const String& text);
    /// Set row alignment.
    void SetTextAlignment(HorizontalAlignment align);
    /// Set row spacing, 1.0 for original font spacing.
    void SetRowSpacing(float spacing);
    /// Set wordwrap. In wordwrap mode the text element will respect its current width. Otherwise it resizes itself freely.
    void SetWordwrap(bool enable);
    /// Set selection.
    void SetSelection(unsigned start, unsigned length);
    /// Clear selection.
    void ClearSelection();
    /// Set selection background color. Color with 0 alpha (default) disables.
    void SetSelectionColor(const Color& color);
    /// Set hover background color. Color with 0 alpha (default) disables.
    void SetHoverColor(const Color& color);
    
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
    /// Return selection start.
    unsigned GetSelectionStart() const { return selectionStart_; }
    /// Return selection length.
    unsigned GetSelectionLength() const { return selectionLength_; }
    /// Return selection background color.
    const Color& GetSelectionColor() const { return selectionColor_; }
    /// Return hover background color.
    const Color& GetHoverColor() const { return hoverColor_; }
    /// Return row height.
    int GetRowHeight() const { return rowHeight_; }
    /// Return number of rows.
    unsigned GetNumRows() const { return rowWidths_.Size(); }
    /// Return width of each row.
    const PODVector<int>& GetRowWidths() const { return rowWidths_; }
    /// Return position of each character.
    const PODVector<IntVector2>& GetCharPositions() const { return charPositions_; }
    /// Return size of each character.
    const PODVector<IntVector2>& GetCharSizes() const { return charSizes_; }
    
    /// Set font attribute.
    void SetFontAttr(ResourceRef value);
    /// Return font attribute.
    ResourceRef GetFontAttr() const;
    
protected:
    /// Update text when text, font or spacing changed.
    void UpdateText(bool inResize = false);
    /// Validate text selection to be within the text.
    void ValidateSelection();
    /// Return row start X position.
    int GetRowStartPosition(unsigned rowIndex) const;
    
    /// Font.
    SharedPtr<Font> font_;
    /// Font size.
    int fontSize_;
    /// UTF-8 encoded text.
    String text_;
    /// Text as Unicode characters.
    PODVector<unsigned> unicodeText_;
    /// Text modified into printed form.
    PODVector<unsigned> printText_;
    /// Row alignment.
    HorizontalAlignment textAlignment_;
    /// Row spacing.
    float rowSpacing_;
    /// Wordwrap mode.
    bool wordWrap_;
    /// Selection start.
    unsigned selectionStart_;
    /// Selection length.
    unsigned selectionLength_;
    /// Selection background color.
    Color selectionColor_;
    /// Hover background color.
    Color hoverColor_;
    /// Row height.
    int rowHeight_;
    /// Row widths.
    PODVector<int> rowWidths_;
    /// Positions of each character.
    PODVector<IntVector2> charPositions_;
    /// Sizes of each character.
    PODVector<IntVector2> charSizes_;
};

}
