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
#include "FileSystem.h"
#include "Graphics.h"
#include "GraphicsImpl.h"
#include "Log.h"
#include "PixelShader.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "SharedArrayPtr.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include <ctype.h>

#include "DebugNew.h"

OBJECTTYPESTATIC(PixelShader);

PixelShader::PixelShader(Context* context) :
    Resource(context),
    GPUObject(GetSubsystem<Graphics>()),
    isSM3_(false)
{
    for (unsigned i = 0; i < MAX_PS_PARAMETERS; ++i)
        useParameter_[i] = false;
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        useTextureUnit_[i] = false;
}

PixelShader::~PixelShader()
{
    Release();
}

void PixelShader::RegisterObject(Context* context)
{
    context->RegisterFactory<PixelShader>();
}

bool PixelShader::Load(Deserializer& source)
{
    PROFILE(LoadPixelShader);
    
    Release();
    
    if (!graphics_)
        return false;
    
    unsigned dataSize = source.GetSize();
    SetMemoryUse(dataSize);
    
    SharedArrayPtr<unsigned char> buffer(new unsigned char[dataSize]);
    source.Read((void*)buffer.GetPtr(), dataSize);
    
    IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
    if ((!device) || (FAILED(device->CreatePixelShader(
        (const DWORD*)buffer.GetPtr(),
        (IDirect3DPixelShader9**)&object_))))
    {
        LOGERROR("Could not create pixel shader " + GetName());
        return false;
    }
    
    LoadParameters();
    return true;
}

bool PixelShader::NeedParameterUpdate(PSParameter parameter, const void* source)
{
    if ((useParameter_[parameter]) && (graphics_->GetPSParameterSource(parameter) != source))
    {
        graphics_->SetPSParameterSource(parameter, source);
        return true;
    }
    return false;
}

void PixelShader::Release()
{
    if (object_)
    {
        if (!graphics_)
            return;
        
        if (graphics_->GetPixelShader() == this)
            graphics_->SetShaders(0, 0);
        
        ((IDirect3DPixelShader9*)object_)->Release();
        object_ = 0;
    }
}

void PixelShader::LoadParameters()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    if ((!cache) || (!graphics_))
        return;
    
    std::string shaderPath;
    std::string shaderName;
    std::string shaderExt;
    
    SplitPath(GetName(), shaderPath, shaderName, shaderExt);
    
    isSM3_ = (shaderExt.find('3') != std::string::npos);
    
    // Take the first part of the shader name (shader group)
    size_t index = 2;
    while ((index < shaderName.length()) && (shaderName[index] != '_'))
        index++;
    std::string shaderGroup = shaderName.substr(0, index);
    
    // Load shader information XML file
    XMLFile* file = cache->GetResource<XMLFile>(shaderPath + shaderGroup + ".xml");
    if (!file)
        return;
    
    // Update (global) parameter register mappings
    XMLElement shadersElem = file->GetRootElement();
    XMLElement paramsElem = shadersElem.GetChildElement("psparameters");
    XMLElement paramElem = paramsElem.GetChildElement("parameter");
    
    while (paramElem)
    {
        std::string name = paramElem.GetString("name");
        PSParameter param = graphics_->GetPSParameter(name);
        if (param != MAX_PS_PARAMETERS)
            graphics_->SetPSRegister(param, paramElem.GetInt("index"));
        else
            LOGERROR("Unknown pixel shader parameter " + name + " in " + GetName());
        
        paramElem = paramElem.GetNextElement("parameter");
    }
    
    // Get parameters and texture units used by this shader
    XMLElement shaderElem = shadersElem.GetChildElement("shader");
    while (shaderElem)
    {
        std::string name = shaderElem.GetString("name");
        std::string type = shaderElem.GetStringLower("type");
        
        if ((name == shaderName) && (type == "ps"))
        {
            for (unsigned i = 0; i < MAX_PS_PARAMETERS; ++i)
                useParameter_[i] = false;
            for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
                useTextureUnit_[i] = false;
            
            XMLElement shaderParamElem = shaderElem.GetChildElement("parameter");
            while (shaderParamElem)
            {
                std::string name = shaderParamElem.GetString("name");
                PSParameter param = graphics_->GetPSParameter(name);
                if (param != MAX_PS_PARAMETERS)
                    useParameter_[param] = true;
                
                shaderParamElem = shaderParamElem.GetNextElement("parameter");
            }
            
            XMLElement textureElem = shaderElem.GetChildElement("textureunit");
            while (textureElem)
            {
                std::string name = textureElem.GetString("name");
                TextureUnit unit = graphics_->GetTextureUnit(name);
                if (unit != MAX_TEXTURE_UNITS)
                    useTextureUnit_[unit] = true;
                else
                    LOGERROR("Unknown texture unit " + name + " in " + GetName());
                
                textureElem = textureElem.GetNextElement("textureunit");
            }
            
            return;
        }
        
        shaderElem = shaderElem.GetNextElement("shader");
    }
    
    LOGERROR("Shader " + shaderName + " not found in shader description XML file");
}
