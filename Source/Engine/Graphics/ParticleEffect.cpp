//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "Log.h"
#include "Material.h"
#include "ParticleEffect.h"
#include "ResourceCache.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

static const char* emitterTypeNames[] =
{
    "Sphere",
    "Box",
    0
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
    numParticles_(10),
    updateInvisible_(false),
    relative_(true),
    scaled_(true),
    sorted_(false),
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
    sizeMul_(1.0f)    
{
}

ParticleEffect::~ParticleEffect()
{
}

void ParticleEffect::RegisterObject(Context* context)
{
    context->RegisterFactory<ParticleEffect>();
}

bool ParticleEffect::Load(Deserializer& source)
{
    XMLFile file(context_);
    if (!file.Load(source))
    {
        LOGERROR("Load particle effect file failed");
        return false;
    }

    XMLElement rootElem = file.GetRoot();
    if (!rootElem)
    {
        LOGERROR("Particle emitter parameter file does not have a valid root element");
        return false;
    }

    if (rootElem.HasChild("material"))
        SetMaterial(GetSubsystem<ResourceCache>()->GetResource<Material>(rootElem.GetChild("material").GetAttribute("name")));

    if (rootElem.HasChild("numparticles"))
        SetNumParticles(rootElem.GetChild("numparticles").GetInt("value"));

    if (rootElem.HasChild("updateinvisible"))
        updateInvisible_ = rootElem.GetChild("updateinvisible").GetBool("enable");

    if (rootElem.HasChild("relative"))
        relative_ = rootElem.GetChild("relative").GetBool("enable");

    if (rootElem.HasChild("scaled"))
        scaled_ = rootElem.GetChild("scaled").GetBool("enable");

    if (rootElem.HasChild("sorted"))
        sorted_ = rootElem.GetChild("sorted").GetBool("enable");

    if (rootElem.HasChild("animlodbias"))
        SetAnimationLodBias(rootElem.GetChild("animlodbias").GetFloat("value"));

    if (rootElem.HasChild("emittertype"))
    {
        String type = rootElem.GetChild("emittertype").GetAttributeLower("value");
        if (type == "point")
        {
            // Point emitter type is deprecated, handled as zero sized sphere
            emitterType_ = EMITTER_SPHERE;
            emitterSize_ = Vector3::ZERO;
        }
        else if (type == "box")
            emitterType_ = EMITTER_BOX;
        else if (type == "sphere")
            emitterType_ = EMITTER_SPHERE;
        else
            LOGERROR("Unknown particle emitter type " + type);
    }

    if (rootElem.HasChild("emittersize"))
        emitterSize_ = rootElem.GetChild("emittersize").GetVector3("value");

    if (rootElem.HasChild("emitterradius"))
        emitterSize_.x_ = emitterSize_.y_ = emitterSize_.z_ = rootElem.GetChild("emitterradius").GetFloat("value");

    if (rootElem.HasChild("direction"))
        GetVector3MinMax(rootElem.GetChild("direction"), directionMin_, directionMax_);

    if (rootElem.HasChild("constantforce"))
        constantForce_ = rootElem.GetChild("constantforce").GetVector3("value");

    if (rootElem.HasChild("dampingforce"))
        dampingForce_ = rootElem.GetChild("dampingforce").GetFloat("value");

    if (rootElem.HasChild("activetime"))
        activeTime_ = rootElem.GetChild("activetime").GetFloat("value");
    if (activeTime_ < 0.0f)
        activeTime_ = M_INFINITY;

    if (rootElem.HasChild("inactivetime"))
        inactiveTime_ = rootElem.GetChild("inactivetime").GetFloat("value");
    if (inactiveTime_ < 0.0f)
        inactiveTime_ = M_INFINITY;

    if (rootElem.HasChild("emissionrate"))
        GetFloatMinMax(rootElem.GetChild("emissionrate"), emissionRateMin_, emissionRateMax_);

    if (rootElem.HasChild("interval"))
    {
        float intervalMin = 0.0f;
        float intervalMax = 0.0f;
        GetFloatMinMax(rootElem.GetChild("interval"), intervalMin, intervalMax);
        emissionRateMax_ = 1.0f / intervalMin;
        emissionRateMin_ = 1.0f / intervalMax;
    }

    if (rootElem.HasChild("particlesize"))
        GetVector2MinMax(rootElem.GetChild("particlesize"), sizeMin_, sizeMax_);

    if (rootElem.HasChild("timetolive"))
        GetFloatMinMax(rootElem.GetChild("timetolive"), timeToLiveMin_, timeToLiveMax_);

    if (rootElem.HasChild("velocity"))
        GetFloatMinMax(rootElem.GetChild("velocity"), velocityMin_, velocityMax_);

    if (rootElem.HasChild("rotation"))
        GetFloatMinMax(rootElem.GetChild("rotation"), rotationMin_, rotationMax_);

    if (rootElem.HasChild("rotationspeed"))
        GetFloatMinMax(rootElem.GetChild("rotationspeed"), rotationSpeedMin_, rotationSpeedMax_);

    if (rootElem.HasChild("sizedelta"))
    {
        XMLElement deltaElem = rootElem.GetChild("sizedelta");
        if (deltaElem.HasAttribute("add"))
            sizeAdd_ = deltaElem.GetFloat("add");
        if (deltaElem.HasAttribute("mul"))
            sizeMul_ = deltaElem.GetFloat("mul");
    }

    if (rootElem.HasChild("color"))
    {
        ColorFrame colorFrame(rootElem.GetChild("color").GetColor("value"));
        SetColorFrame(0, colorFrame);
    }

    if (rootElem.HasChild("colorfade"))
    {
        Vector<ColorFrame> fades;
        for (XMLElement colorFadeElem = rootElem.GetChild("colorfade"); colorFadeElem; colorFadeElem = colorFadeElem.GetNext("colorfade"))
            fades.Push(ColorFrame(colorFadeElem.GetColor("color"), colorFadeElem.GetFloat("time")));

        SetColorFrames(fades);
    }

    if (colorFrames_.Empty())
        colorFrames_.Push(ColorFrame(Color::WHITE));

    if (rootElem.HasChild("texanim"))
    {
        Vector<TextureFrame> animations;
        for (XMLElement animElem = rootElem.GetChild("texanim"); animElem; animElem = animElem.GetNext("texanim"))
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
    XMLFile file(context_);
    XMLElement rootElem = file.CreateRoot("particleeffect");

    XMLElement childElem = rootElem.CreateChild("material");
    childElem.SetAttribute("name", GetResourceName(material_));

    childElem = rootElem.CreateChild("numparticles");
    childElem.SetInt("value", numParticles_);

    childElem = rootElem.CreateChild("updateinvisible");
    childElem.SetBool("enable", updateInvisible_);

    childElem = rootElem.CreateChild("relative");
    childElem.SetBool("enable", relative_);

    childElem = rootElem.CreateChild("scaled");
    childElem.SetBool("enable", scaled_);

    childElem = rootElem.CreateChild("sorted");
    childElem.SetBool("enable", sorted_);

    childElem = rootElem.CreateChild("animlodbias");
    childElem.SetFloat("value", animationLodBias_);

    childElem = rootElem.CreateChild("emittertype");
    childElem.SetAttribute("value", emitterTypeNames[emitterType_]);

    childElem = rootElem.CreateChild("emittersize");
    childElem.SetVector3("value", emitterSize_);

    childElem = rootElem.CreateChild("direction");
    childElem.SetVector3("min", directionMin_);
    childElem.SetVector3("max", directionMax_);

    childElem = rootElem.CreateChild("constantforce");
    childElem.SetVector3("value", constantForce_);

    childElem = rootElem.CreateChild("dampingforce");
    childElem.SetFloat("value", dampingForce_);

    childElem = rootElem.CreateChild("activetime");
    childElem.SetFloat("value", activeTime_);

    childElem = rootElem.CreateChild("inactivetime");
    childElem.SetFloat("value", inactiveTime_);

    childElem = rootElem.CreateChild("emissionrate");
    childElem.SetFloat("min", emissionRateMin_);
    childElem.SetFloat("max", emissionRateMax_);

    childElem = rootElem.CreateChild("particlesize");
    childElem.SetVector2("min", sizeMin_);
    childElem.SetVector2("max", sizeMax_);

    childElem = rootElem.CreateChild("timetolive");
    childElem.SetFloat("min", timeToLiveMin_);
    childElem.SetFloat("max", timeToLiveMax_);

    childElem = rootElem.CreateChild("velocity");
    childElem.SetFloat("min", velocityMin_);
    childElem.SetFloat("max", velocityMax_);

    childElem = rootElem.CreateChild("rotation");
    childElem.SetFloat("min", rotationMin_);
    childElem.SetFloat("max", rotationMax_);

    childElem = rootElem.CreateChild("rotationspeed");
    childElem.SetFloat("min", rotationSpeedMin_);
    childElem.SetFloat("max", rotationSpeedMax_);

    childElem = rootElem.CreateChild("sizedelta");
    childElem.SetFloat("add", sizeAdd_);
    childElem.SetFloat("mul", sizeMul_);

    if (colorFrames_.Size() == 1)
    {
        childElem = rootElem.CreateChild("color");
        childElem.SetColor("value", colorFrames_[0].color_);
    }

    if (colorFrames_.Size() > 1)
    {
        for (unsigned i = 0; i < colorFrames_.Size(); ++i)
        {
            childElem = rootElem.CreateChild("colorfade");
            childElem.SetColor("color", colorFrames_[i].color_);
            childElem.SetFloat("time", colorFrames_[i].time_);
        }
    }

    for (unsigned i = 0; i < textureFrames_.Size(); ++i)
    {
        childElem = rootElem.CreateChild("texanim");
        childElem.SetRect("uv", textureFrames_[i].uv_);
        childElem.SetFloat("time", textureFrames_[i].time_);
    }

    return file.Save(dest);
}

void ParticleEffect::SetMaterial(Material* material)
{
    material_ = material;
}

void ParticleEffect::SetNumParticles(unsigned num)
{
    numParticles_ = Max(0, num);
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

const ColorFrame* ParticleEffect::GetColorFrame(unsigned index) const
{
    return index < colorFrames_.Size() ? &colorFrames_[index] : (ColorFrame*)0;
}

const TextureFrame* ParticleEffect::GetTextureFrame(unsigned index) const
{
    return index < colorFrames_.Size() ? &textureFrames_[index] : (TextureFrame*)0;
}

Vector3 ParticleEffect::GetRandomDirection() const
{
    return Vector3(
        Lerp(directionMin_.x_, directionMax_.x_, Random(1.0f)),
        Lerp(directionMin_.y_, directionMax_.y_, Random(1.0f)),
        Lerp(directionMin_.z_, directionMax_.z_, Random(1.0f))
        );
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
