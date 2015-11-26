//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../Core/Profiler.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Material.h"
#include "../Graphics/Technique.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Texture3D.h"
#include "../Graphics/TextureCube.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../IO/VectorBuffer.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/XMLFile.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneEvents.h"
#include "../Scene/ValueAnimation.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* wrapModeNames[];

static const char* textureUnitNames[] =
{
    "diffuse",
    "normal",
    "specular",
    "emissive",
    "environment",
#ifdef DESKTOP_GRAPHICS
    "volume",
    "custom1",
    "custom2",
    "lightramp",
    "lightshape",
    "shadowmap",
    "faceselect",
    "indirection",
    "depth",
    "light",
    "zone",
    0
#else
    "lightramp",
    "lightshape",
    "shadowmap",
    0
#endif
};

static const char* cullModeNames[] =
{
    "none",
    "ccw",
    "cw",
    0
};

static const char* fillModeNames[] =
{
    "solid",
    "wireframe",
    "point",
    0
};

TextureUnit ParseTextureUnitName(String name)
{
    name = name.ToLower().Trimmed();

    TextureUnit unit = (TextureUnit)GetStringListIndex(name.CString(), textureUnitNames, MAX_TEXTURE_UNITS);
    if (unit == MAX_TEXTURE_UNITS)
    {
        // Check also for shorthand names
        if (name == "diff")
            unit = TU_DIFFUSE;
        else if (name == "albedo")
            unit = TU_DIFFUSE;
        else if (name == "norm")
            unit = TU_NORMAL;
        else if (name == "spec")
            unit = TU_SPECULAR;
        else if (name == "env")
            unit = TU_ENVIRONMENT;
        // Finally check for specifying the texture unit directly as a number
        else if (name.Length() < 3)
            unit = (TextureUnit)Clamp(ToInt(name), 0, MAX_TEXTURE_UNITS - 1);
    }

    if (unit == MAX_TEXTURE_UNITS)
        URHO3D_LOGERROR("Unknown texture unit name " + name);

    return unit;
}

static TechniqueEntry noEntry;

bool CompareTechniqueEntries(const TechniqueEntry& lhs, const TechniqueEntry& rhs)
{
    if (lhs.lodDistance_ != rhs.lodDistance_)
        return lhs.lodDistance_ > rhs.lodDistance_;
    else
        return lhs.qualityLevel_ > rhs.qualityLevel_;
}

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

ShaderParameterAnimationInfo::ShaderParameterAnimationInfo(Material* target, const String& name, ValueAnimation* attributeAnimation,
    WrapMode wrapMode, float speed) :
    ValueAnimationInfo(target, attributeAnimation, wrapMode, speed),
    name_(name)
{
}

ShaderParameterAnimationInfo::ShaderParameterAnimationInfo(const ShaderParameterAnimationInfo& other) :
    ValueAnimationInfo(other),
    name_(other.name_)
{
}

ShaderParameterAnimationInfo::~ShaderParameterAnimationInfo()
{
}

void ShaderParameterAnimationInfo::ApplyValue(const Variant& newValue)
{
    static_cast<Material*>(target_.Get())->SetShaderParameter(name_, newValue);
}

Material::Material(Context* context) :
    Resource(context),
    auxViewFrameNumber_(0),
    shaderParameterHash_(0),
    occlusion_(true),
    specular_(false),
    subscribed_(false),
    batchedParameterUpdate_(false)
{
    ResetToDefaults();
}

Material::~Material()
{
}

void Material::RegisterObject(Context* context)
{
    context->RegisterFactory<Material>();
}

