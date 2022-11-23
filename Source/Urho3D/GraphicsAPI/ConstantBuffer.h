// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Container/ArrayPtr.h"
#include "../Core/Object.h"
#include "../GraphicsAPI/GPUObject.h"
#include "../GraphicsAPI/GraphicsDefs.h"

namespace Urho3D
{

/// Hardware constant buffer.
class URHO3D_API ConstantBuffer : public Object, public GPUObject
{
    URHO3D_OBJECT(ConstantBuffer, Object);

public:
    /// Construct.
    explicit ConstantBuffer(Context* context);
    /// Destruct.
    ~ConstantBuffer() override;

    /// Recreate the GPU resource and restore data if applicable.
    void OnDeviceReset() override;
    /// Release the buffer.
    void Release() override;

    /// Set size and create GPU-side buffer. Return true on success.
    bool SetSize(unsigned size);
    /// Set a generic parameter and mark buffer dirty.
    void SetParameter(unsigned offset, unsigned size, const void* data);
    /// Set a Vector3 array parameter and mark buffer dirty.
    void SetVector3ArrayParameter(unsigned offset, unsigned rows, const void* data);
    /// Apply to GPU.
    void Apply();

    /// Return size.
    unsigned GetSize() const { return size_; }

    /// Return whether has unapplied data.
    bool IsDirty() const { return dirty_; }

private:
#ifdef URHO3D_OPENGL
    void Release_OGL();
    void OnDeviceReset_OGL();
    bool SetSize_OGL(unsigned size);
    void Apply_OGL();
#endif // def URHO3D_OPENGL

#ifdef URHO3D_D3D9
    void Release_D3D9();
    void OnDeviceReset_D3D9();
    bool SetSize_D3D9(unsigned size);
    void Apply_D3D9();
#endif // def URHO3D_D3D9

#ifdef URHO3D_D3D11
    void Release_D3D11();
    void OnDeviceReset_D3D11();
    bool SetSize_D3D11(unsigned size);
    void Apply_D3D11();
#endif // def URHO3D_D3D11

    /// Shadow data.
    SharedArrayPtr<unsigned char> shadowData_;
    /// Buffer byte size.
    unsigned size_{};
    /// Dirty flag.
    bool dirty_{};
};

}
