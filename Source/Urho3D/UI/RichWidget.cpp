#include "../UI/RichWidget.h"
#include "../UI/RichBatchText.h"
#include "../UI/RichBatchImage.h"
#include "../Core/Context.h"
#include "../Scene/Node.h"
#include "../Graphics/Camera.h"

namespace Urho3D {

extern const char* faceCameraModeNames[];

static const char* horizontal_alignments[] =
{
  "Left",
  "Center",
  "Right",
  0
};

static const char* vertical_alignments[] =
{
  "Top",
  "Center",
  "Bottom",
  0
};

const float RichWidget::unitsPerPixel = 1.0f / 128;

/// Register object factory. Drawable must be registered first.
void RichWidget::RegisterObject(Context* context)
{
    context->RegisterFactory<RichWidget>();
    RichWidgetImage::RegisterObject(context);
    RichWidgetText::RegisterObject(context);

    URHO3D_ACCESSOR_ATTRIBUTE("Auto Clip", GetClipToContent, SetClipToContent, bool, true, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Clip Region", GetClipRegion, SetClipRegion, IntRect, IntRect::ZERO, AM_DEFAULT);
    URHO3D_MIXED_ACCESSOR_ATTRIBUTE("Padding", GetPadding, SetPadding, IntRect, IntRect::ZERO, AM_DEFAULT);
    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Node Align H", GetHorizontalAlignment, SetHorizontalAlignment, HorizontalAlignment,
      horizontal_alignments, HA_LEFT, AM_DEFAULT);
    URHO3D_ENUM_ACCESSOR_ATTRIBUTE("Node Align V", GetVerticalAlignment, SetVerticalAlignment, VerticalAlignment,
      vertical_alignments, VA_TOP, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Fixed Screen Size", IsFixedScreenSize, SetFixedScreenSize, bool, false, AM_DEFAULT);
    URHO3D_ENUM_ATTRIBUTE("Face Camera Mode", faceCameraMode_, faceCameraModeNames, FC_NONE, AM_DEFAULT);
    URHO3D_ATTRIBUTE("Min Angle", float, minAngle_, 0.0f, AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
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
 , customWorldTransform_(Matrix3x4::IDENTITY)
 , faceCameraMode_(FC_NONE)
 , minAngle_(0.0f)
 , fixedScreenSize_(false)
{
 
}

RichWidget::~RichWidget()
{
    RemoveWidgetBatches();
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

void RichWidget::RemoveWidgetBatches()
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
        cliprect.min_.x_ = (float)clip_region_.left_;
        cliprect.min_.y_ = (float)clip_region_.top_;
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

void RichWidget::SetFixedScreenSize(bool enable)
{
    if (enable != fixedScreenSize_)
    {
        fixedScreenSize_ = enable;

        // Bounding box must be recalculated
        OnMarkedDirty(node_);
        MarkNetworkUpdate();
    }
}

void RichWidget::SetFaceCameraMode(FaceCameraMode mode)
{
    if (mode != faceCameraMode_)
    {
        faceCameraMode_ = mode;

        // Bounding box must be recalculated
        OnMarkedDirty(node_);
        MarkNetworkUpdate();
    }
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
    RemoveUnusedWidgetBatches();
}

void RichWidget::UpdateBatches(const FrameInfo& frame)
{
    distance_ = frame.camera_->GetDistance(GetWorldBoundingBox().Center());

    if (faceCameraMode_ != FC_NONE || fixedScreenSize_)
        CalculateFixedScreenSize(frame);

    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        batches_[i].distance_ = distance_;
        batches_[i].worldTransform_ = (faceCameraMode_ != FC_NONE || fixedScreenSize_) ? &customWorldTransform_ : &node_->GetWorldTransform();
    }
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

    Vector2 align_size = content_size_;
    if (!clip_to_content_ && clip_region_ != IntRect::ZERO)
      align_size = Vector2((float)clip_region_.Width(), (float)clip_region_.Height());

    switch (align_h_)
    {
    case HA_LEFT:
        break;

    case HA_CENTER:
        offset.x_ -= (float)align_size.x_ * 0.5f;
        break;

    case HA_RIGHT:
        offset.x_ -= align_size.x_;
        break;
    }

    switch (align_v_)
    {
    case VA_TOP:
        break;

    case VA_CENTER:
        offset.y_ -= align_size.y_ * 0.5f;
        break;

    case VA_BOTTOM:
        offset.y_ -= align_size.y_;
        break;
    }

    boundingBox_.Clear();
    boundingBox_.Define(Vector3(offset.x_, offset.y_) * unitsPerPixel, Vector3(align_size + Vector2(offset.x_, offset.y_)) * unitsPerPixel);
    boundingBox_.min_.y_ = -boundingBox_.min_.y_;
    boundingBox_.max_.y_ = -boundingBox_.max_.y_;

    if (ui_vertex_data_.Size())
    {
        for (unsigned i = 0; i < ui_vertex_data_.Size(); i += UI_VERTEX_SIZE)
        {
            Vector3& position = *(reinterpret_cast<Vector3*>(&ui_vertex_data_[i]));
            position += offset;
            position *= unitsPerPixel;
            position.y_ = -position.y_;
        }
    }

    if (!clip_to_content_ && clip_region_ != IntRect::ZERO)
    {
        boundingBox_.Define(
          Vector3(((float)clip_region_.left_ + offset.x_) * unitsPerPixel, -((float)clip_region_.top_ + offset.y_) * unitsPerPixel),
          Vector3(((float)clip_region_.right_ + offset.x_) * unitsPerPixel, -((float)clip_region_.bottom_ + offset.y_) * unitsPerPixel));
    }

    OnMarkedDirty(node_);
    MarkNetworkUpdate();
    worldBoundingBoxDirty_ = true;
}

void RichWidget::UpdateTextMaterials()
{
    batches_.Resize(ui_batches_.Size());
    geometries_.Resize(ui_batches_.Size());

    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        auto& batch = batches_[i];

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
    // In case is being rendered from multiple views, recalculate camera facing & fixed size
    if (faceCameraMode_ != FC_NONE || fixedScreenSize_)
        CalculateFixedScreenSize(frame);

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
    // In face camera mode, use the last camera rotation to build the world bounding box
    if (faceCameraMode_ != FC_NONE || fixedScreenSize_)
    {
        worldBoundingBox_ = boundingBox_.Transformed(Matrix3x4(node_->GetWorldPosition(),
            customWorldTransform_.Rotation(), customWorldTransform_.Scale()));
    }
    else
        worldBoundingBox_ = boundingBox_.Transformed(node_->GetWorldTransform());
}

void RichWidget::CalculateFixedScreenSize(const FrameInfo& frame)
{
    Vector3 worldPosition = node_->GetWorldPosition();
    Vector3 worldScale = node_->GetWorldScale();

    if (fixedScreenSize_)
    {
        float textScaling = 2.0f / unitsPerPixel / frame.viewSize_.y_;
        float halfViewWorldSize = frame.camera_->GetHalfViewSize();

        if (!frame.camera_->IsOrthographic())
        {
            Matrix4 viewProj(frame.camera_->GetProjection() * frame.camera_->GetView());
            Vector4 projPos(viewProj * Vector4(worldPosition, 1.0f));
            worldScale *= textScaling * halfViewWorldSize * projPos.w_;
        }
        else
            worldScale *= textScaling * halfViewWorldSize;
    }

    customWorldTransform_ = Matrix3x4(worldPosition, frame.camera_->GetFaceCameraRotation(
        worldPosition, node_->GetWorldRotation(), faceCameraMode_, minAngle_), worldScale);
    worldBoundingBoxDirty_ = true;
}

} // namespace Urho3D