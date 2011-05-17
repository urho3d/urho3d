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
#include "SharedPtr.h"
#include "SharedArrayPtr.h"

class Geometry;
class IndexBuffer;
class Graphics;
class VertexBuffer;

/// Vertex buffer morph data
struct VertexBufferMorph
{
    /// Vertex elements
    unsigned elementMask_;
    /// Number of vertices
    unsigned vertexCount_;
    /// Morphed vertices. Stored packed as <index, data> pairs
    SharedArrayPtr<unsigned char> morphData_;
};

/// Model vertex morph
struct ModelMorph
{
    /// Morph name
    String name_;
    /// Morph name hash
    StringHash nameHash_;
    /// Current morph weight
    float weight_;
    /// Morph data per vertex buffer
    std::map<unsigned, VertexBufferMorph> buffers_;
};

/// Model resource
class Model : public Resource
{
    OBJECT(Model);
    
public:
    /// Construct
    Model(Context* context);
    /// Destruct
    virtual ~Model();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Load resource. Return true if successful
    virtual bool Load(Deserializer& source);
    /// Save resource. Return true if successful
    virtual bool Save(Serializer& dest);
    
    /// Set bounding box
    void SetBoundingBox(const BoundingBox& box);
    /// Set number of geometries
    void SetNumGeometries(unsigned num);
    /// Set number of LOD levels in a geometry
    bool SetNumGeometryLodLevels(unsigned index, unsigned num);
    /// Set geometry
    bool SetGeometry(unsigned index, unsigned lodLevel, Geometry* geometry);
    /// Set skeleton
    void SetSkeleton(const Skeleton& skeleton);
    /// Set bone mappings when model has more bones than the skinning shader can handle
    void SetGeometryBoneMappings(const std::vector<std::vector<unsigned> >& mappings);
    /// Set vertex morphs
    void SetMorphs(const std::vector<ModelMorph>& morphs);
    
    /// Return bounding box
    const BoundingBox& GetBoundingBox() const { return boundingBox_; }
    /// Return skeleton
    Skeleton& GetSkeleton() { return skeleton_; }
    /// Return vertex buffers
    const std::vector<SharedPtr<VertexBuffer> >& GetVertexBuffers() const { return vertexBuffer_; }
    /// Return index buffers
    const std::vector<SharedPtr<IndexBuffer> >& GetIndexBuffers() const { return indexBuffers_; }
    /// Return number of geometries
    unsigned GetNumGeometries() const { return geometries_.size(); }
    /// Return number of LOD levels in geometry
    unsigned GetNumGeometryLodLevels(unsigned index) const;
    /// Return geometry pointers
    const std::vector<std::vector<SharedPtr<Geometry> > >& GetGeometries() const { return geometries_; }
    /// Return geometry by index and LOD level
    Geometry* GetGeometry(unsigned index, unsigned lodLevel) const;
    /// Return geometery bone mappings
    const std::vector<std::vector<unsigned> >& GetGeometryBoneMappings() const { return geometryBoneMappings_; }
    /// Return vertex morphs
    const std::vector<ModelMorph>& GetMorphs() const { return morphs_; }
    /// Return number of vertex morphs
    unsigned GetNumMorphs() const { return morphs_.size(); }
    /// Return vertex morph by index
    const ModelMorph* GetMorph(unsigned index) const;
    /// Return vertex morph by name
    const ModelMorph* GetMorph(const String& name) const;
    /// Return vertex morph by name hash
    const ModelMorph* GetMorph(StringHash nameHash) const;
    
private:
    /// Bounding box
    BoundingBox boundingBox_;
    /// Skeleton
    Skeleton skeleton_;
    /// Vertex buffer pointers
    std::vector<SharedPtr<VertexBuffer> > vertexBuffer_;
    /// Index buffer pointers
    std::vector<SharedPtr<IndexBuffer> > indexBuffers_;
    /// Geometry pointers
    std::vector<std::vector<SharedPtr<Geometry> > > geometries_;
    /// Geometry bone mappings
    std::vector<std::vector<unsigned> > geometryBoneMappings_;
    /// Vertex morphs
    std::vector<ModelMorph> morphs_;
};
