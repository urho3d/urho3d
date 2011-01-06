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

#ifndef RENDERER_MODEL_H
#define RENDERER_MODEL_H

#include "BoundingBox.h"
#include "Skeleton.h"
#include "Resource.h"
#include "SharedPtr.h"
#include "SharedArrayPtr.h"

#include <map>
#include <vector>

class Bone;
class Geometry;
class IndexBuffer;
class Renderer;
class VertexBuffer;

//! Vertex buffer morph data
struct VertexBufferMorph
{
    //! Vertex elements
    unsigned mElementMask;
    //! Number of vertices
    unsigned mVertexCount;
    //! Morphed vertices. Stored packed as <index, data> pairs
    SharedArrayPtr<unsigned char> mMorphData;
};

//! Model vertex morph
struct ModelMorph
{
    //! Morph name
    std::string mName;
    //! Morph name hash
    StringHash mNameHash;
    //! Current morph weight
    float mWeight;
    //! Morph data per vertex buffer
    std::map<unsigned, VertexBufferMorph> mBuffers;
};

//! Model resource
class Model : public Resource
{
    DEFINE_TYPE(Model);
    
public:
    //! Construct with renderer subsystem pointer and name. Renderer can be null to initialize in CPU-only mode
    Model(Renderer* renderer, const std::string& name = std::string());
    //! Destruct
    virtual ~Model();
    
    //! Load resource. Throw exception on error
    virtual void load(Deserializer& source, ResourceCache* cache = 0);
    
    //! Set bounding box
    void setBoundingBox(const BoundingBox& box);
    //! Set number of geometries
    void setNumGeometries(unsigned num);
    //! Set number of LOD levels in a geometry
    bool setNumGeometryLodLevels(unsigned index, unsigned num);
    //! Set geometry
    bool setGeometry(unsigned index, unsigned lodLevel, Geometry* geometry);
    //! Set skeleton
    void setSkeleton(const Skeleton& skeleton);
    //! Set bone mappings when model has more bones than skinning shader can handle
    void setGeometryBoneMappings(const std::vector<std::vector<unsigned> >& mappings);
    //! Set vertex morphs
    void setMorphs(const std::vector<ModelMorph>& morphs);
    //! Set LOD level to use for physics collision geometry
    void setCollisionLodLevel(unsigned lodLevel);
    //! Set LOD level to use for rendering raycast
    void setRaycastLodLevel(unsigned lodLevel);
    //! Set LOD level to use for occlusion rendering
    void setOcclusionLodLevel(unsigned lodLevel);
    
    //! Return bounding box
    const BoundingBox& getBoundingBox() const { return mBoundingBox; }
    //! Return skeleton
    const Skeleton& getSkeleton() const { return mSkeleton; }
    //! Return vertex buffers
    const std::vector<SharedPtr<VertexBuffer> >& getVertexBuffers() const { return mVertexBuffers; }
    //! Return index buffers
    const std::vector<SharedPtr<IndexBuffer> >& getIndexBuffers() const { return mIndexBuffers; }
    //! Return number of geometries
    unsigned getNumGeometries() const { return mGeometries.size(); }
    //! Return number of LOD levels in geometry
    unsigned getNumGeometryLodLevels(unsigned index) const;
    //! Return geometry pointers
    const std::vector<std::vector<SharedPtr<Geometry> > >& getGeometries() const { return mGeometries; }
    //! Return geometry by index and LOD level
    Geometry* getGeometry(unsigned index, unsigned lodLevel) const;
    //! Return geometery bone mappings
    const std::vector<std::vector<unsigned> >& getGeometryBoneMappings() const { return mGeometryBoneMappings; }
    //! Return vertex morphs
    const std::vector<ModelMorph>& getMorphs() const { return mMorphs; }
    //! Return number of vertex morphs
    unsigned getNumMorphs() const { return mMorphs.size(); }
    //! Return vertex morph by index
    const ModelMorph* getMorph(unsigned index) const;
    //! Return vertex morph by name
    const ModelMorph* getMorph(const std::string& name) const;
    //! Return vertex morph by name hash
    const ModelMorph* getMorph(StringHash nameHash) const;
    //! Return LOD level to use for physics collision geometry
    unsigned getCollisionLodLevel() const { return mCollisionLodLevel; }
    //! Return LOD level to use for renderer raycast
    unsigned getRaycastLodLevel() const { return mRaycastLodLevel; }
    //! Return LOD level to use for occlusion rendering
    unsigned getOcclusionLodLevel() const { return mOcclusionLodLevel; }
    
private:
    //! Renderer subsystem pointer
    WeakPtr<Renderer> mRenderer;
    //! Bounding box
    BoundingBox mBoundingBox;
    //! Skeleton
    Skeleton mSkeleton;
    //! Vertex buffer pointers
    std::vector<SharedPtr<VertexBuffer> > mVertexBuffers;
    //! Index buffer pointers
    std::vector<SharedPtr<IndexBuffer> > mIndexBuffers;
    //! Geometry pointers
    std::vector<std::vector<SharedPtr<Geometry> > > mGeometries;
    //! Geometry bone mappings
    std::vector<std::vector<unsigned> > mGeometryBoneMappings;
    //! Vertex morphs
    std::vector<ModelMorph> mMorphs;
    //! LOD level to use for physics collision geometry
    unsigned mCollisionLodLevel;
    //! LOD level to use for renderer raycast
    unsigned mRaycastLodLevel;
    //! LOD level to use for occlusion rendering
    unsigned mOcclusionLodLevel;
};

#endif // RENDERER_MODEL_H
