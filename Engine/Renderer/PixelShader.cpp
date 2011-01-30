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
#include "PixelShader.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererImpl.h"
#include "ResourceCache.h"
#include "SharedArrayPtr.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include <ctype.h>

#include "DebugNew.h"

std::map<std::string, PSParameter> PixelShader::sParameters;
std::map<std::string, TextureUnit> PixelShader::sTextureUnits;
unsigned PixelShader::sRegisters[MAX_PS_PARAMETERS];
const void* PixelShader::sLastParameterSources[MAX_PS_PARAMETERS];
bool PixelShader::sInitialized = false;

PixelShader::PixelShader(Renderer* renderer, const std::string& name) :
    Resource(name),
    GPUObject(renderer),
    mHash(0),
    mIsSM3(false)
{
    for (unsigned i = 0; i < MAX_PS_PARAMETERS; ++i)
        mUseParameter[i] = false;
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        mUseTextureUnit[i] = false;
}

PixelShader::~PixelShader()
{
    release();
}

void PixelShader::load(Deserializer& source, ResourceCache* cache)
{
    PROFILE(PixelShader_Load);
    
    release();
    
    if (!mRenderer)
        return;
    
    unsigned dataSize = source.getSize();
    setMemoryUse(dataSize);
    
    SharedArrayPtr<unsigned char> buffer(new unsigned char[dataSize]);
    source.read((void*)buffer.getPtr(), dataSize);
    
    if (FAILED(mRenderer->getImpl()->getDevice()->CreatePixelShader(
        (const DWORD*)buffer.getPtr(), 
        (IDirect3DPixelShader9**)&mObject)))
        EXCEPTION("Could not create pixel shader " + getName());
    
    loadParameters(cache);
    
    mHash = *((unsigned short*)this) >> 2;
}

void PixelShader::release()
{
    if (mObject)
    {
        if (!mRenderer)
        {
            LOGWARNING("Renderer has expired, skipping release of PixelShader");
            return;
        }
        
        if (mRenderer->getPixelShader() == this)
            mRenderer->setPixelShader(0);
        
        ((IDirect3DPixelShader9*)mObject)->Release();
        mObject = 0;
    }
}

PSParameter PixelShader::getParameter(const std::string& name)
{
    initializeParameters();
    
    std::map<std::string, PSParameter>::iterator i = sParameters.find(name);
    if (i == sParameters.end())
        return MAX_PS_PARAMETERS;
    return i->second;
}

const std::string& PixelShader::getParameterName(PSParameter parameter)
{
    static const std::string noParameter;
    
    initializeParameters();
    
    for (std::map<std::string, PSParameter>::iterator i = sParameters.begin(); i != sParameters.end(); ++i)
    {
        if (i->second == parameter)
            return i->first;
    }
    return noParameter;
}

void PixelShader::clearLastParameterSources()
{
    for (unsigned i = 0; i < MAX_PS_PARAMETERS; ++i)
        sLastParameterSources[i] = (const void*)M_MAX_UNSIGNED;
}

