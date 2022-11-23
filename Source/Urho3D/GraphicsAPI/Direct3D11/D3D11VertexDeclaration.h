// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../../Container/RefCounted.h"
#include "../../Container/Vector.h"
#include "../../GraphicsAPI/GraphicsDefs.h"

namespace Urho3D
{

class Graphics;
class ShaderVariation;
class VertexBuffer;

/// Vertex declaration.
class URHO3D_API VertexDeclaration_D3D11 : public RefCounted
{
public:
    /// Construct with vertex buffers and element masks to base declaration on.
    VertexDeclaration_D3D11(Graphics* graphics, ShaderVariation* vertexShader, VertexBuffer** buffers);
    /// Destruct.
    virtual ~VertexDeclaration_D3D11() override;

    /// Return input layout object corresponding to the declaration.
    void* GetInputLayout() const { return inputLayout_; }

private:
    /// Input layout object.
    void* inputLayout_;
};

}
