//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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
#include "Log.h"
#include "Material.h"
#include "Matrix3x4.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "Technique.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

const String textureUnitNames[] =
{
    "diffuse",
    "normal",
    "specular",
    "emissive",
    "environment",
    ""
};

static const String cullModeNames[] =
{
    "none",
    "ccw",
    "cw",
    ""
};

TextureUnit ParseTextureUnitName(const String& name)
{
    TextureUnit unit = (TextureUnit)GetStringListIndex(name, textureUnitNames, MAX_MATERIAL_TEXTURE_UNITS);
    if (name == "diff")
        unit = TU_DIFFUSE;
    else if (name == "norm")
        unit = TU_NORMAL;
    else if (name == "spec")
        unit = TU_SPECULAR;
    else if (name == "env")
        unit = TU_ENVIRONMENT;
    
    return unit;
}

static TechniqueEntry noEntry;

TechniqueEntry::TechniqueEntry() :
    qualityLevel_(0),
    lodDistance_(0.0f)
{
}

TechniqueEntry::TechniqueEntry(Technique* tech, unsigned qualityLevel, float lodDistance) :
    technique_(tech),
    qualityLevel_(qualityLevel),
    lodDistance_(lodDistance)
{
}

TechniqueEntry::~TechniqueEntry()
{
}

OBJECTTYPESTATIC(Material);

Material::Material(Context* context) :
    Resource(context),
    cullMode_(CULL_CCW),
    shadowCullMode_(CULL_CCW),
    depthBias_(BiasParameters(0.0f, 0.0f)),
    auxViewFrameNumber_(0),
    occlusion_(true),
    specular_(false)
{
    SetNumTechniques(1);
    
    // Setup often used default parameters
    SetShaderParameter("UOffset", Vector4(1.0f, 0.0f, 0.0f, 0.0f));
    SetShaderParameter("VOffset", Vector4(0.0f, 1.0f, 0.0f, 0.0f));
    SetShaderParameter("MatDiffColor", Vector4::ONE);
    SetShaderParameter("MatEmissiveColor", Vector4::ZERO);
    SetShaderParameter("MatEnvMapColor", Vector4::ONE);
    SetShaderParameter("MatSpecColor", Vector4(0.0f, 0.0f, 0.0f, 1.0f));
}

Material::~Material()
{
}

void Material::RegisterObject(Context* context)
{
    context->RegisterFactory<Material>();
}

bool Material::Load(Deserializer& source)
{
    PROFILE(LoadMaterial);
    
    // In headless mode, do not actually load the material, just return success
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics)
        return true;
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(source))
        return false;
    
    XMLElement rootElem = xml->GetRoot();
    XMLElement techniqueElem = rootElem.GetChild("technique");
    techniques_.Clear();
    while (techniqueElem)
    {
        Technique* tech = cache->GetResource<Technique>(techniqueElem.GetAttribute("name"));
        if (tech)
        {
            TechniqueEntry newTechnique;
            newTechnique.technique_ = tech;
            if (techniqueElem.HasAttribute("quality"))
                newTechnique.qualityLevel_ = techniqueElem.GetInt("quality");
            if (techniqueElem.HasAttribute("loddistance"))
                newTechnique.lodDistance_ = techniqueElem.GetFloat("loddistance");
            techniques_.Push(newTechnique);
        }
        techniqueElem = techniqueElem.GetNext("technique");
    }
    
    XMLElement textureElem = rootElem.GetChild("texture");
    while (textureElem)
    {
        TextureUnit unit = TU_DIFFUSE;
        if (textureElem.HasAttribute("unit"))
        {
            String unitName = textureElem.GetAttributeLower("unit");
            if (unitName.Length() > 1)
            {
                unit = ParseTextureUnitName(unitName);
                if (unit == MAX_MATERIAL_TEXTURE_UNITS)
                    LOGERROR("Unknown texture unit " + unitName);
            }
            else
                unit = (TextureUnit)Clamp(ToInt(unitName), 0, MAX_MATERIAL_TEXTURE_UNITS - 1);
        }
        if (unit != MAX_MATERIAL_TEXTURE_UNITS)
        {
            String name = textureElem.GetAttribute("name");
            // Detect cube maps by file extension: they are defined by an XML file
            if (GetExtension(name) == ".xml")
                SetTexture(unit, cache->GetResource<TextureCube>(name));
            else
                SetTexture(unit, cache->GetResource<Texture2D>(name));
        }
        textureElem = textureElem.GetNext("texture");
    }
    
    XMLElement parameterElem = rootElem.GetChild("parameter");
    while (parameterElem)
    {
        String name = parameterElem.GetAttribute("name");
        Vector4 value = parameterElem.GetVector("value");
        SetShaderParameter(name, value);
        
        parameterElem = parameterElem.GetNext("parameter");
    }
    
    XMLElement cullElem = rootElem.GetChild("cull");
    if (cullElem)
        SetCullMode((CullMode)GetStringListIndex(cullElem.GetAttribute("value"), cullModeNames, CULL_CCW));
    
    XMLElement shadowCullElem = rootElem.GetChild("shadowcull");
    if (shadowCullElem)
        SetShadowCullMode((CullMode)GetStringListIndex(shadowCullElem.GetAttribute("value"), cullModeNames, CULL_CCW));
    
    XMLElement depthBiasElem = rootElem.GetChild("depthbias");
    if (depthBiasElem)
        SetDepthBias(BiasParameters(depthBiasElem.GetFloat("constant"), depthBiasElem.GetFloat("slopescaled")));
    
    // Calculate memory use
    unsigned memoryUse = sizeof(Material);
    
    memoryUse += techniques_.Size() * sizeof(TechniqueEntry);
    memoryUse += MAX_MATERIAL_TEXTURE_UNITS * sizeof(SharedPtr<Texture>);
    memoryUse += shaderParameters_.Size() * sizeof(MaterialShaderParameter);
    
    SetMemoryUse(memoryUse);
    CheckOcclusion();
    return true;
}

