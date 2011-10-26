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
#include "ShaderProgram.h"
#include "ShaderVariation.h"

#include "DebugNew.h"

ShaderProgram::ShaderProgram(Graphics* graphics, ShaderVariation* vertexShader, ShaderVariation* pixelShader) :
    GPUObject(graphics),
    vertexShader_(vertexShader),
    pixelShader_(pixelShader),
    lastParameterFrame_(0),
    linked_(false)
{
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        useTextureUnit_[i] = false;
}

ShaderProgram::~ShaderProgram()
{
    Release();
}

void ShaderProgram::Release()
{
    if (object_)
    {
        if (!graphics_)
            return;
        
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
            useTextureUnit_[i] = false;
        shaderParameters_.Clear();
        
        if (graphics_->GetShaderProgram() == this)
            graphics_->SetShaders(0, 0);
        
        glDeleteProgram(object_);
        object_ = 0;
        linked_ = false;
        linkerOutput_.Clear();
    }
}

bool ShaderProgram::Link()
{
    Release();
    
    if (!vertexShader_ || !pixelShader_ || !vertexShader_->GetGPUObject() || !pixelShader_->GetGPUObject())
        return false;
    
    object_ = glCreateProgram();
    if (!object_)
    {
        linkerOutput_ = "Could not create shader program";
        return false;
    }
    
    glAttachShader(object_, vertexShader_->GetGPUObject());
    glAttachShader(object_, pixelShader_->GetGPUObject());
    glLinkProgram(object_);
    
    int linked, length;
    glGetProgramiv(object_, GL_LINK_STATUS, &linked);
    linked_ = linked != 0;
    if (!linked_)
    {
        glGetProgramiv(object_, GL_INFO_LOG_LENGTH, &length);
        linkerOutput_.Resize(length);
        glGetProgramInfoLog(object_, length, &length, &linkerOutput_[0]);
    }
    else
        linkerOutput_.Clear();
    
    if (!linked_)
        return false;
    
    const int MAX_PARAMETER_NAME_LENGTH = 256;
    char uniformName[MAX_PARAMETER_NAME_LENGTH];
    int uniformCount;
    
    glUseProgram(object_);
    glGetProgramiv(object_, GL_ACTIVE_UNIFORMS, &uniformCount);
    
    // Check for shader parameters and texture units
    for (int i = 0; i < uniformCount; ++i)
    {
        int location;
        unsigned type;
        int count;
        
        glGetActiveUniform(object_, i, MAX_PARAMETER_NAME_LENGTH, 0, &count, &type, uniformName);
        location = glGetUniformLocation(object_, uniformName);
        
        // Skip inbuilt or disabled uniforms
        if (location < 0)
            continue;
        
        // Check for array index included in the name and strip it
        String name(uniformName);
        unsigned index = name.Find('[');
        if (index != String::NPOS)
        {
            // If not the first index, skip
            if (name.Find("[0]") == String::NPOS)
                continue;
            
            name = name.Substring(0, index);
        }
        
        if (name[0] == 'c')
        {
            // Store the constant uniform mapping
            String paramName = name.Substring(1);
            ShaderParameter newParam;
            newParam.location_ = location;
            newParam.type_ = type;
            shaderParameters_[StringHash(paramName)] = newParam;    
        }
        else if (name[0] == 's')
        {
            // Set the samplers here so that they do not have to be set later
            int unit = graphics_->GetTextureUnit(name.Substring(1));
            if (unit < MAX_TEXTURE_UNITS)
            {
                useTextureUnit_[unit] = true;
                glUniform1iv(location, 1, &unit);
            }
        }
    }
    
    // Query the vertex attribute bindings
    attributeLocations_[0] = glGetAttribLocation(object_, "iPos");
    attributeLocations_[1] = glGetAttribLocation(object_, "iNormal");
    attributeLocations_[2] = glGetAttribLocation(object_, "iColor");
    attributeLocations_[3] = glGetAttribLocation(object_, "iTexCoord");
    attributeLocations_[4] = glGetAttribLocation(object_, "iTexCoord2");
    attributeLocations_[5] = glGetAttribLocation(object_, "iCubeTexCoord");
    attributeLocations_[6] = glGetAttribLocation(object_, "iCubeTexCoord2");
    attributeLocations_[7] = glGetAttribLocation(object_, "iTangent");
    attributeLocations_[8] = glGetAttribLocation(object_, "iBlendWeights");
    attributeLocations_[9] = glGetAttribLocation(object_, "iBlendIndices");
    
    // Rehash the parameter map to ensure minimal load factor
    shaderParameters_.Rehash(NextPowerOfTwo(shaderParameters_.Size()));
    
    return true;
}

bool ShaderProgram::NeedParameterUpdate(StringHash param, const void* source, unsigned frame)
{
    // If global parameter frame has changed, clear all remembered sources
    if (frame != lastParameterFrame_)
    {
        lastParameterFrame_ = frame;
        for (HashMap<StringHash, ShaderParameter>::Iterator i = shaderParameters_.Begin(); i != shaderParameters_.End(); ++i)
            i->second_.lastSource_ = (const void*)M_MAX_UNSIGNED;
    }
    
    HashMap<StringHash, ShaderParameter>::Iterator i = shaderParameters_.Find(param);
    if (i == shaderParameters_.End() || i->second_.lastSource_ == source)
        return false;
    
    i->second_.lastSource_ = source;
    return true;
}

void ShaderProgram::ClearParameterSource(StringHash param)
{
    HashMap<StringHash, ShaderParameter>::Iterator i = shaderParameters_.Find(param);
    if (i == shaderParameters_.End())
        return;
    i->second_.lastSource_ = (const void*)M_MAX_UNSIGNED;
}

ShaderVariation* ShaderProgram::GetVertexShader() const
{
    return vertexShader_;
}

ShaderVariation* ShaderProgram::GetPixelShader() const
{
    return pixelShader_;
}

bool ShaderProgram::HasParameter(StringHash param) const
{
    return shaderParameters_.Find(param) != shaderParameters_.End();
}

const ShaderParameter* ShaderProgram::GetParameter(StringHash param) const
{
    HashMap<StringHash, ShaderParameter>::ConstIterator i = shaderParameters_.Find(param);
    if (i != shaderParameters_.End())
        return &i->second_;
    else
        return 0;
}
