#ifndef __RICH_WIDGET_BATCH_H__
#define __RICH_WIDGET_BATCH_H__
#pragma once

#include "../UI/RichUtils.h"
#include "../Graphics/Drawable.h"
#include "../UI/UIBatch.h"
#include "../UI/UIElement.h"

namespace Urho3D {

class RichWidget;
class RichWidgetBatch;
typedef Vector<SharedPtr<RichWidgetBatch>> WidgetBatchVector;

// Quad storage
struct Quad {
  Quad(const FloatRect& _vertices,
    float _z,
    const FloatRect& _texcoords,
    const Color& _color)
    : vertices(_vertices)
    , z(_z)
    , texCoords(_texcoords)
    , color(_color) {}

  Quad() : z(0) {}

  FloatRect vertices;
  FloatRect texCoords;
  Color color;
  float z;
};

// An utility function for copying Quad data to UIBatch
void AddQuadToUIBatch(UIBatch* batch, const Quad& q);

// A batch for rendering inside a widget
class RichWidgetBatch: public UIElement {
  URHO3D_OBJECT(RichWidgetBatch, UIElement)
public:
  explicit RichWidgetBatch(Context* context);
  virtual ~RichWidgetBatch();

  // the texture used on the quads
  Texture* texture_;
  // the material used to render
  SharedPtr<Material> material_;
  // the output batch
  UIBatch* batch_;

  // Set parent widget
  void SetParentWidget(RichWidget* parent);
  // Get parent widget
  RichWidget* GetParentWidget() const { return parent_widget_; }
	// does the WidgetBatch need redrawing
  bool IsDirty() const { return is_dirty_; }
	// force the WidgetBatch to redraw
  void SetDirty() { is_dirty_ = true; }
	// add a quad
  void AddQuad(const FloatRect& vertices, float z, const FloatRect& texcoords, const Color& color);
	// remove all quads
  void ClearQuads();
	// is the render item empty (has no quads)
  bool IsEmpty() const;
  // Get UI batches from this widget
  virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);
protected:
  friend class RichWidget;
  StringHash id_;
	// need to draw ?
	bool is_dirty_;
	// list of quads, always caches the drawn quads so we can move them without processing the input
  PODVector<Quad> quads_;
	// the parent widget (if any)
  RichWidget* parent_widget_;
	// use count, e.g. how many times this item has been referenced in the last draw call
	int use_count_;
  // number of batches in the last GetBatches call
  int num_batches_;
};

} // namespace Urho3D


#endif
