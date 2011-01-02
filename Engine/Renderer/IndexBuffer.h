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

#ifndef RENDERER_INDEXBUFFER_H
#define RENDERER_INDEXBUFFER_H

#include "GPUObject.h"
#include "RendererDefs.h"
#include "SharedArrayPtr.h"

//! A hardware index buffer
class IndexBuffer : public RefCounted, public GPUObject
{
public:
    //! Construct with renderer subsystem pointer and whether is dynamic or not
    IndexBuffer(Renderer* renderer, bool dynamic = false);
    //! Destruct
    virtual ~IndexBuffer();
    
    //! Release default pool resources
    virtual void onDeviceLost();
    //! Recreate default pool resources
    virtual void onDeviceReset();
    
    //! Set buffer size
    void setSize(unsigned indexCount, bool largeIndices);
    //! Set buffer size
    void setSize(unsigned indexCount, unsigned indexSize);
    //! Set all data in the buffer
    void setData(const void* data);
    //! Set a data range in the buffer
    void setDataRange(const void* data, unsigned start, unsigned count);
    //! Lock a data range in the buffer. Throw an exception if fails
    void* lock(unsigned start, unsigned count, LockMode mode);
    //! Unlock buffer
    void unlock();
    //! Clear data lost flag
    void clearDataLost();
    
    //! Return whether is dynamic
    bool isDynamic() const;
    //! Return whether default pool data lost
    bool isDataLost() const { return mDataLost; }
    //! Return number of indices
    unsigned getIndexCount() const {return mIndexCount; }
    //! Return index size
    unsigned getIndexSize() const { return mIndexSize; }
    //! Return used vertex range from index range
    bool getUsedVertexRange(unsigned start, unsigned count, unsigned& minVertex, unsigned& vertexCount);
    
private:
    //! Create buffer
    void create();
    //! Release buffer
    void release();
    
    //! Fallback data when operating with a null renderer
    SharedArrayPtr<unsigned char> mFallbackData;
    //! Memory pool
    unsigned mPool;
    //! Usage type
    unsigned mUsage;
    //! Number of indices
    unsigned mIndexCount;
    //! Index size
    unsigned mIndexSize;
    //! Buffer locked flag
    bool mLocked;
    //! Default pool data lost flag
    bool mDataLost;
};

#endif // RENDERER_INDEXBUFFER_H
