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

#ifndef RENDERER_INSTANCEDMODEL_H
#define RENDERER_INSTANCEDMODEL_H

#include "GeometryNode.h"
#include "Matrix4x3.h"

class IndexBuffer;
class InstanceNode;
class Model;
class Renderer;
class VertexBuffer;

//! Instance transform
struct Instance
{
    //! Position
    Vector3 mPosition;
    //! Rotation
    Quaternion mRotation;
    //! Scale
    Vector3 mScale;
};

//! Scene node that defines instanced geometry
class InstancedModel : public GeometryNode
{
    DEFINE_TYPE(InstancedModel);
    
public:
    //! Construct with initial octant pointer and name
    InstancedModel(Octant* octant = 0, const std::string& name = std::string());
    //! Destruct
    virtual ~InstancedModel();
    
    //! Write component state to a stream
    virtual void save(Serializer& dest);
    //! Read component state from a stream
    virtual void load(Deserializer& source, ResourceCache* cache);
    //! Write component state to an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read component state from an XML element
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Write a network update
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    //! Read a network update
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    
    //! Process renderer raycast
    virtual void processRayQuery(RayOctreeQuery& query, float initialDistance);
    //! Calculate distance for rendering
    virtual void updateDistance(const FrameInfo& frame);
    //! Prepare geometry for rendering
    virtual void updateGeometry(const FrameInfo& frame, Renderer* renderer);
    //! Return number of batches
    virtual unsigned getNumBatches();
    //! Return geometry by batch index
    virtual Geometry* getBatchGeometry(unsigned batchIndex);
    //! Return material by batch index
    virtual Material* getBatchMaterial(unsigned batchIndex);
    //! Return vertex shader parameter
    virtual bool getVertexShaderParameter(unsigned batchIndex, VSParameter parameter, const float** data, unsigned* count);
    //! Draw to occlusion buffer
    virtual bool drawOcclusion(OcclusionBuffer* buffer);
    
    //! Set model
    bool setModel(Model* model);
    //! Set material on all geometries
    void setMaterial(Material* material);
    //! Set material on one geometry
    bool setMaterial(unsigned index, Material* material);
    //! Set number of instances
    void setNumInstances(unsigned num);
    //! Set whether instances are relative to the scene node
    void setInstancesRelative(bool enable);
    //! Call after changing the instances
    void updated();
    
    //! Return model bounding box
    const BoundingBox& getBoundingBox() const { return mBoundingBox; }
    //! Return number of geometries
    unsigned getNumGeometries() const { return mOriginalMaterials.size(); }
    //! Return material by geometry index
    Material* getMaterial(unsigned index) const;
    //! Return model
    Model* getModel() const { return mModel; }
    //! Return number of instances
    unsigned getNumInstances() const { return mInstances.size(); }
    //! Return all instances
    std::vector<Instance>& getInstances() { return mInstances; }
    //! Return instance by index
    Instance* getInstance(unsigned index);
    //! Return whether instances are relative to the scene node
    bool getInstancesRelative() const { return mInstancesRelative; }
    
    //! Set instancing mode (shader or hardware instancing.) Called by Pipeline
    static void setInstancingMode(InstancingMode mode) { sMode = mode; }
    //! Return instancing mode
    static InstancingMode getInstancingMode() { return sMode; }
    
protected:
    //! If relative to the scene node, mark instance transforms needing update
    virtual void onMarkedDirty();
    //! Update world-space bounding box
    virtual void onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox);
    
private:
    //! Build vertex and index buffers
    void buildInstances(Renderer* renderer);
    //! Recalculate instance transforms
    void updateInstanceTransforms();
    //! Update hardware instancing vertex buffer
    void updateHWInstancingBuffer();
    //! Mark instances needing rebuild
    void markInstancesDirty();
    //! Mark instance transforms needing update
    void markInstanceTransformsDirty();
    //! Set bounding box
    void setBoundingBox(const BoundingBox& box);
    //! Reset LOD levels
    void resetLodLevels();
    //! Choose LOD levels based on distance
    void calculateLodLevels();
    
    //! Create a duplicated vertex buffer copy for instancing
    static const SharedPtr<VertexBuffer>& createInstanceVertexBuffer(VertexBuffer* original, unsigned instanceCount);
    //! Create an duplicated index buffer copy for instancing
    static const SharedPtr<IndexBuffer>& createInstanceIndexBuffer(const std::vector<std::vector<SharedPtr<Geometry> > >& geometries,
        unsigned subGeometry, unsigned lodLevel, unsigned instanceCount, unsigned& indexStart);
    //! Clean up unused buffer copies
    static void cleanupInstanceBuffers();
    
    //! Model bounding box
    BoundingBox mBoundingBox;
    //! Model
    SharedPtr<Model> mModel;
    //! Hardware instancing vertex buffer
    SharedPtr<VertexBuffer> mHWInstancingBuffer;
    //! Model's geometries
    std::vector<std::vector<SharedPtr<Geometry> > > mOriginalGeometries;
    //! Materials
    std::vector<SharedPtr<Material> > mOriginalMaterials;
    //! Instancing geometries
    std::vector<std::vector<SharedPtr<Geometry> > > mGeometries;
    //! Instancing materials
    std::vector<SharedPtr<Material> > mMaterials;
    //! LOD levels
    std::vector<unsigned> mOriginalLodLevels;
    //! Instancing LOD levels
    std::vector<unsigned> mLodLevels;
    //! First instance number in each batch
    std::vector<unsigned> mBatchStarts;
    //! Number of instances in each batch
    std::vector<unsigned> mBatchCounts;
    //! Instance structures
    std::vector<Instance> mInstances;
    //! Instance world transform matrices
    std::vector<Matrix4x3> mInstanceTransforms;
    //! Instancing mode used by this scene node
    InstancingMode mMode;
    //! Average scale of instances for LOD calculation
    float mAverageInstanceScale;
    //! Instances relative to the scene node flag
    bool mInstancesRelative;
    //! Instance buffers need update flag
    bool mInstancesDirty;
    //! Instance transforms need update flag
    bool mInstanceTransformsDirty;
    //! Hardware instancing vertex buffer needs update flag
    bool mHWInstancingBufferDirty;
    
    //! Duplicated vertex buffer copies
    static std::map<const VertexBuffer*, SharedPtr<VertexBuffer> > sInstanceVertexBuffers;
    //! Duplicated index buffer copies
    static std::map<std::pair<const IndexBuffer*, unsigned>, SharedPtr<IndexBuffer> > sInstanceIndexBuffers;
    //! Instancing mode
    static InstancingMode sMode;
};

#endif // RENDERER_INSTANCEDNODE_H
