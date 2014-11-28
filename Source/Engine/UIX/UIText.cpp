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

#include "Precompiled.h"
#include "Context.h"
#include "Font.h"
#include "FontFace.h"
#include "Log.h"
#include "Material.h"
#include "Node.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Technique.h"
#include "Texture2D.h"
#include "UIRect.h"
#include "UIText.h"
#include "UIXEvents.h"

#include "DebugNew.h"

namespace Urho3D
{

static const float MIN_ROW_SPACING = 0.5f;

extern const char* textEffects[];
extern const char* horizontalAlignments[];
extern const char* UIX_CATEGORY;

void UITextLineInfo::Clear()
{
    lineWidth_ = 0.0f;
    fontGlyphs_.Clear();
    glyphAdvances_.Clear();    
}

void UITextLineInfo::Add(const FontGlyph* glyph, short kerning)
{
    fontGlyphs_.Push(glyph);
    
    float advance = (glyph->advanceX_ + kerning) * PIXEL_SIZE;
    lineWidth_ += advance;
    glyphAdvances_.Push(advance);
}

UIText::UIText(Context* context) :
    Drawable2D(context),
    usedInText3D_(false),
    fontSize_(DEFAULT_FONT_SIZE),
    textAlignment_(HA_LEFT),
    rowSpacing_(1.0f),
    color_(Color::WHITE),
    selectionStart_(0),
    selectionLength_(0),
    selectionColor_(Color::TRANSPARENT),
    textEffect_(TE_NONE),
    effectColor_(Color::BLACK),
    rowHeight_(0.0f),
    numChars_(0)
{
}

UIText::~UIText()
{
}

void UIText::RegisterObject(Context* context)
{
    context->RegisterFactory<UIText>(UIX_CATEGORY);

    MIXED_ACCESSOR_ATTRIBUTE("Font", GetFontAttr, SetFontAttr, ResourceRef, ResourceRef(Font::GetTypeStatic()), AM_FILE);
    ACCESSOR_ATTRIBUTE("Font Size", GetFontSize, SetFontSize, int, DEFAULT_FONT_SIZE, AM_FILE);
    ACCESSOR_ATTRIBUTE("Text", GetText, SetText, String, String::EMPTY, AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE("Text Alignment", GetTextAlignment, SetTextAlignment, HorizontalAlignment, horizontalAlignments, HA_LEFT, AM_FILE);
    ACCESSOR_ATTRIBUTE("Row Spacing", GetRowSpacing, SetRowSpacing, float, 1.0f, AM_FILE);
    ACCESSOR_ATTRIBUTE("Color", GetColor, SetColor, Color, Color::WHITE, AM_FILE);
    ACCESSOR_ATTRIBUTE("Selection Color", GetSelectionColor, SetSelectionColor, Color, Color::TRANSPARENT, AM_FILE);
    ENUM_ACCESSOR_ATTRIBUTE("Text Effect", GetTextEffect, SetTextEffect, TextEffect, textEffects, TE_NONE, AM_FILE);
    ACCESSOR_ATTRIBUTE("Effect Color", GetEffectColor, SetEffectColor, Color, Color::BLACK, AM_FILE);
    COPY_BASE_ATTRIBUTES(Drawable2D);
}

bool UIText::SetFont(const String& fontName, int size)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    return SetFont(cache->GetResource<Font>(fontName), size);
}

bool UIText::SetFont(Font* font, int size)
{
    if (!font)
    {
        LOGERROR("Null font for Text");
        return false;
    }

    if (font != font_ || size != fontSize_)
    {
        font_ = font;
        fontSize_ = Max(size, 1);

        if (font_)
        {
            fontFace_ = font->GetFace(fontSize_);
            SetTexture(fontFace_->GetTextures()[0]);
            UpdateMaterial(true);
        }
        else
        {
            SetTexture(0);
            SetCustomMaterial(0);
        }
        
        UpdateText();
        verticesDirty_ = true;
    }

    return true;
}

void UIText::SetFontSize(int fontSize)
{
    SetFont(font_, fontSize);
}

void UIText::SetText(const String& text)
{
    if (text == text_)
        return;

    text_ = text;
    
    UpdateText();
    ValidateSelection();

    verticesDirty_ = true;
}

void UIText::SetTextAlignment(HorizontalAlignment align)
{
    if (align == textAlignment_)
        return;
    
    textAlignment_ = align;
    verticesDirty_ = true;
}

void UIText::SetRowSpacing(float spacing)
{
    if (spacing == rowSpacing_)
        return;

    rowSpacing_ = Max(spacing, MIN_ROW_SPACING);
    verticesDirty_ = true;
}

void UIText::SetColor(const Color& color)
{
    if (color == color_)
        return;

    color_ = color;

    verticesDirty_ = true;
}

void UIText::SetSelection(unsigned start, unsigned length)
{
    if (start == selectionStart_ && length == selectionLength_)
        return;

    selectionStart_ = start;
    selectionLength_ = length;

    ValidateSelection();
    verticesDirty_ = true;
}

void UIText::ClearSelection()
{
    selectionStart_ = 0;
    
    if (selectionLength_ != 0)
    {
        selectionLength_ = 0;
        verticesDirty_ = true;
    }
}

void UIText::SetSelectionColor(const Color& color)
{
    if (color == selectionColor_)
        return;

    selectionColor_ = color;

    if (selectionLength_ != 0)
        verticesDirty_ = true;
}

void UIText::SetTextEffect(TextEffect textEffect)
{
    if (textEffect == textEffect_)
        return;

    textEffect_ = textEffect;

    UpdateMaterial();
    verticesDirty_ = true;
}

void UIText::SetEffectColor(const Color& effectColor)
{
    if (effectColor == effectColor_)
        return;

    effectColor_ = effectColor;

    if (textEffect_ != TE_NONE)
        verticesDirty_ = true;
}

void UIText::SetFontAttr(const ResourceRef& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetFont(cache->GetResource<Font>(value.name_), fontSize_);
}

ResourceRef UIText::GetFontAttr() const
{
    return GetResourceRef(font_, Font::GetTypeStatic());
}

void UIText::OnNodeSet(Node* node)
{
    Drawable2D::OnNodeSet(node);

    if (node)
    {
        uiRect_ = node->GetComponent<UIRect>();
        if (uiRect_)
            SubscribeToEvent(uiRect_, E_UIRECTDIRTIED, HANDLER(UIText, HandleRectDirtied));
        else
            LOGERROR("UIRect must by added first");
    }
}

void UIText::OnWorldBoundingBoxUpdate()
{
    boundingBox_.Clear();

    if (uiRect_)
    {
        const Rect& rect = uiRect_->GetRect();
        boundingBox_.Merge(rect.min_);
        boundingBox_.Merge(rect.max_);
    }

    worldBoundingBox_ = boundingBox_;
}

void UIText::UpdateVertices()
{
    if (!verticesDirty_)
        return;

    vertices_.Clear();

    if (textLineInfo_.Empty())
        return;

    TextEffect textEffect = font_->IsSDFFont() ? TE_NONE : textEffect_;
    const Vector<SharedPtr<Texture2D> >& textures = fontFace_->GetTextures();

    const Rect& rect = uiRect_->GetRect();
    float totalHeight = textLineInfo_.Size() * rowHeight_;

    unsigned color = color_.ToUInt();
    unsigned effectColor = effectColor_.ToUInt();

    for (unsigned i = 0; i < textLineInfo_.Size(); ++i)
    {
        const UITextLineInfo& lineInfo = textLineInfo_[i];
        
        float x;
        switch (textAlignment_)
        {
        case HA_LEFT:
            x = rect.min_.x_;
            break;
        case HA_CENTER:
            x = rect.Center().x_ - lineInfo.lineWidth_ * 0.5f;
            break;
        case HA_RIGHT:
            x = rect.max_.x_ - lineInfo.lineWidth_;
            break;
        }

        float y = rect.Center().y_ + totalHeight * 0.5f - rowHeight_ * i;

        switch (textEffect)
        {
        case TE_NONE:
            UpdateTextLineVertices(lineInfo, x, y, color);
            break;

        case TE_SHADOW:
            UpdateTextLineVertices(lineInfo, x + PIXEL_SIZE, y - PIXEL_SIZE, effectColor);
            UpdateTextLineVertices(lineInfo, x, y, color);
            break;

        case TE_STROKE:
            UpdateTextLineVertices(lineInfo, x - PIXEL_SIZE, y - PIXEL_SIZE, effectColor);
            UpdateTextLineVertices(lineInfo, x             , y - PIXEL_SIZE, effectColor);
            UpdateTextLineVertices(lineInfo, x + PIXEL_SIZE, y - PIXEL_SIZE, effectColor);

            UpdateTextLineVertices(lineInfo, x - PIXEL_SIZE, y, effectColor);
            UpdateTextLineVertices(lineInfo, x + PIXEL_SIZE, y, effectColor);
            
            UpdateTextLineVertices(lineInfo, x - PIXEL_SIZE, y + PIXEL_SIZE, effectColor);
            UpdateTextLineVertices(lineInfo, x             , y + PIXEL_SIZE, effectColor);
            UpdateTextLineVertices(lineInfo, x + PIXEL_SIZE, y + PIXEL_SIZE, effectColor);

            UpdateTextLineVertices(lineInfo, x, y, color);
            break;
        }
    }

    verticesDirty_ = false;
}

void UIText::HandleRectDirtied(StringHash eventType, VariantMap& eventData)
{
    worldBoundingBoxDirty_ = true;
    verticesDirty_ = true;
}

void UIText::UpdateMaterial(bool newFont)
{
    Material* material = GetCustomMaterial();
    if (!material)
    {
        material = new Material(context_);
        Technique* tech = new Technique(context_);
        Pass* pass = tech->CreatePass(PASS_ALPHA);
        pass->SetVertexShader("Text");
        pass->SetPixelShader("Text");
        pass->SetDepthWrite(false);

        // Text alway use alpha blend mode
        pass->SetBlendMode(BLEND_ALPHA);

        material->SetTechnique(0, tech);
        material->SetCullMode(CULL_NONE);

        SetCustomMaterial(material);
    }

    material->SetTexture(TU_DIFFUSE, texture_);

    if (newFont)
    {
        Technique* tech = material->GetTechnique(0);
        Pass* pass = tech->GetPass(PASS_ALPHA);
        if (font_ && font_->IsSDFFont())
        {

            switch (textEffect_)
            {
            case TE_NONE:
                pass->SetPixelShaderDefines("SIGNED_DISTANCE_FIELD");
                break;

            case TE_SHADOW:
                pass->SetPixelShaderDefines("SIGNED_DISTANCE_FIELD TEXT_EFFECT_SHADOW");
                break;

            case TE_STROKE:
                pass->SetPixelShaderDefines("SIGNED_DISTANCE_FIELD TEXT_EFFECT_STROKE");
                break;
            }
        }
        else
            pass->SetPixelShaderDefines("");
    }    
}

void UIText::UpdateText()
{
    textLineInfo_.Clear();

    // Convert to Unicode text
    PODVector<unsigned> unicodeText;
    for (unsigned i = 0; i < text_.Length();)
        unicodeText.Push(text_.NextUTF8Char(i));

    numChars_ = unicodeText.Size();

    if (!fontFace_)
        return;

    rowHeight_ = fontFace_->GetRowHeight() * PIXEL_SIZE;

    UITextLineInfo lineInfo;
    for (unsigned i = 0; i < unicodeText.Size(); ++i)
    {
        unsigned c = unicodeText[i];
        if (c != '\n')
        {
            const FontGlyph* glyph = fontFace_->GetGlyph(c);
            if (glyph)
                lineInfo.Add(glyph, i < unicodeText.Size() - 1 ? fontFace_->GetKerning(c, unicodeText[i + 1]) : 0);
        }
        else
        {
            textLineInfo_.Push(lineInfo);
            lineInfo.Clear();
        }
    }

    if (!lineInfo.fontGlyphs_.Empty())
        textLineInfo_.Push(lineInfo);
}

void UIText::ValidateSelection()
{
    if (numChars_)
    {
        if (selectionStart_ >= numChars_)
            selectionStart_ = numChars_ - 1;
        if (selectionStart_ + selectionLength_ > numChars_)
            selectionLength_ = numChars_ - selectionStart_;
    }
    else
    {
        selectionStart_ = 0;
        selectionLength_ = 0;
    }
}


void UIText::UpdateTextLineVertices(const UITextLineInfo& lineInfo, float x, float y, unsigned color)
{
    const PODVector<float>& advances = lineInfo.glyphAdvances_;
    const PODVector<const FontGlyph*>& fontGlyphs = lineInfo.fontGlyphs_;

    float invTexWidth = 1.0f / (float)texture_->GetWidth();
    float invTexHeight = 1.0f / (float)texture_->GetHeight();

    for (unsigned i = 0; i < fontGlyphs.Size(); ++i)
    {
        const FontGlyph& glyph = *fontGlyphs[i];
        /*
        V1---------V2
        |         / |
        |       /   |
        |     /     |
        |   /       |
        | /         |
        V0---------V3
        */
        Vertex2D vertex0;
        Vertex2D vertex1;
        Vertex2D vertex2;
        Vertex2D vertex3;

        float left = x + glyph.offsetX_ * PIXEL_SIZE;
        float right = left + glyph.width_ * PIXEL_SIZE;
        float top = y - glyph.offsetY_ * PIXEL_SIZE;
        float bottom = top -  glyph.height_ * PIXEL_SIZE;

        float uLeft = glyph.x_ * invTexWidth;
        float uRight = (glyph.x_ + glyph.width_) * invTexWidth;
        float vTop = glyph.y_ * invTexHeight;
        float vBottom = (glyph.y_ + glyph.height_) * invTexHeight;

        vertex0.position_ = Vector3(left, bottom);
        vertex1.position_ = Vector3(left, top);
        vertex2.position_ = Vector3(right, top);
        vertex3.position_ = Vector3(right, bottom);

        vertex0.uv_ = Vector2(uLeft, vBottom);
        vertex1.uv_ = Vector2(uLeft, vTop);
        vertex2.uv_ = Vector2(uRight, vTop);
        vertex3.uv_ = Vector2(uRight, vBottom);

        vertex0.color_ = color;
        vertex1.color_ = color;
        vertex2.color_ = color;
        vertex3.color_ = color;

        vertices_.Push(vertex0);
        vertices_.Push(vertex1);
        vertices_.Push(vertex2);
        vertices_.Push(vertex3);

        x += advances[i];
    }
}

}
