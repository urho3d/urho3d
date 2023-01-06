// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include "../Container/ArrayPtr.h"
#include "../Core/Object.h"
#include "../GraphicsAPI/GPUObject.h"
#include "../GraphicsAPI/GraphicsDefs.h"

namespace Urho3D
{

/// Hardware vertex buffer.
class URHO3D_API VertexBuffer : public Object, public GPUObject
{
    URHO3D_OBJECT(VertexBuffer, Object);

public:
    /// Construct. Optionally force headless (no GPU-side buffer) operation.
    explicit VertexBuffer(Context* context, bool forceHeadless = false);
    /// Destruct.
    ~VertexBuffer() override;

    /// Mark the buffer destroyed on graphics context destruction. May be a no-op depending on the API.
    void OnDeviceLost() override;
    /// Recreate the buffer and restore data if applicable. May be a no-op depending on the API.
    void OnDeviceReset() override;
    /// Release buffer.
    void Release() override;

    /// Enable shadowing in CPU memory. Shadowing is forced on if the graphics subsystem does not exist.
    /// @property
    void SetShadowed(bool enable);
    /// Set size, vertex elements and dynamic mode. Previous data will be lost.
    bool SetSize(i32 vertexCount, const Vector<VertexElement>& elements, bool dynamic = false);
    /// Set size and vertex elements and dynamic mode using legacy element bitmask. Previous data will be lost.
    bool SetSize(i32 vertexCount, VertexElements elementMask, bool dynamic = false);
    /// Set all data in the buffer.
    bool SetData(const void* data);
    /// Set a data range in the buffer. Optionally discard data outside the range.
    bool SetDataRange(const void* data, i32 start, i32 count, bool discard = false);
    /// Lock the buffer for write-only editing. Return data pointer if successful. Optionally discard data outside the range.
    void* Lock(i32 start, i32 count, bool discard = false);
    /// Unlock the buffer and apply changes to the GPU buffer.
    void Unlock();

    /// Return whether CPU memory shadowing is enabled.
    /// @property
    bool IsShadowed() const { return shadowed_; }

    /// Return whether is dynamic.
    /// @property
    bool IsDynamic() const { return dynamic_; }

    /// Return whether is currently locked.
    bool IsLocked() const { return lockState_ != LOCK_NONE; }

    /// Return number of vertices.
    /// @property
    i32 GetVertexCount() const { return vertexCount_; }

    /// Return vertex size in bytes.
    /// @property
    i32 GetVertexSize() const { return vertexSize_; }

    /// Return vertex elements.
    /// @property
    const Vector<VertexElement>& GetElements() const { return elements_; }

    /// Return vertex element, or null if does not exist.
    const VertexElement* GetElement(VertexElementSemantic semantic, i8 index = 0) const;

    /// Return vertex element with specific type, or null if does not exist.
    const VertexElement* GetElement(VertexElementType type, VertexElementSemantic semantic, i8 index = 0) const;

    /// Return whether has a specified element semantic.
    bool HasElement(VertexElementSemantic semantic, i8 index = 0) const
    {
        assert(index >= 0);
        return GetElement(semantic, index) != nullptr;
    }

    /// Return whether has an element semantic with specific type.
    bool HasElement(VertexElementType type, VertexElementSemantic semantic, i8 index = 0) const
    {
        assert(index >= 0);
        return GetElement(type, semantic, index) != nullptr;
    }

    /// Return offset of a element within vertex, or NINDEX if does not exist.
    i32 GetElementOffset(VertexElementSemantic semantic, i8 index = 0) const
    {
        assert(index >= 0);
        const VertexElement* element = GetElement(semantic, index);
        return element ? element->offset_ : NINDEX;
    }

    /// Return offset of a element with specific type within vertex, or NINDEX if element does not exist.
    i32 GetElementOffset(VertexElementType type, VertexElementSemantic semantic, i8 index = 0) const
    {
        assert(index >= 0);
        const VertexElement* element = GetElement(type, semantic, index);
        return element ? element->offset_ : NINDEX;
    }

