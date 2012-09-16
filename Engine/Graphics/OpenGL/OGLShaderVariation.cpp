//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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

#include "Precompiled.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "ShaderVariation.h"

#include "DebugNew.h"

namespace Urho3D
{

ShaderVariation::ShaderVariation(Shader* owner, ShaderType type) :
    GPUObject(owner->GetSubsystem<Graphics>()),
    shaderType_(type),
    sourceCodeLength_(0),
    compiled_(false)
{
}

ShaderVariation::~ShaderVariation()
{
    Release();
}

void ShaderVariation::OnDeviceLost()
{
    GPUObject::OnDeviceLost();
    
    compiled_ = false;
    compilerOutput_.Clear();
    
    if (graphics_)
        graphics_->CleanupShaderPrograms();
}

void ShaderVariation::Release()
{
    if (object_)
    {
        if (!graphics_)
            return;
        
        if (shaderType_ == VS)
        {
            if (graphics_->GetVertexShader() == this)
                graphics_->SetShaders(0, 0);
        }
        else
        {
            if (graphics_->GetPixelShader() == this)
                graphics_->SetShaders(0, 0);
        }
        
        glDeleteShader(object_);
        object_ = 0;
        compiled_ = false;
        compilerOutput_.Clear();
        
        graphics_->CleanupShaderPrograms();
    }
}

bool ShaderVariation::Create()
{
    Release();
    
    if (!sourceCode_ || !sourceCodeLength_)
        return false;
    
    object_ = glCreateShader(shaderType_ == VS ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    if (!object_)
    {
        compilerOutput_ = "Could not create shader object";
        return false;
    }
    
    // Prepend the defines to the shader code
    // Check if there is a version definition; it must stay in the beginning
    String shaderCode(sourceCode_.Get(), sourceCodeLength_);
    String defines;
    String version;
    
    if (shaderCode.StartsWith("#version"))
    {
        unsigned firstLineEnd = shaderCode.Find('\n') + 1;
        if (firstLineEnd != String::NPOS)
        {
            version = shaderCode.Substring(0, firstLineEnd);
            shaderCode = shaderCode.Substring(firstLineEnd);
        }
    }
    
    for (unsigned i = 0; i < defines_.Size(); ++i)
        defines += "#define " + defines_[i] + " " + defineValues_[i] + "\n";
    
    if (!defines_.Empty())
        defines += "\n";
    
    shaderCode = version + defines + shaderCode;
    
    const char* shaderCStr = shaderCode.CString();
    glShaderSource(object_, 1, &shaderCStr, 0);
    glCompileShader(object_);
    
    int compiled, length;
    glGetShaderiv(object_, GL_COMPILE_STATUS, &compiled);
    compiled_ = compiled != 0;
    if (!compiled_)
    {
        glGetShaderiv(object_, GL_INFO_LOG_LENGTH, &length);
        compilerOutput_.Resize(length);
        int outLength;
        glGetShaderInfoLog(object_, length, &outLength, &compilerOutput_[0]);
    }
    else
        compilerOutput_.Clear();
    
    return compiled_;
}

void ShaderVariation::SetName(const String& name)
{
    name_ = name;
}

void ShaderVariation::SetSourceCode(const SharedArrayPtr<char>& code, unsigned length)
{
    sourceCode_ = code;
    sourceCodeLength_ = length;
}

void ShaderVariation::SetDefines(const Vector<String>& defines, const Vector<String>& defineValues)
{
    if (defines.Size() == defineValues.Size())
    {
        defines_ = defines;
        defineValues_ = defineValues;
    }
}

}
