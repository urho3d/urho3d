//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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

namespace Urho3D
{

/// Custom geometry vertex.
struct CustomGeometryVertex
{
    /// Position.
    Vector3 position_;
    /// Normal.
    Vector3 normal_;
    /// Color.
    unsigned color_;
    /// Texture coordinates.
    Vector2 texCoord_;
    /// Tangent.
    Vector4 tangent_;
};

/// Custom geometry component.
class CustomGeometry : public Drawable
{
    OBJECT(CustomGeometry);
    
public:
    /// Construct.
    CustomGeometry(Context* context);
    /// Destruct.
    ~CustomGeometry();
    /// Register object factory. Drawable must be registered first.
    static void RegisterObject(Context* context);
    
    /// Process octree raycast. May be called from a worker thread.
    virtual void ProcessRayQuery(const RayOctreeQuery& query, PODVector<RayQueryResult>& results);
    /// Return the geometry for a specific LOD level.
    virtual Geometry* GetLodGeometry(unsigned batchIndex, unsigned level);
    /// Return number of occlusion geometry triangles.
    virtual unsigned GetNumOccluderTriangles();
    /// Draw to occlusion buffer. Return true if did not run out of triangles.
    virtual bool DrawOcclusion(OcclusionBuffer* buffer);
    
    /// Clear all geometries.
    void Clear();
    /// Set number of geometries.
    void SetNumGeometries(unsigned num);
    /// Begin defining a geometry. Clears existing geometry in that index.
    void BeginGeometry(unsigned index, PrimitiveType type);
    /// Define a vertex position. This begins a new vertex.
    void DefineVertex(const Vector3& position);
    /// Define a vertex normal.
    void DefineNormal(const Vector3& normal);
    /// Define a vertex tangent.
    void DefineTangent(const Vector4& tangent);
    /// Define a vertex color.
    void DefineColor(const Color& color);
    /// Define a vertex UV coordinate.
    void DefineTexCoord(const Vector2& texCoord);
    /// Commit all geometries to the vertex buffer and calculate the bounding box.
    void Commit();
    /// Set material on all geometries.
    void SetMaterial(Material* material);
    /// Set material on one geometry. Return true if successful.
    bool SetMaterial(unsigned index, Material* material);
    
    /// Return local space bounding box.
    const BoundingBox& GetBoundingBox() const { return boundingBox_; }
    /// Return number of geometries.
    unsigned GetNumGeometries() const { return geometries_.Size(); }
    /// Return material by geometry index.
    Material* GetMaterial(unsigned index) const;
    
protected:
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    
private:
    /// Recalculate the local-space bounding box.
    void CalculateBoundingBox();
    
    /// Local-space bounding box.
    BoundingBox boundingBox_;
    /// Primitive type per geometry.
    PODVector<PrimitiveType> primitiveTypes_;
    /// Source vertices per geometry.
    Vector<PODVector<CustomGeometryVertex> > vertices_;
    /// All geometries.
    Vector<SharedPtr<Geometry> > geometries_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Material list attribute.
    mutable ResourceRefList materialsAttr_;
    /// Element mask used so far.
    unsigned elementMask_;
    /// Current geometry being updated.
    unsigned geometryIndex_;
};

}