void PixelShader::loadParameters(ResourceCache* cache)
{
    if (!cache)
        return;
    
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
    XMLElement paramsElem = shadersElem.getChildElement("psparameters");
    XMLElement paramElem = paramsElem.getChildElement("parameter");
    
    while (paramElem)
    {
        std::string name = paramElem.getString("name");
        if (sParameters.find(name) == sParameters.end())
            LOGERROR("Unknown pixel shader parameter " + name + " in " + getName());
        else
            sRegisters[sParameters[name]] = paramElem.getInt("index");
        
        paramElem = paramElem.getNextElement("parameter");
    }
    
    // Get parameters and texture units used by this shader
    XMLElement shaderElem = shadersElem.getChildElement("shader");
    while (shaderElem)
    {
        std::string name = shaderElem.getString("name");
        std::string type = shaderElem.getStringLower("type");
        
        if ((name == shaderName) && (type == "ps"))
        {
            for (unsigned i = 0; i < MAX_PS_PARAMETERS; ++i)
                mUseParameter[i] = false;
            for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
                mUseTextureUnit[i] = false;
            
            XMLElement shaderParamElem = shaderElem.getChildElement("parameter");
            while (shaderParamElem)
            {
                std::string name = shaderParamElem.getString("name");
                mUseParameter[sParameters[name]] = true;
                shaderParamElem = shaderParamElem.getNextElement("parameter");
            }
            
            XMLElement textureElem = shaderElem.getChildElement("textureunit");
            while (textureElem)
            {
                std::string name = textureElem.getString("name");
                if (sTextureUnits.find(name) == sTextureUnits.end())
                    LOGERROR("Unknown texture unit " + name + " in " + getName());
                else
                    mUseTextureUnit[sTextureUnits[name]] = true;
                textureElem = textureElem.getNextElement("textureunit");
            }
            
            return;
        }
        
        shaderElem = shaderElem.getNextElement("shader");
    }
    
    LOGERROR("Shader " + shaderName + " not found in shader description XML file");
}

void PixelShader::initializeParameters()
{
    if (sInitialized)
        return;
    
    // Initialize all parameters as unknown
    for (unsigned i = 0; i < MAX_PS_PARAMETERS; ++i)
        sRegisters[i] = MAX_CONSTANT_REGISTERS;
    
    // Map parameter names
    sParameters["AmbientColorPS"] = PSP_AMBIENTCOLOR;
    sParameters["DepthReconstruct"] = PSP_DEPTHRECONSTRUCT;
    sParameters["EdgeFilterParams"] = PSP_EDGEFILTERPARAMS;
    sParameters["ElapsedTimePS"] = PSP_ELAPSEDTIME;
    sParameters["FogColor"] = PSP_FOGCOLOR;
    sParameters["FogParams"] = PSP_FOGPARAMS;
    sParameters["LightAtten"] = PSP_LIGHTATTEN;
    sParameters["LightColor"] = PSP_LIGHTCOLOR;
    sParameters["LightDir"] = PSP_LIGHTDIR;
    sParameters["LightPos"] = PSP_LIGHTPOS;
    sParameters["LightSplits"] = PSP_LIGHTSPLITS;
    sParameters["MatDiffColor"] = PSP_MATDIFFCOLOR;
    sParameters["MatEmissiveColor"] = PSP_MATEMISSIVECOLOR;
    sParameters["MatSpecProperties"] = PSP_MATSPECPROPERTIES;
    sParameters["SampleOffsets"] = PSP_SAMPLEOFFSETS;
    sParameters["ShadowProjPS"] = PSP_SHADOWPROJ;
    sParameters["SpotProjPS"] = PSP_SPOTPROJ;
    
    // Map texture units
    sTextureUnits["NormalMap"] = TU_NORMAL;
    sTextureUnits["DiffMap"] = TU_DIFFUSE;
    sTextureUnits["DiffCubeMap"] = TU_DIFFUSE;
    sTextureUnits["SpecMap"] = TU_SPECULAR;
    sTextureUnits["EmissiveMap"] = TU_EMISSIVE;
    sTextureUnits["DetailMap"] = TU_DETAIL;
    sTextureUnits["EnvironmentMap"] = TU_ENVIRONMENT;
    sTextureUnits["EnvironmentCubeMap"] = TU_ENVIRONMENT;
    sTextureUnits["LightRampMap"] = TU_LIGHTRAMP;
    sTextureUnits["LightSpotMap"] = TU_LIGHTSPOT;
    sTextureUnits["LightCubeMap"]  = TU_LIGHTSPOT;
    sTextureUnits["ShadowMap"] = TU_SHADOWMAP;
    sTextureUnits["DiffBuffer"] = TU_DIFFBUFFER;
    sTextureUnits["NormalBuffer"] = TU_NORMALBUFFER;
    sTextureUnits["DepthBuffer"] = TU_DEPTHBUFFER;
    sTextureUnits["LightBuffer"] = TU_LIGHTBUFFER;
    
    sInitialized = true;
}
