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

#include <ctype.h>

#include "DebugNew.h"

OBJECTTYPESTATIC(ShaderProgram);

ShaderProgram::ShaderProgram(Shader* shader, ShaderType type, bool isSM3) :
    GPUObject(shader->GetSubsystem<Graphics>()),
    shader_(shader),
    shaderType_(type),
    isSM3_(isSM3)
{
    ClearParameters();
}

ShaderProgram::~ShaderProgram()
{
    Release();
}

bool ShaderProgram::Create()
{
    Release();
    
    if ((!graphics_) || (!byteCode_))
        return false;
    
    IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
    if (shaderType_ == VS)
    {
        if ((!device) || (FAILED(device->CreateVertexShader(
            (const DWORD*)byteCode_.GetPtr(),
            (IDirect3DVertexShader9**)&object_))))
            return false;
    }
    else
    {
        if ((!device) || (FAILED(device->CreatePixelShader(
            (const DWORD*)byteCode_.GetPtr(),
            (IDirect3DPixelShader9**)&object_))))
            return false;
    }
    
    return true;
}

void ShaderProgram::Release()
{
    if (object_)
    {
        if (!graphics_)
            return;
        
        if (shaderType_ == VS)
        {
            if (graphics_->GetPixelShader() == this)
                graphics_->SetShaders(0, 0);
            
            ((IDirect3DVertexShader9*)object_)->Release();
        }
        else
        {
            if (graphics_->GetVertexShader() == this)
                graphics_->SetShaders(0, 0);
            
            ((IDirect3DPixelShader9*)object_)->Release();
        }
        
        object_ = 0;
    }
}

void ShaderProgram::SetName(const String& name)
{
    name_ = name;
}

void ShaderProgram::SetByteCode(const SharedArrayPtr<unsigned char>& byteCode)
{
    byteCode_ = byteCode;
    
    // Recreate object if already created from previous bytecode
    if (object_)
        Create();
}

void ShaderProgram::SetUseParameter(ShaderParameter param, bool enable)
{
    useParameter_[param] = enable;
}

void ShaderProgram::SetUseTextureUnit(TextureUnit unit, bool enable)
{
    useTextureUnit_[unit] = enable;
}

void ShaderProgram::ClearParameters()
{
    for (unsigned i = 0; i < MAX_SHADER_PARAMETERS; ++i)
        useParameter_[i] = false;
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        useTextureUnit_[i] = false;
}

bool ShaderProgram::NeedParameterUpdate(ShaderParameter parameter, const void* source)
{
    if ((useParameter_[parameter]) && (graphics_) && (graphics_->GetShaderParameterSource(parameter) != source))
    {
        graphics_->SetShaderParameterSource(parameter, source);
        return true;
    }
    return false;
}

Shader* ShaderProgram::GetShader() const
{
    return shader_;
}
