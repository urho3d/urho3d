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
#include "Log.h"
#include "Material.h"
#include "MemoryBuffer.h"
#include "ParticleEmitter.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "XMLFile.h"
#include "VectorBuffer.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(ParticleEmitter);

ParticleEmitter::ParticleEmitter(Context* context) :
    BillboardSet(context),
    emitterType_(EMITTER_POINT),
    emitterSize_(Vector3::ZERO),
    directionMin_(Vector3(-1.0f, -1.0f, -1.0f)),
    directionMax_(Vector3(1.0f, 1.0f, 1.0f)),
    constanceForce_(Vector3::ZERO),
    sizeMin_(Vector2(0.1f, 0.1f)),
    sizeMax_(Vector2(0.1f, 0.1f)),
    dampingForce_(0.0f),
    emitterRadius_(0.0f),
    periodTimer_(0.0f),
    emissionTimer_(0.0f),
    activeTime_(0.0f),
    inactiveTime_(0.0f),
    intervalMin_(0.1f),
    intervalMax_(0.1f),
    timeToLiveMin_(1.0f),
    timeToLiveMax_(1.0f),
    velocityMin_(1.0f),
    velocityMax_(1.0f),
    rotationMin_(0.0f),
    rotationMax_(0.0f),
    rotationSpeedMin_(0.0f),
    rotationSpeedMax_(0.0f),
    sizeAdd_(0.0f),
    sizeMul_(1.0f),
    active_(true),
    updateInvisible_(false),
    lastUpdateFrameNumber_(M_MAX_UNSIGNED)
{
    SetParticleColor(Color(1.0f, 1.0f, 1.0f));
    SetNumParticles(10);
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::RegisterObject(Context* context)
{
    context->RegisterFactory<ParticleEmitter>();

    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Animation LOD Bias", animationLodBias_, 1.0f);
    ATTRIBUTE(ParticleEmitter, VAR_BOOL, "Relative Scale", scaled_, true);
    ATTRIBUTE(ParticleEmitter, VAR_BOOL, "Is Active", active_, true);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Period Timer", periodTimer_, 0.0f);
    ATTRIBUTE(ParticleEmitter, VAR_FLOAT, "Emission Timer", emissionTimer_, 0.0f);
    ATTRIBUTE(ParticleEmitter, VAR_RESOURCEREF, "Parameter Source", parameterSource_, ResourceRef(XMLFile::GetTypeStatic()));
    ATTRIBUTE_MODE(ParticleEmitter, VAR_BUFFER, "Particles", particles_, PODVector<unsigned char>(), AM_SERIALIZATION);
    ATTRIBUTE_MODE(ParticleEmitter, VAR_BUFFER, "Billboards", billboards_, PODVector<unsigned char>(), AM_SERIALIZATION);
}

void ParticleEmitter::OnSetAttribute(const AttributeInfo& attr, const Variant& value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    switch (attr.offset_)
    {
    case offsetof(ParticleEmitter, parameterSource_):
        LoadParameters(cache->GetResource<XMLFile>(value.GetResourceRef().id_));
        break;
    
    case offsetof(ParticleEmitter, particles_):
        {
            MemoryBuffer buf(value.GetBuffer());
            SetNumParticles(buf.ReadVLE());
            for (PODVector<Particle>::Iterator i = particles_.Begin(); i != particles_.End(); ++i)
            {
                i->velocity_ = buf.ReadVector3();
                i->size_ = buf.ReadVector2();
                i->timer_ = buf.ReadFloat();
                i->timeToLive_ = buf.ReadFloat();
                i->scale_ = buf.ReadFloat();
                i->rotationSpeed_ = buf.ReadFloat();
                i->colorIndex_ = buf.ReadVLE();
                i->texIndex_ = buf.ReadVLE();
            }
        }
        break;
        
    default:
        BillboardSet::OnSetAttribute(attr, value);
        break;
    }
}

Variant ParticleEmitter::OnGetAttribute(const AttributeInfo& attr)
{
    switch (attr.offset_)
    {
    case offsetof(ParticleEmitter, parameterSource_):
        return GetResourceRef(parameterSource_, XMLFile::GetTypeStatic());
        
    case offsetof(ParticleEmitter, particles_):
        {
            VectorBuffer buf;
            buf.WriteVLE(particles_.Size());
            for (PODVector<Particle>::ConstIterator i = particles_.Begin(); i != particles_.End(); ++i)
            {
                buf.WriteVector3(i->velocity_);
                buf.WriteVector2(i->size_);
                buf.WriteFloat(i->timer_);
                buf.WriteFloat(i->timeToLive_);
                buf.WriteFloat(i->scale_);
                buf.WriteFloat(i->rotationSpeed_);
                buf.WriteVLE(i->colorIndex_);
                buf.WriteVLE(i->texIndex_);
            }
            return buf.GetBuffer();
        }
        
    default:
        return BillboardSet::OnGetAttribute(attr);
    }
}

void ParticleEmitter::Update(float timeStep)
{
    // If no invisible update, check that the billboardset is in view (framenumber has changed)
    if (!updateInvisible_)
    {
        if (viewFrameNumber_ == lastUpdateFrameNumber_)
            return;
    }
    lastUpdateFrameNumber_ = viewFrameNumber_;
    
    PROFILE(UpdateParticleEmitter);
    
    // If there is an amount mismatch between particles and billboards, correct it
    if (particles_.Size() != billboards_.Size())
        SetNumBillboards(particles_.Size());
    
    bool needBillboardUpdate = false;
    
    // Check active/inactive period switching
    periodTimer_ += timeStep;
    if (active_)
    {
        if ((activeTime_) && (periodTimer_ >= activeTime_))
        {
            active_ = false;
            periodTimer_ -= activeTime_;
        }
    }
    else
    {
        if ((inactiveTime_) && (periodTimer_ >= inactiveTime_))
        {
            active_ = true;
            periodTimer_ -= inactiveTime_;
        }
    }
    
    // Check for emitting a new particle
    if (active_)
    {
        emissionTimer_ += timeStep;
        if (emissionTimer_ > 0.0f)
        {
            emissionTimer_ -= Lerp(intervalMin_, intervalMax_, Random(1.0f));
            if (EmitNewParticle())
                needBillboardUpdate = true;
        }
    }
    
    // Update existing particles
    Vector3 relativeConstantForce = GetWorldRotation().Inverse() * constanceForce_;
    // If billboards are not relative, apply scaling to the position update
    Vector3 scaleVector = Vector3::UNITY;
    if ((scaled_) && (!relative_))
        scaleVector = GetWorldScale();
    
    for (unsigned i = 0; i < particles_.Size(); ++i)
    {
        Particle& particle = particles_[i];
        Billboard& billboard = billboards_[i];
        
        if (billboard.enabled_)
        {
            needBillboardUpdate = true;
            
            // Time to live
            if (particle.timer_ >= particle.timeToLive_)
            {
                billboard.enabled_ = false;
                continue;
            }
            particle.timer_ += timeStep;
            
            // Velocity & position
            if (constanceForce_ != Vector3::ZERO)
            {
                if (relative_)
                    particle.velocity_ += timeStep * relativeConstantForce;
                else
                    particle.velocity_ += timeStep * constanceForce_;
            }
            if (dampingForce_ != 0.0f)
            {
                Vector3 force = -dampingForce_ * particle.velocity_;
                particle.velocity_ += timeStep * force;
            }
            billboard.position_ += timeStep * particle.velocity_ * scaleVector;
            
            // Rotation
            billboard.rotation_ += timeStep * particle.rotationSpeed_;
            
            // Scaling
            if ((sizeAdd_ != 0.0f) || (sizeMul_ != 1.0f))
            {
                particle.scale_ += timeStep * sizeAdd_;
                if (sizeMul_ != 1.0f)
                    particle.scale_ *= (timeStep * (sizeMul_ - 1.0f)) + 1.0f;
                billboard.size_ = particle.size_ * particle.scale_;
            }
            
            // Color interpolation
            unsigned& index = particle.colorIndex_;
            if (index < colors_.Size())
            {
                if (index < colors_.Size() - 1)
                {
                    if (particle.timer_ >= colors_[index + 1].time_)
                        ++index;
                }
                if (index < colors_.Size() - 1)
                    billboard.color_ = colors_[index].interpolate(colors_[index + 1], particle.timer_);
                else
                    billboard.color_ = colors_[index].color_;
            }
            
            // Texture animation
            unsigned& texIndex = particle.texIndex_;
            if ((textureAnimation_.Size()) && (texIndex < textureAnimation_.Size() - 1))
            {
                if (particle.timer_ >= textureAnimation_[texIndex + 1].time_)
                {
                    billboard.uv_ = textureAnimation_[texIndex + 1].uv_;
                    ++texIndex;
                }
            }
        }
    }
    
    if (needBillboardUpdate)
        Updated();
}

bool ParticleEmitter::LoadParameters(XMLFile* file)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    if ((!file) || (!cache))
        return false;
    
    parameterSource_ = file;
    XMLElement rootElem = parameterSource_->GetRootElement();
    if (!rootElem)
        return false;
    
    if (rootElem.HasChildElement("material"))
        SetMaterial(cache->GetResource<Material>(rootElem.GetChildElement("material").GetString("name")));
    
    if (rootElem.HasChildElement("numparticles"))
        SetNumParticles(rootElem.GetChildElement("numparticles").GetInt("value"));
    
    if (rootElem.HasChildElement("sorted"))
        sorted_ = rootElem.GetChildElement("sorted").GetBool("enable");
    
    if (rootElem.HasChildElement("updateinvisible"))
        updateInvisible_ = rootElem.GetChildElement("updateinvisible").GetBool("enable");
    
    if (rootElem.HasChildElement("relative"))
        relative_ = rootElem.GetChildElement("relative").GetBool("enable");
    
    if (rootElem.HasChildElement("animlodbias"))
        SetAnimationLodBias(rootElem.GetChildElement("relative").GetFloat("value"));
    
    if (rootElem.HasChildElement("emittertype"))
    {
        String type = rootElem.GetChildElement("emittertype").GetStringLower("value");
        if (type == "point")
            emitterType_ = EMITTER_POINT;
        else if (type == "box")
            emitterType_ = EMITTER_BOX;
        else if (type == "sphere")
            emitterType_ = EMITTER_SPHERE;
        else
            LOGERROR("Unknown particle emitter type " + type);
    }
    
    if (rootElem.HasChildElement("emittersize"))
        emitterSize_ = rootElem.GetChildElement("emittersize").GetVector3("value");
    
    if (rootElem.HasChildElement("direction"))
        GetVector3MinMax(rootElem.GetChildElement("direction"), directionMin_, directionMax_);
    
    if (rootElem.HasChildElement("constantforce"))
        constanceForce_ = rootElem.GetChildElement("constantforce").GetVector3("value");
    
    if (rootElem.HasChildElement("dampingforce"))
        dampingForce_ = rootElem.GetChildElement("dampingforce").GetFloat("value");
    
    if (rootElem.HasChildElement("activetime"))
        activeTime_ = rootElem.GetChildElement("activetime").GetFloat("value");
    if (activeTime_ < 0.0f)
        activeTime_ = M_INFINITY;
    
    if (rootElem.HasChildElement("inactivetime"))
        inactiveTime_ = rootElem.GetChildElement("inactivetime").GetFloat("value");
    if (inactiveTime_ < 0.0f)
        inactiveTime_ = M_INFINITY;
    
    if (rootElem.HasChildElement("interval"))
        GetFloatMinMax(rootElem.GetChildElement("interval"), intervalMin_, intervalMax_);
    
    if (rootElem.HasChildElement("particlesize"))
        GetVector2MinMax(rootElem.GetChildElement("particlesize"), sizeMin_, sizeMax_);
    
    if (rootElem.HasChildElement("timetolive"))
        GetFloatMinMax(rootElem.GetChildElement("timetolive"), timeToLiveMin_, timeToLiveMax_);
    
    if (rootElem.HasChildElement("velocity"))
        GetFloatMinMax(rootElem.GetChildElement("velocity"), velocityMin_, velocityMax_);
    
    if (rootElem.HasChildElement("rotation"))
        GetFloatMinMax(rootElem.GetChildElement("rotation"), rotationMin_, rotationMax_);
    
    if (rootElem.HasChildElement("rotationspeed"))
        GetFloatMinMax(rootElem.GetChildElement("rotationspeed"), rotationSpeedMin_, rotationSpeedMax_);
    
    if (rootElem.HasChildElement("sizedelta"))
    {
        XMLElement deltaElem = rootElem.GetChildElement("sizedelta");
        if (deltaElem.HasAttribute("add"))
            sizeAdd_ = deltaElem.GetFloat("add");
        if (deltaElem.HasAttribute("mul"))
            sizeMul_ = deltaElem.GetFloat("mul");
    }
    
    if (rootElem.HasChildElement("color"))
        SetParticleColor(rootElem.GetChildElement("color").GetColor("value"));
    
    if (rootElem.HasChildElement("colorfade"))
    {
        Vector<ColorFade> fades;
        XMLElement colorFadeElem = rootElem.GetChildElement("colorfade");
        while (colorFadeElem)
        {
            ColorFade fade;
            fade.color_ = colorFadeElem.GetColor("color");
            fade.time_ = colorFadeElem.GetFloat("time");
            fades.Push(fade);
            
            colorFadeElem = colorFadeElem.GetNextElement("colorfade");
        }
        SetParticleColors(fades);
    }
    
    if (rootElem.HasChildElement("texanim"))
    {
        Vector<TextureAnimation> animations;
        XMLElement animElem = rootElem.GetChildElement("texanim");
        while (animElem)
        {
            TextureAnimation animation;
            animation.uv_ = animElem.GetRect("uv");
            animation.time_ = animElem.GetFloat("time");
            animations.Push(animation);
            animElem = animElem.GetNextElement("texanim");
        }
        textureAnimation_ = animations;
    }
    
    return true;
}

