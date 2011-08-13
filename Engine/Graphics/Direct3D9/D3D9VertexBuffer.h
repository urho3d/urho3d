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
#include "GraphicsDefs.h"
#include "ArrayPtr.h"

/// Hardware vertex buffer
class VertexBuffer : public Object, public GPUObject
{
    OBJECT(VertexBuffer);
    
public:
    /// Construct.
    VertexBuffer(Context* context);
    /// Destruct.
    virtual ~VertexBuffer();
    
    /// Release default pool resources.
    virtual void OnDeviceLost();
    /// ReCreate default pool resources.
    virtual void OnDeviceReset();
    /// Release buffer.
    virtual void Release();
    
    /// %Set size and vertex elements and dynamic mode. Previous data will be lost.
    bool SetSize(unsigned vertexCount, unsigned elementMask, bool dynamic = false);
    /// %Set all data in the buffer.
    bool SetData(const void* data);
    /// %Set a data range in the buffer.
    bool SetDataRange(const void* data, unsigned first, unsigned count);
    /// %Set the vertex range to use for morphing.
    bool SetMorphRange(unsigned start, unsigned count);
    /// %Set data to be used for resetting the morph vertex range.
    void SetMorphRangeResetData(const SharedArrayPtr<unsigned char>& data);
    /// Lock a data range in the buffer. Return pointer to locked data if successful.
    void* Lock(unsigned start, unsigned count, LockMode mode);
    /// Unlock buffer.
    void Unlock();
    /// Lock the morph vertex range. Return pointer to locked data if successful.
    void* LockMorphRange();
    /// Reset the morph vertex range. Needs to be locked first.
    void ResetMorphRange(void* lockedMorphRange);
    /// Clear data lost flag.
    void ClearDataLost();
    
    /// Return whether is dynamic.
    bool IsDynamic() const;
    /// Return whether default pool data lost.
    bool IsDataLost() const { return dataLost_; }
    /// Return number of vertices.
    unsigned GetVertexCount() const {return vertexCount_; }
    /// Return vertex size.
    unsigned GetVertexSize() const { return vertexSize_; }
    /// Return bitmask of vertex elements.
    unsigned GetElementMask() const { return elementMask_; }
    /// Return offset of a specified element within a vertex.
    unsigned GetElementOffset(VertexElement element) const { return elementOffset_[element]; }
    /// Return morph vertex range start.
    unsigned GetMorphRangeStart() const { return morphRangeStart_; }
    /// Return number of vertices in the morph range.
    unsigned GetMorphRangeCount() const { return morphRangeCount_; }
    /// Return morph vertex range reset data.
    const SharedArrayPtr<unsigned char>& GetMorphRangeResetData() { return morphRangeResetData_; }
    /// Return whether has a morph vertex range defined.
    bool HasMorphRange() const { return morphRangeCount_ > 0; }
    /// Return buffer hash for state sorting.
    unsigned long long GetHash(unsigned streaindex_, unsigned useMask);
    
    /// Return vertex size corresponding to a vertex element mask.
    static unsigned GetVertexSize(unsigned elementMask);
    
    /// Vertex element sizes.
    static const unsigned elementSize[];
    /// Vertex element names.
    static const String elementName[];
    
private:
    /// Update offsets of vertex elements.
    void UpdateOffsets();
    /// Create buffer.
    bool Create();
    
    /// Morph vertex range reset data.
    SharedArrayPtr<unsigned char> morphRangeResetData_;
    /// Memory pool.
    unsigned pool_;
    /// Usage type.
    unsigned usage_;
    /// Number of vertices.
    unsigned vertexCount_;
    /// Vertex size.
    unsigned vertexSize_;
    /// Vertex element bitmask.
    unsigned elementMask_;
    /// Vertex element offsets.
    unsigned elementOffset_[MAX_VERTEX_ELEMENTS];
    /// Morph vertex range start.
    unsigned morphRangeStart_;
    /// Number of vertices in the morph range.
    unsigned morphRangeCount_;
    /// Locked flag.
    bool locked_;
    /// Default pool data lost flag.
    bool dataLost_;
};
