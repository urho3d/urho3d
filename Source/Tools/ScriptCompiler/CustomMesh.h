#pragma once
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/OctreeQuery.h>
#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/Graphics/IndexBuffer.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Drawable.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Material.h>

namespace Urho3D
{
class IndexBuffer;
class Graphics;
class VertexBuffer;

class CustomMesh : public Drawable
{
public:
    CustomMesh(Context* context);
    virtual ~CustomMesh();
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update.)
    virtual void UpdateGeometry(const FrameInfo& frame);
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    virtual UpdateGeometryType GetUpdateGeometryType();
    /// Set Material
    void SetMaterial(Material* material);
    /// Return material.
    Material* GetMaterial() const;
    /// Set material attribute.
    void SetMaterialAttr(const ResourceRef& value);
    /// Return material attribute.
    ResourceRef GetMaterialAttr() const;

    virtual void UpdateBatches(const FrameInfo& frame);
protected:
    /// Resize  vertex and index buffers.
    virtual void UpdateBufferSize();
    /// Rewrite  vertex buffer.
    virtual void UpdateVertexBuffer(const FrameInfo& frame);
    virtual void OnWorldBoundingBoxUpdate();
protected:
    /// Geometry.
    SharedPtr<Geometry>             geometry_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer>         vertexBuffer_;
    /// Index buffer.
    SharedPtr<IndexBuffer>          indexBuffer_;
    /// Buffers need resize flag.
    bool                            bufferSizeDirty_;
    /// Vertex buffer needs rewrite flag.
    bool                            bufferDirty_;
    /// is vertex pos relative or not
    bool                            relativePosition_;
};
}
