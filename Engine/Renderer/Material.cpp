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
#include "Material.h"
#include "Matrix4x3.h"
#include "PixelShader.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "VertexShader.h"
#include "XMLFile.h"

#include "DebugNew.h"

static const std::string passNames[] =
{
    "deferred",
    "prepass",
    "material",
    "emissive",
    "postopaque",
    "ambient",
    "negative",
    "light",
    "shadow"
};

static const std::string textureUnitNames[] =
{
    "diffuse",
    "normal",
    "specular",
    "detail",
    "environment",
    "emissive",
    "lightramp", // Not defined by materials
    "lightspot" // Not defined by materials
};

static const std::string blendModeNames[] =
{
    "replace",
    "add",
    "multiply",
    "alpha",
    "addalpha",
    "premulalpha",
    "invdestalpha"
};

static const std::string cullModeNames[] =
{
    "none",
    "ccw",
    "cw"
};

static const std::string compareModeNames[] =
{
    "always",
    "equal",
    "notequal",
    "less",
    "lessequal",
    "greater",
    "greaterequal"
};

MaterialPass::MaterialPass() :
    mParent(0),
    mAlphaMask(false),
    mAlphaTest(false),
    mBlendMode(BLEND_REPLACE),
    mCullMode(CULL_CCW),
    mDepthTestMode(CMP_LESSEQUAL),
    mDepthWrite(true)
{
}

MaterialPass::~MaterialPass()
{
}

void MaterialPass::setAlphaMask(bool enable)
{
    mAlphaMask = enable;
    if (mParent)
        mParent->setDirty();
}

void MaterialPass::setAlphaTest(bool enable)
{
    mAlphaTest = enable;
    if (mParent)
        mParent->setDirty();
}

void MaterialPass::setBlendMode(BlendMode mode)
{
    mBlendMode = mode;
    if (mParent)
        mParent->setDirty();
}

void MaterialPass::setCullMode(CullMode mode)
{
    mCullMode = mode;
    if (mParent)
        mParent->setDirty();
}

void MaterialPass::setDepthTestMode(CompareMode mode)
{
    mDepthTestMode = mode;
    if (mParent)
        mParent->setDirty();
}

void MaterialPass::setDepthWrite(bool enable)
{
    mDepthWrite = enable;
    if (mParent)
        mParent->setDirty();
}

void MaterialPass::setVertexShader(const std::string& name)
{
    mVertexShaderName = name;
    releaseShaders();
    if (mParent)
        mParent->setDirty();
}

void MaterialPass::setPixelShader(const std::string& name)
{
    mPixelShaderName = name;
    releaseShaders();
    if (mParent)
        mParent->setDirty();
}

void MaterialPass::releaseShaders()
{
    mVertexShaders.clear();
    mPixelShaders.clear();
}

void MaterialPass::setParent(Material* parent)
{
    mParent = parent;
}

MaterialTechnique::MaterialTechnique() :
    mParent(0),
    mQualityLevel(0),
    mLodDistance(0.0f),
    mRequireSM3(false),
    mShadersLoadedFrameNumber(M_MAX_UNSIGNED),
    mAuxViewFrameNumber(M_MAX_UNSIGNED)
{
    mTextures.resize(MAX_MATERIAL_TEXTURE_UNITS);
    
    // Setup often used defaults
    mVSParameters[VSP_UOFFSET] = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
    mVSParameters[VSP_VOFFSET] = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
    mPSParameters[PSP_MATDIFFCOLOR] = Vector4::sUnity;
    mPSParameters[PSP_MATEMISSIVECOLOR] = Vector4::sZero;
    mPSParameters[PSP_MATSPECPROPERTIES] = Vector4::sZero;
}

MaterialTechnique::~MaterialTechnique()
{
}

void MaterialTechnique::setQualityLevel(int quality)
{
    mQualityLevel = quality;
}

