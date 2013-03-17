//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Context.h"
#include "Deserializer.h"
#include "File.h"
#include "FileSystem.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "Log.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Shader.h"
#include "ShaderVariation.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

OBJECTTYPESTATIC(Shader);

Shader::Shader(Context* context) :
    Resource(context),
    sourceModifiedTime_(0)
{
}

Shader::~Shader()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    if (cache)
        cache->ResetDependencies(this);
}

void Shader::RegisterObject(Context* context)
{
    context->RegisterFactory<Shader>();
}

bool Shader::Load(Deserializer& source)
{
    PROFILE(LoadShader);
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    cache->ResetDependencies(this);
    
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics)
        return false;
    
    if (graphics->GetSM3Support())
    {
        vsExtension_ = ".vs3";
        psExtension_ = ".ps3";
        subDir_ = "SM3/";
    }
    else
    {
        vsExtension_ = ".vs2";
        psExtension_ = ".ps2";
        subDir_ = "SM2/";
    }
    
    // Get absolute file name of the shader in case we need to invoke ShaderCompiler. This only works if the shader was not
    // loaded from a package file
    fullFileName_.Clear();
    sourceModifiedTime_ = 0;
    
    File* sourceFile = dynamic_cast<File*>(&source);
    if (sourceFile && !sourceFile->IsPackaged())
    {
        FileSystem* fileSystem = GetSubsystem<FileSystem>();
        
        if (fileSystem && !fileSystem->HasRegisteredPaths())
        {
            fullFileName_ = cache->GetResourceFileName(GetName());
            if (!fullFileName_.Empty())
            {
                // Get last modified time of the main HLSL source file
                String path, fileName, extension;
                SplitPath(fullFileName_, path, fileName, extension);
                String hlslFileName = path + fileName + ".hlsl";
                sourceModifiedTime_ = fileSystem->GetLastModifiedTime(hlslFileName);
                
                String resourcePath = GetPath(GetName());
                cache->StoreResourceDependency(this, resourcePath + fileName + ".hlsl");
                
                // Check also timestamps of any included files and the shader description file
                if (sourceModifiedTime_)
                {
                    SharedPtr<File> file(new File(context_, hlslFileName));
                    while (file->IsOpen() && !file->IsEof())
                    {
                        String line = file->ReadLine();
                        if (line.StartsWith("#include"))
                        {
                            String includeName = line.Substring(9).Replaced("\"", "").Trimmed();
                            String includeFullName = path + includeName;
                            cache->StoreResourceDependency(this, resourcePath + includeName);
                            
                            unsigned includeFileTime = fileSystem->GetLastModifiedTime(includeFullName);
                            if (includeFileTime > sourceModifiedTime_)
                                sourceModifiedTime_ = includeFileTime;
                        }
                    }
                    
                    unsigned descriptionFileTime = fileSystem->GetLastModifiedTime(fullFileName_);
                    if (descriptionFileTime > sourceModifiedTime_)
                        sourceModifiedTime_ = descriptionFileTime;
                }
                else
                {
                    // If the HLSL file was not found, do not attempt to compile shaders
                    fullFileName_.Clear();
                }
            }
        }
    }
    
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(source))
        return false;
    
    Vector<String> globalDefines;
    Vector<String> globalDefineValues;
    
    if (graphics->GetSM3Support())
    {
        globalDefines.Push("SM3");
        globalDefineValues.Push("1");
    }
    
    if (!vsParser_.Parse(VS, xml->GetRoot("shaders"), globalDefines, globalDefineValues))
    {
        LOGERROR("VS: " + vsParser_.GetErrorMessage());
        return false;
    }
    if (!psParser_.Parse(PS, xml->GetRoot("shaders"), globalDefines, globalDefineValues))
    {
        LOGERROR("PS: " + psParser_.GetErrorMessage());
        return false;
    }
    
    // If variations had already been created, clear their bytecode
    for (HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator i = vsVariations_.Begin(); i != vsVariations_.End(); ++i)
    {
        i->second_->Release();
        i->second_->SetByteCode(SharedArrayPtr<unsigned char>());
    }
    for (HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator i = psVariations_.Begin(); i != psVariations_.End(); ++i)
    {
        i->second_->Release();
        i->second_->SetByteCode(SharedArrayPtr<unsigned char>());
    }
    
    SetMemoryUse(sizeof(Shader) + 2 * sizeof(ShaderParser) + (vsVariations_.Size() + psVariations_.Size()) *
        sizeof(ShaderVariation));
    return true;
}

