//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../../Container/HashMap.h"
#include "../../Graphics/ShaderVariation.h"

namespace Urho3D
{

/// Combined information for specific vertex and pixel shaders.
class ShaderProgram : public RefCounted
{
public:
    /// Construct.
    ShaderProgram(ShaderVariation* vertexShader, ShaderVariation* pixelShader)
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
