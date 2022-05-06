// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../../Container/HashMap.h"
#include "../../GraphicsAPI/ShaderVariation.h"

namespace Urho3D
{

/// Combined information for specific vertex and pixel shaders.
class ShaderProgram_D3D9 : public RefCounted
{
public:
    /// Construct.
    ShaderProgram_D3D9(ShaderVariation* vertexShader, ShaderVariation* pixelShader)
    {
        const HashMap<StringHash, ShaderParameter>& vsParams = vertexShader->GetParameters();
        for (HashMap<StringHash, ShaderParameter>::ConstIterator i = vsParams.Begin(); i != vsParams.End(); ++i)
            parameters_[i->first_] = i->second_;

        const HashMap<StringHash, ShaderParameter>& psParams = pixelShader->GetParameters();
        for (HashMap<StringHash, ShaderParameter>::ConstIterator i = psParams.Begin(); i != psParams.End(); ++i)
            parameters_[i->first_] = i->second_;

        // Optimize shader parameter lookup by rehashing to next power of two
        parameters_.Rehash(NextPowerOfTwo(parameters_.Size()));
    }

    /// Combined parameters from the vertex and pixel shader.
    HashMap<StringHash, ShaderParameter> parameters_;
};

}
