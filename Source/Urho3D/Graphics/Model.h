// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/ArrayPtr.h"
#include "../Container/Ptr.h"
#include "../Graphics/Skeleton.h"
#include "../GraphicsAPI/GraphicsDefs.h"
#include "../Math/BoundingBox.h"
#include "../Resource/Resource.h"

namespace Urho3D
{

class Geometry;
class IndexBuffer;
class Graphics;
class VertexBuffer;

/// Vertex buffer morph data.
struct VertexBufferMorph
{
    /// Vertex elements.
    VertexElements elementMask_;
    /// Number of vertices.
    unsigned vertexCount_;
    /// Morphed vertices data size as bytes.
    unsigned dataSize_;
    /// Morphed vertices. Stored packed as <index, data> pairs.
    SharedArrayPtr<unsigned char> morphData_;
};

/// Definition of a model's vertex morph.
struct ModelMorph
{
    /// Morph name.
    String name_;
    /// Morph name hash.
    StringHash nameHash_;
    /// Current morph weight.
    float weight_;
    /// Morph data per vertex buffer.
    HashMap<unsigned, VertexBufferMorph> buffers_;
};

/// Description of vertex buffer data for asynchronous loading.
struct VertexBufferDesc
{
    /// Vertex count.
    unsigned vertexCount_;
    /// Vertex declaration.
    Vector<VertexElement> vertexElements_;
    /// Vertex data size.
    unsigned dataSize_;
    /// Vertex data.
    SharedArrayPtr<unsigned char> data_;
};

/// Description of index buffer data for asynchronous loading.
struct IndexBufferDesc
{
    /// Index count.
    unsigned indexCount_;
    /// Index size.
    unsigned indexSize_;
    /// Index data size.
    unsigned dataSize_;
    /// Index data.
    SharedArrayPtr<unsigned char> data_;
};

/// Description of a geometry for asynchronous loading.
struct GeometryDesc
{
    /// Primitive type.
    PrimitiveType type_;
    /// Vertex buffer ref.
    unsigned vbRef_;
    /// Index buffer ref.
    unsigned ibRef_;
    /// Index start.
    unsigned indexStart_;
    /// Index count.
    unsigned indexCount_;
};

/// 3D model resource.
class URHO3D_API Model : public ResourceWithMetadata
{
    URHO3D_OBJECT(Model, ResourceWithMetadata);

public:
    /// Construct.
    explicit Model(Context* context);
    /// Destruct.
    ~Model() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    bool BeginLoad(Deserializer& source) override;
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    bool EndLoad() override;
    /// Save resource. Return true if successful.
    bool Save(Serializer& dest) const override;

    /// Set local-space bounding box.
    /// @property
    void SetBoundingBox(const BoundingBox& box);
    /// Set vertex buffers and their morph ranges.
    bool SetVertexBuffers(const Vector<SharedPtr<VertexBuffer>>& buffers, const Vector<unsigned>& morphRangeStarts,
        const Vector<unsigned>& morphRangeCounts);
    /// Set index buffers.
    bool SetIndexBuffers(const Vector<SharedPtr<IndexBuffer>>& buffers);
    /// Set number of geometries.
    /// @property
    void SetNumGeometries(unsigned num);
    /// Set number of LOD levels in a geometry.
    /// @property
    bool SetNumGeometryLodLevels(unsigned index, unsigned num);
    /// Set geometry.
    bool SetGeometry(unsigned index, unsigned lodLevel, Geometry* geometry);
    /// Set geometry center.
    /// @property{set_geometryCenters}
    bool SetGeometryCenter(unsigned index, const Vector3& center);
    /// Set skeleton.
    void SetSkeleton(const Skeleton& skeleton);
    /// Set bone mappings when model has more bones than the skinning shader can handle.
    void SetGeometryBoneMappings(const Vector<Vector<unsigned>>& geometryBoneMappings);
    /// Set vertex morphs.
    void SetMorphs(const Vector<ModelMorph>& morphs);
    /// Clone the model. The geometry data is deep-copied and can be modified in the clone without affecting the original.
    SharedPtr<Model> Clone(const String& cloneName = String::EMPTY) const;

