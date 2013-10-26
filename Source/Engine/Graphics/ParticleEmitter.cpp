//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "ParticleEmitter.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "ResourceEvents.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;

static const char* emitterTypeNames[] =
{
    "Sphere",
    "Box",
    0
};

static const unsigned MAX_PARTICLES_IN_FRAME = 100;
static const unsigned DEFAULT_NUM_PARTICLES = 10;
static const Vector2 DEFAULT_PARTICLE_SIZE(0.1f, 0.1f);
static const float DEFAULT_EMISSION_RATE = 10.0f;
static const float MIN_EMISSION_RATE = 0.01f;
static const float DEFAULT_TIME_TO_LIVE = 1.0f;
static const float DEFAULT_VELOCITY = 1.0f;
static const Vector3 DEFAULT_DIRECTION_MIN(-1.0f, -1.0f, -1.0f);
static const Vector3 DEFAULT_DIRECTION_MAX(1.0f, 1.0f, 1.0f);

template<> EmitterType Variant::Get<EmitterType>() const
{
    return (EmitterType)GetInt();
}

ParticleEmitter::ParticleEmitter(Context* context) :
    BillboardSet(context),
    emitterType_(EMITTER_SPHERE),
    emitterSize_(Vector3::ZERO),
    directionMin_(DEFAULT_DIRECTION_MIN),
    directionMax_(DEFAULT_DIRECTION_MAX),
    constantForce_(Vector3::ZERO),
    sizeMin_(DEFAULT_PARTICLE_SIZE),
    sizeMax_(DEFAULT_PARTICLE_SIZE),
    dampingForce_(0.0f),
    periodTimer_(0.0f),
    emissionTimer_(0.0f),
    activeTime_(0.0f),
    inactiveTime_(0.0f),
    emissionRateMin_(DEFAULT_EMISSION_RATE),
    emissionRateMax_(DEFAULT_EMISSION_RATE),
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
    emitting_(true),
    updateInvisible_(false),
    lastTimeStep_(0.0f),
    lastUpdateFrameNumber_(M_MAX_UNSIGNED)
{
    SetColor(Color::WHITE);
    SetNumParticles(DEFAULT_NUM_PARTICLES);
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::RegisterObject(Context* context)
{
    context->RegisterFactory<ParticleEmitter>(GEOMETRY_CATEGORY);
    
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_BOOL, "Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_RESOURCEREF, "Material", GetMaterialAttr, SetMaterialAttr, ResourceRef, ResourceRef(Material::GetTypeStatic()), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_INT, "Max Particles", GetNumParticles, SetNumParticles, unsigned, DEFAULT_NUM_PARTICLES, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Emission Rate Min", emissionRateMin_, DEFAULT_EMISSION_RATE, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Emission Rate Max", emissionRateMax_, DEFAULT_EMISSION_RATE, AM_DEFAULT);
    ENUM_ATTRIBUTE(ParticleEmitter, "Emitter Type", emitterType_, emitterTypeNames, EMITTER_SPHERE, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_VECTOR3, "Emitter Size", emitterSize_, Vector3::ZERO, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Active Time", activeTime_, 0.0f, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Inactive Time", inactiveTime_, 0.0f, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_BOOL, "Is Emitting", emitting_, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_BOOL, "Update When Invisible", GetUpdateInvisible, SetUpdateInvisible, bool, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_BOOL, "Relative Position", IsRelative, SetRelative, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_BOOL, "Relative Scale", IsScaled, SetScaled, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_BOOL, "Sort By Distance", IsSorted, SetSorted, bool, false, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Time To Live Min", timeToLiveMin_, DEFAULT_TIME_TO_LIVE, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Time To Live Max", timeToLiveMax_, DEFAULT_TIME_TO_LIVE, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_VECTOR2, "Particle Size Min", sizeMin_, DEFAULT_PARTICLE_SIZE, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_VECTOR2, "Particle Size Max", sizeMax_, DEFAULT_PARTICLE_SIZE, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_VECTOR3, "Direction Min", directionMin_, DEFAULT_DIRECTION_MIN, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_VECTOR3, "Direction Max", directionMax_, DEFAULT_DIRECTION_MAX, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Velocity Min", velocityMin_, DEFAULT_VELOCITY, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Velocity Max", velocityMax_, DEFAULT_VELOCITY, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Rotation Min", rotationMin_, 0.0f, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Rotation Max", rotationMax_, 0.0f, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Rotation Speed Min", rotationSpeedMin_, 0.0f, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Rotation Speed Max", rotationSpeedMax_, 0.0f, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_VECTOR3, "Constant Force", constantForce_, Vector3::ZERO, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Damping Force", dampingForce_, 0.0f, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Size Add", sizeAdd_, 0.0f, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Size Mul", sizeMul_, 1.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_VARIANTVECTOR, "Particle Colors", GetColorsAttr, SetColorsAttr, VariantVector, Variant::emptyVariantVector, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_VARIANTVECTOR, "UV Animation", GetTextureFramesAttr, SetTextureFramesAttr, VariantVector, Variant::emptyVariantVector, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_BOOL, "Can Be Occluded", IsOccludee, SetOccludee, bool, true, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_BOOL, "Cast Shadows", castShadows_, false, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Draw Distance", GetDrawDistance, SetDrawDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Shadow Distance", GetShadowDistance, SetShadowDistance, float, 0.0f, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Animation LOD Bias", GetAnimationLodBias, SetAnimationLodBias, float, 1.0f, AM_DEFAULT);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Period Timer", periodTimer_, 0.0f, AM_FILE);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Emission Timer", emissionTimer_, 0.0f, AM_FILE);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_VARIANTVECTOR, "Particles", GetParticlesAttr, SetParticlesAttr, VariantVector, Variant::emptyVariantVector, AM_FILE | AM_NOEDIT);
    ACCESSOR_ATTRIBUTE(ParticleEmitter, VAR_VARIANTVECTOR, "Billboards", GetBillboardsAttr, SetBillboardsAttr, VariantVector, Variant::emptyVariantVector, AM_FILE | AM_NOEDIT);
}

