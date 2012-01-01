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
#include "GraphicsImpl.h"
#include "Log.h"
#include "Profiler.h"
#include "Shader.h"
#include "ShaderVariation.h"

OBJECTTYPESTATIC(Shader);

Shader::Shader(Context* context) :
    Resource(context),
    shaderType_(VS),
    isSM3_(false)
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
    
    // Check ID
    if (source.ReadFileID() != "USHD")
    {
        LOGERROR(source.GetName() + " is not a valid shader file");
        return false;
    }
    
    unsigned memoryUse = sizeof(Shader);
    
    String fileName = GetFileName(source.GetName());
    shaderType_ = (ShaderType)source.ReadShort();
    isSM3_ = (source.ReadShort() == 3);
    
    // Read the parameter & texture unit hash-to-string mappings
    HashMap<StringHash, String> parameterNames;
    HashMap<StringHash, String> textureUnitNames;
    
    unsigned numParameterNames = source.ReadUInt();
    for (unsigned i = 0; i < numParameterNames; ++i)
    {
        String name = source.ReadString();
        parameterNames[StringHash(name)] = name;
    }
    
    unsigned numTextureUnitNames = source.ReadUInt();
    for (unsigned i = 0; i < numTextureUnitNames; ++i)
    {
        String name = source.ReadString();
        textureUnitNames[StringHash(name)] = name;
    }
    
    // Read the variations
    unsigned numVariations = source.ReadUInt();
    for (unsigned i = 0; i < numVariations; ++i)
    {
        SharedPtr<ShaderVariation> variation(new ShaderVariation(this, shaderType_, isSM3_));
        String variationName = source.ReadString();
        StringHash nameHash(variationName);
        if (!variationName.Empty())
            variation->SetName(fileName + "_" + variationName);
        else
            variation->SetName(fileName);
        
        // Read the parameters & texture units
        unsigned numParameters = source.ReadInt();
        for (unsigned j = 0; j < numParameters; ++j)
        {
            StringHash param = source.ReadStringHash();
            unsigned reg = source.ReadUByte();
            unsigned regCount = source.ReadUByte();
            ShaderParameter newParameter(shaderType_, reg, regCount);
            variation->AddParameter(param, newParameter);
            // Remember the parameter globally. The parameter is only stored the first time; it can have different register
            // index in different shaders, but must have same shader type (either vertex or pixel)
            graphics->RegisterShaderParameter(param, newParameter);
        }
        
        unsigned numTextureUnits = source.ReadInt();
        for (unsigned j = 0; j < numTextureUnits; ++j)
        {
            StringHash unit = source.ReadStringHash();
            String unitName = textureUnitNames[unit];
            unsigned sampler = source.ReadUByte();
            
            TextureUnit tuIndex = graphics->GetTextureUnit(unitName);
            if (tuIndex != MAX_TEXTURE_UNITS)
                variation->AddTextureUnit(tuIndex);
            else if (sampler < MAX_TEXTURE_UNITS)
                variation->AddTextureUnit((TextureUnit)sampler);
        }
        
        variation->OptimizeParameters();
        
        // Read the bytecode
        unsigned dataSize = source.ReadUInt();
        if (dataSize)
        {
            SharedArrayPtr<unsigned char> byteCode(new unsigned char[dataSize]);
            source.Read(byteCode.Get(), dataSize);
            variation->SetByteCode(byteCode);
        }
        
        // Store the variation
        if (variations_.Contains(nameHash))
            LOGERROR("Shader variation name hash collision: " + variationName);
        variations_[nameHash] = variation;
        
        memoryUse += sizeof(ShaderVariation) + dataSize;
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