    /// Return bounding box.
    /// @property
    const BoundingBox& GetBoundingBox() const { return boundingBox_; }

    /// Return skeleton.
    /// @property
    Skeleton& GetSkeleton() { return skeleton_; }

    /// Return vertex buffers.
    const Vector<SharedPtr<VertexBuffer>>& GetVertexBuffers() const { return vertexBuffers_; }

    /// Return index buffers.
    const Vector<SharedPtr<IndexBuffer>>& GetIndexBuffers() const { return indexBuffers_; }

    /// Return number of geometries.
    /// @property
    unsigned GetNumGeometries() const { return geometries_.Size(); }

    /// Return number of LOD levels in geometry.
    /// @property
    unsigned GetNumGeometryLodLevels(unsigned index) const;

    /// Return geometry pointers.
    const Vector<Vector<SharedPtr<Geometry>>>& GetGeometries() const { return geometries_; }

    /// Return geometry center points.
    const Vector<Vector3>& GetGeometryCenters() const { return geometryCenters_; }

    /// Return geometry by index and LOD level. The LOD level is clamped if out of range.
    Geometry* GetGeometry(unsigned index, unsigned lodLevel) const;

    /// Return geometry center by index.
    /// @property{get_geometryCenters}
    const Vector3& GetGeometryCenter(i32 index) const
    {
        assert(index >= 0);
        return index < geometryCenters_.Size() ? geometryCenters_[index] : Vector3::ZERO;
    }

    /// Return geometery bone mappings.
    const Vector<Vector<unsigned>>& GetGeometryBoneMappings() const { return geometryBoneMappings_; }

    /// Return vertex morphs.
    const Vector<ModelMorph>& GetMorphs() const { return morphs_; }

    /// Return number of vertex morphs.
    /// @property
    unsigned GetNumMorphs() const { return morphs_.Size(); }

    /// Return vertex morph by index.
    const ModelMorph* GetMorph(unsigned index) const;
    /// Return vertex morph by name.
    const ModelMorph* GetMorph(const String& name) const;
    /// Return vertex morph by name hash.
    const ModelMorph* GetMorph(StringHash nameHash) const;
    /// Return vertex buffer morph range start.
    unsigned GetMorphRangeStart(unsigned bufferIndex) const;
    /// Return vertex buffer morph range vertex count.
    unsigned GetMorphRangeCount(unsigned bufferIndex) const;

private:
    /// Bounding box.
    BoundingBox boundingBox_;
    /// Skeleton.
    Skeleton skeleton_;
    /// Vertex buffers.
    Vector<SharedPtr<VertexBuffer>> vertexBuffers_;
    /// Index buffers.
    Vector<SharedPtr<IndexBuffer>> indexBuffers_;
    /// Geometries.
    Vector<Vector<SharedPtr<Geometry>>> geometries_;
    /// Geometry bone mappings.
    Vector<Vector<unsigned>> geometryBoneMappings_;
    /// Geometry centers.
    Vector<Vector3> geometryCenters_;
    /// Vertex morphs.
    Vector<ModelMorph> morphs_;
    /// Vertex buffer morph range start.
    Vector<unsigned> morphRangeStarts_;
    /// Vertex buffer morph range vertex count.
    Vector<unsigned> morphRangeCounts_;
    /// Vertex buffer data for asynchronous loading.
    Vector<VertexBufferDesc> loadVBData_;
    /// Index buffer data for asynchronous loading.
    Vector<IndexBufferDesc> loadIBData_;
    /// Geometry definitions for asynchronous loading.
    Vector<Vector<GeometryDesc>> loadGeometries_;
};

}
