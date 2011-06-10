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

#include <GLee.h>

#include "DebugNew.h"

ShaderProgram::ShaderProgram(Graphics* graphics, ShaderVariation* vertexShader, ShaderVariation* pixelShader) :
    GPUObject(graphics),
    vertexShader_(vertexShader),
    pixelShader_(pixelShader),
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
        
        if ((vertexShader_) && (vertexShader_->GetGPUObject()))
            glDetachShader(object_, vertexShader_->GetGPUObject());
        if ((pixelShader_) && (pixelShader_->GetGPUObject()))
            glDetachShader(object_, pixelShader_->GetGPUObject());
        
        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
            useTextureUnit_[i] = false;
        uniformInfos_.Clear();
        
        glDeleteProgram(object_);
        object_ = 0;
        linked_ = false;
    }
}

bool ShaderProgram::Link()
{
    Release();
    
    if ((!vertexShader_) || (!pixelShader_) || (!vertexShader_->GetGPUObject()) || (!pixelShader_->GetGPUObject()))
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
        glGetShaderInfoLog(object_, length, &length, &linkerOutput_[0]);
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
            ShaderParameter param = graphics_->GetShaderParameter(name.Substring(1));
            if (param < MAX_SHADER_PARAMETERS)
            {
                UniformInfo newInfo;
                newInfo.location_ = location;
                newInfo.type_ = type;
                
                uniformInfos_[param] = newInfo;
            }
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
    attributeLocations_[0] = glGetAttribLocation(object_, "iPosition");
    attributeLocations_[1] = glGetAttribLocation(object_, "iNormal");
    attributeLocations_[2] = glGetAttribLocation(object_, "iColor");
    attributeLocations_[3] = glGetAttribLocation(object_, "iTexCoord");
    attributeLocations_[4] = glGetAttribLocation(object_, "iTexCoord2");
    attributeLocations_[5] = glGetAttribLocation(object_, "iCubeTexCoord");
    attributeLocations_[6] = glGetAttribLocation(object_, "iCubeTexCoord2");
    attributeLocations_[7] = glGetAttribLocation(object_, "iTangent");
    attributeLocations_[8] = glGetAttribLocation(object_, "iBlendWeights");
    attributeLocations_[9] = glGetAttribLocation(object_, "iBlendIndices");
    
    return true;
}

ShaderVariation* ShaderProgram::GetVertexShader() const
{
    return vertexShader_;
}

ShaderVariation* ShaderProgram::GetPixelShader() const
{
    return pixelShader_;
}

bool ShaderProgram::HasParameter(ShaderParameter param) const
{
    return uniformInfos_.Find(param) != uniformInfos_.End();
}

const UniformInfo* ShaderProgram::GetUniformInfo(ShaderParameter param) const
{
    HashMap<ShaderParameter, UniformInfo>::ConstIterator i = uniformInfos_.Find(param);
    if (i != uniformInfos_.End())
        return &i->second_;
    else
        return 0;
}
