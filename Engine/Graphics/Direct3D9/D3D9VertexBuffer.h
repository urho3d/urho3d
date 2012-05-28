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

#include "GPUObject.h"
#include "GraphicsDefs.h"
#include "ArrayPtr.h"

/// Hardware vertex buffer.
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
    
    /// Enable shadowing in CPU memory. Shadowing is forced on if the graphics subsystem does not exist.
    void SetShadowed(bool enable);
    /// %Set size and vertex elements and dynamic mode. Previous data will be lost.
    bool SetSize(unsigned vertexCount, unsigned elementMask, bool dynamic = false);
    /// %Set all data in the buffer.
    bool SetData(const void* data);
    /// %Set a data range in the buffer. Optionally discard data outside the range.
    bool SetDataRange(const void* data, unsigned start, unsigned count, bool discard = false);
    /// Update the shadow data to the GPU buffer. Call after manipulating shadow data directly, not necessary with SetData().
    bool UpdateToGPU();
    /// Clear data lost flag.
    void ClearDataLost();
    
    /// Return whether CPU memory shadowing is enabled.
    bool IsShadowed() const { return shadowed_; }
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
    /// Return buffer hash for building vertex declarations.
    unsigned long long GetBufferHash(unsigned streamIndex, unsigned useMask);
    /// Return CPU memory shadow data.
    unsigned char* GetShadowData() const { return shadowData_.Get(); }
    
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
    /// Lock buffer.
    void* Lock(unsigned start, unsigned count, bool discard);
    /// Unlock buffer.
    void Unlock();
    
    /// Shadow data.
    SharedArrayPtr<unsigned char> shadowData_;
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
    /// Shadowed flag.
    bool shadowed_;
    /// Default pool data lost flag.
    bool dataLost_;
};
