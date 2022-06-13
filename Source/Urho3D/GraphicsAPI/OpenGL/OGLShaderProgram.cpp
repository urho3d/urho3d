// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Graphics/Graphics.h"
#include "../../GraphicsAPI/ConstantBuffer.h"
#include "../../GraphicsAPI/GraphicsImpl.h"
#include "../../GraphicsAPI/ShaderVariation.h"
#include "../../IO/Log.h"
#include "OGLShaderProgram.h"

#include "../../DebugNew.h"

namespace Urho3D
{

static const char* shaderParameterGroups[] = {
    "frame",
    "camera",
    "zone",
    "light",
    "material",
    "object",
    "custom"
};

static unsigned NumberPostfix(const String& str)
{
    for (unsigned i = 0; i < str.Length(); ++i)
    {
        if (IsDigit(str[i]))
            return ToUInt(str.CString() + i);
    }

    return M_MAX_UNSIGNED;
}

i32 ShaderProgram_OGL::globalFrameNumber = 0;
const void* ShaderProgram_OGL::globalParameterSources[MAX_SHADER_PARAMETER_GROUPS];

ShaderProgram_OGL::ShaderProgram_OGL(Graphics* graphics, ShaderVariation* vertexShader, ShaderVariation* pixelShader) :
    GPUObject(graphics),
    vertexShader_(vertexShader),
    pixelShader_(pixelShader)
{
    for (auto& parameterSource : parameterSources_)
        parameterSource = (const void*)M_MAX_UNSIGNED;
}

ShaderProgram_OGL::~ShaderProgram_OGL()
{
    Release();
}

void ShaderProgram_OGL::OnDeviceLost()
{
    if (object_.name_ && !graphics_->IsDeviceLost())
        glDeleteProgram(object_.name_);

    GPUObject::OnDeviceLost();

    if (graphics_ && graphics_->GetShaderProgram_OGL() == this)
        graphics_->SetShaders(nullptr, nullptr);

    linkerOutput_.Clear();
}

void ShaderProgram_OGL::Release()
{
    if (object_.name_)
    {
        if (!graphics_)
            return;

        if (!graphics_->IsDeviceLost())
        {
            if (graphics_->GetShaderProgram_OGL() == this)
                graphics_->SetShaders(nullptr, nullptr);

            glDeleteProgram(object_.name_);
        }

        object_.name_ = 0;
        linkerOutput_.Clear();
        shaderParameters_.Clear();
        vertexAttributes_.Clear();
        usedVertexAttributes_ = 0;

        for (bool& useTextureUnit : useTextureUnits_)
            useTextureUnit = false;
        for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
            constantBuffers_[i].Reset();
    }
}

bool ShaderProgram_OGL::Link()
{
    Release();

    if (!vertexShader_ || !pixelShader_ || !vertexShader_->GetGPUObjectName() || !pixelShader_->GetGPUObjectName())
        return false;

    object_.name_ = glCreateProgram();
    if (!object_.name_)
    {
        linkerOutput_ = "Could not create shader program";
        return false;
    }

    glAttachShader(object_.name_, vertexShader_->GetGPUObjectName());
    glAttachShader(object_.name_, pixelShader_->GetGPUObjectName());
    glLinkProgram(object_.name_);

    int linked, length;
    glGetProgramiv(object_.name_, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        glGetProgramiv(object_.name_, GL_INFO_LOG_LENGTH, &length);
        linkerOutput_.Resize((unsigned)length);
        int outLength;
        glGetProgramInfoLog(object_.name_, length, &outLength, &linkerOutput_[0]);
        glDeleteProgram(object_.name_);
        object_.name_ = 0;
    }
    else
        linkerOutput_.Clear();

    if (!object_.name_)
        return false;

    const int MAX_NAME_LENGTH = 256;
    char nameBuffer[MAX_NAME_LENGTH];
    int attributeCount, uniformCount, elementCount, nameLength;
    GLenum type;

    glUseProgram(object_.name_);

    // Check for vertex attributes
    glGetProgramiv(object_.name_, GL_ACTIVE_ATTRIBUTES, &attributeCount);
    for (int i = 0; i < attributeCount; ++i)
    {
        glGetActiveAttrib(object_.name_, i, (GLsizei)MAX_NAME_LENGTH, &nameLength, &elementCount, &type, nameBuffer);

        String name = String(nameBuffer, nameLength);
        VertexElementSemantic semantic = MAX_VERTEX_ELEMENT_SEMANTICS;
        i8 semanticIndex = 0;

        // Go in reverse order so that "binormal" is detected before "normal"
        for (i32 j = MAX_VERTEX_ELEMENT_SEMANTICS - 1; j >= 0; --j)
        {
            if (name.Contains(ShaderVariation::elementSemanticNames_OGL[j], false))
            {
                semantic = (VertexElementSemantic)j;
                unsigned index = NumberPostfix(name);
                if (index != M_MAX_UNSIGNED)
                    semanticIndex = (i8)index;
                break;
            }
        }

        if (semantic == MAX_VERTEX_ELEMENT_SEMANTICS)
        {
            URHO3D_LOGWARNING("Found vertex attribute " + name + " with no known semantic in shader program " +
                vertexShader_->GetFullName() + " " + pixelShader_->GetFullName());
            continue;
        }

        int location = glGetAttribLocation(object_.name_, name.CString());
        vertexAttributes_[{(i8)semantic, semanticIndex}] = location;
        usedVertexAttributes_ |= (1u << location);
    }

    // Check for constant buffers
#ifndef GL_ES_VERSION_2_0
    HashMap<unsigned, unsigned> blockToBinding;

    if (Graphics::GetGL3Support())
    {
        int numUniformBlocks = 0;

        glGetProgramiv(object_.name_, GL_ACTIVE_UNIFORM_BLOCKS, &numUniformBlocks);
        for (int i = 0; i < numUniformBlocks; ++i)
        {
            glGetActiveUniformBlockName(object_.name_, (GLuint)i, MAX_NAME_LENGTH, &nameLength, nameBuffer);

            String name(nameBuffer, (unsigned)nameLength);

            unsigned blockIndex = glGetUniformBlockIndex(object_.name_, name.CString());
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
                group = NumberPostfix(name);

            if (group >= MAX_SHADER_PARAMETER_GROUPS)
            {
                URHO3D_LOGWARNING("Skipping unrecognized uniform block " + name + " in shader program " + vertexShader_->GetFullName() +
                           " " + pixelShader_->GetFullName());
                continue;
            }

            // Find total constant buffer data size
            int dataSize;
            glGetActiveUniformBlockiv(object_.name_, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &dataSize);
            if (!dataSize)
                continue;

            unsigned bindingIndex = group;
            // Vertex shader constant buffer bindings occupy slots starting from zero to maximum supported, pixel shader bindings
            // from that point onward
            ShaderType shaderType = VS;
            if (name.Contains("PS", false))
            {
                bindingIndex += MAX_SHADER_PARAMETER_GROUPS;
                shaderType = PS;
            }

            glUniformBlockBinding(object_.name_, blockIndex, bindingIndex);
            blockToBinding[blockIndex] = bindingIndex;

            constantBuffers_[bindingIndex] = graphics_->GetOrCreateConstantBuffer(shaderType, bindingIndex, (unsigned)dataSize);
        }
    }
#endif

    // Check for shader parameters and texture units
    glGetProgramiv(object_.name_, GL_ACTIVE_UNIFORMS, &uniformCount);
    for (int i = 0; i < uniformCount; ++i)
    {
        glGetActiveUniform(object_.name_, (GLuint)i, MAX_NAME_LENGTH, nullptr, &elementCount, &type, nameBuffer);
        int location = glGetUniformLocation(object_.name_, nameBuffer);

        // Check for array index included in the name and strip it
        String name(nameBuffer);
        i32 index = name.Find('[');
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
            ShaderParameter parameter{paramName, type, location};
            bool store = location >= 0;

#ifndef GL_ES_VERSION_2_0
            // If running OpenGL 3, the uniform may be inside a constant buffer
            if (parameter.location_ < 0 && Graphics::GetGL3Support())
            {
                int blockIndex, blockOffset;
                glGetActiveUniformsiv(object_.name_, 1, (const GLuint*)&i, GL_UNIFORM_BLOCK_INDEX, &blockIndex);
                glGetActiveUniformsiv(object_.name_, 1, (const GLuint*)&i, GL_UNIFORM_OFFSET, &blockOffset);
                if (blockIndex >= 0)
                {
                    parameter.offset_ = blockOffset;
                    parameter.bufferPtr_ = constantBuffers_[blockToBinding[blockIndex]];
                    store = true;
                }
            }
#endif

            if (store)
                shaderParameters_[StringHash(paramName)] = parameter;
        }
        else if (location >= 0 && name[0] == 's')
        {
            // Set the samplers here so that they do not have to be set later
            unsigned unit = graphics_->GetTextureUnit(name.Substring(1));
            if (unit >= MAX_TEXTURE_UNITS)
                unit = NumberPostfix(name);

            if (unit < MAX_TEXTURE_UNITS)
            {
                useTextureUnits_[unit] = true;
                glUniform1iv(location, 1, reinterpret_cast<int*>(&unit));
            }
        }
    }