void ParticleEmitter::OnSetEnabled()
{
    BillboardSet::OnSetEnabled();
    
    Scene* scene = GetScene();
    if (scene)
    {
        if (IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(ParticleEmitter, HandleScenePostUpdate));
        else
            UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
    }
}

void ParticleEmitter::Update(const FrameInfo& frame)
{
    // Cancel update if has only moved but does not actually need to animate the particles
    if (!needUpdate_)
        return;
    
    // If there is an amount mismatch between particles and billboards, correct it
    if (particles_.Size() != billboards_.Size())
        SetNumBillboards(particles_.Size());
    
    bool needCommit = false;
    
    // Check active/inactive period switching
    periodTimer_ += lastTimeStep_;
    if (emitting_)
    {
        if (activeTime_ && periodTimer_ >= activeTime_)
        {
            emitting_ = false;
            periodTimer_ -= activeTime_;
        }
    }
    else
    {
        if (inactiveTime_ && periodTimer_ >= inactiveTime_)
        {
            emitting_ = true;
            periodTimer_ -= inactiveTime_;
        }
        // If emitter has an indefinite stop interval, keep period timer reset to allow restarting emission in the editor
        if (inactiveTime_ == 0.0f)
            periodTimer_ = 0.0f;
    }
    
    // Check for emitting new particles
    if (emitting_)
    {
        emissionTimer_ += lastTimeStep_;
        
        float intervalMin = 1.0f / Max(emissionRateMax_, MIN_EMISSION_RATE);
        float intervalMax = 1.0f / Max(emissionRateMin_, MIN_EMISSION_RATE);
        
        // If emission timer has a longer delay than max. interval, clamp it
        if (emissionTimer_ < -intervalMax)
            emissionTimer_ = -intervalMax;
        
        unsigned counter = MAX_PARTICLES_IN_FRAME;
        
        while (emissionTimer_ > 0.0f && counter)
        {
            emissionTimer_ -= Lerp(intervalMin, intervalMax, Random(1.0f));
            if (EmitNewParticle())
            {
                --counter;
                needCommit = true;
            }
            else
                break;
        }
    }
    
    // Update existing particles
    Vector3 relativeConstantForce = node_->GetWorldRotation().Inverse() * constantForce_;
    // If billboards are not relative, apply scaling to the position update
    Vector3 scaleVector = Vector3::ONE;
    if (scaled_ && !relative_)
        scaleVector = node_->GetWorldScale();
    
    for (unsigned i = 0; i < particles_.Size(); ++i)
    {
        Particle& particle = particles_[i];
        Billboard& billboard = billboards_[i];
        
        if (billboard.enabled_)
        {
            needCommit = true;
            
            // Time to live
            if (particle.timer_ >= particle.timeToLive_)
            {
                billboard.enabled_ = false;
                continue;
            }
            particle.timer_ += lastTimeStep_;
            
            // Velocity & position
            if (constantForce_ != Vector3::ZERO)
            {
                if (relative_)
                    particle.velocity_ += lastTimeStep_ * relativeConstantForce;
                else
                    particle.velocity_ += lastTimeStep_ * constantForce_;
            }
            if (dampingForce_ != 0.0f)
            {
                Vector3 force = -dampingForce_ * particle.velocity_;
                particle.velocity_ += lastTimeStep_ * force;
            }
            billboard.position_ += lastTimeStep_ * particle.velocity_ * scaleVector;
            
            // Rotation
            billboard.rotation_ += lastTimeStep_ * particle.rotationSpeed_;
            
            // Scaling
            if (sizeAdd_ != 0.0f || sizeMul_ != 1.0f)
            {
                particle.scale_ += lastTimeStep_ * sizeAdd_;
                if (sizeMul_ != 1.0f)
                    particle.scale_ *= (lastTimeStep_ * (sizeMul_ - 1.0f)) + 1.0f;
                billboard.size_ = particle.size_ * particle.scale_;
            }
            
            // Color interpolation
            unsigned& index = particle.colorIndex_;
            if (index < colorFrames_.Size())
            {
                if (index < colorFrames_.Size() - 1)
                {
                    if (particle.timer_ >= colorFrames_[index + 1].time_)
                        ++index;
                }
                if (index < colorFrames_.Size() - 1)
                    billboard.color_ = colorFrames_[index].Interpolate(colorFrames_[index + 1], particle.timer_);
                else
                    billboard.color_ = colorFrames_[index].color_;
            }
            
            // Texture animation
            unsigned& texIndex = particle.texIndex_;
            if (textureFrames_.Size() && texIndex < textureFrames_.Size() - 1)
            {
                if (particle.timer_ >= textureFrames_[texIndex + 1].time_)
                {
                    billboard.uv_ = textureFrames_[texIndex + 1].uv_;
                    ++texIndex;
                }
            }
        }
    }
    
    if (needCommit)
        Commit();
    
    needUpdate_ = false;
}

