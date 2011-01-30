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

#ifndef RENDERER_STATICMODEL_H
#define RENDERER_STATICMODEL_H

#include "GeometryNode.h"

class Model;

//! A static model scene node
class StaticModel : public GeometryNode
{
    DEFINE_TYPE(StaticModel);
    
public:
    //! Construct with initial octant pointer and name
    StaticModel(Octant* octant = 0, const std::string& name = std::string());
    //! Destruct
    ~StaticModel();
    
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
    
    //! Set model
    void setModel(Model* model);
    //! Set material on all geometries
    void setMaterial(Material* material);
    //! Set material on one geometry
    bool setMaterial(unsigned index, Material* material);
    
    //! Return model's bounding box
    const BoundingBox& getBoundingBox() const { return mBoundingBox; }
    //! Return number of geometries
    unsigned getNumGeometries() const { return mGeometries.size(); }
    //! Return material by geometry index
    Material* getMaterial(unsigned index) const;
    //! Return model
    Model* getModel() const { return mModel; }
    
protected:
    //! Construct with node flags, initial octant pointer and name
    StaticModel(unsigned flags, Octant* octant, const std::string& name);
    //! Update the world bounding box
    virtual void onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox);
    //! Set the bounding box
    void setBoundingBox(const BoundingBox& box);
    //! Set number of geometries
    void setNumGeometries(unsigned num);
    //! Reset LOD levels
    void resetLodLevels();
    //! Choose LOD levels based on distance
    void calculateLodLevels();
    
    //! Geometries
    std::vector<std::vector<SharedPtr<Geometry> > > mGeometries;
    //! Materials
    std::vector<SharedPtr<Material> > mMaterials;
    //! LOD levels
    std::vector<unsigned> mLodLevels;
    //! Bounding box
    BoundingBox mBoundingBox;
    //! Model
    SharedPtr<Model> mModel;
};

#endif // RENDERER_STATICMODEL_H
