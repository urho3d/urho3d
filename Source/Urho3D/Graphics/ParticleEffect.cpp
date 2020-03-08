//
// Copyright (c) 2008-2020 the Urho3D project.
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
#include "../Core/StringUtils.h"
#include "../Graphics/Material.h"
#include "../Graphics/ParticleEffect.h"
#include "../Graphics/BillboardSet.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/XMLFile.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* faceCameraModeNames[];

static const char* emitterTypeNames[] =
{
    "Sphere",
    "Box",
    "SphereVolume",
    "Cylinder",
    "Ring",
    nullptr
};

static const Vector2 DEFAULT_PARTICLE_SIZE(0.1f, 0.1f);
static const float DEFAULT_EMISSION_RATE = 10.0f;
static const float MIN_EMISSION_RATE = 0.01f;
static const float DEFAULT_TIME_TO_LIVE = 1.0f;
static const float DEFAULT_VELOCITY = 1.0f;
static const Vector3 DEFAULT_DIRECTION_MIN(-1.0f, -1.0f, -1.0f);
static const Vector3 DEFAULT_DIRECTION_MAX(1.0f, 1.0f, 1.0f);

ParticleEffect::ParticleEffect(Context* context) :
    Resource(context),
    numParticles_(DEFAULT_NUM_PARTICLES),
    updateInvisible_(false),
    relative_(true),
    scaled_(true),
    sorted_(false),
    fixedScreenSize_(false),
    animationLodBias_(0.0f),
    emitterType_(EMITTER_SPHERE),
    emitterSize_(Vector3::ZERO),
    directionMin_(DEFAULT_DIRECTION_MIN),
    directionMax_(DEFAULT_DIRECTION_MAX),
    constantForce_(Vector3::ZERO),
    dampingForce_(0.0f),
    activeTime_(0.0f),
    inactiveTime_(0.0f),
    emissionRateMin_(DEFAULT_EMISSION_RATE),
    emissionRateMax_(DEFAULT_EMISSION_RATE),
    sizeMin_(DEFAULT_PARTICLE_SIZE),
    sizeMax_(DEFAULT_PARTICLE_SIZE),
    timeToLiveMin_(DEFAULT_TIME_TO_LIVE),
    timeToLiveMax_(DEFAULT_TIME_TO_LIVE),
    velocityMin_(DEFAULT_VELOCITY),
    velocityMax_(DEFAULT_VELOCITY),
    rotationMin_(0.0f),
    rotationMax_(0.0f),
    rotationSpeedMin_(0.0f),
    rotationSpeedMax_(0.0f),
    sizeAdd_(0.0f),
    sizeMul_(1.0f),
    faceCameraMode_(FC_ROTATE_XYZ)
{
}

ParticleEffect::~ParticleEffect() = default;

void ParticleEffect::RegisterObject(Context* context)
{
    context->RegisterFactory<ParticleEffect>();
}

bool ParticleEffect::BeginLoad(Deserializer& source)
{
    loadMaterialName_.Clear();

    XMLFile file(context_);
    if (!file.Load(source))
    {
        URHO3D_LOGERROR("Load particle effect file failed");
        return false;
    }

    XMLElement rootElem = file.GetRoot();

    bool success = Load(rootElem);
    if (success)
        SetMemoryUse(source.GetSize());
    return success;
}

bool ParticleEffect::EndLoad()
{
    // Apply the material now
    if (!loadMaterialName_.Empty())
    {
        SetMaterial(GetSubsystem<ResourceCache>()->GetResource<Material>(loadMaterialName_));
        loadMaterialName_.Clear();
    }

    return true;
}