bool ParticleEmitter::Load(XMLFile* file)
{
    if (!file)
    {
        LOGERROR("Null particle emitter parameter file");
        return false;
    }
    
    XMLElement rootElem = file->GetRoot();
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
        SetAnimationLodBias(rootElem.GetChild("relative").GetFloat("value"));
    
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
        SetColor(rootElem.GetChild("color").GetColor("value"));
    
    if (rootElem.HasChild("colorfade"))
    {
        Vector<ColorFrame> fades;
        XMLElement colorFadeElem = rootElem.GetChild("colorfade");
        while (colorFadeElem)
        {
            fades.Push(ColorFrame(colorFadeElem.GetColor("color"), colorFadeElem.GetFloat("time")));
            
            colorFadeElem = colorFadeElem.GetNext("colorfade");
        }
        SetColors(fades);
    }
    
    if (rootElem.HasChild("texanim"))
    {
        Vector<TextureFrame> animations;
        XMLElement animElem = rootElem.GetChild("texanim");
        while (animElem)
        {
            TextureFrame animation;
            animation.uv_ = animElem.GetRect("uv");
            animation.time_ = animElem.GetFloat("time");
            animations.Push(animation);
            animElem = animElem.GetNext("texanim");
        }
        textureFrames_ = animations;
    }
    
    MarkNetworkUpdate();
    return true;
}

