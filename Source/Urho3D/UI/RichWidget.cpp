#include "../UI/RichWidget.h"
#include "../UI/RichBatchText.h"
#include "../UI/RichBatchImage.h"
#include "../Core/Context.h"
#include "../Scene/Node.h"

namespace Urho3D {

extern const char* GEOMETRY_CATEGORY;

/// Register object factory. Drawable must be registered first.
void RichWidget::RegisterObject(Context* context)
{
    context->RegisterFactory<RichWidget>(GEOMETRY_CATEGORY);
    RichWidgetImage::RegisterObject(context);
    RichWidgetText::RegisterObject(context);
}

RichWidget::RichWidget(Context* context)
 : Drawable(context, DRAWABLE_GEOMETRY)
 , vertex_buffer_(new VertexBuffer(context_))
 , clip_region_(0, 0, 0, 0)
 , internal_scale_(1.0f, 1.0f)
 , draw_origin_(0.0f, 0.0f)
 , padding_(0, 0, 0, 0)
 , flags_(WidgetFlags_GeometryDirty)
 , visible_(true)
 , shadow_enabled_(false)
 , shadow_color_(0.0, 0.0, 0.0, 0.0f)
 , zbias_(100)
 , align_h_(HA_LEFT)
 , align_v_(VA_TOP)
 , clip_to_content_(true)
{
 
}

RichWidget::~RichWidget()
{
    RemoveWidgetBatchs();
}

void RichWidget::SetClipRegion(const IntRect& rect)
{
    bool modified = clip_region_ != rect;
    clip_region_ = rect;
    if (modified)
        SetFlags(WidgetFlags_All);
}


void RichWidget::SetClipToContent(bool value)
{
    clip_to_content_ = value;
    SetFlags(WidgetFlags_All);
}

void RichWidget::SetInternalScale(const Vector2& scale)
{
    bool modified = internal_scale_ != scale;
    internal_scale_ = scale;
    if (modified)
        SetFlags(WidgetFlags_GeometryDirty);
}


void RichWidget::SetPadding(const IntRect& padding)
{
    bool modified = padding_ != padding;
    padding_ = padding;
    if (modified)
        SetFlags(WidgetFlags_All);
}

void RichWidget::SetDrawOrigin(const Vector3& point)
{
    bool modified = draw_origin_ != point;
    draw_origin_ = point;
    if (modified)
        SetFlags(WidgetFlags_GeometryDirty);
}

void RichWidget::Clear()
{
    for (auto& item : items_)
    {
        item->ClearQuads();
        item->use_count_ = 0;
    }
}

RichWidgetBatch* RichWidget::CacheWidgetBatchT(StringHash type, StringHash id) {
    // if a WidgetBatch with such name and type exists, return it
    for (auto& item : items_)
    {
        if (item->id_ == id && type == item->GetType()) {
            item->use_count_ ++;
            return item;
        }
    }

    // Create a new batch of the specified type
    SharedPtr<RichWidgetBatch> new_batch;
    new_batch = DynamicCast<RichWidgetBatch>(context_->CreateObject(type));
  
    if (new_batch)
    {
        new_batch->SetParentWidget(this);
        new_batch->use_count_++;
        items_.Push(new_batch);
        new_batch->id_ = id;
    }
    return new_batch;
}

void RichWidget::RemoveWidgetBatchs()
{
    items_.Clear();
}

void RichWidget::RemoveUnusedWidgetBatches()
{
    for (auto it = items_.Begin(); it != items_.End();)
    {
        if ((*it)->use_count_ == 0 && (*it)->IsEmpty())
        {
            it->Reset();
            it = items_.Erase(it);
        }
        else
            it++;
    }
}

Rect RichWidget::GetActualDrawArea(bool withPadding) const
{
    Rect cliprect;
    if (clip_to_content_ && content_size_ != Vector2::ZERO)
    {
        cliprect.min_ = Vector2::ZERO;
        if (!withPadding)
        {
            cliprect.max_ = content_size_ * internal_scale_;
        }
        else
        {
            cliprect.min_.x_ = internal_scale_.x_ * (float)(padding_.left_);
            cliprect.min_.y_ = internal_scale_.y_ * (float)(padding_.top_);
            cliprect.max_.x_ = internal_scale_.x_ * (float)(content_size_.x_ - padding_.right_);
            cliprect.max_.y_ = internal_scale_.y_ * (float)(content_size_.y_ - padding_.bottom_);
        }
        return cliprect;
    }

    if (!withPadding)
    {
        cliprect.min_.x_ = clip_region_.left_;
        cliprect.min_.y_ = clip_region_.top_;
        cliprect.max_.x_ = (float)clip_region_.right_ * internal_scale_.x_;
        cliprect.max_.y_ = (float)clip_region_.bottom_ * internal_scale_.y_;
    }
    else
    {
        cliprect.min_.x_ = internal_scale_.x_ * (float)(clip_region_.left_ + padding_.left_);
        cliprect.min_.y_ = internal_scale_.y_ * (float)(clip_region_.top_ + padding_.top_);
        cliprect.max_.x_ = internal_scale_.x_ * (float)(clip_region_.right_ - padding_.right_);
        cliprect.max_.y_ = internal_scale_.y_ * (float)(clip_region_.bottom_ - padding_.bottom_);
    }
    return cliprect;
}

void RichWidget::SetVisible(bool visible)
{
    visible_ = visible;
}

void RichWidget::SetZBias(int zbias)
{
    zbias_ = zbias;

    for (auto it = items_.Begin(); it != items_.End(); ++ it)
    {
        RichWidgetBatch* ri = (*it);
        // TODO: implement
    }
}

void RichWidget::SetShadowOffset(const Vector4& shadow_offset)
{
    bool modified = shadow_offset_ != shadow_offset;
    shadow_offset_ = shadow_offset;
    if (modified) 
        SetFlags(WidgetFlags_GeometryDirty);
}

void RichWidget::SetShadowColor(const Color& color)
{
    bool modified = shadow_color_ != color;
    shadow_color_ = color;
    if (modified)
        SetFlags(WidgetFlags_GeometryDirty);
}

void RichWidget::SetShadowEnabled(bool shadow_enabled)
{
    bool modified = shadow_enabled_ != shadow_enabled;
    shadow_enabled_ = shadow_enabled;
    if (modified)
        SetFlags(WidgetFlags_GeometryDirty);
}

void RichWidget::SetHorizontalAlignment(HorizontalAlignment align)
{
  align_h_ = align; 
  SetFlags(WidgetFlags_GeometryDirty);
}

void RichWidget::SetVerticalAlignment(VerticalAlignment align)
{ 
  align_v_ = align;
  SetFlags(WidgetFlags_GeometryDirty);
}

void RichWidget::SetFlags(unsigned flags) 
{ 
    flags_ |= flags;
    if (flags_ & WidgetFlags_GeometryDirty)
    {
        OnMarkedDirty(node_);
        MarkNetworkUpdate();
    }
}

#if 0
/// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
void Widget::UpdateBatches(const FrameInfo& frame) {
  if (IsFlagged(WidgetFlags_Dirty)) {
    Draw();
    //ClearFlags(WidgetFlags_Dirty);
  }

  distance_ = frame.camera_->GetDistance(GetWorldBoundingBox().Center());

  //if (faceCameraMode_ != FC_NONE || fixedScreenSize_)
  //  CalculateFixedScreenSize(frame);

  for (unsigned i = 0; i < batches_.Size(); ++i) {
    batches_[i].distance_ = distance_;
    batches_[i].worldTransform_ = &node_->GetWorldTransform();
  }

  for (unsigned i = 0; i < ui_batches_.Size(); ++i) {
    if (ui_batches_[i].texture_ && ui_batches_[i].texture_->IsDataLost()) {
      //fontDataLost_ = true;
      break;
    }
  }
}
#endif

void RichWidget::Draw()
{
    if (visible_)
    {
        bool dirty = IsFlagged(WidgetFlags_GeometryDirty);

        for (auto& item : items_)
        {
            if (dirty)
                item->SetDirty();
        }

        if (dirty)
        {
            UpdateTextBatches();
            UpdateTextMaterials();
        }
    }
    //ClearFlags(WidgetFlags_Dirty);
    RemoveUnusedWidgetBatches();
}

void RichWidget::UpdateBatches(const FrameInfo& frame)
{
#if 0
    distance_ = frame.camera_->GetDistance(GetWorldBoundingBox().Center());

    //if (faceCameraMode_ != FC_NONE || fixedScreenSize_)
    //  CalculateFixedScreenSize(frame);

    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        batches_[i].distance_ = distance_;
        batches_[i].worldTransform_ = /*faceCameraMode_ != FC_NONE ? &customWorldTransform_ : */&node_->GetWorldTransform();
    }
#endif
}

