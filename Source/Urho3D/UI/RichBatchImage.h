#ifndef __RICH_WIDGET_IMAGE_H__
#define __RICH_WIDGET_IMAGE_H__
#pragma once

#include "../UI/RichBatch.h"
#include "../Graphics/Material.h"

namespace Urho3D {

// A mesh that displays image quads
class RichWidgetImage: public RichWidgetBatch {
  URHO3D_OBJECT(RichWidgetImage, RichWidgetBatch)
public:
  /// Register object factory.
  static void RegisterObject(Context* context);

  RichWidgetImage(Context* context);
  virtual ~RichWidgetImage();

  void SetImageSource(const String& sourceUrl);

  String GetImageSource() const { return source_url_; }

  void AddImage(const Vector3 pos, float width, float height);

  int GetImageWidth() const;
  int GetImageHeight() const;

  float GetImageAspect() const;
private:
	String source_url_;
};

} // namespace engine

#endif
