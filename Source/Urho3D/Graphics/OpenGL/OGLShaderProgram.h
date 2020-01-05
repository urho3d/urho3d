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
#include "../../Container/RefCounted.h"
#include "../../Graphics/GPUObject.h"
#include "../../Graphics/GraphicsDefs.h"
#include "../../Graphics/ShaderVariation.h"

namespace Urho3D
{

class ConstantBuffer;
class Graphics;

/// Linked shader program on the GPU.
class URHO3D_API ShaderProgram : public RefCounted, public GPUObject
{
public:
    /// Construct.
    ShaderProgram(Graphics* graphics, ShaderVariation* vertexShader, ShaderVariation* pixelShader);
    /// Destruct.
    ~ShaderProgram() override;

    /// Mark the GPU resource destroyed on context destruction.
    void OnDeviceLost() override;
    /// Release shader program.
    void Release() override;

    /// Link the shaders and examine the uniforms and samplers used. Return true if successful.
    bool Link();

    /// Return the vertex shader.
    ShaderVariation* GetVertexShader() const;
    /// Return the pixel shader.
    ShaderVariation* GetPixelShader() const;
    /// Return whether uses a shader parameter.
    bool HasParameter(StringHash param) const;

    /// Return whether uses a texture unit.
    bool HasTextureUnit(TextureUnit unit) const { return useTextureUnits_[unit]; }

    /// Return the info for a shader parameter, or null if does not exist.
    const ShaderParameter* GetParameter(StringHash param) const;

    /// Return linker output.
    const String& GetLinkerOutput() const { return linkerOutput_; }

    /// Return semantic to vertex attributes location mappings used by the shader.
    const HashMap<Pair<unsigned char, unsigned char>, unsigned>& GetVertexAttributes() const { return vertexAttributes_; }

    /// Return attribute location use bitmask.
    unsigned GetUsedVertexAttributes() const { return usedVertexAttributes_; }

    /// Return all constant buffers.
    const SharedPtr<ConstantBuffer>* GetConstantBuffers() const { return &constantBuffers_[0]; }

    /// Check whether a shader parameter group needs update. Does not actually check whether parameters exist in the shaders.
    bool NeedParameterUpdate(ShaderParameterGroup group, const void* source);
    /// Clear a parameter source. Affects only the current shader program if appropriate.
    void ClearParameterSource(ShaderParameterGroup group);

    /// Clear all parameter sources from all shader programs by incrementing the global parameter source framenumber.
    static void ClearParameterSources();
    /// Clear a global parameter source when constant buffers change.
    static void ClearGlobalParameterSource(ShaderParameterGroup group);

private:
    /// Vertex shader.
    WeakPtr<ShaderVariation> vertexShader_;
    /// Pixel shader.
    WeakPtr<ShaderVariation> pixelShader_;
    /// Shader parameters.
    HashMap<StringHash, ShaderParameter> shaderParameters_;
    /// Texture unit use.
    bool useTextureUnits_[MAX_TEXTURE_UNITS]{};
    /// Vertex attributes.
    HashMap<Pair<unsigned char, unsigned char>, unsigned> vertexAttributes_;
    /// Used vertex attribute location bitmask.
    unsigned usedVertexAttributes_{};
    /// Constant buffers by binding index.
    SharedPtr<ConstantBuffer> constantBuffers_[MAX_SHADER_PARAMETER_GROUPS * 2];
    /// Remembered shader parameter sources for individual uniform mode.
    const void* parameterSources_[MAX_SHADER_PARAMETER_GROUPS]{};
    /// Shader link error string.
    String linkerOutput_;
    /// Shader parameter source framenumber.
    unsigned frameNumber_{};

    /// Global shader parameter source framenumber.
    static unsigned globalFrameNumber;
    /// Remembered global shader parameter sources for constant buffer mode.
    static const void* globalParameterSources[MAX_SHADER_PARAMETER_GROUPS];
};

}
