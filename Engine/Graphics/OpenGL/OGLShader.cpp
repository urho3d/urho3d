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
#include "ShaderVariation.h"
#include "XMLFile.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(Shader);

Shader::Shader(Context* context) :
    Resource(context),
    shaderType_(VS),
    sourceCodeLength_(0)
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
    
    // Clear existing variations
    variations_.Clear();
    
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics)
        return false;
    
    unsigned memoryUse = sizeof(Shader);
    
    sourceCodeLength_ = source.GetSize();
    sourceCode_ = new char[sourceCodeLength_];
    source.Read(&sourceCode_[0], sourceCodeLength_);
    memoryUse += sourceCodeLength_;
    
    String fileName = GetFileName(source.GetName());
    String xmlName = source.GetName() + ".xml";
    XMLFile* file = GetSubsystem<ResourceCache>()->GetResource<XMLFile>(xmlName);
    if (!file)
        return false;
    
    XMLElement shaderElem = file->GetRoot();
    shaderType_ = String(shaderElem.GetAttribute("type")) == "vs" ? VS : PS;
    
    XMLElement variationElem = shaderElem.GetChild("variation");
    while (variationElem)
    {
        String variationName = variationElem.GetAttribute("name");
        StringHash nameHash(variationName);
        SharedPtr<ShaderVariation> newVariation(new ShaderVariation(this, shaderType_));
        if (!variationName.Empty())
            newVariation->SetName(fileName + "_" + variationName);
        else
            newVariation->SetName(fileName);
        newVariation->SetSourceCode(sourceCode_, sourceCodeLength_);
        newVariation->SetDefines(String(variationElem.GetAttribute("defines")).Split(' '));
        
        if (variations_.Contains(nameHash))
            LOGERROR("Shader variation name hash collision: " + variationName);
        variations_[nameHash] = newVariation;
        
        variationElem = variationElem.GetNext();
        memoryUse += sizeof(ShaderVariation);
    }
    
    SetMemoryUse(memoryUse);
    return true;
}

ShaderVariation* Shader::GetVariation(const String& name)
{
    StringHash nameHash(name);
    HashMap<StringHash, SharedPtr<ShaderVariation> >::Iterator i = variations_.Find(nameHash);
    if (i != variations_.End())
        return i->second_;
    else
        return 0;
}