bool Material::Save(Serializer& dest)
{
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    XMLElement materialElem = xml->CreateRoot("material");
    
    // Write techniques
    for (unsigned i = 0; i < techniques_.Size(); ++i)
    {
        TechniqueEntry& entry = techniques_[i];
        if (!entry.technique_)
            continue;
        
        XMLElement techniqueElem = materialElem.CreateChild("technique");
        techniqueElem.SetString("name", entry.technique_->GetName());
        techniqueElem.SetInt("quality", entry.qualityLevel_);
        techniqueElem.SetFloat("loddistance", entry.lodDistance_);
    }
    
    // Write texture units
    for (unsigned j = 0; j < MAX_MATERIAL_TEXTURE_UNITS; ++j)
    {
        Texture* texture = GetTexture((TextureUnit)j);
        if (texture)
        {
            XMLElement textureElem = materialElem.CreateChild("texture");
            textureElem.SetString("unit", textureUnitNames[j]);
            textureElem.SetString("name", texture->GetName());
        }
    }
    
    // Write shader parameters
    for (HashMap<StringHash, MaterialShaderParameter>::ConstIterator j = shaderParameters_.Begin(); j != shaderParameters_.End(); ++j)
    {
        XMLElement parameterElem = materialElem.CreateChild("parameter");
        parameterElem.SetString("name", j->second_.name_);
        parameterElem.SetVector4("value", j->second_.value_);
    }
    
    // Write culling modes
    XMLElement cullElem = materialElem.CreateChild("cull");
    cullElem.SetString("value", cullModeNames[cullMode_]);
    
    XMLElement shadowCullElem = materialElem.CreateChild("shadowcull");
    shadowCullElem.SetString("value", cullModeNames[shadowCullMode_]);
    
    // Write depth bias
    XMLElement depthBiasElem = materialElem.CreateChild("depthbias");
    depthBiasElem.SetFloat("constant", depthBias_.constantBias_);
    depthBiasElem.SetFloat("slopescaled", depthBias_.slopeScaledBias_);
    
    return xml->Save(dest);
}

void Material::SetNumTechniques(unsigned num)
{
    if (!num)
        return;
    
    techniques_.Resize(num);
}

void Material::SetTechnique(unsigned index, Technique* tech, unsigned qualityLevel, float lodDistance)
{
    if (index >= techniques_.Size())
        return;
    
    techniques_[index] = TechniqueEntry(tech, qualityLevel, lodDistance);
    CheckOcclusion();
}

void Material::SetShaderParameter(const String& name, const Vector4& value)
{
    MaterialShaderParameter newParam;
    newParam.name_ = name;
    newParam.value_ = value;
    StringHash stringHash(name);
    shaderParameters_[stringHash] = newParam;
    
    if (stringHash == PSP_MATSPECCOLOR)
        specular_ = value.x_ > 0.0f || value.y_ > 0.0f || value.z_ > 0.0f;
}

void Material::SetTexture(TextureUnit unit, Texture* texture)
{
    if (unit < MAX_MATERIAL_TEXTURE_UNITS)
        textures_[unit] = texture;
}

