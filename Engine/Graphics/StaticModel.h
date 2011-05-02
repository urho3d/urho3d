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

#include "Drawable.h"

class Model;

/// Static model component
class StaticModel : public Drawable
{
    OBJECT(StaticModel);
    
public:
    /// Construct
    StaticModel(Context* context);
    /// Destruct
    ~StaticModel();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Handle attribute write access
    virtual void OnSetAttribute(const AttributeInfo& attr, const Variant& value);
    /// Handle attribute read access
    virtual Variant OnGetAttribute(const AttributeInfo& attr);
    /// Process renderer raycast
    virtual void ProcessRayQuery(RayOctreeQuery& query, float initialDistance);
    /// Prepare geometry for rendering
    virtual void UpdateGeometry(const FrameUpdate& frame);
    /// Return number of batches
    virtual unsigned GetNumBatches();
    /// Return rendering batch
    virtual void GetBatch(const FrameUpdate& frame, unsigned batchIndex, Batch& batch);
    /// Draw to occlusion buffer
    virtual bool DrawOcclusion(OcclusionBuffer* buffer);
    
    /// Set model
    void SetModel(Model* model);
    /// Set material on all geometries
    void SetMaterial(Material* material);
    /// Set material on one geometry
    bool SetMaterial(unsigned index, Material* material);
    /// Set software LOD level, used in raycast and occlusion. By default (M_MAX_UNSIGNED) same as visible
    void SetSoftwareLodLevel(unsigned level);
    
    /// Return model
    Model* GetModel() const { return model_; }
    /// Return model's bounding box
    const BoundingBox& GetBoundingBox() const { return boundingBox_; }
    /// Return number of geometries
    unsigned GetNumGeometries() const { return geometries_.size(); }
    /// Return material by geometry index
    Material* GetMaterial(unsigned index) const;
    /// Return software LOD level
    unsigned GetSoftwareLodLevel() const { return softwareLodLevel_; }
    
protected:
    /// Construct with node flags, initial octant pointer and name
    StaticModel(unsigned flags, Octant* octant, const std::string& name);
    /// Update the world bounding box
    virtual void OnWorldBoundingBoxUpdate();
    /// Set the bounding box
    void SetBoundingBox(const BoundingBox& box);
    /// Set number of geometries
    void SetNumGeometries(unsigned num);
    /// Reset LOD levels
    void ResetLodLevels();
    /// Choose LOD levels based on distance
    void CalculateLodLevels();
    
    /// Model
    SharedPtr<Model> model_;
    /// Bounding box
    BoundingBox boundingBox_;
    /// Geometries
    std::vector<std::vector<SharedPtr<Geometry> > > geometries_;
    /// LOD levels
    std::vector<unsigned> lodLevels_;
    /// Materials
    std::vector<SharedPtr<Material> > materials_;
    /// Software LOD level, used in raycast and occlusion
    unsigned softwareLodLevel_;
    
private:
    /// Handle model reload finished
    void HandleModelReloadFinished(StringHash eventType, VariantMap& eventData);
};
