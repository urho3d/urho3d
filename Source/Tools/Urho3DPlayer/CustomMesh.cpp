#include "CustomMesh.h"
#include <Urho3D/DebugNew.h>

namespace Urho3D
{
CustomMesh::CustomMesh(Context *context)
    :Drawable(context, DRAWABLE_GEOMETRY),
     geometry_(new Geometry(context)),
     vertexBuffer_(new VertexBuffer(context_)),
     indexBuffer_(new IndexBuffer(context_)),
     relativePosition_(true)
{
    drawableFlags_ = DRAWABLE_GEOMETRY;
    geometry_->SetVertexBuffer(0, vertexBuffer_, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1 );
    geometry_->SetIndexBuffer(indexBuffer_);
    batches_.Resize(1);
    batches_[0].geometry_ = geometry_;
    batches_[0].geometryType_ = GEOM_STATIC;
}

CustomMesh::~CustomMesh()
{

}

void CustomMesh::UpdateGeometry(const FrameInfo &frame)
{
    if (bufferSizeDirty_ || indexBuffer_->IsDataLost())
        UpdateBufferSize();

    if (bufferDirty_ || vertexBuffer_->IsDataLost())
        UpdateVertexBuffer(frame);
}

UpdateGeometryType CustomMesh::GetUpdateGeometryType()
{
    if (bufferDirty_ || bufferSizeDirty_ || vertexBuffer_->IsDataLost() || indexBuffer_->IsDataLost())
        return UPDATE_MAIN_THREAD;
    else
        return UPDATE_NONE;
}

void CustomMesh::UpdateBufferSize()
{
}

void CustomMesh::UpdateVertexBuffer(const Urho3D::FrameInfo &frame)
{
}

void CustomMesh::OnWorldBoundingBoxUpdate()
{
    worldBoundingBox_.Clear();
    worldBoundingBox_.Merge(node_->GetWorldPosition());
}

Material* CustomMesh::GetMaterial() const
{
    return batches_[0].material_;
}

void CustomMesh::SetMaterialAttr( const ResourceRef& value )
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetMaterial(cache->GetResource<Material>(value.name_));
}

ResourceRef CustomMesh::GetMaterialAttr() const
{
    return GetResourceRef(batches_[0].material_, Material::GetTypeStatic());
}

void CustomMesh::SetMaterial( Material* material )
{
    batches_[0].material_ = material;
}

void CustomMesh::UpdateBatches( const FrameInfo& frame )
{
    Drawable::UpdateBatches(frame);
    batches_[0].distance_ = distance_;
    batches_[0].worldTransform_ = relativePosition_ ? &node_->GetWorldTransform() : &Matrix3x4::IDENTITY;
}



}