void MaterialTechnique::setLodDistance(float distance)
{
    mLodDistance = distance;
}

void MaterialTechnique::setRequireSM3(bool enable)
{
    mRequireSM3 = enable;
}

void MaterialTechnique::setVertexShaderParameter(VSParameter parameter, const Vector4& value)
{
    mVSParameters[parameter] = value;
}

void MaterialTechnique::setPixelShaderParameter(PSParameter parameter, const Vector4& value)
{
    mPSParameters[parameter] = value;
}

void MaterialTechnique::setTexture(TextureUnit unit, Texture* texture)
{
    if (unit >= MAX_MATERIAL_TEXTURE_UNITS)
        return;
    
    mTextures[unit] = texture;
}

void MaterialTechnique::setUVTransform(const Vector2& offset, float rotation, const Vector2& repeat)
{
    Matrix4x3 transform = Matrix4x3::sIdentity;
    transform.m00 = repeat.mX;
    transform.m11 = repeat.mY;
    transform.m03 = -0.5f * transform.m00 + 0.5f;
    transform.m13 = -0.5f * transform.m11 + 0.5f;
    
    Matrix4x3 rotationMatrix = Matrix4x3::sIdentity;
    float angleRad = rotation * M_DEGTORAD;
    rotationMatrix.m00 = cosf(angleRad);
    rotationMatrix.m01 = sinf(angleRad);
    rotationMatrix.m10 = -rotationMatrix.m01;
    rotationMatrix.m11 = rotationMatrix.m00;
    rotationMatrix.m03 = 0.5f - 0.5f * (rotationMatrix.m00 + rotationMatrix.m01);
    rotationMatrix.m13 = 0.5f - 0.5f * (rotationMatrix.m10 + rotationMatrix.m11);
    
    transform = rotationMatrix * transform;
    
    Matrix4x3 offsetMatrix = Matrix4x3::sIdentity;
    offsetMatrix.m03 = offset.mX;
    offsetMatrix.m13 = offset.mY;
    
    transform = offsetMatrix * transform;
    
    Vector4& uOffset = mVSParameters[VSP_UOFFSET];
    Vector4& vOffset = mVSParameters[VSP_VOFFSET];
    uOffset.mX = transform.m00;
    uOffset.mY = transform.m01;
    uOffset.mW = transform.m03;
    vOffset.mX = transform.m10;
    vOffset.mY = transform.m11;
    vOffset.mW = transform.m13;
}

void MaterialTechnique::setUVTransform(const Vector2& offset, float rotation, float repeat)
{
    setUVTransform(offset, rotation, Vector2(repeat, repeat));
}

void MaterialTechnique::releaseShaders()
{
    for (std::map<PassType, MaterialPass>::iterator i = mPasses.begin(); i != mPasses.end(); ++i)
        i->second.releaseShaders();
}

MaterialPass* MaterialTechnique::createPass(PassType pass)
{
    MaterialPass* existing = getPass(pass);
    if (existing)
        return existing;
    
    MaterialPass newPass;
    newPass.setParent(mParent);
    mPasses[pass] = newPass;
    
    return getPass(pass);
}

void MaterialTechnique::removePass(PassType pass)
{
    mPasses.erase(pass);
}

void MaterialTechnique::setParent(Material* parent)
{
    mParent = parent;
    
    for (std::map<PassType, MaterialPass>::iterator i = mPasses.begin(); i != mPasses.end(); ++i)
        i->second.setParent(parent);
}

void MaterialTechnique::markForAuxView(unsigned frameNumber)
{
    mAuxViewFrameNumber = frameNumber;
}

void MaterialTechnique::markShadersLoaded(unsigned frameNumber)
{
    mShadersLoadedFrameNumber = frameNumber;
}

Texture* MaterialTechnique::getTexture(TextureUnit unit) const
{
    if ((unsigned)unit >= mTextures.size())
        return 0;
    
    return mTextures[unit];
}

