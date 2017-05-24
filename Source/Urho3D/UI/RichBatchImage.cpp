#include "../UI/RichBatchImage.h"
#include "../UI/RichWidget.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/Texture2D.h"
#include "../Core/Context.h"

namespace Urho3D {

extern const char* GEOMETRY_CATEGORY;

/// Register object factory. Drawable must be registered first.
void RichWidgetImage::RegisterObject(Context* context)
{
    context->RegisterFactory<RichWidgetImage>(GEOMETRY_CATEGORY);
}

RichWidgetImage::RichWidgetImage(Context* context) 
 : RichWidgetBatch(context)
{
     ResourceCache* cache = GetSubsystem<ResourceCache>();
     Material* material = cache->GetResource<Material>("Materials/WidgetTexture.xml");
     material_ = material;
}


RichWidgetImage::~RichWidgetImage()
{
}


void RichWidgetImage::SetImageSource(const String& sourceUrl)
{
    if (!texture_ || sourceUrl != texture_->GetName())
    {
        if (context_->GetSubsystem<ResourceCache>()->Exists(sourceUrl))
            texture_ = context_->GetSubsystem<ResourceCache>()->GetResource<Texture2D>(sourceUrl);
        if (texture_ && material_)
        {
            material_->SetTexture(TU_DIFFUSE, texture_);
            if (parent_widget_)
                parent_widget_->SetFlags(WidgetFlags_All);
        }
    }
}

void RichWidgetImage::AddImage(const Vector3 pos, float width, float height)
{
    if (parent_widget_ && parent_widget_->GetShadowEnabled())
    {
        AddQuad(
          Rect(pos.x_ + parent_widget_->GetShadowOffset().x_, 
              pos.y_ + parent_widget_->GetShadowOffset().y_, 
              pos.x_ + parent_widget_->GetShadowOffset().x_ + width,
              pos.y_ + parent_widget_->GetShadowOffset().y_ + height), 
            pos.z_ + 0.01,
            Rect(0, 0, 0, 0), // NOTE: UV is empty
            parent_widget_->GetShadowColor());
    }
    AddQuad(Rect(pos.x_, pos.y_, pos.x_ + width, pos.y_ + height), pos.z_, Rect(0.0f, 0.0f, 1.0f, 1.0f), Color::WHITE);
}

int RichWidgetImage::GetImageWidth() const
{
    if (texture_)
        return texture_->GetWidth();
    return 0;
}

int RichWidgetImage::GetImageHeight() const
{
    if (texture_)
        return texture_->GetHeight();
    return 0;
}

float RichWidgetImage::GetImageAspect() const
{
    if (texture_ && texture_->GetHeight())
        return (float)texture_->GetWidth() / texture_->GetHeight();
    return 0;
}

} // namespace Urho3D