bool ParticleEffect::Load(const XMLElement& source)
{
    // Reset to defaults first so that missing parameters in case of a live reload behave as expected
    material_.Reset();
    numParticles_ = DEFAULT_NUM_PARTICLES;
    updateInvisible_ = false;
    relative_ = true;
    scaled_ = true;
    sorted_ = false;
    fixedScreenSize_ = false;
    animationLodBias_ = 0.0f;
    emitterType_ = EMITTER_SPHERE;
    emitterSize_ = Vector3::ZERO;
    directionMin_ = DEFAULT_DIRECTION_MIN;
    directionMax_ = DEFAULT_DIRECTION_MAX;
    constantForce_ = Vector3::ZERO;
    dampingForce_ = 0.0f;
    activeTime_ = 0.0f;
    inactiveTime_ = 0.0;
    emissionRateMin_ = DEFAULT_EMISSION_RATE;
    emissionRateMax_ = DEFAULT_EMISSION_RATE;
    sizeMin_ = DEFAULT_PARTICLE_SIZE;
    sizeMax_ = DEFAULT_PARTICLE_SIZE;
    timeToLiveMin_ = DEFAULT_TIME_TO_LIVE;
    timeToLiveMax_ = DEFAULT_TIME_TO_LIVE;
    velocityMin_ = DEFAULT_VELOCITY;
    velocityMax_ = DEFAULT_VELOCITY;
    rotationMin_ = 0.0f;
    rotationMax_ = 0.0f;
    rotationSpeedMin_ = 0.0f;
    rotationSpeedMax_ = 0.0f;
    sizeAdd_ = 0.0f;
    sizeMul_ = 1.0f;
    colorFrames_.Clear();
    textureFrames_.Clear();
    faceCameraMode_ = FC_ROTATE_XYZ;

    if (source.IsNull())
    {
        URHO3D_LOGERROR("Can not load particle effect from null XML element");
        return false;
    }

    if (source.HasChild("material"))
    {
        loadMaterialName_ = source.GetChild("material").GetAttribute("name");
        // If async loading, can not GetResource() the material. But can do a background request for it
        if (GetAsyncLoadState() == ASYNC_LOADING)
            GetSubsystem<ResourceCache>()->BackgroundLoadResource<Material>(loadMaterialName_, true, this);
    }

    if (source.HasChild("numparticles"))
        SetNumParticles((unsigned)source.GetChild("numparticles").GetInt("value"));

    if (source.HasChild("updateinvisible"))
        updateInvisible_ = source.GetChild("updateinvisible").GetBool("enable");

    if (source.HasChild("relative"))
        relative_ = source.GetChild("relative").GetBool("enable");

    if (source.HasChild("scaled"))
        scaled_ = source.GetChild("scaled").GetBool("enable");

    if (source.HasChild("sorted"))
        sorted_ = source.GetChild("sorted").GetBool("enable");

    if (source.HasChild("fixedscreensize"))
        fixedScreenSize_ = source.GetChild("fixedscreensize").GetBool("enable");

    if (source.HasChild("animlodbias"))
        SetAnimationLodBias(source.GetChild("animlodbias").GetFloat("value"));

    if (source.HasChild("emittertype"))
    {
        String type = source.GetChild("emittertype").GetAttributeLower("value");
        if (type == "point")
        {
            // Point emitter type is deprecated, handled as zero sized sphere
            emitterType_ = EMITTER_SPHERE;
            emitterSize_ = Vector3::ZERO;
        }
        else
            emitterType_ = (EmitterType)GetStringListIndex(type.CString(), emitterTypeNames, EMITTER_SPHERE);
    }

    if (source.HasChild("emittersize"))
        emitterSize_ = source.GetChild("emittersize").GetVector3("value");

    if (source.HasChild("emitterradius"))
        emitterSize_.x_ = emitterSize_.y_ = emitterSize_.z_ = source.GetChild("emitterradius").GetFloat("value");

    if (source.HasChild("direction"))
        GetVector3MinMax(source.GetChild("direction"), directionMin_, directionMax_);

    if (source.HasChild("constantforce"))
        constantForce_ = source.GetChild("constantforce").GetVector3("value");

    if (source.HasChild("dampingforce"))
        dampingForce_ = source.GetChild("dampingforce").GetFloat("value");

    if (source.HasChild("activetime"))
        activeTime_ = source.GetChild("activetime").GetFloat("value");
    if (activeTime_ < 0.0f)
        activeTime_ = M_INFINITY;

    if (source.HasChild("inactivetime"))
        inactiveTime_ = source.GetChild("inactivetime").GetFloat("value");
    if (inactiveTime_ < 0.0f)
        inactiveTime_ = M_INFINITY;

    if (source.HasChild("emissionrate"))
        GetFloatMinMax(source.GetChild("emissionrate"), emissionRateMin_, emissionRateMax_);

    if (source.HasChild("interval"))
    {
        float intervalMin = 0.0f;
        float intervalMax = 0.0f;
        GetFloatMinMax(source.GetChild("interval"), intervalMin, intervalMax);
        emissionRateMax_ = 1.0f / intervalMin;
        emissionRateMin_ = 1.0f / intervalMax;
    }

    if (source.HasChild("particlesize"))
        GetVector2MinMax(source.GetChild("particlesize"), sizeMin_, sizeMax_);

    if (source.HasChild("timetolive"))
        GetFloatMinMax(source.GetChild("timetolive"), timeToLiveMin_, timeToLiveMax_);

    if (source.HasChild("velocity"))
        GetFloatMinMax(source.GetChild("velocity"), velocityMin_, velocityMax_);

    if (source.HasChild("rotation"))
        GetFloatMinMax(source.GetChild("rotation"), rotationMin_, rotationMax_);

    if (source.HasChild("rotationspeed"))
        GetFloatMinMax(source.GetChild("rotationspeed"), rotationSpeedMin_, rotationSpeedMax_);

    if (source.HasChild("faceCameraMode"))
    {
        String type = source.GetChild("faceCameraMode").GetAttributeLower("value");
        faceCameraMode_ = (FaceCameraMode)GetStringListIndex(type.CString(), faceCameraModeNames, FC_ROTATE_XYZ);
    }

    if (source.HasChild("sizedelta"))
    {
        XMLElement deltaElem = source.GetChild("sizedelta");
        if (deltaElem.HasAttribute("add"))
            sizeAdd_ = deltaElem.GetFloat("add");
        if (deltaElem.HasAttribute("mul"))
            sizeMul_ = deltaElem.GetFloat("mul");
    }

    if (source.HasChild("color"))
    {
        ColorFrame colorFrame(source.GetChild("color").GetColor("value"));
        SetColorFrame(0, colorFrame);
    }

    if (source.HasChild("colorfade"))
    {
        Vector<ColorFrame> fades;
        for (XMLElement colorFadeElem = source.GetChild("colorfade"); colorFadeElem;
             colorFadeElem = colorFadeElem.GetNext("colorfade"))
            fades.Push(ColorFrame(colorFadeElem.GetColor("color"), colorFadeElem.GetFloat("time")));

        SetColorFrames(fades);
    }

    if (colorFrames_.Empty())
        colorFrames_.Push(ColorFrame(Color::WHITE));

    if (source.HasChild("texanim"))
    {
        Vector<TextureFrame> animations;
        for (XMLElement animElem = source.GetChild("texanim"); animElem; animElem = animElem.GetNext("texanim"))
        {
            TextureFrame animation;
            animation.uv_ = animElem.GetRect("uv");
            animation.time_ = animElem.GetFloat("time");
            animations.Push(animation);
        }

        SetTextureFrames(animations);
    }

    return true;
}

