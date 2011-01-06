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
#include "Log.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererImpl.h"
#include "ResourceCache.h"
#include "SharedArrayPtr.h"
#include "StringUtils.h"
#include "VertexShader.h"
#include "XMLFile.h"

#include <ctype.h>

#include "DebugNew.h"

std::map<std::string, VSParameter> VertexShader::sParameters;
unsigned VertexShader::sRegisters[MAX_VS_PARAMETERS];
const void* VertexShader::sLastParameterSources[MAX_VS_PARAMETERS];
bool VertexShader::sInitialized = false;

VertexShader::VertexShader(Renderer* renderer, const std::string& name) :
    Resource(name),
    GPUObject(renderer),
    mIsSM3(false)
{
    for (unsigned i = 0; i < MAX_VS_PARAMETERS; ++i)
        mUseParameter[i] = false;
}

VertexShader::~VertexShader()
{
    release();
}

void VertexShader::load(Deserializer& source, ResourceCache* cache)
{
    PROFILE(VertexShader_Load);
    
    release();
    
    if (!mRenderer)
        return;
    
    unsigned dataSize = source.getSize();
    setMemoryUse(dataSize);
    
    SharedArrayPtr<unsigned char> buffer(new unsigned char[dataSize]);
    source.read((void*)buffer.getPtr(), dataSize);
    
    if (FAILED(mRenderer->getImpl()->getDevice()->CreateVertexShader(
        (const DWORD*)buffer.getPtr(),
        (IDirect3DVertexShader9**)&mObject)))
        EXCEPTION("Could not create vertex shader " + getName());
    
    loadParameters(cache);
    
    mHash = *((unsigned short*)this) >> 2;
    // In state sorting, give priority to non-skinned shaders
    if (!mUseParameter[VSP_MODELSKINMATRICES])
        mHash |= 32768;
}

VSParameter VertexShader::getParameter(const std::string& name)
{
    initializeParameters();
    
    std::map<std::string, VSParameter>::iterator i = sParameters.find(name);
    if (i == sParameters.end())
        return MAX_VS_PARAMETERS;
    return i->second;
}

const std::string& VertexShader::getParameterName(VSParameter parameter)
{
    static const std::string noParameter;
    
    initializeParameters();
    
    for (std::map<std::string, VSParameter>::iterator i = sParameters.begin(); i != sParameters.end(); ++i)
    {
        if (i->second == parameter)
            return i->first;
    }
    return noParameter;
}

void VertexShader::clearLastParameterSources()
{
    for (unsigned i = 0; i < MAX_VS_PARAMETERS; ++i)
        sLastParameterSources[i] = (const void*)M_MAX_UNSIGNED;
}

void VertexShader::release()
{
    if (mObject)
    {
        if (!mRenderer)
        {
            LOGWARNING("Renderer has expired, skipping release of PixelShader");
            return;
        }
        
        if (mRenderer->getVertexShader() == this)
            mRenderer->setVertexShader(0);
        
        ((IDirect3DVertexShader9*)mObject)->Release();
        mObject = 0;
    }
}

void VertexShader::loadParameters(ResourceCache* cache)
{
    if (!cache)
        EXCEPTION("Null resource cache for VertexShader");
    
    initializeParameters();
    
    std::string shaderPath;
    std::string shaderName;
    std::string shaderExt;
    
    splitPath(getName(), shaderPath, shaderName, shaderExt);
    
    mIsSM3 = (shaderExt.find('3') != std::string::npos);
    
    // Take the first part of the shader name (shader group)
    size_t index = 2;
    while ((index < shaderName.length()) && (shaderName[index] != '_'))
        index++;
    std::string shaderGroup = shaderName.substr(0, index);
    
    // Load shader information XML file
    XMLFile* xml = cache->getResource<XMLFile>(shaderPath + shaderGroup + ".xml");
    
    // Update (global) parameter register mappings
    XMLElement shadersElem = xml->getRootElement();
    XMLElement paramsElem = shadersElem.getChildElement("vsparameters", false);
    XMLElement paramElem = paramsElem.getChildElement("parameter", false);
    
    while (paramElem.notNull())
    {
        std::string name = paramElem.getString("name");
        if (sParameters.find(name) == sParameters.end())
            EXCEPTION("Unknown vertex shader parameter " + name + " in " + getName());
        
        sRegisters[sParameters[name]] = paramElem.getInt("index");
        
        paramElem = paramElem.getNextElement("parameter");
    }
    
    // Get parameters and texture units used by this shader
    XMLElement shaderElem = shadersElem.getChildElement("shader", false);
    while (shaderElem.notNull())
    {
        std::string name = shaderElem.getString("name");
        std::string type = shaderElem.getStringLower("type");
        
        if ((name == shaderName) && (type == "vs"))
        {
            for (unsigned i = 0; i < MAX_VS_PARAMETERS; ++i)
                mUseParameter[i] = false;
            
            XMLElement shaderParamElem = shaderElem.getChildElement("parameter", false);
            while (shaderParamElem.notNull())
            {
                std::string name = shaderParamElem.getString("name");
                mUseParameter[sParameters[name]] = true;
                shaderParamElem = shaderParamElem.getNextElement("parameter");
            }
            
            return;
        }
        
        shaderElem = shaderElem.getNextElement("shader");
    }
    
    EXCEPTION("Shader " + shaderName + " not found in shader description XML file");
}

void VertexShader::initializeParameters()
{
    if (sInitialized)
        return;
    
    // Initialize all parameters as unknown
    for (unsigned i = 0; i < MAX_VS_PARAMETERS; ++i)
        sRegisters[i] = MAX_CONSTANT_REGISTERS;
    
    // Map parameter names
    sParameters["AmbientColor"] = VSP_AMBIENTCOLOR;
    sParameters["DepthMode"] = VSP_DEPTHMODE;
    sParameters["ElapsedTime"] = VSP_ELAPSEDTIME;
    sParameters["FrustumSize"] = VSP_FRUSTUMSIZE;
    sParameters["GBufferOffsets"] = VSP_GBUFFEROFFSETS;
    sParameters["Model"] = VSP_MODEL;
    sParameters["ModelViewProj"] = VSP_MODELVIEWPROJ;
    sParameters["ShadowProj"] = VSP_SHADOWPROJ;
    sParameters["SpotProj"] = VSP_SPOTPROJ;
    sParameters["ViewInverse"] = VSP_VIEWINVERSE;
    sParameters["ViewProj"] = VSP_VIEWPROJ;
    sParameters["UOffset"] = VSP_UOFFSET;
    sParameters["VOffset"] = VSP_VOFFSET;
    sParameters["ViewRightVector"] = VSP_VIEWRIGHTVECTOR;
    sParameters["ViewUpVector"] = VSP_VIEWUPVECTOR;
    sParameters["ModelSkinMatrices"] = VSP_MODELSKINMATRICES;
    sParameters["ModelInstances"] = VSP_MODELINSTANCES;
    
    sInitialized = true;
}
