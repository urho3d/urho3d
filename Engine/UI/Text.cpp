//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Precompiled.h"
#include "Context.h"
#include "Font.h"
#include "Log.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "Text.h"
#include "Texture2D.h"

#include "DebugNew.h"

static const float MIN_ROW_SPACING = 0.5f;

static const std::string horizontalAlignments[] =
{
    "left",
    "center",
    "right"
};

OBJECTTYPESTATIC(Text);

Text::Text(Context* context) :
    UIElement(context),
    fontSize_(DEFAULT_FONT_SIZE),
    textAlignment_(HA_LEFT),
    rowSpacing_(1.0f),
    wordWrap_(false),
    selectionStart_(0),
    selectionLength_(0),
    selectionColor_(Color(0.0f, 0.0f, 0.0f, 0.0f)),
    hoverColor_(Color(0.0f, 0.0f, 0.0f, 0.0f)),
    rowHeight_(0)
{
}

Text::~Text()
{
}

void Text::RegisterObject(Context* context)
{
    context->RegisterFactory<Text>();
}

void Text::SetStyle(const XMLElement& element)
{
    UIElement::SetStyle(element);
    
    // Recalculating the text is expensive, so do it only once at the end if something changed
    bool changed = false;
    
    if (element.HasChildElement("font"))
    {
        XMLElement fontElem = element.GetChildElement("font");
        std::string fontName = fontElem.GetString("name");
        
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        if (cache->Exists(fontName))
        {
            Font* font = cache->GetResource<Font>(fontName);
            if (font)
            {
                font_ = font;
                fontSize_ = Max(fontElem.GetInt("size"), 1);
                changed = true;
            }
        }
        else if (element.HasChildElement("fallbackfont"))
        {
            fontElem = element.GetChildElement("fallbackfont");
            std::string fontName = fontElem.GetString("name");
            Font* font = cache->GetResource<Font>(fontName);
            if (font)
            {
                font_ = font;
                fontSize_ = Max(fontElem.GetInt("size"), 1);
                changed = true;
            }
        }
    }
    if (element.HasChildElement("text"))
    {
        std::string text = element.GetChildElement("text").GetString("value");
        ReplaceInPlace(text, "\\n", "\n");
        text_ = text;
        changed = true;
    }
    if (element.HasChildElement("textalignment"))
    {
        std::string horiz = element.GetChildElement("textalignment").GetStringLower("value");
        if (!horiz.empty())
        {
            textAlignment_ = (HorizontalAlignment)GetStringListIndex(horiz, horizontalAlignments, 3, 0);
            changed = true;
        }
    }
    if (element.HasChildElement("rowspacing"))
    {
        rowSpacing_ = Max(element.GetChildElement("rowspacing").GetFloat("value"), MIN_ROW_SPACING);
        changed = true;
    }
    if (element.HasChildElement("wordwrap"))
    {
        wordWrap_ = element.GetChildElement("wordwrap").GetBool("enable");
        changed = true;
    }
    if (element.HasChildElement("selection"))
    {
        XMLElement selectionElem = element.GetChildElement("selection");
        selectionStart_ = selectionElem.GetInt("start");
        selectionLength_ = selectionElem.GetInt("length");
        changed = true;
    }
    if (element.HasChildElement("selectioncolor"))
        SetSelectionColor(element.GetChildElement("selectioncolor").GetColor("value"));
    if (element.HasChildElement("hovercolor"))
        SetHoverColor(element.GetChildElement("hovercolor").GetColor("value"));
    
    if (changed)
    {
        ValidateSelection();
        UpdateText();
    }
}