bool ParticleEffect::Save(Serializer& dest) const
{
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    XMLElement materialElem = xml->CreateRoot("particleeffect");

    Save(materialElem);
    return xml->Save(dest);
}

bool ParticleEffect::Save(XMLElement& dest) const
{
    if (dest.IsNull())
    {
        URHO3D_LOGERROR("Can not save particle effect to null XML element");
        return false;
    }

    XMLElement childElem = dest.CreateChild("material");
    childElem.SetAttribute("name", GetResourceName(material_));

    childElem = dest.CreateChild("numparticles");
    childElem.SetInt("value", numParticles_);

    childElem = dest.CreateChild("updateinvisible");
    childElem.SetBool("enable", updateInvisible_);

    childElem = dest.CreateChild("relative");
    childElem.SetBool("enable", relative_);

    childElem = dest.CreateChild("scaled");
    childElem.SetBool("enable", scaled_);

    childElem = dest.CreateChild("sorted");
    childElem.SetBool("enable", sorted_);

    childElem = dest.CreateChild("fixedscreensize");
    childElem.SetBool("enable", fixedScreenSize_);

    childElem = dest.CreateChild("animlodbias");
    childElem.SetFloat("value", animationLodBias_);

    childElem = dest.CreateChild("emittertype");
    childElem.SetAttribute("value", emitterTypeNames[emitterType_]);

    childElem = dest.CreateChild("emittersize");
    childElem.SetVector3("value", emitterSize_);

    childElem = dest.CreateChild("direction");
    childElem.SetVector3("min", directionMin_);
    childElem.SetVector3("max", directionMax_);

    childElem = dest.CreateChild("constantforce");
    childElem.SetVector3("value", constantForce_);

    childElem = dest.CreateChild("dampingforce");
    childElem.SetFloat("value", dampingForce_);

    childElem = dest.CreateChild("activetime");
    childElem.SetFloat("value", activeTime_);

    childElem = dest.CreateChild("inactivetime");
    childElem.SetFloat("value", inactiveTime_);

    childElem = dest.CreateChild("emissionrate");
    childElem.SetFloat("min", emissionRateMin_);
    childElem.SetFloat("max", emissionRateMax_);

    childElem = dest.CreateChild("particlesize");
    childElem.SetVector2("min", sizeMin_);
    childElem.SetVector2("max", sizeMax_);

    childElem = dest.CreateChild("timetolive");
    childElem.SetFloat("min", timeToLiveMin_);
    childElem.SetFloat("max", timeToLiveMax_);

    childElem = dest.CreateChild("velocity");
    childElem.SetFloat("min", velocityMin_);
    childElem.SetFloat("max", velocityMax_);

    childElem = dest.CreateChild("rotation");
    childElem.SetFloat("min", rotationMin_);
    childElem.SetFloat("max", rotationMax_);

    childElem = dest.CreateChild("rotationspeed");
    childElem.SetFloat("min", rotationSpeedMin_);
    childElem.SetFloat("max", rotationSpeedMax_);

    childElem = dest.CreateChild("sizedelta");
    childElem.SetFloat("add", sizeAdd_);
    childElem.SetFloat("mul", sizeMul_);

    childElem = dest.CreateChild("faceCameraMode");
    childElem.SetAttribute("value", faceCameraModeNames[faceCameraMode_]);

    if (colorFrames_.Size() == 1)
    {
        childElem = dest.CreateChild("color");
        childElem.SetColor("value", colorFrames_[0].color_);
    }

    if (colorFrames_.Size() > 1)
    {
        for (unsigned i = 0; i < colorFrames_.Size(); ++i)
        {
            childElem = dest.CreateChild("colorfade");
            childElem.SetColor("color", colorFrames_[i].color_);
            childElem.SetFloat("time", colorFrames_[i].time_);
        }
    }

    for (unsigned i = 0; i < textureFrames_.Size(); ++i)
    {
        childElem = dest.CreateChild("texanim");
        childElem.SetRect("uv", textureFrames_[i].uv_);
        childElem.SetFloat("time", textureFrames_[i].time_);
    }

    return true;
}