bool Material::BeginLoad(Deserializer& source)
{
    // In headless mode, do not actually load the material, just return success
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics)
        return true;

    loadXMLFile_ = new XMLFile(context_);
    if (loadXMLFile_->Load(source))
    {
        // If async loading, scan the XML content beforehand for technique & texture resources
        // and request them to also be loaded. Can not do anything else at this point
        if (GetAsyncLoadState() == ASYNC_LOADING)
        {
            ResourceCache* cache = GetSubsystem<ResourceCache>();
            XMLElement rootElem = loadXMLFile_->GetRoot();
            XMLElement techniqueElem = rootElem.GetChild("technique");
            while (techniqueElem)
            {
                cache->BackgroundLoadResource<Technique>(techniqueElem.GetAttribute("name"), true, this);
                techniqueElem = techniqueElem.GetNext("technique");
            }

            XMLElement textureElem = rootElem.GetChild("texture");
            while (textureElem)
            {
                String name = textureElem.GetAttribute("name");
                // Detect cube maps by file extension: they are defined by an XML file
                /// \todo Differentiate with 3D textures by actually reading the XML content
                if (GetExtension(name) == ".xml")
                {
#ifdef DESKTOP_GRAPHICS
                    TextureUnit unit = TU_DIFFUSE;
                    if (textureElem.HasAttribute("unit"))
                        unit = ParseTextureUnitName(textureElem.GetAttribute("unit"));
                    if (unit == TU_VOLUMEMAP)
                        cache->BackgroundLoadResource<Texture3D>(name, true, this);
                    else
#endif
                        cache->BackgroundLoadResource<TextureCube>(name, true, this);
                }
                else
                    cache->BackgroundLoadResource<Texture2D>(name, true, this);
                textureElem = textureElem.GetNext("texture");
            }
        }

        return true;
    }
    else
    {
        ResetToDefaults();
        loadXMLFile_.Reset();
        return false;
    }
}

bool Material::EndLoad()
{
    // In headless mode, do not actually load the material, just return success
    Graphics* graphics = GetSubsystem<Graphics>();
    if (!graphics)
        return true;

    bool success = false;
    if (loadXMLFile_)
    {
        // If async loading, get the techniques / textures which should be ready now
        XMLElement rootElem = loadXMLFile_->GetRoot();
        success = Load(rootElem);
    }

    loadXMLFile_.Reset();
    return success;
}


bool Material::Save(Serializer& dest) const
{
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    XMLElement materialElem = xml->CreateRoot("material");

    Save(materialElem);
    return xml->Save(dest);
}

bool Material::Load(const XMLElement& source)
{
    ResetToDefaults();

    if (source.IsNull())
    {
        URHO3D_LOGERROR("Can not load material from null XML element");
        return false;
    }

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    XMLElement techniqueElem = source.GetChild("technique");
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

    SortTechniques();

    XMLElement textureElem = source.GetChild("texture");
    while (textureElem)
    {
        TextureUnit unit = TU_DIFFUSE;
        if (textureElem.HasAttribute("unit"))
            unit = ParseTextureUnitName(textureElem.GetAttribute("unit"));
        if (unit < MAX_TEXTURE_UNITS)
        {
            String name = textureElem.GetAttribute("name");
            // Detect cube maps by file extension: they are defined by an XML file
            /// \todo Differentiate with 3D textures by actually reading the XML content
            if (GetExtension(name) == ".xml")
            {
#ifdef DESKTOP_GRAPHICS
                if (unit == TU_VOLUMEMAP)
                    SetTexture(unit, cache->GetResource<Texture3D>(name));
                else
#endif
                    SetTexture(unit, cache->GetResource<TextureCube>(name));
            }
            else
                SetTexture(unit, cache->GetResource<Texture2D>(name));
        }
        textureElem = textureElem.GetNext("texture");
    }

    batchedParameterUpdate_ = true;
    XMLElement parameterElem = source.GetChild("parameter");
    while (parameterElem)
    {
        String name = parameterElem.GetAttribute("name");
        SetShaderParameter(name, ParseShaderParameterValue(parameterElem.GetAttribute("value")));
        parameterElem = parameterElem.GetNext("parameter");
    }
    batchedParameterUpdate_ = false;

    XMLElement parameterAnimationElem = source.GetChild("parameteranimation");
    while (parameterAnimationElem)
    {
        String name = parameterAnimationElem.GetAttribute("name");
        SharedPtr<ValueAnimation> animation(new ValueAnimation(context_));
        if (!animation->LoadXML(parameterAnimationElem))
        {
            URHO3D_LOGERROR("Could not load parameter animation");
            return false;
        }

        String wrapModeString = parameterAnimationElem.GetAttribute("wrapmode");
        WrapMode wrapMode = WM_LOOP;
        for (int i = 0; i <= WM_CLAMP; ++i)
        {
            if (wrapModeString == wrapModeNames[i])
            {
                wrapMode = (WrapMode)i;
                break;
            }
        }

        float speed = parameterAnimationElem.GetFloat("speed");
        SetShaderParameterAnimation(name, animation, wrapMode, speed);

        parameterAnimationElem = parameterAnimationElem.GetNext("parameteranimation");
    }

    XMLElement cullElem = source.GetChild("cull");
    if (cullElem)
        SetCullMode((CullMode)GetStringListIndex(cullElem.GetAttribute("value").CString(), cullModeNames, CULL_CCW));

    XMLElement shadowCullElem = source.GetChild("shadowcull");
    if (shadowCullElem)
        SetShadowCullMode((CullMode)GetStringListIndex(shadowCullElem.GetAttribute("value").CString(), cullModeNames, CULL_CCW));

    XMLElement fillElem = source.GetChild("fill");
    if (fillElem)
        SetFillMode((FillMode)GetStringListIndex(fillElem.GetAttribute("value").CString(), fillModeNames, FILL_SOLID));

    XMLElement depthBiasElem = source.GetChild("depthbias");
    if (depthBiasElem)
        SetDepthBias(BiasParameters(depthBiasElem.GetFloat("constant"), depthBiasElem.GetFloat("slopescaled")));

    XMLElement renderOrderElem = source.GetChild("renderorder");
    if (renderOrderElem)
        SetRenderOrder((unsigned char)renderOrderElem.GetUInt("value"));

    RefreshShaderParameterHash();
    RefreshMemoryUse();
    CheckOcclusion();
    return true;
}

