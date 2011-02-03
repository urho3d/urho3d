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

#ifndef RENDERER_BILLBOARDSET_H
#define RENDERER_BILLBOARDSET_H

#include "Color.h"
#include "GeometryNode.h"

class IndexBuffer;
class Renderer;
class VertexBuffer;

//! Billboard state
struct Billboard
{
    //! Position
    Vector3 mPosition;
    //! Two-dimensional size
    Vector2 mSize;
    //! Color
    Color mColor;
    //! Rotation
    float mRotation;
    //! Enabled flag
    bool mEnabled;
};

//! Billboard scene node
class BillboardSet : public GeometryNode
{
    DEFINE_TYPE(BillboardSet);
    
public:
    //! Construct with initial octant pointer and name
    BillboardSet(Octant* octant = 0, const std::string& name = std::string());
    //! Destruct
    virtual ~BillboardSet();
    
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
    //! Return resource references
    virtual void getResourceRefs(std::vector<Resource*>& dest);
    
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
    
    //! Set material
    void setMaterial(Material* material);
    //! Set number of billboards
    void setNumBillboards(unsigned num);
    //! Set whether billboards are relative to the scene node
    void setBillboardsRelative(bool enable);
    //! Set whether billboards are sorted by distance
    void setBillboardsSorted(bool enable);
    //! Set whether scene node scale affects billboards' size
    void setScaleBillboards(bool enable);
    //! Set animation LOD bias
    void setAnimationLodBias(float bias);
    //! Call after changing the billboards
    void updated();
    
    //! Return material
    Material* getMaterial() const { return mMaterial; }
    //! Return number of billboards
    unsigned getNumBillboards() const { return mBillboards.size(); }
    //! Return all billboards
    std::vector<Billboard>& getBillboards() { return mBillboards; }
    //! Return billboard by index
    Billboard* getBillboard(unsigned index);
    //! Return whether billboards are relative to the scene node
    bool getBillboardsRelative() const { return mBillboardsRelative; }
    //! Return whether billboards are sorted
    bool getBillboardsSorted() const { return mBillboardsSorted; }
    //! Return whether scene node scale affects billboards' size
    bool getScaleBillboards() const { return mScaleBillboards; }
    //! Return animation LOD bias
    float getAnimationLodBias() const { return mAnimationLodBias; }
    
protected:
    //! Transform has changed. Mark billboards dirty if necessary
    virtual void onMarkedDirty();
    //! Update world-space bounding box
    virtual void onWorldBoundingBoxUpdate(BoundingBox& worldBoundingBox);
    //! Mark billboard vertex buffer to need an update
    void markPositionsDirty();
    
    //! Billboards
    std::vector<Billboard> mBillboards;
    //! Animation LOD bias
    float mAnimationLodBias;
    //! Animation LOD timer
    float mAnimationLodTimer;
    //! Billboards relative flag
    bool mBillboardsRelative;
    //! Billboards sorted flag
    bool mBillboardsSorted;
    //! Scale affects billboard scale flag
    bool mScaleBillboards;
    
private:
    //! Resize billboard vertex and index buffers
    void updateBufferSize(Renderer* renderer);
    //! Rewrite billboard vertex buffer
    void updateVertexBuffer(const FrameInfo& frame);
    
    //! Geometry
    SharedPtr<Geometry> mGeometry;
    //! Material
    SharedPtr<Material> mMaterial;
    //! Vertex buffer
    SharedPtr<VertexBuffer> mVertexBuffer;
    //! Index buffer
    SharedPtr<IndexBuffer> mIndexBuffer;
    //! Billboard sort order
    std::vector<unsigned> mSortOrder;
    //! Buffers need resize flag
    bool mBufferSizeDirty;
    //! Vertex buffer needs rewrite flag
    bool mBufferDirty;
    //! Force update flag (ignore animation LOD momentarily)
    bool mForceUpdate;
    //! Frame number on which was last sorted
    unsigned mSortFrameNumber;
    //! Previous offset to camera for determining whether sorting is necessary
    Vector3 mPreviousOffset;
};

#endif // RENDERER_BILLBOARDSET_H
