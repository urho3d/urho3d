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

#include "Precompiled.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "ShaderVariation.h"

#include "DebugNew.h"

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
    String shaderCode;
    for (unsigned i = 0; i < defines_.Size(); ++i)
    {
        Vector<String> nameAndValue = defines_[i].Split('=');
        if (nameAndValue.Size() < 2)
            shaderCode += "#define " + defines_[i] + "\n";
        else
            shaderCode += "#define " + nameAndValue[0] + " " + nameAndValue[1] + "\n";
    }
    if (!defines_.Empty())
        shaderCode += "\n";
    shaderCode += String(sourceCode_.Get(), sourceCodeLength_);
    
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
        glGetShaderInfoLog(object_, length, &length, &compilerOutput_[0]);
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

void ShaderVariation::SetDefines(const Vector<String>& defines)
{
    defines_ = defines;
}
