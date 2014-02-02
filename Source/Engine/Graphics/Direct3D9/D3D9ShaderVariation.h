//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "GPUObject.h"
#include "GraphicsDefs.h"
#include "HashSet.h"
#include "RefCounted.h"
#include "ArrayPtr.h"

namespace Urho3D
{

class Shader;

/// %Shader parameter definition.
struct ShaderParameter
{
    /// Construct with defaults.
    ShaderParameter() :
        type_(VS),
        register_(M_MAX_UNSIGNED),
        regCount_(0)
    {
    }
    
    /// Construct with parameters.
    ShaderParameter(ShaderType type, unsigned reg, unsigned regCount) :
        type_(type),
        register_(reg),
        regCount_(regCount)
    {
    }
    
    /// %Shader type.
    ShaderType type_;
    /// Hardware register.
    unsigned register_;
    /// Number of registers.
    unsigned regCount_;
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
    
    /// Return shader type.
    ShaderType GetShaderType() const { return type_; }
    /// Return full shader name.
    const String& GetName() const { return name_; }
    /// Return defines.
    const String& GetDefines() const { return defines_; }
    /// Return whether successfully compiled.
    bool IsCompiled() const { return compiled_; }
    /// Return compile error/warning string.
    const String& GetCompilerOutput() const { return compilerOutput_; }
    /// Return whether uses a parameter.
    bool HasParameter(StringHash param) const { return parameters_.Contains(param); }
    /// Return whether uses a texture unit (only for pixel shaders.)
    bool HasTextureUnit(TextureUnit unit) const { return useTextureUnit_[unit]; }
    /// Return all parameter definitions.
    const HashMap<StringHash, ShaderParameter>& GetParameters() const { return parameters_; }
    
private:
    /// Inspect the constant parameters of the shader bytecode using MojoShader.
    void ParseParameters(unsigned char* bufData, unsigned bufSize);
    /// Strip comments from shader bytecode and store it.
    void CopyStrippedCode(PODVector<unsigned>& dest, unsigned char* bufData, unsigned bufSize);
    
    /// Shader this variation belongs to.
    WeakPtr<Shader> owner_;
    /// Shader type.
    ShaderType type_;
    /// Full shader name.
    String name_;
    /// Defines to use in compiling.
    String defines_;
    /// Shader compile error string.
    String compilerOutput_;
    /// Compiled flag.
    bool compiled_;
    /// Shader parameters.
    HashMap<StringHash, ShaderParameter> parameters_;
    /// Texture unit use flags.
    bool useTextureUnit_[MAX_TEXTURE_UNITS];
};

}