    /// Return legacy vertex element mask. Note that both semantic and type must match the legacy element for a mask bit to be set.
    /// @property
    VertexElements GetElementMask() const { return elementMask_; }

    /// Return CPU memory shadow data.
    byte* GetShadowData() const { return shadowData_.Get(); }

    /// Return shared array pointer to the CPU memory shadow data.
    SharedArrayPtr<byte> GetShadowDataShared() const { return shadowData_; }

    /// Return buffer hash for building vertex declarations. Used internally.
    hash64 GetBufferHash(i32 streamIndex) { return elementHash_ << (streamIndex * 16); }

    /// Return element with specified type and semantic from a vertex element list, or null if does not exist.
    static const VertexElement* GetElement(const Vector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, i8 index = 0);

    /// Return whether element list has a specified element type and semantic.
    static bool HasElement(const Vector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, i8 index = 0);

    /// Return element offset for specified type and semantic from a vertex element list, or NINDEX if does not exist.
    static i32 GetElementOffset(const Vector<VertexElement>& elements, VertexElementType type, VertexElementSemantic semantic, i8 index = 0);

    /// Return a vertex element list from a legacy element bitmask.
    static Vector<VertexElement> GetElements(VertexElements elementMask);

    /// Return vertex size from an element list.
    static i32 GetVertexSize(const Vector<VertexElement>& elements);

    /// Return vertex size for a legacy vertex element bitmask.
    static i32 GetVertexSize(VertexElements elementMask);

    /// Update offsets of vertex elements.
    static void UpdateOffsets(Vector<VertexElement>& elements);

private:
    /// Update offsets of vertex elements.
    void UpdateOffsets();
    /// Create buffer.
    bool Create();
    /// Update the shadow data to the GPU buffer.
    bool UpdateToGPU();
    /// Map the GPU buffer into CPU memory. Not used on OpenGL.
    void* MapBuffer(i32 start, i32 count, bool discard);
    /// Unmap the GPU buffer. Not used on OpenGL.
    void UnmapBuffer();

#ifdef URHO3D_OPENGL
    void OnDeviceLost_OGL();
    void OnDeviceReset_OGL();
    void Release_OGL();
    bool SetData_OGL(const void* data);
    bool SetDataRange_OGL(const void* data, i32 start, i32 count, bool discard = false);
    void* Lock_OGL(i32 start, i32 count, bool discard);
    void Unlock_OGL();
    bool Create_OGL();
    bool UpdateToGPU_OGL();
    void* MapBuffer_OGL(i32 start, i32 count, bool discard);
    void UnmapBuffer_OGL();
#endif // def URHO3D_OPENGL

#ifdef URHO3D_D3D11
    void OnDeviceLost_D3D11();
    void OnDeviceReset_D3D11();
    void Release_D3D11();
    bool SetData_D3D11(const void* data);
    bool SetDataRange_D3D11(const void* data, i32 start, i32 count, bool discard = false);
    void* Lock_D3D11(i32 start, i32 count, bool discard);
    void Unlock_D3D11();
    bool Create_D3D11();
    bool UpdateToGPU_D3D11();
    void* MapBuffer_D3D11(i32 start, i32 count, bool discard);
    void UnmapBuffer_D3D11();
#endif // def URHO3D_D3D11

    /// Shadow data.
    SharedArrayPtr<byte> shadowData_;
    /// Number of vertices.
    i32 vertexCount_{};
    /// Vertex size.
    i32 vertexSize_{};
    /// Vertex elements.
    Vector<VertexElement> elements_;
    /// Vertex element hash.
    hash64 elementHash_{};
    /// Vertex element legacy bitmask.
    VertexElements elementMask_{};
    /// Buffer locking state.
    LockState lockState_{LOCK_NONE};
    /// Lock start vertex.
    i32 lockStart_{};
    /// Lock number of vertices.
    i32 lockCount_{};
    /// Scratch buffer for fallback locking.
    void* lockScratchData_{};
    /// Dynamic flag.
    bool dynamic_{};
    /// Shadowed flag.
    bool shadowed_{};
    /// Discard lock flag. Used by OpenGL only.
    bool discardLock_{};
};

}
