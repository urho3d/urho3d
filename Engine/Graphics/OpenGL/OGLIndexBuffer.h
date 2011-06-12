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

#include "GPUObject.h"
#include "Object.h"
#include "GraphicsDefs.h"
#include "SharedArrayPtr.h"

/// Hardware index buffer
class IndexBuffer : public Object, public GPUObject
{
    OBJECT(IndexBuffer);
    
public:
    /// Construct
    IndexBuffer(Context* context);
    /// Destruct
    virtual ~IndexBuffer();
    
    /// Release buffer
    virtual void Release();
    
    /// Set buffer size and dynamic mode. Previous data will be lost
    bool SetSize(unsigned indexCount, bool largeIndices, bool dynamic = false);
    /// Set buffer size and dynamic mode. Previous data will be lost
    bool SetSize(unsigned indexCount, unsigned indexSize, bool dynamic = false);
    /// Set all data in the buffer
    bool SetData(const void* data);
    /// Set all data while resizing the buffer. Index size is not changed. OpenGL-only function for immediate draw optimization
    bool SetData(const void* data, unsigned vertexCount);
    /// Set a data range in the buffer
    bool SetDataRange(const void* data, unsigned start, unsigned count);
    /// Lock a data range in the buffer. Return pointer to locked data if successful
    void* Lock(unsigned start, unsigned count, LockMode mode);
    /// Unlock buffer
    void Unlock();
    /// Clear data lost flag. No-op on OpenGL
    void ClearDataLost() {}
    
    /// Return whether is dynamic
    bool IsDynamic() const { return dynamic_; }
    /// Return whether data is lost. Always false on OpenGL
    bool IsDataLost() const { return false; }
    /// Return number of indices
    unsigned GetIndexCount() const {return indexCount_; }
    /// Return index size
    unsigned GetIndexSize() const { return indexSize_; }
    /// Return used vertex range from index range
    bool GetUsedVertexRange(unsigned start, unsigned count, unsigned& minVertex, unsigned& vertexCount);
    
private:
    /// Create buffer
    bool Create();
    
    /// Fallback data when operating with a null graphics subsystem
    SharedArrayPtr<unsigned char> fallbackData_;
    /// Number of indices
    unsigned indexCount_;
    /// Index size
    unsigned indexSize_;
    /// Dynamic flag
    bool dynamic_;
    /// Buffer locked flag
    bool locked_;
};
