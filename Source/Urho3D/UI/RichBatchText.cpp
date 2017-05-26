#include "../UI/RichBatchText.h"
#include "../UI/RichWidget.h"
#include "../Graphics/Technique.h"
#include "../UI/FontFace.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Texture2D.h"

namespace Urho3D
{

/// Register object factory. Drawable must be registered first.
void RichWidgetText::RegisterObject(Context* context)
{
    context->RegisterFactory<RichWidgetText>();
}

RichWidgetText::RichWidgetText(Context* context)
 : RichWidgetBatch(context)
 , font_(0)
 , font_face_(0)
 , pointsize_(0)
 , bitmap_font_rescale_(Vector2::ONE)
{
    Material* material = new Material(context_);
    Technique* tech = new Technique(context_);
    Pass* pass = tech->CreatePass("alpha");
    pass->SetVertexShader("Text");
    pass->SetPixelShader("Text");
    pass->SetBlendMode(BLEND_ALPHA);
    pass->SetDepthWrite(false);
    material->SetTechnique(0, tech);
    material->SetCullMode(CULL_NONE);
    material_ = material;
}

RichWidgetText::~RichWidgetText()
{

}

void RichWidgetText::SetFont(const String& fontname, int pointsize)
{
    bool changed = pointsize_ != pointsize || (font_face_ && font_->GetName() != fontname);
    pointsize_ = pointsize;
    if (!changed)
        return;

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    font_ = cache->GetResource<Font>(fontname);
    if (!font_)
        return;
    font_face_ = font_->GetFace(pointsize);
    if (font_face_ && !texture_)
        texture_ = font_face_->GetTextures()[0];

    if (font_->IsSDFFont())
        bitmap_font_rescale_ = Vector2((float)pointsize_ / font_face_->GetPointSize(), (float)pointsize_ / font_face_->GetPointSize());

    if (font_->IsSDFFont())
    {
        // Note: custom defined material is assumed to have right shader defines; they aren't modified here
        if (material_)
        {
          Technique* tech = material_->GetTechnique(0);
          Pass* pass = tech ? tech->GetPass("alpha") : (Pass*)0;
          if (pass)
            pass->SetPixelShaderDefines("SIGNED_DISTANCE_FIELD");
        }
    } 
    else 
    {
        Technique* tech = material_->GetTechnique(0);
        Pass* pass = tech ? tech->GetPass("alpha") : (Pass*)0;
        if (pass)
        {
            if (texture_ && texture_->GetFormat() == Graphics::GetAlphaFormat())
              pass->SetPixelShaderDefines("ALPHAMAP");
            else
              pass->SetPixelShaderDefines("");
        }
    }
}

void RichWidgetText::DrawQuad(const Rect& vertices, float z, const Rect& texCoords, const Color& color)
{
    AddQuad(vertices, z, texCoords, color);
}

void RichWidgetText::DrawGlyph(const Rect& texCoords, float x, float y, float z, float width, float height, const Color& color)
{
    Rect vertices;
    vertices.min_.x_ = x;
    vertices.min_.y_ = y;
    vertices.max_.x_ = x + width;
    vertices.max_.y_ = y + height;
    DrawQuad(vertices, z, texCoords, color);
}

void RichWidgetText::DrawGlyphScaled(const Rect& texCoords, float x, float y, float z, float width, float height, const Vector2& scale, const Color& color)
{
    Rect vertices;
    vertices.min_.x_ = x * scale.x_;
    vertices.min_.y_ = y * scale.y_;
    vertices.max_.x_ = x + (width * scale.x_);
    vertices.max_.y_ = y + (height * scale.y_);
    DrawQuad(vertices, z, texCoords, color);
}

void RichWidgetText::AddText(const String& text, const Vector3& pos, const Color& color)
{
    if (!font_ || !font_face_)
        return;

    Vector3 p = pos;

    Texture2D* texture = font_face_->GetTextures()[0];
    Vector2 inverse_size(1.0f / texture->GetWidth(), 1.0f / texture->GetHeight());

    // shadow pass behind the actual text
    // TODO: all shadow passes should be made equal z-order number which is 
    // below all render items in this widget
    if (parent_widget_ && parent_widget_->GetShadowEnabled()) {
        for (auto it = text.Begin(); it != text.End(); ++ it) {
            const FontGlyph* glyph = font_face_->GetGlyph(*it);
            if (glyph == 0)
                continue;

            Rect uv;
            uv.min_.x_ = glyph->x_ * inverse_size.x_;
            uv.max_.x_ = (glyph->x_ + glyph->width_) * inverse_size.x_;
            uv.min_.y_ = glyph->y_ * inverse_size.y_;
            uv.max_.y_ = (glyph->y_ + glyph->height_) * inverse_size.y_;

            DrawGlyph(
              uv, // UV rect
              p.x_ + (bitmap_font_rescale_.x_ * glyph->offsetX_) + parent_widget_->GetShadowOffset().x_,
              p.y_ + (bitmap_font_rescale_.y_ * glyph->offsetY_) + parent_widget_->GetShadowOffset().y_,
              p.z_ + parent_widget_->GetShadowOffset().z_ + 0.01f,
              bitmap_font_rescale_.x_ * glyph->width_,
              bitmap_font_rescale_.y_ * glyph->height_,
              parent_widget_->GetShadowColor());
            p.x_ += glyph->advanceX_ * bitmap_font_rescale_.x_;
        }
    }

    p = pos;

    for (auto it = text.Begin(); it != text.End(); ++it)
    {
        const FontGlyph* glyph = font_face_->GetGlyph(*it);
        if (glyph == 0)
            continue;

        Rect uv;
        uv.min_.x_ = glyph->x_ * inverse_size.x_;
        uv.max_.x_ = (glyph->x_ + glyph->width_) * inverse_size.x_;
        uv.min_.y_ = glyph->y_ * inverse_size.y_;
        uv.max_.y_ = (glyph->y_ + glyph->height_) * inverse_size.y_;

        DrawGlyph(
          uv, // UV rect
          p.x_ + (bitmap_font_rescale_.x_ * glyph->offsetX_),
          p.y_ + (bitmap_font_rescale_.y_ * glyph->offsetY_),
          p.z_,
          bitmap_font_rescale_.x_ * glyph->width_,
          bitmap_font_rescale_.y_ * glyph->height_,
          color);
        p.x_ += glyph->advanceX_ * bitmap_font_rescale_.x_;
    }
}

Vector2 RichWidgetText::CalculateTextExtents(const String& text)
{
    Vector2 res;
    if (!font_face_)
        return res;

    for (auto it = text.Begin(); it != text.End(); ++ it)
    {
        const FontGlyph* glyph = font_face_->GetGlyph(*it);
        if (!glyph)
            continue;
        res.x_ += (float)glyph->advanceX_ * bitmap_font_rescale_.x_;
        res.y_ = Max(res.y_, glyph->height_ * bitmap_font_rescale_.y_);
    }
    return res;
}

float RichWidgetText::GetRowHeight() const
{
    if (font_face_)
        return bitmap_font_rescale_.y_ * font_face_->GetRowHeight();
    return 0;
}

} // namespace Urho3D
