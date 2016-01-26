//
// Copyright (c) 2008-2016 the Urho3D project.
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
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/XMLFile.h"
#include "../Urho2D/ParticleEffect2D.h"
#include "../Urho2D/Sprite2D.h"

#include "../DebugNew.h"

namespace Urho3D
{

static const int srcBlendFuncs[] =
{
    1,      // GL_ONE
    1,      // GL_ONE
    0x0306, // GL_DST_COLOR
    0x0302, // GL_SRC_ALPHA
    0x0302, // GL_SRC_ALPHA
    1,      // GL_ONE
    0x0305  // GL_ONE_MINUS_DST_ALPHA
};

static const int destBlendFuncs[] =
{
    0,      // GL_ZERO
    1,      // GL_ONE
    0,      // GL_ZERO
    0x0303, // GL_ONE_MINUS_SRC_ALPHA
    1,      // GL_ONE
    0x0303, // GL_ONE_MINUS_SRC_ALPHA
    0x0304  // GL_DST_ALPHA
};

ParticleEffect2D::ParticleEffect2D(Context* context) :
    Resource(context),
    sourcePositionVariance_(7.0f, 7.0f),
    speed_(260.0f),
    speedVariance_(10.0f),
    particleLifeSpan_(1.000f),
    particleLifespanVariance_(0.700f),
    angle_(0.0f),
    angleVariance_(360.0f),
    gravity_(0.0f, 0.0f),
    radialAcceleration_(-380.0f),
    tangentialAcceleration_(-140.0f),
    radialAccelVariance_(0.0f),
    tangentialAccelVariance_(0.0f),
    startColor_(1.0f, 0.0f, 0.0f, 1.0f),
    startColorVariance_(0.0f, 0.0f, 0.0f, 0.0f),
    finishColor_(1.0f, 1.0f, 0.0f, 1.0f),
    finishColorVariance_(0.0f, 0.0f, 0.0f, 0.0f),
    maxParticles_(600),
    startParticleSize_(60.0f),
    startParticleSizeVariance_(40.0f),
    finishParticleSize_(5.0f),
    FinishParticleSizeVariance_(5.0f),
    duration_(-1.0f),
    emitterType_(EMITTER_TYPE_GRAVITY),
    maxRadius_(100.0f),
    maxRadiusVariance_(0.0f),
    minRadius_(0.0f),
    minRadiusVariance_(0.0f),
    rotatePerSecond_(0.0f),
    rotatePerSecondVariance_(0.0f),
    blendMode_(BLEND_ALPHA),
    rotationStart_(0.0f),
    rotationStartVariance_(0.0f),
    rotationEnd_(0.0f),
    rotationEndVariance_(0.0f)
{
}

ParticleEffect2D::~ParticleEffect2D()
{
}

void ParticleEffect2D::RegisterObject(Context* context)
{
    context->RegisterFactory<ParticleEffect2D>();
}

bool ParticleEffect2D::BeginLoad(Deserializer& source)
{
    if (GetName().Empty())
        SetName(source.GetName());

    loadSpriteName_.Clear();

    XMLFile xmlFile(context_);
    if (!xmlFile.Load(source))
        return false;

    XMLElement rootElem = xmlFile.GetRoot("particleEmitterConfig");
    if (!rootElem)
        return false;

    String texture = rootElem.GetChild("texture").GetAttribute("name");
    loadSpriteName_ = GetParentPath(GetName()) + texture;
    // If async loading, request the sprite beforehand
    if (GetAsyncLoadState() == ASYNC_LOADING)
        GetSubsystem<ResourceCache>()->BackgroundLoadResource<Sprite2D>(loadSpriteName_, true, this);

    sourcePositionVariance_ = ReadVector2(rootElem, "sourcePositionVariance");

    speed_ = ReadFloat(rootElem, "speed");
    speedVariance_ = ReadFloat(rootElem, "speedVariance");

    particleLifeSpan_ = Max(0.01f, ReadFloat(rootElem, "particleLifeSpan"));
    particleLifespanVariance_ = ReadFloat(rootElem, "particleLifespanVariance");

    angle_ = ReadFloat(rootElem, "angle");
    angleVariance_ = ReadFloat(rootElem, "angleVariance");

    gravity_ = ReadVector2(rootElem, "gravity");

    radialAcceleration_ = ReadFloat(rootElem, "radialAcceleration");
    tangentialAcceleration_ = ReadFloat(rootElem, "tangentialAcceleration");

    radialAccelVariance_ = ReadFloat(rootElem, "radialAccelVariance");
    tangentialAccelVariance_ = ReadFloat(rootElem, "tangentialAccelVariance");

    startColor_ = ReadColor(rootElem, "startColor");
    startColorVariance_ = ReadColor(rootElem, "startColorVariance");

    finishColor_ = ReadColor(rootElem, "finishColor");
    finishColorVariance_ = ReadColor(rootElem, "finishColorVariance");

    maxParticles_ = ReadInt(rootElem, "maxParticles");

    startParticleSize_ = ReadFloat(rootElem, "startParticleSize");
    startParticleSizeVariance_ = ReadFloat(rootElem, "startParticleSizeVariance");

    finishParticleSize_ = ReadFloat(rootElem, "finishParticleSize");
    // Typo in pex file
    FinishParticleSizeVariance_ = ReadFloat(rootElem, "FinishParticleSizeVariance");

    duration_ = M_INFINITY;
    if (rootElem.HasChild("duration"))
    {
        float duration = ReadFloat(rootElem, "duration");
        if (duration > 0.0f)
            duration_ = duration;
    }


    emitterType_ = (EmitterType2D)ReadInt(rootElem, "emitterType");

    maxRadius_ = ReadFloat(rootElem, "maxRadius");
    maxRadiusVariance_ = ReadFloat(rootElem, "maxRadiusVariance");
    minRadius_ = ReadFloat(rootElem, "minRadius");
    minRadiusVariance_ = ReadFloat(rootElem, "minRadiusVariance");

    rotatePerSecond_ = ReadFloat(rootElem, "rotatePerSecond");
    rotatePerSecondVariance_ = ReadFloat(rootElem, "rotatePerSecondVariance");

    int blendFuncSource = ReadInt(rootElem, "blendFuncSource");
    int blendFuncDestination = ReadInt(rootElem, "blendFuncDestination");
    blendMode_ = BLEND_ALPHA;
    for (int i = 0; i < MAX_BLENDMODES; ++i)
    {
        if (blendFuncSource == srcBlendFuncs[i] && blendFuncDestination == destBlendFuncs[i])
        {
            blendMode_ = (BlendMode)i;
            break;
        }
    }

    rotationStart_ = ReadFloat(rootElem, "rotationStart");
    rotationStartVariance_ = ReadFloat(rootElem, "rotationStartVariance");

    rotationEnd_ = ReadFloat(rootElem, "rotationEnd");
    rotationEndVariance_ = ReadFloat(rootElem, "rotationEndVariance");

    // Note: not accurate
    SetMemoryUse(source.GetSize());
    return true;
}

bool ParticleEffect2D::EndLoad()
{
    // Apply the sprite now
    if (!loadSpriteName_.Empty())
    {
        ResourceCache* cache = GetSubsystem<ResourceCache>();
        sprite_ = cache->GetResource<Sprite2D>(loadSpriteName_);
        if (!sprite_)
            URHO3D_LOGERROR("Could not load sprite " + loadSpriteName_ + " for particle effect");

        loadSpriteName_.Clear();
    }

    return true;
}

bool ParticleEffect2D::Save(Serializer& dest) const
{
    if (!sprite_)
        return false;

    XMLFile xmlFile(context_);
    XMLElement rootElem = xmlFile.CreateRoot("particleEmitterConfig");

    String fileName = GetFileNameAndExtension(sprite_->GetName());
    rootElem.CreateChild("texture").SetAttribute("name", fileName);

    WriteVector2(rootElem, "sourcePosition", Vector2::ZERO);
    WriteVector2(rootElem, "sourcePositionVariance", sourcePositionVariance_);

    WriteFloat(rootElem, "speed", speed_);
    WriteFloat(rootElem, "speedVariance", speedVariance_);

    WriteFloat(rootElem, "particleLifeSpan", particleLifeSpan_);
    WriteFloat(rootElem, "particleLifespanVariance", particleLifespanVariance_);

    WriteFloat(rootElem, "angle", angle_);
    WriteFloat(rootElem, "angleVariance", angleVariance_);

    WriteVector2(rootElem, "gravity", gravity_);

    WriteFloat(rootElem, "radialAcceleration", radialAcceleration_);
    WriteFloat(rootElem, "tangentialAcceleration", tangentialAcceleration_);

    WriteFloat(rootElem, "radialAccelVariance", radialAccelVariance_);
    WriteFloat(rootElem, "tangentialAccelVariance", tangentialAccelVariance_);

    WriteColor(rootElem, "startColor", startColor_);
    WriteColor(rootElem, "startColorVariance", startColorVariance_);

    WriteColor(rootElem, "finishColor", finishColor_);
    WriteColor(rootElem, "finishColorVariance", finishColorVariance_);

    WriteInt(rootElem, "maxParticles", maxParticles_);

    WriteFloat(rootElem, "startParticleSize", startParticleSize_);
    WriteFloat(rootElem, "startParticleSizeVariance", startParticleSizeVariance_);

    WriteFloat(rootElem, "finishParticleSize", finishParticleSize_);
    // Typo in pex file
    WriteFloat(rootElem, "FinishParticleSizeVariance", FinishParticleSizeVariance_);

    float duration = duration_;
    if (duration == M_INFINITY)
        duration = -1.0f;
    WriteFloat(rootElem, "duration", duration);
    WriteInt(rootElem, "emitterType", (int)emitterType_);

    WriteFloat(rootElem, "maxRadius", maxRadius_);
    WriteFloat(rootElem, "maxRadiusVariance", maxRadiusVariance_);
    WriteFloat(rootElem, "minRadius", minRadius_);
    WriteFloat(rootElem, "minRadiusVariance", minRadiusVariance_);

    WriteFloat(rootElem, "rotatePerSecond", rotatePerSecond_);
    WriteFloat(rootElem, "rotatePerSecondVariance", rotatePerSecondVariance_);

    WriteInt(rootElem, "blendFuncSource", srcBlendFuncs[blendMode_]);
    WriteInt(rootElem, "blendFuncDestination", destBlendFuncs[blendMode_]);

    WriteFloat(rootElem, "rotationStart", rotationStart_);
    WriteFloat(rootElem, "rotationStartVariance", rotationStartVariance_);

    WriteFloat(rootElem, "rotationEnd", rotationEnd_);
    WriteFloat(rootElem, "rotationEndVariance", rotationEndVariance_);

    return xmlFile.Save(dest);
}

void ParticleEffect2D::SetSprite(Sprite2D* sprite)
{
    sprite_ = sprite;
}

void ParticleEffect2D::SetSourcePositionVariance(const Vector2& sourcePositionVariance)
{
    sourcePositionVariance_ = sourcePositionVariance;
}

void ParticleEffect2D::SetSpeed(float speed)
{
    speed_ = speed;
}

void ParticleEffect2D::SetSpeedVariance(float speedVariance)
{
    speedVariance_ = speedVariance;
}

void ParticleEffect2D::SetParticleLifeSpan(float particleLifeSpan)
{
    particleLifeSpan_ = particleLifeSpan;
}

void ParticleEffect2D::SetParticleLifespanVariance(float particleLifespanVariance)
{
    particleLifespanVariance_ = particleLifespanVariance;
}

void ParticleEffect2D::SetAngle(float angle)
{
    angle_ = angle;
}

void ParticleEffect2D::SetAngleVariance(float angleVariance)
{
    angleVariance_ = angleVariance;
}

void ParticleEffect2D::SetGravity(const Vector2& gravity)
{
    gravity_ = gravity;
}

void ParticleEffect2D::SetRadialAcceleration(float radialAcceleration)
{
    radialAcceleration_ = radialAcceleration;
}

void ParticleEffect2D::SetTangentialAcceleration(float tangentialAcceleration)
{
    tangentialAcceleration_ = tangentialAcceleration;
}

void ParticleEffect2D::SetRadialAccelVariance(float radialAccelVariance)
{
    radialAccelVariance_ = radialAccelVariance;
}

void ParticleEffect2D::SetTangentialAccelVariance(float tangentialAccelVariance)
{
    tangentialAccelVariance_ = tangentialAccelVariance;
}

void ParticleEffect2D::SetStartColor(const Color& startColor)
{
    startColor_ = startColor;
}

void ParticleEffect2D::SetStartColorVariance(const Color& startColorVariance)
{
    startColorVariance_ = startColorVariance;
}

void ParticleEffect2D::SetFinishColor(const Color& finishColor)
{
    finishColor_ = finishColor;
}

void ParticleEffect2D::SetFinishColorVariance(const Color& finishColorVariance)
{
    finishColorVariance_ = finishColorVariance;
}

void ParticleEffect2D::SetMaxParticles(int maxParticles)
{
    maxParticles_ = maxParticles;
}

void ParticleEffect2D::SetStartParticleSize(float startParticleSize)
{
    startParticleSize_ = startParticleSize;
}

void ParticleEffect2D::SetStartParticleSizeVariance(float startParticleSizeVariance)
{
    startParticleSizeVariance_ = startParticleSizeVariance;
}

void ParticleEffect2D::SetFinishParticleSize(float finishParticleSize)
{
    finishParticleSize_ = finishParticleSize;
}

void ParticleEffect2D::SetFinishParticleSizeVariance(float FinishParticleSizeVariance)
{
    FinishParticleSizeVariance_ = FinishParticleSizeVariance;
}

void ParticleEffect2D::SetDuration(float duration)
{
    duration_ = duration;
}

void ParticleEffect2D::SetEmitterType(EmitterType2D emitterType)
{
    emitterType_ = emitterType;
}

void ParticleEffect2D::SetMaxRadius(float maxRadius)
{
    maxRadius_ = maxRadius;
}

void ParticleEffect2D::SetMaxRadiusVariance(float maxRadiusVariance)
{
    maxRadiusVariance_ = maxRadiusVariance;
}

void ParticleEffect2D::SetMinRadius(float minRadius)
{
    minRadius_ = minRadius;
}

void ParticleEffect2D::SetMinRadiusVariance(float minRadiusVariance)
{
    minRadiusVariance_ = minRadiusVariance;
}

void ParticleEffect2D::SetRotatePerSecond(float rotatePerSecond)
{
    rotatePerSecond_ = rotatePerSecond;
}

void ParticleEffect2D::SetRotatePerSecondVariance(float rotatePerSecondVariance)
{
    rotatePerSecondVariance_ = rotatePerSecondVariance;
}

void ParticleEffect2D::SetBlendMode(BlendMode blendMode)
{
    blendMode_ = blendMode;
}

void ParticleEffect2D::SetRotationStart(float rotationStart)
{
    rotationStart_ = rotationStart;
}

void ParticleEffect2D::SetRotationStartVariance(float rotationStartVariance)
{
    rotationStartVariance_ = rotationStartVariance;
}

void ParticleEffect2D::SetRotationEnd(float rotationEnd)
{
    rotationEnd_ = rotationEnd;
}

void ParticleEffect2D::SetRotationEndVariance(float rotationEndVariance)
{
    rotationEndVariance_ = rotationEndVariance;
}

int ParticleEffect2D::ReadInt(const XMLElement& element, const String& name) const
{
    return element.GetChild(name).GetInt("value");
}

float ParticleEffect2D::ReadFloat(const XMLElement& element, const String& name) const
{
    return element.GetChild(name).GetFloat("value");
}

Color ParticleEffect2D::ReadColor(const XMLElement& element, const String& name) const
{
    XMLElement child = element.GetChild(name);
    return Color(child.GetFloat("red"), child.GetFloat("green"), child.GetFloat("blue"), child.GetFloat("alpha"));
}

Vector2 ParticleEffect2D::ReadVector2(const XMLElement& element, const String& name) const
{
    XMLElement child = element.GetChild(name);
    return Vector2(child.GetFloat("x"), child.GetFloat("y"));
}

void ParticleEffect2D::WriteInt(XMLElement& element, const String& name, int value) const
{
    XMLElement child = element.CreateChild(name);
    child.SetInt("value", value);
}

void ParticleEffect2D::WriteFloat(XMLElement& element, const String& name, float value) const
{
    XMLElement child = element.CreateChild(name);
    child.SetFloat("value", value);
}

void ParticleEffect2D::WriteColor(XMLElement& element, const String& name, const Color& color) const
{
    XMLElement child = element.CreateChild(name);
    child.SetFloat("red", color.r_);
    child.SetFloat("green", color.g_);
    child.SetFloat("blue", color.b_);
    child.SetFloat("alpha", color.a_);
}

void ParticleEffect2D::WriteVector2(XMLElement& element, const String& name, const Vector2& value) const
{
    XMLElement child = element.CreateChild(name);
    child.SetFloat("x", value.x_);
    child.SetFloat("y", value.y_);
}

}
