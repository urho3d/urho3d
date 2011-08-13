//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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
#include "RefCounted.h"
#include "ArrayPtr.h"

class Shader;
class ShaderProgram;

/// Shader object on the GPU.
class ShaderVariation : public RefCounted, public GPUObject
{
public:
    /// Construct.
    ShaderVariation(Shader* shader, ShaderType type);
    /// Destruct.
    virtual ~ShaderVariation();
    
    /// Release the shader.
    virtual void Release();
    
    /// Compile the shader. Return true if successful.
    bool Create();
    /// Set name.
    void SetName(const String& name);
    /// Set source code.
    void SetSourceCode(const SharedArrayPtr<char>& code, unsigned length);
    /// Set defines.
    void SetDefines(const Vector<String>& defines);
    
    /// Return shader type.
    ShaderType GetShaderType() const { return shaderType_; }
    /// Return full shader name.
    const String& GetName() const { return name_; }
    /// Return defines.
    const Vector<String>& GetDefines() const { return defines_; }
    /// Return whether successfully compiled.
    bool IsCompiled() const { return compiled_; }
    /// Return compile error/warning string.
    const String& GetCompilerOutput() const { return compilerOutput_; }
    
private:
    /// Shader type.
    ShaderType shaderType_;
    /// Full shader name.
    String name_;
    /// GLSL source code.
    SharedArrayPtr<char> sourceCode_;
    /// Source code length.
    unsigned sourceCodeLength_;
    /// Defines to use in compiling.
    Vector<String> defines_;
    /// Shader compile error string.
    String compilerOutput_;
    /// Compiled flag.
    bool compiled_;
};
