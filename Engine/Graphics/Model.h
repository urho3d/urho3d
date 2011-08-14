//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "BoundingBox.h"
#include "Skeleton.h"
#include "Resource.h"
#include "Ptr.h"
#include "ArrayPtr.h"

class Geometry;
class IndexBuffer;
class Graphics;
class VertexBuffer;

/// Vertex buffer morph data.
struct VertexBufferMorph
{
    /// Vertex elements.
    unsigned elementMask_;
    /// Number of vertices.
    unsigned vertexCount_;
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
    Map<unsigned, VertexBufferMorph> buffers_;
};

/// 3D model resource.
class Model : public Resource
{
    OBJECT(Model);
    
public:
    /// Construct.
    Model(Context* context);
    /// Destruct.
    virtual ~Model();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful.
    virtual bool Load(Deserializer& source);
    /// Save resource. Return true if successful.
    virtual bool Save(Serializer& dest);
    
    /// %Set bounding box.
    void SetBoundingBox(const BoundingBox& box);
    /// %Set number of geometries.
    void SetNumGeometries(unsigned num);
    /// %Set number of LOD levels in a geometry.
    bool SetNumGeometryLodLevels(unsigned index, unsigned num);
    /// %Set geometry.
    bool SetGeometry(unsigned index, unsigned lodLevel, Geometry* geometry);
    /// %Set skeleton.
    void SetSkeleton(const Skeleton& skeleton);
    /// %Set bone mappings when model has more bones than the skinning shader can handle.
    void SetGeometryBoneMappings(const Vector<PODVector<unsigned> >& mappings);
    /// %Set vertex morphs.
    void SetMorphs(const Vector<ModelMorph>& morphs);
    
    /// Return bounding box.
    const BoundingBox& GetBoundingBox() const { return boundingBox_; }
    /// Return skeleton.
    Skeleton& GetSkeleton() { return skeleton_; }
    /// Return vertex buffers.
    const Vector<SharedPtr<VertexBuffer> >& GetVertexBuffers() const { return vertexBuffers_; }
    /// Return index buffers.
    const Vector<SharedPtr<IndexBuffer> >& GetIndexBuffers() const { return indexBuffers_; }
    /// Return number of geometries.
    unsigned GetNumGeometries() const { return geometries_.Size(); }
    /// Return number of LOD levels in geometry.
    unsigned GetNumGeometryLodLevels(unsigned index) const;
    /// Return geometry pointers.
    const Vector<Vector<SharedPtr<Geometry> > >& GetGeometries() const { return geometries_; }
    /// Return geometry by index and LOD level.
    Geometry* GetGeometry(unsigned index, unsigned lodLevel) const;
    /// Return geometery bone mappings.
    const Vector<PODVector<unsigned> >& GetGeometryBoneMappings() const { return geometryBoneMappings_; }
    /// Return vertex morphs.
    const Vector<ModelMorph>& GetMorphs() const { return morphs_; }
    /// Return number of vertex morphs.
    unsigned GetNumMorphs() const { return morphs_.Size(); }
    /// Return vertex morph by index.
    const ModelMorph* GetMorph(unsigned index) const;
    /// Return vertex morph by name.
    const ModelMorph* GetMorph(const String& name) const;
    /// Return vertex morph by name hash.
    const ModelMorph* GetMorph(StringHash nameHash) const;
    /// Return CPU copy of vertices.
    const PODVector<Vector3>& GetVertices() const { return vertices_; }
    /// Return CPU copy of indices.
    const PODVector<unsigned>& GetIndices() const { return indices_; }
    
private:
    /// Bounding box.
    BoundingBox boundingBox_;
    /// Skeleton.
    Skeleton skeleton_;
    /// Vertex buffers.
    Vector<SharedPtr<VertexBuffer> > vertexBuffers_;
    /// Index buffers.
    Vector<SharedPtr<IndexBuffer> > indexBuffers_;
    /// Geometries.
    Vector<Vector<SharedPtr<Geometry> > > geometries_;
    /// Geometry bone mappings.
    Vector<PODVector<unsigned> > geometryBoneMappings_;
    /// Vertex morphs.
    Vector<ModelMorph> morphs_;
    /// CPU copy of vertex positions.
    PODVector<Vector3> vertices_;
    /// CPU copy of indices.
    PODVector<unsigned> indices_;
};
