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

#include "Color.h"
#include "Drawable.h"
#include "Rect.h"

class IndexBuffer;
class Graphics;
class VertexBuffer;

/// One billboard in the billboard set
struct Billboard
{
    /// Position
    Vector3 position_;
    /// Two-dimensional size
    Vector2 size_;
    /// UV coordinates
    Rect uv_;
    /// Color
    Color color_;
    /// Rotation
    float rotation_;
    /// Enabled flag
    bool enabled_;
    /// Sort distance
    float sortDistance_;
};

/// Billboard component
class BillboardSet : public Drawable
{
    OBJECT(BillboardSet);
    
public:
    /// Construct
    BillboardSet(Context* context);
    /// Destruct
    virtual ~BillboardSet();
    /// Register object factory
    static void RegisterObject(Context* context);
    
    /// Calculate distance for rendering
    virtual void UpdateDistance(const FrameInfo& frame);
    /// Prepare geometry for rendering
    virtual void UpdateGeometry(const FrameInfo& frame);
    /// Return number of batches
    virtual unsigned GetNumBatches();
    /// Return rendering batch
    virtual void GetBatch(const FrameInfo& frame, unsigned batchIndex, Batch& batch);
    
    /// Set material
    void SetMaterial(Material* material);
    /// Set number of billboards
    void SetNumBillboards(unsigned num);
    /// Set whether billboards are relative to the scene node
    void SetRelative(bool enable);
    /// Set whether scene node scale affects billboards' size
    void SetScaled(bool enable);
    /// Set whether billboards are sorted by distance
    void SetSorted(bool enable);
    /// Set animation LOD bias
    void SetAnimationLodBias(float bias);
    /// Call after changing the billboards
    void Updated();
    
    /// Return material
    Material* GetMaterial() const { return material_; }
    /// Return number of billboards
    unsigned GetNumBillboards() const { return billboards_.Size(); }
    /// Return all billboards
    PODVector<Billboard>& GetBillboards() { return billboards_; }
    /// Return billboard by index
    Billboard* GetBillboard(unsigned index);
    /// Return whether billboards are relative to the scene node
    bool IsRelative() const { return relative_; }
    /// Return whether scene node scale affects billboards' size
    bool IsScaled() const { return scaled_; }
    /// Return whether billboards are sorted
    bool IsSorted() const { return sorted_; }
    /// Return animation LOD bias
    float GetAnimationLodBias() const { return animationLodBias_; }
    
    /// Set material attribute
    void SetMaterialAttr(ResourceRef value);
    /// Set billboards attribute
    void SetBillboardsAttr(PODVector<unsigned char> value);
    /// Return material attribute
    ResourceRef GetMaterialAttr() const;
    /// Return billboards attribute
    PODVector<unsigned char> GetBillboardsAttr() const;
    
protected:
    /// Transform has changed. Mark billboards dirty if necessary
    virtual void OnMarkedDirty(Node* node);
    /// Update world-space bounding box
    virtual void OnWorldBoundingBoxUpdate();
    /// Mark billboard vertex buffer to need an update
    void MarkPositionsDirty();
    
    /// Billboards
    PODVector<Billboard> billboards_;
    /// Animation LOD bias
    float animationLodBias_;
    /// Animation LOD timer
    float animationLodTimer_;
    /// Billboards relative flag
    bool relative_;
    /// Scale affects billboard scale flag
    bool scaled_;
    /// Billboards sorted flag
    bool sorted_;
    
private:
    /// Resize billboard vertex and index buffers
    void UpdateBufferSize();
    /// Rewrite billboard vertex buffer
    void UpdateVertexBuffer(const FrameInfo& frame);
    
    /// Geometry
    SharedPtr<Geometry> geometry_;
    /// Material
    SharedPtr<Material> material_;
    /// Vertex buffer
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Index buffer
    SharedPtr<IndexBuffer> indexBuffer_;
    /// Buffers need resize flag
    bool bufferSizeDirty_;
    /// Vertex buffer needs rewrite flag
    bool bufferDirty_;
    /// Force update flag (ignore animation LOD momentarily)
    bool forceUpdate_;
    /// Frame number on which was last sorted
    unsigned sortFrameNumber_;
    /// Previous offset to camera for determining whether sorting is necessary
    Vector3 previousOffset_;
    /// Billboard pointers for sorting
    Vector<Billboard*> sortedBillboards_;
};