void RichWidget::UpdateTextBatches()
{
    ui_batches_.Clear();
    ui_vertex_data_.Clear();
    batch_index_to_item_index_.Clear();

    int batch_index = 0;
    for (unsigned i = 0; i < items_.Size(); ++i)
    {
        // Update the UIBatch list with every RichBatch data
        items_[i]->GetBatches(ui_batches_, ui_vertex_data_, IntRect::ZERO);

        // Map item index to UI batch index
        for (int c = 0; c < items_[i]->num_batches_; ++c)
          batch_index_to_item_index_.Push(i);
    }

    Vector3 offset(Vector3::ZERO);
    offset.z_ = GetDrawOrigin().z_;

    switch (align_h_)
    {
    case HA_LEFT:
        break;

    case HA_CENTER:
        offset.x_ -= (float)content_size_.x_ * 0.5f;
        break;

    case HA_RIGHT:
        offset.x_ -= content_size_.x_;
        break;
    }

    switch (align_v_)
    {
    case VA_TOP:
        break;

    case VA_CENTER:
      offset.y_ -= content_size_.y_ * 0.5f;
        break;

    case VA_BOTTOM:
        offset.y_ -= content_size_.y_;
        break;
    }

    static const float unitPerPixel = 1.0f / 128.0f;

    boundingBox_.Clear();
    boundingBox_.Define(Vector3(offset.x_, offset.y_) * unitPerPixel, Vector3(content_size_ + Vector2(offset.x_, offset.y_)) * unitPerPixel);
    boundingBox_.min_.y_ = -boundingBox_.min_.y_;
    boundingBox_.max_.y_ = -boundingBox_.max_.y_;

    if (ui_vertex_data_.Size())
    {
        for (unsigned i = 0; i < ui_vertex_data_.Size(); i += UI_VERTEX_SIZE)
        {
            Vector3& position = *(reinterpret_cast<Vector3*>(&ui_vertex_data_[i]));
            position += offset;
            position *= unitPerPixel;
            position.y_ = -position.y_;
        }
    }

    if (!clip_to_content_ && clip_region_ != IntRect::ZERO)
    {
        boundingBox_.Define(
          Vector3(((float)clip_region_.left_ + offset.x_) * unitPerPixel, -((float)clip_region_.top_ + offset.y_) * unitPerPixel),
          Vector3(((float)clip_region_.right_ + offset.x_) * unitPerPixel, -((float)clip_region_.bottom_ + offset.y_) * unitPerPixel));
    }

    OnMarkedDirty(node_);
    MarkNetworkUpdate();
}

