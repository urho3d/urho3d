// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Graphics/Graphics.h"
#include "../GraphicsAPI/Shader.h"
#include "../GraphicsAPI/ShaderVariation.h"
#include "../IO/Deserializer.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"

#include "../DebugNew.h"

namespace Urho3D
{

void CommentOutFunction(String& code, const String& signature)
{
    unsigned startPos = code.Find(signature);
    unsigned braceLevel = 0;
    if (startPos == String::NPOS)
        return;

    code.Insert(startPos, "/*");

    for (unsigned i = startPos + 2 + signature.Length(); i < code.Length(); ++i)
    {
        if (code[i] == '{')
            ++braceLevel;
        else if (code[i] == '}')
        {
            --braceLevel;
            if (braceLevel == 0)
            {
                code.Insert(i + 1, "*/");
                return;
            }
        }
    }
}

Shader::Shader(Context* context) :
    Resource(context),
    timeStamp_(0),
    numVariations_(0)
{
    RefreshMemoryUse();
}

Shader::~Shader()
{
    auto* cache = GetSubsystem<ResourceCache>();
    if (cache)
        cache->ResetDependencies(this);
}

void Shader::RegisterObject(Context* context)
{
    context->RegisterFactory<Shader>();
}

bool Shader::BeginLoad(Deserializer& source)
{
    auto* graphics = GetSubsystem<Graphics>();
    if (!graphics)
        return false;

    // Load the shader source code and resolve any includes
    timeStamp_ = 0;
    String shaderCode;
    if (!ProcessSource(shaderCode, source))
        return false;

    // Comment out the unneeded shader function
    vsSourceCode_ = shaderCode;
    psSourceCode_ = shaderCode;
    CommentOutFunction(vsSourceCode_, "void PS(");
    CommentOutFunction(psSourceCode_, "void VS(");

    // OpenGL: rename either VS() or PS() to main()
    if (Graphics::GetGAPI() == GAPI_OPENGL)
    {
        vsSourceCode_.Replace("void VS(", "void main(");
        psSourceCode_.Replace("void PS(", "void main(");
    }

    RefreshMemoryUse();
    return true;
}

bool Shader::EndLoad()
{
    // If variations had already been created, release them and require recompile
    for (HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator i = vsVariations_.Begin(); i != vsVariations_.End(); ++i)
        i->second_->Release();
    for (HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator i = psVariations_.Begin(); i != psVariations_.End(); ++i)
        i->second_->Release();

    return true;
}

ShaderVariation* Shader::GetVariation(ShaderType type, const String& defines)
{
    return GetVariation(type, defines.CString());
}

ShaderVariation* Shader::GetVariation(ShaderType type, const char* defines)
{
    StringHash definesHash(defines);
    HashMap<StringHash, SharedPtr<ShaderVariation> >& variations(type == VS ? vsVariations_ : psVariations_);
    HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator i = variations.Find(definesHash);
    if (i == variations.End())
    {
        // If shader not found, normalize the defines (to prevent duplicates) and check again. In that case make an alias
        // so that further queries are faster
        String normalizedDefines = NormalizeDefines(defines);
        StringHash normalizedHash(normalizedDefines);

        i = variations.Find(normalizedHash);
        if (i != variations.End())
            variations.Insert(MakePair(definesHash, i->second_));
        else
        {
            // No shader variation found. Create new
            i = variations.Insert(MakePair(normalizedHash, SharedPtr<ShaderVariation>(new ShaderVariation(this, type))));
            if (definesHash != normalizedHash)
                variations.Insert(MakePair(definesHash, i->second_));

            i->second_->SetName(GetFileName(GetName()));
            i->second_->SetDefines(normalizedDefines);
            ++numVariations_;
            RefreshMemoryUse();
        }
    }

    return i->second_;
}

bool Shader::ProcessSource(String& code, Deserializer& source)
{
    auto* cache = GetSubsystem<ResourceCache>();

    // If the source if a non-packaged file, store the timestamp
    auto* file = dynamic_cast<File*>(&source);
    if (file && !file->IsPackaged())
    {
        auto* fileSystem = GetSubsystem<FileSystem>();
        String fullName = cache->GetResourceFileName(file->GetName());
        unsigned fileTimeStamp = fileSystem->GetLastModifiedTime(fullName);
        if (fileTimeStamp > timeStamp_)
            timeStamp_ = fileTimeStamp;
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

String Shader::NormalizeDefines(const String& defines)
{
    Vector<String> definesVec = defines.ToUpper().Split(' ');
    Sort(definesVec.Begin(), definesVec.End());
    return String::Joined(definesVec, " ");
}

void Shader::RefreshMemoryUse()
{
    SetMemoryUse(
        (unsigned)(sizeof(Shader) + vsSourceCode_.Length() + psSourceCode_.Length() + numVariations_ * sizeof(ShaderVariation)));
}

}