void Text::GetBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor)
{
    // Hovering or whole selection batch
    if ((hovering_ && (hoverColor_.a_ > 0.0f)) || (selected_ && (selectionColor_.a_ > 0.0f)))
    {
        UIBatch batch;
        batch.Begin(&quads);
        batch.blendMode_ = BLEND_ALPHA;
        batch.scissor_ = currentScissor;
        batch.texture_ = 0;
        batch.AddQuad(*this, 0, 0, GetWidth(), GetHeight(), 0, 0, 0, 0, (selected_ && (selectionColor_.a_ > 0.0f)) ? selectionColor_ :
            hoverColor_);
        UIBatch::AddOrMerge(batch, batches);
    }
    
    // Partial selection batch
    if ((!selected_) && (selectionLength_) && (charSizes_.size() >= selectionStart_ + selectionLength_) && (selectionColor_.a_ > 0.0f))
    {
        UIBatch batch;
        batch.Begin(&quads);
        batch.blendMode_ = BLEND_ALPHA;
        batch.scissor_ = currentScissor;
        batch.texture_ = 0;
        
        IntVector2 currentStart = charPositions_[selectionStart_];
        IntVector2 currentEnd = currentStart;
        for (unsigned i = selectionStart_; i < selectionStart_ + selectionLength_; ++i)
        {
            // Check if row changes, and start a new quad in that case
            if ((charSizes_[i].x_) && (charSizes_[i].y_))
            {
                if (charPositions_[i].y_ != currentStart.y_)
                {
                    batch.AddQuad(*this, currentStart.x_, currentStart.y_, currentEnd.x_ - currentStart.x_, currentEnd.y_ - currentStart.y_,
                        0, 0, 0, 0, selectionColor_);
                    currentStart = charPositions_[i];
                    currentEnd = currentStart + charSizes_[i];
                }
                else
                {
                    currentEnd.x_ += charSizes_[i].x_;
                    currentEnd.y_ = Max(currentStart.y_ + charSizes_[i].y_, currentEnd.y_);
                }
            }
        }
        if (currentEnd != currentStart)
        {
            batch.AddQuad(*this, currentStart.x_, currentStart.y_, currentEnd.x_ - currentStart.x_, currentEnd.y_ - currentStart.y_,
                0, 0, 0, 0, selectionColor_);
        }
        
        UIBatch::AddOrMerge(batch, batches);
    }
    
    // Text batch
    if (font_)
    {
        const FontFace* face = font_->GetFace(fontSize_);
        if (!face)
            return;
        
        UIBatch batch;
        batch.Begin(&quads);
        batch.blendMode_ = BLEND_ALPHA;
        batch.scissor_ = currentScissor;
        batch.texture_ = face->texture_;
        
        unsigned rowIndex = 0;
        int x = GetRowStartPosition(rowIndex);
        int y = 0;
        
        for (unsigned i = 0; i < printText_.length(); ++i)
        {
            unsigned char c = (unsigned char)printText_[i];
            
            if (c != '\n')
            {
                const FontGlyph& glyph = face->glyphs_[face->glyphIndex_[c]];
                if (c != ' ')
                    batch.AddQuad(*this, x + glyph.offsetX_, y + glyph.offsetY_, glyph.width_, glyph.height_, glyph.x_, glyph.y_);
                x += glyph.advanceX_;
            }
            else
            {
                rowIndex++;
                x = GetRowStartPosition(rowIndex);
                y += rowHeight_;
            }
        }
        
        UIBatch::AddOrMerge(batch, batches);
    }
    
    // Reset hovering for next frame
    hovering_ = false;
}

void Text::OnResize()
{
    if (wordWrap_)
        UpdateText();
}

bool Text::SetFont(const std::string& fontName, int size)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    return SetFont(cache->GetResource<Font>(fontName), size);
}

bool Text::SetFont(Font* font, int size)
{
    if (!font)
    {
        LOGERROR("Null font for Text");
        return false;
    }
    
    if ((font != font_) || (size != fontSize_))
    {
        font_ = font;
        fontSize_ = Max(size, 1);
        UpdateText();
    }
    
    return true;
}

void Text::SetText(const std::string& text)
{
    text_ = text;
    
    ValidateSelection();
    UpdateText();
}