Material::Material(const std::string& name) :
    Resource(name),
    mDirty(true),
    mCastShadows(false),
    mOcclusion(true),
    mOcclusionCullMode(CULL_CCW)
{
    setNumTechniques(1);
}

Material::~Material()
{
}

void Material::load(Deserializer& source, ResourceCache* cache)
{
    PROFILE(Material_Load);
    
    XMLFile xml;
    xml.load(source, cache);
    
    XMLElement rootElem = xml.getRootElement();
    // Check for base material and inherit all settings, techniques and passes
    XMLElement baseElem = rootElem.getChildElement("base");
    if (baseElem)
    {
        Material* baseMaterial = cache->getResource<Material>(baseElem.getString("name"));
        mTechniques = baseMaterial->mTechniques;
        
        // Reparent, and release all shaders, because they most likely will be different in the new material
        for (unsigned i = 0; i < mTechniques.size(); ++i)
        {
            mTechniques[i].setParent(this);
            mTechniques[i].releaseShaders();
        }
    }
    else
        mTechniques.clear();
    
    XMLElement techniqueElem = rootElem.getChildElement("technique");
    unsigned index = 0;
    while (techniqueElem)
    {
        if (mTechniques.size() < index + 1)
            setNumTechniques(index + 1);
        
        MaterialTechnique& newTechnique = mTechniques[index];
        
        if (techniqueElem.hasAttribute("quality"))
            newTechnique.setQualityLevel(techniqueElem.getInt("quality"));
        if (techniqueElem.hasAttribute("loddistance"))
            newTechnique.setLodDistance(techniqueElem.getFloat("loddistance"));
        if (techniqueElem.hasAttribute("sm3"))
            newTechnique.setRequireSM3(techniqueElem.getBool("sm3"));
        
        XMLElement textureElem = techniqueElem.getChildElement("texture");
        while (textureElem)
        {
            TextureUnit unit = TU_DIFFUSE;
            if (textureElem.hasAttribute("unit"))
            {
                std::string unitName = textureElem.getStringLower("unit");
                unit = (TextureUnit)getIndexFromStringList(unitName, textureUnitNames, MAX_MATERIAL_TEXTURE_UNITS,
                    MAX_MATERIAL_TEXTURE_UNITS);
                if (unitName == "diff")
                    unit = TU_DIFFUSE;
                if (unitName == "norm")
                    unit = TU_NORMAL;
                if (unitName == "spec")
                    unit = TU_SPECULAR;
                if (unitName == "env")
                    unit = TU_ENVIRONMENT;
                if (unit == MAX_MATERIAL_TEXTURE_UNITS)
                    LOGERROR("Unknown texture unit " + unitName);
            }
            if (unit != MAX_MATERIAL_TEXTURE_UNITS)
            {
                std::string name = textureElem.getString("name");
                // Detect cube maps by file extension: they are defined by an XML file
                if (getExtension(name) == ".xml")
                    newTechnique.setTexture(unit, cache->getResource<TextureCube>(name));
                else
                    newTechnique.setTexture(unit, cache->getResource<Texture2D>(name));
            }
            textureElem = textureElem.getNextElement("texture");
        }
        
        XMLElement parameterElem = techniqueElem.getChildElement("parameter");
        while (parameterElem)
        {
            std::string name = parameterElem.getString("name");
            Vector4 value = parameterElem.getVector("value");
            VSParameter vsParam = VertexShader::getParameter(name);
            if (vsParam != MAX_VS_PARAMETERS)
                newTechnique.setVertexShaderParameter(vsParam, value);
            else
            {
                PSParameter psParam = PixelShader::getParameter(name);
                if (psParam != MAX_PS_PARAMETERS)
                    newTechnique.setPixelShaderParameter(psParam, value);
                else
                    LOGERROR("Unknown shader parameter " + name);
            }
            
            parameterElem = parameterElem.getNextElement("parameter");
        }
        
        XMLElement passElem = techniqueElem.getChildElement("pass");
        while (passElem)
        {
            PassType type = MAX_PASSES;
            if (passElem.hasAttribute("name"))
            {
                std::string name = passElem.getStringLower("name");
                type = (PassType)getIndexFromStringList(name, passNames, MAX_PASSES, MAX_PASSES);
                if (name == "gbuffer")
                    type = PASS_DEFERRED;
                if (name == "custom")
                    type = PASS_POSTOPAQUE;
                if (type == MAX_PASSES)
                    LOGERROR("Unknown pass " + name);
            }
            else
                LOGERROR("Missing pass name");
            
            if (type != MAX_PASSES)
            {
                MaterialPass& newPass = *newTechnique.createPass(type);
                
                if (passElem.hasAttribute("vs"))
                    newPass.setVertexShader(passElem.getString("vs"));
                
                if (passElem.hasAttribute("ps"))
                    newPass.setPixelShader(passElem.getString("ps"));
                
                if (passElem.hasAttribute("alphamask"))
                    newPass.setAlphaMask(passElem.getBool("alphamask"));
                
                if (passElem.hasAttribute("alphatest"))
                    newPass.setAlphaTest(passElem.getBool("alphatest"));
                
                if (passElem.hasAttribute("blend"))
                {
                    std::string blend = passElem.getStringLower("blend");
                    newPass.setBlendMode((BlendMode)getIndexFromStringList(blend, blendModeNames, MAX_BLENDMODES, BLEND_REPLACE));
                }
                
                if (passElem.hasAttribute("cull"))
                {
                    std::string cull = passElem.getStringLower("cull");
                    newPass.setCullMode((CullMode)getIndexFromStringList(cull, cullModeNames, MAX_CULLMODES, CULL_CCW));
                }
                
                if (passElem.hasAttribute("depthtest"))
                {
                    std::string depthTest = passElem.getStringLower("depthtest");
                    if (depthTest == "false")
                        newPass.setDepthTestMode(CMP_ALWAYS);
                    else
                        newPass.setDepthTestMode((CompareMode)getIndexFromStringList(depthTest, compareModeNames, MAX_COMPAREMODES,
                            CMP_LESSEQUAL));
                }
                
                if (passElem.hasAttribute("depthwrite"))
                    newPass.setDepthWrite(passElem.getBool("depthwrite"));
                
                // Undefine a pass by setting empty vertex or pixel shader name
                if ((newPass.getVertexShaderName().empty()) || (newPass.getPixelShaderName().empty()))
                    newTechnique.removePass(type);
            }
            
            passElem = passElem.getNextElement("pass");
        }
        
        techniqueElem = techniqueElem.getNextElement("technique");
        ++index;
    }
    
    // Calculate memory use
    unsigned memoryUse = 0;
    memoryUse += sizeof(Material);
    for (unsigned i = 0; i < mTechniques.size(); ++i)
    {
        MaterialTechnique& technique = mTechniques[i];
        memoryUse += sizeof(MaterialTechnique);
        memoryUse += technique.getTextures().size() * sizeof(SharedPtr<Texture>);
        memoryUse += technique.getVertexShaderParameters().size() * (sizeof(VSParameter) + sizeof(Vector4));
        memoryUse += technique.getPixelShaderParameters().size() * (sizeof(PSParameter) + sizeof(Vector4));
        
        const std::map<PassType, MaterialPass>& passes = technique.getPasses();
        for (std::map<PassType, MaterialPass>::const_iterator j = passes.begin(); j != passes.end(); ++j)
            memoryUse += sizeof(MaterialPass);
    }
    setMemoryUse(memoryUse);
    setDirty();
}