void ParticleEmitter::SetActive(bool enable, bool resetPeriod)
{
    if ((enable != active_) || (resetPeriod))
    {
        active_ = enable;
        periodTimer_ = 0.0f;
    }
}

void ParticleEmitter::SetNumParticles(int num)
{
    num = Max(num, 0);
    particles_.Resize(num);
    SetNumBillboards(num);
}

void ParticleEmitter::SetParticleColor(const Color& color)
{
    ColorFade newColor;
    newColor.color_ = color;
    newColor.time_ = 0.0f;
    
    colors_.Clear();
    colors_.Push(newColor);
}

void ParticleEmitter::SetParticleColors(const Vector<ColorFade>& colors)
{
    if (!colors.Size())
        return;
    
    colors_ = colors;
}

void ParticleEmitter::OnNodeSet(Node* node)
{
    if (node)
    {
        Scene* scene = node->GetScene();
        if (scene)
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(ParticleEmitter, HandleScenePostUpdate));
    }
    
    BillboardSet::OnNodeSet(node);
}

void ParticleEmitter::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace ScenePostUpdate;
    
    Update(eventData[P_TIMESTEP].GetFloat());
}

bool ParticleEmitter::EmitNewParticle()
{
    unsigned index = GetFreeParticle();
    if (index >= particles_.Size())
        return false;
    Particle& particle = particles_[index];
    Billboard& billboard = billboards_[index];
    
    Vector3 startPos;
    Vector3 startDir;
    
    switch (emitterType_)
    {
    case EMITTER_POINT:
        startPos = Vector3::ZERO;
        break;
        
    case EMITTER_BOX:
        startPos = Vector3(
            Random(emitterSize_.x_) - emitterSize_.x_ * 0.5f,
            Random(emitterSize_.y_) - emitterSize_.y_ * 0.5f,
            Random(emitterSize_.z_) - emitterSize_.z_ * 0.5f
        );
        break;
        
    case EMITTER_SPHERE:
        {
            Vector3 dir(
                Random(2.0f) - 1.0f,
                Random(2.0f) - 1.0f,
                Random(2.0f) - 1.0f
            );
            dir.Normalize();
            startPos = Random(emitterRadius_) * dir;
        }
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
        startPos = GetWorldTransform() * startPos;
        startDir = GetWorldRotation() * startDir;
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
    billboard.uv_ = textureAnimation_.Size() ? textureAnimation_[0].uv_ : Rect::POSITIVE;
    billboard.rotation_ = Lerp(rotationMin_, rotationMax_, Random(1.0f));
    billboard.color_ = colors_[0].color_;
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
    
    if ((element.HasAttribute("min")) && (element.HasAttribute("max")))
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
    
    if ((element.HasAttribute("min")) && (element.HasAttribute("max")))
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
    
    if ((element.HasAttribute("min")) && (element.HasAttribute("max")))
    {
        minValue = element.GetVector3("min");
        maxValue = element.GetVector3("max");
    }
}
