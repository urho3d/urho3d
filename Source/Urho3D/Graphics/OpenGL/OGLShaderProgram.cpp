//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../../Precompiled.h"

#include "../../Graphics/ConstantBuffer.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../Graphics/ShaderProgram.h"
#include "../../Graphics/ShaderVariation.h"
#include "../../IO/Log.h"

#include "../../DebugNew.h"

namespace Urho3D
{

const char* shaderParameterGroups[] = {
    "frame",
    "camera",
    "zone",
    "light",
    "material",
    "object",
    "custom"
};

unsigned ShaderProgram::globalFrameNumber = 0;
const void* ShaderProgram::globalParameterSources[MAX_SHADER_PARAMETER_GROUPS];

ShaderProgram::ShaderProgram(Graphics* graphics, ShaderVariation* vertexShader, ShaderVariation* pixelShader) :
    GPUObject(graphics),
    vertexShader_(vertexShader),
    pixelShader_(pixelShader),
    frameNumber_(0)
{
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        useTextureUnit_[i] = false;
    for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
        parameterSources_[i] = (const void*)M_MAX_UNSIGNED;
}

ShaderProgram::~ShaderProgram()
{
    Release();
}

void ShaderProgram::OnDeviceLost()
{
    GPUObject::OnDeviceLost();

    if (graphics_ && graphics_->GetShaderProgram() == this)
        graphics_->SetShaders(0, 0);

    linkerOutput_.Clear();
}

void ShaderProgram::Release()
{
    if (object_)
    {
        if (!graphics_)
            return;

        if (!graphics_->IsDeviceLost())
        {
            if (graphics_->GetShaderProgram() == this)
                graphics_->SetShaders(0, 0);

            glDeleteProgram(object_);
        }

        object_ = 0;
        linkerOutput_.Clear();
        shaderParameters_.Clear();

        for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
            useTextureUnit_[i] = false;
        for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
            constantBuffers_[i].Reset();
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

    // Bind vertex attribute locations to ensure they are the same in all shaders
    // Note: this is not the same order as in VertexBuffer, instead a remapping is used to ensure everything except cube texture
    // coordinates fit to the first 8 for better GLES2 device compatibility
    glBindAttribLocation(object_, 0, "iPos");
    glBindAttribLocation(object_, 1, "iNormal");
    glBindAttribLocation(object_, 2, "iColor");
    glBindAttribLocation(object_, 3, "iTexCoord");
    glBindAttribLocation(object_, 4, "iTexCoord2");
    glBindAttribLocation(object_, 5, "iTangent");
    glBindAttribLocation(object_, 6, "iBlendWeights");
    glBindAttribLocation(object_, 7, "iBlendIndices");
    glBindAttribLocation(object_, 8, "iCubeTexCoord");
    glBindAttribLocation(object_, 9, "iCubeTexCoord2");
#if !defined(GL_ES_VERSION_2_0) || defined(__EMSCRIPTEN__)
    glBindAttribLocation(object_, 10, "iInstanceMatrix1");
    glBindAttribLocation(object_, 11, "iInstanceMatrix2");
    glBindAttribLocation(object_, 12, "iInstanceMatrix3");
#endif

    glAttachShader(object_, vertexShader_->GetGPUObject());
    glAttachShader(object_, pixelShader_->GetGPUObject());
    glLinkProgram(object_);

    int linked, length;
    glGetProgramiv(object_, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        glGetProgramiv(object_, GL_INFO_LOG_LENGTH, &length);
        linkerOutput_.Resize((unsigned)length);
        int outLength;
        glGetProgramInfoLog(object_, length, &outLength, &linkerOutput_[0]);
        glDeleteProgram(object_);
        object_ = 0;
    }
    else
        linkerOutput_.Clear();

    if (!object_)
        return false;

    const int MAX_PARAMETER_NAME_LENGTH = 256;
    char uniformName[MAX_PARAMETER_NAME_LENGTH];
    int uniformCount;

    glUseProgram(object_);
    glGetProgramiv(object_, GL_ACTIVE_UNIFORMS, &uniformCount);

    // Check for constant buffers
#ifndef GL_ES_VERSION_2_0
    HashMap<unsigned, unsigned> blockToBinding;

    if (Graphics::GetGL3Support())
    {
        int numUniformBlocks = 0;

        glGetProgramiv(object_, GL_ACTIVE_UNIFORM_BLOCKS, &numUniformBlocks);
        for (int i = 0; i < numUniformBlocks; ++i)
        {
            int nameLength;
            glGetActiveUniformBlockName(object_, (GLuint)i, MAX_PARAMETER_NAME_LENGTH, &nameLength, uniformName);

            String name(uniformName, (unsigned)nameLength);

            unsigned blockIndex = glGetUniformBlockIndex(object_, name.CString());
            unsigned group = M_MAX_UNSIGNED;

            // Try to recognize the use of the buffer from its name
            for (unsigned j = 0; j < MAX_SHADER_PARAMETER_GROUPS; ++j)
            {
                if (name.Contains(shaderParameterGroups[j], false))
                {
                    group = j;
                    break;
                }
            }

            // If name is not recognized, search for a digit in the name and use that as the group index
            if (group == M_MAX_UNSIGNED)
            {
                for (unsigned j = 1; j < name.Length(); ++j)
                {
                    if (name[j] >= '0' && name[j] <= '5')
                    {
                        group = name[j] - '0';
                        break;
                    }
                }
            }

            if (group >= MAX_SHADER_PARAMETER_GROUPS)
            {
                URHO3D_LOGWARNING("Skipping unrecognized uniform block " + name + " in shader program " + vertexShader_->GetFullName() +
                           " " + pixelShader_->GetFullName());
                continue;
            }

            // Find total constant buffer data size
            int dataSize;
            glGetActiveUniformBlockiv(object_, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &dataSize);
            if (!dataSize)
                continue;

            unsigned bindingIndex = group;
            // Vertex shader constant buffer bindings occupy slots starting from zero to maximum supported, pixel shader bindings
            // from that point onward
            if (name.Contains("PS", false))
                bindingIndex += MAX_SHADER_PARAMETER_GROUPS;

            glUniformBlockBinding(object_, blockIndex, bindingIndex);
            blockToBinding[blockIndex] = bindingIndex;

            constantBuffers_[bindingIndex] = graphics_->GetOrCreateConstantBuffer(bindingIndex, (unsigned)dataSize);
        }
    }
#endif

    // Check for shader parameters and texture units
    for (int i = 0; i < uniformCount; ++i)
    {
        unsigned type;
        int count;

        glGetActiveUniform(object_, (GLuint)i, MAX_PARAMETER_NAME_LENGTH, 0, &count, &type, uniformName);
        int location = glGetUniformLocation(object_, uniformName);

        // Check for array index included in the name and strip it
        String name(uniformName);
        unsigned index = name.Find('[');
        if (index != String::NPOS)
        {
            // If not the first index, skip
            if (name.Find("[0]", index) == String::NPOS)
                continue;

            name = name.Substring(0, index);
        }

        if (name[0] == 'c')
        {
            // Store constant uniform
            String paramName = name.Substring(1);
            ShaderParameter newParam;
            newParam.type_ = type;
            newParam.location_ = location;

#ifndef GL_ES_VERSION_2_0
            // If running OpenGL 3, the uniform may be inside a constant buffer
            if (newParam.location_ < 0 && Graphics::GetGL3Support())
            {
                int blockIndex, blockOffset;
                glGetActiveUniformsiv(object_, 1, (const GLuint*)&i, GL_UNIFORM_BLOCK_INDEX, &blockIndex);
                glGetActiveUniformsiv(object_, 1, (const GLuint*)&i, GL_UNIFORM_OFFSET, &blockOffset);
                if (blockIndex >= 0)
                {
                    newParam.location_ = blockOffset;
                    newParam.bufferPtr_ = constantBuffers_[blockToBinding[blockIndex]];
                }
            }
#endif

            if (newParam.location_ >= 0)
                shaderParameters_[StringHash(paramName)] = newParam;
        }
        else if (location >= 0 && name[0] == 's')
        {
            // Set the samplers here so that they do not have to be set later
            int unit = graphics_->GetTextureUnit(name.Substring(1));
            if (unit >= MAX_TEXTURE_UNITS)
            {
                // If texture unit name is not recognized, search for a digit in the name and use that as the unit index
                for (unsigned j = 1; j < name.Length(); ++j)
                {
                    if (name[j] >= '0' && name[j] <= '9')
                    {
                        unit = name[j] - '0';
                        break;
                    }
                }
            }

            if (unit < MAX_TEXTURE_UNITS)
            {
                useTextureUnit_[unit] = true;
                glUniform1iv(location, 1, &unit);
            }
        }
    }

    // Rehash the parameter map to ensure minimal load factor
    shaderParameters_.Rehash(NextPowerOfTwo(shaderParameters_.Size()));

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

bool ShaderProgram::NeedParameterUpdate(ShaderParameterGroup group, const void* source)
{
    // If global framenumber has changed, invalidate all per-program parameter sources now
    if (globalFrameNumber != frameNumber_)
    {
        for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
            parameterSources_[i] = (const void*)M_MAX_UNSIGNED;
        frameNumber_ = globalFrameNumber;
    }

    // The shader program may use a mixture of constant buffers and individual uniforms even in the same group
#ifndef GL_ES_VERSION_2_0
    bool useBuffer = constantBuffers_[group].Get() || constantBuffers_[group + MAX_SHADER_PARAMETER_GROUPS].Get();
    bool useIndividual = !constantBuffers_[group].Get() || !constantBuffers_[group + MAX_SHADER_PARAMETER_GROUPS].Get();
    bool needUpdate = false;

    if (useBuffer && globalParameterSources[group] != source)
    {
        globalParameterSources[group] = source;
        needUpdate = true;
    }

    if (useIndividual && parameterSources_[group] != source)
    {
        parameterSources_[group] = source;
        needUpdate = true;
    }

    return needUpdate;
#else
    if (parameterSources_[group] != source)
    {
        parameterSources_[group] = source;
        return true;
    }
    else
        return false;
#endif
}

void ShaderProgram::ClearParameterSource(ShaderParameterGroup group)
{
    // The shader program may use a mixture of constant buffers and individual uniforms even in the same group
#ifndef GL_ES_VERSION_2_0
    bool useBuffer = constantBuffers_[group].Get() || constantBuffers_[group + MAX_SHADER_PARAMETER_GROUPS].Get();
    bool useIndividual = !constantBuffers_[group].Get() || !constantBuffers_[group + MAX_SHADER_PARAMETER_GROUPS].Get();

    if (useBuffer)
        globalParameterSources[group] = (const void*)M_MAX_UNSIGNED;
    if (useIndividual)
        parameterSources_[group] = (const void*)M_MAX_UNSIGNED;
#else
    parameterSources_[group] = (const void*)M_MAX_UNSIGNED;
#endif
}

void ShaderProgram::ClearParameterSources()
{
    ++globalFrameNumber;
    if (!globalFrameNumber)
        ++globalFrameNumber;

#ifndef GL_ES_VERSION_2_0
    for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
        globalParameterSources[i] = (const void*)M_MAX_UNSIGNED;
#endif
}

void ShaderProgram::ClearGlobalParameterSource(ShaderParameterGroup group)
{
    globalParameterSources[group] = (const void*)M_MAX_UNSIGNED;
}

}
