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

#ifndef RENDERER_GEOMETRY_H
#define RENDERER_GEOMETRY_H

#include "RendererDefs.h"
#include "SharedPtr.h"

#include <map>
#include <vector>

class IndexBuffer;
class Ray;
class Renderer;
class VertexBuffer;

//! Defines one or more vertex buffers, an index buffer and a draw range
class Geometry : public RefCounted
{
public:
    //! Construct with one empty vertex buffer
    Geometry();
    //! Destruct
    virtual ~Geometry();
    
    //! Set number of vertex buffer
    bool setNumVertexBuffers(unsigned num);
    //! Set a vertex buffer by index
    bool setVertexBuffer(unsigned index, VertexBuffer* buffer, unsigned elementMask = MASK_DEFAULT);
    //! Set the index buffer
    void setIndexBuffer(IndexBuffer* buffer);
    //! Set the draw range
    bool setDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, bool getUsedVertexRange = true);
    //! Set the draw range
    bool setDrawRange(PrimitiveType type, unsigned indexStart, unsigned indexCount, unsigned vertexStart, unsigned vertexCount);
    //! Set instance count
    void setInstanceCount(unsigned count);
    //! Set the LOD distance to report
    void setLodDistance(float distance);
    //! Draw
    void draw(Renderer* renderer);
    
    //! Return all vertex buffers
    const std::vector<SharedPtr<VertexBuffer> >& getVertexBuffers() const { return mVertexBuffers; }
    //! Return vertex element masks
    const std::vector<unsigned>& getVertexElementMasks() const { return mVertexElementMasks; }
    //! Return number of vertex buffers
    unsigned getNumVertexBuffers() const { return mVertexBuffers.size(); }
    //! Return vertex buffer by index
    VertexBuffer* getVertexBuffer(unsigned index) const;
    //! Return vertex element mask by index
    unsigned getVertexElementMask(unsigned index) const;
    //! Return the index buffer
    IndexBuffer* getIndexBuffer() const { return mIndexBuffer; }
    //! Return primitive type
    PrimitiveType getPrimitiveType() const { return mPrimitiveType; }
    //! Return start index
    unsigned getIndexStart() const { return mIndexStart; }
    //! Return number of indices
    unsigned getIndexCount() const { return mIndexCount; }
    //! Return first used vertex
    unsigned getVertexStart() const { return mVertexStart; }
    //! Return number of used vertices
    unsigned getVertexCount() const { return mVertexCount; }
    //! Return number of instances
    unsigned getInstanceCount() const { return mInstanceCount; }
    //! Return LOD distance
    float getLodDistance() const { return mLodDistance; }
    //! Return buffers' combined hash value for state sorting
    unsigned short getBufferHash() const;
    //! Return ray hit distance or infinity if no hit
    float getDistance(const Ray& ray);
    //! Lock vertex and index data. Return null pointers if can not lock
    void lockRawData(const unsigned char*& vertexData, unsigned& vertexSize, const unsigned char*& indexData, unsigned& indexSize);
    //! Unlock vertex and index data
    void unlockRawData();
    
private:
    //! Locate vertex buffer with position data
    void getPositionBufferIndex();
    
    //! Vertex buffers
    std::vector<SharedPtr<VertexBuffer> > mVertexBuffers;
    //! Vertex element masks
    std::vector<unsigned> mVertexElementMasks;
    //! Index buffer
    SharedPtr<IndexBuffer> mIndexBuffer;
    //! Primitive type
    PrimitiveType mPrimitiveType;
    //! Start index
    unsigned mIndexStart;
    //! Number of indices
    unsigned mIndexCount;
    //! First used vertex
    unsigned mVertexStart;
    //! Number of used vertices
    unsigned mVertexCount;
    //! Instance count
    unsigned mInstanceCount;
    //! Index of vertex buffer with position data
    unsigned mPositionBufferIndex;
    //! LOD distance
    float mLodDistance;
};

#endif // RENDERER_GEOMETRY_H