void ParticleEmitter::SetNumParticles(unsigned num)
{
    // Prevent negative value being assigned from the editor
    if (num > M_MAX_INT)
        num = 0;
    if (num > MAX_BILLBOARDS)
        num = MAX_BILLBOARDS;
    
    particles_.Resize(num);
    SetNumBillboards(num);
}

void ParticleEmitter::SetEmissionRate(float rate)
{
    SetMinEmissionRate(rate);
    SetMaxEmissionRate(rate);
}

void ParticleEmitter::SetMinEmissionRate(float rate)
{
    emissionRateMin_ = Max(rate, MIN_EMISSION_RATE);
    MarkNetworkUpdate();
}

void ParticleEmitter::SetMaxEmissionRate(float rate)
{
    emissionRateMax_ = Max(rate, MIN_EMISSION_RATE);
    MarkNetworkUpdate();
}

void ParticleEmitter::SetEmitterType(EmitterType type)
{
    emitterType_ = type;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetEmitterSize(const Vector3& size)
{
    emitterSize_ = size;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetActiveTime(float time)
{
    activeTime_ = time;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetInactiveTime(float time)
{
    inactiveTime_ = time;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetEmitting(bool enable, bool resetPeriod)
{
    if (enable != emitting_ || resetPeriod)
    {
        emitting_ = enable;
        periodTimer_ = 0.0f;
        MarkNetworkUpdate();
    }
}

void ParticleEmitter::SetUpdateInvisible(bool enable)
{
    updateInvisible_ = enable;
}

void ParticleEmitter::SetTimeToLive(float time)
{
    SetMinTimeToLive(time);
    SetMaxTimeToLive(time);
}

void ParticleEmitter::SetMinTimeToLive(float time)
{
    timeToLiveMin_ = Max(time, 0.0f);
    MarkNetworkUpdate();
}

void ParticleEmitter::SetMaxTimeToLive(float time)
{
    timeToLiveMax_ = Max(time, 0.0f);
    MarkNetworkUpdate();
}

void ParticleEmitter::SetParticleSize(const Vector2& size)
{
    SetMinParticleSize(size);
    SetMaxParticleSize(size);
}

void ParticleEmitter::SetMinParticleSize(const Vector2& size)
{
    sizeMin_ = size;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetMaxParticleSize(const Vector2& size)
{
    sizeMax_ = size;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetMinDirection(const Vector3& direction)
{
    directionMin_ = direction;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetMaxDirection(const Vector3& direction)
{
    directionMin_ = direction;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetVelocity(float velocity)
{
    SetMinVelocity(velocity);
    SetMaxVelocity(velocity);
}

void ParticleEmitter::SetMinVelocity(float velocity)
{
    velocityMin_ = velocity;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetMaxVelocity(float velocity)
{
    velocityMax_ = velocity;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetRotation(float rotation)
{
    SetMinRotation(rotation);
    SetMaxRotation(rotation);
}

void ParticleEmitter::SetMinRotation(float rotation)
{
    rotationMin_ = rotation;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetMaxRotation(float rotation)
{
    rotationMax_ = rotation;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetRotationSpeed(float speed)
{
    SetMinRotationSpeed(speed);
    SetMaxRotationSpeed(speed);
}

void ParticleEmitter::SetMinRotationSpeed(float speed)
{
    rotationSpeedMin_ = speed;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetMaxRotationSpeed(float speed)
{
    rotationSpeedMax_ = speed;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetConstantForce(const Vector3& force)
{
    constantForce_ = force;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetDampingForce(float force)
{
    dampingForce_ = force;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetSizeAdd(float sizeAdd)
{
    sizeAdd_ = sizeAdd;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetSizeMul(float sizeMul)
{
    sizeMul_ = sizeMul;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetColor(const Color& color)
{
    colorFrames_.Clear();
    colorFrames_.Push(ColorFrame(color));
    MarkNetworkUpdate();
}

void ParticleEmitter::SetColors(const Vector<ColorFrame>& colors)
{
    if (!colors.Size())
        return;
    
    colorFrames_ = colors;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetNumColors(unsigned num)
{
    colorFrames_.Resize(num);
    MarkNetworkUpdate();
}

void ParticleEmitter::SetTextureFrames(const Vector<TextureFrame>& animation)
{
    textureFrames_ = animation;
    MarkNetworkUpdate();
}

void ParticleEmitter::SetNumTextureFrames(unsigned num)
{
    textureFrames_.Resize(num);
}

void ParticleEmitter::SetParticlesAttr(VariantVector value)
{
    unsigned index = 0;
    SetNumParticles(index < value.Size() ? value[index++].GetUInt() : 0);
    
    for (PODVector<Particle>::Iterator i = particles_.Begin(); i != particles_.End() && index < value.Size(); ++i)
    {
        i->velocity_ = value[index++].GetVector3();
        i->size_ = value[index++].GetVector2();
        i->timer_ = value[index++].GetFloat();
        i->timeToLive_ = value[index++].GetFloat();
        i->scale_ = value[index++].GetFloat();
        i->rotationSpeed_ = value[index++].GetFloat();
        i->colorIndex_ = value[index++].GetInt();
        i->texIndex_ = value[index++].GetInt();
    }
}

VariantVector ParticleEmitter::GetParticlesAttr() const
{
    VariantVector ret;
    ret.Reserve(particles_.Size() * 8 + 1);
    ret.Push(particles_.Size());
    for (PODVector<Particle>::ConstIterator i = particles_.Begin(); i != particles_.End(); ++i)
    {
        ret.Push(i->velocity_);
        ret.Push(i->size_);
        ret.Push(i->timer_);
        ret.Push(i->timeToLive_);
        ret.Push(i->scale_);
        ret.Push(i->rotationSpeed_);
        ret.Push(i->colorIndex_);
        ret.Push(i->texIndex_);
    }
    return ret;
}

void ParticleEmitter::SetColorsAttr(VariantVector value)
{
    unsigned index = 0;
    unsigned numColors = index < value.Size() ? value[index++].GetUInt() : 0;
    // Prevent negative value being assigned from the editor
    if (numColors > M_MAX_INT)
        numColors = 0;
    
    colorFrames_.Resize(numColors);
    for (Vector<ColorFrame>::Iterator i = colorFrames_.Begin(); i < colorFrames_.End() && index < value.Size(); ++i)
    {
        i->color_ = value[index++].GetColor();
        i->time_ = value[index++].GetFloat();
    }
}

VariantVector ParticleEmitter::GetColorsAttr() const
{
    VariantVector ret;
    ret.Reserve(colorFrames_.Size() * 2 + 1);
    ret.Push(colorFrames_.Size());
    for (Vector<ColorFrame>::ConstIterator i = colorFrames_.Begin(); i < colorFrames_.End(); ++i)
    {
        ret.Push(i->color_);
        ret.Push(i->time_);
    }
    return ret;
}

void ParticleEmitter::SetTextureFramesAttr(VariantVector value)
{
    unsigned index = 0;
    unsigned numFrames = index < value.Size() ? value[index++].GetUInt() : 0;
    // Prevent negative value being assigned from the editor
    if (numFrames > M_MAX_INT)
        numFrames = 0;
    
    textureFrames_.Resize(numFrames);
    for (Vector<TextureFrame>::Iterator i = textureFrames_.Begin(); i < textureFrames_.End() && index < value.Size(); ++i)
    {
        i->uv_ = value[index++].GetVector4();
        i->time_ = value[index++].GetFloat();
    }
}

VariantVector ParticleEmitter::GetTextureFramesAttr() const
{
    VariantVector ret;
    ret.Reserve(textureFrames_.Size() * 2 + 1);
    ret.Push(textureFrames_.Size());
    for (Vector<TextureFrame>::ConstIterator i = textureFrames_.Begin(); i < textureFrames_.End(); ++i)
    {
        ret.Push(i->uv_.ToVector4());
        ret.Push(i->time_);
    }
    return ret;
}

void ParticleEmitter::OnNodeSet(Node* node)
{
    BillboardSet::OnNodeSet(node);
    
    if (node)
    {
        Scene* scene = GetScene();
        if (scene && IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(ParticleEmitter, HandleScenePostUpdate));
    }
}

bool ParticleEmitter::EmitNewParticle()
{
    unsigned index = GetFreeParticle();
    if (index == M_MAX_UNSIGNED)
        return false;
    assert(index < particles_.Size());
    Particle& particle = particles_[index];
    Billboard& billboard = billboards_[index];
    
    Vector3 startPos;
    Vector3 startDir;
    
    switch (emitterType_)
    {
    case EMITTER_SPHERE:
        {
            Vector3 dir(
                Random(2.0f) - 1.0f,
                Random(2.0f) - 1.0f,
                Random(2.0f) - 1.0f
            );
            dir.Normalize();
            startPos = emitterSize_ * dir * 0.5f;
        }
        break;
        
    case EMITTER_BOX:
        startPos = Vector3(
            Random(emitterSize_.x_) - emitterSize_.x_ * 0.5f,
            Random(emitterSize_.y_) - emitterSize_.y_ * 0.5f,
            Random(emitterSize_.z_) - emitterSize_.z_ * 0.5f
        );
        break;
    }
    
    startDir = Vector3(
        Lerp(directionMin_.x_, directionMax_.x_, Random(1.0f)),
        Lerp(directionMin_.y_, directionMax_.y_, Random(1.0f)),
        Lerp(directionMin_.z_, directionMax_.z_, Random(1.0f))
    );
    startDir.Normalize();
    
    if (!relative_)
    {
        startPos = node_->GetWorldTransform() * startPos;
        startDir = node_->GetWorldRotation() * startDir;
    };
    
    particle.velocity_ = Lerp(velocityMin_, velocityMax_, Random(1.0f)) * startDir;
    particle.size_ = sizeMin_.Lerp(sizeMax_, Random(1.0f));
    particle.timer_ = 0.0f;
    particle.timeToLive_ = Lerp(timeToLiveMin_, timeToLiveMax_, Random(1.0f));
    particle.scale_ = 1.0f;
    particle.rotationSpeed_ = Lerp(rotationSpeedMin_, rotationSpeedMax_, Random(1.0f));
    particle.colorIndex_ = 0;
    particle.texIndex_ = 0;
    
    billboard.position_ = startPos;
    billboard.size_ = particles_[index].size_;
    billboard.uv_ = textureFrames_.Size() ? textureFrames_[0].uv_ : Rect::POSITIVE;
    billboard.rotation_ = Lerp(rotationMin_, rotationMax_, Random(1.0f));
    billboard.color_ = colorFrames_[0].color_;
    billboard.enabled_ = true;
    
    return true;
}

unsigned ParticleEmitter::GetFreeParticle() const
{
    for (unsigned i = 0; i < billboards_.Size(); ++i)
    {
        if (!billboards_[i].enabled_)
            return i;
    }
    
    return M_MAX_UNSIGNED;
}

void ParticleEmitter::GetFloatMinMax(const XMLElement& element, float& minValue, float& maxValue)
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

void ParticleEmitter::GetVector2MinMax(const XMLElement& element, Vector2& minValue, Vector2& maxValue)
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

void ParticleEmitter::GetVector3MinMax(const XMLElement& element, Vector3& minValue, Vector3& maxValue)
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

void ParticleEmitter::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    // Store scene's timestep and use it instead of global timestep, as time scale may be other than 1
    using namespace ScenePostUpdate;
    
    lastTimeStep_ = eventData[P_TIMESTEP].GetFloat();
    
    // If no invisible update, check that the billboardset is in view (framenumber has changed)
    if (updateInvisible_ || viewFrameNumber_ != lastUpdateFrameNumber_)
    {
        lastUpdateFrameNumber_ = viewFrameNumber_;
        needUpdate_ = true;
        MarkForUpdate();
    }
}

}