void ParticleEffect::SetMaterial(Material* material)
{
    material_ = material;
}

void ParticleEffect::SetNumParticles(unsigned num)
{
    numParticles_ = Max(0U, num);
}

void ParticleEffect::SetUpdateInvisible(bool enable)
{
    updateInvisible_ = enable;
}

void ParticleEffect::SetRelative(bool enable)
{
    relative_ = enable;
}

void ParticleEffect::SetScaled(bool enable)
{
    scaled_ = enable;
}

void ParticleEffect::SetSorted(bool enable)
{
    sorted_ = enable;
}

void ParticleEffect::SetFixedScreenSize(bool enable)
{
    fixedScreenSize_ = enable;
}

void ParticleEffect::SetAnimationLodBias(float lodBias)
{
    animationLodBias_ = lodBias;
}

void ParticleEffect::SetEmitterType(EmitterType type)
{
    emitterType_ = type;
}

void ParticleEffect::SetEmitterSize(const Vector3& size)
{
    emitterSize_ = size;
}

void ParticleEffect::SetMinDirection(const Vector3& direction)
{
    directionMin_ = direction;
}

void ParticleEffect::SetMaxDirection(const Vector3& direction)
{
    directionMax_ = direction;
}

void ParticleEffect::SetConstantForce(const Vector3& force)
{
    constantForce_ = force;
}

