// Copyright (c) 2008-2023 the Urho3D project
// License: MIT

#pragma once

#include "../Container/ArrayPtr.h"
#include "../Core/Object.h"
#include "../GraphicsAPI/GPUObject.h"
#include "../GraphicsAPI/GraphicsDefs.h"

namespace Urho3D
{

/// Hardware index buffer.
class URHO3D_API IndexBuffer : public Object, public GPUObject
{
    URHO3D_OBJECT(IndexBuffer, Object);

public:
    /// Construct. Optionally force headless (no GPU-side buffer) operation.
    explicit IndexBuffer(Context* context, bool forceHeadless = false);
    /// Destruct.
    ~IndexBuffer() override;

    /// Mark the buffer destroyed on graphics context destruction. May be a no-op depending on the API.
    void OnDeviceLost() override;
    /// Recreate the buffer and restore data if applicable. May be a no-op depending on the API.
    void OnDeviceReset() override;
    /// Release buffer.
    void Release() override;

    /// Enable shadowing in CPU memory. Shadowing is forced on if the graphics subsystem does not exist.
    /// @property
    void SetShadowed(bool enable);
    /// Set size and vertex elements and dynamic mode. Previous data will be lost.
    bool SetSize(i32 indexCount, bool largeIndices, bool dynamic = false);
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

    /// Return number of indices.
    /// @property
    i32 GetIndexCount() const { return indexCount_; }

    /// Return index size in bytes.
    /// @property
    i32 GetIndexSize() const { return indexSize_; }

    /// Return used vertex range from index range.
    bool GetUsedVertexRange(i32 start, i32 count, i32& minVertex, i32& vertexCount);

    /// Return CPU memory shadow data.
    byte* GetShadowData() const { return shadowData_.Get(); }

    /// Return shared array pointer to the CPU memory shadow data.
    SharedArrayPtr<byte> GetShadowDataShared() const { return shadowData_; }

private:
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
    /// Number of indices.
    i32 indexCount_;
    /// Index size.
    i32 indexSize_;
    /// Buffer locking state.
    LockState lockState_;
    /// Lock start vertex.
    i32 lockStart_;
    /// Lock number of vertices.
    i32 lockCount_;
    /// Scratch buffer for fallback locking.
    void* lockScratchData_;
    /// Dynamic flag.
    bool dynamic_;
    /// Shadowed flag.
    bool shadowed_;
    /// Discard lock flag. Used by OpenGL only.
    bool discardLock_;
};

}
