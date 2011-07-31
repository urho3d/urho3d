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
#include "HashSet.h"
#include "RefCounted.h"
#include "ArrayPtr.h"

class Shader;

/// Vertex or pixel shader on the GPU
class ShaderVariation : public RefCounted, public GPUObject
{
public:
    /// Construct
    ShaderVariation(Shader* shader, ShaderType type, bool isSM3);
    /// Destruct
    virtual ~ShaderVariation();
    
    /// Create the shader program. Return true if successful
    bool Create();
    /// Release shader
    virtual void Release();
    
    /// %Set name
    void SetName(const String& name);
    /// %Set bytecode
    void SetByteCode(const SharedArrayPtr<unsigned char>& byteCode);
    /// %Set to use a parameter
    void SetUseParameter(StringHash param, bool enable);
    /// %Set to use a texture unit
    void SetUseTextureUnit(TextureUnit unit, bool enable);
    /// Clear parameter and texture unit use flags
    void ClearParameters();
    
    /// Return shader type
    ShaderType GetShaderType() const { return shaderType_; }
    /// Return full shader name
    const String& GetName() const { return name_; }
    /// Return whether created successfully
    bool IsCreated() const;
    /// Return whether compile failed
    bool IsFailed() const { return failed_; }
    /// Return whether requires Shader Model 3
    bool IsSM3() const { return isSM3_; }
    /// Return whether uses a specific shader parameter
    bool HasParameter(StringHash param) const { return useParameter_.Contains(param); }
    /// Return whether uses a texture unit (only for pixel shaders)
    bool HasTextureUnit(TextureUnit unit) const { return useTextureUnit_[unit]; }
    
private:
    /// Shader type
    ShaderType shaderType_;
    /// Full shader name
    String name_;
    /// Shader bytecode
    SharedArrayPtr<unsigned char> byteCode_;
    /// Shader Model 3 flag
    bool isSM3_;
    /// Compile failed flag
    bool failed_;
    /// Parameter use flags
    HashSet<StringHash> useParameter_;
    /// Texture unit use flags
    bool useTextureUnit_[MAX_TEXTURE_UNITS];
};