void Material::save(Serializer& dest)
{
    XMLFile xml;
    XMLElement materialElem = xml.createRootElement("material");
    
    // Write techniques
    for (unsigned i = 0; i < mTechniques.size(); ++i)
    {
        MaterialTechnique& technique = mTechniques[i];
        XMLElement techniqueElem = materialElem.createChildElement("technique");
        
        // Write quality & lod settings
        if (technique.getQualityLevel() != 0)
            techniqueElem.setInt("quality", technique.getQualityLevel());
        if (technique.getLodDistance() != 0.0f)
            techniqueElem.setFloat("loddistance", technique.getLodDistance());
        if (technique.getRequireSM3())
            techniqueElem.setBool("sm3", true);
        
        // Write texture units
        for (unsigned j = 0; j < MAX_MATERIAL_TEXTURE_UNITS; ++j)
        {
            Texture* texture = technique.getTexture((TextureUnit)j);
            if (texture)
            {
                XMLElement textureElem = techniqueElem.createChildElement("texture");
                textureElem.setString("unit", textureUnitNames[j]);
                textureElem.setString("name", texture->getName());
            }
        }
        
        // Write shader parameters. Exclude default values to keep output simpler
        const std::map<VSParameter, Vector4>& vsParameters = technique.getVertexShaderParameters();
        for (std::map<VSParameter, Vector4>::const_iterator j = vsParameters.begin(); j != vsParameters.end(); ++j)
        {
            if ((j->first == VSP_UOFFSET) && (j->second == Vector4(1.0f, 0.0f, 0.0f, 0.0f)))
                continue;
            if ((j->first == VSP_VOFFSET) && (j->second == Vector4(0.0f, 1.0f, 0.0f, 0.0f)))
                continue;
            XMLElement parameterElem = techniqueElem.createChildElement("parameter");
            parameterElem.setString("name", VertexShader::getParameterName(j->first));
            parameterElem.setVector4("value", j->second);
        }
        const std::map<PSParameter, Vector4>& psParameters = technique.getPixelShaderParameters();
        for (std::map<PSParameter, Vector4>::const_iterator j = psParameters.begin(); j != psParameters.end(); ++j)
        {
            if ((j->first == PSP_MATDIFFCOLOR) && (j->second == Vector4::sUnity))
                continue;
            if ((j->first == PSP_MATEMISSIVECOLOR) && (j->second == Vector4::sZero))
                continue;
            if ((j->first == PSP_MATSPECPROPERTIES) && (j->second == Vector4::sZero))
                continue;
            XMLElement parameterElem = techniqueElem.createChildElement("parameter");
            parameterElem.setString("name", PixelShader::getParameterName(j->first));
            parameterElem.setVector4("value", j->second);
        }
        
        // Write passes
        const std::map<PassType, MaterialPass>& passes = technique.getPasses();
        for (std::map<PassType, MaterialPass>::const_iterator j = passes.begin(); j != passes.end(); ++j)
        {
            XMLElement passElem = techniqueElem.createChildElement("pass");
            passElem.setString("name", getPassName(j->first));
            
            passElem.setString("vs", j->second.getVertexShaderName());
            passElem.setString("ps", j->second.getPixelShaderName());
            
            // Exclude default values to keep output simpler
            if (j->second.getAlphaMask())
                passElem.setBool("alphamask", true);
            if (j->second.getAlphaTest())
                passElem.setBool("alphatest", true);
            if (j->second.getBlendMode() != BLEND_REPLACE)
                passElem.setString("blend", blendModeNames[j->second.getBlendMode()]);
            if (j->second.getCullMode() != CULL_CCW)
                passElem.setString("cull", cullModeNames[j->second.getCullMode()]);
            if (j->second.getDepthTestMode() != CMP_LESSEQUAL)
                passElem.setString("depthtest", compareModeNames[j->second.getDepthTestMode()]);
            if (!j->second.getDepthWrite())
                passElem.setBool("depthwrite", false);
        }
    }
    
    xml.save(dest);
}

