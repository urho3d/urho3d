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

#include "../../Container/HashSet.h"
#include "../../Container/RefCounted.h"
#include "../../Container/ArrayPtr.h"
#include "../../Graphics/GPUObject.h"
#include "../../Graphics/GraphicsDefs.h"

namespace Urho3D
{

class ConstantBuffer;
class Shader;

/// %Shader parameter definition.
struct ShaderParameter
{
    /// Construct with defaults.
    ShaderParameter() :
        type_(VS),
        buffer_(0),
        offset_(0),
        size_(0),
        bufferPtr_(0)
    {
    }

    /// Construct with parameters.
    ShaderParameter(ShaderType type, const String& name, unsigned buffer, unsigned offset, unsigned size, ConstantBuffer* ptr = 0) :
        type_(type),
        name_(name),
        buffer_(buffer),
        offset_(offset),
        size_(size),
        bufferPtr_(ptr)
    {
    }

    /// %Shader type.
    ShaderType type_;
    /// Name of the parameter.
    String name_;
    /// Constant buffer index.
    unsigned buffer_;
    /// Offset in constant buffer.
    unsigned offset_;
    /// Size of parameter in bytes.
    unsigned size_;
    /// Constant buffer pointer. Defined only in shader programs.
    ConstantBuffer* bufferPtr_;
};

/// Vertex or pixel shader on the GPU.
class URHO3D_API ShaderVariation : public RefCounted, public GPUObject
{
public:
    /// Construct.
    ShaderVariation(Shader* owner, ShaderType type);
    /// Destruct.
    virtual ~ShaderVariation();

    /// Release the shader.
    virtual void Release();

    /// Compile the shader. Return true if successful.
    bool Create();
    /// Set name.
    void SetName(const String& name);
    /// Set defines.
    void SetDefines(const String& defines);

    /// Return the owner resource.
    Shader* GetOwner() const;

    /// Return shader type.
    ShaderType GetShaderType() const { return type_; }

    /// Return shader name.
    const String& GetName() const { return name_; }

    /// Return full shader name.
    String GetFullName() const { return name_ + "(" + defines_ + ")"; }

    /// Return whether uses a parameter.
    bool HasParameter(StringHash param) const { return parameters_.Contains(param); }

    /// Return whether uses a texture unit (only for pixel shaders.)
    bool HasTextureUnit(TextureUnit unit) const { return useTextureUnit_[unit]; }

    /// Return all parameter definitions.
    const HashMap<StringHash, ShaderParameter>& GetParameters() const { return parameters_; }

    /// Return vertex element hash.
    unsigned long long GetElementHash() const { return elementHash_; }

    /// Return shader bytecode.
    const PODVector<unsigned char>& GetByteCode() const { return byteCode_; }

    /// Return defines.
    const String& GetDefines() const { return defines_; }

    /// Return compile error/warning string.
    const String& GetCompilerOutput() const { return compilerOutput_; }

    /// Return constant buffer data sizes.
    const unsigned* GetConstantBufferSizes() const { return &constantBufferSizes_[0]; }

    /// Return defines with the CLIPPLANE define appended. Used internally on D3D11 only.
    const String& GetDefinesClipPlane() { return definesClipPlane_; }

    /// D3D11 vertex semantic names. Used internally.
    static const char* elementSemanticNames[];

private:
    /// Load bytecode from a file. Return true if successful.
    bool LoadByteCode(const String& binaryShaderName);
    /// Compile from source. Return true if successful.
    bool Compile();
    /// Inspect the constant parameters and input layout (if applicable) from the shader bytecode.
    void ParseParameters(unsigned char* bufData, unsigned bufSize);
    /// Save bytecode to a file.
    void SaveByteCode(const String& binaryShaderName);
    /// Calculate constant buffer sizes from parameters.
    void CalculateConstantBufferSizes();

    /// Shader this variation belongs to.
    WeakPtr<Shader> owner_;
    /// Shader type.
    ShaderType type_;
    /// Vertex element hash for vertex shaders. Zero for pixel shaders. Note that hashing is different than vertex buffers.
    unsigned long long elementHash_;
    /// Shader parameters.
    HashMap<StringHash, ShaderParameter> parameters_;
    /// Texture unit use flags.
    bool useTextureUnit_[MAX_TEXTURE_UNITS];
    /// Constant buffer sizes. 0 if a constant buffer slot is not in use.
    unsigned constantBufferSizes_[MAX_SHADER_PARAMETER_GROUPS];
    /// Bytecode. Needed for inspecting the input signature and parameters.
    PODVector<unsigned char> byteCode_;
    /// Shader name.
    String name_;
    /// Defines to use in compiling.
    String defines_;
    /// Defines to use in compiling + CLIPPLANE define appended.
    String definesClipPlane_;
    /// Shader compile error string.
    String compilerOutput_;
};

}
