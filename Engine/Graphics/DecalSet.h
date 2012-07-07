//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "List.h"

/// Decal vertex.
struct DecalVertex
{
    /// Construct with defaults.
    DecalVertex()
    {
    }
    
    /// Construct with parameters.
    DecalVertex(const Vector3& position, const Vector3& normal, const Vector2& texCoord) :
        position_(position),
        normal_(normal),
        texCoord_(texCoord)
    {
    }
    
    /// Position.
    Vector3 position_;
    /// Normal.
    Vector3 normal_;
    /// Texture coordinates coordinates.
    Vector2 texCoord_;
};

/// One decal in a decal set.
struct Decal
{
    /// Construct with defaults.
    Decal() :
        timer_(0.0f),
        timeToLive_(0.0f)
    {
    }
    
    /// Calculate local-space bounding box.
    void CalculateBoundingBox();
    
    /// Decal age timer.
    float timer_;
    /// Maximum time to live in seconds (0 = infinite)
    float timeToLive_;
    /// Local-space bounding box.
    BoundingBox boundingBox_;
    /// Decal vertices.
    PODVector<DecalVertex> vertices_;
};

/// Decal component.
class DecalSet : public Drawable
{
    OBJECT(DecalSet);
    
    /// Construct.
    DecalSet(Context* context);
    /// Destruct.
    virtual ~DecalSet();
    /// Register object factory.
    static void RegisterObject(Context* context);
    
    /// Process octree raycast. May be called from a worker thread.
    virtual void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results);
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateBatches(const FrameInfo& frame);
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update.)
    virtual void UpdateGeometry(const FrameInfo& frame);
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    virtual UpdateGeometryType GetUpdateGeometryType();
    
    /// %Set material.
    void SetMaterial(Material* material);
    /// %Set maximum number of decal vertices.
    void SetMaxVertices(unsigned num);
    /// Add a decal at world coordinates, using an existing drawable's geometry for reference. Return true if successful.
    bool AddDecal(Drawable* target, const Vector3& worldPosition, const Quaternion& worldRotation, const BoundingBox& size, float depthBias, const Vector2& topLeftUV, const Vector2& bottomRightUV, float timeToLive);
    /// Remove n oldest decals.
    void RemoveDecals(unsigned num);
    /// Remove all decals.
    void RemoveAllDecals();
    
    /// Return material.
    Material* GetMaterial() const;
    /// Return number of decals.
    unsigned GetNumDecals() const { return decals_.Size(); }
    /// Retur number of vertices in the decals.
    unsigned GetNumVertices() const { return numVertices_; }
    /// Return maximum number of decal vertices.
    unsigned GetMaxVertices() const { return maxVertices_; }
    
protected:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    
private:
    /// Remove a decal by iterator and return iterator to the next decal.
    List<Decal>::Iterator RemoveDecal(List<Decal>::Iterator i);
    /// Mark decals and the bounding box dirty.
    void MarkDecalsDirty();
    /// Recalculate the local-space bounding box.
    void CalculateBoundingBox();
    /// Resize decal vertex buffer.
    void UpdateBufferSize();
    /// Rewrite decal vertex buffer.
    void UpdateVertexBuffer();
    /// Handle scene post-update event.
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Geometry.
    SharedPtr<Geometry> geometry_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Decals.
    List<Decal> decals_;
    /// Local-space bounding box.
    BoundingBox boundingBox_;
    /// Vertices in the current decals.
    unsigned numVertices_;
    /// Maximum vertices.
    unsigned maxVertices_;
    /// Buffer needs resize flag.
    bool bufferSizeDirty_;
    /// Vertex buffer needs rewrite flag.
    bool bufferDirty_;
    /// Bounding box needs update flag.
    bool boundingBoxDirty_;
};
