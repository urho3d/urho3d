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

#ifndef RENDERER_VERTEXBUFFER_H
#define RENDERER_VERTEXBUFFER_H

#include "GPUObject.h"
#include "RendererDefs.h"
#include "SharedArrayPtr.h"

#include <string>

//! A hardware vertex buffer
class VertexBuffer : public RefCounted, public GPUObject
{
public:
    //! Construct with renderer subsystem pointer and dynamic flag
    VertexBuffer(Renderer* renderer, bool dynamic = false);
    //! Destruct
    virtual ~VertexBuffer();
    
    //! Release default pool resources
    virtual void onDeviceLost();
    //! Recreate default pool resources
    virtual void onDeviceReset();
    
    //! Set size and vertex elements
    void setSize(unsigned vertexCount, unsigned elementMask);
    //! Set all data in the buffer
    void setData(const void* data);
    //! Set a data range in the buffer
    void setDataRange(const void* data, unsigned first, unsigned count);
    //! Set the vertex range to use for morphing
    bool setMorphRange(unsigned start, unsigned count);
    //! Set data to be used for resetting the morph vertex range
    void setMorphRangeResetData(const SharedArrayPtr<unsigned char>& data);
    //! Lock a data range in the buffer. Throw an exception if fails
    void* lock(unsigned start, unsigned count, LockMode mode);
    //! Unlock buffer
    void unlock();
    //! Lock the morph vertex range. Throw an exception if no morph range or if locking fails
    void* lockMorphRange();
    //! Reset the morph vertex range. Needs to be locked first
    void resetMorphRange(void* lockedMorphRange);
    //! Clear data lost flag
    void clearDataLost();
    
    //! Return whether is dynamic
    bool isDynamic() const;
    //! Return whether default pool data lost
    bool isDataLost() const { return mDataLost; }
    //! Return number of vertices
    unsigned getVertexCount() const {return mVertexCount; }
    //! Return vertex size
    unsigned getVertexSize() const { return mVertexSize; }
    //! Return bitmask of vertex elements
    unsigned getElementMask() const { return mElementMask; }
    //! Return offset of a specified element within a vertex
    unsigned getElementOffset(VertexElement element) const { return mElementOffset[element]; }
    //! Return morph vertex range start
    unsigned getMorphRangeStart() const { return mMorphRangeStart; }
    //! Return number of vertices in the morph range
    unsigned getMorphRangeCount() const { return mMorphRangeCount; }
    //! Return morph vertex range reset data
    const SharedArrayPtr<unsigned char>& getMorphRangeResetData() { return mMorphRangeResetData; }
    //! Return whether has a morph vertex range defined
    bool hasMorphRange() const { return mMorphRangeCount > 0; }
    //! Return buffer hash for state sorting
    unsigned long long getHash(unsigned streamIndex, unsigned useMask);
    
    //! Return vertex size corresponding to a vertex element mask
    static unsigned getVertexSize(unsigned elementMask);
    
    //! Vertex element sizes
    static const unsigned sElementSize[];
    //! Vertex element names
    static const std::string sElementName[];
    
private:
    //! Update offsets of vertex elements
    void updateOffsets();
    //! Create buffer
    void create();
    //! Release buffer
    void release();
    
    //! Fallback data when operating with a null renderer
    SharedArrayPtr<unsigned char> mFallbackData;
    //! Morph vertex range reset data
    SharedArrayPtr<unsigned char> mMorphRangeResetData;
    //! Memory pool
    unsigned mPool;
    //! Usage type
    unsigned mUsage;
    //! Number of vertices
    unsigned mVertexCount;
    //! Vertex size
    unsigned mVertexSize;
    //! Vertex element bitmask
    unsigned mElementMask;
    //! Vertex element offsets
    unsigned mElementOffset[MAX_VERTEX_ELEMENTS];
    //! Morph vertex range start
    unsigned mMorphRangeStart;
    //! Number of vertices in the morph range
    unsigned mMorphRangeCount;
    //! Locked flag
    bool mLocked;
    //! Default pool data lost flag
    bool mDataLost;
};

#endif // RENDERER_VERTEXBUFFER_H
