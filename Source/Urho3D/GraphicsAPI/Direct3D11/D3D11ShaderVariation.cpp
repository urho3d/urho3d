// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../../Precompiled.h"

#include "../../Graphics/Graphics.h"
#include "../../GraphicsAPI/Direct3D11/D3D11GraphicsImpl.h"
#include "../../GraphicsAPI/Shader.h"
#include "../../GraphicsAPI/VertexBuffer.h"
#include "../../IO/File.h"
#include "../../IO/FileSystem.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"

#include <d3dcompiler.h>

#include "../../DebugNew.h"

namespace Urho3D
{

const char* ShaderVariation::elementSemanticNames_D3D11[] =
{
    "POSITION",
    "NORMAL",
    "BINORMAL",
    "TANGENT",
    "TEXCOORD",
    "COLOR",
    "BLENDWEIGHT",
    "BLENDINDICES",
    "OBJECTINDEX"
};

void ShaderVariation::OnDeviceLost_D3D11()
{
    // No-op on Direct3D11
}

bool ShaderVariation::Create_D3D11()
{
    Release_D3D11();

    if (!graphics_)
        return false;

    if (!owner_)
    {
        compilerOutput_ = "Owner shader has expired";
        return false;
    }

    // Check for up-to-date bytecode on disk
    String path, name, extension;
    SplitPath(owner_->GetName(), path, name, extension);
    extension = type_ == VS ? ".vs4" : ".ps4";

    String binaryShaderName = graphics_->GetShaderCacheDir() + name + "_" + StringHash(defines_).ToString() + extension;

    if (!LoadByteCode_D3D11(binaryShaderName))
    {
        // Compile shader if don't have valid bytecode
        if (!Compile_D3D11())
            return false;
        // Save the bytecode after successful compile, but not if the source is from a package
        if (owner_->GetTimeStamp())
            SaveByteCode_D3D11(binaryShaderName);
    }

    // Then create shader from the bytecode
    ID3D11Device* device = graphics_->GetImpl_D3D11()->GetDevice();
    if (type_ == VS)
    {
        if (device && byteCode_.Size())
        {
            HRESULT hr = device->CreateVertexShader(&byteCode_[0], byteCode_.Size(), nullptr, (ID3D11VertexShader**)&object_.ptr_);
            if (FAILED(hr))
            {
                URHO3D_SAFE_RELEASE(object_.ptr_);
                compilerOutput_ = "Could not create vertex shader (HRESULT " + ToStringHex((unsigned)hr) + ")";
            }
        }
        else
            compilerOutput_ = "Could not create vertex shader, empty bytecode";
    }
    else
    {
        if (device && byteCode_.Size())
        {
            HRESULT hr = device->CreatePixelShader(&byteCode_[0], byteCode_.Size(), nullptr, (ID3D11PixelShader**)&object_.ptr_);
            if (FAILED(hr))
            {
                URHO3D_SAFE_RELEASE(object_.ptr_);
                compilerOutput_ = "Could not create pixel shader (HRESULT " + ToStringHex((unsigned)hr) + ")";
            }
        }
        else
            compilerOutput_ = "Could not create pixel shader, empty bytecode";
    }

    return object_.ptr_ != nullptr;
}

void ShaderVariation::Release_D3D11()
{
    if (object_.ptr_)
    {
        if (!graphics_)
            return;

        graphics_->CleanupShaderPrograms_D3D11(this);

        if (type_ == VS)
        {
            if (graphics_->GetVertexShader() == this)
                graphics_->SetShaders(nullptr, nullptr);
        }
        else
        {
            if (graphics_->GetPixelShader() == this)
                graphics_->SetShaders(nullptr, nullptr);
        }

        URHO3D_SAFE_RELEASE(object_.ptr_);
    }

    compilerOutput_.Clear();

    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        useTextureUnits_[i] = false;
    for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
        constantBufferSizes_[i] = 0;
    parameters_.Clear();
    byteCode_.Clear();
    elementHash_ = 0;
}

void ShaderVariation::SetDefines_D3D11(const String& defines)
{
    defines_ = defines;

    // Internal mechanism for appending the CLIPPLANE define, prevents runtime (every frame) string manipulation
    definesClipPlane_ = defines;
    if (!definesClipPlane_.EndsWith(" CLIPPLANE"))
        definesClipPlane_ += " CLIPPLANE";
}

bool ShaderVariation::LoadByteCode_D3D11(const String& binaryShaderName)
{
    ResourceCache* cache = owner_->GetSubsystem<ResourceCache>();
    if (!cache->Exists(binaryShaderName))
        return false;

    FileSystem* fileSystem = owner_->GetSubsystem<FileSystem>();
    unsigned sourceTimeStamp = owner_->GetTimeStamp();
    // If source code is loaded from a package, its timestamp will be zero. Else check that binary is not older
    // than source
    if (sourceTimeStamp && fileSystem->GetLastModifiedTime(cache->GetResourceFileName(binaryShaderName)) < sourceTimeStamp)
        return false;

    SharedPtr<File> file = cache->GetFile(binaryShaderName);
    if (!file || file->ReadFileID() != "USHD")
    {
        URHO3D_LOGERROR(binaryShaderName + " is not a valid shader bytecode file");
        return false;
    }

    /// \todo Check that shader type and model match
    /*unsigned short shaderType = */file->ReadUShort();
    /*unsigned short shaderModel = */file->ReadUShort();
    elementHash_ = file->ReadUInt();
    elementHash_ <<= 32;

    unsigned numParameters = file->ReadUInt();
    for (unsigned i = 0; i < numParameters; ++i)
    {
        String name = file->ReadString();
        unsigned buffer = file->ReadUByte();
        unsigned offset = file->ReadUInt();
        unsigned size = file->ReadUInt();

        parameters_[StringHash(name)] = ShaderParameter{type_, name, offset, size, buffer};
    }

    unsigned numTextureUnits = file->ReadUInt();
    for (unsigned i = 0; i < numTextureUnits; ++i)
    {
        /*String unitName = */file->ReadString();
        unsigned reg = file->ReadUByte();

        if (reg < MAX_TEXTURE_UNITS)
            useTextureUnits_[reg] = true;
    }

    unsigned byteCodeSize = file->ReadUInt();
    if (byteCodeSize)
    {
        byteCode_.Resize(byteCodeSize);
        file->Read(&byteCode_[0], byteCodeSize);

        if (type_ == VS)
            URHO3D_LOGDEBUG("Loaded cached vertex shader " + GetFullName());
        else
            URHO3D_LOGDEBUG("Loaded cached pixel shader " + GetFullName());

        CalculateConstantBufferSizes_D3D11();
        return true;
    }
    else
    {
        URHO3D_LOGERROR(binaryShaderName + " has zero length bytecode");
        return false;
    }
}

bool ShaderVariation::Compile_D3D11()
{
    const String& sourceCode = owner_->GetSourceCode(type_);
    Vector<String> defines = defines_.Split(' ');

    // Set the entrypoint, profile and flags according to the shader being compiled
    const char* entryPoint = nullptr;
    const char* profile = nullptr;
    unsigned flags = D3DCOMPILE_OPTIMIZATION_LEVEL3;

    defines.Push("D3D11");

    if (type_ == VS)
    {
        entryPoint = "VS";
        defines.Push("COMPILEVS");
        profile = "vs_4_0";
    }
    else
    {
        entryPoint = "PS";
        defines.Push("COMPILEPS");
        profile = "ps_4_0";
        flags |= D3DCOMPILE_PREFER_FLOW_CONTROL;
    }

    defines.Push("MAXBONES=" + String(Graphics::GetMaxBones()));

    // Collect defines into macros
    Vector<String> defineValues;
    Vector<D3D_SHADER_MACRO> macros;

    for (unsigned i = 0; i < defines.Size(); ++i)
    {
        i32 equalsPos = defines[i].Find('=');
        if (equalsPos != String::NPOS)
        {
            defineValues.Push(defines[i].Substring(equalsPos + 1));
            defines[i].Resize(equalsPos);
        }
        else
            defineValues.Push("1");
    }
    for (unsigned i = 0; i < defines.Size(); ++i)
    {
        D3D_SHADER_MACRO macro;
        macro.Name = defines[i].CString();
        macro.Definition = defineValues[i].CString();
        macros.Push(macro);

        // In debug mode, check that all defines are referenced by the shader code
#ifdef _DEBUG
        if (sourceCode.Find(defines[i]) == String::NPOS)
            URHO3D_LOGWARNING("Shader " + GetFullName() + " does not use the define " + defines[i]);
#endif
    }

    D3D_SHADER_MACRO endMacro;
    endMacro.Name = nullptr;
    endMacro.Definition = nullptr;
    macros.Push(endMacro);

    // Compile using D3DCompile
    ID3DBlob* shaderCode = nullptr;
    ID3DBlob* errorMsgs = nullptr;

    HRESULT hr = D3DCompile(sourceCode.CString(), sourceCode.Length(), owner_->GetName().CString(), &macros.Front(), nullptr,
        entryPoint, profile, flags, 0, &shaderCode, &errorMsgs);
    if (FAILED(hr))
    {
        // Do not include end zero unnecessarily
        compilerOutput_ = String((const char*)errorMsgs->GetBufferPointer(), (unsigned)errorMsgs->GetBufferSize() - 1);
    }
    else
    {
        if (type_ == VS)
            URHO3D_LOGDEBUG("Compiled vertex shader " + GetFullName());
        else
            URHO3D_LOGDEBUG("Compiled pixel shader " + GetFullName());

        unsigned char* bufData = (unsigned char*)shaderCode->GetBufferPointer();
        unsigned bufSize = (unsigned)shaderCode->GetBufferSize();
        // Use the original bytecode to reflect the parameters
        ParseParameters_D3D11(bufData, bufSize);
        CalculateConstantBufferSizes_D3D11();

        // Then strip everything not necessary to use the shader
        ID3DBlob* strippedCode = nullptr;
        D3DStripShader(bufData, bufSize,
            D3DCOMPILER_STRIP_REFLECTION_DATA | D3DCOMPILER_STRIP_DEBUG_INFO | D3DCOMPILER_STRIP_TEST_BLOBS, &strippedCode);
        byteCode_.Resize((unsigned)strippedCode->GetBufferSize());
        memcpy(&byteCode_[0], strippedCode->GetBufferPointer(), byteCode_.Size());
        strippedCode->Release();
    }

    URHO3D_SAFE_RELEASE(shaderCode);
    URHO3D_SAFE_RELEASE(errorMsgs);

    return !byteCode_.Empty();
}

void ShaderVariation::ParseParameters_D3D11(unsigned char* bufData, unsigned bufSize)
{
    ID3D11ShaderReflection* reflection = nullptr;
    D3D11_SHADER_DESC shaderDesc;

    HRESULT hr = D3DReflect(bufData, bufSize, IID_ID3D11ShaderReflection, (void**)&reflection);
    if (FAILED(hr) || !reflection)
    {
        URHO3D_SAFE_RELEASE(reflection);
        URHO3D_LOGD3DERROR("Failed to reflect vertex shader's input signature", hr);
        return;
    }

    reflection->GetDesc(&shaderDesc);

    if (type_ == VS)
    {
        unsigned elementHash = 0;
        for (unsigned i = 0; i < shaderDesc.InputParameters; ++i)
        {
            D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
            reflection->GetInputParameterDesc((UINT)i, &paramDesc);
            VertexElementSemantic semantic = (VertexElementSemantic)GetStringListIndex(paramDesc.SemanticName, elementSemanticNames_D3D11, MAX_VERTEX_ELEMENT_SEMANTICS, true);
            if (semantic != MAX_VERTEX_ELEMENT_SEMANTICS)
            {
                CombineHash(elementHash, semantic);
                CombineHash(elementHash, paramDesc.SemanticIndex);
            }
        }
        elementHash_ = elementHash;
        elementHash_ <<= 32;
    }

    HashMap<String, unsigned> cbRegisterMap;

    for (unsigned i = 0; i < shaderDesc.BoundResources; ++i)
    {
        D3D11_SHADER_INPUT_BIND_DESC resourceDesc;
        reflection->GetResourceBindingDesc(i, &resourceDesc);
        String resourceName(resourceDesc.Name);
        if (resourceDesc.Type == D3D_SIT_CBUFFER)
            cbRegisterMap[resourceName] = resourceDesc.BindPoint;
        else if (resourceDesc.Type == D3D_SIT_SAMPLER && resourceDesc.BindPoint < MAX_TEXTURE_UNITS)
            useTextureUnits_[resourceDesc.BindPoint] = true;
    }

    for (unsigned i = 0; i < shaderDesc.ConstantBuffers; ++i)
    {
        ID3D11ShaderReflectionConstantBuffer* cb = reflection->GetConstantBufferByIndex(i);
        D3D11_SHADER_BUFFER_DESC cbDesc;
        cb->GetDesc(&cbDesc);
        unsigned cbRegister = cbRegisterMap[String(cbDesc.Name)];

        for (unsigned j = 0; j < cbDesc.Variables; ++j)
        {
            ID3D11ShaderReflectionVariable* var = cb->GetVariableByIndex(j);
            D3D11_SHADER_VARIABLE_DESC varDesc;
            var->GetDesc(&varDesc);
            String varName(varDesc.Name);
            if (varName[0] == 'c')
            {
                varName = varName.Substring(1); // Strip the c to follow Urho3D constant naming convention
                parameters_[varName] = ShaderParameter{type_, varName, varDesc.StartOffset, varDesc.Size, cbRegister};
            }
        }
    }

    reflection->Release();
}

void ShaderVariation::SaveByteCode_D3D11(const String& binaryShaderName)
{
    ResourceCache* cache = owner_->GetSubsystem<ResourceCache>();
    FileSystem* fileSystem = owner_->GetSubsystem<FileSystem>();

    // Filename may or may not be inside the resource system
    String fullName = binaryShaderName;
    if (!IsAbsolutePath(fullName))
    {
        // If not absolute, use the resource dir of the shader
        String shaderFileName = cache->GetResourceFileName(owner_->GetName());
        if (shaderFileName.Empty())
            return;
        fullName = shaderFileName.Substring(0, shaderFileName.Find(owner_->GetName())) + binaryShaderName;
    }
    String path = GetPath(fullName);
    if (!fileSystem->DirExists(path))
        fileSystem->CreateDir(path);

    SharedPtr<File> file(new File(owner_->GetContext(), fullName, FILE_WRITE));
    if (!file->IsOpen())
        return;

    file->WriteFileID("USHD");
    file->WriteShort((unsigned short)type_);
    file->WriteShort(4);
    file->WriteUInt(elementHash_ >> 32);

    file->WriteUInt(parameters_.Size());
    for (HashMap<StringHash, ShaderParameter>::ConstIterator i = parameters_.Begin(); i != parameters_.End(); ++i)
    {
        file->WriteString(i->second_.name_);
        file->WriteUByte((unsigned char)i->second_.buffer_);
        file->WriteUInt(i->second_.offset_);
        file->WriteUInt(i->second_.size_);
    }

    unsigned usedTextureUnits = 0;
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
    {
        if (useTextureUnits_[i])
            ++usedTextureUnits;
    }
    file->WriteUInt(usedTextureUnits);
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
    {
        if (useTextureUnits_[i])
        {
            file->WriteString(graphics_->GetTextureUnitName((TextureUnit)i));
            file->WriteUByte((unsigned char)i);
        }
    }

    file->WriteUInt(byteCode_.Size());
    if (byteCode_.Size())
        file->Write(&byteCode_[0], byteCode_.Size());
}

void ShaderVariation::CalculateConstantBufferSizes_D3D11()
{
    for (unsigned i = 0; i < MAX_SHADER_PARAMETER_GROUPS; ++i)
        constantBufferSizes_[i] = 0;

    for (HashMap<StringHash, ShaderParameter>::ConstIterator i = parameters_.Begin(); i != parameters_.End(); ++i)
    {
        if (i->second_.buffer_ < MAX_SHADER_PARAMETER_GROUPS)
        {
            unsigned oldSize = constantBufferSizes_[i->second_.buffer_];
            unsigned paramEnd = i->second_.offset_ + i->second_.size_;
            if (paramEnd > oldSize)
                constantBufferSizes_[i->second_.buffer_] = paramEnd;
        }
    }
}

}
