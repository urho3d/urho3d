#include "../UI/RichBatch.h"
#include "../UI/RichWidget.h"
#include "../UI/RichUtils.h"

namespace Urho3D {

void AddQuadToUIBatch(UIBatch* batch, const Quad& q) {
  unsigned color = q.color.ToUInt();
  unsigned begin = batch->vertexData_->Size();
  batch->vertexData_->Resize(begin + 6 * UI_VERTEX_SIZE);
  float* dest = &(batch->vertexData_->At(begin));
  batch->vertexEnd_ = batch->vertexData_->Size();

  dest[0] = q.vertices.left;
  dest[1] = q.vertices.top;
  dest[2] = q.z;
  ((unsigned&)dest[3]) = color;
  dest[4] = q.texCoords.left;
  dest[5] = q.texCoords.top;

  dest[6] = q.vertices.right;
  dest[7] = q.vertices.top;
  dest[8] = q.z;
  ((unsigned&)dest[9]) = color;
  dest[10] = q.texCoords.right;
  dest[11] = q.texCoords.top;

  dest[12] = q.vertices.left;
  dest[13] = q.vertices.bottom;
  dest[14] = q.z;
  ((unsigned&)dest[15]) = color;
  dest[16] = q.texCoords.left;
  dest[17] = q.texCoords.bottom;

  dest[18] = q.vertices.right;
  dest[19] = q.vertices.top;
  dest[20] = q.z;
  ((unsigned&)dest[21]) = color;
  dest[22] = q.texCoords.right;
  dest[23] = q.texCoords.top;

  dest[24] = q.vertices.right;
  dest[25] = q.vertices.bottom;
  dest[26] = q.z;
  ((unsigned&)dest[27]) = color;
  dest[28] = q.texCoords.right;
  dest[29] = q.texCoords.bottom;

  dest[30] = q.vertices.left;
  dest[31] = q.vertices.bottom;
  dest[32] = q.z;
  ((unsigned&)dest[33]) = color;
  dest[34] = q.texCoords.left;
  dest[35] = q.texCoords.bottom;
}

namespace {

inline void fix_quad_texels(FloatRect& vertices) {
#if 0
  Real xTexel = Ogre::Root::getSingleton().getRenderSystem()->getHorizontalTexelOffset();
  Real yTexel = Ogre::Root::getSingleton().getRenderSystem()->getVerticalTexelOffset();

	Ogre::Viewport* viewport = Ogre::Root::getSingleton().getRenderSystem()->_getViewport();
	if (!viewport)
		return;

  vertices.left -= xTexel / (Ogre::Real)viewport->getActualWidth();
  vertices.right -= xTexel / (Ogre::Real)viewport->getActualWidth();
  vertices.top -= yTexel / (Ogre::Real)viewport->getActualHeight();
  vertices.bottom -= yTexel / (Ogre::Real)viewport->getActualHeight();
#endif
}

inline void move_quad(Urho3D::Vector3 vector, FloatRect& vertices) {
  vertices.left += vector.x_;
  vertices.right += vector.x_;
  vertices.top += vector.y_;
  vertices.bottom += vector.y_;
}

inline void scale_quad(Urho3D::Vector3 scale, FloatRect& vertices) {
  vertices.left *= scale.x_;
  vertices.right *= scale.x_;
  vertices.top *= scale.y_;
  vertices.bottom *= scale.y_;
}
	

// clips a quad to the specified rect, returns false if the quad is outside the rect
inline bool clip_quad(FloatRect& vertices, FloatRect& texcoords, const FloatRect& clip_region) {
  float leftClip = (float)clip_region.left - vertices.left;
	if (leftClip > 0.0f) {
    if ((float)clip_region.left < vertices.right) {
      texcoords.left += texcoords.width() * leftClip / vertices.width();
      vertices.left += leftClip;
		} else
			return false;
	}

  float rightClip = vertices.right - (float)clip_region.right;
	if (rightClip > 0.0f) {
    if (vertices.left < (float)clip_region.right) {
      texcoords.right -= texcoords.width() * rightClip / vertices.width();
      vertices.right -= rightClip;
		} else
			return false;
	}

  float topClip = (float)clip_region.top - vertices.top;
	if (topClip > 0.0f) {
    if ((float)clip_region.top < vertices.bottom) {
      texcoords.top += texcoords.height() * topClip / vertices.height();
      vertices.top += topClip;
		} else
			return false;
	}

  float bottomClip = vertices.bottom - (float)clip_region.bottom;
	if (bottomClip > 0.0f) {
    if (vertices.top < (float)clip_region.bottom) {
      texcoords.bottom -= texcoords.height() * bottomClip / vertices.height();
      vertices.bottom -= bottomClip;
		} else
			return false;
	}

	return true;
}
	
} // namespace

RichWidgetBatch::RichWidgetBatch(Context* context)
 : is_dirty_(false)
 , use_count_(0)
 , parent_widget_(0)
 , UIElement(context)
 , texture_(0)
 , num_batches_(0) {

}

RichWidgetBatch::~RichWidgetBatch() {
	ClearQuads();
}

void RichWidgetBatch::SetParentWidget(RichWidget* parent) {
  parent_widget_ = parent;
}

void RichWidgetBatch::AddQuad(const FloatRect& vertices, float z, const FloatRect& texcoords, const Urho3D::Color& color) {
	quads_.Push(Quad(vertices, z, texcoords, color));
	SetDirty();
}

void RichWidgetBatch::ClearQuads() {
	quads_.Clear();
	SetDirty();
}

void RichWidgetBatch::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) {
  // draw all the quads to the UIBatch list
  UIBatch batch(this, BLEND_ALPHA, currentScissor, texture_ ? texture_ : 0, &vertexData);

  float scalex = parent_widget_ ? parent_widget_->GetInternalScale().x_ : 1.0f;
  float scaley = parent_widget_ ? parent_widget_->GetInternalScale().y_ : 1.0f;

  const FloatRect& cliprect = parent_widget_ ? parent_widget_->GetActualDrawArea(false) : FloatRect();
  const FloatRect& cliprect_with_padding = parent_widget_ ? parent_widget_->GetActualDrawArea(true) : FloatRect();
  Vector3 scaled_draw_origin = parent_widget_ ? parent_widget_->GetDrawOrigin() * Vector3(parent_widget_->GetInternalScale().x_, parent_widget_->GetInternalScale().y_, 1.0f) : Vector3::ZERO;
  IntRect padding = parent_widget_ ? parent_widget_->GetPadding() : IntRect::ZERO;
  padding.left_ *= scalex;
  padding.right_ *= scalex;
  padding.top_ *= scaley;
  padding.bottom_ *= scaley;
  Vector3 scale_vector(scalex, scaley, 1);

  for (auto& quad : quads_) {
    Quad q = quad;
    scale_quad(scale_vector, q.vertices);
    move_quad(scaled_draw_origin, q.vertices);
    q.vertices.left += padding.left_;
    q.vertices.right += padding.left_;
    q.vertices.top += padding.top_;
    q.vertices.bottom += padding.top_;
    if (!cliprect.empty() && !clip_quad(q.vertices, q.texCoords, cliprect_with_padding))
      continue;

    AddQuadToUIBatch(&batch, q);
  }

  batch.texture_ = texture_;

  int batch_count_before = batches.Size();
  UIBatch::AddOrMerge(batch, batches);

  num_batches_ = batches.Size() - batch_count_before;

  is_dirty_ = false;
}

bool RichWidgetBatch::IsEmpty() const {
	return quads_.Empty();
}

} // namespace engine