void Material::setNumTechniques(unsigned num)
{
    if (!num)
        return;
    
    mTechniques.resize(num);
    
    for (unsigned i = 0; i < mTechniques.size(); ++i)
        mTechniques[i].setParent(this);
}

void Material::setVertexShaderParameter(VSParameter parameter, const Vector4& value)
{
    for (unsigned i = 0; i < mTechniques.size(); ++i)
        mTechniques[i].setVertexShaderParameter(parameter, value);
}

void Material::setPixelShaderParameter(PSParameter parameter, const Vector4& value)
{
    for (unsigned i = 0; i < mTechniques.size(); ++i)
        mTechniques[i].setPixelShaderParameter(parameter, value);
}

void Material::setTexture(TextureUnit unit, Texture* texture)
{
    for (unsigned i = 0; i < mTechniques.size(); ++i)
        mTechniques[i].setTexture(unit, texture);
}

void Material::setUVTransform(const Vector2& offset, float rotation, const Vector2& repeat)
{
    for (unsigned i = 0; i < mTechniques.size(); ++i)
        mTechniques[i].setUVTransform(offset, rotation, repeat);
}

void Material::setUVTransform(const Vector2& offset, float rotation, float repeat)
{
    for (unsigned i = 0; i < mTechniques.size(); ++i)
        mTechniques[i].setUVTransform(offset, rotation, repeat);
}