bool Material::Save(XMLElement& dest) const
{
    if (dest.IsNull())
    {
        URHO3D_LOGERROR("Can not save material to null XML element");
        return false;
    }

    // Write techniques
    for (unsigned i = 0; i < techniques_.Size(); ++i)
    {
        const TechniqueEntry& entry = techniques_[i];
        if (!entry.technique_)
            continue;

        XMLElement techniqueElem = dest.CreateChild("technique");
        techniqueElem.SetString("name", entry.technique_->GetName());
        techniqueElem.SetInt("quality", entry.qualityLevel_);
        techniqueElem.SetFloat("loddistance", entry.lodDistance_);
    }

    // Write texture units
    for (unsigned j = 0; j < MAX_TEXTURE_UNITS; ++j)
    {
        Texture* texture = GetTexture((TextureUnit)j);
        if (texture)
        {
            XMLElement textureElem = dest.CreateChild("texture");
            textureElem.SetString("unit", textureUnitNames[j]);
            textureElem.SetString("name", texture->GetName());
        }
    }

    // Write shader parameters
    for (HashMap<StringHash, MaterialShaderParameter>::ConstIterator j = shaderParameters_.Begin();
         j != shaderParameters_.End(); ++j)
    {
        XMLElement parameterElem = dest.CreateChild("parameter");
        parameterElem.SetString("name", j->second_.name_);
        parameterElem.SetVectorVariant("value", j->second_.value_);
    }

    // Write shader parameter animations
    for (HashMap<StringHash, SharedPtr<ShaderParameterAnimationInfo> >::ConstIterator j = shaderParameterAnimationInfos_.Begin();
         j != shaderParameterAnimationInfos_.End(); ++j)
    {
        ShaderParameterAnimationInfo* info = j->second_;
        XMLElement parameterAnimationElem = dest.CreateChild("parameteranimation");
        parameterAnimationElem.SetString("name", info->GetName());
        if (!info->GetAnimation()->SaveXML(parameterAnimationElem))
            return false;

        parameterAnimationElem.SetAttribute("wrapmode", wrapModeNames[info->GetWrapMode()]);
        parameterAnimationElem.SetFloat("speed", info->GetSpeed());
    }

    // Write culling modes
    XMLElement cullElem = dest.CreateChild("cull");
    cullElem.SetString("value", cullModeNames[cullMode_]);

    XMLElement shadowCullElem = dest.CreateChild("shadowcull");
    shadowCullElem.SetString("value", cullModeNames[shadowCullMode_]);

    // Write fill mode
    XMLElement fillElem = dest.CreateChild("fill");
    fillElem.SetString("value", fillModeNames[fillMode_]);

    // Write depth bias
    XMLElement depthBiasElem = dest.CreateChild("depthbias");
    depthBiasElem.SetFloat("constant", depthBias_.constantBias_);
    depthBiasElem.SetFloat("slopescaled", depthBias_.slopeScaledBias_);

    // Write render order
    XMLElement renderOrderElem = dest.CreateChild("renderorder");
    renderOrderElem.SetUInt("value", renderOrder_);

    return true;
}