    // Rehash the parameter & vertex attributes maps to ensure minimal load factor
    vertexAttributes_.Rehash(NextPowerOfTwo(vertexAttributes_.Size()));
    shaderParameters_.Rehash(NextPowerOfTwo(shaderParameters_.Size()));

    return true;
}

ShaderVariation* ShaderProgram_OGL::GetVertexShader() const
{
    return vertexShader_;
}

ShaderVariation* ShaderProgram_OGL::GetPixelShader() const
{
    return pixelShader_;
}

bool ShaderProgram_OGL::HasParameter(StringHash param) const
{
    return shaderParameters_.Find(param) != shaderParameters_.End();
}

const ShaderParameter* ShaderProgram_OGL::GetParameter(StringHash param) const
{
    HashMap<StringHash, ShaderParameter>::ConstIterator i = shaderParameters_.Find(param);
    if (i != shaderParameters_.End())
        return &i->second_;
    else
        return nullptr;
}

bool ShaderProgram_OGL::NeedParameterUpdate(ShaderParameterGroup group, const void* source)
{
    // If global framenumber has changed, invalidate all per-program parameter sources now
    if (globalFrameNumber != frameNumber_)
    {
        for (auto& parameterSource : parameterSources_)
            parameterSource = (const void*)M_MAX_UNSIGNED;
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

void ShaderProgram_OGL::ClearParameterSource(ShaderParameterGroup group)
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

void ShaderProgram_OGL::ClearParameterSources()
{
    ++globalFrameNumber;
    if (!globalFrameNumber)
        ++globalFrameNumber;

#ifndef GL_ES_VERSION_2_0
    for (auto& globalParameterSource : globalParameterSources)
        globalParameterSource = (const void*)M_MAX_UNSIGNED;
#endif
}

void ShaderProgram_OGL::ClearGlobalParameterSource(ShaderParameterGroup group)
{
    globalParameterSources[group] = (const void*)M_MAX_UNSIGNED;
}

}
