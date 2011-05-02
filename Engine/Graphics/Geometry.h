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

#include "Object.h"
#include "GraphicsDefs.h"

class IndexBuffer;
class Ray;
class Graphics;
class VertexBuffer;

/// Defines one or more vertex buffers, an index buffer and a draw range
class Geometry : public Object
{
    OBJECT(Geometry);
    
public:
    /// Construct with one empty vertex buffer
    Geometry(Context* context);
    /// Destruct
    virtual ~Geometry();
    
    /// Set number of vertex buffer
    bool SetNumVertexBuffers(unsigned num);
    /// Set a vertex buffer by index
    bool SetVertexBuffer(unsigned index, VertexBuffer* buffer, unsigned elementMask = MASK_DEFAULT);
    /// Set the index buffer
    void SetIndexBuffer(IndexBuffer* buffer);
    /// Set the draw range
    bool SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, bool GetUsedVertexRange = true);
    /// Set the draw range
    bool SetDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned vertexStart, unsigned vertexCount);
    /// Set the LOD distance to report
    void SetLodDistance(float distance);
    /// Draw
    void Draw(Graphics* graphics);
    
    /// Return all vertex buffers
    const std::vector<SharedPtr<VertexBuffer> >& GetVertexBuffers() const { return vertexBuffer_; }
    /// Return vertex element masks
    const std::vector<unsigned>& GetVertexElementMasks() const { return elementMasks_; }
    /// Return number of vertex buffers
    unsigned GetNumVertexBuffers() const { return vertexBuffer_.size(); }
    /// Return vertex buffer by index
    VertexBuffer* GetVertexBuffer(unsigned index) const;
    /// Return vertex element mask by index
    unsigned GetVertexElementMask(unsigned index) const;
    /// Return the index buffer
    IndexBuffer* GetIndexBuffer() const { return indexBuffer_; }
    /// Return primitive type
    PrimitiveType GetPrimitiveType() const { return primitiveType_; }
    /// Return start index
    unsigned GetIndexStart() const { return indexStart_; }
    /// Return number of indices
    unsigned GetIndexCount() const { return indexCount_; }
    /// Return first used vertex
    unsigned GetVertexStart() const { return vertexStart_; }
    /// Return number of used vertices
    unsigned GetVertexCount() const { return vertexCount_; }
    /// Return LOD distance
    float GetLodDistance() const { return lodDistance_; }
    /// Return buffers' combined hash value for state sorting
    unsigned short GetBufferHash() const;
    /// Return ray hit distance or infinity if no hit
    float GetDistance(const Ray& ray);
    /// Lock vertex and index data. Return null pointers if can not lock
    void LockRawData(const unsigned char*& vertexData, unsigned& vertexSize, const unsigned char*& indexData, unsigned& indexSize);
    /// Unlock vertex and index data
    void UnlockRawData();
    
private:
    /// Locate vertex buffer with position data
    void GetPositionBufferIndex();
    
    /// Vertex buffers
    std::vector<SharedPtr<VertexBuffer> > vertexBuffer_;
    /// Vertex element masks
    std::vector<unsigned> elementMasks_;
    /// Index buffer
    SharedPtr<IndexBuffer> indexBuffer_;
    /// Primitive type
    PrimitiveType primitiveType_;
    /// Start index
    unsigned indexStart_;
    /// Number of indices
    unsigned indexCount_;
    /// First used vertex
    unsigned vertexStart_;
    /// Number of used vertices
    unsigned vertexCount_;
    /// Index of vertex buffer with position data
    unsigned positionBufferIndex_;
    /// LOD distance
    float lodDistance_;
};