void Material::SetNumTechniques(unsigned num)
{
    if (!num)
        return;

    techniques_.Resize(num);
    RefreshMemoryUse();
}

void Material::SetTechnique(unsigned index, Technique* tech, unsigned qualityLevel, float lodDistance)
{
    if (index >= techniques_.Size())
        return;

    techniques_[index] = TechniqueEntry(tech, qualityLevel, lodDistance);
    CheckOcclusion();
}

void Material::SetShaderParameter(const String& name, const Variant& value)
{
    MaterialShaderParameter newParam;
    newParam.name_ = name;
    newParam.value_ = value;
    StringHash nameHash(name);
    shaderParameters_[nameHash] = newParam;

    if (nameHash == PSP_MATSPECCOLOR)
    {
        VariantType type = value.GetType();
        if (type == VAR_VECTOR3)
        {
            const Vector3& vec = value.GetVector3();
            specular_ = vec.x_ > 0.0f || vec.y_ > 0.0f || vec.z_ > 0.0f;
        }
        else if (type == VAR_VECTOR4)
        {
            const Vector4& vec = value.GetVector4();
            specular_ = vec.x_ > 0.0f || vec.y_ > 0.0f || vec.z_ > 0.0f;
        }
    }

    if (!batchedParameterUpdate_)
    {
        RefreshShaderParameterHash();
        RefreshMemoryUse();
    }
}

void Material::SetShaderParameterAnimation(const String& name, ValueAnimation* animation, WrapMode wrapMode, float speed)
{
    ShaderParameterAnimationInfo* info = GetShaderParameterAnimationInfo(name);

    if (animation)
    {
        if (info && info->GetAnimation() == animation)
        {
            info->SetWrapMode(wrapMode);
            info->SetSpeed(speed);
            return;
        }

        if (shaderParameters_.Find(name) == shaderParameters_.End())
        {
            URHO3D_LOGERROR(GetName() + " has no shader parameter: " + name);
            return;
        }

        StringHash nameHash(name);
        shaderParameterAnimationInfos_[nameHash] = new ShaderParameterAnimationInfo(this, name, animation, wrapMode, speed);
        UpdateEventSubscription();
    }
    else
    {
        if (info)
        {
            StringHash nameHash(name);
            shaderParameterAnimationInfos_.Erase(nameHash);
            UpdateEventSubscription();
        }
    }
}

void Material::SetShaderParameterAnimationWrapMode(const String& name, WrapMode wrapMode)
{
    ShaderParameterAnimationInfo* info = GetShaderParameterAnimationInfo(name);
    if (info)
        info->SetWrapMode(wrapMode);
}

void Material::SetShaderParameterAnimationSpeed(const String& name, float speed)
{
    ShaderParameterAnimationInfo* info = GetShaderParameterAnimationInfo(name);
    if (info)
        info->SetSpeed(speed);
}

void Material::SetTexture(TextureUnit unit, Texture* texture)
{
    if (unit < MAX_TEXTURE_UNITS)
    {
        if (texture)
            textures_[unit] = texture;
        else
            textures_.Erase(unit);
    }
}

