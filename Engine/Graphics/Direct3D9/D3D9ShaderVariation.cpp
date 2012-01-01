//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "ShaderVariation.h"

#include <ctype.h>

#include "DebugNew.h"

ShaderVariation::ShaderVariation(Shader* owner, ShaderType type, bool isSM3) :
    GPUObject(owner->GetSubsystem<Graphics>()),
    shaderType_(type),
    isSM3_(isSM3),
    failed_(false)
{
    ClearParameters();
}

ShaderVariation::~ShaderVariation()
{
    Release();
}

bool ShaderVariation::Create()
{
    Release();
    
    if (!graphics_ || !byteCode_)
        return false;
    
    IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
    if (shaderType_ == VS)
    {
        if (!device || FAILED(device->CreateVertexShader(
            (const DWORD*)byteCode_.Get(),
            (IDirect3DVertexShader9**)&object_)))
            failed_ = true;
    }
    else
    {
        if (!device || FAILED(device->CreatePixelShader(
            (const DWORD*)byteCode_.Get(),
            (IDirect3DPixelShader9**)&object_)))
            failed_ = true;
    }
    
    return !failed_;
}

void ShaderVariation::Release()
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
    
    failed_ = false;
}

void ShaderVariation::SetName(const String& name)
{
    name_ = name;
}

void ShaderVariation::SetByteCode(const SharedArrayPtr<unsigned char>& byteCode)
{
    byteCode_ = byteCode;
    
    // Recreate object if already created from previous bytecode
    if (object_)
        Create();
}

void ShaderVariation::AddParameter(StringHash param, const ShaderParameter& definition)
{
    parameters_[param] = definition;
}

void ShaderVariation::AddTextureUnit(TextureUnit unit)
{
    useTextureUnit_[unit] = true;
}

void ShaderVariation::ClearParameters()
{
    parameters_.Clear();
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        useTextureUnit_[i] = false;
}

void ShaderVariation::OptimizeParameters()
{
    parameters_.Rehash(NextPowerOfTwo(parameters_.Size()));
}

bool ShaderVariation::IsCreated() const
{
    return object_ != 0;
}