void Text::SetTextAlignment(HorizontalAlignment align)
{
    if (align != textAlignment_)
    {
        textAlignment_ = align;
        UpdateText();
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

void Text::SetSelectionColor(const Color& color)
{
    selectionColor_ = color;
}

void Text::SetHoverColor(const Color& color)
{
    hoverColor_ = color;
}

void Text::UpdateText(bool inResize)
{
    int width = 0;
    int height = 0;
    
    rowWidths_.clear();
    printText_.clear();
    
    std::vector<unsigned> printToText;
    
    if (font_)
    {
        const FontFace* face = font_->GetFace(fontSize_);
        if (!face)
            return;
        rowHeight_ = face->rowHeight_;
        int rowWidth = 0;
        int rowHeight = (int)(rowSpacing_ * rowHeight_);
        
        // First see if the text must be split up
        if (!wordWrap_)
        {
            printText_ = text_;
            printToText.resize(text_.length());
            for (unsigned i = 0; i < text_.length(); ++i)
                printToText[i] = i;
        }
        else
        {
            int maxWidth = GetWidth();
            unsigned nextBreak = 0;
            unsigned lineStart = 0;
            for (unsigned i = 0; i < text_.length(); ++i)
            {
                unsigned j;
                if (text_[i] != '\n')
                {
                    bool ok = true;
                    
                    if (nextBreak <= i)
                    {
                        int futureRowWidth = rowWidth;
                        for (j = i; j < text_.length(); ++j)
                        {
                            if ((text_[j] == ' ') || (text_[j] == '\n'))
                            {
                                nextBreak = j;
                                break;
                            }
                            futureRowWidth += face->glyphs_[face->glyphIndex_[text_[j]]].advanceX_;
                            if ((text_[j] == '-') && (futureRowWidth <= maxWidth))
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
                            int copyLength = Max(j - i, 1);
                            printText_ += text_.substr(i, copyLength);
                            for (int k = 0; k < copyLength; ++k)
                            {
                                printToText.push_back(i);
                                ++i;
                            }
                        }
                        printText_ += '\n';
                        printToText.push_back(Min((int)i, (int)text_.length() - 1));
                        rowWidth = 0;
                        nextBreak = lineStart = i;
                    }
                    
                    if (i < text_.length())
                    {
                        // When copying a space, position is allowed to be over row width
                        rowWidth += face->glyphs_[face->glyphIndex_[text_[i]]].advanceX_;
                        if (rowWidth <= maxWidth)
                        {
                            printText_ += text_[i];
                            printToText.push_back(i);
                        }
                    }
                }
                else
                {
                    printText_ += '\n';
                    printToText.push_back(Min((int)i, (int)text_.length() - 1));
                    rowWidth = 0;
                    nextBreak = lineStart = i;
                }
            }
        }
        
        rowWidth = 0;
        
        for (unsigned i = 0; i < printText_.length(); ++i)
        {
            unsigned char c = (unsigned char)printText_[i];
            
            if (c != '\n')
            {
                const FontGlyph& glyph = face->glyphs_[face->glyphIndex_[c]];
                rowWidth += glyph.advanceX_;
            }
            else
            {
                width = Max(width, rowWidth);
                height += rowHeight;
                rowWidths_.push_back(rowWidth);
                rowWidth = 0;
            }
        }
        
        if (rowWidth)
        {
            width = Max(width, rowWidth);
            height += rowHeight;
            rowWidths_.push_back(rowWidth);
        }
        
        // Set row height even if text is empty
        if (!height)
            height = rowHeight;
        
        // Store position & size of each character
        charPositions_.resize(text_.length() + 1);
        charSizes_.resize(text_.length());
        
        unsigned rowIndex = 0;
        int x = GetRowStartPosition(rowIndex);
        int y = 0;
        for (unsigned i = 0; i < printText_.length(); ++i)
        {
            charPositions_[printToText[i]] = IntVector2(x, y);
            unsigned char c = (unsigned char)printText_[i];
            if (c != '\n')
            {
                const FontGlyph& glyph = face->glyphs_[face->glyphIndex_[c]];
                charSizes_[printToText[i]] = IntVector2(glyph.advanceX_, rowHeight_);
                x += glyph.advanceX_;
            }
            else
            {
                charSizes_[printToText[i]] = IntVector2::ZERO;
                rowIndex++;
                x = GetRowStartPosition(rowIndex);
                y += rowHeight;
            }
        }
        // Store the ending position
        charPositions_[text_.length()] = IntVector2(x, y);
    }
    
    // Set minimum and current size according to the text size, but respect fixed width if set
    if (GetMinWidth() != GetMaxWidth())
    {
        SetMinWidth(width);
        SetWidth(width);
    }
    SetFixedHeight(height);
}

void Text::ValidateSelection()
{
    unsigned textLength = text_.length();
    
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
    int rowWidth = 0;
    
    if (rowIndex < rowWidths_.size())
        rowWidth = rowWidths_[rowIndex];
    
    switch (textAlignment_)
    {
    default:
        return 0;
    case HA_CENTER:
        return (GetSize().x_ - rowWidth) / 2;
    case HA_RIGHT:
        return GetSize().x_ - rowWidth;
    }
}