void RichWidget::UpdateTextMaterials()
{
    batches_.Resize(ui_batches_.Size());
    geometries_.Resize(ui_batches_.Size());

    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        auto& batch = batches_[i];

        batch.worldTransform_ = &node_->GetWorldTransform();

        if (!geometries_[i])
        {
          Geometry* geometry = new Geometry(context_);
          geometry->SetVertexBuffer(0, vertex_buffer_);
          batch.geometry_ = geometries_[i] = geometry;
        }

        batch.material_ = items_[batch_index_to_item_index_[i]]->material_;

        Texture* texture = ui_batches_[i].texture_;
        if (batch.material_ && texture)
            batch.material_->SetTexture(TU_DIFFUSE, texture);
    }
}

/// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update.)
void RichWidget::UpdateGeometry(const FrameInfo& frame)
{
    if (IsFlagged(WidgetFlags_GeometryDirty))
    {
        for (unsigned i = 0; i < batches_.Size() && i < ui_batches_.Size(); ++i)
        {
            Geometry* geometry = geometries_[i];
            batches_[i].geometry_ = geometry;
            geometry->SetDrawRange(TRIANGLE_LIST, 0, 0, ui_batches_[i].vertexStart_ / UI_VERTEX_SIZE,
              (ui_batches_[i].vertexEnd_ - ui_batches_[i].vertexStart_) / UI_VERTEX_SIZE);
        }

        if (ui_vertex_data_.Size())
        {
            unsigned vertexCount = ui_vertex_data_.Size() / UI_VERTEX_SIZE;
            if (vertex_buffer_->GetVertexCount() != vertexCount)
                vertex_buffer_->SetSize(vertexCount, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1);
            vertex_buffer_->SetData(&ui_vertex_data_[0]);
        }

        ClearFlags(WidgetFlags_GeometryDirty);
    }
}

/// Return whether a geometry update is necessary, and if it can happen in a worker thread.
UpdateGeometryType RichWidget::GetUpdateGeometryType()
{
    if (IsFlagged(WidgetFlags_GeometryDirty))
        Draw();
    return IsFlagged(WidgetFlags_GeometryDirty) ? UPDATE_MAIN_THREAD : UPDATE_NONE;
}

// Recalculate the world-space bounding box.
void RichWidget::OnWorldBoundingBoxUpdate()
{
    worldBoundingBox_ = boundingBox_.Transformed(node_->GetWorldTransform());
}


} // namespace Urho3D