void ParticleEffect::SetDampingForce(float force)
{
    dampingForce_ = force;
}

void ParticleEffect::SetActiveTime(float time)
{
    activeTime_ = time;
}

void ParticleEffect::SetInactiveTime(float time)
{
    inactiveTime_ = time;
}

void ParticleEffect::SetMinEmissionRate(float rate)
{
    emissionRateMin_ = Max(rate, MIN_EMISSION_RATE);
}

void ParticleEffect::SetMaxEmissionRate(float rate)
{
    emissionRateMax_ = Max(rate, MIN_EMISSION_RATE);
}

void ParticleEffect::SetMinParticleSize(const Vector2& size)
{
    sizeMin_ = size;
}

void ParticleEffect::SetMaxParticleSize(const Vector2& size)
{
    sizeMax_ = size;
}

void ParticleEffect::SetMinTimeToLive(float time)
{
    timeToLiveMin_ = Max(time, 0.0f);
}

void ParticleEffect::SetMaxTimeToLive(float time)
{
    timeToLiveMax_ = Max(time, 0.0f);
}

void ParticleEffect::SetMinVelocity(float velocity)
{
    velocityMin_ = velocity;
}

void ParticleEffect::SetMaxVelocity(float velocity)
{
    velocityMax_ = velocity;
}

void ParticleEffect::SetMinRotation(float rotation)
{
    rotationMin_ = rotation;
}

void ParticleEffect::SetMaxRotation(float rotation)
{
    rotationMax_ = rotation;
}

void ParticleEffect::SetMinRotationSpeed(float speed)
{
    rotationSpeedMin_ = speed;
}

void ParticleEffect::SetMaxRotationSpeed(float speed)
{
    rotationSpeedMax_ = speed;
}


void ParticleEffect::SetSizeAdd(float sizeAdd)
{
    sizeAdd_ = sizeAdd;
}

void ParticleEffect::SetSizeMul(float sizeMul)
{
    sizeMul_ = sizeMul;
}

void ParticleEffect::AddColorTime(const Color& color, const float time)
{
    unsigned s = colorFrames_.Size();
    colorFrames_.Resize(s + 1);

    for (unsigned i = 0; i < s; i++)
    {
        if (colorFrames_[i].time_ > time)
        {
            for (unsigned j = s; j > i; j--)
            {
                colorFrames_[j].color_ = colorFrames_[j - 1].color_;
                colorFrames_[j].time_ = colorFrames_[j - 1].time_;
            }
            colorFrames_[i].color_ = color;
            colorFrames_[i].time_ = time;
            return;
        }
    }

    // highest time, add last:
    colorFrames_[s].color_ = color;
    colorFrames_[s].time_ = time;
}

void ParticleEffect::AddColorFrame(const ColorFrame& colorFrame)
{
    AddColorTime(colorFrame.color_, colorFrame.time_);
}

void ParticleEffect::RemoveColorFrame(unsigned index)
{
    unsigned s = colorFrames_.Size();

    for (unsigned i = index; i < s - 1; i++)
    {
        colorFrames_[i].color_ = colorFrames_[i + 1].color_;
        colorFrames_[i].time_ = colorFrames_[i + 1].time_;
    }

    colorFrames_.Resize(s - 1);
}