void Material::SetUVTransform(const Vector2& offset, float rotation, const Vector2& repeat)
{
    Matrix3x4 transform(Matrix3x4::IDENTITY);
    transform.m00_ = repeat.x_;
    transform.m11_ = repeat.y_;
    transform.m03_ = -0.5f * transform.m00_ + 0.5f;
    transform.m13_ = -0.5f * transform.m11_ + 0.5f;

    Matrix3x4 rotationMatrix(Matrix3x4::IDENTITY);
    rotationMatrix.m00_ = Cos(rotation);
    rotationMatrix.m01_ = Sin(rotation);
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

void Material::SetFillMode(FillMode mode)
{
    fillMode_ = mode;
}

void Material::SetDepthBias(const BiasParameters& parameters)
{
    depthBias_ = parameters;
    depthBias_.Validate();
}

void Material::SetRenderOrder(unsigned char order)
{
    renderOrder_ = order;
}

void Material::SetScene(Scene* scene)
{
    UnsubscribeFromEvent(E_UPDATE);
    UnsubscribeFromEvent(E_ATTRIBUTEANIMATIONUPDATE);
    subscribed_ = false;
    scene_ = scene;
    UpdateEventSubscription();
}

void Material::RemoveShaderParameter(const String& name)
{
    StringHash nameHash(name);
    shaderParameters_.Erase(nameHash);

    if (nameHash == PSP_MATSPECCOLOR)
        specular_ = false;

    RefreshShaderParameterHash();
    RefreshMemoryUse();
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
    ret->textures_ = textures_;
    ret->occlusion_ = occlusion_;
    ret->specular_ = specular_;
    ret->cullMode_ = cullMode_;
    ret->shadowCullMode_ = shadowCullMode_;
    ret->fillMode_ = fillMode_;
    ret->renderOrder_ = renderOrder_;
    ret->RefreshMemoryUse();

    return ret;
}

void Material::SortTechniques()
{
    Sort(techniques_.Begin(), techniques_.End(), CompareTechniqueEntries);
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

Pass* Material::GetPass(unsigned index, const String& passName) const
{
    Technique* tech = index < techniques_.Size() ? techniques_[index].technique_ : (Technique*)0;
    return tech ? tech->GetPass(passName) : 0;
}

Texture* Material::GetTexture(TextureUnit unit) const
{
    HashMap<TextureUnit, SharedPtr<Texture> >::ConstIterator i = textures_.Find(unit);
    return i != textures_.End() ? i->second_.Get() : (Texture*)0;
}

const Variant& Material::GetShaderParameter(const String& name) const
{
    HashMap<StringHash, MaterialShaderParameter>::ConstIterator i = shaderParameters_.Find(name);
    return i != shaderParameters_.End() ? i->second_.value_ : Variant::EMPTY;
}

ValueAnimation* Material::GetShaderParameterAnimation(const String& name) const
{
    ShaderParameterAnimationInfo* info = GetShaderParameterAnimationInfo(name);
    return info == 0 ? 0 : info->GetAnimation();
}

WrapMode Material::GetShaderParameterAnimationWrapMode(const String& name) const
{
    ShaderParameterAnimationInfo* info = GetShaderParameterAnimationInfo(name);
    return info == 0 ? WM_LOOP : info->GetWrapMode();
}

float Material::GetShaderParameterAnimationSpeed(const String& name) const
{
    ShaderParameterAnimationInfo* info = GetShaderParameterAnimationInfo(name);
    return info == 0 ? 0 : info->GetSpeed();
}

Scene* Material::GetScene() const
{
    return scene_;
}

String Material::GetTextureUnitName(TextureUnit unit)
{
    return textureUnitNames[unit];
}

Variant Material::ParseShaderParameterValue(const String& value)
{
    String valueTrimmed = value.Trimmed();
    if (valueTrimmed.Length() && IsAlpha((unsigned)valueTrimmed[0]))
        return Variant(ToBool(valueTrimmed));
    else
        return ToVectorVariant(valueTrimmed);
}

void Material::CheckOcclusion()
{
    // Determine occlusion by checking the base pass of each technique
    occlusion_ = false;
    for (unsigned i = 0; i < techniques_.Size(); ++i)
    {
        Technique* tech = techniques_[i].technique_;
        if (tech)
        {
            Pass* pass = tech->GetPass("base");
            if (pass && pass->GetDepthWrite() && !pass->GetAlphaMask())
                occlusion_ = true;
        }
    }
}

void Material::ResetToDefaults()
{
    // Needs to be a no-op when async loading, as this does a GetResource() which is not allowed from worker threads
    if (!Thread::IsMainThread())
        return;

    SetNumTechniques(1);
    SetTechnique(0, GetSubsystem<ResourceCache>()->GetResource<Technique>("Techniques/NoTexture.xml"));

    textures_.Clear();

    batchedParameterUpdate_ = true;
    shaderParameters_.Clear();
    SetShaderParameter("UOffset", Vector4(1.0f, 0.0f, 0.0f, 0.0f));
    SetShaderParameter("VOffset", Vector4(0.0f, 1.0f, 0.0f, 0.0f));
    SetShaderParameter("MatDiffColor", Vector4::ONE);
    SetShaderParameter("MatEmissiveColor", Vector3::ZERO);
    SetShaderParameter("MatEnvMapColor", Vector3::ONE);
    SetShaderParameter("MatSpecColor", Vector4(0.0f, 0.0f, 0.0f, 1.0f));
    batchedParameterUpdate_ = false;

    cullMode_ = CULL_CCW;
    shadowCullMode_ = CULL_CCW;
    fillMode_ = FILL_SOLID;
    depthBias_ = BiasParameters(0.0f, 0.0f);
    renderOrder_ = DEFAULT_RENDER_ORDER;

    RefreshShaderParameterHash();
    RefreshMemoryUse();
}

void Material::RefreshShaderParameterHash()
{
    VectorBuffer temp;
    for (HashMap<StringHash, MaterialShaderParameter>::ConstIterator i = shaderParameters_.Begin();
         i != shaderParameters_.End(); ++i)
    {
        temp.WriteStringHash(i->first_);
        temp.WriteVariant(i->second_.value_);
    }

    shaderParameterHash_ = 0;
    const unsigned char* data = temp.GetData();
    unsigned dataSize = temp.GetSize();
    for (unsigned i = 0; i < dataSize; ++i)
        shaderParameterHash_ = SDBMHash(shaderParameterHash_, data[i]);
}

void Material::RefreshMemoryUse()
{
    unsigned memoryUse = sizeof(Material);

    memoryUse += techniques_.Size() * sizeof(TechniqueEntry);
    memoryUse += MAX_TEXTURE_UNITS * sizeof(SharedPtr<Texture>);
    memoryUse += shaderParameters_.Size() * sizeof(MaterialShaderParameter);

    SetMemoryUse(memoryUse);
}

ShaderParameterAnimationInfo* Material::GetShaderParameterAnimationInfo(const String& name) const
{
    StringHash nameHash(name);
    HashMap<StringHash, SharedPtr<ShaderParameterAnimationInfo> >::ConstIterator i = shaderParameterAnimationInfos_.Find(nameHash);
    if (i == shaderParameterAnimationInfos_.End())
        return 0;
    return i->second_;
}

void Material::UpdateEventSubscription()
{
    if (shaderParameterAnimationInfos_.Size() && !subscribed_)
    {
        if (scene_)
            SubscribeToEvent(scene_, E_ATTRIBUTEANIMATIONUPDATE, URHO3D_HANDLER(Material, HandleAttributeAnimationUpdate));
        else
            SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Material, HandleAttributeAnimationUpdate));
        subscribed_ = true;
    }
    else if (subscribed_)
    {
        UnsubscribeFromEvent(E_UPDATE);
        UnsubscribeFromEvent(E_ATTRIBUTEANIMATIONUPDATE);
        subscribed_ = false;
    }
}

void Material::HandleAttributeAnimationUpdate(StringHash eventType, VariantMap& eventData)
{
    // Timestep parameter is same no matter what event is being listened to
    float timeStep = eventData[Update::P_TIMESTEP].GetFloat();

    Vector<String> finishedNames;
    for (HashMap<StringHash, SharedPtr<ShaderParameterAnimationInfo> >::ConstIterator i = shaderParameterAnimationInfos_.Begin();
         i != shaderParameterAnimationInfos_.End(); ++i)
    {
        if (i->second_->Update(timeStep))
            finishedNames.Push(i->second_->GetName());
    }

    // Remove finished animations
    for (unsigned i = 0; i < finishedNames.Size(); ++i)
        SetShaderParameterAnimation(finishedNames[i], 0);
}

}
