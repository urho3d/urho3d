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

#include "../../IO/File.h"
#include "../../IO/FileSystem.h"
#include "../../Graphics/Graphics.h"
#include "../../Graphics/GraphicsImpl.h"
#include "../../IO/Log.h"
#include "../../Resource/ResourceCache.h"
#include "../../Graphics/Shader.h"
#include "../../Graphics/ShaderVariation.h"

#include <windows.h>
#include <d3dcompiler.h>

#include "../../DebugNew.h"

namespace Urho3D
{

ShaderVariation::ShaderVariation(Shader* owner, ShaderType type) :
    GPUObject(owner->GetSubsystem<Graphics>()),
    owner_(owner),
    type_(type)
{
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        useTextureUnit_[i] = false;
}

ShaderVariation::~ShaderVariation()
{
    Release();
}

bool ShaderVariation::Create()
{
    Release();
    
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
    
    String binaryShaderName = path + "Cache/" + name + "_" + StringHash(defines_).ToString() + extension;
    PODVector<unsigned> byteCode;
    
    if (!LoadByteCode(byteCode, binaryShaderName))
    {
        // Compile shader if don't have valid bytecode
        if (!Compile(byteCode))
            return false;
        // Save the bytecode after successful compile, but not if the source is from a package
        if (owner_->GetTimeStamp())
            SaveByteCode(byteCode, binaryShaderName);
    }
    
    // Then create shader from the bytecode
    ID3D11Device* device = graphics_->GetImpl()->GetDevice();
    if (type_ == VS)
    {
        if (device && byteCode.Size())
            device->CreateVertexShader(&byteCode[0], byteCode.Size(), 0, (ID3D11VertexShader**)&object_);
        if (!object_)
            compilerOutput_ = "Could not create vertex shader";
    }
    else
    {
        if (device && byteCode.Size())
            device->CreatePixelShader(&byteCode[0], byteCode.Size(), 0, (ID3D11PixelShader**)&object_);
        if (!object_)
            compilerOutput_ = "Could not create pixel shader";
    }

    return object_ != 0;
}

void ShaderVariation::Release()
{
    if (object_)
    {
        if (!graphics_)
            return;
        
        graphics_->CleanupShaderParameters(this);

        if (type_ == VS)
        {
            if (graphics_->GetVertexShader() == this)
                graphics_->SetShaders(0, 0);
            
            ((ID3D11VertexShader*)object_)->Release();
        }
        else
        {
            if (graphics_->GetPixelShader() == this)
                graphics_->SetShaders(0, 0);
            
            ((ID3D11PixelShader*)object_)->Release();
        }

        object_ = 0;
    }
    
    compilerOutput_.Clear();
    
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        useTextureUnit_[i] = false;
    parameters_.Clear();
}

void ShaderVariation::SetName(const String& name)
{
    name_ = name;
}

void ShaderVariation::SetDefines(const String& defines)
{
    defines_ = defines;
}

Shader* ShaderVariation::GetOwner() const
{
    return owner_;
}

bool ShaderVariation::LoadByteCode(PODVector<unsigned>& byteCode, const String& binaryShaderName)
{
    ResourceCache* cache = owner_->GetSubsystem<ResourceCache>();
    if (!cache->Exists(binaryShaderName))
        return false;
    
    FileSystem* fileSystem = owner_->GetSubsystem<FileSystem>();
    unsigned sourceTimeStamp = owner_->GetTimeStamp();
    // If source code is loaded from a package, its timestamp will be zero. Else check that binary is not older
    // than source
    if (sourceTimeStamp && fileSystem->GetLastModifiedTime(cache->GetResourceFileName(binaryShaderName)) <
        sourceTimeStamp)
        return false;
    
    SharedPtr<File> file = cache->GetFile(binaryShaderName);
    if (!file || file->ReadFileID() != "USHD")
    {
        LOGERROR(binaryShaderName + " is not a valid shader bytecode file");
        return false;
    }
    
    /// \todo Check that shader type and model match
    unsigned short shaderType = file->ReadUShort();
    unsigned short shaderModel = file->ReadUShort();
    
    unsigned numParameters = file->ReadUInt();
    for (unsigned i = 0; i < numParameters; ++i)
    {
        String name = file->ReadString();
        unsigned buffer = file->ReadUByte();
        unsigned offset = file->ReadUInt();
        unsigned size = file->ReadUInt();

        ShaderParameter parameter(type_, name_, buffer, offset, size);
        parameters_[StringHash(name)] = parameter;
    }
    
    unsigned numTextureUnits = file->ReadUInt();
    for (unsigned i = 0; i < numTextureUnits; ++i)
    {
        String unitName = file->ReadString();
        unsigned reg = file->ReadUByte();
        
        if (reg < MAX_TEXTURE_UNITS)
            useTextureUnit_[reg] = true;
    }
    
    unsigned byteCodeSize = file->ReadUInt();
    if (byteCodeSize)
    {
        byteCode.Resize(byteCodeSize >> 2);
        file->Read(&byteCode[0], byteCodeSize);
        
        if (type_ == VS)
            LOGDEBUG("Loaded cached vertex shader " + GetFullName());
        else
            LOGDEBUG("Loaded cached pixel shader " + GetFullName());
        
        return true;
    }
    else
    {
        LOGERROR(binaryShaderName + " has zero length bytecode");
        return false;
    }
}

bool ShaderVariation::Compile(PODVector<unsigned>& byteCode)
{
    const String& sourceCode = owner_->GetSourceCode(type_);
    Vector<String> defines = defines_.Split(' ');
    
    // Set the entrypoint, profile and flags according to the shader being compiled
    const char* entryPoint = 0;
    const char* profile = 0;
    unsigned flags = D3DCOMPILE_OPTIMIZATION_LEVEL3;
    
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
    
    // Collect defines into macros
    Vector<String> defineValues;
    PODVector<D3D_SHADER_MACRO> macros;
    
    for (unsigned i = 0; i < defines.Size(); ++i)
    {
        unsigned equalsPos = defines[i].Find('=');
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
            LOGWARNING("Shader " + GetFullName() + " does not use the define " + defines[i]);
        #endif
    }
    
    D3D_SHADER_MACRO endMacro;
    endMacro.Name = 0;
    endMacro.Definition = 0;
    macros.Push(endMacro);
    
    // Compile using D3DCompile

    LPD3DBLOB shaderCode = 0;
    LPD3DBLOB errorMsgs = 0;
    
    if (FAILED(D3DCompile(sourceCode.CString(), sourceCode.Length(), owner_->GetName().CString(), &macros.Front(), 0,
        entryPoint, profile, flags, 0, &shaderCode, &errorMsgs)))
        compilerOutput_ = String((const char*)errorMsgs->GetBufferPointer(), errorMsgs->GetBufferSize());
    else
    {
        if (type_ == VS)
            LOGDEBUG("Compiled vertex shader " + GetFullName());
        else
            LOGDEBUG("Compiled pixel shader " + GetFullName());
        
        unsigned char* bufData = (unsigned char*)shaderCode->GetBufferPointer();
        unsigned bufSize = shaderCode->GetBufferSize();
        ParseParameters(bufData, bufSize);
        CopyStrippedCode(byteCode, bufData, bufSize);
    }

    if (shaderCode)
        shaderCode->Release();
    if (errorMsgs)
        errorMsgs->Release();
    
    return !byteCode.Empty();
}

void ShaderVariation::ParseParameters(unsigned char* bufData, unsigned bufSize)
{
    /// \todo Implement
}

void ShaderVariation::CopyStrippedCode(PODVector<unsigned>& byteCode, unsigned char* bufData, unsigned bufSize)
{
    unsigned const D3DSIO_COMMENT = 0xFFFE;
    unsigned* srcWords = (unsigned*)bufData;
    unsigned srcWordSize = bufSize >> 2;
    
    for (unsigned i = 0; i < srcWordSize; ++i)
    {
        unsigned opcode = srcWords[i] & 0xffff;
        unsigned paramLength = (srcWords[i] & 0x0f000000) >> 24;
        unsigned commentLength = srcWords[i] >> 16;
        
        // For now, skip comment only at fixed position to prevent false positives
        if (i == 1 && opcode == D3DSIO_COMMENT)
        {
            // Skip the comment
            i += commentLength;
        }
        else
        {
            // Not a comment, copy the data
            byteCode.Push(srcWords[i]);
        }
    }
}

void ShaderVariation::SaveByteCode(const PODVector<unsigned>& byteCode, const String& binaryShaderName)
{
    ResourceCache* cache = owner_->GetSubsystem<ResourceCache>();
    FileSystem* fileSystem = owner_->GetSubsystem<FileSystem>();
    
    String path = GetPath(cache->GetResourceFileName(owner_->GetName())) + "Cache/";
    String fullName = path + GetFileNameAndExtension(binaryShaderName);
    if (!fileSystem->DirExists(path))
        fileSystem->CreateDir(path);
    
    SharedPtr<File> file(new File(owner_->GetContext(), fullName, FILE_WRITE));
    if (!file->IsOpen())
        return;
    
    file->WriteFileID("USHD");
    file->WriteShort((unsigned short)type_);
    file->WriteShort(4);

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
        if (useTextureUnit_[i])
            ++usedTextureUnits;
    }
    file->WriteUInt(usedTextureUnits);
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
    {
        if (useTextureUnit_[i])
        {
            file->WriteString(graphics_->GetTextureUnitName((TextureUnit)i));
            file->WriteUByte(i);
        }
    }
    
    unsigned dataSize = byteCode.Size() << 2;
    file->WriteUInt(dataSize);
    if (dataSize)
        file->Write(&byteCode[0], dataSize);
}

}