void Material::SetUVTransform(const Vector2& offset, float rotation, const Vector2& repeat)
{
    Matrix3x4 transform(Matrix3x4::IDENTITY);
    transform.m00_ = repeat.x_;
    transform.m11_ = repeat.y_;
    transform.m03_ = -0.5f * transform.m00_ + 0.5f;
    transform.m13_ = -0.5f * transform.m11_ + 0.5f;
    
    Matrix3x4 rotationMatrix(Matrix3x4::IDENTITY);
    float angleRad = rotation * M_DEGTORAD;
    rotationMatrix.m00_ = cosf(angleRad);
    rotationMatrix.m01_ = sinf(angleRad);
    rotationMatrix.m10_ = -rotationMatrix.m01_;
    rotationMatrix.m11_ = rotationMatrix.m00_;
    rotationMatrix.m03_ = 0.5f - 0.5f * (rotationMatrix.m00_ + rotationMatrix.m01_);
    rotationMatrix.m13_ = 0.5f - 0.5f * (rotationMatrix.m10_ + rotationMatrix.m11_);
    
    transform = rotationMatrix * transform;
    
    Matrix3x4 offsetMatrix = Matrix3x4::IDENTITY;
    offsetMatrix.m03_ = offset.x_;
    offsetMatrix.m13_ = offset.y_;
    
    transform = offsetMatrix * transform;
    
    SetShaderParameter("UOffset", Vector4(transform.m00_, transform.m01_, transform.m02_, transform.m03_));
    SetShaderParameter("VOffset", Vector4(transform.m10_, transform.m11_, transform.m12_, transform.m13_));
}

void Material::SetUVTransform(const Vector2& offset, float rotation, float repeat)
{
    SetUVTransform(offset, rotation, Vector2(repeat, repeat));
}

void Material::SetCullMode(CullMode mode)
{
    cullMode_ = mode;
}

void Material::SetShadowCullMode(CullMode mode)
{
    shadowCullMode_ = mode;
}

void Material::SetDepthBias(const BiasParameters& parameters)
{
    depthBias_ = parameters;
    depthBias_.Validate();
}

void Material::RemoveShaderParameter(const String& name)
{
    StringHash stringHash(name);
    shaderParameters_.Erase(stringHash);

    if (stringHash == PSP_MATSPECCOLOR)
        specular_ = false;
}

void Material::ReleaseShaders()
{
    for (unsigned i = 0; i < techniques_.Size(); ++i)
    {
        Technique* tech = techniques_[i].technique_;
        if (tech)
            tech->ReleaseShaders();
    }
}

SharedPtr<Material> Material::Clone(const String& cloneName) const
{
    SharedPtr<Material> ret(new Material(context_));
    
    ret->SetName(cloneName);
    ret->techniques_ = techniques_;
    ret->shaderParameters_ = shaderParameters_;
    for (unsigned i = 0; i < MAX_MATERIAL_TEXTURE_UNITS; ++i)
        ret->textures_[i] = textures_[i];
    ret->occlusion_ = occlusion_;
    ret->cullMode_ = cullMode_;
    ret->shadowCullMode_ = shadowCullMode_;
    
    return ret;
}

void Material::MarkForAuxView(unsigned frameNumber)
{
    auxViewFrameNumber_ = frameNumber;
}

const TechniqueEntry& Material::GetTechniqueEntry(unsigned index) const
{
    return index < techniques_.Size() ? techniques_[index] : noEntry;
}

Technique* Material::GetTechnique(unsigned index) const
{
    return index < techniques_.Size() ? techniques_[index].technique_ : (Technique*)0;
}

Pass* Material::GetPass(unsigned index, PassType pass) const
{
    Technique* tech = index < techniques_.Size() ? techniques_[index].technique_ : (Technique*)0;
    return tech ? tech->GetPass(pass) : 0;
}

Texture* Material::GetTexture(TextureUnit unit) const
{
    return unit < MAX_MATERIAL_TEXTURE_UNITS ? textures_[unit] : (Texture*)0;
}

const Vector4& Material::GetShaderParameter(const String& name) const
{
    HashMap<StringHash, MaterialShaderParameter>::ConstIterator i = shaderParameters_.Find(StringHash(name));
    return i != shaderParameters_.End() ? i->second_.value_ : Vector4::ZERO;
}

const String& Material::GetTextureUnitName(TextureUnit unit)
{
    return textureUnitNames[unit];
}

void Material::CheckOcclusion()
{
    // Determine occlusion by checking the first pass of each technique
    occlusion_ = false;
    for (unsigned i = 0; i < techniques_.Size(); ++i)
    {
        Technique* tech = techniques_[i].technique_;
        if (tech)
        {
            Pass* pass = tech->GetPass(PASS_BASE);
            if (pass && pass->GetDepthWrite() && !pass->GetAlphaMask())
                occlusion_ = true;
        }
    }
}

}