void Material::releaseShaders()
{
    for (unsigned i = 0; i < mTechniques.size(); ++i)
        mTechniques[i].releaseShaders();
}

void Material::setDirty()
{
    mDirty = true;
}

SharedPtr<Material> Material::clone(const std::string& cloneName) const
{
    SharedPtr<Material> ret(new Material(cloneName));
    
    ret->mTechniques = mTechniques;
    ret->mCastShadows = mCastShadows;
    ret->mOcclusion = mOcclusion;
    ret->mOcclusionCullMode = mOcclusionCullMode;
    
    // Reparent, and release shaders from the clone, in case they will be set different
    for (unsigned i = 0; i < ret->mTechniques.size(); ++i)
    {
        ret->mTechniques[i].setParent(ret);
        ret->mTechniques[i].releaseShaders();
    }
    
    return ret;
}

MaterialTechnique* Material::getTechnique(unsigned index)
{
    return index < mTechniques.size() ? &mTechniques[index] : 0;
}

MaterialPass* Material::getPass(unsigned technique, PassType pass)
{
    if (technique >= mTechniques.size())
        return 0;
    
    return mTechniques[technique].getPass(pass);
}

const std::string& Material::getPassName(PassType pass)
{
    return passNames[pass];
}

const std::string& Material::getTextureUnitName(TextureUnit unit)
{
    return textureUnitNames[unit];
}

bool Material::getCastShadows()
{
    if (mDirty)
        update();
    
    return mCastShadows;
}

bool Material::getOcclusion()
{
    if (mDirty)
        update();
    
    return mOcclusion;
}

CullMode Material::getOcclusionCullMode()
{
    if (mDirty)
        update();
    
    return mOcclusionCullMode;
}

void Material::update()
{
    // Report true if any of the material's techniques casts shadows
    mCastShadows = false;
    for (unsigned i = 0; i < mTechniques.size(); ++i)
    {
        if (mTechniques[i].hasPass(PASS_SHADOW))
        {
            mCastShadows = true;
            break;
        }
    }
    
    // Determine occlusion by checking the first pass of each technique
    mOcclusion = false;
    for (unsigned i = 0; i < mTechniques.size(); ++i)
    {
        const std::map<PassType, MaterialPass>& passes = mTechniques[i].getPasses();
        if (!passes.empty())
        {
            // If pass writes depth, enable occlusion
            const MaterialPass& pass = passes.begin()->second;
            if (pass.getDepthWrite())
            {
                mOcclusion = true;
                mOcclusionCullMode = pass.getCullMode();
                break;
            }
        }
    }
    
    mDirty = false;
}