void ParticleEffect::SetColorFrames(const Vector<ColorFrame>& colorFrames)
{
    colorFrames_ = colorFrames;
}

void ParticleEffect::SetColorFrame(unsigned index, const ColorFrame& colorFrame)
{
    if (colorFrames_.Size() < index + 1)
        colorFrames_.Resize(index + 1);
    colorFrames_[index] = colorFrame;
}

void ParticleEffect::SetNumColorFrames(unsigned number)
{
    unsigned s = colorFrames_.Size();
    if (s != number)
        colorFrames_.Resize(number);
}

void ParticleEffect::SetFaceCameraMode(FaceCameraMode mode)
{
    faceCameraMode_ = mode;
}

void ParticleEffect::SortColorFrames()
{
    Vector<ColorFrame> cf = colorFrames_;
    colorFrames_.Clear();
    for (unsigned i = 0; i < cf.Size(); i++)
        AddColorFrame(cf[i]);
}

void ParticleEffect::AddTextureTime(const Rect& uv, const float time)
{
    unsigned s = textureFrames_.Size();
    textureFrames_.Resize(s + 1);

    for (unsigned i = 0; i < s; i++)
    {
        if (textureFrames_[i].time_ > time)
        {
            for (unsigned j = s; j > i; j--)
            {
                textureFrames_[j].uv_ = textureFrames_[j - 1].uv_;
                textureFrames_[j].time_ = textureFrames_[j - 1].time_;
            }
            textureFrames_[i].uv_ = uv;
            textureFrames_[i].time_ = time;
            return;
        }
    }

    // Highest time, add last
    textureFrames_[s].uv_ = uv;
    textureFrames_[s].time_ = time;
}

void ParticleEffect::AddTextureFrame(const TextureFrame& textureFrame)
{
    AddTextureTime(textureFrame.uv_, textureFrame.time_);
}

void ParticleEffect::RemoveTextureFrame(unsigned index)
{
    unsigned s = textureFrames_.Size();

    for (unsigned i = index; i < s - 1; i++)
    {
        textureFrames_[i].uv_ = textureFrames_[i + 1].uv_;
        textureFrames_[i].time_ = textureFrames_[i + 1].time_;
    }

    textureFrames_.Resize(s - 1);
}

void ParticleEffect::SetTextureFrames(const Vector<TextureFrame>& textureFrames)
{
    textureFrames_ = textureFrames;
}

void ParticleEffect::SetTextureFrame(unsigned index, const TextureFrame& textureFrame)
{
    if (textureFrames_.Size() < index + 1)
        textureFrames_.Resize(index + 1);
    textureFrames_[index] = textureFrame;
}

void ParticleEffect::SetNumTextureFrames(unsigned number)
{
    unsigned s = textureFrames_.Size();
    if (s != number)
        textureFrames_.Resize(number);
}

void ParticleEffect::SortTextureFrames()
{
    Vector<TextureFrame> tf = textureFrames_;
    textureFrames_.Clear();
    for (unsigned i = 0; i < tf.Size(); i++)
        AddTextureFrame(tf[i]);
}

