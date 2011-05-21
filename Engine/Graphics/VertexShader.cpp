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
#include "Profiler.h"
#include "ResourceCache.h"
#include "SharedArrayPtr.h"
#include "VertexShader.h"
#include "XMLFile.h"

#include <ctype.h>

#include "DebugNew.h"

OBJECTTYPESTATIC(VertexShader);

VertexShader::VertexShader(Context* context) :
    Resource(context),
    GPUObject(GetSubsystem<Graphics>()),
    isSM3_(false)
{
    ClearParameters();
}

VertexShader::~VertexShader()
{
    Release();
}

void VertexShader::RegisterObject(Context* context)
{
    context->RegisterFactory<VertexShader>();
}

bool VertexShader::Load(Deserializer& source)
{
    PROFILE(LoadVertexShader);
    
    Release();
    
    if (!graphics_)
        return false;
    
    unsigned dataSize = source.GetSize();
    
    SharedArrayPtr<unsigned char> buffer(new unsigned char[dataSize]);
    source.Read((void*)buffer.GetPtr(), dataSize);
    
    IDirect3DDevice9* device = graphics_->GetImpl()->GetDevice();
    if ((!device) || (FAILED(graphics_->GetImpl()->GetDevice()->CreateVertexShader(
        (const DWORD*)buffer.GetPtr(),
        (IDirect3DVertexShader9**)&object_))))
    {
        LOGERROR("Could not create vertex shader " + GetName());
        return false;
    }
    
    SetMemoryUse(dataSize);
    LoadParameters();
    return true;
}

bool VertexShader::NeedParameterUpdate(VSParameter parameter, const void* source)
{
    if ((useParameter_[parameter]) && (graphics_->GetVSParameterSource(parameter) != source))
    {
        graphics_->SetVSParameterSource(parameter, source);
        return true;
    }
    return false;
}

void VertexShader::Release()
{
    if (object_)
    {
        if (!graphics_)
            return;
        
        if (graphics_->GetVertexShader() == this)
            graphics_->SetShaders(0, 0);
        
        ((IDirect3DVertexShader9*)object_)->Release();
        object_ = 0;
        
        SetMemoryUse(0);
    }
}

void VertexShader::LoadParameters()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    ClearParameters();
    
    String shaderPath, shaderName, shaderExt;
    SplitPath(GetName(), shaderPath, shaderName, shaderExt);
    
    isSM3_ = (shaderExt.Find('3') != String::NPOS);
    
    // Take the first part of the shader name (shader group)
    unsigned index = 2;
    while ((index < shaderName.Length()) && (shaderName[index] != '_'))
        ++index;
    String shaderGroup = shaderName.Substring(0, index);
    
    // Load shader information XML file
    XMLFile* file = cache->GetResource<XMLFile>(shaderPath + shaderGroup + ".xml");
    if (!file)
        return;
    
    // Update (global) parameter register mappings
    XMLElement shadersElem = file->GetRootElement();
    XMLElement paramsElem = shadersElem.GetChildElement("vsparameters");
    XMLElement paramElem = paramsElem.GetChildElement("parameter");
    
    while (paramElem)
    {
        String name = paramElem.GetString("name");
        VSParameter param = graphics_->GetVSParameter(name);
        if (param != MAX_VS_PARAMETERS)
            graphics_->SetVSRegister(param, paramElem.GetInt("index"));
        else
            LOGERROR("Unknown vertex shader parameter " + name + " in " + GetName());
        
        paramElem = paramElem.GetNextElement("parameter");
    }
    
    // Get parameters used by this shader
    XMLElement shaderElem = shadersElem.GetChildElement("shader");
    while (shaderElem)
    {
        String name = shaderElem.GetString("name");
        String type = shaderElem.GetStringLower("type");
        
        if ((name == shaderName) && (type == "vs"))
        {
            XMLElement shaderParamElem = shaderElem.GetChildElement("parameter");
            while (shaderParamElem)
            {
                String name = shaderParamElem.GetString("name");
                VSParameter param = graphics_->GetVSParameter(name);
                if (param != MAX_VS_PARAMETERS)
                    useParameter_[param] = true;
                
                shaderParamElem = shaderParamElem.GetNextElement("parameter");
            }
            
            return;
        }
        
        shaderElem = shaderElem.GetNextElement("shader");
    }
    
    LOGERROR("Shader " + shaderName + " not found in shader description XML file");
}

void VertexShader::ClearParameters()
{
    for (unsigned i = 0; i < MAX_VS_PARAMETERS; ++i)
        useParameter_[i] = false;
}
