//
// Copyright (c) 2008-2015 the Urho3D project.
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
#include "../Graphics/Camera.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Material.h"
#include "../Graphics/Technique.h"
#include "../Graphics/VertexBuffer.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"
#include "../Scene/Node.h"
#include "../UI/Font.h"
#include "../UI/Text.h"
#include "../UI/Text3D.h"

namespace Urho3D
{

extern const char* horizontalAlignments[];
extern const char* verticalAlignments[];
extern const char* textEffects[];
extern const char* faceCameraModeNames[];
extern const char* GEOMETRY_CATEGORY;

static const float TEXT_SCALING = 1.0f / 128.0f;
static const float DEFAULT_EFFECT_DEPTH_BIAS = 0.1f;

Text3D::Text3D(Context* context) :
    Drawable(context, DRAWABLE_GEOMETRY),
    text_(context),
    vertexBuffer_(new VertexBuffer(context_)),
    customWorldTransform_(Matrix3x4::IDENTITY),
    faceCameraMode_(FC_NONE),
    textDirty_(true),
    geometryDirty_(true),
    usingSDFShader_(false),
    fontDataLost_(false)
{
    text_.SetUsedInText3D(true);
    text_.SetEffectDepthBias(DEFAULT_EFFECT_DEPTH_BIAS);
}

Text3D::~Text3D()
{
}

void Text3D::RegisterObject(Context* context)
{
    context->RegisterFactory<Text3D>(GEOMETRY_CATEGORY);

    URHO3D_ACCESSOR_ATTRIBUTE("Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Font", GetFontAttr, SetFontAttr, ResourceRef, ResourceRef(Font::GetTypeStatic()), AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()),
        AM_DEFAULT);
    URHO3D_ATTRIBUTE("Font Size", int, text_.fontSize_, DEFAULT_FONT_SIZE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Text", String, text_.text_, String::EMPTY, AM_DEFAULT);
    URHO3D_ENUM_ATTRIBUTE("Text Alignment", text_.textAlignment_, horizontalAlignments, HA_LEFT, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Row Spacing", float, text_.rowSpacing_, 1.0f, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Word Wrap", bool, text_.wordWrap_, false, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    URHO3D_ENUM_ATTRIBUTE("Face Camera Mode", faceCameraMode_, faceCameraModeNames, FC_NONE, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Width", GetWidth, SetWidth, int, 0, AM_DEFAULT);
    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Horiz Alignment", GetHorizontalAlignment, SetHorizontalAlignment, HorizontalAlignment,
        horizontalAlignments, HA_LEFT, AM_DEFAULT);
    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Vert Alignment", GetVerticalAlignment, SetVerticalAlignment, VerticalAlignment, verticalAlignments,
        VA_TOP, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Color", GetColorAttr, SetColor, Color, Color::WHITE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Top Left Color", Color, text_.color_[0], Color::WHITE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Top Right Color", Color, text_.color_[1], Color::WHITE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Bottom Left Color", Color, text_.color_[2], Color::WHITE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Bottom Right Color", Color, text_.color_[3], Color::WHITE, AM_DEFAULT);
    URHO3D_ENUM_ATTRIBUTE("Text Effect", text_.textEffect_, textEffects, TE_NONE, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Effect Color", GetEffectColor, SetEffectColor, Color, Color::BLACK, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Effect Depth Bias", float, text_.effectDepthBias_, DEFAULT_EFFECT_DEPTH_BIAS, AM_DEFAULT);
    URHO3D_COPY_BASE_ATTRIBUTES(Drawable);
}

void Text3D::ApplyAttributes()
{
    text_.ApplyAttributes();
    MarkTextDirty();
    UpdateTextBatches();
    UpdateTextMaterials();
}

void Text3D::UpdateBatches(const FrameInfo& frame)
{
    distance_ = frame.camera_->GetDistance(GetWorldBoundingBox().Center());

    if (faceCameraMode_ != FC_NONE)
    {
        Vector3 worldPosition = node_->GetWorldPosition();
        customWorldTransform_ = Matrix3x4(worldPosition, frame.camera_->GetFaceCameraRotation(
            worldPosition, node_->GetWorldRotation(), faceCameraMode_), node_->GetWorldScale());
        worldBoundingBoxDirty_ = true;
    }

    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        batches_[i].distance_ = distance_;
        batches_[i].worldTransform_ = faceCameraMode_ != FC_NONE ? &customWorldTransform_ : &node_->GetWorldTransform();
    }

    for (unsigned i = 0; i < uiBatches_.Size(); ++i)
    {
        if (uiBatches_[i].texture_ && uiBatches_[i].texture_->IsDataLost())
        {
            fontDataLost_ = true;
            break;
        }
    }
}

void Text3D::UpdateGeometry(const FrameInfo& frame)
{
    if (fontDataLost_)
    {
        // Re-evaluation of the text triggers the font face to reload itself
        UpdateTextBatches();
        UpdateTextMaterials();
        fontDataLost_ = false;
    }

    if (geometryDirty_)
    {
        for (unsigned i = 0; i < batches_.Size(); ++i)
        {
            Geometry* geometry = geometries_[i];
            geometry->SetDrawRange(TRIANGLE_LIST, 0, 0, uiBatches_[i].vertexStart_,
                (uiBatches_[i].vertexEnd_ - uiBatches_[i].vertexStart_) / UI_VERTEX_SIZE);
        }
    }

    if ((geometryDirty_ || vertexBuffer_->IsDataLost()) && uiVertexData_.Size())
    {
        unsigned vertexCount = uiVertexData_.Size() / UI_VERTEX_SIZE;
        if (vertexBuffer_->GetVertexCount() != vertexCount)
            vertexBuffer_->SetSize(vertexCount, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1);
        vertexBuffer_->SetData(&uiVertexData_[0]);
    }

    geometryDirty_ = false;
}

UpdateGeometryType Text3D::GetUpdateGeometryType()
{
    if (geometryDirty_ || fontDataLost_ || vertexBuffer_->IsDataLost())
        return UPDATE_MAIN_THREAD;
    else
        return UPDATE_NONE;
}

void Text3D::SetMaterial(Material* material)
{
    material_ = material;

    UpdateTextMaterials(true);
}

bool Text3D::SetFont(const String& fontName, int size)
{
    bool success = text_.SetFont(fontName, size);

    // Changing font requires materials to be re-evaluated. Material evaluation can not be done in worker threads,
    // so UI batches must be brought up-to-date immediately
    MarkTextDirty();
    UpdateTextBatches();
    UpdateTextMaterials();

    return success;
}

bool Text3D::SetFont(Font* font, int size)
{
    bool success = text_.SetFont(font, size);

    MarkTextDirty();
    UpdateTextBatches();
    UpdateTextMaterials();

    return success;
}

void Text3D::SetText(const String& text)
{
    text_.SetText(text);

    // Changing text requires materials to be re-evaluated, in case the font is multi-page
    MarkTextDirty();
    UpdateTextBatches();
    UpdateTextMaterials();
}

void Text3D::SetAlignment(HorizontalAlignment hAlign, VerticalAlignment vAlign)
{
    text_.SetAlignment(hAlign, vAlign);

    MarkTextDirty();
}

void Text3D::SetHorizontalAlignment(HorizontalAlignment align)
{
    text_.SetHorizontalAlignment(align);

    MarkTextDirty();
}

void Text3D::SetVerticalAlignment(VerticalAlignment align)
{
    text_.SetVerticalAlignment(align);

    MarkTextDirty();
}

void Text3D::SetTextAlignment(HorizontalAlignment align)
{
    text_.SetTextAlignment(align);

    MarkTextDirty();
}

void Text3D::SetRowSpacing(float spacing)
{
    text_.SetRowSpacing(spacing);

    MarkTextDirty();
}

void Text3D::SetWordwrap(bool enable)
{
    text_.SetWordwrap(enable);

    MarkTextDirty();
}

void Text3D::SetTextEffect(TextEffect textEffect)
{
    text_.SetTextEffect(textEffect);

    MarkTextDirty();
    UpdateTextMaterials(true);
}

void Text3D::SetEffectColor(const Color& effectColor)
{
    text_.SetEffectColor(effectColor);

    MarkTextDirty();
    UpdateTextMaterials();
}

void Text3D::SetEffectDepthBias(float bias)
{
    text_.SetEffectDepthBias(bias);

    MarkTextDirty();
}

void Text3D::SetWidth(int width)
{
    text_.SetMinWidth(width);
    text_.SetWidth(width);

    MarkTextDirty();
}

void Text3D::SetColor(const Color& color)
{
    text_.SetColor(color);

    MarkTextDirty();
}

void Text3D::SetColor(Corner corner, const Color& color)
{
    text_.SetColor(corner, color);

    MarkTextDirty();
}

void Text3D::SetOpacity(float opacity)
{
    text_.SetOpacity(opacity);

    MarkTextDirty();
}

void Text3D::SetFaceCameraMode(FaceCameraMode mode)
{
    if (mode != faceCameraMode_)
    {
        faceCameraMode_ = mode;

        // Bounding box must be recalculated
        OnMarkedDirty(node_);
    }
}

Material* Text3D::GetMaterial() const
{
    return material_;
}

Font* Text3D::GetFont() const
{
    return text_.GetFont();
}

int Text3D::GetFontSize() const
{
    return text_.GetFontSize();
}

const String& Text3D::GetText() const
{
    return text_.GetText();
}

HorizontalAlignment Text3D::GetHorizontalAlignment() const
{
    return text_.GetHorizontalAlignment();
}

VerticalAlignment Text3D::GetVerticalAlignment() const
{
    return text_.GetVerticalAlignment();
}

HorizontalAlignment Text3D::GetTextAlignment() const
{
    return text_.GetTextAlignment();
}

float Text3D::GetRowSpacing() const
{
    return text_.GetRowSpacing();
}

bool Text3D::GetWordwrap() const
{
    return text_.GetWordwrap();
}

TextEffect Text3D::GetTextEffect() const
{
    return text_.GetTextEffect();
}

const Color& Text3D::GetEffectColor() const
{
    return text_.GetEffectColor();
}

float Text3D::GetEffectDepthBias() const
{
    return text_.GetEffectDepthBias();
}

int Text3D::GetWidth() const
{
    return text_.GetWidth();
}

int Text3D::GetRowHeight() const
{
    return text_.GetRowHeight();
}

unsigned Text3D::GetNumRows() const
{
    return text_.GetNumRows();
}

unsigned Text3D::GetNumChars() const
{
    return text_.GetNumChars();
}

int Text3D::GetRowWidth(unsigned index) const
{
    return text_.GetRowWidth(index);
}

IntVector2 Text3D::GetCharPosition(unsigned index)
{
    return text_.GetCharPosition(index);
}

IntVector2 Text3D::GetCharSize(unsigned index)
{
    return text_.GetCharSize(index);
}

const Color& Text3D::GetColor(Corner corner) const
{
    return text_.GetColor(corner);
}

float Text3D::GetOpacity() const
{
    return text_.GetOpacity();
}

void Text3D::OnNodeSet(Node* node)
{
    Drawable::OnNodeSet(node);

    if (node)
        customWorldTransform_ = node->GetWorldTransform();
}

void Text3D::OnWorldBoundingBoxUpdate()
{
    if (textDirty_)
        UpdateTextBatches();

    // In face camera mode, use the last camera rotation to build the world bounding box
    worldBoundingBox_ = boundingBox_.Transformed(faceCameraMode_ != FC_NONE ? Matrix3x4(node_->GetWorldPosition(),
        customWorldTransform_.Rotation(), node_->GetWorldScale()) : node_->GetWorldTransform());
}

void Text3D::MarkTextDirty()
{
    textDirty_ = true;

    OnMarkedDirty(node_);
    MarkNetworkUpdate();
}

void Text3D::SetMaterialAttr(const ResourceRef& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetMaterial(cache->GetResource<Material>(value.name_));
}

void Text3D::SetFontAttr(const ResourceRef& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    text_.font_ = cache->GetResource<Font>(value.name_);
}

ResourceRef Text3D::GetMaterialAttr() const
{
    return GetResourceRef(material_, Material::GetTypeStatic());
}

ResourceRef Text3D::GetFontAttr() const
{
    return GetResourceRef(text_.font_, Font::GetTypeStatic());
}

void Text3D::UpdateTextBatches()
{
    uiBatches_.Clear();
    uiVertexData_.Clear();

    text_.GetBatches(uiBatches_, uiVertexData_, IntRect::ZERO);

    Vector3 offset(Vector3::ZERO);

    switch (text_.GetHorizontalAlignment())
    {
    case HA_LEFT:
        break;

    case HA_CENTER:
        offset.x_ -= (float)text_.GetWidth() * 0.5f;
        break;

    case HA_RIGHT:
        offset.x_ -= (float)text_.GetWidth();
        break;
    }

    switch (text_.GetVerticalAlignment())
    {
    case VA_TOP:
        break;

    case VA_CENTER:
        offset.y_ -= (float)text_.GetHeight() * 0.5f;
        break;

    case VA_BOTTOM:
        offset.y_ -= (float)text_.GetHeight();
        break;
    }

    boundingBox_.Clear();

    for (unsigned i = 0; i < uiVertexData_.Size(); i += UI_VERTEX_SIZE)
    {
        Vector3& position = *(reinterpret_cast<Vector3*>(&uiVertexData_[i]));
        position += offset;
        position *= TEXT_SCALING;
        position.y_ = -position.y_;
        boundingBox_.Merge(position);
    }

    textDirty_ = false;
    geometryDirty_ = true;
}

void Text3D::UpdateTextMaterials(bool forceUpdate)
{
    Font* font = GetFont();
    bool isSDFFont = font ? font->IsSDFFont() : false;

    batches_.Resize(uiBatches_.Size());
    geometries_.Resize(uiBatches_.Size());

    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        if (!geometries_[i])
        {
            Geometry* geometry = new Geometry(context_);
            geometry->SetVertexBuffer(0, vertexBuffer_, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1);
            batches_[i].geometry_ = geometries_[i] = geometry;
        }

        if (!batches_[i].material_ || forceUpdate || isSDFFont != usingSDFShader_)
        {
            // If material not defined, create a reasonable default from scratch
            if (!material_)
            {
                Material* material = new Material(context_);
                Technique* tech = new Technique(context_);
                Pass* pass = tech->CreatePass("alpha");
                pass->SetVertexShader("Text");
                pass->SetPixelShader("Text");

                if (isSDFFont)
                {
                    switch (GetTextEffect())
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

                pass->SetBlendMode(BLEND_ALPHA);
                pass->SetDepthWrite(false);
                material->SetTechnique(0, tech);
                material->SetCullMode(CULL_NONE);
                batches_[i].material_ = material;
            }
            else
                batches_[i].material_ = material_->Clone();

            // Note: custom material is assumed to use the right kind of shader; it is not modified to define SIGNED_DISTANCE_FIELD
            usingSDFShader_ = isSDFFont;
        }

        Material* material = batches_[i].material_;
        Texture* texture = uiBatches_[i].texture_;
        material->SetTexture(TU_DIFFUSE, texture);

        if (isSDFFont)
        {
            switch (GetTextEffect())
            {
            case TE_SHADOW:
                if (texture)
                {
                    Vector2 shadowOffset(0.5f / texture->GetWidth(), 0.5f / texture->GetHeight());
                    material->SetShaderParameter("ShadowOffset", shadowOffset);
                }
                material->SetShaderParameter("ShadowColor", GetEffectColor());
                break;

            case TE_STROKE:
                material->SetShaderParameter("StrokeColor", GetEffectColor());
                break;

            default:
                break;
            }
        }
    }
}

}
