//
// Copyright (c) 2008-2019 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/Profiler.h"
#include "../Graphics/Texture2D.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"
#include "../UI/Font.h"
#include "../UI/FontFace.h"
#include "../UI/Text.h"
#include "../Resource/Localization.h"
#include "../Resource/ResourceEvents.h"

#include "../DebugNew.h"

namespace Urho3D
{

const char* textEffects[] =
{
    "None",
    "Shadow",
    "Stroke",
    nullptr
};

static const float MIN_ROW_SPACING = 0.5f;

extern const char* horizontalAlignments[];
extern const char* UI_CATEGORY;

Text::Text(Context* context) :
    UISelectable(context),
    fontSize_(DEFAULT_FONT_SIZE),
    textAlignment_(HA_LEFT),
    rowSpacing_(1.0f),
    wordWrap_(false),
    autoLocalizable_(false),
    charLocationsDirty_(true),
    selectionStart_(0),
    selectionLength_(0),
    textEffect_(TE_NONE),
    shadowOffset_(IntVector2(1, 1)),
    strokeThickness_(1),
    roundStroke_(false),
    effectColor_(Color::BLACK),
    effectDepthBias_(0.0f),
    rowHeight_(0)
{
    // By default Text does not derive opacity from parent elements
    useDerivedOpacity_ = false;
}

Text::~Text() = default;

void Text::RegisterObject(Context* context)
{
    context->RegisterFactory<Text>(UI_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(UISelectable);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Use Derived Opacity", false);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Font", GetFontAttr, SetFontAttr, ResourceRef, ResourceRef(Font::GetTypeStatic()), AM_FILE);
    URHO3D_ATTRIBUTE("Font Size", float, fontSize_, DEFAULT_FONT_SIZE, AM_FILE);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Text", GetTextAttr, SetTextAttr, String, String::EMPTY, AM_FILE);
    URHO3D_ENUM_ATTRIBUTE("Text Alignment", textAlignment_, horizontalAlignments, HA_LEFT, AM_FILE);
    URHO3D_ATTRIBUTE("Row Spacing", float, rowSpacing_, 1.0f, AM_FILE);
    URHO3D_ATTRIBUTE("Word Wrap", bool, wordWrap_, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Auto Localizable", GetAutoLocalizable, SetAutoLocalizable, bool, false, AM_FILE);
    URHO3D_ENUM_ATTRIBUTE("Text Effect", textEffect_, textEffects, TE_NONE, AM_FILE);
    URHO3D_ATTRIBUTE("Shadow Offset", IntVector2, shadowOffset_, IntVector2(1, 1), AM_FILE);
    URHO3D_ATTRIBUTE("Stroke Thickness", int, strokeThickness_, 1, AM_FILE);
    URHO3D_ATTRIBUTE("Round Stroke", bool, roundStroke_, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Effect Color", GetEffectColor, SetEffectColor, Color, Color::BLACK, AM_FILE);

    // Change the default value for UseDerivedOpacity
    context->GetAttribute<Text>("Use Derived Opacity")->defaultValue_ = false;
}

void Text::ApplyAttributes()
{
    UISelectable::ApplyAttributes();

    // Localize now if attributes were loaded out-of-order
    if (autoLocalizable_ && stringId_.Length())
    {
        auto* l10n = GetSubsystem<Localization>();
        text_ = l10n->Get(stringId_);
    }

    DecodeToUnicode();

    fontSize_ = Max(fontSize_, 1);
    strokeThickness_ = Abs(strokeThickness_);
    ValidateSelection();
    UpdateText();
}

void Text::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    FontFace* face = font_ ? font_->GetFace(fontSize_) : nullptr;
    if (!face)
    {
        hovering_ = false;
        return;
    }

    // If face has changed or char locations are not valid anymore, update before rendering
    if (charLocationsDirty_ || !fontFace_ || face != fontFace_)
        UpdateCharLocations();
    // If face uses mutable glyphs mechanism, reacquire glyphs before rendering to make sure they are in the texture
    else if (face->HasMutableGlyphs())
    {
        for (unsigned i = 0; i < printText_.Size(); ++i)
            face->GetGlyph(printText_[i]);
    }

    // Hovering and/or whole selection batch
    UISelectable::GetBatches(batches, vertexData, currentScissor);

    // Partial selection batch
    if (!selected_ && selectionLength_ && charLocations_.Size() >= selectionStart_ + selectionLength_ && selectionColor_.a_ > 0.0f)
    {
        UIBatch batch(this, BLEND_ALPHA, currentScissor, nullptr, &vertexData);
        batch.SetColor(selectionColor_);

        Vector2 currentStart = charLocations_[selectionStart_].position_;
        Vector2 currentEnd = currentStart;
        for (unsigned i = selectionStart_; i < selectionStart_ + selectionLength_; ++i)
        {
            // Check if row changes, and start a new quad in that case
            if (charLocations_[i].size_ != Vector2::ZERO)
            {
                if (charLocations_[i].position_.y_ != currentStart.y_)
                {
                    batch.AddQuad(currentStart.x_, currentStart.y_, currentEnd.x_ - currentStart.x_,
                        currentEnd.y_ - currentStart.y_, 0, 0);
                    currentStart = charLocations_[i].position_;
                    currentEnd = currentStart + charLocations_[i].size_;
                }
                else
                {
                    currentEnd.x_ += charLocations_[i].size_.x_;
                    currentEnd.y_ = Max(currentStart.y_ + charLocations_[i].size_.y_, currentEnd.y_);
                }
            }
        }
        if (currentEnd != currentStart)
        {
            batch.AddQuad(currentStart.x_, currentStart.y_, currentEnd.x_ - currentStart.x_, currentEnd.y_ - currentStart.y_, 0, 0);
        }

        UIBatch::AddOrMerge(batch, batches);
    }

    // Text batch
    TextEffect textEffect = font_->IsSDFFont() ? TE_NONE : textEffect_;
    const Vector<SharedPtr<Texture2D> >& textures = face->GetTextures();
    for (unsigned n = 0; n < textures.Size() && n < pageGlyphLocations_.Size(); ++n)
    {
        // One batch per texture/page
        UIBatch pageBatch(this, BLEND_ALPHA, currentScissor, textures[n], &vertexData);

        const PODVector<GlyphLocation>& pageGlyphLocation = pageGlyphLocations_[n];

        switch (textEffect)
        {
        case TE_NONE:
            ConstructBatch(pageBatch, pageGlyphLocation, 0, 0);
            break;

        case TE_SHADOW:
            ConstructBatch(pageBatch, pageGlyphLocation, shadowOffset_.x_, shadowOffset_.y_, &effectColor_, effectDepthBias_);
            ConstructBatch(pageBatch, pageGlyphLocation, 0, 0);
            break;

        case TE_STROKE:
            if (roundStroke_)
            {
                // Samples should be even or glyph may be redrawn in wrong x y pos making stroke corners rough
                // Adding to thickness helps with thickness of 1 not having enought samples for this formula
                // or certain fonts with reflex corners requiring more glyph samples for a smooth stroke when large
                int thickness = Min(strokeThickness_, fontSize_);
                int samples = thickness * thickness + (thickness % 2 == 0 ? 4 : 3);
                float angle = 360.f / samples;
                auto floatThickness = (float)thickness;
                for (int i = 0; i < samples; ++i)
                {
                    float x = Cos(angle * i) * floatThickness;
                    float y = Sin(angle * i) * floatThickness;
                    ConstructBatch(pageBatch, pageGlyphLocation, x, y, &effectColor_, effectDepthBias_);
                }
            }
            else
            {
                int thickness = Min(strokeThickness_, fontSize_);
                int x, y;
                for (x = -thickness; x <= thickness; ++x)
                {
                    for (y = -thickness; y <= thickness; ++y)
                    {
                        // Don't draw glyphs that aren't on the edges
                        if (x > -thickness && x < thickness &&
                            y > -thickness && y < thickness)
                            continue;

                        ConstructBatch(pageBatch, pageGlyphLocation, x, y, &effectColor_, effectDepthBias_);
                    }
                }
            }
            ConstructBatch(pageBatch, pageGlyphLocation, 0, 0);
            break;
        }

        UIBatch::AddOrMerge(pageBatch, batches);
    }
}

void Text::OnResize(const IntVector2& newSize, const IntVector2& delta)
{
    if (wordWrap_)
        UpdateText(true);
    else
        charLocationsDirty_ = true;
}

void Text::OnIndentSet()
{
    charLocationsDirty_ = true;
}

bool Text::SetFont(const String& fontName, float size)
{
    auto* cache = GetSubsystem<ResourceCache>();
    return SetFont(cache->GetResource<Font>(fontName), size);
}

bool Text::SetFont(Font* font, float size)
{
    if (!font)
    {
        URHO3D_LOGERROR("Null font for Text");
        return false;
    }

    if (font != font_ || size != fontSize_)
    {
        font_ = font;
        fontSize_ = Max(size, 1);
        UpdateText();
    }

    return true;
}

bool Text::SetFontSize(float size)
{
    // Initial font must be set
    if (!font_)
        return false;
    else
        return SetFont(font_, size);
}

void Text::DecodeToUnicode()
{
    unicodeText_.Clear();
    for (unsigned i = 0; i < text_.Length();)
        unicodeText_.Push(text_.NextUTF8Char(i));
}

void Text::SetText(const String& text)
{
    if (autoLocalizable_)
    {
        stringId_ = text;
        auto* l10n = GetSubsystem<Localization>();
        text_ = l10n->Get(stringId_);
    }
    else
    {
        text_ = text;
    }

    DecodeToUnicode();
    ValidateSelection();
    UpdateText();
}

void Text::SetTextAlignment(HorizontalAlignment align)
{
    if (align != textAlignment_)
    {
        textAlignment_ = align;
        charLocationsDirty_ = true;
    }
}

void Text::SetRowSpacing(float spacing)
{
    if (spacing != rowSpacing_)
    {
        rowSpacing_ = Max(spacing, MIN_ROW_SPACING);
        UpdateText();
    }
}

void Text::SetWordwrap(bool enable)
{
    if (enable != wordWrap_)
    {
        wordWrap_ = enable;
        UpdateText();
    }
}

void Text::SetAutoLocalizable(bool enable)
{
    if (enable != autoLocalizable_)
    {
        autoLocalizable_ = enable;
        if (enable)
        {
            stringId_ = text_;
            auto* l10n = GetSubsystem<Localization>();
            text_ = l10n->Get(stringId_);
            SubscribeToEvent(E_CHANGELANGUAGE, URHO3D_HANDLER(Text, HandleChangeLanguage));
        }
        else
        {
            text_ = stringId_;
            stringId_ = "";
            UnsubscribeFromEvent(E_CHANGELANGUAGE);
        }
        DecodeToUnicode();
        ValidateSelection();
        UpdateText();
    }
}

void Text::HandleChangeLanguage(StringHash eventType, VariantMap& eventData)
{
    auto* l10n = GetSubsystem<Localization>();
    text_ = l10n->Get(stringId_);
    DecodeToUnicode();
    ValidateSelection();
    UpdateText();
}

void Text::SetSelection(unsigned start, unsigned length)
{
    selectionStart_ = start;
    selectionLength_ = length;
    ValidateSelection();
}

void Text::ClearSelection()
{
    selectionStart_ = 0;
    selectionLength_ = 0;
}

void Text::SetTextEffect(TextEffect textEffect)
{
    textEffect_ = textEffect;
}

void Text::SetEffectShadowOffset(const IntVector2& offset)
{
    shadowOffset_ = offset;
}

void Text::SetEffectStrokeThickness(int thickness)
{
    strokeThickness_ = Abs(thickness);
}

void Text::SetEffectRoundStroke(bool roundStroke)
{
    roundStroke_ = roundStroke;
}

void Text::SetEffectColor(const Color& effectColor)
{
    effectColor_ = effectColor;
}

void Text::SetEffectDepthBias(float bias)
{
    effectDepthBias_ = bias;
}

float Text::GetRowWidth(unsigned index) const
{
    return index < rowWidths_.Size() ? rowWidths_[index] : 0;
}

float Text::GetMaxRowWidth() const
{
    float maxWidth = 0;
    for (float rowWidth : rowWidths_)
        maxWidth = Max(maxWidth, rowWidth);
    return maxWidth;
}

Vector2 Text::GetCharPosition(unsigned index)
{
    if (charLocationsDirty_)
        UpdateCharLocations();
    if (charLocations_.Empty())
        return Vector2::ZERO;
    // For convenience, return the position of the text ending if index exceeded
    if (index > charLocations_.Size() - 1)
        index = charLocations_.Size() - 1;
    return charLocations_[index].position_;
}

Vector2 Text::GetCharSize(unsigned index)
{
    if (charLocationsDirty_)
        UpdateCharLocations();
    if (charLocations_.Size() < 2)
        return Vector2::ZERO;
    // For convenience, return the size of the last char if index exceeded (last size entry is zero)
    if (index > charLocations_.Size() - 2)
        index = charLocations_.Size() - 2;
    return charLocations_[index].size_;
}

void Text::SetFontAttr(const ResourceRef& value)
{
    auto* cache = GetSubsystem<ResourceCache>();
    font_ = cache->GetResource<Font>(value.name_);
}

ResourceRef Text::GetFontAttr() const
{
    return GetResourceRef(font_, Font::GetTypeStatic());
}

void Text::SetTextAttr(const String& value)
{
    text_ = value;
    if (autoLocalizable_)
        stringId_ = value;
}

String Text::GetTextAttr() const
{
    if (autoLocalizable_ && stringId_.Length())
        return stringId_;
    else
        return text_;
}

bool Text::FilterImplicitAttributes(XMLElement& dest) const
{
    if (!UISelectable::FilterImplicitAttributes(dest))
        return false;

    if (!IsFixedWidth())
    {
        if (!RemoveChildXML(dest, "Size"))
            return false;
        if (!RemoveChildXML(dest, "Min Size"))
            return false;
        if (!RemoveChildXML(dest, "Max Size"))
            return false;
    }

    return true;
}

void Text::UpdateText(bool onResize)
{
    rowWidths_.Clear();
    printText_.Clear();

    if (font_)
    {
        FontFace* face = font_->GetFace(fontSize_);
        if (!face)
            return;

        rowHeight_ = face->GetRowHeight();

        int width = 0;
        int height = 0;
        int rowWidth = 0;
        auto rowHeight = RoundToInt(rowSpacing_ * rowHeight_);

        // First see if the text must be split up
        if (!wordWrap_)
        {
            printText_ = unicodeText_;
            printToText_.Resize(printText_.Size());
            for (unsigned i = 0; i < printText_.Size(); ++i)
                printToText_[i] = i;
        }
        else
        {
            int maxWidth = GetWidth();
            unsigned nextBreak = 0;
            unsigned lineStart = 0;
            printToText_.Clear();

            for (unsigned i = 0; i < unicodeText_.Size(); ++i)
            {
                unsigned j;
                unsigned c = unicodeText_[i];

                if (c != '\n')
                {
                    bool ok = true;

                    if (nextBreak <= i)
                    {
                        int futureRowWidth = rowWidth;
                        for (j = i; j < unicodeText_.Size(); ++j)
                        {
                            unsigned d = unicodeText_[j];
                            if (d == ' ' || d == '\n')
                            {
                                nextBreak = j;
                                break;
                            }
                            const FontGlyph* glyph = face->GetGlyph(d);
                            if (glyph)
                            {
                                futureRowWidth += glyph->advanceX_;
                                if (j < unicodeText_.Size() - 1)
                                    futureRowWidth += face->GetKerning(d, unicodeText_[j + 1]);
                            }
                            if (d == '-' && futureRowWidth <= maxWidth)
                            {
                                nextBreak = j + 1;
                                break;
                            }
                            if (futureRowWidth > maxWidth)
                            {
                                ok = false;
                                break;
                            }
                        }
                    }

                    if (!ok)
                    {
                        // If did not find any breaks on the line, copy until j, or at least 1 char, to prevent infinite loop
                        if (nextBreak == lineStart)
                        {
                            while (i < j)
                            {
                                printText_.Push(unicodeText_[i]);
                                printToText_.Push(i);
                                ++i;
                            }
                        }
                        // Eliminate spaces that have been copied before the forced break
                        while (printText_.Size() && printText_.Back() == ' ')
                        {
                            printText_.Pop();
                            printToText_.Pop();
                        }
                        printText_.Push('\n');
                        printToText_.Push(Min(i, unicodeText_.Size() - 1));
                        rowWidth = 0;
                        nextBreak = lineStart = i;
                    }

                    if (i < unicodeText_.Size())
                    {
                        // When copying a space, position is allowed to be over row width
                        c = unicodeText_[i];
                        const FontGlyph* glyph = face->GetGlyph(c);
                        if (glyph)
                        {
                            rowWidth += glyph->advanceX_;
                            if (i < unicodeText_.Size() - 1)
                                rowWidth += face->GetKerning(c, unicodeText_[i + 1]);
                        }
                        if (rowWidth <= maxWidth)
                        {
                            printText_.Push(c);
                            printToText_.Push(i);
                        }
                    }
                }
                else
                {
                    printText_.Push('\n');
                    printToText_.Push(Min(i, unicodeText_.Size() - 1));
                    rowWidth = 0;
                    nextBreak = lineStart = i;
                }
            }
        }

        rowWidth = 0;

        for (unsigned i = 0; i < printText_.Size(); ++i)
        {
            unsigned c = printText_[i];

            if (c != '\n')
            {
                const FontGlyph* glyph = face->GetGlyph(c);
                if (glyph)
                {
                    rowWidth += glyph->advanceX_;
                    if (i < printText_.Size() - 1)
                        rowWidth += face->GetKerning(c, printText_[i + 1]);
                }
            }
            else
            {
                width = Max(width, rowWidth);
                height += rowHeight;
                rowWidths_.Push(rowWidth);
                rowWidth = 0;
            }
        }

        if (rowWidth)
        {
            width = Max(width, rowWidth);
            height += rowHeight;
            rowWidths_.Push(rowWidth);
        }

        // Set at least one row height even if text is empty
        if (!height)
            height = rowHeight;

        // Set minimum and current size according to the text size, but respect fixed width if set
        if (!IsFixedWidth())
        {
            if (wordWrap_)
                SetMinWidth(0);
            else
            {
                SetMinWidth(width);
                SetWidth(width);
            }
        }
        SetFixedHeight(height);

        charLocationsDirty_ = true;
    }
    else
    {
        // No font, nothing to render
        pageGlyphLocations_.Clear();
    }

    // If wordwrap is on, parent may need layout update to correct for overshoot in size. However, do not do this when the
    // update is a response to resize, as that could cause infinite recursion
    if (wordWrap_ && !onResize)
    {
        UIElement* parent = GetParent();
        if (parent && parent->GetLayoutMode() != LM_FREE)
            parent->UpdateLayout();
    }
}

void Text::UpdateCharLocations()
{
    // Remember the font face to see if it's still valid when it's time to render
    FontFace* face = font_ ? font_->GetFace(fontSize_) : nullptr;
    if (!face)
        return;
    fontFace_ = face;

    auto rowHeight = RoundToInt(rowSpacing_ * rowHeight_);

    // Store position & size of each character, and locations per texture page
    unsigned numChars = unicodeText_.Size();
    charLocations_.Resize(numChars + 1);
    pageGlyphLocations_.Resize(face->GetTextures().Size());
    for (unsigned i = 0; i < pageGlyphLocations_.Size(); ++i)
        pageGlyphLocations_[i].Clear();

    IntVector2 offset = font_->GetTotalGlyphOffset(fontSize_);

    unsigned rowIndex = 0;
    unsigned lastFilled = 0;
    float x = Round(GetRowStartPosition(rowIndex) + offset.x_);
    float y = Round(offset.y_);

    for (unsigned i = 0; i < printText_.Size(); ++i)
    {
        CharLocation loc;
        loc.position_ = Vector2(x, y);

        unsigned c = printText_[i];
        if (c != '\n')
        {
            const FontGlyph* glyph = face->GetGlyph(c);
            loc.size_ = Vector2(glyph ? glyph->advanceX_ : 0, rowHeight_);
            if (glyph)
            {
                // Store glyph's location for rendering. Verify that glyph page is valid
                if (glyph->page_ < pageGlyphLocations_.Size())
                    pageGlyphLocations_[glyph->page_].Push(GlyphLocation(x, y, glyph));
                x += glyph->advanceX_;
                if (i < printText_.Size() - 1)
                    x += face->GetKerning(c, printText_[i + 1]);
            }
        }
        else
        {
            loc.size_ = Vector2::ZERO;
            x = GetRowStartPosition(++rowIndex);
            y += rowHeight;
        }

        if (lastFilled > printToText_[i])
            lastFilled = printToText_[i];

        // Fill gaps in case characters were skipped from printing
        for (unsigned j = lastFilled; j <= printToText_[i]; ++j)
            charLocations_[j] = loc;
        lastFilled = printToText_[i] + 1;
    }
    // Store the ending position
    charLocations_[numChars].position_ = Vector2(x, y);
    charLocations_[numChars].size_ = Vector2::ZERO;

    charLocationsDirty_ = false;
}

void Text::ValidateSelection()
{
    unsigned textLength = unicodeText_.Size();

    if (textLength)
    {
        if (selectionStart_ >= textLength)
            selectionStart_ = textLength - 1;
        if (selectionStart_ + selectionLength_ > textLength)
            selectionLength_ = textLength - selectionStart_;
    }
    else
    {
        selectionStart_ = 0;
        selectionLength_ = 0;
    }
}

int Text::GetRowStartPosition(unsigned rowIndex) const
{
    float rowWidth = 0;

    if (rowIndex < rowWidths_.Size())
        rowWidth = rowWidths_[rowIndex];

    int ret = GetIndentWidth();

    switch (textAlignment_)
    {
    case HA_LEFT:
        break;
    case HA_CENTER:
        ret += (GetSize().x_ - rowWidth) / 2;
        break;
    case HA_RIGHT:
        ret += GetSize().x_ - rowWidth;
        break;
    }

    return ret;
}

void Text::ConstructBatch(UIBatch& pageBatch, const PODVector<GlyphLocation>& pageGlyphLocation, float dx, float dy, Color* color,
    float depthBias)
{
    unsigned startDataSize = pageBatch.vertexData_->Size();

    if (!color)
        pageBatch.SetDefaultColor();
    else
        pageBatch.SetColor(*color);

    for (unsigned i = 0; i < pageGlyphLocation.Size(); ++i)
    {
        const GlyphLocation& glyphLocation = pageGlyphLocation[i];
        const FontGlyph& glyph = *glyphLocation.glyph_;
        pageBatch.AddQuad(dx + glyphLocation.x_ + glyph.offsetX_, dy + glyphLocation.y_ + glyph.offsetY_, glyph.width_,
            glyph.height_, glyph.x_, glyph.y_, glyph.texWidth_, glyph.texHeight_);
    }

    if (depthBias != 0.0f)
    {
        unsigned dataSize = pageBatch.vertexData_->Size();
        for (unsigned i = startDataSize; i < dataSize; i += UI_VERTEX_SIZE)
            pageBatch.vertexData_->At(i + 2) += depthBias;
    }
}

}
