//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../../Container/ArrayPtr.h"
#include "../../Graphics/GPUObject.h"
#include "../../Graphics/GraphicsDefs.h"

namespace Urho3D
{

/// Hardware vertex buffer.
class URHO3D_API VertexBuffer : public Object, public GPUObject
{
    URHO3D_OBJECT(VertexBuffer, Object);

public:
    /// Construct.
    VertexBuffer(Context* context, bool forceHeadless = false);
    /// Destruct.
    virtual ~VertexBuffer();

    /// Recreate the GPU resource and restore data if applicable.
    virtual void OnDeviceReset();
    /// Release the buffer.
    virtual void Release();

    /// Enable shadowing in CPU memory. Shadowing is forced on if the graphics subsystem does not exist.
    void SetShadowed(bool enable);
    /// Set size, vertex elements and dynamic mode. Previous data will be lost.
    bool SetSize(unsigned vertexCount, const PODVector<VertexElement>& elements, bool dynamic = false);
    /// Set size and vertex elements and dynamic mode using legacy element bitmask. Previous data will be lost.
    bool SetSize(unsigned vertexCount, unsigned elementMask, bool dynamic = false);
    /// Set all data in the buffer.
    bool SetData(const void* data);
    /// Set a data range in the buffer. Optionally discard data outside the range.
    bool SetDataRange(const void* data, unsigned start, unsigned count, bool discard = false);
    /// Lock the buffer for write-only editing. Return data pointer if successful. Optionally discard data outside the range.
    void* Lock(unsigned start, unsigned count, bool discard = false);
    /// Unlock the buffer and apply changes to the GPU buffer.
    void Unlock();

    /// Return whether CPU memory shadowing is enabled.
    bool IsShadowed() const { return shadowed_; }

    /// Return whether is dynamic.
    bool IsDynamic() const { return dynamic_; }

    /// Return whether is currently locked.
    bool IsLocked() const { return lockState_ != LOCK_NONE; }

    /// Return number of vertices.
    unsigned GetVertexCount() const { return vertexCount_; }

    /// Return vertex size in bytes.
    unsigned GetVertexSize() const { return vertexSize_; }

    /// Return vertex elements.
    const PODVector<VertexElement>& GetElements() const { return elements_; }

    /// Return vertex element, or null if does not exist.
    const VertexElement* GetElement(VertexElementSemantic semantic, unsigned char index = 0) const;

    /// Return vertex element with specific type, or null if does not exist.
    const VertexElement* GetElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index = 0) const;

    /// Return whether has a specified element semantic.
    bool HasElement(VertexElementSemantic semantic, unsigned char index = 0) const { return GetElement(semantic, index) != 0; }

    /// Return whether has an element semantic with specific type.
    bool HasElement(VertexElementType type, VertexElementSemantic semantic, unsigned char index = 0) const { return GetElement(type, semantic, index) != 0; }

    /// Return offset of a element within vertex, or M_MAX_UNSIGNED if does not exist.
    unsigned GetElementOffset(VertexElementSemantic semantic, unsigned char index = 0) const { const VertexElement* element = GetElement(semantic, index); return element ? element->offset_ : M_MAX_UNSIGNED; }

    /// Return offset of a element with specific type within vertex, or M_MAX_UNSIGNED if element does not exist.
    unsigned GetElementOffset(VertexElementType type, VertexElementSemantic semantic, unsigned char index = 0) const { const VertexElement* element = GetElement(type, semantic, index); return element ? element->offset_ : M_MAX_UNSIGNED; }

    /// Return legacy vertex element mask. Note that both semantic and type must match the legacy element for a mask bit to be set.
    unsigned GetElementMask() const { return elementMask_; }

    /// Return CPU memory shadow data.
    unsigned char* GetShadowData() const { return shadowData_.Get(); }

    /// Return shared array pointer to the CPU memory shadow data.
    SharedArrayPtr<unsigned char> GetShadowDataShared() const { return shadowData_; }

    /// Return buffer hash for building vertex declarations. Used internally.
    unsigned long long GetBufferHash(unsigned streamIndex) { return elementHash_ << (streamIndex * 16); }

    /// Return element with specified type and semantic from a vertex element list, or null if does not exist.
    static const VertexElement* GetElement(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index = 0);

    /// Return whether element list has a specified element type and semantic.
    static bool HasElement(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index = 0);

    /// Return element offset for specified type and semantic from a vertex element list, or M_MAX_UNSIGNED if does not exist.
    static unsigned GetElementOffset(const PODVector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, unsigned char index = 0);

    /// Return a vertex element list from a legacy element bitmask.
    static PODVector<VertexElement> GetElements(unsigned elementMask);

    /// Return vertex size from an element list.
    static unsigned GetVertexSize(const PODVector<VertexElement>& elements);

    /// Return vertex size for a legacy vertex element bitmask.
    static unsigned GetVertexSize(unsigned elementMask);

private:
    /// Update offsets of vertex elements.
    void UpdateOffsets();
    /// Create buffer.
    bool Create();
    /// Update the shadow data to the GPU buffer.
    bool UpdateToGPU();

    /// Shadow data.
    SharedArrayPtr<unsigned char> shadowData_;
    /// Number of vertices.
    unsigned vertexCount_;
    /// Vertex size.
    unsigned vertexSize_;
    /// Vertex elements.
    PODVector<VertexElement> elements_;
    /// Vertex element hash.
    unsigned long long elementHash_;
    /// Vertex element legacy bitmask.
    unsigned elementMask_;
    /// Buffer locking state.
    LockState lockState_;
    /// Lock start vertex.
    unsigned lockStart_;
    /// Lock number of vertices.
    unsigned lockCount_;
    /// Scratch buffer for fallback locking.
    void* lockScratchData_;
    /// Shadowed flag.
    bool shadowed_;
    /// Dynamic flag.
    bool dynamic_;
};

}
