// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../../Container/HashMap.h"
#include "../../Graphics/Graphics.h"
#include "../../GraphicsAPI/ConstantBuffer.h"
#include "../../GraphicsAPI/ShaderVariation.h"

namespace Urho3D
{

/// Combined information for specific vertex and pixel shaders.
class URHO3D_API ShaderProgram_D3D11 : public RefCounted
{
public:
    /// Construct.
    ShaderProgram_D3D11(Graphics* graphics, ShaderVariation* vertexShader, ShaderVariation* pixelShader)
    {
        // Create needed constant buffers
        const unsigned* vsBufferSizes = vertexShader->GetConstantBufferSizes();
        for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
        {
            if (vsBufferSizes[i])
                vsConstantBuffers_[i] = graphics->GetOrCreateConstantBuffer(VS, i, vsBufferSizes[i]);
        }

        const unsigned* psBufferSizes = pixelShader->GetConstantBufferSizes();
        for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
        {
            if (psBufferSizes[i])
                psConstantBuffers_[i] = graphics->GetOrCreateConstantBuffer(PS, i, psBufferSizes[i]);
        }

        // Copy parameters, add direct links to constant buffers
        const HashMap<StringHash, ShaderParameter>& vsParams = vertexShader->GetParameters();
        for (HashMap<StringHash, ShaderParameter>::ConstIterator i = vsParams.Begin(); i != vsParams.End(); ++i)
        {
            parameters_[i->first_] = i->second_;
            parameters_[i->first_].bufferPtr_ = vsConstantBuffers_[i->second_.buffer_].Get();
        }

        const HashMap<StringHash, ShaderParameter>& psParams = pixelShader->GetParameters();
        for (HashMap<StringHash, ShaderParameter>::ConstIterator i = psParams.Begin(); i != psParams.End(); ++i)
        {
            parameters_[i->first_] = i->second_;
            parameters_[i->first_].bufferPtr_ = psConstantBuffers_[i->second_.buffer_].Get();
        }

        // Optimize shader parameter lookup by rehashing to next power of two
        parameters_.Rehash(NextPowerOfTwo(parameters_.Size()));

    }

    /// Destruct.
    virtual ~ShaderProgram_D3D11() override
    {
    }

    /// Combined parameters from the vertex and pixel shader.
    HashMap<StringHash, ShaderParameter> parameters_;
    /// Vertex shader constant buffers.
    SharedPtr<ConstantBuffer> vsConstantBuffers_[MAX_SHADER_PARAMETER_GROUPS];
    /// Pixel shader constant buffers.
    SharedPtr<ConstantBuffer> psConstantBuffers_[MAX_SHADER_PARAMETER_GROUPS];
};

}
