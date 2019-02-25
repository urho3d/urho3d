#pragma once

#include "../Graphics/Drawable.h"
#include "../UI/UIBatch.h"
#include "../UI/UIElement.h"

namespace Urho3D
{

class RichWidget;
class RichWidgetBatch;

/// Quad storage.
struct Quad
{
    Quad(const Rect& vertices,
      float z,
      const Rect& texcoords,
      const Color& color)
      : vertices_(vertices)
      , z_(z)
      , tex_coords_(texcoords)
      , color_(color) {}

    Quad() : z_(0) {}

    Rect vertices_;
    Rect tex_coords_;
    Color color_;
    float z_;
};

/// An utility function for copying Quad data to UIBatch.
void AddQuadToUIBatch(UIBatch* batch, const Quad& q);

/// A batch for rendering inside a widget.
class RichWidgetBatch: public Object
{
    URHO3D_OBJECT(RichWidgetBatch, Object)
public:
    explicit RichWidgetBatch(Context* context);
    virtual ~RichWidgetBatch();

    /// The texture used on the quads.
    Texture* texture_;
    /// The material used to render.
    SharedPtr<Material> material_;
    /// The output batch.
    UIBatch* batch_;

    /// Set parent widget.
    void SetParentWidget(RichWidget* parent);
    /// Get parent widget.
    RichWidget* GetParentWidget() const { return parent_widget_; }
    /// Does the WidgetBatch need redrawing ?
    bool IsDirty() const { return is_dirty_; }
    /// Force the WidgetBatch to redraw.
    void SetDirty() { is_dirty_ = true; }
    /// Add a quad.
    void AddQuad(const Rect& vertices, float z, const Rect& texcoords, const Color& color);
    /// Remove all quads.
    void ClearQuads();
    /// Is the render item empty (has no quads)?
    bool IsEmpty() const;
    /// Get UI batches from this widget.
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);
protected:
    friend class RichWidget;
    /// Used in RichWidget for caching.
    StringHash id_;
    // Flags if the batch has changed since last draw/
    bool is_dirty_;
    /// List of quads.
    PODVector<Quad> quads_;
    /// The parent widget (if any).
    RichWidget* parent_widget_;
    /// Use count in the last draw call.
    int use_count_;
    /// number of batches in the last GetBatches call.
    int num_batches_;
};

} // namespace Urho3D
