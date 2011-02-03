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

#ifndef RENDERER_CUSTOMOBJECT_H
#define RENDERER_CUSTOMOBJECT_H

#include "GeometryNode.h"
#include "SharedArrayPtr.h"

class IndexBuffer;
class VertexBuffer;

//! Custom geometry definition
class CustomGeometry
{
public:
    //! Construct with empty geometry
    CustomGeometry() :
        mVertexCount(0),
        mVertexSize(0),
        mIndexCount(0),
        mIndexSize(sizeof(unsigned short))
    {
    }
    
    //! Return ray hit distance, or infinity if no hit
    float getDistance(const Ray& ray) const;
    
    //! Vertex data
    SharedArrayPtr<unsigned char> mVertexData;
    //! Index data
    SharedArrayPtr<unsigned char> mIndexData;
    //! Material
    SharedPtr<Material> mMaterial;
    //! Bounding box
    BoundingBox mBoundingBox;
    //! Number of vertices
    unsigned mVertexCount;
    //! Vertex size
    unsigned mVertexSize;
    //! Number of indices
    unsigned mIndexCount;
    //! Index size
    unsigned mIndexSize;
};

//! Scene node which defines custom geometry
class CustomObject : public GeometryNode
{
    DEFINE_TYPE(CustomObject);
    
public:
    //! Construct with initial octant pointer and name
    CustomObject(Octant* octant = 0, const std::string& name = std::string());
    //! Destruct
    virtual ~CustomObject();
    
    //! Write component state to a stream
    virtual void save(Serializer& dest);
    //! Read component state from a stream
    virtual void load(Deserializer& source, ResourceCache* cache);
    //! Write component state to an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read component state from an XML element
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Return resource references
    virtual void getResourceRefs(std::vector<Resource*>& dest);
    
    //! Process renderer raycast
    virtual void processRayQuery(RayOctreeQuery& query, float initialDistance);
    //! Prepare geometry for rendering
    virtual void updateGeometry(const FrameInfo& frame, Renderer* renderer);
    //! Return number of batches
    virtual unsigned getNumBatches();
    //! Return geometry by batch index
    virtual Geometry* getBatchGeometry(unsigned batchIndex);
    //! Return material by batch index
    virtual Material* getBatchMaterial(unsigned batchIndex);
    //! Draw to occlusion buffer
    virtual bool drawOcclusion(OcclusionBuffer* buffer);
    
    //! Set vertex data elements
    bool setVertexElementMask(unsigned mask);
    //! Set number of custom geometries
    void setNumGeometries(unsigned num);
    //! Set geometry vertex and index data
    bool setGeometryData(unsigned index, const void* vertexData, unsigned vertexCount, const void* indexData, unsigned indexCount, bool largeIndices = false);
    //! Set material of all geometries
    void setMaterial(Material* material);
    //! Set material of a geometry
    bool setMaterial(unsigned index, Material* material);
    //! Set optimization mode (combine geometries if same material)
    void setOptimization(bool enable);
    
    //! Return bounding box
    const BoundingBox& getBoundingBox() const { return mBoundingBox; }
    //! Return vertex element mask
    unsigned getVertexElementMask() const { return mVertexElementMask; }
    //! Return number of geometries
    unsigned getNumGeometries() const { return mCustomGeometries.size(); }
    //! Return geometry by index
    const CustomGeometry* getGeometry(unsigned index) const;
    //! Return material by index
    Material* getMaterial(unsigned index) const;
    //! Return optimization mode
    bool getOptimization() const { return mOptimization; }
    
protected:
    //! Update world-space bounding box
    virtual void onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox);
    
private:
    //! Calculate bounding box
    void calculateBoundingBox();
    //! Update vertex and index buffer
    void updateBuffer(Renderer* renderer);
    
    //! Custom geometry definitions
    std::vector<CustomGeometry> mCustomGeometries;
    //! Geometries
    std::vector<SharedPtr<Geometry> > mGeometries;
    //! Materials
    std::vector<SharedPtr<Material> > mMaterials;
    //! Bounding box
    BoundingBox mBoundingBox;
    //! Vertex buffer
    SharedPtr<VertexBuffer> mVertexBuffer;
    //! Index buffer
    SharedPtr<IndexBuffer> mIndexBuffer;
    //! Vertex data elements
    unsigned mVertexElementMask;
    //! Buffers need update flag
    bool mGeometriesDirty;
    //! Optimization flag
    bool mOptimization;
};

#endif // RENDERER_CUSTOMOBJECT_H