SharedPtr<ParticleEffect> ParticleEffect::Clone(const String& cloneName) const
{
    SharedPtr<ParticleEffect> ret(new ParticleEffect(context_));

    ret->SetName(cloneName);
    ret->material_ = material_;
    ret->numParticles_ = numParticles_;
    ret->updateInvisible_ = updateInvisible_;
    ret->relative_ = relative_;
    ret->scaled_ = scaled_;
    ret->sorted_ = sorted_;
    ret->fixedScreenSize_ = fixedScreenSize_;
    ret->animationLodBias_ = animationLodBias_;
    ret->emitterType_ = emitterType_;
    ret->emitterSize_ = emitterSize_;
    ret->directionMin_ = directionMin_;
    ret->directionMax_ = directionMax_;
    ret->constantForce_ = constantForce_;
    ret->dampingForce_ = dampingForce_;
    ret->activeTime_ = activeTime_;
    ret->inactiveTime_ = inactiveTime_;
    ret->emissionRateMin_ = emissionRateMin_;
    ret->emissionRateMax_ = emissionRateMax_;
    ret->sizeMin_ = sizeMin_;
    ret->sizeMax_ = sizeMax_;
    ret->timeToLiveMin_ = timeToLiveMin_;
    ret->timeToLiveMax_ = timeToLiveMax_;
    ret->velocityMin_ = velocityMin_;
    ret->velocityMax_ = velocityMax_;
    ret->rotationMin_ = rotationMin_;
    ret->rotationMax_ = rotationMax_;
    ret->rotationSpeedMin_ = rotationSpeedMin_;
    ret->rotationSpeedMax_ = rotationSpeedMax_;
    ret->sizeAdd_ = sizeAdd_;
    ret->sizeMul_ = sizeMul_;
    ret->colorFrames_ = colorFrames_;
    ret->textureFrames_ = textureFrames_;
    ret->faceCameraMode_ = faceCameraMode_;
    /// \todo Zero if source was created programmatically
    ret->SetMemoryUse(GetMemoryUse());

    return ret;
}

const ColorFrame* ParticleEffect::GetColorFrame(unsigned index) const
{
    return index < colorFrames_.Size() ? &colorFrames_[index] : nullptr;
}

const TextureFrame* ParticleEffect::GetTextureFrame(unsigned index) const
{
    return index < textureFrames_.Size() ? &textureFrames_[index] : nullptr;
}

Vector3 ParticleEffect::GetRandomDirection() const
{
    return Vector3(Lerp(directionMin_.x_, directionMax_.x_, Random(1.0f)), Lerp(directionMin_.y_, directionMax_.y_, Random(1.0f)),
        Lerp(directionMin_.z_, directionMax_.z_, Random(1.0f)));
}

Vector2 ParticleEffect::GetRandomSize() const
{
    return sizeMin_.Lerp(sizeMax_, Random(1.0f));
}

float ParticleEffect::GetRandomVelocity() const
{
    return Lerp(velocityMin_, velocityMax_, Random(1.0f));
}

float ParticleEffect::GetRandomTimeToLive() const
{
    return Lerp(timeToLiveMin_, timeToLiveMax_, Random(1.0f));
}

float ParticleEffect::GetRandomRotationSpeed() const
{
    return Lerp(rotationSpeedMin_, rotationSpeedMax_, Random(1.0f));
}

float ParticleEffect::GetRandomRotation() const
{
    return Lerp(rotationMin_, rotationMax_, Random(1.0f));
}

void ParticleEffect::GetFloatMinMax(const XMLElement& element, float& minValue, float& maxValue)
{
    if (element.IsNull())
        return;

    if (element.HasAttribute("value"))
        minValue = maxValue = element.GetFloat("value");

    if (element.HasAttribute("min") && element.HasAttribute("max"))
    {
        minValue = element.GetFloat("min");
        maxValue = element.GetFloat("max");
    }
}

void ParticleEffect::GetVector2MinMax(const XMLElement& element, Vector2& minValue, Vector2& maxValue)
{
    if (element.IsNull())
        return;

    if (element.HasAttribute("value"))
        minValue = maxValue = element.GetVector2("value");

    if (element.HasAttribute("min") && element.HasAttribute("max"))
    {
        minValue = element.GetVector2("min");
        maxValue = element.GetVector2("max");
    }
}

void ParticleEffect::GetVector3MinMax(const XMLElement& element, Vector3& minValue, Vector3& maxValue)
{
    if (element.IsNull())
        return;

    if (element.HasAttribute("value"))
        minValue = maxValue = element.GetVector3("value");

    if (element.HasAttribute("min") && element.HasAttribute("max"))
    {
        minValue = element.GetVector3("min");
        maxValue = element.GetVector3("max");
    }
}


}
