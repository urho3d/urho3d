//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "ShaderVariation.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

Shader::Shader(Context* context) :
    Resource(context),
    timeStamp_(0)
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
    
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics)
        return false;
    
    // Load the shader source code and resolve any includes
    timeStamp_ = 0;
    String shaderCode;
    if (!ProcessSource(shaderCode, source))
        return false;
    
    // Customize the vertex & pixel shader source code to not include the unnecessary shader,
    // and on OpenGL, rename either VS() or PS() to main()
    #ifdef USE_OPENGL
    vsSourceCode_ = shaderCode;
    vsSourceCode_.Replace("void VS(", "void main(");
    if (vsSourceCode_.Find("void PS(") != String::NPOS)
    {
        vsSourceCode_.Replace("void PS(", "/* void PS(");
        vsSourceCode_ += "*/\n";
    }
    
    psSourceCode_ = shaderCode;
    psSourceCode_.Replace("attribute ", "// attribute ");
    psSourceCode_.Replace("void PS(", "void main(");
    if (psSourceCode_.Find("void VS(") != String::NPOS)
    {
        psSourceCode_.Replace("void VS(", "/* void VS(");
        psSourceCode_.Replace("void main(", "*/\nvoid main(");
    }
    #else
    vsSourceCode_ = shaderCode;
    if (vsSourceCode_.Find("void PS(") != String::NPOS)
    {
        vsSourceCode_.Replace("void PS(", "/* void PS(");
        vsSourceCode_ += "*/\n";
    }
    
    psSourceCode_ = shaderCode;
    if (psSourceCode_.Find("void VS(") != String::NPOS)
    {
        psSourceCode_.Replace("void VS(", "/* void VS(");
        psSourceCode_.Replace("void PS(", "*/\nvoid PS(");
    }
    #endif
    
    // If variations had already been created, release them and require recompile
    for (HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator i = vsVariations_.Begin(); i != vsVariations_.End(); ++i)
        i->second_->Release();
    for (HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator i = psVariations_.Begin(); i != psVariations_.End(); ++i)
        i->second_->Release();
    
    SetMemoryUse(sizeof(Shader) + vsSourceCode_.Length() + psSourceCode_.Length() + (vsVariations_.Size() + psVariations_.Size()) *
        sizeof(ShaderVariation));
    
    return true;
}

ShaderVariation* Shader::GetVariation(ShaderType type, const String& defines)
{
    return GetVariation(type, defines.CString());
}

ShaderVariation* Shader::GetVariation(ShaderType type, const char* defines)
{
    StringHash definesHash(defines);
    
    if (type == VS)
    {
        HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator i = vsVariations_.Find(definesHash);
        // Create the shader variation now if not created yet
        if (i == vsVariations_.End())
        {
            i = vsVariations_.Insert(MakePair(definesHash, SharedPtr<ShaderVariation>(new ShaderVariation(this, VS))));
            i->second_->SetName(GetFileName(GetName()) + " " + defines);
            i->second_->SetDefines(defines);
            
            SetMemoryUse(GetMemoryUse() + sizeof(ShaderVariation));
        }
        
        return i->second_;
    }
    else
    {
        HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator i = psVariations_.Find(definesHash);
        // Create the shader variation now if not created yet
        if (i == psVariations_.End())
        {
            i = psVariations_.Insert(MakePair(definesHash, SharedPtr<ShaderVariation>(new ShaderVariation(this, PS))));
            i->second_->SetName(GetFileName(GetName()) + " " + defines);
            i->second_->SetDefines(defines);
            
            SetMemoryUse(GetMemoryUse() + sizeof(ShaderVariation));
        }
        
        return i->second_;
    }
}

String Shader::SanitateDefines(const String& definesIn)
{
    String ret;
    ret.Reserve(definesIn.Length());
    
    unsigned numSpaces = 0;
    
    for (unsigned i = 0; i < definesIn.Length(); ++i)
    {
        // Ensure only one space in a row
        if (definesIn[i] == ' ')
            ++numSpaces;
        else
            numSpaces = 0;
        
        if (numSpaces <= 1)
            ret += definesIn[i];
    }
    
    return ret.Trimmed();
}

bool Shader::ProcessSource(String& code, Deserializer& source)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    if (!cache)
        return false;
    
    // If the source if a non-packaged file, store the timestamp
    File* file = dynamic_cast<File*>(&source);
    if (file && !file->IsPackaged())
    {
        FileSystem* fileSystem = GetSubsystem<FileSystem>();
        if (fileSystem)
        {
            String fullName = cache->GetResourceFileName(file->GetName());
            unsigned fileTimeStamp = fileSystem->GetLastModifiedTime(fullName);
            if (fileTimeStamp > timeStamp_)
                timeStamp_ = fileTimeStamp;
        }
    }
    
    // Store resource dependencies for includes so that we know to reload if any of them changes
    if (source.GetName() != GetName())
        cache->StoreResourceDependency(this, source.GetName());
    
    while (!source.IsEof())
    {
        String line = source.ReadLine();
        
        if (line.StartsWith("#include"))
        {
            String includeFileName = GetPath(source.GetName()) + line.Substring(9).Replaced("\"", "").Trimmed();
            
            SharedPtr<File> includeFile = cache->GetFile(includeFileName);
            if (!includeFile)
                return false;
            
            // Add the include file into the current code recursively
            if (!ProcessSource(code, *includeFile))
                return false;
        }
        else
        {
            code += line;
            code += "\n";
        }
    }

    // Finally insert an empty line to mark the space between files
    code += "\n";
    
    return true;
}

}
