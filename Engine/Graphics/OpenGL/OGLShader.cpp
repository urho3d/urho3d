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
#include "Context.h"
#include "Deserializer.h"
#include "FileSystem.h"
#include "Graphics.h"
#include "Log.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Shader.h"
#include "ShaderParser.h"
#include "ShaderVariation.h"
#include "XMLFile.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(Shader);

Shader::Shader(Context* context) :
    Resource(context),
    vsSourceCodeLength_(0),
    psSourceCodeLength_(0)
{
}

Shader::~Shader()
{
}

void Shader::RegisterObject(Context* context)
{
    context->RegisterFactory<Shader>();
}

bool Shader::Load(Deserializer& source)
{
    PROFILE(LoadShader);
    
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics)
        return false;
    
    unsigned memoryUse = sizeof(Shader);
    vsSourceCodeLength_ = 0;
    psSourceCodeLength_ = 0;
    
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(source))
        return false;
    
    ShaderParser vsParser;
    ShaderParser psParser;
    Vector<String> globalDefines;
    Vector<String> globalDefineValues;
    
    if (!vsParser.Parse(VS, xml->GetRoot("shaders"), globalDefines, globalDefineValues))
    {
        LOGERROR("VS: " + vsParser.GetErrorMessage());
        return false;
    }
    if (!psParser.Parse(PS, xml->GetRoot("shaders"), globalDefines, globalDefineValues))
    {
        LOGERROR("PS: " + psParser.GetErrorMessage());
        return false;
    }
    
    String path, fileName, extension;
    SplitPath(GetName(), path, fileName, extension);
    
    if (!ProcessSource(vsSourceCode_, vsSourceCodeLength_, path + fileName + ".vert"))
        return false;
    if (!ProcessSource(psSourceCode_, psSourceCodeLength_, path + fileName + ".frag"))
        return false;
    
    const Vector<ShaderCombination>& vsCombinations = vsParser.GetCombinations();
    for (Vector<ShaderCombination>::ConstIterator i = vsCombinations.Begin(); i != vsCombinations.End(); ++i)
    {
        StringHash nameHash(i->name_);
        HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator j = vsVariations_.Find(nameHash);
        if (j == vsVariations_.End())
            j = vsVariations_.Insert(MakePair(nameHash, SharedPtr<ShaderVariation>(new ShaderVariation(this, VS))));
        else
        {
            // If shader variation already exists, release
            j->second_->Release();
        }
        
        String shaderName = path + fileName + "_" + i->name_;
        if (shaderName.EndsWith("_"))
            shaderName.Resize(shaderName.Length() - 1);
        
        j->second_->SetName(shaderName);
        j->second_->SetSourceCode(vsSourceCode_, vsSourceCodeLength_);
        j->second_->SetDefines(i->defines_, i->defineValues_);
    }
    
    const Vector<ShaderCombination>& psCombinations = psParser.GetCombinations();
    for (Vector<ShaderCombination>::ConstIterator i = psCombinations.Begin(); i != psCombinations.End(); ++i)
    {
        StringHash nameHash(i->name_);
        HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator j = psVariations_.Find(nameHash);
        if (j == psVariations_.End())
            j = psVariations_.Insert(MakePair(nameHash, SharedPtr<ShaderVariation>(new ShaderVariation(this, PS))));
        else
        {
            // If shader variation already exists, release
            j->second_->Release();
        }
        
        String shaderName = path + fileName + "_" + i->name_;
        if (shaderName.EndsWith("_"))
            shaderName.Resize(shaderName.Length() - 1);
        
        j->second_->SetName(shaderName);
        j->second_->SetSourceCode(psSourceCode_, psSourceCodeLength_);
        j->second_->SetDefines(i->defines_, i->defineValues_);
    }
    
    memoryUse += (vsVariations_.Size() + psVariations_.Size()) * sizeof(ShaderVariation);
    memoryUse += vsSourceCodeLength_;
    memoryUse += psSourceCodeLength_;
    SetMemoryUse(memoryUse);
    
    return true;
}

ShaderVariation* Shader::GetVariation(ShaderType type, const String& name)
{
    StringHash nameHash(name);
    
    if (type == VS)
    {
        HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator i = vsVariations_.Find(nameHash);
        if (i != vsVariations_.End())
            return i->second_;
        else
            return 0;
    }
    else
    {
        HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator i = psVariations_.Find(nameHash);
        if (i != psVariations_.End())
            return i->second_;
        else
            return 0;
    }
}

bool Shader::ProcessSource(SharedArrayPtr<char>& dest, unsigned& length, const String& fileName)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    if (!cache)
        return false;
    
    Vector<String> glslCode;
    
    // Load the shader source code
    SharedPtr<File> glslFile = cache->GetFile(fileName);
    if (!glslFile)
        return false;
    
    while (!glslFile->IsEof())
        glslCode.Push(glslFile->ReadLine());
    
    // Process the code for includes
    for (unsigned i = 0; i < glslCode.Size(); ++i)
    {
        if (glslCode[i].StartsWith("#include"))
        {
            String includeFileName = GetPath(fileName) + glslCode[i].Substring(9).Replaced("\"", "").Trimmed();
            
            SharedPtr<File> glslIncludeFile = cache->GetFile(includeFileName);
            if (!glslIncludeFile)
                return false;
            
            // Remove the #include line, then include the code
            glslCode.Erase(i);
            unsigned pos = i;
            while (!glslIncludeFile->IsEof())
            {
                glslCode.Insert(pos, glslIncludeFile->ReadLine());
                ++pos;
            }
            // Finally insert an empty line to mark the space between files
            glslCode.Insert(pos, "");
        }
    }
    
    // Copy the final code into one memory block
    length = 0;
    for (unsigned i = 0; i < glslCode.Size(); ++i)
        length += glslCode[i].Length() + 1;
    
    dest = new char[length];
    char* destPtr = dest.Get();
    for (unsigned i = 0; i < glslCode.Size(); ++i)
    {
        memcpy(destPtr, glslCode[i].CString(), glslCode[i].Length());
        destPtr += glslCode[i].Length();
        *destPtr++ = '\n';
    }
    
    return true;
}