ShaderVariation* Shader::GetVariation(ShaderType type, const String& name)
{
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics)
        return 0;
    
    StringHash nameHash(name);
    ShaderParser& parser = type == VS ? vsParser_ : psParser_;
    HashMap<StringHash, SharedPtr<ShaderVariation> >& variations = type == VS ? vsVariations_ : psVariations_;
    
    if (parser.HasCombination(name))
    {
        HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator i = variations.Find(nameHash);
        // Create the shader variation now if not created yet
        if (i == variations.End())
        {
            String path, fileName, extension;
            SplitPath(GetName(), path, fileName, extension);
            
            String compiledShaderName = path + subDir_ + fileName;
            if (!name.Empty())
                compiledShaderName += "_" + name;
            compiledShaderName += type == VS ? vsExtension_ : psExtension_;
            
            i = variations.Insert(MakePair(nameHash, SharedPtr<ShaderVariation>(new ShaderVariation(this, type))));
            i->second_->SetName(compiledShaderName);
            
            SetMemoryUse(GetMemoryUse() + sizeof(ShaderVariation));
        }
        
        return i->second_;
    }
    else
        return 0;
}

bool Shader::PrepareVariation(ShaderVariation* variation)
{
    if (!variation)
        return false;
    
    FileSystem* fileSystem = GetSubsystem<FileSystem>();
    Graphics* graphics = GetSubsystem<Graphics>();
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    if (!fileSystem || !graphics || !cache)
        return false;
    
    String shaderName = variation->GetName();
    String variationName = GetFileName(shaderName);
    unsigned pos = variationName.Find('_');
    if (pos != String::NPOS)
        variationName = variationName.Substring(pos + 1);
    else
        variationName.Clear();
    
    if (!fullFileName_.Empty())
    {
        if (fileSystem->GetLastModifiedTime(cache->GetResourceFileName(shaderName)) < sourceModifiedTime_)
        {
            PROFILE(CompileShader);
            
            LOGINFO("Compiling shader " + shaderName);
            
            Vector<String> arguments;
            arguments.Push("\"" + fullFileName_ + "\"");
            arguments.Push("\"" + GetPath(fullFileName_) + subDir_ + "\"");
            arguments.Push(variation->GetShaderType() == VS ? "-tVS" : "-tPS");
            arguments.Push("-v" + variationName);
            if (graphics->GetSM3Support())
                arguments.Push("-dSM3");
            
            if (fileSystem->SystemRun(fileSystem->GetProgramDir() + "ShaderCompiler", arguments) != 0)
            {
                LOGERROR("Failed to compile shader " + shaderName);
                return false;
            }
        }
    }
    
    SharedPtr<File> file(cache->GetFile(shaderName));
    if (!file)
        return false;
    
    if (file->ReadFileID() != "USHD")
    {
        LOGERROR(shaderName + " is not a valid shader bytecode file");
        return false;
    }
    /// \todo Check that shader type and model match
    unsigned short shaderType = file->ReadUShort();
    unsigned short shaderModel = file->ReadUShort();
    
    unsigned numParameters = file->ReadUInt();
    for (unsigned i = 0; i < numParameters; ++i)
    {
        String paramName = file->ReadString();
        unsigned reg = file->ReadUByte();
        unsigned regCount = file->ReadUByte();
        
        StringHash nameHash(paramName);
        ShaderParameter parameter(variation->GetShaderType(), reg, regCount);
        variation->AddParameter(nameHash, parameter);
        
        // Register the parameter globally
        graphics->RegisterShaderParameter(nameHash, parameter);
    }
    
    unsigned numTextureUnits = file->ReadUInt();
    for (unsigned i = 0; i < numTextureUnits; ++i)
    {
        String unitName = file->ReadString();
        unsigned sampler = file->ReadUByte();
        
        TextureUnit tuIndex = graphics->GetTextureUnit(unitName);
        if (tuIndex < MAX_TEXTURE_UNITS)
            variation->AddTextureUnit(tuIndex);
        else if (sampler < MAX_TEXTURE_UNITS)
            variation->AddTextureUnit((TextureUnit)sampler);
    }
    
    unsigned byteCodeSize = file->ReadUInt();
    if (byteCodeSize)
    {
        SharedArrayPtr<unsigned char> byteCode(new unsigned char[byteCodeSize]);
        file->Read(byteCode.Get(), byteCodeSize);
        variation->SetByteCode(byteCode);
        SetMemoryUse(GetMemoryUse() + byteCodeSize);
        return true;
    }
    else
    {
        LOGERROR("Shader " + shaderName + " has zero length bytecode");
        return false;
    }
}

}
