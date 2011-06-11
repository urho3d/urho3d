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
#include "Context.h"
#include "Deserializer.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "Log.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Shader.h"
#include "ShaderVariation.h"
#include "XMLFIle.h"

OBJECTTYPESTATIC(Shader);

Shader::Shader(Context* context) :
    Resource(context),
    shaderType_(VS)
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
    
    unsigned codeLength = source.GetSize();
    shaderCode_.Resize(codeLength);
    source.Read(&shaderCode_[0], codeLength);
    
    String xmlName = source.GetName() + ".xml";
    XMLFile* file = GetSubsystem<ResourceCache>()->GetResource<XMLFile>(xmlName);
    if (!file)
        return false;
    
    XMLElement shaderElem = file->GetRootElement();
    shaderType_ = (shaderElem.GetString("type") == "vs") ? VS : PS;
    
    XMLElement variationElem = shaderElem.GetChildElement("variation");
    while (variationElem)
    {
        String variationName = variationElem.GetString("name");
        StringHash nameHash(variationName);
        SharedPtr<ShaderVariation> newVariation(new ShaderVariation(this, shaderType_));
        newVariation->SetName(variationName);
        newVariation->SetDefines(variationElem.GetString("defines").Split(' '));
        variations_[nameHash] = newVariation;
        
        variationElem = variationElem.GetNextElement();
    }
    
    return true;
}

ShaderVariation* Shader::GetVariation(const String& name)
{
    return GetVariation(StringHash(name));
}

ShaderVariation* Shader::GetVariation(StringHash nameHash)
{
    Map<StringHash, SharedPtr<ShaderVariation> >::Iterator i = variations_.Find(nameHash);
    if (i == variations_.End())
        return 0;
    ShaderVariation* variation = i->second_;
    
    // Create shader object now if not yet created. If fails, remove the variation
    if (!variation->GetGPUObject())
    {
        LOGDEBUG("Creating variation " + variation->GetName() + " of shader " + GetName());
        
        PROFILE(CreateShaderVariation);
        bool success = variation->Create();
        if (!success)
        {
            LOGERROR("Failed to create variation " + variation->GetName() + " of shader " + GetName() + ":\n" +
                variation->GetCompilerOutput());
            variations_.Erase(i);
            return 0;
        }
    }
    
    return variation;
}
