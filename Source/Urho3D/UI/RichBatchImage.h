#pragma once

#include "../UI/RichBatch.h"
#include "../Graphics/Material.h"

namespace Urho3D
{

/// A mesh that displays image quads.
class RichWidgetImage: public RichWidgetBatch
{
    URHO3D_OBJECT(RichWidgetImage, RichWidgetBatch)
public:
    /// Register object factory.
    static void RegisterObject(Context* context);

    RichWidgetImage(Context* context);
    virtual ~RichWidgetImage();

    /// Set image source url.
    void SetImageSource(const String& sourceUrl);
    /// Get image source url.
    String GetImageSource() const { return source_url_; }
    /// Add an image quad.
    void AddImage(const Vector3 pos, float width, float height);
    /// Get image width.
    int GetImageWidth() const;
    /// Get image height.
    int GetImageHeight() const;
    /// Get aspect ratio (width/height).
    float GetImageAspect() const;
private:
    /// Stored url of the image.
    String source_url_;
};

} // namespace Urho3D
