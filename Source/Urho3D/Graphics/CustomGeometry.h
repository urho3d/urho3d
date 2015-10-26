//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Graphics/Drawable.h"

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

class VertexBuffer;

/// Custom geometry component.
class URHO3D_API CustomGeometry : public Drawable
{
    URHO3D_OBJECT(CustomGeometry, Drawable);

public:
    /// Construct.
    CustomGeometry(Context* context);
    /// Destruct.
    virtual ~CustomGeometry();
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
    /// Set vertex buffer dynamic mode. A dynamic buffer should be faster to update frequently. Effective at the next Commit() call.
    void SetDynamic(bool enable);
    /// Begin defining a geometry. Clears existing vertices in that index.
    void BeginGeometry(unsigned index, PrimitiveType type);
    /// Define a vertex position. This begins a new vertex.
    void DefineVertex(const Vector3& position);
    /// Define a vertex normal.
    void DefineNormal(const Vector3& normal);
    /// Define a vertex color.
    void DefineColor(const Color& color);
    /// Define a vertex UV coordinate.
    void DefineTexCoord(const Vector2& texCoord);
    /// Define a vertex tangent.
    void DefineTangent(const Vector4& tangent);
    /// Set the primitive type, number of vertices and elements in a geometry, after which the vertices can be edited with GetVertex(). An alternative to BeginGeometry() / DefineVertex().
    void DefineGeometry
        (unsigned index, PrimitiveType type, unsigned numVertices, bool hasNormals, bool hasColors, bool hasTexCoords,
            bool hasTangents);
    /// Update vertex buffer and calculate the bounding box. Call after finishing defining geometry.
    void Commit();
    /// Set material on all geometries.
    void SetMaterial(Material* material);
    /// Set material on one geometry. Return true if successful.
    bool SetMaterial(unsigned index, Material* material);

    /// Return number of geometries.
    unsigned GetNumGeometries() const { return geometries_.Size(); }

    /// Return number of vertices in a geometry.
    unsigned GetNumVertices(unsigned index) const;

    /// Return whether vertex buffer dynamic mode is enabled.
    bool IsDynamic() const { return dynamic_; }

    /// Return material by geometry index.
    Material* GetMaterial(unsigned index = 0) const;

    /// Return all vertices. These can be edited; calling Commit() updates the vertex buffer.
    Vector<PODVector<CustomGeometryVertex> >& GetVertices() { return vertices_; }

    /// Return a vertex in a geometry for editing, or null if out of bounds. After the edits are finished, calling Commit() updates  the vertex buffer.
    CustomGeometryVertex* GetVertex(unsigned geometryIndex, unsigned vertexNum);

    /// Set geometry data attribute.
    void SetGeometryDataAttr(const PODVector<unsigned char>& value);
    /// Set materials attribute.
    void SetMaterialsAttr(const ResourceRefList& value);
    /// Return geometry data attribute.
    PODVector<unsigned char> GetGeometryDataAttr() const;
    /// Return materials attribute.
    const ResourceRefList& GetMaterialsAttr() const;

protected:
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();

private:
    /// Primitive type per geometry.
    PODVector<PrimitiveType> primitiveTypes_;
    /// Source vertices per geometry.
    Vector<PODVector<CustomGeometryVertex> > vertices_;
    /// All geometries.
    Vector<SharedPtr<Geometry> > geometries_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Element mask used so far.
    unsigned elementMask_;
    /// Current geometry being updated.
    unsigned geometryIndex_;
    /// Material list attribute.
    mutable ResourceRefList materialsAttr_;
    /// Vertex buffer dynamic flag.
    bool dynamic_;
};

}
